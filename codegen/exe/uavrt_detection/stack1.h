//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: stack1.h
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
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
