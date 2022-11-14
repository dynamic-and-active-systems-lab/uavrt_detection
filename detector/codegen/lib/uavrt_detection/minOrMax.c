/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: minOrMax.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : const emxArray_real_T *x
 *                emxArray_real_T *ex
 *                emxArray_int32_T *idx
 * Return Type  : void
 */
void b_maximum(const emxArray_real_T *x, emxArray_real_T *ex,
               emxArray_int32_T *idx)
{
  const double *x_data;
  double *ex_data;
  int j;
  int loop_ub;
  int m;
  int n;
  int *idx_data;
  x_data = x->data;
  m = x->size[0] - 1;
  n = x->size[1];
  j = ex->size[0];
  ex->size[0] = x->size[0];
  emxEnsureCapacity_real_T(ex, j);
  ex_data = ex->data;
  j = idx->size[0];
  idx->size[0] = x->size[0];
  emxEnsureCapacity_int32_T(idx, j);
  idx_data = idx->data;
  loop_ub = x->size[0];
  for (j = 0; j < loop_ub; j++) {
    idx_data[j] = 1;
  }
  if (x->size[0] >= 1) {
    for (loop_ub = 0; loop_ub <= m; loop_ub++) {
      ex_data[loop_ub] = x_data[loop_ub];
    }
    for (j = 2; j <= n; j++) {
      for (loop_ub = 0; loop_ub <= m; loop_ub++) {
        double b;
        bool p;
        b = x_data[loop_ub + x->size[0] * (j - 1)];
        if (rtIsNaN(b)) {
          p = false;
        } else if (rtIsNaN(ex_data[loop_ub])) {
          p = true;
        } else {
          p = (ex_data[loop_ub] < b);
        }
        if (p) {
          ex_data[loop_ub] = b;
          idx_data[loop_ub] = j;
        }
      }
    }
  }
}

/*
 * Arguments    : const emxArray_real_T *x
 *                double *ex
 *                int *idx
 * Return Type  : void
 */
void c_maximum(const emxArray_real_T *x, double *ex, int *idx)
{
  const double *x_data;
  int k;
  int last;
  x_data = x->data;
  last = x->size[0];
  if (x->size[0] <= 2) {
    if (x->size[0] == 1) {
      *ex = x_data[0];
      *idx = 1;
    } else if ((x_data[0] < x_data[x->size[0] - 1]) ||
               (rtIsNaN(x_data[0]) && (!rtIsNaN(x_data[x->size[0] - 1])))) {
      *ex = x_data[x->size[0] - 1];
      *idx = x->size[0];
    } else {
      *ex = x_data[0];
      *idx = 1;
    }
  } else {
    if (!rtIsNaN(x_data[0])) {
      *idx = 1;
    } else {
      bool exitg1;
      *idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= last)) {
        if (!rtIsNaN(x_data[k - 1])) {
          *idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }
    if (*idx == 0) {
      *ex = x_data[0];
      *idx = 1;
    } else {
      int i;
      *ex = x_data[*idx - 1];
      i = *idx + 1;
      for (k = i; k <= last; k++) {
        double d;
        d = x_data[k - 1];
        if (*ex < d) {
          *ex = d;
          *idx = k;
        }
      }
    }
  }
}

/*
 * Arguments    : const double x[2]
 * Return Type  : double
 */
double d_maximum(const double x[2])
{
  double ex;
  if ((x[0] < x[1]) || (rtIsNaN(x[0]) && (!rtIsNaN(x[1])))) {
    ex = x[1];
  } else {
    ex = x[0];
  }
  return ex;
}

/*
 * Arguments    : const emxArray_real_T *x
 * Return Type  : double
 */
double maximum(const emxArray_real_T *x)
{
  const double *x_data;
  double ex;
  int k;
  int last;
  x_data = x->data;
  last = x->size[0];
  if (x->size[0] <= 2) {
    if (x->size[0] == 1) {
      ex = x_data[0];
    } else if ((x_data[0] < x_data[x->size[0] - 1]) ||
               (rtIsNaN(x_data[0]) && (!rtIsNaN(x_data[x->size[0] - 1])))) {
      ex = x_data[x->size[0] - 1];
    } else {
      ex = x_data[0];
    }
  } else {
    int idx;
    if (!rtIsNaN(x_data[0])) {
      idx = 1;
    } else {
      bool exitg1;
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= last)) {
        if (!rtIsNaN(x_data[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }
    if (idx == 0) {
      ex = x_data[0];
    } else {
      ex = x_data[idx - 1];
      idx++;
      for (k = idx; k <= last; k++) {
        double d;
        d = x_data[k - 1];
        if (ex < d) {
          ex = d;
        }
      }
    }
  }
  return ex;
}

/*
 * Arguments    : const double x[2]
 * Return Type  : double
 */
double minimum(const double x[2])
{
  double ex;
  if ((x[0] > x[1]) || (rtIsNaN(x[0]) && (!rtIsNaN(x[1])))) {
    ex = x[1];
  } else {
    ex = x[0];
  }
  return ex;
}

/*
 * File trailer for minOrMax.c
 *
 * [EOF]
 */
