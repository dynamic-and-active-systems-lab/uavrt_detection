//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: colon.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 18-Feb-2023 14:54:54
//

// Include Files
#include "colon.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include <cmath>
#include <string.h>

// Function Definitions
//
// Arguments    : int b
//                ::coder::array<int, 2U> &y
// Return Type  : void
//
namespace coder {
void b_eml_integer_colon_dispatcher(int b, ::coder::array<int, 2U> &y)
{
  int n;
  if (b < 1) {
    n = 0;
  } else {
    n = b;
  }
  y.set_size(1, n);
  if (n > 0) {
    int yk;
    y[0] = 1;
    yk = 1;
    if (n > 2147483646) {
      check_forloop_overflow_error();
    }
    for (int k{2}; k <= n; k++) {
      yk++;
      y[k - 1] = yk;
    }
  }
}

//
// Arguments    : double a
//                double b
//                ::coder::array<double, 2U> &y
// Return Type  : void
//
void eml_float_colon(double a, double b, ::coder::array<double, 2U> &y)
{
  static rtRunTimeErrorInfo pc_emlrtRTEI{
      419,              // lineNo
      "assert_pmaxsize" // fName
  };
  double apnd;
  double cdiff;
  double ndbl;
  int n;
  ndbl = std::floor((b - a) + 0.5);
  apnd = a + ndbl;
  cdiff = apnd - b;
  if (std::abs(cdiff) <
      4.4408920985006262E-16 * std::fmax(std::abs(a), std::abs(b))) {
    ndbl++;
    apnd = b;
  } else if (cdiff > 0.0) {
    apnd = a + (ndbl - 1.0);
  } else {
    ndbl++;
  }
  if (ndbl >= 0.0) {
    n = static_cast<int>(ndbl);
  } else {
    n = 0;
  }
  if (ndbl > 2.147483647E+9) {
    n_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
  }
  y.set_size(1, n);
  if (n > 0) {
    y[0] = a;
    if (n > 1) {
      int nm1d2;
      y[n - 1] = apnd;
      nm1d2 = (n - 1) / 2;
      for (int k{0}; k <= nm1d2 - 2; k++) {
        y[k + 1] = a + (static_cast<double>(k) + 1.0);
        y[(n - k) - 2] = apnd - (static_cast<double>(k) + 1.0);
      }
      if (nm1d2 << 1 == n - 1) {
        y[nm1d2] = (a + apnd) / 2.0;
      } else {
        y[nm1d2] = a + static_cast<double>(nm1d2);
        y[nm1d2 + 1] = apnd - static_cast<double>(nm1d2);
      }
    }
  }
}

//
// Arguments    : int a
//                int b
//                ::coder::array<int, 2U> &y
// Return Type  : void
//
void eml_integer_colon_dispatcher(int a, int b, ::coder::array<int, 2U> &y)
{
  static rtRunTimeErrorInfo pc_emlrtRTEI{
      291,                           // lineNo
      "integer_colon_length_nonnegd" // fName
  };
  int bma;
  if (b < a) {
    bma = 0;
  } else {
    bma = b - a;
    if (bma < 0) {
      i_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
    }
    bma++;
  }
  y.set_size(1, bma);
  if (bma > 0) {
    int yk;
    y[0] = a;
    yk = a;
    if (bma > 2147483646) {
      check_forloop_overflow_error();
    }
    for (int k{2}; k <= bma; k++) {
      yk++;
      y[k - 1] = yk;
    }
  }
}

//
// Arguments    : int a
//                ::coder::array<int, 2U> &y
// Return Type  : void
//
void eml_integer_colon_dispatcher(int a, ::coder::array<int, 2U> &y)
{
  int n;
  if (a > 49621) {
    n = 0;
  } else {
    unsigned int b_a;
    if (a < 0) {
      b_a = 49621U - a;
    } else {
      b_a = static_cast<unsigned int>(49621 - a);
    }
    n = static_cast<int>(b_a) + 1;
  }
  y.set_size(1, n);
  if (n > 0) {
    int yk;
    y[0] = a;
    yk = a;
    if (n > 2147483646) {
      check_forloop_overflow_error();
    }
    for (int k{2}; k <= n; k++) {
      yk++;
      y[k - 1] = yk;
    }
  }
}

} // namespace coder

//
// File trailer for colon.cpp
//
// [EOF]
//
