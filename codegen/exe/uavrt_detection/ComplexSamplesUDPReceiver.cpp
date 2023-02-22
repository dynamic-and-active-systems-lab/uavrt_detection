//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ComplexSamplesUDPReceiver.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 21-Feb-2023 17:21:25
//

// Include Files
#include "ComplexSamplesUDPReceiver.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "udp.h"
#include <algorithm>
#include <cstring>
#include <string.h>

// Function Definitions
//
// Arguments    : double ipPort
// Return Type  : void
//
void ComplexSamplesUDPReceiver::init(double ipPort)
{
  //  Two floats = 2 * 4 bytes;
  samplesPerFrame = 2048.0;
  udpReceiver = udpReceiverSetup(ipPort);
  if (udpReceiver <= 0) {
    rtErrorWithMessageID(b_emlrtRTEI.fName, b_emlrtRTEI.lineNo);
  }
}

//
// Arguments    : creal32_T complexData_data[]
//                int *complexData_size
// Return Type  : void
//
void ComplexSamplesUDPReceiver::read(creal32_T complexData_data[],
                                     int *complexData_size) const
{
  creal32_T complexBuffer_data[2048];
  std::memset(&complexBuffer_data[0], 0, 2048U * sizeof(creal32_T));
  udpReceiverReadComplex(udpReceiver, &complexBuffer_data[0], 2048.0);
  *complexData_size = 2048;
  std::copy(&complexBuffer_data[0], &complexBuffer_data[2048],
            &complexData_data[0]);
}

//
// File trailer for ComplexSamplesUDPReceiver.cpp
//
// [EOF]
//
