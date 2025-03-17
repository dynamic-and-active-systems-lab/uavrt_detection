//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: flipud.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 04-Feb-2025 09:56:05
//

// Include Files
#include "flipud.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : array<creal_T, 1U> &x
// Return Type  : void
//
namespace coder {
void flipud(array<creal_T, 1U> &x)
{
  int m;
  int md2;
  m = x.size(0) - 1;
  md2 = x.size(0) >> 1;
  for (int i{0}; i < md2; i++) {
    double xtmp_im;
    double xtmp_re;
    int b_i;
    xtmp_re = x[i].re;
    xtmp_im = x[i].im;
    b_i = m - i;
    x[i] = x[b_i];
    x[b_i].re = xtmp_re;
    x[b_i].im = xtmp_im;
  }
}

} // namespace coder

//
// File trailer for flipud.cpp
//
// [EOF]
//
