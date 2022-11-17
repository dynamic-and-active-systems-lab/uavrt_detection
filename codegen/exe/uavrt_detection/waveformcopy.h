//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// waveformcopy.h
//
// Code generation for function 'waveformcopy'
//

#ifndef WAVEFORMCOPY_H
#define WAVEFORMCOPY_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
class waveform;

class wfmstft;

class pulsestats;

// Function Declarations
waveform *waveformcopy(waveform *wfmIn, wfmstft *iobj_0, pulsestats *iobj_1,
                       waveform *iobj_2);

#endif
// End of code generation (waveformcopy.h)
