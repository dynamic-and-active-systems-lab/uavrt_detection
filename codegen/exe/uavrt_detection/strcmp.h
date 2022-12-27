//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// strcmp.h
//
// Code generation for function 'strcmp'
//

#ifndef STRCMP_H
#define STRCMP_H

// Include files
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

boolean_T b_strcmp(const char a_data[], const int a_size[2]);

boolean_T b_strcmp(const b_rtString *a);

boolean_T c_strcmp(const ::coder::array<char, 2U> &a);

boolean_T c_strcmp(const char a_data[], const int a_size[2]);

boolean_T c_strcmp(const b_rtString *a);

boolean_T d_strcmp(const ::coder::array<char, 2U> &a);

boolean_T d_strcmp(const char a_data[], const int a_size[2]);

boolean_T e_strcmp(const ::coder::array<char, 2U> &a);

boolean_T e_strcmp(const char a_data[], const int a_size[2]);

boolean_T f_strcmp(const char a_data[], const int a_size[2]);

boolean_T f_strcmp(const ::coder::array<char, 2U> &a);

boolean_T g_strcmp(const ::coder::array<char, 2U> &a);

boolean_T h_strcmp(const ::coder::array<char, 2U> &a);

boolean_T i_strcmp(const ::coder::array<char, 2U> &a);

boolean_T j_strcmp(const ::coder::array<char, 2U> &a);

boolean_T k_strcmp(const ::coder::array<char, 2U> &a);

boolean_T l_strcmp(const ::coder::array<char, 2U> &a);

boolean_T m_strcmp(const ::coder::array<char, 2U> &a);

boolean_T n_strcmp(const ::coder::array<char, 2U> &a);

boolean_T o_strcmp(const ::coder::array<char, 2U> &a);

boolean_T p_strcmp(const ::coder::array<char, 2U> &a);

} // namespace internal
} // namespace coder

#endif
// End of code generation (strcmp.h)
