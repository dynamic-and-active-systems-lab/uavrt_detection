//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: string1.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 14:31:55
//

// Include Files
#include "string1.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <string.h>

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
namespace coder {
void rtString::init()
{
  static const char b_cv[18]{'f', 'r', 'e', 'q', 'S', 'e', 'a', 'r', 'c',
                             'h', 'H', 'a', 'r', 'd', 'L', 'o', 'c', 'k'};
  Value.set_size(1, 18);
  for (int i{0}; i < 18; i++) {
    Value[i] = b_cv[i];
  }
}

} // namespace coder

//
// File trailer for string1.cpp
//
// [EOF]
//
