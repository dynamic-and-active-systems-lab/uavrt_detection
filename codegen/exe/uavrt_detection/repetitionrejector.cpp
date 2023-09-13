//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: repetitionrejector.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 13-Sep-2023 13:30:23
//

// Include Files
#include "repetitionrejector.h"
#include "assertValidSizeArg.h"
#include "blockedSummation.h"
#include "diff.h"
#include "eml_int_forloop_overflow_check.h"
#include "mod.h"
#include "rt_nonfinite.h"
#include "sparse1.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include <cmath>
#include <cstdio>

// Function Declarations
static void b_plus(coder::array<double, 2U> &in1,
                   const coder::array<double, 2U> &in2);

// Function Definitions
//
// Arguments    : coder::array<double, 2U> &in1
//                const coder::array<double, 2U> &in2
// Return Type  : void
//
static void b_plus(coder::array<double, 2U> &in1,
                   const coder::array<double, 2U> &in2)
{
  coder::array<double, 2U> b_in1;
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
    b_in1[i] = in1[i * stride_0_1] + in2[i * stride_1_1];
  }
  in1.set_size(1, b_in1.size(1));
  loop_ub = b_in1.size(1);
  for (int i{0}; i < loop_ub; i++) {
    in1[i] = b_in1[i];
  }
}

//
// UNTITLED2 Summary of this function goes here
//    Detailed explanation goes here
//
// Arguments    : const coder::array<double, 1U> &t
//                coder::sparse &allWeightsMat
// Return Type  : void
//
void repetitionrejector(const coder::array<double, 1U> &t,
                        coder::sparse &allWeightsMat)
{
  static rtBoundsCheckInfo ab_emlrtBCI{
      -1,                   // iFirst
      -1,                   // iLast
      33,                   // lineNo
      14,                   // colNo
      "mask",               // aName
      "repetitionrejector", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/repetitionrejector.m", // pName
      0                                                       // checkKind
  };
  static rtBoundsCheckInfo bb_emlrtBCI{
      -1,                   // iFirst
      -1,                   // iLast
      9,                    // lineNo
      13,                   // colNo
      "t",                  // aName
      "repetitionrejector", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/repetitionrejector.m", // pName
      0                                                       // checkKind
  };
  static rtBoundsCheckInfo cb_emlrtBCI{
      -1,                   // iFirst
      -1,                   // iLast
      9,                    // lineNo
      8,                    // colNo
      "t",                  // aName
      "repetitionrejector", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/repetitionrejector.m", // pName
      0                                                       // checkKind
  };
  static rtBoundsCheckInfo db_emlrtBCI{
      -1,                    // iFirst
      -1,                    // iLast
      54,                    // lineNo
      49,                    // colNo
      "allWeightsDoubleMat", // aName
      "repetitionrejector",  // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/repetitionrejector.m", // pName
      0                                                       // checkKind
  };
  static rtBoundsCheckInfo eb_emlrtBCI{
      -1,                    // iFirst
      -1,                    // iLast
      54,                    // lineNo
      47,                    // colNo
      "allWeightsDoubleMat", // aName
      "repetitionrejector",  // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/repetitionrejector.m", // pName
      0                                                       // checkKind
  };
  static rtBoundsCheckInfo fb_emlrtBCI{
      -1,                    // iFirst
      -1,                    // iLast
      54,                    // lineNo
      67,                    // colNo
      "allWeightsDoubleMat", // aName
      "repetitionrejector",  // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/repetitionrejector.m", // pName
      0                                                       // checkKind
  };
  static rtBoundsCheckInfo gb_emlrtBCI{
      -1,                    // iFirst
      -1,                    // iLast
      54,                    // lineNo
      58,                    // colNo
      "allWeightsDoubleMat", // aName
      "repetitionrejector",  // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/repetitionrejector.m", // pName
      0                                                       // checkKind
  };
  static rtBoundsCheckInfo hb_emlrtBCI{
      -1,                    // iFirst
      -1,                    // iLast
      51,                    // lineNo
      29,                    // colNo
      "allWeightsDoubleMat", // aName
      "repetitionrejector",  // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/repetitionrejector.m", // pName
      0                                                       // checkKind
  };
  static rtBoundsCheckInfo ib_emlrtBCI{
      -1,                   // iFirst
      -1,                   // iLast
      46,                   // lineNo
      16,                   // colNo
      "allWeights",         // aName
      "repetitionrejector", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/repetitionrejector.m", // pName
      0                                                       // checkKind
  };
  static rtBoundsCheckInfo y_emlrtBCI{
      -1,                   // iFirst
      -1,                   // iLast
      39,                   // lineNo
      17,                   // colNo
      "weights",            // aName
      "repetitionrejector", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/repetitionrejector.m", // pName
      0                                                       // checkKind
  };
  static rtDoubleCheckInfo r_emlrtDCI{
      56,                   // lineNo
      5,                    // colNo
      "repetitionrejector", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/repetitionrejector.m", // pName
      4                                                       // checkKind
  };
  static rtEqualityCheckInfo g_emlrtECI{
      2,                    // nDims
      33,                   // lineNo
      14,                   // colNo
      "repetitionrejector", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/repetitionrejector.m" // pName
  };
  static rtEqualityCheckInfo h_emlrtECI{
      -1,                   // nDims
      51,                   // lineNo
      9,                    // colNo
      "repetitionrejector", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/repetitionrejector.m" // pName
  };
  static rtEqualityCheckInfo i_emlrtECI{
      2,                    // nDims
      40,                   // lineNo
      22,                   // colNo
      "repetitionrejector", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/repetitionrejector.m" // pName
  };
  static const signed char iv[4]{2, 3, 5, 10};
  coder::sparse b_t;
  coder::array<double, 2U> allWeights;
  coder::array<double, 2U> allWeightsDouble;
  coder::array<double, 2U> allWeightsDoubleMat;
  coder::array<double, 2U> mask;
  coder::array<double, 2U> weights;
  coder::array<double, 1U> a;
  coder::array<boolean_T, 2U> r;
  coder::array<boolean_T, 2U> r1;
  double b_dt;
  double dt;
  double tmp;
  int iv1[2];
  int b_loop_ub;
  int c_loop_ub;
  int d_loop_ub;
  int hi;
  int i;
  int ib;
  int lastBlockLength;
  int loop_ub;
  int nblocks;
  int nx;
  if (t.size(0) < 2) {
    std::printf("UAV-RT: Time vector must contain at least two elements.\n");
    std::fflush(stdout);
    rtDynamicBoundsError(2, 1, t.size(0), cb_emlrtBCI);
  }
  if (t.size(0) < 1) {
    rtDynamicBoundsError(1, 1, t.size(0), bb_emlrtBCI);
  }
  dt = t[1] - t[0];
  coder::diff(t, a);
  loop_ub = a.size(0);
  for (i = 0; i < loop_ub; i++) {
    a[i] = a[i] * 1.0E+9;
  }
  nx = a.size(0);
  if (a.size(0) > 2147483646) {
    coder::check_forloop_overflow_error();
  }
  for (int k{0}; k < nx; k++) {
    a[k] = std::round(a[k]);
  }
  loop_ub = a.size(0);
  for (i = 0; i < loop_ub; i++) {
    a[i] = a[i] / 1.0E+9 - dt;
  }
  if (coder::blockedSummation(a, a.size(0)) != 0.0) {
    // dealing with numerical precision for diff(t)-dt
    std::printf("UAV-RT: Time difference in t vector must be constant.\n");
    std::fflush(stdout);
  }
  // Force to be a row vector
  coder::internal::assertValidSizeArg(static_cast<double>(t.size(0)));
  coder::sparse::eyeLike(t.size(0), t.size(0), t.size(0), b_t);
  allWeights.set_size(1, t.size(0));
  loop_ub = t.size(0);
  for (i = 0; i < loop_ub; i++) {
    allWeights[i] = 0.0;
  }
  loop_ub = t.size(0);
  b_dt = dt / 2.0;
  b_loop_ub = t.size(0);
  c_loop_ub = t.size(0);
  for (int b_i{0}; b_i < 4; b_i++) {
    double dtOfRepSig;
    int end_tmp;
    dtOfRepSig = 1.0 / static_cast<double>(iv[b_i]);
    mask.set_size(1, t.size(0));
    for (i = 0; i < b_loop_ub; i++) {
      mask[i] = 0.0;
    }
    weights.set_size(1, t.size(0));
    for (i = 0; i < loop_ub; i++) {
      tmp = t[i];
      weights[i] = coder::internal::scalar::b_mod(tmp, dtOfRepSig);
    }
    r.set_size(1, weights.size(1));
    nx = weights.size(1);
    r1.set_size(1, weights.size(1));
    dtOfRepSig -= dt / 2.0;
    for (i = 0; i < nx; i++) {
      tmp = weights[i];
      r[i] = (tmp < b_dt);
      r1[i] = (tmp >= dtOfRepSig);
    }
    if (r.size(1) != r1.size(1)) {
      rtSizeEqNDCheck(r.size(), r1.size(), g_emlrtECI);
    }
    end_tmp = r.size(1) - 1;
    for (nx = 0; nx <= end_tmp; nx++) {
      if (r[nx] || r1[nx]) {
        if (nx > end_tmp) {
          rtDynamicBoundsError(nx, 0, end_tmp, ab_emlrtBCI);
        }
        mask[nx] = 1.0;
      }
    }
    // -1 because the first element of the vector will be the diagonal 1s of the
    // identity part of the matrix. Want the sum of the other terms pulse the
    // first term (1) to be zero)
    if (mask.size(1) == 0) {
      tmp = 0.0;
    } else {
      if (mask.size(1) <= 1024) {
        nx = mask.size(1);
        lastBlockLength = 0;
        nblocks = 1;
      } else {
        nx = 1024;
        nblocks =
            static_cast<int>(static_cast<unsigned int>(mask.size(1)) >> 10);
        lastBlockLength = mask.size(1) - (nblocks << 10);
        if (lastBlockLength > 0) {
          nblocks++;
        } else {
          lastBlockLength = 1024;
        }
      }
      tmp = mask[0];
      for (int k{2}; k <= nx; k++) {
        tmp += mask[k - 1];
      }
      for (ib = 2; ib <= nblocks; ib++) {
        nx = (ib - 1) << 10;
        dtOfRepSig = mask[nx];
        if (ib == nblocks) {
          hi = lastBlockLength;
        } else {
          hi = 1024;
        }
        for (int k{2}; k <= hi; k++) {
          dtOfRepSig += mask[(nx + k) - 1];
        }
        tmp += dtOfRepSig;
      }
    }
    weights.set_size(1, t.size(0));
    for (i = 0; i < c_loop_ub; i++) {
      weights[i] = 0.0;
    }
    for (nx = 0; nx <= end_tmp; nx++) {
      if (mask[nx] == 1.0) {
        if (nx > end_tmp) {
          rtDynamicBoundsError(nx, 0, end_tmp, y_emlrtBCI);
        }
        weights[nx] = -1.0 / (tmp - 1.0);
      }
    }
    if ((allWeights.size(1) != weights.size(1)) &&
        ((allWeights.size(1) != 1) && (weights.size(1) != 1))) {
      emlrtDimSizeImpxCheckR2021b(allWeights.size(1), weights.size(1),
                                  i_emlrtECI);
    }
    if (allWeights.size(1) == weights.size(1)) {
      nx = allWeights.size(1) - 1;
      allWeights.set_size(1, allWeights.size(1));
      for (i = 0; i <= nx; i++) {
        allWeights[i] = allWeights[i] + weights[i];
      }
    } else {
      b_plus(allWeights, weights);
    }
  }
  // Have to flip the weights so there is symetry in negative time so that when
  // we use the circular shift operation, the repeated signal shows up at the
  // right time to the left of the 1 value.
  if (allWeights.size(1) < 1) {
    rtDynamicBoundsError(1, 1, allWeights.size(1), ib_emlrtBCI);
  }
  allWeights[0] = 1.0;
  if (allWeights.size(1) < 2) {
    i = -1;
    ib = -1;
  } else {
    i = 0;
    ib = allWeights.size(1) - 1;
  }
  loop_ub = ib - i;
  weights.set_size(1, loop_ub);
  for (ib = 0; ib < loop_ub; ib++) {
    weights[ib] = allWeights[(i + ib) + 1];
  }
  if (loop_ub > 1) {
    nx = loop_ub >> 1;
    for (int k{0}; k < nx; k++) {
      tmp = weights[k];
      hi = (loop_ub - k) - 1;
      weights[k] = weights[hi];
      weights[hi] = tmp;
    }
  }
  allWeightsDouble.set_size(1, weights.size(1) + allWeights.size(1));
  loop_ub = weights.size(1);
  for (i = 0; i < loop_ub; i++) {
    allWeightsDouble[i] = weights[i];
  }
  loop_ub = allWeights.size(1);
  for (i = 0; i < loop_ub; i++) {
    allWeightsDouble[i + weights.size(1)] = allWeights[i];
  }
  allWeightsDoubleMat.set_size(allWeightsDouble.size(1),
                               allWeightsDouble.size(1));
  loop_ub = allWeightsDouble.size(1) * allWeightsDouble.size(1);
  for (i = 0; i < loop_ub; i++) {
    allWeightsDoubleMat[i] = 0.0;
  }
  i = t.size(0);
  if (t.size(0) - 1 >= 0) {
    d_loop_ub = allWeightsDouble.size(1);
    iv1[0] = 1;
  }
  for (int b_i{0}; b_i < i; b_i++) {
    if (b_i + 1 > allWeightsDoubleMat.size(0)) {
      rtDynamicBoundsError(b_i + 1, 1, allWeightsDoubleMat.size(0),
                           hb_emlrtBCI);
    }
    weights.set_size(1, allWeightsDouble.size(1));
    for (ib = 0; ib < d_loop_ub; ib++) {
      weights[ib] = allWeightsDouble[ib];
    }
    if ((allWeightsDouble.size(1) != 0) && (allWeightsDouble.size(1) != 1)) {
      boolean_T shiftright;
      hi = b_i;
      shiftright = true;
      if (b_i > allWeightsDouble.size(1)) {
        hi = b_i -
             allWeightsDouble.size(1) * div_s32(b_i, allWeightsDouble.size(1));
      }
      if (hi > (allWeightsDouble.size(1) >> 1)) {
        hi = allWeightsDouble.size(1) - hi;
        shiftright = false;
      }
      nx = static_cast<int>(
          static_cast<unsigned int>(allWeightsDouble.size(1)) >> 1);
      mask.set_size(1, nx);
      for (ib = 0; ib < nx; ib++) {
        mask[ib] = 0.0;
      }
      nx = allWeightsDouble.size(1);
      if (hi > 0) {
        if (shiftright) {
          for (int k{0}; k < hi; k++) {
            mask[k] = allWeightsDouble[(k + nx) - hi];
          }
          ib = hi + 1;
          for (int k{nx}; k >= ib; k--) {
            weights[k - 1] = weights[(k - hi) - 1];
          }
          for (int k{0}; k < hi; k++) {
            weights[k] = mask[k];
          }
        } else {
          for (int k{0}; k < hi; k++) {
            mask[k] = allWeightsDouble[k];
          }
          ib = allWeightsDouble.size(1) - hi;
          for (int k{0}; k < ib; k++) {
            weights[k] = weights[k + hi];
          }
          for (int k{0}; k < hi; k++) {
            weights[(k + nx) - hi] = mask[k];
          }
        }
      }
    }
    iv1[1] = allWeightsDoubleMat.size(1);
    rtSubAssignSizeCheck(&iv1[0], 2, weights.size(), 2, h_emlrtECI);
    loop_ub = weights.size(1);
    for (ib = 0; ib < loop_ub; ib++) {
      allWeightsDoubleMat[b_i + allWeightsDoubleMat.size(0) * ib] = weights[ib];
    }
  }
  if (t.size(0) < 1) {
    i = 0;
  } else {
    if (allWeightsDoubleMat.size(0) < 1) {
      rtDynamicBoundsError(1, 1, allWeightsDoubleMat.size(0), eb_emlrtBCI);
    }
    if (t.size(0) > allWeightsDoubleMat.size(0)) {
      rtDynamicBoundsError(t.size(0), 1, allWeightsDoubleMat.size(0),
                           db_emlrtBCI);
    }
    i = t.size(0);
  }
  if (t.size(0) > allWeightsDoubleMat.size(1)) {
    ib = 0;
    hi = 0;
  } else {
    if ((t.size(0) < 1) || (t.size(0) > allWeightsDoubleMat.size(1))) {
      rtDynamicBoundsError(t.size(0), 1, allWeightsDoubleMat.size(1),
                           gb_emlrtBCI);
    }
    ib = t.size(0) - 1;
    if (allWeightsDoubleMat.size(1) < 1) {
      rtDynamicBoundsError(allWeightsDoubleMat.size(1), 1,
                           allWeightsDoubleMat.size(1), fb_emlrtBCI);
    }
    hi = allWeightsDoubleMat.size(1);
  }
  lastBlockLength = hi - ib;
  if (i >= MAX_int32_T) {
    pc_rtErrorWithMessageID(ac_emlrtRTEI.fName, ac_emlrtRTEI.lineNo);
  }
  if (lastBlockLength >= MAX_int32_T) {
    pc_rtErrorWithMessageID(ac_emlrtRTEI.fName, ac_emlrtRTEI.lineNo);
  }
  nx = 0;
  hi = i * lastBlockLength;
  for (int k{0}; k < hi; k++) {
    if (allWeightsDoubleMat[k % i + allWeightsDoubleMat.size(0) *
                                        (ib + k / i)] != 0.0) {
      nx++;
    }
  }
  allWeightsMat.m = i;
  allWeightsMat.n = lastBlockLength;
  if (nx < 1) {
    nx = 1;
  }
  allWeightsMat.maxnz = nx;
  allWeightsMat.d.set_size(nx);
  for (hi = 0; hi < nx; hi++) {
    allWeightsMat.d[hi] = 0.0;
  }
  if (lastBlockLength + 1 < 0) {
    rtNonNegativeError(static_cast<double>(lastBlockLength) + 1.0, r_emlrtDCI);
  }
  loop_ub = lastBlockLength + 1;
  allWeightsMat.colidx.set_size(lastBlockLength + 1);
  for (hi = 0; hi < loop_ub; hi++) {
    allWeightsMat.colidx[hi] = 0;
  }
  allWeightsMat.colidx[0] = 1;
  allWeightsMat.rowidx.set_size(nx);
  for (hi = 0; hi < nx; hi++) {
    allWeightsMat.rowidx[hi] = 0;
  }
  allWeightsMat.rowidx[0] = 1;
  nx = 0;
  for (hi = 0; hi < lastBlockLength; hi++) {
    for (nblocks = 0; nblocks < i; nblocks++) {
      tmp = allWeightsDoubleMat[nblocks +
                                allWeightsDoubleMat.size(0) * (ib + hi)];
      if (tmp != 0.0) {
        allWeightsMat.rowidx[nx] = nblocks + 1;
        allWeightsMat.d[nx] = tmp;
        nx++;
      }
    }
    allWeightsMat.colidx[hi + 1] = nx + 1;
  }
}

//
// File trailer for repetitionrejector.cpp
//
// [EOF]
//
