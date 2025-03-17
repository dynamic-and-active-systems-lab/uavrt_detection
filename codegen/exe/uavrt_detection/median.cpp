//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: median.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "median.h"
#include "eml_int_forloop_overflow_check.h"
#include "quickselect.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const array<double, 2U> &x
//                array<double, 1U> &y
// Return Type  : void
//
namespace coder {
void median(const array<double, 2U> &x, array<double, 1U> &y)
{
  array<double, 1U> xv;
  int a__6;
  int ilast;
  int k;
  if ((x.size(0) == 0) || (x.size(1) == 0)) {
    int loop_ub;
    loop_ub = x.size(0);
    y.set_size(x.size(0));
    for (k = 0; k < loop_ub; k++) {
      y[k] = rtNaN;
    }
  } else {
    int loop_ub;
    int nx_tmp;
    boolean_T b_overflow;
    boolean_T overflow;
    loop_ub = x.size(0);
    y.set_size(x.size(0));
    for (k = 0; k < loop_ub; k++) {
      y[k] = 0.0;
    }
    nx_tmp = x.size(1);
    if (x.size(0) > 2147483646) {
      check_forloop_overflow_error();
    }
    overflow = (x.size(1) > 2147483646);
    b_overflow = (x.size(1) > 2147483646);
    for (int j{0}; j < loop_ub; j++) {
      xv.set_size(nx_tmp);
      for (k = 0; k < nx_tmp; k++) {
        xv[k] = 0.0;
      }
      if (overflow) {
        check_forloop_overflow_error();
      }
      for (k = 0; k < nx_tmp; k++) {
        xv[k] = x[j + k * loop_ub];
      }
      if (b_overflow) {
        check_forloop_overflow_error();
      }
      k = 0;
      int exitg1;
      do {
        exitg1 = 0;
        if (k <= nx_tmp - 1) {
          if (std::isnan(xv[k])) {
            y[j] = rtNaN;
            exitg1 = 1;
          } else {
            k++;
          }
        } else {
          if (nx_tmp <= 4) {
            if (nx_tmp == 1) {
              y[j] = xv[0];
            } else if (nx_tmp == 2) {
              if (((xv[0] < 0.0) != (xv[1] < 0.0)) || std::isinf(xv[0])) {
                y[j] = (xv[0] + xv[1]) / 2.0;
              } else {
                y[j] = xv[0] + (xv[1] - xv[0]) / 2.0;
              }
            } else if (nx_tmp == 3) {
              if (xv[0] < xv[1]) {
                if (xv[1] < xv[2]) {
                  a__6 = 1;
                } else if (xv[0] < xv[2]) {
                  a__6 = 2;
                } else {
                  a__6 = 0;
                }
              } else if (xv[0] < xv[2]) {
                a__6 = 0;
              } else if (xv[1] < xv[2]) {
                a__6 = 2;
              } else {
                a__6 = 1;
              }
              y[j] = xv[a__6];
            } else {
              if (xv[0] < xv[1]) {
                if (xv[1] < xv[2]) {
                  k = 0;
                  a__6 = 1;
                  ilast = 2;
                } else if (xv[0] < xv[2]) {
                  k = 0;
                  a__6 = 2;
                  ilast = 1;
                } else {
                  k = 2;
                  a__6 = 0;
                  ilast = 1;
                }
              } else if (xv[0] < xv[2]) {
                k = 1;
                a__6 = 0;
                ilast = 2;
              } else if (xv[1] < xv[2]) {
                k = 1;
                a__6 = 2;
                ilast = 0;
              } else {
                k = 2;
                a__6 = 1;
                ilast = 0;
              }
              if (xv[k] < xv[3]) {
                if (xv[3] < xv[ilast]) {
                  if (((xv[a__6] < 0.0) != (xv[3] < 0.0)) ||
                      std::isinf(xv[a__6])) {
                    y[j] = (xv[a__6] + xv[3]) / 2.0;
                  } else {
                    y[j] = xv[a__6] + (xv[3] - xv[a__6]) / 2.0;
                  }
                } else if (((xv[a__6] < 0.0) != (xv[ilast] < 0.0)) ||
                           std::isinf(xv[a__6])) {
                  y[j] = (xv[a__6] + xv[ilast]) / 2.0;
                } else {
                  y[j] = xv[a__6] + (xv[ilast] - xv[a__6]) / 2.0;
                }
              } else if (((xv[k] < 0.0) != (xv[a__6] < 0.0)) ||
                         std::isinf(xv[k])) {
                y[j] = (xv[k] + xv[a__6]) / 2.0;
              } else {
                y[j] = xv[k] + (xv[a__6] - xv[k]) / 2.0;
              }
            }
          } else {
            a__6 = nx_tmp >> 1;
            if ((static_cast<unsigned int>(nx_tmp) & 1U) == 0U) {
              double m;
              m = internal::quickselect(xv, a__6 + 1, nx_tmp, k, ilast);
              y[j] = m;
              if (a__6 < k) {
                double b;
                b = internal::quickselect(xv, a__6, ilast - 1, k, a__6);
                if (((m < 0.0) != (b < 0.0)) || std::isinf(m)) {
                  y[j] = (m + b) / 2.0;
                } else {
                  y[j] = m + (b - m) / 2.0;
                }
              }
            } else {
              y[j] = internal::quickselect(xv, a__6 + 1, nx_tmp, k, a__6);
            }
          }
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
  }
}

} // namespace coder

//
// File trailer for median.cpp
//
// [EOF]
//
