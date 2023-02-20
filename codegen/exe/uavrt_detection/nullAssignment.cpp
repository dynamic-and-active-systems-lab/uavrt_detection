//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: nullAssignment.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 14:31:55
//

// Include Files
#include "nullAssignment.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include "omp.h"
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string.h>
#include <string>

// Function Declarations
static void gb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void gb_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Matrix index is out of range for deletion.";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// Arguments    : ::coder::array<char, 2U> &x
//                int idx
// Return Type  : void
//
namespace coder {
namespace internal {
void nullAssignment(::coder::array<char, 2U> &x, int idx)
{
  static rtRunTimeErrorInfo kb_emlrtRTEI{
      85,               // lineNo
      "validate_inputs" // fName
  };
  int nxin;
  int nxout;
  if (idx > x.size(1)) {
    gb_rtErrorWithMessageID(kb_emlrtRTEI.fName, kb_emlrtRTEI.lineNo);
  }
  nxin = x.size(1);
  nxout = x.size(1) - 1;
  for (int k{idx}; k <= nxout; k++) {
    x[k - 1] = x[k];
  }
  if (nxout < 1) {
    nxout = 0;
  } else {
    nxout = nxin - 1;
  }
  x.set_size(x.size(0), nxout);
}

} // namespace internal
} // namespace coder

//
// File trailer for nullAssignment.cpp
//
// [EOF]
//
