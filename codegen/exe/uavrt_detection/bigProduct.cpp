//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: bigProduct.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 21-Feb-2023 17:49:40
//

// Include Files
#include "bigProduct.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Definitions
//
// Arguments    : int a
//                int b
//                int *loworderbits
//                int *highorderbits
// Return Type  : void
//
namespace coder {
namespace internal {
void b_bigProduct(int a, int b, int *loworderbits, int *highorderbits)
{
  int highOrderA;
  int highOrderB;
  int partialResults_idx_0_tmp;
  int partialResults_idx_1;
  int partialResults_idx_2;
  int tmp;
  *loworderbits = 0;
  highOrderA = a >> 16;
  tmp = a & 65535;
  highOrderB = b >> 16;
  partialResults_idx_2 = b & 65535;
  partialResults_idx_0_tmp = tmp * partialResults_idx_2;
  tmp *= highOrderB;
  partialResults_idx_1 = tmp << 16;
  *highorderbits = tmp >> 16;
  if (*highorderbits <= 0) {
    tmp = highOrderA * partialResults_idx_2;
    partialResults_idx_2 = tmp << 16;
    *highorderbits = tmp >> 16;
    if (*highorderbits <= 0) {
      *highorderbits = highOrderA * highOrderB;
      if (*highorderbits <= 0) {
        if (partialResults_idx_0_tmp > MAX_int32_T - partialResults_idx_1) {
          *loworderbits =
              (partialResults_idx_0_tmp + partialResults_idx_1) - MAX_int32_T;
          *highorderbits = 1;
        } else {
          *loworderbits = partialResults_idx_0_tmp + partialResults_idx_1;
        }
        if (*loworderbits > MAX_int32_T - partialResults_idx_2) {
          *loworderbits = (*loworderbits + partialResults_idx_2) - MAX_int32_T;
          (*highorderbits)++;
        } else {
          *loworderbits += partialResults_idx_2;
        }
      }
    }
  }
}

//
// Arguments    : int a
//                int b
//                int *loworderbits
//                int *highorderbits
// Return Type  : void
//
void bigProduct(int a, int b, int *loworderbits, int *highorderbits)
{
  int highOrderA;
  int highOrderB;
  int partialResults_idx_0_tmp;
  int partialResults_idx_1;
  int partialResults_idx_2;
  int tmp;
  highOrderA = a >> 16;
  tmp = a & 65535;
  highOrderB = b >> 16;
  partialResults_idx_2 = b & 65535;
  partialResults_idx_0_tmp = tmp * partialResults_idx_2;
  tmp *= highOrderB;
  partialResults_idx_1 = tmp << 16;
  *highorderbits = tmp >> 16;
  tmp = highOrderA * partialResults_idx_2;
  partialResults_idx_2 = tmp << 16;
  *highorderbits += tmp >> 16;
  *highorderbits += highOrderA * highOrderB;
  if (partialResults_idx_0_tmp > MAX_int32_T - partialResults_idx_1) {
    *loworderbits =
        (partialResults_idx_0_tmp + partialResults_idx_1) - MAX_int32_T;
    (*highorderbits)++;
  } else {
    *loworderbits = partialResults_idx_0_tmp + partialResults_idx_1;
  }
  if (*loworderbits > MAX_int32_T - partialResults_idx_2) {
    *loworderbits = (*loworderbits + partialResults_idx_2) - MAX_int32_T;
    (*highorderbits)++;
  } else {
    *loworderbits += partialResults_idx_2;
  }
}

} // namespace internal
} // namespace coder

//
// File trailer for bigProduct.cpp
//
// [EOF]
//
