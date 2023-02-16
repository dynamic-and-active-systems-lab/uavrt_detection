//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: lower.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 16-Feb-2023 15:25:26
//

// Include Files
#include "lower.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include <string.h>

// Function Definitions
//
// Arguments    : const ::coder::array<char, 2U> &x
//                ::coder::array<char, 2U> &y
// Return Type  : void
//
namespace coder {
void lower(const ::coder::array<char, 2U> &x, ::coder::array<char, 2U> &y)
{
  int ns;
  boolean_T p;
  ns = x.size(1);
  p = true;
  if (x.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{0}; k < ns; k++) {
    p = (p && (static_cast<unsigned char>(x[k]) <= 127));
  }
  if (!p) {
    rc_rtErrorWithMessageID(i_emlrtRTEI.fName, i_emlrtRTEI.lineNo);
  }
  y.set_size(1, x.size(1));
  ns = x.size(1);
  for (int k{0}; k < ns; k++) {
    y[k] = cv[static_cast<unsigned char>(x[k]) & 127];
  }
}

} // namespace coder

//
// File trailer for lower.cpp
//
// [EOF]
//
