//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: assembleWq.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 30-Dec-2022 11:43:16
//

// Include Files
#include "assembleWq.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <string.h>

// Function Definitions
//
// Arguments    : coder::array<double, 2U> &in1
//                const coder::array<double, 2U> &in2
// Return Type  : void
//
void plus(coder::array<double, 2U> &in1, const coder::array<double, 2U> &in2)
{
  coder::array<double, 2U> b_in1;
  int aux_0_1;
  int aux_1_1;
  int b_loop_ub;
  int i;
  int i1;
  int loop_ub;
  int stride_0_0;
  int stride_0_1;
  int stride_1_0;
  int stride_1_1;
  if (in2.size(0) == 1) {
    i = in1.size(0);
  } else {
    i = in2.size(0);
  }
  if (in2.size(1) == 1) {
    i1 = in1.size(1);
  } else {
    i1 = in2.size(1);
  }
  b_in1.set_size(i, i1);
  stride_0_0 = (in1.size(0) != 1);
  stride_0_1 = (in1.size(1) != 1);
  stride_1_0 = (in2.size(0) != 1);
  stride_1_1 = (in2.size(1) != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  if (in2.size(1) == 1) {
    loop_ub = in1.size(1);
  } else {
    loop_ub = in2.size(1);
  }
  for (i = 0; i < loop_ub; i++) {
    if (in2.size(0) == 1) {
      b_loop_ub = in1.size(0);
    } else {
      b_loop_ub = in2.size(0);
    }
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      b_in1[i1 + b_in1.size(0) * i] =
          in1[i1 * stride_0_0 + in1.size(0) * aux_0_1] +
          in2[i1 * stride_1_0 + in2.size(0) * aux_1_1];
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
  in1.set_size(b_in1.size(0), b_in1.size(1));
  loop_ub = b_in1.size(1);
  for (i = 0; i < loop_ub; i++) {
    b_loop_ub = b_in1.size(0);
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      in1[i1 + in1.size(0) * i] = b_in1[i1 + b_in1.size(0) * i];
    }
  }
}

//
// File trailer for assembleWq.cpp
//
// [EOF]
//
