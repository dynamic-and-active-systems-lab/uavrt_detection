//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: DetectorConfig.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 04-Mar-2024 13:02:36
//

// Include Files
#include "DetectorConfig.h"
#include "rt_nonfinite.h"
#include "string1.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
void DetectorConfig::init()
{
  ID = 1.0;
  channelCenterFreqMHz = 150.0;
  portData = 1.0;
  Fs = 192000.0;
  tagFreqMHz = 150.0;
  tp = 0.02;
  tip = 1.0;
  tipu = 0.0;
  tipj = 0.0;
  K = 1.0;
  excldFreqs.set_size(1, 2);
  excldFreqs[0] = rtInf;
  excldFreqs[1] = rtMinusInf;
  falseAlarmProb = 0.01;
  logPath.Value.set_size(1, 0);
  startIndex = 1.0;
}

//
// File trailer for DetectorConfig.cpp
//
// [EOF]
//
