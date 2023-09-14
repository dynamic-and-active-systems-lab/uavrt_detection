//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sprintf.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 14-Sep-2023 07:49:36
//

// Include Files
#include "sprintf.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdio>

// Function Definitions
//
// Arguments    : const ::coder::array<char, 2U> &varargin_1
//                double varargin_2
//                double varargin_3
//                ::coder::array<char, 2U> &str
// Return Type  : void
//
namespace coder {
void b_sprintf(const ::coder::array<char, 2U> &varargin_1, double varargin_2,
               double varargin_3, ::coder::array<char, 2U> &str)
{
  array<char, 2U> b_varargin_1;
  array<char, 2U> c_varargin_1;
  int nbytes;
  b_varargin_1.set_size(1, varargin_1.size(1) + 1);
  nbytes = varargin_1.size(1);
  for (int i{0}; i < nbytes; i++) {
    b_varargin_1[i] = varargin_1[i];
  }
  b_varargin_1[varargin_1.size(1)] = '\x00';
  c_varargin_1.set_size(1, varargin_1.size(1) + 1);
  nbytes = varargin_1.size(1);
  for (int i{0}; i < nbytes; i++) {
    c_varargin_1[i] = varargin_1[i];
  }
  c_varargin_1[varargin_1.size(1)] = '\x00';
  nbytes = std::snprintf(nullptr, 0, "%s_%f_%f_.csv", &c_varargin_1[0],
                         varargin_2, varargin_3);
  if (nbytes + 1 < 0) {
    rtNonNegativeError(static_cast<double>(nbytes + 1), n_emlrtDCI);
  }
  str.set_size(1, nbytes + 1);
  std::snprintf(&str[0], (size_t)(nbytes + 1), "%s_%f_%f_.csv",
                &b_varargin_1[0], varargin_2, varargin_3);
  if (nbytes < 1) {
    nbytes = 0;
  }
  str.set_size(str.size(0), nbytes);
}

} // namespace coder

//
// File trailer for sprintf.cpp
//
// [EOF]
//
