//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: wfmstft.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Oct-2022 17:38:50
//

// Include Files
#include "wfmstft.h"
#include "mean.h"
#include "movSumProdOrMean.h"
#include "quickselect.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_rtwutil.h"
#include "coder_array.h"
#include <cmath>

// Function Declarations
static void binary_expand_op(coder::array<boolean_T, 2U> &in1,
                             const coder::array<double, 2U> &in2,
                             const coder::array<double, 2U> &in3);

// Function Definitions
//
// Arguments    : coder::array<boolean_T, 2U> &in1
//                const coder::array<double, 2U> &in2
//                const coder::array<double, 2U> &in3
// Return Type  : void
//
static void binary_expand_op(coder::array<boolean_T, 2U> &in1,
                             const coder::array<double, 2U> &in2,
                             const coder::array<double, 2U> &in3)
{
  int aux_0_1;
  int aux_1_1;
  int i;
  int i1;
  int loop_ub;
  int stride_0_0;
  int stride_0_1;
  int stride_1_0;
  int stride_1_1;
  if (in3.size(0) == 1) {
    i = in2.size(0);
  } else {
    i = in3.size(0);
  }
  if (in3.size(1) == 1) {
    i1 = in2.size(1);
  } else {
    i1 = in3.size(1);
  }
  in1.set_size(i, i1);
  stride_0_0 = (in2.size(0) != 1);
  stride_0_1 = (in2.size(1) != 1);
  stride_1_0 = (in3.size(0) != 1);
  stride_1_1 = (in3.size(1) != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  if (in3.size(1) == 1) {
    loop_ub = in2.size(1);
  } else {
    loop_ub = in3.size(1);
  }
  for (i = 0; i < loop_ub; i++) {
    int b_loop_ub;
    i1 = in3.size(0);
    if (i1 == 1) {
      b_loop_ub = in2.size(0);
    } else {
      b_loop_ub = i1;
    }
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      in1[i1 + in1.size(0) * i] =
          (in2[i1 * stride_0_0 + in2.size(0) * aux_0_1] >
           10.0 * in3[i1 * stride_1_0 + in3.size(0) * aux_1_1]);
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
}

//
// obj.psd = obj.dt^2/obj.T*mean(abs(obj.S).^2,2);
// obj.psd = obj.dt^2/obj.T*median(abs(obj.S).^2,2);%use median to exclude
// outliers from short pulses
//              runningPsd = obj.dt^2/obj.T*abs(obj.S).^2;
//              psdStdDev  = stdev(runningPsd,[],2);
//              psdStdDevMat = repmat(runningPsd,1,size(runningPsd,2));
//
// Arguments    : void
// Return Type  : void
//
void wfmstft::updatepsd()
{
  coder::array<double, 2U> magSqrd;
  coder::array<double, 2U> movMeanMagSqrd;
  coder::array<double, 1U> xv;
  coder::array<int, 1U> r;
  coder::array<boolean_T, 2U> magSqrdMask;
  double b;
  double varargin_1;
  int ibtile;
  int ilast;
  int len;
  int loop_ub;
  int midm1;
  int nx;
  int outsize_idx_0;
  int stride;
  // This block calculates a three window moving mean of the power
  // spectral density of the waveform and then thresholds that
  // moving mean for values greater than 10x the median. This
  // thresholding step reduced the energy from very high power
  // pulses that might be in the signal from affecting the PSD
  // estimate. It is assumed here that low signal power pulses will
  // only marginally affect the psd estimate.
  // coder.varsize('magSqrd','movMeanMagSqrd','medMovMeanMagSqrd','medMovMeanMagSqrdMat','magSqrdMask')
  nx = S.size(0) * S.size(1);
  movMeanMagSqrd.set_size(S.size(0), S.size(1));
  for (midm1 = 0; midm1 < nx; midm1++) {
    movMeanMagSqrd[midm1] = rt_hypotd_snf(S[midm1].re, S[midm1].im);
  }
  magSqrd.set_size(movMeanMagSqrd.size(0), movMeanMagSqrd.size(1));
  loop_ub = movMeanMagSqrd.size(0) * movMeanMagSqrd.size(1);
  for (ilast = 0; ilast < loop_ub; ilast++) {
    varargin_1 = movMeanMagSqrd[ilast];
    magSqrd[ilast] = varargin_1 * varargin_1;
  }
  movMeanMagSqrd.set_size(magSqrd.size(0), magSqrd.size(1));
  loop_ub = magSqrd.size(0) * magSqrd.size(1);
  for (ilast = 0; ilast < loop_ub; ilast++) {
    movMeanMagSqrd[ilast] = 0.0;
  }
  nx = magSqrd.size(1);
  stride = magSqrd.size(0);
  if (magSqrd.size(0) - 1 >= 0) {
    outsize_idx_0 = magSqrd.size(1);
    ibtile = magSqrd.size(1);
  }
  for (int j{0}; j < stride; j++) {
    xv.set_size(outsize_idx_0);
    for (ilast = 0; ilast < ibtile; ilast++) {
      xv[ilast] = 0.0;
    }
    for (midm1 = 0; midm1 < nx; midm1++) {
      xv[midm1] = magSqrd[j + midm1 * stride];
    }
    coder::vmovfun(xv, magSqrd.size(1), psd);
    len = psd.size(0);
    for (midm1 = 0; midm1 < len; midm1++) {
      movMeanMagSqrd[j + midm1 * stride] = psd[midm1];
    }
  }
  psd.set_size(movMeanMagSqrd.size(0));
  if ((movMeanMagSqrd.size(0) == 0) || (movMeanMagSqrd.size(1) == 0)) {
    len = psd.size(0);
    psd.set_size(len);
    for (ilast = 0; ilast < len; ilast++) {
      psd[ilast] = rtNaN;
    }
  } else {
    int n;
    psd.set_size(movMeanMagSqrd.size(0));
    loop_ub = movMeanMagSqrd.size(0);
    for (ilast = 0; ilast < loop_ub; ilast++) {
      psd[ilast] = 0.0;
    }
    nx = movMeanMagSqrd.size(1);
    stride = movMeanMagSqrd.size(0);
    loop_ub = movMeanMagSqrd.size(1);
    n = movMeanMagSqrd.size(1);
    for (int j{0}; j < stride; j++) {
      xv.set_size(nx);
      for (ilast = 0; ilast < loop_ub; ilast++) {
        xv[ilast] = 0.0;
      }
      for (midm1 = 0; midm1 < nx; midm1++) {
        xv[midm1] = movMeanMagSqrd[j + midm1 * stride];
      }
      midm1 = 0;
      int exitg1;
      do {
        exitg1 = 0;
        if (midm1 <= n - 1) {
          if (std::isnan(xv[midm1])) {
            psd[j] = rtNaN;
            exitg1 = 1;
          } else {
            midm1++;
          }
        } else {
          if (n <= 4) {
            if (n == 1) {
              psd[j] = xv[0];
            } else if (n == 2) {
              if (((xv[0] < 0.0) != (xv[1] < 0.0)) || std::isinf(xv[0])) {
                psd[j] = (xv[0] + xv[1]) / 2.0;
              } else {
                psd[j] = xv[0] + (xv[1] - xv[0]) / 2.0;
              }
            } else if (n == 3) {
              if (xv[0] < xv[1]) {
                if (xv[1] < xv[2]) {
                  ibtile = 1;
                } else if (xv[0] < xv[2]) {
                  ibtile = 2;
                } else {
                  ibtile = 0;
                }
              } else if (xv[0] < xv[2]) {
                ibtile = 0;
              } else if (xv[1] < xv[2]) {
                ibtile = 2;
              } else {
                ibtile = 1;
              }
              psd[j] = xv[ibtile];
            } else {
              if (xv[0] < xv[1]) {
                if (xv[1] < xv[2]) {
                  outsize_idx_0 = 0;
                  ibtile = 1;
                  ilast = 2;
                } else if (xv[0] < xv[2]) {
                  outsize_idx_0 = 0;
                  ibtile = 2;
                  ilast = 1;
                } else {
                  outsize_idx_0 = 2;
                  ibtile = 0;
                  ilast = 1;
                }
              } else if (xv[0] < xv[2]) {
                outsize_idx_0 = 1;
                ibtile = 0;
                ilast = 2;
              } else if (xv[1] < xv[2]) {
                outsize_idx_0 = 1;
                ibtile = 2;
                ilast = 0;
              } else {
                outsize_idx_0 = 2;
                ibtile = 1;
                ilast = 0;
              }
              if (xv[outsize_idx_0] < xv[3]) {
                if (xv[3] < xv[ilast]) {
                  if (((xv[ibtile] < 0.0) != (xv[3] < 0.0)) ||
                      std::isinf(xv[ibtile])) {
                    psd[j] = (xv[ibtile] + xv[3]) / 2.0;
                  } else {
                    psd[j] = xv[ibtile] + (xv[3] - xv[ibtile]) / 2.0;
                  }
                } else if (((xv[ibtile] < 0.0) != (xv[ilast] < 0.0)) ||
                           std::isinf(xv[ibtile])) {
                  psd[j] = (xv[ibtile] + xv[ilast]) / 2.0;
                } else {
                  psd[j] = xv[ibtile] + (xv[ilast] - xv[ibtile]) / 2.0;
                }
              } else if (((xv[outsize_idx_0] < 0.0) != (xv[ibtile] < 0.0)) ||
                         std::isinf(xv[outsize_idx_0])) {
                psd[j] = (xv[outsize_idx_0] + xv[ibtile]) / 2.0;
              } else {
                psd[j] =
                    xv[outsize_idx_0] + (xv[ibtile] - xv[outsize_idx_0]) / 2.0;
              }
            }
          } else {
            midm1 = n >> 1;
            if ((n & 1) == 0) {
              coder::internal::quickselect(xv, midm1 + 1, n, &varargin_1,
                                           &outsize_idx_0, &ilast);
              psd[j] = varargin_1;
              if (midm1 < outsize_idx_0) {
                coder::internal::quickselect(xv, midm1, ilast - 1, &b, &ibtile,
                                             &len);
                if (((varargin_1 < 0.0) != (b < 0.0)) ||
                    std::isinf(varargin_1)) {
                  psd[j] = (varargin_1 + b) / 2.0;
                } else {
                  psd[j] = varargin_1 + (b - varargin_1) / 2.0;
                }
              }
            } else {
              coder::internal::quickselect(xv, midm1 + 1, n, &psd[j],
                                           &outsize_idx_0, &ibtile);
            }
          }
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
  }
  // transpose(median(transpose(movMeanMagSqrd)));%median(rand(80,32767),2);
  movMeanMagSqrd.set_size(psd.size(0), magSqrd.size(1));
  len = psd.size(0);
  outsize_idx_0 = magSqrd.size(1);
  for (ilast = 0; ilast < outsize_idx_0; ilast++) {
    ibtile = ilast * len;
    for (midm1 = 0; midm1 < len; midm1++) {
      movMeanMagSqrd[ibtile + midm1] = psd[midm1];
    }
  }
  if ((magSqrd.size(0) == movMeanMagSqrd.size(0)) &&
      (magSqrd.size(1) == movMeanMagSqrd.size(1))) {
    magSqrdMask.set_size(magSqrd.size(0), magSqrd.size(1));
    loop_ub = magSqrd.size(0) * magSqrd.size(1);
    for (ilast = 0; ilast < loop_ub; ilast++) {
      magSqrdMask[ilast] = (magSqrd[ilast] > 10.0 * movMeanMagSqrd[ilast]);
    }
  } else {
    binary_expand_op(magSqrdMask, magSqrd, movMeanMagSqrd);
  }
  outsize_idx_0 = magSqrdMask.size(0) * magSqrdMask.size(1) - 1;
  len = 0;
  for (ibtile = 0; ibtile <= outsize_idx_0; ibtile++) {
    if (magSqrdMask[ibtile]) {
      len++;
    }
  }
  r.set_size(len);
  len = 0;
  for (ibtile = 0; ibtile <= outsize_idx_0; ibtile++) {
    if (magSqrdMask[ibtile]) {
      r[len] = ibtile + 1;
      len++;
    }
  }
  loop_ub = r.size(0);
  for (ilast = 0; ilast < loop_ub; ilast++) {
    magSqrd[r[ilast] - 1] = rtNaN;
  }
  varargin_1 = dt;
  varargin_1 = varargin_1 * varargin_1 / T;
  coder::mean(magSqrd, psd);
  loop_ub = psd.size(0);
  for (ilast = 0; ilast < loop_ub; ilast++) {
    psd[ilast] = varargin_1 * psd[ilast];
  }
  len = 1;
  if (psd.size(0) != 1) {
    len = psd.size(0);
  }
  if (psd.size(0) == 1) {
    varargin_1 = psd[0];
    psd.set_size(len);
    for (ilast = 0; ilast < len; ilast++) {
      psd[ilast] = varargin_1;
    }
  } else {
    psd.set_size(len);
  }
  // use median to exclude outliers from short pulses
}

//
// File trailer for wfmstft.cpp
//
// [EOF]
//
