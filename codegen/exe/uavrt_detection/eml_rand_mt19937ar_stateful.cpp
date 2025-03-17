//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: eml_rand_mt19937ar_stateful.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "eml_rand_mt19937ar_stateful.h"
#include "eml_rand_mt19937ar.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
void eml_rand_mt19937ar_stateful_init()
{
  static boolean_T state_not_empty;
  coder::internal::randfun::eml_rand_mt19937ar(state);
  state_not_empty = true;
}

//
// File trailer for eml_rand_mt19937ar_stateful.cpp
//
// [EOF]
//
