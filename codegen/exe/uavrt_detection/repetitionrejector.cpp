//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: repetitionrejector.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "repetitionrejector.h"
#include "assertValidSizeArg.h"
#include "diff.h"
#include "round.h"
#include "rt_nonfinite.h"
#include "sparse1.h"
#include "sum.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include <cstdio>

// Function Definitions
//
// REPETITIONREJETOR Build the comb filter matrix used to reject repeaing
// patterns in the stft matrix.
// INPUTS:
//    t   a vector of time values for the columns of an stft matrix
//    repFreqHz   n x 1   a vector of frequencies to reject. ex: [2 3 5 10]
// OUTPUTS
//    allWeightsMat   sparse matrix of the comb filter
//
// Author: Michael Shafer
// Date:  Fall 2023
//
// --------------------------------------------------------------------------
//
//
// Arguments    : const coder::array<double, 1U> &t
//                coder::sparse &allWeightsMat
// Return Type  : void
//
void repetitionrejector(const coder::array<double, 1U> &t,
                        coder::sparse &allWeightsMat)
{
  static rtBoundsCheckInfo ab_emlrtBCI{
      20,                  // lineNo
      "t",                 // aName
      "repetitionrejector" // fName
  };
  static rtBoundsCheckInfo bb_emlrtBCI{
      20,                  // lineNo
      "t",                 // aName
      "repetitionrejector" // fName
  };
  coder::array<double, 1U> a;
  double dt;
  int loop_ub;
  if (t.size(0) < 2) {
    std::printf("UAV-RT: Time vector must contain at least two elements.\n");
    std::fflush(stdout);
    rtDynamicBoundsError(2, 1, t.size(0), bb_emlrtBCI);
  }
  if (t.size(0) < 1) {
    rtDynamicBoundsError(1, 1, t.size(0), ab_emlrtBCI);
  }
  dt = t[1] - t[0];
  coder::diff(t, a);
  loop_ub = a.size(0);
  for (int i{0}; i < loop_ub; i++) {
    a[i] = a[i] * 1.0E+9;
  }
  coder::b_round(a);
  loop_ub = a.size(0);
  for (int i{0}; i < loop_ub; i++) {
    a[i] = a[i] / 1.0E+9 - dt;
  }
  if (coder::sum(a) != 0.0) {
    // dealing with numerical precision for diff(t)-dt
    std::printf("UAV-RT: Time difference in t vector must be constant.\n");
    std::fflush(stdout);
  }
  // Force to be a row vector
  coder::internal::assertValidSizeArg(static_cast<double>(t.size(0)));
  coder::sparse::eyeLike(t.size(0), t.size(0), t.size(0), allWeightsMat);
}

//
// File trailer for repetitionrejector.cpp
//
// [EOF]
//
