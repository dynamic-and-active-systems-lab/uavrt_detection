//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: uavrt_detection_data.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 16-Mar-2023 20:03:46
//

// Include Files
#include "uavrt_detection_data.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_types.h"
#include <string.h>

// Variable Definitions
unsigned int state[625];

double freq;

boolean_T freq_not_empty;

omp_nest_lock_t uavrt_detection_nestLockGlobal;

rtRunTimeErrorInfo emlrtRTEI{
    24,     // lineNo
    "error" // fName
};

rtRunTimeErrorInfo b_emlrtRTEI{
    14,     // lineNo
    "log10" // fName
};

rtRunTimeErrorInfo c_emlrtRTEI{
    22,    // lineNo
    "feof" // fName
};

rtRunTimeErrorInfo d_emlrtRTEI{
    84,           // lineNo
    "getFileStar" // fName
};

rtRunTimeErrorInfo j_emlrtRTEI{
    15,                     // lineNo
    "assertSupportedString" // fName
};

rtRunTimeErrorInfo m_emlrtRTEI{
    52,                 // lineNo
    "reshapeSizeChecks" // fName
};

rtRunTimeErrorInfo n_emlrtRTEI{
    59,                 // lineNo
    "reshapeSizeChecks" // fName
};

rtRunTimeErrorInfo o_emlrtRTEI{
    64,                  // lineNo
    "assertValidSizeArg" // fName
};

rtBoundsCheckInfo
    emlrtBCI{
        1,                           // iFirst
        600651,                      // iLast
        227,                         // lineNo
        23,                          // colNo
        "",                          // aName
        "AsyncBuffercgHelper/write", // fName
        "C:\\Program "
        "Files\\MATLAB\\toolbox\\dsp\\dsp\\+dsp\\+"
        "internal\\AsyncBuffercgHelper.m", // pName
        3                                  // checkKind
    };

rtRunTimeErrorInfo v_emlrtRTEI{
    14,                   // lineNo
    "validatenonnegative" // fName
};

rtRunTimeErrorInfo w_emlrtRTEI{
    324,                       // lineNo
    "AsyncBuffercgHelper/read" // fName
};

rtRunTimeErrorInfo db_emlrtRTEI{
    14,              // lineNo
    "validatefinite" // fName
};

rtRunTimeErrorInfo eb_emlrtRTEI{
    14,              // lineNo
    "validatenonnan" // fName
};

rtRunTimeErrorInfo fb_emlrtRTEI{
    13,                // lineNo
    "validatenonempty" // fName
};

rtRunTimeErrorInfo gb_emlrtRTEI{
    13,               // lineNo
    "validateinteger" // fName
};

rtRunTimeErrorInfo ib_emlrtRTEI{
    31,         // lineNo
    "circshift" // fName
};

rtRunTimeErrorInfo jb_emlrtRTEI{
    53,      // lineNo
    "bsxfun" // fName
};

rtBoundsCheckInfo q_emlrtBCI{
    -1,                                                            // iFirst
    -1,                                                            // iLast
    45,                                                            // lineNo
    11,                                                            // colNo
    "",                                                            // aName
    "datawrap",                                                    // fName
    "C:\\Program Files\\MATLAB\\toolbox\\signal\\eml\\datawrap.m", // pName
    0                                                              // checkKind
};

rtBoundsCheckInfo r_emlrtBCI{
    -1,                                                            // iFirst
    -1,                                                            // iLast
    45,                                                            // lineNo
    25,                                                            // colNo
    "",                                                            // aName
    "datawrap",                                                    // fName
    "C:\\Program Files\\MATLAB\\toolbox\\signal\\eml\\datawrap.m", // pName
    0                                                              // checkKind
};

rtBoundsCheckInfo s_emlrtBCI{
    -1,                                                            // iFirst
    -1,                                                            // iLast
    45,                                                            // lineNo
    18,                                                            // colNo
    "",                                                            // aName
    "datawrap",                                                    // fName
    "C:\\Program Files\\MATLAB\\toolbox\\signal\\eml\\datawrap.m", // pName
    0                                                              // checkKind
};

rtBoundsCheckInfo t_emlrtBCI{
    -1,                                                            // iFirst
    -1,                                                            // iLast
    39,                                                            // lineNo
    7,                                                             // colNo
    "",                                                            // aName
    "datawrap",                                                    // fName
    "C:\\Program Files\\MATLAB\\toolbox\\signal\\eml\\datawrap.m", // pName
    0                                                              // checkKind
};

rtBoundsCheckInfo u_emlrtBCI{
    -1,                                                            // iFirst
    -1,                                                            // iLast
    35,                                                            // lineNo
    7,                                                             // colNo
    "",                                                            // aName
    "datawrap",                                                    // fName
    "C:\\Program Files\\MATLAB\\toolbox\\signal\\eml\\datawrap.m", // pName
    0                                                              // checkKind
};

rtBoundsCheckInfo v_emlrtBCI{
    -1,                                                            // iFirst
    -1,                                                            // iLast
    35,                                                            // lineNo
    14,                                                            // colNo
    "",                                                            // aName
    "datawrap",                                                    // fName
    "C:\\Program Files\\MATLAB\\toolbox\\signal\\eml\\datawrap.m", // pName
    0                                                              // checkKind
};

rtDoubleCheckInfo
    k_emlrtDCI{
        81,                 // lineNo
        1,                  // colNo
        "computeDFTviaFFT", // fName
        "C:\\Program "
        "Files\\MATLAB\\toolbox\\signal\\signal\\private\\computeDFT.m", // pName
        1 // checkKind
    };

rtDoubleCheckInfo
    l_emlrtDCI{
        81,                 // lineNo
        12,                 // colNo
        "computeDFTviaFFT", // fName
        "C:\\Program "
        "Files\\MATLAB\\toolbox\\signal\\signal\\private\\computeDFT.m", // pName
        4 // checkKind
    };

rtDoubleCheckInfo
    m_emlrtDCI{
        81,                 // lineNo
        12,                 // colNo
        "computeDFTviaFFT", // fName
        "C:\\Program "
        "Files\\MATLAB\\toolbox\\signal\\signal\\private\\computeDFT.m", // pName
        1 // checkKind
    };

rtRunTimeErrorInfo kb_emlrtRTEI{
    12,        // lineNo
    "datawrap" // fName
};

rtRunTimeErrorInfo lb_emlrtRTEI{
    37,   // lineNo
    "fft" // fName
};

rtEqualityCheckInfo
    d_emlrtECI{
        -1,                 // nDims
        85,                 // lineNo
        9,                  // colNo
        "computeDFTviaFFT", // fName
        "C:\\Program "
        "Files\\MATLAB\\toolbox\\signal\\signal\\private\\computeDFT.m" // pName
    };

rtBoundsCheckInfo
    w_emlrtBCI{
        -1,                 // iFirst
        -1,                 // iLast
        85,                 // lineNo
        14,                 // colNo
        "",                 // aName
        "computeDFTviaFFT", // fName
        "C:\\Program "
        "Files\\MATLAB\\toolbox\\signal\\signal\\private\\computeDFT.m", // pName
        0 // checkKind
    };

rtBoundsCheckInfo
    x_emlrtBCI{
        -1,                 // iFirst
        -1,                 // iLast
        84,                 // lineNo
        38,                 // colNo
        "",                 // aName
        "computeDFTviaFFT", // fName
        "C:\\Program "
        "Files\\MATLAB\\toolbox\\signal\\signal\\private\\computeDFT.m", // pName
        0 // checkKind
    };

rtRunTimeErrorInfo mb_emlrtRTEI{
    13,              // lineNo
    "toLogicalCheck" // fName
};

rtDoubleCheckInfo o_emlrtDCI{
    31,       // lineNo
    14,       // colNo
    "repmat", // fName
    "C:\\Program Files\\MATLAB\\toolbox\\eml\\lib\\matlab\\elmat\\repmat.m", // pName
    4 // checkKind
};

rtRunTimeErrorInfo ob_emlrtRTEI{
    58,                  // lineNo
    "assertValidSizeArg" // fName
};

rtRunTimeErrorInfo pb_emlrtRTEI{
    13,                    // lineNo
    "assertCompatibleDims" // fName
};

rtRunTimeErrorInfo qb_emlrtRTEI{
    159,                   // lineNo
    "coderTimeCheckStatus" // fName
};

rtEqualityCheckInfo
    e_emlrtECI{
        -1,                          // nDims
        227,                         // lineNo
        13,                          // colNo
        "AsyncBuffercgHelper/write", // fName
        "C:\\Program "
        "Files\\MATLAB\\toolbox\\dsp\\dsp\\+dsp\\+"
        "internal\\AsyncBuffercgHelper.m" // pName
    };

rtRunTimeErrorInfo ub_emlrtRTEI{
    275,                  // lineNo
    "check_non_axis_size" // fName
};

rtRunTimeErrorInfo yb_emlrtRTEI{
    206,           // lineNo
    "interp1_work" // fName
};

rtRunTimeErrorInfo ac_emlrtRTEI{
    164,           // lineNo
    "interp1_work" // fName
};

rtRunTimeErrorInfo bc_emlrtRTEI{
    135,            // lineNo
    "unaryMinOrMax" // fName
};

rtRunTimeErrorInfo dc_emlrtRTEI{
    13,    // lineNo
    "sqrt" // fName
};

rtRunTimeErrorInfo gc_emlrtRTEI{
    138,                  // lineNo
    "dynamic_size_checks" // fName
};

rtRunTimeErrorInfo hc_emlrtRTEI{
    133,                  // lineNo
    "dynamic_size_checks" // fName
};

rtDoubleCheckInfo r_emlrtDCI{
    1501,                  // lineNo
    44,                    // colNo
    "sparse/nullcopyLike", // fName
    "C:\\Program "
    "Files\\MATLAB\\toolbox\\shared\\coder\\coder\\+coder\\+internal\\@"
    "sparse\\sparse.m", // pName
    4                   // checkKind
};

rtRunTimeErrorInfo jc_emlrtRTEI{
    1632,             // lineNo
    "assertValidSize" // fName
};

rtRunTimeErrorInfo mc_emlrtRTEI{
    42,           // lineNo
    "eml_sub2ind" // fName
};

rtRunTimeErrorInfo sc_emlrtRTEI{
    132,          // lineNo
    "eml_idivide" // fName
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

const char cv4[18]{'f', 'r', 'e', 'q', 'S', 'e', 'a', 'r', 'c',
                   'h', 'S', 'o', 'f', 't', 'L', 'o', 'c', 'k'};

boolean_T isInitialized_uavrt_detection{false};

//
// File trailer for uavrt_detection_data.cpp
//
// [EOF]
//
