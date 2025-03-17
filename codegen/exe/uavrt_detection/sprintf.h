//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sprintf.h
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 04-Feb-2025 09:56:05
//

#ifndef SPRINTF_H
#define SPRINTF_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
namespace coder {
class rtString;

}

// Function Declarations
namespace coder {
void b_sprintf(int varargin_1, int varargin_2, array<char, 2U> &str);

void b_sprintf(const array<char, 2U> &varargin_1, double varargin_2,
               double varargin_3, double varargin_4, double varargin_5,
               unsigned int varargin_6, rtString &str);

void c_sprintf(int varargin_1, int varargin_2, array<char, 2U> &str);

} // namespace coder

#endif
//
// File trailer for sprintf.h
//
// [EOF]
//
