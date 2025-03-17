//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: toeplitz.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "toeplitz.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const array<creal_T, 1U> &c
//                const array<creal_T, 1U> &r
//                array<creal_T, 2U> &t
// Return Type  : void
//
namespace coder {
void toeplitz(const array<creal_T, 1U> &c, const array<creal_T, 1U> &r,
              array<creal_T, 2U> &t)
{
  int i;
  int i1;
  int ij;
  i = c.size(0);
  i1 = r.size(0);
  t.set_size(c.size(0), r.size(0));
  ij = 0;
  for (int j{0}; j < i1; j++) {
    int k;
    k = j;
    for (int b_i{0}; b_i < i; b_i++) {
      if (b_i < j) {
        t[ij + b_i] = r[k];
        k--;
      } else {
        t[ij + b_i] = c[k];
        k++;
      }
    }
    if (i - 1 >= 0) {
      ij += i;
    }
  }
}

} // namespace coder

//
// File trailer for toeplitz.cpp
//
// [EOF]
//
