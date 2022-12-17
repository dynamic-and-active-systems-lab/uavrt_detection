//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: weightingmatrix.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 17-Dec-2022 12:06:22
//

// Include Files
#include "weightingmatrix.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <string.h>

// Function Definitions
//
// Arguments    : coder::array<creal_T, 2U> &in1
//                const coder::array<creal_T, 2U> &in2
//                int in3
//                int in4
//                const coder::array<double, 2U> &in5
// Return Type  : void
//
void binary_expand_op(coder::array<creal_T, 2U> &in1,
                      const coder::array<creal_T, 2U> &in2, int in3, int in4,
                      const coder::array<double, 2U> &in5)
{
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in5.size(0) == 1) {
    i = in4;
  } else {
    i = in5.size(0);
  }
  in1.set_size(i, 1);
  stride_0_0 = (in4 != 1);
  stride_1_0 = (in5.size(0) != 1);
  if (in5.size(0) == 1) {
    loop_ub = in4;
  } else {
    loop_ub = in5.size(0);
  }
  for (i = 0; i < loop_ub; i++) {
    double d;
    d = in5[i * stride_1_0];
    in1[i].re = d * in2[i * stride_0_0 + in2.size(0) * in3].re;
    in1[i].im = d * in2[i * stride_0_0 + in2.size(0) * in3].im;
  }
}

//
// File trailer for weightingmatrix.cpp
//
// [EOF]
//
