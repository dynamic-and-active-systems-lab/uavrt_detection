//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sort.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
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
// Arguments    : array<double, 2U> &x
// Return Type  : void
//
namespace coder {
namespace internal {
void sort(array<double, 2U> &x)
{
  array<int, 2U> b_x;
  sortIdx(x, b_x);
}

//
// Arguments    : array<double, 1U> &x
//                array<int, 1U> &idx
// Return Type  : void
//
void sort(array<double, 1U> &x, array<int, 1U> &idx)
{
  array<double, 1U> vwork;
  array<double, 1U> xwork;
  array<int, 1U> iidx;
  array<int, 1U> iwork;
  int dim;
  int i;
  int i1;
  int vstride;
  boolean_T overflow;
  dim = 2;
  if (x.size(0) != 1) {
    dim = 1;
  }
  if (dim <= 1) {
    i = x.size(0);
  } else {
    i = 1;
  }
  vwork.set_size(i);
  idx.set_size(x.size(0));
  vstride = 1;
  i1 = dim - 2;
  for (int k{0}; k <= i1; k++) {
    vstride *= x.size(0);
  }
  overflow = (vstride > 2147483646);
  for (int b_i{0}; b_i < 1; b_i++) {
    if (overflow) {
      check_forloop_overflow_error();
    }
    for (int j{0}; j < vstride; j++) {
      int bLen2;
      if (i > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int k{0}; k < i; k++) {
        vwork[k] = x[j + k * vstride];
      }
      bLen2 = vwork.size(0);
      iidx.set_size(vwork.size(0));
      for (i1 = 0; i1 < bLen2; i1++) {
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
        int nBlocks;
        int wOffset_tmp;
        iwork.set_size(vwork.size(0));
        for (i1 = 0; i1 < bLen2; i1++) {
          iwork[i1] = 0;
        }
        xwork.set_size(vwork.size(0));
        x4[0] = 0.0;
        idx4[0] = 0;
        x4[1] = 0.0;
        idx4[1] = 0;
        x4[2] = 0.0;
        idx4[2] = 0;
        x4[3] = 0.0;
        idx4[3] = 0;
        nBlocks = 0;
        dim = 0;
        if (vwork.size(0) > 2147483646) {
          check_forloop_overflow_error();
        }
        for (int k{0}; k < bLen2; k++) {
          if (std::isnan(vwork[k])) {
            iidx_tmp = (bLen2 - nBlocks) - 1;
            iidx[iidx_tmp] = k + 1;
            xwork[iidx_tmp] = vwork[k];
            nBlocks++;
          } else {
            dim++;
            idx4[dim - 1] = k + 1;
            x4[dim - 1] = vwork[k];
            if (dim == 4) {
              double d;
              double d1;
              dim = k - nBlocks;
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
              d = x4[b_i1 - 1];
              d1 = x4[i3 - 1];
              if (d <= d1) {
                d = x4[i2 - 1];
                if (d <= d1) {
                  i1 = b_i1;
                  bLen = i2;
                  b_i1 = i3;
                  i2 = i4;
                } else if (d <= x4[i4 - 1]) {
                  i1 = b_i1;
                  bLen = i3;
                  b_i1 = i2;
                  i2 = i4;
                } else {
                  i1 = b_i1;
                  bLen = i3;
                  b_i1 = i4;
                }
              } else {
                d1 = x4[i4 - 1];
                if (d <= d1) {
                  if (x4[i2 - 1] <= d1) {
                    i1 = i3;
                    bLen = b_i1;
                    b_i1 = i2;
                    i2 = i4;
                  } else {
                    i1 = i3;
                    bLen = b_i1;
                    b_i1 = i4;
                  }
                } else {
                  i1 = i3;
                  bLen = i4;
                }
              }
              iidx[dim - 3] = idx4[i1 - 1];
              iidx[dim - 2] = idx4[bLen - 1];
              iidx[dim - 1] = idx4[b_i1 - 1];
              iidx[dim] = idx4[i2 - 1];
              vwork[dim - 3] = x4[i1 - 1];
              vwork[dim - 2] = x4[bLen - 1];
              vwork[dim - 1] = x4[b_i1 - 1];
              vwork[dim] = x4[i2 - 1];
              dim = 0;
            }
          }
        }
        wOffset_tmp = vwork.size(0) - nBlocks;
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
            iidx_tmp = (wOffset_tmp - dim) + k;
            bLen = perm[k];
            iidx[iidx_tmp] = idx4[bLen - 1];
            vwork[iidx_tmp] = x4[bLen - 1];
          }
        }
        dim = nBlocks >> 1;
        for (int k{0}; k < dim; k++) {
          b_i1 = wOffset_tmp + k;
          i2 = iidx[b_i1];
          iidx_tmp = (bLen2 - k) - 1;
          iidx[b_i1] = iidx[iidx_tmp];
          iidx[iidx_tmp] = i2;
          vwork[b_i1] = xwork[iidx_tmp];
          vwork[iidx_tmp] = xwork[b_i1];
        }
        if ((static_cast<unsigned int>(nBlocks) & 1U) != 0U) {
          dim += wOffset_tmp;
          vwork[dim] = xwork[dim];
        }
        dim = 2;
        if (wOffset_tmp > 1) {
          if (vwork.size(0) >= 256) {
            nBlocks = wOffset_tmp >> 8;
            if (nBlocks > 0) {
              for (int b{0}; b < nBlocks; b++) {
                double b_xwork[256];
                int b_iwork[256];
                i4 = (b << 8) - 1;
                for (int b_b{0}; b_b < 6; b_b++) {
                  bLen = 1 << (b_b + 2);
                  bLen2 = bLen << 1;
                  i1 = 256 >> (b_b + 3);
                  for (int k{0}; k < i1; k++) {
                    i2 = (i4 + k * bLen2) + 1;
                    for (b_i1 = 0; b_i1 < bLen2; b_i1++) {
                      dim = i2 + b_i1;
                      b_iwork[b_i1] = iidx[dim];
                      b_xwork[b_i1] = vwork[dim];
                    }
                    i3 = 0;
                    b_i1 = bLen;
                    dim = i2 - 1;
                    int exitg1;
                    do {
                      exitg1 = 0;
                      dim++;
                      if (b_xwork[i3] <= b_xwork[b_i1]) {
                        iidx[dim] = b_iwork[i3];
                        vwork[dim] = b_xwork[i3];
                        if (i3 + 1 < bLen) {
                          i3++;
                        } else {
                          exitg1 = 1;
                        }
                      } else {
                        iidx[dim] = b_iwork[b_i1];
                        vwork[dim] = b_xwork[b_i1];
                        if (b_i1 + 1 < bLen2) {
                          b_i1++;
                        } else {
                          dim -= i3;
                          for (b_i1 = i3 + 1; b_i1 <= bLen; b_i1++) {
                            iidx_tmp = dim + b_i1;
                            iidx[iidx_tmp] = b_iwork[b_i1 - 1];
                            vwork[iidx_tmp] = b_xwork[b_i1 - 1];
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
              dim = 8;
            }
          }
          merge_block(iidx, vwork, 0, wOffset_tmp, dim, iwork, xwork);
        }
      }
      for (int k{0}; k < i; k++) {
        i1 = j + k * vstride;
        x[i1] = vwork[k];
        idx[i1] = iidx[k];
      }
    }
  }
}

//
// Arguments    : array<double, 2U> &x
//                array<int, 2U> &idx
// Return Type  : void
//
void sort(array<double, 2U> &x, array<int, 2U> &idx)
{
  sortIdx(x, idx);
}

} // namespace internal
} // namespace coder

//
// File trailer for sort.cpp
//
// [EOF]
//
