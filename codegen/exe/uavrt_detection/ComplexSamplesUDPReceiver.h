//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ComplexSamplesUDPReceiver.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 21-Feb-2023 17:49:40
//

#ifndef COMPLEXSAMPLESUDPRECEIVER_H
#define COMPLEXSAMPLESUDPRECEIVER_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
class ComplexSamplesUDPReceiver {
public:
  void read(creal32_T complexData_data[], int *complexData_size) const;
  void init(double ipPort);
  int udpReceiver;
  double samplesPerFrame;
};

#endif
//
// File trailer for ComplexSamplesUDPReceiver.h
//
// [EOF]
//
