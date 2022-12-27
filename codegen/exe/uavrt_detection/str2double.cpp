//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// str2double.cpp
//
// Code generation for function 'str2double'
//

// Include files
#include "str2double.h"
#include "rt_nonfinite.h"
#include "str2double1.h"
#include "uavrt_detection_data.h"
#include "coder_array.h"
#include <stdio.h>
#include <string.h>

// Function Definitions
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
    internal::readfloat(s1, &idx, s, &k, s.size(1), true, &isimag1, &isfinite1,
                        &scanned1, &a__1, &success);
    if (isfinite1) {
      ntoread = 1;
    }
    if (success && (k <= s.size(1))) {
      s1[idx - 1] = ' ';
      idx++;
      internal::readfloat(s1, &idx, s, &k, s.size(1), true, &a__1, &isfinite2,
                          &scanned2, &foundsign, &success);
      if (isfinite2) {
        ntoread++;
      }
      if (success && (k > s.size(1)) &&
          (static_cast<boolean_T>(isimag1 ^ a__1)) && foundsign) {
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

// End of code generation (str2double.cpp)
