//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: wfmstft.h
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 20-Oct-2022 20:46:49
//

#ifndef WFMSTFT_H
#define WFMSTFT_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
class wfmstft {
public:
  void updatepsd();
  coder::array<creal_T, 2U> S;
  coder::array<double, 1U> f;
  coder::array<double, 1U> t;
  coder::array<double, 1U> psd;
  double dt;
  double T;
  coder::array<double, 1U> wind;
};

#endif
//
// File trailer for wfmstft.h
//
// [EOF]
//
