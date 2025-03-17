//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: evfit.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
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
#include <sstream>
#include <stdexcept>
#include <string>

// Function Declarations
namespace coder {
static double lkeqn(double sigma, const array<double, 1U> &x,
                    double xbarWgtUnc);

}
static void ub_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void vb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void wb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void xb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : double sigma
//                const array<double, 1U> &x
//                double xbarWgtUnc
// Return Type  : double
//
namespace coder {
static double lkeqn(double sigma, const array<double, 1U> &x, double xbarWgtUnc)
{
  array<double, 1U> b_x;
  array<double, 1U> wt;
  double v;
  int loop_ub;
  loop_ub = x.size(0);
  wt.set_size(x.size(0));
  for (int k{0}; k < loop_ub; k++) {
    wt[k] = x[k] / sigma;
  }
  if (wt.size(0) > 2147483646) {
    check_forloop_overflow_error();
  }
  b_x.set_size(x.size(0));
  for (int k{0}; k < loop_ub; k++) {
    v = std::exp(wt[k]);
    wt[k] = v;
    b_x[k] = x[k] * v;
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
static void ub_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
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
static void vb_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
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
static void wb_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
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
static void xb_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
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
// Arguments    : const array<double, 1U> &x
//                double parmhat[2]
// Return Type  : void
//
namespace coder {
void evfit(const array<double, 1U> &x, double parmhat[2])
{
  static rtBoundsCheckInfo ab_emlrtBCI{
      13,                  // lineNo
      "",                  // aName
      "rangeWithCensoring" // fName
  };
  static rtBoundsCheckInfo bb_emlrtBCI{
      16,                  // lineNo
      "",                  // aName
      "rangeWithCensoring" // fName
  };
  static rtBoundsCheckInfo cb_emlrtBCI{
      15,                  // lineNo
      "",                  // aName
      "rangeWithCensoring" // fName
  };
  static rtBoundsCheckInfo db_emlrtBCI{
      12,                  // lineNo
      "",                  // aName
      "rangeWithCensoring" // fName
  };
  static rtRunTimeErrorInfo rc_emlrtRTEI{
      218,    // lineNo
      "evfit" // fName
  };
  static rtRunTimeErrorInfo sc_emlrtRTEI{
      149,    // lineNo
      "fzero" // fName
  };
  static rtRunTimeErrorInfo tc_emlrtRTEI{
      14,   // lineNo
      "log" // fName
  };
  static rtRunTimeErrorInfo uc_emlrtRTEI{
      227,    // lineNo
      "evfit" // fName
  };
  static rtRunTimeErrorInfo vc_emlrtRTEI{
      137,    // lineNo
      "fzero" // fName
  };
  static rtRunTimeErrorInfo wc_emlrtRTEI{
      127,    // lineNo
      "fzero" // fName
  };
  static rtRunTimeErrorInfo xc_emlrtRTEI{
      209,    // lineNo
      "evfit" // fName
  };
  array<double, 1U> x0;
  double rangex;
  double tempMax;
  double tempMin;
  double wgtmeanUnc;
  int idx;
  int loop_ub;
  if (x.size(0) == 0) {
    g_rtErrorWithMessageID("X", u_emlrtRTEI.fName, u_emlrtRTEI.lineNo);
  }
  tempMin = rtInf;
  tempMax = rtMinusInf;
  loop_ub = x.size(0);
  for (idx = 0; idx < loop_ub; idx++) {
    if (idx + 1 > loop_ub) {
      rtDynamicBoundsError(idx + 1, 1, loop_ub, db_emlrtBCI);
    }
    wgtmeanUnc = x[idx];
    if (wgtmeanUnc > tempMax) {
      if (idx + 1 > loop_ub) {
        rtDynamicBoundsError(idx + 1, 1, loop_ub, ab_emlrtBCI);
      }
      tempMax = wgtmeanUnc;
    }
    if (idx + 1 > loop_ub) {
      rtDynamicBoundsError(idx + 1, 1, loop_ub, cb_emlrtBCI);
    }
    if (wgtmeanUnc < tempMin) {
      if (idx + 1 > loop_ub) {
        rtDynamicBoundsError(idx + 1, 1, loop_ub, bb_emlrtBCI);
      }
      tempMin = wgtmeanUnc;
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
    double sigmahat;
    double t;
    double upper;
    x0.set_size(x.size(0));
    for (idx = 0; idx < loop_ub; idx++) {
      x0[idx] = (x[idx] - tempMax) / rangex;
    }
    if (x0.size(0) == 1) {
      if ((!std::isinf(x0[0])) && (!std::isnan(x0[0]))) {
        sigmahat = 0.0;
      } else {
        sigmahat = rtNaN;
      }
    } else {
      tempMin =
          blockedSummation(x0, x0.size(0)) / static_cast<double>(x0.size(0));
      if (x0.size(0) > 2147483646) {
        check_forloop_overflow_error();
      }
      sigmahat = 0.0;
      scale = 3.3121686421112381E-170;
      for (idx = 0; idx < loop_ub; idx++) {
        wgtmeanUnc = std::abs(x0[idx] - tempMin);
        if (wgtmeanUnc > scale) {
          t = scale / wgtmeanUnc;
          sigmahat = sigmahat * t * t + 1.0;
          scale = wgtmeanUnc;
        } else {
          t = wgtmeanUnc / scale;
          sigmahat += t * t;
        }
      }
      sigmahat = scale * std::sqrt(sigmahat);
      sigmahat /= std::sqrt(static_cast<double>(x0.size(0)) - 1.0);
    }
    sigmahat = 2.4494897427831779 * sigmahat / 3.1415926535897931;
    wgtmeanUnc =
        blockedSummation(x0, x0.size(0)) / static_cast<double>(x.size(0));
    if (lkeqn(sigmahat, x0, wgtmeanUnc) > 0.0) {
      upper = sigmahat;
      sigmahat *= 0.5;
      while (lkeqn(sigmahat, x0, wgtmeanUnc) > 0.0) {
        upper = sigmahat;
        sigmahat *= 0.5;
        if (sigmahat < 2.2250738585072014E-308) {
          xb_rtErrorWithMessageID(xc_emlrtRTEI.fName, xc_emlrtRTEI.lineNo);
        }
      }
    } else {
      upper = 2.0 * sigmahat;
      while (lkeqn(upper, x0, wgtmeanUnc) < 0.0) {
        sigmahat = upper;
        upper *= 2.0;
        if (sigmahat < 2.2250738585072014E-308) {
          xb_rtErrorWithMessageID(rc_emlrtRTEI.fName, rc_emlrtRTEI.lineNo);
        }
      }
    }
    idx = 1;
    if (std::isinf(sigmahat) || std::isnan(sigmahat) ||
        (std::isinf(upper) || std::isnan(upper))) {
      wb_rtErrorWithMessageID(wc_emlrtRTEI.fName, wc_emlrtRTEI.lineNo);
    }
    tempMin = lkeqn(sigmahat, x0, wgtmeanUnc);
    fb = lkeqn(upper, x0, wgtmeanUnc);
    if (std::isinf(tempMin) || std::isnan(tempMin) ||
        (std::isinf(fb) || std::isnan(fb))) {
      vb_rtErrorWithMessageID(vc_emlrtRTEI.fName, vc_emlrtRTEI.lineNo);
    }
    savefa = tempMin;
    savefb = fb;
    if (tempMin == 0.0) {
      upper = sigmahat;
    } else if (!(fb == 0.0)) {
      double c;
      double d;
      double e;
      double fc;
      boolean_T exitg1;
      if ((tempMin > 0.0) == (fb > 0.0)) {
        ub_rtErrorWithMessageID(sc_emlrtRTEI.fName, sc_emlrtRTEI.lineNo);
      }
      fc = fb;
      c = upper;
      e = 0.0;
      d = 0.0;
      exitg1 = false;
      while ((!exitg1) && ((fb != 0.0) && (sigmahat != upper))) {
        double m;
        double toler;
        if ((fb > 0.0) == (fc > 0.0)) {
          c = sigmahat;
          fc = tempMin;
          d = upper - sigmahat;
          e = d;
        }
        if (std::abs(fc) < std::abs(fb)) {
          sigmahat = upper;
          upper = c;
          c = sigmahat;
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
            if (sigmahat == c) {
              tempMin = 2.0 * m * s;
              scale = 1.0 - s;
            } else {
              scale = tempMin / fc;
              t = fb / fc;
              tempMin = s * (2.0 * m * scale * (scale - t) -
                             (upper - sigmahat) * (t - 1.0));
              scale = (scale - 1.0) * (t - 1.0) * (s - 1.0);
            }
            if (tempMin > 0.0) {
              scale = -scale;
            } else {
              tempMin = -tempMin;
            }
            if ((2.0 * tempMin < 3.0 * m * scale - std::abs(toler * scale)) &&
                (tempMin < std::abs(0.5 * e * scale))) {
              e = d;
              d = tempMin / scale;
            } else {
              d = m;
              e = m;
            }
          }
          sigmahat = upper;
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
        idx = -5;
      }
    }
    if (idx < 0) {
      xb_rtErrorWithMessageID(uc_emlrtRTEI.fName, uc_emlrtRTEI.lineNo);
    }
    for (idx = 0; idx < loop_ub; idx++) {
      x0[idx] = x0[idx] / upper;
    }
    for (idx = 0; idx < loop_ub; idx++) {
      x0[idx] = std::exp(x0[idx]);
    }
    tempMin = blockedSummation(x0, x0.size(0)) / static_cast<double>(x.size(0));
    if (tempMin < 0.0) {
      n_rtErrorWithMessageID("log", tc_emlrtRTEI.fName, tc_emlrtRTEI.lineNo);
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
