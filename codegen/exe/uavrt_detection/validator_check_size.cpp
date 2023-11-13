//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: validator_check_size.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 13-Nov-2023 11:57:04
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

static void o_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void p_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

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
static void o_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Value must be a vector.";
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
static void p_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
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
// Arguments    : const array<double, 2U> &in
//                array<double, 2U> &out
// Return Type  : void
//
namespace coder {
namespace internal {
void validator_check_size(const array<double, 2U> &in, array<double, 2U> &out)
{
  static rtRunTimeErrorInfo yc_emlrtRTEI{
      164,               // lineNo
      31,                // colNo
      "expandOrReshape", // fName
      "/Applications/MATLAB_R2023b.app/toolbox/eml/eml/+coder/+internal/"
      "validator_check_size.m" // pName
  };
  if ((in.size(0) != 1) || (in.size(1) != 1)) {
    if (in.size(1) != 2) {
      b_rtErrorWithMessageID(static_cast<long>(in.size(1)), yc_emlrtRTEI.fName,
                             yc_emlrtRTEI.lineNo);
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
        k_rtErrorWithMessageID(n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
      }
      if (maxdimlen < 2) {
        k_rtErrorWithMessageID(n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
      }
      maxdimlen = in.size(0) << 1;
      if (maxdimlen != nx) {
        l_rtErrorWithMessageID(o_emlrtRTEI.fName, o_emlrtRTEI.lineNo);
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
      m_rtErrorWithMessageID(p_emlrtRTEI.fName, p_emlrtRTEI.lineNo);
    }
    out.set_size(in.size(0), 2);
    maxdimlen = in.size(0) << 1;
    for (int nx{0}; nx < maxdimlen; nx++) {
      out[nx] = in[0];
    }
  }
}

//
// Arguments    : const array<c_struct_T, 2U> &in
//                array<c_struct_T, 2U> &out
// Return Type  : void
//
void validator_check_size(const array<c_struct_T, 2U> &in,
                          array<c_struct_T, 2U> &out)
{
  static rtRunTimeErrorInfo ad_emlrtRTEI{
      219,               // lineNo
      32,                // colNo
      "expandOrReshape", // fName
      "/Applications/MATLAB_R2023b.app/toolbox/eml/eml/+coder/+internal/"
      "validator_check_size.m" // pName
  };
  static rtRunTimeErrorInfo yc_emlrtRTEI{
      277,                                          // lineNo
      5,                                            // colNo
      "getExclusiveNonSingletonDimSizeOr1IfScalar", // fName
      "/Applications/MATLAB_R2023b.app/toolbox/eml/eml/+coder/+internal/"
      "validator_check_size.m" // pName
  };
  int inVectorLength;
  boolean_T hitNotSingletonDim;
  boolean_T isequal_the_empty_in;
  boolean_T szNot1;
  if ((in.size(0) == 0) && (in.size(1) == 0)) {
    isequal_the_empty_in = true;
  } else {
    isequal_the_empty_in = false;
  }
  if (((in.size(0) != 1) || (in.size(1) != 1)) && (!isequal_the_empty_in)) {
    isequal_the_empty_in = true;
  } else {
    isequal_the_empty_in = false;
  }
  inVectorLength = 1;
  if (in.size(0) != 1) {
    hitNotSingletonDim = true;
    inVectorLength = in.size(0);
  } else {
    hitNotSingletonDim = false;
  }
  szNot1 = (in.size(1) != 1);
  if (isequal_the_empty_in && hitNotSingletonDim && szNot1) {
    o_rtErrorWithMessageID(yc_emlrtRTEI.fName, yc_emlrtRTEI.lineNo);
  }
  if (szNot1) {
    inVectorLength = in.size(1);
  }
  if ((in.size(0) == 0) || (in.size(1) == 0)) {
    if (inVectorLength != 0) {
      p_rtErrorWithMessageID(ad_emlrtRTEI.fName, ad_emlrtRTEI.lineNo);
    }
    out.set_size(1, 0);
  } else {
    int n;
    int nx;
    nx = in.size(0) * in.size(1);
    n = in.size(0);
    if (in.size(1) > in.size(0)) {
      n = in.size(1);
    }
    if (nx >= n) {
      n = nx;
    }
    if (inVectorLength > n) {
      k_rtErrorWithMessageID(n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
    }
    if (inVectorLength != nx) {
      l_rtErrorWithMessageID(o_emlrtRTEI.fName, o_emlrtRTEI.lineNo);
    }
    out.set_size(1, inVectorLength);
    for (nx = 0; nx < inVectorLength; nx++) {
      out[nx] = in[nx];
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
