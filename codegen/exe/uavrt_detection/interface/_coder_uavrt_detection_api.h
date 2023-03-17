//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: _coder_uavrt_detection_api.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 16-Mar-2023 19:52:57
//

#ifndef _CODER_UAVRT_DETECTION_API_H
#define _CODER_UAVRT_DETECTION_API_H

// Include Files
#include "coder_array_mex.h"
#include "emlrt.h"
#include "tmwtypes.h"
#include <algorithm>
#include <cstring>

// Variable Declarations
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

// Function Declarations
void uavrt_detection(coder::array<char_T, 2U> *configPath);

void uavrt_detection_api(const mxArray *prhs);

void uavrt_detection_atexit();

void uavrt_detection_initialize();

void uavrt_detection_terminate();

void uavrt_detection_xil_shutdown();

void uavrt_detection_xil_terminate();

#endif
//
// File trailer for _coder_uavrt_detection_api.h
//
// [EOF]
//
