/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: stft.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

#ifndef STFT_H
#define STFT_H

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
void computeSTFT(
    const emxArray_creal_T *x, double c_opts_next_next_next_next_next,
    double d_opts_next_next_next_next_next,
    double e_opts_next_next_next_next_next,
    const emxArray_real_T *f_opts_next_next_next_next_next,
    const h_coder_internal_stickyStruct g_opts_next_next_next_next_next,
    emxArray_creal_T *S, emxArray_real_T *F, emxArray_real_T *T);

void stft(const emxArray_creal32_T *x, double varargin_1,
          const emxArray_real_T *varargin_3, double varargin_5,
          double varargin_7, emxArray_creal32_T *varargout_1,
          emxArray_real32_T *varargout_2, emxArray_real32_T *varargout_3);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for stft.h
 *
 * [EOF]
 */
