/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: locBsearch.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

#ifndef LOCBSEARCH_H
#define LOCBSEARCH_H

/* Include Files */
#include "rtwtypes.h"
#include "uavrt_detection_types.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void b_sparse_locBsearch(const emxArray_int32_T *x, int xi, int xstart,
                         int xend, int *n, bool *found);

void sparse_locBsearch(const emxArray_int32_T *x, double xi, int xstart,
                       int xend, int *n, bool *found);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for locBsearch.h
 *
 * [EOF]
 */
