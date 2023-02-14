function [] = uavrt_detection()
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

 %#codegen
 coder.cinclude('time.h') %Needed for usleep function in generated code

configPath = "config/detectorConfig.txt"; %Must exist in the same directory as the execution of this executable

Config =  DetectorConfig(); %Build empty config object
updateconfig()              %Update (fill) the configuration
configUpdatedFlag = true;
 
% %Get current working directory
% if coder.target('MATLAB')
%     currDir = pwd;
% else
%     %Solution from https://www.mathworks.com/matlabcentral/answers/1843008-using-coder-ceval-to-getcwd
%     coder.cinclude('unistd.h');
%     bufferTemplate = repmat('c', 1, 200);
%     untokenizedDir = coder.nullcopy(bufferTemplate);
%     coder.ceval('getcwd', coder.ref(untokenizedDir), 200);
%     currDir = strtok(untokenizedDir, char(0));
% end


%Attempts at catching a failed getcwd() call
% Get current working directory
if coder.target('MATLAB')
    currDir = pwd;
else
     coder.cinclude('unistd.h');
     nullVal = coder.opaque('char*', 'NULL', 'HeaderFile', 'stdio.h');
     retVal = nullVal;
     bufferTemplate = repmat('c', 1, 200);
     untokenizedDir = coder.nullcopy(bufferTemplate);
     retVal = coder.ceval('getcwd', coder.ref(untokenizedDir), 200);
     if retVal == nullVal
         % Do some error handling here
         currDir = 'current_working_directory_error';
     else
         currDir = strtok(untokenizedDir, char(0));
     end
end

fprintf('Curr Directory is: %s\n',currDir)

% ROS2 Setup
ros2Enable = true;%Config.ros2enable; %Hard coded switch so that can be ROS2 can be turned off for testing/debugging
if ros2Enable
    fprintf("Preparing ROS2 Node and Messages...")
    node = ros2node("detector",0);
    pulsePub = ros2publisher(node,"/pulse","uavrt_interfaces/Pulse");
    pulseMsg = ros2message(pulsePub);
    %pulseMsg = ros2message("uavrt_interfaces/Pulse");
    fprintf("complete.\n")
end

blankThresh = threshold(Config.falseAlarmProb);
pulseStatsPriori = pulsestats(Config.tp, Config.tip, Config.tipu, ... % tp, tip, tipu
                              Config.tipj, 0 , 0 ,0 , [1 1], "D" ,... % tipj, fp, fstart, fend, tmplt, mode
                              makepulsestruc(), makepulsestruc(),...  % pl ,clst
                              [] ,[]);                                % cmsk ,cpki)

stftOverlapFraction = 0.5;
zetas               = [0 0.5];
pauseWhenIdleTime   = 0.25;

%Initialize and then set these variable needed for buffer reads
overlapSamples	= 0;
sampsForKPulses = 0;
updatebufferreadvariables(pulseStatsPriori);

coder.varsize("dataReceived",[1025 1]);
coder.varsize("state",[1 64]);
coder.varsize("previousState",[1 64]);
packetLength = 1025; %1024 plus a time stamp.
fprintf('Startup set 1 complete. \n')

%% Prepare data writing buffer
% Calculating the max size that would ever be needed for the buffer
% maxK    = 6;
% maxFs   = 912000/2;
% maxtp   = 0.04;
% maxtip  = 2;
% maxtipu = 0.1;
% maxpulseStatsPriori = pulsestats(maxtp,maxtip,maxtipu,[],[],[],[1 1],pulse);
% Xmax = waveform([], maxFs, 0, maxpulseStatsPriori, stftOverlapFraction);
% [~,~,~,maxn_ws,~,~,maxN,maxM] = Xmax.getprioridependentprops(Xmax.ps_pre);
% sampsForMaxPulses = maxK*maxn_ws*(maxN+maxM+1+1);
sampsForMaxPulses = 5800320;
asyncDataBuff = dsp.AsyncBuffer(sampsForMaxPulses);
asyncTimeBuff = dsp.AsyncBuffer(sampsForMaxPulses);
fprintf('Startup set 2 complete. \n')
dataWriterTimeIntervalNominal = 10; %Write interval in seconds. 2.5*60*4000*32/8 should work out the 2.4Mb of data at 4ksps.
dataWriterPacketsPerInterval  = ceil(dataWriterTimeIntervalNominal/((packetLength-1)/Config.Fs));
dataWriterTimeIntervalActual  = dataWriterPacketsPerInterval*packetLength/Config.Fs;
dataWriterSamples             = dataWriterPacketsPerInterval*packetLength;
asyncWriteBuff                = dsp.AsyncBuffer(600650); %600650 is the result of the nominal settings of ceil(150/(1024/4000)*1025.
asyncWriteBuff.write(single(1+1i));%Write to give Code the type. Read to remove data.
asyncWriteBuff.read();
dataWriterFileID    = fopen(Config.dataRecordPath,'w');
%dataWriterFileID    = fopen('output/data.bin','w');
if dataWriterFileID == -1
    fprintf("UAV-RT: Error opening/creating data record file with error:\n")
end
fprintf('Startup set 3 complete. \n')


%pulseWriterFileID    = fopen(cat(2,char(Config.processedOuputPath),'PULSE_LOG.txt'),'w');
%pulseWriterFileID    = fopen('pulse_log','w');
% pulseWriterFileID    = fopen('/config/data2.bin','w');
% if dataWriterFileID == -1
%     fprintf("UAV-RT: Error opening/creating pulse record file with error:\n")
% end
% 

fprintf('Startup set 4 complete. \n')



%Define a pulsestats structure that isn't an object.
%This is needed for the loop, as Matlab coder has problems seeing
%that the pulsestats handle object is set for all execution paths.
%Holding all these properties in a structure rather than the
%pulsestats object addressed this problem.
%Needed to let coder know that some of these will be varying in size
%https://www.mathworks.com/help/simulink/ug/how-working-with-matlab-classes-is-different-for-code-generation.html
localMode = 'D';
coder.varsize('localMode',[1 inf],[0 1]); %dims 0 if fixed, 1 if variable
localPl = makepulsestruc();
coder.varsize('localPl',[inf inf],[1 1]);
localClst = makepulsestruc();
coder.varsize('localClst',[inf inf],[1 1]);
localCmsk = false;
coder.varsize('localCmsk',[inf inf],[1 1]);
localCpki = NaN;
coder.varsize('localCpki',[inf 1],[1 1]);
fprintf('Startup set 5 complete. \n')
ps_pre_struc.t_p    = 0;
ps_pre_struc.t_ip   = 0;
ps_pre_struc.t_ipu  = 0;
ps_pre_struc.t_ipj  = 0;
ps_pre_struc.fp     = 0;
ps_pre_struc.fstart = 0;
ps_pre_struc.fend   = 0;
ps_pre_struc.tmplt  = [1 1];
ps_pre_struc.mode   = localMode;
ps_pre_struc.pl     = localPl;
ps_pre_struc.clst   = localClst;
ps_pre_struc.cmsk   = localCmsk;
ps_pre_struc.cpki   = localCpki;


% pulseOut.tag_id                     = uint32(0);%ID is a string
% pulseOut.detector_dir               = currDir;%ID is a string
% pulseOut.frequency                  = 0;
% pulseOut.start_time.sec             =  int32(0);
% pulseOut.start_time.nanosec         = uint32(0);
% pulseOut.end_time.sec               =  int32(0);
% pulseOut.end_time.nanosec           = uint32(0);
% pulseOut.predict_next_start.sec     =  int32(0);
% pulseOut.predict_next_start.nanosec = uint32(0);
% pulseOut.predict_next_end.sec       =  int32(0);
% pulseOut.predict_next_end.nanosec   = uint32(0);
% pulseOut.snr                        = 0;
% pulseOut.stft_score                 = 0;
% pulseOut.group_ind                  = uint16(0);
% pulseOut.group_snr                  = double(0);
% pulseOut.detection_status           = false;
% pulseOut.confirmed_status           = false;


udpPulseOut = dsp.UDPSender('RemoteIPPort',50000);


fprintf('Startup set 6 complete. \n')

%% Preallocate X and Xhold so that coder knows the data types.
coder.varsize("emptyData",[1, inf]);
exampleData = single(complex(wgn(1000,1,1,'linear','complex'))).';
Xhold = waveform(exampleData, Config.Fs, 0, pulseStatsPriori, stftOverlapFraction, threshold(Config.falseAlarmProb));
X     = waveform(exampleData, Config.Fs, 0, pulseStatsPriori, stftOverlapFraction, threshold(Config.falseAlarmProb));
Xhold.spectro();
X.spectro();

fprintf('Startup set 7 complete. \n')

%Initialize loop variables
resetBuffersFlag  = true;
framesReceived    = 0;
segmentsProcessed = 0;
previousState     = 'unspawned';
suggestedMode     = 'S';
fLock             = false;
resetUdp          = true;
staleDataFlag     = true;%Force buffer  flush on start
idleTic           = 1;
i                 = 1;
lastTimeStamp     = 0;
cleanBuffer       = true;
trackedCount      = 0;
startTime         = round(posixtime(datetime('now'))*1000000)/1000000;
sampleTimeInitial = 0;
%sysClockElapsedTime = 0;
tocAtLastCommandCheck = 0;
nReceived         = uint64(0);
currSampleCount   = uint64(0);
nextSampleCount   = uint64(0);
rawIdealSampleCount = uint64(0);
idealSampleCount  = uint64(0);
sampleOffset      = uint64(0);


if Config.startInRunState
    state = 'run';
else
    state = 'idle';
end

fprintf('Startup set 8 complete. Starting processing... \n')

while true %i <= maxInd

    switch state
        case 'run'

            if resetBuffersFlag
                asyncDataBuff.reset();
                asyncTimeBuff.reset();
                resetBuffersFlag =false;
                cleanBuffer = true;
            end

            %% Get data
            [dataReceived]  = channelreceiver('127.0.0.1', Config.portData,resetUdp,false);
            resetUdp = false;

            %% Flush UDP buffer if data in the buffer is stale.
            if staleDataFlag
                fprintf('********STALE DATA FLAG: %u *********\n',uint32(staleDataFlag));
                runs = 0;
                while ~isempty(dataReceived)
                    fprintf('********CLEARING UDP DATA BUFFER*********\n');
                    [dataReceived]  = channelreceiver('127.0.0.1', Config.portData,resetUdp,false);
                    runs = runs+1;
                end
                staleDataFlag = false;

                fprintf('********RESETTING TIMES*********\n');
                startTime = round(posixtime(datetime('now'))*1000000)/1000000;
                framesReceived = 0;
                currSampleCount = uint64(0);
                nextSampleCount = uint64(0);
                
                tic
            end

            %% Wait for new data if none ready, else put data in buffers
            if isempty(dataReceived)
                pauseTimeSec = 0.0001;
                %pauseTimeSec = (packetLength-1)/2*1/Config.Fs;
                if isdeployed
                    coder.ceval('usleep',uint32(pauseTimeSec * 1e6));
                else
                    pause(pauseTimeSec);  
                end
            else
                
                framesReceived = framesReceived + 1;
                
%                 timeStamp      = 10^-3*singlecomplex2int(dataReceived(1)); % OLD TIME STAMP METHOD
%                 iqData         = dataReceived(2:end);% OLD TIME STAMP METHOD
%                 timeVector     = timeStamp+1/Config.Fs*(0:(numel(iqData)-1)).';% OLD TIME STAMP METHOD
                
                iqData           = dataReceived(1:end-1);
                %samplesReceived = samplesReceived + numel(iqData);
                nReceived        = uint64(numel(iqData));
                currSampleCount  = nextSampleCount + nReceived;
                
                rawIdealSampleCount = uint64(singlecomplex2int(dataReceived(end)));

                if framesReceived == 1
                    sampleOffset = rawIdealSampleCount - nReceived;
                    lastTimeStamp = startTime - (double(nReceived) + 1) * 1/Config.Fs; %To estimate the timestamp of the sample before the first one in this first frame.
                end

                idealSampleCount = rawIdealSampleCount - sampleOffset;

                missingSamples  = idealSampleCount - currSampleCount;
                
                if missingSamples > 0 
                    zerosMissing = single(zeros(missingSamples, 1)) + 1i*single(zeros(missingSamples, 1));
                    iqDataToWrite = [zerosMissing(:); iqData];
                    nextSampleCount = nextSampleCount + nReceived + missingSamples;
                    fprintf('Missing samples detected. Filling with zeros for %u samples.',missingSamples);
                elseif missingSamples < 0
                    error('UAV-RT: Number of samples transmitted to the detector is less than that expected by the detector. Upstream processes (channelizer) may be transmitting more than 1024 IQ data samples per packet. This is not supported by this detetor.')
                else
                    iqDataToWrite = iqData;
                    nextSampleCount = nextSampleCount + nReceived; 
                end
                timeVector = lastTimeStamp + (1 : numel(iqDataToWrite)).' * 1/Config.Fs;
                lastTimeStamp = timeVector(end);

                %Check for missing packets based on packet timestamps.
                % if asyncTimeBuff.NumUnreadSamples ~= 0
                %     packetTimeDiffActual = timeStamp - lastTimeStamp;
                %     packetTimeDiffExpect = (packetLength-1)/Config.Fs;
                %     missingTime          = packetTimeDiffActual - packetTimeDiffExpect;
                %     missingPackets       = missingTime*Config.Fs/(packetLength-1);
                %     if  missingPackets > 1
                %         fprintf('Packet drop detected. Missed %f packets, or %f seconds of data. \n', missingPackets, missingTime)
                %     end
                %     lastTimeStamp = timeStamp;
                % else
                %     lastTimeStamp = timeStamp;
                % end

                %Write out data and time.
                asyncDataBuff.write(iqDataToWrite);
                asyncTimeBuff.write(timeVector);
                asyncWriteBuff.write(dataReceived);% OLD TIME STAMP METHOD
                %asyncWriteBuff.write([dataReceived; int2singlecomplex(timeAtPacketReceive*10^3)]);
                if asyncWriteBuff.NumUnreadSamples == dataWriterSamples
                    dataWriterBuffData = asyncWriteBuff.read();
                    [~] = fwrite(dataWriterFileID,interleaveComplexVector(dataWriterBuffData),'single');
                end

                %end

                %% Process data if there is enough in the buffers
                if asyncDataBuff.NumUnreadSamples >= sampsForKPulses + overlapSamples
                    fprintf('Buffer Full|| sampsForKPulses: %u, overlapSamples: %u,\n',uint32(sampsForKPulses),uint32(overlapSamples))
                    fprintf('Running...Buffer full with %d samples. Processing. \n', asyncDataBuff.NumUnreadSamples)
                    
%tic
previousToc = toc;
processingStartToc = previousToc;
% lastSampInBuffTimeStamp      = timeStamp; 
                    if cleanBuffer
                        %Overlap reads back into the buffer, but there 
                        %isn't anything back there on the first segment. 
                        %Using an overlap will fill the output with 
                        %overlapSamples of zeros at beginning 
                        %of x if you specify overlap here. Don't want that
                        %so specify zero overlap for first read after
                        %cleaning buffer
                        x = asyncDataBuff.read(sampsForKPulses);
                        t = asyncTimeBuff.read(sampsForKPulses);
                        cleanBuffer = false;
                    else
                        x = asyncDataBuff.read(sampsForKPulses, overlapSamples);
                        t = asyncTimeBuff.read(sampsForKPulses, overlapSamples);
                    end
% lastSampReadFromBuffTimeStamp = lastSampInBuffTimeStamp - double(1/Config.Fs*(asyncDataBuff.NumUnreadSamples));
% t     = lastSampReadFromBuffTimeStamp+1/Config.Fs*(-(sampsForKPulses-1):0).';
%plotstyle = ':-';
%plot(t,abs(x),plotstyle(1+mod(framesReceived,2)));hold on

% fprintf('TIME STAMP AT PROCESSING: %.6f \n NEXT PROCESSING TIME STAMP SHOULD BE: %.6f \n ',lastSampReadFromBuffTimeStamp, lastSampReadFromBuffTimeStamp + 1/Config.Fs*(sampsForKPulses - overlapSamples ));

plot(t,abs(x)); hold on
                    %Check the timestamps in the buffer for gaps larger
                    %than the max interpulse uncertainty. If there are
                    %enough dropped packets such that the time is shifted
                    %by more than the interpulse uncertainty, then the
                    %detection will likely fail or produces bad results. In
                    %this case. Skip the processing and clear the buffer.
                    maxTimeUncertainty  = Config.tipu + Config.tipj;
                    integratedTimeError = sum(diff(t) - 1/Config.Fs);
                    if Config.K>1 & integratedTimeError > maxTimeUncertainty
                        fprintf('Significant time differences found in timestamp record. Skipping processing and clearing buffers.\n')
                        resetBuffersFlag = true;
                        staleDataFlag    = true;
                    else
                        t0 = t(1);
                        fprintf('Running...Building priori and waveform. \n')
                        %Set the priori info
                        if configUpdatedFlag
                            %Initialize states for operational modes
                            switch Config.opMode
                                case 'freqSearchHardLock'
                                    fLock = false;
                                case 'freqKnownHardLock'
                                    fLock = true;
                                case 'freqSearchSoftLock'
                                    fLock = false;
                                case 'freqAllNoLock'
                                    fLock = false;
                                otherwise
                                    fLock = false;
                            end
                            prioriRelativeFreqHz = 10e-6 * abs(Config.tagFreqMHz - Config.channelCenterFreqMHz);
                            ps_pre = pulsestats(Config.tp, Config.tip, Config.tipu,...
                                                Config.tipj, prioriRelativeFreqHz ,0     ,0   ,[1 1],'D' ,...
                                                makepulsestruc(),makepulsestruc(),false , NaN);
                            configUpdatedFlag = false;
                        else
                            
                            ps_pre = pulsestats(ps_pre_struc.t_p, ps_pre_struc.t_ip, ps_pre_struc.t_ipu, ...
                                                ps_pre_struc.t_ipj ,ps_pre_struc.fp ,ps_pre_struc.fstart, ...
                                                ps_pre_struc.fend   ,ps_pre_struc.tmplt, ps_pre_struc.mode, ...
                                                ps_pre_struc.pl, ps_pre_struc.clst, ps_pre_struc.cmsk, ...
                                                ps_pre_struc.cpki);
                            configUpdatedFlag = false;
                        end


                        %% PRIMARY PROCESSING BLOCK
                        %Prep waveform for processing/detection
                        X = waveform(x, Config.Fs, t0, ps_pre, stftOverlapFraction, threshold(Config.falseAlarmProb));
                        X.K = Config.K;
                        fprintf('Current interpulse params || N: %u, M: %u, J: %u,\n',uint32(X.N),uint32(X.M),uint32(X.J))
                        X.setprioridependentprops(X.ps_pre)
                        fprintf('Samples in waveform: %u \n',uint32(numel(X.x)))
%tic
previousToc = toc;
                        fprintf('Computing STFT...')
                        X.spectro();
                        fprintf('complete. Elapsed time: %f seconds \n', toc - previousToc)
                        fprintf('Building weighting matrix and generating thresholds...')
%tic
previousToc = toc;
                        X.setweightingmatrix(zetas);

                        switch suggestedMode
                            case 'S'
                                if fLock
                                    mode = 'I';
                                else
                                    mode = 'D';
                                end
                            case 'C'
                                mode = 'C';
                            case 'T'
                                mode = 'T';
                                trackedCount = trackedCount + 1;
                            otherwise
                                msg = 'UAV-RT: Unsupported mode requested. Defaulting to Discovery (D) mode.';
                                if coder.target('MATLAB')
                                    warning(msg)
                                else
                                    fprintf(msg)
                                end
                                mode = 'D';
                        end

                        if strcmp(Config.opMode, 'freqAllNeverLock')
                            mode = 'D';
                        end

                        if segmentsProcessed==0
                            X.thresh = X.thresh.makenewthreshold(X);
                        else
                            X.thresh = X.thresh.setthreshold(X,Xhold);
                        end

                        fprintf('complete. Elapsed time: %f seconds \n', toc - previousToc)
                        fprintf('Time windows in S: %u \n',uint32(size(X.stft.S,2)))
                        fprintf('Finding pulses...')
                        X.process(mode, 'most', Config.excldFreqs)
                        processingTime = toc - processingStartToc;
                        fprintf('complete. Elapsed time: %f seconds \n', toc - previousToc)
                        fprintf('TOTAL PULSE PROCESSING TIME: %f seconds \n', processingTime)

                        %% PREP FOR NEXT LOOP

                        %Latch/Release the frequency lock and setup the
                        %suggested mode
                        suggestedMode = X.ps_pos.mode;
                        pulsesConfirmed = all([X.ps_pos.pl.con_dec],2);
                        if pulsesConfirmed%Check if all were confirmed
                            fLock = true;
                        end
                        %We only ever release if we are in softlock mode and
                        %only do so in that case if we are no longer confirming
                        %pulses.
                        if strcmp(Config.opMode, 'freqSearchSoftLock') & ~pulsesConfirmed
                            fLock = false;
                        end

                        %Decide when/how the priori is updated for the next
                        %segment's processing.
                        if pulsesConfirmed & (strcmp(mode,'C') || strcmp(mode,'T'))
                            X.ps_pos.updateposteriori(X.ps_pre, X.ps_pos.pl, 'freq')
                            if trackedCount > 5
                                trackedCount = 0;
                                X.ps_pos.updateposteriori(X.ps_pre, X.ps_pos.pl, 'time')
                            end
                        end

                        %Check lagging processing
                        if segmentsProcessed ~= 0 && Config.K > 1 && processingTime > 0.9 * sampsForKPulses/Config.Fs
                            %Config.K = Config.K - 1;
                            fprintf('WARNING!!! PROCESSING TIME TOOK LONGER THAN WAVEFORM LENGTH. STREAMING NOT POSSIBLE. TRY REDUCING NUMBER OF PULSES CONSIDERED BY 1 TO K = %u \n',uint32(Config.K));
                            fprintf('Resetting all internal data buffers and udp buffers to clear potential stale data. \n');
                            resetBuffersFlag = true;
                            staleDataFlag = true;
                            suggestedMode = 'S';
                        end
                        segmentsProcessed = segmentsProcessed+1;

%tic
previousToc = toc;
                        %Prepare priori for next segment
                        fprintf('Updating priori...\n')
                        ps_pre_struc.t_p   = X.ps_pos.t_p;
                        ps_pre_struc.t_ip  = X.ps_pos.t_ip;
                        ps_pre_struc.t_ipu = X.ps_pos.t_ipu;
                        ps_pre_struc.t_ipj = X.ps_pos.t_ipj;
                        ps_pre_struc.fp    = X.ps_pos.fp;
                        ps_pre_struc.fstart= X.ps_pos.fstart;
                        ps_pre_struc.fend  = X.ps_pos.fend;
                        ps_pre_struc.tmplt = X.ps_pos.tmplt;
                        ps_pre_struc.mode  = X.ps_pos.mode;
                        ps_pre_struc.pl    = X.ps_pos.pl;
                        ps_pre_struc.clst  = X.ps_pos.clst;
                        ps_pre_struc.cmsk  = X.ps_pos.cmsk;
                        ps_pre_struc.cpki  = X.ps_pos.cpki;

                        updatebufferreadvariables(X.ps_pos);
                        fprintf('complete. Elapsed time: %f seconds \n', toc - previousToc)

                        %Deal with detected pulses
                        %Xhold{mod(segmentsProcessed,maxSegments)} = X;%Keep a maxSegments running record of waveforms for debugging in Matlab
                        %Xstruct = obj2structrecursive(X);
                        %Xhold = X;
                        Xhold = waveformcopy(X);

                        for j = 1:numel(ps_pre_struc.pl)
                            fprintf('Pulse at %e Hz detected. SNR: %e Confirmation status: %u \n', ...
                                ps_pre_struc.pl(j).fp, ...
                                ps_pre_struc.pl(j).SNR, ...
                                uint32(ps_pre_struc.pl(j).con_dec))
                        end

                        pulseCount = 0;
                        if ~isnan(X.ps_pos.cpki)
                            fprintf("Transmitting ROS2 pulse messages");
                            for j = 1:numel(X.ps_pos.pl)
                                
                                % %% Build out pulseOut structure parameters for sending
                                % pulseOut.tag_id                     = uint32(Config.ID);
                                % pulseOut.detector_dir               = currDir;%ID is a string
                                % pulseOut.frequency                  = Config.channelCenterFreqMHz + (X.ps_pos.pl(j).fp)*1e-6;
                                %     t_0     = X.ps_pos.pl(j).t_0;
                                %     t_f     = X.ps_pos.pl(j).t_f;
                                %     t_nxt_0 = X.ps_pos.pl(j).t_next(1);
                                %     t_nxt_f = X.ps_pos.pl(j).t_next(2);
                                % pulseOut.start_time.sec             = int32(floor(t_0));
                                % pulseOut.start_time.nanosec         = uint32(mod(t_0,floor(t_0))*1e9);
                                % pulseOut.end_time.sec               = int32(floor(t_f));
                                % pulseOut.end_time.nanosec           = uint32(mod(t_f,floor(t_f))*1e9);
                                % pulseOut.predict_next_start.sec     = int32(floor(t_nxt_0));
                                % pulseOut.predict_next_start.nanosec = uint32(mod(t_nxt_0,floor(t_nxt_0))*1e9);
                                % pulseOut.predict_next_end.sec       = int32(floor(t_nxt_f));
                                % pulseOut.predict_next_end.nanosec   = uint32(mod(t_nxt_f,round(t_nxt_f))*1e9);
                                % pulseOut.snr                        = X.ps_pos.pl(j).SNR;
                                % pulseOut.stft_score                 = real(X.ps_pos.pl(j).yw);
                                % pulseOut.group_ind                  = uint16(j);
                                % groupSNRList                        = 10.^([X.ps_pos.pl(:).SNR]/10);%Average SNR in dB
                                % groupSNRMeanLinear                  = mean(groupSNRList,'all');
                                % if groupSNRMeanLinear<0
                                %     groupSNRMeanDB                  = -Inf;
                                % else
                                %     groupSNRMeanDB                  = 10*log10(groupSNRMeanLinear);
                                % end
                                % %10log10 can produce complex results and group_snr required a real value. Otherwise coder will
                                % %generate type errors
                                % pulseOut.group_snr          = double(groupSNRMeanDB);%10*log10(mean(10.^([X.ps_pos.clst(X.ps_pos.cpki(j),:).SNR]/10)));%Average SNR in dB
                                % pulseOut.detection_status   = X.ps_pos.pl(j).det_dec;
                                % pulseOut.confirmed_status   = X.ps_pos.pl(j).con_dec;

                                groupSNRList                        = 10.^([X.ps_pos.pl(:).SNR]/10);%Average SNR in dB
                                groupSNRMeanLinear                  = mean(groupSNRList,'all');
                                if groupSNRMeanLinear<0
                                    groupSNRMeanDB                  = -Inf;
                                else
                                    groupSNRMeanDB                  = 10*log10(groupSNRMeanLinear);
                                end
                                %10log10 can produce complex results and group_snr required a real value. Otherwise coder will
                                %generate type errors
                                groupSNR         = double(groupSNRMeanDB);%10*log10(mean(10.^([X.ps_pos.clst(X.ps_pos.cpki(j),:).SNR]/10)));%Average SNR in dB
                                

                                % Publish pulses to UDP
                                currPulseOut = pulseOut( X.ps_pos.pl(j), Config.ID, currDir, Config.channelCenterFreqMHz, j, groupSNR, []);
                                mavlinkTunnelMsg = currPulseOut.formatForTunnelMsg(255, 0, 0);    %tunnelPulse = formatPulseForTunnel(255, 0, 0, pulseOut);
                                udpPulseOut(mavlinkTunnelMsg);
                                

                                %% Package and send ROS2 pulse message
                                if ros2Enable
                                    pulseMsg.detector_dir               = char( currPulseOut.detector_dir );
                                    pulseMsg.tag_id                     = currPulseOut.tag_id;
                                    pulseMsg.frequency                  = currPulseOut.frequency;
                                    pulseMsg.start_time.sec             = currPulseOut.start_time_sec;
                                    pulseMsg.start_time.nanosec         = currPulseOut.start_time_nanosec;
                                    pulseMsg.end_time.sec               = currPulseOut.end_time_sec;
                                    pulseMsg.end_time.nanosec           = currPulseOut.end_time_nanosec;
                                    pulseMsg.predict_next_start.sec     = currPulseOut.predict_next_start_sec;
                                    pulseMsg.predict_next_start.nanosec = currPulseOut.predict_next_start_nanosec;
                                    pulseMsg.predict_next_end.sec       = currPulseOut.predict_next_end_sec;
                                    pulseMsg.predict_next_end.nanosec   = currPulseOut.predict_next_end_nanosec;
                                    pulseMsg.snr                        = currPulseOut.snr;
                                    pulseMsg.stft_score                 = currPulseOut.stft_score;
                                    pulseMsg.group_ind                  = currPulseOut.group_ind;
                                    pulseMsg.group_snr                  = currPulseOut.group_snr;
                                    pulseMsg.detection_status           = currPulseOut.detection_status;
                                    pulseMsg.confirmed_status           = currPulseOut.confirmed_status;

                                    send(pulsePub,pulseMsg)
                                end

                                pulseCount = pulseCount+1;


                                % %s pulseMsg.detector_dir
                                % %s pulseMsg.tag_id
                                % %.6f pulseMsg.frequency
                                % %d pulseMsg.start_time.sec
                                % %u pulseMsg.start_time.nanosec
                                % %d pulseMsg.end_time.sec
                                % %u pulseMsg.end_time.nanosec
                                % %d pulseMsg.predict_next_start.sec
                                % %u pulseMsg.predict_next_start.nanosec
                                % %d pulseMsg.predict_next_end.sec
                                % %u pulseMsg.predict_next_end.nanosec
                                % %.2f pulseMsg.snr
                                % %.3e pulseMsg.dft_real
                                % %.3e pulseMsg.dft_imag
                                % %u pulseMsg.group_ind
                                % %.2e pulseMsg.group_snr
                                % logicalStr = {'0','1'}
                                % %u logicalStr{int8(pulseMsg.detection_status)+1}
                                % %u logicalStr{int8(pulseMsg.confirmed_status)+1}
                                %
                                %                                         logicalStr = {'0','1'};
                                %                                         formatSpecPulseMsg = ['%.6f',',','%d',',','%u','%d',',','%u',',','%d',',','%u',',','%d',',','%u',',',...
                                %                                                               '%.2f',',','%.3e',',','%.3e',',','%u',',','%.2e',',','%c',',','%c','\n'];
                                %
                                %                                         fprintf(pulseWriterFileID,formatSpecPulseMsg,...
                                %                                             pulseMsg.frequency,...
                                %                                             pulseMsg.start_time.sec,...
                                %                                             pulseMsg.start_time.nanosec,...
                                %                                             pulseMsg.end_time.sec,...
                                %                                             pulseMsg.end_time.nanosec,...
                                %                                             pulseMsg.predict_next_start.sec,...
                                %                                             pulseMsg.predict_next_start.nanosec,...
                                %                                             pulseMsg.predict_next_end.sec,...
                                %                                             pulseMsg.predict_next_end.nanosec,...
                                %                                             pulseMsg.snr,...
                                %                                             pulseMsg.dft_real,...
                                %                                             pulseMsg.dft_imag,...
                                %                                             pulseMsg.group_ind,...
                                %                                             pulseMsg.group_snr,...
                                %                                             logicalStr{int8(pulseMsg.detection_status)+1},...
                                %                                             logicalStr{int8(pulseMsg.confirmed_status)+1});

                                fprintf(".");
                                %                                    end
                            end
                            fprintf("complete. Transmitted %u pulse(s).\n",uint32(pulseCount));
                        else
                            fprintf("\n");
                        end
                        fprintf('Current Mode: %s\n', ps_pre_struc.mode)
                        fprintf('====================================\n')
                    end
                    
                    elapsedTimeClock = round(posixtime(datetime('now'))*1000000)/1000000 - startTime;
                    elapsedTimeToc   = toc;
                    fprintf('tocElapsed - clockElapsed = %0.6f  **************** \n', elapsedTimeToc - elapsedTimeClock)
                    totalLoopTime = toc - processingStartToc;                    
                    fprintf('TOTAL SEGMENT PROCESSING TIME: %f seconds \n', totalLoopTime)
                    % packetTimeSec = (packetLength-1)*1/Config.Fs;
                    % segmentTimeSec  = 1/Config.Fs * sampsForKPulses;
                    % sleepTime = segmentTimeSec  - packetTimeSec -  totalLoopTime;
                    % if sleepTime < 0
                    %     fprintf('WARNING: CALCULATED SLEEP TIME IS NEGATIVE MEANING THAT I AM NOT KEEPING UP WITH THE INCOMING DATA RATE \n');
                    % else
                    %     % if isdeployed
                    %     %     coder.ceval('usleep',uint32(sleepTime * 1e6));
                    %     % else
                    %     %     pause(sleepTime);
                    %     % end
                    % end
                end
            end


            if toc >= 1 + tocAtLastCommandCheck %no faster than every 1 s check for new commands
                disp('*******************************************')
                disp('*******************************************')
                tocAtLastCommandCheck = toc;
                cmdReceived = controlreceiver('127.0.0.1', Config.portCntrl,false);
                previousState = state;
                state = checkcommand(cmdReceived,state);
            end

        case 'idle'
            if mod(idleTic,8) ==0
                fprintf('Waiting in idle state...\n')
                idleTic = 1;
            end
            idleTic = idleTic+1;
            dataWriterBuffData = asyncWriteBuff.read();
            count = fwrite(dataWriterFileID, interleaveComplexVector(dataWriterBuffData), 'single');

            asyncDataBuff.reset();
            asyncTimeBuff.reset();
            asyncWriteBuff.reset();

            pause(pauseWhenIdleTime);%Wait a bit so to throttle idle execution
            staleDataFlag = true;
            resetUdp = true;
            cmdReceived = controlreceiver('127.0.0.1', Config.portCntrl,false);
            previousState = state;
            state = checkcommand(cmdReceived,state);

        case 'updateconfig'
            %Write all remaining data in buffer before clearing
            dataWriterBuffData = asyncWriteBuff.read();
            count = fwrite(dataWriterFileID, interleaveComplexVector(dataWriterBuffData), 'single');
            updateconfig();
            configUpdatedFlag = true;

            %Reset all the buffers and setup the buffer read variables
            asyncDataBuff.reset();
            asyncTimeBuff.reset();
            asyncWriteBuff.reset();
            updatebufferreadvariables(initializeps(Config));

            %Check control and update states
            staleDataFlag = true;
            resetUdp = true;
            cmdReceived = controlreceiver('127.0.0.1', Config.portCntrl,false);
            if ~isempty(cmdReceived)
                previousState = state;
                state = checkcommand(cmdReceived,state);
            else %On no command after config update, default to previous state
                state = previousState;
                previousState = 'updateconfig';
            end

        case 'test'
            if mod(idleTic,8) ==0
                fprintf('In test mode. Publishing one test pulse per second.\n')
                idleTic = 1;
                
                % pulseOut.tag_id                     = uint32(Config.ID);
                % pulseOut.detector_dir               = currDir;%ID is a string
                % pulseOut.frequency                  = Config.tagFreqMHz;
                % t_0     = posixtime(datetime('now'));
                % t_f     = 0;
                % t_nxt_0 = 1;
                % t_nxt_f = 2;
                % pulseOut.start_time.sec             = int32(floor(t_0));
                % pulseOut.start_time.nanosec         = uint32(mod(t_0,floor(t_0))*1e9);
                % pulseOut.end_time.sec               = int32(floor(t_f));
                % pulseOut.end_time.nanosec           = uint32(mod(t_f,floor(t_f))*1e9);
                % pulseOut.predict_next_start.sec     = int32(floor(t_nxt_0));
                % pulseOut.predict_next_start.nanosec = uint32(mod(t_nxt_0,floor(t_nxt_0))*1e9);
                % pulseOut.predict_next_end.sec       = int32(floor(t_nxt_f));
                % pulseOut.predict_next_end.nanosec   = uint32(mod(t_nxt_f,round(t_nxt_f))*1e9);
                % pulseOut.snr                        = 1;
                % pulseOut.stft_score                 = 1;
                % pulseOut.group_ind                  = uint16(1);
                % pulseOut.group_snr          = 1;
                % pulseOut.detection_status   = false;
                % pulseOut.confirmed_status   = true;

                %% Publish pulses to UDP
                currPulseOut = pulseOut( );
                mavlinkTunnelMsg = currPulseOut.formatForTunnelMsg(255, 0, 0);  %tunnelPulse = formatPulseForTunnel(255, 0, 0, pulseOut);
                udpPulseOut(mavlinkTunnelMsg);

                if ros2Enable & (coder.target('MATLAB') | coder.target("EXE"))
                    fprintf("Transmitting ROS2 pulse messages");
                    pulseCount = 0;
                    for j = 1:1
                        %Set pulseMsg parameters for sending
%                         pulseMsg.tag_id        = uint32(Config.ID);
%                         pulseMsg.detector_dir  = currDir; %ID is a string
%                         pulseMsg.frequency          = Config.tagFreqMHz;
%                         t_0     = posixtime(datetime('now'));
%                         t_f     = 0;
%                         t_nxt_0 = 1;
%                         t_nxt_f = 2;
%                         pulseMsg.start_time.sec             = int32(floor(t_0));
%                         pulseMsg.start_time.nanosec         = uint32(mod(t_0,floor(t_0))*1e9);
%                         pulseMsg.end_time.sec               = int32(floor(t_f));
%                         pulseMsg.end_time.nanosec           = uint32(mod(t_f,floor(t_f))*1e9);
%                         pulseMsg.predict_next_start.sec     = int32(floor(t_nxt_0));
%                         pulseMsg.predict_next_start.nanosec = uint32(mod(t_nxt_0,floor(t_nxt_0))*1e9);
%                         pulseMsg.predict_next_end.sec       = int32(floor(t_nxt_f));
%                         pulseMsg.predict_next_end.nanosec   = uint32(mod(t_nxt_f,round(t_nxt_f))*1e9);
%                         pulseMsg.snr                = 1;
%                         pulseMsg.dft_real           = real(1);
%                         pulseMsg.dft_imag           = imag(1);
%                         pulseMsg.group_ind          = uint16(Config.K);
%                         pulseMsg.group_snr          = 1;
%                         pulseMsg.detection_status   = false;
%                         pulseMsg.confirmed_status   = true;
%                         send(pulsePub,pulseMsg)


                        %% Package and send ROS2 pulse message
                        if ros2Enable
                            pulseMsg.detector_dir               = char( currPulseOut.detector_dir );
                            pulseMsg.tag_id                     = currPulseOut.tag_id;
                            pulseMsg.frequency                  = currPulseOut.frequency;
                            pulseMsg.start_time.sec             = currPulseOut.start_time_sec;
                            pulseMsg.start_time.nanosec         = currPulseOut.start_time_nanosec;
                            pulseMsg.end_time.sec               = currPulseOut.end_time_sec;
                            pulseMsg.end_time.nanosec           = currPulseOut.end_time_nanosec;
                            pulseMsg.predict_next_start.sec     = currPulseOut.predict_next_start_sec;
                            pulseMsg.predict_next_start.nanosec = currPulseOut.predict_next_start_nanosec;
                            pulseMsg.predict_next_end.sec       = currPulseOut.predict_next_end_sec;
                            pulseMsg.predict_next_end.nanosec   = currPulseOut.predict_next_end_nanosec;
                            pulseMsg.snr                        = currPulseOut.snr;
                            pulseMsg.stft_score                 = currPulseOut.stft_score;
                            pulseMsg.group_ind                  = currPulseOut.group_ind;
                            pulseMsg.group_snr                  = currPulseOut.group_snr;
                            pulseMsg.detection_status           = currPulseOut.detection_status;
                            pulseMsg.confirmed_status           = currPulseOut.confirmed_status;

                            send(pulsePub,pulseMsg)
                        end

                        pulseCount = pulseCount+1;
                        fprintf(".");
                    end
                    fprintf("complete. Transmitted %u pulse(s).\n",uint32(pulseCount));

                    fprintf("\n");
                end


            end
            idleTic = idleTic+1;

            asyncDataBuff.reset();
            asyncTimeBuff.reset();
            asyncWriteBuff.reset();

            pause(pauseWhenIdleTime);%Wait a bit so to throttle idle execution
            staleDataFlag = true;
            resetUdp = true;
            cmdReceived = controlreceiver('127.0.0.1', Config.portCntrl,false);
            previousState = state;
            state = checkcommand(cmdReceived,state);

        case 'kill'
            %Send command to release the udp system objects
            controlreceiver('127.0.0.1', Config.portCntrl,true);
            channelreceiver('127.0.0.1', Config.portData,true,true);
            dataWriterBuffData = asyncWriteBuff.read();
            count = fwrite(dataWriterFileID, interleaveComplexVector(dataWriterBuffData), 'single');

            asyncDataBuff.reset();
            asyncTimeBuff.reset();
            asyncWriteBuff.reset();
            asyncDataBuff.release();
            asyncTimeBuff.release();
            asyncWriteBuff.release();

            previousState = state;
            fCloseStatus = fclose(dataWriterFileID);
            if fCloseStatus == -1
                error('UAV-RT: Error closing data record file. ')
            end

            
%             fCloseStatusPulseWriter = fclose(pulseWriterFileID);
%             if fCloseStatusPulseWriter == -1
%                 error('UAV-RT: Error closing pulse record file. ')
%             end

            %release(writer);
            break

        otherwise
            %Should never get to this case, but jump to idle if we get
            %here.
            previousState = state;
            state = 'idle';
    end



end

    function [mavlinkTunnelMsgUint8] = formatPulseForTunnel(target_system_in, target_component_in, payload_type_in, pulseStructIn)
         %% Build PulsePose Mavlink Tunnel Message Payload
         %Typecast maintains little-endian, in line
         %with the mavlink serialization standard: https://mavlink.io/en/guide/serialization.html
         target_system        = dec2hex(typecast(uint8(target_system_in),'uint8'), 2);                %uint8
         target_component     = dec2hex(typecast(uint8(target_component_in),'uint8'), 2);                  %uint8
         payload_type         = dec2hex(typecast(uint16(payload_type_in),'uint8'), 2);                 %uint16
         %payload_length      = dec2hex(typecast(uint8(0),'uint8'), 2);                  %uint8
         id                   = dec2hex(typecast(uint32(pulseStructIn.tag_id),'uint8'), 2);   %uint32
         freq                 = dec2hex(typecast(double(pulseStructIn.frequency),'uint8'), 2);                    %uint32
         start_time_sec       = dec2hex(typecast(int32(pulseStructIn.start_time.sec),'uint8'), 2);                %int32
         start_time_nanosec   = dec2hex(typecast(uint32(pulseStructIn.start_time.nanosec),'uint8'), 2);           %uint32
         predict_next_sec     = dec2hex(typecast(int32(pulseStructIn.predict_next_start.sec),'uint8'), 2);        %int32
         predict_next_nanosec = dec2hex(typecast(uint32(pulseStructIn.predict_next_start.nanosec),'uint8'), 2);   %uint32
         snr                  = dec2hex(typecast(double(pulseStructIn.snr),'uint8'), 2);          %double
         stft_score           = dec2hex(typecast(double(pulseStructIn.stft_score),'uint8'), 2);   %double
         group_ind            = dec2hex(typecast(uint16(pulseStructIn.group_ind),'uint8'), 2);    %uint16
         detection_status     = dec2hex(typecast(uint8(pulseStructIn.detection_status),'uint8'), 2);    %uint8
         confirmed_status     = dec2hex(typecast(uint8(pulseStructIn.confirmed_status),'uint8'), 2);    %uint8

         payload_hex = [id; freq; start_time_sec; start_time_nanosec; ...
                    predict_next_sec; predict_next_nanosec; snr; ...
                    stft_score; group_ind; detection_status; ...
                    confirmed_status];
         payload_length = dec2hex(typecast(uint8(size(payload_hex,1)),'uint8'),2);
         mavlinkTunnelMsgHex = [target_system; target_component; ...
                                payload_type; payload_length;...
                                payload_hex];
         mavlinkTunnelMsgUint8 = uint8( hex2dec( mavlinkTunnelMsgHex ) );
    end


    function [interleaveDataOut] = interleaveComplexVector(complexDataIn)
        %This function takes a vector of complex values, and interleaves
        %the real and complex parts to generate a output vector of 2x the
        %number of elements as the number of rows of the input.
        complexDataIn = complexDataIn(:);   %Enforce column vector
        dataMatrix = [real(complexDataIn), imag(complexDataIn)].';
        interleaveDataOut = dataMatrix(:);  %Interleave
    end

    function [ps] = initializeps(theConfig)
        %This sets up a standarized pulsestats object based on the config
        %passed to it.
        relativeFreqHz = 10e-6 * abs(theConfig.tagFreqMHz - theConfig.channelCenterFreqMHz);
        ps = pulsestats(theConfig.tp, theConfig.tip, theConfig.tipu,...
            theConfig.tipj,relativeFreqHz ,0     ,0   ,[1 1],'D' ,...
            makepulsestruc(),makepulsestruc(),false ,...
            NaN);
    end

    function [] = updateconfig()
        %Add code here to update the variables within the function that are
        %part of the configuration file. Will first need to load the correct
        %file and
        %
        Config =  DetectorConfig().setFromFile(configPath,-1);
        %Do we update the tip and tipu or use the ones that were adapted from
        %the previous detections? Probably just use the file. The supervisor
        %will have access to the detected pulses and can update these values if
        %it sees fit.

    end

    function [] = updatebufferreadvariables(ps_input)
        %This function updates the buffer reading variables as needed by
        %the priori information about the pulse statistics. The segment
        %lengths depend on the interpulse duration and uncertainty
        %parameters.

        %persistent X0
        %if isempty(X0)
        %Build an empty waveform just so that we can calculate number
        %of overlapSamples. This is needed for buffer operations
        %X0 = waveform([], Config.Fs, 0, pulsestats, stftOverlapFraction);
        X0 = waveform(single(complex([])), Config.Fs, 0, ps_input, stftOverlapFraction, threshold(0.01));
        %end

        %X0.ps_pre = ps_pre;
        X0.setprioridependentprops(ps_input)
        [~,~,n_ol,n_ws,~,~,N,M,J] = X0.getprioridependentprops(X0.ps_pre);
        %         overlapWindows  = 2*Config.K*M+1;
        %         overlapSamples	= n_ws*overlapWindows;
        %         %sampsForKPulses = Config.K*n_ws*(N+M+1+1);
        %         sampsForKPulses = n_ws*(Config.K*(N+M)+1+1);

        overlapWindows  = 2*(Config.K*M+J);
        overlapSamples	= n_ws*overlapWindows;
        %         if Config.K~=1
        %             sampsForKPulses = n_ws*(Config.K*(N+M)-2*M)+n_ol;
        %         else
        %             sampsForKPulses = n_ws*(N+M+J)+n_ol;
        %         end
        %See 2022-07-11 for updates to samples def
        sampsForKPulses = n_ws*(Config.K*(N+M)+J+1)+n_ol;

        fprintf('Updating buffer read vars|| N: %u, M: %u, J: %u,\n',uint32(N),uint32(M),uint32(J))
        fprintf('Updating buffer read vars|| sampForKPulses: %u,  overlapSamples: %u,\n',uint32(sampsForKPulses),uint32(overlapSamples))
    end


    function state = checkcommand(cmdReceived,currentState)
        %This function is designed to check the incoming command and decide what to
        %do based on the received command and the current state
        if ~isempty(cmdReceived)
            if cmdReceived == -1
                fprintf('Received kill command. \n')
                state = 'kill';
            elseif cmdReceived == 0
                fprintf('Received idle command. \n')
                state = 'idle';
            elseif cmdReceived == 1
                fprintf('Received run command. \n')
                state = 'run';
            elseif cmdReceived == 2
                fprintf('Received update config command. \n')
                state = 'updateconfig';
            elseif cmdReceived == 3
                fprintf('Received test command. \n')
                state = 'test';
            else
                %Invalid command. Continue with current state.
                state = currentState;
            end
        else
            %Nothing received. Continue with current state.
            state = currentState;
        end
    end



end


                                %% Build PulsePose Mavlink Tunnel Message Payload
                                %Typecast maintains little-endian, in line
                                %with the mavlink serialization standard: https://mavlink.io/en/guide/serialization.html
%                                 target_system                = dec2hex(typecast(uint8(255),'uint8'), 2);                %uint8
%                                 target_component             = dec2hex(typecast(uint8(0),'uint8'), 2);                  %uint8
%                                 payload_type                 = dec2hex(typecast(uint16(0),'uint8'), 2);                 %uint16
%                                 payload_length               = dec2hex(typecast(uint8(0),'uint8'), 2);                  %uint8
%                                 payload_id                   = dec2hex(typecast(uint32(pulseOut.tag_id),'uint8'), 2);   %uint32
%                                 payload_freq                 = dec2hex(typecast(double(pulseOut.frequency),'uint8'), 2);                    %uint32
%                                 payload_start_time_sec       = dec2hex(typecast(int32(pulseOut.start_time.sec),'uint8'), 2);                %int32
%                                 payload_start_time_nanosec   = dec2hex(typecast(uint32(pulseOut.start_time.nanosec),'uint8'), 2);           %uint32
%                                 payload_predict_next_sec     = dec2hex(typecast(int32(pulseOut.predict_next_start.sec),'uint8'), 2);        %int32
%                                 payload_predict_next_nanosec = dec2hex(typecast(uint32(pulseOut.predict_next_start.nanosec),'uint8'), 2);   %uint32
%                                 payload_snr                  = dec2hex(typecast(double(pulseOut.snr),'uint8'), 2);          %double
%                                 payload_stft_score           = dec2hex(typecast(double(pulseOut.stft_score),'uint8'), 2);   %double
%                                 payload_group_ind            = dec2hex(typecast(uint16(pulseOut.group_ind),'uint8'), 2);    %uint16
%                                 payload_detection_status     = dec2hex(typecast(uint8(pulseOut.detection_status),'uint8'), 2);    %uint8
%                                 payload_confirmed_status     = dec2hex(typecast(uint8(pulseOut.confirmed_status),'uint8'), 2);    %uint8
% 
%                                 payload = [payload_id; payload_freq; payload_start_time_sec; ...
%                                            payload_start_time_nanosec; payload_predict_next_sec;...
%                                            payload_predict_next_nanosec; payload_snr; ...
%                                            payload_stft_score; payload_group_ind; payload_detection_status; ...
%                                            payload_confirmed_status];
%                                 mavlinkTunnelMsgHex = [target_system; target_component; ...
%                                                        payload_type; payload_length;...
%                                                        payload];
%                                 mavlinkTunnelMsgUint8 = uint8( hex2dec( mavlinkTunnelMsgHex ) );

