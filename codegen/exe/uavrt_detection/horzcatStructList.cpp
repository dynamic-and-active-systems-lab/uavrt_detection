//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: horzcatStructList.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 11-Aug-2023 10:24:30
//

// Include Files
#include "horzcatStructList.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_internal_types.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<c_struct_T, 2U> &structure
//                ::coder::array<double, 2U> &result
// Return Type  : void
//
namespace coder {
namespace internal {
void b_horzcatStructList(const ::coder::array<c_struct_T, 2U> &structure,
                         ::coder::array<double, 2U> &result)
{
  int i;
  int n;
  n = structure.size(1);
  if (structure.size(1) == 0) {
    i = 0;
  } else {
    i = structure.size(1);
  }
  result.set_size(1, i);
  if (structure.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (i = 0; i < n; i++) {
    result[i] = structure[i].t_0;
  }
}

//
// Arguments    : const ::coder::array<c_struct_T, 2U> &structure
//                ::coder::array<double, 2U> &result
// Return Type  : void
//
void horzcatStructList(const ::coder::array<c_struct_T, 2U> &structure,
                       ::coder::array<double, 2U> &result)
{
  int i;
  int n;
  n = structure.size(1);
  if (structure.size(1) == 0) {
    i = 0;
  } else {
    i = structure.size(1);
  }
  result.set_size(1, i);
  if (structure.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (i = 0; i < n; i++) {
    result[i] = structure[i].fp;
  }
}

} // namespace internal
} // namespace coder

//
// File trailer for horzcatStructList.cpp
//
// [EOF]
//
