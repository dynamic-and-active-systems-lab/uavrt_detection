function [axis1,axis2,axis3] = resultsplot(Xs,zetas,PF,fig_h)
%RESULTSPLOTS Plots the results from the processed waveforms in the
%waformvector Xs
%   This function creates three linked figures. The left figure is the
%   scores for each waveform segment across all frequencies, with peaks
%   color coded by frequency and sidebands highlighted in the same color.
%   Also plotted in this figure are black lines where the decision
%   thresholds were for each waveform segmen.
%   The top figure is the time domain data in Xs(:).s with all peak pulses
%   identified in the same color as the they are in the frequency plot. The
%   main central plot is the frequency-time plot with the identified peaks
%   highlighted with color dots. This can be though of as a highlighting
%   of the STFT result where pulses were identifed. 
%
%INPUTS:
%   Xs      A vector of processed waveform objects
%   zetas   The frequency fractions used for processing Xs
%   PF      The probabiliy of false alarm used for processing
%   fig_h   Where the results should be plotted. This can be empty and will
%           result in this function creating a new figure window. It can
%           also be a figure handle, in which case this function will all
%           the three necessary axes to that figure. Finally, it can be
%           a vector of three axis handles where the results should be
%           plotted. The order would be [left plot, center plot, top plot].
%OUTPUTS:
%   axis1   The axis handle for the score v frequency plot
%   axis2   The axis handle for the time v frequency plot
%   axis3   The axis handle for the time v amplitude plot
%  
%----------------------------------------------------------------------
%Author: Michael W. Shafer
%Date: 2021-07-15
%
%----------------------------------------------------------------------
%%

if isempty(fig_h)
    mainfig = figure;
    t = tiledlayout(mainfig,5,5);
    axis1 = nexttile(t,6,[4,1]);
    axis2 = nexttile(t,7,[4,4]);
    axis3 = nexttile(t,2,[1,4]);
    
elseif strcmp(class(fig_h),'matlab.ui.Figure') %Figure window
    mainfig = figure;
    t = tiledlayout(mainfig,5,5);
    axis1 = nexttile(t,6,[4,1]);
    axis2 = nexttile(t,7,[4,4]);
    axis3 = nexttile(t,2,[1,4]);
    
elseif (isa(fig_h,'matlab.graphics.axis.Axes')||...
        isa(fig_h,'matlab.ui.control.UIAxes')) && numel(fig_h)==3
	axis1 = fig_h(1);
    axis2 = fig_h(2);
    axis3 = fig_h(3);
    
    grid(axis1,'on')
    grid(axis2,'on')
    grid(axis3,'on')
else
    error('UAV-RT: Input handles must be empty, one figure handle, or an array of three axis handles.')
end



%X.setprioridependentprops(X.ps_pre)
%Create dummy weighting matrix call just to get needed frequency vector
[~,Wf] = weightingmatrix(1:Xs(1).n_w,Xs(1).Fs,zetas,'twosided');

SNRs = zeros([size(Xs(1).ps_pos.clst),numel(Xs)]);
for i = 1:numel(Xs)
    SNRs(:,:,i) = reshape([Xs(i).ps_pos.clst.SNR],size(Xs(1).ps_pos.clst,1),size(Xs(1).ps_pos.clst,2));
end

SNR_range_vec = linspace(-20,60);%Min is -20 dB max is 60dB
numel(SNR_range_vec)
SNR_colors_mat = hsv(numel(SNR_range_vec));
%SNR_colors_mat = turbo(numel(SNR_range_vec));%turbo Doesn't seem to work with a
%deployed application
%minSNR = min(SNRs,[],'all');
%maxSNR = max(SNRs,[],'all');
% if minSNR~=maxSNR
%     SNR_range_vec = linspace(minSNR,maxSNR,100);
%     SNR_colors_mat = turbo(numel(SNR_range_vec));
% else
%     SNR_range_vec = [-1000 1000];%Just make black dots if SNR
%     SNR_colors_mat = [0 0 0;0 0 0];
% end


for i = 1:numel(Xs)                 %For each processed segment
   %if ~isnan(Xs(i).ps_pos.cpki)    %Run this if candidates were recorded
        pk_ind = Xs(i).ps_pos.cpki; %Get time index listing of peaks
        candidatelist = Xs(i).ps_pos.clst;%Pulse list candidates for this segment
        msk = Xs(i).ps_pos.cmsk;    %Get sideband mask for this set of pulses
        scores{i} = sum(reshape([candidatelist.yw],size(candidatelist,1),size(candidatelist,2)),2);
        freqs2plot = sort(unique([candidatelist.fp]'));
        
        if i==1%For first index, build the plot window
            
            set(axis1,'YTick',floor(-Xs(i).Fs/2):200:ceil(Xs(i).Fs/2));
            set(axis1,'YLim',[floor(-Xs(i).Fs/2),ceil(Xs(i).Fs/2)]);
            grid(axis1,'on');
            axis1.YLabel.String = 'Frequency from Baseband (Hz)';
            axis1.XLabel.String = 'z-score (V^2)';
            set(axis1,'xscale','log')
            
            set(axis2,'YTick',get(axis1,'YTick'));
            set(axis2,'YTickLabel',{});
            set(axis2,'XLim',[Xs(1).t_0,Xs(end).t_f]);
            grid(axis2,'on');
            axis2.XLabel.String = 'Time (s)';
            
            set(axis3,'XTick',get(axis2,'XTick'));
            set(axis3,'XTickLabel',{});
            axis3.YLabel.String = 'Amplitude';
            axis3.YLimMode = 'auto';
            grid(axis3,'on');
            linkaxes([axis1 axis2],'y')
            linkaxes([axis2 axis3],'x')
            hold(axis3,'on')
            hold(axis2,'on')
            hold(axis1,'on')
        end
        %else
        %    set(0, 'currentfigure', mainfig);
        %end
        %set(mainfig, 'currentaxes', axis1);
%         %Plot the true pulse frequencies with a horizontal line for
%         %reference
%         if i==1
%             for z = 1:numel(Fp)
%                 yline(Fp(z),'-','Color',0*[1 1 1])
%                 hold on
%             end
%         end
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
        plot(axis1,scores{i},freqs2plot,'Color',[0.6 0.6 0.6]);
        hold(axis1,'on')
        if ~isnan(pk_ind)
            for p = 1:size(msk,2)
                plot(axis1,scores{i}.*msk(:,p),freqs2plot,'Linewidth',2,'Color',peakcolors(p,:));
                hold(axis1,'on')
                %plot(axis1,scores{i}(pk_ind(p)),freqs2plot(pk_ind(p)),'o','Markersize',10,'Color',peakcolors(p,:));hold on
            end
        end
        %set(gca,'xscale','log')
        
        %Plot the freq-time bins of candidate pulses in the temporal plot
        %set(mainfig, 'currentaxes', axis2);
        scores_normalized = (scores{i}-min(scores{i}))/max(scores{i});
        for p = 1:size(candidatelist,1)
            for o = 1:size(candidatelist,2)
                %Only plot if this frequency was processed
                if ~isnan(candidatelist(p,o).yw) &&  any(Xs(i).ps_pos.cpki==p)%candidatelist(p,o).det_dec
                    t0 = candidatelist(p,o).t_0;
                    tf = candidatelist(p,o).t_f;
                    f0 = candidatelist(p,o).fstart;
                    ff = candidatelist(p,o).fend;
                    %pg{i}(p,o) = polyshape([t0 tf tf t0],[ff ff f0 f0]); hold on
                    %ps{i}(p,o) = plot(axis2,pg{i}(p,o));hold on
                    ps{i}(p,o) = plot(axis2,(t0+tf)/2,(f0+ff)/2,'o','Markersize',5); 
                    hold(axis2,'on')
                end
            end
        end
        %SNR_range = -20:60
        %SNR_colors = jet()
        %Highlight the peaks with colors
        for p = 1:size(candidatelist,1)
            for o = 1:size(candidatelist,2)
                %Only plot if this frequency was processed
                if ~isnan(candidatelist(p,o).yw) && any(Xs(i).ps_pos.cpki==p)%candidatelist(p,o).det_dec
                    if any(p==pk_ind)%this is a peak pulse group
                        whichpeak = find(p==pk_ind);
                        if isa(ps{i}(p,o),'matlab.graphics.primitive.Polygon')
                            ps{i}(p,o).FaceColor = peakcolors(whichpeak,:);
                            ps{i}(p,o).EdgeColor = peakcolors(whichpeak,:);
                            ps{i}(p,o).EdgeAlpha = 1;
                            ps{i}(p,o).FaceAlpha = 0.8;
                        elseif isa(ps{i}(p,o),'matlab.graphics.chart.primitive.Line')
                            %ps{i}(p,o).MarkerFaceColor = peakcolors(whichpeak,:);
                            %ps{i}(p,o).MarkerEdgeColor = peakcolors(whichpeak,:);
                            
                            if isreal(candidatelist(p,o).SNR) && candidatelist(p,o).SNR>=-20 && candidatelist(p,o).SNR<=60;
                                SNRcolor = interp1(SNR_range_vec,SNR_colors_mat,candidatelist(p,o).SNR);
                                
                            else
                                SNRcolor = [0 0 0];
                            end
                           
                            ps{i}(p,o).MarkerFaceColor = SNRcolor;
                            ps{i}(p,o).MarkerEdgeColor = SNRcolor;
                        end
                    else %this isn't a peak pulse group
                        if any(msk(p,:))
                            whichpeakassociated = find(msk(p,:));
                            if isa(ps{i}(p,o),'matlab.graphics.primitive.Polygon')
                                ps{i}(p,o).FaceColor = peakcolors(whichpeakassociated,:);
                                ps{i}(p,o).EdgeColor = peakcolors(whichpeakassociated,:);
                            elseif isa(ps{i}(p,o),'matlab.graphics.chart.primitive.Line')
                                ps{i}(p,o).MarkerFaceColor = peakcolors(whichpeakassociated,:);
                                ps{i}(p,o).MarkerEdgeColor = peakcolors(whichpeakassociated,:);
                            end
                        else
                            if isa(ps{i}(p,o),'matlab.graphics.primitive.Polygon')
                                ps{i}(p,o).FaceColor = 0.6*[1 1 1];
                                ps{i}(p,o).EdgeColor = 0.6*[1 1 1];
                            elseif isa(ps{i}(p,o),'matlab.graphics.chart.primitive.Line')
                                ps{i}(p,o).MarkerFaceColor = 0.6*[1 1 1];
                                ps{i}(p,o).MarkerEdgeColor = 0.6*[1 1 1];
                            end
                        end
                        if isa(ps{i}(p,o),'matlab.graphics.primitive.Polygon')
                        ps{i}(p,o).EdgeAlpha = 0.4;
                        ps{i}(p,o).FaceAlpha = 0.1;
                        end
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
        plot(axis2,[Xs(i).t_0,Xs(i).t_f],max(get(axis2,'YLim'))*[1 1],'Linewidth',5,'Color',mode_color)
        plot(axis2,[Xs(i).t_0,Xs(i).t_f],min(get(axis2,'YLim'))*[1 1],'Linewidth',5,'Color',mode_color)
        drawnow
        
        
        %set(mainfig, 'currentaxes', axis3);
        
        t_temp = Xs(i).t;
        x_temp = Xs(i).x;
        plot(axis3,t_temp,real(x_temp),'Color',[0.8 0.8 0.8])
        for p = 1:numel(Xs(i).ps_pos.cpki)
            pk_ind = Xs(i).ps_pos.cpki(p);
            if ~isnan(pk_ind) 
            for k = 1:size(Xs(i).ps_pos.clst,2)
                curr_msk = t_temp>=Xs(i).ps_pos.clst(pk_ind,k).t_0 &...
                            t_temp<=Xs(i).ps_pos.clst(pk_ind,k).t_f;
                plot(axis3,t_temp(curr_msk),real(x_temp(curr_msk)),'Linewidth',2,'Color',peakcolors(p,:));
                hold(axis3,'on')
            end
            end
        end
       
    %end 
end

%Plot the decision thresholds used
%load('decision_database.mat')
thresh_matrix = zeros(numel(Wf),numel(Xs));
%decision_entry = decision_initialize(Xs(1).Fs,Xs(1).K,Xs(1).ps_pre.t_p,Xs(1).ps_pre.t_ip,Xs(1).ps_pre.t_ipu,Xs(1).OLF,zetas);
for i = 1:numel(Xs)
    if strcmp(Xs(i).ps_pre.pl(1).mode,'D') ||...
        strcmp(Xs(i).ps_pre.pl(1).mode,'C') 
        timesearchmode = 'naive';
        linetype = '--';
    else
         timesearchmode = 'informed';
         linetype = '-';
    end
%    thresh = getthreshold(Xs(i),PF,decision_entry,timesearchmode);
    %set(mainfig, 'currentaxes', axis1);
 %   xline(axis1,thresh,linetype)
    thresh_matrix(:,i) = Xs(i).ps_pos.thresh;
end
%plot(axis1,Xs(i).ps_pos.thresh,Wf)
plot(axis1,mean(thresh_matrix,2),Wf,'-','Linewidth',2,'Color','k')

grid(axis1,'on')
grid(axis2,'on')
grid(axis3,'on')

isimaglogic = true;
for i = 1:numel(Xs)
    isimaglogic = isimaglogic & all(~isreal(Xs(i).x));
end
maxfreq = max(get(axis1,'YLim'));
if ~isimaglogic
    set(axis1,'YLim',[0 maxfreq])
    set(axis2,'YLim',[0 maxfreq])
end

end

