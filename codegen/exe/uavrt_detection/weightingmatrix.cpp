//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: weightingmatrix.cpp
//
<<<<<<< HEAD
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 23-May-2023 12:05:02
=======
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Apr-2023 11:47:02
>>>>>>> 3930a1e557481905555f2756f2f70ac82e87beba
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
void binary_expand_op(coder::array<creal_T, 2U> &in1,
                      const coder::array<creal_T, 2U> &in2, int in3,
                      const coder::array<double, 2U> &in4)
{
  int in2_idx_0;
  int loop_ub;
  int stride_1_0;
  in2_idx_0 = in2.size(0);
  if (in4.size(0) == 1) {
    loop_ub = in2_idx_0;
  } else {
    loop_ub = in4.size(0);
  }
  in1.set_size(loop_ub, 1);
  in2_idx_0 = (in2_idx_0 != 1);
  stride_1_0 = (in4.size(0) != 1);
  for (int i{0}; i < loop_ub; i++) {
    double d;
    int i1;
    d = in4[i * stride_1_0];
    i1 = i * in2_idx_0;
    in1[i].re = d * in2[i1 + in2.size(0) * in3].re;
    in1[i].im = d * in2[i1 + in2.size(0) * in3].im;
  }
}

//
// File trailer for weightingmatrix.cpp
//
// [EOF]
//
