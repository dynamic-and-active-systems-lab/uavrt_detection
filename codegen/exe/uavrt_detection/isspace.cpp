//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: isspace.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 04-Feb-2025 09:56:05
//

// Include Files
#include "isspace.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"

// Function Definitions
//
// Arguments    : char x
// Return Type  : boolean_T
//
namespace coder {
boolean_T b_isspace(char x)
{
  if (static_cast<unsigned char>(x) > 127) {
    vc_rtErrorWithMessageID(i_emlrtRTEI.fName, i_emlrtRTEI.lineNo);
  }
  return bv[static_cast<int>(static_cast<unsigned char>(x) & 127U)];
}

} // namespace coder

//
// File trailer for isspace.cpp
//
// [EOF]
//
