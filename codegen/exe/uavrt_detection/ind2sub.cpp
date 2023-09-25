//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ind2sub.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 24-Sep-2023 17:58:12
//

// Include Files
#include "ind2sub.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"

// Variable Definitions
static rtRunTimeErrorInfo
    kc_emlrtRTEI{
        21,        // lineNo
        15,        // colNo
        "ind2sub", // fName
        "/Applications/MATLAB_R2023a.app/toolbox/eml/eml/+coder/+internal/"
        "ind2sub.m" // pName
    };

// Function Definitions
//
// Arguments    : const double siz[2]
//                double ndx
//                int &varargout_2
// Return Type  : int
//
namespace coder {
namespace internal {
int ind2sub(const double siz[2], double ndx, int &varargout_2)
{
  int vk;
  if (static_cast<int>(ndx) >
      static_cast<int>(siz[0]) * static_cast<int>(siz[1])) {
    cc_rtErrorWithMessageID(kc_emlrtRTEI.fName, kc_emlrtRTEI.lineNo);
  }
  vk = div_s32(static_cast<int>(ndx) - 1, static_cast<int>(siz[0]));
  varargout_2 = vk + 1;
  return static_cast<int>(ndx) - vk * static_cast<int>(siz[0]);
}

//
// Arguments    : const double siz[2]
//                int ndx
//                int &varargout_2
// Return Type  : int
//
int ind2sub(const double siz[2], int ndx, int &varargout_2)
{
  int vk;
  if (ndx > static_cast<int>(siz[0]) * static_cast<int>(siz[1])) {
    cc_rtErrorWithMessageID(kc_emlrtRTEI.fName, kc_emlrtRTEI.lineNo);
  }
  vk = div_s32(ndx - 1, static_cast<int>(siz[0]));
  varargout_2 = vk + 1;
  return ndx - vk * static_cast<int>(siz[0]);
}

} // namespace internal
} // namespace coder

//
// File trailer for ind2sub.cpp
//
// [EOF]
//
