function [thepulse] = makepulsestruc(A,yw,SNR,t_0,t_f,t_next,fp,fstart,fend)
%PULSE is an thepulseect containing the details of an individual pulse
%
%INPUTS
%   A           Amplitude
%   SNR         Signal to noise ratio in dB - This is often estimated as signal+noise to noise.
%   yw          STFT value at location (time and freq) of pulse. w here mean omega. This is equation 14 in the paper draft.
%   t_0         Start time of pulse
%   t_f         End time of pulse
%   t_next      Time range [tstart tend] of expected location of next pulse
%   fp          Peak frequency of pulse (Center frequency if symmetric in frequency domain
%   fstart      Start of the frequency bandwidth
%   fend        End of frequency bandwidth

%OUTPUTS
%   thePulse    a pulse struture with the properties:
%         A           Amplitude
%         P           Power
%         SNR         Signal to noise ratio in dB - This is often estimated as signal+noise to noise.
%         yw          STFT value at location (time and freq) of pulse. w here mean omega. This is equation 14 in the paper draft.
%         t_0         Start time of pulse
%         t_f         End time of pulse
%         t_next      Time range [tstart tend] of expected location of next pulse
%         fp          Peak frequency of pulse (Center frequency if symmetric in frequency domain
%         fstart      Start of the frequency bandwidth
%         fend        End of frequency bandwidth
%         mode        State machine mode under which pulse was discovered
%         det_dec     Detection decision (true/false)
%         con_dec     Was the pulse confirmed (true/false). In tracking, no confirmation step is executed so we record false.
%
%
%Author:    Michael Shafer
%Date:      Summer 2022
%--------------------------------------------------------------------------
%
%Needed to let coder know the mode string will be of variable length
%https://www.mathworks.com/help/simulink/ug/how-working-with-matlab-classes-is-different-for-code-generation.html
localMode = 'TBD';
coder.varsize('localMode',[1 inf],[0 1]); %dims 0 if fixed, 1 if variable

if nargin>0 %Allows for array construction https://www.mathworks.com/help/matlab/matlab_oop/initialize-thepulseect-arrays.html
    thepulse.A   = A;
    thepulse.P   = A.^2;
    thepulse.SNR = SNR;
    thepulse.yw  = yw;
    thepulse.t_0 = t_0;
    thepulse.t_f = t_f;
    thepulse.t_next = t_next;
    thepulse.fp  = fp;
    thepulse.fstart  = fstart;
    thepulse.fend    = fend;
    thepulse.mode = localMode;
    thepulse.det_dec = false;
    thepulse.con_dec = false;
else
    thepulse.A   = NaN;
    thepulse.P   = NaN;
    thepulse.SNR = NaN;
    thepulse.yw  = NaN;
    thepulse.t_0 = NaN;
    thepulse.t_f = NaN;
    thepulse.t_next = [NaN NaN];
    thepulse.fp  = NaN;
    thepulse.fstart  = NaN;
    thepulse.fend    = NaN;
    thepulse.mode = localMode;
    thepulse.det_dec = false;
    thepulse.con_dec = false;
end
end

