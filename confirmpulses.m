function [confLog] = confirmpulses(X)
%confirmpulses Returns a boolean vector that say if the pulses in the
%X.ps_pos pulse stats are where they should be in frequency and time based on
%the last pulse of the X.ps_pre and its pulse timing parameter.

tref = X.ps_pre.pl(end).t_0;
%tp   = X.ps_pre.t_p;
tip  = X.ps_pre.t_ip;
tipu = X.ps_pre.t_ipu;
tipj = X.ps_pre.t_ipj;
if tref>X.t_0 %First pulse in this segment exists in last segment as well because of overlap
    if abs(X.ps_pos.pl(1).t_0 - tref) < tipu+tipj %X.ps_pos.pl(1).t_0 <= tref + (tip + tipu + tipj)
       %new first pulse is the same one as the last one in the last
        %segment
        pulsestarttimes_withuncert = tref+((tip-tipu)*(0:(X.K-1)))-tipj*ones(1,X.K);
        pulseendtimes_withuncert   = tref+((tip+tipu)*(0:(X.K-1)))+tipj*ones(1,X.K);
    else
        %new first pulse isn't the same one as the last one in the last
        %segment because the detector detected the last K pulses in the
        %segment and not the first three. Remember that the segment can
        %contain K+1 pulses
        pulsestarttimes_withuncert = tref+((tip-tipu)*(1:(X.K)))-tipj*ones(1,X.K);
        pulseendtimes_withuncert   = tref+((tip+tipu)*(1:(X.K)))+tipj*ones(1,X.K);
    end
else %First pulse in this segment does not exists in last segment as well because of overlap
    pulsestarttimes_withuncert = tref+((tip-tipu)*(1:(X.K)))-tipj*ones(1,X.K);
    pulseendtimes_withuncert   = tref+((tip+tipu)*(1:(X.K)))+tipj*ones(1,X.K);
end
%%Debugging plots
% figure;xline(pulsestarttimes_withuncert,'--')
% hold on;xline(pulseendtimes_withuncert,'--')
% plot([X.ps_pos.pl(:).t_0],zeros(size([X.ps_pos.pl(:).t_0])),'ob')

%Check if pulses started after expected minimum start times
minstartlog = [X.ps_pos.pl(:).t_0]>=pulsestarttimes_withuncert;
%Check if pulses started before expected maximum start times
maxstartlog = [X.ps_pos.pl(:).t_0]<=pulseendtimes_withuncert;

%Frequency check. Within +/- 100 Hz of previously
%detected pulses?
freqInBand = [X.ps_pos.pl.fp] >= [X.ps_pre.pl.fp]-100 &...
             [X.ps_pos.pl.fp] <= [X.ps_pre.pl.fp]+100;

%confLog = maxstartlog & minstartlog & freqInBand;

%2023-09-14
%The method above has increasing uncertainty bounds for the Kth pulse that
%allows for the entire group to be shifted in time and only the last K
%pulse gets confirmed. We really need to only check that the first pulse in
%the group is in the correct position. If it is, then the others are
%confirmed by default. 

numPulses = numel(X.ps_pos.pl);
indivConfLog = maxstartlog & minstartlog & freqInBand; 
confLog = false(numPulses ,1);
confLog(:) = indivConfLog(1);


%2023-09-21
%If an individual pulse of noise energy is sufficient to be above exceed
%the threshold, even if all the other K-1 pulses in its groups are just
%noise, and the noise pulses are repeated in a way that a confirmation in
%time might occur, the SNR of the adjacent pulses in the group will be
%very low. Here we check to make sure all the pulses have SNRs within 7dB
%of the max SNR in the pulse group. If they don't we reject the pulses. If
%we are dealing with a K = 1 case, we check against the previous pulse. 
SNRnotNegInf = false(numPulses, 1);

if numPulses > 1
    SNRall = [X.ps_pos.pl(:).SNR].';
    %SNRmax     = max(SNRall,[],'all');
    %SNRsimilar = SNRall >= SNRmax - abs(SNRmax/2);%use -abs() because SNRmax could be negative. Can't just mult by 0.5
    %SNRsimilar = SNRall >= SNRmax - 7;%use a fixed distance of 7 dB (5x)
    SNRnotNegInfLog = SNRall ~= -inf;
    SNRnotNegInfAll = all(SNRnotNegInfLog,'all');
    SNRnotNegInf = false(size(SNRall));
    SNRnotNegInf(:) = SNRnotNegInfAll;
elseif numPulses == 1
    %If K = 1 and we are confirming pulses, we should always have a pulse
    %in the previous pulse list. Just in case, we check here that there is
    %pulse in the previous segment. 
    if isnan(X.ps_pre.pl(1).fp)
        SNRnotNegInf = false;
    else
        % SNRprevious = X.ps_pre.pl(1).SNR; 
        % SNRsimilar  = X.ps_pos.pl(1).SNR >= SNRprevious - 7;
        SNRnotNegInf = X.ps_pos.pl(1).SNR ~= -Inf;
    end
end
% if X.ps_pos.pl(1).t_0>328
%     pause(1);
% end
confLog = confLog & SNRnotNegInf;


end