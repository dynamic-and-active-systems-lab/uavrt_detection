//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: introsort.h
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 20-Oct-2022 20:46:49
//

#ifndef INTROSORT_H
#define INTROSORT_H

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
void introsort(::coder::array<int, 1U> &x, int xend,
               const c_anonymous_function *cmp);

void introsort(::coder::array<int, 1U> &x, int xend,
               const anonymous_function *cmp);

} // namespace internal
} // namespace coder

#endif
//
// File trailer for introsort.h
//
// [EOF]
//
