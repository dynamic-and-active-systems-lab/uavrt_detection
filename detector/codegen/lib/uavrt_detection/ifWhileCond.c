/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: ifWhileCond.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "ifWhileCond.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"

/* Function Definitions */
/*
 * Arguments    : const emxArray_boolean_T *x
 * Return Type  : bool
 */
bool b_ifWhileCond(const emxArray_boolean_T *x)
{
  const bool *x_data;
  bool y;
  x_data = x->data;
  y = ((x->size[0] != 0) && (x->size[1] != 0));
  if (y) {
    int i;
    int k;
    bool exitg1;
    i = x->size[0] * x->size[1];
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k <= i - 1)) {
      if (!x_data[k]) {
        y = false;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }
  return y;
}

/*
 * Arguments    : const emxArray_boolean_T *x
 * Return Type  : bool
 */
bool ifWhileCond(const emxArray_boolean_T *x)
{
  const bool *x_data;
  bool y;
  x_data = x->data;
  y = (x->size[0] != 0);
  if (y) {
    int k;
    bool exitg1;
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k <= x->size[0] - 1)) {
      if (!x_data[k]) {
        y = false;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }
  return y;
}

/*
 * File trailer for ifWhileCond.c
 *
 * [EOF]
 */
