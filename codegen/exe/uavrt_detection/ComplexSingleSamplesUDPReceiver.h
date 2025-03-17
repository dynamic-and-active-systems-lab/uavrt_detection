//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ComplexSingleSamplesUDPReceiver.h
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

#ifndef COMPLEXSINGLESAMPLESUDPRECEIVER_H
#define COMPLEXSINGLESAMPLESUDPRECEIVER_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
class ComplexSingleSamplesUDPReceiver {
public:
  int receive(creal32_T complexData_data[]) const;
  void init(double ipPort);
  int udpReceiver;
};

#endif
//
// File trailer for ComplexSingleSamplesUDPReceiver.h
//
// [EOF]
//
