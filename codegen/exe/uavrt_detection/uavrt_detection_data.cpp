//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: uavrt_detection_data.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 14:31:55
//

// Include Files
#include "uavrt_detection_data.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_types.h"
#include <string.h>

// Variable Definitions
unsigned int method;

unsigned int b_method;

unsigned int state[625];

double freq;

boolean_T freq_not_empty;

omp_nest_lock_t uavrt_detection_nestLockGlobal;

rtRunTimeErrorInfo emlrtRTEI{
    275,                  // lineNo
    "check_non_axis_size" // fName
};

rtRunTimeErrorInfo b_emlrtRTEI{
    24,     // lineNo
    "error" // fName
};

rtRunTimeErrorInfo c_emlrtRTEI{
    22,    // lineNo
    "feof" // fName
};

rtRunTimeErrorInfo d_emlrtRTEI{
    84,           // lineNo
    "getFileStar" // fName
};

rtRunTimeErrorInfo h_emlrtRTEI{
    81,        // lineNo
    "eml_find" // fName
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

rtRunTimeErrorInfo v_emlrtRTEI{
    14,                   // lineNo
    "validatenonnegative" // fName
};

rtRunTimeErrorInfo w_emlrtRTEI{
    324,                       // lineNo
    "AsyncBuffercgHelper/read" // fName
};

rtRunTimeErrorInfo x_emlrtRTEI{
    473,                                        // lineNo
    "AsyncBuffercgHelper/ReadSamplesFromBuffer" // fName
};

rtEqualityCheckInfo
    emlrtECI{
        -1,                                          // nDims
        462,                                         // lineNo
        17,                                          // colNo
        "AsyncBuffercgHelper/ReadSamplesFromBuffer", // fName
        "C:\\Program "
        "Files\\MATLAB\\toolbox\\dsp\\dsp\\+dsp\\+"
        "internal\\AsyncBuffercgHelper.m" // pName
    };

rtBoundsCheckInfo
    b_emlrtBCI{
        -1,                                          // iFirst
        -1,                                          // iLast
        462,                                         // lineNo
        50,                                          // colNo
        "",                                          // aName
        "AsyncBuffercgHelper/ReadSamplesFromBuffer", // fName
        "C:\\Program "
        "Files\\MATLAB\\toolbox\\dsp\\dsp\\+dsp\\+"
        "internal\\AsyncBuffercgHelper.m", // pName
        0                                  // checkKind
    };

rtBoundsCheckInfo
    c_emlrtBCI{
        -1,                                          // iFirst
        -1,                                          // iLast
        462,                                         // lineNo
        21,                                          // colNo
        "",                                          // aName
        "AsyncBuffercgHelper/ReadSamplesFromBuffer", // fName
        "C:\\Program "
        "Files\\MATLAB\\toolbox\\dsp\\dsp\\+dsp\\+"
        "internal\\AsyncBuffercgHelper.m", // pName
        0                                  // checkKind
    };

rtDoubleCheckInfo
    emlrtDCI{
        463,                                         // lineNo
        27,                                          // colNo
        "AsyncBuffercgHelper/ReadSamplesFromBuffer", // fName
        "C:\\Program "
        "Files\\MATLAB\\toolbox\\dsp\\dsp\\+dsp\\+"
        "internal\\AsyncBuffercgHelper.m", // pName
        4                                  // checkKind
    };

rtRunTimeErrorInfo cb_emlrtRTEI{
    14,              // lineNo
    "validatefinite" // fName
};

rtRunTimeErrorInfo db_emlrtRTEI{
    14,              // lineNo
    "validatenonnan" // fName
};

rtRunTimeErrorInfo eb_emlrtRTEI{
    13,                // lineNo
    "validatenonempty" // fName
};

rtRunTimeErrorInfo fb_emlrtRTEI{
    13,               // lineNo
    "validateinteger" // fName
};

rtRunTimeErrorInfo gb_emlrtRTEI{
    58,                  // lineNo
    "assertValidSizeArg" // fName
};

rtRunTimeErrorInfo hb_emlrtRTEI{
    159,                   // lineNo
    "coderTimeCheckStatus" // fName
};

rtBoundsCheckInfo
    e_emlrtBCI{
        1,                                           // iFirst
        5800321,                                     // iLast
        457,                                         // lineNo
        29,                                          // colNo
        "",                                          // aName
        "AsyncBuffercgHelper/ReadSamplesFromBuffer", // fName
        "C:\\Program "
        "Files\\MATLAB\\toolbox\\dsp\\dsp\\+dsp\\+"
        "internal\\AsyncBuffercgHelper.m", // pName
        0                                  // checkKind
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

const char cv[22]{'c', 'o', 'd', 'e', 'r', 'I', 'n', 'i', 't', 'T', 'i',
                  'm', 'e', 'F', 'u', 'n', 'c', 't', 'i', 'o', 'n', 's'};

const char cv1[30]{'c', 'o', 'd', 'e', 'r', 'T', 'i', 'm', 'e', 'C',
                   'l', 'o', 'c', 'k', 'G', 'e', 't', 't', 'i', 'm',
                   'e', 'M', 'o', 'n', 'o', 't', 'o', 'n', 'i', 'c'};

boolean_T isInitialized_uavrt_detection{false};

//
// File trailer for uavrt_detection_data.cpp
//
// [EOF]
//
