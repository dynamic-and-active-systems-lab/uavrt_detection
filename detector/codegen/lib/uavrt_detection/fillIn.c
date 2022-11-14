/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: fillIn.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "fillIn.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"

/* Function Definitions */
/*
 * Arguments    : d_sparse *this
 * Return Type  : void
 */
void sparse_fillIn(d_sparse *this)
{
  int c;
  int i;
  int idx;
  idx = 1;
  i = this->colidx->size[0];
  for (c = 0; c <= i - 2; c++) {
    int ridx;
    ridx = this->colidx->data[c];
    this->colidx->data[c] = idx;
    int exitg1;
    int i1;
    do {
      exitg1 = 0;
      i1 = this->colidx->data[c + 1];
      if (ridx < i1) {
        double val;
        int currRowIdx;
        val = 0.0;
        currRowIdx = this->rowidx->data[ridx - 1];
        while ((ridx < i1) && (this->rowidx->data[ridx - 1] == currRowIdx)) {
          val += this->d->data[ridx - 1];
          ridx++;
        }
        if (val != 0.0) {
          this->d->data[idx - 1] = val;
          this->rowidx->data[idx - 1] = currRowIdx;
          idx++;
        }
      } else {
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  this->colidx->data[this->colidx->size[0] - 1] = idx;
}

/*
 * File trailer for fillIn.c
 *
 * [EOF]
 */
