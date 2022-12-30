//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: uavrt_detection.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 30-Dec-2022 12:50:56
//

// Include Files
#include "uavrt_detection.h"
#include "AsyncBuffer.h"
#include "AsyncBuffercgHelper.h"
#include "DetectorConfig.h"
#include "all.h"
#include "diff.h"
#include "eml_int_forloop_overflow_check.h"
#include "feof.h"
#include "fgetl.h"
#include "fileManager.h"
#include "find.h"
#include "fseek.h"
#include "ftell.h"
#include "ifWhileCond.h"
#include "lower.h"
#include "makepulsestruc.h"
#include "pulsestats.h"
#include "ref.h"
#include "rt_nonfinite.h"
#include "str2double.h"
#include "str2matrix.h"
#include "strcmp.h"
#include "string1.h"
#include "sum.h"
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
#include "wfmstft.h"
#include "wgn.h"
#include "coder_array.h"
#include "omp.h"
#include "udp.h"
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <stdio.h>
#include <string.h>
#include <string>

// Variable Definitions
static rtRunTimeErrorInfo b_emlrtRTEI{
    10,              // lineNo
    "mustBePositive" // fName
};

// Function Declarations
static void b_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void c_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void i_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void rtErrorWithMessageID(const char *r, const char *aFcnName,
                                 int aLineNum);

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
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void c_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
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
static void i_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Value must be integer.";
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
static void rtErrorWithMessageID(const char *r, const char *aFcnName,
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
  double a__1;
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
  a__1 = std::ceil(ps_input->t_p * X0.Fs);
  // Samples per pulse
  // Number of elements in STFT window
  n_ol = std::floor(stftOverlapFraction->contents * a__1);
  // Number of elements overlap in STFT window
  a__1 -= n_ol;
  // Number of elements in each step of STFT
  // Time of each step of STFT
  N = std::floor(std::ceil(ps_input->t_ip * X0.Fs) / a__1);
  M = std::ceil(std::ceil(ps_input->t_ipu * X0.Fs) / a__1);
  J = std::ceil(std::ceil(ps_input->t_ipj * X0.Fs) / a__1);
  //          overlapWindows  = 2*Config.K*M+1;
  //          overlapSamples	= n_ws*overlapWindows;
  //          %sampsForKPulses = Config.K*n_ws*(N+M+1+1);
  //          sampsForKPulses = n_ws*(Config.K*(N+M)+1+1);
  overlapSamples->contents = a__1 * (2.0 * (Config->contents.K * M + J));
  //          if Config.K~=1
  //              sampsForKPulses = n_ws*(Config.K*(N+M)-2*M)+n_ol;
  //          else
  //              sampsForKPulses = n_ws*(N+M+J)+n_ol;
  //          end
  // See 2022-07-11 for updates to samples def
  sampsForKPulses->contents =
      a__1 * ((Config->contents.K * (N + M) + J) + 1.0) + n_ol;
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
  a__1 = std::round(sampsForKPulses->contents);
  if (a__1 < 4.294967296E+9) {
    if (a__1 >= 0.0) {
      u = static_cast<unsigned int>(a__1);
    } else {
      u = 0U;
    }
  } else if (a__1 >= 4.294967296E+9) {
    u = MAX_uint32_T;
  } else {
    u = 0U;
  }
  a__1 = std::round(overlapSamples->contents);
  if (a__1 < 4.294967296E+9) {
    if (a__1 >= 0.0) {
      u1 = static_cast<unsigned int>(a__1);
    } else {
      u1 = 0U;
    }
  } else if (a__1 >= 4.294967296E+9) {
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
  static rtBoundsCheckInfo eb_emlrtBCI{
      -1,                           // iFirst
      -1,                           // iLast
      136,                          // lineNo
      28,                           // colNo
      "rawLine",                    // aName
      "DetectorConfig/setFromFile", // fName
      "H:\\repos\\uavrt_detection\\detector\\config\\DetectorConfig.m", // pName
      0 // checkKind
  };
  static rtBoundsCheckInfo fb_emlrtBCI{
      -1,                           // iFirst
      -1,                           // iLast
      167,                          // lineNo
      31,                           // colNo
      "sepByte",                    // aName
      "DetectorConfig/setFromFile", // fName
      "H:\\repos\\uavrt_detection\\detector\\config\\DetectorConfig.m", // pName
      0 // checkKind
  };
  static rtBoundsCheckInfo gb_emlrtBCI{
      -1,                           // iFirst
      -1,                           // iLast
      171,                          // lineNo
      28,                           // colNo
      "lineStr",                    // aName
      "DetectorConfig/setFromFile", // fName
      "H:\\repos\\uavrt_detection\\detector\\config\\DetectorConfig.m", // pName
      0 // checkKind
  };
  static rtBoundsCheckInfo hb_emlrtBCI{
      -1,                           // iFirst
      -1,                           // iLast
      174,                          // lineNo
      55,                           // colNo
      "tabLocs",                    // aName
      "DetectorConfig/setFromFile", // fName
      "H:\\repos\\uavrt_detection\\detector\\config\\DetectorConfig.m", // pName
      0 // checkKind
  };
  static rtBoundsCheckInfo ib_emlrtBCI{
      -1,                           // iFirst
      -1,                           // iLast
      175,                          // lineNo
      63,                           // colNo
      "colonLocation",              // aName
      "DetectorConfig/setFromFile", // fName
      "H:\\repos\\uavrt_detection\\detector\\config\\DetectorConfig.m", // pName
      0 // checkKind
  };
  static rtBoundsCheckInfo jb_emlrtBCI{
      -1,                           // iFirst
      -1,                           // iLast
      220,                          // lineNo
      69,                           // colNo
      "sepByte",                    // aName
      "DetectorConfig/setFromFile", // fName
      "H:\\repos\\uavrt_detection\\detector\\config\\DetectorConfig.m", // pName
      0 // checkKind
  };
  static rtBoundsCheckInfo kb_emlrtBCI{
      -1,                           // iFirst
      -1,                           // iLast
      176,                          // lineNo
      47,                           // colNo
      "lineStr",                    // aName
      "DetectorConfig/setFromFile", // fName
      "H:\\repos\\uavrt_detection\\detector\\config\\DetectorConfig.m", // pName
      0 // checkKind
  };
  static rtBoundsCheckInfo lb_emlrtBCI{
      -1,                           // iFirst
      -1,                           // iLast
      176,                          // lineNo
      74,                           // colNo
      "lineStr",                    // aName
      "DetectorConfig/setFromFile", // fName
      "H:\\repos\\uavrt_detection\\detector\\config\\DetectorConfig.m", // pName
      0 // checkKind
  };
  static rtBoundsCheckInfo mb_emlrtBCI{
      -1,                           // iFirst
      -1,                           // iLast
      175,                          // lineNo
      47,                           // colNo
      "lineStr",                    // aName
      "DetectorConfig/setFromFile", // fName
      "H:\\repos\\uavrt_detection\\detector\\config\\DetectorConfig.m", // pName
      0 // checkKind
  };
  static rtBoundsCheckInfo nb_emlrtBCI{
      -1,                           // iFirst
      -1,                           // iLast
      175,                          // lineNo
      49,                           // colNo
      "lineStr",                    // aName
      "DetectorConfig/setFromFile", // fName
      "H:\\repos\\uavrt_detection\\detector\\config\\DetectorConfig.m", // pName
      0 // checkKind
  };
  static rtBoundsCheckInfo ob_emlrtBCI{
      -1,                           // iFirst
      -1,                           // iLast
      222,                          // lineNo
      69,                           // colNo
      "sepByte",                    // aName
      "DetectorConfig/setFromFile", // fName
      "H:\\repos\\uavrt_detection\\detector\\config\\DetectorConfig.m", // pName
      0 // checkKind
  };
  static rtRunTimeErrorInfo qc_emlrtRTEI{
      18,                    // lineNo
      "binaryRelopValidator" // fName
  };
  static rtRunTimeErrorInfo rc_emlrtRTEI{
      10,                 // lineNo
      "mustBeNonnegative" // fName
  };
  coder::b_rtString _in;
  coder::array<creal_T, 2U> r;
  coder::array<double, 2U> sepByte;
  coder::array<double, 2U> val;
  coder::array<int, 2U> match_out;
  coder::array<int, 2U> matches;
  coder::array<unsigned int, 2U> tabLocs;
  coder::array<char, 2U> c_lineStr;
  coder::array<char, 2U> lineStr;
  coder::array<boolean_T, 2U> b_lineStr;
  int ii_data;
  char varargin_1[66];
  signed char fileid;
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
  fileid = coder::cfopen(configPath->contents.Value);
  if (fileid == -1) {
    std::copy(&configPath->contents.Value[0], &configPath->contents.Value[65],
              &varargin_1[0]);
    varargin_1[65] = '\x00';
    printf("Failed to open config file: %s\n", &varargin_1[0]);
    fflush(stdout);
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  } else {
    double configNum;
    double d;
    int i;
    boolean_T done;
    configNum = 0.0;
    done = false;
    // coder.varsize('sepLine')
    sepByte.set_size(1, 1);
    sepByte[0] = 0.0;
    // First figure out where the separator lines are
    while (!done) {
      // currByte = ftell(fid);
      coder::fgetl(static_cast<double>(fileid), lineStr);
      if (lineStr.size(1) < 1) {
        rtDynamicBoundsError(1, 1, lineStr.size(1), &eb_emlrtBCI);
      }
      if (lineStr[0] == '#') {
        // && lineNum~=1
        if (configNum == 0.0) {
          sepByte.set_size(1, 1);
          d = coder::b_ftell(static_cast<double>(fileid));
          sepByte[0] = d;
        } else {
          // sepByte(configNum) = ftell(fid);
          d = coder::b_ftell(static_cast<double>(fileid));
          i = sepByte.size(1);
          sepByte.set_size(1, sepByte.size(1) + 1);
          sepByte[i] = d;
          // Modified for Coder compatibility
        }
        configNum++;
      }
      done = (coder::b_feof(static_cast<double>(fileid)) == 1.0);
    }
    // sepByte(configNum) = ftell(fid);
    d = coder::b_ftell(static_cast<double>(fileid));
    i = sepByte.size(1);
    sepByte.set_size(1, sepByte.size(1) + 1);
    sepByte[i] = d;
    // Modified for Coder compatibility
    // Jump to the line for the entry requested
    if ((static_cast<int>(configNum) < 1) ||
        (static_cast<int>(configNum) > sepByte.size(1))) {
      rtDynamicBoundsError(static_cast<int>(configNum), 1, sepByte.size(1),
                           &fb_emlrtBCI);
    }
    coder::b_fseek(static_cast<double>(fileid),
                   sepByte[static_cast<int>(configNum) - 1]);
    done = false;
    int exitg1;
    do {
      exitg1 = 0;
      if (!done) {
        coder::fgetl(static_cast<double>(fileid), lineStr);
        if (lineStr.size(1) < 1) {
          rtDynamicBoundsError(1, 1, lineStr.size(1), &gb_emlrtBCI);
        }
        if (lineStr[0] != '#') {
          int ii_size[2];
          int match_idx;
          int text_len;
          b_lineStr.set_size(1, lineStr.size(1));
          text_len = lineStr.size(1);
          for (i = 0; i < text_len; i++) {
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
            text_len = match_out.size(1);
            for (i = 0; i < text_len; i++) {
              tabLocs[i] = static_cast<unsigned int>(match_out[i]);
            }
          }
          // Thanks to
          // https://www.mathworks.com/matlabcentral/answers/529668-how-do-i-detect-a-tab-character-in-a-line-of-text-read-by-fgetl
          if (tabLocs.size(1) < 1) {
            rtDynamicBoundsError(1, 1, tabLocs.size(1), &hb_emlrtBCI);
          }
          // note regexp is not supported for code generation
          if (ii_size[1] < 1) {
            rtDynamicBoundsError(1, 1, ii_size[1], &ib_emlrtBCI);
          }
          if (static_cast<double>(ii_data) - 1.0 < 1.0) {
            text_len = 0;
          } else {
            if (lineStr.size(1) < 1) {
              rtDynamicBoundsError(1, 1, lineStr.size(1), &mb_emlrtBCI);
            }
            if ((ii_data - 1 < 1) || (ii_data - 1 > lineStr.size(1))) {
              rtDynamicBoundsError(ii_data - 1, 1, lineStr.size(1),
                                   &nb_emlrtBCI);
            }
            text_len = ii_data - 1;
          }
          if (tabLocs[0] + 1U > static_cast<unsigned int>(lineStr.size(1))) {
            i = 0;
            match_idx = 0;
          } else {
            i = static_cast<int>(tabLocs[0] + 1U);
            if ((i < 1) || (i > lineStr.size(1))) {
              rtDynamicBoundsError(i, 1, lineStr.size(1), &kb_emlrtBCI);
            }
            i--;
            if (lineStr.size(1) < 1) {
              rtDynamicBoundsError(lineStr.size(1), 1, lineStr.size(1),
                                   &lb_emlrtBCI);
            }
            match_idx = lineStr.size(1);
          }
          c_lineStr.set_size(1, text_len);
          for (ii_data = 0; ii_data < text_len; ii_data++) {
            c_lineStr[ii_data] = lineStr[ii_data];
          }
          if (!coder::internal::b_strcmp(c_lineStr)) {
            c_lineStr.set_size(1, text_len);
            for (ii_data = 0; ii_data < text_len; ii_data++) {
              c_lineStr[ii_data] = lineStr[ii_data];
            }
            if (coder::internal::c_strcmp(c_lineStr)) {
              creal_T dc;
              text_len = match_idx - i;
              c_lineStr.set_size(1, text_len);
              for (match_idx = 0; match_idx < text_len; match_idx++) {
                c_lineStr[match_idx] = lineStr[i + match_idx];
              }
              dc = coder::str2double(c_lineStr);
              if (!(dc.re >= 0.0)) {
                b_rtErrorWithMessageID(rc_emlrtRTEI.fName, rc_emlrtRTEI.lineNo);
              }
              Config->contents.channelCenterFreqMHz = dc.re;
            } else {
              c_lineStr.set_size(1, text_len);
              for (ii_data = 0; ii_data < text_len; ii_data++) {
                c_lineStr[ii_data] = lineStr[ii_data];
              }
              if (!coder::internal::d_strcmp(c_lineStr)) {
                c_lineStr.set_size(1, text_len);
                for (ii_data = 0; ii_data < text_len; ii_data++) {
                  c_lineStr[ii_data] = lineStr[ii_data];
                }
                if (coder::internal::e_strcmp(c_lineStr)) {
                  unsigned short in;
                  text_len = match_idx - i;
                  c_lineStr.set_size(1, text_len);
                  for (match_idx = 0; match_idx < text_len; match_idx++) {
                    c_lineStr[match_idx] = lineStr[i + match_idx];
                  }
                  creal_T dc;
                  dc = coder::str2double(c_lineStr);
                  d = std::round(dc.re);
                  if (d < 65536.0) {
                    if (d >= 0.0) {
                      in = static_cast<unsigned short>(d);
                    } else {
                      in = 0U;
                    }
                  } else if (d >= 65536.0) {
                    in = MAX_uint16_T;
                  } else {
                    in = 0U;
                  }
                  Config->contents.portData = in;
                  if (in <= 0) {
                    c_rtErrorWithMessageID(b_emlrtRTEI.fName,
                                           b_emlrtRTEI.lineNo);
                  }
                } else {
                  c_lineStr.set_size(1, text_len);
                  for (ii_data = 0; ii_data < text_len; ii_data++) {
                    c_lineStr[ii_data] = lineStr[ii_data];
                  }
                  if (!coder::internal::f_strcmp(c_lineStr)) {
                    c_lineStr.set_size(1, text_len);
                    for (ii_data = 0; ii_data < text_len; ii_data++) {
                      c_lineStr[ii_data] = lineStr[ii_data];
                    }
                    if (coder::internal::g_strcmp(c_lineStr)) {
                      unsigned short in;
                      text_len = match_idx - i;
                      c_lineStr.set_size(1, text_len);
                      for (match_idx = 0; match_idx < text_len; match_idx++) {
                        c_lineStr[match_idx] = lineStr[i + match_idx];
                      }
                      creal_T dc;
                      dc = coder::str2double(c_lineStr);
                      d = std::round(dc.re);
                      if (d < 65536.0) {
                        if (d >= 0.0) {
                          in = static_cast<unsigned short>(d);
                        } else {
                          in = 0U;
                        }
                      } else if (d >= 65536.0) {
                        in = MAX_uint16_T;
                      } else {
                        in = 0U;
                      }
                      if (in <= 0) {
                        c_rtErrorWithMessageID(b_emlrtRTEI.fName,
                                               b_emlrtRTEI.lineNo);
                      }
                    } else {
                      c_lineStr.set_size(1, text_len);
                      for (ii_data = 0; ii_data < text_len; ii_data++) {
                        c_lineStr[ii_data] = lineStr[ii_data];
                      }
                      if (coder::internal::h_strcmp(c_lineStr)) {
                        creal_T dc;
                        text_len = match_idx - i;
                        c_lineStr.set_size(1, text_len);
                        for (match_idx = 0; match_idx < text_len; match_idx++) {
                          c_lineStr[match_idx] = lineStr[i + match_idx];
                        }
                        dc = coder::str2double(c_lineStr);
                        if (!(dc.re > 0.0)) {
                          c_rtErrorWithMessageID(b_emlrtRTEI.fName,
                                                 b_emlrtRTEI.lineNo);
                        }
                        Config->contents.Fs = dc.re;
                      } else {
                        c_lineStr.set_size(1, text_len);
                        for (ii_data = 0; ii_data < text_len; ii_data++) {
                          c_lineStr[ii_data] = lineStr[ii_data];
                        }
                        if (coder::internal::i_strcmp(c_lineStr)) {
                          text_len = match_idx - i;
                          c_lineStr.set_size(1, text_len);
                          for (match_idx = 0; match_idx < text_len;
                               match_idx++) {
                            c_lineStr[match_idx] = lineStr[i + match_idx];
                          }
                          creal_T dc;
                          dc = coder::str2double(c_lineStr);
                          Config->contents.tagFreqMHz = dc.re;
                        } else {
                          c_lineStr.set_size(1, text_len);
                          for (ii_data = 0; ii_data < text_len; ii_data++) {
                            c_lineStr[ii_data] = lineStr[ii_data];
                          }
                          if (coder::internal::j_strcmp(c_lineStr)) {
                            creal_T dc;
                            text_len = match_idx - i;
                            c_lineStr.set_size(1, text_len);
                            for (match_idx = 0; match_idx < text_len;
                                 match_idx++) {
                              c_lineStr[match_idx] = lineStr[i + match_idx];
                            }
                            dc = coder::str2double(c_lineStr);
                            if (!(dc.re > 0.0)) {
                              c_rtErrorWithMessageID(b_emlrtRTEI.fName,
                                                     b_emlrtRTEI.lineNo);
                            }
                            Config->contents.tp = dc.re;
                          } else {
                            c_lineStr.set_size(1, text_len);
                            for (ii_data = 0; ii_data < text_len; ii_data++) {
                              c_lineStr[ii_data] = lineStr[ii_data];
                            }
                            if (coder::internal::k_strcmp(c_lineStr)) {
                              creal_T dc;
                              text_len = match_idx - i;
                              c_lineStr.set_size(1, text_len);
                              for (match_idx = 0; match_idx < text_len;
                                   match_idx++) {
                                c_lineStr[match_idx] = lineStr[i + match_idx];
                              }
                              dc = coder::str2double(c_lineStr);
                              if (!(dc.re > 0.0)) {
                                c_rtErrorWithMessageID(b_emlrtRTEI.fName,
                                                       b_emlrtRTEI.lineNo);
                              }
                              Config->contents.tip = dc.re;
                            } else {
                              c_lineStr.set_size(1, text_len);
                              for (ii_data = 0; ii_data < text_len; ii_data++) {
                                c_lineStr[ii_data] = lineStr[ii_data];
                              }
                              if (coder::internal::l_strcmp(c_lineStr)) {
                                creal_T dc;
                                text_len = match_idx - i;
                                c_lineStr.set_size(1, text_len);
                                for (match_idx = 0; match_idx < text_len;
                                     match_idx++) {
                                  c_lineStr[match_idx] = lineStr[i + match_idx];
                                }
                                dc = coder::str2double(c_lineStr);
                                if (!(dc.re >= 0.0)) {
                                  b_rtErrorWithMessageID(rc_emlrtRTEI.fName,
                                                         rc_emlrtRTEI.lineNo);
                                }
                                Config->contents.tipu = dc.re;
                              } else {
                                c_lineStr.set_size(1, text_len);
                                for (ii_data = 0; ii_data < text_len;
                                     ii_data++) {
                                  c_lineStr[ii_data] = lineStr[ii_data];
                                }
                                if (coder::internal::m_strcmp(c_lineStr)) {
                                  creal_T dc;
                                  text_len = match_idx - i;
                                  c_lineStr.set_size(1, text_len);
                                  for (match_idx = 0; match_idx < text_len;
                                       match_idx++) {
                                    c_lineStr[match_idx] =
                                        lineStr[i + match_idx];
                                  }
                                  dc = coder::str2double(c_lineStr);
                                  if (!(dc.re >= 0.0)) {
                                    b_rtErrorWithMessageID(rc_emlrtRTEI.fName,
                                                           rc_emlrtRTEI.lineNo);
                                  }
                                  Config->contents.tipj = dc.re;
                                } else {
                                  boolean_T b_bool;
                                  b_bool = false;
                                  if ((text_len == 1) && (lineStr[0] == 'K')) {
                                    b_bool = true;
                                  }
                                  if (b_bool) {
                                    unsigned char b_in;
                                    text_len = match_idx - i;
                                    c_lineStr.set_size(1, text_len);
                                    for (match_idx = 0; match_idx < text_len;
                                         match_idx++) {
                                      c_lineStr[match_idx] =
                                          lineStr[i + match_idx];
                                    }
                                    creal_T dc;
                                    dc = coder::str2double(c_lineStr);
                                    d = std::round(dc.re);
                                    if (d < 256.0) {
                                      if (d >= 0.0) {
                                        b_in = static_cast<unsigned char>(d);
                                      } else {
                                        b_in = 0U;
                                      }
                                    } else if (d >= 256.0) {
                                      b_in = MAX_uint8_T;
                                    } else {
                                      b_in = 0U;
                                    }
                                    Config->contents.K = b_in;
                                    if (b_in <= 0) {
                                      c_rtErrorWithMessageID(
                                          b_emlrtRTEI.fName,
                                          b_emlrtRTEI.lineNo);
                                    }
                                  } else {
                                    c_lineStr.set_size(1, text_len);
                                    for (ii_data = 0; ii_data < text_len;
                                         ii_data++) {
                                      c_lineStr[ii_data] = lineStr[ii_data];
                                    }
                                    if (coder::internal::n_strcmp(c_lineStr)) {
                                      text_len = match_idx - i;
                                      _in.Value.set_size(1, text_len);
                                      for (match_idx = 0; match_idx < text_len;
                                           match_idx++) {
                                        _in.Value[match_idx] =
                                            lineStr[i + match_idx];
                                      }
                                      Config->contents.opMode = _in;
                                    } else {
                                      c_lineStr.set_size(1, text_len);
                                      for (ii_data = 0; ii_data < text_len;
                                           ii_data++) {
                                        c_lineStr[ii_data] = lineStr[ii_data];
                                      }
                                      if (coder::internal::o_strcmp(
                                              c_lineStr)) {
                                        text_len = match_idx - i;
                                        c_lineStr.set_size(1, text_len);
                                        for (match_idx = 0;
                                             match_idx < text_len;
                                             match_idx++) {
                                          c_lineStr[match_idx] =
                                              lineStr[i + match_idx];
                                        }
                                        str2matrix(c_lineStr, r);
                                        val.set_size(r.size(0), r.size(1));
                                        text_len = r.size(0) * r.size(1);
                                        for (i = 0; i < text_len; i++) {
                                          val[i] = r[i].re;
                                        }
                                        coder::internal::validator_check_size(
                                            val, Config->contents.excldFreqs);
                                      } else {
                                        c_lineStr.set_size(1, text_len);
                                        for (ii_data = 0; ii_data < text_len;
                                             ii_data++) {
                                          c_lineStr[ii_data] = lineStr[ii_data];
                                        }
                                        if (coder::internal::p_strcmp(
                                                c_lineStr)) {
                                          creal_T dc;
                                          text_len = match_idx - i;
                                          c_lineStr.set_size(1, text_len);
                                          for (match_idx = 0;
                                               match_idx < text_len;
                                               match_idx++) {
                                            c_lineStr[match_idx] =
                                                lineStr[i + match_idx];
                                          }
                                          dc = coder::str2double(c_lineStr);
                                          if (!(dc.re > 0.0)) {
                                            c_rtErrorWithMessageID(
                                                b_emlrtRTEI.fName,
                                                b_emlrtRTEI.lineNo);
                                          }
                                          if (!(dc.re < 1.0)) {
                                            rtErrorWithMessageID(
                                                "  1.000000000000000e+00",
                                                qc_emlrtRTEI.fName,
                                                qc_emlrtRTEI.lineNo);
                                          }
                                          Config->contents.falseAlarmProb =
                                              dc.re;
                                        } else {
                                          c_lineStr.set_size(1, text_len);
                                          for (ii_data = 0; ii_data < text_len;
                                               ii_data++) {
                                            c_lineStr[ii_data] =
                                                lineStr[ii_data];
                                          }
                                          if (coder::internal::q_strcmp(
                                                  c_lineStr)) {
                                            text_len = match_idx - i;
                                            _in.Value.set_size(1, text_len);
                                            for (match_idx = 0;
                                                 match_idx < text_len;
                                                 match_idx++) {
                                              _in.Value[match_idx] =
                                                  lineStr[i + match_idx];
                                            }
                                            Config->contents.dataRecordPath =
                                                _in;
                                          } else {
                                            c_lineStr.set_size(1, text_len);
                                            for (ii_data = 0;
                                                 ii_data < text_len;
                                                 ii_data++) {
                                              c_lineStr[ii_data] =
                                                  lineStr[ii_data];
                                            }
                                            if (!coder::internal::r_strcmp(
                                                    c_lineStr)) {
                                              c_lineStr.set_size(1, text_len);
                                              for (ii_data = 0;
                                                   ii_data < text_len;
                                                   ii_data++) {
                                                c_lineStr[ii_data] =
                                                    lineStr[ii_data];
                                              }
                                              if (coder::internal::s_strcmp(
                                                      c_lineStr)) {
                                                // STR2BOOL Converts a string in
                                                // to a boolean.
                                                //    This function converts a
                                                //    string to a boolean
                                                //    output. Valid input
                                                //    strings are '1', '0',
                                                //    'true', or 'false'. The
                                                //    input is case insensitive.
                                                //    If input is invalid, the
                                                //    function returns an empty
                                                //    false of size 0x1.
                                                //
                                                // INPUTS:
                                                //    stringIn    string of '1',
                                                //    '0', 'true', or 'false',
                                                //    case insensitive.
                                                //
                                                // OUTPUTS:
                                                //    boolOut     boolean
                                                //
                                                // Author: Michael W. Shafer
                                                // Date:   2022-06-21
                                                // --------------------------------------------------------------------------
                                                text_len = match_idx - i;
                                                c_lineStr.set_size(1, text_len);
                                                for (match_idx = 0;
                                                     match_idx < text_len;
                                                     match_idx++) {
                                                  c_lineStr[match_idx] =
                                                      lineStr[i + match_idx];
                                                }
                                                coder::lower(c_lineStr,
                                                             lineStr);
                                                b_bool = false;
                                                if ((lineStr.size(1) == 1) &&
                                                    (lineStr[0] == '1')) {
                                                  b_bool = true;
                                                }
                                                if (b_bool) {
                                                  text_len = 1;
                                                  b_bool = true;
                                                } else {
                                                  b_bool = false;
                                                  if ((lineStr.size(1) == 1) &&
                                                      (lineStr[0] == '0')) {
                                                    b_bool = true;
                                                  }
                                                  if (b_bool) {
                                                    text_len = 1;
                                                    b_bool = false;
                                                  } else if (coder::internal::
                                                                 t_strcmp(
                                                                     lineStr)) {
                                                    text_len = 1;
                                                    b_bool = true;
                                                  } else if (coder::internal::
                                                                 u_strcmp(
                                                                     lineStr)) {
                                                    text_len = 1;
                                                    b_bool = false;
                                                  } else {
                                                    text_len = 0;
                                                  }
                                                }
                                                coder::internal::
                                                    b_validator_check_size(
                                                        (const boolean_T
                                                             *)&b_bool,
                                                        text_len);
                                              } else {
                                                c_lineStr.set_size(1, text_len);
                                                for (ii_data = 0;
                                                     ii_data < text_len;
                                                     ii_data++) {
                                                  c_lineStr[ii_data] =
                                                      lineStr[ii_data];
                                                }
                                                if (coder::internal::v_strcmp(
                                                        c_lineStr)) {
                                                  // STR2BOOL Converts a string
                                                  // in to a boolean.
                                                  //    This function converts a
                                                  //    string to a boolean
                                                  //    output. Valid input
                                                  //    strings are '1', '0',
                                                  //    'true', or 'false'. The
                                                  //    input is case
                                                  //    insensitive. If input is
                                                  //    invalid, the function
                                                  //    returns an empty false
                                                  //    of size 0x1.
                                                  //
                                                  // INPUTS:
                                                  //    stringIn    string of
                                                  //    '1', '0', 'true', or
                                                  //    'false', case
                                                  //    insensitive.
                                                  //
                                                  // OUTPUTS:
                                                  //    boolOut     boolean
                                                  //
                                                  // Author: Michael W. Shafer
                                                  // Date:   2022-06-21
                                                  // --------------------------------------------------------------------------
                                                  text_len = match_idx - i;
                                                  c_lineStr.set_size(1,
                                                                     text_len);
                                                  for (match_idx = 0;
                                                       match_idx < text_len;
                                                       match_idx++) {
                                                    c_lineStr[match_idx] =
                                                        lineStr[i + match_idx];
                                                  }
                                                  coder::lower(c_lineStr,
                                                               lineStr);
                                                  b_bool = false;
                                                  if ((lineStr.size(1) == 1) &&
                                                      (lineStr[0] == '1')) {
                                                    b_bool = true;
                                                  }
                                                  if (b_bool) {
                                                    text_len = 1;
                                                    b_bool = true;
                                                  } else {
                                                    b_bool = false;
                                                    if ((lineStr.size(1) ==
                                                         1) &&
                                                        (lineStr[0] == '0')) {
                                                      b_bool = true;
                                                    }
                                                    if (b_bool) {
                                                      text_len = 1;
                                                      b_bool = false;
                                                    } else if (
                                                        coder::internal::
                                                            t_strcmp(lineStr)) {
                                                      text_len = 1;
                                                      b_bool = true;
                                                    } else if (
                                                        coder::internal::
                                                            u_strcmp(lineStr)) {
                                                      text_len = 1;
                                                      b_bool = false;
                                                    } else {
                                                      text_len = 0;
                                                    }
                                                  }
                                                  coder::internal::
                                                      b_validator_check_size(
                                                          (const boolean_T
                                                               *)&b_bool,
                                                          text_len);
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
                  }
                }
              }
            }
          }
          // Stop when we have finished reading this entry.
          if (coder::b_feof(static_cast<double>(fileid)) == 1.0) {
            done = true;
          } else {
            if ((static_cast<int>(static_cast<unsigned int>(configNum) + 1U) <
                 1) ||
                (static_cast<int>(static_cast<unsigned int>(configNum) + 1U) >
                 sepByte.size(1))) {
              rtDynamicBoundsError(
                  static_cast<int>(static_cast<unsigned int>(configNum) + 1U),
                  1, sepByte.size(1), &jb_emlrtBCI);
            }
            if (coder::b_ftell(static_cast<double>(fileid)) ==
                sepByte[static_cast<int>(
                    static_cast<unsigned int>(configNum))]) {
              done = true;
            }
          }
        } else if (coder::b_feof(static_cast<double>(fileid)) == 1.0) {
          done = true;
        } else {
          if ((static_cast<int>(static_cast<unsigned int>(configNum) + 1U) <
               1) ||
              (static_cast<int>(static_cast<unsigned int>(configNum) + 1U) >
               sepByte.size(1))) {
            rtDynamicBoundsError(
                static_cast<int>(static_cast<unsigned int>(configNum) + 1U), 1,
                sepByte.size(1), &ob_emlrtBCI);
          }
          if (coder::b_ftell(static_cast<double>(fileid)) ==
              sepByte[static_cast<int>(static_cast<unsigned int>(configNum))]) {
            done = true;
          }
        }
      } else {
        exitg1 = 1;
      }
    } while (exitg1 == 0);
    coder::cfclose(static_cast<double>(fileid));
  }
  // Do we update the tip and tipu or use the ones that were adapted from
  // the previous detections? Probably just use the file. The supervisor
  // will have access to the detected pulses and can update these values if
  // it sees fit.
}

//
// UNTITLED Summary of this function goes here
//    Detailed explanation goes here
//
// Arguments    : void
// Return Type  : void
//
void uavrt_detection()
{
  static coder::dsp::AsyncBuffer asyncDataBuff;
  static coder::dsp::b_AsyncBuffer asyncTimeBuff;
  static rtBoundsCheckInfo eb_emlrtBCI{
      -1,                                              // iFirst
      -1,                                              // iLast
      199,                                             // lineNo
      32,                                              // colNo
      "t",                                             // aName
      "uavrt_detection",                               // fName
      "H:\\repos\\uavrt_detection\\uavrt_detection.m", // pName
      0                                                // checkKind
  };
  static rtBoundsCheckInfo fb_emlrtBCI{
      -1,                                              // iFirst
      -1,                                              // iLast
      352,                                             // lineNo
      53,                                              // colNo
      "ps_pre_struc.pl",                               // aName
      "uavrt_detection",                               // fName
      "H:\\repos\\uavrt_detection\\uavrt_detection.m", // pName
      0                                                // checkKind
  };
  static rtRunTimeErrorInfo qc_emlrtRTEI{
      10,             // lineNo
      "mustBeInteger" // fName
  };
  DetectorConfig *obj;
  b_waveform X;
  coder::b_captured_var Config;
  coder::c_captured_var overlapSamples;
  coder::c_captured_var sampsForKPulses;
  coder::c_captured_var stftOverlapFraction;
  coder::captured_var configPath;
  pulsestats lobj_10[4];
  pulsestats lobj_19[2];
  pulsestats lobj_13;
  pulsestats lobj_15;
  pulsestats lobj_16;
  pulsestats *pulseStatsPriori;
  threshold val;
  waveform b_X;
  waveform lobj_11;
  waveform lobj_18;
  waveform *Xhold;
  wfmstft lobj_17[3];
  wfmstft lobj_12;
  wfmstft lobj_14;
  wfmstft lobj_9;
  coder::array<c_struct_T, 2U> ps_pre_struc_clst;
  coder::array<c_struct_T, 2U> ps_pre_struc_pl;
  coder::array<creal32_T, 1U> x;
  coder::array<double, 2U> ps_pre_struc_cpki;
  coder::array<double, 1U> r1;
  coder::array<double, 1U> t;
  coder::array<char, 2U> d_varargin_1;
  coder::array<boolean_T, 2U> b_varargin_1;
  coder::array<boolean_T, 2U> c_varargin_1;
  coder::array<boolean_T, 2U> ps_pre_struc_cmsk;
  coder::array<boolean_T, 1U> b_tmp_data;
  coder::array<boolean_T, 1U> r2;
  c_struct_T b_expl_temp;
  c_struct_T expl_temp;
  c_struct_T r;
  creal_T dcv[1000];
  creal32_T exampleData[1000];
  double ps_pre_struc_tmplt[2];
  double integratedTimeError;
  double segmentsProcessed;
  double t9_P;
  double t9_SNR;
  double t9_fend;
  double t9_fp;
  double t9_fstart;
  double t9_t_0;
  double t9_t_f;
  double t9_yw;
  double timeStamp;
  double trackedCount;
  int i;
  int udpReceiver;
  int udpSender;
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
  configPath.contents.init();
  // Must exist in the same directory as the execution of this executable
  Config.contents.init();
  // Build empty config object
  updateconfig(&Config, &configPath);
  // Update (fill) the configuration
  configUpdatedFlag = true;
  makepulsestruc(&r.A, &r.P, &r.SNR, &r.yw, &r.t_0, &r.t_f, r.t_next, &r.fp,
                 &r.fstart, &r.fend, r.mode, &r.det_dec, &r.con_dec);
  makepulsestruc(&integratedTimeError, &t9_P, &t9_SNR, &t9_yw, &t9_t_0, &t9_t_f,
                 expl_temp.t_next, &t9_fp, &t9_fstart, &t9_fend, expl_temp.mode,
                 &t9_det_dec, &t9_con_dec);
  expl_temp.con_dec = t9_con_dec;
  expl_temp.det_dec = t9_det_dec;
  expl_temp.fend = t9_fend;
  expl_temp.fstart = t9_fstart;
  expl_temp.fp = t9_fp;
  expl_temp.t_f = t9_t_f;
  expl_temp.t_0 = t9_t_0;
  expl_temp.yw = t9_yw;
  expl_temp.SNR = t9_SNR;
  expl_temp.P = t9_P;
  expl_temp.A = integratedTimeError;
  pulseStatsPriori = lobj_19[1].init(Config.contents.tp, Config.contents.tip,
                                     Config.contents.tipu, Config.contents.tipj,
                                     &r, &expl_temp);
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
  // data at 4ksps. asyncWriteBuff                = dsp.AsyncBuffer(600650);
  // %600650 is the result of the nominal settings of ceil(150/(1024/4000)*1025.
  // asyncWriteBuff.write(single(1+1i));%Write to give Code the type. Read to
  // remove data. asyncWriteBuff.read();
  fileid = coder::cfopen(Config.contents.dataRecordPath.Value);
  if (fileid == -1) {
    printf("UAV-RT: Error opening/creating data record file with error:\n");
    fflush(stdout);
  }
  printf("Startup set 3 complete. \n");
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
  printf("Startup set 4 complete. \n");
  fflush(stdout);
  t9_SNR = 0.0;
  t9_yw = 0.0;
  t9_t_0 = 0.0;
  t9_t_f = 0.0;
  t9_fp = 0.0;
  t9_fstart = 0.0;
  t9_fend = 0.0;
  ps_pre_struc_tmplt[0] = 1.0;
  ps_pre_struc_tmplt[1] = 1.0;
  makepulsestruc(&r.A, &r.P, &r.SNR, &r.yw, &r.t_0, &r.t_f, r.t_next, &r.fp,
                 &r.fstart, &r.fend, r.mode, &r.det_dec, &r.con_dec);
  ps_pre_struc_pl.set_size(1, 1);
  ps_pre_struc_pl[0] = r;
  makepulsestruc(&r.A, &r.P, &r.SNR, &r.yw, &r.t_0, &r.t_f, r.t_next, &r.fp,
                 &r.fstart, &r.fend, r.mode, &r.det_dec, &r.con_dec);
  ps_pre_struc_clst.set_size(1, 1);
  ps_pre_struc_clst[0] = r;
  ps_pre_struc_cmsk.set_size(1, 1);
  ps_pre_struc_cmsk[0] = false;
  ps_pre_struc_cpki.set_size(1, 1);
  ps_pre_struc_cpki[0] = rtNaN;
  printf("Startup set 5 complete. \n");
  fflush(stdout);
  //  Preallocate X and Xhold so that coder knows the data types.
  coder::wgn(dcv);
  for (i = 0; i < 1000; i++) {
    exampleData[i].re = static_cast<float>(dcv[i].re);
    exampleData[i].im = static_cast<float>(dcv[i].im);
  }
  integratedTimeError = Config.contents.falseAlarmProb;
  // UNTITLED2 Construct an instance of this class
  //    Detailed explanation goes here
  val.pf = integratedTimeError;
  val.evMuParam = 0.0;
  val.evSigmaParam = 0.0;
  val.threshVecFine.set_size(1);
  val.threshVecFine[0] = 0.0;
  Xhold = lobj_18.init(exampleData, Config.contents.Fs, pulseStatsPriori, &val);
  // UNTITLED2 Construct an instance of this class
  //    Detailed explanation goes here
  X.init(exampleData, Config.contents.Fs, pulseStatsPriori, &lobj_19[0],
         &lobj_17[2]);
  Xhold->spectro(&lobj_17[1]);
  X.spectro(&lobj_17[0]);
  printf("Startup set 6 complete. \n");
  fflush(stdout);
  udpReceiver = udpReceiverSetup(Config.contents.portData);
  if (udpReceiver <= 0) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  udpSender = udpSenderSetup(30000.0);
  if (udpSender <= 0) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  // Initialize loop variables
  resetBuffersFlag = true;
  segmentsProcessed = 0.0;
  suggestedMode = 'S';
  fLock = false;
  staleDataFlag = true;
  // Force buffer  flush on start
  timeStamp = 0.0;
  cleanBuffer = true;
  trackedCount = 0.0;
  printf("Startup set 7 complete. Starting processing... \n");
  fflush(stdout);
  while (1) {
    creal32_T complexBuffer[4096];
    double timeVector[4096];
    int n;
    int qY;
    // i <= maxInd
    if (resetBuffersFlag) {
      asyncDataBuff.reset();
      asyncTimeBuff.reset();
      resetBuffersFlag = false;
      cleanBuffer = true;
    }
    //             %% Flush UDP buffer if data in the buffer is stale.
    if (staleDataFlag) {
      printf("********STALE DATA FLAG: %u *********\n", 1U);
      fflush(stdout);
      udpReceiverClear(udpReceiver);
      staleDataFlag = false;
    }
    //             %% Get data
    udpReceiverRead(udpReceiver, &complexBuffer[0], 4096.0);
    //             %% Wait for new data if none ready, else put data in buffers
    integratedTimeError = 1.0 / Config.contents.Fs;
    for (i = 0; i < 4096; i++) {
      timeVector[i] = timeStamp + integratedTimeError * static_cast<double>(i);
    }
    timeStamp += 4096.0 / Config.contents.Fs;
    // Write out data and time.
    asyncDataBuff.write(complexBuffer);
    asyncTimeBuff.write(timeVector);
    // asyncWriteBuff.write(dataReceived);
    // if asyncWriteBuff.NumUnreadSamples == dataWriterSamples
    //     dataWriterBuffData = asyncWriteBuff.read();
    //     %dataWriterBuffDataComplexInterleave = [real(dataWriterBuffData),
    //     imag(dataWriterBuffData)].';
    //     [~] =
    //     fwrite(dataWriterFileID,interleaveComplexVector(dataWriterBuffData),'single');
    // end
    //                 %% Process data if there is enough in the buffers
    if ((asyncDataBuff.pBuffer.WritePointer >= 0) &&
        (asyncDataBuff.pBuffer.ReadPointer <
         asyncDataBuff.pBuffer.WritePointer - MAX_int32_T)) {
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
    if (asyncDataBuff.pBuffer.ReadPointer < -2147434027) {
      qY = MAX_int32_T;
    } else {
      qY = 49620 - asyncDataBuff.pBuffer.ReadPointer;
    }
    if ((qY < 0) && (asyncDataBuff.pBuffer.WritePointer < MIN_int32_T - qY)) {
      qY = MIN_int32_T;
    } else if ((qY > 0) &&
               (asyncDataBuff.pBuffer.WritePointer > MAX_int32_T - qY)) {
      qY = MAX_int32_T;
    } else {
      qY += asyncDataBuff.pBuffer.WritePointer;
    }
    if (asyncDataBuff.pBuffer.ReadPointer <
        asyncDataBuff.pBuffer.WritePointer) {
      qY = n;
    } else if (asyncDataBuff.pBuffer.ReadPointer ==
               asyncDataBuff.pBuffer.WritePointer) {
      qY = 49620;
    }
    if (qY >= sampsForKPulses.contents + overlapSamples.contents) {
      unsigned int varargin_1;
      unsigned int varargin_2;
      t9_P = std::round(sampsForKPulses.contents);
      if (t9_P < 4.294967296E+9) {
        if (t9_P >= 0.0) {
          varargin_1 = static_cast<unsigned int>(t9_P);
        } else {
          varargin_1 = 0U;
        }
      } else if (t9_P >= 4.294967296E+9) {
        varargin_1 = MAX_uint32_T;
      } else {
        varargin_1 = 0U;
      }
      t9_P = std::round(overlapSamples.contents);
      if (t9_P < 4.294967296E+9) {
        if (t9_P >= 0.0) {
          varargin_2 = static_cast<unsigned int>(t9_P);
        } else {
          varargin_2 = 0U;
        }
      } else if (t9_P >= 4.294967296E+9) {
        varargin_2 = MAX_uint32_T;
      } else {
        varargin_2 = 0U;
      }
      printf("Buffer Full|| sampsForKPulses: %u, overlapSamples: %u,\n",
             varargin_1, varargin_2);
      fflush(stdout);
      if ((asyncDataBuff.pBuffer.WritePointer >= 0) &&
          (asyncDataBuff.pBuffer.ReadPointer <
           asyncDataBuff.pBuffer.WritePointer - MAX_int32_T)) {
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
      if (asyncDataBuff.pBuffer.ReadPointer < -2147434027) {
        qY = MAX_int32_T;
      } else {
        qY = 49620 - asyncDataBuff.pBuffer.ReadPointer;
      }
      if ((qY < 0) && (asyncDataBuff.pBuffer.WritePointer < MIN_int32_T - qY)) {
        qY = MIN_int32_T;
      } else if ((qY > 0) &&
                 (asyncDataBuff.pBuffer.WritePointer > MAX_int32_T - qY)) {
        qY = MAX_int32_T;
      } else {
        qY += asyncDataBuff.pBuffer.WritePointer;
      }
      if (asyncDataBuff.pBuffer.ReadPointer <
          asyncDataBuff.pBuffer.WritePointer) {
        qY = n;
      } else if (asyncDataBuff.pBuffer.ReadPointer ==
                 asyncDataBuff.pBuffer.WritePointer) {
        qY = 49620;
      }
      printf("Running...Buffer full with %d samples. Processing. \n", qY);
      fflush(stdout);
      coder::tic();
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
      // Check the timestamps in the buffer for gaps larger
      // than the max interpulse uncertainty. If there are
      // enough dropped packets such that the time is shifted
      // by more than the interpulse uncertainty, then the
      // detection will likely fail or produces bad results. In
      // this case. Skip the processing and clear the buffer.
      coder::diff(t, r1);
      qY = r1.size(0);
      for (i = 0; i < qY; i++) {
        r1[i] = r1[i] - integratedTimeError;
      }
      integratedTimeError = coder::sum(r1);
      if ((Config.contents.K > 1.0) &&
          (integratedTimeError > Config.contents.tipu + Config.contents.tipj)) {
        printf("Significant time differences found in timestamp record. "
               "Skipping processing and clearing buffers.\n");
        fflush(stdout);
        resetBuffersFlag = true;
        staleDataFlag = true;
      } else {
        unsigned int validatedHoleFilling[3];
        unsigned int varargin_3;
        if (t.size(0) < 1) {
          rtDynamicBoundsError(1, 1, t.size(0), &eb_emlrtBCI);
        }
        printf("Running...Building priori and waveform. \n");
        fflush(stdout);
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
          makepulsestruc(&r.A, &r.P, &r.SNR, &r.yw, &r.t_0, &r.t_f, r.t_next,
                         &r.fp, &r.fstart, &r.fend, r.mode, &r.det_dec,
                         &r.con_dec);
          makepulsestruc(&integratedTimeError, &t9_P, &t9_SNR, &t9_yw, &t9_t_0,
                         &t9_t_f, expl_temp.t_next, &t9_fp, &t9_fstart,
                         &t9_fend, expl_temp.mode, &t9_det_dec, &t9_con_dec);
          b_expl_temp.con_dec = t9_con_dec;
          b_expl_temp.det_dec = t9_det_dec;
          b_expl_temp.mode.set_size(1, expl_temp.mode.size(1));
          qY = expl_temp.mode.size(1);
          for (i = 0; i < qY; i++) {
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
          b_expl_temp.SNR = t9_SNR;
          b_expl_temp.P = t9_P;
          b_expl_temp.A = integratedTimeError;
          pulseStatsPriori = lobj_13.init(
              Config.contents.tp, Config.contents.tip, Config.contents.tipu,
              Config.contents.tipj,
              1.0E-5 * std::abs(Config.contents.tagFreqMHz -
                                Config.contents.channelCenterFreqMHz),
              &r, &b_expl_temp);
          configUpdatedFlag = false;
        } else {
          pulseStatsPriori = lobj_16.c_init(
              t9_SNR, t9_yw, t9_t_0, t9_t_f, t9_fp, t9_fstart, t9_fend,
              ps_pre_struc_tmplt, (char *)&mode, ps_pre_struc_pl,
              ps_pre_struc_clst, ps_pre_struc_cmsk, ps_pre_struc_cpki);
        }
        //                         %% PRIMARY PROCESSING BLOCK
        // Prep waveform for processing/detection
        integratedTimeError = Config.contents.falseAlarmProb;
        // UNTITLED2 Construct an instance of this class
        //    Detailed explanation goes here
        val.pf = integratedTimeError;
        val.evMuParam = 0.0;
        val.evSigmaParam = 0.0;
        val.threshVecFine.set_size(1);
        val.threshVecFine[0] = 0.0;
        b_X.init(x, Config.contents.Fs, t[0], pulseStatsPriori, &val, &lobj_15,
                 &lobj_14);
        b_X.K = Config.contents.K;
        t9_P = std::round(b_X.N);
        if (t9_P < 4.294967296E+9) {
          if (t9_P >= 0.0) {
            varargin_1 = static_cast<unsigned int>(t9_P);
          } else {
            varargin_1 = 0U;
          }
        } else if (t9_P >= 4.294967296E+9) {
          varargin_1 = MAX_uint32_T;
        } else {
          varargin_1 = 0U;
        }
        t9_P = std::round(b_X.M);
        if (t9_P < 4.294967296E+9) {
          if (t9_P >= 0.0) {
            varargin_2 = static_cast<unsigned int>(t9_P);
          } else {
            varargin_2 = 0U;
          }
        } else if (t9_P >= 4.294967296E+9) {
          varargin_2 = MAX_uint32_T;
        } else {
          varargin_2 = 0U;
        }
        t9_P = std::round(b_X.J);
        if (t9_P < 4.294967296E+9) {
          if (t9_P >= 0.0) {
            varargin_3 = static_cast<unsigned int>(t9_P);
          } else {
            varargin_3 = 0U;
          }
        } else if (t9_P >= 4.294967296E+9) {
          varargin_3 = MAX_uint32_T;
        } else {
          varargin_3 = 0U;
        }
        coder::internal::validate_print_arguments(
            varargin_1, varargin_2, varargin_3, validatedHoleFilling);
        printf("Current interpulse params || N: %u, M: %u, J: %u,\n",
               validatedHoleFilling[0], validatedHoleFilling[1],
               validatedHoleFilling[2]);
        fflush(stdout);
        b_X.setprioridependentprops(b_X.ps_pre);
        varargin_1 = static_cast<unsigned int>(b_X.x.size(1));
        printf("Samples in waveform: %u \n", varargin_1);
        fflush(stdout);
        coder::tic();
        printf("Computing STFT...");
        fflush(stdout);
        b_X.spectro(&lobj_12);
        t9_P = coder::toc();
        printf("complete. Elapsed time: %f seconds \n", t9_P);
        fflush(stdout);
        printf("Building weighting matrix and generating thresholds...");
        fflush(stdout);
        coder::tic();
        b_X.setweightingmatrix();
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
          printf("UAV-RT: Unsupported mode requested. Defaulting to Discovery "
                 "(D) mode.");
          fflush(stdout);
          mode = 'D';
          break;
        }
        if (coder::internal::b_strcmp(&Config.contents.opMode)) {
          mode = 'D';
        }
        if (segmentsProcessed == 0.0) {
          val = b_X.thresh;
          val.makenewthreshold(&b_X);
          b_X.thresh = val;
        } else {
          val = b_X.thresh;
          val.setthreshold(&b_X, Xhold);
          b_X.thresh = val;
        }
        t9_P = coder::toc();
        printf("complete. Elapsed time: %f seconds \n", t9_P);
        fflush(stdout);
        varargin_1 = static_cast<unsigned int>(b_X.stft->S.size(1));
        printf("Time windows in S: %u \n", varargin_1);
        fflush(stdout);
        printf("Finding pulses...");
        fflush(stdout);
        b_X.process(mode, Config.contents.excldFreqs);
        integratedTimeError = coder::toc();
        t9_P = coder::toc();
        printf("complete. Elapsed time: %f seconds \n", t9_P);
        fflush(stdout);
        //                         %% PREP FOR NEXT LOOP
        // Latch/Release the frequency lock and setup the
        // suggested mode
        suggestedMode = b_X.ps_pos->mode;
        ps_pre_struc_pl.set_size(1, b_X.ps_pos->pl.size(1));
        qY = b_X.ps_pos->pl.size(0) * b_X.ps_pos->pl.size(1) - 1;
        for (i = 0; i <= qY; i++) {
          ps_pre_struc_pl[i] = b_X.ps_pos->pl[i];
        }
        n = ps_pre_struc_pl.size(1);
        if (ps_pre_struc_pl.size(1) == 0) {
          i = 0;
        } else {
          i = ps_pre_struc_pl.size(1);
        }
        b_varargin_1.set_size(1, i);
        if (ps_pre_struc_pl.size(1) > 2147483646) {
          coder::check_forloop_overflow_error();
        }
        for (qY = 0; qY < n; qY++) {
          b_varargin_1[qY] = ps_pre_struc_pl[qY].con_dec;
        }
        if (b_varargin_1.size(1) != 0) {
          n = b_varargin_1.size(1);
        } else {
          n = 0;
        }
        c_varargin_1 = b_varargin_1.reshape(1, n);
        coder::all(c_varargin_1, r2);
        if (coder::internal::ifWhileCond(r2)) {
          // Check if all were confirmed
          fLock = true;
        }
        // We only ever release if we are in softlock mode and
        // only do so in that case if we are no longer confirming
        // pulses.
        if (coder::internal::c_strcmp(&Config.contents.opMode)) {
          n = r2.size(0);
          qY = r2.size(0);
          for (i = 0; i < qY; i++) {
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
          qY = b_X.ps_pos->pl.size(0) * b_X.ps_pos->pl.size(1) - 1;
          for (i = 0; i <= qY; i++) {
            ps_pre_struc_pl[i] = b_X.ps_pos->pl[i];
          }
          b_X.ps_pos->updateposteriori(b_X.ps_pre, ps_pre_struc_pl);
          if (trackedCount > 5.0) {
            trackedCount = 0.0;
            ps_pre_struc_pl.set_size(1, b_X.ps_pos->pl.size(1));
            qY = b_X.ps_pos->pl.size(0) * b_X.ps_pos->pl.size(1) - 1;
            for (i = 0; i <= qY; i++) {
              ps_pre_struc_pl[i] = b_X.ps_pos->pl[i];
            }
            b_X.ps_pos->b_updateposteriori(b_X.ps_pre, ps_pre_struc_pl);
          }
        }
        // Check lagging processing
        if ((segmentsProcessed != 0.0) && (Config.contents.K > 1.0) &&
            (integratedTimeError >
             0.9 * sampsForKPulses.contents / Config.contents.Fs)) {
          obj = &Config.contents;
          integratedTimeError = Config.contents.K - 1.0;
          if (!(integratedTimeError > 0.0)) {
            c_rtErrorWithMessageID(b_emlrtRTEI.fName, b_emlrtRTEI.lineNo);
          }
          if (std::isinf(integratedTimeError) ||
              (!(integratedTimeError == std::floor(integratedTimeError)))) {
            i_rtErrorWithMessageID(qc_emlrtRTEI.fName, qc_emlrtRTEI.lineNo);
          }
          obj->K = integratedTimeError;
          t9_P = std::round(Config.contents.K);
          if (t9_P < 4.294967296E+9) {
            if (t9_P >= 0.0) {
              varargin_1 = static_cast<unsigned int>(t9_P);
            } else {
              varargin_1 = 0U;
            }
          } else if (t9_P >= 4.294967296E+9) {
            varargin_1 = MAX_uint32_T;
          } else {
            varargin_1 = 0U;
          }
          printf("WARNING!!! PROCESSING TIME TOOK LONGER THAN WAVEFORM LENGTH. "
                 "STREAMING NOT POSSIBLE. REDUCING NUMBER OF PULSES CONSIDERED "
                 "BY 1 T"
                 "O K = %u \n",
                 varargin_1);
          fflush(stdout);
          printf("Resetting all internal data buffers and udp buffers to clear "
                 "potential stale data. \n");
          fflush(stdout);
          resetBuffersFlag = true;
          staleDataFlag = true;
          suggestedMode = 'S';
        }
        segmentsProcessed++;
        coder::tic();
        // Prepare priori for next segment
        printf("Updating priori...\n");
        fflush(stdout);
        t9_SNR = b_X.ps_pos->t_p;
        t9_yw = b_X.ps_pos->t_ip;
        t9_t_0 = b_X.ps_pos->t_ipu;
        t9_t_f = b_X.ps_pos->t_ipj;
        t9_fp = b_X.ps_pos->fp;
        t9_fstart = b_X.ps_pos->fstart;
        t9_fend = b_X.ps_pos->fend;
        ps_pre_struc_tmplt[0] = b_X.ps_pos->tmplt[0];
        ps_pre_struc_tmplt[1] = b_X.ps_pos->tmplt[1];
        mode = b_X.ps_pos->mode;
        ps_pre_struc_pl.set_size(1, b_X.ps_pos->pl.size(1));
        qY = b_X.ps_pos->pl.size(1);
        for (i = 0; i < qY; i++) {
          ps_pre_struc_pl[i] = b_X.ps_pos->pl[i];
        }
        ps_pre_struc_clst.set_size(b_X.ps_pos->clst.size(0),
                                   b_X.ps_pos->clst.size(1));
        qY = b_X.ps_pos->clst.size(0) * b_X.ps_pos->clst.size(1);
        for (i = 0; i < qY; i++) {
          ps_pre_struc_clst[i] = b_X.ps_pos->clst[i];
        }
        ps_pre_struc_cmsk.set_size(b_X.ps_pos->cmsk.size(0),
                                   b_X.ps_pos->cmsk.size(1));
        qY = b_X.ps_pos->cmsk.size(0) * b_X.ps_pos->cmsk.size(1);
        for (i = 0; i < qY; i++) {
          ps_pre_struc_cmsk[i] = b_X.ps_pos->cmsk[i];
        }
        ps_pre_struc_cpki.set_size(b_X.ps_pos->cpki.size(0),
                                   b_X.ps_pos->cpki.size(1));
        qY = b_X.ps_pos->cpki.size(0) * b_X.ps_pos->cpki.size(1);
        for (i = 0; i < qY; i++) {
          ps_pre_struc_cpki[i] = b_X.ps_pos->cpki[i];
        }
        updatebufferreadvariables(&Config, &stftOverlapFraction,
                                  &overlapSamples, &sampsForKPulses,
                                  b_X.ps_pos);
        t9_P = coder::toc();
        printf("complete. Elapsed time: %f seconds \n", t9_P);
        fflush(stdout);
        // Deal with detected pulses
        // Xhold{mod(segmentsProcessed,maxSegments)} = X;%Keep a maxSegments
        // running record of waveforms for debugging in Matlab Xstruct =
        // obj2structrecursive(X); Xhold = X;
        Xhold = waveformcopy(&b_X, &lobj_9, &lobj_10[0], &lobj_11);
        i = ps_pre_struc_pl.size(1);
        for (qY = 0; qY < i; qY++) {
          double pulseInfo[3];
          if (qY + 1 > ps_pre_struc_pl.size(1)) {
            rtDynamicBoundsError(qY + 1, 1, ps_pre_struc_pl.size(1),
                                 &fb_emlrtBCI);
          }
          printf("Pulse at %e Hz detected. SNR: %e Confirmation status: %u \n",
                 ps_pre_struc_pl[qY].fp, ps_pre_struc_pl[qY].SNR,
                 static_cast<unsigned int>(ps_pre_struc_pl[qY].con_dec));
          fflush(stdout);
          pulseInfo[0] = ps_pre_struc_pl[qY].SNR;
          pulseInfo[1] = ps_pre_struc_pl[qY].con_dec;
          pulseInfo[2] = ps_pre_struc_pl[qY].t_0;
          udpSenderSend(udpSender, &pulseInfo[0]);
        }
        d_varargin_1.set_size(1, 2);
        d_varargin_1[0] = mode;
        d_varargin_1[1] = '\x00';
        printf("Current Mode: %s\n", &d_varargin_1[0]);
        fflush(stdout);
        printf("====================================\n");
        fflush(stdout);
      }
    }
  }
}

//
// File trailer for uavrt_detection.cpp
//
// [EOF]
//
