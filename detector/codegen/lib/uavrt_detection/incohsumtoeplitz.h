/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: incohsumtoeplitz.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

#ifndef INCOHSUMTOEPLITZ_H
#define INCOHSUMTOEPLITZ_H

/* Include Files */
#include "rtwtypes.h"
#include "uavrt_detection_types.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void incohsumtoeplitz(const emxArray_boolean_T *Fb,
                      const emxArray_creal_T *Wfherm, const emxArray_creal_T *S,
                      const emxArray_real_T *Tb, const emxArray_real_T *Wq_d,
                      const emxArray_int32_T *Wq_colidx,
                      const emxArray_int32_T *Wq_rowidx, int Wq_m, int Wq_n,
                      emxArray_real_T *Sscores, emxArray_real_T *Scols);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for incohsumtoeplitz.h
 *
 * [EOF]
 */
