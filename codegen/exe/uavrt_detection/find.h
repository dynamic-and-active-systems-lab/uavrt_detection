//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: find.h
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Oct-2022 17:38:50
//

#ifndef FIND_H
#define FIND_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
namespace coder {
class sparse;

}
class waveform;

// Function Declarations
void b_binary_expand_op(int in1_data[], int *in1_size,
                        const coder::array<double, 1U> &in2, int in3, int in4,
                        int in5, const waveform *in6, int in7, int in8,
                        int in9);

void b_binary_expand_op(int in1_data[], int *in1_size,
                        const coder::array<double, 1U> &in2, int in3, int in4,
                        const waveform *in5, int in6, int in7);

namespace coder {
void b_eml_find(const ::coder::array<boolean_T, 2U> &x,
                ::coder::array<int, 2U> &i);

void c_eml_find(const ::coder::array<boolean_T, 1U> &x, int i_data[],
                int *i_size);

void d_eml_find(const ::coder::array<boolean_T, 1U> &x, int i_data[],
                int *i_size);

void e_eml_find(const sparse *x, ::coder::array<int, 1U> &i,
                ::coder::array<int, 1U> &j);

void eml_find(const ::coder::array<boolean_T, 2U> &x, int i_data[],
              int i_size[2]);

} // namespace coder

#endif
//
// File trailer for find.h
//
// [EOF]
//
