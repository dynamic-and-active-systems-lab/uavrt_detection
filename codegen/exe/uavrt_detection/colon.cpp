//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: colon.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Oct-2022 17:38:50
//

// Include Files
#include "colon.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : double a
//                double b
//                ::coder::array<double, 2U> &y
// Return Type  : void
//
namespace coder {
void eml_float_colon(double a, double b, ::coder::array<double, 2U> &y)
{
  double apnd;
  double cdiff;
  double ndbl;
  int n;
  ndbl = std::floor((b - a) + 0.5);
  apnd = a + ndbl;
  cdiff = apnd - b;
  if (std::abs(cdiff) <
      4.4408920985006262E-16 * std::fmax(std::abs(a), std::abs(b))) {
    ndbl++;
    apnd = b;
  } else if (cdiff > 0.0) {
    apnd = a + (ndbl - 1.0);
  } else {
    ndbl++;
  }
  if (ndbl >= 0.0) {
    n = static_cast<int>(ndbl);
  } else {
    n = 0;
  }
  y.set_size(1, n);
  if (n > 0) {
    y[0] = a;
    if (n > 1) {
      int nm1d2;
      y[n - 1] = apnd;
      nm1d2 = (n - 1) / 2;
      for (int k{0}; k <= nm1d2 - 2; k++) {
        y[k + 1] = a + (static_cast<double>(k) + 1.0);
        y[(n - k) - 2] = apnd - (static_cast<double>(k) + 1.0);
      }
      if (nm1d2 << 1 == n - 1) {
        y[nm1d2] = (a + apnd) / 2.0;
      } else {
        y[nm1d2] = a + static_cast<double>(nm1d2);
        y[nm1d2 + 1] = apnd - static_cast<double>(nm1d2);
      }
    }
  }
}

//
// Arguments    : int a
//                ::coder::array<int, 2U> &y
// Return Type  : void
//
void eml_integer_colon_dispatcher(int a, ::coder::array<int, 2U> &y)
{
  int n;
  if (a > 49621) {
    n = 0;
  } else {
    unsigned int u;
    if (a < 0) {
      u = 49621U - static_cast<unsigned int>(a);
    } else {
      u = static_cast<unsigned int>(49621 - a);
    }
    n = static_cast<int>(u) + 1;
  }
  y.set_size(1, n);
  if (n > 0) {
    int yk;
    y[0] = a;
    yk = a;
    for (int k{2}; k <= n; k++) {
      yk++;
      y[k - 1] = yk;
    }
  }
}

} // namespace coder

//
// File trailer for colon.cpp
//
// [EOF]
//
