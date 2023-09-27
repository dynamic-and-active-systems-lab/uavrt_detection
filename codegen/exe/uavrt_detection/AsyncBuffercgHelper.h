//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: AsyncBuffercgHelper.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 25-Sep-2023 12:08:03
//

#ifndef ASYNCBUFFERCGHELPER_H
#define ASYNCBUFFERCGHELPER_H

// Include Files
#include "rtwtypes.h"
#include "uavrt_detection_internal_types.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
namespace dsp {
namespace internal {
class AsyncBuffercgHelper {
public:
  int read(int numRows, ::coder::array<creal32_T, 1U> &out);
  static int ReadSamplesFromBuffer(const AsyncBuffercgHelper *obj,
                                   int numRowsCast,
                                   ::coder::array<creal32_T, 1U> &out, int &c);
  static int ReadSamplesFromBuffer(const AsyncBuffercgHelper &obj,
                                   int numRowsCast, int overlapCast,
                                   ::coder::array<creal32_T, 1U> &out,
                                   int &overlapUnderrun, int &c);
  void matlabCodegenDestructor();
  void release();
  void releaseWrapper();
  ~AsyncBuffercgHelper();
  AsyncBuffercgHelper();

protected:
  void releaseImpl();

private:
  void SystemCore_delete();

public:
  boolean_T matlabCodegenIsDeleted;
  int isInitialized;
  boolean_T isSetupComplete;
  cell_wrap_2 inputVarSize[1];
  int NumChannels;
  creal32_T Cache[5800321];
  int CumulativeOverrun;
  int CumulativeUnderrun;
  int ReadPointer;
  int WritePointer;
  boolean_T AsyncBuffercgHelper_isInitialized;
};

class b_AsyncBuffercgHelper {
public:
  int read(int numRows, ::coder::array<double, 1U> &out);
  static int ReadSamplesFromBuffer(const b_AsyncBuffercgHelper *obj,
                                   int numRowsCast,
                                   ::coder::array<double, 1U> &out, int &c);
  static int ReadSamplesFromBuffer(const b_AsyncBuffercgHelper &obj,
                                   int numRowsCast, int overlapCast,
                                   ::coder::array<double, 1U> &out,
                                   int &overlapUnderrun, int &c);
  void matlabCodegenDestructor();
  void release();
  void releaseWrapper();
  ~b_AsyncBuffercgHelper();
  b_AsyncBuffercgHelper();

protected:
  void releaseImpl();

private:
  void SystemCore_delete();

public:
  boolean_T matlabCodegenIsDeleted;
  int isInitialized;
  boolean_T isSetupComplete;
  cell_wrap_2 inputVarSize[1];
  int NumChannels;
  double Cache[5800321];
  int CumulativeOverrun;
  int CumulativeUnderrun;
  int ReadPointer;
  int WritePointer;
  boolean_T AsyncBuffercgHelper_isInitialized;
};

class c_AsyncBuffercgHelper {
public:
  int read(int numRows, ::coder::array<creal32_T, 1U> &out);
  static int ReadSamplesFromBuffer(const c_AsyncBuffercgHelper *obj,
                                   int numRowsCast,
                                   ::coder::array<creal32_T, 1U> &out, int &c);
  int stepImpl(const creal32_T in_data[], int in_size);
  void matlabCodegenDestructor();
  void release();
  void releaseWrapper();
  ~c_AsyncBuffercgHelper();
  c_AsyncBuffercgHelper();

protected:
  void releaseImpl();

private:
  void SystemCore_delete();

public:
  boolean_T matlabCodegenIsDeleted;
  int isInitialized;
  boolean_T isSetupComplete;
  cell_wrap_2 inputVarSize[1];
  int NumChannels;
  creal32_T Cache[600651];
  int CumulativeOverrun;
  int CumulativeUnderrun;
  int ReadPointer;
  int WritePointer;
  boolean_T AsyncBuffercgHelper_isInitialized;
};

} // namespace internal
} // namespace dsp
} // namespace coder

#endif
//
// File trailer for AsyncBuffercgHelper.h
//
// [EOF]
//
