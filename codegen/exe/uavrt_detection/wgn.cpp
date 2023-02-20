//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: wgn.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 14:31:55
//

// Include Files
#include "wgn.h"
#include "randn.h"
#include "rt_nonfinite.h"
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
static void eb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void eb_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "In linear mode, the required noise power must be >= 0.";
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
// Arguments    : creal_T y[1000]
// Return Type  : void
//
namespace coder {
void wgn(creal_T y[1000])
{
  static const char b_cv[128]{
      '\x00',   '\x01', '\x02', '\x03', '\x04', '\x05', '\x06', '\x07', '\x08',
      '	', '\x0a', '\x0b', '\x0c', '\x0d', '\x0e', '\x0f', '\x10', '\x11',
      '\x12',   '\x13', '\x14', '\x15', '\x16', '\x17', '\x18', '\x19', '\x1a',
      '\x1b',   '\x1c', '\x1d', '\x1e', '\x1f', ' ',    '!',    '\"',   '#',
      '$',      '%',    '&',    '\'',   '(',    ')',    '*',    '+',    ',',
      '-',      '.',    '/',    '0',    '1',    '2',    '3',    '4',    '5',
      '6',      '7',    '8',    '9',    ':',    ';',    '<',    '=',    '>',
      '?',      '@',    'a',    'b',    'c',    'd',    'e',    'f',    'g',
      'h',      'i',    'j',    'k',    'l',    'm',    'n',    'o',    'p',
      'q',      'r',    's',    't',    'u',    'v',    'w',    'x',    'y',
      'z',      '[',    '\\',   ']',    '^',    '_',    '`',    'a',    'b',
      'c',      'd',    'e',    'f',    'g',    'h',    'i',    'j',    'k',
      'l',      'm',    'n',    'o',    'p',    'q',    'r',    's',    't',
      'u',      'v',    'w',    'x',    'y',    'z',    '{',    '|',    '}',
      '~',      '\x7f'};
  static const char b[7]{'c', 'o', 'm', 'p', 'l', 'e', 'x'};
  static const char cv2[7]{'c', 'o', 'm', 'p', 'l', 'e', 'x'};
  static const char b_b[6]{'l', 'i', 'n', 'e', 'a', 'r'};
  static const char b_cv1[6]{'l', 'i', 'n', 'e', 'a', 'r'};
  double noisePower;
  int exitg1;
  int i;
  char cplxMode_data[7];
  char switch_expression_data[6];
  char x_data[6];
  boolean_T b_bool;
  for (i = 0; i < 7; i++) {
    cplxMode_data[i] = b[i];
  }
  for (i = 0; i < 6; i++) {
    x_data[i] = b_b[i];
    switch_expression_data[i] = b_cv[static_cast<int>(x_data[i])];
  }
  b_bool = false;
  i = 0;
  do {
    exitg1 = 0;
    if (i < 6) {
      if (switch_expression_data[i] != b_cv1[i]) {
        exitg1 = 1;
      } else {
        i++;
      }
    } else {
      b_bool = true;
      exitg1 = 1;
    }
  } while (exitg1 == 0);
  if (b_bool) {
    i = 0;
  } else {
    i = -1;
  }
  if (i == 0) {
    noisePower = 1.0;
  } else {
    noisePower = 0.0012589254117941675;
  }
  b_bool = false;
  i = 0;
  do {
    exitg1 = 0;
    if (i < 7) {
      if (cplxMode_data[i] != cv2[i]) {
        exitg1 = 1;
      } else {
        i++;
      }
    } else {
      b_bool = true;
      exitg1 = 1;
    }
  } while (exitg1 == 0);
  if (b_bool) {
    double c_b[1000];
    double dv[1000];
    randn(c_b);
    noisePower = std::sqrt(noisePower / 2.0);
    randn(dv);
    for (i = 0; i < 1000; i++) {
      double d;
      d = c_b[i];
      y[i].re = noisePower * (dv[i] + 0.0 * d);
      y[i].im = noisePower * d;
    }
  } else {
    double c_b[1000];
    noisePower = std::sqrt(noisePower);
    randn(c_b);
    for (i = 0; i < 1000; i++) {
      y[i].re = noisePower * c_b[i];
      y[i].im = 0.0;
    }
  }
}

//
// Arguments    : double varargin_1
//                double varargin_3
//                creal_T y_data[]
//                int y_size[2]
// Return Type  : void
//
void wgn(double varargin_1, double varargin_3, creal_T y_data[], int y_size[2])
{
  static rtEqualityCheckInfo c_emlrtECI{
      2,                                                      // nDims
      223,                                                    // lineNo
      38,                                                     // colNo
      "wgn",                                                  // fName
      "C:\\Program Files\\MATLAB\\toolbox\\comm\\comm\\wgn.m" // pName
  };
  static rtRunTimeErrorInfo kb_emlrtRTEI{
      173,  // lineNo
      "wgn" // fName
  };
  static const char b_b[7]{'c', 'o', 'm', 'p', 'l', 'e', 'x'};
  static const char b_cv1[7]{'c', 'o', 'm', 'p', 'l', 'e', 'x'};
  static const char b[6]{'l', 'i', 'n', 'e', 'a', 'r'};
  static const char b_cv[6]{'l', 'i', 'n', 'e', 'a', 'r'};
  double b_data[100];
  double noisePower;
  int tmp_size[2];
  int exitg1;
  int kstr;
  char cplxMode_data;
  char pMode_data;
  boolean_T b_bool;
  for (kstr = 0; kstr < 6; kstr++) {
    pMode_data = b[kstr];
  }
  for (kstr = 0; kstr < 7; kstr++) {
    cplxMode_data = b_b[kstr];
  }
  b_bool = false;
  kstr = 0;
  do {
    exitg1 = 0;
    if (kstr < 6) {
      if (pMode_data != b_cv[kstr]) {
        exitg1 = 1;
      } else {
        kstr++;
      }
    } else {
      b_bool = true;
      exitg1 = 1;
    }
  } while (exitg1 == 0);
  if (b_bool && (varargin_3 < 0.0)) {
    eb_rtErrorWithMessageID(kb_emlrtRTEI.fName, kb_emlrtRTEI.lineNo);
  }
  noisePower = rt_powd_snf(10.0, (varargin_3 - 30.0) / 10.0);
  b_bool = false;
  kstr = 0;
  do {
    exitg1 = 0;
    if (kstr < 7) {
      if (cplxMode_data != b_cv1[kstr]) {
        exitg1 = 1;
      } else {
        kstr++;
      }
    } else {
      b_bool = true;
      exitg1 = 1;
    }
  } while (exitg1 == 0);
  if (b_bool) {
    int b_size[2];
    int loop_ub;
    randn(varargin_1, tmp_size);
    randn(varargin_1, b_size);
    y_size[0] = b_size[0];
    y_size[1] = 100;
    loop_ub = b_size[0] * 100;
    for (kstr = 0; kstr < loop_ub; kstr++) {
      double d;
      d = b_data[kstr];
      y_data[kstr].re = d * 0.0;
      y_data[kstr].im = d;
    }
    rtSizeEqNDCheck(&tmp_size[0], &y_size[0], &c_emlrtECI);
    noisePower = std::sqrt(noisePower / 2.0);
    loop_ub = tmp_size[0] * 100;
    y_size[0] = tmp_size[0];
    y_size[1] = 100;
    for (kstr = 0; kstr < loop_ub; kstr++) {
      y_data[kstr].re = noisePower * (b_data[kstr] + y_data[kstr].re);
      y_data[kstr].im *= noisePower;
    }
  } else {
    int b_size[2];
    int loop_ub;
    noisePower = std::sqrt(noisePower);
    randn(varargin_1, b_size);
    y_size[0] = b_size[0];
    y_size[1] = 100;
    loop_ub = b_size[0] * 100;
    for (kstr = 0; kstr < loop_ub; kstr++) {
      y_data[kstr].re = noisePower * b_data[kstr];
      y_data[kstr].im = 0.0;
    }
  }
}

} // namespace coder

//
// File trailer for wgn.cpp
//
// [EOF]
//
