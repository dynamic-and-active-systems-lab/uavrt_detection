//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sortIdx.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "sortIdx.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Declarations
namespace coder {
namespace internal {
static void merge(array<int, 1U> &idx, array<double, 1U> &x, int offset, int np,
                  int nq, array<int, 1U> &iwork, array<double, 1U> &xwork);

static void merge(array<int, 2U> &idx, array<double, 2U> &x, int offset, int np,
                  int nq, array<int, 1U> &iwork, array<double, 1U> &xwork);

static void merge_block(array<int, 2U> &idx, array<double, 2U> &x, int offset,
                        int n, int preSortLevel, array<int, 1U> &iwork,
                        array<double, 1U> &xwork);

} // namespace internal
} // namespace coder

// Function Definitions
//
// Arguments    : array<int, 1U> &idx
//                array<double, 1U> &x
//                int offset
//                int np
//                int nq
//                array<int, 1U> &iwork
//                array<double, 1U> &xwork
// Return Type  : void
//
namespace coder {
namespace internal {
static void merge(array<int, 1U> &idx, array<double, 1U> &x, int offset, int np,
                  int nq, array<int, 1U> &iwork, array<double, 1U> &xwork)
{
  if (nq != 0) {
    int iout;
    int n_tmp;
    int p;
    int q;
    n_tmp = np + nq;
    if (n_tmp > 2147483646) {
      check_forloop_overflow_error();
    }
    for (int j{0}; j < n_tmp; j++) {
      iout = offset + j;
      iwork[j] = idx[iout];
      xwork[j] = x[iout];
    }
    p = 0;
    q = np;
    iout = offset - 1;
    int exitg1;
    do {
      exitg1 = 0;
      iout++;
      if (xwork[p] <= xwork[q]) {
        idx[iout] = iwork[p];
        x[iout] = xwork[p];
        if (p + 1 < np) {
          p++;
        } else {
          exitg1 = 1;
        }
      } else {
        idx[iout] = iwork[q];
        x[iout] = xwork[q];
        if (q + 1 < n_tmp) {
          q++;
        } else {
          q = iout - p;
          if ((p + 1 <= np) && (np > 2147483646)) {
            check_forloop_overflow_error();
          }
          for (int j{p + 1}; j <= np; j++) {
            iout = q + j;
            idx[iout] = iwork[j - 1];
            x[iout] = xwork[j - 1];
          }
          exitg1 = 1;
        }
      }
    } while (exitg1 == 0);
  }
}

//
// Arguments    : array<int, 2U> &idx
//                array<double, 2U> &x
//                int offset
//                int np
//                int nq
//                array<int, 1U> &iwork
//                array<double, 1U> &xwork
// Return Type  : void
//
static void merge(array<int, 2U> &idx, array<double, 2U> &x, int offset, int np,
                  int nq, array<int, 1U> &iwork, array<double, 1U> &xwork)
{
  if (nq != 0) {
    int iout;
    int n_tmp;
    int p;
    int q;
    n_tmp = np + nq;
    if (n_tmp > 2147483646) {
      check_forloop_overflow_error();
    }
    for (int j{0}; j < n_tmp; j++) {
      iout = offset + j;
      iwork[j] = idx[iout];
      xwork[j] = x[iout];
    }
    p = 0;
    q = np;
    iout = offset - 1;
    int exitg1;
    do {
      exitg1 = 0;
      iout++;
      if (xwork[p] <= xwork[q]) {
        idx[iout] = iwork[p];
        x[iout] = xwork[p];
        if (p + 1 < np) {
          p++;
        } else {
          exitg1 = 1;
        }
      } else {
        idx[iout] = iwork[q];
        x[iout] = xwork[q];
        if (q + 1 < n_tmp) {
          q++;
        } else {
          q = iout - p;
          if ((p + 1 <= np) && (np > 2147483646)) {
            check_forloop_overflow_error();
          }
          for (int j{p + 1}; j <= np; j++) {
            iout = q + j;
            idx[iout] = iwork[j - 1];
            x[iout] = xwork[j - 1];
          }
          exitg1 = 1;
        }
      }
    } while (exitg1 == 0);
  }
}

//
// Arguments    : array<int, 2U> &idx
//                array<double, 2U> &x
//                int offset
//                int n
//                int preSortLevel
//                array<int, 1U> &iwork
//                array<double, 1U> &xwork
// Return Type  : void
//
static void merge_block(array<int, 2U> &idx, array<double, 2U> &x, int offset,
                        int n, int preSortLevel, array<int, 1U> &iwork,
                        array<double, 1U> &xwork)
{
  int bLen;
  int nPairs;
  nPairs = n >> preSortLevel;
  bLen = 1 << preSortLevel;
  while (nPairs > 1) {
    int nTail;
    int tailOffset;
    if ((static_cast<unsigned int>(nPairs) & 1U) != 0U) {
      nPairs--;
      tailOffset = bLen * nPairs;
      nTail = n - tailOffset;
      if (nTail > bLen) {
        merge(idx, x, offset + tailOffset, bLen, nTail - bLen, iwork, xwork);
      }
    }
    tailOffset = bLen << 1;
    nPairs >>= 1;
    for (nTail = 0; nTail < nPairs; nTail++) {
      merge(idx, x, offset + nTail * tailOffset, bLen, bLen, iwork, xwork);
    }
    bLen = tailOffset;
  }
  if (n > bLen) {
    merge(idx, x, offset, bLen, n - bLen, iwork, xwork);
  }
}

//
// Arguments    : array<int, 1U> &idx
//                array<double, 1U> &x
//                int offset
//                int n
//                int preSortLevel
//                array<int, 1U> &iwork
//                array<double, 1U> &xwork
// Return Type  : void
//
void merge_block(array<int, 1U> &idx, array<double, 1U> &x, int offset, int n,
                 int preSortLevel, array<int, 1U> &iwork,
                 array<double, 1U> &xwork)
{
  int bLen;
  int nPairs;
  nPairs = n >> preSortLevel;
  bLen = 1 << preSortLevel;
  while (nPairs > 1) {
    int nTail;
    int tailOffset;
    if ((static_cast<unsigned int>(nPairs) & 1U) != 0U) {
      nPairs--;
      tailOffset = bLen * nPairs;
      nTail = n - tailOffset;
      if (nTail > bLen) {
        merge(idx, x, offset + tailOffset, bLen, nTail - bLen, iwork, xwork);
      }
    }
    tailOffset = bLen << 1;
    nPairs >>= 1;
    for (nTail = 0; nTail < nPairs; nTail++) {
      merge(idx, x, offset + nTail * tailOffset, bLen, bLen, iwork, xwork);
    }
    bLen = tailOffset;
  }
  if (n > bLen) {
    merge(idx, x, offset, bLen, n - bLen, iwork, xwork);
  }
}

//
// Arguments    : array<double, 2U> &x
//                array<int, 2U> &idx
// Return Type  : void
//
void sortIdx(array<double, 2U> &x, array<int, 2U> &idx)
{
  array<double, 1U> xwork;
  array<int, 1U> iwork;
  int bLen2;
  int i;
  bLen2 = x.size(1);
  idx.set_size(1, bLen2);
  for (i = 0; i < bLen2; i++) {
    idx[i] = 0;
  }
  if (x.size(1) != 0) {
    double x4[4];
    int idx4[4];
    int bLen;
    int i1;
    int i2;
    int i3;
    int i4;
    int ib;
    int idx_tmp;
    int nBlocks;
    int wOffset_tmp;
    iwork.set_size(bLen2);
    for (i = 0; i < bLen2; i++) {
      iwork[i] = 0;
    }
    xwork.set_size(bLen2);
    x4[0] = 0.0;
    idx4[0] = 0;
    x4[1] = 0.0;
    idx4[1] = 0;
    x4[2] = 0.0;
    idx4[2] = 0;
    x4[3] = 0.0;
    idx4[3] = 0;
    nBlocks = 0;
    ib = 0;
    if (x.size(1) > 2147483646) {
      check_forloop_overflow_error();
    }
    for (int k{0}; k < bLen2; k++) {
      if (std::isnan(x[k])) {
        idx_tmp = (bLen2 - nBlocks) - 1;
        idx[idx_tmp] = k + 1;
        xwork[idx_tmp] = x[k];
        nBlocks++;
      } else {
        ib++;
        idx4[ib - 1] = k + 1;
        x4[ib - 1] = x[k];
        if (ib == 4) {
          double d;
          double d1;
          ib = k - nBlocks;
          if (x4[0] <= x4[1]) {
            i1 = 1;
            i2 = 2;
          } else {
            i1 = 2;
            i2 = 1;
          }
          if (x4[2] <= x4[3]) {
            i3 = 3;
            i4 = 4;
          } else {
            i3 = 4;
            i4 = 3;
          }
          d = x4[i1 - 1];
          d1 = x4[i3 - 1];
          if (d <= d1) {
            d = x4[i2 - 1];
            if (d <= d1) {
              i = i1;
              bLen = i2;
              i1 = i3;
              i2 = i4;
            } else if (d <= x4[i4 - 1]) {
              i = i1;
              bLen = i3;
              i1 = i2;
              i2 = i4;
            } else {
              i = i1;
              bLen = i3;
              i1 = i4;
            }
          } else {
            d1 = x4[i4 - 1];
            if (d <= d1) {
              if (x4[i2 - 1] <= d1) {
                i = i3;
                bLen = i1;
                i1 = i2;
                i2 = i4;
              } else {
                i = i3;
                bLen = i1;
                i1 = i4;
              }
            } else {
              i = i3;
              bLen = i4;
            }
          }
          idx[ib - 3] = idx4[i - 1];
          idx[ib - 2] = idx4[bLen - 1];
          idx[ib - 1] = idx4[i1 - 1];
          idx[ib] = idx4[i2 - 1];
          x[ib - 3] = x4[i - 1];
          x[ib - 2] = x4[bLen - 1];
          x[ib - 1] = x4[i1 - 1];
          x[ib] = x4[i2 - 1];
          ib = 0;
        }
      }
    }
    wOffset_tmp = x.size(1) - nBlocks;
    if (ib > 0) {
      signed char perm[4];
      perm[1] = 0;
      perm[2] = 0;
      perm[3] = 0;
      if (ib == 1) {
        perm[0] = 1;
      } else if (ib == 2) {
        if (x4[0] <= x4[1]) {
          perm[0] = 1;
          perm[1] = 2;
        } else {
          perm[0] = 2;
          perm[1] = 1;
        }
      } else if (x4[0] <= x4[1]) {
        if (x4[1] <= x4[2]) {
          perm[0] = 1;
          perm[1] = 2;
          perm[2] = 3;
        } else if (x4[0] <= x4[2]) {
          perm[0] = 1;
          perm[1] = 3;
          perm[2] = 2;
        } else {
          perm[0] = 3;
          perm[1] = 1;
          perm[2] = 2;
        }
      } else if (x4[0] <= x4[2]) {
        perm[0] = 2;
        perm[1] = 1;
        perm[2] = 3;
      } else if (x4[1] <= x4[2]) {
        perm[0] = 2;
        perm[1] = 3;
        perm[2] = 1;
      } else {
        perm[0] = 3;
        perm[1] = 2;
        perm[2] = 1;
      }
      if (ib > 2147483646) {
        check_forloop_overflow_error();
      }
      i = static_cast<unsigned char>(ib);
      for (int k{0}; k < i; k++) {
        idx_tmp = (wOffset_tmp - ib) + k;
        bLen = perm[k];
        idx[idx_tmp] = idx4[bLen - 1];
        x[idx_tmp] = x4[bLen - 1];
      }
    }
    i1 = nBlocks >> 1;
    for (int k{0}; k < i1; k++) {
      ib = wOffset_tmp + k;
      i2 = idx[ib];
      idx_tmp = (bLen2 - k) - 1;
      idx[ib] = idx[idx_tmp];
      idx[idx_tmp] = i2;
      x[ib] = xwork[idx_tmp];
      x[idx_tmp] = xwork[ib];
    }
    if ((static_cast<unsigned int>(nBlocks) & 1U) != 0U) {
      i = wOffset_tmp + i1;
      x[i] = xwork[i];
    }
    ib = 2;
    if (wOffset_tmp > 1) {
      if (x.size(1) >= 256) {
        nBlocks = wOffset_tmp >> 8;
        if (nBlocks > 0) {
          for (int b{0}; b < nBlocks; b++) {
            double b_xwork[256];
            int b_iwork[256];
            i4 = (b << 8) - 1;
            for (int b_b{0}; b_b < 6; b_b++) {
              bLen = 1 << (b_b + 2);
              bLen2 = bLen << 1;
              i = 256 >> (b_b + 3);
              for (int k{0}; k < i; k++) {
                i2 = (i4 + k * bLen2) + 1;
                for (i1 = 0; i1 < bLen2; i1++) {
                  ib = i2 + i1;
                  b_iwork[i1] = idx[ib];
                  b_xwork[i1] = x[ib];
                }
                i3 = 0;
                i1 = bLen;
                ib = i2 - 1;
                int exitg1;
                do {
                  exitg1 = 0;
                  ib++;
                  if (b_xwork[i3] <= b_xwork[i1]) {
                    idx[ib] = b_iwork[i3];
                    x[ib] = b_xwork[i3];
                    if (i3 + 1 < bLen) {
                      i3++;
                    } else {
                      exitg1 = 1;
                    }
                  } else {
                    idx[ib] = b_iwork[i1];
                    x[ib] = b_xwork[i1];
                    if (i1 + 1 < bLen2) {
                      i1++;
                    } else {
                      ib -= i3;
                      for (i1 = i3 + 1; i1 <= bLen; i1++) {
                        idx_tmp = ib + i1;
                        idx[idx_tmp] = b_iwork[i1 - 1];
                        x[idx_tmp] = b_xwork[i1 - 1];
                      }
                      exitg1 = 1;
                    }
                  }
                } while (exitg1 == 0);
              }
            }
          }
          ib = nBlocks << 8;
          i1 = wOffset_tmp - ib;
          if (i1 > 0) {
            merge_block(idx, x, ib, i1, 2, iwork, xwork);
          }
          ib = 8;
        }
      }
      merge_block(idx, x, 0, wOffset_tmp, ib, iwork, xwork);
    }
  }
}

} // namespace internal
} // namespace coder

//
// File trailer for sortIdx.cpp
//
// [EOF]
//
