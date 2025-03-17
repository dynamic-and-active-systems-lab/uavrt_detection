//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: abs.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "abs.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const creal_T x
// Return Type  : double
//
namespace coder {
double b_abs(const creal_T x)
{
  double b;
  double y;
  y = std::abs(x.re);
  b = std::abs(x.im);
  if (y < b) {
    y /= b;
    y = b * std::sqrt(y * y + 1.0);
  } else if (y > b) {
    b /= y;
    y *= std::sqrt(b * b + 1.0);
  } else if (std::isnan(b)) {
    y = rtNaN;
  } else {
    y *= 1.4142135623730951;
  }
  return y;
}

//
// Arguments    : const array<creal_T, 2U> &x
//                array<double, 2U> &y
// Return Type  : void
//
void b_abs(const array<creal_T, 2U> &x, array<double, 2U> &y)
{
  int nx_tmp;
  nx_tmp = x.size(0) * x.size(1);
  y.set_size(x.size(0), x.size(1));
  if (nx_tmp > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{0}; k < nx_tmp; k++) {
    double a;
    double b;
    a = std::abs(x[k].re);
    b = std::abs(x[k].im);
    if (a < b) {
      a /= b;
      y[k] = b * std::sqrt(a * a + 1.0);
    } else if (a > b) {
      b /= a;
      y[k] = a * std::sqrt(b * b + 1.0);
    } else if (std::isnan(b)) {
      y[k] = rtNaN;
    } else {
      y[k] = a * 1.4142135623730951;
    }
  }
}

//
// Arguments    : const array<double, 1U> &x
//                array<double, 1U> &y
// Return Type  : void
//
void b_abs(const array<double, 1U> &x, array<double, 1U> &y)
{
  int nx_tmp;
  nx_tmp = x.size(0);
  y.set_size(x.size(0));
  if (x.size(0) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{0}; k < nx_tmp; k++) {
    y[k] = std::abs(x[k]);
  }
}

} // namespace coder

//
// File trailer for abs.cpp
//
// [EOF]
//
