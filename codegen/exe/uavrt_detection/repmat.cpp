//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// repmat.cpp
//
// Code generation for function 'repmat'
//

// Include files
#include "repmat.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_internal_types.h"
#include "coder_array.h"
#include <string.h>

// Function Definitions
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

// End of code generation (repmat.cpp)
