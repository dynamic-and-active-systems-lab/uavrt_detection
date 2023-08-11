//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: insertionsort.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 11-Aug-2023 12:07:41
//

#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
namespace coder {
class anonymous_function;

class c_anonymous_function;

} // namespace coder

// Function Declarations
namespace coder {
namespace internal {
void insertionsort(::coder::array<int, 1U> &x, int xstart, int xend,
                   const anonymous_function &cmp);

void insertionsort(::coder::array<int, 1U> &x, int xstart, int xend,
                   const c_anonymous_function &cmp);

} // namespace internal
} // namespace coder

#endif
//
// File trailer for insertionsort.h
//
// [EOF]
//
