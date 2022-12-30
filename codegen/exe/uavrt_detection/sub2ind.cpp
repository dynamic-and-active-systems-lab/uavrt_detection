//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sub2ind.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 30-Dec-2022 12:50:56
//

// Include Files
#include "sub2ind.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include "omp.h"
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string.h>
#include <string>

// Variable Definitions
static rtRunTimeErrorInfo ic_emlrtRTEI{
    32,           // lineNo
    "eml_sub2ind" // fName
};

// Function Declarations
static void ac_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

namespace coder {
static boolean_T allinrange(const ::coder::array<double, 2U> &x, int hi);

}

// Function Definitions
//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void ac_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "The subscript vectors must all be of the same size.";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// Arguments    : const ::coder::array<double, 2U> &x
//                int hi
// Return Type  : boolean_T
//
namespace coder {
static boolean_T allinrange(const ::coder::array<double, 2U> &x, int hi)
{
  int i;
  int k;
  boolean_T p;
  i = x.size(0) * x.size(1);
  k = 0;
  int exitg1;
  do {
    exitg1 = 0;
    if (k <= i - 1) {
      if ((x[k] >= 1.0) && (x[k] <= hi)) {
        k++;
      } else {
        p = false;
        exitg1 = 1;
      }
    } else {
      p = true;
      exitg1 = 1;
    }
  } while (exitg1 == 0);
  return p;
}

//
// Arguments    : const int siz[2]
//                const ::coder::array<double, 2U> &varargin_1
//                const ::coder::array<double, 2U> &varargin_2
//                ::coder::array<int, 2U> &idx
// Return Type  : void
//
void b_eml_sub2ind(const int siz[2],
                   const ::coder::array<double, 2U> &varargin_1,
                   const ::coder::array<double, 2U> &varargin_2,
                   ::coder::array<int, 2U> &idx)
{
  unsigned int b_varargin_1[2];
  unsigned int b_varargin_2[2];
  int k;
  boolean_T exitg1;
  boolean_T p;
  if (!allinrange(varargin_1, siz[0])) {
    yb_rtErrorWithMessageID(hc_emlrtRTEI.fName, hc_emlrtRTEI.lineNo);
  }
  b_varargin_1[0] = static_cast<unsigned int>(varargin_1.size(0));
  b_varargin_2[0] = static_cast<unsigned int>(varargin_2.size(0));
  b_varargin_1[1] = static_cast<unsigned int>(varargin_1.size(1));
  b_varargin_2[1] = static_cast<unsigned int>(varargin_2.size(1));
  p = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 2)) {
    if (static_cast<int>(b_varargin_1[k]) !=
        static_cast<int>(b_varargin_2[k])) {
      p = false;
      exitg1 = true;
    } else {
      k++;
    }
  }
  if (!p) {
    ac_rtErrorWithMessageID(ic_emlrtRTEI.fName, ic_emlrtRTEI.lineNo);
  }
  if (!allinrange(varargin_2, siz[1])) {
    yb_rtErrorWithMessageID(hc_emlrtRTEI.fName, hc_emlrtRTEI.lineNo);
  }
  idx.set_size(varargin_1.size(0), varargin_1.size(1));
  k = varargin_1.size(0) * varargin_1.size(1);
  for (int i{0}; i < k; i++) {
    idx[i] = static_cast<int>(varargin_1[i]) +
             siz[0] * (static_cast<int>(varargin_2[i]) - 1);
  }
}

//
// Arguments    : const int siz[2]
//                const ::coder::array<double, 2U> &varargin_1
//                const ::coder::array<double, 2U> &varargin_2
//                ::coder::array<int, 2U> &idx
// Return Type  : void
//
void eml_sub2ind(const int siz[2], const ::coder::array<double, 2U> &varargin_1,
                 const ::coder::array<double, 2U> &varargin_2,
                 ::coder::array<int, 2U> &idx)
{
  unsigned int b_varargin_1[2];
  unsigned int b_varargin_2[2];
  int hi;
  int k;
  boolean_T exitg1;
  boolean_T p;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= varargin_1.size(1) - 1)) {
    if ((varargin_1[k] >= 1.0) && (varargin_1[k] <= siz[0])) {
      k++;
    } else {
      yb_rtErrorWithMessageID(hc_emlrtRTEI.fName, hc_emlrtRTEI.lineNo);
    }
  }
  b_varargin_1[0] = 1U;
  b_varargin_2[0] = 1U;
  b_varargin_1[1] = static_cast<unsigned int>(varargin_1.size(1));
  b_varargin_2[1] = static_cast<unsigned int>(varargin_2.size(1));
  p = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 2)) {
    if (static_cast<int>(b_varargin_1[k]) !=
        static_cast<int>(b_varargin_2[k])) {
      p = false;
      exitg1 = true;
    } else {
      k++;
    }
  }
  if (!p) {
    ac_rtErrorWithMessageID(ic_emlrtRTEI.fName, ic_emlrtRTEI.lineNo);
  }
  hi = siz[1];
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= varargin_2.size(1) - 1)) {
    if ((varargin_2[k] >= 1.0) && (varargin_2[k] <= hi)) {
      k++;
    } else {
      yb_rtErrorWithMessageID(hc_emlrtRTEI.fName, hc_emlrtRTEI.lineNo);
    }
  }
  idx.set_size(1, varargin_1.size(1));
  k = varargin_1.size(1);
  for (hi = 0; hi < k; hi++) {
    idx[hi] = static_cast<int>(varargin_1[hi]) +
              siz[0] * (static_cast<int>(varargin_2[hi]) - 1);
  }
}

//
// Arguments    : const int siz[2]
//                const ::coder::array<double, 1U> &varargin_1
//                const ::coder::array<double, 1U> &varargin_2
//                ::coder::array<int, 1U> &idx
// Return Type  : void
//
void eml_sub2ind(const int siz[2], const ::coder::array<double, 1U> &varargin_1,
                 const ::coder::array<double, 1U> &varargin_2,
                 ::coder::array<int, 1U> &idx)
{
  unsigned int b_varargin_1[2];
  unsigned int b_varargin_2[2];
  int hi;
  int k;
  boolean_T exitg1;
  boolean_T p;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= varargin_1.size(0) - 1)) {
    if ((varargin_1[k] >= 1.0) && (varargin_1[k] <= siz[0])) {
      k++;
    } else {
      yb_rtErrorWithMessageID(hc_emlrtRTEI.fName, hc_emlrtRTEI.lineNo);
    }
  }
  b_varargin_1[0] = static_cast<unsigned int>(varargin_1.size(0));
  b_varargin_1[1] = 1U;
  b_varargin_2[0] = static_cast<unsigned int>(varargin_2.size(0));
  b_varargin_2[1] = 1U;
  p = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 2)) {
    if (static_cast<int>(b_varargin_1[k]) !=
        static_cast<int>(b_varargin_2[k])) {
      p = false;
      exitg1 = true;
    } else {
      k++;
    }
  }
  if (!p) {
    ac_rtErrorWithMessageID(ic_emlrtRTEI.fName, ic_emlrtRTEI.lineNo);
  }
  hi = siz[1];
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= varargin_2.size(0) - 1)) {
    if ((varargin_2[k] >= 1.0) && (varargin_2[k] <= hi)) {
      k++;
    } else {
      yb_rtErrorWithMessageID(hc_emlrtRTEI.fName, hc_emlrtRTEI.lineNo);
    }
  }
  idx.set_size(varargin_1.size(0));
  k = varargin_1.size(0);
  for (hi = 0; hi < k; hi++) {
    idx[hi] = static_cast<int>(varargin_1[hi]) +
              siz[0] * (static_cast<int>(varargin_2[hi]) - 1);
  }
}

//
// Arguments    : const int siz[2]
//                double varargin_2
// Return Type  : int
//
int eml_sub2ind(const int siz[2], double varargin_2)
{
  if (siz[0] < 1) {
    yb_rtErrorWithMessageID(hc_emlrtRTEI.fName, hc_emlrtRTEI.lineNo);
  }
  if (!(varargin_2 <= siz[1])) {
    yb_rtErrorWithMessageID(hc_emlrtRTEI.fName, hc_emlrtRTEI.lineNo);
  }
  return siz[0] * (static_cast<int>(varargin_2) - 1) + 1;
}

} // namespace coder

//
// File trailer for sub2ind.cpp
//
// [EOF]
//
