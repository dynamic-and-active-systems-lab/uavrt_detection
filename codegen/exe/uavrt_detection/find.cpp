//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: find.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 17:51:34
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
#include <string.h>

// Variable Definitions
static rtRunTimeErrorInfo h_emlrtRTEI{
    81,        // lineNo
    "eml_find" // fName
};

static rtRunTimeErrorInfo i_emlrtRTEI{
    392,                 // lineNo
    "find_first_indices" // fName
};

// Function Definitions
//
// Arguments    : int in1_data[]
//                int *in1_size
//                const coder::array<double, 1U> &in2
//                int in3
//                int in4
//                int in5
//                const waveform *in6
//                int in7
//                int in8
//                int in9
// Return Type  : void
//
void binary_expand_op(int in1_data[], int *in1_size,
                      const coder::array<double, 1U> &in2, int in3, int in4,
                      int in5, const waveform *in6, int in7, int in8, int in9)
{
  coder::array<boolean_T, 1U> b_in2;
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (div_s32((in9 - in7) + 1, in8) + 1 == 1) {
    i = div_s32((in5 - in3) + 1, in4) + 1;
  } else {
    i = div_s32((in9 - in7) + 1, in8) + 1;
  }
  b_in2.set_size(i);
  stride_0_0 = (div_s32((in5 - in3) + 1, in4) + 1 != 1);
  stride_1_0 = (div_s32((in9 - in7) + 1, in8) + 1 != 1);
  if (div_s32((in9 - in7) + 1, in8) + 1 == 1) {
    loop_ub = div_s32((in5 - in3) + 1, in4) + 1;
  } else {
    loop_ub = div_s32((in9 - in7) + 1, in8) + 1;
  }
  for (i = 0; i < loop_ub; i++) {
    b_in2[i] = (in2[(in3 + in4 * (i * stride_0_0)) - 1] <
                in6->thresh.threshVecFine[(in7 + in8 * (i * stride_1_0)) - 1]);
  }
  coder::c_eml_find(b_in2, in1_data, in1_size);
}

//
// Arguments    : int in1_data[]
//                int *in1_size
//                const coder::array<double, 1U> &in2
//                int in3
//                int in4
//                const waveform *in5
//                int in6
//                int in7
// Return Type  : void
//
void binary_expand_op(int in1_data[], int *in1_size,
                      const coder::array<double, 1U> &in2, int in3, int in4,
                      const waveform *in5, int in6, int in7)
{
  coder::array<boolean_T, 1U> b_in2;
  int b_in7;
  int loop_ub;
  int stride_1_0;
  if (in7 - in6 == 1) {
    b_in7 = in4 - in3;
  } else {
    b_in7 = in7 - in6;
  }
  b_in2.set_size(b_in7);
  b_in7 = (in4 - in3 != 1);
  stride_1_0 = (in7 - in6 != 1);
  if (in7 - in6 == 1) {
    loop_ub = in4 - in3;
  } else {
    loop_ub = in7 - in6;
  }
  for (int i{0}; i < loop_ub; i++) {
    b_in2[i] = (in2[in3 + i * b_in7] <
                in5->thresh.threshVecFine[in6 + i * stride_1_0]);
  }
  coder::c_eml_find(b_in2, in1_data, in1_size);
}

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
    i_rtErrorWithMessageID(i_emlrtRTEI.fName, i_emlrtRTEI.lineNo);
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
// Arguments    : const ::coder::array<boolean_T, 1U> &x
//                int i_data[]
//                int *i_size
// Return Type  : void
//
void c_eml_find(const ::coder::array<boolean_T, 1U> &x, int i_data[],
                int *i_size)
{
  int idx;
  int ii;
  boolean_T exitg1;
  *i_size = (x.size(0) >= 1);
  if (*i_size > x.size(0)) {
    i_rtErrorWithMessageID(h_emlrtRTEI.fName, h_emlrtRTEI.lineNo);
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
  if (idx > *i_size) {
    i_rtErrorWithMessageID(i_emlrtRTEI.fName, i_emlrtRTEI.lineNo);
  }
  if (*i_size == 1) {
    if (idx == 0) {
      *i_size = 0;
    }
  } else {
    int iv[2];
    *i_size = (idx >= 1);
    iv[0] = 1;
    iv[1] = *i_size;
    internal::indexShapeCheck(0, iv);
  }
}

//
// Arguments    : const ::coder::array<boolean_T, 1U> &x
//                int i_data[]
//                int *i_size
// Return Type  : void
//
void d_eml_find(const ::coder::array<boolean_T, 1U> &x, int i_data[],
                int *i_size)
{
  static rtRunTimeErrorInfo tc_emlrtRTEI{
      447,                // lineNo
      "find_last_indices" // fName
  };
  int idx;
  int ii;
  boolean_T exitg1;
  *i_size = (x.size(0) >= 1);
  if (*i_size > x.size(0)) {
    i_rtErrorWithMessageID(h_emlrtRTEI.fName, h_emlrtRTEI.lineNo);
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
  if (idx > *i_size) {
    i_rtErrorWithMessageID(tc_emlrtRTEI.fName, tc_emlrtRTEI.lineNo);
  }
  if (*i_size == 1) {
    if (idx == 0) {
      *i_size = 0;
    }
  } else {
    int iv[2];
    *i_size = (idx >= 1);
    iv[0] = 1;
    iv[1] = *i_size;
    internal::indexShapeCheck(0, iv);
  }
}

//
// Arguments    : const sparse *x
//                ::coder::array<int, 1U> &i
//                ::coder::array<int, 1U> &j
// Return Type  : void
//
void e_eml_find(const sparse *x, ::coder::array<int, 1U> &i,
                ::coder::array<int, 1U> &j)
{
  static rtDoubleCheckInfo t_emlrtDCI{
      195,                           // lineNo
      30,                            // colNo
      "find_first_nonempty_triples", // fName
      "C:\\Program Files\\MATLAB\\toolbox\\eml\\lib\\matlab\\elmat\\find.m", // pName
      4 // checkKind
  };
  static rtRunTimeErrorInfo tc_emlrtRTEI{
      239,                          // lineNo
      "find_first_nonempty_triples" // fName
  };
  array<double, 1U> v;
  int nx;
  nx = x->colidx[x->colidx.size(0) - 1] - 2;
  if (x->colidx[x->colidx.size(0) - 1] - 1 == 0) {
    i.set_size(0);
    j.set_size(0);
  } else {
    int col;
    int idx;
    col = x->colidx[x->colidx.size(0) - 1] - 1;
    if (col < 0) {
      rtNonNegativeError(static_cast<double>(col), &t_emlrtDCI);
    }
    i.set_size(col);
    j.set_size(x->colidx[x->colidx.size(0) - 1] - 1);
    v.set_size(x->colidx[x->colidx.size(0) - 1] - 1);
    if (x->colidx[x->colidx.size(0) - 1] - 1 > 2147483646) {
      check_forloop_overflow_error();
    }
    for (idx = 0; idx <= nx; idx++) {
      i[idx] = x->rowidx[idx];
    }
    if (x->colidx[x->colidx.size(0) - 1] - 1 > 2147483646) {
      check_forloop_overflow_error();
    }
    for (col = 0; col <= nx; col++) {
      v[col] = x->d[col];
    }
    idx = 0;
    col = 1;
    while (idx < nx + 1) {
      if (idx == x->colidx[col] - 1) {
        col++;
      } else {
        idx++;
        j[idx - 1] = col;
      }
    }
    if (idx > x->colidx[x->colidx.size(0) - 1] - 1) {
      i_rtErrorWithMessageID(tc_emlrtRTEI.fName, tc_emlrtRTEI.lineNo);
    }
    if (x->colidx[x->colidx.size(0) - 1] - 1 == 1) {
      if (idx == 0) {
        i.set_size(0);
        j.set_size(0);
      }
    } else {
      int iv[2];
      if (idx < 1) {
        col = 0;
      } else {
        col = idx;
      }
      iv[0] = 1;
      iv[1] = col;
      internal::indexShapeCheck(i.size(0), iv);
      i.set_size(col);
      if (idx < 1) {
        col = 0;
      } else {
        col = idx;
      }
      iv[0] = 1;
      iv[1] = col;
      internal::indexShapeCheck(j.size(0), iv);
      j.set_size(col);
      iv[0] = 1;
      if (idx < 1) {
        iv[1] = 0;
      } else {
        iv[1] = idx;
      }
      internal::indexShapeCheck(v.size(0), iv);
    }
  }
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
    i_rtErrorWithMessageID(h_emlrtRTEI.fName, h_emlrtRTEI.lineNo);
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
    i_rtErrorWithMessageID(i_emlrtRTEI.fName, i_emlrtRTEI.lineNo);
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
