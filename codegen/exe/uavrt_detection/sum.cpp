//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sum.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 14:31:55
//

// Include Files
#include "sum.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Definitions
//
// Arguments    : const double x_data[]
//                int x_size
// Return Type  : double
//
namespace coder {
double sum(const double x_data[], int x_size)
{
  double y;
  if (x_size == 0) {
    y = 0.0;
  } else {
    y = x_data[0];
  }
  return y;
}

} // namespace coder

//
// File trailer for sum.cpp
//
// [EOF]
//
