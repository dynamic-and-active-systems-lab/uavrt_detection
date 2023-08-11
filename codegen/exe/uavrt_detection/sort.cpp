//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sort.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 11-Aug-2023 09:25:46
//

// Include Files
#include "sort.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "sortIdx.h"
#include "coder_array.h"
#include <cmath>

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
  int i;
  int ib;
  idx.set_size(1, x.size(1));
  ib = x.size(1);
  for (i = 0; i < ib; i++) {
    idx[i] = 0;
  }
  if (x.size(1) != 0) {
    double x4[4];
    int idx4[4];
    int bLen;
    int i2;
    int i3;
    int i4;
    int idx_tmp;
    int n;
    int quartetOffset;
    int wOffset_tmp;
    n = x.size(1);
    x4[0] = 0.0;
    idx4[0] = 0;
    x4[1] = 0.0;
    idx4[1] = 0;
    x4[2] = 0.0;
    idx4[2] = 0;
    x4[3] = 0.0;
    idx4[3] = 0;
    ib = x.size(1);
    iwork.set_size(ib);
    xwork.set_size(x.size(1));
    for (i = 0; i < ib; i++) {
      iwork[i] = 0;
      xwork[i] = 0.0;
    }
    bLen = 0;
    ib = 0;
    if (x.size(1) > 2147483646) {
      check_forloop_overflow_error();
    }
    for (int k{0}; k < n; k++) {
      if (std::isnan(x[k])) {
        idx_tmp = (n - bLen) - 1;
        idx[idx_tmp] = k + 1;
        xwork[idx_tmp] = x[k];
        bLen++;
      } else {
        ib++;
        idx4[ib - 1] = k + 1;
        x4[ib - 1] = x[k];
        if (ib == 4) {
          double d;
          double d1;
          signed char b_i2;
          signed char b_i3;
          signed char b_i4;
          signed char i1;
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
          d = x4[i3 - 1];
          d1 = x4[ib - 1];
          if (d1 <= d) {
            d1 = x4[i2 - 1];
            if (d1 <= d) {
              i1 = static_cast<signed char>(ib);
              b_i2 = static_cast<signed char>(i2);
              b_i3 = static_cast<signed char>(i3);
              b_i4 = static_cast<signed char>(i4);
            } else if (d1 <= x4[i4 - 1]) {
              i1 = static_cast<signed char>(ib);
              b_i2 = static_cast<signed char>(i3);
              b_i3 = static_cast<signed char>(i2);
              b_i4 = static_cast<signed char>(i4);
            } else {
              i1 = static_cast<signed char>(ib);
              b_i2 = static_cast<signed char>(i3);
              b_i3 = static_cast<signed char>(i4);
              b_i4 = static_cast<signed char>(i2);
            }
          } else {
            d = x4[i4 - 1];
            if (d1 <= d) {
              if (x4[i2 - 1] <= d) {
                i1 = static_cast<signed char>(i3);
                b_i2 = static_cast<signed char>(ib);
                b_i3 = static_cast<signed char>(i2);
                b_i4 = static_cast<signed char>(i4);
              } else {
                i1 = static_cast<signed char>(i3);
                b_i2 = static_cast<signed char>(ib);
                b_i3 = static_cast<signed char>(i4);
                b_i4 = static_cast<signed char>(i2);
              }
            } else {
              i1 = static_cast<signed char>(i3);
              b_i2 = static_cast<signed char>(i4);
              b_i3 = static_cast<signed char>(ib);
              b_i4 = static_cast<signed char>(i2);
            }
          }
          idx[quartetOffset - 3] = idx4[i1 - 1];
          idx[quartetOffset - 2] = idx4[b_i2 - 1];
          idx[quartetOffset - 1] = idx4[b_i3 - 1];
          idx[quartetOffset] = idx4[b_i4 - 1];
          x[quartetOffset - 3] = x4[i1 - 1];
          x[quartetOffset - 2] = x4[b_i2 - 1];
          x[quartetOffset - 1] = x4[b_i3 - 1];
          x[quartetOffset] = x4[b_i4 - 1];
          ib = 0;
        }
      }
    }
    wOffset_tmp = x.size(1) - bLen;
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
        idx_tmp = perm[k] - 1;
        quartetOffset = (wOffset_tmp - ib) + k;
        idx[quartetOffset] = idx4[idx_tmp];
        x[quartetOffset] = x4[idx_tmp];
      }
    }
    ib = bLen >> 1;
    for (int k{0}; k < ib; k++) {
      quartetOffset = wOffset_tmp + k;
      i2 = idx[quartetOffset];
      idx_tmp = (n - k) - 1;
      idx[quartetOffset] = idx[idx_tmp];
      idx[idx_tmp] = i2;
      x[quartetOffset] = xwork[idx_tmp];
      x[idx_tmp] = xwork[quartetOffset];
    }
    if ((bLen & 1) != 0) {
      i = wOffset_tmp + ib;
      x[i] = xwork[i];
    }
    ib = 2;
    if (wOffset_tmp > 1) {
      if (x.size(1) >= 256) {
        int nBlocks;
        nBlocks = wOffset_tmp >> 8;
        if (nBlocks > 0) {
          for (int b{0}; b < nBlocks; b++) {
            double b_xwork[256];
            int b_iwork[256];
            i4 = (b << 8) - 1;
            for (int b_b{0}; b_b < 6; b_b++) {
              bLen = 1 << (b_b + 2);
              n = bLen << 1;
              i = 256 >> (b_b + 3);
              for (int k{0}; k < i; k++) {
                i2 = (i4 + k * n) + 1;
                for (quartetOffset = 0; quartetOffset < n; quartetOffset++) {
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
                    if (quartetOffset + 1 < n) {
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
          ib = nBlocks << 8;
          quartetOffset = wOffset_tmp - ib;
          if (quartetOffset > 0) {
            merge_block(idx, x, ib, quartetOffset, 2, iwork, xwork);
          }
          ib = 8;
        }
      }
      merge_block(idx, x, 0, wOffset_tmp, ib, iwork, xwork);
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
  array<double, 1U> b_xwork;
  array<double, 1U> vwork;
  array<double, 1U> xwork;
  array<int, 1U> b_iwork;
  array<int, 1U> iidx;
  array<int, 1U> iwork;
  int dim;
  int i;
  int vlen;
  int vstride;
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
    int i1;
    if (i > 2147483646) {
      check_forloop_overflow_error();
    }
    for (int k{0}; k <= vlen; k++) {
      vwork[k] = x[j + k * vstride];
    }
    iidx.set_size(vwork.size(0));
    dim = vwork.size(0);
    for (i1 = 0; i1 < dim; i1++) {
      iidx[i1] = 0;
    }
    if (vwork.size(0) != 0) {
      double x4[4];
      int idx4[4];
      int bLen;
      int b_i1;
      int i2;
      int i3;
      int i4;
      int iidx_tmp;
      int n;
      int wOffset_tmp;
      n = vwork.size(0);
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
      dim = 0;
      if (vwork.size(0) > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int k{0}; k < n; k++) {
        if (std::isnan(vwork[k])) {
          iidx_tmp = (n - bLen) - 1;
          iidx[iidx_tmp] = k + 1;
          xwork[iidx_tmp] = vwork[k];
          bLen++;
        } else {
          dim++;
          idx4[dim - 1] = k + 1;
          x4[dim - 1] = vwork[k];
          if (dim == 4) {
            double d;
            double d1;
            signed char b_i2;
            signed char b_i3;
            signed char b_i4;
            signed char i5;
            dim = k - bLen;
            if (x4[0] <= x4[1]) {
              b_i1 = 1;
              i2 = 2;
            } else {
              b_i1 = 2;
              i2 = 1;
            }
            if (x4[2] <= x4[3]) {
              i3 = 3;
              i4 = 4;
            } else {
              i3 = 4;
              i4 = 3;
            }
            d = x4[i3 - 1];
            d1 = x4[b_i1 - 1];
            if (d1 <= d) {
              d1 = x4[i2 - 1];
              if (d1 <= d) {
                b_i2 = static_cast<signed char>(b_i1);
                b_i3 = static_cast<signed char>(i2);
                b_i4 = static_cast<signed char>(i3);
                i5 = static_cast<signed char>(i4);
              } else if (d1 <= x4[i4 - 1]) {
                b_i2 = static_cast<signed char>(b_i1);
                b_i3 = static_cast<signed char>(i3);
                b_i4 = static_cast<signed char>(i2);
                i5 = static_cast<signed char>(i4);
              } else {
                b_i2 = static_cast<signed char>(b_i1);
                b_i3 = static_cast<signed char>(i3);
                b_i4 = static_cast<signed char>(i4);
                i5 = static_cast<signed char>(i2);
              }
            } else {
              d = x4[i4 - 1];
              if (d1 <= d) {
                if (x4[i2 - 1] <= d) {
                  b_i2 = static_cast<signed char>(i3);
                  b_i3 = static_cast<signed char>(b_i1);
                  b_i4 = static_cast<signed char>(i2);
                  i5 = static_cast<signed char>(i4);
                } else {
                  b_i2 = static_cast<signed char>(i3);
                  b_i3 = static_cast<signed char>(b_i1);
                  b_i4 = static_cast<signed char>(i4);
                  i5 = static_cast<signed char>(i2);
                }
              } else {
                b_i2 = static_cast<signed char>(i3);
                b_i3 = static_cast<signed char>(i4);
                b_i4 = static_cast<signed char>(b_i1);
                i5 = static_cast<signed char>(i2);
              }
            }
            iidx[dim - 3] = idx4[b_i2 - 1];
            iidx[dim - 2] = idx4[b_i3 - 1];
            iidx[dim - 1] = idx4[b_i4 - 1];
            iidx[dim] = idx4[i5 - 1];
            vwork[dim - 3] = x4[b_i2 - 1];
            vwork[dim - 2] = x4[b_i3 - 1];
            vwork[dim - 1] = x4[b_i4 - 1];
            vwork[dim] = x4[i5 - 1];
            dim = 0;
          }
        }
      }
      wOffset_tmp = vwork.size(0) - bLen;
      if (dim > 0) {
        signed char perm[4];
        perm[1] = 0;
        perm[2] = 0;
        perm[3] = 0;
        if (dim == 1) {
          perm[0] = 1;
        } else if (dim == 2) {
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
        if (dim > 2147483646) {
          check_forloop_overflow_error();
        }
        i1 = static_cast<unsigned char>(dim);
        for (int k{0}; k < i1; k++) {
          iidx_tmp = perm[k] - 1;
          b_i1 = (wOffset_tmp - dim) + k;
          iidx[b_i1] = idx4[iidx_tmp];
          vwork[b_i1] = x4[iidx_tmp];
        }
      }
      dim = bLen >> 1;
      for (int k{0}; k < dim; k++) {
        b_i1 = wOffset_tmp + k;
        i2 = iidx[b_i1];
        iidx_tmp = (n - k) - 1;
        iidx[b_i1] = iidx[iidx_tmp];
        iidx[iidx_tmp] = i2;
        vwork[b_i1] = xwork[iidx_tmp];
        vwork[iidx_tmp] = xwork[b_i1];
      }
      if ((bLen & 1) != 0) {
        dim += wOffset_tmp;
        vwork[dim] = xwork[dim];
      }
      b_i1 = 2;
      if (wOffset_tmp > 1) {
        if (vwork.size(0) >= 256) {
          int nBlocks;
          nBlocks = wOffset_tmp >> 8;
          if (nBlocks > 0) {
            for (int b{0}; b < nBlocks; b++) {
              double c_xwork[256];
              int c_iwork[256];
              i4 = (b << 8) - 1;
              for (int b_b{0}; b_b < 6; b_b++) {
                bLen = 1 << (b_b + 2);
                n = bLen << 1;
                i1 = 256 >> (b_b + 3);
                for (int k{0}; k < i1; k++) {
                  i2 = (i4 + k * n) + 1;
                  for (b_i1 = 0; b_i1 < n; b_i1++) {
                    dim = i2 + b_i1;
                    c_iwork[b_i1] = iidx[dim];
                    c_xwork[b_i1] = vwork[dim];
                  }
                  i3 = 0;
                  b_i1 = bLen;
                  dim = i2 - 1;
                  int exitg1;
                  do {
                    exitg1 = 0;
                    dim++;
                    if (c_xwork[i3] <= c_xwork[b_i1]) {
                      iidx[dim] = c_iwork[i3];
                      vwork[dim] = c_xwork[i3];
                      if (i3 + 1 < bLen) {
                        i3++;
                      } else {
                        exitg1 = 1;
                      }
                    } else {
                      iidx[dim] = c_iwork[b_i1];
                      vwork[dim] = c_xwork[b_i1];
                      if (b_i1 + 1 < n) {
                        b_i1++;
                      } else {
                        dim -= i3;
                        for (b_i1 = i3 + 1; b_i1 <= bLen; b_i1++) {
                          iidx_tmp = dim + b_i1;
                          iidx[iidx_tmp] = c_iwork[b_i1 - 1];
                          vwork[iidx_tmp] = c_xwork[b_i1 - 1];
                        }
                        exitg1 = 1;
                      }
                    }
                  } while (exitg1 == 0);
                }
              }
            }
            dim = nBlocks << 8;
            b_i1 = wOffset_tmp - dim;
            if (b_i1 > 0) {
              merge_block(iidx, vwork, dim, b_i1, 2, iwork, xwork);
            }
            b_i1 = 8;
          }
        }
        dim = iwork.size(0);
        b_iwork.set_size(iwork.size(0));
        for (i1 = 0; i1 < dim; i1++) {
          b_iwork[i1] = iwork[i1];
        }
        b_xwork.set_size(xwork.size(0));
        dim = xwork.size(0);
        for (i1 = 0; i1 < dim; i1++) {
          b_xwork[i1] = xwork[i1];
        }
        merge_block(iidx, vwork, 0, wOffset_tmp, b_i1, b_iwork, b_xwork);
      }
    }
    for (int k{0}; k <= vlen; k++) {
      i1 = j + k * vstride;
      x[i1] = vwork[k];
      idx[i1] = iidx[k];
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
