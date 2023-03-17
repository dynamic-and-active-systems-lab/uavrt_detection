//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: str2double1.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 16-Mar-2023 20:12:42
//

// Include Files
#include "str2double1.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include <string.h>

// Function Declarations
namespace coder {
namespace internal {
static boolean_T copydigits(::coder::array<char, 2U> &s1, int *idx,
                            const ::coder::array<char, 2U> &s, int *k, int n,
                            boolean_T allowpoint);

}
} // namespace coder

// Function Definitions
//
// Arguments    : ::coder::array<char, 2U> &s1
//                int *idx
//                const ::coder::array<char, 2U> &s
//                int *k
//                int n
//                boolean_T allowpoint
// Return Type  : boolean_T
//
namespace coder {
namespace internal {
static boolean_T copydigits(::coder::array<char, 2U> &s1, int *idx,
                            const ::coder::array<char, 2U> &s, int *k, int n,
                            boolean_T allowpoint)
{
  boolean_T exitg1;
  boolean_T haspoint;
  boolean_T success;
  success = (*k <= n);
  haspoint = false;
  exitg1 = false;
  while ((!exitg1) && (success && (*k <= n))) {
    char c;
    c = s[*k - 1];
    if ((c >= '0') && (c <= '9')) {
      s1[*idx - 1] = c;
      (*idx)++;
      (*k)++;
    } else if (c == '.') {
      if (allowpoint && (!haspoint)) {
        success = true;
      } else {
        success = false;
      }
      if (success) {
        s1[*idx - 1] = '.';
        (*idx)++;
        haspoint = true;
      }
      (*k)++;
    } else if (c == ',') {
      (*k)++;
    } else {
      exitg1 = true;
    }
  }
  return success;
}

//
// Arguments    : ::coder::array<char, 2U> &s1
//                int *idx
//                const ::coder::array<char, 2U> &s
//                int *k
//                int n
//                boolean_T allowimag
//                boolean_T *isimag
//                boolean_T *b_finite
//                double *nfv
//                boolean_T *foundsign
//                boolean_T *success
// Return Type  : void
//
void readfloat(::coder::array<char, 2U> &s1, int *idx,
               const ::coder::array<char, 2U> &s, int *k, int n,
               boolean_T allowimag, boolean_T *isimag, boolean_T *b_finite,
               double *nfv, boolean_T *foundsign, boolean_T *success)
{
  int b_idx;
  int b_k;
  char c_idx_0;
  boolean_T a__3;
  boolean_T exitg1;
  boolean_T isneg;
  *isimag = false;
  *b_finite = true;
  *nfv = 0.0;
  b_idx = *idx;
  isneg = false;
  *foundsign = false;
  exitg1 = false;
  while ((!exitg1) && (*k <= n)) {
    c_idx_0 = s[*k - 1];
    if (c_idx_0 == '-') {
      isneg = !isneg;
      *foundsign = true;
      (*k)++;
    } else if (c_idx_0 == ',') {
      (*k)++;
    } else if (c_idx_0 == '+') {
      *foundsign = true;
      (*k)++;
    } else {
      if (static_cast<unsigned char>(c_idx_0) > 127) {
        qc_rtErrorWithMessageID(j_emlrtRTEI.fName, j_emlrtRTEI.lineNo);
      }
      if (!bv[static_cast<unsigned char>(s[*k - 1]) & 127]) {
        exitg1 = true;
      } else {
        (*k)++;
      }
    }
  }
  *success = (*k <= n);
  if ((*success) && isneg) {
    if ((*idx >= 2) && (s1[*idx - 2] == '-')) {
      s1[*idx - 2] = ' ';
    } else {
      s1[*idx - 1] = '-';
      b_idx = *idx + 1;
    }
  }
  *idx = b_idx;
  if (*success) {
    char c_idx_1;
    char c_idx_2;
    boolean_T guard1{false};
    boolean_T guard2{false};
    guard1 = false;
    guard2 = false;
    if (*k <= n) {
      c_idx_0 = s[*k - 1];
      if (c_idx_0 == 'j') {
        guard2 = true;
      } else if (c_idx_0 == 'i') {
        if (*k >= n - 1) {
          guard2 = true;
        } else {
          b_k = *k;
          c_idx_0 = '\x00';
          while ((b_k <= n) && (s[b_k - 1] == ',')) {
            b_k++;
          }
          if (b_k <= n) {
            c_idx_0 = s[b_k - 1];
          }
          b_k++;
          c_idx_1 = '\x00';
          while ((b_k <= n) && (s[b_k - 1] == ',')) {
            b_k++;
          }
          if (b_k <= n) {
            c_idx_1 = s[b_k - 1];
          }
          b_k++;
          c_idx_2 = '\x00';
          while ((b_k <= n) && (s[b_k - 1] == ',')) {
            b_k++;
          }
          if (b_k <= n) {
            c_idx_2 = s[b_k - 1];
          }
          if ((((c_idx_0 == 'I') || (c_idx_0 == 'i')) &&
               ((c_idx_1 == 'N') || (c_idx_1 == 'n')) &&
               ((c_idx_2 == 'F') || (c_idx_2 == 'f'))) ||
              (((c_idx_0 == 'N') || (c_idx_0 == 'n')) &&
               ((c_idx_1 == 'A') || (c_idx_1 == 'a')) &&
               ((c_idx_2 == 'N') || (c_idx_2 == 'n')))) {
            guard1 = true;
          } else {
            guard2 = true;
          }
        }
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }
    if (guard2) {
      if (allowimag) {
        *isimag = true;
        (*k)++;
        exitg1 = false;
        while ((!exitg1) && (*k <= n)) {
          c_idx_0 = s[*k - 1];
          if (static_cast<unsigned char>(c_idx_0) > 127) {
            qc_rtErrorWithMessageID(j_emlrtRTEI.fName, j_emlrtRTEI.lineNo);
          }
          if (bv[static_cast<unsigned char>(c_idx_0) & 127] ||
              (c_idx_0 == '\x00') || (c_idx_0 == ',')) {
            (*k)++;
          } else {
            exitg1 = true;
          }
        }
        if ((*k <= n) && (s[*k - 1] == '*')) {
          (*k)++;
          readfloat(s1, idx, s, k, n, false, &isneg, b_finite, nfv, &a__3,
                    success);
        } else {
          s1[b_idx - 1] = '1';
          *idx = b_idx + 1;
        }
      } else {
        *success = false;
      }
    }
    if (guard1) {
      b_k = *k;
      c_idx_0 = '\x00';
      while ((b_k <= n) && (s[b_k - 1] == ',')) {
        b_k++;
      }
      if (b_k <= n) {
        c_idx_0 = s[b_k - 1];
      }
      b_k++;
      c_idx_1 = '\x00';
      while ((b_k <= n) && (s[b_k - 1] == ',')) {
        b_k++;
      }
      if (b_k <= n) {
        c_idx_1 = s[b_k - 1];
      }
      b_k++;
      c_idx_2 = '\x00';
      while ((b_k <= n) && (s[b_k - 1] == ',')) {
        b_k++;
      }
      if (b_k <= n) {
        c_idx_2 = s[b_k - 1];
      }
      b_k++;
      if (((c_idx_0 == 'I') || (c_idx_0 == 'i')) &&
          ((c_idx_1 == 'N') || (c_idx_1 == 'n')) &&
          ((c_idx_2 == 'F') || (c_idx_2 == 'f'))) {
        *b_finite = false;
        *nfv = rtInf;
      } else if (((c_idx_0 == 'N') || (c_idx_0 == 'n')) &&
                 ((c_idx_1 == 'A') || (c_idx_1 == 'a')) &&
                 ((c_idx_2 == 'N') || (c_idx_2 == 'n'))) {
        *b_finite = false;
        *nfv = rtNaN;
      } else {
        *b_finite = true;
        *nfv = 0.0;
        b_k = *k;
      }
      *k = b_k;
      if (*b_finite) {
        *success = copydigits(s1, &b_idx, s, &b_k, n, true);
        *idx = b_idx;
        *k = b_k;
        if (*success) {
          *success = true;
          if (b_k <= n) {
            c_idx_0 = s[b_k - 1];
            if ((c_idx_0 == 'E') || (c_idx_0 == 'e')) {
              s1[b_idx - 1] = 'e';
              *idx = b_idx + 1;
              b_k++;
              while ((b_k <= n) && (s[b_k - 1] == ',')) {
                b_k++;
              }
              if (b_k <= n) {
                c_idx_0 = s[b_k - 1];
                if (c_idx_0 == '-') {
                  s1[b_idx] = '-';
                  *idx = b_idx + 2;
                  b_k++;
                } else if (c_idx_0 == '+') {
                  b_k++;
                }
              }
              *k = b_k;
              isneg = copydigits(s1, idx, s, k, n, false);
              if ((!isneg) || (*k <= b_k)) {
                *success = false;
              }
            }
          }
        }
      } else if ((b_idx >= 2) && (s1[b_idx - 2] == '-')) {
        *idx = b_idx - 1;
        s1[b_idx - 2] = ' ';
        *nfv = -*nfv;
      }
      exitg1 = false;
      while ((!exitg1) && (*k <= n)) {
        if (static_cast<unsigned char>(s[*k - 1]) > 127) {
          qc_rtErrorWithMessageID(j_emlrtRTEI.fName, j_emlrtRTEI.lineNo);
        }
        if (bv[static_cast<unsigned char>(s[*k - 1]) & 127]) {
          (*k)++;
        } else {
          c_idx_0 = s[*k - 1];
          if ((c_idx_0 == '\x00') || (c_idx_0 == ',')) {
            (*k)++;
          } else {
            exitg1 = true;
          }
        }
      }
      if ((*k <= n) && (s[*k - 1] == '*')) {
        (*k)++;
        exitg1 = false;
        while ((!exitg1) && (*k <= n)) {
          if (static_cast<unsigned char>(s[*k - 1]) > 127) {
            qc_rtErrorWithMessageID(j_emlrtRTEI.fName, j_emlrtRTEI.lineNo);
          }
          if (bv[static_cast<unsigned char>(s[*k - 1]) & 127] ||
              (s[*k - 1] == '\x00') || (s[*k - 1] == ',')) {
            (*k)++;
          } else {
            exitg1 = true;
          }
        }
      }
      if (*k <= n) {
        c_idx_0 = s[*k - 1];
        if ((c_idx_0 == 'i') || (c_idx_0 == 'j')) {
          (*k)++;
          *isimag = true;
        }
      }
    }
    int exitg3;
    do {
      exitg3 = 0;
      if (*k <= n) {
        if (static_cast<unsigned char>(s[*k - 1]) > 127) {
          qc_rtErrorWithMessageID(j_emlrtRTEI.fName, j_emlrtRTEI.lineNo);
        }
        if (bv[static_cast<unsigned char>(s[*k - 1]) & 127]) {
          (*k)++;
        } else {
          c_idx_0 = s[*k - 1];
          if ((c_idx_0 == '\x00') || (c_idx_0 == ',')) {
            (*k)++;
          } else {
            exitg3 = 1;
          }
        }
      } else {
        exitg3 = 1;
      }
    } while (exitg3 == 0);
  }
}

} // namespace internal
} // namespace coder

//
// File trailer for str2double1.cpp
//
// [EOF]
//
