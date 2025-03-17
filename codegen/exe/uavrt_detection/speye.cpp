//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: speye.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 04-Feb-2025 09:56:05
//

// Include Files
#include "speye.h"
#include "rt_nonfinite.h"
#include "sparse1.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const double m[2]
//                sparse &y
// Return Type  : void
//
namespace coder {
void speye(const double m[2], sparse &y)
{
  double d;
  int u0;
  int u1;
  if ((m[0] != std::floor(m[0])) || std::isinf(m[0]) ||
      (m[0] < -2.147483648E+9) || (m[0] > 2.147483647E+9)) {
    b_rtErrorWithMessageID(MIN_int32_T, jb_emlrtRTEI.fName,
                           jb_emlrtRTEI.lineNo);
  }
  if (m[0] <= 0.0) {
    d = 0.0;
  } else {
    d = m[0];
  }
  if (!(d <= 2.147483647E+9)) {
    m_rtErrorWithMessageID(m_emlrtRTEI.fName, m_emlrtRTEI.lineNo);
  }
  if ((m[1] != std::floor(m[1])) || std::isinf(m[1]) ||
      (m[1] < -2.147483648E+9) || (m[1] > 2.147483647E+9)) {
    b_rtErrorWithMessageID(MIN_int32_T, jb_emlrtRTEI.fName,
                           jb_emlrtRTEI.lineNo);
  }
  if (m[1] <= 0.0) {
    d = 0.0;
  } else {
    d = m[1];
  }
  if (!(d <= 2.147483647E+9)) {
    m_rtErrorWithMessageID(m_emlrtRTEI.fName, m_emlrtRTEI.lineNo);
  }
  u0 = static_cast<int>(m[0]);
  u1 = static_cast<int>(m[1]);
  if (u0 <= u1) {
    u1 = u0;
  }
  sparse::eyeLike(u1, static_cast<int>(m[0]), static_cast<int>(m[1]), y);
}

} // namespace coder

//
// File trailer for speye.cpp
//
// [EOF]
//
