/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: sortLE.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "sortLE.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : const emxArray_real_T *v
 *                const emxArray_int32_T *dir
 *                int idx1
 *                int idx2
 * Return Type  : bool
 */
bool sortLE(const emxArray_real_T *v, const emxArray_int32_T *dir, int idx1,
            int idx2)
{
  const double *v_data;
  const int *dir_data;
  int k;
  bool exitg1;
  bool p;
  dir_data = dir->data;
  v_data = v->data;
  p = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= dir->size[1] - 1)) {
    double v1;
    double v2;
    v1 = v_data[(idx1 + v->size[0] * (dir_data[k] - 1)) - 1];
    v2 = v_data[(idx2 + v->size[0] * (dir_data[k] - 1)) - 1];
    if ((v1 == v2) || (rtIsNaN(v1) && rtIsNaN(v2))) {
      k++;
    } else {
      if ((!(v1 <= v2)) && (!rtIsNaN(v2))) {
        p = false;
      }
      exitg1 = true;
    }
  }
  return p;
}

/*
 * File trailer for sortLE.c
 *
 * [EOF]
 */
