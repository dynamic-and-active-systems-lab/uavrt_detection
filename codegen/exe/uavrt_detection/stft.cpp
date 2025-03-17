//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: stft.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "stft.h"
#include "FFTImplementationCallback.h"
#include "computeDFT.h"
#include "eml_int_forloop_overflow_check.h"
#include "formatSTFTOutput.h"
#include "indexShapeCheck.h"
#include "psdfreqvec.h"
#include "rt_nonfinite.h"
#include "stickyStruct.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "validateattributes.h"
#include "coder_array.h"
#include "omp.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>

// Variable Definitions
static rtEqualityCheckInfo c_emlrtECI{
    -1,              // nDims
    35,              // lineNo
    "getSTFTColumns" // fName
};

static rtBoundsCheckInfo d_emlrtBCI{
    35,              // lineNo
    "",              // aName
    "getSTFTColumns" // fName
};

static rtBoundsCheckInfo e_emlrtBCI{
    35,              // lineNo
    "",              // aName
    "getSTFTColumns" // fName
};

static rtDoubleCheckInfo c_emlrtDCI{
    35,              // lineNo
    "getSTFTColumns" // fName
};

static rtBoundsCheckInfo f_emlrtBCI{
    35,              // lineNo
    "",              // aName
    "getSTFTColumns" // fName
};

static rtDoubleCheckInfo d_emlrtDCI{
    35,              // lineNo
    "getSTFTColumns" // fName
};

static rtDoubleCheckInfo e_emlrtDCI{
    15,              // lineNo
    "getSTFTColumns" // fName
};

static rtDoubleCheckInfo f_emlrtDCI{
    15,              // lineNo
    "getSTFTColumns" // fName
};

static rtRunTimeErrorInfo y_emlrtRTEI{
    336,                // lineNo
    "verifyDataAndTime" // fName
};

static rtRunTimeErrorInfo ab_emlrtRTEI{
    318,                // lineNo
    "verifyDataAndTime" // fName
};

static rtBoundsCheckInfo g_emlrtBCI{
    278,          // lineNo
    "",           // aName
    "computeSTFT" // fName
};

static rtBoundsCheckInfo h_emlrtBCI{
    278,          // lineNo
    "",           // aName
    "computeSTFT" // fName
};

static rtBoundsCheckInfo i_emlrtBCI{
    277,          // lineNo
    "",           // aName
    "computeSTFT" // fName
};

static rtBoundsCheckInfo j_emlrtBCI{
    277,          // lineNo
    "",           // aName
    "computeSTFT" // fName
};

static rtRunTimeErrorInfo cb_emlrtRTEI{
    14,                // lineNo
    "validatepositive" // fName
};

// Function Declarations
static void k_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum);

static void rtErrorWithMessageID(const long i, const char *aFcnName,
                                 int aLineNum);

static void s_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void u_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : const char *r
//                const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void k_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((outStream << "Expected ") << r) << " to be positive.";
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
// Arguments    : const long i
//                const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void rtErrorWithMessageID(const long i, const char *aFcnName,
                                 int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((outStream << "Input signal length must be greater than or equal to the "
                 "window length, ")
   << i)
      << ".";
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
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void s_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Colon operands must be in range of the data type and exactly "
               "representable without loss of precision.";
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
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void u_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Input signal must have at least 2 samples.";
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
// Arguments    : const array<creal32_T, 2U> &x
//                double varargin_1
//                const array<double, 1U> &varargin_3
//                double varargin_5
//                double varargin_7
//                array<creal32_T, 2U> &varargout_1
//                array<float, 1U> &varargout_2
//                array<float, 1U> &varargout_3
// Return Type  : void
//
namespace coder {
void stft(const array<creal32_T, 2U> &x, double varargin_1,
          const array<double, 1U> &varargin_3, double varargin_5,
          double varargin_7, array<creal32_T, 2U> &varargout_1,
          array<float, 1U> &varargout_2, array<float, 1U> &varargout_3)
{
  static rtRunTimeErrorInfo rc_emlrtRTEI{
      398,         // lineNo
      "checkrange" // fName
  };
  internal::j_stickyStruct obj;
  array<creal32_T, 2U> c;
  array<creal32_T, 2U> xin;
  array<double, 1U> b_f;
  array<double, 1U> f;
  array<float, 2U> y;
  double hopSize;
  double nCol;
  float b_varargin_3;
  int iv[2];
  int bcoef;
  int csz_idx_0;
  int i;
  int i1;
  int i2;
  int k;
  int loop_ub;
  boolean_T exitg1;
  boolean_T p;
  validateattributes(varargin_3);
  validateattributes(static_cast<double>(varargin_3.size(0)));
  validateattributes(varargin_5, static_cast<double>(varargin_3.size(0)));
  b_validateattributes(varargin_7, static_cast<double>(varargin_3.size(0)));
  p = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= x.size(1) - 1)) {
    if ((!std::isinf(x[k].re)) && (!std::isinf(x[k].im)) &&
        ((!std::isnan(x[k].re)) && (!std::isnan(x[k].im)))) {
      k++;
    } else {
      p = false;
      exitg1 = true;
    }
  }
  if (!p) {
    i_rtErrorWithMessageID("X", w_emlrtRTEI.fName, w_emlrtRTEI.lineNo);
  }
  p = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= x.size(1) - 1)) {
    if ((!std::isnan(x[k].re)) && (!std::isnan(x[k].im))) {
      k++;
    } else {
      p = false;
      exitg1 = true;
    }
  }
  if (!p) {
    h_rtErrorWithMessageID("X", v_emlrtRTEI.fName, v_emlrtRTEI.lineNo);
  }
  if (x.size(1) == 0) {
    g_rtErrorWithMessageID("X", u_emlrtRTEI.fName, u_emlrtRTEI.lineNo);
  }
  if (x.size(1) < 2) {
    u_rtErrorWithMessageID(ab_emlrtRTEI.fName, ab_emlrtRTEI.lineNo);
  }
  if (varargin_3.size(0) > x.size(1)) {
    rtErrorWithMessageID(static_cast<long>(varargin_3.size(0)),
                         y_emlrtRTEI.fName, y_emlrtRTEI.lineNo);
  }
  if (std::isinf(varargin_1) || std::isnan(varargin_1)) {
    i_rtErrorWithMessageID("sample rate", w_emlrtRTEI.fName,
                           w_emlrtRTEI.lineNo);
  }
  if (varargin_1 <= 0.0) {
    k_rtErrorWithMessageID("sample rate", cb_emlrtRTEI.fName,
                           cb_emlrtRTEI.lineNo);
  }
  loop_ub = varargin_3.size(0);
  obj.value.set_size(varargin_3.size(0));
  for (i = 0; i < loop_ub; i++) {
    obj.value[i] = static_cast<float>(varargin_3[i]);
  }
  hopSize = static_cast<double>(varargin_3.size(0)) - varargin_5;
  nCol = std::trunc((static_cast<double>(x.size(1)) - varargin_5) / hopSize);
  if (!(nCol >= 0.0)) {
    rtNonNegativeError(nCol, f_emlrtDCI);
  }
  if (nCol != static_cast<int>(nCol)) {
    rtIntegerError(nCol, e_emlrtDCI);
  }
  i = static_cast<int>(nCol);
  xin.set_size(varargin_3.size(0), static_cast<int>(nCol));
  bcoef = varargin_3.size(0) * static_cast<int>(nCol);
  for (i1 = 0; i1 < bcoef; i1++) {
    xin[i1].re = 0.0F;
    xin[i1].im = 0.0F;
  }
  if (nCol - 1.0 < 0.0) {
    y.set_size(y.size(0), 0);
  } else {
    if (!(nCol - 1.0 <= 3.4028234663852886E+38)) {
      s_rtErrorWithMessageID(rc_emlrtRTEI.fName, rc_emlrtRTEI.lineNo);
    }
    y.set_size(1, static_cast<int>(nCol - 1.0) + 1);
    bcoef = static_cast<int>(nCol - 1.0);
    for (i1 = 0; i1 <= bcoef; i1++) {
      y[i1] = static_cast<float>(i1);
    }
  }
  for (bcoef = 0; bcoef < i; bcoef++) {
    double d;
    double d1;
    d = hopSize * ((static_cast<double>(bcoef) + 1.0) - 1.0);
    d1 = static_cast<double>(varargin_3.size(0)) + d;
    if (d + 1.0 > d1) {
      i1 = 0;
      i2 = 0;
    } else {
      if (d + 1.0 != static_cast<int>(std::floor(d + 1.0))) {
        rtIntegerError(d + 1.0, d_emlrtDCI);
      }
      if ((static_cast<int>(d + 1.0) < 1) ||
          (static_cast<int>(d + 1.0) > x.size(1))) {
        rtDynamicBoundsError(static_cast<int>(d + 1.0), 1, x.size(1),
                             f_emlrtBCI);
      }
      i1 = static_cast<int>(d + 1.0) - 1;
      if (d1 != static_cast<int>(std::floor(d1))) {
        rtIntegerError(d1, c_emlrtDCI);
      }
      if ((static_cast<int>(d1) < 1) || (static_cast<int>(d1) > x.size(1))) {
        rtDynamicBoundsError(static_cast<int>(d1), 1, x.size(1), e_emlrtBCI);
      }
      i2 = static_cast<int>(d1);
    }
    if ((bcoef + 1 < 1) || (bcoef + 1 > static_cast<int>(nCol))) {
      rtDynamicBoundsError(bcoef + 1, 1, static_cast<int>(nCol), d_emlrtBCI);
    }
    i2 -= i1;
    rtSubAssignSizeCheck(&loop_ub, 1, &i2, 1, c_emlrtECI);
    for (i2 = 0; i2 < loop_ub; i2++) {
      xin[i2 + xin.size(0) * bcoef] = x[i1 + i2];
    }
  }
  y.set_size(1, y.size(1));
  b_varargin_3 =
      static_cast<float>(static_cast<double>(varargin_3.size(0)) / 2.0);
  loop_ub = y.size(1) - 1;
  for (i1 = 0; i1 <= loop_ub; i1++) {
    y[i1] = (y[i1] * static_cast<float>(hopSize) + b_varargin_3) /
            static_cast<float>(varargin_1);
  }
  if (xin.size(0) == 1) {
    csz_idx_0 = varargin_3.size(0);
  } else if (obj.value.size(0) == 1) {
    csz_idx_0 = varargin_3.size(0);
  } else if (obj.value.size(0) == xin.size(0)) {
    csz_idx_0 = varargin_3.size(0);
  } else {
    t_rtErrorWithMessageID(x_emlrtRTEI.fName, x_emlrtRTEI.lineNo);
  }
  c.set_size(csz_idx_0, static_cast<int>(nCol));
  if ((csz_idx_0 != 0) && (xin.size(1) != 0)) {
    bcoef = (xin.size(1) != 1);
    loop_ub = (obj.value.size(0) != 1);
    for (k = 0; k < i; k++) {
      csz_idx_0 = bcoef * k;
      i1 = c.size(0);
      for (int b_k{0}; b_k < i1; b_k++) {
        i2 = loop_ub * b_k;
        b_varargin_3 = obj.value[i2];
        c[b_k + c.size(0) * k].re =
            b_varargin_3 * xin[i2 + xin.size(0) * csz_idx_0].re;
        c[b_k + c.size(0) * k].im =
            b_varargin_3 * xin[i2 + xin.size(0) * csz_idx_0].im;
      }
    }
  }
  computeDFT(c, varargin_7, varargin_1, varargout_1, f);
  b_signal::internal::stft::formatSTFTOutput(varargout_1, f, b_f);
  if (varargout_1.size(0) < 1) {
    loop_ub = 0;
  } else {
    if (b_f.size(0) < 1) {
      rtDynamicBoundsError(1, 1, b_f.size(0), j_emlrtBCI);
    }
    if (varargout_1.size(0) > b_f.size(0)) {
      rtDynamicBoundsError(varargout_1.size(0), 1, b_f.size(0), i_emlrtBCI);
    }
    loop_ub = varargout_1.size(0);
  }
  iv[0] = 1;
  iv[1] = loop_ub;
  internal::indexShapeCheck(b_f.size(0), iv);
  varargout_2.set_size(loop_ub);
  for (i = 0; i < loop_ub; i++) {
    varargout_2[i] = static_cast<float>(b_f[i]);
  }
  if (varargout_1.size(1) < 1) {
    loop_ub = 0;
  } else {
    if (y.size(1) < 1) {
      rtDynamicBoundsError(1, 1, y.size(1), h_emlrtBCI);
    }
    if (varargout_1.size(1) > y.size(1)) {
      rtDynamicBoundsError(varargout_1.size(1), 1, y.size(1), g_emlrtBCI);
    }
    loop_ub = varargout_1.size(1);
  }
  varargout_3.set_size(loop_ub);
  for (i = 0; i < loop_ub; i++) {
    varargout_3[i] = y[i];
  }
}

//
// Arguments    : const array<creal_T, 2U> &x
//                double varargin_1
//                const array<double, 1U> &varargin_3
//                double varargin_5
//                double varargin_7
//                array<creal_T, 3U> &varargout_1
//                array<double, 1U> &varargout_2
//                array<double, 1U> &varargout_3
// Return Type  : void
//
void stft(const array<creal_T, 2U> &x, double varargin_1,
          const array<double, 1U> &varargin_3, double varargin_5,
          double varargin_7, array<creal_T, 3U> &varargout_1,
          array<double, 1U> &varargout_2, array<double, 1U> &varargout_3)
{
  array<creal_T, 3U> b_c;
  array<creal_T, 3U> xin;
  array<creal_T, 2U> b_wrappedData;
  array<creal_T, 2U> wrappedData;
  array<creal_T, 1U> b_x;
  array<double, 2U> costab;
  array<double, 2U> sintab;
  array<double, 2U> sintabinv;
  array<double, 2U> y;
  array<double, 1U> b_f;
  array<double, 1U> f;
  double b_varargin_3;
  double hopSize;
  double nCol;
  int b_xin[3];
  int c[2];
  int b_bcoef;
  int b_loop_ub;
  int b_varargin_5;
  int bcoef;
  int c_tmp;
  int csz_idx_0;
  int i;
  int i1;
  int i2;
  int i3;
  int k;
  int loop_ub;
  int loop_ub_tmp;
  boolean_T exitg1;
  boolean_T useRadix2;
  validateattributes(varargin_3);
  validateattributes(static_cast<double>(varargin_3.size(0)));
  validateattributes(varargin_5, static_cast<double>(varargin_3.size(0)));
  b_validateattributes(varargin_7, static_cast<double>(varargin_3.size(0)));
  useRadix2 = true;
  bcoef = x.size(0) * x.size(1);
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= bcoef - 1)) {
    if ((!std::isinf(x[k].re)) && (!std::isinf(x[k].im)) &&
        ((!std::isnan(x[k].re)) && (!std::isnan(x[k].im)))) {
      k++;
    } else {
      useRadix2 = false;
      exitg1 = true;
    }
  }
  if (!useRadix2) {
    i_rtErrorWithMessageID("X", w_emlrtRTEI.fName, w_emlrtRTEI.lineNo);
  }
  useRadix2 = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= bcoef - 1)) {
    if ((!std::isnan(x[k].re)) && (!std::isnan(x[k].im))) {
      k++;
    } else {
      useRadix2 = false;
      exitg1 = true;
    }
  }
  if (!useRadix2) {
    h_rtErrorWithMessageID("X", v_emlrtRTEI.fName, v_emlrtRTEI.lineNo);
  }
  if ((x.size(0) == 0) || (x.size(1) == 0)) {
    g_rtErrorWithMessageID("X", u_emlrtRTEI.fName, u_emlrtRTEI.lineNo);
  }
  if (x.size(0) == 1) {
    bcoef = x.size(1);
    wrappedData.set_size(x.size(1), 1);
    for (i = 0; i < bcoef; i++) {
      wrappedData[i] = x[i];
    }
  } else {
    wrappedData.set_size(x.size(0), x.size(1));
    for (i = 0; i < bcoef; i++) {
      wrappedData[i] = x[i];
    }
  }
  if (wrappedData.size(0) < 2) {
    u_rtErrorWithMessageID(ab_emlrtRTEI.fName, ab_emlrtRTEI.lineNo);
  }
  if (varargin_3.size(0) > wrappedData.size(0)) {
    rtErrorWithMessageID(static_cast<long>(varargin_3.size(0)),
                         y_emlrtRTEI.fName, y_emlrtRTEI.lineNo);
  }
  if (std::isinf(varargin_1) || std::isnan(varargin_1)) {
    i_rtErrorWithMessageID("sample rate", w_emlrtRTEI.fName,
                           w_emlrtRTEI.lineNo);
  }
  if (varargin_1 <= 0.0) {
    k_rtErrorWithMessageID("sample rate", cb_emlrtRTEI.fName,
                           cb_emlrtRTEI.lineNo);
  }
  hopSize = static_cast<double>(varargin_3.size(0)) - varargin_5;
  nCol = std::trunc((static_cast<double>(wrappedData.size(0)) - varargin_5) /
                    hopSize);
  if (!(nCol >= 0.0)) {
    rtNonNegativeError(nCol, f_emlrtDCI);
  }
  if (nCol != static_cast<int>(nCol)) {
    rtIntegerError(nCol, e_emlrtDCI);
  }
  bcoef = varargin_3.size(0);
  i = static_cast<int>(nCol);
  loop_ub = wrappedData.size(1);
  xin.set_size(varargin_3.size(0), static_cast<int>(nCol), wrappedData.size(1));
  loop_ub_tmp =
      varargin_3.size(0) * static_cast<int>(nCol) * wrappedData.size(1);
  for (i1 = 0; i1 < loop_ub_tmp; i1++) {
    xin[i1].re = 0.0;
    xin[i1].im = 0.0;
  }
  if (nCol - 1.0 < 0.0) {
    y.set_size(y.size(0), 0);
  } else {
    y.set_size(1, static_cast<int>(nCol - 1.0) + 1);
    b_bcoef = static_cast<int>(nCol - 1.0);
    for (i1 = 0; i1 <= b_bcoef; i1++) {
      y[i1] = i1;
    }
  }
  if (static_cast<int>(nCol) - 1 >= 0) {
    c[1] = wrappedData.size(1);
    b_loop_ub = wrappedData.size(1);
  }
  if (i - 1 >= 0) {
    b_xin[0] = bcoef;
    b_xin[1] = 1;
    b_xin[2] = loop_ub;
  }
  for (b_bcoef = 0; b_bcoef < i; b_bcoef++) {
    double d;
    b_varargin_3 = hopSize * ((static_cast<double>(b_bcoef) + 1.0) - 1.0);
    d = static_cast<double>(varargin_3.size(0)) + b_varargin_3;
    if (b_varargin_3 + 1.0 > d) {
      i1 = 0;
      i2 = 0;
    } else {
      if (b_varargin_3 + 1.0 !=
          static_cast<int>(std::floor(b_varargin_3 + 1.0))) {
        rtIntegerError(b_varargin_3 + 1.0, d_emlrtDCI);
      }
      if ((static_cast<int>(b_varargin_3 + 1.0) < 1) ||
          (static_cast<int>(b_varargin_3 + 1.0) > wrappedData.size(0))) {
        rtDynamicBoundsError(static_cast<int>(b_varargin_3 + 1.0), 1,
                             wrappedData.size(0), f_emlrtBCI);
      }
      i1 = static_cast<int>(b_varargin_3 + 1.0) - 1;
      if (d != static_cast<int>(std::floor(d))) {
        rtIntegerError(d, c_emlrtDCI);
      }
      if ((static_cast<int>(d) < 1) ||
          (static_cast<int>(d) > wrappedData.size(0))) {
        rtDynamicBoundsError(static_cast<int>(d), 1, wrappedData.size(0),
                             e_emlrtBCI);
      }
      i2 = static_cast<int>(d);
    }
    if ((b_bcoef + 1 < 1) || (b_bcoef + 1 > static_cast<int>(nCol))) {
      rtDynamicBoundsError(b_bcoef + 1, 1, static_cast<int>(nCol), d_emlrtBCI);
    }
    c_tmp = i2 - i1;
    c[0] = c_tmp;
    rtSubAssignSizeCheck(&b_xin[0], 3, &c[0], 2, c_emlrtECI);
    b_wrappedData.set_size(c_tmp, loop_ub);
    for (i2 = 0; i2 < b_loop_ub; i2++) {
      for (i3 = 0; i3 < c_tmp; i3++) {
        b_wrappedData[i3 + b_wrappedData.size(0) * i2] =
            wrappedData[(i1 + i3) + wrappedData.size(0) * i2];
      }
    }
    for (i1 = 0; i1 < loop_ub; i1++) {
      for (i2 = 0; i2 < bcoef; i2++) {
        xin[(i2 + xin.size(0) * b_bcoef) + xin.size(0) * xin.size(1) * i1] =
            b_wrappedData[i2 + bcoef * i1];
      }
    }
  }
  y.set_size(1, y.size(1));
  b_varargin_3 = static_cast<double>(varargin_3.size(0)) / 2.0;
  bcoef = y.size(1) - 1;
  for (i1 = 0; i1 <= bcoef; i1++) {
    y[i1] = (y[i1] * hopSize + b_varargin_3) / varargin_1;
  }
  if (xin.size(0) == 1) {
    csz_idx_0 = varargin_3.size(0);
  } else if (varargin_3.size(0) == 1) {
    csz_idx_0 = varargin_3.size(0);
  } else if (varargin_3.size(0) == xin.size(0)) {
    csz_idx_0 = varargin_3.size(0);
  } else {
    t_rtErrorWithMessageID(x_emlrtRTEI.fName, x_emlrtRTEI.lineNo);
  }
  b_c.set_size(csz_idx_0, static_cast<int>(nCol), wrappedData.size(1));
  if ((csz_idx_0 != 0) && (xin.size(1) != 0)) {
    b_bcoef = (xin.size(2) != 1);
    bcoef = (xin.size(1) != 1);
    b_loop_ub = (varargin_3.size(0) != 1);
    for (k = 0; k < loop_ub; k++) {
      csz_idx_0 = b_bcoef * k;
      for (loop_ub_tmp = 0; loop_ub_tmp < i; loop_ub_tmp++) {
        b_varargin_5 = bcoef * loop_ub_tmp;
        i1 = b_c.size(0);
        for (c_tmp = 0; c_tmp < i1; c_tmp++) {
          i2 = b_loop_ub * c_tmp;
          b_varargin_3 = varargin_3[i2];
          b_c[(c_tmp + b_c.size(0) * loop_ub_tmp) +
              b_c.size(0) * b_c.size(1) * k]
              .re = b_varargin_3 * xin[(i2 + xin.size(0) * b_varargin_5) +
                                       xin.size(0) * xin.size(1) * csz_idx_0]
                                       .re;
          b_c[(c_tmp + b_c.size(0) * loop_ub_tmp) +
              b_c.size(0) * b_c.size(1) * k]
              .im = b_varargin_3 * xin[(i2 + xin.size(0) * b_varargin_5) +
                                       xin.size(0) * xin.size(1) * csz_idx_0]
                                       .im;
        }
      }
    }
  }
  if (b_c.size(0) > varargin_7) {
    if (!(varargin_7 >= 0.0)) {
      rtNonNegativeError(varargin_7, g_emlrtDCI);
    }
    if (varargin_7 != std::floor(varargin_7)) {
      rtIntegerError(varargin_7, h_emlrtDCI);
    }
    loop_ub_tmp = static_cast<int>(varargin_7);
    xin.set_size(loop_ub_tmp, static_cast<int>(nCol), wrappedData.size(1));
    b_varargin_5 = static_cast<int>(varargin_7) * b_c.size(1) * b_c.size(2);
    for (i = 0; i < b_varargin_5; i++) {
      xin[i].re = 0.0;
      xin[i].im = 0.0;
    }
    i = static_cast<int>(static_cast<double>(b_c.size(1)) *
                         static_cast<double>(b_c.size(2)));
    for (b_loop_ub = 0; b_loop_ub < i; b_loop_ub++) {
      b_varargin_5 = b_c.size(0);
      c[0] = b_c.size(0);
      c_tmp = b_c.size(1) * b_c.size(2);
      if ((static_cast<int>(static_cast<unsigned int>(b_loop_ub) + 1U) < 1) ||
          (static_cast<int>(static_cast<unsigned int>(b_loop_ub) + 1U) >
           c_tmp)) {
        rtDynamicBoundsError(
            static_cast<int>(static_cast<unsigned int>(b_loop_ub) + 1U), 1,
            c_tmp, k_emlrtBCI);
      }
      b_x.set_size(b_c.size(0));
      for (i1 = 0; i1 < b_varargin_5; i1++) {
        b_x[i1] = b_c[i1 + c[0] * b_loop_ub];
      }
      if (!(varargin_7 >= 1.0)) {
        b_rtErrorWithMessageID(1, gb_emlrtRTEI.fName, gb_emlrtRTEI.lineNo);
      }
      if (b_c.size(0) == 1) {
        wrappedData.set_size(1, loop_ub_tmp);
        for (i1 = 0; i1 < loop_ub_tmp; i1++) {
          wrappedData[i1].re = 0.0;
          wrappedData[i1].im = 0.0;
        }
      } else {
        wrappedData.set_size(loop_ub_tmp, 1);
        for (i1 = 0; i1 < loop_ub_tmp; i1++) {
          wrappedData[i1].re = 0.0;
          wrappedData[i1].im = 0.0;
        }
      }
      i1 = static_cast<int>(static_cast<unsigned int>(b_c.size(0)) /
                            static_cast<unsigned int>(varargin_7));
      bcoef = i1 * static_cast<int>(varargin_7);
      b_bcoef = b_c.size(0) - bcoef;
      if (b_bcoef > 2147483646) {
        check_forloop_overflow_error();
      }
      for (k = 0; k < b_bcoef; k++) {
        i2 = wrappedData.size(0) * wrappedData.size(1);
        if ((k + 1 < 1) || (k + 1 > i2)) {
          rtDynamicBoundsError(k + 1, 1, i2, n_emlrtBCI);
        }
        i3 = (bcoef + k) + 1;
        if ((i3 < 1) || (i3 > b_varargin_5)) {
          rtDynamicBoundsError(i3, 1, b_varargin_5, m_emlrtBCI);
        }
        wrappedData[k].re = b_x[i3 - 1].re;
        if (k + 1 > i2) {
          rtDynamicBoundsError(k + 1, 1, i2, n_emlrtBCI);
        }
        wrappedData[k].im = b_x[i3 - 1].im;
      }
      i2 = b_bcoef + 1;
      for (k = i2; k <= loop_ub_tmp; k++) {
        i3 = wrappedData.size(0) * wrappedData.size(1);
        if ((k < 1) || (k > i3)) {
          rtDynamicBoundsError(k, 1, i3, o_emlrtBCI);
        }
        wrappedData[k - 1].re = 0.0;
        if (k > i3) {
          rtDynamicBoundsError(k, 1, i3, o_emlrtBCI);
        }
        wrappedData[k - 1].im = 0.0;
      }
      if (i1 > 2147483646) {
        check_forloop_overflow_error();
      }
      for (b_bcoef = 0; b_bcoef < i1; b_bcoef++) {
        bcoef = b_bcoef * static_cast<int>(varargin_7);
        for (k = 0; k < loop_ub_tmp; k++) {
          i2 = wrappedData.size(0) * wrappedData.size(1);
          if (k + 1 > i2) {
            rtDynamicBoundsError(k + 1, 1, i2, r_emlrtBCI);
          }
          i3 = (bcoef + k) + 1;
          if ((i3 < 1) || (i3 > b_varargin_5)) {
            rtDynamicBoundsError(i3, 1, b_varargin_5, q_emlrtBCI);
          }
          wrappedData[k].re = wrappedData[k].re + b_x[i3 - 1].re;
          if (k + 1 > i2) {
            rtDynamicBoundsError(k + 1, 1, i2, p_emlrtBCI);
          }
          wrappedData[k].im = wrappedData[k].im + b_x[i3 - 1].im;
        }
      }
      if ((b_loop_ub + 1 < 1) || (b_loop_ub + 1 > c_tmp)) {
        rtDynamicBoundsError(b_loop_ub + 1, 1, c_tmp, l_emlrtBCI);
      }
      bcoef = wrappedData.size(0) * wrappedData.size(1);
      rtSubAssignSizeCheck(&loop_ub_tmp, 1, &bcoef, 1, d_emlrtECI);
      for (i1 = 0; i1 < loop_ub_tmp; i1++) {
        xin[i1 + static_cast<int>(varargin_7) * b_loop_ub] = wrappedData[i1];
      }
    }
  } else {
    xin.set_size(b_c.size(0), static_cast<int>(nCol), wrappedData.size(1));
    loop_ub_tmp = b_c.size(0) * b_c.size(1) * b_c.size(2);
    for (i = 0; i < loop_ub_tmp; i++) {
      xin[i] = b_c[i];
    }
  }
  if (xin.size(0) == 1) {
    v_rtErrorWithMessageID(db_emlrtRTEI.fName, db_emlrtRTEI.lineNo);
  }
  if ((!(varargin_7 >= 0.0)) || (!(varargin_7 == std::floor(varargin_7)))) {
    w_rtErrorWithMessageID(eb_emlrtRTEI.fName, eb_emlrtRTEI.lineNo);
  }
  if (!(varargin_7 <= 2.147483647E+9)) {
    x_rtErrorWithMessageID(fb_emlrtRTEI.fName, fb_emlrtRTEI.lineNo);
  }
  if ((xin.size(0) == 0) || (xin.size(1) == 0) ||
      (static_cast<int>(varargin_7) == 0)) {
    varargout_1.set_size(static_cast<int>(varargin_7), xin.size(1),
                         xin.size(2));
    loop_ub_tmp = static_cast<int>(varargin_7) * xin.size(1) * xin.size(2);
    for (i = 0; i < loop_ub_tmp; i++) {
      varargout_1[i].re = 0.0;
      varargout_1[i].im = 0.0;
    }
  } else {
    useRadix2 =
        ((static_cast<int>(varargin_7) > 0) &&
         (static_cast<int>(
              static_cast<unsigned int>(static_cast<int>(varargin_7)) &
              static_cast<unsigned int>(static_cast<int>(varargin_7) - 1)) ==
          0));
    bcoef = internal::fft::FFTImplementationCallback::get_algo_sizes(
        static_cast<int>(varargin_7), useRadix2, b_bcoef);
    internal::fft::FFTImplementationCallback::generate_twiddle_tables(
        b_bcoef, useRadix2, costab, sintab, sintabinv);
    if (useRadix2) {
      internal::fft::FFTImplementationCallback::r2br_r2dit_trig(
          xin, static_cast<int>(varargin_7), costab, sintab, varargout_1);
    } else {
      internal::fft::FFTImplementationCallback::dobluesteinfft(
          xin, bcoef, static_cast<int>(varargin_7), costab, sintab, sintabinv,
          varargout_1);
    }
  }
  psdfreqvec(varargin_7, varargin_1, f);
  b_signal::internal::stft::formatSTFTOutput(varargout_1, f, b_f);
  if (varargout_1.size(0) < 1) {
    bcoef = 0;
  } else {
    if (b_f.size(0) < 1) {
      rtDynamicBoundsError(1, 1, b_f.size(0), j_emlrtBCI);
    }
    if (varargout_1.size(0) > b_f.size(0)) {
      rtDynamicBoundsError(varargout_1.size(0), 1, b_f.size(0), i_emlrtBCI);
    }
    bcoef = varargout_1.size(0);
  }
  c[0] = 1;
  c[1] = bcoef;
  internal::indexShapeCheck(b_f.size(0), c);
  varargout_2.set_size(bcoef);
  for (i = 0; i < bcoef; i++) {
    varargout_2[i] = b_f[i];
  }
  if (varargout_1.size(1) < 1) {
    bcoef = 0;
  } else {
    if (y.size(1) < 1) {
      rtDynamicBoundsError(1, 1, y.size(1), h_emlrtBCI);
    }
    if (varargout_1.size(1) > y.size(1)) {
      rtDynamicBoundsError(varargout_1.size(1), 1, y.size(1), g_emlrtBCI);
    }
    bcoef = varargout_1.size(1);
  }
  varargout_3.set_size(bcoef);
  for (i = 0; i < bcoef; i++) {
    varargout_3[i] = y[i];
  }
}

} // namespace coder

//
// File trailer for stft.cpp
//
// [EOF]
//
