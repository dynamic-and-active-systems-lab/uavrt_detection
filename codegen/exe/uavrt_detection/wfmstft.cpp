//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// wfmstft.cpp
//
// Code generation for function 'wfmstft'
//

// Include files
#include "wfmstft.h"
#include "mean.h"
#include "movSumProdOrMean.h"
#include "quickselect.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_rtwutil.h"
#include "validator_check_size.h"
#include "coder_array.h"
#include <cmath>
#include <string.h>

// Function Declarations
static void binary_expand_op(coder::array<boolean_T, 2U> &in1,
                             const coder::array<double, 2U> &in2,
                             const coder::array<double, 2U> &in3);

// Function Definitions
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
    if (in3.size(0) == 1) {
      b_loop_ub = in2.size(0);
    } else {
      b_loop_ub = in3.size(0);
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

void wfmstft::updatepsd()
{
  coder::array<double, 2U> magSqrd;
  coder::array<double, 2U> movMeanMagSqrd;
  coder::array<double, 1U> xv;
  coder::array<double, 1U> yv;
  coder::array<int, 1U> r;
  coder::array<boolean_T, 2U> magSqrdMask;
  double b;
  double varargin_1;
  int k;
  int len;
  int loop_ub;
  int midm1;
  int ntilecols;
  int nx;
  int outsize_idx_0;
  int stride;
  // obj.psd = obj.dt^2/obj.T*mean(abs(obj.S).^2,2);
  // obj.psd = obj.dt^2/obj.T*median(abs(obj.S).^2,2);%use median to exclude
  // outliers from short pulses
  //              runningPsd = obj.dt^2/obj.T*abs(obj.S).^2;
  //              psdStdDev  = stdev(runningPsd,[],2);
  //              psdStdDevMat = repmat(runningPsd,1,size(runningPsd,2));
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
  for (k = 0; k < nx; k++) {
    movMeanMagSqrd[k] = rt_hypotd_snf(S[k].re, S[k].im);
  }
  magSqrd.set_size(movMeanMagSqrd.size(0), movMeanMagSqrd.size(1));
  loop_ub = movMeanMagSqrd.size(0) * movMeanMagSqrd.size(1);
  for (ntilecols = 0; ntilecols < loop_ub; ntilecols++) {
    varargin_1 = movMeanMagSqrd[ntilecols];
    magSqrd[ntilecols] = varargin_1 * varargin_1;
  }
  movMeanMagSqrd.set_size(magSqrd.size(0), magSqrd.size(1));
  loop_ub = magSqrd.size(0) * magSqrd.size(1);
  for (ntilecols = 0; ntilecols < loop_ub; ntilecols++) {
    movMeanMagSqrd[ntilecols] = 0.0;
  }
  nx = magSqrd.size(1);
  stride = magSqrd.size(0);
  if (magSqrd.size(0) - 1 >= 0) {
    outsize_idx_0 = magSqrd.size(1);
    midm1 = magSqrd.size(1);
  }
  for (int j{0}; j < stride; j++) {
    xv.set_size(outsize_idx_0);
    for (ntilecols = 0; ntilecols < midm1; ntilecols++) {
      xv[ntilecols] = 0.0;
    }
    for (k = 0; k < nx; k++) {
      xv[k] = magSqrd[j + k * stride];
    }
    coder::vmovfun(xv, magSqrd.size(1), yv);
    len = yv.size(0);
    for (k = 0; k < len; k++) {
      movMeanMagSqrd[j + k * stride] = yv[k];
    }
  }
  if ((movMeanMagSqrd.size(0) == 0) || (movMeanMagSqrd.size(1) == 0)) {
    yv.set_size(movMeanMagSqrd.size(0));
    loop_ub = movMeanMagSqrd.size(0);
    for (ntilecols = 0; ntilecols < loop_ub; ntilecols++) {
      yv[ntilecols] = rtNaN;
    }
  } else {
    int n;
    yv.set_size(movMeanMagSqrd.size(0));
    loop_ub = movMeanMagSqrd.size(0);
    for (ntilecols = 0; ntilecols < loop_ub; ntilecols++) {
      yv[ntilecols] = 0.0;
    }
    nx = movMeanMagSqrd.size(1);
    stride = movMeanMagSqrd.size(0);
    loop_ub = movMeanMagSqrd.size(1);
    n = movMeanMagSqrd.size(1);
    for (int j{0}; j < stride; j++) {
      xv.set_size(nx);
      for (ntilecols = 0; ntilecols < loop_ub; ntilecols++) {
        xv[ntilecols] = 0.0;
      }
      for (k = 0; k < nx; k++) {
        xv[k] = movMeanMagSqrd[j + k * stride];
      }
      k = 0;
      int exitg1;
      do {
        exitg1 = 0;
        if (k <= n - 1) {
          if (std::isnan(xv[k])) {
            yv[j] = rtNaN;
            exitg1 = 1;
          } else {
            k++;
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
                  ntilecols = 0;
                  outsize_idx_0 = 1;
                  midm1 = 2;
                } else if (xv[0] < xv[2]) {
                  ntilecols = 0;
                  outsize_idx_0 = 2;
                  midm1 = 1;
                } else {
                  ntilecols = 2;
                  outsize_idx_0 = 0;
                  midm1 = 1;
                }
              } else if (xv[0] < xv[2]) {
                ntilecols = 1;
                outsize_idx_0 = 0;
                midm1 = 2;
              } else if (xv[1] < xv[2]) {
                ntilecols = 1;
                outsize_idx_0 = 2;
                midm1 = 0;
              } else {
                ntilecols = 2;
                outsize_idx_0 = 1;
                midm1 = 0;
              }
              if (xv[ntilecols] < xv[3]) {
                if (xv[3] < xv[midm1]) {
                  if (((xv[outsize_idx_0] < 0.0) != (xv[3] < 0.0)) ||
                      std::isinf(xv[outsize_idx_0])) {
                    yv[j] = (xv[outsize_idx_0] + xv[3]) / 2.0;
                  } else {
                    yv[j] =
                        xv[outsize_idx_0] + (xv[3] - xv[outsize_idx_0]) / 2.0;
                  }
                } else if (((xv[outsize_idx_0] < 0.0) != (xv[midm1] < 0.0)) ||
                           std::isinf(xv[outsize_idx_0])) {
                  yv[j] = (xv[outsize_idx_0] + xv[midm1]) / 2.0;
                } else {
                  yv[j] =
                      xv[outsize_idx_0] + (xv[midm1] - xv[outsize_idx_0]) / 2.0;
                }
              } else if (((xv[ntilecols] < 0.0) != (xv[outsize_idx_0] < 0.0)) ||
                         std::isinf(xv[ntilecols])) {
                yv[j] = (xv[ntilecols] + xv[outsize_idx_0]) / 2.0;
              } else {
                yv[j] =
                    xv[ntilecols] + (xv[outsize_idx_0] - xv[ntilecols]) / 2.0;
              }
            }
          } else {
            midm1 = n >> 1;
            if ((n & 1) == 0) {
              coder::internal::quickselect(xv, midm1 + 1, n, &varargin_1,
                                           &ntilecols, &outsize_idx_0);
              yv[j] = varargin_1;
              if (midm1 < ntilecols) {
                coder::internal::quickselect(xv, midm1, outsize_idx_0 - 1, &b,
                                             &ntilecols, &len);
                if (((varargin_1 < 0.0) != (b < 0.0)) ||
                    std::isinf(varargin_1)) {
                  yv[j] = (varargin_1 + b) / 2.0;
                } else {
                  yv[j] = varargin_1 + (b - varargin_1) / 2.0;
                }
              }
            } else {
              coder::internal::quickselect(xv, midm1 + 1, n, &yv[j], &ntilecols,
                                           &outsize_idx_0);
            }
          }
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
  }
  // transpose(median(transpose(movMeanMagSqrd)));%median(rand(80,32767),2);
  movMeanMagSqrd.set_size(yv.size(0), magSqrd.size(1));
  len = yv.size(0);
  ntilecols = magSqrd.size(1);
  for (midm1 = 0; midm1 < ntilecols; midm1++) {
    outsize_idx_0 = midm1 * len;
    for (k = 0; k < len; k++) {
      movMeanMagSqrd[outsize_idx_0 + k] = yv[k];
    }
  }
  if ((magSqrd.size(0) == movMeanMagSqrd.size(0)) &&
      (magSqrd.size(1) == movMeanMagSqrd.size(1))) {
    magSqrdMask.set_size(magSqrd.size(0), magSqrd.size(1));
    loop_ub = magSqrd.size(0) * magSqrd.size(1);
    for (ntilecols = 0; ntilecols < loop_ub; ntilecols++) {
      magSqrdMask[ntilecols] =
          (magSqrd[ntilecols] > 10.0 * movMeanMagSqrd[ntilecols]);
    }
  } else {
    binary_expand_op(magSqrdMask, magSqrd, movMeanMagSqrd);
  }
  ntilecols = magSqrdMask.size(0) * magSqrdMask.size(1) - 1;
  len = 0;
  for (outsize_idx_0 = 0; outsize_idx_0 <= ntilecols; outsize_idx_0++) {
    if (magSqrdMask[outsize_idx_0]) {
      len++;
    }
  }
  r.set_size(len);
  len = 0;
  for (outsize_idx_0 = 0; outsize_idx_0 <= ntilecols; outsize_idx_0++) {
    if (magSqrdMask[outsize_idx_0]) {
      r[len] = outsize_idx_0 + 1;
      len++;
    }
  }
  loop_ub = r.size(0) - 1;
  for (ntilecols = 0; ntilecols <= loop_ub; ntilecols++) {
    magSqrd[r[ntilecols] - 1] = rtNaN;
  }
  varargin_1 = dt;
  varargin_1 = varargin_1 * varargin_1 / T;
  coder::mean(magSqrd, yv);
  loop_ub = yv.size(0);
  for (ntilecols = 0; ntilecols < loop_ub; ntilecols++) {
    yv[ntilecols] = varargin_1 * yv[ntilecols];
  }
  coder::internal::validator_check_size(yv, psd);
  // use median to exclude outliers from short pulses
}

// End of code generation (wfmstft.cpp)
