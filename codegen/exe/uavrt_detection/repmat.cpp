//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: repmat.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Oct-2022 17:38:50
//

// Include Files
#include "repmat.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_internal_types.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const c_struct_T *a
//                double varargin_1
//                double varargin_2
//                ::coder::array<c_struct_T, 2U> &b
// Return Type  : void
//
namespace coder {
void repmat(const c_struct_T *a, double varargin_1, double varargin_2,
            ::coder::array<c_struct_T, 2U> &b)
{
  int loop_ub;
  b.set_size(static_cast<int>(varargin_1), static_cast<int>(varargin_2));
  loop_ub = static_cast<int>(varargin_1) * static_cast<int>(varargin_2);
  for (int i{0}; i < loop_ub; i++) {
    b[i] = *a;
  }
}

} // namespace coder

//
// File trailer for repmat.cpp
//
// [EOF]
//
