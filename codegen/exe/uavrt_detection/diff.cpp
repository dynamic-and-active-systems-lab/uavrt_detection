//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// diff.cpp
//
// Code generation for function 'diff'
//

// Include files
#include "diff.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <string.h>

// Function Definitions
namespace coder {
void diff(const ::coder::array<double, 1U> &x, ::coder::array<double, 1U> &y)
{
  int dimSize;
  dimSize = x.size(0);
  if (x.size(0) == 0) {
    y.set_size(0);
  } else {
    int u0;
    u0 = x.size(0) - 1;
    if (u0 > 1) {
      u0 = 1;
    }
    if (u0 < 1) {
      y.set_size(0);
    } else {
      y.set_size(x.size(0) - 1);
      if (x.size(0) - 1 != 0) {
        double work_data;
        work_data = x[0];
        for (u0 = 2; u0 <= dimSize; u0++) {
          double tmp2;
          tmp2 = work_data;
          work_data = x[u0 - 1];
          y[u0 - 2] = work_data - tmp2;
        }
      }
    }
  }
}

} // namespace coder

// End of code generation (diff.cpp)
