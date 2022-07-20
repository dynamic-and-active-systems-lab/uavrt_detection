function [newThresh] = buildthreshold(Wfm, PF ,W, Wf)
%BUILDTHRESHOLD generates a threshold vector for the waveform argument
%based on the false alarm probability input. 
%
%This function creates a vector of thresholds for the incoherently summed
%results of the data in the input waveform. The probability of false alarm
%input is used for threshold generation. The output vector is a spectrally
%tuned threshold for each frequency in the STFT of the waveform. These
%thresholds are dependent on the power spectral density for each frequency
%bin, so areas of the spectrum with a high noise floor will have a higher
%output thresholde value
%
%INPUTS:
%   Wfm     A single waveform object
%   PF      A scalar probability of false alarm value (0 1];
%OUTPUTS:
%   newThresh   A vector of threshold with as many elements as rows in the
%               S matrix of the wfmstft object within the Wfm input. 
%
%Author:    Michael W. Shafer   
%Date:      2022-05-04
%--------------------------------------------------------------------------
%tic
freqBinPSD = Wfm.stft.psd; %Extract psd for current waveform
freqBinPow = freqBinPSD*(Wfm.stft.f(2)-Wfm.stft.f(1));  %PSD (W/Hz) times bin width (Hz/bin) gives bin total power in (W/bin)
%freqBinPSD = (1/Wfm.Fs)^2/Wfm.ps_pre.t_p*mean(abs(W'*Wfm.stft.S).^2,2); %Extract psd for current waveform
%freqBinPow = freqBinPSD*(Wfm.stft.f(2)-Wfm.stft.f(1));  %PSD (W/Hz) times bin width (Hz/bin) gives bin total power in (W/bin)
%MULT BY THE ORIGINAL FREQUENCY BIN WIDTH BECAUSE STILL CONSIDERS FREQUENCY
%BINS OF THE ORIGINAL WIDTH, BUT WITH STEPS THAT ARE A FRACTION OF A
%FREQUENCY BIN WIDTH BETWEEN THEM.

medPowAllFreqBins = median(freqBinPow);

stftSz     = size(Wfm.stft.S);
nTimeWinds = stftSz(2);
nFreqBins  = stftSz(1);


Wq = buildtimecorrelatormatrix(Wfm.N, Wfm.M, Wfm.J, Wfm.K);
%Wq = Wfm.TimeCorr.Wq(Wfm.K); %Build the Wq matrix using the Wq method of the temporalcorrelator object for K pulses
if nTimeWinds ~= size(Wq,1)
    error('UAV-RT: Time correlator/selection matrix must have the same number of rows as the number of columns (time windows) in the waveforms STFT matrix.')
end
%Here we approximated the number of samples of synthetic noise data needed 
%to get the correct number of time windows. We over estimate here and then
%clip the number of correct windows after the stft operation.
nSamps = (nTimeWinds+1)*Wfm.n_ws+Wfm.n_ol;%Based on the STFT help file for the number of windows as a function of samples. We add an additional windows worth of samples to ensure we have enough in our STFT output. We'll clip off any excess after the STFT

trials       = 100;                              %Number of sets of synthetic noise to generate
%scores      = zeros(nFreqBins,trials);         %Preallocate the scores matrix
scores       = zeros(trials,1);         %Preallocate the scores matrix
Psynthall    = medPowAllFreqBins*nFreqBins;     %Use the median power of the input wfm as the power for the synth data. We'll use a linear relationship later to scale threshold for each of the different power values for each frequency bin.
xsynth       = wgn(nSamps,trials,Psynthall,'linear','complex'); %Generate the synthetic data
[Ssynth,~,~] = stft(xsynth,Wfm.Fs,'Window',Wfm.stft.wind,'OverlapLength',Wfm.n_ol,'FFTLength',Wfm.n_w);
Ssynth(:,nTimeWinds+1:end,:) = [];              %Trim excess so we have the correct number of windows. 

%SsynthMagSqrd = abs(Ssynth).^2;                 %Calculate the mag^2
 %tic
%  SsynthMagSqrd = zeros([size(W,2),size(Ssynth,2),trials]);
%  for i = 1:trials    
%      SsynthMagSqrd(:,:,i) = abs(W'*Ssynth(:,:,i)).^2;
%  end


%Preform the incoherent summation using a matrix multiply.
%Could use pagetimes.m for this, but it isn't supported for code generation
for i = 1:trials    
    %scores(:,i) = max(SsynthMagSqrd(:,:,i)*Wq,[],2);
    scores(i) = max(abs(W'*Ssynth(:,:,i)).^2 * Wq, [], 'all');
    %scores(i) = max(SsynthMagSqrd(:,:,i)*Wq,[],'all');
end

%Because all frequeny bins have the same power the score of each frequency
%bin for each trial is and independent sample. Build the distribution for
%all scores. 
% [f,xi]   = ksdensity(scores(:),'BoundaryCorrection','reflection','Support','positive');
% F        = cumtrapz(xi,f);
% tic
% [fm,xmi]   = ksdensity(max(scores,[],1),'BoundaryCorrection','reflection','Support','positive');
% Fm        = cumtrapz(xi,f);
% toc
xi = linspace(1/2*min(scores),2*max(scores),1000);
paramEstsMaxima = evfit(-scores);
F = 1 - evcdf(-xi,paramEstsMaxima(1),paramEstsMaxima(2));
%figure;plot(xi,F)


% subplot(3,1,1)
% plot(i,paramEstsMaxima(1),'bo');hold on
% subplot(3,1,2)
% plot(i,paramEstsMaxima(2),'ro');hold on
% subplot(3,1,3)

% p = evpdf(-xim,paramEstsMaxima(1),paramEstsMaxima(2));
% toc
% figure;
% histogram(max(scores,[],1),'Normalization','pdf');
% hold on
% plot(xim,fm,'DisplayName','kernel'); hold on;
% plot(xim,p,'DisplayName','ev'); legend('Location','best')

%Now we linearly interpolate the threshold values for different noise
%powers. We showed elsewhere this linear relationship hold by calculating
%thresholds for ranges of noise power. 
%Here we deal with points where there is no change in F. Interp needs 
%unique values and at the tails of the distibution, there may be repeated 
%values. 
nochangelogic = [false,diff(F)==0]; 
threshMedPow = interp1(F(~nochangelogic),xi(~nochangelogic),1-PF,'pchip','extrap');

powGrid    = [0 medPowAllFreqBins];
threshGrid = [0 threshMedPow];
newThresh = interp1(powGrid,threshGrid,freqBinPow,'linear','extrap');

%Finally,extrapolating the thresholds that are a little beyond the original 
%frequeny range can result in negative thresholds. Here we copy the first
%and last valid threshold out to the places where the extrapolations would
%have occured
isnanThreshLogic   = isnan(newThresh);
firstTrueThreshInd = find(~isnanThreshLogic,1,'first');
lastTrueThreshInd  = find(~isnanThreshLogic,1,'last');
firstTrueThresh    = newThresh(firstTrueThreshInd);
lastTrueThresh     = newThresh(lastTrueThreshInd);
newThresh(1:firstTrueThreshInd(1)) = firstTrueThresh; %The (1) call is needed by coder, as it doesn't know that the find call above will only produced a scalar output.
newThresh(lastTrueThreshInd(1):end) = lastTrueThresh; %The (1) call is needed by coder, as it doesn't know that the find call above will only produced a scalar output.
%toc
end
