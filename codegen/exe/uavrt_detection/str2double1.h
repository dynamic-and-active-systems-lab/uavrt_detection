//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// str2double1.h
//
// Code generation for function 'str2double1'
//

#ifndef STR2DOUBLE1_H
#define STR2DOUBLE1_H

// Include files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
void readfloat(::coder::array<char, 2U> &s1, int *idx,
               const ::coder::array<char, 2U> &s, int *k, int n,
               boolean_T allowimag, boolean_T *isimag, boolean_T *b_finite,
               double *nfv, boolean_T *foundsign, boolean_T *success);

}
} // namespace coder

#endif
// End of code generation (str2double1.h)
