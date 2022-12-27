//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// FFTImplementationCallback.cpp
//
// Code generation for function 'FFTImplementationCallback'
//

// Include files
#include "FFTImplementationCallback.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "omp.h"
#include <cmath>
#include <string.h>

// Function Definitions
namespace coder {
namespace internal {
void FFTImplementationCallback::r2br_r2dit_trig_impl(
    const ::coder::array<creal32_T, 1U> &x, int unsigned_nRows,
    const ::coder::array<float, 2U> &costab,
    const ::coder::array<float, 2U> &sintab, ::coder::array<creal32_T, 1U> &y)
{
  float temp_im;
  float temp_re;
  float temp_re_tmp;
  float twid_re;
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
  iDelta2 = x.size(0);
  if (iDelta2 > unsigned_nRows) {
    iDelta2 = unsigned_nRows;
  }
  iheight = unsigned_nRows - 2;
  nRowsD2 = unsigned_nRows / 2;
  k = nRowsD2 / 2;
  iy = 0;
  ju = 0;
  for (i = 0; i <= iDelta2 - 2; i++) {
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
  y[iy] = x[iDelta2 - 1];
  if (unsigned_nRows > 1) {
    for (i = 0; i <= iheight; i += 2) {
      temp_re_tmp = y[i + 1].re;
      temp_im = y[i + 1].im;
      temp_re = y[i].re;
      twid_re = y[i].im;
      y[i + 1].re = temp_re - temp_re_tmp;
      y[i + 1].im = twid_re - temp_im;
      y[i].re = temp_re + temp_re_tmp;
      y[i].im = twid_re + temp_im;
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
      int ihi;
      twid_re = costab[j];
      twid_im = sintab[j];
      i = ju;
      ihi = ju + iheight;
      while (i < ihi) {
        b_temp_re_tmp = i + iy;
        temp_re_tmp = y[b_temp_re_tmp].im;
        temp_im = y[b_temp_re_tmp].re;
        temp_re = twid_re * temp_im - twid_im * temp_re_tmp;
        temp_im = twid_re * temp_re_tmp + twid_im * temp_im;
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

void FFTImplementationCallback::r2br_r2dit_trig_impl(
    const ::coder::array<creal_T, 1U> &x, int unsigned_nRows,
    const ::coder::array<double, 2U> &costab,
    const ::coder::array<double, 2U> &sintab, ::coder::array<creal_T, 1U> &y)
{
  double temp_im;
  double temp_re;
  double temp_re_tmp;
  double twid_re;
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
  iDelta2 = x.size(0);
  if (iDelta2 > unsigned_nRows) {
    iDelta2 = unsigned_nRows;
  }
  iheight = unsigned_nRows - 2;
  nRowsD2 = unsigned_nRows / 2;
  k = nRowsD2 / 2;
  iy = 0;
  ju = 0;
  for (i = 0; i <= iDelta2 - 2; i++) {
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
  y[iy] = x[iDelta2 - 1];
  if (unsigned_nRows > 1) {
    for (i = 0; i <= iheight; i += 2) {
      temp_re_tmp = y[i + 1].re;
      temp_im = y[i + 1].im;
      temp_re = y[i].re;
      twid_re = y[i].im;
      y[i + 1].re = temp_re - temp_re_tmp;
      y[i + 1].im = twid_re - temp_im;
      y[i].re = temp_re + temp_re_tmp;
      y[i].im = twid_re + temp_im;
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
      int ihi;
      twid_re = costab[j];
      twid_im = sintab[j];
      i = ju;
      ihi = ju + iheight;
      while (i < ihi) {
        b_temp_re_tmp = i + iy;
        temp_re_tmp = y[b_temp_re_tmp].im;
        temp_im = y[b_temp_re_tmp].re;
        temp_re = twid_re * temp_im - twid_im * temp_re_tmp;
        temp_im = twid_re * temp_re_tmp + twid_im * temp_im;
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

void FFTImplementationCallback::dobluesteinfft(
    const ::coder::array<creal32_T, 2U> &x, int n2blue, int nfft,
    const ::coder::array<float, 2U> &costab,
    const ::coder::array<float, 2U> &sintab,
    const ::coder::array<float, 2U> &sintabinv,
    ::coder::array<creal32_T, 2U> &y)
{
  array<creal32_T, 1U> fv;
  array<creal32_T, 1U> fy;
  array<creal32_T, 1U> r;
  array<creal32_T, 1U> wwc;
  float b_temp_re_tmp;
  float temp_im;
  float temp_re;
  float twid_im;
  float twid_re;
  int b_i;
  int b_k;
  int b_y;
  int i;
  int ihi;
  int iy;
  int j;
  int ju;
  int minNrowsNx;
  int nInt2;
  int nInt2m1;
  int nRowsD2;
  int rt;
  int temp_re_tmp;
  int xoff;
  boolean_T tst;
  nInt2m1 = (nfft + nfft) - 1;
  wwc.set_size(nInt2m1);
  rt = 0;
  wwc[nfft - 1].re = 1.0F;
  wwc[nfft - 1].im = 0.0F;
  nInt2 = nfft << 1;
  for (int k{0}; k <= nfft - 2; k++) {
    float nt_im;
    float nt_re;
    b_y = ((k + 1) << 1) - 1;
    if (nInt2 - rt <= b_y) {
      rt += b_y - nInt2;
    } else {
      rt += b_y;
    }
    nt_im = -3.14159274F * static_cast<float>(rt) / static_cast<float>(nfft);
    if (nt_im == 0.0F) {
      nt_re = 1.0F;
      nt_im = 0.0F;
    } else {
      nt_re = std::cos(nt_im);
      nt_im = std::sin(nt_im);
    }
    i = (nfft - k) - 2;
    wwc[i].re = nt_re;
    wwc[i].im = -nt_im;
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
  b_y = x.size(1) - 1;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    fv, fy, r, xoff, ju, minNrowsNx, b_k, temp_re_tmp, temp_re, temp_im, iy,   \
    j, nRowsD2, b_i, tst, b_temp_re_tmp, twid_im, twid_re, ihi)

  for (int chan = 0; chan <= b_y; chan++) {
    xoff = chan * nInt2m1;
    r.set_size(nfft);
    if (nfft > x.size(0)) {
      r.set_size(nfft);
      for (ju = 0; ju < nfft; ju++) {
        r[ju].re = 0.0F;
        r[ju].im = 0.0F;
      }
    }
    minNrowsNx = x.size(0);
    if (nfft <= minNrowsNx) {
      minNrowsNx = nfft;
    }
    for (b_k = 0; b_k < minNrowsNx; b_k++) {
      temp_re_tmp = (nfft + b_k) - 1;
      temp_re = wwc[temp_re_tmp].re;
      temp_im = wwc[temp_re_tmp].im;
      ju = xoff + b_k;
      r[b_k].re = temp_re * x[ju].re + temp_im * x[ju].im;
      r[b_k].im = temp_re * x[ju].im - temp_im * x[ju].re;
    }
    ju = minNrowsNx + 1;
    for (b_k = ju; b_k <= nfft; b_k++) {
      r[b_k - 1].re = 0.0F;
      r[b_k - 1].im = 0.0F;
    }
    fy.set_size(n2blue);
    if (n2blue > r.size(0)) {
      fy.set_size(n2blue);
      for (ju = 0; ju < n2blue; ju++) {
        fy[ju].re = 0.0F;
        fy[ju].im = 0.0F;
      }
    }
    iy = r.size(0);
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
    fy[iy] = r[j - 1];
    if (n2blue > 1) {
      for (b_i = 0; b_i <= minNrowsNx; b_i += 2) {
        b_temp_re_tmp = fy[b_i + 1].re;
        temp_im = fy[b_i + 1].im;
        twid_im = fy[b_i].re;
        temp_re = fy[b_i].im;
        fy[b_i + 1].re = twid_im - b_temp_re_tmp;
        fy[b_i + 1].im = temp_re - temp_im;
        fy[b_i].re = twid_im + b_temp_re_tmp;
        fy[b_i].im = temp_re + temp_im;
      }
    }
    xoff = 2;
    minNrowsNx = 4;
    iy = ((b_k - 1) << 2) + 1;
    while (b_k > 0) {
      for (b_i = 0; b_i < iy; b_i += minNrowsNx) {
        temp_re_tmp = b_i + xoff;
        temp_re = fy[temp_re_tmp].re;
        temp_im = fy[temp_re_tmp].im;
        fy[temp_re_tmp].re = fy[b_i].re - temp_re;
        fy[temp_re_tmp].im = fy[b_i].im - temp_im;
        fy[b_i].re = fy[b_i].re + temp_re;
        fy[b_i].im = fy[b_i].im + temp_im;
      }
      ju = 1;
      for (j = b_k; j < nRowsD2; j += b_k) {
        twid_re = costab[j];
        twid_im = sintab[j];
        b_i = ju;
        ihi = ju + iy;
        while (b_i < ihi) {
          temp_re_tmp = b_i + xoff;
          b_temp_re_tmp = fy[temp_re_tmp].im;
          temp_im = fy[temp_re_tmp].re;
          temp_re = twid_re * temp_im - twid_im * b_temp_re_tmp;
          temp_im = twid_re * b_temp_re_tmp + twid_im * temp_im;
          fy[temp_re_tmp].re = fy[b_i].re - temp_re;
          fy[temp_re_tmp].im = fy[b_i].im - temp_im;
          fy[b_i].re = fy[b_i].re + temp_re;
          fy[b_i].im = fy[b_i].im + temp_im;
          b_i += minNrowsNx;
        }
        ju++;
      }
      b_k /= 2;
      xoff = minNrowsNx;
      minNrowsNx += minNrowsNx;
      iy -= xoff;
    }
    FFTImplementationCallback::r2br_r2dit_trig_impl(wwc, n2blue, costab, sintab,
                                                    fv);
    iy = fy.size(0);
    for (ju = 0; ju < iy; ju++) {
      twid_im = fy[ju].re;
      temp_im = fv[ju].im;
      temp_re = fy[ju].im;
      twid_re = fv[ju].re;
      fy[ju].re = twid_im * twid_re - temp_re * temp_im;
      fy[ju].im = twid_im * temp_im + temp_re * twid_re;
    }
    FFTImplementationCallback::r2br_r2dit_trig_impl(fy, n2blue, costab,
                                                    sintabinv, fv);
    if (fv.size(0) > 1) {
      temp_im = 1.0F / static_cast<float>(fv.size(0));
      iy = fv.size(0);
      for (ju = 0; ju < iy; ju++) {
        fv[ju].re = temp_im * fv[ju].re;
        fv[ju].im = temp_im * fv[ju].im;
      }
    }
    ju = static_cast<int>(static_cast<float>(nfft));
    iy = wwc.size(0);
    for (b_k = ju; b_k <= iy; b_k++) {
      temp_im = wwc[b_k - 1].re;
      temp_re = fv[b_k - 1].im;
      twid_re = wwc[b_k - 1].im;
      twid_im = fv[b_k - 1].re;
      xoff = b_k - static_cast<int>(static_cast<float>(nfft));
      r[xoff].re = temp_im * twid_im + twid_re * temp_re;
      r[xoff].im = temp_im * temp_re - twid_re * twid_im;
    }
    iy = r.size(0);
    for (ju = 0; ju < iy; ju++) {
      y[ju + y.size(0) * chan] = r[ju];
    }
  }
}

void FFTImplementationCallback::dobluesteinfft(
    const ::coder::array<creal_T, 2U> &x, int n2blue, int nfft,
    const ::coder::array<double, 2U> &costab,
    const ::coder::array<double, 2U> &sintab,
    const ::coder::array<double, 2U> &sintabinv, ::coder::array<creal_T, 2U> &y)
{
  array<creal_T, 1U> b_fv;
  array<creal_T, 1U> fv;
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
  wwc.set_size(nInt2m1);
  rt = 0;
  wwc[nfft - 1].re = 1.0;
  wwc[nfft - 1].im = 0.0;
  nInt2 = nfft << 1;
  for (int k{0}; k <= nfft - 2; k++) {
    b_y = ((k + 1) << 1) - 1;
    if (nInt2 - rt <= b_y) {
      rt += b_y - nInt2;
    } else {
      rt += b_y;
    }
    nt_im = -3.1415926535897931 * static_cast<double>(rt) /
            static_cast<double>(nfft);
    if (nt_im == 0.0) {
      nt_re = 1.0;
      nt_im = 0.0;
    } else {
      nt_re = std::cos(nt_im);
      nt_im = std::sin(nt_im);
    }
    i = (nfft - k) - 2;
    wwc[i].re = nt_re;
    wwc[i].im = -nt_im;
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
  nInt2m1 = x.size(0);
  if (nfft <= nInt2m1) {
    nInt2m1 = nfft;
  }
  i = nInt2m1 + 1;
  rt = wwc.size(0);
  r.set_size(nfft);
  if (nfft > x.size(0)) {
    r.set_size(nfft);
    for (b_y = 0; b_y < nfft; b_y++) {
      r[b_y].re = 0.0;
      r[b_y].im = 0.0;
    }
  }
  for (int k{0}; k < nInt2m1; k++) {
    b_y = (nfft + k) - 1;
    nt_re = wwc[b_y].re;
    nt_im = wwc[b_y].im;
    re_tmp = x[k].im;
    b_re_tmp = x[k].re;
    r[k].re = nt_re * b_re_tmp + nt_im * re_tmp;
    r[k].im = nt_re * re_tmp - nt_im * b_re_tmp;
  }
  for (int k{i}; k <= nfft; k++) {
    r[k - 1].re = 0.0;
    r[k - 1].im = 0.0;
  }
  FFTImplementationCallback::r2br_r2dit_trig_impl(r, n2blue, costab, sintab,
                                                  fv);
  FFTImplementationCallback::r2br_r2dit_trig_impl(wwc, n2blue, costab, sintab,
                                                  b_fv);
  b_fv.set_size(fv.size(0));
  b_y = fv.size(0);
  for (i = 0; i < b_y; i++) {
    nt_re = fv[i].re;
    nt_im = b_fv[i].im;
    re_tmp = fv[i].im;
    b_re_tmp = b_fv[i].re;
    b_fv[i].re = nt_re * b_re_tmp - re_tmp * nt_im;
    b_fv[i].im = nt_re * nt_im + re_tmp * b_re_tmp;
  }
  FFTImplementationCallback::r2br_r2dit_trig_impl(b_fv, n2blue, costab,
                                                  sintabinv, fv);
  if (fv.size(0) > 1) {
    nt_re = 1.0 / static_cast<double>(fv.size(0));
    b_y = fv.size(0);
    for (i = 0; i < b_y; i++) {
      fv[i].re = nt_re * fv[i].re;
      fv[i].im = nt_re * fv[i].im;
    }
  }
  for (int k{nfft}; k <= rt; k++) {
    re_tmp = wwc[k - 1].re;
    b_re_tmp = fv[k - 1].im;
    nt_re = wwc[k - 1].im;
    nt_im = fv[k - 1].re;
    i = k - nfft;
    r[i].re = re_tmp * nt_im + nt_re * b_re_tmp;
    r[i].im = re_tmp * b_re_tmp - nt_re * nt_im;
  }
  b_y = r.size(0);
  for (i = 0; i < b_y; i++) {
    y[i] = r[i];
  }
}

void FFTImplementationCallback::dobluesteinfft(
    const ::coder::array<creal_T, 3U> &x, int n2blue, int nfft,
    const ::coder::array<double, 2U> &costab,
    const ::coder::array<double, 2U> &sintab,
    const ::coder::array<double, 2U> &sintabinv, ::coder::array<creal_T, 3U> &y)
{
  array<creal_T, 1U> b_fv;
  array<creal_T, 1U> fv;
  array<creal_T, 1U> r;
  array<creal_T, 1U> wwc;
  double a_im;
  double a_re;
  double b_re_tmp;
  double re_tmp;
  int b_k;
  int b_y;
  int i;
  int i1;
  int minNrowsNx;
  int nInt2;
  int nInt2m1;
  int rt;
  int u0;
  int xoff;
  nInt2m1 = (nfft + nfft) - 1;
  wwc.set_size(nInt2m1);
  rt = 0;
  wwc[nfft - 1].re = 1.0;
  wwc[nfft - 1].im = 0.0;
  nInt2 = nfft << 1;
  for (int k{0}; k <= nfft - 2; k++) {
    double nt_im;
    double nt_re;
    b_y = ((k + 1) << 1) - 1;
    if (nInt2 - rt <= b_y) {
      rt += b_y - nInt2;
    } else {
      rt += b_y;
    }
    nt_im = -3.1415926535897931 * static_cast<double>(rt) /
            static_cast<double>(nfft);
    if (nt_im == 0.0) {
      nt_re = 1.0;
      nt_im = 0.0;
    } else {
      nt_re = std::cos(nt_im);
      nt_im = std::sin(nt_im);
    }
    i = (nfft - k) - 2;
    wwc[i].re = nt_re;
    wwc[i].im = -nt_im;
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
  b_y = x.size(1) * x.size(2) - 1;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    fv, b_fv, r, xoff, i1, minNrowsNx, b_k, u0, a_re, a_im, re_tmp, b_re_tmp)

  for (int chan = 0; chan <= b_y; chan++) {
    xoff = chan * nInt2m1;
    r.set_size(nfft);
    if (nfft > x.size(0)) {
      r.set_size(nfft);
      for (i1 = 0; i1 < nfft; i1++) {
        r[i1].re = 0.0;
        r[i1].im = 0.0;
      }
    }
    minNrowsNx = x.size(0);
    if (nfft <= minNrowsNx) {
      minNrowsNx = nfft;
    }
    for (b_k = 0; b_k < minNrowsNx; b_k++) {
      u0 = (nfft + b_k) - 1;
      a_re = wwc[u0].re;
      a_im = wwc[u0].im;
      i1 = xoff + b_k;
      r[b_k].re = a_re * x[i1].re + a_im * x[i1].im;
      r[b_k].im = a_re * x[i1].im - a_im * x[i1].re;
    }
    i1 = minNrowsNx + 1;
    for (b_k = i1; b_k <= nfft; b_k++) {
      r[b_k - 1].re = 0.0;
      r[b_k - 1].im = 0.0;
    }
    FFTImplementationCallback::r2br_r2dit_trig_impl(r, n2blue, costab, sintab,
                                                    b_fv);
    FFTImplementationCallback::r2br_r2dit_trig_impl(wwc, n2blue, costab, sintab,
                                                    fv);
    fv.set_size(b_fv.size(0));
    u0 = b_fv.size(0);
    for (i1 = 0; i1 < u0; i1++) {
      a_re = b_fv[i1].re;
      a_im = fv[i1].im;
      re_tmp = b_fv[i1].im;
      b_re_tmp = fv[i1].re;
      fv[i1].re = a_re * b_re_tmp - re_tmp * a_im;
      fv[i1].im = a_re * a_im + re_tmp * b_re_tmp;
    }
    FFTImplementationCallback::r2br_r2dit_trig_impl(fv, n2blue, costab,
                                                    sintabinv, b_fv);
    if (b_fv.size(0) > 1) {
      a_re = 1.0 / static_cast<double>(b_fv.size(0));
      u0 = b_fv.size(0);
      for (i1 = 0; i1 < u0; i1++) {
        b_fv[i1].re = a_re * b_fv[i1].re;
        b_fv[i1].im = a_re * b_fv[i1].im;
      }
    }
    i1 = wwc.size(0);
    for (b_k = nfft; b_k <= i1; b_k++) {
      a_re = wwc[b_k - 1].re;
      a_im = b_fv[b_k - 1].im;
      re_tmp = wwc[b_k - 1].im;
      b_re_tmp = b_fv[b_k - 1].re;
      u0 = b_k - nfft;
      r[u0].re = a_re * b_re_tmp + re_tmp * a_im;
      r[u0].im = a_re * a_im - re_tmp * b_re_tmp;
    }
    xoff = y.size(0);
    u0 = r.size(0);
    for (i1 = 0; i1 < u0; i1++) {
      y[i1 + xoff * chan] = r[i1];
    }
  }
}

void FFTImplementationCallback::generate_twiddle_tables(
    int nRows, boolean_T useRadix2, ::coder::array<double, 2U> &costab,
    ::coder::array<double, 2U> &sintab, ::coder::array<double, 2U> &sintabinv)
{
  array<double, 2U> costab1q;
  double e;
  int i;
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
  i = nd2 + 2;
  nd2 = n - 1;
  for (int k{i}; k <= nd2; k++) {
    costab1q[k] = std::sin(e * static_cast<double>(n - k));
  }
  costab1q[n] = 0.0;
  if (!useRadix2) {
    n = costab1q.size(1) - 1;
    nd2 = (costab1q.size(1) - 1) << 1;
    costab.set_size(1, nd2 + 1);
    sintab.set_size(1, nd2 + 1);
    costab[0] = 1.0;
    sintab[0] = 0.0;
    sintabinv.set_size(1, nd2 + 1);
    for (int k{0}; k < n; k++) {
      sintabinv[k + 1] = costab1q[(n - k) - 1];
    }
    i = costab1q.size(1);
    for (int k{i}; k <= nd2; k++) {
      sintabinv[k] = costab1q[k - n];
    }
    for (int k{0}; k < n; k++) {
      costab[k + 1] = costab1q[k + 1];
      sintab[k + 1] = -costab1q[(n - k) - 1];
    }
    i = costab1q.size(1);
    for (int k{i}; k <= nd2; k++) {
      costab[k] = -costab1q[nd2 - k];
      sintab[k] = -costab1q[k - n];
    }
  } else {
    n = costab1q.size(1) - 1;
    nd2 = (costab1q.size(1) - 1) << 1;
    costab.set_size(1, nd2 + 1);
    sintab.set_size(1, nd2 + 1);
    costab[0] = 1.0;
    sintab[0] = 0.0;
    for (int k{0}; k < n; k++) {
      costab[k + 1] = costab1q[k + 1];
      sintab[k + 1] = -costab1q[(n - k) - 1];
    }
    i = costab1q.size(1);
    for (int k{i}; k <= nd2; k++) {
      costab[k] = -costab1q[nd2 - k];
      sintab[k] = -costab1q[k - n];
    }
    sintabinv.set_size(1, 0);
  }
}

void FFTImplementationCallback::get_algo_sizes(int nfft, boolean_T useRadix2,
                                               int *n2blue, int *nRows)
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
        boolean_T exitg1;
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

void FFTImplementationCallback::r2br_r2dit_trig(
    const ::coder::array<creal32_T, 2U> &x, int n1_unsigned,
    const ::coder::array<float, 2U> &costab,
    const ::coder::array<float, 2U> &sintab, ::coder::array<creal32_T, 2U> &y)
{
  array<creal32_T, 1U> r;
  float temp_im;
  float temp_re;
  float temp_re_tmp;
  float twid_im;
  float twid_re;
  int b_i;
  int b_temp_re_tmp;
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
  boolean_T tst;
  nrows = x.size(0);
  y.set_size(n1_unsigned, x.size(1));
  if (n1_unsigned > x.size(0)) {
    y.set_size(n1_unsigned, x.size(1));
    loop_ub = n1_unsigned * x.size(1);
    for (int i{0}; i < loop_ub; i++) {
      y[i].re = 0.0F;
      y[i].im = 0.0F;
    }
  }
  loop_ub = x.size(1) - 1;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    r, xoff, iDelta2, iy, j, iheight, nRowsD2, k, ju, b_i, tst, temp_re_tmp,   \
    temp_im, temp_re, twid_re, b_temp_re_tmp, twid_im)

  for (int chan = 0; chan <= loop_ub; chan++) {
    xoff = chan * nrows;
    r.set_size(n1_unsigned);
    if (n1_unsigned > x.size(0)) {
      r.set_size(n1_unsigned);
      for (iDelta2 = 0; iDelta2 < n1_unsigned; iDelta2++) {
        r[iDelta2].re = 0.0F;
        r[iDelta2].im = 0.0F;
      }
    }
    iy = x.size(0);
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
    r[iy] = x[(xoff + j) - 1];
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
        r[b_i].re = r[b_i].re + temp_re;
        r[b_i].im = r[b_i].im + temp_im;
      }
      ju = 1;
      for (j = k; j < nRowsD2; j += k) {
        twid_re = costab[j];
        twid_im = sintab[j];
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
          r[b_i].re = r[b_i].re + temp_re;
          r[b_i].im = r[b_i].im + temp_im;
          b_i += iDelta2;
        }
        ju++;
      }
      k /= 2;
      iy = iDelta2;
      iDelta2 += iDelta2;
      iheight -= iy;
    }
    iy = r.size(0);
    for (iDelta2 = 0; iDelta2 < iy; iDelta2++) {
      y[iDelta2 + y.size(0) * chan] = r[iDelta2];
    }
  }
}

void FFTImplementationCallback::r2br_r2dit_trig(
    const ::coder::array<creal_T, 2U> &x, int n1_unsigned,
    const ::coder::array<double, 2U> &costab,
    const ::coder::array<double, 2U> &sintab, ::coder::array<creal_T, 2U> &y)
{
  array<creal_T, 1U> r;
  double temp_im;
  double temp_re;
  double temp_re_tmp;
  double twid_re;
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
  iheight = x.size(0);
  if (iheight > n1_unsigned) {
    iheight = n1_unsigned;
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
  for (i = 0; i <= iheight - 2; i++) {
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
  r[iy] = x[iheight - 1];
  if (n1_unsigned > 1) {
    for (i = 0; i <= istart; i += 2) {
      temp_re_tmp = r[i + 1].re;
      temp_im = r[i + 1].im;
      temp_re = r[i].re;
      twid_re = r[i].im;
      r[i + 1].re = temp_re - temp_re_tmp;
      r[i + 1].im = twid_re - temp_im;
      r[i].re = temp_re + temp_re_tmp;
      r[i].im = twid_re + temp_im;
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
      int ihi;
      twid_re = costab[j];
      twid_im = sintab[j];
      i = istart;
      ihi = istart + iheight;
      while (i < ihi) {
        b_temp_re_tmp = i + iy;
        temp_re_tmp = r[b_temp_re_tmp].im;
        temp_im = r[b_temp_re_tmp].re;
        temp_re = twid_re * temp_im - twid_im * temp_re_tmp;
        temp_im = twid_re * temp_re_tmp + twid_im * temp_im;
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
  iy = r.size(0);
  for (ju = 0; ju < iy; ju++) {
    y[ju] = r[ju];
  }
}

void FFTImplementationCallback::r2br_r2dit_trig(
    const ::coder::array<creal_T, 3U> &x, int n1_unsigned,
    const ::coder::array<double, 2U> &costab,
    const ::coder::array<double, 2U> &sintab, ::coder::array<creal_T, 3U> &y)
{
  array<creal_T, 1U> r;
  double temp_im;
  double temp_re;
  double temp_re_tmp;
  double twid_im;
  double twid_re;
  int b_i;
  int b_temp_re_tmp;
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
  boolean_T tst;
  nrows = x.size(0);
  y.set_size(n1_unsigned, x.size(1), x.size(2));
  if (n1_unsigned > x.size(0)) {
    y.set_size(n1_unsigned, x.size(1), x.size(2));
    loop_ub = n1_unsigned * x.size(1) * x.size(2);
    for (int i{0}; i < loop_ub; i++) {
      y[i].re = 0.0;
      y[i].im = 0.0;
    }
  }
  loop_ub = x.size(1) * x.size(2) - 1;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    r, xoff, iheight, iy, j, nRowsD2, k, ju, b_i, iDelta2, tst, temp_re_tmp,   \
    temp_im, temp_re, twid_re, b_temp_re_tmp, twid_im)

  for (int chan = 0; chan <= loop_ub; chan++) {
    xoff = chan * nrows;
    r.set_size(n1_unsigned);
    if (n1_unsigned > x.size(0)) {
      r.set_size(n1_unsigned);
      for (iheight = 0; iheight < n1_unsigned; iheight++) {
        r[iheight].re = 0.0;
        r[iheight].im = 0.0;
      }
    }
    iy = x.size(0);
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
    r[iy] = x[(xoff + j) - 1];
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
        r[b_i].re = r[b_i].re + temp_re;
        r[b_i].im = r[b_i].im + temp_im;
      }
      ju = 1;
      for (j = k; j < nRowsD2; j += k) {
        twid_re = costab[j];
        twid_im = sintab[j];
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
          r[b_i].re = r[b_i].re + temp_re;
          r[b_i].im = r[b_i].im + temp_im;
          b_i += iDelta2;
        }
        ju++;
      }
      k /= 2;
      iy = iDelta2;
      iDelta2 += iDelta2;
      iheight -= iy;
    }
    iy = y.size(0);
    iDelta2 = r.size(0);
    for (iheight = 0; iheight < iDelta2; iheight++) {
      y[iheight + iy * chan] = r[iheight];
    }
  }
}

} // namespace internal
} // namespace coder

// End of code generation (FFTImplementationCallback.cpp)
