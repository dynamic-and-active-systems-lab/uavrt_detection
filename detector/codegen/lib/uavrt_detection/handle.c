/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: handle.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "handle.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_internal_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"

/* Function Definitions */
/*
 * Arguments    : e_dsp_internal_AsyncBuffercgHel *obj
 * Return Type  : void
 */
void b_handle_matlabCodegenDestructo(e_dsp_internal_AsyncBuffercgHel *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    if (obj->isInitialized == 1) {
      obj->isInitialized = 2;
      if (obj->isSetupComplete) {
        obj->ReadPointer = 1;
        obj->WritePointer = 2;
        obj->CumulativeOverrun = 0;
        obj->CumulativeUnderrun = 0;
        obj->c_AsyncBuffercgHelper_isInitial = false;
        obj->NumChannels = -1;
      }
    }
  }
}

/*
 * Arguments    : d_dsp_internal_AsyncBuffercgHel *obj
 * Return Type  : void
 */
void c_handle_matlabCodegenDestructo(d_dsp_internal_AsyncBuffercgHel *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    if (obj->isInitialized == 1) {
      obj->isInitialized = 2;
      if (obj->isSetupComplete) {
        obj->ReadPointer = 1;
        obj->WritePointer = 2;
        obj->CumulativeOverrun = 0;
        obj->CumulativeUnderrun = 0;
        obj->c_AsyncBuffercgHelper_isInitial = false;
        obj->NumChannels = -1;
      }
    }
  }
}

/*
 * Arguments    : c_dsp_internal_AsyncBuffercgHel *obj
 * Return Type  : void
 */
void handle_matlabCodegenDestructor(c_dsp_internal_AsyncBuffercgHel *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    if (obj->isInitialized == 1) {
      obj->isInitialized = 2;
      if (obj->isSetupComplete) {
        obj->ReadPointer = 1;
        obj->WritePointer = 2;
        obj->CumulativeOverrun = 0;
        obj->CumulativeUnderrun = 0;
        obj->c_AsyncBuffercgHelper_isInitial = false;
        obj->NumChannels = -1;
      }
    }
  }
}

/*
 * File trailer for handle.c
 *
 * [EOF]
 */
