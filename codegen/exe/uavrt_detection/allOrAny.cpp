//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: allOrAny.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 01-Dec-2022 10:02:54
//

// Include Files
#include "allOrAny.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <string.h>

// Function Definitions
//
// Arguments    : const ::coder::array<bool, 1U> &x
// Return Type  : bool
//
namespace coder {
namespace internal {
bool allOrAny_anonFcn1(const ::coder::array<bool, 1U> &x)
{
  int ix;
  bool exitg1;
  bool varargout_1;
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
