//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: validate_print_arguments.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 20-Oct-2022 20:46:49
//

// Include Files
#include "validate_print_arguments.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : unsigned int varargin_1
//                unsigned int varargin_2
//                unsigned int varargin_3
//                unsigned int validatedArguments[3]
// Return Type  : void
//
namespace coder {
namespace internal {
void validate_print_arguments(unsigned int varargin_1, unsigned int varargin_2,
                              unsigned int varargin_3,
                              unsigned int validatedArguments[3])
{
  validatedArguments[0] = varargin_1;
  validatedArguments[1] = varargin_2;
  validatedArguments[2] = varargin_3;
}

} // namespace internal
} // namespace coder

//
// File trailer for validate_print_arguments.cpp
//
// [EOF]
//
