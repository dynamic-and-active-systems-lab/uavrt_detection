//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: unique.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 14:31:55
//

// Include Files
#include "unique.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Definitions
//
// Arguments    : int a_size[2]
// Return Type  : void
//
namespace coder {
void unique_rows(int a_size[2])
{
  if (a_size[0] != 0) {
    int a;
    a = a_size[1] - 1;
    a_size[0] = 1;
    a_size[1] = a + 1;
  }
}

} // namespace coder

//
// File trailer for unique.cpp
//
// [EOF]
//
