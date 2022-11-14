/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: validator_check_size.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

#ifndef VALIDATOR_CHECK_SIZE_H
#define VALIDATOR_CHECK_SIZE_H

/* Include Files */
#include "rtwtypes.h"
#include "uavrt_detection_types.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void b_validator_check_size(const emxArray_struct_T *in,
                            emxArray_struct_T *out);

void c_validator_check_size(emxArray_struct_T *in);

void d_validator_check_size(emxArray_boolean_T *in);

void e_validator_check_size(emxArray_real_T *in);

void validator_check_size(const emxArray_real_T *in, emxArray_real_T *out);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for validator_check_size.h
 *
 * [EOF]
 */
