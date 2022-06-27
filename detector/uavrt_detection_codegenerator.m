%To create a startup to add CMake to path run this line and then add the
%code below to that startup.m scripte
%edit(fullfile(userpath,'startup.m'))
% % %To add CMake Directory to PATH
% % %Based on answer from https://www.mathworks.com/matlabcentral/answers/1461834-why-do-i-get-the-error-could-not-find-cmake-in-your-system-when-using-rosgenmsg
% % oldPath = getenv('PATH');
% % %newPath = strcat(oldPath, pathsep, 'C:\Program Files\CMake\bin'); % on Windows
% % newPath = strcat(oldPath, pathsep, '/Applications/CMake.app/Contents/bin'); % on Mac
% % setenv('PATH', newPath);
% % %system('cmake --version')
% % clear

%pyenv('Version','/usr/local/opt/python@3.9/bin/python3.9')

clear

%% Remote ROS2 BUILDING
cfg = coder.config('exe');
cfg.Hardware = coder.hardware('Robot Operating System 2 (ROS 2)');
%cfg.Hardware.BuildAction = 'Build and run';
cfg.Hardware.BuildAction = 'Build and load';
cfg.Hardware.RemoteDeviceAddress = '134.114.16.153';
cfg.Hardware.RemoteDeviceUsername = 'dasl';
cfg.Hardware.RemoteDevicePassword = 'dasl249!';
cfg.Hardware.DeployTo = 'Remote Device';
cfg.Hardware.ROS2Folder = '/opt/ros/galactic';
cfg.Hardware.ROS2Workspace = '~/uavrt_ws';
cfg.HardwareImplementation.ProdHWDeviceType = 'Intel->x86-64 (Linux 64)';
codegen uavrt_detection -args {} -config cfg

% cfg.RuntimeChecks = true;%Disable for final deployments.
% cfg.Hardware.ROS2Workspace = '~/detector_debug_ws';
% codegen detectstreaming_debug -args {} -config cfg

%% Local ROS2 BUILDING
cfg = coder.config('exe');
cfg.Hardware = coder.hardware('Robot Operating System 2 (ROS 2)');
cfg.Hardware.DeployTo = 'Localhost';
cfg.Hardware.BuildAction = 'Build and run';
codegen detectstreaming -args {} -config cfg

%% Local ROS2 BUILDING to uavrt_ws workspace
cfg = coder.config('exe');
cfg.Hardware = coder.hardware('Robot Operating System 2 (ROS 2)');
cfg.Hardware.DeployTo = 'Localhost';
cfg.Hardware.ROS2Folder = '/opt/ros/galactic';
cfg.Hardware.ROS2Workspace = '~/uavrt_ws';
cfg.Hardware.BuildAction = 'Build and load';
codegen detectstreaming -args {} -config cfg

%% LOCAL EXE Build (for non-ROS2 testing)
cfg = coder.config('exe');
cfg.TargetLang = 'C++';
cfg.GenerateReport = true;
cfg.MaxIdLength = 1024;
cfg.ReportPotentialDifferences = false;
cfg.GenerateExampleMain = 'GenerateCodeAndCompile';
cfg.RuntimeChecks = true;
codegen detectstreaming -args {} -config cfg

codegen -report detectstreaming -args {}
