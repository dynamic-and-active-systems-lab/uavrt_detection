//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: AsyncBuffer.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "AsyncBuffer.h"
#include "AsyncBufferSysObj.h"
#include "colon.h"
#include "eml_int_forloop_overflow_check.h"
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
#include <string>

// Variable Definitions
static rtRunTimeErrorInfo o_emlrtRTEI{
    1,                   // lineNo
    "SystemCore/release" // fName
};

static rtRunTimeErrorInfo p_emlrtRTEI{
    101,                                   // lineNo
    "AsyncBufferSysObj/validateInputsImpl" // fName
};

static rtRunTimeErrorInfo q_emlrtRTEI{
    104,               // lineNo
    "AsyncBuffer/read" // fName
};

static rtRunTimeErrorInfo mb_emlrtRTEI{
    1,                 // lineNo
    "SystemCore/reset" // fName
};

static rtRunTimeErrorInfo nb_emlrtRTEI{
    1,                // lineNo
    "SystemCore/step" // fName
};

static rtRunTimeErrorInfo ob_emlrtRTEI{
    93,                                    // lineNo
    "AsyncBufferSysObj/validateInputsImpl" // fName
};

static rtRunTimeErrorInfo pb_emlrtRTEI{
    1,                 // lineNo
    "SystemCore/setup" // fName
};

static rtBoundsCheckInfo s_emlrtBCI{
    227,                      // lineNo
    "",                       // aName
    "AsyncBufferSysObj/write" // fName
};

static rtRunTimeErrorInfo rb_emlrtRTEI{
    110,               // lineNo
    "AsyncBuffer/read" // fName
};

// Function Declarations
static void c_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum);

static void d_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum);

static void eb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void hb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void o_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void p_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
namespace coder {
namespace dsp {
void AsyncBuffer::matlabCodegenDestructor()
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
void c_AsyncBuffer::matlabCodegenDestructor()
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
static void eb_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Invalid number of input rows. Specify an input with number of "
               "rows less than or equal to the buffer capacity.";
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
static void hb_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
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
static void o_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Changing the number of channels (number of columns) of the "
               "input signal is not supported.";
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
  outStream << "Invalid number of rows requested. Specify the number of rows "
               "to read as less than or equal to the buffer capacity.";
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
// Return Type  : AsyncBuffer
//
namespace coder {
namespace dsp {
AsyncBuffer::AsyncBuffer()
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
// Return Type  : c_AsyncBuffer
//
c_AsyncBuffer::c_AsyncBuffer()
{
  matlabCodegenIsDeleted = true;
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
b_AsyncBuffer::~b_AsyncBuffer()
{
  matlabCodegenDestructor();
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
// Return Type  : int
//
int c_AsyncBuffer::get_NumUnreadSamples() const
{
  int q0_tmp;
  int q1_tmp;
  int unreadSamples;
  q0_tmp = pBuffer.WritePointer;
  q1_tmp = pBuffer.ReadPointer;
  if ((q0_tmp >= 0) && (q1_tmp < q0_tmp - MAX_int32_T)) {
    unreadSamples = MAX_int32_T;
  } else if ((q0_tmp < 0) && (q1_tmp > q0_tmp - MIN_int32_T)) {
    unreadSamples = MIN_int32_T;
  } else {
    unreadSamples = q0_tmp - q1_tmp;
  }
  if (unreadSamples < -2147483647) {
    unreadSamples = MIN_int32_T;
  } else {
    unreadSamples--;
  }
  if (q1_tmp < -2146882997) {
    q1_tmp = MAX_int32_T;
  } else {
    q1_tmp = 600650 - q1_tmp;
  }
  if ((q1_tmp < 0) && (q0_tmp < MIN_int32_T - q1_tmp)) {
    q1_tmp = MIN_int32_T;
  } else if ((q1_tmp > 0) && (q0_tmp > MAX_int32_T - q1_tmp)) {
    q1_tmp = MAX_int32_T;
  } else {
    q1_tmp += q0_tmp;
  }
  if (pBuffer.ReadPointer >= pBuffer.WritePointer) {
    if (pBuffer.ReadPointer == pBuffer.WritePointer) {
      unreadSamples = 600650;
    } else {
      unreadSamples = q1_tmp;
    }
  }
  return unreadSamples;
}

//
// Arguments    : void
// Return Type  : int
//
int AsyncBuffer::get_NumUnreadSamples() const
{
  int q0_tmp;
  int q1_tmp;
  int unreadSamples;
  q0_tmp = pBuffer.WritePointer;
  q1_tmp = pBuffer.ReadPointer;
  if ((q0_tmp >= 0) && (q1_tmp < q0_tmp - MAX_int32_T)) {
    unreadSamples = MAX_int32_T;
  } else if ((q0_tmp < 0) && (q1_tmp > q0_tmp - MIN_int32_T)) {
    unreadSamples = MIN_int32_T;
  } else {
    unreadSamples = q0_tmp - q1_tmp;
  }
  if (unreadSamples < -2147483647) {
    unreadSamples = MIN_int32_T;
  } else {
    unreadSamples--;
  }
  if (q1_tmp < -2141683327) {
    q1_tmp = MAX_int32_T;
  } else {
    q1_tmp = 5800320 - q1_tmp;
  }
  if ((q1_tmp < 0) && (q0_tmp < MIN_int32_T - q1_tmp)) {
    q1_tmp = MIN_int32_T;
  } else if ((q1_tmp > 0) && (q0_tmp > MAX_int32_T - q1_tmp)) {
    q1_tmp = MAX_int32_T;
  } else {
    q1_tmp += q0_tmp;
  }
  if (pBuffer.ReadPointer >= pBuffer.WritePointer) {
    if (pBuffer.ReadPointer == pBuffer.WritePointer) {
      unreadSamples = 5800320;
    } else {
      unreadSamples = q1_tmp;
    }
  }
  return unreadSamples;
}

//
// Arguments    : void
// Return Type  : AsyncBuffer *
//
AsyncBuffer *AsyncBuffer::init()
{
  AsyncBuffer *obj;
  obj = this;
  obj->pBuffer.NumChannels = -1;
  obj->pBuffer.isInitialized = 0;
  obj->pBuffer.matlabCodegenIsDeleted = false;
  obj->matlabCodegenIsDeleted = false;
  return obj;
}

//
// Arguments    : void
// Return Type  : c_AsyncBuffer *
//
c_AsyncBuffer *c_AsyncBuffer::init()
{
  c_AsyncBuffer *obj;
  obj = this;
  obj->pBuffer.NumChannels = -1;
  obj->pBuffer.isInitialized = 0;
  obj->pBuffer.matlabCodegenIsDeleted = false;
  obj->matlabCodegenIsDeleted = false;
  return obj;
}

//
// Arguments    : void
// Return Type  : b_AsyncBuffer *
//
b_AsyncBuffer *b_AsyncBuffer::init()
{
  b_AsyncBuffer *obj;
  obj = this;
  obj->pBuffer.NumChannels = -1;
  obj->pBuffer.isInitialized = 0;
  obj->pBuffer.matlabCodegenIsDeleted = false;
  obj->matlabCodegenIsDeleted = false;
  return obj;
}

//
// Arguments    : double numRows
//                array<creal32_T, 1U> &out
// Return Type  : void
//
void AsyncBuffer::read(double numRows, array<creal32_T, 1U> &out)
{
  if (numRows < 0.0) {
    e_rtErrorWithMessageID("number of rows", r_emlrtRTEI.fName,
                           r_emlrtRTEI.lineNo);
  }
  if (std::isinf(numRows) || std::isnan(numRows)) {
    i_rtErrorWithMessageID("number of rows", w_emlrtRTEI.fName,
                           w_emlrtRTEI.lineNo);
  }
  if (!(std::floor(numRows) == numRows)) {
    j_rtErrorWithMessageID("number of rows", bb_emlrtRTEI.fName,
                           bb_emlrtRTEI.lineNo);
  }
  if (numRows > 5.80032E+6) {
    p_rtErrorWithMessageID(q_emlrtRTEI.fName, q_emlrtRTEI.lineNo);
  }
  pBuffer.read(static_cast<int>(numRows), out);
}

//
// Arguments    : double numRows
//                array<double, 1U> &out
// Return Type  : void
//
void b_AsyncBuffer::read(double numRows, array<double, 1U> &out)
{
  if (numRows < 0.0) {
    e_rtErrorWithMessageID("number of rows", r_emlrtRTEI.fName,
                           r_emlrtRTEI.lineNo);
  }
  if (std::isinf(numRows) || std::isnan(numRows)) {
    i_rtErrorWithMessageID("number of rows", w_emlrtRTEI.fName,
                           w_emlrtRTEI.lineNo);
  }
  if (!(std::floor(numRows) == numRows)) {
    j_rtErrorWithMessageID("number of rows", bb_emlrtRTEI.fName,
                           bb_emlrtRTEI.lineNo);
  }
  if (numRows > 5.80032E+6) {
    p_rtErrorWithMessageID(q_emlrtRTEI.fName, q_emlrtRTEI.lineNo);
  }
  pBuffer.read(static_cast<int>(numRows), out);
}

//
// Arguments    : double numRows
//                double overlap
//                array<creal32_T, 1U> &out
// Return Type  : void
//
void AsyncBuffer::read(double numRows, double overlap,
                       array<creal32_T, 1U> &out)
{
  array<creal32_T, 1U> b_out;
  int c;
  int overlapUnderrun;
  int underrun;
  if (numRows < 0.0) {
    e_rtErrorWithMessageID("number of rows", r_emlrtRTEI.fName,
                           r_emlrtRTEI.lineNo);
  }
  if (std::isinf(numRows) || std::isnan(numRows)) {
    i_rtErrorWithMessageID("number of rows", w_emlrtRTEI.fName,
                           w_emlrtRTEI.lineNo);
  }
  if (!(std::floor(numRows) == numRows)) {
    j_rtErrorWithMessageID("number of rows", bb_emlrtRTEI.fName,
                           bb_emlrtRTEI.lineNo);
  }
  if (numRows > 5.80032E+6) {
    p_rtErrorWithMessageID(q_emlrtRTEI.fName, q_emlrtRTEI.lineNo);
  }
  if (overlap < 0.0) {
    e_rtErrorWithMessageID("overlap", r_emlrtRTEI.fName, r_emlrtRTEI.lineNo);
  }
  if (std::isinf(overlap) || std::isnan(overlap)) {
    i_rtErrorWithMessageID("overlap", w_emlrtRTEI.fName, w_emlrtRTEI.lineNo);
  }
  if (!(std::floor(overlap) == overlap)) {
    j_rtErrorWithMessageID("overlap", bb_emlrtRTEI.fName, bb_emlrtRTEI.lineNo);
  }
  if (overlap > numRows) {
    hb_rtErrorWithMessageID(rb_emlrtRTEI.fName, rb_emlrtRTEI.lineNo);
  }
  if (!pBuffer.AsyncBufferSysObj_isInitialized) {
    q_rtErrorWithMessageID(s_emlrtRTEI.fName, s_emlrtRTEI.lineNo);
  }
  underrun = internal::codegen::AsyncBufferSysObj::ReadSamplesFromBuffer(
      pBuffer, static_cast<int>(numRows), static_cast<int>(overlap), b_out,
      overlapUnderrun, c);
  overlapUnderrun = b_out.size(0);
  out.set_size(b_out.size(0));
  for (int i{0}; i < overlapUnderrun; i++) {
    out[i] = b_out[i];
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
  overlapUnderrun = pBuffer.WritePointer;
  if (overlapUnderrun < -2147483647) {
    overlapUnderrun = MIN_int32_T;
  } else {
    overlapUnderrun--;
  }
  if (underrun != 0) {
    pBuffer.ReadPointer = overlapUnderrun;
  } else {
    pBuffer.ReadPointer = c;
  }
}

//
// Arguments    : double numRows
//                double overlap
//                array<double, 1U> &out
// Return Type  : void
//
void b_AsyncBuffer::read(double numRows, double overlap, array<double, 1U> &out)
{
  array<double, 1U> b_out;
  int c;
  int overlapUnderrun;
  int underrun;
  if (numRows < 0.0) {
    e_rtErrorWithMessageID("number of rows", r_emlrtRTEI.fName,
                           r_emlrtRTEI.lineNo);
  }
  if (std::isinf(numRows) || std::isnan(numRows)) {
    i_rtErrorWithMessageID("number of rows", w_emlrtRTEI.fName,
                           w_emlrtRTEI.lineNo);
  }
  if (!(std::floor(numRows) == numRows)) {
    j_rtErrorWithMessageID("number of rows", bb_emlrtRTEI.fName,
                           bb_emlrtRTEI.lineNo);
  }
  if (numRows > 5.80032E+6) {
    p_rtErrorWithMessageID(q_emlrtRTEI.fName, q_emlrtRTEI.lineNo);
  }
  if (overlap < 0.0) {
    e_rtErrorWithMessageID("overlap", r_emlrtRTEI.fName, r_emlrtRTEI.lineNo);
  }
  if (std::isinf(overlap) || std::isnan(overlap)) {
    i_rtErrorWithMessageID("overlap", w_emlrtRTEI.fName, w_emlrtRTEI.lineNo);
  }
  if (!(std::floor(overlap) == overlap)) {
    j_rtErrorWithMessageID("overlap", bb_emlrtRTEI.fName, bb_emlrtRTEI.lineNo);
  }
  if (overlap > numRows) {
    hb_rtErrorWithMessageID(rb_emlrtRTEI.fName, rb_emlrtRTEI.lineNo);
  }
  if (!pBuffer.AsyncBufferSysObj_isInitialized) {
    q_rtErrorWithMessageID(s_emlrtRTEI.fName, s_emlrtRTEI.lineNo);
  }
  underrun = internal::codegen::b_AsyncBufferSysObj::ReadSamplesFromBuffer(
      pBuffer, static_cast<int>(numRows), static_cast<int>(overlap), b_out,
      overlapUnderrun, c);
  overlapUnderrun = b_out.size(0);
  out.set_size(b_out.size(0));
  for (int i{0}; i < overlapUnderrun; i++) {
    out[i] = b_out[i];
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
  overlapUnderrun = pBuffer.WritePointer;
  if (overlapUnderrun < -2147483647) {
    overlapUnderrun = MIN_int32_T;
  } else {
    overlapUnderrun--;
  }
  if (underrun != 0) {
    pBuffer.ReadPointer = overlapUnderrun;
  } else {
    pBuffer.ReadPointer = c;
  }
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
    e_rtErrorWithMessageID("number of rows", r_emlrtRTEI.fName,
                           r_emlrtRTEI.lineNo);
  }
  if (numRows > 600650) {
    p_rtErrorWithMessageID(q_emlrtRTEI.fName, q_emlrtRTEI.lineNo);
  }
  pBuffer.read(numRows, out);
}

//
// Arguments    : array<creal32_T, 1U> &out
// Return Type  : void
//
void c_AsyncBuffer::read(array<creal32_T, 1U> &out)
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
    e_rtErrorWithMessageID("number of rows", r_emlrtRTEI.fName,
                           r_emlrtRTEI.lineNo);
  }
  if (numRows > 600650) {
    p_rtErrorWithMessageID(q_emlrtRTEI.fName, q_emlrtRTEI.lineNo);
  }
  pBuffer.read(numRows, out);
}

//
// Arguments    : void
// Return Type  : void
//
void c_AsyncBuffer::reset()
{
  if (pBuffer.isInitialized == 2) {
    c_rtErrorWithMessageID("reset", mb_emlrtRTEI.fName, mb_emlrtRTEI.lineNo);
  }
  if (pBuffer.isInitialized == 1) {
    pBuffer.ReadPointer = 1;
    pBuffer.WritePointer = 2;
    pBuffer.CumulativeOverrun = 0;
    pBuffer.CumulativeUnderrun = 0;
    std::memset(&pBuffer.Cache[0], 0, 600651U * sizeof(creal32_T));
  }
}

//
// Arguments    : void
// Return Type  : void
//
void b_AsyncBuffer::reset()
{
  if (pBuffer.isInitialized == 2) {
    c_rtErrorWithMessageID("reset", mb_emlrtRTEI.fName, mb_emlrtRTEI.lineNo);
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
void AsyncBuffer::reset()
{
  if (pBuffer.isInitialized == 2) {
    c_rtErrorWithMessageID("reset", o_emlrtRTEI.fName, o_emlrtRTEI.lineNo);
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
// Arguments    : const creal32_T in_data[]
// Return Type  : void
//
void c_AsyncBuffer::write(const creal32_T in_data[])
{
  static const short inSize[8]{1023, 1, 1, 1, 1, 1, 1, 1};
  static const short iv[8]{1023, 1, 1, 1, 1, 1, 1, 1};
  static const short iv1[8]{1023, 1, 1, 1, 1, 1, 1, 1};
  int k;
  boolean_T anyInputSizeChanged;
  boolean_T exitg1;
  if (pBuffer.isInitialized == 2) {
    c_rtErrorWithMessageID("step", nb_emlrtRTEI.fName, nb_emlrtRTEI.lineNo);
  }
  if (pBuffer.isInitialized != 1) {
    if (pBuffer.isInitialized != 0) {
      d_rtErrorWithMessageID("setup", pb_emlrtRTEI.fName, pb_emlrtRTEI.lineNo);
    }
    pBuffer.isInitialized = 1;
    for (k = 0; k < 8; k++) {
      pBuffer.inputVarSize[0].f1[k] = static_cast<unsigned int>(iv[k]);
    }
    if ((pBuffer.NumChannels != -1) && (pBuffer.NumChannels != 1)) {
      o_rtErrorWithMessageID(p_emlrtRTEI.fName, p_emlrtRTEI.lineNo);
    }
    pBuffer.NumChannels = 1;
    pBuffer.AsyncBufferSysObj_isInitialized = true;
    pBuffer.isSetupComplete = true;
    pBuffer.ReadPointer = 1;
    pBuffer.WritePointer = 2;
    pBuffer.CumulativeOverrun = 0;
    pBuffer.CumulativeUnderrun = 0;
    std::memset(&pBuffer.Cache[0], 0, 600651U * sizeof(creal32_T));
  }
  anyInputSizeChanged = false;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 8)) {
    if (pBuffer.inputVarSize[0].f1[k] != static_cast<unsigned int>(iv1[k])) {
      anyInputSizeChanged = true;
      for (k = 0; k < 8; k++) {
        pBuffer.inputVarSize[0].f1[k] = static_cast<unsigned int>(inSize[k]);
      }
      exitg1 = true;
    } else {
      k++;
    }
  }
  if (anyInputSizeChanged && (pBuffer.NumChannels != -1) &&
      (pBuffer.NumChannels != 1)) {
    o_rtErrorWithMessageID(p_emlrtRTEI.fName, p_emlrtRTEI.lineNo);
  }
  pBuffer.stepImpl(in_data);
}

//
// Arguments    : const array<double, 1U> &in
// Return Type  : void
//
void b_AsyncBuffer::write(const array<double, 1U> &in)
{
  array<int, 2U> b_y;
  array<int, 2U> bc;
  array<int, 2U> y;
  array<int, 1U> r;
  unsigned int inSize[8];
  int b_qY;
  int c;
  int k;
  int n;
  int qY;
  int rPtr;
  int wPtr;
  int yk;
  boolean_T anyInputSizeChanged;
  boolean_T exitg1;
  if (pBuffer.isInitialized == 2) {
    c_rtErrorWithMessageID("step", nb_emlrtRTEI.fName, nb_emlrtRTEI.lineNo);
  }
  if (pBuffer.isInitialized != 1) {
    if (pBuffer.isInitialized != 0) {
      d_rtErrorWithMessageID("setup", pb_emlrtRTEI.fName, pb_emlrtRTEI.lineNo);
    }
    pBuffer.isInitialized = 1;
    pBuffer.inputVarSize[0].f1[0] = static_cast<unsigned int>(in.size(0));
    pBuffer.inputVarSize[0].f1[1] = 1U;
    for (yk = 0; yk < 6; yk++) {
      pBuffer.inputVarSize[0].f1[yk + 2] = 1U;
    }
    if (in.size(0) > 5800320) {
      eb_rtErrorWithMessageID(ob_emlrtRTEI.fName, ob_emlrtRTEI.lineNo);
    }
    if ((pBuffer.NumChannels != -1) && (pBuffer.NumChannels != 1)) {
      o_rtErrorWithMessageID(p_emlrtRTEI.fName, p_emlrtRTEI.lineNo);
    }
    pBuffer.NumChannels = 1;
    pBuffer.AsyncBufferSysObj_isInitialized = true;
    pBuffer.isSetupComplete = true;
    pBuffer.ReadPointer = 1;
    pBuffer.WritePointer = 2;
    pBuffer.CumulativeOverrun = 0;
    pBuffer.CumulativeUnderrun = 0;
    std::memset(&pBuffer.Cache[0], 0, 5800321U * sizeof(double));
  }
  anyInputSizeChanged = false;
  inSize[0] = static_cast<unsigned int>(in.size(0));
  inSize[1] = 1U;
  for (yk = 0; yk < 6; yk++) {
    inSize[yk + 2] = 1U;
  }
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 8)) {
    if (pBuffer.inputVarSize[0].f1[k] != inSize[k]) {
      anyInputSizeChanged = true;
      for (yk = 0; yk < 8; yk++) {
        pBuffer.inputVarSize[0].f1[yk] = inSize[yk];
      }
      exitg1 = true;
    } else {
      k++;
    }
  }
  if (anyInputSizeChanged) {
    if (in.size(0) > 5800320) {
      eb_rtErrorWithMessageID(ob_emlrtRTEI.fName, ob_emlrtRTEI.lineNo);
    }
    if ((pBuffer.NumChannels != -1) && (pBuffer.NumChannels != 1)) {
      o_rtErrorWithMessageID(p_emlrtRTEI.fName, p_emlrtRTEI.lineNo);
    }
  }
  wPtr = pBuffer.WritePointer;
  rPtr = pBuffer.ReadPointer;
  qY = 0;
  if ((wPtr < 1) || (wPtr > 5800321)) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  if (in.size(0) > MAX_int32_T - wPtr) {
    b_qY = MAX_int32_T;
  } else {
    b_qY = wPtr + in.size(0);
  }
  c = b_qY - 1;
  if (b_qY - 1 > 5800321) {
    c = b_qY - 5800322;
    n = 5800322 - wPtr;
    y.set_size(1, n);
    y[0] = wPtr;
    yk = wPtr;
    for (k = 2; k <= n; k++) {
      yk++;
      y[k - 1] = yk;
    }
    if (b_qY - 5800322 < 1) {
      n = 0;
    } else {
      n = b_qY - 5800322;
    }
    b_y.set_size(1, n);
    if (n > 0) {
      b_y[0] = 1;
      yk = 1;
      if (n > 2147483646) {
        check_forloop_overflow_error();
      }
      for (k = 2; k <= n; k++) {
        yk++;
        b_y[k - 1] = yk;
      }
    }
    bc.set_size(1, y.size(1) + b_y.size(1));
    n = y.size(1);
    for (yk = 0; yk < n; yk++) {
      bc[yk] = y[yk];
    }
    n = b_y.size(1);
    for (yk = 0; yk < n; yk++) {
      bc[yk + y.size(1)] = b_y[yk];
    }
    if (wPtr <= rPtr) {
      qY = b_qY - rPtr;
    } else if (rPtr <= b_qY - 5800322) {
      if (rPtr < b_qY + 2141683327) {
        b_qY = MAX_int32_T;
      } else {
        b_qY = (b_qY - rPtr) - 5800322;
      }
      if (b_qY > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY = b_qY + 1;
      }
    }
  } else {
    eml_integer_colon_dispatcher(wPtr, b_qY - 1, bc);
    if ((wPtr <= rPtr) && (rPtr <= b_qY - 1)) {
      qY = b_qY - rPtr;
    }
  }
  n = bc.size(1);
  r.set_size(bc.size(1));
  for (yk = 0; yk < n; yk++) {
    if ((bc[yk] < 1) || (bc[yk] > 5800321)) {
      rtDynamicBoundsError(bc[yk], 1, 5800321, s_emlrtBCI);
    }
    r[yk] = bc[yk] - 1;
  }
  rtSubAssignSizeCheck(&(bc.size())[1], 1, ((array<double, 1U> *)&in)->size(),
                       1, e_emlrtECI);
  for (yk = 0; yk < n; yk++) {
    pBuffer.Cache[r[yk]] = in[yk];
  }
  if (c + 1 > 5800321) {
    wPtr = 1;
  } else {
    wPtr = c + 1;
  }
  if (qY != 0) {
    rPtr = wPtr;
  }
  n = pBuffer.CumulativeOverrun;
  if ((n < 0) && (qY < MIN_int32_T - n)) {
    b_qY = MIN_int32_T;
  } else if ((n > 0) && (qY > MAX_int32_T - n)) {
    b_qY = MAX_int32_T;
  } else {
    b_qY = n + qY;
  }
  pBuffer.CumulativeOverrun = b_qY;
  pBuffer.WritePointer = wPtr;
  pBuffer.ReadPointer = rPtr;
}

//
// Arguments    : const array<creal32_T, 1U> &in
// Return Type  : void
//
void AsyncBuffer::write(const array<creal32_T, 1U> &in)
{
  array<int, 2U> b_y;
  array<int, 2U> bc;
  array<int, 2U> y;
  array<int, 1U> r;
  unsigned int inSize[8];
  int b_qY;
  int c;
  int k;
  int n;
  int qY;
  int rPtr;
  int wPtr;
  int yk;
  boolean_T anyInputSizeChanged;
  boolean_T exitg1;
  if (pBuffer.isInitialized == 2) {
    c_rtErrorWithMessageID("step", nb_emlrtRTEI.fName, nb_emlrtRTEI.lineNo);
  }
  if (pBuffer.isInitialized != 1) {
    if (pBuffer.isInitialized != 0) {
      d_rtErrorWithMessageID("setup", pb_emlrtRTEI.fName, pb_emlrtRTEI.lineNo);
    }
    pBuffer.isInitialized = 1;
    pBuffer.inputVarSize[0].f1[0] = static_cast<unsigned int>(in.size(0));
    pBuffer.inputVarSize[0].f1[1] = 1U;
    for (yk = 0; yk < 6; yk++) {
      pBuffer.inputVarSize[0].f1[yk + 2] = 1U;
    }
    if (in.size(0) > 5800320) {
      eb_rtErrorWithMessageID(ob_emlrtRTEI.fName, ob_emlrtRTEI.lineNo);
    }
    if ((pBuffer.NumChannels != -1) && (pBuffer.NumChannels != 1)) {
      o_rtErrorWithMessageID(p_emlrtRTEI.fName, p_emlrtRTEI.lineNo);
    }
    pBuffer.NumChannels = 1;
    pBuffer.AsyncBufferSysObj_isInitialized = true;
    pBuffer.isSetupComplete = true;
    pBuffer.ReadPointer = 1;
    pBuffer.WritePointer = 2;
    pBuffer.CumulativeOverrun = 0;
    pBuffer.CumulativeUnderrun = 0;
    std::memset(&pBuffer.Cache[0], 0, 5800321U * sizeof(creal32_T));
  }
  anyInputSizeChanged = false;
  inSize[0] = static_cast<unsigned int>(in.size(0));
  inSize[1] = 1U;
  for (yk = 0; yk < 6; yk++) {
    inSize[yk + 2] = 1U;
  }
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 8)) {
    if (pBuffer.inputVarSize[0].f1[k] != inSize[k]) {
      anyInputSizeChanged = true;
      for (yk = 0; yk < 8; yk++) {
        pBuffer.inputVarSize[0].f1[yk] = inSize[yk];
      }
      exitg1 = true;
    } else {
      k++;
    }
  }
  if (anyInputSizeChanged) {
    if (in.size(0) > 5800320) {
      eb_rtErrorWithMessageID(ob_emlrtRTEI.fName, ob_emlrtRTEI.lineNo);
    }
    if ((pBuffer.NumChannels != -1) && (pBuffer.NumChannels != 1)) {
      o_rtErrorWithMessageID(p_emlrtRTEI.fName, p_emlrtRTEI.lineNo);
    }
  }
  wPtr = pBuffer.WritePointer;
  rPtr = pBuffer.ReadPointer;
  qY = 0;
  if ((wPtr < 1) || (wPtr > 5800321)) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  if (in.size(0) > MAX_int32_T - wPtr) {
    b_qY = MAX_int32_T;
  } else {
    b_qY = wPtr + in.size(0);
  }
  c = b_qY - 1;
  if (b_qY - 1 > 5800321) {
    c = b_qY - 5800322;
    n = 5800322 - wPtr;
    y.set_size(1, n);
    y[0] = wPtr;
    yk = wPtr;
    for (k = 2; k <= n; k++) {
      yk++;
      y[k - 1] = yk;
    }
    if (b_qY - 5800322 < 1) {
      n = 0;
    } else {
      n = b_qY - 5800322;
    }
    b_y.set_size(1, n);
    if (n > 0) {
      b_y[0] = 1;
      yk = 1;
      if (n > 2147483646) {
        check_forloop_overflow_error();
      }
      for (k = 2; k <= n; k++) {
        yk++;
        b_y[k - 1] = yk;
      }
    }
    bc.set_size(1, y.size(1) + b_y.size(1));
    n = y.size(1);
    for (yk = 0; yk < n; yk++) {
      bc[yk] = y[yk];
    }
    n = b_y.size(1);
    for (yk = 0; yk < n; yk++) {
      bc[yk + y.size(1)] = b_y[yk];
    }
    if (wPtr <= rPtr) {
      qY = b_qY - rPtr;
    } else if (rPtr <= b_qY - 5800322) {
      if (rPtr < b_qY + 2141683327) {
        b_qY = MAX_int32_T;
      } else {
        b_qY = (b_qY - rPtr) - 5800322;
      }
      if (b_qY > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY = b_qY + 1;
      }
    }
  } else {
    eml_integer_colon_dispatcher(wPtr, b_qY - 1, bc);
    if ((wPtr <= rPtr) && (rPtr <= b_qY - 1)) {
      qY = b_qY - rPtr;
    }
  }
  n = bc.size(1);
  r.set_size(bc.size(1));
  for (yk = 0; yk < n; yk++) {
    if ((bc[yk] < 1) || (bc[yk] > 5800321)) {
      rtDynamicBoundsError(bc[yk], 1, 5800321, s_emlrtBCI);
    }
    r[yk] = bc[yk] - 1;
  }
  rtSubAssignSizeCheck(&(bc.size())[1], 1,
                       ((array<creal32_T, 1U> *)&in)->size(), 1, e_emlrtECI);
  for (yk = 0; yk < n; yk++) {
    pBuffer.Cache[r[yk]] = in[yk];
  }
  if (c + 1 > 5800321) {
    wPtr = 1;
  } else {
    wPtr = c + 1;
  }
  if (qY != 0) {
    rPtr = wPtr;
  }
  n = pBuffer.CumulativeOverrun;
  if ((n < 0) && (qY < MIN_int32_T - n)) {
    b_qY = MIN_int32_T;
  } else if ((n > 0) && (qY > MAX_int32_T - n)) {
    b_qY = MAX_int32_T;
  } else {
    b_qY = n + qY;
  }
  pBuffer.CumulativeOverrun = b_qY;
  pBuffer.WritePointer = wPtr;
  pBuffer.ReadPointer = rPtr;
}

//
// Arguments    : void
// Return Type  : void
//
void c_AsyncBuffer::write()
{
  array<int, 2U> bc;
  array<int, 1U> r;
  int i;
  int overrun;
  int rPtr;
  int wPtr;
  boolean_T anyInputSizeChanged;
  boolean_T exitg1;
  if (pBuffer.isInitialized == 2) {
    c_rtErrorWithMessageID("step", o_emlrtRTEI.fName, o_emlrtRTEI.lineNo);
  }
  if (pBuffer.isInitialized != 1) {
    if (pBuffer.isInitialized != 0) {
      d_rtErrorWithMessageID("setup", o_emlrtRTEI.fName, o_emlrtRTEI.lineNo);
    }
    pBuffer.isInitialized = 1;
    for (int b_i{0}; b_i < 8; b_i++) {
      pBuffer.inputVarSize[0].f1[b_i] = 1U;
    }
    if ((pBuffer.NumChannels != -1) && (pBuffer.NumChannels != 1)) {
      o_rtErrorWithMessageID(p_emlrtRTEI.fName, p_emlrtRTEI.lineNo);
    }
    pBuffer.NumChannels = 1;
    pBuffer.AsyncBufferSysObj_isInitialized = true;
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
    if (pBuffer.inputVarSize[0].f1[i] != 1U) {
      anyInputSizeChanged = true;
      for (int b_i{0}; b_i < 8; b_i++) {
        pBuffer.inputVarSize[0].f1[b_i] = 1U;
      }
      exitg1 = true;
    } else {
      i++;
    }
  }
  if (anyInputSizeChanged && (pBuffer.NumChannels != -1) &&
      (pBuffer.NumChannels != 1)) {
    o_rtErrorWithMessageID(p_emlrtRTEI.fName, p_emlrtRTEI.lineNo);
  }
  wPtr = pBuffer.WritePointer;
  rPtr = pBuffer.ReadPointer;
  overrun = 0;
  if ((wPtr < 1) || (wPtr > 600651)) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  eml_integer_colon_dispatcher(wPtr, wPtr, bc);
  if ((wPtr <= rPtr) && (rPtr <= wPtr)) {
    overrun = (wPtr - rPtr) + 1;
  }
  i = bc.size(1);
  r.set_size(bc.size(1));
  for (int b_i{0}; b_i < i; b_i++) {
    if ((bc[b_i] < 1) || (bc[b_i] > 600651)) {
      rtDynamicBoundsError(bc[b_i], 1, 600651, emlrtBCI);
    }
    r[b_i] = bc[b_i];
  }
  for (int b_i{0}; b_i < i; b_i++) {
    pBuffer.Cache[r[b_i] - 1].re = 1.0F;
    pBuffer.Cache[r[b_i] - 1].im = 1.0F;
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

} // namespace dsp
} // namespace coder

//
// File trailer for AsyncBuffer.cpp
//
// [EOF]
//
