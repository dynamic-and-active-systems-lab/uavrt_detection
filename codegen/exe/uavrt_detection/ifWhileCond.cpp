//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: ifWhileCond.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 20-Oct-2022 20:46:49
//

// Include Files
#include "ifWhileCond.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<boolean_T, 1U> &x
// Return Type  : boolean_T
//
namespace coder {
namespace internal {
boolean_T ifWhileCond(const ::coder::array<boolean_T, 1U> &x)
{
  boolean_T y;
  y = (x.size(0) != 0);
  if (y) {
    int k;
    boolean_T exitg1;
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k <= x.size(0) - 1)) {
      if (!x[k]) {
        y = false;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }
  return y;
}

} // namespace internal
} // namespace coder

//
// File trailer for ifWhileCond.cpp
//
// [EOF]
//
