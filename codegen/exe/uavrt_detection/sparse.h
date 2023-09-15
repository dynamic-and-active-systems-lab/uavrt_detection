//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sparse.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 15-Sep-2023 12:46:31
//

#ifndef SPARSE_H
#define SPARSE_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
namespace coder {
class sparse;

class d_sparse;

class g_sparse;

} // namespace coder

// Function Declarations
namespace coder {
void i_sparse(const ::coder::array<double, 1U> &varargin_1,
              const ::coder::array<double, 1U> &varargin_2,
              const ::coder::array<double, 1U> &varargin_3, sparse &y);

void i_sparse(const ::coder::array<double, 1U> &varargin_1, g_sparse &y);

void j_sparse(const ::coder::array<boolean_T, 2U> &varargin_1, d_sparse &y);

} // namespace coder

#endif
//
// File trailer for sparse.h
//
// [EOF]
//
