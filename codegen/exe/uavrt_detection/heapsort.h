//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: heapsort.h
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Oct-2022 17:38:50
//

#ifndef HEAPSORT_H
#define HEAPSORT_H

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
void b_heapsort(::coder::array<int, 1U> &x, int xstart, int xend,
                const c_anonymous_function *cmp);

void b_heapsort(::coder::array<int, 1U> &x, int xstart, int xend,
                const anonymous_function *cmp);

} // namespace internal
} // namespace coder

#endif
//
// File trailer for heapsort.h
//
// [EOF]
//
