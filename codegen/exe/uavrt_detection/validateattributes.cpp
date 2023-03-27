//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: validateattributes.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 27-Mar-2023 15:47:21
//

// Include Files
#include "validateattributes.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include "omp.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string.h>
#include <string>

// Function Declarations
static void rtErrorWithMessageID(const char *r, const char *r1, const char *r2,
                                 const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : const char *r
//                const char *r1
//                const char *r2
//                const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void rtErrorWithMessageID(const char *r, const char *r1, const char *r2,
                                 const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((((((outStream << "Expected ") << r) << " to be a scalar with value ") << r1)
    << " ")
   << r2)
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
// Arguments    : double a
//                double attributesMixed_f9
// Return Type  : void
//
namespace coder {
void b_validateattributes(double a, double attributesMixed_f9)
{
  static rtRunTimeErrorInfo wc_emlrtRTEI{
      22,          // lineNo
      "validatege" // fName
  };
  if (std::isinf(a) || std::isnan(a) || (!(std::floor(a) == a))) {
    j_rtErrorWithMessageID("FFTLength", hb_emlrtRTEI.fName,
                           hb_emlrtRTEI.lineNo);
  }
  if (a < 0.0) {
    e_rtErrorWithMessageID("FFTLength", v_emlrtRTEI.fName, v_emlrtRTEI.lineNo);
  }
  if (!(a >= attributesMixed_f9)) {
    rtErrorWithMessageID("FFTLength", ">=", "NaN", wc_emlrtRTEI.fName,
                         wc_emlrtRTEI.lineNo);
  }
}

//
// Arguments    : const ::coder::array<double, 1U> &a
// Return Type  : void
//
void validateattributes(const ::coder::array<double, 1U> &a)
{
  int k;
  boolean_T exitg1;
  boolean_T p;
  if (a.size(0) == 0) {
    i_rtErrorWithMessageID("Window", gb_emlrtRTEI.fName, gb_emlrtRTEI.lineNo);
  }
  p = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= a.size(0) - 1)) {
    if ((!std::isinf(a[k])) && (!std::isnan(a[k]))) {
      k++;
    } else {
      p = false;
      exitg1 = true;
    }
  }
  if (!p) {
    g_rtErrorWithMessageID("Window", eb_emlrtRTEI.fName, eb_emlrtRTEI.lineNo);
  }
  p = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= a.size(0) - 1)) {
    if (!std::isnan(a[k])) {
      k++;
    } else {
      p = false;
      exitg1 = true;
    }
  }
  if (!p) {
    h_rtErrorWithMessageID("Window", fb_emlrtRTEI.fName, fb_emlrtRTEI.lineNo);
  }
}

//
// Arguments    : double a
// Return Type  : void
//
void validateattributes(double a)
{
  static rtRunTimeErrorInfo wc_emlrtRTEI{
      22,          // lineNo
      "validategt" // fName
  };
  if (std::isinf(a) || std::isnan(a) || (!(std::floor(a) == a))) {
    j_rtErrorWithMessageID("WindowLength", hb_emlrtRTEI.fName,
                           hb_emlrtRTEI.lineNo);
  }
  if (a < 0.0) {
    e_rtErrorWithMessageID("WindowLength", v_emlrtRTEI.fName,
                           v_emlrtRTEI.lineNo);
  }
  if (!(a > 1.0)) {
    rtErrorWithMessageID("WindowLength", ">", "1", wc_emlrtRTEI.fName,
                         wc_emlrtRTEI.lineNo);
  }
}

//
// Arguments    : double a
//                double attributesMixed_f11
// Return Type  : void
//
void validateattributes(double a, double attributesMixed_f11)
{
  static rtRunTimeErrorInfo wc_emlrtRTEI{
      22,          // lineNo
      "validatelt" // fName
  };
  if (std::isinf(a) || std::isnan(a) || (!(std::floor(a) == a))) {
    j_rtErrorWithMessageID("OverlapLength", hb_emlrtRTEI.fName,
                           hb_emlrtRTEI.lineNo);
  }
  if (a < 0.0) {
    e_rtErrorWithMessageID("OverlapLength", v_emlrtRTEI.fName,
                           v_emlrtRTEI.lineNo);
  }
  if (!(a < attributesMixed_f11)) {
    rtErrorWithMessageID("OverlapLength", "<", "NaN", wc_emlrtRTEI.fName,
                         wc_emlrtRTEI.lineNo);
  }
}

} // namespace coder

//
// File trailer for validateattributes.cpp
//
// [EOF]
//
