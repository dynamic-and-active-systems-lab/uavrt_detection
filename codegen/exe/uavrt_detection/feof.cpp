//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: feof.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 17-Feb-2023 12:17:58
//

// Include Files
#include "feof.h"
#include "fileManager.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include <stdio.h>
#include <string.h>

// Function Definitions
//
// Arguments    : double fileID
// Return Type  : double
//
namespace coder {
double b_feof(double fileID)
{
  FILE *b_NULL;
  FILE *filestar;
  double st;
  b_NULL = NULL;
  filestar = fileManager(fileID);
  if (filestar == b_NULL) {
    e_rtErrorWithMessageID(d_emlrtRTEI.fName, d_emlrtRTEI.lineNo);
  } else {
    int b_st;
    b_st = feof(filestar);
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
