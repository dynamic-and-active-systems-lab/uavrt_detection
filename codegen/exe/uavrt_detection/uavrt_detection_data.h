//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: uavrt_detection_data.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 15-Aug-2023 14:57:30
//

#ifndef UAVRT_DETECTION_DATA_H
#define UAVRT_DETECTION_DATA_H

// Include Files
#include "rtwtypes.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include "omp.h"
#include <cstddef>
#include <cstdio>
#include <cstdlib>

// Variable Declarations
extern coder::array<char, 2U> globalThresholdCachePath;
extern unsigned int state[625];
extern double freq;
extern boolean_T freq_not_empty;
extern omp_nest_lock_t uavrt_detection_nestLockGlobal;
extern rtRunTimeErrorInfo emlrtRTEI;
extern rtRunTimeErrorInfo b_emlrtRTEI;
extern rtRunTimeErrorInfo c_emlrtRTEI;
extern rtRunTimeErrorInfo d_emlrtRTEI;
extern rtRunTimeErrorInfo j_emlrtRTEI;
extern rtRunTimeErrorInfo k_emlrtRTEI;
extern rtRunTimeErrorInfo l_emlrtRTEI;
extern rtRunTimeErrorInfo m_emlrtRTEI;
extern rtBoundsCheckInfo emlrtBCI;
extern rtRunTimeErrorInfo q_emlrtRTEI;
extern rtRunTimeErrorInfo r_emlrtRTEI;
extern rtRunTimeErrorInfo v_emlrtRTEI;
extern rtRunTimeErrorInfo w_emlrtRTEI;
extern rtRunTimeErrorInfo x_emlrtRTEI;
extern rtRunTimeErrorInfo y_emlrtRTEI;
extern rtRunTimeErrorInfo cb_emlrtRTEI;
extern rtBoundsCheckInfo k_emlrtBCI;
extern rtBoundsCheckInfo l_emlrtBCI;
extern rtBoundsCheckInfo m_emlrtBCI;
extern rtBoundsCheckInfo n_emlrtBCI;
extern rtBoundsCheckInfo o_emlrtBCI;
extern rtDoubleCheckInfo g_emlrtDCI;
extern rtDoubleCheckInfo h_emlrtDCI;
extern rtDoubleCheckInfo i_emlrtDCI;
extern rtRunTimeErrorInfo eb_emlrtRTEI;
extern rtRunTimeErrorInfo fb_emlrtRTEI;
extern rtEqualityCheckInfo d_emlrtECI;
extern rtBoundsCheckInfo p_emlrtBCI;
extern rtBoundsCheckInfo q_emlrtBCI;
extern rtRunTimeErrorInfo gb_emlrtRTEI;
extern rtRunTimeErrorInfo ib_emlrtRTEI;
extern rtRunTimeErrorInfo jb_emlrtRTEI;
extern rtRunTimeErrorInfo kb_emlrtRTEI;
extern rtEqualityCheckInfo e_emlrtECI;
extern rtRunTimeErrorInfo ob_emlrtRTEI;
extern rtRunTimeErrorInfo sb_emlrtRTEI;
extern rtRunTimeErrorInfo tb_emlrtRTEI;
extern rtRunTimeErrorInfo ub_emlrtRTEI;
extern rtRunTimeErrorInfo wb_emlrtRTEI;
extern rtRunTimeErrorInfo ac_emlrtRTEI;
extern rtRunTimeErrorInfo bc_emlrtRTEI;
extern rtDoubleCheckInfo m_emlrtDCI;
extern rtRunTimeErrorInfo dc_emlrtRTEI;
extern rtRunTimeErrorInfo gc_emlrtRTEI;
extern const boolean_T bv[128];
extern const char cv1[22];
extern const char cv2[30];
extern const char cv4[18];
extern boolean_T isInitialized_uavrt_detection;

#endif
//
// File trailer for uavrt_detection_data.h
//
// [EOF]
//
