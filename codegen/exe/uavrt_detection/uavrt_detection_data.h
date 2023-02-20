//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: uavrt_detection_data.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 14:31:55
//

#ifndef UAVRT_DETECTION_DATA_H
#define UAVRT_DETECTION_DATA_H

// Include Files
#include "rtwtypes.h"
#include "uavrt_detection_types.h"
#include "omp.h"
#include <cstddef>
#include <cstdlib>

// Variable Declarations
extern unsigned int method;
extern unsigned int b_method;
extern unsigned int state[625];
extern double freq;
extern boolean_T freq_not_empty;
extern omp_nest_lock_t uavrt_detection_nestLockGlobal;
extern rtRunTimeErrorInfo emlrtRTEI;
extern rtRunTimeErrorInfo b_emlrtRTEI;
extern rtRunTimeErrorInfo c_emlrtRTEI;
extern rtRunTimeErrorInfo d_emlrtRTEI;
extern rtRunTimeErrorInfo h_emlrtRTEI;
extern rtRunTimeErrorInfo j_emlrtRTEI;
extern rtRunTimeErrorInfo m_emlrtRTEI;
extern rtRunTimeErrorInfo n_emlrtRTEI;
extern rtRunTimeErrorInfo v_emlrtRTEI;
extern rtRunTimeErrorInfo w_emlrtRTEI;
extern rtRunTimeErrorInfo x_emlrtRTEI;
extern rtEqualityCheckInfo emlrtECI;
extern rtBoundsCheckInfo b_emlrtBCI;
extern rtBoundsCheckInfo c_emlrtBCI;
extern rtDoubleCheckInfo emlrtDCI;
extern rtRunTimeErrorInfo cb_emlrtRTEI;
extern rtRunTimeErrorInfo db_emlrtRTEI;
extern rtRunTimeErrorInfo eb_emlrtRTEI;
extern rtRunTimeErrorInfo fb_emlrtRTEI;
extern rtRunTimeErrorInfo gb_emlrtRTEI;
extern rtRunTimeErrorInfo hb_emlrtRTEI;
extern rtBoundsCheckInfo e_emlrtBCI;
extern const boolean_T bv[128];
extern const char cv[22];
extern const char cv1[30];
extern boolean_T isInitialized_uavrt_detection;

#endif
//
// File trailer for uavrt_detection_data.h
//
// [EOF]
//
