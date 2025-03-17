//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: unique.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "unique.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "sortLE.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const array<double, 2U> &a
//                array<double, 2U> &b
// Return Type  : void
//
namespace coder {
void unique_rows(const array<double, 2U> &a, array<double, 2U> &b)
{
  static rtRunTimeErrorInfo rc_emlrtRTEI{
      331,          // lineNo
      "unique_rows" // fName
  };
  array<double, 1U> ycol;
  array<int, 2U> col;
  array<int, 1U> idx;
  array<int, 1U> iwork;
  int qEnd;
  if (a.size(0) == 0) {
    b.set_size(0, a.size(1));
  } else {
    int b_i;
    int b_n;
    int i;
    int i1;
    int i2;
    int j;
    int k;
    int loop_ub;
    int n;
    int pEnd;
    loop_ub = a.size(0);
    n = a.size(1);
    b.set_size(a.size(0), a.size(1));
    i2 = a.size(0) * a.size(1);
    for (i = 0; i < i2; i++) {
      b[i] = a[i];
    }
    col.set_size(1, a.size(1));
    if (a.size(1) > 2147483646) {
      check_forloop_overflow_error();
    }
    for (k = 0; k < n; k++) {
      col[k] = k + 1;
    }
    b_n = a.size(0) + 1;
    idx.set_size(a.size(0));
    for (i = 0; i < loop_ub; i++) {
      idx[i] = 0;
    }
    if (a.size(1) == 0) {
      if (a.size(0) > 2147483646) {
        check_forloop_overflow_error();
      }
      for (k = 0; k <= b_n - 2; k++) {
        idx[k] = k + 1;
      }
    } else {
      iwork.set_size(a.size(0));
      i2 = a.size(0) - 1;
      if (a.size(0) - 1 > 2147483645) {
        check_forloop_overflow_error();
      }
      for (k = 1; k <= i2; k += 2) {
        if (internal::sortLE(a, col, k, k + 1)) {
          idx[k - 1] = k;
          idx[k] = k + 1;
        } else {
          idx[k - 1] = k + 1;
          idx[k] = k;
        }
      }
      if ((static_cast<unsigned int>(a.size(0)) & 1U) != 0U) {
        idx[a.size(0) - 1] = a.size(0);
      }
      b_i = 2;
      while (b_i < b_n - 1) {
        i2 = b_i << 1;
        j = 1;
        for (pEnd = b_i + 1; pEnd < b_n; pEnd = qEnd + b_i) {
          int kEnd;
          int p;
          int q;
          p = j;
          q = pEnd;
          qEnd = j + i2;
          if (qEnd > b_n) {
            qEnd = b_n;
          }
          k = 0;
          kEnd = qEnd - j;
          while (k + 1 <= kEnd) {
            i = idx[q - 1];
            i1 = idx[p - 1];
            if (internal::sortLE(a, col, i1, i)) {
              iwork[k] = i1;
              p++;
              if (p == pEnd) {
                while (q < qEnd) {
                  k++;
                  iwork[k] = idx[q - 1];
                  q++;
                }
              }
            } else {
              iwork[k] = i;
              q++;
              if (q == qEnd) {
                while (p < pEnd) {
                  k++;
                  iwork[k] = idx[p - 1];
                  p++;
                }
              }
            }
            k++;
          }
          for (k = 0; k < kEnd; k++) {
            idx[(j + k) - 1] = iwork[k];
          }
          j = qEnd;
        }
        b_i = i2;
      }
    }
    ycol.set_size(a.size(0));
    for (j = 0; j < n; j++) {
      if (loop_ub > 2147483646) {
        check_forloop_overflow_error();
      }
      for (b_i = 0; b_i < loop_ub; b_i++) {
        ycol[b_i] = b[(idx[b_i] + b.size(0) * j) - 1];
      }
      for (b_i = 0; b_i < loop_ub; b_i++) {
        b[b_i + b.size(0) * j] = ycol[b_i];
      }
    }
    pEnd = 0;
    k = 0;
    while (k + 1 <= loop_ub) {
      i2 = k;
      int exitg1;
      do {
        exitg1 = 0;
        k++;
        if (k + 1 > loop_ub) {
          exitg1 = 1;
        } else {
          boolean_T b_p;
          boolean_T exitg2;
          b_p = false;
          j = 0;
          exitg2 = false;
          while ((!exitg2) && (j <= b.size(1) - 1)) {
            if (b[i2 + b.size(0) * j] != b[k + b.size(0) * j]) {
              b_p = true;
              exitg2 = true;
            } else {
              j++;
            }
          }
          if (b_p) {
            exitg1 = 1;
          }
        }
      } while (exitg1 == 0);
      pEnd++;
      if (b.size(1) > 2147483646) {
        check_forloop_overflow_error();
      }
      for (j = 0; j < n; j++) {
        b[(pEnd + b.size(0) * j) - 1] = b[i2 + b.size(0) * j];
      }
      if ((i2 + 1 <= k) && (k > 2147483646)) {
        check_forloop_overflow_error();
      }
    }
    if (pEnd > a.size(0)) {
      g_rtErrorWithMessageID(rc_emlrtRTEI.fName, rc_emlrtRTEI.lineNo);
    }
    if (pEnd < 1) {
      loop_ub = 0;
    } else {
      loop_ub = pEnd;
    }
    for (i = 0; i < n; i++) {
      for (i1 = 0; i1 < loop_ub; i1++) {
        b[i1 + loop_ub * i] = b[i1 + b.size(0) * i];
      }
    }
    b.set_size(loop_ub, b.size(1));
    if (pEnd > 2147483646) {
      check_forloop_overflow_error();
    }
  }
}

} // namespace coder

//
// File trailer for unique.cpp
//
// [EOF]
//
