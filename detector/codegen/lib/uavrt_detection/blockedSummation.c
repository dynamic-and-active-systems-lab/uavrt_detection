/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: blockedSummation.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "blockedSummation.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : const emxArray_real_T *x
 *                int vlen
 *                double *y
 *                int *counts
 * Return Type  : void
 */
void colMajorFlatIter(const emxArray_real_T *x, int vlen, double *y,
                      int *counts)
{
  const double *x_data;
  double bsum;
  int firstBlockLength;
  int ib;
  int k;
  int lastBlockLength;
  int nblocks;
  x_data = x->data;
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
  if (rtIsNaN(x_data[0])) {
    *y = 0.0;
    *counts = 0;
  } else {
    *y = x_data[0];
    *counts = 1;
  }
  for (k = 2; k <= firstBlockLength; k++) {
    bsum = x_data[k - 1];
    if (!rtIsNaN(bsum)) {
      *y += bsum;
      (*counts)++;
    }
  }
  for (ib = 2; ib <= nblocks; ib++) {
    int hi;
    firstBlockLength = (ib - 1) << 10;
    if (rtIsNaN(x_data[firstBlockLength])) {
      bsum = 0.0;
    } else {
      bsum = x_data[firstBlockLength];
      (*counts)++;
    }
    if (ib == nblocks) {
      hi = lastBlockLength;
    } else {
      hi = 1024;
    }
    for (k = 2; k <= hi; k++) {
      int xoffset;
      xoffset = (firstBlockLength + k) - 1;
      if (!rtIsNaN(x_data[xoffset])) {
        bsum += x_data[xoffset];
        (*counts)++;
      }
    }
    *y += bsum;
  }
}

/*
 * File trailer for blockedSummation.c
 *
 * [EOF]
 */
