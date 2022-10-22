//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: sum.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Oct-2022 17:38:50
//

// Include Files
#include "sum.h"
#include "rt_nonfinite.h"
#include "sparse1.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<double, 1U> &x
// Return Type  : double
//
namespace coder {
double sum(const ::coder::array<double, 1U> &x)
{
  double y;
  if (x.size(0) == 0) {
    y = 0.0;
  } else {
    int firstBlockLength;
    int lastBlockLength;
    int nblocks;
    if (x.size(0) <= 1024) {
      firstBlockLength = x.size(0);
      lastBlockLength = 0;
      nblocks = 1;
    } else {
      firstBlockLength = 1024;
      nblocks = static_cast<int>(static_cast<unsigned int>(x.size(0)) >> 10);
      lastBlockLength = x.size(0) - (nblocks << 10);
      if (lastBlockLength > 0) {
        nblocks++;
      } else {
        lastBlockLength = 1024;
      }
    }
    y = x[0];
    for (int k{2}; k <= firstBlockLength; k++) {
      y += x[k - 1];
    }
    for (int ib{2}; ib <= nblocks; ib++) {
      double bsum;
      int hi;
      firstBlockLength = (ib - 1) << 10;
      bsum = x[firstBlockLength];
      if (ib == nblocks) {
        hi = lastBlockLength;
      } else {
        hi = 1024;
      }
      for (int k{2}; k <= hi; k++) {
        bsum += x[(firstBlockLength + k) - 1];
      }
      y += bsum;
    }
  }
  return y;
}

//
// Arguments    : const sparse *x
//                b_sparse *y
// Return Type  : void
//
void sum(const sparse *x, b_sparse *y)
{
  if ((x->m == 0) || (x->n == 0) || (x->m == 0)) {
    int outidx;
    y->n = x->n;
    y->colidx.set_size(x->n + 1);
    outidx = x->n;
    for (int i{0}; i <= outidx; i++) {
      y->colidx[i] = 1;
    }
    y->d.set_size(1);
    y->d[0] = 0.0;
    y->rowidx.set_size(1);
    y->rowidx[0] = 1;
  } else {
    int i;
    int outidx;
    int xstart;
    outidx = x->n;
    xstart = x->colidx[x->colidx.size(0) - 1] - 1;
    if (outidx <= xstart) {
      xstart = outidx;
    }
    y->n = x->n;
    if (xstart < 1) {
      xstart = 1;
    }
    y->d.set_size(xstart);
    y->rowidx.set_size(xstart);
    y->colidx.set_size(x->n + 1);
    y->colidx[0] = 1;
    outidx = 1;
    i = x->n;
    for (int col{0}; col < i; col++) {
      double r;
      int xend;
      xstart = x->colidx[col];
      xend = x->colidx[col + 1] - 1;
      r = 0.0;
      for (int xp{xstart}; xp <= xend; xp++) {
        r += x->d[xp - 1];
      }
      if (r != 0.0) {
        y->d[outidx - 1] = r;
        outidx++;
      }
      y->colidx[col + 1] = outidx;
    }
    i = y->colidx[y->colidx.size(0) - 1];
    for (outidx = 0; outidx <= i - 2; outidx++) {
      y->rowidx[outidx] = 1;
    }
  }
}

//
// Arguments    : const g_sparse *x
//                e_sparse *y
// Return Type  : void
//
void sum(const g_sparse *x, e_sparse *y)
{
  if (x->m == 0) {
    y->colidx.set_size(2);
    y->colidx[0] = 1;
    y->colidx[1] = 1;
    y->d.set_size(1);
    y->d[0] = 0.0;
    y->rowidx.set_size(1);
    y->rowidx[0] = 1;
  } else {
    double r;
    int xend;
    int xstart;
    y->d.set_size(1);
    y->rowidx.set_size(1);
    y->colidx.set_size(2);
    y->colidx[0] = 1;
    y->colidx[1] = 1;
    xstart = x->colidx[0];
    xend = x->colidx[1] - 1;
    r = 0.0;
    for (int xp{xstart}; xp <= xend; xp++) {
      r += x->d[xp - 1];
    }
    if (r != 0.0) {
      y->d[0] = r;
      y->colidx[1] = 2;
    }
    if (y->colidx[1] - 2 >= 0) {
      y->rowidx[0] = 1;
    }
  }
}

//
// Arguments    : const ::coder::array<double, 2U> &x
//                ::coder::array<double, 1U> &y
// Return Type  : void
//
void sum(const ::coder::array<double, 2U> &x, ::coder::array<double, 1U> &y)
{
  array<double, 1U> bsum;
  if ((x.size(0) == 0) || (x.size(1) == 0)) {
    int firstBlockLength;
    y.set_size(x.size(0));
    firstBlockLength = x.size(0);
    for (int xblockoffset{0}; xblockoffset < firstBlockLength; xblockoffset++) {
      y[xblockoffset] = 0.0;
    }
  } else {
    int bvstride;
    int firstBlockLength;
    int lastBlockLength;
    int nblocks;
    int vstride;
    int xoffset;
    vstride = x.size(0) - 1;
    bvstride = x.size(0) << 10;
    y.set_size(x.size(0));
    bsum.set_size(x.size(0));
    if (x.size(1) <= 1024) {
      firstBlockLength = x.size(1);
      lastBlockLength = 0;
      nblocks = 1;
    } else {
      firstBlockLength = 1024;
      nblocks = static_cast<int>(static_cast<unsigned int>(x.size(1)) >> 10);
      lastBlockLength = x.size(1) - (nblocks << 10);
      if (lastBlockLength > 0) {
        nblocks++;
      } else {
        lastBlockLength = 1024;
      }
    }
    for (int xj{0}; xj <= vstride; xj++) {
      y[xj] = x[xj];
      bsum[xj] = 0.0;
    }
    for (int k{2}; k <= firstBlockLength; k++) {
      xoffset = (k - 1) * (vstride + 1);
      for (int xj{0}; xj <= vstride; xj++) {
        y[xj] = y[xj] + x[xoffset + xj];
      }
    }
    for (int ib{2}; ib <= nblocks; ib++) {
      int xblockoffset;
      xblockoffset = (ib - 1) * bvstride;
      for (int xj{0}; xj <= vstride; xj++) {
        bsum[xj] = x[xblockoffset + xj];
      }
      if (ib == nblocks) {
        firstBlockLength = lastBlockLength;
      } else {
        firstBlockLength = 1024;
      }
      for (int k{2}; k <= firstBlockLength; k++) {
        xoffset = xblockoffset + (k - 1) * (vstride + 1);
        for (int xj{0}; xj <= vstride; xj++) {
          bsum[xj] = bsum[xj] + x[xoffset + xj];
        }
      }
      for (int xj{0}; xj <= vstride; xj++) {
        y[xj] = y[xj] + bsum[xj];
      }
    }
  }
}

} // namespace coder

//
// File trailer for sum.cpp
//
// [EOF]
//
