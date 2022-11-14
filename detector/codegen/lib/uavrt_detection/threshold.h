/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: threshold.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

#ifndef THRESHOLD_H
#define THRESHOLD_H

/* Include Files */
#include "rtwtypes.h"
#include "uavrt_detection_types.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void threshold_makenewthreshold(threshold *obj, const waveform *Wfm);

void threshold_setthreshold(threshold *obj, const waveform *WfmCurr,
                            const waveform *WfmPrev);

void threshold_threshold(double pf, double *obj_pf, double *obj_evMuParam,
                         double *obj_evSigmaParam,
                         emxArray_real_T *obj_threshVecFine);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for threshold.h
 *
 * [EOF]
 */
