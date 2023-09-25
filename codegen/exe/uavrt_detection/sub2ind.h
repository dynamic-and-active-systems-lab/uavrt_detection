//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sub2ind.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 24-Sep-2023 17:58:12
//

#ifndef SUB2IND_H
#define SUB2IND_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
void b_sub2ind(const int siz[2], const ::coder::array<double, 2U> &varargin_1,
               const ::coder::array<double, 2U> &varargin_2,
               ::coder::array<int, 2U> &idx);

void sub2ind(const int siz[2], const ::coder::array<double, 2U> &varargin_1,
             const ::coder::array<double, 2U> &varargin_2,
             ::coder::array<int, 2U> &idx);

void sub2ind(const int siz[2], const ::coder::array<double, 1U> &varargin_1,
             const ::coder::array<double, 1U> &varargin_2,
             ::coder::array<int, 1U> &idx);

int sub2ind(const int siz[2], double varargin_2);

} // namespace internal
} // namespace coder

#endif
//
// File trailer for sub2ind.h
//
// [EOF]
//
