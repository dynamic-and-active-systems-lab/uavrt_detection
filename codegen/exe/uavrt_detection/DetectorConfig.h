//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: DetectorConfig.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 17:16:38
//

#ifndef DETECTORCONFIG_H
#define DETECTORCONFIG_H

// Include Files
#include "rtwtypes.h"
#include "string1.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
class DetectorConfig {
public:
  void init();
  double ID;
  double channelCenterFreqMHz;
  double portData;
  double Fs;
  double tagFreqMHz;
  double tp;
  double tip;
  double tipu;
  double tipj;
  double K;
  coder::rtString opMode;
  coder::array<double, 2U> excldFreqs;
  double falseAlarmProb;
  coder::rtString dataRecordPath;
};

#endif
//
// File trailer for DetectorConfig.h
//
// [EOF]
//
