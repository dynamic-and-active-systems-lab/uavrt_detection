function [] = wfmcsvwrite(X,radioFcMHz, filePath)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

fid = fopen(filePath,'w');
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


% for i = 1:numel(X.x)
%     fprintf(fid,'%f,', real(X.x(i)));
% end
% fprintf(fid, '\n');
% for i = 1:numel(X.x)
%     fprintf(fid, '%f,', imag(X.x(i)));
% end
% for i = 1:numel(X.stft.S)
%     fprintf(fid, '%f,', real(X.stft.S(i)));
% end
% fprintf(fid, '\n');
% for i = 1:numel(X.stft.S)
%     fprintf(fid, '%f,', imag(X.stft.S(i)));
% end

end