//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: fzero.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 14:31:55
//

// Include Files
#include "fzero.h"
#include "anonymous_function.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_internal_types.h"
#include "uavrt_detection_types.h"
#include "omp.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string.h>
#include <string>

// Function Declarations
static void fb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void fb_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Initial function value must be finite and real.";
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
// Arguments    : const b_anonymous_function FunFcn
// Return Type  : double
//
namespace coder {
double fzero(const b_anonymous_function FunFcn)
{
  static rtRunTimeErrorInfo kb_emlrtRTEI{
      83,     // lineNo
      "fzero" // fName
  };
  double b;
  double fx;
  fx = (1.0 - std::exp(-std::exp((-0.0 - FunFcn.workspace.mu) /
                                 FunFcn.workspace.sigma))) -
       FunFcn.workspace.pf;
  if (fx == 0.0) {
    b = 0.0;
  } else {
    double a;
    double dx;
    double fb;
    int exitg2;
    if (std::isinf(fx) || std::isnan(fx)) {
      fb_rtErrorWithMessageID(kb_emlrtRTEI.fName, kb_emlrtRTEI.lineNo);
    }
    dx = 0.02;
    a = 0.0;
    b = 0.0;
    fb = fx;
    do {
      exitg2 = 0;
      if ((fx > 0.0) == (fb > 0.0)) {
        dx *= 1.4142135623730951;
        a = 0.0 - dx;
        fx = (1.0 - std::exp(-std::exp((-(0.0 - dx) - FunFcn.workspace.mu) /
                                       FunFcn.workspace.sigma))) -
             FunFcn.workspace.pf;
        if (std::isinf(fx) || std::isnan(fx)) {
          b = rtNaN;
          exitg2 = 1;
        } else if (std::isinf(0.0 - dx)) {
          b = rtNaN;
          exitg2 = 1;
        } else if ((fx > 0.0) != (fb > 0.0)) {
          exitg2 = 2;
        } else {
          b = dx;
          fb = (1.0 - std::exp(-std::exp((-dx - FunFcn.workspace.mu) /
                                         FunFcn.workspace.sigma))) -
               FunFcn.workspace.pf;
          if (std::isinf(fb) || std::isnan(fb)) {
            b = rtNaN;
            exitg2 = 1;
          } else if (std::isinf(dx)) {
            b = rtNaN;
            exitg2 = 1;
          }
        }
      } else {
        exitg2 = 2;
      }
    } while (exitg2 == 0);
    if (exitg2 != 1) {
      double c;
      double d;
      double e;
      double fc;
      boolean_T exitg1;
      fc = fb;
      c = b;
      e = 0.0;
      d = 0.0;
      exitg1 = false;
      while ((!exitg1) && ((fb != 0.0) && (a != b))) {
        double m;
        double toler;
        if ((fb > 0.0) == (fc > 0.0)) {
          c = a;
          fc = fx;
          d = b - a;
          e = d;
        }
        if (std::abs(fc) < std::abs(fb)) {
          a = b;
          b = c;
          c = a;
          fx = fb;
          fb = fc;
          fc = fx;
        }
        m = 0.5 * (c - b);
        toler = 4.4408920985006262E-16 * std::abs(b);
        if ((std::abs(m) <= toler) || (fb == 0.0)) {
          exitg1 = true;
        } else {
          if ((std::abs(e) < toler) || (std::abs(fx) <= std::abs(fb))) {
            d = m;
            e = m;
          } else {
            double s;
            s = fb / fx;
            if (a == c) {
              dx = 2.0 * m * s;
              fx = 1.0 - s;
            } else {
              double r;
              fx /= fc;
              r = fb / fc;
              dx = s * (2.0 * m * fx * (fx - r) - (b - a) * (r - 1.0));
              fx = (fx - 1.0) * (r - 1.0) * (s - 1.0);
            }
            if (dx > 0.0) {
              fx = -fx;
            } else {
              dx = -dx;
            }
            if ((2.0 * dx < 3.0 * m * fx - std::abs(toler * fx)) &&
                (dx < std::abs(0.5 * e * fx))) {
              e = d;
              d = dx / fx;
            } else {
              d = m;
              e = m;
            }
          }
          a = b;
          fx = fb;
          if (std::abs(d) > toler) {
            b += d;
          } else if (b > c) {
            b -= toler;
          } else {
            b += toler;
          }
          fb = (1.0 - std::exp(-std::exp((-b - FunFcn.workspace.mu) /
                                         FunFcn.workspace.sigma))) -
               FunFcn.workspace.pf;
        }
      }
    }
  }
  return b;
}

} // namespace coder

//
// File trailer for fzero.cpp
//
// [EOF]
//
