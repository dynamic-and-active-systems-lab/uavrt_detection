//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: AsyncBuffercgHelper.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 16:51:51
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
  void read(int numRows, ::coder::array<creal32_T, 1U> &out, int *underrun);
  static void ReadSamplesFromBuffer(const AsyncBuffercgHelper *obj,
                                    int numRowsCast,
                                    ::coder::array<creal32_T, 1U> &out,
                                    int *underrun, int *c);
  static void ReadSamplesFromBuffer(const AsyncBuffercgHelper *obj,
                                    int numRowsCast, int overlapCast,
                                    ::coder::array<creal32_T, 1U> &out,
                                    int *underrun, int *overlapUnderrun,
                                    int *c);
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
  void read(int numRows, ::coder::array<double, 1U> &out, int *underrun);
  static void ReadSamplesFromBuffer(const b_AsyncBuffercgHelper *obj,
                                    int numRowsCast,
                                    ::coder::array<double, 1U> &out,
                                    int *underrun, int *c);
  static void ReadSamplesFromBuffer(const b_AsyncBuffercgHelper *obj,
                                    int numRowsCast, int overlapCast,
                                    ::coder::array<double, 1U> &out,
                                    int *underrun, int *overlapUnderrun,
                                    int *c);
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
  void read(int numRows, ::coder::array<creal32_T, 1U> &out, int *underrun);
  static void ReadSamplesFromBuffer(const c_AsyncBuffercgHelper *obj,
                                    int numRowsCast,
                                    ::coder::array<creal32_T, 1U> &out,
                                    int *underrun, int *c);
  int stepImpl(const ::coder::array<creal32_T, 1U> &in);
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
