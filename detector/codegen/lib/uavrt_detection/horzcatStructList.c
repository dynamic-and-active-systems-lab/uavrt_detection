/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: horzcatStructList.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "horzcatStructList.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"

/* Function Definitions */
/*
 * Arguments    : const emxArray_struct_T *structure
 *                emxArray_real_T *result
 * Return Type  : void
 */
void b_horzcatStructList(const emxArray_struct_T *structure,
                         emxArray_real_T *result)
{
  const b_struct_T *structure_data;
  double *result_data;
  int i;
  int n;
  structure_data = structure->data;
  n = structure->size[1];
  i = result->size[0] * result->size[1];
  result->size[0] = 1;
  if (structure->size[1] == 0) {
    result->size[1] = 0;
  } else {
    result->size[1] = structure->size[1];
  }
  emxEnsureCapacity_real_T(result, i);
  result_data = result->data;
  for (i = 0; i < n; i++) {
    result_data[i] = structure_data[i].fp;
  }
}

/*
 * Arguments    : const emxArray_struct_T *structure
 *                emxArray_boolean_T *result
 * Return Type  : void
 */
void c_horzcatStructList(const emxArray_struct_T *structure,
                         emxArray_boolean_T *result)
{
  const b_struct_T *structure_data;
  int i;
  int n;
  bool *result_data;
  structure_data = structure->data;
  n = structure->size[1];
  i = result->size[0] * result->size[1];
  result->size[0] = 1;
  if (structure->size[1] == 0) {
    result->size[1] = 0;
  } else {
    result->size[1] = structure->size[1];
  }
  emxEnsureCapacity_boolean_T(result, i);
  result_data = result->data;
  for (i = 0; i < n; i++) {
    result_data[i] = structure_data[i].con_dec;
  }
}

/*
 * Arguments    : const emxArray_struct_T *structure
 *                emxArray_real_T *result
 * Return Type  : void
 */
void horzcatStructList(const emxArray_struct_T *structure,
                       emxArray_real_T *result)
{
  const b_struct_T *structure_data;
  double *result_data;
  int i;
  int n;
  structure_data = structure->data;
  n = structure->size[0];
  i = result->size[0] * result->size[1];
  result->size[0] = 1;
  if (structure->size[0] == 0) {
    result->size[1] = 0;
  } else {
    result->size[1] = structure->size[0];
  }
  emxEnsureCapacity_real_T(result, i);
  result_data = result->data;
  for (i = 0; i < n; i++) {
    result_data[i] = structure_data[i].t_0;
  }
}

/*
 * File trailer for horzcatStructList.c
 *
 * [EOF]
 */
