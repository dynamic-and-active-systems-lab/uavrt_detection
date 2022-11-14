/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: ftell.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "ftell.h"
#include "fileManager.h"
#include "rt_nonfinite.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include <stdio.h>

/* Function Definitions */
/*
 * Arguments    : double fileID
 * Return Type  : double
 */
double b_ftell(double fileID)
{
  FILE *filestar;
  double position;
  bool a;
  getfilestar(fileID, &filestar, &a);
  if ((!(fileID != 0.0)) || (!(fileID != 1.0)) || (!(fileID != 2.0))) {
    filestar = NULL;
  }
  if (filestar == NULL) {
    position = -1.0;
  } else {
    long position_t;
    position_t = ftell(filestar);
    position = (double)position_t;
  }
  return position;
}

/*
 * File trailer for ftell.c
 *
 * [EOF]
 */
