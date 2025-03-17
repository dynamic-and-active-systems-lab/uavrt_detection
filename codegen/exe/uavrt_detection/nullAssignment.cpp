//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: nullAssignment.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "nullAssignment.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include "omp.h"
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>

// Variable Definitions
static rtRunTimeErrorInfo mc_emlrtRTEI{
    85,               // lineNo
    "validate_inputs" // fName
};

// Function Declarations
static void nc_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void nc_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Matrix index is out of range for deletion.";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// Arguments    : array<char, 2U> &x
//                int idx
// Return Type  : void
//
namespace coder {
namespace internal {
void nullAssignment(array<char, 2U> &x, int idx)
{
  int nxout;
  if (idx > x.size(1)) {
    nc_rtErrorWithMessageID(mc_emlrtRTEI.fName, mc_emlrtRTEI.lineNo);
  }
  nxout = x.size(1);
  for (int k{idx}; k < nxout; k++) {
    x[k - 1] = x[k];
  }
  if (x.size(1) - 1 < 1) {
    nxout = 0;
  } else {
    nxout = x.size(1) - 1;
  }
  x.set_size(x.size(0), nxout);
}

//
// Arguments    : array<creal_T, 3U> &x
//                const array<int, 2U> &idx
// Return Type  : void
//
void nullAssignment(array<creal_T, 3U> &x, const array<int, 2U> &idx)
{
  static rtDoubleCheckInfo q_emlrtDCI{
      451,                      // lineNo
      "general_null_assignment" // fName
  };
  static rtRunTimeErrorInfo rc_emlrtRTEI{
      448,                      // lineNo
      "general_null_assignment" // fName
  };
  static rtRunTimeErrorInfo sc_emlrtRTEI{
      81,               // lineNo
      "validate_inputs" // fName
  };
  array<creal_T, 3U> b_x;
  array<boolean_T, 2U> b;
  int i;
  int i1;
  int ix0;
  int k;
  int loop_ub;
  int loop_ub_tmp_tmp;
  int nxout;
  boolean_T exitg1;
  boolean_T p;
  p = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= idx.size(1) - 1)) {
    if (idx[k] > x.size(1)) {
      p = false;
      exitg1 = true;
    } else {
      k++;
    }
  }
  if (!p) {
    nc_rtErrorWithMessageID(sc_emlrtRTEI.fName, sc_emlrtRTEI.lineNo);
  }
  i = x.size(0);
  loop_ub = x.size(1);
  i1 = x.size(2);
  b_x.set_size(i, loop_ub, i1);
  loop_ub_tmp_tmp = x.size(0) * x.size(1);
  nxout = loop_ub_tmp_tmp * x.size(2);
  for (ix0 = 0; ix0 < nxout; ix0++) {
    b_x[ix0] = x[ix0];
  }
  b.set_size(1, loop_ub);
  for (ix0 = 0; ix0 < loop_ub; ix0++) {
    b[ix0] = false;
  }
  nxout = idx.size(1);
  if (idx.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (k = 0; k < nxout; k++) {
    b[idx[k] - 1] = true;
  }
  nxout = 0;
  if (b.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (k = 0; k < loop_ub; k++) {
    nxout += b[k];
  }
  nxout = x.size(1) - nxout;
  if (nxout > x.size(1)) {
    g_rtErrorWithMessageID(rc_emlrtRTEI.fName, rc_emlrtRTEI.lineNo);
  }
  if (nxout < 0) {
    rtNonNegativeError(static_cast<double>(nxout), q_emlrtDCI);
  }
  x.set_size(x.size(0), nxout, x.size(2));
  nxout *= b_x.size(0);
  if (b_x.size(2) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int b_i{0}; b_i < i1; b_i++) {
    int iy0;
    ix0 = b_i * loop_ub_tmp_tmp;
    iy0 = b_i * nxout;
    if (loop_ub > 2147483646) {
      check_forloop_overflow_error();
    }
    for (k = 0; k < loop_ub; k++) {
      if ((k + 1 > b.size(1)) || (!b[k])) {
        if (i > 2147483646) {
          check_forloop_overflow_error();
        }
        for (int j{0}; j < i; j++) {
          x[iy0 + j] = b_x[ix0 + j];
        }
        iy0 += i;
      }
      ix0 += i;
    }
  }
}

//
// Arguments    : array<double, 1U> &x
//                const array<int, 2U> &idx
// Return Type  : void
//
void nullAssignment(array<double, 1U> &x, const array<int, 2U> &idx)
{
  static rtRunTimeErrorInfo rc_emlrtRTEI{
      181,                     // lineNo
      "onearg_null_assignment" // fName
  };
  array<boolean_T, 2U> b;
  int k;
  int k0;
  int nxin_tmp;
  int nxout;
  boolean_T exitg1;
  boolean_T p;
  p = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= idx.size(1) - 1)) {
    if (idx[k] > x.size(0)) {
      p = false;
      exitg1 = true;
    } else {
      k++;
    }
  }
  if (!p) {
    nc_rtErrorWithMessageID(mc_emlrtRTEI.fName, mc_emlrtRTEI.lineNo);
  }
  nxin_tmp = x.size(0);
  b.set_size(1, nxin_tmp);
  for (nxout = 0; nxout < nxin_tmp; nxout++) {
    b[nxout] = false;
  }
  nxout = idx.size(1);
  if (idx.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (k = 0; k < nxout; k++) {
    b[idx[k] - 1] = true;
  }
  nxout = 0;
  if (b.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (k = 0; k < nxin_tmp; k++) {
    nxout += b[k];
  }
  nxout = x.size(0) - nxout;
  k0 = -1;
  if (x.size(0) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (k = 0; k < nxin_tmp; k++) {
    if ((k + 1 > b.size(1)) || (!b[k])) {
      k0++;
      x[k0] = x[k];
    }
  }
  if (nxout > x.size(0)) {
    g_rtErrorWithMessageID(rc_emlrtRTEI.fName, rc_emlrtRTEI.lineNo);
  }
  if (nxout < 1) {
    nxout = 0;
  }
  x.set_size(nxout);
}

} // namespace internal
} // namespace coder

//
// File trailer for nullAssignment.cpp
//
// [EOF]
//
