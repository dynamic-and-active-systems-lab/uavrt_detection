function [boolOut] = str2bool(stringIn)
%STR2BOOL Converts a string in to a boolean. 
%   This function converts a string to a boolean output. Valid input
%   strings are '1', '0', 'true', or 'false'. The input is case
%   insensitive. If input is invalid, the function returns an empty false
%   of size 0x1. 
%
%INPUTS:
%   stringIn    string of '1', '0', 'true', or 'false', case insensitive.
%
%OUTPUTS:
%   boolOut     boolean
%    
%Author: Michael W. Shafer
%Date:   2022-06-21
%--------------------------------------------------------------------------

    coder.varsize('boolOut',[1 1], [1 0]);

    stringIn = lower(stringIn);

    if strcmp(stringIn,'1') 
        boolOut = true;
    elseif strcmp(stringIn,'0')
        boolOut = false;
    elseif strcmp(stringIn,'true')
        boolOut = true;
    elseif strcmp(stringIn,'false')
        boolOut = false;
    else
        if coder.target('Matlab')
            warning('UAV-RT: input string is not 1, 0, true, or false. Returning empty boolean.')
        end
        boolOut = false(0,1);
    end
                            
end