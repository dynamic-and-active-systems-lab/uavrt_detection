//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: assertValidSizeArg.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 17-Feb-2023 12:17:58
//

// Include Files
#include "assertValidSizeArg.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include <cmath>
#include <string.h>

// Function Definitions
//
// Arguments    : double varargin_2
// Return Type  : void
//
namespace coder {
namespace internal {
void assertValidSizeArg(double varargin_2)
{
  double b_varargin_2;
  if ((varargin_2 != std::floor(varargin_2)) || std::isinf(varargin_2) ||
      (varargin_2 < -2.147483648E+9) || (varargin_2 > 2.147483647E+9)) {
    c_rtErrorWithMessageID(MIN_int32_T, ib_emlrtRTEI.fName,
                           ib_emlrtRTEI.lineNo);
  }
  if (varargin_2 <= 0.0) {
    b_varargin_2 = 0.0;
  } else {
    b_varargin_2 = varargin_2;
  }
  if (!(b_varargin_2 <= 2.147483647E+9)) {
    n_rtErrorWithMessageID(n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
  }
}

} // namespace internal
} // namespace coder

//
// File trailer for assertValidSizeArg.cpp
//
// [EOF]
//
