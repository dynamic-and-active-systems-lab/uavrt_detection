/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: validator_check_size.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "validator_check_size.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"

/* Function Definitions */
/*
 * Arguments    : const emxArray_struct_T *in
 *                emxArray_struct_T *out
 * Return Type  : void
 */
void b_validator_check_size(const emxArray_struct_T *in, emxArray_struct_T *out)
{
  const b_struct_T *in_data;
  b_struct_T *out_data;
  int i;
  int inVectorLength;
  in_data = in->data;
  inVectorLength = 1;
  if (in->size[1] != 1) {
    inVectorLength = in->size[1];
  }
  if (in->size[1] == 1) {
    i = out->size[0] * out->size[1];
    out->size[0] = 1;
    out->size[1] = inVectorLength;
    emxEnsureCapacity_struct_T(out, i);
    out_data = out->data;
    for (i = 0; i < inVectorLength; i++) {
      emxCopyStruct_struct_T(&out_data[i], &in_data[0]);
    }
  } else if (in->size[1] == 0) {
    i = out->size[0] * out->size[1];
    out->size[0] = 1;
    out->size[1] = inVectorLength;
    emxEnsureCapacity_struct_T(out, i);
    out_data = out->data;
    for (i = 0; i < inVectorLength; i++) {
      emxCopyStruct_struct_T(&out_data[i], &in_data[i]);
    }
  } else {
    i = out->size[0] * out->size[1];
    out->size[0] = 1;
    out->size[1] = inVectorLength;
    emxEnsureCapacity_struct_T(out, i);
    out_data = out->data;
    for (i = 0; i < inVectorLength; i++) {
      emxCopyStruct_struct_T(&out_data[i], &in_data[i]);
    }
  }
}

/*
 * Arguments    : emxArray_struct_T *in
 * Return Type  : void
 */
void c_validator_check_size(emxArray_struct_T *in)
{
  b_struct_T b_in;
  b_struct_T *in_data;
  int i;
  int i1;
  in_data = in->data;
  if ((in->size[0] == 1) && (in->size[1] == 1)) {
    int outsize_idx_0;
    int outsize_idx_1;
    outsize_idx_0 = in->size[0];
    outsize_idx_1 = in->size[1];
    emxInitStruct_struct_T(&b_in);
    emxCopyStruct_struct_T(&b_in, &in_data[0]);
    i = in->size[0] * in->size[1];
    in->size[0] = outsize_idx_0;
    in->size[1] = outsize_idx_1;
    emxEnsureCapacity_struct_T(in, i);
    in_data = in->data;
    for (i = 0; i < outsize_idx_1; i++) {
      for (i1 = 0; i1 < outsize_idx_0; i1++) {
        emxCopyStruct_struct_T(&in_data[i1 + in->size[0] * i], &b_in);
      }
    }
    emxFreeStruct_struct_T(&b_in);
  }
}

/*
 * Arguments    : emxArray_boolean_T *in
 * Return Type  : void
 */
void d_validator_check_size(emxArray_boolean_T *in)
{
  int i;
  int i1;
  bool *in_data;
  in_data = in->data;
  if ((in->size[0] == 1) && (in->size[1] == 1)) {
    int outsize_idx_0;
    int outsize_idx_1;
    bool b_in;
    outsize_idx_0 = in->size[0];
    outsize_idx_1 = in->size[1];
    b_in = in_data[0];
    i = in->size[0] * in->size[1];
    in->size[0] = outsize_idx_0;
    in->size[1] = outsize_idx_1;
    emxEnsureCapacity_boolean_T(in, i);
    in_data = in->data;
    for (i = 0; i < outsize_idx_1; i++) {
      for (i1 = 0; i1 < outsize_idx_0; i1++) {
        in_data[i1 + in->size[0] * i] = b_in;
      }
    }
  }
}

/*
 * Arguments    : emxArray_real_T *in
 * Return Type  : void
 */
void e_validator_check_size(emxArray_real_T *in)
{
  double *in_data;
  int i;
  in_data = in->data;
  if (in->size[0] == 1) {
    double b_in;
    int outsize_idx_0;
    outsize_idx_0 = in->size[0];
    b_in = in_data[0];
    i = in->size[0];
    in->size[0] = outsize_idx_0;
    emxEnsureCapacity_real_T(in, i);
    in_data = in->data;
    for (i = 0; i < outsize_idx_0; i++) {
      in_data[i] = b_in;
    }
  }
}

/*
 * Arguments    : const emxArray_real_T *in
 *                emxArray_real_T *out
 * Return Type  : void
 */
void validator_check_size(const emxArray_real_T *in, emxArray_real_T *out)
{
  const double *in_data;
  double *out_data;
  int i;
  int inVectorLength;
  in_data = in->data;
  inVectorLength = 1;
  if (in->size[0] != 1) {
    inVectorLength = in->size[0];
  }
  if (in->size[0] == 1) {
    i = out->size[0];
    out->size[0] = inVectorLength;
    emxEnsureCapacity_real_T(out, i);
    out_data = out->data;
    for (i = 0; i < inVectorLength; i++) {
      out_data[i] = in_data[0];
    }
  } else if (in->size[0] == 0) {
    i = out->size[0];
    out->size[0] = inVectorLength;
    emxEnsureCapacity_real_T(out, i);
    out_data = out->data;
    for (i = 0; i < inVectorLength; i++) {
      out_data[i] = in_data[i];
    }
  } else {
    i = out->size[0];
    out->size[0] = inVectorLength;
    emxEnsureCapacity_real_T(out, i);
    out_data = out->data;
    for (i = 0; i < inVectorLength; i++) {
      out_data[i] = in_data[i];
    }
  }
}

/*
 * File trailer for validator_check_size.c
 *
 * [EOF]
 */
