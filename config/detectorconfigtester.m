IDstr  = '01';
freqMHz = 150.000;
ipData = '0.0.0.0';
portData = 20000;
centerFreq = 150327000;
Fs = 6000;
tp = 0.02;
tip = 1.3;
tipu = 0.001;
K = 3;
focusMode = 'focus';
excldFreqs = [Inf -Inf];
falseAlarmProb = 0.001;
%decisionEntryPath  = '/Users/mshafer/Desktop/PLAYGROUND';
dataRecordPath = '/Users/mshafer/Desktop/PLAYGROUND';
processedOuputPath = '/Users/mshafer/Desktop/PLAYGROUND';


configPath = '/Users/mshafer/Desktop/PLAYGROUND/DETECTOR/CONFIGURATION';
configFileName = 'detectorConfig.txt';
if isunix
    folderSep = '/';
else
    folderSep = '\';
end
fullConfigPath = [configPath,folderSep,configFileName];

% configStr  = detectorsetting2configstr(ip, port, centerFreq, Fs, tp, tip, tipu, K, focusMode, excldFreqs, falseAlarmProb, decisionEntryPath, dataRecordPath, processedOuputPath);
% detectorconfigwrite(fullConfigPath, configStr, 'w')
% configStr  = detectorsetting2configstr(ip, port, centerFreq, Fs, tp, tip, tipu, K, focusMode, excldFreqs, falseAlarmProb, decisionEntryPath, dataRecordPath, processedOuputPath);
% detectorconfigwrite(fullConfigPath, configStr, 'a')

InitialDetector = DetectorConfig(IDstr, freqMHz, ipData, portData, centerFreq, Fs, tp, tip, tipu, K, focusMode, excldFreqs, falseAlarmProb, dataRecordPath, processedOuputPath);
InitialDetector.writeToFile(fullConfigPath,'a') 

%SecondDetector = DetectorConfig();
SecondDetector = DetectorConfig().setFromFile(fullConfigPath,5);



% configFileInfo = dir(fullConfigPath);
%    configFileSize = configFileInfo.bytes;
% 



