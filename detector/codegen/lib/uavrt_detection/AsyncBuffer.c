/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: AsyncBuffer.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "AsyncBuffer.h"
#include "AsyncBuffercgHelper.h"
#include "colon.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_internal_types.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"

/* Function Definitions */
/*
 * Arguments    : b_dsp_AsyncBuffer *obj
 * Return Type  : void
 */
void AsyncBuffer_read(b_dsp_AsyncBuffer *obj)
{
  emxArray_creal32_T *out;
  int b_qY;
  int q0_tmp;
  int q1_tmp;
  int qY;
  q0_tmp = obj->pBuffer.WritePointer;
  q1_tmp = obj->pBuffer.ReadPointer;
  if ((q0_tmp >= 0) && (q1_tmp < q0_tmp - MAX_int32_T)) {
    qY = MAX_int32_T;
  } else if ((q0_tmp < 0) && (q1_tmp > q0_tmp - MIN_int32_T)) {
    qY = MIN_int32_T;
  } else {
    qY = q0_tmp - q1_tmp;
  }
  if (qY < -2147483647) {
    qY = MIN_int32_T;
  } else {
    qY--;
  }
  if (q1_tmp < -2146882997) {
    b_qY = MAX_int32_T;
  } else {
    b_qY = 600650 - q1_tmp;
  }
  if ((b_qY < 0) && (q0_tmp < MIN_int32_T - b_qY)) {
    b_qY = MIN_int32_T;
  } else if ((b_qY > 0) && (q0_tmp > MAX_int32_T - b_qY)) {
    b_qY = MAX_int32_T;
  } else {
    b_qY += q0_tmp;
  }
  emxInit_creal32_T(&out, 1);
  if (obj->pBuffer.ReadPointer < obj->pBuffer.WritePointer) {
    b_qY = qY;
  } else if (obj->pBuffer.ReadPointer == obj->pBuffer.WritePointer) {
    b_qY = 600650;
  }
  AsyncBuffercgHelper_read(&obj->pBuffer, b_qY, out, &q1_tmp);
  emxFree_creal32_T(&out);
}

/*
 * Arguments    : dsp_AsyncBuffer *obj
 * Return Type  : void
 */
void AsyncBuffer_release(dsp_AsyncBuffer *obj)
{
  if (obj->pBuffer.isInitialized == 1) {
    obj->pBuffer.isInitialized = 2;
    if (obj->pBuffer.isSetupComplete) {
      obj->pBuffer.ReadPointer = 1;
      obj->pBuffer.WritePointer = 2;
      obj->pBuffer.CumulativeOverrun = 0;
      obj->pBuffer.CumulativeUnderrun = 0;
      obj->pBuffer.c_AsyncBuffercgHelper_isInitial = false;
      obj->pBuffer.NumChannels = -1;
    }
  }
}

/*
 * Arguments    : b_dsp_AsyncBuffer *obj
 * Return Type  : void
 */
void AsyncBuffer_write(b_dsp_AsyncBuffer *obj)
{
  d_dsp_internal_AsyncBuffercgHel *b_obj;
  emxArray_int32_T *r;
  emxArray_int32_T *y;
  int i;
  int k;
  int overrun;
  int qY;
  int rPtr;
  int wPtr;
  int *r1;
  int *y_data;
  bool exitg1;
  b_obj = &obj->pBuffer;
  if (obj->pBuffer.isInitialized != 1) {
    cell_wrap_2 varSizes;
    obj->pBuffer.isSetupComplete = false;
    obj->pBuffer.isInitialized = 1;
    for (k = 0; k < 8; k++) {
      varSizes.f1[k] = 1U;
    }
    obj->pBuffer.inputVarSize[0] = varSizes;
    obj->pBuffer.NumChannels = 1;
    obj->pBuffer.c_AsyncBuffercgHelper_isInitial = true;
    for (i = 0; i < 600651; i++) {
      obj->pBuffer.Cache[i].re = 0.0F;
      obj->pBuffer.Cache[i].im = 0.0F;
    }
    obj->pBuffer.isSetupComplete = true;
    obj->pBuffer.ReadPointer = 1;
    obj->pBuffer.WritePointer = 2;
    obj->pBuffer.CumulativeOverrun = 0;
    obj->pBuffer.CumulativeUnderrun = 0;
    for (i = 0; i < 600651; i++) {
      obj->pBuffer.Cache[i].re = 0.0F;
      obj->pBuffer.Cache[i].im = 0.0F;
    }
  }
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 8)) {
    if (b_obj->inputVarSize[0].f1[k] != 1U) {
      for (k = 0; k < 8; k++) {
        b_obj->inputVarSize[0].f1[k] = 1U;
      }
      exitg1 = true;
    } else {
      k++;
    }
  }
  b_obj = &obj->pBuffer;
  wPtr = obj->pBuffer.WritePointer;
  rPtr = obj->pBuffer.ReadPointer;
  overrun = 0;
  if (wPtr > 2147483646) {
    qY = MAX_int32_T;
  } else {
    qY = wPtr + 1;
  }
  if ((wPtr <= rPtr) && (rPtr <= qY - 1)) {
    if ((qY - 1 >= 0) && (rPtr < qY + MIN_int32_T)) {
      i = MAX_int32_T;
    } else if ((qY - 1 < 0) && (rPtr > qY + MAX_int32_T)) {
      i = MIN_int32_T;
    } else {
      i = (qY - rPtr) - 1;
    }
    if (i > 2147483646) {
      overrun = MAX_int32_T;
    } else {
      overrun = i + 1;
    }
  }
  if (qY - 1 < wPtr) {
    i = 0;
  } else {
    i = qY - wPtr;
  }
  emxInit_int32_T(&y, 2);
  k = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = i;
  emxEnsureCapacity_int32_T(y, k);
  y_data = y->data;
  if (i > 0) {
    y_data[0] = wPtr;
    for (k = 2; k <= i; k++) {
      wPtr++;
      y_data[k - 1] = wPtr;
    }
  }
  emxInit_int32_T(&r, 1);
  k = r->size[0];
  r->size[0] = y->size[1];
  emxEnsureCapacity_int32_T(r, k);
  r1 = r->data;
  i = y->size[1];
  for (k = 0; k < i; k++) {
    r1[k] = y_data[k];
  }
  emxFree_int32_T(&y);
  i = r->size[0];
  for (k = 0; k < i; k++) {
    b_obj->Cache[r1[k] - 1].re = 1.0F;
    b_obj->Cache[r1[k] - 1].im = 1.0F;
  }
  emxFree_int32_T(&r);
  if (qY > 600651) {
    wPtr = 1;
  } else {
    wPtr = qY;
  }
  if (overrun != 0) {
    rPtr = wPtr;
  }
  i = obj->pBuffer.CumulativeOverrun;
  if ((i < 0) && (overrun < MIN_int32_T - i)) {
    qY = MIN_int32_T;
  } else if ((i > 0) && (overrun > MAX_int32_T - i)) {
    qY = MAX_int32_T;
  } else {
    qY = i + overrun;
  }
  obj->pBuffer.CumulativeOverrun = qY;
  obj->pBuffer.WritePointer = wPtr;
  obj->pBuffer.ReadPointer = rPtr;
}

/*
 * Arguments    : b_dsp_AsyncBuffer *obj
 *                emxArray_creal32_T *out
 * Return Type  : void
 */
void b_AsyncBuffer_read(b_dsp_AsyncBuffer *obj, emxArray_creal32_T *out)
{
  int b_qY;
  int q0_tmp;
  int q1_tmp;
  int qY;
  q0_tmp = obj->pBuffer.WritePointer;
  q1_tmp = obj->pBuffer.ReadPointer;
  if ((q0_tmp >= 0) && (q1_tmp < q0_tmp - MAX_int32_T)) {
    qY = MAX_int32_T;
  } else if ((q0_tmp < 0) && (q1_tmp > q0_tmp - MIN_int32_T)) {
    qY = MIN_int32_T;
  } else {
    qY = q0_tmp - q1_tmp;
  }
  if (qY < -2147483647) {
    qY = MIN_int32_T;
  } else {
    qY--;
  }
  if (q1_tmp < -2146882997) {
    b_qY = MAX_int32_T;
  } else {
    b_qY = 600650 - q1_tmp;
  }
  if ((b_qY < 0) && (q0_tmp < MIN_int32_T - b_qY)) {
    b_qY = MIN_int32_T;
  } else if ((b_qY > 0) && (q0_tmp > MAX_int32_T - b_qY)) {
    b_qY = MAX_int32_T;
  } else {
    b_qY += q0_tmp;
  }
  if (obj->pBuffer.ReadPointer < obj->pBuffer.WritePointer) {
    b_qY = qY;
  } else if (obj->pBuffer.ReadPointer == obj->pBuffer.WritePointer) {
    b_qY = 600650;
  }
  AsyncBuffercgHelper_read(&obj->pBuffer, b_qY, out, &q1_tmp);
}

/*
 * Arguments    : c_dsp_AsyncBuffer *obj
 * Return Type  : void
 */
void b_AsyncBuffer_release(c_dsp_AsyncBuffer *obj)
{
  if (obj->pBuffer.isInitialized == 1) {
    obj->pBuffer.isInitialized = 2;
    if (obj->pBuffer.isSetupComplete) {
      obj->pBuffer.ReadPointer = 1;
      obj->pBuffer.WritePointer = 2;
      obj->pBuffer.CumulativeOverrun = 0;
      obj->pBuffer.CumulativeUnderrun = 0;
      obj->pBuffer.c_AsyncBuffercgHelper_isInitial = false;
      obj->pBuffer.NumChannels = -1;
    }
  }
}

/*
 * Arguments    : dsp_AsyncBuffer *obj
 *                const creal32_T in_data[]
 *                int in_size
 * Return Type  : void
 */
void b_AsyncBuffer_write(dsp_AsyncBuffer *obj, const creal32_T in_data[],
                         int in_size)
{
  c_dsp_internal_AsyncBuffercgHel *b_obj;
  int i;
  short inSize[8];
  bool exitg1;
  b_obj = &obj->pBuffer;
  if (obj->pBuffer.isInitialized != 1) {
    cell_wrap_2 varSizes;
    obj->pBuffer.isSetupComplete = false;
    obj->pBuffer.isInitialized = 1;
    varSizes.f1[0] = (unsigned int)in_size;
    varSizes.f1[1] = 1U;
    for (i = 0; i < 6; i++) {
      varSizes.f1[i + 2] = 1U;
    }
    obj->pBuffer.inputVarSize[0] = varSizes;
    obj->pBuffer.NumChannels = 1;
    obj->pBuffer.c_AsyncBuffercgHelper_isInitial = true;
    for (i = 0; i < 5800321; i++) {
      obj->pBuffer.Cache[i].re = 0.0F;
      obj->pBuffer.Cache[i].im = 0.0F;
    }
    obj->pBuffer.isSetupComplete = true;
    obj->pBuffer.ReadPointer = 1;
    obj->pBuffer.WritePointer = 2;
    obj->pBuffer.CumulativeOverrun = 0;
    obj->pBuffer.CumulativeUnderrun = 0;
    for (i = 0; i < 5800321; i++) {
      obj->pBuffer.Cache[i].re = 0.0F;
      obj->pBuffer.Cache[i].im = 0.0F;
    }
  }
  inSize[0] = (short)in_size;
  inSize[1] = 1;
  for (i = 0; i < 6; i++) {
    inSize[i + 2] = 1;
  }
  i = 0;
  exitg1 = false;
  while ((!exitg1) && (i < 8)) {
    if (b_obj->inputVarSize[0].f1[i] != (unsigned int)inSize[i]) {
      for (i = 0; i < 8; i++) {
        b_obj->inputVarSize[0].f1[i] = (unsigned int)inSize[i];
      }
      exitg1 = true;
    } else {
      i++;
    }
  }
  AsyncBuffercgHelper_stepImpl(&obj->pBuffer, in_data, in_size);
}

/*
 * Arguments    : dsp_AsyncBuffer *obj
 *                double numRows
 *                emxArray_creal32_T *out
 * Return Type  : void
 */
void c_AsyncBuffer_read(dsp_AsyncBuffer *obj, double numRows,
                        emxArray_creal32_T *out)
{
  emxArray_creal32_T *b_out;
  creal32_T *b_out_data;
  creal32_T *out_data;
  double d;
  int c;
  int loop_ub;
  int qY;
  int underrun;
  d = rt_roundd_snf(numRows);
  if (d < 2.147483648E+9) {
    if (d >= -2.147483648E+9) {
      qY = (int)d;
    } else {
      qY = MIN_int32_T;
    }
  } else if (d >= 2.147483648E+9) {
    qY = MAX_int32_T;
  } else {
    qY = 0;
  }
  emxInit_creal32_T(&b_out, 1);
  d_AsyncBuffercgHelper_ReadSampl(&obj->pBuffer, qY, b_out, &underrun, &c);
  out_data = b_out->data;
  qY = out->size[0];
  out->size[0] = b_out->size[0];
  emxEnsureCapacity_creal32_T(out, qY);
  b_out_data = out->data;
  loop_ub = b_out->size[0];
  for (qY = 0; qY < loop_ub; qY++) {
    b_out_data[qY] = out_data[qY];
  }
  emxFree_creal32_T(&b_out);
  loop_ub = obj->pBuffer.WritePointer;
  if (loop_ub < -2147483647) {
    qY = MIN_int32_T;
  } else {
    qY = loop_ub - 1;
  }
  loop_ub = obj->pBuffer.CumulativeUnderrun;
  if ((loop_ub < 0) && (underrun < MIN_int32_T - loop_ub)) {
    loop_ub = MIN_int32_T;
  } else if ((loop_ub > 0) && (underrun > MAX_int32_T - loop_ub)) {
    loop_ub = MAX_int32_T;
  } else {
    loop_ub += underrun;
  }
  obj->pBuffer.CumulativeUnderrun = loop_ub;
  if (underrun != 0) {
    obj->pBuffer.ReadPointer = qY;
  } else {
    obj->pBuffer.ReadPointer = c;
  }
}

/*
 * Arguments    : b_dsp_AsyncBuffer *obj
 * Return Type  : void
 */
void c_AsyncBuffer_release(b_dsp_AsyncBuffer *obj)
{
  if (obj->pBuffer.isInitialized == 1) {
    obj->pBuffer.isInitialized = 2;
    if (obj->pBuffer.isSetupComplete) {
      obj->pBuffer.ReadPointer = 1;
      obj->pBuffer.WritePointer = 2;
      obj->pBuffer.CumulativeOverrun = 0;
      obj->pBuffer.CumulativeUnderrun = 0;
      obj->pBuffer.c_AsyncBuffercgHelper_isInitial = false;
      obj->pBuffer.NumChannels = -1;
    }
  }
}

/*
 * Arguments    : c_dsp_AsyncBuffer *obj
 *                const double in_data[]
 *                int in_size
 * Return Type  : void
 */
void c_AsyncBuffer_write(c_dsp_AsyncBuffer *obj, const double in_data[],
                         int in_size)
{
  e_dsp_internal_AsyncBuffercgHel *b_obj;
  int i;
  short inSize[8];
  bool exitg1;
  b_obj = &obj->pBuffer;
  if (obj->pBuffer.isInitialized != 1) {
    cell_wrap_2 varSizes;
    obj->pBuffer.isSetupComplete = false;
    obj->pBuffer.isInitialized = 1;
    varSizes.f1[0] = (unsigned int)in_size;
    varSizes.f1[1] = 1U;
    for (i = 0; i < 6; i++) {
      varSizes.f1[i + 2] = 1U;
    }
    obj->pBuffer.inputVarSize[0] = varSizes;
    obj->pBuffer.NumChannels = 1;
    obj->pBuffer.c_AsyncBuffercgHelper_isInitial = true;
    for (i = 0; i < 5800321; i++) {
      obj->pBuffer.Cache[i] = 0.0;
    }
    obj->pBuffer.isSetupComplete = true;
    obj->pBuffer.ReadPointer = 1;
    obj->pBuffer.WritePointer = 2;
    obj->pBuffer.CumulativeOverrun = 0;
    obj->pBuffer.CumulativeUnderrun = 0;
    for (i = 0; i < 5800321; i++) {
      obj->pBuffer.Cache[i] = 0.0;
    }
  }
  inSize[0] = (short)in_size;
  inSize[1] = 1;
  for (i = 0; i < 6; i++) {
    inSize[i + 2] = 1;
  }
  i = 0;
  exitg1 = false;
  while ((!exitg1) && (i < 8)) {
    if (b_obj->inputVarSize[0].f1[i] != (unsigned int)inSize[i]) {
      for (i = 0; i < 8; i++) {
        b_obj->inputVarSize[0].f1[i] = (unsigned int)inSize[i];
      }
      exitg1 = true;
    } else {
      i++;
    }
  }
  b_AsyncBuffercgHelper_stepImpl(&obj->pBuffer, in_data, in_size);
}

/*
 * Arguments    : c_dsp_AsyncBuffer *obj
 *                double numRows
 *                emxArray_real_T *out
 * Return Type  : void
 */
void d_AsyncBuffer_read(c_dsp_AsyncBuffer *obj, double numRows,
                        emxArray_real_T *out)
{
  emxArray_real_T *b_out;
  double d;
  double *b_out_data;
  double *out_data;
  int c;
  int loop_ub;
  int qY;
  int underrun;
  d = rt_roundd_snf(numRows);
  if (d < 2.147483648E+9) {
    if (d >= -2.147483648E+9) {
      qY = (int)d;
    } else {
      qY = MIN_int32_T;
    }
  } else if (d >= 2.147483648E+9) {
    qY = MAX_int32_T;
  } else {
    qY = 0;
  }
  emxInit_real_T(&b_out, 1);
  e_AsyncBuffercgHelper_ReadSampl(&obj->pBuffer, qY, b_out, &underrun, &c);
  out_data = b_out->data;
  qY = out->size[0];
  out->size[0] = b_out->size[0];
  emxEnsureCapacity_real_T(out, qY);
  b_out_data = out->data;
  loop_ub = b_out->size[0];
  for (qY = 0; qY < loop_ub; qY++) {
    b_out_data[qY] = out_data[qY];
  }
  emxFree_real_T(&b_out);
  loop_ub = obj->pBuffer.WritePointer;
  if (loop_ub < -2147483647) {
    qY = MIN_int32_T;
  } else {
    qY = loop_ub - 1;
  }
  loop_ub = obj->pBuffer.CumulativeUnderrun;
  if ((loop_ub < 0) && (underrun < MIN_int32_T - loop_ub)) {
    loop_ub = MIN_int32_T;
  } else if ((loop_ub > 0) && (underrun > MAX_int32_T - loop_ub)) {
    loop_ub = MAX_int32_T;
  } else {
    loop_ub += underrun;
  }
  obj->pBuffer.CumulativeUnderrun = loop_ub;
  if (underrun != 0) {
    obj->pBuffer.ReadPointer = qY;
  } else {
    obj->pBuffer.ReadPointer = c;
  }
}

/*
 * Arguments    : b_dsp_AsyncBuffer *obj
 *                const creal32_T in_data[]
 *                int in_size
 * Return Type  : void
 */
void d_AsyncBuffer_write(b_dsp_AsyncBuffer *obj, const creal32_T in_data[],
                         int in_size)
{
  d_dsp_internal_AsyncBuffercgHel *b_obj;
  int i;
  short inSize[8];
  bool exitg1;
  b_obj = &obj->pBuffer;
  if (obj->pBuffer.isInitialized != 1) {
    cell_wrap_2 varSizes;
    obj->pBuffer.isSetupComplete = false;
    obj->pBuffer.isInitialized = 1;
    varSizes.f1[0] = (unsigned int)in_size;
    varSizes.f1[1] = 1U;
    for (i = 0; i < 6; i++) {
      varSizes.f1[i + 2] = 1U;
    }
    obj->pBuffer.inputVarSize[0] = varSizes;
    obj->pBuffer.NumChannels = 1;
    obj->pBuffer.c_AsyncBuffercgHelper_isInitial = true;
    for (i = 0; i < 600651; i++) {
      obj->pBuffer.Cache[i].re = 0.0F;
      obj->pBuffer.Cache[i].im = 0.0F;
    }
    obj->pBuffer.isSetupComplete = true;
    obj->pBuffer.ReadPointer = 1;
    obj->pBuffer.WritePointer = 2;
    obj->pBuffer.CumulativeOverrun = 0;
    obj->pBuffer.CumulativeUnderrun = 0;
    for (i = 0; i < 600651; i++) {
      obj->pBuffer.Cache[i].re = 0.0F;
      obj->pBuffer.Cache[i].im = 0.0F;
    }
  }
  inSize[0] = (short)in_size;
  inSize[1] = 1;
  for (i = 0; i < 6; i++) {
    inSize[i + 2] = 1;
  }
  i = 0;
  exitg1 = false;
  while ((!exitg1) && (i < 8)) {
    if (b_obj->inputVarSize[0].f1[i] != (unsigned int)inSize[i]) {
      for (i = 0; i < 8; i++) {
        b_obj->inputVarSize[0].f1[i] = (unsigned int)inSize[i];
      }
      exitg1 = true;
    } else {
      i++;
    }
  }
  c_AsyncBuffercgHelper_stepImpl(&obj->pBuffer, in_data, in_size);
}

/*
 * Arguments    : dsp_AsyncBuffer *obj
 *                double numRows
 *                double overlap
 *                emxArray_creal32_T *out
 * Return Type  : void
 */
void e_AsyncBuffer_read(dsp_AsyncBuffer *obj, double numRows, double overlap,
                        emxArray_creal32_T *out)
{
  emxArray_creal32_T *b_out;
  emxArray_int32_T *r;
  emxArray_int32_T *readIdx;
  emxArray_int32_T *y;
  creal32_T *b_out_data;
  creal32_T *out_data;
  double d;
  int b_numRows;
  int b_qY;
  int c;
  int c_qY;
  int k;
  int n;
  int qY;
  int rPtr;
  int wPtr_tmp;
  int yk;
  int *r1;
  int *readIdx_data;
  int *y_data;
  d = rt_roundd_snf(numRows);
  if (d < 2.147483648E+9) {
    if (d >= -2.147483648E+9) {
      b_numRows = (int)d;
    } else {
      b_numRows = MIN_int32_T;
    }
  } else if (d >= 2.147483648E+9) {
    b_numRows = MAX_int32_T;
  } else {
    b_numRows = 0;
  }
  d = rt_roundd_snf(overlap);
  if (d < 2.147483648E+9) {
    if (d >= -2.147483648E+9) {
      yk = (int)d;
    } else {
      yk = MIN_int32_T;
    }
  } else if (d >= 2.147483648E+9) {
    yk = MAX_int32_T;
  } else {
    yk = 0;
  }
  wPtr_tmp = obj->pBuffer.WritePointer;
  qY = 0;
  b_qY = 0;
  n = obj->pBuffer.ReadPointer;
  if (n > 2147483646) {
    rPtr = MAX_int32_T;
  } else {
    rPtr = n + 1;
  }
  if (rPtr > 5800321) {
    rPtr = 1;
  }
  emxInit_int32_T(&readIdx, 2);
  emxInit_int32_T(&y, 2);
  emxInit_int32_T(&r, 2);
  if (yk == 0) {
    if ((rPtr < 0) && (b_numRows < MIN_int32_T - rPtr)) {
      c_qY = MIN_int32_T;
    } else if ((rPtr > 0) && (b_numRows > MAX_int32_T - rPtr)) {
      c_qY = MAX_int32_T;
    } else {
      c_qY = rPtr + b_numRows;
    }
    if (c_qY < -2147483647) {
      c_qY = MIN_int32_T;
    } else {
      c_qY--;
    }
    c = c_qY;
    if (c_qY > 5800321) {
      c = c_qY - 5800321;
      k = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = c_qY - 5800321;
      emxEnsureCapacity_int32_T(y, k);
      y_data = y->data;
      y_data[0] = 1;
      yk = 1;
      for (k = 2; k <= c; k++) {
        yk++;
        y_data[k - 1] = yk;
      }
      eml_integer_colon_dispatcher(rPtr, r);
      r1 = r->data;
      k = readIdx->size[0] * readIdx->size[1];
      readIdx->size[0] = 1;
      readIdx->size[1] = r->size[1] + y->size[1];
      emxEnsureCapacity_int32_T(readIdx, k);
      readIdx_data = readIdx->data;
      yk = r->size[1];
      for (k = 0; k < yk; k++) {
        readIdx_data[k] = r1[k];
      }
      yk = y->size[1];
      for (k = 0; k < yk; k++) {
        readIdx_data[k + r->size[1]] = y_data[k];
      }
      if (rPtr <= wPtr_tmp) {
        if (wPtr_tmp < -2141683326) {
          qY = MAX_int32_T;
        } else {
          qY = 5800321 - wPtr_tmp;
        }
        if (qY > 2147483646) {
          qY = MAX_int32_T;
        } else {
          qY++;
        }
        if ((qY < 0) && (c_qY - 5800321 < MIN_int32_T - qY)) {
          qY = MIN_int32_T;
        } else if ((qY > 0) && (c_qY - 5800321 > MAX_int32_T - qY)) {
          qY = MAX_int32_T;
        } else {
          qY = (qY + c_qY) - 5800321;
        }
      } else if (wPtr_tmp <= c_qY - 5800321) {
        if (wPtr_tmp < c_qY + 2141683328) {
          c_qY = MAX_int32_T;
        } else {
          c_qY = (c_qY - wPtr_tmp) - 5800321;
        }
        if (c_qY > 2147483646) {
          qY = MAX_int32_T;
        } else {
          qY = c_qY + 1;
        }
      }
    } else {
      if (c_qY < rPtr) {
        n = 0;
      } else {
        n = (c_qY - rPtr) + 1;
      }
      k = readIdx->size[0] * readIdx->size[1];
      readIdx->size[0] = 1;
      readIdx->size[1] = n;
      emxEnsureCapacity_int32_T(readIdx, k);
      readIdx_data = readIdx->data;
      if (n > 0) {
        readIdx_data[0] = rPtr;
        yk = rPtr;
        for (k = 2; k <= n; k++) {
          yk++;
          readIdx_data[k - 1] = yk;
        }
      }
      if ((rPtr <= wPtr_tmp) && (wPtr_tmp <= c_qY)) {
        if ((c_qY >= 0) && (wPtr_tmp < c_qY - MAX_int32_T)) {
          c_qY = MAX_int32_T;
        } else if ((c_qY < 0) && (wPtr_tmp > c_qY - MIN_int32_T)) {
          c_qY = MIN_int32_T;
        } else {
          c_qY -= wPtr_tmp;
        }
        if (c_qY > 2147483646) {
          qY = MAX_int32_T;
        } else {
          qY = c_qY + 1;
        }
      }
    }
  } else {
    int qY_tmp;
    if ((rPtr >= 0) && (yk < rPtr - MAX_int32_T)) {
      qY_tmp = MAX_int32_T;
      c_qY = MAX_int32_T;
    } else if ((rPtr < 0) && (yk > rPtr - MIN_int32_T)) {
      qY_tmp = MIN_int32_T;
      c_qY = MIN_int32_T;
    } else {
      qY_tmp = rPtr - yk;
      c_qY = qY_tmp;
    }
    if ((c_qY < 0) && (b_numRows < MIN_int32_T - c_qY)) {
      c_qY = MIN_int32_T;
    } else if ((c_qY > 0) && (b_numRows > MAX_int32_T - c_qY)) {
      c_qY = MAX_int32_T;
    } else {
      c_qY += b_numRows;
    }
    if (c_qY < -2147483647) {
      c_qY = MIN_int32_T;
    } else {
      c_qY--;
    }
    c = c_qY;
    if (qY_tmp < 1) {
      if (c_qY < 1) {
        n = 0;
      } else {
        n = c_qY;
      }
      k = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = n;
      emxEnsureCapacity_int32_T(y, k);
      y_data = y->data;
      if (n > 0) {
        y_data[0] = 1;
        yk = 1;
        for (k = 2; k <= n; k++) {
          yk++;
          y_data[k - 1] = yk;
        }
      }
      eml_integer_colon_dispatcher(qY_tmp + 5800321, r);
      r1 = r->data;
      k = readIdx->size[0] * readIdx->size[1];
      readIdx->size[0] = 1;
      readIdx->size[1] = r->size[1] + y->size[1];
      emxEnsureCapacity_int32_T(readIdx, k);
      readIdx_data = readIdx->data;
      yk = r->size[1];
      for (k = 0; k < yk; k++) {
        readIdx_data[k] = r1[k];
      }
      yk = y->size[1];
      for (k = 0; k < yk; k++) {
        readIdx_data[k + r->size[1]] = y_data[k];
      }
      if ((rPtr <= wPtr_tmp) && (wPtr_tmp <= c_qY)) {
        if ((c_qY >= 0) && (wPtr_tmp < c_qY - MAX_int32_T)) {
          c_qY = MAX_int32_T;
        } else if ((c_qY < 0) && (wPtr_tmp > c_qY - MIN_int32_T)) {
          c_qY = MIN_int32_T;
        } else {
          c_qY -= wPtr_tmp;
        }
        if (c_qY > 2147483646) {
          qY = MAX_int32_T;
        } else {
          qY = c_qY + 1;
        }
      } else if (wPtr_tmp < rPtr) {
        if (qY_tmp + 5800321 < -2141683326) {
          c_qY = MAX_int32_T;
        } else {
          c_qY = -qY_tmp;
        }
        if (c_qY > 2147483646) {
          c_qY = MAX_int32_T;
        } else {
          c_qY++;
        }
        if ((c_qY < 0) && (wPtr_tmp < MIN_int32_T - c_qY)) {
          b_qY = MIN_int32_T;
        } else if ((c_qY > 0) && (wPtr_tmp > MAX_int32_T - c_qY)) {
          b_qY = MAX_int32_T;
        } else {
          b_qY = c_qY + wPtr_tmp;
        }
      } else if (wPtr_tmp > qY_tmp + 5800321) {
        if ((wPtr_tmp >= 0) && (qY_tmp + 5800321 < wPtr_tmp - MAX_int32_T)) {
          c_qY = MAX_int32_T;
        } else if ((wPtr_tmp < 0) &&
                   (qY_tmp + 5800321 > wPtr_tmp - MIN_int32_T)) {
          c_qY = MIN_int32_T;
        } else {
          c_qY = (wPtr_tmp - qY_tmp) - 5800321;
        }
        if (c_qY > 2147483646) {
          b_qY = MAX_int32_T;
        } else {
          b_qY = c_qY + 1;
        }
      }
    } else if (c_qY > 5800321) {
      c = c_qY - 5800321;
      k = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = c_qY - 5800321;
      emxEnsureCapacity_int32_T(y, k);
      y_data = y->data;
      y_data[0] = 1;
      yk = 1;
      for (k = 2; k <= c; k++) {
        yk++;
        y_data[k - 1] = yk;
      }
      eml_integer_colon_dispatcher(qY_tmp, r);
      r1 = r->data;
      k = readIdx->size[0] * readIdx->size[1];
      readIdx->size[0] = 1;
      readIdx->size[1] = r->size[1] + y->size[1];
      emxEnsureCapacity_int32_T(readIdx, k);
      readIdx_data = readIdx->data;
      yk = r->size[1];
      for (k = 0; k < yk; k++) {
        readIdx_data[k] = r1[k];
      }
      yk = y->size[1];
      for (k = 0; k < yk; k++) {
        readIdx_data[k + r->size[1]] = y_data[k];
      }
      if (rPtr <= wPtr_tmp) {
        if (wPtr_tmp < -2141683326) {
          qY = MAX_int32_T;
        } else {
          qY = 5800321 - wPtr_tmp;
        }
        if (qY > 2147483646) {
          qY = MAX_int32_T;
        } else {
          qY++;
        }
        if ((qY < 0) && (c_qY - 5800321 < MIN_int32_T - qY)) {
          qY = MIN_int32_T;
        } else if ((qY > 0) && (c_qY - 5800321 > MAX_int32_T - qY)) {
          qY = MAX_int32_T;
        } else {
          qY = (qY + c_qY) - 5800321;
        }
      } else if (wPtr_tmp <= c_qY - 5800321) {
        if (wPtr_tmp < c_qY + 2141683328) {
          c_qY = MAX_int32_T;
        } else {
          c_qY = (c_qY - wPtr_tmp) - 5800321;
        }
        if (c_qY > 2147483646) {
          qY = MAX_int32_T;
        } else {
          qY = c_qY + 1;
        }
      } else if ((qY_tmp < wPtr_tmp) && (wPtr_tmp < rPtr)) {
        b_qY = (wPtr_tmp - qY_tmp) + 1;
      }
    } else {
      if (c_qY < qY_tmp) {
        n = 0;
      } else {
        n = (c_qY - qY_tmp) + 1;
      }
      k = readIdx->size[0] * readIdx->size[1];
      readIdx->size[0] = 1;
      readIdx->size[1] = n;
      emxEnsureCapacity_int32_T(readIdx, k);
      readIdx_data = readIdx->data;
      if (n > 0) {
        readIdx_data[0] = qY_tmp;
        yk = qY_tmp;
        for (k = 2; k <= n; k++) {
          yk++;
          readIdx_data[k - 1] = yk;
        }
      }
      if ((rPtr <= wPtr_tmp) && (wPtr_tmp <= c_qY)) {
        if ((c_qY >= 0) && (wPtr_tmp < c_qY - MAX_int32_T)) {
          c_qY = MAX_int32_T;
        } else if ((c_qY < 0) && (wPtr_tmp > c_qY - MIN_int32_T)) {
          c_qY = MIN_int32_T;
        } else {
          c_qY -= wPtr_tmp;
        }
        if (c_qY > 2147483646) {
          qY = MAX_int32_T;
        } else {
          qY = c_qY + 1;
        }
      } else if ((qY_tmp <= wPtr_tmp) && (wPtr_tmp < rPtr)) {
        b_qY = (wPtr_tmp - qY_tmp) + 1;
      }
    }
  }
  emxFree_int32_T(&r);
  emxFree_int32_T(&y);
  emxInit_creal32_T(&b_out, 1);
  k = b_out->size[0];
  b_out->size[0] = readIdx->size[1];
  emxEnsureCapacity_creal32_T(b_out, k);
  out_data = b_out->data;
  yk = readIdx->size[1];
  for (k = 0; k < yk; k++) {
    out_data[k] = obj->pBuffer.Cache[readIdx_data[k] - 1];
  }
  emxFree_int32_T(&readIdx);
  if (qY != 0) {
    if ((b_numRows >= 0) && (qY < b_numRows - MAX_int32_T)) {
      c_qY = MAX_int32_T;
    } else if ((b_numRows < 0) && (qY > b_numRows - MIN_int32_T)) {
      c_qY = MIN_int32_T;
    } else {
      c_qY = b_numRows - qY;
    }
    if (c_qY > 2147483646) {
      c_qY = MAX_int32_T;
    } else {
      c_qY++;
    }
    if (c_qY > b_numRows) {
      c_qY = 1;
    }
    for (k = 0; k < qY; k++) {
      yk = (c_qY + k) - 1;
      out_data[yk].re = 0.0F;
      out_data[yk].im = 0.0F;
    }
  } else if (b_qY != 0) {
    if (b_qY == b_numRows) {
      k = b_out->size[0];
      b_out->size[0] = b_qY;
      emxEnsureCapacity_creal32_T(b_out, k);
      out_data = b_out->data;
      for (k = 0; k < b_qY; k++) {
        out_data[k].re = 0.0F;
        out_data[k].im = 0.0F;
      }
    } else {
      for (k = 0; k < b_qY; k++) {
        out_data[k].re = 0.0F;
        out_data[k].im = 0.0F;
      }
    }
  }
  k = out->size[0];
  out->size[0] = b_out->size[0];
  emxEnsureCapacity_creal32_T(out, k);
  b_out_data = out->data;
  yk = b_out->size[0];
  for (k = 0; k < yk; k++) {
    b_out_data[k] = out_data[k];
  }
  emxFree_creal32_T(&b_out);
  if (wPtr_tmp < -2147483647) {
    c_qY = MIN_int32_T;
  } else {
    c_qY = wPtr_tmp - 1;
  }
  n = obj->pBuffer.CumulativeUnderrun;
  if ((n < 0) && (qY < MIN_int32_T - n)) {
    b_qY = MIN_int32_T;
  } else if ((n > 0) && (qY > MAX_int32_T - n)) {
    b_qY = MAX_int32_T;
  } else {
    b_qY = n + qY;
  }
  obj->pBuffer.CumulativeUnderrun = b_qY;
  if (qY != 0) {
    obj->pBuffer.ReadPointer = c_qY;
  } else {
    obj->pBuffer.ReadPointer = c;
  }
}

/*
 * Arguments    : c_dsp_AsyncBuffer *obj
 *                double numRows
 *                double overlap
 *                emxArray_real_T *out
 * Return Type  : void
 */
void f_AsyncBuffer_read(c_dsp_AsyncBuffer *obj, double numRows, double overlap,
                        emxArray_real_T *out)
{
  emxArray_int32_T *r;
  emxArray_int32_T *readIdx;
  emxArray_int32_T *y;
  emxArray_real_T *b_out;
  double d;
  double *b_out_data;
  double *out_data;
  int b_numRows;
  int b_qY;
  int c;
  int c_qY;
  int k;
  int n;
  int qY;
  int rPtr;
  int wPtr_tmp;
  int yk;
  int *r1;
  int *readIdx_data;
  int *y_data;
  d = rt_roundd_snf(numRows);
  if (d < 2.147483648E+9) {
    if (d >= -2.147483648E+9) {
      b_numRows = (int)d;
    } else {
      b_numRows = MIN_int32_T;
    }
  } else if (d >= 2.147483648E+9) {
    b_numRows = MAX_int32_T;
  } else {
    b_numRows = 0;
  }
  d = rt_roundd_snf(overlap);
  if (d < 2.147483648E+9) {
    if (d >= -2.147483648E+9) {
      yk = (int)d;
    } else {
      yk = MIN_int32_T;
    }
  } else if (d >= 2.147483648E+9) {
    yk = MAX_int32_T;
  } else {
    yk = 0;
  }
  wPtr_tmp = obj->pBuffer.WritePointer;
  qY = 0;
  b_qY = 0;
  n = obj->pBuffer.ReadPointer;
  if (n > 2147483646) {
    rPtr = MAX_int32_T;
  } else {
    rPtr = n + 1;
  }
  if (rPtr > 5800321) {
    rPtr = 1;
  }
  emxInit_int32_T(&readIdx, 2);
  emxInit_int32_T(&y, 2);
  emxInit_int32_T(&r, 2);
  if (yk == 0) {
    if ((rPtr < 0) && (b_numRows < MIN_int32_T - rPtr)) {
      c_qY = MIN_int32_T;
    } else if ((rPtr > 0) && (b_numRows > MAX_int32_T - rPtr)) {
      c_qY = MAX_int32_T;
    } else {
      c_qY = rPtr + b_numRows;
    }
    if (c_qY < -2147483647) {
      c_qY = MIN_int32_T;
    } else {
      c_qY--;
    }
    c = c_qY;
    if (c_qY > 5800321) {
      c = c_qY - 5800321;
      k = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = c_qY - 5800321;
      emxEnsureCapacity_int32_T(y, k);
      y_data = y->data;
      y_data[0] = 1;
      yk = 1;
      for (k = 2; k <= c; k++) {
        yk++;
        y_data[k - 1] = yk;
      }
      eml_integer_colon_dispatcher(rPtr, r);
      r1 = r->data;
      k = readIdx->size[0] * readIdx->size[1];
      readIdx->size[0] = 1;
      readIdx->size[1] = r->size[1] + y->size[1];
      emxEnsureCapacity_int32_T(readIdx, k);
      readIdx_data = readIdx->data;
      yk = r->size[1];
      for (k = 0; k < yk; k++) {
        readIdx_data[k] = r1[k];
      }
      yk = y->size[1];
      for (k = 0; k < yk; k++) {
        readIdx_data[k + r->size[1]] = y_data[k];
      }
      if (rPtr <= wPtr_tmp) {
        if (wPtr_tmp < -2141683326) {
          qY = MAX_int32_T;
        } else {
          qY = 5800321 - wPtr_tmp;
        }
        if (qY > 2147483646) {
          qY = MAX_int32_T;
        } else {
          qY++;
        }
        if ((qY < 0) && (c_qY - 5800321 < MIN_int32_T - qY)) {
          qY = MIN_int32_T;
        } else if ((qY > 0) && (c_qY - 5800321 > MAX_int32_T - qY)) {
          qY = MAX_int32_T;
        } else {
          qY = (qY + c_qY) - 5800321;
        }
      } else if (wPtr_tmp <= c_qY - 5800321) {
        if (wPtr_tmp < c_qY + 2141683328) {
          c_qY = MAX_int32_T;
        } else {
          c_qY = (c_qY - wPtr_tmp) - 5800321;
        }
        if (c_qY > 2147483646) {
          qY = MAX_int32_T;
        } else {
          qY = c_qY + 1;
        }
      }
    } else {
      if (c_qY < rPtr) {
        n = 0;
      } else {
        n = (c_qY - rPtr) + 1;
      }
      k = readIdx->size[0] * readIdx->size[1];
      readIdx->size[0] = 1;
      readIdx->size[1] = n;
      emxEnsureCapacity_int32_T(readIdx, k);
      readIdx_data = readIdx->data;
      if (n > 0) {
        readIdx_data[0] = rPtr;
        yk = rPtr;
        for (k = 2; k <= n; k++) {
          yk++;
          readIdx_data[k - 1] = yk;
        }
      }
      if ((rPtr <= wPtr_tmp) && (wPtr_tmp <= c_qY)) {
        if ((c_qY >= 0) && (wPtr_tmp < c_qY - MAX_int32_T)) {
          c_qY = MAX_int32_T;
        } else if ((c_qY < 0) && (wPtr_tmp > c_qY - MIN_int32_T)) {
          c_qY = MIN_int32_T;
        } else {
          c_qY -= wPtr_tmp;
        }
        if (c_qY > 2147483646) {
          qY = MAX_int32_T;
        } else {
          qY = c_qY + 1;
        }
      }
    }
  } else {
    int qY_tmp;
    if ((rPtr >= 0) && (yk < rPtr - MAX_int32_T)) {
      qY_tmp = MAX_int32_T;
      c_qY = MAX_int32_T;
    } else if ((rPtr < 0) && (yk > rPtr - MIN_int32_T)) {
      qY_tmp = MIN_int32_T;
      c_qY = MIN_int32_T;
    } else {
      qY_tmp = rPtr - yk;
      c_qY = qY_tmp;
    }
    if ((c_qY < 0) && (b_numRows < MIN_int32_T - c_qY)) {
      c_qY = MIN_int32_T;
    } else if ((c_qY > 0) && (b_numRows > MAX_int32_T - c_qY)) {
      c_qY = MAX_int32_T;
    } else {
      c_qY += b_numRows;
    }
    if (c_qY < -2147483647) {
      c_qY = MIN_int32_T;
    } else {
      c_qY--;
    }
    c = c_qY;
    if (qY_tmp < 1) {
      if (c_qY < 1) {
        n = 0;
      } else {
        n = c_qY;
      }
      k = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = n;
      emxEnsureCapacity_int32_T(y, k);
      y_data = y->data;
      if (n > 0) {
        y_data[0] = 1;
        yk = 1;
        for (k = 2; k <= n; k++) {
          yk++;
          y_data[k - 1] = yk;
        }
      }
      eml_integer_colon_dispatcher(qY_tmp + 5800321, r);
      r1 = r->data;
      k = readIdx->size[0] * readIdx->size[1];
      readIdx->size[0] = 1;
      readIdx->size[1] = r->size[1] + y->size[1];
      emxEnsureCapacity_int32_T(readIdx, k);
      readIdx_data = readIdx->data;
      yk = r->size[1];
      for (k = 0; k < yk; k++) {
        readIdx_data[k] = r1[k];
      }
      yk = y->size[1];
      for (k = 0; k < yk; k++) {
        readIdx_data[k + r->size[1]] = y_data[k];
      }
      if ((rPtr <= wPtr_tmp) && (wPtr_tmp <= c_qY)) {
        if ((c_qY >= 0) && (wPtr_tmp < c_qY - MAX_int32_T)) {
          c_qY = MAX_int32_T;
        } else if ((c_qY < 0) && (wPtr_tmp > c_qY - MIN_int32_T)) {
          c_qY = MIN_int32_T;
        } else {
          c_qY -= wPtr_tmp;
        }
        if (c_qY > 2147483646) {
          qY = MAX_int32_T;
        } else {
          qY = c_qY + 1;
        }
      } else if (wPtr_tmp < rPtr) {
        if (qY_tmp + 5800321 < -2141683326) {
          c_qY = MAX_int32_T;
        } else {
          c_qY = -qY_tmp;
        }
        if (c_qY > 2147483646) {
          c_qY = MAX_int32_T;
        } else {
          c_qY++;
        }
        if ((c_qY < 0) && (wPtr_tmp < MIN_int32_T - c_qY)) {
          b_qY = MIN_int32_T;
        } else if ((c_qY > 0) && (wPtr_tmp > MAX_int32_T - c_qY)) {
          b_qY = MAX_int32_T;
        } else {
          b_qY = c_qY + wPtr_tmp;
        }
      } else if (wPtr_tmp > qY_tmp + 5800321) {
        if ((wPtr_tmp >= 0) && (qY_tmp + 5800321 < wPtr_tmp - MAX_int32_T)) {
          c_qY = MAX_int32_T;
        } else if ((wPtr_tmp < 0) &&
                   (qY_tmp + 5800321 > wPtr_tmp - MIN_int32_T)) {
          c_qY = MIN_int32_T;
        } else {
          c_qY = (wPtr_tmp - qY_tmp) - 5800321;
        }
        if (c_qY > 2147483646) {
          b_qY = MAX_int32_T;
        } else {
          b_qY = c_qY + 1;
        }
      }
    } else if (c_qY > 5800321) {
      c = c_qY - 5800321;
      k = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = c_qY - 5800321;
      emxEnsureCapacity_int32_T(y, k);
      y_data = y->data;
      y_data[0] = 1;
      yk = 1;
      for (k = 2; k <= c; k++) {
        yk++;
        y_data[k - 1] = yk;
      }
      eml_integer_colon_dispatcher(qY_tmp, r);
      r1 = r->data;
      k = readIdx->size[0] * readIdx->size[1];
      readIdx->size[0] = 1;
      readIdx->size[1] = r->size[1] + y->size[1];
      emxEnsureCapacity_int32_T(readIdx, k);
      readIdx_data = readIdx->data;
      yk = r->size[1];
      for (k = 0; k < yk; k++) {
        readIdx_data[k] = r1[k];
      }
      yk = y->size[1];
      for (k = 0; k < yk; k++) {
        readIdx_data[k + r->size[1]] = y_data[k];
      }
      if (rPtr <= wPtr_tmp) {
        if (wPtr_tmp < -2141683326) {
          qY = MAX_int32_T;
        } else {
          qY = 5800321 - wPtr_tmp;
        }
        if (qY > 2147483646) {
          qY = MAX_int32_T;
        } else {
          qY++;
        }
        if ((qY < 0) && (c_qY - 5800321 < MIN_int32_T - qY)) {
          qY = MIN_int32_T;
        } else if ((qY > 0) && (c_qY - 5800321 > MAX_int32_T - qY)) {
          qY = MAX_int32_T;
        } else {
          qY = (qY + c_qY) - 5800321;
        }
      } else if (wPtr_tmp <= c_qY - 5800321) {
        if (wPtr_tmp < c_qY + 2141683328) {
          c_qY = MAX_int32_T;
        } else {
          c_qY = (c_qY - wPtr_tmp) - 5800321;
        }
        if (c_qY > 2147483646) {
          qY = MAX_int32_T;
        } else {
          qY = c_qY + 1;
        }
      } else if ((qY_tmp < wPtr_tmp) && (wPtr_tmp < rPtr)) {
        b_qY = (wPtr_tmp - qY_tmp) + 1;
      }
    } else {
      if (c_qY < qY_tmp) {
        n = 0;
      } else {
        n = (c_qY - qY_tmp) + 1;
      }
      k = readIdx->size[0] * readIdx->size[1];
      readIdx->size[0] = 1;
      readIdx->size[1] = n;
      emxEnsureCapacity_int32_T(readIdx, k);
      readIdx_data = readIdx->data;
      if (n > 0) {
        readIdx_data[0] = qY_tmp;
        yk = qY_tmp;
        for (k = 2; k <= n; k++) {
          yk++;
          readIdx_data[k - 1] = yk;
        }
      }
      if ((rPtr <= wPtr_tmp) && (wPtr_tmp <= c_qY)) {
        if ((c_qY >= 0) && (wPtr_tmp < c_qY - MAX_int32_T)) {
          c_qY = MAX_int32_T;
        } else if ((c_qY < 0) && (wPtr_tmp > c_qY - MIN_int32_T)) {
          c_qY = MIN_int32_T;
        } else {
          c_qY -= wPtr_tmp;
        }
        if (c_qY > 2147483646) {
          qY = MAX_int32_T;
        } else {
          qY = c_qY + 1;
        }
      } else if ((qY_tmp <= wPtr_tmp) && (wPtr_tmp < rPtr)) {
        b_qY = (wPtr_tmp - qY_tmp) + 1;
      }
    }
  }
  emxFree_int32_T(&r);
  emxFree_int32_T(&y);
  emxInit_real_T(&b_out, 1);
  k = b_out->size[0];
  b_out->size[0] = readIdx->size[1];
  emxEnsureCapacity_real_T(b_out, k);
  out_data = b_out->data;
  yk = readIdx->size[1];
  for (k = 0; k < yk; k++) {
    out_data[k] = obj->pBuffer.Cache[readIdx_data[k] - 1];
  }
  emxFree_int32_T(&readIdx);
  if (qY != 0) {
    if ((b_numRows >= 0) && (qY < b_numRows - MAX_int32_T)) {
      c_qY = MAX_int32_T;
    } else if ((b_numRows < 0) && (qY > b_numRows - MIN_int32_T)) {
      c_qY = MIN_int32_T;
    } else {
      c_qY = b_numRows - qY;
    }
    if (c_qY > 2147483646) {
      c_qY = MAX_int32_T;
    } else {
      c_qY++;
    }
    if (c_qY > b_numRows) {
      c_qY = 1;
    }
    for (k = 0; k < qY; k++) {
      out_data[(c_qY + k) - 1] = 0.0;
    }
  } else if (b_qY != 0) {
    if (b_qY == b_numRows) {
      k = b_out->size[0];
      b_out->size[0] = b_qY;
      emxEnsureCapacity_real_T(b_out, k);
      out_data = b_out->data;
      for (k = 0; k < b_qY; k++) {
        out_data[k] = 0.0;
      }
    } else {
      for (k = 0; k < b_qY; k++) {
        out_data[k] = 0.0;
      }
    }
  }
  k = out->size[0];
  out->size[0] = b_out->size[0];
  emxEnsureCapacity_real_T(out, k);
  b_out_data = out->data;
  yk = b_out->size[0];
  for (k = 0; k < yk; k++) {
    b_out_data[k] = out_data[k];
  }
  emxFree_real_T(&b_out);
  if (wPtr_tmp < -2147483647) {
    c_qY = MIN_int32_T;
  } else {
    c_qY = wPtr_tmp - 1;
  }
  n = obj->pBuffer.CumulativeUnderrun;
  if ((n < 0) && (qY < MIN_int32_T - n)) {
    b_qY = MIN_int32_T;
  } else if ((n > 0) && (qY > MAX_int32_T - n)) {
    b_qY = MAX_int32_T;
  } else {
    b_qY = n + qY;
  }
  obj->pBuffer.CumulativeUnderrun = b_qY;
  if (qY != 0) {
    obj->pBuffer.ReadPointer = c_qY;
  } else {
    obj->pBuffer.ReadPointer = c;
  }
}

/*
 * File trailer for AsyncBuffer.c
 *
 * [EOF]
 */
