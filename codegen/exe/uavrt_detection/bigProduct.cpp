//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: bigProduct.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "bigProduct.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : int a
//                int b
//                int &highorderbits
// Return Type  : int
//
namespace coder {
namespace internal {
int b_bigProduct(int a, int b, int &highorderbits)
{
  int highOrderA;
  int highOrderB;
  int loworderbits;
  int partialResults_idx_0_tmp;
  int partialResults_idx_1;
  int partialResults_idx_2;
  int tmp;
  loworderbits = 0;
  highOrderA = a >> 16;
  tmp = static_cast<int>(static_cast<unsigned int>(a) & 65535U);
  highOrderB = b >> 16;
  partialResults_idx_2 =
      static_cast<int>(static_cast<unsigned int>(b) & 65535U);
  partialResults_idx_0_tmp = tmp * partialResults_idx_2;
  tmp *= highOrderB;
  partialResults_idx_1 = tmp << 16;
  highorderbits = tmp >> 16;
  if (highorderbits <= 0) {
    tmp = highOrderA * partialResults_idx_2;
    partialResults_idx_2 = tmp << 16;
    highorderbits = tmp >> 16;
    if (highorderbits <= 0) {
      highorderbits = highOrderA * highOrderB;
      if (highorderbits <= 0) {
        if (partialResults_idx_0_tmp > MAX_int32_T - partialResults_idx_1) {
          loworderbits =
              (partialResults_idx_0_tmp + partialResults_idx_1) - MAX_int32_T;
          highorderbits = 1;
        } else {
          loworderbits = partialResults_idx_0_tmp + partialResults_idx_1;
        }
        if (loworderbits > MAX_int32_T - partialResults_idx_2) {
          loworderbits = (loworderbits + partialResults_idx_2) - MAX_int32_T;
          highorderbits++;
        } else {
          loworderbits += partialResults_idx_2;
        }
      }
    }
  }
  return loworderbits;
}

//
// Arguments    : int a
//                int b
//                int &highorderbits
// Return Type  : int
//
int bigProduct(int a, int b, int &highorderbits)
{
  int highOrderB;
  int loworderbits;
  int partialResults_idx_0_tmp;
  int partialResults_idx_1;
  int partialResults_idx_2;
  int tmp;
  loworderbits = a >> 16;
  tmp = static_cast<int>(static_cast<unsigned int>(a) & 65535U);
  highOrderB = b >> 16;
  partialResults_idx_2 =
      static_cast<int>(static_cast<unsigned int>(b) & 65535U);
  partialResults_idx_0_tmp = tmp * partialResults_idx_2;
  tmp *= highOrderB;
  partialResults_idx_1 = tmp << 16;
  highorderbits = tmp >> 16;
  tmp = loworderbits * partialResults_idx_2;
  partialResults_idx_2 = tmp << 16;
  highorderbits += tmp >> 16;
  highorderbits += loworderbits * highOrderB;
  if (partialResults_idx_0_tmp > MAX_int32_T - partialResults_idx_1) {
    loworderbits =
        (partialResults_idx_0_tmp + partialResults_idx_1) - MAX_int32_T;
    highorderbits++;
  } else {
    loworderbits = partialResults_idx_0_tmp + partialResults_idx_1;
  }
  if (loworderbits > MAX_int32_T - partialResults_idx_2) {
    loworderbits = (loworderbits + partialResults_idx_2) - MAX_int32_T;
    highorderbits++;
  } else {
    loworderbits += partialResults_idx_2;
  }
  return loworderbits;
}

} // namespace internal
} // namespace coder

//
// File trailer for bigProduct.cpp
//
// [EOF]
//
