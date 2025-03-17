//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: exp.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "exp.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : array<creal_T, 1U> &x
// Return Type  : void
//
namespace coder {
void b_exp(array<creal_T, 1U> &x)
{
  int nx;
  nx = x.size(0);
  if (x.size(0) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{0}; k < nx; k++) {
    double im;
    double r;
    r = x[k].re;
    im = x[k].im;
    if (r == 0.0) {
      x[k].re = std::cos(im);
      x[k].im = std::sin(im);
    } else if (im == 0.0) {
      x[k].re = std::exp(r);
      x[k].im = 0.0;
    } else if (std::isinf(im) && std::isinf(r) && (r < 0.0)) {
      x[k].re = 0.0;
      x[k].im = 0.0;
    } else {
      r = std::exp(r / 2.0);
      x[k].re = r * (r * std::cos(im));
      x[k].im = r * (r * std::sin(im));
    }
  }
}

} // namespace coder

//
// File trailer for exp.cpp
//
// [EOF]
//
