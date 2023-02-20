//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: singlecomplex2int.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 16:02:05
//

// Include Files
#include "singlecomplex2int.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include <cmath>
#include <string.h>

// Function Definitions
//
// singlecomplex2int Converts a complex single precision positive
// number with a portion of the integer digits in the real and imaginary
// parts to integer value. The integer is split at the 7th digit. The top
// digits are then held in the real part of the input, while the lower 7
// digits are held in the imaginary part of the input. These digits are
// recombined to create a double precision output of the integer.
//
// A single precision number has a maximum integer
// values of flintmax('single') = 16777216. To avoid overrunning the
// available digits, the output integer is split at digit 7.
//
// The max value for each input part would be:   16777216 + 1i * 16777216
// To avoid overflow, the complex part
// containing the lower digits only use          16777216 + 1i *  xxxxxxx
// the first 7 digits available
//
// Based on this standard, the maximum value that can be transmitted is
//    167772169999999 = 1.6777e14;
//
// INPUTS:
//    singleComplex   Matrix of where each elements' imaginary part contains
//                    the bottom 7 digits of the output integer. The inputs
//                    real part contain the upper digits of the output.
//                    The maximum value of the input real part is 16,777,216.
//                    The maximum value of the imaginary part if 9,999,999.
//                    An error is generated if these values are exceeded.
//                    Imaginary parts (lower digits) must be positive. Sign
//                    can be contained in the upper digits (real part). Real
//                    and imaginary parts must only contain integers.
// OUTPUTS:
//    intOut           Matrix of integer values.
//                    Maximum input value is 167772169999999. Inputs
//                    exceedign this value will result in an error.
//
// Arguments    : const creal32_T singleComplex
// Return Type  : double
//
double singlecomplex2int(const creal32_T singleComplex)
{
  //
  // -------------------------------------------------------------------------
  // Author:    Michael Shafer
  // Date:      2022-08-19
  // -------------------------------------------------------------------------
  if ((!(singleComplex.re == std::floor(singleComplex.re))) ||
      (!(singleComplex.im == std::floor(singleComplex.im)))) {
    rtErrorWithMessageID(b_emlrtRTEI.fName, b_emlrtRTEI.lineNo);
  }
  if ((singleComplex.im > 9.999999E+6F) || (singleComplex.im < 0.0F)) {
    rtErrorWithMessageID(b_emlrtRTEI.fName, b_emlrtRTEI.lineNo);
  }
  return singleComplex.re * 1.0E+7 + singleComplex.im;
}

//
// File trailer for singlecomplex2int.cpp
//
// [EOF]
//
