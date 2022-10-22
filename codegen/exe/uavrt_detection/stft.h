//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: stft.h
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 22-Oct-2022 12:48:10
//

#ifndef STFT_H
#define STFT_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
namespace coder {
namespace internal {
class s_stickyStruct;

}
} // namespace coder

// Function Declarations
namespace coder {
void computeSTFT(const ::coder::array<creal_T, 2U> &x,
                 const internal::s_stickyStruct *opts,
                 ::coder::array<creal_T, 3U> &S, ::coder::array<double, 1U> &F,
                 ::coder::array<double, 2U> &T);

void stft(const ::coder::array<creal32_T, 2U> &x, double varargin_1,
          const ::coder::array<double, 1U> &varargin_3, double varargin_5,
          double varargin_7, ::coder::array<creal32_T, 2U> &varargout_1,
          ::coder::array<float, 1U> &varargout_2,
          ::coder::array<float, 1U> &varargout_3);

} // namespace coder

#endif
//
// File trailer for stft.h
//
// [EOF]
//
