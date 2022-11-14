/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: fseek.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "fseek.h"
#include "fileManager.h"
#include "rt_nonfinite.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <stdio.h>

/* Function Definitions */
/*
 * Arguments    : double fileID
 *                double offset
 * Return Type  : void
 */
void b_fseek(double fileID, double offset)
{
  FILE *filestar;
  int wherefrom;
  bool a;
  wherefrom = SEEK_SET;
  if ((!rtIsInf(offset)) && (!rtIsNaN(offset)) && (floor(offset) == offset)) {
    getfilestar(fileID, &filestar, &a);
    if ((!(fileID != 0.0)) || (!(fileID != 1.0)) || (!(fileID != 2.0))) {
      filestar = NULL;
    }
    if (!(filestar == NULL)) {
      fseek(filestar, (long int)offset, wherefrom);
    }
  }
}

/*
 * File trailer for fseek.c
 *
 * [EOF]
 */
