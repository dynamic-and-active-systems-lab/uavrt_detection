//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: locBsearch.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 21-Feb-2023 09:24:56
//

#ifndef LOCBSEARCH_H
#define LOCBSEARCH_H

// Include Files
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
//
// File trailer for locBsearch.h
//
// [EOF]
//
