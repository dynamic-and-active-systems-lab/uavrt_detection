//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: mean.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 22-Oct-2022 12:48:10
//

// Include Files
#include "mean.h"
#include "div.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &x
//                ::coder::array<double, 1U> &y
// Return Type  : void
//
namespace coder {
void mean(const ::coder::array<double, 2U> &x, ::coder::array<double, 1U> &y)
{
  array<double, 1U> bsum;
  array<int, 1U> counts;
  int firstBlockLength;
  int xblockoffset;
  if ((x.size(0) == 0) || (x.size(1) == 0)) {
    y.set_size(x.size(0));
    firstBlockLength = x.size(0);
    for (xblockoffset = 0; xblockoffset < firstBlockLength; xblockoffset++) {
      y[xblockoffset] = 0.0;
    }
    counts.set_size(x.size(0));
    firstBlockLength = x.size(0);
    for (xblockoffset = 0; xblockoffset < firstBlockLength; xblockoffset++) {
      counts[xblockoffset] = 0;
    }
  } else {
    int bvstride;
    int ix;
    int lastBlockLength;
    int nblocks;
    int vstride;
    int xoffset;
    vstride = x.size(0) - 1;
    bvstride = x.size(0) << 10;
    y.set_size(x.size(0));
    counts.set_size(x.size(0));
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
      if (std::isnan(x[xj])) {
        y[xj] = 0.0;
        counts[xj] = 0;
      } else {
        y[xj] = x[xj];
        counts[xj] = 1;
      }
      bsum[xj] = 0.0;
    }
    for (int k{2}; k <= firstBlockLength; k++) {
      xoffset = (k - 1) * (vstride + 1);
      for (int xj{0}; xj <= vstride; xj++) {
        ix = xoffset + xj;
        if (!std::isnan(x[ix])) {
          y[xj] = y[xj] + x[ix];
          counts[xj] = counts[xj] + 1;
        }
      }
    }
    for (int ib{2}; ib <= nblocks; ib++) {
      xblockoffset = (ib - 1) * bvstride;
      for (int xj{0}; xj <= vstride; xj++) {
        ix = xblockoffset + xj;
        if (std::isnan(x[ix])) {
          bsum[xj] = 0.0;
        } else {
          bsum[xj] = x[ix];
          counts[xj] = counts[xj] + 1;
        }
      }
      if (ib == nblocks) {
        firstBlockLength = lastBlockLength;
      } else {
        firstBlockLength = 1024;
      }
      for (int k{2}; k <= firstBlockLength; k++) {
        xoffset = xblockoffset + (k - 1) * (vstride + 1);
        for (int xj{0}; xj <= vstride; xj++) {
          ix = xoffset + xj;
          if (!std::isnan(x[ix])) {
            bsum[xj] = bsum[xj] + x[ix];
            counts[xj] = counts[xj] + 1;
          }
        }
      }
      for (int xj{0}; xj <= vstride; xj++) {
        y[xj] = y[xj] + bsum[xj];
      }
    }
  }
  if (y.size(0) == counts.size(0)) {
    firstBlockLength = y.size(0);
    for (xblockoffset = 0; xblockoffset < firstBlockLength; xblockoffset++) {
      y[xblockoffset] =
          y[xblockoffset] / static_cast<double>(counts[xblockoffset]);
    }
  } else {
    b_binary_expand_op(y, counts);
  }
}

} // namespace coder

//
// File trailer for mean.cpp
//
// [EOF]
//
