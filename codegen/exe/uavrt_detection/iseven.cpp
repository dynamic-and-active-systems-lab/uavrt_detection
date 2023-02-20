//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: iseven.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 14:31:55
//

// Include Files
#include "iseven.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_types.h"
#include "omp.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string.h>
#include <string>

// Function Declarations
static void u_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void u_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Argument must be integer-valued.";
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
// Arguments    : double x
// Return Type  : boolean_T
//
namespace coder {
namespace signalwavelet {
namespace internal {
boolean_T iseven(double x)
{
  static rtRunTimeErrorInfo kb_emlrtRTEI{
      12,      // lineNo
      "iseven" // fName
  };
  double r;
  if (x - std::trunc(x) != 0.0) {
    u_rtErrorWithMessageID(kb_emlrtRTEI.fName, kb_emlrtRTEI.lineNo);
  }
  if (std::isnan(x) || std::isinf(x)) {
    r = rtNaN;
  } else if (x == 0.0) {
    r = 0.0;
  } else {
    r = std::fmod(x, 2.0);
    if (r == 0.0) {
      r = 0.0;
    } else if (x < 0.0) {
      r += 2.0;
    }
  }
  return r == 0.0;
}

} // namespace internal
} // namespace signalwavelet
} // namespace coder

//
// File trailer for iseven.cpp
//
// [EOF]
//
