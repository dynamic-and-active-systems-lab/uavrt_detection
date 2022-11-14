/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: heapsort.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

#ifndef HEAPSORT_H
#define HEAPSORT_H

/* Include Files */
#include "rtwtypes.h"
#include "uavrt_detection_types.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void b_heapsort(emxArray_int32_T *x, int xstart, int xend,
                const emxArray_int32_T *cmp_workspace_a,
                const emxArray_int32_T *cmp_workspace_b);

void c_heapsort(emxArray_int32_T *x, int xstart, int xend,
                const emxArray_int32_T *cmp_workspace_x);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for heapsort.h
 *
 * [EOF]
 */
