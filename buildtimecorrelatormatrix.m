function [Wq] = buildtimecorrelatormatrix(pri, priUncert, priJtr, reps)
%BUILDTIMECORRELATIONMATRIX Assembles the time correlation matrix that is
%used in the incoherent summation step.
%INPUTS:
%   pri         Pulse repetition interval in stft time windows (N)
%   priUncert   Pulse repetition interval uncertainty in stft time windows
%               (M)
%   priJtr      Pulse repetition interval jitter in stft time windows (J)
%   reps        Pulse repetitions to consider (K)

arguments
    pri         (1,1)   double  { mustBeGreaterThanOrEqual(pri, 0)}
    priUncert   (1,1)   double  { mustBeGreaterThanOrEqual(priUncert, 0)}
    priJtr      (1,1)   double  { mustBeGreaterThanOrEqual(priJtr, 0)}
    reps        (1,1)   double  { mustBeGreaterThanOrEqual(reps, 1)}
end


%First check to make sure all inputs contain the same number of
%elements
numelOfInputsVec = [numel(pri),...
    numel(priUncert),...
    numel(priJtr),...
    numel(reps)];

if any(numelOfInputsVec ~= 1)
    error('UAV-RT: All inputs must have the one element')
end

priMeansList = zeros(1, 2 * priUncert + 1);

priJtrList   = zeros(1, 2 * priJtr + 1);

%Change names to align with other code.
N = pri;
M = priUncert;
J = priJtr;
K = reps;

priMeansList(:)   = N + ( -M : M );

priJtrList(:)     = -J : J;

Wq = assembleWq(priMeansList(:), priJtrList(:), K);

end

