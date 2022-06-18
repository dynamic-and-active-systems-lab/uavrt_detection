classdef pulse %< handle
    %PULSE is an object containing the details of an individual pulse
    %
    % 
    %Author: Michael Shafer
    %Date:   Sometime in the summer of 2020. 
    %
    %%
    properties
        A           %Amplitude
        P           %Power
        SNR         %Signal to noise ratio in dB - This is often estimated as signal+noise to noise. 
        yw          %STFT value at location (time and freq) of pulse. w here mean omega. This is equation 14 in the paper draft.
        t_0         %Start time of pulse
        t_f         %End time of pulse
        t_next      %Time range [tstart tend] of expected location of next pulse
        fp          %Peak frequency of pulse (Center frequency if symmetric in frequency domain
        fstart      %Start of the frequency bandwidth
        fend        %End of frequency bandwidth
        mode        %State machine mode under which pulse was discovered
        det_dec     %Detection decision (true/false)
        con_dec     %Was the pulse confirmed (true/false). In tracking, no confirmation step is executed so we record false.
    end
    
    methods
        function obj = pulse(A,yw,SNR,t_0,t_f,t_next,fp,fstart,fend)
            %PULSE Constructs an instance of this class
            %   
            if nargin>0 %Allows for array construction https://www.mathworks.com/help/matlab/matlab_oop/initialize-object-arrays.html
                obj.A   = A;
                obj.P   = A.^2;
                obj.SNR = SNR;
                obj.yw  = yw;
                obj.t_0 = t_0;
                obj.t_f = t_f;
                obj.t_next = t_next;
                obj.fp  = fp;
                obj.fstart  = fstart;
                obj.fend    = fend;
                obj.mode = 'TBD';
                obj.det_dec = false;
                obj.con_dec = false;
            else
                obj.A   = NaN;
                obj.P   = NaN;
                obj.SNR = NaN;
                obj.yw  = NaN;
                obj.t_0 = NaN;
                obj.t_f = NaN;
                obj.t_next = [NaN NaN];
                obj.fp  = NaN;
                obj.fstart  = NaN;
                obj.fend    = NaN;
                obj.mode = 'TBD';
                obj.det_dec = false;
                obj.con_dec = false;
           end
        end
        
    end
end

