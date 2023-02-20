//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: find.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 14:31:55
//

#ifndef FIND_H
#define FIND_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
void b_eml_find(const ::coder::array<boolean_T, 2U> &x,
                ::coder::array<int, 2U> &i);

int c_eml_find(int x_size);

void eml_find(const ::coder::array<boolean_T, 2U> &x, int i_data[],
              int i_size[2]);

} // namespace coder

#endif
//
// File trailer for find.h
//
// [EOF]
//
