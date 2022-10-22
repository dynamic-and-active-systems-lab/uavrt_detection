//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: uavrt_detection.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 22-Oct-2022 15:24:58
//

// Include Files
#include "uavrt_detection.h"
#include "AsyncBuffer.h"
#include "AsyncBuffercgHelper.h"
#include "DetectorConfig.h"
#include "all.h"
#include "diff.h"
#include "feof.h"
#include "fgetl.h"
#include "fileManager.h"
#include "find.h"
#include "fseek.h"
#include "ftell.h"
#include "ifWhileCond.h"
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
#include "validate_print_arguments.h"
#include "waveform.h"
#include "waveformcopy.h"
#include "wfmstft.h"
#include "wgn.h"
#include "coder_array.h"
#include "udp.h"
#include <algorithm>
#include <cmath>
#include <cstring>
#include <stdio.h>

// Function Declarations
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
  static const char b_cv1[20]{'c', 'h', 'a', 'n', 'n', 'e', 'l', 'C', 'e', 'n',
                              't', 'e', 'r', 'F', 'r', 'e', 'q', 'M', 'H', 'z'};
  static const char cv7[10]{'t', 'a', 'g', 'F', 'r', 'e', 'q', 'M', 'H', 'z'};
  static const char cv5[9]{'p', 'o', 'r', 't', 'C', 'n', 't', 'r', 'l'};
  static const char cv3[8]{'p', 'o', 'r', 't', 'D', 'a', 't', 'a'};
  static const char cv4[7]{'i', 'p', 'C', 'n', 't', 'r', 'l'};
  static const char b_cv2[6]{'i', 'p', 'D', 'a', 't', 'a'};
  static const char cv10[4]{'t', 'i', 'p', 'u'};
  static const char cv9[3]{'t', 'i', 'p'};
  static const char b_cv[2]{'I', 'D'};
  static const char cv6[2]{'F', 's'};
  static const char cv8[2]{'t', 'p'};
  coder::b_rtString _in;
  coder::array<creal_T, 2U> r;
  coder::array<double, 2U> sepByte;
  coder::array<double, 2U> val;
  coder::array<int, 2U> match_out;
  coder::array<int, 2U> matches;
  coder::array<unsigned int, 2U> tabLocs;
  coder::array<char, 2U> configType;
  coder::array<char, 2U> configValStr;
  coder::array<char, 2U> lineStr;
  coder::array<boolean_T, 2U> b_lineStr;
  int colonLocation_data;
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
    char varargin_1[35];
    for (int i{0}; i < 34; i++) {
      varargin_1[i] = configPath->contents.Value[i];
    }
    varargin_1[34] = '\x00';
    printf("Failed to open config file: %s\n", &varargin_1[0]);
    fflush(stdout);
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
    coder::b_fseek(static_cast<double>(fileid),
                   sepByte[static_cast<int>(configNum) - 1]);
    done = false;
    while (!done) {
      coder::fgetl(static_cast<double>(fileid), lineStr);
      if (lineStr[0] != '#') {
        int exitg1;
        int loop_ub;
        int match_idx;
        int text_len;
        boolean_T b_bool;
        b_lineStr.set_size(1, lineStr.size(1));
        loop_ub = lineStr.size(1);
        for (i = 0; i < loop_ub; i++) {
          b_lineStr[i] = (lineStr[i] == ':');
        }
        int colonLocation_size[2];
        coder::eml_find(b_lineStr, (int *)&colonLocation_data,
                        colonLocation_size);
        // note regexp is not supported for code generation
        if (lineStr.size(1) == 0) {
          tabLocs.set_size(1, 0);
        } else {
          text_len = lineStr.size(1);
          matches.set_size(1, lineStr.size(1));
          match_idx = 0;
          for (loop_ub = 0; loop_ub < text_len; loop_ub++) {
            if (lineStr[loop_ub] == '\x09') {
              matches[match_idx] = loop_ub + 1;
              match_idx++;
            }
          }
          match_out.set_size(1, match_idx);
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
        // note regexp is not supported for code generation
        if (static_cast<double>(colonLocation_data) - 1.0 < 1.0) {
          loop_ub = 0;
        } else {
          loop_ub = colonLocation_data - 1;
        }
        configType.set_size(1, loop_ub);
        for (i = 0; i < loop_ub; i++) {
          configType[i] = lineStr[i];
        }
        if (tabLocs[0] + 1U > static_cast<unsigned int>(lineStr.size(1))) {
          i = 0;
          text_len = 0;
        } else {
          i = static_cast<int>(tabLocs[0]);
          text_len = lineStr.size(1);
        }
        match_idx = text_len - i;
        configValStr.set_size(1, match_idx);
        for (text_len = 0; text_len < match_idx; text_len++) {
          configValStr[text_len] = lineStr[i + text_len];
        }
        b_bool = false;
        if (loop_ub == 2) {
          text_len = 0;
          do {
            exitg1 = 0;
            if (text_len < 2) {
              if (lineStr[text_len] != b_cv[text_len]) {
                exitg1 = 1;
              } else {
                text_len++;
              }
            } else {
              b_bool = true;
              exitg1 = 1;
            }
          } while (exitg1 == 0);
        }
        if (!b_bool) {
          b_bool = false;
          if (loop_ub == 20) {
            text_len = 0;
            do {
              exitg1 = 0;
              if (text_len < 20) {
                if (lineStr[text_len] != b_cv1[text_len]) {
                  exitg1 = 1;
                } else {
                  text_len++;
                }
              } else {
                b_bool = true;
                exitg1 = 1;
              }
            } while (exitg1 == 0);
          }
          if (b_bool) {
            creal_T dc;
            dc = coder::str2double(configValStr);
            Config->contents.channelCenterFreqMHz = dc.re;
          } else {
            b_bool = false;
            if (loop_ub == 6) {
              text_len = 0;
              do {
                exitg1 = 0;
                if (text_len < 6) {
                  if (lineStr[text_len] != b_cv2[text_len]) {
                    exitg1 = 1;
                  } else {
                    text_len++;
                  }
                } else {
                  b_bool = true;
                  exitg1 = 1;
                }
              } while (exitg1 == 0);
            }
            if (!b_bool) {
              b_bool = false;
              if (loop_ub == 8) {
                text_len = 0;
                do {
                  exitg1 = 0;
                  if (text_len < 8) {
                    if (lineStr[text_len] != cv3[text_len]) {
                      exitg1 = 1;
                    } else {
                      text_len++;
                    }
                  } else {
                    b_bool = true;
                    exitg1 = 1;
                  }
                } while (exitg1 == 0);
              }
              if (b_bool) {
                creal_T dc;
                unsigned short in;
                dc = coder::str2double(configValStr);
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
              } else {
                b_bool = false;
                if (loop_ub == 7) {
                  text_len = 0;
                  do {
                    exitg1 = 0;
                    if (text_len < 7) {
                      if (lineStr[text_len] != cv4[text_len]) {
                        exitg1 = 1;
                      } else {
                        text_len++;
                      }
                    } else {
                      b_bool = true;
                      exitg1 = 1;
                    }
                  } while (exitg1 == 0);
                }
                if (!b_bool) {
                  b_bool = false;
                  if (loop_ub == 9) {
                    text_len = 0;
                    do {
                      exitg1 = 0;
                      if (text_len < 9) {
                        if (lineStr[text_len] != cv5[text_len]) {
                          exitg1 = 1;
                        } else {
                          text_len++;
                        }
                      } else {
                        b_bool = true;
                        exitg1 = 1;
                      }
                    } while (exitg1 == 0);
                  }
                  if (b_bool) {
                    coder::str2double(configValStr);
                  } else {
                    b_bool = false;
                    if (loop_ub == 2) {
                      text_len = 0;
                      do {
                        exitg1 = 0;
                        if (text_len < 2) {
                          if (lineStr[text_len] != cv6[text_len]) {
                            exitg1 = 1;
                          } else {
                            text_len++;
                          }
                        } else {
                          b_bool = true;
                          exitg1 = 1;
                        }
                      } while (exitg1 == 0);
                    }
                    if (b_bool) {
                      creal_T dc;
                      dc = coder::str2double(configValStr);
                      Config->contents.Fs = dc.re;
                    } else {
                      b_bool = false;
                      if (loop_ub == 10) {
                        text_len = 0;
                        do {
                          exitg1 = 0;
                          if (text_len < 10) {
                            if (lineStr[text_len] != cv7[text_len]) {
                              exitg1 = 1;
                            } else {
                              text_len++;
                            }
                          } else {
                            b_bool = true;
                            exitg1 = 1;
                          }
                        } while (exitg1 == 0);
                      }
                      if (b_bool) {
                        creal_T dc;
                        dc = coder::str2double(configValStr);
                        Config->contents.tagFreqMHz = dc.re;
                      } else {
                        b_bool = false;
                        if (loop_ub == 2) {
                          text_len = 0;
                          do {
                            exitg1 = 0;
                            if (text_len < 2) {
                              if (lineStr[text_len] != cv8[text_len]) {
                                exitg1 = 1;
                              } else {
                                text_len++;
                              }
                            } else {
                              b_bool = true;
                              exitg1 = 1;
                            }
                          } while (exitg1 == 0);
                        }
                        if (b_bool) {
                          creal_T dc;
                          dc = coder::str2double(configValStr);
                          Config->contents.tp = dc.re;
                        } else {
                          b_bool = false;
                          if (loop_ub == 3) {
                            text_len = 0;
                            do {
                              exitg1 = 0;
                              if (text_len < 3) {
                                if (lineStr[text_len] != cv9[text_len]) {
                                  exitg1 = 1;
                                } else {
                                  text_len++;
                                }
                              } else {
                                b_bool = true;
                                exitg1 = 1;
                              }
                            } while (exitg1 == 0);
                          }
                          if (b_bool) {
                            creal_T dc;
                            dc = coder::str2double(configValStr);
                            Config->contents.tip = dc.re;
                          } else {
                            b_bool = false;
                            if (loop_ub == 4) {
                              text_len = 0;
                              do {
                                exitg1 = 0;
                                if (text_len < 4) {
                                  if (lineStr[text_len] != cv10[text_len]) {
                                    exitg1 = 1;
                                  } else {
                                    text_len++;
                                  }
                                } else {
                                  b_bool = true;
                                  exitg1 = 1;
                                }
                              } while (exitg1 == 0);
                            }
                            if (b_bool) {
                              creal_T dc;
                              dc = coder::str2double(configValStr);
                              Config->contents.tipu = dc.re;
                            } else if (coder::internal::b_strcmp(configType)) {
                              creal_T dc;
                              dc = coder::str2double(configValStr);
                              Config->contents.tipj = dc.re;
                            } else {
                              b_bool = false;
                              if ((loop_ub == 1) && (lineStr[0] == 'K')) {
                                b_bool = true;
                              }
                              if (b_bool) {
                                creal_T dc;
                                unsigned char b_in;
                                dc = coder::str2double(configValStr);
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
                              } else if (coder::internal::c_strcmp(
                                             configType)) {
                                _in.Value.set_size(1, match_idx);
                                for (text_len = 0; text_len < match_idx;
                                     text_len++) {
                                  _in.Value[text_len] = lineStr[i + text_len];
                                }
                                Config->contents.opMode = _in;
                              } else if (coder::internal::d_strcmp(
                                             configType)) {
                                str2matrix(configValStr, r);
                                val.set_size(r.size(0), r.size(1));
                                loop_ub = r.size(0) * r.size(1);
                                for (i = 0; i < loop_ub; i++) {
                                  val[i] = r[i].re;
                                }
                                if ((val.size(0) == 1) && (val.size(1) == 1)) {
                                  Config->contents.excldFreqs.set_size(1, 2);
                                  Config->contents.excldFreqs[0] = val[0];
                                  Config->contents.excldFreqs[1] = val[0];
                                } else if (val.size(0) == 0) {
                                  Config->contents.excldFreqs.set_size(0, 2);
                                } else {
                                  Config->contents.excldFreqs.set_size(
                                      val.size(0), 2);
                                  loop_ub = val.size(0) << 1;
                                  for (i = 0; i < loop_ub; i++) {
                                    Config->contents.excldFreqs[i] = val[i];
                                  }
                                }
                              } else if (coder::internal::e_strcmp(
                                             configType)) {
                                creal_T dc;
                                dc = coder::str2double(configValStr);
                                Config->contents.falseAlarmProb = dc.re;
                              } else if (coder::internal::f_strcmp(
                                             configType)) {
                                _in.Value.set_size(1, match_idx);
                                for (text_len = 0; text_len < match_idx;
                                     text_len++) {
                                  _in.Value[text_len] = lineStr[i + text_len];
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
        // Stop when we have finished reading this entry.
        if ((coder::b_feof(static_cast<double>(fileid)) == 1.0) ||
            (coder::b_ftell(static_cast<double>(fileid)) ==
             sepByte[static_cast<int>(static_cast<unsigned int>(configNum))])) {
          done = true;
        }
      } else if ((coder::b_feof(static_cast<double>(fileid)) == 1.0) ||
                 (coder::b_ftell(static_cast<double>(fileid)) ==
                  sepByte[static_cast<int>(
                      static_cast<unsigned int>(configNum))])) {
        done = true;
      }
    }
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
  static coder::dsp::AsyncBuffer asyncTimeBuff;
  static coder::dsp::b_AsyncBuffer asyncDataBuff;
  b_waveform X;
  coder::array<c_struct_T, 2U> *structure;
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
  coder::array<char, 2U> c_varargin_1;
  coder::array<boolean_T, 2U> b_varargin_1;
  coder::array<boolean_T, 2U> ps_pre_struc_cmsk;
  coder::array<boolean_T, 1U> b_tmp_data;
  coder::array<boolean_T, 1U> r2;
  c_struct_T expl_temp;
  c_struct_T r;
  creal_T dcv[1000];
  creal32_T complexBuffer[1025];
  creal32_T complexBuffer_data[1024];
  creal32_T exampleData[1000];
  double ps_pre_struc_tmplt[2];
  double lastTimeStamp;
  double missingPackets;
  double missingTime;
  double ps_pre_struc_fend;
  double ps_pre_struc_fstart;
  double segmentsProcessed;
  double t5_fend;
  double t5_fp;
  double t5_fstart;
  double t5_t_0;
  double t5_t_f;
  double t5_yw;
  double timeStamp;
  double trackedCount;
  int q1;
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
  boolean_T t5_con_dec;
  boolean_T t5_det_dec;
  boolean_T tmp_data;
  if (!isInitialized_uavrt_detection) {
    uavrt_detection_initialize();
  }
  asyncTimeBuff.pBuffer.matlabCodegenIsDeleted = true;
  asyncTimeBuff.matlabCodegenIsDeleted = true;
  configPath.contents.init();
  // Must exist in the same directory as the execution of this executable
  Config.contents.init();
  // Build empty config object
  updateconfig(&Config, &configPath);
  // Update (fill) the configuration
  configUpdatedFlag = true;
  makepulsestruc(&r.A, &r.P, &r.SNR, &r.yw, &r.t_0, &r.t_f, r.t_next, &r.fp,
                 &r.fstart, &r.fend, r.mode, &r.det_dec, &r.con_dec);
  makepulsestruc(&missingTime, &missingPackets, &timeStamp, &t5_yw, &t5_t_0,
                 &t5_t_f, expl_temp.t_next, &t5_fp, &t5_fstart, &t5_fend,
                 expl_temp.mode, &t5_det_dec, &t5_con_dec);
  expl_temp.con_dec = t5_con_dec;
  expl_temp.det_dec = t5_det_dec;
  expl_temp.fend = t5_fend;
  expl_temp.fstart = t5_fstart;
  expl_temp.fp = t5_fp;
  expl_temp.t_f = t5_t_f;
  expl_temp.t_0 = t5_t_0;
  expl_temp.yw = t5_yw;
  expl_temp.SNR = timeStamp;
  expl_temp.P = missingPackets;
  expl_temp.A = missingTime;
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
  asyncTimeBuff.init();
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
  t5_t_0 = 0.0;
  t5_t_f = 0.0;
  t5_fp = 0.0;
  t5_fstart = 0.0;
  t5_fend = 0.0;
  ps_pre_struc_fstart = 0.0;
  ps_pre_struc_fend = 0.0;
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
  for (q1 = 0; q1 < 1000; q1++) {
    exampleData[q1].re = static_cast<float>(dcv[q1].re);
    exampleData[q1].im = static_cast<float>(dcv[q1].im);
  }
  // UNTITLED2 Construct an instance of this class
  //    Detailed explanation goes here
  val.pf = Config.contents.falseAlarmProb;
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
  udpSender = udpSenderSetup(30000.0);
  // Initialize loop variables
  resetBuffersFlag = true;
  segmentsProcessed = 0.0;
  suggestedMode = 'S';
  fLock = false;
  staleDataFlag = true;
  // Force buffer  flush on start
  lastTimeStamp = 0.0;
  cleanBuffer = true;
  trackedCount = 0.0;
  printf("Startup set 7 complete. Starting processing... \n");
  fflush(stdout);
  int exitg1;
  do {
    double timeStamp_data[1024];
    int n;
    int qY;
    exitg1 = 0;
    // i <= maxInd
    if (resetBuffersFlag) {
      if (asyncDataBuff.pBuffer.isInitialized == 1) {
        asyncDataBuff.pBuffer.ReadPointer = 1;
        asyncDataBuff.pBuffer.WritePointer = 2;
        asyncDataBuff.pBuffer.CumulativeOverrun = 0;
        asyncDataBuff.pBuffer.CumulativeUnderrun = 0;
        std::memset(&asyncDataBuff.pBuffer.Cache[0], 0,
                    49621U * sizeof(creal32_T));
      }
      if (asyncTimeBuff.pBuffer.isInitialized == 1) {
        asyncTimeBuff.pBuffer.ReadPointer = 1;
        asyncTimeBuff.pBuffer.WritePointer = 2;
        asyncTimeBuff.pBuffer.CumulativeOverrun = 0;
        asyncTimeBuff.pBuffer.CumulativeUnderrun = 0;
        std::memset(&asyncTimeBuff.pBuffer.Cache[0], 0,
                    49621U * sizeof(double));
      }
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
    udpReceiverRead(udpReceiver, &complexBuffer[0], 1025.0);
    //             %% Wait for new data if none ready, else put data in buffers
    // singlecomplex2int Converts a complex single precision positive
    // number with a portion of the integer digits in the real and imaginary
    // parts to integer value. The integer is split at the 7th digit. The top
    // digits are then held in the real part of the input, while the lower 7
    // digits are held in the imaginary part of the input. These digits are
    // recombined to create a double precision output of the integer.
    //
    // A single precision number has a maximum integer
    // values of flintmax('single') = 16777216. To avoid overrunning the
    // available digits, the output integer is split at digit 7.
    //
    // The max value for each input part would be:   16777216 + 1i * 16777216
    // To avoid overflow, the complex part
    // containing the lower digits only use          16777216 + 1i *  xxxxxxx
    // the first 7 digits available
    //
    // Based on this standard, the maximum value that can be transmitted is
    //    167772169999999 = 1.6777e14;
    //
    // INPUTS:
    //    singleComplex   Matrix of where each elements' imaginary part contains
    //                    the bottom 7 digits of the output integer. The inputs
    //                    real part contain the upper digits of the output.
    //                    The maximum value of the input real part is
    //                    16,777,216. The maximum value of the imaginary part if
    //                    9,999,999. An error is generated if these values are
    //                    exceeded. Imaginary parts (lower digits) must be
    //                    positive. Sign can be contained in the upper digits
    //                    (real part). Real and imaginary parts must only
    //                    contain integers.
    // OUTPUTS:
    //    intOut           Matrix of integer values.
    //                    Maximum input value is 167772169999999. Inputs
    //                    exceedign this value will result in an error.
    //
    // -------------------------------------------------------------------------
    // Author:    Michael Shafer
    // Date:      2022-08-19
    // -------------------------------------------------------------------------
    timeStamp = 0.001 * (complexBuffer[0].re * 1.0E+7 + complexBuffer[0].im);
    t5_yw = 1.0 / Config.contents.Fs;
    // Check for missing packets based on packet timestamps.
    n = asyncTimeBuff.pBuffer.WritePointer;
    q1 = asyncTimeBuff.pBuffer.ReadPointer;
    if ((n >= 0) && (q1 < n - MAX_int32_T)) {
      n = MAX_int32_T;
    } else if ((n < 0) && (q1 > n - MIN_int32_T)) {
      n = MIN_int32_T;
    } else {
      n -= q1;
    }
    if (n < -2147483647) {
      n = MIN_int32_T;
    } else {
      n--;
    }
    q1 = asyncTimeBuff.pBuffer.ReadPointer;
    if (q1 < -2147434027) {
      qY = MAX_int32_T;
    } else {
      qY = 49620 - q1;
    }
    q1 = asyncTimeBuff.pBuffer.WritePointer;
    if ((qY < 0) && (q1 < MIN_int32_T - qY)) {
      qY = MIN_int32_T;
    } else if ((qY > 0) && (q1 > MAX_int32_T - qY)) {
      qY = MAX_int32_T;
    } else {
      qY += q1;
    }
    if (asyncTimeBuff.pBuffer.ReadPointer >=
        asyncTimeBuff.pBuffer.WritePointer) {
      if (asyncTimeBuff.pBuffer.ReadPointer ==
          asyncTimeBuff.pBuffer.WritePointer) {
        n = 49620;
      } else {
        n = qY;
      }
    }
    if (n != 0) {
      missingTime = (timeStamp - lastTimeStamp) - 1024.0 / Config.contents.Fs;
      missingPackets = missingTime * Config.contents.Fs / 1024.0;
      if (missingPackets > 1.0) {
        printf("Packet drop detected. Missed %f packets, or %f seconds of "
               "data. \n",
               missingPackets, missingTime);
        fflush(stdout);
      }
      lastTimeStamp = timeStamp;
    } else {
      lastTimeStamp = timeStamp;
    }
    // Write out data and time.
    std::copy(&complexBuffer[1], &complexBuffer[1025], &complexBuffer_data[0]);
    asyncDataBuff.write(complexBuffer_data);
    for (q1 = 0; q1 < 1024; q1++) {
      timeStamp_data[q1] = timeStamp + t5_yw * static_cast<double>(q1);
    }
    asyncTimeBuff.write(timeStamp_data);
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
      boolean_T guard1{false};
      missingTime = std::round(sampsForKPulses.contents);
      if (missingTime < 4.294967296E+9) {
        if (missingTime >= 0.0) {
          varargin_1 = static_cast<unsigned int>(missingTime);
        } else {
          varargin_1 = 0U;
        }
      } else if (missingTime >= 4.294967296E+9) {
        varargin_1 = MAX_uint32_T;
      } else {
        varargin_1 = 0U;
      }
      missingTime = std::round(overlapSamples.contents);
      if (missingTime < 4.294967296E+9) {
        if (missingTime >= 0.0) {
          varargin_2 = static_cast<unsigned int>(missingTime);
        } else {
          varargin_2 = 0U;
        }
      } else if (missingTime >= 4.294967296E+9) {
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
      guard1 = false;
      if (Config.contents.K > 1.0) {
        coder::diff(t, r1);
        n = r1.size(0);
        for (q1 = 0; q1 < n; q1++) {
          r1[q1] = r1[q1] - t5_yw;
        }
        if (coder::sum(r1) > Config.contents.tipu + Config.contents.tipj) {
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
        unsigned int varargin_3;
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
          makepulsestruc(&missingTime, &missingPackets, &timeStamp, &t5_yw,
                         &t5_t_0, &t5_t_f, expl_temp.t_next, &t5_fp, &t5_fstart,
                         &t5_fend, expl_temp.mode, &t5_det_dec, &t5_con_dec);
          expl_temp.con_dec = t5_con_dec;
          expl_temp.det_dec = t5_det_dec;
          expl_temp.fend = t5_fend;
          expl_temp.fstart = t5_fstart;
          expl_temp.fp = t5_fp;
          expl_temp.t_f = t5_t_f;
          expl_temp.t_0 = t5_t_0;
          expl_temp.yw = t5_yw;
          expl_temp.SNR = timeStamp;
          expl_temp.P = missingPackets;
          expl_temp.A = missingTime;
          pulseStatsPriori = lobj_13.init(
              Config.contents.tp, Config.contents.tip, Config.contents.tipu,
              Config.contents.tipj,
              1.0E-5 * std::abs(Config.contents.tagFreqMHz -
                                Config.contents.channelCenterFreqMHz),
              &r, &expl_temp);
          configUpdatedFlag = false;
        } else {
          pulseStatsPriori = lobj_16.c_init(
              t5_t_0, t5_t_f, t5_fp, t5_fstart, t5_fend, ps_pre_struc_fstart,
              ps_pre_struc_fend, ps_pre_struc_tmplt, (char *)&mode,
              ps_pre_struc_pl, ps_pre_struc_clst, ps_pre_struc_cmsk,
              ps_pre_struc_cpki);
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
        b_X.init(x, Config.contents.Fs, t[0], pulseStatsPriori, &val, &lobj_15,
                 &lobj_14);
        b_X.K = Config.contents.K;
        missingTime = std::round(b_X.N);
        if (missingTime < 4.294967296E+9) {
          if (missingTime >= 0.0) {
            varargin_1 = static_cast<unsigned int>(missingTime);
          } else {
            varargin_1 = 0U;
          }
        } else if (missingTime >= 4.294967296E+9) {
          varargin_1 = MAX_uint32_T;
        } else {
          varargin_1 = 0U;
        }
        missingTime = std::round(b_X.M);
        if (missingTime < 4.294967296E+9) {
          if (missingTime >= 0.0) {
            varargin_2 = static_cast<unsigned int>(missingTime);
          } else {
            varargin_2 = 0U;
          }
        } else if (missingTime >= 4.294967296E+9) {
          varargin_2 = MAX_uint32_T;
        } else {
          varargin_2 = 0U;
        }
        missingTime = std::round(b_X.J);
        if (missingTime < 4.294967296E+9) {
          if (missingTime >= 0.0) {
            varargin_3 = static_cast<unsigned int>(missingTime);
          } else {
            varargin_3 = 0U;
          }
        } else if (missingTime >= 4.294967296E+9) {
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
        missingPackets = coder::toc();
        printf("complete. Elapsed time: %f seconds \n", missingPackets);
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
        missingPackets = coder::toc();
        printf("complete. Elapsed time: %f seconds \n", missingPackets);
        fflush(stdout);
        varargin_1 = static_cast<unsigned int>(b_X.stft->S.size(1));
        printf("Time windows in S: %u \n", varargin_1);
        fflush(stdout);
        printf("Finding pulses...");
        fflush(stdout);
        b_X.process(mode, Config.contents.excldFreqs);
        missingTime = coder::toc();
        missingPackets = coder::toc();
        printf("complete. Elapsed time: %f seconds \n", missingPackets);
        fflush(stdout);
        //                         %% PREP FOR NEXT LOOP
        // Latch/Release the frequency lock and setup the
        // suggested mode
        suggestedMode = b_X.ps_pos->mode;
        structure = &b_X.ps_pos->pl;
        n = structure->size(1);
        if (structure->size(1) == 0) {
          q1 = 0;
        } else {
          q1 = structure->size(1);
        }
        b_varargin_1.set_size(1, q1);
        for (qY = 0; qY < n; qY++) {
          b_varargin_1[qY] = (*structure)[qY].con_dec;
        }
        coder::all(b_varargin_1, r2);
        if (coder::internal::ifWhileCond(r2)) {
          // Check if all were confirmed
          fLock = true;
        }
        // We only ever release if we are in softlock mode and
        // only do so in that case if we are no longer confirming
        // pulses.
        if (coder::internal::c_strcmp(&Config.contents.opMode)) {
          qY = r2.size(0);
          n = r2.size(0);
          for (q1 = 0; q1 < n; q1++) {
            tmp_data = !r2[q1];
          }
          b_tmp_data.set(&tmp_data, qY);
          if (coder::internal::ifWhileCond(b_tmp_data)) {
            fLock = false;
          }
        }
        // Decide when/how the priori is updated for the next
        // segment's processing.
        if (coder::internal::ifWhileCond(r2) &&
            ((mode == 'C') || (mode == 'T'))) {
          ps_pre_struc_pl.set_size(1, b_X.ps_pos->pl.size(1));
          n = b_X.ps_pos->pl.size(0) * b_X.ps_pos->pl.size(1) - 1;
          for (q1 = 0; q1 <= n; q1++) {
            ps_pre_struc_pl[q1] = b_X.ps_pos->pl[q1];
          }
          b_X.ps_pos->updateposteriori(ps_pre_struc_pl);
          if (trackedCount > 5.0) {
            trackedCount = 0.0;
            ps_pre_struc_pl.set_size(1, b_X.ps_pos->pl.size(1));
            n = b_X.ps_pos->pl.size(0) * b_X.ps_pos->pl.size(1) - 1;
            for (q1 = 0; q1 <= n; q1++) {
              ps_pre_struc_pl[q1] = b_X.ps_pos->pl[q1];
            }
            b_X.ps_pos->updateposteriori(b_X.ps_pre, ps_pre_struc_pl);
          }
        }
        // Check lagging processing
        if ((segmentsProcessed != 0.0) && (Config.contents.K > 1.0) &&
            (missingTime >
             0.9 * sampsForKPulses.contents / Config.contents.Fs)) {
          missingTime = Config.contents.K - 1.0;
          Config.contents.K--;
          missingTime = std::round(missingTime);
          if (missingTime < 4.294967296E+9) {
            varargin_1 = static_cast<unsigned int>(missingTime);
          } else {
            varargin_1 = MAX_uint32_T;
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
        t5_t_0 = b_X.ps_pos->t_p;
        t5_t_f = b_X.ps_pos->t_ip;
        t5_fp = b_X.ps_pos->t_ipu;
        t5_fstart = b_X.ps_pos->t_ipj;
        t5_fend = b_X.ps_pos->fp;
        ps_pre_struc_fstart = b_X.ps_pos->fstart;
        ps_pre_struc_fend = b_X.ps_pos->fend;
        ps_pre_struc_tmplt[0] = b_X.ps_pos->tmplt[0];
        ps_pre_struc_tmplt[1] = b_X.ps_pos->tmplt[1];
        mode = b_X.ps_pos->mode;
        ps_pre_struc_pl.set_size(1, b_X.ps_pos->pl.size(1));
        n = b_X.ps_pos->pl.size(1);
        for (q1 = 0; q1 < n; q1++) {
          ps_pre_struc_pl[q1] = b_X.ps_pos->pl[q1];
        }
        ps_pre_struc_clst.set_size(b_X.ps_pos->clst.size(0),
                                   b_X.ps_pos->clst.size(1));
        n = b_X.ps_pos->clst.size(0) * b_X.ps_pos->clst.size(1);
        for (q1 = 0; q1 < n; q1++) {
          ps_pre_struc_clst[q1] = b_X.ps_pos->clst[q1];
        }
        ps_pre_struc_cmsk.set_size(b_X.ps_pos->cmsk.size(0),
                                   b_X.ps_pos->cmsk.size(1));
        n = b_X.ps_pos->cmsk.size(0) * b_X.ps_pos->cmsk.size(1);
        for (q1 = 0; q1 < n; q1++) {
          ps_pre_struc_cmsk[q1] = b_X.ps_pos->cmsk[q1];
        }
        ps_pre_struc_cpki.set_size(b_X.ps_pos->cpki.size(0),
                                   b_X.ps_pos->cpki.size(1));
        n = b_X.ps_pos->cpki.size(0) * b_X.ps_pos->cpki.size(1);
        for (q1 = 0; q1 < n; q1++) {
          ps_pre_struc_cpki[q1] = b_X.ps_pos->cpki[q1];
        }
        updatebufferreadvariables(&Config, &stftOverlapFraction,
                                  &overlapSamples, &sampsForKPulses,
                                  b_X.ps_pos);
        missingPackets = coder::toc();
        printf("complete. Elapsed time: %f seconds \n", missingPackets);
        fflush(stdout);
        // Deal with detected pulses
        // Xhold{mod(segmentsProcessed,maxSegments)} = X;%Keep a maxSegments
        // running record of waveforms for debugging in Matlab Xstruct =
        // obj2structrecursive(X); Xhold = X;
        Xhold = waveformcopy(&b_X, &lobj_9, &lobj_10[0], &lobj_11);
        q1 = ps_pre_struc_pl.size(1);
        for (n = 0; n < q1; n++) {
          float pulseInfo[3];
          printf("Pulse at %e Hz detected. SNR: %e Confirmation status: %u \n",
                 ps_pre_struc_pl[n].fp, ps_pre_struc_pl[n].SNR,
                 static_cast<unsigned int>(ps_pre_struc_pl[n].con_dec));
          fflush(stdout);
          pulseInfo[0] = static_cast<float>(ps_pre_struc_pl[n].SNR);
          pulseInfo[1] = ps_pre_struc_pl[n].con_dec;
          pulseInfo[2] = static_cast<float>(ps_pre_struc_pl[n].t_0);
          udpSenderSend(udpSender, &pulseInfo[0]);
        }
        c_varargin_1.set_size(1, 2);
        c_varargin_1[0] = mode;
        c_varargin_1[1] = '\x00';
        printf("Current Mode: %s\n", &c_varargin_1[0]);
        fflush(stdout);
        printf("====================================\n");
        fflush(stdout);
      }
    }
  } while (exitg1 == 0);
}

//
// File trailer for uavrt_detection.cpp
//
// [EOF]
//
