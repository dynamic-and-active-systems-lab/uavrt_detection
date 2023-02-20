//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: computeDFT.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 14:31:55
//

// Include Files
#include "computeDFT.h"
#include "FFTImplementationCallback.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include "omp.h"
#include <cfloat>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string.h>
#include <string>

// Function Declarations
static double rt_remd_snf(double u0, double u1);

static void w_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
static double rt_remd_snf(double u0, double u1)
{
  double y;
  if (std::isnan(u0) || std::isnan(u1) || std::isinf(u0)) {
    y = rtNaN;
  } else if (std::isinf(u1)) {
    y = u0;
  } else if ((u1 != 0.0) && (u1 != std::trunc(u1))) {
    double q;
    q = std::abs(u0 / u1);
    if (!(std::abs(q - std::floor(q + 0.5)) > DBL_EPSILON * q)) {
      y = 0.0 * u0;
    } else {
      y = std::fmod(u0, u1);
    }
  } else {
    y = std::fmod(u0, u1);
  }
  return y;
}

//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void w_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream
      << "The dimension to operate along was selected automatically, is "
         "variable-length, and has length 1 at run time. This is not support"
         "ed. Manually select the dimension to operate along by supplying the "
         "DIM argument.";
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
  static rtBoundsCheckInfo f_emlrtBCI{
      -1,                 // iFirst
      -1,                 // iLast
      84,                 // lineNo
      38,                 // colNo
      "",                 // aName
      "computeDFTviaFFT", // fName
      "C:\\Program "
      "Files\\MATLAB\\toolbox\\signal\\signal\\private\\computeDFT.m", // pName
      0 // checkKind
  };
  static rtBoundsCheckInfo g_emlrtBCI{
      -1,                                                            // iFirst
      -1,                                                            // iLast
      35,                                                            // lineNo
      7,                                                             // colNo
      "",                                                            // aName
      "datawrap",                                                    // fName
      "C:\\Program Files\\MATLAB\\toolbox\\signal\\eml\\datawrap.m", // pName
      0 // checkKind
  };
  static rtBoundsCheckInfo h_emlrtBCI{
      -1,                                                            // iFirst
      -1,                                                            // iLast
      35,                                                            // lineNo
      14,                                                            // colNo
      "",                                                            // aName
      "datawrap",                                                    // fName
      "C:\\Program Files\\MATLAB\\toolbox\\signal\\eml\\datawrap.m", // pName
      0 // checkKind
  };
  static rtBoundsCheckInfo i_emlrtBCI{
      -1,                                                            // iFirst
      -1,                                                            // iLast
      39,                                                            // lineNo
      7,                                                             // colNo
      "",                                                            // aName
      "datawrap",                                                    // fName
      "C:\\Program Files\\MATLAB\\toolbox\\signal\\eml\\datawrap.m", // pName
      0 // checkKind
  };
  static rtBoundsCheckInfo j_emlrtBCI{
      -1,                                                            // iFirst
      -1,                                                            // iLast
      45,                                                            // lineNo
      11,                                                            // colNo
      "",                                                            // aName
      "datawrap",                                                    // fName
      "C:\\Program Files\\MATLAB\\toolbox\\signal\\eml\\datawrap.m", // pName
      0 // checkKind
  };
  static rtBoundsCheckInfo k_emlrtBCI{
      -1,                                                            // iFirst
      -1,                                                            // iLast
      45,                                                            // lineNo
      18,                                                            // colNo
      "",                                                            // aName
      "datawrap",                                                    // fName
      "C:\\Program Files\\MATLAB\\toolbox\\signal\\eml\\datawrap.m", // pName
      0 // checkKind
  };
  static rtBoundsCheckInfo l_emlrtBCI{
      -1,                                                            // iFirst
      -1,                                                            // iLast
      45,                                                            // lineNo
      25,                                                            // colNo
      "",                                                            // aName
      "datawrap",                                                    // fName
      "C:\\Program Files\\MATLAB\\toolbox\\signal\\eml\\datawrap.m", // pName
      0 // checkKind
  };
  static rtBoundsCheckInfo m_emlrtBCI{
      -1,                 // iFirst
      -1,                 // iLast
      85,                 // lineNo
      14,                 // colNo
      "",                 // aName
      "computeDFTviaFFT", // fName
      "C:\\Program "
      "Files\\MATLAB\\toolbox\\signal\\signal\\private\\computeDFT.m", // pName
      0 // checkKind
  };
  static rtBoundsCheckInfo n_emlrtBCI{
      -1,              // iFirst
      -1,              // iLast
      74,              // lineNo
      8,               // colNo
      "",              // aName
      "frequencygrid", // fName
      "C:\\Program Files\\MATLAB\\toolbox\\shared\\siglib\\psdfreqvec.m", // pName
      0 // checkKind
  };
  static rtBoundsCheckInfo o_emlrtBCI{
      -1,              // iFirst
      -1,              // iLast
      75,              // lineNo
      8,               // colNo
      "",              // aName
      "frequencygrid", // fName
      "C:\\Program Files\\MATLAB\\toolbox\\shared\\siglib\\psdfreqvec.m", // pName
      0 // checkKind
  };
  static rtBoundsCheckInfo p_emlrtBCI{
      -1,              // iFirst
      -1,              // iLast
      80,              // lineNo
      4,               // colNo
      "",              // aName
      "frequencygrid", // fName
      "C:\\Program Files\\MATLAB\\toolbox\\shared\\siglib\\psdfreqvec.m", // pName
      0 // checkKind
  };
  static rtBoundsCheckInfo q_emlrtBCI{
      -1,              // iFirst
      -1,              // iLast
      78,              // lineNo
      8,               // colNo
      "",              // aName
      "frequencygrid", // fName
      "C:\\Program Files\\MATLAB\\toolbox\\shared\\siglib\\psdfreqvec.m", // pName
      0 // checkKind
  };
  static rtDoubleCheckInfo b_emlrtDCI{
      81,                 // lineNo
      12,                 // colNo
      "computeDFTviaFFT", // fName
      "C:\\Program "
      "Files\\MATLAB\\toolbox\\signal\\signal\\private\\computeDFT.m", // pName
      4 // checkKind
  };
  static rtDoubleCheckInfo c_emlrtDCI{
      81,                 // lineNo
      12,                 // colNo
      "computeDFTviaFFT", // fName
      "C:\\Program "
      "Files\\MATLAB\\toolbox\\signal\\signal\\private\\computeDFT.m", // pName
      1 // checkKind
  };
  static rtDoubleCheckInfo d_emlrtDCI{
      81,                 // lineNo
      1,                  // colNo
      "computeDFTviaFFT", // fName
      "C:\\Program "
      "Files\\MATLAB\\toolbox\\signal\\signal\\private\\computeDFT.m", // pName
      1 // checkKind
  };
  static rtDoubleCheckInfo e_emlrtDCI{
      74,              // lineNo
      8,               // colNo
      "frequencygrid", // fName
      "C:\\Program Files\\MATLAB\\toolbox\\shared\\siglib\\psdfreqvec.m", // pName
      1 // checkKind
  };
  static rtDoubleCheckInfo f_emlrtDCI{
      78,              // lineNo
      8,               // colNo
      "frequencygrid", // fName
      "C:\\Program Files\\MATLAB\\toolbox\\shared\\siglib\\psdfreqvec.m", // pName
      1 // checkKind
  };
  static rtEqualityCheckInfo c_emlrtECI{
      -1,                 // nDims
      85,                 // lineNo
      9,                  // colNo
      "computeDFTviaFFT", // fName
      "C:\\Program "
      "Files\\MATLAB\\toolbox\\signal\\signal\\private\\computeDFT.m" // pName
  };
  static rtRunTimeErrorInfo kb_emlrtRTEI{
      12,        // lineNo
      "datawrap" // fName
  };
  static rtRunTimeErrorInfo lb_emlrtRTEI{
      37,   // lineNo
      "fft" // fName
  };
  static rtRunTimeErrorInfo mb_emlrtRTEI{
      417,                                       // lineNo
      "FFTImplementationCallback/get_algo_sizes" // fName
  };
  array<creal32_T, 2U> wrappedData;
  array<creal32_T, 2U> xw;
  array<creal32_T, 1U> x;
  array<double, 2U> w1;
  array<float, 2U> costab;
  array<float, 2U> costab1q;
  array<float, 2U> sintab;
  array<float, 2U> sintabinv;
  double Fs1;
  double Nyq;
  double freq_res;
  double half_res;
  int b_remainder;
  int i;
  int i1;
  int k;
  int loop_ub_tmp;
  int n;
  int nFullPasses;
  int offset;
  if (!(nfft >= 0.0)) {
    rtNonNegativeError(nfft, &b_emlrtDCI);
  }
  i = static_cast<int>(std::floor(nfft));
  if (nfft != i) {
    rtIntegerError(nfft, &c_emlrtDCI);
  }
  loop_ub_tmp = static_cast<int>(nfft);
  xw.set_size(loop_ub_tmp, xin.size(1));
  if (loop_ub_tmp != i) {
    rtIntegerError(nfft, &d_emlrtDCI);
  }
  offset = loop_ub_tmp * xin.size(1);
  for (i = 0; i < offset; i++) {
    xw[i].re = 0.0F;
    xw[i].im = 0.0F;
  }
  if (xin.size(0) > loop_ub_tmp) {
    i = xin.size(1);
    for (int j{0}; j < i; j++) {
      if (j + 1 > xin.size(1)) {
        rtDynamicBoundsError(j + 1, 1, xin.size(1), &f_emlrtBCI);
      }
      offset = xin.size(0);
      x.set_size(xin.size(0));
      for (i1 = 0; i1 < offset; i1++) {
        x[i1] = xin[i1 + xin.size(0) * j];
      }
      if (!(nfft >= 1.0)) {
        c_rtErrorWithMessageID(1, kb_emlrtRTEI.fName, kb_emlrtRTEI.lineNo);
      }
      if (xin.size(0) == 1) {
        wrappedData.set_size(1, loop_ub_tmp);
        for (i1 = 0; i1 < loop_ub_tmp; i1++) {
          wrappedData[i1].re = 0.0F;
          wrappedData[i1].im = 0.0F;
        }
      } else {
        wrappedData.set_size(loop_ub_tmp, 1);
        for (i1 = 0; i1 < loop_ub_tmp; i1++) {
          wrappedData[i1].re = 0.0F;
          wrappedData[i1].im = 0.0F;
        }
      }
      nFullPasses = div_s32(xin.size(0), loop_ub_tmp);
      offset = nFullPasses * loop_ub_tmp;
      b_remainder = xin.size(0) - offset;
      if (b_remainder > 2147483646) {
        check_forloop_overflow_error();
      }
      for (k = 0; k < b_remainder; k++) {
        i1 = wrappedData.size(0) * wrappedData.size(1);
        if ((k + 1 < 1) || (k + 1 > i1)) {
          rtDynamicBoundsError(k + 1, 1, i1, &g_emlrtBCI);
        }
        i1 = (offset + k) + 1;
        if ((i1 < 1) || (i1 > xin.size(0))) {
          rtDynamicBoundsError(i1, 1, xin.size(0), &h_emlrtBCI);
        }
        wrappedData[k].re = x[i1 - 1].re;
        n = wrappedData.size(0) * wrappedData.size(1);
        if (k + 1 > n) {
          rtDynamicBoundsError(k + 1, 1, n, &g_emlrtBCI);
        }
        if (i1 > xin.size(0)) {
          rtDynamicBoundsError(i1, 1, xin.size(0), &h_emlrtBCI);
        }
        wrappedData[k].im = x[i1 - 1].im;
      }
      i1 = b_remainder + 1;
      for (k = i1; k <= loop_ub_tmp; k++) {
        n = wrappedData.size(0) * wrappedData.size(1);
        if ((k < 1) || (k > n)) {
          rtDynamicBoundsError(k, 1, n, &i_emlrtBCI);
        }
        wrappedData[k - 1].re = 0.0F;
        n = wrappedData.size(0) * wrappedData.size(1);
        if (k > n) {
          rtDynamicBoundsError(k, 1, n, &i_emlrtBCI);
        }
        wrappedData[k - 1].im = 0.0F;
      }
      if (nFullPasses > 2147483646) {
        check_forloop_overflow_error();
      }
      for (b_remainder = 0; b_remainder < nFullPasses; b_remainder++) {
        offset = b_remainder * loop_ub_tmp;
        for (k = 0; k < loop_ub_tmp; k++) {
          i1 = wrappedData.size(0) * wrappedData.size(1);
          if (k + 1 > i1) {
            rtDynamicBoundsError(k + 1, 1, i1, &j_emlrtBCI);
          }
          i1 = wrappedData.size(0) * wrappedData.size(1);
          if (k + 1 > i1) {
            rtDynamicBoundsError(k + 1, 1, i1, &k_emlrtBCI);
          }
          i1 = (offset + k) + 1;
          if ((i1 < 1) || (i1 > xin.size(0))) {
            rtDynamicBoundsError(i1, 1, xin.size(0), &l_emlrtBCI);
          }
          wrappedData[k].re = wrappedData[k].re + x[i1 - 1].re;
          n = wrappedData.size(0) * wrappedData.size(1);
          if (k + 1 > n) {
            rtDynamicBoundsError(k + 1, 1, n, &j_emlrtBCI);
          }
          if (i1 > xin.size(0)) {
            rtDynamicBoundsError(i1, 1, xin.size(0), &l_emlrtBCI);
          }
          n = wrappedData.size(0) * wrappedData.size(1);
          if (k + 1 > n) {
            rtDynamicBoundsError(k + 1, 1, n, &k_emlrtBCI);
          }
          wrappedData[k].im = wrappedData[k].im + x[i1 - 1].im;
        }
      }
      if (j + 1 > xw.size(1)) {
        rtDynamicBoundsError(j + 1, 1, xw.size(1), &m_emlrtBCI);
      }
      offset = wrappedData.size(0) * wrappedData.size(1);
      rtSubAssignSizeCheck(xw.size(), 1, &offset, 1, &c_emlrtECI);
      offset = wrappedData.size(0) * wrappedData.size(1);
      for (i1 = 0; i1 < offset; i1++) {
        xw[i1 + xw.size(0) * j] = wrappedData[i1];
      }
    }
  } else {
    xw.set_size(xin.size(0), xin.size(1));
    offset = xin.size(0) * xin.size(1);
    for (i = 0; i < offset; i++) {
      xw[i] = xin[i];
    }
  }
  if (xw.size(0) == 1) {
    w_rtErrorWithMessageID(lb_emlrtRTEI.fName, lb_emlrtRTEI.lineNo);
  }
  if ((xw.size(0) == 0) || (xw.size(1) == 0) || (nfft == 0.0)) {
    Xx.set_size(loop_ub_tmp, xw.size(1));
    offset = loop_ub_tmp * xw.size(1);
    for (i = 0; i < offset; i++) {
      Xx[i].re = 0.0F;
      Xx[i].im = 0.0F;
    }
  } else {
    float e;
    boolean_T useRadix2;
    useRadix2 = ((loop_ub_tmp & (loop_ub_tmp - 1)) == 0);
    nFullPasses = 1;
    if (useRadix2) {
      offset = loop_ub_tmp;
    } else {
      n = (loop_ub_tmp + loop_ub_tmp) - 1;
      offset = 31;
      if (n <= 1) {
        offset = 0;
      } else {
        boolean_T exitg1;
        b_remainder = 0;
        exitg1 = false;
        while ((!exitg1) && (offset - b_remainder > 1)) {
          k = (b_remainder + offset) >> 1;
          nFullPasses = 1 << k;
          if (nFullPasses == n) {
            offset = k;
            exitg1 = true;
          } else if (nFullPasses > n) {
            offset = k;
          } else {
            b_remainder = k;
          }
        }
      }
      nFullPasses = 1 << offset;
      offset = loop_ub_tmp << 2;
      if (offset < 1) {
        offset = 1;
      }
      if (nFullPasses > offset) {
        j_rtErrorWithMessageID(mb_emlrtRTEI.fName, mb_emlrtRTEI.lineNo);
      }
      offset = nFullPasses;
    }
    e = 6.28318548F / static_cast<float>(offset);
    n = offset / 2 / 2;
    costab1q.set_size(1, n + 1);
    costab1q[0] = 1.0F;
    offset = n / 2 - 1;
    for (k = 0; k <= offset; k++) {
      costab1q[k + 1] = std::cos(e * static_cast<float>(k + 1));
    }
    i = offset + 2;
    i1 = n - 1;
    for (k = i; k <= i1; k++) {
      costab1q[k] = std::sin(e * static_cast<float>(n - k));
    }
    costab1q[n] = 0.0F;
    if (!useRadix2) {
      n = costab1q.size(1) - 1;
      offset = (costab1q.size(1) - 1) << 1;
      costab.set_size(1, offset + 1);
      sintab.set_size(1, offset + 1);
      costab[0] = 1.0F;
      sintab[0] = 0.0F;
      sintabinv.set_size(1, offset + 1);
      for (k = 0; k < n; k++) {
        sintabinv[k + 1] = costab1q[(n - k) - 1];
      }
      i = costab1q.size(1);
      for (k = i; k <= offset; k++) {
        sintabinv[k] = costab1q[k - n];
      }
      for (k = 0; k < n; k++) {
        costab[k + 1] = costab1q[k + 1];
        sintab[k + 1] = -costab1q[(n - k) - 1];
      }
      i = costab1q.size(1);
      for (k = i; k <= offset; k++) {
        costab[k] = -costab1q[offset - k];
        sintab[k] = -costab1q[k - n];
      }
    } else {
      n = costab1q.size(1) - 1;
      offset = (costab1q.size(1) - 1) << 1;
      costab.set_size(1, offset + 1);
      sintab.set_size(1, offset + 1);
      costab[0] = 1.0F;
      sintab[0] = 0.0F;
      for (k = 0; k < n; k++) {
        costab[k + 1] = costab1q[k + 1];
        sintab[k + 1] = -costab1q[(n - k) - 1];
      }
      i = costab1q.size(1);
      for (k = i; k <= offset; k++) {
        costab[k] = -costab1q[offset - k];
        sintab[k] = -costab1q[k - n];
      }
      sintabinv.set_size(1, 0);
    }
    if (useRadix2) {
      internal::fft::FFTImplementationCallback::r2br_r2dit_trig(
          xw, static_cast<int>(nfft), costab, sintab, Xx);
    } else {
      internal::fft::FFTImplementationCallback::dobluesteinfft(
          xw, nFullPasses, static_cast<int>(nfft), costab, sintab, sintabinv,
          Xx);
    }
  }
  if (std::isnan(varargin_1)) {
    Fs1 = 6.2831853071795862;
  } else {
    Fs1 = varargin_1;
  }
  freq_res = Fs1 / nfft;
  if (nfft - 1.0 < 0.0) {
    w1.set_size(w1.size(0), 0);
  } else {
    w1.set_size(1, loop_ub_tmp);
    offset = static_cast<int>(nfft) - 1;
    for (i = 0; i <= offset; i++) {
      w1[i] = i;
    }
  }
  w1.set_size(1, w1.size(1));
  offset = w1.size(1) - 1;
  for (i = 0; i <= offset; i++) {
    w1[i] = freq_res * w1[i];
  }
  Nyq = Fs1 / 2.0;
  half_res = freq_res / 2.0;
  if (rt_remd_snf(nfft, 2.0) != 0.0) {
    double halfNPTS;
    halfNPTS = (nfft + 1.0) / 2.0;
    if (halfNPTS != std::floor(halfNPTS)) {
      rtIntegerError(halfNPTS, &e_emlrtDCI);
    }
    if ((static_cast<int>(halfNPTS) < 1) ||
        (static_cast<int>(halfNPTS) > w1.size(1))) {
      rtDynamicBoundsError(static_cast<int>(halfNPTS), 1, w1.size(1),
                           &n_emlrtBCI);
    }
    w1[static_cast<int>(halfNPTS) - 1] = Nyq - half_res;
    if (static_cast<int>(halfNPTS) + 1 > w1.size(1)) {
      rtDynamicBoundsError(static_cast<int>(halfNPTS) + 1, 1, w1.size(1),
                           &o_emlrtBCI);
    }
    w1[static_cast<int>(halfNPTS)] = Nyq + half_res;
  } else {
    half_res = nfft / 2.0 + 1.0;
    if (half_res != std::floor(half_res)) {
      rtIntegerError(half_res, &f_emlrtDCI);
    }
    if (static_cast<int>(half_res) > w1.size(1)) {
      rtDynamicBoundsError(static_cast<int>(half_res), 1, w1.size(1),
                           &q_emlrtBCI);
    }
    w1[static_cast<int>(half_res) - 1] = Nyq;
  }
  if ((nfft < 1.0) || (loop_ub_tmp > w1.size(1))) {
    rtDynamicBoundsError(static_cast<int>(nfft), 1, w1.size(1), &p_emlrtBCI);
  }
  w1[static_cast<int>(nfft) - 1] = Fs1 - freq_res;
  f.set_size(w1.size(1));
  offset = w1.size(1);
  for (i = 0; i < offset; i++) {
    f[i] = w1[i];
  }
}

} // namespace coder

//
// File trailer for computeDFT.cpp
//
// [EOF]
//
