%% MAIN.m
%
%
%
%----------------------------------------------------------------------
%Author: Michael W. Shafer
%Date: 2020-05-28
%Change log:
%	2020-05-28: Initial release
%
%----------------------------------------------------------------------
%
%%
clear
%clc
%close all
%% DEFINE TRUE PULSE SPECIFCATIONS
Fs_hifi   = 48000;  %Sampling frequency of the orginal signal
Fs        = 4000;   %Sampling frequency of the decimated signal
%This needs to be at least twice the frequencies in the
%signal or filter bank. I've been using a 500 Hz pulse,
%so technically 1k would be the minimum here, but we'll
%use 2xNyquist
SNR_dB    = -5;     %SNR of the pulses
n_tags    = 5;
numpulses = 12;
tp        = 0.02;   %Standard pulse width
tip_mu    = 1.31;   %Average inter-pulse duration
tip_sigma = 0.02;   %Standard dev of inter-pulse duration
p1_offset  = (tip_mu-0).*rand(n_tags,1) + 0;%0.25;%0.1;   %Start time (s) of fist pulse


zetas = [0,0.5]; %Specify the frequency bin fractions to build the template in. Range should be between [0,1)

%Minimum frequency spacing is about 4*frequency resolution in each window
%of the STFT output. We can decrease it by the inverse of the number of
%zeta values, as that gives use better frequency resolution.
min_freq_spacing = 4*Fs/(Fs*tp)*1/numel(zetas);%Assuming even spacing in zeta vector

%This creates a frequency for each tag while obeying the minimum frequency
%spacing. It does this recursively, first taking a randome guess within
%75% of the BW and then checking the frequency spacing.
Fp        = sort(randi(0.75*Fs/2*[-1 1],n_tags,1));%0.75 to stay inside of the rolloff-500;    %True pulse frequency;
while any(diff(Fp)<min_freq_spacing) || any(abs(Fp)>0.75*Fs/2)
    inds_to_change = find(diff(Fp,[],1)<min_freq_spacing)+1;
    inds_to_change = unique([inds_to_change;find(abs(Fp)>0.75*Fs/2)]);
    Fp(inds_to_change) = randi(Fs/2*[-1 1],numel(inds_to_change),1);
    Fp = sort(Fp);
end

%Specify the time and phase deviations of the pulses.
deviations = normrnd(0,tip_sigma,[n_tags,numpulses]);
phases = pi/180*360*rand(n_tags,numpulses);
%Determine the pulse amplitudes to meet the desired SNR
airspy_noise_power_W_4k  = 1.3e-8;
Sxx      = airspy_noise_power_W_4k/4000;%Power spectral density V^2/Hz
Sxx_bar  = airspy_noise_power_W_4k*0.02*4000;%Energy spectral density in pulse
airspy_noise_power_W_Fs_hifi = Sxx*Fs_hifi;
amp_hi  = sqrt(Sxx*Fs_hifi)*10^(SNR_dB/20);
amp_lo  = sqrt(Sxx*Fs)*10^(SNR_dB/20);
amps_hi = amp_hi*ones(n_tags,numpulses);
amps_lo = amp_lo*ones(n_tags,numpulses);
amp_factors = (1-1).*rand(n_tags,1) + 1;%factors to multiply the amplitudes by above the minimum defined by SNR_dB
amps_hi = repmat(amp_factors,1,numpulses).*amps_hi;
amps_lo = amps_hi;% repmat(amp_factors,1,numpulses).*amps_lo;

%% DEFINE WHAT WE THINK WE KNOW ABOUT THE TAG
%This is what you might have from a tag specification sheet.
tp_spec     = 0.02;     %Pulse duration spec (s)
tip_spec    = 1.3;      %Interpulse time spec (s)
tipu_spec   = 3*tip_sigma;%Uncertainty in tip
%If you specify a frequency and bandwidth here the search will only occur
%over that range. If unknown, set the spec as NaN
Fp_spec     = NaN;      %Unknown center frequency (Hz)
fstart_spec = -Inf;     %Use -Inf for unknown start frequency (Hz)
fend_spec   = Inf;      %Use  Inf for unknown stop frequency (Hz)
tmplt_spec  = [1 1];    %Pulse template. See pulse_stats object for how
%this is defined. [1 1] is a rectangular pulse
%between 0 and tp

%% BUILD THE DATA VECTOR
%Build start time vector
%num_pulses = numel(deviations);     %Number of pulses to be considered
for j = 1:n_tags
    for i = 1:numpulses
        if i==1
            real_starts(j,i) = p1_offset(j)+deviations(j,i);
        else
            real_starts(j,i) = real_starts(j,i-1)+tip_mu+deviations(j,i);
        end
    end
end
Fp_mat = repmat(Fp,1,size(real_starts,2));
for j = 1:n_tags
    for i = 1:numpulses
        pulse_true(j,i) = pulse(amps_hi(j,i),NaN,NaN,real_starts(j,i),real_starts(j,i)+tp_spec,NaN,Fp_mat(j,i),NaN,NaN);
    end
end

if floor(Fs_hifi/Fs)~=Fs_hifi/Fs
    error('Hifi sample rate is not an integer multiple of Fs. Must be to decimate.')
end
PNdB_add_hifi  = 10*log10(airspy_noise_power_W_Fs_hifi);
PNdB_add_lofi  = 10*log10(airspy_noise_power_W_4k);
%Minimum number of samples. This assumes there could be an error in the tip mean a priori.
samps_min_hifi = ceil(Fs_hifi*(tip_mu+tipu_spec)*numpulses);
%Minimum number of samples. This assumes there could be an error in the tip mean a priori.
samps_min_lofi = ceil(Fs*(tip_mu+tipu_spec)*numpulses);
SEG_hi = pulseseg;%Pre-set as a pulseseg object
SEG_lo = pulseseg;%Pre-set as a pulseseg object
SEG_hi.ht = 0;
SEG_lo.ht = 0;
for i = 1:n_tags
    SEG_hi_ind{i} = pulseseg(samps_min_hifi,Fs_hifi,Fp(i),tp,real_starts(i,:),phases(i,:),amps_hi(i,:));%Build pulse segment
    SEG_lo_ind{i} = pulseseg(samps_min_lofi,Fs,Fp(i),tp,real_starts(i,:),phases(i,:),amps_lo(i,:));%Build pulse segment
    SEG_hi.ht = SEG_hi.ht + SEG_hi_ind{i}.ht;
    SEG_lo.ht = SEG_lo.ht + SEG_lo_ind{i}.ht;
end
x_clean_hi = SEG_hi.ht;
x_clean_lo = SEG_lo.ht;
SEG_hi.addnoise(PNdB_add_hifi); %Add the noise using addnoise method
SEG_lo.addnoise(PNdB_add_lofi); %Add the noise using addnoise method
DF = factor(Fs_hifi/Fs);        %Decimation factors
x_raw = SEG_hi.ht;
x_hold = x_raw;
x_hold_clean = x_clean_hi;
%Decimate in stages to not exceed the Matlab decimation factor limit
for i = 1:length(DF)
    %Decimate data dirty signal.
    x_hold = decimate(x_hold,DF(i));
    %Decimate data dirty signal.
    x_hold_clean = decimate(x_hold_clean,DF(i));
    
end
x = x_hold;
t = (0:length(x)-1)*1/Fs;

%%
[file,path] = uigetfile('*.dat','Select binary IQ radio data file');
count=inf;
f = fopen (fullfile(path,file), 'rb');
d = fread (f, [2, count], 'float'); %read in img and real parts of file
fclose (f);
x = (d(1,:) + d(2,:)*1i)'; %combine real and imag into one vector and transpose to make a column

%Fs = 48000;
%plot((0:numel(x)-1)/48000,x,'g--');hold on
x = x.*exp(-1i*2*pi*1600*(0:numel(x)-1)/48000)';
DF = factor(48000/8000);        %Decimation factors
%DF = factor(3e6/8000);        %Decimation factors

for i = 1:length(DF)
    %Decimate data dirty signal.
    x = decimate(x,DF(i));
end

%plot((0:numel(x)-1)/8000,x,'b-')
Fs = 8000;
tip_spec = 1.38;
x = zeromean(x,floor(8000*3*tip_spec)) ;%Remove DC bias
%plot((0:numel(x)-1)/8000,x,'ko')

A = max(abs(x));
SNR = 100;%dB
noise = wgn(numel(x),1,A/10^(SNR/10),'linear','complex');
x_clean = x ;%Hold on for debugging
x       = x + noise ;%Hold on for debugging
            


%% PREPARE FOR COHERENT SUMMATION AND DETECTION
% Build initial pulse stats object

%%%YOU SHOULD BUILD THE TEMPLATE HERE AND DON'T FORGET TO DEFINE THE
%%%BANDWIDTH HERE BASED ON SOME FRACTION OF THE SPECTRAL ENERGY. RIGHT NOW
%%%WE ARE USING SOME STANDARD BANDWIDTH, BUT THIS NEEDS TO BE UPDATED. THE
%%%BANDWIDTH IS USED IN THE FINDPULSE METHOD AND

%sound(real(x./max(real(x))),Fs)

PS_DEFAULT = pulsestats(tp_spec,tip_spec,tipu_spec,Fp_spec,fstart_spec,fend_spec,tmplt_spec,pulse); %Inputs are (tp,tip,tipu,fc,bw,Hf,pl)
%X          = waveform(real(round(x,7)),Fs,0,PS_DEFAULT,0.8); %Create waveform
X          = waveform(x,Fs,0,PS_DEFAULT,0.8); %Create waveform

%% EXECUTE ALGORITHM
xcld_freqs = [];% [400 600;1000 1400];%[-400 -200; 400 600];
K = 3;
PF = 0.005;
%zetas were already defined to nail down min_freq_spacing above
tic
[Xs,pulse_list] = detect(X,zetas,K,PF,'open','most',xcld_freqs);
toc

X.setprioridependentprops(X.ps_pre)
%Create dummy weighting matrix call just to get needed frequency vector
[~,Wf] = weightingmatrix(1:X.n_w,X.Fs,zetas);



%% Create graphs of the results of processing
for i = 1:numel(Xs)                 %For each processed segment
   %if ~isnan(Xs(i).ps_pos.cpki)    %Run this if candidates were recorded
        pk_ind = Xs(i).ps_pos.cpki; %Get time index listing of peaks
        candidatelist = Xs(i).ps_pos.clst;%Pulse list candidates for this segment
        msk = Xs(i).ps_pos.cmsk;    %Get sideband mask for this set of pulses
        scores{i} = sum(reshape([candidatelist.yw],size(candidatelist,1),size(candidatelist,2)),2);
        freqs2plot = sort(unique([candidatelist.fp]'));
        
        if i==1%For first index, build the plot window
            mainfig = figure;
            axis1 = subplot(3,4,[1,5,9]);
            set(gca,'YTick',floor(-Xs(i).Fs/2):200:ceil(Xs(i).Fs/2));
            set(gca,'YLim',[floor(-Xs(i).Fs/2),ceil(Xs(i).Fs/2)]);
            grid on;
            ylabel('Frequency from Baseband (Hz)')
            xlabel('z-score (V^2)')
            set(gca,'xscale','log')
            axis2 = subplot(3,4,[2:4,6:8,10:12]);
            set(gca,'YTick',get(axis1,'YTick'));
            set(gca,'XLim',[X.t_0,X.t_f]);
            grid on;
            xlabel('Time (s)')
            linkaxes([axis1 axis2],'y')
        else
            set(0, 'currentfigure', mainfig);
        end
        set(mainfig, 'currentaxes', axis1);
        %Plot the true pulse frequencies with a horizontal line for
        %reference
        if i==1
            for z = 1:numel(Fp)
                yline(Fp(z),'-','Color',0*[1 1 1])
                hold on
            end
        end
        %Set the colors of the different peaks in the specturm
        thecolors  = hsv(numel(Wf));
        color_inds = nan(numel(pk_ind),1);
        if ~isnan(pk_ind)
            for p = 1:numel(pk_ind)
                color_inds(p) = find(freqs2plot(pk_ind(p))==Wf);
            end
            peakcolors = thecolors(color_inds,:);%thecolors(pk_ind,:);
        end
        %Plot the scores in the spectral plot
        plot(scores{i},freqs2plot,'Color',[0.6 0.6 0.6]);hold on
        if ~isnan(pk_ind)
            for p = 1:size(msk,2)
                plot(scores{i}.*msk(:,p),freqs2plot,'Linewidth',2,'Color',peakcolors(p,:));hold on
                plot(scores{i}(pk_ind(p)),freqs2plot(pk_ind(p)),'o','Markersize',10,'Color',[1 0 0]);hold on
            end
        end
        %Plot the freq-time bins of candidate pulses in the temporal plot
        set(mainfig, 'currentaxes', axis2);
        scores_normalized = (scores{i}-min(scores{i}))/max(scores{i});
        for p = 1:size(candidatelist,1)
            for o = 1:size(candidatelist,2)
                %Only plot if this frequency was processed
                if ~isnan(candidatelist(p,o).yw)
                    t0 = candidatelist(p,o).t_0;
                    tf = candidatelist(p,o).t_f;
                    f0 = candidatelist(p,o).fstart;
                    ff = candidatelist(p,o).fend;
                    pg{i}(p,o) = polyshape([t0 tf tf t0],[ff ff f0 f0]); hold on
                    ps{i}(p,o) = plot(pg{i}(p,o));hold on
                end
            end
        end
        %Highlight the peaks with colors
        for p = 1:size(candidatelist,1)
            for o = 1:size(candidatelist,2)
                %Only plot if this frequency was processed
                if ~isnan(candidatelist(p,o).yw)
                    if any(p==pk_ind)%this is a peak pulse group
                        whichpeak = find(p==pk_ind);
                        ps{i}(p,o).FaceColor = peakcolors(whichpeak,:);
                        ps{i}(p,o).EdgeColor = peakcolors(whichpeak,:);
                        ps{i}(p,o).EdgeAlpha = 1;
                        ps{i}(p,o).FaceAlpha = 0.8;
                    else %this isn't a peak pulse group
                        if any(msk(p,:))
                            whichpeakassociated = find(msk(p,:));
                            ps{i}(p,o).FaceColor = peakcolors(whichpeakassociated,:);
                            ps{i}(p,o).EdgeColor = peakcolors(whichpeakassociated,:);
                        else
                            ps{i}(p,o).FaceColor = 0.6*[1 1 1];
                            ps{i}(p,o).EdgeColor = 0.6*[1 1 1];
                        end
                        ps{i}(p,o).EdgeAlpha = 0.4;
                        ps{i}(p,o).FaceAlpha = 0.1;
                    end
                end
            end
        end
        if strcmp(Xs(i).ps_pos.clst(1).mode,'D')
            mode_color = [1 0 0];
        elseif strcmp(Xs(i).ps_pos.clst(1).mode,'C')
            mode_color = [0 1 0];
        else
            mode_color = [0 0 1];
        end
        plot([Xs(i).t_0,Xs(i).t_f],max(get(gca,'YLim'))*[1 1],'Linewidth',5,'Color',mode_color)
        plot([Xs(i).t_0,Xs(i).t_f],min(get(gca,'YLim'))*[1 1],'Linewidth',5,'Color',mode_color)
        drawnow
    %end 
end

%Plot the decision thresholds used
%load('decision_database.mat')
decision_entry = decision_initialize(X.Fs,K,X.ps_pre.t_p,X.ps_pre.t_ip,X.ps_pre.t_ipu,X.OLF,zetas);
for i = 1:numel(Xs)
    if strcmp(Xs(i).ps_pre.pl(1).mode,'D') ||...
        strcmp(Xs(i).ps_pre.pl(1).mode,'C') 
        timesearchmode = 'naive';
        linetype = '--';
    else
         timesearchmode = 'informed';
         linetype = '-';
    end
    thresh = getthreshold(Xs(i),PF,decision_entry,timesearchmode);
    set(mainfig, 'currentaxes', axis1);
    xline(thresh,linetype)
end

% %Get a upper and lower bands of frequency for all found pulses.
% lower_f_band = abs([pulse_list(:).fstart]-[pulse_list(:).fp]);
% upper_f_band = abs([pulse_list(:).fend]  -[pulse_list(:).fp]);
% 
% %The code below looks for pulses that are in the same frequency band and
% %are within tp of each other in time, and then eliminate one if repeats are
% %found.
% rep_freq_mat = vecfind([pulse_list(:).fp],'>=',[pulse_list(:).fstart]-2*lower_f_band)&...
%     vecfind([pulse_list(:).fp],'<=',[pulse_list(:).fend  ]+2*upper_f_band);
% rep_time_mat = vecfind([pulse_list(:).t_0],'>=',[pulse_list(:).t_0]-tp/2)&...
%     vecfind([pulse_list(:).t_0],'<=',[pulse_list(:).t_0]+tp/2);
% rep_pulse_mat = rep_freq_mat & rep_time_mat;
% cols_remaining = size(rep_pulse_mat,1);
% i = 1;
% while cols_remaining~=0%
%     repeated_cols = i+find(rep_pulse_mat(i,i+1:end));
%     rep_pulse_mat(:,repeated_cols) = [];
%     rep_pulse_mat(repeated_cols,:) = [];
%     pulse_list(repeated_cols)=[];
%     i = i+1;
%     cols_remaining = cols_remaining-1-numel(repeated_cols);
% end
% %Now that we've eliminated redundant detections, we create a new frequency
% %bounds for the detected pulses
% lower_f_band = abs([pulse_list(:).fstart]-[pulse_list(:).fp]);
% upper_f_band = abs([pulse_list(:).fend]  -[pulse_list(:).fp]);
% 
% %Now generate matrices for found frequency and time
% found_freq_mat = vecfind([pulse_true(:).fp],'>=',[pulse_list(:).fstart]-2*lower_f_band)&...
%     vecfind([pulse_true(:).fp],'<=',[pulse_list(:).fend]+2*upper_f_band);
% found_time_mat = vecfind([pulse_true(:).t_0],'>=',[pulse_list(:).t_0]-tp/2)&...
%     vecfind([pulse_true(:).t_0],'<=',[pulse_list(:).t_0]+tp/2);
% found_both_mat = found_freq_mat & found_time_mat;
% %spy(found_both_mat,'go')
% 
% T_MAX = Xs(end).t_0;
% %We don't go all the way to the end of the record for the stats
% %because the last pulse is often not caught due to the need for
% %multiple pulses and there not being enough samples for a final
% %segement
% 
% found_both_mat_T_sub = found_both_mat(...
%     [pulse_true(:).t_0]<=T_MAX,...
%     [pulse_list(:).t_0]<=T_MAX);
% pulse_true_T_sub = pulse_true([pulse_true(:).t_0]<=T_MAX);
% pulse_list_T_sub = pulse_list([pulse_list(:).t_0]<=T_MAX);
% 
% figure(mainfig)
% set(mainfig, 'currentaxes', axis2);
% for i = 1:numel(pulse_true_T_sub)
%     if sum(found_both_mat_T_sub(i,:))
%         themarker = 'g+';
%     else
%         themarker = 'ro';
%     end
%     plot(pulse_true_T_sub(i).t_0,pulse_true_T_sub(i).fp,themarker)
% end
% 
% %Count the total number of candidate pulses that were rejected
% n_rejected = 0;
% n_accepted = 0;
% for i = 1:numel(Xs)-1
%     n_found_this_seg = numel(Xs(i).ps_pos.clst(Xs(i).ps_pos.cpki,:));
%     n_rej_this_seg   = numel(Xs(i).ps_pos.clst)-n_found_this_seg;
%     n_rejected = n_rejected+n_rej_this_seg;
%     n_accepted = n_accepted+n_found_this_seg;
% end
% n_potential = n_accepted+n_rejected;
% 
% 
% n_TP   = sum(sum(found_both_mat_T_sub)); % True alarms     (True pos)
% n_FP   = numel(pulse_list_T_sub)-n_TP  ; % False positive  (Alarm  - True pos)
% n_FN   = numel(pulse_true_T_sub)-n_TP  ; % False negative  (True   - True pos)
% n_TN   = n_rejected-n_FN               ; % True negative   (No alarms  - False  neg)
% 
% n_true = numel(pulse_true_T_sub);
% n_alarms = numel(pulse_list_T_sub);
% n_true_negatives = n_potential-n_true;
