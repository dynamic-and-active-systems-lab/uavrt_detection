//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: norm.cpp
//
<<<<<<< HEAD
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 23-May-2023 12:05:02
=======
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Apr-2023 11:47:02
>>>>>>> 3930a1e557481905555f2756f2f70ac82e87beba
//

// Include Files
#include "norm.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_rtwutil.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const ::coder::array<creal_T, 2U> &x
// Return Type  : double
//
namespace coder {
double b_norm(const ::coder::array<creal_T, 2U> &x)
{
  double y;
  if (x.size(0) == 0) {
    y = 0.0;
  } else {
    y = 0.0;
    if (x.size(0) == 1) {
      y = rt_hypotd_snf(x[0].re, x[0].im);
    } else {
      double scale;
      int kend;
      scale = 3.3121686421112381E-170;
      kend = x.size(0);
      if (x.size(0) > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int k{0}; k < kend; k++) {
        double absxk;
        double t;
        absxk = std::abs(x[k].re);
        if (absxk > scale) {
          t = scale / absxk;
          y = y * t * t + 1.0;
          scale = absxk;
        } else {
          t = absxk / scale;
          y += t * t;
        }
        absxk = std::abs(x[k].im);
        if (absxk > scale) {
          t = scale / absxk;
          y = y * t * t + 1.0;
          scale = absxk;
        } else {
          t = absxk / scale;
          y += t * t;
        }
      }
      y = scale * std::sqrt(y);
    }
  }
  return y;
}

} // namespace coder

//
// File trailer for norm.cpp
//
// [EOF]
//
