function [freqs] = makeSTFTFreqVector(nfft,frequencyRangeType,Fs)
%MAKESTFTFREQVECTOR Generates the frequency vector based on the frequency
%range specification for Matlab's stft.m 'FrequencyRange' input standard,
%
%   This function outputs a frequency vector based on the frequency
%   range specification for Matlab's stft.m 'FrequencyRange' input 
%   standard. The options for the frequency ranges are 'centered'
%   (default), 'twosided', and 'onesided'. The sftf.m documentation
%   standard states: 
%       STFT frequency range, specified as 'centered', 'twosided', or 
%       'onesided'.
%
%       'centered' — Compute a two-sided, centered STFT. If 'FFTLength' is 
%       even, then s is computed over the interval (–π, π] rad/sample. If  
%       'FFTLength' is odd, then s is computed over the interval (–π, π)  
%       rad/sample. If you specify time information, then the intervals are 
%        (–fs, fs/2] cycles/unit time and (–fs, fs/2) cycles/unit time,  
%       respectively, where fs is the effective sample rate.
%
%       'twosided' — Compute a two-sided STFT over the interval [0, 2π)  
%       rad/sample. If you specify time information, then the interval is  
%       [0, fs) cycles/unit time.
%
%       'onesided' — Compute a one-sided STFT. If 'FFTLength' is even,  
%       then s is computed over the interval [0, π] rad/sample. If  
%       'FFTLength' is odd, then s is computed over the interval [0, π)  
%       rad/sample. If you specify time information, then the intervals are 
%        [0, fs/2] cycles/unit time and [0, fs/2) cycles/unit time,  
%       respectively, where fs is the effective sample rate. This option is 
%        valid only for real signals.
%
%
%   If Fs is not specificed, outputs will be in rad/sample with pi as
%   specified in the stft.m frequency range standard. 
%   
%INPUTS:
%   nfft                 Length of FFT performed on the STFT.
%   frequencyRangeType   String containing 'centered', 'twosided', 'onesided'
%   Fs                   Sample rate of data         
%
%OUTPUTS:
%   freqs       Vector of frequencies at which the STFT is calculated
%
%Author:    Michael Shafer
%Date:      2022-01-11
%
%%

if nargin == 2
    
    Fs = 2*pi;
    
end


if strcmp(frequencyRangeType, 'centered')    
    
    if mod(nfft, 2)==0
        
        freqs = (-nfft/2+1:nfft/2)*Fs/nfft;
        
    else
        
        freqs = (ceil(-nfft/2):floor(nfft/2))*Fs/nfft;
        
    end
    
elseif strcmp(frequencyRangeType, 'twosided')
    
    freqs = (0:(nfft-1))*Fs/(nfft);
    
elseif strcmp(frequencyRangeType, 'onesided')
    
    if mod(nfft, 2)==0
        
        freqs = (0:nfft/2)*Fs/nfft;
        
    else
        
        freqs = (0:floor(nfft/2))*Fs/nfft;
        
    end
        
end

end

