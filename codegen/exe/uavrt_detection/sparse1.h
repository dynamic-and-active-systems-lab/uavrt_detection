//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sparse1.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 14:31:55
//

#ifndef SPARSE1_H
#define SPARSE1_H

// Include Files
#include "rtwtypes.h"
#include "uavrt_detection_internal_types.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
class sparse {
public:
  emxArray_real_T_1 d;
  emxArray_int32_T_1 colidx;
  emxArray_int32_T_1 rowidx;
  int m;
  int n;
  int maxnz;
};

} // namespace coder

#endif
//
// File trailer for sparse1.h
//
// [EOF]
//
