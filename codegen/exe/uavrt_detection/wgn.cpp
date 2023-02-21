//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: wgn.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 18:16:21
//

// Include Files
#include "wgn.h"
#include "randn.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include <cmath>
#include <string.h>

// Function Definitions
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

} // namespace coder

//
// File trailer for wgn.cpp
//
// [EOF]
//
