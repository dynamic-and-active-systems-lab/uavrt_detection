//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: find.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "find.h"
#include "eml_int_forloop_overflow_check.h"
#include "indexShapeCheck.h"
#include "rt_nonfinite.h"
#include "sparse1.h"
#include "threshold.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "waveform.h"
#include "coder_array.h"

// Variable Definitions
static rtRunTimeErrorInfo g_emlrtRTEI{
    81,        // lineNo
    "eml_find" // fName
};

static rtRunTimeErrorInfo h_emlrtRTEI{
    386,                 // lineNo
    "find_first_indices" // fName
};

// Function Definitions
//
// Arguments    : int in1_data[]
//                const coder::array<double, 1U> &in2
//                int in3
//                int in4
//                const waveform *in5
//                int in6
//                int in7
// Return Type  : int
//
int binary_expand_op_2(int in1_data[], const coder::array<double, 1U> &in2,
                       int in3, int in4, const waveform *in5, int in6, int in7)
{
  coder::array<boolean_T, 1U> b_in2;
  int i;
  int in1_size;
  int loop_ub;
  int stride_1_0;
  i = in7 - in6;
  in1_size = in4 - in3;
  if (i == 1) {
    loop_ub = in1_size;
  } else {
    loop_ub = i;
  }
  b_in2.set_size(loop_ub);
  in1_size = (in1_size != 1);
  stride_1_0 = (i != 1);
  for (i = 0; i < loop_ub; i++) {
    b_in2[i] = (in2[in3 + i * in1_size] <
                in5->thresh.threshVecFine[in6 + i * stride_1_0]);
  }
  return coder::c_eml_find(b_in2, in1_data);
}

//
// Arguments    : int in1_data[]
//                const coder::array<double, 1U> &in2
//                int in3
//                int in4
//                int in5
//                const waveform *in6
//                int in7
//                int in8
//                int in9
// Return Type  : int
//
int binary_expand_op_3(int in1_data[], const coder::array<double, 1U> &in2,
                       int in3, int in4, int in5, const waveform *in6, int in7,
                       int in8, int in9)
{
  coder::array<boolean_T, 1U> b_in2;
  int i;
  int in1_size;
  int loop_ub;
  int stride_1_0;
  i = div_s32((in9 - in7) + 1, in8) + 1;
  in1_size = div_s32((in5 - in3) + 1, in4) + 1;
  if (i == 1) {
    loop_ub = in1_size;
  } else {
    loop_ub = i;
  }
  b_in2.set_size(loop_ub);
  in1_size = (in1_size != 1);
  stride_1_0 = (i != 1);
  for (i = 0; i < loop_ub; i++) {
    b_in2[i] = (in2[(in3 + in4 * (i * in1_size)) - 1] <
                in6->thresh.threshVecFine[(in7 + in8 * (i * stride_1_0)) - 1]);
  }
  return coder::c_eml_find(b_in2, in1_data);
}

//
// Arguments    : const array<boolean_T, 2U> &x
//                array<int, 2U> &i
// Return Type  : void
//
namespace coder {
void b_eml_find(const array<boolean_T, 2U> &x, array<int, 2U> &i)
{
  int idx;
  int ii;
  int nx_tmp;
  boolean_T exitg1;
  nx_tmp = x.size(1);
  idx = 0;
  i.set_size(1, x.size(1));
  if (x.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  ii = 0;
  exitg1 = false;
  while ((!exitg1) && (ii <= nx_tmp - 1)) {
    if (x[ii]) {
      idx++;
      i[idx - 1] = ii + 1;
      if (idx >= nx_tmp) {
        exitg1 = true;
      } else {
        ii++;
      }
    } else {
      ii++;
    }
  }
  if (idx > x.size(1)) {
    g_rtErrorWithMessageID(h_emlrtRTEI.fName, h_emlrtRTEI.lineNo);
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
// Arguments    : const array<boolean_T, 1U> &x
//                int i_data[]
// Return Type  : int
//
int c_eml_find(const array<boolean_T, 1U> &x, int i_data[])
{
  int i_size;
  int idx;
  int ii;
  boolean_T exitg1;
  i_size = (x.size(0) >= 1);
  if (i_size > x.size(0)) {
    g_rtErrorWithMessageID(g_emlrtRTEI.fName, g_emlrtRTEI.lineNo);
  }
  idx = 0;
  if (x.size(0) > 2147483646) {
    check_forloop_overflow_error();
  }
  ii = 0;
  exitg1 = false;
  while ((!exitg1) && (ii <= x.size(0) - 1)) {
    if (x[ii]) {
      idx = 1;
      i_data[0] = ii + 1;
      exitg1 = true;
    } else {
      ii++;
    }
  }
  if (idx > i_size) {
    g_rtErrorWithMessageID(h_emlrtRTEI.fName, h_emlrtRTEI.lineNo);
  }
  if (i_size == 1) {
    if (idx == 0) {
      i_size = 0;
    }
  } else {
    int iv[2];
    i_size = (idx >= 1);
    iv[0] = 1;
    iv[1] = i_size;
    internal::indexShapeCheck(0, iv);
  }
  return i_size;
}

//
// Arguments    : const array<boolean_T, 1U> &x
//                int i_data[]
// Return Type  : int
//
int d_eml_find(const array<boolean_T, 1U> &x, int i_data[])
{
  static rtRunTimeErrorInfo rc_emlrtRTEI{
      441,                // lineNo
      "find_last_indices" // fName
  };
  int i_size;
  int idx;
  int ii;
  boolean_T exitg1;
  i_size = (x.size(0) >= 1);
  if (i_size > x.size(0)) {
    g_rtErrorWithMessageID(g_emlrtRTEI.fName, g_emlrtRTEI.lineNo);
  }
  ii = x.size(0);
  idx = 0;
  exitg1 = false;
  while ((!exitg1) && (ii > 0)) {
    if (x[ii - 1]) {
      idx = 1;
      i_data[0] = ii;
      exitg1 = true;
    } else {
      ii--;
    }
  }
  if (idx > i_size) {
    g_rtErrorWithMessageID(rc_emlrtRTEI.fName, rc_emlrtRTEI.lineNo);
  }
  if (i_size == 1) {
    if (idx == 0) {
      i_size = 0;
    }
  } else {
    int iv[2];
    i_size = (idx >= 1);
    iv[0] = 1;
    iv[1] = i_size;
    internal::indexShapeCheck(0, iv);
  }
  return i_size;
}

//
// Arguments    : const sparse &x
//                array<int, 1U> &i
//                array<int, 1U> &j
// Return Type  : void
//
void e_eml_find(const sparse &x, array<int, 1U> &i, array<int, 1U> &j)
{
  static rtDoubleCheckInfo q_emlrtDCI{
      189,                          // lineNo
      "find_first_nonempty_triples" // fName
  };
  static rtRunTimeErrorInfo rc_emlrtRTEI{
      233,                          // lineNo
      "find_first_nonempty_triples" // fName
  };
  int nx_tmp;
  nx_tmp = x.colidx[x.colidx.size(0) - 1] - 1;
  if (nx_tmp == 0) {
    i.set_size(0);
    j.set_size(0);
  } else {
    int col;
    int idx;
    if (nx_tmp < 0) {
      rtNonNegativeError(static_cast<double>(nx_tmp), q_emlrtDCI);
    }
    i.set_size(nx_tmp);
    j.set_size(nx_tmp);
    if (nx_tmp > 2147483646) {
      check_forloop_overflow_error();
    }
    for (idx = 0; idx < nx_tmp; idx++) {
      i[idx] = x.rowidx[idx];
    }
    idx = 0;
    col = 1;
    while (idx < nx_tmp) {
      if (idx == x.colidx[col] - 1) {
        col++;
      } else {
        idx++;
        j[idx - 1] = col;
      }
    }
    if (idx > nx_tmp) {
      g_rtErrorWithMessageID(rc_emlrtRTEI.fName, rc_emlrtRTEI.lineNo);
    }
    if (nx_tmp == 1) {
      if (idx == 0) {
        i.set_size(0);
        j.set_size(0);
      }
    } else {
      int iv[2];
      iv[0] = 1;
      iv[1] = idx;
      internal::indexShapeCheck(i.size(0), iv);
      i.set_size(idx);
      iv[0] = 1;
      iv[1] = idx;
      internal::indexShapeCheck(j.size(0), iv);
      j.set_size(idx);
      iv[0] = 1;
      iv[1] = idx;
      internal::indexShapeCheck(nx_tmp, iv);
    }
  }
}

//
// Arguments    : const array<double, 1U> &x
//                int i_data[]
// Return Type  : int
//
int e_eml_find(const array<double, 1U> &x, int i_data[])
{
  int i_size;
  int idx;
  int ii;
  boolean_T exitg1;
  i_size = (x.size(0) >= 1);
  if (i_size > x.size(0)) {
    g_rtErrorWithMessageID(g_emlrtRTEI.fName, g_emlrtRTEI.lineNo);
  }
  idx = 0;
  if (x.size(0) > 2147483646) {
    check_forloop_overflow_error();
  }
  ii = 0;
  exitg1 = false;
  while ((!exitg1) && (ii <= x.size(0) - 1)) {
    if (x[ii] != 0.0) {
      idx = 1;
      i_data[0] = ii + 1;
      exitg1 = true;
    } else {
      ii++;
    }
  }
  if (idx > i_size) {
    g_rtErrorWithMessageID(h_emlrtRTEI.fName, h_emlrtRTEI.lineNo);
  }
  if (i_size == 1) {
    if (idx == 0) {
      i_size = 0;
    }
  } else {
    int iv[2];
    i_size = (idx >= 1);
    iv[0] = 1;
    iv[1] = i_size;
    internal::indexShapeCheck(0, iv);
  }
  return i_size;
}

//
// Arguments    : const array<boolean_T, 2U> &x
//                int i_data[]
//                int i_size[2]
// Return Type  : void
//
void eml_find(const array<boolean_T, 2U> &x, int i_data[], int i_size[2])
{
  int idx;
  int ii;
  int k;
  boolean_T exitg1;
  k = (x.size(1) >= 1);
  if (k > x.size(1)) {
    g_rtErrorWithMessageID(g_emlrtRTEI.fName, g_emlrtRTEI.lineNo);
  }
  idx = 0;
  i_size[0] = 1;
  i_size[1] = k;
  if (x.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  ii = 0;
  exitg1 = false;
  while ((!exitg1) && (ii <= x.size(1) - 1)) {
    if (x[ii]) {
      idx = 1;
      i_data[0] = ii + 1;
      exitg1 = true;
    } else {
      ii++;
    }
  }
  if (idx > k) {
    g_rtErrorWithMessageID(h_emlrtRTEI.fName, h_emlrtRTEI.lineNo);
  }
  if (k == 1) {
    if (idx == 0) {
      i_size[0] = 1;
      i_size[1] = 0;
    }
  } else {
    i_size[1] = (idx >= 1);
  }
}

} // namespace coder

//
// File trailer for find.cpp
//
// [EOF]
//
