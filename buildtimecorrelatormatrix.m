function [Wq] = buildtimecorrelatormatrix(pri, priUncert, priJtr, reps)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

%First check to make sure all inputs contain the same number of
%elements
numelOfInputsVec = [numel(pri),...
    numel(priUncert),...
    numel(priJtr),...
    numel(reps)];
if any(numelOfInputsVec~=1) %numel(unique(numelOfInputsVec))~=1
    error('UAV-RT: All inputs must have the one element')
end

priMeansList = zeros(1,2*priUncert+1);
priJtrList   = zeros(1,2*priJtr+1);

    %Change names to align with other code.
    N = pri;
    M = priUncert;
    J = priJtr;
    K = reps;
    
    priMeansList(:)   = N+(-M:M);
    priJtrList(:)     = -J:J;


Wq = assembleWq(priMeansList(:), priJtrList(:), K);%, obj.reps(i));

end

