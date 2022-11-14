/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: fileManager.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

/* Include Files */
#include "rtwtypes.h"
#include "uavrt_detection_types.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
signed char b_cfopen(const emxArray_char_T *cfilename);

int cfclose(double fid);

signed char cfopen(const char cfilename[25]);

void filedata_init(void);

void getfilestar(double fid, FILE **filestar, bool *autoflush);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for fileManager.h
 *
 * [EOF]
 */
