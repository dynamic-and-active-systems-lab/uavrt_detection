//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: mpower.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "mpower.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "omp.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>

// Function Declarations
static void lb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void lb_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Domain error. To compute complex results, make at least one "
               "input complex, e.g. \'power(complex(a),b)\'.";
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
// Arguments    : double a
//                double b
// Return Type  : double
//
namespace coder {
double mpower(double a, double b)
{
  static rtRunTimeErrorInfo rc_emlrtRTEI{
      82,        // lineNo
      "fltpower" // fName
  };
  if ((a < 0.0) && (!std::isnan(b)) && (std::floor(b) != b)) {
    lb_rtErrorWithMessageID(rc_emlrtRTEI.fName, rc_emlrtRTEI.lineNo);
  }
  return rt_powd_snf(a, b);
}

} // namespace coder

//
// File trailer for mpower.cpp
//
// [EOF]
//
