//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: string1.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 22-Oct-2022 15:24:58
//

// Include Files
#include "string1.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "coder_array.h"

// Variable Definitions
static const char cv1[18]{'f', 'r', 'e', 'q', 'S', 'e', 'a', 'r', 'c',
                          'h', 'H', 'a', 'r', 'd', 'L', 'o', 'c', 'k'};

// Function Definitions
//
// Arguments    : void
// Return Type  : boolean_T
//
namespace coder {
boolean_T b_rtString::b_eq() const
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
boolean_T b_rtString::c_eq() const
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
        if (cv2[kstr] != Value[kstr]) {
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
boolean_T b_rtString::d_eq() const
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
boolean_T b_rtString::eq() const
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
        if (cv1[kstr] != Value[kstr]) {
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
  static const char b_cv[34]{'d', 'e', 't', 'e', 'c', 't', 'o', 'r', '/',
                             'c', 'o', 'n', 'f', 'i', 'g', '/', 'd', 'e',
                             't', 'e', 'c', 't', 'o', 'r', 'C', 'o', 'n',
                             'f', 'i', 'g', '.', 't', 'x', 't'};
  for (int i{0}; i < 34; i++) {
    Value[i] = b_cv[i];
  }
}

//
// Arguments    : void
// Return Type  : void
//
void b_rtString::init()
{
  Value.set_size(1, 18);
  for (int i{0}; i < 18; i++) {
    Value[i] = cv1[i];
  }
}

} // namespace coder

//
// File trailer for string1.cpp
//
// [EOF]
//
