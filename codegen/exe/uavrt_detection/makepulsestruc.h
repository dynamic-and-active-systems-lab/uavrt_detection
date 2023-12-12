//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: makepulsestruc.h
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 12-Dec-2023 09:08:48
//

#ifndef MAKEPULSESTRUC_H
#define MAKEPULSESTRUC_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
struct c_struct_T;

// Function Declarations
void makepulsestruc(c_struct_T *thepulse);

void makepulsestruc(double A, double yw, double SNR, double t_0, double t_f,
                    const double t_next[2], double fp, double fstart,
                    double fend, c_struct_T *thepulse);

#endif
//
// File trailer for makepulsestruc.h
//
// [EOF]
//
