//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: str2double1.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Oct-2022 17:38:50
//

// Include Files
#include "str2double1.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "coder_array.h"

// Function Declarations
namespace coder {
namespace internal {
static void b_copysign(::coder::array<char, 2U> &s1, int *idx,
                       const ::coder::array<char, 2U> &s, int *k, int n,
                       boolean_T *foundsign, boolean_T *success);

static boolean_T copydigits(::coder::array<char, 2U> &s1, int *idx,
                            const ::coder::array<char, 2U> &s, int *k, int n,
                            boolean_T allowpoint);

static boolean_T copyexponent(::coder::array<char, 2U> &s1, int *idx,
                              const ::coder::array<char, 2U> &s, int *k, int n);

static boolean_T isUnitImag(const ::coder::array<char, 2U> &s, int k, int n);

static void readNonFinite(const ::coder::array<char, 2U> &s, int *k, int n,
                          boolean_T *b_finite, double *fv);

} // namespace internal
} // namespace coder

// Function Definitions
//
// Arguments    : ::coder::array<char, 2U> &s1
//                int *idx
//                const ::coder::array<char, 2U> &s
//                int *k
//                int n
//                boolean_T *foundsign
//                boolean_T *success
// Return Type  : void
//
namespace coder {
namespace internal {
static void b_copysign(::coder::array<char, 2U> &s1, int *idx,
                       const ::coder::array<char, 2U> &s, int *k, int n,
                       boolean_T *foundsign, boolean_T *success)
{
  boolean_T exitg1;
  boolean_T isneg;
  isneg = false;
  *foundsign = false;
  exitg1 = false;
  while ((!exitg1) && (*k <= n)) {
    char c;
    c = s[*k - 1];
    if (c == '-') {
      isneg = !isneg;
      *foundsign = true;
      (*k)++;
    } else if (c == ',') {
      (*k)++;
    } else if (c == '+') {
      *foundsign = true;
      (*k)++;
    } else if (!bv[static_cast<unsigned char>(c) & 127]) {
      exitg1 = true;
    } else {
      (*k)++;
    }
  }
  *success = (*k <= n);
  if ((*success) && isneg) {
    if ((*idx >= 2) && (s1[*idx - 2] == '-')) {
      s1[*idx - 2] = ' ';
    } else {
      s1[*idx - 1] = '-';
      (*idx)++;
    }
  }
}

//
// Arguments    : ::coder::array<char, 2U> &s1
//                int *idx
//                const ::coder::array<char, 2U> &s
//                int *k
//                int n
//                boolean_T allowpoint
// Return Type  : boolean_T
//
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
// Return Type  : boolean_T
//
static boolean_T copyexponent(::coder::array<char, 2U> &s1, int *idx,
                              const ::coder::array<char, 2U> &s, int *k, int n)
{
  boolean_T success;
  success = true;
  if (*k <= n) {
    char c;
    c = s[*k - 1];
    if ((c == 'E') || (c == 'e')) {
      int kexp;
      boolean_T b_success;
      s1[*idx - 1] = 'e';
      (*idx)++;
      (*k)++;
      while ((*k <= n) && (s[*k - 1] == ',')) {
        (*k)++;
      }
      if (*k <= n) {
        if (s[*k - 1] == '-') {
          s1[*idx - 1] = '-';
          (*idx)++;
          (*k)++;
        } else if (s[*k - 1] == '+') {
          (*k)++;
        }
      }
      kexp = *k;
      b_success = copydigits(s1, idx, s, k, n, false);
      if ((!b_success) || (*k <= kexp)) {
        success = false;
      }
    }
  }
  return success;
}

//
// Arguments    : const ::coder::array<char, 2U> &s
//                int k
//                int n
// Return Type  : boolean_T
//
static boolean_T isUnitImag(const ::coder::array<char, 2U> &s, int k, int n)
{
  boolean_T p;
  p = false;
  if (k <= n) {
    char c_idx_0;
    c_idx_0 = s[k - 1];
    if (c_idx_0 == 'j') {
      p = true;
    } else if (c_idx_0 == 'i') {
      if (k >= n - 1) {
        p = true;
      } else {
        int b_k;
        char c_idx_1;
        char c_idx_2;
        b_k = k;
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
        if ((((c_idx_0 != 'I') && (c_idx_0 != 'i')) ||
             ((c_idx_1 != 'N') && (c_idx_1 != 'n')) ||
             ((c_idx_2 != 'F') && (c_idx_2 != 'f'))) &&
            (((c_idx_0 != 'N') && (c_idx_0 != 'n')) ||
             ((c_idx_1 != 'A') && (c_idx_1 != 'a')) ||
             ((c_idx_2 != 'N') && (c_idx_2 != 'n')))) {
          p = true;
        }
      }
    }
  }
  return p;
}

//
// Arguments    : const ::coder::array<char, 2U> &s
//                int *k
//                int n
//                boolean_T *b_finite
//                double *fv
// Return Type  : void
//
static void readNonFinite(const ::coder::array<char, 2U> &s, int *k, int n,
                          boolean_T *b_finite, double *fv)
{
  int ksaved;
  char c_idx_0;
  char c_idx_1;
  char c_idx_2;
  ksaved = *k;
  c_idx_0 = '\x00';
  while ((*k <= n) && (s[*k - 1] == ',')) {
    (*k)++;
  }
  if (*k <= n) {
    c_idx_0 = s[*k - 1];
  }
  (*k)++;
  c_idx_1 = '\x00';
  while ((*k <= n) && (s[*k - 1] == ',')) {
    (*k)++;
  }
  if (*k <= n) {
    c_idx_1 = s[*k - 1];
  }
  (*k)++;
  c_idx_2 = '\x00';
  while ((*k <= n) && (s[*k - 1] == ',')) {
    (*k)++;
  }
  if (*k <= n) {
    c_idx_2 = s[*k - 1];
  }
  (*k)++;
  if (((c_idx_0 == 'I') || (c_idx_0 == 'i')) &&
      ((c_idx_1 == 'N') || (c_idx_1 == 'n')) &&
      ((c_idx_2 == 'F') || (c_idx_2 == 'f'))) {
    *b_finite = false;
    *fv = rtInf;
  } else if (((c_idx_0 == 'N') || (c_idx_0 == 'n')) &&
             ((c_idx_1 == 'A') || (c_idx_1 == 'a')) &&
             ((c_idx_2 == 'N') || (c_idx_2 == 'n'))) {
    *b_finite = false;
    *fv = rtNaN;
  } else {
    *b_finite = true;
    *fv = 0.0;
    *k = ksaved;
  }
}

//
// Arguments    : ::coder::array<char, 2U> &s1
//                int *idx
//                const ::coder::array<char, 2U> &s
//                int *k
//                int n
//                boolean_T *isimag
//                boolean_T *b_finite
//                double *nfv
//                boolean_T *foundsign
//                boolean_T *success
// Return Type  : void
//
void readfloat(::coder::array<char, 2U> &s1, int *idx,
               const ::coder::array<char, 2U> &s, int *k, int n,
               boolean_T *isimag, boolean_T *b_finite, double *nfv,
               boolean_T *foundsign, boolean_T *success)
{
  int b_idx;
  boolean_T b_foundsign;
  *isimag = false;
  *b_finite = true;
  *nfv = 0.0;
  b_idx = *idx;
  b_copysign(s1, &b_idx, s, k, n, foundsign, success);
  *idx = b_idx;
  if (*success) {
    char c;
    if (isUnitImag(s, *k, n)) {
      boolean_T exitg4;
      *isimag = true;
      (*k)++;
      exitg4 = false;
      while ((!exitg4) && (*k <= n)) {
        c = s[*k - 1];
        if (bv[static_cast<unsigned char>(c) & 127] || (c == '\x00') ||
            (c == ',')) {
          (*k)++;
        } else {
          exitg4 = true;
        }
      }
      if ((*k <= n) && (s[*k - 1] == '*')) {
        (*k)++;
        b_copysign(s1, &b_idx, s, k, n, &b_foundsign, success);
        *idx = b_idx;
        if (*success) {
          if (isUnitImag(s, *k, n)) {
            *success = false;
          } else {
            readNonFinite(s, k, n, b_finite, nfv);
            if (*b_finite) {
              *success = copydigits(s1, idx, s, k, n, true);
              if (*success) {
                *success = copyexponent(s1, idx, s, k, n);
              }
            } else if ((b_idx >= 2) && (s1[b_idx - 2] == '-')) {
              *idx = b_idx - 1;
              s1[b_idx - 2] = ' ';
              *nfv = -*nfv;
            }
            exitg4 = false;
            while ((!exitg4) && (*k <= n)) {
              c = s[*k - 1];
              if (bv[static_cast<unsigned char>(c) & 127] || (c == '\x00') ||
                  (c == ',')) {
                (*k)++;
              } else {
                exitg4 = true;
              }
            }
            if ((*k <= n) && (s[*k - 1] == '*')) {
              (*k)++;
              exitg4 = false;
              while ((!exitg4) && (*k <= n)) {
                c = s[*k - 1];
                if (bv[static_cast<unsigned char>(c) & 127] || (c == '\x00') ||
                    (c == ',')) {
                  (*k)++;
                } else {
                  exitg4 = true;
                }
              }
            }
            if (*k <= n) {
              c = s[*k - 1];
              if ((c == 'i') || (c == 'j')) {
                (*k)++;
              }
            }
          }
          int exitg3;
          do {
            exitg3 = 0;
            if (*k <= n) {
              c = s[*k - 1];
              if (bv[static_cast<unsigned char>(c) & 127] || (c == '\x00') ||
                  (c == ',')) {
                (*k)++;
              } else {
                exitg3 = 1;
              }
            } else {
              exitg3 = 2;
            }
          } while (exitg3 == 0);
        }
      } else {
        s1[b_idx - 1] = '1';
        *idx = b_idx + 1;
      }
    } else {
      boolean_T exitg4;
      readNonFinite(s, k, n, b_finite, nfv);
      if (*b_finite) {
        *success = copydigits(s1, idx, s, k, n, true);
        if (*success) {
          *success = copyexponent(s1, idx, s, k, n);
        }
      } else if ((b_idx >= 2) && (s1[b_idx - 2] == '-')) {
        *idx = b_idx - 1;
        s1[b_idx - 2] = ' ';
        *nfv = -*nfv;
      }
      exitg4 = false;
      while ((!exitg4) && (*k <= n)) {
        if (bv[static_cast<unsigned char>(s[*k - 1]) & 127]) {
          (*k)++;
        } else {
          c = s[*k - 1];
          if ((c == '\x00') || (c == ',')) {
            (*k)++;
          } else {
            exitg4 = true;
          }
        }
      }
      if ((*k <= n) && (s[*k - 1] == '*')) {
        (*k)++;
        while ((*k <= n) && (bv[static_cast<unsigned char>(s[*k - 1]) & 127] ||
                             (s[*k - 1] == '\x00') || (s[*k - 1] == ','))) {
          (*k)++;
        }
      }
      if (*k <= n) {
        c = s[*k - 1];
        if ((c == 'i') || (c == 'j')) {
          (*k)++;
          *isimag = true;
        }
      }
    }
    int exitg2;
    do {
      exitg2 = 0;
      if (*k <= n) {
        if (bv[static_cast<unsigned char>(s[*k - 1]) & 127]) {
          (*k)++;
        } else {
          c = s[*k - 1];
          if ((c == '\x00') || (c == ',')) {
            (*k)++;
          } else {
            exitg2 = 1;
          }
        }
      } else {
        exitg2 = 1;
      }
    } while (exitg2 == 0);
  }
}

} // namespace internal
} // namespace coder

//
// File trailer for str2double1.cpp
//
// [EOF]
//
