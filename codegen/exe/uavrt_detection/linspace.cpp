//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: linspace.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Oct-2022 17:38:50
//

// Include Files
#include "linspace.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : double d2
//                double n
//                ::coder::array<double, 2U> &y
// Return Type  : void
//
namespace coder {
void linspace(double d2, double n, ::coder::array<double, 2U> &y)
{
  if (!(n >= 0.0)) {
    y.set_size(1, 0);
  } else {
    double delta1;
    delta1 = std::floor(n);
    y.set_size(1, static_cast<int>(delta1));
    if (static_cast<int>(delta1) >= 1) {
      y[static_cast<int>(delta1) - 1] = d2;
      if (y.size(1) >= 2) {
        y[0] = 0.0;
        if (y.size(1) >= 3) {
          if (-d2 == 0.0) {
            int i;
            delta1 = d2 / (static_cast<double>(y.size(1)) - 1.0);
            i = y.size(1) - 1;
            for (int k{2}; k <= i; k++) {
              y[k - 1] =
                  static_cast<double>(((k << 1) - y.size(1)) - 1) * delta1;
            }
            if ((y.size(1) & 1) == 1) {
              y[y.size(1) >> 1] = 0.0;
            }
          } else if ((d2 < 0.0) && (std::abs(d2) > 8.9884656743115785E+307)) {
            int i;
            delta1 = d2 / (static_cast<double>(y.size(1)) - 1.0);
            i = y.size(1);
            for (int k{0}; k <= i - 3; k++) {
              y[k + 1] = delta1 * (static_cast<double>(k) + 1.0);
            }
          } else {
            int i;
            delta1 = d2 / (static_cast<double>(y.size(1)) - 1.0);
            i = y.size(1);
            for (int k{0}; k <= i - 3; k++) {
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
