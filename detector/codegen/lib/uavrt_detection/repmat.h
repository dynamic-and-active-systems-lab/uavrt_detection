/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: repmat.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

#ifndef REPMAT_H
#define REPMAT_H

/* Include Files */
#include "rtwtypes.h"
#include "uavrt_detection_types.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void b_repmat(const emxArray_real_T *a, double varargin_1, emxArray_real_T *b);

void c_repmat(const b_struct_T *a, double varargin_1, double varargin_2,
              emxArray_struct_T *b);

void repmat(const emxArray_real_T *a, double varargin_2, emxArray_real_T *b);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for repmat.h
 *
 * [EOF]
 */
