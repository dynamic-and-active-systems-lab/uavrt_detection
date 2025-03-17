//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: AsyncBufferSysObj.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "AsyncBufferSysObj.h"
#include "colon.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"

// Variable Definitions
static rtRunTimeErrorInfo t_emlrtRTEI{
    473,                                      // lineNo
    "AsyncBufferSysObj/ReadSamplesFromBuffer" // fName
};

static rtEqualityCheckInfo b_emlrtECI{
    -1,                                       // nDims
    462,                                      // lineNo
    "AsyncBufferSysObj/ReadSamplesFromBuffer" // fName
};

static rtBoundsCheckInfo b_emlrtBCI{
    462,                                      // lineNo
    "",                                       // aName
    "AsyncBufferSysObj/ReadSamplesFromBuffer" // fName
};

static rtBoundsCheckInfo c_emlrtBCI{
    462,                                      // lineNo
    "",                                       // aName
    "AsyncBufferSysObj/ReadSamplesFromBuffer" // fName
};

static rtDoubleCheckInfo b_emlrtDCI{
    463,                                      // lineNo
    "AsyncBufferSysObj/ReadSamplesFromBuffer" // fName
};

static rtBoundsCheckInfo t_emlrtBCI{
    457,                                      // lineNo
    "",                                       // aName
    "AsyncBufferSysObj/ReadSamplesFromBuffer" // fName
};

static rtEqualityCheckInfo f_emlrtECI{
    -1,                                       // nDims
    469,                                      // lineNo
    "AsyncBufferSysObj/ReadSamplesFromBuffer" // fName
};

static rtBoundsCheckInfo u_emlrtBCI{
    469,                                      // lineNo
    "",                                       // aName
    "AsyncBufferSysObj/ReadSamplesFromBuffer" // fName
};

static rtBoundsCheckInfo v_emlrtBCI{
    469,                                      // lineNo
    "",                                       // aName
    "AsyncBufferSysObj/ReadSamplesFromBuffer" // fName
};

static rtDoubleCheckInfo k_emlrtDCI{
    470,                                      // lineNo
    "AsyncBufferSysObj/ReadSamplesFromBuffer" // fName
};

static rtDoubleCheckInfo l_emlrtDCI{
    467,                                      // lineNo
    "AsyncBufferSysObj/ReadSamplesFromBuffer" // fName
};

// Function Definitions
//
// Arguments    : const c_AsyncBufferSysObj *obj
//                int numRowsCast
//                array<creal32_T, 1U> &out
//                int &c
// Return Type  : int
//
namespace coder {
namespace dsp {
namespace internal {
namespace codegen {
int c_AsyncBufferSysObj::ReadSamplesFromBuffer(const c_AsyncBufferSysObj *obj,
                                               int numRowsCast,
                                               array<creal32_T, 1U> &out,
                                               int &c)
{
  static rtBoundsCheckInfo ab_emlrtBCI{
      457,                                      // lineNo
      "",                                       // aName
      "AsyncBufferSysObj/ReadSamplesFromBuffer" // fName
  };
  array<int, 2U> b_y;
  array<int, 2U> c_y;
  array<int, 2U> y;
  int i;
  int k;
  int n;
  int rPtr;
  int underrun;
  int wPtr;
  int yk;
  wPtr = obj->WritePointer;
  underrun = 0;
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
  c = (rPtr + numRowsCast) - 1;
  if (c > 600651) {
    c -= 600651;
    n = 600652 - rPtr;
    b_y.set_size(1, 600652 - rPtr);
    b_y[0] = rPtr;
    yk = rPtr;
    for (k = 2; k <= n; k++) {
      yk++;
      b_y[k - 1] = yk;
    }
    c_y.set_size(1, c);
    c_y[0] = 1;
    yk = 1;
    for (k = 2; k <= c; k++) {
      yk++;
      c_y[k - 1] = yk;
    }
    y.set_size(1, b_y.size(1) + c_y.size(1));
    k = b_y.size(1);
    for (i = 0; i < k; i++) {
      y[i] = b_y[i];
    }
    k = c_y.size(1);
    for (i = 0; i < k; i++) {
      y[i + b_y.size(1)] = c_y[i];
    }
    if (rPtr <= wPtr) {
      underrun = (c - wPtr) + 600652;
    } else if (wPtr <= c) {
      underrun = (c - wPtr) + 1;
    }
  } else {
    eml_integer_colon_dispatcher(rPtr, c, y);
    if ((rPtr <= wPtr) && (wPtr <= c)) {
      underrun = (c - wPtr) + 1;
    }
  }
  k = y.size(1);
  out.set_size(y.size(1));
  for (i = 0; i < k; i++) {
    boolean_T b;
    b = ((y[i] < 1) || (y[i] > 600651));
    if (b) {
      rtDynamicBoundsError(y[i], 1, 600651, ab_emlrtBCI);
    }
    out[i].re = obj->Cache[y[i] - 1].re;
    out[i].im = obj->Cache[y[i] - 1].im;
  }
  if (underrun != 0) {
    if ((numRowsCast >= 0) && (underrun < numRowsCast - MAX_int32_T)) {
      n = MAX_int32_T;
    } else if ((numRowsCast < 0) && (underrun > numRowsCast - MIN_int32_T)) {
      n = MIN_int32_T;
    } else {
      n = numRowsCast - underrun;
    }
    if (n + 1 > numRowsCast) {
      n = 0;
      i = 0;
    } else {
      if ((n + 1 < 1) || (n + 1 > y.size(1))) {
        rtDynamicBoundsError(n + 1, 1, y.size(1), c_emlrtBCI);
      }
      if ((numRowsCast < 1) || (numRowsCast > y.size(1))) {
        rtDynamicBoundsError(numRowsCast, 1, y.size(1), b_emlrtBCI);
      }
      i = numRowsCast;
    }
    if (underrun < 0) {
      rtNonNegativeError(static_cast<double>(underrun), b_emlrtDCI);
    }
    k = i - n;
    rtSubAssignSizeCheck(&k, 1, &underrun, 1, b_emlrtECI);
    for (i = 0; i < k; i++) {
      yk = n + i;
      out[yk].re = 0.0F;
      out[yk].im = 0.0F;
    }
  }
  if (out.size(0) != numRowsCast) {
    g_rtErrorWithMessageID(t_emlrtRTEI.fName, t_emlrtRTEI.lineNo);
  }
  return underrun;
}

//
// Arguments    : const AsyncBufferSysObj *obj
//                int numRowsCast
//                array<creal32_T, 1U> &out
//                int &c
// Return Type  : int
//
int AsyncBufferSysObj::ReadSamplesFromBuffer(const AsyncBufferSysObj *obj,
                                             int numRowsCast,
                                             array<creal32_T, 1U> &out, int &c)
{
  array<int, 2U> b_y;
  array<int, 2U> readIdx;
  array<int, 2U> y;
  int i;
  int k;
  int n;
  int rPtr;
  int underrun;
  int wPtr;
  int yk;
  wPtr = obj->WritePointer;
  underrun = 0;
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
  c = (rPtr + numRowsCast) - 1;
  if (c > 5800321) {
    c -= 5800321;
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
    b_y.set_size(1, c);
    b_y[0] = 1;
    yk = 1;
    for (k = 2; k <= c; k++) {
      yk++;
      b_y[k - 1] = yk;
    }
    readIdx.set_size(1, y.size(1) + b_y.size(1));
    k = y.size(1);
    for (i = 0; i < k; i++) {
      readIdx[i] = y[i];
    }
    k = b_y.size(1);
    for (i = 0; i < k; i++) {
      readIdx[i + y.size(1)] = b_y[i];
    }
    if (rPtr <= wPtr) {
      underrun = (c - wPtr) + 5800322;
    } else if (wPtr <= c) {
      underrun = (c - wPtr) + 1;
    }
  } else {
    eml_integer_colon_dispatcher(rPtr, c, readIdx);
    if ((rPtr <= wPtr) && (wPtr <= c)) {
      underrun = (c - wPtr) + 1;
    }
  }
  k = readIdx.size(1);
  out.set_size(readIdx.size(1));
  for (i = 0; i < k; i++) {
    boolean_T b;
    b = ((readIdx[i] < 1) || (readIdx[i] > 5800321));
    if (b) {
      rtDynamicBoundsError(readIdx[i], 1, 5800321, t_emlrtBCI);
    }
    out[i].re = obj->Cache[readIdx[i] - 1].re;
    out[i].im = obj->Cache[readIdx[i] - 1].im;
  }
  if (underrun != 0) {
    if ((numRowsCast >= 0) && (underrun < numRowsCast - MAX_int32_T)) {
      n = MAX_int32_T;
    } else if ((numRowsCast < 0) && (underrun > numRowsCast - MIN_int32_T)) {
      n = MIN_int32_T;
    } else {
      n = numRowsCast - underrun;
    }
    if (n + 1 > numRowsCast) {
      n = 0;
      i = 0;
    } else {
      if ((n + 1 < 1) || (n + 1 > readIdx.size(1))) {
        rtDynamicBoundsError(n + 1, 1, readIdx.size(1), c_emlrtBCI);
      }
      if ((numRowsCast < 1) || (numRowsCast > readIdx.size(1))) {
        rtDynamicBoundsError(numRowsCast, 1, readIdx.size(1), b_emlrtBCI);
      }
      i = numRowsCast;
    }
    if (underrun < 0) {
      rtNonNegativeError(static_cast<double>(underrun), b_emlrtDCI);
    }
    k = i - n;
    rtSubAssignSizeCheck(&k, 1, &underrun, 1, b_emlrtECI);
    for (i = 0; i < k; i++) {
      yk = n + i;
      out[yk].re = 0.0F;
      out[yk].im = 0.0F;
    }
  }
  if (out.size(0) != numRowsCast) {
    g_rtErrorWithMessageID(t_emlrtRTEI.fName, t_emlrtRTEI.lineNo);
  }
  return underrun;
}

//
// Arguments    : const b_AsyncBufferSysObj *obj
//                int numRowsCast
//                array<double, 1U> &out
//                int &c
// Return Type  : int
//
int b_AsyncBufferSysObj::ReadSamplesFromBuffer(const b_AsyncBufferSysObj *obj,
                                               int numRowsCast,
                                               array<double, 1U> &out, int &c)
{
  array<int, 2U> b_y;
  array<int, 2U> readIdx;
  array<int, 2U> y;
  int k;
  int n;
  int rPtr;
  int underrun;
  int wPtr;
  int yk;
  wPtr = obj->WritePointer;
  underrun = 0;
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
  c = (rPtr + numRowsCast) - 1;
  if (c > 5800321) {
    c -= 5800321;
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
    b_y.set_size(1, c);
    b_y[0] = 1;
    yk = 1;
    for (k = 2; k <= c; k++) {
      yk++;
      b_y[k - 1] = yk;
    }
    readIdx.set_size(1, y.size(1) + b_y.size(1));
    yk = y.size(1);
    for (k = 0; k < yk; k++) {
      readIdx[k] = y[k];
    }
    yk = b_y.size(1);
    for (k = 0; k < yk; k++) {
      readIdx[k + y.size(1)] = b_y[k];
    }
    if (rPtr <= wPtr) {
      underrun = (c - wPtr) + 5800322;
    } else if (wPtr <= c) {
      underrun = (c - wPtr) + 1;
    }
  } else {
    eml_integer_colon_dispatcher(rPtr, c, readIdx);
    if ((rPtr <= wPtr) && (wPtr <= c)) {
      underrun = (c - wPtr) + 1;
    }
  }
  yk = readIdx.size(1);
  out.set_size(readIdx.size(1));
  for (k = 0; k < yk; k++) {
    if ((readIdx[k] < 1) || (readIdx[k] > 5800321)) {
      rtDynamicBoundsError(readIdx[k], 1, 5800321, t_emlrtBCI);
    }
    out[k] = obj->Cache[readIdx[k] - 1];
  }
  if (underrun != 0) {
    if ((numRowsCast >= 0) && (underrun < numRowsCast - MAX_int32_T)) {
      n = MAX_int32_T;
    } else if ((numRowsCast < 0) && (underrun > numRowsCast - MIN_int32_T)) {
      n = MIN_int32_T;
    } else {
      n = numRowsCast - underrun;
    }
    if (n + 1 > numRowsCast) {
      n = 0;
      k = 0;
    } else {
      if ((n + 1 < 1) || (n + 1 > readIdx.size(1))) {
        rtDynamicBoundsError(n + 1, 1, readIdx.size(1), c_emlrtBCI);
      }
      if ((numRowsCast < 1) || (numRowsCast > readIdx.size(1))) {
        rtDynamicBoundsError(numRowsCast, 1, readIdx.size(1), b_emlrtBCI);
      }
      k = numRowsCast;
    }
    if (underrun < 0) {
      rtNonNegativeError(static_cast<double>(underrun), b_emlrtDCI);
    }
    yk = k - n;
    rtSubAssignSizeCheck(&yk, 1, &underrun, 1, b_emlrtECI);
    for (k = 0; k < yk; k++) {
      out[n + k] = 0.0;
    }
  }
  if (out.size(0) != numRowsCast) {
    g_rtErrorWithMessageID(t_emlrtRTEI.fName, t_emlrtRTEI.lineNo);
  }
  return underrun;
}

//
// Arguments    : void
// Return Type  : void
//
void c_AsyncBufferSysObj::SystemCore_delete()
{
  release();
}

//
// Arguments    : void
// Return Type  : void
//
void b_AsyncBufferSysObj::SystemCore_delete()
{
  release();
}

//
// Arguments    : void
// Return Type  : void
//
void AsyncBufferSysObj::SystemCore_delete()
{
  release();
}

//
// Arguments    : void
// Return Type  : void
//
void c_AsyncBufferSysObj::matlabCodegenDestructor()
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
void b_AsyncBufferSysObj::matlabCodegenDestructor()
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
void AsyncBufferSysObj::matlabCodegenDestructor()
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
void c_AsyncBufferSysObj::release()
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
void b_AsyncBufferSysObj::release()
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
void AsyncBufferSysObj::release()
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
void c_AsyncBufferSysObj::releaseImpl()
{
  ReadPointer = 1;
  WritePointer = 2;
  CumulativeOverrun = 0;
  CumulativeUnderrun = 0;
  AsyncBufferSysObj_isInitialized = false;
  NumChannels = -1;
}

//
// Arguments    : void
// Return Type  : void
//
void b_AsyncBufferSysObj::releaseImpl()
{
  ReadPointer = 1;
  WritePointer = 2;
  CumulativeOverrun = 0;
  CumulativeUnderrun = 0;
  AsyncBufferSysObj_isInitialized = false;
  NumChannels = -1;
}

//
// Arguments    : void
// Return Type  : void
//
void AsyncBufferSysObj::releaseImpl()
{
  ReadPointer = 1;
  WritePointer = 2;
  CumulativeOverrun = 0;
  CumulativeUnderrun = 0;
  AsyncBufferSysObj_isInitialized = false;
  NumChannels = -1;
}

//
// Arguments    : void
// Return Type  : void
//
void c_AsyncBufferSysObj::releaseWrapper()
{
  if (isSetupComplete) {
    releaseImpl();
  }
}

//
// Arguments    : void
// Return Type  : void
//
void b_AsyncBufferSysObj::releaseWrapper()
{
  if (isSetupComplete) {
    releaseImpl();
  }
}

//
// Arguments    : void
// Return Type  : void
//
void AsyncBufferSysObj::releaseWrapper()
{
  if (isSetupComplete) {
    releaseImpl();
  }
}

//
// Arguments    : const AsyncBufferSysObj &obj
//                int numRowsCast
//                int overlapCast
//                array<creal32_T, 1U> &out
//                int &overlapUnderrun
//                int &c
// Return Type  : int
//
int AsyncBufferSysObj::ReadSamplesFromBuffer(const AsyncBufferSysObj &obj,
                                             int numRowsCast, int overlapCast,
                                             array<creal32_T, 1U> &out,
                                             int &overlapUnderrun, int &c)
{
  array<int, 2U> b_y;
  array<int, 2U> readIdx;
  array<int, 2U> y;
  int k;
  int n;
  int qY;
  int rPtr;
  int underrun;
  int wPtr;
  int yk;
  wPtr = obj.WritePointer;
  underrun = 0;
  overlapUnderrun = 0;
  n = obj.ReadPointer;
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
  if (overlapCast == 0) {
    c = (rPtr + numRowsCast) - 1;
    if (c > 5800321) {
      c -= 5800321;
      eml_integer_colon_dispatcher(rPtr, y);
      b_y.set_size(1, c);
      b_y[0] = 1;
      yk = 1;
      for (k = 2; k <= c; k++) {
        yk++;
        b_y[k - 1] = yk;
      }
      readIdx.set_size(1, y.size(1) + b_y.size(1));
      yk = y.size(1);
      for (k = 0; k < yk; k++) {
        readIdx[k] = y[k];
      }
      yk = b_y.size(1);
      for (k = 0; k < yk; k++) {
        readIdx[k + y.size(1)] = b_y[k];
      }
      if (rPtr <= wPtr) {
        underrun = (c - wPtr) + 5800322;
      } else if (wPtr <= c) {
        underrun = (c - wPtr) + 1;
      }
    } else {
      eml_integer_colon_dispatcher(rPtr, c, readIdx);
      if ((rPtr <= wPtr) && (wPtr <= c)) {
        underrun = (c - wPtr) + 1;
      }
    }
  } else {
    int b_qY;
    if (overlapCast < rPtr - MAX_int32_T) {
      qY = MAX_int32_T;
      b_qY = MAX_int32_T;
    } else {
      qY = rPtr - overlapCast;
      b_qY = rPtr - overlapCast;
    }
    if ((b_qY < 0) && (numRowsCast < MIN_int32_T - b_qY)) {
      b_qY = MIN_int32_T;
    } else if ((b_qY > 0) && (numRowsCast > MAX_int32_T - b_qY)) {
      b_qY = MAX_int32_T;
    } else {
      b_qY += numRowsCast;
    }
    if (b_qY < -2147483647) {
      b_qY = MIN_int32_T;
    } else {
      b_qY--;
    }
    c = b_qY;
    if (qY < 1) {
      eml_integer_colon_dispatcher(qY + 5800321, y);
      if (b_qY < 1) {
        n = 0;
      } else {
        n = b_qY;
      }
      b_y.set_size(1, n);
      if (n > 0) {
        b_y[0] = 1;
        yk = 1;
        for (k = 2; k <= n; k++) {
          yk++;
          b_y[k - 1] = yk;
        }
      }
      readIdx.set_size(1, y.size(1) + b_y.size(1));
      yk = y.size(1);
      for (k = 0; k < yk; k++) {
        readIdx[k] = y[k];
      }
      yk = b_y.size(1);
      for (k = 0; k < yk; k++) {
        readIdx[k + y.size(1)] = b_y[k];
      }
      if ((rPtr <= wPtr) && (wPtr <= b_qY)) {
        underrun = (b_qY - wPtr) + 1;
      } else if (wPtr < rPtr) {
        if ((1 - qY < 0) && (wPtr < qY + MAX_int32_T)) {
          overlapUnderrun = MIN_int32_T;
        } else if ((1 - qY > 0) && (wPtr > qY + 2147483646)) {
          overlapUnderrun = MAX_int32_T;
        } else {
          overlapUnderrun = (wPtr - qY) + 1;
        }
      } else if (wPtr > qY + 5800321) {
        overlapUnderrun = (wPtr - qY) - 5800320;
      }
    } else if (b_qY > 5800321) {
      n = b_qY - 5800321;
      c = b_qY - 5800321;
      eml_integer_colon_dispatcher(qY, y);
      b_y.set_size(1, n);
      b_y[0] = 1;
      yk = 1;
      for (k = 2; k <= n; k++) {
        yk++;
        b_y[k - 1] = yk;
      }
      readIdx.set_size(1, y.size(1) + b_y.size(1));
      yk = y.size(1);
      for (k = 0; k < yk; k++) {
        readIdx[k] = y[k];
      }
      yk = b_y.size(1);
      for (k = 0; k < yk; k++) {
        readIdx[k + y.size(1)] = b_y[k];
      }
      if (rPtr <= wPtr) {
        underrun = (b_qY - wPtr) + 1;
      } else if (wPtr <= b_qY - 5800321) {
        underrun = (b_qY - wPtr) - 5800320;
      } else if ((qY < wPtr) && (wPtr < rPtr)) {
        overlapUnderrun = (wPtr - qY) + 1;
      }
    } else {
      eml_integer_colon_dispatcher(qY, b_qY, readIdx);
      if ((rPtr <= wPtr) && (wPtr <= b_qY)) {
        underrun = (b_qY - wPtr) + 1;
      } else if ((qY <= wPtr) && (wPtr < rPtr)) {
        overlapUnderrun = (wPtr - qY) + 1;
      }
    }
  }
  yk = readIdx.size(1);
  out.set_size(readIdx.size(1));
  for (k = 0; k < yk; k++) {
    boolean_T b;
    b = ((readIdx[k] < 1) || (readIdx[k] > 5800321));
    if (b) {
      rtDynamicBoundsError(readIdx[k], 1, 5800321, t_emlrtBCI);
    }
    out[k].re = obj.Cache[readIdx[k] - 1].re;
    out[k].im = obj.Cache[readIdx[k] - 1].im;
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
      k = 0;
    } else {
      if ((qY + 1 < 1) || (qY + 1 > readIdx.size(1))) {
        rtDynamicBoundsError(qY + 1, 1, readIdx.size(1), c_emlrtBCI);
      }
      if ((numRowsCast < 1) || (numRowsCast > readIdx.size(1))) {
        rtDynamicBoundsError(numRowsCast, 1, readIdx.size(1), b_emlrtBCI);
      }
      k = numRowsCast;
    }
    if (underrun < 0) {
      rtNonNegativeError(static_cast<double>(underrun), b_emlrtDCI);
    }
    yk = k - qY;
    rtSubAssignSizeCheck(&yk, 1, &underrun, 1, b_emlrtECI);
    for (k = 0; k < yk; k++) {
      n = qY + k;
      out[n].re = 0.0F;
      out[n].im = 0.0F;
    }
  } else if (overlapUnderrun != 0) {
    if (overlapUnderrun == numRowsCast) {
      if (overlapUnderrun < 0) {
        rtNonNegativeError(static_cast<double>(overlapUnderrun), l_emlrtDCI);
      }
      out.set_size(overlapUnderrun);
      for (k = 0; k < overlapUnderrun; k++) {
        out[k].re = 0.0F;
        out[k].im = 0.0F;
      }
    } else {
      if (overlapUnderrun < 1) {
        yk = 0;
      } else {
        if (readIdx.size(1) < 1) {
          rtDynamicBoundsError(1, 1, readIdx.size(1), v_emlrtBCI);
        }
        if (overlapUnderrun > readIdx.size(1)) {
          rtDynamicBoundsError(overlapUnderrun, 1, readIdx.size(1), u_emlrtBCI);
        }
        yk = overlapUnderrun;
      }
      if (overlapUnderrun < 0) {
        rtNonNegativeError(static_cast<double>(overlapUnderrun), k_emlrtDCI);
      }
      rtSubAssignSizeCheck(&yk, 1, &overlapUnderrun, 1, f_emlrtECI);
      for (k = 0; k < yk; k++) {
        out[k].re = 0.0F;
        out[k].im = 0.0F;
      }
    }
  }
  if (out.size(0) != numRowsCast) {
    g_rtErrorWithMessageID(t_emlrtRTEI.fName, t_emlrtRTEI.lineNo);
  }
  return underrun;
}

//
// Arguments    : const b_AsyncBufferSysObj &obj
//                int numRowsCast
//                int overlapCast
//                array<double, 1U> &out
//                int &overlapUnderrun
//                int &c
// Return Type  : int
//
int b_AsyncBufferSysObj::ReadSamplesFromBuffer(const b_AsyncBufferSysObj &obj,
                                               int numRowsCast, int overlapCast,
                                               array<double, 1U> &out,
                                               int &overlapUnderrun, int &c)
{
  array<int, 2U> b_y;
  array<int, 2U> readIdx;
  array<int, 2U> y;
  int n;
  int q0;
  int qY;
  int rPtr;
  int underrun;
  int wPtr;
  wPtr = obj.WritePointer;
  underrun = 0;
  overlapUnderrun = 0;
  q0 = obj.ReadPointer;
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
    c = (rPtr + numRowsCast) - 1;
    if (c > 5800321) {
      int yk;
      c -= 5800321;
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
      b_y.set_size(1, c);
      b_y[0] = 1;
      yk = 1;
      for (int k{2}; k <= c; k++) {
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
        underrun = (c - wPtr) + 5800322;
      } else if (wPtr <= c) {
        underrun = (c - wPtr) + 1;
      }
    } else {
      eml_integer_colon_dispatcher(rPtr, c, readIdx);
      if ((rPtr <= wPtr) && (wPtr <= c)) {
        underrun = (c - wPtr) + 1;
      }
    }
  } else {
    int b_qY;
    if (overlapCast < rPtr - MAX_int32_T) {
      qY = MAX_int32_T;
      b_qY = MAX_int32_T;
    } else {
      qY = rPtr - overlapCast;
      b_qY = rPtr - overlapCast;
    }
    if ((b_qY < 0) && (numRowsCast < MIN_int32_T - b_qY)) {
      b_qY = MIN_int32_T;
    } else if ((b_qY > 0) && (numRowsCast > MAX_int32_T - b_qY)) {
      b_qY = MAX_int32_T;
    } else {
      b_qY += numRowsCast;
    }
    if (b_qY < -2147483647) {
      b_qY = MIN_int32_T;
    } else {
      b_qY--;
    }
    c = b_qY;
    if (qY < 1) {
      unsigned int u;
      int yk;
      if (qY + 5800321 < 0) {
        u = static_cast<unsigned int>(-qY);
      } else {
        u = static_cast<unsigned int>(-qY);
      }
      n = static_cast<int>(u) + 1;
      y.set_size(1, n);
      if (n > 0) {
        y[0] = qY + 5800321;
        yk = qY + 5800321;
        if (n > 2147483646) {
          check_forloop_overflow_error();
        }
        for (int k{2}; k <= n; k++) {
          yk++;
          y[k - 1] = yk;
        }
      }
      if (b_qY < 1) {
        n = 0;
      } else {
        n = b_qY;
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
      if ((rPtr <= wPtr) && (wPtr <= b_qY)) {
        underrun = (b_qY - wPtr) + 1;
      } else if (wPtr < rPtr) {
        if ((1 - qY < 0) && (wPtr < qY + MAX_int32_T)) {
          overlapUnderrun = MIN_int32_T;
        } else if ((1 - qY > 0) && (wPtr > qY + 2147483646)) {
          overlapUnderrun = MAX_int32_T;
        } else {
          overlapUnderrun = (wPtr - qY) + 1;
        }
      } else if (wPtr > qY + 5800321) {
        overlapUnderrun = (wPtr - qY) - 5800320;
      }
    } else if (b_qY > 5800321) {
      int yk;
      q0 = b_qY - 5800321;
      c = b_qY - 5800321;
      if (qY > 5800321) {
        n = 0;
      } else {
        n = 5800322 - qY;
      }
      y.set_size(1, n);
      if (n > 0) {
        y[0] = qY;
        yk = qY;
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
        underrun = (b_qY - wPtr) + 1;
      } else if (wPtr <= b_qY - 5800321) {
        underrun = (b_qY - wPtr) - 5800320;
      } else if ((qY < wPtr) && (wPtr < rPtr)) {
        overlapUnderrun = (wPtr - qY) + 1;
      }
    } else {
      eml_integer_colon_dispatcher(qY, b_qY, readIdx);
      if ((rPtr <= wPtr) && (wPtr <= b_qY)) {
        underrun = (b_qY - wPtr) + 1;
      } else if ((qY <= wPtr) && (wPtr < rPtr)) {
        overlapUnderrun = (wPtr - qY) + 1;
      }
    }
  }
  q0 = readIdx.size(1);
  out.set_size(readIdx.size(1));
  for (n = 0; n < q0; n++) {
    if ((readIdx[n] < 1) || (readIdx[n] > 5800321)) {
      rtDynamicBoundsError(readIdx[n], 1, 5800321, t_emlrtBCI);
    }
    out[n] = obj.Cache[readIdx[n] - 1];
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
      n = 0;
    } else {
      if ((qY + 1 < 1) || (qY + 1 > readIdx.size(1))) {
        rtDynamicBoundsError(qY + 1, 1, readIdx.size(1), c_emlrtBCI);
      }
      if ((numRowsCast < 1) || (numRowsCast > readIdx.size(1))) {
        rtDynamicBoundsError(numRowsCast, 1, readIdx.size(1), b_emlrtBCI);
      }
      n = numRowsCast;
    }
    if (underrun < 0) {
      rtNonNegativeError(static_cast<double>(underrun), b_emlrtDCI);
    }
    q0 = n - qY;
    rtSubAssignSizeCheck(&q0, 1, &underrun, 1, b_emlrtECI);
    for (n = 0; n < q0; n++) {
      out[qY + n] = 0.0;
    }
  } else if (overlapUnderrun != 0) {
    if (overlapUnderrun == numRowsCast) {
      if (overlapUnderrun < 0) {
        rtNonNegativeError(static_cast<double>(overlapUnderrun), l_emlrtDCI);
      }
      out.set_size(overlapUnderrun);
      for (n = 0; n < overlapUnderrun; n++) {
        out[n] = 0.0;
      }
    } else {
      if (overlapUnderrun < 1) {
        q0 = 0;
      } else {
        if (readIdx.size(1) < 1) {
          rtDynamicBoundsError(1, 1, readIdx.size(1), v_emlrtBCI);
        }
        if (overlapUnderrun > readIdx.size(1)) {
          rtDynamicBoundsError(overlapUnderrun, 1, readIdx.size(1), u_emlrtBCI);
        }
        q0 = overlapUnderrun;
      }
      if (overlapUnderrun < 0) {
        rtNonNegativeError(static_cast<double>(overlapUnderrun), k_emlrtDCI);
      }
      rtSubAssignSizeCheck(&q0, 1, &overlapUnderrun, 1, f_emlrtECI);
      for (n = 0; n < q0; n++) {
        out[n] = 0.0;
      }
    }
  }
  if (out.size(0) != numRowsCast) {
    g_rtErrorWithMessageID(t_emlrtRTEI.fName, t_emlrtRTEI.lineNo);
  }
  return underrun;
}

//
// Arguments    : void
// Return Type  : c_AsyncBufferSysObj
//
c_AsyncBufferSysObj::c_AsyncBufferSysObj()
{
  matlabCodegenIsDeleted = true;
}

//
// Arguments    : void
// Return Type  : b_AsyncBufferSysObj
//
b_AsyncBufferSysObj::b_AsyncBufferSysObj()
{
  matlabCodegenIsDeleted = true;
}

//
// Arguments    : void
// Return Type  : AsyncBufferSysObj
//
AsyncBufferSysObj::AsyncBufferSysObj()
{
  matlabCodegenIsDeleted = true;
}

//
// Arguments    : void
// Return Type  : void
//
c_AsyncBufferSysObj::~c_AsyncBufferSysObj()
{
  matlabCodegenDestructor();
}

//
// Arguments    : void
// Return Type  : void
//
b_AsyncBufferSysObj::~b_AsyncBufferSysObj()
{
  matlabCodegenDestructor();
}

//
// Arguments    : void
// Return Type  : void
//
AsyncBufferSysObj::~AsyncBufferSysObj()
{
  matlabCodegenDestructor();
}

//
// Arguments    : int numRows
//                array<creal32_T, 1U> &out
// Return Type  : int
//
int c_AsyncBufferSysObj::read(int numRows, array<creal32_T, 1U> &out)
{
  array<creal32_T, 1U> b_out;
  int c;
  int loop_ub;
  int underrun;
  if (!AsyncBufferSysObj_isInitialized) {
    q_rtErrorWithMessageID(s_emlrtRTEI.fName, s_emlrtRTEI.lineNo);
  }
  underrun =
      c_AsyncBufferSysObj::ReadSamplesFromBuffer(this, numRows, b_out, c);
  loop_ub = b_out.size(0);
  out.set_size(b_out.size(0));
  for (int i{0}; i < loop_ub; i++) {
    out[i] = b_out[i];
  }
  loop_ub = CumulativeUnderrun;
  if ((loop_ub < 0) && (underrun < MIN_int32_T - loop_ub)) {
    loop_ub = MIN_int32_T;
  } else if ((loop_ub > 0) && (underrun > MAX_int32_T - loop_ub)) {
    loop_ub = MAX_int32_T;
  } else {
    loop_ub += underrun;
  }
  CumulativeUnderrun = loop_ub;
  loop_ub = WritePointer;
  if (loop_ub < -2147483647) {
    loop_ub = MIN_int32_T;
  } else {
    loop_ub--;
  }
  if (underrun != 0) {
    ReadPointer = loop_ub;
  } else {
    ReadPointer = c;
  }
  return underrun;
}

//
// Arguments    : int numRows
//                array<creal32_T, 1U> &out
// Return Type  : int
//
int AsyncBufferSysObj::read(int numRows, array<creal32_T, 1U> &out)
{
  array<creal32_T, 1U> b_out;
  int c;
  int loop_ub;
  int underrun;
  if (!AsyncBufferSysObj_isInitialized) {
    q_rtErrorWithMessageID(s_emlrtRTEI.fName, s_emlrtRTEI.lineNo);
  }
  underrun = AsyncBufferSysObj::ReadSamplesFromBuffer(this, numRows, b_out, c);
  loop_ub = b_out.size(0);
  out.set_size(b_out.size(0));
  for (int i{0}; i < loop_ub; i++) {
    out[i] = b_out[i];
  }
  loop_ub = CumulativeUnderrun;
  if ((loop_ub < 0) && (underrun < MIN_int32_T - loop_ub)) {
    loop_ub = MIN_int32_T;
  } else if ((loop_ub > 0) && (underrun > MAX_int32_T - loop_ub)) {
    loop_ub = MAX_int32_T;
  } else {
    loop_ub += underrun;
  }
  CumulativeUnderrun = loop_ub;
  loop_ub = WritePointer;
  if (loop_ub < -2147483647) {
    loop_ub = MIN_int32_T;
  } else {
    loop_ub--;
  }
  if (underrun != 0) {
    ReadPointer = loop_ub;
  } else {
    ReadPointer = c;
  }
  return underrun;
}

//
// Arguments    : int numRows
//                array<double, 1U> &out
// Return Type  : int
//
int b_AsyncBufferSysObj::read(int numRows, array<double, 1U> &out)
{
  array<double, 1U> b_out;
  int c;
  int loop_ub;
  int underrun;
  if (!AsyncBufferSysObj_isInitialized) {
    q_rtErrorWithMessageID(s_emlrtRTEI.fName, s_emlrtRTEI.lineNo);
  }
  underrun =
      b_AsyncBufferSysObj::ReadSamplesFromBuffer(this, numRows, b_out, c);
  loop_ub = b_out.size(0);
  out.set_size(b_out.size(0));
  for (int i{0}; i < loop_ub; i++) {
    out[i] = b_out[i];
  }
  loop_ub = CumulativeUnderrun;
  if ((loop_ub < 0) && (underrun < MIN_int32_T - loop_ub)) {
    loop_ub = MIN_int32_T;
  } else if ((loop_ub > 0) && (underrun > MAX_int32_T - loop_ub)) {
    loop_ub = MAX_int32_T;
  } else {
    loop_ub += underrun;
  }
  CumulativeUnderrun = loop_ub;
  loop_ub = WritePointer;
  if (loop_ub < -2147483647) {
    loop_ub = MIN_int32_T;
  } else {
    loop_ub--;
  }
  if (underrun != 0) {
    ReadPointer = loop_ub;
  } else {
    ReadPointer = c;
  }
  return underrun;
}

//
// Arguments    : const creal32_T in_data[]
// Return Type  : int
//
int c_AsyncBufferSysObj::stepImpl(const creal32_T in_data[])
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
  c = wPtr + 1022;
  if (wPtr + 1022 > 600651) {
    c = wPtr - 599629;
    n = 600652 - wPtr;
    b_y.set_size(1, 600652 - wPtr);
    b_y[0] = wPtr;
    yk = wPtr;
    for (int k{2}; k <= n; k++) {
      yk++;
      b_y[k - 1] = yk;
    }
    if (wPtr - 599629 < 1) {
      n = 0;
    } else {
      n = wPtr - 599629;
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
      overrun = (wPtr - rPtr) + 1023;
    } else if (rPtr <= wPtr - 599629) {
      if ((wPtr - 599629 >= 0) && (rPtr < wPtr + 2146884020)) {
        n = MAX_int32_T;
      } else if ((wPtr - 599629 < 0) && (rPtr > wPtr + 2146884019)) {
        n = MIN_int32_T;
      } else {
        n = (wPtr - rPtr) - 599629;
      }
      if (n > 2147483646) {
        overrun = MAX_int32_T;
      } else {
        overrun = n + 1;
      }
    }
  } else {
    eml_integer_colon_dispatcher(wPtr, wPtr + 1022, y);
    if ((wPtr <= rPtr) && (rPtr <= wPtr + 1022)) {
      overrun = (wPtr - rPtr) + 1023;
    }
  }
  n = y.size(1);
  r.set_size(y.size(1));
  for (yk = 0; yk < n; yk++) {
    if ((y[yk] < 1) || (y[yk] > 600651)) {
      rtDynamicBoundsError(y[yk], 1, 600651, emlrtBCI);
    }
    r[yk] = y[yk] - 1;
  }
  yk = 1023;
  rtSubAssignSizeCheck(&(y.size())[1], 1, &yk, 1, e_emlrtECI);
  for (yk = 0; yk < n; yk++) {
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

} // namespace codegen
} // namespace internal
} // namespace dsp
} // namespace coder

//
// File trailer for AsyncBufferSysObj.cpp
//
// [EOF]
//
