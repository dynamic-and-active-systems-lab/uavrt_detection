//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: uavrt_detection_initialize.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 20-Oct-2022 20:46:49
//

// Include Files
#include "uavrt_detection_initialize.h"
#include "CoderTimeAPI.h"
#include "eml_rand_mt19937ar_stateful.h"
#include "fileManager.h"
#include "rt_nonfinite.h"
#include "timeKeeper.h"
#include "uavrt_detection_data.h"
#include "omp.h"

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
void uavrt_detection_initialize()
{
  omp_init_nest_lock(&uavrt_detection_nestLockGlobal);
  savedTime_not_empty_init();
  freq_not_empty_init();
  filedata_init();
  eml_rand_mt19937ar_stateful_init();
  isInitialized_uavrt_detection = true;
}

//
// File trailer for uavrt_detection_initialize.cpp
//
// [EOF]
//
