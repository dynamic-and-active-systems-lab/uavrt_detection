//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: _coder_uavrt_detection_mex.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 22-Oct-2022 15:24:58
//

// Include Files
#include "_coder_uavrt_detection_mex.h"
#include "_coder_uavrt_detection_api.h"

// Function Definitions
//
// Arguments    : int32_T nlhs
//                mxArray *plhs[]
//                int32_T nrhs
//                const mxArray *prhs[]
// Return Type  : void
//
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

//
// Arguments    : void
// Return Type  : emlrtCTX
//
emlrtCTX mexFunctionCreateRootTLS()
{
  emlrtCreateRootTLSR2022a(&emlrtRootTLSGlobal, &emlrtContextGlobal, nullptr, 1,
                           nullptr, "UTF-8", true);
  return emlrtRootTLSGlobal;
}

//
// Arguments    : int32_T nlhs
//                int32_T nrhs
// Return Type  : void
//
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

//
// File trailer for _coder_uavrt_detection_mex.cpp
//
// [EOF]
//
