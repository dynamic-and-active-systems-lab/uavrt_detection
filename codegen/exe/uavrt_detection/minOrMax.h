//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: minOrMax.h
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 22-Oct-2022 12:48:10
//

#ifndef MINORMAX_H
#define MINORMAX_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
void maximum(const ::coder::array<double, 2U> &x,
             ::coder::array<double, 1U> &ex, ::coder::array<int, 1U> &idx);

void maximum(const ::coder::array<double, 1U> &x, double *ex, int *idx);

double maximum(const double x[2]);

double maximum(const ::coder::array<double, 1U> &x);

double minimum(const double x[2]);

} // namespace internal
} // namespace coder

#endif
//
// File trailer for minOrMax.h
//
// [EOF]
//
