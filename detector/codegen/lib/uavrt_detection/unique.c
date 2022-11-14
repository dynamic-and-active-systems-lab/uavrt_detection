/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: unique.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "unique.h"
#include "rt_nonfinite.h"
#include "sortLE.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"

/* Function Definitions */
/*
 * Arguments    : const emxArray_real_T *a
 *                emxArray_real_T *b
 * Return Type  : void
 */
void unique_rows(const emxArray_real_T *a, emxArray_real_T *b)
{
  emxArray_int32_T *col;
  emxArray_int32_T *idx;
  emxArray_int32_T *iwork;
  emxArray_real_T *ycol;
  const double *a_data;
  double *b_data;
  double *ycol_data;
  int b_i;
  int i;
  int i1;
  int j;
  int k;
  int pEnd;
  int qEnd;
  int *idx_data;
  int *iwork_data;
  a_data = a->data;
  if (a->size[0] == 0) {
    b->size[0] = 0;
    b->size[1] = a->size[1];
  } else {
    int i2;
    int n;
    int p;
    i = b->size[0] * b->size[1];
    b->size[0] = a->size[0];
    b->size[1] = a->size[1];
    emxEnsureCapacity_real_T(b, i);
    b_data = b->data;
    pEnd = a->size[0] * a->size[1];
    for (i = 0; i < pEnd; i++) {
      b_data[i] = a_data[i];
    }
    n = a->size[1];
    emxInit_int32_T(&col, 2);
    i = col->size[0] * col->size[1];
    col->size[0] = 1;
    col->size[1] = a->size[1];
    emxEnsureCapacity_int32_T(col, i);
    idx_data = col->data;
    for (k = 0; k < n; k++) {
      idx_data[k] = k + 1;
    }
    n = a->size[0] + 1;
    emxInit_int32_T(&idx, 1);
    i = idx->size[0];
    idx->size[0] = a->size[0];
    emxEnsureCapacity_int32_T(idx, i);
    idx_data = idx->data;
    pEnd = a->size[0];
    for (i = 0; i < pEnd; i++) {
      idx_data[i] = 0;
    }
    if (a->size[1] == 0) {
      for (k = 0; k <= n - 2; k++) {
        idx_data[k] = k + 1;
      }
    } else {
      emxInit_int32_T(&iwork, 1);
      i = iwork->size[0];
      iwork->size[0] = a->size[0];
      emxEnsureCapacity_int32_T(iwork, i);
      iwork_data = iwork->data;
      i = a->size[0] - 1;
      for (k = 1; k <= i; k += 2) {
        if (sortLE(a, col, k, k + 1)) {
          idx_data[k - 1] = k;
          idx_data[k] = k + 1;
        } else {
          idx_data[k - 1] = k + 1;
          idx_data[k] = k;
        }
      }
      if ((a->size[0] & 1) != 0) {
        idx_data[a->size[0] - 1] = a->size[0];
      }
      b_i = 2;
      while (b_i < n - 1) {
        i2 = b_i << 1;
        j = 1;
        for (pEnd = b_i + 1; pEnd < n; pEnd = qEnd + b_i) {
          int kEnd;
          int q;
          p = j;
          q = pEnd;
          qEnd = j + i2;
          if (qEnd > n) {
            qEnd = n;
          }
          k = 0;
          kEnd = qEnd - j;
          while (k + 1 <= kEnd) {
            i = idx_data[q - 1];
            i1 = idx_data[p - 1];
            if (sortLE(a, col, i1, i)) {
              iwork_data[k] = i1;
              p++;
              if (p == pEnd) {
                while (q < qEnd) {
                  k++;
                  iwork_data[k] = idx_data[q - 1];
                  q++;
                }
              }
            } else {
              iwork_data[k] = i;
              q++;
              if (q == qEnd) {
                while (p < pEnd) {
                  k++;
                  iwork_data[k] = idx_data[p - 1];
                  p++;
                }
              }
            }
            k++;
          }
          for (k = 0; k < kEnd; k++) {
            idx_data[(j + k) - 1] = iwork_data[k];
          }
          j = qEnd;
        }
        b_i = i2;
      }
      emxFree_int32_T(&iwork);
    }
    emxFree_int32_T(&col);
    i2 = a->size[0] - 1;
    n = a->size[1];
    emxInit_real_T(&ycol, 1);
    i = ycol->size[0];
    ycol->size[0] = a->size[0];
    emxEnsureCapacity_real_T(ycol, i);
    ycol_data = ycol->data;
    for (j = 0; j < n; j++) {
      for (b_i = 0; b_i <= i2; b_i++) {
        ycol_data[b_i] = b_data[(idx_data[b_i] + b->size[0] * j) - 1];
      }
      for (b_i = 0; b_i <= i2; b_i++) {
        b_data[b_i + b->size[0] * j] = ycol_data[b_i];
      }
    }
    emxFree_real_T(&ycol);
    emxFree_int32_T(&idx);
    pEnd = -1;
    i2 = a->size[0];
    k = 0;
    while (k + 1 <= i2) {
      p = k;
      int exitg1;
      do {
        exitg1 = 0;
        k++;
        if (k + 1 > i2) {
          exitg1 = 1;
        } else {
          bool b_p;
          bool exitg2;
          b_p = false;
          j = 0;
          exitg2 = false;
          while ((!exitg2) && (j <= b->size[1] - 1)) {
            if (b_data[p + b->size[0] * j] != b_data[k + b->size[0] * j]) {
              b_p = true;
              exitg2 = true;
            } else {
              j++;
            }
          }
          if (b_p) {
            exitg1 = 1;
          }
        }
      } while (exitg1 == 0);
      pEnd++;
      i = b->size[1];
      for (j = 0; j < i; j++) {
        b_data[pEnd + b->size[0] * j] = b_data[p + b->size[0] * j];
      }
    }
    if (pEnd + 1 < 1) {
      pEnd = 0;
    } else {
      pEnd++;
    }
    i2 = b->size[1];
    for (i = 0; i < i2; i++) {
      for (i1 = 0; i1 < pEnd; i1++) {
        b_data[i1 + pEnd * i] = b_data[i1 + b->size[0] * i];
      }
    }
    i = b->size[0] * b->size[1];
    b->size[0] = pEnd;
    emxEnsureCapacity_real_T(b, i);
  }
}

/*
 * File trailer for unique.c
 *
 * [EOF]
 */
