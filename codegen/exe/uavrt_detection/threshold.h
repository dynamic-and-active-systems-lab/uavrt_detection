//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: threshold.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 11-Aug-2023 12:59:41
//

#ifndef THRESHOLD_H
#define THRESHOLD_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
class waveform;

// Type Definitions
class threshold {
public:
  void makenewthreshold(const waveform &Wfm);
  double pf;
  double evMuParam;
  double evSigmaParam;
  coder::array<double, 1U> threshVecFine;
  unsigned int trials;
};

#endif
//
// File trailer for threshold.h
//
// [EOF]
//
