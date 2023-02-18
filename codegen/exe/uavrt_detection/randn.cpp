//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: randn.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 18-Feb-2023 14:54:54
//

// Include Files
#include "randn.h"
#include "eml_rand_mt19937ar.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include <string.h>

// Function Definitions
//
// Arguments    : double r[1000]
// Return Type  : void
//
namespace coder {
void randn(double r[1000])
{
  for (int k{0}; k < 1000; k++) {
    r[k] = eml_rand_mt19937ar(state);
  }
}

//
// Arguments    : double varargin_1
//                ::coder::array<double, 2U> &r
// Return Type  : void
//
void randn(double varargin_1, ::coder::array<double, 2U> &r)
{
  static rtDoubleCheckInfo t_emlrtDCI{
      37,                            // lineNo
      34,                            // colNo
      "eml_rand_mt19937ar_stateful", // fName
      "C:\\Program "
      "Files\\MATLAB\\toolbox\\eml\\lib\\matlab\\randfun\\private\\eml_rand_"
      "mt19937ar_stateful.m", // pName
      4                       // checkKind
  };
  int i;
  if (!(varargin_1 >= 0.0)) {
    rtNonNegativeError(varargin_1, &t_emlrtDCI);
  }
  r.set_size(static_cast<int>(varargin_1), 100);
  i = static_cast<int>(varargin_1) * 100;
  for (int k{0}; k < i; k++) {
    r[k] = eml_rand_mt19937ar(state);
  }
}

} // namespace coder

//
// File trailer for randn.cpp
//
// [EOF]
//
