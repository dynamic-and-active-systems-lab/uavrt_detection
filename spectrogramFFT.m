function [] = spectrogramFFT(TheStftObj)
%Does a single sided amplitude spectrum FFT of the time columns of the stft 
%after computing the spectrogram (abs(stft).^2)

%If X is a matrix, then fft(X) treats the columns of X as vectors and returns the Fourier transform of each column.
nFreqs     = size(TheStftObj.S, 1);
nTimeSamps = size(TheStftObj.S, 2);

dtSpec = TheStftObj.t(2) - TheStftObj.t(1);
Fs = 1/dtSpec;

ff = Fs/nTimeSamps*(0:(nTimeSamps/2));
fftResult = fft(abs(TheStftObj.S).^2.').';
P2 = abs(fftResult/nTimeSamps);
P1 = P2(:,1:nTimeSamps/2+1);
P1(:,2:end-1) = 2*P1(:,2:end-1);

figure;
surf(ff(2:end), TheStftObj.f, P1(:,2:end))


end