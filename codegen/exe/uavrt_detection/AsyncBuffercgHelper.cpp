//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: AsyncBuffercgHelper.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 14:31:55
//

// Include Files
#include "AsyncBuffercgHelper.h"
#include "colon.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include <cstring>
#include <string.h>

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
  static rtBoundsCheckInfo f_emlrtBCI{
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
  array<int, 2U> readIdx;
  array<int, 2U> y;
  int i;
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
    b_rtErrorWithMessageID(b_emlrtRTEI.fName, b_emlrtRTEI.lineNo);
  }
  *c = (rPtr + numRowsCast) - 1;
  if (*c > 600651) {
    *c -= 600651;
    n = 600652 - rPtr;
    readIdx.set_size(1, 600652 - rPtr);
    readIdx[0] = rPtr;
    yk = rPtr;
    for (k = 2; k <= n; k++) {
      yk++;
      readIdx[k - 1] = yk;
    }
    y.set_size(1, *c);
    y[0] = 1;
    yk = 1;
    for (k = 2; k <= *c; k++) {
      yk++;
      y[k - 1] = yk;
    }
    k = readIdx.size(1);
    readIdx.set_size(1, readIdx.size(1) + y.size(1));
    n = y.size(1);
    for (i = 0; i < n; i++) {
      readIdx[i + k] = y[i];
    }
    if (rPtr <= wPtr) {
      *underrun = (*c - wPtr) + 600652;
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
    if ((readIdx[k] < 1) || (readIdx[k] > 600651)) {
      rtDynamicBoundsError(readIdx[k], 1, 600651, &f_emlrtBCI);
    }
    out[k].re = obj->Cache[readIdx[k] - 1].re;
    if ((readIdx[k] < 1) || (readIdx[k] > 600651)) {
      rtDynamicBoundsError(readIdx[k], 1, 600651, &f_emlrtBCI);
    }
    out[k].im = obj->Cache[readIdx[k] - 1].im;
  }
  if (*underrun != 0) {
    if ((numRowsCast >= 0) && (*underrun < numRowsCast - MAX_int32_T)) {
      yk = MAX_int32_T;
    } else if ((numRowsCast < 0) && (*underrun > numRowsCast - MIN_int32_T)) {
      yk = MIN_int32_T;
    } else {
      yk = numRowsCast - *underrun;
    }
    if (yk + 1 > numRowsCast) {
      yk = 0;
      k = 0;
    } else {
      if ((yk + 1 < 1) || (yk + 1 > readIdx.size(1))) {
        rtDynamicBoundsError(yk + 1, 1, readIdx.size(1), &c_emlrtBCI);
      }
      if ((numRowsCast < 1) || (numRowsCast > readIdx.size(1))) {
        rtDynamicBoundsError(numRowsCast, 1, readIdx.size(1), &b_emlrtBCI);
      }
      k = numRowsCast;
    }
    if (*underrun < 0) {
      rtNonNegativeError(static_cast<double>(*underrun), &emlrtDCI);
    }
    n = k - yk;
    rtSubAssignSizeCheck(&n, 1, underrun, 1, &emlrtECI);
    for (k = 0; k < *underrun; k++) {
      i = yk + k;
      out[i].re = 0.0F;
      out[i].im = 0.0F;
    }
  }
  if (out.size(0) != numRowsCast) {
    j_rtErrorWithMessageID(x_emlrtRTEI.fName, x_emlrtRTEI.lineNo);
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
    q_rtErrorWithMessageID(w_emlrtRTEI.fName, w_emlrtRTEI.lineNo);
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
//                creal32_T out_data[]
//                int *out_size
//                int *underrun
// Return Type  : void
//
void AsyncBuffercgHelper::read(int numRows, creal32_T out_data[], int *out_size,
                               int *underrun)
{
  array<int, 2U> b_y;
  array<int, 2U> y;
  int c;
  int k;
  int rPtr;
  int wPtr_tmp;
  int yk;
  if (!AsyncBuffercgHelper_isInitialized) {
    q_rtErrorWithMessageID(w_emlrtRTEI.fName, w_emlrtRTEI.lineNo);
  }
  wPtr_tmp = WritePointer;
  *underrun = 0;
  yk = ReadPointer;
  if (yk > 2147483646) {
    rPtr = MAX_int32_T;
  } else {
    rPtr = yk + 1;
  }
  if (rPtr > 5800321) {
    rPtr = 1;
  }
  if ((wPtr_tmp < 1) || (wPtr_tmp > 5800321) || (rPtr < 1) ||
      (numRows > 5800321)) {
    b_rtErrorWithMessageID(b_emlrtRTEI.fName, b_emlrtRTEI.lineNo);
  }
  c = (rPtr + numRows) - 1;
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
      *underrun = (c - wPtr_tmp) + 5800322;
    } else if (wPtr_tmp <= c) {
      *underrun = (c - wPtr_tmp) + 1;
    }
  } else {
    eml_integer_colon_dispatcher(rPtr, c, y);
    if ((rPtr <= wPtr_tmp) && (wPtr_tmp <= c)) {
      *underrun = (c - wPtr_tmp) + 1;
    }
  }
  *out_size = y.size(1);
  yk = y.size(1);
  for (k = 0; k < yk; k++) {
    if ((y[k] < 1) || (y[k] > 5800321)) {
      rtDynamicBoundsError(y[k], 1, 5800321, &e_emlrtBCI);
    }
    out_data[k].re = Cache[y[k] - 1].re;
    if ((y[k] < 1) || (y[k] > 5800321)) {
      rtDynamicBoundsError(y[k], 1, 5800321, &e_emlrtBCI);
    }
    out_data[k].im = Cache[y[k] - 1].im;
  }
  if (*underrun != 0) {
    if ((numRows >= 0) && (*underrun < numRows - MAX_int32_T)) {
      yk = MAX_int32_T;
    } else if ((numRows < 0) && (*underrun > numRows - MIN_int32_T)) {
      yk = MIN_int32_T;
    } else {
      yk = numRows - *underrun;
    }
    if (yk + 1 > numRows) {
      k = 0;
    } else {
      if ((yk + 1 < 1) || (yk + 1 > y.size(1))) {
        rtDynamicBoundsError(yk + 1, 1, y.size(1), &c_emlrtBCI);
      }
      if ((numRows < 1) || (numRows > y.size(1))) {
        rtDynamicBoundsError(numRows, 1, y.size(1), &b_emlrtBCI);
      }
      k = 1;
    }
    if (*underrun < 0) {
      rtNonNegativeError(static_cast<double>(*underrun), &emlrtDCI);
    }
    rtSubAssignSizeCheck(&k, 1, underrun, 1, &emlrtECI);
    if (*underrun - 1 >= 0) {
      std::memset(&out_data[0], 0, *underrun * sizeof(creal32_T));
    }
  }
  if (*out_size != numRows) {
    j_rtErrorWithMessageID(x_emlrtRTEI.fName, x_emlrtRTEI.lineNo);
  }
  yk = CumulativeUnderrun;
  if ((yk < 0) && (*underrun < MIN_int32_T - yk)) {
    yk = MIN_int32_T;
  } else if ((yk > 0) && (*underrun > MAX_int32_T - yk)) {
    yk = MAX_int32_T;
  } else {
    yk += *underrun;
  }
  CumulativeUnderrun = yk;
  if (*underrun != 0) {
    ReadPointer = wPtr_tmp - 1;
  } else {
    ReadPointer = c;
  }
}

} // namespace internal
} // namespace dsp
} // namespace coder

//
// File trailer for AsyncBuffercgHelper.cpp
//
// [EOF]
//
