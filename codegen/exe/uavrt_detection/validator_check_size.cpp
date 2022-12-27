//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// validator_check_size.cpp
//
// Code generation for function 'validator_check_size'
//

// Include files
#include "validator_check_size.h"
#include "int2str.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_internal_types.h"
#include "coder_array.h"
#include <stdio.h>
#include <string.h>

// Type Definitions
struct emxArray_char_T_1x10 {
  char data[10];
  int size[2];
};

// Function Definitions
namespace coder {
namespace internal {
boolean_T b_validator_check_size(const boolean_T in_data[], int in_size)
{
  emxArray_char_T_1x10 r;
  boolean_T out;
  if (in_size != 1) {
    int2str(0.0, r.data, r.size);
    if (in_size != 0) {
      out = in_data[0];
    }
  } else {
    out = in_data[0];
  }
  return out;
}

void c_validator_check_size(const ::coder::array<c_struct_T, 2U> &in,
                            ::coder::array<c_struct_T, 2U> &out)
{
  emxArray_char_T_1x10 b_in;
  int sizes_idx_0;
  int sizes_idx_1;
  boolean_T isempty_in;
  boolean_T isscalar_in;
  isscalar_in = ((in.size(0) == 1) && (in.size(1) == 1));
  isempty_in = ((in.size(0) == 0) || (in.size(1) == 0));
  if (isscalar_in) {
    sizes_idx_0 = 1;
    sizes_idx_1 = 1;
  } else {
    sizes_idx_0 = in.size(0);
    sizes_idx_1 = in.size(1);
  }
  if ((!isempty_in) && (!isscalar_in)) {
    char st[12];
    if (in.size(0) != sizes_idx_0) {
      int2str(static_cast<double>(in.size(0)), b_in.data, b_in.size);
      sprintf(&st[0], "%d", sizes_idx_0);
    }
    if (in.size(1) != sizes_idx_1) {
      int2str(static_cast<double>(in.size(1)), b_in.data, b_in.size);
      sprintf(&st[0], "%d", sizes_idx_1);
    }
  }
  if (isscalar_in) {
    out.set_size(sizes_idx_0, sizes_idx_1);
    sizes_idx_0 *= sizes_idx_1;
    for (sizes_idx_1 = 0; sizes_idx_1 < sizes_idx_0; sizes_idx_1++) {
      out[sizes_idx_1] = in[0];
    }
  } else if (isempty_in) {
    out.set_size(sizes_idx_0, sizes_idx_1);
    sizes_idx_0 *= sizes_idx_1;
    for (sizes_idx_1 = 0; sizes_idx_1 < sizes_idx_0; sizes_idx_1++) {
      out[sizes_idx_1] = in[sizes_idx_1];
    }
  } else {
    out.set_size(sizes_idx_0, sizes_idx_1);
    sizes_idx_0 *= sizes_idx_1;
    for (sizes_idx_1 = 0; sizes_idx_1 < sizes_idx_0; sizes_idx_1++) {
      out[sizes_idx_1] = in[sizes_idx_1];
    }
  }
}

void c_validator_check_size(const ::coder::array<double, 2U> &in,
                            ::coder::array<double, 2U> &out)
{
  emxArray_char_T_1x10 b_in;
  int sizes_idx_0;
  int sizes_idx_1;
  boolean_T isempty_in;
  boolean_T isscalar_in;
  isscalar_in = ((in.size(0) == 1) && (in.size(1) == 1));
  isempty_in = ((in.size(0) == 0) || (in.size(1) == 0));
  if (isscalar_in) {
    sizes_idx_0 = 1;
    sizes_idx_1 = 1;
  } else {
    sizes_idx_0 = in.size(0);
    sizes_idx_1 = in.size(1);
  }
  if ((!isempty_in) && (!isscalar_in)) {
    char st[12];
    if (in.size(0) != sizes_idx_0) {
      int2str(static_cast<double>(in.size(0)), b_in.data, b_in.size);
      sprintf(&st[0], "%d", sizes_idx_0);
    }
    if (in.size(1) != sizes_idx_1) {
      int2str(static_cast<double>(in.size(1)), b_in.data, b_in.size);
      sprintf(&st[0], "%d", sizes_idx_1);
    }
  }
  if (isscalar_in) {
    out.set_size(sizes_idx_0, sizes_idx_1);
    sizes_idx_0 *= sizes_idx_1;
    for (sizes_idx_1 = 0; sizes_idx_1 < sizes_idx_0; sizes_idx_1++) {
      out[sizes_idx_1] = in[0];
    }
  } else if (isempty_in) {
    out.set_size(sizes_idx_0, sizes_idx_1);
    sizes_idx_0 *= sizes_idx_1;
    for (sizes_idx_1 = 0; sizes_idx_1 < sizes_idx_0; sizes_idx_1++) {
      out[sizes_idx_1] = in[sizes_idx_1];
    }
  } else {
    out.set_size(sizes_idx_0, sizes_idx_1);
    sizes_idx_0 *= sizes_idx_1;
    for (sizes_idx_1 = 0; sizes_idx_1 < sizes_idx_0; sizes_idx_1++) {
      out[sizes_idx_1] = in[sizes_idx_1];
    }
  }
}

void d_validator_check_size(const ::coder::array<boolean_T, 2U> &in,
                            ::coder::array<boolean_T, 2U> &out)
{
  emxArray_char_T_1x10 b_in;
  int sizes_idx_0;
  int sizes_idx_1;
  boolean_T isempty_in;
  boolean_T isscalar_in;
  isscalar_in = ((in.size(0) == 1) && (in.size(1) == 1));
  isempty_in = ((in.size(0) == 0) || (in.size(1) == 0));
  if (isscalar_in) {
    sizes_idx_0 = 1;
    sizes_idx_1 = 1;
  } else {
    sizes_idx_0 = in.size(0);
    sizes_idx_1 = in.size(1);
  }
  if ((!isempty_in) && (!isscalar_in)) {
    char st[12];
    if (in.size(0) != sizes_idx_0) {
      int2str(static_cast<double>(in.size(0)), b_in.data, b_in.size);
      sprintf(&st[0], "%d", sizes_idx_0);
    }
    if (in.size(1) != sizes_idx_1) {
      int2str(static_cast<double>(in.size(1)), b_in.data, b_in.size);
      sprintf(&st[0], "%d", sizes_idx_1);
    }
  }
  if (isscalar_in) {
    out.set_size(sizes_idx_0, sizes_idx_1);
    sizes_idx_0 *= sizes_idx_1;
    for (sizes_idx_1 = 0; sizes_idx_1 < sizes_idx_0; sizes_idx_1++) {
      out[sizes_idx_1] = in[0];
    }
  } else if (isempty_in) {
    out.set_size(sizes_idx_0, sizes_idx_1);
    sizes_idx_0 *= sizes_idx_1;
    for (sizes_idx_1 = 0; sizes_idx_1 < sizes_idx_0; sizes_idx_1++) {
      out[sizes_idx_1] = in[sizes_idx_1];
    }
  } else {
    out.set_size(sizes_idx_0, sizes_idx_1);
    sizes_idx_0 *= sizes_idx_1;
    for (sizes_idx_1 = 0; sizes_idx_1 < sizes_idx_0; sizes_idx_1++) {
      out[sizes_idx_1] = in[sizes_idx_1];
    }
  }
}

void validator_check_size(const ::coder::array<double, 2U> &in,
                          ::coder::array<double, 2U> &out)
{
  emxArray_char_T_1x10 b_in;
  int sizes_idx_0;
  boolean_T b;
  boolean_T hasMismatchingDims;
  boolean_T isscalar_in;
  isscalar_in = ((in.size(0) == 1) && (in.size(1) == 1));
  b = (in.size(0) == 0);
  hasMismatchingDims = false;
  if (b) {
    hasMismatchingDims = (in.size(1) != 2);
  }
  if (isscalar_in) {
    sizes_idx_0 = 1;
  } else if (b && hasMismatchingDims) {
    sizes_idx_0 = 0;
  } else {
    sizes_idx_0 = in.size(0);
  }
  if ((!b) && (!isscalar_in)) {
    if (in.size(0) != sizes_idx_0) {
      char st[12];
      int2str(static_cast<double>(in.size(0)), b_in.data, b_in.size);
      sprintf(&st[0], "%d", sizes_idx_0);
    }
    if (in.size(1) != 2) {
      int2str(static_cast<double>(in.size(1)), b_in.data, b_in.size);
    }
  }
  if (isscalar_in) {
    out.set_size(sizes_idx_0, 2);
    sizes_idx_0 <<= 1;
    for (int i{0}; i < sizes_idx_0; i++) {
      out[i] = in[0];
    }
  } else if (b) {
    out.set_size(sizes_idx_0, 2);
    sizes_idx_0 <<= 1;
    for (int i{0}; i < sizes_idx_0; i++) {
      out[i] = in[i];
    }
  } else {
    out.set_size(sizes_idx_0, 2);
    sizes_idx_0 <<= 1;
    for (int i{0}; i < sizes_idx_0; i++) {
      out[i] = in[i];
    }
  }
}

void validator_check_size(const ::coder::array<creal32_T, 2U> &in,
                          ::coder::array<creal32_T, 2U> &out)
{
  emxArray_char_T_1x10 b_in;
  int sizes_idx_1;
  boolean_T b;
  boolean_T b1;
  b = (in.size(1) == 1);
  b1 = (in.size(1) == 0);
  if (b) {
    sizes_idx_1 = 1;
  } else {
    sizes_idx_1 = in.size(1);
  }
  if ((!b1) && (!b) && (in.size(1) != sizes_idx_1)) {
    char st[12];
    int2str(static_cast<double>(in.size(1)), b_in.data, b_in.size);
    sprintf(&st[0], "%d", sizes_idx_1);
  }
  if (b) {
    out.set_size(1, sizes_idx_1);
    for (int i{0}; i < sizes_idx_1; i++) {
      out[i] = in[0];
    }
  } else if (b1) {
    out.set_size(1, sizes_idx_1);
    for (int i{0}; i < sizes_idx_1; i++) {
      out[i] = in[i];
    }
  } else {
    out.set_size(1, sizes_idx_1);
    for (int i{0}; i < sizes_idx_1; i++) {
      out[i] = in[i];
    }
  }
}

void validator_check_size(const ::coder::array<creal_T, 2U> &in,
                          ::coder::array<creal_T, 2U> &out)
{
  emxArray_char_T_1x10 b_in;
  int sizes_idx_0;
  int sizes_idx_1;
  boolean_T isempty_in;
  boolean_T isscalar_in;
  isscalar_in = ((in.size(0) == 1) && (in.size(1) == 1));
  isempty_in = ((in.size(0) == 0) || (in.size(1) == 0));
  if (isscalar_in) {
    sizes_idx_0 = 1;
    sizes_idx_1 = 1;
  } else {
    sizes_idx_0 = in.size(0);
    sizes_idx_1 = in.size(1);
  }
  if ((!isempty_in) && (!isscalar_in)) {
    char st[12];
    if (in.size(0) != sizes_idx_0) {
      int2str(static_cast<double>(in.size(0)), b_in.data, b_in.size);
      sprintf(&st[0], "%d", sizes_idx_0);
    }
    if (in.size(1) != sizes_idx_1) {
      int2str(static_cast<double>(in.size(1)), b_in.data, b_in.size);
      sprintf(&st[0], "%d", sizes_idx_1);
    }
  }
  if (isscalar_in) {
    out.set_size(sizes_idx_0, sizes_idx_1);
    sizes_idx_0 *= sizes_idx_1;
    for (sizes_idx_1 = 0; sizes_idx_1 < sizes_idx_0; sizes_idx_1++) {
      out[sizes_idx_1] = in[0];
    }
  } else if (isempty_in) {
    out.set_size(sizes_idx_0, sizes_idx_1);
    sizes_idx_0 *= sizes_idx_1;
    for (sizes_idx_1 = 0; sizes_idx_1 < sizes_idx_0; sizes_idx_1++) {
      out[sizes_idx_1] = in[sizes_idx_1];
    }
  } else {
    out.set_size(sizes_idx_0, sizes_idx_1);
    sizes_idx_0 *= sizes_idx_1;
    for (sizes_idx_1 = 0; sizes_idx_1 < sizes_idx_0; sizes_idx_1++) {
      out[sizes_idx_1] = in[sizes_idx_1];
    }
  }
}

void validator_check_size(const ::coder::array<double, 1U> &in,
                          ::coder::array<double, 2U> &out)
{
  emxArray_char_T_1x10 b_in;
  int sizes_idx_0;
  boolean_T isempty_in;
  boolean_T isscalar_in;
  isscalar_in = (in.size(0) == 1);
  isempty_in = (in.size(0) == 0);
  if (isscalar_in) {
    sizes_idx_0 = 1;
  } else {
    sizes_idx_0 = in.size(0);
  }
  if ((!isempty_in) && (!isscalar_in) && (in.size(0) != sizes_idx_0)) {
    char st[12];
    int2str(static_cast<double>(in.size(0)), b_in.data, b_in.size);
    sprintf(&st[0], "%d", sizes_idx_0);
  }
  if (isscalar_in) {
    out.set_size(sizes_idx_0, 1);
    for (int i{0}; i < sizes_idx_0; i++) {
      out[i] = in[0];
    }
  } else if (isempty_in) {
    out.set_size(sizes_idx_0, 1);
    for (int i{0}; i < sizes_idx_0; i++) {
      out[i] = in[i];
    }
  } else {
    out.set_size(sizes_idx_0, 1);
    for (int i{0}; i < sizes_idx_0; i++) {
      out[i] = in[i];
    }
  }
}

void validator_check_size(const ::coder::array<double, 1U> &in,
                          ::coder::array<double, 1U> &out)
{
  emxArray_char_T_1x10 b_in;
  int sizes_idx_0;
  boolean_T isempty_in;
  boolean_T isscalar_in;
  isscalar_in = (in.size(0) == 1);
  isempty_in = (in.size(0) == 0);
  if (isscalar_in) {
    sizes_idx_0 = 1;
  } else {
    sizes_idx_0 = in.size(0);
  }
  if ((!isempty_in) && (!isscalar_in) && (in.size(0) != sizes_idx_0)) {
    char st[12];
    int2str(static_cast<double>(in.size(0)), b_in.data, b_in.size);
    sprintf(&st[0], "%d", sizes_idx_0);
  }
  if (isscalar_in) {
    out.set_size(sizes_idx_0);
    for (int i{0}; i < sizes_idx_0; i++) {
      out[i] = in[0];
    }
  } else if (isempty_in) {
    out.set_size(sizes_idx_0);
    for (int i{0}; i < sizes_idx_0; i++) {
      out[i] = in[i];
    }
  } else {
    out.set_size(sizes_idx_0);
    for (int i{0}; i < sizes_idx_0; i++) {
      out[i] = in[i];
    }
  }
}

void validator_check_size(const ::coder::array<c_struct_T, 2U> &in,
                          ::coder::array<c_struct_T, 2U> &out)
{
  emxArray_char_T_1x10 b_in;
  int sizes_idx_1;
  boolean_T b;
  boolean_T b1;
  b = (in.size(1) == 1);
  b1 = (in.size(1) == 0);
  if (b) {
    sizes_idx_1 = 1;
  } else {
    sizes_idx_1 = in.size(1);
  }
  if ((!b1) && (!b) && (in.size(1) != sizes_idx_1)) {
    char st[12];
    int2str(static_cast<double>(in.size(1)), b_in.data, b_in.size);
    sprintf(&st[0], "%d", sizes_idx_1);
  }
  if (b) {
    out.set_size(1, sizes_idx_1);
    for (int i{0}; i < sizes_idx_1; i++) {
      out[i] = in[0];
    }
  } else if (b1) {
    out.set_size(1, sizes_idx_1);
    for (int i{0}; i < sizes_idx_1; i++) {
      out[i] = in[i];
    }
  } else {
    out.set_size(1, sizes_idx_1);
    for (int i{0}; i < sizes_idx_1; i++) {
      out[i] = in[i];
    }
  }
}

} // namespace internal
} // namespace coder

// End of code generation (validator_check_size.cpp)
