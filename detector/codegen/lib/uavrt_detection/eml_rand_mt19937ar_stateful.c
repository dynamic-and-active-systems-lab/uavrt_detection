/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: eml_rand_mt19937ar_stateful.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "eml_rand_mt19937ar_stateful.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : void
 */
void c_eml_rand_mt19937ar_stateful_i(void)
{
  int mti;
  unsigned int r;
  memset(&state[0], 0, 625U * sizeof(unsigned int));
  r = 5489U;
  state[0] = 5489U;
  for (mti = 0; mti < 623; mti++) {
    r = ((r ^ r >> 30U) * 1812433253U + (unsigned int)mti) + 1U;
    state[mti + 1] = r;
  }
  state[624] = 624U;
}

/*
 * File trailer for eml_rand_mt19937ar_stateful.c
 *
 * [EOF]
 */
