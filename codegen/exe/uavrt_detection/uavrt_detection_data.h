//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: uavrt_detection_data.h
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 11-Nov-2023 11:31:43
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
extern rtRunTimeErrorInfo i_emlrtRTEI;
extern rtRunTimeErrorInfo j_emlrtRTEI;
extern rtRunTimeErrorInfo k_emlrtRTEI;
extern rtRunTimeErrorInfo l_emlrtRTEI;
extern rtRunTimeErrorInfo m_emlrtRTEI;
extern rtRunTimeErrorInfo n_emlrtRTEI;
extern rtBoundsCheckInfo emlrtBCI;
extern rtRunTimeErrorInfo r_emlrtRTEI;
extern rtRunTimeErrorInfo s_emlrtRTEI;
extern rtDoubleCheckInfo b_emlrtDCI;
extern rtRunTimeErrorInfo w_emlrtRTEI;
extern rtRunTimeErrorInfo x_emlrtRTEI;
extern rtRunTimeErrorInfo y_emlrtRTEI;
extern rtRunTimeErrorInfo ab_emlrtRTEI;
extern rtRunTimeErrorInfo db_emlrtRTEI;
extern rtBoundsCheckInfo k_emlrtBCI;
extern rtBoundsCheckInfo l_emlrtBCI;
extern rtEqualityCheckInfo d_emlrtECI;
extern rtRunTimeErrorInfo fb_emlrtRTEI;
extern rtRunTimeErrorInfo gb_emlrtRTEI;
extern rtRunTimeErrorInfo hb_emlrtRTEI;
extern rtRunTimeErrorInfo ib_emlrtRTEI;
extern rtDoubleCheckInfo h_emlrtDCI;
extern rtDoubleCheckInfo i_emlrtDCI;
extern rtDoubleCheckInfo j_emlrtDCI;
extern rtBoundsCheckInfo m_emlrtBCI;
extern rtBoundsCheckInfo n_emlrtBCI;
extern rtBoundsCheckInfo o_emlrtBCI;
extern rtBoundsCheckInfo p_emlrtBCI;
extern rtBoundsCheckInfo q_emlrtBCI;
extern rtBoundsCheckInfo r_emlrtBCI;
extern rtRunTimeErrorInfo jb_emlrtRTEI;
extern rtRunTimeErrorInfo lb_emlrtRTEI;
extern rtRunTimeErrorInfo mb_emlrtRTEI;
extern rtRunTimeErrorInfo nb_emlrtRTEI;
extern rtEqualityCheckInfo e_emlrtECI;
extern rtRunTimeErrorInfo sb_emlrtRTEI;
extern rtRunTimeErrorInfo wb_emlrtRTEI;
extern rtRunTimeErrorInfo xb_emlrtRTEI;
extern rtRunTimeErrorInfo yb_emlrtRTEI;
extern rtRunTimeErrorInfo bc_emlrtRTEI;
extern rtDoubleCheckInfo n_emlrtDCI;
extern rtRunTimeErrorInfo ec_emlrtRTEI;
extern rtRunTimeErrorInfo fc_emlrtRTEI;
extern rtRunTimeErrorInfo hc_emlrtRTEI;
extern rtRunTimeErrorInfo jc_emlrtRTEI;
extern rtRunTimeErrorInfo oc_emlrtRTEI;
extern rtRunTimeErrorInfo pc_emlrtRTEI;
extern const boolean_T bv[128];
extern const char cv1[22];
extern const char cv2[30];
extern boolean_T isInitialized_uavrt_detection;

#endif
//
// File trailer for uavrt_detection_data.h
//
// [EOF]
//
