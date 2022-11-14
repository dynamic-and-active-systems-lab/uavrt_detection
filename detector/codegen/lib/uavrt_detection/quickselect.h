/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: quickselect.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

#ifndef QUICKSELECT_H
#define QUICKSELECT_H

/* Include Files */
#include "rtwtypes.h"
#include "uavrt_detection_types.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void quickselect(emxArray_real_T *v, int n, int vlen, double *vn, int *nfirst,
                 int *nlast);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for quickselect.h
 *
 * [EOF]
 */
