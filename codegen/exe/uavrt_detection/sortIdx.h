//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sortIdx.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 11-Aug-2023 12:59:41
//

#ifndef SORTIDX_H
#define SORTIDX_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
void merge_block(::coder::array<int, 2U> &idx, ::coder::array<double, 2U> &x,
                 int offset, int n, int preSortLevel,
                 ::coder::array<int, 1U> &iwork,
                 ::coder::array<double, 1U> &xwork);

void merge_block(::coder::array<int, 1U> &idx, ::coder::array<double, 1U> &x,
                 int offset, int n, int preSortLevel,
                 ::coder::array<int, 1U> &iwork,
                 ::coder::array<double, 1U> &xwork);

} // namespace internal
} // namespace coder

#endif
//
// File trailer for sortIdx.h
//
// [EOF]
//
