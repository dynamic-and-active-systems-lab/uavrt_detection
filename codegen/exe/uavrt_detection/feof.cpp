//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: feof.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 22-Oct-2022 15:24:58
//

// Include Files
#include "feof.h"
#include "fileManager.h"
#include "rt_nonfinite.h"
#include <stdio.h>

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
    st = 0.0;
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
