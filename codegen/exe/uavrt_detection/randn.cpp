//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// randn.cpp
//
// Code generation for function 'randn'
//

// Include files
#include "randn.h"
#include "eml_rand_mt19937ar.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "coder_array.h"
#include <string.h>

// Function Definitions
namespace coder {
void randn(double r[1000])
{
  for (int k{0}; k < 1000; k++) {
    r[k] = eml_rand_mt19937ar(state);
  }
}

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

// End of code generation (randn.cpp)
