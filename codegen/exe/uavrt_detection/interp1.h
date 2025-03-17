//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: interp1.h
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

#ifndef INTERP1_H
#define INTERP1_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
void interp1(const double varargin_1[2], const double varargin_2[2],
             const array<double, 2U> &varargin_3, array<double, 2U> &Vq);

void interp1(const double varargin_2[2], const array<double, 1U> &varargin_3,
             array<double, 1U> &Vq);

void interp1(const array<double, 1U> &varargin_1,
             const array<double, 1U> &varargin_2,
             const array<double, 1U> &varargin_3, array<double, 1U> &Vq);

} // namespace coder

#endif
//
// File trailer for interp1.h
//
// [EOF]
//
