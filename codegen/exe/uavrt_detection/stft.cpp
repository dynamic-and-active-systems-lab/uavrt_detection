//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// stft.cpp
//
// Code generation for function 'stft'
//

// Include files
#include "stft.h"
#include "FFTImplementationCallback.h"
#include "formatSTFTOutput.h"
#include "psdfreqvec.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_rtwutil.h"
#include "coder_array.h"
#include <cmath>
#include <string.h>

// Function Definitions
namespace coder {
void stft(const ::coder::array<creal32_T, 2U> &x, double varargin_1,
          const ::coder::array<double, 1U> &varargin_3, double varargin_5,
          double varargin_7, ::coder::array<creal32_T, 2U> &varargout_1,
          ::coder::array<float, 1U> &varargout_2,
          ::coder::array<float, 1U> &varargout_3)
{
  static const char b[8]{'o', 'n', 'e', 's', 'i', 'd', 'e', 'd'};
  static const char freqRange[8]{'c', 'e', 'n', 't', 'e', 'r', 'e', 'd'};
  array<creal32_T, 2U> c;
  array<creal32_T, 2U> xin;
  array<creal32_T, 2U> xw;
  array<creal32_T, 1U> b_x;
  array<double, 2U> y;
  array<double, 1U> f;
  array<float, 2U> costab;
  array<float, 2U> costab1q;
  array<float, 2U> sintab;
  array<float, 2U> sintabinv;
  array<float, 1U> varargout_2_Window;
  double hopSize;
  double nCol;
  double varargout_2_NumFreqSamples;
  float e;
  int acoef;
  int b_varargin_3;
  int bcoef;
  int i;
  int i1;
  int i2;
  int ret;
  ret = memcmp(&freqRange[0], &b[0], 8);
  if (ret == 0) {
    if (std::isnan(varargin_7) || std::isinf(varargin_7)) {
      nCol = rtNaN;
    } else if (varargin_7 == 0.0) {
      nCol = 0.0;
    } else {
      nCol = std::fmod(varargin_7, 2.0);
      if (nCol == 0.0) {
        nCol = 0.0;
      } else if (varargin_7 < 0.0) {
        nCol += 2.0;
      }
    }
    if (nCol == 0.0) {
      varargout_2_NumFreqSamples = varargin_7 / 2.0 + 1.0;
    } else {
      varargout_2_NumFreqSamples = (varargin_7 + 1.0) / 2.0;
    }
  } else {
    varargout_2_NumFreqSamples = varargin_7;
  }
  varargout_2_Window.set_size(varargin_3.size(0));
  ret = varargin_3.size(0);
  for (i = 0; i < ret; i++) {
    varargout_2_Window[i] = static_cast<float>(varargin_3[i]);
  }
  hopSize = static_cast<double>(varargin_3.size(0)) - varargin_5;
  nCol = std::trunc((static_cast<double>(x.size(1)) - varargin_5) / hopSize);
  i = static_cast<int>(nCol);
  xin.set_size(varargin_3.size(0), i);
  ret = varargin_3.size(0) * static_cast<int>(nCol);
  for (i1 = 0; i1 < ret; i1++) {
    xin[i1].re = 0.0F;
    xin[i1].im = 0.0F;
  }
  if (nCol - 1.0 < 0.0) {
    y.set_size(y.size(0), 0);
  } else {
    y.set_size(1, static_cast<int>(nCol - 1.0) + 1);
    ret = static_cast<int>(nCol - 1.0);
    for (i1 = 0; i1 <= ret; i1++) {
      y[i1] = i1;
    }
  }
  for (acoef = 0; acoef < i; acoef++) {
    double d;
    nCol = hopSize * ((static_cast<double>(acoef) + 1.0) - 1.0);
    d = static_cast<double>(varargin_3.size(0)) + nCol;
    if (nCol + 1.0 > d) {
      i1 = 0;
      i2 = 0;
    } else {
      i1 = static_cast<int>(nCol + 1.0) - 1;
      i2 = static_cast<int>(d);
    }
    ret = i2 - i1;
    for (i2 = 0; i2 < ret; i2++) {
      xin[i2 + xin.size(0) * acoef] = x[i1 + i2];
    }
  }
  y.set_size(1, y.size(1));
  nCol = static_cast<double>(varargin_3.size(0)) / 2.0;
  ret = y.size(1) - 1;
  for (i = 0; i <= ret; i++) {
    y[i] = (y[i] * hopSize + nCol) / varargin_1;
  }
  ret = xin.size(0);
  acoef = varargout_2_Window.size(0);
  if (ret <= acoef) {
    acoef = ret;
  }
  if (xin.size(0) == 1) {
    acoef = varargout_2_Window.size(0);
  } else if (varargout_2_Window.size(0) == 1) {
    acoef = xin.size(0);
  } else if (varargout_2_Window.size(0) == xin.size(0)) {
    acoef = varargout_2_Window.size(0);
  }
  c.set_size(acoef, xin.size(1));
  ret = xin.size(0);
  acoef = varargout_2_Window.size(0);
  if (ret <= acoef) {
    acoef = ret;
  }
  if (xin.size(0) == 1) {
    acoef = varargout_2_Window.size(0);
  } else if (varargout_2_Window.size(0) == 1) {
    acoef = xin.size(0);
  } else if (varargout_2_Window.size(0) == xin.size(0)) {
    acoef = varargout_2_Window.size(0);
  }
  if ((acoef != 0) && (xin.size(1) != 0)) {
    ret = (xin.size(1) != 1);
    i = xin.size(1) - 1;
    acoef = (varargout_2_Window.size(0) != 1);
    bcoef = (xin.size(0) != 1);
    for (int k{0}; k <= i; k++) {
      b_varargin_3 = ret * k;
      i1 = c.size(0) - 1;
      for (int b_k{0}; b_k <= i1; b_k++) {
        i2 = bcoef * b_k;
        e = varargout_2_Window[acoef * b_k];
        c[b_k + c.size(0) * k].re = e * xin[i2 + xin.size(0) * b_varargin_3].re;
        c[b_k + c.size(0) * k].im = e * xin[i2 + xin.size(0) * b_varargin_3].im;
      }
    }
  }
  b_varargin_3 = static_cast<int>(varargin_7);
  xw.set_size(b_varargin_3, c.size(1));
  ret = static_cast<int>(varargin_7) * c.size(1);
  for (i = 0; i < ret; i++) {
    xw[i].re = 0.0F;
    xw[i].im = 0.0F;
  }
  if (c.size(0) > varargin_7) {
    i = c.size(1);
    for (int b_k{0}; b_k < i; b_k++) {
      ret = c.size(0);
      b_x.set_size(c.size(0));
      for (i1 = 0; i1 < ret; i1++) {
        b_x[i1] = c[i1 + c.size(0) * b_k];
      }
      if (c.size(0) == 1) {
        xin.set_size(1, b_varargin_3);
        for (i1 = 0; i1 < b_varargin_3; i1++) {
          xin[i1].re = 0.0F;
          xin[i1].im = 0.0F;
        }
      } else {
        xin.set_size(b_varargin_3, 1);
        for (i1 = 0; i1 < b_varargin_3; i1++) {
          xin[i1].re = 0.0F;
          xin[i1].im = 0.0F;
        }
      }
      bcoef = div_s32(c.size(0), static_cast<int>(varargin_7));
      ret = bcoef * static_cast<int>(varargin_7);
      acoef = (c.size(0) - ret) - 1;
      for (int k{0}; k <= acoef; k++) {
        xin[k] = b_x[ret + k];
      }
      i1 = acoef + 2;
      for (int k{i1}; k <= b_varargin_3; k++) {
        xin[k - 1].re = 0.0F;
        xin[k - 1].im = 0.0F;
      }
      for (acoef = 0; acoef < bcoef; acoef++) {
        ret = acoef * static_cast<int>(varargin_7);
        for (int k{0}; k < b_varargin_3; k++) {
          i1 = ret + k;
          xin[k].re = xin[k].re + b_x[i1].re;
          xin[k].im = xin[k].im + b_x[i1].im;
        }
      }
      ret = xin.size(0) * xin.size(1);
      for (i1 = 0; i1 < ret; i1++) {
        xw[i1 + xw.size(0) * b_k] = xin[i1];
      }
    }
  } else {
    xw.set_size(c.size(0), c.size(1));
    ret = c.size(0) * c.size(1);
    for (i = 0; i < ret; i++) {
      xw[i] = c[i];
    }
  }
  if ((xw.size(0) == 0) || (xw.size(1) == 0) ||
      (static_cast<int>(varargin_7) == 0)) {
    varargout_1.set_size(b_varargin_3, xw.size(1));
    ret = static_cast<int>(varargin_7) * xw.size(1);
    for (i = 0; i < ret; i++) {
      varargout_1[i].re = 0.0F;
      varargout_1[i].im = 0.0F;
    }
  } else {
    boolean_T useRadix2;
    useRadix2 = ((static_cast<int>(varargin_7) > 0) &&
                 ((static_cast<int>(varargin_7) &
                   (static_cast<int>(varargin_7) - 1)) == 0));
    internal::FFTImplementationCallback::get_algo_sizes(
        static_cast<int>(varargin_7), useRadix2, &bcoef, &ret);
    e = 6.28318548F / static_cast<float>(ret);
    acoef = ret / 2 / 2;
    costab1q.set_size(1, acoef + 1);
    costab1q[0] = 1.0F;
    ret = acoef / 2 - 1;
    for (int k{0}; k <= ret; k++) {
      costab1q[k + 1] = std::cos(e * static_cast<float>(k + 1));
    }
    i = ret + 2;
    i1 = acoef - 1;
    for (int k{i}; k <= i1; k++) {
      costab1q[k] = std::sin(e * static_cast<float>(acoef - k));
    }
    costab1q[acoef] = 0.0F;
    if (!useRadix2) {
      acoef = costab1q.size(1) - 1;
      ret = (costab1q.size(1) - 1) << 1;
      costab.set_size(1, ret + 1);
      sintab.set_size(1, ret + 1);
      costab[0] = 1.0F;
      sintab[0] = 0.0F;
      sintabinv.set_size(1, ret + 1);
      for (int k{0}; k < acoef; k++) {
        sintabinv[k + 1] = costab1q[(acoef - k) - 1];
      }
      i = costab1q.size(1);
      for (int k{i}; k <= ret; k++) {
        sintabinv[k] = costab1q[k - acoef];
      }
      for (int k{0}; k < acoef; k++) {
        costab[k + 1] = costab1q[k + 1];
        sintab[k + 1] = -costab1q[(acoef - k) - 1];
      }
      i = costab1q.size(1);
      for (int k{i}; k <= ret; k++) {
        costab[k] = -costab1q[ret - k];
        sintab[k] = -costab1q[k - acoef];
      }
    } else {
      acoef = costab1q.size(1) - 1;
      ret = (costab1q.size(1) - 1) << 1;
      costab.set_size(1, ret + 1);
      sintab.set_size(1, ret + 1);
      costab[0] = 1.0F;
      sintab[0] = 0.0F;
      for (int k{0}; k < acoef; k++) {
        costab[k + 1] = costab1q[k + 1];
        sintab[k + 1] = -costab1q[(acoef - k) - 1];
      }
      i = costab1q.size(1);
      for (int k{i}; k <= ret; k++) {
        costab[k] = -costab1q[ret - k];
        sintab[k] = -costab1q[k - acoef];
      }
      sintabinv.set_size(1, 0);
    }
    if (useRadix2) {
      internal::FFTImplementationCallback::r2br_r2dit_trig(
          xw, static_cast<int>(varargin_7), costab, sintab, varargout_1);
    } else {
      internal::FFTImplementationCallback::dobluesteinfft(
          xw, bcoef, static_cast<int>(varargin_7), costab, sintab, sintabinv,
          varargout_1);
    }
  }
  psdfreqvec(varargin_7, varargin_1, f);
  signal::internal::stft::formatSTFTOutput(varargout_1, f, freqRange,
                                           varargout_2_NumFreqSamples);
  if (varargout_1.size(0) < 1) {
    ret = 0;
  } else {
    ret = varargout_1.size(0);
  }
  varargout_2.set_size(ret);
  for (i = 0; i < ret; i++) {
    varargout_2[i] = static_cast<float>(f[i]);
  }
  if (varargout_1.size(1) < 1) {
    ret = 0;
  } else {
    ret = varargout_1.size(1);
  }
  costab1q.set_size(1, ret);
  for (i = 0; i < ret; i++) {
    costab1q[i] = static_cast<float>(y[i]);
  }
  varargout_3.set_size(costab1q.size(1));
  ret = costab1q.size(1);
  for (i = 0; i < ret; i++) {
    varargout_3[i] = costab1q[i];
  }
}

void stft(const ::coder::array<creal_T, 2U> &x, double varargin_1,
          const ::coder::array<double, 1U> &varargin_3, double varargin_5,
          double varargin_7, ::coder::array<creal_T, 3U> &varargout_1,
          ::coder::array<double, 1U> &varargout_2,
          ::coder::array<double, 1U> &varargout_3)
{
  static const char b[8]{'o', 'n', 'e', 's', 'i', 'd', 'e', 'd'};
  static const char freqRange[8]{'c', 'e', 'n', 't', 'e', 'r', 'e', 'd'};
  array<creal_T, 3U> c;
  array<creal_T, 3U> xin;
  array<creal_T, 2U> b_varargout_1;
  array<creal_T, 2U> c_varargout_1;
  array<creal_T, 2U> wrappedData;
  array<creal_T, 1U> b_x;
  array<double, 2U> costab;
  array<double, 2U> sintab;
  array<double, 2U> sintabinv;
  array<double, 2U> y;
  array<double, 1U> f;
  double hopSize;
  double nCol;
  double varargout_2_NumFreqSamples;
  int acoef;
  int b_bcoef;
  int bcoef;
  int i;
  int i1;
  int i2;
  int i3;
  int iCol;
  int loop_ub;
  int ret;
  if (x.size(0) == 1) {
    b_varargout_1.set_size(100, 1);
    for (i = 0; i < 100; i++) {
      b_varargout_1[i] = x[i];
    }
  } else {
    b_varargout_1.set_size(x.size(0), 100);
    loop_ub = x.size(0) * 100;
    for (i = 0; i < loop_ub; i++) {
      b_varargout_1[i] = x[i];
    }
  }
  ret = memcmp(&freqRange[0], &b[0], 8);
  if (ret == 0) {
    if (std::isnan(varargin_7) || std::isinf(varargin_7)) {
      nCol = rtNaN;
    } else if (varargin_7 == 0.0) {
      nCol = 0.0;
    } else {
      nCol = std::fmod(varargin_7, 2.0);
      if (nCol == 0.0) {
        nCol = 0.0;
      } else if (varargin_7 < 0.0) {
        nCol += 2.0;
      }
    }
    if (nCol == 0.0) {
      varargout_2_NumFreqSamples = varargin_7 / 2.0 + 1.0;
    } else {
      varargout_2_NumFreqSamples = (varargin_7 + 1.0) / 2.0;
    }
  } else {
    varargout_2_NumFreqSamples = varargin_7;
  }
  hopSize = static_cast<double>(varargin_3.size(0)) - varargin_5;
  nCol = std::trunc((static_cast<double>(b_varargout_1.size(0)) - varargin_5) /
                    hopSize);
  i = static_cast<int>(nCol);
  xin.set_size(varargin_3.size(0), i, b_varargout_1.size(1));
  loop_ub = varargin_3.size(0) * static_cast<int>(nCol) * b_varargout_1.size(1);
  for (i1 = 0; i1 < loop_ub; i1++) {
    xin[i1].re = 0.0;
    xin[i1].im = 0.0;
  }
  if (nCol - 1.0 < 0.0) {
    y.set_size(y.size(0), 0);
  } else {
    y.set_size(1, static_cast<int>(nCol - 1.0) + 1);
    loop_ub = static_cast<int>(nCol - 1.0);
    for (i1 = 0; i1 <= loop_ub; i1++) {
      y[i1] = i1;
    }
  }
  if (static_cast<int>(nCol) - 1 >= 0) {
    i2 = b_varargout_1.size(1);
    bcoef = b_varargout_1.size(1);
  }
  for (iCol = 0; iCol < i; iCol++) {
    double d;
    nCol = hopSize * ((static_cast<double>(iCol) + 1.0) - 1.0);
    d = static_cast<double>(varargin_3.size(0)) + nCol;
    if (nCol + 1.0 > d) {
      i1 = 0;
      i3 = 0;
    } else {
      i1 = static_cast<int>(nCol + 1.0) - 1;
      i3 = static_cast<int>(d);
    }
    b_bcoef = xin.size(0);
    acoef = xin.size(2);
    loop_ub = i3 - i1;
    c_varargout_1.set_size(loop_ub, i2);
    for (i3 = 0; i3 < bcoef; i3++) {
      for (ret = 0; ret < loop_ub; ret++) {
        c_varargout_1[ret + c_varargout_1.size(0) * i3] =
            b_varargout_1[(i1 + ret) + b_varargout_1.size(0) * i3];
      }
    }
    ret = xin.size(0);
    for (i1 = 0; i1 < acoef; i1++) {
      for (i3 = 0; i3 < b_bcoef; i3++) {
        xin[(i3 + xin.size(0) * iCol) + xin.size(0) * xin.size(1) * i1] =
            c_varargout_1[i3 + ret * i1];
      }
    }
  }
  y.set_size(1, y.size(1));
  nCol = static_cast<double>(varargin_3.size(0)) / 2.0;
  loop_ub = y.size(1) - 1;
  for (i = 0; i <= loop_ub; i++) {
    y[i] = (y[i] * hopSize + nCol) / varargin_1;
  }
  ret = xin.size(0);
  b_bcoef = varargin_3.size(0);
  if (ret <= b_bcoef) {
    b_bcoef = ret;
  }
  if (xin.size(0) == 1) {
    b_bcoef = varargin_3.size(0);
  } else if (varargin_3.size(0) == 1) {
    b_bcoef = xin.size(0);
  } else if (varargin_3.size(0) == xin.size(0)) {
    b_bcoef = varargin_3.size(0);
  }
  c.set_size(b_bcoef, xin.size(1), xin.size(2));
  ret = xin.size(0);
  b_bcoef = varargin_3.size(0);
  if (ret <= b_bcoef) {
    b_bcoef = ret;
  }
  if (xin.size(0) == 1) {
    b_bcoef = varargin_3.size(0);
  } else if (varargin_3.size(0) == 1) {
    b_bcoef = xin.size(0);
  } else if (varargin_3.size(0) == xin.size(0)) {
    b_bcoef = varargin_3.size(0);
  }
  if ((b_bcoef != 0) && (xin.size(1) != 0)) {
    ret = (xin.size(2) != 1);
    i = xin.size(2) - 1;
    b_bcoef = (xin.size(1) != 1);
    acoef = (varargin_3.size(0) != 1);
    bcoef = (xin.size(0) != 1);
    for (int k{0}; k <= i; k++) {
      loop_ub = ret * k;
      i1 = c.size(1) - 1;
      for (int b_k{0}; b_k <= i1; b_k++) {
        iCol = b_bcoef * b_k;
        i2 = c.size(0) - 1;
        for (int c_k{0}; c_k <= i2; c_k++) {
          i3 = bcoef * c_k;
          nCol = varargin_3[acoef * c_k];
          c[(c_k + c.size(0) * b_k) + c.size(0) * c.size(1) * k].re =
              nCol * xin[(i3 + xin.size(0) * iCol) +
                         xin.size(0) * xin.size(1) * loop_ub]
                         .re;
          c[(c_k + c.size(0) * b_k) + c.size(0) * c.size(1) * k].im =
              nCol * xin[(i3 + xin.size(0) * iCol) +
                         xin.size(0) * xin.size(1) * loop_ub]
                         .im;
        }
      }
    }
  }
  bcoef = static_cast<int>(varargin_7);
  xin.set_size(bcoef, c.size(1), c.size(2));
  loop_ub = static_cast<int>(varargin_7) * c.size(1) * c.size(2);
  for (i = 0; i < loop_ub; i++) {
    xin[i].re = 0.0;
    xin[i].im = 0.0;
  }
  if (c.size(0) > varargin_7) {
    i = c.size(1) * c.size(2);
    for (iCol = 0; iCol < i; iCol++) {
      loop_ub = c.size(0);
      ret = c.size(0);
      b_x.set_size(c.size(0));
      for (i1 = 0; i1 < loop_ub; i1++) {
        b_x[i1] = c[i1 + ret * iCol];
      }
      if (c.size(0) == 1) {
        wrappedData.set_size(1, bcoef);
        for (i1 = 0; i1 < bcoef; i1++) {
          wrappedData[i1].re = 0.0;
          wrappedData[i1].im = 0.0;
        }
      } else {
        wrappedData.set_size(bcoef, 1);
        for (i1 = 0; i1 < bcoef; i1++) {
          wrappedData[i1].re = 0.0;
          wrappedData[i1].im = 0.0;
        }
      }
      acoef = div_s32(c.size(0), static_cast<int>(varargin_7));
      b_bcoef = acoef * static_cast<int>(varargin_7);
      ret = (c.size(0) - b_bcoef) - 1;
      for (int k{0}; k <= ret; k++) {
        wrappedData[k] = b_x[b_bcoef + k];
      }
      i1 = ret + 2;
      for (int k{i1}; k <= bcoef; k++) {
        wrappedData[k - 1].re = 0.0;
        wrappedData[k - 1].im = 0.0;
      }
      for (ret = 0; ret < acoef; ret++) {
        b_bcoef = ret * static_cast<int>(varargin_7);
        for (int k{0}; k < bcoef; k++) {
          i1 = b_bcoef + k;
          wrappedData[k].re = wrappedData[k].re + b_x[i1].re;
          wrappedData[k].im = wrappedData[k].im + b_x[i1].im;
        }
      }
      b_bcoef = wrappedData.size(0) * wrappedData.size(1);
      ret = xin.size(0);
      for (i1 = 0; i1 < b_bcoef; i1++) {
        xin[i1 + ret * iCol] = wrappedData[i1];
      }
    }
  } else {
    xin.set_size(c.size(0), c.size(1), c.size(2));
    loop_ub = c.size(0) * c.size(1) * c.size(2);
    for (i = 0; i < loop_ub; i++) {
      xin[i] = c[i];
    }
  }
  if ((xin.size(0) == 0) || (xin.size(1) == 0) ||
      (static_cast<int>(varargin_7) == 0)) {
    varargout_1.set_size(bcoef, xin.size(1), xin.size(2));
    loop_ub = static_cast<int>(varargin_7) * xin.size(1) * xin.size(2);
    for (i = 0; i < loop_ub; i++) {
      varargout_1[i].re = 0.0;
      varargout_1[i].im = 0.0;
    }
  } else {
    boolean_T useRadix2;
    useRadix2 = ((static_cast<int>(varargin_7) > 0) &&
                 ((static_cast<int>(varargin_7) &
                   (static_cast<int>(varargin_7) - 1)) == 0));
    internal::FFTImplementationCallback::get_algo_sizes(
        static_cast<int>(varargin_7), useRadix2, &ret, &b_bcoef);
    internal::FFTImplementationCallback::generate_twiddle_tables(
        b_bcoef, useRadix2, costab, sintab, sintabinv);
    if (useRadix2) {
      internal::FFTImplementationCallback::r2br_r2dit_trig(
          xin, static_cast<int>(varargin_7), costab, sintab, varargout_1);
    } else {
      internal::FFTImplementationCallback::dobluesteinfft(
          xin, ret, static_cast<int>(varargin_7), costab, sintab, sintabinv,
          varargout_1);
    }
  }
  psdfreqvec(varargin_7, varargin_1, f);
  signal::internal::stft::formatSTFTOutput(varargout_1, f, freqRange,
                                           varargout_2_NumFreqSamples);
  if (varargout_1.size(0) < 1) {
    loop_ub = 0;
  } else {
    loop_ub = varargout_1.size(0);
  }
  varargout_2.set_size(loop_ub);
  for (i = 0; i < loop_ub; i++) {
    varargout_2[i] = f[i];
  }
  if (varargout_1.size(1) < 1) {
    loop_ub = 0;
  } else {
    loop_ub = varargout_1.size(1);
  }
  varargout_3.set_size(loop_ub);
  for (i = 0; i < loop_ub; i++) {
    varargout_3[i] = y[i];
  }
}

} // namespace coder

// End of code generation (stft.cpp)
