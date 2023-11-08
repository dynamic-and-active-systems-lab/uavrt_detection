function [] = wfmcsvfile(filePath)
%UNTITLED5 Summary of this function goes here
%   Detailed explanation goes here


[SpecCell,tCell,fVec,pulseLists] = wfmcsvreadermulti(filePath);

numSegments = numel(SpecCell);

figure
for i = 1:numSegments
    for j = 1:numel(pulseLists(i).t0)
        color = 'r';
        if pulseLists(i).conf == 1
            color = 'g';
        end
        plot(pulseLists(i).t0(j),pulseLists(i).SNR,'o','Color',color);hold on
    end
end


startTime = tCell{1}(1,1);
figure;
surf(tCell{1}-startTime, fVec, 10*log10(SpecCell{1}),'EdgeColor','none');hold on
view([0 90])
prevTime = tCell{1}(end);
for i = 2:numSegments
    mask2Plot = tCell{i} > prevTime;
    currTimeVec = tCell{i};
    times2Plot = currTimeVec(mask2Plot);
    surf(times2Plot - startTime, fVec, 10*log10(SpecCell{i}(:,mask2Plot)),'EdgeColor','none')
    prevTime = tCell{i}(end);

    if ~isnan(pulseLists(i).t0(1))
    for j = 1:numel(pulseLists(i).t0)
        [~, SpecInd_time] = min(abs(tCell{i} - pulseLists(i).t0(j)));%find(t == pl.t0(i),1,'first');
        [~, SpecInd_freq] = min(abs(fVec   - pulseLists(i).fp(j)));%find(f == pl.fp(i),1,'first');
        if pulseLists(i).conf(j)
            ringColor = 'g';
        else
            ringColor = 'r';
        end
        plot3(pulseLists(i).t0(j) - startTime, pulseLists(i).fp(j),10*log10(SpecCell{i}(SpecInd_freq,SpecInd_time)),'o','Color',ringColor,'Markersize',10)
    end
    end
     drawnow
end

   


pause(1);

end