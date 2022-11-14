/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: str2double.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "str2double.h"
#include "rt_nonfinite.h"
#include "str2double1.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include <stdio.h>

/* Function Definitions */
/*
 * Arguments    : const emxArray_char_T *s
 * Return Type  : creal_T
 */
creal_T str2double(const emxArray_char_T *s)
{
  emxArray_char_T *s1;
  creal_T x;
  double scanned1;
  double scanned2;
  int i;
  int idx;
  int k;
  const char *s_data;
  char *s1_data;
  bool a__1;
  bool foundsign;
  bool isfinite1;
  bool isfinite2;
  bool isimag1;
  bool success;
  s_data = s->data;
  x.re = rtNaN;
  x.im = 0.0;
  if (s->size[1] >= 1) {
    int ntoread;
    bool exitg1;
    emxInit_char_T(&s1);
    ntoread = 0;
    k = 1;
    exitg1 = false;
    while ((!exitg1) && (k <= s->size[1])) {
      char c;
      c = s_data[k - 1];
      if (bv[(unsigned char)c & 127] || (c == '\x00')) {
        k++;
      } else {
        exitg1 = true;
      }
    }
    i = s1->size[0] * s1->size[1];
    s1->size[0] = 1;
    s1->size[1] = s->size[1] + 2;
    emxEnsureCapacity_char_T(s1, i);
    s1_data = s1->data;
    idx = s->size[1] + 2;
    for (i = 0; i < idx; i++) {
      s1_data[i] = '\x00';
    }
    idx = 1;
    readfloat(s1, &idx, s, &k, s->size[1], &isimag1, &isfinite1, &scanned1,
              &a__1, &success);
    s1_data = s1->data;
    if (isfinite1) {
      ntoread = 1;
    }
    if (success && (k <= s->size[1])) {
      s1_data[idx - 1] = ' ';
      idx++;
      readfloat(s1, &idx, s, &k, s->size[1], &a__1, &isfinite2, &scanned2,
                &foundsign, &success);
      s1_data = s1->data;
      if (isfinite2) {
        ntoread++;
      }
      if (success && (k > s->size[1]) && ((bool)(isimag1 ^ a__1)) &&
          foundsign) {
        success = true;
      } else {
        success = false;
      }
    } else {
      scanned2 = 0.0;
    }
    if (success) {
      s1_data[idx - 1] = '\x00';
      if (ntoread == 2) {
        idx = sscanf(&s1_data[0], "%lf %lf", &scanned1, &scanned2);
        if (idx != 2) {
          scanned1 = rtNaN;
          scanned2 = rtNaN;
        }
      } else if (ntoread == 1) {
        double b_scanned1;
        idx = sscanf(&s1_data[0], "%lf", &b_scanned1);
        if (idx != 1) {
          b_scanned1 = rtNaN;
        }
        if (isfinite1) {
          scanned1 = b_scanned1;
        } else {
          scanned2 = b_scanned1;
        }
      }
      if (isimag1) {
        x.re = scanned2;
        x.im = scanned1;
      } else {
        x.re = scanned1;
        x.im = scanned2;
      }
    }
    emxFree_char_T(&s1);
  }
  return x;
}

/*
 * File trailer for str2double.c
 *
 * [EOF]
 */
