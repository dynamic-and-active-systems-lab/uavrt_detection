/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: psdfreqvec.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "psdfreqvec.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include "rt_nonfinite.h"
#include <float.h>
#include <math.h>

/* Function Declarations */
static double rt_remd_snf(double u0, double u1);

/* Function Definitions */
/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_remd_snf(double u0, double u1)
{
  double y;
  if (rtIsNaN(u0) || rtIsNaN(u1) || rtIsInf(u0)) {
    y = rtNaN;
  } else if (rtIsInf(u1)) {
    y = u0;
  } else if ((u1 != 0.0) && (u1 != trunc(u1))) {
    double q;
    q = fabs(u0 / u1);
    if (!(fabs(q - floor(q + 0.5)) > DBL_EPSILON * q)) {
      y = 0.0 * u0;
    } else {
      y = fmod(u0, u1);
    }
  } else {
    y = fmod(u0, u1);
  }
  return y;
}

/*
 * Arguments    : double varargin_2
 *                double varargin_4
 *                emxArray_real_T *w
 * Return Type  : void
 */
void psdfreqvec(double varargin_2, double varargin_4, emxArray_real_T *w)
{
  emxArray_real_T *w1;
  double Fs1;
  double Nyq;
  double freq_res;
  double half_res;
  double *w1_data;
  double *w_data;
  int i;
  int loop_ub;
  if (rtIsNaN(varargin_4)) {
    Fs1 = 6.2831853071795862;
  } else {
    Fs1 = varargin_4;
  }
  freq_res = Fs1 / varargin_2;
  emxInit_real_T(&w1, 2);
  if (rtIsNaN(varargin_2 - 1.0)) {
    i = w1->size[0] * w1->size[1];
    w1->size[0] = 1;
    w1->size[1] = 1;
    emxEnsureCapacity_real_T(w1, i);
    w1_data = w1->data;
    w1_data[0] = rtNaN;
  } else if (varargin_2 - 1.0 < 0.0) {
    w1->size[1] = 0;
  } else {
    i = w1->size[0] * w1->size[1];
    w1->size[0] = 1;
    w1->size[1] = (int)(varargin_2 - 1.0) + 1;
    emxEnsureCapacity_real_T(w1, i);
    w1_data = w1->data;
    loop_ub = (int)(varargin_2 - 1.0);
    for (i = 0; i <= loop_ub; i++) {
      w1_data[i] = i;
    }
  }
  i = w1->size[0] * w1->size[1];
  w1->size[0] = 1;
  emxEnsureCapacity_real_T(w1, i);
  w1_data = w1->data;
  loop_ub = w1->size[1] - 1;
  for (i = 0; i <= loop_ub; i++) {
    w1_data[i] *= freq_res;
  }
  Nyq = Fs1 / 2.0;
  half_res = freq_res / 2.0;
  if (rt_remd_snf(varargin_2, 2.0) != 0.0) {
    double halfNPTS;
    halfNPTS = (varargin_2 + 1.0) / 2.0;
    w1_data[(int)halfNPTS - 1] = Nyq - half_res;
    w1_data[(int)(unsigned int)halfNPTS] = Nyq + half_res;
  } else {
    w1_data[(int)(varargin_2 / 2.0 + 1.0) - 1] = Nyq;
  }
  w1_data[(int)varargin_2 - 1] = Fs1 - freq_res;
  i = w->size[0];
  w->size[0] = w1->size[1];
  emxEnsureCapacity_real_T(w, i);
  w_data = w->data;
  loop_ub = w1->size[1];
  for (i = 0; i < loop_ub; i++) {
    w_data[i] = w1_data[i];
  }
  emxFree_real_T(&w1);
}

/*
 * File trailer for psdfreqvec.c
 *
 * [EOF]
 */
