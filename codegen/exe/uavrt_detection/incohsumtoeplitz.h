//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: incohsumtoeplitz.h
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 04-Mar-2024 13:02:36
//

#ifndef INCOHSUMTOEPLITZ_H
#define INCOHSUMTOEPLITZ_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
namespace coder {
class sparse;

}

// Function Declarations
void incohsumtoeplitz(const coder::array<boolean_T, 1U> &Fb,
                      const coder::array<creal_T, 2U> &Wfherm,
                      const coder::array<creal_T, 2U> &S,
                      const coder::sparse &IR,
                      const coder::array<double, 1U> &Tb,
                      const coder::sparse &Wq,
                      coder::array<double, 2U> &Sscores,
                      coder::array<double, 2U> &Scols);

#endif
//
// File trailer for incohsumtoeplitz.h
//
// [EOF]
//
