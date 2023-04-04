//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sqrt.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Apr-2023 11:47:02
//

// Include Files
#include "sqrt.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include <cmath>
#include <string.h>

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &x
// Return Type  : void
//
namespace coder {
void b_sqrt(::coder::array<double, 2U> &x)
{
  int nx;
  boolean_T p;
  p = false;
  nx = x.size(0) * x.size(1);
  for (int k{0}; k < nx; k++) {
    if (p || (x[k] < 0.0)) {
      p = true;
    }
  }
  if (p) {
    rtErrorWithMessageID("sqrt", ec_emlrtRTEI.fName, ec_emlrtRTEI.lineNo);
  }
  nx = x.size(0) * x.size(1);
  if (nx > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{0}; k < nx; k++) {
    x[k] = std::sqrt(x[k]);
  }
}

} // namespace coder

//
// File trailer for sqrt.cpp
//
// [EOF]
//
