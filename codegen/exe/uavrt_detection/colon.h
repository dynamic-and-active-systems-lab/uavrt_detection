//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: colon.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 21-Sep-2023 14:06:08
//

#ifndef COLON_H
#define COLON_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
void eml_float_colon(double a, double b, ::coder::array<double, 2U> &y);

void eml_integer_colon_dispatcher(int a, ::coder::array<int, 2U> &y);

void eml_integer_colon_dispatcher(int a, int b, ::coder::array<int, 2U> &y);

} // namespace coder

#endif
//
// File trailer for colon.h
//
// [EOF]
//
