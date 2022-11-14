/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: movSumProdOrMean.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "movSumProdOrMean.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include "omp.h"

/* Function Definitions */
/*
 * Arguments    : const emxArray_real_T *x
 *                int nx
 *                emxArray_real_T *y
 * Return Type  : void
 */
void vmovfun(const emxArray_real_T *x, int nx, emxArray_real_T *y)
{
  const double *x_data;
  double b_y;
  double bsum;
  double *y_data;
  int b_k;
  int firstBlockLength;
  int hi;
  int i;
  int iLeft;
  int ib;
  int k;
  int lastBlockLength;
  int loop_ub;
  int nblocks;
  int vlen;
  x_data = x->data;
  i = y->size[0];
  y->size[0] = x->size[0];
  emxEnsureCapacity_real_T(y, i);
  y_data = y->data;
  loop_ub = x->size[0];
  for (i = 0; i < loop_ub; i++) {
    y_data[i] = 0.0;
  }
  loop_ub = nx - 1;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    iLeft, vlen, b_y, firstBlockLength, lastBlockLength, nblocks, b_k, ib,     \
    bsum, hi)

  for (k = 0; k <= loop_ub; k++) {
    if (k + 1 <= 1) {
      iLeft = 0;
    } else {
      iLeft = k - 1;
    }
    if (k + 2 > x->size[0]) {
      vlen = x->size[0];
    } else {
      vlen = k + 2;
    }
    vlen -= iLeft;
    if ((x->size[0] == 0) || (vlen == 0)) {
      b_y = 0.0;
    } else {
      if (vlen <= 1024) {
        firstBlockLength = vlen;
        lastBlockLength = 0;
        nblocks = 1;
      } else {
        firstBlockLength = 1024;
        nblocks = vlen / 1024;
        lastBlockLength = vlen - (nblocks << 10);
        if (lastBlockLength > 0) {
          nblocks++;
        } else {
          lastBlockLength = 1024;
        }
      }
      b_y = x_data[iLeft];
      for (b_k = 2; b_k <= firstBlockLength; b_k++) {
        b_y += x_data[(iLeft + b_k) - 1];
      }
      for (ib = 2; ib <= nblocks; ib++) {
        firstBlockLength = iLeft + ((ib - 1) << 10);
        bsum = x_data[firstBlockLength];
        if (ib == nblocks) {
          hi = lastBlockLength;
        } else {
          hi = 1024;
        }
        for (b_k = 2; b_k <= hi; b_k++) {
          bsum += x_data[(firstBlockLength + b_k) - 1];
        }
        b_y += bsum;
      }
    }
    y_data[k] = b_y / (double)vlen;
  }
}

/*
 * File trailer for movSumProdOrMean.c
 *
 * [EOF]
 */
