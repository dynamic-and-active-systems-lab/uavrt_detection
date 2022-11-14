/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: computeDFT.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

#ifndef COMPUTEDFT_H
#define COMPUTEDFT_H

/* Include Files */
#include "rtwtypes.h"
#include "uavrt_detection_types.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void computeDFT(const emxArray_creal32_T *xin, double nfft, double varargin_1,
                emxArray_creal32_T *Xx, emxArray_real_T *f);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for computeDFT.h
 *
 * [EOF]
 */
