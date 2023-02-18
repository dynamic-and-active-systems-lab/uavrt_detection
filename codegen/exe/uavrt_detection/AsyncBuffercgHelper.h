//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: AsyncBuffercgHelper.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 18-Feb-2023 14:54:54
//

#ifndef ASYNCBUFFERCGHELPER_H
#define ASYNCBUFFERCGHELPER_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
struct cell_wrap_3 {
  unsigned int f1[8];
};

namespace coder {
namespace dsp {
namespace internal {
class AsyncBuffercgHelper {
public:
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
  int NumChannels;
  creal32_T Cache[49621];
  int CumulativeOverrun;
  int CumulativeUnderrun;
  int ReadPointer;
  int WritePointer;
  boolean_T AsyncBuffercgHelper_isInitialized;

private:
  cell_wrap_3 inputVarSize[1];
};

class b_AsyncBuffercgHelper {
public:
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
  int NumChannels;
  double Cache[49621];
  int CumulativeOverrun;
  int CumulativeUnderrun;
  int ReadPointer;
  int WritePointer;
  boolean_T AsyncBuffercgHelper_isInitialized;

private:
  cell_wrap_3 inputVarSize[1];
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
