function [] = wfmcsvfolder(folderPath,tagID,startIndex)
%UNTITLED5 Summary of this function goes here
%   Detailed explanation goes here

currDir = pwd();
cd(folderPath);
try
    allFiles = dir('*.csv');
    cd(currDir);
catch
    cd(currDir);
end

%%OLD METHOD OF NAMING CSVS
% str2Match = ['data_record.',num2str(tagID),'_'];
% numChars2Compare = numel(str2Match);
% filesWeWantMask = zeros(numel(allFiles),1);
% for i = 1:numel(allFiles)
%     maxInd = min(numel(allFiles(i).name), numChars2Compare);
%     if strcmp(str2Match, allFiles(i).name(1:maxInd))
%       filesWeWantMask(i) = 1;  
%     end
% end

str2Match = 'spectro_segment';
numChars2Compare = numel(str2Match);
filesWeWantMask = zeros(numel(allFiles),1);
for i = 1:numel(allFiles)
    maxInd = min(numel(allFiles(i).name), numChars2Compare);
    if strcmp(str2Match, allFiles(i).name(1:maxInd)) && ...       %Check it is a spectro_segment
            str2num(allFiles(i).name(end-4)) == startIndex && ... %Check it is the correct startIndex
            str2num(allFiles(i).name(end-6)) == tagID             %Check it is the correct startIndex
      filesWeWantMask(i) = 1;  
    end
end

recordFilesStruct = allFiles(logical(filesWeWantMask));
recordFilesTable = struct2table(recordFilesStruct);
%Assuming the time value in the filename is the only thing that changes
recordFilesTable = sortrows(recordFilesTable,'name', 'ascend');

numFiles = size(recordFilesTable,1);

Specs       = cell(numFiles,1);
times       = cell(numFiles,1);
freqs       = cell(numFiles,1);
pulseLists  = cell(numFiles,1);
for i = 1:numFiles
    fullFilePath = fullfile(recordFilesTable.folder{i},recordFilesTable.name{i});
    [Spec,t,f,pl] = wfmcsvreader(fullFilePath);
    Specs{i} = Spec;
    times{i} = t;
    freqs{i} = f;
    pulseLists{i} = pl;
end

figure
for i = 1:numFiles
    for j = 1:numel(pulseLists{i}.t0)
        color = 'r';
        if pulseLists{i}.conf == 1
            color = 'g';
        end
        plot(pulseLists{i}.t0(j),pulseLists{i}.SNR,'o','Color',color);hold on
    end
end



startTime = times{1}(1);
figure;
surf(times{1}-startTime,freqs{1},10*log10(Specs{1}),'EdgeColor','none');hold on
view([0 90])
prevTime = times{1}(end);
for i = 2:numFiles
    mask2Plot = times{i}>prevTime;
    times2Plot = times{i}(mask2Plot);
    surf(times2Plot - startTime,freqs{i},10*log10(Specs{i}(:,mask2Plot)),'EdgeColor','none')
    prevTime = times{i}(end);

    if ~isnan(pulseLists{i}.t0(1))
    for j = 1:numel(pl.t0)
        [~, SpecInd_time] = min(abs(times{i} - pulseLists{i}.t0(j)));%find(t == pl.t0(i),1,'first');
        [~, SpecInd_freq] = min(abs(freqs{i} - pulseLists{i}.fp(j)));%find(f == pl.fp(i),1,'first');
        if pulseLists{i}.conf(j)
            ringColor = 'g';
        else
            ringColor = 'r';
        end
        plot3(pulseLists{i}.t0(j) - startTime, pulseLists{i}.fp(j),10*log10(Specs{i}(SpecInd_freq,SpecInd_time)),'o','Color',ringColor,'Markersize',10)
    end
    end
     drawnow
end

   


pause(1);

end