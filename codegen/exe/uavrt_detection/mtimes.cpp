//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: mtimes.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 16-Mar-2023 20:12:42
//

// Include Files
#include "mtimes.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <string.h>

// Function Definitions
//
// Arguments    : const ::coder::array<creal_T, 2U> &A
//                const ::coder::array<creal_T, 2U> &B
//                ::coder::array<creal_T, 2U> &C
// Return Type  : void
//
namespace coder {
namespace internal {
namespace blas {
void mtimes(const ::coder::array<creal_T, 2U> &A,
            const ::coder::array<creal_T, 2U> &B,
            ::coder::array<creal_T, 2U> &C)
{
  int inner;
  int m;
  int n;
  m = A.size(0);
  inner = A.size(1);
  n = B.size(1);
  C.set_size(A.size(0), B.size(1));
  if (B.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int j{0}; j < n; j++) {
    int boffset;
    int coffset;
    coffset = j * m;
    boffset = j * B.size(0);
    if (m > 2147483646) {
      check_forloop_overflow_error();
    }
    for (int i{0}; i < m; i++) {
      double s_im;
      double s_re;
      int A_re_tmp;
      s_re = 0.0;
      s_im = 0.0;
      if (inner > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int k{0}; k < inner; k++) {
        A_re_tmp = boffset + k;
        s_re += A[k * A.size(0) + i].re * B[A_re_tmp].re -
                A[k * A.size(0) + i].im * B[A_re_tmp].im;
        s_im += A[k * A.size(0) + i].re * B[A_re_tmp].im +
                A[k * A.size(0) + i].im * B[A_re_tmp].re;
      }
      A_re_tmp = coffset + i;
      C[A_re_tmp].re = s_re;
      C[A_re_tmp].im = s_im;
    }
  }
}

} // namespace blas
} // namespace internal
} // namespace coder

//
// File trailer for mtimes.cpp
//
// [EOF]
//
