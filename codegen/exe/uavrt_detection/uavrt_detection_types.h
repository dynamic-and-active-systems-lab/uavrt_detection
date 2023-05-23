//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: uavrt_detection_types.h
//
<<<<<<< HEAD
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 23-May-2023 12:05:02
=======
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Apr-2023 11:47:02
>>>>>>> 3930a1e557481905555f2756f2f70ac82e87beba
//

#ifndef UAVRT_DETECTION_TYPES_H
#define UAVRT_DETECTION_TYPES_H

// Include Files
#include "rtwtypes.h"
#define MAX_THREADS omp_get_max_threads()

// Type Definitions
struct rtDoubleCheckInfo {
  int lineNo;
  int colNo;
  const char *fName;
  const char *pName;
  int checkKind;
};

struct rtEqualityCheckInfo {
  int nDims;
  int lineNo;
  int colNo;
  const char *fName;
  const char *pName;
};

struct rtBoundsCheckInfo {
  int iFirst;
  int iLast;
  int lineNo;
  int colNo;
  const char *aName;
  const char *fName;
  const char *pName;
  int checkKind;
};

struct rtRunTimeErrorInfo {
  int lineNo;
  int colNo;
  const char *fName;
  const char *pName;
};

#endif
//
// File trailer for uavrt_detection_types.h
//
// [EOF]
//
