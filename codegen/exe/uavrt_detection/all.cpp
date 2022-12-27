//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// all.cpp
//
// Code generation for function 'all'
//

// Include files
#include "all.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <string.h>

// Function Definitions
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

// End of code generation (all.cpp)
