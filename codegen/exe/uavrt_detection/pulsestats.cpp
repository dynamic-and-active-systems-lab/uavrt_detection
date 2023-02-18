//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: pulsestats.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 18-Feb-2023 14:54:54
//

// Include Files
#include "pulsestats.h"
#include "blockedSummation.h"
#include "diff.h"
#include "eml_int_forloop_overflow_check.h"
#include "horzcatStructList.h"
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
#include <string.h>
#include <string>

// Variable Definitions
static rtEqualityCheckInfo emlrtECI{
    2,                                         // nDims
    148,                                       // lineNo
    17,                                        // colNo
    "pulsestats/pulsestats",                   // fName
    "H:\\repos\\uavrt_detection\\pulsestats.m" // pName
};

static rtBoundsCheckInfo cb_emlrtBCI{
    -1,                                         // iFirst
    -1,                                         // iLast
    245,                                        // lineNo
    64,                                         // colNo
    "ps_pre.pl",                                // aName
    "pulsestats/updateposteriori",              // fName
    "H:\\repos\\uavrt_detection\\pulsestats.m", // pName
    0                                           // checkKind
};

static rtBoundsCheckInfo db_emlrtBCI{
    -1,                                         // iFirst
    -1,                                         // iLast
    246,                                        // lineNo
    25,                                         // colNo
    "ps_pre.pl",                                // aName
    "pulsestats/updateposteriori",              // fName
    "H:\\repos\\uavrt_detection\\pulsestats.m", // pName
    0                                           // checkKind
};

// Function Declarations
static void rtDimSizeGeqError(const int aDim2,
                              const rtEqualityCheckInfo *aInfo);

// Function Definitions
//
// Arguments    : const int aDim2
//                const rtEqualityCheckInfo *aInfo
// Return Type  : void
//
static void rtDimSizeGeqError(const int aDim2, const rtEqualityCheckInfo *aInfo)
{
  std::string errMsg;
  std::stringstream outStream;
  ((((((outStream << "Size overflow error on dimension ") << aInfo->nDims)
      << ": upper bound is ")
     << 1)
    << ", but actual size is ")
   << aDim2)
      << ".";
  outStream << "\n";
  ((((outStream << "Error in ") << aInfo->fName) << " (line ") << aInfo->lineNo)
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
  coder::array<c_struct_T, 2U> _in;
  coder::array<c_struct_T, 2U> val;
  coder::array<double, 2U> localCpki;
  coder::array<boolean_T, 2U> b_val;
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
    rtDimSizeGeqError(b_cpki.size(1), &emlrtECI);
  }
  // Tell coder these are variable size.
  // Now actually assign them
  coder::internal::validator_check_size(b_pl, _in);
  obj->pl.set_size(1, _in.size(1));
  loop_ub = _in.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->pl[i] = _in[i];
  }
  coder::internal::c_validator_check_size(b_clst, val);
  obj->clst.set_size(val.size(0), val.size(1));
  loop_ub = val.size(0) * val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->clst[i] = val[i];
  }
  coder::internal::d_validator_check_size(b_cmsk, b_val);
  obj->cmsk.set_size(b_val.size(0), b_val.size(1));
  loop_ub = b_val.size(0) * b_val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->cmsk[i] = b_val[i];
  }
  coder::internal::c_validator_check_size(b_cpki, localCpki);
  obj->cpki.set_size(localCpki.size(0), localCpki.size(1));
  loop_ub = localCpki.size(0) * localCpki.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->cpki[i] = localCpki[i];
  }
  return obj;
}

//
// %UPDATEPOSTERIORI updates the posteriori pulse statistics
//              object using the new pulse list (input), prior pulse stats
//              and the waveforms power spectral density vector. This
//              methods is typically going to be called on a posteriori pulse
//              stats object after a waveform has been processed and a set
//              of candidate pulses found. This method uses those pulses and
//              the prior information about the pulses to update the
//              posteriori pulse stats.
//
//              The pulse contained in the waveform's ps_pos
//              property is not used directly so that the caller can decide
//              which pulses on which to focus the posteriori updates
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
  coder::array<double, 1U> result;
  coder::array<boolean_T, 2U> b_recent_tip;
  coder::array<boolean_T, 2U> b_recent_tip_data;
  double x;
  int input_sizes_idx_1;
  boolean_T recent_tip_data;
  if (pulselist.size(1) != 0) {
    int i;
    boolean_T exitg1;
    boolean_T y;
    coder::internal::b_horzcatStructList(pulselist, varargin_1);
    if (varargin_1.size(1) != 0) {
      input_sizes_idx_1 = varargin_1.size(1);
    } else {
      input_sizes_idx_1 = 0;
    }
    coder::internal::b_horzcatStructList(pulselist, varargin_1);
    //  pulselist(:).t_0]'
    coder::internal::horzcatStructList(pulselist, b_pulselist);
    // pulselist(:).fp
    // Create a vector of bandwidths from the pulselist
    // fEnds   = [pulselist.fend];
    // fStarts = [pulselist.fstart];
    // bw_found = 2*(mean(fEnds,'all','omitnan')-mean(fStarts,'all','omitnan'));
    // if isempty(bw_found)
    //     bw_found = 100;
    //     if coder.target('MATLAB')
    //        warning(['UAV-R: No bandwidth could be calculated ',...
    //             'from the start and stop frequencies of the ',...
    //             'identified pulses. A bandwidth of 100 Hz ',...
    //             'will be used for continued informed search.'])
    //     end
    // end
    // Fix the bandwidth in the priori to +/- 100 Hz.
    // Here is where we update the stats. These methods of updates
    // could be improved in the future.
    // wfm.ps_pre.t_p; %tp doesn't change. We assume it is stationary
    if (pulselist.size(1) == 1) {
      boolean_T guard1{false};
      //  Happens if K=1
      // We only have one pulse to reference, so we need to check
      // the prior pulse too.
      y = (ps_pre->pl.size(1) == 0);
      guard1 = false;
      if (!y) {
        i = ps_pre->pl.size(1);
        input_sizes_idx_1 = ps_pre->pl.size(1);
        if ((input_sizes_idx_1 < 1) || (input_sizes_idx_1 > i)) {
          rtDynamicBoundsError(input_sizes_idx_1, 1, i, &cb_emlrtBCI);
        }
        x = ps_pre->pl[input_sizes_idx_1 - 1].t_0;
        if (!std::isnan(x)) {
          recent_tip.set_size(1, 1);
          i = ps_pre->pl.size(1);
          input_sizes_idx_1 = ps_pre->pl.size(1);
          if ((input_sizes_idx_1 < 1) || (input_sizes_idx_1 > i)) {
            rtDynamicBoundsError(input_sizes_idx_1, 1, i, &db_emlrtBCI);
          }
          recent_tip[0] =
              pulselist[0].t_0 - ps_pre->pl[input_sizes_idx_1 - 1].t_0;
          // recent_tip =
          // pulselist.t_0-ps_pre.pl(end).t_0;%Conflicts with
          // Coder. Needed the (1) callout
          // There could be a case where the last segment and this
          // segement identified the same pulse. In this case
          // recent_tip will be very small. In this case, we just
          // say we learned nothing about t_ip in this segment.
          x = ps_pre->t_ipu + ps_pre->t_ipj;
          recent_tip_data = (recent_tip[0] < x);
          b_recent_tip_data.set(&recent_tip_data, 1, 1);
          y = (b_recent_tip_data.size(0) != 0);
          if (y) {
            if (b_recent_tip_data.size(0) > 2147483646) {
              coder::check_forloop_overflow_error();
            }
            input_sizes_idx_1 = 0;
            exitg1 = false;
            while ((!exitg1) &&
                   (input_sizes_idx_1 <= b_recent_tip_data.size(0) - 1)) {
              if (!b_recent_tip_data[input_sizes_idx_1]) {
                y = false;
                exitg1 = true;
              } else {
                input_sizes_idx_1++;
              }
            }
          }
          if (y) {
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
      b_varargin_1.set_size(input_sizes_idx_1, 1);
      for (i = 0; i < input_sizes_idx_1; i++) {
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
    x = 1.5 * ps_pre->t_ip;
    b_recent_tip.set_size(recent_tip.size(0), 1);
    input_sizes_idx_1 = recent_tip.size(0);
    for (i = 0; i < input_sizes_idx_1; i++) {
      b_recent_tip[i] = (recent_tip[i] > x);
    }
    y = (b_recent_tip.size(0) != 0);
    if (y) {
      if (b_recent_tip.size(0) > 2147483646) {
        coder::check_forloop_overflow_error();
      }
      input_sizes_idx_1 = 0;
      exitg1 = false;
      while ((!exitg1) && (input_sizes_idx_1 <= b_recent_tip.size(0) - 1)) {
        if (!b_recent_tip[input_sizes_idx_1]) {
          y = false;
          exitg1 = true;
        } else {
          input_sizes_idx_1++;
        }
      }
    }
    if (y) {
      x = 0.5 * ps_pre->t_ip;
      b_recent_tip.set_size(recent_tip.size(0), 1);
      input_sizes_idx_1 = recent_tip.size(0);
      for (i = 0; i < input_sizes_idx_1; i++) {
        b_recent_tip[i] = (recent_tip[i] < x);
      }
      y = (b_recent_tip.size(0) != 0);
      if (y) {
        if (b_recent_tip.size(0) > 2147483646) {
          coder::check_forloop_overflow_error();
        }
        input_sizes_idx_1 = 0;
        exitg1 = false;
        while ((!exitg1) && (input_sizes_idx_1 <= b_recent_tip.size(0) - 1)) {
          if (!b_recent_tip[input_sizes_idx_1]) {
            y = false;
            exitg1 = true;
          } else {
            input_sizes_idx_1++;
          }
        }
      }
      if (y) {
        recent_tip.set_size(1, 1);
        recent_tip[0] = rtNaN;
      }
    }
    //                  %Only update time parameters if we are in tracking mode.
    //                  If we %aren't, we may have identified somethign that
    //                  isn't a pulse if strcmp(obj.mode,'T') ||
    //                  strcmp(ps_pre.mode,'T')
    //                      obj.t_ip  =
    //                      mean([recent_tip;ps_pre.t_ip],'omitnan'); obj.t_ipu
    //                      = ps_pre.t_ipu; %Don't update this because it can
    //                      get too
    //                      narrow.%mean([3*std(diff(t_found));wfm.ps_pre.t_ipu]);
    //                      obj.t_ipj = ps_pre.t_ipj;
    //                  end
    //                  fp_pos     =
    //                  freq_found;%nanmean([freq_found;wfm.ps_pre.fp]);%Previous
    //                  fc may be nan if unknown obj.fp     = fp_pos; obj.fstart
    //                  = fp_pos-bw_found/2; obj.fend   = fp_pos+bw_found/2;
    x = ps_pre->t_ip;
    if (recent_tip.size(0) != 0) {
      input_sizes_idx_1 = recent_tip.size(0);
    } else {
      input_sizes_idx_1 = 0;
    }
    result.set_size(input_sizes_idx_1 + 1);
    for (i = 0; i < input_sizes_idx_1; i++) {
      result[i] = recent_tip[i];
    }
    result[input_sizes_idx_1] = x;
    coder::colMajorFlatIter(result, result.size(0), &x, &input_sizes_idx_1);
    t_ip = x / static_cast<double>(input_sizes_idx_1);
    x = ps_pre->t_ipu;
    t_ipu = x;
    // Don't update this because it can get too
    // narrow.%mean([3*std(diff(t_found));wfm.ps_pre.t_ipu]);
    x = ps_pre->t_ipj;
    t_ipj = x;
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
  coder::array<c_struct_T, 2U> _in;
  coder::array<c_struct_T, 2U> val;
  coder::array<double, 2U> localCpki;
  coder::array<boolean_T, 2U> b_val;
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
    rtDimSizeGeqError(b_cpki.size(1), &emlrtECI);
  }
  // Tell coder these are variable size.
  // Now actually assign them
  coder::internal::validator_check_size(b_pl, _in);
  obj->pl.set_size(1, _in.size(1));
  loop_ub = _in.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->pl[i] = _in[i];
  }
  coder::internal::c_validator_check_size(b_clst, val);
  obj->clst.set_size(val.size(0), val.size(1));
  loop_ub = val.size(0) * val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->clst[i] = val[i];
  }
  coder::internal::d_validator_check_size(b_cmsk, b_val);
  obj->cmsk.set_size(b_val.size(0), b_val.size(1));
  loop_ub = b_val.size(0) * b_val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->cmsk[i] = b_val[i];
  }
  coder::internal::c_validator_check_size(b_cpki, localCpki);
  obj->cpki.set_size(localCpki.size(0), localCpki.size(1));
  loop_ub = localCpki.size(0) * localCpki.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->cpki[i] = localCpki[i];
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
//                const c_struct_T *b_pl
//                const c_struct_T *b_clst
// Return Type  : pulsestats *
//
pulsestats *pulsestats::init(double tp, double tip, double tipu, double tipj,
                             const c_struct_T *b_pl, const c_struct_T *b_clst)
{
  pulsestats *obj;
  coder::array<c_struct_T, 2U> _in;
  coder::array<c_struct_T, 2U> d_pl;
  coder::array<c_struct_T, 2U> e_pl;
  coder::array<c_struct_T, 2U> val;
  coder::array<double, 2U> b_cmsk;
  coder::array<double, 2U> b_val;
  coder::array<boolean_T, 2U> b__in;
  coder::array<boolean_T, 2U> cmsk_data;
  emxArray_struct_T_1x1 c_pl;
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
  c_pl.size[0] = 1;
  c_pl.size[1] = 1;
  c_pl.data[0] = *b_pl;
  d_pl.set(&c_pl.data[0], c_pl.size[0], c_pl.size[1]);
  coder::internal::validator_check_size(d_pl, _in);
  obj->pl.set_size(1, _in.size(1));
  loop_ub = _in.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->pl[i] = _in[i];
  }
  c_pl.size[0] = 1;
  c_pl.size[1] = 1;
  c_pl.data[0] = *b_clst;
  e_pl.set(&c_pl.data[0], c_pl.size[0], c_pl.size[1]);
  coder::internal::c_validator_check_size(e_pl, val);
  obj->clst.set_size(val.size(0), val.size(1));
  loop_ub = val.size(0) * val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->clst[i] = val[i];
  }
  cmsk_data.set(nullptr, 0, 0);
  coder::internal::d_validator_check_size(cmsk_data, b__in);
  obj->cmsk.set_size(b__in.size(0), b__in.size(1));
  loop_ub = b__in.size(0) * b__in.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->cmsk[i] = b__in[i];
  }
  b_cmsk.set(nullptr, 0, 0);
  coder::internal::c_validator_check_size(b_cmsk, b_val);
  obj->cpki.set_size(b_val.size(0), b_val.size(1));
  loop_ub = b_val.size(0) * b_val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->cpki[i] = b_val[i];
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
//                double b_fp
//                const c_struct_T *b_pl
//                const c_struct_T *b_clst
// Return Type  : pulsestats *
//
pulsestats *pulsestats::init(double tp, double tip, double tipu, double tipj,
                             double b_fp, const c_struct_T *b_pl,
                             const c_struct_T *b_clst)
{
  pulsestats *obj;
  coder::array<c_struct_T, 2U> _in;
  coder::array<c_struct_T, 2U> d_pl;
  coder::array<c_struct_T, 2U> e_pl;
  coder::array<c_struct_T, 2U> val;
  coder::array<double, 2U> c_val;
  coder::array<double, 2U> d_tmp_data;
  coder::array<boolean_T, 2U> b_tmp_data;
  coder::array<boolean_T, 2U> b_val;
  emxArray_struct_T_1x1 c_pl;
  double c_tmp_data;
  int loop_ub;
  boolean_T tmp_data;
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
  c_pl.size[0] = 1;
  c_pl.size[1] = 1;
  c_pl.data[0] = *b_pl;
  d_pl.set(&c_pl.data[0], c_pl.size[0], c_pl.size[1]);
  coder::internal::validator_check_size(d_pl, _in);
  obj->pl.set_size(1, _in.size(1));
  loop_ub = _in.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->pl[i] = _in[i];
  }
  c_pl.size[0] = 1;
  c_pl.size[1] = 1;
  c_pl.data[0] = *b_clst;
  e_pl.set(&c_pl.data[0], c_pl.size[0], c_pl.size[1]);
  coder::internal::c_validator_check_size(e_pl, val);
  obj->clst.set_size(val.size(0), val.size(1));
  loop_ub = val.size(0) * val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->clst[i] = val[i];
  }
  tmp_data = false;
  b_tmp_data.set(&tmp_data, 1, 1);
  coder::internal::d_validator_check_size(b_tmp_data, b_val);
  obj->cmsk.set_size(b_val.size(0), b_val.size(1));
  loop_ub = b_val.size(0) * b_val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->cmsk[i] = b_val[i];
  }
  c_tmp_data = rtNaN;
  d_tmp_data.set(&c_tmp_data, 1, 1);
  coder::internal::c_validator_check_size(d_tmp_data, c_val);
  obj->cpki.set_size(c_val.size(0), c_val.size(1));
  loop_ub = c_val.size(0) * c_val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->cpki[i] = c_val[i];
  }
  return obj;
}

//
// %UPDATEPOSTERIORI updates the posteriori pulse statistics
//              object using the new pulse list (input), prior pulse stats
//              and the waveforms power spectral density vector. This
//              methods is typically going to be called on a posteriori pulse
//              stats object after a waveform has been processed and a set
//              of candidate pulses found. This method uses those pulses and
//              the prior information about the pulses to update the
//              posteriori pulse stats.
//
//              The pulse contained in the waveform's ps_pos
//              property is not used directly so that the caller can decide
//              which pulses on which to focus the posteriori updates
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
  coder::array<double, 2U> b_varargin_1;
  coder::array<double, 2U> d_varargin_1;
  coder::array<double, 2U> recent_tip;
  coder::array<double, 2U> varargin_1;
  coder::array<boolean_T, 2U> b_recent_tip;
  coder::array<boolean_T, 2U> b_recent_tip_data;
  double y;
  int counts;
  boolean_T recent_tip_data;
  if (pulselist.size(1) != 0) {
    double freq_found;
    int b_input_sizes_idx_1;
    int input_sizes_idx_1;
    boolean_T b_y;
    boolean_T exitg1;
    coder::internal::b_horzcatStructList(pulselist, varargin_1);
    if (varargin_1.size(1) != 0) {
      input_sizes_idx_1 = varargin_1.size(1);
    } else {
      input_sizes_idx_1 = 0;
    }
    coder::internal::b_horzcatStructList(pulselist, varargin_1);
    //  pulselist(:).t_0]'
    coder::internal::horzcatStructList(pulselist, b_varargin_1);
    if (b_varargin_1.size(1) != 0) {
      b_input_sizes_idx_1 = b_varargin_1.size(1);
    } else {
      b_input_sizes_idx_1 = 0;
    }
    if (b_input_sizes_idx_1 == 0) {
      y = 0.0;
      counts = 0;
    } else {
      coder::array<double, 1U> c_varargin_1;
      c_varargin_1 = b_varargin_1.reshape(b_input_sizes_idx_1);
      coder::colMajorFlatIter(c_varargin_1, b_input_sizes_idx_1, &y, &counts);
    }
    freq_found = y / static_cast<double>(counts);
    // pulselist(:).fp
    // Create a vector of bandwidths from the pulselist
    // fEnds   = [pulselist.fend];
    // fStarts = [pulselist.fstart];
    // bw_found = 2*(mean(fEnds,'all','omitnan')-mean(fStarts,'all','omitnan'));
    // if isempty(bw_found)
    //     bw_found = 100;
    //     if coder.target('MATLAB')
    //        warning(['UAV-R: No bandwidth could be calculated ',...
    //             'from the start and stop frequencies of the ',...
    //             'identified pulses. A bandwidth of 100 Hz ',...
    //             'will be used for continued informed search.'])
    //     end
    // end
    // Fix the bandwidth in the priori to +/- 100 Hz.
    // Here is where we update the stats. These methods of updates
    // could be improved in the future.
    // wfm.ps_pre.t_p; %tp doesn't change. We assume it is stationary
    if (pulselist.size(1) == 1) {
      boolean_T guard1{false};
      //  Happens if K=1
      // We only have one pulse to reference, so we need to check
      // the prior pulse too.
      b_y = (ps_pre->pl.size(1) == 0);
      guard1 = false;
      if (!b_y) {
        counts = ps_pre->pl.size(1);
        b_input_sizes_idx_1 = ps_pre->pl.size(1);
        if ((b_input_sizes_idx_1 < 1) || (b_input_sizes_idx_1 > counts)) {
          rtDynamicBoundsError(b_input_sizes_idx_1, 1, counts, &cb_emlrtBCI);
        }
        y = ps_pre->pl[b_input_sizes_idx_1 - 1].t_0;
        if (!std::isnan(y)) {
          recent_tip.set_size(1, 1);
          counts = ps_pre->pl.size(1);
          b_input_sizes_idx_1 = ps_pre->pl.size(1);
          if ((b_input_sizes_idx_1 < 1) || (b_input_sizes_idx_1 > counts)) {
            rtDynamicBoundsError(b_input_sizes_idx_1, 1, counts, &db_emlrtBCI);
          }
          recent_tip[0] =
              pulselist[0].t_0 - ps_pre->pl[b_input_sizes_idx_1 - 1].t_0;
          // recent_tip =
          // pulselist.t_0-ps_pre.pl(end).t_0;%Conflicts with
          // Coder. Needed the (1) callout
          // There could be a case where the last segment and this
          // segement identified the same pulse. In this case
          // recent_tip will be very small. In this case, we just
          // say we learned nothing about t_ip in this segment.
          y = ps_pre->t_ipu + ps_pre->t_ipj;
          recent_tip_data = (recent_tip[0] < y);
          b_recent_tip_data.set(&recent_tip_data, 1, 1);
          b_y = (b_recent_tip_data.size(0) != 0);
          if (b_y) {
            if (b_recent_tip_data.size(0) > 2147483646) {
              coder::check_forloop_overflow_error();
            }
            b_input_sizes_idx_1 = 0;
            exitg1 = false;
            while ((!exitg1) &&
                   (b_input_sizes_idx_1 <= b_recent_tip_data.size(0) - 1)) {
              if (!b_recent_tip_data[b_input_sizes_idx_1]) {
                b_y = false;
                exitg1 = true;
              } else {
                b_input_sizes_idx_1++;
              }
            }
          }
          if (b_y) {
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
      d_varargin_1.set_size(input_sizes_idx_1, 1);
      for (counts = 0; counts < input_sizes_idx_1; counts++) {
        d_varargin_1[counts] = varargin_1[counts];
      }
      coder::diff(d_varargin_1, recent_tip);
    }
    // Do a check here to make sure the new tip isn't a huge change.
    // This could potentially happen if we are in the K = 1 case and
    // the block getting processed contained two pulses, with the
    // latter pulse getting identified/detected. The lines above
    // would look back to the last identified pulse and it might be
    // 2*tip back in time, producing a very large recenttip values.
    // If something like this happens, we ignore it so it doesn't
    // affect our new tip estimates.
    y = 1.5 * ps_pre->t_ip;
    b_recent_tip.set_size(recent_tip.size(0), 1);
    b_input_sizes_idx_1 = recent_tip.size(0);
    for (counts = 0; counts < b_input_sizes_idx_1; counts++) {
      b_recent_tip[counts] = (recent_tip[counts] > y);
    }
    b_y = (b_recent_tip.size(0) != 0);
    if (b_y) {
      if (b_recent_tip.size(0) > 2147483646) {
        coder::check_forloop_overflow_error();
      }
      b_input_sizes_idx_1 = 0;
      exitg1 = false;
      while ((!exitg1) && (b_input_sizes_idx_1 <= b_recent_tip.size(0) - 1)) {
        if (!b_recent_tip[b_input_sizes_idx_1]) {
          b_y = false;
          exitg1 = true;
        } else {
          b_input_sizes_idx_1++;
        }
      }
    }
    if (b_y) {
      y = 0.5 * ps_pre->t_ip;
      b_recent_tip.set_size(recent_tip.size(0), 1);
      b_input_sizes_idx_1 = recent_tip.size(0);
      for (counts = 0; counts < b_input_sizes_idx_1; counts++) {
        b_recent_tip[counts] = (recent_tip[counts] < y);
      }
      b_y = (b_recent_tip.size(0) != 0);
      if (b_y && (b_recent_tip.size(0) > 2147483646)) {
        coder::check_forloop_overflow_error();
      }
    } else {
      //                  %Only update time parameters if we are in tracking
      //                  mode. If we %aren't, we may have identified somethign
      //                  that isn't a pulse if strcmp(obj.mode,'T') ||
      //                  strcmp(ps_pre.mode,'T')
      //                      obj.t_ip  =
      //                      mean([recent_tip;ps_pre.t_ip],'omitnan');
      //                      obj.t_ipu = ps_pre.t_ipu; %Don't update this
      //                      because it can get too
      //                      narrow.%mean([3*std(diff(t_found));wfm.ps_pre.t_ipu]);
      //                      obj.t_ipj = ps_pre.t_ipj;
      //                  end
      //                  fp_pos     =
      //                  freq_found;%nanmean([freq_found;wfm.ps_pre.fp]);%Previous
      //                  fc may be nan if unknown obj.fp     = fp_pos;
      //                  obj.fstart = fp_pos-bw_found/2;
      //                  obj.fend   = fp_pos+bw_found/2;
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
