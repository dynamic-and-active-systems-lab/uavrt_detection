/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: mtimes.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

#ifndef MTIMES_H
#define MTIMES_H

/* Include Files */
#include "rtwtypes.h"
#include "uavrt_detection_types.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void b_sparse_mtimes(const emxArray_boolean_T *a_d,
                     const emxArray_int32_T *a_colidx,
                     const emxArray_int32_T *a_rowidx, int a_m, int a_n,
                     const emxArray_real_T *b, emxArray_real_T *c);

void c_sparse_mtimes(const emxArray_real_T *a, const emxArray_boolean_T *b_d,
                     const emxArray_int32_T *b_colidx,
                     const emxArray_int32_T *b_rowidx, int b_n,
                     emxArray_real_T *c);

void sparse_mtimes(const emxArray_real_T *a, const emxArray_real_T *b_d,
                   const emxArray_int32_T *b_colidx,
                   const emxArray_int32_T *b_rowidx, int b_n,
                   emxArray_real_T *c);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for mtimes.h
 *
 * [EOF]
 */
