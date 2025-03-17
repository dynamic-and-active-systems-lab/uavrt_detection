//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: uavrt_detection_data.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "uavrt_detection_data.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_types.h"

// Variable Definitions
coder::array<char, 2U> globalThresholdCachePath;

unsigned int state[625];

double freq;

boolean_T freq_not_empty;

omp_nest_lock_t uavrt_detection_nestLockGlobal;

rtRunTimeErrorInfo emlrtRTEI{
    24,     // lineNo
    "error" // fName
};

rtRunTimeErrorInfo b_emlrtRTEI{
    86,           // lineNo
    "getFileStar" // fName
};

rtRunTimeErrorInfo c_emlrtRTEI{
    24,    // lineNo
    "feof" // fName
};

rtRunTimeErrorInfo i_emlrtRTEI{
    15,                     // lineNo
    "assertSupportedString" // fName
};

rtRunTimeErrorInfo j_emlrtRTEI{
    12,              // lineNo
    "mustBePositive" // fName
};

rtRunTimeErrorInfo k_emlrtRTEI{
    80,                 // lineNo
    "reshapeSizeChecks" // fName
};

rtRunTimeErrorInfo l_emlrtRTEI{
    87,                 // lineNo
    "reshapeSizeChecks" // fName
};

rtRunTimeErrorInfo m_emlrtRTEI{
    64,                  // lineNo
    "assertValidSizeArg" // fName
};

rtRunTimeErrorInfo n_emlrtRTEI{
    18,                    // lineNo
    "binaryRelopValidator" // fName
};

rtDoubleCheckInfo emlrtDCI{
    12,      // lineNo
    "blanks" // fName
};

rtBoundsCheckInfo emlrtBCI{
    227,                      // lineNo
    "",                       // aName
    "AsyncBufferSysObj/write" // fName
};

rtRunTimeErrorInfo r_emlrtRTEI{
    14,                   // lineNo
    "validatenonnegative" // fName
};

rtRunTimeErrorInfo s_emlrtRTEI{
    324,                     // lineNo
    "AsyncBufferSysObj/read" // fName
};

rtRunTimeErrorInfo u_emlrtRTEI{
    13,                // lineNo
    "validatenonempty" // fName
};

rtRunTimeErrorInfo v_emlrtRTEI{
    14,              // lineNo
    "validatenonnan" // fName
};

rtRunTimeErrorInfo w_emlrtRTEI{
    14,              // lineNo
    "validatefinite" // fName
};

rtRunTimeErrorInfo x_emlrtRTEI{
    53,      // lineNo
    "bsxfun" // fName
};

rtRunTimeErrorInfo bb_emlrtRTEI{
    13,               // lineNo
    "validateinteger" // fName
};

rtDoubleCheckInfo g_emlrtDCI{
    82,                // lineNo
    "computeDFTviaFFT" // fName
};

rtDoubleCheckInfo h_emlrtDCI{
    82,                // lineNo
    "computeDFTviaFFT" // fName
};

rtBoundsCheckInfo k_emlrtBCI{
    84,                // lineNo
    "",                // aName
    "computeDFTviaFFT" // fName
};

rtBoundsCheckInfo l_emlrtBCI{
    85,                // lineNo
    "",                // aName
    "computeDFTviaFFT" // fName
};

rtEqualityCheckInfo d_emlrtECI{
    -1,                // nDims
    85,                // lineNo
    "computeDFTviaFFT" // fName
};

rtRunTimeErrorInfo db_emlrtRTEI{
    37,   // lineNo
    "fft" // fName
};

rtRunTimeErrorInfo eb_emlrtRTEI{
    48,   // lineNo
    "fft" // fName
};

rtRunTimeErrorInfo fb_emlrtRTEI{
    52,   // lineNo
    "fft" // fName
};

rtRunTimeErrorInfo gb_emlrtRTEI{
    12,        // lineNo
    "datawrap" // fName
};

rtBoundsCheckInfo m_emlrtBCI{
    35,        // lineNo
    "",        // aName
    "datawrap" // fName
};

rtBoundsCheckInfo n_emlrtBCI{
    35,        // lineNo
    "",        // aName
    "datawrap" // fName
};

rtBoundsCheckInfo o_emlrtBCI{
    39,        // lineNo
    "",        // aName
    "datawrap" // fName
};

rtBoundsCheckInfo p_emlrtBCI{
    71,        // lineNo
    "",        // aName
    "datawrap" // fName
};

rtBoundsCheckInfo q_emlrtBCI{
    71,        // lineNo
    "",        // aName
    "datawrap" // fName
};

rtBoundsCheckInfo r_emlrtBCI{
    71,        // lineNo
    "",        // aName
    "datawrap" // fName
};

rtRunTimeErrorInfo hb_emlrtRTEI{
    13,              // lineNo
    "toLogicalCheck" // fName
};

rtRunTimeErrorInfo jb_emlrtRTEI{
    58,                  // lineNo
    "assertValidSizeArg" // fName
};

rtRunTimeErrorInfo kb_emlrtRTEI{
    13,                    // lineNo
    "assertCompatibleDims" // fName
};

rtRunTimeErrorInfo lb_emlrtRTEI{
    159,                   // lineNo
    "coderTimeCheckStatus" // fName
};

rtEqualityCheckInfo e_emlrtECI{
    -1,                       // nDims
    227,                      // lineNo
    "AsyncBufferSysObj/write" // fName
};

rtRunTimeErrorInfo qb_emlrtRTEI{
    225,                  // lineNo
    "check_non_axis_size" // fName
};

rtRunTimeErrorInfo tb_emlrtRTEI{
    85,                 // lineNo
    "reshapeSizeChecks" // fName
};

rtRunTimeErrorInfo wb_emlrtRTEI{
    198,            // lineNo
    "unaryMinOrMax" // fName
};

rtRunTimeErrorInfo xb_emlrtRTEI{
    13,    // lineNo
    "sqrt" // fName
};

rtDoubleCheckInfo m_emlrtDCI{
    1495,                 // lineNo
    "sparse/nullcopyLike" // fName
};

rtRunTimeErrorInfo ac_emlrtRTEI{
    18,                              // lineNo
    "eml_int_forloop_overflow_check" // fName
};

rtRunTimeErrorInfo cc_emlrtRTEI{
    1626,             // lineNo
    "assertValidSize" // fName
};

rtRunTimeErrorInfo ec_emlrtRTEI{
    28,       // lineNo
    "sub2ind" // fName
};

rtRunTimeErrorInfo gc_emlrtRTEI{
    21,       // lineNo
    "ind2sub" // fName
};

rtRunTimeErrorInfo jc_emlrtRTEI{
    48,       // lineNo
    "fprintf" // fName
};

rtRunTimeErrorInfo kc_emlrtRTEI{
    125,       // lineNo
    "cfprintf" // fName
};

const boolean_T bv[128]{
    false, false, false, false, false, false, false, false, false, true,  true,
    true,  true,  true,  false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, true,  true,  true,  true,  true,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false};

const char cv1[22]{'c', 'o', 'd', 'e', 'r', 'I', 'n', 'i', 't', 'T', 'i',
                   'm', 'e', 'F', 'u', 'n', 'c', 't', 'i', 'o', 'n', 's'};

const char cv2[30]{'c', 'o', 'd', 'e', 'r', 'T', 'i', 'm', 'e', 'C',
                   'l', 'o', 'c', 'k', 'G', 'e', 't', 't', 'i', 'm',
                   'e', 'M', 'o', 'n', 'o', 't', 'o', 'n', 'i', 'c'};

boolean_T isInitialized_uavrt_detection{false};

//
// File trailer for uavrt_detection_data.cpp
//
// [EOF]
//
