function [sig_template] = gettemplate(X,varargin)
%GETTEMPLATE Generates a time domain template of the the signal template in
%the priori pulsestats object in the waveform passed to the function. The
%returned vector is the template at the waveform's sample rate. The
%caller can request a total number of samples greater than the samples
%required to describe the signal. This is useful if the call will be using
%a DFT on the result and wants a specific number of samples to ensure a
%particular frequency resolutions.
%
%INPUTS:
%   X       A waveform object with a populated ps_pre property
%   samples The number of sample desired in the output. Must be greater
%           than or equal to ceil(X.ps_pre.t_p*X.Fs)
%
%OUTPUTS:
%   sig_template    A vector of the signal amplitude over the samples
%                   requested at the sample rate of the input waveform.
%%
%Author: Michael W. Shafer
%Date:   2021-05-21
%
%%
%Sort out the samples input, if submitted by the caller
if ~isempty(varargin)
    samples = varargin{1};
    if samples<ceil(X.ps_pre.t_p*X.Fs)
        error('UAV-RT: If requesting a specific number of samples, the number of samples must be greater than equal to the number of samples in the template i.e. ceil(Fs*tp).')
    end
else
    samples = [];
end

%Generates a the template in the time domain at the sample rate of the
%waveform.
tmplt_samps  = linspace(0,ceil(X.Fs*X.ps_pre.t_p),numel(X.ps_pre.tmplt));
output_samps = linspace(0,ceil(X.Fs*X.ps_pre.t_p),ceil(X.ps_pre.t_p*X.Fs));
sig_template = interp1(tmplt_samps,...
    X.ps_pre.tmplt,...
    output_samps);

if ~isempty(samples)
    %Generate the extra-zeros needed to pad to get to 'samples' samples
    zero_padding = zeros(1,samples-numel(output_samps));
    sig_template = [sig_template,zero_padding];%Build a rectagular waveform in the time domain with the same number of samples as frequency bins
end

%t = (0:numel(sig_template)-1)/X.Fs;
%A vector of times associated with the output template.
%Useful for plotting in the time domain.

end

