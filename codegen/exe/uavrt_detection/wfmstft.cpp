//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: wfmstft.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 09-Mar-2023 11:19:16
//

// Include Files
#include "wfmstft.h"
#include "eml_int_forloop_overflow_check.h"
#include "mean.h"
#include "movSumProdOrMean.h"
#include "quickselect.h"
#include "repmat.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "validator_check_size.h"
#include "coder_array.h"
#include <cmath>
#include <string.h>

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
    if (in3.size(0) == 1) {
      b_loop_ub = in2.size(0);
    } else {
      b_loop_ub = in3.size(0);
    }
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      in1[i1 + in1.size(0) * i] =
          (in2[i1 * stride_0_0 + in2.size(0) * aux_0_1] >
           in3[i1 * stride_1_0 + in3.size(0) * aux_1_1]);
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
}

//
// WFMSTFT Constructs and returns an instance of this class
//
// An waveform object must be passed to this construction method
// so that the constructor has access to the data vector, desired
// overlap fraction, and priori pulse data, which is used to
// develop the window sizes.
// INPUTS:
//    waveform_obj   A single waveform object with prior
//                   dependent properties set.
// OUTPUTS:
//    obj             A wfmstft object
//             %%
//
// The following are variable sized properties. To tell coder
// that they may vary setup as a local variable size variable
// first, then set.
// Instructions on
// https://www.mathworks.com/help/simulink/ug/how-working-with-matlab-classes-is-different-for-code-generation.html
//
// Arguments    : void
// Return Type  : wfmstft *
//
wfmstft *wfmstft::init()
{
  wfmstft *obj;
  coder::array<creal_T, 2U> r;
  coder::array<creal_T, 2U> val;
  coder::array<double, 1U> b_tmp_data;
  coder::array<double, 1U> b_val;
  coder::array<double, 1U> d_tmp_data;
  coder::array<double, 1U> e_tmp_data;
  coder::array<double, 1U> f_tmp_data;
  double tmp_data[2000];
  double c_tmp_data[200];
  int loop_ub;
  obj = this;
  // maxFs*maxpulsewidth
  // Now actually assign them
  r.set(nullptr, 0, 0);
  coder::internal::validator_check_size(r, val);
  obj->S.set_size(val.size(0), val.size(1));
  loop_ub = val.size(0) * val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->S[i] = val[i];
  }
  b_tmp_data.set(&tmp_data[0], 0);
  coder::internal::validator_check_size(b_tmp_data, b_val);
  obj->t.set_size(b_val.size(0));
  loop_ub = b_val.size(0);
  for (int i{0}; i < loop_ub; i++) {
    obj->t[i] = b_val[i];
  }
  d_tmp_data.set(&c_tmp_data[0], 0);
  coder::internal::validator_check_size(d_tmp_data, b_val);
  obj->f.set_size(b_val.size(0));
  loop_ub = b_val.size(0);
  for (int i{0}; i < loop_ub; i++) {
    obj->f[i] = b_val[i];
  }
  e_tmp_data.set(&c_tmp_data[0], 0);
  coder::internal::validator_check_size(e_tmp_data, b_val);
  obj->psd.set_size(b_val.size(0));
  loop_ub = b_val.size(0);
  for (int i{0}; i < loop_ub; i++) {
    obj->psd[i] = b_val[i];
  }
  f_tmp_data.set(&c_tmp_data[0], 0);
  coder::internal::validator_check_size(f_tmp_data, b_val);
  obj->wind.set_size(b_val.size(0));
  loop_ub = b_val.size(0);
  for (int i{0}; i < loop_ub; i++) {
    obj->wind[i] = b_val[i];
  }
  obj->dt = 0.0;
  obj->T = 0.0;
  return obj;
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
  static rtBoundsCheckInfo fb_emlrtBCI{
      -1,                                      // iFirst
      -1,                                      // iLast
      161,                                     // lineNo
      13,                                      // colNo
      "magSqrd",                               // aName
      "wfmstft/updatepsd",                     // fName
      "H:\\repos\\uavrt_detection\\wfmstft.m", // pName
      0                                        // checkKind
  };
  static rtEqualityCheckInfo g_emlrtECI{
      1,                                      // nDims
      160,                                    // lineNo
      27,                                     // colNo
      "wfmstft/updatepsd",                    // fName
      "H:\\repos\\uavrt_detection\\wfmstft.m" // pName
  };
  static rtEqualityCheckInfo h_emlrtECI{
      2,                                      // nDims
      160,                                    // lineNo
      27,                                     // colNo
      "wfmstft/updatepsd",                    // fName
      "H:\\repos\\uavrt_detection\\wfmstft.m" // pName
  };
  coder::array<double, 2U> magSqrd;
  coder::array<double, 2U> movMeanMagSqrd;
  coder::array<double, 1U> xv;
  coder::array<double, 1U> yv;
  coder::array<int, 1U> r;
  coder::array<boolean_T, 2U> magSqrdMask;
  double b;
  double varargin_1;
  int b_loop_ub;
  int len;
  int loop_ub;
  int midm1;
  int nx;
  int outsize_idx_0;
  int stride;
  boolean_T overflow;
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
  if (nx > 2147483646) {
    coder::check_forloop_overflow_error();
  }
  for (midm1 = 0; midm1 < nx; midm1++) {
    movMeanMagSqrd[midm1] = rt_hypotd_snf(S[midm1].re, S[midm1].im);
  }
  magSqrd.set_size(movMeanMagSqrd.size(0), movMeanMagSqrd.size(1));
  loop_ub = movMeanMagSqrd.size(0) * movMeanMagSqrd.size(1);
  for (midm1 = 0; midm1 < loop_ub; midm1++) {
    varargin_1 = movMeanMagSqrd[midm1];
    magSqrd[midm1] = varargin_1 * varargin_1;
  }
  movMeanMagSqrd.set_size(magSqrd.size(0), magSqrd.size(1));
  loop_ub = magSqrd.size(0) * magSqrd.size(1);
  for (midm1 = 0; midm1 < loop_ub; midm1++) {
    movMeanMagSqrd[midm1] = 0.0;
  }
  nx = magSqrd.size(1);
  stride = magSqrd.size(0);
  if (magSqrd.size(0) > 2147483646) {
    coder::check_forloop_overflow_error();
  }
  if (magSqrd.size(0) - 1 >= 0) {
    outsize_idx_0 = magSqrd.size(1);
    b_loop_ub = magSqrd.size(1);
    overflow = (magSqrd.size(1) > 2147483646);
  }
  for (int j{0}; j < stride; j++) {
    xv.set_size(outsize_idx_0);
    for (midm1 = 0; midm1 < b_loop_ub; midm1++) {
      xv[midm1] = 0.0;
    }
    if (overflow) {
      coder::check_forloop_overflow_error();
    }
    for (midm1 = 0; midm1 < nx; midm1++) {
      xv[midm1] = magSqrd[j + midm1 * stride];
    }
    coder::vmovfun(xv, magSqrd.size(1), yv);
    len = yv.size(0);
    if (yv.size(0) > 2147483646) {
      coder::check_forloop_overflow_error();
    }
    for (midm1 = 0; midm1 < len; midm1++) {
      movMeanMagSqrd[j + midm1 * stride] = yv[midm1];
    }
  }
  if ((movMeanMagSqrd.size(0) == 0) || (movMeanMagSqrd.size(1) == 0)) {
    yv.set_size(movMeanMagSqrd.size(0));
    loop_ub = movMeanMagSqrd.size(0);
    for (midm1 = 0; midm1 < loop_ub; midm1++) {
      yv[midm1] = rtNaN;
    }
  } else {
    int n;
    boolean_T b_overflow;
    yv.set_size(movMeanMagSqrd.size(0));
    loop_ub = movMeanMagSqrd.size(0);
    for (midm1 = 0; midm1 < loop_ub; midm1++) {
      yv[midm1] = 0.0;
    }
    nx = movMeanMagSqrd.size(1);
    stride = movMeanMagSqrd.size(0);
    if (movMeanMagSqrd.size(0) > 2147483646) {
      coder::check_forloop_overflow_error();
    }
    loop_ub = movMeanMagSqrd.size(1);
    overflow = (movMeanMagSqrd.size(1) > 2147483646);
    n = movMeanMagSqrd.size(1);
    b_overflow = (movMeanMagSqrd.size(1) > 2147483646);
    for (int j{0}; j < stride; j++) {
      xv.set_size(nx);
      for (midm1 = 0; midm1 < loop_ub; midm1++) {
        xv[midm1] = 0.0;
      }
      if (overflow) {
        coder::check_forloop_overflow_error();
      }
      for (midm1 = 0; midm1 < nx; midm1++) {
        xv[midm1] = movMeanMagSqrd[j + midm1 * stride];
      }
      if (b_overflow) {
        coder::check_forloop_overflow_error();
      }
      midm1 = 0;
      int exitg1;
      do {
        exitg1 = 0;
        if (midm1 <= n - 1) {
          if (std::isnan(xv[midm1])) {
            yv[j] = rtNaN;
            exitg1 = 1;
          } else {
            midm1++;
          }
        } else {
          if (n <= 4) {
            if (n == 1) {
              yv[j] = xv[0];
            } else if (n == 2) {
              if (((xv[0] < 0.0) != (xv[1] < 0.0)) || std::isinf(xv[0])) {
                yv[j] = (xv[0] + xv[1]) / 2.0;
              } else {
                yv[j] = xv[0] + (xv[1] - xv[0]) / 2.0;
              }
            } else if (n == 3) {
              if (xv[0] < xv[1]) {
                if (xv[1] < xv[2]) {
                  outsize_idx_0 = 1;
                } else if (xv[0] < xv[2]) {
                  outsize_idx_0 = 2;
                } else {
                  outsize_idx_0 = 0;
                }
              } else if (xv[0] < xv[2]) {
                outsize_idx_0 = 0;
              } else if (xv[1] < xv[2]) {
                outsize_idx_0 = 2;
              } else {
                outsize_idx_0 = 1;
              }
              yv[j] = xv[outsize_idx_0];
            } else {
              if (xv[0] < xv[1]) {
                if (xv[1] < xv[2]) {
                  len = 0;
                  outsize_idx_0 = 1;
                  b_loop_ub = 2;
                } else if (xv[0] < xv[2]) {
                  len = 0;
                  outsize_idx_0 = 2;
                  b_loop_ub = 1;
                } else {
                  len = 2;
                  outsize_idx_0 = 0;
                  b_loop_ub = 1;
                }
              } else if (xv[0] < xv[2]) {
                len = 1;
                outsize_idx_0 = 0;
                b_loop_ub = 2;
              } else if (xv[1] < xv[2]) {
                len = 1;
                outsize_idx_0 = 2;
                b_loop_ub = 0;
              } else {
                len = 2;
                outsize_idx_0 = 1;
                b_loop_ub = 0;
              }
              if (xv[len] < xv[3]) {
                if (xv[3] < xv[b_loop_ub]) {
                  if (((xv[outsize_idx_0] < 0.0) != (xv[3] < 0.0)) ||
                      std::isinf(xv[outsize_idx_0])) {
                    yv[j] = (xv[outsize_idx_0] + xv[3]) / 2.0;
                  } else {
                    yv[j] =
                        xv[outsize_idx_0] + (xv[3] - xv[outsize_idx_0]) / 2.0;
                  }
                } else if (((xv[outsize_idx_0] < 0.0) !=
                            (xv[b_loop_ub] < 0.0)) ||
                           std::isinf(xv[outsize_idx_0])) {
                  yv[j] = (xv[outsize_idx_0] + xv[b_loop_ub]) / 2.0;
                } else {
                  yv[j] = xv[outsize_idx_0] +
                          (xv[b_loop_ub] - xv[outsize_idx_0]) / 2.0;
                }
              } else if (((xv[len] < 0.0) != (xv[outsize_idx_0] < 0.0)) ||
                         std::isinf(xv[len])) {
                yv[j] = (xv[len] + xv[outsize_idx_0]) / 2.0;
              } else {
                yv[j] = xv[len] + (xv[outsize_idx_0] - xv[len]) / 2.0;
              }
            }
          } else {
            midm1 = n >> 1;
            if ((n & 1) == 0) {
              coder::internal::quickselect(xv, midm1 + 1, n, &varargin_1, &len,
                                           &b_loop_ub);
              yv[j] = varargin_1;
              if (midm1 < len) {
                coder::internal::quickselect(xv, midm1, b_loop_ub - 1, &b, &len,
                                             &outsize_idx_0);
                if (((varargin_1 < 0.0) != (b < 0.0)) ||
                    std::isinf(varargin_1)) {
                  yv[j] = (varargin_1 + b) / 2.0;
                } else {
                  yv[j] = varargin_1 + (b - varargin_1) / 2.0;
                }
              }
            } else {
              coder::internal::quickselect(xv, midm1 + 1, n, &yv[j],
                                           &outsize_idx_0, &b_loop_ub);
            }
          }
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
  }
  // transpose(median(transpose(movMeanMagSqrd)));%median(rand(80,32767),2);
  coder::repmat(yv, static_cast<double>(magSqrd.size(1)), movMeanMagSqrd);
  loop_ub = movMeanMagSqrd.size(0) * movMeanMagSqrd.size(1);
  for (midm1 = 0; midm1 < loop_ub; midm1++) {
    movMeanMagSqrd[midm1] = 10.0 * movMeanMagSqrd[midm1];
  }
  if ((magSqrd.size(0) != movMeanMagSqrd.size(0)) &&
      ((magSqrd.size(0) != 1) && (movMeanMagSqrd.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(magSqrd.size(0), movMeanMagSqrd.size(0),
                                &g_emlrtECI);
  }
  if ((magSqrd.size(1) != movMeanMagSqrd.size(1)) &&
      ((magSqrd.size(1) != 1) && (movMeanMagSqrd.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(magSqrd.size(1), movMeanMagSqrd.size(1),
                                &h_emlrtECI);
  }
  if ((magSqrd.size(0) == movMeanMagSqrd.size(0)) &&
      (magSqrd.size(1) == movMeanMagSqrd.size(1))) {
    magSqrdMask.set_size(magSqrd.size(0), magSqrd.size(1));
    loop_ub = magSqrd.size(0) * magSqrd.size(1);
    for (midm1 = 0; midm1 < loop_ub; midm1++) {
      magSqrdMask[midm1] = (magSqrd[midm1] > movMeanMagSqrd[midm1]);
    }
  } else {
    gt(magSqrdMask, magSqrd, movMeanMagSqrd);
  }
  outsize_idx_0 = magSqrdMask.size(0) * magSqrdMask.size(1) - 1;
  len = 0;
  for (b_loop_ub = 0; b_loop_ub <= outsize_idx_0; b_loop_ub++) {
    if (magSqrdMask[b_loop_ub]) {
      len++;
    }
  }
  r.set_size(len);
  len = 0;
  for (b_loop_ub = 0; b_loop_ub <= outsize_idx_0; b_loop_ub++) {
    if (magSqrdMask[b_loop_ub]) {
      r[len] = b_loop_ub + 1;
      len++;
    }
  }
  loop_ub = r.size(0) - 1;
  len = magSqrd.size(0) * magSqrd.size(1);
  for (midm1 = 0; midm1 <= loop_ub; midm1++) {
    if ((r[midm1] < 1) || (r[midm1] > len)) {
      rtDynamicBoundsError(r[midm1], 1, len, &fb_emlrtBCI);
    }
    magSqrd[r[midm1] - 1] = rtNaN;
  }
  varargin_1 = dt;
  varargin_1 = varargin_1 * varargin_1 / T;
  coder::mean(magSqrd, yv);
  loop_ub = yv.size(0);
  for (midm1 = 0; midm1 < loop_ub; midm1++) {
    yv[midm1] = varargin_1 * yv[midm1];
  }
  coder::internal::validator_check_size(yv, psd);
  // use median to exclude outliers from short pulses
}

//
// File trailer for wfmstft.cpp
//
// [EOF]
//
