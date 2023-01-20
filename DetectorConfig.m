classdef DetectorConfig 
    %DETECTORCONFIG Class contains the information needed by the detector
    %to process a channel of radio data. 
    %
    %PROPERTIES
    %   ID              A string identifier for the detector
    %   channelCenterFreqMHZ    Center frequency of incoming data stream in MHz
    %   ipData          String ip from which to receive data. Enter
    %                   '0.0.0.0' to receive from any IP.
    %   portData        Port from which to receive data
    %   ipCntrl         String ip from which to receive control inputs. 
    %                   Enter '0.0.0.0' to receive from any IP.
    %   portCntrl       Port from which to receive control inputs
    %   Fs              Sample rate of incoming data
    %   tagFreqMHz      Expected frequency of tag
    %   tp              Duration of pulse in seconds
    %   tip             Interpulse duration in seconds
    %   tipu            Interpulse duration uncertainty in seconds
    %   tipj            Interpulse duration jitter in seconds
    %   K               Number of pulses to integrate
    %   opMode          Operational mode for processing:
    %                       freqSearchHardLock
    %                       freqSearchSoftLock
    %                       freqKnownHardLock
    %                       freqAllNeverLock
    %   excldFreqs      [nx2] matrix of frequency bands to exclude
    %   falsAlarmProb   False alarm probability
    %   decisionEntryPath   Path to decision entry
    %   decisionEntry       The decision entry (theshold_database object)
    %                       contained in the decisionEntryPath file. This
    %                       gets loaded from the decisionEntryPath. 
    %   dataRecordPath      Path to location to which record the
    %                       data
    %   processedOuputPath  Path to location to save processed
    %                       results.
    %   ros2enable          Turn on or off ROS2 suppport (True or False)
    %   startInRunState     Start detector in run state (True or False)
    %
    %METHODS:
    %DetectorConfig     Constructor of this class
    %setFromFile        Sets the properties of an instance from a file
    %writeToFile        Writes the instance to a file
    %copy               Creates a copy of an instance
    %
    %Author:    Michael W. Shafer
    %Date:      2022-02-14
    %----------------------------------------------------------------------
    
    properties
        ID          (1, 1) string {mustBeTextScalar}                          = "01"; 
        channelCenterFreqMHz     (1, 1) double {mustBeNonnegative, mustBeReal}             = 150.000;
        ipData      (1, 1) string {mustBeTextScalar}                          = "0.0.0.0"
        portData    (1, 1) double {mustBeReal, mustBePositive, mustBeInteger} = 1
        ipCntrl     (1, 1) string {mustBeTextScalar}                          = "0.0.0.0"
        portCntrl   (1, 1) double {mustBeReal, mustBePositive, mustBeInteger} = 1     
        Fs          (1, 1) double {mustBeReal, mustBePositive}                = 192000
        tagFreqMHz  (1, 1) double {mustBeReal}                                = 150.000;
        tp 	        (1, 1) double {mustBeReal, mustBePositive}                = 0.02
        tip         (1, 1) double {mustBeReal, mustBePositive}                = 1
        tipu        (1, 1) double {mustBeReal, mustBeNonnegative}             = 0
        tipj        (1, 1) double {mustBeReal, mustBeNonnegative}             = 0
        K           (1, 1) double {mustBeReal, mustBePositive, mustBeInteger} = 1
        opMode      (1, 1) string {mustBeTextScalar}                          = 'freqSearchHardLock'
        excldFreqs  (:, 2) double {mustBeReal}                                = [inf, -inf]
        falseAlarmProb(1,1) double {mustBePositive, mustBeLessThan(falseAlarmProb,1)} = 0.01
        dataRecordPath(1,1) string                                            = ''
        processedOuputPath(1,1) string                                        = ''
        ros2enable  (1,1) logical                                             = false
        startInRunState (1,1) logical                                         = false
    end
    
    methods
        function obj = DetectorConfig(IDstr, channelCenterFreqMHZ, ipData, portData, ipCntrl, portCntrl, Fs, tagFreqMHz, tp, tip, tipu, K, opMode, excldFreqs, falseAlarmProb, decisionEntryPath, dataRecordPath, processedOuputPath, ros2enable, startInRunState)
            if nargin>0
                obj.ID          = IDstr;
                obj.channelCenterFreqMHz     = channelCenterFreqMHZ;
                obj.ipData      = ipData;
                obj.portData    = portData;
                obj.ipCntrl     = ipCntrl;
                obj.portCntrl   = portCntrl;               
                obj.Fs          = Fs;
                obj.tagFreqMHz  = tagFreqMHz;
                obj.tp          = tp;
                obj.tip         = tip;
                obj.tipu        = tipu;
                obj.tipj        = tipj;
                obj.K           = K;
                obj.opMode           = opMode;
                obj.excldFreqs          = excldFreqs;
                obj.falseAlarmProb      = falseAlarmProb;
                obj.dataRecordPath      = dataRecordPath;
                obj.processedOuputPath  = processedOuputPath;
                obj.ros2enable          = ros2enable;
                obj.startInRunState     = startInRunState;
            end
        end
        
        function [obj] = setFromFile(obj,filePath,entry)
            %fillFromFile Replaces the properties of the instance passed to
            %it with the values specified in the configuration file passed
            %to the function. If multiple entries exist in the config file,
            %use the 'entry' argument to specify which entry to use (1-n).
            %If entry is not specified, the method will use the last entry
            %in the config file. 
            %
            %INPUTS:
            %   filePath        String of full path to config file, 
            %                   including the file name and extension
            %                   
            %   entry           Scalar number (1-n) of which entry to use.
            %                   Method will use the last entry if entry is
            %                   not provided. Alternatively, enter -1 to 
            %                   use last entry.
            %
            %OUTPUTS:
            %   none (method modifies the properties of the instance)
            %
            %
            fid = fopen(filePath);
            
            if fid == -1
                fprintf("UAV-RT: Error opening configurationfile file with error. Attempted to find config file at the location %s:\n", filePath)
            end

            configNum = 0;
            done = false;
            %coder.varsize('sepLine')
            coder.varsize('sepByte')
            sepByte = 0;
            lineNum = 1;
            %First figure out where the separator lines are
            while ~done
                %currByte = ftell(fid);
                rawLine = fgetl(fid);
                
                if rawLine(1)=='#' %&& lineNum~=1
                    if configNum == 0
                        sepByte = ftell(fid);
                    else
                        %sepByte(configNum) = ftell(fid);
                        sepByte = [sepByte, ftell(fid)];%Modified for Coder compatibility
                    end
                    configNum = configNum + 1;
                end
                lineNum = lineNum+1;
                done = (feof(fid) == 1);
            end
            %sepByte(configNum) = ftell(fid);
            sepByte = [sepByte, ftell(fid)];%Modified for Coder compatibility
            
            if nargin == 2
                entry = configNum;
            end
            
            if entry == -1
                entry = configNum;
            end
            
            if entry > configNum
                if coder.target('Matlab')
                    warning('UAV-RT: Requested config entry higher than available. Defaulting to last configuration in file.')
                end
                entry = configNum;
            end
            
            %Jump to the line for the entry requested
            fseek(fid,sepByte(entry),'bof');
            done = false;
            while ~done
                lineStr = fgetl(fid);
                if lineStr(1)~='#'
                    colonLocation   = find(lineStr == ':',1,'first');%note regexp is not supported for code generation
                    tabLocs         = strfind(lineStr,sprintf('\t')); %Thanks to https://www.mathworks.com/matlabcentral/answers/529668-how-do-i-detect-a-tab-character-in-a-line-of-text-read-by-fgetl
                    firstConfigCharLocation = tabLocs(1)+1;%note regexp is not supported for code generation
                    configType      = lineStr(1:colonLocation(1)-1);
                    configValStr    = lineStr(firstConfigCharLocation(1):end);
                    
                    if strcmp(configType,'ID')
                        obj.ID      = configValStr;
                    elseif strcmp(configType,'channelCenterFreqMHz')
                        obj.channelCenterFreqMHz  = real(str2double(configValStr));
                    elseif strcmp(configType,'ipData')
                        obj.ipData  = configValStr;
                    elseif strcmp(configType,'portData')
                        obj.portData    = uint16(real(str2double(configValStr)));
                    elseif strcmp(configType,'ipCntrl')
                        obj.ipCntrl = configValStr;
                    elseif strcmp(configType,'portCntrl')
                        obj.portCntrl   = uint16(real(str2double(configValStr)));    
                    elseif strcmp(configType,'Fs')
                        obj.Fs      = real(str2double(configValStr));
                    elseif strcmp(configType,'tagFreqMHz')
                        obj.tagFreqMHz  = real(str2double(configValStr));
                    elseif strcmp(configType,'tp')
                        obj.tp      = real(str2double(configValStr));
                    elseif strcmp(configType,'tip')
                        obj.tip     = real(str2double(configValStr));
                    elseif strcmp(configType,'tipu')
                        obj.tipu    = real(str2double(configValStr));
                    elseif strcmp(configType,'tipj')
                        obj.tipj    = real(str2double(configValStr));
                    elseif strcmp(configType,'K')
                        obj.K       = uint8(real(str2double(configValStr)));
                    elseif strcmp(configType,'opMode')
                        obj.opMode =  configValStr;
                    elseif strcmp(configType,'excldFreqs')
                        obj.excldFreqs =  real(str2matrix(configValStr));
                    elseif strcmp(configType,'falseAlarmProb')
                        obj.falseAlarmProb = real(str2double(configValStr));
                    elseif strcmp(configType,'dataRecordPath')
                        obj.dataRecordPath = configValStr;
                    elseif strcmp(configType,'processedOuputPath')
                        obj.processedOuputPath =  configValStr;
                    elseif strcmp(configType,'ros2enable')
                        obj.ros2enable =  str2bool(configValStr);
                    elseif strcmp(configType,'startInRunState')
                        obj.startInRunState =  str2bool(configValStr);
                    end
                    %Stop when we have finished reading this entry.
                    done = (feof(fid) == 1) || (ftell(fid)==sepByte(entry+1)) ;
                else 
                    done = (feof(fid) == 1) || (ftell(fid)==sepByte(entry+1)) ;
                end
            end
            fclose(fid);
        end
        
        function [] = writeToFile(obj,fullConfigPath,writeType) 
            %writeToFiles Writes the detector configuration of the 
            %object passed to it to the path passed.
            %
            %INPUTS:
            %   configPath      String of full path to config file, 
            %                   including the file name and extension
            %                   
            %   configStr       String for writing into the config file.
            %   writeType       Char of either 'a' to append to existing 
            %                   file or 'w' to write. 'w' will overwrite 
            %                   file if it already exists.
            %
            %OUTPUTS:
            %   none
            configStr  = detectorsetting2configstr(obj.ID, obj.channelCenterFreqMHz, ...
                                                   obj.ipData, obj.portData, ...
                                                   obj.ipCntrl, obj.portCntrl, ...
                                                   obj.Fs, obj.tagFreqMHz, ...
                                                   obj.tp, obj.tip, ...
                                                   obj.tipu,obj.tipj,...
                                                   obj.K, obj.opMode,...
                                                   obj.excldFreqs,...
                                                   obj.falseAlarmProb,...
                                                   obj.dataRecordPath, ...
                                                   obj.processedOuputPath,...
                                                   obj.ros2enable,...
                                                   obj.startInRunState);
                                                   
            detectorconfigwrite(fullConfigPath, configStr, writeType)
        end
        function objOut = copy(obj)
            %Creates a copy of the instance passed to the function. Keep in
            %mind that the dector ID also gets cancelled. The caller should
            %reset the property after the copy completes.
            objOut = DetectorConfig();
            objOut.ID          = obj.ID;
            objOut.channelCenterFreqMHz     = obj.channelCenterFreqMHz;
            objOut.ipData      = obj.ipData;
            objOut.portData    = obj.portData;
            objOut.ipCntrl     = obj.ipCntrl;
            objOut.portCntrl   = obj.portCntrl;
            objOut.Fs          = obj.Fs;
            objOut.tagFreqMHz  = obj.tagFreqMHz;
            objOut.tp          = obj.tp;
            objOut.tip         = obj.tip;
            objOut.tipu        = obj.tipu;
            objOut.tipj        = obj.tipj;
            objOut.K           = obj.K;
            objOut.opMode      = obj.opMode;
            objOut.excldFreqs          = obj.excldFreqs;
            objOut.falseAlarmProb      = obj.falseAlarmProb;
            objOut.dataRecordPath      = obj.dataRecordPath;
            objOut.processedOuputPath  = obj.processedOuputPath;
            objOut.ros2enable          = obj.ros2enable;
            objOut.startInRunState     = obj.startInRunState;
        end
    end
end


