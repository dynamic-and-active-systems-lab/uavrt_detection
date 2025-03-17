//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: mtimes.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "mtimes.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const array<creal_T, 2U> &A
//                const array<creal_T, 2U> &B
//                array<creal_T, 2U> &C
// Return Type  : void
//
namespace coder {
namespace internal {
namespace blas {
void b_mtimes(const array<creal_T, 2U> &A, const array<creal_T, 2U> &B,
              array<creal_T, 2U> &C)
{
  int inner;
  int m_tmp;
  int n_tmp;
  m_tmp = A.size(0);
  inner = A.size(1);
  n_tmp = B.size(1);
  C.set_size(A.size(0), B.size(1));
  if (B.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int j{0}; j < n_tmp; j++) {
    int boffset;
    int coffset;
    coffset = j * m_tmp;
    boffset = j * B.size(0);
    if (m_tmp > 2147483646) {
      check_forloop_overflow_error();
    }
    for (int i{0}; i < m_tmp; i++) {
      double s_im;
      double s_re;
      int A_re_tmp;
      s_re = 0.0;
      s_im = 0.0;
      if (inner > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int k{0}; k < inner; k++) {
        double c_A_re_tmp;
        double d_A_re_tmp;
        double e_A_re_tmp;
        double f_A_re_tmp;
        int b_A_re_tmp;
        A_re_tmp = k * A.size(0) + i;
        b_A_re_tmp = boffset + k;
        c_A_re_tmp = A[A_re_tmp].re;
        d_A_re_tmp = B[b_A_re_tmp].im;
        e_A_re_tmp = A[A_re_tmp].im;
        f_A_re_tmp = B[b_A_re_tmp].re;
        s_re += c_A_re_tmp * f_A_re_tmp - e_A_re_tmp * d_A_re_tmp;
        s_im += c_A_re_tmp * d_A_re_tmp + e_A_re_tmp * f_A_re_tmp;
      }
      A_re_tmp = coffset + i;
      C[A_re_tmp].re = s_re;
      C[A_re_tmp].im = s_im;
    }
  }
}

//
// Arguments    : const array<creal_T, 2U> &A
//                const array<creal_T, 2U> &B
//                array<creal_T, 2U> &C
// Return Type  : void
//
void mtimes(const array<creal_T, 2U> &A, const array<creal_T, 2U> &B,
            array<creal_T, 2U> &C)
{
  int inner;
  int m_tmp;
  int n_tmp;
  m_tmp = A.size(1);
  inner = A.size(0);
  n_tmp = B.size(1);
  C.set_size(A.size(1), B.size(1));
  if (B.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int j{0}; j < n_tmp; j++) {
    int boffset;
    int coffset;
    coffset = j * m_tmp;
    boffset = j * B.size(0);
    if (m_tmp > 2147483646) {
      check_forloop_overflow_error();
    }
    for (int i{0}; i < m_tmp; i++) {
      double s_im;
      double s_re;
      int aoffset;
      aoffset = i * A.size(0);
      s_re = 0.0;
      s_im = 0.0;
      if (inner > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int k{0}; k < inner; k++) {
        double A_im;
        double A_re;
        double b_A_re_tmp;
        double c_A_re_tmp;
        int A_re_tmp;
        A_re_tmp = aoffset + k;
        A_re = A[A_re_tmp].re;
        A_im = -A[A_re_tmp].im;
        A_re_tmp = boffset + k;
        b_A_re_tmp = B[A_re_tmp].im;
        c_A_re_tmp = B[A_re_tmp].re;
        s_re += A_re * c_A_re_tmp - A_im * b_A_re_tmp;
        s_im += A_re * b_A_re_tmp + A_im * c_A_re_tmp;
      }
      aoffset = coffset + i;
      C[aoffset].re = s_re;
      C[aoffset].im = s_im;
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
