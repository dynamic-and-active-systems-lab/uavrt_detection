function [Xs,pulse_list] = detect(X,zetas,K,PF,focus_mode,selection_mode,xcld_freqs)
%DETECT Processes a waveform object to find pulses based on the priori
%information object within the waveform properties using the incoherent
%detection algorithm.
%   This function loads the appropriate decision table for threshold values
%   and then processes the waveform through segmentation. It can use two
%   different focus and selection modes. The 'focus' mode allows the program
%   to either focus down on a particular frequency once a tag is dectected.
%   This speed the processing significantly. If 'open' mode is selected,
%   the frequency and time bounds are left open so that all potential tags
%   can continue to be found in the dataset. If 'focus' is selected, the
%   selection mode must be specified. The seletion mode tells the algorithm
%   which pulse to focus on in the focus stage. The 'most' powerful pulse,
%   or the 'least' powerful. If priori data exists for X that include an 
%   upper and lower frequency band and if 'focus' is selected, the 
%   algorithm will only search in that range. For example if 
%   X.ps_pre.fstart = 200 and X.ps_pre.fstart = 600,
%   and 'focus' is selected, the algorith will only search in the band of
%   200-400 Hz.
%--------------------------------------------------------------------------
%Author: Michael W. Shafer
%Date: 2020-05-28
%
%--------------------------------------------------------------------------
%INPUTS:
%   X       A waveform object with a sufficienty fill ps_pre object
%               At a minimum, ps_pre is required to have the following
%               properties specified: t_p, t_ip, t_ipu
%   zetas   [1xp]   A vector of frequency fractions over which the
%                   weighting matrix will by built. [0 0.5] will generated
%                   a weighting matrix for the cases when the pulse
%                   frequencies fall at integer multiples and 1/2 multiples
%                   of the frequency resolution of the STFT. See the
%                   weightingmatrix.m help for more information. Increasing
%                   the resolution potentially increases the precision of
%                   the detected frequency, but will slow processing.
%
%   K      [1x1]    The integer number of pulses desired for incoherent
%                   summation.
%   PF     [1x1]    The desired probability of false alarm as a decimal.
%                   ie. 0.04 for 4%.
%   focus mode  [string]   (Case insensitive)
%                 Operational focus modes
%       'open'  - Stays in discovery mode, no narrowing of frequency or
%                 time windows. Slow, but will see all tags that match the
%                 priori
%       'focus' - Narrows focus in time and frequency to a single tag based
%                 on the selection mode:
%   selection_mode  [string]  (Case insensitive)
%               Method of selecting the pulse group on which to focus
%       'most'  - Selects the most powerful
%       'least' - Selects the least powerful
%
%   xcld_freqs   nx2    matrix of bands of
%                       frequencies to exclude in
%                       the search. This is useful if
%                       there has already been a tag
%                       found and you want to exclude
%                       that band when looking for
%                       other frequencies. The lower
%                       frequecie of the band should
%                       be in the first column and
%                       the upper should be in the
%                       second. This is only used in
%                       the naive frequency search
%                       mode. Leave empty [] if no
%                       exclusion zones are
%                       necessary.
%
%   If the signal is lost and a detection was previously made the search
%   will continue in the range bandwidth of the pulse previously detected.
%   If selection mode is left empty, the method will use 'most' method.
%   If the ps_pos object in X contains a mode selection, and 'focus' is
%   selected as the operating mode, the algorithm will begin in this mode,
%   (discovery, confirmation, or tracking).
%
%--------------------------------------------------------------------------
%OUTPUTS:
%   Xs      A vector of waveforms, segmented versions of input X, each with
%           a pulse stats object (ps_pos) containing relevent pulse
%           detections.
%
%   pulse_list A vector of pulse objects detected during processing.
%              Note that you can extract particular pulses using array
%              logicals. For example, to get all pulses in the 300-500 Hz
%              frequency band you would enter:
%                mask = [pulse_list(:).fp]>=300 &[pulse_list(:).fp]<=500
%
%
%--------------------------------------------------------------------------
%% CHECK THE INPUTS
% Check that zeta vector is supported by the currently available decision
% tables.
if any(zetas~=[0 0.5])
    error('UAV-RT: zeta vector specified for weighting matrix is not yet supported.')
end

% Check that 1<=K<=3
if K<1 || K>3
    error('UAV-RT: The number of pulsese selected must be between 1 and 3.')
end

% Check for in-bounds PF
if PF<0.001 || PF>0.999
    error('UAV-RT: Probability of false alarm must be between 0.1 and 99.9% (0.01-0.999).')
end

% Check for in-bounds PF
if strcmp(focus_mode,'open') && ~strcmp(selection_mode,'')
    warning('UAV-RT: Focus mode selected is `open`, but a selection mode was specified. No selection is used in open mode and will be ignored. In the future, specify an empty string for the selection mode when using an open focus mode to avoid this warning.')
    selection_mode = '';
end

if strcmp(focus_mode,'focus') && ~(strcmp(selection_mode,'most') || ...
        strcmp(selection_mode,'least'))
    warning('UAV-RT: Focus mode selected is `focus`, but selection mode specified is not `most` nor `least`. Defaulting to `most` powerful selection mode.' )
end

%--------------------------------------------------------------------------
%%
%Change mode selections to all lowercase
focus_mode = lower(focus_mode);
selection_mode = lower(selection_mode);

%load('decision_database.mat')

%decision_entry = decision_initialize(X.Fs,K,X.ps_pre.t_p,X.ps_pre.t_ip,X.ps_pre.t_ipu,X.OLF,zetas);


%Note that we should never let tp change during processing, as this would
%change the Wf vector (number of frequencies) and some of this processing
%assumes that the frequency vector is constant.



%Pseudo functional code
% while ~break & ~done
%   set priori dependent props in X
%   cleave a segment
%   set the priori of the cleave segment
%
%   set the mode based on focus mode or priori of the recently cleave
%   segment
%
%   call the state machine
%    (inputs are the cleaved segment and the mode)
%    (outputs are the cleaved segment (with new posteriori))
%
%
%X.setprioridependentprops(X.ps_pre);
%focus_mode = 'open'



breaklogic = false;
donelogic = false;
i = 1;

while ~breaklogic&&~donelogic%tick<10
    %i
    % Cleave new segment
    if i==1
        %Xs(i) = X.leave(K);    %Cut off section to process
        Xs(i) = X.leave(K,X.t_0,X.ps_pre);    %Cut off section to process
    else
        Xs(i) = X.leave(K,Xs(i-1).t_nextsegstart,Xs(i-1).ps_pos);    %Cut off section to process
    end
    % Naïve Incohsum segment processing
    Xs(i).spectro               %Build stft object
    nFreqBins   = size(Xs(i).stft.S,1);
    
    if strcmp(focus_mode,'open')
        mode = 'D';             %Force discovery mode if in 'open' focus mode
    else                        %Last processing decision mode selection is used in 'focus' focus mode
        mode = Xs(i).ps_pre.mode;
    end
    
    
    %Xs(i).process(mode,focus_mode,selection_mode,zetas,PF,DECISION_TABLE,xcld_freqs)
%     if i==4
%         pause(1);
%     end
    %Xs(i).process(mode,focus_mode,selection_mode,zetas,PF,decision_entry,xcld_freqs)
    Xs(i).process(mode,focus_mode,selection_mode,zetas,PF,xcld_freqs)
    
    
    %Logic on if there are enough pulses left to cleave another K pulses
    %enough_samps_left_for_another_cleave = (numel(X.x)>K*X.n_ws*(X.N+X.M+1));
    samples_left_to_process = sum(X.t>=Xs(end).t_nextsegstart);
    %enough_samps_left_for_another_cleave = samples_left_to_process >K*X.n_ws*(X.N+X.M+1);
    [new_n_p,new_n_w,new_n_ol,new_n_ws,new_t_ws,new_n_ip,new_N,new_M,new_J] = Xs(i).getprioridependentprops(Xs(i).ps_pos);
    %enough_samps_left_for_another_cleave = samples_left_to_process >K*new_depndt_props.n_ws*(new_depndt_props.N+new_depndt_props.M+1);
    %enough_samps_left_for_another_cleave = samples_left_to_process > K*new_n_ws*(new_N+new_M+1+1);
    enough_samps_left_for_another_cleave = samples_left_to_process > new_n_ws*(K*(new_N+new_M)+1+1)+new_n_ol;
    donelogic = ~enough_samps_left_for_another_cleave;
    i = i+1;
    
end
%Set the SNR of the found pulses. 
setpulseSNR(Xs)

pulse_list = [];
for i = 1:numel(Xs)
    if ~isnan(Xs(i).ps_pos.cpki)%pulse_listing only updated if peaks were found
        pk_ind = Xs(i).ps_pos.cpki;
        candidatelist = Xs(i).ps_pos.clst;
        new_pulses = candidatelist(pk_ind,:)';
        pulse_list = [pulse_list;new_pulses(:)];
    end
end




end

