//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// threshold.h
//
// Code generation for function 'threshold'
//

#ifndef THRESHOLD_H
#define THRESHOLD_H

// Include files
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
// End of code generation (threshold.h)
