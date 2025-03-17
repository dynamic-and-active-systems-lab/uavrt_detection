//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: any1.h
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

#ifndef ANY1_H
#define ANY1_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
namespace coder {
class d_sparse;

class e_sparse;

} // namespace coder

// Function Declarations
namespace coder {
void any(const d_sparse &x, e_sparse &y);

boolean_T b_any(const boolean_T x[2]);

void c_any(const array<boolean_T, 2U> &x, array<boolean_T, 1U> &y);

} // namespace coder

#endif
//
// File trailer for any1.h
//
// [EOF]
//
