/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: computeDFT.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "computeDFT.h"
#include "FFTImplementationCallback.h"
#include "psdfreqvec.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include <math.h>

/* Function Definitions */
/*
 * Arguments    : const emxArray_creal32_T *xin
 *                double nfft
 *                double varargin_1
 *                emxArray_creal32_T *Xx
 *                emxArray_real_T *f
 * Return Type  : void
 */
void computeDFT(const emxArray_creal32_T *xin, double nfft, double varargin_1,
                emxArray_creal32_T *Xx, emxArray_real_T *f)
{
  emxArray_creal32_T *wrappedData;
  emxArray_creal32_T *x;
  emxArray_creal32_T *xw;
  emxArray_real32_T *costab;
  emxArray_real32_T *costab1q;
  emxArray_real32_T *sintab;
  emxArray_real32_T *sintabinv;
  const creal32_T *xin_data;
  creal32_T *wrappedData_data;
  creal32_T *x_data;
  creal32_T *xw_data;
  float *costab1q_data;
  float *costab_data;
  float *sintab_data;
  float *sintabinv_data;
  int b_j;
  int b_remainder;
  int i;
  int i1;
  int j;
  int k;
  int loop_ub_tmp;
  int nd2;
  xin_data = xin->data;
  emxInit_creal32_T(&xw, 2);
  loop_ub_tmp = (int)nfft;
  i = xw->size[0] * xw->size[1];
  xw->size[0] = (int)nfft;
  xw->size[1] = xin->size[1];
  emxEnsureCapacity_creal32_T(xw, i);
  xw_data = xw->data;
  nd2 = (int)nfft * xin->size[1];
  for (i = 0; i < nd2; i++) {
    xw_data[i].re = 0.0F;
    xw_data[i].im = 0.0F;
  }
  if (xin->size[0] > nfft) {
    i = xin->size[1];
    emxInit_creal32_T(&wrappedData, 2);
    emxInit_creal32_T(&x, 1);
    for (j = 0; j < i; j++) {
      nd2 = xin->size[0];
      i1 = x->size[0];
      x->size[0] = xin->size[0];
      emxEnsureCapacity_creal32_T(x, i1);
      x_data = x->data;
      for (i1 = 0; i1 < nd2; i1++) {
        x_data[i1] = xin_data[i1 + xin->size[0] * j];
      }
      if (xin->size[0] == 1) {
        i1 = wrappedData->size[0] * wrappedData->size[1];
        wrappedData->size[0] = 1;
        wrappedData->size[1] = (int)nfft;
        emxEnsureCapacity_creal32_T(wrappedData, i1);
        wrappedData_data = wrappedData->data;
        for (i1 = 0; i1 < loop_ub_tmp; i1++) {
          wrappedData_data[i1].re = 0.0F;
          wrappedData_data[i1].im = 0.0F;
        }
      } else {
        i1 = wrappedData->size[0] * wrappedData->size[1];
        wrappedData->size[0] = (int)nfft;
        wrappedData->size[1] = 1;
        emxEnsureCapacity_creal32_T(wrappedData, i1);
        wrappedData_data = wrappedData->data;
        for (i1 = 0; i1 < loop_ub_tmp; i1++) {
          wrappedData_data[i1].re = 0.0F;
          wrappedData_data[i1].im = 0.0F;
        }
      }
      if ((unsigned int)nfft == 0U) {
        i1 = MAX_int32_T;
      } else {
        i1 = (int)((unsigned int)xin->size[0] / (unsigned int)nfft);
      }
      nd2 = i1 * (int)nfft;
      b_remainder = (xin->size[0] - nd2) - 1;
      for (k = 0; k <= b_remainder; k++) {
        wrappedData_data[k] = x_data[nd2 + k];
      }
      nd2 = b_remainder + 2;
      for (k = nd2; k <= loop_ub_tmp; k++) {
        wrappedData_data[k - 1].re = 0.0F;
        wrappedData_data[k - 1].im = 0.0F;
      }
      for (b_j = 0; b_j < i1; b_j++) {
        b_remainder = b_j * (int)nfft;
        for (k = 0; k < loop_ub_tmp; k++) {
          nd2 = b_remainder + k;
          wrappedData_data[k].re += x_data[nd2].re;
          wrappedData_data[k].im += x_data[nd2].im;
        }
      }
      nd2 = wrappedData->size[0] * wrappedData->size[1];
      for (i1 = 0; i1 < nd2; i1++) {
        xw_data[i1 + xw->size[0] * j] = wrappedData_data[i1];
      }
    }
    emxFree_creal32_T(&x);
    emxFree_creal32_T(&wrappedData);
  } else {
    i = xw->size[0] * xw->size[1];
    xw->size[0] = xin->size[0];
    xw->size[1] = xin->size[1];
    emxEnsureCapacity_creal32_T(xw, i);
    xw_data = xw->data;
    nd2 = xin->size[0] * xin->size[1];
    for (i = 0; i < nd2; i++) {
      xw_data[i] = xin_data[i];
    }
  }
  emxInit_real32_T(&costab1q, 2);
  emxInit_real32_T(&costab, 2);
  emxInit_real32_T(&sintab, 2);
  emxInit_real32_T(&sintabinv, 2);
  if ((xw->size[0] == 0) || (xw->size[1] == 0) || ((int)nfft == 0)) {
    i = Xx->size[0] * Xx->size[1];
    Xx->size[0] = (int)nfft;
    Xx->size[1] = xw->size[1];
    emxEnsureCapacity_creal32_T(Xx, i);
    xw_data = Xx->data;
    nd2 = (int)nfft * xw->size[1];
    for (i = 0; i < nd2; i++) {
      xw_data[i].re = 0.0F;
      xw_data[i].im = 0.0F;
    }
  } else {
    float e;
    bool useRadix2;
    useRadix2 = (((int)nfft > 0) && (((int)nfft & ((int)nfft - 1)) == 0));
    c_FFTImplementationCallback_get((int)nfft, useRadix2, &loop_ub_tmp, &nd2);
    e = 6.28318548F / (float)nd2;
    b_remainder = nd2 / 2 / 2;
    i = costab1q->size[0] * costab1q->size[1];
    costab1q->size[0] = 1;
    costab1q->size[1] = b_remainder + 1;
    emxEnsureCapacity_real32_T(costab1q, i);
    costab1q_data = costab1q->data;
    costab1q_data[0] = 1.0F;
    nd2 = b_remainder / 2 - 1;
    for (k = 0; k <= nd2; k++) {
      costab1q_data[k + 1] = cosf(e * (float)(k + 1));
    }
    i = nd2 + 2;
    i1 = b_remainder - 1;
    for (k = i; k <= i1; k++) {
      costab1q_data[k] = sinf(e * (float)(b_remainder - k));
    }
    costab1q_data[b_remainder] = 0.0F;
    if (!useRadix2) {
      b_remainder = costab1q->size[1] - 1;
      nd2 = (costab1q->size[1] - 1) << 1;
      i = costab->size[0] * costab->size[1];
      costab->size[0] = 1;
      costab->size[1] = nd2 + 1;
      emxEnsureCapacity_real32_T(costab, i);
      costab_data = costab->data;
      i = sintab->size[0] * sintab->size[1];
      sintab->size[0] = 1;
      sintab->size[1] = nd2 + 1;
      emxEnsureCapacity_real32_T(sintab, i);
      sintab_data = sintab->data;
      costab_data[0] = 1.0F;
      sintab_data[0] = 0.0F;
      i = sintabinv->size[0] * sintabinv->size[1];
      sintabinv->size[0] = 1;
      sintabinv->size[1] = nd2 + 1;
      emxEnsureCapacity_real32_T(sintabinv, i);
      sintabinv_data = sintabinv->data;
      for (k = 0; k < b_remainder; k++) {
        sintabinv_data[k + 1] = costab1q_data[(b_remainder - k) - 1];
      }
      i = costab1q->size[1];
      for (k = i; k <= nd2; k++) {
        sintabinv_data[k] = costab1q_data[k - b_remainder];
      }
      for (k = 0; k < b_remainder; k++) {
        costab_data[k + 1] = costab1q_data[k + 1];
        sintab_data[k + 1] = -costab1q_data[(b_remainder - k) - 1];
      }
      i = costab1q->size[1];
      for (k = i; k <= nd2; k++) {
        costab_data[k] = -costab1q_data[nd2 - k];
        sintab_data[k] = -costab1q_data[k - b_remainder];
      }
    } else {
      b_remainder = costab1q->size[1] - 1;
      nd2 = (costab1q->size[1] - 1) << 1;
      i = costab->size[0] * costab->size[1];
      costab->size[0] = 1;
      costab->size[1] = nd2 + 1;
      emxEnsureCapacity_real32_T(costab, i);
      costab_data = costab->data;
      i = sintab->size[0] * sintab->size[1];
      sintab->size[0] = 1;
      sintab->size[1] = nd2 + 1;
      emxEnsureCapacity_real32_T(sintab, i);
      sintab_data = sintab->data;
      costab_data[0] = 1.0F;
      sintab_data[0] = 0.0F;
      for (k = 0; k < b_remainder; k++) {
        costab_data[k + 1] = costab1q_data[k + 1];
        sintab_data[k + 1] = -costab1q_data[(b_remainder - k) - 1];
      }
      i = costab1q->size[1];
      for (k = i; k <= nd2; k++) {
        costab_data[k] = -costab1q_data[nd2 - k];
        sintab_data[k] = -costab1q_data[k - b_remainder];
      }
      sintabinv->size[0] = 1;
      sintabinv->size[1] = 0;
    }
    if (useRadix2) {
      c_FFTImplementationCallback_r2b(xw, (int)nfft, costab, sintab, Xx);
    } else {
      c_FFTImplementationCallback_dob(xw, loop_ub_tmp, (int)nfft, costab,
                                      sintab, sintabinv, Xx);
    }
  }
  emxFree_real32_T(&sintabinv);
  emxFree_real32_T(&sintab);
  emxFree_real32_T(&costab);
  emxFree_real32_T(&costab1q);
  emxFree_creal32_T(&xw);
  psdfreqvec(nfft, varargin_1, f);
}

/*
 * File trailer for computeDFT.c
 *
 * [EOF]
 */
