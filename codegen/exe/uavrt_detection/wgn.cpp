//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: wgn.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 16-Feb-2023 15:25:26
//

// Include Files
#include "wgn.h"
#include "eml_int_forloop_overflow_check.h"
#include "randn.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
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
  static const char b_cv1[7]{'c', 'o', 'm', 'p', 'l', 'e', 'x'};
  static const char c_b[7]{'c', 'o', 'm', 'p', 'l', 'e', 'x'};
  static const char b_b[6]{'l', 'i', 'n', 'e', 'a', 'r'};
  static const char b_cv[6]{'l', 'i', 'n', 'e', 'a', 'r'};
  array<char, 2U> b;
  array<char, 2U> r;
  double noisePower;
  int exitg1;
  int ns;
  char cplxMode_data[7];
  boolean_T p;
  for (ns = 0; ns < 7; ns++) {
    cplxMode_data[ns] = c_b[ns];
  }
  b.set((char *)&b_b[0], 1, 6);
  ns = b.size(1);
  p = true;
  if (b.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{0}; k < ns; k++) {
    p = (p && (static_cast<unsigned char>(b[k]) <= 127));
  }
  if (!p) {
    rc_rtErrorWithMessageID(i_emlrtRTEI.fName, i_emlrtRTEI.lineNo);
  }
  r.set_size(1, b.size(1));
  ns = b.size(1);
  for (int k{0}; k < ns; k++) {
    r[k] = cv[static_cast<unsigned char>(b[k]) & 127];
  }
  p = false;
  ns = 0;
  do {
    exitg1 = 0;
    if (ns < 6) {
      if (r[ns] != b_cv[ns]) {
        exitg1 = 1;
      } else {
        ns++;
      }
    } else {
      p = true;
      exitg1 = 1;
    }
  } while (exitg1 == 0);
  if (p) {
    ns = 0;
  } else {
    ns = -1;
  }
  if (ns == 0) {
    noisePower = 1.0;
  } else {
    noisePower = 0.0012589254117941675;
  }
  p = false;
  ns = 0;
  do {
    exitg1 = 0;
    if (ns < 7) {
      if (cplxMode_data[ns] != b_cv1[ns]) {
        exitg1 = 1;
      } else {
        ns++;
      }
    } else {
      p = true;
      exitg1 = 1;
    }
  } while (exitg1 == 0);
  if (p) {
    double d_b[1000];
    double dv[1000];
    randn(d_b);
    noisePower = std::sqrt(noisePower / 2.0);
    randn(dv);
    for (ns = 0; ns < 1000; ns++) {
      double d;
      d = d_b[ns];
      y[ns].re = noisePower * (dv[ns] + 0.0 * d);
      y[ns].im = noisePower * d;
    }
  } else {
    double d_b[1000];
    noisePower = std::sqrt(noisePower);
    randn(d_b);
    for (ns = 0; ns < 1000; ns++) {
      y[ns].re = noisePower * d_b[ns];
      y[ns].im = 0.0;
    }
  }
}

} // namespace coder

//
// File trailer for wgn.cpp
//
// [EOF]
//
