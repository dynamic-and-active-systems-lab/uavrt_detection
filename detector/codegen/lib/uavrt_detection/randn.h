/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: randn.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

#ifndef RANDN_H
#define RANDN_H

/* Include Files */
#include "rtwtypes.h"
#include "uavrt_detection_types.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void b_complexLike(creal_T r[1000]);

void b_randn(double varargin_1, emxArray_real_T *r);

void complexLike(double varargin_1, emxArray_creal_T *r);

void randn(double r[1000]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for randn.h
 *
 * [EOF]
 */
