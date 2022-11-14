/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: fwrite.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "fwrite.h"
#include "fileManager.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include <stddef.h>
#include <stdio.h>

/* Function Definitions */
/*
 * Arguments    : double fileID
 *                const emxArray_real32_T *x
 * Return Type  : double
 */
double b_fwrite(double fileID, const emxArray_real32_T *x)
{
  FILE *filestar;
  double count;
  const float *x_data;
  bool autoflush;
  x_data = x->data;
  getfilestar(fileID, &filestar, &autoflush);
  if (!(fileID != 0.0)) {
    filestar = NULL;
  }
  if ((filestar == NULL) || (x->size[0] == 0)) {
    count = 0.0;
  } else {
    size_t bytesOutSizet;
    bytesOutSizet =
        fwrite(&x_data[0], sizeof(float), (size_t)x->size[0], filestar);
    count = (double)bytesOutSizet;
    if (((double)bytesOutSizet > 0.0) && autoflush) {
      int status;
      status = fflush(filestar);
      if (status != 0) {
        count = 0.0;
      }
    }
  }
  return count;
}

/*
 * File trailer for fwrite.c
 *
 * [EOF]
 */
