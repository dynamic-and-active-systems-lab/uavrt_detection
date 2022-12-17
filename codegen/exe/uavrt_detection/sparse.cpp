//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sparse.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 17-Dec-2022 13:40:17
//

// Include Files
#include "sparse.h"
#include "anonymous_function.h"
#include "eml_int_forloop_overflow_check.h"
#include "introsort.h"
#include "rt_nonfinite.h"
#include "sparse1.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_internal_types.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include <string.h>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 1U> &varargin_1
//                g_sparse *y
// Return Type  : void
//
namespace coder {
void i_sparse(const ::coder::array<double, 1U> &varargin_1, g_sparse *y)
{
  int mInt;
  int numalloc;
  int row;
  mInt = varargin_1.size(0);
  if (varargin_1.size(0) >= MAX_int32_T) {
    pc_rtErrorWithMessageID(ec_emlrtRTEI.fName, ec_emlrtRTEI.lineNo);
  }
  numalloc = 0;
  row = varargin_1.size(0);
  for (int k{0}; k < row; k++) {
    if (varargin_1[k] != 0.0) {
      numalloc++;
    }
  }
  y->m = varargin_1.size(0);
  if (numalloc < 1) {
    numalloc = 1;
  }
  y->maxnz = numalloc;
  y->d.set_size(numalloc);
  y->colidx.set_size(2);
  y->colidx[0] = 1;
  y->rowidx.set_size(numalloc);
  for (row = 0; row < numalloc; row++) {
    y->d[row] = 0.0;
    y->rowidx[row] = 0;
  }
  y->rowidx[0] = 1;
  numalloc = 0;
  for (row = 0; row < mInt; row++) {
    if (varargin_1[row] != 0.0) {
      y->rowidx[numalloc] = row + 1;
      y->d[numalloc] = 1.0;
      numalloc++;
    }
  }
  y->colidx[1] = numalloc + 1;
}

//
// Arguments    : const ::coder::array<double, 1U> &varargin_1
//                const ::coder::array<double, 1U> &varargin_2
//                const ::coder::array<double, 1U> &varargin_3
//                sparse *y
// Return Type  : void
//
void i_sparse(const ::coder::array<double, 1U> &varargin_1,
              const ::coder::array<double, 1U> &varargin_2,
              const ::coder::array<double, 1U> &varargin_3, sparse *y)
{
  static rtDoubleCheckInfo t_emlrtDCI{
      193,             // lineNo
      48,              // colNo
      "sparse/sparse", // fName
      "C:\\Program "
      "Files\\MATLAB\\toolbox\\shared\\coder\\coder\\+coder\\+internal\\@"
      "sparse\\sparse.m", // pName
      4                   // checkKind
  };
  static rtRunTimeErrorInfo qc_emlrtRTEI{
      111,            // lineNo
      "sparse/sparse" // fName
  };
  static rtRunTimeErrorInfo rc_emlrtRTEI{
      116,            // lineNo
      "sparse/sparse" // fName
  };
  anonymous_function b_this;
  array<int, 1U> sortedIndices;
  array<int, 1U> t;
  int i;
  int nc;
  int numalloc;
  int ny;
  nc = varargin_2.size(0);
  if ((varargin_1.size(0) != varargin_2.size(0)) ||
      (varargin_3.size(0) != varargin_2.size(0))) {
    hb_rtErrorWithMessageID(qc_emlrtRTEI.fName, qc_emlrtRTEI.lineNo);
  }
  if ((varargin_3.size(0) != varargin_2.size(0)) &&
      (varargin_3.size(0) != varargin_1.size(0))) {
    hb_rtErrorWithMessageID(rc_emlrtRTEI.fName, rc_emlrtRTEI.lineNo);
  }
  sparse::assertValidIndexArg(varargin_1, b_this.workspace.b);
  sparse::assertValidIndexArg(varargin_2, b_this.workspace.a);
  sortedIndices.set_size(varargin_2.size(0));
  if (varargin_2.size(0) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{0}; k < nc; k++) {
    sortedIndices[k] = k + 1;
  }
  internal::introsort(sortedIndices, b_this.workspace.a.size(0), &b_this);
  ny = b_this.workspace.a.size(0);
  t.set_size(b_this.workspace.a.size(0));
  numalloc = b_this.workspace.a.size(0);
  for (i = 0; i < numalloc; i++) {
    t[i] = b_this.workspace.a[i];
  }
  if (b_this.workspace.a.size(0) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{0}; k < ny; k++) {
    b_this.workspace.a[k] = t[sortedIndices[k] - 1];
  }
  ny = b_this.workspace.b.size(0);
  t.set_size(b_this.workspace.b.size(0));
  numalloc = b_this.workspace.b.size(0);
  for (i = 0; i < numalloc; i++) {
    t[i] = b_this.workspace.b[i];
  }
  if (b_this.workspace.b.size(0) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{0}; k < ny; k++) {
    b_this.workspace.b[k] = t[sortedIndices[k] - 1];
  }
  if ((b_this.workspace.b.size(0) == 0) || (b_this.workspace.a.size(0) == 0)) {
    ny = 0;
    y->n = 0;
  } else {
    numalloc = b_this.workspace.b.size(0);
    ny = b_this.workspace.b[0];
    if (b_this.workspace.b.size(0) > 2147483646) {
      check_forloop_overflow_error();
    }
    for (int k{2}; k <= numalloc; k++) {
      i = b_this.workspace.b[k - 1];
      if (ny < i) {
        ny = i;
      }
    }
    y->n = b_this.workspace.a[b_this.workspace.a.size(0) - 1];
  }
  y->m = ny;
  numalloc = varargin_2.size(0);
  if (numalloc < 1) {
    numalloc = 1;
  }
  y->d.set_size(numalloc);
  for (i = 0; i < numalloc; i++) {
    y->d[i] = 0.0;
  }
  y->maxnz = numalloc;
  if (y->n + 1 < 0) {
    rtNonNegativeError(static_cast<double>(y->n + 1), &t_emlrtDCI);
  }
  y->colidx.set_size(y->n + 1);
  y->colidx[0] = 1;
  y->rowidx.set_size(numalloc);
  for (i = 0; i < numalloc; i++) {
    y->rowidx[i] = 0;
  }
  numalloc = 0;
  ny = y->n;
  if (y->n > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{0}; k < ny; k++) {
    while ((numalloc + 1 <= nc) && (b_this.workspace.a[numalloc] == k + 1)) {
      y->rowidx[numalloc] = b_this.workspace.b[numalloc];
      numalloc++;
    }
    y->colidx[k + 1] = numalloc + 1;
  }
  for (int k{0}; k < nc; k++) {
    y->d[k] = 1.0;
  }
  y->fillIn();
}

//
// Arguments    : const ::coder::array<boolean_T, 2U> &varargin_1
//                d_sparse *y
// Return Type  : void
//
void j_sparse(const ::coder::array<boolean_T, 2U> &varargin_1, d_sparse *y)
{
  int ctr;
  int i;
  int nInt;
  int numalloc;
  nInt = varargin_1.size(1);
  if (varargin_1.size(1) >= MAX_int32_T) {
    pc_rtErrorWithMessageID(ec_emlrtRTEI.fName, ec_emlrtRTEI.lineNo);
  }
  numalloc = 0;
  i = varargin_1.size(1);
  for (ctr = 0; ctr < i; ctr++) {
    if (varargin_1[ctr]) {
      numalloc++;
    }
  }
  y->n = varargin_1.size(1);
  if (numalloc < 1) {
    numalloc = 1;
  }
  y->d.set_size(numalloc);
  for (i = 0; i < numalloc; i++) {
    y->d[i] = false;
  }
  y->colidx.set_size(varargin_1.size(1) + 1);
  ctr = varargin_1.size(1);
  for (i = 0; i <= ctr; i++) {
    y->colidx[i] = 0;
  }
  y->colidx[0] = 1;
  y->rowidx.set_size(numalloc);
  for (i = 0; i < numalloc; i++) {
    y->rowidx[i] = 0;
  }
  y->rowidx[0] = 1;
  ctr = 0;
  for (numalloc = 0; numalloc < nInt; numalloc++) {
    if (varargin_1[numalloc]) {
      y->rowidx[ctr] = 1;
      y->d[ctr] = true;
      ctr++;
    }
    y->colidx[numalloc + 1] = ctr + 1;
  }
}

} // namespace coder

//
// File trailer for sparse.cpp
//
// [EOF]
//
