//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: evfit.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Apr-2023 11:47:02
//

// Include Files
#include "evfit.h"
#include "blockedSummation.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include "omp.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <sstream>
#include <stdexcept>
#include <string.h>
#include <string>

// Function Declarations
namespace coder {
static double lkeqn(double sigma, const ::coder::array<double, 1U> &x,
                    double xbarWgtUnc);

}
static void pb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void qb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void rb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void sb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void times(coder::array<double, 1U> &in1,
                  const coder::array<double, 1U> &in2,
                  const coder::array<double, 1U> &in3);

// Function Definitions
//
// Arguments    : double sigma
//                const ::coder::array<double, 1U> &x
//                double xbarWgtUnc
// Return Type  : double
//
namespace coder {
static double lkeqn(double sigma, const ::coder::array<double, 1U> &x,
                    double xbarWgtUnc)
{
  static rtEqualityCheckInfo g_emlrtECI{
      1,                                                        // nDims
      273,                                                      // lineNo
      34,                                                       // colNo
      "lkeqn",                                                  // fName
      "C:\\Program Files\\MATLAB\\toolbox\\stats\\eml\\evfit.m" // pName
  };
  array<double, 1U> b_x;
  array<double, 1U> wt;
  int nx;
  wt.set_size(x.size(0));
  nx = x.size(0);
  for (int k{0}; k < nx; k++) {
    wt[k] = x[k] / sigma;
  }
  nx = wt.size(0);
  if (wt.size(0) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{0}; k < nx; k++) {
    wt[k] = std::exp(wt[k]);
  }
  if ((x.size(0) != wt.size(0)) && ((x.size(0) != 1) && (wt.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(x.size(0), wt.size(0), &g_emlrtECI);
  }
  if (x.size(0) == wt.size(0)) {
    b_x.set_size(x.size(0));
    nx = x.size(0);
    for (int k{0}; k < nx; k++) {
      b_x[k] = x[k] * wt[k];
    }
  } else {
    times(b_x, x, wt);
  }
  return (sigma + xbarWgtUnc) -
         blockedSummation(b_x, b_x.size(0)) / blockedSummation(wt, wt.size(0));
}

//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
} // namespace coder
static void pb_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Function values at the interval endpoints must differ in sign.";
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
static void qb_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Function values at interval endpoints must be finite and real.";
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
static void rb_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Second argument must be finite.";
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
static void sb_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Unable to reach a maximum likelihood solution.";
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
// Arguments    : coder::array<double, 1U> &in1
//                const coder::array<double, 1U> &in2
//                const coder::array<double, 1U> &in3
// Return Type  : void
//
static void times(coder::array<double, 1U> &in1,
                  const coder::array<double, 1U> &in2,
                  const coder::array<double, 1U> &in3)
{
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in3.size(0) == 1) {
    i = in2.size(0);
  } else {
    i = in3.size(0);
  }
  in1.set_size(i);
  stride_0_0 = (in2.size(0) != 1);
  stride_1_0 = (in3.size(0) != 1);
  if (in3.size(0) == 1) {
    loop_ub = in2.size(0);
  } else {
    loop_ub = in3.size(0);
  }
  for (i = 0; i < loop_ub; i++) {
    in1[i] = in2[i * stride_0_0] * in3[i * stride_1_0];
  }
}

//
// Arguments    : const ::coder::array<double, 1U> &x
//                double parmhat[2]
// Return Type  : void
//
namespace coder {
void evfit(const ::coder::array<double, 1U> &x, double parmhat[2])
{
  static rtBoundsCheckInfo fb_emlrtBCI{
      -1,                   // iFirst
      -1,                   // iLast
      16,                   // lineNo
      25,                   // colNo
      "",                   // aName
      "rangeWithCensoring", // fName
      "C:\\Program "
      "Files\\MATLAB\\toolbox\\stats\\stats\\+stats\\+coder\\+"
      "internal\\rangeWithCensoring.m", // pName
      0                                 // checkKind
  };
  static rtBoundsCheckInfo gb_emlrtBCI{
      -1,                   // iFirst
      -1,                   // iLast
      15,                   // lineNo
      14,                   // colNo
      "",                   // aName
      "rangeWithCensoring", // fName
      "C:\\Program "
      "Files\\MATLAB\\toolbox\\stats\\stats\\+stats\\+coder\\+"
      "internal\\rangeWithCensoring.m", // pName
      0                                 // checkKind
  };
  static rtBoundsCheckInfo hb_emlrtBCI{
      -1,                   // iFirst
      -1,                   // iLast
      13,                   // lineNo
      25,                   // colNo
      "",                   // aName
      "rangeWithCensoring", // fName
      "C:\\Program "
      "Files\\MATLAB\\toolbox\\stats\\stats\\+stats\\+coder\\+"
      "internal\\rangeWithCensoring.m", // pName
      0                                 // checkKind
  };
  static rtBoundsCheckInfo ib_emlrtBCI{
      -1,                   // iFirst
      -1,                   // iLast
      12,                   // lineNo
      14,                   // colNo
      "",                   // aName
      "rangeWithCensoring", // fName
      "C:\\Program "
      "Files\\MATLAB\\toolbox\\stats\\stats\\+stats\\+coder\\+"
      "internal\\rangeWithCensoring.m", // pName
      0                                 // checkKind
  };
  static rtRunTimeErrorInfo ad_emlrtRTEI{
      14,   // lineNo
      "log" // fName
  };
  static rtRunTimeErrorInfo bd_emlrtRTEI{
      137,    // lineNo
      "fzero" // fName
  };
  static rtRunTimeErrorInfo cd_emlrtRTEI{
      127,    // lineNo
      "fzero" // fName
  };
  static rtRunTimeErrorInfo dd_emlrtRTEI{
      209,    // lineNo
      "evfit" // fName
  };
  static rtRunTimeErrorInfo wc_emlrtRTEI{
      218,    // lineNo
      "evfit" // fName
  };
  static rtRunTimeErrorInfo xc_emlrtRTEI{
      227,    // lineNo
      "evfit" // fName
  };
  static rtRunTimeErrorInfo yc_emlrtRTEI{
      149,    // lineNo
      "fzero" // fName
  };
  array<double, 1U> absdiff;
  array<double, 1U> x0;
  double rangex;
  double tempMax;
  double tempMin;
  int exponent;
  int k;
  int kend;
  if (x.size(0) == 0) {
    i_rtErrorWithMessageID("X", gb_emlrtRTEI.fName, gb_emlrtRTEI.lineNo);
  }
  tempMin = rtInf;
  tempMax = rtMinusInf;
  k = x.size(0);
  for (kend = 0; kend < k; kend++) {
    if (kend + 1 > x.size(0)) {
      rtDynamicBoundsError(kend + 1, 1, x.size(0), &ib_emlrtBCI);
    }
    if (x[kend] > tempMax) {
      if (kend + 1 > x.size(0)) {
        rtDynamicBoundsError(kend + 1, 1, x.size(0), &hb_emlrtBCI);
      }
      tempMax = x[kend];
    }
    if (kend + 1 > x.size(0)) {
      rtDynamicBoundsError(kend + 1, 1, x.size(0), &gb_emlrtBCI);
    }
    if (x[kend] < tempMin) {
      if (kend + 1 > x.size(0)) {
        rtDynamicBoundsError(kend + 1, 1, x.size(0), &fb_emlrtBCI);
      }
      tempMin = x[kend];
    }
  }
  rangex = tempMax - tempMin;
  if (std::isinf(rangex) || std::isnan(rangex)) {
    parmhat[0] = rtNaN;
    parmhat[1] = rtNaN;
  } else if (rangex < 2.2250738585072014E-308) {
    parmhat[0] = x[0];
    parmhat[1] = 0.0;
  } else {
    double fb;
    double savefa;
    double savefb;
    double scale;
    double t;
    double upper;
    double wgtmeanUnc;
    x0.set_size(x.size(0));
    kend = x.size(0);
    for (k = 0; k < kend; k++) {
      x0[k] = (x[k] - tempMax) / rangex;
    }
    kend = x0.size(0);
    if (x0.size(0) == 1) {
      if ((!std::isinf(x0[0])) && (!std::isnan(x0[0]))) {
        tempMin = 0.0;
      } else {
        tempMin = rtNaN;
      }
    } else {
      tempMin =
          blockedSummation(x0, x0.size(0)) / static_cast<double>(x0.size(0));
      absdiff.set_size(x0.size(0));
      if (x0.size(0) > 2147483646) {
        check_forloop_overflow_error();
      }
      for (k = 0; k < kend; k++) {
        absdiff[k] = std::abs(x0[k] - tempMin);
      }
      tempMin = 0.0;
      scale = 3.3121686421112381E-170;
      kend = x0.size(0);
      for (k = 0; k < kend; k++) {
        if (absdiff[k] > scale) {
          t = scale / absdiff[k];
          tempMin = tempMin * t * t + 1.0;
          scale = absdiff[k];
        } else {
          t = absdiff[k] / scale;
          tempMin += t * t;
        }
      }
      tempMin = scale * std::sqrt(tempMin);
      tempMin /= std::sqrt(static_cast<double>(x0.size(0)) - 1.0);
    }
    scale = 2.4494897427831779 * tempMin / 3.1415926535897931;
    wgtmeanUnc =
        blockedSummation(x0, x0.size(0)) / static_cast<double>(x.size(0));
    if (lkeqn(scale, x0, wgtmeanUnc) > 0.0) {
      upper = scale;
      scale *= 0.5;
      while (lkeqn(scale, x0, wgtmeanUnc) > 0.0) {
        upper = scale;
        scale *= 0.5;
        if (scale < 2.2250738585072014E-308) {
          sb_rtErrorWithMessageID(dd_emlrtRTEI.fName, dd_emlrtRTEI.lineNo);
        }
      }
    } else {
      upper = 2.0 * scale;
      while (lkeqn(upper, x0, wgtmeanUnc) < 0.0) {
        scale = upper;
        upper *= 2.0;
        if (scale < 2.2250738585072014E-308) {
          sb_rtErrorWithMessageID(wc_emlrtRTEI.fName, wc_emlrtRTEI.lineNo);
        }
      }
    }
    if (std::isinf(scale) || std::isnan(scale) ||
        (std::isinf(upper) || std::isnan(upper))) {
      rb_rtErrorWithMessageID(cd_emlrtRTEI.fName, cd_emlrtRTEI.lineNo);
    }
    tempMin = lkeqn(scale, x0, wgtmeanUnc);
    fb = lkeqn(upper, x0, wgtmeanUnc);
    if (std::isinf(tempMin) || std::isnan(tempMin) ||
        (std::isinf(fb) || std::isnan(fb))) {
      qb_rtErrorWithMessageID(bd_emlrtRTEI.fName, bd_emlrtRTEI.lineNo);
    }
    savefa = tempMin;
    savefb = fb;
    if (tempMin == 0.0) {
      upper = scale;
      fb = tempMin;
    } else if (!(fb == 0.0)) {
      double c;
      double d;
      double e;
      double fc;
      boolean_T exitg1;
      if ((tempMin > 0.0) == (fb > 0.0)) {
        pb_rtErrorWithMessageID(yc_emlrtRTEI.fName, yc_emlrtRTEI.lineNo);
      }
      fc = fb;
      c = upper;
      e = 0.0;
      d = 0.0;
      exitg1 = false;
      while ((!exitg1) && ((fb != 0.0) && (scale != upper))) {
        double m;
        double toler;
        if ((fb > 0.0) == (fc > 0.0)) {
          c = scale;
          fc = tempMin;
          d = upper - scale;
          e = d;
        }
        if (std::abs(fc) < std::abs(fb)) {
          scale = upper;
          upper = c;
          c = scale;
          tempMin = fb;
          fb = fc;
          fc = tempMin;
        }
        m = 0.5 * (c - upper);
        toler = 2.0E-6 * std::fmax(std::abs(upper), 1.0);
        if ((std::abs(m) <= toler) || (fb == 0.0)) {
          exitg1 = true;
        } else {
          if ((std::abs(e) < toler) || (std::abs(tempMin) <= std::abs(fb))) {
            d = m;
            e = m;
          } else {
            double s;
            s = fb / tempMin;
            if (scale == c) {
              tempMin = 2.0 * m * s;
              t = 1.0 - s;
            } else {
              double r;
              t = tempMin / fc;
              r = fb / fc;
              tempMin =
                  s * (2.0 * m * t * (t - r) - (upper - scale) * (r - 1.0));
              t = (t - 1.0) * (r - 1.0) * (s - 1.0);
            }
            if (tempMin > 0.0) {
              t = -t;
            } else {
              tempMin = -tempMin;
            }
            if ((2.0 * tempMin < 3.0 * m * t - std::abs(toler * t)) &&
                (tempMin < std::abs(0.5 * e * t))) {
              e = d;
              d = tempMin / t;
            } else {
              d = m;
              e = m;
            }
          }
          scale = upper;
          tempMin = fb;
          if (std::abs(d) > toler) {
            upper += d;
          } else if (upper > c) {
            upper -= toler;
          } else {
            upper += toler;
          }
          fb = lkeqn(upper, x0, wgtmeanUnc);
        }
      }
      if (!(std::abs(fb) <= std::fmax(std::abs(savefa), std::abs(savefb)))) {
        sb_rtErrorWithMessageID(xc_emlrtRTEI.fName, xc_emlrtRTEI.lineNo);
      }
    }
    tempMin = std::abs(fb);
    if ((!std::isinf(tempMin)) && (!std::isnan(tempMin)) &&
        (!(tempMin <= 2.2250738585072014E-308))) {
      frexp(tempMin, &exponent);
    }
    kend = x0.size(0);
    for (k = 0; k < kend; k++) {
      x0[k] = x0[k] / upper;
    }
    kend = x0.size(0);
    for (k = 0; k < kend; k++) {
      x0[k] = std::exp(x0[k]);
    }
    tempMin = blockedSummation(x0, x0.size(0)) / static_cast<double>(x.size(0));
    if (tempMin < 0.0) {
      rtErrorWithMessageID("log", ad_emlrtRTEI.fName, ad_emlrtRTEI.lineNo);
    }
    tempMin = std::log(tempMin);
    parmhat[0] = rangex * (upper * tempMin) + tempMax;
    parmhat[1] = rangex * upper;
  }
}

} // namespace coder

//
// File trailer for evfit.cpp
//
// [EOF]
//
