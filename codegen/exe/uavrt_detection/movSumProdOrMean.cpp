//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: movSumProdOrMean.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 17-Dec-2022 12:06:22
//

// Include Files
#include "movSumProdOrMean.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "omp.h"
#include <string.h>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 1U> &x
//                int nx
//                ::coder::array<double, 1U> &y
// Return Type  : void
//
namespace coder {
void vmovfun(const ::coder::array<double, 1U> &x, int nx,
             ::coder::array<double, 1U> &y)
{
  double b_y;
  double bsum;
  int b_k;
  int firstBlockLength;
  int hi;
  int iLeft;
  int ib;
  int lastBlockLength;
  int loop_ub;
  int nblocks;
  int vlen;
  y.set_size(x.size(0));
  loop_ub = x.size(0);
  for (int i{0}; i < loop_ub; i++) {
    y[i] = 0.0;
  }
  if (nx > 2147483646) {
    check_forloop_overflow_error();
  }
  loop_ub = nx - 1;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    iLeft, b_k, vlen, b_y, firstBlockLength, lastBlockLength, nblocks, ib,     \
    bsum, hi)

  for (int k = 0; k <= loop_ub; k++) {
    if (k + 1 <= 1) {
      iLeft = 0;
    } else {
      iLeft = k - 1;
    }
    if (k + 2 > x.size(0)) {
      b_k = x.size(0);
    } else {
      b_k = k + 2;
    }
    vlen = b_k - iLeft;
    if ((x.size(0) == 0) || (vlen == 0)) {
      b_y = 0.0;
    } else {
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
      b_y = x[iLeft];
      for (b_k = 2; b_k <= firstBlockLength; b_k++) {
        b_y += x[(iLeft + b_k) - 1];
      }
      for (ib = 2; ib <= nblocks; ib++) {
        firstBlockLength = iLeft + ((ib - 1) << 10);
        bsum = x[firstBlockLength];
        if (ib == nblocks) {
          hi = lastBlockLength;
        } else {
          hi = 1024;
        }
        for (b_k = 2; b_k <= hi; b_k++) {
          bsum += x[(firstBlockLength + b_k) - 1];
        }
        b_y += bsum;
      }
    }
    y[k] = b_y / static_cast<double>(vlen);
  }
}

} // namespace coder

//
// File trailer for movSumProdOrMean.cpp
//
// [EOF]
//
