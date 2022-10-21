//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: randn.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 20-Oct-2022 20:46:49
//

// Include Files
#include "randn.h"
#include "eml_rand_mt19937ar.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : creal_T r[1000]
// Return Type  : void
//
namespace coder {
void complexLike(creal_T r[1000])
{
  double im;
  double re;
  for (int k{0}; k < 1000; k++) {
    re = eml_rand_mt19937ar(state);
    im = eml_rand_mt19937ar(state);
    r[k].re = re;
    r[k].im = im;
  }
  for (int k{0}; k < 1000; k++) {
    double ai;
    im = r[k].re;
    ai = r[k].im;
    if (ai == 0.0) {
      re = im / 1.4142135623730951;
      im = 0.0;
    } else if (im == 0.0) {
      re = 0.0;
      im = ai / 1.4142135623730951;
    } else {
      re = im / 1.4142135623730951;
      im = ai / 1.4142135623730951;
    }
    r[k].re = re;
    r[k].im = im;
  }
}

//
// Arguments    : double varargin_1
//                ::coder::array<creal_T, 2U> &r
// Return Type  : void
//
void complexLike(double varargin_1, ::coder::array<creal_T, 2U> &r)
{
  double im;
  double re;
  int i;
  int k;
  r.set_size(static_cast<int>(varargin_1), 100);
  i = static_cast<int>(varargin_1) * 100;
  for (k = 0; k < i; k++) {
    re = eml_rand_mt19937ar(state);
    im = eml_rand_mt19937ar(state);
    r[k].re = re;
    r[k].im = im;
  }
  k = r.size(0) * 100;
  r.set_size(r.size(0), 100);
  for (i = 0; i < k; i++) {
    double ai;
    im = r[i].re;
    ai = r[i].im;
    if (ai == 0.0) {
      re = im / 1.4142135623730951;
      im = 0.0;
    } else if (im == 0.0) {
      re = 0.0;
      im = ai / 1.4142135623730951;
    } else {
      re = im / 1.4142135623730951;
      im = ai / 1.4142135623730951;
    }
    r[i].re = re;
    r[i].im = im;
  }
}

//
// Arguments    : double r[1000]
// Return Type  : void
//
void randn(double r[1000])
{
  for (int k{0}; k < 1000; k++) {
    r[k] = eml_rand_mt19937ar(state);
  }
}

//
// Arguments    : double varargin_1
//                ::coder::array<double, 2U> &r
// Return Type  : void
//
void randn(double varargin_1, ::coder::array<double, 2U> &r)
{
  int i;
  r.set_size(static_cast<int>(varargin_1), 100);
  i = static_cast<int>(varargin_1) * 100;
  for (int k{0}; k < i; k++) {
    r[k] = eml_rand_mt19937ar(state);
  }
}

} // namespace coder

//
// File trailer for randn.cpp
//
// [EOF]
//
