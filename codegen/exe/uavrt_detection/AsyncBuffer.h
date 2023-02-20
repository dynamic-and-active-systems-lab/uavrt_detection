//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: AsyncBuffer.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 14:31:55
//

#ifndef ASYNCBUFFER_H
#define ASYNCBUFFER_H

// Include Files
#include "AsyncBuffercgHelper.h"
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
namespace dsp {
class AsyncBuffer {
public:
  void reset();
  void write(const creal32_T in_data[], int in_size);
  void read(int numRows, creal32_T out_data[], int *out_size);
  void read(double numRows, creal32_T out_data[], int *out_size);
  void matlabCodegenDestructor();
  ~AsyncBuffer();
  AsyncBuffer();
  boolean_T matlabCodegenIsDeleted;
  internal::AsyncBuffercgHelper pBuffer;
};

class b_AsyncBuffer {
public:
  void write(const double in_data[], int in_size);
  void read(double numRows, double out_data[], int *out_size);
  void reset();
  void matlabCodegenDestructor();
  ~b_AsyncBuffer();
  b_AsyncBuffer();
  boolean_T matlabCodegenIsDeleted;
  internal::b_AsyncBuffercgHelper pBuffer;
};

class c_AsyncBuffer {
public:
  void write();
  void read();
  void write(const creal32_T in_data[], int in_size);
  void read(creal32_T out_data[], int *out_size);
  void matlabCodegenDestructor();
  ~c_AsyncBuffer();
  c_AsyncBuffer();
  boolean_T matlabCodegenIsDeleted;
  internal::c_AsyncBuffercgHelper pBuffer;
};

} // namespace dsp
} // namespace coder

#endif
//
// File trailer for AsyncBuffer.h
//
// [EOF]
//
