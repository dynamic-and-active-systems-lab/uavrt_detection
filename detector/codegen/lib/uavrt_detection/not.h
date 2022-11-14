/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: not.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

#ifndef NOT_H
#define NOT_H

/* Include Files */
#include "rtwtypes.h"
#include "uavrt_detection_types.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void sparse_not(const emxArray_int32_T *S_colidx,
                const emxArray_int32_T *S_rowidx, int S_n,
                emxArray_boolean_T *out_d, emxArray_int32_T *out_colidx,
                emxArray_int32_T *out_rowidx, int *out_n);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for not.h
 *
 * [EOF]
 */
