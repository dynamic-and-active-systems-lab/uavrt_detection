/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: str2double1.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

#ifndef STR2DOUBLE1_H
#define STR2DOUBLE1_H

/* Include Files */
#include "rtwtypes.h"
#include "uavrt_detection_types.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void readfloat(emxArray_char_T *s1, int *idx, const emxArray_char_T *s, int *k,
               int n, bool *isimag, bool *b_finite, double *nfv,
               bool *foundsign, bool *success);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for str2double1.h
 *
 * [EOF]
 */
