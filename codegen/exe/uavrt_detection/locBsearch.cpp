//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: locBsearch.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "locBsearch.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const array<int, 1U> &x
//                double xi
//                int xstart
//                int xend
//                boolean_T &found
// Return Type  : int
//
namespace coder {
int sparse_locBsearch(const array<int, 1U> &x, double xi, int xstart, int xend,
                      boolean_T &found)
{
  int n;
  if (xstart < xend) {
    if (xi < x[xstart - 1]) {
      n = xstart - 1;
      found = false;
    } else {
      int high_i;
      high_i = xend;
      n = xstart;
      while (high_i > n + 1) {
        int mid_i;
        mid_i = (n >> 1) + (high_i >> 1);
        if (((static_cast<unsigned int>(n) & 1U) == 1U) &&
            ((static_cast<unsigned int>(high_i) & 1U) == 1U)) {
          mid_i++;
        }
        if (xi >= x[mid_i - 1]) {
          n = mid_i;
        } else {
          high_i = mid_i;
        }
      }
      found = (x[n - 1] == xi);
    }
  } else if (xstart == xend) {
    n = xstart - 1;
    found = false;
  } else {
    n = 0;
    found = false;
  }
  return n;
}

} // namespace coder

//
// File trailer for locBsearch.cpp
//
// [EOF]
//
