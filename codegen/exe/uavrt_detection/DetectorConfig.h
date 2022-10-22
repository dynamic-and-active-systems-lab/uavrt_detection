//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: DetectorConfig.h
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Oct-2022 17:38:50
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
  double channelCenterFreqMHz;
  double portData;
  double Fs;
  double tagFreqMHz;
  double tp;
  double tip;
  double tipu;
  double tipj;
  double K;
  coder::b_rtString opMode;
  coder::array<double, 2U> excldFreqs;
  double falseAlarmProb;
  coder::b_rtString dataRecordPath;
};

#endif
//
// File trailer for DetectorConfig.h
//
// [EOF]
//
