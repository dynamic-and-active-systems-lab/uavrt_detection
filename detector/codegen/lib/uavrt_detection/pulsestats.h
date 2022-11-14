/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: pulsestats.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

#ifndef PULSESTATS_H
#define PULSESTATS_H

/* Include Files */
#include "rtwtypes.h"
#include "uavrt_detection_types.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
pulsestats *b_pulsestats_pulsestats(
    pulsestats *obj, double tp, double tip, double tipu, double tipj, double fp,
    double fstart, double fend, const double tmplt[2], char mode,
    const emxArray_struct_T *pl, const emxArray_struct_T *clst,
    const emxArray_boolean_T *cmsk, const emxArray_real_T *cpki);

void b_pulsestats_updateposteriori(pulsestats *obj, const pulsestats *ps_pre,
                                   const emxArray_struct_T *pulselist);

pulsestats *c_pulsestats_pulsestats(pulsestats *obj, double tp, double tip,
                                    double tipu, double tipj, double fp,
                                    const b_struct_T *pl,
                                    const b_struct_T *clst);

pulsestats *d_pulsestats_pulsestats(
    pulsestats *obj, double tp, double tip, double tipu, double tipj, double fp,
    double fstart, double fend, const double tmplt[2], const char mode_data[],
    const emxArray_struct_T *pl, const emxArray_struct_T *clst,
    const emxArray_boolean_T *cmsk, const emxArray_real_T *cpki);

pulsestats *pulsestats_pulsestats(pulsestats *obj, double tp, double tip,
                                  double tipu, double tipj,
                                  const b_struct_T *pl, const b_struct_T *clst);

void pulsestats_updateposteriori(pulsestats *obj,
                                 const emxArray_struct_T *pulselist);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for pulsestats.h
 *
 * [EOF]
 */
