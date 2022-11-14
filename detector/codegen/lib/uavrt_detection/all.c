/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: all.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "all.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"

/* Function Definitions */
/*
 * Arguments    : const emxArray_boolean_T *x
 *                emxArray_boolean_T *y
 * Return Type  : void
 */
void all(const emxArray_boolean_T *x, emxArray_boolean_T *y)
{
  int i1;
  int i2;
  int j;
  int vstride;
  const bool *x_data;
  bool *y_data;
  x_data = x->data;
  i2 = y->size[0];
  y->size[0] = x->size[0];
  emxEnsureCapacity_boolean_T(y, i2);
  y_data = y->data;
  vstride = x->size[0];
  for (i2 = 0; i2 < vstride; i2++) {
    y_data[i2] = true;
  }
  vstride = x->size[0];
  i2 = (x->size[1] - 1) * x->size[0];
  i1 = 0;
  for (j = 0; j < vstride; j++) {
    int ix;
    bool exitg1;
    i1++;
    i2++;
    ix = i1;
    exitg1 = false;
    while ((!exitg1) && ((vstride > 0) && (ix <= i2))) {
      if (!x_data[ix - 1]) {
        y_data[j] = false;
        exitg1 = true;
      } else {
        ix += vstride;
      }
    }
  }
}

/*
 * File trailer for all.c
 *
 * [EOF]
 */
