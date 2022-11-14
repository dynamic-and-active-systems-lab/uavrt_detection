/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: mean.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "mean.h"
#include "div.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : const emxArray_real_T *x
 *                emxArray_real_T *y
 * Return Type  : void
 */
void mean(const emxArray_real_T *x, emxArray_real_T *y)
{
  emxArray_int32_T *counts;
  emxArray_real_T *bsum;
  const double *x_data;
  double *bsum_data;
  double *y_data;
  int firstBlockLength;
  int hi;
  int ib;
  int k;
  int xj;
  int *counts_data;
  x_data = x->data;
  emxInit_int32_T(&counts, 1);
  if ((x->size[0] == 0) || (x->size[1] == 0)) {
    hi = y->size[0];
    y->size[0] = x->size[0];
    emxEnsureCapacity_real_T(y, hi);
    y_data = y->data;
    firstBlockLength = x->size[0];
    for (hi = 0; hi < firstBlockLength; hi++) {
      y_data[hi] = 0.0;
    }
    hi = counts->size[0];
    counts->size[0] = x->size[0];
    emxEnsureCapacity_int32_T(counts, hi);
    counts_data = counts->data;
    firstBlockLength = x->size[0];
    for (hi = 0; hi < firstBlockLength; hi++) {
      counts_data[hi] = 0;
    }
  } else {
    int bvstride;
    int ix;
    int lastBlockLength;
    int nblocks;
    int vstride;
    int xoffset;
    vstride = x->size[0] - 1;
    bvstride = x->size[0] << 10;
    hi = y->size[0];
    y->size[0] = x->size[0];
    emxEnsureCapacity_real_T(y, hi);
    y_data = y->data;
    hi = counts->size[0];
    counts->size[0] = x->size[0];
    emxEnsureCapacity_int32_T(counts, hi);
    counts_data = counts->data;
    emxInit_real_T(&bsum, 1);
    hi = bsum->size[0];
    bsum->size[0] = x->size[0];
    emxEnsureCapacity_real_T(bsum, hi);
    bsum_data = bsum->data;
    if (x->size[1] <= 1024) {
      firstBlockLength = x->size[1];
      lastBlockLength = 0;
      nblocks = 1;
    } else {
      firstBlockLength = 1024;
      nblocks = (int)((unsigned int)x->size[1] >> 10);
      lastBlockLength = x->size[1] - (nblocks << 10);
      if (lastBlockLength > 0) {
        nblocks++;
      } else {
        lastBlockLength = 1024;
      }
    }
    for (xj = 0; xj <= vstride; xj++) {
      if (rtIsNaN(x_data[xj])) {
        y_data[xj] = 0.0;
        counts_data[xj] = 0;
      } else {
        y_data[xj] = x_data[xj];
        counts_data[xj] = 1;
      }
      bsum_data[xj] = 0.0;
    }
    for (k = 2; k <= firstBlockLength; k++) {
      xoffset = (k - 1) * (vstride + 1);
      for (xj = 0; xj <= vstride; xj++) {
        ix = xoffset + xj;
        if (!rtIsNaN(x_data[ix])) {
          y_data[xj] += x_data[ix];
          counts_data[xj]++;
        }
      }
    }
    for (ib = 2; ib <= nblocks; ib++) {
      firstBlockLength = (ib - 1) * bvstride;
      for (xj = 0; xj <= vstride; xj++) {
        ix = firstBlockLength + xj;
        if (rtIsNaN(x_data[ix])) {
          bsum_data[xj] = 0.0;
        } else {
          bsum_data[xj] = x_data[ix];
          counts_data[xj]++;
        }
      }
      if (ib == nblocks) {
        hi = lastBlockLength;
      } else {
        hi = 1024;
      }
      for (k = 2; k <= hi; k++) {
        xoffset = firstBlockLength + (k - 1) * (vstride + 1);
        for (xj = 0; xj <= vstride; xj++) {
          ix = xoffset + xj;
          if (!rtIsNaN(x_data[ix])) {
            bsum_data[xj] += x_data[ix];
            counts_data[xj]++;
          }
        }
      }
      for (xj = 0; xj <= vstride; xj++) {
        y_data[xj] += bsum_data[xj];
      }
    }
    emxFree_real_T(&bsum);
  }
  if (y->size[0] == counts->size[0]) {
    firstBlockLength = y->size[0];
    for (hi = 0; hi < firstBlockLength; hi++) {
      y_data[hi] /= (double)counts_data[hi];
    }
  } else {
    b_binary_expand_op(y, counts);
  }
  emxFree_int32_T(&counts);
}

/*
 * File trailer for mean.c
 *
 * [EOF]
 */
