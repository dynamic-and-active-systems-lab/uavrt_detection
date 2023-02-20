//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: FFTImplementationCallback.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 14:31:55
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
#include <string.h>

// Function Definitions
//
// Arguments    : const ::coder::array<creal32_T, 1U> &x
//                int unsigned_nRows
//                const ::coder::array<float, 2U> &costab
//                const ::coder::array<float, 2U> &sintab
//                ::coder::array<creal32_T, 1U> &y
// Return Type  : void
//
namespace coder {
namespace internal {
namespace fft {
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
  if (iDelta2 - 1 > 2147483646) {
    check_forloop_overflow_error();
  }
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

//
// Arguments    : const ::coder::array<creal32_T, 2U> &x
//                int n2blue
//                int nfft
//                const ::coder::array<float, 2U> &costab
//                const ::coder::array<float, 2U> &sintab
//                const ::coder::array<float, 2U> &sintabinv
//                ::coder::array<creal32_T, 2U> &y
// Return Type  : void
//
void FFTImplementationCallback::dobluesteinfft(
    const ::coder::array<creal32_T, 2U> &x, int n2blue, int nfft,
    const ::coder::array<float, 2U> &costab,
    const ::coder::array<float, 2U> &sintab,
    const ::coder::array<float, 2U> &sintabinv,
    ::coder::array<creal32_T, 2U> &y)
{
  static rtDoubleCheckInfo
      b_emlrtDCI{
          33,                     // lineNo
          28,                     // colNo
          "bluestein_setup_impl", // fName
          "C:\\Program "
          "Files\\MATLAB\\toolbox\\eml\\eml\\+coder\\+internal\\bluesteinSetup."
          "m", // pName
          4    // checkKind
      };
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
  if (nInt2m1 < 0) {
    rtNonNegativeError(static_cast<double>(nInt2m1), &b_emlrtDCI);
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
  if (x.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  b_y = x.size(1) - 1;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    fv, fy, r, xoff, ju, minNrowsNx, b_k, iy, temp_re_tmp, temp_re, temp_im,   \
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
    if (minNrowsNx > 2147483646) {
      check_forloop_overflow_error();
    }
    for (b_k = 0; b_k < minNrowsNx; b_k++) {
      temp_re_tmp = (nfft + b_k) - 1;
      temp_re = wwc[temp_re_tmp].re;
      temp_im = wwc[temp_re_tmp].im;
      ju = xoff + b_k;
      r[b_k].re = temp_re * x[ju].re + temp_im * x[ju].im;
      r[b_k].im = temp_re * x[ju].im - temp_im * x[ju].re;
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
    if (j - 1 > 2147483646) {
      check_forloop_overflow_error();
    }
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
    iy = static_cast<int>(static_cast<float>(nfft));
    xoff = wwc.size(0);
    if ((static_cast<int>(static_cast<float>(nfft)) <= wwc.size(0)) &&
        (wwc.size(0) > 2147483646)) {
      check_forloop_overflow_error();
    }
    for (b_k = iy; b_k <= xoff; b_k++) {
      temp_im = wwc[b_k - 1].re;
      temp_re = fv[b_k - 1].im;
      twid_re = wwc[b_k - 1].im;
      twid_im = fv[b_k - 1].re;
      ju = b_k - static_cast<int>(static_cast<float>(nfft));
      r[ju].re = temp_im * twid_im + twid_re * temp_re;
      r[ju].im = temp_im * temp_re - twid_re * twid_im;
    }
    iy = r.size(0);
    for (ju = 0; ju < iy; ju++) {
      y[ju + y.size(0) * chan] = r[ju];
    }
  }
}

//
// Arguments    : const ::coder::array<creal32_T, 2U> &x
//                int n1_unsigned
//                const ::coder::array<float, 2U> &costab
//                const ::coder::array<float, 2U> &sintab
//                ::coder::array<creal32_T, 2U> &y
// Return Type  : void
//
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
  if (x.size(1) > 2147483646) {
    check_forloop_overflow_error();
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
    if (j - 1 > 2147483646) {
      check_forloop_overflow_error();
    }
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

} // namespace fft
} // namespace internal
} // namespace coder

//
// File trailer for FFTImplementationCallback.cpp
//
// [EOF]
//
