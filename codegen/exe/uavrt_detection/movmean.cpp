//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: movmean.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "movmean.h"
#include "eml_int_forloop_overflow_check.h"
#include "movSumProdOrMean.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const array<double, 2U> &x
//                array<double, 2U> &y
// Return Type  : void
//
namespace coder {
void movmean(const array<double, 2U> &x, array<double, 2U> &y)
{
  array<double, 1U> xv;
  array<double, 1U> yv;
  int i;
  int len;
  int loop_ub;
  int outsize_idx_0;
  int stride;
  boolean_T overflow{false};
  i = x.size(1);
  y.set_size(x.size(0), x.size(1));
  len = x.size(0) * x.size(1);
  for (int k{0}; k < len; k++) {
    y[k] = 0.0;
  }
  stride = x.size(0);
  if (x.size(0) > 2147483646) {
    check_forloop_overflow_error();
  }
  if (x.size(0) - 1 >= 0) {
    outsize_idx_0 = x.size(1);
    loop_ub = x.size(1);
    overflow = (x.size(1) > 2147483646);
  }
  for (int j{0}; j < stride; j++) {
    xv.set_size(outsize_idx_0);
    for (int k{0}; k < loop_ub; k++) {
      xv[k] = 0.0;
    }
    if (overflow) {
      check_forloop_overflow_error();
    }
    for (int k{0}; k < i; k++) {
      xv[k] = x[j + k * stride];
    }
    vmovfun(xv, x.size(1), yv);
    len = yv.size(0);
    if (yv.size(0) > 2147483646) {
      check_forloop_overflow_error();
    }
    for (int k{0}; k < len; k++) {
      y[j + k * stride] = yv[k];
    }
  }
}

} // namespace coder

//
// File trailer for movmean.cpp
//
// [EOF]
//
