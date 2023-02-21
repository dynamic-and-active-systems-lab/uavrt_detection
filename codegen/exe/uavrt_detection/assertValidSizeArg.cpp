//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: assertValidSizeArg.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 18:16:21
//

// Include Files
#include "assertValidSizeArg.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
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
static void sc_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void sc_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((((outStream << "Size vector must be a row vector with finite integer "
                   "elements in the range: ")
     << MIN_int32_T)
    << " to ")
   << MAX_int32_T)
      << ".";
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
// Arguments    : const double varargin_1[2]
// Return Type  : void
//
namespace coder {
namespace internal {
void assertValidSizeArg(const double varargin_1[2])
{
  static rtRunTimeErrorInfo tc_emlrtRTEI{
      49,                  // lineNo
      "assertValidSizeArg" // fName
  };
  double b_varargin_1;
  int k;
  boolean_T exitg1;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 2)) {
    if ((varargin_1[k] != varargin_1[k]) || std::isinf(varargin_1[k])) {
      sc_rtErrorWithMessageID(tc_emlrtRTEI.fName, tc_emlrtRTEI.lineNo);
    } else {
      k++;
    }
  }
  if (varargin_1[0] <= 0.0) {
    b_varargin_1 = 0.0;
  } else {
    b_varargin_1 = varargin_1[0];
  }
  if (varargin_1[1] <= 0.0) {
    b_varargin_1 = 0.0;
  } else {
    b_varargin_1 *= varargin_1[1];
  }
  if (!(b_varargin_1 <= 2.147483647E+9)) {
    m_rtErrorWithMessageID(o_emlrtRTEI.fName, o_emlrtRTEI.lineNo);
  }
}

//
// Arguments    : double varargin_2
// Return Type  : void
//
void assertValidSizeArg(double varargin_2)
{
  double b_varargin_2;
  if ((varargin_2 != std::floor(varargin_2)) || std::isinf(varargin_2) ||
      (varargin_2 < -2.147483648E+9) || (varargin_2 > 2.147483647E+9)) {
    c_rtErrorWithMessageID(MIN_int32_T, ob_emlrtRTEI.fName,
                           ob_emlrtRTEI.lineNo);
  }
  if (varargin_2 <= 0.0) {
    b_varargin_2 = 0.0;
  } else {
    b_varargin_2 = varargin_2;
  }
  if (!(b_varargin_2 <= 2.147483647E+9)) {
    m_rtErrorWithMessageID(o_emlrtRTEI.fName, o_emlrtRTEI.lineNo);
  }
}

} // namespace internal
} // namespace coder

//
// File trailer for assertValidSizeArg.cpp
//
// [EOF]
//
