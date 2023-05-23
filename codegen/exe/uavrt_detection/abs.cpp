//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: abs.cpp
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
#include "abs.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_rtwutil.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<creal_T, 2U> &x
//                ::coder::array<double, 2U> &y
// Return Type  : void
//
namespace coder {
void b_abs(const ::coder::array<creal_T, 2U> &x, ::coder::array<double, 2U> &y)
{
  int nx;
  nx = x.size(0) * x.size(1);
  y.set_size(x.size(0), x.size(1));
  if (nx > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{0}; k < nx; k++) {
    y[k] = rt_hypotd_snf(x[k].re, x[k].im);
  }
}

} // namespace coder

//
// File trailer for abs.cpp
//
// [EOF]
//
