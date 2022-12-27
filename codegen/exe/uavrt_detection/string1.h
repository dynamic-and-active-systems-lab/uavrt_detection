//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// string1.h
//
// Code generation for function 'string1'
//

#ifndef STRING1_H
#define STRING1_H

// Include files
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
  boolean_T eq() const;
  boolean_T b_eq() const;
  boolean_T c_eq() const;
  boolean_T d_eq() const;
  void init();
  array<char, 2U> Value;
};

} // namespace coder

#endif
// End of code generation (string1.h)
