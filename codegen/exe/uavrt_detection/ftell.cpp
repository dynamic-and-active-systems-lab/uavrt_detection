//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: ftell.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 20-Oct-2022 20:46:49
//

// Include Files
#include "ftell.h"
#include "fileManager.h"
#include "rt_nonfinite.h"
#include <stdio.h>

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
