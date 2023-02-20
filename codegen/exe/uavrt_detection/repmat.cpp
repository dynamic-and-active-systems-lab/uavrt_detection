//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: repmat.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 15:31:40
//

// Include Files
#include "repmat.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_internal_types.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include <cmath>
#include <string.h>

// Function Definitions
//
// Arguments    : const c_struct_T *a
//                double varargin_1
//                double varargin_2
//                ::coder::array<c_struct_T, 2U> &b
// Return Type  : void
//
namespace coder {
void repmat(const c_struct_T *a, double varargin_1, double varargin_2,
            ::coder::array<c_struct_T, 2U> &b)
{
  double b_varargin_1;
  int loop_ub;
  boolean_T b_b;
  if ((varargin_1 != std::floor(varargin_1)) || std::isinf(varargin_1) ||
      (varargin_1 < -2.147483648E+9) || (varargin_1 > 2.147483647E+9)) {
    c_rtErrorWithMessageID(MIN_int32_T, ob_emlrtRTEI.fName,
                           ob_emlrtRTEI.lineNo);
  } else {
    b_b = true;
  }
  if ((varargin_2 != std::floor(varargin_2)) || std::isinf(varargin_2) ||
      (varargin_2 < -2.147483648E+9) || (varargin_2 > 2.147483647E+9)) {
    b_b = false;
  }
  if (!b_b) {
    c_rtErrorWithMessageID(MIN_int32_T, ob_emlrtRTEI.fName,
                           ob_emlrtRTEI.lineNo);
  }
  if (varargin_1 <= 0.0) {
    b_varargin_1 = 0.0;
  } else {
    b_varargin_1 = varargin_1;
  }
  if (varargin_2 <= 0.0) {
    b_varargin_1 = 0.0;
  } else {
    b_varargin_1 *= varargin_2;
  }
  if (!(b_varargin_1 <= 2.147483647E+9)) {
    m_rtErrorWithMessageID(o_emlrtRTEI.fName, o_emlrtRTEI.lineNo);
  }
  b.set_size(static_cast<int>(varargin_1), static_cast<int>(varargin_2));
  loop_ub = static_cast<int>(varargin_1) * static_cast<int>(varargin_2);
  for (int i{0}; i < loop_ub; i++) {
    b[i] = *a;
  }
}

//
// Arguments    : const ::coder::array<double, 2U> &a
//                double varargin_1
//                ::coder::array<double, 2U> &b
// Return Type  : void
//
void repmat(const ::coder::array<double, 2U> &a, double varargin_1,
            ::coder::array<double, 2U> &b)
{
  double b_varargin_1;
  int i;
  int ncols;
  if ((varargin_1 != std::floor(varargin_1)) || std::isinf(varargin_1) ||
      (varargin_1 < -2.147483648E+9) || (varargin_1 > 2.147483647E+9)) {
    c_rtErrorWithMessageID(MIN_int32_T, ob_emlrtRTEI.fName,
                           ob_emlrtRTEI.lineNo);
  }
  if (varargin_1 <= 0.0) {
    b_varargin_1 = 0.0;
  } else {
    b_varargin_1 = varargin_1;
  }
  if (!(b_varargin_1 <= 2.147483647E+9)) {
    m_rtErrorWithMessageID(o_emlrtRTEI.fName, o_emlrtRTEI.lineNo);
  }
  i = static_cast<int>(varargin_1);
  b.set_size(i, a.size(1));
  ncols = a.size(1);
  if (a.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int jcol{0}; jcol < ncols; jcol++) {
    int ibmat;
    ibmat = jcol * static_cast<int>(varargin_1);
    if (static_cast<int>(varargin_1) > 2147483646) {
      check_forloop_overflow_error();
    }
    for (int itilerow{0}; itilerow < i; itilerow++) {
      b[ibmat + itilerow] = a[jcol];
    }
  }
}

//
// Arguments    : const ::coder::array<double, 1U> &a
//                double varargin_2
//                ::coder::array<double, 2U> &b
// Return Type  : void
//
void repmat(const ::coder::array<double, 1U> &a, double varargin_2,
            ::coder::array<double, 2U> &b)
{
  double b_varargin_2;
  int i;
  int nrows;
  if ((varargin_2 != std::floor(varargin_2)) || std::isinf(varargin_2) ||
      (varargin_2 < -2.147483648E+9) || (varargin_2 > 2.147483647E+9)) {
    c_rtErrorWithMessageID(MIN_int32_T, ob_emlrtRTEI.fName,
                           ob_emlrtRTEI.lineNo);
  }
  if (varargin_2 <= 0.0) {
    b_varargin_2 = 0.0;
  } else {
    b_varargin_2 = varargin_2;
  }
  if (!(b_varargin_2 <= 2.147483647E+9)) {
    m_rtErrorWithMessageID(o_emlrtRTEI.fName, o_emlrtRTEI.lineNo);
  }
  if (!(varargin_2 >= 0.0)) {
    rtNonNegativeError(varargin_2, &o_emlrtDCI);
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
