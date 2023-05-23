//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: locBsearch.cpp
//
<<<<<<< HEAD
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 23-May-2023 12:05:02
=======
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Apr-2023 11:47:02
>>>>>>> 3930a1e557481905555f2756f2f70ac82e87beba
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
//                boolean_T &found
// Return Type  : int
//
namespace coder {
int b_sparse_locBsearch(const ::coder::array<int, 1U> &x, int xi, int xstart,
                        int xend, boolean_T &found)
{
  int n;
  if (xstart < xend) {
    if (xi < x[xstart - 1]) {
      n = xstart - 1;
      found = false;
    } else {
      int high_i;
      int low_ip1;
      high_i = xend;
      n = xstart;
      low_ip1 = xstart;
      while (high_i > low_ip1 + 1) {
        int mid_i;
        mid_i = (n >> 1) + (high_i >> 1);
        if (((n & 1) == 1) && ((high_i & 1) == 1)) {
          mid_i++;
        }
        if (xi >= x[mid_i - 1]) {
          n = mid_i;
          low_ip1 = mid_i;
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

//
// Arguments    : const ::coder::array<int, 1U> &x
//                double xi
//                int xstart
//                int xend
//                boolean_T &found
// Return Type  : int
//
int sparse_locBsearch(const ::coder::array<int, 1U> &x, double xi, int xstart,
                      int xend, boolean_T &found)
{
  int n;
  if (xstart < xend) {
    if (xi < x[xstart - 1]) {
      n = xstart - 1;
      found = false;
    } else {
      int high_i;
      int low_ip1;
      high_i = xend;
      n = xstart;
      low_ip1 = xstart;
      while (high_i > low_ip1 + 1) {
        int mid_i;
        mid_i = (n >> 1) + (high_i >> 1);
        if (((n & 1) == 1) && ((high_i & 1) == 1)) {
          mid_i++;
        }
        if (xi >= x[mid_i - 1]) {
          n = mid_i;
          low_ip1 = mid_i;
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
