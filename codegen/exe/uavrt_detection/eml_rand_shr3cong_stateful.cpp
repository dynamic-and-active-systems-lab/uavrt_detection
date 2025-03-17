//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: eml_rand_shr3cong_stateful.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "eml_rand_shr3cong_stateful.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
void eml_rand_shr3cong_stateful_init()
{
  static unsigned int b_state[2];
  static boolean_T state_not_empty;
  b_state[0] = 362436069U;
  b_state[1] = 521288629U;
  state_not_empty = true;
}

//
// File trailer for eml_rand_shr3cong_stateful.cpp
//
// [EOF]
//
