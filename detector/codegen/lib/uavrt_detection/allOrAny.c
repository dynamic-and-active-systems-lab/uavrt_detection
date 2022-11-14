/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: allOrAny.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "allOrAny.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"

/* Function Definitions */
/*
 * Arguments    : const emxArray_boolean_T *x
 * Return Type  : bool
 */
bool allOrAny_anonFcn1(const emxArray_boolean_T *x)
{
  int ix;
  const bool *x_data;
  bool exitg1;
  bool varargout_1;
  x_data = x->data;
  varargout_1 = false;
  ix = 1;
  exitg1 = false;
  while ((!exitg1) && (ix <= x->size[0])) {
    if (x_data[ix - 1]) {
      varargout_1 = true;
      exitg1 = true;
    } else {
      ix++;
    }
  }
  return varargout_1;
}

/*
 * File trailer for allOrAny.c
 *
 * [EOF]
 */
