/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: sparse1.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

#ifndef SPARSE1_H
#define SPARSE1_H

/* Include Files */
#include "rtwtypes.h"
#include "uavrt_detection_types.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void b_sparse_parenAssign(c_sparse *this, const emxArray_real_T *rhs,
                          const emxArray_real_T *varargin_1);

void b_sparse_parenReference(const emxArray_real_T *this_d,
                             const emxArray_int32_T *this_colidx,
                             const emxArray_int32_T *this_rowidx, int this_m,
                             emxArray_real_T *s_d, emxArray_int32_T *s_colidx,
                             emxArray_int32_T *s_rowidx, int *s_m,
                             int *s_maxnz);

void c_sparse_parenReference(const emxArray_real_T *this_d,
                             const emxArray_int32_T *this_colidx,
                             const emxArray_int32_T *this_rowidx, int this_m,
                             const emxArray_real_T *varargin_2, d_sparse *s);

void sparse_eq(const emxArray_real_T *a_d, const emxArray_int32_T *a_colidx,
               const emxArray_int32_T *a_rowidx, int a_n,
               const emxArray_real_T *b_d, const emxArray_int32_T *b_colidx,
               emxArray_boolean_T *s_d, emxArray_int32_T *s_colidx,
               emxArray_int32_T *s_rowidx, int *s_n);

void sparse_logical(const emxArray_real_T *this_d,
                    const emxArray_int32_T *this_colidx,
                    const emxArray_int32_T *this_rowidx, int this_m, int this_n,
                    int this_maxnz, emxArray_boolean_T *y_d,
                    emxArray_int32_T *y_colidx, emxArray_int32_T *y_rowidx,
                    int *y_m, int *y_n, int *y_maxnz);

void sparse_parenAssign(c_sparse *this, const emxArray_boolean_T *rhs_d,
                        const emxArray_int32_T *rhs_colidx,
                        const emxArray_int32_T *rhs_rowidx, int rhs_m,
                        const emxArray_real_T *varargin_1);

void sparse_parenReference(const emxArray_boolean_T *this_d,
                           const emxArray_int32_T *this_colidx,
                           const emxArray_int32_T *this_rowidx, int this_m,
                           const emxArray_real_T *varargin_1,
                           emxArray_boolean_T *s_d, emxArray_int32_T *s_colidx,
                           emxArray_int32_T *s_rowidx, int *s_n);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for sparse1.h
 *
 * [EOF]
 */
