//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ind2sub.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "ind2sub.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"

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
  int varargout_1;
  if ((static_cast<int>(ndx) < 1) ||
      (static_cast<int>(ndx) >
       static_cast<int>(siz[0]) * static_cast<int>(siz[1]))) {
    gc_rtErrorWithMessageID(gc_emlrtRTEI.fName, gc_emlrtRTEI.lineNo);
  }
  varargout_1 = div_s32(static_cast<int>(ndx) - 1, static_cast<int>(siz[0]));
  varargout_2 = varargout_1 + 1;
  return static_cast<int>(ndx) - varargout_1 * static_cast<int>(siz[0]);
}

} // namespace internal
} // namespace coder

//
// File trailer for ind2sub.cpp
//
// [EOF]
//
