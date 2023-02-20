//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: int2str.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 14:31:55
//

// Include Files
#include "int2str.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "omp.h"
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <stdio.h>
#include <string.h>
#include <string>

// Variable Definitions
static rtRunTimeErrorInfo p_emlrtRTEI{
    41,           // lineNo
    "callSprintf" // fName
};

static rtRunTimeErrorInfo q_emlrtRTEI{
    42,           // lineNo
    "callSprintf" // fName
};

static rtRunTimeErrorInfo r_emlrtRTEI{
    43,           // lineNo
    "callSprintf" // fName
};

// Function Declarations
static void b_rtErrorWithMessageID(const int i, const char *aFcnName,
                                   int aLineNum);

// Function Definitions
//
// Arguments    : const int i
//                const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void b_rtErrorWithMessageID(const int i, const char *aFcnName,
                                   int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((outStream << "Call to C sprintf failed with status ") << i) << ".";
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
// Arguments    : double xin
//                char s_data[]
//                int s_size[2]
// Return Type  : void
//
namespace coder {
void int2str(double xin, char s_data[], int s_size[2])
{
  double x;
  char st[311];
  x = std::round(xin);
  if (x == 0.0) {
    s_size[0] = 1;
    s_size[1] = 1;
    s_data[0] = '0';
  } else if (std::isinf(x)) {
    s_size[0] = 1;
    s_size[1] = 3;
    s_data[0] = 'I';
    s_data[1] = 'n';
    s_data[2] = 'f';
  } else if (std::isnan(x)) {
    s_size[0] = 1;
    s_size[1] = 3;
    s_data[0] = 'N';
    s_data[1] = 'a';
    s_data[2] = 'N';
  } else {
    int resCount;
    resCount = sprintf(&st[0], "%.0f", x);
    if (resCount < 0) {
      b_rtErrorWithMessageID(resCount, p_emlrtRTEI.fName, p_emlrtRTEI.lineNo);
    }
    if (resCount > 310) {
      j_rtErrorWithMessageID(q_emlrtRTEI.fName, q_emlrtRTEI.lineNo);
    }
    if (resCount >
        static_cast<int>(std::floor(std::log10(std::abs(x))) + 1.0)) {
      j_rtErrorWithMessageID(r_emlrtRTEI.fName, r_emlrtRTEI.lineNo);
    }
    s_size[0] = 1;
    s_size[1] = resCount;
    if (resCount - 1 >= 0) {
      std::copy(&st[0], &st[resCount], &s_data[0]);
    }
  }
}

//
// Arguments    : int xin
//                char s_data[]
//                int s_size[2]
// Return Type  : void
//
void int2str(int xin, char s_data[], int s_size[2])
{
  double b_xin;
  int resCount;
  char st[12];
  resCount = sprintf(&st[0], "%d", xin);
  if (resCount < 0) {
    b_rtErrorWithMessageID(resCount, p_emlrtRTEI.fName, p_emlrtRTEI.lineNo);
  }
  if (resCount > 11) {
    j_rtErrorWithMessageID(q_emlrtRTEI.fName, q_emlrtRTEI.lineNo);
  }
  if (xin == 0) {
    b_xin = 1.0;
  } else {
    b_xin = std::floor(std::log10(std::abs(static_cast<double>(xin)))) + 1.0;
  }
  if (resCount > static_cast<int>(b_xin)) {
    j_rtErrorWithMessageID(r_emlrtRTEI.fName, r_emlrtRTEI.lineNo);
  }
  s_size[0] = 1;
  s_size[1] = resCount;
  if (resCount - 1 >= 0) {
    std::copy(&st[0], &st[resCount], &s_data[0]);
  }
}

} // namespace coder

//
// File trailer for int2str.cpp
//
// [EOF]
//
