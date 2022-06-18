function [outputStr] = detectorsetting2configstr(ipData, portData, ipCntrl, portCntrl, centerFreq, Fs, tp, tip, tipu,tipj, K, focusMode, excldFreqs, falseAlarmProb, decisionEntryPath, dataRecordPath, processedOuputPath)
%DETECTORCONFIGS2STR Ingests detector parameter specs and returns a string
%   in the proper the configuration file format, 
%
%INPUTS:
%   ipData          String ip from which to receive data. Enter
%                   '0.0.0.0' to receive from any IP.
%   portData        Port from which to receive data
%   ipCntrl         String ip from which to receive control inputs.
%                   Enter '0.0.0.0' to receive from any IP.
%   portCntrl       Port from which to receive control inputs
%	centerFreq          Center frequency of the incoming data (scalar)
%   Fs                  Sample rate of incoming data (scalar)
%   tp                  Expected pulse duration in seconds (scalar)
%   tip                 Expected interp-pulse time in seconds (scalar)
%   tipu                Uncertainty of interp-pulse time in seconds (scalar)
%   tipj                Interp-pulse jitter time in seconds (scalar)
%   K                   Number of pulses to integrate 
%   focusMode           Focus mode for processing ('focus' or 'open')
%   excldFreqs          nx2 matrix of excluded frequecy bands. If all
%                       frequencies are to be include
%   falseAlarmProb      Desired false alarm probability as a decimal
%                       (not percentage)
%   decisionEntryPath   Full path to the decision entry for threshold
%   dataRecordPath      Full path to the location to record the raw data.
%                       Pass an empty string ('') if no recording is
%                       needed.
%   processedOuputPath  Full path to the file containing processed results.
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
 

outputStr = sprintf('##################################################\ntimeStamp:\t%0.3f\nipData:\t%s\nportData:\t%d\nipCntrl:\t%s\nportCntrl:\t%d\ncenterFreq:\t%0.6f \nFs:\t%0.3f\ntp:\t%0.6f\ntip:\t%0.6f\ntipu:\t%0.6f\ntipj:\t%0.6f\nK:\t%d\nfocusMode:\t%s\nexcldFreqs:\t%s\nfalseAlarmProb:\t%0.4f\ndecisionEntryPath:\t%s\ndataRecordPath:\t%s\nprocessedOuputPath:\t%s\n',currTime,ipData,portData,ipCntrl,portCntrl,centerFreq,Fs,tp,tip,tipu,tipj,K,focusMode,excldFreqStrPrint,falseAlarmProb,decisionEntryPath,dataRecordPath,processedOuputPath);
end

