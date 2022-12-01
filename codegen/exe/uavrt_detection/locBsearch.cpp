//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: locBsearch.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 01-Dec-2022 10:02:54
//

// Include Files
#include "locBsearch.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <string.h>

// Function Definitions
//
// Arguments    : const ::coder::array<int, 1U> &x
//                int xi
//                int xstart
//                int xend
//                int *n
//                bool *found
// Return Type  : void
//
namespace coder {
void b_sparse_locBsearch(const ::coder::array<int, 1U> &x, int xi, int xstart,
                         int xend, int *n, bool *found)
{
  if (xstart < xend) {
    if (xi < x[xstart - 1]) {
      *n = xstart - 1;
      *found = false;
    } else {
      int high_i;
      int low_ip1;
      high_i = xend;
      *n = xstart;
      low_ip1 = xstart;
      while (high_i > low_ip1 + 1) {
        int mid_i;
        mid_i = (*n >> 1) + (high_i >> 1);
        if (((*n & 1) == 1) && ((high_i & 1) == 1)) {
          mid_i++;
        }
        if (xi >= x[mid_i - 1]) {
          *n = mid_i;
          low_ip1 = mid_i;
        } else {
          high_i = mid_i;
        }
      }
      *found = (x[*n - 1] == xi);
    }
  } else if (xstart == xend) {
    *n = xstart - 1;
    *found = false;
  } else {
    *n = 0;
    *found = false;
  }
}

//
// Arguments    : const ::coder::array<int, 1U> &x
//                double xi
//                int xstart
//                int xend
//                int *n
//                bool *found
// Return Type  : void
//
void sparse_locBsearch(const ::coder::array<int, 1U> &x, double xi, int xstart,
                       int xend, int *n, bool *found)
{
  if (xstart < xend) {
    if (xi < x[xstart - 1]) {
      *n = xstart - 1;
      *found = false;
    } else {
      int high_i;
      int low_ip1;
      high_i = xend;
      *n = xstart;
      low_ip1 = xstart;
      while (high_i > low_ip1 + 1) {
        int mid_i;
        mid_i = (*n >> 1) + (high_i >> 1);
        if (((*n & 1) == 1) && ((high_i & 1) == 1)) {
          mid_i++;
        }
        if (xi >= x[mid_i - 1]) {
          *n = mid_i;
          low_ip1 = mid_i;
        } else {
          high_i = mid_i;
        }
      }
      *found = (x[*n - 1] == xi);
    }
  } else if (xstart == xend) {
    *n = xstart - 1;
    *found = false;
  } else {
    *n = 0;
    *found = false;
  }
}

} // namespace coder

//
// File trailer for locBsearch.cpp
//
// [EOF]
//
