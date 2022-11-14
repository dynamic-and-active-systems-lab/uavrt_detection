/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: locBsearch.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "locBsearch.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"

/* Function Definitions */
/*
 * Arguments    : const emxArray_int32_T *x
 *                int xi
 *                int xstart
 *                int xend
 *                int *n
 *                bool *found
 * Return Type  : void
 */
void b_sparse_locBsearch(const emxArray_int32_T *x, int xi, int xstart,
                         int xend, int *n, bool *found)
{
  const int *x_data;
  x_data = x->data;
  if (xstart < xend) {
    if (xi < x_data[xstart - 1]) {
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
        if (xi >= x_data[mid_i - 1]) {
          *n = mid_i;
          low_ip1 = mid_i;
        } else {
          high_i = mid_i;
        }
      }
      *found = (x_data[*n - 1] == xi);
    }
  } else if (xstart == xend) {
    *n = xstart - 1;
    *found = false;
  } else {
    *n = 0;
    *found = false;
  }
}

/*
 * Arguments    : const emxArray_int32_T *x
 *                double xi
 *                int xstart
 *                int xend
 *                int *n
 *                bool *found
 * Return Type  : void
 */
void sparse_locBsearch(const emxArray_int32_T *x, double xi, int xstart,
                       int xend, int *n, bool *found)
{
  const int *x_data;
  x_data = x->data;
  if (xstart < xend) {
    if (xi < x_data[xstart - 1]) {
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
        if (xi >= x_data[mid_i - 1]) {
          *n = mid_i;
          low_ip1 = mid_i;
        } else {
          high_i = mid_i;
        }
      }
      *found = (x_data[*n - 1] == xi);
    }
  } else if (xstart == xend) {
    *n = xstart - 1;
    *found = false;
  } else {
    *n = 0;
    *found = false;
  }
}

/*
 * File trailer for locBsearch.c
 *
 * [EOF]
 */
