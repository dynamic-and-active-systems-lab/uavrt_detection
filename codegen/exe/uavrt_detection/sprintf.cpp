//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sprintf.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 04-Feb-2025 09:56:05
//

// Include Files
#include "sprintf.h"
#include "rt_nonfinite.h"
#include "string1.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdio>

// Function Definitions
//
// Arguments    : int varargin_1
//                int varargin_2
//                array<char, 2U> &str
// Return Type  : void
//
namespace coder {
void b_sprintf(int varargin_1, int varargin_2, array<char, 2U> &str)
{
  int nbytes;
  nbytes = std::snprintf(nullptr, 0, "data_record.%d.%d.bin", varargin_1,
                         varargin_2);
  if (nbytes + 1 < 0) {
    rtNonNegativeError(static_cast<double>(nbytes + 1), emlrtDCI);
  }
  str.set_size(1, nbytes + 1);
  std::snprintf(&str[0], (size_t)(nbytes + 1), "data_record.%d.%d.bin",
                varargin_1, varargin_2);
  if (nbytes < 1) {
    nbytes = 0;
  }
  str.set_size(str.size(0), nbytes);
}

//
// Arguments    : const array<char, 2U> &varargin_1
//                double varargin_2
//                double varargin_3
//                double varargin_4
//                double varargin_5
//                unsigned int varargin_6
//                rtString &str
// Return Type  : void
//
void b_sprintf(const array<char, 2U> &varargin_1, double varargin_2,
               double varargin_3, double varargin_4, double varargin_5,
               unsigned int varargin_6, rtString &str)
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
  for (int i{0}; i < nbytes; i++) {
    c_varargin_1[i] = varargin_1[i];
  }
  c_varargin_1[varargin_1.size(1)] = '\x00';
  nbytes = std::snprintf(nullptr, 0, "%s/N%f-M%f-J%f-K%f-Trials%u.threshold",
                         &c_varargin_1[0], varargin_2, varargin_3, varargin_4,
                         varargin_5, varargin_6);
  if (nbytes + 1 < 0) {
    rtNonNegativeError(static_cast<double>(nbytes + 1), emlrtDCI);
  }
  str.Value.set_size(1, nbytes + 1);
  std::snprintf(&str.Value[0], (size_t)(nbytes + 1),
                "%s/N%f-M%f-J%f-K%f-Trials%u.threshold", &b_varargin_1[0],
                varargin_2, varargin_3, varargin_4, varargin_5, varargin_6);
  if (nbytes < 1) {
    nbytes = 0;
  }
  str.Value.set_size(str.Value.size(0), nbytes);
}

//
// Arguments    : int varargin_1
//                int varargin_2
//                array<char, 2U> &str
// Return Type  : void
//
void c_sprintf(int varargin_1, int varargin_2, array<char, 2U> &str)
{
  int nbytes;
  nbytes = std::snprintf(nullptr, 0, "spectro_segment.%d.%d.csv", varargin_1,
                         varargin_2);
  if (nbytes + 1 < 0) {
    rtNonNegativeError(static_cast<double>(nbytes + 1), emlrtDCI);
  }
  str.set_size(1, nbytes + 1);
  std::snprintf(&str[0], (size_t)(nbytes + 1), "spectro_segment.%d.%d.csv",
                varargin_1, varargin_2);
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
