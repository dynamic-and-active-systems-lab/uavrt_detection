/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: not.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "not.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"

/* Function Definitions */
/*
 * Arguments    : const emxArray_int32_T *S_colidx
 *                const emxArray_int32_T *S_rowidx
 *                int S_n
 *                emxArray_boolean_T *out_d
 *                emxArray_int32_T *out_colidx
 *                emxArray_int32_T *out_rowidx
 *                int *out_n
 * Return Type  : void
 */
void sparse_not(const emxArray_int32_T *S_colidx,
                const emxArray_int32_T *S_rowidx, int S_n,
                emxArray_boolean_T *out_d, emxArray_int32_T *out_colidx,
                emxArray_int32_T *out_rowidx, int *out_n)
{
  const int *S_colidx_data;
  const int *S_rowidx_data;
  int c;
  int curPosition;
  int larger;
  int writeRow;
  int writeStart;
  int *out_colidx_data;
  int *out_rowidx_data;
  bool *out_d_data;
  S_rowidx_data = S_rowidx->data;
  S_colidx_data = S_colidx->data;
  if (S_n < 1) {
    larger = 0;
  } else {
    larger = (S_n - S_colidx_data[S_colidx->size[0] - 1]) + 1;
    if (larger == 0) {
      larger = 0;
    }
  }
  writeStart = larger;
  if (larger < 1) {
    writeStart = 1;
  }
  writeRow = out_d->size[0];
  out_d->size[0] = writeStart;
  emxEnsureCapacity_boolean_T(out_d, writeRow);
  out_d_data = out_d->data;
  writeRow = out_rowidx->size[0];
  out_rowidx->size[0] = writeStart;
  emxEnsureCapacity_int32_T(out_rowidx, writeRow);
  out_rowidx_data = out_rowidx->data;
  writeRow = out_colidx->size[0];
  out_colidx->size[0] = S_n + 1;
  emxEnsureCapacity_int32_T(out_colidx, writeRow);
  out_colidx_data = out_colidx->data;
  if (larger < 1) {
    larger = 0;
  }
  for (writeRow = 0; writeRow < larger; writeRow++) {
    out_d_data[writeRow] = true;
  }
  curPosition = 1;
  for (c = 0; c < S_n; c++) {
    out_colidx_data[c] = curPosition;
    writeRow = S_colidx_data[c + 1];
    if (S_colidx_data[c] == writeRow) {
      out_rowidx_data[curPosition - 1] = 1;
      curPosition++;
    } else {
      larger = S_rowidx_data[writeRow - 2];
      writeStart = larger + 1;
      for (writeRow = writeStart; writeRow < 2; writeRow++) {
        out_rowidx_data[((curPosition + writeRow) - larger) - 2] = 1;
      }
      curPosition = (curPosition - larger) + 1;
    }
  }
  out_colidx_data[S_n] = curPosition;
  *out_n = S_n;
}

/*
 * File trailer for not.c
 *
 * [EOF]
 */
