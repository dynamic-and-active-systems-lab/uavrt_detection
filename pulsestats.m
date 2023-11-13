classdef pulsestats < handle
    %PULSESTATS Object contain parameter for a set of pulses. This class can be
    %used as a set of priori information that details the expectation of these
    %properties or built posteriori after detection. Some properties associated
    %with detections (pl, clst, cmsk,cpki) are not typically populated for
    %priori pulsestats object, unless they are known. The pulses listed in the
    %'pl' property depend on the selection mode selected in waveform process
    %method, but the items in clst, cmsk, and cpki, properties here always
    %contain all of the candidate pulses, mask, and peak indicies for the
    %waveform that was processed. The details of how these are specified can be
    %see in the process method of the waveform class.
    %
    %PROPERTIES:
    %   t_p     Duration of pulse (second)
    %           signal energy contained for 0<=t<tp
    %   t_ip    Inter-pulse time (seconds)
    %   t_ipu   Inter-pulse time uncertainty(seconds)
    %   t_ipj   Inter-pulse time jitter (deviations from means) (seconds)
    %   fp      Pulses' peak frequency (Hz) (highest power)
    %   fstart  Pulses' lower frequency bound
    %   fend    Pulses' upper frequency bound
    %   tmplt   Time domain amplitude template of the baseband pulse
    %           described with any number of evenly space time points
    %           between 0 and tp. [1 1] would represent a rectangular
    %           pulse of duration tp. [1 1 -1 -1] would be a constant
    %           1 from 0-tp/3, a ramp from tp/3-2tp/3, and a constant
    %           -1 from 2tp/3-tp.
    %   mode    What tracking mode should be use (for priori) or was used
    %           (for posteriori). 'D' 'C' or 'T'
    %   pl      'Pulse List' Vector of pulses objects in waveform (if
    %           known). This is the pulse group currently being
    %           tracked by the algorithm. The items in this list depend on the
    %           'selection_mode' used in the in the waveform process method.
    %   clst    'Candidate List' is a matrix of pulses objects in the
    %           waveform (if known). Pulses objects in row i are those
    %           found at ith frequeny of the Wf frequency vector.
    %           Pulses objects in column j are those found at jth time
    %           window of the STFT for the processed segment. This has
    %           as many columns as K (number of pulses) for the
    %           waveform segment. Has as many rows as frequencies used
    %           in the processing. Most of these 'pulses' will not
    %           meet the decision threshold and are just noise.
    %           Others might be sidebands. Some will be true pulses.
    %    cmsk   'Candidate List Mask' is a matrix the contains masks for
    %           each of the pulses that met the threshold. These masks
    %           are true for frequencies that the peeling algorithm
    %           deteremined to be sidebands of the true peak. These
    %           were determined through time correlations with the
    %           peaks. This matrix can be used to exclude candidate
    %           pulses in clst from further consideration. There is one
    %           row in cmsk for each frequency (like clst), but the
    %           number of columns corresponds to the number of peaks
    %           found in the processing result that met the decision
    %           criteria. For example, cmsk might have true values in
    %           column 2 at rows 5-8. This would indicated that
    %           the candidate pulses in clst in rows 5-8 correspond to
    %           the peak and sidebands of the #2 pulse listed cpki.
    %     cpki  These are the row indices of clst that were found to be
    %           peak (the center of the pulse frequency). Sidebands
    %           accociated with these peaks are recorded in each
    %           column cmsk. For example, the if the second element of
    %           cpki is 10, then the 10th row (frequency index) of clst
    %           contains a set of pulses that meet the decision
    %           criteria. The sidebands of this pulse group would be
    %           found in the 2nd column of cmsk.
    %   thresh  A vector of the thresholds computed for this used as the
    %           decision criteria for each of the candidate pulses in clst
    
    %METHODS SUMMARY:
    %   PULSESTATS Constructs an instance of this class
    %   COPY Creates an exact copy of the pulse stats object as a separate object
    %
    %
    %Author: Michael W. Shafer
    %Date: 2020-05-28
    %----------------------------------------------------------------------
    %
    properties
        t_p   (1, 1) double %Duration of pulse (second)
        t_ip  (1, 1) double %Inter-pulse time (seconds)
        t_ipu (1, 1) double %Inter-pulse time uncertainty (seconds)
        t_ipj (1, 1) double %Inter-pulse time jitter (deviations from means) (seconds)
        fp    (1, 1) double %Pulses' peak frequency (Hz) (highest power)
        fstart(1, 1) double %Pulses' lower frequency bound
        fend  (1, 1) double %Pulses' upper frequency bound
        tmplt (1, :) double %Time domain amplitude template of the baseband pulse
        mode  (1, 1) char   %The tracking mode that should be use (for priori) or was used (for posteriori). 'D' 'C' or 'T'
        pl    (1, :)        %'Pulse List' Vector of pulses objects in waveform
        clst  (:, :)        %'Candidate List' is a matrix of pulses objects in the waveform
        cmsk  (:, :) logical%'Candidate List Mask' is a matrix the contains masks for each of the pulses that met the threshold.
        cpki  (:,:)  double %These are the row indices of clst that were found to be peak (the center of the pulse frequency).
    end
    methods
        function obj = pulsestats(tp,tip,tipu,tipj,fp,fstart,fend,tmplt,mode,pl,clst,cmsk,cpki)
            %PULSESTATS Constructs an instance of this class
            %
            %INPUTS:
            %   tp      1x1     Duration of pulse (second)
            %   tip     1x1     Inter-pulse time (seconds)
            %   tipu    1x1     Inter-pulse time uncertainty (seconds)
            %   tipj    1x1     Inter-pulse time jitter (deviations from means) (seconds)
            %   fp      1x1     Pulses' center frequency (Hz) (if known)
            %   fstart  1x1     Lower frequency bound pulses' center frequency (Hz) (if known)
            %   fend    1x1     Upper frequency bound pulses' center frequency (Hz) (if known)
            %   tmplt   1xn     Pulse template. See properies for
            %                   definition. Usually set to [1 1] for
            %                   square pulse.
            %   pl      px1     Vector of pulse objects in waveform (if
            %                   known). If unknown enter a blank pulse made
            %                   from the contstructor "pulse";
            % Note: Unknown inputs should be set to NaN.
            %
            %OUTPUTS:
            %   pulsestats object
            %
            %%
            
            if nargin>0
                if (~isempty(tp) && isnan(tp)) ||...
                        (~isempty(tip) && isnan(tip)) ||...
                        (~isempty(tipu) && isnan(tipu)) ||...
                        (~isempty(tipj) && isnan(tipj))
                    error('UAVRT:incompleteparameters',...
                        'Other inputs can be NaN, but not tip,tipu, tp, nor tipj.')
                end
                obj.t_p     = tp;
                obj.t_ip    = tip;
                obj.t_ipu   = tipu;
                obj.t_ipj   = tipj;
                obj.fp      = fp;
                obj.fstart  = fstart;
                obj.fend    = fend;
                obj.tmplt   = tmplt;
                obj.mode    = mode;
                
                %The following are variable sized properties. To tell coder
                %that they may vary setup as a local variable size variable
                %first, then set.
                %Instructions on https://www.mathworks.com/help/simulink/ug/how-working-with-matlab-classes-is-different-for-code-generation.html
                %localMode = mode;
                %coder.varsize('localMode',[1 inf],[0 1]); %dims 0 if fixed, 1 if variable
                localPl = pl;
                localClst = clst;
                localCmsk = cmsk;
                localCpki = cpki;
            else
                localPl   = makepulsestruc();
                localClst = makepulsestruc();
                localCmsk = false(0,0);
                localCpki = zeros(0,0);
            end
                %Tell coder these are variable size.
                coder.varsize('localClst',[inf inf],[1 1]);
                coder.varsize('localPl',  [inf inf],[1 1]);
                coder.varsize('localCmsk',[inf inf],[1 1]);
                coder.varsize('localCpki',[inf 1],[1 1]);
                %Now actually assign them 
                obj.pl   = localPl;
                obj.clst = localClst;
                obj.cmsk = localCmsk;
                obj.cpki = localCpki;
        end
        function obj_out = makepropertycopy(obj)
            %COPY Creates an exact copy of the pulse stats object as a 
            %separate object
                 obj_out =   pulsestats(obj.t_p,...
                                        obj.t_ip,...
                                        obj.t_ipu,...
                                        obj.t_ipj,...
                                        obj.fp,...
                                        obj.fstart,...
                                        obj.fend,...
                                        obj.tmplt,...
                                        obj.mode,...
                                        obj.pl,...
                                        obj.clst,...
                                        obj.cmsk,...
                                        obj.cpki);%,...
                                        %obj.thresh);
        end
        function [] = copydetectionresults(obj,ps_tocopyfrom)
            %Copy the other properties not used in the constructor
            obj.mode = ps_tocopyfrom.mode;
            obj.pl   = ps_tocopyfrom.pl;
            obj.clst = ps_tocopyfrom.clst;
            obj.cmsk = ps_tocopyfrom.cmsk;
            obj.cpki = ps_tocopyfrom.cpki;
        end

        function [] = updateposteriori(obj, ps_pre, pulselist, updateType)
            %UPDATEPOSTERIORI updates the posteriori pulse statistics
            %object using the new pulse list (input), prior pulse stats
            %and the waveforms power spectral density vector. This
            %methods is typically going to be called on a posteriori pulse
            %stats object after a waveform has been processed and a set
            %of candidate pulses found. This method uses those pulses and
            %the prior information about the pulses to update the
            %posteriori pulse stats.
            %
            %The pulse contained in the waveform's ps_pos
            %property is not used directly so that the caller can decide
            %which pulses on which to focus the posteriori updates
            %
            % updateType    What parts of the pulsestats to update. Valid
            %               options are 'time', 'freq', 'timeandfreq'. The
            %               'time' option will only update the interpulse
            %               time statistics. The 'freq' option will only
            %               update the frequency stats. The 'timeandfreq'
            %               option will update both. 
            %
            coder.varsize('recent_tip',[inf 1], [1 1]);
            
            if ~isempty(pulselist)                
                t_found    = [pulselist.t_0]'; % pulselist(:).t_0]'
                freq_found = mean([pulselist.fp],'all','omitnan'); %pulselist(:).fp
                
                %Fix the bandwidth in the priori to +/- 100 Hz.
                bw_found = 200;
                
                %Here is where we update the stats. These methods of updates
                %could be improved in the future.
                
                if numel(pulselist)==1% Happens if K=1
                    %We only have one pulse to reference, so we need to check
                    %the prior pulse too.
                    if ~isempty(ps_pre.pl) && ~isnan(ps_pre.pl(end).t_0)
                        recent_tip = pulselist(1).t_0-ps_pre.pl(end).t_0;
                        %recent_tip =
                        %pulselist.t_0-ps_pre.pl(end).t_0;%Conflicts with
                        %Coder. Needed the (1) callout
                        
                        %There could be a case where the last segment and this
                        %segement identified the same pulse. In this case
                        %recent_tip will be very small. In this case, we just
                        %say we learned nothing about t_ip in this segment.
                        if recent_tip < ps_pre.t_ipu + ps_pre.t_ipj
                            recent_tip = NaN;
                        end
                    else
                        %No new information because we don't know the last
                        %pulse time
                        recent_tip = NaN;
                    end
                else
                    recent_tip = diff(t_found);
                end
                %Do a check here to make sure the new tip isn't a huge change.
                %This could potentially happen if we are in the K = 1 case and
                %the block getting processed contained two pulses, with the
                %latter pulse getting identified/detected. The lines above
                %would look back to the last identified pulse and it might be
                %2*tip back in time, producing a very large recenttip values.
                %If something like this happens, we ignore it so it doesn't
                %affect our new tip estimates.
                if recent_tip > 1.5*ps_pre.t_ip & recent_tip < 0.5*ps_pre.t_ip
                    recent_tip = NaN;
                end
                                
                switch updateType
                    case 'time'
                        obj.t_ip  = mean([recent_tip;ps_pre.t_ip],'omitnan');
                        obj.t_ipu = ps_pre.t_ipu; %Don't update this because it can get too narrow.%mean([3*std(diff(t_found));wfm.ps_pre.t_ipu]);
                        obj.t_ipj = ps_pre.t_ipj;
                    case 'freq'
                        fp_pos     = freq_found;%nanmean([freq_found;wfm.ps_pre.fp]);%Previous fc may be nan if unknown
                        obj.fp     = fp_pos;
                        obj.fstart = fp_pos-bw_found/2;
                        obj.fend   = fp_pos+bw_found/2;
                    case 'timeandfreq'
                        obj.t_ip  = mean([recent_tip;ps_pre.t_ip],'omitnan');
                        obj.t_ipu = ps_pre.t_ipu; %Don't update this because it can get too narrow.%mean([3*std(diff(t_found));wfm.ps_pre.t_ipu]);
                        obj.t_ipj = ps_pre.t_ipj;
                        fp_pos     = freq_found;%nanmean([freq_found;wfm.ps_pre.fp]);%Previous fc may be nan if unknown
                        obj.fp     = fp_pos;
                        obj.fstart = fp_pos-bw_found/2;
                        obj.fend   = fp_pos+bw_found/2;
                end                    
            end
            
        end


    end
end

