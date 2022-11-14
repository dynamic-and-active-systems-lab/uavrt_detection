/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: sparse.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "sparse.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"

/* Function Definitions */
/*
 * Arguments    : const emxArray_real_T *varargin_1
 *                emxArray_real_T *y_d
 *                emxArray_int32_T *y_colidx
 *                emxArray_int32_T *y_rowidx
 *                int *y_m
 *                int *y_maxnz
 * Return Type  : void
 */
void b_sparse(const emxArray_real_T *varargin_1, emxArray_real_T *y_d,
              emxArray_int32_T *y_colidx, emxArray_int32_T *y_rowidx, int *y_m,
              int *y_maxnz)
{
  const double *varargin_1_data;
  double *y_d_data;
  int ctr;
  int k;
  int mInt;
  int numalloc;
  int *y_colidx_data;
  int *y_rowidx_data;
  varargin_1_data = varargin_1->data;
  mInt = varargin_1->size[0];
  numalloc = 0;
  ctr = varargin_1->size[0];
  for (k = 0; k < ctr; k++) {
    if (varargin_1_data[k] != 0.0) {
      numalloc++;
    }
  }
  *y_m = varargin_1->size[0];
  if (numalloc < 1) {
    numalloc = 1;
  }
  ctr = y_d->size[0];
  y_d->size[0] = numalloc;
  emxEnsureCapacity_real_T(y_d, ctr);
  y_d_data = y_d->data;
  for (ctr = 0; ctr < numalloc; ctr++) {
    y_d_data[ctr] = 0.0;
  }
  ctr = y_colidx->size[0];
  y_colidx->size[0] = 2;
  emxEnsureCapacity_int32_T(y_colidx, ctr);
  y_colidx_data = y_colidx->data;
  y_colidx_data[0] = 1;
  ctr = y_rowidx->size[0];
  y_rowidx->size[0] = numalloc;
  emxEnsureCapacity_int32_T(y_rowidx, ctr);
  y_rowidx_data = y_rowidx->data;
  for (ctr = 0; ctr < numalloc; ctr++) {
    y_rowidx_data[ctr] = 0;
  }
  y_rowidx_data[0] = 1;
  ctr = 0;
  for (k = 0; k < mInt; k++) {
    if (varargin_1_data[k] != 0.0) {
      y_rowidx_data[ctr] = k + 1;
      y_d_data[ctr] = 1.0;
      ctr++;
    }
  }
  y_colidx_data[1] = ctr + 1;
  *y_maxnz = numalloc;
}

/*
 * Arguments    : const emxArray_boolean_T *varargin_1
 *                emxArray_boolean_T *y_d
 *                emxArray_int32_T *y_colidx
 *                emxArray_int32_T *y_rowidx
 *                int *y_n
 * Return Type  : void
 */
void sparse(const emxArray_boolean_T *varargin_1, emxArray_boolean_T *y_d,
            emxArray_int32_T *y_colidx, emxArray_int32_T *y_rowidx, int *y_n)
{
  int ctr;
  int i;
  int nInt;
  int numalloc;
  int *y_colidx_data;
  int *y_rowidx_data;
  const bool *varargin_1_data;
  bool *y_d_data;
  varargin_1_data = varargin_1->data;
  nInt = varargin_1->size[1];
  numalloc = 0;
  i = varargin_1->size[1];
  for (ctr = 0; ctr < i; ctr++) {
    if (varargin_1_data[ctr]) {
      numalloc++;
    }
  }
  *y_n = varargin_1->size[1];
  if (numalloc < 1) {
    numalloc = 1;
  }
  i = y_d->size[0];
  y_d->size[0] = numalloc;
  emxEnsureCapacity_boolean_T(y_d, i);
  y_d_data = y_d->data;
  for (i = 0; i < numalloc; i++) {
    y_d_data[i] = false;
  }
  i = y_colidx->size[0];
  y_colidx->size[0] = varargin_1->size[1] + 1;
  emxEnsureCapacity_int32_T(y_colidx, i);
  y_colidx_data = y_colidx->data;
  ctr = varargin_1->size[1];
  for (i = 0; i <= ctr; i++) {
    y_colidx_data[i] = 0;
  }
  y_colidx_data[0] = 1;
  i = y_rowidx->size[0];
  y_rowidx->size[0] = numalloc;
  emxEnsureCapacity_int32_T(y_rowidx, i);
  y_rowidx_data = y_rowidx->data;
  for (i = 0; i < numalloc; i++) {
    y_rowidx_data[i] = 0;
  }
  y_rowidx_data[0] = 1;
  ctr = 0;
  for (numalloc = 0; numalloc < nInt; numalloc++) {
    if (varargin_1_data[numalloc]) {
      y_rowidx_data[ctr] = 1;
      y_d_data[ctr] = true;
      ctr++;
    }
    y_colidx_data[numalloc + 1] = ctr + 1;
  }
}

/*
 * File trailer for sparse.c
 *
 * [EOF]
 */
