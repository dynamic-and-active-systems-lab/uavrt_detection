//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: mean.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "mean.h"
#include "blockedSummation.h"
#include "div.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const array<double, 2U> &x
//                array<double, 1U> &y
// Return Type  : void
//
namespace coder {
void mean(const array<double, 2U> &x, array<double, 1U> &y)
{
  array<double, 1U> bsum;
  array<int, 1U> counts;
  int firstBlockLength;
  int xblockoffset;
  if ((x.size(0) == 0) || (x.size(1) == 0)) {
    firstBlockLength = x.size(0);
    y.set_size(x.size(0));
    counts.set_size(x.size(0));
    for (xblockoffset = 0; xblockoffset < firstBlockLength; xblockoffset++) {
      y[xblockoffset] = 0.0;
      counts[xblockoffset] = 0;
    }
  } else {
    int bvstride;
    int ix;
    int lastBlockLength;
    int nblocks;
    int vstride_tmp;
    int xoffset;
    vstride_tmp = x.size(0);
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
    if (x.size(0) > 2147483646) {
      check_forloop_overflow_error();
    }
    for (int xj{0}; xj < vstride_tmp; xj++) {
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
      xoffset = (k - 1) * vstride_tmp;
      if (vstride_tmp > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int xj{0}; xj < vstride_tmp; xj++) {
        ix = xoffset + xj;
        if (!std::isnan(x[ix])) {
          y[xj] = y[xj] + x[ix];
          counts[xj] = counts[xj] + 1;
        }
      }
    }
    for (int ib{2}; ib <= nblocks; ib++) {
      xblockoffset = (ib - 1) * bvstride;
      if (vstride_tmp > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int xj{0}; xj < vstride_tmp; xj++) {
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
        xoffset = xblockoffset + (k - 1) * vstride_tmp;
        for (int xj{0}; xj < vstride_tmp; xj++) {
          ix = xoffset + xj;
          if (!std::isnan(x[ix])) {
            bsum[xj] = bsum[xj] + x[ix];
            counts[xj] = counts[xj] + 1;
          }
        }
      }
      for (int xj{0}; xj < vstride_tmp; xj++) {
        y[xj] = y[xj] + bsum[xj];
      }
    }
  }
  firstBlockLength = counts.size(0);
  bsum.set_size(counts.size(0));
  for (xblockoffset = 0; xblockoffset < firstBlockLength; xblockoffset++) {
    bsum[xblockoffset] = counts[xblockoffset];
  }
  if ((y.size(0) != 1) && (bsum.size(0) != 1) && (y.size(0) != bsum.size(0))) {
    cb_rtErrorWithMessageID(kb_emlrtRTEI.fName, kb_emlrtRTEI.lineNo);
  }
  if (y.size(0) == bsum.size(0)) {
    for (xblockoffset = 0; xblockoffset < firstBlockLength; xblockoffset++) {
      y[xblockoffset] = y[xblockoffset] / bsum[xblockoffset];
    }
  } else {
    rdivide(y, bsum);
  }
}

//
// Arguments    : const array<double, 2U> &x
// Return Type  : double
//
double mean(const array<double, 2U> &x)
{
  array<double, 1U> c_x;
  double y;
  int b_x;
  if (x.size(1) == 0) {
    y = 0.0;
    b_x = 0;
  } else {
    b_x = x.size(1);
    c_x = x.reshape(b_x);
    y = colMajorFlatIter(c_x, x.size(1), b_x);
  }
  y /= static_cast<double>(b_x);
  return y;
}

} // namespace coder

//
// File trailer for mean.cpp
//
// [EOF]
//
