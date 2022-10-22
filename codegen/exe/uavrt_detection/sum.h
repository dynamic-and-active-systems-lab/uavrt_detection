//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: sum.h
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Oct-2022 17:38:50
//

#ifndef SUM_H
#define SUM_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
namespace coder {
class sparse;

class b_sparse;

class g_sparse;

class e_sparse;

} // namespace coder

// Function Declarations
namespace coder {
double sum(const ::coder::array<double, 1U> &x);

void sum(const sparse *x, b_sparse *y);

void sum(const g_sparse *x, e_sparse *y);

void sum(const ::coder::array<double, 2U> &x, ::coder::array<double, 1U> &y);

} // namespace coder

#endif
//
// File trailer for sum.h
//
// [EOF]
//
