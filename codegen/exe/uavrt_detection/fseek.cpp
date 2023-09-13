//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: fseek.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 13-Sep-2023 10:17:59
//

// Include Files
#include "fseek.h"
#include "fileManager.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include <cmath>
#include <cstdio>

// Function Definitions
//
// Arguments    : double fileID
//                double offset
// Return Type  : void
//
namespace coder {
void b_fseek(double fileID, double offset)
{
  int wherefrom;
  std::FILE *f;
  std::FILE *filestar;
  boolean_T a;
  wherefrom = SEEK_SET;
  if ((!std::isinf(offset)) && (!std::isnan(offset)) &&
      (std::floor(offset) == offset)) {
    f = internal::getfilestar(fileID, a);
    filestar = f;
    if (f == nullptr) {
      c_rtErrorWithMessageID(d_emlrtRTEI.fName, d_emlrtRTEI.lineNo);
    }
    if ((!(fileID != 0.0)) || (!(fileID != 1.0)) || (!(fileID != 2.0))) {
      filestar = nullptr;
    }
    if (!(filestar == nullptr)) {
      std::fseek(filestar, (long int)offset, wherefrom);
    }
  }
}

} // namespace coder

//
// File trailer for fseek.cpp
//
// [EOF]
//
