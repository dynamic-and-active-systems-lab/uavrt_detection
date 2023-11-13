function [allWeightsMat] = repetitionrejector(t,repFreqHz)
%REPETITIONREJETOR Build the comb filter matrix used to reject repeaing
%patterns in the stft matrix. 
%INPUTS:
%   t   a vector of time values for the columns of an stft matrix
%   repFreqHz   n x 1   a vector of frequencies to reject. ex: [2 3 5 10]
%OUTPUTS
%   allWeightsMat   sparse matrix of the comb filter
%
%Author: Michael Shafer
%Date:  Fall 2023
%
%--------------------------------------------------------------------------
%

if numel(t)<2
    fprintf('UAV-RT: Time vector must contain at least two elements.\n')
end

dt = t(2)-t(1);

if sum(round(diff(t)*1e9)/1e9-dt)~=0 %dealing with numerical precision for diff(t)-dt
    fprintf('UAV-RT: Time difference in t vector must be constant.\n')
end

numRepFreqs = numel(repFreqHz);

if numRepFreqs < 1
    fprintf('UAV-RT: Number of repetition frequencies must be greater than 0.\n')
end

%Force to be a row vector
t = t(:).';

allWeightsMat = speye(numel(t));

if repFreqHz ~= 0
    allWeights = zeros(size(t));


    for i = 1:numRepFreqs
        dtOfRepSig = 1/repFreqHz(i);
        mask = zeros(size(t));
        mask(mod(t, dtOfRepSig) < dt/2 | mod(t, dtOfRepSig) >= dtOfRepSig - dt/2)= 1;
        %-1 because the first element of the vector will be the diagonal 1s of the
        %identity part of the matrix. Want the sum of the other terms pulse the
        %first term (1) to be zero)
        numMask = sum(mask) - 1 ;
        weights = zeros(size(t));
        weights(mask==1)   = -1/numMask;
        allWeights = allWeights + weights;
    end

    %Have to flip the weights so there is symetry in negative time so that when
    %we use the circular shift operation, the repeated signal shows up at the
    %right time to the left of the 1 value.
    allWeights(1) = 1;
    allWeightsDouble = [flip(allWeights(2:end)),allWeights];
    allWeightsDoubleMat = zeros(numel(allWeightsDouble),numel(allWeightsDouble));

    for i = 0:numel(t)-1
        allWeightsDoubleMat(i+1,:) = circshift(allWeightsDouble,i);
    end

    allWeightsUpperLeft = allWeightsDoubleMat(1:numel(t),numel(t):end);

    allWeightsMat = sparse(allWeightsUpperLeft);

end


end