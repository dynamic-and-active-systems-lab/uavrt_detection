function [outputStr] = detectorsetting2configstr(ID, channelCenterFreqMHZ, ipData, portData, ipCntrl, portCntrl, Fs, tagFreqMHz, tp, tip, tipu,tipj, K, opMode, excldFreqs, falseAlarmProb, dataRecordPath, processedOuputPath, ros2enable, startInRunState)
%DETECTORCONFIGS2STR Ingests detector parameter specs and returns a string
%   in the proper the configuration file format, 
%
%INPUTS:
%   ID           String of identifier for the detector
%   Remaining arguments are the same as DetectorConfig class
%   
%
%OUTPUTS:
%   outputStr           A sting that can be saved to a detector 
%                       configuration file. 
%
%
%Author:    Michael W. Shafer
%Date:      2022-02-11
%
%--------------------------------------------------------------------------
%

currTime = posixtime(datetime('now'));
excldFreqsTrans = excldFreqs';
excldFreqsVec = excldFreqsTrans(:);
excldFreqStrPrint = '[';
for i = 1:2:numel(excldFreqsVec)-1
    excldFreqStrPrintNew = [num2str(excldFreqsVec(i)), ', ', num2str(excldFreqsVec(i+1))];
    excldFreqStrPrint = [excldFreqStrPrint, excldFreqStrPrintNew, '; '];
end
 excldFreqStrPrint = [excldFreqStrPrint(1:end-2), ']'];

outputStr = sprintf('##################################################\ntimeStamp:\t%0.3f\nID:\t%d\channelCenterFreqMHZ:%f\nipData:\t%s\nportData:\t%d\nipCntrl:\t%s\nportCntrl:\t%d\nFs:\t%0.3f\ntagFreqMHz:\t%0.6f\ntp:\t%0.6f\ntip:\t%0.6f\ntipu:\t%0.6f\ntipj:\t%0.6f\nK:\t%d\nopMode:\t%s\nexcldFreqs:\t%s\nfalseAlarmProb:\t%0.4f\ndataRecordPath:\t%s\nprocessedOuputPath:\t%s\nros2enable:\t%s\nstartInRunState:\t%s\n',uint32(ID),channelCenterFreqMHZ, currTime,ipData, portData, ipCntrl, portCntrl, Fs, tagFreqMHz, tp, tip, tipu, tipj, K, opMode, excldFreqStrPrint, falseAlarmProb, dataRecordPath, processedOuputPath, string(ros2enable), string(startInRunState));
end

