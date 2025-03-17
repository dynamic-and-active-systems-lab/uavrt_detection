//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: formatSTFTOutput.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "formatSTFTOutput.h"
#include "eml_int_forloop_overflow_check.h"
#include "iseven.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include "omp.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>

// Variable Definitions
static rtRunTimeErrorInfo nc_emlrtRTEI{
    38,         // lineNo
    "circshift" // fName
};

static rtBoundsCheckInfo x_emlrtBCI{
    16,          // lineNo
    "",          // aName
    "centerfreq" // fName
};

static rtDoubleCheckInfo n_emlrtDCI{
    16,          // lineNo
    "centerfreq" // fName
};

static rtBoundsCheckInfo y_emlrtBCI{
    13,          // lineNo
    "",          // aName
    "centerfreq" // fName
};

static rtDoubleCheckInfo o_emlrtDCI{
    13,          // lineNo
    "centerfreq" // fName
};

// Function Declarations
static void rtErrorWithMessageID(const char *r, const char *r1,
                                 const char *aFcnName, int aLineNum);

// Function Definitions
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
// Arguments    : array<creal32_T, 2U> &S
//                const array<double, 1U> &F
//                array<double, 1U> &Fout
// Return Type  : void
//
namespace coder {
namespace b_signal {
namespace internal {
namespace stft {
void formatSTFTOutput(array<creal32_T, 2U> &S, const array<double, 1U> &F,
                      array<double, 1U> &Fout)
{
  array<creal32_T, 2U> buffer;
  double p;
  int b_i;
  int vlend2;
  if (signalwavelet::internal::iseven(static_cast<double>(S.size(0)))) {
    int vspread;
    p = static_cast<double>(S.size(0)) / 2.0 - 1.0;
    vspread = 1;
    if (S.size(0) != 1) {
      vspread = 0;
    }
    if (static_cast<int>(p) != p) {
      rtErrorWithMessageID("int32", "int32", nc_emlrtRTEI.fName,
                           nc_emlrtRTEI.lineNo);
    }
    if ((S.size(0) != 0) && (S.size(1) != 0) &&
        ((S.size(0) != 1) || (S.size(1) != 1))) {
      int b_i1;
      int i2;
      int ib;
      int npages;
      int xtmp_re_tmp;
      boolean_T shiftright;
      if (p < 0.0) {
        ib = 1;
        shiftright = false;
      } else {
        ib = static_cast<int>(p);
        shiftright = true;
      }
      b_i = S.size(vspread);
      if (b_i <= 1) {
        ib = 0;
      } else {
        if (ib > b_i) {
          ib -= b_i * static_cast<int>(static_cast<unsigned int>(ib) /
                                       static_cast<unsigned int>(b_i));
        }
        if (ib > (b_i >> 1)) {
          ib = b_i - ib;
          shiftright = !shiftright;
        }
      }
      if ((S.size(0) == 0) || (S.size(1) == 0)) {
        xtmp_re_tmp = 0;
      } else {
        vlend2 = S.size(0);
        xtmp_re_tmp = S.size(1);
        if (vlend2 >= xtmp_re_tmp) {
          xtmp_re_tmp = vlend2;
        }
      }
      vlend2 = xtmp_re_tmp / 2;
      buffer.set_size(1, vlend2);
      for (b_i1 = 0; b_i1 < vlend2; b_i1++) {
        buffer[b_i1].re = 0.0F;
        buffer[b_i1].im = 0.0F;
      }
      i2 = 1;
      for (int k{0}; k < vspread; k++) {
        i2 *= S.size(0);
      }
      npages = 1;
      vlend2 = vspread + 2;
      for (int k{vlend2}; k < 3; k++) {
        npages *= S.size(1);
      }
      xtmp_re_tmp = i2 * b_i;
      if ((b_i > 1) && (ib > 0)) {
        if (npages > 2147483646) {
          check_forloop_overflow_error();
        }
        for (int i{0}; i < npages; i++) {
          vlend2 = i * xtmp_re_tmp;
          if (i2 > 2147483646) {
            check_forloop_overflow_error();
          }
          for (vspread = 0; vspread < i2; vspread++) {
            int i1;
            i1 = vlend2 + vspread;
            if (shiftright) {
              for (int k{0}; k < ib; k++) {
                buffer[k] = S[i1 + ((k + b_i) - ib) * i2];
              }
              b_i1 = ib + 1;
              for (int k{b_i}; k >= b_i1; k--) {
                S[i1 + (k - 1) * i2] = S[i1 + ((k - ib) - 1) * i2];
              }
              for (int k{0}; k < ib; k++) {
                S[i1 + k * i2] = buffer[k];
              }
            } else {
              for (int k{0}; k < ib; k++) {
                buffer[k] = S[i1 + k * i2];
              }
              b_i1 = b_i - ib;
              for (int k{0}; k < b_i1; k++) {
                S[i1 + k * i2] = S[i1 + (k + ib) * i2];
              }
              for (int k{0}; k < ib; k++) {
                S[i1 + ((k + b_i) - ib) * i2] = buffer[k];
              }
            }
          }
        }
      }
    }
  } else if (S.size(0) > 1) {
    int npages;
    int vspread;
    vlend2 = static_cast<int>(static_cast<unsigned int>(S.size(0)) >> 1) - 1;
    npages = S.size(1);
    vspread = S.size(0);
    if ((vlend2 + 1) << 1 == S.size(0)) {
      int i2;
      i2 = 1;
      if (S.size(1) > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int i{0}; i < npages; i++) {
        int i1;
        int ib;
        i1 = i2;
        i2 += vspread;
        ib = i1 + vlend2;
        for (int k{0}; k <= vlend2; k++) {
          float xtmp_im;
          float xtmp_re;
          int xtmp_re_tmp;
          xtmp_re_tmp = (i1 + k) - 1;
          xtmp_re = S[xtmp_re_tmp].re;
          xtmp_im = S[xtmp_re_tmp].im;
          b_i = ib + k;
          S[xtmp_re_tmp] = S[b_i];
          S[b_i].re = xtmp_re;
          S[b_i].im = xtmp_im;
        }
      }
    } else {
      int i2;
      i2 = 1;
      if (S.size(1) > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int i{0}; i < npages; i++) {
        float xtmp_im;
        float xtmp_re;
        int i1;
        int ib;
        i1 = i2;
        i2 += vspread;
        ib = i1 + vlend2;
        xtmp_re = S[ib].re;
        xtmp_im = S[ib].im;
        for (int k{0}; k <= vlend2; k++) {
          int b_i1;
          b_i = ib + k;
          b_i1 = (i1 + k) - 1;
          S[b_i] = S[b_i1];
          S[b_i1] = S[b_i + 1];
        }
        ib = (ib + vlend2) + 1;
        S[ib].re = xtmp_re;
        S[ib].im = xtmp_im;
      }
    }
  }
  if (signalwavelet::internal::iseven(static_cast<double>(F.size(0)))) {
    vlend2 = F.size(0);
    p = static_cast<double>(F.size(0)) / 2.0;
    if (p != std::floor(p)) {
      rtIntegerError(p, o_emlrtDCI);
    }
    if ((static_cast<int>(p) < 1) || (static_cast<int>(p) > F.size(0))) {
      rtDynamicBoundsError(static_cast<int>(p), 1, F.size(0), y_emlrtBCI);
    }
    p = F[static_cast<int>(p) - 1];
    Fout.set_size(F.size(0));
    for (b_i = 0; b_i < vlend2; b_i++) {
      Fout[b_i] = F[b_i] - p;
    }
  } else {
    vlend2 = F.size(0);
    p = (static_cast<double>(F.size(0)) + 1.0) / 2.0;
    if (p != std::floor(p)) {
      rtIntegerError(p, n_emlrtDCI);
    }
    if ((static_cast<int>(p) < 1) || (static_cast<int>(p) > F.size(0))) {
      rtDynamicBoundsError(static_cast<int>(p), 1, F.size(0), x_emlrtBCI);
    }
    p = F[static_cast<int>(p) - 1];
    Fout.set_size(F.size(0));
    for (b_i = 0; b_i < vlend2; b_i++) {
      Fout[b_i] = F[b_i] - p;
    }
  }
}

//
// Arguments    : array<creal_T, 3U> &S
//                const array<double, 1U> &F
//                array<double, 1U> &Fout
// Return Type  : void
//
void formatSTFTOutput(array<creal_T, 3U> &S, const array<double, 1U> &F,
                      array<double, 1U> &Fout)
{
  array<creal_T, 2U> buffer;
  double xtmp_re;
  int b_i;
  int lowerDim;
  if (signalwavelet::internal::iseven(static_cast<double>(S.size(0)))) {
    int vlend2;
    xtmp_re = static_cast<double>(S.size(0)) / 2.0 - 1.0;
    vlend2 = 1;
    if (S.size(0) != 1) {
      vlend2 = 0;
    } else if ((S.size(1) == 1) && (S.size(2) != 1)) {
      vlend2 = 2;
    }
    if (static_cast<int>(xtmp_re) != xtmp_re) {
      rtErrorWithMessageID("int32", "int32", nc_emlrtRTEI.fName,
                           nc_emlrtRTEI.lineNo);
    }
    if ((S.size(0) != 0) && (S.size(1) != 0) && (S.size(2) != 0) &&
        ((S.size(0) != 1) || (S.size(1) != 1) || (S.size(2) != 1))) {
      int b_i1;
      int ib;
      int npages;
      int vspread;
      boolean_T shiftright;
      if (xtmp_re < 0.0) {
        ib = 1;
        shiftright = false;
      } else {
        ib = static_cast<int>(xtmp_re);
        shiftright = true;
      }
      b_i = S.size(vlend2);
      if (b_i <= 1) {
        ib = 0;
      } else {
        if (ib > b_i) {
          ib -= b_i * static_cast<int>(static_cast<unsigned int>(ib) /
                                       static_cast<unsigned int>(b_i));
        }
        if (ib > (b_i >> 1)) {
          ib = b_i - ib;
          shiftright = !shiftright;
        }
      }
      lowerDim = S.size(0);
      if ((S.size(0) > 0) && ((S.size(1) == 0) || (S.size(1) > S.size(0)))) {
        lowerDim = S.size(1);
      }
      if ((lowerDim > 0) && ((S.size(2) == 0) || (S.size(2) > lowerDim))) {
        lowerDim = S.size(2);
      }
      lowerDim /= 2;
      buffer.set_size(1, lowerDim);
      for (b_i1 = 0; b_i1 < lowerDim; b_i1++) {
        buffer[b_i1].re = 0.0;
        buffer[b_i1].im = 0.0;
      }
      vspread = 1;
      for (int k{0}; k < vlend2; k++) {
        vspread *= S.size(k);
      }
      npages = 1;
      lowerDim = vlend2 + 2;
      for (int k{lowerDim}; k < 4; k++) {
        npages *= S.size(k - 1);
      }
      lowerDim = vspread * b_i;
      if ((b_i > 1) && (ib > 0)) {
        if (npages > 2147483646) {
          check_forloop_overflow_error();
        }
        for (int i{0}; i < npages; i++) {
          vlend2 = i * lowerDim;
          if (vspread > 2147483646) {
            check_forloop_overflow_error();
          }
          for (int i2{0}; i2 < vspread; i2++) {
            int i1;
            i1 = vlend2 + i2;
            if (shiftright) {
              for (int k{0}; k < ib; k++) {
                buffer[k] = S[i1 + ((k + b_i) - ib) * vspread];
              }
              b_i1 = ib + 1;
              for (int k{b_i}; k >= b_i1; k--) {
                S[i1 + (k - 1) * vspread] = S[i1 + ((k - ib) - 1) * vspread];
              }
              for (int k{0}; k < ib; k++) {
                S[i1 + k * vspread] = buffer[k];
              }
            } else {
              for (int k{0}; k < ib; k++) {
                buffer[k] = S[i1 + k * vspread];
              }
              b_i1 = b_i - ib;
              for (int k{0}; k < b_i1; k++) {
                S[i1 + k * vspread] = S[i1 + (k + ib) * vspread];
              }
              for (int k{0}; k < ib; k++) {
                S[i1 + ((k + b_i) - ib) * vspread] = buffer[k];
              }
            }
          }
        }
      }
    }
  } else if (S.size(0) > 1) {
    int npages;
    int vlend2;
    int vspread;
    vlend2 = static_cast<int>(static_cast<unsigned int>(S.size(0)) >> 1) - 1;
    npages = S.size(1) * S.size(2);
    vspread = S.size(0);
    if ((vlend2 + 1) << 1 == S.size(0)) {
      int i2;
      i2 = 1;
      if (npages > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int i{0}; i < npages; i++) {
        int i1;
        int ib;
        i1 = i2;
        i2 += vspread;
        ib = i1 + vlend2;
        for (int k{0}; k <= vlend2; k++) {
          double xtmp_im;
          lowerDim = (i1 + k) - 1;
          xtmp_re = S[lowerDim].re;
          xtmp_im = S[lowerDim].im;
          b_i = ib + k;
          S[lowerDim] = S[b_i];
          S[b_i].re = xtmp_re;
          S[b_i].im = xtmp_im;
        }
      }
    } else {
      int i2;
      i2 = 1;
      if (npages > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int i{0}; i < npages; i++) {
        double xtmp_im;
        int i1;
        int ib;
        i1 = i2;
        i2 += vspread;
        ib = i1 + vlend2;
        xtmp_re = S[ib].re;
        xtmp_im = S[ib].im;
        for (int k{0}; k <= vlend2; k++) {
          int b_i1;
          b_i = ib + k;
          b_i1 = (i1 + k) - 1;
          S[b_i] = S[b_i1];
          S[b_i1] = S[b_i + 1];
        }
        ib = (ib + vlend2) + 1;
        S[ib].re = xtmp_re;
        S[ib].im = xtmp_im;
      }
    }
  }
  if (signalwavelet::internal::iseven(static_cast<double>(F.size(0)))) {
    lowerDim = F.size(0);
    xtmp_re = static_cast<double>(F.size(0)) / 2.0;
    if (xtmp_re != std::floor(xtmp_re)) {
      rtIntegerError(xtmp_re, o_emlrtDCI);
    }
    if ((static_cast<int>(xtmp_re) < 1) ||
        (static_cast<int>(xtmp_re) > F.size(0))) {
      rtDynamicBoundsError(static_cast<int>(xtmp_re), 1, F.size(0), y_emlrtBCI);
    }
    xtmp_re = F[static_cast<int>(xtmp_re) - 1];
    Fout.set_size(F.size(0));
    for (b_i = 0; b_i < lowerDim; b_i++) {
      Fout[b_i] = F[b_i] - xtmp_re;
    }
  } else {
    lowerDim = F.size(0);
    xtmp_re = (static_cast<double>(F.size(0)) + 1.0) / 2.0;
    if (xtmp_re != std::floor(xtmp_re)) {
      rtIntegerError(xtmp_re, n_emlrtDCI);
    }
    if ((static_cast<int>(xtmp_re) < 1) ||
        (static_cast<int>(xtmp_re) > F.size(0))) {
      rtDynamicBoundsError(static_cast<int>(xtmp_re), 1, F.size(0), x_emlrtBCI);
    }
    xtmp_re = F[static_cast<int>(xtmp_re) - 1];
    Fout.set_size(F.size(0));
    for (b_i = 0; b_i < lowerDim; b_i++) {
      Fout[b_i] = F[b_i] - xtmp_re;
    }
  }
}

} // namespace stft
} // namespace internal
} // namespace b_signal
} // namespace coder

//
// File trailer for formatSTFTOutput.cpp
//
// [EOF]
//
