//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: AsyncBuffercgHelper.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 09-Mar-2023 11:19:16
//

// Include Files
#include "AsyncBuffercgHelper.h"
#include "colon.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include <string.h>

// Variable Definitions
static rtRunTimeErrorInfo x_emlrtRTEI{
    473,                                        // lineNo
    "AsyncBuffercgHelper/ReadSamplesFromBuffer" // fName
};

static rtEqualityCheckInfo
    b_emlrtECI{
        -1,                                          // nDims
        462,                                         // lineNo
        17,                                          // colNo
        "AsyncBuffercgHelper/ReadSamplesFromBuffer", // fName
        "C:\\Program "
        "Files\\MATLAB\\toolbox\\dsp\\dsp\\+dsp\\+"
        "internal\\AsyncBuffercgHelper.m" // pName
    };

static rtBoundsCheckInfo
    b_emlrtBCI{
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
    c_emlrtBCI{
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
    emlrtDCI{
        463,                                         // lineNo
        27,                                          // colNo
        "AsyncBuffercgHelper/ReadSamplesFromBuffer", // fName
        "C:\\Program "
        "Files\\MATLAB\\toolbox\\dsp\\dsp\\+dsp\\+"
        "internal\\AsyncBuffercgHelper.m", // pName
        4                                  // checkKind
    };

static rtBoundsCheckInfo
    ab_emlrtBCI{
        1,                                           // iFirst
        5800321,                                     // iLast
        457,                                         // lineNo
        29,                                          // colNo
        "",                                          // aName
        "AsyncBuffercgHelper/ReadSamplesFromBuffer", // fName
        "C:\\Program "
        "Files\\MATLAB\\toolbox\\dsp\\dsp\\+dsp\\+"
        "internal\\AsyncBuffercgHelper.m", // pName
        0                                  // checkKind
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
    bb_emlrtBCI{
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
    cb_emlrtBCI{
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

// Function Definitions
//
// Arguments    : const c_AsyncBuffercgHelper *obj
//                int numRowsCast
//                ::coder::array<creal32_T, 1U> &out
//                int *underrun
//                int *c
// Return Type  : void
//
namespace coder {
namespace dsp {
namespace internal {
void c_AsyncBuffercgHelper::ReadSamplesFromBuffer(
    const c_AsyncBuffercgHelper *obj, int numRowsCast,
    ::coder::array<creal32_T, 1U> &out, int *underrun, int *c)
{
  static rtBoundsCheckInfo fb_emlrtBCI{
      1,                                           // iFirst
      600651,                                      // iLast
      457,                                         // lineNo
      29,                                          // colNo
      "",                                          // aName
      "AsyncBuffercgHelper/ReadSamplesFromBuffer", // fName
      "C:\\Program "
      "Files\\MATLAB\\toolbox\\dsp\\dsp\\+dsp\\+internal\\AsyncBuffercgHelper."
      "m", // pName
      0    // checkKind
  };
  array<int, 2U> b_y;
  array<int, 2U> c_y;
  array<int, 2U> y;
  int k;
  int n;
  int rPtr;
  int wPtr;
  int yk;
  wPtr = obj->WritePointer;
  *underrun = 0;
  n = obj->ReadPointer;
  if (n > 2147483646) {
    rPtr = MAX_int32_T;
  } else {
    rPtr = n + 1;
  }
  if (rPtr > 600651) {
    rPtr = 1;
  }
  if ((wPtr < 1) || (wPtr > 600651) || (rPtr < 1) || (numRowsCast > 600651)) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  *c = (rPtr + numRowsCast) - 1;
  if (*c > 600651) {
    *c -= 600651;
    n = 600652 - rPtr;
    b_y.set_size(1, 600652 - rPtr);
    b_y[0] = rPtr;
    yk = rPtr;
    for (k = 2; k <= n; k++) {
      yk++;
      b_y[k - 1] = yk;
    }
    c_y.set_size(1, *c);
    c_y[0] = 1;
    yk = 1;
    for (k = 2; k <= *c; k++) {
      yk++;
      c_y[k - 1] = yk;
    }
    y.set_size(1, b_y.size(1) + c_y.size(1));
    n = b_y.size(1);
    for (k = 0; k < n; k++) {
      y[k] = b_y[k];
    }
    n = c_y.size(1);
    for (k = 0; k < n; k++) {
      y[k + b_y.size(1)] = c_y[k];
    }
    if (rPtr <= wPtr) {
      *underrun = (*c - wPtr) + 600652;
    } else if (wPtr <= *c) {
      *underrun = (*c - wPtr) + 1;
    }
  } else {
    eml_integer_colon_dispatcher(rPtr, *c, y);
    if ((rPtr <= wPtr) && (wPtr <= *c)) {
      *underrun = (*c - wPtr) + 1;
    }
  }
  out.set_size(y.size(1));
  n = y.size(1);
  for (k = 0; k < n; k++) {
    if ((y[k] < 1) || (y[k] > 600651)) {
      rtDynamicBoundsError(y[k], 1, 600651, &fb_emlrtBCI);
    }
    out[k].re = obj->Cache[y[k] - 1].re;
    if ((y[k] < 1) || (y[k] > 600651)) {
      rtDynamicBoundsError(y[k], 1, 600651, &fb_emlrtBCI);
    }
    out[k].im = obj->Cache[y[k] - 1].im;
  }
  if (*underrun != 0) {
    if ((numRowsCast >= 0) && (*underrun < numRowsCast - MAX_int32_T)) {
      n = MAX_int32_T;
    } else if ((numRowsCast < 0) && (*underrun > numRowsCast - MIN_int32_T)) {
      n = MIN_int32_T;
    } else {
      n = numRowsCast - *underrun;
    }
    if (n + 1 > numRowsCast) {
      n = 0;
      k = 0;
    } else {
      if ((n + 1 < 1) || (n + 1 > y.size(1))) {
        rtDynamicBoundsError(n + 1, 1, y.size(1), &c_emlrtBCI);
      }
      if ((numRowsCast < 1) || (numRowsCast > y.size(1))) {
        rtDynamicBoundsError(numRowsCast, 1, y.size(1), &b_emlrtBCI);
      }
      k = numRowsCast;
    }
    if (*underrun < 0) {
      rtNonNegativeError(static_cast<double>(*underrun), &emlrtDCI);
    }
    k -= n;
    rtSubAssignSizeCheck(&k, 1, underrun, 1, &b_emlrtECI);
    for (k = 0; k < *underrun; k++) {
      yk = n + k;
      out[yk].re = 0.0F;
      out[yk].im = 0.0F;
    }
  }
  if (out.size(0) != numRowsCast) {
    i_rtErrorWithMessageID(x_emlrtRTEI.fName, x_emlrtRTEI.lineNo);
  }
}

//
// Arguments    : const AsyncBuffercgHelper *obj
//                int numRowsCast
//                ::coder::array<creal32_T, 1U> &out
//                int *underrun
//                int *c
// Return Type  : void
//
void AsyncBuffercgHelper::ReadSamplesFromBuffer(
    const AsyncBuffercgHelper *obj, int numRowsCast,
    ::coder::array<creal32_T, 1U> &out, int *underrun, int *c)
{
  array<int, 2U> b_y;
  array<int, 2U> readIdx;
  array<int, 2U> y;
  int k;
  int n;
  int rPtr;
  int wPtr;
  int yk;
  wPtr = obj->WritePointer;
  *underrun = 0;
  n = obj->ReadPointer;
  if (n > 2147483646) {
    rPtr = MAX_int32_T;
  } else {
    rPtr = n + 1;
  }
  if (rPtr > 5800321) {
    rPtr = 1;
  }
  if ((wPtr < 1) || (wPtr > 5800321) || (rPtr < 1) || (numRowsCast > 5800321)) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  *c = (rPtr + numRowsCast) - 1;
  if (*c > 5800321) {
    *c -= 5800321;
    if (rPtr > 5800321) {
      n = 0;
    } else {
      n = 5800322 - rPtr;
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
    b_y.set_size(1, *c);
    b_y[0] = 1;
    yk = 1;
    for (k = 2; k <= *c; k++) {
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
      *underrun = (*c - wPtr) + 5800322;
    } else if (wPtr <= *c) {
      *underrun = (*c - wPtr) + 1;
    }
  } else {
    eml_integer_colon_dispatcher(rPtr, *c, readIdx);
    if ((rPtr <= wPtr) && (wPtr <= *c)) {
      *underrun = (*c - wPtr) + 1;
    }
  }
  out.set_size(readIdx.size(1));
  n = readIdx.size(1);
  for (k = 0; k < n; k++) {
    if ((readIdx[k] < 1) || (readIdx[k] > 5800321)) {
      rtDynamicBoundsError(readIdx[k], 1, 5800321, &ab_emlrtBCI);
    }
    out[k].re = obj->Cache[readIdx[k] - 1].re;
    if ((readIdx[k] < 1) || (readIdx[k] > 5800321)) {
      rtDynamicBoundsError(readIdx[k], 1, 5800321, &ab_emlrtBCI);
    }
    out[k].im = obj->Cache[readIdx[k] - 1].im;
  }
  if (*underrun != 0) {
    if ((numRowsCast >= 0) && (*underrun < numRowsCast - MAX_int32_T)) {
      n = MAX_int32_T;
    } else if ((numRowsCast < 0) && (*underrun > numRowsCast - MIN_int32_T)) {
      n = MIN_int32_T;
    } else {
      n = numRowsCast - *underrun;
    }
    if (n + 1 > numRowsCast) {
      n = 0;
      k = 0;
    } else {
      if ((n + 1 < 1) || (n + 1 > readIdx.size(1))) {
        rtDynamicBoundsError(n + 1, 1, readIdx.size(1), &c_emlrtBCI);
      }
      if ((numRowsCast < 1) || (numRowsCast > readIdx.size(1))) {
        rtDynamicBoundsError(numRowsCast, 1, readIdx.size(1), &b_emlrtBCI);
      }
      k = numRowsCast;
    }
    if (*underrun < 0) {
      rtNonNegativeError(static_cast<double>(*underrun), &emlrtDCI);
    }
    k -= n;
    rtSubAssignSizeCheck(&k, 1, underrun, 1, &b_emlrtECI);
    for (k = 0; k < *underrun; k++) {
      yk = n + k;
      out[yk].re = 0.0F;
      out[yk].im = 0.0F;
    }
  }
  if (out.size(0) != numRowsCast) {
    i_rtErrorWithMessageID(x_emlrtRTEI.fName, x_emlrtRTEI.lineNo);
  }
}

//
// Arguments    : const b_AsyncBuffercgHelper *obj
//                int numRowsCast
//                ::coder::array<double, 1U> &out
//                int *underrun
//                int *c
// Return Type  : void
//
void b_AsyncBuffercgHelper::ReadSamplesFromBuffer(
    const b_AsyncBuffercgHelper *obj, int numRowsCast,
    ::coder::array<double, 1U> &out, int *underrun, int *c)
{
  array<int, 2U> b_y;
  array<int, 2U> readIdx;
  array<int, 2U> y;
  int n;
  int rPtr;
  int wPtr;
  int yk;
  wPtr = obj->WritePointer;
  *underrun = 0;
  n = obj->ReadPointer;
  if (n > 2147483646) {
    rPtr = MAX_int32_T;
  } else {
    rPtr = n + 1;
  }
  if (rPtr > 5800321) {
    rPtr = 1;
  }
  if ((wPtr < 1) || (wPtr > 5800321) || (rPtr < 1) || (numRowsCast > 5800321)) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  *c = (rPtr + numRowsCast) - 1;
  if (*c > 5800321) {
    *c -= 5800321;
    if (rPtr > 5800321) {
      n = 0;
    } else {
      n = 5800322 - rPtr;
    }
    y.set_size(1, n);
    if (n > 0) {
      y[0] = rPtr;
      yk = rPtr;
      for (int k{2}; k <= n; k++) {
        yk++;
        y[k - 1] = yk;
      }
    }
    b_y.set_size(1, *c);
    b_y[0] = 1;
    yk = 1;
    for (int k{2}; k <= *c; k++) {
      yk++;
      b_y[k - 1] = yk;
    }
    readIdx.set_size(1, y.size(1) + b_y.size(1));
    n = y.size(1);
    for (yk = 0; yk < n; yk++) {
      readIdx[yk] = y[yk];
    }
    n = b_y.size(1);
    for (yk = 0; yk < n; yk++) {
      readIdx[yk + y.size(1)] = b_y[yk];
    }
    if (rPtr <= wPtr) {
      *underrun = (*c - wPtr) + 5800322;
    } else if (wPtr <= *c) {
      *underrun = (*c - wPtr) + 1;
    }
  } else {
    eml_integer_colon_dispatcher(rPtr, *c, readIdx);
    if ((rPtr <= wPtr) && (wPtr <= *c)) {
      *underrun = (*c - wPtr) + 1;
    }
  }
  out.set_size(readIdx.size(1));
  n = readIdx.size(1);
  for (yk = 0; yk < n; yk++) {
    if ((readIdx[yk] < 1) || (readIdx[yk] > 5800321)) {
      rtDynamicBoundsError(readIdx[yk], 1, 5800321, &ab_emlrtBCI);
    }
    out[yk] = obj->Cache[readIdx[yk] - 1];
  }
  if (*underrun != 0) {
    if ((numRowsCast >= 0) && (*underrun < numRowsCast - MAX_int32_T)) {
      n = MAX_int32_T;
    } else if ((numRowsCast < 0) && (*underrun > numRowsCast - MIN_int32_T)) {
      n = MIN_int32_T;
    } else {
      n = numRowsCast - *underrun;
    }
    if (n + 1 > numRowsCast) {
      n = 0;
      yk = 0;
    } else {
      if ((n + 1 < 1) || (n + 1 > readIdx.size(1))) {
        rtDynamicBoundsError(n + 1, 1, readIdx.size(1), &c_emlrtBCI);
      }
      if ((numRowsCast < 1) || (numRowsCast > readIdx.size(1))) {
        rtDynamicBoundsError(numRowsCast, 1, readIdx.size(1), &b_emlrtBCI);
      }
      yk = numRowsCast;
    }
    if (*underrun < 0) {
      rtNonNegativeError(static_cast<double>(*underrun), &emlrtDCI);
    }
    yk -= n;
    rtSubAssignSizeCheck(&yk, 1, underrun, 1, &b_emlrtECI);
    for (yk = 0; yk < *underrun; yk++) {
      out[n + yk] = 0.0;
    }
  }
  if (out.size(0) != numRowsCast) {
    i_rtErrorWithMessageID(x_emlrtRTEI.fName, x_emlrtRTEI.lineNo);
  }
}

//
// Arguments    : void
// Return Type  : void
//
void c_AsyncBuffercgHelper::SystemCore_delete()
{
  release();
}

//
// Arguments    : void
// Return Type  : void
//
void b_AsyncBuffercgHelper::SystemCore_delete()
{
  release();
}

//
// Arguments    : void
// Return Type  : void
//
void AsyncBuffercgHelper::SystemCore_delete()
{
  release();
}

//
// Arguments    : void
// Return Type  : void
//
void c_AsyncBuffercgHelper::matlabCodegenDestructor()
{
  if (!matlabCodegenIsDeleted) {
    matlabCodegenIsDeleted = true;
    SystemCore_delete();
  }
}

//
// Arguments    : void
// Return Type  : void
//
void b_AsyncBuffercgHelper::matlabCodegenDestructor()
{
  if (!matlabCodegenIsDeleted) {
    matlabCodegenIsDeleted = true;
    SystemCore_delete();
  }
}

//
// Arguments    : void
// Return Type  : void
//
void AsyncBuffercgHelper::matlabCodegenDestructor()
{
  if (!matlabCodegenIsDeleted) {
    matlabCodegenIsDeleted = true;
    SystemCore_delete();
  }
}

//
// Arguments    : void
// Return Type  : void
//
void c_AsyncBuffercgHelper::release()
{
  if (isInitialized == 1) {
    isInitialized = 2;
    releaseWrapper();
  }
}

//
// Arguments    : void
// Return Type  : void
//
void b_AsyncBuffercgHelper::release()
{
  if (isInitialized == 1) {
    isInitialized = 2;
    releaseWrapper();
  }
}

//
// Arguments    : void
// Return Type  : void
//
void AsyncBuffercgHelper::release()
{
  if (isInitialized == 1) {
    isInitialized = 2;
    releaseWrapper();
  }
}

//
// Arguments    : void
// Return Type  : void
//
void c_AsyncBuffercgHelper::releaseImpl()
{
  ReadPointer = 1;
  WritePointer = 2;
  CumulativeOverrun = 0;
  CumulativeUnderrun = 0;
  AsyncBuffercgHelper_isInitialized = false;
  NumChannels = -1;
}

//
// Arguments    : void
// Return Type  : void
//
void b_AsyncBuffercgHelper::releaseImpl()
{
  ReadPointer = 1;
  WritePointer = 2;
  CumulativeOverrun = 0;
  CumulativeUnderrun = 0;
  AsyncBuffercgHelper_isInitialized = false;
  NumChannels = -1;
}

//
// Arguments    : void
// Return Type  : void
//
void AsyncBuffercgHelper::releaseImpl()
{
  ReadPointer = 1;
  WritePointer = 2;
  CumulativeOverrun = 0;
  CumulativeUnderrun = 0;
  AsyncBuffercgHelper_isInitialized = false;
  NumChannels = -1;
}

//
// Arguments    : void
// Return Type  : void
//
void c_AsyncBuffercgHelper::releaseWrapper()
{
  if (isSetupComplete) {
    releaseImpl();
  }
}

//
// Arguments    : void
// Return Type  : void
//
void b_AsyncBuffercgHelper::releaseWrapper()
{
  if (isSetupComplete) {
    releaseImpl();
  }
}

//
// Arguments    : void
// Return Type  : void
//
void AsyncBuffercgHelper::releaseWrapper()
{
  if (isSetupComplete) {
    releaseImpl();
  }
}

//
// Arguments    : const AsyncBuffercgHelper *obj
//                int numRowsCast
//                int overlapCast
//                ::coder::array<creal32_T, 1U> &out
//                int *underrun
//                int *overlapUnderrun
//                int *c
// Return Type  : void
//
void AsyncBuffercgHelper::ReadSamplesFromBuffer(
    const AsyncBuffercgHelper *obj, int numRowsCast, int overlapCast,
    ::coder::array<creal32_T, 1U> &out, int *underrun, int *overlapUnderrun,
    int *c)
{
  array<int, 2U> b_y;
  array<int, 2U> readIdx;
  array<int, 2U> y;
  int b_qY;
  int n;
  int q0;
  int qY;
  int rPtr;
  int wPtr;
  wPtr = obj->WritePointer;
  *underrun = 0;
  qY = 0;
  q0 = obj->ReadPointer;
  if (q0 > 2147483646) {
    rPtr = MAX_int32_T;
  } else {
    rPtr = q0 + 1;
  }
  if (rPtr > 5800321) {
    rPtr = 1;
  }
  if ((wPtr < 1) || (wPtr > 5800321) || (rPtr < 1) || (numRowsCast > 5800321)) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  if (overlapCast == 0) {
    *c = (rPtr + numRowsCast) - 1;
    if (*c > 5800321) {
      int yk;
      *c -= 5800321;
      if (rPtr > 5800321) {
        n = 0;
      } else {
        n = 5800322 - rPtr;
      }
      y.set_size(1, n);
      if (n > 0) {
        y[0] = rPtr;
        yk = rPtr;
        for (int k{2}; k <= n; k++) {
          yk++;
          y[k - 1] = yk;
        }
      }
      b_y.set_size(1, *c);
      b_y[0] = 1;
      yk = 1;
      for (int k{2}; k <= *c; k++) {
        yk++;
        b_y[k - 1] = yk;
      }
      readIdx.set_size(1, y.size(1) + b_y.size(1));
      q0 = y.size(1);
      for (n = 0; n < q0; n++) {
        readIdx[n] = y[n];
      }
      q0 = b_y.size(1);
      for (n = 0; n < q0; n++) {
        readIdx[n + y.size(1)] = b_y[n];
      }
      if (rPtr <= wPtr) {
        *underrun = (*c - wPtr) + 5800322;
      } else if (wPtr <= *c) {
        *underrun = (*c - wPtr) + 1;
      }
    } else {
      eml_integer_colon_dispatcher(rPtr, *c, readIdx);
      if ((rPtr <= wPtr) && (wPtr <= *c)) {
        *underrun = (*c - wPtr) + 1;
      }
    }
  } else {
    int c_qY;
    if (overlapCast < rPtr - MAX_int32_T) {
      b_qY = MAX_int32_T;
      c_qY = MAX_int32_T;
    } else {
      b_qY = rPtr - overlapCast;
      c_qY = rPtr - overlapCast;
    }
    if ((c_qY < 0) && (numRowsCast < MIN_int32_T - c_qY)) {
      c_qY = MIN_int32_T;
    } else if ((c_qY > 0) && (numRowsCast > MAX_int32_T - c_qY)) {
      c_qY = MAX_int32_T;
    } else {
      c_qY += numRowsCast;
    }
    if (c_qY < -2147483647) {
      c_qY = MIN_int32_T;
    } else {
      c_qY--;
    }
    *c = c_qY;
    if (b_qY < 1) {
      unsigned int d_qY;
      int yk;
      if (b_qY + 5800321 < 0) {
        d_qY = static_cast<unsigned int>(-b_qY);
      } else {
        d_qY = static_cast<unsigned int>(-b_qY);
      }
      n = static_cast<int>(d_qY) + 1;
      y.set_size(1, n);
      if (n > 0) {
        y[0] = b_qY + 5800321;
        yk = b_qY + 5800321;
        if (n > 2147483646) {
          check_forloop_overflow_error();
        }
        for (int k{2}; k <= n; k++) {
          yk++;
          y[k - 1] = yk;
        }
      }
      if (c_qY < 1) {
        n = 0;
      } else {
        n = c_qY;
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
      readIdx.set_size(1, y.size(1) + b_y.size(1));
      q0 = y.size(1);
      for (n = 0; n < q0; n++) {
        readIdx[n] = y[n];
      }
      q0 = b_y.size(1);
      for (n = 0; n < q0; n++) {
        readIdx[n + y.size(1)] = b_y[n];
      }
      if ((rPtr <= wPtr) && (wPtr <= c_qY)) {
        *underrun = (c_qY - wPtr) + 1;
      } else if (wPtr < rPtr) {
        if ((1 - b_qY < 0) && (wPtr < b_qY + MAX_int32_T)) {
          qY = MIN_int32_T;
        } else if ((1 - b_qY > 0) && (wPtr > b_qY + 2147483646)) {
          qY = MAX_int32_T;
        } else {
          qY = (wPtr - b_qY) + 1;
        }
      } else if (wPtr > b_qY + 5800321) {
        qY = (wPtr - b_qY) - 5800320;
      }
    } else if (c_qY > 5800321) {
      int yk;
      q0 = c_qY - 5800321;
      *c = c_qY - 5800321;
      if (b_qY > 5800321) {
        n = 0;
      } else {
        n = 5800322 - b_qY;
      }
      y.set_size(1, n);
      if (n > 0) {
        y[0] = b_qY;
        yk = b_qY;
        for (int k{2}; k <= n; k++) {
          yk++;
          y[k - 1] = yk;
        }
      }
      b_y.set_size(1, q0);
      b_y[0] = 1;
      yk = 1;
      for (int k{2}; k <= q0; k++) {
        yk++;
        b_y[k - 1] = yk;
      }
      readIdx.set_size(1, y.size(1) + b_y.size(1));
      q0 = y.size(1);
      for (n = 0; n < q0; n++) {
        readIdx[n] = y[n];
      }
      q0 = b_y.size(1);
      for (n = 0; n < q0; n++) {
        readIdx[n + y.size(1)] = b_y[n];
      }
      if (rPtr <= wPtr) {
        *underrun = (c_qY - wPtr) + 1;
      } else if (wPtr <= c_qY - 5800321) {
        *underrun = (c_qY - wPtr) - 5800320;
      } else if ((b_qY < wPtr) && (wPtr < rPtr)) {
        qY = (wPtr - b_qY) + 1;
      }
    } else {
      eml_integer_colon_dispatcher(b_qY, c_qY, readIdx);
      if ((rPtr <= wPtr) && (wPtr <= c_qY)) {
        *underrun = (c_qY - wPtr) + 1;
      } else if ((b_qY <= wPtr) && (wPtr < rPtr)) {
        qY = (wPtr - b_qY) + 1;
      }
    }
  }
  out.set_size(readIdx.size(1));
  q0 = readIdx.size(1);
  for (n = 0; n < q0; n++) {
    if ((readIdx[n] < 1) || (readIdx[n] > 5800321)) {
      rtDynamicBoundsError(readIdx[n], 1, 5800321, &ab_emlrtBCI);
    }
    out[n].re = obj->Cache[readIdx[n] - 1].re;
    if ((readIdx[n] < 1) || (readIdx[n] > 5800321)) {
      rtDynamicBoundsError(readIdx[n], 1, 5800321, &ab_emlrtBCI);
    }
    out[n].im = obj->Cache[readIdx[n] - 1].im;
  }
  if (*underrun != 0) {
    if ((numRowsCast >= 0) && (*underrun < numRowsCast - MAX_int32_T)) {
      b_qY = MAX_int32_T;
    } else if ((numRowsCast < 0) && (*underrun > numRowsCast - MIN_int32_T)) {
      b_qY = MIN_int32_T;
    } else {
      b_qY = numRowsCast - *underrun;
    }
    if (b_qY + 1 > numRowsCast) {
      b_qY = 0;
      n = 0;
    } else {
      if ((b_qY + 1 < 1) || (b_qY + 1 > readIdx.size(1))) {
        rtDynamicBoundsError(b_qY + 1, 1, readIdx.size(1), &c_emlrtBCI);
      }
      if ((numRowsCast < 1) || (numRowsCast > readIdx.size(1))) {
        rtDynamicBoundsError(numRowsCast, 1, readIdx.size(1), &b_emlrtBCI);
      }
      n = numRowsCast;
    }
    if (*underrun < 0) {
      rtNonNegativeError(static_cast<double>(*underrun), &emlrtDCI);
    }
    n -= b_qY;
    rtSubAssignSizeCheck(&n, 1, underrun, 1, &b_emlrtECI);
    for (n = 0; n < *underrun; n++) {
      q0 = b_qY + n;
      out[q0].re = 0.0F;
      out[q0].im = 0.0F;
    }
  } else if (qY != 0) {
    if (qY == numRowsCast) {
      if (qY < 0) {
        rtNonNegativeError(static_cast<double>(qY), &q_emlrtDCI);
      }
      out.set_size(qY);
      for (n = 0; n < qY; n++) {
        out[n].re = 0.0F;
        out[n].im = 0.0F;
      }
    } else {
      if (qY < 1) {
        n = 0;
      } else {
        if (readIdx.size(1) < 1) {
          rtDynamicBoundsError(1, 1, readIdx.size(1), &cb_emlrtBCI);
        }
        if (qY > readIdx.size(1)) {
          rtDynamicBoundsError(qY, 1, readIdx.size(1), &bb_emlrtBCI);
        }
        n = qY;
      }
      if (qY < 0) {
        rtNonNegativeError(static_cast<double>(qY), &p_emlrtDCI);
      }
      rtSubAssignSizeCheck(&n, 1, &qY, 1, &f_emlrtECI);
      for (n = 0; n < qY; n++) {
        out[n].re = 0.0F;
        out[n].im = 0.0F;
      }
    }
  }
  if (out.size(0) != numRowsCast) {
    i_rtErrorWithMessageID(x_emlrtRTEI.fName, x_emlrtRTEI.lineNo);
  }
  *overlapUnderrun = qY;
}

//
// Arguments    : const b_AsyncBuffercgHelper *obj
//                int numRowsCast
//                int overlapCast
//                ::coder::array<double, 1U> &out
//                int *underrun
//                int *overlapUnderrun
//                int *c
// Return Type  : void
//
void b_AsyncBuffercgHelper::ReadSamplesFromBuffer(
    const b_AsyncBuffercgHelper *obj, int numRowsCast, int overlapCast,
    ::coder::array<double, 1U> &out, int *underrun, int *overlapUnderrun,
    int *c)
{
  array<int, 2U> b_y;
  array<int, 2U> readIdx;
  array<int, 2U> y;
  int b_qY;
  int n;
  int q0;
  int qY;
  int rPtr;
  int wPtr;
  wPtr = obj->WritePointer;
  *underrun = 0;
  qY = 0;
  q0 = obj->ReadPointer;
  if (q0 > 2147483646) {
    rPtr = MAX_int32_T;
  } else {
    rPtr = q0 + 1;
  }
  if (rPtr > 5800321) {
    rPtr = 1;
  }
  if ((wPtr < 1) || (wPtr > 5800321) || (rPtr < 1) || (numRowsCast > 5800321)) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  if (overlapCast == 0) {
    *c = (rPtr + numRowsCast) - 1;
    if (*c > 5800321) {
      int yk;
      *c -= 5800321;
      if (rPtr > 5800321) {
        n = 0;
      } else {
        n = 5800322 - rPtr;
      }
      y.set_size(1, n);
      if (n > 0) {
        y[0] = rPtr;
        yk = rPtr;
        for (int k{2}; k <= n; k++) {
          yk++;
          y[k - 1] = yk;
        }
      }
      b_y.set_size(1, *c);
      b_y[0] = 1;
      yk = 1;
      for (int k{2}; k <= *c; k++) {
        yk++;
        b_y[k - 1] = yk;
      }
      readIdx.set_size(1, y.size(1) + b_y.size(1));
      q0 = y.size(1);
      for (n = 0; n < q0; n++) {
        readIdx[n] = y[n];
      }
      q0 = b_y.size(1);
      for (n = 0; n < q0; n++) {
        readIdx[n + y.size(1)] = b_y[n];
      }
      if (rPtr <= wPtr) {
        *underrun = (*c - wPtr) + 5800322;
      } else if (wPtr <= *c) {
        *underrun = (*c - wPtr) + 1;
      }
    } else {
      eml_integer_colon_dispatcher(rPtr, *c, readIdx);
      if ((rPtr <= wPtr) && (wPtr <= *c)) {
        *underrun = (*c - wPtr) + 1;
      }
    }
  } else {
    int c_qY;
    if (overlapCast < rPtr - MAX_int32_T) {
      b_qY = MAX_int32_T;
      c_qY = MAX_int32_T;
    } else {
      b_qY = rPtr - overlapCast;
      c_qY = rPtr - overlapCast;
    }
    if ((c_qY < 0) && (numRowsCast < MIN_int32_T - c_qY)) {
      c_qY = MIN_int32_T;
    } else if ((c_qY > 0) && (numRowsCast > MAX_int32_T - c_qY)) {
      c_qY = MAX_int32_T;
    } else {
      c_qY += numRowsCast;
    }
    if (c_qY < -2147483647) {
      c_qY = MIN_int32_T;
    } else {
      c_qY--;
    }
    *c = c_qY;
    if (b_qY < 1) {
      unsigned int d_qY;
      int yk;
      if (b_qY + 5800321 < 0) {
        d_qY = static_cast<unsigned int>(-b_qY);
      } else {
        d_qY = static_cast<unsigned int>(-b_qY);
      }
      n = static_cast<int>(d_qY) + 1;
      y.set_size(1, n);
      if (n > 0) {
        y[0] = b_qY + 5800321;
        yk = b_qY + 5800321;
        if (n > 2147483646) {
          check_forloop_overflow_error();
        }
        for (int k{2}; k <= n; k++) {
          yk++;
          y[k - 1] = yk;
        }
      }
      if (c_qY < 1) {
        n = 0;
      } else {
        n = c_qY;
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
      readIdx.set_size(1, y.size(1) + b_y.size(1));
      q0 = y.size(1);
      for (n = 0; n < q0; n++) {
        readIdx[n] = y[n];
      }
      q0 = b_y.size(1);
      for (n = 0; n < q0; n++) {
        readIdx[n + y.size(1)] = b_y[n];
      }
      if ((rPtr <= wPtr) && (wPtr <= c_qY)) {
        *underrun = (c_qY - wPtr) + 1;
      } else if (wPtr < rPtr) {
        if ((1 - b_qY < 0) && (wPtr < b_qY + MAX_int32_T)) {
          qY = MIN_int32_T;
        } else if ((1 - b_qY > 0) && (wPtr > b_qY + 2147483646)) {
          qY = MAX_int32_T;
        } else {
          qY = (wPtr - b_qY) + 1;
        }
      } else if (wPtr > b_qY + 5800321) {
        qY = (wPtr - b_qY) - 5800320;
      }
    } else if (c_qY > 5800321) {
      int yk;
      q0 = c_qY - 5800321;
      *c = c_qY - 5800321;
      if (b_qY > 5800321) {
        n = 0;
      } else {
        n = 5800322 - b_qY;
      }
      y.set_size(1, n);
      if (n > 0) {
        y[0] = b_qY;
        yk = b_qY;
        for (int k{2}; k <= n; k++) {
          yk++;
          y[k - 1] = yk;
        }
      }
      b_y.set_size(1, q0);
      b_y[0] = 1;
      yk = 1;
      for (int k{2}; k <= q0; k++) {
        yk++;
        b_y[k - 1] = yk;
      }
      readIdx.set_size(1, y.size(1) + b_y.size(1));
      q0 = y.size(1);
      for (n = 0; n < q0; n++) {
        readIdx[n] = y[n];
      }
      q0 = b_y.size(1);
      for (n = 0; n < q0; n++) {
        readIdx[n + y.size(1)] = b_y[n];
      }
      if (rPtr <= wPtr) {
        *underrun = (c_qY - wPtr) + 1;
      } else if (wPtr <= c_qY - 5800321) {
        *underrun = (c_qY - wPtr) - 5800320;
      } else if ((b_qY < wPtr) && (wPtr < rPtr)) {
        qY = (wPtr - b_qY) + 1;
      }
    } else {
      eml_integer_colon_dispatcher(b_qY, c_qY, readIdx);
      if ((rPtr <= wPtr) && (wPtr <= c_qY)) {
        *underrun = (c_qY - wPtr) + 1;
      } else if ((b_qY <= wPtr) && (wPtr < rPtr)) {
        qY = (wPtr - b_qY) + 1;
      }
    }
  }
  out.set_size(readIdx.size(1));
  q0 = readIdx.size(1);
  for (n = 0; n < q0; n++) {
    if ((readIdx[n] < 1) || (readIdx[n] > 5800321)) {
      rtDynamicBoundsError(readIdx[n], 1, 5800321, &ab_emlrtBCI);
    }
    out[n] = obj->Cache[readIdx[n] - 1];
  }
  if (*underrun != 0) {
    if ((numRowsCast >= 0) && (*underrun < numRowsCast - MAX_int32_T)) {
      b_qY = MAX_int32_T;
    } else if ((numRowsCast < 0) && (*underrun > numRowsCast - MIN_int32_T)) {
      b_qY = MIN_int32_T;
    } else {
      b_qY = numRowsCast - *underrun;
    }
    if (b_qY + 1 > numRowsCast) {
      b_qY = 0;
      n = 0;
    } else {
      if ((b_qY + 1 < 1) || (b_qY + 1 > readIdx.size(1))) {
        rtDynamicBoundsError(b_qY + 1, 1, readIdx.size(1), &c_emlrtBCI);
      }
      if ((numRowsCast < 1) || (numRowsCast > readIdx.size(1))) {
        rtDynamicBoundsError(numRowsCast, 1, readIdx.size(1), &b_emlrtBCI);
      }
      n = numRowsCast;
    }
    if (*underrun < 0) {
      rtNonNegativeError(static_cast<double>(*underrun), &emlrtDCI);
    }
    n -= b_qY;
    rtSubAssignSizeCheck(&n, 1, underrun, 1, &b_emlrtECI);
    for (n = 0; n < *underrun; n++) {
      out[b_qY + n] = 0.0;
    }
  } else if (qY != 0) {
    if (qY == numRowsCast) {
      if (qY < 0) {
        rtNonNegativeError(static_cast<double>(qY), &q_emlrtDCI);
      }
      out.set_size(qY);
      for (n = 0; n < qY; n++) {
        out[n] = 0.0;
      }
    } else {
      if (qY < 1) {
        n = 0;
      } else {
        if (readIdx.size(1) < 1) {
          rtDynamicBoundsError(1, 1, readIdx.size(1), &cb_emlrtBCI);
        }
        if (qY > readIdx.size(1)) {
          rtDynamicBoundsError(qY, 1, readIdx.size(1), &bb_emlrtBCI);
        }
        n = qY;
      }
      if (qY < 0) {
        rtNonNegativeError(static_cast<double>(qY), &p_emlrtDCI);
      }
      rtSubAssignSizeCheck(&n, 1, &qY, 1, &f_emlrtECI);
      for (n = 0; n < qY; n++) {
        out[n] = 0.0;
      }
    }
  }
  if (out.size(0) != numRowsCast) {
    i_rtErrorWithMessageID(x_emlrtRTEI.fName, x_emlrtRTEI.lineNo);
  }
  *overlapUnderrun = qY;
}

//
// Arguments    : void
// Return Type  : c_AsyncBuffercgHelper
//
c_AsyncBuffercgHelper::c_AsyncBuffercgHelper()
{
  matlabCodegenIsDeleted = true;
}

//
// Arguments    : void
// Return Type  : b_AsyncBuffercgHelper
//
b_AsyncBuffercgHelper::b_AsyncBuffercgHelper()
{
  matlabCodegenIsDeleted = true;
}

//
// Arguments    : void
// Return Type  : AsyncBuffercgHelper
//
AsyncBuffercgHelper::AsyncBuffercgHelper()
{
  matlabCodegenIsDeleted = true;
}

//
// Arguments    : void
// Return Type  : void
//
c_AsyncBuffercgHelper::~c_AsyncBuffercgHelper()
{
  matlabCodegenDestructor();
}

//
// Arguments    : void
// Return Type  : void
//
b_AsyncBuffercgHelper::~b_AsyncBuffercgHelper()
{
  matlabCodegenDestructor();
}

//
// Arguments    : void
// Return Type  : void
//
AsyncBuffercgHelper::~AsyncBuffercgHelper()
{
  matlabCodegenDestructor();
}

//
// Arguments    : int numRows
//                ::coder::array<creal32_T, 1U> &out
//                int *underrun
// Return Type  : void
//
void c_AsyncBuffercgHelper::read(int numRows,
                                 ::coder::array<creal32_T, 1U> &out,
                                 int *underrun)
{
  array<creal32_T, 1U> b_out;
  int c;
  int loop_ub;
  int qY;
  if (!AsyncBuffercgHelper_isInitialized) {
    p_rtErrorWithMessageID(w_emlrtRTEI.fName, w_emlrtRTEI.lineNo);
  }
  c_AsyncBuffercgHelper::ReadSamplesFromBuffer(this, numRows, b_out, underrun,
                                               &c);
  out.set_size(b_out.size(0));
  loop_ub = b_out.size(0);
  for (qY = 0; qY < loop_ub; qY++) {
    out[qY] = b_out[qY];
  }
  loop_ub = WritePointer;
  if (loop_ub < -2147483647) {
    qY = MIN_int32_T;
  } else {
    qY = loop_ub - 1;
  }
  loop_ub = CumulativeUnderrun;
  if ((loop_ub < 0) && (*underrun < MIN_int32_T - loop_ub)) {
    loop_ub = MIN_int32_T;
  } else if ((loop_ub > 0) && (*underrun > MAX_int32_T - loop_ub)) {
    loop_ub = MAX_int32_T;
  } else {
    loop_ub += *underrun;
  }
  CumulativeUnderrun = loop_ub;
  if (*underrun != 0) {
    ReadPointer = qY;
  } else {
    ReadPointer = c;
  }
}

//
// Arguments    : int numRows
//                ::coder::array<creal32_T, 1U> &out
//                int *underrun
// Return Type  : void
//
void AsyncBuffercgHelper::read(int numRows, ::coder::array<creal32_T, 1U> &out,
                               int *underrun)
{
  array<creal32_T, 1U> b_out;
  int c;
  int loop_ub;
  int qY;
  if (!AsyncBuffercgHelper_isInitialized) {
    p_rtErrorWithMessageID(w_emlrtRTEI.fName, w_emlrtRTEI.lineNo);
  }
  AsyncBuffercgHelper::ReadSamplesFromBuffer(this, numRows, b_out, underrun,
                                             &c);
  out.set_size(b_out.size(0));
  loop_ub = b_out.size(0);
  for (qY = 0; qY < loop_ub; qY++) {
    out[qY] = b_out[qY];
  }
  loop_ub = WritePointer;
  if (loop_ub < -2147483647) {
    qY = MIN_int32_T;
  } else {
    qY = loop_ub - 1;
  }
  loop_ub = CumulativeUnderrun;
  if ((loop_ub < 0) && (*underrun < MIN_int32_T - loop_ub)) {
    loop_ub = MIN_int32_T;
  } else if ((loop_ub > 0) && (*underrun > MAX_int32_T - loop_ub)) {
    loop_ub = MAX_int32_T;
  } else {
    loop_ub += *underrun;
  }
  CumulativeUnderrun = loop_ub;
  if (*underrun != 0) {
    ReadPointer = qY;
  } else {
    ReadPointer = c;
  }
}

//
// Arguments    : int numRows
//                ::coder::array<double, 1U> &out
//                int *underrun
// Return Type  : void
//
void b_AsyncBuffercgHelper::read(int numRows, ::coder::array<double, 1U> &out,
                                 int *underrun)
{
  array<double, 1U> b_out;
  int c;
  int loop_ub;
  int qY;
  if (!AsyncBuffercgHelper_isInitialized) {
    p_rtErrorWithMessageID(w_emlrtRTEI.fName, w_emlrtRTEI.lineNo);
  }
  b_AsyncBuffercgHelper::ReadSamplesFromBuffer(this, numRows, b_out, underrun,
                                               &c);
  out.set_size(b_out.size(0));
  loop_ub = b_out.size(0);
  for (qY = 0; qY < loop_ub; qY++) {
    out[qY] = b_out[qY];
  }
  loop_ub = WritePointer;
  if (loop_ub < -2147483647) {
    qY = MIN_int32_T;
  } else {
    qY = loop_ub - 1;
  }
  loop_ub = CumulativeUnderrun;
  if ((loop_ub < 0) && (*underrun < MIN_int32_T - loop_ub)) {
    loop_ub = MIN_int32_T;
  } else if ((loop_ub > 0) && (*underrun > MAX_int32_T - loop_ub)) {
    loop_ub = MAX_int32_T;
  } else {
    loop_ub += *underrun;
  }
  CumulativeUnderrun = loop_ub;
  if (*underrun != 0) {
    ReadPointer = qY;
  } else {
    ReadPointer = c;
  }
}

//
// Arguments    : const creal32_T in_data[]
//                int in_size
// Return Type  : int
//
int c_AsyncBuffercgHelper::stepImpl(const creal32_T in_data[], int in_size)
{
  array<int, 2U> b_y;
  array<int, 2U> c_y;
  array<int, 2U> y;
  array<int, 1U> r;
  int c;
  int n;
  int overrun;
  int rPtr;
  int wPtr;
  int yk;
  wPtr = WritePointer;
  rPtr = ReadPointer;
  overrun = 0;
  if ((wPtr < 1) || (wPtr > 600651)) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  c = wPtr + 1023;
  if (wPtr + 1023 > 600651) {
    c = wPtr - 599628;
    n = 600652 - wPtr;
    b_y.set_size(1, 600652 - wPtr);
    b_y[0] = wPtr;
    yk = wPtr;
    for (int k{2}; k <= n; k++) {
      yk++;
      b_y[k - 1] = yk;
    }
    if (wPtr - 599628 < 1) {
      n = 0;
    } else {
      n = wPtr - 599628;
    }
    c_y.set_size(1, n);
    if (n > 0) {
      c_y[0] = 1;
      yk = 1;
      for (int k{2}; k <= n; k++) {
        yk++;
        c_y[k - 1] = yk;
      }
    }
    y.set_size(1, b_y.size(1) + c_y.size(1));
    n = b_y.size(1);
    for (yk = 0; yk < n; yk++) {
      y[yk] = b_y[yk];
    }
    n = c_y.size(1);
    for (yk = 0; yk < n; yk++) {
      y[yk + b_y.size(1)] = c_y[yk];
    }
    if (wPtr <= rPtr) {
      overrun = (wPtr - rPtr) + 1024;
    } else if (rPtr <= wPtr - 599628) {
      if ((wPtr - 599628 >= 0) && (rPtr < wPtr + 2146884021)) {
        n = MAX_int32_T;
      } else if ((wPtr - 599628 < 0) && (rPtr > wPtr + 2146884020)) {
        n = MIN_int32_T;
      } else {
        n = (wPtr - rPtr) - 599628;
      }
      if (n > 2147483646) {
        overrun = MAX_int32_T;
      } else {
        overrun = n + 1;
      }
    }
  } else {
    eml_integer_colon_dispatcher(wPtr, wPtr + 1023, y);
    if ((wPtr <= rPtr) && (rPtr <= wPtr + 1023)) {
      overrun = (wPtr - rPtr) + 1024;
    }
  }
  r.set_size(y.size(1));
  n = y.size(1);
  for (yk = 0; yk < n; yk++) {
    if ((y[yk] < 1) || (y[yk] > 600651)) {
      rtDynamicBoundsError(y[yk], 1, 600651, &emlrtBCI);
    }
    r[yk] = y[yk] - 1;
  }
  rtSubAssignSizeCheck(r.size(), 1, &in_size, 1, &e_emlrtECI);
  for (yk = 0; yk < 1024; yk++) {
    Cache[r[yk]] = in_data[yk];
  }
  if (c + 1 > 600651) {
    wPtr = 1;
  } else {
    wPtr = c + 1;
  }
  if (overrun != 0) {
    rPtr = wPtr;
  }
  n = CumulativeOverrun;
  if ((n < 0) && (overrun < MIN_int32_T - n)) {
    n = MIN_int32_T;
  } else if ((n > 0) && (overrun > MAX_int32_T - n)) {
    n = MAX_int32_T;
  } else {
    n += overrun;
  }
  CumulativeOverrun = n;
  WritePointer = wPtr;
  ReadPointer = rPtr;
  return overrun;
}

} // namespace internal
} // namespace dsp
} // namespace coder

//
// File trailer for AsyncBuffercgHelper.cpp
//
// [EOF]
//
