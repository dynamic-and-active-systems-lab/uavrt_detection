/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: sum.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "sum.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"

/* Function Definitions */
/*
 * Arguments    : const emxArray_real_T *x_d
 *                const emxArray_int32_T *x_colidx
 *                int x_m
 *                int x_n
 *                emxArray_real_T *y_d
 *                emxArray_int32_T *y_colidx
 *                emxArray_int32_T *y_rowidx
 *                int *y_n
 * Return Type  : void
 */
void b_sum(const emxArray_real_T *x_d, const emxArray_int32_T *x_colidx,
           int x_m, int x_n, emxArray_real_T *y_d, emxArray_int32_T *y_colidx,
           emxArray_int32_T *y_rowidx, int *y_n)
{
  const double *x_d_data;
  double *y_d_data;
  const int *x_colidx_data;
  int col;
  int outidx;
  int xp;
  int xstart;
  int *y_colidx_data;
  int *y_rowidx_data;
  x_colidx_data = x_colidx->data;
  x_d_data = x_d->data;
  if ((x_m == 0) || (x_n == 0) || (x_m == 0)) {
    xstart = y_colidx->size[0];
    y_colidx->size[0] = x_n + 1;
    emxEnsureCapacity_int32_T(y_colidx, xstart);
    y_colidx_data = y_colidx->data;
    for (xstart = 0; xstart <= x_n; xstart++) {
      y_colidx_data[xstart] = 1;
    }
    xstart = y_d->size[0];
    y_d->size[0] = 1;
    emxEnsureCapacity_real_T(y_d, xstart);
    y_d_data = y_d->data;
    y_d_data[0] = 0.0;
    xstart = y_rowidx->size[0];
    y_rowidx->size[0] = 1;
    emxEnsureCapacity_int32_T(y_rowidx, xstart);
    y_rowidx_data = y_rowidx->data;
    y_rowidx_data[0] = 1;
  } else {
    outidx = x_colidx_data[x_colidx->size[0] - 1] - 1;
    if (x_n <= outidx) {
      outidx = x_n;
    }
    if (outidx < 1) {
      outidx = 1;
    }
    xstart = y_d->size[0];
    y_d->size[0] = outidx;
    emxEnsureCapacity_real_T(y_d, xstart);
    y_d_data = y_d->data;
    xstart = y_rowidx->size[0];
    y_rowidx->size[0] = outidx;
    emxEnsureCapacity_int32_T(y_rowidx, xstart);
    y_rowidx_data = y_rowidx->data;
    xstart = y_colidx->size[0];
    y_colidx->size[0] = x_n + 1;
    emxEnsureCapacity_int32_T(y_colidx, xstart);
    y_colidx_data = y_colidx->data;
    y_colidx_data[0] = 1;
    outidx = 1;
    for (col = 0; col < x_n; col++) {
      double r;
      int xend;
      xstart = x_colidx_data[col];
      xend = x_colidx_data[col + 1] - 1;
      r = 0.0;
      for (xp = xstart; xp <= xend; xp++) {
        r += x_d_data[xp - 1];
      }
      if (r != 0.0) {
        y_d_data[outidx - 1] = r;
        outidx++;
      }
      y_colidx_data[col + 1] = outidx;
    }
    xstart = y_colidx_data[y_colidx->size[0] - 1];
    for (outidx = 0; outidx <= xstart - 2; outidx++) {
      y_rowidx_data[outidx] = 1;
    }
  }
  *y_n = x_n;
}

/*
 * Arguments    : const emxArray_real_T *x_d
 *                const emxArray_int32_T *x_colidx
 *                int x_m
 *                emxArray_real_T *y_d
 *                emxArray_int32_T *y_colidx
 *                emxArray_int32_T *y_rowidx
 * Return Type  : void
 */
void c_sum(const emxArray_real_T *x_d, const emxArray_int32_T *x_colidx,
           int x_m, emxArray_real_T *y_d, emxArray_int32_T *y_colidx,
           emxArray_int32_T *y_rowidx)
{
  const double *x_d_data;
  double *y_d_data;
  const int *x_colidx_data;
  int xp;
  int *y_colidx_data;
  int *y_rowidx_data;
  x_colidx_data = x_colidx->data;
  x_d_data = x_d->data;
  if (x_m == 0) {
    int xstart;
    xstart = y_colidx->size[0];
    y_colidx->size[0] = 2;
    emxEnsureCapacity_int32_T(y_colidx, xstart);
    y_colidx_data = y_colidx->data;
    y_colidx_data[0] = 1;
    y_colidx_data[1] = 1;
    xstart = y_d->size[0];
    y_d->size[0] = 1;
    emxEnsureCapacity_real_T(y_d, xstart);
    y_d_data = y_d->data;
    y_d_data[0] = 0.0;
    xstart = y_rowidx->size[0];
    y_rowidx->size[0] = 1;
    emxEnsureCapacity_int32_T(y_rowidx, xstart);
    y_rowidx_data = y_rowidx->data;
    y_rowidx_data[0] = 1;
  } else {
    double r;
    int xend;
    int xstart;
    xstart = y_d->size[0];
    y_d->size[0] = 1;
    emxEnsureCapacity_real_T(y_d, xstart);
    y_d_data = y_d->data;
    xstart = y_rowidx->size[0];
    y_rowidx->size[0] = 1;
    emxEnsureCapacity_int32_T(y_rowidx, xstart);
    y_rowidx_data = y_rowidx->data;
    xstart = y_colidx->size[0];
    y_colidx->size[0] = 2;
    emxEnsureCapacity_int32_T(y_colidx, xstart);
    y_colidx_data = y_colidx->data;
    y_colidx_data[0] = 1;
    y_colidx_data[1] = 1;
    xstart = x_colidx_data[0];
    xend = x_colidx_data[1] - 1;
    r = 0.0;
    for (xp = xstart; xp <= xend; xp++) {
      r += x_d_data[xp - 1];
    }
    if (r != 0.0) {
      y_d_data[0] = r;
      y_colidx_data[1] = 2;
    }
    if (y_colidx_data[1] - 2 >= 0) {
      y_rowidx_data[0] = 1;
    }
  }
}

/*
 * Arguments    : const emxArray_real_T *x
 *                emxArray_real_T *y
 * Return Type  : void
 */
void d_sum(const emxArray_real_T *x, emxArray_real_T *y)
{
  emxArray_real_T *bsum;
  const double *x_data;
  double *bsum_data;
  double *y_data;
  int hi;
  int ib;
  int k;
  int xj;
  x_data = x->data;
  if ((x->size[0] == 0) || (x->size[1] == 0)) {
    int firstBlockLength;
    hi = y->size[0];
    y->size[0] = x->size[0];
    emxEnsureCapacity_real_T(y, hi);
    y_data = y->data;
    firstBlockLength = x->size[0];
    for (hi = 0; hi < firstBlockLength; hi++) {
      y_data[hi] = 0.0;
    }
  } else {
    int bvstride;
    int firstBlockLength;
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
      y_data[xj] = x_data[xj];
      bsum_data[xj] = 0.0;
    }
    for (k = 2; k <= firstBlockLength; k++) {
      xoffset = (k - 1) * (vstride + 1);
      for (xj = 0; xj <= vstride; xj++) {
        y_data[xj] += x_data[xoffset + xj];
      }
    }
    for (ib = 2; ib <= nblocks; ib++) {
      firstBlockLength = (ib - 1) * bvstride;
      for (xj = 0; xj <= vstride; xj++) {
        bsum_data[xj] = x_data[firstBlockLength + xj];
      }
      if (ib == nblocks) {
        hi = lastBlockLength;
      } else {
        hi = 1024;
      }
      for (k = 2; k <= hi; k++) {
        xoffset = firstBlockLength + (k - 1) * (vstride + 1);
        for (xj = 0; xj <= vstride; xj++) {
          bsum_data[xj] += x_data[xoffset + xj];
        }
      }
      for (xj = 0; xj <= vstride; xj++) {
        y_data[xj] += bsum_data[xj];
      }
    }
    emxFree_real_T(&bsum);
  }
}

/*
 * Arguments    : const emxArray_real_T *x
 * Return Type  : double
 */
double sum(const emxArray_real_T *x)
{
  const double *x_data;
  double y;
  int ib;
  int k;
  x_data = x->data;
  if (x->size[0] == 0) {
    y = 0.0;
  } else {
    int firstBlockLength;
    int lastBlockLength;
    int nblocks;
    if (x->size[0] <= 1024) {
      firstBlockLength = x->size[0];
      lastBlockLength = 0;
      nblocks = 1;
    } else {
      firstBlockLength = 1024;
      nblocks = (int)((unsigned int)x->size[0] >> 10);
      lastBlockLength = x->size[0] - (nblocks << 10);
      if (lastBlockLength > 0) {
        nblocks++;
      } else {
        lastBlockLength = 1024;
      }
    }
    y = x_data[0];
    for (k = 2; k <= firstBlockLength; k++) {
      y += x_data[k - 1];
    }
    for (ib = 2; ib <= nblocks; ib++) {
      double bsum;
      int hi;
      firstBlockLength = (ib - 1) << 10;
      bsum = x_data[firstBlockLength];
      if (ib == nblocks) {
        hi = lastBlockLength;
      } else {
        hi = 1024;
      }
      for (k = 2; k <= hi; k++) {
        bsum += x_data[(firstBlockLength + k) - 1];
      }
      y += bsum;
    }
  }
  return y;
}

/*
 * File trailer for sum.c
 *
 * [EOF]
 */
