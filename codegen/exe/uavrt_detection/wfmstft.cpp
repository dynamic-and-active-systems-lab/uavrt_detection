//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: wfmstft.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "wfmstft.h"
#include "abs.h"
#include "mean.h"
#include "median.h"
#include "movmean.h"
#include "repmat.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"

// Function Declarations
static void gt(coder::array<boolean_T, 2U> &in1,
               const coder::array<double, 2U> &in2,
               const coder::array<double, 2U> &in3);

// Function Definitions
//
// Arguments    : coder::array<boolean_T, 2U> &in1
//                const coder::array<double, 2U> &in2
//                const coder::array<double, 2U> &in3
// Return Type  : void
//
static void gt(coder::array<boolean_T, 2U> &in1,
               const coder::array<double, 2U> &in2,
               const coder::array<double, 2U> &in3)
{
  int aux_0_1;
  int aux_1_1;
  int b_loop_ub;
  int loop_ub;
  int stride_0_0;
  int stride_0_1;
  int stride_1_0;
  int stride_1_1;
  if (in3.size(0) == 1) {
    loop_ub = in2.size(0);
  } else {
    loop_ub = in3.size(0);
  }
  in1.set_size(loop_ub, in1.size(1));
  if (in3.size(1) == 1) {
    b_loop_ub = in2.size(1);
  } else {
    b_loop_ub = in3.size(1);
  }
  in1.set_size(in1.size(0), b_loop_ub);
  stride_0_0 = (in2.size(0) != 1);
  stride_0_1 = (in2.size(1) != 1);
  stride_1_0 = (in3.size(0) != 1);
  stride_1_1 = (in3.size(1) != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (int i{0}; i < b_loop_ub; i++) {
    for (int i1{0}; i1 < loop_ub; i1++) {
      in1[i1 + in1.size(0) * i] =
          (in2[i1 * stride_0_0 + in2.size(0) * aux_0_1] >
           in3[i1 * stride_1_0 + in3.size(0) * aux_1_1]);
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
}

//
// This block calculates a three window moving mean of the power
// spectral density of the waveform and then thresholds that
// moving mean for values greater than 10x the median. This
// thresholding step reduced the energy from very high power
// pulses that might be in the signal from affecting the PSD
// estimate. It is assumed here that low signal power pulses will
// only marginally affect the psd estimate.
// coder.varsize('magSqrd','movMeanMagSqrd','medMovMeanMagSqrd','medMovMeanMagSqrdMat','magSqrdMask')
//
// Arguments    : void
// Return Type  : void
//
void wfmstft::updatepsd()
{
  static rtBoundsCheckInfo ab_emlrtBCI{
      155,                // lineNo
      "magSqrd",          // aName
      "wfmstft/updatepsd" // fName
  };
  static rtEqualityCheckInfo g_emlrtECI{
      1,                  // nDims
      154,                // lineNo
      "wfmstft/updatepsd" // fName
  };
  static rtEqualityCheckInfo h_emlrtECI{
      2,                  // nDims
      154,                // lineNo
      "wfmstft/updatepsd" // fName
  };
  coder::array<double, 2U> magSqrd;
  coder::array<double, 2U> movMeanMagSqrd;
  coder::array<double, 1U> medMovMeanMagSqrd;
  coder::array<boolean_T, 2U> r;
  double varargin_1;
  int b_loop_ub_tmp;
  int end_tmp;
  int i;
  int loop_ub_tmp;
  coder::b_abs(S, movMeanMagSqrd);
  i = movMeanMagSqrd.size(0);
  end_tmp = movMeanMagSqrd.size(1);
  magSqrd.set_size(movMeanMagSqrd.size(0), movMeanMagSqrd.size(1));
  loop_ub_tmp = movMeanMagSqrd.size(0) * movMeanMagSqrd.size(1);
  for (int i1{0}; i1 < loop_ub_tmp; i1++) {
    varargin_1 = movMeanMagSqrd[i1];
    magSqrd[i1] = varargin_1 * varargin_1;
  }
  coder::movmean(magSqrd, movMeanMagSqrd);
  coder::median(movMeanMagSqrd, medMovMeanMagSqrd);
  // transpose(median(transpose(movMeanMagSqrd)));%median(rand(80,32767),2);
  coder::repmat(medMovMeanMagSqrd, static_cast<double>(magSqrd.size(1)),
                movMeanMagSqrd);
  b_loop_ub_tmp = movMeanMagSqrd.size(0) * movMeanMagSqrd.size(1);
  for (int i1{0}; i1 < b_loop_ub_tmp; i1++) {
    movMeanMagSqrd[i1] = 10.0 * movMeanMagSqrd[i1];
  }
  if ((i != movMeanMagSqrd.size(0)) &&
      ((i != 1) && (movMeanMagSqrd.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(i, movMeanMagSqrd.size(0), g_emlrtECI);
  }
  if ((end_tmp != movMeanMagSqrd.size(1)) &&
      ((end_tmp != 1) && (movMeanMagSqrd.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(end_tmp, movMeanMagSqrd.size(1), h_emlrtECI);
  }
  if ((magSqrd.size(0) == movMeanMagSqrd.size(0)) &&
      (magSqrd.size(1) == movMeanMagSqrd.size(1))) {
    r.set_size(i, end_tmp);
    for (i = 0; i < loop_ub_tmp; i++) {
      r[i] = (magSqrd[i] > movMeanMagSqrd[i]);
    }
  } else {
    gt(r, magSqrd, movMeanMagSqrd);
  }
  end_tmp = r.size(0) * r.size(1);
  for (loop_ub_tmp = 0; loop_ub_tmp < end_tmp; loop_ub_tmp++) {
    if (r[loop_ub_tmp]) {
      i = magSqrd.size(0) * magSqrd.size(1);
      if (loop_ub_tmp > i - 1) {
        rtDynamicBoundsError(loop_ub_tmp, 0, i - 1, ab_emlrtBCI);
      }
      magSqrd[loop_ub_tmp] = rtNaN;
    }
  }
  varargin_1 = dt;
  varargin_1 = varargin_1 * varargin_1 / T;
  coder::mean(magSqrd, medMovMeanMagSqrd);
  end_tmp = medMovMeanMagSqrd.size(0);
  psd.set_size(medMovMeanMagSqrd.size(0));
  for (i = 0; i < end_tmp; i++) {
    psd[i] = varargin_1 * medMovMeanMagSqrd[i];
  }
  // use median to exclude outliers from short pulses
}

//
// File trailer for wfmstft.cpp
//
// [EOF]
//
