/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: pause.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "pause.h"
#include "rt_nonfinite.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include "coder_posix_time.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
/*
 * Arguments    : double varargin_1
 * Return Type  : void
 */
void pause(double varargin_1)
{
  coderTimespec b_timespec;
  double delay;
  double delayInt;
  delay = varargin_1;
  if ((varargin_1 < 0.0) || rtIsNaN(varargin_1)) {
    delay = 0.0;
  }
  delayInt = floor(delay);
  if (delayInt > 4.294967295E+9) {
    delayInt = 4.294967295E+9;
  }
  delay -= delayInt;
  if (delay > 0.0) {
    b_timespec.tv_nsec = floor(delay * 1.0E+9);
  } else {
    b_timespec.tv_nsec = 0.0;
  }
  b_timespec.tv_sec = delayInt;
  coderTimeSleep(&b_timespec);
}

/*
 * File trailer for pause.c
 *
 * [EOF]
 */
