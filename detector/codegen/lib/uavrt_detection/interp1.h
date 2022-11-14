/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: interp1.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

#ifndef INTERP1_H
#define INTERP1_H

/* Include Files */
#include "rtwtypes.h"
#include "uavrt_detection_types.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void b_interp1Linear(const double y[2], const emxArray_real_T *xi,
                     emxArray_real_T *yi);

void interp1(const emxArray_real_T *varargin_1,
             const emxArray_real_T *varargin_2,
             const emxArray_real_T *varargin_3, emxArray_real_T *Vq);

void interp1Linear(const double y[2], const emxArray_real_T *xi,
                   emxArray_real_T *yi, const double varargin_1[2]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for interp1.h
 *
 * [EOF]
 */
