//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: computeDFT.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 22-Oct-2022 15:24:58
//

// Include Files
#include "computeDFT.h"
#include "FFTImplementationCallback.h"
#include "psdfreqvec.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const ::coder::array<creal32_T, 2U> &xin
//                double nfft
//                double varargin_1
//                ::coder::array<creal32_T, 2U> &Xx
//                ::coder::array<double, 1U> &f
// Return Type  : void
//
namespace coder {
void computeDFT(const ::coder::array<creal32_T, 2U> &xin, double nfft,
                double varargin_1, ::coder::array<creal32_T, 2U> &Xx,
                ::coder::array<double, 1U> &f)
{
  array<creal32_T, 2U> wrappedData;
  array<creal32_T, 2U> xw;
  array<creal32_T, 1U> x;
  array<float, 2U> costab;
  array<float, 2U> costab1q;
  array<float, 2U> sintab;
  array<float, 2U> sintabinv;
  int b_remainder;
  int i;
  int i1;
  int i3;
  int loop_ub;
  int loop_ub_tmp;
  int offset;
  int remainder_tmp;
  loop_ub_tmp = static_cast<int>(nfft);
  xw.set_size(loop_ub_tmp, xin.size(1));
  offset = static_cast<int>(nfft) * xin.size(1);
  for (i = 0; i < offset; i++) {
    xw[i].re = 0.0F;
    xw[i].im = 0.0F;
  }
  if (xin.size(0) > nfft) {
    i = xin.size(1);
    if (i - 1 >= 0) {
      loop_ub = xin.size(0);
      if (static_cast<unsigned int>(nfft) == 0U) {
        i1 = MAX_int32_T;
      } else {
        i1 = static_cast<int>(static_cast<unsigned int>(xin.size(0)) /
                              static_cast<unsigned int>(nfft));
      }
      remainder_tmp = i1 * static_cast<int>(nfft);
      b_remainder = (xin.size(0) - remainder_tmp) - 1;
      i3 = b_remainder + 2;
    }
    for (int j{0}; j < i; j++) {
      int i2;
      x.set_size(xin.size(0));
      for (i2 = 0; i2 < loop_ub; i2++) {
        x[i2] = xin[i2 + xin.size(0) * j];
      }
      if (xin.size(0) == 1) {
        wrappedData.set_size(1, loop_ub_tmp);
        for (i2 = 0; i2 < loop_ub_tmp; i2++) {
          wrappedData[i2].re = 0.0F;
          wrappedData[i2].im = 0.0F;
        }
      } else {
        wrappedData.set_size(loop_ub_tmp, 1);
        for (i2 = 0; i2 < loop_ub_tmp; i2++) {
          wrappedData[i2].re = 0.0F;
          wrappedData[i2].im = 0.0F;
        }
      }
      for (int k{0}; k <= b_remainder; k++) {
        wrappedData[k] = x[remainder_tmp + k];
      }
      for (int k{i3}; k <= loop_ub_tmp; k++) {
        wrappedData[k - 1].re = 0.0F;
        wrappedData[k - 1].im = 0.0F;
      }
      for (int b_j{0}; b_j < i1; b_j++) {
        offset = b_j * static_cast<int>(nfft);
        for (int k{0}; k < loop_ub_tmp; k++) {
          i2 = offset + k;
          wrappedData[k].re = wrappedData[k].re + x[i2].re;
          wrappedData[k].im = wrappedData[k].im + x[i2].im;
        }
      }
      offset = wrappedData.size(0) * wrappedData.size(1);
      for (i2 = 0; i2 < offset; i2++) {
        xw[i2 + xw.size(0) * j] = wrappedData[i2];
      }
    }
  } else {
    xw.set_size(xin.size(0), xin.size(1));
    offset = xin.size(0) * xin.size(1);
    for (i = 0; i < offset; i++) {
      xw[i] = xin[i];
    }
  }
  if ((xw.size(0) == 0) || (xw.size(1) == 0) || (static_cast<int>(nfft) == 0)) {
    Xx.set_size(loop_ub_tmp, xw.size(1));
    offset = static_cast<int>(nfft) * xw.size(1);
    for (i = 0; i < offset; i++) {
      Xx[i].re = 0.0F;
      Xx[i].im = 0.0F;
    }
  } else {
    float e;
    boolean_T useRadix2;
    useRadix2 =
        ((static_cast<int>(nfft) > 0) &&
         ((static_cast<int>(nfft) & (static_cast<int>(nfft) - 1)) == 0));
    internal::FFTImplementationCallback::get_algo_sizes(
        static_cast<int>(nfft), useRadix2, &loop_ub, &offset);
    e = 6.28318548F / static_cast<float>(offset);
    loop_ub_tmp = offset / 2 / 2;
    costab1q.set_size(1, loop_ub_tmp + 1);
    costab1q[0] = 1.0F;
    offset = loop_ub_tmp / 2 - 1;
    for (int k{0}; k <= offset; k++) {
      costab1q[k + 1] = std::cos(e * static_cast<float>(k + 1));
    }
    i = offset + 2;
    i1 = loop_ub_tmp - 1;
    for (int k{i}; k <= i1; k++) {
      costab1q[k] = std::sin(e * static_cast<float>(loop_ub_tmp - k));
    }
    costab1q[loop_ub_tmp] = 0.0F;
    if (!useRadix2) {
      loop_ub_tmp = costab1q.size(1) - 1;
      offset = (costab1q.size(1) - 1) << 1;
      costab.set_size(1, offset + 1);
      sintab.set_size(1, offset + 1);
      costab[0] = 1.0F;
      sintab[0] = 0.0F;
      sintabinv.set_size(1, offset + 1);
      for (int k{0}; k < loop_ub_tmp; k++) {
        sintabinv[k + 1] = costab1q[(loop_ub_tmp - k) - 1];
      }
      i = costab1q.size(1);
      for (int k{i}; k <= offset; k++) {
        sintabinv[k] = costab1q[k - loop_ub_tmp];
      }
      for (int k{0}; k < loop_ub_tmp; k++) {
        costab[k + 1] = costab1q[k + 1];
        sintab[k + 1] = -costab1q[(loop_ub_tmp - k) - 1];
      }
      i = costab1q.size(1);
      for (int k{i}; k <= offset; k++) {
        costab[k] = -costab1q[offset - k];
        sintab[k] = -costab1q[k - loop_ub_tmp];
      }
    } else {
      loop_ub_tmp = costab1q.size(1) - 1;
      offset = (costab1q.size(1) - 1) << 1;
      costab.set_size(1, offset + 1);
      sintab.set_size(1, offset + 1);
      costab[0] = 1.0F;
      sintab[0] = 0.0F;
      for (int k{0}; k < loop_ub_tmp; k++) {
        costab[k + 1] = costab1q[k + 1];
        sintab[k + 1] = -costab1q[(loop_ub_tmp - k) - 1];
      }
      i = costab1q.size(1);
      for (int k{i}; k <= offset; k++) {
        costab[k] = -costab1q[offset - k];
        sintab[k] = -costab1q[k - loop_ub_tmp];
      }
      sintabinv.set_size(1, 0);
    }
    if (useRadix2) {
      internal::FFTImplementationCallback::r2br_r2dit_trig(
          xw, static_cast<int>(nfft), costab, sintab, Xx);
    } else {
      internal::FFTImplementationCallback::dobluesteinfft(
          xw, loop_ub, static_cast<int>(nfft), costab, sintab, sintabinv, Xx);
    }
  }
  psdfreqvec(nfft, varargin_1, f);
}

} // namespace coder

//
// File trailer for computeDFT.cpp
//
// [EOF]
//
