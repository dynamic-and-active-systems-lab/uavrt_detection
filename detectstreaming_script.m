% DETECTSTREAMING_SCRIPT   Generate executable detectstreaming from
%  detectstreaming.
% 
% Script generated from project 'detectstreaming.prj' on 14-Jun-2022.
% 
% See also CODER, CODER.CONFIG, CODER.TYPEOF, CODEGEN.

%% Create configuration object of class 'coder.CodeConfig'.
cfg = coder.config('exe','ecoder',false);
cfg.TargetLang = 'C++';
cfg.GenerateExampleMain = 'GenerateCodeAndCompile';
cfg.GenerateReport = true;
cfg.MaxIdLength = 1024;
cfg.ReportPotentialDifferences = false;

%% Invoke MATLAB Coder.
cd('/Users/mshafer/Desktop/PLAYGROUND/CODE_TOEPLITZ/uavrt_detection/detector');
codegen -config cfg detectstreaming

