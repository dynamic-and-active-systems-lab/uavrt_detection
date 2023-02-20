//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: find.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 14:31:55
//

// Include Files
#include "find.h"
#include "eml_int_forloop_overflow_check.h"
#include "indexShapeCheck.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include <string.h>

// Variable Definitions
static rtRunTimeErrorInfo i_emlrtRTEI{
    392,                 // lineNo
    "find_first_indices" // fName
};

// Function Definitions
//
// Arguments    : const ::coder::array<boolean_T, 2U> &x
//                ::coder::array<int, 2U> &i
// Return Type  : void
//
namespace coder {
void b_eml_find(const ::coder::array<boolean_T, 2U> &x,
                ::coder::array<int, 2U> &i)
{
  int idx;
  int ii;
  int nx;
  boolean_T exitg1;
  nx = x.size(1);
  idx = 0;
  i.set_size(1, x.size(1));
  if (x.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  ii = 0;
  exitg1 = false;
  while ((!exitg1) && (ii <= nx - 1)) {
    if (x[ii]) {
      idx++;
      i[idx - 1] = ii + 1;
      if (idx >= nx) {
        exitg1 = true;
      } else {
        ii++;
      }
    } else {
      ii++;
    }
  }
  if (idx > x.size(1)) {
    j_rtErrorWithMessageID(i_emlrtRTEI.fName, i_emlrtRTEI.lineNo);
  }
  if (x.size(1) == 1) {
    if (idx == 0) {
      i.set_size(1, 0);
    }
  } else {
    if (idx < 1) {
      idx = 0;
    }
    i.set_size(i.size(0), idx);
  }
}

//
// Arguments    : int x_size
// Return Type  : int
//
int c_eml_find(int x_size)
{
  int i_size;
  int k;
  k = (x_size >= 1);
  if (k > x_size) {
    j_rtErrorWithMessageID(h_emlrtRTEI.fName, h_emlrtRTEI.lineNo);
  }
  if (k == 1) {
    i_size = 0;
  } else {
    int iv[2];
    iv[0] = 1;
    iv[1] = 0;
    internal::indexShapeCheck(0, iv);
    i_size = 0;
  }
  return i_size;
}

//
// Arguments    : const ::coder::array<boolean_T, 2U> &x
//                int i_data[]
//                int i_size[2]
// Return Type  : void
//
void eml_find(const ::coder::array<boolean_T, 2U> &x, int i_data[],
              int i_size[2])
{
  array<int, 2U> i;
  int idx;
  int ii;
  int k;
  boolean_T exitg1;
  k = (x.size(1) >= 1);
  if (k > x.size(1)) {
    j_rtErrorWithMessageID(h_emlrtRTEI.fName, h_emlrtRTEI.lineNo);
  }
  idx = 0;
  i.set_size(1, k);
  if (x.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  ii = 0;
  exitg1 = false;
  while ((!exitg1) && (ii <= x.size(1) - 1)) {
    if (x[ii]) {
      idx++;
      i[idx - 1] = ii + 1;
      if (idx >= k) {
        exitg1 = true;
      } else {
        ii++;
      }
    } else {
      ii++;
    }
  }
  if (idx > k) {
    j_rtErrorWithMessageID(i_emlrtRTEI.fName, i_emlrtRTEI.lineNo);
  }
  if (k == 1) {
    if (idx == 0) {
      i.set_size(1, 0);
    }
  } else {
    i.set_size(i.size(0), static_cast<int>(idx >= 1));
  }
  i_size[0] = 1;
  i_size[1] = i.size(1);
  k = i.size(1);
  if (k - 1 >= 0) {
    i_data[0] = i[0];
  }
}

} // namespace coder

//
// File trailer for find.cpp
//
// [EOF]
//
