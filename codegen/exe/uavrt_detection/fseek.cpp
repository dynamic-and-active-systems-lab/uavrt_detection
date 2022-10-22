//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: fseek.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Oct-2022 17:38:50
//

// Include Files
#include "fseek.h"
#include "fileManager.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <stdio.h>

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

//
// File trailer for fseek.cpp
//
// [EOF]
//
