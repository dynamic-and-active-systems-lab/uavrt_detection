//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: quickselect.h
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 04-Mar-2024 13:02:36
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
