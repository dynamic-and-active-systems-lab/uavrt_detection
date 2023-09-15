//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: indexShapeCheck.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 15-Sep-2023 11:38:47
//

#ifndef INDEXSHAPECHECK_H
#define INDEXSHAPECHECK_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
void b_indexShapeCheck(const int matrixSize[2], const int indexSize[2]);

void indexShapeCheck(const int matrixSize[2], const int indexSize[2]);

void indexShapeCheck(const double matrixSize[2], const double indexSize[2]);

void indexShapeCheck(int matrixSize, const int indexSize[2]);

} // namespace internal
} // namespace coder

#endif
//
// File trailer for indexShapeCheck.h
//
// [EOF]
//
