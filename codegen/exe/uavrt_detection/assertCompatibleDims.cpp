//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: assertCompatibleDims.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 13-Sep-2023 10:17:59
//

// Include Files
#include "assertCompatibleDims.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &x
//                const ::coder::array<double, 2U> &y
// Return Type  : void
//
namespace coder {
namespace internal {
void assertCompatibleDims(const ::coder::array<double, 2U> &x,
                          const ::coder::array<double, 2U> &y)
{
  if (((x.size(0) != 1) && (y.size(0) != 1) && (x.size(0) != y.size(0))) ||
      ((x.size(1) != 1) && (y.size(1) != 1) && (x.size(1) != y.size(1)))) {
    y_rtErrorWithMessageID(kb_emlrtRTEI.fName, kb_emlrtRTEI.lineNo);
  }
}

} // namespace internal
} // namespace coder

//
// File trailer for assertCompatibleDims.cpp
//
// [EOF]
//
