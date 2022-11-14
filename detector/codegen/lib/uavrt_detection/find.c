/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: find.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "find.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"

/* Function Definitions */
/*
 * Arguments    : const emxArray_boolean_T *x
 *                emxArray_int32_T *i
 * Return Type  : void
 */
void b_eml_find(const emxArray_boolean_T *x, emxArray_int32_T *i)
{
  int idx;
  int ii;
  int nx;
  int *i_data;
  const bool *x_data;
  bool exitg1;
  x_data = x->data;
  nx = x->size[1];
  idx = 0;
  ii = i->size[0] * i->size[1];
  i->size[0] = 1;
  i->size[1] = x->size[1];
  emxEnsureCapacity_int32_T(i, ii);
  i_data = i->data;
  ii = 0;
  exitg1 = false;
  while ((!exitg1) && (ii <= nx - 1)) {
    if (x_data[ii]) {
      idx++;
      i_data[idx - 1] = ii + 1;
      if (idx >= nx) {
        exitg1 = true;
      } else {
        ii++;
      }
    } else {
      ii++;
    }
  }
  if (x->size[1] == 1) {
    if (idx == 0) {
      i->size[0] = 1;
      i->size[1] = 0;
    }
  } else {
    ii = i->size[0] * i->size[1];
    if (idx < 1) {
      i->size[1] = 0;
    } else {
      i->size[1] = idx;
    }
    emxEnsureCapacity_int32_T(i, ii);
  }
}

/*
 * Arguments    : const emxArray_boolean_T *x
 *                int i_data[]
 *                int *i_size
 * Return Type  : void
 */
void c_eml_find(const emxArray_boolean_T *x, int i_data[], int *i_size)
{
  int idx;
  int ii;
  const bool *x_data;
  bool exitg1;
  x_data = x->data;
  *i_size = (x->size[0] >= 1);
  idx = 0;
  ii = 0;
  exitg1 = false;
  while ((!exitg1) && (ii <= x->size[0] - 1)) {
    if (x_data[ii]) {
      idx = 1;
      i_data[0] = ii + 1;
      exitg1 = true;
    } else {
      ii++;
    }
  }
  if (*i_size == 1) {
    if (idx == 0) {
      *i_size = 0;
    }
  } else {
    *i_size = (idx >= 1);
  }
}

/*
 * Arguments    : const emxArray_boolean_T *x
 *                int i_data[]
 *                int *i_size
 * Return Type  : void
 */
void d_eml_find(const emxArray_boolean_T *x, int i_data[], int *i_size)
{
  int idx;
  int ii;
  const bool *x_data;
  bool exitg1;
  x_data = x->data;
  *i_size = (x->size[0] >= 1);
  ii = x->size[0];
  idx = 0;
  exitg1 = false;
  while ((!exitg1) && (ii > 0)) {
    if (x_data[ii - 1]) {
      idx = 1;
      i_data[0] = ii;
      exitg1 = true;
    } else {
      ii--;
    }
  }
  if (*i_size == 1) {
    if (idx == 0) {
      *i_size = 0;
    }
  } else {
    *i_size = (idx >= 1);
  }
}

/*
 * Arguments    : const emxArray_int32_T *x_colidx
 *                const emxArray_int32_T *x_rowidx
 *                emxArray_int32_T *i
 *                emxArray_int32_T *j
 * Return Type  : void
 */
void e_eml_find(const emxArray_int32_T *x_colidx,
                const emxArray_int32_T *x_rowidx, emxArray_int32_T *i,
                emxArray_int32_T *j)
{
  const int *x_colidx_data;
  const int *x_rowidx_data;
  int idx;
  int nx;
  int *i_data;
  int *j_data;
  x_rowidx_data = x_rowidx->data;
  x_colidx_data = x_colidx->data;
  nx = x_colidx_data[x_colidx->size[0] - 1] - 1;
  if (x_colidx_data[x_colidx->size[0] - 1] - 1 == 0) {
    i->size[0] = 0;
    j->size[0] = 0;
  } else {
    int col;
    col = i->size[0];
    i->size[0] = x_colidx_data[x_colidx->size[0] - 1] - 1;
    emxEnsureCapacity_int32_T(i, col);
    i_data = i->data;
    col = j->size[0];
    j->size[0] = x_colidx_data[x_colidx->size[0] - 1] - 1;
    emxEnsureCapacity_int32_T(j, col);
    j_data = j->data;
    for (idx = 0; idx < nx; idx++) {
      i_data[idx] = x_rowidx_data[idx];
    }
    idx = 0;
    col = 1;
    while (idx < nx) {
      if (idx == x_colidx_data[col] - 1) {
        col++;
      } else {
        idx++;
        j_data[idx - 1] = col;
      }
    }
    if (x_colidx_data[x_colidx->size[0] - 1] - 1 == 1) {
      if (idx == 0) {
        i->size[0] = 0;
        j->size[0] = 0;
      }
    } else {
      col = i->size[0];
      if (idx < 1) {
        i->size[0] = 0;
      } else {
        i->size[0] = idx;
      }
      emxEnsureCapacity_int32_T(i, col);
      col = j->size[0];
      if (idx < 1) {
        j->size[0] = 0;
      } else {
        j->size[0] = idx;
      }
      emxEnsureCapacity_int32_T(j, col);
    }
  }
}

/*
 * Arguments    : const emxArray_boolean_T *x
 *                int i_data[]
 *                int i_size[2]
 * Return Type  : void
 */
void eml_find(const emxArray_boolean_T *x, int i_data[], int i_size[2])
{
  emxArray_int32_T *i;
  int idx;
  int ii;
  int k;
  int *b_i_data;
  const bool *x_data;
  bool exitg1;
  x_data = x->data;
  k = (x->size[1] >= 1);
  idx = 0;
  emxInit_int32_T(&i, 2);
  ii = i->size[0] * i->size[1];
  i->size[0] = 1;
  i->size[1] = k;
  emxEnsureCapacity_int32_T(i, ii);
  b_i_data = i->data;
  ii = 0;
  exitg1 = false;
  while ((!exitg1) && (ii <= x->size[1] - 1)) {
    if (x_data[ii]) {
      idx++;
      b_i_data[idx - 1] = ii + 1;
      if (idx >= k) {
        exitg1 = true;
      } else {
        ii++;
      }
    } else {
      ii++;
    }
  }
  if (k == 1) {
    if (idx == 0) {
      i->size[0] = 1;
      i->size[1] = 0;
    }
  } else {
    ii = i->size[0] * i->size[1];
    i->size[1] = (idx >= 1);
    emxEnsureCapacity_int32_T(i, ii);
    b_i_data = i->data;
  }
  i_size[0] = 1;
  i_size[1] = i->size[1];
  ii = i->size[1];
  if (ii - 1 >= 0) {
    i_data[0] = b_i_data[0];
  }
  emxFree_int32_T(&i);
}

/*
 * Arguments    : int in1_data[]
 *                int *in1_size
 *                const emxArray_real_T *in2
 *                int in3
 *                int in4
 *                const waveform *in5
 *                int in6
 *                int in7
 * Return Type  : void
 */
void i_binary_expand_op(int in1_data[], int *in1_size,
                        const emxArray_real_T *in2, int in3, int in4,
                        const waveform *in5, int in6, int in7)
{
  emxArray_boolean_T *b_in2;
  const double *in2_data;
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  bool *b_in2_data;
  in2_data = in2->data;
  emxInit_boolean_T(&b_in2, 1);
  i = b_in2->size[0];
  if ((in7 - in6) + 1 == 1) {
    b_in2->size[0] = (in4 - in3) + 1;
  } else {
    b_in2->size[0] = (in7 - in6) + 1;
  }
  emxEnsureCapacity_boolean_T(b_in2, i);
  b_in2_data = b_in2->data;
  stride_0_0 = ((in4 - in3) + 1 != 1);
  stride_1_0 = ((in7 - in6) + 1 != 1);
  if ((in7 - in6) + 1 == 1) {
    loop_ub = (in4 - in3) + 1;
  } else {
    loop_ub = (in7 - in6) + 1;
  }
  for (i = 0; i < loop_ub; i++) {
    b_in2_data[i] = (in2_data[in3 + i * stride_0_0] <
                     in5->thresh.threshVecFine->data[in6 + i * stride_1_0]);
  }
  c_eml_find(b_in2, in1_data, in1_size);
  emxFree_boolean_T(&b_in2);
}

/*
 * Arguments    : int in1_data[]
 *                int *in1_size
 *                const emxArray_real_T *in2
 *                int in3
 *                int in4
 *                int in5
 *                const waveform *in6
 *                int in7
 *                int in8
 *                int in9
 * Return Type  : void
 */
void j_binary_expand_op(int in1_data[], int *in1_size,
                        const emxArray_real_T *in2, int in3, int in4, int in5,
                        const waveform *in6, int in7, int in8, int in9)
{
  emxArray_boolean_T *b_in2;
  const double *in2_data;
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  bool *b_in2_data;
  in2_data = in2->data;
  emxInit_boolean_T(&b_in2, 1);
  i = b_in2->size[0];
  if (div_s32(in9 - in7, in8) + 1 == 1) {
    b_in2->size[0] = div_s32(in5 - in3, in4) + 1;
  } else {
    b_in2->size[0] = div_s32(in9 - in7, in8) + 1;
  }
  emxEnsureCapacity_boolean_T(b_in2, i);
  b_in2_data = b_in2->data;
  stride_0_0 = (div_s32(in5 - in3, in4) + 1 != 1);
  stride_1_0 = (div_s32(in9 - in7, in8) + 1 != 1);
  if (div_s32(in9 - in7, in8) + 1 == 1) {
    loop_ub = div_s32(in5 - in3, in4) + 1;
  } else {
    loop_ub = div_s32(in9 - in7, in8) + 1;
  }
  for (i = 0; i < loop_ub; i++) {
    b_in2_data[i] =
        (in2_data[in3 + in4 * (i * stride_0_0)] <
         in6->thresh.threshVecFine->data[in7 + in8 * (i * stride_1_0)]);
  }
  c_eml_find(b_in2, in1_data, in1_size);
  emxFree_boolean_T(&b_in2);
}

/*
 * File trailer for find.c
 *
 * [EOF]
 */
