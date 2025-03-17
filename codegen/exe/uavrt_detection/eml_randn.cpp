//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: eml_randn.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 04-Feb-2025 09:56:05
//

// Include Files
#include "eml_randn.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
void eml_randn_init()
{
  static unsigned int b_state[2];
  static unsigned int method;
  static boolean_T method_not_empty;
  static boolean_T state_not_empty;
  method = 0U;
  method_not_empty = true;
  b_state[0] = 362436069U;
  b_state[1] = 521288629U;
  state_not_empty = true;
}

//
// File trailer for eml_randn.cpp
//
// [EOF]
//
