//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: udpPulseSenderSend.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 17:51:34
//

// Include Files
#include "udpPulseSenderSend.h"
#include "rt_nonfinite.h"
#include "udp.h"
#include <algorithm>
#include <cstddef>
#include <cstring>
#include <string.h>

// Function Definitions
//
// Arguments    : int udpSender
//                unsigned int pulseInfo_tag_id
//                unsigned int pulseInfo_frequency_hz
//                double pulseInfo_start_time_seconds
//                double pulseInfo_predict_next_start_seconds
//                double pulseInfo_snr
//                double pulseInfo_stft_score
//                unsigned short pulseInfo_group_ind
//                double pulseInfo_group_snr
//                unsigned char pulseInfo_detection_status
//                unsigned char pulseInfo_confirmed_status
// Return Type  : void
//
void udpPulseSenderSend(int udpSender, unsigned int pulseInfo_tag_id,
                        unsigned int pulseInfo_frequency_hz,
                        double pulseInfo_start_time_seconds,
                        double pulseInfo_predict_next_start_seconds,
                        double pulseInfo_snr, double pulseInfo_stft_score,
                        unsigned short pulseInfo_group_ind,
                        double pulseInfo_group_snr,
                        unsigned char pulseInfo_detection_status,
                        unsigned char pulseInfo_confirmed_status)
{
  double x;
  unsigned char bytes_data[108];
  unsigned char c_y[8];
  unsigned char d_y[8];
  unsigned char e_y[8];
  unsigned char f_y[8];
  unsigned char h_y[8];
  unsigned char b_y[4];
  unsigned char y[4];
  unsigned char g_y[2];
  unsigned char i_y;
  unsigned char j_y;
  std::memcpy((void *)&y[0], (void *)&pulseInfo_tag_id,
              (unsigned int)((size_t)4 * sizeof(unsigned char)));
  std::memcpy((void *)&b_y[0], (void *)&pulseInfo_frequency_hz,
              (unsigned int)((size_t)4 * sizeof(unsigned char)));
  std::memcpy((void *)&c_y[0], (void *)&pulseInfo_start_time_seconds,
              (unsigned int)((size_t)8 * sizeof(unsigned char)));
  std::memcpy((void *)&d_y[0], (void *)&pulseInfo_predict_next_start_seconds,
              (unsigned int)((size_t)8 * sizeof(unsigned char)));
  std::memcpy((void *)&e_y[0], (void *)&pulseInfo_snr,
              (unsigned int)((size_t)8 * sizeof(unsigned char)));
  std::memcpy((void *)&f_y[0], (void *)&pulseInfo_stft_score,
              (unsigned int)((size_t)8 * sizeof(unsigned char)));
  std::memcpy((void *)&g_y[0], (void *)&pulseInfo_group_ind,
              (unsigned int)((size_t)2 * sizeof(unsigned char)));
  std::memcpy((void *)&h_y[0], (void *)&pulseInfo_group_snr,
              (unsigned int)((size_t)8 * sizeof(unsigned char)));
  std::copy(&pulseInfo_detection_status, &pulseInfo_detection_status + 1U,
            &i_y);
  std::copy(&pulseInfo_confirmed_status, &pulseInfo_confirmed_status + 1U,
            &j_y);
  bytes_data[0] = y[0];
  bytes_data[4] = b_y[0];
  bytes_data[1] = y[1];
  bytes_data[5] = b_y[1];
  bytes_data[2] = y[2];
  bytes_data[6] = b_y[2];
  bytes_data[3] = y[3];
  bytes_data[7] = b_y[3];
  bytes_data[40] = g_y[0];
  bytes_data[41] = g_y[1];
  for (int i{0}; i < 8; i++) {
    bytes_data[i + 8] = c_y[i];
    bytes_data[i + 16] = d_y[i];
    bytes_data[i + 24] = e_y[i];
    bytes_data[i + 32] = f_y[i];
    bytes_data[i + 42] = h_y[i];
  }
  bytes_data[50] = i_y;
  bytes_data[51] = j_y;
  x = rtNaN;
  std::memcpy((void *)&c_y[0], (void *)&x,
              (unsigned int)((size_t)8 * sizeof(unsigned char)));
  for (int i{0}; i < 8; i++) {
    bytes_data[i + 52] = c_y[i];
  }
  x = rtNaN;
  std::memcpy((void *)&c_y[0], (void *)&x,
              (unsigned int)((size_t)8 * sizeof(unsigned char)));
  for (int i{0}; i < 8; i++) {
    bytes_data[i + 60] = c_y[i];
  }
  x = rtNaN;
  std::memcpy((void *)&c_y[0], (void *)&x,
              (unsigned int)((size_t)8 * sizeof(unsigned char)));
  for (int i{0}; i < 8; i++) {
    bytes_data[i + 68] = c_y[i];
  }
  x = rtNaN;
  std::memcpy((void *)&c_y[0], (void *)&x,
              (unsigned int)((size_t)8 * sizeof(unsigned char)));
  for (int i{0}; i < 8; i++) {
    bytes_data[i + 76] = c_y[i];
  }
  x = rtNaN;
  std::memcpy((void *)&c_y[0], (void *)&x,
              (unsigned int)((size_t)8 * sizeof(unsigned char)));
  for (int i{0}; i < 8; i++) {
    bytes_data[i + 84] = c_y[i];
  }
  x = rtNaN;
  std::memcpy((void *)&c_y[0], (void *)&x,
              (unsigned int)((size_t)8 * sizeof(unsigned char)));
  for (int i{0}; i < 8; i++) {
    bytes_data[i + 92] = c_y[i];
  }
  x = rtNaN;
  std::memcpy((void *)&c_y[0], (void *)&x,
              (unsigned int)((size_t)8 * sizeof(unsigned char)));
  for (int i{0}; i < 8; i++) {
    bytes_data[i + 100] = c_y[i];
  }
  udpSenderSend(udpSender, &bytes_data[0], 108.0);
}

//
// File trailer for udpPulseSenderSend.cpp
//
// [EOF]
//
