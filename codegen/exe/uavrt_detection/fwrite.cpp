//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: fwrite.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "fwrite.h"
#include "fileManager.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdio>

// Function Definitions
//
// Arguments    : double fileID
//                const array<float, 1U> &x
// Return Type  : double
//
namespace coder {
double b_fwrite(double fileID, const array<float, 1U> &x)
{
  static rtRunTimeErrorInfo rc_emlrtRTEI{
      163,          // lineNo
      "getFileStar" // fName
  };
  static rtRunTimeErrorInfo sc_emlrtRTEI{
      33,      // lineNo
      "fwrite" // fName
  };
  std::FILE *f;
  double count;
  boolean_T autoflush;
  if (!(fileID != 0.0)) {
    e_rtErrorWithMessageID(sc_emlrtRTEI.fName, sc_emlrtRTEI.lineNo);
  }
  f = internal::getfilestar(fileID, autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(rc_emlrtRTEI.fName, rc_emlrtRTEI.lineNo);
  }
  if ((f == nullptr) || (x.size(0) == 0)) {
    count = 0.0;
  } else {
    size_t bytesOutSizet;
    bytesOutSizet =
        std::fwrite(&(x.data())[0], sizeof(float), (size_t)x.size(0), f);
    count = (double)bytesOutSizet;
    if (((double)bytesOutSizet > 0.0) && autoflush) {
      int status;
      status = std::fflush(f);
      if (status != 0) {
        count = 0.0;
      }
    }
  }
  return count;
}

} // namespace coder

//
// File trailer for fwrite.cpp
//
// [EOF]
//
