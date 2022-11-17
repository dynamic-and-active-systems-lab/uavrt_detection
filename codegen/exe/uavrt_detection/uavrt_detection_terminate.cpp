//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// uavrt_detection_terminate.cpp
//
// Code generation for function 'uavrt_detection_terminate'
//

// Include files
#include "uavrt_detection_terminate.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "omp.h"
#include <string.h>

// Function Definitions
void uavrt_detection_terminate()
{
  omp_destroy_nest_lock(&uavrt_detection_nestLockGlobal);
  isInitialized_uavrt_detection = false;
}

// End of code generation (uavrt_detection_terminate.cpp)
