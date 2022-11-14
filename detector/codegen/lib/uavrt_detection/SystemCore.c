/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: SystemCore.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "SystemCore.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"

/* Function Definitions */
/*
 * Arguments    : dspcodegen_UDPReceiver *obj
 * Return Type  : void
 */
void SystemCore_release(dspcodegen_UDPReceiver *obj)
{
  char *sErr;
  if (obj->isInitialized == 1) {
    obj->isInitialized = 2;
    if (obj->isSetupComplete) {
      /* System object Destructor function: dsp.UDPReceiver */
      /* System object Terminate function: dsp.UDPReceiver */
      sErr = GetErrorBuffer(&obj->cSFunObject.W0_NetworkLib[0U]);
      LibTerminate(&obj->cSFunObject.W0_NetworkLib[0U]);
      if (*sErr != 0) {
        PrintError(sErr);
      }
      LibDestroy(&obj->cSFunObject.W0_NetworkLib[0U], 0);
      DestroyUDPInterface(&obj->cSFunObject.W0_NetworkLib[0U]);
    }
  }
}

/*
 * Arguments    : b_dspcodegen_UDPReceiver *obj
 * Return Type  : void
 */
void b_SystemCore_release(b_dspcodegen_UDPReceiver *obj)
{
  char *sErr;
  if (obj->isInitialized == 1) {
    obj->isInitialized = 2;
    if (obj->isSetupComplete) {
      /* System object Destructor function: dsp.UDPReceiver */
      /* System object Terminate function: dsp.UDPReceiver */
      sErr = GetErrorBuffer(&obj->cSFunObject.W0_NetworkLib[0U]);
      LibTerminate(&obj->cSFunObject.W0_NetworkLib[0U]);
      if (*sErr != 0) {
        PrintError(sErr);
      }
      LibDestroy(&obj->cSFunObject.W0_NetworkLib[0U], 0);
      DestroyUDPInterface(&obj->cSFunObject.W0_NetworkLib[0U]);
    }
  }
}

/*
 * File trailer for SystemCore.c
 *
 * [EOF]
 */
