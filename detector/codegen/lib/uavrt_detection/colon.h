/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: colon.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

#ifndef COLON_H
#define COLON_H

/* Include Files */
#include "rtwtypes.h"
#include "uavrt_detection_types.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void eml_float_colon(double a, double b, emxArray_real_T *y);

void eml_integer_colon_dispatcher(int a, emxArray_int32_T *y);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for colon.h
 *
 * [EOF]
 */
