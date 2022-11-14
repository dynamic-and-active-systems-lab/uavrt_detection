/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: _coder_uavrt_detection_mex.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

#ifndef _CODER_UAVRT_DETECTION_MEX_H
#define _CODER_UAVRT_DETECTION_MEX_H

/* Include Files */
#include "emlrt.h"
#include "mex.h"
#include "tmwtypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
MEXFUNCTION_LINKAGE void mexFunction(int32_T nlhs, mxArray *plhs[],
                                     int32_T nrhs, const mxArray *prhs[]);

emlrtCTX mexFunctionCreateRootTLS(void);

void unsafe_uavrt_detection_mexFunction(int32_T nlhs, int32_T nrhs);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for _coder_uavrt_detection_mex.h
 *
 * [EOF]
 */
