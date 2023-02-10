classdef pulseOut
    %PULSEOUT Class is used to format pulse information for transmission
    %as tunnel messages
    %   This class is different than the PULSE class which is used within
    %   the detectors. This class contains the information necessary for
    %   transmission as Mavlink Tunnel messages as specified within the
    %   Interface Control Document. It contains fields for the pulse
    %   information as well as the pose of the antenna at the moment of
    %   pulse reception. These pose fields may be set to NaN if not
    %   provided at the moment of property setting. 

    properties
        tag_id                      (1, 1) uint32
        detector_dir                (1, 1) string
        frequency                   (1, 1) double
        start_time_sec              (1, 1) int32
        start_time_nanosec          (1, 1) uint32
        end_time_sec                (1, 1) int32
        end_time_nanosec            (1, 1) uint32
        predict_next_start_sec      (1, 1) int32
        predict_next_start_nanosec  (1, 1) uint32 {mustBeNonnegative}
        predict_next_end_sec        (1, 1) int32
        predict_next_end_nanosec    (1, 1) uint32 {mustBeNonnegative}
        snr                         (1, 1) double
        stft_score                  (1, 1) double
        group_ind                   (1, 1) uint16
        group_snr                   (1, 1) double
        detection_status            (1, 1) logical
        confirmed_status            (1, 1) logical 

        pos_x                       (1, 1) double
        pos_y                       (1, 1) double
        pos_z                       (1, 1) double
        quat_x                      (1, 1) double
        quat_y                      (1, 1) double
        quat_z                      (1, 1) double
        quat_w                      (1, 1) double
    end

    methods
        function obj = pulseOut(detectorPulse, tagID, detectorDir, channelCenterFreq, groupInd, groupSNR, poseVect)
            %PULSEOUT Construct an instance of this class
            %   Detailed explanation goes here
            %
            %INPUTS:
            %   detectorPulse   1x1     pulse object instance (Not pulseOut
            %                           object)
            %   tagID           1x1     tag ID number from 0-65536
            %   detectorDir     1x1     string of the directory where
            %                           detector that found the pulse is 
            %                           running
            %   channelCenterFreq 1x1   Center frequency of channel where
            %                           pulse was found in MHz
            %   groundInd       1x1     Index of pulse in its group
            %   groupSNR        1x1     SNR of the pulse group to which
            %                           this pulse belongs
            %   poseVect        7x1     Vetor of pose information (optional
            %                           input) with position in [x, y, x,
            %                           quat_x, quat_y, quat_z, quat_w]
            %
            %OUTPUTS:
            %   pulseOut object instance
            %
            %

            if nargin > 0 %Inputs were provided

            obj.tag_id                     = uint32(tagID);
            obj.detector_dir               = detectorDir;%ID is a string
            obj.frequency                  = channelCenterFreq + (detectorPulse.fp)*1e-6;
                t_0     = detectorPulse.t_0;
                t_f     = detectorPulse.t_f;
                t_nxt_0 = detectorPulse.t_next(1);
                t_nxt_f = detectorPulse.t_next(2);
            obj.start_time_sec             = int32(floor(t_0));
            obj.start_time_nanosec         = uint32(mod(t_0,floor(t_0))*1e9);
            obj.end_time_sec               = int32(floor(t_f));
            obj.end_time_nanosec           = uint32(mod(t_f,floor(t_f))*1e9);
            obj.predict_next_start_sec     = int32(floor(t_nxt_0));
            obj.predict_next_start_nanosec = uint32(mod(t_nxt_0,floor(t_nxt_0))*1e9);
            obj.predict_next_end_sec       = int32(floor(t_nxt_f));
            obj.predict_next_end_nanosec   = uint32(mod(t_nxt_f,round(t_nxt_f))*1e9);
            obj.snr                        = detectorPulse.SNR;
            obj.stft_score                 = real(detectorPulse.yw);
            obj.group_ind                  = uint16(groupInd);
            obj.group_snr                  = groupSNR;
            obj.detection_status           = detectorPulse.det_dec;
            obj.confirmed_status           = detectorPulse.con_dec; 
            
            if ~isempty(poseVect) %Populate pose elements if provided
                obj.pos_x  = poseVect(1);
                obj.pos_y  = poseVect(2);
                obj.pos_z  = poseVect(3);
                obj.quat_x = poseVect(4);
                obj.quat_y = poseVect(5);
                obj.quat_z = poseVect(6);
                obj.quat_w = poseVect(7);
            end

            else %Build and empty object

            obj.tag_id                     = uint32(2);
            obj.detector_dir               = pwd;
            obj.frequency                  = 0;
            obj.start_time_sec             = int32(0);
            obj.start_time_nanosec         = uint32(0);
            obj.end_time_sec               = int32(0);
            obj.end_time_nanosec           = uint32(0);
            obj.predict_next_start_sec     = int32(0);
            obj.predict_next_start_nanosec = uint32(0);
            obj.predict_next_end_sec       = int32(0);
            obj.predict_next_end_nanosec   = uint32(0);
            obj.snr                        = 0;
            obj.stft_score                 = 0;
            obj.group_ind                  = uint16(0);
            obj.group_snr                  = 0;
            obj.detection_status           = false;
            obj.confirmed_status           = false;

            obj.pos_x  = NaN;
            obj.pos_y  = NaN;
            obj.pos_z  = NaN;
            obj.quat_x = NaN;
            obj.quat_y = NaN;
            obj.quat_z = NaN;
            obj.quat_w = NaN;

            end
        end

        function [obj, target_system, target_component, payload_type, payload_length] = setFromTunnelMsg(obj, tunnelMsg)
            %SETFROMTUNNELMESSAGE Sets the pulse properties based on the tunnel
            %message, effectively decoding the mavlink message
            %INPUTS:
            %   obj         1x1     pulseOut object to set
            %   tunnelMsg   nx1     formatted Tunnel Message of 66 or 122
            %                       uint8 formatted bytes.
            %
            %OUTPUTS:
            %   obj         1x1     pulseOut instance with properties set
            %   target_system       1x1 Target system from Tunnel Message
            %   target_component    1x1 Target component from Tunnel Message
            %   payload_type        1x1 Payload type from Tunnel Message
            %   payload_length      1x1 Payload length from Tunnel Message
            %
            %

            
            if numel(tunnelMsg) ~= 66 || numel(tunnelMsg) ~= 122
                warning('UAV-RT: Sub packet Tunnel Message detected. Returning unset pulseOut object. Input message must be 66 or 122 bytes. ')
            else
                target_system_bytes                 = 1;
                target_component_bytes              = 2;
                payload_type_bytes                  = 3:4;
                payload_length_bytes                = 5;
                id_bytes                            = 6:9;
                freq_bytes                          = 10:17;
                start_time_sec_bytes                = 18:21;
                start_time_nanosec_bytes            = 22:25;
                predict_next_start_sec_bytes        = 26:29;
                predict_next_start_nanosec_bytes    = 30:33;
                snr_bytes                           = 34:41;
                stft_score_bytes                    = 41:48;
                group_ind_bytes                     = 49:56;
                group_snr_bytes                     = 57:64;
                detection_status_bytes              = 65;
                confirmed_status_bytes              = 66;
                pos_x_bytes                         = 67:74;
                pos_y_bytes                         = 75:82;
                pos_z_bytes                         = 83:90;
                quat_x_bytes                        = 91:98;
                quat_y_bytes                        = 99:106;
                quat_z_bytes                        = 107:114;
                quat_w_bytes                        = 115:122;


                target_system = typecast(tunnelMsg(target_system_bytes),'uint8');
                target_component = typecast(tunnelMsg(target_component_bytes),'uint8');
                payload_type = typecast(tunnelMsg(payload_type_bytes),'uint16');
                payload_length = typecast(tunnelMsg(payload_length_bytes),'uint8');

                obj.tag_id = typecast(tunnelMsg(id_bytes),'uint32');
                obj.frequency = typecast(tunnelMsg(freq_bytes),'double');
                obj.start_time_sec = typecast(tunnelMsg(start_time_sec_bytes),'int32');
                obj.start_time_nanosec = typecast(tunnelMsg(start_time_nanosec_bytes),'uint32');
                obj.predict_next_start_sec = typecast(tunnelMsg(predict_next_start_sec_bytes),'int32');
                obj.predict_next_start_nanosec = typecast(tunnelMsg(predict_next_start_nanosec_bytes),'uint32');
                obj.snr = typecast(tunnelMsg(snr_bytes),'double');
                obj.stft_score = typecast(tunnelMsg(stft_score_bytes),'double');
                obj.group_ind = typecast(tunnelMsg(group_ind_bytes),'int16');
                obj.group_snr = typecast(tunnelMsg(group_snr_bytes),'double');
                obj.detection_status = typecast(tunnelMsg(detection_status_bytes),'uint8');
                obj.confirmed_status = typecast(tunnelMsg(confirmed_status_bytes),'uint8');
                if numel(tunnelMsg) > 66
                    obj.pos_x = typecast(tunnelMsg(pos_x_bytes),'double');
                    obj.pos_y = typecast(tunnelMsg(pos_y_bytes),'double');
                    obj.pos_z = typecast(tunnelMsg(pos_z_bytes),'double');
                    obj.quat_x = typecast(tunnelMsg(quat_x_bytes),'double');
                    obj.quat_y = typecast(tunnelMsg(quat_y_bytes),'double');
                    obj.quat_z = typecast(tunnelMsg(quat_z_bytes),'double');
                    obj.quat_w = typecast(tunnelMsg(quat_w_bytes),'double');
                else
                    obj.pos_x  = NaN;
                    obj.pos_y  = NaN;
                    obj.pos_z  = NaN;
                    obj.quat_x = NaN;
                    obj.quat_y = NaN;
                    obj.quat_z = NaN;
                    obj.quat_w = NaN;
                end
            end

        end


        function [mavlinkTunnelMsgUint8] = formatForTunnelMsg(obj, target_system_in, target_component_in, payload_type_in)
            %FORMATFORTUNNELMSG prepares the uint8 formatted Tunnel message
            %for transmission as a mavlink message. 
            %
            %INPUTS:
            %   obj         1x1     pulseOut object to be formatted
            %   target_system_in        1x1     scalar 0-255
            %   target_component_in     1x1     scalar 0-255
            %   payload_type            1x1     scalar 0-65535
            %
            %OUTPUTS:
            %   mavlinkTunnelMsgUint8  nx1 output vector of uint8s

            
            %Build PulsePose Mavlink Tunnel Message Payload
            %Typecast maintains little-endian, in line
            %with the mavlink serialization standard: https://mavlink.io/en/guide/serialization.html
            target_system        = dec2hex(typecast(uint8(  target_system_in               ),'uint8'), 2);  %uint8
            target_component     = dec2hex(typecast(uint8(  target_component_in            ),'uint8'), 2);  %uint8
            payload_type         = dec2hex(typecast(uint16( payload_type_in                ),'uint8'), 2);  %uint16
            id                   = dec2hex(typecast(uint32( obj.tag_id                     ),'uint8'), 2);  %uint32
            freq                 = dec2hex(typecast(double( obj.frequency                  ),'uint8'), 2);  %uint32
            start_time_sec       = dec2hex(typecast(int32(  obj.start_time_sec             ),'uint8'), 2);  %int32
            start_time_nanosec   = dec2hex(typecast(uint32( obj.start_time_nanosec         ),'uint8'), 2);  %uint32
            predict_next_sec     = dec2hex(typecast(int32(  obj.predict_next_start_sec     ),'uint8'), 2);  %int32
            predict_next_nanosec = dec2hex(typecast(uint32( obj.predict_next_start_nanosec ),'uint8'), 2);  %uint32
            snr                  = dec2hex(typecast(double( obj.snr                        ),'uint8'), 2);  %double
            stft_score           = dec2hex(typecast(double( obj.stft_score                 ),'uint8'), 2);  %double
            group_ind            = dec2hex(typecast(uint16( obj.group_ind                  ),'uint8'), 2);  %uint16
            detection_status     = dec2hex(typecast(uint8(  obj.detection_status           ),'uint8'), 2);  %uint8
            confirmed_status     = dec2hex(typecast(uint8(  obj.confirmed_status           ),'uint8'), 2);  %uint8

            payload_hex = [id; freq; start_time_sec; start_time_nanosec; ...
                           predict_next_sec; predict_next_nanosec; snr; ...
                           stft_score; group_ind; detection_status; ...
                           confirmed_status];

            payload_length = dec2hex(typecast(uint8(size(payload_hex,1)),'uint8'),2);

            mavlinkTunnelMsgHex = [target_system; target_component; ...
                                   payload_type; payload_length;...
                                   payload_hex];

            mavlinkTunnelMsgUint8 = uint8( hex2dec( mavlinkTunnelMsgHex ) );
        end
    end
end