//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: FFTImplementationCallback.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 14:31:55
//

#ifndef FFTIMPLEMENTATIONCALLBACK_H
#define FFTIMPLEMENTATIONCALLBACK_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
namespace internal {
namespace fft {
class FFTImplementationCallback {
public:
  static void r2br_r2dit_trig(const ::coder::array<creal32_T, 2U> &x,
                              int n1_unsigned,
                              const ::coder::array<float, 2U> &costab,
                              const ::coder::array<float, 2U> &sintab,
                              ::coder::array<creal32_T, 2U> &y);
  static void dobluesteinfft(const ::coder::array<creal32_T, 2U> &x, int n2blue,
                             int nfft, const ::coder::array<float, 2U> &costab,
                             const ::coder::array<float, 2U> &sintab,
                             const ::coder::array<float, 2U> &sintabinv,
                             ::coder::array<creal32_T, 2U> &y);

protected:
  static void r2br_r2dit_trig_impl(const ::coder::array<creal32_T, 1U> &x,
                                   int unsigned_nRows,
                                   const ::coder::array<float, 2U> &costab,
                                   const ::coder::array<float, 2U> &sintab,
                                   ::coder::array<creal32_T, 1U> &y);
};

} // namespace fft
} // namespace internal
} // namespace coder

#endif
//
// File trailer for FFTImplementationCallback.h
//
// [EOF]
//
