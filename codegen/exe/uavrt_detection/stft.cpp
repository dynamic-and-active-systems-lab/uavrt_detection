//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: stft.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 14:31:55
//

// Include Files
#include "stft.h"
#include "computeDFT.h"
#include "eml_int_forloop_overflow_check.h"
#include "indexShapeCheck.h"
#include "iseven.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "validateattributes.h"
#include "coder_array.h"
#include "omp.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string.h>
#include <string>

// Variable Definitions
static rtRunTimeErrorInfo bb_emlrtRTEI{
    368,                // lineNo
    "verifyDataAndTime" // fName
};

// Function Declarations
namespace coder {
static void computeSTFT(const ::coder::array<creal32_T, 1U> &x,
                        double opts_DataLength, double opts_EffectiveFs,
                        const ::coder::array<float, 1U> &opts_Window,
                        double opts_WindowLength, double opts_OverlapLength,
                        double opts_FFTLength, const char opts_FreqRange[8],
                        double opts_NumFreqSamples,
                        ::coder::array<creal32_T, 2U> &S,
                        ::coder::array<float, 1U> &F,
                        ::coder::array<float, 2U> &T);

}
static void j_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum);

static void rtErrorWithMessageID(const long long i, const char *aFcnName,
                                 int aLineNum);

static void rtErrorWithMessageID(const char *r, const char *r1,
                                 const char *aFcnName, int aLineNum);

static void s_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void t_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void v_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : const ::coder::array<creal32_T, 1U> &x
//                double opts_DataLength
//                double opts_EffectiveFs
//                const ::coder::array<float, 1U> &opts_Window
//                double opts_WindowLength
//                double opts_OverlapLength
//                double opts_FFTLength
//                const char opts_FreqRange[8]
//                double opts_NumFreqSamples
//                ::coder::array<creal32_T, 2U> &S
//                ::coder::array<float, 1U> &F
//                ::coder::array<float, 2U> &T
// Return Type  : void
//
namespace coder {
static void computeSTFT(const ::coder::array<creal32_T, 1U> &x,
                        double opts_DataLength, double opts_EffectiveFs,
                        const ::coder::array<float, 1U> &opts_Window,
                        double opts_WindowLength, double opts_OverlapLength,
                        double opts_FFTLength, const char opts_FreqRange[8],
                        double opts_NumFreqSamples,
                        ::coder::array<creal32_T, 2U> &S,
                        ::coder::array<float, 1U> &F,
                        ::coder::array<float, 2U> &T)
{
  static rtBoundsCheckInfo f_emlrtBCI{
      -1,               // iFirst
      -1,               // iLast
      23,               // lineNo
      11,               // colNo
      "",               // aName
      "getSTFTColumns", // fName
      "C:\\Program "
      "Files\\MATLAB\\toolbox\\signal\\signal\\+signal\\+internal\\+"
      "stft\\getSTFTColumns.m", // pName
      0                         // checkKind
  };
  static rtBoundsCheckInfo g_emlrtBCI{
      -1,               // iFirst
      -1,               // iLast
      23,               // lineNo
      23,               // colNo
      "",               // aName
      "getSTFTColumns", // fName
      "C:\\Program "
      "Files\\MATLAB\\toolbox\\signal\\signal\\+signal\\+internal\\+"
      "stft\\getSTFTColumns.m", // pName
      0                         // checkKind
  };
  static rtBoundsCheckInfo h_emlrtBCI{
      -1,               // iFirst
      -1,               // iLast
      23,               // lineNo
      42,               // colNo
      "",               // aName
      "getSTFTColumns", // fName
      "C:\\Program "
      "Files\\MATLAB\\toolbox\\signal\\signal\\+signal\\+internal\\+"
      "stft\\getSTFTColumns.m", // pName
      0                         // checkKind
  };
  static rtBoundsCheckInfo i_emlrtBCI{
      -1,                                                           // iFirst
      -1,                                                           // iLast
      279,                                                          // lineNo
      12,                                                           // colNo
      "",                                                           // aName
      "computeSTFT",                                                // fName
      "C:\\Program Files\\MATLAB\\toolbox\\signal\\signal\\stft.m", // pName
      0                                                             // checkKind
  };
  static rtBoundsCheckInfo j_emlrtBCI{
      -1,                                                           // iFirst
      -1,                                                           // iLast
      279,                                                          // lineNo
      14,                                                           // colNo
      "",                                                           // aName
      "computeSTFT",                                                // fName
      "C:\\Program Files\\MATLAB\\toolbox\\signal\\signal\\stft.m", // pName
      0                                                             // checkKind
  };
  static rtBoundsCheckInfo k_emlrtBCI{
      -1,                                                           // iFirst
      -1,                                                           // iLast
      278,                                                          // lineNo
      12,                                                           // colNo
      "",                                                           // aName
      "computeSTFT",                                                // fName
      "C:\\Program Files\\MATLAB\\toolbox\\signal\\signal\\stft.m", // pName
      0                                                             // checkKind
  };
  static rtBoundsCheckInfo l_emlrtBCI{
      -1,                                                           // iFirst
      -1,                                                           // iLast
      278,                                                          // lineNo
      14,                                                           // colNo
      "",                                                           // aName
      "computeSTFT",                                                // fName
      "C:\\Program Files\\MATLAB\\toolbox\\signal\\signal\\stft.m", // pName
      0                                                             // checkKind
  };
  static rtBoundsCheckInfo m_emlrtBCI{
      -1,           // iFirst
      -1,           // iLast
      13,           // lineNo
      13,           // colNo
      "",           // aName
      "centerfreq", // fName
      "C:\\Program "
      "Files\\MATLAB\\toolbox\\signal\\signal\\+signal\\+internal\\+"
      "spectral\\centerfreq.m", // pName
      0                         // checkKind
  };
  static rtBoundsCheckInfo n_emlrtBCI{
      -1,           // iFirst
      -1,           // iLast
      16,           // lineNo
      13,           // colNo
      "",           // aName
      "centerfreq", // fName
      "C:\\Program "
      "Files\\MATLAB\\toolbox\\signal\\signal\\+signal\\+internal\\+"
      "spectral\\centerfreq.m", // pName
      0                         // checkKind
  };
  static rtBoundsCheckInfo o_emlrtBCI{
      -1,                 // iFirst
      -1,                 // iLast
      23,                 // lineNo
      22,                 // colNo
      "",                 // aName
      "formatSTFTOutput", // fName
      "C:\\Program "
      "Files\\MATLAB\\toolbox\\signal\\signal\\+signal\\+internal\\+"
      "stft\\formatSTFTOutput.m", // pName
      0                           // checkKind
  };
  static rtBoundsCheckInfo p_emlrtBCI{
      -1,                 // iFirst
      -1,                 // iLast
      23,                 // lineNo
      24,                 // colNo
      "",                 // aName
      "formatSTFTOutput", // fName
      "C:\\Program "
      "Files\\MATLAB\\toolbox\\signal\\signal\\+signal\\+internal\\+"
      "stft\\formatSTFTOutput.m", // pName
      0                           // checkKind
  };
  static rtBoundsCheckInfo q_emlrtBCI{
      -1,                 // iFirst
      -1,                 // iLast
      18,                 // lineNo
      22,                 // colNo
      "",                 // aName
      "formatSTFTOutput", // fName
      "C:\\Program "
      "Files\\MATLAB\\toolbox\\signal\\signal\\+signal\\+internal\\+"
      "stft\\formatSTFTOutput.m", // pName
      0                           // checkKind
  };
  static rtBoundsCheckInfo r_emlrtBCI{
      -1,                 // iFirst
      -1,                 // iLast
      18,                 // lineNo
      24,                 // colNo
      "",                 // aName
      "formatSTFTOutput", // fName
      "C:\\Program "
      "Files\\MATLAB\\toolbox\\signal\\signal\\+signal\\+internal\\+"
      "stft\\formatSTFTOutput.m", // pName
      0                           // checkKind
  };
  static rtDoubleCheckInfo b_emlrtDCI{
      14,               // lineNo
      30,               // colNo
      "getSTFTColumns", // fName
      "C:\\Program "
      "Files\\MATLAB\\toolbox\\signal\\signal\\+signal\\+internal\\+"
      "stft\\getSTFTColumns.m", // pName
      4                         // checkKind
  };
  static rtDoubleCheckInfo c_emlrtDCI{
      14,               // lineNo
      30,               // colNo
      "getSTFTColumns", // fName
      "C:\\Program "
      "Files\\MATLAB\\toolbox\\signal\\signal\\+signal\\+internal\\+"
      "stft\\getSTFTColumns.m", // pName
      1                         // checkKind
  };
  static rtDoubleCheckInfo d_emlrtDCI{
      14,               // lineNo
      5,                // colNo
      "getSTFTColumns", // fName
      "C:\\Program "
      "Files\\MATLAB\\toolbox\\signal\\signal\\+signal\\+internal\\+"
      "stft\\getSTFTColumns.m", // pName
      1                         // checkKind
  };
  static rtDoubleCheckInfo e_emlrtDCI{
      23,               // lineNo
      23,               // colNo
      "getSTFTColumns", // fName
      "C:\\Program "
      "Files\\MATLAB\\toolbox\\signal\\signal\\+signal\\+internal\\+"
      "stft\\getSTFTColumns.m", // pName
      1                         // checkKind
  };
  static rtDoubleCheckInfo f_emlrtDCI{
      23,               // lineNo
      42,               // colNo
      "getSTFTColumns", // fName
      "C:\\Program "
      "Files\\MATLAB\\toolbox\\signal\\signal\\+signal\\+internal\\+"
      "stft\\getSTFTColumns.m", // pName
      1                         // checkKind
  };
  static rtDoubleCheckInfo g_emlrtDCI{
      13,           // lineNo
      13,           // colNo
      "centerfreq", // fName
      "C:\\Program "
      "Files\\MATLAB\\toolbox\\signal\\signal\\+signal\\+internal\\+"
      "spectral\\centerfreq.m", // pName
      1                         // checkKind
  };
  static rtDoubleCheckInfo h_emlrtDCI{
      16,           // lineNo
      13,           // colNo
      "centerfreq", // fName
      "C:\\Program "
      "Files\\MATLAB\\toolbox\\signal\\signal\\+signal\\+internal\\+"
      "spectral\\centerfreq.m", // pName
      1                         // checkKind
  };
  static rtDoubleCheckInfo i_emlrtDCI{
      23,                 // lineNo
      24,                 // colNo
      "formatSTFTOutput", // fName
      "C:\\Program "
      "Files\\MATLAB\\toolbox\\signal\\signal\\+signal\\+internal\\+"
      "stft\\formatSTFTOutput.m", // pName
      1                           // checkKind
  };
  static rtDoubleCheckInfo j_emlrtDCI{
      18,                 // lineNo
      24,                 // colNo
      "formatSTFTOutput", // fName
      "C:\\Program "
      "Files\\MATLAB\\toolbox\\signal\\signal\\+signal\\+internal\\+"
      "stft\\formatSTFTOutput.m", // pName
      1                           // checkKind
  };
  static rtEqualityCheckInfo c_emlrtECI{
      -1,               // nDims
      23,               // lineNo
      5,                // colNo
      "getSTFTColumns", // fName
      "C:\\Program "
      "Files\\MATLAB\\toolbox\\signal\\signal\\+signal\\+internal\\+"
      "stft\\getSTFTColumns.m" // pName
  };
  static rtRunTimeErrorInfo kb_emlrtRTEI{
      31,         // lineNo
      "circshift" // fName
  };
  static rtRunTimeErrorInfo lb_emlrtRTEI{
      53,      // lineNo
      "bsxfun" // fName
  };
  static const char b[8]{'c', 'e', 'n', 't', 'e', 'r', 'e', 'd'};
  static const char b_b[8]{'t', 'w', 'o', 's', 'i', 'd', 'e', 'd'};
  array<creal32_T, 2U> buffer;
  array<creal32_T, 2U> c;
  array<creal32_T, 2U> xin;
  array<double, 2U> y;
  array<double, 1U> f;
  double hopSize;
  double nCol;
  float xtmp_re;
  int iv[2];
  int acoef;
  int b_i1;
  int bcoef;
  int csz_idx_0;
  int i;
  int i1;
  int i2;
  int ib;
  hopSize = opts_WindowLength - opts_OverlapLength;
  nCol = std::trunc((opts_DataLength - opts_OverlapLength) / hopSize);
  xin.set_size(static_cast<int>(opts_WindowLength), xin.size(1));
  if (!(nCol >= 0.0)) {
    rtNonNegativeError(nCol, &b_emlrtDCI);
  }
  if (nCol != static_cast<int>(nCol)) {
    rtIntegerError(nCol, &c_emlrtDCI);
  }
  xin.set_size(xin.size(0), static_cast<int>(nCol));
  if (nCol != static_cast<int>(nCol)) {
    rtIntegerError(nCol, &d_emlrtDCI);
  }
  bcoef = static_cast<int>(opts_WindowLength) * static_cast<int>(nCol);
  for (i = 0; i < bcoef; i++) {
    xin[i].re = 0.0F;
    xin[i].im = 0.0F;
  }
  if (nCol - 1.0 < 0.0) {
    y.set_size(y.size(0), 0);
  } else {
    y.set_size(1, static_cast<int>(nCol - 1.0) + 1);
    bcoef = static_cast<int>(nCol - 1.0);
    for (i = 0; i <= bcoef; i++) {
      y[i] = i;
    }
  }
  i = static_cast<int>(nCol);
  for (acoef = 0; acoef < i; acoef++) {
    double d;
    nCol = hopSize * ((static_cast<double>(acoef) + 1.0) - 1.0);
    d = opts_WindowLength + nCol;
    if (nCol + 1.0 > d) {
      i1 = 0;
      b_i1 = 0;
    } else {
      if (nCol + 1.0 != static_cast<int>(std::floor(nCol + 1.0))) {
        rtIntegerError(nCol + 1.0, &e_emlrtDCI);
      }
      if ((static_cast<int>(nCol + 1.0) < 1) ||
          (static_cast<int>(nCol + 1.0) > x.size(0))) {
        rtDynamicBoundsError(static_cast<int>(nCol + 1.0), 1, x.size(0),
                             &g_emlrtBCI);
      }
      i1 = static_cast<int>(nCol + 1.0) - 1;
      if (d != static_cast<int>(std::floor(d))) {
        rtIntegerError(d, &f_emlrtDCI);
      }
      if ((static_cast<int>(d) < 1) || (static_cast<int>(d) > x.size(0))) {
        rtDynamicBoundsError(static_cast<int>(d), 1, x.size(0), &h_emlrtBCI);
      }
      b_i1 = static_cast<int>(d);
    }
    if ((acoef + 1 < 1) || (acoef + 1 > xin.size(1))) {
      rtDynamicBoundsError(acoef + 1, 1, xin.size(1), &f_emlrtBCI);
    }
    bcoef = b_i1 - i1;
    rtSubAssignSizeCheck(xin.size(), 1, &bcoef, 1, &c_emlrtECI);
    for (b_i1 = 0; b_i1 < bcoef; b_i1++) {
      xin[b_i1 + xin.size(0) * acoef] = x[i1 + b_i1];
    }
  }
  y.set_size(1, y.size(1));
  nCol = opts_WindowLength / 2.0;
  bcoef = y.size(1) - 1;
  for (i = 0; i <= bcoef; i++) {
    y[i] = (y[i] * hopSize + nCol) / opts_EffectiveFs;
  }
  if (xin.size(0) == 1) {
    csz_idx_0 = opts_Window.size(0);
  } else if (opts_Window.size(0) == 1) {
    csz_idx_0 = xin.size(0);
  } else if (opts_Window.size(0) == xin.size(0)) {
    csz_idx_0 = opts_Window.size(0);
  } else {
    v_rtErrorWithMessageID(lb_emlrtRTEI.fName, lb_emlrtRTEI.lineNo);
  }
  c.set_size(csz_idx_0, xin.size(1));
  if ((csz_idx_0 != 0) && (xin.size(1) != 0)) {
    csz_idx_0 = (xin.size(1) != 1);
    i = xin.size(1) - 1;
    acoef = (opts_Window.size(0) != 1);
    bcoef = (xin.size(0) != 1);
    for (int k{0}; k <= i; k++) {
      i2 = csz_idx_0 * k;
      i1 = c.size(0) - 1;
      for (ib = 0; ib <= i1; ib++) {
        b_i1 = bcoef * ib;
        xtmp_re = opts_Window[acoef * ib];
        c[ib + c.size(0) * k].re = xtmp_re * xin[b_i1 + xin.size(0) * i2].re;
        c[ib + c.size(0) * k].im = xtmp_re * xin[b_i1 + xin.size(0) * i2].im;
      }
    }
  }
  computeDFT(c, opts_FFTLength, opts_EffectiveFs, S, f);
  csz_idx_0 = memcmp(&opts_FreqRange[0], &b[0], 8);
  if (csz_idx_0 == 0) {
    csz_idx_0 = 0;
  } else {
    csz_idx_0 = memcmp(&opts_FreqRange[0], &b_b[0], 8);
    if (csz_idx_0 == 0) {
      csz_idx_0 = 1;
    } else {
      csz_idx_0 = -1;
    }
  }
  switch (csz_idx_0) {
  case 0: {
    if (signalwavelet::internal::iseven(static_cast<double>(S.size(0)))) {
      nCol = static_cast<double>(S.size(0)) / 2.0 - 1.0;
      i2 = 1;
      if (S.size(0) != 1) {
        i2 = 0;
      }
      if (static_cast<int>(nCol) != nCol) {
        rtErrorWithMessageID("int32", "int32", kb_emlrtRTEI.fName,
                             kb_emlrtRTEI.lineNo);
      }
      if ((S.size(0) != 0) && (S.size(1) != 0) &&
          ((S.size(0) != 1) || (S.size(1) != 1))) {
        int npages;
        int ns;
        boolean_T shiftright;
        if (nCol < 0.0) {
          ns = 1;
          shiftright = false;
        } else {
          ns = static_cast<int>(nCol);
          shiftright = true;
        }
        if (ns > S.size(i2)) {
          ns -= div_s32(ns, S.size(i2)) * S.size(i2);
        }
        if (ns > (S.size(i2) >> 1)) {
          ns = S.size(i2) - ns;
          shiftright = !shiftright;
        }
        csz_idx_0 = S.size(0);
        acoef = S.size(1);
        if (csz_idx_0 >= acoef) {
          acoef = csz_idx_0;
        }
        bcoef = static_cast<int>(std::floor(static_cast<double>(acoef) / 2.0));
        csz_idx_0 = S.size(0);
        acoef = S.size(1);
        if (csz_idx_0 >= acoef) {
          acoef = csz_idx_0;
        }
        buffer.set_size(
            1, static_cast<int>(std::floor(static_cast<double>(acoef) / 2.0)));
        for (i = 0; i < bcoef; i++) {
          buffer[i].re = 0.0F;
          buffer[i].im = 0.0F;
        }
        i = S.size(i2);
        bcoef = S.size(i2);
        ib = 1;
        for (int k{0}; k < i2; k++) {
          ib *= S.size(0);
        }
        npages = 1;
        acoef = i2 + 2;
        for (int k{acoef}; k < 3; k++) {
          npages *= S.size(1);
        }
        acoef = ib * S.size(i2);
        if ((S.size(i2) > 1) && (ns > 0)) {
          if (npages > 2147483646) {
            check_forloop_overflow_error();
          }
          for (int b_i{0}; b_i < npages; b_i++) {
            csz_idx_0 = b_i * acoef;
            if (ib > 2147483646) {
              check_forloop_overflow_error();
            }
            for (i2 = 0; i2 < ib; i2++) {
              b_i1 = csz_idx_0 + i2;
              if (shiftright) {
                for (int k{0}; k < ns; k++) {
                  buffer[k] = S[b_i1 + ((k + i) - ns) * ib];
                }
                i1 = ns + 1;
                for (int k{bcoef}; k >= i1; k--) {
                  S[b_i1 + (k - 1) * ib] = S[b_i1 + ((k - ns) - 1) * ib];
                }
                for (int k{0}; k < ns; k++) {
                  S[b_i1 + k * ib] = buffer[k];
                }
              } else {
                for (int k{0}; k < ns; k++) {
                  buffer[k] = S[b_i1 + k * ib];
                }
                i1 = (i - ns) - 1;
                for (int k{0}; k <= i1; k++) {
                  S[b_i1 + k * ib] = S[b_i1 + (k + ns) * ib];
                }
                for (int k{0}; k < ns; k++) {
                  S[b_i1 + ((k + i) - ns) * ib] = buffer[k];
                }
              }
            }
          }
        }
      }
    } else if (S.size(0) > 1) {
      int npages;
      acoef = S.size(0) / 2 - 1;
      npages = S.size(1) - 1;
      bcoef = S.size(0);
      if ((acoef + 1) << 1 == S.size(0)) {
        i2 = 1;
        if (S.size(1) > 2147483646) {
          check_forloop_overflow_error();
        }
        for (int b_i{0}; b_i <= npages; b_i++) {
          b_i1 = i2;
          i2 += bcoef;
          ib = b_i1 + acoef;
          for (int k{0}; k <= acoef; k++) {
            float xtmp_im;
            csz_idx_0 = (b_i1 + k) - 1;
            xtmp_re = S[csz_idx_0].re;
            xtmp_im = S[csz_idx_0].im;
            i = ib + k;
            S[csz_idx_0] = S[i];
            S[i].re = xtmp_re;
            S[i].im = xtmp_im;
          }
        }
      } else {
        i2 = 1;
        if (S.size(1) > 2147483646) {
          check_forloop_overflow_error();
        }
        for (int b_i{0}; b_i <= npages; b_i++) {
          float xtmp_im;
          b_i1 = i2;
          i2 += bcoef;
          ib = b_i1 + acoef;
          xtmp_re = S[ib].re;
          xtmp_im = S[ib].im;
          for (int k{0}; k <= acoef; k++) {
            i = ib + k;
            i1 = (b_i1 + k) - 1;
            S[i] = S[i1];
            S[i1] = S[i + 1];
          }
          ib = (ib + acoef) + 1;
          S[ib].re = xtmp_re;
          S[ib].im = xtmp_im;
        }
      }
    }
    if (signalwavelet::internal::iseven(static_cast<double>(f.size(0)))) {
      nCol = static_cast<double>(f.size(0)) / 2.0;
      if (nCol != std::floor(nCol)) {
        rtIntegerError(nCol, &g_emlrtDCI);
      }
      if ((static_cast<int>(nCol) < 1) ||
          (static_cast<int>(nCol) > f.size(0))) {
        rtDynamicBoundsError(static_cast<int>(nCol), 1, f.size(0), &m_emlrtBCI);
      }
      nCol = f[static_cast<int>(nCol) - 1];
      bcoef = f.size(0);
      for (i = 0; i < bcoef; i++) {
        f[i] = f[i] - nCol;
      }
    } else {
      nCol = (static_cast<double>(f.size(0)) + 1.0) / 2.0;
      if (nCol != std::floor(nCol)) {
        rtIntegerError(nCol, &h_emlrtDCI);
      }
      if ((static_cast<int>(nCol) < 1) ||
          (static_cast<int>(nCol) > f.size(0))) {
        rtDynamicBoundsError(static_cast<int>(nCol), 1, f.size(0), &n_emlrtBCI);
      }
      nCol = f[static_cast<int>(nCol) - 1];
      bcoef = f.size(0);
      for (i = 0; i < bcoef; i++) {
        f[i] = f[i] - nCol;
      }
    }
  } break;
  case 1:
    break;
  default:
    if (S.size(0) != opts_NumFreqSamples) {
      if (opts_NumFreqSamples < 1.0) {
        bcoef = 0;
      } else {
        if (S.size(0) < 1) {
          rtDynamicBoundsError(1, 1, S.size(0), &q_emlrtBCI);
        }
        if (opts_NumFreqSamples !=
            static_cast<int>(std::floor(opts_NumFreqSamples))) {
          rtIntegerError(opts_NumFreqSamples, &j_emlrtDCI);
        }
        if ((static_cast<int>(opts_NumFreqSamples) < 1) ||
            (static_cast<int>(opts_NumFreqSamples) > S.size(0))) {
          rtDynamicBoundsError(static_cast<int>(opts_NumFreqSamples), 1,
                               S.size(0), &r_emlrtBCI);
        }
        bcoef = static_cast<int>(opts_NumFreqSamples);
      }
      csz_idx_0 = S.size(1) - 1;
      for (i = 0; i <= csz_idx_0; i++) {
        for (i1 = 0; i1 < bcoef; i1++) {
          S[i1 + bcoef * i] = S[i1 + S.size(0) * i];
        }
      }
      S.set_size(bcoef, csz_idx_0 + 1);
    }
    if (f.size(0) != opts_NumFreqSamples) {
      if (opts_NumFreqSamples < 1.0) {
        i = 0;
      } else {
        if (f.size(0) < 1) {
          rtDynamicBoundsError(1, 1, f.size(0), &o_emlrtBCI);
        }
        if (opts_NumFreqSamples !=
            static_cast<int>(std::floor(opts_NumFreqSamples))) {
          rtIntegerError(opts_NumFreqSamples, &i_emlrtDCI);
        }
        if ((static_cast<int>(opts_NumFreqSamples) < 1) ||
            (static_cast<int>(opts_NumFreqSamples) > f.size(0))) {
          rtDynamicBoundsError(static_cast<int>(opts_NumFreqSamples), 1,
                               f.size(0), &p_emlrtBCI);
        }
        i = static_cast<int>(opts_NumFreqSamples);
      }
      iv[0] = 1;
      iv[1] = i;
      internal::indexShapeCheck(f.size(0), iv);
      f.set_size(i);
    }
    break;
  }
  if (S.size(0) < 1) {
    bcoef = 0;
  } else {
    if (f.size(0) < 1) {
      rtDynamicBoundsError(1, 1, f.size(0), &k_emlrtBCI);
    }
    if (S.size(0) > f.size(0)) {
      rtDynamicBoundsError(S.size(0), 1, f.size(0), &l_emlrtBCI);
    }
    bcoef = S.size(0);
  }
  iv[0] = 1;
  iv[1] = bcoef;
  internal::indexShapeCheck(f.size(0), iv);
  F.set_size(bcoef);
  for (i = 0; i < bcoef; i++) {
    F[i] = static_cast<float>(f[i]);
  }
  if (S.size(1) < 1) {
    bcoef = 0;
  } else {
    if (y.size(1) < 1) {
      rtDynamicBoundsError(1, 1, y.size(1), &i_emlrtBCI);
    }
    if (S.size(1) > y.size(1)) {
      rtDynamicBoundsError(S.size(1), 1, y.size(1), &j_emlrtBCI);
    }
    bcoef = S.size(1);
  }
  T.set_size(1, bcoef);
  for (i = 0; i < bcoef; i++) {
    T[i] = static_cast<float>(y[i]);
  }
}

//
// Arguments    : const char *r
//                const char *aFcnName
//                int aLineNum
// Return Type  : void
//
} // namespace coder
static void j_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((outStream << "Expected ") << r) << " to be positive.";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// Arguments    : const long long i
//                const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void rtErrorWithMessageID(const long long i, const char *aFcnName,
                                 int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((outStream << "Input signal length must be greater than or equal to the "
                 "window length, ")
   << i)
      << ".";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// Arguments    : const char *r
//                const char *r1
//                const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void rtErrorWithMessageID(const char *r, const char *r1,
                                 const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((((outStream << "Invalid shift argument: must be a finite, real, integer "
                   "vector with entries between -intmax(\'")
     << r)
    << "\') and intmax(\'")
   << r1)
      << "\').";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void s_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Input signal must have at least 2 samples.";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void t_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream
      << "Input signal must be a real-valued vector, matrix, or timetable when "
         "\'FrequencyRange\' is specified as \'onesided\'.";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void v_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Non-singleton dimensions of the two input arrays must match "
               "each other.";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
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
namespace coder {
void stft(const ::coder::array<creal32_T, 2U> &x, double varargin_1,
          const ::coder::array<double, 1U> &varargin_3, double varargin_5,
          double varargin_7, ::coder::array<creal32_T, 2U> &varargout_1,
          ::coder::array<float, 1U> &varargout_2,
          ::coder::array<float, 1U> &varargout_3)
{
  static rtRunTimeErrorInfo kb_emlrtRTEI{
      386,                // lineNo
      "verifyDataAndTime" // fName
  };
  static rtRunTimeErrorInfo lb_emlrtRTEI{
      14,                // lineNo
      "validatepositive" // fName
  };
  static rtRunTimeErrorInfo mb_emlrtRTEI{
      419,                // lineNo
      "verifyDataAndTime" // fName
  };
  static const char b[8]{'o', 'n', 'e', 's', 'i', 'd', 'e', 'd'};
  static const char freqRange[8]{'c', 'e', 'n', 't', 'e', 'r', 'e', 'd'};
  array<creal32_T, 1U> b_x;
  array<float, 2U> T;
  array<float, 1U> varargout_2_Window;
  double varargout_2_NumFreqSamples;
  int ret;
  boolean_T exitg1;
  boolean_T isOnesided;
  validateattributes(varargin_3);
  validateattributes(static_cast<double>(varargin_3.size(0)));
  validateattributes(varargin_5, static_cast<double>(varargin_3.size(0)));
  b_validateattributes(varargin_7, static_cast<double>(varargin_3.size(0)));
  isOnesided = true;
  ret = 0;
  exitg1 = false;
  while ((!exitg1) && (ret <= x.size(1) - 1)) {
    if ((!std::isinf(x[ret].re)) && (!std::isinf(x[ret].im)) &&
        ((!std::isnan(x[ret].re)) && (!std::isnan(x[ret].im)))) {
      ret++;
    } else {
      isOnesided = false;
      exitg1 = true;
    }
  }
  if (!isOnesided) {
    g_rtErrorWithMessageID("X", cb_emlrtRTEI.fName, cb_emlrtRTEI.lineNo);
  }
  isOnesided = true;
  ret = 0;
  exitg1 = false;
  while ((!exitg1) && (ret <= x.size(1) - 1)) {
    if ((!std::isnan(x[ret].re)) && (!std::isnan(x[ret].im))) {
      ret++;
    } else {
      isOnesided = false;
      exitg1 = true;
    }
  }
  if (!isOnesided) {
    h_rtErrorWithMessageID("X", db_emlrtRTEI.fName, db_emlrtRTEI.lineNo);
  }
  if (x.size(1) == 0) {
    i_rtErrorWithMessageID("X", eb_emlrtRTEI.fName, eb_emlrtRTEI.lineNo);
  }
  if (x.size(1) < 2) {
    s_rtErrorWithMessageID(bb_emlrtRTEI.fName, bb_emlrtRTEI.lineNo);
  }
  ret = memcmp(&freqRange[0], &b[0], 8);
  isOnesided = (ret == 0);
  if (isOnesided) {
    if (signalwavelet::internal::iseven(varargin_7)) {
      varargout_2_NumFreqSamples = varargin_7 / 2.0 + 1.0;
    } else {
      varargout_2_NumFreqSamples = (varargin_7 + 1.0) / 2.0;
    }
  } else {
    varargout_2_NumFreqSamples = varargin_7;
  }
  if (varargin_3.size(0) > x.size(1)) {
    rtErrorWithMessageID(static_cast<long long>(varargin_3.size(0)),
                         kb_emlrtRTEI.fName, kb_emlrtRTEI.lineNo);
  }
  if (isOnesided) {
    t_rtErrorWithMessageID(mb_emlrtRTEI.fName, mb_emlrtRTEI.lineNo);
  }
  varargout_2_Window.set_size(varargin_3.size(0));
  ret = varargin_3.size(0);
  for (int i{0}; i < ret; i++) {
    varargout_2_Window[i] = static_cast<float>(varargin_3[i]);
  }
  if (std::isinf(varargin_1) || std::isnan(varargin_1)) {
    g_rtErrorWithMessageID("sample rate", cb_emlrtRTEI.fName,
                           cb_emlrtRTEI.lineNo);
  }
  if (varargin_1 <= 0.0) {
    j_rtErrorWithMessageID("sample rate", lb_emlrtRTEI.fName,
                           lb_emlrtRTEI.lineNo);
  }
  ret = x.size(1);
  b_x = x.reshape(ret);
  computeSTFT(b_x, static_cast<double>(x.size(1)), varargin_1,
              varargout_2_Window, static_cast<double>(varargin_3.size(0)),
              varargin_5, varargin_7, freqRange, varargout_2_NumFreqSamples,
              varargout_1, varargout_2, T);
  varargout_3.set_size(T.size(1));
  ret = T.size(1);
  for (int i{0}; i < ret; i++) {
    varargout_3[i] = T[i];
  }
}

//
// Arguments    : const int x_size[2]
//                const double varargin_3_data[]
//                int varargin_3_size
//                double varargin_5
//                double varargin_7
// Return Type  : void
//
void stft(const int x_size[2], const double varargin_3_data[],
          int varargin_3_size, double varargin_5, double varargin_7)
{
  array<double, 1U> b_varargin_3_data;
  b_varargin_3_data.set((double *)&varargin_3_data[0], varargin_3_size);
  validateattributes(b_varargin_3_data);
  validateattributes(static_cast<double>(varargin_3_size));
  validateattributes(varargin_5, static_cast<double>(varargin_3_size));
  b_validateattributes(varargin_7, static_cast<double>(varargin_3_size));
  if (x_size[0] == 0) {
    i_rtErrorWithMessageID("X", eb_emlrtRTEI.fName, eb_emlrtRTEI.lineNo);
  }
  s_rtErrorWithMessageID(bb_emlrtRTEI.fName, bb_emlrtRTEI.lineNo);
}

} // namespace coder

//
// File trailer for stft.cpp
//
// [EOF]
//
