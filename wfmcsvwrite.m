function [] = wfmcsvwrite(X,radioFcMHz, filePath)
%WFMCSVWRITE Saves the spectrogram, pulses, and the spectrogram frequencies
%and times to a file for record keeping and post-flight analysis. 
%
%INPUTS:
%   X   waveform instance
%   radioFcMHz  radio channel center frequency in MHz
%   filePath    file path to write to
%OUTPUTS:
%   none other than the file
%
%Author:    Michael Shafer
%Date:      Fall 2023
%
%--------------------------------------------------------------------------

persistent fid

persistent filePathPersistent

if isempty(fid)
    fprintf('\t Opening new spectro_segment record file.\n.')
    fid = fopen(filePath,'w');
    filePathPersistent = filePath;
elseif ~isempty(fid) & strcmp(filePathPersistent, filePath)
    fprintf('\t Writing to an already open spectro_segment record file.\n.')
    %Do nothing, since we want to write to the same file
elseif ~isempty(fid) & ~strcmp(filePathPersistent, filePath)
    %Close the previously opened file and open a new one with the updated file name
    fprintf('\t Closing existing spectro_segment file and opening a new one with an updated file name.\n.')
    fclose(fid);
    fid = fopen(filePath,'w');
    filePathPersistent = filePath;
end



fprintf(fid, '%s\n','----------------------------------------');
fprintf(fid, '%s\n','Record Start Time (s):');
fprintf(fid, '%f\n', X.t_0);
fprintf(fid, '%s\n','----------------------------------------');
fprintf(fid, '%s\n','Pulse Listing:');
    for i = 1:numel(X.ps_pos.pl)
        fprintf(fid, '%f,', X.ps_pos.pl(i).t_0);
    end
    fprintf(fid, '\n');
    for i = 1:numel(X.ps_pos.pl)
        fprintf(fid, '%f,', X.ps_pos.pl(i).fp/1e6 + radioFcMHz);
    end
    fprintf(fid, '\n');
    for i = 1:numel(X.ps_pos.pl)
        fprintf(fid, '%f,', X.ps_pos.pl(i).SNR);
    end
    fprintf(fid, '\n');
    for i = 1:numel(X.ps_pos.pl)
        fprintf(fid, '%u,', uint8(X.ps_pos.pl(i).con_dec));
    end

fprintf(fid, '\n%s\n','----------------------------------------');
fprintf(fid, '%s\n','Spectrogram Frequencies (MHz):');
for i = 1:numel(X.stft.f)
    fprintf(fid, '%f,', X.stft.f(i)/1e6 + radioFcMHz);
end
fprintf(fid, '\n%s\n','----------------------------------------');
fprintf(fid, '%s\n','Spectrogram Times (s):');
for i = 1:numel(X.stft.t)
    fprintf(fid, '%f,', X.stft.t(i));
end
fprintf(fid, '\n%s\n','----------------------------------------');
fprintf(fid, '%s\n','Spectrogram Values (|STFT|):');
for i = 1:numel(X.stft.S)
    fprintf(fid, '%f,', abs(X.stft.S(i)));
end

fprintf(fid, '\n');


end