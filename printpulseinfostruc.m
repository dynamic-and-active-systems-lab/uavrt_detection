function [] = printpulseinfostruc(pulseInfoStruct)
%PRINTPULSEINFOSTRUC Prints the pulse struct to the terminal
%
%INPUTS:
%   pulseInfoStruct A pulse structure generated by makepulsestruc.m
%
%OUTPUTS:
%   none other than prints to terminal
%
%
%--------------------------------------------------------------------------


tag_id_fspec            = '%u'; %uint32(Config.ID);
freq_Hz_fspec           = '%u'; % uint32((Config.channelCenterFreqMHz * 1e6) + detectorPulse.fp);
start_time_fspec        = '%.3f';% detectorPulse.t_0;
next_time_fspec         = '%.3f';%detectorPulse.t_next(1);
snr_fspec               = '%g';% detectorPulse.SNR;
stft_score_fspec        = '%g';%real(detectorPulse.yw);
group_seq_count_fspec   = '%u';%groupSeqCounter;
group_ind_fspec         = '%u';%uint16(j);
group_snr_fspec         = '%g';%groupSNR;
noise_psd_fspec         = '%g';%real(detectorPulse.yw ) * dt^2 / T * (1 + 10^(detectorPulse.SNR/10))^(-1); %See Notebook Entry 2023-07-07 for derivation
det_status_fspec        = '%u';% uint8(detectorPulse.det_dec);
con_status_fspec        = '%u';%uint8(detectorPulse.con_dec);

delimiter = ', ';

total_fspec = [ tag_id_fspec, delimiter, ...
                freq_Hz_fspec,delimiter, ...
                start_time_fspec, delimiter, ...
                next_time_fspec, delimiter, ...
                snr_fspec, delimiter, ...
                stft_score_fspec , delimiter, ...
                group_seq_count_fspec, delimiter, ...
                group_ind_fspec, delimiter, ...
                group_snr_fspec, delimiter, ...
                noise_psd_fspec, delimiter, ...
                det_status_fspec, delimiter, ...
                con_status_fspec, '\n'];


fprintf(total_fspec,uint32(pulseInfoStruct.tag_id),...
                    uint32(pulseInfoStruct.frequency_hz),...
                    pulseInfoStruct.start_time_seconds,...
                    pulseInfoStruct.predict_next_start_seconds,...
                    pulseInfoStruct.snr,...
                    pulseInfoStruct.stft_score,...
                    uint16(pulseInfoStruct.group_seq_counter),...
                    uint16(pulseInfoStruct.group_ind),...
                    pulseInfoStruct.group_snr,...
                    pulseInfoStruct.noise_psd,...
                    uint8(pulseInfoStruct.detection_status),...
                    uint8(pulseInfoStruct.confirmed_status));



end