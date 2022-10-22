//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: abs.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 22-Oct-2022 15:24:58
//

// Include Files
#include "abs.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_rtwutil.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<creal_T, 2U> &x
//                ::coder::array<double, 2U> &y
// Return Type  : void
//
namespace coder {
void b_abs(const ::coder::array<creal_T, 2U> &x, ::coder::array<double, 2U> &y)
{
  int nx;
  nx = x.size(0) * x.size(1);
  y.set_size(x.size(0), x.size(1));
  for (int k{0}; k < nx; k++) {
    y[k] = rt_hypotd_snf(x[k].re, x[k].im);
  }
}

} // namespace coder

//
// File trailer for abs.cpp
//
// [EOF]
//
