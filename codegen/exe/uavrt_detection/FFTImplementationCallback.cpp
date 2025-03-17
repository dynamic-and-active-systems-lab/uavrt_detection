//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: FFTImplementationCallback.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "FFTImplementationCallback.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include "omp.h"
#include <cmath>

// Variable Definitions
static rtDoubleCheckInfo i_emlrtDCI{
    33,                    // lineNo
    "bluestein_setup_impl" // fName
};

// Function Definitions
//
// Arguments    : const array<creal32_T, 1U> &x
//                int unsigned_nRows
//                const array<float, 2U> &costab
//                const array<float, 2U> &sintab
//                array<creal32_T, 1U> &y
// Return Type  : void
//
namespace coder {
namespace internal {
namespace fft {
void FFTImplementationCallback::r2br_r2dit_trig_impl(
    const array<creal32_T, 1U> &x, int unsigned_nRows,
    const array<float, 2U> &costab, const array<float, 2U> &sintab,
    array<creal32_T, 1U> &y)
{
  float im;
  float temp_im;
  float temp_re;
  float temp_re_tmp;
  int i;
  int iDelta2;
  int iheight;
  int iy;
  int ju;
  int k;
  int nRowsD2;
  y.set_size(unsigned_nRows);
  if (unsigned_nRows > x.size(0)) {
    y.set_size(unsigned_nRows);
    for (iy = 0; iy < unsigned_nRows; iy++) {
      y[iy].re = 0.0F;
      y[iy].im = 0.0F;
    }
  }
  if (x.size(0) <= unsigned_nRows) {
    iDelta2 = x.size(0) - 1;
  } else {
    iDelta2 = unsigned_nRows - 1;
  }
  iheight = unsigned_nRows - 2;
  nRowsD2 = unsigned_nRows / 2;
  k = nRowsD2 / 2;
  iy = 0;
  ju = 0;
  if (iDelta2 > 2147483646) {
    check_forloop_overflow_error();
  }
  for (i = 0; i < iDelta2; i++) {
    boolean_T tst;
    y[iy] = x[i];
    iy = unsigned_nRows;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }
    iy = ju;
  }
  if (iDelta2 - 1 < 0) {
    iDelta2 = 0;
  }
  y[iy] = x[iDelta2];
  if (unsigned_nRows > 1) {
    for (i = 0; i <= iheight; i += 2) {
      temp_re_tmp = y[i + 1].re;
      temp_im = y[i + 1].im;
      temp_re = y[i].re;
      im = y[i].im;
      y[i + 1].re = temp_re - temp_re_tmp;
      y[i + 1].im = y[i].im - y[i + 1].im;
      im += temp_im;
      y[i].re = temp_re + temp_re_tmp;
      y[i].im = im;
    }
  }
  iy = 2;
  iDelta2 = 4;
  iheight = ((k - 1) << 2) + 1;
  while (k > 0) {
    int b_temp_re_tmp;
    for (i = 0; i < iheight; i += iDelta2) {
      b_temp_re_tmp = i + iy;
      temp_re = y[b_temp_re_tmp].re;
      temp_im = y[b_temp_re_tmp].im;
      y[b_temp_re_tmp].re = y[i].re - temp_re;
      y[b_temp_re_tmp].im = y[i].im - temp_im;
      y[i].re = y[i].re + temp_re;
      y[i].im = y[i].im + temp_im;
    }
    ju = 1;
    for (int j{k}; j < nRowsD2; j += k) {
      float twid_im;
      float twid_re;
      int ihi;
      twid_re = costab[j];
      twid_im = sintab[j];
      i = ju;
      ihi = ju + iheight;
      while (i < ihi) {
        b_temp_re_tmp = i + iy;
        temp_re_tmp = y[b_temp_re_tmp].im;
        im = y[b_temp_re_tmp].re;
        temp_re = twid_re * im - twid_im * temp_re_tmp;
        temp_im = twid_re * temp_re_tmp + twid_im * im;
        y[b_temp_re_tmp].re = y[i].re - temp_re;
        y[b_temp_re_tmp].im = y[i].im - temp_im;
        y[i].re = y[i].re + temp_re;
        y[i].im = y[i].im + temp_im;
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

//
// Arguments    : const array<creal_T, 1U> &x
//                int unsigned_nRows
//                const array<double, 2U> &costab
//                const array<double, 2U> &sintab
//                array<creal_T, 1U> &y
// Return Type  : void
//
void FFTImplementationCallback::r2br_r2dit_trig_impl(
    const array<creal_T, 1U> &x, int unsigned_nRows,
    const array<double, 2U> &costab, const array<double, 2U> &sintab,
    array<creal_T, 1U> &y)
{
  double im;
  double temp_im;
  double temp_re;
  double temp_re_tmp;
  int i;
  int iDelta2;
  int iheight;
  int iy;
  int ju;
  int k;
  int nRowsD2;
  y.set_size(unsigned_nRows);
  if (unsigned_nRows > x.size(0)) {
    y.set_size(unsigned_nRows);
    for (iy = 0; iy < unsigned_nRows; iy++) {
      y[iy].re = 0.0;
      y[iy].im = 0.0;
    }
  }
  if (x.size(0) <= unsigned_nRows) {
    iDelta2 = x.size(0) - 1;
  } else {
    iDelta2 = unsigned_nRows - 1;
  }
  iheight = unsigned_nRows - 2;
  nRowsD2 = unsigned_nRows / 2;
  k = nRowsD2 / 2;
  iy = 0;
  ju = 0;
  if (iDelta2 > 2147483646) {
    check_forloop_overflow_error();
  }
  for (i = 0; i < iDelta2; i++) {
    boolean_T tst;
    y[iy] = x[i];
    iy = unsigned_nRows;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }
    iy = ju;
  }
  if (iDelta2 - 1 < 0) {
    iDelta2 = 0;
  }
  y[iy] = x[iDelta2];
  if (unsigned_nRows > 1) {
    for (i = 0; i <= iheight; i += 2) {
      temp_re_tmp = y[i + 1].re;
      temp_im = y[i + 1].im;
      temp_re = y[i].re;
      im = y[i].im;
      y[i + 1].re = temp_re - temp_re_tmp;
      y[i + 1].im = y[i].im - y[i + 1].im;
      im += temp_im;
      y[i].re = temp_re + temp_re_tmp;
      y[i].im = im;
    }
  }
  iy = 2;
  iDelta2 = 4;
  iheight = ((k - 1) << 2) + 1;
  while (k > 0) {
    int b_temp_re_tmp;
    for (i = 0; i < iheight; i += iDelta2) {
      b_temp_re_tmp = i + iy;
      temp_re = y[b_temp_re_tmp].re;
      temp_im = y[b_temp_re_tmp].im;
      y[b_temp_re_tmp].re = y[i].re - temp_re;
      y[b_temp_re_tmp].im = y[i].im - temp_im;
      y[i].re = y[i].re + temp_re;
      y[i].im = y[i].im + temp_im;
    }
    ju = 1;
    for (int j{k}; j < nRowsD2; j += k) {
      double twid_im;
      double twid_re;
      int ihi;
      twid_re = costab[j];
      twid_im = sintab[j];
      i = ju;
      ihi = ju + iheight;
      while (i < ihi) {
        b_temp_re_tmp = i + iy;
        temp_re_tmp = y[b_temp_re_tmp].im;
        im = y[b_temp_re_tmp].re;
        temp_re = twid_re * im - twid_im * temp_re_tmp;
        temp_im = twid_re * temp_re_tmp + twid_im * im;
        y[b_temp_re_tmp].re = y[i].re - temp_re;
        y[b_temp_re_tmp].im = y[i].im - temp_im;
        y[i].re = y[i].re + temp_re;
        y[i].im = y[i].im + temp_im;
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

//
// Arguments    : const array<creal32_T, 2U> &x
//                int n2blue
//                int nfft
//                const array<float, 2U> &costab
//                const array<float, 2U> &sintab
//                const array<float, 2U> &sintabinv
//                array<creal32_T, 2U> &y
// Return Type  : void
//
void FFTImplementationCallback::dobluesteinfft(
    const array<creal32_T, 2U> &x, int n2blue, int nfft,
    const array<float, 2U> &costab, const array<float, 2U> &sintab,
    const array<float, 2U> &sintabinv, array<creal32_T, 2U> &y)
{
  array<creal32_T, 1U> fv;
  array<creal32_T, 1U> fy;
  array<creal32_T, 1U> r;
  array<creal32_T, 1U> wwc;
  float temp_im;
  float temp_re;
  float twid_im;
  float twid_re;
  int b_i;
  int b_k;
  int b_y;
  int i;
  int ihi;
  int istart;
  int iy;
  int ju;
  int minNrowsNx;
  int nInt2;
  int nInt2m1;
  int nRowsD2;
  int rt;
  int xoff;
  boolean_T tst;
  nInt2m1 = (nfft + nfft) - 1;
  if (nInt2m1 < 0) {
    rtNonNegativeError(static_cast<double>(nInt2m1), i_emlrtDCI);
  }
  wwc.set_size(nInt2m1);
  rt = 0;
  wwc[nfft - 1].re = 1.0F;
  wwc[nfft - 1].im = 0.0F;
  nInt2 = nfft << 1;
  if (nfft - 1 > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{0}; k <= nfft - 2; k++) {
    float nt_im;
    b_y = ((k + 1) << 1) - 1;
    if (nInt2 - rt <= b_y) {
      rt += b_y - nInt2;
    } else {
      rt += b_y;
    }
    nt_im = -3.14159274F * static_cast<float>(rt) / static_cast<float>(nfft);
    i = (nfft - k) - 2;
    wwc[i].re = std::cos(nt_im);
    wwc[i].im = -std::sin(nt_im);
  }
  i = nInt2m1 - 1;
  for (int k{i}; k >= nfft; k--) {
    wwc[k] = wwc[(nInt2m1 - k) - 1];
  }
  nInt2m1 = x.size(0);
  y.set_size(nfft, x.size(1));
  if (nfft > x.size(0)) {
    y.set_size(nfft, x.size(1));
    b_y = nfft * x.size(1);
    for (i = 0; i < b_y; i++) {
      y[i].re = 0.0F;
      y[i].im = 0.0F;
    }
  }
  if (x.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  b_y = x.size(1);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
        fv, fy, r, xoff, minNrowsNx, b_k, iy, temp_re, temp_im, istart,        \
            nRowsD2, ju, b_i, tst, twid_re, twid_im, ihi)

  for (int chan = 0; chan < b_y; chan++) {
    xoff = chan * nInt2m1;
    r.set_size(nfft);
    if (nfft > x.size(0)) {
      r.set_size(nfft);
      for (minNrowsNx = 0; minNrowsNx < nfft; minNrowsNx++) {
        r[minNrowsNx].re = 0.0F;
        r[minNrowsNx].im = 0.0F;
      }
    }
    minNrowsNx = x.size(0);
    if (nfft <= minNrowsNx) {
      minNrowsNx = nfft;
    }
    if (minNrowsNx > 2147483646) {
      check_forloop_overflow_error();
    }
    for (b_k = 0; b_k < minNrowsNx; b_k++) {
      temp_re = wwc[(nfft + b_k) - 1].re;
      temp_im = wwc[(nfft + b_k) - 1].im;
      r[b_k].re = temp_re * x[xoff + b_k].re + temp_im * x[xoff + b_k].im;
      r[b_k].im = temp_re * x[xoff + b_k].im - temp_im * x[xoff + b_k].re;
    }
    iy = minNrowsNx + 1;
    if ((minNrowsNx + 1 <= nfft) && (nfft > 2147483646)) {
      check_forloop_overflow_error();
    }
    for (b_k = iy; b_k <= nfft; b_k++) {
      r[b_k - 1].re = 0.0F;
      r[b_k - 1].im = 0.0F;
    }
    fy.set_size(n2blue);
    if (n2blue > r.size(0)) {
      fy.set_size(n2blue);
      for (minNrowsNx = 0; minNrowsNx < n2blue; minNrowsNx++) {
        fy[minNrowsNx].re = 0.0F;
        fy[minNrowsNx].im = 0.0F;
      }
    }
    if (r.size(0) <= n2blue) {
      minNrowsNx = r.size(0) - 1;
    } else {
      minNrowsNx = n2blue - 1;
    }
    istart = n2blue - 2;
    nRowsD2 = n2blue / 2;
    b_k = nRowsD2 / 2;
    iy = 0;
    ju = 0;
    if (minNrowsNx > 2147483646) {
      check_forloop_overflow_error();
    }
    for (b_i = 0; b_i < minNrowsNx; b_i++) {
      fy[iy] = r[b_i];
      xoff = n2blue;
      tst = true;
      while (tst) {
        xoff >>= 1;
        ju ^= xoff;
        tst = ((ju & xoff) == 0);
      }
      iy = ju;
    }
    if (minNrowsNx - 1 < 0) {
      minNrowsNx = 0;
    }
    fy[iy] = r[minNrowsNx];
    if (n2blue > 1) {
      for (b_i = 0; b_i <= istart; b_i += 2) {
        temp_re = fy[b_i + 1].re;
        temp_im = fy[b_i + 1].im;
        twid_re = fy[b_i].re;
        twid_im = fy[b_i].im;
        fy[b_i + 1].re = fy[b_i].re - fy[b_i + 1].re;
        fy[b_i + 1].im = fy[b_i].im - fy[b_i + 1].im;
        twid_re += temp_re;
        twid_im += temp_im;
        fy[b_i].re = twid_re;
        fy[b_i].im = twid_im;
      }
    }
    xoff = 2;
    minNrowsNx = 4;
    iy = ((b_k - 1) << 2) + 1;
    while (b_k > 0) {
      for (b_i = 0; b_i < iy; b_i += minNrowsNx) {
        temp_re = fy[b_i + xoff].re;
        temp_im = fy[b_i + xoff].im;
        fy[b_i + xoff].re = fy[b_i].re - temp_re;
        fy[b_i + xoff].im = fy[b_i].im - temp_im;
        fy[b_i].re = fy[b_i].re + temp_re;
        fy[b_i].im = fy[b_i].im + temp_im;
      }
      istart = 1;
      for (ju = b_k; ju < nRowsD2; ju += b_k) {
        twid_re = costab[ju];
        twid_im = sintab[ju];
        b_i = istart;
        ihi = istart + iy;
        while (b_i < ihi) {
          temp_re = twid_re * fy[b_i + xoff].re - twid_im * fy[b_i + xoff].im;
          temp_im = twid_re * fy[b_i + xoff].im + twid_im * fy[b_i + xoff].re;
          fy[b_i + xoff].re = fy[b_i].re - temp_re;
          fy[b_i + xoff].im = fy[b_i].im - temp_im;
          fy[b_i].re = fy[b_i].re + temp_re;
          fy[b_i].im = fy[b_i].im + temp_im;
          b_i += minNrowsNx;
        }
        istart++;
      }
      b_k /= 2;
      xoff = minNrowsNx;
      minNrowsNx += minNrowsNx;
      iy -= xoff;
    }
    FFTImplementationCallback::r2br_r2dit_trig_impl(wwc, n2blue, costab, sintab,
                                                    fv);
    iy = fy.size(0);
    for (minNrowsNx = 0; minNrowsNx < iy; minNrowsNx++) {
      twid_im = fy[minNrowsNx].re * fv[minNrowsNx].im +
                fy[minNrowsNx].im * fv[minNrowsNx].re;
      fy[minNrowsNx].re = fy[minNrowsNx].re * fv[minNrowsNx].re -
                          fy[minNrowsNx].im * fv[minNrowsNx].im;
      fy[minNrowsNx].im = twid_im;
    }
    FFTImplementationCallback::r2br_r2dit_trig_impl(fy, n2blue, costab,
                                                    sintabinv, fv);
    if (fv.size(0) > 1) {
      twid_re = 1.0F / static_cast<float>(fv.size(0));
      iy = fv.size(0);
      for (minNrowsNx = 0; minNrowsNx < iy; minNrowsNx++) {
        fv[minNrowsNx].re = twid_re * fv[minNrowsNx].re;
        fv[minNrowsNx].im = twid_re * fv[minNrowsNx].im;
      }
    }
    iy = static_cast<int>(static_cast<float>(nfft));
    xoff = wwc.size(0);
    if ((static_cast<int>(static_cast<float>(nfft)) <= wwc.size(0)) &&
        (wwc.size(0) > 2147483646)) {
      check_forloop_overflow_error();
    }
    for (b_k = iy; b_k <= xoff; b_k++) {
      r[b_k - static_cast<int>(static_cast<float>(nfft))].re =
          wwc[b_k - 1].re * fv[b_k - 1].re + wwc[b_k - 1].im * fv[b_k - 1].im;
      r[b_k - static_cast<int>(static_cast<float>(nfft))].im =
          wwc[b_k - 1].re * fv[b_k - 1].im - wwc[b_k - 1].im * fv[b_k - 1].re;
    }
    iy = y.size(0);
    for (minNrowsNx = 0; minNrowsNx < iy; minNrowsNx++) {
      y[minNrowsNx + y.size(0) * chan] = r[minNrowsNx];
    }
  }
}

//
// Arguments    : const array<creal_T, 2U> &x
//                int n2blue
//                int nfft
//                const array<double, 2U> &costab
//                const array<double, 2U> &sintab
//                const array<double, 2U> &sintabinv
//                array<creal_T, 2U> &y
// Return Type  : void
//
void FFTImplementationCallback::dobluesteinfft(
    const array<creal_T, 2U> &x, int n2blue, int nfft,
    const array<double, 2U> &costab, const array<double, 2U> &sintab,
    const array<double, 2U> &sintabinv, array<creal_T, 2U> &y)
{
  array<creal_T, 1U> fv;
  array<creal_T, 1U> fy;
  array<creal_T, 1U> r;
  array<creal_T, 1U> wwc;
  double b_re_tmp;
  double nt_im;
  double nt_re;
  double re_tmp;
  int b_y;
  int i;
  int nInt2;
  int nInt2m1;
  int rt;
  nInt2m1 = (nfft + nfft) - 1;
  if (nInt2m1 < 0) {
    rtNonNegativeError(static_cast<double>(nInt2m1), i_emlrtDCI);
  }
  wwc.set_size(nInt2m1);
  rt = 0;
  wwc[nfft - 1].re = 1.0;
  wwc[nfft - 1].im = 0.0;
  nInt2 = nfft << 1;
  if (nfft - 1 > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{0}; k <= nfft - 2; k++) {
    b_y = ((k + 1) << 1) - 1;
    if (nInt2 - rt <= b_y) {
      rt += b_y - nInt2;
    } else {
      rt += b_y;
    }
    nt_im = -3.1415926535897931 * static_cast<double>(rt) /
            static_cast<double>(nfft);
    i = (nfft - k) - 2;
    wwc[i].re = std::cos(nt_im);
    wwc[i].im = -std::sin(nt_im);
  }
  i = nInt2m1 - 1;
  for (int k{i}; k >= nfft; k--) {
    wwc[k] = wwc[(nInt2m1 - k) - 1];
  }
  y.set_size(nfft, 1);
  if (nfft > x.size(0)) {
    y.set_size(nfft, 1);
    for (i = 0; i < nfft; i++) {
      y[i].re = 0.0;
      y[i].im = 0.0;
    }
  }
  rt = x.size(0);
  if (nfft <= rt) {
    rt = nfft;
  }
  nInt2 = rt + 1;
  r.set_size(nfft);
  if (nfft > x.size(0)) {
    r.set_size(nfft);
    for (i = 0; i < nfft; i++) {
      r[i].re = 0.0;
      r[i].im = 0.0;
    }
  }
  if (rt > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{0}; k < rt; k++) {
    b_y = (nfft + k) - 1;
    nt_re = wwc[b_y].re;
    nt_im = wwc[b_y].im;
    re_tmp = x[k].im;
    b_re_tmp = x[k].re;
    r[k].re = nt_re * b_re_tmp + nt_im * re_tmp;
    r[k].im = nt_re * re_tmp - nt_im * b_re_tmp;
  }
  if ((rt + 1 <= nfft) && (nfft > 2147483646)) {
    check_forloop_overflow_error();
  }
  for (int k{nInt2}; k <= nfft; k++) {
    r[k - 1].re = 0.0;
    r[k - 1].im = 0.0;
  }
  FFTImplementationCallback::r2br_r2dit_trig_impl(r, n2blue, costab, sintab,
                                                  fy);
  FFTImplementationCallback::r2br_r2dit_trig_impl(wwc, n2blue, costab, sintab,
                                                  fv);
  b_y = fy.size(0);
  for (i = 0; i < b_y; i++) {
    nt_re = fy[i].re;
    nt_im = fv[i].im;
    re_tmp = fy[i].im;
    b_re_tmp = fv[i].re;
    fy[i].re = nt_re * b_re_tmp - re_tmp * nt_im;
    fy[i].im = nt_re * nt_im + re_tmp * b_re_tmp;
  }
  FFTImplementationCallback::r2br_r2dit_trig_impl(fy, n2blue, costab, sintabinv,
                                                  fv);
  if (fv.size(0) > 1) {
    nt_re = 1.0 / static_cast<double>(fv.size(0));
    b_y = fv.size(0);
    for (i = 0; i < b_y; i++) {
      fv[i].re = nt_re * fv[i].re;
      fv[i].im = nt_re * fv[i].im;
    }
  }
  if ((nfft <= wwc.size(0)) && (wwc.size(0) > 2147483646)) {
    check_forloop_overflow_error();
  }
  for (int k{nfft}; k <= nInt2m1; k++) {
    re_tmp = wwc[k - 1].re;
    b_re_tmp = fv[k - 1].im;
    nt_re = wwc[k - 1].im;
    nt_im = fv[k - 1].re;
    i = k - nfft;
    r[i].re = re_tmp * nt_im + nt_re * b_re_tmp;
    r[i].im = re_tmp * b_re_tmp - nt_re * nt_im;
  }
  b_y = y.size(0);
  for (i = 0; i < b_y; i++) {
    y[i] = r[i];
  }
}

//
// Arguments    : const array<creal_T, 3U> &x
//                int n2blue
//                int nfft
//                const array<double, 2U> &costab
//                const array<double, 2U> &sintab
//                const array<double, 2U> &sintabinv
//                array<creal_T, 3U> &y
// Return Type  : void
//
void FFTImplementationCallback::dobluesteinfft(
    const array<creal_T, 3U> &x, int n2blue, int nfft,
    const array<double, 2U> &costab, const array<double, 2U> &sintab,
    const array<double, 2U> &sintabinv, array<creal_T, 3U> &y)
{
  array<creal_T, 1U> fv;
  array<creal_T, 1U> fy;
  array<creal_T, 1U> r;
  array<creal_T, 1U> wwc;
  double a_im;
  double a_re;
  int b_k;
  int b_y;
  int i;
  int minNrowsNx;
  int nChan;
  int nInt2;
  int nInt2m1;
  int rt;
  int u0;
  int xoff;
  nChan = x.size(1) * x.size(2);
  nInt2m1 = (nfft + nfft) - 1;
  if (nInt2m1 < 0) {
    rtNonNegativeError(static_cast<double>(nInt2m1), i_emlrtDCI);
  }
  wwc.set_size(nInt2m1);
  rt = 0;
  wwc[nfft - 1].re = 1.0;
  wwc[nfft - 1].im = 0.0;
  nInt2 = nfft << 1;
  if (nfft - 1 > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{0}; k <= nfft - 2; k++) {
    double nt_im;
    b_y = ((k + 1) << 1) - 1;
    if (nInt2 - rt <= b_y) {
      rt += b_y - nInt2;
    } else {
      rt += b_y;
    }
    nt_im = -3.1415926535897931 * static_cast<double>(rt) /
            static_cast<double>(nfft);
    i = (nfft - k) - 2;
    wwc[i].re = std::cos(nt_im);
    wwc[i].im = -std::sin(nt_im);
  }
  i = nInt2m1 - 1;
  for (int k{i}; k >= nfft; k--) {
    wwc[k] = wwc[(nInt2m1 - k) - 1];
  }
  nInt2m1 = x.size(0);
  y.set_size(nfft, x.size(1), x.size(2));
  if (nfft > x.size(0)) {
    y.set_size(nfft, x.size(1), x.size(2));
    b_y = nfft * x.size(1) * x.size(2);
    for (i = 0; i < b_y; i++) {
      y[i].re = 0.0;
      y[i].im = 0.0;
    }
  }
  if (nChan > 2147483646) {
    check_forloop_overflow_error();
  }
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
        fv, fy, r, xoff, minNrowsNx, b_k, u0, a_re, a_im)

  for (int chan = 0; chan < nChan; chan++) {
    xoff = chan * nInt2m1;
    r.set_size(nfft);
    if (nfft > x.size(0)) {
      r.set_size(nfft);
      for (minNrowsNx = 0; minNrowsNx < nfft; minNrowsNx++) {
        r[minNrowsNx].re = 0.0;
        r[minNrowsNx].im = 0.0;
      }
    }
    minNrowsNx = x.size(0);
    if (nfft <= minNrowsNx) {
      minNrowsNx = nfft;
    }
    if (minNrowsNx > 2147483646) {
      check_forloop_overflow_error();
    }
    for (b_k = 0; b_k < minNrowsNx; b_k++) {
      a_re = wwc[(nfft + b_k) - 1].re;
      a_im = wwc[(nfft + b_k) - 1].im;
      r[b_k].re = a_re * x[xoff + b_k].re + a_im * x[xoff + b_k].im;
      r[b_k].im = a_re * x[xoff + b_k].im - a_im * x[xoff + b_k].re;
    }
    u0 = minNrowsNx + 1;
    if ((minNrowsNx + 1 <= nfft) && (nfft > 2147483646)) {
      check_forloop_overflow_error();
    }
    for (b_k = u0; b_k <= nfft; b_k++) {
      r[b_k - 1].re = 0.0;
      r[b_k - 1].im = 0.0;
    }
    FFTImplementationCallback::r2br_r2dit_trig_impl(r, n2blue, costab, sintab,
                                                    fy);
    FFTImplementationCallback::r2br_r2dit_trig_impl(wwc, n2blue, costab, sintab,
                                                    fv);
    u0 = fy.size(0);
    for (minNrowsNx = 0; minNrowsNx < u0; minNrowsNx++) {
      a_re = fy[minNrowsNx].re * fv[minNrowsNx].im +
             fy[minNrowsNx].im * fv[minNrowsNx].re;
      fy[minNrowsNx].re = fy[minNrowsNx].re * fv[minNrowsNx].re -
                          fy[minNrowsNx].im * fv[minNrowsNx].im;
      fy[minNrowsNx].im = a_re;
    }
    FFTImplementationCallback::r2br_r2dit_trig_impl(fy, n2blue, costab,
                                                    sintabinv, fv);
    if (fv.size(0) > 1) {
      a_re = 1.0 / static_cast<double>(fv.size(0));
      u0 = fv.size(0);
      for (minNrowsNx = 0; minNrowsNx < u0; minNrowsNx++) {
        fv[minNrowsNx].re = a_re * fv[minNrowsNx].re;
        fv[minNrowsNx].im = a_re * fv[minNrowsNx].im;
      }
    }
    u0 = wwc.size(0);
    if ((nfft <= wwc.size(0)) && (wwc.size(0) > 2147483646)) {
      check_forloop_overflow_error();
    }
    for (b_k = nfft; b_k <= u0; b_k++) {
      r[b_k - nfft].re =
          wwc[b_k - 1].re * fv[b_k - 1].re + wwc[b_k - 1].im * fv[b_k - 1].im;
      r[b_k - nfft].im =
          wwc[b_k - 1].re * fv[b_k - 1].im - wwc[b_k - 1].im * fv[b_k - 1].re;
    }
    xoff = y.size(0);
    u0 = y.size(0);
    for (minNrowsNx = 0; minNrowsNx < u0; minNrowsNx++) {
      y[minNrowsNx + xoff * chan] = r[minNrowsNx];
    }
  }
}

//
// Arguments    : int nRows
//                boolean_T useRadix2
//                array<double, 2U> &costab
//                array<double, 2U> &sintab
//                array<double, 2U> &sintabinv
// Return Type  : void
//
void FFTImplementationCallback::generate_twiddle_tables(
    int nRows, boolean_T useRadix2, array<double, 2U> &costab,
    array<double, 2U> &sintab, array<double, 2U> &sintabinv)
{
  array<double, 2U> costab1q;
  double e;
  int n;
  int nd2;
  e = 6.2831853071795862 / static_cast<double>(nRows);
  n = nRows / 2 / 2;
  costab1q.set_size(1, n + 1);
  costab1q[0] = 1.0;
  nd2 = n / 2 - 1;
  for (int k{0}; k <= nd2; k++) {
    costab1q[k + 1] = std::cos(e * (static_cast<double>(k) + 1.0));
  }
  nd2 += 2;
  for (int k{nd2}; k < n; k++) {
    costab1q[k] = std::sin(e * static_cast<double>(n - k));
  }
  costab1q[n] = 0.0;
  if (!useRadix2) {
    int n2;
    n = costab1q.size(1) - 1;
    n2 = (costab1q.size(1) - 1) << 1;
    costab.set_size(1, n2 + 1);
    sintab.set_size(1, n2 + 1);
    costab[0] = 1.0;
    sintab[0] = 0.0;
    sintabinv.set_size(1, n2 + 1);
    for (int k{0}; k < n; k++) {
      sintabinv[k + 1] = costab1q[(n - k) - 1];
    }
    nd2 = costab1q.size(1);
    for (int k{nd2}; k <= n2; k++) {
      sintabinv[k] = costab1q[k - n];
    }
    for (int k{0}; k < n; k++) {
      costab[k + 1] = costab1q[k + 1];
      sintab[k + 1] = -costab1q[(n - k) - 1];
    }
    for (int k{nd2}; k <= n2; k++) {
      costab[k] = -costab1q[n2 - k];
      sintab[k] = -costab1q[k - n];
    }
  } else {
    int n2;
    n = costab1q.size(1) - 1;
    n2 = (costab1q.size(1) - 1) << 1;
    costab.set_size(1, n2 + 1);
    sintab.set_size(1, n2 + 1);
    costab[0] = 1.0;
    sintab[0] = 0.0;
    for (int k{0}; k < n; k++) {
      costab[k + 1] = costab1q[k + 1];
      sintab[k + 1] = -costab1q[(n - k) - 1];
    }
    nd2 = costab1q.size(1);
    for (int k{nd2}; k <= n2; k++) {
      costab[k] = -costab1q[n2 - k];
      sintab[k] = -costab1q[k - n];
    }
    sintabinv.set_size(1, 0);
  }
}

//
// Arguments    : int nfft
//                boolean_T useRadix2
//                int &nRows
// Return Type  : int
//
int FFTImplementationCallback::get_algo_sizes(int nfft, boolean_T useRadix2,
                                              int &nRows)
{
  static rtRunTimeErrorInfo rc_emlrtRTEI{
      792,                                       // lineNo
      "FFTImplementationCallback/get_algo_sizes" // fName
  };
  int n2blue;
  n2blue = 1;
  if (useRadix2) {
    nRows = nfft;
  } else {
    int n;
    if (nfft > 0) {
      n = (nfft + nfft) - 1;
      n2blue = 31;
      if (n <= 1) {
        n2blue = 0;
      } else {
        int pmin;
        boolean_T exitg1;
        pmin = 0;
        exitg1 = false;
        while ((!exitg1) && (n2blue - pmin > 1)) {
          int k;
          int pow2p;
          k = (pmin + n2blue) >> 1;
          pow2p = 1 << k;
          if (pow2p == n) {
            n2blue = k;
            exitg1 = true;
          } else if (pow2p > n) {
            n2blue = k;
          } else {
            pmin = k;
          }
        }
      }
      n2blue = 1 << n2blue;
    }
    n = nfft << 2;
    if (n < 1) {
      n = 1;
    }
    if (n2blue > n) {
      g_rtErrorWithMessageID(rc_emlrtRTEI.fName, rc_emlrtRTEI.lineNo);
    }
    nRows = n2blue;
  }
  return n2blue;
}

//
// Arguments    : const array<creal32_T, 2U> &x
//                int n1_unsigned
//                const array<float, 2U> &costab
//                const array<float, 2U> &sintab
//                array<creal32_T, 2U> &y
// Return Type  : void
//
void FFTImplementationCallback::r2br_r2dit_trig(const array<creal32_T, 2U> &x,
                                                int n1_unsigned,
                                                const array<float, 2U> &costab,
                                                const array<float, 2U> &sintab,
                                                array<creal32_T, 2U> &y)
{
  array<creal32_T, 1U> r;
  float temp_im;
  float temp_re;
  float twid_im;
  float twid_re;
  int b_i;
  int iDelta2;
  int iheight;
  int istart;
  int iy;
  int ju;
  int k;
  int loop_ub_tmp;
  int nRowsD2;
  int nrows;
  int xoff;
  boolean_T tst;
  nrows = x.size(0);
  y.set_size(n1_unsigned, x.size(1));
  if (n1_unsigned > x.size(0)) {
    y.set_size(n1_unsigned, x.size(1));
    loop_ub_tmp = n1_unsigned * x.size(1);
    for (int i{0}; i < loop_ub_tmp; i++) {
      y[i].re = 0.0F;
      y[i].im = 0.0F;
    }
  }
  if (x.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  loop_ub_tmp = x.size(1);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
        r, xoff, iDelta2, iheight, istart, nRowsD2, k, iy, ju, b_i, tst,       \
            temp_re, temp_im, twid_re, twid_im)

  for (int chan = 0; chan < loop_ub_tmp; chan++) {
    xoff = chan * nrows;
    r.set_size(n1_unsigned);
    if (n1_unsigned > x.size(0)) {
      r.set_size(n1_unsigned);
      for (iDelta2 = 0; iDelta2 < n1_unsigned; iDelta2++) {
        r[iDelta2].re = 0.0F;
        r[iDelta2].im = 0.0F;
      }
    }
    if (x.size(0) <= n1_unsigned) {
      iheight = x.size(0) - 1;
    } else {
      iheight = n1_unsigned - 1;
    }
    istart = n1_unsigned - 2;
    nRowsD2 = n1_unsigned / 2;
    k = nRowsD2 / 2;
    iy = 0;
    ju = 0;
    if (iheight > 2147483646) {
      check_forloop_overflow_error();
    }
    for (b_i = 0; b_i < iheight; b_i++) {
      r[iy] = x[xoff + b_i];
      iDelta2 = n1_unsigned;
      tst = true;
      while (tst) {
        iDelta2 >>= 1;
        ju ^= iDelta2;
        tst = ((ju & iDelta2) == 0);
      }
      iy = ju;
    }
    if (iheight - 1 >= 0) {
      xoff += iheight;
    }
    r[iy] = x[xoff];
    if (n1_unsigned > 1) {
      for (b_i = 0; b_i <= istart; b_i += 2) {
        temp_re = r[b_i + 1].re;
        temp_im = r[b_i + 1].im;
        twid_re = r[b_i].re;
        twid_im = r[b_i].im;
        r[b_i + 1].re = r[b_i].re - r[b_i + 1].re;
        r[b_i + 1].im = r[b_i].im - r[b_i + 1].im;
        twid_re += temp_re;
        twid_im += temp_im;
        r[b_i].re = twid_re;
        r[b_i].im = twid_im;
      }
    }
    iy = 2;
    iDelta2 = 4;
    iheight = ((k - 1) << 2) + 1;
    while (k > 0) {
      for (b_i = 0; b_i < iheight; b_i += iDelta2) {
        temp_re = r[b_i + iy].re;
        temp_im = r[b_i + iy].im;
        r[b_i + iy].re = r[b_i].re - temp_re;
        r[b_i + iy].im = r[b_i].im - temp_im;
        r[b_i].re = r[b_i].re + temp_re;
        r[b_i].im = r[b_i].im + temp_im;
      }
      istart = 1;
      for (ju = k; ju < nRowsD2; ju += k) {
        twid_re = costab[ju];
        twid_im = sintab[ju];
        b_i = istart;
        xoff = istart + iheight;
        while (b_i < xoff) {
          temp_re = twid_re * r[b_i + iy].re - twid_im * r[b_i + iy].im;
          temp_im = twid_re * r[b_i + iy].im + twid_im * r[b_i + iy].re;
          r[b_i + iy].re = r[b_i].re - temp_re;
          r[b_i + iy].im = r[b_i].im - temp_im;
          r[b_i].re = r[b_i].re + temp_re;
          r[b_i].im = r[b_i].im + temp_im;
          b_i += iDelta2;
        }
        istart++;
      }
      k /= 2;
      iy = iDelta2;
      iDelta2 += iDelta2;
      iheight -= iy;
    }
    iy = y.size(0);
    for (iDelta2 = 0; iDelta2 < iy; iDelta2++) {
      y[iDelta2 + y.size(0) * chan] = r[iDelta2];
    }
  }
}

//
// Arguments    : const array<creal_T, 2U> &x
//                int n1_unsigned
//                const array<double, 2U> &costab
//                const array<double, 2U> &sintab
//                array<creal_T, 2U> &y
// Return Type  : void
//
void FFTImplementationCallback::r2br_r2dit_trig(const array<creal_T, 2U> &x,
                                                int n1_unsigned,
                                                const array<double, 2U> &costab,
                                                const array<double, 2U> &sintab,
                                                array<creal_T, 2U> &y)
{
  array<creal_T, 1U> r;
  double im;
  double temp_im;
  double temp_re;
  double temp_re_tmp;
  int i;
  int iheight;
  int istart;
  int iy;
  int ju;
  int k;
  int nRowsD2;
  y.set_size(n1_unsigned, 1);
  if (n1_unsigned > x.size(0)) {
    y.set_size(n1_unsigned, 1);
    for (ju = 0; ju < n1_unsigned; ju++) {
      y[ju].re = 0.0;
      y[ju].im = 0.0;
    }
  }
  if (x.size(0) <= n1_unsigned) {
    iheight = x.size(0) - 1;
  } else {
    iheight = n1_unsigned - 1;
  }
  istart = n1_unsigned - 2;
  nRowsD2 = n1_unsigned / 2;
  k = nRowsD2 / 2;
  r.set_size(n1_unsigned);
  if (n1_unsigned > x.size(0)) {
    r.set_size(n1_unsigned);
    for (ju = 0; ju < n1_unsigned; ju++) {
      r[ju].re = 0.0;
      r[ju].im = 0.0;
    }
  }
  iy = 0;
  ju = 0;
  if (iheight > 2147483646) {
    check_forloop_overflow_error();
  }
  for (i = 0; i < iheight; i++) {
    boolean_T tst;
    r[iy] = x[i];
    iy = n1_unsigned;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }
    iy = ju;
  }
  if (iheight - 1 < 0) {
    iheight = 0;
  }
  r[iy] = x[iheight];
  if (n1_unsigned > 1) {
    for (i = 0; i <= istart; i += 2) {
      temp_re_tmp = r[i + 1].re;
      temp_im = r[i + 1].im;
      temp_re = r[i].re;
      im = r[i].im;
      r[i + 1].re = temp_re - temp_re_tmp;
      r[i + 1].im = r[i].im - r[i + 1].im;
      im += temp_im;
      r[i].re = temp_re + temp_re_tmp;
      r[i].im = im;
    }
  }
  iy = 2;
  ju = 4;
  iheight = ((k - 1) << 2) + 1;
  while (k > 0) {
    int b_temp_re_tmp;
    for (i = 0; i < iheight; i += ju) {
      b_temp_re_tmp = i + iy;
      temp_re = r[b_temp_re_tmp].re;
      temp_im = r[b_temp_re_tmp].im;
      r[b_temp_re_tmp].re = r[i].re - temp_re;
      r[b_temp_re_tmp].im = r[i].im - temp_im;
      r[i].re = r[i].re + temp_re;
      r[i].im = r[i].im + temp_im;
    }
    istart = 1;
    for (int j{k}; j < nRowsD2; j += k) {
      double twid_im;
      double twid_re;
      int ihi;
      twid_re = costab[j];
      twid_im = sintab[j];
      i = istart;
      ihi = istart + iheight;
      while (i < ihi) {
        b_temp_re_tmp = i + iy;
        temp_re_tmp = r[b_temp_re_tmp].im;
        im = r[b_temp_re_tmp].re;
        temp_re = twid_re * im - twid_im * temp_re_tmp;
        temp_im = twid_re * temp_re_tmp + twid_im * im;
        r[b_temp_re_tmp].re = r[i].re - temp_re;
        r[b_temp_re_tmp].im = r[i].im - temp_im;
        r[i].re = r[i].re + temp_re;
        r[i].im = r[i].im + temp_im;
        i += ju;
      }
      istart++;
    }
    k /= 2;
    iy = ju;
    ju += ju;
    iheight -= iy;
  }
  iy = y.size(0);
  for (ju = 0; ju < iy; ju++) {
    y[ju] = r[ju];
  }
}

//
// Arguments    : const array<creal_T, 3U> &x
//                int n1_unsigned
//                const array<double, 2U> &costab
//                const array<double, 2U> &sintab
//                array<creal_T, 3U> &y
// Return Type  : void
//
void FFTImplementationCallback::r2br_r2dit_trig(const array<creal_T, 3U> &x,
                                                int n1_unsigned,
                                                const array<double, 2U> &costab,
                                                const array<double, 2U> &sintab,
                                                array<creal_T, 3U> &y)
{
  array<creal_T, 1U> r;
  double temp_im;
  double temp_re;
  double twid_im;
  double twid_re;
  int b_i;
  int iDelta2;
  int iheight;
  int istart;
  int iy;
  int ju;
  int k;
  int nChan;
  int nRowsD2;
  int nrows;
  int xoff;
  boolean_T tst;
  nChan = x.size(1) * x.size(2);
  nrows = x.size(0);
  y.set_size(n1_unsigned, x.size(1), x.size(2));
  if (n1_unsigned > x.size(0)) {
    int loop_ub_tmp;
    y.set_size(n1_unsigned, x.size(1), x.size(2));
    loop_ub_tmp = n1_unsigned * x.size(1) * x.size(2);
    for (int i{0}; i < loop_ub_tmp; i++) {
      y[i].re = 0.0;
      y[i].im = 0.0;
    }
  }
  if (nChan > 2147483646) {
    check_forloop_overflow_error();
  }
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
        r, xoff, iheight, istart, nRowsD2, k, iy, ju, b_i, iDelta2, tst,       \
            temp_re, temp_im, twid_re, twid_im)

  for (int chan = 0; chan < nChan; chan++) {
    xoff = chan * nrows;
    r.set_size(n1_unsigned);
    if (n1_unsigned > x.size(0)) {
      r.set_size(n1_unsigned);
      for (iheight = 0; iheight < n1_unsigned; iheight++) {
        r[iheight].re = 0.0;
        r[iheight].im = 0.0;
      }
    }
    if (x.size(0) <= n1_unsigned) {
      iheight = x.size(0) - 1;
    } else {
      iheight = n1_unsigned - 1;
    }
    istart = n1_unsigned - 2;
    nRowsD2 = n1_unsigned / 2;
    k = nRowsD2 / 2;
    iy = 0;
    ju = 0;
    if (iheight > 2147483646) {
      check_forloop_overflow_error();
    }
    for (b_i = 0; b_i < iheight; b_i++) {
      r[iy] = x[xoff + b_i];
      iDelta2 = n1_unsigned;
      tst = true;
      while (tst) {
        iDelta2 >>= 1;
        ju ^= iDelta2;
        tst = ((ju & iDelta2) == 0);
      }
      iy = ju;
    }
    if (iheight - 1 >= 0) {
      xoff += iheight;
    }
    r[iy] = x[xoff];
    if (n1_unsigned > 1) {
      for (b_i = 0; b_i <= istart; b_i += 2) {
        temp_re = r[b_i + 1].re;
        temp_im = r[b_i + 1].im;
        twid_re = r[b_i].re;
        twid_im = r[b_i].im;
        r[b_i + 1].re = r[b_i].re - r[b_i + 1].re;
        r[b_i + 1].im = r[b_i].im - r[b_i + 1].im;
        twid_re += temp_re;
        twid_im += temp_im;
        r[b_i].re = twid_re;
        r[b_i].im = twid_im;
      }
    }
    iy = 2;
    iDelta2 = 4;
    iheight = ((k - 1) << 2) + 1;
    while (k > 0) {
      for (b_i = 0; b_i < iheight; b_i += iDelta2) {
        temp_re = r[b_i + iy].re;
        temp_im = r[b_i + iy].im;
        r[b_i + iy].re = r[b_i].re - temp_re;
        r[b_i + iy].im = r[b_i].im - temp_im;
        r[b_i].re = r[b_i].re + temp_re;
        r[b_i].im = r[b_i].im + temp_im;
      }
      istart = 1;
      for (ju = k; ju < nRowsD2; ju += k) {
        twid_re = costab[ju];
        twid_im = sintab[ju];
        b_i = istart;
        xoff = istart + iheight;
        while (b_i < xoff) {
          temp_re = twid_re * r[b_i + iy].re - twid_im * r[b_i + iy].im;
          temp_im = twid_re * r[b_i + iy].im + twid_im * r[b_i + iy].re;
          r[b_i + iy].re = r[b_i].re - temp_re;
          r[b_i + iy].im = r[b_i].im - temp_im;
          r[b_i].re = r[b_i].re + temp_re;
          r[b_i].im = r[b_i].im + temp_im;
          b_i += iDelta2;
        }
        istart++;
      }
      k /= 2;
      iy = iDelta2;
      iDelta2 += iDelta2;
      iheight -= iy;
    }
    iy = y.size(0);
    iDelta2 = y.size(0);
    for (iheight = 0; iheight < iDelta2; iheight++) {
      y[iheight + iy * chan] = r[iheight];
    }
  }
}

} // namespace fft
} // namespace internal
} // namespace coder

//
// File trailer for FFTImplementationCallback.cpp
//
// [EOF]
//
