//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: PulseInfoStruct.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 21-Feb-2023 17:49:40
//

#ifndef PULSEINFOSTRUCT_H
#define PULSEINFOSTRUCT_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
class PulseInfoStruct {
public:
  void sendOverUDP() const;
  double tag_id;
  double frequency_hz;
  double start_time_seconds;
  double predict_next_start_seconds;
  double snr;
  double stft_score;
  double group_ind;
  double group_snr;
  double detection_status;
  double confirmed_status;
  int udpSender;
  double udpBufferSizeBytes;
};

#endif
//
// File trailer for PulseInfoStruct.h
//
// [EOF]
//
