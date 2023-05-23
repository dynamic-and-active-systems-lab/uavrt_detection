//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: DetectorConfig.cpp
//
<<<<<<< HEAD
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 23-May-2023 12:05:02
=======
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Apr-2023 11:47:02
>>>>>>> 3930a1e557481905555f2756f2f70ac82e87beba
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
  opMode.init();
  excldFreqs.set_size(1, 2);
  excldFreqs[0] = rtInf;
  excldFreqs[1] = rtMinusInf;
  falseAlarmProb = 0.01;
  dataRecordPath.Value.set_size(1, 0);
}

//
// File trailer for DetectorConfig.cpp
//
// [EOF]
//
