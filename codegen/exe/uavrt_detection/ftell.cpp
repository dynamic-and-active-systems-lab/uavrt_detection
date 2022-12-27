//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ftell.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 27-Dec-2022 15:25:33
//

// Include Files
#include "ftell.h"
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
double b_ftell(double fileID)
{
  FILE *filestar;
  double position;
  filestar = fileManager(fileID);
  if (filestar == NULL) {
    d_rtErrorWithMessageID(c_emlrtRTEI.fName, c_emlrtRTEI.lineNo);
  }
  if ((!(fileID != 0.0)) || (!(fileID != 1.0)) || (!(fileID != 2.0))) {
    filestar = NULL;
  }
  if (filestar == NULL) {
    position = -1.0;
  } else {
    long position_t;
    position_t = ftell(filestar);
    position = (double)position_t;
  }
  return position;
}

} // namespace coder

//
// File trailer for ftell.cpp
//
// [EOF]
//
