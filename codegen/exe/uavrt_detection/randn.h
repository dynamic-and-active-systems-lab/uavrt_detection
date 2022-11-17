//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// randn.h
//
// Code generation for function 'randn'
//

#ifndef RANDN_H
#define RANDN_H

// Include files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
void randn(double r[1000]);

void randn(double varargin_1, ::coder::array<double, 2U> &r);

} // namespace coder

#endif
// End of code generation (randn.h)
