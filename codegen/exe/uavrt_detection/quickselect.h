//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: quickselect.h
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

#ifndef QUICKSELECT_H
#define QUICKSELECT_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
double quickselect(array<double, 1U> &v, int n, int vlen, int &nfirst,
                   int &nlast);

}
} // namespace coder

#endif
//
// File trailer for quickselect.h
//
// [EOF]
//
