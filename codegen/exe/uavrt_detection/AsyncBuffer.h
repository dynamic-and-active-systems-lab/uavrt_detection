//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: AsyncBuffer.h
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 22-Oct-2022 12:48:10
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
  void read(double numRows, ::coder::array<double, 1U> &out);
  void read(double numRows, double overlap, ::coder::array<double, 1U> &out);
  AsyncBuffer *init();
  void matlabCodegenDestructor();
  void write(const double in_data[]);
  ~AsyncBuffer();
  AsyncBuffer();
  boolean_T matlabCodegenIsDeleted;
  internal::AsyncBuffercgHelper pBuffer;
};

class b_AsyncBuffer {
public:
  void read(double numRows, ::coder::array<creal32_T, 1U> &out);
  void read(double numRows, double overlap, ::coder::array<creal32_T, 1U> &out);
  void matlabCodegenDestructor();
  void write(const creal32_T in_data[]);
  ~b_AsyncBuffer();
  b_AsyncBuffer();
  boolean_T matlabCodegenIsDeleted;
  internal::b_AsyncBuffercgHelper pBuffer;
};

} // namespace dsp
} // namespace coder

#endif
//
// File trailer for AsyncBuffer.h
//
// [EOF]
//
