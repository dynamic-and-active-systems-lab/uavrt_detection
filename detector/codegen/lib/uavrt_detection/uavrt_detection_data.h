/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: uavrt_detection_data.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

#ifndef UAVRT_DETECTION_DATA_H
#define UAVRT_DETECTION_DATA_H

/* Include Files */
#include "rtwtypes.h"
#include "uavrt_detection_types.h"
#include "omp.h"
#include <stddef.h>
#include <stdlib.h>

/* Variable Declarations */
extern unsigned int state[625];
extern dspcodegen_UDPReceiver udpRx;
extern bool udpRx_not_empty;
extern double freq;
extern bool freq_not_empty;
extern b_dspcodegen_UDPReceiver b_udpRx;
extern bool b_udpRx_not_empty;
extern omp_nest_lock_t uavrt_detection_nestLockGlobal;
extern const char cv[12];
extern const char cv1[18];
extern const bool bv[128];
extern const char cv2[128];
extern const char cv3[18];
extern bool isInitialized_uavrt_detection;

#endif
/*
 * File trailer for uavrt_detection_data.h
 *
 * [EOF]
 */
