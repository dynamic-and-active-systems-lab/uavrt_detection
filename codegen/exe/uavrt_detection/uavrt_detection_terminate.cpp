//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: uavrt_detection_terminate.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "uavrt_detection_terminate.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "omp.h"

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
void uavrt_detection_terminate()
{
  omp_destroy_nest_lock(&uavrt_detection_nestLockGlobal);
  isInitialized_uavrt_detection = false;
}

//
// File trailer for uavrt_detection_terminate.cpp
//
// [EOF]
//
