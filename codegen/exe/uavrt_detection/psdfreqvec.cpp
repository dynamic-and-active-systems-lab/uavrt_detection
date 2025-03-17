//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: psdfreqvec.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "psdfreqvec.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : double varargin_2
//                double varargin_4
//                array<double, 1U> &w
// Return Type  : void
//
namespace coder {
void psdfreqvec(double varargin_2, double varargin_4, array<double, 1U> &w)
{
  static rtBoundsCheckInfo ab_emlrtBCI{
      74,             // lineNo
      "",             // aName
      "frequencygrid" // fName
  };
  static rtBoundsCheckInfo bb_emlrtBCI{
      75,             // lineNo
      "",             // aName
      "frequencygrid" // fName
  };
  static rtBoundsCheckInfo cb_emlrtBCI{
      80,             // lineNo
      "",             // aName
      "frequencygrid" // fName
  };
  static rtBoundsCheckInfo db_emlrtBCI{
      78,             // lineNo
      "",             // aName
      "frequencygrid" // fName
  };
  static rtDoubleCheckInfo q_emlrtDCI{
      74,             // lineNo
      "frequencygrid" // fName
  };
  static rtDoubleCheckInfo r_emlrtDCI{
      80,             // lineNo
      "frequencygrid" // fName
  };
  static rtDoubleCheckInfo s_emlrtDCI{
      78,             // lineNo
      "frequencygrid" // fName
  };
  array<double, 2U> w1;
  double Fs1;
  double Nyq;
  double d;
  double freq_res;
  double half_res;
  double x;
  int loop_ub;
  boolean_T isNPTSodd;
  if (std::isnan(varargin_4)) {
    Fs1 = 6.2831853071795862;
  } else {
    Fs1 = varargin_4;
  }
  freq_res = Fs1 / varargin_2;
  if (std::isnan(varargin_2 - 1.0)) {
    w1.set_size(1, 1);
    w1[0] = rtNaN;
  } else if (varargin_2 - 1.0 < 0.0) {
    w1.set_size(w1.size(0), 0);
  } else {
    w1.set_size(1, static_cast<int>(varargin_2 - 1.0) + 1);
    loop_ub = static_cast<int>(varargin_2 - 1.0);
    for (int i{0}; i <= loop_ub; i++) {
      w1[i] = i;
    }
  }
  w1.set_size(1, w1.size(1));
  loop_ub = w1.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    w1[i] = freq_res * w1[i];
  }
  Nyq = Fs1 / 2.0;
  half_res = freq_res / 2.0;
  if (std::isnan(varargin_2) || std::isinf(varargin_2)) {
    x = rtNaN;
  } else {
    x = std::fmod(varargin_2, 2.0);
  }
  if (std::isnan(x)) {
    y_rtErrorWithMessageID(hb_emlrtRTEI.fName, hb_emlrtRTEI.lineNo);
  }
  isNPTSodd = (x != 0.0);
  if (isNPTSodd) {
    x = (varargin_2 + 1.0) / 2.0;
  } else {
    x = varargin_2 / 2.0 + 1.0;
  }
  if (std::isnan(x) || std::isinf(x)) {
    d = rtNaN;
  } else {
    d = std::fmod(x, 2.0);
  }
  if (std::isnan(d)) {
    y_rtErrorWithMessageID(hb_emlrtRTEI.fName, hb_emlrtRTEI.lineNo);
  }
  if (isNPTSodd) {
    if (x != static_cast<int>(std::floor(x))) {
      rtIntegerError(x, q_emlrtDCI);
    }
    if ((static_cast<int>(x) < 1) || (static_cast<int>(x) > w1.size(1))) {
      rtDynamicBoundsError(static_cast<int>(x), 1, w1.size(1), ab_emlrtBCI);
    }
    w1[static_cast<int>(x) - 1] = Nyq - half_res;
    if ((static_cast<int>(static_cast<unsigned int>(x) + 1U) < 1) ||
        (static_cast<int>(static_cast<unsigned int>(x) + 1U) > w1.size(1))) {
      rtDynamicBoundsError(static_cast<int>(static_cast<unsigned int>(x) + 1U),
                           1, w1.size(1), bb_emlrtBCI);
    }
    w1[static_cast<int>(static_cast<unsigned int>(x))] = Nyq + half_res;
  } else {
    if (x != static_cast<int>(std::floor(x))) {
      rtIntegerError(x, s_emlrtDCI);
    }
    if ((static_cast<int>(x) < 1) || (static_cast<int>(x) > w1.size(1))) {
      rtDynamicBoundsError(static_cast<int>(x), 1, w1.size(1), db_emlrtBCI);
    }
    w1[static_cast<int>(x) - 1] = Nyq;
  }
  loop_ub = w1.size(1);
  if (varargin_2 != static_cast<int>(std::floor(varargin_2))) {
    rtIntegerError(varargin_2, r_emlrtDCI);
  }
  if ((static_cast<int>(varargin_2) < 1) ||
      (static_cast<int>(varargin_2) > w1.size(1))) {
    rtDynamicBoundsError(static_cast<int>(varargin_2), 1, w1.size(1),
                         cb_emlrtBCI);
  }
  w1[static_cast<int>(varargin_2) - 1] = Fs1 - freq_res;
  w.set_size(w1.size(1));
  for (int i{0}; i < loop_ub; i++) {
    w[i] = w1[i];
  }
}

} // namespace coder

//
// File trailer for psdfreqvec.cpp
//
// [EOF]
//
