//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: locBsearch.h
//
<<<<<<< HEAD
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 23-May-2023 12:05:02
=======
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Apr-2023 11:47:02
>>>>>>> 3930a1e557481905555f2756f2f70ac82e87beba
//

#ifndef LOCBSEARCH_H
#define LOCBSEARCH_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
int b_sparse_locBsearch(const ::coder::array<int, 1U> &x, int xi, int xstart,
                        int xend, boolean_T &found);

int sparse_locBsearch(const ::coder::array<int, 1U> &x, double xi, int xstart,
                      int xend, boolean_T &found);

} // namespace coder

#endif
//
// File trailer for locBsearch.h
//
// [EOF]
//
