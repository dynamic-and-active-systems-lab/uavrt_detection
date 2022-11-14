function [] = uavrt_detection()
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

 %#codegen
configPath = "detector/config/detectorConfig.txt"; %Must exist in the same directory as the execution of this executable

Config =  DetectorConfig(); %Build empty config object
updateconfig()              %Update (fill) the configuration
configUpdatedFlag = true;


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

coder.varsize("dataReceived", [10251]);
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
sampsForMaxPulses = 24810 * 2;
asyncDataBuff = dsp.AsyncBuffer(sampsForMaxPulses);
asyncTimeBuff = dsp.AsyncBuffer(sampsForMaxPulses);
fprintf('Startup set 2 complete. \n')
dataWriterTimeIntervalNominal = 10; %Write interval in seconds. 2.5*60*4000*32/8 should work out the 2.4Mb of data at 4ksps.
dataWriterPacketsPerInterval  = ceil(dataWriterTimeIntervalNominal/((packetLength-1)/Config.Fs));
dataWriterTimeIntervalActual  = dataWriterPacketsPerInterval*packetLength/Config.Fs;
dataWriterSamples             = dataWriterPacketsPerInterval*packetLength;
%asyncWriteBuff                = dsp.AsyncBuffer(600650); %600650 is the result of the nominal settings of ceil(150/(1024/4000)*1025.
%asyncWriteBuff.write(single(1+1i));%Write to give Code the type. Read to remove data.
%asyncWriteBuff.read();
dataWriterFileID    = fopen(Config.dataRecordPath,'w');
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

fprintf('Startup set 5 complete. \n')

%% Preallocate X and Xhold so that coder knows the data types.
coder.varsize("emptyData",[1, inf]);
exampleData = single(complex(wgn(1000,1,1,'linear','complex'))).';
Xhold = waveform(exampleData, Config.Fs, 0, pulseStatsPriori, stftOverlapFraction, threshold(Config.falseAlarmProb));
X     = waveform(exampleData, Config.Fs, 0, pulseStatsPriori, stftOverlapFraction, threshold(Config.falseAlarmProb));
Xhold.spectro();
X.spectro();

fprintf('Startup set 6 complete. \n')

samplesPerFrame = 2048;
udpReceiveBufferSize = samplesPerFrame * 2;
%udpReceiver = udpReceiverSetup('127.0.0.1', Config.portData, udpReceiveBufferSize, udpReceiveBufferSize);
udpReceiver = udpReceiverSetup('127.0.0.1', 20000, udpReceiveBufferSize, samplesPerFrame);

udpSender = udpSenderSetup('127.0.0.1', 30000, 4);

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

fprintf('Startup set 7 complete. Starting processing... \n')

while true %i <= maxInd

            if resetBuffersFlag
                asyncDataBuff.reset();
                asyncTimeBuff.reset();
                resetBuffersFlag =false;
                cleanBuffer = true;
            end

            %% Flush UDP buffer if data in the buffer is stale.
            if staleDataFlag
                fprintf('********STALE DATA FLAG: %u *********\n',uint32(staleDataFlag));
                udpReceiverClear(udpReceiver);
                staleDataFlag = false;
            end

            %% Get data
            [iqData]  = udpReceiverRead(udpReceiver, udpReceiveBufferSize);

            %% Wait for new data if none ready, else put data in buffers
            if isempty(iqData)
                pause((packetLength-1)/2*1/Config.Fs);
            else
                framesReceived = framesReceived + 1;
                timeStamp      = posixtime(datetime('now'));
                timeVector     = timeStamp+1/Config.Fs*(0:(numel(iqData)-1)).';
                %Write out data and time.
                asyncDataBuff.write(iqData);
                asyncTimeBuff.write(timeVector);
                %asyncWriteBuff.write(dataReceived);
                %if asyncWriteBuff.NumUnreadSamples == dataWriterSamples
                %    dataWriterBuffData = asyncWriteBuff.read();
                %    %dataWriterBuffDataComplexInterleave = [real(dataWriterBuffData), imag(dataWriterBuffData)].';
                %    [~] = fwrite(dataWriterFileID,interleaveComplexVector(dataWriterBuffData),'single');
                %end

                %end

                %% Process data if there is enough in the buffers
                if asyncDataBuff.NumUnreadSamples >= sampsForKPulses + overlapSamples
                    fprintf('Buffer Full|| sampsForKPulses: %u, overlapSamples: %u,\n',uint32(sampsForKPulses),uint32(overlapSamples))
                    fprintf('Running...Buffer full with %d samples. Processing. \n', asyncDataBuff.NumUnreadSamples)
                    
                    tic
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

                        fprintf('complete. Elapsed time: %f seconds \n', toc)
                        fprintf('Time windows in S: %u \n',uint32(size(X.stft.S,2)))
                        fprintf('Finding pulses...')
                        X.process(mode, 'most', Config.excldFreqs)
                        processingTime = toc;
                        fprintf('complete. Elapsed time: %f seconds \n', toc)

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
                        %Xhold{mod(segmentsProcessed,maxSegments)} = X;%Keep a maxSegments running record of waveforms for debugging in Matlab
                        %Xstruct = obj2structrecursive(X);
                        %Xhold = X;
                        Xhold = waveformcopy(X);

                        for j = 1:numel(ps_pre_struc.pl)
                            pulse = ps_pre_struc.pl(j);
                            fprintf('Pulse at %e Hz detected. SNR: %e Confirmation status: %u \n', pulse.fp, pulse.SNR, uint32(pulse.con_dec));
                            udpSenderSend(udpSender, [ single(pulse.SNR) single(pulse.con_dec) single(pulse.t_0)]);
                        end

                        if false %Config.ros2enable
                            pulseCount = 0;
                            if ~isnan(X.ps_pos.cpki)
                                fprintf("Transmitting ROS2 pulse messages");
                                for j = 1:numel(X.ps_pos.cpki)
                                    for k = 1:size(X.ps_pos.clst,2)
                                        %Set pulseMsg parameters for sending
                                        pulseMsg.tag_id             = char(Config.ID);
                                        pulseMsg.frequency          = Config.channelCenterFreqMHz + (X.ps_pos.clst(X.ps_pos.cpki(j),k).fp)*1e-6;
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
                                        pulseMsg.group_SNR          = 10*log10(mean(10.^([X.ps_pos.clst(X.ps_pos.cpki(j),:).SNR]/10)));%Average SNR in dB
                                        pulseMsg.detection_status   = boolean(X.ps_pos.clst(X.ps_pos.cpki(j),k).det_dec);
                                        pulseMsg.confirmed_status   = boolean(X.ps_pos.clst(X.ps_pos.cpki(j),k).con_dec);
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
end

