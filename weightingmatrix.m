function [W,Wf] = weightingmatrix(x_of_n_in,Fs,zetas,frequencyRangeType)
%WEIGHTINGMATRIX Builds the spectral weighting matrix for the incoherent
%summationation algorithm. The matrix is based on the DFT coefficients
%developed from the waveform passed to the function. The function first
%developeds a weighting vectors based on an unaltered waveform, but then
%shifts the waveforms spectral content base fractions of the DFT bin width,
%as defined by the zetas input. These shifted waveforms then have their
%DFT's computed. The original and shifted DFT coefficients are then aligned
%in a matrix. In this way, this weighting matrix allows for the dominant
%frequency in the vector it weights to be between bins. This submatrix is
%then row shifted and concantinated a number of times so that the DFT
%coefficients are shifted across all DFT frequency bins. The outputs are 
%the weighting matrix W and a frequency vector Wf that corresponds to the 
%rows of W. The frequencies, and therefore the rows of the W matrix, use a
%centered frequency definitions defined by the STFT.m algorithm. 
%
%   Example:   [W,Wf] = weightingmatrix(rand(1,10),1,[0 0.5])
% 
%   INPUTS:
%   x_of_n      nx1     Vector of discrete data sampled as Fs. Can be 1xn.
%   Fs          1x1     Sampling rate in Hz of the dataset
%   zetas       mx1     A vector of fractions of the DFT frequency bin
%                       width for which to compute and include in the
%                       spectral weighting matrix output. If no interbin
%                       shifting is desired, enter 0. Range of inputs
%                       [0,1).
%   frequencyRangeType  String of either 'centered' or 'twosided'. See
%                       stft.m documentation on details of these frequency
%                       bounds. If 'centered' is selected, the zero
%                       frequency point is near the center of the output
%                       matrix. If 'twosided' is selected, the zero
%                       frequency points is in the upper left corner of the
%                       output W matrix. 
%
%   OUTPUTS:
%   W           nxnm    A matrix of spectral weighting vectors along each
%                       column. The hermitian of this matrix is designed to
%                       be multiplied by a vector of DFT coefficients. The 
%                       weights held in column p can be thought of as the
%                       matched DFT coefficients if the signal were to have
%                       been shifted by the template by Wf(p). 
%   Wf          nmx1    A matrix of the frequency shifts corresponding to
%                       each column of W 
%
%
% The intended use of the W matrix is to multiply it's hermetian by a FFT 
% vector, or STFT matrix with frequencies in the rows. 
%          
%
%   [W^h]*S         or          [W^h]*FFT
%
% The outputs of this multiplication will have n*m rows. The rows of the
% result there for are the "scores" of at frequency associated with that
% row. The row frequencies are dependent on the zetas. Consider an input
% series that had frequencies [-100 0 100 200]. If the zeta input was 
% [0 0.5], weightings for full and half frequencies steps would be 
% developed. 
%
%       output freq     input freq
%                           -100    0   100     200
%               -150    [                           ]
%               -100    [                           ]
%               -50     [                           ]
%               0       [            W^h            ]
%               50      [                           ]
%               100     [                           ]
%               150     [                           ]
%               200     [                           ]
%
%   The first row of the matrix above would contain the weightings for the
%   -100 0 100 and 200 Hz frequencie bins if the FFT (or STFT time window)
%   had a signal at -150 Hz. Similarly, the second row would contain the 
%   weightings for the -100 0 100 and 200 Hz frequencie bins if the FFT 
%   (or STFT time window) had a signal at -100 Hz. 
%
%
%
%
%Author: Michael Shafer
%Date:   2020-12-19
%
%% Change Log
% 2022-01-12    Updated to include twosided frequency range for output and
%               updated the code associated with generating the unsorted W
%               matrix to increase speed. Added use of makestftFreqVector
%               function. 
%
%

%Check the inputs
if ~isvector(x_of_n_in)
        error('Input x must be a vector with only one row or column')
end

if numel(Fs)~=1 && Fs>0
    error('Sample rate input must be a positive scalar. ')
end

if ~isvector(zetas) && ~isreal(zetas)
    error('Zetas input must be a real valued vector or scalar.')
end

if max(zetas)>=1
    error('Maximum input interbin fractions (zeta) must be less than 1.')
end
if min(zetas)<0
    error('Minimum input interbin fractions (zeta) must be greater than or equal to 0.')
end

if strcmp(frequencyRangeType,'twosided') && strcmp(frequencyRangeType,'centered')
        error('UAV-RT: Frequency range type must be either twosided or centered')
end


%Reshape to a column vector, as the algorithm expects
if size(x_of_n_in,2)~=1
    x_of_n = transpose(x_of_n_in);
else
    x_of_n = x_of_n_in;
end
nw = numel(x_of_n);
numZetas = numel(zetas);
%F_bin_width = Fs/nw;
n = transpose(0:(nw-1));

%Use complex so when implementing in simulink later, it knows this is a
%complex vector.

s	= 1i*zeros(nw,numZetas);
Xs  = 1i*zeros(nw,numZetas);

%Develop a vector of frequencies that would result from the centered method
%of the STFT function if it were computed on the x input. This is useful
%for debugging the frequency outputs.
%These are designed to develop the same freqs as the STFT centered method 
%Check the "'FrequencyRange' — STFT frequency range" in the STFT help file
%if mod(nw,2)==0
%    freqs_orig = ((-nw/2+1):nw/2)*Fs/nw;
%else
%    freqs_orig = (ceil(-nw/2):floor(nw/2))*Fs/nw;
%end

%figure;
for i = 1:numZetas
    s(:,i)  = exp(1i*2*pi*zetas(i)*n./nw);
    currDFT = fft(s(:,i).*x_of_n);
    Xs(:,i) = fftshiftstft(currDFT/norm(currDFT));
%   stem(freqs_orig,abs(Xs(:,i)),'DisplayName',['\zeta =',num2str(zetas(i))]); 
%   hold on
end
%ylabel('|Xs|');xlabel('Frequency');legend('Location',"best");
%title('DFT of primary frequency shifts of the template')

%New W generation method. ~25% faster on average
stackedToeplitzMatrices = complex(zeros(numZetas*nw,nw));
for i = 1:numZetas
    rowStart = (i-1)*nw+1;
    rowEnd = rowStart+nw-1;
    stackedToeplitzMatrices(rowStart:rowEnd,:) = toeplitz(Xs(:,i),[Xs(1,i); flipud(Xs(2:end,i))]);    
end
%Reshape in this way will interweave rows of each sub matrix of the stack
W = reshape(stackedToeplitzMatrices,nw,numZetas*nw);

%OLD W generation method. Easier to understand, but slower
% W     = 1i*zeros(nw,numZetas*nw);
% freqs = zeros(1,numZetas*nw);
% for i = 1:nw
%     W(:,(i-1)*numZetas+(1:numZetas))=...
%         circshift(Xs,i-1,1);
% end


%Build a vector of the frequencies
%  tick=1;
%  for i = 1:numZetas:size(W,2)
%      freqs(i:i+(numZetas-1)) = Fs/nw*((tick-1)+zetas);
%      tick = tick+1;
%  end
freqs = makeSTFTFreqVector(2*nw,'twosided',Fs);

%Simulink (coder?) didn't like the new round inputs
%freqs = round(freqs,3);

%freqs = round(freqs*1000)/1000;



%Shift everything so we use a negative frequencies
nyq_ind = zeros(1,1);%A little non-matlab notation to get this to run in simulink.
%nyq_ind(1)  = find(freqs == floor(Fs/2),1,'first');
nyq_ind(1)  = find(freqs == Fs/2,1,'first');
frequency_shift_amount = -freqs(end)-(Fs-freqs(end));
zero_padding = zeros(1,nyq_ind);
wrapper = [zero_padding,frequency_shift_amount*ones(1,numel(freqs)-nyq_ind)];
Wf = wrapper'+freqs';

%Here we sort the output to set up to have an ascending order of frequency
%to be similar to the centered frequency list used elsewhere in the
%codebase for the STFT output. 

[Wf,inds] = sort(Wf);
W = W(:,inds);

if strcmp(frequencyRangeType,'twosided')
    W = ifftshiftstft(W);%Shift the rows to twosided from centered
    W = transpose(ifftshiftstft(transpose(W)));%Shift the colums to two sided from centered
end

end

