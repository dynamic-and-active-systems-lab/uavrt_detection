//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: pause.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 04-Feb-2025 09:56:05
//

// Include Files
#include "pause.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
void cpause_init()
{
  static unsigned char pauseState;
  static boolean_T pauseState_not_empty;
  pauseState = 0U;
  pauseState_not_empty = true;
}

//
// File trailer for pause.cpp
//
// [EOF]
//
