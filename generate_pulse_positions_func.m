% generate_pulse_positions_func.m
function pulse_position_matrix = generate_pulse_positions_func( K, PRI_mean_value, PRI_jitter_value )

% INPUTS:
%   PRI_mean_value          row vector of PRI means (scale/index is STFT step
%                           size)
%
%   PRI_jitter_value        row vector of jitter values (scale/index is STFT step
%                           size)
%
%   K                       number of pulses forming the pattern
%
% OUTPUTS:
%   pulse_position_matrix   row is a pattern; each pattern has K pulse
%                           position values
%
% CALLS: 
%                           cartesion_prod_func()
%

% Author: Paul G. Flikkema
% Date:   1 Oct 2021


num_PRI_means = length( PRI_mean_value );
num_PRI_jitters = length( PRI_jitter_value );
num_PRI_patterns = num_PRI_means*num_PRI_jitters^(K-1);

pulse_position_matrix = zeros( num_PRI_patterns, K );
% place first pulse at pulse position q = 1
pulse_position_matrix( :, 1 ) = ones( num_PRI_patterns, 1 );

% based on the model, generate all the pulse position values in a 3D matrix
% pulse_position_value(k, i_position, i_mean )
pulse_position_value = zeros( K, num_PRI_jitters, num_PRI_means );
pulse_position_value( 1, :, : ) = 1; % first pulse is always in position 1
% loop through the mean PRI values
for i_mean = 1:num_PRI_means
    for k = 2:K
        for i_jitter = 1:num_PRI_jitters
            pulse_position_value( k, i_jitter, i_mean) = ...
                1 + (k-1)*PRI_mean_value(i_mean) + PRI_jitter_value(i_jitter);
        end
    end
end

% generate the pulse_position_matrix by considering
% all possible combinations of the values;
% each row is for one pattern, there are K columns;
% pulse_position_matrix( i_pattern, k)
%
% The number of columns is the number of possible positions
%
% we generate a num_PRI_jitters^(K-1) x K matrix
% using the function cartesian_prod_func
%
% we stack matrices vertically into the pulse_position_matrix
num_position_patterns = num_PRI_means*num_PRI_jitters^(K-1);
pulse_position_matrix = zeros( num_position_patterns, K-1 );

n_rows = num_PRI_jitters^(K-1); % number of rows per PRI mean
for i_set = 1:num_PRI_means
    
%     % DEBUG
%     a = [ 1 1 1 ]; b = [ 309 310 311 ]; c = [ 618 619 620 ];
%     A = [ a; b; c ];

    % since pattern is "fundamental" pattern starting with a pulse in the
    % first STFT window, we only need to look at combinations
    % rows 2:end, and then add the column of ones
    pattern_matrix = cartesian_prod_func( pulse_position_value( 2:end, :, i_set ) );
    pulse_position_matrix( ( (i_set - 1)*n_rows + 1 ):i_set*n_rows, : ) = pattern_matrix;
end
pulse_position_matrix = ...
    horzcat( ones( num_position_patterns, 1 ), pulse_position_matrix );

% remove duplicate patterns
pulse_position_matrix = unique( pulse_position_matrix, 'rows');
    

