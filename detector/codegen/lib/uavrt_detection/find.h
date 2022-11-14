/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: find.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

#ifndef FIND_H
#define FIND_H

/* Include Files */
#include "rtwtypes.h"
#include "uavrt_detection_types.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void b_eml_find(const emxArray_boolean_T *x, emxArray_int32_T *i);

void c_eml_find(const emxArray_boolean_T *x, int i_data[], int *i_size);

void d_eml_find(const emxArray_boolean_T *x, int i_data[], int *i_size);

void e_eml_find(const emxArray_int32_T *x_colidx,
                const emxArray_int32_T *x_rowidx, emxArray_int32_T *i,
                emxArray_int32_T *j);

void eml_find(const emxArray_boolean_T *x, int i_data[], int i_size[2]);

void i_binary_expand_op(int in1_data[], int *in1_size,
                        const emxArray_real_T *in2, int in3, int in4,
                        const waveform *in5, int in6, int in7);

void j_binary_expand_op(int in1_data[], int *in1_size,
                        const emxArray_real_T *in2, int in3, int in4, int in5,
                        const waveform *in6, int in7, int in8, int in9);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for find.h
 *
 * [EOF]
 */
