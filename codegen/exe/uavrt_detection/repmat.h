//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// repmat.h
//
// Code generation for function 'repmat'
//

#ifndef REPMAT_H
#define REPMAT_H

// Include files
#include "rtwtypes.h"
#include "uavrt_detection_internal_types.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
void repmat(const c_struct_T *a, double varargin_1, double varargin_2,
            ::coder::array<c_struct_T, 2U> &b);

}

#endif
// End of code generation (repmat.h)
