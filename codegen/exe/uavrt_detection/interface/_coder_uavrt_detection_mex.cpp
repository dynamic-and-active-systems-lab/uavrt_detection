//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// _coder_uavrt_detection_mex.cpp
//
// Code generation for function 'uavrt_detection'
//

// Include files
#include "_coder_uavrt_detection_mex.h"
#include "_coder_uavrt_detection_api.h"

// Function Definitions
void mexFunction(int32_T nlhs, mxArray *[], int32_T nrhs, const mxArray *[])
{
  mexAtExit(&uavrt_detection_atexit);
  // Module initialization.
  uavrt_detection_initialize();
  // Dispatch the entry-point.
  unsafe_uavrt_detection_mexFunction(nlhs, nrhs);
  // Module termination.
  uavrt_detection_terminate();
}

emlrtCTX mexFunctionCreateRootTLS()
{
  emlrtCreateRootTLSR2022a(&emlrtRootTLSGlobal, &emlrtContextGlobal, nullptr, 1,
                           nullptr, (const char_T *)"UTF-8", true);
  return emlrtRootTLSGlobal;
}

void unsafe_uavrt_detection_mexFunction(int32_T nlhs, int32_T nrhs)
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  st.tls = emlrtRootTLSGlobal;
  // Check for proper number of arguments.
  if (nrhs != 0) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 0, 4,
                        15, "uavrt_detection");
  }
  if (nlhs > 0) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 15,
                        "uavrt_detection");
  }
  // Call the function.
  uavrt_detection_api();
}

// End of code generation (_coder_uavrt_detection_mex.cpp)
