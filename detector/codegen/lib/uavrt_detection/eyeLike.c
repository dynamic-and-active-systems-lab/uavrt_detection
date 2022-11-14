/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: eyeLike.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "eyeLike.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"

/* Function Definitions */
/*
 * Arguments    : int ndiag
 *                int m
 *                int n
 *                emxArray_real_T *I_d
 *                emxArray_int32_T *I_colidx
 *                emxArray_int32_T *I_rowidx
 *                int *I_m
 *                int *I_n
 *                int *I_maxnz
 * Return Type  : void
 */
void sparse_eyeLike(int ndiag, int m, int n, emxArray_real_T *I_d,
                    emxArray_int32_T *I_colidx, emxArray_int32_T *I_rowidx,
                    int *I_m, int *I_n, int *I_maxnz)
{
  double *I_d_data;
  int b_i;
  int c;
  int i;
  int nzmax;
  int *I_colidx_data;
  int *I_rowidx_data;
  nzmax = ndiag;
  if (ndiag < 1) {
    nzmax = 1;
  }
  i = I_d->size[0];
  I_d->size[0] = nzmax;
  emxEnsureCapacity_real_T(I_d, i);
  I_d_data = I_d->data;
  i = I_rowidx->size[0];
  I_rowidx->size[0] = nzmax;
  emxEnsureCapacity_int32_T(I_rowidx, i);
  I_rowidx_data = I_rowidx->data;
  i = I_colidx->size[0];
  I_colidx->size[0] = n + 1;
  emxEnsureCapacity_int32_T(I_colidx, i);
  I_colidx_data = I_colidx->data;
  for (i = 0; i < ndiag; i++) {
    I_d_data[i] = 1.0;
    I_rowidx_data[i] = i + 1;
  }
  I_colidx_data[0] = 1;
  for (c = 2; c <= ndiag; c++) {
    I_colidx_data[c - 1] = c;
  }
  i = ndiag + 1;
  b_i = n + 1;
  for (c = i; c <= b_i; c++) {
    I_colidx_data[c - 1] = ndiag + 1;
  }
  *I_m = m;
  *I_n = n;
  *I_maxnz = nzmax;
}

/*
 * File trailer for eyeLike.c
 *
 * [EOF]
 */
