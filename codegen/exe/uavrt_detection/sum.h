//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sum.h
//
<<<<<<< HEAD
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 23-May-2023 12:05:02
=======
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Apr-2023 11:47:02
>>>>>>> 3930a1e557481905555f2756f2f70ac82e87beba
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

class c_sparse;

} // namespace coder

// Function Declarations
namespace coder {
void sum(const sparse &x, b_sparse &y);

void sum(const g_sparse &x, c_sparse &y);

void sum(const ::coder::array<double, 2U> &x, ::coder::array<double, 1U> &y);

} // namespace coder

#endif
//
// File trailer for sum.h
//
// [EOF]
//
