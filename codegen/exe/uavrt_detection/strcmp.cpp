//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: strcmp.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 17:51:34
//

// Include Files
#include "strcmp.h"
#include "rt_nonfinite.h"
#include "string1.h"
#include "uavrt_detection_data.h"
#include "coder_array.h"
#include <string.h>

// Function Definitions
//
// Arguments    : const ::coder::array<char, 2U> &a
// Return Type  : boolean_T
//
namespace coder {
namespace internal {
boolean_T b_strcmp(const ::coder::array<char, 2U> &a)
{
  static const char b_cv[3]{'a', 'l', 'l'};
  boolean_T b_bool;
  b_bool = false;
  if (a.size(1) == 3) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 3) {
        if (a[kstr] != b_cv[kstr]) {
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

//
// Arguments    : const rtString *a
// Return Type  : boolean_T
//
boolean_T b_strcmp(const rtString *a)
{
  static const char b_cv[16]{'f', 'r', 'e', 'q', 'A', 'l', 'l', 'N',
                             'e', 'v', 'e', 'r', 'L', 'o', 'c', 'k'};
  boolean_T b_bool;
  b_bool = false;
  if (a->Value.size(1) == 16) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 16) {
        if (a->Value[kstr] != b_cv[kstr]) {
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

//
// Arguments    : const char a_data[]
//                const int a_size[2]
// Return Type  : boolean_T
//
boolean_T b_strcmp(const char a_data[], const int a_size[2])
{
  static const char b_cv[6]{'s', 'e', 'a', 'r', 'c', 'h'};
  boolean_T b_bool;
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

//
// Arguments    : const ::coder::array<char, 2U> &a
// Return Type  : boolean_T
//
boolean_T c_strcmp(const ::coder::array<char, 2U> &a)
{
  static const char b_cv[20]{'c', 'h', 'a', 'n', 'n', 'e', 'l', 'C', 'e', 'n',
                             't', 'e', 'r', 'F', 'r', 'e', 'q', 'M', 'H', 'z'};
  boolean_T b_bool;
  b_bool = false;
  if (a.size(1) == 20) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 20) {
        if (a[kstr] != b_cv[kstr]) {
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

//
// Arguments    : const rtString *a
// Return Type  : boolean_T
//
boolean_T c_strcmp(const rtString *a)
{
  boolean_T b_bool;
  b_bool = false;
  if (a->Value.size(1) == 18) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 18) {
        if (a->Value[kstr] != cv4[kstr]) {
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

//
// Arguments    : const char a_data[]
//                const int a_size[2]
// Return Type  : boolean_T
//
boolean_T c_strcmp(const char a_data[], const int a_size[2])
{
  static const char b_cv[7]{'c', 'o', 'n', 'f', 'i', 'r', 'm'};
  boolean_T b_bool;
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

//
// Arguments    : const ::coder::array<char, 2U> &a
// Return Type  : boolean_T
//
boolean_T d_strcmp(const ::coder::array<char, 2U> &a)
{
  static const char b_cv[6]{'i', 'p', 'D', 'a', 't', 'a'};
  boolean_T b_bool;
  b_bool = false;
  if (a.size(1) == 6) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 6) {
        if (a[kstr] != b_cv[kstr]) {
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

//
// Arguments    : const char a_data[]
//                const int a_size[2]
// Return Type  : boolean_T
//
boolean_T d_strcmp(const char a_data[], const int a_size[2])
{
  static const char b_cv[5]{'t', 'r', 'a', 'c', 'k'};
  boolean_T b_bool;
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

//
// Arguments    : const ::coder::array<char, 2U> &a
// Return Type  : boolean_T
//
boolean_T e_strcmp(const ::coder::array<char, 2U> &a)
{
  static const char b_cv[8]{'p', 'o', 'r', 't', 'D', 'a', 't', 'a'};
  boolean_T b_bool;
  b_bool = false;
  if (a.size(1) == 8) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 8) {
        if (a[kstr] != b_cv[kstr]) {
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

//
// Arguments    : const char a_data[]
//                const int a_size[2]
// Return Type  : boolean_T
//
boolean_T e_strcmp(const char a_data[], const int a_size[2])
{
  static const char b_cv[5]{'n', 'a', 'i', 'v', 'e'};
  boolean_T b_bool;
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

//
// Arguments    : const ::coder::array<char, 2U> &a
// Return Type  : boolean_T
//
boolean_T f_strcmp(const ::coder::array<char, 2U> &a)
{
  static const char b_cv[2]{'F', 's'};
  boolean_T b_bool;
  b_bool = false;
  if (a.size(1) == 2) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 2) {
        if (a[kstr] != b_cv[kstr]) {
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

//
// Arguments    : const char a_data[]
//                const int a_size[2]
// Return Type  : boolean_T
//
boolean_T f_strcmp(const char a_data[], const int a_size[2])
{
  static const char b_cv[8]{'i', 'n', 'f', 'o', 'r', 'm', 'e', 'd'};
  boolean_T b_bool;
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

//
// Arguments    : const ::coder::array<char, 2U> &a
// Return Type  : boolean_T
//
boolean_T g_strcmp(const ::coder::array<char, 2U> &a)
{
  static const char b_cv[10]{'t', 'a', 'g', 'F', 'r', 'e', 'q', 'M', 'H', 'z'};
  boolean_T b_bool;
  b_bool = false;
  if (a.size(1) == 10) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 10) {
        if (a[kstr] != b_cv[kstr]) {
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

//
// Arguments    : const ::coder::array<char, 2U> &a
// Return Type  : boolean_T
//
boolean_T h_strcmp(const ::coder::array<char, 2U> &a)
{
  static const char b_cv[2]{'t', 'p'};
  boolean_T b_bool;
  b_bool = false;
  if (a.size(1) == 2) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 2) {
        if (a[kstr] != b_cv[kstr]) {
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

//
// Arguments    : const ::coder::array<char, 2U> &a
// Return Type  : boolean_T
//
boolean_T i_strcmp(const ::coder::array<char, 2U> &a)
{
  static const char b_cv[3]{'t', 'i', 'p'};
  boolean_T b_bool;
  b_bool = false;
  if (a.size(1) == 3) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 3) {
        if (a[kstr] != b_cv[kstr]) {
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

//
// Arguments    : const ::coder::array<char, 2U> &a
// Return Type  : boolean_T
//
boolean_T j_strcmp(const ::coder::array<char, 2U> &a)
{
  static const char b_cv[4]{'t', 'i', 'p', 'u'};
  boolean_T b_bool;
  b_bool = false;
  if (a.size(1) == 4) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 4) {
        if (a[kstr] != b_cv[kstr]) {
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

//
// Arguments    : const ::coder::array<char, 2U> &a
// Return Type  : boolean_T
//
boolean_T k_strcmp(const ::coder::array<char, 2U> &a)
{
  static const char b_cv[4]{'t', 'i', 'p', 'j'};
  boolean_T b_bool;
  b_bool = false;
  if (a.size(1) == 4) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 4) {
        if (a[kstr] != b_cv[kstr]) {
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

//
// Arguments    : const ::coder::array<char, 2U> &a
// Return Type  : boolean_T
//
boolean_T l_strcmp(const ::coder::array<char, 2U> &a)
{
  static const char b_cv[6]{'o', 'p', 'M', 'o', 'd', 'e'};
  boolean_T b_bool;
  b_bool = false;
  if (a.size(1) == 6) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 6) {
        if (a[kstr] != b_cv[kstr]) {
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

//
// Arguments    : const ::coder::array<char, 2U> &a
// Return Type  : boolean_T
//
boolean_T m_strcmp(const ::coder::array<char, 2U> &a)
{
  static const char b_cv[10]{'e', 'x', 'c', 'l', 'd', 'F', 'r', 'e', 'q', 's'};
  boolean_T b_bool;
  b_bool = false;
  if (a.size(1) == 10) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 10) {
        if (a[kstr] != b_cv[kstr]) {
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

//
// Arguments    : const ::coder::array<char, 2U> &a
// Return Type  : boolean_T
//
boolean_T n_strcmp(const ::coder::array<char, 2U> &a)
{
  static const char b_cv[14]{'f', 'a', 'l', 's', 'e', 'A', 'l',
                             'a', 'r', 'm', 'P', 'r', 'o', 'b'};
  boolean_T b_bool;
  b_bool = false;
  if (a.size(1) == 14) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 14) {
        if (a[kstr] != b_cv[kstr]) {
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

//
// Arguments    : const ::coder::array<char, 2U> &a
// Return Type  : boolean_T
//
boolean_T o_strcmp(const ::coder::array<char, 2U> &a)
{
  static const char b_cv[14]{'d', 'a', 't', 'a', 'R', 'e', 'c',
                             'o', 'r', 'd', 'P', 'a', 't', 'h'};
  boolean_T b_bool;
  b_bool = false;
  if (a.size(1) == 14) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 14) {
        if (a[kstr] != b_cv[kstr]) {
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

} // namespace internal
} // namespace coder

//
// File trailer for strcmp.cpp
//
// [EOF]
//
