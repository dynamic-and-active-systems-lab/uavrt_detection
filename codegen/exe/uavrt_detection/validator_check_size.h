//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: validator_check_size.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 17-Dec-2022 12:06:22
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
boolean_T b_validator_check_size(const boolean_T in_data[], int in_size);

void c_validator_check_size(const ::coder::array<c_struct_T, 2U> &in,
                            ::coder::array<c_struct_T, 2U> &out);

void c_validator_check_size(const ::coder::array<double, 2U> &in,
                            ::coder::array<double, 2U> &out);

void d_validator_check_size(const ::coder::array<boolean_T, 2U> &in,
                            ::coder::array<boolean_T, 2U> &out);

void validator_check_size(const ::coder::array<double, 2U> &in,
                          ::coder::array<double, 2U> &out);

void validator_check_size(const ::coder::array<creal32_T, 2U> &in,
                          ::coder::array<creal32_T, 2U> &out);

void validator_check_size(const ::coder::array<creal_T, 2U> &in,
                          ::coder::array<creal_T, 2U> &out);

void validator_check_size(const ::coder::array<double, 1U> &in,
                          ::coder::array<double, 2U> &out);

void validator_check_size(const ::coder::array<double, 1U> &in,
                          ::coder::array<double, 1U> &out);

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
