//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: unique.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 20-Oct-2022 20:46:49
//

// Include Files
#include "unique.h"
#include "rt_nonfinite.h"
#include "sortLE.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &a
//                ::coder::array<double, 2U> &b
// Return Type  : void
//
namespace coder {
void unique_rows(const ::coder::array<double, 2U> &a,
                 ::coder::array<double, 2U> &b)
{
  array<double, 1U> ycol;
  array<int, 2U> col;
  array<int, 1U> idx;
  array<int, 1U> iwork;
  int qEnd;
  if (a.size(0) == 0) {
    b.set_size(0, a.size(1));
  } else {
    int b_i;
    int i;
    int i1;
    int i2;
    int j;
    int k;
    int n;
    int p;
    int pEnd;
    b.set_size(a.size(0), a.size(1));
    pEnd = a.size(0) * a.size(1);
    for (i = 0; i < pEnd; i++) {
      b[i] = a[i];
    }
    n = a.size(1);
    col.set_size(1, a.size(1));
    for (k = 0; k < n; k++) {
      col[k] = k + 1;
    }
    n = a.size(0) + 1;
    idx.set_size(a.size(0));
    pEnd = a.size(0);
    for (i = 0; i < pEnd; i++) {
      idx[i] = 0;
    }
    if (a.size(1) == 0) {
      for (k = 0; k <= n - 2; k++) {
        idx[k] = k + 1;
      }
    } else {
      iwork.set_size(a.size(0));
      i = a.size(0) - 1;
      for (k = 1; k <= i; k += 2) {
        if (internal::sortLE(a, col, k, k + 1)) {
          idx[k - 1] = k;
          idx[k] = k + 1;
        } else {
          idx[k - 1] = k + 1;
          idx[k] = k;
        }
      }
      if ((a.size(0) & 1) != 0) {
        idx[a.size(0) - 1] = a.size(0);
      }
      b_i = 2;
      while (b_i < n - 1) {
        i2 = b_i << 1;
        j = 1;
        for (pEnd = b_i + 1; pEnd < n; pEnd = qEnd + b_i) {
          int kEnd;
          int q;
          p = j;
          q = pEnd;
          qEnd = j + i2;
          if (qEnd > n) {
            qEnd = n;
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
    i2 = a.size(0) - 1;
    n = a.size(1);
    ycol.set_size(a.size(0));
    for (j = 0; j < n; j++) {
      for (b_i = 0; b_i <= i2; b_i++) {
        ycol[b_i] = b[(idx[b_i] + b.size(0) * j) - 1];
      }
      for (b_i = 0; b_i <= i2; b_i++) {
        b[b_i + b.size(0) * j] = ycol[b_i];
      }
    }
    i2 = -1;
    pEnd = a.size(0);
    k = 0;
    while (k + 1 <= pEnd) {
      p = k;
      int exitg1;
      do {
        exitg1 = 0;
        k++;
        if (k + 1 > pEnd) {
          exitg1 = 1;
        } else {
          boolean_T b_p;
          boolean_T exitg2;
          b_p = false;
          j = 0;
          exitg2 = false;
          while ((!exitg2) && (j <= b.size(1) - 1)) {
            if (b[p + b.size(0) * j] != b[k + b.size(0) * j]) {
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
      i2++;
      i = b.size(1);
      for (j = 0; j < i; j++) {
        b[i2 + b.size(0) * j] = b[p + b.size(0) * j];
      }
    }
    if (i2 + 1 < 1) {
      pEnd = 0;
    } else {
      pEnd = i2 + 1;
    }
    i2 = b.size(1);
    for (i = 0; i < i2; i++) {
      for (i1 = 0; i1 < pEnd; i1++) {
        b[i1 + pEnd * i] = b[i1 + b.size(0) * i];
      }
    }
    b.set_size(pEnd, b.size(1));
  }
}

} // namespace coder

//
// File trailer for unique.cpp
//
// [EOF]
//
