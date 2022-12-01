//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: string1.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 01-Dec-2022 10:02:54
//

#ifndef STRING1_H
#define STRING1_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
class rtString {
public:
  void init();
  char Value[34];
};

class b_rtString {
public:
  bool eq() const;
  bool b_eq() const;
  bool c_eq() const;
  bool d_eq() const;
  void init();
  array<char, 2U> Value;
};

} // namespace coder

#endif
//
// File trailer for string1.h
//
// [EOF]
//
