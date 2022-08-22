function [] = uavrt_detection()
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

configPath = "config/detectorConfig.txt"; %Must exist in the same directory as the execution of this executable

Config =  DetectorConfig(); %Build empty config object
updateconfig()              %Update (fill) the configuration
configUpdatedFlag = true;


% ROS2 Setup
%Only setup ROS2 for Matlab and
ros2Enable = true;
if ros2Enable
    fprintf("Preparing ROS2 Node and Messages...")
    node = ros2node("detector",0);
    pulsePub = ros2publisher(node,"/detected_pulse","uavrt_interfaces/Pulse");
    pulseMsg = ros2message(pulsePub);
    fprintf("complete.\n")
end

blankThresh = threshold(Config.falseAlarmProb);
% pulseStatsPriori = pulsestats(Config.tp, Config.tip, Config.tipu, ... % tp, tip, tipu
%     Config.tipj, 0 , 0 ,0 , [1 1], "D" ,... % tipj, fp, fstart, fend, tmplt, mode
%     makepulsestruc(), makepulsestruc(),...  % pl ,clst
%     [] ,[] , []);                           % cmsk ,cpki ,thresh)
pulseStatsPriori = pulsestats(Config.tp, Config.tip, Config.tipu, ... % tp, tip, tipu
    Config.tipj, 0 , 0 ,0 , [1 1], "D" ,... % tipj, fp, fstart, fend, tmplt, mode
    makepulsestruc(), makepulsestruc(),...  % pl ,clst
    [] ,[]);                                % cmsk ,cpki )



stftOverlapFraction = 0.5;
zetas = [0 0.5];

pauseWhenIdleTime   = 0.25;

%Initialize and then set these variable needed for buffer reads
overlapSamples	= 0;
sampsForKPulses = 0;
updatebufferreadvariables(pulseStatsPriori);

coder.varsize("dataReceived",[1025 1]);
coder.varsize("state",[1 64]);
packetLength = 1025; %1024 plus a time stamp.

%% Calculating the max size that would ever be needed for the buffer
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

dataWriterTimeIntervalNominal = 10; %Write interval in seconds. 2.5*60*4000*32/8 should work out the 2.4Mb of data at 4ksps.
dataWriterPacketsPerInterval  = ceil(dataWriterTimeIntervalNominal/((packetLength-1)/Config.Fs));
dataWriterTimeIntervalActual  = dataWriterPacketsPerInterval*packetLength/Config.Fs;
dataWriterSamples             = dataWriterPacketsPerInterval*packetLength;
%dataWriterBuffer             = zeros(packetLength,dataWriterPacketsPerInterval);
asyncWriteBuff                = dsp.AsyncBuffer(600650); %600650 is the result of the nominal settings of ceil(150/(1024/4000)*1025.
asyncWriteBuff.write(single(1+1i));%Write to give Code the type. Read to remove data. 
asyncWriteBuff.read();
dataWriterFileID    = fopen(Config.dataRecordPath,'w');
if dataWriterFileID == -1
    fprintf("UAV-RT: Error opening/creating data record file with error:\n")
end

% writer = dsp.BinaryFileWriter(Config.dataRecordPath);

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
% localThresh = NaN;
% coder.varsize('localThresh',[inf 1],[1 1]);

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
% ps_pre_struc.thresh = localThresh;


%Set max segments kepts in record for testing purposes
maxSegments = 100;

%Preallocate Xhold for Coder
Xhold = cell(maxSegments,1);
for i = 1:maxSegments
    Xhold{i} = waveform();
end

%Initialize loop variables
resetBuffersFlag = true;
framesReceived = 0;
segmentsProcessed = 0;
state = 'idle';
previousState = 'unspawned';
resetUdp = true;
staleDataFlag = true;%Force buffer  flush on start
idleTic = 1;
i = 1;
lastTimeStamp = 0;
cleanBuffer = true;
trackedCount = 0;

% errorFlag = true;
% if errorFlag
% count = fprintf(2,"UAV-RT: There was an error!\n");
% else


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
            [dataReceived]  = channelreceiver('0.0.0.0', Config.portData,resetUdp,false);
            resetUdp = false;

            %% Flush UDP buffer if data in the buffer is stale.
            if staleDataFlag
                fprintf('********STALE DATA FLAG: %u *********\n',uint32(staleDataFlag));
                runs = 0;
                while ~isempty(dataReceived)
                    fprintf('********CLEARING UDP DATA BUFFER*********\n');
                    [dataReceived]  = channelreceiver('0.0.0.0', Config.portData,resetUdp,false);
                    runs = runs+1;
                end
                staleDataFlag = false;
            end

            %% Wait for new data if none ready, else put data in buffers
            if isempty(dataReceived)
                pause((packetLength-1)/2*1/Config.Fs);
            else
                framesReceived = framesReceived + 1;
                timeStamp   = 10^-3*singlecomplex2int(dataReceived(1));
                iqData      = dataReceived(2:end);
                timeVector  = timeStamp+1/Config.Fs*(0:(numel(iqData)-1)).';
                %Check for missing packets based on packet timestamps.
                if asyncTimeBuff.NumUnreadSamples ~= 0
                    packetTimeDiffActual = timeStamp - lastTimeStamp;
                    packetTimeDiffExpect = (packetLength-1)/Config.Fs;
                    missingTime = packetTimeDiffActual - packetTimeDiffExpect;
                    missingPackets = missingTime*Config.Fs/(packetLength-1);
                    if  missingPackets > 1
                        fprintf('Packet drop detected. Missed %f packets, or %f seconds of data. \n', missingPackets, missingTime)
                    end
                    lastTimeStamp = timeStamp;
                else
                    lastTimeStamp = timeStamp;
                end
                %Write out data and time.
                asyncDataBuff.write(iqData);
                asyncTimeBuff.write(timeVector);
                asyncWriteBuff.write(dataReceived);
                if asyncWriteBuff.NumUnreadSamples == dataWriterSamples
                    dataWriterBuffData = asyncWriteBuff.read();
                    %dataWriterBuffDataComplexInterleave = [real(dataWriterBuffData), imag(dataWriterBuffData)].';
                    [~] = fwrite(dataWriterFileID,interleaveComplexVector(dataWriterBuffData),'single');
                end

            %end

            %% Process data if there is enough in the buffers
            if asyncDataBuff.NumUnreadSamples >= sampsForKPulses + overlapSamples
                fprintf('Buffer Full|| sampsForKPulses: %u, overlapSamples: %u,\n',uint32(sampsForKPulses),uint32(overlapSamples))
                fprintf('Running...Buffer full with %d samples. Processing. \n', asyncDataBuff.NumUnreadSamples)
                %i
                tic
                if cleanBuffer
                    x = asyncDataBuff.read(sampsForKPulses);%Overlap reads back into the buffer, but there isn't anything back there on the first segment. Will fill with overlapSamples zeros at beginning of x if you specify overlap here.
                    t = asyncTimeBuff.read(sampsForKPulses);
                    cleanBuffer = false;
                else
                    x = asyncDataBuff.read(sampsForKPulses, overlapSamples);
                    t = asyncTimeBuff.read(sampsForKPulses, overlapSamples);
                end
                %Check the timestamps in the buffer for gaps larger
                %than the max interpulse uncertainty. If there are
                %enough dropped packets such that the time is shifted
                %by more than the interpulse uncertainty, then the
                %detection will likely fail or produces bad results. In
                %this case. Skip the processing and clear the buffer.
                maxTimeUncertainty = Config.tipu + Config.tipj;
                integratedTimeError = sum(diff(t)-1/Config.Fs);
                if Config.K>1 & integratedTimeError > maxTimeUncertainty
                    fprintf('Significant time differences found in timestamp record. Skipping processing and clearing buffers.\n')
                    resetBuffersFlag = true;
                    staleDataFlag = true;  
                    
                else
                    t0 = t(1);
                    fprintf('Running...Building priori and waveform. \n')
                    %Set the priori info
                    if configUpdatedFlag
                        %Initialize states for different operational modes
                        suggestedMode = 'S';
                        switch Config.opMode
                            case 'freqSearchHardLock'
                                fLock = false;
                            case 'freqKnownHardLock'
                                fLock = true;
                            case 'freqSearchSoftLock'
                                fLock = false;
                            case 'freqAllNoLock'
                                fLock = false;
                        end
                        ps_pre = initializeps(Config);
                        configUpdatedFlag = false;
                    else
                        %ps_pre = pulsestats(ps_pre_struc.t_p, ps_pre_struc.t_ip, ps_pre_struc.t_ipu, ps_pre_struc.t_ipj ,ps_pre_struc.fp ,ps_pre_struc.fstart     ,ps_pre_struc.fend   ,ps_pre_struc.tmplt, ps_pre_struc.mode, ps_pre_struc.pl, ps_pre_struc.clst, ps_pre_struc.cmsk, ps_pre_struc.cpki, ps_pre_struc.thresh);
                        ps_pre = pulsestats(ps_pre_struc.t_p, ps_pre_struc.t_ip, ps_pre_struc.t_ipu, ps_pre_struc.t_ipj ,ps_pre_struc.fp ,ps_pre_struc.fstart     ,ps_pre_struc.fend   ,ps_pre_struc.tmplt, ps_pre_struc.mode, ps_pre_struc.pl, ps_pre_struc.clst, ps_pre_struc.cmsk, ps_pre_struc.cpki);
                        configUpdatedFlag = false;
                    end

                    
                    
                    %% PRIMARY PROCESSING BLOCK
                    %Prep waveform for processing/detection
                    X = waveform(x, Config.Fs, t0, ps_pre, stftOverlapFraction, threshold(Config.falseAlarmProb));
                    X.K = Config.K;
                    fprintf('Current interpulse params || N: %u, M: %u, J: %u,\n',uint32(X.N),uint32(X.M),uint32(X.J))
                    X.setprioridependentprops(X.ps_pre)
                    fprintf('Samples in waveform: %u \n',uint32(numel(X.x)))
                    tic
                    fprintf('Computing STFT...')
                    X.spectro();
                    fprintf('complete. Elapsed time: %f seconds \n', toc)
                    fprintf('Building weighting matrix and generating thresholds...')
                    tic
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
                            warning('UAV-RT: Unsupported mode requested. Defaulting to Discovery (D) mode.')
                            mode = 'D';
                    end

                    if strcmp(Config.opMode, 'freqAllNeverLock')
                        mode = 'D';
                    end
                    
                    if segmentsProcessed==0
                        X.thresh = X.thresh.makenewthreshold(X);
                    else
                        X.thresh = X.thresh.setthreshold(X,Xhold{segmentsProcessed});
                    end

                    fprintf('complete. Elapsed time: %f seconds \n', toc)
                    fprintf('Time windows in S: %u \n',uint32(size(X.stft.S,2)))
                    fprintf('Finding pulses...')
                    X.process(mode, 'most', Config.excldFreqs)
                    processingTime = toc;
                    fprintf('complete. Elapsed time: %f seconds \n', toc)
                    
                    %X.stft.displaystft()
                    
                    %% PREP FOR NEXT LOOP

                    %Latch/Release the frequency lock and setup the
                    %suggested mode
                    suggestedMode = X.ps_pos.mode;
                    pulsesConfirmed = all([X.ps_pos.pl.con_dec]);
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
                    if Config.K > 1 & processingTime > 0.9 * sampsForKPulses/Config.Fs
                        Config.K = Config.K - 1;
                        fprintf('WARNING!!! PROCESSING TIME TOOK LONGER THAN WAVEFORM LENGTH. STREAMING NOT POSSIBLE. REDUCING NUMBER OF PULSES CONSIDERED BY 1 TO K = %u \n',uint32(Config.K));
                        fprintf('Resetting all internal data buffers and udp buffers to clear potential stale data. \n');
                        resetBuffersFlag = true;
                        staleDataFlag = true;
                        suggestedMode = 'S';
                    end
                    segmentsProcessed = segmentsProcessed+1;

                    tic
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
                    fprintf('complete. Elapsed time: %f seconds \n', toc)
                    
                    %Deal with detected pulses
                    Xhold{mod(segmentsProcessed,maxSegments)} = X;%Keep a maxSegments running record of waveforms for debugging in Matlab
                    for j = 1:numel(ps_pre_struc.pl)
                        fprintf('Pulse at %e Hz detected. Confirmation status: %u \n', ps_pre_struc.pl(j).fp,uint32(ps_pre_struc.pl(j).con_dec))
                    end

                    if ros2Enable %Config.ros2enable & (coder.target('MATLAB') | coder.target("EXE"))
                        pulseCount = 0;
                        if ~isnan(X.ps_pos.cpki)
                            fprintf("Transmitting ROS2 pulse messages");
                            for j = 1:numel(X.ps_pos.cpki)
                                for k = 1:size(X.ps_pos.clst,2)
                                    %Set pulseMsg parameters for sending
                                    pulseMsg.detector_id        = char(Config.ID);
                                    pulseMsg.frequency          = Config.channelCenterFreqMHz + (X.ps_pos.clst(X.ps_pos.cpki(j),k).fp)*1e6;
                                    t_0     = X.ps_pos.clst(X.ps_pos.cpki(j),k).t_0;
                                    t_f     = X.ps_pos.clst(X.ps_pos.cpki(j),k).t_f;
                                    t_nxt_0 = X.ps_pos.clst(X.ps_pos.cpki(j),k).t_next(1);
                                    t_nxt_f = X.ps_pos.clst(X.ps_pos.cpki(j),k).t_next(2);
                                    pulseMsg.start_time.sec             = int32(floor(t_0));
                                    pulseMsg.start_time.nanosec         = uint32(mod(t_0,floor(t_0))*1e9);
                                    pulseMsg.end_time.sec               = int32(floor(t_f));
                                    pulseMsg.end_time.nanosec           = uint32(mod(t_f,floor(t_f))*1e9);
                                    pulseMsg.predict_next_start.sec     = int32(floor(t_nxt_0));
                                    pulseMsg.predict_next_start.nanosec = uint32(mod(t_nxt_0,floor(t_nxt_0))*1e9);
                                    pulseMsg.predict_next_end.sec       = int32(floor(t_nxt_f));
                                    pulseMsg.predict_next_end.nanosec   = uint32(mod(t_nxt_f,round(t_nxt_f))*1e9);
                                    pulseMsg.snr                = X.ps_pos.clst(X.ps_pos.cpki(j),k).SNR;
                                    pulseMsg.dft_real           = real(X.ps_pos.clst(X.ps_pos.cpki(j),k).yw);
                                    pulseMsg.dft_imag           = imag(X.ps_pos.clst(X.ps_pos.cpki(j),k).yw);
                                    pulseMsg.group_ind          = uint16(k);
                                    pulseMsg.detection_status   = X.ps_pos.clst(X.ps_pos.cpki(j),k).det_dec;
                                    pulseMsg.confirmed_status   = X.ps_pos.clst(X.ps_pos.cpki(j),k).con_dec;
                                    send(pulsePub,pulseMsg)
                                    pulseCount = pulseCount+1;
                                    fprintf(".");
                                end
                            end
                            fprintf("complete. Transmitted %u pulse(s).\n",uint32(pulseCount));
                        else
                            fprintf("\n");
                        end
                    end
                    fprintf('Current Mode: %s\n', ps_pre_struc.mode)
                    fprintf('====================================\n')
                end
            end
            end

            cmdReceived = controlreceiver('0.0.0.0', Config.portCntrl,false);
            previousState = state;
            state = checkcommand(cmdReceived,state);


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
            cmdReceived = controlreceiver('0.0.0.0', Config.portCntrl,false);
            previousState = state;
            state = checkcommand(cmdReceived,state);

        case 'updateconfig'
            %Write all remaining data in buffer before clearing
            dataWriterBuffData = asyncWriteBuff.read();
            count = fwrite(dataWriterFileID, interleaveComplexVector(dataWriterBuffData), 'sinlge');
            updateconfig();
            configUpdatedFlag = true;

            %Reset all the buffers and setup the buffer read variables
            asyncDataBuff.reset();
            asyncTimeBuff.reset();
            asyncWriteBuff.reset();
            ps_pre = initializeps(Config);
            updatebufferreadvariables(ps_pre);

            %Check control and update states
            staleDataFlag = true;
            resetUdp = true;
            cmdReceived = controlreceiver('0.0.0.0', Config.portCntrl,false);
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
                ps_pre = initializeps(Config);

                if ros2Enable %Config.ros2enable & (coder.target('MATLAB') | coder.target("EXE"))
                    fprintf("Transmitting ROS2 pulse messages");
                    pulseCount = 0;
                    for j = 1:1
                        %Set pulseMsg parameters for sending
                        pulseMsg.detector_id        = char(Config.ID);
                        pulseMsg.frequency          = Config.freqMHz ;
                        t_0     = posixtime(datetime('now'));
                        t_f     = 0;
                        t_nxt_0 = 1;
                        t_nxt_f = 2;
                        pulseMsg.start_time.sec             = int32(floor(t_0));
                        pulseMsg.start_time.nanosec         = uint32(mod(t_0,floor(t_0))*1e9);
                        pulseMsg.end_time.sec               = int32(floor(t_f));
                        pulseMsg.end_time.nanosec           = uint32(mod(t_f,floor(t_f))*1e9);
                        pulseMsg.predict_next_start.sec     = int32(floor(t_nxt_0));
                        pulseMsg.predict_next_start.nanosec = uint32(mod(t_nxt_0,floor(t_nxt_0))*1e9);
                        pulseMsg.predict_next_end.sec       = int32(floor(t_nxt_f));
                        pulseMsg.predict_next_end.nanosec   = uint32(mod(t_nxt_f,round(t_nxt_f))*1e9);
                        pulseMsg.snr                = 1;
                        pulseMsg.dft_real           = real(1);
                        pulseMsg.dft_imag           = imag(1);
                        pulseMsg.group_ind          = uint16(Config.K);
                        pulseMsg.detection_status   = false;
                        pulseMsg.confirmed_status   = true;
                        send(pulsePub,pulseMsg)
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
            cmdReceived = controlreceiver('0.0.0.0', Config.portCntrl,false);
            previousState = state;
            state = checkcommand(cmdReceived,state);

        case 'kill'
            %Send command to release the udp system objects
            controlreceiver('0.0.0.0', Config.portCntrl,true);
            channelreceiver('0.0.0.0', Config.portData,true,true);
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
            %release(writer);
            break

        otherwise
            %Should never get to this case, but jump to idle if we get
            %here.
            previousState = state;
            state = 'idle';
    end



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
            NaN, NaN);
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

    function [] = updatebufferreadvariables(ps_pre)
        %This function updates the buffer reading variables as needed by
        %the priori information about the pulse statistics. The segment
        %lengths depend on the interpulse duration and uncertainty
        %parameters.

        %persistent X0
        %if isempty(X0)
        %Build an empty waveform just so that we can calculate number
        %of overlapSamples. This is needed for buffer operations
        %X0 = waveform([], Config.Fs, 0, pulsestats, stftOverlapFraction);
        X0 = waveform([], Config.Fs, 0, ps_pre, stftOverlapFraction, threshold(0.01));
        %end

        %X0.ps_pre = ps_pre;
        X0.setprioridependentprops(ps_pre)
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



%                 tic
%                 fprintf('Checking packet loss...')
%                 %Here we check to see if the next segment started where
%                 %we expected based on the last segment. If packets were
%                 %dropped, the prediction will be less than the current
%                 %t0. Default to discovery mode in this case.
%                 if t0PrevSeg~=0
%                     packetLostFlag = (t0-t0PrevSeg)>(sampsForKPulses-overlapSamples)/Config.Fs;
%                     if packetLostFlag
%                         fprintf(['\n Difference between current segment start time and that predicted by the last \n', ...
%                             'segment is larger than expected and may indicate packet loss. Defaulting to \n',...
%                             'Discovery mode. Flushing UDP and data buffers after processing this segment.\n'])
%                         fprintf('Expected time difference: %f\n',(sampsForKPulses-overlapSamples)/Config.Fs)
%                         fprintf('Actual   time difference: %f\n',t0-t0PrevSeg)
%                         asyncDataBuff.reset();
%                         asyncTimeBuff.reset();
%                         staleDataFlag = true;
%                         t0PrevSeg = 0;
%                         mode = 'D';
%                     else
%                         staleDataFlag = false;
%                         t0PrevSeg = t0;
%                     end
%                 else
%                     staleDataFlag = false;
%                     t0PrevSeg = t0;
%                 end
%                 fprintf('complete. Elapsed time: %f seconds \n', toc)

