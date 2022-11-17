//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// feof.cpp
//
// Code generation for function 'feof'
//

// Include files
#include "feof.h"
#include "fileManager.h"
#include "rt_nonfinite.h"
#include <stdio.h>
#include <string.h>

// Function Definitions
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

// End of code generation (feof.cpp)
