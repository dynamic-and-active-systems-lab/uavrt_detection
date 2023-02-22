//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: strtok.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 21-Feb-2023 18:11:38
//

// Include Files
#include "strtok.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Definitions
//
// Arguments    : const char x[200]
//                char token_data[]
//                int token_size[2]
// Return Type  : void
//
namespace coder {
void b_strtok(const char x[200], char token_data[], int token_size[2])
{
  int i;
  int itoken;
  int k;
  k = 1;
  while ((k <= 200) && (x[k - 1] == '\x00')) {
    k++;
  }
  itoken = k;
  while ((k <= 200) && (x[k - 1] != '\x00')) {
    k++;
  }
  if (itoken > k - 1) {
    i = 0;
    itoken = 0;
  } else {
    i = itoken - 1;
    itoken = k - 1;
  }
  token_size[0] = 1;
  k = itoken - i;
  token_size[1] = k;
  for (itoken = 0; itoken < k; itoken++) {
    token_data[itoken] = x[i + itoken];
  }
}

} // namespace coder

//
// File trailer for strtok.cpp
//
// [EOF]
//
