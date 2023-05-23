//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: function_handle.h
//
<<<<<<< HEAD
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 23-May-2023 12:05:02
=======
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Apr-2023 11:47:02
>>>>>>> 3930a1e557481905555f2756f2f70ac82e87beba
//

#ifndef FUNCTION_HANDLE_H
#define FUNCTION_HANDLE_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
class waveform;

// Function Declarations
boolean_T binary_expand_op(const coder::array<double, 1U> &in1,
                           const waveform *in2);

void h_binary_expand_op(const coder::array<boolean_T, 1U> &in1,
                        const coder::array<boolean_T, 1U> &in2);

#endif
//
// File trailer for function_handle.h
//
// [EOF]
//
