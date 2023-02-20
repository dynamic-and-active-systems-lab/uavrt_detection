//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: heapsort.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 14:31:55
//

// Include Files
#include "heapsort.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Definitions
//
// Arguments    : int xstart
//                int xend
// Return Type  : void
//
namespace coder {
namespace internal {
void b_heapsort(int xstart, int xend)
{
  if (xend - xstart > 2147483646) {
    check_forloop_overflow_error();
  }
}

} // namespace internal
} // namespace coder

//
// File trailer for heapsort.cpp
//
// [EOF]
//
