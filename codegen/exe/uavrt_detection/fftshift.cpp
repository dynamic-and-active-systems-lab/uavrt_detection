//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: fftshift.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 23-Mar-2023 12:56:08
//

// Include Files
#include "fftshift.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <string.h>

// Function Definitions
//
// Arguments    : ::coder::array<creal_T, 2U> &x
// Return Type  : void
//
namespace coder {
void fftshift(::coder::array<creal_T, 2U> &x)
{
  if (x.size(0) > 1) {
    int vlend2;
    vlend2 = x.size(0) / 2 - 1;
    if ((vlend2 + 1) << 1 == x.size(0)) {
      for (int k{0}; k <= vlend2; k++) {
        creal_T xtmp;
        int i;
        xtmp = x[k];
        i = (vlend2 + k) + 1;
        x[k] = x[i];
        x[i] = xtmp;
      }
    } else {
      creal_T xtmp;
      xtmp = x[vlend2 + 1];
      for (int k{0}; k <= vlend2; k++) {
        int i;
        i = (vlend2 + k) + 1;
        x[i] = x[k];
        x[k] = x[i + 1];
      }
      x[(vlend2 + vlend2) + 2] = xtmp;
    }
  }
}

} // namespace coder

//
// File trailer for fftshift.cpp
//
// [EOF]
//
