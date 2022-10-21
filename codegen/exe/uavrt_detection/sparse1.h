//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: sparse1.h
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 20-Oct-2022 20:46:49
//

#ifndef SPARSE1_H
#define SPARSE1_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
namespace coder {
class f_sparse;

class g_sparse;

class e_sparse;

class c_sparse;

class h_sparse;

} // namespace coder

// Type Definitions
namespace coder {
class sparse {
public:
  void mtimes(const ::coder::array<double, 2U> &a,
              ::coder::array<double, 2U> &c) const;
  static void eyeLike(int ndiag, int b_m, int b_n, sparse *b_I);
  void logical(f_sparse *y) const;
  void parenReference(g_sparse *s) const;
  void parenReference(const ::coder::array<double, 1U> &varargin_2,
                      sparse *s) const;
  void fillIn();
  static void b_realloc(f_sparse *b_this, int numAllocRequested, int ub1,
                        int lb2, int ub2);
  array<double, 1U> d;
  array<int, 1U> colidx;
  array<int, 1U> rowidx;
  int m;
  int n;
  int maxnz;
};

class b_sparse {
public:
  void eq(const e_sparse *b, c_sparse *s) const;
  array<double, 1U> d;
  array<int, 1U> colidx;
  array<int, 1U> rowidx;
  int n;
};

class c_sparse {
public:
  void b_not(c_sparse *out) const;
  array<boolean_T, 1U> d;
  array<int, 1U> colidx;
  array<int, 1U> rowidx;
  int n;
};

class d_sparse {
public:
  array<boolean_T, 1U> d;
  array<int, 1U> colidx;
  array<int, 1U> rowidx;
};

class e_sparse {
public:
  array<double, 1U> d;
  array<int, 1U> colidx;
  array<int, 1U> rowidx;
};

class f_sparse {
public:
  void parenReference(const ::coder::array<double, 2U> &varargin_1,
                      c_sparse *s) const;
  void mtimes(const ::coder::array<double, 2U> &b,
              ::coder::array<double, 2U> &c) const;
  void b_mtimes(const ::coder::array<double, 2U> &a,
                ::coder::array<double, 2U> &c) const;
  void parenAssign2D(boolean_T rhs, double r, double c);
  void parenAssign(const h_sparse *rhs,
                   const ::coder::array<double, 2U> &varargin_1);
  void parenAssign(const ::coder::array<double, 2U> &rhs,
                   const ::coder::array<double, 2U> &varargin_1);
  array<boolean_T, 1U> d;
  array<int, 1U> colidx;
  array<int, 1U> rowidx;
  int m;
  int n;
  int maxnz;
};

class g_sparse {
public:
  array<double, 1U> d;
  array<int, 1U> colidx;
  array<int, 1U> rowidx;
  int m;
  int maxnz;
};

class h_sparse {
public:
  array<boolean_T, 1U> d;
  array<int, 1U> colidx;
  array<int, 1U> rowidx;
  int m;
};

} // namespace coder

#endif
//
// File trailer for sparse1.h
//
// [EOF]
//
