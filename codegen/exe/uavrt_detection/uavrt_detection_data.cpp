//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: uavrt_detection_data.cpp
//
<<<<<<< HEAD
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 23-May-2023 12:05:02
=======
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Apr-2023 11:47:02
>>>>>>> 3930a1e557481905555f2756f2f70ac82e87beba
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
    24,      // lineNo
    9,       // colNo
    "error", // fName
    "/Applications/MATLAB_R2023a.app/toolbox/eml/lib/matlab/lang/error.m" // pName
};

rtRunTimeErrorInfo b_emlrtRTEI{
    14,      // lineNo
    9,       // colNo
    "log10", // fName
    "/Applications/MATLAB_R2023a.app/toolbox/eml/lib/matlab/elfun/log10.m" // pName
};

rtRunTimeErrorInfo c_emlrtRTEI{
    24,     // lineNo
    13,     // colNo
    "feof", // fName
    "/Applications/MATLAB_R2023a.app/toolbox/eml/lib/matlab/iofun/feof.m" // pName
};

rtRunTimeErrorInfo d_emlrtRTEI{
    86,            // lineNo
    5,             // colNo
    "getFileStar", // fName
    "/Applications/MATLAB_R2023a.app/toolbox/eml/lib/matlab/iofun/fseek.m" // pName
};

rtRunTimeErrorInfo j_emlrtRTEI{
    15,                      // lineNo
    9,                       // colNo
    "assertSupportedString", // fName
    "/Applications/MATLAB_R2023a.app/toolbox/eml/eml/+coder/+internal/"
    "assertSupportedString.m" // pName
};

rtRunTimeErrorInfo k_emlrtRTEI{
    74,                  // lineNo
    13,                  // colNo
    "reshapeSizeChecks", // fName
    "/Applications/MATLAB_R2023a.app/toolbox/eml/eml/+coder/+internal/"
    "reshapeSizeChecks.m" // pName
};

rtRunTimeErrorInfo l_emlrtRTEI{
    81,                  // lineNo
    23,                  // colNo
    "reshapeSizeChecks", // fName
    "/Applications/MATLAB_R2023a.app/toolbox/eml/eml/+coder/+internal/"
    "reshapeSizeChecks.m" // pName
};

rtRunTimeErrorInfo m_emlrtRTEI{
    64,                   // lineNo
    15,                   // colNo
    "assertValidSizeArg", // fName
    "/Applications/MATLAB_R2023a.app/toolbox/eml/eml/+coder/+internal/"
    "assertValidSizeArg.m" // pName
};

rtBoundsCheckInfo emlrtBCI{
    1,                           // iFirst
    600651,                      // iLast
    227,                         // lineNo
    23,                          // colNo
    "",                          // aName
    "AsyncBuffercgHelper/write", // fName
    "/Applications/MATLAB_R2023a.app/toolbox/dsp/dsp/+dsp/+internal/"
    "AsyncBuffercgHelper.m", // pName
    3                        // checkKind
};

rtRunTimeErrorInfo q_emlrtRTEI{
    14,                    // lineNo
    37,                    // colNo
    "validatenonnegative", // fName
    "/Applications/MATLAB_R2023a.app/toolbox/eml/eml/+coder/+internal/+valattr/"
    "validatenonnegative.m" // pName
};

rtRunTimeErrorInfo r_emlrtRTEI{
    324,                        // lineNo
    13,                         // colNo
    "AsyncBuffercgHelper/read", // fName
    "/Applications/MATLAB_R2023a.app/toolbox/dsp/dsp/+dsp/+internal/"
    "AsyncBuffercgHelper.m" // pName
};

rtRunTimeErrorInfo v_emlrtRTEI{
    13,                 // lineNo
    37,                 // colNo
    "validatenonempty", // fName
    "/Applications/MATLAB_R2023a.app/toolbox/eml/eml/+coder/+internal/+valattr/"
    "validatenonempty.m" // pName
};

rtRunTimeErrorInfo w_emlrtRTEI{
    14,               // lineNo
    37,               // colNo
    "validatenonnan", // fName
    "/Applications/MATLAB_R2023a.app/toolbox/eml/eml/+coder/+internal/+valattr/"
    "validatenonnan.m" // pName
};

rtRunTimeErrorInfo x_emlrtRTEI{
    14,               // lineNo
    37,               // colNo
    "validatefinite", // fName
    "/Applications/MATLAB_R2023a.app/toolbox/eml/eml/+coder/+internal/+valattr/"
    "validatefinite.m" // pName
};

rtRunTimeErrorInfo y_emlrtRTEI{
    53,       // lineNo
    15,       // colNo
    "bsxfun", // fName
    "/Applications/MATLAB_R2023a.app/toolbox/eml/lib/matlab/elmat/bsxfun.m" // pName
};

rtRunTimeErrorInfo cb_emlrtRTEI{
    13,                // lineNo
    37,                // colNo
    "validateinteger", // fName
    "/Applications/MATLAB_R2023a.app/toolbox/eml/eml/+coder/+internal/+valattr/"
    "validateinteger.m" // pName
};

rtBoundsCheckInfo k_emlrtBCI{
    -1,                                                              // iFirst
    -1,                                                              // iLast
    45,                                                              // lineNo
    11,                                                              // colNo
    "",                                                              // aName
    "datawrap",                                                      // fName
    "/Applications/MATLAB_R2023a.app/toolbox/signal/eml/datawrap.m", // pName
    0 // checkKind
};

rtBoundsCheckInfo l_emlrtBCI{
    -1,                                                              // iFirst
    -1,                                                              // iLast
    45,                                                              // lineNo
    25,                                                              // colNo
    "",                                                              // aName
    "datawrap",                                                      // fName
    "/Applications/MATLAB_R2023a.app/toolbox/signal/eml/datawrap.m", // pName
    0 // checkKind
};

rtBoundsCheckInfo m_emlrtBCI{
    -1,                                                              // iFirst
    -1,                                                              // iLast
    39,                                                              // lineNo
    7,                                                               // colNo
    "",                                                              // aName
    "datawrap",                                                      // fName
    "/Applications/MATLAB_R2023a.app/toolbox/signal/eml/datawrap.m", // pName
    0 // checkKind
};

rtBoundsCheckInfo n_emlrtBCI{
    -1,                                                              // iFirst
    -1,                                                              // iLast
    35,                                                              // lineNo
    7,                                                               // colNo
    "",                                                              // aName
    "datawrap",                                                      // fName
    "/Applications/MATLAB_R2023a.app/toolbox/signal/eml/datawrap.m", // pName
    0 // checkKind
};

rtBoundsCheckInfo o_emlrtBCI{
    -1,                                                              // iFirst
    -1,                                                              // iLast
    35,                                                              // lineNo
    14,                                                              // colNo
    "",                                                              // aName
    "datawrap",                                                      // fName
    "/Applications/MATLAB_R2023a.app/toolbox/signal/eml/datawrap.m", // pName
    0 // checkKind
};

rtDoubleCheckInfo g_emlrtDCI{
    81,                 // lineNo
    1,                  // colNo
    "computeDFTviaFFT", // fName
    "/Applications/MATLAB_R2023a.app/toolbox/signal/signal/private/"
    "computeDFT.m", // pName
    1               // checkKind
};

rtDoubleCheckInfo h_emlrtDCI{
    81,                 // lineNo
    12,                 // colNo
    "computeDFTviaFFT", // fName
    "/Applications/MATLAB_R2023a.app/toolbox/signal/signal/private/"
    "computeDFT.m", // pName
    4               // checkKind
};

rtDoubleCheckInfo i_emlrtDCI{
    81,                 // lineNo
    12,                 // colNo
    "computeDFTviaFFT", // fName
    "/Applications/MATLAB_R2023a.app/toolbox/signal/signal/private/"
    "computeDFT.m", // pName
    1               // checkKind
};

rtRunTimeErrorInfo eb_emlrtRTEI{
    12,                                                             // lineNo
    23,                                                             // colNo
    "datawrap",                                                     // fName
    "/Applications/MATLAB_R2023a.app/toolbox/signal/eml/datawrap.m" // pName
};

rtRunTimeErrorInfo fb_emlrtRTEI{
    37,    // lineNo
    31,    // colNo
    "fft", // fName
    "/Applications/MATLAB_R2023a.app/toolbox/eml/lib/matlab/datafun/fft.m" // pName
};

rtEqualityCheckInfo
    d_emlrtECI{
        -1,                 // nDims
        85,                 // lineNo
        9,                  // colNo
        "computeDFTviaFFT", // fName
        "/Applications/MATLAB_R2023a.app/toolbox/signal/signal/private/"
        "computeDFT.m" // pName
    };

rtBoundsCheckInfo p_emlrtBCI{
    -1,                 // iFirst
    -1,                 // iLast
    85,                 // lineNo
    14,                 // colNo
    "",                 // aName
    "computeDFTviaFFT", // fName
    "/Applications/MATLAB_R2023a.app/toolbox/signal/signal/private/"
    "computeDFT.m", // pName
    0               // checkKind
};

rtBoundsCheckInfo q_emlrtBCI{
    -1,                 // iFirst
    -1,                 // iLast
    84,                 // lineNo
    38,                 // colNo
    "",                 // aName
    "computeDFTviaFFT", // fName
    "/Applications/MATLAB_R2023a.app/toolbox/signal/signal/private/"
    "computeDFT.m", // pName
    0               // checkKind
};

rtRunTimeErrorInfo gb_emlrtRTEI{
    13,               // lineNo
    13,               // colNo
    "toLogicalCheck", // fName
    "/Applications/MATLAB_R2023a.app/toolbox/eml/eml/+coder/+internal/"
    "toLogicalCheck.m" // pName
};

rtRunTimeErrorInfo ib_emlrtRTEI{
    58,                   // lineNo
    23,                   // colNo
    "assertValidSizeArg", // fName
    "/Applications/MATLAB_R2023a.app/toolbox/eml/eml/+coder/+internal/"
    "assertValidSizeArg.m" // pName
};

rtRunTimeErrorInfo jb_emlrtRTEI{
    13,                     // lineNo
    27,                     // colNo
    "assertCompatibleDims", // fName
    "/Applications/MATLAB_R2023a.app/toolbox/shared/coder/coder/lib/+coder/"
    "+internal/assertCompatibleDims.m" // pName
};

rtRunTimeErrorInfo kb_emlrtRTEI{
    159,                    // lineNo
    13,                     // colNo
    "coderTimeCheckStatus", // fName
    "/Applications/MATLAB_R2023a.app/toolbox/shared/coder/coder/lib/+coder/"
    "+internal/+time/CoderTimeAPI.m" // pName
};

rtEqualityCheckInfo e_emlrtECI{
    -1,                          // nDims
    227,                         // lineNo
    13,                          // colNo
    "AsyncBuffercgHelper/write", // fName
    "/Applications/MATLAB_R2023a.app/toolbox/dsp/dsp/+dsp/+internal/"
    "AsyncBuffercgHelper.m" // pName
};

rtRunTimeErrorInfo ob_emlrtRTEI{
    288,                   // lineNo
    27,                    // colNo
    "check_non_axis_size", // fName
    "/Applications/MATLAB_R2023a.app/toolbox/eml/eml/+coder/+internal/cat.m" // pName
};

rtRunTimeErrorInfo
    sb_emlrtRTEI{
        208,            // lineNo
        13,             // colNo
        "interp1_work", // fName
        "/Applications/MATLAB_R2023a.app/toolbox/eml/lib/matlab/polyfun/"
        "interp1.m" // pName
    };

rtRunTimeErrorInfo
    tb_emlrtRTEI{
        166,            // lineNo
        13,             // colNo
        "interp1_work", // fName
        "/Applications/MATLAB_R2023a.app/toolbox/eml/lib/matlab/polyfun/"
        "interp1.m" // pName
    };

rtRunTimeErrorInfo ub_emlrtRTEI{
    134,             // lineNo
    27,              // colNo
    "unaryMinOrMax", // fName
    "/Applications/MATLAB_R2023a.app/toolbox/eml/eml/+coder/+internal/"
    "unaryMinOrMax.m" // pName
};

rtRunTimeErrorInfo wb_emlrtRTEI{
    13,     // lineNo
    9,      // colNo
    "sqrt", // fName
    "/Applications/MATLAB_R2023a.app/toolbox/eml/lib/matlab/elfun/sqrt.m" // pName
};

rtRunTimeErrorInfo ac_emlrtRTEI{
    138,                   // lineNo
    23,                    // colNo
    "dynamic_size_checks", // fName
    "/Applications/MATLAB_R2023a.app/toolbox/eml/lib/matlab/ops/"
    "eml_mtimes_helper.m" // pName
};

rtRunTimeErrorInfo bc_emlrtRTEI{
    133,                   // lineNo
    23,                    // colNo
    "dynamic_size_checks", // fName
    "/Applications/MATLAB_R2023a.app/toolbox/eml/lib/matlab/ops/"
    "eml_mtimes_helper.m" // pName
};

rtDoubleCheckInfo m_emlrtDCI{
    1501,                  // lineNo
    44,                    // colNo
    "sparse/nullcopyLike", // fName
    "/Applications/MATLAB_R2023a.app/toolbox/shared/coder/coder/+coder/"
    "+internal/@sparse/sparse.m", // pName
    4                             // checkKind
};

rtRunTimeErrorInfo dc_emlrtRTEI{
    1632,              // lineNo
    31,                // colNo
    "assertValidSize", // fName
    "/Applications/MATLAB_R2023a.app/toolbox/shared/coder/coder/+coder/"
    "+internal/@sparse/sparse.m" // pName
};

rtRunTimeErrorInfo
    gc_emlrtRTEI{
        28,        // lineNo
        19,        // colNo
        "sub2ind", // fName
        "/Applications/MATLAB_R2023a.app/toolbox/eml/eml/+coder/+internal/"
        "sub2ind.m" // pName
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
