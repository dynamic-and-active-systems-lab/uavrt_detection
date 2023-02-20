//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: uavrt_detection_data.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 15:31:40
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
extern rtRunTimeErrorInfo b_emlrtRTEI;
extern rtRunTimeErrorInfo c_emlrtRTEI;
extern rtRunTimeErrorInfo d_emlrtRTEI;
extern rtRunTimeErrorInfo j_emlrtRTEI;
extern rtRunTimeErrorInfo m_emlrtRTEI;
extern rtRunTimeErrorInfo n_emlrtRTEI;
extern rtRunTimeErrorInfo o_emlrtRTEI;
extern rtBoundsCheckInfo emlrtBCI;
extern rtRunTimeErrorInfo u_emlrtRTEI;
extern rtRunTimeErrorInfo v_emlrtRTEI;
extern rtRunTimeErrorInfo w_emlrtRTEI;
extern rtRunTimeErrorInfo db_emlrtRTEI;
extern rtRunTimeErrorInfo eb_emlrtRTEI;
extern rtRunTimeErrorInfo fb_emlrtRTEI;
extern rtRunTimeErrorInfo gb_emlrtRTEI;
extern rtRunTimeErrorInfo ib_emlrtRTEI;
extern rtRunTimeErrorInfo jb_emlrtRTEI;
extern rtBoundsCheckInfo q_emlrtBCI;
extern rtBoundsCheckInfo r_emlrtBCI;
extern rtBoundsCheckInfo s_emlrtBCI;
extern rtBoundsCheckInfo t_emlrtBCI;
extern rtBoundsCheckInfo u_emlrtBCI;
extern rtBoundsCheckInfo v_emlrtBCI;
extern rtDoubleCheckInfo k_emlrtDCI;
extern rtDoubleCheckInfo l_emlrtDCI;
extern rtDoubleCheckInfo m_emlrtDCI;
extern rtRunTimeErrorInfo kb_emlrtRTEI;
extern rtRunTimeErrorInfo lb_emlrtRTEI;
extern rtEqualityCheckInfo d_emlrtECI;
extern rtBoundsCheckInfo w_emlrtBCI;
extern rtBoundsCheckInfo x_emlrtBCI;
extern rtRunTimeErrorInfo mb_emlrtRTEI;
extern rtDoubleCheckInfo o_emlrtDCI;
extern rtRunTimeErrorInfo ob_emlrtRTEI;
extern rtRunTimeErrorInfo pb_emlrtRTEI;
extern rtRunTimeErrorInfo qb_emlrtRTEI;
extern rtEqualityCheckInfo e_emlrtECI;
extern rtRunTimeErrorInfo ub_emlrtRTEI;
extern rtRunTimeErrorInfo yb_emlrtRTEI;
extern rtRunTimeErrorInfo ac_emlrtRTEI;
extern rtRunTimeErrorInfo bc_emlrtRTEI;
extern rtRunTimeErrorInfo fc_emlrtRTEI;
extern rtRunTimeErrorInfo gc_emlrtRTEI;
extern rtDoubleCheckInfo r_emlrtDCI;
extern rtRunTimeErrorInfo ic_emlrtRTEI;
extern rtRunTimeErrorInfo lc_emlrtRTEI;
extern rtRunTimeErrorInfo rc_emlrtRTEI;
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
