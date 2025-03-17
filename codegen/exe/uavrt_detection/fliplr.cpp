//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: fliplr.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 04-Feb-2025 09:56:05
//

// Include Files
#include "fliplr.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : array<char, 2U> &x
// Return Type  : void
//
namespace coder {
void fliplr(array<char, 2U> &x)
{
  int nd2;
  nd2 = x.size(1) >> 1;
  for (int b_j1{0}; b_j1 < nd2; b_j1++) {
    int j2;
    char xtmp;
    j2 = (x.size(1) - b_j1) - 1;
    xtmp = x[b_j1];
    x[b_j1] = x[j2];
    x[j2] = xtmp;
  }
}

} // namespace coder

//
// File trailer for fliplr.cpp
//
// [EOF]
//
