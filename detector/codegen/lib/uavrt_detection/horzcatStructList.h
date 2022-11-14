/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: horzcatStructList.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

#ifndef HORZCATSTRUCTLIST_H
#define HORZCATSTRUCTLIST_H

/* Include Files */
#include "rtwtypes.h"
#include "uavrt_detection_types.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void b_horzcatStructList(const emxArray_struct_T *structure,
                         emxArray_real_T *result);

void c_horzcatStructList(const emxArray_struct_T *structure,
                         emxArray_boolean_T *result);

void horzcatStructList(const emxArray_struct_T *structure,
                       emxArray_real_T *result);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for horzcatStructList.h
 *
 * [EOF]
 */
