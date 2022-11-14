/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: uavrt_detection_initialize.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "uavrt_detection_initialize.h"
#include "CoderTimeAPI.h"
#include "channelreceiver.h"
#include "controlreceiver.h"
#include "eml_rand_mt19937ar_stateful.h"
#include "fileManager.h"
#include "rt_nonfinite.h"
#include "timeKeeper.h"
#include "uavrt_detection_data.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include "omp.h"

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : void
 */
void uavrt_detection_initialize(void)
{
  omp_init_nest_lock(&uavrt_detection_nestLockGlobal);
  savedTime_not_empty_init();
  freq_not_empty_init();
  channelreceiver_init();
  controlreceiver_init();
  filedata_init();
  c_eml_rand_mt19937ar_stateful_i();
  isInitialized_uavrt_detection = true;
}

/*
 * File trailer for uavrt_detection_initialize.c
 *
 * [EOF]
 */
