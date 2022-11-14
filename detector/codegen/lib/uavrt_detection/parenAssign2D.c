/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: parenAssign2D.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "parenAssign2D.h"
#include "locBsearch.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include <stddef.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : c_sparse *this
 *                int numAllocRequested
 *                int ub1
 *                int lb2
 *                int ub2
 * Return Type  : void
 */
void b_realloc(c_sparse *this, int numAllocRequested, int ub1, int lb2, int ub2)
{
  emxArray_boolean_T *dt;
  emxArray_int32_T *rowidxt;
  int highOrderA;
  int highOrderB;
  int lowOrderB;
  int overflow;
  int partialResults_idx_0_tmp;
  int partialResults_idx_1;
  int tmp;
  int *rowidxt_data;
  bool *dt_data;
  emxInit_int32_T(&rowidxt, 1);
  highOrderA = rowidxt->size[0];
  rowidxt->size[0] = this->rowidx->size[0];
  emxEnsureCapacity_int32_T(rowidxt, highOrderA);
  rowidxt_data = rowidxt->data;
  partialResults_idx_1 = this->rowidx->size[0];
  for (highOrderA = 0; highOrderA < partialResults_idx_1; highOrderA++) {
    rowidxt_data[highOrderA] = this->rowidx->data[highOrderA];
  }
  emxInit_boolean_T(&dt, 1);
  highOrderA = dt->size[0];
  dt->size[0] = this->d->size[0];
  emxEnsureCapacity_boolean_T(dt, highOrderA);
  dt_data = dt->data;
  partialResults_idx_1 = this->d->size[0];
  for (highOrderA = 0; highOrderA < partialResults_idx_1; highOrderA++) {
    dt_data[highOrderA] = this->d->data[highOrderA];
  }
  highOrderA = this->m >> 16;
  partialResults_idx_1 = this->m & 65535;
  highOrderB = this->n >> 16;
  lowOrderB = this->n & 65535;
  partialResults_idx_0_tmp = partialResults_idx_1 * lowOrderB;
  tmp = partialResults_idx_1 * highOrderB;
  partialResults_idx_1 = tmp << 16;
  overflow = tmp >> 16;
  if (overflow <= 0) {
    tmp = highOrderA * lowOrderB;
    overflow = tmp >> 16;
    if (overflow <= 0) {
      overflow = highOrderA * highOrderB;
      if (overflow <= 0) {
        if (partialResults_idx_0_tmp > MAX_int32_T - partialResults_idx_1) {
          partialResults_idx_1 =
              (partialResults_idx_0_tmp + partialResults_idx_1) - MAX_int32_T;
          overflow = 1;
        } else {
          partialResults_idx_1 += partialResults_idx_0_tmp;
        }
        if (partialResults_idx_1 > MAX_int32_T - (tmp << 16)) {
          overflow++;
        }
      }
    }
  }
  if (overflow == 0) {
    partialResults_idx_1 = this->m * this->n;
    if (numAllocRequested <= partialResults_idx_1) {
      partialResults_idx_1 = numAllocRequested;
    }
    if (partialResults_idx_1 <= 1) {
      partialResults_idx_1 = 1;
    }
  } else if (numAllocRequested <= 1) {
    partialResults_idx_1 = 1;
  } else {
    partialResults_idx_1 = numAllocRequested;
  }
  highOrderA = this->rowidx->size[0];
  this->rowidx->size[0] = partialResults_idx_1;
  emxEnsureCapacity_int32_T(this->rowidx, highOrderA);
  for (highOrderA = 0; highOrderA < partialResults_idx_1; highOrderA++) {
    this->rowidx->data[highOrderA] = 0;
  }
  highOrderA = this->d->size[0];
  this->d->size[0] = partialResults_idx_1;
  emxEnsureCapacity_boolean_T(this->d, highOrderA);
  for (highOrderA = 0; highOrderA < partialResults_idx_1; highOrderA++) {
    this->d->data[highOrderA] = false;
  }
  this->maxnz = partialResults_idx_1;
  for (partialResults_idx_1 = 0; partialResults_idx_1 < ub1;
       partialResults_idx_1++) {
    this->rowidx->data[partialResults_idx_1] =
        rowidxt_data[partialResults_idx_1];
    this->d->data[partialResults_idx_1] = dt_data[partialResults_idx_1];
  }
  for (partialResults_idx_1 = lb2; partialResults_idx_1 <= ub2;
       partialResults_idx_1++) {
    this->rowidx->data[partialResults_idx_1] =
        rowidxt_data[partialResults_idx_1 - 1];
    this->d->data[partialResults_idx_1] = dt_data[partialResults_idx_1 - 1];
  }
  emxFree_boolean_T(&dt);
  emxFree_int32_T(&rowidxt);
}

/*
 * Arguments    : c_sparse *this
 *                bool rhs
 *                double r
 *                double c
 * Return Type  : void
 */
void sparse_parenAssign2D(c_sparse *this, bool rhs, double r, double c)
{
  int k;
  int vidx;
  bool thisv;
  b_sparse_locBsearch(this->rowidx, (int)r, this->colidx->data[(int)c - 1],
                      this->colidx->data[(int)c], &vidx, &thisv);
  if (thisv) {
    thisv = this->d->data[vidx - 1];
  } else {
    thisv = false;
  }
  if (thisv || rhs) {
    if (thisv && rhs) {
      this->d->data[vidx - 1] = true;
    } else if (!thisv) {
      int nelem;
      if (this->colidx->data[this->colidx->size[0] - 1] - 1 == this->maxnz) {
        b_realloc(this, this->colidx->data[this->colidx->size[0] - 1] + 9, vidx,
                  vidx + 1, this->colidx->data[this->colidx->size[0] - 1] - 1);
        this->rowidx->data[vidx] = (int)r;
        this->d->data[vidx] = rhs;
      } else {
        nelem = (this->colidx->data[this->colidx->size[0] - 1] - vidx) - 1;
        if (nelem > 0) {
          memmove((void *)&this->rowidx->data[vidx + 1],
                  (void *)&this->rowidx->data[vidx],
                  (size_t)nelem * sizeof(int));
          memmove((void *)&this->d->data[vidx + 1],
                  (void *)&this->d->data[vidx], (size_t)nelem * sizeof(bool));
        }
        this->d->data[vidx] = rhs;
        this->rowidx->data[vidx] = (int)r;
      }
      vidx = (int)c + 1;
      nelem = this->n + 1;
      for (k = vidx; k <= nelem; k++) {
        this->colidx->data[k - 1]++;
      }
    } else {
      int nelem;
      nelem = (this->colidx->data[this->colidx->size[0] - 1] - vidx) - 1;
      if (nelem > 0) {
        memmove((void *)&this->rowidx->data[vidx - 1],
                (void *)&this->rowidx->data[vidx], (size_t)nelem * sizeof(int));
        memmove((void *)&this->d->data[vidx - 1], (void *)&this->d->data[vidx],
                (size_t)nelem * sizeof(bool));
      }
      vidx = (int)c + 1;
      nelem = this->n + 1;
      for (k = vidx; k <= nelem; k++) {
        this->colidx->data[k - 1]--;
      }
    }
  }
}

/*
 * File trailer for parenAssign2D.c
 *
 * [EOF]
 */
