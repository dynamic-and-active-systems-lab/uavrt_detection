//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: strcmp.h
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 20-Oct-2022 20:46:49
//

#ifndef STRCMP_H
#define STRCMP_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
namespace coder {
class b_rtString;

}

// Function Declarations
namespace coder {
namespace internal {
boolean_T b_strcmp(const ::coder::array<char, 2U> &a);

boolean_T b_strcmp(const b_rtString *a);

boolean_T b_strcmp(const char a_data[], const int a_size[2]);

boolean_T c_strcmp(const ::coder::array<char, 2U> &a);

boolean_T c_strcmp(const b_rtString *a);

boolean_T c_strcmp(const char a_data[], const int a_size[2]);

boolean_T d_strcmp(const ::coder::array<char, 2U> &a);

boolean_T d_strcmp(const char a_data[], const int a_size[2]);

boolean_T e_strcmp(const ::coder::array<char, 2U> &a);

boolean_T e_strcmp(const char a_data[], const int a_size[2]);

boolean_T f_strcmp(const ::coder::array<char, 2U> &a);

boolean_T f_strcmp(const char a_data[], const int a_size[2]);

} // namespace internal
} // namespace coder

#endif
//
// File trailer for strcmp.h
//
// [EOF]
//
