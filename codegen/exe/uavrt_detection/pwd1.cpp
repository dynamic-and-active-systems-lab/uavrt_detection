//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: pwd1.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 04-Feb-2025 09:56:05
//

// Include Files
#include "pwd1.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include "coder_fileops.h"
#include "omp.h"
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>

// Function Declarations
static void b_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum);

static void n_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : const char *r
//                const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void b_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((outStream
    << "To generate code, in configuration settings, enable dynamic memory "
       "allocation and support for variable-size arrays/signals. To p"
       "erform Simulink simulation, enable dynamic memory allocation only. "
       "Alternately, remove the function \'")
   << r)
      << "\'.";
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
static void n_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream
      << "Unable to access current directory or directory no longer exists.";
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
// Arguments    : array<char, 2U> &wd
// Return Type  : void
//
namespace coder {
void pwd(array<char, 2U> &wd)
{
  static rtRunTimeErrorInfo rc_emlrtRTEI{
      23,                          // lineNo
      "CoderFileOperationsAPI/pwd" // fName
  };
  static rtRunTimeErrorInfo sc_emlrtRTEI{
      30,                          // lineNo
      "CoderFileOperationsAPI/pwd" // fName
  };
  array<char, 2U> wdTemp;
  int fileNameMax;
  fileNameMax = coderGetLenghtOfCwd();
  if (fileNameMax == -2) {
    n_rtErrorWithMessageID(rc_emlrtRTEI.fName, rc_emlrtRTEI.lineNo);
  }
  if (fileNameMax + 1 < 0) {
    rtNonNegativeError(static_cast<double>(fileNameMax + 1), emlrtDCI);
  }
  wdTemp.set_size(1, fileNameMax + 1);
  fileNameMax = coderGetCurrentDirectory(&wdTemp[0], fileNameMax + 1);
  if (fileNameMax == -1) {
    b_rtErrorWithMessageID("pwd", sc_emlrtRTEI.fName, sc_emlrtRTEI.lineNo);
  }
  if (fileNameMax < 1) {
    fileNameMax = 0;
  }
  wd.set_size(1, fileNameMax);
  for (int i{0}; i < fileNameMax; i++) {
    wd[i] = wdTemp[i];
  }
}

} // namespace coder

//
// File trailer for pwd1.cpp
//
// [EOF]
//
