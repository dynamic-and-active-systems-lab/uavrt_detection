//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: udpPulseSenderSend.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 17:16:38
//

#ifndef UDPPULSESENDERSEND_H
#define UDPPULSESENDERSEND_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
void udpPulseSenderSend(int udpSender, unsigned int pulseInfo_tag_id,
                        unsigned int pulseInfo_frequency_hz,
                        double pulseInfo_start_time_seconds,
                        double pulseInfo_predict_next_start_seconds,
                        double pulseInfo_snr, double pulseInfo_stft_score,
                        unsigned short pulseInfo_group_ind,
                        double pulseInfo_group_snr,
                        unsigned char pulseInfo_detection_status,
                        unsigned char pulseInfo_confirmed_status);

#endif
//
// File trailer for udpPulseSenderSend.h
//
// [EOF]
//
