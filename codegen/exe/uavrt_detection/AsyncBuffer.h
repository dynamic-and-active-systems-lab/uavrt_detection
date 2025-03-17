//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: AsyncBuffer.h
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

#ifndef ASYNCBUFFER_H
#define ASYNCBUFFER_H

// Include Files
#include "AsyncBufferSysObj.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
namespace dsp {
class AsyncBuffer {
public:
  AsyncBuffer *init();
  void reset();
  void write(const array<creal32_T, 1U> &in);
  int get_NumUnreadSamples() const;
  void read(double numRows, array<creal32_T, 1U> &out);
  void read(double numRows, double overlap, array<creal32_T, 1U> &out);
  void matlabCodegenDestructor();
  ~AsyncBuffer();
  AsyncBuffer();
  boolean_T matlabCodegenIsDeleted;
  internal::codegen::AsyncBufferSysObj pBuffer;
};

class b_AsyncBuffer {
public:
  void write(const array<double, 1U> &in);
  void read(double numRows, array<double, 1U> &out);
  void read(double numRows, double overlap, array<double, 1U> &out);
  void reset();
  b_AsyncBuffer *init();
  void matlabCodegenDestructor();
  ~b_AsyncBuffer();
  b_AsyncBuffer();
  boolean_T matlabCodegenIsDeleted;
  internal::codegen::b_AsyncBufferSysObj pBuffer;
};

class c_AsyncBuffer {
public:
  c_AsyncBuffer *init();
  void write();
  void read();
  void reset();
  int get_NumUnreadSamples() const;
  void read(array<creal32_T, 1U> &out);
  void matlabCodegenDestructor();
  void write(const creal32_T in_data[]);
  ~c_AsyncBuffer();
  c_AsyncBuffer();
  boolean_T matlabCodegenIsDeleted;
  internal::codegen::c_AsyncBufferSysObj pBuffer;
};

} // namespace dsp
} // namespace coder

#endif
//
// File trailer for AsyncBuffer.h
//
// [EOF]
//
