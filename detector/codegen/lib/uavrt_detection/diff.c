/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: diff.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "diff.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"

/* Function Definitions */
/*
 * Arguments    : const emxArray_real_T *x
 *                emxArray_real_T *y
 * Return Type  : void
 */
void diff(const emxArray_real_T *x, emxArray_real_T *y)
{
  const double *x_data;
  double *y_data;
  int dimSize;
  int u0;
  x_data = x->data;
  dimSize = x->size[0];
  if (x->size[0] == 0) {
    y->size[0] = 0;
  } else {
    u0 = x->size[0] - 1;
    if (u0 > 1) {
      u0 = 1;
    }
    if (u0 < 1) {
      y->size[0] = 0;
    } else {
      u0 = y->size[0];
      y->size[0] = x->size[0] - 1;
      emxEnsureCapacity_real_T(y, u0);
      y_data = y->data;
      if (x->size[0] - 1 != 0) {
        double work_data;
        work_data = x_data[0];
        for (u0 = 2; u0 <= dimSize; u0++) {
          double tmp2;
          tmp2 = work_data;
          work_data = x_data[u0 - 1];
          y_data[u0 - 2] = work_data - tmp2;
        }
      }
    }
  }
}

/*
 * File trailer for diff.c
 *
 * [EOF]
 */
