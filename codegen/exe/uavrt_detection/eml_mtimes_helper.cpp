//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: eml_mtimes_helper.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "eml_mtimes_helper.h"
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

// Function Declarations
static void tb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void tb_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream
      << "Inner dimensions must agree. Generated code for a general matrix "
         "multiplication at this call site. If this should have been a sc"
         "alar times a variable-size matrix, the scalar input must be "
         "fixed-size.";
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
// Arguments    : const array<creal_T, 2U> &a
//                const array<creal_T, 2U> &b
//                int innerDimA
//                int innerDimB
// Return Type  : void
//
namespace coder {
void dynamic_size_checks(const array<creal_T, 2U> &a,
                         const array<creal_T, 2U> &b, int innerDimA,
                         int innerDimB)
{
  static rtRunTimeErrorInfo rc_emlrtRTEI{
      138,                  // lineNo
      "dynamic_size_checks" // fName
  };
  static rtRunTimeErrorInfo sc_emlrtRTEI{
      133,                  // lineNo
      "dynamic_size_checks" // fName
  };
  if (innerDimA != innerDimB) {
    if (((a.size(0) == 1) && (a.size(1) == 1)) ||
        ((b.size(0) == 1) && (b.size(1) == 1))) {
      tb_rtErrorWithMessageID(sc_emlrtRTEI.fName, sc_emlrtRTEI.lineNo);
    } else {
      sb_rtErrorWithMessageID(rc_emlrtRTEI.fName, rc_emlrtRTEI.lineNo);
    }
  }
}

} // namespace coder

//
// File trailer for eml_mtimes_helper.cpp
//
// [EOF]
//
