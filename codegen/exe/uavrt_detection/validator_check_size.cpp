//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: validator_check_size.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 04-Aug-2023 15:45:46
//

// Include Files
#include "validator_check_size.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_internal_types.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include "omp.h"
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>

// Function Declarations
static void b_rtErrorWithMessageID(const long i, const char *aFcnName,
                                   int aLineNum);

static void n_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : const long i
//                const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void b_rtErrorWithMessageID(const long i, const char *aFcnName,
                                   int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((((((outStream << "Validation size mismatch: input size ") << i)
      << " ~= allowed size ")
     << 2)
    << " for dimension ")
   << 2L)
      << ".";
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
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void n_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream
      << "Number of elements must not change. Use [] as one of the size inputs "
         "to automatically calculate the appropriate size for that di"
         "mension.";
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
// Arguments    : const ::coder::array<double, 2U> &in
//                ::coder::array<double, 2U> &out
// Return Type  : void
//
namespace coder {
namespace internal {
void validator_check_size(const ::coder::array<double, 2U> &in,
                          ::coder::array<double, 2U> &out)
{
  static rtRunTimeErrorInfo qc_emlrtRTEI{
      158,               // lineNo
      31,                // colNo
      "expandOrReshape", // fName
      "/Applications/MATLAB_R2023a.app/toolbox/eml/eml/+coder/+internal/"
      "validator_check_size.m" // pName
  };
  if ((in.size(0) != 1) || (in.size(1) != 1)) {
    if (in.size(1) != 2) {
      b_rtErrorWithMessageID(static_cast<long>(in.size(1)), qc_emlrtRTEI.fName,
                             qc_emlrtRTEI.lineNo);
    }
    if (in.size(0) == 0) {
      out.set_size(0, 2);
    } else {
      int maxdimlen;
      int nx;
      nx = in.size(0) * in.size(1);
      maxdimlen = in.size(0);
      if (in.size(1) > in.size(0)) {
        maxdimlen = in.size(1);
      }
      if (nx >= maxdimlen) {
        maxdimlen = nx;
      }
      if (in.size(0) > maxdimlen) {
        k_rtErrorWithMessageID(k_emlrtRTEI.fName, k_emlrtRTEI.lineNo);
      }
      if (maxdimlen < 2) {
        k_rtErrorWithMessageID(k_emlrtRTEI.fName, k_emlrtRTEI.lineNo);
      }
      maxdimlen = in.size(0) << 1;
      if (maxdimlen != nx) {
        l_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
      }
      out.set_size(in.size(0), 2);
      for (nx = 0; nx < maxdimlen; nx++) {
        out[nx] = in[nx];
      }
    }
  } else {
    int maxdimlen;
    unsigned int u;
    if (in.size(0) <= 0) {
      u = 0U;
    } else {
      u = static_cast<unsigned int>(in.size(0));
    }
    if ((u << 1) > 2147483647U) {
      m_rtErrorWithMessageID(m_emlrtRTEI.fName, m_emlrtRTEI.lineNo);
    }
    out.set_size(in.size(0), 2);
    maxdimlen = in.size(0) << 1;
    for (int nx{0}; nx < maxdimlen; nx++) {
      out[nx] = in[0];
    }
  }
}

//
// Arguments    : const ::coder::array<c_struct_T, 2U> &in
//                ::coder::array<c_struct_T, 2U> &out
// Return Type  : void
//
void validator_check_size(const ::coder::array<c_struct_T, 2U> &in,
                          ::coder::array<c_struct_T, 2U> &out)
{
  static rtRunTimeErrorInfo qc_emlrtRTEI{
      218,               // lineNo
      32,                // colNo
      "expandOrReshape", // fName
      "/Applications/MATLAB_R2023a.app/toolbox/eml/eml/+coder/+internal/"
      "validator_check_size.m" // pName
  };
  int inVectorLength;
  inVectorLength = 1;
  if (in.size(1) != 1) {
    inVectorLength = in.size(1);
  }
  if (in.size(1) == 1) {
    out.set_size(1, inVectorLength);
    for (int u1{0}; u1 < inVectorLength; u1++) {
      out[u1] = in[0];
    }
  } else if (in.size(1) == 0) {
    if (inVectorLength != 0) {
      n_rtErrorWithMessageID(qc_emlrtRTEI.fName, qc_emlrtRTEI.lineNo);
    }
    out.set_size(1, 0);
  } else {
    int u0;
    int u1;
    u1 = 1;
    if (in.size(1) > 1) {
      u1 = in.size(1);
    }
    u0 = in.size(1);
    if (u0 >= u1) {
      u1 = u0;
    }
    if (inVectorLength > u1) {
      k_rtErrorWithMessageID(k_emlrtRTEI.fName, k_emlrtRTEI.lineNo);
    }
    if (inVectorLength != in.size(1)) {
      l_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
    }
    out.set_size(1, inVectorLength);
    for (u1 = 0; u1 < inVectorLength; u1++) {
      out[u1] = in[u1];
    }
  }
}

} // namespace internal
} // namespace coder

//
// File trailer for validator_check_size.cpp
//
// [EOF]
//
