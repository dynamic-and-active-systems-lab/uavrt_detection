function Wq = assembleWq(PRI_means_q,PRI_jitters_q, K)

pulsePositionMatrix = generate_pulse_positions_func(K, PRI_means_q, PRI_jitters_q );

if K>1
    n_shifts = min(pulsePositionMatrix(:,2))-1;   %The number of shifts necessary. 
else
    n_shifts = max(PRI_means_q)+max(PRI_jitters_q);
end
ppmRows     = size(pulsePositionMatrix, 1);       %Number of rows in pulse_position_matrix
ppmCols     = size(pulsePositionMatrix, 2);       %Number of cols in pulse_position_matrix --- should always be K
ppmBig      = repmat(pulsePositionMatrix, n_shifts, 1); %Create multiple copies of the PPM matrix. Each copy will eventually be shifted. The second copy will get a 1 added to it, the third a 2 added, and so on. 
ppmBigRows  = size(ppmBig,1);                      %Get the number of rows in the big PPM matrix
shiftermat  = repmat(0:n_shifts-1, ppmRows, 1);  %Create a matrix of the shifts needed for each copy of the PPM matrix
WqRowInds   = repmat(shiftermat(:), 1, ppmCols) + ppmBig;
WqColInds   = repmat(1:ppmBigRows,1,ppmCols);
WqElements  = ones(size(WqRowInds));
Wq          = sparse(WqRowInds(:),WqColInds(:),WqElements(:));

end

