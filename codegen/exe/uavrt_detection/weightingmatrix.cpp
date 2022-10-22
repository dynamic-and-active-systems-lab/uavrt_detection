//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: weightingmatrix.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Oct-2022 17:38:50
//

// Include Files
#include "weightingmatrix.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : coder::array<creal_T, 2U> &in1
//                const coder::array<creal_T, 2U> &in2
//                int in3
//                const coder::array<double, 2U> &in4
// Return Type  : void
//
void b_binary_expand_op(coder::array<creal_T, 2U> &in1,
                        const coder::array<creal_T, 2U> &in2, int in3,
                        const coder::array<double, 2U> &in4)
{
  int i;
  int in2_idx_0;
  int stride_0_0;
  int stride_1_0;
  in2_idx_0 = in2.size(0);
  if (in4.size(0) == 1) {
    i = in2_idx_0;
  } else {
    i = in4.size(0);
  }
  in1.set_size(i, 1);
  stride_0_0 = (in2_idx_0 != 1);
  stride_1_0 = (in4.size(0) != 1);
  if (in4.size(0) != 1) {
    in2_idx_0 = in4.size(0);
  }
  for (i = 0; i < in2_idx_0; i++) {
    double d;
    int i1;
    i1 = i * stride_0_0;
    d = in4[i * stride_1_0];
    in1[i].re = d * in2[i1 + in2.size(0) * in3].re;
    in1[i].im = d * in2[i1 + in2.size(0) * in3].im;
  }
}

//
// File trailer for weightingmatrix.cpp
//
// [EOF]
//
