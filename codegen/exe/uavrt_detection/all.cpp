//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: all.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "all.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const array<boolean_T, 2U> &x
//                array<boolean_T, 1U> &y
// Return Type  : void
//
namespace coder {
void all(const array<boolean_T, 2U> &x, array<boolean_T, 1U> &y)
{
  int i1;
  int i2;
  int loop_ub;
  loop_ub = x.size(0);
  y.set_size(x.size(0));
  for (i2 = 0; i2 < loop_ub; i2++) {
    y[i2] = true;
  }
  i2 = (x.size(1) - 1) * x.size(0);
  i1 = 1;
  if (x.size(0) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int j{0}; j < loop_ub; j++) {
    int i1_tmp;
    int ix;
    boolean_T exitg1;
    boolean_T overflow;
    i1_tmp = i1;
    i1++;
    i2++;
    if ((loop_ub == 0) || (i1_tmp > i2)) {
      overflow = false;
    } else {
      overflow = (i2 > MAX_int32_T - loop_ub);
    }
    if (loop_ub == 0) {
      cc_rtErrorWithMessageID(ac_emlrtRTEI.fName, ac_emlrtRTEI.lineNo);
    }
    if (overflow) {
      check_forloop_overflow_error();
    }
    ix = i1_tmp;
    exitg1 = false;
    while ((!exitg1) && (ix <= i2)) {
      if (!x[ix - 1]) {
        y[i1_tmp - 1] = false;
        exitg1 = true;
      } else {
        ix += loop_ub;
      }
    }
  }
}

//
// Arguments    : const array<boolean_T, 2U> &x
// Return Type  : boolean_T
//
boolean_T b_all(const array<boolean_T, 2U> &x)
{
  int ix;
  boolean_T exitg1;
  boolean_T y;
  y = true;
  if (x.size(0) > 2147483646) {
    check_forloop_overflow_error();
  }
  ix = 1;
  exitg1 = false;
  while ((!exitg1) && (ix <= x.size(0))) {
    if (!x[ix - 1]) {
      y = false;
      exitg1 = true;
    } else {
      ix++;
    }
  }
  return y;
}

} // namespace coder

//
// File trailer for all.cpp
//
// [EOF]
//
