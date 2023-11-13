function [thresh] = evthresh(mu,sigma,pf)
%EVTHRESH computs a threshold value based on the parameters of an extreme
%value distribution and a desired false alarm probability
%
%INPUTS:
%   mu      scalar location parameter of the EV distribution
%   sigma   scalar scale parameter of the EV distribution
%   pf      scalar probability of false alarm desired

%OUPUTS:
%   thresh  scalar value of the threshold
%--------------------------------------------------------------------------

arguments
    mu    (1,1) double {mustBeReal}
    sigma (1,1) double {mustBeReal, mustBePositive}
    pf    (1,1) double {mustBeReal, mustBeGreaterThanOrEqual(pf,0)}
end

%Equivalent to 1-evcdf(x,mu,sigma)-pf
theFunc  = @(x) 1-exp(-exp((-x-mu)/sigma))-pf;

%theFunc monitonically decrease, so starting at x = 0 should always converge
thresh   = fzero(theFunc,0);

end