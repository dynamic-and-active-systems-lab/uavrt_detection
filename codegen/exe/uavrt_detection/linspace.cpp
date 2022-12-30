//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: linspace.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 30-Dec-2022 11:43:16
//

// Include Files
#include "linspace.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include "omp.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string.h>
#include <string>

// Function Declarations
static void k_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum);

// Function Definitions
//
// Arguments    : const char *r
//                const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void k_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((outStream << "For code generation, ") << r) << " must not be NaN.";
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
// Arguments    : double d2
//                double n
//                ::coder::array<double, 2U> &y
// Return Type  : void
//
namespace coder {
void linspace(double d2, double n, ::coder::array<double, 2U> &y)
{
  static rtRunTimeErrorInfo qc_emlrtRTEI{
      33,        // lineNo
      "linspace" // fName
  };
  if (!(n >= 0.0)) {
    if (std::isnan(n)) {
      k_rtErrorWithMessageID("N", qc_emlrtRTEI.fName, qc_emlrtRTEI.lineNo);
    }
    y.set_size(1, 0);
  } else {
    double delta1;
    delta1 = std::floor(n);
    y.set_size(1, static_cast<int>(delta1));
    if (static_cast<int>(delta1) >= 1) {
      int y_tmp;
      y_tmp = static_cast<int>(delta1) - 1;
      y[static_cast<int>(delta1) - 1] = d2;
      if (y.size(1) >= 2) {
        y[0] = 0.0;
        if (y.size(1) >= 3) {
          if ((-d2 == 0.0) && (static_cast<int>(delta1) > 2)) {
            double d2scaled;
            d2scaled =
                d2 / (static_cast<double>(static_cast<int>(delta1)) - 1.0);
            for (int k{2}; k <= y_tmp; k++) {
              y[k - 1] = static_cast<double>(
                             ((k << 1) - static_cast<int>(delta1)) - 1) *
                         d2scaled;
            }
            if ((static_cast<int>(delta1) & 1) == 1) {
              y[static_cast<int>(delta1) >> 1] = 0.0;
            }
          } else if ((d2 < 0.0) && (std::abs(d2) > 8.9884656743115785E+307)) {
            delta1 = d2 / (static_cast<double>(y.size(1)) - 1.0);
            y_tmp = y.size(1);
            for (int k{0}; k <= y_tmp - 3; k++) {
              y[k + 1] = delta1 * (static_cast<double>(k) + 1.0);
            }
          } else {
            delta1 = d2 / (static_cast<double>(y.size(1)) - 1.0);
            y_tmp = y.size(1);
            for (int k{0}; k <= y_tmp - 3; k++) {
              y[k + 1] = (static_cast<double>(k) + 1.0) * delta1;
            }
          }
        }
      }
    }
  }
}

} // namespace coder

//
// File trailer for linspace.cpp
//
// [EOF]
//
