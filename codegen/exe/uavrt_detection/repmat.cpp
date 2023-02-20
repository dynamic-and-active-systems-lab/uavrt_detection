//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: repmat.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 14:31:55
//

// Include Files
#include "repmat.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include <cmath>
#include <string.h>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 1U> &a
//                double varargin_2
//                ::coder::array<double, 2U> &b
// Return Type  : void
//
namespace coder {
void repmat(const ::coder::array<double, 1U> &a, double varargin_2,
            ::coder::array<double, 2U> &b)
{
  int i;
  int nrows;
  if ((varargin_2 != varargin_2) || std::isinf(varargin_2)) {
    c_rtErrorWithMessageID(MIN_int32_T, gb_emlrtRTEI.fName,
                           gb_emlrtRTEI.lineNo);
  }
  i = static_cast<int>(varargin_2);
  b.set_size(a.size(0), i);
  nrows = a.size(0);
  if (static_cast<int>(varargin_2) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int jtilecol{0}; jtilecol < i; jtilecol++) {
    int ibtile;
    ibtile = jtilecol * nrows;
    if (nrows > 2147483646) {
      check_forloop_overflow_error();
    }
    for (int k{0}; k < nrows; k++) {
      b[ibtile + k] = a[k];
    }
  }
}

} // namespace coder

//
// File trailer for repmat.cpp
//
// [EOF]
//
