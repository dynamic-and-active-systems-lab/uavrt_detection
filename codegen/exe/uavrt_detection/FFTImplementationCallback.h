//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: FFTImplementationCallback.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 11-Aug-2023 08:04:26
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
  static int get_algo_sizes(int nfft, boolean_T useRadix2, int &nRows);
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
  static void generate_twiddle_tables(int nRows, boolean_T useRadix2,
                                      ::coder::array<double, 2U> &costab,
                                      ::coder::array<double, 2U> &sintab,
                                      ::coder::array<double, 2U> &sintabinv);
  static void r2br_r2dit_trig(const ::coder::array<creal_T, 2U> &x,
                              int n1_unsigned,
                              const ::coder::array<double, 2U> &costab,
                              const ::coder::array<double, 2U> &sintab,
                              ::coder::array<creal_T, 2U> &y);
  static void dobluesteinfft(const ::coder::array<creal_T, 2U> &x, int n2blue,
                             int nfft, const ::coder::array<double, 2U> &costab,
                             const ::coder::array<double, 2U> &sintab,
                             const ::coder::array<double, 2U> &sintabinv,
                             ::coder::array<creal_T, 2U> &y);
  static void r2br_r2dit_trig(const ::coder::array<creal_T, 3U> &x,
                              int n1_unsigned,
                              const ::coder::array<double, 2U> &costab,
                              const ::coder::array<double, 2U> &sintab,
                              ::coder::array<creal_T, 3U> &y);
  static void dobluesteinfft(const ::coder::array<creal_T, 3U> &x, int n2blue,
                             int nfft, const ::coder::array<double, 2U> &costab,
                             const ::coder::array<double, 2U> &sintab,
                             const ::coder::array<double, 2U> &sintabinv,
                             ::coder::array<creal_T, 3U> &y);

protected:
  static void r2br_r2dit_trig_impl(const ::coder::array<creal32_T, 1U> &x,
                                   int unsigned_nRows,
                                   const ::coder::array<float, 2U> &costab,
                                   const ::coder::array<float, 2U> &sintab,
                                   ::coder::array<creal32_T, 1U> &y);
  static void r2br_r2dit_trig_impl(const ::coder::array<creal_T, 1U> &x,
                                   int unsigned_nRows,
                                   const ::coder::array<double, 2U> &costab,
                                   const ::coder::array<double, 2U> &sintab,
                                   ::coder::array<creal_T, 1U> &y);
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
