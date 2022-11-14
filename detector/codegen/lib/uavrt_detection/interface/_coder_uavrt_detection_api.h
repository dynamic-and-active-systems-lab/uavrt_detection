/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: _coder_uavrt_detection_api.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

#ifndef _CODER_UAVRT_DETECTION_API_H
#define _CODER_UAVRT_DETECTION_API_H

/* Include Files */
#include "emlrt.h"
#include "tmwtypes.h"
#include <string.h>

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void uavrt_detection(void);

void uavrt_detection_api(void);

void uavrt_detection_atexit(void);

void uavrt_detection_initialize(void);

void uavrt_detection_terminate(void);

void uavrt_detection_xil_shutdown(void);

void uavrt_detection_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for _coder_uavrt_detection_api.h
 *
 * [EOF]
 */
