//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: uavrt_detection.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 14:31:55
//

// Include Files
#include "uavrt_detection.h"
#include "AsyncBuffer.h"
#include "AsyncBuffercgHelper.h"
#include "DetectorConfig.h"
#include "datetime.h"
#include "diff.h"
#include "eml_int_forloop_overflow_check.h"
#include "fgetl.h"
#include "fileManager.h"
#include "find.h"
#include "fseek.h"
#include "ftell.h"
#include "fwrite.h"
#include "horzcatStructList.h"
#include "indexShapeCheck.h"
#include "makepulsestruc.h"
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
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <stdio.h>
#include <string.h>
#include <string>

// Type Definitions
struct emxArray_creal32_T_1 {
  creal32_T data[1];
  int size[1];
};

// Function Declarations
static void c_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void e_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void f_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void interleaveComplexVector(const creal32_T complexDataIn_data[],
                                    int complexDataIn_size,
                                    float interleaveDataOut_data[],
                                    int *interleaveDataOut_size);

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
static void c_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
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
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void e_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
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
static void f_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
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
// Arguments    : const creal32_T complexDataIn_data[]
//                int complexDataIn_size
//                float interleaveDataOut_data[]
//                int *interleaveDataOut_size
// Return Type  : void
//
static void interleaveComplexVector(const creal32_T complexDataIn_data[],
                                    int complexDataIn_size,
                                    float interleaveDataOut_data[],
                                    int *interleaveDataOut_size)
{
  float dataMatrix_data[2];
  float varargin_1_data;
  float varargin_2_data;
  // Enforce column vector
  for (int i{0}; i < complexDataIn_size; i++) {
    varargin_1_data = complexDataIn_data[0].re;
  }
  for (int i{0}; i < complexDataIn_size; i++) {
    varargin_2_data = complexDataIn_data[0].im;
  }
  if (complexDataIn_size - 1 >= 0) {
    dataMatrix_data[0] = varargin_1_data;
    dataMatrix_data[1] = varargin_2_data;
  }
  *interleaveDataOut_size = complexDataIn_size << 1;
  if (*interleaveDataOut_size - 1 >= 0) {
    std::copy(&dataMatrix_data[0], &dataMatrix_data[*interleaveDataOut_size],
              &interleaveDataOut_data[0]);
  }
  // Interleave
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
  static rtBoundsCheckInfo f_emlrtBCI{
      -1,                                             // iFirst
      -1,                                             // iLast
      124,                                            // lineNo
      28,                                             // colNo
      "rawLine",                                      // aName
      "DetectorConfig/setFromFile",                   // fName
      "H:\\repos\\uavrt_detection\\DetectorConfig.m", // pName
      0                                               // checkKind
  };
  static rtBoundsCheckInfo g_emlrtBCI{
      -1,                                             // iFirst
      -1,                                             // iLast
      155,                                            // lineNo
      31,                                             // colNo
      "sepByte",                                      // aName
      "DetectorConfig/setFromFile",                   // fName
      "H:\\repos\\uavrt_detection\\DetectorConfig.m", // pName
      0                                               // checkKind
  };
  static rtBoundsCheckInfo h_emlrtBCI{
      -1,                                             // iFirst
      -1,                                             // iLast
      159,                                            // lineNo
      28,                                             // colNo
      "lineStr",                                      // aName
      "DetectorConfig/setFromFile",                   // fName
      "H:\\repos\\uavrt_detection\\DetectorConfig.m", // pName
      0                                               // checkKind
  };
  static rtBoundsCheckInfo i_emlrtBCI{
      -1,                                             // iFirst
      -1,                                             // iLast
      162,                                            // lineNo
      55,                                             // colNo
      "tabLocs",                                      // aName
      "DetectorConfig/setFromFile",                   // fName
      "H:\\repos\\uavrt_detection\\DetectorConfig.m", // pName
      0                                               // checkKind
  };
  static rtBoundsCheckInfo j_emlrtBCI{
      -1,                                             // iFirst
      -1,                                             // iLast
      163,                                            // lineNo
      63,                                             // colNo
      "colonLocation",                                // aName
      "DetectorConfig/setFromFile",                   // fName
      "H:\\repos\\uavrt_detection\\DetectorConfig.m", // pName
      0                                               // checkKind
  };
  static rtBoundsCheckInfo k_emlrtBCI{
      -1,                                             // iFirst
      -1,                                             // iLast
      200,                                            // lineNo
      69,                                             // colNo
      "sepByte",                                      // aName
      "DetectorConfig/setFromFile",                   // fName
      "H:\\repos\\uavrt_detection\\DetectorConfig.m", // pName
      0                                               // checkKind
  };
  static rtBoundsCheckInfo l_emlrtBCI{
      -1,                                             // iFirst
      -1,                                             // iLast
      164,                                            // lineNo
      47,                                             // colNo
      "lineStr",                                      // aName
      "DetectorConfig/setFromFile",                   // fName
      "H:\\repos\\uavrt_detection\\DetectorConfig.m", // pName
      0                                               // checkKind
  };
  static rtBoundsCheckInfo m_emlrtBCI{
      -1,                                             // iFirst
      -1,                                             // iLast
      164,                                            // lineNo
      74,                                             // colNo
      "lineStr",                                      // aName
      "DetectorConfig/setFromFile",                   // fName
      "H:\\repos\\uavrt_detection\\DetectorConfig.m", // pName
      0                                               // checkKind
  };
  static rtBoundsCheckInfo n_emlrtBCI{
      -1,                                             // iFirst
      -1,                                             // iLast
      163,                                            // lineNo
      47,                                             // colNo
      "lineStr",                                      // aName
      "DetectorConfig/setFromFile",                   // fName
      "H:\\repos\\uavrt_detection\\DetectorConfig.m", // pName
      0                                               // checkKind
  };
  static rtBoundsCheckInfo o_emlrtBCI{
      -1,                                             // iFirst
      -1,                                             // iLast
      163,                                            // lineNo
      49,                                             // colNo
      "lineStr",                                      // aName
      "DetectorConfig/setFromFile",                   // fName
      "H:\\repos\\uavrt_detection\\DetectorConfig.m", // pName
      0                                               // checkKind
  };
  static rtBoundsCheckInfo p_emlrtBCI{
      -1,                                             // iFirst
      -1,                                             // iLast
      202,                                            // lineNo
      69,                                             // colNo
      "sepByte",                                      // aName
      "DetectorConfig/setFromFile",                   // fName
      "H:\\repos\\uavrt_detection\\DetectorConfig.m", // pName
      0                                               // checkKind
  };
  static rtRunTimeErrorInfo kb_emlrtRTEI{
      37,     // lineNo
      "fopen" // fName
  };
  static rtRunTimeErrorInfo lb_emlrtRTEI{
      10,              // lineNo
      "mustBePositive" // fName
  };
  static rtRunTimeErrorInfo mb_emlrtRTEI{
      10,                 // lineNo
      "mustBeNonnegative" // fName
  };
  static rtRunTimeErrorInfo nb_emlrtRTEI{
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
    c_rtErrorWithMessageID(kb_emlrtRTEI.fName, kb_emlrtRTEI.lineNo);
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
      rtDynamicBoundsError(1, 1, lineStr.size(1), &f_emlrtBCI);
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
      d_rtErrorWithMessageID(c_emlrtRTEI.fName, c_emlrtRTEI.lineNo);
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
                         &g_emlrtBCI);
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
        rtDynamicBoundsError(1, 1, lineStr.size(1), &h_emlrtBCI);
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
          rtDynamicBoundsError(1, 1, tabLocs.size(1), &i_emlrtBCI);
        }
        // note regexp is not supported for code generation
        if (ii_size[1] < 1) {
          rtDynamicBoundsError(1, 1, ii_size[1], &j_emlrtBCI);
        }
        if (static_cast<double>(ii_data) - 1.0 < 1.0) {
          match_idx = 0;
        } else {
          if (lineStr.size(1) < 1) {
            rtDynamicBoundsError(1, 1, lineStr.size(1), &n_emlrtBCI);
          }
          if ((ii_data - 1 < 1) || (ii_data - 1 > lineStr.size(1))) {
            rtDynamicBoundsError(ii_data - 1, 1, lineStr.size(1), &o_emlrtBCI);
          }
          match_idx = ii_data - 1;
        }
        if (tabLocs[0] + 1U > static_cast<unsigned int>(lineStr.size(1))) {
          i = 0;
          ii_data = 0;
        } else {
          i = static_cast<int>(tabLocs[0] + 1U);
          if ((i < 1) || (i > lineStr.size(1))) {
            rtDynamicBoundsError(i, 1, lineStr.size(1), &l_emlrtBCI);
          }
          i--;
          if (lineStr.size(1) < 1) {
            rtDynamicBoundsError(lineStr.size(1), 1, lineStr.size(1),
                                 &m_emlrtBCI);
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
            e_rtErrorWithMessageID(lb_emlrtRTEI.fName, lb_emlrtRTEI.lineNo);
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
              f_rtErrorWithMessageID(mb_emlrtRTEI.fName, mb_emlrtRTEI.lineNo);
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
                  e_rtErrorWithMessageID(lb_emlrtRTEI.fName,
                                         lb_emlrtRTEI.lineNo);
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
                    e_rtErrorWithMessageID(lb_emlrtRTEI.fName,
                                           lb_emlrtRTEI.lineNo);
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
                        e_rtErrorWithMessageID(lb_emlrtRTEI.fName,
                                               lb_emlrtRTEI.lineNo);
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
                          e_rtErrorWithMessageID(lb_emlrtRTEI.fName,
                                                 lb_emlrtRTEI.lineNo);
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
                            f_rtErrorWithMessageID(mb_emlrtRTEI.fName,
                                                   mb_emlrtRTEI.lineNo);
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
                              f_rtErrorWithMessageID(mb_emlrtRTEI.fName,
                                                     mb_emlrtRTEI.lineNo);
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
                                e_rtErrorWithMessageID(lb_emlrtRTEI.fName,
                                                       lb_emlrtRTEI.lineNo);
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
                                      e_rtErrorWithMessageID(
                                          lb_emlrtRTEI.fName,
                                          lb_emlrtRTEI.lineNo);
                                    }
                                    if (!(dc.re < 1.0)) {
                                      rtErrorWithMessageID(
                                          "  1.000000000000000e+00",
                                          nb_emlrtRTEI.fName,
                                          nb_emlrtRTEI.lineNo);
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
          d_rtErrorWithMessageID(c_emlrtRTEI.fName, c_emlrtRTEI.lineNo);
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
                sepByte.size(1), &k_emlrtBCI);
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
          d_rtErrorWithMessageID(c_emlrtRTEI.fName, c_emlrtRTEI.lineNo);
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
                sepByte.size(1), &p_emlrtBCI);
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
  static rtBoundsCheckInfo f_emlrtBCI{
      -1,                                              // iFirst
      -1,                                              // iLast
      308,                                             // lineNo
      44,                                              // colNo
      "timeVector",                                    // aName
      "uavrt_detection",                               // fName
      "H:\\repos\\uavrt_detection\\uavrt_detection.m", // pName
      0                                                // checkKind
  };
  static rtBoundsCheckInfo g_emlrtBCI{
      -1,                                              // iFirst
      -1,                                              // iLast
      373,                                             // lineNo
      32,                                              // colNo
      "t",                                             // aName
      "uavrt_detection",                               // fName
      "H:\\repos\\uavrt_detection\\uavrt_detection.m", // pName
      0                                                // checkKind
  };
  static rtBoundsCheckInfo h_emlrtBCI{
      -1,                                       // iFirst
      -1,                                       // iLast
      1600,                                     // lineNo
      56,                                       // colNo
      "obj.ps_pre.pl",                          // aName
      "waveform/process",                       // fName
      "H:\\repos\\uavrt_detection\\waveform.m", // pName
      0                                         // checkKind
  };
  static rtBoundsCheckInfo i_emlrtBCI{
      -1,                                       // iFirst
      -1,                                       // iLast
      1605,                                     // lineNo
      56,                                       // colNo
      "obj.ps_pre.pl",                          // aName
      "waveform/process",                       // fName
      "H:\\repos\\uavrt_detection\\waveform.m", // pName
      0                                         // checkKind
  };
  static rtDoubleCheckInfo b_emlrtDCI{
      282,                                             // lineNo
      46,                                              // colNo
      "uavrt_detection",                               // fName
      "H:\\repos\\uavrt_detection\\uavrt_detection.m", // pName
      4                                                // checkKind
  };
  static rtDoubleCheckInfo c_emlrtDCI{
      282,                                             // lineNo
      46,                                              // colNo
      "uavrt_detection",                               // fName
      "H:\\repos\\uavrt_detection\\uavrt_detection.m", // pName
      1                                                // checkKind
  };
  static rtDoubleCheckInfo d_emlrtDCI{
      283,                                             // lineNo
      53,                                              // colNo
      "uavrt_detection",                               // fName
      "H:\\repos\\uavrt_detection\\uavrt_detection.m", // pName
      4                                                // checkKind
  };
  static rtDoubleCheckInfo e_emlrtDCI{
      283,                                             // lineNo
      53,                                              // colNo
      "uavrt_detection",                               // fName
      "H:\\repos\\uavrt_detection\\uavrt_detection.m", // pName
      1                                                // checkKind
  };
  static rtEqualityCheckInfo c_emlrtECI{
      1,                                              // nDims
      218,                                            // lineNo
      14,                                             // colNo
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
  coder::datetime b;
  coder::datetime b_this;
  coder::datetime c_this;
  pulsestats lobj_11[4];
  pulsestats lobj_20[2];
  pulsestats lobj_14;
  pulsestats lobj_16;
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
  coder::array<creal32_T, 1U> dataReceived;
  coder::array<char, 2U> varargin_1;
  c_struct_T b_expl_temp;
  c_struct_T c_expl_temp;
  c_struct_T d_expl_temp;
  c_struct_T expl_temp;
  emxArray_creal32_T_1 b_asyncDataBuff;
  creal_T dcv[1000];
  creal32_T exampleData[1000];
  double b_tmp_data;
  double dataWriterSamples;
  double previousToc;
  double t6_P;
  double t6_SNR;
  double t6_fend;
  double t6_fp;
  double t6_fstart;
  double t6_t_0;
  double t6_t_f;
  double t6_yw;
  double t7_A;
  double t7_P;
  double t7_SNR;
  double t7_fend;
  double t7_fp;
  double t7_fstart;
  double t7_t_0;
  double t7_t_f;
  double t7_yw;
  unsigned long long nextSampleCount;
  float tmp_data;
  int currDir_size[2];
  int b_qY;
  int i;
  int iqDataToWrite_size;
  int udpReceiver;
  int udpSender;
  char currDir_data[200];
  char untokenizedDir[200];
  signed char fileid;
  boolean_T resetBuffersFlag;
  boolean_T staleDataFlag;
  boolean_T t6_con_dec;
  boolean_T t6_det_dec;
  boolean_T t7_con_dec;
  boolean_T t7_det_dec;
  if (!isInitialized_uavrt_detection) {
    uavrt_detection_initialize();
  }
  b_configPath.contents.set_size(1, configPath.size(1));
  udpSender = configPath.size(1);
  for (i = 0; i < udpSender; i++) {
    b_configPath.contents[i] = configPath[i];
  }
  // Needed for usleep function in generated code
  Config.contents.init();
  // Build empty config object
  updateconfig(&Config, &b_configPath);
  // Update (fill) the configuration
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
  udpSender = currDir_size[1];
  for (i = 0; i < udpSender; i++) {
    varargin_1[i] = currDir_data[i];
  }
  varargin_1[currDir_size[1]] = '\x00';
  printf("Curr Directory is: %s\n", &varargin_1[0]);
  fflush(stdout);
  printf("ROS2 disabled");
  fflush(stdout);
  makepulsestruc(&previousToc, &t6_P, &t6_SNR, &t6_yw, &t6_t_0, &t6_t_f,
                 expl_temp.t_next, &t6_fp, &t6_fstart, &t6_fend, expl_temp.mode,
                 &t6_det_dec, &t6_con_dec);
  makepulsestruc(&t7_A, &t7_P, &t7_SNR, &t7_yw, &t7_t_0, &t7_t_f,
                 b_expl_temp.t_next, &t7_fp, &t7_fstart, &t7_fend,
                 b_expl_temp.mode, &t7_det_dec, &t7_con_dec);
  expl_temp.con_dec = t6_con_dec;
  expl_temp.det_dec = t6_det_dec;
  expl_temp.fend = t6_fend;
  expl_temp.fstart = t6_fstart;
  expl_temp.fp = t6_fp;
  expl_temp.t_f = t6_t_f;
  expl_temp.t_0 = t6_t_0;
  expl_temp.yw = t6_yw;
  expl_temp.SNR = t6_SNR;
  expl_temp.P = t6_P;
  expl_temp.A = previousToc;
  b_expl_temp.con_dec = t7_con_dec;
  b_expl_temp.det_dec = t7_det_dec;
  b_expl_temp.fend = t7_fend;
  b_expl_temp.fstart = t7_fstart;
  b_expl_temp.fp = t7_fp;
  b_expl_temp.t_f = t7_t_f;
  b_expl_temp.t_0 = t7_t_0;
  b_expl_temp.yw = t7_yw;
  b_expl_temp.SNR = t7_SNR;
  b_expl_temp.P = t7_P;
  b_expl_temp.A = t7_A;
  pulseStatsPriori = lobj_20[1].init(Config.contents.tp, Config.contents.tip,
                                     Config.contents.tipu, Config.contents.tipj,
                                     &expl_temp, &b_expl_temp);
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
  // dims 0 if fixed, 1 if variable
  printf("Startup set 5 complete. \n");
  fflush(stdout);
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
  udpSender = udpSenderSetup(50000.0);
  if (udpSender <= 0) {
    b_rtErrorWithMessageID(b_emlrtRTEI.fName, b_emlrtRTEI.lineNo);
  }
  //  Two floats = 2 * 4 bytes;
  udpReceiver = udpReceiverSetup(Config.contents.portData);
  if (udpReceiver <= 0) {
    b_rtErrorWithMessageID(b_emlrtRTEI.fName, b_emlrtRTEI.lineNo);
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
  staleDataFlag = true;
  // Force buffer  flush on start
  b.init();
  // sysClockElapsedTime = 0;
  nextSampleCount = 0ULL;
  printf("Startup set 8 complete. Starting processing... \n");
  fflush(stdout);
  currDir_size[0] = 1;
  currDir_size[1] = 16383;
  while (1) {
    creal32_T iqDataToWrite_data;
    double timeVector_data;
    unsigned long long q0;
    unsigned long long qY;
    // i <= maxInd
    if (resetBuffersFlag) {
      asyncDataBuff.reset();
      asyncTimeBuff.reset();
      resetBuffersFlag = false;
    }
    //             %% Get data
    udpSamplesReceiverRead(udpReceiver, dataReceived);
    rtDimSizeGeqError(1025, 16384, &c_emlrtECI);
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
    coder::internal::indexShapeCheck(16384, currDir_size);
    // This is the number of samples transmitted by the
    // upstream process (ideal if none are dropped)
    previousToc = singlecomplex2int(dataReceived[16383]);
    previousToc = std::round(previousToc);
    if (previousToc < 1.8446744073709552E+19) {
      if (previousToc >= 0.0) {
        q0 = static_cast<unsigned long long>(previousToc);
      } else {
        q0 = 0ULL;
      }
    } else if (previousToc >= 1.8446744073709552E+19) {
      q0 = MAX_uint64_T;
    } else {
      q0 = 0ULL;
    }
    // If this is the first packet, calculate the offset
    // sample count since the upstream processess may have
    // started a while ago and its sample count may not be zero
    b_this.init();
    // To estimate the timestamp of the sample before the
    // first one in this first frame we go back in time
    // from the start time.
    qY = q0 - 16383ULL;
    if (q0 - 16383ULL > q0) {
      qY = 0ULL;
    }
    qY = q0 - qY;
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
        rtNonNegativeError(static_cast<double>(q0), &b_emlrtDCI);
      }
      previousToc = static_cast<int>(std::floor(static_cast<double>(
          static_cast<unsigned long long>(static_cast<double>(q0)))));
      if (static_cast<unsigned long long>(static_cast<double>(q0)) !=
          previousToc) {
        rtIntegerError(static_cast<double>(static_cast<unsigned long long>(
                           static_cast<double>(q0))),
                       &c_emlrtDCI);
      }
      if (!(q0 >= 0.0)) {
        rtNonNegativeError(static_cast<double>(q0), &d_emlrtDCI);
      }
      if (static_cast<unsigned long long>(static_cast<double>(q0)) !=
          previousToc) {
        rtIntegerError(static_cast<double>(static_cast<unsigned long long>(
                           static_cast<double>(q0))),
                       &e_emlrtDCI);
      }
      udpSender = static_cast<int>(q0);
      iqDataToWrite_size = static_cast<int>(q0) + 16383;
      if (udpSender - 1 >= 0) {
        iqDataToWrite_data.re = 0.0F;
        iqDataToWrite_data.im = 0.0F;
      }
      for (i = 0; i < 16383; i++) {
        iqDataToWrite_data = dataReceived[i];
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
      iqDataToWrite_size = 16383;
      for (i = 0; i < 16383; i++) {
        iqDataToWrite_data = dataReceived[i];
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
    if (iqDataToWrite_size < 1) {
      udpSender = 0;
    } else {
      udpSender = iqDataToWrite_size;
    }
    for (i = 0; i < udpSender; i++) {
      timeVector_data = 1.0 / Config.contents.Fs;
    }
    // fprintf('Sample elapsed seconds: %f \t Posix elapsed seconds:  \n',
    // timeVector(end), round(posixtime(datetime('now'))*1000000)/1000000 -
    // startTime)
    if (udpSender < 1) {
      rtDynamicBoundsError(0, 1, 0, &f_emlrtBCI);
    }
    // Write out data and time.
    asyncDataBuff.write((creal32_T *)&iqDataToWrite_data, iqDataToWrite_size);
    asyncTimeBuff.write((double *)&timeVector_data, udpSender);
    asyncWriteBuff.write((creal32_T *)dataReceived.data(),
                         (*(int(*)[1])dataReceived.size())[0]);
    //  OLD TIME STAMP METHOD
    // asyncWriteBuff.write([dataReceived;
    // int2singlecomplex(timeAtPacketReceive*10^3)]);
    if ((asyncWriteBuff.pBuffer.WritePointer >= 0) &&
        (asyncWriteBuff.pBuffer.ReadPointer <
         asyncWriteBuff.pBuffer.WritePointer - MAX_int32_T)) {
      udpSender = MAX_int32_T;
    } else if ((asyncWriteBuff.pBuffer.WritePointer < 0) &&
               (asyncWriteBuff.pBuffer.ReadPointer >
                asyncWriteBuff.pBuffer.WritePointer - MIN_int32_T)) {
      udpSender = MIN_int32_T;
    } else {
      udpSender = asyncWriteBuff.pBuffer.WritePointer -
                  asyncWriteBuff.pBuffer.ReadPointer;
    }
    if (udpSender < -2147483647) {
      udpSender = MIN_int32_T;
    } else {
      udpSender--;
    }
    if (asyncWriteBuff.pBuffer.ReadPointer < -2146882997) {
      b_qY = MAX_int32_T;
    } else {
      b_qY = 600650 - asyncWriteBuff.pBuffer.ReadPointer;
    }
    if ((b_qY < 0) &&
        (asyncWriteBuff.pBuffer.WritePointer < MIN_int32_T - b_qY)) {
      b_qY = MIN_int32_T;
    } else if ((b_qY > 0) &&
               (asyncWriteBuff.pBuffer.WritePointer > MAX_int32_T - b_qY)) {
      b_qY = MAX_int32_T;
    } else {
      b_qY += asyncWriteBuff.pBuffer.WritePointer;
    }
    if (asyncWriteBuff.pBuffer.ReadPointer <
        asyncWriteBuff.pBuffer.WritePointer) {
      b_qY = udpSender;
    } else if (asyncWriteBuff.pBuffer.ReadPointer ==
               asyncWriteBuff.pBuffer.WritePointer) {
      b_qY = 600650;
    }
    if (b_qY == dataWriterSamples) {
      asyncWriteBuff.read((creal32_T *)&iqDataToWrite_data,
                          &iqDataToWrite_size);
      if (fileid != -1) {
        interleaveComplexVector((const creal32_T *)&iqDataToWrite_data,
                                iqDataToWrite_size, (float *)&tmp_data,
                                &udpSender);
        coder::b_fwrite(static_cast<double>(fileid), (const float *)&tmp_data,
                        udpSender);
      }
    }
    // end
    if ((asyncDataBuff.pBuffer.WritePointer >= 0) &&
        (asyncDataBuff.pBuffer.ReadPointer <
         asyncDataBuff.pBuffer.WritePointer - MAX_int32_T)) {
      udpSender = MAX_int32_T;
    } else if ((asyncDataBuff.pBuffer.WritePointer < 0) &&
               (asyncDataBuff.pBuffer.ReadPointer >
                asyncDataBuff.pBuffer.WritePointer - MIN_int32_T)) {
      udpSender = MIN_int32_T;
    } else {
      udpSender = asyncDataBuff.pBuffer.WritePointer -
                  asyncDataBuff.pBuffer.ReadPointer;
    }
    if (udpSender < -2147483647) {
      udpSender = MIN_int32_T;
    } else {
      udpSender--;
    }
    if (asyncDataBuff.pBuffer.ReadPointer < -2141683327) {
      b_qY = MAX_int32_T;
    } else {
      b_qY = 5800320 - asyncDataBuff.pBuffer.ReadPointer;
    }
    if ((b_qY < 0) &&
        (asyncDataBuff.pBuffer.WritePointer < MIN_int32_T - b_qY)) {
      b_qY = MIN_int32_T;
    } else if ((b_qY > 0) &&
               (asyncDataBuff.pBuffer.WritePointer > MAX_int32_T - b_qY)) {
      b_qY = MAX_int32_T;
    } else {
      b_qY += asyncDataBuff.pBuffer.WritePointer;
    }
    previousToc = sampsForKPulses.contents + overlapSamples.contents;
    if (asyncDataBuff.pBuffer.ReadPointer <
        asyncDataBuff.pBuffer.WritePointer) {
      b_qY = udpSender;
    } else if (asyncDataBuff.pBuffer.ReadPointer ==
               asyncDataBuff.pBuffer.WritePointer) {
      b_qY = 5800320;
    }
    if (b_qY >= 3.0 * previousToc) {
      printf("Buffer anomaly detected. Printing buffer from back to front:\n");
      fflush(stdout);
      if ((asyncDataBuff.pBuffer.WritePointer >= 0) &&
          (asyncDataBuff.pBuffer.ReadPointer <
           asyncDataBuff.pBuffer.WritePointer - MAX_int32_T)) {
        udpSender = MAX_int32_T;
      } else if ((asyncDataBuff.pBuffer.WritePointer < 0) &&
                 (asyncDataBuff.pBuffer.ReadPointer >
                  asyncDataBuff.pBuffer.WritePointer - MIN_int32_T)) {
        udpSender = MIN_int32_T;
      } else {
        udpSender = asyncDataBuff.pBuffer.WritePointer -
                    asyncDataBuff.pBuffer.ReadPointer;
      }
      if (udpSender < -2147483647) {
        udpSender = MIN_int32_T;
      } else {
        udpSender--;
      }
      if (asyncDataBuff.pBuffer.ReadPointer < -2141683327) {
        b_qY = MAX_int32_T;
      } else {
        b_qY = 5800320 - asyncDataBuff.pBuffer.ReadPointer;
      }
      if ((b_qY < 0) &&
          (asyncDataBuff.pBuffer.WritePointer < MIN_int32_T - b_qY)) {
        b_qY = MIN_int32_T;
      } else if ((b_qY > 0) &&
                 (asyncDataBuff.pBuffer.WritePointer > MAX_int32_T - b_qY)) {
        b_qY = MAX_int32_T;
      } else {
        b_qY += asyncDataBuff.pBuffer.WritePointer;
      }
      if (asyncDataBuff.pBuffer.ReadPointer <
          asyncDataBuff.pBuffer.WritePointer) {
        b_qY = udpSender;
      } else if (asyncDataBuff.pBuffer.ReadPointer ==
                 asyncDataBuff.pBuffer.WritePointer) {
        b_qY = 5800320;
      }
      asyncDataBuff.read(b_qY, b_asyncDataBuff.data, &b_asyncDataBuff.size[0]);
      //  for i = numel(data):-1:1
      //       fprintf('%f + i%f, ', real(data(i)), imag(data(i)));
      //       if mod(i,20) == 0
      //           fprintf('\n')
      //       end
      //  end
      b_rtErrorWithMessageID(b_emlrtRTEI.fName, b_emlrtRTEI.lineNo);
    }
    //                 %% Process data if there is enough in the buffers
    if ((asyncDataBuff.pBuffer.WritePointer >= 0) &&
        (asyncDataBuff.pBuffer.ReadPointer <
         asyncDataBuff.pBuffer.WritePointer - MAX_int32_T)) {
      udpSender = MAX_int32_T;
    } else if ((asyncDataBuff.pBuffer.WritePointer < 0) &&
               (asyncDataBuff.pBuffer.ReadPointer >
                asyncDataBuff.pBuffer.WritePointer - MIN_int32_T)) {
      udpSender = MIN_int32_T;
    } else {
      udpSender = asyncDataBuff.pBuffer.WritePointer -
                  asyncDataBuff.pBuffer.ReadPointer;
    }
    if (udpSender < -2147483647) {
      udpSender = MIN_int32_T;
    } else {
      udpSender--;
    }
    if (asyncDataBuff.pBuffer.ReadPointer < -2141683327) {
      b_qY = MAX_int32_T;
    } else {
      b_qY = 5800320 - asyncDataBuff.pBuffer.ReadPointer;
    }
    if ((b_qY < 0) &&
        (asyncDataBuff.pBuffer.WritePointer < MIN_int32_T - b_qY)) {
      b_qY = MIN_int32_T;
    } else if ((b_qY > 0) &&
               (asyncDataBuff.pBuffer.WritePointer > MAX_int32_T - b_qY)) {
      b_qY = MAX_int32_T;
    } else {
      b_qY += asyncDataBuff.pBuffer.WritePointer;
    }
    if (asyncDataBuff.pBuffer.ReadPointer <
        asyncDataBuff.pBuffer.WritePointer) {
      b_qY = udpSender;
    } else if (asyncDataBuff.pBuffer.ReadPointer ==
               asyncDataBuff.pBuffer.WritePointer) {
      b_qY = 5800320;
    }
    if (b_qY >= previousToc) {
      double processingStartToc;
      unsigned int b_varargin_1;
      unsigned int varargin_2;
      boolean_T guard1{false};
      previousToc = std::round(sampsForKPulses.contents);
      if (previousToc < 4.294967296E+9) {
        if (previousToc >= 0.0) {
          b_varargin_1 = static_cast<unsigned int>(previousToc);
        } else {
          b_varargin_1 = 0U;
        }
      } else if (previousToc >= 4.294967296E+9) {
        b_varargin_1 = MAX_uint32_T;
      } else {
        b_varargin_1 = 0U;
      }
      previousToc = std::round(overlapSamples.contents);
      if (previousToc < 4.294967296E+9) {
        if (previousToc >= 0.0) {
          varargin_2 = static_cast<unsigned int>(previousToc);
        } else {
          varargin_2 = 0U;
        }
      } else if (previousToc >= 4.294967296E+9) {
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
        udpSender = MAX_int32_T;
      } else if ((asyncDataBuff.pBuffer.WritePointer < 0) &&
                 (asyncDataBuff.pBuffer.ReadPointer >
                  asyncDataBuff.pBuffer.WritePointer - MIN_int32_T)) {
        udpSender = MIN_int32_T;
      } else {
        udpSender = asyncDataBuff.pBuffer.WritePointer -
                    asyncDataBuff.pBuffer.ReadPointer;
      }
      if (udpSender < -2147483647) {
        udpSender = MIN_int32_T;
      } else {
        udpSender--;
      }
      if (asyncDataBuff.pBuffer.ReadPointer < -2141683327) {
        b_qY = MAX_int32_T;
      } else {
        b_qY = 5800320 - asyncDataBuff.pBuffer.ReadPointer;
      }
      if ((b_qY < 0) &&
          (asyncDataBuff.pBuffer.WritePointer < MIN_int32_T - b_qY)) {
        b_qY = MIN_int32_T;
      } else if ((b_qY > 0) &&
                 (asyncDataBuff.pBuffer.WritePointer > MAX_int32_T - b_qY)) {
        b_qY = MAX_int32_T;
      } else {
        b_qY += asyncDataBuff.pBuffer.WritePointer;
      }
      if (asyncDataBuff.pBuffer.ReadPointer <
          asyncDataBuff.pBuffer.WritePointer) {
        b_qY = udpSender;
      } else if (asyncDataBuff.pBuffer.ReadPointer ==
                 asyncDataBuff.pBuffer.WritePointer) {
        b_qY = 5800320;
      }
      printf("Running...Buffer full with %d samples. Processing. \n", b_qY);
      fflush(stdout);
      processingStartToc = coder::toc();
      // Overlap reads back into the buffer, but there
      // isn't anything back there on the first segment.
      // Using an overlap will fill the output with
      // overlapSamples of zeros at beginning
      // of x if you specify overlap here. Don't want that
      // so specify zero overlap for first read after
      // cleaning buffer
      asyncDataBuff.read(sampsForKPulses.contents,
                         (creal32_T *)&iqDataToWrite_data, &iqDataToWrite_size);
      asyncTimeBuff.read(sampsForKPulses.contents, (double *)&timeVector_data,
                         &b_qY);
      // plot(t,abs(x)); hold on
      // Check the timestamps in the buffer for gaps larger
      // than the max interpulse uncertainty. If there are
      // enough dropped packets such that the time is shifted
      // by more than the interpulse uncertainty, then the
      // detection will likely fail or produces bad results. In
      // this case. Skip the processing and clear the buffer.
      guard1 = false;
      if (Config.contents.K > 1.0) {
        udpSender = coder::diff();
        previousToc = 1.0 / Config.contents.Fs;
        for (i = 0; i < udpSender; i++) {
          b_tmp_data -= previousToc;
        }
        if (coder::sum((const double *)&b_tmp_data, udpSender) >
            Config.contents.tipu + Config.contents.tipj) {
          printf("Significant time differences found in timestamp record. "
                 "Skipping processing and clearing buffers.\n");
          fflush(stdout);
          resetBuffersFlag = true;
          staleDataFlag = true;
        } else {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }
      if (guard1) {
        unsigned int validatedHoleFilling[3];
        int varargin_1_size[2];
        unsigned int varargin_3;
        char varargin_1_data;
        if (b_qY < 1) {
          rtDynamicBoundsError(1, 1, b_qY, &g_emlrtBCI);
        }
        printf("Running...Building priori and waveform. \n");
        fflush(stdout);
        // Set the priori info
        // Initialize states for operational modes
        makepulsestruc(&previousToc, &t6_P, &t6_SNR, &t6_yw, &t6_t_0, &t6_t_f,
                       expl_temp.t_next, &t6_fp, &t6_fstart, &t6_fend,
                       expl_temp.mode, &t6_det_dec, &t6_con_dec);
        makepulsestruc(&t7_A, &t7_P, &t7_SNR, &t7_yw, &t7_t_0, &t7_t_f,
                       b_expl_temp.t_next, &t7_fp, &t7_fstart, &t7_fend,
                       b_expl_temp.mode, &t7_det_dec, &t7_con_dec);
        c_expl_temp.con_dec = t6_con_dec;
        c_expl_temp.det_dec = t6_det_dec;
        c_expl_temp.mode.set_size(1, expl_temp.mode.size(1));
        udpSender = expl_temp.mode.size(1);
        for (i = 0; i < udpSender; i++) {
          c_expl_temp.mode[i] = expl_temp.mode[i];
        }
        c_expl_temp.fend = t6_fend;
        c_expl_temp.fstart = t6_fstart;
        c_expl_temp.fp = t6_fp;
        c_expl_temp.t_next[0] = expl_temp.t_next[0];
        c_expl_temp.t_next[1] = expl_temp.t_next[1];
        c_expl_temp.t_f = t6_t_f;
        c_expl_temp.t_0 = t6_t_0;
        c_expl_temp.yw = t6_yw;
        c_expl_temp.SNR = t6_SNR;
        c_expl_temp.P = t6_P;
        c_expl_temp.A = previousToc;
        d_expl_temp.con_dec = t7_con_dec;
        d_expl_temp.det_dec = t7_det_dec;
        d_expl_temp.mode.set_size(1, b_expl_temp.mode.size(1));
        udpSender = b_expl_temp.mode.size(1);
        for (i = 0; i < udpSender; i++) {
          d_expl_temp.mode[i] = b_expl_temp.mode[i];
        }
        d_expl_temp.fend = t7_fend;
        d_expl_temp.fstart = t7_fstart;
        d_expl_temp.fp = t7_fp;
        d_expl_temp.t_next[0] = b_expl_temp.t_next[0];
        d_expl_temp.t_next[1] = b_expl_temp.t_next[1];
        d_expl_temp.t_f = t7_t_f;
        d_expl_temp.t_0 = t7_t_0;
        d_expl_temp.yw = t7_yw;
        d_expl_temp.SNR = t7_SNR;
        d_expl_temp.P = t7_P;
        d_expl_temp.A = t7_A;
        pulseStatsPriori = lobj_14.init(
            Config.contents.tp, Config.contents.tip, Config.contents.tipu,
            Config.contents.tipj,
            1.0E-5 * std::abs(Config.contents.tagFreqMHz -
                              Config.contents.channelCenterFreqMHz),
            &c_expl_temp, &d_expl_temp);
        //                         %% PRIMARY PROCESSING BLOCK
        // Prep waveform for processing/detection
        // UNTITLED2 Construct an instance of this class
        //    Detailed explanation goes here
        val.pf = Config.contents.falseAlarmProb;
        val.evMuParam = 0.0;
        val.evSigmaParam = 0.0;
        val.threshVecFine.set_size(1);
        val.threshVecFine[0] = 0.0;
        b_X.init((creal32_T *)&iqDataToWrite_data, iqDataToWrite_size,
                 Config.contents.Fs, timeVector_data, pulseStatsPriori, &val,
                 &lobj_16, &lobj_15);
        b_X.K = rtNaN;
        previousToc = std::round(b_X.N);
        if (previousToc < 4.294967296E+9) {
          if (previousToc >= 0.0) {
            b_varargin_1 = static_cast<unsigned int>(previousToc);
          } else {
            b_varargin_1 = 0U;
          }
        } else if (previousToc >= 4.294967296E+9) {
          b_varargin_1 = MAX_uint32_T;
        } else {
          b_varargin_1 = 0U;
        }
        previousToc = std::round(b_X.M);
        if (previousToc < 4.294967296E+9) {
          if (previousToc >= 0.0) {
            varargin_2 = static_cast<unsigned int>(previousToc);
          } else {
            varargin_2 = 0U;
          }
        } else if (previousToc >= 4.294967296E+9) {
          varargin_2 = MAX_uint32_T;
        } else {
          varargin_2 = 0U;
        }
        previousToc = std::round(b_X.J);
        if (previousToc < 4.294967296E+9) {
          if (previousToc >= 0.0) {
            varargin_3 = static_cast<unsigned int>(previousToc);
          } else {
            varargin_3 = 0U;
          }
        } else if (previousToc >= 4.294967296E+9) {
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
        printf("Samples in waveform: %u \n", 1U);
        fflush(stdout);
        previousToc = coder::toc();
        printf("Computing STFT...");
        fflush(stdout);
        b_X.spectro(&lobj_13);
        previousToc = coder::toc() - previousToc;
        printf("complete. Elapsed time: %f seconds \n", previousToc);
        fflush(stdout);
        printf("Building weighting matrix ...");
        fflush(stdout);
        previousToc = coder::toc();
        b_X.setweightingmatrix();
        previousToc = coder::toc() - previousToc;
        printf("complete. Elapsed time: %f seconds \n", previousToc);
        fflush(stdout);
        printf("UAV-RT: Unsupported mode requested. Defaulting to Discovery "
               "(D) mode.");
        fflush(stdout);
        previousToc = coder::toc();
        printf("Building thresholds  ...");
        fflush(stdout);
        val = b_X.thresh;
        val.makenewthreshold(&b_X);
        b_X.thresh = val;
        previousToc = coder::toc() - previousToc;
        printf("complete. Elapsed time: %f seconds \n", previousToc);
        fflush(stdout);
        printf("Time windows in S: %u \n", 1U);
        fflush(stdout);
        previousToc = coder::toc();
        printf("Finding pulses...");
        fflush(stdout);
        // PROCESS is a method that runs the pulse detection algorithm on
        // a waveform object.
        //
        // This method is is intended to be run on a waveform
        // segment that is short enought to contain at most K+1 pulses,
        // but at least K pulses, where K is the number of pulses to be
        // summed. Input paramets allow for the selection of search mode,
        // the focus mode, and the selection mode. The search mode
        // ('mode') is eithr 'discovery', 'confirmation', or 'tracking'
        // and selection of each of these affects how priori information
        // is used to reduce the frequency or time scope of the pulse
        // search. This also affects how the resulting ps_pos property of
        // the waveform is set. The false alarm probabilty is used along
        // with the decision table in order to determine the thresholds
        // used for the decision making on pulse detection.
        // Mode description:
        // Processing can be done in either discovery 'D', confirmation
        // 'C', or tracking 'T' modes. The selection of these modes
        // affects how time and frequency focusing is used to improve
        // processing time. In discovery mode is used for intial
        // detection when little is know about where pulses might exist
        // in time or frequeny. Confirmation is similar to discovery, but
        // is used after an initial detection to confirm that the
        // subsequent pulses exists where they should based on
        // forecasting from a previous detection. After pulses are
        // confirmed, the mode can be set to tracking which reduces the
        // frequency and time search space to improve processing speed.
        //
        //    Discovey mode:      'D'
        //        This mode uses no priori information and looks at the
        //        widest possible time bounds for pulses. If there is
        //        no priori frequency information in the ps_pre property
        //        or the focus mode is set to 'open', discovery mode
        //        will search across all frequencies. Otherwise it
        //        will search over all frequencies. If it detects pulses
        //        in the dataset that exceed the decision threshold, the
        //        posterior pulsestats object will be set to a mode of
        //        'C' so that the next segment processed will run in
        //        confirmation mode. If a detection or set of detections
        //        are made, the 'selection_mode' input will dictate how
        //        the posterior pulsestat property is set.
        //
        //    Confirmation mode:  'C'
        //        This mode is similar to discovery mode, but after a
        //        detection is made, it will compare the spectral and
        //        temporal location of the detected pulses to determine
        //        if the pulses align with what could be predicted from
        //        the pulses listed in the priori information of the
        //        waveform getting processed. If these pulses are
        //        confirmed, then the posteriori pulsestats mode property
        //        is set to 'T' so that subsequent segments can move to
        //        tracking mode. If pulses are detected but not where
        //        they should have been based on predictions from the
        //        priori, then the posteriori mode is set back to 'D'.
        //
        //    Tracking mode:      'T'
        //        Tracking mode uses priori pulsestats information in
        //        order to reduce the time and/or frequency space used
        //        for detection. The significantly speed processing
        //        speeds, but can miss detections if pulses move in time
        //        from where they should be based on a previous segment's
        //        detection. If using tracking mode and pulses aren't
        //        detected (scores don't meet the decision threhold), the
        //        posteriori pulsestats mode is set back to 'D'.
        //
        // INPUTS:
        //    mode    The search mode used. Must be string 'D' for
        //            discovery, 'C' for confirmation, or 'T' for
        //            tracking.
        //    focus_mode  How the algorithm decided whether or not to
        //            focus on a particular pulse. This mode can be set
        //            to 'open' wherein no focusing is done and the
        //            processing always proceeds along in discovery mode
        //            without narrowing the frequency or time span of the
        //            search. If this mode is set to 'focus', the method
        //            will allow for down selection of detected pulses
        //            for subsequent processing. The method of this
        //            downselection is determined by the 'selection_mode'
        //            input.
        //    selection_mode  How the algorithm narrows the scope for
        //            subsequent segment processing. This input is
        //            used when in 'discovery' mode. If pulses are
        //            detected, the focus mode will dictate which
        //            pulse is focused on for subsequent data
        //            segments. Focus mode can be set to 'most' to
        //            focus on the most powerful detecte pulse or
        //            'least' to focus on the least powerful detected
        //            pulse. See DETECT.M for more
        //            information on these focus modes.
        //    zetas   A vector of fractions of the DFT frequency bin
        //            width for which to compute and include in the
        //            spectral weighting matrix output. If no interbin
        //            shifting is desired, enter 0. Range of inputs
        //            [0,1). See WEIGHTINGMATRIX.m for more information
        //            on this vector.
        //    PF      A numeric probability of false alarm for decision
        //            threshold determination. Value range of PF must be
        //            within the pf property vector of the decision_table
        //            input.
        //    decision_table  A structure with two properties - 'pf' and
        //            'values'. The pf property is a vector of false alarm
        //            probabilities in decimal form (not percentage). The
        //            values property is vector of the same size as pf
        //            with the decision thresholds for the corresponding
        //            false alarm probability.
        //    excluded_freq_bands   nx2    matrix of bands of
        //                                 frequencies to exclude in
        //                                 the search. This is useful if
        //                                 there has already been a tag
        //                                 found and you want to exclude
        //                                 that band when looking for
        //                                 other frequencies. The lower
        //                                 frequecie of the band should
        //                                 be in the first column and
        //                                 the upper should be in the
        //                                 second. This is only used in
        //                                 the naive frequency search
        //                                 mode. Leave empty [] if no
        //                                 exclusion zones are
        //                                 necessary.
        //
        // OUTPUTS:
        //    None. This method updates the ps_pos property of the
        //    waveform object 'obj'.
        //
        //             %%
        //
        //         %% CHECK MODE ENTRANCE REQUIREMENTS
        // Determine if there is sufficient priori for the operation of each
        // mode. Check to see if they have entries and if they are finite (not
        // Nan or Inf). We just catch that and then set the have_priori flag to
        // false.
        i = b_X.ps_pre->pl.size(1);
        udpSender = b_X.ps_pre->pl.size(1);
        if ((udpSender < 1) || (udpSender > i)) {
          rtDynamicBoundsError(udpSender, 1, i, &h_emlrtBCI);
        }
        i = b_X.ps_pre->pl.size(1);
        udpSender = b_X.ps_pre->pl.size(1);
        if ((udpSender < 1) || (udpSender > i)) {
          rtDynamicBoundsError(udpSender, 1, i, &i_emlrtBCI);
        }
        // Enforce entry requirements on the modes so we don't get errors in
        // the 'C' and 'T' modes, as they required priori freq and time info.
        //                 %% SOMETHING BROKE
        previousToc = coder::toc() - previousToc;
        printf("complete. Elapsed time: %f seconds \n", previousToc);
        fflush(stdout);
        previousToc = coder::toc() - processingStartToc;
        printf("TOTAL PULSE PROCESSING TIME: %f seconds \n", previousToc);
        fflush(stdout);
        //                         %% PREP FOR NEXT LOOP
        // Latch/Release the frequency lock and setup the
        // suggested mode
        coder::internal::horzcatStructList(*(int(*)[2])b_X.ps_pos->pl.size(),
                                           varargin_1_size);
        if ((varargin_1_size[0] != 0) && (varargin_1_size[1] != 0)) {
          udpSender = 1;
        } else {
          udpSender = (varargin_1_size[0] > 0);
        }
        if ((varargin_1_size[0] != udpSender) &&
            ((varargin_1_size[0] != 0) && (varargin_1_size[1] != 0))) {
          rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
        }
        // Check lagging processing
        // tic
        previousToc = coder::toc();
        // Prepare priori for next segment
        printf("Updating priori...\n");
        fflush(stdout);
        updatebufferreadvariables(&Config, &stftOverlapFraction,
                                  &overlapSamples, &sampsForKPulses,
                                  b_X.ps_pos);
        previousToc = coder::toc() - previousToc;
        printf("complete. Elapsed time: %f seconds \n", previousToc);
        fflush(stdout);
        // Deal with detected pulses
        // Xhold{mod(segmentsProcessed,maxSegments)} = X;%Keep a maxSegments
        // running record of waveforms for debugging in Matlab Xstruct =
        // obj2structrecursive(); Xhold = X;
        waveformcopy(&b_X, &lobj_10, &lobj_11[0], &lobj_12);
        // Report pulses and check for repeat detections
        udpSender = b_X.ps_pos->cpki.size(0);
        b_qY = b_X.ps_pos->cpki.size(1);
        if ((static_cast<signed char>(udpSender) == 0) ||
            (static_cast<signed char>(b_qY) == 0)) {
          printf("No pulses detected \n");
          fflush(stdout);
        }
        udpSender = b_X.ps_pos->cpki.size(0);
        b_qY = b_X.ps_pos->cpki.size(1);
        if ((static_cast<signed char>(udpSender) != 0) &&
            (static_cast<signed char>(b_qY) != 0)) {
          printf("Transmitting ROS2 pulse messages");
          fflush(stdout);
          printf("complete. Transmitted %u pulse(s).\n", 1U);
          fflush(stdout);
        } else {
          printf("\n");
          fflush(stdout);
        }
        varargin_1_data = '\x00';
        printf("Current Mode: %s\n", &varargin_1_data);
        fflush(stdout);
        printf("====================================\n");
        fflush(stdout);
      }
      c_this.init();
      previousToc = coder::toc();
      printf("tocElapsed - clockElapsed = %0.6f  **************** \n",
             previousToc - (c_this.data.re / 1000.0 * 1.0E+6 / 1.0E+6 -
                            b_this.data.re / 1000.0 * 1.0E+6 / 1.0E+6));
      fflush(stdout);
      previousToc = coder::toc() - processingStartToc;
      printf("TOTAL SEGMENT PROCESSING TIME: %f seconds \n", previousToc);
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
