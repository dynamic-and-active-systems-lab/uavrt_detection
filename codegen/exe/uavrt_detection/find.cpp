//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: find.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 22-Oct-2022 15:24:58
//

// Include Files
#include "find.h"
#include "rt_nonfinite.h"
#include "sparse1.h"
#include "threshold.h"
#include "uavrt_detection_rtwutil.h"
#include "waveform.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : int in1_data[]
//                int *in1_size
//                const coder::array<double, 1U> &in2
//                int in3
//                int in4
//                int in5
//                const waveform *in6
//                int in7
//                int in8
//                int in9
// Return Type  : void
//
void b_binary_expand_op(int in1_data[], int *in1_size,
                        const coder::array<double, 1U> &in2, int in3, int in4,
                        int in5, const waveform *in6, int in7, int in8, int in9)
{
  coder::array<boolean_T, 1U> b_in2;
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (div_s32(in9 - in7, in8) + 1 == 1) {
    i = div_s32(in5 - in3, in4) + 1;
  } else {
    i = div_s32(in9 - in7, in8) + 1;
  }
  b_in2.set_size(i);
  stride_0_0 = (div_s32(in5 - in3, in4) + 1 != 1);
  stride_1_0 = (div_s32(in9 - in7, in8) + 1 != 1);
  if (div_s32(in9 - in7, in8) + 1 == 1) {
    loop_ub = div_s32(in5 - in3, in4) + 1;
  } else {
    loop_ub = div_s32(in9 - in7, in8) + 1;
  }
  for (i = 0; i < loop_ub; i++) {
    b_in2[i] = (in2[in3 + in4 * (i * stride_0_0)] <
                in6->thresh.threshVecFine[in7 + in8 * (i * stride_1_0)]);
  }
  coder::c_eml_find(b_in2, in1_data, in1_size);
}

//
// Arguments    : int in1_data[]
//                int *in1_size
//                const coder::array<double, 1U> &in2
//                int in3
//                int in4
//                const waveform *in5
//                int in6
//                int in7
// Return Type  : void
//
void b_binary_expand_op(int in1_data[], int *in1_size,
                        const coder::array<double, 1U> &in2, int in3, int in4,
                        const waveform *in5, int in6, int in7)
{
  coder::array<boolean_T, 1U> b_in2;
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if ((in7 - in6) + 1 == 1) {
    i = (in4 - in3) + 1;
  } else {
    i = (in7 - in6) + 1;
  }
  b_in2.set_size(i);
  stride_0_0 = ((in4 - in3) + 1 != 1);
  stride_1_0 = ((in7 - in6) + 1 != 1);
  if ((in7 - in6) + 1 == 1) {
    loop_ub = (in4 - in3) + 1;
  } else {
    loop_ub = (in7 - in6) + 1;
  }
  for (i = 0; i < loop_ub; i++) {
    b_in2[i] = (in2[in3 + i * stride_0_0] <
                in5->thresh.threshVecFine[in6 + i * stride_1_0]);
  }
  coder::c_eml_find(b_in2, in1_data, in1_size);
}

//
// Arguments    : const ::coder::array<boolean_T, 2U> &x
//                ::coder::array<int, 2U> &i
// Return Type  : void
//
namespace coder {
void b_eml_find(const ::coder::array<boolean_T, 2U> &x,
                ::coder::array<int, 2U> &i)
{
  int idx;
  int ii;
  int nx;
  boolean_T exitg1;
  nx = x.size(1);
  idx = 0;
  i.set_size(1, x.size(1));
  ii = 0;
  exitg1 = false;
  while ((!exitg1) && (ii <= nx - 1)) {
    if (x[ii]) {
      idx++;
      i[idx - 1] = ii + 1;
      if (idx >= nx) {
        exitg1 = true;
      } else {
        ii++;
      }
    } else {
      ii++;
    }
  }
  if (x.size(1) == 1) {
    if (idx == 0) {
      i.set_size(1, 0);
    }
  } else {
    if (idx < 1) {
      idx = 0;
    }
    i.set_size(i.size(0), idx);
  }
}

//
// Arguments    : const ::coder::array<boolean_T, 1U> &x
//                int i_data[]
//                int *i_size
// Return Type  : void
//
void c_eml_find(const ::coder::array<boolean_T, 1U> &x, int i_data[],
                int *i_size)
{
  int idx;
  int ii;
  boolean_T exitg1;
  *i_size = (x.size(0) >= 1);
  idx = 0;
  ii = 0;
  exitg1 = false;
  while ((!exitg1) && (ii <= x.size(0) - 1)) {
    if (x[ii]) {
      idx = 1;
      i_data[0] = ii + 1;
      exitg1 = true;
    } else {
      ii++;
    }
  }
  if (*i_size == 1) {
    if (idx == 0) {
      *i_size = 0;
    }
  } else {
    *i_size = (idx >= 1);
  }
}

//
// Arguments    : const ::coder::array<boolean_T, 1U> &x
//                int i_data[]
//                int *i_size
// Return Type  : void
//
void d_eml_find(const ::coder::array<boolean_T, 1U> &x, int i_data[],
                int *i_size)
{
  int idx;
  int ii;
  boolean_T exitg1;
  *i_size = (x.size(0) >= 1);
  ii = x.size(0);
  idx = 0;
  exitg1 = false;
  while ((!exitg1) && (ii > 0)) {
    if (x[ii - 1]) {
      idx = 1;
      i_data[0] = ii;
      exitg1 = true;
    } else {
      ii--;
    }
  }
  if (*i_size == 1) {
    if (idx == 0) {
      *i_size = 0;
    }
  } else {
    *i_size = (idx >= 1);
  }
}

//
// Arguments    : const sparse *x
//                ::coder::array<int, 1U> &i
//                ::coder::array<int, 1U> &j
// Return Type  : void
//
void e_eml_find(const sparse *x, ::coder::array<int, 1U> &i,
                ::coder::array<int, 1U> &j)
{
  int nx;
  nx = x->colidx[x->colidx.size(0) - 1] - 1;
  if (x->colidx[x->colidx.size(0) - 1] - 1 == 0) {
    i.set_size(0);
    j.set_size(0);
  } else {
    int col;
    int idx;
    i.set_size(x->colidx[x->colidx.size(0) - 1] - 1);
    j.set_size(x->colidx[x->colidx.size(0) - 1] - 1);
    for (idx = 0; idx < nx; idx++) {
      i[idx] = x->rowidx[idx];
    }
    idx = 0;
    col = 1;
    while (idx < nx) {
      if (idx == x->colidx[col] - 1) {
        col++;
      } else {
        idx++;
        j[idx - 1] = col;
      }
    }
    if (x->colidx[x->colidx.size(0) - 1] - 1 == 1) {
      if (idx == 0) {
        i.set_size(0);
        j.set_size(0);
      }
    } else {
      if (idx < 1) {
        nx = 0;
      } else {
        nx = idx;
      }
      i.set_size(nx);
      if (idx < 1) {
        idx = 0;
      }
      j.set_size(idx);
    }
  }
}

//
// Arguments    : const ::coder::array<boolean_T, 2U> &x
//                int i_data[]
//                int i_size[2]
// Return Type  : void
//
void eml_find(const ::coder::array<boolean_T, 2U> &x, int i_data[],
              int i_size[2])
{
  array<int, 2U> i;
  int idx;
  int ii;
  int k;
  boolean_T exitg1;
  k = (x.size(1) >= 1);
  idx = 0;
  i.set_size(1, k);
  ii = 0;
  exitg1 = false;
  while ((!exitg1) && (ii <= x.size(1) - 1)) {
    if (x[ii]) {
      idx++;
      i[idx - 1] = ii + 1;
      if (idx >= k) {
        exitg1 = true;
      } else {
        ii++;
      }
    } else {
      ii++;
    }
  }
  if (k == 1) {
    if (idx == 0) {
      i.set_size(1, 0);
    }
  } else {
    i.set_size(i.size(0), static_cast<int>(idx >= 1));
  }
  i_size[0] = 1;
  i_size[1] = i.size(1);
  k = i.size(1);
  if (k - 1 >= 0) {
    i_data[0] = i[0];
  }
}

} // namespace coder

//
// File trailer for find.cpp
//
// [EOF]
//
