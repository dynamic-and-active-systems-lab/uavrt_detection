% DETECTSTREAMING_SCRIPT4   Generate executable detectstreaming from
%  detectstreaming.
% 
% Script generated from project 'detectstreaming.prj' on 06-Jun-2022.
% 
% See also CODER, CODER.CONFIG, CODER.TYPEOF, CODEGEN.

%% Create configuration object of class 'coder.CodeConfig'.
cfg = coder.config('exe','ecoder',false);
cfg.TargetLang = 'C++';
cfg.GenerateReport = true;
cfg.MaxIdLength = 1024;
cfg.ReportPotentialDifferences = false;
cfg.GenerateExampleMain = 'GenerateCodeAndCompile';

%% Invoke MATLAB Coder.
codegen -config cfg detectstreaming

