//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: wfmcsvwrite.h
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

#ifndef WFMCSVWRITE_H
#define WFMCSVWRITE_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
class waveform;

// Function Declarations
void wfmcsvwrite(waveform &X, double radioFcMHz,
                 const coder::array<char, 2U> &filePath);

void wfmcsvwrite_init();

#endif
//
// File trailer for wfmcsvwrite.h
//
// [EOF]
//
