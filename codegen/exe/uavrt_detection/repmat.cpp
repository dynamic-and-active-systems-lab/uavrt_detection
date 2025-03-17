//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: repmat.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
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

// Variable Definitions
static rtDoubleCheckInfo j_emlrtDCI{
    37,      // lineNo
    "repmat" // fName
};

// Function Definitions
//
// Arguments    : const array<double, 2U> &a
//                double varargin_1
//                array<double, 2U> &b
// Return Type  : void
//
namespace coder {
void b_repmat(const array<double, 2U> &a, double varargin_1,
              array<double, 2U> &b)
{
  double d;
  int i;
  int i1;
  if ((varargin_1 != std::floor(varargin_1)) || std::isinf(varargin_1) ||
      (varargin_1 < -2.147483648E+9) || (varargin_1 > 2.147483647E+9)) {
    b_rtErrorWithMessageID(MIN_int32_T, jb_emlrtRTEI.fName,
                           jb_emlrtRTEI.lineNo);
  }
  if (varargin_1 <= 0.0) {
    d = 0.0;
  } else {
    d = varargin_1;
  }
  if (!(d <= 2.147483647E+9)) {
    m_rtErrorWithMessageID(m_emlrtRTEI.fName, m_emlrtRTEI.lineNo);
  }
  i = static_cast<int>(varargin_1);
  i1 = a.size(1);
  b.set_size(i, a.size(1));
  if (a.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int jcol{0}; jcol < i1; jcol++) {
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
// Arguments    : const array<double, 2U> &a
//                double varargin_2
//                array<double, 2U> &b
// Return Type  : void
//
void c_repmat(const array<double, 2U> &a, double varargin_2,
              array<double, 2U> &b)
{
  double d;
  int ncols;
  int ntilecols;
  if ((varargin_2 != std::floor(varargin_2)) || std::isinf(varargin_2) ||
      (varargin_2 < -2.147483648E+9) || (varargin_2 > 2.147483647E+9)) {
    b_rtErrorWithMessageID(MIN_int32_T, jb_emlrtRTEI.fName,
                           jb_emlrtRTEI.lineNo);
  }
  if (varargin_2 <= 0.0) {
    d = 0.0;
  } else {
    d = varargin_2;
  }
  if (!(d <= 2.147483647E+9)) {
    m_rtErrorWithMessageID(m_emlrtRTEI.fName, m_emlrtRTEI.lineNo);
  }
  b.set_size(1, a.size(1) * static_cast<int>(varargin_2));
  ncols = a.size(1);
  ntilecols = static_cast<int>(varargin_2);
  if (static_cast<int>(varargin_2) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int jtilecol{0}; jtilecol < ntilecols; jtilecol++) {
    int ibtile;
    ibtile = jtilecol * ncols;
    if (ncols > 2147483646) {
      check_forloop_overflow_error();
    }
    for (int jcol{0}; jcol < ncols; jcol++) {
      b[ibtile + jcol] = a[jcol];
    }
  }
}

//
// Arguments    : const array<double, 2U> &a
//                double varargin_1
//                array<double, 2U> &b
// Return Type  : void
//
void repmat(const array<double, 2U> &a, double varargin_1, array<double, 2U> &b)
{
  double d;
  int i;
  int i1;
  int nrows;
  int ntilerows;
  if ((varargin_1 != std::floor(varargin_1)) || std::isinf(varargin_1) ||
      (varargin_1 < -2.147483648E+9) || (varargin_1 > 2.147483647E+9)) {
    b_rtErrorWithMessageID(MIN_int32_T, jb_emlrtRTEI.fName,
                           jb_emlrtRTEI.lineNo);
  }
  if (varargin_1 <= 0.0) {
    d = 0.0;
  } else {
    d = varargin_1;
  }
  if (!(d <= 2.147483647E+9)) {
    m_rtErrorWithMessageID(m_emlrtRTEI.fName, m_emlrtRTEI.lineNo);
  }
  if (!(varargin_1 >= 0.0)) {
    rtNonNegativeError(varargin_1, j_emlrtDCI);
  }
  i = a.size(0) * static_cast<int>(varargin_1);
  i1 = a.size(1);
  b.set_size(i, a.size(1));
  nrows = a.size(0);
  ntilerows = static_cast<int>(varargin_1);
  if (a.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int jcol{0}; jcol < i1; jcol++) {
    int iacol;
    int ibmat;
    iacol = jcol * nrows;
    ibmat = jcol * i - 1;
    if (static_cast<int>(varargin_1) > 2147483646) {
      check_forloop_overflow_error();
    }
    for (int itilerow{0}; itilerow < ntilerows; itilerow++) {
      int ibcol;
      ibcol = ibmat + itilerow * nrows;
      if (nrows > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int k{0}; k < nrows; k++) {
        b[(ibcol + k) + 1] = a[iacol + k];
      }
    }
  }
}

//
// Arguments    : const c_struct_T &a
//                double varargin_1
//                double varargin_2
//                array<c_struct_T, 2U> &b
// Return Type  : void
//
void repmat(const c_struct_T &a, double varargin_1, double varargin_2,
            array<c_struct_T, 2U> &b)
{
  double d;
  int loop_ub_tmp;
  boolean_T b_b;
  if ((varargin_1 != std::floor(varargin_1)) || std::isinf(varargin_1) ||
      (varargin_1 < -2.147483648E+9) || (varargin_1 > 2.147483647E+9)) {
    b_rtErrorWithMessageID(MIN_int32_T, jb_emlrtRTEI.fName,
                           jb_emlrtRTEI.lineNo);
  } else {
    b_b = true;
  }
  if ((varargin_2 != std::floor(varargin_2)) || std::isinf(varargin_2) ||
      (varargin_2 < -2.147483648E+9) || (varargin_2 > 2.147483647E+9)) {
    b_b = false;
  }
  if (!b_b) {
    b_rtErrorWithMessageID(MIN_int32_T, jb_emlrtRTEI.fName,
                           jb_emlrtRTEI.lineNo);
  }
  if (varargin_1 <= 0.0) {
    d = 0.0;
  } else {
    d = varargin_1;
  }
  if (varargin_2 <= 0.0) {
    d = 0.0;
  } else {
    d *= varargin_2;
  }
  if (!(d <= 2.147483647E+9)) {
    m_rtErrorWithMessageID(m_emlrtRTEI.fName, m_emlrtRTEI.lineNo);
  }
  b.set_size(static_cast<int>(varargin_1), static_cast<int>(varargin_2));
  loop_ub_tmp = static_cast<int>(varargin_1) * static_cast<int>(varargin_2);
  for (int i{0}; i < loop_ub_tmp; i++) {
    b[i] = a;
  }
}

//
// Arguments    : const array<double, 1U> &a
//                double varargin_2
//                array<double, 2U> &b
// Return Type  : void
//
void repmat(const array<double, 1U> &a, double varargin_2, array<double, 2U> &b)
{
  double d;
  int i;
  int i1;
  if ((varargin_2 != std::floor(varargin_2)) || std::isinf(varargin_2) ||
      (varargin_2 < -2.147483648E+9) || (varargin_2 > 2.147483647E+9)) {
    b_rtErrorWithMessageID(MIN_int32_T, jb_emlrtRTEI.fName,
                           jb_emlrtRTEI.lineNo);
  }
  if (varargin_2 <= 0.0) {
    d = 0.0;
  } else {
    d = varargin_2;
  }
  if (!(d <= 2.147483647E+9)) {
    m_rtErrorWithMessageID(m_emlrtRTEI.fName, m_emlrtRTEI.lineNo);
  }
  if (!(varargin_2 >= 0.0)) {
    rtNonNegativeError(varargin_2, j_emlrtDCI);
  }
  i = a.size(0);
  i1 = static_cast<int>(varargin_2);
  b.set_size(a.size(0), i1);
  if (static_cast<int>(varargin_2) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int jtilecol{0}; jtilecol < i1; jtilecol++) {
    int ibtile;
    ibtile = jtilecol * i;
    if (i > 2147483646) {
      check_forloop_overflow_error();
    }
    for (int k{0}; k < i; k++) {
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
