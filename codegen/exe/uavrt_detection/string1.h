//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: string1.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 11-Aug-2023 11:48:47
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
  boolean_T eq() const;
  boolean_T b_eq() const;
  boolean_T c_eq() const;
  boolean_T d_eq() const;
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
