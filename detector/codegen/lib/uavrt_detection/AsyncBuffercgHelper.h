/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: AsyncBuffercgHelper.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

#ifndef ASYNCBUFFERCGHELPER_H
#define ASYNCBUFFERCGHELPER_H

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
void AsyncBuffercgHelper_read(d_dsp_internal_AsyncBuffercgHel *obj, int numRows,
                              emxArray_creal32_T *out, int *underrun);

int AsyncBuffercgHelper_stepImpl(c_dsp_internal_AsyncBuffercgHel *obj,
                                 const creal32_T in_data[], int in_size);

int b_AsyncBuffercgHelper_stepImpl(e_dsp_internal_AsyncBuffercgHel *obj,
                                   const double in_data[], int in_size);

int c_AsyncBuffercgHelper_stepImpl(d_dsp_internal_AsyncBuffercgHel *obj,
                                   const creal32_T in_data[], int in_size);

void d_AsyncBuffercgHelper_ReadSampl(const c_dsp_internal_AsyncBuffercgHel *obj,
                                     int numRowsCast, emxArray_creal32_T *out,
                                     int *underrun, int *c);

void e_AsyncBuffercgHelper_ReadSampl(const e_dsp_internal_AsyncBuffercgHel *obj,
                                     int numRowsCast, emxArray_real_T *out,
                                     int *underrun, int *c);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for AsyncBuffercgHelper.h
 *
 * [EOF]
 */
