% configPath            - Fully qualified path to detect config file
% thresholdCachePath    - Fully qualified path to where the threshold cache files are stored.
%                         If not specified thresholds will be re-generated.

function [] = uavrt_detection(configPath, thresholdCachePath)

 %#codegen
 coder.cinclude('time.h') %Needed for usleep function in generated code

if nargin == 0
    %Must exist in the same directory as the execution of this executable
    configPath          = "config/detectorConfig.txt"; 
    % Forces thresholds to be generated
    thresholdCachePath  = "";                              
end

global globalThresholdCachePath;
globalThresholdCachePath = thresholdCachePath;

Config =  DetectorConfig(); %Build empty config object
updateconfig()              %Update (fill) the configuration
configUpdatedFlag = true;
 

currDir = pwd;

% %Attempts at catching a failed getcwd() call
% % Get current working directory
% if coder.target('MATLAB')
%       currDir = pwd;  
% else
%      coder.cinclude('unistd.h');
%      nullVal = coder.opaque('char*', 'NULL', 'HeaderFile', 'stdio.h');
%      retVal = nullVal;
%      bufferTemplate = repmat('c', 1, 200);
%      untokenizedDir = coder.nullcopy(bufferTemplate);
%      retVal = coder.ceval('getcwd', coder.ref(untokenizedDir), 200);
%      if retVal == nullVal
%          % Do some error handling here
%          currDir = 'current_working_directory_error';
%      else
%          currDir = strtok(untokenizedDir, char(0));
%      end
% end

fprintf('Curr Directory is: %s\n',currDir)

[pulsePub, pulseMsg] = ros2Setup();

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

dataRecordFilename = sprintf('data_record.%d.%d.bin',int32(Config.ID),int32(Config.startIndex));
%dataWriterFileID    = fopen(fullfile(Config.logPath,dataRecordFilename),'w');%Use this after upgrade to R2023b that supports full file
dataWriterFileID    = fopen([char(Config.logPath),'/',char(dataRecordFilename)],'w');

if dataWriterFileID == -1
    fprintf("UAV-RT: Error opening/creating data record file with error:\n")
end
fprintf('Startup set 3 complete. \n')


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
fprintf('Startup set 4 complete. \n')
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


pulseInfoStruct = PulseInfoStruct();
pulseInfoStruct.udpSenderSetup("127.0.0.1", 50000);

% The specified frame size must exactly match the size of udp packets sent out by the channelizer.
channelizerSampleFrameSize = 1024;
udpReceiver = ComplexSingleSamplesUDPReceiver(Config.ipData, Config.portData, channelizerSampleFrameSize);

fprintf('Startup set 5 complete. \n')

%% Preallocate X and Xhold so that coder knows the data types.
coder.varsize("emptyData",[1, inf]);
exampleData = single(complex(wgn(1000,1,1,'linear','complex'))).';
Xhold = waveform(exampleData, Config.Fs, 0, pulseStatsPriori, stftOverlapFraction, threshold(Config.falseAlarmProb));
X     = waveform(exampleData, Config.Fs, 0, pulseStatsPriori, stftOverlapFraction, threshold(Config.falseAlarmProb));
Xhold.spectro();
X.spectro();

fprintf('Startup set 6 complete. \n')

%Initialize loop variables
resetBuffersFlag  = true;
framesReceived    = 0;
segmentsProcessed = 0;
suggestedMode     = 'S';
fLock             = false;
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
previousPulseTime = 0;
repeatedDetectionFlag = false;
missingSamples    = 0;
iqDataToWrite     = single(complex([]));
groupSeqCounter   = 0;

fprintf('Startup set 7 complete. Starting processing... \n')

expectedNextTimeStamp = 0;

while true 

            if resetBuffersFlag
                asyncDataBuff.reset();
                asyncTimeBuff.reset();
                asyncWriteBuff.reset();
                resetBuffersFlag = false;
                cleanBuffer = true;
            end

            %% Get data
            [dataReceived]  = udpReceiver.receive();

            %% Flush UDP buffer if data in the buffer is stale.
            if staleDataFlag
                fprintf('********STALE DATA FLAG: %u**************\n',uint32(staleDataFlag));
                fprintf('********CLEARING UDP DATA BUFFER*********\n');
                udpReceiver.clear();
                staleDataFlag = false;

                fprintf('********RESETTING TIMES******************\n');
                %startTime = round(posixtime(datetime('now'))*1000000)/1000000;
                framesReceived = 0;
                currSampleCount = uint64(0);
                nextSampleCount = uint64(0);
                
                startTime         = round(posixtime(datetime('now'))*1000000)/1000000;
                tic
            end

            %% Wait for new data if none ready, else put data in buffers
            if isempty(dataReceived)
                pauseTimeSec = 0.0001;
                if isdeployed
                    coder.ceval('usleep',uint32(pauseTimeSec * 1e6));
                else
                    pause(pauseTimeSec);  
                end
            else
                
                
                timeStampRaw     = dataReceived(1);
                timeStampReal    = real(timeStampRaw);
                timeStampImag    = imag(timeStampRaw);
                timeStampSec     = typecast(timeStampReal,'uint32');
                timeStampNanoSec = typecast(timeStampImag,'uint32');
                timeStamp        = double(timeStampSec) + 10^-9*double(timeStampNanoSec); 
                iqData           = dataReceived(2:end);
                
                
                if framesReceived == 0 
                    iqDataToWrite = iqData;
                    
                else
                    timeDiff = timeStamp - expectedNextTimeStamp;

                    if abs(timeDiff) < Config.tp / 2
                        
                        iqDataToWrite = iqData;
                    elseif timeDiff >= Config.tp / 2  && timeDiff < Config.tip %missed samples but not a whole lot
                        missingSamples = round(timeDiff * Config.Fs);
                        fprintf('Missing samples detected. Filling with zeros for %u samples.', uint64(missingSamples));
                        zerosFill = single(zeros(missingSamples, 1)) + ...
                                    1i*single(zeros(missingSamples, 1));
                        iqDataToWrite = [zerosFill(:); iqData];
                    elseif (timeDiff >= Config.tp / 2  && timeDiff >= Config.tip) ||... %missed a lot of samples. Reset buffers 
                           (timeDiff < -Config.tp / 2) %predictions is ahead of recently received packet. Shouldn't ever happen. If it is, reset the incoming data
                        staleDataFlag    = true;
                        resetBuffersFlag = true;
                        suggestedMode    = 'S';
                        iqDataToWrite = single(complex(zeros(0,1)));
                    end
                end
                
                timeVector     = timeStamp+1/Config.Fs*(0:(numel(iqDataToWrite)-1)).';
                
                frameNSamps          = numel(iqData);
                expectedNextTimeStamp = timeStamp + 1/Config.Fs * frameNSamps;
                framesReceived       = framesReceived + 1;

                %Write out data and time.
                asyncDataBuff.write(iqDataToWrite(:));
                asyncTimeBuff.write(timeVector(:));
                asyncWriteBuff.write(iqData);
                
                if asyncWriteBuff.NumUnreadSamples >= dataWriterSamples
                    dataWriterBuffData = asyncWriteBuff.read();
                    if dataWriterFileID ~= -1
                    [~] = fwrite(dataWriterFileID,interleaveComplexVector(dataWriterBuffData),'single');
                    end
                end

                

                %% Process data if there is enough in the buffers
                if asyncDataBuff.NumUnreadSamples >= sampsForKPulses + overlapSamples
fprintf('++++++++++BUFFER FULL, PROCESSING SEGMENT -- sampsForKPulses: %u, overlapSamples: %u,\n',uint32(sampsForKPulses),uint32(overlapSamples))
                    
previousToc = toc;
processingStartToc = previousToc;

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

fprintf('Sample elapsed seconds: %f \t Posix elapsed seconds: %f \n', timeVector(end) - startTime, round(posixtime(datetime('now'))*1000000)/1000000 - startTime)

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
                            fLock = false;
                            % switch Config.opMode
                            
                            prioriRelativeFreqHz = 10e-6 * abs(Config.tagFreqMHz - Config.channelCenterFreqMHz);
                            ps_pre = pulsestats(Config.tp, Config.tip, Config.tipu,...
                                                Config.tipj, prioriRelativeFreqHz ,...
                                                prioriRelativeFreqHz-(ceil(Config.Fs/2)),...
                                                prioriRelativeFreqHz+(ceil(Config.Fs/2)),...
                                                [1 1],'D' ,...
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
fprintf('ps_pre.fstart and ps.pre.fend before making waveform X: \t %f \t to \t %f. \n',...
            ps_pre.fstart, ps_pre.fend);%(1) is for coder so it knows it is a scalar
                       


                        %% PRIMARY PROCESSING BLOCK
                        %Prep waveform for processing/detection
                        X = waveform(x, Config.Fs, t0, ps_pre, stftOverlapFraction, threshold(Config.falseAlarmProb));
                        X.K = Config.K;
                        fprintf('Current interpulse params || N: %u, M: %u, J: %u,\n',uint32(X.N),uint32(X.M),uint32(X.J))
                        X.setprioridependentprops(X.ps_pre)
                        fprintf('Samples in waveform: %u \n',uint32(numel(X.x)))
previousToc = toc;
                        fprintf('Computing STFT...')
                        X.spectro();
                        fprintf('complete. Elapsed time: %f seconds \n', toc - previousToc)
                        fprintf('Building weighting matrix...')
previousToc = toc;
                        X.setweightingmatrix(zetas);
                        fprintf('complete. Elapsed time: %f seconds \n', toc - previousToc)

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

                        previousToc = toc;
                        
                        if segmentsProcessed==0
                            fprintf('Building thresholds...\n')
                            X.thresh = X.thresh.makenewthreshold(X);
                        else
                            fprintf('Setting thresholds from previous waveform...\n')
                            %Setting the threshold takes too long to run in
                            %real time if any of the dependent variables
                            %change so we can't use.
                            %X.thresh = X.thresh.setthreshold(X,Xhold);
                            %We also don't want to simply hold the same
                            %threshold from the last waveform:
                            %X.thresh = Xhold.thresh;
                            %We will hold the mu and sigma parameters
                            %contant (Xhold.thresh1W will be the same as 
                            %the last segment, but we  update the 
                            %thresholds as the noise values change.
                            X.thresh = Xhold.thresh.setthreshprops(Xhold.thresh.thresh1W, X);
                        end
                        fprintf(' \n \t Threshold setting complete. Elapsed time: %f seconds \n', toc - previousToc)
                        
                        fprintf('Time windows in S: %u \n',uint32(size(X.stft.S,2)))
previousToc = toc;

                        pulseInfoStruct.sendHeartbeatOverUDP(uint32(Config.ID));

fprintf('BEGINNING PROCESSING IN %s MODE \n', mode)
                        fprintf('====================================\n')
fprintf('First 5 entries of the real data block being processed are:\n')
for i = 1:5
fprintf('%.8f,',real(X.x(i)))
end
fprintf('\n')
fprintf('First 5 entries of the imaginary data block being processed are:\n')
for i = 1:5
fprintf('%.8f,',imag(X.x(i)))
end
fprintf('\n')

fprintf('Last 5 entries of the real data block being processed are:\n')
for i = numel(X.x)-5:numel(X.x)
fprintf('%.8f,',real(X.x(i)))
end
fprintf('\n')
fprintf('Last 5 entries of the imaginary data block being processed are:\n')
for i = numel(X.x)-5:numel(X.x)
fprintf('%.8f,',imag(X.x(i)))
end
fprintf('\n')

                        X.process(mode, 'most', Config.excldFreqs)
                        fprintf('complete. Elapsed time: %f seconds \n', toc - previousToc)

fprintf('ps_pre.fstart and ps_pre.fend after PROCESS step : \t %f \t to \t %f.\n',...
            X.ps_pre.fstart, X.ps_pre.fend);%(1) is for coder so it knows it is a scalar
fprintf('ps_pos.fstart and ps_pos.fend after PROCESS step : \t %f \t to \t %f.\n',...
            X.ps_pos.fstart, X.ps_pos.fend);%(1) is for coder so it knows it is a scalar

                        processingTime = toc - processingStartToc;
                        fprintf('TOTAL PULSE PROCESSING TIME: %f seconds \n', processingTime)

                        %% PREP FOR NEXT LOOP

                        %Latch/Release the frequency lock and setup the
                        %suggested mode
                        suggestedMode = X.ps_pos.mode;
                        pulsesConfirmed = all([X.ps_pos.pl.con_dec],2);
                        
                        if pulsesConfirmed%Check if all were confirmed
                            fLock = true;
                        else
                            fLock = false;
                        end

                        %Decide when/how the priori is updated for the next
                        %segment's processing.
                        if pulsesConfirmed %Now checking for confirmation during search mode as well& (strcmp(mode,'C') || strcmp(mode,'T'))
                            X.ps_pos.updateposteriori(X.ps_pre, X.ps_pos.pl, 'freq')
                            if trackedCount > 5
                                trackedCount = 0;
                                X.ps_pos.updateposteriori(X.ps_pre, X.ps_pos.pl, 'time')
                            end
                        end
fprintf('ps_pre.fstart and ps_pre.fend after PRIORI UPDATE step : \t %f \t to \t %f.\n',...
            X.ps_pre.fstart, X.ps_pre.fend);%(1) is for coder so it knows it is a scalar
fprintf('ps_pos.fstart and ps_pos.fend after PRIORI UPDATE step : \t %f \t to \t %f.\n',...
            X.ps_pos.fstart, X.ps_pos.fend);%(1) is for coder so it knows it is a scalar

                        %Check lagging processing
                        if segmentsProcessed ~= 0 && Config.K > 1 && processingTime > 0.9 * sampsForKPulses/Config.Fs
                            %Config.K = Config.K - 1;
                            fprintf('WARNING!!! PROCESSING TIME TOOK LONGER THAN WAVEFORM LENGTH. STREAMING NOT POSSIBLE. TRY REDUCING NUMBER OF PULSES CONSIDERED BY 1 TO K = %u \n',uint32(Config.K - 1));
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
                        
                        Xhold = waveformcopy(X);
                        
                        nPulseList           = numel(X.ps_pos.pl);
                        pulsesToSkip         = false(1, nPulseList);

                        %Report pulses and check for repeat detections
                        if ~isnan(X.ps_pos.cpki)
                            for j = 1 : nPulseList
                                currPulseTime = X.ps_pos.pl(j).t_0;
                                
                                fprintf(['Pulse at %f Hz detected. SNR: %f \n ' ...
                                         '\t Confirmation status: %u \n', ...
                                         '\t Interpulse time    : %f \n'], ...
                                Config.channelCenterFreqMHz + ps_pre_struc.pl(j).fp * 10^-6, ...
                                ps_pre_struc.pl(j).SNR, ...
                                uint32(ps_pre_struc.pl(j).con_dec),...
                                currPulseTime - previousPulseTime);
                                if currPulseTime - previousPulseTime < 1/10 * X.ps_pre.t_ip %Overlap occasionally will redetect the same pulse
                                    fprintf('(\t ^---This likely a repeat of a previously detected pulse. Will not be transmitted. \n');
                                    pulsesToSkip(j) = true;
                                else
                                    previousPulseTime = currPulseTime;
                                end
                                
                            end
                        else
                            fprintf('No pulses detected \n')
                        end
                        

                        pulseCount = 0;

                        if ~isnan(X.ps_pos.cpki)
                            fprintf("Transmitting pulse messages.  ");
                            for j = 1:nPulseList
                                
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
                                detectorPulse                               = X.ps_pos.pl(j);
                                pulseInfoStruct.tag_id                      = uint32(Config.ID);
                                pulseInfoStruct.frequency_hz                = uint32((Config.channelCenterFreqMHz * 1e6) + detectorPulse.fp);
                                pulseInfoStruct.start_time_seconds          = detectorPulse.t_0;
                                pulseInfoStruct.predict_next_start_seconds  = detectorPulse.t_next(1);
                                pulseInfoStruct.snr                         = detectorPulse.SNR;
                                pulseInfoStruct.stft_score                  = real(detectorPulse.yw);
                                pulseInfoStruct.group_seq_counter           = uint16(groupSeqCounter);
                                pulseInfoStruct.group_ind                   = uint16(j);
                                pulseInfoStruct.group_snr                   = groupSNR;
                                dt                                          = X.stft.dt;
                                T                                           = X.stft.T;
                                pulseInfoStruct.noise_psd                   = real(detectorPulse.yw ) * dt^2 / T * (1 + 10^(detectorPulse.SNR/10))^(-1); %See Notebook Entry 2023-07-07 for derivation
                                pulseInfoStruct.detection_status            = uint8(detectorPulse.det_dec);
                                pulseInfoStruct.confirmed_status            = uint8(detectorPulse.con_dec);
                                
                                if ~pulsesToSkip(j)
                                    % UDP Send
                                    pulseInfoStruct.sendOverUDP();

                                    % ROS send
                                    ros2PulseSend(pulsePub, pulseMsg, pulseInfoStruct, detectorPulse);

                                    pulseCount = pulseCount+1;
                                end
fprintf('EXPECTED GCS ENTRY:\n')
printpulseinfostruc(pulseInfoStruct);

                            end
                            groupSeqCounter = groupSeqCounter + 1;
                            fprintf("complete. Transmitted %u pulse(s).\n",uint32(pulseCount));
                        else
                            fprintf("\n");
                        end
                        
                        spectroFileName = sprintf('spectro_segment.%d.%d.csv',int32(Config.ID),int32(Config.startIndex));
                        %waveformRecordPath =fullfile(Config.logPath,spectroFileName);%Use this after upgrade to R2023b that supports full file
                        waveformRecordPath =[char(Config.logPath),'/',char(spectroFileName)];
                        fprintf("Writing waveform record csv file: %s\n",waveformRecordPath)
                        wfmcsvwrite(X,Config.channelCenterFreqMHz, waveformRecordPath);
                        fprintf("...complete.\n");
                     
                    end
                    
                    elapsedTimeClock = round(posixtime(datetime('now'))*1000000)/1000000 - startTime;
                    elapsedTimeToc   = toc;
                    fprintf('tocElapsed - clockElapsed = %0.6f  **************** \n', elapsedTimeToc - elapsedTimeClock)
                    totalLoopTime = toc - processingStartToc;                    
                    fprintf('TOTAL SEGMENT PROCESSING TIME: %f seconds \n', totalLoopTime)
                    
                end
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

        %Build an empty waveform just so that we can calculate number
        %of overlapSamples. This is needed for buffer operations
        X0 = waveform(single(complex([])), Config.Fs, 0, ps_input, stftOverlapFraction, threshold(0.01));
        X0.setprioridependentprops(ps_input)
        [~,~,n_ol,n_ws,~,~,N,M,J] = X0.getprioridependentprops(X0.ps_pre);
        
        overlapWindows  = 2*(Config.K*M+J);
        overlapSamples	= n_ws*overlapWindows;
        
        %See 2022-07-11 for updates to samples def
        sampsForKPulses = n_ws*(Config.K*(N+M)+J+1)+n_ol;

        fprintf('Updated buffer read vars -- N: %u, M: %u, J: %u,\n',uint32(N),uint32(M),uint32(J))
        fprintf('Updated buffer read vars -- sampForKPulses: %u,  overlapSamples: %u,\n',uint32(sampsForKPulses),uint32(overlapSamples))
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



    % function [mavlinkTunnelMsgUint8] = formatPulseForTunnel(target_system_in, target_component_in, payload_type_in, pulseStructIn)
    %      %% Build PulsePose Mavlink Tunnel Message Payload
    %      %Typecast maintains little-endian, in line
    %      %with the mavlink serialization standard: https://mavlink.io/en/guide/serialization.html
    %      target_system        = dec2hex(typecast(uint8(target_system_in),'uint8'), 2);                %uint8
    %      target_component     = dec2hex(typecast(uint8(target_component_in),'uint8'), 2);                  %uint8
    %      payload_type         = dec2hex(typecast(uint16(payload_type_in),'uint8'), 2);                 %uint16
    %      %payload_length      = dec2hex(typecast(uint8(0),'uint8'), 2);                  %uint8
    %      id                   = dec2hex(typecast(uint32(pulseStructIn.tag_id),'uint8'), 2);   %uint32
    %      freq                 = dec2hex(typecast(double(pulseStructIn.frequency),'uint8'), 2);                    %uint32
    %      start_time_sec       = dec2hex(typecast(int32(pulseStructIn.start_time.sec),'uint8'), 2);                %int32
    %      start_time_nanosec   = dec2hex(typecast(uint32(pulseStructIn.start_time.nanosec),'uint8'), 2);           %uint32
    %      predict_next_sec     = dec2hex(typecast(int32(pulseStructIn.predict_next_start.sec),'uint8'), 2);        %int32
    %      predict_next_nanosec = dec2hex(typecast(uint32(pulseStructIn.predict_next_start.nanosec),'uint8'), 2);   %uint32
    %      snr                  = dec2hex(typecast(double(pulseStructIn.snr),'uint8'), 2);          %double
    %      stft_score           = dec2hex(typecast(double(pulseStructIn.stft_score),'uint8'), 2);   %double
    %      group_ind            = dec2hex(typecast(uint16(pulseStructIn.group_ind),'uint8'), 2);    %uint16
    %      detection_status     = dec2hex(typecast(uint8(pulseStructIn.detection_status),'uint8'), 2);    %uint8
    %      confirmed_status     = dec2hex(typecast(uint8(pulseStructIn.confirmed_status),'uint8'), 2);    %uint8
    %      noise_psd            = dec2hex(typecast(double(pulseStructIn.noise_psd),'uint8'), 2);          %double
    % 
    %      payload_hex = [id; freq; start_time_sec; start_time_nanosec; ...
    %                 predict_next_sec; predict_next_nanosec; snr; ...
    %                 stft_score; group_ind; detection_status; ...
    %                 confirmed_status; noise_psd];
    %      payload_length = dec2hex(typecast(uint8(size(payload_hex,1)),'uint8'),2);
    %      mavlinkTunnelMsgHex = [target_system; target_component; ...
    %                             payload_type; payload_length;...
    %                             payload_hex];
    %      mavlinkTunnelMsgUint8 = uint8( hex2dec( mavlinkTunnelMsgHex ) );
    % end


