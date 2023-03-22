//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: confirmpulses.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 22-Mar-2023 16:43:02
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
#include <string.h>

// Function Declarations
static void binary_expand_op(coder::array<double, 2U> &in1, double in2,
                             double in3, const waveform *in4);

static void d_and(coder::array<boolean_T, 2U> &in1,
                  const coder::array<boolean_T, 2U> &in2);

static void j_binary_expand_op(coder::array<boolean_T, 2U> &in1,
                               const coder::array<double, 2U> &in2,
                               const int in3[2],
                               const coder::array<double, 2U> &in4,
                               const int in5[2]);

static void k_binary_expand_op(coder::array<boolean_T, 2U> &in1,
                               const coder::array<double, 2U> &in2,
                               const int in3[2],
                               const coder::array<double, 2U> &in4,
                               const int in5[2]);

static void l_binary_expand_op(coder::array<boolean_T, 2U> &in1,
                               const coder::array<double, 2U> &in2,
                               const int in3[2],
                               const coder::array<double, 2U> &in4);

static void m_binary_expand_op(coder::array<boolean_T, 2U> &in1,
                               const coder::array<double, 2U> &in2,
                               const int in3[2],
                               const coder::array<double, 2U> &in4);

static void n_binary_expand_op(coder::array<double, 2U> &in1, double in2,
                               double in3, const waveform *in4);

// Function Definitions
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
  int b_unnamed_idx_1;
  int unnamed_idx_1;
  unnamed_idx_1 = static_cast<int>(in4->K);
  if (unnamed_idx_1 == 1) {
    b_unnamed_idx_1 = in1.size(1);
  } else {
    b_unnamed_idx_1 = unnamed_idx_1;
  }
  b_in2.set_size(1, b_unnamed_idx_1);
  b_unnamed_idx_1 = (in1.size(1) != 1);
  if (unnamed_idx_1 == 1) {
    unnamed_idx_1 = in1.size(1);
  }
  for (int i{0}; i < unnamed_idx_1; i++) {
    b_in2[i] = (in2 + in1[i * b_unnamed_idx_1]) + in3;
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
  int i;
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  if (in2.size(1) == 1) {
    i = in1.size(1);
  } else {
    i = in2.size(1);
  }
  b_in1.set_size(1, i);
  stride_0_1 = (in1.size(1) != 1);
  stride_1_1 = (in2.size(1) != 1);
  if (in2.size(1) == 1) {
    loop_ub = in1.size(1);
  } else {
    loop_ub = in2.size(1);
  }
  for (i = 0; i < loop_ub; i++) {
    b_in1[i] = (in1[i * stride_0_1] && in2[i * stride_1_1]);
  }
  in1.set_size(1, b_in1.size(1));
  loop_ub = b_in1.size(1);
  for (i = 0; i < loop_ub; i++) {
    in1[i] = b_in1[i];
  }
}

//
// Arguments    : coder::array<boolean_T, 2U> &in1
//                const coder::array<double, 2U> &in2
//                const int in3[2]
//                const coder::array<double, 2U> &in4
//                const int in5[2]
// Return Type  : void
//
static void j_binary_expand_op(coder::array<boolean_T, 2U> &in1,
                               const coder::array<double, 2U> &in2,
                               const int in3[2],
                               const coder::array<double, 2U> &in4,
                               const int in5[2])
{
  int b_unnamed_idx_1;
  int c_unnamed_idx_1;
  int stride_1_1;
  int unnamed_idx_1;
  unnamed_idx_1 = in3[1];
  b_unnamed_idx_1 = in5[1];
  if (b_unnamed_idx_1 == 1) {
    c_unnamed_idx_1 = unnamed_idx_1;
  } else {
    c_unnamed_idx_1 = b_unnamed_idx_1;
  }
  in1.set_size(1, c_unnamed_idx_1);
  c_unnamed_idx_1 = (unnamed_idx_1 != 1);
  stride_1_1 = (b_unnamed_idx_1 != 1);
  if (b_unnamed_idx_1 != 1) {
    unnamed_idx_1 = b_unnamed_idx_1;
  }
  for (b_unnamed_idx_1 = 0; b_unnamed_idx_1 < unnamed_idx_1;
       b_unnamed_idx_1++) {
    in1[b_unnamed_idx_1] = (in2[b_unnamed_idx_1 * c_unnamed_idx_1] <=
                            in4[b_unnamed_idx_1 * stride_1_1] + 100.0);
  }
}

//
// Arguments    : coder::array<boolean_T, 2U> &in1
//                const coder::array<double, 2U> &in2
//                const int in3[2]
//                const coder::array<double, 2U> &in4
//                const int in5[2]
// Return Type  : void
//
static void k_binary_expand_op(coder::array<boolean_T, 2U> &in1,
                               const coder::array<double, 2U> &in2,
                               const int in3[2],
                               const coder::array<double, 2U> &in4,
                               const int in5[2])
{
  int b_unnamed_idx_1;
  int c_unnamed_idx_1;
  int stride_1_1;
  int unnamed_idx_1;
  unnamed_idx_1 = in3[1];
  b_unnamed_idx_1 = in5[1];
  if (b_unnamed_idx_1 == 1) {
    c_unnamed_idx_1 = unnamed_idx_1;
  } else {
    c_unnamed_idx_1 = b_unnamed_idx_1;
  }
  in1.set_size(1, c_unnamed_idx_1);
  c_unnamed_idx_1 = (unnamed_idx_1 != 1);
  stride_1_1 = (b_unnamed_idx_1 != 1);
  if (b_unnamed_idx_1 != 1) {
    unnamed_idx_1 = b_unnamed_idx_1;
  }
  for (b_unnamed_idx_1 = 0; b_unnamed_idx_1 < unnamed_idx_1;
       b_unnamed_idx_1++) {
    in1[b_unnamed_idx_1] = (in2[b_unnamed_idx_1 * c_unnamed_idx_1] >=
                            in4[b_unnamed_idx_1 * stride_1_1] - 100.0);
  }
}

//
// Arguments    : coder::array<boolean_T, 2U> &in1
//                const coder::array<double, 2U> &in2
//                const int in3[2]
//                const coder::array<double, 2U> &in4
// Return Type  : void
//
static void l_binary_expand_op(coder::array<boolean_T, 2U> &in1,
                               const coder::array<double, 2U> &in2,
                               const int in3[2],
                               const coder::array<double, 2U> &in4)
{
  int i;
  int stride_0_1;
  int stride_1_1;
  int unnamed_idx_1;
  unnamed_idx_1 = in3[1];
  if (in4.size(1) == 1) {
    i = unnamed_idx_1;
  } else {
    i = in4.size(1);
  }
  in1.set_size(1, i);
  stride_0_1 = (unnamed_idx_1 != 1);
  stride_1_1 = (in4.size(1) != 1);
  if (in4.size(1) != 1) {
    unnamed_idx_1 = in4.size(1);
  }
  for (i = 0; i < unnamed_idx_1; i++) {
    in1[i] = (in2[i * stride_0_1] <= in4[i * stride_1_1]);
  }
}

//
// Arguments    : coder::array<boolean_T, 2U> &in1
//                const coder::array<double, 2U> &in2
//                const int in3[2]
//                const coder::array<double, 2U> &in4
// Return Type  : void
//
static void m_binary_expand_op(coder::array<boolean_T, 2U> &in1,
                               const coder::array<double, 2U> &in2,
                               const int in3[2],
                               const coder::array<double, 2U> &in4)
{
  int i;
  int stride_0_1;
  int stride_1_1;
  int unnamed_idx_1;
  unnamed_idx_1 = in3[1];
  if (in4.size(1) == 1) {
    i = unnamed_idx_1;
  } else {
    i = in4.size(1);
  }
  in1.set_size(1, i);
  stride_0_1 = (unnamed_idx_1 != 1);
  stride_1_1 = (in4.size(1) != 1);
  if (in4.size(1) != 1) {
    unnamed_idx_1 = in4.size(1);
  }
  for (i = 0; i < unnamed_idx_1; i++) {
    in1[i] = (in2[i * stride_0_1] >= in4[i * stride_1_1]);
  }
}

//
// Arguments    : coder::array<double, 2U> &in1
//                double in2
//                double in3
//                const waveform *in4
// Return Type  : void
//
static void n_binary_expand_op(coder::array<double, 2U> &in1, double in2,
                               double in3, const waveform *in4)
{
  coder::array<double, 2U> b_in2;
  int b_unnamed_idx_1;
  int unnamed_idx_1;
  unnamed_idx_1 = static_cast<int>(in4->K);
  if (unnamed_idx_1 == 1) {
    b_unnamed_idx_1 = in1.size(1);
  } else {
    b_unnamed_idx_1 = unnamed_idx_1;
  }
  b_in2.set_size(1, b_unnamed_idx_1);
  b_unnamed_idx_1 = (in1.size(1) != 1);
  if (unnamed_idx_1 == 1) {
    unnamed_idx_1 = in1.size(1);
  }
  for (int i{0}; i < unnamed_idx_1; i++) {
    b_in2[i] = (in2 + in1[i * b_unnamed_idx_1]) - in3;
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
  static rtBoundsCheckInfo fb_emlrtBCI{
      -1,                                            // iFirst
      -1,                                            // iLast
      6,                                             // lineNo
      20,                                            // colNo
      "X.ps_pre.pl",                                 // aName
      "confirmpulses",                               // fName
      "H:\\repos\\uavrt_detection\\confirmpulses.m", // pName
      0                                              // checkKind
  };
  static rtDoubleCheckInfo ab_emlrtDCI{
      12,                                            // lineNo
      76,                                            // colNo
      "confirmpulses",                               // fName
      "H:\\repos\\uavrt_detection\\confirmpulses.m", // pName
      1                                              // checkKind
  };
  static rtDoubleCheckInfo bb_emlrtDCI{
      12,                                            // lineNo
      76,                                            // colNo
      "confirmpulses",                               // fName
      "H:\\repos\\uavrt_detection\\confirmpulses.m", // pName
      4                                              // checkKind
  };
  static rtDoubleCheckInfo t_emlrtDCI{
      16,                                            // lineNo
      74,                                            // colNo
      "confirmpulses",                               // fName
      "H:\\repos\\uavrt_detection\\confirmpulses.m", // pName
      4                                              // checkKind
  };
  static rtDoubleCheckInfo u_emlrtDCI{
      16,                                            // lineNo
      74,                                            // colNo
      "confirmpulses",                               // fName
      "H:\\repos\\uavrt_detection\\confirmpulses.m", // pName
      1                                              // checkKind
  };
  static rtDoubleCheckInfo v_emlrtDCI{
      15,                                            // lineNo
      74,                                            // colNo
      "confirmpulses",                               // fName
      "H:\\repos\\uavrt_detection\\confirmpulses.m", // pName
      1                                              // checkKind
  };
  static rtDoubleCheckInfo w_emlrtDCI{
      15,                                            // lineNo
      74,                                            // colNo
      "confirmpulses",                               // fName
      "H:\\repos\\uavrt_detection\\confirmpulses.m", // pName
      4                                              // checkKind
  };
  static rtDoubleCheckInfo x_emlrtDCI{
      13,                                            // lineNo
      76,                                            // colNo
      "confirmpulses",                               // fName
      "H:\\repos\\uavrt_detection\\confirmpulses.m", // pName
      1                                              // checkKind
  };
  static rtDoubleCheckInfo y_emlrtDCI{
      13,                                            // lineNo
      76,                                            // colNo
      "confirmpulses",                               // fName
      "H:\\repos\\uavrt_detection\\confirmpulses.m", // pName
      4                                              // checkKind
  };
  static rtEqualityCheckInfo g_emlrtECI{
      2,                                            // nDims
      16,                                           // lineNo
      34,                                           // colNo
      "confirmpulses",                              // fName
      "H:\\repos\\uavrt_detection\\confirmpulses.m" // pName
  };
  static rtEqualityCheckInfo h_emlrtECI{
      2,                                            // nDims
      15,                                           // lineNo
      34,                                           // colNo
      "confirmpulses",                              // fName
      "H:\\repos\\uavrt_detection\\confirmpulses.m" // pName
  };
  static rtEqualityCheckInfo i_emlrtECI{
      2,                                            // nDims
      29,                                           // lineNo
      11,                                           // colNo
      "confirmpulses",                              // fName
      "H:\\repos\\uavrt_detection\\confirmpulses.m" // pName
  };
  static rtEqualityCheckInfo j_emlrtECI{
      2,                                            // nDims
      27,                                           // lineNo
      14,                                           // colNo
      "confirmpulses",                              // fName
      "H:\\repos\\uavrt_detection\\confirmpulses.m" // pName
  };
  static rtEqualityCheckInfo k_emlrtECI{
      2,                                            // nDims
      26,                                           // lineNo
      14,                                           // colNo
      "confirmpulses",                              // fName
      "H:\\repos\\uavrt_detection\\confirmpulses.m" // pName
  };
  static rtEqualityCheckInfo l_emlrtECI{
      2,                                            // nDims
      22,                                           // lineNo
      15,                                           // colNo
      "confirmpulses",                              // fName
      "H:\\repos\\uavrt_detection\\confirmpulses.m" // pName
  };
  static rtEqualityCheckInfo m_emlrtECI{
      2,                                            // nDims
      20,                                           // lineNo
      15,                                           // colNo
      "confirmpulses",                              // fName
      "H:\\repos\\uavrt_detection\\confirmpulses.m" // pName
  };
  static rtEqualityCheckInfo n_emlrtECI{
      2,                                            // nDims
      13,                                           // lineNo
      34,                                           // colNo
      "confirmpulses",                              // fName
      "H:\\repos\\uavrt_detection\\confirmpulses.m" // pName
  };
  static rtEqualityCheckInfo o_emlrtECI{
      2,                                            // nDims
      12,                                           // lineNo
      34,                                           // colNo
      "confirmpulses",                              // fName
      "H:\\repos\\uavrt_detection\\confirmpulses.m" // pName
  };
  const coder::array<c_struct_T, 2U> *structure;
  coder::array<c_struct_T, 1U> b_X;
  coder::array<double, 2U> b_varargin_1;
  coder::array<double, 2U> pulseendtimes_withuncert;
  coder::array<double, 2U> pulsestarttimes_withuncert;
  coder::array<double, 2U> varargin_1;
  coder::array<boolean_T, 2U> freqInBand;
  coder::array<boolean_T, 2U> minstartlog;
  coder::array<boolean_T, 2U> r;
  double tip;
  double tipj;
  double tipu;
  double tref;
  int b_input_sizes[2];
  int c_input_sizes[2];
  int d_input_sizes[2];
  int e_input_sizes[2];
  int f_input_sizes[2];
  int input_sizes[2];
  int i;
  int loop_ub;
  int n;
  i = X->ps_pre->pl.size(1);
  n = X->ps_pre->pl.size(1);
  if ((n < 1) || (n > i)) {
    rtDynamicBoundsError(n, 1, i, &fb_emlrtBCI);
  }
  tref = X->ps_pre->pl[n - 1].t_0;
  // tp   = X.ps_pre.t_p;
  tip = X->ps_pre->t_ip;
  tipu = X->ps_pre->t_ipu;
  tipj = X->ps_pre->t_ipj;
  if (tref > X->t_0) {
    double b;
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
      loop_ub = static_cast<int>(b);
      for (i = 0; i <= loop_ub; i++) {
        pulseendtimes_withuncert[i] = i;
      }
    }
    b = tip - tipu;
    pulsestarttimes_withuncert.set_size(1, pulseendtimes_withuncert.size(1));
    loop_ub = pulseendtimes_withuncert.size(1);
    for (i = 0; i < loop_ub; i++) {
      pulsestarttimes_withuncert[i] = b * pulseendtimes_withuncert[i];
    }
    if (!(X->K >= 0.0)) {
      rtNonNegativeError(X->K, &bb_emlrtDCI);
    }
    i = static_cast<int>(std::floor(X->K));
    if (X->K != i) {
      rtIntegerError(X->K, &ab_emlrtDCI);
    }
    n = static_cast<int>(X->K);
    if ((pulsestarttimes_withuncert.size(1) != n) &&
        ((pulsestarttimes_withuncert.size(1) != 1) && (n != 1))) {
      emlrtDimSizeImpxCheckR2021b(pulsestarttimes_withuncert.size(1), n,
                                  &o_emlrtECI);
    }
    if (pulsestarttimes_withuncert.size(1) == n) {
      loop_ub = pulsestarttimes_withuncert.size(1) - 1;
      pulsestarttimes_withuncert.set_size(1,
                                          pulsestarttimes_withuncert.size(1));
      for (int i1{0}; i1 <= loop_ub; i1++) {
        pulsestarttimes_withuncert[i1] =
            (tref + pulsestarttimes_withuncert[i1]) - tipj;
      }
    } else {
      n_binary_expand_op(pulsestarttimes_withuncert, tref, tipj, X);
    }
    b = tip + tipu;
    pulseendtimes_withuncert.set_size(1, pulseendtimes_withuncert.size(1));
    loop_ub = pulseendtimes_withuncert.size(1) - 1;
    for (int i1{0}; i1 <= loop_ub; i1++) {
      pulseendtimes_withuncert[i1] = b * pulseendtimes_withuncert[i1];
    }
    if (!(X->K >= 0.0)) {
      rtNonNegativeError(X->K, &y_emlrtDCI);
    }
    if (X->K != i) {
      rtIntegerError(X->K, &x_emlrtDCI);
    }
    if ((pulseendtimes_withuncert.size(1) != n) &&
        ((pulseendtimes_withuncert.size(1) != 1) && (n != 1))) {
      emlrtDimSizeImpxCheckR2021b(pulseendtimes_withuncert.size(1), n,
                                  &n_emlrtECI);
    }
    if (pulseendtimes_withuncert.size(1) == n) {
      loop_ub = pulseendtimes_withuncert.size(1) - 1;
      pulseendtimes_withuncert.set_size(1, pulseendtimes_withuncert.size(1));
      for (i = 0; i <= loop_ub; i++) {
        pulseendtimes_withuncert[i] =
            (tref + pulseendtimes_withuncert[i]) + tipj;
      }
    } else {
      binary_expand_op(pulseendtimes_withuncert, tref, tipj, X);
    }
  } else {
    double b;
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
      loop_ub = static_cast<int>(b - 1.0);
      for (i = 0; i <= loop_ub; i++) {
        pulseendtimes_withuncert[i] = static_cast<double>(i) + 1.0;
      }
    }
    b = tip - tipu;
    pulsestarttimes_withuncert.set_size(1, pulseendtimes_withuncert.size(1));
    loop_ub = pulseendtimes_withuncert.size(1);
    for (i = 0; i < loop_ub; i++) {
      pulsestarttimes_withuncert[i] = b * pulseendtimes_withuncert[i];
    }
    if (!(X->K >= 0.0)) {
      rtNonNegativeError(X->K, &w_emlrtDCI);
    }
    i = static_cast<int>(std::floor(X->K));
    if (X->K != i) {
      rtIntegerError(X->K, &v_emlrtDCI);
    }
    n = static_cast<int>(X->K);
    if ((pulsestarttimes_withuncert.size(1) != n) &&
        ((pulsestarttimes_withuncert.size(1) != 1) && (n != 1))) {
      emlrtDimSizeImpxCheckR2021b(pulsestarttimes_withuncert.size(1), n,
                                  &h_emlrtECI);
    }
    if (pulsestarttimes_withuncert.size(1) == n) {
      loop_ub = pulsestarttimes_withuncert.size(1) - 1;
      pulsestarttimes_withuncert.set_size(1,
                                          pulsestarttimes_withuncert.size(1));
      for (int i1{0}; i1 <= loop_ub; i1++) {
        pulsestarttimes_withuncert[i1] =
            (tref + pulsestarttimes_withuncert[i1]) - tipj;
      }
    } else {
      n_binary_expand_op(pulsestarttimes_withuncert, tref, tipj, X);
    }
    b = tip + tipu;
    pulseendtimes_withuncert.set_size(1, pulseendtimes_withuncert.size(1));
    loop_ub = pulseendtimes_withuncert.size(1) - 1;
    for (int i1{0}; i1 <= loop_ub; i1++) {
      pulseendtimes_withuncert[i1] = b * pulseendtimes_withuncert[i1];
    }
    if (!(X->K >= 0.0)) {
      rtNonNegativeError(X->K, &t_emlrtDCI);
    }
    if (X->K != i) {
      rtIntegerError(X->K, &u_emlrtDCI);
    }
    if ((pulseendtimes_withuncert.size(1) != n) &&
        ((pulseendtimes_withuncert.size(1) != 1) && (n != 1))) {
      emlrtDimSizeImpxCheckR2021b(pulseendtimes_withuncert.size(1), n,
                                  &g_emlrtECI);
    }
    if (pulseendtimes_withuncert.size(1) == n) {
      loop_ub = pulseendtimes_withuncert.size(1) - 1;
      pulseendtimes_withuncert.set_size(1, pulseendtimes_withuncert.size(1));
      for (i = 0; i <= loop_ub; i++) {
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
  varargin_1.set_size(1, i);
  if (b_X.size(0) > 2147483646) {
    coder::check_forloop_overflow_error();
  }
  for (loop_ub = 0; loop_ub < n; loop_ub++) {
    varargin_1[loop_ub] = b_X[loop_ub].t_0;
  }
  if (varargin_1.size(1) != 0) {
    input_sizes[1] = varargin_1.size(1);
  } else {
    input_sizes[1] = 0;
  }
  if ((input_sizes[1] != pulsestarttimes_withuncert.size(1)) &&
      ((input_sizes[1] != 1) && (pulsestarttimes_withuncert.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(
        input_sizes[1], pulsestarttimes_withuncert.size(1), &m_emlrtECI);
  }
  if (input_sizes[1] == pulsestarttimes_withuncert.size(1)) {
    minstartlog.set_size(1, input_sizes[1]);
    loop_ub = input_sizes[1];
    for (i = 0; i < loop_ub; i++) {
      minstartlog[i] = (varargin_1[i] >= pulsestarttimes_withuncert[i]);
    }
  } else {
    m_binary_expand_op(minstartlog, varargin_1, input_sizes,
                       pulsestarttimes_withuncert);
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
  varargin_1.set_size(1, i);
  if (b_X.size(0) > 2147483646) {
    coder::check_forloop_overflow_error();
  }
  for (loop_ub = 0; loop_ub < n; loop_ub++) {
    varargin_1[loop_ub] = b_X[loop_ub].t_0;
  }
  if (varargin_1.size(1) != 0) {
    b_input_sizes[1] = varargin_1.size(1);
  } else {
    b_input_sizes[1] = 0;
  }
  if ((b_input_sizes[1] != pulseendtimes_withuncert.size(1)) &&
      ((b_input_sizes[1] != 1) && (pulseendtimes_withuncert.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(b_input_sizes[1],
                                pulseendtimes_withuncert.size(1), &l_emlrtECI);
  }
  if (b_input_sizes[1] == pulseendtimes_withuncert.size(1)) {
    confLog.set_size(1, b_input_sizes[1]);
    loop_ub = b_input_sizes[1];
    for (i = 0; i < loop_ub; i++) {
      confLog[i] = (varargin_1[i] <= pulseendtimes_withuncert[i]);
    }
  } else {
    l_binary_expand_op(confLog, varargin_1, b_input_sizes,
                       pulseendtimes_withuncert);
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
  varargin_1.set_size(1, i);
  if (structure->size(1) > 2147483646) {
    coder::check_forloop_overflow_error();
  }
  for (loop_ub = 0; loop_ub < n; loop_ub++) {
    varargin_1[loop_ub] = (*structure)[loop_ub].fp;
  }
  if (varargin_1.size(1) != 0) {
    c_input_sizes[1] = varargin_1.size(1);
  } else {
    c_input_sizes[1] = 0;
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
  for (loop_ub = 0; loop_ub < n; loop_ub++) {
    pulsestarttimes_withuncert[loop_ub] = (*structure)[loop_ub].fp;
  }
  if (pulsestarttimes_withuncert.size(1) != 0) {
    d_input_sizes[1] = pulsestarttimes_withuncert.size(1);
  } else {
    d_input_sizes[1] = 0;
  }
  if ((c_input_sizes[1] != d_input_sizes[1]) &&
      ((c_input_sizes[1] != 1) && (d_input_sizes[1] != 1))) {
    emlrtDimSizeImpxCheckR2021b(c_input_sizes[1], d_input_sizes[1],
                                &k_emlrtECI);
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
  for (loop_ub = 0; loop_ub < n; loop_ub++) {
    pulseendtimes_withuncert[loop_ub] = (*structure)[loop_ub].fp;
  }
  if (pulseendtimes_withuncert.size(1) != 0) {
    e_input_sizes[1] = pulseendtimes_withuncert.size(1);
  } else {
    e_input_sizes[1] = 0;
  }
  structure = &X->ps_pre->pl;
  n = structure->size(1);
  if (structure->size(1) == 0) {
    i = 0;
  } else {
    i = structure->size(1);
  }
  b_varargin_1.set_size(1, i);
  if (structure->size(1) > 2147483646) {
    coder::check_forloop_overflow_error();
  }
  for (loop_ub = 0; loop_ub < n; loop_ub++) {
    b_varargin_1[loop_ub] = (*structure)[loop_ub].fp;
  }
  if (b_varargin_1.size(1) != 0) {
    f_input_sizes[1] = b_varargin_1.size(1);
  } else {
    f_input_sizes[1] = 0;
  }
  if ((e_input_sizes[1] != f_input_sizes[1]) &&
      ((e_input_sizes[1] != 1) && (f_input_sizes[1] != 1))) {
    emlrtDimSizeImpxCheckR2021b(e_input_sizes[1], f_input_sizes[1],
                                &j_emlrtECI);
  }
  if (c_input_sizes[1] == d_input_sizes[1]) {
    freqInBand.set_size(1, c_input_sizes[1]);
    loop_ub = c_input_sizes[1];
    for (i = 0; i < loop_ub; i++) {
      freqInBand[i] = (varargin_1[i] >= pulsestarttimes_withuncert[i] - 100.0);
    }
  } else {
    k_binary_expand_op(freqInBand, varargin_1, c_input_sizes,
                       pulsestarttimes_withuncert, d_input_sizes);
  }
  if (e_input_sizes[1] == f_input_sizes[1]) {
    r.set_size(1, e_input_sizes[1]);
    loop_ub = e_input_sizes[1];
    for (i = 0; i < loop_ub; i++) {
      r[i] = (pulseendtimes_withuncert[i] <= b_varargin_1[i] + 100.0);
    }
  } else {
    j_binary_expand_op(r, pulseendtimes_withuncert, e_input_sizes, b_varargin_1,
                       f_input_sizes);
  }
  if ((freqInBand.size(1) != r.size(1)) &&
      ((freqInBand.size(1) != 1) && (r.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(freqInBand.size(1), r.size(1), &k_emlrtECI);
  }
  if (freqInBand.size(1) == r.size(1)) {
    loop_ub = freqInBand.size(1) - 1;
    freqInBand.set_size(1, freqInBand.size(1));
    for (i = 0; i <= loop_ub; i++) {
      freqInBand[i] = (freqInBand[i] && r[i]);
    }
  } else {
    d_and(freqInBand, r);
  }
  if ((confLog.size(1) != minstartlog.size(1)) &&
      ((confLog.size(1) != 1) && (minstartlog.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(confLog.size(1), minstartlog.size(1),
                                &i_emlrtECI);
  }
  if (confLog.size(1) == minstartlog.size(1)) {
    loop_ub = confLog.size(1) - 1;
    confLog.set_size(1, confLog.size(1));
    for (i = 0; i <= loop_ub; i++) {
      confLog[i] = (confLog[i] && minstartlog[i]);
    }
  } else {
    d_and(confLog, minstartlog);
  }
  if ((confLog.size(1) != freqInBand.size(1)) &&
      ((confLog.size(1) != 1) && (freqInBand.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(confLog.size(1), freqInBand.size(1),
                                &i_emlrtECI);
  }
  if (confLog.size(1) == freqInBand.size(1)) {
    loop_ub = confLog.size(1) - 1;
    confLog.set_size(1, confLog.size(1));
    for (i = 0; i <= loop_ub; i++) {
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
