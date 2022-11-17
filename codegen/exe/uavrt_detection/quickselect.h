//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// quickselect.h
//
// Code generation for function 'quickselect'
//

#ifndef QUICKSELECT_H
#define QUICKSELECT_H

// Include files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
void quickselect(::coder::array<double, 1U> &v, int n, int vlen, double *vn,
                 int *nfirst, int *nlast);

}
} // namespace coder

#endif
// End of code generation (quickselect.h)
