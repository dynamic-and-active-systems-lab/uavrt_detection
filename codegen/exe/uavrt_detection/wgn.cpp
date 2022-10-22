//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: wgn.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 22-Oct-2022 12:48:10
//

// Include Files
#include "wgn.h"
#include "randn.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : creal_T y[1000]
// Return Type  : void
//
namespace coder {
void wgn(creal_T y[1000])
{
  static const char b_cv1[7]{'c', 'o', 'm', 'p', 'l', 'e', 'x'};
  static const char b[6]{'l', 'i', 'n', 'e', 'a', 'r'};
  static const char b_cv[6]{'l', 'i', 'n', 'e', 'a', 'r'};
  array<char, 2U> b_y;
  array<char, 2U> x;
  double noisePower;
  int i;
  char a_data[7];
  boolean_T b_bool;
  x.set_size(1, 6);
  for (i = 0; i < 6; i++) {
    x[i] = b[i];
  }
  b_y.set_size(1, 6);
  for (i = 0; i < 6; i++) {
    b_y[i] = cv[static_cast<int>(x[i])];
  }
  b_bool = false;
  i = 0;
  int exitg1;
  do {
    exitg1 = 0;
    if (i < 6) {
      if (b_y[i] != b_cv[i]) {
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
  for (i = 0; i < 7; i++) {
    a_data[i] = b_cv1[i];
  }
  if (cv[static_cast<int>(a_data[0])] == 'r') {
    double b_b[1000];
    noisePower = std::sqrt(noisePower);
    randn(b_b);
    for (i = 0; i < 1000; i++) {
      y[i].re = noisePower * b_b[i];
      y[i].im = 0.0;
    }
  } else {
    noisePower = std::sqrt(noisePower);
    complexLike(y);
    for (i = 0; i < 1000; i++) {
      y[i].re *= noisePower;
      y[i].im *= noisePower;
    }
  }
}

} // namespace coder

//
// File trailer for wgn.cpp
//
// [EOF]
//
