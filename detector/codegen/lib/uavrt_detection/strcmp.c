/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: strcmp.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "strcmp.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"

/* Function Definitions */
/*
 * Arguments    : const char a_data[]
 *                const int a_size[2]
 * Return Type  : bool
 */
bool b_strcmp(const char a_data[], const int a_size[2])
{
  static const char b_cv[3] = {'r', 'u', 'n'};
  bool b_bool;
  b_bool = false;
  if (a_size[1] == 3) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 3) {
        if (a_data[kstr] != b_cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  return b_bool;
}

/*
 * Arguments    : const b_rtString a
 * Return Type  : bool
 */
bool c_strcmp(const b_rtString a)
{
  static const char b_cv[16] = {'f', 'r', 'e', 'q', 'A', 'l', 'l', 'N',
                                'e', 'v', 'e', 'r', 'L', 'o', 'c', 'k'};
  bool b_bool;
  b_bool = false;
  if (a.Value->size[1] == 16) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 16) {
        if (a.Value->data[kstr] != b_cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  return b_bool;
}

/*
 * Arguments    : const b_rtString a
 * Return Type  : bool
 */
bool d_strcmp(const b_rtString a)
{
  bool b_bool;
  b_bool = false;
  if (a.Value->size[1] == 18) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 18) {
        if (a.Value->data[kstr] != cv3[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  return b_bool;
}

/*
 * Arguments    : const char a_data[]
 *                const int a_size[2]
 * Return Type  : bool
 */
bool e_strcmp(const char a_data[], const int a_size[2])
{
  static const char b_cv[4] = {'i', 'd', 'l', 'e'};
  bool b_bool;
  b_bool = false;
  if (a_size[1] == 4) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 4) {
        if (a_data[kstr] != b_cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  return b_bool;
}

/*
 * Arguments    : const char a_data[]
 *                const int a_size[2]
 * Return Type  : bool
 */
bool f_strcmp(const char a_data[], const int a_size[2])
{
  bool b_bool;
  b_bool = false;
  if (a_size[1] == 12) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 12) {
        if (a_data[kstr] != cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  return b_bool;
}

/*
 * Arguments    : const char a_data[]
 *                const int a_size[2]
 * Return Type  : bool
 */
bool g_strcmp(const char a_data[], const int a_size[2])
{
  static const char b_cv[4] = {'k', 'i', 'l', 'l'};
  bool b_bool;
  b_bool = false;
  if (a_size[1] == 4) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 4) {
        if (a_data[kstr] != b_cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  return b_bool;
}

/*
 * Arguments    : const emxArray_char_T *a
 * Return Type  : bool
 */
bool h_strcmp(const emxArray_char_T *a)
{
  static const char b_cv[2] = {'t', 'p'};
  const char *a_data;
  bool b_bool;
  a_data = a->data;
  b_bool = false;
  if (a->size[1] == 2) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 2) {
        if (a_data[kstr] != b_cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  return b_bool;
}

/*
 * Arguments    : const emxArray_char_T *a
 * Return Type  : bool
 */
bool i_strcmp(const emxArray_char_T *a)
{
  static const char b_cv[3] = {'t', 'i', 'p'};
  const char *a_data;
  bool b_bool;
  a_data = a->data;
  b_bool = false;
  if (a->size[1] == 3) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 3) {
        if (a_data[kstr] != b_cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  return b_bool;
}

/*
 * Arguments    : const emxArray_char_T *a
 * Return Type  : bool
 */
bool j_strcmp(const emxArray_char_T *a)
{
  static const char b_cv[4] = {'t', 'i', 'p', 'u'};
  const char *a_data;
  bool b_bool;
  a_data = a->data;
  b_bool = false;
  if (a->size[1] == 4) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 4) {
        if (a_data[kstr] != b_cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  return b_bool;
}

/*
 * Arguments    : const emxArray_char_T *a
 * Return Type  : bool
 */
bool k_strcmp(const emxArray_char_T *a)
{
  static const char b_cv[4] = {'t', 'i', 'p', 'j'};
  const char *a_data;
  bool b_bool;
  a_data = a->data;
  b_bool = false;
  if (a->size[1] == 4) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 4) {
        if (a_data[kstr] != b_cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  return b_bool;
}

/*
 * Arguments    : const emxArray_char_T *a
 * Return Type  : bool
 */
bool l_strcmp(const emxArray_char_T *a)
{
  static const char b_cv[6] = {'o', 'p', 'M', 'o', 'd', 'e'};
  const char *a_data;
  bool b_bool;
  a_data = a->data;
  b_bool = false;
  if (a->size[1] == 6) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 6) {
        if (a_data[kstr] != b_cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  return b_bool;
}

/*
 * Arguments    : const emxArray_char_T *a
 * Return Type  : bool
 */
bool m_strcmp(const emxArray_char_T *a)
{
  static const char b_cv[10] = {'e', 'x', 'c', 'l', 'd',
                                'F', 'r', 'e', 'q', 's'};
  const char *a_data;
  bool b_bool;
  a_data = a->data;
  b_bool = false;
  if (a->size[1] == 10) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 10) {
        if (a_data[kstr] != b_cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  return b_bool;
}

/*
 * Arguments    : const emxArray_char_T *a
 * Return Type  : bool
 */
bool n_strcmp(const emxArray_char_T *a)
{
  static const char b_cv[14] = {'f', 'a', 'l', 's', 'e', 'A', 'l',
                                'a', 'r', 'm', 'P', 'r', 'o', 'b'};
  const char *a_data;
  bool b_bool;
  a_data = a->data;
  b_bool = false;
  if (a->size[1] == 14) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 14) {
        if (a_data[kstr] != b_cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  return b_bool;
}

/*
 * Arguments    : const emxArray_char_T *a
 * Return Type  : bool
 */
bool o_strcmp(const emxArray_char_T *a)
{
  static const char b_cv[14] = {'d', 'a', 't', 'a', 'R', 'e', 'c',
                                'o', 'r', 'd', 'P', 'a', 't', 'h'};
  const char *a_data;
  bool b_bool;
  a_data = a->data;
  b_bool = false;
  if (a->size[1] == 14) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 14) {
        if (a_data[kstr] != b_cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  return b_bool;
}

/*
 * Arguments    : const char a_data[]
 *                const int a_size[2]
 * Return Type  : bool
 */
bool p_strcmp(const char a_data[], const int a_size[2])
{
  static const char b_cv[6] = {'s', 'e', 'a', 'r', 'c', 'h'};
  bool b_bool;
  b_bool = false;
  if (a_size[1] == 6) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 6) {
        if (a_data[kstr] != b_cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  return b_bool;
}

/*
 * Arguments    : const char a_data[]
 *                const int a_size[2]
 * Return Type  : bool
 */
bool q_strcmp(const char a_data[], const int a_size[2])
{
  static const char b_cv[7] = {'c', 'o', 'n', 'f', 'i', 'r', 'm'};
  bool b_bool;
  b_bool = false;
  if (a_size[1] == 7) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 7) {
        if (a_data[kstr] != b_cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  return b_bool;
}

/*
 * Arguments    : const char a_data[]
 *                const int a_size[2]
 * Return Type  : bool
 */
bool r_strcmp(const char a_data[], const int a_size[2])
{
  static const char b_cv[5] = {'t', 'r', 'a', 'c', 'k'};
  bool b_bool;
  b_bool = false;
  if (a_size[1] == 5) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 5) {
        if (a_data[kstr] != b_cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  return b_bool;
}

/*
 * Arguments    : const char a_data[]
 *                const int a_size[2]
 * Return Type  : bool
 */
bool s_strcmp(const char a_data[], const int a_size[2])
{
  static const char b_cv[5] = {'n', 'a', 'i', 'v', 'e'};
  bool b_bool;
  b_bool = false;
  if (a_size[1] == 5) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 5) {
        if (a_data[kstr] != b_cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  return b_bool;
}

/*
 * Arguments    : const char a_data[]
 *                const int a_size[2]
 * Return Type  : bool
 */
bool t_strcmp(const char a_data[], const int a_size[2])
{
  static const char b_cv[8] = {'i', 'n', 'f', 'o', 'r', 'm', 'e', 'd'};
  bool b_bool;
  b_bool = false;
  if (a_size[1] == 8) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 8) {
        if (a_data[kstr] != b_cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  return b_bool;
}

/*
 * File trailer for strcmp.c
 *
 * [EOF]
 */
