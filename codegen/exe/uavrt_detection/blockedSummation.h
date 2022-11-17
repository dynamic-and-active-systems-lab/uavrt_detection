//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// blockedSummation.h
//
// Code generation for function 'blockedSummation'
//

#ifndef BLOCKEDSUMMATION_H
#define BLOCKEDSUMMATION_H

// Include files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
void colMajorFlatIter(const ::coder::array<double, 1U> &x, int vlen, double *y,
                      int *counts);

}

#endif
// End of code generation (blockedSummation.h)
