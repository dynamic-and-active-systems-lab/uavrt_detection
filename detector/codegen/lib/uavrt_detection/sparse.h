/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: sparse.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

#ifndef SPARSE_H
#define SPARSE_H

/* Include Files */
#include "rtwtypes.h"
#include "uavrt_detection_types.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void b_sparse(const emxArray_real_T *varargin_1, emxArray_real_T *y_d,
              emxArray_int32_T *y_colidx, emxArray_int32_T *y_rowidx, int *y_m,
              int *y_maxnz);

void sparse(const emxArray_boolean_T *varargin_1, emxArray_boolean_T *y_d,
            emxArray_int32_T *y_colidx, emxArray_int32_T *y_rowidx, int *y_n);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for sparse.h
 *
 * [EOF]
 */
