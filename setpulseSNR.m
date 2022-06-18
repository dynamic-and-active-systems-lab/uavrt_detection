function [] = setpulseSNR(Xs)

for k = 1:numel(Xs)
    freqs  = sum(~isnan(Xs(k).ps_pos.cpki(:)));% Used to be numel(Xs(k).ps_pos.cpki) but this will be 1 if cpki contains a Nan value.
    pulses = size(Xs(k).ps_pos.clst,2);
    n      =  numel(Xs(k).x);
    pulse_msk = false(freqs,n);
    
    t = Xs(k).t;
    for i = 1:freqs
        freq_ind = Xs(k).ps_pos.cpki(i);
        t_pad = 0.25*Xs(k).ps_pos.t_p;%Window step size has 80% overlap so pad by a little more than 20%
        for j = 1:pulses %Number of columns (pulses K)
%             if [k, i,j]==[2 1 1] 
%                 pause(1)
%             end
            
            pulse_msk(i,:) = pulse_msk(i,:) |...
                (t >=Xs(k).ps_pos.clst(freq_ind,j).t_0 - t_pad &...
                 t <=Xs(k).ps_pos.clst(freq_ind,j).t_f + t_pad) ;
        end
    end
    
    pulse_msk_all = any(pulse_msk,1);
    
    IQ_data_energy = real(Xs(k).x).^2+imag(Xs(k).x).^2;% abs(Xs(k).x).^2 Produces same result but is ~2x slower
    
    SNR_star = -inf*ones(1,freqs);
    SNR      = -inf*ones(1,freqs);
    P_N  = sum(IQ_data_energy(~pulse_msk_all))/sum(~pulse_msk_all);
    
    for i = 1:freqs
        freq_msk = false(1,freqs);
        freq_msk(i) = true;
        mask_of_pulses_at_other_freqs = any(pulse_msk(~freq_msk,:),1);
        E_SN_ith_freq = sum(IQ_data_energy(~mask_of_pulses_at_other_freqs));
        
        P_SN = E_SN_ith_freq/sum(~mask_of_pulses_at_other_freqs);
        Ft_N = sum(~pulse_msk_all)/numel(IQ_data_energy);
        %Ft_S = 1-Ft_N;
        Ft_S = sum(pulse_msk(i,:))/numel(IQ_data_energy);
        P_S = P_SN-P_N;
        %SNR During Transmissions:
        SNR_star(i) = 10*log10((P_S*1/Ft_S)/P_N); %Step 10 and Step 9
        %SNR Over Entire Data Record
        SNR(i) = 10*log10(P_S/P_N); %Step 11
        freq_ind = Xs(k).ps_pos.cpki(i);
        for j = 1:pulses
            Xs(k).ps_pos.clst(freq_ind,j).SNR = SNR_star(i);
            %Don't need to update the values in ps_pos.pl because pulses are
            %handle objects and updating the pulse in clst and pl are the same
            %object.
        end
    end
end
end

