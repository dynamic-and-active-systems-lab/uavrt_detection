//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: randn.h
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

#ifndef RANDN_H
#define RANDN_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
void complexLike(creal_T r[1000]);

void complexLike(double varargin_1, unsigned int varargin_2,
                 array<creal_T, 2U> &r);

void randn(double r[1000]);

void randn(double varargin_1, unsigned int varargin_2, array<double, 2U> &r);

} // namespace coder

#endif
//
// File trailer for randn.h
//
// [EOF]
//
