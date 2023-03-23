//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: wgn.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 23-Mar-2023 12:56:08
//

// Include Files
#include "wgn.h"
#include "randn.h"
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

// Variable Definitions
static const char cv[128]{
    '\x00', '\x01', '\x02', '\x03', '\x04', '\x05', '\x06', '\x07', '\x08',
    '	', '\x0a', '\x0b', '\x0c', '\x0d', '\x0e', '\x0f', '\x10', '\x11',
    '\x12', '\x13', '\x14', '\x15', '\x16', '\x17', '\x18', '\x19', '\x1a',
    '\x1b', '\x1c', '\x1d', '\x1e', '\x1f', ' ',    '!',    '\"',   '#',
    '$',    '%',    '&',    '\'',   '(',    ')',    '*',    '+',    ',',
    '-',    '.',    '/',    '0',    '1',    '2',    '3',    '4',    '5',
    '6',    '7',    '8',    '9',    ':',    ';',    '<',    '=',    '>',
    '?',    '@',    'a',    'b',    'c',    'd',    'e',    'f',    'g',
    'h',    'i',    'j',    'k',    'l',    'm',    'n',    'o',    'p',
    'q',    'r',    's',    't',    'u',    'v',    'w',    'x',    'y',
    'z',    '[',    '\\',   ']',    '^',    '_',    '`',    'a',    'b',
    'c',    'd',    'e',    'f',    'g',    'h',    'i',    'j',    'k',
    'l',    'm',    'n',    'o',    'p',    'q',    'r',    's',    't',
    'u',    'v',    'w',    'x',    'y',    'z',    '{',    '|',    '}',
    '~',    '\x7f'};

// Function Declarations
static void nb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void nb_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "The required dimensions must be real, integer scalars > 1.";
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
  static const char b[7]{'c', 'o', 'm', 'p', 'l', 'e', 'x'};
  static const char b_cv1[7]{'c', 'o', 'm', 'p', 'l', 'e', 'x'};
  static const char b_b[6]{'l', 'i', 'n', 'e', 'a', 'r'};
  static const char b_cv[6]{'l', 'i', 'n', 'e', 'a', 'r'};
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
    switch_expression_data[i] = cv[static_cast<int>(x_data[i])];
  }
  b_bool = false;
  i = 0;
  do {
    exitg1 = 0;
    if (i < 6) {
      if (switch_expression_data[i] != b_cv[i]) {
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
      if (cplxMode_data[i] != b_cv1[i]) {
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
//                unsigned int varargin_2
//                double varargin_3
//                ::coder::array<creal_T, 2U> &y
// Return Type  : void
//
void wgn(double varargin_1, unsigned int varargin_2, double varargin_3,
         ::coder::array<creal_T, 2U> &y)
{
  static rtEqualityCheckInfo g_emlrtECI{
      2,                                                      // nDims
      223,                                                    // lineNo
      38,                                                     // colNo
      "wgn",                                                  // fName
      "C:\\Program Files\\MATLAB\\toolbox\\comm\\comm\\wgn.m" // pName
  };
  static rtRunTimeErrorInfo wc_emlrtRTEI{
      180,  // lineNo
      "wgn" // fName
  };
  static const char b[7]{'c', 'o', 'm', 'p', 'l', 'e', 'x'};
  static const char b_cv1[7]{'c', 'o', 'm', 'p', 'l', 'e', 'x'};
  static const char b_b[6]{'l', 'i', 'n', 'e', 'a', 'r'};
  static const char b_cv[6]{'l', 'i', 'n', 'e', 'a', 'r'};
  array<double, 2U> c_b;
  array<double, 2U> r;
  double noisePower;
  int iv[2];
  int iv1[2];
  int b_y;
  int exitg2;
  int k;
  char cplxMode_data[7];
  char switch_expression_data[6];
  char x_data[6];
  boolean_T x[6];
  boolean_T c_y;
  boolean_T exitg1;
  for (b_y = 0; b_y < 7; b_y++) {
    cplxMode_data[b_y] = b[b_y];
  }
  x[0] = (varargin_1 <= 0.0);
  x[1] = (varargin_2 <= 0U);
  x[2] = false;
  x[3] = false;
  x[4] = (varargin_1 - std::floor(varargin_1) != 0.0);
  x[5] = false;
  c_y = false;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 6)) {
    if (x[k]) {
      c_y = true;
      exitg1 = true;
    } else {
      k++;
    }
  }
  if (c_y) {
    nb_rtErrorWithMessageID(wc_emlrtRTEI.fName, wc_emlrtRTEI.lineNo);
  }
  for (k = 0; k < 6; k++) {
    x_data[k] = b_b[k];
    switch_expression_data[k] = cv[static_cast<int>(x_data[k])];
  }
  c_y = false;
  k = 0;
  do {
    exitg2 = 0;
    if (k < 6) {
      if (switch_expression_data[k] != b_cv[k]) {
        exitg2 = 1;
      } else {
        k++;
      }
    } else {
      c_y = true;
      exitg2 = 1;
    }
  } while (exitg2 == 0);
  if (c_y) {
    b_y = 0;
  } else {
    b_y = -1;
  }
  if (b_y == 0) {
    noisePower = varargin_3;
  } else {
    noisePower = rt_powd_snf(10.0, (varargin_3 - 30.0) / 10.0);
  }
  c_y = false;
  k = 0;
  do {
    exitg2 = 0;
    if (k < 7) {
      if (cplxMode_data[k] != b_cv1[k]) {
        exitg2 = 1;
      } else {
        k++;
      }
    } else {
      c_y = true;
      exitg2 = 1;
    }
  } while (exitg2 == 0);
  if (c_y) {
    randn(varargin_1, varargin_2, r);
    randn(varargin_1, varargin_2, c_b);
    y.set_size(c_b.size(0), c_b.size(1));
    k = c_b.size(0) * c_b.size(1);
    for (b_y = 0; b_y < k; b_y++) {
      y[b_y].re = c_b[b_y] * 0.0;
      y[b_y].im = c_b[b_y];
    }
    iv[0] = (*(int(*)[2])r.size())[0];
    iv[1] = (*(int(*)[2])r.size())[1];
    iv1[0] = (*(int(*)[2])y.size())[0];
    iv1[1] = (*(int(*)[2])y.size())[1];
    rtSizeEqNDCheck(&iv[0], &iv1[0], &g_emlrtECI);
    noisePower /= 2.0;
    if (noisePower < 0.0) {
      rtErrorWithMessageID("sqrt", ec_emlrtRTEI.fName, ec_emlrtRTEI.lineNo);
    }
    noisePower = std::sqrt(noisePower);
    k = r.size(0) * r.size(1);
    y.set_size(r.size(0), r.size(1));
    for (b_y = 0; b_y < k; b_y++) {
      y[b_y].re = noisePower * (r[b_y] + y[b_y].re);
      y[b_y].im = noisePower * y[b_y].im;
    }
  } else {
    if (noisePower < 0.0) {
      rtErrorWithMessageID("sqrt", ec_emlrtRTEI.fName, ec_emlrtRTEI.lineNo);
    }
    noisePower = std::sqrt(noisePower);
    randn(varargin_1, varargin_2, c_b);
    y.set_size(c_b.size(0), c_b.size(1));
    k = c_b.size(0) * c_b.size(1);
    for (b_y = 0; b_y < k; b_y++) {
      y[b_y].re = noisePower * c_b[b_y];
      y[b_y].im = 0.0;
    }
  }
}

} // namespace coder

//
// File trailer for wgn.cpp
//
// [EOF]
//
