//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ifWhileCond.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 17-Dec-2022 13:40:17
//

// Include Files
#include "ifWhileCond.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <string.h>

// Function Definitions
//
// Arguments    : const ::coder::array<boolean_T, 1U> &x
// Return Type  : boolean_T
//
namespace coder {
namespace internal {
boolean_T ifWhileCond(const ::coder::array<boolean_T, 1U> &x)
{
  boolean_T y;
  y = (x.size(0) != 0);
  if (y) {
    int k;
    boolean_T exitg1;
    if (x.size(0) > 2147483646) {
      check_forloop_overflow_error();
    }
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k <= x.size(0) - 1)) {
      if (!x[k]) {
        y = false;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }
  return y;
}

} // namespace internal
} // namespace coder

//
// File trailer for ifWhileCond.cpp
//
// [EOF]
//
