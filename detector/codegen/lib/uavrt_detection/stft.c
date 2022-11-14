/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: stft.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "stft.h"
#include "FFTImplementationCallback.h"
#include "computeDFT.h"
#include "psdfreqvec.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_internal_types.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include <math.h>

/* Function Definitions */
/*
 * Arguments    : const emxArray_creal_T *x
 *                double c_opts_next_next_next_next_next
 *                double d_opts_next_next_next_next_next
 *                double e_opts_next_next_next_next_next
 *                const emxArray_real_T *f_opts_next_next_next_next_next
 *                const h_coder_internal_stickyStruct
 * g_opts_next_next_next_next_next emxArray_creal_T *S emxArray_real_T *F
 *                emxArray_real_T *T
 * Return Type  : void
 */
void computeSTFT(
    const emxArray_creal_T *x, double c_opts_next_next_next_next_next,
    double d_opts_next_next_next_next_next,
    double e_opts_next_next_next_next_next,
    const emxArray_real_T *f_opts_next_next_next_next_next,
    const h_coder_internal_stickyStruct g_opts_next_next_next_next_next,
    emxArray_creal_T *S, emxArray_real_T *F, emxArray_real_T *T)
{
  emxArray_creal_T *b_x;
  emxArray_creal_T *buffer;
  emxArray_creal_T *c;
  emxArray_creal_T *c_x;
  emxArray_creal_T *wrappedData;
  emxArray_creal_T *xin;
  emxArray_real_T *costab;
  emxArray_real_T *f;
  emxArray_real_T *sintab;
  emxArray_real_T *sintabinv;
  emxArray_real_T *y;
  const creal_T *x_data;
  creal_T *S_data;
  creal_T *b_x_data;
  creal_T *wrappedData_data;
  creal_T *xin_data;
  const double *h_opts_next_next_next_next_next;
  double hopSize;
  double nCol;
  double xtmp_im;
  double *F_data;
  double *T_data;
  double *y_data;
  int acoef;
  int b_bcoef;
  int b_i;
  int b_i1;
  int bcoef;
  int c_bcoef;
  int i;
  int i1;
  int i2;
  int ib;
  int j;
  int k;
  int npages;
  int varargin_5;
  bool useRadix2;
  h_opts_next_next_next_next_next = f_opts_next_next_next_next_next->data;
  x_data = x->data;
  hopSize = e_opts_next_next_next_next_next - d_opts_next_next_next_next_next;
  nCol = trunc((g_opts_next_next_next_next_next.next.next.next.next.next.next
                    .next.value -
                d_opts_next_next_next_next_next) /
               hopSize);
  emxInit_creal_T(&xin, 3);
  i = xin->size[0] * xin->size[1] * xin->size[2];
  xin->size[0] = (int)e_opts_next_next_next_next_next;
  i1 = (int)nCol;
  xin->size[1] = (int)nCol;
  xin->size[2] = x->size[1];
  emxEnsureCapacity_creal_T(xin, i);
  xin_data = xin->data;
  acoef = (int)e_opts_next_next_next_next_next * (int)nCol * x->size[1];
  for (i = 0; i < acoef; i++) {
    xin_data[i].re = 0.0;
    xin_data[i].im = 0.0;
  }
  emxInit_real_T(&y, 2);
  if (nCol - 1.0 < 0.0) {
    y->size[1] = 0;
  } else {
    i = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = (int)(nCol - 1.0) + 1;
    emxEnsureCapacity_real_T(y, i);
    y_data = y->data;
    acoef = (int)(nCol - 1.0);
    for (i = 0; i <= acoef; i++) {
      y_data[i] = i;
    }
  }
  if ((int)nCol - 1 >= 0) {
    bcoef = x->size[1];
  }
  emxInit_creal_T(&b_x, 2);
  for (ib = 0; ib < i1; ib++) {
    nCol = hopSize * (((double)ib + 1.0) - 1.0);
    xtmp_im = e_opts_next_next_next_next_next + nCol;
    if (nCol + 1.0 > xtmp_im) {
      i = 0;
      i2 = 0;
    } else {
      i = (int)(nCol + 1.0) - 1;
      i2 = (int)xtmp_im;
    }
    acoef = i2 - i;
    i2 = b_x->size[0] * b_x->size[1];
    b_x->size[0] = acoef;
    b_x->size[1] = x->size[1];
    emxEnsureCapacity_creal_T(b_x, i2);
    b_x_data = b_x->data;
    for (i2 = 0; i2 < bcoef; i2++) {
      for (b_i = 0; b_i < acoef; b_i++) {
        b_x_data[b_i + b_x->size[0] * i2] = x_data[(i + b_i) + x->size[0] * i2];
      }
    }
    b_bcoef = xin->size[0];
    acoef = xin->size[2];
    for (i = 0; i < acoef; i++) {
      for (i2 = 0; i2 < b_bcoef; i2++) {
        xin_data[(i2 + xin->size[0] * ib) + xin->size[0] * xin->size[1] * i] =
            b_x_data[i2 + b_bcoef * i];
      }
    }
  }
  emxFree_creal_T(&b_x);
  i = y->size[0] * y->size[1];
  y->size[0] = 1;
  emxEnsureCapacity_real_T(y, i);
  y_data = y->data;
  nCol = e_opts_next_next_next_next_next / 2.0;
  acoef = y->size[1] - 1;
  for (i = 0; i <= acoef; i++) {
    y_data[i] =
        (y_data[i] * hopSize + nCol) / g_opts_next_next_next_next_next.value;
  }
  emxInit_creal_T(&c, 3);
  i = c->size[0] * c->size[1] * c->size[2];
  b_bcoef = xin->size[0];
  bcoef = f_opts_next_next_next_next_next->size[0];
  if (b_bcoef <= bcoef) {
    bcoef = b_bcoef;
  }
  if (xin->size[0] == 1) {
    c->size[0] = f_opts_next_next_next_next_next->size[0];
  } else if (f_opts_next_next_next_next_next->size[0] == 1) {
    c->size[0] = xin->size[0];
  } else if (f_opts_next_next_next_next_next->size[0] == xin->size[0]) {
    c->size[0] = f_opts_next_next_next_next_next->size[0];
  } else {
    c->size[0] = bcoef;
  }
  c->size[1] = xin->size[1];
  c->size[2] = xin->size[2];
  emxEnsureCapacity_creal_T(c, i);
  S_data = c->data;
  b_bcoef = xin->size[0];
  bcoef = f_opts_next_next_next_next_next->size[0];
  if (b_bcoef <= bcoef) {
    bcoef = b_bcoef;
  }
  if (xin->size[0] == 1) {
    bcoef = f_opts_next_next_next_next_next->size[0];
  } else if (f_opts_next_next_next_next_next->size[0] == 1) {
    bcoef = xin->size[0];
  } else if (f_opts_next_next_next_next_next->size[0] == xin->size[0]) {
    bcoef = f_opts_next_next_next_next_next->size[0];
  }
  if ((bcoef != 0) && (xin->size[1] != 0)) {
    b_bcoef = (xin->size[2] != 1);
    i = xin->size[2] - 1;
    bcoef = (xin->size[1] != 1);
    acoef = (f_opts_next_next_next_next_next->size[0] != 1);
    c_bcoef = (xin->size[0] != 1);
    i1 = c->size[1] - 1;
    i2 = c->size[0] - 1;
    for (k = 0; k <= i; k++) {
      ib = b_bcoef * k;
      for (b_i1 = 0; b_i1 <= i1; b_i1++) {
        varargin_5 = bcoef * b_i1;
        for (npages = 0; npages <= i2; npages++) {
          b_i = c_bcoef * npages;
          nCol = h_opts_next_next_next_next_next[acoef * npages];
          S_data[(npages + c->size[0] * b_i1) + c->size[0] * c->size[1] * k]
              .re = nCol * xin_data[(b_i + xin->size[0] * varargin_5) +
                                    xin->size[0] * xin->size[1] * ib]
                               .re;
          S_data[(npages + c->size[0] * b_i1) + c->size[0] * c->size[1] * k]
              .im = nCol * xin_data[(b_i + xin->size[0] * varargin_5) +
                                    xin->size[0] * xin->size[1] * ib]
                               .im;
        }
      }
    }
  }
  ib = (int)c_opts_next_next_next_next_next;
  i = xin->size[0] * xin->size[1] * xin->size[2];
  xin->size[0] = (int)c_opts_next_next_next_next_next;
  xin->size[1] = c->size[1];
  xin->size[2] = c->size[2];
  emxEnsureCapacity_creal_T(xin, i);
  xin_data = xin->data;
  acoef = (int)c_opts_next_next_next_next_next * c->size[1] * c->size[2];
  for (i = 0; i < acoef; i++) {
    xin_data[i].re = 0.0;
    xin_data[i].im = 0.0;
  }
  if (c->size[0] > c_opts_next_next_next_next_next) {
    i = c->size[1] * c->size[2];
    emxInit_creal_T(&wrappedData, 2);
    emxInit_creal_T(&c_x, 1);
    for (j = 0; j < i; j++) {
      acoef = c->size[0];
      bcoef = c->size[0];
      i1 = c_x->size[0];
      c_x->size[0] = c->size[0];
      emxEnsureCapacity_creal_T(c_x, i1);
      b_x_data = c_x->data;
      for (i1 = 0; i1 < acoef; i1++) {
        b_x_data[i1] = S_data[i1 + bcoef * j];
      }
      if (c->size[0] == 1) {
        i1 = wrappedData->size[0] * wrappedData->size[1];
        wrappedData->size[0] = 1;
        wrappedData->size[1] = (int)c_opts_next_next_next_next_next;
        emxEnsureCapacity_creal_T(wrappedData, i1);
        wrappedData_data = wrappedData->data;
        for (i1 = 0; i1 < ib; i1++) {
          wrappedData_data[i1].re = 0.0;
          wrappedData_data[i1].im = 0.0;
        }
      } else {
        i1 = wrappedData->size[0] * wrappedData->size[1];
        wrappedData->size[0] = (int)c_opts_next_next_next_next_next;
        wrappedData->size[1] = 1;
        emxEnsureCapacity_creal_T(wrappedData, i1);
        wrappedData_data = wrappedData->data;
        for (i1 = 0; i1 < ib; i1++) {
          wrappedData_data[i1].re = 0.0;
          wrappedData_data[i1].im = 0.0;
        }
      }
      if ((unsigned int)c_opts_next_next_next_next_next == 0U) {
        i1 = MAX_int32_T;
      } else {
        i1 = (int)((unsigned int)c->size[0] /
                   (unsigned int)c_opts_next_next_next_next_next);
      }
      bcoef = i1 * (int)c_opts_next_next_next_next_next;
      b_bcoef = (c->size[0] - bcoef) - 1;
      for (k = 0; k <= b_bcoef; k++) {
        wrappedData_data[k] = b_x_data[bcoef + k];
      }
      i2 = b_bcoef + 2;
      for (k = i2; k <= ib; k++) {
        wrappedData_data[k - 1].re = 0.0;
        wrappedData_data[k - 1].im = 0.0;
      }
      for (bcoef = 0; bcoef < i1; bcoef++) {
        b_bcoef = bcoef * (int)c_opts_next_next_next_next_next;
        for (k = 0; k < ib; k++) {
          i2 = b_bcoef + k;
          wrappedData_data[k].re += b_x_data[i2].re;
          wrappedData_data[k].im += b_x_data[i2].im;
        }
      }
      b_bcoef = wrappedData->size[0] * wrappedData->size[1];
      bcoef = xin->size[0];
      for (i1 = 0; i1 < b_bcoef; i1++) {
        xin_data[i1 + bcoef * j] = wrappedData_data[i1];
      }
    }
    emxFree_creal_T(&c_x);
    emxFree_creal_T(&wrappedData);
  } else {
    i = xin->size[0] * xin->size[1] * xin->size[2];
    xin->size[0] = c->size[0];
    xin->size[1] = c->size[1];
    xin->size[2] = c->size[2];
    emxEnsureCapacity_creal_T(xin, i);
    xin_data = xin->data;
    acoef = c->size[0] * c->size[1] * c->size[2];
    for (i = 0; i < acoef; i++) {
      xin_data[i] = S_data[i];
    }
  }
  emxFree_creal_T(&c);
  emxInit_real_T(&costab, 2);
  emxInit_real_T(&sintab, 2);
  emxInit_real_T(&sintabinv, 2);
  if ((xin->size[0] == 0) || (xin->size[1] == 0) ||
      ((int)c_opts_next_next_next_next_next == 0)) {
    i = S->size[0] * S->size[1] * S->size[2];
    S->size[0] = (int)c_opts_next_next_next_next_next;
    S->size[1] = xin->size[1];
    S->size[2] = xin->size[2];
    emxEnsureCapacity_creal_T(S, i);
    S_data = S->data;
    acoef = (int)c_opts_next_next_next_next_next * xin->size[1] * xin->size[2];
    for (i = 0; i < acoef; i++) {
      S_data[i].re = 0.0;
      S_data[i].im = 0.0;
    }
  } else {
    useRadix2 = (((int)c_opts_next_next_next_next_next > 0) &&
                 (((int)c_opts_next_next_next_next_next &
                   ((int)c_opts_next_next_next_next_next - 1)) == 0));
    c_FFTImplementationCallback_get((int)c_opts_next_next_next_next_next,
                                    useRadix2, &b_bcoef, &bcoef);
    c_FFTImplementationCallback_gen(bcoef, useRadix2, costab, sintab,
                                    sintabinv);
    if (useRadix2) {
      g_FFTImplementationCallback_r2b(xin, (int)c_opts_next_next_next_next_next,
                                      costab, sintab, S);
      S_data = S->data;
    } else {
      e_FFTImplementationCallback_dob(xin, b_bcoef,
                                      (int)c_opts_next_next_next_next_next,
                                      costab, sintab, sintabinv, S);
      S_data = S->data;
    }
  }
  emxFree_real_T(&sintabinv);
  emxFree_real_T(&sintab);
  emxFree_real_T(&costab);
  emxFree_creal_T(&xin);
  emxInit_real_T(&f, 1);
  psdfreqvec(c_opts_next_next_next_next_next,
             g_opts_next_next_next_next_next.value, f);
  T_data = f->data;
  if (S->size[0] == 0) {
    hopSize = 0.0;
  } else {
    hopSize = fmod(S->size[0], 2.0);
  }
  if (hopSize == 0.0) {
    nCol = (double)S->size[0] / 2.0 - 1.0;
    bcoef = 1;
    if (S->size[0] != 1) {
      bcoef = 0;
    } else if ((S->size[1] == 1) && (S->size[2] != 1)) {
      bcoef = 2;
    }
    emxInit_creal_T(&buffer, 2);
    if ((S->size[0] != 0) && (S->size[1] != 0) &&
        ((S->size[0] != 1) || (S->size[1] != 1) || (S->size[2] != 1))) {
      if (nCol < 0.0) {
        varargin_5 = -(int)nCol;
        useRadix2 = false;
      } else {
        varargin_5 = (int)nCol;
        useRadix2 = true;
      }
      if (S->size[bcoef] <= 1) {
        varargin_5 = 0;
      } else {
        if (varargin_5 > S->size[bcoef]) {
          unsigned int u;
          u = (unsigned int)S->size[bcoef];
          if (u == 0U) {
            i = MAX_int32_T;
          } else {
            i = (int)((unsigned int)varargin_5 / u);
          }
          varargin_5 -= S->size[bcoef] * i;
        }
        if (varargin_5 > (S->size[bcoef] >> 1)) {
          varargin_5 = S->size[bcoef] - varargin_5;
          useRadix2 = !useRadix2;
        }
      }
      b_bcoef = S->size[0];
      if (S->size[1] > S->size[0]) {
        b_bcoef = S->size[1];
      }
      if (S->size[2] > b_bcoef) {
        b_bcoef = S->size[2];
      }
      b_bcoef /= 2;
      i = buffer->size[0] * buffer->size[1];
      buffer->size[0] = 1;
      buffer->size[1] = b_bcoef;
      emxEnsureCapacity_creal_T(buffer, i);
      wrappedData_data = buffer->data;
      for (i = 0; i < b_bcoef; i++) {
        wrappedData_data[i].re = 0.0;
        wrappedData_data[i].im = 0.0;
      }
      i = S->size[bcoef];
      acoef = S->size[bcoef];
      c_bcoef = 1;
      for (k = 0; k < bcoef; k++) {
        c_bcoef *= S->size[k];
      }
      npages = 1;
      b_bcoef = bcoef + 2;
      for (k = b_bcoef; k < 4; k++) {
        npages *= S->size[k - 1];
      }
      ib = c_bcoef * S->size[bcoef];
      if ((S->size[bcoef] > 1) && (varargin_5 > 0)) {
        for (b_i = 0; b_i < npages; b_i++) {
          b_bcoef = b_i * ib;
          for (j = 0; j < c_bcoef; j++) {
            b_i1 = b_bcoef + j;
            if (useRadix2) {
              for (k = 0; k < varargin_5; k++) {
                wrappedData_data[k] =
                    S_data[b_i1 + ((k + i) - varargin_5) * c_bcoef];
              }
              i1 = varargin_5 + 1;
              for (k = acoef; k >= i1; k--) {
                S_data[b_i1 + (k - 1) * c_bcoef] =
                    S_data[b_i1 + ((k - varargin_5) - 1) * c_bcoef];
              }
              for (k = 0; k < varargin_5; k++) {
                S_data[b_i1 + k * c_bcoef] = wrappedData_data[k];
              }
            } else {
              for (k = 0; k < varargin_5; k++) {
                wrappedData_data[k] = S_data[b_i1 + k * c_bcoef];
              }
              i1 = (i - varargin_5) - 1;
              for (k = 0; k <= i1; k++) {
                S_data[b_i1 + k * c_bcoef] =
                    S_data[b_i1 + (k + varargin_5) * c_bcoef];
              }
              for (k = 0; k < varargin_5; k++) {
                S_data[b_i1 + ((k + i) - varargin_5) * c_bcoef] =
                    wrappedData_data[k];
              }
            }
          }
        }
      }
    }
    emxFree_creal_T(&buffer);
  } else if (S->size[0] > 1) {
    bcoef = (int)((unsigned int)S->size[0] >> 1) - 1;
    npages = S->size[1] * S->size[2] - 1;
    acoef = S->size[0];
    if ((bcoef + 1) << 1 == S->size[0]) {
      c_bcoef = 1;
      for (b_i = 0; b_i <= npages; b_i++) {
        b_i1 = c_bcoef;
        c_bcoef += acoef;
        ib = b_i1 + bcoef;
        for (k = 0; k <= bcoef; k++) {
          b_bcoef = (b_i1 + k) - 1;
          nCol = S_data[b_bcoef].re;
          xtmp_im = S_data[b_bcoef].im;
          i = ib + k;
          S_data[b_bcoef] = S_data[i];
          S_data[i].re = nCol;
          S_data[i].im = xtmp_im;
        }
      }
    } else {
      c_bcoef = 1;
      for (b_i = 0; b_i <= npages; b_i++) {
        b_i1 = c_bcoef;
        c_bcoef += acoef;
        ib = b_i1 + bcoef;
        nCol = S_data[ib].re;
        xtmp_im = S_data[ib].im;
        for (k = 0; k <= bcoef; k++) {
          i = ib + k;
          i1 = (b_i1 + k) - 1;
          S_data[i] = S_data[i1];
          S_data[i1] = S_data[i + 1];
        }
        ib = (ib + bcoef) + 1;
        S_data[ib].re = nCol;
        S_data[ib].im = xtmp_im;
      }
    }
  }
  if (f->size[0] == 0) {
    hopSize = 0.0;
  } else {
    hopSize = fmod(f->size[0], 2.0);
  }
  if (hopSize == 0.0) {
    nCol = T_data[(int)((double)f->size[0] / 2.0) - 1];
    acoef = f->size[0];
    for (i = 0; i < acoef; i++) {
      T_data[i] -= nCol;
    }
  } else {
    nCol = T_data[(int)(((double)f->size[0] + 1.0) / 2.0) - 1];
    acoef = f->size[0];
    for (i = 0; i < acoef; i++) {
      T_data[i] -= nCol;
    }
  }
  if (S->size[0] < 1) {
    acoef = 0;
  } else {
    acoef = S->size[0];
  }
  i = F->size[0];
  F->size[0] = acoef;
  emxEnsureCapacity_real_T(F, i);
  F_data = F->data;
  for (i = 0; i < acoef; i++) {
    F_data[i] = T_data[i];
  }
  emxFree_real_T(&f);
  if (S->size[1] < 1) {
    acoef = 0;
  } else {
    acoef = S->size[1];
  }
  i = T->size[0] * T->size[1];
  T->size[0] = 1;
  T->size[1] = acoef;
  emxEnsureCapacity_real_T(T, i);
  T_data = T->data;
  for (i = 0; i < acoef; i++) {
    T_data[i] = y_data[i];
  }
  emxFree_real_T(&y);
}

/*
 * Arguments    : const emxArray_creal32_T *x
 *                double varargin_1
 *                const emxArray_real_T *varargin_3
 *                double varargin_5
 *                double varargin_7
 *                emxArray_creal32_T *varargout_1
 *                emxArray_real32_T *varargout_2
 *                emxArray_real32_T *varargout_3
 * Return Type  : void
 */
void stft(const emxArray_creal32_T *x, double varargin_1,
          const emxArray_real_T *varargin_3, double varargin_5,
          double varargin_7, emxArray_creal32_T *varargout_1,
          emxArray_real32_T *varargout_2, emxArray_real32_T *varargout_3)
{
  emxArray_creal32_T *buffer;
  emxArray_creal32_T *c;
  emxArray_creal32_T *xin;
  emxArray_real32_T *obj_value;
  emxArray_real32_T *tempT;
  emxArray_real_T *f;
  emxArray_real_T *y;
  const creal32_T *x_data;
  creal32_T *c_data;
  creal32_T *xin_data;
  const double *varargin_3_data;
  double d;
  double hopSize;
  double nCol;
  double *f_data;
  double *y_data;
  float xtmp_re;
  float *obj_value_data;
  float *varargout_3_data;
  int acoef;
  int b_bcoef;
  int b_i;
  int b_i1;
  int bcoef;
  int i;
  int i1;
  int i2;
  int ib;
  int k;
  varargin_3_data = varargin_3->data;
  x_data = x->data;
  emxInit_real32_T(&obj_value, 1);
  i = obj_value->size[0];
  obj_value->size[0] = varargin_3->size[0];
  emxEnsureCapacity_real32_T(obj_value, i);
  obj_value_data = obj_value->data;
  bcoef = varargin_3->size[0];
  for (i = 0; i < bcoef; i++) {
    obj_value_data[i] = (float)varargin_3_data[i];
  }
  hopSize = (double)varargin_3->size[0] - varargin_5;
  nCol = trunc(((double)x->size[1] - varargin_5) / hopSize);
  emxInit_creal32_T(&xin, 2);
  i = xin->size[0] * xin->size[1];
  xin->size[0] = varargin_3->size[0];
  i1 = (int)nCol;
  xin->size[1] = (int)nCol;
  emxEnsureCapacity_creal32_T(xin, i);
  xin_data = xin->data;
  bcoef = varargin_3->size[0] * (int)nCol;
  for (i = 0; i < bcoef; i++) {
    xin_data[i].re = 0.0F;
    xin_data[i].im = 0.0F;
  }
  emxInit_real_T(&y, 2);
  if (nCol - 1.0 < 0.0) {
    y->size[1] = 0;
  } else {
    i = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = (int)(nCol - 1.0) + 1;
    emxEnsureCapacity_real_T(y, i);
    y_data = y->data;
    bcoef = (int)(nCol - 1.0);
    for (i = 0; i <= bcoef; i++) {
      y_data[i] = i;
    }
  }
  for (acoef = 0; acoef < i1; acoef++) {
    nCol = hopSize * (((double)acoef + 1.0) - 1.0);
    d = (double)varargin_3->size[0] + nCol;
    if (nCol + 1.0 > d) {
      i = 0;
      b_i1 = 0;
    } else {
      i = (int)(nCol + 1.0) - 1;
      b_i1 = (int)d;
    }
    bcoef = b_i1 - i;
    for (b_i1 = 0; b_i1 < bcoef; b_i1++) {
      xin_data[b_i1 + xin->size[0] * acoef] = x_data[i + b_i1];
    }
  }
  i = y->size[0] * y->size[1];
  y->size[0] = 1;
  emxEnsureCapacity_real_T(y, i);
  y_data = y->data;
  nCol = (double)varargin_3->size[0] / 2.0;
  bcoef = y->size[1] - 1;
  for (i = 0; i <= bcoef; i++) {
    y_data[i] = (y_data[i] * hopSize + nCol) / varargin_1;
  }
  emxInit_creal32_T(&c, 2);
  i = c->size[0] * c->size[1];
  bcoef = xin->size[0];
  acoef = obj_value->size[0];
  if (bcoef <= acoef) {
    acoef = bcoef;
  }
  if (xin->size[0] == 1) {
    c->size[0] = obj_value->size[0];
  } else if (obj_value->size[0] == 1) {
    c->size[0] = xin->size[0];
  } else if (obj_value->size[0] == xin->size[0]) {
    c->size[0] = obj_value->size[0];
  } else {
    c->size[0] = acoef;
  }
  c->size[1] = xin->size[1];
  emxEnsureCapacity_creal32_T(c, i);
  c_data = c->data;
  bcoef = xin->size[0];
  acoef = obj_value->size[0];
  if (bcoef <= acoef) {
    acoef = bcoef;
  }
  if (xin->size[0] == 1) {
    acoef = obj_value->size[0];
  } else if (obj_value->size[0] == 1) {
    acoef = xin->size[0];
  } else if (obj_value->size[0] == xin->size[0]) {
    acoef = obj_value->size[0];
  }
  if ((acoef != 0) && (xin->size[1] != 0)) {
    bcoef = (xin->size[1] != 1);
    i = xin->size[1] - 1;
    acoef = (obj_value->size[0] != 1);
    b_bcoef = (xin->size[0] != 1);
    i1 = c->size[0] - 1;
    for (k = 0; k <= i; k++) {
      i2 = bcoef * k;
      for (ib = 0; ib <= i1; ib++) {
        b_i1 = b_bcoef * ib;
        xtmp_re = obj_value_data[acoef * ib];
        c_data[ib + c->size[0] * k].re =
            xtmp_re * xin_data[b_i1 + xin->size[0] * i2].re;
        c_data[ib + c->size[0] * k].im =
            xtmp_re * xin_data[b_i1 + xin->size[0] * i2].im;
      }
    }
  }
  emxFree_creal32_T(&xin);
  emxFree_real32_T(&obj_value);
  emxInit_real_T(&f, 1);
  computeDFT(c, varargin_7, varargin_1, varargout_1, f);
  f_data = f->data;
  c_data = varargout_1->data;
  emxFree_creal32_T(&c);
  if (varargout_1->size[0] == 0) {
    d = 0.0;
  } else {
    d = fmod(varargout_1->size[0], 2.0);
  }
  if (d == 0.0) {
    nCol = (double)varargout_1->size[0] / 2.0 - 1.0;
    b_bcoef = 1;
    if (varargout_1->size[0] != 1) {
      b_bcoef = 0;
    }
    if ((varargout_1->size[0] != 0) && (varargout_1->size[1] != 0) &&
        ((varargout_1->size[0] != 1) || (varargout_1->size[1] != 1))) {
      int npages;
      int ns;
      bool shiftright;
      if (nCol < 0.0) {
        ns = -(int)nCol;
        shiftright = false;
      } else {
        ns = (int)nCol;
        shiftright = true;
      }
      if (varargout_1->size[b_bcoef] <= 1) {
        ns = 0;
      } else {
        if (ns > varargout_1->size[b_bcoef]) {
          ns -= varargout_1->size[b_bcoef] *
                div_s32(ns, varargout_1->size[b_bcoef]);
        }
        if (ns > (varargout_1->size[b_bcoef] >> 1)) {
          ns = varargout_1->size[b_bcoef] - ns;
          shiftright = !shiftright;
        }
      }
      bcoef = varargout_1->size[0];
      acoef = varargout_1->size[1];
      if (bcoef >= acoef) {
        acoef = bcoef;
      }
      bcoef = acoef / 2;
      emxInit_creal32_T(&buffer, 2);
      i = buffer->size[0] * buffer->size[1];
      buffer->size[0] = 1;
      buffer->size[1] = bcoef;
      emxEnsureCapacity_creal32_T(buffer, i);
      xin_data = buffer->data;
      for (i = 0; i < bcoef; i++) {
        xin_data[i].re = 0.0F;
        xin_data[i].im = 0.0F;
      }
      i = varargout_1->size[b_bcoef];
      i2 = varargout_1->size[b_bcoef];
      ib = 1;
      for (k = 0; k < b_bcoef; k++) {
        ib *= varargout_1->size[0];
      }
      npages = 1;
      bcoef = b_bcoef + 2;
      for (k = bcoef; k < 3; k++) {
        npages *= varargout_1->size[1];
      }
      acoef = ib * varargout_1->size[b_bcoef];
      if ((varargout_1->size[b_bcoef] > 1) && (ns > 0)) {
        for (b_i = 0; b_i < npages; b_i++) {
          bcoef = b_i * acoef;
          for (b_bcoef = 0; b_bcoef < ib; b_bcoef++) {
            b_i1 = bcoef + b_bcoef;
            if (shiftright) {
              for (k = 0; k < ns; k++) {
                xin_data[k] = c_data[b_i1 + ((k + i) - ns) * ib];
              }
              i1 = ns + 1;
              for (k = i2; k >= i1; k--) {
                c_data[b_i1 + (k - 1) * ib] =
                    c_data[b_i1 + ((k - ns) - 1) * ib];
              }
              for (k = 0; k < ns; k++) {
                c_data[b_i1 + k * ib] = xin_data[k];
              }
            } else {
              for (k = 0; k < ns; k++) {
                xin_data[k] = c_data[b_i1 + k * ib];
              }
              i1 = (i - ns) - 1;
              for (k = 0; k <= i1; k++) {
                c_data[b_i1 + k * ib] = c_data[b_i1 + (k + ns) * ib];
              }
              for (k = 0; k < ns; k++) {
                c_data[b_i1 + ((k + i) - ns) * ib] = xin_data[k];
              }
            }
          }
        }
      }
      emxFree_creal32_T(&buffer);
    }
  } else if (varargout_1->size[0] > 1) {
    int npages;
    acoef = (int)((unsigned int)varargout_1->size[0] >> 1) - 1;
    npages = varargout_1->size[1] - 1;
    b_bcoef = varargout_1->size[0];
    if ((acoef + 1) << 1 == varargout_1->size[0]) {
      i2 = 1;
      for (b_i = 0; b_i <= npages; b_i++) {
        b_i1 = i2;
        i2 += b_bcoef;
        ib = b_i1 + acoef;
        for (k = 0; k <= acoef; k++) {
          float xtmp_im;
          bcoef = (b_i1 + k) - 1;
          xtmp_re = c_data[bcoef].re;
          xtmp_im = c_data[bcoef].im;
          i = ib + k;
          c_data[bcoef] = c_data[i];
          c_data[i].re = xtmp_re;
          c_data[i].im = xtmp_im;
        }
      }
    } else {
      i2 = 1;
      for (b_i = 0; b_i <= npages; b_i++) {
        float xtmp_im;
        b_i1 = i2;
        i2 += b_bcoef;
        ib = b_i1 + acoef;
        xtmp_re = c_data[ib].re;
        xtmp_im = c_data[ib].im;
        for (k = 0; k <= acoef; k++) {
          i = ib + k;
          i1 = (b_i1 + k) - 1;
          c_data[i] = c_data[i1];
          c_data[i1] = c_data[i + 1];
        }
        ib = (ib + acoef) + 1;
        c_data[ib].re = xtmp_re;
        c_data[ib].im = xtmp_im;
      }
    }
  }
  if (f->size[0] == 0) {
    d = 0.0;
  } else {
    d = fmod(f->size[0], 2.0);
  }
  if (d == 0.0) {
    nCol = f_data[(int)((double)f->size[0] / 2.0) - 1];
    bcoef = f->size[0];
    for (i = 0; i < bcoef; i++) {
      f_data[i] -= nCol;
    }
  } else {
    nCol = f_data[(int)(((double)f->size[0] + 1.0) / 2.0) - 1];
    bcoef = f->size[0];
    for (i = 0; i < bcoef; i++) {
      f_data[i] -= nCol;
    }
  }
  if (varargout_1->size[0] < 1) {
    bcoef = 0;
  } else {
    bcoef = varargout_1->size[0];
  }
  i = varargout_2->size[0];
  varargout_2->size[0] = bcoef;
  emxEnsureCapacity_real32_T(varargout_2, i);
  obj_value_data = varargout_2->data;
  for (i = 0; i < bcoef; i++) {
    obj_value_data[i] = (float)f_data[i];
  }
  emxFree_real_T(&f);
  if (varargout_1->size[1] < 1) {
    bcoef = 0;
  } else {
    bcoef = varargout_1->size[1];
  }
  emxInit_real32_T(&tempT, 2);
  i = tempT->size[0] * tempT->size[1];
  tempT->size[0] = 1;
  tempT->size[1] = bcoef;
  emxEnsureCapacity_real32_T(tempT, i);
  obj_value_data = tempT->data;
  for (i = 0; i < bcoef; i++) {
    obj_value_data[i] = (float)y_data[i];
  }
  emxFree_real_T(&y);
  i = varargout_3->size[0];
  varargout_3->size[0] = tempT->size[1];
  emxEnsureCapacity_real32_T(varargout_3, i);
  varargout_3_data = varargout_3->data;
  bcoef = tempT->size[1];
  for (i = 0; i < bcoef; i++) {
    varargout_3_data[i] = obj_value_data[i];
  }
  emxFree_real32_T(&tempT);
}

/*
 * File trailer for stft.c
 *
 * [EOF]
 */
