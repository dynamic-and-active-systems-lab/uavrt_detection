//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: minOrMax.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "minOrMax.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const coder::array<double, 1U> &in1
//                const coder::array<double, 1U> &in2
//                int &out2
// Return Type  : double
//
double binary_expand_op_21(const coder::array<double, 1U> &in1,
                           const coder::array<double, 1U> &in2, int &out2)
{
  coder::array<double, 1U> b_in1;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in2.size(0) == 1) {
    loop_ub = in1.size(0);
  } else {
    loop_ub = in2.size(0);
  }
  b_in1.set_size(loop_ub);
  stride_0_0 = (in1.size(0) != 1);
  stride_1_0 = (in2.size(0) != 1);
  for (int i{0}; i < loop_ub; i++) {
    b_in1[i] = in1[i * stride_0_0] * in2[i * stride_1_0];
  }
  return coder::internal::b_maximum(b_in1, out2);
}

//
// Arguments    : const coder::array<boolean_T, 1U> &in1
//                const coder::array<double, 1U> &in2
//                int &out2
// Return Type  : double
//
double binary_expand_op_23(const coder::array<boolean_T, 1U> &in1,
                           const coder::array<double, 1U> &in2, int &out2)
{
  coder::array<double, 1U> b_in1;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in2.size(0) == 1) {
    loop_ub = in1.size(0);
  } else {
    loop_ub = in2.size(0);
  }
  b_in1.set_size(loop_ub);
  stride_0_0 = (in1.size(0) != 1);
  stride_1_0 = (in2.size(0) != 1);
  for (int i{0}; i < loop_ub; i++) {
    b_in1[i] = static_cast<double>(in1[i * stride_0_0]) * in2[i * stride_1_0];
  }
  return coder::internal::b_maximum(b_in1, out2);
}

//
// Arguments    : const array<double, 1U> &x
//                int &idx
// Return Type  : double
//
namespace coder {
namespace internal {
double b_maximum(const array<double, 1U> &x, int &idx)
{
  double ex;
  int last;
  if (x.size(0) < 1) {
    mb_rtErrorWithMessageID(wb_emlrtRTEI.fName, wb_emlrtRTEI.lineNo);
  }
  last = x.size(0);
  if (x.size(0) <= 2) {
    if (x.size(0) == 1) {
      ex = x[0];
      idx = 1;
    } else if ((x[0] < x[1]) || (std::isnan(x[0]) && (!std::isnan(x[1])))) {
      ex = x[1];
      idx = 2;
    } else {
      ex = x[0];
      idx = 1;
    }
  } else {
    int k;
    if (!std::isnan(x[0])) {
      idx = 1;
    } else {
      boolean_T exitg1;
      idx = 0;
      if (x.size(0) > 2147483646) {
        check_forloop_overflow_error();
      }
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= last)) {
        if (!std::isnan(x[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }
    if (idx == 0) {
      ex = x[0];
      idx = 1;
    } else {
      int a;
      ex = x[idx - 1];
      a = idx + 1;
      if ((idx + 1 <= x.size(0)) && (x.size(0) > 2147483646)) {
        check_forloop_overflow_error();
      }
      for (k = a; k <= last; k++) {
        double d;
        d = x[k - 1];
        if (ex < d) {
          ex = d;
          idx = k;
        }
      }
    }
  }
  return ex;
}

//
// Arguments    : const double x_data[]
// Return Type  : double
//
double b_minimum(const double x_data[])
{
  double ex;
  if ((x_data[0] > x_data[1]) ||
      (std::isnan(x_data[0]) && (!std::isnan(x_data[1])))) {
    ex = x_data[1];
  } else {
    ex = x_data[0];
  }
  return ex;
}

//
// Arguments    : const array<double, 1U> &x
// Return Type  : double
//
double maximum(const array<double, 1U> &x)
{
  double ex;
  int last;
  if (x.size(0) < 1) {
    mb_rtErrorWithMessageID(wb_emlrtRTEI.fName, wb_emlrtRTEI.lineNo);
  }
  last = x.size(0);
  if (x.size(0) <= 2) {
    if (x.size(0) == 1) {
      ex = x[0];
    } else if ((x[0] < x[1]) || (std::isnan(x[0]) && (!std::isnan(x[1])))) {
      ex = x[1];
    } else {
      ex = x[0];
    }
  } else {
    int idx;
    int k;
    if (!std::isnan(x[0])) {
      idx = 1;
    } else {
      boolean_T exitg1;
      idx = 0;
      if (x.size(0) > 2147483646) {
        check_forloop_overflow_error();
      }
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= last)) {
        if (!std::isnan(x[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }
    if (idx == 0) {
      ex = x[0];
    } else {
      int a;
      ex = x[idx - 1];
      a = idx + 1;
      if ((idx + 1 <= x.size(0)) && (x.size(0) > 2147483646)) {
        check_forloop_overflow_error();
      }
      for (k = a; k <= last; k++) {
        double d;
        d = x[k - 1];
        if (ex < d) {
          ex = d;
        }
      }
    }
  }
  return ex;
}

//
// Arguments    : const array<double, 2U> &x
//                array<double, 1U> &ex
//                array<int, 1U> &idx
// Return Type  : void
//
void maximum(const array<double, 2U> &x, array<double, 1U> &ex,
             array<int, 1U> &idx)
{
  int m_tmp;
  int n;
  if (x.size(1) < 1) {
    mb_rtErrorWithMessageID(wb_emlrtRTEI.fName, wb_emlrtRTEI.lineNo);
  }
  m_tmp = x.size(0);
  n = x.size(1);
  ex.set_size(x.size(0));
  idx.set_size(x.size(0));
  for (int i{0}; i < m_tmp; i++) {
    idx[i] = 1;
  }
  if (x.size(0) >= 1) {
    if (x.size(0) > 2147483646) {
      check_forloop_overflow_error();
    }
    for (int i{0}; i < m_tmp; i++) {
      ex[i] = x[i];
    }
    for (int j{2}; j <= n; j++) {
      if (m_tmp > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int i{0}; i < m_tmp; i++) {
        double b;
        boolean_T p;
        b = x[i + x.size(0) * (j - 1)];
        if (std::isnan(b)) {
          p = false;
        } else if (std::isnan(ex[i])) {
          p = true;
        } else {
          p = (ex[i] < b);
        }
        if (p) {
          ex[i] = b;
          idx[i] = j;
        }
      }
    }
  }
}

//
// Arguments    : const array<double, 1U> &x
//                int &idx
// Return Type  : double
//
double maximum(const array<double, 1U> &x, int &idx)
{
  double ex;
  int last;
  if (x.size(0) < 1) {
    mb_rtErrorWithMessageID(wb_emlrtRTEI.fName, wb_emlrtRTEI.lineNo);
  }
  last = x.size(0);
  if (x.size(0) <= 2) {
    if (x.size(0) == 1) {
      ex = x[0];
      idx = 1;
    } else if ((x[0] < x[1]) || (std::isnan(x[0]) && (!std::isnan(x[1])))) {
      ex = x[1];
      idx = 2;
    } else {
      ex = x[0];
      idx = 1;
    }
  } else {
    int k;
    if (!std::isnan(x[0])) {
      idx = 1;
    } else {
      boolean_T exitg1;
      idx = 0;
      if (x.size(0) > 2147483646) {
        check_forloop_overflow_error();
      }
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= last)) {
        if (!std::isnan(x[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }
    if (idx == 0) {
      ex = x[0];
      idx = 1;
    } else {
      int a;
      ex = x[idx - 1];
      a = idx + 1;
      if ((idx + 1 <= x.size(0)) && (x.size(0) > 2147483646)) {
        check_forloop_overflow_error();
      }
      for (k = a; k <= last; k++) {
        double d;
        d = x[k - 1];
        if (ex < d) {
          ex = d;
          idx = k;
        }
      }
    }
  }
  return ex;
}

//
// Arguments    : const double x[2]
// Return Type  : double
//
double maximum(const double x[2])
{
  double ex;
  if ((x[0] < x[1]) || (std::isnan(x[0]) && (!std::isnan(x[1])))) {
    ex = x[1];
  } else {
    ex = x[0];
  }
  return ex;
}

//
// Arguments    : const double x[2]
// Return Type  : double
//
double minimum(const double x[2])
{
  double ex;
  if ((x[0] > x[1]) || (std::isnan(x[0]) && (!std::isnan(x[1])))) {
    ex = x[1];
  } else {
    ex = x[0];
  }
  return ex;
}

} // namespace internal
} // namespace coder

//
// File trailer for minOrMax.cpp
//
// [EOF]
//
