/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: AsyncBuffercgHelper.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "AsyncBuffercgHelper.h"
#include "colon.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_internal_types.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"

/* Function Declarations */
static void
c_AsyncBuffercgHelper_ReadSampl(const d_dsp_internal_AsyncBuffercgHel *obj,
                                int numRowsCast, emxArray_creal32_T *out,
                                int *underrun, int *c);

/* Function Definitions */
/*
 * Arguments    : const d_dsp_internal_AsyncBuffercgHel *obj
 *                int numRowsCast
 *                emxArray_creal32_T *out
 *                int *underrun
 *                int *c
 * Return Type  : void
 */
static void
c_AsyncBuffercgHelper_ReadSampl(const d_dsp_internal_AsyncBuffercgHel *obj,
                                int numRowsCast, emxArray_creal32_T *out,
                                int *underrun, int *c)
{
  emxArray_int32_T *b_y;
  emxArray_int32_T *c_y;
  emxArray_int32_T *y;
  creal32_T *out_data;
  int b_qY;
  int k;
  int qY;
  int rPtr;
  int wPtr;
  int yk;
  int *b_y_data;
  int *c_y_data;
  int *y_data;
  wPtr = obj->WritePointer;
  qY = 0;
  yk = obj->ReadPointer;
  if (yk > 2147483646) {
    rPtr = MAX_int32_T;
  } else {
    rPtr = yk + 1;
  }
  if (rPtr > 600651) {
    rPtr = 1;
  }
  if ((rPtr < 0) && (numRowsCast < MIN_int32_T - rPtr)) {
    b_qY = MIN_int32_T;
  } else if ((rPtr > 0) && (numRowsCast > MAX_int32_T - rPtr)) {
    b_qY = MAX_int32_T;
  } else {
    b_qY = rPtr + numRowsCast;
  }
  if (b_qY < -2147483647) {
    b_qY = MIN_int32_T;
  } else {
    b_qY--;
  }
  *c = b_qY;
  emxInit_int32_T(&y, 2);
  if (b_qY > 600651) {
    int n;
    *c = b_qY - 600651;
    n = 600652 - rPtr;
    emxInit_int32_T(&b_y, 2);
    k = b_y->size[0] * b_y->size[1];
    b_y->size[0] = 1;
    b_y->size[1] = 600652 - rPtr;
    emxEnsureCapacity_int32_T(b_y, k);
    b_y_data = b_y->data;
    b_y_data[0] = rPtr;
    yk = rPtr;
    for (k = 2; k <= n; k++) {
      yk++;
      b_y_data[k - 1] = yk;
    }
    emxInit_int32_T(&c_y, 2);
    k = c_y->size[0] * c_y->size[1];
    c_y->size[0] = 1;
    c_y->size[1] = b_qY - 600651;
    emxEnsureCapacity_int32_T(c_y, k);
    c_y_data = c_y->data;
    c_y_data[0] = 1;
    yk = 1;
    for (k = 2; k <= *c; k++) {
      yk++;
      c_y_data[k - 1] = yk;
    }
    k = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = b_y->size[1] + c_y->size[1];
    emxEnsureCapacity_int32_T(y, k);
    y_data = y->data;
    yk = b_y->size[1];
    for (k = 0; k < yk; k++) {
      y_data[k] = b_y_data[k];
    }
    yk = c_y->size[1];
    for (k = 0; k < yk; k++) {
      y_data[k + b_y->size[1]] = c_y_data[k];
    }
    emxFree_int32_T(&c_y);
    emxFree_int32_T(&b_y);
    if (rPtr <= wPtr) {
      if (wPtr < -2146882996) {
        qY = MAX_int32_T;
      } else {
        qY = 600651 - wPtr;
      }
      if (qY > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY++;
      }
      if ((qY < 0) && (b_qY - 600651 < MIN_int32_T - qY)) {
        qY = MIN_int32_T;
      } else if ((qY > 0) && (b_qY - 600651 > MAX_int32_T - qY)) {
        qY = MAX_int32_T;
      } else {
        qY = (qY + b_qY) - 600651;
      }
    } else if (wPtr <= b_qY - 600651) {
      if (wPtr < b_qY + 2146882998) {
        b_qY = MAX_int32_T;
      } else {
        b_qY = (b_qY - wPtr) - 600651;
      }
      if (b_qY > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY = b_qY + 1;
      }
    }
  } else {
    int n;
    if (b_qY < rPtr) {
      n = 0;
    } else {
      n = (b_qY - rPtr) + 1;
    }
    k = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = n;
    emxEnsureCapacity_int32_T(y, k);
    y_data = y->data;
    if (n > 0) {
      y_data[0] = rPtr;
      yk = rPtr;
      for (k = 2; k <= n; k++) {
        yk++;
        y_data[k - 1] = yk;
      }
    }
    if ((rPtr <= wPtr) && (wPtr <= b_qY)) {
      if ((b_qY >= 0) && (wPtr < b_qY - MAX_int32_T)) {
        b_qY = MAX_int32_T;
      } else if ((b_qY < 0) && (wPtr > b_qY - MIN_int32_T)) {
        b_qY = MIN_int32_T;
      } else {
        b_qY -= wPtr;
      }
      if (b_qY > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY = b_qY + 1;
      }
    }
  }
  k = out->size[0];
  out->size[0] = y->size[1];
  emxEnsureCapacity_creal32_T(out, k);
  out_data = out->data;
  yk = y->size[1];
  for (k = 0; k < yk; k++) {
    out_data[k] = obj->Cache[y_data[k] - 1];
  }
  emxFree_int32_T(&y);
  if (qY != 0) {
    if ((numRowsCast >= 0) && (qY < numRowsCast - MAX_int32_T)) {
      b_qY = MAX_int32_T;
    } else if ((numRowsCast < 0) && (qY > numRowsCast - MIN_int32_T)) {
      b_qY = MIN_int32_T;
    } else {
      b_qY = numRowsCast - qY;
    }
    if (b_qY > 2147483646) {
      b_qY = MAX_int32_T;
    } else {
      b_qY++;
    }
    if (b_qY > numRowsCast) {
      b_qY = 1;
    }
    for (k = 0; k < qY; k++) {
      yk = (b_qY + k) - 1;
      out_data[yk].re = 0.0F;
      out_data[yk].im = 0.0F;
    }
  }
  *underrun = qY;
}

/*
 * Arguments    : d_dsp_internal_AsyncBuffercgHel *obj
 *                int numRows
 *                emxArray_creal32_T *out
 *                int *underrun
 * Return Type  : void
 */
void AsyncBuffercgHelper_read(d_dsp_internal_AsyncBuffercgHel *obj, int numRows,
                              emxArray_creal32_T *out, int *underrun)
{
  emxArray_creal32_T *b_out;
  creal32_T *b_out_data;
  creal32_T *out_data;
  int c;
  int loop_ub;
  int qY;
  emxInit_creal32_T(&b_out, 1);
  c_AsyncBuffercgHelper_ReadSampl(obj, numRows, b_out, underrun, &c);
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
  loop_ub = obj->WritePointer;
  if (loop_ub < -2147483647) {
    qY = MIN_int32_T;
  } else {
    qY = loop_ub - 1;
  }
  loop_ub = obj->CumulativeUnderrun;
  if ((loop_ub < 0) && (*underrun < MIN_int32_T - loop_ub)) {
    loop_ub = MIN_int32_T;
  } else if ((loop_ub > 0) && (*underrun > MAX_int32_T - loop_ub)) {
    loop_ub = MAX_int32_T;
  } else {
    loop_ub += *underrun;
  }
  obj->CumulativeUnderrun = loop_ub;
  if (*underrun != 0) {
    obj->ReadPointer = qY;
  } else {
    obj->ReadPointer = c;
  }
}

/*
 * Arguments    : c_dsp_internal_AsyncBuffercgHel *obj
 *                const creal32_T in_data[]
 *                int in_size
 * Return Type  : int
 */
int AsyncBuffercgHelper_stepImpl(c_dsp_internal_AsyncBuffercgHel *obj,
                                 const creal32_T in_data[], int in_size)
{
  emxArray_int32_T *bc;
  emxArray_int32_T *r;
  emxArray_int32_T *r1;
  emxArray_int32_T *y;
  int c;
  int k;
  int overrun;
  int qY;
  int rPtr;
  int wPtr;
  int yk;
  int *bc_data;
  int *r2;
  int *y_data;
  wPtr = obj->WritePointer;
  rPtr = obj->ReadPointer;
  overrun = 0;
  if ((wPtr < 0) && (in_size < MIN_int32_T - wPtr)) {
    qY = MIN_int32_T;
  } else if ((wPtr > 0) && (in_size > MAX_int32_T - wPtr)) {
    qY = MAX_int32_T;
  } else {
    qY = wPtr + in_size;
  }
  if (qY < -2147483647) {
    qY = MIN_int32_T;
  } else {
    qY--;
  }
  c = qY;
  emxInit_int32_T(&bc, 2);
  if (qY > 5800321) {
    c = qY - 5800321;
    emxInit_int32_T(&y, 2);
    k = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = qY - 5800321;
    emxEnsureCapacity_int32_T(y, k);
    y_data = y->data;
    y_data[0] = 1;
    yk = 1;
    for (k = 2; k <= c; k++) {
      yk++;
      y_data[k - 1] = yk;
    }
    emxInit_int32_T(&r, 2);
    eml_integer_colon_dispatcher(wPtr, r);
    r2 = r->data;
    k = bc->size[0] * bc->size[1];
    bc->size[0] = 1;
    bc->size[1] = r->size[1] + y->size[1];
    emxEnsureCapacity_int32_T(bc, k);
    bc_data = bc->data;
    yk = r->size[1];
    for (k = 0; k < yk; k++) {
      bc_data[k] = r2[k];
    }
    yk = y->size[1];
    for (k = 0; k < yk; k++) {
      bc_data[k + r->size[1]] = y_data[k];
    }
    emxFree_int32_T(&r);
    emxFree_int32_T(&y);
    if (wPtr <= rPtr) {
      if (rPtr < -2141683326) {
        yk = MAX_int32_T;
      } else {
        yk = 5800321 - rPtr;
      }
      if (yk > 2147483646) {
        yk = MAX_int32_T;
      } else {
        yk++;
      }
      if ((yk < 0) && (qY - 5800321 < MIN_int32_T - yk)) {
        overrun = MIN_int32_T;
      } else if ((yk > 0) && (qY - 5800321 > MAX_int32_T - yk)) {
        overrun = MAX_int32_T;
      } else {
        overrun = (yk + qY) - 5800321;
      }
    } else if (rPtr <= qY - 5800321) {
      if (rPtr < qY + 2141683328) {
        qY = MAX_int32_T;
      } else {
        qY = (qY - rPtr) - 5800321;
      }
      if (qY > 2147483646) {
        overrun = MAX_int32_T;
      } else {
        overrun = qY + 1;
      }
    }
  } else {
    int n;
    if (qY < wPtr) {
      n = 0;
    } else {
      n = (qY - wPtr) + 1;
    }
    k = bc->size[0] * bc->size[1];
    bc->size[0] = 1;
    bc->size[1] = n;
    emxEnsureCapacity_int32_T(bc, k);
    bc_data = bc->data;
    if (n > 0) {
      bc_data[0] = wPtr;
      yk = wPtr;
      for (k = 2; k <= n; k++) {
        yk++;
        bc_data[k - 1] = yk;
      }
    }
    if ((wPtr <= rPtr) && (rPtr <= qY)) {
      if ((qY >= 0) && (rPtr < qY - MAX_int32_T)) {
        qY = MAX_int32_T;
      } else if ((qY < 0) && (rPtr > qY - MIN_int32_T)) {
        qY = MIN_int32_T;
      } else {
        qY -= rPtr;
      }
      if (qY > 2147483646) {
        overrun = MAX_int32_T;
      } else {
        overrun = qY + 1;
      }
    }
  }
  emxInit_int32_T(&r1, 1);
  k = r1->size[0];
  r1->size[0] = bc->size[1];
  emxEnsureCapacity_int32_T(r1, k);
  r2 = r1->data;
  yk = bc->size[1];
  for (k = 0; k < yk; k++) {
    r2[k] = bc_data[k] - 1;
  }
  emxFree_int32_T(&bc);
  for (k = 0; k < in_size; k++) {
    obj->Cache[r2[k]] = in_data[k];
  }
  emxFree_int32_T(&r1);
  if (c + 1 > 5800321) {
    wPtr = 1;
  } else {
    wPtr = c + 1;
  }
  if (overrun != 0) {
    rPtr = wPtr;
  }
  yk = obj->CumulativeOverrun;
  if ((yk < 0) && (overrun < MIN_int32_T - yk)) {
    qY = MIN_int32_T;
  } else if ((yk > 0) && (overrun > MAX_int32_T - yk)) {
    qY = MAX_int32_T;
  } else {
    qY = yk + overrun;
  }
  obj->CumulativeOverrun = qY;
  obj->WritePointer = wPtr;
  obj->ReadPointer = rPtr;
  return overrun;
}

/*
 * Arguments    : e_dsp_internal_AsyncBuffercgHel *obj
 *                const double in_data[]
 *                int in_size
 * Return Type  : int
 */
int b_AsyncBuffercgHelper_stepImpl(e_dsp_internal_AsyncBuffercgHel *obj,
                                   const double in_data[], int in_size)
{
  emxArray_int32_T *bc;
  emxArray_int32_T *r;
  emxArray_int32_T *r1;
  emxArray_int32_T *y;
  int c;
  int k;
  int overrun;
  int qY;
  int rPtr;
  int wPtr;
  int yk;
  int *bc_data;
  int *r2;
  int *y_data;
  wPtr = obj->WritePointer;
  rPtr = obj->ReadPointer;
  overrun = 0;
  if ((wPtr < 0) && (in_size < MIN_int32_T - wPtr)) {
    qY = MIN_int32_T;
  } else if ((wPtr > 0) && (in_size > MAX_int32_T - wPtr)) {
    qY = MAX_int32_T;
  } else {
    qY = wPtr + in_size;
  }
  if (qY < -2147483647) {
    qY = MIN_int32_T;
  } else {
    qY--;
  }
  c = qY;
  emxInit_int32_T(&bc, 2);
  if (qY > 5800321) {
    c = qY - 5800321;
    emxInit_int32_T(&y, 2);
    k = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = qY - 5800321;
    emxEnsureCapacity_int32_T(y, k);
    y_data = y->data;
    y_data[0] = 1;
    yk = 1;
    for (k = 2; k <= c; k++) {
      yk++;
      y_data[k - 1] = yk;
    }
    emxInit_int32_T(&r, 2);
    eml_integer_colon_dispatcher(wPtr, r);
    r2 = r->data;
    k = bc->size[0] * bc->size[1];
    bc->size[0] = 1;
    bc->size[1] = r->size[1] + y->size[1];
    emxEnsureCapacity_int32_T(bc, k);
    bc_data = bc->data;
    yk = r->size[1];
    for (k = 0; k < yk; k++) {
      bc_data[k] = r2[k];
    }
    yk = y->size[1];
    for (k = 0; k < yk; k++) {
      bc_data[k + r->size[1]] = y_data[k];
    }
    emxFree_int32_T(&r);
    emxFree_int32_T(&y);
    if (wPtr <= rPtr) {
      if (rPtr < -2141683326) {
        yk = MAX_int32_T;
      } else {
        yk = 5800321 - rPtr;
      }
      if (yk > 2147483646) {
        yk = MAX_int32_T;
      } else {
        yk++;
      }
      if ((yk < 0) && (qY - 5800321 < MIN_int32_T - yk)) {
        overrun = MIN_int32_T;
      } else if ((yk > 0) && (qY - 5800321 > MAX_int32_T - yk)) {
        overrun = MAX_int32_T;
      } else {
        overrun = (yk + qY) - 5800321;
      }
    } else if (rPtr <= qY - 5800321) {
      if (rPtr < qY + 2141683328) {
        qY = MAX_int32_T;
      } else {
        qY = (qY - rPtr) - 5800321;
      }
      if (qY > 2147483646) {
        overrun = MAX_int32_T;
      } else {
        overrun = qY + 1;
      }
    }
  } else {
    int n;
    if (qY < wPtr) {
      n = 0;
    } else {
      n = (qY - wPtr) + 1;
    }
    k = bc->size[0] * bc->size[1];
    bc->size[0] = 1;
    bc->size[1] = n;
    emxEnsureCapacity_int32_T(bc, k);
    bc_data = bc->data;
    if (n > 0) {
      bc_data[0] = wPtr;
      yk = wPtr;
      for (k = 2; k <= n; k++) {
        yk++;
        bc_data[k - 1] = yk;
      }
    }
    if ((wPtr <= rPtr) && (rPtr <= qY)) {
      if ((qY >= 0) && (rPtr < qY - MAX_int32_T)) {
        qY = MAX_int32_T;
      } else if ((qY < 0) && (rPtr > qY - MIN_int32_T)) {
        qY = MIN_int32_T;
      } else {
        qY -= rPtr;
      }
      if (qY > 2147483646) {
        overrun = MAX_int32_T;
      } else {
        overrun = qY + 1;
      }
    }
  }
  emxInit_int32_T(&r1, 1);
  k = r1->size[0];
  r1->size[0] = bc->size[1];
  emxEnsureCapacity_int32_T(r1, k);
  r2 = r1->data;
  yk = bc->size[1];
  for (k = 0; k < yk; k++) {
    r2[k] = bc_data[k] - 1;
  }
  emxFree_int32_T(&bc);
  for (k = 0; k < in_size; k++) {
    obj->Cache[r2[k]] = in_data[k];
  }
  emxFree_int32_T(&r1);
  if (c + 1 > 5800321) {
    wPtr = 1;
  } else {
    wPtr = c + 1;
  }
  if (overrun != 0) {
    rPtr = wPtr;
  }
  yk = obj->CumulativeOverrun;
  if ((yk < 0) && (overrun < MIN_int32_T - yk)) {
    qY = MIN_int32_T;
  } else if ((yk > 0) && (overrun > MAX_int32_T - yk)) {
    qY = MAX_int32_T;
  } else {
    qY = yk + overrun;
  }
  obj->CumulativeOverrun = qY;
  obj->WritePointer = wPtr;
  obj->ReadPointer = rPtr;
  return overrun;
}

/*
 * Arguments    : d_dsp_internal_AsyncBuffercgHel *obj
 *                const creal32_T in_data[]
 *                int in_size
 * Return Type  : int
 */
int c_AsyncBuffercgHelper_stepImpl(d_dsp_internal_AsyncBuffercgHel *obj,
                                   const creal32_T in_data[], int in_size)
{
  emxArray_int32_T *b_y;
  emxArray_int32_T *c_y;
  emxArray_int32_T *r;
  emxArray_int32_T *y;
  int c;
  int k;
  int overrun;
  int qY;
  int rPtr;
  int wPtr;
  int yk;
  int *b_y_data;
  int *c_y_data;
  int *y_data;
  wPtr = obj->WritePointer;
  rPtr = obj->ReadPointer;
  overrun = 0;
  if ((wPtr < 0) && (in_size < MIN_int32_T - wPtr)) {
    qY = MIN_int32_T;
  } else if ((wPtr > 0) && (in_size > MAX_int32_T - wPtr)) {
    qY = MAX_int32_T;
  } else {
    qY = wPtr + in_size;
  }
  if (qY < -2147483647) {
    qY = MIN_int32_T;
  } else {
    qY--;
  }
  c = qY;
  emxInit_int32_T(&y, 2);
  if (qY > 600651) {
    int n;
    c = qY - 600651;
    n = 600652 - wPtr;
    emxInit_int32_T(&b_y, 2);
    k = b_y->size[0] * b_y->size[1];
    b_y->size[0] = 1;
    b_y->size[1] = 600652 - wPtr;
    emxEnsureCapacity_int32_T(b_y, k);
    b_y_data = b_y->data;
    b_y_data[0] = wPtr;
    yk = wPtr;
    for (k = 2; k <= n; k++) {
      yk++;
      b_y_data[k - 1] = yk;
    }
    emxInit_int32_T(&c_y, 2);
    k = c_y->size[0] * c_y->size[1];
    c_y->size[0] = 1;
    c_y->size[1] = qY - 600651;
    emxEnsureCapacity_int32_T(c_y, k);
    c_y_data = c_y->data;
    c_y_data[0] = 1;
    yk = 1;
    for (k = 2; k <= c; k++) {
      yk++;
      c_y_data[k - 1] = yk;
    }
    k = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = b_y->size[1] + c_y->size[1];
    emxEnsureCapacity_int32_T(y, k);
    y_data = y->data;
    yk = b_y->size[1];
    for (k = 0; k < yk; k++) {
      y_data[k] = b_y_data[k];
    }
    yk = c_y->size[1];
    for (k = 0; k < yk; k++) {
      y_data[k + b_y->size[1]] = c_y_data[k];
    }
    emxFree_int32_T(&c_y);
    emxFree_int32_T(&b_y);
    if (wPtr <= rPtr) {
      if (rPtr < -2146882996) {
        yk = MAX_int32_T;
      } else {
        yk = 600651 - rPtr;
      }
      if (yk > 2147483646) {
        yk = MAX_int32_T;
      } else {
        yk++;
      }
      if ((yk < 0) && (qY - 600651 < MIN_int32_T - yk)) {
        overrun = MIN_int32_T;
      } else if ((yk > 0) && (qY - 600651 > MAX_int32_T - yk)) {
        overrun = MAX_int32_T;
      } else {
        overrun = (yk + qY) - 600651;
      }
    } else if (rPtr <= qY - 600651) {
      if (rPtr < qY + 2146882998) {
        qY = MAX_int32_T;
      } else {
        qY = (qY - rPtr) - 600651;
      }
      if (qY > 2147483646) {
        overrun = MAX_int32_T;
      } else {
        overrun = qY + 1;
      }
    }
  } else {
    int n;
    if (qY < wPtr) {
      n = 0;
    } else {
      n = (qY - wPtr) + 1;
    }
    k = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = n;
    emxEnsureCapacity_int32_T(y, k);
    y_data = y->data;
    if (n > 0) {
      y_data[0] = wPtr;
      yk = wPtr;
      for (k = 2; k <= n; k++) {
        yk++;
        y_data[k - 1] = yk;
      }
    }
    if ((wPtr <= rPtr) && (rPtr <= qY)) {
      if ((qY >= 0) && (rPtr < qY - MAX_int32_T)) {
        qY = MAX_int32_T;
      } else if ((qY < 0) && (rPtr > qY - MIN_int32_T)) {
        qY = MIN_int32_T;
      } else {
        qY -= rPtr;
      }
      if (qY > 2147483646) {
        overrun = MAX_int32_T;
      } else {
        overrun = qY + 1;
      }
    }
  }
  emxInit_int32_T(&r, 1);
  k = r->size[0];
  r->size[0] = y->size[1];
  emxEnsureCapacity_int32_T(r, k);
  b_y_data = r->data;
  yk = y->size[1];
  for (k = 0; k < yk; k++) {
    b_y_data[k] = y_data[k] - 1;
  }
  emxFree_int32_T(&y);
  for (k = 0; k < in_size; k++) {
    obj->Cache[b_y_data[k]] = in_data[k];
  }
  emxFree_int32_T(&r);
  if (c + 1 > 600651) {
    wPtr = 1;
  } else {
    wPtr = c + 1;
  }
  if (overrun != 0) {
    rPtr = wPtr;
  }
  yk = obj->CumulativeOverrun;
  if ((yk < 0) && (overrun < MIN_int32_T - yk)) {
    qY = MIN_int32_T;
  } else if ((yk > 0) && (overrun > MAX_int32_T - yk)) {
    qY = MAX_int32_T;
  } else {
    qY = yk + overrun;
  }
  obj->CumulativeOverrun = qY;
  obj->WritePointer = wPtr;
  obj->ReadPointer = rPtr;
  return overrun;
}

/*
 * Arguments    : const c_dsp_internal_AsyncBuffercgHel *obj
 *                int numRowsCast
 *                emxArray_creal32_T *out
 *                int *underrun
 *                int *c
 * Return Type  : void
 */
void d_AsyncBuffercgHelper_ReadSampl(const c_dsp_internal_AsyncBuffercgHel *obj,
                                     int numRowsCast, emxArray_creal32_T *out,
                                     int *underrun, int *c)
{
  emxArray_int32_T *r;
  emxArray_int32_T *readIdx;
  emxArray_int32_T *y;
  creal32_T *out_data;
  int b_qY;
  int k;
  int qY;
  int rPtr;
  int wPtr;
  int yk;
  int *r1;
  int *readIdx_data;
  int *y_data;
  wPtr = obj->WritePointer;
  qY = 0;
  yk = obj->ReadPointer;
  if (yk > 2147483646) {
    rPtr = MAX_int32_T;
  } else {
    rPtr = yk + 1;
  }
  if (rPtr > 5800321) {
    rPtr = 1;
  }
  if ((rPtr < 0) && (numRowsCast < MIN_int32_T - rPtr)) {
    b_qY = MIN_int32_T;
  } else if ((rPtr > 0) && (numRowsCast > MAX_int32_T - rPtr)) {
    b_qY = MAX_int32_T;
  } else {
    b_qY = rPtr + numRowsCast;
  }
  if (b_qY < -2147483647) {
    b_qY = MIN_int32_T;
  } else {
    b_qY--;
  }
  *c = b_qY;
  emxInit_int32_T(&readIdx, 2);
  if (b_qY > 5800321) {
    *c = b_qY - 5800321;
    emxInit_int32_T(&y, 2);
    k = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = b_qY - 5800321;
    emxEnsureCapacity_int32_T(y, k);
    y_data = y->data;
    y_data[0] = 1;
    yk = 1;
    for (k = 2; k <= *c; k++) {
      yk++;
      y_data[k - 1] = yk;
    }
    emxInit_int32_T(&r, 2);
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
    emxFree_int32_T(&r);
    emxFree_int32_T(&y);
    if (rPtr <= wPtr) {
      if (wPtr < -2141683326) {
        qY = MAX_int32_T;
      } else {
        qY = 5800321 - wPtr;
      }
      if (qY > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY++;
      }
      if ((qY < 0) && (b_qY - 5800321 < MIN_int32_T - qY)) {
        qY = MIN_int32_T;
      } else if ((qY > 0) && (b_qY - 5800321 > MAX_int32_T - qY)) {
        qY = MAX_int32_T;
      } else {
        qY = (qY + b_qY) - 5800321;
      }
    } else if (wPtr <= b_qY - 5800321) {
      if (wPtr < b_qY + 2141683328) {
        b_qY = MAX_int32_T;
      } else {
        b_qY = (b_qY - wPtr) - 5800321;
      }
      if (b_qY > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY = b_qY + 1;
      }
    }
  } else {
    int n;
    if (b_qY < rPtr) {
      n = 0;
    } else {
      n = (b_qY - rPtr) + 1;
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
    if ((rPtr <= wPtr) && (wPtr <= b_qY)) {
      if ((b_qY >= 0) && (wPtr < b_qY - MAX_int32_T)) {
        b_qY = MAX_int32_T;
      } else if ((b_qY < 0) && (wPtr > b_qY - MIN_int32_T)) {
        b_qY = MIN_int32_T;
      } else {
        b_qY -= wPtr;
      }
      if (b_qY > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY = b_qY + 1;
      }
    }
  }
  k = out->size[0];
  out->size[0] = readIdx->size[1];
  emxEnsureCapacity_creal32_T(out, k);
  out_data = out->data;
  yk = readIdx->size[1];
  for (k = 0; k < yk; k++) {
    out_data[k] = obj->Cache[readIdx_data[k] - 1];
  }
  emxFree_int32_T(&readIdx);
  if (qY != 0) {
    if ((numRowsCast >= 0) && (qY < numRowsCast - MAX_int32_T)) {
      b_qY = MAX_int32_T;
    } else if ((numRowsCast < 0) && (qY > numRowsCast - MIN_int32_T)) {
      b_qY = MIN_int32_T;
    } else {
      b_qY = numRowsCast - qY;
    }
    if (b_qY > 2147483646) {
      b_qY = MAX_int32_T;
    } else {
      b_qY++;
    }
    if (b_qY > numRowsCast) {
      b_qY = 1;
    }
    for (k = 0; k < qY; k++) {
      yk = (b_qY + k) - 1;
      out_data[yk].re = 0.0F;
      out_data[yk].im = 0.0F;
    }
  }
  *underrun = qY;
}

/*
 * Arguments    : const e_dsp_internal_AsyncBuffercgHel *obj
 *                int numRowsCast
 *                emxArray_real_T *out
 *                int *underrun
 *                int *c
 * Return Type  : void
 */
void e_AsyncBuffercgHelper_ReadSampl(const e_dsp_internal_AsyncBuffercgHel *obj,
                                     int numRowsCast, emxArray_real_T *out,
                                     int *underrun, int *c)
{
  emxArray_int32_T *r;
  emxArray_int32_T *readIdx;
  emxArray_int32_T *y;
  double *out_data;
  int b_qY;
  int k;
  int qY;
  int rPtr;
  int wPtr;
  int yk;
  int *r1;
  int *readIdx_data;
  int *y_data;
  wPtr = obj->WritePointer;
  qY = 0;
  yk = obj->ReadPointer;
  if (yk > 2147483646) {
    rPtr = MAX_int32_T;
  } else {
    rPtr = yk + 1;
  }
  if (rPtr > 5800321) {
    rPtr = 1;
  }
  if ((rPtr < 0) && (numRowsCast < MIN_int32_T - rPtr)) {
    b_qY = MIN_int32_T;
  } else if ((rPtr > 0) && (numRowsCast > MAX_int32_T - rPtr)) {
    b_qY = MAX_int32_T;
  } else {
    b_qY = rPtr + numRowsCast;
  }
  if (b_qY < -2147483647) {
    b_qY = MIN_int32_T;
  } else {
    b_qY--;
  }
  *c = b_qY;
  emxInit_int32_T(&readIdx, 2);
  if (b_qY > 5800321) {
    *c = b_qY - 5800321;
    emxInit_int32_T(&y, 2);
    k = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = b_qY - 5800321;
    emxEnsureCapacity_int32_T(y, k);
    y_data = y->data;
    y_data[0] = 1;
    yk = 1;
    for (k = 2; k <= *c; k++) {
      yk++;
      y_data[k - 1] = yk;
    }
    emxInit_int32_T(&r, 2);
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
    emxFree_int32_T(&r);
    emxFree_int32_T(&y);
    if (rPtr <= wPtr) {
      if (wPtr < -2141683326) {
        qY = MAX_int32_T;
      } else {
        qY = 5800321 - wPtr;
      }
      if (qY > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY++;
      }
      if ((qY < 0) && (b_qY - 5800321 < MIN_int32_T - qY)) {
        qY = MIN_int32_T;
      } else if ((qY > 0) && (b_qY - 5800321 > MAX_int32_T - qY)) {
        qY = MAX_int32_T;
      } else {
        qY = (qY + b_qY) - 5800321;
      }
    } else if (wPtr <= b_qY - 5800321) {
      if (wPtr < b_qY + 2141683328) {
        b_qY = MAX_int32_T;
      } else {
        b_qY = (b_qY - wPtr) - 5800321;
      }
      if (b_qY > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY = b_qY + 1;
      }
    }
  } else {
    int n;
    if (b_qY < rPtr) {
      n = 0;
    } else {
      n = (b_qY - rPtr) + 1;
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
    if ((rPtr <= wPtr) && (wPtr <= b_qY)) {
      if ((b_qY >= 0) && (wPtr < b_qY - MAX_int32_T)) {
        b_qY = MAX_int32_T;
      } else if ((b_qY < 0) && (wPtr > b_qY - MIN_int32_T)) {
        b_qY = MIN_int32_T;
      } else {
        b_qY -= wPtr;
      }
      if (b_qY > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY = b_qY + 1;
      }
    }
  }
  k = out->size[0];
  out->size[0] = readIdx->size[1];
  emxEnsureCapacity_real_T(out, k);
  out_data = out->data;
  yk = readIdx->size[1];
  for (k = 0; k < yk; k++) {
    out_data[k] = obj->Cache[readIdx_data[k] - 1];
  }
  emxFree_int32_T(&readIdx);
  if (qY != 0) {
    if ((numRowsCast >= 0) && (qY < numRowsCast - MAX_int32_T)) {
      b_qY = MAX_int32_T;
    } else if ((numRowsCast < 0) && (qY > numRowsCast - MIN_int32_T)) {
      b_qY = MIN_int32_T;
    } else {
      b_qY = numRowsCast - qY;
    }
    if (b_qY > 2147483646) {
      b_qY = MAX_int32_T;
    } else {
      b_qY++;
    }
    if (b_qY > numRowsCast) {
      b_qY = 1;
    }
    for (k = 0; k < qY; k++) {
      out_data[(b_qY + k) - 1] = 0.0;
    }
  }
  *underrun = qY;
}

/*
 * File trailer for AsyncBuffercgHelper.c
 *
 * [EOF]
 */
