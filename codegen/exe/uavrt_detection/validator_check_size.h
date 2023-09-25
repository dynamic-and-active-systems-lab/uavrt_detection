//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: validator_check_size.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 24-Sep-2023 17:58:12
//

#ifndef VALIDATOR_CHECK_SIZE_H
#define VALIDATOR_CHECK_SIZE_H

// Include Files
#include "rtwtypes.h"
#include "uavrt_detection_internal_types.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
void validator_check_size(const ::coder::array<double, 2U> &in,
                          ::coder::array<double, 2U> &out);

void validator_check_size(const ::coder::array<c_struct_T, 2U> &in,
                          ::coder::array<c_struct_T, 2U> &out);

} // namespace internal
} // namespace coder

#endif
//
// File trailer for validator_check_size.h
//
// [EOF]
//
