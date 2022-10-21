//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: interp1.h
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 20-Oct-2022 20:46:49
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
void interp1(const ::coder::array<double, 1U> &varargin_1,
             const ::coder::array<double, 1U> &varargin_2,
             const ::coder::array<double, 1U> &varargin_3,
             ::coder::array<double, 1U> &Vq);

void interp1Linear(const double y[2], const ::coder::array<double, 2U> &xi,
                   ::coder::array<double, 2U> &yi, const double varargin_1[2]);

void interp1Linear(const double y[2], const ::coder::array<double, 1U> &xi,
                   ::coder::array<double, 1U> &yi);

} // namespace coder

#endif
//
// File trailer for interp1.h
//
// [EOF]
//
