//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: stack1.h
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 20-Oct-2022 20:46:49
//

#ifndef STACK1_H
#define STACK1_H

// Include Files
#include "rtwtypes.h"
#include "uavrt_detection_internal_types.h"
#include "coder_bounded_array.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
namespace internal {
class stack {
public:
  bounded_array<struct_T, 120U, 1U> d;
  int n;
};

} // namespace internal
} // namespace coder

#endif
//
// File trailer for stack1.h
//
// [EOF]
//
