//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: allOrAny.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 27-Mar-2023 15:47:21
//

// Include Files
#include "allOrAny.h"
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
boolean_T allOrAny_anonFcn1(const ::coder::array<boolean_T, 1U> &x)
{
  int ix;
  boolean_T exitg1;
  boolean_T varargout_1;
  varargout_1 = false;
  if (x.size(0) > 2147483646) {
    check_forloop_overflow_error();
  }
  ix = 1;
  exitg1 = false;
  while ((!exitg1) && (ix <= x.size(0))) {
    if (x[ix - 1]) {
      varargout_1 = true;
      exitg1 = true;
    } else {
      ix++;
    }
  }
  return varargout_1;
}

} // namespace internal
} // namespace coder

//
// File trailer for allOrAny.cpp
//
// [EOF]
//
