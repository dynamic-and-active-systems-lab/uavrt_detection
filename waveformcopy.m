function [wfmOut] = waveformcopy(wfmIn)
%WAVEFORMCOPY makes a copy of the input waveform. Waveforms are handle
%objects, as are some of their properties. This function make new instances
%of these objects. 
%
%INPUTS:
%   wfmIn   an individual waveform
%OUTPUTS
%   wfmOut  copy of input waveform
%

wfmOut = waveform();
wfmOut.ps_pre = pulsestats(wfmIn.ps_pre.t_p, wfmIn.ps_pre.t_ip, ...
                           wfmIn.ps_pre.t_ipu, wfmIn.ps_pre.t_ipj, ...
                           wfmIn.ps_pre.fp, wfmIn.ps_pre.fstart, ...
                           wfmIn.ps_pre.fend, wfmIn.ps_pre.tmplt, ...
                           wfmIn.ps_pre.mode, wfmIn.ps_pre.pl, ...
                           wfmIn.ps_pre.clst, wfmIn.ps_pre.cmsk, ...
                           wfmIn.ps_pre.cpki);
wfmOut.ps_pos = pulsestats(wfmIn.ps_pos.t_p, wfmIn.ps_pos.t_ip, ...
                           wfmIn.ps_pos.t_ipu, wfmIn.ps_pos.t_ipj, ...
                           wfmIn.ps_pos.fp, wfmIn.ps_pos.fstart, ...
                           wfmIn.ps_pos.fend, wfmIn.ps_pos.tmplt, ...
                           wfmIn.ps_pos.mode, wfmIn.ps_pos.pl, ...
                           wfmIn.ps_pos.clst, wfmIn.ps_pos.cmsk, ...
                           wfmIn.ps_pos.cpki);

wfmOut.thresh    = wfmIn.thresh;
wfmOut.stft.S    = wfmIn.stft.S;
wfmOut.stft.f    = wfmIn.stft.f;
wfmOut.stft.t    = wfmIn.stft.t;
wfmOut.stft.psd  = wfmIn.stft.psd;
wfmOut.stft.dt   = wfmIn.stft.dt;
wfmOut.stft.T    = wfmIn.stft.T;
wfmOut.stft.wind = wfmIn.stft.wind;

wfmOut.K         = wfmIn.K;
wfmOut.x         = wfmIn.x;
wfmOut.Fs        = wfmIn.Fs;
wfmOut.l         = wfmIn.l;
wfmOut.t_0       = wfmIn.t_0;
wfmOut.t_0       = wfmIn.t_f;
wfmOut.t_nextsegstart = wfmIn.t_nextsegstart;
wfmOut.OLF       = wfmIn.OLF;
wfmOut.W         = wfmIn.W;
wfmOut.Wf        = wfmIn.Wf;
wfmOut.n_p       = wfmIn.n_p;
wfmOut.n_w       = wfmIn.n_w;
wfmOut.n_ol      = wfmIn.n_ol;
wfmOut.n_ws      = wfmIn.n_ws;
wfmOut.t_ws      = wfmIn.t_ws;
wfmOut.n_ip      = wfmIn.n_ip;
wfmOut.N         = wfmIn.N;
wfmOut.M         = wfmIn.M;
wfmOut.J         = wfmIn.J;

end