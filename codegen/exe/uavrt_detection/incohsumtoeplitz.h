//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: incohsumtoeplitz.h
//
<<<<<<< HEAD
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 23-May-2023 12:05:02
=======
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Apr-2023 11:47:02
>>>>>>> 3930a1e557481905555f2756f2f70ac82e87beba
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
