//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: any1.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "any1.h"
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
// Arguments    : const d_sparse &x
//                e_sparse &y
// Return Type  : void
//
namespace coder {
void any(const d_sparse &x, e_sparse &y)
{
  c_anonymous_function b_this;
  array<int, 2U> b_y;
  array<int, 1U> xrowidx;
  array<int, 1U> xrowidxPerm;
  if (x.n == 0) {
    y.colidx.set_size(2);
    y.colidx[0] = 1;
    y.colidx[1] = 1;
    y.d.set_size(1);
    y.d[0] = false;
    y.rowidx.set_size(1);
    y.rowidx[0] = 1;
  } else if (x.n != 0) {
    int xnnz_tmp;
    int yk;
    int ynnz;
    xnnz_tmp = x.colidx[x.colidx.size(0) - 1];
    yk = 0;
    if (xnnz_tmp - 1 > 2147483646) {
      check_forloop_overflow_error();
    }
    for (int k{0}; k <= xnnz_tmp - 2; k++) {
      if (yk == 0) {
        yk = 1;
      }
    }
    ynnz = 0;
    if (yk > 0) {
      ynnz = 1;
    } else {
      yk = 1;
    }
    y.d.set_size(1);
    y.d[0] = true;
    y.rowidx.set_size(1);
    y.rowidx[0] = yk;
    y.colidx.set_size(2);
    y.colidx[0] = 1;
    y.colidx[1] = ynnz + 1;
  } else {
    int k;
    int n_tmp;
    int xnnz_tmp;
    int yk;
    int ynnz;
    xnnz_tmp = x.colidx[x.colidx.size(0) - 1] - 1;
    if (xnnz_tmp < 1) {
      ynnz = 0;
    } else {
      ynnz = xnnz_tmp;
    }
    if (ynnz < 1) {
      n_tmp = 0;
    } else {
      n_tmp = ynnz;
    }
    b_y.set_size(1, n_tmp);
    if (n_tmp > 0) {
      b_y[0] = 1;
      yk = 1;
      if (n_tmp > 2147483646) {
        check_forloop_overflow_error();
      }
      for (k = 2; k <= n_tmp; k++) {
        yk++;
        b_y[k - 1] = yk;
      }
    }
    b_this.workspace.x.set_size(ynnz);
    for (k = 0; k < ynnz; k++) {
      b_this.workspace.x[k] = x.rowidx[k];
    }
    xrowidxPerm.set_size(n_tmp);
    for (k = 0; k < n_tmp; k++) {
      xrowidxPerm[k] = b_y[k];
    }
    internal::introsort(xrowidxPerm, ynnz, b_this);
    ynnz = xrowidxPerm.size(0);
    xrowidx.set_size(xrowidxPerm.size(0));
    for (k = 0; k < ynnz; k++) {
      xrowidx[k] = x.rowidx[xrowidxPerm[k] - 1];
    }
    ynnz = 0;
    k = 0;
    while (k + 1 <= xnnz_tmp) {
      yk = xrowidx[k];
      ynnz++;
      xrowidx[ynnz - 1] = xrowidx[k];
      while ((k + 1 <= xnnz_tmp) && (xrowidx[k] == yk)) {
        k++;
      }
    }
    yk = ynnz;
    if (ynnz < 1) {
      yk = 1;
    }
    y.rowidx.set_size(yk);
    y.colidx.set_size(2);
    y.colidx[0] = 1;
    y.colidx[1] = ynnz + 1;
    if (ynnz > 2147483646) {
      check_forloop_overflow_error();
    }
    for (k = 0; k < ynnz; k++) {
      y.rowidx[k] = xrowidx[k];
    }
    y.d.set_size(yk);
    for (k = 0; k < yk; k++) {
      y.d[k] = true;
    }
  }
}

//
// Arguments    : const boolean_T x[2]
// Return Type  : boolean_T
//
boolean_T b_any(const boolean_T x[2])
{
  int k;
  boolean_T exitg1;
  boolean_T y;
  y = false;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 2)) {
    if (x[k]) {
      y = true;
      exitg1 = true;
    } else {
      k++;
    }
  }
  return y;
}

//
// Arguments    : const array<boolean_T, 2U> &x
//                array<boolean_T, 1U> &y
// Return Type  : void
//
void c_any(const array<boolean_T, 2U> &x, array<boolean_T, 1U> &y)
{
  int i1;
  int i2;
  int loop_ub;
  loop_ub = x.size(0);
  y.set_size(x.size(0));
  for (i2 = 0; i2 < loop_ub; i2++) {
    y[i2] = false;
  }
  i2 = (x.size(1) - 1) * x.size(0);
  i1 = 1;
  if (x.size(0) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int j{0}; j < loop_ub; j++) {
    int i1_tmp;
    int ix;
    boolean_T exitg1;
    boolean_T overflow;
    i1_tmp = i1;
    i1++;
    i2++;
    if ((loop_ub == 0) || (i1_tmp > i2)) {
      overflow = false;
    } else {
      overflow = (i2 > MAX_int32_T - loop_ub);
    }
    if (loop_ub == 0) {
      cc_rtErrorWithMessageID(ac_emlrtRTEI.fName, ac_emlrtRTEI.lineNo);
    }
    if (overflow) {
      check_forloop_overflow_error();
    }
    ix = i1_tmp;
    exitg1 = false;
    while ((!exitg1) && (ix <= i2)) {
      if (x[ix - 1]) {
        y[i1_tmp - 1] = true;
        exitg1 = true;
      } else {
        ix += loop_ub;
      }
    }
  }
}

} // namespace coder

//
// File trailer for any1.cpp
//
// [EOF]
//
