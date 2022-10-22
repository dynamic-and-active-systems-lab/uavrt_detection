//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: uavrt_detection_terminate.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Oct-2022 17:38:50
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
