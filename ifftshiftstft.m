function [xout] = ifftshiftstft(x)
%IFFTSHIFTSTFT Performs a standard ifftshift operation but accounts for the
%different frequency range definition in Matlabs STFT function when
%outputing a 'centered' frequency range
%   When calling the STFT function, the default output for frequency is
%   the 'centered' method where frequencys are reported on the range of
%   (-n/2+1:n/2)*Fs/n if the vector is of even length and
%   (ceil(-n/2):floor(n/2))*Fs/n if the vector is of odd length. It seems
%   that Matlab's ifftshift function is develped for frequencies in the
%   range of (-n/2:n/2+1)*Fs/n if the vector is of even length. The odd
%   length definition is unaffected. The result is an incorrect shifting of
%   the frequency vector if ifftshift is used on f defined by stft's
%   centered method. This function usese the ifftshift command for vectors
%   of even length, but first shifts the vector by 1 to the right to 
%   correct for this problem. 
%
%INPUTS:
%   x       nxm     A matrix of real or complex data. If passed a matrix,
%                   the rows should represent frequency bins
%OUTPUT:
%   xout    nxm     A matrix of real or complex shifted data
%%
%
% Author: Michael Shafer
% Date:   2020-12-19
%
%% Change log:
% 2022-01-10    Updated to deal with row or column vectors or stft matrices
%
%%
sz = size(x);
% if (numel(sz)~=2) && (min(sz)~=1)
%     error('fftshiftstft only accepts vector inputs.')
% end

if sz(1)==1 && sz(2)~= sz(1) %Passed a row vector
    dim2shift = 2;
else %Passed a matrix or a column vector
    dim2shift = 1;
end

n = numel(x);
if mod(n,2)
    xout = ifftshift(x,dim2shift);    
else
    xout = ifftshift(circshift(x,1,dim2shift),dim2shift);
end

end

