//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: uavrt_detection_data.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 17-Dec-2022 13:40:17
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
extern unsigned int state[625];
extern double freq;
extern boolean_T freq_not_empty;
extern omp_nest_lock_t uavrt_detection_nestLockGlobal;
extern rtRunTimeErrorInfo emlrtRTEI;
extern rtRunTimeErrorInfo c_emlrtRTEI;
extern rtRunTimeErrorInfo d_emlrtRTEI;
extern rtRunTimeErrorInfo i_emlrtRTEI;
extern rtRunTimeErrorInfo l_emlrtRTEI;
extern rtRunTimeErrorInfo m_emlrtRTEI;
extern rtRunTimeErrorInfo n_emlrtRTEI;
extern rtRunTimeErrorInfo v_emlrtRTEI;
extern rtRunTimeErrorInfo w_emlrtRTEI;
extern rtRunTimeErrorInfo x_emlrtRTEI;
extern rtRunTimeErrorInfo y_emlrtRTEI;
extern rtRunTimeErrorInfo ab_emlrtRTEI;
extern rtRunTimeErrorInfo cb_emlrtRTEI;
extern rtRunTimeErrorInfo db_emlrtRTEI;
extern rtBoundsCheckInfo n_emlrtBCI;
extern rtBoundsCheckInfo o_emlrtBCI;
extern rtBoundsCheckInfo p_emlrtBCI;
extern rtBoundsCheckInfo q_emlrtBCI;
extern rtBoundsCheckInfo r_emlrtBCI;
extern rtBoundsCheckInfo s_emlrtBCI;
extern rtDoubleCheckInfo j_emlrtDCI;
extern rtDoubleCheckInfo k_emlrtDCI;
extern rtDoubleCheckInfo l_emlrtDCI;
extern rtRunTimeErrorInfo eb_emlrtRTEI;
extern rtRunTimeErrorInfo fb_emlrtRTEI;
extern rtEqualityCheckInfo c_emlrtECI;
extern rtBoundsCheckInfo t_emlrtBCI;
extern rtBoundsCheckInfo u_emlrtBCI;
extern rtRunTimeErrorInfo gb_emlrtRTEI;
extern rtDoubleCheckInfo n_emlrtDCI;
extern rtRunTimeErrorInfo ib_emlrtRTEI;
extern rtRunTimeErrorInfo jb_emlrtRTEI;
extern rtRunTimeErrorInfo mb_emlrtRTEI;
extern rtRunTimeErrorInfo vb_emlrtRTEI;
extern rtRunTimeErrorInfo wb_emlrtRTEI;
extern rtRunTimeErrorInfo bc_emlrtRTEI;
extern rtRunTimeErrorInfo cc_emlrtRTEI;
extern rtDoubleCheckInfo r_emlrtDCI;
extern rtRunTimeErrorInfo ec_emlrtRTEI;
extern rtRunTimeErrorInfo hc_emlrtRTEI;
extern rtRunTimeErrorInfo oc_emlrtRTEI;
extern const boolean_T bv[128];
extern const char cv[128];
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
