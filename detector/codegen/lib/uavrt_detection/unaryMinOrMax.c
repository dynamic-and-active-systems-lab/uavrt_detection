/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: unaryMinOrMax.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "unaryMinOrMax.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : const emxArray_real_T *x
 * Return Type  : double
 */
double unaryMinOrMax_anonFcn1(const emxArray_real_T *x)
{
  const double *x_data;
  double varargout_1;
  int k;
  int last;
  x_data = x->data;
  last = x->size[0];
  if (x->size[0] <= 2) {
    if (x->size[0] == 1) {
      varargout_1 = x_data[0];
    } else if ((x_data[0] > x_data[x->size[0] - 1]) ||
               (rtIsNaN(x_data[0]) && (!rtIsNaN(x_data[x->size[0] - 1])))) {
      varargout_1 = x_data[x->size[0] - 1];
    } else {
      varargout_1 = x_data[0];
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
      varargout_1 = x_data[0];
    } else {
      varargout_1 = x_data[idx - 1];
      idx++;
      for (k = idx; k <= last; k++) {
        double d;
        d = x_data[k - 1];
        if (varargout_1 > d) {
          varargout_1 = d;
        }
      }
    }
  }
  return varargout_1;
}

/*
 * File trailer for unaryMinOrMax.c
 *
 * [EOF]
 */
