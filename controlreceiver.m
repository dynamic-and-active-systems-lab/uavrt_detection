function [dataReceived] = controlreceiver(remoteIP,localIPPort,releaseSysObj)
%CONTROLRECEIVER receives control signal data from the 
%via the specified local IP port from the specified remote IP.
%
%This function is defined to receive integer control commands and pass
%those receive integers as output. The remoteIP port is not tunable and is 
%only used on the first call to setup the dsp.UDPReceiver object. Changing 
%it on ubsequent calls will do nothing to change the receiver. The local 
%IP port is tuneable however. This funtion uses persistant variables and 
%must be cleared if subsequent calls are needed to change the remote IP. 
%For example call 
%
%   mycntrl = controlreceiver('127.0.0.1',12345);
%   mynewercntrl = controlreceiver('127.0.0.1',12345);
%   mynewercntrlfromdifferentport = controlreceiver('127.0.0.1',54321);
%   clear channelreceiver
%   cntrlfromnewip = controlreceiver('127.0.0.2',12345);
%
%INPUTS:
%   remoteIP    A string of the remote IP address from which to accept
%               messages
%               Example: '127.0.0.1' - local machine
%                        '0.0.0.0'   - receive from any remote IP
%                        '127.0.0.7' - receive from some other IP on the 
%                                      network
%   localIPPort     Scalar value of the port on which to receive the 
%                   message.
%   releaseSysObj   Logical to release the dsp.UDPReceiver system object 
%
%OUTPUTS:
%   dataReceived    The received real scalar command message passed.
%                   Received messages are int8.
%                   Maximum length is 1025
%
%
%Author:    Michael W. Shafer
%Date:      2022-02-16
%--------------------------------------------------------------------------
   
persistent udpRx
%Reset to clear the buffer of stale data.
if isempty(udpRx)
    udpRx = dsp.UDPReceiver('RemoteIPAddress',remoteIP,...%127.0.0.1',... %Accept all
                            'ReceiveBufferSize',2^6,...%2^16 = 65536, 2^18
                            'MaximumMessageLength',1024,...
                            'MessageDataType','int8',...
                            'IsMessageComplex',false);
end

if ~releaseSysObj
  %  if udpRx.LocalIPPort ~= localIPPort
  %      udpRx.release();
        udpRx.LocalIPPort = localIPPort;
   % end
    dataReceived      = udpRx();
else
    release(udpRx);
    dataReceived = 1;
end

end

