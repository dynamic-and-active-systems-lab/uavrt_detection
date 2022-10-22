//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: str2double.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 22-Oct-2022 15:24:58
//

// Include Files
#include "str2double.h"
#include "rt_nonfinite.h"
#include "str2double1.h"
#include "uavrt_detection_data.h"
#include "coder_array.h"
#include <stdio.h>

// Function Definitions
//
// Arguments    : const ::coder::array<char, 2U> &s
// Return Type  : creal_T
//
namespace coder {
creal_T str2double(const ::coder::array<char, 2U> &s)
{
  array<char, 2U> s1;
  creal_T x;
  double scanned1;
  double scanned2;
  int idx;
  int k;
  boolean_T a__1;
  boolean_T foundsign;
  boolean_T isfinite1;
  boolean_T isfinite2;
  boolean_T isimag1;
  boolean_T success;
  x.re = rtNaN;
  x.im = 0.0;
  if (s.size(1) >= 1) {
    int ntoread;
    boolean_T exitg1;
    ntoread = 0;
    k = 1;
    exitg1 = false;
    while ((!exitg1) && (k <= s.size(1))) {
      char c;
      c = s[k - 1];
      if (bv[static_cast<unsigned char>(c) & 127] || (c == '\x00')) {
        k++;
      } else {
        exitg1 = true;
      }
    }
    s1.set_size(1, s.size(1) + 2);
    idx = s.size(1) + 2;
    for (int i{0}; i < idx; i++) {
      s1[i] = '\x00';
    }
    idx = 1;
    internal::readfloat(s1, &idx, s, &k, s.size(1), &isimag1, &isfinite1,
                        &scanned1, &a__1, &success);
    if (isfinite1) {
      ntoread = 1;
    }
    if (success && (k <= s.size(1))) {
      s1[idx - 1] = ' ';
      idx++;
      internal::readfloat(s1, &idx, s, &k, s.size(1), &a__1, &isfinite2,
                          &scanned2, &foundsign, &success);
      if (isfinite2) {
        ntoread++;
      }
      if (success && (k > s.size(1)) && (isimag1 ^ a__1) && foundsign) {
        success = true;
      } else {
        success = false;
      }
    } else {
      scanned2 = 0.0;
    }
    if (success) {
      s1[idx - 1] = '\x00';
      if (ntoread == 2) {
        idx = sscanf(&s1[0], "%lf %lf", &scanned1, &scanned2);
        if (idx != 2) {
          scanned1 = rtNaN;
          scanned2 = rtNaN;
        }
      } else if (ntoread == 1) {
        double b_scanned1;
        idx = sscanf(&s1[0], "%lf", &b_scanned1);
        if (idx != 1) {
          b_scanned1 = rtNaN;
        }
        if (isfinite1) {
          scanned1 = b_scanned1;
        } else {
          scanned2 = b_scanned1;
        }
      }
      if (isimag1) {
        x.re = scanned2;
        x.im = scanned1;
      } else {
        x.re = scanned1;
        x.im = scanned2;
      }
    }
  }
  return x;
}

} // namespace coder

//
// File trailer for str2double.cpp
//
// [EOF]
//
