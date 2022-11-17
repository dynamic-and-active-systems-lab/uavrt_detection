//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// sortLE.h
//
// Code generation for function 'sortLE'
//

#ifndef SORTLE_H
#define SORTLE_H

// Include files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
boolean_T sortLE(const ::coder::array<double, 2U> &v,
                 const ::coder::array<int, 2U> &dir, int idx1, int idx2);

}
} // namespace coder

#endif
// End of code generation (sortLE.h)
