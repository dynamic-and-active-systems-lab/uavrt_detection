//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: confirmpulses.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 24-Sep-2023 17:58:12
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
                               const coder::array<boolean_T, 1U> &in2);

static void k_binary_expand_op(coder::array<boolean_T, 2U> &in1,
                               const coder::array<double, 2U> &in2,
                               const coder::array<double, 2U> &in3);

static void l_binary_expand_op(coder::array<boolean_T, 2U> &in1,
                               const coder::array<double, 2U> &in2,
                               const coder::array<double, 2U> &in3);

static void m_binary_expand_op(coder::array<double, 2U> &in1, double in2,
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
//                const coder::array<boolean_T, 1U> &in2
// Return Type  : void
//
static void j_binary_expand_op(coder::array<boolean_T, 2U> &in1,
                               const coder::array<boolean_T, 1U> &in2)
{
  coder::array<boolean_T, 2U> b_in2;
  int in2_idx_0;
  int loop_ub;
  int stride_1_0;
  in2_idx_0 = in2.size(0);
  if (in1.size(0) == 1) {
    loop_ub = in2_idx_0;
  } else {
    loop_ub = in1.size(0);
  }
  b_in2.set_size(loop_ub, 1);
  in2_idx_0 = (in2_idx_0 != 1);
  stride_1_0 = (in1.size(0) != 1);
  for (int i{0}; i < loop_ub; i++) {
    b_in2[i] = (in2[i * in2_idx_0] && in1[i * stride_1_0]);
  }
  in1.set_size(b_in2.size(0), 1);
  loop_ub = b_in2.size(0);
  for (int i{0}; i < loop_ub; i++) {
    in1[i] = b_in2[i];
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
    in1[i] = (in2[i * stride_0_1] <= in3[i * stride_1_1] + 100.0);
  }
}

//
// Arguments    : coder::array<boolean_T, 2U> &in1
//                const coder::array<double, 2U> &in2
//                const coder::array<double, 2U> &in3
// Return Type  : void
//
static void l_binary_expand_op(coder::array<boolean_T, 2U> &in1,
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
static void m_binary_expand_op(coder::array<double, 2U> &in1, double in2,
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
  static rtBoundsCheckInfo ab_emlrtBCI{
      -1,              // iFirst
      -1,              // iLast
      12,              // lineNo
      24,              // colNo
      "X.ps_pos.pl",   // aName
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m", // pName
      0                                                  // checkKind
  };
  static rtBoundsCheckInfo bb_emlrtBCI{
      -1,              // iFirst
      -1,              // iLast
      56,              // lineNo
      27,              // colNo
      "indivConfLog",  // aName
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m", // pName
      0                                                  // checkKind
  };
  static rtBoundsCheckInfo cb_emlrtBCI{
      -1,              // iFirst
      -1,              // iLast
      82,              // lineNo
      26,              // colNo
      "X.ps_pre.pl",   // aName
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m", // pName
      0                                                  // checkKind
  };
  static rtBoundsCheckInfo db_emlrtBCI{
      -1,              // iFirst
      -1,              // iLast
      87,              // lineNo
      36,              // colNo
      "X.ps_pos.pl",   // aName
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m", // pName
      0                                                  // checkKind
  };
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
  static rtDoubleCheckInfo ab_emlrtDCI{
      27,              // lineNo
      74,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m", // pName
      1                                                  // checkKind
  };
  static rtDoubleCheckInfo r_emlrtDCI{
      15,              // lineNo
      80,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m", // pName
      4                                                  // checkKind
  };
  static rtDoubleCheckInfo s_emlrtDCI{
      15,              // lineNo
      80,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m", // pName
      1                                                  // checkKind
  };
  static rtDoubleCheckInfo t_emlrtDCI{
      16,              // lineNo
      80,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m", // pName
      1                                                  // checkKind
  };
  static rtDoubleCheckInfo u_emlrtDCI{
      22,              // lineNo
      78,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m", // pName
      4                                                  // checkKind
  };
  static rtDoubleCheckInfo v_emlrtDCI{
      22,              // lineNo
      78,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m", // pName
      1                                                  // checkKind
  };
  static rtDoubleCheckInfo w_emlrtDCI{
      23,              // lineNo
      78,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m", // pName
      1                                                  // checkKind
  };
  static rtDoubleCheckInfo x_emlrtDCI{
      26,              // lineNo
      74,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m", // pName
      4                                                  // checkKind
  };
  static rtDoubleCheckInfo y_emlrtDCI{
      26,              // lineNo
      74,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m", // pName
      1                                                  // checkKind
  };
  static rtEqualityCheckInfo g_emlrtECI{
      2,               // nDims
      15,              // lineNo
      38,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m" // pName
  };
  static rtEqualityCheckInfo h_emlrtECI{
      2,               // nDims
      16,              // lineNo
      38,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m" // pName
  };
  static rtEqualityCheckInfo i_emlrtECI{
      2,               // nDims
      35,              // lineNo
      15,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m" // pName
  };
  static rtEqualityCheckInfo j_emlrtECI{
      2,               // nDims
      37,              // lineNo
      15,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m" // pName
  };
  static rtEqualityCheckInfo k_emlrtECI{
      2,               // nDims
      41,              // lineNo
      14,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m" // pName
  };
  static rtEqualityCheckInfo l_emlrtECI{
      2,               // nDims
      42,              // lineNo
      14,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m" // pName
  };
  static rtEqualityCheckInfo m_emlrtECI{
      2,               // nDims
      54,              // lineNo
      16,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m" // pName
  };
  static rtEqualityCheckInfo n_emlrtECI{
      1,               // nDims
      93,              // lineNo
      11,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m" // pName
  };
  static rtEqualityCheckInfo o_emlrtECI{
      2,               // nDims
      22,              // lineNo
      38,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m" // pName
  };
  static rtEqualityCheckInfo p_emlrtECI{
      2,               // nDims
      23,              // lineNo
      38,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m" // pName
  };
  static rtEqualityCheckInfo q_emlrtECI{
      2,               // nDims
      26,              // lineNo
      34,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m" // pName
  };
  static rtEqualityCheckInfo r_emlrtECI{
      2,               // nDims
      27,              // lineNo
      34,              // colNo
      "confirmpulses", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/confirmpulses.m" // pName
  };
  const coder::array<c_struct_T, 2U> *structure;
  coder::array<c_struct_T, 1U> b_X;
  coder::array<double, 2U> SNRall;
  coder::array<double, 2U> pulseendtimes_withuncert;
  coder::array<double, 2U> pulsestarttimes_withuncert;
  coder::array<double, 2U> r;
  coder::array<double, 2U> r1;
  coder::array<boolean_T, 2U> SNRnotNegInfLog;
  coder::array<boolean_T, 2U> freqInBand;
  coder::array<boolean_T, 2U> maxstartlog;
  coder::array<boolean_T, 2U> minstartlog;
  coder::array<boolean_T, 2U> r2;
  coder::array<boolean_T, 1U> b_confLog;
  double b;
  double tip;
  double tipj;
  double tipu;
  double tref;
  int i;
  int loop_ub;
  int n;
  int size_tmp_idx_1;
  boolean_T SNRnotNegInfAll;
  i = X->ps_pre->pl.size(1);
  size_tmp_idx_1 = X->ps_pre->pl.size(1);
  if ((size_tmp_idx_1 < 1) || (size_tmp_idx_1 > i)) {
    rtDynamicBoundsError(size_tmp_idx_1, 1, i, y_emlrtBCI);
  }
  tref = X->ps_pre->pl[size_tmp_idx_1 - 1].t_0;
  // tp   = X.ps_pre.t_p;
  tip = X->ps_pre->t_ip;
  tipu = X->ps_pre->t_ipu;
  tipj = X->ps_pre->t_ipj;
  if (tref > X->t_0) {
    // First pulse in this segment exists in last segment as well because of
    // overlap
    i = X->ps_pos->pl.size(1);
    if (i < 1) {
      rtDynamicBoundsError(1, 1, i, ab_emlrtBCI);
    }
    b = X->ps_pos->pl[0].t_0 - tref;
    if (std::abs(b) < tipu + tipj) {
      // X.ps_pos.pl(1).t_0 <= tref + (tip + tipu + tipj)
      // new first pulse is the same one as the last one in the last
      // segment
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
      SNRnotNegInfAll = !(X->K >= 0.0);
      if (SNRnotNegInfAll) {
        rtNonNegativeError(X->K, r_emlrtDCI);
      }
      i = static_cast<int>(std::floor(X->K));
      if (X->K != i) {
        rtIntegerError(X->K, s_emlrtDCI);
      }
      size_tmp_idx_1 = static_cast<int>(X->K);
      SNRnotNegInfAll =
          ((pulsestarttimes_withuncert.size(1) != size_tmp_idx_1) &&
           ((pulsestarttimes_withuncert.size(1) != 1) &&
            (size_tmp_idx_1 != 1)));
      if (SNRnotNegInfAll) {
        emlrtDimSizeImpxCheckR2021b(pulsestarttimes_withuncert.size(1),
                                    size_tmp_idx_1, g_emlrtECI);
      }
      if (pulsestarttimes_withuncert.size(1) == static_cast<int>(X->K)) {
        loop_ub = pulsestarttimes_withuncert.size(1) - 1;
        pulsestarttimes_withuncert.set_size(1,
                                            pulsestarttimes_withuncert.size(1));
        for (int i1{0}; i1 <= loop_ub; i1++) {
          pulsestarttimes_withuncert[i1] =
              (tref + pulsestarttimes_withuncert[i1]) - tipj;
        }
      } else {
        m_binary_expand_op(pulsestarttimes_withuncert, tref, tipj, X);
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
      if (SNRnotNegInfAll) {
        emlrtDimSizeImpxCheckR2021b(pulseendtimes_withuncert.size(1),
                                    size_tmp_idx_1, h_emlrtECI);
      }
      if (pulseendtimes_withuncert.size(1) == static_cast<int>(X->K)) {
        pulseendtimes_withuncert.set_size(1, pulseendtimes_withuncert.size(1));
        for (i = 0; i <= n; i++) {
          pulseendtimes_withuncert[i] =
              (tref + pulseendtimes_withuncert[i]) + tipj;
        }
      } else {
        binary_expand_op(pulseendtimes_withuncert, tref, tipj, X);
      }
    } else {
      double b_tmp;
      boolean_T b_b;
      // new first pulse isn't the same one as the last one in the last
      // segment because the detector detected the last K pulses in the
      // segment and not the first three. Remember that the segment can
      // contain K+1 pulses
      b_tmp = X->K;
      SNRnotNegInfAll = std::isnan(b_tmp);
      if (SNRnotNegInfAll) {
        pulsestarttimes_withuncert.set_size(1, 1);
        pulsestarttimes_withuncert[0] = rtNaN;
      } else if (b_tmp < 1.0) {
        pulsestarttimes_withuncert.set_size(pulsestarttimes_withuncert.size(0),
                                            0);
      } else {
        pulsestarttimes_withuncert.set_size(1,
                                            static_cast<int>(b_tmp - 1.0) + 1);
        loop_ub = static_cast<int>(b_tmp - 1.0);
        for (i = 0; i <= loop_ub; i++) {
          pulsestarttimes_withuncert[i] = static_cast<double>(i) + 1.0;
        }
      }
      b = tip - tipu;
      pulsestarttimes_withuncert.set_size(1,
                                          pulsestarttimes_withuncert.size(1));
      n = pulsestarttimes_withuncert.size(1) - 1;
      for (i = 0; i <= n; i++) {
        pulsestarttimes_withuncert[i] = b * pulsestarttimes_withuncert[i];
      }
      b_b = !(X->K >= 0.0);
      if (b_b) {
        rtNonNegativeError(X->K, u_emlrtDCI);
      }
      i = static_cast<int>(std::floor(X->K));
      if (X->K != i) {
        rtIntegerError(X->K, v_emlrtDCI);
      }
      size_tmp_idx_1 = static_cast<int>(X->K);
      if ((pulsestarttimes_withuncert.size(1) != size_tmp_idx_1) &&
          ((pulsestarttimes_withuncert.size(1) != 1) &&
           (size_tmp_idx_1 != 1))) {
        emlrtDimSizeImpxCheckR2021b(pulsestarttimes_withuncert.size(1),
                                    size_tmp_idx_1, o_emlrtECI);
      }
      if (pulsestarttimes_withuncert.size(1) == static_cast<int>(X->K)) {
        pulsestarttimes_withuncert.set_size(1,
                                            pulsestarttimes_withuncert.size(1));
        for (int i1{0}; i1 <= n; i1++) {
          pulsestarttimes_withuncert[i1] =
              (tref + pulsestarttimes_withuncert[i1]) - tipj;
        }
      } else {
        m_binary_expand_op(pulsestarttimes_withuncert, tref, tipj, X);
      }
      if (SNRnotNegInfAll) {
        pulseendtimes_withuncert.set_size(1, 1);
        pulseendtimes_withuncert[0] = rtNaN;
      } else if (b_tmp < 1.0) {
        pulseendtimes_withuncert.set_size(pulseendtimes_withuncert.size(0), 0);
      } else {
        pulseendtimes_withuncert.set_size(1, static_cast<int>(b_tmp - 1.0) + 1);
        loop_ub = static_cast<int>(b_tmp - 1.0);
        for (int i1{0}; i1 <= loop_ub; i1++) {
          pulseendtimes_withuncert[i1] = static_cast<double>(i1) + 1.0;
        }
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
      if ((pulseendtimes_withuncert.size(1) != size_tmp_idx_1) &&
          ((pulseendtimes_withuncert.size(1) != 1) && (size_tmp_idx_1 != 1))) {
        emlrtDimSizeImpxCheckR2021b(pulseendtimes_withuncert.size(1),
                                    size_tmp_idx_1, p_emlrtECI);
      }
      if (pulseendtimes_withuncert.size(1) == static_cast<int>(X->K)) {
        pulseendtimes_withuncert.set_size(1, pulseendtimes_withuncert.size(1));
        for (i = 0; i <= n; i++) {
          pulseendtimes_withuncert[i] =
              (tref + pulseendtimes_withuncert[i]) + tipj;
        }
      } else {
        binary_expand_op(pulseendtimes_withuncert, tref, tipj, X);
      }
    }
  } else {
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
    SNRnotNegInfAll = !(X->K >= 0.0);
    if (SNRnotNegInfAll) {
      rtNonNegativeError(X->K, x_emlrtDCI);
    }
    i = static_cast<int>(std::floor(X->K));
    if (X->K != i) {
      rtIntegerError(X->K, y_emlrtDCI);
    }
    size_tmp_idx_1 = static_cast<int>(X->K);
    SNRnotNegInfAll =
        ((pulsestarttimes_withuncert.size(1) != size_tmp_idx_1) &&
         ((pulsestarttimes_withuncert.size(1) != 1) && (size_tmp_idx_1 != 1)));
    if (SNRnotNegInfAll) {
      emlrtDimSizeImpxCheckR2021b(pulsestarttimes_withuncert.size(1),
                                  size_tmp_idx_1, q_emlrtECI);
    }
    if (pulsestarttimes_withuncert.size(1) == size_tmp_idx_1) {
      loop_ub = pulsestarttimes_withuncert.size(1) - 1;
      pulsestarttimes_withuncert.set_size(1,
                                          pulsestarttimes_withuncert.size(1));
      for (int i1{0}; i1 <= loop_ub; i1++) {
        pulsestarttimes_withuncert[i1] =
            (tref + pulsestarttimes_withuncert[i1]) - tipj;
      }
    } else {
      m_binary_expand_op(pulsestarttimes_withuncert, tref, tipj, X);
    }
    b = tip + tipu;
    pulseendtimes_withuncert.set_size(1, pulseendtimes_withuncert.size(1));
    n = pulseendtimes_withuncert.size(1) - 1;
    for (int i1{0}; i1 <= n; i1++) {
      pulseendtimes_withuncert[i1] = b * pulseendtimes_withuncert[i1];
    }
    if (X->K != i) {
      rtIntegerError(X->K, ab_emlrtDCI);
    }
    if (SNRnotNegInfAll) {
      emlrtDimSizeImpxCheckR2021b(pulseendtimes_withuncert.size(1),
                                  size_tmp_idx_1, r_emlrtECI);
    }
    if (pulseendtimes_withuncert.size(1) == size_tmp_idx_1) {
      pulseendtimes_withuncert.set_size(1, pulseendtimes_withuncert.size(1));
      for (i = 0; i <= n; i++) {
        pulseendtimes_withuncert[i] =
            (tref + pulseendtimes_withuncert[i]) + tipj;
      }
    } else {
      binary_expand_op(pulseendtimes_withuncert, tref, tipj, X);
    }
  }
  // Debugging plots
  //  figure;xline(pulsestarttimes_withuncert,'--')
  //  hold on;xline(pulseendtimes_withuncert,'--')
  //  plot([X.ps_pos.pl(:).t_0],zeros(size([X.ps_pos.pl(:).t_0])),'ob')
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
  for (loop_ub = 0; loop_ub < n; loop_ub++) {
    r[loop_ub] = b_X[loop_ub].t_0;
  }
  if ((r.size(1) != pulsestarttimes_withuncert.size(1)) &&
      ((r.size(1) != 1) && (pulsestarttimes_withuncert.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(r.size(1), pulsestarttimes_withuncert.size(1),
                                i_emlrtECI);
  }
  if (r.size(1) == pulsestarttimes_withuncert.size(1)) {
    minstartlog.set_size(1, r.size(1));
    loop_ub = r.size(1);
    for (i = 0; i < loop_ub; i++) {
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
  for (loop_ub = 0; loop_ub < n; loop_ub++) {
    r[loop_ub] = b_X[loop_ub].t_0;
  }
  if ((r.size(1) != pulseendtimes_withuncert.size(1)) &&
      ((r.size(1) != 1) && (pulseendtimes_withuncert.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(r.size(1), pulseendtimes_withuncert.size(1),
                                j_emlrtECI);
  }
  if (r.size(1) == pulseendtimes_withuncert.size(1)) {
    maxstartlog.set_size(1, r.size(1));
    loop_ub = r.size(1);
    for (i = 0; i < loop_ub; i++) {
      maxstartlog[i] = (r[i] <= pulseendtimes_withuncert[i]);
    }
  } else {
    b_le(maxstartlog, r, pulseendtimes_withuncert);
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
  for (loop_ub = 0; loop_ub < n; loop_ub++) {
    r[loop_ub] = (*structure)[loop_ub].fp;
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
  for (loop_ub = 0; loop_ub < n; loop_ub++) {
    pulseendtimes_withuncert[loop_ub] = (*structure)[loop_ub].fp;
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
  for (loop_ub = 0; loop_ub < n; loop_ub++) {
    r1[loop_ub] = (*structure)[loop_ub].fp;
  }
  if ((pulseendtimes_withuncert.size(1) != r1.size(1)) &&
      ((pulseendtimes_withuncert.size(1) != 1) && (r1.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(pulseendtimes_withuncert.size(1), r1.size(1),
                                l_emlrtECI);
  }
  if (r.size(1) == pulsestarttimes_withuncert.size(1)) {
    freqInBand.set_size(1, r.size(1));
    loop_ub = r.size(1);
    for (i = 0; i < loop_ub; i++) {
      freqInBand[i] = (r[i] >= pulsestarttimes_withuncert[i] - 100.0);
    }
  } else {
    l_binary_expand_op(freqInBand, r, pulsestarttimes_withuncert);
  }
  if (pulseendtimes_withuncert.size(1) == r1.size(1)) {
    r2.set_size(1, pulseendtimes_withuncert.size(1));
    loop_ub = pulseendtimes_withuncert.size(1);
    for (i = 0; i < loop_ub; i++) {
      r2[i] = (pulseendtimes_withuncert[i] <= r1[i] + 100.0);
    }
  } else {
    k_binary_expand_op(r2, pulseendtimes_withuncert, r1);
  }
  if ((freqInBand.size(1) != r2.size(1)) &&
      ((freqInBand.size(1) != 1) && (r2.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(freqInBand.size(1), r2.size(1), k_emlrtECI);
  }
  if (freqInBand.size(1) == r2.size(1)) {
    loop_ub = freqInBand.size(1) - 1;
    freqInBand.set_size(1, freqInBand.size(1));
    for (i = 0; i <= loop_ub; i++) {
      freqInBand[i] = (freqInBand[i] && r2[i]);
    }
  } else {
    d_and(freqInBand, r2);
  }
  // confLog = maxstartlog & minstartlog & freqInBand;
  // 2023-09-14
  // The method above has increasing uncertainty bounds for the Kth pulse that
  // allows for the entire group to be shifted in time and only the last K
  // pulse gets confirmed. We really need to only check that the first pulse in
  // the group is in the correct position. If it is, then the others are
  // confirmed by default.
  n = X->ps_pos->pl.size(1);
  if ((maxstartlog.size(1) != minstartlog.size(1)) &&
      ((maxstartlog.size(1) != 1) && (minstartlog.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(maxstartlog.size(1), minstartlog.size(1),
                                m_emlrtECI);
  }
  if (maxstartlog.size(1) == minstartlog.size(1)) {
    loop_ub = maxstartlog.size(1) - 1;
    maxstartlog.set_size(1, maxstartlog.size(1));
    for (i = 0; i <= loop_ub; i++) {
      maxstartlog[i] = (maxstartlog[i] && minstartlog[i]);
    }
  } else {
    d_and(maxstartlog, minstartlog);
  }
  if ((maxstartlog.size(1) != freqInBand.size(1)) &&
      ((maxstartlog.size(1) != 1) && (freqInBand.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(maxstartlog.size(1), freqInBand.size(1),
                                m_emlrtECI);
  }
  if (maxstartlog.size(1) == freqInBand.size(1)) {
    loop_ub = maxstartlog.size(1) - 1;
    maxstartlog.set_size(1, maxstartlog.size(1));
    for (i = 0; i <= loop_ub; i++) {
      maxstartlog[i] = (maxstartlog[i] && freqInBand[i]);
    }
  } else {
    d_and(maxstartlog, freqInBand);
  }
  if (maxstartlog.size(1) < 1) {
    rtDynamicBoundsError(1, 1, maxstartlog.size(1), bb_emlrtBCI);
  }
  b_confLog.set_size(n);
  // 2023-09-21
  // If an individual pulse of noise energy is sufficient to be above exceed
  // the threshold, even if all the other K-1 pulses in its groups are just
  // noise, and the noise pulses are repeated in a way that a confirmation in
  // time might occur, the SNR of the adjacent pulses in the group will be
  // very low. Here we check to make sure all the pulses have SNRs within 7dB
  // of the max SNR in the pulse group. If they don't we reject the pulses. If
  // we are dealing with a K = 1 case, we check against the previous pulse.
  confLog.set_size(n, 1);
  for (i = 0; i < n; i++) {
    b_confLog[i] = maxstartlog[0];
    confLog[i] = false;
  }
  if (n > 1) {
    boolean_T exitg1;
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
    for (loop_ub = 0; loop_ub < n; loop_ub++) {
      r[loop_ub] = b_X[loop_ub].SNR;
    }
    size_tmp_idx_1 = r.size(1);
    n = X->ps_pos->pl.size(1);
    b_X = X->ps_pos->pl.reshape(n);
    n = b_X.size(0);
    if (b_X.size(0) == 0) {
      i = 0;
    } else {
      i = b_X.size(0);
    }
    pulsestarttimes_withuncert.set_size(1, i);
    if (b_X.size(0) > 2147483646) {
      coder::check_forloop_overflow_error();
    }
    for (loop_ub = 0; loop_ub < n; loop_ub++) {
      pulsestarttimes_withuncert[loop_ub] = b_X[loop_ub].SNR;
    }
    SNRall.set_size(r.size(1), 1);
    for (i = 0; i < size_tmp_idx_1; i++) {
      SNRall[i] = pulsestarttimes_withuncert[i];
    }
    // SNRmax     = max(SNRall,[],'all');
    // SNRsimilar = SNRall >= SNRmax - abs(SNRmax/2);%use -abs() because SNRmax
    // could be negative. Can't just mult by 0.5 SNRsimilar = SNRall >= SNRmax -
    // 7;%use a fixed distance of 7 dB (5x)
    SNRnotNegInfLog.set_size(SNRall.size(0), 1);
    loop_ub = SNRall.size(0);
    for (i = 0; i < loop_ub; i++) {
      SNRnotNegInfLog[i] = (SNRall[i] != rtMinusInf);
    }
    SNRnotNegInfAll = true;
    if (SNRnotNegInfLog.size(0) > 2147483646) {
      coder::check_forloop_overflow_error();
    }
    n = 1;
    exitg1 = false;
    while ((!exitg1) && (n <= SNRnotNegInfLog.size(0))) {
      if (!SNRnotNegInfLog[n - 1]) {
        SNRnotNegInfAll = false;
        exitg1 = true;
      } else {
        n++;
      }
    }
    n = SNRall.size(0);
    confLog.set_size(SNRall.size(0), 1);
    for (i = 0; i < n; i++) {
      confLog[i] = SNRnotNegInfAll;
    }
  } else if (n == 1) {
    // If K = 1 and we are confirming pulses, we should always have a pulse
    // in the previous pulse list. Just in case, we check here that there is
    // pulse in the previous segment.
    i = X->ps_pre->pl.size(1);
    if (i < 1) {
      rtDynamicBoundsError(1, 1, i, cb_emlrtBCI);
    }
    b = X->ps_pre->pl[0].fp;
    if (std::isnan(b)) {
      confLog.set_size(1, 1);
      confLog[0] = false;
    } else {
      //  SNRprevious = X.ps_pre.pl(1).SNR;
      //  SNRsimilar  = X.ps_pos.pl(1).SNR >= SNRprevious - 7;
      i = X->ps_pos->pl.size(1);
      if (i < 1) {
        rtDynamicBoundsError(1, 1, i, db_emlrtBCI);
      }
      confLog.set_size(1, 1);
      confLog[0] = (X->ps_pos->pl[0].SNR != rtMinusInf);
    }
  }
  //  if X.ps_pos.pl(1).t_0>328
  //      pause(1);
  //  end
  if ((b_confLog.size(0) != confLog.size(0)) &&
      ((b_confLog.size(0) != 1) && (confLog.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(b_confLog.size(0), confLog.size(0), n_emlrtECI);
  }
  if (b_confLog.size(0) == confLog.size(0)) {
    loop_ub = b_confLog.size(0) - 1;
    confLog.set_size(b_confLog.size(0), 1);
    for (i = 0; i <= loop_ub; i++) {
      confLog[i] = (b_confLog[i] && confLog[i]);
    }
  } else {
    j_binary_expand_op(confLog, b_confLog);
  }
}

//
// File trailer for confirmpulses.cpp
//
// [EOF]
//
