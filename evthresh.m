function [thresh] = evthresh(mu,sigma,pf)


%theFunc = @(x) 1-exp(-exp((x-mu)/sigma));%Equivalent to evcdf(x,mu,sigma)
%theFunc = @(x) exp(-exp((x-mu)/sigma));%Equivalent to 1-evcdf(x,mu,sigma)
theFunc  = @(x) 1-exp(-exp((-x-mu)/sigma))-pf;%Equivalent to 1-evcdf(x,mu,sigma)-pf
thresh   = fzero(theFunc,0);%theFunc monitonically decrease, so starting at x = 0 should always converge
end