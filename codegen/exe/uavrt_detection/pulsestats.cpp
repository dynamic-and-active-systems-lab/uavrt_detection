//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: pulsestats.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "pulsestats.h"
#include "blockedSummation.h"
#include "diff.h"
#include "horzcatStructList.h"
#include "ifWhileCond.h"
#include "mean.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_internal_types.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "validator_check_size.h"
#include "coder_array.h"
#include "omp.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>

// Variable Definitions
static rtEqualityCheckInfo emlrtECI{
    2,                      // nDims
    145,                    // lineNo
    "pulsestats/pulsestats" // fName
};

static rtBoundsCheckInfo w_emlrtBCI{
    226,                          // lineNo
    "ps_pre.pl",                  // aName
    "pulsestats/updateposteriori" // fName
};

// Function Declarations
static void rtDimSizeGeqError(const int aDim2,
                              const rtEqualityCheckInfo &aInfo);

// Function Definitions
//
// Arguments    : const int aDim2
//                const rtEqualityCheckInfo &aInfo
// Return Type  : void
//
static void rtDimSizeGeqError(const int aDim2, const rtEqualityCheckInfo &aInfo)
{
  std::string errMsg;
  std::stringstream outStream;
  ((((((outStream << "Size overflow error on dimension ") << aInfo.nDims)
      << ": upper bound is ")
     << 1)
    << ", but actual size is ")
   << aDim2)
      << ".";
  outStream << "\n";
  ((((outStream << "Error in ") << aInfo.fName) << " (line ") << aInfo.lineNo)
      << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// PULSESTATS Constructs an instance of this class
//
// INPUTS:
//    tp      1x1     Duration of pulse (second)
//    tip     1x1     Inter-pulse time (seconds)
//    tipu    1x1     Inter-pulse time uncertainty (seconds)
//    tipj    1x1     Inter-pulse time jitter (deviations from means) (seconds)
//    fp      1x1     Pulses' center frequency (Hz) (if known)
//    fstart  1x1     Lower frequency bound pulses' center frequency (Hz) (if
//    known) fend    1x1     Upper frequency bound pulses' center frequency (Hz)
//    (if known) tmplt   1xn     Pulse template. See properies for
//                    definition. Usually set to [1 1] for
//                    square pulse.
//    pl      px1     Vector of pulse objects in waveform (if
//                    known). If unknown enter a blank pulse made
//                    from the contstructor "pulse";
//  Note: Unknown inputs should be set to NaN.
//
// OUTPUTS:
//    pulsestats object
//
//             %%
//
// Arguments    : double tp
//                double tip
//                double tipu
//                double tipj
//                double b_fp
//                double b_fstart
//                double b_fend
//                const double b_tmplt[2]
//                char b_mode
//                const coder::array<c_struct_T, 2U> &b_pl
//                const coder::array<c_struct_T, 2U> &b_clst
//                const coder::array<boolean_T, 2U> &b_cmsk
//                const coder::array<double, 2U> &b_cpki
// Return Type  : pulsestats *
//
pulsestats *pulsestats::b_init(double tp, double tip, double tipu, double tipj,
                               double b_fp, double b_fstart, double b_fend,
                               const double b_tmplt[2], char b_mode,
                               const coder::array<c_struct_T, 2U> &b_pl,
                               const coder::array<c_struct_T, 2U> &b_clst,
                               const coder::array<boolean_T, 2U> &b_cmsk,
                               const coder::array<double, 2U> &b_cpki)
{
  pulsestats *obj;
  coder::array<c_struct_T, 2U> val;
  int loop_ub;
  obj = this;
  if (std::isnan(tp) || std::isnan(tip) || std::isnan(tipu) ||
      std::isnan(tipj)) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  obj->t_p = tp;
  obj->t_ip = tip;
  obj->t_ipu = tipu;
  obj->t_ipj = tipj;
  obj->fp = b_fp;
  obj->fstart = b_fstart;
  obj->fend = b_fend;
  obj->tmplt[0] = b_tmplt[0];
  obj->tmplt[1] = b_tmplt[1];
  obj->mode = b_mode;
  // The following are variable sized properties. To tell coder
  // that they may vary setup as a local variable size variable
  // first, then set.
  // Instructions on
  // https://www.mathworks.com/help/simulink/ug/how-working-with-matlab-classes-is-different-for-code-generation.html
  // localMode = mode;
  // coder.varsize('localMode',[1 inf],[0 1]); %dims 0 if fixed, 1 if variable
  if (b_cpki.size(1) > 1) {
    rtDimSizeGeqError(b_cpki.size(1), emlrtECI);
  }
  // Tell coder these are variable size.
  // Now actually assign them
  loop_ub = b_pl.size(1);
  val.set_size(1, b_pl.size(1));
  for (int i{0}; i < loop_ub; i++) {
    val[i] = b_pl[i];
  }
  coder::internal::validator_check_size(val);
  obj->pl.set_size(1, obj->pl.size(1));
  loop_ub = val.size(1);
  obj->pl.set_size(obj->pl.size(0), val.size(1));
  for (int i{0}; i < loop_ub; i++) {
    obj->pl[i] = val[i];
  }
  obj->clst.set_size(b_clst.size(0), b_clst.size(1));
  loop_ub = b_clst.size(0) * b_clst.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->clst[i] = b_clst[i];
  }
  obj->cmsk.set_size(b_cmsk.size(0), b_cmsk.size(1));
  loop_ub = b_cmsk.size(0) * b_cmsk.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->cmsk[i] = b_cmsk[i];
  }
  obj->cpki.set_size(b_cpki.size(0), b_cpki.size(1));
  loop_ub = b_cpki.size(0) * b_cpki.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->cpki[i] = b_cpki[i];
  }
  return obj;
}

//
// UPDATEPOSTERIORI updates the posteriori pulse statistics
// object using the new pulse list (input), prior pulse stats
// and the waveforms power spectral density vector. This
// methods is typically going to be called on a posteriori pulse
// stats object after a waveform has been processed and a set
// of candidate pulses found. This method uses those pulses and
// the prior information about the pulses to update the
// posteriori pulse stats.
//
// The pulse contained in the waveform's ps_pos
// property is not used directly so that the caller can decide
// which pulses on which to focus the posteriori updates
//
//  updateType    What parts of the pulsestats to update. Valid
//                options are 'time', 'freq', 'timeandfreq'. The
//                'time' option will only update the interpulse
//                time statistics. The 'freq' option will only
//                update the frequency stats. The 'timeandfreq'
//                option will update both.
//
//
// Arguments    : const pulsestats *ps_pre
//                const coder::array<c_struct_T, 2U> &pulselist
// Return Type  : void
//
void pulsestats::b_updateposteriori(
    const pulsestats *ps_pre, const coder::array<c_struct_T, 2U> &pulselist)
{
  coder::array<double, 2U> b_pulselist;
  coder::array<double, 2U> b_varargin_1;
  coder::array<double, 2U> recent_tip;
  coder::array<double, 2U> varargin_1;
  coder::array<double, 1U> x;
  coder::array<boolean_T, 2U> b_recent_tip;
  coder::array<boolean_T, 2U> b_recent_tip_data;
  boolean_T recent_tip_data;
  if (pulselist.size(1) != 0) {
    double x_tmp;
    int i;
    int input_sizes_idx_0;
    coder::internal::e_horzcatStructList(pulselist, varargin_1);
    input_sizes_idx_0 = varargin_1.size(1);
    coder::internal::e_horzcatStructList(pulselist, varargin_1);
    //  pulselist(:).t_0]'
    coder::internal::c_horzcatStructList(pulselist, b_pulselist);
    // pulselist(:).fp
    // Fix the bandwidth in the priori to +/- 100 Hz.
    // Here is where we update the stats. These methods of updates
    // could be improved in the future.
    if (pulselist.size(1) == 1) {
      boolean_T guard1;
      //  Happens if K=1
      // We only have one pulse to reference, so we need to check
      // the prior pulse too.
      guard1 = false;
      if (ps_pre->pl.size(1) != 0) {
        i = ps_pre->pl.size(1);
        if (i < 1) {
          rtDynamicBoundsError(i, 1, i, w_emlrtBCI);
        }
        x_tmp = ps_pre->pl[i - 1].t_0;
        if (!std::isnan(x_tmp)) {
          recent_tip.set_size(1, 1);
          recent_tip[0] = pulselist[0].t_0 - x_tmp;
          // recent_tip =
          // pulselist.t_0-ps_pre.pl(end).t_0;%Conflicts with
          // Coder. Needed the (1) callout
          // There could be a case where the last segment and this
          // segement identified the same pulse. In this case
          // recent_tip will be very small. In this case, we just
          // say we learned nothing about t_ip in this segment.
          recent_tip_data = (recent_tip[0] < ps_pre->t_ipu + ps_pre->t_ipj);
          b_recent_tip_data.set(&recent_tip_data, 1, 1);
          if (coder::internal::b_ifWhileCond(b_recent_tip_data)) {
            recent_tip.set_size(1, 1);
            recent_tip[0] = rtNaN;
          }
        } else {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }
      if (guard1) {
        // No new information because we don't know the last
        // pulse time
        recent_tip.set_size(1, 1);
        recent_tip[0] = rtNaN;
      }
    } else {
      b_varargin_1.set_size(input_sizes_idx_0, 1);
      for (i = 0; i < input_sizes_idx_0; i++) {
        b_varargin_1[i] = varargin_1[i];
      }
      coder::diff(b_varargin_1, recent_tip);
    }
    // Do a check here to make sure the new tip isn't a huge change.
    // This could potentially happen if we are in the K = 1 case and
    // the block getting processed contained two pulses, with the
    // latter pulse getting identified/detected. The lines above
    // would look back to the last identified pulse and it might be
    // 2*tip back in time, producing a very large recenttip values.
    // If something like this happens, we ignore it so it doesn't
    // affect our new tip estimates.
    x_tmp = 1.5 * ps_pre->t_ip;
    input_sizes_idx_0 = recent_tip.size(0);
    b_recent_tip.set_size(recent_tip.size(0), 1);
    for (i = 0; i < input_sizes_idx_0; i++) {
      b_recent_tip[i] = (recent_tip[i] > x_tmp);
    }
    if (coder::internal::b_ifWhileCond(b_recent_tip)) {
      x_tmp = 0.5 * ps_pre->t_ip;
      b_recent_tip.set_size(recent_tip.size(0), 1);
      for (i = 0; i < input_sizes_idx_0; i++) {
        b_recent_tip[i] = (recent_tip[i] < x_tmp);
      }
      if (coder::internal::b_ifWhileCond(b_recent_tip)) {
        recent_tip.set_size(1, 1);
        recent_tip[0] = rtNaN;
      }
    }
    if (recent_tip.size(0) != 0) {
      input_sizes_idx_0 = recent_tip.size(0);
    } else {
      input_sizes_idx_0 = 0;
    }
    x.set_size(input_sizes_idx_0 + 1);
    for (i = 0; i < input_sizes_idx_0; i++) {
      x[i] = recent_tip[i];
    }
    x[input_sizes_idx_0] = ps_pre->t_ip;
    x_tmp = coder::colMajorFlatIter(x, x.size(0), input_sizes_idx_0);
    t_ip = x_tmp / static_cast<double>(input_sizes_idx_0);
    t_ipu = ps_pre->t_ipu;
    // Don't update this because it can get too
    // narrow.%mean([3*std(diff(t_found));wfm.ps_pre.t_ipu]);
    t_ipj = ps_pre->t_ipj;
  }
}

//
// PULSESTATS Constructs an instance of this class
//
// INPUTS:
//    tp      1x1     Duration of pulse (second)
//    tip     1x1     Inter-pulse time (seconds)
//    tipu    1x1     Inter-pulse time uncertainty (seconds)
//    tipj    1x1     Inter-pulse time jitter (deviations from means) (seconds)
//    fp      1x1     Pulses' center frequency (Hz) (if known)
//    fstart  1x1     Lower frequency bound pulses' center frequency (Hz) (if
//    known) fend    1x1     Upper frequency bound pulses' center frequency (Hz)
//    (if known) tmplt   1xn     Pulse template. See properies for
//                    definition. Usually set to [1 1] for
//                    square pulse.
//    pl      px1     Vector of pulse objects in waveform (if
//                    known). If unknown enter a blank pulse made
//                    from the contstructor "pulse";
//  Note: Unknown inputs should be set to NaN.
//
// OUTPUTS:
//    pulsestats object
//
//             %%
//
// Arguments    : double tp
//                double tip
//                double tipu
//                double tipj
//                double b_fp
//                double b_fstart
//                double b_fend
//                const double b_tmplt[2]
//                const char mode_data[]
//                const coder::array<c_struct_T, 2U> &b_pl
//                const coder::array<c_struct_T, 2U> &b_clst
//                const coder::array<boolean_T, 2U> &b_cmsk
//                const coder::array<double, 2U> &b_cpki
// Return Type  : pulsestats *
//
pulsestats *pulsestats::c_init(double tp, double tip, double tipu, double tipj,
                               double b_fp, double b_fstart, double b_fend,
                               const double b_tmplt[2], const char mode_data[],
                               const coder::array<c_struct_T, 2U> &b_pl,
                               const coder::array<c_struct_T, 2U> &b_clst,
                               const coder::array<boolean_T, 2U> &b_cmsk,
                               const coder::array<double, 2U> &b_cpki)
{
  pulsestats *obj;
  coder::array<c_struct_T, 2U> val;
  int loop_ub;
  obj = this;
  if (std::isnan(tp) || std::isnan(tip) || std::isnan(tipu) ||
      std::isnan(tipj)) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  obj->t_p = tp;
  obj->t_ip = tip;
  obj->t_ipu = tipu;
  obj->t_ipj = tipj;
  obj->fp = b_fp;
  obj->fstart = b_fstart;
  obj->fend = b_fend;
  obj->tmplt[0] = b_tmplt[0];
  obj->tmplt[1] = b_tmplt[1];
  obj->mode = mode_data[0];
  // The following are variable sized properties. To tell coder
  // that they may vary setup as a local variable size variable
  // first, then set.
  // Instructions on
  // https://www.mathworks.com/help/simulink/ug/how-working-with-matlab-classes-is-different-for-code-generation.html
  // localMode = mode;
  // coder.varsize('localMode',[1 inf],[0 1]); %dims 0 if fixed, 1 if variable
  if (b_cpki.size(1) > 1) {
    rtDimSizeGeqError(b_cpki.size(1), emlrtECI);
  }
  // Tell coder these are variable size.
  // Now actually assign them
  loop_ub = b_pl.size(1);
  val.set_size(1, b_pl.size(1));
  for (int i{0}; i < loop_ub; i++) {
    val[i] = b_pl[i];
  }
  coder::internal::validator_check_size(val);
  obj->pl.set_size(1, obj->pl.size(1));
  loop_ub = val.size(1);
  obj->pl.set_size(obj->pl.size(0), val.size(1));
  for (int i{0}; i < loop_ub; i++) {
    obj->pl[i] = val[i];
  }
  obj->clst.set_size(b_clst.size(0), b_clst.size(1));
  loop_ub = b_clst.size(0) * b_clst.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->clst[i] = b_clst[i];
  }
  obj->cmsk.set_size(b_cmsk.size(0), b_cmsk.size(1));
  loop_ub = b_cmsk.size(0) * b_cmsk.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->cmsk[i] = b_cmsk[i];
  }
  obj->cpki.set_size(b_cpki.size(0), b_cpki.size(1));
  loop_ub = b_cpki.size(0) * b_cpki.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->cpki[i] = b_cpki[i];
  }
  return obj;
}

//
// PULSESTATS Constructs an instance of this class
//
// INPUTS:
//    tp      1x1     Duration of pulse (second)
//    tip     1x1     Inter-pulse time (seconds)
//    tipu    1x1     Inter-pulse time uncertainty (seconds)
//    tipj    1x1     Inter-pulse time jitter (deviations from means) (seconds)
//    fp      1x1     Pulses' center frequency (Hz) (if known)
//    fstart  1x1     Lower frequency bound pulses' center frequency (Hz) (if
//    known) fend    1x1     Upper frequency bound pulses' center frequency (Hz)
//    (if known) tmplt   1xn     Pulse template. See properies for
//                    definition. Usually set to [1 1] for
//                    square pulse.
//    pl      px1     Vector of pulse objects in waveform (if
//                    known). If unknown enter a blank pulse made
//                    from the contstructor "pulse";
//  Note: Unknown inputs should be set to NaN.
//
// OUTPUTS:
//    pulsestats object
//
//             %%
//
// Arguments    : double tp
//                double tip
//                double tipu
//                double tipj
//                const c_struct_T &b_pl
//                const c_struct_T &b_clst
// Return Type  : pulsestats *
//
pulsestats *pulsestats::init(double tp, double tip, double tipu, double tipj,
                             const c_struct_T &b_pl, const c_struct_T &b_clst)
{
  pulsestats *obj;
  coder::array<c_struct_T, 2U> val;
  int loop_ub;
  obj = this;
  if (std::isnan(tp) || std::isnan(tip) || std::isnan(tipu) ||
      std::isnan(tipj)) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  obj->t_p = tp;
  obj->t_ip = tip;
  obj->t_ipu = tipu;
  obj->t_ipj = tipj;
  obj->fp = 0.0;
  obj->fstart = 0.0;
  obj->fend = 0.0;
  obj->tmplt[0] = 1.0;
  obj->tmplt[1] = 1.0;
  obj->mode = 'D';
  // The following are variable sized properties. To tell coder
  // that they may vary setup as a local variable size variable
  // first, then set.
  // Instructions on
  // https://www.mathworks.com/help/simulink/ug/how-working-with-matlab-classes-is-different-for-code-generation.html
  // localMode = mode;
  // coder.varsize('localMode',[1 inf],[0 1]); %dims 0 if fixed, 1 if variable
  // Tell coder these are variable size.
  // Now actually assign them
  val.set_size(1, 1);
  val[0] = b_pl;
  coder::internal::validator_check_size(val);
  obj->pl.set_size(1, obj->pl.size(1));
  loop_ub = val.size(1);
  obj->pl.set_size(obj->pl.size(0), val.size(1));
  for (int i{0}; i < loop_ub; i++) {
    obj->pl[i] = val[i];
  }
  obj->clst.set_size(1, 1);
  obj->clst[0] = b_clst;
  obj->cmsk.set_size(0, 0);
  obj->cpki.set_size(0, 0);
  return obj;
}

//
// PULSESTATS Constructs an instance of this class
//
// INPUTS:
//    tp      1x1     Duration of pulse (second)
//    tip     1x1     Inter-pulse time (seconds)
//    tipu    1x1     Inter-pulse time uncertainty (seconds)
//    tipj    1x1     Inter-pulse time jitter (deviations from means) (seconds)
//    fp      1x1     Pulses' center frequency (Hz) (if known)
//    fstart  1x1     Lower frequency bound pulses' center frequency (Hz) (if
//    known) fend    1x1     Upper frequency bound pulses' center frequency (Hz)
//    (if known) tmplt   1xn     Pulse template. See properies for
//                    definition. Usually set to [1 1] for
//                    square pulse.
//    pl      px1     Vector of pulse objects in waveform (if
//                    known). If unknown enter a blank pulse made
//                    from the contstructor "pulse";
//  Note: Unknown inputs should be set to NaN.
//
// OUTPUTS:
//    pulsestats object
//
//             %%
//
// Arguments    : double tp
//                double tip
//                double tipu
//                double tipj
//                double b_fp
//                double b_fstart
//                double b_fend
//                const c_struct_T &b_pl
//                const c_struct_T &b_clst
// Return Type  : pulsestats *
//
pulsestats *pulsestats::init(double tp, double tip, double tipu, double tipj,
                             double b_fp, double b_fstart, double b_fend,
                             const c_struct_T &b_pl, const c_struct_T &b_clst)
{
  pulsestats *obj;
  coder::array<c_struct_T, 2U> val;
  int loop_ub;
  obj = this;
  if (std::isnan(tp) || std::isnan(tip) || std::isnan(tipu) ||
      std::isnan(tipj)) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  obj->t_p = tp;
  obj->t_ip = tip;
  obj->t_ipu = tipu;
  obj->t_ipj = tipj;
  obj->fp = b_fp;
  obj->fstart = b_fstart;
  obj->fend = b_fend;
  obj->tmplt[0] = 1.0;
  obj->tmplt[1] = 1.0;
  obj->mode = 'D';
  // The following are variable sized properties. To tell coder
  // that they may vary setup as a local variable size variable
  // first, then set.
  // Instructions on
  // https://www.mathworks.com/help/simulink/ug/how-working-with-matlab-classes-is-different-for-code-generation.html
  // localMode = mode;
  // coder.varsize('localMode',[1 inf],[0 1]); %dims 0 if fixed, 1 if variable
  // Tell coder these are variable size.
  // Now actually assign them
  val.set_size(1, 1);
  val[0] = b_pl;
  coder::internal::validator_check_size(val);
  obj->pl.set_size(1, obj->pl.size(1));
  loop_ub = val.size(1);
  obj->pl.set_size(obj->pl.size(0), val.size(1));
  for (int i{0}; i < loop_ub; i++) {
    obj->pl[i] = val[i];
  }
  obj->clst.set_size(1, 1);
  obj->clst[0] = b_clst;
  obj->cmsk.set_size(1, 1);
  obj->cmsk[0] = false;
  obj->cpki.set_size(1, 1);
  obj->cpki[0] = rtNaN;
  return obj;
}

//
// UPDATEPOSTERIORI updates the posteriori pulse statistics
// object using the new pulse list (input), prior pulse stats
// and the waveforms power spectral density vector. This
// methods is typically going to be called on a posteriori pulse
// stats object after a waveform has been processed and a set
// of candidate pulses found. This method uses those pulses and
// the prior information about the pulses to update the
// posteriori pulse stats.
//
// The pulse contained in the waveform's ps_pos
// property is not used directly so that the caller can decide
// which pulses on which to focus the posteriori updates
//
//  updateType    What parts of the pulsestats to update. Valid
//                options are 'time', 'freq', 'timeandfreq'. The
//                'time' option will only update the interpulse
//                time statistics. The 'freq' option will only
//                update the frequency stats. The 'timeandfreq'
//                option will update both.
//
//
// Arguments    : const pulsestats *ps_pre
//                const coder::array<c_struct_T, 2U> &pulselist
// Return Type  : void
//
void pulsestats::updateposteriori(const pulsestats *ps_pre,
                                  const coder::array<c_struct_T, 2U> &pulselist)
{
  static rtBoundsCheckInfo ab_emlrtBCI{
      227,                          // lineNo
      "ps_pre.pl",                  // aName
      "pulsestats/updateposteriori" // fName
  };
  coder::array<double, 2U> b_varargin_1;
  coder::array<double, 2U> c_varargin_1;
  coder::array<double, 2U> recent_tip;
  coder::array<double, 2U> varargin_1;
  coder::array<boolean_T, 2U> b_recent_tip;
  coder::array<boolean_T, 2U> b_recent_tip_data;
  boolean_T recent_tip_data;
  if (pulselist.size(1) != 0) {
    double d;
    double freq_found;
    int i;
    int size_tmp_idx_1;
    coder::internal::e_horzcatStructList(pulselist, varargin_1);
    size_tmp_idx_1 = varargin_1.size(1);
    coder::internal::e_horzcatStructList(pulselist, varargin_1);
    //  pulselist(:).t_0]'
    coder::internal::c_horzcatStructList(pulselist, b_varargin_1);
    freq_found = coder::mean(b_varargin_1);
    // pulselist(:).fp
    // Fix the bandwidth in the priori to +/- 100 Hz.
    // Here is where we update the stats. These methods of updates
    // could be improved in the future.
    if (pulselist.size(1) == 1) {
      boolean_T guard1;
      //  Happens if K=1
      // We only have one pulse to reference, so we need to check
      // the prior pulse too.
      guard1 = false;
      if (ps_pre->pl.size(1) != 0) {
        i = ps_pre->pl.size(1);
        size_tmp_idx_1 = ps_pre->pl.size(1);
        if ((size_tmp_idx_1 < 1) || (size_tmp_idx_1 > i)) {
          rtDynamicBoundsError(size_tmp_idx_1, 1, i, w_emlrtBCI);
        }
        if (!std::isnan(ps_pre->pl[size_tmp_idx_1 - 1].t_0)) {
          recent_tip.set_size(1, 1);
          i = ps_pre->pl.size(1);
          size_tmp_idx_1 = ps_pre->pl.size(1);
          if ((size_tmp_idx_1 < 1) || (size_tmp_idx_1 > i)) {
            rtDynamicBoundsError(size_tmp_idx_1, 1, i, ab_emlrtBCI);
          }
          recent_tip[0] = pulselist[0].t_0 - ps_pre->pl[size_tmp_idx_1 - 1].t_0;
          // recent_tip =
          // pulselist.t_0-ps_pre.pl(end).t_0;%Conflicts with
          // Coder. Needed the (1) callout
          // There could be a case where the last segment and this
          // segement identified the same pulse. In this case
          // recent_tip will be very small. In this case, we just
          // say we learned nothing about t_ip in this segment.
          recent_tip_data = (recent_tip[0] < ps_pre->t_ipu + ps_pre->t_ipj);
          b_recent_tip_data.set(&recent_tip_data, 1, 1);
          if (coder::internal::b_ifWhileCond(b_recent_tip_data)) {
            recent_tip.set_size(1, 1);
            recent_tip[0] = rtNaN;
          }
        } else {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }
      if (guard1) {
        // No new information because we don't know the last
        // pulse time
        recent_tip.set_size(1, 1);
        recent_tip[0] = rtNaN;
      }
    } else {
      c_varargin_1.set_size(size_tmp_idx_1, 1);
      for (i = 0; i < size_tmp_idx_1; i++) {
        c_varargin_1[i] = varargin_1[i];
      }
      coder::diff(c_varargin_1, recent_tip);
    }
    // Do a check here to make sure the new tip isn't a huge change.
    // This could potentially happen if we are in the K = 1 case and
    // the block getting processed contained two pulses, with the
    // latter pulse getting identified/detected. The lines above
    // would look back to the last identified pulse and it might be
    // 2*tip back in time, producing a very large recenttip values.
    // If something like this happens, we ignore it so it doesn't
    // affect our new tip estimates.
    d = 1.5 * ps_pre->t_ip;
    size_tmp_idx_1 = recent_tip.size(0);
    b_recent_tip.set_size(recent_tip.size(0), 1);
    for (i = 0; i < size_tmp_idx_1; i++) {
      b_recent_tip[i] = (recent_tip[i] > d);
    }
    if (coder::internal::b_ifWhileCond(b_recent_tip)) {
      d = 0.5 * ps_pre->t_ip;
      b_recent_tip.set_size(recent_tip.size(0), 1);
      for (i = 0; i < size_tmp_idx_1; i++) {
        b_recent_tip[i] = (recent_tip[i] < d);
      }
      coder::internal::b_ifWhileCond(b_recent_tip);
    }
    // nanmean([freq_found;wfm.ps_pre.fp]);%Previous fc may be nan if unknown
    fp = freq_found;
    fstart = freq_found - 100.0;
    fend = freq_found + 100.0;
  }
}

//
// File trailer for pulsestats.cpp
//
// [EOF]
//
