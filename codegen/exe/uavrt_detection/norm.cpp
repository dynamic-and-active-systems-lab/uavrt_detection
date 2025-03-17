//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: norm.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "norm.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const array<creal_T, 2U> &x
// Return Type  : double
//
namespace coder {
double b_norm(const array<creal_T, 2U> &x)
{
  double y;
  if (x.size(0) == 0) {
    y = 0.0;
  } else {
    y = 0.0;
    if (x.size(0) == 1) {
      double absxk;
      double scale;
      scale = std::abs(x[0].re);
      absxk = std::abs(x[0].im);
      if (scale < absxk) {
        scale /= absxk;
        y = absxk * std::sqrt(scale * scale + 1.0);
      } else if (scale > absxk) {
        absxk /= scale;
        y = scale * std::sqrt(absxk * absxk + 1.0);
      } else if (std::isnan(absxk)) {
        y = rtNaN;
      } else {
        y = scale * 1.4142135623730951;
      }
    } else {
      double scale;
      int kend;
      scale = 3.3121686421112381E-170;
      kend = x.size(0);
      if (x.size(0) > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int k{0}; k < kend; k++) {
        double absxk;
        double t;
        absxk = std::abs(x[k].re);
        if (absxk > scale) {
          t = scale / absxk;
          y = y * t * t + 1.0;
          scale = absxk;
        } else {
          t = absxk / scale;
          y += t * t;
        }
        absxk = std::abs(x[k].im);
        if (absxk > scale) {
          t = scale / absxk;
          y = y * t * t + 1.0;
          scale = absxk;
        } else {
          t = absxk / scale;
          y += t * t;
        }
      }
      y = scale * std::sqrt(y);
    }
  }
  return y;
}

} // namespace coder

//
// File trailer for norm.cpp
//
// [EOF]
//
