//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: threshold.h
//
<<<<<<< HEAD
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 23-May-2023 12:05:02
=======
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Apr-2023 11:47:02
>>>>>>> 3930a1e557481905555f2756f2f70ac82e87beba
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
