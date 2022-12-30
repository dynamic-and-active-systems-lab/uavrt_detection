//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sort.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 30-Dec-2022 12:50:56
//

// Include Files
#include "sort.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "sortIdx.h"
#include "coder_array.h"
#include <cmath>
#include <string.h>

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &x
// Return Type  : void
//
namespace coder {
namespace internal {
void sort(::coder::array<double, 2U> &x)
{
  array<double, 1U> xwork;
  array<int, 2U> idx;
  array<int, 1U> iwork;
  int ib;
  int quartetOffset;
  signed char perm[4];
  idx.set_size(1, x.size(1));
  quartetOffset = x.size(1);
  for (ib = 0; ib < quartetOffset; ib++) {
    idx[ib] = 0;
  }
  if (x.size(1) != 0) {
    double x4[4];
    int idx4[4];
    int bLen;
    int b_n;
    int i2;
    int i3;
    int i4;
    int idx_tmp;
    int n;
    int nNonNaN;
    n = x.size(1);
    b_n = x.size(1);
    x4[0] = 0.0;
    idx4[0] = 0;
    x4[1] = 0.0;
    idx4[1] = 0;
    x4[2] = 0.0;
    idx4[2] = 0;
    x4[3] = 0.0;
    idx4[3] = 0;
    quartetOffset = x.size(1);
    iwork.set_size(quartetOffset);
    for (ib = 0; ib < quartetOffset; ib++) {
      iwork[ib] = 0;
    }
    quartetOffset = x.size(1);
    xwork.set_size(quartetOffset);
    for (ib = 0; ib < quartetOffset; ib++) {
      xwork[ib] = 0.0;
    }
    bLen = 0;
    ib = -1;
    if (x.size(1) > 2147483646) {
      check_forloop_overflow_error();
    }
    for (int k{0}; k < b_n; k++) {
      if (std::isnan(x[k])) {
        idx_tmp = (b_n - bLen) - 1;
        idx[idx_tmp] = k + 1;
        xwork[idx_tmp] = x[k];
        bLen++;
      } else {
        ib++;
        idx4[ib] = k + 1;
        x4[ib] = x[k];
        if (ib + 1 == 4) {
          double d;
          double d1;
          quartetOffset = k - bLen;
          if (x4[0] <= x4[1]) {
            ib = 1;
            i2 = 2;
          } else {
            ib = 2;
            i2 = 1;
          }
          if (x4[2] <= x4[3]) {
            i3 = 3;
            i4 = 4;
          } else {
            i3 = 4;
            i4 = 3;
          }
          d = x4[ib - 1];
          d1 = x4[i3 - 1];
          if (d <= d1) {
            d = x4[i2 - 1];
            if (d <= d1) {
              perm[0] = static_cast<signed char>(ib);
              perm[1] = static_cast<signed char>(i2);
              perm[2] = static_cast<signed char>(i3);
              perm[3] = static_cast<signed char>(i4);
            } else if (d <= x4[i4 - 1]) {
              perm[0] = static_cast<signed char>(ib);
              perm[1] = static_cast<signed char>(i3);
              perm[2] = static_cast<signed char>(i2);
              perm[3] = static_cast<signed char>(i4);
            } else {
              perm[0] = static_cast<signed char>(ib);
              perm[1] = static_cast<signed char>(i3);
              perm[2] = static_cast<signed char>(i4);
              perm[3] = static_cast<signed char>(i2);
            }
          } else {
            d1 = x4[i4 - 1];
            if (d <= d1) {
              if (x4[i2 - 1] <= d1) {
                perm[0] = static_cast<signed char>(i3);
                perm[1] = static_cast<signed char>(ib);
                perm[2] = static_cast<signed char>(i2);
                perm[3] = static_cast<signed char>(i4);
              } else {
                perm[0] = static_cast<signed char>(i3);
                perm[1] = static_cast<signed char>(ib);
                perm[2] = static_cast<signed char>(i4);
                perm[3] = static_cast<signed char>(i2);
              }
            } else {
              perm[0] = static_cast<signed char>(i3);
              perm[1] = static_cast<signed char>(i4);
              perm[2] = static_cast<signed char>(ib);
              perm[3] = static_cast<signed char>(i2);
            }
          }
          idx[quartetOffset - 3] = idx4[perm[0] - 1];
          idx[quartetOffset - 2] = idx4[perm[1] - 1];
          idx[quartetOffset - 1] = idx4[perm[2] - 1];
          idx[quartetOffset] = idx4[perm[3] - 1];
          x[quartetOffset - 3] = x4[perm[0] - 1];
          x[quartetOffset - 2] = x4[perm[1] - 1];
          x[quartetOffset - 1] = x4[perm[2] - 1];
          x[quartetOffset] = x4[perm[3] - 1];
          ib = -1;
        }
      }
    }
    i3 = (b_n - bLen) - 1;
    if (ib + 1 > 0) {
      perm[1] = 0;
      perm[2] = 0;
      perm[3] = 0;
      if (ib + 1 == 1) {
        perm[0] = 1;
      } else if (ib + 1 == 2) {
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
      if (ib + 1 > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int k{0}; k <= ib; k++) {
        idx_tmp = perm[k] - 1;
        quartetOffset = (i3 - ib) + k;
        idx[quartetOffset] = idx4[idx_tmp];
        x[quartetOffset] = x4[idx_tmp];
      }
    }
    ib = (bLen >> 1) + 1;
    for (int k{0}; k <= ib - 2; k++) {
      quartetOffset = (i3 + k) + 1;
      i2 = idx[quartetOffset];
      idx_tmp = (b_n - k) - 1;
      idx[quartetOffset] = idx[idx_tmp];
      idx[idx_tmp] = i2;
      x[quartetOffset] = xwork[idx_tmp];
      x[idx_tmp] = xwork[quartetOffset];
    }
    if ((bLen & 1) != 0) {
      ib += i3;
      x[ib] = xwork[ib];
    }
    nNonNaN = n - bLen;
    quartetOffset = 2;
    if (nNonNaN > 1) {
      if (n >= 256) {
        int nBlocks;
        nBlocks = nNonNaN >> 8;
        if (nBlocks > 0) {
          for (int b{0}; b < nBlocks; b++) {
            double b_xwork[256];
            int b_iwork[256];
            i4 = (b << 8) - 1;
            for (int b_b{0}; b_b < 6; b_b++) {
              bLen = 1 << (b_b + 2);
              b_n = bLen << 1;
              n = 256 >> (b_b + 3);
              for (int k{0}; k < n; k++) {
                i2 = (i4 + k * b_n) + 1;
                for (quartetOffset = 0; quartetOffset < b_n; quartetOffset++) {
                  ib = i2 + quartetOffset;
                  b_iwork[quartetOffset] = idx[ib];
                  b_xwork[quartetOffset] = x[ib];
                }
                i3 = 0;
                quartetOffset = bLen;
                ib = i2 - 1;
                int exitg1;
                do {
                  exitg1 = 0;
                  ib++;
                  if (b_xwork[i3] <= b_xwork[quartetOffset]) {
                    idx[ib] = b_iwork[i3];
                    x[ib] = b_xwork[i3];
                    if (i3 + 1 < bLen) {
                      i3++;
                    } else {
                      exitg1 = 1;
                    }
                  } else {
                    idx[ib] = b_iwork[quartetOffset];
                    x[ib] = b_xwork[quartetOffset];
                    if (quartetOffset + 1 < b_n) {
                      quartetOffset++;
                    } else {
                      ib -= i3;
                      for (quartetOffset = i3 + 1; quartetOffset <= bLen;
                           quartetOffset++) {
                        idx_tmp = ib + quartetOffset;
                        idx[idx_tmp] = b_iwork[quartetOffset - 1];
                        x[idx_tmp] = b_xwork[quartetOffset - 1];
                      }
                      exitg1 = 1;
                    }
                  }
                } while (exitg1 == 0);
              }
            }
          }
          quartetOffset = nBlocks << 8;
          ib = nNonNaN - quartetOffset;
          if (ib > 0) {
            merge_block(idx, x, quartetOffset, ib, 2, iwork, xwork);
          }
          quartetOffset = 8;
        }
      }
      merge_block(idx, x, 0, nNonNaN, quartetOffset, iwork, xwork);
    }
  }
}

//
// Arguments    : ::coder::array<double, 1U> &x
//                ::coder::array<int, 1U> &idx
// Return Type  : void
//
void sort(::coder::array<double, 1U> &x, ::coder::array<int, 1U> &idx)
{
  array<double, 1U> b_vwork;
  array<double, 1U> vwork;
  array<double, 1U> xwork;
  array<int, 1U> b_iwork;
  array<int, 1U> iidx;
  array<int, 1U> iwork;
  int dim;
  int i;
  int vlen;
  int vstride;
  signed char perm[4];
  dim = 0;
  if (x.size(0) != 1) {
    dim = -1;
  }
  if (dim + 2 <= 1) {
    i = x.size(0);
  } else {
    i = 1;
  }
  vlen = i - 1;
  vwork.set_size(i);
  idx.set_size(x.size(0));
  vstride = 1;
  for (int k{0}; k <= dim; k++) {
    vstride *= x.size(0);
  }
  if (vstride > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int j{0}; j < vstride; j++) {
    int bLen2;
    if (i > 2147483646) {
      check_forloop_overflow_error();
    }
    for (int k{0}; k <= vlen; k++) {
      vwork[k] = x[j + k * vstride];
    }
    dim = vwork.size(0);
    b_vwork.set_size(vwork.size(0));
    for (bLen2 = 0; bLen2 < dim; bLen2++) {
      b_vwork[bLen2] = vwork[bLen2];
    }
    iidx.set_size(vwork.size(0));
    dim = vwork.size(0);
    for (bLen2 = 0; bLen2 < dim; bLen2++) {
      iidx[bLen2] = 0;
    }
    bLen2 = vwork.size(0);
    if (vwork.size(0) != 0) {
      double x4[4];
      int idx4[4];
      int bLen;
      int i1;
      int i2;
      int i3;
      int i4;
      int iidx_tmp;
      int nNonNaN;
      x4[0] = 0.0;
      idx4[0] = 0;
      x4[1] = 0.0;
      idx4[1] = 0;
      x4[2] = 0.0;
      idx4[2] = 0;
      x4[3] = 0.0;
      idx4[3] = 0;
      iwork.set_size(vwork.size(0));
      dim = vwork.size(0);
      for (i1 = 0; i1 < dim; i1++) {
        iwork[i1] = 0;
      }
      xwork.set_size(vwork.size(0));
      dim = vwork.size(0);
      for (i1 = 0; i1 < dim; i1++) {
        xwork[i1] = 0.0;
      }
      bLen = 0;
      dim = -1;
      if (vwork.size(0) > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int k{0}; k < bLen2; k++) {
        if (std::isnan(b_vwork[k])) {
          iidx_tmp = (bLen2 - bLen) - 1;
          iidx[iidx_tmp] = k + 1;
          xwork[iidx_tmp] = b_vwork[k];
          bLen++;
        } else {
          dim++;
          idx4[dim] = k + 1;
          x4[dim] = b_vwork[k];
          if (dim + 1 == 4) {
            double d;
            double d1;
            dim = k - bLen;
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
                perm[0] = static_cast<signed char>(i1);
                perm[1] = static_cast<signed char>(i2);
                perm[2] = static_cast<signed char>(i3);
                perm[3] = static_cast<signed char>(i4);
              } else if (d <= x4[i4 - 1]) {
                perm[0] = static_cast<signed char>(i1);
                perm[1] = static_cast<signed char>(i3);
                perm[2] = static_cast<signed char>(i2);
                perm[3] = static_cast<signed char>(i4);
              } else {
                perm[0] = static_cast<signed char>(i1);
                perm[1] = static_cast<signed char>(i3);
                perm[2] = static_cast<signed char>(i4);
                perm[3] = static_cast<signed char>(i2);
              }
            } else {
              d1 = x4[i4 - 1];
              if (d <= d1) {
                if (x4[i2 - 1] <= d1) {
                  perm[0] = static_cast<signed char>(i3);
                  perm[1] = static_cast<signed char>(i1);
                  perm[2] = static_cast<signed char>(i2);
                  perm[3] = static_cast<signed char>(i4);
                } else {
                  perm[0] = static_cast<signed char>(i3);
                  perm[1] = static_cast<signed char>(i1);
                  perm[2] = static_cast<signed char>(i4);
                  perm[3] = static_cast<signed char>(i2);
                }
              } else {
                perm[0] = static_cast<signed char>(i3);
                perm[1] = static_cast<signed char>(i4);
                perm[2] = static_cast<signed char>(i1);
                perm[3] = static_cast<signed char>(i2);
              }
            }
            iidx[dim - 3] = idx4[perm[0] - 1];
            iidx[dim - 2] = idx4[perm[1] - 1];
            iidx[dim - 1] = idx4[perm[2] - 1];
            iidx[dim] = idx4[perm[3] - 1];
            b_vwork[dim - 3] = x4[perm[0] - 1];
            b_vwork[dim - 2] = x4[perm[1] - 1];
            b_vwork[dim - 1] = x4[perm[2] - 1];
            b_vwork[dim] = x4[perm[3] - 1];
            dim = -1;
          }
        }
      }
      i3 = (vwork.size(0) - bLen) - 1;
      if (dim + 1 > 0) {
        perm[1] = 0;
        perm[2] = 0;
        perm[3] = 0;
        if (dim + 1 == 1) {
          perm[0] = 1;
        } else if (dim + 1 == 2) {
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
        if (dim + 1 > 2147483646) {
          check_forloop_overflow_error();
        }
        for (int k{0}; k <= dim; k++) {
          iidx_tmp = perm[k] - 1;
          i1 = (i3 - dim) + k;
          iidx[i1] = idx4[iidx_tmp];
          b_vwork[i1] = x4[iidx_tmp];
        }
      }
      dim = (bLen >> 1) + 1;
      for (int k{0}; k <= dim - 2; k++) {
        i1 = (i3 + k) + 1;
        i2 = iidx[i1];
        iidx_tmp = (bLen2 - k) - 1;
        iidx[i1] = iidx[iidx_tmp];
        iidx[iidx_tmp] = i2;
        b_vwork[i1] = xwork[iidx_tmp];
        b_vwork[iidx_tmp] = xwork[i1];
      }
      if ((bLen & 1) != 0) {
        dim += i3;
        b_vwork[dim] = xwork[dim];
      }
      nNonNaN = vwork.size(0) - bLen;
      i1 = 2;
      if (nNonNaN > 1) {
        if (vwork.size(0) >= 256) {
          int nBlocks;
          nBlocks = nNonNaN >> 8;
          if (nBlocks > 0) {
            for (int b{0}; b < nBlocks; b++) {
              double b_xwork[256];
              int c_iwork[256];
              i4 = (b << 8) - 1;
              for (int b_b{0}; b_b < 6; b_b++) {
                int nPairs;
                bLen = 1 << (b_b + 2);
                bLen2 = bLen << 1;
                nPairs = 256 >> (b_b + 3);
                for (int k{0}; k < nPairs; k++) {
                  i2 = (i4 + k * bLen2) + 1;
                  for (i1 = 0; i1 < bLen2; i1++) {
                    dim = i2 + i1;
                    c_iwork[i1] = iidx[dim];
                    b_xwork[i1] = b_vwork[dim];
                  }
                  i3 = 0;
                  i1 = bLen;
                  dim = i2 - 1;
                  int exitg1;
                  do {
                    exitg1 = 0;
                    dim++;
                    if (b_xwork[i3] <= b_xwork[i1]) {
                      iidx[dim] = c_iwork[i3];
                      b_vwork[dim] = b_xwork[i3];
                      if (i3 + 1 < bLen) {
                        i3++;
                      } else {
                        exitg1 = 1;
                      }
                    } else {
                      iidx[dim] = c_iwork[i1];
                      b_vwork[dim] = b_xwork[i1];
                      if (i1 + 1 < bLen2) {
                        i1++;
                      } else {
                        dim -= i3;
                        for (i1 = i3 + 1; i1 <= bLen; i1++) {
                          iidx_tmp = dim + i1;
                          iidx[iidx_tmp] = c_iwork[i1 - 1];
                          b_vwork[iidx_tmp] = b_xwork[i1 - 1];
                        }
                        exitg1 = 1;
                      }
                    }
                  } while (exitg1 == 0);
                }
              }
            }
            dim = nBlocks << 8;
            i1 = nNonNaN - dim;
            if (i1 > 0) {
              merge_block(iidx, b_vwork, dim, i1, 2, iwork, xwork);
            }
            i1 = 8;
          }
        }
        dim = iwork.size(0);
        b_iwork.set_size(iwork.size(0));
        for (bLen2 = 0; bLen2 < dim; bLen2++) {
          b_iwork[bLen2] = iwork[bLen2];
        }
        vwork.set_size(xwork.size(0));
        dim = xwork.size(0);
        for (bLen2 = 0; bLen2 < dim; bLen2++) {
          vwork[bLen2] = xwork[bLen2];
        }
        merge_block(iidx, b_vwork, 0, nNonNaN, i1, b_iwork, vwork);
      }
    }
    vwork.set_size(b_vwork.size(0));
    dim = b_vwork.size(0);
    for (bLen2 = 0; bLen2 < dim; bLen2++) {
      vwork[bLen2] = b_vwork[bLen2];
    }
    for (int k{0}; k <= vlen; k++) {
      bLen2 = j + k * vstride;
      x[bLen2] = b_vwork[k];
      idx[bLen2] = iidx[k];
    }
  }
}

} // namespace internal
} // namespace coder

//
// File trailer for sort.cpp
//
// [EOF]
//
