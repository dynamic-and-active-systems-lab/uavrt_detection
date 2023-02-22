//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: PulseInfoStruct.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 21-Feb-2023 17:21:25
//

// Include Files
#include "PulseInfoStruct.h"
#include "rt_nonfinite.h"
#include "udp.h"
#include <cstddef>
#include <cstring>
#include <string.h>

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
void PulseInfoStruct::sendOverUDP() const
{
  unsigned char pulseInfoBytes[80];
  unsigned char confirmed_status_bytes[8];
  unsigned char detection_status_bytes[8];
  unsigned char frequency_hz_bytes[8];
  unsigned char group_ind_bytes[8];
  unsigned char group_snr_bytes[8];
  unsigned char predict_next_start_seconds_bytes[8];
  unsigned char snr_bytes[8];
  unsigned char start_time_seconds_bytes[8];
  unsigned char stft_score_bytes[8];
  unsigned char tag_id_bytes[8];
  std::memcpy((void *)&tag_id_bytes[0], (void *)&tag_id,
              (unsigned int)((size_t)8 * sizeof(unsigned char)));
  std::memcpy((void *)&frequency_hz_bytes[0], (void *)&frequency_hz,
              (unsigned int)((size_t)8 * sizeof(unsigned char)));
  std::memcpy((void *)&start_time_seconds_bytes[0], (void *)&start_time_seconds,
              (unsigned int)((size_t)8 * sizeof(unsigned char)));
  std::memcpy((void *)&predict_next_start_seconds_bytes[0],
              (void *)&predict_next_start_seconds,
              (unsigned int)((size_t)8 * sizeof(unsigned char)));
  std::memcpy((void *)&snr_bytes[0], (void *)&snr,
              (unsigned int)((size_t)8 * sizeof(unsigned char)));
  std::memcpy((void *)&stft_score_bytes[0], (void *)&stft_score,
              (unsigned int)((size_t)8 * sizeof(unsigned char)));
  std::memcpy((void *)&group_ind_bytes[0], (void *)&group_ind,
              (unsigned int)((size_t)8 * sizeof(unsigned char)));
  std::memcpy((void *)&group_snr_bytes[0], (void *)&group_snr,
              (unsigned int)((size_t)8 * sizeof(unsigned char)));
  std::memcpy((void *)&detection_status_bytes[0], (void *)&detection_status,
              (unsigned int)((size_t)8 * sizeof(unsigned char)));
  std::memcpy((void *)&confirmed_status_bytes[0], (void *)&confirmed_status,
              (unsigned int)((size_t)8 * sizeof(unsigned char)));
  for (int i{0}; i < 8; i++) {
    pulseInfoBytes[i] = tag_id_bytes[i];
    pulseInfoBytes[i + 8] = frequency_hz_bytes[i];
    pulseInfoBytes[i + 16] = start_time_seconds_bytes[i];
    pulseInfoBytes[i + 24] = predict_next_start_seconds_bytes[i];
    pulseInfoBytes[i + 32] = snr_bytes[i];
    pulseInfoBytes[i + 40] = stft_score_bytes[i];
    pulseInfoBytes[i + 48] = group_ind_bytes[i];
    pulseInfoBytes[i + 56] = group_snr_bytes[i];
    pulseInfoBytes[i + 64] = detection_status_bytes[i];
    pulseInfoBytes[i + 72] = confirmed_status_bytes[i];
  }
  udpSenderSend(udpSender, &pulseInfoBytes[0], udpBufferSizeBytes);
}

//
// File trailer for PulseInfoStruct.cpp
//
// [EOF]
//
