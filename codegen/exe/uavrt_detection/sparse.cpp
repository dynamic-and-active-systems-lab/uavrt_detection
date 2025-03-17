//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sparse.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
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

// Function Definitions
//
// Arguments    : const array<double, 1U> &varargin_1
//                const array<double, 1U> &varargin_2
//                const array<double, 1U> &varargin_3
//                sparse &y
// Return Type  : void
//
namespace coder {
void i_sparse(const array<double, 1U> &varargin_1,
              const array<double, 1U> &varargin_2,
              const array<double, 1U> &varargin_3, sparse &y)
{
  static rtDoubleCheckInfo q_emlrtDCI{
      13,      // lineNo
      "sparse" // fName
  };
  static rtRunTimeErrorInfo rc_emlrtRTEI{
      111,            // lineNo
      "sparse/sparse" // fName
  };
  static rtRunTimeErrorInfo sc_emlrtRTEI{
      116,            // lineNo
      "sparse/sparse" // fName
  };
  anonymous_function b_this;
  array<int, 1U> sortedIndices;
  array<int, 1U> t;
  int i;
  int nc_tmp;
  int numalloc;
  int thism;
  nc_tmp = varargin_2.size(0);
  if ((varargin_1.size(0) != varargin_2.size(0)) ||
      (varargin_3.size(0) != varargin_2.size(0))) {
    nb_rtErrorWithMessageID(rc_emlrtRTEI.fName, rc_emlrtRTEI.lineNo);
  }
  if ((varargin_3.size(0) != varargin_2.size(0)) &&
      (varargin_3.size(0) != varargin_1.size(0))) {
    nb_rtErrorWithMessageID(sc_emlrtRTEI.fName, sc_emlrtRTEI.lineNo);
  }
  sparse::assertValidIndexArg(varargin_1, b_this.workspace.b);
  sparse::assertValidIndexArg(varargin_2, b_this.workspace.a);
  sortedIndices.set_size(varargin_2.size(0));
  if (varargin_2.size(0) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{0}; k < nc_tmp; k++) {
    sortedIndices[k] = k + 1;
  }
  internal::introsort(sortedIndices, b_this.workspace.a.size(0), b_this);
  numalloc = b_this.workspace.a.size(0);
  t.set_size(b_this.workspace.a.size(0));
  for (i = 0; i < numalloc; i++) {
    t[i] = b_this.workspace.a[i];
  }
  if (b_this.workspace.a.size(0) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{0}; k < numalloc; k++) {
    b_this.workspace.a[k] = t[sortedIndices[k] - 1];
  }
  numalloc = b_this.workspace.b.size(0);
  t.set_size(b_this.workspace.b.size(0));
  for (i = 0; i < numalloc; i++) {
    t[i] = b_this.workspace.b[i];
  }
  if (b_this.workspace.b.size(0) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{0}; k < numalloc; k++) {
    b_this.workspace.b[k] = t[sortedIndices[k] - 1];
  }
  if ((b_this.workspace.b.size(0) == 0) || (b_this.workspace.a.size(0) == 0)) {
    thism = 0;
    y.n = 0;
  } else {
    thism = b_this.workspace.b[0];
    if (b_this.workspace.b.size(0) > 2147483646) {
      check_forloop_overflow_error();
    }
    for (int k{2}; k <= numalloc; k++) {
      i = b_this.workspace.b[k - 1];
      if (thism < i) {
        thism = i;
      }
    }
    y.n = b_this.workspace.a[b_this.workspace.a.size(0) - 1];
  }
  y.m = thism;
  numalloc = varargin_2.size(0);
  if (numalloc < 1) {
    numalloc = 1;
  }
  y.d.set_size(numalloc);
  for (i = 0; i < numalloc; i++) {
    y.d[i] = 0.0;
  }
  y.maxnz = numalloc;
  if (y.n + 1 < 0) {
    rtNonNegativeError(static_cast<double>(y.n + 1), q_emlrtDCI);
  }
  y.colidx.set_size(y.n + 1);
  if (y.n + 1 < 0) {
    rtNonNegativeError(static_cast<double>(y.n + 1), q_emlrtDCI);
  }
  thism = y.n + 1;
  for (i = 0; i < thism; i++) {
    y.colidx[i] = 0;
  }
  y.colidx[0] = 1;
  y.rowidx.set_size(numalloc);
  for (i = 0; i < numalloc; i++) {
    y.rowidx[i] = 0;
  }
  numalloc = 0;
  thism = y.n;
  if (y.n > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{0}; k < thism; k++) {
    while ((numalloc + 1 <= nc_tmp) &&
           (b_this.workspace.a[numalloc] == k + 1)) {
      y.rowidx[numalloc] = b_this.workspace.b[numalloc];
      numalloc++;
    }
    y.colidx[k + 1] = numalloc + 1;
  }
  for (int k{0}; k < nc_tmp; k++) {
    y.d[k] = 1.0;
  }
  y.fillIn();
}

//
// Arguments    : const array<double, 1U> &varargin_1
//                g_sparse &y
// Return Type  : void
//
void i_sparse(const array<double, 1U> &varargin_1, g_sparse &y)
{
  int mInt_tmp;
  int numalloc;
  mInt_tmp = varargin_1.size(0);
  if (varargin_1.size(0) >= MAX_int32_T) {
    wc_rtErrorWithMessageID(cc_emlrtRTEI.fName, cc_emlrtRTEI.lineNo);
  }
  numalloc = 0;
  for (int k{0}; k < mInt_tmp; k++) {
    if (varargin_1[k] != 0.0) {
      numalloc++;
    }
  }
  y.m = varargin_1.size(0);
  if (numalloc < 1) {
    numalloc = 1;
  }
  y.maxnz = numalloc;
  y.d.set_size(numalloc);
  y.colidx.set_size(2);
  y.colidx[0] = 1;
  y.rowidx.set_size(numalloc);
  for (int k{0}; k < numalloc; k++) {
    y.d[k] = 0.0;
    y.rowidx[k] = 0;
  }
  y.rowidx[0] = 1;
  numalloc = 0;
  for (int k{0}; k < mInt_tmp; k++) {
    if (varargin_1[k] != 0.0) {
      y.rowidx[numalloc] = k + 1;
      y.d[numalloc] = 1.0;
      numalloc++;
    }
  }
  y.colidx[1] = numalloc + 1;
}

//
// Arguments    : const array<boolean_T, 2U> &varargin_1
//                d_sparse &y
// Return Type  : void
//
void j_sparse(const array<boolean_T, 2U> &varargin_1, d_sparse &y)
{
  int nInt_tmp;
  int numalloc;
  nInt_tmp = varargin_1.size(1);
  if (varargin_1.size(1) >= MAX_int32_T) {
    wc_rtErrorWithMessageID(cc_emlrtRTEI.fName, cc_emlrtRTEI.lineNo);
  }
  numalloc = 0;
  for (int k{0}; k < nInt_tmp; k++) {
    if (varargin_1[k]) {
      numalloc++;
    }
  }
  y.n = varargin_1.size(1);
  if (numalloc < 1) {
    numalloc = 1;
  }
  y.d.set_size(numalloc);
  for (int k{0}; k < numalloc; k++) {
    y.d[k] = false;
  }
  y.colidx.set_size(varargin_1.size(1) + 1);
  for (int k{0}; k <= nInt_tmp; k++) {
    y.colidx[k] = 0;
  }
  y.colidx[0] = 1;
  y.rowidx.set_size(numalloc);
  for (int k{0}; k < numalloc; k++) {
    y.rowidx[k] = 0;
  }
  y.rowidx[0] = 1;
  numalloc = 0;
  for (int k{0}; k < nInt_tmp; k++) {
    if (varargin_1[k]) {
      y.rowidx[numalloc] = 1;
      y.d[numalloc] = true;
      numalloc++;
    }
    y.colidx[k + 1] = numalloc + 1;
  }
}

} // namespace coder

//
// File trailer for sparse.cpp
//
// [EOF]
//
