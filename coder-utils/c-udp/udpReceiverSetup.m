function udpReceiver = udpReceiverSetup(ipAddress, ipPort, bufferSizeInSamples, samplesPerFrame)
	%#codegen
	if coder.target('MATLAB')
		udpReceiver = dsp.UDPReceiver( ...
									'RemoteIPAddress', 		ipAddress, ...
							    	'LocalIPPort',			ipPort, ...
							    	'ReceiveBufferSize',	bufferSizeInSamples * 8, ...   % This is in bytes
							    	'MaximumMessageLength',	samplesPerFrame, ...           % This is in samples
							    	'MessageDataType',		'single', ...
							    	'IsMessageComplex',		true);
	    setup(udpReceiver);
	else
		coder.cinclude('udp.h');
		coder.updateBuildInfo('addSourceFiles', 'udp.cpp');
		udpReceiver = int32(0);
		udpReceiver = coder.ceval('udpReceiverSetup', ipPort);
		if udpReceiver <= 0
			error('udpReceiverSetup failed');
		end
	end
end
