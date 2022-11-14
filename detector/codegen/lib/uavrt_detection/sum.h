/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: sum.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

#ifndef SUM_H
#define SUM_H

/* Include Files */
#include "rtwtypes.h"
#include "uavrt_detection_types.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void b_sum(const emxArray_real_T *x_d, const emxArray_int32_T *x_colidx,
           int x_m, int x_n, emxArray_real_T *y_d, emxArray_int32_T *y_colidx,
           emxArray_int32_T *y_rowidx, int *y_n);

void c_sum(const emxArray_real_T *x_d, const emxArray_int32_T *x_colidx,
           int x_m, emxArray_real_T *y_d, emxArray_int32_T *y_colidx,
           emxArray_int32_T *y_rowidx);

void d_sum(const emxArray_real_T *x, emxArray_real_T *y);

double sum(const emxArray_real_T *x);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for sum.h
 *
 * [EOF]
 */
