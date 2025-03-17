//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: horzcatStructList.h
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

#ifndef HORZCATSTRUCTLIST_H
#define HORZCATSTRUCTLIST_H

// Include Files
#include "rtwtypes.h"
#include "uavrt_detection_internal_types.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
void b_horzcatStructList(const array<c_struct_T, 1U> &structure,
                         array<double, 2U> &result);

void b_horzcatStructList(const c_struct_T structure[2], double result[2]);

void b_horzcatStructList(const array<c_struct_T, 2U> &structure,
                         array<double, 2U> &result);

void c_horzcatStructList(const array<c_struct_T, 1U> &structure,
                         array<double, 2U> &result);

void c_horzcatStructList(const array<c_struct_T, 2U> &structure,
                         array<double, 2U> &result);

void d_horzcatStructList(const array<c_struct_T, 2U> &structure,
                         array<boolean_T, 2U> &result);

void e_horzcatStructList(const array<c_struct_T, 2U> &structure,
                         array<double, 2U> &result);

void horzcatStructList(const array<c_struct_T, 2U> &structure,
                       array<boolean_T, 2U> &result);

} // namespace internal
} // namespace coder

#endif
//
// File trailer for horzcatStructList.h
//
// [EOF]
//
