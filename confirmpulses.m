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
    pulsestarttimes_withuncert = tref+((tip-tipu)*(0:(X.K-1)))-tipj*ones(1,X.K);
    pulseendtimes_withuncert   = tref+((tip+tipu)*(0:(X.K-1)))+tipj*ones(1,X.K);
else %First pulse in this segment does not exists in last segment as well because of overlap
    pulsestarttimes_withuncert = tref+((tip-tipu)*(1:(X.K)))-tipj*ones(1,X.K);
    pulseendtimes_withuncert   = tref+((tip+tipu)*(1:(X.K)))+tipj*ones(1,X.K);
end

%Check if pulses started after expected minimum start times
minstartlog = [X.ps_pos.pl(:).t_0]>=pulsestarttimes_withuncert;
%Check if pulses started before expected maximum start times
maxstartlog = [X.ps_pos.pl(:).t_0]<=pulseendtimes_withuncert;

%Frequency check. Within +/- 100 Hz of previously
%detected pulses?
freqInBand = [X.ps_pos.pl.fp] >= [X.ps_pre.pl.fp]-100 &...
             [X.ps_pos.pl.fp] <= [X.ps_pre.pl.fp]+100;

confLog = maxstartlog & minstartlog & freqInBand;

end