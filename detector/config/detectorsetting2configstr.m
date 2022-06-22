function [outputStr] = detectorsetting2configstr(IDstr, freqMHz, ipData, portData, ipCntrl, portCntrl, centerFreq, Fs, tp, tip, tipu,tipj, K, focusMode, excldFreqs, falseAlarmProb, dataRecordPath, processedOuputPath, ros2enable)
%DETECTORCONFIGS2STR Ingests detector parameter specs and returns a string
%   in the proper the configuration file format, 
%
%INPUTS:
%   IDstr           String of identifier for the detector
%   freqMHz         Center frequeny in MHz incoming data to the detector
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
%                       frequencies are to be include input should be
%                       [Inf, -Inf]
%   falseAlarmProb      Desired false alarm probability as a decimal
%                       (not percentage)
%   dataRecordPath      Full path to the location to record the raw data.
%                       Pass an empty string ('') if no recording is
%                       needed.
%   processedOuputPath  Full path to the file containing processed results.
%   ros2enable      Boolean (true/false) to enable ros2 network
%                   publishing    
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

arguments
    IDstr       (1, 1) string {mustBeTextScalar}                = "01"
    freqMHz     (1, 1) double {mustBeNonnegative, mustBeReal}   = 150.000;
    ipData      (1, 1) string {mustBeTextScalar}                = "0.0.0.0"
    portData    (1, 1) double {mustBeReal, mustBePositive, mustBeInteger}           = 20000
    ipCntrl     (1, 1) string {mustBeTextScalar}                = "0.0.0.0"
    portCntrl   (1, 1) double {mustBeReal, mustBePositive, mustBeInteger}            = 30000
    centerFreq  (1, 1) double {mustBeReal}                      = 150000000
    Fs          (1, 1) double {mustBeReal, mustBePositive}      = 4000
    tp          (1, 1) double {mustBeReal, mustBePositive}      = 0.02
    tip         (1, 1) double {mustBeReal, mustBePositive}      = 1
    tipu        (1, 1) double {mustBeReal, mustBeNonnegative}   = 0
    tipj        (1, 1) double {mustBeReal, mustBeNonnegative}   = 0
    K           (1, 1) double {mustBeReal, mustBePositive, mustBeInteger} = 1
    focusMode   (1, 1) string {mustBeTextScalar}         = 'D'
    excldFreqs  (:, 2) double                            = [Inf, -Inf]
    falseAlarmProb      (1,1) double {mustBePostive, mustBeLessThan(falseAlarmProb,1)} = 0.01
    dataRecordPath      (1,1) string                    = ""
    processedOuputPath  (1,1) string                    = ""
    ros2enable          (1,1) logical                   = 'false'
end

currTime = posixtime(datetime('now'));
excldFreqsTrans = excldFreqs';
excldFreqsVec = excldFreqsTrans(:);
excldFreqStrPrint = '[';
for i = 1:2:numel(excldFreqsVec)-1
    excldFreqStrPrintNew = [num2str(excldFreqsVec(i)), ', ', num2str(excldFreqsVec(i+1))];
    excldFreqStrPrint = [excldFreqStrPrint, excldFreqStrPrintNew, '; '];
end
 excldFreqStrPrint = [excldFreqStrPrint(1:end-2), ']'];


 if ros2enable
     ros2enablestr = "true";
 elseif ~ros2enable
     ros2enablestr = "false";
 else
     error('UAV-RT: Unsupported ros2enable input. Must be a boolean')
 end

outputStr = sprintf('##################################################\ntimeStamp:\t%0.3f\nID:\t%s\nfreqMHz:%f\nipData:\t%s\nportData:\t%d\nipCntrl:\t%s\nportCntrl:\t%d\ncenterFreq:\t%0.6f \nFs:\t%0.3f\ntp:\t%0.6f\ntip:\t%0.6f\ntipu:\t%0.6f\ntipj:\t%0.6f\nK:\t%d\nfocusMode:\t%s\nexcldFreqs:\t%s\nfalseAlarmProb:\t%0.4f\ndataRecordPath:\t%s\nprocessedOuputPath:\t%s\ros2enable:\t%s\n',IDstr,freqMHz, currTime,ipData, portData, ipCntrl, portCntrl, centerFreq, Fs, tp, tip, tipu, tipj, K, focusMode, excldFreqStrPrint, falseAlarmProb, dataRecordPath, processedOuputPath, ros2enablestr);
end

