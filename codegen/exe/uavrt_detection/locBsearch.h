//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: locBsearch.h
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 22-Oct-2022 15:24:58
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
