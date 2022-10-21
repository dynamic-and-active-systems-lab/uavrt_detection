//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: threshold.h
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 20-Oct-2022 20:46:49
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
  void init();
  void makenewthreshold(const waveform *Wfm);
  void setthreshold(const waveform *WfmCurr, const waveform *WfmPrev);

protected:
  void setthreshprops(double thresh, const waveform *Wfm);

public:
  double pf;
  double evMuParam;
  double evSigmaParam;
  coder::array<double, 1U> threshVecFine;
};

#endif
//
// File trailer for threshold.h
//
// [EOF]
//
