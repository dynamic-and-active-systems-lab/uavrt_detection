//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: feof.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "feof.h"
#include "fileManager.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include <cstdio>

// Function Definitions
//
// Arguments    : double fileID
// Return Type  : double
//
namespace coder {
double b_feof(double fileID)
{
  std::FILE *f;
  double st;
  boolean_T a;
  f = internal::getfilestar(fileID, a);
  if (f == nullptr) {
    c_rtErrorWithMessageID(c_emlrtRTEI.fName, c_emlrtRTEI.lineNo);
  } else {
    int b_st;
    b_st = std::feof(f);
    st = ((int)b_st != 0);
  }
  return st;
}

} // namespace coder

//
// File trailer for feof.cpp
//
// [EOF]
//
