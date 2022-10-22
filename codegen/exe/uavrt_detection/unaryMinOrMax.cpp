//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: unaryMinOrMax.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 22-Oct-2022 15:24:58
//

// Include Files
#include "unaryMinOrMax.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 1U> &x
// Return Type  : double
//
namespace coder {
namespace internal {
double unaryMinOrMax_anonFcn1(const ::coder::array<double, 1U> &x)
{
  double varargout_1;
  int last;
  last = x.size(0);
  if (x.size(0) <= 2) {
    if (x.size(0) == 1) {
      varargout_1 = x[0];
    } else if ((x[0] > x[x.size(0) - 1]) ||
               (std::isnan(x[0]) && (!std::isnan(x[x.size(0) - 1])))) {
      varargout_1 = x[x.size(0) - 1];
    } else {
      varargout_1 = x[0];
    }
  } else {
    int idx;
    int k;
    if (!std::isnan(x[0])) {
      idx = 1;
    } else {
      boolean_T exitg1;
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= last)) {
        if (!std::isnan(x[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }
    if (idx == 0) {
      varargout_1 = x[0];
    } else {
      varargout_1 = x[idx - 1];
      idx++;
      for (k = idx; k <= last; k++) {
        double d;
        d = x[k - 1];
        if (varargout_1 > d) {
          varargout_1 = d;
        }
      }
    }
  }
  return varargout_1;
}

} // namespace internal
} // namespace coder

//
// File trailer for unaryMinOrMax.cpp
//
// [EOF]
//
