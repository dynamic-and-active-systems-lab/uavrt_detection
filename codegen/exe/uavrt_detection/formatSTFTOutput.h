//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: formatSTFTOutput.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 25-Sep-2023 11:48:59
//

#ifndef FORMATSTFTOUTPUT_H
#define FORMATSTFTOUTPUT_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace b_signal {
namespace internal {
namespace stft {
void formatSTFTOutput(::coder::array<creal32_T, 2U> &S,
                      const ::coder::array<double, 1U> &F,
                      ::coder::array<double, 1U> &Fout);

void formatSTFTOutput(::coder::array<creal_T, 3U> &S,
                      const ::coder::array<double, 1U> &F,
                      ::coder::array<double, 1U> &Fout);

} // namespace stft
} // namespace internal
} // namespace b_signal
} // namespace coder

#endif
//
// File trailer for formatSTFTOutput.h
//
// [EOF]
//
