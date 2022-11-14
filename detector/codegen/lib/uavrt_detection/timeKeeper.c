/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: timeKeeper.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "timeKeeper.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include "coder_posix_time.h"

/* Variable Definitions */
static coderTimespec savedTime;

static bool savedTime_not_empty;

/* Function Definitions */
/*
 * Arguments    : double *outTime_tv_sec
 *                double *outTime_tv_nsec
 * Return Type  : void
 */
void b_timeKeeper(double *outTime_tv_sec, double *outTime_tv_nsec)
{
  *outTime_tv_sec = savedTime.tv_sec;
  *outTime_tv_nsec = savedTime.tv_nsec;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void savedTime_not_empty_init(void)
{
  savedTime_not_empty = false;
}

/*
 * Arguments    : double newTime_tv_sec
 *                double newTime_tv_nsec
 * Return Type  : void
 */
void timeKeeper(double newTime_tv_sec, double newTime_tv_nsec)
{
  if (!savedTime_not_empty) {
    coderTimespec b_timespec;
    if (!freq_not_empty) {
      freq_not_empty = true;
      coderInitTimeFunctions(&freq);
    }
    coderTimeClockGettimeMonotonic(&b_timespec, freq);
    savedTime_not_empty = true;
  }
  savedTime.tv_sec = newTime_tv_sec;
  savedTime.tv_nsec = newTime_tv_nsec;
}

/*
 * File trailer for timeKeeper.c
 *
 * [EOF]
 */
