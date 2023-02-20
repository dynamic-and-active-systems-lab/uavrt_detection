//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: AsyncBuffer.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 14:31:55
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

static rtBoundsCheckInfo
    emlrtBCI{
        1,                           // iFirst
        600651,                      // iLast
        227,                         // lineNo
        23,                          // colNo
        "",                          // aName
        "AsyncBuffercgHelper/write", // fName
        "C:\\Program "
        "Files\\MATLAB\\toolbox\\dsp\\dsp\\+dsp\\+"
        "internal\\AsyncBuffercgHelper.m", // pName
        3                                  // checkKind
    };

static rtRunTimeErrorInfo u_emlrtRTEI{
    103,                 // lineNo
    "AsyncBuffercg/read" // fName
};

static rtRunTimeErrorInfo ib_emlrtRTEI{
    1,                // lineNo
    "SystemCore/step" // fName
};

static rtRunTimeErrorInfo jb_emlrtRTEI{
    1,                 // lineNo
    "SystemCore/setup" // fName
};

static rtEqualityCheckInfo
    b_emlrtECI{
        -1,                          // nDims
        227,                         // lineNo
        13,                          // colNo
        "AsyncBuffercgHelper/write", // fName
        "C:\\Program "
        "Files\\MATLAB\\toolbox\\dsp\\dsp\\+dsp\\+"
        "internal\\AsyncBuffercgHelper.m" // pName
    };

static rtBoundsCheckInfo
    d_emlrtBCI{
        1,                           // iFirst
        5800321,                     // iLast
        227,                         // lineNo
        23,                          // colNo
        "",                          // aName
        "AsyncBuffercgHelper/write", // fName
        "C:\\Program "
        "Files\\MATLAB\\toolbox\\dsp\\dsp\\+dsp\\+"
        "internal\\AsyncBuffercgHelper.m", // pName
        3                                  // checkKind
    };

// Function Declarations
static void c_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum);

static void d_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum);

static void o_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void p_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

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
static void o_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
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
    p_rtErrorWithMessageID(u_emlrtRTEI.fName, u_emlrtRTEI.lineNo);
  }
  pBuffer.read(numRows, out, &q0_tmp);
}

//
// Arguments    : creal32_T out_data[]
//                int *out_size
// Return Type  : void
//
void c_AsyncBuffer::read(creal32_T out_data[], int *out_size)
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
    p_rtErrorWithMessageID(u_emlrtRTEI.fName, u_emlrtRTEI.lineNo);
  }
  pBuffer.read(numRows, out, &q0_tmp);
  *out_size = out.size(0);
  numRows = out.size(0);
  for (q0_tmp = 0; q0_tmp < numRows; q0_tmp++) {
    out_data[q0_tmp] = out[q0_tmp];
  }
}

//
// Arguments    : int numRows
//                creal32_T out_data[]
//                int *out_size
// Return Type  : void
//
void AsyncBuffer::read(int numRows, creal32_T out_data[], int *out_size)
{
  int underrun;
  if (numRows < 0) {
    e_rtErrorWithMessageID("number of rows", v_emlrtRTEI.fName,
                           v_emlrtRTEI.lineNo);
  }
  if (numRows > 5800320) {
    p_rtErrorWithMessageID(u_emlrtRTEI.fName, u_emlrtRTEI.lineNo);
  }
  pBuffer.read(numRows, out_data, out_size, &underrun);
}

//
// Arguments    : double numRows
//                creal32_T out_data[]
//                int *out_size
// Return Type  : void
//
void AsyncBuffer::read(double numRows, creal32_T out_data[], int *out_size)
{
  int underrun;
  if (numRows < 0.0) {
    e_rtErrorWithMessageID("number of rows", v_emlrtRTEI.fName,
                           v_emlrtRTEI.lineNo);
  }
  if (std::isinf(numRows) || std::isnan(numRows)) {
    g_rtErrorWithMessageID("number of rows", cb_emlrtRTEI.fName,
                           cb_emlrtRTEI.lineNo);
  }
  if (!(std::floor(numRows) == numRows)) {
    k_rtErrorWithMessageID("number of rows", fb_emlrtRTEI.fName,
                           fb_emlrtRTEI.lineNo);
  }
  if (numRows > 5.80032E+6) {
    p_rtErrorWithMessageID(u_emlrtRTEI.fName, u_emlrtRTEI.lineNo);
  }
  pBuffer.read(static_cast<int>(numRows), out_data, out_size, &underrun);
}

//
// Arguments    : double numRows
//                double out_data[]
//                int *out_size
// Return Type  : void
//
void b_AsyncBuffer::read(double numRows, double out_data[], int *out_size)
{
  array<int, 2U> b_y;
  array<int, 2U> y;
  double d;
  int c;
  int k;
  int numRowsCast;
  int rPtr;
  int underrun;
  int wPtr_tmp;
  int yk;
  d = std::round(numRows);
  if (d < 2.147483648E+9) {
    if (d >= -2.147483648E+9) {
      numRowsCast = static_cast<int>(d);
    } else {
      numRowsCast = MIN_int32_T;
    }
  } else if (d >= 2.147483648E+9) {
    numRowsCast = MAX_int32_T;
  } else {
    numRowsCast = 0;
  }
  if (numRows < 0.0) {
    e_rtErrorWithMessageID("number of rows", v_emlrtRTEI.fName,
                           v_emlrtRTEI.lineNo);
  }
  if (std::isinf(numRows) || std::isnan(numRows)) {
    g_rtErrorWithMessageID("number of rows", cb_emlrtRTEI.fName,
                           cb_emlrtRTEI.lineNo);
  }
  if (!(std::floor(numRows) == numRows)) {
    k_rtErrorWithMessageID("number of rows", fb_emlrtRTEI.fName,
                           fb_emlrtRTEI.lineNo);
  }
  if (numRows > 5.80032E+6) {
    p_rtErrorWithMessageID(u_emlrtRTEI.fName, u_emlrtRTEI.lineNo);
  }
  if (!pBuffer.AsyncBuffercgHelper_isInitialized) {
    q_rtErrorWithMessageID(w_emlrtRTEI.fName, w_emlrtRTEI.lineNo);
  }
  wPtr_tmp = pBuffer.WritePointer;
  underrun = 0;
  yk = pBuffer.ReadPointer;
  if (yk > 2147483646) {
    rPtr = MAX_int32_T;
  } else {
    rPtr = yk + 1;
  }
  if (rPtr > 5800321) {
    rPtr = 1;
  }
  if ((wPtr_tmp < 1) || (wPtr_tmp > 5800321) || (rPtr < 1) ||
      (numRowsCast > 5800321)) {
    b_rtErrorWithMessageID(b_emlrtRTEI.fName, b_emlrtRTEI.lineNo);
  }
  c = (rPtr + numRowsCast) - 1;
  if (c > 5800321) {
    c -= 5800321;
    b_y.set_size(1, c);
    b_y[0] = 1;
    yk = 1;
    for (k = 2; k <= c; k++) {
      yk++;
      b_y[k - 1] = yk;
    }
    y.set_size(1, (b_y.size(1) - rPtr) + 5800322);
    yk = 5800322 - rPtr;
    for (k = 0; k < yk; k++) {
      y[k] = rPtr;
    }
    yk = b_y.size(1);
    for (k = 0; k < yk; k++) {
      y[(k - rPtr) + 5800322] = b_y[k];
    }
    if (rPtr <= wPtr_tmp) {
      underrun = (c - wPtr_tmp) + 5800322;
    } else if (wPtr_tmp <= c) {
      underrun = (c - wPtr_tmp) + 1;
    }
  } else {
    eml_integer_colon_dispatcher(rPtr, c, y);
    if ((rPtr <= wPtr_tmp) && (wPtr_tmp <= c)) {
      underrun = (c - wPtr_tmp) + 1;
    }
  }
  *out_size = y.size(1);
  yk = y.size(1);
  for (k = 0; k < yk; k++) {
    if ((y[k] < 1) || (y[k] > 5800321)) {
      rtDynamicBoundsError(y[k], 1, 5800321, &e_emlrtBCI);
    }
    out_data[k] = pBuffer.Cache[y[k] - 1];
  }
  if (underrun != 0) {
    if ((numRowsCast >= 0) && (underrun < numRowsCast - MAX_int32_T)) {
      yk = MAX_int32_T;
    } else if ((numRowsCast < 0) && (underrun > numRowsCast - MIN_int32_T)) {
      yk = MIN_int32_T;
    } else {
      yk = numRowsCast - underrun;
    }
    if (yk + 1 > numRowsCast) {
      k = 0;
    } else {
      if ((yk + 1 < 1) || (yk + 1 > y.size(1))) {
        rtDynamicBoundsError(yk + 1, 1, y.size(1), &c_emlrtBCI);
      }
      if ((numRowsCast < 1) || (numRowsCast > y.size(1))) {
        rtDynamicBoundsError(numRowsCast, 1, y.size(1), &b_emlrtBCI);
      }
      k = 1;
    }
    if (underrun < 0) {
      rtNonNegativeError(static_cast<double>(underrun), &emlrtDCI);
    }
    rtSubAssignSizeCheck(&k, 1, &underrun, 1, &emlrtECI);
    if (underrun - 1 >= 0) {
      std::memset(&out_data[0], 0, underrun * sizeof(double));
    }
  }
  if (*out_size != numRowsCast) {
    j_rtErrorWithMessageID(x_emlrtRTEI.fName, x_emlrtRTEI.lineNo);
  }
  yk = pBuffer.CumulativeUnderrun;
  if ((yk < 0) && (underrun < MIN_int32_T - yk)) {
    yk = MIN_int32_T;
  } else if ((yk > 0) && (underrun > MAX_int32_T - yk)) {
    yk = MAX_int32_T;
  } else {
    yk += underrun;
  }
  pBuffer.CumulativeUnderrun = yk;
  if (underrun != 0) {
    pBuffer.ReadPointer = wPtr_tmp - 1;
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
      o_rtErrorWithMessageID(t_emlrtRTEI.fName, t_emlrtRTEI.lineNo);
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
    o_rtErrorWithMessageID(t_emlrtRTEI.fName, t_emlrtRTEI.lineNo);
  }
  obj = &pBuffer;
  wPtr = pBuffer.WritePointer;
  rPtr = pBuffer.ReadPointer;
  overrun = 0;
  if ((wPtr < 1) || (wPtr > 600651)) {
    b_rtErrorWithMessageID(b_emlrtRTEI.fName, b_emlrtRTEI.lineNo);
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
// Arguments    : const creal32_T in_data[]
//                int in_size
// Return Type  : void
//
void AsyncBuffer::write(const creal32_T in_data[], int in_size)
{
  array<int, 2U> y;
  int c;
  int loop_ub;
  int rPtr;
  int tmp_data;
  int varargout_1;
  int wPtr;
  if (pBuffer.isInitialized == 2) {
    c_rtErrorWithMessageID("step", ib_emlrtRTEI.fName, ib_emlrtRTEI.lineNo);
  }
  if (pBuffer.isInitialized != 1) {
    pBuffer.isSetupComplete = false;
    if (pBuffer.isInitialized != 0) {
      d_rtErrorWithMessageID("setup", jb_emlrtRTEI.fName, jb_emlrtRTEI.lineNo);
    }
    pBuffer.isInitialized = 1;
    pBuffer.inputVarSize[0].f1[0] = static_cast<unsigned int>(in_size);
    pBuffer.inputVarSize[0].f1[1] = 1U;
    for (int i{0}; i < 6; i++) {
      pBuffer.inputVarSize[0].f1[i + 2] = 1U;
    }
    if ((pBuffer.NumChannels != -1) && (pBuffer.NumChannels != 1)) {
      o_rtErrorWithMessageID(t_emlrtRTEI.fName, t_emlrtRTEI.lineNo);
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
  wPtr = pBuffer.WritePointer;
  rPtr = pBuffer.ReadPointer;
  varargout_1 = 0;
  if ((wPtr < 1) || (wPtr > 5800321)) {
    b_rtErrorWithMessageID(b_emlrtRTEI.fName, b_emlrtRTEI.lineNo);
  }
  c = wPtr + in_size;
  eml_integer_colon_dispatcher(wPtr, c - 1, y);
  if ((wPtr <= rPtr) && (rPtr <= c - 1)) {
    varargout_1 = c - rPtr;
  }
  wPtr = y.size(1);
  loop_ub = y.size(1);
  for (int i{0}; i < loop_ub; i++) {
    if ((y[i] < 1) || (y[i] > 5800321)) {
      rtDynamicBoundsError(y[i], 1, 5800321, &d_emlrtBCI);
    }
    tmp_data = y[i] - 1;
  }
  rtSubAssignSizeCheck(&wPtr, 1, &in_size, 1, &b_emlrtECI);
  for (int i{0}; i < in_size; i++) {
    pBuffer.Cache[tmp_data] = in_data[0];
  }
  if (c > 5800321) {
    wPtr = 1;
  } else {
    wPtr = c;
  }
  if (varargout_1 != 0) {
    rPtr = wPtr;
  }
  tmp_data = pBuffer.CumulativeOverrun;
  if ((tmp_data < 0) && (varargout_1 < MIN_int32_T - tmp_data)) {
    tmp_data = MIN_int32_T;
  } else if ((tmp_data > 0) && (varargout_1 > MAX_int32_T - tmp_data)) {
    tmp_data = MAX_int32_T;
  } else {
    tmp_data += varargout_1;
  }
  pBuffer.CumulativeOverrun = tmp_data;
  pBuffer.WritePointer = wPtr;
  pBuffer.ReadPointer = rPtr;
}

//
// Arguments    : const double in_data[]
//                int in_size
// Return Type  : void
//
void b_AsyncBuffer::write(const double in_data[], int in_size)
{
  array<int, 2U> y;
  int c;
  int loop_ub;
  int rPtr;
  int tmp_data;
  int varargout_1;
  int wPtr;
  if (pBuffer.isInitialized == 2) {
    c_rtErrorWithMessageID("step", ib_emlrtRTEI.fName, ib_emlrtRTEI.lineNo);
  }
  if (pBuffer.isInitialized != 1) {
    pBuffer.isSetupComplete = false;
    if (pBuffer.isInitialized != 0) {
      d_rtErrorWithMessageID("setup", jb_emlrtRTEI.fName, jb_emlrtRTEI.lineNo);
    }
    pBuffer.isInitialized = 1;
    pBuffer.inputVarSize[0].f1[0] = static_cast<unsigned int>(in_size);
    pBuffer.inputVarSize[0].f1[1] = 1U;
    for (int i{0}; i < 6; i++) {
      pBuffer.inputVarSize[0].f1[i + 2] = 1U;
    }
    if ((pBuffer.NumChannels != -1) && (pBuffer.NumChannels != 1)) {
      o_rtErrorWithMessageID(t_emlrtRTEI.fName, t_emlrtRTEI.lineNo);
    }
    pBuffer.NumChannels = 1;
    pBuffer.AsyncBuffercgHelper_isInitialized = true;
    pBuffer.isSetupComplete = true;
    pBuffer.ReadPointer = 1;
    pBuffer.WritePointer = 2;
    pBuffer.CumulativeOverrun = 0;
    pBuffer.CumulativeUnderrun = 0;
    std::memset(&pBuffer.Cache[0], 0, 5800321U * sizeof(double));
  }
  wPtr = pBuffer.WritePointer;
  rPtr = pBuffer.ReadPointer;
  varargout_1 = 0;
  if ((wPtr < 1) || (wPtr > 5800321)) {
    b_rtErrorWithMessageID(b_emlrtRTEI.fName, b_emlrtRTEI.lineNo);
  }
  c = wPtr + in_size;
  eml_integer_colon_dispatcher(wPtr, c - 1, y);
  if ((wPtr <= rPtr) && (rPtr <= c - 1)) {
    varargout_1 = c - rPtr;
  }
  wPtr = y.size(1);
  loop_ub = y.size(1);
  for (int i{0}; i < loop_ub; i++) {
    if ((y[i] < 1) || (y[i] > 5800321)) {
      rtDynamicBoundsError(y[i], 1, 5800321, &d_emlrtBCI);
    }
    tmp_data = y[i] - 1;
  }
  rtSubAssignSizeCheck(&wPtr, 1, &in_size, 1, &b_emlrtECI);
  for (int i{0}; i < in_size; i++) {
    pBuffer.Cache[tmp_data] = in_data[0];
  }
  if (c > 5800321) {
    wPtr = 1;
  } else {
    wPtr = c;
  }
  if (varargout_1 != 0) {
    rPtr = wPtr;
  }
  tmp_data = pBuffer.CumulativeOverrun;
  if ((tmp_data < 0) && (varargout_1 < MIN_int32_T - tmp_data)) {
    tmp_data = MIN_int32_T;
  } else if ((tmp_data > 0) && (varargout_1 > MAX_int32_T - tmp_data)) {
    tmp_data = MAX_int32_T;
  } else {
    tmp_data += varargout_1;
  }
  pBuffer.CumulativeOverrun = tmp_data;
  pBuffer.WritePointer = wPtr;
  pBuffer.ReadPointer = rPtr;
}

//
// Arguments    : const creal32_T in_data[]
//                int in_size
// Return Type  : void
//
void c_AsyncBuffer::write(const creal32_T in_data[], int in_size)
{
  array<int, 2U> y;
  int c;
  int loop_ub;
  int rPtr;
  int tmp_data;
  int varargout_1;
  int wPtr;
  if (pBuffer.isInitialized == 2) {
    c_rtErrorWithMessageID("step", ib_emlrtRTEI.fName, ib_emlrtRTEI.lineNo);
  }
  if (pBuffer.isInitialized != 1) {
    pBuffer.isSetupComplete = false;
    if (pBuffer.isInitialized != 0) {
      d_rtErrorWithMessageID("setup", jb_emlrtRTEI.fName, jb_emlrtRTEI.lineNo);
    }
    pBuffer.isInitialized = 1;
    pBuffer.inputVarSize[0].f1[0] = static_cast<unsigned int>(in_size);
    pBuffer.inputVarSize[0].f1[1] = 1U;
    for (int i{0}; i < 6; i++) {
      pBuffer.inputVarSize[0].f1[i + 2] = 1U;
    }
    if ((pBuffer.NumChannels != -1) && (pBuffer.NumChannels != 1)) {
      o_rtErrorWithMessageID(t_emlrtRTEI.fName, t_emlrtRTEI.lineNo);
    }
    pBuffer.NumChannels = 1;
    pBuffer.AsyncBuffercgHelper_isInitialized = true;
    pBuffer.isSetupComplete = true;
    pBuffer.ReadPointer = 1;
    pBuffer.WritePointer = 2;
    pBuffer.CumulativeOverrun = 0;
    pBuffer.CumulativeUnderrun = 0;
    std::memset(&pBuffer.Cache[0], 0, 600651U * sizeof(creal32_T));
  }
  wPtr = pBuffer.WritePointer;
  rPtr = pBuffer.ReadPointer;
  varargout_1 = 0;
  if ((wPtr < 1) || (wPtr > 600651)) {
    b_rtErrorWithMessageID(b_emlrtRTEI.fName, b_emlrtRTEI.lineNo);
  }
  c = wPtr + in_size;
  eml_integer_colon_dispatcher(wPtr, c - 1, y);
  if ((wPtr <= rPtr) && (rPtr <= c - 1)) {
    varargout_1 = c - rPtr;
  }
  wPtr = y.size(1);
  loop_ub = y.size(1);
  for (int i{0}; i < loop_ub; i++) {
    if ((y[i] < 1) || (y[i] > 600651)) {
      rtDynamicBoundsError(y[i], 1, 600651, &emlrtBCI);
    }
    tmp_data = y[i] - 1;
  }
  rtSubAssignSizeCheck(&wPtr, 1, &in_size, 1, &b_emlrtECI);
  for (int i{0}; i < in_size; i++) {
    pBuffer.Cache[tmp_data] = in_data[0];
  }
  if (c > 600651) {
    wPtr = 1;
  } else {
    wPtr = c;
  }
  if (varargout_1 != 0) {
    rPtr = wPtr;
  }
  tmp_data = pBuffer.CumulativeOverrun;
  if ((tmp_data < 0) && (varargout_1 < MIN_int32_T - tmp_data)) {
    tmp_data = MIN_int32_T;
  } else if ((tmp_data > 0) && (varargout_1 > MAX_int32_T - tmp_data)) {
    tmp_data = MAX_int32_T;
  } else {
    tmp_data += varargout_1;
  }
  pBuffer.CumulativeOverrun = tmp_data;
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
