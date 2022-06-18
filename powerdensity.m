function [xpsd_out] = powerdensity(x,Fs,freqs,frequencyRangeType)
%POWERDENSITY Calculate the power spectral density (W/Hz) of the input
%signal x at the frequencies requested.
%   This function calculates the power spectral density of the input signal
%   x sampled at Fs at the frequencies requested in the input freqs
%   vector. The specral density is calculated from a dft of the input
%   signal. The number of samples in x should be larger than the number of
%   frequencies requested, as the fft length
%
%INPUTS:
%   x       [1xn]   Vector of samples taken at frequency Fs
%   Fs      1x1     Sample frequency (Hz) of x
%   freqs   [1xm]   A vector of frequencies at which the PSD is wanted.
%                   Values must be between +/-Fs/2 for 'centered' 
%                   frequencyRangeType and 0 and Fs for 'twosided'. Note
%                   that some extrapolation will be used if frequencies are
%                   above the limits defined for the two different range
%                   types. 
%
%                   For 'centered' frequenyRangeType:
%                   Minimum and maximum frequencies are dependent on Fs and
%                   the length of x. If x is even, -Fs/2<=freqs<=Fs/2. If x
%                   is of odd length, power can be computed 
%                   between Fs/N*ceil(-(N)/2) and Fs/N*floor(N/2). Between
%                   these limits and +/-Fs/2, power estimates are an
%                   extrapolation. 
%
%                   For 'twosided' frequenyRangeType:
%                   Minimum and maximum frequencies are dependent on Fs and
%                   the length of x. If x is even, 0<=freqs<=Fs/2. If x
%                   is of odd length, power can be computed 
%                   between Fs/N*ceil(-(N)/2) and Fs/N*floor(N/2).Between
%                   these limits and +/-Fs/2, power estimates are an
%                   extrapolation. 
%
%   
%   frequenyRangeType   A string containing 'centered' (default), 
%                       'twosided', or 'onesided'. See matlab stft.m 
%                       documentation for information on these ranges. 
%
%OUTPUTS:
%   xpsd_out [1xm]  Vector of power spectral densities at the requested
%                   frequencies
%%
%Author:    Michael W. Shafer
%Date:      2021-05-24
%
%% Validate inputs
%Check inputs

if (numel(x)+1)<numel(freqs)
    if coder.target('MATLAB')
       warning('UAV-RT: The number of requested frequencies is above those available from the discrete Fourier transform. Output values calculated between the FFT resolution will be interpolated values of those at the DFT frequencies. ')
    end
end

N = length(x);

if strcmp(frequencyRangeType,'centered')
    if max(freqs)>Fs/2
        error('UAV-RT: Maximum requested frequency is above the Nyquist frequency. For input x with even sample length N, requested frequencies must be less than Fs/2.')
    end
    if min(freqs)<-Fs/2
        error('UAV-RT: Minimum requested frequency is below the Nyquist frequency. For input x with even sample length N, requested frequencies must be between +/-Fs/2.')
    end
elseif strcmp(frequencyRangeType,'twosided')
    if max(freqs)>Fs
        error('UAV-RT: Maximum requested frequency is above the Nyquist frequency. For input x with even sample length N, requested frequencies must be less than Fs.')
    end
    if min(freqs)<0
        error('UAV-RT: Minimum requested frequency is below zero.')
    end 
end

[fftFreqs] = makeSTFTFreqVector(N,frequencyRangeType,Fs);
% 
% if max(freqs)>max(fftFreqs)
%     error('UAV-RT: Maximum requested frequency is above maximum allowabe frequency. For `centered` frequency range, requested frequencies must be between +/-Fs/2. For `twosided` frequency range, requested frequencies must be between 0 and Fs. For `onesided` frequency range, requested frequencies must be between 0 and Fs/2.')
% end
% if min(freqs)<min(fftFreqs)
%     error('UAV-RT: Minimum requested frequency is below minimum allowable frequency. For `centered` frequency range, requested frequencies must be between +/-Fs/2. For `twosided` frequency range, requested frequencies must be between 0 and Fs. For `onesided` frequency range, requested frequencies must be between 0 and Fs/2.')
% end



%% Calculate the output
dt = 1/Fs;
T  = numel(x)/Fs;
%Define the frequency bounds for the DFT needed for the PSD calcs
%See the fftshiftstft.m help to see these frequency definitions.
% if mod(N,2)==0
%     fftFreqs = Fs/N*(-N/2+1:N/2);
% else
%     fftFreqs = Fs/N*(ceil(-(N)/2):floor(N/2));
% end

%Compute the fft and shift to align with the frequency vector
xdft = fft(x);
%Compute power spectral density

if strcmp(frequencyRangeType,'onesided')
    xpsd = dt^2/T*abs(xdft).^2;
    inds = 1:floor(N/2)+1;
    xpsd = 2*xpsd(inds);
elseif strcmp(frequencyRangeType,'centered')
    xdft = fftshiftstft(xdft);
    xpsd = dt^2/T*abs(xdft).^2;
elseif strcmp(frequencyRangeType,'twosided')
    xpsd = dt^2/T*abs(xdft).^2;
end

% Use a moving mean as a way of averaging the xpsd with a bin width equal
% to the fftlenght/number of frequencies requested.
if numel(fftFreqs)>=numel(freqs)
    xpsd_movmean  = movmean(xpsd,floor(numel(fftFreqs)/numel(freqs)));
    xpsd_out  = interp1(fftFreqs,xpsd_movmean,freqs,'linear','extrap');
else
    xpsd_out  = interp1(fftFreqs,xpsd,freqs,'linear','extrap');
    
end

end

