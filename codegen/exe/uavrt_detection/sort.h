//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sort.h
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

#ifndef SORT_H
#define SORT_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
void sort(array<double, 2U> &x);

void sort(array<double, 1U> &x, array<int, 1U> &idx);

void sort(array<double, 2U> &x, array<int, 2U> &idx);

} // namespace internal
} // namespace coder

#endif
//
// File trailer for sort.h
//
// [EOF]
//
