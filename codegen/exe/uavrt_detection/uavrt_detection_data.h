//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// uavrt_detection_data.h
//
// Code generation for function 'uavrt_detection_data'
//

#ifndef UAVRT_DETECTION_DATA_H
#define UAVRT_DETECTION_DATA_H

// Include files
#include "rtwtypes.h"
#include "omp.h"
#include <cstddef>
#include <cstdlib>

// Variable Declarations
extern unsigned int state[625];
extern double freq;
extern boolean_T freq_not_empty;
extern omp_nest_lock_t uavrt_detection_nestLockGlobal;
extern const char cv[128];
extern const boolean_T bv[128];
extern const char cv2[18];
extern boolean_T isInitialized_uavrt_detection;

#endif
// End of code generation (uavrt_detection_data.h)
