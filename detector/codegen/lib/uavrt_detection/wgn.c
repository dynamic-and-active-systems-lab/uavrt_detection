/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: wgn.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "wgn.h"
#include "randn.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include <math.h>

/* Function Definitions */
/*
 * Arguments    : creal_T y[1000]
 * Return Type  : void
 */
void wgn(creal_T y[1000])
{
  static const char b_cv1[7] = {'c', 'o', 'm', 'p', 'l', 'e', 'x'};
  static const char b[6] = {'l', 'i', 'n', 'e', 'a', 'r'};
  static const char b_cv[6] = {'l', 'i', 'n', 'e', 'a', 'r'};
  emxArray_char_T *switch_expression;
  emxArray_char_T *x;
  double noisePower;
  int i;
  char a_data[7];
  char *switch_expression_data;
  char *x_data;
  bool b_bool;
  emxInit_char_T(&x);
  i = x->size[0] * x->size[1];
  x->size[0] = 1;
  x->size[1] = 6;
  emxEnsureCapacity_char_T(x, i);
  x_data = x->data;
  for (i = 0; i < 6; i++) {
    x_data[i] = b[i];
  }
  emxInit_char_T(&switch_expression);
  i = switch_expression->size[0] * switch_expression->size[1];
  switch_expression->size[0] = 1;
  switch_expression->size[1] = 6;
  emxEnsureCapacity_char_T(switch_expression, i);
  switch_expression_data = switch_expression->data;
  for (i = 0; i < 6; i++) {
    switch_expression_data[i] = cv2[(int)x_data[i]];
  }
  emxFree_char_T(&x);
  b_bool = false;
  i = 0;
  int exitg1;
  do {
    exitg1 = 0;
    if (i < 6) {
      if (switch_expression_data[i] != b_cv[i]) {
        exitg1 = 1;
      } else {
        i++;
      }
    } else {
      b_bool = true;
      exitg1 = 1;
    }
  } while (exitg1 == 0);
  emxFree_char_T(&switch_expression);
  if (b_bool) {
    noisePower = 1.0;
  } else {
    noisePower = 0.0012589254117941675;
  }
  for (i = 0; i < 7; i++) {
    a_data[i] = b_cv1[i];
  }
  if (cv2[(int)a_data[0]] == 'r') {
    double b_b[1000];
    noisePower = sqrt(noisePower);
    randn(b_b);
    for (i = 0; i < 1000; i++) {
      y[i].re = noisePower * b_b[i];
      y[i].im = 0.0;
    }
  } else {
    noisePower = sqrt(noisePower);
    b_complexLike(y);
    for (i = 0; i < 1000; i++) {
      y[i].re *= noisePower;
      y[i].im *= noisePower;
    }
  }
}

/*
 * File trailer for wgn.c
 *
 * [EOF]
 */
