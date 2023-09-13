//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: confirmpulses.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 13-Sep-2023 13:30:23
//

// Include Files
#include "confirmpulses.h"
#include "eml_int_forloop_overflow_check.h"
#include "pulsestats.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_internal_types.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "waveform.h"
#include "coder_array.h"
#include <cmath>

// Function Declarations
static void b_ge(coder::array<boolean_T, 2U> &in1,
                 const coder::array<double, 2U> &in2,
                 const coder::array<double, 2U> &in3);

static void b_le(coder::array<boolean_T, 2U> &in1,
                 const coder::array<double, 2U> &in2,
                 const coder::array<double, 2U> &in3);

static void binary_expand_op(coder::array<double, 2U> &in1, double in2,
                             double in3, const waveform *in4);

static void d_and(coder::array<boolean_T, 2U> &in1,
                  const coder::array<boolean_T, 2U> &in2);

static void j_binary_expand_op(coder::array<boolean_T, 2U> &in1,
                               const coder::array<double, 2U> &in2,
                               const coder::array<double, 2U> &in3);

static void k_binary_expand_op(coder::array<boolean_T, 2U> &in1,
                               const coder::array<double, 2U> &in2,
                               const coder::array<double, 2U> &in3);

static void l_binary_expand_op(coder::array<double, 2U> &in1, double in2,
                               double in3, const waveform *in4);

// Function Definitions
//
// Arguments    : coder::array<boolean_T, 2U> &in1
//                const coder::array<double, 2U> &in2
//                const coder::array<double, 2U> &in3
// Return Type  : void
//
static void b_ge(coder::array<boolean_T, 2U> &in1,
                 const coder::array<double, 2U> &in2,
                 const coder::array<double, 2U> &in3)
{
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  in1.set_size(1, in1.size(1));
  if (in3.size(1) == 1) {
    loop_ub = in2.size(1);
  } else {
    loop_ub = in3.size(1);
  }
  in1.set_size(in1.size(0), loop_ub);
  stride_0_1 = (in2.size(1) != 1);
  stride_1_1 = (in3.size(1) != 1);
  for (int i{0}; i < loop_ub; i++) {
    in1[i] = (in2[i * stride_0_1] >= in3[i * stride_1_1]);
  }
}

//
// Arguments    : coder::array<boolean_T, 2U> &in1
//                const coder::array<double, 2U> &in2
//                const coder::array<double, 2U> &in3
// Return Type  : void
//
static void b_le(coder::array<boolean_T, 2U> &in1,
                 const coder::array<double, 2U> &in2,
                 const coder::array<double, 2U> &in3)
{
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  in1.set_size(1, in1.size(1));
  if (in3.size(1) == 1) {
    loop_ub = in2.size(1);
  } else {
    loop_ub = in3.size(1);
  }
  in1.set_size(in1.size(0), loop_ub);
  stride_0_1 = (in2.size(1) != 1);
  stride_1_1 = (in3.size(1) != 1);
  for (int i{0}; i < loop_ub; i++) {
    in1[i] = (in2[i * stride_0_1] <= in3[i * stride_1_1]);
  }
}

//
// Arguments    : coder::array<double, 2U> &in1
//                double in2
//                double in3
//                const waveform *in4
// Return Type  : void
//
static void binary_expand_op(coder::array<double, 2U> &in1, double in2,
                             double in3, const waveform *in4)
{
  coder::array<double, 2U> b_in2;
  int stride_0_1;
  int unnamed_idx_1;
  unnamed_idx_1 = static_cast<int>(in4->K);
  if (unnamed_idx_1 == 1) {
    unnamed_idx_1 = in1.size(1);
  }
  b_in2.set_size(1, unnamed_idx_1);
  stride_0_1 = (in1.size(1) != 1);
  for (int i{0}; i < unnamed_idx_1; i++) {
    b_in2[i] = (in2 + in1[i * stride_0_1]) + in3;
  }
  in1.set_size(1, b_in2.size(1));
  unnamed_idx_1 = b_in2.size(1);
  for (int i{0}; i < unnamed_idx_1; i++) {
    in1[i] = b_in2[i];
  }
}

//
// Arguments    : coder::array<boolean_T, 2U> &in1
//                const coder::array<boolean_T, 2U> &in2
// Return Type  : void
//
static void d_and(coder::array<boolean_T, 2U> &in1,
                  const coder::array<boolean_T, 2U> &in2)
{
  coder::array<boolean_T, 2U> b_in1;
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  if (in2.size(1) == 1) {
    loop_ub = in1.size(1);
  } else {
    loop_ub = in2.size(1);
  }
  b_in1.set_size(1, loop_ub);
  stride_0_1 = (in1.size(1) != 1);
  stride_1_1 = (in2.size(1) != 1);
  for (int i{0}; i < loop_ub; i++) {
    b_in1[i] = (in1[i * stride_0_1] && in2[i * stride_1_1]);
  }
  in1.set_size(1, b_in1.size(1));
  loop_ub = b_in1.size(1);
  for (int i{0}; i < loop_ub; i++) {
    in1[i] = b_in1[i];
  }
}

//
// Arguments    : coder::array<boolean_T, 2U> &in1
//                const coder::array<double, 2U> &in2
//                const coder::array<double, 2U> &in3
// Return Type  : void
//
static void j_binary_expand_op(coder::array<boolean_T, 2U> &in1,
                               const coder::array<double, 2U> &in2,
                               const coder::array<double, 2U> &in3)
{
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  in1.set_size(1, in1.size(1));
  if (in3.size(1) == 1) {
    loop_ub = in2.size(1);
  } else {
    loop_ub = in3.size(1);
  }
  in1.set_size(in1.size(0), loop_ub);
  stride_0_1 = (in2.size(1) != 1);
  stride_1_1 = (in3.size(1) != 1);
  for (int i{0}; i < loop_ub; i++) {
    in1[i] = (in2[i * stride_0_1] <= in3[i * stride_1_1] + 100.0);
  }
}

//
// Arguments    : coder::array<boolean_T, 2U> &in1
//                const coder::array<double, 2U> &in2
//                const coder::array<double, 2U> &in3
// Return Type  : void
//
static void k_binary_expand_op(coder::array<boolean_T, 2U> &in1,
                               const coder::array<double, 2U> &in2,
                               const coder::array<double, 2U> &in3)
{
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  in1.set_size(1, in1.size(1));
  if (in3.size(1) == 1) {
    loop_ub = in2.size(1);
  } else {
    loop_ub = in3.size(1);
  }
  in1.set_size(in1.size(0), loop_ub);
  stride_0_1 = (in2.size(1) != 1);
  stride_1_1 = (in3.size(1) != 1);
  for (int i{0}; i < loop_ub; i++) {
    in1[i] = (in2[i * stride_0_1] >= in3[i * stride_1_1] - 100.0);
  }
}

//
// Arguments    : coder::array<double, 2U> &in1
//                double in2
//                double in3
//                const waveform *in4
// Return Type  : void
//
static void l_binary_expand_op(coder::array<double, 2U> &in1, double in2,
                               double in3, const waveform *in4)
{
  coder::array<double, 2U> b_in2;
  int stride_0_1;
  int unnamed_idx_1;
  unnamed_idx_1 = static_cast<int>(in4->K);
  if (unnamed_idx_1 == 1) {
    unnamed_idx_1 = in1.size(1);
  }
  b_in2.set_size(1, unnamed_idx_1);
  stride_0_1 = (in1.size(1) != 1);
  for (int i{0}; i < unnamed_idx_1; i++) {
    b_in2[i] = (in2 + in1[i * stride_0_1]) - in3;
  }
  in1.set_size(1, b_in2.size(1));
  unnamed_idx_1 = b_in2.size(1);
  for (int i{0}; i < unnamed_idx_1; i++) {
    in1[i] = b_in2[i];
  }
}

//
// confirmpulses Returns a boolean vector that say if the pulses in the
// X.ps_pos pulse stats are where they should be in frequency and time based on
// the last pulse of the X.ps_pre and its pulse timing parameter.
//
// Arguments    : const waveform *X
//                coder::array<boolean_T, 2U> &confLog
// Return Type  : void
//
void confirmpulses(const waveform *X, coder::array<boolean_T, 2U> &confLog)
{
  static rtBoundsCheckInfo y_emlrtBCI{
      -1,              // iFirst
      -1,              // iLast
      6,               // lineNo
      20,              // colNo
      "X.ps_pre.pl",   // aName
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m", // pName
      0                                                  // checkKind
  };
  static rtDoubleCheckInfo r_emlrtDCI{
      12,              // lineNo
      76,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m", // pName
      4                                                  // checkKind
  };
  static rtDoubleCheckInfo s_emlrtDCI{
      12,              // lineNo
      76,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m", // pName
      1                                                  // checkKind
  };
  static rtDoubleCheckInfo t_emlrtDCI{
      13,              // lineNo
      76,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m", // pName
      1                                                  // checkKind
  };
  static rtDoubleCheckInfo u_emlrtDCI{
      15,              // lineNo
      74,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m", // pName
      4                                                  // checkKind
  };
  static rtDoubleCheckInfo v_emlrtDCI{
      15,              // lineNo
      74,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m", // pName
      1                                                  // checkKind
  };
  static rtDoubleCheckInfo w_emlrtDCI{
      16,              // lineNo
      74,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m", // pName
      1                                                  // checkKind
  };
  static rtEqualityCheckInfo g_emlrtECI{
      2,               // nDims
      12,              // lineNo
      34,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m" // pName
  };
  static rtEqualityCheckInfo h_emlrtECI{
      2,               // nDims
      13,              // lineNo
      34,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m" // pName
  };
  static rtEqualityCheckInfo i_emlrtECI{
      2,               // nDims
      20,              // lineNo
      15,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m" // pName
  };
  static rtEqualityCheckInfo j_emlrtECI{
      2,               // nDims
      22,              // lineNo
      15,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m" // pName
  };
  static rtEqualityCheckInfo k_emlrtECI{
      2,               // nDims
      26,              // lineNo
      14,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m" // pName
  };
  static rtEqualityCheckInfo l_emlrtECI{
      2,               // nDims
      27,              // lineNo
      14,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m" // pName
  };
  static rtEqualityCheckInfo m_emlrtECI{
      2,               // nDims
      29,              // lineNo
      11,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m" // pName
  };
  static rtEqualityCheckInfo n_emlrtECI{
      2,               // nDims
      15,              // lineNo
      34,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m" // pName
  };
  static rtEqualityCheckInfo o_emlrtECI{
      2,               // nDims
      16,              // lineNo
      34,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m" // pName
  };
  const coder::array<c_struct_T, 2U> *structure;
  coder::array<c_struct_T, 1U> b_X;
  coder::array<double, 2U> pulseendtimes_withuncert;
  coder::array<double, 2U> pulsestarttimes_withuncert;
  coder::array<double, 2U> r;
  coder::array<double, 2U> r1;
  coder::array<boolean_T, 2U> freqInBand;
  coder::array<boolean_T, 2U> minstartlog;
  coder::array<boolean_T, 2U> r2;
  double tip;
  double tipj;
  double tipu;
  double tref;
  int b_i;
  int i;
  int n;
  i = X->ps_pre->pl.size(1);
  b_i = X->ps_pre->pl.size(1);
  if ((b_i < 1) || (b_i > i)) {
    rtDynamicBoundsError(b_i, 1, i, y_emlrtBCI);
  }
  tref = X->ps_pre->pl[b_i - 1].t_0;
  // tp   = X.ps_pre.t_p;
  tip = X->ps_pre->t_ip;
  tipu = X->ps_pre->t_ipu;
  tipj = X->ps_pre->t_ipj;
  if (tref > X->t_0) {
    double b;
    boolean_T b_b;
    // First pulse in this segment exists in last segment as well because of
    // overlap
    b = X->K - 1.0;
    if (std::isnan(b)) {
      pulseendtimes_withuncert.set_size(1, 1);
      pulseendtimes_withuncert[0] = rtNaN;
    } else if (b < 0.0) {
      pulseendtimes_withuncert.set_size(1, 0);
    } else {
      pulseendtimes_withuncert.set_size(1, static_cast<int>(b) + 1);
      n = static_cast<int>(b);
      for (i = 0; i <= n; i++) {
        pulseendtimes_withuncert[i] = i;
      }
    }
    b = tip - tipu;
    pulsestarttimes_withuncert.set_size(1, pulseendtimes_withuncert.size(1));
    n = pulseendtimes_withuncert.size(1);
    for (i = 0; i < n; i++) {
      pulsestarttimes_withuncert[i] = b * pulseendtimes_withuncert[i];
    }
    b_b = !(X->K >= 0.0);
    if (b_b) {
      rtNonNegativeError(X->K, r_emlrtDCI);
    }
    i = static_cast<int>(std::floor(X->K));
    if (X->K != i) {
      rtIntegerError(X->K, s_emlrtDCI);
    }
    b_i = static_cast<int>(X->K);
    b_b = ((pulsestarttimes_withuncert.size(1) != b_i) &&
           ((pulsestarttimes_withuncert.size(1) != 1) && (b_i != 1)));
    if (b_b) {
      emlrtDimSizeImpxCheckR2021b(pulsestarttimes_withuncert.size(1), b_i,
                                  g_emlrtECI);
    }
    if (pulsestarttimes_withuncert.size(1) == b_i) {
      n = pulsestarttimes_withuncert.size(1) - 1;
      pulsestarttimes_withuncert.set_size(1,
                                          pulsestarttimes_withuncert.size(1));
      for (int i1{0}; i1 <= n; i1++) {
        pulsestarttimes_withuncert[i1] =
            (tref + pulsestarttimes_withuncert[i1]) - tipj;
      }
    } else {
      l_binary_expand_op(pulsestarttimes_withuncert, tref, tipj, X);
    }
    b = tip + tipu;
    pulseendtimes_withuncert.set_size(1, pulseendtimes_withuncert.size(1));
    n = pulseendtimes_withuncert.size(1) - 1;
    for (int i1{0}; i1 <= n; i1++) {
      pulseendtimes_withuncert[i1] = b * pulseendtimes_withuncert[i1];
    }
    if (X->K != i) {
      rtIntegerError(X->K, t_emlrtDCI);
    }
    if (b_b) {
      emlrtDimSizeImpxCheckR2021b(pulseendtimes_withuncert.size(1), b_i,
                                  h_emlrtECI);
    }
    if (pulseendtimes_withuncert.size(1) == b_i) {
      pulseendtimes_withuncert.set_size(1, pulseendtimes_withuncert.size(1));
      for (i = 0; i <= n; i++) {
        pulseendtimes_withuncert[i] =
            (tref + pulseendtimes_withuncert[i]) + tipj;
      }
    } else {
      binary_expand_op(pulseendtimes_withuncert, tref, tipj, X);
    }
  } else {
    double b;
    boolean_T b_b;
    // First pulse in this segment does not exists in last segment as well
    // because of overlap
    b = X->K;
    if (std::isnan(b)) {
      pulseendtimes_withuncert.set_size(1, 1);
      pulseendtimes_withuncert[0] = rtNaN;
    } else if (b < 1.0) {
      pulseendtimes_withuncert.set_size(1, 0);
    } else {
      pulseendtimes_withuncert.set_size(1, static_cast<int>(b - 1.0) + 1);
      n = static_cast<int>(b - 1.0);
      for (i = 0; i <= n; i++) {
        pulseendtimes_withuncert[i] = static_cast<double>(i) + 1.0;
      }
    }
    b = tip - tipu;
    pulsestarttimes_withuncert.set_size(1, pulseendtimes_withuncert.size(1));
    n = pulseendtimes_withuncert.size(1);
    for (i = 0; i < n; i++) {
      pulsestarttimes_withuncert[i] = b * pulseendtimes_withuncert[i];
    }
    b_b = !(X->K >= 0.0);
    if (b_b) {
      rtNonNegativeError(X->K, u_emlrtDCI);
    }
    i = static_cast<int>(std::floor(X->K));
    if (X->K != i) {
      rtIntegerError(X->K, v_emlrtDCI);
    }
    b_i = static_cast<int>(X->K);
    b_b = ((pulsestarttimes_withuncert.size(1) != b_i) &&
           ((pulsestarttimes_withuncert.size(1) != 1) && (b_i != 1)));
    if (b_b) {
      emlrtDimSizeImpxCheckR2021b(pulsestarttimes_withuncert.size(1), b_i,
                                  n_emlrtECI);
    }
    if (pulsestarttimes_withuncert.size(1) == b_i) {
      n = pulsestarttimes_withuncert.size(1) - 1;
      pulsestarttimes_withuncert.set_size(1,
                                          pulsestarttimes_withuncert.size(1));
      for (int i1{0}; i1 <= n; i1++) {
        pulsestarttimes_withuncert[i1] =
            (tref + pulsestarttimes_withuncert[i1]) - tipj;
      }
    } else {
      l_binary_expand_op(pulsestarttimes_withuncert, tref, tipj, X);
    }
    b = tip + tipu;
    pulseendtimes_withuncert.set_size(1, pulseendtimes_withuncert.size(1));
    n = pulseendtimes_withuncert.size(1) - 1;
    for (int i1{0}; i1 <= n; i1++) {
      pulseendtimes_withuncert[i1] = b * pulseendtimes_withuncert[i1];
    }
    if (X->K != i) {
      rtIntegerError(X->K, w_emlrtDCI);
    }
    if (b_b) {
      emlrtDimSizeImpxCheckR2021b(pulseendtimes_withuncert.size(1), b_i,
                                  o_emlrtECI);
    }
    if (pulseendtimes_withuncert.size(1) == b_i) {
      pulseendtimes_withuncert.set_size(1, pulseendtimes_withuncert.size(1));
      for (i = 0; i <= n; i++) {
        pulseendtimes_withuncert[i] =
            (tref + pulseendtimes_withuncert[i]) + tipj;
      }
    } else {
      binary_expand_op(pulseendtimes_withuncert, tref, tipj, X);
    }
  }
  // Check if pulses started after expected minimum start times
  n = X->ps_pos->pl.size(1);
  b_X = X->ps_pos->pl.reshape(n);
  n = b_X.size(0);
  if (b_X.size(0) == 0) {
    i = 0;
  } else {
    i = b_X.size(0);
  }
  r.set_size(1, i);
  if (b_X.size(0) > 2147483646) {
    coder::check_forloop_overflow_error();
  }
  for (b_i = 0; b_i < n; b_i++) {
    r[b_i] = b_X[b_i].t_0;
  }
  if ((r.size(1) != pulsestarttimes_withuncert.size(1)) &&
      ((r.size(1) != 1) && (pulsestarttimes_withuncert.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(r.size(1), pulsestarttimes_withuncert.size(1),
                                i_emlrtECI);
  }
  if (r.size(1) == pulsestarttimes_withuncert.size(1)) {
    minstartlog.set_size(1, r.size(1));
    n = r.size(1);
    for (i = 0; i < n; i++) {
      minstartlog[i] = (r[i] >= pulsestarttimes_withuncert[i]);
    }
  } else {
    b_ge(minstartlog, r, pulsestarttimes_withuncert);
  }
  // Check if pulses started before expected maximum start times
  n = X->ps_pos->pl.size(1);
  b_X = X->ps_pos->pl.reshape(n);
  n = b_X.size(0);
  if (b_X.size(0) == 0) {
    i = 0;
  } else {
    i = b_X.size(0);
  }
  r.set_size(1, i);
  if (b_X.size(0) > 2147483646) {
    coder::check_forloop_overflow_error();
  }
  for (b_i = 0; b_i < n; b_i++) {
    r[b_i] = b_X[b_i].t_0;
  }
  if ((r.size(1) != pulseendtimes_withuncert.size(1)) &&
      ((r.size(1) != 1) && (pulseendtimes_withuncert.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(r.size(1), pulseendtimes_withuncert.size(1),
                                j_emlrtECI);
  }
  if (r.size(1) == pulseendtimes_withuncert.size(1)) {
    confLog.set_size(1, r.size(1));
    n = r.size(1);
    for (i = 0; i < n; i++) {
      confLog[i] = (r[i] <= pulseendtimes_withuncert[i]);
    }
  } else {
    b_le(confLog, r, pulseendtimes_withuncert);
  }
  // Frequency check. Within +/- 100 Hz of previously
  // detected pulses?
  structure = &X->ps_pos->pl;
  n = structure->size(1);
  if (structure->size(1) == 0) {
    i = 0;
  } else {
    i = structure->size(1);
  }
  r.set_size(1, i);
  if (structure->size(1) > 2147483646) {
    coder::check_forloop_overflow_error();
  }
  for (b_i = 0; b_i < n; b_i++) {
    r[b_i] = (*structure)[b_i].fp;
  }
  structure = &X->ps_pre->pl;
  n = structure->size(1);
  if (structure->size(1) == 0) {
    i = 0;
  } else {
    i = structure->size(1);
  }
  pulsestarttimes_withuncert.set_size(1, i);
  if (structure->size(1) > 2147483646) {
    coder::check_forloop_overflow_error();
  }
  for (b_i = 0; b_i < n; b_i++) {
    pulsestarttimes_withuncert[b_i] = (*structure)[b_i].fp;
  }
  if ((r.size(1) != pulsestarttimes_withuncert.size(1)) &&
      ((r.size(1) != 1) && (pulsestarttimes_withuncert.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(r.size(1), pulsestarttimes_withuncert.size(1),
                                k_emlrtECI);
  }
  structure = &X->ps_pos->pl;
  n = structure->size(1);
  if (structure->size(1) == 0) {
    i = 0;
  } else {
    i = structure->size(1);
  }
  pulseendtimes_withuncert.set_size(1, i);
  if (structure->size(1) > 2147483646) {
    coder::check_forloop_overflow_error();
  }
  for (b_i = 0; b_i < n; b_i++) {
    pulseendtimes_withuncert[b_i] = (*structure)[b_i].fp;
  }
  structure = &X->ps_pre->pl;
  n = structure->size(1);
  if (structure->size(1) == 0) {
    i = 0;
  } else {
    i = structure->size(1);
  }
  r1.set_size(1, i);
  if (structure->size(1) > 2147483646) {
    coder::check_forloop_overflow_error();
  }
  for (b_i = 0; b_i < n; b_i++) {
    r1[b_i] = (*structure)[b_i].fp;
  }
  if ((pulseendtimes_withuncert.size(1) != r1.size(1)) &&
      ((pulseendtimes_withuncert.size(1) != 1) && (r1.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(pulseendtimes_withuncert.size(1), r1.size(1),
                                l_emlrtECI);
  }
  if (r.size(1) == pulsestarttimes_withuncert.size(1)) {
    freqInBand.set_size(1, r.size(1));
    n = r.size(1);
    for (i = 0; i < n; i++) {
      freqInBand[i] = (r[i] >= pulsestarttimes_withuncert[i] - 100.0);
    }
  } else {
    k_binary_expand_op(freqInBand, r, pulsestarttimes_withuncert);
  }
  if (pulseendtimes_withuncert.size(1) == r1.size(1)) {
    r2.set_size(1, pulseendtimes_withuncert.size(1));
    n = pulseendtimes_withuncert.size(1);
    for (i = 0; i < n; i++) {
      r2[i] = (pulseendtimes_withuncert[i] <= r1[i] + 100.0);
    }
  } else {
    j_binary_expand_op(r2, pulseendtimes_withuncert, r1);
  }
  if ((freqInBand.size(1) != r2.size(1)) &&
      ((freqInBand.size(1) != 1) && (r2.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(freqInBand.size(1), r2.size(1), k_emlrtECI);
  }
  if (freqInBand.size(1) == r2.size(1)) {
    n = freqInBand.size(1) - 1;
    freqInBand.set_size(1, freqInBand.size(1));
    for (i = 0; i <= n; i++) {
      freqInBand[i] = (freqInBand[i] && r2[i]);
    }
  } else {
    d_and(freqInBand, r2);
  }
  if ((confLog.size(1) != minstartlog.size(1)) &&
      ((confLog.size(1) != 1) && (minstartlog.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(confLog.size(1), minstartlog.size(1),
                                m_emlrtECI);
  }
  if (confLog.size(1) == minstartlog.size(1)) {
    n = confLog.size(1) - 1;
    confLog.set_size(1, confLog.size(1));
    for (i = 0; i <= n; i++) {
      confLog[i] = (confLog[i] && minstartlog[i]);
    }
  } else {
    d_and(confLog, minstartlog);
  }
  if ((confLog.size(1) != freqInBand.size(1)) &&
      ((confLog.size(1) != 1) && (freqInBand.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(confLog.size(1), freqInBand.size(1),
                                m_emlrtECI);
  }
  if (confLog.size(1) == freqInBand.size(1)) {
    n = confLog.size(1) - 1;
    confLog.set_size(1, confLog.size(1));
    for (i = 0; i <= n; i++) {
      confLog[i] = (confLog[i] && freqInBand[i]);
    }
  } else {
    d_and(confLog, freqInBand);
  }
}

//
// File trailer for confirmpulses.cpp
//
// [EOF]
//
