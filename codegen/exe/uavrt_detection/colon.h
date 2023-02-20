//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: colon.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 14:31:55
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
void eml_float_colon(double a, double b, double y_data[], int y_size[2]);

void eml_integer_colon_dispatcher(int a, int b, ::coder::array<int, 2U> &y);

} // namespace coder

#endif
//
// File trailer for colon.h
//
// [EOF]
//
