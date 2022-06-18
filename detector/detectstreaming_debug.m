function [out] = detectstreaming_debug()

localMode = 'D';
coder.varsize('localMode',[1 inf],[0 1]); %dims 0 if fixed, 1 if variable
localPl = makepulsestruc();
coder.varsize('localPl',[inf 1],[1 0]);
localClst = makepulsestruc();
coder.varsize('localClst',[inf 1],[1 0]);
localCmsk = false;
coder.varsize('localCmsk',[inf 1],[1 0]);
localCpki = NaN;
coder.varsize('localCpki',[inf 1],[1 0]);
localThresh = NaN;
coder.varsize('localThresh',[inf 1],[1 0]);

ps_pre_struc.t_p    = 0;
ps_pre_struc.t_ip   = 0;
ps_pre_struc.t_ipu  = 0;
ps_pre_struc.t_ipj  = 0;
ps_pre_struc.fp     = 0;
ps_pre_struc.fstart = 0;
ps_pre_struc.fend   = 0;
ps_pre_struc.tmplt  = [1 1];
ps_pre_struc.mode   = localMode;
ps_pre_struc.pl     = localPl;
ps_pre_struc.clst   = localClst;
ps_pre_struc.cmsk   = localCmsk;
ps_pre_struc.cpki   = localCpki;
ps_pre_struc.thresh = localThresh;

segmentsProcessed  = 0;
for i = 1:5
    if segmentsProcessed == 0
        ps_pre = pulsestats(0, 0, 0, 0,0 ,0     ,0   ,[1 1],'D' ,makepulsestruc(),makepulsestruc(),false     ,NaN       ,NaN);
        %(tp,              tip,      tipu,       tipj   ,fp,fstart,fend,tmplt,mode,pl              ,clst            ,cmsk      ,cpki      ,thresh)
    else
        ps_pre = pulsestats(ps_pre_struc.t_p, ps_pre_struc.t_ip, ps_pre_struc.t_ipu, ps_pre_struc.t_ipj ,ps_pre_struc.fp ,ps_pre_struc.fstart     ,ps_pre_struc.fend   ,ps_pre_struc.tmplt, ps_pre_struc.mode, ps_pre_struc.pl, ps_pre_struc.clst, ps_pre_struc.cmsk, ps_pre_struc.cpki, ps_pre_struc.thresh);
    end


    ps_pre_struc.t_p    = 1;
    ps_pre_struc.t_ip   = 1;
    ps_pre_struc.t_ipu  = 1;
    ps_pre_struc.t_ipj  = 1;
    ps_pre_struc.fp     = 1;
    ps_pre_struc.fstart = 1;
    ps_pre_struc.fend   = 1;
    ps_pre_struc.tmplt  = [1 1];
    ps_pre_struc.mode   = 'D';
    ps_pre_struc.pl     = makepulsestruc();
    ps_pre_struc.clst   = [makepulsestruc(); makepulsestruc()];
    ps_pre_struc.cmsk   = [false; true];
    ps_pre_struc.cpki   = 1;
    ps_pre_struc.thresh = 15;



    segmentsProcessed = segmentsProcessed + 1;
end
out = 1;    
end