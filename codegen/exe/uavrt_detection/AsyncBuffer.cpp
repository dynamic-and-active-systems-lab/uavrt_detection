//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: AsyncBuffer.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 21-Feb-2023 09:24:56
//

// Include Files
#include "AsyncBuffer.h"
#include "AsyncBuffercgHelper.h"
#include "colon.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_internal_types.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include "omp.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <stdexcept>
#include <string.h>
#include <string>

// Variable Definitions
static rtRunTimeErrorInfo s_emlrtRTEI{
    1,                 // lineNo
    "SystemCore/reset" // fName
};

static rtRunTimeErrorInfo t_emlrtRTEI{
    101,                                     // lineNo
    "AsyncBuffercgHelper/validateInputsImpl" // fName
};

static rtRunTimeErrorInfo rb_emlrtRTEI{
    1,                 // lineNo
    "SystemCore/setup" // fName
};

static rtRunTimeErrorInfo sb_emlrtRTEI{
    1,                // lineNo
    "SystemCore/step" // fName
};

static rtRunTimeErrorInfo ub_emlrtRTEI{
    109,                 // lineNo
    "AsyncBuffercg/read" // fName
};

// Function Declarations
static void c_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum);

static void d_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum);

static void db_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void n_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
namespace coder {
namespace dsp {
void c_AsyncBuffer::matlabCodegenDestructor()
{
  if (!matlabCodegenIsDeleted) {
    matlabCodegenIsDeleted = true;
  }
}

//
// Arguments    : void
// Return Type  : void
//
void b_AsyncBuffer::matlabCodegenDestructor()
{
  if (!matlabCodegenIsDeleted) {
    matlabCodegenIsDeleted = true;
  }
}

//
// Arguments    : void
// Return Type  : void
//
void AsyncBuffer::matlabCodegenDestructor()
{
  if (!matlabCodegenIsDeleted) {
    matlabCodegenIsDeleted = true;
  }
}

//
// Arguments    : const char *r
//                const char *aFcnName
//                int aLineNum
// Return Type  : void
//
} // namespace dsp
} // namespace coder
static void c_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((outStream << "The ") << r)
      << " method cannot be called after calling the release method.";
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
// Arguments    : const char *r
//                const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void d_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((outStream << "The ") << r)
      << " method cannot be called on an initialized System object or after "
         "calling the release method.";
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
static void db_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Invalid overlap requested. Specify overlap as less than or "
               "equal to the requested number of rows.";
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
  outStream << "The number of channels (number of columns) of the input signal "
               "cannot change.";
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
// Arguments    : void
// Return Type  : c_AsyncBuffer
//
namespace coder {
namespace dsp {
c_AsyncBuffer::c_AsyncBuffer()
{
  matlabCodegenIsDeleted = true;
}

//
// Arguments    : void
// Return Type  : b_AsyncBuffer
//
b_AsyncBuffer::b_AsyncBuffer()
{
  matlabCodegenIsDeleted = true;
}

//
// Arguments    : void
// Return Type  : AsyncBuffer
//
AsyncBuffer::AsyncBuffer()
{
  matlabCodegenIsDeleted = true;
}

//
// Arguments    : void
// Return Type  : void
//
c_AsyncBuffer::~c_AsyncBuffer()
{
  matlabCodegenDestructor();
}

//
// Arguments    : void
// Return Type  : void
//
b_AsyncBuffer::~b_AsyncBuffer()
{
  matlabCodegenDestructor();
}

//
// Arguments    : void
// Return Type  : void
//
AsyncBuffer::~AsyncBuffer()
{
  matlabCodegenDestructor();
}

//
// Arguments    : void
// Return Type  : void
//
void c_AsyncBuffer::read()
{
  array<creal32_T, 1U> out;
  int numRows;
  int q0_tmp;
  int qY;
  q0_tmp = pBuffer.WritePointer;
  numRows = pBuffer.ReadPointer;
  if ((q0_tmp >= 0) && (numRows < q0_tmp - MAX_int32_T)) {
    qY = MAX_int32_T;
  } else if ((q0_tmp < 0) && (numRows > q0_tmp - MIN_int32_T)) {
    qY = MIN_int32_T;
  } else {
    qY = q0_tmp - numRows;
  }
  if (qY < -2147483647) {
    qY = MIN_int32_T;
  } else {
    qY--;
  }
  if (numRows < -2146882997) {
    numRows = MAX_int32_T;
  } else {
    numRows = 600650 - numRows;
  }
  if ((numRows < 0) && (q0_tmp < MIN_int32_T - numRows)) {
    numRows = MIN_int32_T;
  } else if ((numRows > 0) && (q0_tmp > MAX_int32_T - numRows)) {
    numRows = MAX_int32_T;
  } else {
    numRows += q0_tmp;
  }
  if (pBuffer.ReadPointer < pBuffer.WritePointer) {
    numRows = qY;
  } else if (pBuffer.ReadPointer == pBuffer.WritePointer) {
    numRows = 600650;
  }
  if (numRows < 0) {
    e_rtErrorWithMessageID("number of rows", v_emlrtRTEI.fName,
                           v_emlrtRTEI.lineNo);
  }
  if (numRows > 600650) {
    o_rtErrorWithMessageID(u_emlrtRTEI.fName, u_emlrtRTEI.lineNo);
  }
  pBuffer.read(numRows, out, &q0_tmp);
}

//
// Arguments    : ::coder::array<creal32_T, 1U> &out
// Return Type  : void
//
void c_AsyncBuffer::read(::coder::array<creal32_T, 1U> &out)
{
  int numRows;
  int q0_tmp;
  int qY;
  q0_tmp = pBuffer.WritePointer;
  numRows = pBuffer.ReadPointer;
  if ((q0_tmp >= 0) && (numRows < q0_tmp - MAX_int32_T)) {
    qY = MAX_int32_T;
  } else if ((q0_tmp < 0) && (numRows > q0_tmp - MIN_int32_T)) {
    qY = MIN_int32_T;
  } else {
    qY = q0_tmp - numRows;
  }
  if (qY < -2147483647) {
    qY = MIN_int32_T;
  } else {
    qY--;
  }
  if (numRows < -2146882997) {
    numRows = MAX_int32_T;
  } else {
    numRows = 600650 - numRows;
  }
  if ((numRows < 0) && (q0_tmp < MIN_int32_T - numRows)) {
    numRows = MIN_int32_T;
  } else if ((numRows > 0) && (q0_tmp > MAX_int32_T - numRows)) {
    numRows = MAX_int32_T;
  } else {
    numRows += q0_tmp;
  }
  if (pBuffer.ReadPointer < pBuffer.WritePointer) {
    numRows = qY;
  } else if (pBuffer.ReadPointer == pBuffer.WritePointer) {
    numRows = 600650;
  }
  if (numRows < 0) {
    e_rtErrorWithMessageID("number of rows", v_emlrtRTEI.fName,
                           v_emlrtRTEI.lineNo);
  }
  if (numRows > 600650) {
    o_rtErrorWithMessageID(u_emlrtRTEI.fName, u_emlrtRTEI.lineNo);
  }
  pBuffer.read(numRows, out, &q0_tmp);
}

//
// Arguments    : double numRows
//                ::coder::array<creal32_T, 1U> &out
// Return Type  : void
//
void AsyncBuffer::read(double numRows, ::coder::array<creal32_T, 1U> &out)
{
  int underrun;
  if (numRows < 0.0) {
    e_rtErrorWithMessageID("number of rows", v_emlrtRTEI.fName,
                           v_emlrtRTEI.lineNo);
  }
  if (std::isinf(numRows) || std::isnan(numRows)) {
    g_rtErrorWithMessageID("number of rows", db_emlrtRTEI.fName,
                           db_emlrtRTEI.lineNo);
  }
  if (!(std::floor(numRows) == numRows)) {
    j_rtErrorWithMessageID("number of rows", gb_emlrtRTEI.fName,
                           gb_emlrtRTEI.lineNo);
  }
  if (numRows > 5.80032E+6) {
    o_rtErrorWithMessageID(u_emlrtRTEI.fName, u_emlrtRTEI.lineNo);
  }
  pBuffer.read(static_cast<int>(numRows), out, &underrun);
}

//
// Arguments    : double numRows
//                ::coder::array<double, 1U> &out
// Return Type  : void
//
void b_AsyncBuffer::read(double numRows, ::coder::array<double, 1U> &out)
{
  int underrun;
  if (numRows < 0.0) {
    e_rtErrorWithMessageID("number of rows", v_emlrtRTEI.fName,
                           v_emlrtRTEI.lineNo);
  }
  if (std::isinf(numRows) || std::isnan(numRows)) {
    g_rtErrorWithMessageID("number of rows", db_emlrtRTEI.fName,
                           db_emlrtRTEI.lineNo);
  }
  if (!(std::floor(numRows) == numRows)) {
    j_rtErrorWithMessageID("number of rows", gb_emlrtRTEI.fName,
                           gb_emlrtRTEI.lineNo);
  }
  if (numRows > 5.80032E+6) {
    o_rtErrorWithMessageID(u_emlrtRTEI.fName, u_emlrtRTEI.lineNo);
  }
  pBuffer.read(static_cast<int>(numRows), out, &underrun);
}

//
// Arguments    : double numRows
//                double overlap
//                ::coder::array<creal32_T, 1U> &out
// Return Type  : void
//
void AsyncBuffer::read(double numRows, double overlap,
                       ::coder::array<creal32_T, 1U> &out)
{
  array<creal32_T, 1U> b_out;
  int c;
  int overlapUnderrun;
  int qY;
  int underrun;
  if (numRows < 0.0) {
    e_rtErrorWithMessageID("number of rows", v_emlrtRTEI.fName,
                           v_emlrtRTEI.lineNo);
  }
  if (std::isinf(numRows) || std::isnan(numRows)) {
    g_rtErrorWithMessageID("number of rows", db_emlrtRTEI.fName,
                           db_emlrtRTEI.lineNo);
  }
  if (!(std::floor(numRows) == numRows)) {
    j_rtErrorWithMessageID("number of rows", gb_emlrtRTEI.fName,
                           gb_emlrtRTEI.lineNo);
  }
  if (numRows > 5.80032E+6) {
    o_rtErrorWithMessageID(u_emlrtRTEI.fName, u_emlrtRTEI.lineNo);
  }
  if (overlap < 0.0) {
    e_rtErrorWithMessageID("overlap", v_emlrtRTEI.fName, v_emlrtRTEI.lineNo);
  }
  if (std::isinf(overlap) || std::isnan(overlap)) {
    g_rtErrorWithMessageID("overlap", db_emlrtRTEI.fName, db_emlrtRTEI.lineNo);
  }
  if (!(std::floor(overlap) == overlap)) {
    j_rtErrorWithMessageID("overlap", gb_emlrtRTEI.fName, gb_emlrtRTEI.lineNo);
  }
  if (overlap > numRows) {
    db_rtErrorWithMessageID(ub_emlrtRTEI.fName, ub_emlrtRTEI.lineNo);
  }
  if (!pBuffer.AsyncBuffercgHelper_isInitialized) {
    p_rtErrorWithMessageID(w_emlrtRTEI.fName, w_emlrtRTEI.lineNo);
  }
  internal::AsyncBuffercgHelper::ReadSamplesFromBuffer(
      &pBuffer, static_cast<int>(numRows), static_cast<int>(overlap), b_out,
      &underrun, &overlapUnderrun, &c);
  out.set_size(b_out.size(0));
  overlapUnderrun = b_out.size(0);
  for (qY = 0; qY < overlapUnderrun; qY++) {
    out[qY] = b_out[qY];
  }
  overlapUnderrun = pBuffer.WritePointer;
  if (overlapUnderrun < -2147483647) {
    qY = MIN_int32_T;
  } else {
    qY = overlapUnderrun - 1;
  }
  overlapUnderrun = pBuffer.CumulativeUnderrun;
  if ((overlapUnderrun < 0) && (underrun < MIN_int32_T - overlapUnderrun)) {
    overlapUnderrun = MIN_int32_T;
  } else if ((overlapUnderrun > 0) &&
             (underrun > MAX_int32_T - overlapUnderrun)) {
    overlapUnderrun = MAX_int32_T;
  } else {
    overlapUnderrun += underrun;
  }
  pBuffer.CumulativeUnderrun = overlapUnderrun;
  if (underrun != 0) {
    pBuffer.ReadPointer = qY;
  } else {
    pBuffer.ReadPointer = c;
  }
}

//
// Arguments    : double numRows
//                double overlap
//                ::coder::array<double, 1U> &out
// Return Type  : void
//
void b_AsyncBuffer::read(double numRows, double overlap,
                         ::coder::array<double, 1U> &out)
{
  array<double, 1U> b_out;
  int c;
  int overlapUnderrun;
  int qY;
  int underrun;
  if (numRows < 0.0) {
    e_rtErrorWithMessageID("number of rows", v_emlrtRTEI.fName,
                           v_emlrtRTEI.lineNo);
  }
  if (std::isinf(numRows) || std::isnan(numRows)) {
    g_rtErrorWithMessageID("number of rows", db_emlrtRTEI.fName,
                           db_emlrtRTEI.lineNo);
  }
  if (!(std::floor(numRows) == numRows)) {
    j_rtErrorWithMessageID("number of rows", gb_emlrtRTEI.fName,
                           gb_emlrtRTEI.lineNo);
  }
  if (numRows > 5.80032E+6) {
    o_rtErrorWithMessageID(u_emlrtRTEI.fName, u_emlrtRTEI.lineNo);
  }
  if (overlap < 0.0) {
    e_rtErrorWithMessageID("overlap", v_emlrtRTEI.fName, v_emlrtRTEI.lineNo);
  }
  if (std::isinf(overlap) || std::isnan(overlap)) {
    g_rtErrorWithMessageID("overlap", db_emlrtRTEI.fName, db_emlrtRTEI.lineNo);
  }
  if (!(std::floor(overlap) == overlap)) {
    j_rtErrorWithMessageID("overlap", gb_emlrtRTEI.fName, gb_emlrtRTEI.lineNo);
  }
  if (overlap > numRows) {
    db_rtErrorWithMessageID(ub_emlrtRTEI.fName, ub_emlrtRTEI.lineNo);
  }
  if (!pBuffer.AsyncBuffercgHelper_isInitialized) {
    p_rtErrorWithMessageID(w_emlrtRTEI.fName, w_emlrtRTEI.lineNo);
  }
  internal::b_AsyncBuffercgHelper::ReadSamplesFromBuffer(
      &pBuffer, static_cast<int>(numRows), static_cast<int>(overlap), b_out,
      &underrun, &overlapUnderrun, &c);
  out.set_size(b_out.size(0));
  overlapUnderrun = b_out.size(0);
  for (qY = 0; qY < overlapUnderrun; qY++) {
    out[qY] = b_out[qY];
  }
  overlapUnderrun = pBuffer.WritePointer;
  if (overlapUnderrun < -2147483647) {
    qY = MIN_int32_T;
  } else {
    qY = overlapUnderrun - 1;
  }
  overlapUnderrun = pBuffer.CumulativeUnderrun;
  if ((overlapUnderrun < 0) && (underrun < MIN_int32_T - overlapUnderrun)) {
    overlapUnderrun = MIN_int32_T;
  } else if ((overlapUnderrun > 0) &&
             (underrun > MAX_int32_T - overlapUnderrun)) {
    overlapUnderrun = MAX_int32_T;
  } else {
    overlapUnderrun += underrun;
  }
  pBuffer.CumulativeUnderrun = overlapUnderrun;
  if (underrun != 0) {
    pBuffer.ReadPointer = qY;
  } else {
    pBuffer.ReadPointer = c;
  }
}

//
// Arguments    : void
// Return Type  : void
//
void AsyncBuffer::reset()
{
  if (pBuffer.isInitialized == 2) {
    c_rtErrorWithMessageID("reset", s_emlrtRTEI.fName, s_emlrtRTEI.lineNo);
  }
  if (pBuffer.isInitialized == 1) {
    pBuffer.ReadPointer = 1;
    pBuffer.WritePointer = 2;
    pBuffer.CumulativeOverrun = 0;
    pBuffer.CumulativeUnderrun = 0;
    std::memset(&pBuffer.Cache[0], 0, 5800321U * sizeof(creal32_T));
  }
}

//
// Arguments    : void
// Return Type  : void
//
void b_AsyncBuffer::reset()
{
  if (pBuffer.isInitialized == 2) {
    c_rtErrorWithMessageID("reset", s_emlrtRTEI.fName, s_emlrtRTEI.lineNo);
  }
  if (pBuffer.isInitialized == 1) {
    pBuffer.ReadPointer = 1;
    pBuffer.WritePointer = 2;
    pBuffer.CumulativeOverrun = 0;
    pBuffer.CumulativeUnderrun = 0;
    std::memset(&pBuffer.Cache[0], 0, 5800321U * sizeof(double));
  }
}

//
// Arguments    : void
// Return Type  : void
//
void c_AsyncBuffer::write()
{
  internal::c_AsyncBuffercgHelper *obj;
  array<int, 2U> bc;
  array<int, 1U> r;
  int i;
  int overrun;
  int rPtr;
  int wPtr;
  boolean_T anyInputSizeChanged;
  boolean_T exitg1;
  obj = &pBuffer;
  if (pBuffer.isInitialized == 2) {
    c_rtErrorWithMessageID("step", s_emlrtRTEI.fName, s_emlrtRTEI.lineNo);
  }
  if (pBuffer.isInitialized != 1) {
    cell_wrap_2 varSizes;
    pBuffer.isSetupComplete = false;
    if (pBuffer.isInitialized != 0) {
      d_rtErrorWithMessageID("setup", s_emlrtRTEI.fName, s_emlrtRTEI.lineNo);
    }
    pBuffer.isInitialized = 1;
    for (int b_i{0}; b_i < 8; b_i++) {
      varSizes.f1[b_i] = 1U;
    }
    pBuffer.inputVarSize[0] = varSizes;
    if ((pBuffer.NumChannels != -1) && (pBuffer.NumChannels != 1)) {
      n_rtErrorWithMessageID(t_emlrtRTEI.fName, t_emlrtRTEI.lineNo);
    }
    pBuffer.NumChannels = 1;
    pBuffer.AsyncBuffercgHelper_isInitialized = true;
    for (i = 0; i < 600651; i++) {
      pBuffer.Cache[i].re = 0.0F;
      pBuffer.Cache[i].im = 0.0F;
    }
    pBuffer.isSetupComplete = true;
    pBuffer.ReadPointer = 1;
    pBuffer.WritePointer = 2;
    pBuffer.CumulativeOverrun = 0;
    pBuffer.CumulativeUnderrun = 0;
    for (i = 0; i < 600651; i++) {
      pBuffer.Cache[i].re = 0.0F;
      pBuffer.Cache[i].im = 0.0F;
    }
  }
  anyInputSizeChanged = false;
  i = 0;
  exitg1 = false;
  while ((!exitg1) && (i < 8)) {
    if (obj->inputVarSize[0].f1[i] != 1U) {
      anyInputSizeChanged = true;
      for (int b_i{0}; b_i < 8; b_i++) {
        obj->inputVarSize[0].f1[b_i] = 1U;
      }
      exitg1 = true;
    } else {
      i++;
    }
  }
  if (anyInputSizeChanged && (pBuffer.NumChannels != -1) &&
      (pBuffer.NumChannels != 1)) {
    n_rtErrorWithMessageID(t_emlrtRTEI.fName, t_emlrtRTEI.lineNo);
  }
  obj = &pBuffer;
  wPtr = pBuffer.WritePointer;
  rPtr = pBuffer.ReadPointer;
  overrun = 0;
  if ((wPtr < 1) || (wPtr > 600651)) {
    rtErrorWithMessageID(b_emlrtRTEI.fName, b_emlrtRTEI.lineNo);
  }
  eml_integer_colon_dispatcher(wPtr, wPtr, bc);
  if ((wPtr <= rPtr) && (rPtr <= wPtr)) {
    overrun = (wPtr - rPtr) + 1;
  }
  r.set_size(bc.size(1));
  i = bc.size(1);
  for (int b_i{0}; b_i < i; b_i++) {
    if ((bc[b_i] < 1) || (bc[b_i] > 600651)) {
      rtDynamicBoundsError(bc[b_i], 1, 600651, &emlrtBCI);
    }
    r[b_i] = bc[b_i];
  }
  i = r.size(0);
  for (int b_i{0}; b_i < i; b_i++) {
    obj->Cache[r[b_i] - 1].re = 1.0F;
    obj->Cache[r[b_i] - 1].im = 1.0F;
  }
  if (wPtr + 1 > 600651) {
    wPtr = 1;
  } else {
    wPtr++;
  }
  if (overrun != 0) {
    rPtr = wPtr;
  }
  i = pBuffer.CumulativeOverrun;
  if ((i < 0) && (overrun < MIN_int32_T - i)) {
    i = MIN_int32_T;
  } else if ((i > 0) && (overrun > MAX_int32_T - i)) {
    i = MAX_int32_T;
  } else {
    i += overrun;
  }
  pBuffer.CumulativeOverrun = i;
  pBuffer.WritePointer = wPtr;
  pBuffer.ReadPointer = rPtr;
}

//
// Arguments    : const ::coder::array<creal32_T, 1U> &in
// Return Type  : void
//
void AsyncBuffer::write(const ::coder::array<creal32_T, 1U> &in)
{
  if (pBuffer.isInitialized == 2) {
    c_rtErrorWithMessageID("step", sb_emlrtRTEI.fName, sb_emlrtRTEI.lineNo);
  }
  if (pBuffer.isInitialized != 1) {
    pBuffer.isSetupComplete = false;
    if (pBuffer.isInitialized != 0) {
      d_rtErrorWithMessageID("setup", rb_emlrtRTEI.fName, rb_emlrtRTEI.lineNo);
    }
    pBuffer.isInitialized = 1;
    if ((pBuffer.NumChannels != -1) && (pBuffer.NumChannels != 1)) {
      n_rtErrorWithMessageID(t_emlrtRTEI.fName, t_emlrtRTEI.lineNo);
    }
    pBuffer.NumChannels = 1;
    pBuffer.AsyncBuffercgHelper_isInitialized = true;
    pBuffer.isSetupComplete = true;
    pBuffer.ReadPointer = 1;
    pBuffer.WritePointer = 2;
    pBuffer.CumulativeOverrun = 0;
    pBuffer.CumulativeUnderrun = 0;
    std::memset(&pBuffer.Cache[0], 0, 5800321U * sizeof(creal32_T));
  }
  pBuffer.stepImpl(in);
}

//
// Arguments    : const ::coder::array<double, 1U> &in
// Return Type  : void
//
void b_AsyncBuffer::write(const ::coder::array<double, 1U> &in)
{
  internal::b_AsyncBuffercgHelper *obj;
  int i;
  short inSize[8];
  boolean_T anyInputSizeChanged;
  boolean_T exitg1;
  obj = &pBuffer;
  if (pBuffer.isInitialized == 2) {
    c_rtErrorWithMessageID("step", sb_emlrtRTEI.fName, sb_emlrtRTEI.lineNo);
  }
  if (pBuffer.isInitialized != 1) {
    cell_wrap_2 varSizes;
    pBuffer.isSetupComplete = false;
    if (pBuffer.isInitialized != 0) {
      d_rtErrorWithMessageID("setup", rb_emlrtRTEI.fName, rb_emlrtRTEI.lineNo);
    }
    pBuffer.isInitialized = 1;
    varSizes.f1[0] = static_cast<unsigned int>(in.size(0));
    varSizes.f1[1] = 1U;
    for (i = 0; i < 6; i++) {
      varSizes.f1[i + 2] = 1U;
    }
    pBuffer.inputVarSize[0] = varSizes;
    if ((pBuffer.NumChannels != -1) && (pBuffer.NumChannels != 1)) {
      n_rtErrorWithMessageID(t_emlrtRTEI.fName, t_emlrtRTEI.lineNo);
    }
    pBuffer.NumChannels = 1;
    pBuffer.AsyncBuffercgHelper_isInitialized = true;
    for (i = 0; i < 5800321; i++) {
      pBuffer.Cache[i] = 0.0;
    }
    pBuffer.isSetupComplete = true;
    pBuffer.ReadPointer = 1;
    pBuffer.WritePointer = 2;
    pBuffer.CumulativeOverrun = 0;
    pBuffer.CumulativeUnderrun = 0;
    for (i = 0; i < 5800321; i++) {
      pBuffer.Cache[i] = 0.0;
    }
  }
  anyInputSizeChanged = false;
  inSize[0] = static_cast<short>(in.size(0));
  inSize[1] = 1;
  for (i = 0; i < 6; i++) {
    inSize[i + 2] = 1;
  }
  i = 0;
  exitg1 = false;
  while ((!exitg1) && (i < 8)) {
    if (obj->inputVarSize[0].f1[i] != static_cast<unsigned int>(inSize[i])) {
      anyInputSizeChanged = true;
      for (i = 0; i < 8; i++) {
        obj->inputVarSize[0].f1[i] = static_cast<unsigned int>(inSize[i]);
      }
      exitg1 = true;
    } else {
      i++;
    }
  }
  if (anyInputSizeChanged && (pBuffer.NumChannels != -1) &&
      (pBuffer.NumChannels != 1)) {
    n_rtErrorWithMessageID(t_emlrtRTEI.fName, t_emlrtRTEI.lineNo);
  }
  pBuffer.stepImpl(in);
}

//
// Arguments    : const ::coder::array<creal32_T, 1U> &in
// Return Type  : void
//
void c_AsyncBuffer::write(const ::coder::array<creal32_T, 1U> &in)
{
  static const short inSize[8]{16384, 1, 1, 1, 1, 1, 1, 1};
  static const short iv[8]{16384, 1, 1, 1, 1, 1, 1, 1};
  internal::c_AsyncBuffercgHelper *obj;
  int i;
  boolean_T anyInputSizeChanged;
  boolean_T exitg1;
  obj = &pBuffer;
  if (pBuffer.isInitialized == 2) {
    c_rtErrorWithMessageID("step", sb_emlrtRTEI.fName, sb_emlrtRTEI.lineNo);
  }
  if (pBuffer.isInitialized != 1) {
    cell_wrap_2 varSizes;
    pBuffer.isSetupComplete = false;
    if (pBuffer.isInitialized != 0) {
      d_rtErrorWithMessageID("setup", rb_emlrtRTEI.fName, rb_emlrtRTEI.lineNo);
    }
    pBuffer.isInitialized = 1;
    for (i = 0; i < 8; i++) {
      varSizes.f1[i] = static_cast<unsigned int>(inSize[i]);
    }
    pBuffer.inputVarSize[0] = varSizes;
    if ((pBuffer.NumChannels != -1) && (pBuffer.NumChannels != 1)) {
      n_rtErrorWithMessageID(t_emlrtRTEI.fName, t_emlrtRTEI.lineNo);
    }
    pBuffer.NumChannels = 1;
    pBuffer.AsyncBuffercgHelper_isInitialized = true;
    for (i = 0; i < 600651; i++) {
      pBuffer.Cache[i].re = 0.0F;
      pBuffer.Cache[i].im = 0.0F;
    }
    pBuffer.isSetupComplete = true;
    pBuffer.ReadPointer = 1;
    pBuffer.WritePointer = 2;
    pBuffer.CumulativeOverrun = 0;
    pBuffer.CumulativeUnderrun = 0;
    for (i = 0; i < 600651; i++) {
      pBuffer.Cache[i].re = 0.0F;
      pBuffer.Cache[i].im = 0.0F;
    }
  }
  anyInputSizeChanged = false;
  i = 0;
  exitg1 = false;
  while ((!exitg1) && (i < 8)) {
    if (obj->inputVarSize[0].f1[i] != static_cast<unsigned int>(iv[i])) {
      anyInputSizeChanged = true;
      for (i = 0; i < 8; i++) {
        obj->inputVarSize[0].f1[i] = static_cast<unsigned int>(inSize[i]);
      }
      exitg1 = true;
    } else {
      i++;
    }
  }
  if (anyInputSizeChanged && (pBuffer.NumChannels != -1) &&
      (pBuffer.NumChannels != 1)) {
    n_rtErrorWithMessageID(t_emlrtRTEI.fName, t_emlrtRTEI.lineNo);
  }
  pBuffer.stepImpl(in);
}

} // namespace dsp
} // namespace coder

//
// File trailer for AsyncBuffer.cpp
//
// [EOF]
//
