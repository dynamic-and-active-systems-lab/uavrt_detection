/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: AsyncBuffer.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

#ifndef ASYNCBUFFER_H
#define ASYNCBUFFER_H

/* Include Files */
#include "rtwtypes.h"
#include "uavrt_detection_internal_types.h"
#include "uavrt_detection_types.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void AsyncBuffer_read(b_dsp_AsyncBuffer *obj);

void AsyncBuffer_release(dsp_AsyncBuffer *obj);

void AsyncBuffer_write(b_dsp_AsyncBuffer *obj);

void b_AsyncBuffer_read(b_dsp_AsyncBuffer *obj, emxArray_creal32_T *out);

void b_AsyncBuffer_release(c_dsp_AsyncBuffer *obj);

void b_AsyncBuffer_write(dsp_AsyncBuffer *obj, const creal32_T in_data[],
                         int in_size);

void c_AsyncBuffer_read(dsp_AsyncBuffer *obj, double numRows,
                        emxArray_creal32_T *out);

void c_AsyncBuffer_release(b_dsp_AsyncBuffer *obj);

void c_AsyncBuffer_write(c_dsp_AsyncBuffer *obj, const double in_data[],
                         int in_size);

void d_AsyncBuffer_read(c_dsp_AsyncBuffer *obj, double numRows,
                        emxArray_real_T *out);

void d_AsyncBuffer_write(b_dsp_AsyncBuffer *obj, const creal32_T in_data[],
                         int in_size);

void e_AsyncBuffer_read(dsp_AsyncBuffer *obj, double numRows, double overlap,
                        emxArray_creal32_T *out);

void f_AsyncBuffer_read(c_dsp_AsyncBuffer *obj, double numRows, double overlap,
                        emxArray_real_T *out);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for AsyncBuffer.h
 *
 * [EOF]
 */
