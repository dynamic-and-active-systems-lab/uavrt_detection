//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: wfmstft.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 14:31:55
//

// Include Files
#include "wfmstft.h"
#include "eml_int_forloop_overflow_check.h"
#include "median.h"
#include "movSumProdOrMean.h"
#include "repmat.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "validator_check_size.h"
#include "coder_array.h"
#include "omp.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string.h>
#include <string>

// Function Declarations
static void binary_expand_op(wfmstft *in1, double in2,
                             const coder::array<double, 1U> &in3,
                             const coder::array<double, 1U> &in4);

static void gt(coder::array<boolean_T, 2U> &in1,
               const coder::array<double, 2U> &in2,
               const coder::array<double, 2U> &in3);

static double rt_hypotd_snf(double u0, double u1);

static void y_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : wfmstft *in1
//                double in2
//                const coder::array<double, 1U> &in3
//                const coder::array<double, 1U> &in4
// Return Type  : void
//
static void binary_expand_op(wfmstft *in1, double in2,
                             const coder::array<double, 1U> &in3,
                             const coder::array<double, 1U> &in4)
{
  coder::array<double, 1U> b_in2;
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in4.size(0) == 1) {
    i = in3.size(0);
  } else {
    i = in4.size(0);
  }
  b_in2.set_size(i);
  stride_0_0 = (in3.size(0) != 1);
  stride_1_0 = (in4.size(0) != 1);
  if (in4.size(0) == 1) {
    loop_ub = in3.size(0);
  } else {
    loop_ub = in4.size(0);
  }
  for (i = 0; i < loop_ub; i++) {
    b_in2[i] = in2 * (in3[i * stride_0_0] / in4[i * stride_1_0]);
  }
  coder::internal::validator_check_size(b_in2, in1->psd);
}

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
// Arguments    : double u0
//                double u1
// Return Type  : double
//
static double rt_hypotd_snf(double u0, double u1)
{
  double a;
  double y;
  a = std::abs(u0);
  y = std::abs(u1);
  if (a < y) {
    a /= y;
    y *= std::sqrt(a * a + 1.0);
  } else if (a > y) {
    y /= a;
    y = a * std::sqrt(y * y + 1.0);
  } else if (!std::isnan(y)) {
    y = a * 1.4142135623730951;
  }
  return y;
}

//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void y_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Arrays have incompatible sizes for this operation.";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
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
  static rtBoundsCheckInfo f_emlrtBCI{
      -1,                                      // iFirst
      -1,                                      // iLast
      161,                                     // lineNo
      13,                                      // colNo
      "magSqrd",                               // aName
      "wfmstft/updatepsd",                     // fName
      "H:\\repos\\uavrt_detection\\wfmstft.m", // pName
      0                                        // checkKind
  };
  static rtEqualityCheckInfo c_emlrtECI{
      1,                                      // nDims
      160,                                    // lineNo
      27,                                     // colNo
      "wfmstft/updatepsd",                    // fName
      "H:\\repos\\uavrt_detection\\wfmstft.m" // pName
  };
  static rtEqualityCheckInfo d_emlrtECI{
      2,                                      // nDims
      160,                                    // lineNo
      27,                                     // colNo
      "wfmstft/updatepsd",                    // fName
      "H:\\repos\\uavrt_detection\\wfmstft.m" // pName
  };
  static rtRunTimeErrorInfo kb_emlrtRTEI{
      13,                    // lineNo
      "assertCompatibleDims" // fName
  };
  coder::array<double, 2U> magSqrd;
  coder::array<double, 2U> movMeanMagSqrd;
  coder::array<double, 1U> xv;
  coder::array<double, 1U> yv;
  coder::array<int, 1U> counts;
  coder::array<boolean_T, 2U> magSqrdMask;
  double varargin_1;
  int bvstride;
  int lastBlockLength;
  int len;
  int nx;
  int outsize_idx_0;
  int stride;
  int xoffset;
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
  for (int k{0}; k < nx; k++) {
    movMeanMagSqrd[k] = rt_hypotd_snf(S[k].re, S[k].im);
  }
  magSqrd.set_size(movMeanMagSqrd.size(0), movMeanMagSqrd.size(1));
  nx = movMeanMagSqrd.size(0) * movMeanMagSqrd.size(1);
  for (bvstride = 0; bvstride < nx; bvstride++) {
    varargin_1 = movMeanMagSqrd[bvstride];
    magSqrd[bvstride] = varargin_1 * varargin_1;
  }
  movMeanMagSqrd.set_size(magSqrd.size(0), magSqrd.size(1));
  nx = magSqrd.size(0) * magSqrd.size(1);
  for (bvstride = 0; bvstride < nx; bvstride++) {
    movMeanMagSqrd[bvstride] = 0.0;
  }
  nx = magSqrd.size(1);
  stride = magSqrd.size(0);
  if (magSqrd.size(0) > 2147483646) {
    coder::check_forloop_overflow_error();
  }
  if (magSqrd.size(0) - 1 >= 0) {
    outsize_idx_0 = magSqrd.size(1);
    lastBlockLength = magSqrd.size(1);
    overflow = (magSqrd.size(1) > 2147483646);
  }
  for (xoffset = 0; xoffset < stride; xoffset++) {
    xv.set_size(outsize_idx_0);
    for (bvstride = 0; bvstride < lastBlockLength; bvstride++) {
      xv[bvstride] = 0.0;
    }
    if (overflow) {
      coder::check_forloop_overflow_error();
    }
    for (int k{0}; k < nx; k++) {
      xv[k] = magSqrd[xoffset + k * stride];
    }
    coder::vmovfun(xv, magSqrd.size(1), yv);
    len = yv.size(0);
    if (yv.size(0) > 2147483646) {
      coder::check_forloop_overflow_error();
    }
    for (int k{0}; k < len; k++) {
      movMeanMagSqrd[xoffset + k * stride] = yv[k];
    }
  }
  coder::median(movMeanMagSqrd, xv);
  // transpose(median(transpose(movMeanMagSqrd)));%median(rand(80,32767),2);
  coder::repmat(xv, static_cast<double>(magSqrd.size(1)), movMeanMagSqrd);
  nx = movMeanMagSqrd.size(0) * movMeanMagSqrd.size(1);
  for (bvstride = 0; bvstride < nx; bvstride++) {
    movMeanMagSqrd[bvstride] = 10.0 * movMeanMagSqrd[bvstride];
  }
  if ((magSqrd.size(0) != movMeanMagSqrd.size(0)) &&
      ((magSqrd.size(0) != 1) && (movMeanMagSqrd.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(magSqrd.size(0), movMeanMagSqrd.size(0),
                                &c_emlrtECI);
  }
  if ((magSqrd.size(1) != movMeanMagSqrd.size(1)) &&
      ((magSqrd.size(1) != 1) && (movMeanMagSqrd.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(magSqrd.size(1), movMeanMagSqrd.size(1),
                                &d_emlrtECI);
  }
  if ((magSqrd.size(0) == movMeanMagSqrd.size(0)) &&
      (magSqrd.size(1) == movMeanMagSqrd.size(1))) {
    magSqrdMask.set_size(magSqrd.size(0), magSqrd.size(1));
    nx = magSqrd.size(0) * magSqrd.size(1);
    for (bvstride = 0; bvstride < nx; bvstride++) {
      magSqrdMask[bvstride] = (magSqrd[bvstride] > movMeanMagSqrd[bvstride]);
    }
  } else {
    gt(magSqrdMask, magSqrd, movMeanMagSqrd);
  }
  nx = magSqrdMask.size(0) * magSqrdMask.size(1) - 1;
  len = 0;
  for (stride = 0; stride <= nx; stride++) {
    if (magSqrdMask[stride]) {
      len++;
    }
  }
  counts.set_size(len);
  len = 0;
  for (stride = 0; stride <= nx; stride++) {
    if (magSqrdMask[stride]) {
      counts[len] = stride + 1;
      len++;
    }
  }
  nx = counts.size(0) - 1;
  len = magSqrd.size(0) * magSqrd.size(1);
  for (bvstride = 0; bvstride <= nx; bvstride++) {
    if ((counts[bvstride] < 1) || (counts[bvstride] > len)) {
      rtDynamicBoundsError(counts[bvstride], 1, len, &f_emlrtBCI);
    }
    magSqrd[counts[bvstride] - 1] = rtNaN;
  }
  varargin_1 = dt;
  varargin_1 = varargin_1 * varargin_1 / T;
  if ((magSqrd.size(0) == 0) || (magSqrd.size(1) == 0)) {
    yv.set_size(magSqrd.size(0));
    nx = magSqrd.size(0);
    for (bvstride = 0; bvstride < nx; bvstride++) {
      yv[bvstride] = 0.0;
    }
    counts.set_size(magSqrd.size(0));
    nx = magSqrd.size(0);
    for (bvstride = 0; bvstride < nx; bvstride++) {
      counts[bvstride] = 0;
    }
  } else {
    int ix;
    stride = magSqrd.size(0);
    bvstride = magSqrd.size(0) << 10;
    yv.set_size(magSqrd.size(0));
    counts.set_size(magSqrd.size(0));
    xv.set_size(magSqrd.size(0));
    if (magSqrd.size(1) <= 1024) {
      len = magSqrd.size(1);
      lastBlockLength = 0;
      outsize_idx_0 = 1;
    } else {
      len = 1024;
      outsize_idx_0 = magSqrd.size(1) / 1024;
      lastBlockLength = magSqrd.size(1) - (outsize_idx_0 << 10);
      if (lastBlockLength > 0) {
        outsize_idx_0++;
      } else {
        lastBlockLength = 1024;
      }
    }
    if (magSqrd.size(0) > 2147483646) {
      coder::check_forloop_overflow_error();
    }
    for (int xj{0}; xj < stride; xj++) {
      if (std::isnan(magSqrd[xj])) {
        yv[xj] = 0.0;
        counts[xj] = 0;
      } else {
        yv[xj] = magSqrd[xj];
        counts[xj] = 1;
      }
      xv[xj] = 0.0;
    }
    for (int k{2}; k <= len; k++) {
      xoffset = (k - 1) * stride;
      if (stride > 2147483646) {
        coder::check_forloop_overflow_error();
      }
      for (int xj{0}; xj < stride; xj++) {
        ix = xoffset + xj;
        if (!std::isnan(magSqrd[ix])) {
          yv[xj] = yv[xj] + magSqrd[ix];
          counts[xj] = counts[xj] + 1;
        }
      }
    }
    for (int ib{2}; ib <= outsize_idx_0; ib++) {
      len = (ib - 1) * bvstride;
      if (stride > 2147483646) {
        coder::check_forloop_overflow_error();
      }
      for (int xj{0}; xj < stride; xj++) {
        ix = len + xj;
        if (std::isnan(magSqrd[ix])) {
          xv[xj] = 0.0;
        } else {
          xv[xj] = magSqrd[ix];
          counts[xj] = counts[xj] + 1;
        }
      }
      if (ib == outsize_idx_0) {
        nx = lastBlockLength;
      } else {
        nx = 1024;
      }
      for (int k{2}; k <= nx; k++) {
        xoffset = len + (k - 1) * stride;
        for (int xj{0}; xj < stride; xj++) {
          ix = xoffset + xj;
          if (!std::isnan(magSqrd[ix])) {
            xv[xj] = xv[xj] + magSqrd[ix];
            counts[xj] = counts[xj] + 1;
          }
        }
      }
      for (int xj{0}; xj < stride; xj++) {
        yv[xj] = yv[xj] + xv[xj];
      }
    }
  }
  xv.set_size(counts.size(0));
  nx = counts.size(0);
  for (bvstride = 0; bvstride < nx; bvstride++) {
    xv[bvstride] = counts[bvstride];
  }
  if ((yv.size(0) != 1) && (xv.size(0) != 1) && (yv.size(0) != xv.size(0))) {
    y_rtErrorWithMessageID(kb_emlrtRTEI.fName, kb_emlrtRTEI.lineNo);
  }
  if (yv.size(0) == xv.size(0)) {
    nx = yv.size(0);
    for (bvstride = 0; bvstride < nx; bvstride++) {
      yv[bvstride] = varargin_1 * (yv[bvstride] / xv[bvstride]);
    }
    coder::internal::validator_check_size(yv, psd);
  } else {
    binary_expand_op(this, varargin_1, yv, xv);
  }
  // use median to exclude outliers from short pulses
}

//
// File trailer for wfmstft.cpp
//
// [EOF]
//
