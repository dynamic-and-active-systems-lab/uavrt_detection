classdef wfmstft < handle
    %WFMSTFT is a class designed to containt a short-time Fourier 
    %transform and its associated descriptive properties
    %
    %
    %This class will build and hold and STFT for a waveform pddrovided to it
    %as an input. It will also hold the time and frequency vectors for the
    %resulting STFT matrix.
    %   
    %PROPERTIES:
    %   S           Spectrogram ouput
    %   f           Frequency vector for rows of S
    %   t           Time vector for columns of S
    %   wind_per_pulse  number of STFT time windows per pulse as described
    %                    in the waveform properties
    %   stft_steps_per_pulse    %number of stft time windpws
    %   dt          1/Fs of the data used to generate the STFT. This is
    %               needed for the PSD calculation.
    %   T           Time duration of an STFT window (n_w/Fs). This is
    %               needed for the PSD calculation.
    %   psd         A noise-only power spectral density estimate that based
    %               on a moving average of the S matrix, with thresholding
    %               the exclude high-power pulses. 
    %   window      The window used for the STFT
    %   
    %----------------------------------------------------------------------
    %Author: Michael W. Shafer
    %Date: 2020-05-28
    %	
    %----------------------------------------------------------------------
    %Updates:
    %   2022-03-31  Added psd, dt and T as properties. 
    %
    %%
    
    properties
        S(:,:) double	%Spectrogram ouput
        f(:,1) double   %Frequency vector for rows of S
        t(:,1) double   %Time vector for columns of S
        psd %Power spectral density (W/Hz)
        dt(1,1) double  %1/Fs of data used to generate STFT
        T(1,1) double   %Time of each window of the STFT (n_w/Fs)
        wind(:,1) double %Window definition used for the STFT
    end
    
    methods
        function obj = wfmstft(waveform_obj)
            %WFMSTFT Constructs and returns an instance of this class
            %
            %An waveform object must be passed to this construction method
            %so that the constructor has access to the data vector, desired
            %overlap fraction, and priori pulse data, which is used to
            %develop the window sizes. 
            %INPUTS:
            %   waveform_obj   A single waveform object with prior
            %                  dependent properties set. 
            %OUTPUTS:
            %   obj             A wfmstft object
            %%
            if nargin>0
                %wind = hann(waveform_obj.n_w,'periodic');
                %wind = tukeywin(waveform_obj.n_w,0.3);
                obj.wind = rectwin(waveform_obj.n_w);
                [obj.S,obj.f,local_time] = stft(waveform_obj.x,waveform_obj.Fs,'Window',obj.wind,'OverlapLength',waveform_obj.n_ol,'FFTLength',waveform_obj.n_w);
                obj.t = double(local_time)+waveform_obj.t_0; %Convert to global time of waveform. Double cast is needed because if x data in stft is single precision then the output t will be single as well.
                obj.dt = 1/waveform_obj.Fs;
                obj.T  = waveform_obj.n_w/waveform_obj.Fs;
                obj.updatepsd();
                
                %obj.psd = obj.dt^2/obj.T*mean(abs(obj.S).^2,2);% Sxx = dt^2/T*|xhat(f)|^2 
                %Vestigial properties no longer used. Kept in case we want
                %to resurect them. 
                %obj.wind_per_pulse = floor(waveform_obj.n_w/waveform_obj.n_p); %How many windows are needed to capture a pulse
                %obj.stft_steps_per_pulse = floor(waveform_obj.t_ws/waveform_obj.ps_pre.t_p);%How many stft steps are needed to capture a pulse
            end
        end
        
        function [] = adddata(obj,Snew,tnew)
            %ADDDATA Tacks on additional time windows to the existing STFT
            %object and ammends the time vector accordingly. 
            %INPUTS:
            %   Snew    STFT matrix to be appended with same number of
            %           frequency bins (rows) as obj.S
            %   tnew    Time vector of columns of Snew
            %OUTPUT:
            %   none
            %%
            obj.S = [obj.S, Snew];
            obj.t = [obj.t;tnew];
            obj.updatepsd();
            
        end
        
        function [] = setfreqs(obj,freqs)
            %SETFREQS Sets the frequency vector for the stft matrix rows. 
            %INPUTS:
            %   freqs   A vector of frequencies corresponding to the rows
            %           of the stft matrix S
            %OUTPUT:
            %   none
            %%
            obj.f = freqs;
        end
        
        function wfmstftout = copy(obj)
            wfmstftout = wfmstft;
            wfmstftout.S = obj.S;
            wfmstftout.f = obj.f;
            wfmstftout.t = obj.t;
            wfmstftout.dt  = obj.dt;
            wfmstftout.T   = obj.T;
            wfmstftout.psd = obj.psd;
            wfmstftout.wind = obj.wind;
            
        end
        function [] = updatepsd(obj)
            %obj.psd = obj.dt^2/obj.T*mean(abs(obj.S).^2,2);
            %obj.psd = obj.dt^2/obj.T*median(abs(obj.S).^2,2);%use median to exclude outliers from short pulses
%             runningPsd = obj.dt^2/obj.T*abs(obj.S).^2;
%             psdStdDev  = stdev(runningPsd,[],2);
%             psdStdDevMat = repmat(runningPsd,1,size(runningPsd,2));

            %This block calculates a three window moving mean of the power
            %spectral density of the waveform and then thresholds that
            %moving mean for values greater than 10x the median. This
            %thresholding step reduced the energy from very high power
            %pulses that might be in the signal from affecting the PSD
            %estimate. It is assumed here that low signal power pulses will
            %only marginally affect the psd estimate. 
            %coder.varsize('magSqrd','movMeanMagSqrd','medMovMeanMagSqrd','medMovMeanMagSqrdMat','magSqrdMask')
            magSqrd             = abs(obj.S).^2;
            movMeanMagSqrd      = movmean(magSqrd,3,2);
            medMovMeanMagSqrd   = median(movMeanMagSqrd,2);%transpose(median(transpose(movMeanMagSqrd)));%median(rand(80,32767),2);
            medMovMeanMagSqrdMat = repmat(medMovMeanMagSqrd,1,size(magSqrd,2));
            magSqrdMask = magSqrd > 10 * medMovMeanMagSqrdMat;
            magSqrd(magSqrdMask) = NaN;
            obj.psd = obj.dt^2/obj.T*mean(magSqrd,2,'omitnan');%use median to exclude outliers from short pulses
        end
        
        function [] = displaystft(obj)
            %This function will plot the STFT as a filled contour plot. It
            %has no functionality when deployed outside of Matlab. 
            if coder.target('MATLAB')
                figure
                contourf(obj.t,obj.f,abs(obj.S),'EdgeColor','none')
                xlabel('Time (s)');
                ylabel('Frequency (Hz)')
                title('Spectrogram')
            end
        end
    end
end

