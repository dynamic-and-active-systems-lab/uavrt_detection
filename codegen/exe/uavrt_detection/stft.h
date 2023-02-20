//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: stft.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 14:31:55
//

#ifndef STFT_H
#define STFT_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
void stft(const ::coder::array<creal32_T, 2U> &x, double varargin_1,
          const ::coder::array<double, 1U> &varargin_3, double varargin_5,
          double varargin_7, ::coder::array<creal32_T, 2U> &varargout_1,
          ::coder::array<float, 1U> &varargout_2,
          ::coder::array<float, 1U> &varargout_3);

void stft(const int x_size[2], const double varargin_3_data[],
          int varargin_3_size, double varargin_5, double varargin_7);

} // namespace coder

#endif
//
// File trailer for stft.h
//
// [EOF]
//
