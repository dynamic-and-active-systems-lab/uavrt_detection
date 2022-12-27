//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// AsyncBuffer.h
//
// Code generation for function 'AsyncBuffer'
//

#ifndef ASYNCBUFFER_H
#define ASYNCBUFFER_H

// Include files
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
  void write(const creal32_T in[4096]);
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
  void write(const double in[4096]);
  void read(double numRows, ::coder::array<double, 1U> &out);
  void read(double numRows, double overlap, ::coder::array<double, 1U> &out);
  void matlabCodegenDestructor();
  ~b_AsyncBuffer();
  b_AsyncBuffer();
  boolean_T matlabCodegenIsDeleted;
  internal::b_AsyncBuffercgHelper pBuffer;
};

} // namespace dsp
} // namespace coder

#endif
// End of code generation (AsyncBuffer.h)
