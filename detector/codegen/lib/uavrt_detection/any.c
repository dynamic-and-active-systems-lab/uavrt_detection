/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: any.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "any.h"
#include "introsort.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"

/* Function Definitions */
/*
 * Arguments    : const emxArray_int32_T *x_colidx
 *                const emxArray_int32_T *x_rowidx
 *                int x_n
 *                emxArray_boolean_T *y_d
 *                emxArray_int32_T *y_colidx
 *                emxArray_int32_T *y_rowidx
 * Return Type  : void
 */
void any(const emxArray_int32_T *x_colidx, const emxArray_int32_T *x_rowidx,
         int x_n, emxArray_boolean_T *y_d, emxArray_int32_T *y_colidx,
         emxArray_int32_T *y_rowidx)
{
  emxArray_int32_T *xrowidx;
  emxArray_int32_T *xrowidxPerm;
  emxArray_int32_T *y;
  const int *x_colidx_data;
  const int *x_rowidx_data;
  int k;
  int *xrowidxPerm_data;
  int *xrowidx_data;
  int *y_data;
  bool *y_d_data;
  x_rowidx_data = x_rowidx->data;
  x_colidx_data = x_colidx->data;
  if (x_n == 0) {
    k = y_colidx->size[0];
    y_colidx->size[0] = 2;
    emxEnsureCapacity_int32_T(y_colidx, k);
    xrowidxPerm_data = y_colidx->data;
    xrowidxPerm_data[0] = 1;
    xrowidxPerm_data[1] = 1;
    k = y_d->size[0];
    y_d->size[0] = 1;
    emxEnsureCapacity_boolean_T(y_d, k);
    y_d_data = y_d->data;
    y_d_data[0] = false;
    k = y_rowidx->size[0];
    y_rowidx->size[0] = 1;
    emxEnsureCapacity_int32_T(y_rowidx, k);
    y_data = y_rowidx->data;
    y_data[0] = 1;
  } else if (x_n != 0) {
    int n;
    int xnnz;
    int yk;
    xnnz = x_colidx_data[x_colidx->size[0] - 1];
    yk = 0;
    for (k = 0; k <= xnnz - 2; k++) {
      if (yk == 0) {
        yk = 1;
      }
    }
    n = 0;
    if (yk > 0) {
      n = 1;
    } else {
      yk = 1;
    }
    k = y_d->size[0];
    y_d->size[0] = 1;
    emxEnsureCapacity_boolean_T(y_d, k);
    y_d_data = y_d->data;
    y_d_data[0] = true;
    k = y_rowidx->size[0];
    y_rowidx->size[0] = 1;
    emxEnsureCapacity_int32_T(y_rowidx, k);
    y_data = y_rowidx->data;
    y_data[0] = yk;
    k = y_colidx->size[0];
    y_colidx->size[0] = 2;
    emxEnsureCapacity_int32_T(y_colidx, k);
    xrowidxPerm_data = y_colidx->data;
    xrowidxPerm_data[0] = 1;
    xrowidxPerm_data[1] = n + 1;
  } else {
    int loop_ub;
    int n;
    int xnnz;
    int yk;
    xnnz = x_colidx_data[x_colidx->size[0] - 1] - 1;
    if (x_colidx_data[x_colidx->size[0] - 1] - 1 < 1) {
      loop_ub = 0;
    } else {
      loop_ub = x_colidx_data[x_colidx->size[0] - 1] - 1;
    }
    if (loop_ub < 1) {
      n = 0;
    } else {
      n = loop_ub;
    }
    emxInit_int32_T(&y, 2);
    k = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = n;
    emxEnsureCapacity_int32_T(y, k);
    y_data = y->data;
    if (n > 0) {
      y_data[0] = 1;
      yk = 1;
      for (k = 2; k <= n; k++) {
        yk++;
        y_data[k - 1] = yk;
      }
    }
    emxInit_int32_T(&xrowidx, 1);
    k = xrowidx->size[0];
    xrowidx->size[0] = loop_ub;
    emxEnsureCapacity_int32_T(xrowidx, k);
    xrowidx_data = xrowidx->data;
    for (k = 0; k < loop_ub; k++) {
      xrowidx_data[k] = x_rowidx_data[k];
    }
    emxInit_int32_T(&xrowidxPerm, 1);
    k = xrowidxPerm->size[0];
    xrowidxPerm->size[0] = y->size[1];
    emxEnsureCapacity_int32_T(xrowidxPerm, k);
    xrowidxPerm_data = xrowidxPerm->data;
    yk = y->size[1];
    for (k = 0; k < yk; k++) {
      xrowidxPerm_data[k] = y_data[k];
    }
    emxFree_int32_T(&y);
    b_introsort(xrowidxPerm, loop_ub, xrowidx);
    xrowidxPerm_data = xrowidxPerm->data;
    k = xrowidx->size[0];
    xrowidx->size[0] = xrowidxPerm->size[0];
    emxEnsureCapacity_int32_T(xrowidx, k);
    xrowidx_data = xrowidx->data;
    loop_ub = xrowidxPerm->size[0];
    for (k = 0; k < loop_ub; k++) {
      xrowidx_data[k] = x_rowidx_data[xrowidxPerm_data[k] - 1];
    }
    emxFree_int32_T(&xrowidxPerm);
    n = 0;
    k = 0;
    while (k + 1 <= xnnz) {
      yk = xrowidx_data[k];
      n++;
      xrowidx_data[n - 1] = xrowidx_data[k];
      while ((k + 1 <= xnnz) && (xrowidx_data[k] == yk)) {
        k++;
      }
    }
    yk = n;
    if (n < 1) {
      yk = 1;
    }
    k = y_rowidx->size[0];
    y_rowidx->size[0] = yk;
    emxEnsureCapacity_int32_T(y_rowidx, k);
    y_data = y_rowidx->data;
    k = y_colidx->size[0];
    y_colidx->size[0] = 2;
    emxEnsureCapacity_int32_T(y_colidx, k);
    xrowidxPerm_data = y_colidx->data;
    xrowidxPerm_data[0] = 1;
    xrowidxPerm_data[1] = n + 1;
    for (k = 0; k < n; k++) {
      y_data[k] = xrowidx_data[k];
    }
    emxFree_int32_T(&xrowidx);
    k = y_d->size[0];
    y_d->size[0] = yk;
    emxEnsureCapacity_boolean_T(y_d, k);
    y_d_data = y_d->data;
    for (k = 0; k < yk; k++) {
      y_d_data[k] = true;
    }
  }
}

/*
 * File trailer for any.c
 *
 * [EOF]
 */
