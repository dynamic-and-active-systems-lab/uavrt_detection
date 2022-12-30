//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: circshift.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 30-Dec-2022 11:43:16
//

// Include Files
#include "circshift.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include <cmath>
#include <string.h>

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &a
// Return Type  : void
//
namespace coder {
void b_circshift(::coder::array<double, 2U> &a)
{
  array<double, 2U> buffer;
  if ((a.size(0) != 0) && (a.size(1) != 0) &&
      ((a.size(0) != 1) || (a.size(1) != 1))) {
    int i;
    int npages;
    int ns;
    int nv;
    boolean_T shiftright;
    ns = 0;
    shiftright = false;
    if (a.size(0) < 1) {
      mc_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
    }
    if ((a.size(0) >> 1) < 1) {
      ns = a.size(0) - 2;
      shiftright = true;
    }
    nv = static_cast<int>(std::floor(static_cast<double>(a.size(0)) / 2.0));
    buffer.set_size(
        1, static_cast<int>(std::floor(static_cast<double>(a.size(0)) / 2.0)));
    for (i = 0; i < nv; i++) {
      buffer[i] = 0.0;
    }
    nv = a.size(0);
    npages = a.size(1);
    if ((a.size(0) > 1) && (ns + 1 > 0)) {
      if (a.size(1) > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int b_i{0}; b_i < npages; b_i++) {
        int pageroot;
        pageroot = b_i * nv;
        if (shiftright) {
          for (int k{0}; k <= ns; k++) {
            buffer[k] = a[(((pageroot + k) + nv) - ns) - 1];
          }
          i = ns + 2;
          for (int k{nv}; k >= i; k--) {
            int i1;
            i1 = pageroot + k;
            a[i1 - 1] = a[(i1 - ns) - 2];
          }
          for (int k{0}; k <= ns; k++) {
            a[pageroot + k] = buffer[k];
          }
        } else {
          for (int k{0}; k <= ns; k++) {
            buffer[k] = a[pageroot + k];
          }
          i = nv - ns;
          for (int k{0}; k <= i - 2; k++) {
            int i1;
            i1 = pageroot + k;
            a[i1] = a[(i1 + ns) + 1];
          }
          for (int k{0}; k <= ns; k++) {
            a[(((pageroot + k) + nv) - ns) - 1] = buffer[k];
          }
        }
      }
    }
  }
}

//
// Arguments    : ::coder::array<double, 2U> &a
// Return Type  : void
//
void c_circshift(::coder::array<double, 2U> &a)
{
  array<double, 2U> buffer;
  if ((a.size(0) != 0) && (a.size(1) != 0) &&
      ((a.size(0) != 1) || (a.size(1) != 1))) {
    int i;
    int npages;
    int ns;
    int nv;
    boolean_T shiftright;
    ns = 1;
    shiftright = true;
    if (a.size(0) < 2) {
      if (a.size(0) == 0) {
        mc_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
      }
      ns = 1 - (a.size(0) << 1);
    }
    if (ns + 1 > (a.size(0) >> 1)) {
      ns = (a.size(0) - ns) - 2;
      shiftright = false;
    }
    nv = static_cast<int>(std::floor(static_cast<double>(a.size(0)) / 2.0));
    buffer.set_size(
        1, static_cast<int>(std::floor(static_cast<double>(a.size(0)) / 2.0)));
    for (i = 0; i < nv; i++) {
      buffer[i] = 0.0;
    }
    nv = a.size(0);
    npages = a.size(1);
    if ((a.size(0) > 1) && (ns + 1 > 0)) {
      if (a.size(1) > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int b_i{0}; b_i < npages; b_i++) {
        int pageroot;
        pageroot = b_i * nv;
        if (shiftright) {
          for (int k{0}; k <= ns; k++) {
            buffer[k] = a[(((pageroot + k) + nv) - ns) - 1];
          }
          i = ns + 2;
          for (int k{nv}; k >= i; k--) {
            int i1;
            i1 = pageroot + k;
            a[i1 - 1] = a[(i1 - ns) - 2];
          }
          for (int k{0}; k <= ns; k++) {
            a[pageroot + k] = buffer[k];
          }
        } else {
          for (int k{0}; k <= ns; k++) {
            buffer[k] = a[pageroot + k];
          }
          i = nv - ns;
          for (int k{0}; k <= i - 2; k++) {
            int i1;
            i1 = pageroot + k;
            a[i1] = a[(i1 + ns) + 1];
          }
          for (int k{0}; k <= ns; k++) {
            a[(((pageroot + k) + nv) - ns) - 1] = buffer[k];
          }
        }
      }
    }
  }
}

//
// Arguments    : ::coder::array<creal_T, 2U> &a
// Return Type  : void
//
void circshift(::coder::array<creal_T, 2U> &a)
{
  array<creal_T, 2U> buffer;
  if ((a.size(0) != 0) && (a.size(0) != 1)) {
    int i;
    int loop_ub;
    int ns;
    int u0;
    boolean_T shiftright;
    ns = 0;
    shiftright = false;
    if (a.size(0) < 1) {
      mc_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
    }
    if ((a.size(0) >> 1) < 1) {
      ns = a.size(0) - 2;
      shiftright = true;
    }
    u0 = a.size(0);
    if (u0 < 1) {
      u0 = 1;
    }
    if (a.size(0) == 0) {
      u0 = 0;
    }
    loop_ub = static_cast<int>(std::floor(static_cast<double>(u0) / 2.0));
    u0 = a.size(0);
    if (u0 < 1) {
      u0 = 1;
    }
    if (a.size(0) == 0) {
      u0 = 0;
    }
    buffer.set_size(
        1, static_cast<int>(std::floor(static_cast<double>(u0) / 2.0)));
    for (i = 0; i < loop_ub; i++) {
      buffer[i].re = 0.0;
      buffer[i].im = 0.0;
    }
    i = a.size(0) - 1;
    u0 = a.size(0);
    if ((a.size(0) > 1) && (ns + 1 > 0)) {
      if (shiftright) {
        for (loop_ub = 0; loop_ub <= ns; loop_ub++) {
          buffer[loop_ub] = a[(loop_ub + i) - ns];
        }
        i = ns + 2;
        for (loop_ub = u0; loop_ub >= i; loop_ub--) {
          a[loop_ub - 1] = a[(loop_ub - ns) - 2];
        }
        for (loop_ub = 0; loop_ub <= ns; loop_ub++) {
          a[loop_ub] = buffer[loop_ub];
        }
      } else {
        for (loop_ub = 0; loop_ub <= ns; loop_ub++) {
          buffer[loop_ub] = a[loop_ub];
        }
        u0 = (i - ns) - 1;
        for (loop_ub = 0; loop_ub <= u0; loop_ub++) {
          a[loop_ub] = a[(loop_ub + ns) + 1];
        }
        for (loop_ub = 0; loop_ub <= ns; loop_ub++) {
          a[(loop_ub + i) - ns] = buffer[loop_ub];
        }
      }
    }
  }
}

//
// Arguments    : ::coder::array<double, 2U> &a
// Return Type  : void
//
void circshift(::coder::array<double, 2U> &a)
{
  array<double, 2U> buffer;
  if ((a.size(0) != 0) && (a.size(1) != 0) &&
      ((a.size(0) != 1) || (a.size(1) != 1))) {
    int i;
    int npages;
    int ns;
    int nv;
    boolean_T shiftright;
    ns = 0;
    shiftright = true;
    if (a.size(0) < 1) {
      mc_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
    }
    if ((a.size(0) >> 1) < 1) {
      ns = a.size(0) - 2;
      shiftright = false;
    }
    nv = static_cast<int>(std::floor(static_cast<double>(a.size(0)) / 2.0));
    buffer.set_size(
        1, static_cast<int>(std::floor(static_cast<double>(a.size(0)) / 2.0)));
    for (i = 0; i < nv; i++) {
      buffer[i] = 0.0;
    }
    nv = a.size(0);
    npages = a.size(1);
    if ((a.size(0) > 1) && (ns + 1 > 0)) {
      if (a.size(1) > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int b_i{0}; b_i < npages; b_i++) {
        int pageroot;
        pageroot = b_i * nv;
        if (shiftright) {
          for (int k{0}; k <= ns; k++) {
            buffer[k] = a[(((pageroot + k) + nv) - ns) - 1];
          }
          i = ns + 2;
          for (int k{nv}; k >= i; k--) {
            int i1;
            i1 = pageroot + k;
            a[i1 - 1] = a[(i1 - ns) - 2];
          }
          for (int k{0}; k <= ns; k++) {
            a[pageroot + k] = buffer[k];
          }
        } else {
          for (int k{0}; k <= ns; k++) {
            buffer[k] = a[pageroot + k];
          }
          i = nv - ns;
          for (int k{0}; k <= i - 2; k++) {
            int i1;
            i1 = pageroot + k;
            a[i1] = a[(i1 + ns) + 1];
          }
          for (int k{0}; k <= ns; k++) {
            a[(((pageroot + k) + nv) - ns) - 1] = buffer[k];
          }
        }
      }
    }
  }
}

//
// Arguments    : ::coder::array<double, 2U> &a
// Return Type  : void
//
void d_circshift(::coder::array<double, 2U> &a)
{
  array<double, 2U> buffer;
  if ((a.size(0) != 0) && (a.size(1) != 0) &&
      ((a.size(0) != 1) || (a.size(1) != 1))) {
    int i;
    int npages;
    int ns;
    int nv;
    boolean_T shiftright;
    ns = 1;
    shiftright = false;
    if (a.size(0) < 2) {
      if (a.size(0) == 0) {
        mc_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
      }
      ns = 1 - (a.size(0) << 1);
    }
    if (ns + 1 > (a.size(0) >> 1)) {
      ns = (a.size(0) - ns) - 2;
      shiftright = true;
    }
    nv = static_cast<int>(std::floor(static_cast<double>(a.size(0)) / 2.0));
    buffer.set_size(
        1, static_cast<int>(std::floor(static_cast<double>(a.size(0)) / 2.0)));
    for (i = 0; i < nv; i++) {
      buffer[i] = 0.0;
    }
    nv = a.size(0);
    npages = a.size(1);
    if ((a.size(0) > 1) && (ns + 1 > 0)) {
      if (a.size(1) > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int b_i{0}; b_i < npages; b_i++) {
        int pageroot;
        pageroot = b_i * nv;
        if (shiftright) {
          for (int k{0}; k <= ns; k++) {
            buffer[k] = a[(((pageroot + k) + nv) - ns) - 1];
          }
          i = ns + 2;
          for (int k{nv}; k >= i; k--) {
            int i1;
            i1 = pageroot + k;
            a[i1 - 1] = a[(i1 - ns) - 2];
          }
          for (int k{0}; k <= ns; k++) {
            a[pageroot + k] = buffer[k];
          }
        } else {
          for (int k{0}; k <= ns; k++) {
            buffer[k] = a[pageroot + k];
          }
          i = nv - ns;
          for (int k{0}; k <= i - 2; k++) {
            int i1;
            i1 = pageroot + k;
            a[i1] = a[(i1 + ns) + 1];
          }
          for (int k{0}; k <= ns; k++) {
            a[(((pageroot + k) + nv) - ns) - 1] = buffer[k];
          }
        }
      }
    }
  }
}

//
// Arguments    : ::coder::array<double, 2U> &a
// Return Type  : void
//
void e_circshift(::coder::array<double, 2U> &a)
{
  array<double, 2U> buffer;
  if ((a.size(0) != 0) && (a.size(1) != 0) &&
      ((a.size(0) != 1) || (a.size(1) != 1))) {
    int i;
    int loop_ub;
    int ns;
    int stride;
    boolean_T shiftright;
    ns = 0;
    shiftright = true;
    if (a.size(1) < 1) {
      mc_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
    }
    if ((a.size(1) >> 1) < 1) {
      ns = a.size(1) - 2;
      shiftright = false;
    }
    loop_ub =
        static_cast<int>(std::floor(static_cast<double>(a.size(1)) / 2.0));
    buffer.set_size(
        1, static_cast<int>(std::floor(static_cast<double>(a.size(1)) / 2.0)));
    for (i = 0; i < loop_ub; i++) {
      buffer[i] = 0.0;
    }
    loop_ub = a.size(1) - 1;
    stride = a.size(0);
    if ((a.size(1) > 1) && (ns + 1 > 0)) {
      if (a.size(0) > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int j{0}; j < stride; j++) {
        if (shiftright) {
          for (int k{0}; k <= ns; k++) {
            buffer[k] = a[j + ((k + loop_ub) - ns) * stride];
          }
          i = ns + 2;
          for (int k{loop_ub + 1}; k >= i; k--) {
            a[j + (k - 1) * stride] = a[j + ((k - ns) - 2) * stride];
          }
          for (int k{0}; k <= ns; k++) {
            a[j + k * stride] = buffer[k];
          }
        } else {
          for (int k{0}; k <= ns; k++) {
            buffer[k] = a[j + k * stride];
          }
          i = loop_ub - ns;
          for (int k{0}; k < i; k++) {
            a[j + k * stride] = a[j + ((k + ns) + 1) * stride];
          }
          for (int k{0}; k <= ns; k++) {
            a[j + ((k + loop_ub) - ns) * stride] = buffer[k];
          }
        }
      }
    }
  }
}

//
// Arguments    : ::coder::array<double, 2U> &a
// Return Type  : void
//
void f_circshift(::coder::array<double, 2U> &a)
{
  array<double, 2U> buffer;
  if ((a.size(0) != 0) && (a.size(1) != 0) &&
      ((a.size(0) != 1) || (a.size(1) != 1))) {
    int i;
    int loop_ub;
    int ns;
    int stride;
    boolean_T shiftright;
    ns = 0;
    shiftright = false;
    if (a.size(1) < 1) {
      mc_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
    }
    if ((a.size(1) >> 1) < 1) {
      ns = a.size(1) - 2;
      shiftright = true;
    }
    loop_ub =
        static_cast<int>(std::floor(static_cast<double>(a.size(1)) / 2.0));
    buffer.set_size(
        1, static_cast<int>(std::floor(static_cast<double>(a.size(1)) / 2.0)));
    for (i = 0; i < loop_ub; i++) {
      buffer[i] = 0.0;
    }
    loop_ub = a.size(1) - 1;
    stride = a.size(0);
    if ((a.size(1) > 1) && (ns + 1 > 0)) {
      if (a.size(0) > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int j{0}; j < stride; j++) {
        if (shiftright) {
          for (int k{0}; k <= ns; k++) {
            buffer[k] = a[j + ((k + loop_ub) - ns) * stride];
          }
          i = ns + 2;
          for (int k{loop_ub + 1}; k >= i; k--) {
            a[j + (k - 1) * stride] = a[j + ((k - ns) - 2) * stride];
          }
          for (int k{0}; k <= ns; k++) {
            a[j + k * stride] = buffer[k];
          }
        } else {
          for (int k{0}; k <= ns; k++) {
            buffer[k] = a[j + k * stride];
          }
          i = loop_ub - ns;
          for (int k{0}; k < i; k++) {
            a[j + k * stride] = a[j + ((k + ns) + 1) * stride];
          }
          for (int k{0}; k <= ns; k++) {
            a[j + ((k + loop_ub) - ns) * stride] = buffer[k];
          }
        }
      }
    }
  }
}

//
// Arguments    : ::coder::array<boolean_T, 2U> &a
// Return Type  : void
//
void g_circshift(::coder::array<boolean_T, 2U> &a)
{
  array<boolean_T, 2U> buffer;
  if ((a.size(0) != 0) && (a.size(1) != 0) &&
      ((a.size(0) != 1) || (a.size(1) != 1))) {
    int i;
    int loop_ub;
    int ns;
    int stride;
    boolean_T shiftright;
    ns = 0;
    shiftright = false;
    if (a.size(1) < 1) {
      mc_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
    }
    if ((a.size(1) >> 1) < 1) {
      ns = a.size(1) - 2;
      shiftright = true;
    }
    loop_ub =
        static_cast<int>(std::floor(static_cast<double>(a.size(1)) / 2.0));
    buffer.set_size(
        1, static_cast<int>(std::floor(static_cast<double>(a.size(1)) / 2.0)));
    for (i = 0; i < loop_ub; i++) {
      buffer[i] = false;
    }
    loop_ub = a.size(1) - 1;
    stride = a.size(0);
    if ((a.size(1) > 1) && (ns + 1 > 0)) {
      if (a.size(0) > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int j{0}; j < stride; j++) {
        if (shiftright) {
          for (int k{0}; k <= ns; k++) {
            buffer[k] = a[j + ((k + loop_ub) - ns) * stride];
          }
          i = ns + 2;
          for (int k{loop_ub + 1}; k >= i; k--) {
            a[j + (k - 1) * stride] = a[j + ((k - ns) - 2) * stride];
          }
          for (int k{0}; k <= ns; k++) {
            a[j + k * stride] = buffer[k];
          }
        } else {
          for (int k{0}; k <= ns; k++) {
            buffer[k] = a[j + k * stride];
          }
          i = loop_ub - ns;
          for (int k{0}; k < i; k++) {
            a[j + k * stride] = a[j + ((k + ns) + 1) * stride];
          }
          for (int k{0}; k <= ns; k++) {
            a[j + ((k + loop_ub) - ns) * stride] = buffer[k];
          }
        }
      }
    }
  }
}

} // namespace coder

//
// File trailer for circshift.cpp
//
// [EOF]
//
