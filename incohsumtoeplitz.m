function [Sscores,Scols] = incohsumtoeplitz(Fb,Wfherm,S,IR,Tb,Wq)
%INCOHSUMTOEPLITZ Performs the incoherent summation of time windows of an
%input matrix S per the elements in the time selection matrix Wq.
%   This function performs the incoherent summation of time elements within
%   the short time Fourier transform matrix S per the selections within the
%   Wq matrix. The rows of the S matrix represent frequency bins, whereas
%   the columns represent the time windows. The Wq matrix is a Toeplitz
%   based matrix with non-zero elements of each column used to select and
%   then sum through matrix multiplication the time windows of S.
%    abs(S).^2    *  Wq
%   [1   2  3  4]  [1 0]
%   [5   6  7  8]  [0 1]
%   [9  10 11 12]  [1 0]
%   [13 14 15 16]  [0 1]
%
%   The other matricies are used to select and weight the frequency and
%   time elements of S through matrix multiplication. The Wfherm matrix
%   applies weightings to the S matrix across frequency in order to capture
%   energy spread across frequency bins. Fb is a matrix or a vector with 1s
%   in elements associated with the frequency bins of Wh that are to be
%   included for consideration. Similarly, the Tb matrix (vector) uses 1s
%   to select time elements for consideration. Both Fb and Tb can use zeros
%   to exclude particular frequencies or times from consideration in
%   processing.
%
%   The code performs the matrix multiplication Fb*Wfherm*abs(S).^2*Tb*Wq.
%   The sizes of these matricies must be set so that this matrix
%   multiplication can be performed. The functions checks for correct
%   dimensions and will generate an error of dimensional mismatch occurs.
%   After performing the matrix multiplication of Fb*Wfherm*S*Tb*Wq, it
%   determines which columns of the resulting matrix are maximum in each
%   row (frequency bin). The function reports the a matrix that has the
%   same number of rows as Fb and K columns that contains the scores for
%   in each S time window that the maximum summed score based on the Wq
%   matrix selections for each frequency bin. It also reports a similarly
%   size matrix that contains the columns in S where these max scores were
%   found
%
%   The number of pulses for summation (K) is extracted from Wq by querying
%   the number of non-zero elements in the first column of the Wq matrix.
%
%
%INPUTS:
%   Fb      Frequency blinder matrix: A matrix (fz x fz) or vector (fz x 1)
%           of elements with 1s for frequencies of the Wfherm matrix that
%           should be considered when looking for maximum incoheren
%           summation. If the rows of the Wfherm matrix represent
%           frequencies of [100 50 0 -50 -100] and the search needs to
%           focus only on the 0 and 50 Hz bins, Fb should be [0 1 1 0 0]
%           or diag([0 1 1 0 0]). Inputs can be full or sparse.
%   Wfherm  Hermitian of the spectral weighting matrix. This matrix should
%           have the same number of columns as the number of rows in S. See
%           weightingmatrix.m for information on this matrix. The function
%           weightingmatrix.m generates Wf, so when passing Wf to this
%           function, Wf' should be used.
%   S       STFT output matrix
%   Tb      Time blinder matrix: A matrix with only diagonal elements or a
%           vector that contains 1s that corresponds to the columns (time
%           windows) of the S matrix that should be considered for
%           summation. If priori information informs the caller as to the
%           potential location of the pulses in the block being processed,
%           the Tb matrix can be used to exclude other times from
%           consideration which can considerably decrease processing time
%           for this function. If no-priori is available, this entry should
%           be the identity matrix or vector of size equal to the number
%           of columns of S.
%   Wq      Time correlation matrix: A matrix containing 1s in entries in
%           each column for S matrix time windows that should be summed.
%           Wq must have the same number of rows as columns of S, but can
%           have as many columns as summation cases that need to be
%           considered.
%   IR      Repetition rejection comb filter matrix. Set to the identity to
%           if no comb filtering is needed.
%
%OUTPUTS:
%   Sscores The results of the incoherent summation of S per the time
%           selections of the inputs after looking for maximums for each
%           frequency bin. This has the same number of rows as that of the
%           input Fb and the same number of columns a the number of pulses
%           used for summation. The matrix has K columns. The scores
%           represent the square magnitudes of the selected elements of the
%           S matrix.
%
%   Scols   A matrix of the columns of S (time windows of STFT)
%           that correspond to the potential pulses identified
%           in Sscors. The size of this matrix is the same as Sscores.
%
%%
%Author: Michael W. Shafer
%Date:   2022-03-31
%--------------------------------------------------------------------------

Ssz  = size(S);
Wqsz = size(Wq);
Tbsz = size(Tb);
Wfhermsz = size(Wfherm);
Fbsz = size(Fb);

TbisaMatrix = min(Tbsz)~=1;
FbisaMatrix = min(Fbsz)~=1;

if numel(Fbsz)>2 || numel(Tbsz)>2 
    error('UAV-RT: Fb and Tb arguments must be a square matrix or a vector.')
end
if numel(Ssz)~=2 || numel(Wqsz)~=2 || numel(Wfhermsz)~=2
    error('UAV-RT: S, Wq, and Wfherm arguments must be a matrix.')
end

if ~TbisaMatrix && Tbsz(2)~=1
    error('UAV-RT: Tb must be a logical square matrix or a column vector')
end
if ~FbisaMatrix && Fbsz(2)~=1
     error('UAV-RT: Fb must be a logical square matrix or a column vector')
end


if TbisaMatrix && (Tbsz(1)~=Tbsz(2))
    error('UAV-RT: If Tb is a matrix, it must be square.')    
end
if FbisaMatrix && (Fbsz(1)~=Fbsz(2))
    error('UAV-RT: If Fb is a matrix, it must be square.')    
end
Tbnumrows = max(Tbsz);
Tbnumcols = Tbnumrows;
Fbnumrows = max(Fbsz);
Fbnumcols = Fbnumrows;

if Fbnumcols~=Wfhermsz(1) 
    error('UAV-RT: Number of columns of Fb must equal number of rows of Wfherm')
end
if Wfhermsz(2)~=Ssz(1)
    error('UAV-RT: Number of columns of Wfherm must equal number of rows of S')
end
if Ssz(2)~=Tbnumrows 
    error('UAV-RT: Number of columns of S must equal number of rows of Tb')
end
if Tbnumcols~=Wqsz(1)
    error('UAV-RT: Number of columns of Tb must equal number of rows of Wq')
end

%Make sure the number of pulses considered for all Wq columns is the same
pulsesInEachColumn  = sum(Wq,1);
firstPulseNum = pulsesInEachColumn(1);
if any(pulsesInEachColumn<=0)
    error('UAV-RT: Number of pulses in each column of Wq matrix must be greater than zero');
end
sameAsFirst = pulsesInEachColumn==firstPulseNum;
if any(~sameAsFirst) %numel(unique(full(pulsesInEachColumn)))~=1 %Unique doesn't support sparse for code-generation. %numel(unique(sum(Wq,1)))~=1 
	error('UAV-RT: Number of non-zero entries in each column of the Wq matrix must the the same for all columns.')
end


%% Generate Tb and Fb sparse matrices if entered as vectors
%Frequency Blinder (Fb) matrix definitions:
numelFbDiagElements = max(Fbsz);
FbMatSz = [1,1]*numelFbDiagElements;
FbSparseMat = logical(speye(FbMatSz));%Prototype Fb matrix with identity logical matrix
FbmatDiagInds = sub2ind(FbMatSz,1:numelFbDiagElements,1:numelFbDiagElements);
if min(Fbsz) == 1 %Passed a vector, so make the matrix
    Fbdiags = logical(full(Fb));
    %FbSparseMat = logical(speye(max(Fbsz)));
    FbSparseMat(FbmatDiagInds) = Fb;
else %Passed a matrix, so make sparse. 
    %FbSparseMat = logical(sparse(Fb));
    FbSparseMat(FbmatDiagInds) = Fb(FbmatDiagInds); %Had do do it this way rather than with logical(sparse(Fb)) to get code to work with Fb being either a vector or matrix.
    Fbdiags = transpose(full(FbSparseMat(FbmatDiagInds))); %Get the diag elements. Transpose needed for size considerations for code generation.
end
%Time Blinder (Tb) matrix definitions:
numelTbDiagElements = max(Tbsz);
TbMatSz = [1,1]*numelTbDiagElements;
TbSparseMat = logical(speye(TbMatSz));%Prototype Fb matrix with identity logical matrix
TbmatDiagInds = sub2ind(TbMatSz,1:numelTbDiagElements,1:numelTbDiagElements);
if min(Tbsz) == 1
    Tbdiags = logical(sparse(Tb));
    TbSparseMat = logical(speye(max(Tbsz)));
    TbSparseMat(TbmatDiagInds) = Tbdiags;
else
    TbSparseMat(TbmatDiagInds) = Tb(TbmatDiagInds); %Had do do it this way rather than with logical(sparse(Tb)) to get code to work with Tb being either a vector or matrix.
end
%% Perform the incoherent summation

SnumRows   = Ssz(1);
K          = full(sum(Wq(:,1)));
allScores  = abs(Wfherm*S).^2 * IR;
selectedCombinedScores  = FbSparseMat*allScores*TbSparseMat*Wq;
[~,I]      = max(selectedCombinedScores, [], 2);     %Check max on each row (frequency). This gives the columns of the resulting matrix output with the max for each frequency bin
%This and the next line gets the column numbers (time windows) of the S matrix where the highest K-summed entries exist for each row (frequency bin)
[Wqrows,~] = find(Wq(:,I));                         %Get the rows that had 1s in them that corresponded to the winning columns         
numOfSelectedWqElements = full(numel(Wqrows));
Scols      = reshape(Wqrows, K, numOfSelectedWqElements/K).';
Srows      = repmat((1:Wfhermsz(1)).', 1,K);
Sinds      = sub2ind(size(allScores), Srows, Scols);
Sscores    = allScores(Sinds);                   %Extract individual pulse scores

%The max function will just return the first index if all elements are
%equal. Here we zero out the scores and set the cols to NaN for frequencies
%were ignored with the frequency blinder matrix.
Sscores(~Fbdiags,:) = NaN;
Scols(~Fbdiags,:)   = NaN;


end

