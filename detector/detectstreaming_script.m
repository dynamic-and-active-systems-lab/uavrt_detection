% DETECTSTEAMING_SCRIPT   Generate MEX-function detectsteaming_mex from
%  detectsteaming.
% 
% Script generated from project 'detectsteaming.prj' on 03-Jun-2022.
% 
% See also CODER, CODER.CONFIG, CODER.TYPEOF, CODEGEN.

%% Create configuration object of class 'coder.MexCodeConfig'.
cfg = coder.config('mex');
cfg.TargetLang = 'C++';
cfg.GenerateReport = true;
cfg.EnableJIT = true;
cfg.EnableJITSilentBailOut = true;

%% Invoke MATLAB Coder.
codegen -config cfg detectsteaming

