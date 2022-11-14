/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: weightingmatrix.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "weightingmatrix.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"

/* Function Definitions */
/*
 * Arguments    : emxArray_creal_T *in1
 *                const emxArray_creal_T *in2
 *                int in3
 *                const emxArray_real_T *in4
 * Return Type  : void
 */
void c_binary_expand_op(emxArray_creal_T *in1, const emxArray_creal_T *in2,
                        int in3, const emxArray_real_T *in4)
{
  const creal_T *in2_data;
  creal_T *in1_data;
  const double *in4_data;
  int i;
  int in2_idx_0;
  int stride_0_0;
  int stride_1_0;
  in4_data = in4->data;
  in2_data = in2->data;
  in2_idx_0 = in2->size[0];
  i = in1->size[0] * in1->size[1];
  if (in4->size[0] == 1) {
    in1->size[0] = in2_idx_0;
  } else {
    in1->size[0] = in4->size[0];
  }
  in1->size[1] = 1;
  emxEnsureCapacity_creal_T(in1, i);
  in1_data = in1->data;
  stride_0_0 = (in2_idx_0 != 1);
  stride_1_0 = (in4->size[0] != 1);
  if (in4->size[0] != 1) {
    in2_idx_0 = in4->size[0];
  }
  for (i = 0; i < in2_idx_0; i++) {
    double d;
    int i1;
    i1 = i * stride_0_0;
    d = in4_data[i * stride_1_0];
    in1_data[i].re = d * in2_data[i1 + in2->size[0] * in3].re;
    in1_data[i].im = d * in2_data[i1 + in2->size[0] * in3].im;
  }
}

/*
 * File trailer for weightingmatrix.c
 *
 * [EOF]
 */
