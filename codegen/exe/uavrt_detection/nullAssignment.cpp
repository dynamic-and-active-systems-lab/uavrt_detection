//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: nullAssignment.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 09-Mar-2023 11:19:16
//

// Include Files
#include "nullAssignment.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include <string.h>

// Function Definitions
//
// Arguments    : ::coder::array<char, 2U> &x
//                int idx
// Return Type  : void
//
namespace coder {
namespace internal {
void nullAssignment(::coder::array<char, 2U> &x, int idx)
{
  static rtRunTimeErrorInfo uc_emlrtRTEI{
      85,               // lineNo
      "validate_inputs" // fName
  };
  int nxin;
  int nxout;
  if (idx > x.size(1)) {
    jc_rtErrorWithMessageID(uc_emlrtRTEI.fName, uc_emlrtRTEI.lineNo);
  }
  nxin = x.size(1);
  nxout = x.size(1) - 1;
  for (int k{idx}; k <= nxout; k++) {
    x[k - 1] = x[k];
  }
  if (nxout < 1) {
    nxout = 0;
  } else {
    nxout = nxin - 1;
  }
  x.set_size(x.size(0), nxout);
}

} // namespace internal
} // namespace coder

//
// File trailer for nullAssignment.cpp
//
// [EOF]
//
