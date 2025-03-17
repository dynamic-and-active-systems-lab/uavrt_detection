//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: weightingmatrix.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "weightingmatrix.h"
#include "fft.h"
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
void binary_expand_op(coder::array<creal_T, 2U> &in1,
                      const coder::array<creal_T, 2U> &in2, int in3,
                      const coder::array<double, 2U> &in4)
{
  coder::array<creal_T, 2U> b_in2;
  int in2_idx_0;
  int loop_ub;
  int stride_1_0;
  in2_idx_0 = in2.size(0);
  if (in4.size(0) == 1) {
    loop_ub = in2_idx_0;
  } else {
    loop_ub = in4.size(0);
  }
  b_in2.set_size(loop_ub, 1);
  in2_idx_0 = (in2_idx_0 != 1);
  stride_1_0 = (in4.size(0) != 1);
  for (int i{0}; i < loop_ub; i++) {
    double d;
    int i1;
    d = in4[i * stride_1_0];
    i1 = i * in2_idx_0;
    b_in2[i].re = d * in2[i1 + in2.size(0) * in3].re;
    b_in2[i].im = d * in2[i1 + in2.size(0) * in3].im;
  }
  coder::fft(b_in2, in1);
}

//
// File trailer for weightingmatrix.cpp
//
// [EOF]
//
