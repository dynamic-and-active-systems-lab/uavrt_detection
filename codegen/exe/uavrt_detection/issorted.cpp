//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: issorted.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 04-Feb-2025 09:56:05
//

// Include Files
#include "issorted.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const array<double, 2U> &x
// Return Type  : boolean_T
//
namespace coder {
boolean_T issorted(const array<double, 2U> &x)
{
  boolean_T y;
  y = true;
  if ((x.size(1) != 0) && (x.size(1) != 1)) {
    int k;
    boolean_T exitg1;
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k <= x.size(1) - 2)) {
      double v_idx_1;
      v_idx_1 = x[k + 1];
      if ((x[k] <= v_idx_1) || std::isnan(v_idx_1)) {
        k++;
      } else {
        y = false;
        exitg1 = true;
      }
    }
  }
  return y;
}

} // namespace coder

//
// File trailer for issorted.cpp
//
// [EOF]
//
