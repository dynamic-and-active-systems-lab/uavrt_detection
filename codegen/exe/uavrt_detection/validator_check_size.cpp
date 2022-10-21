//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: validator_check_size.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 20-Oct-2022 20:46:49
//

// Include Files
#include "validator_check_size.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_internal_types.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<double, 1U> &in
//                ::coder::array<double, 1U> &out
// Return Type  : void
//
namespace coder {
namespace internal {
void validator_check_size(const ::coder::array<double, 1U> &in,
                          ::coder::array<double, 1U> &out)
{
  int inVectorLength;
  inVectorLength = 1;
  if (in.size(0) != 1) {
    inVectorLength = in.size(0);
  }
  if (in.size(0) == 1) {
    out.set_size(inVectorLength);
    for (int i{0}; i < inVectorLength; i++) {
      out[i] = in[0];
    }
  } else if (in.size(0) == 0) {
    out.set_size(inVectorLength);
    for (int i{0}; i < inVectorLength; i++) {
      out[i] = in[i];
    }
  } else {
    out.set_size(inVectorLength);
    for (int i{0}; i < inVectorLength; i++) {
      out[i] = in[i];
    }
  }
}

//
// Arguments    : const ::coder::array<c_struct_T, 2U> &in
//                ::coder::array<c_struct_T, 2U> &out
// Return Type  : void
//
void validator_check_size(const ::coder::array<c_struct_T, 2U> &in,
                          ::coder::array<c_struct_T, 2U> &out)
{
  int inVectorLength;
  inVectorLength = 1;
  if (in.size(1) != 1) {
    inVectorLength = in.size(1);
  }
  if (in.size(1) == 1) {
    out.set_size(1, inVectorLength);
    for (int i{0}; i < inVectorLength; i++) {
      out[i] = in[0];
    }
  } else if (in.size(1) == 0) {
    out.set_size(1, inVectorLength);
    for (int i{0}; i < inVectorLength; i++) {
      out[i] = in[i];
    }
  } else {
    out.set_size(1, inVectorLength);
    for (int i{0}; i < inVectorLength; i++) {
      out[i] = in[i];
    }
  }
}

//
// Arguments    : ::coder::array<c_struct_T, 2U> &in
// Return Type  : void
//
void validator_check_size(::coder::array<c_struct_T, 2U> &in)
{
  if ((in.size(0) == 1) && (in.size(1) == 1)) {
    c_struct_T b_in;
    int outsize_idx_0;
    int outsize_idx_1;
    outsize_idx_0 = in.size(0);
    outsize_idx_1 = in.size(1);
    b_in = in[0];
    in.set_size(outsize_idx_0, outsize_idx_1);
    for (int i{0}; i < outsize_idx_1; i++) {
      for (int i1{0}; i1 < outsize_idx_0; i1++) {
        in[i1 + in.size(0) * i] = b_in;
      }
    }
  }
}

} // namespace internal
} // namespace coder

//
// File trailer for validator_check_size.cpp
//
// [EOF]
//
