//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// sparse.h
//
// Code generation for function 'sparse'
//

#ifndef SPARSE_H
#define SPARSE_H

// Include files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
namespace coder {
class c_sparse;

class g_sparse;

} // namespace coder

// Function Declarations
namespace coder {
void i_sparse(const ::coder::array<boolean_T, 2U> &varargin_1, c_sparse *y);

void j_sparse(const ::coder::array<double, 1U> &varargin_1, g_sparse *y);

} // namespace coder

#endif
// End of code generation (sparse.h)
