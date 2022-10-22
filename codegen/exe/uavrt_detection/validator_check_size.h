//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: validator_check_size.h
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 22-Oct-2022 12:48:10
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
void validator_check_size(const ::coder::array<double, 1U> &in,
                          ::coder::array<double, 1U> &out);

void validator_check_size(const ::coder::array<c_struct_T, 2U> &in,
                          ::coder::array<c_struct_T, 2U> &out);

void validator_check_size(::coder::array<c_struct_T, 2U> &in);

} // namespace internal
} // namespace coder

#endif
//
// File trailer for validator_check_size.h
//
// [EOF]
//
