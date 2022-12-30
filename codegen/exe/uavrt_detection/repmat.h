//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: repmat.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 30-Dec-2022 12:50:56
//

#ifndef REPMAT_H
#define REPMAT_H

// Include Files
#include "rtwtypes.h"
#include "uavrt_detection_internal_types.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
void repmat(const c_struct_T *a, double varargin_1, double varargin_2,
            ::coder::array<c_struct_T, 2U> &b);

void repmat(const ::coder::array<double, 2U> &a, double varargin_1,
            ::coder::array<double, 2U> &b);

void repmat(const ::coder::array<double, 1U> &a, double varargin_2,
            ::coder::array<double, 2U> &b);

} // namespace coder

#endif
//
// File trailer for repmat.h
//
// [EOF]
//
