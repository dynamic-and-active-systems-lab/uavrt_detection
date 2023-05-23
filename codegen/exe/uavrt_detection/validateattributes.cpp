//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: validateattributes.cpp
//
<<<<<<< HEAD
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 23-May-2023 12:05:02
=======
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Apr-2023 11:47:02
>>>>>>> 3930a1e557481905555f2756f2f70ac82e87beba
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
  static rtRunTimeErrorInfo qc_emlrtRTEI{
      22,           // lineNo
      27,           // colNo
      "validatege", // fName
      "/Applications/MATLAB_R2023a.app/toolbox/eml/eml/+coder/+internal/"
      "+valattr/validatege.m" // pName
  };
  if (std::isinf(a) || std::isnan(a) || (!(std::floor(a) == a))) {
    j_rtErrorWithMessageID("FFTLength", cb_emlrtRTEI.fName,
                           cb_emlrtRTEI.lineNo);
  }
  if (a < 0.0) {
    e_rtErrorWithMessageID("FFTLength", q_emlrtRTEI.fName, q_emlrtRTEI.lineNo);
  }
  if (!(a >= attributesMixed_f9)) {
    rtErrorWithMessageID("FFTLength", ">=", "NaN", qc_emlrtRTEI.fName,
                         qc_emlrtRTEI.lineNo);
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
    g_rtErrorWithMessageID("Window", v_emlrtRTEI.fName, v_emlrtRTEI.lineNo);
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
    i_rtErrorWithMessageID("Window", x_emlrtRTEI.fName, x_emlrtRTEI.lineNo);
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
    h_rtErrorWithMessageID("Window", w_emlrtRTEI.fName, w_emlrtRTEI.lineNo);
  }
}

//
// Arguments    : double a
// Return Type  : void
//
void validateattributes(double a)
{
  static rtRunTimeErrorInfo qc_emlrtRTEI{
      22,           // lineNo
      27,           // colNo
      "validategt", // fName
      "/Applications/MATLAB_R2023a.app/toolbox/eml/eml/+coder/+internal/"
      "+valattr/validategt.m" // pName
  };
  if (std::isinf(a) || std::isnan(a) || (!(std::floor(a) == a))) {
    j_rtErrorWithMessageID("WindowLength", cb_emlrtRTEI.fName,
                           cb_emlrtRTEI.lineNo);
  }
  if (a < 0.0) {
    e_rtErrorWithMessageID("WindowLength", q_emlrtRTEI.fName,
                           q_emlrtRTEI.lineNo);
  }
  if (!(a > 1.0)) {
    rtErrorWithMessageID("WindowLength", ">", "1", qc_emlrtRTEI.fName,
                         qc_emlrtRTEI.lineNo);
  }
}

//
// Arguments    : double a
//                double attributesMixed_f11
// Return Type  : void
//
void validateattributes(double a, double attributesMixed_f11)
{
  static rtRunTimeErrorInfo qc_emlrtRTEI{
      22,           // lineNo
      27,           // colNo
      "validatelt", // fName
      "/Applications/MATLAB_R2023a.app/toolbox/eml/eml/+coder/+internal/"
      "+valattr/validatelt.m" // pName
  };
  if (std::isinf(a) || std::isnan(a) || (!(std::floor(a) == a))) {
    j_rtErrorWithMessageID("OverlapLength", cb_emlrtRTEI.fName,
                           cb_emlrtRTEI.lineNo);
  }
  if (a < 0.0) {
    e_rtErrorWithMessageID("OverlapLength", q_emlrtRTEI.fName,
                           q_emlrtRTEI.lineNo);
  }
  if (!(a < attributesMixed_f11)) {
    rtErrorWithMessageID("OverlapLength", "<", "NaN", qc_emlrtRTEI.fName,
                         qc_emlrtRTEI.lineNo);
  }
}

} // namespace coder

//
// File trailer for validateattributes.cpp
//
// [EOF]
//
