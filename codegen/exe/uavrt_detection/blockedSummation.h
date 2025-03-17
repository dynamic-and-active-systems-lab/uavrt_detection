//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: blockedSummation.h
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

#ifndef BLOCKEDSUMMATION_H
#define BLOCKEDSUMMATION_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
double blockedSummation(const array<double, 1U> &x, int vlen);

double colMajorFlatIter(const array<double, 1U> &x, int vlen, int &counts);

} // namespace coder

#endif
//
// File trailer for blockedSummation.h
//
// [EOF]
//
