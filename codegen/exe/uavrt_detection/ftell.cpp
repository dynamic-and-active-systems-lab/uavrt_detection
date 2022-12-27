//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// ftell.cpp
//
// Code generation for function 'ftell'
//

// Include files
#include "ftell.h"
#include "fileManager.h"
#include "rt_nonfinite.h"
#include <stdio.h>
#include <string.h>

// Function Definitions
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

// End of code generation (ftell.cpp)
