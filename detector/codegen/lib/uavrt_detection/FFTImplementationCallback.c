/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: FFTImplementationCallback.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "FFTImplementationCallback.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include "omp.h"
#include <math.h>

/* Function Declarations */
static void d_FFTImplementationCallback_r2b(const emxArray_creal32_T *x,
                                            int unsigned_nRows,
                                            const emxArray_real32_T *costab,
                                            const emxArray_real32_T *sintab,
                                            emxArray_creal32_T *y);

static void f_FFTImplementationCallback_r2b(const emxArray_creal_T *x,
                                            int unsigned_nRows,
                                            const emxArray_real_T *costab,
                                            const emxArray_real_T *sintab,
                                            emxArray_creal_T *y);

/* Function Definitions */
/*
 * Arguments    : const emxArray_creal32_T *x
 *                int unsigned_nRows
 *                const emxArray_real32_T *costab
 *                const emxArray_real32_T *sintab
 *                emxArray_creal32_T *y
 * Return Type  : void
 */
static void d_FFTImplementationCallback_r2b(const emxArray_creal32_T *x,
                                            int unsigned_nRows,
                                            const emxArray_real32_T *costab,
                                            const emxArray_real32_T *sintab,
                                            emxArray_creal32_T *y)
{
  const creal32_T *x_data;
  creal32_T *y_data;
  const float *costab_data;
  const float *sintab_data;
  float temp_im;
  float temp_re;
  float temp_re_tmp;
  float twid_re;
  int i;
  int iDelta2;
  int iheight;
  int iy;
  int j;
  int ju;
  int k;
  int nRowsD2;
  sintab_data = sintab->data;
  costab_data = costab->data;
  x_data = x->data;
  iy = y->size[0];
  y->size[0] = unsigned_nRows;
  emxEnsureCapacity_creal32_T(y, iy);
  y_data = y->data;
  if (unsigned_nRows > x->size[0]) {
    iy = y->size[0];
    y->size[0] = unsigned_nRows;
    emxEnsureCapacity_creal32_T(y, iy);
    y_data = y->data;
    for (iy = 0; iy < unsigned_nRows; iy++) {
      y_data[iy].re = 0.0F;
      y_data[iy].im = 0.0F;
    }
  }
  iDelta2 = x->size[0];
  if (iDelta2 > unsigned_nRows) {
    iDelta2 = unsigned_nRows;
  }
  iheight = unsigned_nRows - 2;
  nRowsD2 = unsigned_nRows / 2;
  k = nRowsD2 / 2;
  iy = 0;
  ju = 0;
  for (i = 0; i <= iDelta2 - 2; i++) {
    bool tst;
    y_data[iy] = x_data[i];
    iy = unsigned_nRows;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }
    iy = ju;
  }
  y_data[iy] = x_data[iDelta2 - 1];
  if (unsigned_nRows > 1) {
    for (i = 0; i <= iheight; i += 2) {
      temp_re_tmp = y_data[i + 1].re;
      temp_im = y_data[i + 1].im;
      temp_re = y_data[i].re;
      twid_re = y_data[i].im;
      y_data[i + 1].re = temp_re - temp_re_tmp;
      y_data[i + 1].im = twid_re - temp_im;
      y_data[i].re = temp_re + temp_re_tmp;
      y_data[i].im = twid_re + temp_im;
    }
  }
  iy = 2;
  iDelta2 = 4;
  iheight = ((k - 1) << 2) + 1;
  while (k > 0) {
    int b_temp_re_tmp;
    for (i = 0; i < iheight; i += iDelta2) {
      b_temp_re_tmp = i + iy;
      temp_re = y_data[b_temp_re_tmp].re;
      temp_im = y_data[b_temp_re_tmp].im;
      y_data[b_temp_re_tmp].re = y_data[i].re - temp_re;
      y_data[b_temp_re_tmp].im = y_data[i].im - temp_im;
      y_data[i].re += temp_re;
      y_data[i].im += temp_im;
    }
    ju = 1;
    for (j = k; j < nRowsD2; j += k) {
      float twid_im;
      int ihi;
      twid_re = costab_data[j];
      twid_im = sintab_data[j];
      i = ju;
      ihi = ju + iheight;
      while (i < ihi) {
        b_temp_re_tmp = i + iy;
        temp_re_tmp = y_data[b_temp_re_tmp].im;
        temp_im = y_data[b_temp_re_tmp].re;
        temp_re = twid_re * temp_im - twid_im * temp_re_tmp;
        temp_im = twid_re * temp_re_tmp + twid_im * temp_im;
        y_data[b_temp_re_tmp].re = y_data[i].re - temp_re;
        y_data[b_temp_re_tmp].im = y_data[i].im - temp_im;
        y_data[i].re += temp_re;
        y_data[i].im += temp_im;
        i += iDelta2;
      }
      ju++;
    }
    k /= 2;
    iy = iDelta2;
    iDelta2 += iDelta2;
    iheight -= iy;
  }
}

/*
 * Arguments    : const emxArray_creal_T *x
 *                int unsigned_nRows
 *                const emxArray_real_T *costab
 *                const emxArray_real_T *sintab
 *                emxArray_creal_T *y
 * Return Type  : void
 */
static void f_FFTImplementationCallback_r2b(const emxArray_creal_T *x,
                                            int unsigned_nRows,
                                            const emxArray_real_T *costab,
                                            const emxArray_real_T *sintab,
                                            emxArray_creal_T *y)
{
  const creal_T *x_data;
  creal_T *y_data;
  const double *costab_data;
  const double *sintab_data;
  double temp_im;
  double temp_re;
  double temp_re_tmp;
  double twid_re;
  int i;
  int iDelta2;
  int iheight;
  int iy;
  int j;
  int ju;
  int k;
  int nRowsD2;
  sintab_data = sintab->data;
  costab_data = costab->data;
  x_data = x->data;
  iy = y->size[0];
  y->size[0] = unsigned_nRows;
  emxEnsureCapacity_creal_T(y, iy);
  y_data = y->data;
  if (unsigned_nRows > x->size[0]) {
    iy = y->size[0];
    y->size[0] = unsigned_nRows;
    emxEnsureCapacity_creal_T(y, iy);
    y_data = y->data;
    for (iy = 0; iy < unsigned_nRows; iy++) {
      y_data[iy].re = 0.0;
      y_data[iy].im = 0.0;
    }
  }
  iDelta2 = x->size[0];
  if (iDelta2 > unsigned_nRows) {
    iDelta2 = unsigned_nRows;
  }
  iheight = unsigned_nRows - 2;
  nRowsD2 = unsigned_nRows / 2;
  k = nRowsD2 / 2;
  iy = 0;
  ju = 0;
  for (i = 0; i <= iDelta2 - 2; i++) {
    bool tst;
    y_data[iy] = x_data[i];
    iy = unsigned_nRows;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }
    iy = ju;
  }
  y_data[iy] = x_data[iDelta2 - 1];
  if (unsigned_nRows > 1) {
    for (i = 0; i <= iheight; i += 2) {
      temp_re_tmp = y_data[i + 1].re;
      temp_im = y_data[i + 1].im;
      temp_re = y_data[i].re;
      twid_re = y_data[i].im;
      y_data[i + 1].re = temp_re - temp_re_tmp;
      y_data[i + 1].im = twid_re - temp_im;
      y_data[i].re = temp_re + temp_re_tmp;
      y_data[i].im = twid_re + temp_im;
    }
  }
  iy = 2;
  iDelta2 = 4;
  iheight = ((k - 1) << 2) + 1;
  while (k > 0) {
    int b_temp_re_tmp;
    for (i = 0; i < iheight; i += iDelta2) {
      b_temp_re_tmp = i + iy;
      temp_re = y_data[b_temp_re_tmp].re;
      temp_im = y_data[b_temp_re_tmp].im;
      y_data[b_temp_re_tmp].re = y_data[i].re - temp_re;
      y_data[b_temp_re_tmp].im = y_data[i].im - temp_im;
      y_data[i].re += temp_re;
      y_data[i].im += temp_im;
    }
    ju = 1;
    for (j = k; j < nRowsD2; j += k) {
      double twid_im;
      int ihi;
      twid_re = costab_data[j];
      twid_im = sintab_data[j];
      i = ju;
      ihi = ju + iheight;
      while (i < ihi) {
        b_temp_re_tmp = i + iy;
        temp_re_tmp = y_data[b_temp_re_tmp].im;
        temp_im = y_data[b_temp_re_tmp].re;
        temp_re = twid_re * temp_im - twid_im * temp_re_tmp;
        temp_im = twid_re * temp_re_tmp + twid_im * temp_im;
        y_data[b_temp_re_tmp].re = y_data[i].re - temp_re;
        y_data[b_temp_re_tmp].im = y_data[i].im - temp_im;
        y_data[i].re += temp_re;
        y_data[i].im += temp_im;
        i += iDelta2;
      }
      ju++;
    }
    k /= 2;
    iy = iDelta2;
    iDelta2 += iDelta2;
    iheight -= iy;
  }
}

/*
 * Arguments    : const emxArray_creal32_T *x
 *                int n2blue
 *                int nfft
 *                const emxArray_real32_T *costab
 *                const emxArray_real32_T *sintab
 *                const emxArray_real32_T *sintabinv
 *                emxArray_creal32_T *y
 * Return Type  : void
 */
void c_FFTImplementationCallback_dob(const emxArray_creal32_T *x, int n2blue,
                                     int nfft, const emxArray_real32_T *costab,
                                     const emxArray_real32_T *sintab,
                                     const emxArray_real32_T *sintabinv,
                                     emxArray_creal32_T *y)
{
  emxArray_creal32_T *fv;
  emxArray_creal32_T *fy;
  emxArray_creal32_T *r1;
  emxArray_creal32_T *wwc;
  const creal32_T *x_data;
  creal32_T *fv_data;
  creal32_T *fy_data;
  creal32_T *r;
  creal32_T *wwc_data;
  creal32_T *y_data;
  const float *costab_data;
  const float *sintab_data;
  float b_temp_re_tmp;
  float nt_im;
  float nt_re;
  float temp_im;
  float temp_re;
  float twid_im;
  float twid_re;
  int b_i;
  int b_k;
  int b_y;
  int chan;
  int i;
  int ihi;
  int iy;
  int j;
  int ju;
  int k;
  int minNrowsNx;
  int nInt2;
  int nInt2m1;
  int nRowsD2;
  int rt;
  int temp_re_tmp;
  int xoff;
  bool tst;
  sintab_data = sintab->data;
  costab_data = costab->data;
  x_data = x->data;
  nInt2m1 = (nfft + nfft) - 1;
  emxInit_creal32_T(&wwc, 1);
  i = wwc->size[0];
  wwc->size[0] = nInt2m1;
  emxEnsureCapacity_creal32_T(wwc, i);
  wwc_data = wwc->data;
  rt = 0;
  wwc_data[nfft - 1].re = 1.0F;
  wwc_data[nfft - 1].im = 0.0F;
  nInt2 = nfft << 1;
  for (k = 0; k <= nfft - 2; k++) {
    b_y = ((k + 1) << 1) - 1;
    if (nInt2 - rt <= b_y) {
      rt += b_y - nInt2;
    } else {
      rt += b_y;
    }
    nt_im = -3.14159274F * (float)rt / (float)nfft;
    if (nt_im == 0.0F) {
      nt_re = 1.0F;
      nt_im = 0.0F;
    } else {
      nt_re = cosf(nt_im);
      nt_im = sinf(nt_im);
    }
    i = (nfft - k) - 2;
    wwc_data[i].re = nt_re;
    wwc_data[i].im = -nt_im;
  }
  i = nInt2m1 - 1;
  for (k = i; k >= nfft; k--) {
    wwc_data[k] = wwc_data[(nInt2m1 - k) - 1];
  }
  nInt2m1 = x->size[0];
  i = y->size[0] * y->size[1];
  y->size[0] = nfft;
  y->size[1] = x->size[1];
  emxEnsureCapacity_creal32_T(y, i);
  y_data = y->data;
  if (nfft > x->size[0]) {
    i = y->size[0] * y->size[1];
    y->size[0] = nfft;
    y->size[1] = x->size[1];
    emxEnsureCapacity_creal32_T(y, i);
    y_data = y->data;
    b_y = nfft * x->size[1];
    for (i = 0; i < b_y; i++) {
      y_data[i].re = 0.0F;
      y_data[i].im = 0.0F;
    }
  }
  b_y = x->size[1] - 1;
#pragma omp parallel num_threads(omp_get_max_threads()) private(               \
    r, fy_data, fv_data, fv, fy, r1, xoff, ju, minNrowsNx, b_k, temp_re_tmp,   \
    temp_re, temp_im, iy, j, nRowsD2, b_i, tst, b_temp_re_tmp, twid_im,        \
    twid_re, ihi)
  {
    emxInit_creal32_T(&fv, 1);
    emxInit_creal32_T(&fy, 1);
    emxInit_creal32_T(&r1, 1);
#pragma omp for nowait
    for (chan = 0; chan <= b_y; chan++) {
      xoff = chan * nInt2m1;
      ju = r1->size[0];
      r1->size[0] = nfft;
      emxEnsureCapacity_creal32_T(r1, ju);
      r = r1->data;
      if (nfft > x->size[0]) {
        ju = r1->size[0];
        r1->size[0] = nfft;
        emxEnsureCapacity_creal32_T(r1, ju);
        r = r1->data;
        for (ju = 0; ju < nfft; ju++) {
          r[ju].re = 0.0F;
          r[ju].im = 0.0F;
        }
      }
      minNrowsNx = x->size[0];
      if (nfft <= minNrowsNx) {
        minNrowsNx = nfft;
      }
      for (b_k = 0; b_k < minNrowsNx; b_k++) {
        temp_re_tmp = (nfft + b_k) - 1;
        temp_re = wwc_data[temp_re_tmp].re;
        temp_im = wwc_data[temp_re_tmp].im;
        ju = xoff + b_k;
        r[b_k].re = temp_re * x_data[ju].re + temp_im * x_data[ju].im;
        r[b_k].im = temp_re * x_data[ju].im - temp_im * x_data[ju].re;
      }
      ju = minNrowsNx + 1;
      for (b_k = ju; b_k <= nfft; b_k++) {
        r[b_k - 1].re = 0.0F;
        r[b_k - 1].im = 0.0F;
      }
      ju = fy->size[0];
      fy->size[0] = n2blue;
      emxEnsureCapacity_creal32_T(fy, ju);
      fy_data = fy->data;
      if (n2blue > r1->size[0]) {
        ju = fy->size[0];
        fy->size[0] = n2blue;
        emxEnsureCapacity_creal32_T(fy, ju);
        fy_data = fy->data;
        for (ju = 0; ju < n2blue; ju++) {
          fy_data[ju].re = 0.0F;
          fy_data[ju].im = 0.0F;
        }
      }
      iy = r1->size[0];
      j = n2blue;
      if (iy <= n2blue) {
        j = iy;
      }
      minNrowsNx = n2blue - 2;
      nRowsD2 = n2blue / 2;
      b_k = nRowsD2 / 2;
      iy = 0;
      ju = 0;
      for (b_i = 0; b_i <= j - 2; b_i++) {
        fy_data[iy] = r[b_i];
        xoff = n2blue;
        tst = true;
        while (tst) {
          xoff >>= 1;
          ju ^= xoff;
          tst = ((ju & xoff) == 0);
        }
        iy = ju;
      }
      fy_data[iy] = r[j - 1];
      if (n2blue > 1) {
        for (b_i = 0; b_i <= minNrowsNx; b_i += 2) {
          b_temp_re_tmp = fy_data[b_i + 1].re;
          temp_im = fy_data[b_i + 1].im;
          twid_im = fy_data[b_i].re;
          temp_re = fy_data[b_i].im;
          fy_data[b_i + 1].re = twid_im - b_temp_re_tmp;
          fy_data[b_i + 1].im = temp_re - temp_im;
          fy_data[b_i].re = twid_im + b_temp_re_tmp;
          fy_data[b_i].im = temp_re + temp_im;
        }
      }
      xoff = 2;
      minNrowsNx = 4;
      iy = ((b_k - 1) << 2) + 1;
      while (b_k > 0) {
        for (b_i = 0; b_i < iy; b_i += minNrowsNx) {
          temp_re_tmp = b_i + xoff;
          temp_re = fy_data[temp_re_tmp].re;
          temp_im = fy_data[temp_re_tmp].im;
          fy_data[temp_re_tmp].re = fy_data[b_i].re - temp_re;
          fy_data[temp_re_tmp].im = fy_data[b_i].im - temp_im;
          fy_data[b_i].re += temp_re;
          fy_data[b_i].im += temp_im;
        }
        ju = 1;
        for (j = b_k; j < nRowsD2; j += b_k) {
          twid_re = costab_data[j];
          twid_im = sintab_data[j];
          b_i = ju;
          ihi = ju + iy;
          while (b_i < ihi) {
            temp_re_tmp = b_i + xoff;
            b_temp_re_tmp = fy_data[temp_re_tmp].im;
            temp_im = fy_data[temp_re_tmp].re;
            temp_re = twid_re * temp_im - twid_im * b_temp_re_tmp;
            temp_im = twid_re * b_temp_re_tmp + twid_im * temp_im;
            fy_data[temp_re_tmp].re = fy_data[b_i].re - temp_re;
            fy_data[temp_re_tmp].im = fy_data[b_i].im - temp_im;
            fy_data[b_i].re += temp_re;
            fy_data[b_i].im += temp_im;
            b_i += minNrowsNx;
          }
          ju++;
        }
        b_k /= 2;
        xoff = minNrowsNx;
        minNrowsNx += minNrowsNx;
        iy -= xoff;
      }
      d_FFTImplementationCallback_r2b(wwc, n2blue, costab, sintab, fv);
      fv_data = fv->data;
      iy = fy->size[0];
      for (ju = 0; ju < iy; ju++) {
        twid_im = fy_data[ju].re;
        temp_im = fv_data[ju].im;
        temp_re = fy_data[ju].im;
        twid_re = fv_data[ju].re;
        fy_data[ju].re = twid_im * twid_re - temp_re * temp_im;
        fy_data[ju].im = twid_im * temp_im + temp_re * twid_re;
      }
      d_FFTImplementationCallback_r2b(fy, n2blue, costab, sintabinv, fv);
      fv_data = fv->data;
      if (fv->size[0] > 1) {
        temp_im = 1.0F / (float)fv->size[0];
        iy = fv->size[0];
        for (ju = 0; ju < iy; ju++) {
          fv_data[ju].re *= temp_im;
          fv_data[ju].im *= temp_im;
        }
      }
      ju = (int)(float)nfft;
      iy = wwc->size[0];
      for (b_k = ju; b_k <= iy; b_k++) {
        temp_im = wwc_data[b_k - 1].re;
        temp_re = fv_data[b_k - 1].im;
        twid_re = wwc_data[b_k - 1].im;
        twid_im = fv_data[b_k - 1].re;
        xoff = b_k - (int)(float)nfft;
        r[xoff].re = temp_im * twid_im + twid_re * temp_re;
        r[xoff].im = temp_im * temp_re - twid_re * twid_im;
      }
      iy = r1->size[0];
      for (ju = 0; ju < iy; ju++) {
        y_data[ju + y->size[0] * chan] = r[ju];
      }
    }
    emxFree_creal32_T(&r1);
    emxFree_creal32_T(&fy);
    emxFree_creal32_T(&fv);
  }
  emxFree_creal32_T(&wwc);
}

/*
 * Arguments    : int nRows
 *                bool useRadix2
 *                emxArray_real_T *costab
 *                emxArray_real_T *sintab
 *                emxArray_real_T *sintabinv
 * Return Type  : void
 */
void c_FFTImplementationCallback_gen(int nRows, bool useRadix2,
                                     emxArray_real_T *costab,
                                     emxArray_real_T *sintab,
                                     emxArray_real_T *sintabinv)
{
  emxArray_real_T *costab1q;
  double e;
  double *costab1q_data;
  double *costab_data;
  double *sintab_data;
  double *sintabinv_data;
  int i;
  int k;
  int n;
  int nd2;
  e = 6.2831853071795862 / (double)nRows;
  n = nRows / 2 / 2;
  emxInit_real_T(&costab1q, 2);
  i = costab1q->size[0] * costab1q->size[1];
  costab1q->size[0] = 1;
  costab1q->size[1] = n + 1;
  emxEnsureCapacity_real_T(costab1q, i);
  costab1q_data = costab1q->data;
  costab1q_data[0] = 1.0;
  nd2 = n / 2 - 1;
  for (k = 0; k <= nd2; k++) {
    costab1q_data[k + 1] = cos(e * ((double)k + 1.0));
  }
  i = nd2 + 2;
  nd2 = n - 1;
  for (k = i; k <= nd2; k++) {
    costab1q_data[k] = sin(e * (double)(n - k));
  }
  costab1q_data[n] = 0.0;
  if (!useRadix2) {
    n = costab1q->size[1] - 1;
    nd2 = (costab1q->size[1] - 1) << 1;
    i = costab->size[0] * costab->size[1];
    costab->size[0] = 1;
    costab->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(costab, i);
    costab_data = costab->data;
    i = sintab->size[0] * sintab->size[1];
    sintab->size[0] = 1;
    sintab->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(sintab, i);
    sintab_data = sintab->data;
    costab_data[0] = 1.0;
    sintab_data[0] = 0.0;
    i = sintabinv->size[0] * sintabinv->size[1];
    sintabinv->size[0] = 1;
    sintabinv->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(sintabinv, i);
    sintabinv_data = sintabinv->data;
    for (k = 0; k < n; k++) {
      sintabinv_data[k + 1] = costab1q_data[(n - k) - 1];
    }
    i = costab1q->size[1];
    for (k = i; k <= nd2; k++) {
      sintabinv_data[k] = costab1q_data[k - n];
    }
    for (k = 0; k < n; k++) {
      costab_data[k + 1] = costab1q_data[k + 1];
      sintab_data[k + 1] = -costab1q_data[(n - k) - 1];
    }
    i = costab1q->size[1];
    for (k = i; k <= nd2; k++) {
      costab_data[k] = -costab1q_data[nd2 - k];
      sintab_data[k] = -costab1q_data[k - n];
    }
  } else {
    n = costab1q->size[1] - 1;
    nd2 = (costab1q->size[1] - 1) << 1;
    i = costab->size[0] * costab->size[1];
    costab->size[0] = 1;
    costab->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(costab, i);
    costab_data = costab->data;
    i = sintab->size[0] * sintab->size[1];
    sintab->size[0] = 1;
    sintab->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(sintab, i);
    sintab_data = sintab->data;
    costab_data[0] = 1.0;
    sintab_data[0] = 0.0;
    for (k = 0; k < n; k++) {
      costab_data[k + 1] = costab1q_data[k + 1];
      sintab_data[k + 1] = -costab1q_data[(n - k) - 1];
    }
    i = costab1q->size[1];
    for (k = i; k <= nd2; k++) {
      costab_data[k] = -costab1q_data[nd2 - k];
      sintab_data[k] = -costab1q_data[k - n];
    }
    sintabinv->size[0] = 1;
    sintabinv->size[1] = 0;
  }
  emxFree_real_T(&costab1q);
}

/*
 * Arguments    : int nfft
 *                bool useRadix2
 *                int *n2blue
 *                int *nRows
 * Return Type  : void
 */
void c_FFTImplementationCallback_get(int nfft, bool useRadix2, int *n2blue,
                                     int *nRows)
{
  *n2blue = 1;
  if (useRadix2) {
    *nRows = nfft;
  } else {
    if (nfft > 0) {
      int n;
      int pmax;
      n = (nfft + nfft) - 1;
      pmax = 31;
      if (n <= 1) {
        pmax = 0;
      } else {
        int pmin;
        bool exitg1;
        pmin = 0;
        exitg1 = false;
        while ((!exitg1) && (pmax - pmin > 1)) {
          int k;
          int pow2p;
          k = (pmin + pmax) >> 1;
          pow2p = 1 << k;
          if (pow2p == n) {
            pmax = k;
            exitg1 = true;
          } else if (pow2p > n) {
            pmax = k;
          } else {
            pmin = k;
          }
        }
      }
      *n2blue = 1 << pmax;
    }
    *nRows = *n2blue;
  }
}

/*
 * Arguments    : const emxArray_creal32_T *x
 *                int n1_unsigned
 *                const emxArray_real32_T *costab
 *                const emxArray_real32_T *sintab
 *                emxArray_creal32_T *y
 * Return Type  : void
 */
void c_FFTImplementationCallback_r2b(const emxArray_creal32_T *x,
                                     int n1_unsigned,
                                     const emxArray_real32_T *costab,
                                     const emxArray_real32_T *sintab,
                                     emxArray_creal32_T *y)
{
  emxArray_creal32_T *r1;
  const creal32_T *x_data;
  creal32_T *r;
  creal32_T *y_data;
  const float *costab_data;
  const float *sintab_data;
  float temp_im;
  float temp_re;
  float temp_re_tmp;
  float twid_im;
  float twid_re;
  int b_i;
  int b_temp_re_tmp;
  int chan;
  int i;
  int iDelta2;
  int ihi;
  int istart;
  int iy;
  int ju;
  int k;
  int loop_ub;
  int nRowsD2;
  int nrows;
  int xoff;
  bool tst;
  sintab_data = sintab->data;
  costab_data = costab->data;
  x_data = x->data;
  nrows = x->size[0];
  i = y->size[0] * y->size[1];
  y->size[0] = n1_unsigned;
  y->size[1] = x->size[1];
  emxEnsureCapacity_creal32_T(y, i);
  y_data = y->data;
  if (n1_unsigned > x->size[0]) {
    i = y->size[0] * y->size[1];
    y->size[0] = n1_unsigned;
    y->size[1] = x->size[1];
    emxEnsureCapacity_creal32_T(y, i);
    y_data = y->data;
    loop_ub = n1_unsigned * x->size[1];
    for (i = 0; i < loop_ub; i++) {
      y_data[i].re = 0.0F;
      y_data[i].im = 0.0F;
    }
  }
  loop_ub = x->size[1] - 1;
#pragma omp parallel num_threads(omp_get_max_threads()) private(               \
    r, r1, xoff, ju, iy, istart, iDelta2, nRowsD2, k, b_i, tst, temp_re_tmp,   \
    temp_im, temp_re, twid_re, b_temp_re_tmp, twid_im, ihi)
  {
    emxInit_creal32_T(&r1, 1);
#pragma omp for nowait
    for (chan = 0; chan <= loop_ub; chan++) {
      xoff = chan * nrows;
      ju = r1->size[0];
      r1->size[0] = n1_unsigned;
      emxEnsureCapacity_creal32_T(r1, ju);
      r = r1->data;
      if (n1_unsigned > x->size[0]) {
        ju = r1->size[0];
        r1->size[0] = n1_unsigned;
        emxEnsureCapacity_creal32_T(r1, ju);
        r = r1->data;
        for (ju = 0; ju < n1_unsigned; ju++) {
          r[ju].re = 0.0F;
          r[ju].im = 0.0F;
        }
      }
      iy = x->size[0];
      istart = n1_unsigned;
      if (iy <= n1_unsigned) {
        istart = iy;
      }
      iDelta2 = n1_unsigned - 2;
      nRowsD2 = n1_unsigned / 2;
      k = nRowsD2 / 2;
      iy = 0;
      ju = 0;
      for (b_i = 0; b_i <= istart - 2; b_i++) {
        r[iy] = x_data[xoff + b_i];
        iy = n1_unsigned;
        tst = true;
        while (tst) {
          iy >>= 1;
          ju ^= iy;
          tst = ((ju & iy) == 0);
        }
        iy = ju;
      }
      r[iy] = x_data[(xoff + istart) - 1];
      if (n1_unsigned > 1) {
        for (b_i = 0; b_i <= iDelta2; b_i += 2) {
          temp_re_tmp = r[b_i + 1].re;
          temp_im = r[b_i + 1].im;
          temp_re = r[b_i].re;
          twid_re = r[b_i].im;
          r[b_i + 1].re = temp_re - temp_re_tmp;
          r[b_i + 1].im = twid_re - temp_im;
          r[b_i].re = temp_re + temp_re_tmp;
          r[b_i].im = twid_re + temp_im;
        }
      }
      iy = 2;
      iDelta2 = 4;
      ju = ((k - 1) << 2) + 1;
      while (k > 0) {
        for (b_i = 0; b_i < ju; b_i += iDelta2) {
          b_temp_re_tmp = b_i + iy;
          temp_re = r[b_temp_re_tmp].re;
          temp_im = r[b_temp_re_tmp].im;
          r[b_temp_re_tmp].re = r[b_i].re - temp_re;
          r[b_temp_re_tmp].im = r[b_i].im - temp_im;
          r[b_i].re += temp_re;
          r[b_i].im += temp_im;
        }
        istart = 1;
        for (xoff = k; xoff < nRowsD2; xoff += k) {
          twid_re = costab_data[xoff];
          twid_im = sintab_data[xoff];
          b_i = istart;
          ihi = istart + ju;
          while (b_i < ihi) {
            b_temp_re_tmp = b_i + iy;
            temp_re_tmp = r[b_temp_re_tmp].im;
            temp_im = r[b_temp_re_tmp].re;
            temp_re = twid_re * temp_im - twid_im * temp_re_tmp;
            temp_im = twid_re * temp_re_tmp + twid_im * temp_im;
            r[b_temp_re_tmp].re = r[b_i].re - temp_re;
            r[b_temp_re_tmp].im = r[b_i].im - temp_im;
            r[b_i].re += temp_re;
            r[b_i].im += temp_im;
            b_i += iDelta2;
          }
          istart++;
        }
        k /= 2;
        iy = iDelta2;
        iDelta2 += iDelta2;
        ju -= iy;
      }
      iy = r1->size[0];
      for (ju = 0; ju < iy; ju++) {
        y_data[ju + y->size[0] * chan] = r[ju];
      }
    }
    emxFree_creal32_T(&r1);
  }
}

/*
 * Arguments    : const emxArray_creal_T *x
 *                int n2blue
 *                int nfft
 *                const emxArray_real_T *costab
 *                const emxArray_real_T *sintab
 *                const emxArray_real_T *sintabinv
 *                emxArray_creal_T *y
 * Return Type  : void
 */
void d_FFTImplementationCallback_dob(const emxArray_creal_T *x, int n2blue,
                                     int nfft, const emxArray_real_T *costab,
                                     const emxArray_real_T *sintab,
                                     const emxArray_real_T *sintabinv,
                                     emxArray_creal_T *y)
{
  emxArray_creal_T *b_fv;
  emxArray_creal_T *fv;
  emxArray_creal_T *r;
  emxArray_creal_T *wwc;
  const creal_T *x_data;
  creal_T *b_fv_data;
  creal_T *fv_data;
  creal_T *r1;
  creal_T *wwc_data;
  creal_T *y_data;
  double b_re_tmp;
  double nt_im;
  double nt_re;
  double re_tmp;
  int b_y;
  int i;
  int k;
  int nInt2;
  int nInt2m1;
  int rt;
  x_data = x->data;
  nInt2m1 = (nfft + nfft) - 1;
  emxInit_creal_T(&wwc, 1);
  i = wwc->size[0];
  wwc->size[0] = nInt2m1;
  emxEnsureCapacity_creal_T(wwc, i);
  wwc_data = wwc->data;
  rt = 0;
  wwc_data[nfft - 1].re = 1.0;
  wwc_data[nfft - 1].im = 0.0;
  nInt2 = nfft << 1;
  for (k = 0; k <= nfft - 2; k++) {
    b_y = ((k + 1) << 1) - 1;
    if (nInt2 - rt <= b_y) {
      rt += b_y - nInt2;
    } else {
      rt += b_y;
    }
    nt_im = -3.1415926535897931 * (double)rt / (double)nfft;
    if (nt_im == 0.0) {
      nt_re = 1.0;
      nt_im = 0.0;
    } else {
      nt_re = cos(nt_im);
      nt_im = sin(nt_im);
    }
    i = (nfft - k) - 2;
    wwc_data[i].re = nt_re;
    wwc_data[i].im = -nt_im;
  }
  i = nInt2m1 - 1;
  for (k = i; k >= nfft; k--) {
    wwc_data[k] = wwc_data[(nInt2m1 - k) - 1];
  }
  i = y->size[0] * y->size[1];
  y->size[0] = nfft;
  y->size[1] = 1;
  emxEnsureCapacity_creal_T(y, i);
  y_data = y->data;
  if (nfft > x->size[0]) {
    i = y->size[0] * y->size[1];
    y->size[0] = nfft;
    y->size[1] = 1;
    emxEnsureCapacity_creal_T(y, i);
    y_data = y->data;
    for (i = 0; i < nfft; i++) {
      y_data[i].re = 0.0;
      y_data[i].im = 0.0;
    }
  }
  nInt2m1 = x->size[0];
  if (nfft <= nInt2m1) {
    nInt2m1 = nfft;
  }
  i = nInt2m1 + 1;
  rt = wwc->size[0];
  emxInit_creal_T(&r, 1);
  b_y = r->size[0];
  r->size[0] = nfft;
  emxEnsureCapacity_creal_T(r, b_y);
  r1 = r->data;
  if (nfft > x->size[0]) {
    b_y = r->size[0];
    r->size[0] = nfft;
    emxEnsureCapacity_creal_T(r, b_y);
    r1 = r->data;
    for (b_y = 0; b_y < nfft; b_y++) {
      r1[b_y].re = 0.0;
      r1[b_y].im = 0.0;
    }
  }
  for (k = 0; k < nInt2m1; k++) {
    b_y = (nfft + k) - 1;
    nt_re = wwc_data[b_y].re;
    nt_im = wwc_data[b_y].im;
    re_tmp = x_data[k].im;
    b_re_tmp = x_data[k].re;
    r1[k].re = nt_re * b_re_tmp + nt_im * re_tmp;
    r1[k].im = nt_re * re_tmp - nt_im * b_re_tmp;
  }
  for (k = i; k <= nfft; k++) {
    r1[k - 1].re = 0.0;
    r1[k - 1].im = 0.0;
  }
  emxInit_creal_T(&fv, 1);
  f_FFTImplementationCallback_r2b(r, n2blue, costab, sintab, fv);
  fv_data = fv->data;
  emxInit_creal_T(&b_fv, 1);
  f_FFTImplementationCallback_r2b(wwc, n2blue, costab, sintab, b_fv);
  i = b_fv->size[0];
  b_fv->size[0] = fv->size[0];
  emxEnsureCapacity_creal_T(b_fv, i);
  b_fv_data = b_fv->data;
  b_y = fv->size[0];
  for (i = 0; i < b_y; i++) {
    nt_re = fv_data[i].re;
    nt_im = b_fv_data[i].im;
    re_tmp = fv_data[i].im;
    b_re_tmp = b_fv_data[i].re;
    b_fv_data[i].re = nt_re * b_re_tmp - re_tmp * nt_im;
    b_fv_data[i].im = nt_re * nt_im + re_tmp * b_re_tmp;
  }
  f_FFTImplementationCallback_r2b(b_fv, n2blue, costab, sintabinv, fv);
  fv_data = fv->data;
  emxFree_creal_T(&b_fv);
  if (fv->size[0] > 1) {
    nt_re = 1.0 / (double)fv->size[0];
    b_y = fv->size[0];
    for (i = 0; i < b_y; i++) {
      fv_data[i].re *= nt_re;
      fv_data[i].im *= nt_re;
    }
  }
  for (k = nfft; k <= rt; k++) {
    re_tmp = wwc_data[k - 1].re;
    b_re_tmp = fv_data[k - 1].im;
    nt_re = wwc_data[k - 1].im;
    nt_im = fv_data[k - 1].re;
    i = k - nfft;
    r1[i].re = re_tmp * nt_im + nt_re * b_re_tmp;
    r1[i].im = re_tmp * b_re_tmp - nt_re * nt_im;
  }
  emxFree_creal_T(&fv);
  emxFree_creal_T(&wwc);
  b_y = r->size[0];
  for (i = 0; i < b_y; i++) {
    y_data[i] = r1[i];
  }
  emxFree_creal_T(&r);
}

/*
 * Arguments    : const emxArray_creal_T *x
 *                int n2blue
 *                int nfft
 *                const emxArray_real_T *costab
 *                const emxArray_real_T *sintab
 *                const emxArray_real_T *sintabinv
 *                emxArray_creal_T *y
 * Return Type  : void
 */
void e_FFTImplementationCallback_dob(const emxArray_creal_T *x, int n2blue,
                                     int nfft, const emxArray_real_T *costab,
                                     const emxArray_real_T *sintab,
                                     const emxArray_real_T *sintabinv,
                                     emxArray_creal_T *y)
{
  emxArray_creal_T *b_fv;
  emxArray_creal_T *fv;
  emxArray_creal_T *r1;
  emxArray_creal_T *wwc;
  const creal_T *x_data;
  creal_T *b_fv_data;
  creal_T *fv_data;
  creal_T *r;
  creal_T *wwc_data;
  creal_T *y_data;
  double a_im;
  double a_re;
  double b_re_tmp;
  double nt_im;
  double nt_re;
  double re_tmp;
  int b_k;
  int b_y;
  int chan;
  int i;
  int i1;
  int k;
  int minNrowsNx;
  int nInt2;
  int nInt2m1;
  int rt;
  int u0;
  int xoff;
  x_data = x->data;
  nInt2m1 = (nfft + nfft) - 1;
  emxInit_creal_T(&wwc, 1);
  i = wwc->size[0];
  wwc->size[0] = nInt2m1;
  emxEnsureCapacity_creal_T(wwc, i);
  wwc_data = wwc->data;
  rt = 0;
  wwc_data[nfft - 1].re = 1.0;
  wwc_data[nfft - 1].im = 0.0;
  nInt2 = nfft << 1;
  for (k = 0; k <= nfft - 2; k++) {
    b_y = ((k + 1) << 1) - 1;
    if (nInt2 - rt <= b_y) {
      rt += b_y - nInt2;
    } else {
      rt += b_y;
    }
    nt_im = -3.1415926535897931 * (double)rt / (double)nfft;
    if (nt_im == 0.0) {
      nt_re = 1.0;
      nt_im = 0.0;
    } else {
      nt_re = cos(nt_im);
      nt_im = sin(nt_im);
    }
    i = (nfft - k) - 2;
    wwc_data[i].re = nt_re;
    wwc_data[i].im = -nt_im;
  }
  i = nInt2m1 - 1;
  for (k = i; k >= nfft; k--) {
    wwc_data[k] = wwc_data[(nInt2m1 - k) - 1];
  }
  nInt2m1 = x->size[0];
  i = y->size[0] * y->size[1] * y->size[2];
  y->size[0] = nfft;
  y->size[1] = x->size[1];
  y->size[2] = x->size[2];
  emxEnsureCapacity_creal_T(y, i);
  y_data = y->data;
  if (nfft > x->size[0]) {
    i = y->size[0] * y->size[1] * y->size[2];
    y->size[0] = nfft;
    y->size[1] = x->size[1];
    y->size[2] = x->size[2];
    emxEnsureCapacity_creal_T(y, i);
    y_data = y->data;
    b_y = nfft * x->size[1] * x->size[2];
    for (i = 0; i < b_y; i++) {
      y_data[i].re = 0.0;
      y_data[i].im = 0.0;
    }
  }
  b_y = x->size[1] * x->size[2] - 1;
#pragma omp parallel num_threads(omp_get_max_threads()) private(               \
    r, fv_data, b_fv_data, fv, b_fv, r1, xoff, i1, minNrowsNx, b_k, u0, a_re,  \
    a_im, re_tmp, b_re_tmp)
  {
    emxInit_creal_T(&fv, 1);
    emxInit_creal_T(&b_fv, 1);
    emxInit_creal_T(&r1, 1);
#pragma omp for nowait
    for (chan = 0; chan <= b_y; chan++) {
      xoff = chan * nInt2m1;
      i1 = r1->size[0];
      r1->size[0] = nfft;
      emxEnsureCapacity_creal_T(r1, i1);
      r = r1->data;
      if (nfft > x->size[0]) {
        i1 = r1->size[0];
        r1->size[0] = nfft;
        emxEnsureCapacity_creal_T(r1, i1);
        r = r1->data;
        for (i1 = 0; i1 < nfft; i1++) {
          r[i1].re = 0.0;
          r[i1].im = 0.0;
        }
      }
      minNrowsNx = x->size[0];
      if (nfft <= minNrowsNx) {
        minNrowsNx = nfft;
      }
      for (b_k = 0; b_k < minNrowsNx; b_k++) {
        u0 = (nfft + b_k) - 1;
        a_re = wwc_data[u0].re;
        a_im = wwc_data[u0].im;
        i1 = xoff + b_k;
        r[b_k].re = a_re * x_data[i1].re + a_im * x_data[i1].im;
        r[b_k].im = a_re * x_data[i1].im - a_im * x_data[i1].re;
      }
      i1 = minNrowsNx + 1;
      for (b_k = i1; b_k <= nfft; b_k++) {
        r[b_k - 1].re = 0.0;
        r[b_k - 1].im = 0.0;
      }
      f_FFTImplementationCallback_r2b(r1, n2blue, costab, sintab, b_fv);
      fv_data = b_fv->data;
      f_FFTImplementationCallback_r2b(wwc, n2blue, costab, sintab, fv);
      i1 = fv->size[0];
      fv->size[0] = b_fv->size[0];
      emxEnsureCapacity_creal_T(fv, i1);
      b_fv_data = fv->data;
      u0 = b_fv->size[0];
      for (i1 = 0; i1 < u0; i1++) {
        a_re = fv_data[i1].re;
        a_im = b_fv_data[i1].im;
        re_tmp = fv_data[i1].im;
        b_re_tmp = b_fv_data[i1].re;
        b_fv_data[i1].re = a_re * b_re_tmp - re_tmp * a_im;
        b_fv_data[i1].im = a_re * a_im + re_tmp * b_re_tmp;
      }
      f_FFTImplementationCallback_r2b(fv, n2blue, costab, sintabinv, b_fv);
      fv_data = b_fv->data;
      if (b_fv->size[0] > 1) {
        a_re = 1.0 / (double)b_fv->size[0];
        u0 = b_fv->size[0];
        for (i1 = 0; i1 < u0; i1++) {
          fv_data[i1].re *= a_re;
          fv_data[i1].im *= a_re;
        }
      }
      i1 = wwc->size[0];
      for (b_k = nfft; b_k <= i1; b_k++) {
        a_re = wwc_data[b_k - 1].re;
        a_im = fv_data[b_k - 1].im;
        re_tmp = wwc_data[b_k - 1].im;
        b_re_tmp = fv_data[b_k - 1].re;
        u0 = b_k - nfft;
        r[u0].re = a_re * b_re_tmp + re_tmp * a_im;
        r[u0].im = a_re * a_im - re_tmp * b_re_tmp;
      }
      xoff = y->size[0];
      u0 = r1->size[0];
      for (i1 = 0; i1 < u0; i1++) {
        y_data[i1 + xoff * chan] = r[i1];
      }
    }
    emxFree_creal_T(&r1);
    emxFree_creal_T(&b_fv);
    emxFree_creal_T(&fv);
  }
  emxFree_creal_T(&wwc);
}

/*
 * Arguments    : const emxArray_creal_T *x
 *                int n1_unsigned
 *                const emxArray_real_T *costab
 *                const emxArray_real_T *sintab
 *                emxArray_creal_T *y
 * Return Type  : void
 */
void e_FFTImplementationCallback_r2b(const emxArray_creal_T *x, int n1_unsigned,
                                     const emxArray_real_T *costab,
                                     const emxArray_real_T *sintab,
                                     emxArray_creal_T *y)
{
  emxArray_creal_T *r;
  const creal_T *x_data;
  creal_T *r1;
  creal_T *y_data;
  const double *costab_data;
  const double *sintab_data;
  double temp_im;
  double temp_re;
  double temp_re_tmp;
  double twid_re;
  int i;
  int iheight;
  int istart;
  int iy;
  int j;
  int ju;
  int k;
  int nRowsD2;
  sintab_data = sintab->data;
  costab_data = costab->data;
  x_data = x->data;
  ju = y->size[0] * y->size[1];
  y->size[0] = n1_unsigned;
  y->size[1] = 1;
  emxEnsureCapacity_creal_T(y, ju);
  y_data = y->data;
  if (n1_unsigned > x->size[0]) {
    ju = y->size[0] * y->size[1];
    y->size[0] = n1_unsigned;
    y->size[1] = 1;
    emxEnsureCapacity_creal_T(y, ju);
    y_data = y->data;
    for (ju = 0; ju < n1_unsigned; ju++) {
      y_data[ju].re = 0.0;
      y_data[ju].im = 0.0;
    }
  }
  iheight = x->size[0];
  if (iheight > n1_unsigned) {
    iheight = n1_unsigned;
  }
  istart = n1_unsigned - 2;
  nRowsD2 = n1_unsigned / 2;
  k = nRowsD2 / 2;
  emxInit_creal_T(&r, 1);
  ju = r->size[0];
  r->size[0] = n1_unsigned;
  emxEnsureCapacity_creal_T(r, ju);
  r1 = r->data;
  if (n1_unsigned > x->size[0]) {
    ju = r->size[0];
    r->size[0] = n1_unsigned;
    emxEnsureCapacity_creal_T(r, ju);
    r1 = r->data;
    for (ju = 0; ju < n1_unsigned; ju++) {
      r1[ju].re = 0.0;
      r1[ju].im = 0.0;
    }
  }
  iy = 0;
  ju = 0;
  for (i = 0; i <= iheight - 2; i++) {
    bool tst;
    r1[iy] = x_data[i];
    iy = n1_unsigned;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }
    iy = ju;
  }
  r1[iy] = x_data[iheight - 1];
  if (n1_unsigned > 1) {
    for (i = 0; i <= istart; i += 2) {
      temp_re_tmp = r1[i + 1].re;
      temp_im = r1[i + 1].im;
      temp_re = r1[i].re;
      twid_re = r1[i].im;
      r1[i + 1].re = temp_re - temp_re_tmp;
      r1[i + 1].im = twid_re - temp_im;
      r1[i].re = temp_re + temp_re_tmp;
      r1[i].im = twid_re + temp_im;
    }
  }
  iy = 2;
  ju = 4;
  iheight = ((k - 1) << 2) + 1;
  while (k > 0) {
    int b_temp_re_tmp;
    for (i = 0; i < iheight; i += ju) {
      b_temp_re_tmp = i + iy;
      temp_re = r1[b_temp_re_tmp].re;
      temp_im = r1[b_temp_re_tmp].im;
      r1[b_temp_re_tmp].re = r1[i].re - temp_re;
      r1[b_temp_re_tmp].im = r1[i].im - temp_im;
      r1[i].re += temp_re;
      r1[i].im += temp_im;
    }
    istart = 1;
    for (j = k; j < nRowsD2; j += k) {
      double twid_im;
      int ihi;
      twid_re = costab_data[j];
      twid_im = sintab_data[j];
      i = istart;
      ihi = istart + iheight;
      while (i < ihi) {
        b_temp_re_tmp = i + iy;
        temp_re_tmp = r1[b_temp_re_tmp].im;
        temp_im = r1[b_temp_re_tmp].re;
        temp_re = twid_re * temp_im - twid_im * temp_re_tmp;
        temp_im = twid_re * temp_re_tmp + twid_im * temp_im;
        r1[b_temp_re_tmp].re = r1[i].re - temp_re;
        r1[b_temp_re_tmp].im = r1[i].im - temp_im;
        r1[i].re += temp_re;
        r1[i].im += temp_im;
        i += ju;
      }
      istart++;
    }
    k /= 2;
    iy = ju;
    ju += ju;
    iheight -= iy;
  }
  iy = r->size[0];
  for (ju = 0; ju < iy; ju++) {
    y_data[ju] = r1[ju];
  }
  emxFree_creal_T(&r);
}

/*
 * Arguments    : const emxArray_creal_T *x
 *                int n1_unsigned
 *                const emxArray_real_T *costab
 *                const emxArray_real_T *sintab
 *                emxArray_creal_T *y
 * Return Type  : void
 */
void g_FFTImplementationCallback_r2b(const emxArray_creal_T *x, int n1_unsigned,
                                     const emxArray_real_T *costab,
                                     const emxArray_real_T *sintab,
                                     emxArray_creal_T *y)
{
  emxArray_creal_T *r1;
  const creal_T *x_data;
  creal_T *r;
  creal_T *y_data;
  const double *costab_data;
  const double *sintab_data;
  double temp_im;
  double temp_re;
  double temp_re_tmp;
  double twid_im;
  double twid_re;
  int b_i;
  int b_temp_re_tmp;
  int chan;
  int i;
  int iDelta2;
  int iheight;
  int iy;
  int j;
  int ju;
  int k;
  int loop_ub;
  int nRowsD2;
  int nrows;
  int xoff;
  bool tst;
  sintab_data = sintab->data;
  costab_data = costab->data;
  x_data = x->data;
  nrows = x->size[0];
  i = y->size[0] * y->size[1] * y->size[2];
  y->size[0] = n1_unsigned;
  y->size[1] = x->size[1];
  y->size[2] = x->size[2];
  emxEnsureCapacity_creal_T(y, i);
  y_data = y->data;
  if (n1_unsigned > x->size[0]) {
    i = y->size[0] * y->size[1] * y->size[2];
    y->size[0] = n1_unsigned;
    y->size[1] = x->size[1];
    y->size[2] = x->size[2];
    emxEnsureCapacity_creal_T(y, i);
    y_data = y->data;
    loop_ub = n1_unsigned * x->size[1] * x->size[2];
    for (i = 0; i < loop_ub; i++) {
      y_data[i].re = 0.0;
      y_data[i].im = 0.0;
    }
  }
  loop_ub = x->size[1] * x->size[2] - 1;
#pragma omp parallel num_threads(omp_get_max_threads()) private(               \
    r, r1, xoff, ju, iy, j, iheight, nRowsD2, k, b_i, iDelta2, tst,            \
    temp_re_tmp, temp_im, temp_re, twid_re, b_temp_re_tmp, twid_im)
  {
    emxInit_creal_T(&r1, 1);
#pragma omp for nowait
    for (chan = 0; chan <= loop_ub; chan++) {
      xoff = chan * nrows;
      ju = r1->size[0];
      r1->size[0] = n1_unsigned;
      emxEnsureCapacity_creal_T(r1, ju);
      r = r1->data;
      if (n1_unsigned > x->size[0]) {
        ju = r1->size[0];
        r1->size[0] = n1_unsigned;
        emxEnsureCapacity_creal_T(r1, ju);
        r = r1->data;
        for (ju = 0; ju < n1_unsigned; ju++) {
          r[ju].re = 0.0;
          r[ju].im = 0.0;
        }
      }
      iy = x->size[0];
      j = n1_unsigned;
      if (iy <= n1_unsigned) {
        j = iy;
      }
      iheight = n1_unsigned - 2;
      nRowsD2 = n1_unsigned / 2;
      k = nRowsD2 / 2;
      iy = 0;
      ju = 0;
      for (b_i = 0; b_i <= j - 2; b_i++) {
        r[iy] = x_data[xoff + b_i];
        iDelta2 = n1_unsigned;
        tst = true;
        while (tst) {
          iDelta2 >>= 1;
          ju ^= iDelta2;
          tst = ((ju & iDelta2) == 0);
        }
        iy = ju;
      }
      r[iy] = x_data[(xoff + j) - 1];
      if (n1_unsigned > 1) {
        for (b_i = 0; b_i <= iheight; b_i += 2) {
          temp_re_tmp = r[b_i + 1].re;
          temp_im = r[b_i + 1].im;
          temp_re = r[b_i].re;
          twid_re = r[b_i].im;
          r[b_i + 1].re = temp_re - temp_re_tmp;
          r[b_i + 1].im = twid_re - temp_im;
          r[b_i].re = temp_re + temp_re_tmp;
          r[b_i].im = twid_re + temp_im;
        }
      }
      iy = 2;
      iDelta2 = 4;
      iheight = ((k - 1) << 2) + 1;
      while (k > 0) {
        for (b_i = 0; b_i < iheight; b_i += iDelta2) {
          b_temp_re_tmp = b_i + iy;
          temp_re = r[b_temp_re_tmp].re;
          temp_im = r[b_temp_re_tmp].im;
          r[b_temp_re_tmp].re = r[b_i].re - temp_re;
          r[b_temp_re_tmp].im = r[b_i].im - temp_im;
          r[b_i].re += temp_re;
          r[b_i].im += temp_im;
        }
        ju = 1;
        for (j = k; j < nRowsD2; j += k) {
          twid_re = costab_data[j];
          twid_im = sintab_data[j];
          b_i = ju;
          xoff = ju + iheight;
          while (b_i < xoff) {
            b_temp_re_tmp = b_i + iy;
            temp_re_tmp = r[b_temp_re_tmp].im;
            temp_im = r[b_temp_re_tmp].re;
            temp_re = twid_re * temp_im - twid_im * temp_re_tmp;
            temp_im = twid_re * temp_re_tmp + twid_im * temp_im;
            r[b_temp_re_tmp].re = r[b_i].re - temp_re;
            r[b_temp_re_tmp].im = r[b_i].im - temp_im;
            r[b_i].re += temp_re;
            r[b_i].im += temp_im;
            b_i += iDelta2;
          }
          ju++;
        }
        k /= 2;
        iy = iDelta2;
        iDelta2 += iDelta2;
        iheight -= iy;
      }
      iy = y->size[0];
      iDelta2 = r1->size[0];
      for (ju = 0; ju < iDelta2; ju++) {
        y_data[ju + iy * chan] = r[ju];
      }
    }
    emxFree_creal_T(&r1);
  }
}

/*
 * File trailer for FFTImplementationCallback.c
 *
 * [EOF]
 */
