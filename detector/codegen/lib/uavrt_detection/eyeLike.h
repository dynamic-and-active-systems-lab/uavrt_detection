/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: eyeLike.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

#ifndef EYELIKE_H
#define EYELIKE_H

/* Include Files */
#include "rtwtypes.h"
#include "uavrt_detection_types.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void sparse_eyeLike(int ndiag, int m, int n, emxArray_real_T *I_d,
                    emxArray_int32_T *I_colidx, emxArray_int32_T *I_rowidx,
                    int *I_m, int *I_n, int *I_maxnz);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for eyeLike.h
 *
 * [EOF]
 */
