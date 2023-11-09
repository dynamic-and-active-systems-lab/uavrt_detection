function [X] = uavrt_detection_post_flight_analysis() %configPath, thresholdCachePath)

% filePath =           '/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/FLIGHT_TESTING_DATA/Flight Logs/2023-05-22-Flight_archive/data_record.2.bin';
%configPath =         '/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/FLIGHT_TESTING_DATA/Flight Logs/2023-05-22-Flight_archive/detector.2.config';
%thresholdCachePath = '/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/FLIGHT_TESTING_DATA/Flight Logs/2023-05-22-Flight_archive';

% filePath =           '/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/FLIGHT_TESTING_DATA/2023-08-16-Egr Quad Testing/2023-08-16-LOGS/data_record.2.bin';
% filePath =           '/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/FLIGHT_TESTING_DATA/2023-08-16-Egr Quad Testing/2023-08-16-LOGS/data_record.3.bin';
% filePath =           '/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/FLIGHT_TESTING_DATA/2023-08-16-Egr Quad Testing/2023-08-16-LOGS/data_record.4.bin';
% filePath =           '/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/FLIGHT_TESTING_DATA/2023-08-18-NAVHDA Site/data_record.2.bin';
% 
% filePath =           '/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/FLIGHT_TESTING_DATA/2023-08-17-Kachina Park/2023-08-17-LOGS/data_record.2.bin';

% filePath =           '/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/FLIGHT_TESTING_DATA/2023-09-06-NAVHDA Site and Lab Noise/LOGS-2023-09-05/data_record.2.bin';
% configPath =         '/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/FLIGHT_TESTING_DATA/2023-09-06-NAVHDA Site and Lab Noise/LOGS-2023-09-05/detector.2.config';
% thresholdCachePath = '/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/FLIGHT_TESTING_DATA/2023-09-06-NAVHDA Site and Lab Noise/LOGS-2023-09-05/';

% filePath =           '/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/FLIGHT_TESTING_DATA/LOGS-2023-09-14-NAVHDA_site_flight/data_record.2.bin';
% configPath =         '/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/FLIGHT_TESTING_DATA/LOGS-2023-09-14-NAVHDA_site_flight/detector.2.config';
% thresholdCachePath = '/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/FLIGHT_TESTING_DATA/LOGS-2023-09-14-NAVHDA_site_flight';

% filePath =           '/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/FLIGHT_TESTING_DATA/2023-09-14-Office Testing/LOGS-2023-09-15-Ft Valley Flight/data_record.2.bin';
% configPath =         '/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/FLIGHT_TESTING_DATA/2023-09-14-Office Testing/LOGS-2023-09-15-Ft Valley Flight/detector.2.config';
% thresholdCachePath = '/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/FLIGHT_TESTING_DATA/2023-09-14-Office Testing/LOGS-2023-09-15-Ft Valley Flight';

filePath =           '/Users/michael/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/data_for_testing_detection_code/data_record.2.5.bin';
configPath =         '/Users/michael/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/data_for_testing_detection_code/detector.2.config';
thresholdCachePath = '/Users/michael/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/uavrt_detection/data_for_testing_detection_code';


global globalThresholdCachePath;
globalThresholdCachePath = thresholdCachePath;

Config =  DetectorConfig(); %Build empty config object
updateconfig()              %Update (fill) the configuration
configUpdatedFlag = true;



fprintf('Loading data...\n')
fid = fopen(filePath);
if fid ~= -1
    dataRaw = fread(fid,'single');
    fclose(fid);
    fprintf('Done.\n')
else
    fprintf('UAV-RT: Error opening file at path provided.\n')
    return
end
if mod(dataRaw,2)~=0
    dataRaw(end) = [];
end

n_samps = numel(dataRaw)/2;

x = dataRaw(1:2:end-1)+1i*dataRaw(2:2:end);

%indMax = 2304000;
indMax = numel(x);

dt = 1/Config.Fs;
x = x(1:indMax);

nSamps = numel(x);
t = dt*(0:1:nSamps-1);

asyncDataBuff = dsp.AsyncBuffer(nSamps);
asyncTimeBuff = dsp.AsyncBuffer(nSamps);
asyncDataBuff.write(x(:));
asyncTimeBuff.write(t(:));



blankThresh = threshold(Config.falseAlarmProb);

prioriRelativeFreqHz = 10e-6 * abs(Config.tagFreqMHz - Config.channelCenterFreqMHz);
ps_pre = pulsestats(Config.tp, Config.tip, Config.tipu,...
                    Config.tipj, prioriRelativeFreqHz ,0     ,0   ,[1 1],'D' ,...
                    makepulsestruc(),makepulsestruc(),false , NaN);


stftOverlapFraction = 0.5;
zetas               = [0 0.5];

overlapSamples	= 0;
sampsForKPulses = 0;
updatebufferreadvariables(ps_pre);

fLock = false;
% switch Config.opMode
%     case 'freqSearchHardLock'
%         fLock = false;
%     case 'freqKnownHardLock'
%         fLock = true;
%     case 'freqSearchSoftLock'
%         fLock = false;
%     case 'freqAllNoLock'
%         fLock = false;
%     otherwise
%         fLock = false;
% end


segmentsProcessed = 0;

suggestedMode    = 'S';

previousPulseTime = 0;

trackedCount      = 0;

i = 1;

while asyncDataBuff.NumUnreadSamples > sampsForKPulses + overlapSamples

    if asyncDataBuff.NumUnreadSamples >= sampsForKPulses + overlapSamples

        if segmentsProcessed == 0
            x = asyncDataBuff.read(sampsForKPulses);
            t = asyncTimeBuff.read(sampsForKPulses);
        else
            x = asyncDataBuff.read(sampsForKPulses, overlapSamples);
            t = asyncTimeBuff.read(sampsForKPulses, overlapSamples);
        end

        if segmentsProcessed == 0
            X(i) = waveform(x, Config.Fs, t(1), ps_pre, stftOverlapFraction,  threshold(Config.falseAlarmProb));
        else
            X(i) = waveform(x, Config.Fs, t(1), X(i-1).ps_pos, stftOverlapFraction,  threshold(Config.falseAlarmProb));
        end
        X(i).K = Config.K;
        X(i).setprioridependentprops(X(i).ps_pre)
        X(i).spectro();
        X(i).setweightingmatrix(zetas);



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


        if segmentsProcessed==0
            fprintf('Building thresholds  ...')
            X(i).thresh = X(i).thresh.makenewthreshold(X);
        else
            fprintf('Setting thresholds from previous waveform  ...')
            %OLD METHOD HOLDING CONSTANT
            %X(i).thresh = X(i-1).thresh;

            % fprintf('Setting thresholds from previous waveform...\n')
            % %Setting the threshold takes too long to run in
            % %real time if any of the dependent variables
            % %change so we can't use.
            % %X.thresh = X.thresh.setthreshold(X,Xhold);
            % %We also don't want to simply hold the same
            % %threshold from the last waveform:
            % %X.thresh = Xhold.thresh;
            % %We will hold the mu and sigma parameters
            % %contant (Xhold.thresh1W will be the same as
            % %the last segment, but we  update the
            % %thresholds as the noise values change.
             X(i).thresh = X(i-1).thresh.setthreshprops(X(i-1).thresh.thresh1W, X(i));



        end

% if i==4
%     pause(1)
% end
% if i>96
%     pause(1);
% end
        X(i).process(mode, 'most', Config.excldFreqs)
%if i == 1
    figure;
%end
plot([X(i).ps_pos.clst(:,1).yw]);hold on
plot([X(i).ps_pos.clst(:,2).yw]);
plot([X(i).ps_pos.clst(:,3).yw]);

% plot([X(i).ps_pos.clst(:,1).yw]+[X(i).ps_pos.clst(:,2).yw]+[X(i).ps_pos.clst(:,3).yw])        
% hold on;
% plot(X(i).thresh.threshVecFine)
drawnow
pause(0.5)
hold off


        %% PREP FOR NEXT LOOP

        %Latch/Release the frequency lock and setup the
        %suggested mode
        suggestedMode = X(i).ps_pos.mode;
        pulsesConfirmed = all([X(i).ps_pos.pl.con_dec],2);
        % if pulsesConfirmed%Check if all were confirmed
        %     fLock = true;
        % end
        % %We only ever release if we are in softlock mode and
        % %only do so in that case if we are no longer confirming
        % %pulses.
        % if strcmp(Config.opMode, 'freqSearchSoftLock') & ~pulsesConfirmed
        %     fLock = false;
        % end
        if pulsesConfirmed%Check if all were confirmed
            fLock = true;
        else
            fLock = false;
        end

        %Decide when/how the priori is updated for the next
        %segment's processing.
        if pulsesConfirmed & (strcmp(mode,'C') || strcmp(mode,'T'))
            X(i).ps_pos.updateposteriori(X(i).ps_pre, X(i).ps_pos.pl, 'freq')
            if trackedCount > 5
                trackedCount = 0;
                X(i).ps_pos.updateposteriori(X(i).ps_pre, X(i).ps_pos.pl, 'time')
            end
        end

        segmentsProcessed = segmentsProcessed+1;

        updatebufferreadvariables(X(i).ps_pos);
        
        nPulseList   = numel(X(i).ps_pos.pl);
        pulsesToSkip = false(1, nPulseList);
        %Report pulses and check for repeat detections
        if ~isnan(X(i).ps_pos.cpki)
            for j = 1 : nPulseList
                currPulseTime = X(i).ps_pos.pl(j).t_0;

                fprintf(['Pulse at %f Hz detected. SNR: %f \n ' ...
                    '\t Confirmation status: %u \n', ...
                    '\t Interpulse time    : %f \n'], ...
                    Config.channelCenterFreqMHz + X(i).ps_pos.pl(j).fp * 10^-6, ...
                    X(i).ps_pos.pl(j).SNR, ...
                    uint32(X(i).ps_pos.pl(j).con_dec),...
                    currPulseTime - previousPulseTime);
                if currPulseTime - previousPulseTime < 1/10 * X(i).ps_pre.t_ip %Overlap occasionally will redetect the same pulse
                    fprintf('(\t ^---This likely a repeat of a previously detected pulse. Will not be transmitted. \n');
                    pulsesToSkip(j) = true;
                else
                    previousPulseTime = currPulseTime;
                end

            end
        else
            fprintf('No pulses detected \n')
        end

        i = i + 1

    end

end
iMax = i-1; 
figure;
for i = 1:iMax
    for j = 1:numel(X(i).ps_pos.pl(:))
         color = 'r';
        if X(i).ps_pos.pl(j).con_dec
            color = 'g';
        end
         if X(i).ps_pos.pl(j).SNR == -inf
             plot(X(i).ps_pos.pl(j).t_0, -20,'.','Color',color);
         else
        plot(X(i).ps_pos.pl(j).t_0, X(i).ps_pos.pl(j).SNR,'o','Color',color);
         end
    end
    hold on;
end


% tVerify = 93;
% indVerify = find([X(:).t_0] >= tVerify,1,'first');
% for indVerify = 1:numel(X)
% figHand = X(indVerify).stft.displaystft;
% hold on
% for i = 1:numel(X(indVerify).ps_pos.pl)
%     plot(X(indVerify).ps_pos.pl(i).t_0,X(indVerify).ps_pos.pl(i).fp,'ro','MarkerSize',10);
% end
% title(num2str(indVerify));
% drawnow;
% pause(1);
% close(figHand)
% end



% 
%         ind = 32
%         [Sfft] = stftFFT(abs(X(ind).stft.S).^2);
%         dt_STFT = X(ind).stft.t(2) - X(ind).stft.t(1);
%         nSTFT = size(X(ind).stft.S, 2);
%         Fs_STFT = 1/dt_STFT;
%         if mod(nSTFT,2)==0
%             freqsHz_STFT  = Fs_STFT/nSTFT * (-nSTFT/2:nSTFT/2-1);
%         else
%             freqsHz_STFT = Fs_STFT/nSTFT * (-(nSTFT-1)/2:(nSTFT-1)/2);
%         end
%         Sfft(:,freqsHz_STFT == 0) = NaN;
%         freqsHz_STFT_geq0_mask = freqsHz_STFT<=0;
%         Sfft(:,freqsHz_STFT_geq0_mask) = [];
%         freqsHz_STFT_geq0 = freqsHz_STFT(~freqsHz_STFT_geq0_mask);
% 
%         blah = figure;
%         %surf(freqsHz_STFT,f_stft_stitch,10*log10(abs(Sfft).^2),'EdgeColor','none')
%         surf(freqsHz_STFT_geq0,X(ind).stft.f,10*log10(abs(Sfft).^2),'EdgeColor','none')
%         xlabel('STFT Freq (Hz)');ylabel('Freq (MHz)');zlabel('S-fft magnitudes')
%         view([-28 84])
% 
 pause(1);

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