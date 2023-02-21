//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: udpSamplesReceiverRead.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 16:51:51
//

// Include Files
#include "udpSamplesReceiverRead.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "udp.h"
#include <string.h>

// Function Definitions
//
// Arguments    : int udpReceiver
//                coder::array<creal32_T, 1U> &complexData
// Return Type  : void
//
void udpSamplesReceiverRead(int udpReceiver,
                            coder::array<creal32_T, 1U> &complexData)
{
  coder::array<creal32_T, 2U> complexBuffer;
  complexBuffer.set_size(1, 16384);
  for (int i{0}; i < 16384; i++) {
    complexBuffer[i].re = 0.0F;
    complexBuffer[i].im = 0.0F;
  }
  udpReceiverRead(udpReceiver, &complexBuffer[0], 16384.0);
  complexData.set_size(16384);
  for (int i{0}; i < 16384; i++) {
    complexData[i] = complexBuffer[i];
  }
}

//
// File trailer for udpSamplesReceiverRead.cpp
//
// [EOF]
//
