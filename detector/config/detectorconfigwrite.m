function [] = detectorconfigwrite(configPath, configStr, writeType)
%DETECTORCONFIGWRITE Writes the detector configuration string passed to it
%to the path passed to it. 
%
%INPUTS:
%   configPath      String of full path to config file, including the file
%                   name and extension
%   configStr       String for writing into the config file. 
%   writeType       Char of either 'a' to append to existing file or 'w' to
%                   write. 'w' will overwrite file if it already exists.
%
%OUTPUTS:
%   none
%
%
%Author:    Michael W. Shafer
%Date:      2022-02-11
%
%--------------------------------------------------------------------------
%

if ~strcmp(writeType,'w') && ~strcmp(writeType,'a')
    if coder.target('MATLAB')
       warning('writeType argument must be either a (append) or w (overwrite existing file).') 
    end
end

fid = fopen(configPath, writeType);
fprintf(fid,configStr);
fclose(fid);

end

