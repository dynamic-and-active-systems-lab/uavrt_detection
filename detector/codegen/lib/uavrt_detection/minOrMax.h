/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: minOrMax.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

#ifndef MINORMAX_H
#define MINORMAX_H

/* Include Files */
#include "rtwtypes.h"
#include "uavrt_detection_types.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void b_maximum(const emxArray_real_T *x, emxArray_real_T *ex,
               emxArray_int32_T *idx);

void c_maximum(const emxArray_real_T *x, double *ex, int *idx);

double d_maximum(const double x[2]);

double maximum(const emxArray_real_T *x);

double minimum(const double x[2]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for minOrMax.h
 *
 * [EOF]
 */
