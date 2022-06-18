function [d_lo_all] = bigIQdec(filepath,Fsraw,Fsdec,fshift)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here


% count=inf;
% f = fopen (app.filepath, 'rb');
% if liveflag
%     fseek(f,-bytesneeded,'eof')
% else
%     frewind(f);
% end
% 
% 
% frewind(f)
% tic
% d_lo_all = [];
% d = fread (f, [2, inf], 'float'); %read in img and real parts of file
% d_cmplx = (d(1,:) + d(2,:)*1i);
% segsize = 10000;
% for i = 1:segsize:length(d_cmplx)
%     
%     d_lo = stageddecimate(d_cmplx(i:min([(i+segsize),length(d_cmplx)])),...
%                           Fsraw,Fsdec);
%     d_lo_all = [d_lo_all,d_lo];
% end
% toc
% 
% 

f = fopen (filepath, 'rb');
frewind(f)

d_lo_all = [];
segsize = Fsraw/Fsdec*1000;
i = 1;
s = dir(filepath);
bytesperIQsamp = 8;
IQdecsampoverlap  = 10;
IQsampoverlap  = Fsraw/Fsdec*IQdecsampoverlap;
bytesoverlap  = bytesperIQsamp*IQsampoverlap;
fwait = waitbar(0,'Loading and decimating');
stopflag = 0;

%Nsamps = s.bytes/bytesperIQsamp;
%Tmax  = Nsamps/Fsraw;

if any(fshift>=Fsraw/2)
    warning('Frequency shift requested is larger than the Nyquist frequency. Results will may be not what you intendend. ')
end

while ~stopflag
    curr_file_loc_byte = ftell(f);
    curr_file_loc_samp = curr_file_loc_byte/bytesperIQsamp;%ZERO BASE SAMPLE NUMBER
    %curr_file_loc_time = curr_file_loc_samp/Fsraw;
    
    if i ==1
        d = fread (f, [2, segsize+IQsampoverlap], 'float'); %read in img and real parts of file
    else
        d = fread (f, [2, segsize+2*IQsampoverlap], 'float'); %read in img and real parts of file
    end
    d_cmplx = d(1,:) + d(2,:)*1i;
    
    %currlocation = ftell(f)
    sample_numbers = curr_file_loc_samp+(0:(numel(d_cmplx)-1));
    sample_times = sample_numbers/Fsraw;
    D_CMPLX_SHIFTED = zeros(numel(fshift),numel(d_cmplx));
    for j = 1:numel(fshift)
        if fshift(j)==0
            D_CMPLX_SHIFTED(j,:) = d_cmplx;
        else
            MXR = exp(1i*2*pi*fshift(j)*sample_times);%Zero phase complex exponential
            D_CMPLX_SHIFTED(j,:) = d_cmplx.*MXR;
        end
    end
    %stageddecimate expexts and returns data as column vectors but we have
    %things as row vectors here. 
    if Fsraw==Fsdec %requested no decimation
        d_lo = D_CMPLX_SHIFTED;
    else
        d_lo = transpose(stageddecimate(transpose(D_CMPLX_SHIFTED),Fsraw,Fsdec));
    end
    %d_lo = stageddecimate(d_cmplx,Fsraw,Fsdec);
    
    stopflag = (feof(f) | ftell(f)==s.bytes);
    
    fseek(f,-2*bytesoverlap,'cof');%move memory pointer back by overlap
    
    if i==1
        new_data = d_lo(:,1:end);
    else
        new_data = d_lo(:,1+IQdecsampoverlap:end);
        d_lo_all(:,end-IQdecsampoverlap+1:end) = [];
    end
    
    d_lo_all = [d_lo_all,new_data];
    
    i = i+1;
    fwait = waitbar(ftell(f)/s.bytes,fwait);
end
close(fwait);

fclose (f);

end










