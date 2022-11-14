/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: linspace.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "linspace.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include <math.h>

/* Function Definitions */
/*
 * Arguments    : double d2
 *                double n
 *                emxArray_real_T *y
 * Return Type  : void
 */
void linspace(double d2, double n, emxArray_real_T *y)
{
  double *y_data;
  int k;
  if (!(n >= 0.0)) {
    y->size[0] = 1;
    y->size[1] = 0;
  } else {
    double delta1;
    int i;
    delta1 = floor(n);
    i = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = (int)delta1;
    emxEnsureCapacity_real_T(y, i);
    y_data = y->data;
    if ((int)delta1 >= 1) {
      y_data[(int)delta1 - 1] = d2;
      if (y->size[1] >= 2) {
        y_data[0] = 0.0;
        if (y->size[1] >= 3) {
          if (-d2 == 0.0) {
            delta1 = d2 / ((double)y->size[1] - 1.0);
            i = y->size[1] - 1;
            for (k = 2; k <= i; k++) {
              y_data[k - 1] = (double)(((k << 1) - y->size[1]) - 1) * delta1;
            }
            if ((y->size[1] & 1) == 1) {
              y_data[y->size[1] >> 1] = 0.0;
            }
          } else if ((d2 < 0.0) && (fabs(d2) > 8.9884656743115785E+307)) {
            delta1 = d2 / ((double)y->size[1] - 1.0);
            i = y->size[1];
            for (k = 0; k <= i - 3; k++) {
              y_data[k + 1] = delta1 * ((double)k + 1.0);
            }
          } else {
            delta1 = d2 / ((double)y->size[1] - 1.0);
            i = y->size[1];
            for (k = 0; k <= i - 3; k++) {
              y_data[k + 1] = ((double)k + 1.0) * delta1;
            }
          }
        }
      }
    }
  }
}

/*
 * File trailer for linspace.c
 *
 * [EOF]
 */
