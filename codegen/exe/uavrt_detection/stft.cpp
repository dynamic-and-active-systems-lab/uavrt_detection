//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: stft.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 22-Oct-2022 12:48:10
//

// Include Files
#include "stft.h"
#include "FFTImplementationCallback.h"
#include "computeDFT.h"
#include "psdfreqvec.h"
#include "rt_nonfinite.h"
#include "stickyStruct.h"
#include "uavrt_detection_rtwutil.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const ::coder::array<creal_T, 2U> &x
//                const internal::s_stickyStruct *opts
//                ::coder::array<creal_T, 3U> &S
//                ::coder::array<double, 1U> &F
//                ::coder::array<double, 2U> &T
// Return Type  : void
//
namespace coder {
void computeSTFT(const ::coder::array<creal_T, 2U> &x,
                 const internal::s_stickyStruct *opts,
                 ::coder::array<creal_T, 3U> &S, ::coder::array<double, 1U> &F,
                 ::coder::array<double, 2U> &T)
{
  array<creal_T, 3U> c;
  array<creal_T, 3U> xin;
  array<creal_T, 2U> b_x;
  array<creal_T, 2U> buffer;
  array<creal_T, 2U> wrappedData;
  array<creal_T, 1U> c_x;
  array<double, 2U> costab;
  array<double, 2U> sintab;
  array<double, 2U> sintabinv;
  array<double, 2U> y;
  array<double, 1U> f;
  double hopSize;
  double nCol;
  double nfft_tmp_tmp;
  double xtmp_im;
  int acoef;
  int b_bcoef;
  int b_i;
  int b_i1;
  int b_k;
  int b_remainder;
  int bcoef;
  int c_bcoef;
  int i;
  int i1;
  int i2;
  int i3;
  int loop_ub;
  int npages;
  int offset;
  int remainder_tmp;
  int stride;
  boolean_T useRadix2;
  nfft_tmp_tmp = opts->next.next.next.next.next.value;
  hopSize = opts->next.next.next.next.next.next.next.value -
            opts->next.next.next.next.next.next.value;
  nCol = std::trunc((opts->next.next.next.next.next.next.next.next.next.next
                         .next.next.next.next.next.next.next.value -
                     opts->next.next.next.next.next.next.value) /
                    hopSize);
  i = static_cast<int>(nCol);
  xin.set_size(static_cast<int>(opts->next.next.next.next.next.next.next.value),
               i, x.size(1));
  bcoef = static_cast<int>(opts->next.next.next.next.next.next.next.value) *
          static_cast<int>(nCol) * x.size(1);
  for (i1 = 0; i1 < bcoef; i1++) {
    xin[i1].re = 0.0;
    xin[i1].im = 0.0;
  }
  if (nCol - 1.0 < 0.0) {
    y.set_size(y.size(0), 0);
  } else {
    y.set_size(1, static_cast<int>(nCol - 1.0) + 1);
    bcoef = static_cast<int>(nCol - 1.0);
    for (i1 = 0; i1 <= bcoef; i1++) {
      y[i1] = i1;
    }
  }
  if (static_cast<int>(nCol) - 1 >= 0) {
    b_bcoef = x.size(1);
  }
  for (acoef = 0; acoef < i; acoef++) {
    xtmp_im = hopSize * ((static_cast<double>(acoef) + 1.0) - 1.0);
    nCol = opts->next.next.next.next.next.next.next.value + xtmp_im;
    if (xtmp_im + 1.0 > nCol) {
      i1 = 0;
      b_i = 0;
    } else {
      i1 = static_cast<int>(xtmp_im + 1.0) - 1;
      b_i = static_cast<int>(nCol);
    }
    bcoef = b_i - i1;
    b_x.set_size(bcoef, x.size(1));
    for (b_i = 0; b_i < b_bcoef; b_i++) {
      for (npages = 0; npages < bcoef; npages++) {
        b_x[npages + b_x.size(0) * b_i] = x[(i1 + npages) + x.size(0) * b_i];
      }
    }
    offset = xin.size(0);
    bcoef = xin.size(2);
    for (i1 = 0; i1 < bcoef; i1++) {
      for (b_i = 0; b_i < offset; b_i++) {
        xin[(b_i + xin.size(0) * acoef) + xin.size(0) * xin.size(1) * i1] =
            b_x[b_i + offset * i1];
      }
    }
  }
  y.set_size(1, y.size(1));
  xtmp_im = opts->next.next.next.next.next.next.next.value / 2.0;
  bcoef = y.size(1) - 1;
  for (i = 0; i <= bcoef; i++) {
    y[i] = (y[i] * hopSize + xtmp_im) /
           opts->next.next.next.next.next.next.next.next.next.next.value;
  }
  offset = xin.size(0);
  c_bcoef = opts->next.next.next.next.next.next.next.next.value.size(0);
  if (offset <= c_bcoef) {
    c_bcoef = offset;
  }
  if (xin.size(0) == 1) {
    c_bcoef = opts->next.next.next.next.next.next.next.next.value.size(0);
  } else if (opts->next.next.next.next.next.next.next.next.value.size(0) == 1) {
    c_bcoef = xin.size(0);
  } else if (opts->next.next.next.next.next.next.next.next.value.size(0) ==
             xin.size(0)) {
    c_bcoef = opts->next.next.next.next.next.next.next.next.value.size(0);
  }
  c.set_size(c_bcoef, xin.size(1), xin.size(2));
  offset = xin.size(0);
  c_bcoef = opts->next.next.next.next.next.next.next.next.value.size(0);
  if (offset <= c_bcoef) {
    c_bcoef = offset;
  }
  if (xin.size(0) == 1) {
    c_bcoef = opts->next.next.next.next.next.next.next.next.value.size(0);
  } else if (opts->next.next.next.next.next.next.next.next.value.size(0) == 1) {
    c_bcoef = xin.size(0);
  } else if (opts->next.next.next.next.next.next.next.next.value.size(0) ==
             xin.size(0)) {
    c_bcoef = opts->next.next.next.next.next.next.next.next.value.size(0);
  }
  if ((c_bcoef != 0) && (xin.size(1) != 0)) {
    b_bcoef = (xin.size(2) != 1);
    i = xin.size(2) - 1;
    bcoef = (xin.size(1) != 1);
    acoef = (opts->next.next.next.next.next.next.next.next.value.size(0) != 1);
    c_bcoef = (xin.size(0) != 1);
    for (int k{0}; k <= i; k++) {
      offset = b_bcoef * k;
      i1 = c.size(1) - 1;
      for (b_k = 0; b_k <= i1; b_k++) {
        stride = bcoef * b_k;
        b_i = c.size(0) - 1;
        for (b_i1 = 0; b_i1 <= b_i; b_i1++) {
          npages = c_bcoef * b_i1;
          xtmp_im =
              opts->next.next.next.next.next.next.next.next.value[acoef * b_i1];
          c[(b_i1 + c.size(0) * b_k) + c.size(0) * c.size(1) * k].re =
              xtmp_im * xin[(npages + xin.size(0) * stride) +
                            xin.size(0) * xin.size(1) * offset]
                            .re;
          c[(b_i1 + c.size(0) * b_k) + c.size(0) * c.size(1) * k].im =
              xtmp_im * xin[(npages + xin.size(0) * stride) +
                            xin.size(0) * xin.size(1) * offset]
                            .im;
        }
      }
    }
  }
  b_bcoef = static_cast<int>(nfft_tmp_tmp);
  xin.set_size(b_bcoef, c.size(1), c.size(2));
  bcoef = static_cast<int>(nfft_tmp_tmp) * c.size(1) * c.size(2);
  for (i = 0; i < bcoef; i++) {
    xin[i].re = 0.0;
    xin[i].im = 0.0;
  }
  if (c.size(0) > opts->next.next.next.next.next.value) {
    i = c.size(1) * c.size(2);
    if (i - 1 >= 0) {
      loop_ub = c.size(0);
      if (static_cast<unsigned int>(static_cast<int>(nfft_tmp_tmp)) == 0U) {
        i2 = MAX_int32_T;
      } else {
        i2 = static_cast<int>(
            static_cast<unsigned int>(c.size(0)) /
            static_cast<unsigned int>(static_cast<int>(nfft_tmp_tmp)));
      }
      remainder_tmp = i2 * static_cast<int>(nfft_tmp_tmp);
      b_remainder = (c.size(0) - remainder_tmp) - 1;
      i3 = b_remainder + 2;
    }
    for (int j{0}; j < i; j++) {
      c_bcoef = c.size(0);
      c_x.set_size(c.size(0));
      for (i1 = 0; i1 < loop_ub; i1++) {
        c_x[i1] = c[i1 + c_bcoef * j];
      }
      if (c.size(0) == 1) {
        wrappedData.set_size(1, b_bcoef);
        for (i1 = 0; i1 < b_bcoef; i1++) {
          wrappedData[i1].re = 0.0;
          wrappedData[i1].im = 0.0;
        }
      } else {
        wrappedData.set_size(b_bcoef, 1);
        for (i1 = 0; i1 < b_bcoef; i1++) {
          wrappedData[i1].re = 0.0;
          wrappedData[i1].im = 0.0;
        }
      }
      for (int k{0}; k <= b_remainder; k++) {
        wrappedData[k] = c_x[remainder_tmp + k];
      }
      for (int k{i3}; k <= b_bcoef; k++) {
        wrappedData[k - 1].re = 0.0;
        wrappedData[k - 1].im = 0.0;
      }
      for (bcoef = 0; bcoef < i2; bcoef++) {
        offset = bcoef * static_cast<int>(nfft_tmp_tmp);
        for (int k{0}; k < b_bcoef; k++) {
          i1 = offset + k;
          wrappedData[k].re = wrappedData[k].re + c_x[i1].re;
          wrappedData[k].im = wrappedData[k].im + c_x[i1].im;
        }
      }
      offset = wrappedData.size(0) * wrappedData.size(1);
      c_bcoef = xin.size(0);
      for (i1 = 0; i1 < offset; i1++) {
        xin[i1 + c_bcoef * j] = wrappedData[i1];
      }
    }
  } else {
    xin.set_size(c.size(0), c.size(1), c.size(2));
    bcoef = c.size(0) * c.size(1) * c.size(2);
    for (i = 0; i < bcoef; i++) {
      xin[i] = c[i];
    }
  }
  if ((xin.size(0) == 0) || (xin.size(1) == 0) ||
      (static_cast<int>(nfft_tmp_tmp) == 0)) {
    S.set_size(b_bcoef, xin.size(1), xin.size(2));
    bcoef = static_cast<int>(nfft_tmp_tmp) * xin.size(1) * xin.size(2);
    for (i = 0; i < bcoef; i++) {
      S[i].re = 0.0;
      S[i].im = 0.0;
    }
  } else {
    useRadix2 = ((static_cast<int>(nfft_tmp_tmp) > 0) &&
                 ((static_cast<int>(nfft_tmp_tmp) &
                   (static_cast<int>(nfft_tmp_tmp) - 1)) == 0));
    internal::FFTImplementationCallback::get_algo_sizes(
        static_cast<int>(opts->next.next.next.next.next.value), useRadix2,
        &offset, &c_bcoef);
    internal::FFTImplementationCallback::generate_twiddle_tables(
        c_bcoef, useRadix2, costab, sintab, sintabinv);
    if (useRadix2) {
      internal::FFTImplementationCallback::r2br_r2dit_trig(
          xin, static_cast<int>(opts->next.next.next.next.next.value), costab,
          sintab, S);
    } else {
      internal::FFTImplementationCallback::dobluesteinfft(
          xin, offset, static_cast<int>(opts->next.next.next.next.next.value),
          costab, sintab, sintabinv, S);
    }
  }
  psdfreqvec(nfft_tmp_tmp,
             opts->next.next.next.next.next.next.next.next.next.next.value, f);
  if (S.size(0) == 0) {
    nfft_tmp_tmp = 0.0;
  } else {
    nfft_tmp_tmp = std::fmod(static_cast<double>(S.size(0)), 2.0);
  }
  if (nfft_tmp_tmp == 0.0) {
    nCol = static_cast<double>(S.size(0)) / 2.0 - 1.0;
    c_bcoef = 1;
    if (S.size(0) != 1) {
      c_bcoef = 0;
    } else if ((S.size(1) == 1) && (S.size(2) != 1)) {
      c_bcoef = 2;
    }
    if ((S.size(0) != 0) && (S.size(1) != 0) &&
        ((S.size(0) != 1) || (S.size(1) != 1) || (S.size(2) != 1))) {
      if (nCol < 0.0) {
        b_k = -static_cast<int>(nCol);
        useRadix2 = false;
      } else {
        b_k = static_cast<int>(nCol);
        useRadix2 = true;
      }
      if (S.size(c_bcoef) <= 1) {
        b_k = 0;
      } else {
        if (b_k > S.size(c_bcoef)) {
          unsigned int u;
          u = static_cast<unsigned int>(S.size(c_bcoef));
          if (u == 0U) {
            i = MAX_int32_T;
          } else {
            i = static_cast<int>(static_cast<unsigned int>(b_k) / u);
          }
          b_k -= S.size(c_bcoef) * i;
        }
        if (b_k > (S.size(c_bcoef) >> 1)) {
          b_k = S.size(c_bcoef) - b_k;
          useRadix2 = !useRadix2;
        }
      }
      offset = S.size(0);
      if (S.size(1) > S.size(0)) {
        offset = S.size(1);
      }
      if (S.size(2) > offset) {
        offset = S.size(2);
      }
      offset /= 2;
      buffer.set_size(1, offset);
      for (i = 0; i < offset; i++) {
        buffer[i].re = 0.0;
        buffer[i].im = 0.0;
      }
      i = S.size(c_bcoef);
      acoef = S.size(c_bcoef);
      stride = 1;
      for (int k{0}; k < c_bcoef; k++) {
        stride *= S.size(k);
      }
      npages = 1;
      offset = c_bcoef + 2;
      for (int k{offset}; k < 4; k++) {
        npages *= S.size(k - 1);
      }
      bcoef = stride * S.size(c_bcoef);
      if ((S.size(c_bcoef) > 1) && (b_k > 0)) {
        for (b_i = 0; b_i < npages; b_i++) {
          b_bcoef = b_i * bcoef;
          for (int j{0}; j < stride; j++) {
            b_i1 = b_bcoef + j;
            if (useRadix2) {
              for (int k{0}; k < b_k; k++) {
                buffer[k] = S[b_i1 + ((k + i) - b_k) * stride];
              }
              i1 = b_k + 1;
              for (int k{acoef}; k >= i1; k--) {
                S[b_i1 + (k - 1) * stride] = S[b_i1 + ((k - b_k) - 1) * stride];
              }
              for (int k{0}; k < b_k; k++) {
                S[b_i1 + k * stride] = buffer[k];
              }
            } else {
              for (int k{0}; k < b_k; k++) {
                buffer[k] = S[b_i1 + k * stride];
              }
              i1 = (i - b_k) - 1;
              for (int k{0}; k <= i1; k++) {
                S[b_i1 + k * stride] = S[b_i1 + (k + b_k) * stride];
              }
              for (int k{0}; k < b_k; k++) {
                S[b_i1 + ((k + i) - b_k) * stride] = buffer[k];
              }
            }
          }
        }
      }
    }
  } else if (S.size(0) > 1) {
    offset = static_cast<int>(static_cast<unsigned int>(S.size(0)) >> 1) - 1;
    npages = S.size(1) * S.size(2) - 1;
    b_bcoef = S.size(0);
    if ((offset + 1) << 1 == S.size(0)) {
      bcoef = 1;
      for (b_i = 0; b_i <= npages; b_i++) {
        b_i1 = bcoef;
        bcoef += b_bcoef;
        acoef = b_i1 + offset;
        for (int k{0}; k <= offset; k++) {
          c_bcoef = (b_i1 + k) - 1;
          nCol = S[c_bcoef].re;
          xtmp_im = S[c_bcoef].im;
          i = acoef + k;
          S[c_bcoef] = S[i];
          S[i].re = nCol;
          S[i].im = xtmp_im;
        }
      }
    } else {
      bcoef = 1;
      for (b_i = 0; b_i <= npages; b_i++) {
        b_i1 = bcoef;
        bcoef += b_bcoef;
        acoef = b_i1 + offset;
        nCol = S[acoef].re;
        xtmp_im = S[acoef].im;
        for (int k{0}; k <= offset; k++) {
          i = acoef + k;
          i1 = (b_i1 + k) - 1;
          S[i] = S[i1];
          S[i1] = S[i + 1];
        }
        acoef = (acoef + offset) + 1;
        S[acoef].re = nCol;
        S[acoef].im = xtmp_im;
      }
    }
  }
  if (f.size(0) == 0) {
    nfft_tmp_tmp = 0.0;
  } else {
    nfft_tmp_tmp = std::fmod(static_cast<double>(f.size(0)), 2.0);
  }
  if (nfft_tmp_tmp == 0.0) {
    nCol = f[static_cast<int>(static_cast<double>(f.size(0)) / 2.0) - 1];
    bcoef = f.size(0);
    for (i = 0; i < bcoef; i++) {
      f[i] = f[i] - nCol;
    }
  } else {
    nCol =
        f[static_cast<int>((static_cast<double>(f.size(0)) + 1.0) / 2.0) - 1];
    bcoef = f.size(0);
    for (i = 0; i < bcoef; i++) {
      f[i] = f[i] - nCol;
    }
  }
  if (S.size(0) < 1) {
    bcoef = 0;
  } else {
    bcoef = S.size(0);
  }
  F.set_size(bcoef);
  for (i = 0; i < bcoef; i++) {
    F[i] = f[i];
  }
  if (S.size(1) < 1) {
    bcoef = 0;
  } else {
    bcoef = S.size(1);
  }
  T.set_size(1, bcoef);
  for (i = 0; i < bcoef; i++) {
    T[i] = y[i];
  }
}

//
// Arguments    : const ::coder::array<creal32_T, 2U> &x
//                double varargin_1
//                const ::coder::array<double, 1U> &varargin_3
//                double varargin_5
//                double varargin_7
//                ::coder::array<creal32_T, 2U> &varargout_1
//                ::coder::array<float, 1U> &varargout_2
//                ::coder::array<float, 1U> &varargout_3
// Return Type  : void
//
void stft(const ::coder::array<creal32_T, 2U> &x, double varargin_1,
          const ::coder::array<double, 1U> &varargin_3, double varargin_5,
          double varargin_7, ::coder::array<creal32_T, 2U> &varargout_1,
          ::coder::array<float, 1U> &varargout_2,
          ::coder::array<float, 1U> &varargout_3)
{
  internal::j_stickyStruct obj;
  array<creal32_T, 2U> buffer;
  array<creal32_T, 2U> c;
  array<creal32_T, 2U> xin;
  array<double, 2U> y;
  array<double, 1U> f;
  array<float, 2U> tempT;
  double d;
  double hopSize;
  double nCol;
  float xtmp_re;
  int acoef;
  int b_bcoef;
  int b_i1;
  int bcoef;
  int i;
  int i1;
  int i2;
  int ib;
  obj.value.set_size(varargin_3.size(0));
  acoef = varargin_3.size(0);
  for (i = 0; i < acoef; i++) {
    obj.value[i] = static_cast<float>(varargin_3[i]);
  }
  hopSize = static_cast<double>(varargin_3.size(0)) - varargin_5;
  nCol = std::trunc((static_cast<double>(x.size(1)) - varargin_5) / hopSize);
  i = static_cast<int>(nCol);
  xin.set_size(varargin_3.size(0), i);
  acoef = varargin_3.size(0) * static_cast<int>(nCol);
  for (i1 = 0; i1 < acoef; i1++) {
    xin[i1].re = 0.0F;
    xin[i1].im = 0.0F;
  }
  if (nCol - 1.0 < 0.0) {
    y.set_size(y.size(0), 0);
  } else {
    y.set_size(1, static_cast<int>(nCol - 1.0) + 1);
    acoef = static_cast<int>(nCol - 1.0);
    for (i1 = 0; i1 <= acoef; i1++) {
      y[i1] = i1;
    }
  }
  for (bcoef = 0; bcoef < i; bcoef++) {
    nCol = hopSize * ((static_cast<double>(bcoef) + 1.0) - 1.0);
    d = static_cast<double>(varargin_3.size(0)) + nCol;
    if (nCol + 1.0 > d) {
      i1 = 0;
      b_i1 = 0;
    } else {
      i1 = static_cast<int>(nCol + 1.0) - 1;
      b_i1 = static_cast<int>(d);
    }
    acoef = b_i1 - i1;
    for (b_i1 = 0; b_i1 < acoef; b_i1++) {
      xin[b_i1 + xin.size(0) * bcoef] = x[i1 + b_i1];
    }
  }
  y.set_size(1, y.size(1));
  nCol = static_cast<double>(varargin_3.size(0)) / 2.0;
  acoef = y.size(1) - 1;
  for (i = 0; i <= acoef; i++) {
    y[i] = (y[i] * hopSize + nCol) / varargin_1;
  }
  bcoef = xin.size(0);
  acoef = obj.value.size(0);
  if (bcoef <= acoef) {
    acoef = bcoef;
  }
  if (xin.size(0) == 1) {
    acoef = obj.value.size(0);
  } else if (obj.value.size(0) == 1) {
    acoef = xin.size(0);
  } else if (obj.value.size(0) == xin.size(0)) {
    acoef = obj.value.size(0);
  }
  c.set_size(acoef, xin.size(1));
  bcoef = xin.size(0);
  acoef = obj.value.size(0);
  if (bcoef <= acoef) {
    acoef = bcoef;
  }
  if (xin.size(0) == 1) {
    acoef = obj.value.size(0);
  } else if (obj.value.size(0) == 1) {
    acoef = xin.size(0);
  } else if (obj.value.size(0) == xin.size(0)) {
    acoef = obj.value.size(0);
  }
  if ((acoef != 0) && (xin.size(1) != 0)) {
    bcoef = (xin.size(1) != 1);
    i = xin.size(1) - 1;
    acoef = (obj.value.size(0) != 1);
    b_bcoef = (xin.size(0) != 1);
    for (int k{0}; k <= i; k++) {
      i2 = bcoef * k;
      i1 = c.size(0) - 1;
      for (ib = 0; ib <= i1; ib++) {
        b_i1 = b_bcoef * ib;
        xtmp_re = obj.value[acoef * ib];
        c[ib + c.size(0) * k].re = xtmp_re * xin[b_i1 + xin.size(0) * i2].re;
        c[ib + c.size(0) * k].im = xtmp_re * xin[b_i1 + xin.size(0) * i2].im;
      }
    }
  }
  computeDFT(c, varargin_7, varargin_1, varargout_1, f);
  if (varargout_1.size(0) == 0) {
    d = 0.0;
  } else {
    d = std::fmod(static_cast<double>(varargout_1.size(0)), 2.0);
  }
  if (d == 0.0) {
    nCol = static_cast<double>(varargout_1.size(0)) / 2.0 - 1.0;
    b_bcoef = 1;
    if (varargout_1.size(0) != 1) {
      b_bcoef = 0;
    }
    if ((varargout_1.size(0) != 0) && (varargout_1.size(1) != 0) &&
        ((varargout_1.size(0) != 1) || (varargout_1.size(1) != 1))) {
      int npages;
      int ns;
      boolean_T shiftright;
      if (nCol < 0.0) {
        ns = -static_cast<int>(nCol);
        shiftright = false;
      } else {
        ns = static_cast<int>(nCol);
        shiftright = true;
      }
      if (varargout_1.size(b_bcoef) <= 1) {
        ns = 0;
      } else {
        if (ns > varargout_1.size(b_bcoef)) {
          ns -= varargout_1.size(b_bcoef) *
                div_s32(ns, varargout_1.size(b_bcoef));
        }
        if (ns > (varargout_1.size(b_bcoef) >> 1)) {
          ns = varargout_1.size(b_bcoef) - ns;
          shiftright = !shiftright;
        }
      }
      bcoef = varargout_1.size(0);
      acoef = varargout_1.size(1);
      if (bcoef >= acoef) {
        acoef = bcoef;
      }
      bcoef = acoef / 2;
      buffer.set_size(1, bcoef);
      for (i = 0; i < bcoef; i++) {
        buffer[i].re = 0.0F;
        buffer[i].im = 0.0F;
      }
      i = varargout_1.size(b_bcoef);
      i2 = varargout_1.size(b_bcoef);
      ib = 1;
      for (int k{0}; k < b_bcoef; k++) {
        ib *= varargout_1.size(0);
      }
      npages = 1;
      bcoef = b_bcoef + 2;
      for (int k{bcoef}; k < 3; k++) {
        npages *= varargout_1.size(1);
      }
      acoef = ib * varargout_1.size(b_bcoef);
      if ((varargout_1.size(b_bcoef) > 1) && (ns > 0)) {
        for (int b_i{0}; b_i < npages; b_i++) {
          bcoef = b_i * acoef;
          for (b_bcoef = 0; b_bcoef < ib; b_bcoef++) {
            b_i1 = bcoef + b_bcoef;
            if (shiftright) {
              for (int k{0}; k < ns; k++) {
                buffer[k] = varargout_1[b_i1 + ((k + i) - ns) * ib];
              }
              i1 = ns + 1;
              for (int k{i2}; k >= i1; k--) {
                varargout_1[b_i1 + (k - 1) * ib] =
                    varargout_1[b_i1 + ((k - ns) - 1) * ib];
              }
              for (int k{0}; k < ns; k++) {
                varargout_1[b_i1 + k * ib] = buffer[k];
              }
            } else {
              for (int k{0}; k < ns; k++) {
                buffer[k] = varargout_1[b_i1 + k * ib];
              }
              i1 = (i - ns) - 1;
              for (int k{0}; k <= i1; k++) {
                varargout_1[b_i1 + k * ib] = varargout_1[b_i1 + (k + ns) * ib];
              }
              for (int k{0}; k < ns; k++) {
                varargout_1[b_i1 + ((k + i) - ns) * ib] = buffer[k];
              }
            }
          }
        }
      }
    }
  } else if (varargout_1.size(0) > 1) {
    int npages;
    acoef =
        static_cast<int>(static_cast<unsigned int>(varargout_1.size(0)) >> 1) -
        1;
    npages = varargout_1.size(1) - 1;
    b_bcoef = varargout_1.size(0);
    if ((acoef + 1) << 1 == varargout_1.size(0)) {
      i2 = 1;
      for (int b_i{0}; b_i <= npages; b_i++) {
        b_i1 = i2;
        i2 += b_bcoef;
        ib = b_i1 + acoef;
        for (int k{0}; k <= acoef; k++) {
          float xtmp_im;
          bcoef = (b_i1 + k) - 1;
          xtmp_re = varargout_1[bcoef].re;
          xtmp_im = varargout_1[bcoef].im;
          i = ib + k;
          varargout_1[bcoef] = varargout_1[i];
          varargout_1[i].re = xtmp_re;
          varargout_1[i].im = xtmp_im;
        }
      }
    } else {
      i2 = 1;
      for (int b_i{0}; b_i <= npages; b_i++) {
        float xtmp_im;
        b_i1 = i2;
        i2 += b_bcoef;
        ib = b_i1 + acoef;
        xtmp_re = varargout_1[ib].re;
        xtmp_im = varargout_1[ib].im;
        for (int k{0}; k <= acoef; k++) {
          i = ib + k;
          i1 = (b_i1 + k) - 1;
          varargout_1[i] = varargout_1[i1];
          varargout_1[i1] = varargout_1[i + 1];
        }
        ib = (ib + acoef) + 1;
        varargout_1[ib].re = xtmp_re;
        varargout_1[ib].im = xtmp_im;
      }
    }
  }
  if (f.size(0) == 0) {
    d = 0.0;
  } else {
    d = std::fmod(static_cast<double>(f.size(0)), 2.0);
  }
  if (d == 0.0) {
    nCol = f[static_cast<int>(static_cast<double>(f.size(0)) / 2.0) - 1];
    acoef = f.size(0);
    for (i = 0; i < acoef; i++) {
      f[i] = f[i] - nCol;
    }
  } else {
    nCol =
        f[static_cast<int>((static_cast<double>(f.size(0)) + 1.0) / 2.0) - 1];
    acoef = f.size(0);
    for (i = 0; i < acoef; i++) {
      f[i] = f[i] - nCol;
    }
  }
  if (varargout_1.size(0) < 1) {
    acoef = 0;
  } else {
    acoef = varargout_1.size(0);
  }
  varargout_2.set_size(acoef);
  for (i = 0; i < acoef; i++) {
    varargout_2[i] = static_cast<float>(f[i]);
  }
  if (varargout_1.size(1) < 1) {
    acoef = 0;
  } else {
    acoef = varargout_1.size(1);
  }
  tempT.set_size(1, acoef);
  for (i = 0; i < acoef; i++) {
    tempT[i] = static_cast<float>(y[i]);
  }
  varargout_3.set_size(tempT.size(1));
  acoef = tempT.size(1);
  for (i = 0; i < acoef; i++) {
    varargout_3[i] = tempT[i];
  }
}

} // namespace coder

//
// File trailer for stft.cpp
//
// [EOF]
//
