//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// locBsearch.h
//
// Code generation for function 'locBsearch'
//

#ifndef LOCBSEARCH_H
#define LOCBSEARCH_H

// Include files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
void b_sparse_locBsearch(const ::coder::array<int, 1U> &x, int xi, int xstart,
                         int xend, int *n, boolean_T *found);

void sparse_locBsearch(const ::coder::array<int, 1U> &x, double xi, int xstart,
                       int xend, int *n, boolean_T *found);

} // namespace coder

#endif
// End of code generation (locBsearch.h)
