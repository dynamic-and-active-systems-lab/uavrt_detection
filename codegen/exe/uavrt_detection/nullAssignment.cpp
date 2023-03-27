//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: nullAssignment.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 27-Mar-2023 15:47:21
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
#include <string.h>
#include <string>

// Function Declarations
static void jc_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void jc_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
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
// Arguments    : ::coder::array<char, 2U> &x
//                int idx
// Return Type  : void
//
namespace coder {
namespace internal {
void nullAssignment(::coder::array<char, 2U> &x, int idx)
{
  static rtRunTimeErrorInfo wc_emlrtRTEI{
      85,               // lineNo
      "validate_inputs" // fName
  };
  int nxin;
  int nxout;
  if (idx > x.size(1)) {
    jc_rtErrorWithMessageID(wc_emlrtRTEI.fName, wc_emlrtRTEI.lineNo);
  }
  nxin = x.size(1);
  nxout = x.size(1) - 1;
  for (int k{idx}; k <= nxout; k++) {
    x[k - 1] = x[k];
  }
  if (nxout < 1) {
    nxout = 0;
  } else {
    nxout = nxin - 1;
  }
  x.set_size(x.size(0), nxout);
}

//
// Arguments    : ::coder::array<creal_T, 3U> &x
//                const ::coder::array<int, 2U> &idx
// Return Type  : void
//
void nullAssignment(::coder::array<creal_T, 3U> &x,
                    const ::coder::array<int, 2U> &idx)
{
  static rtDoubleCheckInfo
      t_emlrtDCI{
          452,                       // lineNo
          58,                        // colNo
          "general_null_assignment", // fName
          "C:\\Program "
          "Files\\MATLAB\\toolbox\\eml\\eml\\+coder\\+internal\\nullAssignment."
          "m", // pName
          4    // checkKind
      };
  static rtRunTimeErrorInfo wc_emlrtRTEI{
      81,               // lineNo
      "validate_inputs" // fName
  };
  static rtRunTimeErrorInfo xc_emlrtRTEI{
      449,                      // lineNo
      "general_null_assignment" // fName
  };
  array<creal_T, 3U> b_x;
  array<boolean_T, 2U> b;
  int k;
  int nxout;
  int sz_idx_2;
  int vlen;
  int vstride;
  int xpagesize;
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
    jc_rtErrorWithMessageID(wc_emlrtRTEI.fName, wc_emlrtRTEI.lineNo);
  }
  b_x.set_size(x.size(0), x.size(1), x.size(2));
  sz_idx_2 = x.size(0) * x.size(1) * x.size(2);
  for (nxout = 0; nxout < sz_idx_2; nxout++) {
    b_x[nxout] = x[nxout];
  }
  vlen = x.size(1);
  b.set_size(1, x.size(1));
  sz_idx_2 = x.size(1);
  for (nxout = 0; nxout < sz_idx_2; nxout++) {
    b[nxout] = false;
  }
  sz_idx_2 = idx.size(1);
  if (idx.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (k = 0; k < sz_idx_2; k++) {
    b[idx[k] - 1] = true;
  }
  nxout = 0;
  sz_idx_2 = b.size(1);
  if (b.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (k = 0; k < sz_idx_2; k++) {
    nxout += b[k];
  }
  nxout = x.size(1) - nxout;
  sz_idx_2 = x.size(2);
  if (nxout > x.size(1)) {
    i_rtErrorWithMessageID(xc_emlrtRTEI.fName, xc_emlrtRTEI.lineNo);
  }
  if (nxout < 0) {
    rtNonNegativeError(static_cast<double>(nxout), &t_emlrtDCI);
  }
  x.set_size(x.size(0), nxout, sz_idx_2);
  vstride = b_x.size(0);
  xpagesize = vlen * b_x.size(0);
  sz_idx_2 = nxout * b_x.size(0);
  nxout = b_x.size(2);
  if (b_x.size(2) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int i{0}; i < nxout; i++) {
    int ix0;
    int iy0;
    ix0 = i * xpagesize;
    iy0 = i * sz_idx_2;
    if (vlen > 2147483646) {
      check_forloop_overflow_error();
    }
    for (k = 0; k < vlen; k++) {
      if ((k + 1 > b.size(1)) || (!b[k])) {
        if (vstride > 2147483646) {
          check_forloop_overflow_error();
        }
        for (int j{0}; j < vstride; j++) {
          x[iy0 + j] = b_x[ix0 + j];
        }
        iy0 += vstride;
      }
      ix0 += vstride;
    }
  }
}

} // namespace internal
} // namespace coder

//
// File trailer for nullAssignment.cpp
//
// [EOF]
//
