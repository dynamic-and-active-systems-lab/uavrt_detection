//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// fseek.cpp
//
// Code generation for function 'fseek'
//

// Include files
#include "fseek.h"
#include "fileManager.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <stdio.h>
#include <string.h>

// Function Definitions
namespace coder {
void b_fseek(double fileID, double offset)
{
  int wherefrom;
  wherefrom = SEEK_SET;
  if ((!std::isinf(offset)) && (!std::isnan(offset)) &&
      (std::floor(offset) == offset)) {
    FILE *filestar;
    filestar = fileManager(fileID);
    if ((!(fileID != 0.0)) || (!(fileID != 1.0)) || (!(fileID != 2.0))) {
      filestar = NULL;
    }
    if (!(filestar == NULL)) {
      fseek(filestar, (long int)offset, wherefrom);
    }
  }
}

} // namespace coder

// End of code generation (fseek.cpp)
