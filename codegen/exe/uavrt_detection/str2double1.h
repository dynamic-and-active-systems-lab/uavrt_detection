//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: str2double1.h
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Oct-2022 17:38:50
//

#ifndef STR2DOUBLE1_H
#define STR2DOUBLE1_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
void readfloat(::coder::array<char, 2U> &s1, int *idx,
               const ::coder::array<char, 2U> &s, int *k, int n,
               boolean_T *isimag, boolean_T *b_finite, double *nfv,
               boolean_T *foundsign, boolean_T *success);

}
} // namespace coder

#endif
//
// File trailer for str2double1.h
//
// [EOF]
//
