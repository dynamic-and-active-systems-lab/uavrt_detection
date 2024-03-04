//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: repetitionrejector.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 04-Mar-2024 13:02:36
//

// Include Files
#include "repetitionrejector.h"
#include "blockedSummation.h"
#include "diff.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "sparse1.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include <cmath>
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
      -1,                   // iFirst
      -1,                   // iLast
      20,                   // lineNo
      13,                   // colNo
      "t",                  // aName
      "repetitionrejector", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/repetitionrejector.m", // pName
      0                                                       // checkKind
  };
  static rtBoundsCheckInfo bb_emlrtBCI{
      -1,                   // iFirst
      -1,                   // iLast
      20,                   // lineNo
      8,                    // colNo
      "t",                  // aName
      "repetitionrejector", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/repetitionrejector.m", // pName
      0                                                       // checkKind
  };
  coder::array<double, 1U> a;
  double dt;
  int nx;
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
  nx = a.size(0);
  for (int k{0}; k < nx; k++) {
    a[k] = a[k] * 1.0E+9;
  }
  nx = a.size(0);
  if (a.size(0) > 2147483646) {
    coder::check_forloop_overflow_error();
  }
  for (int k{0}; k < nx; k++) {
    a[k] = std::round(a[k]);
  }
  nx = a.size(0);
  for (int k{0}; k < nx; k++) {
    a[k] = a[k] / 1.0E+9 - dt;
  }
  if (coder::blockedSummation(a, a.size(0)) != 0.0) {
    // dealing with numerical precision for diff(t)-dt
    std::printf("UAV-RT: Time difference in t vector must be constant.\n");
    std::fflush(stdout);
  }
  // Force to be a row vector
  coder::sparse::eyeLike(t.size(0), t.size(0), t.size(0), allWeightsMat);
}

//
// File trailer for repetitionrejector.cpp
//
// [EOF]
//
