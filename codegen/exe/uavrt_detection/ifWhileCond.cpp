//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// ifWhileCond.cpp
//
// Code generation for function 'ifWhileCond'
//

// Include files
#include "ifWhileCond.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <string.h>

// Function Definitions
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

// End of code generation (ifWhileCond.cpp)
