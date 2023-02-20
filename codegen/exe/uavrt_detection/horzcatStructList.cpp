//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: horzcatStructList.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 14:31:55
//

// Include Files
#include "horzcatStructList.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Definitions
//
// Arguments    : const int structure_size[2]
//                int result_size[2]
// Return Type  : void
//
namespace coder {
namespace internal {
void horzcatStructList(const int structure_size[2], int result_size[2])
{
  result_size[0] = 1;
  result_size[1] = (structure_size[1] != 0);
}

} // namespace internal
} // namespace coder

//
// File trailer for horzcatStructList.cpp
//
// [EOF]
//
