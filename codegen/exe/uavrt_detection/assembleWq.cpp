//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: assembleWq.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 14:31:55
//

// Include Files
#include "assembleWq.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <string.h>

// Function Definitions
//
// Arguments    : coder::array<double, 2U> &in1
//                const double in2_data[]
//                const int in2_size[2]
// Return Type  : void
//
void binary_expand_op(coder::array<double, 2U> &in1, const double in2_data[],
                      const int in2_size[2])
{
  double in1_data;
  int aux_0_1;
  int aux_1_1;
  int in1_size_idx_0;
  int in1_size_idx_1;
  int loop_ub;
  int stride_0_0;
  int stride_0_1;
  int stride_1_0;
  int stride_1_1;
  if (in2_size[0] == 1) {
    in1_size_idx_0 = in1.size(0);
  } else {
    in1_size_idx_0 = in2_size[0];
  }
  if (in2_size[1] == 1) {
    in1_size_idx_1 = in1.size(1);
  } else {
    in1_size_idx_1 = in2_size[1];
  }
  stride_0_0 = (in1.size(0) != 1);
  stride_0_1 = (in1.size(1) != 1);
  stride_1_0 = (in2_size[0] != 1);
  stride_1_1 = (in2_size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  if (in2_size[1] == 1) {
    loop_ub = in1.size(1);
  } else {
    loop_ub = in2_size[1];
  }
  for (int i{0}; i < loop_ub; i++) {
    int b_loop_ub;
    if (in2_size[0] == 1) {
      b_loop_ub = in1.size(0);
    } else {
      b_loop_ub = in2_size[0];
    }
    for (int i1{0}; i1 < b_loop_ub; i1++) {
      in1_data = in1[i1 * stride_0_0 + in1.size(0) * aux_0_1] +
                 in2_data[i1 * stride_1_0 + in2_size[0] * aux_1_1];
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
  in1.set_size(in1_size_idx_0, in1_size_idx_1);
  for (int i{0}; i < in1_size_idx_1; i++) {
    for (int i1{0}; i1 < in1_size_idx_0; i1++) {
      in1[0] = in1_data;
    }
  }
}

//
// File trailer for assembleWq.cpp
//
// [EOF]
//
