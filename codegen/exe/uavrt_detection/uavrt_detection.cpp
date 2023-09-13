//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: uavrt_detection.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 13-Sep-2023 10:17:59
//

// Include Files
#include "uavrt_detection.h"
#include "AsyncBuffer.h"
#include "AsyncBuffercgHelper.h"
#include "ComplexSingleSamplesUDPReceiver.h"
#include "DetectorConfig.h"
#include "all.h"
#include "blockedSummation.h"
#include "datetime.h"
#include "diff.h"
#include "eml_int_forloop_overflow_check.h"
#include "fgetl.h"
#include "fileManager.h"
#include "find.h"
#include "fseek.h"
#include "ftell.h"
#include "fwrite.h"
#include "ifWhileCond.h"
#include "indexShapeCheck.h"
#include "makepulsestruc.h"
#include "pulsestats.h"
#include "ref.h"
#include "rt_nonfinite.h"
#include "sprintf.h"
#include "str2double.h"
#include "str2matrix.h"
#include "strcmp.h"
#include "string1.h"
#include "strtok.h"
#include "threshold.h"
#include "tic.h"
#include "toc.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_initialize.h"
#include "uavrt_detection_internal_types.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "validate_print_arguments.h"
#include "validator_check_size.h"
#include "waveform.h"
#include "waveformcopy.h"
#include "wfmcsvwrite.h"
#include "wfmstft.h"
#include "wgn.h"
#include "coder_array.h"
#include "omp.h"
#include "stdio.h"
#include "time.h"
#include "udp.h"
#include "unistd.h"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <stdexcept>
#include <string>

// Function Declarations
static void b_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void b_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum);

static void d_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void e_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void
interleaveComplexVector(const coder::array<creal32_T, 1U> &complexDataIn,
                        coder::array<float, 1U> &interleaveDataOut);

static void
updatebufferreadvariables(const coder::b_captured_var &Config,
                          const coder::c_captured_var &stftOverlapFraction,
                          coder::c_captured_var &overlapSamples,
                          coder::c_captured_var &sampsForKPulses,
                          const pulsestats *ps_input);

static void updateconfig(coder::b_captured_var &Config,
                         const coder::captured_var &configPath);

// Function Definitions
//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void b_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "fopen(\'all\') is not supported for code generation.";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// Arguments    : const char *r
//                const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void b_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((outStream << "Value must be less than ") << r) << ".";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void d_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Value must be positive.";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void e_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Value must be nonnegative.";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// This function takes a vector of complex values, and interleaves
// the real and complex parts to generate a output vector of 2x the
// number of elements as the number of rows of the input.
//
// Arguments    : const coder::array<creal32_T, 1U> &complexDataIn
//                coder::array<float, 1U> &interleaveDataOut
// Return Type  : void
//
static void
interleaveComplexVector(const coder::array<creal32_T, 1U> &complexDataIn,
                        coder::array<float, 1U> &interleaveDataOut)
{
  coder::array<float, 2U> dataMatrix;
  coder::array<float, 1U> varargin_1;
  coder::array<float, 1U> varargin_2;
  int loop_ub;
  //  function [mavlinkTunnelMsgUint8] = formatPulseForTunnel(target_system_in,
  //  target_component_in, payload_type_in, pulseStructIn)
  //       %% Build PulsePose Mavlink Tunnel Message Payload
  //       %Typecast maintains little-endian, in line
  //       %with the mavlink serialization standard:
  //       https://mavlink.io/en/guide/serialization.html target_system        =
  //       dec2hex(typecast(uint8(target_system_in),'uint8'), 2); %uint8
  //       target_component     =
  //       dec2hex(typecast(uint8(target_component_in),'uint8'), 2); %uint8
  //       payload_type         =
  //       dec2hex(typecast(uint16(payload_type_in),'uint8'), 2); %uint16
  //       %payload_length      = dec2hex(typecast(uint8(0),'uint8'), 2); %uint8
  //       id                   =
  //       dec2hex(typecast(uint32(pulseStructIn.tag_id),'uint8'), 2);   %uint32
  //       freq                 =
  //       dec2hex(typecast(double(pulseStructIn.frequency),'uint8'), 2);
  //       %uint32 start_time_sec       =
  //       dec2hex(typecast(int32(pulseStructIn.start_time.sec),'uint8'), 2);
  //       %int32 start_time_nanosec   =
  //       dec2hex(typecast(uint32(pulseStructIn.start_time.nanosec),'uint8'),
  //       2);           %uint32 predict_next_sec     =
  //       dec2hex(typecast(int32(pulseStructIn.predict_next_start.sec),'uint8'),
  //       2);        %int32 predict_next_nanosec =
  //       dec2hex(typecast(uint32(pulseStructIn.predict_next_start.nanosec),'uint8'),
  //       2);   %uint32 snr                  =
  //       dec2hex(typecast(double(pulseStructIn.snr),'uint8'), 2); %double
  //       stft_score           =
  //       dec2hex(typecast(double(pulseStructIn.stft_score),'uint8'), 2);
  //       %double group_ind            =
  //       dec2hex(typecast(uint16(pulseStructIn.group_ind),'uint8'), 2);
  //       %uint16 detection_status     =
  //       dec2hex(typecast(uint8(pulseStructIn.detection_status),'uint8'), 2);
  //       %uint8 confirmed_status     =
  //       dec2hex(typecast(uint8(pulseStructIn.confirmed_status),'uint8'), 2);
  //       %uint8 noise_psd            =
  //       dec2hex(typecast(double(pulseStructIn.noise_psd),'uint8'), 2);
  //       %double
  //
  //       payload_hex = [id; freq; start_time_sec; start_time_nanosec; ...
  //                  predict_next_sec; predict_next_nanosec; snr; ...
  //                  stft_score; group_ind; detection_status; ...
  //                  confirmed_status; noise_psd];
  //       payload_length =
  //       dec2hex(typecast(uint8(size(payload_hex,1)),'uint8'),2);
  //       mavlinkTunnelMsgHex = [target_system; target_component; ...
  //                              payload_type; payload_length;...
  //                              payload_hex];
  //       mavlinkTunnelMsgUint8 = uint8( hex2dec( mavlinkTunnelMsgHex ) );
  //  end
  // Enforce column vector
  varargin_1.set_size(complexDataIn.size(0));
  loop_ub = complexDataIn.size(0);
  varargin_2.set_size(complexDataIn.size(0));
  for (int i{0}; i < loop_ub; i++) {
    varargin_1[i] = complexDataIn[i].re;
    varargin_2[i] = complexDataIn[i].im;
  }
  if (varargin_2.size(0) != varargin_1.size(0)) {
    cb_rtErrorWithMessageID(pb_emlrtRTEI.fName, pb_emlrtRTEI.lineNo);
  }
  dataMatrix.set_size(2, varargin_1.size(0));
  loop_ub = varargin_1.size(0);
  for (int i{0}; i < loop_ub; i++) {
    dataMatrix[2 * i] = varargin_1[i];
    dataMatrix[2 * i + 1] = varargin_2[i];
  }
  loop_ub = dataMatrix.size(1) << 1;
  interleaveDataOut.set_size(loop_ub);
  for (int i{0}; i < loop_ub; i++) {
    interleaveDataOut[i] = dataMatrix[i];
  }
  // Interleave
}

//
// This function updates the buffer reading variables as needed by
// the priori information about the pulse statistics. The segment
// lengths depend on the interpulse duration and uncertainty
// parameters.
//
// Arguments    : const coder::b_captured_var &Config
//                const coder::c_captured_var &stftOverlapFraction
//                coder::c_captured_var &overlapSamples
//                coder::c_captured_var &sampsForKPulses
//                const pulsestats *ps_input
// Return Type  : void
//
static void
updatebufferreadvariables(const coder::b_captured_var &Config,
                          const coder::c_captured_var &stftOverlapFraction,
                          coder::c_captured_var &overlapSamples,
                          coder::c_captured_var &sampsForKPulses,
                          const pulsestats *ps_input)
{
  b_waveform X0;
  pulsestats lobj_2;
  double J;
  double M;
  double N;
  double a__2;
  double n_ol;
  unsigned int u;
  unsigned int u1;
  unsigned int u2;
  // persistent X0
  // if isempty(X0)
  // Build an empty waveform just so that we can calculate number
  // of overlapSamples. This is needed for buffer operations
  // X0 = waveform([], Config.Fs, 0, pulsestats, stftOverlapFraction);
  // UNTITLED2 Construct an instance of this class
  //    Detailed explanation goes here
  // WAVEFORM Constructs an instance of this class
  // INPUTS:
  //    x       1xn     Vector of samples
  //    Fs      1x1     Sample frequency (Hz)
  //    t_0     1x1     Time stamp of first element (s)
  // 	ps_pre  1x1     Pulse stats object from previous data (priori)
  //    OLF     1x1     Overlap fraction as decimal (0.5 = 50%
  //                    overlap)
  // OUTPUTS:
  //    obj             The waveform object
  //             %%
  // Flatten input to row
  // Data vector
  // Elements in the data
  X0.Fs = Config.contents.Fs;
  // Sample rate
  // Time stamp of first element
  // Time stamp of last element
  // This is the time when next
  // segment should start to
  // ensure sufficient overlap.
  // Will need to be updated
  // elsewhere.
  // Overlap Fraction for STFT
  // Unknown number of pulses.
  // WFMSTFT Constructs and returns an instance of this class
  //
  // An waveform object must be passed to this construction method
  // so that the constructor has access to the data vector, desired
  // overlap fraction, and priori pulse data, which is used to
  // develop the window sizes.
  // INPUTS:
  //    waveform_obj   A single waveform object with prior
  //                   dependent properties set.
  // OUTPUTS:
  //    obj             A wfmstft object
  //             %%
  //
  // The following are variable sized properties. To tell coder
  // that they may vary setup as a local variable size variable
  // first, then set.
  // Instructions on
  // https://www.mathworks.com/help/simulink/ug/how-working-with-matlab-classes-is-different-for-code-generation.html
  // maxFs*maxpulsewidth
  // Now actually assign them
  // Unknown values but set types
  // Copy over ps_
  // COPY Creates an exact copy of the pulse stats object as a separate object
  lobj_2.b_init(ps_input->t_p, ps_input->t_ip, ps_input->t_ipu, ps_input->t_ipj,
                ps_input->fp, ps_input->fstart, ps_input->fend, ps_input->tmplt,
                ps_input->mode, ps_input->pl, ps_input->clst, ps_input->cmsk,
                ps_input->cpki);
  // ,...
  // obj.thresh);
  // Current stats are same as previous during construction
  // obj.ps_pos = pulsestats();%TESTING FOR CODER - NEEDS TO BE REVERTED BACK TO
  // LAST LINE obj.TimeCorr = TemporalCorrelator(10, 0, 0);%Generate a
  // temporalcorrelator object so coder knows the type of the object
  // SETPRIORIDEPENDENTVARS updates the properties in the
  // waveform that are dependent on properties in a pulsestats
  // object.
  //
  // INPUTS:
  //    obj     waveform object
  //    ps_obj  a pulse stats object
  // OUTPUTS:
  //    None (This method modifies the waveform object properties)
  //
  //             %%
  // GETPRIORIDEPENDENTVARS returns the properties in the
  // waveform that are dependent on prior pulse data estimates. It
  // depends on the waveform properties list Fs etc, as well as
  // pulse stats like t_ip, etc.
  // INPUTS:  ps_obj  1x1 pulse stats object
  // OUTPUTS:  pulse stats object
  // WHAT WAS DONE BY THIS METHOD IS NOW DONE BY A METHOD OF THE
  // PULSESTATS CLASS.
  //          function [] = update_posteriori(obj,pulselist)
  //              %UPDATE_POSTERIORI updates the posteriori pulse statistics of
  //              %this waveform object using the new pulse list (input) and the
  //              %apriori stats. The pulse contained in the waveform's ps_pos
  //              %property is not used directly so that the caller can decide
  //              %which pulses on which to focus the posteriori.
  //
  //              t_found    = [pulselist(:).t_0]';
  //              freq_found = mean([pulselist(:).fp],'omitnan');
  //
  //              %Create a vector of bandwidths from the pulselist
  //              bw_found =
  //              2*(mean([pulselist.fend],'omitnan')-mean([pulselist.fstart],'omitnan'));
  //              if isempty(bw_found)
  //                  bw_found = 100;
  //                  if coder.target('MATLAB')
  //                      warning(['UAV-R: No bandwidth could be calculated
  //                      ',...
  //                           'from the start and stop frequencies of the ',...
  //                           'identified pulses. A bandwidth of 100 Hz ',...
  //                           'will be used for continued informed search.'])
  //                  end
  //              end
  //
  //              %Here is where we update the stats. These methods of updates
  //              %could be improved in the future.
  //              %obj.ps_pre.t_p; %tp doesn't change. We assume it is
  //              stationary
  //
  //              if numel(pulselist)==1% Happens if K=1
  //                  %We only have one pulse to reference, so we need to check
  //                  %the prior pulse too.
  //                  if ~isempty(obj.ps_pre.pl) &&
  //                  ~isnan(obj.ps_pre.pl(end).t_0)
  //                      recent_tip = pulselist.t_0-obj.ps_pre.pl(end).t_0;
  //                      %There could be a case where the last segment and this
  //                      %segement identified the same pulse. In this case
  //                      %recent_tip will be very small. In this case, we just
  //                      %say we learned nothing about t_ip in this segment.
  //                      if recent_tip < obj.ps_pre.t_ipu + obj.ps_pre.t_ipJ
  //                          recent_tip = NaN;
  //                      end
  //                  else
  //                      %No new information because we don't know the last
  //                      %pulse time
  //                      recent_tip = NaN;
  //                  end
  //              else
  //                  recent_tip = diff(t_found);
  //              end
  //              %Do a check here to make sure the new tip isn't a huge change.
  //              %This could potentially happen if we are in the K = 1 case and
  //              %the block getting processed contained two pulses, with the
  //              %latter pulse getting identified/detected. The lines above
  //              %would look back to the last identified pulse and it might be
  //              %2*tip back in time, producing a very large recenttip values.
  //              %If something like this happens, we ignore it so it doesn't
  //              %affect our new tip estimates.
  //              if recent_tip > 1.5*obj.ps_pre.t_ip & recent_tip <
  //              0.5*obj.ps_pre.t_ip
  //                  recent_tip = NaN;
  //              end
  //
  //              %Only update time parameters if we are in tracking mode. If we
  //              %aren't, we may have identified somethign that isn't a pulse
  //              if strcmp(obj.ps_pos.mode,'T') || strcmp(obj.ps_pre.mode,'T')
  //                  obj.ps_pos.t_ip  =
  //                  mean([recent_tip;obj.ps_pre.t_ip],'omitnan');
  //                  obj.ps_pos.t_ipu = obj.ps_pre.t_ipu; %Don't update this
  //                  because it can get too
  //                  narrow.%mean([3*std(diff(t_found));obj.ps_pre.t_ipu]);
  //                  obj.ps_pos.t_ipj = obj.ps_pre.t_ipj;
  //              end
  //              fp_pos           =
  //              freq_found;%nanmean([freq_found;obj.ps_pre.fp]);%Previous fc
  //              may be nan if unknown obj.ps_pos.fp    = fp_pos;
  //              obj.ps_pos.fstart = fp_pos-bw_found/2;
  //              obj.ps_pos.fend   = fp_pos+bw_found/2;
  //
  //              obj.ps_pos.psdHist = obj.stft.psd
  //          end
  // Samples per pulse
  // Number of elements in STFT window
  // Number of elements overlap in STFT window
  // Number of elements in each step of STFT
  // Time of each step of STFT
  // Samples per pulse
  // Number of elements in STFT window
  // Number of elements overlap in STFT window
  // Number of elements in each step of STFT
  // Time of each step of STFT
  // Samples of interpulse duration
  // Baseline interpulse duration in units of STFT windows
  // Interpulse duration deviation from baselines in units of STFT windows
  // Amount of deviation from the PRI means to search
  //              if K ~= 1
  //                  samplesforKpulses = n_ws*(K*(N+M)-2*M)+n_ol;
  //              else
  //                  samplesforKpulses = n_ws*(N+M+J+1)+n_ol;
  //              end
  // See 2022-07-11 for updates to samples def
  // obj.t_nextsegstart  = obj.t_0+(samplesforKpulses)/obj.Fs; %Don't need the
  // overlap here since the next segment starts at samplesforKpulses+n_ol-n_ol
  // from current sample Don't need the overlap here since the next segment
  // starts at samplesforKpulses+n_ol-n_ol from current sample
  //              if isempty(obj.TimeCorr)
  //                  obj.TimeCorr = TemporalCorrelator(N, M, J);
  //              else
  //                  obj.TimeCorr.update(N, M, J);
  //              end
  // end
  // X0.ps_pre = ps_pre;
  // SETPRIORIDEPENDENTVARS updates the properties in the
  // waveform that are dependent on properties in a pulsestats
  // object.
  //
  // INPUTS:
  //    obj     waveform object
  //    ps_obj  a pulse stats object
  // OUTPUTS:
  //    None (This method modifies the waveform object properties)
  //
  //             %%
  // GETPRIORIDEPENDENTVARS returns the properties in the
  // waveform that are dependent on prior pulse data estimates. It
  // depends on the waveform properties list Fs etc, as well as
  // pulse stats like t_ip, etc.
  // INPUTS:  ps_obj  1x1 pulse stats object
  // OUTPUTS:  pulse stats object
  // WHAT WAS DONE BY THIS METHOD IS NOW DONE BY A METHOD OF THE
  // PULSESTATS CLASS.
  //          function [] = update_posteriori(obj,pulselist)
  //              %UPDATE_POSTERIORI updates the posteriori pulse statistics of
  //              %this waveform object using the new pulse list (input) and the
  //              %apriori stats. The pulse contained in the waveform's ps_pos
  //              %property is not used directly so that the caller can decide
  //              %which pulses on which to focus the posteriori.
  //
  //              t_found    = [pulselist(:).t_0]';
  //              freq_found = mean([pulselist(:).fp],'omitnan');
  //
  //              %Create a vector of bandwidths from the pulselist
  //              bw_found =
  //              2*(mean([pulselist.fend],'omitnan')-mean([pulselist.fstart],'omitnan'));
  //              if isempty(bw_found)
  //                  bw_found = 100;
  //                  if coder.target('MATLAB')
  //                      warning(['UAV-R: No bandwidth could be calculated
  //                      ',...
  //                           'from the start and stop frequencies of the ',...
  //                           'identified pulses. A bandwidth of 100 Hz ',...
  //                           'will be used for continued informed search.'])
  //                  end
  //              end
  //
  //              %Here is where we update the stats. These methods of updates
  //              %could be improved in the future.
  //              %obj.ps_pre.t_p; %tp doesn't change. We assume it is
  //              stationary
  //
  //              if numel(pulselist)==1% Happens if K=1
  //                  %We only have one pulse to reference, so we need to check
  //                  %the prior pulse too.
  //                  if ~isempty(obj.ps_pre.pl) &&
  //                  ~isnan(obj.ps_pre.pl(end).t_0)
  //                      recent_tip = pulselist.t_0-obj.ps_pre.pl(end).t_0;
  //                      %There could be a case where the last segment and this
  //                      %segement identified the same pulse. In this case
  //                      %recent_tip will be very small. In this case, we just
  //                      %say we learned nothing about t_ip in this segment.
  //                      if recent_tip < obj.ps_pre.t_ipu + obj.ps_pre.t_ipJ
  //                          recent_tip = NaN;
  //                      end
  //                  else
  //                      %No new information because we don't know the last
  //                      %pulse time
  //                      recent_tip = NaN;
  //                  end
  //              else
  //                  recent_tip = diff(t_found);
  //              end
  //              %Do a check here to make sure the new tip isn't a huge change.
  //              %This could potentially happen if we are in the K = 1 case and
  //              %the block getting processed contained two pulses, with the
  //              %latter pulse getting identified/detected. The lines above
  //              %would look back to the last identified pulse and it might be
  //              %2*tip back in time, producing a very large recenttip values.
  //              %If something like this happens, we ignore it so it doesn't
  //              %affect our new tip estimates.
  //              if recent_tip > 1.5*obj.ps_pre.t_ip & recent_tip <
  //              0.5*obj.ps_pre.t_ip
  //                  recent_tip = NaN;
  //              end
  //
  //              %Only update time parameters if we are in tracking mode. If we
  //              %aren't, we may have identified somethign that isn't a pulse
  //              if strcmp(obj.ps_pos.mode,'T') || strcmp(obj.ps_pre.mode,'T')
  //                  obj.ps_pos.t_ip  =
  //                  mean([recent_tip;obj.ps_pre.t_ip],'omitnan');
  //                  obj.ps_pos.t_ipu = obj.ps_pre.t_ipu; %Don't update this
  //                  because it can get too
  //                  narrow.%mean([3*std(diff(t_found));obj.ps_pre.t_ipu]);
  //                  obj.ps_pos.t_ipj = obj.ps_pre.t_ipj;
  //              end
  //              fp_pos           =
  //              freq_found;%nanmean([freq_found;obj.ps_pre.fp]);%Previous fc
  //              may be nan if unknown obj.ps_pos.fp    = fp_pos;
  //              obj.ps_pos.fstart = fp_pos-bw_found/2;
  //              obj.ps_pos.fend   = fp_pos+bw_found/2;
  //
  //              obj.ps_pos.psdHist = obj.stft.psd
  //          end
  // Samples per pulse
  // Number of elements in STFT window
  // Number of elements overlap in STFT window
  // Number of elements in each step of STFT
  // Time of each step of STFT
  // Samples per pulse
  // Number of elements in STFT window
  // Number of elements overlap in STFT window
  // Number of elements in each step of STFT
  // Time of each step of STFT
  // Samples of interpulse duration
  // Baseline interpulse duration in units of STFT windows
  // Interpulse duration deviation from baselines in units of STFT windows
  // Amount of deviation from the PRI means to search
  //              if K ~= 1
  //                  samplesforKpulses = n_ws*(K*(N+M)-2*M)+n_ol;
  //              else
  //                  samplesforKpulses = n_ws*(N+M+J+1)+n_ol;
  //              end
  // See 2022-07-11 for updates to samples def
  // obj.t_nextsegstart  = obj.t_0+(samplesforKpulses)/obj.Fs; %Don't need the
  // overlap here since the next segment starts at samplesforKpulses+n_ol-n_ol
  // from current sample Don't need the overlap here since the next segment
  // starts at samplesforKpulses+n_ol-n_ol from current sample
  //              if isempty(obj.TimeCorr)
  //                  obj.TimeCorr = TemporalCorrelator(N, M, J);
  //              else
  //                  obj.TimeCorr.update(N, M, J);
  //              end
  // GETPRIORIDEPENDENTVARS returns the properties in the
  // waveform that are dependent on prior pulse data estimates. It
  // depends on the waveform properties list Fs etc, as well as
  // pulse stats like t_ip, etc.
  // INPUTS:  ps_obj  1x1 pulse stats object
  // OUTPUTS:  pulse stats object
  // WHAT WAS DONE BY THIS METHOD IS NOW DONE BY A METHOD OF THE
  // PULSESTATS CLASS.
  //          function [] = update_posteriori(obj,pulselist)
  //              %UPDATE_POSTERIORI updates the posteriori pulse statistics of
  //              %this waveform object using the new pulse list (input) and the
  //              %apriori stats. The pulse contained in the waveform's ps_pos
  //              %property is not used directly so that the caller can decide
  //              %which pulses on which to focus the posteriori.
  //
  //              t_found    = [pulselist(:).t_0]';
  //              freq_found = mean([pulselist(:).fp],'omitnan');
  //
  //              %Create a vector of bandwidths from the pulselist
  //              bw_found =
  //              2*(mean([pulselist.fend],'omitnan')-mean([pulselist.fstart],'omitnan'));
  //              if isempty(bw_found)
  //                  bw_found = 100;
  //                  if coder.target('MATLAB')
  //                      warning(['UAV-R: No bandwidth could be calculated
  //                      ',...
  //                           'from the start and stop frequencies of the ',...
  //                           'identified pulses. A bandwidth of 100 Hz ',...
  //                           'will be used for continued informed search.'])
  //                  end
  //              end
  //
  //              %Here is where we update the stats. These methods of updates
  //              %could be improved in the future.
  //              %obj.ps_pre.t_p; %tp doesn't change. We assume it is
  //              stationary
  //
  //              if numel(pulselist)==1% Happens if K=1
  //                  %We only have one pulse to reference, so we need to check
  //                  %the prior pulse too.
  //                  if ~isempty(obj.ps_pre.pl) &&
  //                  ~isnan(obj.ps_pre.pl(end).t_0)
  //                      recent_tip = pulselist.t_0-obj.ps_pre.pl(end).t_0;
  //                      %There could be a case where the last segment and this
  //                      %segement identified the same pulse. In this case
  //                      %recent_tip will be very small. In this case, we just
  //                      %say we learned nothing about t_ip in this segment.
  //                      if recent_tip < obj.ps_pre.t_ipu + obj.ps_pre.t_ipJ
  //                          recent_tip = NaN;
  //                      end
  //                  else
  //                      %No new information because we don't know the last
  //                      %pulse time
  //                      recent_tip = NaN;
  //                  end
  //              else
  //                  recent_tip = diff(t_found);
  //              end
  //              %Do a check here to make sure the new tip isn't a huge change.
  //              %This could potentially happen if we are in the K = 1 case and
  //              %the block getting processed contained two pulses, with the
  //              %latter pulse getting identified/detected. The lines above
  //              %would look back to the last identified pulse and it might be
  //              %2*tip back in time, producing a very large recenttip values.
  //              %If something like this happens, we ignore it so it doesn't
  //              %affect our new tip estimates.
  //              if recent_tip > 1.5*obj.ps_pre.t_ip & recent_tip <
  //              0.5*obj.ps_pre.t_ip
  //                  recent_tip = NaN;
  //              end
  //
  //              %Only update time parameters if we are in tracking mode. If we
  //              %aren't, we may have identified somethign that isn't a pulse
  //              if strcmp(obj.ps_pos.mode,'T') || strcmp(obj.ps_pre.mode,'T')
  //                  obj.ps_pos.t_ip  =
  //                  mean([recent_tip;obj.ps_pre.t_ip],'omitnan');
  //                  obj.ps_pos.t_ipu = obj.ps_pre.t_ipu; %Don't update this
  //                  because it can get too
  //                  narrow.%mean([3*std(diff(t_found));obj.ps_pre.t_ipu]);
  //                  obj.ps_pos.t_ipj = obj.ps_pre.t_ipj;
  //              end
  //              fp_pos           =
  //              freq_found;%nanmean([freq_found;obj.ps_pre.fp]);%Previous fc
  //              may be nan if unknown obj.ps_pos.fp    = fp_pos;
  //              obj.ps_pos.fstart = fp_pos-bw_found/2;
  //              obj.ps_pos.fend   = fp_pos+bw_found/2;
  //
  //              obj.ps_pos.psdHist = obj.stft.psd
  //          end
  a__2 = std::ceil(ps_input->t_p * X0.Fs);
  // Samples per pulse
  // Number of elements in STFT window
  n_ol = std::floor(stftOverlapFraction.contents * a__2);
  // Number of elements overlap in STFT window
  a__2 -= n_ol;
  // Number of elements in each step of STFT
  // Time of each step of STFT
  N = std::floor(std::ceil(ps_input->t_ip * X0.Fs) / a__2);
  M = std::ceil(std::ceil(ps_input->t_ipu * X0.Fs) / a__2);
  J = std::ceil(std::ceil(ps_input->t_ipj * X0.Fs) / a__2);
  //          overlapWindows  = 2*Config.K*M+1;
  //          overlapSamples	= n_ws*overlapWindows;
  //          %sampsForKPulses = Config.K*n_ws*(N+M+1+1);
  //          sampsForKPulses = n_ws*(Config.K*(N+M)+1+1);
  overlapSamples.contents = a__2 * (2.0 * (Config.contents.K * M + J));
  //          if Config.K~=1
  //              sampsForKPulses = n_ws*(Config.K*(N+M)-2*M)+n_ol;
  //          else
  //              sampsForKPulses = n_ws*(N+M+J)+n_ol;
  //          end
  // See 2022-07-11 for updates to samples def
  sampsForKPulses.contents =
      a__2 * ((Config.contents.K * (N + M) + J) + 1.0) + n_ol;
  if (N < 4.294967296E+9) {
    if (N >= 0.0) {
      u = static_cast<unsigned int>(N);
    } else {
      u = 0U;
    }
  } else if (N >= 4.294967296E+9) {
    u = MAX_uint32_T;
  } else {
    u = 0U;
  }
  if (M < 4.294967296E+9) {
    if (M >= 0.0) {
      u1 = static_cast<unsigned int>(M);
    } else {
      u1 = 0U;
    }
  } else if (M >= 4.294967296E+9) {
    u1 = MAX_uint32_T;
  } else {
    u1 = 0U;
  }
  if (J < 4.294967296E+9) {
    if (J >= 0.0) {
      u2 = static_cast<unsigned int>(J);
    } else {
      u2 = 0U;
    }
  } else if (J >= 4.294967296E+9) {
    u2 = MAX_uint32_T;
  } else {
    u2 = 0U;
  }
  std::printf("Updating buffer read vars|| N: %u, M: %u, J: %u,\n", u, u1, u2);
  std::fflush(stdout);
  a__2 = std::round(sampsForKPulses.contents);
  if (a__2 < 4.294967296E+9) {
    if (a__2 >= 0.0) {
      u = static_cast<unsigned int>(a__2);
    } else {
      u = 0U;
    }
  } else if (a__2 >= 4.294967296E+9) {
    u = MAX_uint32_T;
  } else {
    u = 0U;
  }
  a__2 = std::round(overlapSamples.contents);
  if (a__2 < 4.294967296E+9) {
    if (a__2 >= 0.0) {
      u1 = static_cast<unsigned int>(a__2);
    } else {
      u1 = 0U;
    }
  } else if (a__2 >= 4.294967296E+9) {
    u1 = MAX_uint32_T;
  } else {
    u1 = 0U;
  }
  std::printf(
      "Updating buffer read vars|| sampForKPulses: %u,  overlapSamples: %u,\n",
      u, u1);
  std::fflush(stdout);
}

//
// Add code here to update the variables within the function that are
// part of the configuration file. Will first need to load the correct
// file and
//
//
// Arguments    : coder::b_captured_var &Config
//                const coder::captured_var &configPath
// Return Type  : void
//
static void updateconfig(coder::b_captured_var &Config,
                         const coder::captured_var &configPath)
{
  static rtBoundsCheckInfo ab_emlrtBCI{
      -1,                           // iFirst
      -1,                           // iLast
      151,                          // lineNo
      31,                           // colNo
      "sepByte",                    // aName
      "DetectorConfig/setFromFile", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/DetectorConfig.m", // pName
      0                                                   // checkKind
  };
  static rtBoundsCheckInfo bb_emlrtBCI{
      -1,                           // iFirst
      -1,                           // iLast
      155,                          // lineNo
      28,                           // colNo
      "lineStr",                    // aName
      "DetectorConfig/setFromFile", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/DetectorConfig.m", // pName
      0                                                   // checkKind
  };
  static rtBoundsCheckInfo cb_emlrtBCI{
      -1,                           // iFirst
      -1,                           // iLast
      158,                          // lineNo
      55,                           // colNo
      "tabLocs",                    // aName
      "DetectorConfig/setFromFile", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/DetectorConfig.m", // pName
      0                                                   // checkKind
  };
  static rtBoundsCheckInfo db_emlrtBCI{
      -1,                           // iFirst
      -1,                           // iLast
      159,                          // lineNo
      63,                           // colNo
      "colonLocation",              // aName
      "DetectorConfig/setFromFile", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/DetectorConfig.m", // pName
      0                                                   // checkKind
  };
  static rtBoundsCheckInfo eb_emlrtBCI{
      -1,                           // iFirst
      -1,                           // iLast
      194,                          // lineNo
      69,                           // colNo
      "sepByte",                    // aName
      "DetectorConfig/setFromFile", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/DetectorConfig.m", // pName
      0                                                   // checkKind
  };
  static rtBoundsCheckInfo fb_emlrtBCI{
      -1,                           // iFirst
      -1,                           // iLast
      160,                          // lineNo
      47,                           // colNo
      "lineStr",                    // aName
      "DetectorConfig/setFromFile", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/DetectorConfig.m", // pName
      0                                                   // checkKind
  };
  static rtBoundsCheckInfo gb_emlrtBCI{
      -1,                           // iFirst
      -1,                           // iLast
      160,                          // lineNo
      74,                           // colNo
      "lineStr",                    // aName
      "DetectorConfig/setFromFile", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/DetectorConfig.m", // pName
      0                                                   // checkKind
  };
  static rtBoundsCheckInfo hb_emlrtBCI{
      -1,                           // iFirst
      -1,                           // iLast
      159,                          // lineNo
      47,                           // colNo
      "lineStr",                    // aName
      "DetectorConfig/setFromFile", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/DetectorConfig.m", // pName
      0                                                   // checkKind
  };
  static rtBoundsCheckInfo ib_emlrtBCI{
      -1,                           // iFirst
      -1,                           // iLast
      159,                          // lineNo
      49,                           // colNo
      "lineStr",                    // aName
      "DetectorConfig/setFromFile", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/DetectorConfig.m", // pName
      0                                                   // checkKind
  };
  static rtBoundsCheckInfo jb_emlrtBCI{
      -1,                           // iFirst
      -1,                           // iLast
      196,                          // lineNo
      69,                           // colNo
      "sepByte",                    // aName
      "DetectorConfig/setFromFile", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/DetectorConfig.m", // pName
      0                                                   // checkKind
  };
  static rtBoundsCheckInfo y_emlrtBCI{
      -1,                           // iFirst
      -1,                           // iLast
      120,                          // lineNo
      28,                           // colNo
      "rawLine",                    // aName
      "DetectorConfig/setFromFile", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/DetectorConfig.m", // pName
      0                                                   // checkKind
  };
  static rtRunTimeErrorInfo tc_emlrtRTEI{
      37,      // lineNo
      9,       // colNo
      "fopen", // fName
      "/Applications/MATLAB_R2023a.app/toolbox/eml/lib/matlab/iofun/fopen.m" // pName
  };
  static rtRunTimeErrorInfo uc_emlrtRTEI{
      12,               // lineNo
      23,               // colNo
      "mustBePositive", // fName
      "/Applications/MATLAB_R2023a.app/toolbox/eml/lib/matlab/validators/"
      "mustBePositive.m" // pName
  };
  static rtRunTimeErrorInfo vc_emlrtRTEI{
      11,                  // lineNo
      24,                  // colNo
      "mustBeNonnegative", // fName
      "/Applications/MATLAB_R2023a.app/toolbox/eml/lib/matlab/validators/"
      "mustBeNonnegative.m" // pName
  };
  static rtRunTimeErrorInfo wc_emlrtRTEI{
      18,                     // lineNo
      5,                      // colNo
      "binaryRelopValidator", // fName
      "/Applications/MATLAB_R2023a.app/toolbox/eml/lib/matlab/validators/"
      "private/binaryRelopValidator.m" // pName
  };
  static const char b_cv[2]{'I', 'D'};
  int st;
  std::FILE *f;
  DetectorConfig r;
  coder::array<creal_T, 2U> r1;
  coder::array<double, 2U> sepByte;
  coder::array<double, 2U> val;
  coder::array<int, 2U> match_out;
  coder::array<int, 2U> matches;
  coder::array<unsigned int, 2U> tabLocs;
  coder::array<char, 2U> configType;
  coder::array<char, 2U> configValStr;
  coder::array<char, 2U> lineStr;
  coder::array<boolean_T, 2U> b_lineStr;
  double configNum;
  double d;
  int b_st;
  int c_st;
  int fid;
  int i;
  int ii_data;
  int loop_ub;
  int text_len;
  boolean_T a;
  boolean_T done;
  r.init();
  lineStr.set_size(1, configPath.contents.size(1));
  loop_ub = configPath.contents.size(1);
  for (i = 0; i < loop_ub; i++) {
    lineStr[i] = configPath.contents[i];
  }
  // fillFromFile Replaces the properties of the instance passed to
  // it with the values specified in the configuration file passed
  // to the function. If multiple entries exist in the config file,
  // use the 'entry' argument to specify which entry to use (1-n).
  // If entry is not specified, the method will use the last entry
  // in the config file.
  //
  // INPUTS:
  //    filePath        String of full path to config file,
  //                    including the file name and extension
  //
  //    entry           Scalar number (1-n) of which entry to use.
  //                    Method will use the last entry if entry is
  //                    not provided. Alternatively, enter -1 to
  //                    use last entry.
  //
  // OUTPUTS:
  //    none (method modifies the properties of the instance)
  //
  if (coder::internal::b_strcmp(lineStr)) {
    b_rtErrorWithMessageID(tc_emlrtRTEI.fName, tc_emlrtRTEI.lineNo);
  } else {
    signed char fileid;
    fileid = coder::internal::cfopen(lineStr, "rb");
    fid = fileid;
  }
  if (fid == -1) {
    configType.set_size(1, lineStr.size(1) + 1);
    loop_ub = lineStr.size(1);
    for (i = 0; i < loop_ub; i++) {
      configType[i] = lineStr[i];
    }
    configType[lineStr.size(1)] = '\x00';
    std::printf("UAV-RT: Error opening configurationfile file with error. "
                "Attempted to find config file at the location %s:\n",
                &configType[0]);
    std::fflush(stdout);
  }
  configNum = 0.0;
  done = false;
  // coder.varsize('sepLine')
  sepByte.set_size(1, 1);
  sepByte[0] = 0.0;
  // First figure out where the separator lines are
  while (!done) {
    // currByte = ftell(fid);
    coder::fgetl(static_cast<double>(fid), lineStr);
    if (lineStr.size(1) < 1) {
      rtDynamicBoundsError(1, 1, lineStr.size(1), y_emlrtBCI);
    }
    if (lineStr[0] == '#') {
      // && lineNum~=1
      if (configNum == 0.0) {
        sepByte.set_size(1, 1);
        d = coder::b_ftell(static_cast<double>(fid));
        sepByte[0] = d;
      } else {
        // sepByte(configNum) = ftell(fid);
        d = coder::b_ftell(static_cast<double>(fid));
        i = sepByte.size(1);
        sepByte.set_size(1, sepByte.size(1) + 1);
        sepByte[i] = d;
        // Modified for Coder compatibility
      }
      configNum++;
    }
    f = coder::internal::getfilestar(static_cast<double>(fid), a);
    if (f == nullptr) {
      c_rtErrorWithMessageID(c_emlrtRTEI.fName, c_emlrtRTEI.lineNo);
    } else {
      st = std::feof(f);
      text_len = ((int)st != 0);
    }
    done = (text_len == 1);
  }
  // sepByte(configNum) = ftell(fid);
  d = coder::b_ftell(static_cast<double>(fid));
  i = sepByte.size(1);
  sepByte.set_size(1, sepByte.size(1) + 1);
  sepByte[i] = d;
  // Modified for Coder compatibility
  // Jump to the line for the entry requested
  if ((static_cast<int>(configNum) < 1) ||
      (static_cast<int>(configNum) > sepByte.size(1))) {
    rtDynamicBoundsError(static_cast<int>(configNum), 1, sepByte.size(1),
                         ab_emlrtBCI);
  }
  coder::b_fseek(static_cast<double>(fid),
                 sepByte[static_cast<int>(configNum) - 1]);
  done = false;
  int exitg1;
  do {
    exitg1 = 0;
    if (!done) {
      coder::fgetl(static_cast<double>(fid), lineStr);
      if (lineStr.size(1) < 1) {
        rtDynamicBoundsError(1, 1, lineStr.size(1), bb_emlrtBCI);
      }
      if (lineStr[0] != '#') {
        int ii_size[2];
        int match_idx;
        b_lineStr.set_size(1, lineStr.size(1));
        loop_ub = lineStr.size(1);
        for (i = 0; i < loop_ub; i++) {
          b_lineStr[i] = (lineStr[i] == ':');
        }
        coder::eml_find(b_lineStr, (int *)&ii_data, ii_size);
        // note regexp is not supported for code generation
        if (lineStr.size(1) == 0) {
          tabLocs.set_size(1, 0);
        } else {
          text_len = lineStr.size(1);
          matches.set_size(1, lineStr.size(1));
          match_idx = 0;
          if (lineStr.size(1) > 2147483646) {
            coder::check_forloop_overflow_error();
          }
          for (loop_ub = 0; loop_ub < text_len; loop_ub++) {
            if (lineStr[loop_ub] == '\t') {
              matches[match_idx] = loop_ub + 1;
              match_idx++;
            }
          }
          match_out.set_size(1, match_idx);
          if (match_idx > 2147483646) {
            coder::check_forloop_overflow_error();
          }
          for (loop_ub = 0; loop_ub < match_idx; loop_ub++) {
            match_out[loop_ub] = matches[loop_ub];
          }
          tabLocs.set_size(1, match_out.size(1));
          loop_ub = match_out.size(1);
          for (i = 0; i < loop_ub; i++) {
            tabLocs[i] = static_cast<unsigned int>(match_out[i]);
          }
        }
        // Thanks to
        // https://www.mathworks.com/matlabcentral/answers/529668-how-do-i-detect-a-tab-character-in-a-line-of-text-read-by-fgetl
        if (tabLocs.size(1) < 1) {
          rtDynamicBoundsError(1, 1, tabLocs.size(1), cb_emlrtBCI);
        }
        // note regexp is not supported for code generation
        if (ii_size[1] < 1) {
          rtDynamicBoundsError(1, 1, ii_size[1], db_emlrtBCI);
        }
        if (static_cast<double>(ii_data) - 1.0 < 1.0) {
          loop_ub = 0;
        } else {
          if (lineStr.size(1) < 1) {
            rtDynamicBoundsError(1, 1, lineStr.size(1), hb_emlrtBCI);
          }
          if ((ii_data - 1 < 1) || (ii_data - 1 > lineStr.size(1))) {
            rtDynamicBoundsError(ii_data - 1, 1, lineStr.size(1), ib_emlrtBCI);
          }
          loop_ub = ii_data - 1;
        }
        configType.set_size(1, loop_ub);
        for (i = 0; i < loop_ub; i++) {
          configType[i] = lineStr[i];
        }
        if (tabLocs[0] + 1U > static_cast<unsigned int>(lineStr.size(1))) {
          i = 0;
          text_len = 0;
        } else {
          i = static_cast<int>(tabLocs[0] + 1U);
          if ((i < 1) || (i > lineStr.size(1))) {
            rtDynamicBoundsError(i, 1, lineStr.size(1), fb_emlrtBCI);
          }
          i--;
          if (lineStr.size(1) < 1) {
            rtDynamicBoundsError(lineStr.size(1), 1, lineStr.size(1),
                                 gb_emlrtBCI);
          }
          text_len = lineStr.size(1);
        }
        match_idx = text_len - i;
        configValStr.set_size(1, match_idx);
        for (text_len = 0; text_len < match_idx; text_len++) {
          configValStr[text_len] = lineStr[i + text_len];
        }
        a = false;
        if (loop_ub == 2) {
          text_len = 0;
          int exitg2;
          do {
            exitg2 = 0;
            if (text_len < 2) {
              if (lineStr[text_len] != b_cv[text_len]) {
                exitg2 = 1;
              } else {
                text_len++;
              }
            } else {
              a = true;
              exitg2 = 1;
            }
          } while (exitg2 == 0);
        }
        if (a) {
          creal_T x;
          unsigned int in_tmp;
          unsigned int u;
          x = coder::internal::str2double(configValStr);
          d = std::round(x.re);
          if (d < 4.294967296E+9) {
            if (d >= 0.0) {
              in_tmp = static_cast<unsigned int>(d);
              u = in_tmp;
            } else {
              in_tmp = 0U;
              u = 0U;
            }
          } else if (d >= 4.294967296E+9) {
            in_tmp = MAX_uint32_T;
            u = MAX_uint32_T;
          } else {
            in_tmp = 0U;
            u = 0U;
          }
          r.ID = in_tmp;
          if (u <= 0U) {
            d_rtErrorWithMessageID(uc_emlrtRTEI.fName, uc_emlrtRTEI.lineNo);
          }
        } else if (coder::internal::c_strcmp(configType)) {
          creal_T x;
          x = coder::internal::str2double(configValStr);
          if (!(x.re >= 0.0)) {
            e_rtErrorWithMessageID(vc_emlrtRTEI.fName, vc_emlrtRTEI.lineNo);
          }
          r.channelCenterFreqMHz = x.re;
        } else if (!coder::internal::d_strcmp(configType)) {
          if (coder::internal::e_strcmp(configType)) {
            creal_T x;
            unsigned short b_in_tmp;
            unsigned short u1;
            x = coder::internal::str2double(configValStr);
            d = std::round(x.re);
            if (d < 65536.0) {
              if (d >= 0.0) {
                b_in_tmp = static_cast<unsigned short>(d);
                u1 = b_in_tmp;
              } else {
                b_in_tmp = 0U;
                u1 = 0U;
              }
            } else if (d >= 65536.0) {
              b_in_tmp = MAX_uint16_T;
              u1 = MAX_uint16_T;
            } else {
              b_in_tmp = 0U;
              u1 = 0U;
            }
            r.portData = b_in_tmp;
            if (u1 <= 0) {
              d_rtErrorWithMessageID(uc_emlrtRTEI.fName, uc_emlrtRTEI.lineNo);
            }
          } else if (coder::internal::f_strcmp(configType)) {
            creal_T x;
            x = coder::internal::str2double(configValStr);
            if (!(x.re > 0.0)) {
              d_rtErrorWithMessageID(uc_emlrtRTEI.fName, uc_emlrtRTEI.lineNo);
            }
            r.Fs = x.re;
          } else if (coder::internal::g_strcmp(configType)) {
            creal_T x;
            x = coder::internal::str2double(configValStr);
            r.tagFreqMHz = x.re;
          } else if (coder::internal::h_strcmp(configType)) {
            creal_T x;
            x = coder::internal::str2double(configValStr);
            if (!(x.re > 0.0)) {
              d_rtErrorWithMessageID(uc_emlrtRTEI.fName, uc_emlrtRTEI.lineNo);
            }
            r.tp = x.re;
          } else if (coder::internal::i_strcmp(configType)) {
            creal_T x;
            x = coder::internal::str2double(configValStr);
            if (!(x.re > 0.0)) {
              d_rtErrorWithMessageID(uc_emlrtRTEI.fName, uc_emlrtRTEI.lineNo);
            }
            r.tip = x.re;
          } else if (coder::internal::j_strcmp(configType)) {
            creal_T x;
            x = coder::internal::str2double(configValStr);
            if (!(x.re >= 0.0)) {
              e_rtErrorWithMessageID(vc_emlrtRTEI.fName, vc_emlrtRTEI.lineNo);
            }
            r.tipu = x.re;
          } else if (coder::internal::k_strcmp(configType)) {
            creal_T x;
            x = coder::internal::str2double(configValStr);
            if (!(x.re >= 0.0)) {
              e_rtErrorWithMessageID(vc_emlrtRTEI.fName, vc_emlrtRTEI.lineNo);
            }
            r.tipj = x.re;
          } else {
            a = false;
            if ((loop_ub == 1) && (lineStr[0] == 'K')) {
              a = true;
            }
            if (a) {
              creal_T x;
              unsigned char c_in_tmp;
              unsigned char u2;
              x = coder::internal::str2double(configValStr);
              d = std::round(x.re);
              if (d < 256.0) {
                if (d >= 0.0) {
                  c_in_tmp = static_cast<unsigned char>(d);
                  u2 = c_in_tmp;
                } else {
                  c_in_tmp = 0U;
                  u2 = 0U;
                }
              } else if (d >= 256.0) {
                c_in_tmp = MAX_uint8_T;
                u2 = MAX_uint8_T;
              } else {
                c_in_tmp = 0U;
                u2 = 0U;
              }
              r.K = c_in_tmp;
              if (u2 <= 0) {
                d_rtErrorWithMessageID(uc_emlrtRTEI.fName, uc_emlrtRTEI.lineNo);
              }
            } else if (coder::internal::l_strcmp(configType)) {
              r.opMode.Value.set_size(1, match_idx);
              for (text_len = 0; text_len < match_idx; text_len++) {
                r.opMode.Value[text_len] = lineStr[i + text_len];
              }
            } else if (coder::internal::m_strcmp(configType)) {
              str2matrix(configValStr, r1);
              val.set_size(r1.size(0), r1.size(1));
              loop_ub = r1.size(0) * r1.size(1);
              for (i = 0; i < loop_ub; i++) {
                val[i] = r1[i].re;
              }
              coder::internal::validator_check_size(val, r.excldFreqs);
            } else if (coder::internal::n_strcmp(configType)) {
              creal_T x;
              x = coder::internal::str2double(configValStr);
              if (!(x.re > 0.0)) {
                d_rtErrorWithMessageID(uc_emlrtRTEI.fName, uc_emlrtRTEI.lineNo);
              }
              if (!(x.re < 1.0)) {
                b_rtErrorWithMessageID("1", wc_emlrtRTEI.fName,
                                       wc_emlrtRTEI.lineNo);
              }
              r.falseAlarmProb = x.re;
            } else if (coder::internal::o_strcmp(configType)) {
              r.dataRecordPath.Value.set_size(1, match_idx);
              for (text_len = 0; text_len < match_idx; text_len++) {
                r.dataRecordPath.Value[text_len] = lineStr[i + text_len];
              }
            }
          }
        }
        // Stop when we have finished reading this entry.
        f = coder::internal::getfilestar(static_cast<double>(fid), a);
        if (f == nullptr) {
          c_rtErrorWithMessageID(c_emlrtRTEI.fName, c_emlrtRTEI.lineNo);
        } else {
          st = std::feof(f);
          c_st = ((int)st != 0);
        }
        if (c_st == 1) {
          done = true;
        } else {
          if ((static_cast<int>(static_cast<unsigned int>(configNum) + 1U) <
               1) ||
              (static_cast<int>(static_cast<unsigned int>(configNum) + 1U) >
               sepByte.size(1))) {
            rtDynamicBoundsError(
                static_cast<int>(static_cast<unsigned int>(configNum) + 1U), 1,
                sepByte.size(1), eb_emlrtBCI);
          }
          if (coder::b_ftell(static_cast<double>(fid)) ==
              sepByte[static_cast<int>(static_cast<unsigned int>(configNum))]) {
            done = true;
          }
        }
      } else {
        f = coder::internal::getfilestar(static_cast<double>(fid), a);
        if (f == nullptr) {
          c_rtErrorWithMessageID(c_emlrtRTEI.fName, c_emlrtRTEI.lineNo);
        } else {
          st = std::feof(f);
          b_st = ((int)st != 0);
        }
        if (b_st == 1) {
          done = true;
        } else {
          if ((static_cast<int>(static_cast<unsigned int>(configNum) + 1U) <
               1) ||
              (static_cast<int>(static_cast<unsigned int>(configNum) + 1U) >
               sepByte.size(1))) {
            rtDynamicBoundsError(
                static_cast<int>(static_cast<unsigned int>(configNum) + 1U), 1,
                sepByte.size(1), jb_emlrtBCI);
          }
          if (coder::b_ftell(static_cast<double>(fid)) ==
              sepByte[static_cast<int>(static_cast<unsigned int>(configNum))]) {
            done = true;
          }
        }
      }
    } else {
      exitg1 = 1;
    }
  } while (exitg1 == 0);
  coder::internal::cfclose(static_cast<double>(fid));
  Config.contents = r;
  // Do we update the tip and tipu or use the ones that were adapted from
  // the previous detections? Probably just use the file. The supervisor
  // will have access to the detected pulses and can update these values if
  // it sees fit.
}

//
// Arguments    : const coder::array<char, 2U> &configPath
//                const coder::array<char, 2U> &thresholdCachePath
// Return Type  : void
//
void uavrt_detection(const coder::array<char, 2U> &configPath,
                     const coder::array<char, 2U> &thresholdCachePath)
{
  static coder::dsp::AsyncBuffer asyncDataBuff;
  static coder::dsp::b_AsyncBuffer asyncTimeBuff;
  static coder::dsp::c_AsyncBuffer asyncWriteBuff;
  static rtBoundsCheckInfo ab_emlrtBCI{
      -1,                // iFirst
      -1,                // iLast
      416,               // lineNo
      32,                // colNo
      "t",               // aName
      "uavrt_detection", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/uavrt_detection.m", // pName
      0                                                    // checkKind
  };
  static rtBoundsCheckInfo bb_emlrtBCI{
      -1,                // iFirst
      -1,                // iLast
      585,               // lineNo
      61,                // colNo
      "X.ps_pos.pl",     // aName
      "uavrt_detection", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/uavrt_detection.m", // pName
      0                                                    // checkKind
  };
  static rtBoundsCheckInfo cb_emlrtBCI{
      -1,                // iFirst
      -1,                // iLast
      590,               // lineNo
      79,                // colNo
      "ps_pre_struc.pl", // aName
      "uavrt_detection", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/uavrt_detection.m", // pName
      0                                                    // checkKind
  };
  static rtBoundsCheckInfo db_emlrtBCI{
      -1,                // iFirst
      -1,                // iLast
      596,               // lineNo
      50,                // colNo
      "pulsesToSkip",    // aName
      "uavrt_detection", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/uavrt_detection.m", // pName
      0                                                    // checkKind
  };
  static rtBoundsCheckInfo eb_emlrtBCI{
      -1,                // iFirst
      -1,                // iLast
      625,               // lineNo
      91,                // colNo
      "X.ps_pos.pl",     // aName
      "uavrt_detection", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/uavrt_detection.m", // pName
      0                                                    // checkKind
  };
  static rtBoundsCheckInfo fb_emlrtBCI{
      -1,                // iFirst
      -1,                // iLast
      641,               // lineNo
      50,                // colNo
      "pulsesToSkip",    // aName
      "uavrt_detection", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/uavrt_detection.m", // pName
      0                                                    // checkKind
  };
  static rtBoundsCheckInfo gb_emlrtBCI{
      -1,                   // iFirst
      -1,                   // iLast
      662,                  // lineNo
      89,                   // colNo
      "dataRecordPathChar", // aName
      "uavrt_detection",    // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/uavrt_detection.m", // pName
      0                                                    // checkKind
  };
  static rtBoundsCheckInfo hb_emlrtBCI{
      -1,                   // iFirst
      -1,                   // iLast
      662,                  // lineNo
      91,                   // colNo
      "dataRecordPathChar", // aName
      "uavrt_detection",    // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/uavrt_detection.m", // pName
      0                                                    // checkKind
  };
  static rtBoundsCheckInfo y_emlrtBCI{
      -1,                // iFirst
      -1,                // iLast
      400,               // lineNo
      82,                // colNo
      "timeVector",      // aName
      "uavrt_detection", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/uavrt_detection.m", // pName
      0                                                    // checkKind
  };
  static rtDoubleCheckInfo r_emlrtDCI{
      285,               // lineNo
      50,                // colNo
      "uavrt_detection", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/uavrt_detection.m", // pName
      4                                                    // checkKind
  };
  static rtDoubleCheckInfo s_emlrtDCI{
      285,               // lineNo
      50,                // colNo
      "uavrt_detection", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/uavrt_detection.m", // pName
      1                                                    // checkKind
  };
  static rtEqualityCheckInfo g_emlrtECI{
      -1,                // nDims
      285,               // lineNo
      37,                // colNo
      "uavrt_detection", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/uavrt_detection.m" // pName
  };
  static const char b_cv[31]{'c', 'u', 'r', 'r', 'e', 'n', 't', '_',
                             'w', 'o', 'r', 'k', 'i', 'n', 'g', '_',
                             'd', 'i', 'r', 'e', 'c', 't', 'o', 'r',
                             'y', '_', 'e', 'r', 'r', 'o', 'r'};
  char *nullVal;
  char *retVal;
  ComplexSingleSamplesUDPReceiver udpReceiver;
  b_waveform X;
  coder::b_captured_var Config;
  coder::c_captured_var overlapSamples;
  coder::c_captured_var sampsForKPulses;
  coder::c_captured_var stftOverlapFraction;
  coder::captured_var b_configPath;
  coder::datetime b_this;
  pulsestats lobj_12[4];
  pulsestats lobj_21[2];
  pulsestats lobj_15;
  pulsestats lobj_17;
  pulsestats lobj_18;
  pulsestats *pulseStatsPriori;
  threshold Xhold_tmp;
  threshold _in;
  waveform b_X;
  waveform lobj_13;
  waveform lobj_20;
  waveform *Xhold;
  wfmstft lobj_19[3];
  wfmstft lobj_11;
  wfmstft lobj_14;
  wfmstft lobj_16;
  coder::array<c_struct_T, 2U> ps_pre_struc_clst;
  coder::array<c_struct_T, 2U> ps_pre_struc_pl;
  coder::array<c_struct_T, 1U> c_X;
  coder::array<creal32_T, 2U> iqDataToWrite;
  coder::array<creal32_T, 1U> b_iqDataToWrite;
  coder::array<creal32_T, 1U> c_iqDataToWrite;
  coder::array<creal32_T, 1U> dataWriterBuffData;
  coder::array<creal32_T, 1U> x;
  coder::array<cuint8_T, 1U> r;
  coder::array<double, 2U> b_x;
  coder::array<double, 2U> groupSNRList;
  coder::array<double, 2U> ps_pre_struc_cpki;
  coder::array<double, 1U> b_groupSNRList;
  coder::array<double, 1U> b_timeVector;
  coder::array<double, 1U> t;
  coder::array<double, 1U> timeVector;
  coder::array<float, 1U> r1;
  coder::array<char, 2U> varargin_1;
  coder::array<char, 2U> waveformRecordPath;
  coder::array<boolean_T, 2U> ps_pre_struc_cmsk;
  coder::array<boolean_T, 2U> pulsesToSkip;
  coder::array<boolean_T, 2U> r3;
  coder::array<boolean_T, 1U> b_tmp_data;
  coder::array<boolean_T, 1U> r2;
  c_struct_T detectorPulse;
  c_struct_T expl_temp;
  creal_T dcv[1000];
  creal32_T dataReceived_data[1024];
  creal32_T b_dataReceived_data[1023];
  creal32_T exampleData[1000];
  double doublesBuffer[12];
  double ps_pre_struc_tmplt[2];
  double T;
  double dataWriterSamples;
  double expectedNextTimeStamp;
  double framesReceived;
  double groupSeqCounter;
  double previousPulseTime;
  double ps_pre_struc_fend;
  double ps_pre_struc_fp;
  double ps_pre_struc_fstart;
  double ps_pre_struc_t_ipj;
  double ps_pre_struc_t_ipu;
  double segmentsProcessed;
  double startTime;
  double t9_SNR;
  double t9_fend;
  double t9_fp;
  double t9_fstart;
  double t9_t_f;
  double t9_yw;
  double timeDiff;
  double timeStamp;
  double trackedCount;
  int currDir_size[2];
  int i;
  int loop_ub;
  unsigned int u1;
  int val;
  unsigned short u2;
  char currDir_data[200];
  char untokenizedDir[200];
  signed char fileid;
  char mode;
  char suggestedMode;
  boolean_T cleanBuffer;
  boolean_T configUpdatedFlag;
  boolean_T fLock;
  boolean_T resetBuffersFlag;
  boolean_T staleDataFlag;
  boolean_T t9_con_dec;
  boolean_T t9_det_dec;
  boolean_T tmp_data;
  if (!isInitialized_uavrt_detection) {
    uavrt_detection_initialize();
  }
  b_configPath.contents.set_size(1, configPath.size(1));
  loop_ub = configPath.size(1);
  for (i = 0; i < loop_ub; i++) {
    b_configPath.contents[i] = configPath[i];
  }
  //  configPath            - Fully qualified path to detect config file
  //  thresholdCachePath    - Fully qualified path to where the threshold cache
  //  files are stored.
  //                          If not specified thresholds will be re-generated.
  // Needed for usleep function in generated code
  //  coder.cinclude('stdlib.h')%needed for system call to kill the channelizer
  globalThresholdCachePath.set_size(1, thresholdCachePath.size(1));
  loop_ub = thresholdCachePath.size(1);
  for (i = 0; i < loop_ub; i++) {
    globalThresholdCachePath[i] = thresholdCachePath[i];
  }
  Config.contents.init();
  // Build empty config object
  updateconfig(Config, b_configPath);
  // Update (fill) the configuration
  configUpdatedFlag = true;
  //  %Get current working directory
  //  if coder.target('MATLAB')
  //      currDir = pwd;
  //  else
  //      %Solution from
  //      https://www.mathworks.com/matlabcentral/answers/1843008-using-coder-ceval-to-getcwd
  //      coder.cinclude('unistd.h');
  //      bufferTemplate = repmat('c', 1, 200);
  //      untokenizedDir = coder.nullcopy(bufferTemplate);
  //      coder.ceval('getcwd', coder.ref(untokenizedDir), 200);
  //      currDir = strtok(untokenizedDir, char(0));
  //  end
  // Attempts at catching a failed getcwd() call
  //  Get current working directory
  nullVal = nullptr;
  retVal = getcwd(&untokenizedDir[0], 200.0);
  if (retVal == nullVal) {
    //  Do some error handling here
    currDir_size[1] = 31;
    for (i = 0; i < 31; i++) {
      currDir_data[i] = b_cv[i];
    }
  } else {
    coder::b_strtok(untokenizedDir, currDir_data, currDir_size);
  }
  varargin_1.set_size(1, currDir_size[1] + 1);
  loop_ub = currDir_size[1];
  for (i = 0; i < loop_ub; i++) {
    varargin_1[i] = currDir_data[i];
  }
  varargin_1[currDir_size[1]] = '\x00';
  std::printf("Curr Directory is: %s\n", &varargin_1[0]);
  std::fflush(stdout);
  std::printf("ROS2 setup disabled");
  std::fflush(stdout);
  detectorPulse.A = makepulsestruc(
      detectorPulse.t_next, detectorPulse.mode, detectorPulse.P,
      detectorPulse.SNR, detectorPulse.yw, detectorPulse.t_0, detectorPulse.t_f,
      detectorPulse.fp, detectorPulse.fstart, detectorPulse.fend,
      detectorPulse.det_dec, detectorPulse.con_dec);
  timeDiff = makepulsestruc(expl_temp.t_next, expl_temp.mode, timeStamp, t9_SNR,
                            t9_yw, T, t9_t_f, t9_fp, t9_fstart, t9_fend,
                            t9_det_dec, t9_con_dec);
  expl_temp.con_dec = t9_con_dec;
  expl_temp.det_dec = t9_det_dec;
  expl_temp.fend = t9_fend;
  expl_temp.fstart = t9_fstart;
  expl_temp.fp = t9_fp;
  expl_temp.t_f = t9_t_f;
  expl_temp.t_0 = T;
  expl_temp.yw = t9_yw;
  expl_temp.SNR = t9_SNR;
  expl_temp.P = timeStamp;
  expl_temp.A = timeDiff;
  pulseStatsPriori = lobj_21[1].init(Config.contents.tp, Config.contents.tip,
                                     Config.contents.tipu, Config.contents.tipj,
                                     detectorPulse, expl_temp);
  //  % tp, tip, tipu
  //  % tipj, fp, fstart, fend, tmplt, mode
  //   % pl ,clst
  //  cmsk ,cpki)
  stftOverlapFraction.contents = 0.5;
  // Initialize and then set these variable needed for buffer reads
  overlapSamples.contents = 0.0;
  sampsForKPulses.contents = 0.0;
  updatebufferreadvariables(Config, stftOverlapFraction, overlapSamples,
                            sampsForKPulses, pulseStatsPriori);
  // 1024 plus a time stamp.
  std::printf("Startup set 1 complete. \n");
  std::fflush(stdout);
  //  Prepare data writing buffer
  //  Calculating the max size that would ever be needed for the buffer
  //  maxK    = 6;
  //  maxFs   = 912000/2;
  //  maxtp   = 0.04;
  //  maxtip  = 2;
  //  maxtipu = 0.1;
  //  maxpulseStatsPriori = pulsestats(maxtp,maxtip,maxtipu,[],[],[],[1
  //  1],pulse); Xmax = waveform([], maxFs, 0, maxpulseStatsPriori,
  //  stftOverlapFraction);
  //  [~,~,~,maxn_ws,~,~,maxN,maxM] = Xmax.getprioridependentprops(Xmax.ps_pre);
  //  sampsForMaxPulses = maxK*maxn_ws*(maxN+maxM+1+1);
  asyncDataBuff.pBuffer.NumChannels = -1;
  asyncDataBuff.pBuffer.isInitialized = 0;
  asyncDataBuff.pBuffer.matlabCodegenIsDeleted = false;
  asyncDataBuff.matlabCodegenIsDeleted = false;
  asyncTimeBuff.pBuffer.NumChannels = -1;
  asyncTimeBuff.pBuffer.isInitialized = 0;
  asyncTimeBuff.pBuffer.matlabCodegenIsDeleted = false;
  asyncTimeBuff.matlabCodegenIsDeleted = false;
  std::printf("Startup set 2 complete. \n");
  std::fflush(stdout);
  // Write interval in seconds. 2.5*60*4000*32/8 should work out the 2.4Mb of
  // data at 4ksps.
  dataWriterSamples = std::ceil(10.0 / (1024.0 / Config.contents.Fs)) * 1025.0;
  asyncWriteBuff.pBuffer.NumChannels = -1;
  asyncWriteBuff.pBuffer.isInitialized = 0;
  asyncWriteBuff.pBuffer.matlabCodegenIsDeleted = false;
  asyncWriteBuff.matlabCodegenIsDeleted = false;
  // 600650 is the result of the nominal settings of ceil(150/(1024/4000)*1025.
  asyncWriteBuff.write();
  // Write to give Code the type. Read to remove data.
  asyncWriteBuff.read();
  fileid = coder::internal::cfopen(Config.contents.dataRecordPath.Value, "wb");
  // dataWriterFileID    = fopen('output/data.bin','w');
  if (fileid == -1) {
    std::printf(
        "UAV-RT: Error opening/creating data record file with error:\n");
    std::fflush(stdout);
  }
  std::printf("Startup set 3 complete. \n");
  std::fflush(stdout);
  // pulseWriterFileID    =
  // fopen(cat(2,char(Config.processedOuputPath),'PULSE_LOG.txt'),'w');
  // pulseWriterFileID    = fopen('pulse_log','w');
  //  pulseWriterFileID    = fopen('/config/data2.bin','w');
  //  if dataWriterFileID == -1
  //      fprintf("UAV-RT: Error opening/creating pulse record file with
  //      error:\n")
  //  end
  //
  std::printf("Startup set 4 complete. \n");
  std::fflush(stdout);
  // Define a pulsestats structure that isn't an object.
  // This is needed for the loop, as Matlab coder has problems seeing
  // that the pulsestats handle object is set for all execution paths.
  // Holding all these properties in a structure rather than the
  // pulsestats object addressed this problem.
  // Needed to let coder know that some of these will be varying in size
  // https://www.mathworks.com/help/simulink/ug/how-working-with-matlab-classes-is-different-for-code-generation.html
  mode = 'D';
  // dims 0 if fixed, 1 if variable
  std::printf("Startup set 5 complete. \n");
  std::fflush(stdout);
  t9_fstart = 0.0;
  t9_fend = 0.0;
  ps_pre_struc_t_ipu = 0.0;
  ps_pre_struc_t_ipj = 0.0;
  ps_pre_struc_fp = 0.0;
  ps_pre_struc_fstart = 0.0;
  ps_pre_struc_fend = 0.0;
  ps_pre_struc_tmplt[0] = 1.0;
  ps_pre_struc_tmplt[1] = 1.0;
  detectorPulse.A = makepulsestruc(
      detectorPulse.t_next, detectorPulse.mode, detectorPulse.P,
      detectorPulse.SNR, detectorPulse.yw, detectorPulse.t_0, detectorPulse.t_f,
      detectorPulse.fp, detectorPulse.fstart, detectorPulse.fend,
      detectorPulse.det_dec, detectorPulse.con_dec);
  ps_pre_struc_pl.set_size(1, 1);
  ps_pre_struc_pl[0] = detectorPulse;
  detectorPulse.A = makepulsestruc(
      detectorPulse.t_next, detectorPulse.mode, detectorPulse.P,
      detectorPulse.SNR, detectorPulse.yw, detectorPulse.t_0, detectorPulse.t_f,
      detectorPulse.fp, detectorPulse.fstart, detectorPulse.fend,
      detectorPulse.det_dec, detectorPulse.con_dec);
  ps_pre_struc_clst.set_size(1, 1);
  ps_pre_struc_clst[0] = detectorPulse;
  ps_pre_struc_cmsk.set_size(1, 1);
  ps_pre_struc_cmsk[0] = false;
  ps_pre_struc_cpki.set_size(1, 1);
  ps_pre_struc_cpki[0] = rtNaN;
  //  pulseOut.tag_id                     = uint32(0);%ID is a string
  //  pulseOut.detector_dir               = currDir;%ID is a string
  //  pulseOut.frequency                  = 0;
  //  pulseOut.start_time.sec             =  int32(0);
  //  pulseOut.start_time.nanosec         = uint32(0);
  //  pulseOut.end_time.sec               =  int32(0);
  //  pulseOut.end_time.nanosec           = uint32(0);
  //  pulseOut.predict_next_start.sec     =  int32(0);
  //  pulseOut.predict_next_start.nanosec = uint32(0);
  //  pulseOut.predict_next_end.sec       =  int32(0);
  //  pulseOut.predict_next_end.nanosec   = uint32(0);
  //  pulseOut.snr                        = 0;
  //  pulseOut.stft_score                 = 0;
  //  pulseOut.group_ind                  = uint16(0);
  //  pulseOut.group_snr                  = double(0);
  //  pulseOut.detection_status           = false;
  //  pulseOut.confirmed_status           = false;
  val = udpSenderSetup(50000.0);
  if (val <= 0) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  //  The specified frame size must exactly match the size of udp packets sent
  //  out by the channelizer.
  udpReceiver.init(Config.contents.portData);
  std::printf("Startup set 6 complete. \n");
  std::fflush(stdout);
  //  Preallocate X and Xhold so that coder knows the data types.
  coder::wgn(dcv);
  for (i = 0; i < 1000; i++) {
    exampleData[i].re = static_cast<float>(dcv[i].re);
    exampleData[i].im = static_cast<float>(dcv[i].im);
  }
  // UNTITLED2 Construct an instance of this class
  //    Detailed explanation goes here
  Xhold_tmp.trials = 100U;
  Xhold_tmp.pf = Config.contents.falseAlarmProb;
  Xhold_tmp.evMuParam = 0.0;
  Xhold_tmp.evSigmaParam = 0.0;
  Xhold_tmp.threshVecFine.set_size(1);
  Xhold_tmp.threshVecFine[0] = 0.0;
  Xhold = lobj_20.init(exampleData, Config.contents.Fs, pulseStatsPriori,
                       Xhold_tmp);
  // UNTITLED2 Construct an instance of this class
  //    Detailed explanation goes here
  X.init(exampleData, Config.contents.Fs, pulseStatsPriori, lobj_21[0],
         lobj_19[2]);
  Xhold->spectro(lobj_19[1]);
  X.spectro(lobj_19[0]);
  std::printf("Startup set 7 complete. \n");
  std::fflush(stdout);
  // Initialize loop variables
  resetBuffersFlag = true;
  framesReceived = 0.0;
  segmentsProcessed = 0.0;
  suggestedMode = 'S';
  fLock = false;
  staleDataFlag = true;
  // Force buffer  flush on start
  cleanBuffer = true;
  trackedCount = 0.0;
  b_this.init();
  startTime = std::round(b_this.data.re / 1000.0 * 1.0E+6) / 1.0E+6;
  // sysClockElapsedTime = 0;
  previousPulseTime = 0.0;
  iqDataToWrite.set_size(0, 0);
  groupSeqCounter = 0.0;
  std::printf("Startup set 8 complete. Starting processing... \n");
  std::fflush(stdout);
  expectedNextTimeStamp = 0.0;
  currDir_size[0] = 1;
  currDir_size[1] = 1023;
  while (1) {
    int n;
    int nPulseList;
    unsigned int timeStampNanoSec;
    unsigned int timeStampSec;
    // i <= maxInd
    if (resetBuffersFlag) {
      asyncDataBuff.reset();
      asyncTimeBuff.reset();
      asyncWriteBuff.reset();
      resetBuffersFlag = false;
      cleanBuffer = true;
    }
    //             %% Get data
    udpReceiver.receive(dataReceived_data);
    //             %% Flush UDP buffer if data in the buffer is stale.
    if (staleDataFlag) {
      std::printf("********STALE DATA FLAG: %u *********\n", 1U);
      std::fflush(stdout);
      std::printf("********CLEARING UDP DATA BUFFER*********\n");
      std::fflush(stdout);
      udpReceiverClear(udpReceiver.udpReceiver);
      staleDataFlag = false;
      std::printf("********RESETTING TIMES*********\n");
      std::fflush(stdout);
      // startTime = round(posixtime(datetime('now'))*1000000)/1000000;
      framesReceived = 0.0;
      b_this.init();
      startTime = std::round(b_this.data.re / 1000.0 * 1.0E+6) / 1.0E+6;
      coder::tic();
    }
    //             %% Wait for new data if none ready, else put data in buffers
    // timeStamp      = 10^-3*singlecomplex2int(dataReceived(1)); % OLD TIME
    // STAMP METHOD
    std::memcpy((void *)&timeStampSec, (void *)&dataReceived_data[0].re,
                (unsigned int)((size_t)1 * sizeof(unsigned int)));
    std::memcpy((void *)&timeStampNanoSec, (void *)&dataReceived_data[0].im,
                (unsigned int)((size_t)1 * sizeof(unsigned int)));
    timeStamp = static_cast<double>(timeStampSec) +
                1.0E-9 * static_cast<double>(timeStampNanoSec);
    //  OLD TIME STAMP METHOD
    coder::internal::indexShapeCheck(1024, currDir_size);
    //  OLD TIME STAMP METHOD
    // timeVector     = timeStamp+1/Config.Fs*(0:(numel(iqData)-1)).';% OLD TIME
    // STAMP METHOD
    if (framesReceived == 0.0) {
      iqDataToWrite.set_size(1023, 1);
      for (i = 0; i < 1023; i++) {
        iqDataToWrite[i] = dataReceived_data[i + 1];
      }
      // dataFirstTimeStamp = timeStamp;
    } else {
      timeDiff = timeStamp - expectedNextTimeStamp;
      // fprintf('Current Received Time Stamp: %f \t Expected Time Stamp: %f \t
      // Diff: %f \n',timeStamp, expectedNextTimeStamp, timeDiff)
      t9_fp = Config.contents.tp / 2.0;
      if (std::abs(timeDiff) < t9_fp) {
        iqDataToWrite.set_size(1023, 1);
        for (i = 0; i < 1023; i++) {
          iqDataToWrite[i] = dataReceived_data[i + 1];
        }
      } else if ((timeDiff >= t9_fp) && (timeDiff < Config.contents.tip)) {
        unsigned long u;
        // missed samples but not a whole lot
        timeDiff = std::round(timeDiff * Config.contents.Fs);
        if (timeDiff < 1.8446744073709552E+19) {
          if (timeDiff >= 0.0) {
            u = static_cast<unsigned long>(timeDiff);
          } else {
            u = 0UL;
          }
        } else if (timeDiff >= 1.8446744073709552E+19) {
          u = MAX_uint64_T;
        } else {
          u = 0UL;
        }
        std::printf(
            "Missing samples detected. Filling with zeros for %lu samples.", u);
        std::fflush(stdout);
        if (!(timeDiff >= 0.0)) {
          rtNonNegativeError(timeDiff, r_emlrtDCI);
        }
        if (timeDiff != static_cast<int>(timeDiff)) {
          rtIntegerError(timeDiff, s_emlrtDCI);
        }
        loop_ub = static_cast<int>(timeDiff);
        r.set_size(static_cast<int>(timeDiff));
        for (i = 0; i < loop_ub; i++) {
          r[i].re = 0U;
          r[i].im = 0U;
        }
        if (static_cast<int>(timeDiff) != r.size(0)) {
          rtSizeEq1DError(static_cast<int>(timeDiff), r.size(0), g_emlrtECI);
        }
        b_iqDataToWrite.set_size(static_cast<int>(timeDiff) + 1023);
        for (i = 0; i < loop_ub; i++) {
          b_iqDataToWrite[i].re = 0.0F;
          b_iqDataToWrite[i].im = static_cast<signed char>(r[i].im);
        }
        for (i = 0; i < 1023; i++) {
          b_iqDataToWrite[i + static_cast<int>(timeDiff)] =
              dataReceived_data[i + 1];
        }
        iqDataToWrite.set_size(b_iqDataToWrite.size(0), 1);
        loop_ub = b_iqDataToWrite.size(0);
        for (i = 0; i < loop_ub; i++) {
          iqDataToWrite[i] = b_iqDataToWrite[i];
        }
      } else if (((timeDiff >= t9_fp) && (timeDiff >= Config.contents.tip)) ||
                 (timeDiff < -Config.contents.tp / 2.0)) {
        //  %missed a lot of samples. Reset buffers
        // predictions is ahead of recently received packet. Shouldn't ever
        // happen. If it is, reset the incoming data
        staleDataFlag = true;
        resetBuffersFlag = true;
        suggestedMode = 'S';
        iqDataToWrite.set_size(0, 1);
      }
    }
    nPulseList = iqDataToWrite.size(0) * iqDataToWrite.size(1);
    n = nPulseList - 1;
    if (nPulseList - 1 < 0) {
      groupSNRList.set_size(1, 0);
    } else {
      groupSNRList.set_size(1, nPulseList);
      for (i = 0; i <= n; i++) {
        groupSNRList[i] = i;
      }
    }
    timeDiff = 1.0 / Config.contents.Fs;
    timeVector.set_size(groupSNRList.size(1));
    loop_ub = groupSNRList.size(1);
    for (i = 0; i < loop_ub; i++) {
      timeVector[i] = timeStamp + timeDiff * groupSNRList[i];
    }
    expectedNextTimeStamp = timeStamp + timeDiff * 1023.0;
    framesReceived++;
    //                 % Parse the incoming data and sample count.
    //                 % and fill in any missing data with zeros.
    //                  framesReceived = framesReceived + 1;
    //
    //                  iqData           = dataReceived(1:end-1);
    //
    //                  nReceived        = uint64(numel(iqData));
    //
    //                  currSampleCount  = nextSampleCount + nReceived;
    //                  %This is the number of samples transmitted by the
    //                  %upstream process (ideal if none are dropped)
    //                  %If this is the first packet, calculate the offset
    //                  %sample count since the upstream processess may have
    //                  %started a while ago and its sample count may not be
    //                  zero if framesReceived == 1
    //                      startTime =
    //                      round(posixtime(datetime('now'))*1000000)/1000000;
    //                      sampleOffset = rawIdealSampleCount - nReceived;
    //                      %To estimate the timestamp of the sample before the
    //                      %first one in this first frame we go back in time
    //                      %from the start time.
    //                      lastTimeStamp = startTime - (double(nReceived) + 1)
    //                      * 1/Config.Fs;
    //                  end
    //
    //                  idealSampleCount = rawIdealSampleCount - sampleOffset;
    //
    //                  missingSamples  = idealSampleCount - currSampleCount;
    //
    //                  if missingSamples > 0
    //
    //                      zerosFill = single(zeros(missingSamples, 1)) + ...
    //                                      1i*single(zeros(missingSamples, 1));
    //
    //                      iqDataToWrite = [zerosFill(:); iqData];
    //
    //                      nextSampleCount = nextSampleCount + nReceived +
    //                      missingSamples;
    //
    //                      fprintf('Missing samples detected. Filling with
    //                      zeros for %u samples.',missingSamples);
    //
    //                  elseif missingSamples < 0
    //
    //                      error('UAV-RT: Number of samples transmitted to the
    //                      detector is less than that expected by the detector.
    //                      Upstream processes (channelizer) may be transmitting
    //                      more than 1024 IQ data samples per packet. This is
    //                      not supported by this detetor.')
    //
    //                  else
    //
    //                      iqDataToWrite = iqData;
    //
    //                      nextSampleCount = nextSampleCount + nReceived;
    //
    //                  end
    //
    //  fprintf('nReceived: %u \t currSampleCount: %u \t idealSampleCount: %u \t
    //  rawIdealSampleCount: %u \t missingSamples: %u numel(iqData): %u
    //  numel(iqDataToWrite): %u nextSampleCount: %u \t\n',nReceived,
    //  currSampleCount, idealSampleCount, rawIdealSampleCount, missingSamples,
    //  uint64(numel(iqData)), uint64(numel(iqDataToWrite)), nextSampleCount)
    //
    //                  timeVector = lastTimeStamp + ...
    //                               (1 : numel(iqDataToWrite)).' * 1/Config.Fs;
    //                  lastTimeStamp = timeVector(end);
    // Write out data and time.
    c_iqDataToWrite = iqDataToWrite.reshape(nPulseList);
    asyncDataBuff.write(c_iqDataToWrite);
    asyncTimeBuff.write(timeVector);
    std::copy(&dataReceived_data[1], &dataReceived_data[1024],
              &b_dataReceived_data[0]);
    asyncWriteBuff.write(b_dataReceived_data);
    // asyncWriteBuff.write([dataReceived;
    // int2singlecomplex(timeAtPacketReceive*10^3)]);
    if ((asyncWriteBuff.pBuffer.WritePointer >= 0) &&
        (asyncWriteBuff.pBuffer.ReadPointer <
         asyncWriteBuff.pBuffer.WritePointer - MAX_int32_T)) {
      n = MAX_int32_T;
    } else if ((asyncWriteBuff.pBuffer.WritePointer < 0) &&
               (asyncWriteBuff.pBuffer.ReadPointer >
                asyncWriteBuff.pBuffer.WritePointer - MIN_int32_T)) {
      n = MIN_int32_T;
    } else {
      n = asyncWriteBuff.pBuffer.WritePointer -
          asyncWriteBuff.pBuffer.ReadPointer;
    }
    if (n < -2147483647) {
      n = MIN_int32_T;
    } else {
      n--;
    }
    if (asyncWriteBuff.pBuffer.ReadPointer < -2146882997) {
      nPulseList = MAX_int32_T;
    } else {
      nPulseList = 600650 - asyncWriteBuff.pBuffer.ReadPointer;
    }
    if ((nPulseList < 0) &&
        (asyncWriteBuff.pBuffer.WritePointer < MIN_int32_T - nPulseList)) {
      nPulseList = MIN_int32_T;
    } else if ((nPulseList > 0) && (asyncWriteBuff.pBuffer.WritePointer >
                                    MAX_int32_T - nPulseList)) {
      nPulseList = MAX_int32_T;
    } else {
      nPulseList += asyncWriteBuff.pBuffer.WritePointer;
    }
    if (asyncWriteBuff.pBuffer.ReadPointer <
        asyncWriteBuff.pBuffer.WritePointer) {
      nPulseList = n;
    } else if (asyncWriteBuff.pBuffer.ReadPointer ==
               asyncWriteBuff.pBuffer.WritePointer) {
      nPulseList = 600650;
    }
    if (nPulseList >= dataWriterSamples) {
      asyncWriteBuff.read(dataWriterBuffData);
      if (fileid != -1) {
        interleaveComplexVector(dataWriterBuffData, r1);
        coder::b_fwrite(static_cast<double>(fileid), r1);
      }
    }
    // end
    //                 %% Process data if there is enough in the buffers
    t9_det_dec = ((asyncDataBuff.pBuffer.WritePointer >= 0) &&
                  (asyncDataBuff.pBuffer.ReadPointer <
                   asyncDataBuff.pBuffer.WritePointer - MAX_int32_T));
    if (t9_det_dec) {
      n = MAX_int32_T;
    } else if ((asyncDataBuff.pBuffer.WritePointer < 0) &&
               (asyncDataBuff.pBuffer.ReadPointer >
                asyncDataBuff.pBuffer.WritePointer - MIN_int32_T)) {
      n = MIN_int32_T;
    } else {
      n = asyncDataBuff.pBuffer.WritePointer -
          asyncDataBuff.pBuffer.ReadPointer;
    }
    if (n < -2147483647) {
      n = MIN_int32_T;
    } else {
      n--;
    }
    if (asyncDataBuff.pBuffer.ReadPointer < -2141683327) {
      nPulseList = MAX_int32_T;
    } else {
      nPulseList = 5800320 - asyncDataBuff.pBuffer.ReadPointer;
    }
    if ((nPulseList < 0) &&
        (asyncDataBuff.pBuffer.WritePointer < MIN_int32_T - nPulseList)) {
      nPulseList = MIN_int32_T;
    } else if ((nPulseList > 0) && (asyncDataBuff.pBuffer.WritePointer >
                                    MAX_int32_T - nPulseList)) {
      nPulseList = MAX_int32_T;
    } else {
      nPulseList += asyncDataBuff.pBuffer.WritePointer;
    }
    if (asyncDataBuff.pBuffer.ReadPointer <
        asyncDataBuff.pBuffer.WritePointer) {
      nPulseList = n;
    } else if (asyncDataBuff.pBuffer.ReadPointer ==
               asyncDataBuff.pBuffer.WritePointer) {
      nPulseList = 5800320;
    }
    if (nPulseList >= sampsForKPulses.contents + overlapSamples.contents) {
      double processingStartToc;
      std::printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
      std::fflush(stdout);
      t9_fp = std::round(sampsForKPulses.contents);
      if (t9_fp < 4.294967296E+9) {
        if (t9_fp >= 0.0) {
          timeStampSec = static_cast<unsigned int>(t9_fp);
        } else {
          timeStampSec = 0U;
        }
      } else if (t9_fp >= 4.294967296E+9) {
        timeStampSec = MAX_uint32_T;
      } else {
        timeStampSec = 0U;
      }
      t9_fp = std::round(overlapSamples.contents);
      if (t9_fp < 4.294967296E+9) {
        if (t9_fp >= 0.0) {
          timeStampNanoSec = static_cast<unsigned int>(t9_fp);
        } else {
          timeStampNanoSec = 0U;
        }
      } else if (t9_fp >= 4.294967296E+9) {
        timeStampNanoSec = MAX_uint32_T;
      } else {
        timeStampNanoSec = 0U;
      }
      std::printf("Buffer Full || sampsForKPulses: %u, overlapSamples: %u,\n",
                  timeStampSec, timeStampNanoSec);
      std::fflush(stdout);
      if (t9_det_dec) {
        n = MAX_int32_T;
      } else if ((asyncDataBuff.pBuffer.WritePointer < 0) &&
                 (asyncDataBuff.pBuffer.ReadPointer >
                  asyncDataBuff.pBuffer.WritePointer - MIN_int32_T)) {
        n = MIN_int32_T;
      } else {
        n = asyncDataBuff.pBuffer.WritePointer -
            asyncDataBuff.pBuffer.ReadPointer;
      }
      if (n < -2147483647) {
        n = MIN_int32_T;
      } else {
        n--;
      }
      if (asyncDataBuff.pBuffer.ReadPointer < -2141683327) {
        nPulseList = MAX_int32_T;
      } else {
        nPulseList = 5800320 - asyncDataBuff.pBuffer.ReadPointer;
      }
      if ((nPulseList < 0) &&
          (asyncDataBuff.pBuffer.WritePointer < MIN_int32_T - nPulseList)) {
        nPulseList = MIN_int32_T;
      } else if ((nPulseList > 0) && (asyncDataBuff.pBuffer.WritePointer >
                                      MAX_int32_T - nPulseList)) {
        nPulseList = MAX_int32_T;
      } else {
        nPulseList += asyncDataBuff.pBuffer.WritePointer;
      }
      if (asyncDataBuff.pBuffer.ReadPointer <
          asyncDataBuff.pBuffer.WritePointer) {
        nPulseList = n;
      } else if (asyncDataBuff.pBuffer.ReadPointer ==
                 asyncDataBuff.pBuffer.WritePointer) {
        nPulseList = 5800320;
      }
      std::printf("Running...Buffer full with %d samples. Processing. \n",
                  nPulseList);
      std::fflush(stdout);
      processingStartToc = coder::toc();
      if (cleanBuffer) {
        // Overlap reads back into the buffer, but there
        // isn't anything back there on the first segment.
        // Using an overlap will fill the output with
        // overlapSamples of zeros at beginning
        // of x if you specify overlap here. Don't want that
        // so specify zero overlap for first read after
        // cleaning buffer
        asyncDataBuff.read(sampsForKPulses.contents, x);
        asyncTimeBuff.read(sampsForKPulses.contents, t);
        cleanBuffer = false;
      } else {
        asyncDataBuff.read(sampsForKPulses.contents, overlapSamples.contents,
                           x);
        asyncTimeBuff.read(sampsForKPulses.contents, overlapSamples.contents,
                           t);
      }
      if (timeVector.size(0) < 1) {
        rtDynamicBoundsError(timeVector.size(0), 1, timeVector.size(0),
                             y_emlrtBCI);
      }
      b_this.init();
      std::printf("Sample elapsed seconds: %f \t Posix elapsed seconds: %f \n",
                  timeVector[timeVector.size(0) - 1] - startTime,
                  std::round(b_this.data.re / 1000.0 * 1.0E+6) / 1.0E+6 -
                      startTime);
      std::fflush(stdout);
      // plot(t, abs(x)); hold on
      // Check the timestamps in the buffer for gaps larger
      // than the max interpulse uncertainty. If there are
      // enough dropped packets such that the time is shifted
      // by more than the interpulse uncertainty, then the
      // detection will likely fail or produces bad results. In
      // this case. Skip the processing and clear the buffer.
      coder::diff(t, timeVector);
      b_timeVector.set_size(timeVector.size(0));
      loop_ub = timeVector.size(0);
      for (i = 0; i < loop_ub; i++) {
        b_timeVector[i] = timeVector[i] - timeDiff;
      }
      timeDiff = coder::blockedSummation(b_timeVector, b_timeVector.size(0));
      if ((Config.contents.K > 1.0) &&
          (timeDiff > Config.contents.tipu + Config.contents.tipj)) {
        std::printf("Significant time differences found in timestamp record. "
                    "Skipping processing and clearing buffers.\n");
        std::fflush(stdout);
        resetBuffersFlag = true;
        staleDataFlag = true;
      } else {
        unsigned int validatedHoleFilling[3];
        int pulseCount;
        unsigned int varargin_3;
        char b_varargin_1[2];
        if (t.size(0) < 1) {
          rtDynamicBoundsError(1, 1, t.size(0), ab_emlrtBCI);
        }
        std::printf("Running...Building priori and waveform. \n");
        std::fflush(stdout);
        // Set the priori info
        if (configUpdatedFlag) {
          // Initialize states for operational modes
          if (Config.contents.opMode.eq()) {
            n = 0;
          } else if (Config.contents.opMode.b_eq()) {
            n = 1;
          } else if (Config.contents.opMode.c_eq()) {
            n = 2;
          } else if (Config.contents.opMode.d_eq()) {
            n = 3;
          } else {
            n = -1;
          }
          switch (n) {
          case 0:
            fLock = false;
            break;
          case 1:
            fLock = true;
            break;
          case 2:
            fLock = false;
            break;
          case 3:
            fLock = false;
            break;
          default:
            fLock = false;
            break;
          }
          detectorPulse.A = makepulsestruc(
              detectorPulse.t_next, detectorPulse.mode, detectorPulse.P,
              detectorPulse.SNR, detectorPulse.yw, detectorPulse.t_0,
              detectorPulse.t_f, detectorPulse.fp, detectorPulse.fstart,
              detectorPulse.fend, detectorPulse.det_dec, detectorPulse.con_dec);
          timeDiff = makepulsestruc(expl_temp.t_next, expl_temp.mode, timeStamp,
                                    t9_SNR, t9_yw, T, t9_t_f, t9_fp, t9_fstart,
                                    t9_fend, t9_det_dec, t9_con_dec);
          expl_temp.con_dec = t9_con_dec;
          expl_temp.det_dec = t9_det_dec;
          expl_temp.fend = t9_fend;
          expl_temp.fstart = t9_fstart;
          expl_temp.fp = t9_fp;
          expl_temp.t_f = t9_t_f;
          expl_temp.t_0 = T;
          expl_temp.yw = t9_yw;
          expl_temp.SNR = t9_SNR;
          expl_temp.P = timeStamp;
          expl_temp.A = timeDiff;
          pulseStatsPriori = lobj_15.init(
              Config.contents.tp, Config.contents.tip, Config.contents.tipu,
              Config.contents.tipj,
              1.0E-5 * std::abs(Config.contents.tagFreqMHz -
                                Config.contents.channelCenterFreqMHz),
              detectorPulse, expl_temp);
          configUpdatedFlag = false;
        } else {
          pulseStatsPriori = lobj_18.c_init(
              t9_fstart, t9_fend, ps_pre_struc_t_ipu, ps_pre_struc_t_ipj,
              ps_pre_struc_fp, ps_pre_struc_fstart, ps_pre_struc_fend,
              ps_pre_struc_tmplt, (char *)&mode, ps_pre_struc_pl,
              ps_pre_struc_clst, ps_pre_struc_cmsk, ps_pre_struc_cpki);
        }
        //                         %% PRIMARY PROCESSING BLOCK
        // Prep waveform for processing/detection
        b_X.init(x, Config.contents.Fs, t[0], pulseStatsPriori, Xhold_tmp,
                 lobj_17, lobj_16);
        b_X.K = Config.contents.K;
        t9_fp = std::round(b_X.N);
        if (t9_fp < 4.294967296E+9) {
          if (t9_fp >= 0.0) {
            timeStampSec = static_cast<unsigned int>(t9_fp);
          } else {
            timeStampSec = 0U;
          }
        } else if (t9_fp >= 4.294967296E+9) {
          timeStampSec = MAX_uint32_T;
        } else {
          timeStampSec = 0U;
        }
        t9_fp = std::round(b_X.M);
        if (t9_fp < 4.294967296E+9) {
          if (t9_fp >= 0.0) {
            timeStampNanoSec = static_cast<unsigned int>(t9_fp);
          } else {
            timeStampNanoSec = 0U;
          }
        } else if (t9_fp >= 4.294967296E+9) {
          timeStampNanoSec = MAX_uint32_T;
        } else {
          timeStampNanoSec = 0U;
        }
        t9_fp = std::round(b_X.J);
        if (t9_fp < 4.294967296E+9) {
          if (t9_fp >= 0.0) {
            varargin_3 = static_cast<unsigned int>(t9_fp);
          } else {
            varargin_3 = 0U;
          }
        } else if (t9_fp >= 4.294967296E+9) {
          varargin_3 = MAX_uint32_T;
        } else {
          varargin_3 = 0U;
        }
        coder::internal::validate_print_arguments(
            timeStampSec, timeStampNanoSec, varargin_3, validatedHoleFilling);
        std::printf("Current interpulse params || N: %u, M: %u, J: %u,\n",
                    validatedHoleFilling[0], validatedHoleFilling[1],
                    validatedHoleFilling[2]);
        std::fflush(stdout);
        b_X.setprioridependentprops(b_X.ps_pre);
        timeStampSec = static_cast<unsigned int>(b_X.x.size(1));
        std::printf("Samples in waveform: %u \n", timeStampSec);
        std::fflush(stdout);
        timeDiff = coder::toc();
        std::printf("Computing STFT...");
        std::fflush(stdout);
        b_X.spectro(lobj_14);
        timeDiff = coder::toc() - timeDiff;
        std::printf("complete. Elapsed time: %f seconds \n", timeDiff);
        std::fflush(stdout);
        std::printf("Building weighting matrix ...");
        std::fflush(stdout);
        timeDiff = coder::toc();
        b_X.setweightingmatrix();
        timeDiff = coder::toc() - timeDiff;
        std::printf("complete. Elapsed time: %f seconds \n", timeDiff);
        std::fflush(stdout);
        if (suggestedMode == 'S') {
          n = 0;
        } else if (suggestedMode == 'C') {
          n = 1;
        } else if (suggestedMode == 'T') {
          n = 2;
        } else {
          n = -1;
        }
        switch (n) {
        case 0:
          if (fLock) {
            mode = 'I';
          } else {
            mode = 'D';
          }
          break;
        case 1:
          mode = 'C';
          break;
        case 2:
          mode = 'T';
          trackedCount++;
          break;
        default:
          std::printf("UAV-RT: Unsupported mode requested. Defaulting to "
                      "Discovery (D) mode.");
          std::fflush(stdout);
          mode = 'D';
          break;
        }
        if (coder::internal::b_strcmp(Config.contents.opMode)) {
          mode = 'D';
        }
        timeDiff = coder::toc();
        if (segmentsProcessed == 0.0) {
          std::printf("Building thresholds  ...");
          std::fflush(stdout);
          _in = b_X.thresh;
          _in.makenewthreshold(b_X);
          b_X.thresh = _in;
        } else {
          std::printf("Setting thresholds from previous waveform  ...");
          std::fflush(stdout);
          // X.thresh = X.thresh.setthreshold(X,Xhold);
          _in = Xhold->thresh;
          b_X.thresh = _in;
        }
        timeDiff = coder::toc() - timeDiff;
        std::printf("complete. Elapsed time: %f seconds \n", timeDiff);
        std::fflush(stdout);
        timeStampSec = static_cast<unsigned int>(b_X.stft->S.size(1));
        std::printf("Time windows in S: %u \n", timeStampSec);
        std::fflush(stdout);
        timeDiff = coder::toc();
        t9_fp = std::round(Config.contents.ID);
        if (t9_fp < 4.294967296E+9) {
          if (t9_fp >= 0.0) {
            timeStampSec = static_cast<unsigned int>(t9_fp);
          } else {
            timeStampSec = 0U;
          }
        } else if (t9_fp >= 4.294967296E+9) {
          timeStampSec = MAX_uint32_T;
        } else {
          timeStampSec = 0U;
        }
        doublesBuffer[0] = timeStampSec;
        std::memset(&doublesBuffer[1], 0, 11U * sizeof(double));
        //  % self.frequency_hz ...
        //  % self.start_time_seconds ...
        //  % self.predict_next_start_seconds ...
        //  % self.snr ...
        //  % self.stft_score ...
        //  % self.group_seq_counter ...
        //  % self.group_ind ...
        //  % self.group_snr ...
        //  % self.detection_status ...
        //  % self.confirmed_status ...
        //  % self.noise_psd ...
        udpSenderSendDoubles(val, &doublesBuffer[0], 12U);
        std::printf("Finding pulses...");
        std::fflush(stdout);
        b_varargin_1[0] = mode;
        b_varargin_1[1] = '\x00';
        std::printf("PROCESSING IN %s MODE \n", &b_varargin_1[0]);
        std::fflush(stdout);
        std::printf("====================================\n");
        std::fflush(stdout);
        b_X.process(mode, Config.contents.excldFreqs);
        timeDiff = coder::toc() - timeDiff;
        std::printf("complete. Elapsed time: %f seconds \n", timeDiff);
        std::fflush(stdout);
        timeDiff = coder::toc() - processingStartToc;
        std::printf("TOTAL PULSE PROCESSING TIME: %f seconds \n", timeDiff);
        std::fflush(stdout);
        //                         %% PREP FOR NEXT LOOP
        // Latch/Release the frequency lock and setup the
        // suggested mode
        suggestedMode = b_X.ps_pos->mode;
        ps_pre_struc_pl.set_size(1, b_X.ps_pos->pl.size(1));
        loop_ub = b_X.ps_pos->pl.size(0) * b_X.ps_pos->pl.size(1) - 1;
        for (i = 0; i <= loop_ub; i++) {
          ps_pre_struc_pl[i] = b_X.ps_pos->pl[i];
        }
        n = ps_pre_struc_pl.size(1);
        if (ps_pre_struc_pl.size(1) == 0) {
          i = 0;
        } else {
          i = ps_pre_struc_pl.size(1);
        }
        pulsesToSkip.set_size(1, i);
        if (ps_pre_struc_pl.size(1) > 2147483646) {
          coder::check_forloop_overflow_error();
        }
        for (loop_ub = 0; loop_ub < n; loop_ub++) {
          pulsesToSkip[loop_ub] = ps_pre_struc_pl[loop_ub].con_dec;
        }
        coder::all(pulsesToSkip, r2);
        if (coder::internal::ifWhileCond(r2)) {
          // Check if all were confirmed
          fLock = true;
        }
        // We only ever release if we are in softlock mode and
        // only do so in that case if we are no longer confirming
        // pulses.
        if (coder::internal::c_strcmp(Config.contents.opMode)) {
          n = r2.size(0);
          loop_ub = r2.size(0);
          for (i = 0; i < loop_ub; i++) {
            tmp_data = !r2[i];
          }
          b_tmp_data.set(&tmp_data, n);
          if (coder::internal::ifWhileCond(b_tmp_data)) {
            fLock = false;
          }
        }
        // Decide when/how the priori is updated for the next
        // segment's processing.
        if (coder::internal::ifWhileCond(r2) &&
            ((mode == 'C') || (mode == 'T'))) {
          ps_pre_struc_pl.set_size(1, b_X.ps_pos->pl.size(1));
          loop_ub = b_X.ps_pos->pl.size(0) * b_X.ps_pos->pl.size(1) - 1;
          for (i = 0; i <= loop_ub; i++) {
            ps_pre_struc_pl[i] = b_X.ps_pos->pl[i];
          }
          b_X.ps_pos->updateposteriori(b_X.ps_pre, ps_pre_struc_pl);
          if (trackedCount > 5.0) {
            trackedCount = 0.0;
            ps_pre_struc_pl.set_size(1, b_X.ps_pos->pl.size(1));
            loop_ub = b_X.ps_pos->pl.size(0) * b_X.ps_pos->pl.size(1) - 1;
            for (i = 0; i <= loop_ub; i++) {
              ps_pre_struc_pl[i] = b_X.ps_pos->pl[i];
            }
            b_X.ps_pos->b_updateposteriori(b_X.ps_pre, ps_pre_struc_pl);
          }
        }
        // Check lagging processing
        if ((segmentsProcessed != 0.0) && (Config.contents.K > 1.0) &&
            (timeDiff > 0.9 * sampsForKPulses.contents / Config.contents.Fs)) {
          // Config.K = Config.K - 1;
          timeDiff = std::round(Config.contents.K - 1.0);
          if (timeDiff < 4.294967296E+9) {
            timeStampSec = static_cast<unsigned int>(timeDiff);
          } else {
            timeStampSec = MAX_uint32_T;
          }
          std::printf("WARNING!!! PROCESSING TIME TOOK LONGER THAN WAVEFORM "
                      "LENGTH. STREAMING NOT POSSIBLE. TRY REDUCING NUMBER OF "
                      "PULSES CONSIDERED BY"
                      " 1 TO K = %u \n",
                      timeStampSec);
          std::fflush(stdout);
          std::printf("Resetting all internal data buffers and udp buffers to "
                      "clear potential stale data. \n");
          std::fflush(stdout);
          resetBuffersFlag = true;
          staleDataFlag = true;
          suggestedMode = 'S';
        }
        segmentsProcessed++;
        // tic
        timeDiff = coder::toc();
        // Prepare priori for next segment
        std::printf("Updating priori...\n");
        std::fflush(stdout);
        t9_fstart = b_X.ps_pos->t_p;
        t9_fend = b_X.ps_pos->t_ip;
        ps_pre_struc_t_ipu = b_X.ps_pos->t_ipu;
        ps_pre_struc_t_ipj = b_X.ps_pos->t_ipj;
        ps_pre_struc_fp = b_X.ps_pos->fp;
        ps_pre_struc_fstart = b_X.ps_pos->fstart;
        ps_pre_struc_fend = b_X.ps_pos->fend;
        ps_pre_struc_tmplt[0] = b_X.ps_pos->tmplt[0];
        ps_pre_struc_tmplt[1] = b_X.ps_pos->tmplt[1];
        mode = b_X.ps_pos->mode;
        ps_pre_struc_pl.set_size(1, b_X.ps_pos->pl.size(1));
        loop_ub = b_X.ps_pos->pl.size(1);
        for (i = 0; i < loop_ub; i++) {
          ps_pre_struc_pl[i] = b_X.ps_pos->pl[i];
        }
        ps_pre_struc_clst.set_size(b_X.ps_pos->clst.size(0),
                                   b_X.ps_pos->clst.size(1));
        loop_ub = b_X.ps_pos->clst.size(0) * b_X.ps_pos->clst.size(1);
        for (i = 0; i < loop_ub; i++) {
          ps_pre_struc_clst[i] = b_X.ps_pos->clst[i];
        }
        ps_pre_struc_cmsk.set_size(b_X.ps_pos->cmsk.size(0),
                                   b_X.ps_pos->cmsk.size(1));
        loop_ub = b_X.ps_pos->cmsk.size(0) * b_X.ps_pos->cmsk.size(1);
        for (i = 0; i < loop_ub; i++) {
          ps_pre_struc_cmsk[i] = b_X.ps_pos->cmsk[i];
        }
        ps_pre_struc_cpki.set_size(b_X.ps_pos->cpki.size(0),
                                   b_X.ps_pos->cpki.size(1));
        loop_ub = b_X.ps_pos->cpki.size(0) * b_X.ps_pos->cpki.size(1);
        for (i = 0; i < loop_ub; i++) {
          ps_pre_struc_cpki[i] = b_X.ps_pos->cpki[i];
        }
        updatebufferreadvariables(Config, stftOverlapFraction, overlapSamples,
                                  sampsForKPulses, b_X.ps_pos);
        timeDiff = coder::toc() - timeDiff;
        std::printf("complete. Elapsed time: %f seconds \n", timeDiff);
        std::fflush(stdout);
        // Deal with detected pulses
        // Xhold{mod(segmentsProcessed,maxSegments)} = X;%Keep a maxSegments
        // running record of waveforms for debugging in Matlab Xstruct =
        // obj2structrecursive(); Xhold = X;
        Xhold = waveformcopy(b_X, lobj_11, lobj_12[0], lobj_13);
        nPulseList = b_X.ps_pos->pl.size(1);
        pulsesToSkip.set_size(1, nPulseList);
        for (i = 0; i < nPulseList; i++) {
          pulsesToSkip[i] = false;
        }
        // Report pulses and check for repeat detections
        b_x.set_size(b_X.ps_pos->cpki.size(0), b_X.ps_pos->cpki.size(1));
        loop_ub = b_X.ps_pos->cpki.size(0) * b_X.ps_pos->cpki.size(1);
        for (i = 0; i < loop_ub; i++) {
          b_x[i] = b_X.ps_pos->cpki[i];
        }
        r3.set_size(b_x.size(0), b_x.size(1));
        loop_ub = b_x.size(0) * b_x.size(1);
        for (i = 0; i < loop_ub; i++) {
          r3[i] = !std::isnan(b_x[i]);
        }
        if (coder::internal::b_ifWhileCond(r3)) {
          for (int j{0}; j < nPulseList; j++) {
            i = b_X.ps_pos->pl.size(1);
            if (j + 1 > i) {
              rtDynamicBoundsError(j + 1, 1, i, bb_emlrtBCI);
            }
            timeDiff = b_X.ps_pos->pl[j].t_0;
            if (j + 1 > ps_pre_struc_pl.size(1)) {
              rtDynamicBoundsError(j + 1, 1, ps_pre_struc_pl.size(1),
                                   cb_emlrtBCI);
            }
            std::printf("Pulse at %f Hz detected. SNR: %f \n \t Confirmation "
                        "status: %u \n\t Interpulse time    : %f \n",
                        Config.contents.channelCenterFreqMHz +
                            ps_pre_struc_pl[j].fp * 1.0E-6,
                        ps_pre_struc_pl[j].SNR,
                        static_cast<unsigned int>(ps_pre_struc_pl[j].con_dec),
                        timeDiff - previousPulseTime);
            std::fflush(stdout);
            if (timeDiff - previousPulseTime < 0.1 * b_X.ps_pre->t_ip) {
              // Overlap occasionally will redetect the same pulse
              std::printf("(\t ^---This likely a repeat of a previously "
                          "detected pulse. Will not be transmitted. \n");
              std::fflush(stdout);
              if (j + 1 > pulsesToSkip.size(1)) {
                rtDynamicBoundsError(j + 1, 1, pulsesToSkip.size(1),
                                     db_emlrtBCI);
              }
              pulsesToSkip[j] = true;
            } else {
              previousPulseTime = timeDiff;
            }
          }
        } else {
          std::printf("No pulses detected \n");
          std::fflush(stdout);
        }
        pulseCount = 0;
        b_x.set_size(b_X.ps_pos->cpki.size(0), b_X.ps_pos->cpki.size(1));
        loop_ub = b_X.ps_pos->cpki.size(0) * b_X.ps_pos->cpki.size(1);
        for (i = 0; i < loop_ub; i++) {
          b_x[i] = b_X.ps_pos->cpki[i];
        }
        r3.set_size(b_x.size(0), b_x.size(1));
        loop_ub = b_x.size(0) * b_x.size(1);
        for (i = 0; i < loop_ub; i++) {
          r3[i] = !std::isnan(b_x[i]);
        }
        if (coder::internal::b_ifWhileCond(r3)) {
          std::printf("Transmitting pulse messages");
          std::fflush(stdout);
          if (nPulseList - 1 >= 0) {
            if (t9_fp < 4.294967296E+9) {
              if (t9_fp >= 0.0) {
                u1 = static_cast<unsigned int>(t9_fp);
              } else {
                u1 = 0U;
              }
            } else if (t9_fp >= 4.294967296E+9) {
              u1 = MAX_uint32_T;
            } else {
              u1 = 0U;
            }
            if (groupSeqCounter < 65536.0) {
              u2 = static_cast<unsigned short>(groupSeqCounter);
            } else {
              u2 = MAX_uint16_T;
            }
          }
          for (int j{0}; j < nPulseList; j++) {
            unsigned short u3;
            n = b_X.ps_pos->pl.size(1);
            c_X.set_size(n);
            loop_ub = n - 1;
            for (i = 0; i <= loop_ub; i++) {
              c_X[i] = b_X.ps_pos->pl[i];
            }
            n = c_X.size(0);
            if (c_X.size(0) == 0) {
              i = 0;
            } else {
              i = c_X.size(0);
            }
            groupSNRList.set_size(1, i);
            if (c_X.size(0) > 2147483646) {
              coder::check_forloop_overflow_error();
            }
            for (loop_ub = 0; loop_ub < n; loop_ub++) {
              groupSNRList[loop_ub] = c_X[loop_ub].SNR;
            }
            groupSNRList.set_size(1, groupSNRList.size(1));
            loop_ub = groupSNRList.size(1) - 1;
            for (i = 0; i <= loop_ub; i++) {
              timeDiff = groupSNRList[i] / 10.0;
              groupSNRList[i] = rt_powd_snf(10.0, timeDiff);
            }
            // Average SNR in dB
            n = groupSNRList.size(1);
            b_groupSNRList = groupSNRList.reshape(n);
            t9_SNR =
                coder::blockedSummation(b_groupSNRList, groupSNRList.size(1)) /
                static_cast<double>(groupSNRList.size(1));
            if (t9_SNR < 0.0) {
              rtErrorWithMessageID("log10", b_emlrtRTEI.fName,
                                   b_emlrtRTEI.lineNo);
            }
            t9_SNR = std::log10(t9_SNR);
            // 10log10 can produce complex results and group_snr required a real
            // value. Otherwise coder will generate type errors
            // 10*log10(mean(10.^([X.ps_pos.clst(X.ps_pos.cpki(j),:).SNR]/10)));%Average
            // SNR in dB
            //  Publish pulses to UDP
            i = b_X.ps_pos->pl.size(1);
            if (j + 1 > i) {
              rtDynamicBoundsError(j + 1, 1, i, eb_emlrtBCI);
            }
            detectorPulse = b_X.ps_pos->pl[j];
            t9_yw = b_X.stft->dt;
            T = b_X.stft->T;
            t9_t_f = rt_powd_snf(10.0, detectorPulse.SNR / 10.0);
            // See Notebook Entry 2023-07-07 for derivation
            if (j + 1 > pulsesToSkip.size(1)) {
              rtDynamicBoundsError(j + 1, 1, pulsesToSkip.size(1), fb_emlrtBCI);
            }
            if (!pulsesToSkip[j]) {
              //  UDP Send
              if (t9_fp < 4.294967296E+9) {
                if (t9_fp >= 0.0) {
                  timeStampSec = static_cast<unsigned int>(t9_fp);
                } else {
                  timeStampSec = 0U;
                }
              } else if (t9_fp >= 4.294967296E+9) {
                timeStampSec = MAX_uint32_T;
              } else {
                timeStampSec = 0U;
              }
              doublesBuffer[0] = timeStampSec;
              timeDiff =
                  std::round(Config.contents.channelCenterFreqMHz * 1.0E+6 +
                             detectorPulse.fp);
              if (timeDiff < 4.294967296E+9) {
                if (timeDiff >= 0.0) {
                  timeStampSec = static_cast<unsigned int>(timeDiff);
                } else {
                  timeStampSec = 0U;
                }
              } else if (timeDiff >= 4.294967296E+9) {
                timeStampSec = MAX_uint32_T;
              } else {
                timeStampSec = 0U;
              }
              doublesBuffer[1] = timeStampSec;
              doublesBuffer[2] = detectorPulse.t_0;
              doublesBuffer[3] = detectorPulse.t_next[0];
              doublesBuffer[4] = detectorPulse.SNR;
              doublesBuffer[5] = detectorPulse.yw;
              if (groupSeqCounter < 65536.0) {
                u3 = static_cast<unsigned short>(groupSeqCounter);
              } else {
                u3 = MAX_uint16_T;
              }
              doublesBuffer[6] = u3;
              if (static_cast<unsigned int>(j) + 1U < 65536U) {
                u3 = static_cast<unsigned short>(static_cast<double>(j) + 1.0);
              } else {
                u3 = MAX_uint16_T;
              }
              doublesBuffer[7] = u3;
              doublesBuffer[8] = 10.0 * t9_SNR;
              doublesBuffer[9] = detectorPulse.det_dec;
              doublesBuffer[10] = detectorPulse.con_dec;
              doublesBuffer[11] = detectorPulse.yw * (t9_yw * t9_yw) / T *
                                  (1.0 / (t9_t_f + 1.0));
              udpSenderSendDoubles(val, &doublesBuffer[0], 12U);
              //  ROS send
              std::printf("Skipping ROS2 Pulse send...\n");
              std::fflush(stdout);
              pulseCount++;
            }
            std::printf("EXPECTED GCS ENTRY:\n");
            std::fflush(stdout);
            // UNTITLED6 Summary of this function goes here
            //    Detailed explanation goes here
            // uint32(Config.ID);
            //  uint32((Config.channelCenterFreqMHz * 1e6) + detectorPulse.fp);
            //  detectorPulse.t_0;
            // detectorPulse.t_next(1);
            //  detectorPulse.SNR;
            // real(detectorPulse.yw);
            // groupSeqCounter;
            // uint16(j);
            // groupSNR;
            // real(detectorPulse.yw ) * dt^2 / T * (1 +
            // 10^(detectorPulse.SNR/10))^(-1); %See Notebook Entry 2023-07-07
            // for derivation
            //  uint8(detectorPulse.det_dec);
            // uint8(detectorPulse.con_dec);
            timeDiff =
                std::round(Config.contents.channelCenterFreqMHz * 1.0E+6 +
                           detectorPulse.fp);
            if (timeDiff < 4.294967296E+9) {
              if (timeDiff >= 0.0) {
                timeStampSec = static_cast<unsigned int>(timeDiff);
              } else {
                timeStampSec = 0U;
              }
            } else if (timeDiff >= 4.294967296E+9) {
              timeStampSec = MAX_uint32_T;
            } else {
              timeStampSec = 0U;
            }
            if (static_cast<unsigned int>(j) + 1U < 65536U) {
              u3 = static_cast<unsigned short>(static_cast<double>(j) + 1.0);
            } else {
              u3 = MAX_uint16_T;
            }
            std::printf(
                "%u, %u, %g, %g, %g, %g, %u, %u, %g, %g, %u, %u\n", u1,
                timeStampSec, detectorPulse.t_0, detectorPulse.t_next[0],
                detectorPulse.SNR, detectorPulse.yw, u2, u3, 10.0 * t9_SNR,
                detectorPulse.yw * (t9_yw * t9_yw) / T * (1.0 / (t9_t_f + 1.0)),
                static_cast<unsigned char>(detectorPulse.det_dec),
                static_cast<unsigned char>(detectorPulse.con_dec));
            std::fflush(stdout);
            //                                     end
          }
          groupSeqCounter++;
          std::printf("complete. Transmitted %u pulse(s).\n",
                      static_cast<unsigned int>(pulseCount));
          std::fflush(stdout);
        } else {
          std::printf("\n");
          std::fflush(stdout);
        }
        if (Config.contents.dataRecordPath.Value.size(1) - 4 < 1) {
          loop_ub = 0;
        } else {
          if (Config.contents.dataRecordPath.Value.size(1) < 1) {
            rtDynamicBoundsError(1, 1,
                                 Config.contents.dataRecordPath.Value.size(1),
                                 gb_emlrtBCI);
          }
          if ((Config.contents.dataRecordPath.Value.size(1) - 4 < 1) ||
              (Config.contents.dataRecordPath.Value.size(1) - 4 >
               Config.contents.dataRecordPath.Value.size(1))) {
            rtDynamicBoundsError(
                Config.contents.dataRecordPath.Value.size(1) - 4, 1,
                Config.contents.dataRecordPath.Value.size(1), hb_emlrtBCI);
          }
          loop_ub = Config.contents.dataRecordPath.Value.size(1) - 4;
        }
        varargin_1.set_size(1, loop_ub);
        for (i = 0; i < loop_ub; i++) {
          varargin_1[i] = Config.contents.dataRecordPath.Value[i];
        }
        coder::b_sprintf(varargin_1, startTime, b_X.t_0, waveformRecordPath);
        varargin_1.set_size(1, waveformRecordPath.size(1) + 1);
        loop_ub = waveformRecordPath.size(1);
        for (i = 0; i < loop_ub; i++) {
          varargin_1[i] = waveformRecordPath[i];
        }
        varargin_1[waveformRecordPath.size(1)] = '\x00';
        std::printf("Writing waveform record csv file: %s\n", &varargin_1[0]);
        std::fflush(stdout);
        wfmcsvwrite(b_X, Config.contents.channelCenterFreqMHz,
                    waveformRecordPath);
        std::printf("...complete.\n");
        std::fflush(stdout);
      }
      b_this.init();
      timeDiff = coder::toc();
      std::printf("tocElapsed - clockElapsed = %0.6f  **************** \n",
                  timeDiff -
                      (std::round(b_this.data.re / 1000.0 * 1.0E+6) / 1.0E+6 -
                       startTime));
      std::fflush(stdout);
      timeDiff = coder::toc() - processingStartToc;
      std::printf("TOTAL SEGMENT PROCESSING TIME: %f seconds \n", timeDiff);
      std::fflush(stdout);
      //  packetTimeSec = (packetLength-1)*1/Config.Fs;
      //  segmentTimeSec  = 1/Config.Fs * sampsForKPulses;
      //  sleepTime = segmentTimeSec  - packetTimeSec -  totalLoopTime;
      //  if sleepTime < 0
      //      fprintf('WARNING: CALCULATED SLEEP TIME IS NEGATIVE MEANING THAT I
      //      AM NOT KEEPING UP WITH THE INCOMING DATA RATE \n');
      //  else
      //      % if isdeployed
      //      %     coder.ceval('usleep',uint32(sleepTime * 1e6));
      //      % else
      //      %     pause(sleepTime);
      //      % end
      //  end
    }
  }
}

//
// File trailer for uavrt_detection.cpp
//
// [EOF]
//
