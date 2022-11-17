//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// formatSTFTOutput.h
//
// Code generation for function 'formatSTFTOutput'
//

#ifndef FORMATSTFTOUTPUT_H
#define FORMATSTFTOUTPUT_H

// Include files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace signal {
namespace internal {
namespace stft {
void formatSTFTOutput(::coder::array<creal32_T, 2U> &S,
                      ::coder::array<double, 1U> &F,
                      const char opts_FreqRange[8], double opts_NumFreqSamples);

void formatSTFTOutput(::coder::array<creal_T, 3U> &S,
                      ::coder::array<double, 1U> &F,
                      const char opts_FreqRange[8], double opts_NumFreqSamples);

} // namespace stft
} // namespace internal
} // namespace signal
} // namespace coder

#endif
// End of code generation (formatSTFTOutput.h)
