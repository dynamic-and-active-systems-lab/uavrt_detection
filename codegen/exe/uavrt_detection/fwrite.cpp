//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: fwrite.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 14:31:55
//

// Include Files
#include "fwrite.h"
#include "fileManager.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include <cstddef>
#include <stdio.h>
#include <string.h>

// Function Definitions
//
// Arguments    : double fileID
//                const float x_data[]
//                int x_size
// Return Type  : double
//
namespace coder {
double b_fwrite(double fileID, const float x_data[], int x_size)
{
  static rtRunTimeErrorInfo kb_emlrtRTEI{
      158,          // lineNo
      "getFileStar" // fName
  };
  static rtRunTimeErrorInfo lb_emlrtRTEI{
      33,      // lineNo
      "fwrite" // fName
  };
  FILE *filestar;
  double count;
  boolean_T autoflush;
  if (!(fileID != 0.0)) {
    h_rtErrorWithMessageID(lb_emlrtRTEI.fName, lb_emlrtRTEI.lineNo);
  }
  getfilestar(fileID, &filestar, &autoflush);
  if (filestar == NULL) {
    d_rtErrorWithMessageID(kb_emlrtRTEI.fName, kb_emlrtRTEI.lineNo);
  }
  if (!(fileID != 0.0)) {
    filestar = NULL;
  }
  if ((filestar == NULL) || (x_size == 0)) {
    count = 0.0;
  } else {
    size_t bytesOutSizet;
    bytesOutSizet = fwrite(&x_data[0], sizeof(float), (size_t)1, filestar);
    count = (double)bytesOutSizet;
    if (((double)bytesOutSizet > 0.0) && autoflush) {
      int status;
      status = fflush(filestar);
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
