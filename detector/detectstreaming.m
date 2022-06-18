function [] = detectstreaming()
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

configPath = 'config/detectorConfig.txt'; %Must exist in the same directory as the execution of this executable

Config =  DetectorConfig(); %Build empty config object
updateconfig()              %Update (fill) the configuration
configUpdatedFlag = true;

% if coder.target('MATLAB')
%     clear channelreceiver %Clear out persistent variables in channelreceiver
%     clear controlreceiver %Clear out persistent variables in controlreceiver
% end


%% ROS2 Setup
%node = ros2node("detector");



pulseStatsPriori = pulsestats(Config.tp,Config.tip,Config.tipu,Config.tipj,0 ,0     ,0   ,[1 1],'D' ,makepulsestruc(),makepulsestruc(),[]        ,[]        ,[]);
%                                    tp,       tip,       tipu,       tipj,fp,fstart,fend,tmplt,mode,pl              ,clst            ,cmsk      ,cpki      ,thresh)
stftOverlapFraction = 0.5;
zetas = [0 0.5];



pauseWhenIdleTime   = 0.25;

%Initialize and then set these variable needed for buffer reads
overlapSamples	= 0;
sampsForKPulses = 0;
updatebufferreadvariables(pulseStatsPriori);

coder.varsize('dataReceived',[1025 1]);
coder.varsize('state',[1 64]);
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

dataWriterTimeIntervalNominal = 150; %Write interval in seconds. 2.5*60*4000*32/8 should work out the 2.4Mb of data at 4ksps. 
dataWriterPacketsPerInterval  = ceil(dataWriterTimeIntervalNominal/((packetLength-1)/Config.Fs));
dataWriterTimeIntervalActual  = dataWriterPacketsPerInterval*packetLength/Config.Fs;
dataWriterSamples             = dataWriterPacketsPerInterval*packetLength;
%dataWriterBuffer             = zeros(packetLength,dataWriterPacketsPerInterval);
asyncWriteBuff                = dsp.AsyncBuffer(600650); %600650 is the result of the nominal settings of ceil(150/(1024/4000)*1025.
asyncWriteBuff.write(single(1+1i));
dataWriterFileID              = fopen(Config.dataRecordPath,'w');
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
localThresh = NaN;
coder.varsize('localThresh',[inf 1],[1 1]);

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
ps_pre_struc.thresh = localThresh;

maxInd = 4000;
maxSegments = 100;
%figure;
i = 1;
framesReceived = 0;
segmentsProcessed = 0;
%tLast = posixtime(datetime('now'));
state = 'idle';
resetUdp = true;
%Preallocate Xhold for Coder
Xhold = cell(maxSegments,1);
for i = 1:maxSegments
    Xhold{i} = waveform();
end

staleDataFlag = true;

idleTic = 1;
while i <= maxInd
    
    switch state
        case 'run'

            [dataReceived]  = channelreceiver('0.0.0.0', Config.portData,resetUdp,false);
            resetUdp = false;
            
            if staleDataFlag
                fprintf('********STALE DATA FLAG: %u *********\n',uint32(staleDataFlag));
                while ~isempty(dataReceived)
                    fprintf('********CLEARING UDP DATA BUFFER*********\n');
                    [dataReceived]  = channelreceiver('0.0.0.0', Config.portData,resetUdp,false);
                end
                staleDataFlag = false;
            end

            %Wait for new data if none ready. 
            if isempty(dataReceived)
                %fprintf('Running...no data received. \n')
                pause(packetLength/2*1/Config.Fs);%Pause for 1/2th of a packet time
            else
                framesReceived = framesReceived + 1;
                timeStamp   = singlecomplex2double(dataReceived(1));
                iqData      = dataReceived(2:end);
                timeVector  = timeStamp+1/Config.Fs*(0:(numel(iqData)-1)).';
                asyncDataBuff.write(iqData);
                asyncTimeBuff.write(timeVector);
                asyncWriteBuff.write(dataReceived);
                if asyncWriteBuff.NumUnreadSamples ==dataWriterSamples
                    dataWriterBuffData = asyncWriteBuff.read();
                    count = fwrite(dataWriterFileID,dataWriterBuffData);
                    %disp(['Wrote ',num2str(count),' samples to file.'])
                end
                if asyncDataBuff.NumUnreadSamples >= sampsForKPulses + overlapSamples
                    fprintf('Buffer Full|| sampsForKPulses: %u, overlapSamples: %u,\n',uint32(sampsForKPulses),uint32(overlapSamples))
                    fprintf('Running...Buffer full with %d samples. Processing. \n', asyncDataBuff.NumUnreadSamples)
                    %i
                    tic
                    if segmentsProcessed == 0
                        x = asyncDataBuff.read(sampsForKPulses);%Overlap reads back into the buffer, but there isn't anything back there on the first segment. Will fill with overlapSamples zeros at beginning of x if you specify overlap here.
                        t = asyncTimeBuff.read(sampsForKPulses);
                        %fprintf('Read %d samples \n', sampsForKPulses)
                    else
                        x = asyncDataBuff.read(sampsForKPulses, overlapSamples);
                        t = asyncTimeBuff.read(sampsForKPulses, overlapSamples);
                        %fprintf('Read %d samples \n', sampsForKPulses+overlapSamples)
                    end
                        %fprintf('Now there are %d samples in the buffer \n', asyncDataBuff.NumUnreadSamples)
                    %plot(x(:,2),real(x(:,1)))
                    t0 = t(1);
                    fprintf('Running...Building priori and waveform. \n')
                    %Set the priori info
                    if configUpdatedFlag
                        ps_pre = initializeps(Config);
                        configUpdatedFlag = false;
                    else
                        ps_pre = pulsestats(ps_pre_struc.t_p, ps_pre_struc.t_ip, ps_pre_struc.t_ipu, ps_pre_struc.t_ipj ,ps_pre_struc.fp ,ps_pre_struc.fstart     ,ps_pre_struc.fend   ,ps_pre_struc.tmplt, ps_pre_struc.mode, ps_pre_struc.pl, ps_pre_struc.clst, ps_pre_struc.cmsk, ps_pre_struc.cpki, ps_pre_struc.thresh);
                        configUpdatedFlag = false;
                    end
                    %fprintf('x: %e \n',x(1));

                    X = waveform(x, Config.Fs, t0, ps_pre, stftOverlapFraction);
                    %fprintf('X.x: %e \n',X.x(1));
                    X.K = Config.K;
                    fprintf('Current ip vars|| N: %u, M: %u, J: %u,\n',uint32(X.N),uint32(X.M),uint32(X.J))
                    X.setprioridependentprops(X.ps_pre)
                    fprintf('Samples in waveform: %u \n',uint32(numel(X.x)))
                    fprintf('Current ip vars|| N: %u, M: %u, J: %u,\n',uint32(X.N),uint32(X.M),uint32(X.J))

                    fprintf('Running...STFT...')
                    X.spectro
                    fprintf('Time windows in S: %u \n',uint32(size(X.stft.S,2)))
                    fprintf('Current ip vars|| N: %u, M: %u, J: %u,\n',uint32(X.N),uint32(X.M),uint32(X.J))
                    fprintf('complete.\n')

                    fprintf('Running...Setting mode...')
                    if strcmp(Config.focusMode,'open')
                        mode = 'D';             %Force discovery mode if in 'open' focus mode
                    else                        %Last processing decision mode selection is used in 'focus' focus mode
                        mode = X.ps_pre.mode;
                    end
                    fprintf('complete.\n')
                    
                    fprintf('Running...Checking packet loss...')
                    %Here we check to see if the next segment started where
                    %we expected base on the last segment. If packets were
                    %dropped, the prediction will be less than the current
                    %t0. Default to discovery mode in this case.
                    packetLostFlag = (t0-X.t_nextsegstart)>=packetLength/Config.Fs;
                    if packetLostFlag
                        disp('Difference between current segment start time and that predicted by the last segment is larger than expected and may indicate packet loss. Defaulting to Discovery mode.')
                        mode = 'D';
                    end
                    fprintf('complete.\n')
                    
                    fprintf('Running...Processing...')

                    %xline(posixtime(datetime('now')),'--');hold on;
                    %plot(X.t,X.x); hold on
                    %figure;plot(sum(reshape([X.ps_pos.clst.yw],240,3),2));hold on;plot(X.ps_pos.thresh)
                    
                    %X.process(mode,Config.focusMode,'most',zetas,Config.falseAlarmProb,Config.decisionEntry,Config.excldFreqs)
                    X.process(mode,Config.focusMode,'most',zetas,Config.falseAlarmProb,Config.excldFreqs)
                    segmentsProcessed = segmentsProcessed+1;
                    %pulseStatsPriori = X.ps_pos;      %Priori of next is posterior of current
                    %ps_pre = pulsestats(X.ps_pos.t_p,X.ps_pos.t_ip,X.ps_pos.t_ipu,X.ps_pos.t_ipj,X.ps_pos.fp ,X.ps_pos.fstart ,X.ps_pos.fend ,X.ps_pos.tmplt,X.ps_pos.mode,X.ps_pos.pl,pulse,[],[],[]);
                    fprintf('complete. \n')
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
                    ps_pre_struc.thresh= X.ps_pos.thresh;
                    
                    fprintf('Updating priori. \n')
                    
                    %updatebufferreadvariables(ps_pre);
                    updatebufferreadvariables(X.ps_pos);
                    %[X.ps_pos.pl(:).SNR]
                    toc
                    
                    Xhold{segmentsProcessed} = X;
                    for j = 1:numel(ps_pre_struc.pl)
                        fprintf('Pulse at %e Hz detected. Confirmation status: %u \n', ps_pre_struc.pl(j).fp,uint32(ps_pre_struc.pl(j).con_dec))
                    end
                    fprintf('Mode: %s', ps_pre_struc.mode)
                    %sound(real(X.x)/max(real(X.x)),Config.Fs)
                end
                i = i+1;
            end

            staleDataFlag = false;
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
            count = fwrite(dataWriterFileID,dataWriterBuffData);
            
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
            count = fwrite(dataWriterFileID,dataWriterBuffData);
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

            
        case 'kill'
            %Send command to release the udp system objects
            controlreceiver('0.0.0.0', Config.portCntrl,true);
            channelreceiver('0.0.0.0', Config.portData,true,true);
            dataWriterBuffData = asyncWriteBuff.read();
            count = fwrite(dataWriterFileID,dataWriterBuffData);
            
            asyncDataBuff.reset();
            asyncTimeBuff.reset();
            asyncWriteBuff.reset();
            asyncDataBuff.release();
            asyncTimeBuff.release();
            asyncWriteBuff.release();
            
            
            fclose(dataWriterFileID);
            %release(writer);
            break
            
        otherwise
            %Should never get to this case, but jump to idle if we get
            %here.
            state = 'idle';
    end
    
    
    
end
    function [ps] = initializeps(theConfig)
        %This sets up a standarized pulsestats object based on the config
        %passed to it. 
         ps = pulsestats(theConfig.tp, theConfig.tip, theConfig.tipu,...
                             theConfig.tipj,0 ,0     ,0   ,[1 1],'D' ,...
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
        X0 = waveform([], Config.Fs, 0, ps_pre, stftOverlapFraction);
        %end
        
        %X0.ps_pre = ps_pre;
        X0.setprioridependentprops(ps_pre)
        [~,~,n_ol,n_ws,~,~,N,M,J] = X0.getprioridependentprops(X0.ps_pre);
        %         overlapWindows  = 2*Config.K*M+1;
        %         overlapSamples	= n_ws*overlapWindows;
        %         %sampsForKPulses = Config.K*n_ws*(N+M+1+1);
        %         sampsForKPulses = n_ws*(Config.K*(N+M)+1+1);
        
        overlapWindows  = 2*Config.K*(M+J);
        overlapSamples	= n_ws*overlapWindows;
        if Config.K~=1
            sampsForKPulses = n_ws*(Config.K*(N+M)-2*M)+n_ol;
        else
            sampsForKPulses = n_ws*(N+M+J)+n_ol;
        end
        fprintf('Updating buffer read vars|| N: %u, M: %u, J: %u,\n',uint32(N),uint32(M),uint32(J))
        fprintf('Updating buffer read vars|| sampForKPulses: %u,  overlapSamples: %u,\n',uint32(sampsForKPulses),uint32(overlapSamples))
    end

%[~] = receiver(udpReceivePort,true);
% if coder.target('MATLAB')
%     clear channelreceiver; %Has persistant variables. Clears them from memory.
%     clear controlreceiver; %Has persistant variables. Clears them from memory.
% end



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

