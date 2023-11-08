function [] = wfmcsvplot(filePath)
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here
lineLocs = gettextfilelinelocs(filePath);
fid = fopen(filePath,'r');
nLines = numel(lineLocs);
for i = 1:nLines
    lineStr = fgetl(fid);
    if strcmp(lineStr,'Record Start Time (s):')
        t0_string = fgetl(fid);
        t0 = textscan(t0_string,'%f');
    elseif strcmp(lineStr,'Pulse Listing:')
        pl_t0_string = fgetl(fid);
        pl_t0_cell = textscan(pl_t0_string,'%f,');
        pl_fp_string = fgetl(fid);
        pl_fp_cell = textscan(pl_fp_string,'%f,');
        pl_SNR_string = fgetl(fid);
        pl_SNR_cell = textscan(pl_SNR_string,'%f,');
        pl_conf_string = fgetl(fid);
        pl_conf_cell = textscan(pl_conf_string,'%u,');
        pl.t0 = pl_t0_cell{1};
        pl.fp = pl_fp_cell{1};
        pl.SNR = pl_SNR_cell{1};
        pl.conf = pl_conf_cell{1};
    elseif strcmp(lineStr,'Spectrogram Frequencies (MHz):')
        f_string = fgetl(fid);
        fcell = textscan(f_string,'%f,');
        f = fcell{1};
        numFreqs = numel(fcell{1});
    elseif strcmp(lineStr,'Spectrogram Times (s):')
        t_string = fgetl(fid);
        tcell = textscan(t_string,'%f,');
        t = tcell{1};
        numTimes = numel(tcell{1});
    elseif strcmp(lineStr,'Spectrogram Values (|STFT|):')
        Spec_string = fgetl(fid);
        SpecVec = textscan(Spec_string,'%f,');
        numSpecVec = numel(SpecVec{1});
    end
end
if numFreqs * numTimes ~= numSpecVec
    error('UAV-RT: Numer of frequency times number of time elements does not equal number of spectrogram elements')
end
Spec = reshape(SpecVec{1},numFreqs,numTimes);
figure;surf(t ,f ,Spec,'Edgecolor','none')
view([0 90])

hold on
if ~isnan(pl.t0(1))
    for i = 1:numel(pl.t0)
        [~, SpecInd_time] = min(abs(t - pl.t0(i)));%find(t == pl.t0(i),1,'first');
        [~, SpecInd_freq] = min(abs(f - pl.fp(i)));%find(f == pl.fp(i),1,'first');
        if pl.conf
            ringColor = 'g';
        else
            ringColor = 'r';
        end
        plot3(pl.t0(i), pl.fp(i),Spec(SpecInd_freq,SpecInd_time),'o','Color',ringColor,'Markersize',10)
    end
end

[Sfft] = stftFFT(Spec);
dt_STFT = t(2)-t(1);
nSTFT = size(Spec,2);
Fs_STFT = 1/dt_STFT;
if mod(nSTFT,2)==0
    freqsHz_STFT  = Fs_STFT/nSTFT * (-nSTFT/2:nSTFT/2-1);
else
    freqsHz_STFT = Fs_STFT/nSTFT * (-(nSTFT-1)/2:(nSTFT-1)/2);
end
Sfft(:,freqsHz_STFT == 0) = NaN;
freqsHz_STFT_geq0_mask = freqsHz_STFT<=0;
Sfft(:,freqsHz_STFT_geq0_mask) = [];
freqsHz_STFT_geq0 = freqsHz_STFT(~freqsHz_STFT_geq0_mask);

blah = figure;
%surf(freqsHz_STFT,f_stft_stitch,10*log10(abs(Sfft).^2),'EdgeColor','none')
surf(freqsHz_STFT_geq0, f ,10*log10(abs(Sfft).^2),'EdgeColor','none')
xlabel('STFT Freq (Hz)');ylabel('Freq (MHz)');zlabel('S-fft magnitudes')
view([-28 84])




fclose(fid);


end