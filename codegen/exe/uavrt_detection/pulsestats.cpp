//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: pulsestats.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 14:31:55
//

// Include Files
#include "pulsestats.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_internal_types.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "validator_check_size.h"
#include "coder_array.h"
#include <cmath>
#include <string.h>

// Function Definitions
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
  static rtEqualityCheckInfo c_emlrtECI{
      2,                                         // nDims
      148,                                       // lineNo
      17,                                        // colNo
      "pulsestats/pulsestats",                   // fName
      "H:\\repos\\uavrt_detection\\pulsestats.m" // pName
  };
  pulsestats *obj;
  coder::array<c_struct_T, 2U> _in;
  coder::array<c_struct_T, 2U> val;
  coder::array<double, 2U> localCpki;
  coder::array<boolean_T, 2U> b_val;
  int loop_ub;
  obj = this;
  if (std::isnan(tp) || std::isnan(tip) || std::isnan(tipu) ||
      std::isnan(tipj)) {
    b_rtErrorWithMessageID(b_emlrtRTEI.fName, b_emlrtRTEI.lineNo);
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
    rtDimSizeGeqError(1, b_cpki.size(1), &c_emlrtECI);
  }
  // Tell coder these are variable size.
  // Now actually assign them
  coder::internal::validator_check_size(b_pl, _in);
  obj->pl.set_size(1, _in.size(1));
  loop_ub = _in.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->pl[i] = _in[i];
  }
  coder::internal::b_validator_check_size(b_clst, val);
  obj->clst.set_size(val.size(0), val.size(1));
  loop_ub = val.size(0) * val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->clst[i] = val[i];
  }
  coder::internal::c_validator_check_size(b_cmsk, b_val);
  obj->cmsk.set_size(b_val.size(0), b_val.size(1));
  loop_ub = b_val.size(0) * b_val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->cmsk[i] = b_val[i];
  }
  coder::internal::b_validator_check_size(b_cpki, localCpki);
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
  coder::array<boolean_T, 2U> cmsk_data;
  coder::array<boolean_T, 2U> r;
  emxArray_struct_T_1x1 c_pl;
  int loop_ub;
  obj = this;
  if (std::isnan(tp) || std::isnan(tip) || std::isnan(tipu) ||
      std::isnan(tipj)) {
    b_rtErrorWithMessageID(b_emlrtRTEI.fName, b_emlrtRTEI.lineNo);
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
  coder::internal::b_validator_check_size(e_pl, val);
  obj->clst.set_size(val.size(0), val.size(1));
  loop_ub = val.size(0) * val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->clst[i] = val[i];
  }
  cmsk_data.set(nullptr, 0, 0);
  coder::internal::c_validator_check_size(cmsk_data, r);
  obj->cmsk.set_size(r.size(0), r.size(1));
  loop_ub = r.size(0) * r.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->cmsk[i] = r[i];
  }
  b_cmsk.set(nullptr, 0, 0);
  coder::internal::b_validator_check_size(b_cmsk, b_val);
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
    b_rtErrorWithMessageID(b_emlrtRTEI.fName, b_emlrtRTEI.lineNo);
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
  coder::internal::b_validator_check_size(e_pl, val);
  obj->clst.set_size(val.size(0), val.size(1));
  loop_ub = val.size(0) * val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->clst[i] = val[i];
  }
  tmp_data = false;
  b_tmp_data.set(&tmp_data, 1, 1);
  coder::internal::c_validator_check_size(b_tmp_data, b_val);
  obj->cmsk.set_size(b_val.size(0), b_val.size(1));
  loop_ub = b_val.size(0) * b_val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->cmsk[i] = b_val[i];
  }
  c_tmp_data = rtNaN;
  d_tmp_data.set(&c_tmp_data, 1, 1);
  coder::internal::b_validator_check_size(d_tmp_data, c_val);
  obj->cpki.set_size(c_val.size(0), c_val.size(1));
  loop_ub = c_val.size(0) * c_val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->cpki[i] = c_val[i];
  }
  return obj;
}

//
// File trailer for pulsestats.cpp
//
// [EOF]
//
