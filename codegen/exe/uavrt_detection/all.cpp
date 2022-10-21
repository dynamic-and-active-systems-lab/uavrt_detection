//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: all.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 20-Oct-2022 20:46:49
//

// Include Files
#include "all.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<boolean_T, 2U> &x
//                ::coder::array<boolean_T, 1U> &y
// Return Type  : void
//
namespace coder {
void all(const ::coder::array<boolean_T, 2U> &x,
         ::coder::array<boolean_T, 1U> &y)
{
  int i1;
  int i2;
  int vstride;
  y.set_size(x.size(0));
  vstride = x.size(0);
  for (i2 = 0; i2 < vstride; i2++) {
    y[i2] = true;
  }
  vstride = x.size(0);
  i2 = (x.size(1) - 1) * x.size(0);
  i1 = 0;
  for (int j{0}; j < vstride; j++) {
    int ix;
    boolean_T exitg1;
    i1++;
    i2++;
    ix = i1;
    exitg1 = false;
    while ((!exitg1) && ((vstride > 0) && (ix <= i2))) {
      if (!x[ix - 1]) {
        y[j] = false;
        exitg1 = true;
      } else {
        ix += vstride;
      }
    }
  }
}

} // namespace coder

//
// File trailer for all.cpp
//
// [EOF]
//
