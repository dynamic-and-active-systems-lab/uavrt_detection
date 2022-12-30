//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: insertionsort.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 30-Dec-2022 11:43:16
//

// Include Files
#include "insertionsort.h"
#include "anonymous_function.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_internal_types.h"
#include "coder_array.h"
#include <string.h>

// Function Definitions
//
// Arguments    : ::coder::array<int, 1U> &x
//                int xstart
//                int xend
//                const c_anonymous_function *cmp
// Return Type  : void
//
namespace coder {
namespace internal {
void insertionsort(::coder::array<int, 1U> &x, int xstart, int xend,
                   const c_anonymous_function *cmp)
{
  int a;
  a = xstart + 1;
  if ((xstart + 1 <= xend) && (xend > 2147483646)) {
    check_forloop_overflow_error();
  }
  for (int k{a}; k <= xend; k++) {
    int idx;
    int xc;
    xc = x[k - 1];
    idx = k - 1;
    while ((idx >= xstart) &&
           (cmp->workspace.x[xc - 1] < cmp->workspace.x[x[idx - 1] - 1])) {
      x[idx] = x[idx - 1];
      idx--;
    }
    x[idx] = xc;
  }
}

//
// Arguments    : ::coder::array<int, 1U> &x
//                int xstart
//                int xend
//                const anonymous_function *cmp
// Return Type  : void
//
void insertionsort(::coder::array<int, 1U> &x, int xstart, int xend,
                   const anonymous_function *cmp)
{
  int a;
  a = xstart + 1;
  if ((xstart + 1 <= xend) && (xend > 2147483646)) {
    check_forloop_overflow_error();
  }
  for (int k{a}; k <= xend; k++) {
    int idx;
    int xc;
    boolean_T exitg1;
    xc = x[k - 1] - 1;
    idx = k - 2;
    exitg1 = false;
    while ((!exitg1) && (idx + 1 >= xstart)) {
      boolean_T varargout_1;
      if (cmp->workspace.a[xc] < cmp->workspace.a[x[idx] - 1]) {
        varargout_1 = true;
      } else if (cmp->workspace.a[xc] == cmp->workspace.a[x[idx] - 1]) {
        varargout_1 = (cmp->workspace.b[xc] < cmp->workspace.b[x[idx] - 1]);
      } else {
        varargout_1 = false;
      }
      if (varargout_1) {
        x[idx + 1] = x[idx];
        idx--;
      } else {
        exitg1 = true;
      }
    }
    x[idx + 1] = xc + 1;
  }
}

} // namespace internal
} // namespace coder

//
// File trailer for insertionsort.cpp
//
// [EOF]
//
