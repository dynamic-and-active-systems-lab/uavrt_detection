//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// uavrt_detection_initialize.cpp
//
// Code generation for function 'uavrt_detection_initialize'
//

// Include files
#include "uavrt_detection_initialize.h"
#include "CoderTimeAPI.h"
#include "eml_rand_mt19937ar_stateful.h"
#include "fileManager.h"
#include "rt_nonfinite.h"
#include "timeKeeper.h"
#include "uavrt_detection_data.h"
#include "omp.h"
#include <string.h>

// Function Definitions
void uavrt_detection_initialize()
{
  omp_init_nest_lock(&uavrt_detection_nestLockGlobal);
  savedTime_not_empty_init();
  freq_not_empty_init();
  filedata_init();
  eml_rand_mt19937ar_stateful_init();
  isInitialized_uavrt_detection = true;
}

// End of code generation (uavrt_detection_initialize.cpp)
