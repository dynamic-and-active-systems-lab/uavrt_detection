function [threshold_vec] = getthresholdvec(X,PF,DECISION_ENTRY,time_search_type)
%GETTHRESHOLDVEC provides the decision threshold (lambda) vector based on 
%the decision database provided and the probability of false alarm.
%   This function will look up the the appropriate threshold values from
%   the decision database provided as the input based on the parameters of
%   the pulse within priori pulse stats information in the waveform. The
%   program calculates the necessary non-dimensional parameters from the
%   priori information. It then checks to see if a decision table exists in
%   the provided database. The necessary non-dimensional decision parameter
%   is then extracted from the table. The noise power spectral density is
%   then estimated from the signal waveform data and the dimesional
%   decision threshold is calculated  
%
%INPUTS:
%   X      A single input waveform with populated priori pulsestats object.
%   PF     Probability false alarm 
%   DECISION_ENTRY   The decision_threshold object. 
%
%OUTPUTS:
%   threshold_vec   A threshold vector in units of W for each frequency bin 
%                   in the SFTF matrix . Note that this will have the same 
%                   precision as the data within the waveform (x). If 
%                   single precision data is held in x, the threshold 
%                   output will be single precision. 
%
%
%
%%
%Author: Michael W. Shafer
%Date:   2021-05-21
%
%
%%
%Extract necessary variables for cleaner coding
Fs   = X.Fs;
x    = X.x;
OLF  = X.OLF;
K    = X.K;
tp   = X.ps_pre.t_p;
tip  = X.ps_pre.t_ip;
tipu = X.ps_pre.t_ipu;

%Calculate the non-dimensional parameters
S_P   = ceil(X.ps_pre.t_p*X.Fs);   %Samples per pulse
S_IPU = round(X.ps_pre.t_ipu*X.Fs);%Inter-pulse uncertainty samples
S_IP  = round(X.ps_pre.t_ip*X.Fs); %Inter-pulse samples


if strcmp(time_search_type,'naive')
    nondim_thresh = interpn(DECISION_ENTRY.K_vec,...
                            DECISION_ENTRY.S_IPU_vec,...
                            DECISION_ENTRY.PF_vec,...
                            DECISION_ENTRY.naive_lambda_array,...
                            K,S_IPU,PF);
else
    nondim_thresh = interpn(DECISION_ENTRY.K_vec,...
                            DECISION_ENTRY.S_IPU_vec,...
                            DECISION_ENTRY.PF_vec,...
                            DECISION_ENTRY.informed_lambda_array,...
                            K,S_IPU,PF);
end



%Does the required decision table exist in the database?
% existing_entry = any(DECISION_DATABASE.K      == K     &...
%                       DECISION_DATABASE.OLF   == OLF   &...
%                       DECISION_DATABASE.S_P   == S_P   &...
%                       DECISION_DATABASE.S_IPU == S_IPU);
% %                      DECISION_DATABASE.S_IP  == S_IP  &...
% if ~existing_entry
%     caseneededstr = ['K = ',num2str(K),', '...
%                  'OLF = ',num2str(OLF),', '...
%                  'S_P = ',num2str(S_P),', '...
%                  'S_IPU = ',num2str(S_IPU)];
%     error(['UAV-RT: Decision database does not include an entry for the case required here. Add the case ',caseneededstr,' to the database and try again.']);
% end
% 
% %Find the rows that have the decision table we need                  
% tablerows = find(DECISION_DATABASE.K     == K     &...
%                       DECISION_DATABASE.OLF   == OLF   &...
%                       DECISION_DATABASE.S_P   == S_P   &...
%                       DECISION_DATABASE.S_IPU == S_IPU);
% %                      DECISION_DATABASE.S_IP  == S_IP  &...
%  
% %There are entries for a variety of S_IP values, but all the distributions 
% %are the same, so we'll just use the first. 
% tablerow = tablerows(1);
% 
% %Extract the necessary table
% nondim_thresh = interp1(DECISION_DATABASE{tablerow,7},...%PF Vector
%                         DECISION_DATABASE{tablerow,8},...%Lambda Values
%                         PF);
%Get the number of FFT bins. Needed later to get PSD in the central 75% of
%BW.
fftlength = length(X.stft.f);
%Clip large amplitude and estimate the power spectral density
if any(X.x~=0)
inds2use = (abs(X.x)<4*median(abs(X.x(X.x~=0))))&...
           (abs(X.x)~=0);
else
    inds2use = true(1,numel(X.x));
end

%Old method that used PSD of entire signal. 
noise_pdx_est = powerdensity(X.x(inds2use),X.Fs,X.stft.f,'centered');
%PSD = dt^2/T*mag(dft)^2
%New method like Welch's SPD method, but using median. 
%noise_pdx_est = median((1/X.Fs).^2/(X.n_w/X.Fs)*abs(X.stft.S).^2,2);

%Get average noise power density in region away from
%rolloff at edges of bandwidth. Using the central 75% of
%BW.
%central_noise_pdx = mean(noise_pdx_est(floor(0.125*fftlength):ceil(0.875*fftlength)));
%lengthfor400HzBWmovingaverage = 400/(Fs*1/fftlength);
%central_noise_pdx = max(movmean(noise_pdx_est,lengthfor400HzBWmovingaverage));
%Calculate the dimensional threshold. 
%threshold = nondim_thresh*central_noise_pdx*X.Fs;
threshold_vec = nondim_thresh*noise_pdx_est*X.Fs;
%threshold_vec = nondim_thresh*movmean(noise_pdx_est,lengthfor400HzBWmovingaverage)*X.Fs;

end

