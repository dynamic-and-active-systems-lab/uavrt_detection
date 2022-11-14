/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: any.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

#ifndef ANY_H
#define ANY_H

/* Include Files */
#include "rtwtypes.h"
#include "uavrt_detection_types.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void any(const emxArray_int32_T *x_colidx, const emxArray_int32_T *x_rowidx,
         int x_n, emxArray_boolean_T *y_d, emxArray_int32_T *y_colidx,
         emxArray_int32_T *y_rowidx);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for any.h
 *
 * [EOF]
 */
