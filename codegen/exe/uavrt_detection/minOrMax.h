//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: minOrMax.h
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Nov-2023 20:09:42
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
double b_minimum(const double x[2]);

double maximum(const array<double, 1U> &x);

void maximum(const array<double, 2U> &x, array<double, 1U> &ex,
             array<int, 1U> &idx);

double maximum(const array<double, 1U> &x, int &idx);

double maximum(const double x[2]);

double minimum(const double x_data[]);

} // namespace internal
} // namespace coder

#endif
//
// File trailer for minOrMax.h
//
// [EOF]
//
