//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// sparse.cpp
//
// Code generation for function 'sparse'
//

// Include files
#include "sparse.h"
#include "rt_nonfinite.h"
#include "sparse1.h"
#include "coder_array.h"
#include <string.h>

// Function Definitions
namespace coder {
void i_sparse(const ::coder::array<boolean_T, 2U> &varargin_1, c_sparse *y)
{
  int ctr;
  int i;
  int nInt;
  int numalloc;
  nInt = varargin_1.size(1);
  numalloc = 0;
  i = varargin_1.size(1);
  for (ctr = 0; ctr < i; ctr++) {
    if (varargin_1[ctr]) {
      numalloc++;
    }
  }
  y->n = varargin_1.size(1);
  if (numalloc < 1) {
    numalloc = 1;
  }
  y->d.set_size(numalloc);
  for (i = 0; i < numalloc; i++) {
    y->d[i] = false;
  }
  y->colidx.set_size(varargin_1.size(1) + 1);
  ctr = varargin_1.size(1);
  for (i = 0; i <= ctr; i++) {
    y->colidx[i] = 0;
  }
  y->colidx[0] = 1;
  y->rowidx.set_size(numalloc);
  for (i = 0; i < numalloc; i++) {
    y->rowidx[i] = 0;
  }
  y->rowidx[0] = 1;
  ctr = 0;
  for (numalloc = 0; numalloc < nInt; numalloc++) {
    if (varargin_1[numalloc]) {
      y->rowidx[ctr] = 1;
      y->d[ctr] = true;
      ctr++;
    }
    y->colidx[numalloc + 1] = ctr + 1;
  }
}

void j_sparse(const ::coder::array<double, 1U> &varargin_1, g_sparse *y)
{
  int mInt;
  int numalloc;
  int row;
  mInt = varargin_1.size(0);
  numalloc = 0;
  row = varargin_1.size(0);
  for (int k{0}; k < row; k++) {
    if (varargin_1[k] != 0.0) {
      numalloc++;
    }
  }
  y->m = varargin_1.size(0);
  if (numalloc < 1) {
    numalloc = 1;
  }
  y->maxnz = numalloc;
  y->d.set_size(numalloc);
  y->colidx.set_size(2);
  y->colidx[0] = 1;
  y->rowidx.set_size(numalloc);
  for (row = 0; row < numalloc; row++) {
    y->d[row] = 0.0;
    y->rowidx[row] = 0;
  }
  y->rowidx[0] = 1;
  numalloc = 0;
  for (row = 0; row < mInt; row++) {
    if (varargin_1[row] != 0.0) {
      y->rowidx[numalloc] = row + 1;
      y->d[numalloc] = 1.0;
      numalloc++;
    }
  }
  y->colidx[1] = numalloc + 1;
}

} // namespace coder

// End of code generation (sparse.cpp)
