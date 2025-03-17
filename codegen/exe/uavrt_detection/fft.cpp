//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: fft.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 04-Feb-2025 09:56:05
//

// Include Files
#include "fft.h"
#include "FFTImplementationCallback.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const array<creal_T, 2U> &x
//                array<creal_T, 2U> &y
// Return Type  : void
//
namespace coder {
void fft(const array<creal_T, 2U> &x, array<creal_T, 2U> &y)
{
  array<double, 2U> costab;
  array<double, 2U> sintab;
  array<double, 2U> sintabinv;
  int nRows;
  if (x.size(0) == 1) {
    v_rtErrorWithMessageID(db_emlrtRTEI.fName, db_emlrtRTEI.lineNo);
  }
  if (x.size(0) == 0) {
    y.set_size(0, 1);
  } else {
    int N2blue;
    boolean_T useRadix2;
    useRadix2 =
        (static_cast<int>(static_cast<unsigned int>(x.size(0)) &
                          static_cast<unsigned int>(x.size(0) - 1)) == 0);
    N2blue = internal::fft::FFTImplementationCallback::get_algo_sizes(
        x.size(0), useRadix2, nRows);
    internal::fft::FFTImplementationCallback::generate_twiddle_tables(
        nRows, useRadix2, costab, sintab, sintabinv);
    if (useRadix2) {
      internal::fft::FFTImplementationCallback::r2br_r2dit_trig(
          x, x.size(0), costab, sintab, y);
    } else {
      internal::fft::FFTImplementationCallback::dobluesteinfft(
          x, N2blue, x.size(0), costab, sintab, sintabinv, y);
    }
  }
}

} // namespace coder

//
// File trailer for fft.cpp
//
// [EOF]
//
