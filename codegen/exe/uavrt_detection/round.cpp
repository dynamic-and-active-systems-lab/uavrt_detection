//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: round.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 04-Feb-2025 09:56:05
//

// Include Files
#include "round.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : array<double, 1U> &x
// Return Type  : void
//
namespace coder {
void b_round(array<double, 1U> &x)
{
  int nx;
  nx = x.size(0);
  if (x.size(0) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{0}; k < nx; k++) {
    x[k] = std::round(x[k]);
  }
}

} // namespace coder

//
// File trailer for round.cpp
//
// [EOF]
//
