//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: FFTImplementationCallback.h
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 20-Oct-2022 20:46:49
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
class FFTImplementationCallback {
public:
  static void get_algo_sizes(int nfft, boolean_T useRadix2, int *n2blue,
                             int *nRows);
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

} // namespace internal
} // namespace coder

#endif
//
// File trailer for FFTImplementationCallback.h
//
// [EOF]
//
