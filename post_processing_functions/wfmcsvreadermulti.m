function [SpecCell,t,f,plList] = wfmcsvreadermulti(filePath)
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here

%lineLocs = gettextfilelinelocs(filePath);
fileAsCharArray = fileread(filePath);
[newLineStartIndices,~] = regexp(fileAsCharArray,'\n');
numLines = numel(newLineStartIndices);


[recordStartStartIndices,~] = regexp(fileAsCharArray,'Record');
numSegments = numel(recordStartStartIndices);

% fid = fopen(filePath,'r');
% numSegments = 0;
% fWait = waitbar(0,'Scanning file Data...');
% while ~feof(fid)
%     lineStr = fgetl(fid);
%     if strcmp(lineStr,'Record Start Time (s):')
%         numSegments = numSegments+1;
%     end
%     waitbar(i/numLines,fWait,['Scanned ',num2str(i),' out of ',num2str(numLines),' lines.'])
% end
% close(fWait)

fid = fopen(filePath,'r');

t0 = zeros(numSegments,1);
pl.t0 = [];
pl.fp = [];
pl.SNR = [];
pl.conf = [];
plList = repmat(pl,numSegments,1);
numRead = 1;
fWait = waitbar(0,'Importing Data...');
for i = 1:numLines
    lineStr = fgetl(fid);
    if strcmp(lineStr,'Record Start Time (s):')
        t0_string = fgetl(fid);
        t0Cell = textscan(t0_string,'%f');
        t0(numRead) = t0Cell{1};
    elseif strcmp(lineStr,'Pulse Listing:')
        pl_t0_string = fgetl(fid);
        pl_t0_cell = textscan(pl_t0_string,'%f,');
        pl_fp_string = fgetl(fid);
        pl_fp_cell = textscan(pl_fp_string,'%f,');
        pl_SNR_string = fgetl(fid);
        pl_SNR_cell = textscan(pl_SNR_string,'%f,');
        pl_conf_string = fgetl(fid);
        pl_conf_cell = textscan(pl_conf_string,'%u,');
        pl.t0 = pl_t0_cell{1};
        pl.fp = pl_fp_cell{1};
        pl.SNR = pl_SNR_cell{1};
        pl.conf = pl_conf_cell{1};
        plList(numRead) = pl;
    elseif strcmp(lineStr,'Spectrogram Frequencies (MHz):')
        f_string = fgetl(fid);
        fcell = textscan(f_string,'%f,');
        numFreqs = numel(fcell{1});
        %Frequencies should be the same for all entries
        if numRead ==1 
            f = fcell{1};
        end
    elseif strcmp(lineStr,'Spectrogram Times (s):')
        t_string = fgetl(fid);
        tcell = textscan(t_string,'%f,');
        numTimes = numel(tcell{1});
        if numRead == 1
            t = cell(numSegments,1);
        end
        try
        t{numRead} = tcell{1};
        catch
            pause(1)
        end
    elseif strcmp(lineStr,'Spectrogram Values (|STFT|):')
        Spec_string = fgetl(fid);
        SpecVec = textscan(Spec_string,'%f,');
        numSpecVec = numel(SpecVec{1});
        if numFreqs * numTimes ~= numSpecVec
            error('UAV-RT: Numer of frequency times number of time elements does not equal number of spectrogram elements')
        end
        if numRead == 1
            SpecCell = cell(numSegments,1);
        end
        SpecCell{numRead} = reshape(SpecVec{1},numFreqs,numTimes);
        numRead = numRead + 1;
    end
    waitbar(numRead/numSegments,fWait,['Imported ',num2str(numRead),' out of ',num2str(numSegments),' segments.'])
end
close(fWait)

fclose(fid);


end