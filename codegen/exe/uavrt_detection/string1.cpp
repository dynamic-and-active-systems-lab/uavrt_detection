//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: string1.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 13-Sep-2023 13:30:23
//

// Include Files
#include "string1.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "coder_array.h"

// Variable Definitions
static const char cv3[18]{'f', 'r', 'e', 'q', 'S', 'e', 'a', 'r', 'c',
                          'h', 'H', 'a', 'r', 'd', 'L', 'o', 'c', 'k'};

// Function Definitions
//
// Arguments    : void
// Return Type  : boolean_T
//
namespace coder {
boolean_T rtString::b_eq() const
{
  static const char b_cv[17]{'f', 'r', 'e', 'q', 'K', 'n', 'o', 'w', 'n',
                             'H', 'a', 'r', 'd', 'L', 'o', 'c', 'k'};
  boolean_T equal;
  equal = false;
  if (Value.size(1) == 17) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 17) {
        if (b_cv[kstr] != Value[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        equal = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  return equal;
}

//
// Arguments    : void
// Return Type  : boolean_T
//
boolean_T rtString::c_eq() const
{
  boolean_T equal;
  equal = false;
  if (Value.size(1) == 18) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 18) {
        if (cv4[kstr] != Value[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        equal = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  return equal;
}

//
// Arguments    : void
// Return Type  : boolean_T
//
boolean_T rtString::d_eq() const
{
  static const char b_cv[13]{'f', 'r', 'e', 'q', 'A', 'l', 'l',
                             'N', 'o', 'L', 'o', 'c', 'k'};
  boolean_T equal;
  equal = false;
  if (Value.size(1) == 13) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 13) {
        if (b_cv[kstr] != Value[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        equal = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  return equal;
}

//
// Arguments    : void
// Return Type  : boolean_T
//
boolean_T rtString::eq() const
{
  boolean_T equal;
  equal = false;
  if (Value.size(1) == 18) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 18) {
        if (cv3[kstr] != Value[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        equal = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  return equal;
}

//
// Arguments    : void
// Return Type  : void
//
void rtString::init()
{
  Value.set_size(1, 18);
  for (int i{0}; i < 18; i++) {
    Value[i] = cv3[i];
  }
}

} // namespace coder

//
// File trailer for string1.cpp
//
// [EOF]
//
