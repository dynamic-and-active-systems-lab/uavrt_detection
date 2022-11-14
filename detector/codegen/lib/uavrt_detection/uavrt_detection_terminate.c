/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: uavrt_detection_terminate.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "uavrt_detection_terminate.h"
#include "channelreceiver.h"
#include "controlreceiver.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include "omp.h"

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : void
 */
void uavrt_detection_terminate(void)
{
  controlreceiver_free();
  channelreceiver_free();
  omp_destroy_nest_lock(&uavrt_detection_nestLockGlobal);
  isInitialized_uavrt_detection = false;
}

/*
 * File trailer for uavrt_detection_terminate.c
 *
 * [EOF]
 */
