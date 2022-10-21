//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: string1.h
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 20-Oct-2022 20:46:49
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
