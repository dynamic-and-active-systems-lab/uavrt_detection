//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// blockedSummation.cpp
//
// Code generation for function 'blockedSummation'
//

// Include files
#include "blockedSummation.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>
#include <string.h>

// Function Definitions
namespace coder {
void colMajorFlatIter(const ::coder::array<double, 1U> &x, int vlen, double *y,
                      int *counts)
{
  double bsum;
  int firstBlockLength;
  int lastBlockLength;
  int nblocks;
  if (vlen <= 1024) {
    firstBlockLength = vlen;
    lastBlockLength = 0;
    nblocks = 1;
  } else {
    firstBlockLength = 1024;
    nblocks = vlen / 1024;
    lastBlockLength = vlen - (nblocks << 10);
    if (lastBlockLength > 0) {
      nblocks++;
    } else {
      lastBlockLength = 1024;
    }
  }
  if (std::isnan(x[0])) {
    *y = 0.0;
    *counts = 0;
  } else {
    *y = x[0];
    *counts = 1;
  }
  for (int k{2}; k <= firstBlockLength; k++) {
    bsum = x[k - 1];
    if (!std::isnan(bsum)) {
      *y += bsum;
      (*counts)++;
    }
  }
  for (int ib{2}; ib <= nblocks; ib++) {
    int hi;
    firstBlockLength = (ib - 1) << 10;
    if (std::isnan(x[firstBlockLength])) {
      bsum = 0.0;
    } else {
      bsum = x[firstBlockLength];
      (*counts)++;
    }
    if (ib == nblocks) {
      hi = lastBlockLength;
    } else {
      hi = 1024;
    }
    for (int k{2}; k <= hi; k++) {
      int xoffset;
      xoffset = (firstBlockLength + k) - 1;
      if (!std::isnan(x[xoffset])) {
        bsum += x[xoffset];
        (*counts)++;
      }
    }
    *y += bsum;
  }
}

} // namespace coder

// End of code generation (blockedSummation.cpp)
