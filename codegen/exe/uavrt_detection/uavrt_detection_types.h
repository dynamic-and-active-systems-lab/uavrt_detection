//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: uavrt_detection_types.h
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

#ifndef UAVRT_DETECTION_TYPES_H
#define UAVRT_DETECTION_TYPES_H

// Include Files
#include "rtwtypes.h"
#define MAX_THREADS omp_get_max_threads()

// Type Definitions
struct rtRunTimeErrorInfo {
  int lineNo;
  const char *fName;
};

struct rtDoubleCheckInfo {
  int lineNo;
  const char *fName;
};

struct rtBoundsCheckInfo {
  int lineNo;
  const char *aName;
  const char *fName;
};

struct rtEqualityCheckInfo {
  int nDims;
  int lineNo;
  const char *fName;
};

#endif
//
// File trailer for uavrt_detection_types.h
//
// [EOF]
//
