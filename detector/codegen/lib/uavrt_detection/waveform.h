/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: waveform.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

#ifndef WAVEFORM_H
#define WAVEFORM_H

/* Include Files */
#include "rtwtypes.h"
#include "uavrt_detection_types.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void b_waveform_spectro(waveform *obj, wfmstft *iobj_0);

b_waveform *b_waveform_waveform(b_waveform *obj, const creal32_T x[1000],
                                double Fs, pulsestats *ps_pre,
                                pulsestats *iobj_0, wfmstft *iobj_1);

void c_waveform_setprioridependentpr(waveform *obj, const pulsestats *ps_obj);

waveform *c_waveform_waveform(waveform *obj, const emxArray_creal32_T *x,
                              double Fs, double t_0, pulsestats *ps_pre,
                              const threshold thresh, pulsestats *iobj_0,
                              wfmstft *iobj_1);

void waveform_process(waveform *obj, char mode,
                      const emxArray_real_T *excluded_freq_bands);

void waveform_setweightingmatrix(waveform *obj);

void waveform_spectro(b_waveform *obj, wfmstft *iobj_0);

waveform *waveform_waveform(waveform *obj, const creal32_T x[1000], double Fs,
                            pulsestats *ps_pre, const threshold thresh);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for waveform.h
 *
 * [EOF]
 */
