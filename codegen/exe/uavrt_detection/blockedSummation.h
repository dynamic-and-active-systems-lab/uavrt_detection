//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: blockedSummation.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 31-Jul-2023 09:40:06
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
double blockedSummation(const ::coder::array<double, 1U> &x, int vlen);

double colMajorFlatIter(const ::coder::array<double, 1U> &x, int vlen,
                        int &counts);

} // namespace coder

#endif
//
// File trailer for blockedSummation.h
//
// [EOF]
//
