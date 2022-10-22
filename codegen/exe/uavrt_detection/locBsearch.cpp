//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: locBsearch.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Oct-2022 17:38:50
//

// Include Files
#include "locBsearch.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<int, 1U> &x
//                int xi
//                int xstart
//                int xend
//                int *n
//                boolean_T *found
// Return Type  : void
//
namespace coder {
void b_sparse_locBsearch(const ::coder::array<int, 1U> &x, int xi, int xstart,
                         int xend, int *n, boolean_T *found)
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
//                boolean_T *found
// Return Type  : void
//
void sparse_locBsearch(const ::coder::array<int, 1U> &x, double xi, int xstart,
                       int xend, int *n, boolean_T *found)
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
