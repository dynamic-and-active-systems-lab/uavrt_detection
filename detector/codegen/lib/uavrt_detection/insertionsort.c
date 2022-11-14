/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: insertionsort.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "insertionsort.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"

/* Function Definitions */
/*
 * Arguments    : emxArray_int32_T *x
 *                int xstart
 *                int xend
 *                const emxArray_int32_T *cmp_workspace_x
 * Return Type  : void
 */
void b_insertionsort(emxArray_int32_T *x, int xstart, int xend,
                     const emxArray_int32_T *cmp_workspace_x)
{
  const int *cmp_workspace_x_data;
  int i;
  int k;
  int *x_data;
  cmp_workspace_x_data = cmp_workspace_x->data;
  x_data = x->data;
  i = xstart + 1;
  for (k = i; k <= xend; k++) {
    int idx;
    int xc;
    xc = x_data[k - 1];
    idx = k - 1;
    while ((idx >= xstart) && (cmp_workspace_x_data[xc - 1] <
                               cmp_workspace_x_data[x_data[idx - 1] - 1])) {
      x_data[idx] = x_data[idx - 1];
      idx--;
    }
    x_data[idx] = xc;
  }
}

/*
 * Arguments    : emxArray_int32_T *x
 *                int xstart
 *                int xend
 *                const emxArray_int32_T *cmp_workspace_a
 *                const emxArray_int32_T *cmp_workspace_b
 * Return Type  : void
 */
void insertionsort(emxArray_int32_T *x, int xstart, int xend,
                   const emxArray_int32_T *cmp_workspace_a,
                   const emxArray_int32_T *cmp_workspace_b)
{
  const int *cmp_workspace_a_data;
  const int *cmp_workspace_b_data;
  int i;
  int k;
  int *x_data;
  cmp_workspace_b_data = cmp_workspace_b->data;
  cmp_workspace_a_data = cmp_workspace_a->data;
  x_data = x->data;
  i = xstart + 1;
  for (k = i; k <= xend; k++) {
    int idx;
    int xc;
    bool exitg1;
    xc = x_data[k - 1] - 1;
    idx = k - 2;
    exitg1 = false;
    while ((!exitg1) && (idx + 1 >= xstart)) {
      bool varargout_1;
      if (cmp_workspace_a_data[xc] < cmp_workspace_a_data[x_data[idx] - 1]) {
        varargout_1 = true;
      } else if (cmp_workspace_a_data[xc] ==
                 cmp_workspace_a_data[x_data[idx] - 1]) {
        varargout_1 =
            (cmp_workspace_b_data[xc] < cmp_workspace_b_data[x_data[idx] - 1]);
      } else {
        varargout_1 = false;
      }
      if (varargout_1) {
        x_data[idx + 1] = x_data[idx];
        idx--;
      } else {
        exitg1 = true;
      }
    }
    x_data[idx + 1] = xc + 1;
  }
}

/*
 * File trailer for insertionsort.c
 *
 * [EOF]
 */
