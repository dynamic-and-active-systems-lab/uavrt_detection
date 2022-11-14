/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: introsort.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

#ifndef INTROSORT_H
#define INTROSORT_H

/* Include Files */
#include "rtwtypes.h"
#include "uavrt_detection_types.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void b_introsort(emxArray_int32_T *x, int xend,
                 const emxArray_int32_T *cmp_workspace_x);

void introsort(emxArray_int32_T *x, int xend,
               const emxArray_int32_T *cmp_workspace_a,
               const emxArray_int32_T *cmp_workspace_b);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for introsort.h
 *
 * [EOF]
 */
