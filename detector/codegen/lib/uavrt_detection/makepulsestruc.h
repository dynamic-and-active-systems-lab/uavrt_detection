/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: makepulsestruc.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

#ifndef MAKEPULSESTRUC_H
#define MAKEPULSESTRUC_H

/* Include Files */
#include "rtwtypes.h"
#include "uavrt_detection_types.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void b_makepulsestruc(double A, double yw, double SNR, double t_0, double t_f,
                      const double t_next[2], double fp, double fstart,
                      double fend, b_struct_T *thepulse);

void makepulsestruc(double *thepulse_A, double *thepulse_P,
                    double *thepulse_SNR, double *thepulse_yw,
                    double *thepulse_t_0, double *thepulse_t_f,
                    double thepulse_t_next[2], double *thepulse_fp,
                    double *thepulse_fstart, double *thepulse_fend,
                    emxArray_char_T *thepulse_mode, bool *thepulse_det_dec,
                    bool *thepulse_con_dec);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for makepulsestruc.h
 *
 * [EOF]
 */
