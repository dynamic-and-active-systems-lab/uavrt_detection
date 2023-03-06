//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: validator_check_size.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 06-Mar-2023 15:57:44
//

// Include Files
#include "validator_check_size.h"
#include "int2str.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_internal_types.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include "omp.h"
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string.h>
#include <string>

// Variable Definitions
static rtRunTimeErrorInfo k_emlrtRTEI{
    143,                   // lineNo
    "validator_check_size" // fName
};

static rtRunTimeErrorInfo l_emlrtRTEI{
    93,                    // lineNo
    "validator_check_size" // fName
};

// Function Declarations
static void j_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void rtErrorWithMessageID(const std::string r, const char *r1,
                                 const char *r2, const char *aFcnName,
                                 int aLineNum);

static void rtErrorWithMessageID(const std::string r, const std::string r1,
                                 const char *r2, const char *aFcnName,
                                 int aLineNum);

// Function Definitions
//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void j_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
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
// Arguments    : const std::string r
//                const char *r1
//                const char *r2
//                const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void rtErrorWithMessageID(const std::string r, const char *r1,
                                 const char *r2, const char *aFcnName,
                                 int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((((((outStream << "Validation size mismatch: input size ") << r)
      << " ~= allowed size ")
     << r1)
    << " for dimension ")
   << r2)
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
// Arguments    : const std::string r
//                const std::string r1
//                const char *r2
//                const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void rtErrorWithMessageID(const std::string r, const std::string r1,
                                 const char *r2, const char *aFcnName,
                                 int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((((((outStream << "Validation size mismatch: input size ") << r)
      << " ~= allowed size ")
     << r1)
    << " for dimension ")
   << r2)
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
// Arguments    : const ::coder::array<c_struct_T, 2U> &in
//                ::coder::array<c_struct_T, 2U> &out
// Return Type  : void
//
namespace coder {
namespace internal {
void b_validator_check_size(const ::coder::array<c_struct_T, 2U> &in,
                            ::coder::array<c_struct_T, 2U> &out)
{
  int sizes_idx_0;
  int sizes_idx_1;
  char b_tmp_data[10];
  char tmp_data[10];
  boolean_T isempty_in;
  boolean_T isscalar_in;
  isscalar_in = ((in.size(0) == 1) && (in.size(1) == 1));
  isempty_in = ((in.size(0) == 0) || (in.size(1) == 0));
  if (isscalar_in) {
    sizes_idx_0 = 1;
    sizes_idx_1 = 1;
  } else {
    sizes_idx_0 = in.size(0);
    sizes_idx_1 = in.size(1);
  }
  if ((!isempty_in) && (!isscalar_in)) {
    int b_tmp_size[2];
    int tmp_size[2];
    if (in.size(0) != sizes_idx_0) {
      int2str(static_cast<double>(in.size(0)), tmp_data, tmp_size);
      int2str(sizes_idx_0, b_tmp_data, b_tmp_size);
      rtErrorWithMessageID(std::string(&tmp_data[0], tmp_size[1]),
                           std::string(&b_tmp_data[0], b_tmp_size[1]), "1",
                           l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
    }
    if (in.size(1) != sizes_idx_1) {
      int2str(static_cast<double>(in.size(1)), tmp_data, tmp_size);
      int2str(sizes_idx_1, b_tmp_data, b_tmp_size);
      rtErrorWithMessageID(std::string(&tmp_data[0], tmp_size[1]),
                           std::string(&b_tmp_data[0], b_tmp_size[1]), "2",
                           l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
    }
  }
  if (isscalar_in) {
    double b_sizes_idx_0;
    int maxdimlen;
    if (sizes_idx_0 <= 0) {
      b_sizes_idx_0 = 0.0;
    } else {
      b_sizes_idx_0 = sizes_idx_0;
    }
    if (sizes_idx_1 <= 0) {
      b_sizes_idx_0 = 0.0;
    } else {
      b_sizes_idx_0 *= static_cast<double>(sizes_idx_1);
    }
    if (!(b_sizes_idx_0 <= 2.147483647E+9)) {
      m_rtErrorWithMessageID(o_emlrtRTEI.fName, o_emlrtRTEI.lineNo);
    }
    out.set_size(sizes_idx_0, sizes_idx_1);
    maxdimlen = sizes_idx_0 * sizes_idx_1;
    for (sizes_idx_0 = 0; sizes_idx_0 < maxdimlen; sizes_idx_0++) {
      out[sizes_idx_0] = in[0];
    }
  } else if (isempty_in) {
    int maxdimlen;
    isscalar_in = (sizes_idx_0 == 0);
    if (isscalar_in || (sizes_idx_1 == 0)) {
      isscalar_in = true;
    }
    if (!isscalar_in) {
      j_rtErrorWithMessageID(k_emlrtRTEI.fName, k_emlrtRTEI.lineNo);
    }
    out.set_size(sizes_idx_0, sizes_idx_1);
    maxdimlen = sizes_idx_0 * sizes_idx_1;
    for (sizes_idx_0 = 0; sizes_idx_0 < maxdimlen; sizes_idx_0++) {
      out[sizes_idx_0] = in[sizes_idx_0];
    }
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
    if (sizes_idx_0 > maxdimlen) {
      k_rtErrorWithMessageID(m_emlrtRTEI.fName, m_emlrtRTEI.lineNo);
    }
    if (sizes_idx_1 > maxdimlen) {
      k_rtErrorWithMessageID(m_emlrtRTEI.fName, m_emlrtRTEI.lineNo);
    }
    maxdimlen = sizes_idx_0 * sizes_idx_1;
    if (maxdimlen != nx) {
      l_rtErrorWithMessageID(n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
    }
    out.set_size(sizes_idx_0, sizes_idx_1);
    for (sizes_idx_0 = 0; sizes_idx_0 < maxdimlen; sizes_idx_0++) {
      out[sizes_idx_0] = in[sizes_idx_0];
    }
  }
}

//
// Arguments    : const ::coder::array<double, 2U> &in
//                ::coder::array<double, 2U> &out
// Return Type  : void
//
void b_validator_check_size(const ::coder::array<double, 2U> &in,
                            ::coder::array<double, 2U> &out)
{
  int loop_ub;
  int maxdimlen;
  int sizes_idx_0;
  int sizes_idx_1;
  char b_tmp_data[10];
  char tmp_data[10];
  char c_tmp_data[3];
  boolean_T isempty_in;
  boolean_T isscalar_in;
  isscalar_in = ((in.size(0) == 1) && (in.size(1) == 1));
  isempty_in = ((in.size(0) == 0) || (in.size(1) == 0));
  if (isscalar_in) {
    sizes_idx_0 = 1;
    sizes_idx_1 = 1;
  } else {
    sizes_idx_0 = in.size(0);
    sizes_idx_1 = in.size(1);
  }
  if ((!isempty_in) && (!isscalar_in)) {
    int tmp_size[2];
    if (in.size(0) != sizes_idx_0) {
      int b_tmp_size[2];
      int2str(static_cast<double>(in.size(0)), tmp_data, tmp_size);
      int2str(sizes_idx_0, b_tmp_data, b_tmp_size);
      rtErrorWithMessageID(std::string(&tmp_data[0], tmp_size[1]),
                           std::string(&b_tmp_data[0], b_tmp_size[1]), "1",
                           l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
    }
    if (in.size(1) != sizes_idx_1) {
      int2str(static_cast<double>(in.size(1)), tmp_data, tmp_size);
      maxdimlen = tmp_size[1];
      loop_ub = tmp_size[1];
      if (loop_ub - 1 >= 0) {
        std::copy(&tmp_data[0], &tmp_data[loop_ub], &c_tmp_data[0]);
      }
      int2str(sizes_idx_1, tmp_data, tmp_size);
      rtErrorWithMessageID(std::string(&c_tmp_data[0], maxdimlen),
                           std::string(&tmp_data[0], tmp_size[1]), "2",
                           l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
    }
  }
  if (isscalar_in) {
    out.set_size(sizes_idx_0, sizes_idx_1);
    loop_ub = sizes_idx_0 * sizes_idx_1;
    for (int nx{0}; nx < loop_ub; nx++) {
      out[nx] = in[0];
    }
  } else if (isempty_in) {
    isscalar_in = (sizes_idx_0 == 0);
    if (isscalar_in || (sizes_idx_1 == 0)) {
      isscalar_in = true;
    }
    if (!isscalar_in) {
      j_rtErrorWithMessageID(k_emlrtRTEI.fName, k_emlrtRTEI.lineNo);
    }
    out.set_size(sizes_idx_0, sizes_idx_1);
    maxdimlen = sizes_idx_0 * sizes_idx_1;
    for (int nx{0}; nx < maxdimlen; nx++) {
      out[nx] = in[nx];
    }
  } else {
    int nx;
    nx = in.size(0) * in.size(1);
    maxdimlen = in.size(0);
    if (in.size(1) > in.size(0)) {
      maxdimlen = 1;
    }
    if (nx >= maxdimlen) {
      maxdimlen = nx;
    }
    if (sizes_idx_0 > maxdimlen) {
      k_rtErrorWithMessageID(m_emlrtRTEI.fName, m_emlrtRTEI.lineNo);
    }
    if (sizes_idx_1 > maxdimlen) {
      k_rtErrorWithMessageID(m_emlrtRTEI.fName, m_emlrtRTEI.lineNo);
    }
    loop_ub = sizes_idx_0 * sizes_idx_1;
    if (loop_ub != nx) {
      l_rtErrorWithMessageID(n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
    }
    out.set_size(sizes_idx_0, sizes_idx_1);
    for (nx = 0; nx < loop_ub; nx++) {
      out[nx] = in[nx];
    }
  }
}

//
// Arguments    : const ::coder::array<boolean_T, 2U> &in
//                ::coder::array<boolean_T, 2U> &out
// Return Type  : void
//
void c_validator_check_size(const ::coder::array<boolean_T, 2U> &in,
                            ::coder::array<boolean_T, 2U> &out)
{
  int sizes_idx_0;
  int sizes_idx_1;
  char b_tmp_data[10];
  char tmp_data[10];
  boolean_T isempty_in;
  boolean_T isscalar_in;
  isscalar_in = ((in.size(0) == 1) && (in.size(1) == 1));
  isempty_in = ((in.size(0) == 0) || (in.size(1) == 0));
  if (isscalar_in) {
    sizes_idx_0 = 1;
    sizes_idx_1 = 1;
  } else {
    sizes_idx_0 = in.size(0);
    sizes_idx_1 = in.size(1);
  }
  if ((!isempty_in) && (!isscalar_in)) {
    int b_tmp_size[2];
    int tmp_size[2];
    if (in.size(0) != sizes_idx_0) {
      int2str(static_cast<double>(in.size(0)), tmp_data, tmp_size);
      int2str(sizes_idx_0, b_tmp_data, b_tmp_size);
      rtErrorWithMessageID(std::string(&tmp_data[0], tmp_size[1]),
                           std::string(&b_tmp_data[0], b_tmp_size[1]), "1",
                           l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
    }
    if (in.size(1) != sizes_idx_1) {
      int2str(static_cast<double>(in.size(1)), tmp_data, tmp_size);
      int2str(sizes_idx_1, b_tmp_data, b_tmp_size);
      rtErrorWithMessageID(std::string(&tmp_data[0], tmp_size[1]),
                           std::string(&b_tmp_data[0], b_tmp_size[1]), "2",
                           l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
    }
  }
  if (isscalar_in) {
    double b_sizes_idx_0;
    int maxdimlen;
    if (sizes_idx_0 <= 0) {
      b_sizes_idx_0 = 0.0;
    } else {
      b_sizes_idx_0 = sizes_idx_0;
    }
    if (sizes_idx_1 <= 0) {
      b_sizes_idx_0 = 0.0;
    } else {
      b_sizes_idx_0 *= static_cast<double>(sizes_idx_1);
    }
    if (!(b_sizes_idx_0 <= 2.147483647E+9)) {
      m_rtErrorWithMessageID(o_emlrtRTEI.fName, o_emlrtRTEI.lineNo);
    }
    out.set_size(sizes_idx_0, sizes_idx_1);
    maxdimlen = sizes_idx_0 * sizes_idx_1;
    for (sizes_idx_0 = 0; sizes_idx_0 < maxdimlen; sizes_idx_0++) {
      out[sizes_idx_0] = in[0];
    }
  } else if (isempty_in) {
    int maxdimlen;
    isscalar_in = (sizes_idx_0 == 0);
    if (isscalar_in || (sizes_idx_1 == 0)) {
      isscalar_in = true;
    }
    if (!isscalar_in) {
      j_rtErrorWithMessageID(k_emlrtRTEI.fName, k_emlrtRTEI.lineNo);
    }
    out.set_size(sizes_idx_0, sizes_idx_1);
    maxdimlen = sizes_idx_0 * sizes_idx_1;
    for (sizes_idx_0 = 0; sizes_idx_0 < maxdimlen; sizes_idx_0++) {
      out[sizes_idx_0] = in[sizes_idx_0];
    }
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
    if (sizes_idx_0 > maxdimlen) {
      k_rtErrorWithMessageID(m_emlrtRTEI.fName, m_emlrtRTEI.lineNo);
    }
    if (sizes_idx_1 > maxdimlen) {
      k_rtErrorWithMessageID(m_emlrtRTEI.fName, m_emlrtRTEI.lineNo);
    }
    maxdimlen = sizes_idx_0 * sizes_idx_1;
    if (maxdimlen != nx) {
      l_rtErrorWithMessageID(n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
    }
    out.set_size(sizes_idx_0, sizes_idx_1);
    for (sizes_idx_0 = 0; sizes_idx_0 < maxdimlen; sizes_idx_0++) {
      out[sizes_idx_0] = in[sizes_idx_0];
    }
  }
}

//
// Arguments    : const ::coder::array<double, 2U> &in
//                ::coder::array<double, 2U> &out
// Return Type  : void
//
void validator_check_size(const ::coder::array<double, 2U> &in,
                          ::coder::array<double, 2U> &out)
{
  int sizes_idx_0;
  char b_tmp_data[10];
  char tmp_data[10];
  boolean_T b;
  boolean_T hasMismatchingDims;
  boolean_T isscalar_in;
  isscalar_in = ((in.size(0) == 1) && (in.size(1) == 1));
  b = (in.size(0) == 0);
  hasMismatchingDims = false;
  if (b) {
    hasMismatchingDims = (in.size(1) != 2);
  }
  if (isscalar_in) {
    sizes_idx_0 = 1;
  } else if (b && hasMismatchingDims) {
    sizes_idx_0 = 0;
  } else {
    sizes_idx_0 = in.size(0);
  }
  if ((!b) && (!isscalar_in)) {
    int tmp_size[2];
    if (in.size(0) != sizes_idx_0) {
      int b_tmp_size[2];
      int2str(static_cast<double>(in.size(0)), tmp_data, tmp_size);
      int2str(sizes_idx_0, b_tmp_data, b_tmp_size);
      rtErrorWithMessageID(std::string(&tmp_data[0], tmp_size[1]),
                           std::string(&b_tmp_data[0], b_tmp_size[1]), "1",
                           l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
    }
    if (in.size(1) != 2) {
      int2str(static_cast<double>(in.size(1)), tmp_data, tmp_size);
      rtErrorWithMessageID(std::string(&tmp_data[0], tmp_size[1]), "2", "2",
                           l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
    }
  }
  if (isscalar_in) {
    unsigned int b_sizes_idx_0;
    int maxdimlen;
    if (sizes_idx_0 <= 0) {
      b_sizes_idx_0 = 0U;
    } else {
      b_sizes_idx_0 = static_cast<unsigned int>(sizes_idx_0);
    }
    if ((b_sizes_idx_0 << 1) > 2147483647U) {
      m_rtErrorWithMessageID(o_emlrtRTEI.fName, o_emlrtRTEI.lineNo);
    }
    out.set_size(sizes_idx_0, 2);
    maxdimlen = sizes_idx_0 << 1;
    for (sizes_idx_0 = 0; sizes_idx_0 < maxdimlen; sizes_idx_0++) {
      out[sizes_idx_0] = in[0];
    }
  } else if (b) {
    if (sizes_idx_0 != 0) {
      j_rtErrorWithMessageID(k_emlrtRTEI.fName, k_emlrtRTEI.lineNo);
    }
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
    if (sizes_idx_0 > maxdimlen) {
      k_rtErrorWithMessageID(m_emlrtRTEI.fName, m_emlrtRTEI.lineNo);
    }
    if (maxdimlen < 2) {
      k_rtErrorWithMessageID(m_emlrtRTEI.fName, m_emlrtRTEI.lineNo);
    }
    maxdimlen = sizes_idx_0 << 1;
    if (maxdimlen != nx) {
      l_rtErrorWithMessageID(n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
    }
    out.set_size(sizes_idx_0, 2);
    for (sizes_idx_0 = 0; sizes_idx_0 < maxdimlen; sizes_idx_0++) {
      out[sizes_idx_0] = in[sizes_idx_0];
    }
  }
}

//
// Arguments    : const ::coder::array<creal32_T, 2U> &in
//                ::coder::array<creal32_T, 2U> &out
// Return Type  : void
//
void validator_check_size(const ::coder::array<creal32_T, 2U> &in,
                          ::coder::array<creal32_T, 2U> &out)
{
  int sizes_idx_1;
  char b_tmp_data[10];
  char tmp_data[10];
  boolean_T b;
  boolean_T b1;
  b = (in.size(1) == 1);
  b1 = (in.size(1) == 0);
  if (b) {
    sizes_idx_1 = 1;
  } else {
    sizes_idx_1 = in.size(1);
  }
  if ((!b1) && (!b) && (in.size(1) != sizes_idx_1)) {
    int b_tmp_size[2];
    int tmp_size[2];
    int2str(static_cast<double>(in.size(1)), tmp_data, tmp_size);
    int2str(sizes_idx_1, b_tmp_data, b_tmp_size);
    rtErrorWithMessageID(std::string(&tmp_data[0], tmp_size[1]),
                         std::string(&b_tmp_data[0], b_tmp_size[1]), "2",
                         l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
  }
  if (b) {
    out.set_size(1, sizes_idx_1);
    for (int u1{0}; u1 < sizes_idx_1; u1++) {
      out[u1] = in[0];
    }
  } else if (b1) {
    if (sizes_idx_1 != 0) {
      j_rtErrorWithMessageID(k_emlrtRTEI.fName, k_emlrtRTEI.lineNo);
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
    if (sizes_idx_1 > u1) {
      k_rtErrorWithMessageID(m_emlrtRTEI.fName, m_emlrtRTEI.lineNo);
    }
    if (sizes_idx_1 != in.size(1)) {
      l_rtErrorWithMessageID(n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
    }
    out.set_size(1, sizes_idx_1);
    for (u1 = 0; u1 < sizes_idx_1; u1++) {
      out[u1] = in[u1];
    }
  }
}

//
// Arguments    : const ::coder::array<creal_T, 2U> &in
//                ::coder::array<creal_T, 2U> &out
// Return Type  : void
//
void validator_check_size(const ::coder::array<creal_T, 2U> &in,
                          ::coder::array<creal_T, 2U> &out)
{
  int sizes_idx_0;
  int sizes_idx_1;
  char b_tmp_data[10];
  char tmp_data[10];
  boolean_T isempty_in;
  boolean_T isscalar_in;
  isscalar_in = ((in.size(0) == 1) && (in.size(1) == 1));
  isempty_in = ((in.size(0) == 0) || (in.size(1) == 0));
  if (isscalar_in) {
    sizes_idx_0 = 1;
    sizes_idx_1 = 1;
  } else {
    sizes_idx_0 = in.size(0);
    sizes_idx_1 = in.size(1);
  }
  if ((!isempty_in) && (!isscalar_in)) {
    int b_tmp_size[2];
    int tmp_size[2];
    if (in.size(0) != sizes_idx_0) {
      int2str(static_cast<double>(in.size(0)), tmp_data, tmp_size);
      int2str(sizes_idx_0, b_tmp_data, b_tmp_size);
      rtErrorWithMessageID(std::string(&tmp_data[0], tmp_size[1]),
                           std::string(&b_tmp_data[0], b_tmp_size[1]), "1",
                           l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
    }
    if (in.size(1) != sizes_idx_1) {
      int2str(static_cast<double>(in.size(1)), tmp_data, tmp_size);
      int2str(sizes_idx_1, b_tmp_data, b_tmp_size);
      rtErrorWithMessageID(std::string(&tmp_data[0], tmp_size[1]),
                           std::string(&b_tmp_data[0], b_tmp_size[1]), "2",
                           l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
    }
  }
  if (isscalar_in) {
    double b_sizes_idx_0;
    int maxdimlen;
    if (sizes_idx_0 <= 0) {
      b_sizes_idx_0 = 0.0;
    } else {
      b_sizes_idx_0 = sizes_idx_0;
    }
    if (sizes_idx_1 <= 0) {
      b_sizes_idx_0 = 0.0;
    } else {
      b_sizes_idx_0 *= static_cast<double>(sizes_idx_1);
    }
    if (!(b_sizes_idx_0 <= 2.147483647E+9)) {
      m_rtErrorWithMessageID(o_emlrtRTEI.fName, o_emlrtRTEI.lineNo);
    }
    out.set_size(sizes_idx_0, sizes_idx_1);
    maxdimlen = sizes_idx_0 * sizes_idx_1;
    for (sizes_idx_0 = 0; sizes_idx_0 < maxdimlen; sizes_idx_0++) {
      out[sizes_idx_0] = in[0];
    }
  } else if (isempty_in) {
    int maxdimlen;
    isscalar_in = (sizes_idx_0 == 0);
    if (isscalar_in || (sizes_idx_1 == 0)) {
      isscalar_in = true;
    }
    if (!isscalar_in) {
      j_rtErrorWithMessageID(k_emlrtRTEI.fName, k_emlrtRTEI.lineNo);
    }
    out.set_size(sizes_idx_0, sizes_idx_1);
    maxdimlen = sizes_idx_0 * sizes_idx_1;
    for (sizes_idx_0 = 0; sizes_idx_0 < maxdimlen; sizes_idx_0++) {
      out[sizes_idx_0] = in[sizes_idx_0];
    }
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
    if (sizes_idx_0 > maxdimlen) {
      k_rtErrorWithMessageID(m_emlrtRTEI.fName, m_emlrtRTEI.lineNo);
    }
    if (sizes_idx_1 > maxdimlen) {
      k_rtErrorWithMessageID(m_emlrtRTEI.fName, m_emlrtRTEI.lineNo);
    }
    maxdimlen = sizes_idx_0 * sizes_idx_1;
    if (maxdimlen != nx) {
      l_rtErrorWithMessageID(n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
    }
    out.set_size(sizes_idx_0, sizes_idx_1);
    for (sizes_idx_0 = 0; sizes_idx_0 < maxdimlen; sizes_idx_0++) {
      out[sizes_idx_0] = in[sizes_idx_0];
    }
  }
}

//
// Arguments    : const ::coder::array<double, 1U> &in
//                ::coder::array<double, 1U> &out
// Return Type  : void
//
void validator_check_size(const ::coder::array<double, 1U> &in,
                          ::coder::array<double, 1U> &out)
{
  int sizes_idx_0;
  char b_tmp_data[10];
  char tmp_data[10];
  boolean_T isempty_in;
  boolean_T isscalar_in;
  isscalar_in = (in.size(0) == 1);
  isempty_in = (in.size(0) == 0);
  if (isscalar_in) {
    sizes_idx_0 = 1;
  } else {
    sizes_idx_0 = in.size(0);
  }
  if ((!isempty_in) && (!isscalar_in) && (in.size(0) != sizes_idx_0)) {
    int b_tmp_size[2];
    int tmp_size[2];
    int2str(static_cast<double>(in.size(0)), tmp_data, tmp_size);
    int2str(sizes_idx_0, b_tmp_data, b_tmp_size);
    rtErrorWithMessageID(std::string(&tmp_data[0], tmp_size[1]),
                         std::string(&b_tmp_data[0], b_tmp_size[1]), "1",
                         l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
  }
  if (isscalar_in) {
    out.set_size(sizes_idx_0);
    for (int n{0}; n < sizes_idx_0; n++) {
      out[n] = in[0];
    }
  } else if (isempty_in) {
    if (sizes_idx_0 != 0) {
      j_rtErrorWithMessageID(k_emlrtRTEI.fName, k_emlrtRTEI.lineNo);
    }
    out.set_size(0);
  } else {
    int n;
    int u0;
    n = in.size(0);
    if (in.size(0) < 1) {
      n = 1;
    }
    u0 = in.size(0);
    if (u0 >= n) {
      n = u0;
    }
    if (sizes_idx_0 > n) {
      k_rtErrorWithMessageID(m_emlrtRTEI.fName, m_emlrtRTEI.lineNo);
    }
    if (sizes_idx_0 != in.size(0)) {
      l_rtErrorWithMessageID(n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
    }
    out.set_size(sizes_idx_0);
    for (n = 0; n < sizes_idx_0; n++) {
      out[n] = in[n];
    }
  }
}

//
// Arguments    : const ::coder::array<double, 1U> &in
//                ::coder::array<double, 2U> &out
// Return Type  : void
//
void validator_check_size(const ::coder::array<double, 1U> &in,
                          ::coder::array<double, 2U> &out)
{
  int sizes_idx_0;
  char b_tmp_data[10];
  char tmp_data[10];
  boolean_T isempty_in;
  boolean_T isscalar_in;
  isscalar_in = (in.size(0) == 1);
  isempty_in = (in.size(0) == 0);
  if (isscalar_in) {
    sizes_idx_0 = 1;
  } else {
    sizes_idx_0 = in.size(0);
  }
  if ((!isempty_in) && (!isscalar_in) && (in.size(0) != sizes_idx_0)) {
    int b_tmp_size[2];
    int tmp_size[2];
    int2str(static_cast<double>(in.size(0)), tmp_data, tmp_size);
    int2str(sizes_idx_0, b_tmp_data, b_tmp_size);
    rtErrorWithMessageID(std::string(&tmp_data[0], tmp_size[1]),
                         std::string(&b_tmp_data[0], b_tmp_size[1]), "1",
                         l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
  }
  if (isscalar_in) {
    out.set_size(sizes_idx_0, 1);
    for (int n{0}; n < sizes_idx_0; n++) {
      out[n] = in[0];
    }
  } else if (isempty_in) {
    if (sizes_idx_0 != 0) {
      j_rtErrorWithMessageID(k_emlrtRTEI.fName, k_emlrtRTEI.lineNo);
    }
    out.set_size(0, 1);
  } else {
    int n;
    int u0;
    n = in.size(0);
    if (in.size(0) < 1) {
      n = 1;
    }
    u0 = in.size(0);
    if (u0 >= n) {
      n = u0;
    }
    if (sizes_idx_0 > n) {
      k_rtErrorWithMessageID(m_emlrtRTEI.fName, m_emlrtRTEI.lineNo);
    }
    if (sizes_idx_0 != in.size(0)) {
      l_rtErrorWithMessageID(n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
    }
    out.set_size(sizes_idx_0, 1);
    for (n = 0; n < sizes_idx_0; n++) {
      out[n] = in[n];
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
  int sizes_idx_1;
  char b_tmp_data[10];
  char tmp_data[10];
  boolean_T b;
  boolean_T b1;
  b = (in.size(1) == 1);
  b1 = (in.size(1) == 0);
  if (b) {
    sizes_idx_1 = 1;
  } else {
    sizes_idx_1 = in.size(1);
  }
  if ((!b1) && (!b) && (in.size(1) != sizes_idx_1)) {
    int b_tmp_size[2];
    int tmp_size[2];
    int2str(static_cast<double>(in.size(1)), tmp_data, tmp_size);
    int2str(sizes_idx_1, b_tmp_data, b_tmp_size);
    rtErrorWithMessageID(std::string(&tmp_data[0], tmp_size[1]),
                         std::string(&b_tmp_data[0], b_tmp_size[1]), "2",
                         l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
  }
  if (b) {
    out.set_size(1, sizes_idx_1);
    for (int u1{0}; u1 < sizes_idx_1; u1++) {
      out[u1] = in[0];
    }
  } else if (b1) {
    if (sizes_idx_1 != 0) {
      j_rtErrorWithMessageID(k_emlrtRTEI.fName, k_emlrtRTEI.lineNo);
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
    if (sizes_idx_1 > u1) {
      k_rtErrorWithMessageID(m_emlrtRTEI.fName, m_emlrtRTEI.lineNo);
    }
    if (sizes_idx_1 != in.size(1)) {
      l_rtErrorWithMessageID(n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
    }
    out.set_size(1, sizes_idx_1);
    for (u1 = 0; u1 < sizes_idx_1; u1++) {
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
