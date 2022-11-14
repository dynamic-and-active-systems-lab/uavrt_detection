/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: parenAssign2D.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

#ifndef PARENASSIGN2D_H
#define PARENASSIGN2D_H

/* Include Files */
#include "rtwtypes.h"
#include "uavrt_detection_types.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void b_realloc(c_sparse *this, int numAllocRequested, int ub1, int lb2,
               int ub2);

void sparse_parenAssign2D(c_sparse *this, bool rhs, double r, double c);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for parenAssign2D.h
 *
 * [EOF]
 */
