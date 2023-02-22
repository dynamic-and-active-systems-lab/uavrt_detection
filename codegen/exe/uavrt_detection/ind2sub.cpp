//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ind2sub.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 21-Feb-2023 17:21:25
//

// Include Files
#include "ind2sub.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include <string.h>

// Variable Definitions
static rtRunTimeErrorInfo mc_emlrtRTEI{
    40,                  // lineNo
    "ind2sub_indexClass" // fName
};

// Function Definitions
//
// Arguments    : const double siz[2]
//                double ndx
//                int *varargout_1
//                int *varargout_2
// Return Type  : void
//
namespace coder {
void ind2sub_indexClass(const double siz[2], double ndx, int *varargout_1,
                        int *varargout_2)
{
  int vk;
  if (static_cast<int>(ndx) >
      static_cast<int>(siz[0]) * static_cast<int>(siz[1])) {
    ac_rtErrorWithMessageID(mc_emlrtRTEI.fName, mc_emlrtRTEI.lineNo);
  }
  vk = div_s32(static_cast<int>(ndx) - 1, static_cast<int>(siz[0]));
  *varargout_2 = vk + 1;
  *varargout_1 = static_cast<int>(ndx) - vk * static_cast<int>(siz[0]);
}

//
// Arguments    : const double siz[2]
//                int ndx
//                int *varargout_1
//                int *varargout_2
// Return Type  : void
//
void ind2sub_indexClass(const double siz[2], int ndx, int *varargout_1,
                        int *varargout_2)
{
  int vk;
  if (ndx > static_cast<int>(siz[0]) * static_cast<int>(siz[1])) {
    ac_rtErrorWithMessageID(mc_emlrtRTEI.fName, mc_emlrtRTEI.lineNo);
  }
  vk = div_s32(ndx - 1, static_cast<int>(siz[0]));
  *varargout_2 = vk + 1;
  *varargout_1 = ndx - vk * static_cast<int>(siz[0]);
}

} // namespace coder

//
// File trailer for ind2sub.cpp
//
// [EOF]
//
