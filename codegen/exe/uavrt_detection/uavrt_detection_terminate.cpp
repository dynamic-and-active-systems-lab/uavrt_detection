//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: uavrt_detection_terminate.cpp
//
<<<<<<< HEAD
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 23-May-2023 12:05:02
=======
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Apr-2023 11:47:02
>>>>>>> 3930a1e557481905555f2756f2f70ac82e87beba
//

// Include Files
#include "uavrt_detection_terminate.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "omp.h"

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
void uavrt_detection_terminate()
{
  omp_destroy_nest_lock(&uavrt_detection_nestLockGlobal);
  isInitialized_uavrt_detection = false;
}

//
// File trailer for uavrt_detection_terminate.cpp
//
// [EOF]
//
