//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: colon.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 14:31:55
//

// Include Files
#include "colon.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include <cmath>
#include <string.h>

// Function Definitions
//
// Arguments    : double a
//                double b
//                double y_data[]
//                int y_size[2]
// Return Type  : void
//
namespace coder {
void eml_float_colon(double a, double b, double y_data[], int y_size[2])
{
  static rtDoubleCheckInfo b_emlrtDCI{
      320,               // lineNo
      28,                // colNo
      "eml_float_colon", // fName
      "C:\\Program Files\\MATLAB\\toolbox\\eml\\lib\\matlab\\ops\\colon.m", // pName
      4 // checkKind
  };
  double apnd;
  double cdiff;
  double ndbl;
  int n;
  ndbl = std::floor((b - a) + 0.5);
  apnd = a + ndbl;
  cdiff = apnd - b;
  if (std::abs(cdiff) < 4.4408920985006262E-16 * std::abs(a)) {
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
  y_size[0] = 1;
  if (n < 0) {
    rtNonNegativeError(static_cast<double>(n), &b_emlrtDCI);
  }
  y_size[1] = n;
  if (n > 0) {
    y_data[0] = a;
    if (n > 1) {
      int nm1d2;
      y_data[n - 1] = apnd;
      nm1d2 = (n - 1) / 2;
      if (nm1d2 << 1 == n - 1) {
        y_data[nm1d2] = (a + apnd) / 2.0;
      } else {
        y_data[nm1d2] = a + static_cast<double>(nm1d2);
        y_data[nm1d2 + 1] = apnd - static_cast<double>(nm1d2);
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
  static rtRunTimeErrorInfo kb_emlrtRTEI{
      291,                           // lineNo
      "integer_colon_length_nonnegd" // fName
  };
  int bma;
  if (b < a) {
    bma = 0;
  } else {
    bma = b - a;
    if (bma < 0) {
      j_rtErrorWithMessageID(kb_emlrtRTEI.fName, kb_emlrtRTEI.lineNo);
    }
    bma++;
  }
  y.set_size(1, bma);
  if (bma > 0) {
    int yk;
    y[0] = a;
    yk = a;
    for (int k{2}; k <= bma; k++) {
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
