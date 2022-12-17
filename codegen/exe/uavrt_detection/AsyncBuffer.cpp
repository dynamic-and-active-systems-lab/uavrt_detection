//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: AsyncBuffer.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 17-Dec-2022 13:40:17
//

// Include Files
#include "AsyncBuffer.h"
#include "AsyncBuffercgHelper.h"
#include "colon.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
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
static rtRunTimeErrorInfo kb_emlrtRTEI{
    1,                // lineNo
    "SystemCore/step" // fName
};

static rtRunTimeErrorInfo lb_emlrtRTEI{
    101,                                     // lineNo
    "AsyncBuffercgHelper/validateInputsImpl" // fName
};

static rtEqualityCheckInfo
    d_emlrtECI{
        -1,                          // nDims
        227,                         // lineNo
        13,                          // colNo
        "AsyncBuffercgHelper/write", // fName
        "C:\\Program "
        "Files\\MATLAB\\toolbox\\dsp\\dsp\\+dsp\\+"
        "internal\\AsyncBuffercgHelper.m" // pName
    };

static rtBoundsCheckInfo
    v_emlrtBCI{
        1,                           // iFirst
        49621,                       // iLast
        227,                         // lineNo
        23,                          // colNo
        "",                          // aName
        "AsyncBuffercgHelper/write", // fName
        "C:\\Program "
        "Files\\MATLAB\\toolbox\\dsp\\dsp\\+dsp\\+"
        "internal\\AsyncBuffercgHelper.m", // pName
        3                                  // checkKind
    };

static rtRunTimeErrorInfo nb_emlrtRTEI{
    103,                 // lineNo
    "AsyncBuffercg/read" // fName
};

static rtRunTimeErrorInfo ob_emlrtRTEI{
    324,                       // lineNo
    "AsyncBuffercgHelper/read" // fName
};

static rtRunTimeErrorInfo pb_emlrtRTEI{
    473,                                        // lineNo
    "AsyncBuffercgHelper/ReadSamplesFromBuffer" // fName
};

static rtEqualityCheckInfo
    e_emlrtECI{
        -1,                                          // nDims
        462,                                         // lineNo
        17,                                          // colNo
        "AsyncBuffercgHelper/ReadSamplesFromBuffer", // fName
        "C:\\Program "
        "Files\\MATLAB\\toolbox\\dsp\\dsp\\+dsp\\+"
        "internal\\AsyncBuffercgHelper.m" // pName
    };

static rtBoundsCheckInfo
    w_emlrtBCI{
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

static rtBoundsCheckInfo
    x_emlrtBCI{
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

static rtDoubleCheckInfo
    o_emlrtDCI{
        463,                                         // lineNo
        27,                                          // colNo
        "AsyncBuffercgHelper/ReadSamplesFromBuffer", // fName
        "C:\\Program "
        "Files\\MATLAB\\toolbox\\dsp\\dsp\\+dsp\\+"
        "internal\\AsyncBuffercgHelper.m", // pName
        4                                  // checkKind
    };

static rtBoundsCheckInfo
    y_emlrtBCI{
        1,                                           // iFirst
        49621,                                       // iLast
        457,                                         // lineNo
        29,                                          // colNo
        "",                                          // aName
        "AsyncBuffercgHelper/ReadSamplesFromBuffer", // fName
        "C:\\Program "
        "Files\\MATLAB\\toolbox\\dsp\\dsp\\+dsp\\+"
        "internal\\AsyncBuffercgHelper.m", // pName
        0                                  // checkKind
    };

static rtRunTimeErrorInfo qb_emlrtRTEI{
    109,                 // lineNo
    "AsyncBuffercg/read" // fName
};

static rtEqualityCheckInfo
    f_emlrtECI{
        -1,                                          // nDims
        469,                                         // lineNo
        21,                                          // colNo
        "AsyncBuffercgHelper/ReadSamplesFromBuffer", // fName
        "C:\\Program "
        "Files\\MATLAB\\toolbox\\dsp\\dsp\\+dsp\\+"
        "internal\\AsyncBuffercgHelper.m" // pName
    };

static rtBoundsCheckInfo
    ab_emlrtBCI{
        -1,                                          // iFirst
        -1,                                          // iLast
        469,                                         // lineNo
        33,                                          // colNo
        "",                                          // aName
        "AsyncBuffercgHelper/ReadSamplesFromBuffer", // fName
        "C:\\Program "
        "Files\\MATLAB\\toolbox\\dsp\\dsp\\+dsp\\+"
        "internal\\AsyncBuffercgHelper.m", // pName
        0                                  // checkKind
    };

static rtBoundsCheckInfo
    bb_emlrtBCI{
        -1,                                          // iFirst
        -1,                                          // iLast
        469,                                         // lineNo
        25,                                          // colNo
        "",                                          // aName
        "AsyncBuffercgHelper/ReadSamplesFromBuffer", // fName
        "C:\\Program "
        "Files\\MATLAB\\toolbox\\dsp\\dsp\\+dsp\\+"
        "internal\\AsyncBuffercgHelper.m", // pName
        0                                  // checkKind
    };

static rtDoubleCheckInfo
    p_emlrtDCI{
        470,                                         // lineNo
        31,                                          // colNo
        "AsyncBuffercgHelper/ReadSamplesFromBuffer", // fName
        "C:\\Program "
        "Files\\MATLAB\\toolbox\\dsp\\dsp\\+dsp\\+"
        "internal\\AsyncBuffercgHelper.m", // pName
        4                                  // checkKind
    };

static rtDoubleCheckInfo
    q_emlrtDCI{
        467,                                         // lineNo
        21,                                          // colNo
        "AsyncBuffercgHelper/ReadSamplesFromBuffer", // fName
        "C:\\Program "
        "Files\\MATLAB\\toolbox\\dsp\\dsp\\+dsp\\+"
        "internal\\AsyncBuffercgHelper.m", // pName
        4                                  // checkKind
    };

// Function Declarations
static void ab_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void i_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum);

static void j_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum);

static void w_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void x_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void y_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
namespace coder {
namespace dsp {
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
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
} // namespace dsp
} // namespace coder
static void ab_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
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
// Arguments    : const char *r
//                const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void i_rtErrorWithMessageID(const char *r, const char *aFcnName,
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
static void j_rtErrorWithMessageID(const char *r, const char *aFcnName,
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
static void w_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
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
static void x_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
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
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void y_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream
      << "Buffer not initialized. You must call write before read or peek.";
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
// Return Type  : b_AsyncBuffer
//
namespace coder {
namespace dsp {
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
// Arguments    : double numRows
//                ::coder::array<creal32_T, 1U> &out
// Return Type  : void
//
void AsyncBuffer::read(double numRows, ::coder::array<creal32_T, 1U> &out)
{
  internal::AsyncBuffercgHelper *obj;
  array<creal32_T, 1U> b_out;
  array<int, 2U> b_y;
  array<int, 2U> readIdx;
  array<int, 2U> y;
  int c;
  int i;
  int k;
  int n;
  int rPtr;
  int underrun;
  int wPtr;
  int yk;
  if (numRows < 0.0) {
    g_rtErrorWithMessageID("number of rows", ab_emlrtRTEI.fName,
                           ab_emlrtRTEI.lineNo);
  }
  if (std::isinf(numRows) || std::isnan(numRows)) {
    c_rtErrorWithMessageID("number of rows", v_emlrtRTEI.fName,
                           v_emlrtRTEI.lineNo);
  }
  if (!(std::floor(numRows) == numRows)) {
    f_rtErrorWithMessageID("number of rows", y_emlrtRTEI.fName,
                           y_emlrtRTEI.lineNo);
  }
  if (numRows > 49620.0) {
    x_rtErrorWithMessageID(nb_emlrtRTEI.fName, nb_emlrtRTEI.lineNo);
  }
  if (!pBuffer.AsyncBuffercgHelper_isInitialized) {
    y_rtErrorWithMessageID(ob_emlrtRTEI.fName, ob_emlrtRTEI.lineNo);
  }
  i = static_cast<int>(numRows);
  obj = &pBuffer;
  wPtr = pBuffer.WritePointer;
  underrun = 0;
  n = pBuffer.ReadPointer;
  if (n > 2147483646) {
    rPtr = MAX_int32_T;
  } else {
    rPtr = n + 1;
  }
  if (rPtr > 49621) {
    rPtr = 1;
  }
  if ((wPtr < 1) || (wPtr > 49621) || (rPtr < 1)) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  c = (rPtr + i) - 1;
  if (c > 49621) {
    c -= 49621;
    if (rPtr > 49621) {
      n = 0;
    } else {
      n = 49622 - rPtr;
    }
    y.set_size(1, n);
    if (n > 0) {
      y[0] = rPtr;
      yk = rPtr;
      for (k = 2; k <= n; k++) {
        yk++;
        y[k - 1] = yk;
      }
    }
    b_y.set_size(1, c);
    b_y[0] = 1;
    yk = 1;
    for (k = 2; k <= c; k++) {
      yk++;
      b_y[k - 1] = yk;
    }
    readIdx.set_size(1, y.size(1) + b_y.size(1));
    n = y.size(1);
    for (k = 0; k < n; k++) {
      readIdx[k] = y[k];
    }
    n = b_y.size(1);
    for (k = 0; k < n; k++) {
      readIdx[k + y.size(1)] = b_y[k];
    }
    if (rPtr <= wPtr) {
      underrun = (c - wPtr) + 49622;
    } else if (wPtr <= c) {
      underrun = (c - wPtr) + 1;
    }
  } else {
    eml_integer_colon_dispatcher(rPtr, c, readIdx);
    if ((rPtr <= wPtr) && (wPtr <= c)) {
      underrun = (c - wPtr) + 1;
    }
  }
  b_out.set_size(readIdx.size(1));
  n = readIdx.size(1);
  for (k = 0; k < n; k++) {
    if ((readIdx[k] < 1) || (readIdx[k] > 49621)) {
      rtDynamicBoundsError(readIdx[k], 1, 49621, &y_emlrtBCI);
    }
    b_out[k].re = obj->Cache[readIdx[k] - 1].re;
    if ((readIdx[k] < 1) || (readIdx[k] > 49621)) {
      rtDynamicBoundsError(readIdx[k], 1, 49621, &y_emlrtBCI);
    }
    b_out[k].im = obj->Cache[readIdx[k] - 1].im;
  }
  if (underrun != 0) {
    yk = i - underrun;
    if (yk + 1 > i) {
      yk = 0;
      k = 0;
    } else {
      if ((yk + 1 < 1) || (yk + 1 > readIdx.size(1))) {
        rtDynamicBoundsError(yk + 1, 1, readIdx.size(1), &x_emlrtBCI);
      }
      if ((i < 1) || (i > readIdx.size(1))) {
        rtDynamicBoundsError(i, 1, readIdx.size(1), &w_emlrtBCI);
      }
      k = i;
    }
    if (underrun < 0) {
      rtNonNegativeError(static_cast<double>(underrun), &o_emlrtDCI);
    }
    k -= yk;
    rtSubAssignSizeCheck(&k, 1, &underrun, 1, &e_emlrtECI);
    for (k = 0; k < underrun; k++) {
      n = yk + k;
      b_out[n].re = 0.0F;
      b_out[n].im = 0.0F;
    }
  }
  if (b_out.size(0) != i) {
    h_rtErrorWithMessageID(pb_emlrtRTEI.fName, pb_emlrtRTEI.lineNo);
  }
  out.set_size(b_out.size(0));
  n = b_out.size(0);
  for (i = 0; i < n; i++) {
    out[i] = b_out[i];
  }
  n = pBuffer.WritePointer;
  if (n < -2147483647) {
    yk = MIN_int32_T;
  } else {
    yk = n - 1;
  }
  n = pBuffer.CumulativeUnderrun;
  if ((n < 0) && (underrun < MIN_int32_T - n)) {
    n = MIN_int32_T;
  } else if ((n > 0) && (underrun > MAX_int32_T - n)) {
    n = MAX_int32_T;
  } else {
    n += underrun;
  }
  pBuffer.CumulativeUnderrun = n;
  if (underrun != 0) {
    pBuffer.ReadPointer = yk;
  } else {
    pBuffer.ReadPointer = c;
  }
}

//
// Arguments    : double numRows
//                ::coder::array<double, 1U> &out
// Return Type  : void
//
void b_AsyncBuffer::read(double numRows, ::coder::array<double, 1U> &out)
{
  internal::b_AsyncBuffercgHelper *obj;
  array<double, 1U> b_out;
  array<int, 2U> b_y;
  array<int, 2U> readIdx;
  array<int, 2U> y;
  int c;
  int i;
  int k;
  int n;
  int rPtr;
  int underrun;
  int wPtr;
  int yk;
  if (numRows < 0.0) {
    g_rtErrorWithMessageID("number of rows", ab_emlrtRTEI.fName,
                           ab_emlrtRTEI.lineNo);
  }
  if (std::isinf(numRows) || std::isnan(numRows)) {
    c_rtErrorWithMessageID("number of rows", v_emlrtRTEI.fName,
                           v_emlrtRTEI.lineNo);
  }
  if (!(std::floor(numRows) == numRows)) {
    f_rtErrorWithMessageID("number of rows", y_emlrtRTEI.fName,
                           y_emlrtRTEI.lineNo);
  }
  if (numRows > 49620.0) {
    x_rtErrorWithMessageID(nb_emlrtRTEI.fName, nb_emlrtRTEI.lineNo);
  }
  if (!pBuffer.AsyncBuffercgHelper_isInitialized) {
    y_rtErrorWithMessageID(ob_emlrtRTEI.fName, ob_emlrtRTEI.lineNo);
  }
  i = static_cast<int>(numRows);
  obj = &pBuffer;
  wPtr = pBuffer.WritePointer;
  underrun = 0;
  n = pBuffer.ReadPointer;
  if (n > 2147483646) {
    rPtr = MAX_int32_T;
  } else {
    rPtr = n + 1;
  }
  if (rPtr > 49621) {
    rPtr = 1;
  }
  if ((wPtr < 1) || (wPtr > 49621) || (rPtr < 1)) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  c = (rPtr + i) - 1;
  if (c > 49621) {
    c -= 49621;
    if (rPtr > 49621) {
      n = 0;
    } else {
      n = 49622 - rPtr;
    }
    y.set_size(1, n);
    if (n > 0) {
      y[0] = rPtr;
      yk = rPtr;
      for (k = 2; k <= n; k++) {
        yk++;
        y[k - 1] = yk;
      }
    }
    b_y.set_size(1, c);
    b_y[0] = 1;
    yk = 1;
    for (k = 2; k <= c; k++) {
      yk++;
      b_y[k - 1] = yk;
    }
    readIdx.set_size(1, y.size(1) + b_y.size(1));
    n = y.size(1);
    for (k = 0; k < n; k++) {
      readIdx[k] = y[k];
    }
    n = b_y.size(1);
    for (k = 0; k < n; k++) {
      readIdx[k + y.size(1)] = b_y[k];
    }
    if (rPtr <= wPtr) {
      underrun = (c - wPtr) + 49622;
    } else if (wPtr <= c) {
      underrun = (c - wPtr) + 1;
    }
  } else {
    eml_integer_colon_dispatcher(rPtr, c, readIdx);
    if ((rPtr <= wPtr) && (wPtr <= c)) {
      underrun = (c - wPtr) + 1;
    }
  }
  b_out.set_size(readIdx.size(1));
  n = readIdx.size(1);
  for (k = 0; k < n; k++) {
    if ((readIdx[k] < 1) || (readIdx[k] > 49621)) {
      rtDynamicBoundsError(readIdx[k], 1, 49621, &y_emlrtBCI);
    }
    b_out[k] = obj->Cache[readIdx[k] - 1];
  }
  if (underrun != 0) {
    yk = i - underrun;
    if (yk + 1 > i) {
      yk = 0;
      k = 0;
    } else {
      if ((yk + 1 < 1) || (yk + 1 > readIdx.size(1))) {
        rtDynamicBoundsError(yk + 1, 1, readIdx.size(1), &x_emlrtBCI);
      }
      if ((i < 1) || (i > readIdx.size(1))) {
        rtDynamicBoundsError(i, 1, readIdx.size(1), &w_emlrtBCI);
      }
      k = i;
    }
    if (underrun < 0) {
      rtNonNegativeError(static_cast<double>(underrun), &o_emlrtDCI);
    }
    k -= yk;
    rtSubAssignSizeCheck(&k, 1, &underrun, 1, &e_emlrtECI);
    for (k = 0; k < underrun; k++) {
      b_out[yk + k] = 0.0;
    }
  }
  if (b_out.size(0) != i) {
    h_rtErrorWithMessageID(pb_emlrtRTEI.fName, pb_emlrtRTEI.lineNo);
  }
  out.set_size(b_out.size(0));
  n = b_out.size(0);
  for (i = 0; i < n; i++) {
    out[i] = b_out[i];
  }
  n = pBuffer.WritePointer;
  if (n < -2147483647) {
    yk = MIN_int32_T;
  } else {
    yk = n - 1;
  }
  n = pBuffer.CumulativeUnderrun;
  if ((n < 0) && (underrun < MIN_int32_T - n)) {
    n = MIN_int32_T;
  } else if ((n > 0) && (underrun > MAX_int32_T - n)) {
    n = MAX_int32_T;
  } else {
    n += underrun;
  }
  pBuffer.CumulativeUnderrun = n;
  if (underrun != 0) {
    pBuffer.ReadPointer = yk;
  } else {
    pBuffer.ReadPointer = c;
  }
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
  array<int, 2U> b_y;
  array<int, 2U> readIdx;
  array<int, 2U> y;
  double d;
  int c;
  int i;
  int numRowsCast;
  int overlapCast;
  int overlapUnderrun;
  int q0;
  int qY;
  int rPtr;
  int underrun;
  int wPtr_tmp;
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
    g_rtErrorWithMessageID("number of rows", ab_emlrtRTEI.fName,
                           ab_emlrtRTEI.lineNo);
  }
  if (std::isinf(numRows) || std::isnan(numRows)) {
    c_rtErrorWithMessageID("number of rows", v_emlrtRTEI.fName,
                           v_emlrtRTEI.lineNo);
  }
  if (!(std::floor(numRows) == numRows)) {
    f_rtErrorWithMessageID("number of rows", y_emlrtRTEI.fName,
                           y_emlrtRTEI.lineNo);
  }
  if (numRows > 49620.0) {
    x_rtErrorWithMessageID(nb_emlrtRTEI.fName, nb_emlrtRTEI.lineNo);
  }
  if (overlap < 0.0) {
    g_rtErrorWithMessageID("overlap", ab_emlrtRTEI.fName, ab_emlrtRTEI.lineNo);
  }
  if (std::isinf(overlap) || std::isnan(overlap)) {
    c_rtErrorWithMessageID("overlap", v_emlrtRTEI.fName, v_emlrtRTEI.lineNo);
  }
  if (!(std::floor(overlap) == overlap)) {
    f_rtErrorWithMessageID("overlap", y_emlrtRTEI.fName, y_emlrtRTEI.lineNo);
  }
  if (overlap > numRows) {
    ab_rtErrorWithMessageID(qb_emlrtRTEI.fName, qb_emlrtRTEI.lineNo);
  }
  overlapCast = static_cast<int>(overlap);
  if (!pBuffer.AsyncBuffercgHelper_isInitialized) {
    y_rtErrorWithMessageID(ob_emlrtRTEI.fName, ob_emlrtRTEI.lineNo);
  }
  wPtr_tmp = pBuffer.WritePointer;
  underrun = 0;
  overlapUnderrun = 0;
  q0 = pBuffer.ReadPointer;
  if (q0 > 2147483646) {
    rPtr = MAX_int32_T;
  } else {
    rPtr = q0 + 1;
  }
  if (rPtr > 49621) {
    rPtr = 1;
  }
  if ((wPtr_tmp < 1) || (wPtr_tmp > 49621) || (rPtr < 1) ||
      (numRowsCast > 49621)) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  if (overlapCast == 0) {
    c = (rPtr + numRowsCast) - 1;
    if (c > 49621) {
      c -= 49621;
      eml_integer_colon_dispatcher(rPtr, y);
      b_eml_integer_colon_dispatcher(c, b_y);
      readIdx.set_size(1, y.size(1) + b_y.size(1));
      q0 = y.size(1);
      for (i = 0; i < q0; i++) {
        readIdx[i] = y[i];
      }
      q0 = b_y.size(1);
      for (i = 0; i < q0; i++) {
        readIdx[i + y.size(1)] = b_y[i];
      }
      if (rPtr <= wPtr_tmp) {
        underrun = (c - wPtr_tmp) + 49622;
      } else if (wPtr_tmp <= c) {
        underrun = (c - wPtr_tmp) + 1;
      }
    } else {
      eml_integer_colon_dispatcher(rPtr, c, readIdx);
      if ((rPtr <= wPtr_tmp) && (wPtr_tmp <= c)) {
        underrun = (c - wPtr_tmp) + 1;
      }
    }
  } else {
    overlapCast = rPtr - overlapCast;
    if ((overlapCast < 0) && (numRowsCast < MIN_int32_T - overlapCast)) {
      qY = MIN_int32_T;
    } else if ((overlapCast > 0) && (numRowsCast > MAX_int32_T - overlapCast)) {
      qY = MAX_int32_T;
    } else {
      qY = overlapCast + numRowsCast;
    }
    if (qY < -2147483647) {
      qY = MIN_int32_T;
    } else {
      qY--;
    }
    c = qY;
    if (overlapCast < 1) {
      eml_integer_colon_dispatcher(overlapCast + 49621, y);
      b_eml_integer_colon_dispatcher(qY, b_y);
      readIdx.set_size(1, y.size(1) + b_y.size(1));
      q0 = y.size(1);
      for (i = 0; i < q0; i++) {
        readIdx[i] = y[i];
      }
      q0 = b_y.size(1);
      for (i = 0; i < q0; i++) {
        readIdx[i + y.size(1)] = b_y[i];
      }
      if ((rPtr <= wPtr_tmp) && (wPtr_tmp <= qY)) {
        underrun = (qY - wPtr_tmp) + 1;
      } else if (wPtr_tmp < rPtr) {
        overlapUnderrun = (wPtr_tmp - overlapCast) + 1;
      } else if (wPtr_tmp > overlapCast + 49621) {
        overlapUnderrun = (wPtr_tmp - overlapCast) - 49620;
      }
    } else if (qY > 49621) {
      c = qY - 49621;
      eml_integer_colon_dispatcher(overlapCast, y);
      b_eml_integer_colon_dispatcher(qY - 49621, b_y);
      readIdx.set_size(1, y.size(1) + b_y.size(1));
      q0 = y.size(1);
      for (i = 0; i < q0; i++) {
        readIdx[i] = y[i];
      }
      q0 = b_y.size(1);
      for (i = 0; i < q0; i++) {
        readIdx[i + y.size(1)] = b_y[i];
      }
      if (rPtr <= wPtr_tmp) {
        underrun = (qY - wPtr_tmp) + 1;
      } else if (wPtr_tmp <= qY - 49621) {
        underrun = (qY - wPtr_tmp) - 49620;
      } else if ((overlapCast < wPtr_tmp) && (wPtr_tmp < rPtr)) {
        overlapUnderrun = (wPtr_tmp - overlapCast) + 1;
      }
    } else {
      eml_integer_colon_dispatcher(overlapCast, qY, readIdx);
      if ((rPtr <= wPtr_tmp) && (wPtr_tmp <= qY)) {
        underrun = (qY - wPtr_tmp) + 1;
      } else if ((overlapCast <= wPtr_tmp) && (wPtr_tmp < rPtr)) {
        overlapUnderrun = (wPtr_tmp - overlapCast) + 1;
      }
    }
  }
  b_out.set_size(readIdx.size(1));
  q0 = readIdx.size(1);
  for (i = 0; i < q0; i++) {
    if ((readIdx[i] < 1) || (readIdx[i] > 49621)) {
      rtDynamicBoundsError(readIdx[i], 1, 49621, &y_emlrtBCI);
    }
    b_out[i].re = pBuffer.Cache[readIdx[i] - 1].re;
    if ((readIdx[i] < 1) || (readIdx[i] > 49621)) {
      rtDynamicBoundsError(readIdx[i], 1, 49621, &y_emlrtBCI);
    }
    b_out[i].im = pBuffer.Cache[readIdx[i] - 1].im;
  }
  if (underrun != 0) {
    if ((numRowsCast >= 0) && (underrun < numRowsCast - MAX_int32_T)) {
      qY = MAX_int32_T;
    } else if ((numRowsCast < 0) && (underrun > numRowsCast - MIN_int32_T)) {
      qY = MIN_int32_T;
    } else {
      qY = numRowsCast - underrun;
    }
    if (qY + 1 > numRowsCast) {
      qY = 0;
      i = 0;
    } else {
      if ((qY + 1 < 1) || (qY + 1 > readIdx.size(1))) {
        rtDynamicBoundsError(qY + 1, 1, readIdx.size(1), &x_emlrtBCI);
      }
      if ((numRowsCast < 1) || (numRowsCast > readIdx.size(1))) {
        rtDynamicBoundsError(numRowsCast, 1, readIdx.size(1), &w_emlrtBCI);
      }
      i = numRowsCast;
    }
    if (underrun < 0) {
      rtNonNegativeError(static_cast<double>(underrun), &o_emlrtDCI);
    }
    i -= qY;
    rtSubAssignSizeCheck(&i, 1, &underrun, 1, &e_emlrtECI);
    for (i = 0; i < underrun; i++) {
      overlapCast = qY + i;
      b_out[overlapCast].re = 0.0F;
      b_out[overlapCast].im = 0.0F;
    }
  } else if (overlapUnderrun != 0) {
    if (overlapUnderrun == numRowsCast) {
      if (overlapUnderrun < 0) {
        rtNonNegativeError(static_cast<double>(overlapUnderrun), &q_emlrtDCI);
      }
      b_out.set_size(overlapUnderrun);
      for (i = 0; i < overlapUnderrun; i++) {
        b_out[i].re = 0.0F;
        b_out[i].im = 0.0F;
      }
    } else {
      if (overlapUnderrun < 1) {
        i = 0;
      } else {
        if (readIdx.size(1) < 1) {
          rtDynamicBoundsError(1, 1, readIdx.size(1), &bb_emlrtBCI);
        }
        if (overlapUnderrun > readIdx.size(1)) {
          rtDynamicBoundsError(overlapUnderrun, 1, readIdx.size(1),
                               &ab_emlrtBCI);
        }
        i = overlapUnderrun;
      }
      if (overlapUnderrun < 0) {
        rtNonNegativeError(static_cast<double>(overlapUnderrun), &p_emlrtDCI);
      }
      rtSubAssignSizeCheck(&i, 1, &overlapUnderrun, 1, &f_emlrtECI);
      for (i = 0; i < overlapUnderrun; i++) {
        b_out[i].re = 0.0F;
        b_out[i].im = 0.0F;
      }
    }
  }
  if (b_out.size(0) != numRowsCast) {
    h_rtErrorWithMessageID(pb_emlrtRTEI.fName, pb_emlrtRTEI.lineNo);
  }
  out.set_size(b_out.size(0));
  q0 = b_out.size(0);
  for (i = 0; i < q0; i++) {
    out[i] = b_out[i];
  }
  q0 = pBuffer.CumulativeUnderrun;
  if ((q0 < 0) && (underrun < MIN_int32_T - q0)) {
    qY = MIN_int32_T;
  } else if ((q0 > 0) && (underrun > MAX_int32_T - q0)) {
    qY = MAX_int32_T;
  } else {
    qY = q0 + underrun;
  }
  pBuffer.CumulativeUnderrun = qY;
  if (underrun != 0) {
    pBuffer.ReadPointer = wPtr_tmp - 1;
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
  array<int, 2U> b_y;
  array<int, 2U> readIdx;
  array<int, 2U> y;
  double d;
  int c;
  int i;
  int loop_ub;
  int numRowsCast;
  int overlapCast;
  int overlapUnderrun;
  int q0;
  int rPtr;
  int underrun;
  int wPtr_tmp;
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
    g_rtErrorWithMessageID("number of rows", ab_emlrtRTEI.fName,
                           ab_emlrtRTEI.lineNo);
  }
  if (std::isinf(numRows) || std::isnan(numRows)) {
    c_rtErrorWithMessageID("number of rows", v_emlrtRTEI.fName,
                           v_emlrtRTEI.lineNo);
  }
  if (!(std::floor(numRows) == numRows)) {
    f_rtErrorWithMessageID("number of rows", y_emlrtRTEI.fName,
                           y_emlrtRTEI.lineNo);
  }
  if (numRows > 49620.0) {
    x_rtErrorWithMessageID(nb_emlrtRTEI.fName, nb_emlrtRTEI.lineNo);
  }
  if (overlap < 0.0) {
    g_rtErrorWithMessageID("overlap", ab_emlrtRTEI.fName, ab_emlrtRTEI.lineNo);
  }
  if (std::isinf(overlap) || std::isnan(overlap)) {
    c_rtErrorWithMessageID("overlap", v_emlrtRTEI.fName, v_emlrtRTEI.lineNo);
  }
  if (!(std::floor(overlap) == overlap)) {
    f_rtErrorWithMessageID("overlap", y_emlrtRTEI.fName, y_emlrtRTEI.lineNo);
  }
  if (overlap > numRows) {
    ab_rtErrorWithMessageID(qb_emlrtRTEI.fName, qb_emlrtRTEI.lineNo);
  }
  overlapCast = static_cast<int>(overlap);
  if (!pBuffer.AsyncBuffercgHelper_isInitialized) {
    y_rtErrorWithMessageID(ob_emlrtRTEI.fName, ob_emlrtRTEI.lineNo);
  }
  wPtr_tmp = pBuffer.WritePointer;
  underrun = 0;
  overlapUnderrun = 0;
  q0 = pBuffer.ReadPointer;
  if (q0 > 2147483646) {
    rPtr = MAX_int32_T;
  } else {
    rPtr = q0 + 1;
  }
  if (rPtr > 49621) {
    rPtr = 1;
  }
  if ((wPtr_tmp < 1) || (wPtr_tmp > 49621) || (rPtr < 1) ||
      (numRowsCast > 49621)) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  if (overlapCast == 0) {
    c = (rPtr + numRowsCast) - 1;
    if (c > 49621) {
      c -= 49621;
      eml_integer_colon_dispatcher(rPtr, y);
      b_eml_integer_colon_dispatcher(c, b_y);
      readIdx.set_size(1, y.size(1) + b_y.size(1));
      loop_ub = y.size(1);
      for (i = 0; i < loop_ub; i++) {
        readIdx[i] = y[i];
      }
      loop_ub = b_y.size(1);
      for (i = 0; i < loop_ub; i++) {
        readIdx[i + y.size(1)] = b_y[i];
      }
      if (rPtr <= wPtr_tmp) {
        underrun = (c - wPtr_tmp) + 49622;
      } else if (wPtr_tmp <= c) {
        underrun = (c - wPtr_tmp) + 1;
      }
    } else {
      eml_integer_colon_dispatcher(rPtr, c, readIdx);
      if ((rPtr <= wPtr_tmp) && (wPtr_tmp <= c)) {
        underrun = (c - wPtr_tmp) + 1;
      }
    }
  } else {
    overlapCast = rPtr - overlapCast;
    if ((overlapCast < 0) && (numRowsCast < MIN_int32_T - overlapCast)) {
      q0 = MIN_int32_T;
    } else if ((overlapCast > 0) && (numRowsCast > MAX_int32_T - overlapCast)) {
      q0 = MAX_int32_T;
    } else {
      q0 = overlapCast + numRowsCast;
    }
    if (q0 < -2147483647) {
      q0 = MIN_int32_T;
    } else {
      q0--;
    }
    c = q0;
    if (overlapCast < 1) {
      eml_integer_colon_dispatcher(overlapCast + 49621, y);
      b_eml_integer_colon_dispatcher(q0, b_y);
      readIdx.set_size(1, y.size(1) + b_y.size(1));
      loop_ub = y.size(1);
      for (i = 0; i < loop_ub; i++) {
        readIdx[i] = y[i];
      }
      loop_ub = b_y.size(1);
      for (i = 0; i < loop_ub; i++) {
        readIdx[i + y.size(1)] = b_y[i];
      }
      if ((rPtr <= wPtr_tmp) && (wPtr_tmp <= q0)) {
        underrun = (q0 - wPtr_tmp) + 1;
      } else if (wPtr_tmp < rPtr) {
        overlapUnderrun = (wPtr_tmp - overlapCast) + 1;
      } else if (wPtr_tmp > overlapCast + 49621) {
        overlapUnderrun = (wPtr_tmp - overlapCast) - 49620;
      }
    } else if (q0 > 49621) {
      c = q0 - 49621;
      eml_integer_colon_dispatcher(overlapCast, y);
      b_eml_integer_colon_dispatcher(q0 - 49621, b_y);
      readIdx.set_size(1, y.size(1) + b_y.size(1));
      loop_ub = y.size(1);
      for (i = 0; i < loop_ub; i++) {
        readIdx[i] = y[i];
      }
      loop_ub = b_y.size(1);
      for (i = 0; i < loop_ub; i++) {
        readIdx[i + y.size(1)] = b_y[i];
      }
      if (rPtr <= wPtr_tmp) {
        underrun = (q0 - wPtr_tmp) + 1;
      } else if (wPtr_tmp <= q0 - 49621) {
        underrun = (q0 - wPtr_tmp) - 49620;
      } else if ((overlapCast < wPtr_tmp) && (wPtr_tmp < rPtr)) {
        overlapUnderrun = (wPtr_tmp - overlapCast) + 1;
      }
    } else {
      eml_integer_colon_dispatcher(overlapCast, q0, readIdx);
      if ((rPtr <= wPtr_tmp) && (wPtr_tmp <= q0)) {
        underrun = (q0 - wPtr_tmp) + 1;
      } else if ((overlapCast <= wPtr_tmp) && (wPtr_tmp < rPtr)) {
        overlapUnderrun = (wPtr_tmp - overlapCast) + 1;
      }
    }
  }
  b_out.set_size(readIdx.size(1));
  loop_ub = readIdx.size(1);
  for (i = 0; i < loop_ub; i++) {
    if ((readIdx[i] < 1) || (readIdx[i] > 49621)) {
      rtDynamicBoundsError(readIdx[i], 1, 49621, &y_emlrtBCI);
    }
    b_out[i] = pBuffer.Cache[readIdx[i] - 1];
  }
  if (underrun != 0) {
    if ((numRowsCast >= 0) && (underrun < numRowsCast - MAX_int32_T)) {
      q0 = MAX_int32_T;
    } else if ((numRowsCast < 0) && (underrun > numRowsCast - MIN_int32_T)) {
      q0 = MIN_int32_T;
    } else {
      q0 = numRowsCast - underrun;
    }
    if (q0 + 1 > numRowsCast) {
      q0 = 0;
      i = 0;
    } else {
      if ((q0 + 1 < 1) || (q0 + 1 > readIdx.size(1))) {
        rtDynamicBoundsError(q0 + 1, 1, readIdx.size(1), &x_emlrtBCI);
      }
      if ((numRowsCast < 1) || (numRowsCast > readIdx.size(1))) {
        rtDynamicBoundsError(numRowsCast, 1, readIdx.size(1), &w_emlrtBCI);
      }
      i = numRowsCast;
    }
    if (underrun < 0) {
      rtNonNegativeError(static_cast<double>(underrun), &o_emlrtDCI);
    }
    i -= q0;
    rtSubAssignSizeCheck(&i, 1, &underrun, 1, &e_emlrtECI);
    for (i = 0; i < underrun; i++) {
      b_out[q0 + i] = 0.0;
    }
  } else if (overlapUnderrun != 0) {
    if (overlapUnderrun == numRowsCast) {
      if (overlapUnderrun < 0) {
        rtNonNegativeError(static_cast<double>(overlapUnderrun), &q_emlrtDCI);
      }
      b_out.set_size(overlapUnderrun);
      for (i = 0; i < overlapUnderrun; i++) {
        b_out[i] = 0.0;
      }
    } else {
      if (overlapUnderrun < 1) {
        i = 0;
      } else {
        if (readIdx.size(1) < 1) {
          rtDynamicBoundsError(1, 1, readIdx.size(1), &bb_emlrtBCI);
        }
        if (overlapUnderrun > readIdx.size(1)) {
          rtDynamicBoundsError(overlapUnderrun, 1, readIdx.size(1),
                               &ab_emlrtBCI);
        }
        i = overlapUnderrun;
      }
      if (overlapUnderrun < 0) {
        rtNonNegativeError(static_cast<double>(overlapUnderrun), &p_emlrtDCI);
      }
      rtSubAssignSizeCheck(&i, 1, &overlapUnderrun, 1, &f_emlrtECI);
      for (i = 0; i < overlapUnderrun; i++) {
        b_out[i] = 0.0;
      }
    }
  }
  if (b_out.size(0) != numRowsCast) {
    h_rtErrorWithMessageID(pb_emlrtRTEI.fName, pb_emlrtRTEI.lineNo);
  }
  out.set_size(b_out.size(0));
  loop_ub = b_out.size(0);
  for (i = 0; i < loop_ub; i++) {
    out[i] = b_out[i];
  }
  q0 = pBuffer.CumulativeUnderrun;
  if ((q0 < 0) && (underrun < MIN_int32_T - q0)) {
    q0 = MIN_int32_T;
  } else if ((q0 > 0) && (underrun > MAX_int32_T - q0)) {
    q0 = MAX_int32_T;
  } else {
    q0 += underrun;
  }
  pBuffer.CumulativeUnderrun = q0;
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
    i_rtErrorWithMessageID("reset", kb_emlrtRTEI.fName, kb_emlrtRTEI.lineNo);
  }
  if (pBuffer.isInitialized == 1) {
    pBuffer.ReadPointer = 1;
    pBuffer.WritePointer = 2;
    pBuffer.CumulativeOverrun = 0;
    pBuffer.CumulativeUnderrun = 0;
    std::memset(&pBuffer.Cache[0], 0, 49621U * sizeof(creal32_T));
  }
}

//
// Arguments    : void
// Return Type  : void
//
void b_AsyncBuffer::reset()
{
  static rtRunTimeErrorInfo qc_emlrtRTEI{
      1,                 // lineNo
      "SystemCore/reset" // fName
  };
  if (pBuffer.isInitialized == 2) {
    i_rtErrorWithMessageID("reset", qc_emlrtRTEI.fName, qc_emlrtRTEI.lineNo);
  }
  if (pBuffer.isInitialized == 1) {
    pBuffer.ReadPointer = 1;
    pBuffer.WritePointer = 2;
    pBuffer.CumulativeOverrun = 0;
    pBuffer.CumulativeUnderrun = 0;
    std::memset(&pBuffer.Cache[0], 0, 49621U * sizeof(double));
  }
}

//
// Arguments    : const creal32_T in[4096]
// Return Type  : void
//
void AsyncBuffer::write(const creal32_T in[4096])
{
  array<int, 2U> b_y;
  array<int, 2U> bc;
  array<int, 2U> y;
  array<unsigned short, 1U> r;
  int c;
  int n;
  int qY;
  int rPtr;
  int wPtr;
  int yk;
  if (pBuffer.isInitialized == 2) {
    i_rtErrorWithMessageID("step", kb_emlrtRTEI.fName, kb_emlrtRTEI.lineNo);
  }
  if (pBuffer.isInitialized != 1) {
    pBuffer.isSetupComplete = false;
    if (pBuffer.isInitialized != 0) {
      j_rtErrorWithMessageID("setup", kb_emlrtRTEI.fName, kb_emlrtRTEI.lineNo);
    }
    pBuffer.isInitialized = 1;
    if ((pBuffer.NumChannels != -1) && (pBuffer.NumChannels != 1)) {
      w_rtErrorWithMessageID(lb_emlrtRTEI.fName, lb_emlrtRTEI.lineNo);
    }
    pBuffer.NumChannels = 1;
    pBuffer.AsyncBuffercgHelper_isInitialized = true;
    pBuffer.isSetupComplete = true;
    pBuffer.ReadPointer = 1;
    pBuffer.WritePointer = 2;
    pBuffer.CumulativeOverrun = 0;
    pBuffer.CumulativeUnderrun = 0;
    std::memset(&pBuffer.Cache[0], 0, 49621U * sizeof(creal32_T));
  }
  wPtr = pBuffer.WritePointer;
  rPtr = pBuffer.ReadPointer;
  qY = 0;
  if ((wPtr < 1) || (wPtr > 49621)) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  c = wPtr + 4095;
  if (wPtr + 4095 > 49621) {
    c = wPtr - 45526;
    n = 49622 - wPtr;
    y.set_size(1, n);
    y[0] = wPtr;
    yk = wPtr;
    for (int k{2}; k <= n; k++) {
      yk++;
      y[k - 1] = yk;
    }
    if (wPtr - 45526 < 1) {
      n = 0;
    } else {
      n = wPtr - 45526;
    }
    b_y.set_size(1, n);
    if (n > 0) {
      b_y[0] = 1;
      yk = 1;
      for (int k{2}; k <= n; k++) {
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
      qY = (wPtr - rPtr) + 4096;
    } else if (rPtr <= wPtr - 45526) {
      if ((wPtr - 45526 >= 0) && (rPtr < wPtr + 2147438123)) {
        qY = MAX_int32_T;
      } else if ((wPtr - 45526 < 0) && (rPtr > wPtr + 2147438122)) {
        qY = MIN_int32_T;
      } else {
        qY = (wPtr - rPtr) - 45526;
      }
      if (qY > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY++;
      }
    }
  } else {
    eml_integer_colon_dispatcher(wPtr, wPtr + 4095, bc);
    if ((wPtr <= rPtr) && (rPtr <= wPtr + 4095)) {
      qY = (wPtr - rPtr) + 4096;
    }
  }
  r.set_size(bc.size(1));
  n = bc.size(1);
  for (yk = 0; yk < n; yk++) {
    if ((static_cast<unsigned short>(bc[yk]) < 1) ||
        (static_cast<unsigned short>(bc[yk]) > 49621)) {
      rtDynamicBoundsError(
          static_cast<int>(static_cast<unsigned short>(bc[yk])), 1, 49621,
          &v_emlrtBCI);
    }
    r[yk] =
        static_cast<unsigned short>(static_cast<unsigned short>(bc[yk]) - 1U);
  }
  yk = 4096;
  rtSubAssignSizeCheck(r.size(), 1, &yk, 1, &d_emlrtECI);
  n = r.size(0);
  for (yk = 0; yk < n; yk++) {
    pBuffer.Cache[r[yk]] = in[yk];
  }
  if (c + 1 > 49621) {
    wPtr = 1;
  } else {
    wPtr = c + 1;
  }
  if (qY != 0) {
    rPtr = wPtr;
  }
  n = pBuffer.CumulativeOverrun;
  if ((n < 0) && (qY < MIN_int32_T - n)) {
    qY = MIN_int32_T;
  } else if ((n > 0) && (qY > MAX_int32_T - n)) {
    qY = MAX_int32_T;
  } else {
    qY += n;
  }
  pBuffer.CumulativeOverrun = qY;
  pBuffer.WritePointer = wPtr;
  pBuffer.ReadPointer = rPtr;
}

//
// Arguments    : const double in[4096]
// Return Type  : void
//
void b_AsyncBuffer::write(const double in[4096])
{
  static rtRunTimeErrorInfo qc_emlrtRTEI{
      1,                 // lineNo
      "SystemCore/setup" // fName
  };
  array<int, 2U> b_y;
  array<int, 2U> bc;
  array<int, 2U> y;
  array<unsigned short, 1U> r;
  int c;
  int n;
  int qY;
  int rPtr;
  int wPtr;
  int yk;
  if (pBuffer.isInitialized == 2) {
    i_rtErrorWithMessageID("step", kb_emlrtRTEI.fName, kb_emlrtRTEI.lineNo);
  }
  if (pBuffer.isInitialized != 1) {
    pBuffer.isSetupComplete = false;
    if (pBuffer.isInitialized != 0) {
      j_rtErrorWithMessageID("setup", qc_emlrtRTEI.fName, qc_emlrtRTEI.lineNo);
    }
    pBuffer.isInitialized = 1;
    if ((pBuffer.NumChannels != -1) && (pBuffer.NumChannels != 1)) {
      w_rtErrorWithMessageID(lb_emlrtRTEI.fName, lb_emlrtRTEI.lineNo);
    }
    pBuffer.NumChannels = 1;
    pBuffer.AsyncBuffercgHelper_isInitialized = true;
    pBuffer.isSetupComplete = true;
    pBuffer.ReadPointer = 1;
    pBuffer.WritePointer = 2;
    pBuffer.CumulativeOverrun = 0;
    pBuffer.CumulativeUnderrun = 0;
    std::memset(&pBuffer.Cache[0], 0, 49621U * sizeof(double));
  }
  wPtr = pBuffer.WritePointer;
  rPtr = pBuffer.ReadPointer;
  qY = 0;
  if ((wPtr < 1) || (wPtr > 49621)) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  c = wPtr + 4095;
  if (wPtr + 4095 > 49621) {
    c = wPtr - 45526;
    n = 49622 - wPtr;
    y.set_size(1, n);
    y[0] = wPtr;
    yk = wPtr;
    for (int k{2}; k <= n; k++) {
      yk++;
      y[k - 1] = yk;
    }
    if (wPtr - 45526 < 1) {
      n = 0;
    } else {
      n = wPtr - 45526;
    }
    b_y.set_size(1, n);
    if (n > 0) {
      b_y[0] = 1;
      yk = 1;
      for (int k{2}; k <= n; k++) {
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
      qY = (wPtr - rPtr) + 4096;
    } else if (rPtr <= wPtr - 45526) {
      if ((wPtr - 45526 >= 0) && (rPtr < wPtr + 2147438123)) {
        qY = MAX_int32_T;
      } else if ((wPtr - 45526 < 0) && (rPtr > wPtr + 2147438122)) {
        qY = MIN_int32_T;
      } else {
        qY = (wPtr - rPtr) - 45526;
      }
      if (qY > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY++;
      }
    }
  } else {
    eml_integer_colon_dispatcher(wPtr, wPtr + 4095, bc);
    if ((wPtr <= rPtr) && (rPtr <= wPtr + 4095)) {
      qY = (wPtr - rPtr) + 4096;
    }
  }
  r.set_size(bc.size(1));
  n = bc.size(1);
  for (yk = 0; yk < n; yk++) {
    if ((static_cast<unsigned short>(bc[yk]) < 1) ||
        (static_cast<unsigned short>(bc[yk]) > 49621)) {
      rtDynamicBoundsError(
          static_cast<int>(static_cast<unsigned short>(bc[yk])), 1, 49621,
          &v_emlrtBCI);
    }
    r[yk] =
        static_cast<unsigned short>(static_cast<unsigned short>(bc[yk]) - 1U);
  }
  yk = 4096;
  rtSubAssignSizeCheck(r.size(), 1, &yk, 1, &d_emlrtECI);
  n = r.size(0);
  for (yk = 0; yk < n; yk++) {
    pBuffer.Cache[r[yk]] = in[yk];
  }
  if (c + 1 > 49621) {
    wPtr = 1;
  } else {
    wPtr = c + 1;
  }
  if (qY != 0) {
    rPtr = wPtr;
  }
  n = pBuffer.CumulativeOverrun;
  if ((n < 0) && (qY < MIN_int32_T - n)) {
    qY = MIN_int32_T;
  } else if ((n > 0) && (qY > MAX_int32_T - n)) {
    qY = MAX_int32_T;
  } else {
    qY += n;
  }
  pBuffer.CumulativeOverrun = qY;
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
