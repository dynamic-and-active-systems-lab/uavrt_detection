% UAVRT_DETECTION_CODEGEN_NO_ROS_SCRIPT   Generate executable uavrt_detection
%  from uavrt_detection.
% 
% Script generated from project 'uavrt_detection.prj' on 24-Feb-2023.
% 
% See also CODER, CODER.CONFIG, CODER.TYPEOF, CODEGEN.

%% Create configuration object of class 'coder.EmbeddedCodeConfig'.
cfg = coder.config('exe','ecoder',true);
cfg.HardwareImplementation.ProdEqTarget = false;
cfg.TargetLang = 'C++';
cfg.GenCodeOnly = true;
cfg.GenerateExampleMain = 'DoNotGenerate';
cfg.GenerateMakefile = false;
cfg.GenerateReport = false;
cfg.MaxIdLength = 1024;
cfg.ReportPotentialDifferences = false;
cfg.TargetLangStandard = 'C++11 (ISO)';
cfg.RuntimeChecks = true;

%% Define argument types for entry-point 'uavrt_detection'.
ARGS = cell(1,1);
ARGS{1} = cell(1,1);
ARGS{1}{1} = coder.typeof('X',[1 Inf],[0 1]);

%% Invoke MATLAB Coder.
codegen -config cfg uavrt_detection -args ARGS{1}

