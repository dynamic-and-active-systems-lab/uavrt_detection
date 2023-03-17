//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: AsyncBuffer.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 16-Mar-2023 20:12:42
//

#ifndef ASYNCBUFFER_H
#define ASYNCBUFFER_H

// Include Files
#include "AsyncBuffercgHelper.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
namespace dsp {
class AsyncBuffer {
public:
  void reset();
  void write(const ::coder::array<creal32_T, 1U> &in);
  void read(double numRows, ::coder::array<creal32_T, 1U> &out);
  void read(double numRows, double overlap, ::coder::array<creal32_T, 1U> &out);
  void matlabCodegenDestructor();
  ~AsyncBuffer();
  AsyncBuffer();
  boolean_T matlabCodegenIsDeleted;
  internal::AsyncBuffercgHelper pBuffer;
};

class b_AsyncBuffer {
public:
  void write(const ::coder::array<double, 1U> &in);
  void read(double numRows, ::coder::array<double, 1U> &out);
  void read(double numRows, double overlap, ::coder::array<double, 1U> &out);
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
  void reset();
  void write(const creal32_T in_data[], int in_size);
  void read(::coder::array<creal32_T, 1U> &out);
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
