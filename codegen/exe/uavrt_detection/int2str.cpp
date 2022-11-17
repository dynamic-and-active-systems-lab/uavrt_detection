//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// int2str.cpp
//
// Code generation for function 'int2str'
//

// Include files
#include "int2str.h"
#include "rt_nonfinite.h"
#include <algorithm>
#include <cmath>
#include <stdio.h>
#include <string.h>

// Function Definitions
namespace coder {
void int2str(double xin, char s_data[], int s_size[2])
{
  double x;
  char st[311];
  x = std::round(xin);
  if (x == 0.0) {
    s_size[0] = 1;
    s_size[1] = 1;
    s_data[0] = '0';
  } else if (std::isinf(x)) {
    s_size[0] = 1;
    s_size[1] = 3;
    s_data[0] = 'I';
    s_data[1] = 'n';
    s_data[2] = 'f';
  } else if (std::isnan(x)) {
    s_size[0] = 1;
    s_size[1] = 3;
    s_data[0] = 'N';
    s_data[1] = 'a';
    s_data[2] = 'N';
  } else {
    int resCount;
    resCount = sprintf(&st[0], "%.0f", x);
    s_size[0] = 1;
    s_size[1] = resCount;
    if (resCount - 1 >= 0) {
      std::copy(&st[0], &st[resCount], &s_data[0]);
    }
  }
}

} // namespace coder

// End of code generation (int2str.cpp)
