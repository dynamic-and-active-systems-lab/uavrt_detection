/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: string1.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "string1.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"

/* Function Definitions */
/*
 * Arguments    : const emxArray_char_T *obj2_Value
 * Return Type  : bool
 */
bool b_string_eq(const emxArray_char_T *obj2_Value)
{
  static const char b_cv[17] = {'f', 'r', 'e', 'q', 'K', 'n', 'o', 'w', 'n',
                                'H', 'a', 'r', 'd', 'L', 'o', 'c', 'k'};
  const char *obj2_Value_data;
  bool equal;
  obj2_Value_data = obj2_Value->data;
  equal = false;
  if (obj2_Value->size[1] == 17) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 17) {
        if (b_cv[kstr] != obj2_Value_data[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        equal = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  return equal;
}

/*
 * Arguments    : const emxArray_char_T *obj2_Value
 * Return Type  : bool
 */
bool c_string_eq(const emxArray_char_T *obj2_Value)
{
  const char *obj2_Value_data;
  bool equal;
  obj2_Value_data = obj2_Value->data;
  equal = false;
  if (obj2_Value->size[1] == 18) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 18) {
        if (cv3[kstr] != obj2_Value_data[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        equal = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  return equal;
}

/*
 * Arguments    : const emxArray_char_T *obj2_Value
 * Return Type  : bool
 */
bool d_string_eq(const emxArray_char_T *obj2_Value)
{
  static const char b_cv[13] = {'f', 'r', 'e', 'q', 'A', 'l', 'l',
                                'N', 'o', 'L', 'o', 'c', 'k'};
  const char *obj2_Value_data;
  bool equal;
  obj2_Value_data = obj2_Value->data;
  equal = false;
  if (obj2_Value->size[1] == 13) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 13) {
        if (b_cv[kstr] != obj2_Value_data[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        equal = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  return equal;
}

/*
 * Arguments    : const emxArray_char_T *obj2_Value
 * Return Type  : bool
 */
bool string_eq(const emxArray_char_T *obj2_Value)
{
  const char *obj2_Value_data;
  bool equal;
  obj2_Value_data = obj2_Value->data;
  equal = false;
  if (obj2_Value->size[1] == 18) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 18) {
        if (cv1[kstr] != obj2_Value_data[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        equal = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  return equal;
}

/*
 * File trailer for string1.c
 *
 * [EOF]
 */
