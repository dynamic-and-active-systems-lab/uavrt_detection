/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: repmat.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "repmat.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"

/* Function Definitions */
/*
 * Arguments    : const emxArray_real_T *a
 *                double varargin_1
 *                emxArray_real_T *b
 * Return Type  : void
 */
void b_repmat(const emxArray_real_T *a, double varargin_1, emxArray_real_T *b)
{
  const double *a_data;
  double *b_data;
  int i;
  int itilerow;
  int jcol;
  int ncols;
  a_data = a->data;
  i = (int)varargin_1;
  ncols = b->size[0] * b->size[1];
  b->size[0] = (int)varargin_1;
  b->size[1] = a->size[1];
  emxEnsureCapacity_real_T(b, ncols);
  b_data = b->data;
  ncols = a->size[1];
  for (jcol = 0; jcol < ncols; jcol++) {
    int ibmat;
    ibmat = jcol * (int)varargin_1;
    for (itilerow = 0; itilerow < i; itilerow++) {
      b_data[ibmat + itilerow] = a_data[jcol];
    }
  }
}

/*
 * Arguments    : const b_struct_T *a
 *                double varargin_1
 *                double varargin_2
 *                emxArray_struct_T *b
 * Return Type  : void
 */
void c_repmat(const b_struct_T *a, double varargin_1, double varargin_2,
              emxArray_struct_T *b)
{
  b_struct_T *b_data;
  int i;
  int loop_ub;
  i = b->size[0] * b->size[1];
  b->size[0] = (int)varargin_1;
  b->size[1] = (int)varargin_2;
  emxEnsureCapacity_struct_T(b, i);
  b_data = b->data;
  loop_ub = (int)varargin_1 * (int)varargin_2;
  for (i = 0; i < loop_ub; i++) {
    emxCopyStruct_struct_T(&b_data[i], a);
  }
}

/*
 * Arguments    : const emxArray_real_T *a
 *                double varargin_2
 *                emxArray_real_T *b
 * Return Type  : void
 */
void repmat(const emxArray_real_T *a, double varargin_2, emxArray_real_T *b)
{
  const double *a_data;
  double *b_data;
  int i;
  int jtilecol;
  int k;
  int nrows;
  a_data = a->data;
  nrows = b->size[0] * b->size[1];
  b->size[0] = a->size[0];
  i = (int)varargin_2;
  b->size[1] = (int)varargin_2;
  emxEnsureCapacity_real_T(b, nrows);
  b_data = b->data;
  nrows = a->size[0];
  for (jtilecol = 0; jtilecol < i; jtilecol++) {
    int ibtile;
    ibtile = jtilecol * nrows;
    for (k = 0; k < nrows; k++) {
      b_data[ibtile + k] = a_data[k];
    }
  }
}

/*
 * File trailer for repmat.c
 *
 * [EOF]
 */
