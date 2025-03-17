//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: rectwin.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 04-Feb-2025 09:56:05
//

// Include Files
#include "rectwin.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include "omp.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>

// Function Declarations
static void f_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum);

static void r_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : const char *r
//                const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void f_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((outStream << "Order, ") << r) << ", must be finite.";
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
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void r_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Order must be greater than or equal to zero.";
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
// Arguments    : double n_est
//                array<double, 1U> &w
// Return Type  : void
//
namespace coder {
void rectwin(double n_est, array<double, 1U> &w)
{
  static rtRunTimeErrorInfo rc_emlrtRTEI{
      18,           // lineNo
      "check_order" // fName
  };
  static rtRunTimeErrorInfo sc_emlrtRTEI{
      22,           // lineNo
      "check_order" // fName
  };
  int n;
  if (std::isinf(n_est) || std::isnan(n_est)) {
    f_rtErrorWithMessageID("N", rc_emlrtRTEI.fName, rc_emlrtRTEI.lineNo);
  }
  if (!(n_est >= 0.0)) {
    r_rtErrorWithMessageID(sc_emlrtRTEI.fName, sc_emlrtRTEI.lineNo);
  }
  if (n_est == std::floor(n_est)) {
    n = static_cast<int>(n_est);
  } else {
    n = static_cast<int>(std::round(n_est));
  }
  w.set_size(n);
  for (int i{0}; i < n; i++) {
    w[i] = 1.0;
  }
}

} // namespace coder

//
// File trailer for rectwin.cpp
//
// [EOF]
//
