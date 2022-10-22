% BUILDDONUDPARMCODER   Generate executable uavrt_detection from
%  uavrt_detection.
% 
% Script generated from project 'uavrt_detection.prj' on 22-Oct-2022.
% 
% See also CODER, CODER.CONFIG, CODER.TYPEOF, CODEGEN.

%% Create configuration object of class 'coder.EmbeddedCodeConfig'.
cfg = coder.config('exe','ecoder',true);
cfg.TargetLang = 'C++';
cfg.GenCodeOnly = true;
cfg.GenerateExampleMain = 'GenerateCodeAndCompile';
cfg.GenerateReport = true;
cfg.MaxIdLength = 1024;
cfg.ReportPotentialDifferences = false;

%% Invoke MATLAB Coder.
codegen -config cfg uavrt_detection

