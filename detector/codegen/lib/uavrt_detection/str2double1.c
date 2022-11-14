/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: str2double1.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "str2double1.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"

/* Function Declarations */
static void b_copysign(emxArray_char_T *s1, int *idx, const emxArray_char_T *s,
                       int *k, int n, bool *foundsign, bool *success);

static bool copydigits(emxArray_char_T *s1, int *idx, const emxArray_char_T *s,
                       int *k, int n, bool allowpoint);

static bool copyexponent(emxArray_char_T *s1, int *idx,
                         const emxArray_char_T *s, int *k, int n);

static bool isUnitImag(const emxArray_char_T *s, int k, int n);

static void readNonFinite(const emxArray_char_T *s, int *k, int n,
                          bool *b_finite, double *fv);

/* Function Definitions */
/*
 * Arguments    : emxArray_char_T *s1
 *                int *idx
 *                const emxArray_char_T *s
 *                int *k
 *                int n
 *                bool *foundsign
 *                bool *success
 * Return Type  : void
 */
static void b_copysign(emxArray_char_T *s1, int *idx, const emxArray_char_T *s,
                       int *k, int n, bool *foundsign, bool *success)
{
  const char *s_data;
  char *s1_data;
  bool exitg1;
  bool isneg;
  s_data = s->data;
  s1_data = s1->data;
  isneg = false;
  *foundsign = false;
  exitg1 = false;
  while ((!exitg1) && (*k <= n)) {
    char c;
    c = s_data[*k - 1];
    if (c == '-') {
      isneg = !isneg;
      *foundsign = true;
      (*k)++;
    } else if (c == ',') {
      (*k)++;
    } else if (c == '+') {
      *foundsign = true;
      (*k)++;
    } else if (!bv[(unsigned char)c & 127]) {
      exitg1 = true;
    } else {
      (*k)++;
    }
  }
  *success = (*k <= n);
  if ((*success) && isneg) {
    if ((*idx >= 2) && (s1_data[*idx - 2] == '-')) {
      s1_data[*idx - 2] = ' ';
    } else {
      s1_data[*idx - 1] = '-';
      (*idx)++;
    }
  }
}

/*
 * Arguments    : emxArray_char_T *s1
 *                int *idx
 *                const emxArray_char_T *s
 *                int *k
 *                int n
 *                bool allowpoint
 * Return Type  : bool
 */
static bool copydigits(emxArray_char_T *s1, int *idx, const emxArray_char_T *s,
                       int *k, int n, bool allowpoint)
{
  const char *s_data;
  char *s1_data;
  bool exitg1;
  bool haspoint;
  bool success;
  s_data = s->data;
  s1_data = s1->data;
  success = (*k <= n);
  haspoint = false;
  exitg1 = false;
  while ((!exitg1) && (success && (*k <= n))) {
    char c;
    c = s_data[*k - 1];
    if ((c >= '0') && (c <= '9')) {
      s1_data[*idx - 1] = c;
      (*idx)++;
      (*k)++;
    } else if (c == '.') {
      if (allowpoint && (!haspoint)) {
        success = true;
      } else {
        success = false;
      }
      if (success) {
        s1_data[*idx - 1] = '.';
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

/*
 * Arguments    : emxArray_char_T *s1
 *                int *idx
 *                const emxArray_char_T *s
 *                int *k
 *                int n
 * Return Type  : bool
 */
static bool copyexponent(emxArray_char_T *s1, int *idx,
                         const emxArray_char_T *s, int *k, int n)
{
  const char *s_data;
  char *s1_data;
  bool success;
  s_data = s->data;
  s1_data = s1->data;
  success = true;
  if (*k <= n) {
    char c;
    c = s_data[*k - 1];
    if ((c == 'E') || (c == 'e')) {
      int kexp;
      bool b_success;
      s1_data[*idx - 1] = 'e';
      (*idx)++;
      (*k)++;
      while ((*k <= n) && (s_data[*k - 1] == ',')) {
        (*k)++;
      }
      if (*k <= n) {
        if (s_data[*k - 1] == '-') {
          s1_data[*idx - 1] = '-';
          (*idx)++;
          (*k)++;
        } else if (s_data[*k - 1] == '+') {
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

/*
 * Arguments    : const emxArray_char_T *s
 *                int k
 *                int n
 * Return Type  : bool
 */
static bool isUnitImag(const emxArray_char_T *s, int k, int n)
{
  const char *s_data;
  bool p;
  s_data = s->data;
  p = false;
  if (k <= n) {
    char c_idx_0;
    c_idx_0 = s_data[k - 1];
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
        while ((b_k <= n) && (s_data[b_k - 1] == ',')) {
          b_k++;
        }
        if (b_k <= n) {
          c_idx_0 = s_data[b_k - 1];
        }
        b_k++;
        c_idx_1 = '\x00';
        while ((b_k <= n) && (s_data[b_k - 1] == ',')) {
          b_k++;
        }
        if (b_k <= n) {
          c_idx_1 = s_data[b_k - 1];
        }
        b_k++;
        c_idx_2 = '\x00';
        while ((b_k <= n) && (s_data[b_k - 1] == ',')) {
          b_k++;
        }
        if (b_k <= n) {
          c_idx_2 = s_data[b_k - 1];
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

/*
 * Arguments    : const emxArray_char_T *s
 *                int *k
 *                int n
 *                bool *b_finite
 *                double *fv
 * Return Type  : void
 */
static void readNonFinite(const emxArray_char_T *s, int *k, int n,
                          bool *b_finite, double *fv)
{
  int ksaved;
  const char *s_data;
  char c_idx_0;
  char c_idx_1;
  char c_idx_2;
  s_data = s->data;
  ksaved = *k;
  c_idx_0 = '\x00';
  while ((*k <= n) && (s_data[*k - 1] == ',')) {
    (*k)++;
  }
  if (*k <= n) {
    c_idx_0 = s_data[*k - 1];
  }
  (*k)++;
  c_idx_1 = '\x00';
  while ((*k <= n) && (s_data[*k - 1] == ',')) {
    (*k)++;
  }
  if (*k <= n) {
    c_idx_1 = s_data[*k - 1];
  }
  (*k)++;
  c_idx_2 = '\x00';
  while ((*k <= n) && (s_data[*k - 1] == ',')) {
    (*k)++;
  }
  if (*k <= n) {
    c_idx_2 = s_data[*k - 1];
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

/*
 * Arguments    : emxArray_char_T *s1
 *                int *idx
 *                const emxArray_char_T *s
 *                int *k
 *                int n
 *                bool *isimag
 *                bool *b_finite
 *                double *nfv
 *                bool *foundsign
 *                bool *success
 * Return Type  : void
 */
void readfloat(emxArray_char_T *s1, int *idx, const emxArray_char_T *s, int *k,
               int n, bool *isimag, bool *b_finite, double *nfv,
               bool *foundsign, bool *success)
{
  int b_idx;
  const char *s_data;
  char *s1_data;
  bool b_foundsign;
  s_data = s->data;
  *isimag = false;
  *b_finite = true;
  *nfv = 0.0;
  b_idx = *idx;
  b_copysign(s1, &b_idx, s, k, n, foundsign, success);
  s1_data = s1->data;
  *idx = b_idx;
  if (*success) {
    char c;
    if (isUnitImag(s, *k, n)) {
      bool exitg4;
      *isimag = true;
      (*k)++;
      exitg4 = false;
      while ((!exitg4) && (*k <= n)) {
        c = s_data[*k - 1];
        if (bv[(unsigned char)c & 127] || (c == '\x00') || (c == ',')) {
          (*k)++;
        } else {
          exitg4 = true;
        }
      }
      if ((*k <= n) && (s_data[*k - 1] == '*')) {
        (*k)++;
        b_copysign(s1, &b_idx, s, k, n, &b_foundsign, success);
        s1_data = s1->data;
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
            } else if ((b_idx >= 2) && (s1_data[b_idx - 2] == '-')) {
              *idx = b_idx - 1;
              s1_data[b_idx - 2] = ' ';
              *nfv = -*nfv;
            }
            exitg4 = false;
            while ((!exitg4) && (*k <= n)) {
              c = s_data[*k - 1];
              if (bv[(unsigned char)c & 127] || (c == '\x00') || (c == ',')) {
                (*k)++;
              } else {
                exitg4 = true;
              }
            }
            if ((*k <= n) && (s_data[*k - 1] == '*')) {
              (*k)++;
              exitg4 = false;
              while ((!exitg4) && (*k <= n)) {
                c = s_data[*k - 1];
                if (bv[(unsigned char)c & 127] || (c == '\x00') || (c == ',')) {
                  (*k)++;
                } else {
                  exitg4 = true;
                }
              }
            }
            if (*k <= n) {
              c = s_data[*k - 1];
              if ((c == 'i') || (c == 'j')) {
                (*k)++;
              }
            }
          }
          int exitg3;
          do {
            exitg3 = 0;
            if (*k <= n) {
              c = s_data[*k - 1];
              if (bv[(unsigned char)c & 127] || (c == '\x00') || (c == ',')) {
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
        s1_data[b_idx - 1] = '1';
        *idx = b_idx + 1;
      }
    } else {
      bool exitg4;
      readNonFinite(s, k, n, b_finite, nfv);
      if (*b_finite) {
        *success = copydigits(s1, idx, s, k, n, true);
        if (*success) {
          *success = copyexponent(s1, idx, s, k, n);
        }
      } else if ((b_idx >= 2) && (s1_data[b_idx - 2] == '-')) {
        *idx = b_idx - 1;
        s1_data[b_idx - 2] = ' ';
        *nfv = -*nfv;
      }
      exitg4 = false;
      while ((!exitg4) && (*k <= n)) {
        if (bv[(unsigned char)s_data[*k - 1] & 127]) {
          (*k)++;
        } else {
          c = s_data[*k - 1];
          if ((c == '\x00') || (c == ',')) {
            (*k)++;
          } else {
            exitg4 = true;
          }
        }
      }
      if ((*k <= n) && (s_data[*k - 1] == '*')) {
        (*k)++;
        while ((*k <= n) &&
               (bv[(unsigned char)s_data[*k - 1] & 127] ||
                (s_data[*k - 1] == '\x00') || (s_data[*k - 1] == ','))) {
          (*k)++;
        }
      }
      if (*k <= n) {
        c = s_data[*k - 1];
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
        if (bv[(unsigned char)s_data[*k - 1] & 127]) {
          (*k)++;
        } else {
          c = s_data[*k - 1];
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

/*
 * File trailer for str2double1.c
 *
 * [EOF]
 */
