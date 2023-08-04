//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: randn.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 04-Aug-2023 15:45:46
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
                 ::coder::array<creal_T, 2U> &r);

void randn(double r[1000]);

void randn(double varargin_1, unsigned int varargin_2,
           ::coder::array<double, 2U> &r);

} // namespace coder

#endif
//
// File trailer for randn.h
//
// [EOF]
//
