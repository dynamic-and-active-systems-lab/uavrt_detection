//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: mtimes.h
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

#ifndef MTIMES_H
#define MTIMES_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
namespace blas {
void b_mtimes(const array<creal_T, 2U> &A, const array<creal_T, 2U> &B,
              array<creal_T, 2U> &C);

void mtimes(const array<creal_T, 2U> &A, const array<creal_T, 2U> &B,
            array<creal_T, 2U> &C);

} // namespace blas
} // namespace internal
} // namespace coder

#endif
//
// File trailer for mtimes.h
//
// [EOF]
//
