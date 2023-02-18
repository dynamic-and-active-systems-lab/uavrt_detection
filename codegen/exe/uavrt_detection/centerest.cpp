//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: centerest.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 18-Feb-2023 14:54:54
//

// Include Files
#include "centerest.h"
#include "eml_int_forloop_overflow_check.h"
#include "iseven.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include "omp.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string.h>
#include <string>

// Function Declarations
static void b_rtDivisionByZeroErrorN();

static int div_s32_sat(int numerator, int denominator);

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
static void b_rtDivisionByZeroErrorN()
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Division by zero detected.\nEarly termination due to division "
               "by zero.";
  outStream << "\n";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// Arguments    : int numerator
//                int denominator
// Return Type  : int
//
static int div_s32_sat(int numerator, int denominator)
{
  int quotient;
  if (denominator == 0) {
    b_rtDivisionByZeroErrorN();
  } else {
    unsigned int b_denominator;
    unsigned int b_numerator;
    boolean_T quotientNeedsNegation;
    quotientNeedsNegation = ((numerator < 0) != (denominator < 0));
    if (numerator < 0) {
      b_numerator = ~static_cast<unsigned int>(numerator) + 1U;
    } else {
      b_numerator = static_cast<unsigned int>(numerator);
    }
    if (denominator < 0) {
      b_denominator = ~static_cast<unsigned int>(denominator) + 1U;
    } else {
      b_denominator = static_cast<unsigned int>(denominator);
    }
    b_numerator /= b_denominator;
    if ((!quotientNeedsNegation) && (b_numerator >= 2147483647U)) {
      quotient = MAX_int32_T;
    } else if (quotientNeedsNegation && (b_numerator > 2147483647U)) {
      quotient = MIN_int32_T;
    } else if (quotientNeedsNegation) {
      quotient = -static_cast<int>(b_numerator);
    } else {
      quotient = static_cast<int>(b_numerator);
    }
  }
  return quotient;
}

//
// Arguments    : ::coder::array<creal_T, 3U> &y
// Return Type  : void
//
namespace coder {
namespace signal {
namespace internal {
namespace spectral {
void centerest(::coder::array<creal_T, 3U> &y)
{
  array<creal_T, 2U> buffer;
  if (signalwavelet::internal::iseven(static_cast<double>(y.size(0)))) {
    double xtmp_re;
    int vlend2;
    xtmp_re = static_cast<double>(y.size(0)) / 2.0 - 1.0;
    vlend2 = 1;
    if (y.size(0) != 1) {
      vlend2 = 0;
    } else if ((y.size(1) == 1) && (y.size(2) != 1)) {
      vlend2 = 2;
    }
    if (static_cast<int>(xtmp_re) != xtmp_re) {
      rtErrorWithMessageID("int32", "int32", cb_emlrtRTEI.fName,
                           cb_emlrtRTEI.lineNo);
    }
    if ((y.size(0) != 0) && (y.size(1) != 0) &&
        ((y.size(0) != 1) || (y.size(1) != 1) || (y.size(2) != 1))) {
      int b_i;
      int i2;
      int ib;
      int lowerDim;
      int npages;
      int ns;
      int vspread;
      boolean_T shiftright;
      if (xtmp_re < 0.0) {
        ns = 1;
        shiftright = false;
      } else {
        ns = static_cast<int>(xtmp_re);
        shiftright = true;
      }
      if (ns > y.size(vlend2)) {
        if (y.size(vlend2) == 0) {
          mc_rtErrorWithMessageID(nc_emlrtRTEI.fName, nc_emlrtRTEI.lineNo);
        }
        ns -= div_s32_sat(ns, y.size(vlend2)) * y.size(vlend2);
      }
      if (ns > (y.size(vlend2) >> 1)) {
        ns = y.size(vlend2) - ns;
        shiftright = !shiftright;
      }
      lowerDim = y.size(0);
      if ((y.size(0) > 0) && ((y.size(1) == 0) || (y.size(1) > y.size(0)))) {
        lowerDim = y.size(1);
      }
      if ((lowerDim > 0) && (y.size(2) > lowerDim)) {
        lowerDim = y.size(2);
      }
      lowerDim =
          static_cast<int>(std::floor(static_cast<double>(lowerDim) / 2.0));
      buffer.set_size(1, lowerDim);
      for (b_i = 0; b_i < lowerDim; b_i++) {
        buffer[b_i].re = 0.0;
        buffer[b_i].im = 0.0;
      }
      b_i = y.size(vlend2);
      i2 = y.size(vlend2);
      ib = 1;
      for (int k{0}; k < vlend2; k++) {
        ib *= y.size(k);
      }
      npages = 1;
      lowerDim = vlend2 + 2;
      for (int k{lowerDim}; k < 4; k++) {
        npages *= y.size(k - 1);
      }
      vspread = ib * y.size(vlend2);
      if ((y.size(vlend2) > 1) && (ns > 0)) {
        if (npages > 2147483646) {
          check_forloop_overflow_error();
        }
        for (int i{0}; i < npages; i++) {
          lowerDim = i * vspread;
          if (ib > 2147483646) {
            check_forloop_overflow_error();
          }
          for (vlend2 = 0; vlend2 < ib; vlend2++) {
            int i1;
            i1 = lowerDim + vlend2;
            if (shiftright) {
              int b_i1;
              for (int k{0}; k < ns; k++) {
                buffer[k] = y[i1 + ((k + b_i) - ns) * ib];
              }
              b_i1 = ns + 1;
              for (int k{i2}; k >= b_i1; k--) {
                y[i1 + (k - 1) * ib] = y[i1 + ((k - ns) - 1) * ib];
              }
              for (int k{0}; k < ns; k++) {
                y[i1 + k * ib] = buffer[k];
              }
            } else {
              int b_i1;
              for (int k{0}; k < ns; k++) {
                buffer[k] = y[i1 + k * ib];
              }
              b_i1 = (b_i - ns) - 1;
              for (int k{0}; k <= b_i1; k++) {
                y[i1 + k * ib] = y[i1 + (k + ns) * ib];
              }
              for (int k{0}; k < ns; k++) {
                y[i1 + ((k + b_i) - ns) * ib] = buffer[k];
              }
            }
          }
        }
      }
    }
  } else if (y.size(0) > 1) {
    int npages;
    int vlend2;
    int vspread;
    vlend2 = y.size(0) / 2 - 1;
    npages = y.size(1) * y.size(2);
    vspread = y.size(0);
    if ((vlend2 + 1) << 1 == y.size(0)) {
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
          double xtmp_re;
          int b_i;
          int lowerDim;
          lowerDim = (i1 + k) - 1;
          xtmp_re = y[lowerDim].re;
          xtmp_im = y[lowerDim].im;
          b_i = ib + k;
          y[lowerDim] = y[b_i];
          y[b_i].re = xtmp_re;
          y[b_i].im = xtmp_im;
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
        double xtmp_re;
        int i1;
        int ib;
        i1 = i2;
        i2 += vspread;
        ib = i1 + vlend2;
        xtmp_re = y[ib].re;
        xtmp_im = y[ib].im;
        for (int k{0}; k <= vlend2; k++) {
          int b_i;
          int b_i1;
          b_i = ib + k;
          b_i1 = (i1 + k) - 1;
          y[b_i] = y[b_i1];
          y[b_i1] = y[b_i + 1];
        }
        ib = (ib + vlend2) + 1;
        y[ib].re = xtmp_re;
        y[ib].im = xtmp_im;
      }
    }
  }
}

} // namespace spectral
} // namespace internal
} // namespace signal
} // namespace coder

//
// File trailer for centerest.cpp
//
// [EOF]
//
