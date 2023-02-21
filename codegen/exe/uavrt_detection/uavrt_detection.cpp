//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: uavrt_detection.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 16:51:51
//

// Include Files
#include "uavrt_detection.h"
#include "AsyncBuffer.h"
#include "AsyncBuffercgHelper.h"
#include "DetectorConfig.h"
#include "all.h"
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
#include "mean.h"
#include "pulsestats.h"
#include "ref.h"
#include "rt_nonfinite.h"
#include "singlecomplex2int.h"
#include "str2double.h"
#include "str2matrix.h"
#include "strcmp.h"
#include "string1.h"
#include "strtok.h"
#include "sum.h"
#include "threshold.h"
#include "tic.h"
#include "toc.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_initialize.h"
#include "uavrt_detection_internal_types.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "udpPulseSenderSend.h"
#include "udpSamplesReceiverRead.h"
#include "validate_print_arguments.h"
#include "validator_check_size.h"
#include "waveform.h"
#include "waveformcopy.h"
#include "wfmstft.h"
#include "wgn.h"
#include "coder_array.h"
#include "omp.h"
#include "stdio.h"
#include "time.h"
#include "udp.h"
#include "unistd.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <stdio.h>
#include <string.h>
#include <string>

// Function Declarations
static void b_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void b_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum);

static void binary_expand_op(coder::array<creal32_T, 1U> &in1,
                             unsigned long long in2,
                             const coder::array<cuint8_T, 1U> &in3,
                             const coder::array<creal32_T, 1U> &in4);

static void d_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void e_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void
interleaveComplexVector(const coder::array<creal32_T, 1U> &complexDataIn,
                        coder::array<float, 1U> &interleaveDataOut);

static void
updatebufferreadvariables(const coder::b_captured_var *Config,
                          const coder::c_captured_var *stftOverlapFraction,
                          coder::c_captured_var *overlapSamples,
                          coder::c_captured_var *sampsForKPulses,
                          const pulsestats *ps_input);

static void updateconfig(coder::b_captured_var *Config,
                         const coder::captured_var *configPath);

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
// Arguments    : coder::array<creal32_T, 1U> &in1
//                unsigned long long in2
//                const coder::array<cuint8_T, 1U> &in3
//                const coder::array<creal32_T, 1U> &in4
// Return Type  : void
//
static void binary_expand_op(coder::array<creal32_T, 1U> &in1,
                             unsigned long long in2,
                             const coder::array<cuint8_T, 1U> &in3,
                             const coder::array<creal32_T, 1U> &in4)
{
  coder::array<creal32_T, 1U> r;
  int i;
  int loop_ub;
  int stride_1_0;
  if (in3.size(0) == 1) {
    i = static_cast<int>(in2);
  } else {
    i = in3.size(0);
  }
  r.set_size(i);
  stride_1_0 = (in3.size(0) != 1);
  if (in3.size(0) == 1) {
    loop_ub = static_cast<int>(in2);
  } else {
    loop_ub = in3.size(0);
  }
  for (i = 0; i < loop_ub; i++) {
    r[i].re = static_cast<signed char>(in3[i * stride_1_0].re);
    r[i].im = static_cast<signed char>(in3[i * stride_1_0].im);
  }
  in1.set_size(r.size(0) + 16383);
  loop_ub = r.size(0);
  for (i = 0; i < loop_ub; i++) {
    in1[i] = r[i];
  }
  for (i = 0; i < 16383; i++) {
    in1[i + r.size(0)] = in4[i];
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
  // Enforce column vector
  varargin_1.set_size(complexDataIn.size(0));
  loop_ub = complexDataIn.size(0);
  for (int i{0}; i < loop_ub; i++) {
    varargin_1[i] = complexDataIn[i].re;
  }
  varargin_2.set_size(complexDataIn.size(0));
  loop_ub = complexDataIn.size(0);
  for (int i{0}; i < loop_ub; i++) {
    varargin_2[i] = complexDataIn[i].im;
  }
  if (varargin_2.size(0) != varargin_1.size(0)) {
    cb_rtErrorWithMessageID(ub_emlrtRTEI.fName, ub_emlrtRTEI.lineNo);
  }
  dataMatrix.set_size(2, varargin_1.size(0));
  loop_ub = varargin_1.size(0);
  for (int i{0}; i < loop_ub; i++) {
    dataMatrix[2 * i] = varargin_1[i];
  }
  loop_ub = varargin_2.size(0);
  for (int i{0}; i < loop_ub; i++) {
    dataMatrix[2 * i + 1] = varargin_2[i];
  }
  interleaveDataOut.set_size(dataMatrix.size(1) << 1);
  loop_ub = dataMatrix.size(1) << 1;
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
// Arguments    : const coder::b_captured_var *Config
//                const coder::c_captured_var *stftOverlapFraction
//                coder::c_captured_var *overlapSamples
//                coder::c_captured_var *sampsForKPulses
//                const pulsestats *ps_input
// Return Type  : void
//
static void
updatebufferreadvariables(const coder::b_captured_var *Config,
                          const coder::c_captured_var *stftOverlapFraction,
                          coder::c_captured_var *overlapSamples,
                          coder::c_captured_var *sampsForKPulses,
                          const pulsestats *ps_input)
{
  b_waveform X0;
  pulsestats lobj_2;
  wfmstft lobj_1;
  coder::array<creal_T, 2U> r;
  coder::array<creal_T, 2U> r1;
  coder::array<creal32_T, 2U> b_val;
  coder::array<creal32_T, 2U> val;
  coder::array<double, 1U> b_tmp_data;
  coder::array<double, 1U> c_tmp_data;
  double tmp_data[400];
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
  val.set(nullptr, 1, 0);
  coder::internal::validator_check_size(val, b_val);
  r.set(nullptr, 0, 0);
  coder::internal::validator_check_size(r, r1);
  b_tmp_data.set(&tmp_data[0], 0);
  coder::internal::validator_check_size(b_tmp_data, c_tmp_data);
  // Flatten input to row
  // Data vector
  // Elements in the data
  X0.Fs = Config->contents.Fs;
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
  lobj_1.init();
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
  n_ol = std::floor(stftOverlapFraction->contents * a__2);
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
  overlapSamples->contents = a__2 * (2.0 * (Config->contents.K * M + J));
  //          if Config.K~=1
  //              sampsForKPulses = n_ws*(Config.K*(N+M)-2*M)+n_ol;
  //          else
  //              sampsForKPulses = n_ws*(N+M+J)+n_ol;
  //          end
  // See 2022-07-11 for updates to samples def
  sampsForKPulses->contents =
      a__2 * ((Config->contents.K * (N + M) + J) + 1.0) + n_ol;
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
  printf("Updating buffer read vars|| N: %u, M: %u, J: %u,\n", u, u1, u2);
  fflush(stdout);
  a__2 = std::round(sampsForKPulses->contents);
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
  a__2 = std::round(overlapSamples->contents);
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
  printf(
      "Updating buffer read vars|| sampForKPulses: %u,  overlapSamples: %u,\n",
      u, u1);
  fflush(stdout);
}

//
// Add code here to update the variables within the function that are
// part of the configuration file. Will first need to load the correct
// file and
//
//
// Arguments    : coder::b_captured_var *Config
//                const coder::captured_var *configPath
// Return Type  : void
//
static void updateconfig(coder::b_captured_var *Config,
                         const coder::captured_var *configPath)
{
  static rtBoundsCheckInfo fb_emlrtBCI{
      -1,                                             // iFirst
      -1,                                             // iLast
      124,                                            // lineNo
      28,                                             // colNo
      "rawLine",                                      // aName
      "DetectorConfig/setFromFile",                   // fName
      "H:\\repos\\uavrt_detection\\DetectorConfig.m", // pName
      0                                               // checkKind
  };
  static rtBoundsCheckInfo gb_emlrtBCI{
      -1,                                             // iFirst
      -1,                                             // iLast
      155,                                            // lineNo
      31,                                             // colNo
      "sepByte",                                      // aName
      "DetectorConfig/setFromFile",                   // fName
      "H:\\repos\\uavrt_detection\\DetectorConfig.m", // pName
      0                                               // checkKind
  };
  static rtBoundsCheckInfo hb_emlrtBCI{
      -1,                                             // iFirst
      -1,                                             // iLast
      159,                                            // lineNo
      28,                                             // colNo
      "lineStr",                                      // aName
      "DetectorConfig/setFromFile",                   // fName
      "H:\\repos\\uavrt_detection\\DetectorConfig.m", // pName
      0                                               // checkKind
  };
  static rtBoundsCheckInfo ib_emlrtBCI{
      -1,                                             // iFirst
      -1,                                             // iLast
      162,                                            // lineNo
      55,                                             // colNo
      "tabLocs",                                      // aName
      "DetectorConfig/setFromFile",                   // fName
      "H:\\repos\\uavrt_detection\\DetectorConfig.m", // pName
      0                                               // checkKind
  };
  static rtBoundsCheckInfo jb_emlrtBCI{
      -1,                                             // iFirst
      -1,                                             // iLast
      163,                                            // lineNo
      63,                                             // colNo
      "colonLocation",                                // aName
      "DetectorConfig/setFromFile",                   // fName
      "H:\\repos\\uavrt_detection\\DetectorConfig.m", // pName
      0                                               // checkKind
  };
  static rtBoundsCheckInfo kb_emlrtBCI{
      -1,                                             // iFirst
      -1,                                             // iLast
      200,                                            // lineNo
      69,                                             // colNo
      "sepByte",                                      // aName
      "DetectorConfig/setFromFile",                   // fName
      "H:\\repos\\uavrt_detection\\DetectorConfig.m", // pName
      0                                               // checkKind
  };
  static rtBoundsCheckInfo lb_emlrtBCI{
      -1,                                             // iFirst
      -1,                                             // iLast
      164,                                            // lineNo
      47,                                             // colNo
      "lineStr",                                      // aName
      "DetectorConfig/setFromFile",                   // fName
      "H:\\repos\\uavrt_detection\\DetectorConfig.m", // pName
      0                                               // checkKind
  };
  static rtBoundsCheckInfo mb_emlrtBCI{
      -1,                                             // iFirst
      -1,                                             // iLast
      164,                                            // lineNo
      74,                                             // colNo
      "lineStr",                                      // aName
      "DetectorConfig/setFromFile",                   // fName
      "H:\\repos\\uavrt_detection\\DetectorConfig.m", // pName
      0                                               // checkKind
  };
  static rtBoundsCheckInfo nb_emlrtBCI{
      -1,                                             // iFirst
      -1,                                             // iLast
      163,                                            // lineNo
      47,                                             // colNo
      "lineStr",                                      // aName
      "DetectorConfig/setFromFile",                   // fName
      "H:\\repos\\uavrt_detection\\DetectorConfig.m", // pName
      0                                               // checkKind
  };
  static rtBoundsCheckInfo ob_emlrtBCI{
      -1,                                             // iFirst
      -1,                                             // iLast
      163,                                            // lineNo
      49,                                             // colNo
      "lineStr",                                      // aName
      "DetectorConfig/setFromFile",                   // fName
      "H:\\repos\\uavrt_detection\\DetectorConfig.m", // pName
      0                                               // checkKind
  };
  static rtBoundsCheckInfo pb_emlrtBCI{
      -1,                                             // iFirst
      -1,                                             // iLast
      202,                                            // lineNo
      69,                                             // colNo
      "sepByte",                                      // aName
      "DetectorConfig/setFromFile",                   // fName
      "H:\\repos\\uavrt_detection\\DetectorConfig.m", // pName
      0                                               // checkKind
  };
  static rtRunTimeErrorInfo tc_emlrtRTEI{
      37,     // lineNo
      "fopen" // fName
  };
  static rtRunTimeErrorInfo uc_emlrtRTEI{
      10,              // lineNo
      "mustBePositive" // fName
  };
  static rtRunTimeErrorInfo vc_emlrtRTEI{
      10,                 // lineNo
      "mustBeNonnegative" // fName
  };
  static rtRunTimeErrorInfo wc_emlrtRTEI{
      18,                    // lineNo
      "binaryRelopValidator" // fName
  };
  static const char b_cv[2]{'I', 'D'};
  FILE *b_NULL;
  FILE *filestar;
  int st;
  coder::rtString _in;
  coder::array<creal_T, 2U> r;
  coder::array<double, 2U> sepByte;
  coder::array<double, 2U> val;
  coder::array<int, 2U> match_out;
  coder::array<int, 2U> matches;
  coder::array<unsigned int, 2U> tabLocs;
  coder::array<char, 2U> c_lineStr;
  coder::array<char, 2U> lineStr;
  coder::array<boolean_T, 2U> b_lineStr;
  double configNum;
  double d;
  int b_st;
  int c_st;
  int fid;
  int i;
  int ii_data;
  int match_idx;
  int text_len;
  boolean_T a;
  boolean_T done;
  Config->contents.init();
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
  if (coder::internal::b_strcmp(configPath->contents)) {
    b_rtErrorWithMessageID(tc_emlrtRTEI.fName, tc_emlrtRTEI.lineNo);
  } else {
    signed char fileid;
    fileid = coder::cfopen(configPath->contents, "rb");
    fid = fileid;
  }
  if (fid == -1) {
    text_len = configPath->contents.size(1);
    lineStr.set_size(1, text_len + 1);
    for (i = 0; i < text_len; i++) {
      lineStr[i] = configPath->contents[i];
    }
    lineStr[text_len] = '\x00';
    printf("UAV-RT: Error opening configurationfile file with error. Attempted "
           "to find config file at the location %s:\n",
           &lineStr[0]);
    fflush(stdout);
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
      rtDynamicBoundsError(1, 1, lineStr.size(1), &fb_emlrtBCI);
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
    b_NULL = NULL;
    coder::getfilestar(static_cast<double>(fid), &filestar, &a);
    if (filestar == b_NULL) {
      c_rtErrorWithMessageID(c_emlrtRTEI.fName, c_emlrtRTEI.lineNo);
    } else {
      st = feof(filestar);
      match_idx = ((int)st != 0);
    }
    done = (match_idx == 1);
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
                         &gb_emlrtBCI);
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
        rtDynamicBoundsError(1, 1, lineStr.size(1), &hb_emlrtBCI);
      }
      if (lineStr[0] != '#') {
        int ii_size[2];
        b_lineStr.set_size(1, lineStr.size(1));
        match_idx = lineStr.size(1);
        for (i = 0; i < match_idx; i++) {
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
          for (i = 0; i < text_len; i++) {
            if (lineStr[i] == '	') {
              matches[match_idx] = i + 1;
              match_idx++;
            }
          }
          match_out.set_size(1, match_idx);
          if (match_idx > 2147483646) {
            coder::check_forloop_overflow_error();
          }
          for (i = 0; i < match_idx; i++) {
            match_out[i] = matches[i];
          }
          tabLocs.set_size(1, match_out.size(1));
          match_idx = match_out.size(1);
          for (i = 0; i < match_idx; i++) {
            tabLocs[i] = static_cast<unsigned int>(match_out[i]);
          }
        }
        // Thanks to
        // https://www.mathworks.com/matlabcentral/answers/529668-how-do-i-detect-a-tab-character-in-a-line-of-text-read-by-fgetl
        if (tabLocs.size(1) < 1) {
          rtDynamicBoundsError(1, 1, tabLocs.size(1), &ib_emlrtBCI);
        }
        // note regexp is not supported for code generation
        if (ii_size[1] < 1) {
          rtDynamicBoundsError(1, 1, ii_size[1], &jb_emlrtBCI);
        }
        if (static_cast<double>(ii_data) - 1.0 < 1.0) {
          match_idx = 0;
        } else {
          if (lineStr.size(1) < 1) {
            rtDynamicBoundsError(1, 1, lineStr.size(1), &nb_emlrtBCI);
          }
          if ((ii_data - 1 < 1) || (ii_data - 1 > lineStr.size(1))) {
            rtDynamicBoundsError(ii_data - 1, 1, lineStr.size(1), &ob_emlrtBCI);
          }
          match_idx = ii_data - 1;
        }
        if (tabLocs[0] + 1U > static_cast<unsigned int>(lineStr.size(1))) {
          i = 0;
          ii_data = 0;
        } else {
          i = static_cast<int>(tabLocs[0] + 1U);
          if ((i < 1) || (i > lineStr.size(1))) {
            rtDynamicBoundsError(i, 1, lineStr.size(1), &lb_emlrtBCI);
          }
          i--;
          if (lineStr.size(1) < 1) {
            rtDynamicBoundsError(lineStr.size(1), 1, lineStr.size(1),
                                 &mb_emlrtBCI);
          }
          ii_data = lineStr.size(1);
        }
        a = false;
        if (match_idx == 2) {
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
          unsigned int in;
          match_idx = ii_data - i;
          c_lineStr.set_size(1, match_idx);
          for (ii_data = 0; ii_data < match_idx; ii_data++) {
            c_lineStr[ii_data] = lineStr[i + ii_data];
          }
          creal_T dc;
          dc = coder::str2double(c_lineStr);
          d = std::round(dc.re);
          if (d < 4.294967296E+9) {
            if (d >= 0.0) {
              in = static_cast<unsigned int>(d);
            } else {
              in = 0U;
            }
          } else if (d >= 4.294967296E+9) {
            in = MAX_uint32_T;
          } else {
            in = 0U;
          }
          Config->contents.ID = in;
          if (in <= 0U) {
            d_rtErrorWithMessageID(uc_emlrtRTEI.fName, uc_emlrtRTEI.lineNo);
          }
        } else {
          c_lineStr.set_size(1, match_idx);
          for (text_len = 0; text_len < match_idx; text_len++) {
            c_lineStr[text_len] = lineStr[text_len];
          }
          if (coder::internal::c_strcmp(c_lineStr)) {
            creal_T dc;
            match_idx = ii_data - i;
            c_lineStr.set_size(1, match_idx);
            for (ii_data = 0; ii_data < match_idx; ii_data++) {
              c_lineStr[ii_data] = lineStr[i + ii_data];
            }
            dc = coder::str2double(c_lineStr);
            if (!(dc.re >= 0.0)) {
              e_rtErrorWithMessageID(vc_emlrtRTEI.fName, vc_emlrtRTEI.lineNo);
            }
            Config->contents.channelCenterFreqMHz = dc.re;
          } else {
            c_lineStr.set_size(1, match_idx);
            for (text_len = 0; text_len < match_idx; text_len++) {
              c_lineStr[text_len] = lineStr[text_len];
            }
            if (!coder::internal::d_strcmp(c_lineStr)) {
              c_lineStr.set_size(1, match_idx);
              for (text_len = 0; text_len < match_idx; text_len++) {
                c_lineStr[text_len] = lineStr[text_len];
              }
              if (coder::internal::e_strcmp(c_lineStr)) {
                unsigned short b_in;
                match_idx = ii_data - i;
                c_lineStr.set_size(1, match_idx);
                for (ii_data = 0; ii_data < match_idx; ii_data++) {
                  c_lineStr[ii_data] = lineStr[i + ii_data];
                }
                creal_T dc;
                dc = coder::str2double(c_lineStr);
                d = std::round(dc.re);
                if (d < 65536.0) {
                  if (d >= 0.0) {
                    b_in = static_cast<unsigned short>(d);
                  } else {
                    b_in = 0U;
                  }
                } else if (d >= 65536.0) {
                  b_in = MAX_uint16_T;
                } else {
                  b_in = 0U;
                }
                Config->contents.portData = b_in;
                if (b_in <= 0) {
                  d_rtErrorWithMessageID(uc_emlrtRTEI.fName,
                                         uc_emlrtRTEI.lineNo);
                }
              } else {
                c_lineStr.set_size(1, match_idx);
                for (text_len = 0; text_len < match_idx; text_len++) {
                  c_lineStr[text_len] = lineStr[text_len];
                }
                if (coder::internal::f_strcmp(c_lineStr)) {
                  creal_T dc;
                  match_idx = ii_data - i;
                  c_lineStr.set_size(1, match_idx);
                  for (ii_data = 0; ii_data < match_idx; ii_data++) {
                    c_lineStr[ii_data] = lineStr[i + ii_data];
                  }
                  dc = coder::str2double(c_lineStr);
                  if (!(dc.re > 0.0)) {
                    d_rtErrorWithMessageID(uc_emlrtRTEI.fName,
                                           uc_emlrtRTEI.lineNo);
                  }
                  Config->contents.Fs = dc.re;
                } else {
                  c_lineStr.set_size(1, match_idx);
                  for (text_len = 0; text_len < match_idx; text_len++) {
                    c_lineStr[text_len] = lineStr[text_len];
                  }
                  if (coder::internal::g_strcmp(c_lineStr)) {
                    match_idx = ii_data - i;
                    c_lineStr.set_size(1, match_idx);
                    for (ii_data = 0; ii_data < match_idx; ii_data++) {
                      c_lineStr[ii_data] = lineStr[i + ii_data];
                    }
                    creal_T dc;
                    dc = coder::str2double(c_lineStr);
                    Config->contents.tagFreqMHz = dc.re;
                  } else {
                    c_lineStr.set_size(1, match_idx);
                    for (text_len = 0; text_len < match_idx; text_len++) {
                      c_lineStr[text_len] = lineStr[text_len];
                    }
                    if (coder::internal::h_strcmp(c_lineStr)) {
                      creal_T dc;
                      match_idx = ii_data - i;
                      c_lineStr.set_size(1, match_idx);
                      for (ii_data = 0; ii_data < match_idx; ii_data++) {
                        c_lineStr[ii_data] = lineStr[i + ii_data];
                      }
                      dc = coder::str2double(c_lineStr);
                      if (!(dc.re > 0.0)) {
                        d_rtErrorWithMessageID(uc_emlrtRTEI.fName,
                                               uc_emlrtRTEI.lineNo);
                      }
                      Config->contents.tp = dc.re;
                    } else {
                      c_lineStr.set_size(1, match_idx);
                      for (text_len = 0; text_len < match_idx; text_len++) {
                        c_lineStr[text_len] = lineStr[text_len];
                      }
                      if (coder::internal::i_strcmp(c_lineStr)) {
                        creal_T dc;
                        match_idx = ii_data - i;
                        c_lineStr.set_size(1, match_idx);
                        for (ii_data = 0; ii_data < match_idx; ii_data++) {
                          c_lineStr[ii_data] = lineStr[i + ii_data];
                        }
                        dc = coder::str2double(c_lineStr);
                        if (!(dc.re > 0.0)) {
                          d_rtErrorWithMessageID(uc_emlrtRTEI.fName,
                                                 uc_emlrtRTEI.lineNo);
                        }
                        Config->contents.tip = dc.re;
                      } else {
                        c_lineStr.set_size(1, match_idx);
                        for (text_len = 0; text_len < match_idx; text_len++) {
                          c_lineStr[text_len] = lineStr[text_len];
                        }
                        if (coder::internal::j_strcmp(c_lineStr)) {
                          creal_T dc;
                          match_idx = ii_data - i;
                          c_lineStr.set_size(1, match_idx);
                          for (ii_data = 0; ii_data < match_idx; ii_data++) {
                            c_lineStr[ii_data] = lineStr[i + ii_data];
                          }
                          dc = coder::str2double(c_lineStr);
                          if (!(dc.re >= 0.0)) {
                            e_rtErrorWithMessageID(vc_emlrtRTEI.fName,
                                                   vc_emlrtRTEI.lineNo);
                          }
                          Config->contents.tipu = dc.re;
                        } else {
                          c_lineStr.set_size(1, match_idx);
                          for (text_len = 0; text_len < match_idx; text_len++) {
                            c_lineStr[text_len] = lineStr[text_len];
                          }
                          if (coder::internal::k_strcmp(c_lineStr)) {
                            creal_T dc;
                            match_idx = ii_data - i;
                            c_lineStr.set_size(1, match_idx);
                            for (ii_data = 0; ii_data < match_idx; ii_data++) {
                              c_lineStr[ii_data] = lineStr[i + ii_data];
                            }
                            dc = coder::str2double(c_lineStr);
                            if (!(dc.re >= 0.0)) {
                              e_rtErrorWithMessageID(vc_emlrtRTEI.fName,
                                                     vc_emlrtRTEI.lineNo);
                            }
                            Config->contents.tipj = dc.re;
                          } else {
                            a = false;
                            if ((match_idx == 1) && (lineStr[0] == 'K')) {
                              a = true;
                            }
                            if (a) {
                              unsigned char c_in;
                              match_idx = ii_data - i;
                              c_lineStr.set_size(1, match_idx);
                              for (ii_data = 0; ii_data < match_idx;
                                   ii_data++) {
                                c_lineStr[ii_data] = lineStr[i + ii_data];
                              }
                              creal_T dc;
                              dc = coder::str2double(c_lineStr);
                              d = std::round(dc.re);
                              if (d < 256.0) {
                                if (d >= 0.0) {
                                  c_in = static_cast<unsigned char>(d);
                                } else {
                                  c_in = 0U;
                                }
                              } else if (d >= 256.0) {
                                c_in = MAX_uint8_T;
                              } else {
                                c_in = 0U;
                              }
                              Config->contents.K = c_in;
                              if (c_in <= 0) {
                                d_rtErrorWithMessageID(uc_emlrtRTEI.fName,
                                                       uc_emlrtRTEI.lineNo);
                              }
                            } else {
                              c_lineStr.set_size(1, match_idx);
                              for (text_len = 0; text_len < match_idx;
                                   text_len++) {
                                c_lineStr[text_len] = lineStr[text_len];
                              }
                              if (coder::internal::l_strcmp(c_lineStr)) {
                                match_idx = ii_data - i;
                                _in.Value.set_size(1, match_idx);
                                for (ii_data = 0; ii_data < match_idx;
                                     ii_data++) {
                                  _in.Value[ii_data] = lineStr[i + ii_data];
                                }
                                Config->contents.opMode = _in;
                              } else {
                                c_lineStr.set_size(1, match_idx);
                                for (text_len = 0; text_len < match_idx;
                                     text_len++) {
                                  c_lineStr[text_len] = lineStr[text_len];
                                }
                                if (coder::internal::m_strcmp(c_lineStr)) {
                                  match_idx = ii_data - i;
                                  c_lineStr.set_size(1, match_idx);
                                  for (ii_data = 0; ii_data < match_idx;
                                       ii_data++) {
                                    c_lineStr[ii_data] = lineStr[i + ii_data];
                                  }
                                  str2matrix(c_lineStr, r);
                                  val.set_size(r.size(0), r.size(1));
                                  match_idx = r.size(0) * r.size(1);
                                  for (i = 0; i < match_idx; i++) {
                                    val[i] = r[i].re;
                                  }
                                  coder::internal::validator_check_size(
                                      val, Config->contents.excldFreqs);
                                } else {
                                  c_lineStr.set_size(1, match_idx);
                                  for (text_len = 0; text_len < match_idx;
                                       text_len++) {
                                    c_lineStr[text_len] = lineStr[text_len];
                                  }
                                  if (coder::internal::n_strcmp(c_lineStr)) {
                                    creal_T dc;
                                    match_idx = ii_data - i;
                                    c_lineStr.set_size(1, match_idx);
                                    for (ii_data = 0; ii_data < match_idx;
                                         ii_data++) {
                                      c_lineStr[ii_data] = lineStr[i + ii_data];
                                    }
                                    dc = coder::str2double(c_lineStr);
                                    if (!(dc.re > 0.0)) {
                                      d_rtErrorWithMessageID(
                                          uc_emlrtRTEI.fName,
                                          uc_emlrtRTEI.lineNo);
                                    }
                                    if (!(dc.re < 1.0)) {
                                      b_rtErrorWithMessageID(
                                          "  1.000000000000000e+00",
                                          wc_emlrtRTEI.fName,
                                          wc_emlrtRTEI.lineNo);
                                    }
                                    Config->contents.falseAlarmProb = dc.re;
                                  } else {
                                    c_lineStr.set_size(1, match_idx);
                                    for (text_len = 0; text_len < match_idx;
                                         text_len++) {
                                      c_lineStr[text_len] = lineStr[text_len];
                                    }
                                    if (coder::internal::o_strcmp(c_lineStr)) {
                                      match_idx = ii_data - i;
                                      _in.Value.set_size(1, match_idx);
                                      for (ii_data = 0; ii_data < match_idx;
                                           ii_data++) {
                                        _in.Value[ii_data] =
                                            lineStr[i + ii_data];
                                      }
                                      Config->contents.dataRecordPath = _in;
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
        // Stop when we have finished reading this entry.
        b_NULL = NULL;
        coder::getfilestar(static_cast<double>(fid), &filestar, &a);
        if (filestar == b_NULL) {
          c_rtErrorWithMessageID(c_emlrtRTEI.fName, c_emlrtRTEI.lineNo);
        } else {
          st = feof(filestar);
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
                sepByte.size(1), &kb_emlrtBCI);
          }
          if (coder::b_ftell(static_cast<double>(fid)) ==
              sepByte[static_cast<int>(static_cast<unsigned int>(configNum))]) {
            done = true;
          }
        }
      } else {
        b_NULL = NULL;
        coder::getfilestar(static_cast<double>(fid), &filestar, &a);
        if (filestar == b_NULL) {
          c_rtErrorWithMessageID(c_emlrtRTEI.fName, c_emlrtRTEI.lineNo);
        } else {
          st = feof(filestar);
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
                sepByte.size(1), &pb_emlrtBCI);
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
  coder::cfclose(static_cast<double>(fid));
  // Do we update the tip and tipu or use the ones that were adapted from
  // the previous detections? Probably just use the file. The supervisor
  // will have access to the detected pulses and can update these values if
  // it sees fit.
}

//
// UNTITLED Summary of this function goes here
//    Detailed explanation goes here
//
// Arguments    : const coder::array<char, 2U> &configPath
// Return Type  : void
//
void uavrt_detection(const coder::array<char, 2U> &configPath)
{
  static coder::dsp::AsyncBuffer asyncDataBuff;
  static coder::dsp::b_AsyncBuffer asyncTimeBuff;
  static coder::dsp::c_AsyncBuffer asyncWriteBuff;
  static rtBoundsCheckInfo fb_emlrtBCI{
      -1,                                              // iFirst
      -1,                                              // iLast
      308,                                             // lineNo
      44,                                              // colNo
      "timeVector",                                    // aName
      "uavrt_detection",                               // fName
      "H:\\repos\\uavrt_detection\\uavrt_detection.m", // pName
      0                                                // checkKind
  };
  static rtBoundsCheckInfo gb_emlrtBCI{
      -1,                                              // iFirst
      -1,                                              // iLast
      373,                                             // lineNo
      32,                                              // colNo
      "t",                                             // aName
      "uavrt_detection",                               // fName
      "H:\\repos\\uavrt_detection\\uavrt_detection.m", // pName
      0                                                // checkKind
  };
  static rtBoundsCheckInfo hb_emlrtBCI{
      -1,                                              // iFirst
      -1,                                              // iLast
      535,                                             // lineNo
      61,                                              // colNo
      "X.ps_pos.pl",                                   // aName
      "uavrt_detection",                               // fName
      "H:\\repos\\uavrt_detection\\uavrt_detection.m", // pName
      0                                                // checkKind
  };
  static rtBoundsCheckInfo ib_emlrtBCI{
      -1,                                              // iFirst
      -1,                                              // iLast
      540,                                             // lineNo
      79,                                              // colNo
      "ps_pre_struc.pl",                               // aName
      "uavrt_detection",                               // fName
      "H:\\repos\\uavrt_detection\\uavrt_detection.m", // pName
      0                                                // checkKind
  };
  static rtBoundsCheckInfo jb_emlrtBCI{
      -1,                                              // iFirst
      -1,                                              // iLast
      546,                                             // lineNo
      50,                                              // colNo
      "pulsesToSkip",                                  // aName
      "uavrt_detection",                               // fName
      "H:\\repos\\uavrt_detection\\uavrt_detection.m", // pName
      0                                                // checkKind
  };
  static rtBoundsCheckInfo kb_emlrtBCI{
      -1,                                              // iFirst
      -1,                                              // iLast
      608,                                             // lineNo
      91,                                              // colNo
      "X.ps_pos.pl",                                   // aName
      "uavrt_detection",                               // fName
      "H:\\repos\\uavrt_detection\\uavrt_detection.m", // pName
      0                                                // checkKind
  };
  static rtBoundsCheckInfo lb_emlrtBCI{
      -1,                                              // iFirst
      -1,                                              // iLast
      628,                                             // lineNo
      50,                                              // colNo
      "pulsesToSkip",                                  // aName
      "uavrt_detection",                               // fName
      "H:\\repos\\uavrt_detection\\uavrt_detection.m", // pName
      0                                                // checkKind
  };
  static rtDoubleCheckInfo t_emlrtDCI{
      282,                                             // lineNo
      46,                                              // colNo
      "uavrt_detection",                               // fName
      "H:\\repos\\uavrt_detection\\uavrt_detection.m", // pName
      4                                                // checkKind
  };
  static rtDoubleCheckInfo u_emlrtDCI{
      282,                                             // lineNo
      46,                                              // colNo
      "uavrt_detection",                               // fName
      "H:\\repos\\uavrt_detection\\uavrt_detection.m", // pName
      1                                                // checkKind
  };
  static rtDoubleCheckInfo v_emlrtDCI{
      283,                                             // lineNo
      53,                                              // colNo
      "uavrt_detection",                               // fName
      "H:\\repos\\uavrt_detection\\uavrt_detection.m", // pName
      4                                                // checkKind
  };
  static rtDoubleCheckInfo w_emlrtDCI{
      283,                                             // lineNo
      53,                                              // colNo
      "uavrt_detection",                               // fName
      "H:\\repos\\uavrt_detection\\uavrt_detection.m", // pName
      1                                                // checkKind
  };
  static rtEqualityCheckInfo g_emlrtECI{
      1,                                              // nDims
      282,                                            // lineNo
      33,                                             // colNo
      "uavrt_detection",                              // fName
      "H:\\repos\\uavrt_detection\\uavrt_detection.m" // pName
  };
  static const char b_cv[31]{'c', 'u', 'r', 'r', 'e', 'n', 't', '_',
                             'w', 'o', 'r', 'k', 'i', 'n', 'g', '_',
                             'd', 'i', 'r', 'e', 'c', 't', 'o', 'r',
                             'y', '_', 'e', 'r', 'r', 'o', 'r'};
  char *nullVal;
  char *retVal;
  b_waveform X;
  coder::b_captured_var Config;
  coder::c_captured_var overlapSamples;
  coder::c_captured_var sampsForKPulses;
  coder::c_captured_var stftOverlapFraction;
  coder::captured_var b_configPath;
  coder::datetime b_this;
  pulsestats lobj_11[4];
  pulsestats lobj_20[2];
  pulsestats lobj_14;
  pulsestats lobj_16;
  pulsestats lobj_17;
  pulsestats *pulseStatsPriori;
  threshold val;
  waveform b_X;
  waveform lobj_12;
  waveform lobj_19;
  waveform *Xhold;
  wfmstft lobj_18[3];
  wfmstft lobj_10;
  wfmstft lobj_13;
  wfmstft lobj_15;
  coder::array<c_struct_T, 2U> ps_pre_struc_clst;
  coder::array<c_struct_T, 2U> ps_pre_struc_pl;
  coder::array<c_struct_T, 1U> c_X;
  coder::array<creal32_T, 1U> b_asyncDataBuff;
  coder::array<creal32_T, 1U> dataReceived;
  coder::array<creal32_T, 1U> dataWriterBuffData;
  coder::array<creal32_T, 1U> iqDataToWrite;
  coder::array<creal32_T, 1U> x;
  coder::array<cuint8_T, 1U> r;
  coder::array<double, 2U> b_x;
  coder::array<double, 2U> c_varargin_1;
  coder::array<double, 2U> ps_pre_struc_cpki;
  coder::array<double, 1U> r2;
  coder::array<double, 1U> t;
  coder::array<double, 1U> timeVector;
  coder::array<float, 1U> r1;
  coder::array<char, 2U> varargin_1;
  coder::array<boolean_T, 2U> b_pulsesToSkip;
  coder::array<boolean_T, 2U> ps_pre_struc_cmsk;
  coder::array<boolean_T, 2U> pulsesToSkip;
  coder::array<boolean_T, 2U> r4;
  coder::array<boolean_T, 2U> r5;
  coder::array<boolean_T, 1U> b_tmp_data;
  coder::array<boolean_T, 1U> r3;
  c_struct_T b_expl_temp;
  c_struct_T detectorPulse;
  c_struct_T expl_temp;
  creal_T dcv[1000];
  creal32_T exampleData[1000];
  double ps_pre_struc_tmplt[2];
  double dataWriterSamples;
  double framesReceived;
  double integratedTimeError;
  double lastTimeStamp;
  double previousPulseTime;
  double ps_pre_struc_fend;
  double pulseCount;
  double segmentsProcessed;
  double startTime;
  double t9_P;
  double t9_fend;
  double t9_fp;
  double t9_fstart;
  double t9_t_0;
  double t9_t_f;
  double t9_yw;
  double trackedCount;
  unsigned long long nextSampleCount;
  unsigned long long sampleOffset;
  int currDir_size[2];
  int i;
  int loop_ub;
  int n;
  int udpPulseSender;
  int udpReceiver;
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
  // Needed for usleep function in generated code
  Config.contents.init();
  // Build empty config object
  updateconfig(&Config, &b_configPath);
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
  nullVal = NULL;
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
  printf("Curr Directory is: %s\n", &varargin_1[0]);
  fflush(stdout);
  printf("ROS2 disabled");
  fflush(stdout);
  makepulsestruc(&detectorPulse.A, &detectorPulse.P, &detectorPulse.SNR,
                 &detectorPulse.yw, &detectorPulse.t_0, &detectorPulse.t_f,
                 detectorPulse.t_next, &detectorPulse.fp, &detectorPulse.fstart,
                 &detectorPulse.fend, detectorPulse.mode,
                 &detectorPulse.det_dec, &detectorPulse.con_dec);
  makepulsestruc(&integratedTimeError, &t9_P, &pulseCount, &t9_yw, &t9_t_0,
                 &t9_t_f, expl_temp.t_next, &t9_fp, &t9_fstart, &t9_fend,
                 expl_temp.mode, &t9_det_dec, &t9_con_dec);
  expl_temp.con_dec = t9_con_dec;
  expl_temp.det_dec = t9_det_dec;
  expl_temp.fend = t9_fend;
  expl_temp.fstart = t9_fstart;
  expl_temp.fp = t9_fp;
  expl_temp.t_f = t9_t_f;
  expl_temp.t_0 = t9_t_0;
  expl_temp.yw = t9_yw;
  expl_temp.SNR = pulseCount;
  expl_temp.P = t9_P;
  expl_temp.A = integratedTimeError;
  pulseStatsPriori = lobj_20[1].init(Config.contents.tp, Config.contents.tip,
                                     Config.contents.tipu, Config.contents.tipj,
                                     &detectorPulse, &expl_temp);
  //  % tp, tip, tipu
  //  % tipj, fp, fstart, fend, tmplt, mode
  //   % pl ,clst
  //  cmsk ,cpki)
  stftOverlapFraction.contents = 0.5;
  // Initialize and then set these variable needed for buffer reads
  overlapSamples.contents = 0.0;
  sampsForKPulses.contents = 0.0;
  updatebufferreadvariables(&Config, &stftOverlapFraction, &overlapSamples,
                            &sampsForKPulses, pulseStatsPriori);
  // coder.varsize("dataReceived",[1025 1]);
  // 1024 plus a time stamp.
  printf("Startup set 1 complete. \n");
  fflush(stdout);
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
  printf("Startup set 2 complete. \n");
  fflush(stdout);
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
  fileid = coder::cfopen(Config.contents.dataRecordPath.Value, "wb");
  // dataWriterFileID    = fopen('output/data.bin','w');
  if (fileid == -1) {
    printf("UAV-RT: Error opening/creating data record file with error:\n");
    fflush(stdout);
  }
  printf("Startup set 3 complete. \n");
  fflush(stdout);
  // pulseWriterFileID    =
  // fopen(cat(2,char(Config.processedOuputPath),'PULSE_LOG.txt'),'w');
  // pulseWriterFileID    = fopen('pulse_log','w');
  //  pulseWriterFileID    = fopen('/config/data2.bin','w');
  //  if dataWriterFileID == -1
  //      fprintf("UAV-RT: Error opening/creating pulse record file with
  //      error:\n")
  //  end
  //
  printf("Startup set 4 complete. \n");
  fflush(stdout);
  // Define a pulsestats structure that isn't an object.
  // This is needed for the loop, as Matlab coder has problems seeing
  // that the pulsestats handle object is set for all execution paths.
  // Holding all these properties in a structure rather than the
  // pulsestats object addressed this problem.
  // Needed to let coder know that some of these will be varying in size
  // https://www.mathworks.com/help/simulink/ug/how-working-with-matlab-classes-is-different-for-code-generation.html
  mode = 'D';
  // dims 0 if fixed, 1 if variable
  printf("Startup set 5 complete. \n");
  fflush(stdout);
  t9_yw = 0.0;
  t9_t_0 = 0.0;
  t9_t_f = 0.0;
  t9_fp = 0.0;
  t9_fstart = 0.0;
  t9_fend = 0.0;
  ps_pre_struc_fend = 0.0;
  ps_pre_struc_tmplt[0] = 1.0;
  ps_pre_struc_tmplt[1] = 1.0;
  makepulsestruc(&detectorPulse.A, &detectorPulse.P, &detectorPulse.SNR,
                 &detectorPulse.yw, &detectorPulse.t_0, &detectorPulse.t_f,
                 detectorPulse.t_next, &detectorPulse.fp, &detectorPulse.fstart,
                 &detectorPulse.fend, detectorPulse.mode,
                 &detectorPulse.det_dec, &detectorPulse.con_dec);
  ps_pre_struc_pl.set_size(1, 1);
  ps_pre_struc_pl[0] = detectorPulse;
  makepulsestruc(&detectorPulse.A, &detectorPulse.P, &detectorPulse.SNR,
                 &detectorPulse.yw, &detectorPulse.t_0, &detectorPulse.t_f,
                 detectorPulse.t_next, &detectorPulse.fp, &detectorPulse.fstart,
                 &detectorPulse.fend, detectorPulse.mode,
                 &detectorPulse.det_dec, &detectorPulse.con_dec);
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
  udpPulseSender = udpSenderSetup(50000.0);
  if (udpPulseSender <= 0) {
    rtErrorWithMessageID(b_emlrtRTEI.fName, b_emlrtRTEI.lineNo);
  }
  //  Two floats = 2 * 4 bytes;
  udpReceiver = udpReceiverSetup(Config.contents.portData);
  if (udpReceiver <= 0) {
    rtErrorWithMessageID(b_emlrtRTEI.fName, b_emlrtRTEI.lineNo);
  }
  printf("Startup set 6 complete. \n");
  fflush(stdout);
  //  Preallocate X and Xhold so that coder knows the data types.
  coder::wgn(dcv);
  for (i = 0; i < 1000; i++) {
    exampleData[i].re = static_cast<float>(dcv[i].re);
    exampleData[i].im = static_cast<float>(dcv[i].im);
  }
  // UNTITLED2 Construct an instance of this class
  //    Detailed explanation goes here
  val.pf = Config.contents.falseAlarmProb;
  val.evMuParam = 0.0;
  val.evSigmaParam = 0.0;
  val.threshVecFine.set_size(1);
  val.threshVecFine[0] = 0.0;
  Xhold = lobj_19.init(exampleData, Config.contents.Fs, pulseStatsPriori, &val);
  // UNTITLED2 Construct an instance of this class
  //    Detailed explanation goes here
  X.init(exampleData, Config.contents.Fs, pulseStatsPriori, &lobj_20[0],
         &lobj_18[2]);
  Xhold->spectro(&lobj_18[1]);
  X.spectro(&lobj_18[0]);
  printf("Startup set 7 complete. \n");
  fflush(stdout);
  // Initialize loop variables
  resetBuffersFlag = true;
  framesReceived = 0.0;
  segmentsProcessed = 0.0;
  suggestedMode = 'S';
  fLock = false;
  staleDataFlag = true;
  // Force buffer  flush on start
  lastTimeStamp = 0.0;
  cleanBuffer = true;
  trackedCount = 0.0;
  b_this.init();
  startTime = std::round(b_this.data.re / 1000.0 * 1.0E+6) / 1.0E+6;
  // sysClockElapsedTime = 0;
  nextSampleCount = 0ULL;
  sampleOffset = 0ULL;
  previousPulseTime = 0.0;
  printf("Startup set 8 complete. Starting processing... \n");
  fflush(stdout);
  while (1) {
    unsigned long long q0;
    unsigned long long qY;
    // i <= maxInd
    if (resetBuffersFlag) {
      asyncDataBuff.reset();
      asyncTimeBuff.reset();
      resetBuffersFlag = false;
      cleanBuffer = true;
    }
    //             %% Get data
    udpSamplesReceiverRead(udpReceiver, dataReceived);
    //             %% Flush UDP buffer if data in the buffer is stale.
    if (staleDataFlag) {
      printf("********STALE DATA FLAG: %u *********\n", 1U);
      fflush(stdout);
      printf("********CLEARING UDP DATA BUFFER*********\n");
      fflush(stdout);
      udpReceiverClear(udpReceiver);
      staleDataFlag = false;
      printf("********RESETTING TIMES*********\n");
      fflush(stdout);
      // startTime = round(posixtime(datetime('now'))*1000000)/1000000;
      framesReceived = 0.0;
      nextSampleCount = 0ULL;
      coder::tic();
    }
    //             %% Wait for new data if none ready, else put data in buffers
    // timeStamp      = 10^-3*singlecomplex2int(dataReceived(1)); % OLD TIME
    // STAMP METHOD iqData         = dataReceived(2:end);% OLD TIME STAMP METHOD
    // timeVector     = timeStamp+1/Config.Fs*(0:(numel(iqData)-1)).';% OLD TIME
    // STAMP METHOD
    //  Parse the incoming data and sample count.
    //  and fill in any missing data with zeros.
    framesReceived++;
    currDir_size[0] = 1;
    currDir_size[1] = 16383;
    coder::internal::indexShapeCheck(16384, currDir_size);
    // This is the number of samples transmitted by the
    // upstream process (ideal if none are dropped)
    integratedTimeError = singlecomplex2int(dataReceived[16383]);
    integratedTimeError = std::round(integratedTimeError);
    if (integratedTimeError < 1.8446744073709552E+19) {
      if (integratedTimeError >= 0.0) {
        q0 = static_cast<unsigned long long>(integratedTimeError);
      } else {
        q0 = 0ULL;
      }
    } else if (integratedTimeError >= 1.8446744073709552E+19) {
      q0 = MAX_uint64_T;
    } else {
      q0 = 0ULL;
    }
    // If this is the first packet, calculate the offset
    // sample count since the upstream processess may have
    // started a while ago and its sample count may not be zero
    if (framesReceived == 1.0) {
      b_this.init();
      startTime = std::round(b_this.data.re / 1000.0 * 1.0E+6) / 1.0E+6;
      sampleOffset = q0 - 16383ULL;
      if (q0 - 16383ULL > q0) {
        sampleOffset = 0ULL;
      }
      // To estimate the timestamp of the sample before the
      // first one in this first frame we go back in time
      // from the start time.
      lastTimeStamp = startTime - 16384.0 / Config.contents.Fs;
    }
    qY = q0 - sampleOffset;
    if (qY > q0) {
      qY = 0ULL;
    }
    q0 = nextSampleCount + 16383ULL;
    if (nextSampleCount + 16383ULL < nextSampleCount) {
      q0 = MAX_uint64_T;
    }
    q0 = qY - q0;
    if (q0 > qY) {
      q0 = 0ULL;
    }
    if (q0 > 0ULL) {
      if (!(q0 >= 0.0)) {
        rtNonNegativeError(static_cast<double>(q0), &t_emlrtDCI);
      }
      integratedTimeError = static_cast<int>(std::floor(static_cast<double>(
          static_cast<unsigned long long>(static_cast<double>(q0)))));
      if (static_cast<unsigned long long>(static_cast<double>(q0)) !=
          integratedTimeError) {
        rtIntegerError(static_cast<double>(static_cast<unsigned long long>(
                           static_cast<double>(q0))),
                       &u_emlrtDCI);
      }
      if (!(q0 >= 0.0)) {
        rtNonNegativeError(static_cast<double>(q0), &v_emlrtDCI);
      }
      if (static_cast<unsigned long long>(static_cast<double>(q0)) !=
          integratedTimeError) {
        rtIntegerError(static_cast<double>(static_cast<unsigned long long>(
                           static_cast<double>(q0))),
                       &w_emlrtDCI);
      }
      r.set_size(static_cast<int>(q0));
      loop_ub = static_cast<int>(q0);
      for (i = 0; i < loop_ub; i++) {
        r[i].re = 0U;
        r[i].im = 0U;
      }
      if ((static_cast<int>(q0) != r.size(0)) &&
          ((static_cast<int>(q0) != 1) && (r.size(0) != 1))) {
        emlrtDimSizeImpxCheckR2021b(static_cast<int>(q0), r.size(0),
                                    &g_emlrtECI);
      }
      if (static_cast<int>(q0) == r.size(0)) {
        iqDataToWrite.set_size(static_cast<int>(q0) + 16383);
        loop_ub = static_cast<int>(q0);
        for (i = 0; i < loop_ub; i++) {
          iqDataToWrite[i].re = 0.0F;
          iqDataToWrite[i].im = static_cast<signed char>(r[i].im);
        }
        for (i = 0; i < 16383; i++) {
          iqDataToWrite[i + static_cast<int>(q0)] = dataReceived[i];
        }
      } else {
        binary_expand_op(iqDataToWrite, q0, r, dataReceived);
      }
      qY = nextSampleCount + 16383ULL;
      if (nextSampleCount + 16383ULL < nextSampleCount) {
        qY = MAX_uint64_T;
      }
      nextSampleCount = qY + q0;
      if (nextSampleCount < qY) {
        nextSampleCount = MAX_uint64_T;
      }
      printf("Missing samples detected. Filling with zeros for %llu samples.",
             q0);
      fflush(stdout);
    } else {
      iqDataToWrite.set_size(16383);
      for (i = 0; i < 16383; i++) {
        iqDataToWrite[i] = dataReceived[i];
      }
      qY = nextSampleCount + 16383ULL;
      if (nextSampleCount + 16383ULL < nextSampleCount) {
        qY = MAX_uint64_T;
      }
      nextSampleCount = qY;
    }
    // fprintf('nReceived: %u \t currSampleCount: %u \t idealSampleCount: %u \t
    // rawIdealSampleCount: %u \t missingSamples: %u numel(iqData): %u
    // numel(iqDataToWrite): %u nextSampleCount: %u \t\n',nReceived,
    // currSampleCount, idealSampleCount, rawIdealSampleCount, missingSamples,
    // uint64(numel(iqData)), uint64(numel(iqDataToWrite)), nextSampleCount)
    timeVector.set_size(iqDataToWrite.size(0));
    loop_ub = iqDataToWrite.size(0) - 1;
    for (i = 0; i <= loop_ub; i++) {
      timeVector[i] =
          lastTimeStamp + (static_cast<double>(i) + 1.0) / Config.contents.Fs;
    }
    // fprintf('Sample elapsed seconds: %f \t Posix elapsed seconds:  \n',
    // timeVector(end), round(posixtime(datetime('now'))*1000000)/1000000 -
    // startTime)
    if (timeVector.size(0) < 1) {
      rtDynamicBoundsError(timeVector.size(0), 1, timeVector.size(0),
                           &fb_emlrtBCI);
    }
    lastTimeStamp = timeVector[timeVector.size(0) - 1];
    // Write out data and time.
    asyncDataBuff.write(iqDataToWrite);
    asyncTimeBuff.write(timeVector);
    asyncWriteBuff.write(dataReceived);
    //  OLD TIME STAMP METHOD
    // asyncWriteBuff.write([dataReceived;
    // int2singlecomplex(timeAtPacketReceive*10^3)]);
    if ((asyncWriteBuff.pBuffer.WritePointer >= 0) &&
        (asyncWriteBuff.pBuffer.ReadPointer <
         asyncWriteBuff.pBuffer.WritePointer - MAX_int32_T)) {
      loop_ub = MAX_int32_T;
    } else if ((asyncWriteBuff.pBuffer.WritePointer < 0) &&
               (asyncWriteBuff.pBuffer.ReadPointer >
                asyncWriteBuff.pBuffer.WritePointer - MIN_int32_T)) {
      loop_ub = MIN_int32_T;
    } else {
      loop_ub = asyncWriteBuff.pBuffer.WritePointer -
                asyncWriteBuff.pBuffer.ReadPointer;
    }
    if (loop_ub < -2147483647) {
      loop_ub = MIN_int32_T;
    } else {
      loop_ub--;
    }
    if (asyncWriteBuff.pBuffer.ReadPointer < -2146882997) {
      n = MAX_int32_T;
    } else {
      n = 600650 - asyncWriteBuff.pBuffer.ReadPointer;
    }
    if ((n < 0) && (asyncWriteBuff.pBuffer.WritePointer < MIN_int32_T - n)) {
      n = MIN_int32_T;
    } else if ((n > 0) &&
               (asyncWriteBuff.pBuffer.WritePointer > MAX_int32_T - n)) {
      n = MAX_int32_T;
    } else {
      n += asyncWriteBuff.pBuffer.WritePointer;
    }
    if (asyncWriteBuff.pBuffer.ReadPointer <
        asyncWriteBuff.pBuffer.WritePointer) {
      n = loop_ub;
    } else if (asyncWriteBuff.pBuffer.ReadPointer ==
               asyncWriteBuff.pBuffer.WritePointer) {
      n = 600650;
    }
    if (n == dataWriterSamples) {
      asyncWriteBuff.read(dataWriterBuffData);
      if (fileid != -1) {
        interleaveComplexVector(dataWriterBuffData, r1);
        coder::b_fwrite(static_cast<double>(fileid), r1);
      }
    }
    // end
    if ((asyncDataBuff.pBuffer.WritePointer >= 0) &&
        (asyncDataBuff.pBuffer.ReadPointer <
         asyncDataBuff.pBuffer.WritePointer - MAX_int32_T)) {
      loop_ub = MAX_int32_T;
    } else if ((asyncDataBuff.pBuffer.WritePointer < 0) &&
               (asyncDataBuff.pBuffer.ReadPointer >
                asyncDataBuff.pBuffer.WritePointer - MIN_int32_T)) {
      loop_ub = MIN_int32_T;
    } else {
      loop_ub = asyncDataBuff.pBuffer.WritePointer -
                asyncDataBuff.pBuffer.ReadPointer;
    }
    if (loop_ub < -2147483647) {
      loop_ub = MIN_int32_T;
    } else {
      loop_ub--;
    }
    if (asyncDataBuff.pBuffer.ReadPointer < -2141683327) {
      n = MAX_int32_T;
    } else {
      n = 5800320 - asyncDataBuff.pBuffer.ReadPointer;
    }
    if ((n < 0) && (asyncDataBuff.pBuffer.WritePointer < MIN_int32_T - n)) {
      n = MIN_int32_T;
    } else if ((n > 0) &&
               (asyncDataBuff.pBuffer.WritePointer > MAX_int32_T - n)) {
      n = MAX_int32_T;
    } else {
      n += asyncDataBuff.pBuffer.WritePointer;
    }
    integratedTimeError = sampsForKPulses.contents + overlapSamples.contents;
    if (asyncDataBuff.pBuffer.ReadPointer <
        asyncDataBuff.pBuffer.WritePointer) {
      n = loop_ub;
    } else if (asyncDataBuff.pBuffer.ReadPointer ==
               asyncDataBuff.pBuffer.WritePointer) {
      n = 5800320;
    }
    if (n >= 3.0 * integratedTimeError) {
      printf("Buffer anomaly detected. Printing buffer from back to front:\n");
      fflush(stdout);
      if ((asyncDataBuff.pBuffer.WritePointer >= 0) &&
          (asyncDataBuff.pBuffer.ReadPointer <
           asyncDataBuff.pBuffer.WritePointer - MAX_int32_T)) {
        loop_ub = MAX_int32_T;
      } else if ((asyncDataBuff.pBuffer.WritePointer < 0) &&
                 (asyncDataBuff.pBuffer.ReadPointer >
                  asyncDataBuff.pBuffer.WritePointer - MIN_int32_T)) {
        loop_ub = MIN_int32_T;
      } else {
        loop_ub = asyncDataBuff.pBuffer.WritePointer -
                  asyncDataBuff.pBuffer.ReadPointer;
      }
      if (loop_ub < -2147483647) {
        loop_ub = MIN_int32_T;
      } else {
        loop_ub--;
      }
      if (asyncDataBuff.pBuffer.ReadPointer < -2141683327) {
        n = MAX_int32_T;
      } else {
        n = 5800320 - asyncDataBuff.pBuffer.ReadPointer;
      }
      if ((n < 0) && (asyncDataBuff.pBuffer.WritePointer < MIN_int32_T - n)) {
        n = MIN_int32_T;
      } else if ((n > 0) &&
                 (asyncDataBuff.pBuffer.WritePointer > MAX_int32_T - n)) {
        n = MAX_int32_T;
      } else {
        n += asyncDataBuff.pBuffer.WritePointer;
      }
      if (asyncDataBuff.pBuffer.ReadPointer >=
          asyncDataBuff.pBuffer.WritePointer) {
        if (asyncDataBuff.pBuffer.ReadPointer ==
            asyncDataBuff.pBuffer.WritePointer) {
          loop_ub = 5800320;
        } else {
          loop_ub = n;
        }
      }
      if (loop_ub < 0) {
        e_rtErrorWithMessageID("number of rows", v_emlrtRTEI.fName,
                               v_emlrtRTEI.lineNo);
      }
      if (loop_ub > 5800320) {
        o_rtErrorWithMessageID(u_emlrtRTEI.fName, u_emlrtRTEI.lineNo);
      }
      asyncDataBuff.pBuffer.read(loop_ub, b_asyncDataBuff, &n);
      //  for i = numel(data):-1:1
      //       fprintf('%f + i%f, ', real(data(i)), imag(data(i)));
      //       if mod(i,20) == 0
      //           fprintf('\n')
      //       end
      //  end
      rtErrorWithMessageID(b_emlrtRTEI.fName, b_emlrtRTEI.lineNo);
    }
    //                 %% Process data if there is enough in the buffers
    if ((asyncDataBuff.pBuffer.WritePointer >= 0) &&
        (asyncDataBuff.pBuffer.ReadPointer <
         asyncDataBuff.pBuffer.WritePointer - MAX_int32_T)) {
      loop_ub = MAX_int32_T;
    } else if ((asyncDataBuff.pBuffer.WritePointer < 0) &&
               (asyncDataBuff.pBuffer.ReadPointer >
                asyncDataBuff.pBuffer.WritePointer - MIN_int32_T)) {
      loop_ub = MIN_int32_T;
    } else {
      loop_ub = asyncDataBuff.pBuffer.WritePointer -
                asyncDataBuff.pBuffer.ReadPointer;
    }
    if (loop_ub < -2147483647) {
      loop_ub = MIN_int32_T;
    } else {
      loop_ub--;
    }
    if (asyncDataBuff.pBuffer.ReadPointer < -2141683327) {
      n = MAX_int32_T;
    } else {
      n = 5800320 - asyncDataBuff.pBuffer.ReadPointer;
    }
    if ((n < 0) && (asyncDataBuff.pBuffer.WritePointer < MIN_int32_T - n)) {
      n = MIN_int32_T;
    } else if ((n > 0) &&
               (asyncDataBuff.pBuffer.WritePointer > MAX_int32_T - n)) {
      n = MAX_int32_T;
    } else {
      n += asyncDataBuff.pBuffer.WritePointer;
    }
    if (asyncDataBuff.pBuffer.ReadPointer <
        asyncDataBuff.pBuffer.WritePointer) {
      n = loop_ub;
    } else if (asyncDataBuff.pBuffer.ReadPointer ==
               asyncDataBuff.pBuffer.WritePointer) {
      n = 5800320;
    }
    if (n >= integratedTimeError) {
      double processingStartToc;
      unsigned int b_varargin_1;
      unsigned int varargin_2;
      integratedTimeError = std::round(sampsForKPulses.contents);
      if (integratedTimeError < 4.294967296E+9) {
        if (integratedTimeError >= 0.0) {
          b_varargin_1 = static_cast<unsigned int>(integratedTimeError);
        } else {
          b_varargin_1 = 0U;
        }
      } else if (integratedTimeError >= 4.294967296E+9) {
        b_varargin_1 = MAX_uint32_T;
      } else {
        b_varargin_1 = 0U;
      }
      integratedTimeError = std::round(overlapSamples.contents);
      if (integratedTimeError < 4.294967296E+9) {
        if (integratedTimeError >= 0.0) {
          varargin_2 = static_cast<unsigned int>(integratedTimeError);
        } else {
          varargin_2 = 0U;
        }
      } else if (integratedTimeError >= 4.294967296E+9) {
        varargin_2 = MAX_uint32_T;
      } else {
        varargin_2 = 0U;
      }
      printf("Buffer Full|| sampsForKPulses: %u, overlapSamples: %u,\n",
             b_varargin_1, varargin_2);
      fflush(stdout);
      if ((asyncDataBuff.pBuffer.WritePointer >= 0) &&
          (asyncDataBuff.pBuffer.ReadPointer <
           asyncDataBuff.pBuffer.WritePointer - MAX_int32_T)) {
        loop_ub = MAX_int32_T;
      } else if ((asyncDataBuff.pBuffer.WritePointer < 0) &&
                 (asyncDataBuff.pBuffer.ReadPointer >
                  asyncDataBuff.pBuffer.WritePointer - MIN_int32_T)) {
        loop_ub = MIN_int32_T;
      } else {
        loop_ub = asyncDataBuff.pBuffer.WritePointer -
                  asyncDataBuff.pBuffer.ReadPointer;
      }
      if (loop_ub < -2147483647) {
        loop_ub = MIN_int32_T;
      } else {
        loop_ub--;
      }
      if (asyncDataBuff.pBuffer.ReadPointer < -2141683327) {
        n = MAX_int32_T;
      } else {
        n = 5800320 - asyncDataBuff.pBuffer.ReadPointer;
      }
      if ((n < 0) && (asyncDataBuff.pBuffer.WritePointer < MIN_int32_T - n)) {
        n = MIN_int32_T;
      } else if ((n > 0) &&
                 (asyncDataBuff.pBuffer.WritePointer > MAX_int32_T - n)) {
        n = MAX_int32_T;
      } else {
        n += asyncDataBuff.pBuffer.WritePointer;
      }
      if (asyncDataBuff.pBuffer.ReadPointer <
          asyncDataBuff.pBuffer.WritePointer) {
        n = loop_ub;
      } else if (asyncDataBuff.pBuffer.ReadPointer ==
                 asyncDataBuff.pBuffer.WritePointer) {
        n = 5800320;
      }
      printf("Running...Buffer full with %d samples. Processing. \n", n);
      fflush(stdout);
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
      // plot(t,abs(x)); hold on
      // Check the timestamps in the buffer for gaps larger
      // than the max interpulse uncertainty. If there are
      // enough dropped packets such that the time is shifted
      // by more than the interpulse uncertainty, then the
      // detection will likely fail or produces bad results. In
      // this case. Skip the processing and clear the buffer.
      coder::diff(t, r2);
      integratedTimeError = 1.0 / Config.contents.Fs;
      loop_ub = r2.size(0);
      for (i = 0; i < loop_ub; i++) {
        r2[i] = r2[i] - integratedTimeError;
      }
      integratedTimeError = coder::sum(r2);
      if ((Config.contents.K > 1.0) &&
          (integratedTimeError > Config.contents.tipu + Config.contents.tipj)) {
        printf("Significant time differences found in timestamp record. "
               "Skipping processing and clearing buffers.\n");
        fflush(stdout);
        resetBuffersFlag = true;
        staleDataFlag = true;
      } else {
        unsigned int validatedHoleFilling[3];
        int nPulseList;
        unsigned int varargin_3;
        if (t.size(0) < 1) {
          rtDynamicBoundsError(1, 1, t.size(0), &gb_emlrtBCI);
        }
        printf("Running...Building priori and waveform. \n");
        fflush(stdout);
        // Set the priori info
        if (configUpdatedFlag) {
          // Initialize states for operational modes
          if (Config.contents.opMode.eq()) {
            loop_ub = 0;
          } else if (Config.contents.opMode.b_eq()) {
            loop_ub = 1;
          } else if (Config.contents.opMode.c_eq()) {
            loop_ub = 2;
          } else if (Config.contents.opMode.d_eq()) {
            loop_ub = 3;
          } else {
            loop_ub = -1;
          }
          switch (loop_ub) {
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
          makepulsestruc(&detectorPulse.A, &detectorPulse.P, &detectorPulse.SNR,
                         &detectorPulse.yw, &detectorPulse.t_0,
                         &detectorPulse.t_f, detectorPulse.t_next,
                         &detectorPulse.fp, &detectorPulse.fstart,
                         &detectorPulse.fend, detectorPulse.mode,
                         &detectorPulse.det_dec, &detectorPulse.con_dec);
          makepulsestruc(&integratedTimeError, &t9_P, &pulseCount, &t9_yw,
                         &t9_t_0, &t9_t_f, expl_temp.t_next, &t9_fp, &t9_fstart,
                         &t9_fend, expl_temp.mode, &t9_det_dec, &t9_con_dec);
          b_expl_temp.con_dec = t9_con_dec;
          b_expl_temp.det_dec = t9_det_dec;
          b_expl_temp.mode.set_size(1, expl_temp.mode.size(1));
          loop_ub = expl_temp.mode.size(1);
          for (i = 0; i < loop_ub; i++) {
            b_expl_temp.mode[i] = expl_temp.mode[i];
          }
          b_expl_temp.fend = t9_fend;
          b_expl_temp.fstart = t9_fstart;
          b_expl_temp.fp = t9_fp;
          b_expl_temp.t_next[0] = expl_temp.t_next[0];
          b_expl_temp.t_next[1] = expl_temp.t_next[1];
          b_expl_temp.t_f = t9_t_f;
          b_expl_temp.t_0 = t9_t_0;
          b_expl_temp.yw = t9_yw;
          b_expl_temp.SNR = pulseCount;
          b_expl_temp.P = t9_P;
          b_expl_temp.A = integratedTimeError;
          pulseStatsPriori = lobj_14.init(
              Config.contents.tp, Config.contents.tip, Config.contents.tipu,
              Config.contents.tipj,
              1.0E-5 * std::abs(Config.contents.tagFreqMHz -
                                Config.contents.channelCenterFreqMHz),
              &detectorPulse, &b_expl_temp);
          configUpdatedFlag = false;
        } else {
          pulseStatsPriori =
              lobj_17.c_init(t9_yw, t9_t_0, t9_t_f, t9_fp, t9_fstart, t9_fend,
                             ps_pre_struc_fend, ps_pre_struc_tmplt,
                             (char *)&mode, ps_pre_struc_pl, ps_pre_struc_clst,
                             ps_pre_struc_cmsk, ps_pre_struc_cpki);
        }
        //                         %% PRIMARY PROCESSING BLOCK
        // Prep waveform for processing/detection
        // UNTITLED2 Construct an instance of this class
        //    Detailed explanation goes here
        val.pf = Config.contents.falseAlarmProb;
        val.evMuParam = 0.0;
        val.evSigmaParam = 0.0;
        val.threshVecFine.set_size(1);
        val.threshVecFine[0] = 0.0;
        b_X.init(x, Config.contents.Fs, t[0], pulseStatsPriori, &val, &lobj_16,
                 &lobj_15);
        b_X.K = Config.contents.K;
        integratedTimeError = std::round(b_X.N);
        if (integratedTimeError < 4.294967296E+9) {
          if (integratedTimeError >= 0.0) {
            b_varargin_1 = static_cast<unsigned int>(integratedTimeError);
          } else {
            b_varargin_1 = 0U;
          }
        } else if (integratedTimeError >= 4.294967296E+9) {
          b_varargin_1 = MAX_uint32_T;
        } else {
          b_varargin_1 = 0U;
        }
        integratedTimeError = std::round(b_X.M);
        if (integratedTimeError < 4.294967296E+9) {
          if (integratedTimeError >= 0.0) {
            varargin_2 = static_cast<unsigned int>(integratedTimeError);
          } else {
            varargin_2 = 0U;
          }
        } else if (integratedTimeError >= 4.294967296E+9) {
          varargin_2 = MAX_uint32_T;
        } else {
          varargin_2 = 0U;
        }
        integratedTimeError = std::round(b_X.J);
        if (integratedTimeError < 4.294967296E+9) {
          if (integratedTimeError >= 0.0) {
            varargin_3 = static_cast<unsigned int>(integratedTimeError);
          } else {
            varargin_3 = 0U;
          }
        } else if (integratedTimeError >= 4.294967296E+9) {
          varargin_3 = MAX_uint32_T;
        } else {
          varargin_3 = 0U;
        }
        coder::internal::validate_print_arguments(
            b_varargin_1, varargin_2, varargin_3, validatedHoleFilling);
        printf("Current interpulse params || N: %u, M: %u, J: %u,\n",
               validatedHoleFilling[0], validatedHoleFilling[1],
               validatedHoleFilling[2]);
        fflush(stdout);
        b_X.setprioridependentprops(b_X.ps_pre);
        b_varargin_1 = static_cast<unsigned int>(b_X.x.size(1));
        printf("Samples in waveform: %u \n", b_varargin_1);
        fflush(stdout);
        integratedTimeError = coder::toc();
        printf("Computing STFT...");
        fflush(stdout);
        b_X.spectro(&lobj_13);
        integratedTimeError = coder::toc() - integratedTimeError;
        printf("complete. Elapsed time: %f seconds \n", integratedTimeError);
        fflush(stdout);
        printf("Building weighting matrix ...");
        fflush(stdout);
        integratedTimeError = coder::toc();
        b_X.setweightingmatrix();
        integratedTimeError = coder::toc() - integratedTimeError;
        printf("complete. Elapsed time: %f seconds \n", integratedTimeError);
        fflush(stdout);
        if (suggestedMode == 'S') {
          loop_ub = 0;
        } else if (suggestedMode == 'C') {
          loop_ub = 1;
        } else if (suggestedMode == 'T') {
          loop_ub = 2;
        } else {
          loop_ub = -1;
        }
        switch (loop_ub) {
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
          printf("UAV-RT: Unsupported mode requested. Defaulting to Discovery "
                 "(D) mode.");
          fflush(stdout);
          mode = 'D';
          break;
        }
        if (coder::internal::b_strcmp(&Config.contents.opMode)) {
          mode = 'D';
        }
        integratedTimeError = coder::toc();
        if (segmentsProcessed == 0.0) {
          printf("Building thresholds  ...");
          fflush(stdout);
          val = b_X.thresh;
          val.makenewthreshold(&b_X);
          b_X.thresh = val;
        } else {
          printf("Setting thresholds from previous waveform  ...");
          fflush(stdout);
          val = b_X.thresh;
          val.setthreshold(&b_X, Xhold);
          b_X.thresh = val;
        }
        integratedTimeError = coder::toc() - integratedTimeError;
        printf("complete. Elapsed time: %f seconds \n", integratedTimeError);
        fflush(stdout);
        b_varargin_1 = static_cast<unsigned int>(b_X.stft->S.size(1));
        printf("Time windows in S: %u \n", b_varargin_1);
        fflush(stdout);
        integratedTimeError = coder::toc();
        printf("Finding pulses...");
        fflush(stdout);
        b_X.process(mode, Config.contents.excldFreqs);
        integratedTimeError = coder::toc() - integratedTimeError;
        printf("complete. Elapsed time: %f seconds \n", integratedTimeError);
        fflush(stdout);
        integratedTimeError = coder::toc() - processingStartToc;
        printf("TOTAL PULSE PROCESSING TIME: %f seconds \n",
               integratedTimeError);
        fflush(stdout);
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
        if (pulsesToSkip.size(1) != 0) {
          currDir_size[1] = pulsesToSkip.size(1);
        } else {
          currDir_size[1] = 0;
        }
        b_pulsesToSkip = pulsesToSkip.reshape(1, currDir_size[1]);
        coder::all(b_pulsesToSkip, r3);
        if (coder::internal::ifWhileCond(r3)) {
          // Check if all were confirmed
          fLock = true;
        }
        // We only ever release if we are in softlock mode and
        // only do so in that case if we are no longer confirming
        // pulses.
        if (coder::internal::c_strcmp(&Config.contents.opMode)) {
          n = r3.size(0);
          loop_ub = r3.size(0);
          for (i = 0; i < loop_ub; i++) {
            tmp_data = !r3[i];
          }
          b_tmp_data.set(&tmp_data, n);
          if (coder::internal::ifWhileCond(b_tmp_data)) {
            fLock = false;
          }
        }
        // Decide when/how the priori is updated for the next
        // segment's processing.
        if (coder::internal::ifWhileCond(r3) &&
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
            (integratedTimeError >
             0.9 * sampsForKPulses.contents / Config.contents.Fs)) {
          // Config.K = Config.K - 1;
          integratedTimeError = std::round(Config.contents.K - 1.0);
          if (integratedTimeError < 4.294967296E+9) {
            b_varargin_1 = static_cast<unsigned int>(integratedTimeError);
          } else {
            b_varargin_1 = MAX_uint32_T;
          }
          printf("WARNING!!! PROCESSING TIME TOOK LONGER THAN WAVEFORM LENGTH. "
                 "STREAMING NOT POSSIBLE. TRY REDUCING NUMBER OF PULSES "
                 "CONSIDERED BY"
                 " 1 TO K = %u \n",
                 b_varargin_1);
          fflush(stdout);
          printf("Resetting all internal data buffers and udp buffers to clear "
                 "potential stale data. \n");
          fflush(stdout);
          resetBuffersFlag = true;
          staleDataFlag = true;
          suggestedMode = 'S';
        }
        segmentsProcessed++;
        // tic
        integratedTimeError = coder::toc();
        // Prepare priori for next segment
        printf("Updating priori...\n");
        fflush(stdout);
        t9_yw = b_X.ps_pos->t_p;
        t9_t_0 = b_X.ps_pos->t_ip;
        t9_t_f = b_X.ps_pos->t_ipu;
        t9_fp = b_X.ps_pos->t_ipj;
        t9_fstart = b_X.ps_pos->fp;
        t9_fend = b_X.ps_pos->fstart;
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
        updatebufferreadvariables(&Config, &stftOverlapFraction,
                                  &overlapSamples, &sampsForKPulses,
                                  b_X.ps_pos);
        integratedTimeError = coder::toc() - integratedTimeError;
        printf("complete. Elapsed time: %f seconds \n", integratedTimeError);
        fflush(stdout);
        // Deal with detected pulses
        // Xhold{mod(segmentsProcessed,maxSegments)} = X;%Keep a maxSegments
        // running record of waveforms for debugging in Matlab Xstruct =
        // obj2structrecursive(); Xhold = X;
        Xhold = waveformcopy(&b_X, &lobj_10, &lobj_11[0], &lobj_12);
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
        r4.set_size(b_x.size(0), b_x.size(1));
        loop_ub = b_x.size(0) * b_x.size(1);
        for (i = 0; i < loop_ub; i++) {
          r4[i] = std::isnan(b_x[i]);
        }
        r5.set_size(r4.size(0), r4.size(1));
        loop_ub = r4.size(0) * r4.size(1);
        for (i = 0; i < loop_ub; i++) {
          r5[i] = !r4[i];
        }
        if (coder::internal::b_ifWhileCond(r5)) {
          for (int j{0}; j < nPulseList; j++) {
            i = b_X.ps_pos->pl.size(1);
            if (j + 1 > i) {
              rtDynamicBoundsError(j + 1, 1, i, &hb_emlrtBCI);
            }
            integratedTimeError = b_X.ps_pos->pl[j].t_0;
            if (j + 1 > ps_pre_struc_pl.size(1)) {
              rtDynamicBoundsError(j + 1, 1, ps_pre_struc_pl.size(1),
                                   &ib_emlrtBCI);
            }
            printf("Pulse at %f Hz detected. SNR: %f \n \t Confirmation "
                   "status: %u \n\t Interpulse time    : %f \n",
                   Config.contents.channelCenterFreqMHz +
                       ps_pre_struc_pl[j].fp * 1.0E-6,
                   ps_pre_struc_pl[j].SNR,
                   static_cast<unsigned int>(ps_pre_struc_pl[j].con_dec),
                   integratedTimeError - previousPulseTime);
            fflush(stdout);
            if (integratedTimeError - previousPulseTime <
                0.1 * b_X.ps_pre->t_ip) {
              // Overlap occasionally will redetect the same pulse
              printf("(\t ^---This likely a repeat of a previously detected "
                     "pulse. Will not be transmitted. \n");
              fflush(stdout);
              if (j + 1 > pulsesToSkip.size(1)) {
                rtDynamicBoundsError(j + 1, 1, pulsesToSkip.size(1),
                                     &jb_emlrtBCI);
              }
              pulsesToSkip[j] = true;
            } else {
              previousPulseTime = integratedTimeError;
            }
          }
        } else {
          printf("No pulses detected \n");
          fflush(stdout);
        }
        pulseCount = 0.0;
        b_x.set_size(b_X.ps_pos->cpki.size(0), b_X.ps_pos->cpki.size(1));
        loop_ub = b_X.ps_pos->cpki.size(0) * b_X.ps_pos->cpki.size(1);
        for (i = 0; i < loop_ub; i++) {
          b_x[i] = b_X.ps_pos->cpki[i];
        }
        r4.set_size(b_x.size(0), b_x.size(1));
        loop_ub = b_x.size(0) * b_x.size(1);
        for (i = 0; i < loop_ub; i++) {
          r4[i] = std::isnan(b_x[i]);
        }
        r5.set_size(r4.size(0), r4.size(1));
        loop_ub = r4.size(0) * r4.size(1);
        for (i = 0; i < loop_ub; i++) {
          r5[i] = !r4[i];
        }
        if (coder::internal::b_ifWhileCond(r5)) {
          printf("Transmitting ROS2 pulse messages");
          fflush(stdout);
          for (int j{0}; j < nPulseList; j++) {
            //  %% Build out pulseOut structure parameters for sending
            //  pulseOut.tag_id                     = uint32(Config.ID);
            //  pulseOut.detector_dir               = currDir;%ID is a string
            //  pulseOut.frequency                  =
            //  Config.channelCenterFreqMHz + (X.ps_pos.pl(j).fp)*1e-6;
            //      t_0     = X.ps_pos.pl(j).t_0;
            //      t_f     = X.ps_pos.pl(j).t_f;
            //      t_nxt_0 = X.ps_pos.pl(j).t_next(1);
            //      t_nxt_f = X.ps_pos.pl(j).t_next(2);
            //  pulseOut.start_time.sec             = int32(floor(t_0));
            //  pulseOut.start_time.nanosec         =
            //  uint32(mod(t_0,floor(t_0))*1e9); pulseOut.end_time.sec =
            //  int32(floor(t_f)); pulseOut.end_time.nanosec           =
            //  uint32(mod(t_f,floor(t_f))*1e9); pulseOut.predict_next_start.sec
            //  = int32(floor(t_nxt_0)); pulseOut.predict_next_start.nanosec =
            //  uint32(mod(t_nxt_0,floor(t_nxt_0))*1e9);
            //  pulseOut.predict_next_end.sec       = int32(floor(t_nxt_f));
            //  pulseOut.predict_next_end.nanosec   =
            //  uint32(mod(t_nxt_f,round(t_nxt_f))*1e9); pulseOut.snr =
            //  X.ps_pos.pl(j).SNR; pulseOut.stft_score                 =
            //  real(X.ps_pos.pl(j).yw); pulseOut.group_ind                  =
            //  uint16(j); groupSNRList = 10.^([X.ps_pos.pl(:).SNR]/10);%Average
            //  SNR in dB groupSNRMeanLinear                  =
            //  mean(groupSNRList,'all'); if groupSNRMeanLinear<0
            //      groupSNRMeanDB                  = -Inf;
            //  else
            //      groupSNRMeanDB                  =
            //      10*log10(groupSNRMeanLinear);
            //  end
            //  %10log10 can produce complex results and group_snr required a
            //  real value. Otherwise coder will %generate type errors
            //  pulseOut.group_snr          =
            //  double(groupSNRMeanDB);%10*log10(mean(10.^([X.ps_pos.clst(X.ps_pos.cpki(j),:).SNR]/10)));%Average
            //  SNR in dB pulseOut.detection_status   = X.ps_pos.pl(j).det_dec;
            //  pulseOut.confirmed_status   = X.ps_pos.pl(j).con_dec;
            loop_ub = b_X.ps_pos->pl.size(1);
            c_X.set_size(loop_ub);
            loop_ub--;
            for (i = 0; i <= loop_ub; i++) {
              c_X[i] = b_X.ps_pos->pl[i];
            }
            n = c_X.size(0);
            if (c_X.size(0) == 0) {
              i = 0;
            } else {
              i = c_X.size(0);
            }
            c_varargin_1.set_size(1, i);
            if (c_X.size(0) > 2147483646) {
              coder::check_forloop_overflow_error();
            }
            for (loop_ub = 0; loop_ub < n; loop_ub++) {
              c_varargin_1[loop_ub] = c_X[loop_ub].SNR;
            }
            if (c_varargin_1.size(1) != 0) {
              loop_ub = c_varargin_1.size(1);
            } else {
              loop_ub = 0;
            }
            // Average SNR in dB
            c_varargin_1.set_size(1, loop_ub);
            for (i = 0; i < loop_ub; i++) {
              integratedTimeError = c_varargin_1[i] / 10.0;
              c_varargin_1[i] = rt_powd_snf(10.0, integratedTimeError);
            }
            t9_P = coder::mean(c_varargin_1);
            if (t9_P < 0.0) {
              rtErrorWithMessageID("log10", emlrtRTEI.fName, emlrtRTEI.lineNo);
            }
            t9_P = std::log10(t9_P);
            // 10log10 can produce complex results and group_snr required a real
            // value. Otherwise coder will generate type errors
            // 10*log10(mean(10.^([X.ps_pos.clst(X.ps_pos.cpki(j),:).SNR]/10)));%Average
            // SNR in dB
            //  Publish pulses to UDP
            i = b_X.ps_pos->pl.size(1);
            if (j + 1 > i) {
              rtDynamicBoundsError(j + 1, 1, i, &kb_emlrtBCI);
            }
            detectorPulse = b_X.ps_pos->pl[j];
            if (j + 1 > pulsesToSkip.size(1)) {
              rtDynamicBoundsError(j + 1, 1, pulsesToSkip.size(1),
                                   &lb_emlrtBCI);
            }
            if (!pulsesToSkip[j]) {
              unsigned short u;
              //  UDP Send
              integratedTimeError = std::round(Config.contents.ID);
              if (integratedTimeError < 4.294967296E+9) {
                if (integratedTimeError >= 0.0) {
                  b_varargin_1 = static_cast<unsigned int>(integratedTimeError);
                } else {
                  b_varargin_1 = 0U;
                }
              } else if (integratedTimeError >= 4.294967296E+9) {
                b_varargin_1 = MAX_uint32_T;
              } else {
                b_varargin_1 = 0U;
              }
              integratedTimeError = std::round(
                  (Config.contents.channelCenterFreqMHz + detectorPulse.fp) *
                  1.0E+6);
              if (integratedTimeError < 4.294967296E+9) {
                if (integratedTimeError >= 0.0) {
                  varargin_2 = static_cast<unsigned int>(integratedTimeError);
                } else {
                  varargin_2 = 0U;
                }
              } else if (integratedTimeError >= 4.294967296E+9) {
                varargin_2 = MAX_uint32_T;
              } else {
                varargin_2 = 0U;
              }
              if (j + 1U < 65536U) {
                u = static_cast<unsigned short>(static_cast<double>(j) + 1.0);
              } else {
                u = MAX_uint16_T;
              }
              udpPulseSenderSend(
                  udpPulseSender, b_varargin_1, varargin_2, detectorPulse.t_0,
                  detectorPulse.t_next[0], detectorPulse.SNR, detectorPulse.yw,
                  u, 10.0 * t9_P,
                  static_cast<unsigned char>(detectorPulse.det_dec),
                  static_cast<unsigned char>(detectorPulse.con_dec));
              //  ROS send
              pulseCount++;
            }
            //  %s pulseMsg.detector_dir
            //  %s pulseMsg.tag_id
            //  %.6f pulseMsg.frequency
            //  %d pulseMsg.start_time.sec
            //  %u pulseMsg.start_time.nanosec
            //  %d pulseMsg.end_time.sec
            //  %u pulseMsg.end_time.nanosec
            //  %d pulseMsg.predict_next_start.sec
            //  %u pulseMsg.predict_next_start.nanosec
            //  %d pulseMsg.predict_next_end.sec
            //  %u pulseMsg.predict_next_end.nanosec
            //  %.2f pulseMsg.snr
            //  %.3e pulseMsg.dft_real
            //  %.3e pulseMsg.dft_imag
            //  %u pulseMsg.group_ind
            //  %.2e pulseMsg.group_snr
            //  logicalStr = {'0','1'}
            //  %u logicalStr{int8(pulseMsg.detection_status)+1}
            //  %u logicalStr{int8(pulseMsg.confirmed_status)+1}
            //
            //                                          logicalStr = {'0','1'};
            //                                          formatSpecPulseMsg =
            //                                          ['%.6f',',','%d',',','%u','%d',',','%u',',','%d',',','%u',',','%d',',','%u',',',...
            //                                                                '%.2f',',','%.3e',',','%.3e',',','%u',',','%.2e',',','%c',',','%c','\n'];
            //
            //                                          fprintf(pulseWriterFileID,formatSpecPulseMsg,...
            //                                              pulseMsg.frequency,...
            //                                              pulseMsg.start_time.sec,...
            //                                              pulseMsg.start_time.nanosec,...
            //                                              pulseMsg.end_time.sec,...
            //                                              pulseMsg.end_time.nanosec,...
            //                                              pulseMsg.predict_next_start.sec,...
            //                                              pulseMsg.predict_next_start.nanosec,...
            //                                              pulseMsg.predict_next_end.sec,...
            //                                              pulseMsg.predict_next_end.nanosec,...
            //                                              pulseMsg.snr,...
            //                                              pulseMsg.dft_real,...
            //                                              pulseMsg.dft_imag,...
            //                                              pulseMsg.group_ind,...
            //                                              pulseMsg.group_snr,...
            //                                              logicalStr{int8(pulseMsg.detection_status)+1},...
            //                                              logicalStr{int8(pulseMsg.confirmed_status)+1});
            printf(".");
            fflush(stdout);
            //                                     end
          }
          if (pulseCount < 4.294967296E+9) {
            b_varargin_1 = static_cast<unsigned int>(pulseCount);
          } else {
            b_varargin_1 = MAX_uint32_T;
          }
          printf("complete. Transmitted %u pulse(s).\n", b_varargin_1);
          fflush(stdout);
        } else {
          printf("\n");
          fflush(stdout);
        }
        varargin_1.set_size(1, 2);
        varargin_1[0] = mode;
        varargin_1[1] = '\x00';
        printf("Current Mode: %s\n", &varargin_1[0]);
        fflush(stdout);
        printf("====================================\n");
        fflush(stdout);
      }
      b_this.init();
      integratedTimeError = coder::toc();
      printf("tocElapsed - clockElapsed = %0.6f  **************** \n",
             integratedTimeError -
                 (std::round(b_this.data.re / 1000.0 * 1.0E+6) / 1.0E+6 -
                  startTime));
      fflush(stdout);
      integratedTimeError = coder::toc() - processingStartToc;
      printf("TOTAL SEGMENT PROCESSING TIME: %f seconds \n",
             integratedTimeError);
      fflush(stdout);
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
