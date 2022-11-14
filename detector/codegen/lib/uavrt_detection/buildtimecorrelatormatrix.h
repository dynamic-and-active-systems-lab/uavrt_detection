/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: buildtimecorrelatormatrix.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

#ifndef BUILDTIMECORRELATORMATRIX_H
#define BUILDTIMECORRELATORMATRIX_H

/* Include Files */
#include "rtwtypes.h"
#include "uavrt_detection_types.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void buildtimecorrelatormatrix(double pri, double priUncert, double priJtr,
                               double reps, d_sparse *Wq);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for buildtimecorrelatormatrix.h
 *
 * [EOF]
 */
