/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: randn.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "randn.h"
#include "eml_rand_mt19937ar.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"

/* Function Definitions */
/*
 * Arguments    : creal_T r[1000]
 * Return Type  : void
 */
void b_complexLike(creal_T r[1000])
{
  double im;
  double re;
  int k;
  for (k = 0; k < 1000; k++) {
    re = eml_rand_mt19937ar(state);
    im = eml_rand_mt19937ar(state);
    r[k].re = re;
    r[k].im = im;
  }
  for (k = 0; k < 1000; k++) {
    double ai;
    im = r[k].re;
    ai = r[k].im;
    if (ai == 0.0) {
      re = im / 1.4142135623730951;
      im = 0.0;
    } else if (im == 0.0) {
      re = 0.0;
      im = ai / 1.4142135623730951;
    } else {
      re = im / 1.4142135623730951;
      im = ai / 1.4142135623730951;
    }
    r[k].re = re;
    r[k].im = im;
  }
}

/*
 * Arguments    : double varargin_1
 *                emxArray_real_T *r
 * Return Type  : void
 */
void b_randn(double varargin_1, emxArray_real_T *r)
{
  double *r_data;
  int i;
  int k;
  i = r->size[0] * r->size[1];
  r->size[0] = (int)varargin_1;
  r->size[1] = 100;
  emxEnsureCapacity_real_T(r, i);
  r_data = r->data;
  i = (int)varargin_1 * 100;
  for (k = 0; k < i; k++) {
    r_data[k] = eml_rand_mt19937ar(state);
  }
}

/*
 * Arguments    : double varargin_1
 *                emxArray_creal_T *r
 * Return Type  : void
 */
void complexLike(double varargin_1, emxArray_creal_T *r)
{
  creal_T *r_data;
  double im;
  double re;
  int i;
  int k;
  i = r->size[0] * r->size[1];
  r->size[0] = (int)varargin_1;
  r->size[1] = 100;
  emxEnsureCapacity_creal_T(r, i);
  r_data = r->data;
  i = (int)varargin_1 * 100;
  for (k = 0; k < i; k++) {
    re = eml_rand_mt19937ar(state);
    im = eml_rand_mt19937ar(state);
    r_data[k].re = re;
    r_data[k].im = im;
  }
  k = r->size[0] * 100;
  i = r->size[0] * r->size[1];
  r->size[1] = 100;
  emxEnsureCapacity_creal_T(r, i);
  r_data = r->data;
  for (i = 0; i < k; i++) {
    double ai;
    im = r_data[i].re;
    ai = r_data[i].im;
    if (ai == 0.0) {
      re = im / 1.4142135623730951;
      im = 0.0;
    } else if (im == 0.0) {
      re = 0.0;
      im = ai / 1.4142135623730951;
    } else {
      re = im / 1.4142135623730951;
      im = ai / 1.4142135623730951;
    }
    r_data[i].re = re;
    r_data[i].im = im;
  }
}

/*
 * Arguments    : double r[1000]
 * Return Type  : void
 */
void randn(double r[1000])
{
  int k;
  for (k = 0; k < 1000; k++) {
    r[k] = eml_rand_mt19937ar(state);
  }
}

/*
 * File trailer for randn.c
 *
 * [EOF]
 */
