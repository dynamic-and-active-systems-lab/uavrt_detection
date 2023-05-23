//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: wfmstft.h
//
<<<<<<< HEAD
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 23-May-2023 12:05:02
=======
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Apr-2023 11:47:02
>>>>>>> 3930a1e557481905555f2756f2f70ac82e87beba
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
