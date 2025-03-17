//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sparse1.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "sparse1.h"
#include "anonymous_function.h"
#include "bigProduct.h"
#include "eml_int_forloop_overflow_check.h"
#include "ind2sub.h"
#include "indexShapeCheck.h"
#include "issorted.h"
#include "locBsearch.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include "sparse.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_internal_types.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include "omp.h"
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <stdexcept>
#include <string>

// Variable Definitions
static rtRunTimeErrorInfo yb_emlrtRTEI{
    29,             // lineNo
    "sparse/mtimes" // fName
};

static rtRunTimeErrorInfo bc_emlrtRTEI{
    12,                                  // lineNo
    "sparse/sparse_validateNumericIndex" // fName
};

static rtRunTimeErrorInfo dc_emlrtRTEI{
    1623,             // lineNo
    "assertValidSize" // fName
};

static rtRunTimeErrorInfo hc_emlrtRTEI{
    11,                                  // lineNo
    "sparse/sparse_validateNumericIndex" // fName
};

static rtRunTimeErrorInfo ic_emlrtRTEI{
    92,                       // lineNo
    "parenReference2DColumns" // fName
};

static rtRunTimeErrorInfo pc_emlrtRTEI{
    18,                    // lineNo
    "sparse/parenAssign1D" // fName
};

// Function Declarations
static void dc_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void ec_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void fc_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void ic_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void ob_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void pb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void qb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void rc_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void rtErrorWithMessageID(const int i, const int i1,
                                 const char *aFcnName, int aLineNum);

static void rtErrorWithMessageID(const long i, const int i1,
                                 const char *aFcnName, int aLineNum);

static void sc_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void tc_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : f_sparse *b_this
//                int numAllocRequested
//                int ub1
//                int lb2
//                int ub2
//                int offs
// Return Type  : void
//
namespace coder {
void sparse::b_realloc(f_sparse *b_this, int numAllocRequested, int ub1,
                       int lb2, int ub2, int offs)
{
  static rtRunTimeErrorInfo rc_emlrtRTEI{
      237,           // lineNo
      "sparse/numel" // fName
  };
  array<int, 1U> rowidxt;
  array<boolean_T, 1U> dt;
  int numAlloc;
  int overflow;
  numAlloc = b_this->rowidx.size(0);
  rowidxt.set_size(numAlloc);
  for (overflow = 0; overflow < numAlloc; overflow++) {
    rowidxt[overflow] = b_this->rowidx[overflow];
  }
  numAlloc = b_this->d.size(0);
  dt.set_size(numAlloc);
  for (overflow = 0; overflow < numAlloc; overflow++) {
    dt[overflow] = b_this->d[overflow];
  }
  internal::b_bigProduct(b_this->m, b_this->n, overflow);
  if (overflow == 0) {
    internal::b_bigProduct(b_this->m, b_this->n, overflow);
    if (overflow != 0) {
      tc_rtErrorWithMessageID(rc_emlrtRTEI.fName, rc_emlrtRTEI.lineNo);
    }
    numAlloc = b_this->m * b_this->n;
    if (numAllocRequested <= numAlloc) {
      numAlloc = numAllocRequested;
    }
    if (numAlloc <= 1) {
      numAlloc = 1;
    }
  } else if (numAllocRequested <= 1) {
    numAlloc = 1;
  } else {
    numAlloc = numAllocRequested;
  }
  b_this->rowidx.set_size(numAlloc);
  b_this->d.set_size(numAlloc);
  for (overflow = 0; overflow < numAlloc; overflow++) {
    b_this->rowidx[overflow] = 0;
    b_this->d[overflow] = false;
  }
  b_this->maxnz = numAlloc;
  if (ub1 > 2147483646) {
    check_forloop_overflow_error();
  }
  for (numAlloc = 0; numAlloc < ub1; numAlloc++) {
    b_this->rowidx[numAlloc] = rowidxt[numAlloc];
    b_this->d[numAlloc] = dt[numAlloc];
  }
  if ((lb2 <= ub2) && (ub2 > 2147483646)) {
    check_forloop_overflow_error();
  }
  for (numAlloc = lb2; numAlloc <= ub2; numAlloc++) {
    overflow = (numAlloc + offs) - 1;
    b_this->rowidx[overflow] = rowidxt[numAlloc - 1];
    b_this->d[overflow] = dt[numAlloc - 1];
  }
}

//
// Arguments    : const array<boolean_T, 1U> &rhs
//                const array<int, 1U> &r
//                int c
// Return Type  : void
//
void f_sparse::parenAssign2D(const array<boolean_T, 1U> &rhs,
                             const array<int, 1U> &r, int c)
{
  static rtRunTimeErrorInfo rc_emlrtRTEI{
      42,                    // lineNo
      "sparse/parenAssign2D" // fName
  };
  int extraAlloc;
  int low_i;
  int nrow;
  int pass;
  int shiftleft;
  int sm;
  int vidx;
  if ((static_cast<int>(static_cast<unsigned int>(rhs.size(0)) & 65535U) +
           ((rhs.size(0) >> 16) << 16) !=
       r.size(0)) &&
      (r.size(0) != rhs.size(0))) {
    sc_rtErrorWithMessageID(rc_emlrtRTEI.fName, rc_emlrtRTEI.lineNo);
  }
  nrow = m;
  sm = r.size(0);
  for (low_i = 0; low_i < sm; low_i++) {
    if (r[low_i] <= 0) {
      ic_rtErrorWithMessageID(hc_emlrtRTEI.fName, hc_emlrtRTEI.lineNo);
    }
    if (r[low_i] > nrow) {
      rtErrorWithMessageID(r[low_i], nrow, bc_emlrtRTEI.fName,
                           bc_emlrtRTEI.lineNo);
    }
  }
  if (c <= 0) {
    ic_rtErrorWithMessageID(hc_emlrtRTEI.fName, hc_emlrtRTEI.lineNo);
  }
  if (c > n) {
    rtErrorWithMessageID(c, n, bc_emlrtRTEI.fName, bc_emlrtRTEI.lineNo);
  }
  pass = 0;
  shiftleft = 0;
  extraAlloc = 0;
  vidx = 0;
  if (r.size(0) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int ridx{0}; ridx < sm; ridx++) {
    if (ridx + 1 != sm) {
      nrow = r[ridx + 1];
    } else {
      nrow = 0;
    }
    if (r[ridx] == nrow) {
      if (pass != 0) {
        shiftleft++;
        pass--;
      }
    } else {
      int low_ip1;
      int mid_i;
      boolean_T guard1;
      boolean_T guard2;
      boolean_T thisv;
      guard1 = false;
      guard2 = false;
      if (pass == 0) {
        if (colidx[c - 1] < colidx[c]) {
          if (r[ridx] < rowidx[colidx[c - 1] - 1]) {
            low_i = colidx[c - 1] - 1;
            thisv = false;
          } else {
            nrow = colidx[c];
            low_i = colidx[c - 1];
            low_ip1 = colidx[c - 1];
            while (nrow > low_ip1 + 1) {
              mid_i = (low_i >> 1) + (nrow >> 1);
              if (((static_cast<unsigned int>(low_i) & 1U) == 1U) &&
                  ((static_cast<unsigned int>(nrow) & 1U) == 1U)) {
                mid_i++;
              }
              if (r[ridx] >= rowidx[mid_i - 1]) {
                low_i = mid_i;
                low_ip1 = mid_i;
              } else {
                nrow = mid_i;
              }
            }
            thisv = (rowidx[low_i - 1] == r[ridx]);
          }
        } else if (colidx[c - 1] == colidx[c]) {
          low_i = colidx[c - 1] - 1;
          thisv = false;
        } else {
          low_i = 0;
          thisv = false;
        }
        vidx = low_i - 1;
        if (thisv) {
          thisv = d[low_i - 1];
        } else {
          thisv = false;
        }
        if ((colidx[c] - low_i > 1) ||
            ((colidx[c] - low_i == 1) && (r[ridx] != m))) {
          if (colidx[c] - low_i > 1) {
            nrow = rowidx[low_i];
          } else {
            nrow = m + 1;
          }
          if ((ridx + 2 <= sm) && (sm > 2147483646)) {
            check_forloop_overflow_error();
          }
          low_ip1 = ridx + 1;
          while ((low_ip1 + 1 <= sm) && (r[low_ip1] < nrow)) {
            pass++;
            low_ip1++;
          }
        }
        extraAlloc = pass;
        shiftleft = 0;
        if (!thisv) {
          if (colidx[colidx.size(0) - 1] + pass > maxnz) {
            if (pass + 1 < 10) {
              nrow = 9;
            } else {
              nrow = pass;
            }
            sparse::b_realloc(this, colidx[colidx.size(0) - 1] + nrow, low_i,
                              low_i + 1, colidx[colidx.size(0) - 1] - 1,
                              pass + 1);
          } else {
            nrow = (low_i + pass) + 1;
            low_ip1 = (colidx[colidx.size(0) - 1] - low_i) - 1;
            if (low_ip1 > 0) {
              std::memmove((void *)&rowidx[nrow], (void *)&rowidx[low_i],
                           (unsigned int)((size_t)low_ip1 * sizeof(int)));
              std::memmove((void *)&d[nrow], (void *)&d[low_i],
                           (unsigned int)((size_t)low_ip1 * sizeof(boolean_T)));
            }
          }
          extraAlloc = pass + 1;
          vidx = low_i;
          guard2 = true;
        } else {
          if ((colidx[colidx.size(0) - 1] + pass) - 1 > maxnz) {
            if (pass < 10) {
              nrow = 10;
            } else {
              nrow = pass;
            }
            sparse::b_realloc(this, (colidx[colidx.size(0) - 1] + nrow) - 1,
                              low_i, low_i + 1, colidx[colidx.size(0) - 1] - 1,
                              pass);
          } else {
            nrow = low_i + pass;
            low_ip1 = (colidx[colidx.size(0) - 1] - low_i) - 1;
            if (low_ip1 > 0) {
              std::memmove((void *)&rowidx[nrow], (void *)&rowidx[low_i],
                           (unsigned int)((size_t)low_ip1 * sizeof(int)));
              std::memmove((void *)&d[nrow], (void *)&d[low_i],
                           (unsigned int)((size_t)low_ip1 * sizeof(boolean_T)));
            }
          }
          guard1 = true;
        }
      } else {
        thisv = false;
        pass--;
        guard2 = true;
      }
      if (guard2) {
        if (!rhs[ridx]) {
          shiftleft++;
        } else {
          guard1 = true;
        }
      }
      if (guard1) {
        if (thisv && rhs[ridx]) {
          d[vidx] = true;
          vidx++;
        } else if (!thisv) {
          d[vidx] = rhs[ridx];
          rowidx[vidx] = r[ridx];
          vidx++;
        } else {
          shiftleft++;
        }
      }
      if (pass == 0) {
        low_ip1 = extraAlloc - shiftleft;
        if (low_ip1 > 0) {
          mid_i = c + 1;
          nrow = n + 1;
          if ((c + 1 <= nrow) && (nrow > 2147483646)) {
            check_forloop_overflow_error();
          }
          for (low_i = mid_i; low_i <= nrow; low_i++) {
            colidx[low_i - 1] = colidx[low_i - 1] + low_ip1;
          }
        } else if (low_ip1 < 0) {
          low_ip1 = shiftleft - extraAlloc;
          mid_i = c + 1;
          nrow = n + 1;
          if ((c + 1 <= n + 1) && (n + 1 > 2147483646)) {
            check_forloop_overflow_error();
          }
          for (low_i = mid_i; low_i <= nrow; low_i++) {
            colidx[low_i - 1] = colidx[low_i - 1] - low_ip1;
          }
        }
        if (shiftleft != 0) {
          nrow = vidx + shiftleft;
          low_ip1 = (colidx[colidx.size(0) - 1] - vidx) - 1;
          if (low_ip1 > 0) {
            std::memmove((void *)&rowidx[vidx], (void *)&rowidx[nrow],
                         (unsigned int)((size_t)low_ip1 * sizeof(int)));
            std::memmove((void *)&d[vidx], (void *)&d[nrow],
                         (unsigned int)((size_t)low_ip1 * sizeof(boolean_T)));
          }
        }
      }
    }
  }
}

//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
} // namespace coder
static void dc_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "The number of nonzeros must be at least as large as the number "
               "of elements specified by the first 3 arguments to sparse.";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void ec_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Sparse matrix sizes must be non-negative integers.";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void fc_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Unable to represent result of \'~\' because it contains too "
               "many nonzero elements.";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void ic_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream
      << "Subscript indices must either be real positive integers or logicals.";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void ob_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Index into matrix must be an integer.";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void pb_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Index into matrix is too large.";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void qb_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Index into matrix must be positive.";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void rc_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "In an assignment  A(:) = B, the number of elements in A and B "
               "must be the same.";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// Arguments    : const long i
//                const int i1
//                const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void rtErrorWithMessageID(const long i, const int i1,
                                 const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((((((outStream << "Array element ") << i)
      << " is out-of-bounds. Modify the index expression to access elements in "
         "the range ")
     << 1)
    << "-")
   << i1)
      << ".";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// Arguments    : const int i
//                const int i1
//                const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void rtErrorWithMessageID(const int i, const int i1,
                                 const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((((((outStream << "Array element ") << i)
      << " is out-of-bounds. Modify the index expression to access elements in "
         "the range ")
     << 1)
    << "-")
   << i1)
      << ".";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void sc_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Unable to perform assignment because the indices on the left "
               "side are not compatible with the size of the right side.";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void tc_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Number of elements exceeds maximum representable value.";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// Arguments    : const array<double, 1U> &s
//                array<int, 1U> &sint
// Return Type  : void
//
namespace coder {
void sparse::assertValidIndexArg(const array<double, 1U> &s,
                                 array<int, 1U> &sint)
{
  static rtRunTimeErrorInfo rc_emlrtRTEI{
      1652,                 // lineNo
      "assertValidIndexArg" // fName
  };
  static rtRunTimeErrorInfo sc_emlrtRTEI{
      1654,                 // lineNo
      "assertValidIndexArg" // fName
  };
  static rtRunTimeErrorInfo tc_emlrtRTEI{
      1656,                 // lineNo
      "assertValidIndexArg" // fName
  };
  int ns_tmp;
  ns_tmp = s.size(0);
  sint.set_size(s.size(0));
  if (s.size(0) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{0}; k < ns_tmp; k++) {
    if (!(std::floor(s[k]) == s[k])) {
      ob_rtErrorWithMessageID(rc_emlrtRTEI.fName, rc_emlrtRTEI.lineNo);
    }
    if (!(s[k] < 2.147483647E+9)) {
      pb_rtErrorWithMessageID(sc_emlrtRTEI.fName, sc_emlrtRTEI.lineNo);
    }
    if (!(s[k] > 0.0)) {
      qb_rtErrorWithMessageID(tc_emlrtRTEI.fName, tc_emlrtRTEI.lineNo);
    }
    sint[k] = static_cast<int>(s[k]);
  }
}

//
// Arguments    : const array<double, 2U> &a
//                array<double, 2U> &c
// Return Type  : void
//
void f_sparse::b_mtimes(const array<double, 2U> &a, array<double, 2U> &c) const
{
  int aoff;
  int i;
  int m_tmp;
  int n_tmp;
  if (a.size(1) != m) {
    sb_rtErrorWithMessageID(yb_emlrtRTEI.fName, yb_emlrtRTEI.lineNo);
  }
  m_tmp = a.size(0);
  n_tmp = n;
  c.set_size(a.size(0), n);
  aoff = a.size(0) * n;
  for (i = 0; i < aoff; i++) {
    c[i] = 0.0;
  }
  if ((a.size(1) != 0) && (a.size(0) != 0) && (n != 0) &&
      (colidx[colidx.size(0) - 1] - 1 != 0)) {
    if (a.size(0) == 1) {
      if (n > 2147483646) {
        check_forloop_overflow_error();
      }
      for (aoff = 0; aoff < n_tmp; aoff++) {
        double cd;
        int b_a;
        cd = 0.0;
        i = colidx[aoff + 1];
        b_a = colidx[aoff];
        if ((colidx[aoff] <= i - 1) && (i - 1 > 2147483646)) {
          check_forloop_overflow_error();
        }
        for (int cidx{b_a}; cidx < i; cidx++) {
          cd += static_cast<double>(d[cidx - 1]) * a[rowidx[cidx - 1] - 1];
        }
        c[aoff] = cd;
      }
    } else if (a.size(0) >= 4) {
      if (n > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int ccol{0}; ccol < n_tmp; ccol++) {
        int b_a;
        int coff;
        coff = ccol * c.size(0);
        i = colidx[ccol + 1];
        b_a = colidx[ccol];
        if ((colidx[ccol] <= i - 1) && (i - 1 > 2147483646)) {
          check_forloop_overflow_error();
        }
        for (int bp{b_a}; bp < i; bp++) {
          int aoff_tmp;
          int cidx;
          int mend;
          boolean_T bd;
          aoff_tmp = rowidx[bp - 1] - 1;
          aoff = aoff_tmp * a.size(0);
          bd = d[bp - 1];
          mend = (m_tmp / 4) << 2;
          if (mend > 2147483643) {
            check_forloop_overflow_error();
          }
          for (int crow{1}; crow <= mend; crow += 4) {
            int aidx_tmp;
            cidx = crow + coff;
            aidx_tmp = crow + aoff;
            c[cidx - 1] =
                c[cidx - 1] + a[aidx_tmp - 1] * static_cast<double>(bd);
            c[cidx] = c[cidx] + a[aidx_tmp] * static_cast<double>(bd);
            c[cidx + 1] =
                c[cidx + 1] + a[aidx_tmp + 1] * static_cast<double>(bd);
            c[cidx + 2] =
                c[cidx + 2] + a[aidx_tmp + 2] * static_cast<double>(bd);
          }
          cidx = mend + 1;
          if ((mend + 1 <= m_tmp) && (m_tmp > 2147483646)) {
            check_forloop_overflow_error();
          }
          for (int crow{cidx}; crow <= m_tmp; crow++) {
            aoff = (crow + coff) - 1;
            c[aoff] = c[aoff] + a[(crow + a.size(0) * aoff_tmp) - 1] *
                                    static_cast<double>(bd);
          }
        }
      }
    } else {
      if (n > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int ccol{0}; ccol < n_tmp; ccol++) {
        int b_a;
        i = colidx[ccol + 1];
        b_a = colidx[ccol];
        if ((colidx[ccol] <= i - 1) && (i - 1 > 2147483646)) {
          check_forloop_overflow_error();
        }
        for (int bp{b_a}; bp < i; bp++) {
          for (int crow{0}; crow < m_tmp; crow++) {
            c[crow + c.size(0) * ccol] =
                c[crow + c.size(0) * ccol] +
                a[crow + a.size(0) * (rowidx[bp - 1] - 1)] *
                    static_cast<double>(d[bp - 1]);
          }
        }
      }
    }
  }
}

//
// Arguments    : const array<double, 2U> &a
//                array<double, 2U> &c
// Return Type  : void
//
void sparse::b_mtimes(const array<double, 2U> &a, array<double, 2U> &c) const
{
  int aoff;
  int i;
  int m_tmp;
  int n_tmp;
  if (a.size(1) != m) {
    sb_rtErrorWithMessageID(yb_emlrtRTEI.fName, yb_emlrtRTEI.lineNo);
  }
  m_tmp = a.size(0);
  n_tmp = n;
  c.set_size(a.size(0), n);
  aoff = a.size(0) * n;
  for (i = 0; i < aoff; i++) {
    c[i] = 0.0;
  }
  if ((a.size(1) != 0) && (a.size(0) != 0) && (n != 0) &&
      (colidx[colidx.size(0) - 1] - 1 != 0)) {
    if (a.size(0) == 1) {
      if (n > 2147483646) {
        check_forloop_overflow_error();
      }
      for (aoff = 0; aoff < n_tmp; aoff++) {
        double bd;
        int b_a;
        bd = 0.0;
        i = colidx[aoff + 1];
        b_a = colidx[aoff];
        if ((colidx[aoff] <= i - 1) && (i - 1 > 2147483646)) {
          check_forloop_overflow_error();
        }
        for (int cidx{b_a}; cidx < i; cidx++) {
          bd += d[cidx - 1] * a[rowidx[cidx - 1] - 1];
        }
        c[aoff] = bd;
      }
    } else if (a.size(0) >= 4) {
      if (n > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int ccol{0}; ccol < n_tmp; ccol++) {
        int b_a;
        int coff;
        coff = ccol * c.size(0);
        i = colidx[ccol + 1];
        b_a = colidx[ccol];
        if ((colidx[ccol] <= i - 1) && (i - 1 > 2147483646)) {
          check_forloop_overflow_error();
        }
        for (int bp{b_a}; bp < i; bp++) {
          double bd;
          int aoff_tmp;
          int cidx;
          int mend;
          aoff_tmp = rowidx[bp - 1] - 1;
          aoff = aoff_tmp * a.size(0);
          bd = d[bp - 1];
          mend = (m_tmp / 4) << 2;
          if (mend > 2147483643) {
            check_forloop_overflow_error();
          }
          for (int crow{1}; crow <= mend; crow += 4) {
            int aidx_tmp;
            cidx = crow + coff;
            aidx_tmp = crow + aoff;
            c[cidx - 1] = c[cidx - 1] + a[aidx_tmp - 1] * bd;
            c[cidx] = c[cidx] + a[aidx_tmp] * bd;
            c[cidx + 1] = c[cidx + 1] + a[aidx_tmp + 1] * bd;
            c[cidx + 2] = c[cidx + 2] + a[aidx_tmp + 2] * bd;
          }
          cidx = mend + 1;
          if ((mend + 1 <= m_tmp) && (m_tmp > 2147483646)) {
            check_forloop_overflow_error();
          }
          for (int crow{cidx}; crow <= m_tmp; crow++) {
            aoff = (crow + coff) - 1;
            c[aoff] = c[aoff] + a[(crow + a.size(0) * aoff_tmp) - 1] * bd;
          }
        }
      }
    } else {
      if (n > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int ccol{0}; ccol < n_tmp; ccol++) {
        int b_a;
        i = colidx[ccol + 1];
        b_a = colidx[ccol];
        if ((colidx[ccol] <= i - 1) && (i - 1 > 2147483646)) {
          check_forloop_overflow_error();
        }
        for (int bp{b_a}; bp < i; bp++) {
          for (int crow{0}; crow < m_tmp; crow++) {
            c[crow + c.size(0) * ccol] =
                c[crow + c.size(0) * ccol] +
                a[crow + a.size(0) * (rowidx[bp - 1] - 1)] * d[bp - 1];
          }
        }
      }
    }
  }
}

//
// Arguments    : d_sparse &out
// Return Type  : void
//
void d_sparse::b_not(d_sparse &out) const
{
  static rtRunTimeErrorInfo rc_emlrtRTEI{
      83,      // lineNo
      "notnnz" // fName
  };
  int b;
  int curPosition;
  int larger;
  int nzmax;
  if (n < 1) {
    larger = 0;
  } else {
    larger = (n - colidx[colidx.size(0) - 1]) + 1;
    if (larger == 0) {
      larger = 0;
    } else if (div_s32(MAX_int32_T, larger) < 1) {
      fc_rtErrorWithMessageID(rc_emlrtRTEI.fName, rc_emlrtRTEI.lineNo);
    }
  }
  nzmax = larger;
  out.n = n;
  if (larger < 1) {
    nzmax = 1;
  }
  out.d.set_size(nzmax);
  out.rowidx.set_size(nzmax);
  if (n + 1 < 0) {
    rtNonNegativeError(static_cast<double>(n + 1), m_emlrtDCI);
  }
  out.colidx.set_size(n + 1);
  if (larger < 1) {
    larger = 0;
  }
  for (nzmax = 0; nzmax < larger; nzmax++) {
    out.d[nzmax] = true;
  }
  curPosition = 1;
  b = n;
  if (n > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int c{0}; c < b; c++) {
    out.colidx[c] = curPosition;
    nzmax = colidx[c + 1];
    if (colidx[c] == nzmax) {
      out.rowidx[curPosition - 1] = 1;
      curPosition++;
    } else {
      if (rowidx[colidx[c] - 1] - 1 > 2147483646) {
        check_forloop_overflow_error();
      }
      larger = (nzmax - colidx[c]) - 2;
      for (int i{0}; i <= larger; i++) {
        int b_b;
        nzmax = colidx[c] + i;
        b_b = rowidx[nzmax] - 1;
        if ((rowidx[nzmax - 1] + 1 <= b_b) && (b_b > 2147483646)) {
          check_forloop_overflow_error();
        }
      }
      larger = rowidx[colidx[c] + larger] + 1;
      for (nzmax = larger; nzmax < 2; nzmax++) {
        out.rowidx[((curPosition + nzmax) - larger) - 1] = 1;
      }
      if (larger <= 1) {
        curPosition = (curPosition - larger) + 2;
      }
    }
  }
  out.colidx[n] = curPosition;
}

//
// Arguments    : const array<boolean_T, 2U> &rhs
//                const array<double, 2U> &varargin_1
// Return Type  : void
//
void f_sparse::b_parenAssign(const array<boolean_T, 2U> &rhs,
                             const array<double, 2U> &varargin_1)
{
  array<double, 2U> y;
  array<int, 2U> iidx;
  array<int, 1U> b_rowsToAssign;
  array<int, 1U> rowsToAssign;
  array<boolean_T, 2U> b_rhs;
  array<boolean_T, 1U> rhsv;
  int cnt;
  int col;
  int i;
  int lb;
  int overflow;
  int prevcol;
  internal::bigProduct(m, n, overflow);
  if (rhs.size(1) != varargin_1.size(1)) {
    rc_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
  }
  if (overflow == 0) {
    cnt = m * n;
    i = varargin_1.size(1);
    for (int k{0}; k < i; k++) {
      double b_d;
      double d1;
      b_d = varargin_1[k];
      d1 = std::floor(b_d);
      if ((!(d1 == b_d)) || std::isinf(b_d)) {
        ic_rtErrorWithMessageID(hc_emlrtRTEI.fName, hc_emlrtRTEI.lineNo);
      }
      if (!(b_d <= cnt)) {
        rtErrorWithMessageID(static_cast<long>(d1), cnt, bc_emlrtRTEI.fName,
                             bc_emlrtRTEI.lineNo);
      }
    }
  } else {
    i = varargin_1.size(1);
    for (int k{0}; k < i; k++) {
      double b_d;
      b_d = varargin_1[k];
      if ((!(std::floor(b_d) == b_d)) || std::isinf(b_d)) {
        ic_rtErrorWithMessageID(hc_emlrtRTEI.fName, hc_emlrtRTEI.lineNo);
      }
    }
  }
  overflow = varargin_1.size(1);
  y.set_size(1, varargin_1.size(1));
  for (i = 0; i < overflow; i++) {
    y[i] = varargin_1[i];
  }
  overflow = rhs.size(1);
  b_rhs.set_size(1, rhs.size(1));
  for (i = 0; i < overflow; i++) {
    b_rhs[i] = rhs[i];
  }
  if (!issorted(varargin_1)) {
    internal::sort(y, iidx);
    if (y.size(1) != 1) {
      i = y.size(1);
      for (int b_i{0}; b_i < i; b_i++) {
        b_rhs[b_i] = rhs[iidx[b_i] - 1];
      }
    }
  }
  lb = -1;
  cnt = 0;
  overflow = y.size(1);
  rowsToAssign.set_size(y.size(1));
  for (i = 0; i < overflow; i++) {
    rowsToAssign[i] = 0;
  }
  prevcol = 0;
  for (int k{0}; k <= overflow; k++) {
    if (static_cast<unsigned int>(k) + 1U <=
        static_cast<unsigned int>(y.size(1))) {
      double b_this[2];
      b_this[0] = m;
      b_this[1] = n;
      rowsToAssign[k] = internal::ind2sub(b_this, y[k], col);
    } else {
      col = -1;
    }
    if (col == prevcol) {
      cnt++;
    } else {
      if (cnt > 0) {
        int iv[2];
        rhsv.set_size(cnt);
        for (i = 0; i < cnt; i++) {
          rhsv[i] = false;
        }
        if (cnt > 2147483646) {
          check_forloop_overflow_error();
        }
        for (int b_i{0}; b_i < cnt; b_i++) {
          rhsv[b_i] = b_rhs[lb + b_i];
        }
        i = lb + cnt;
        if (lb + 1 > i) {
          lb = 0;
          i = 0;
        }
        iv[0] = 1;
        cnt = i - lb;
        iv[1] = cnt;
        internal::indexShapeCheck(rowsToAssign.size(0), iv);
        b_rowsToAssign.set_size(cnt);
        for (i = 0; i < cnt; i++) {
          b_rowsToAssign[i] = rowsToAssign[lb + i];
        }
        parenAssign2D(rhsv, b_rowsToAssign, prevcol);
      }
      lb = k;
      cnt = 1;
      prevcol = col;
    }
  }
}

//
// Arguments    : d_sparse &s
// Return Type  : void
//
void b_sparse::c_le(d_sparse &s) const
{
  array<boolean_T, 2U> S;
  int a;
  int loop_ub_tmp;
  S.set_size(1, n);
  loop_ub_tmp = n;
  for (a = 0; a < loop_ub_tmp; a++) {
    S[a] = true;
  }
  if (n > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int col{0}; col < loop_ub_tmp; col++) {
    int b_tmp;
    a = colidx[col];
    b_tmp = colidx[col + 1];
    if ((colidx[col] <= b_tmp - 1) && (b_tmp - 1 > 2147483646)) {
      check_forloop_overflow_error();
    }
    for (int idx{a}; idx < b_tmp; idx++) {
      S[col] = (d[idx - 1] <= 0.0);
    }
  }
  j_sparse(S, s);
}

//
// Arguments    : const h_sparse &rhs
//                const array<double, 2U> &varargin_1
// Return Type  : void
//
void f_sparse::c_parenAssign(const h_sparse &rhs,
                             const array<double, 2U> &varargin_1)
{
  array<double, 2U> y;
  array<int, 2U> iidx;
  array<int, 1U> b_rowsToAssign;
  array<int, 1U> rowsToAssign;
  array<boolean_T, 1U> b_rhs;
  array<boolean_T, 1U> temp;
  int cend;
  int col;
  int i;
  int lb;
  int partialResults_idx_2;
  int prevcol;
  internal::bigProduct(m, n, prevcol);
  cend = static_cast<int>(static_cast<unsigned int>(rhs.m) & 65535U);
  partialResults_idx_2 = (rhs.m >> 16) << 16;
  lb = 0;
  if (cend > MAX_int32_T - partialResults_idx_2) {
    cend = (cend + partialResults_idx_2) - MAX_int32_T;
    lb = 1;
  } else {
    cend += partialResults_idx_2;
  }
  if ((static_cast<int>(static_cast<unsigned int>(varargin_1.size(1)) &
                        65535U) +
           ((varargin_1.size(1) >> 16) << 16) !=
       cend) ||
      (lb != 0)) {
    rc_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
  }
  if (prevcol == 0) {
    cend = m * n;
    i = varargin_1.size(1);
    for (int k{0}; k < i; k++) {
      double b_d;
      double d1;
      b_d = varargin_1[k];
      d1 = std::floor(b_d);
      if ((!(d1 == b_d)) || std::isinf(b_d)) {
        ic_rtErrorWithMessageID(hc_emlrtRTEI.fName, hc_emlrtRTEI.lineNo);
      }
      if (!(b_d <= cend)) {
        rtErrorWithMessageID(static_cast<long>(d1), cend, bc_emlrtRTEI.fName,
                             bc_emlrtRTEI.lineNo);
      }
    }
  } else {
    i = varargin_1.size(1);
    for (int k{0}; k < i; k++) {
      double b_d;
      b_d = varargin_1[k];
      if ((!(std::floor(b_d) == b_d)) || std::isinf(b_d)) {
        ic_rtErrorWithMessageID(hc_emlrtRTEI.fName, hc_emlrtRTEI.lineNo);
      }
    }
  }
  cend = varargin_1.size(1);
  y.set_size(1, varargin_1.size(1));
  for (i = 0; i < cend; i++) {
    y[i] = varargin_1[i];
  }
  b_rhs.set_size(rhs.m);
  lb = rhs.m;
  for (i = 0; i < lb; i++) {
    b_rhs[i] = false;
  }
  cend = rhs.colidx[1];
  partialResults_idx_2 = rhs.colidx[0];
  if ((rhs.colidx[0] <= rhs.colidx[1] - 1) &&
      (rhs.colidx[1] - 1 > 2147483646)) {
    check_forloop_overflow_error();
  }
  for (prevcol = partialResults_idx_2; prevcol < cend; prevcol++) {
    b_rhs[rhs.rowidx[prevcol - 1] - 1] = rhs.d[prevcol - 1];
  }
  if (!issorted(varargin_1)) {
    internal::sort(y, iidx);
    temp.set_size(rhs.m);
    for (i = 0; i < lb; i++) {
      temp[i] = b_rhs[i];
    }
    if (y.size(1) != 1) {
      i = y.size(1);
      for (int b_i{0}; b_i < i; b_i++) {
        b_rhs[b_i] = temp[iidx[b_i] - 1];
      }
    }
  }
  lb = -1;
  partialResults_idx_2 = 0;
  cend = y.size(1);
  rowsToAssign.set_size(y.size(1));
  for (i = 0; i < cend; i++) {
    rowsToAssign[i] = 0;
  }
  prevcol = 0;
  for (int k{0}; k <= cend; k++) {
    if (static_cast<unsigned int>(k) + 1U <=
        static_cast<unsigned int>(y.size(1))) {
      double b_this[2];
      b_this[0] = m;
      b_this[1] = n;
      rowsToAssign[k] = internal::ind2sub(b_this, y[k], col);
    } else {
      col = -1;
    }
    if (col == prevcol) {
      partialResults_idx_2++;
    } else {
      if (partialResults_idx_2 > 0) {
        int c_rhs[2];
        temp.set_size(partialResults_idx_2);
        for (i = 0; i < partialResults_idx_2; i++) {
          temp[i] = false;
        }
        if (partialResults_idx_2 > 2147483646) {
          check_forloop_overflow_error();
        }
        for (int b_i{0}; b_i < partialResults_idx_2; b_i++) {
          temp[b_i] = b_rhs[lb + b_i];
        }
        i = lb + partialResults_idx_2;
        if (lb + 1 > i) {
          lb = 0;
          i = 0;
        }
        c_rhs[0] = 1;
        partialResults_idx_2 = i - lb;
        c_rhs[1] = partialResults_idx_2;
        internal::indexShapeCheck(rowsToAssign.size(0), c_rhs);
        b_rowsToAssign.set_size(partialResults_idx_2);
        for (i = 0; i < partialResults_idx_2; i++) {
          b_rowsToAssign[i] = rowsToAssign[lb + i];
        }
        parenAssign2D(temp, b_rowsToAssign, prevcol);
      }
      lb = k;
      partialResults_idx_2 = 1;
      prevcol = col;
    }
  }
}

//
// Arguments    : const array<double, 2U> &rhs
//                const array<double, 2U> &varargin_1
// Return Type  : void
//
void f_sparse::c_parenAssign(const array<double, 2U> &rhs,
                             const array<double, 2U> &varargin_1)
{
  array<double, 2U> b_rhs;
  array<double, 2U> y;
  array<int, 2U> iidx;
  array<int, 1U> b_rowsToAssign;
  array<int, 1U> rowsToAssign;
  array<boolean_T, 1U> rhsv;
  int cnt;
  int col;
  int i;
  int lb;
  int overflow;
  int prevcol;
  internal::bigProduct(m, n, overflow);
  if (rhs.size(1) != varargin_1.size(1)) {
    rc_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
  }
  if (overflow == 0) {
    cnt = m * n;
    i = varargin_1.size(1);
    for (int k{0}; k < i; k++) {
      double b_d;
      double d1;
      b_d = varargin_1[k];
      d1 = std::floor(b_d);
      if ((!(d1 == b_d)) || std::isinf(b_d)) {
        ic_rtErrorWithMessageID(hc_emlrtRTEI.fName, hc_emlrtRTEI.lineNo);
      }
      if (!(b_d <= cnt)) {
        rtErrorWithMessageID(static_cast<long>(d1), cnt, bc_emlrtRTEI.fName,
                             bc_emlrtRTEI.lineNo);
      }
    }
  } else {
    i = varargin_1.size(1);
    for (int k{0}; k < i; k++) {
      double b_d;
      b_d = varargin_1[k];
      if ((!(std::floor(b_d) == b_d)) || std::isinf(b_d)) {
        ic_rtErrorWithMessageID(hc_emlrtRTEI.fName, hc_emlrtRTEI.lineNo);
      }
    }
  }
  overflow = varargin_1.size(1);
  y.set_size(1, varargin_1.size(1));
  for (i = 0; i < overflow; i++) {
    y[i] = varargin_1[i];
  }
  overflow = rhs.size(1);
  b_rhs.set_size(1, rhs.size(1));
  for (i = 0; i < overflow; i++) {
    b_rhs[i] = rhs[i];
  }
  if (!issorted(varargin_1)) {
    internal::sort(y, iidx);
    if (y.size(1) != 1) {
      i = y.size(1);
      for (int b_i{0}; b_i < i; b_i++) {
        b_rhs[b_i] = rhs[iidx[b_i] - 1];
      }
    }
  }
  lb = -1;
  cnt = 0;
  overflow = y.size(1);
  rowsToAssign.set_size(y.size(1));
  for (i = 0; i < overflow; i++) {
    rowsToAssign[i] = 0;
  }
  prevcol = 0;
  for (int k{0}; k <= overflow; k++) {
    if (static_cast<unsigned int>(k) + 1U <=
        static_cast<unsigned int>(y.size(1))) {
      double b_this[2];
      b_this[0] = m;
      b_this[1] = n;
      rowsToAssign[k] = internal::ind2sub(b_this, y[k], col);
    } else {
      col = -1;
    }
    if (col == prevcol) {
      cnt++;
    } else {
      if (cnt > 0) {
        int iv[2];
        rhsv.set_size(cnt);
        for (i = 0; i < cnt; i++) {
          rhsv[i] = false;
        }
        if (cnt > 2147483646) {
          check_forloop_overflow_error();
        }
        for (int b_i{0}; b_i < cnt; b_i++) {
          rhsv[b_i] = (b_rhs[lb + b_i] != 0.0);
        }
        i = lb + cnt;
        if (lb + 1 > i) {
          lb = 0;
          i = 0;
        }
        iv[0] = 1;
        cnt = i - lb;
        iv[1] = cnt;
        internal::indexShapeCheck(rowsToAssign.size(0), iv);
        b_rowsToAssign.set_size(cnt);
        for (i = 0; i < cnt; i++) {
          b_rowsToAssign[i] = rowsToAssign[lb + i];
        }
        parenAssign2D(rhsv, b_rowsToAssign, prevcol);
      }
      lb = k;
      cnt = 1;
      prevcol = col;
    }
  }
}

//
// Arguments    : const c_sparse &b
//                d_sparse &s
// Return Type  : void
//
void b_sparse::eq(const c_sparse &b, d_sparse &s) const
{
  static rtRunTimeErrorInfo rc_emlrtRTEI{
      460,               // lineNo
      "sparse/spfunImpl" // fName
  };
  static rtRunTimeErrorInfo sc_emlrtRTEI{
      178,            // lineNo
      "sparse/sparse" // fName
  };
  d_anonymous_function uniOp;
  array<boolean_T, 2U> S;
  array<boolean_T, 1U> tmpd;
  if (b.colidx[b.colidx.size(0) - 1] - 1 > 0) {
    uniOp.workspace.sb = b.d[0];
  } else {
    uniOp.workspace.sb = 0.0;
  }
  if (!(uniOp.workspace.sb == 0.0)) {
    int col;
    int currRowIdx;
    int i;
    int idx;
    int loop_ub_tmp;
    int numalloc;
    int nzs_tmp_tmp;
    boolean_T val;
    nzs_tmp_tmp = colidx[colidx.size(0) - 1];
    if (nzs_tmp_tmp - 1 < 1) {
      col = 0;
    } else {
      col = nzs_tmp_tmp - 1;
    }
    tmpd.set_size(col);
    for (i = 0; i < col; i++) {
      tmpd[i] = (d[i] == uniOp.workspace.sb);
    }
    if (tmpd.size(0) != nzs_tmp_tmp - 1) {
      nb_rtErrorWithMessageID(rc_emlrtRTEI.fName, rc_emlrtRTEI.lineNo);
    }
    if (n < 0) {
      ec_rtErrorWithMessageID(dc_emlrtRTEI.fName, dc_emlrtRTEI.lineNo);
    }
    if (n >= MAX_int32_T) {
      wc_rtErrorWithMessageID(cc_emlrtRTEI.fName, cc_emlrtRTEI.lineNo);
    }
    s.n = n;
    if (nzs_tmp_tmp - 1 < 0) {
      ec_rtErrorWithMessageID(dc_emlrtRTEI.fName, dc_emlrtRTEI.lineNo);
    }
    if (nzs_tmp_tmp - 1 >= MAX_int32_T) {
      wc_rtErrorWithMessageID(cc_emlrtRTEI.fName, cc_emlrtRTEI.lineNo);
    }
    if (nzs_tmp_tmp - 1 < 0) {
      dc_rtErrorWithMessageID(sc_emlrtRTEI.fName, sc_emlrtRTEI.lineNo);
    }
    if (nzs_tmp_tmp - 1 >= 1) {
      numalloc = nzs_tmp_tmp - 2;
    } else {
      numalloc = 0;
    }
    s.d.set_size(numalloc + 1);
    for (i = 0; i <= numalloc; i++) {
      s.d[i] = false;
    }
    i = n + 1;
    s.colidx.set_size(i);
    loop_ub_tmp = n;
    for (currRowIdx = 0; currRowIdx <= loop_ub_tmp; currRowIdx++) {
      s.colidx[currRowIdx] = 0;
    }
    s.colidx[0] = 1;
    s.rowidx.set_size(numalloc + 1);
    for (currRowIdx = 0; currRowIdx <= numalloc; currRowIdx++) {
      s.rowidx[currRowIdx] = 0;
    }
    for (int c{0}; c < loop_ub_tmp; c++) {
      s.colidx[c + 1] = 1;
    }
    idx = 0;
    for (int c{0}; c <= i - 2; c++) {
      numalloc = s.colidx[c];
      s.colidx[c] = idx + 1;
      while (numalloc < s.colidx[c + 1]) {
        val = false;
        while (numalloc < s.colidx[c + 1]) {
          if (val || s.d[numalloc - 1]) {
            val = true;
          }
          numalloc++;
        }
        if (val) {
          s.d[idx] = true;
          s.rowidx[idx] = 0;
          idx++;
        }
      }
    }
    if (nzs_tmp_tmp - 1 < 1) {
      col = 1;
    } else {
      col = nzs_tmp_tmp;
    }
    for (i = 0; i <= col - 2; i++) {
      s.rowidx[i] = rowidx[i];
    }
    col = colidx.size(0);
    s.colidx.set_size(colidx.size(0));
    for (i = 0; i < col; i++) {
      s.colidx[i] = colidx[i];
    }
    if (nzs_tmp_tmp - 1 > 2147483646) {
      check_forloop_overflow_error();
    }
    for (numalloc = 0; numalloc <= nzs_tmp_tmp - 2; numalloc++) {
      s.d[numalloc] = tmpd[numalloc];
    }
    idx = 1;
    for (int c{0}; c <= col - 2; c++) {
      numalloc = s.colidx[c];
      s.colidx[c] = idx;
      while (numalloc < s.colidx[c + 1]) {
        currRowIdx = s.rowidx[numalloc - 1];
        val = s.d[numalloc - 1];
        numalloc++;
        if (val) {
          s.d[idx - 1] = true;
          s.rowidx[idx - 1] = currRowIdx;
          idx++;
        }
      }
    }
    s.colidx[colidx.size(0) - 1] = idx;
  } else {
    int loop_ub_tmp;
    S.set_size(1, n);
    loop_ub_tmp = n;
    for (int i{0}; i < loop_ub_tmp; i++) {
      S[i] = true;
    }
    if (n > 2147483646) {
      check_forloop_overflow_error();
    }
    for (int col{0}; col < loop_ub_tmp; col++) {
      int currRowIdx;
      int numalloc;
      numalloc = colidx[col];
      currRowIdx = colidx[col + 1];
      if ((colidx[col] <= currRowIdx - 1) && (currRowIdx - 1 > 2147483646)) {
        check_forloop_overflow_error();
      }
      for (int idx{numalloc}; idx < currRowIdx; idx++) {
        S[col] = (d[idx - 1] == uniOp.workspace.sb);
      }
    }
    j_sparse(S, s);
  }
}

//
// Arguments    : int ndiag
//                int b_m
//                int b_n
//                sparse &b_I
// Return Type  : void
//
void sparse::eyeLike(int ndiag, int b_m, int b_n, sparse &b_I)
{
  int b;
  int nzmax;
  b_I.m = b_m;
  nzmax = ndiag;
  b_I.n = b_n;
  if (ndiag < 1) {
    nzmax = 1;
  }
  b_I.maxnz = nzmax;
  b_I.d.set_size(nzmax);
  b_I.rowidx.set_size(nzmax);
  if (b_n + 1 < 0) {
    rtNonNegativeError(static_cast<double>(b_n + 1), m_emlrtDCI);
  }
  b_I.colidx.set_size(b_n + 1);
  if (ndiag > 2147483646) {
    check_forloop_overflow_error();
  }
  for (nzmax = 0; nzmax < ndiag; nzmax++) {
    b_I.d[nzmax] = 1.0;
    b_I.rowidx[nzmax] = nzmax + 1;
  }
  b_I.colidx[0] = 1;
  for (int c{2}; c <= ndiag; c++) {
    b_I.colidx[c - 1] = c;
  }
  nzmax = ndiag + 1;
  b = b_n + 1;
  if ((ndiag + 1 <= b_n + 1) && (b_n + 1 > 2147483646)) {
    check_forloop_overflow_error();
  }
  for (int c{nzmax}; c <= b; c++) {
    b_I.colidx[c - 1] = ndiag + 1;
  }
}

//
// Arguments    : void
// Return Type  : void
//
void sparse::fillIn()
{
  int i;
  int idx;
  idx = 1;
  i = colidx.size(0);
  for (int c{0}; c <= i - 2; c++) {
    int ridx;
    ridx = colidx[c];
    colidx[c] = idx;
    while (ridx < colidx[c + 1]) {
      double val;
      int currRowIdx;
      val = 0.0;
      currRowIdx = rowidx[ridx - 1];
      while ((ridx < colidx[c + 1]) && (rowidx[ridx - 1] == currRowIdx)) {
        val += d[ridx - 1];
        ridx++;
      }
      if (val != 0.0) {
        d[idx - 1] = val;
        rowidx[idx - 1] = currRowIdx;
        idx++;
      }
    }
  }
  colidx[colidx.size(0) - 1] = idx;
}

//
// Arguments    : array<boolean_T, 2U> &y
// Return Type  : void
//
void d_sparse::full(array<boolean_T, 2U> &y) const
{
  int i;
  int loop_ub_tmp;
  y.set_size(1, n);
  loop_ub_tmp = n;
  for (i = 0; i < loop_ub_tmp; i++) {
    y[i] = false;
  }
  if (n > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int c{0}; c < loop_ub_tmp; c++) {
    int a;
    i = colidx[c + 1];
    a = colidx[c];
    if ((colidx[c] <= i - 1) && (i - 1 > 2147483646)) {
      check_forloop_overflow_error();
    }
    for (int idx{a}; idx < i; idx++) {
      y[c] = d[idx - 1];
    }
  }
}

//
// Arguments    : void
// Return Type  : double
//
double c_sparse::full() const
{
  double y;
  int a;
  int cend;
  y = 0.0;
  cend = colidx[1];
  a = colidx[0];
  if ((colidx[0] <= colidx[1] - 1) && (colidx[1] - 1 > 2147483646)) {
    check_forloop_overflow_error();
  }
  for (int idx{a}; idx < cend; idx++) {
    y = d[0];
  }
  return y;
}

//
// Arguments    : void
// Return Type  : boolean_T
//
boolean_T e_sparse::full() const
{
  int a;
  int cend;
  boolean_T y;
  y = false;
  cend = colidx[1];
  a = colidx[0];
  if ((colidx[0] <= colidx[1] - 1) && (colidx[1] - 1 > 2147483646)) {
    check_forloop_overflow_error();
  }
  for (int idx{a}; idx < cend; idx++) {
    y = d[idx - 1];
  }
  return y;
}

//
// Arguments    : f_sparse &y
// Return Type  : void
//
void sparse::logical(f_sparse &y) const
{
  int i;
  int numalloc;
  int ridx;
  if (m < 0) {
    ec_rtErrorWithMessageID(dc_emlrtRTEI.fName, dc_emlrtRTEI.lineNo);
  }
  if (m >= MAX_int32_T) {
    wc_rtErrorWithMessageID(cc_emlrtRTEI.fName, cc_emlrtRTEI.lineNo);
  }
  if (n < 0) {
    ec_rtErrorWithMessageID(dc_emlrtRTEI.fName, dc_emlrtRTEI.lineNo);
  }
  if (n >= MAX_int32_T) {
    wc_rtErrorWithMessageID(cc_emlrtRTEI.fName, cc_emlrtRTEI.lineNo);
  }
  y.m = m;
  y.n = n;
  if (maxnz < 0) {
    ec_rtErrorWithMessageID(dc_emlrtRTEI.fName, dc_emlrtRTEI.lineNo);
  }
  if (maxnz >= MAX_int32_T) {
    wc_rtErrorWithMessageID(cc_emlrtRTEI.fName, cc_emlrtRTEI.lineNo);
  }
  numalloc = maxnz;
  if (numalloc < 1) {
    numalloc = 1;
  }
  y.d.set_size(numalloc);
  for (i = 0; i < numalloc; i++) {
    y.d[i] = false;
  }
  y.maxnz = numalloc;
  y.colidx.set_size(n + 1);
  numalloc = n;
  for (i = 0; i <= numalloc; i++) {
    y.colidx[i] = 0;
  }
  y.colidx[0] = 1;
  for (int c{0}; c < numalloc; c++) {
    y.colidx[c + 1] = 1;
  }
  numalloc = 1;
  i = y.colidx.size(0);
  for (int c{0}; c <= i - 2; c++) {
    ridx = y.colidx[c];
    y.colidx[c] = numalloc;
    while (ridx < y.colidx[c + 1]) {
      boolean_T val;
      val = false;
      while (ridx < y.colidx[c + 1]) {
        if (val || y.d[ridx - 1]) {
          val = true;
        }
        ridx++;
      }
      if (val) {
        y.d[numalloc - 1] = true;
        numalloc++;
      }
    }
  }
  numalloc = rowidx.size(0);
  y.rowidx.set_size(rowidx.size(0));
  for (i = 0; i < numalloc; i++) {
    y.rowidx[i] = rowidx[i];
  }
  numalloc = colidx.size(0);
  y.colidx.set_size(colidx.size(0));
  for (i = 0; i < numalloc; i++) {
    y.colidx[i] = colidx[i];
  }
  numalloc = colidx[colidx.size(0) - 1] - 1;
  if (numalloc < 1) {
    numalloc = 1;
  }
  for (ridx = 0; ridx < numalloc; ridx++) {
    if (std::isnan(d[ridx])) {
      y_rtErrorWithMessageID(hb_emlrtRTEI.fName, hb_emlrtRTEI.lineNo);
    }
  }
  for (i = 0; i < numalloc; i++) {
    y.d[i] = (d[i] != 0.0);
  }
}

//
// Arguments    : h_sparse &y
// Return Type  : void
//
void g_sparse::logical(h_sparse &y) const
{
  int numalloc;
  if (m < 0) {
    ec_rtErrorWithMessageID(dc_emlrtRTEI.fName, dc_emlrtRTEI.lineNo);
  }
  if (m >= MAX_int32_T) {
    wc_rtErrorWithMessageID(cc_emlrtRTEI.fName, cc_emlrtRTEI.lineNo);
  }
  y.m = m;
  if (maxnz < 0) {
    ec_rtErrorWithMessageID(dc_emlrtRTEI.fName, dc_emlrtRTEI.lineNo);
  }
  if (maxnz >= MAX_int32_T) {
    wc_rtErrorWithMessageID(cc_emlrtRTEI.fName, cc_emlrtRTEI.lineNo);
  }
  numalloc = maxnz;
  if (numalloc < 1) {
    numalloc = 1;
  }
  y.d.set_size(numalloc);
  for (int k{0}; k < numalloc; k++) {
    y.d[k] = false;
  }
  y.colidx.set_size(2);
  y.colidx[1] = 1;
  y.colidx[0] = 1;
  numalloc = rowidx.size(0);
  y.rowidx.set_size(rowidx.size(0));
  for (int k{0}; k < numalloc; k++) {
    y.rowidx[k] = rowidx[k];
  }
  numalloc = colidx.size(0);
  y.colidx.set_size(colidx.size(0));
  for (int k{0}; k < numalloc; k++) {
    y.colidx[k] = colidx[k];
  }
  numalloc = colidx[colidx.size(0) - 1] - 1;
  if (numalloc < 1) {
    numalloc = 1;
  }
  for (int k{0}; k < numalloc; k++) {
    if (std::isnan(d[k])) {
      y_rtErrorWithMessageID(hb_emlrtRTEI.fName, hb_emlrtRTEI.lineNo);
    }
  }
  for (int k{0}; k < numalloc; k++) {
    y.d[k] = (d[k] != 0.0);
  }
}

//
// Arguments    : const array<double, 2U> &b
//                array<double, 2U> &c
// Return Type  : void
//
void f_sparse::mtimes(const array<double, 2U> &b, array<double, 2U> &c) const
{
  int i;
  int n_tmp;
  int nap;
  if (n != b.size(0)) {
    sb_rtErrorWithMessageID(yb_emlrtRTEI.fName, yb_emlrtRTEI.lineNo);
  }
  n_tmp = b.size(1);
  c.set_size(m, b.size(1));
  nap = m * b.size(1);
  for (i = 0; i < nap; i++) {
    c[i] = 0.0;
  }
  if ((n != 0) && (m != 0) && (b.size(1) != 0) &&
      (colidx[colidx.size(0) - 1] - 1 != 0)) {
    if (b.size(1) == 1) {
      int b_b;
      b_b = n;
      if (n > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int acol{0}; acol < b_b; acol++) {
        double bc;
        int a;
        bc = b[acol];
        a = colidx[acol];
        i = colidx[acol + 1];
        nap = i - colidx[acol];
        if (nap >= 4) {
          int apend1;
          apend1 = ((i - nap) + ((nap / 4) << 2)) - 1;
          if ((colidx[acol] <= apend1) && (apend1 > 2147483643)) {
            check_forloop_overflow_error();
          }
          for (int ap{a}; ap <= apend1; ap += 4) {
            nap = rowidx[ap - 1] - 1;
            c[nap] = c[nap] + static_cast<double>(d[ap - 1]) * bc;
            c[rowidx[ap] - 1] =
                c[rowidx[ap] - 1] + static_cast<double>(d[ap]) * bc;
            nap = rowidx[ap + 1] - 1;
            c[nap] = c[nap] + static_cast<double>(d[ap + 1]) * bc;
            nap = rowidx[ap + 2] - 1;
            c[nap] = c[nap] + static_cast<double>(d[ap + 2]) * bc;
          }
          a = apend1 + 1;
          if ((apend1 + 1 <= i - 1) && (i - 1 > 2147483646)) {
            check_forloop_overflow_error();
          }
          for (int ap{a}; ap < i; ap++) {
            nap = rowidx[ap - 1] - 1;
            c[nap] = c[nap] + static_cast<double>(d[ap - 1]) * bc;
          }
        } else {
          if ((colidx[acol] <= i - 1) && (i - 1 > 2147483646)) {
            check_forloop_overflow_error();
          }
          for (int ap{a}; ap < i; ap++) {
            nap = rowidx[ap - 1] - 1;
            c[nap] = c[nap] + static_cast<double>(d[ap - 1]) * bc;
          }
        }
      }
    } else {
      int b_b;
      boolean_T overflow;
      if (b.size(1) > 2147483646) {
        check_forloop_overflow_error();
      }
      b_b = n;
      overflow = (n > 2147483646);
      for (int j{0}; j < n_tmp; j++) {
        int coff;
        coff = j * c.size(0) - 1;
        if (overflow) {
          check_forloop_overflow_error();
        }
        for (int acol{0}; acol < b_b; acol++) {
          double bc;
          int a;
          bc = b[acol + b.size(0) * j];
          a = colidx[acol];
          i = colidx[acol + 1];
          nap = i - colidx[acol];
          if (nap >= 4) {
            int apend1;
            apend1 = ((i - nap) + ((nap / 4) << 2)) - 1;
            if ((colidx[acol] <= apend1) && (apend1 > 2147483643)) {
              check_forloop_overflow_error();
            }
            for (int ap{a}; ap <= apend1; ap += 4) {
              nap = rowidx[ap - 1] + coff;
              c[nap] = c[nap] + static_cast<double>(d[ap - 1]) * bc;
              nap = rowidx[ap] + coff;
              c[nap] = c[nap] + static_cast<double>(d[ap]) * bc;
              nap = rowidx[ap + 1] + coff;
              c[nap] = c[nap] + static_cast<double>(d[ap + 1]) * bc;
              nap = rowidx[ap + 2] + coff;
              c[nap] = c[nap] + static_cast<double>(d[ap + 2]) * bc;
            }
            a = apend1 + 1;
            if ((apend1 + 1 <= i - 1) && (i - 1 > 2147483646)) {
              check_forloop_overflow_error();
            }
            for (int ap{a}; ap < i; ap++) {
              nap = rowidx[ap - 1] - 1;
              c[nap + c.size(0) * j] =
                  c[nap + c.size(0) * j] + static_cast<double>(d[ap - 1]) * bc;
            }
          } else {
            if ((colidx[acol] <= i - 1) && (i - 1 > 2147483646)) {
              check_forloop_overflow_error();
            }
            for (int ap{a}; ap < i; ap++) {
              nap = rowidx[ap - 1] + coff;
              c[nap] = c[nap] + static_cast<double>(d[ap - 1]) * bc;
            }
          }
        }
      }
    }
  }
}

//
// Arguments    : const array<double, 2U> &a
//                array<double, 2U> &c
// Return Type  : void
//
void sparse::mtimes(const array<double, 2U> &a, array<double, 2U> &c) const
{
  int aoff;
  int i;
  int m_tmp;
  int n_tmp;
  if (a.size(1) != m) {
    sb_rtErrorWithMessageID(yb_emlrtRTEI.fName, yb_emlrtRTEI.lineNo);
  }
  m_tmp = a.size(0);
  n_tmp = n;
  c.set_size(a.size(0), n);
  aoff = a.size(0) * n;
  for (i = 0; i < aoff; i++) {
    c[i] = 0.0;
  }
  if ((a.size(1) != 0) && (a.size(0) != 0) && (n != 0) &&
      (colidx[colidx.size(0) - 1] - 1 != 0)) {
    if (a.size(0) == 1) {
      if (n > 2147483646) {
        check_forloop_overflow_error();
      }
      for (aoff = 0; aoff < n_tmp; aoff++) {
        double cd;
        int b_a;
        cd = 0.0;
        i = colidx[aoff + 1];
        b_a = colidx[aoff];
        if ((colidx[aoff] <= i - 1) && (i - 1 > 2147483646)) {
          check_forloop_overflow_error();
        }
        for (int cidx{b_a}; cidx < i; cidx++) {
          cd += a[rowidx[cidx - 1] - 1];
        }
        c[aoff] = cd;
      }
    } else if (a.size(0) >= 4) {
      if (n > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int ccol{0}; ccol < n_tmp; ccol++) {
        int b_a;
        int coff;
        coff = ccol * c.size(0);
        i = colidx[ccol + 1];
        b_a = colidx[ccol];
        if ((colidx[ccol] <= i - 1) && (i - 1 > 2147483646)) {
          check_forloop_overflow_error();
        }
        for (int bp{b_a}; bp < i; bp++) {
          int aoff_tmp;
          int cidx;
          int mend;
          aoff_tmp = rowidx[bp - 1] - 1;
          aoff = aoff_tmp * a.size(0);
          mend = (m_tmp / 4) << 2;
          if (mend > 2147483643) {
            check_forloop_overflow_error();
          }
          for (int crow{1}; crow <= mend; crow += 4) {
            int aidx_tmp;
            cidx = crow + coff;
            aidx_tmp = crow + aoff;
            c[cidx - 1] = c[cidx - 1] + a[aidx_tmp - 1];
            c[cidx] = c[cidx] + a[aidx_tmp];
            c[cidx + 1] = c[cidx + 1] + a[aidx_tmp + 1];
            c[cidx + 2] = c[cidx + 2] + a[aidx_tmp + 2];
          }
          cidx = mend + 1;
          if ((mend + 1 <= m_tmp) && (m_tmp > 2147483646)) {
            check_forloop_overflow_error();
          }
          for (int crow{cidx}; crow <= m_tmp; crow++) {
            aoff = (crow + coff) - 1;
            c[aoff] = c[aoff] + a[(crow + a.size(0) * aoff_tmp) - 1];
          }
        }
      }
    } else {
      if (n > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int ccol{0}; ccol < n_tmp; ccol++) {
        int b_a;
        i = colidx[ccol + 1];
        b_a = colidx[ccol];
        if ((colidx[ccol] <= i - 1) && (i - 1 > 2147483646)) {
          check_forloop_overflow_error();
        }
        for (int bp{b_a}; bp < i; bp++) {
          for (int crow{0}; crow < m_tmp; crow++) {
            c[crow + c.size(0) * ccol] =
                c[crow + c.size(0) * ccol] +
                a[crow + a.size(0) * (rowidx[bp - 1] - 1)];
          }
        }
      }
    }
  }
}

//
// Arguments    : const array<boolean_T, 1U> &rhs
//                const array<double, 2U> &varargin_1
// Return Type  : void
//
void f_sparse::parenAssign(const array<boolean_T, 1U> &rhs,
                           const array<double, 2U> &varargin_1)
{
  array<double, 2U> y;
  array<int, 2U> iidx;
  array<int, 1U> b_rowsToAssign;
  array<int, 1U> rowsToAssign;
  array<boolean_T, 1U> b_rhs;
  array<boolean_T, 1U> rhsv;
  int cnt;
  int col;
  int i;
  int lb;
  int overflow;
  int prevcol;
  internal::bigProduct(m, n, overflow);
  if (rhs.size(0) != varargin_1.size(1)) {
    rc_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
  }
  if (overflow == 0) {
    cnt = m * n;
    i = varargin_1.size(1);
    for (int k{0}; k < i; k++) {
      double b_d;
      double d1;
      b_d = varargin_1[k];
      d1 = std::floor(b_d);
      if ((!(d1 == b_d)) || std::isinf(b_d)) {
        ic_rtErrorWithMessageID(hc_emlrtRTEI.fName, hc_emlrtRTEI.lineNo);
      }
      if (!(b_d <= cnt)) {
        rtErrorWithMessageID(static_cast<long>(d1), cnt, bc_emlrtRTEI.fName,
                             bc_emlrtRTEI.lineNo);
      }
    }
  } else {
    i = varargin_1.size(1);
    for (int k{0}; k < i; k++) {
      double b_d;
      b_d = varargin_1[k];
      if ((!(std::floor(b_d) == b_d)) || std::isinf(b_d)) {
        ic_rtErrorWithMessageID(hc_emlrtRTEI.fName, hc_emlrtRTEI.lineNo);
      }
    }
  }
  overflow = varargin_1.size(1);
  y.set_size(1, varargin_1.size(1));
  for (i = 0; i < overflow; i++) {
    y[i] = varargin_1[i];
  }
  overflow = rhs.size(0);
  b_rhs.set_size(rhs.size(0));
  for (i = 0; i < overflow; i++) {
    b_rhs[i] = rhs[i];
  }
  if (!issorted(varargin_1)) {
    internal::sort(y, iidx);
    if (y.size(1) != 1) {
      i = y.size(1);
      for (int b_i{0}; b_i < i; b_i++) {
        b_rhs[b_i] = rhs[iidx[b_i] - 1];
      }
    }
  }
  lb = -1;
  cnt = 0;
  overflow = y.size(1);
  rowsToAssign.set_size(y.size(1));
  for (i = 0; i < overflow; i++) {
    rowsToAssign[i] = 0;
  }
  prevcol = 0;
  for (int k{0}; k <= overflow; k++) {
    if (static_cast<unsigned int>(k) + 1U <=
        static_cast<unsigned int>(y.size(1))) {
      double b_this[2];
      b_this[0] = m;
      b_this[1] = n;
      rowsToAssign[k] = internal::ind2sub(b_this, y[k], col);
    } else {
      col = -1;
    }
    if (col == prevcol) {
      cnt++;
    } else {
      if (cnt > 0) {
        int iv[2];
        rhsv.set_size(cnt);
        for (i = 0; i < cnt; i++) {
          rhsv[i] = false;
        }
        if (cnt > 2147483646) {
          check_forloop_overflow_error();
        }
        for (int b_i{0}; b_i < cnt; b_i++) {
          rhsv[b_i] = b_rhs[lb + b_i];
        }
        i = lb + cnt;
        if (lb + 1 > i) {
          lb = 0;
          i = 0;
        }
        iv[0] = 1;
        cnt = i - lb;
        iv[1] = cnt;
        internal::indexShapeCheck(rowsToAssign.size(0), iv);
        b_rowsToAssign.set_size(cnt);
        for (i = 0; i < cnt; i++) {
          b_rowsToAssign[i] = rowsToAssign[lb + i];
        }
        parenAssign2D(rhsv, b_rowsToAssign, prevcol);
      }
      lb = k;
      cnt = 1;
      prevcol = col;
    }
  }
}

//
// Arguments    : const array<double, 1U> &varargin_2
//                sparse &s
// Return Type  : void
//
void sparse::parenReference(const array<double, 1U> &varargin_2,
                            sparse &s) const
{
  int i;
  int loop_ub;
  int nd;
  int nd_tmp;
  int ub;
  ub = n;
  loop_ub = varargin_2.size(0);
  for (int k{0}; k < loop_ub; k++) {
    double b_d;
    b_d = std::floor(varargin_2[k]);
    if ((!(b_d == varargin_2[k])) || std::isinf(varargin_2[k])) {
      ic_rtErrorWithMessageID(hc_emlrtRTEI.fName, hc_emlrtRTEI.lineNo);
    }
    if (!(varargin_2[k] <= ub)) {
      rtErrorWithMessageID(static_cast<long>(b_d), ub, bc_emlrtRTEI.fName,
                           bc_emlrtRTEI.lineNo);
    }
  }
  ub = m * varargin_2.size(0);
  nd = 0;
  if (varargin_2.size(0) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int cidx{0}; cidx < loop_ub; cidx++) {
    nd_tmp = static_cast<int>(varargin_2[cidx]);
    nd = (nd + colidx[nd_tmp]) - colidx[nd_tmp - 1];
  }
  if ((nd > ub) && (ub != 0)) {
    g_rtErrorWithMessageID(ic_emlrtRTEI.fName, ic_emlrtRTEI.lineNo);
  }
  if (m < 0) {
    ec_rtErrorWithMessageID(dc_emlrtRTEI.fName, dc_emlrtRTEI.lineNo);
  }
  if (m >= MAX_int32_T) {
    wc_rtErrorWithMessageID(cc_emlrtRTEI.fName, cc_emlrtRTEI.lineNo);
  }
  s.m = m;
  s.n = varargin_2.size(0);
  if (nd < 0) {
    ec_rtErrorWithMessageID(dc_emlrtRTEI.fName, dc_emlrtRTEI.lineNo);
  }
  if (nd >= MAX_int32_T) {
    wc_rtErrorWithMessageID(cc_emlrtRTEI.fName, cc_emlrtRTEI.lineNo);
  }
  if (nd >= 1) {
    ub = nd;
  } else {
    ub = 1;
  }
  s.d.set_size(ub);
  for (i = 0; i < ub; i++) {
    s.d[i] = 0.0;
  }
  s.maxnz = ub;
  s.colidx.set_size(varargin_2.size(0) + 1);
  for (i = 0; i <= loop_ub; i++) {
    s.colidx[i] = 0;
  }
  s.colidx[0] = 1;
  s.rowidx.set_size(ub);
  for (i = 0; i < ub; i++) {
    s.rowidx[i] = 0;
  }
  for (ub = 0; ub < loop_ub; ub++) {
    s.colidx[ub + 1] = 1;
  }
  s.fillIn();
  if (nd != 0) {
    nd = 0;
    for (int cidx{0}; cidx < loop_ub; cidx++) {
      int colstart_tmp;
      ub = static_cast<int>(varargin_2[cidx]);
      colstart_tmp = colidx[ub - 1];
      ub = colidx[ub] - colstart_tmp;
      if (ub > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int k{0}; k < ub; k++) {
        i = (colstart_tmp + k) - 1;
        nd_tmp = nd + k;
        s.d[nd_tmp] = d[i];
        s.rowidx[nd_tmp] = rowidx[i];
      }
      if (ub - 1 >= 0) {
        nd += ub;
      }
      s.colidx[cidx + 1] = s.colidx[cidx] + ub;
    }
  }
}

//
// Arguments    : g_sparse &s
// Return Type  : void
//
void sparse::parenReference(g_sparse &s) const
{
  int i;
  int nd_tmp;
  int numalloc;
  if (n < 1) {
    rtErrorWithMessageID(static_cast<long>(1L), static_cast<int>(0),
                         bc_emlrtRTEI.fName, bc_emlrtRTEI.lineNo);
  }
  nd_tmp = colidx[1] - colidx[0];
  if ((nd_tmp > m) && (m != 0)) {
    g_rtErrorWithMessageID(ic_emlrtRTEI.fName, ic_emlrtRTEI.lineNo);
  }
  if (m < 0) {
    ec_rtErrorWithMessageID(dc_emlrtRTEI.fName, dc_emlrtRTEI.lineNo);
  }
  if (m >= MAX_int32_T) {
    wc_rtErrorWithMessageID(cc_emlrtRTEI.fName, cc_emlrtRTEI.lineNo);
  }
  s.m = m;
  if (nd_tmp < 0) {
    ec_rtErrorWithMessageID(dc_emlrtRTEI.fName, dc_emlrtRTEI.lineNo);
  }
  if (nd_tmp >= MAX_int32_T) {
    wc_rtErrorWithMessageID(cc_emlrtRTEI.fName, cc_emlrtRTEI.lineNo);
  }
  if (nd_tmp >= 1) {
    numalloc = nd_tmp;
  } else {
    numalloc = 1;
  }
  s.d.set_size(numalloc);
  s.maxnz = numalloc;
  s.colidx.set_size(2);
  s.rowidx.set_size(numalloc);
  for (i = 0; i < numalloc; i++) {
    s.d[i] = 0.0;
    s.rowidx[i] = 0;
  }
  s.colidx[0] = 1;
  s.colidx[1] = 1;
  if (nd_tmp != 0) {
    numalloc = colidx[0] - 2;
    for (int k{0}; k < nd_tmp; k++) {
      i = (numalloc + k) + 1;
      s.d[k] = d[i];
      s.rowidx[k] = rowidx[i];
    }
    s.colidx[1] = nd_tmp + 1;
  }
}

//
// Arguments    : const array<double, 2U> &varargin_1
//                d_sparse &s
// Return Type  : void
//
void f_sparse::parenReference(const array<double, 2U> &varargin_1,
                              d_sparse &s) const
{
  double dv[2];
  double dv1[2];
  double b_d;
  int colNnz;
  int i;
  int ncol_tmp;
  int overflow;
  int vk;
  boolean_T found;
  internal::b_bigProduct(m, n, overflow);
  if (overflow == 0) {
    vk = m * n;
    i = varargin_1.size(1);
    for (overflow = 0; overflow < i; overflow++) {
      double d1;
      b_d = varargin_1[overflow];
      d1 = std::floor(b_d);
      if ((!(d1 == b_d)) || std::isinf(b_d)) {
        ic_rtErrorWithMessageID(hc_emlrtRTEI.fName, hc_emlrtRTEI.lineNo);
      }
      if (!(b_d <= vk)) {
        rtErrorWithMessageID(static_cast<long>(d1), vk, bc_emlrtRTEI.fName,
                             bc_emlrtRTEI.lineNo);
      }
    }
  } else {
    i = varargin_1.size(1);
    for (overflow = 0; overflow < i; overflow++) {
      b_d = varargin_1[overflow];
      if ((!(std::floor(b_d) == b_d)) || std::isinf(b_d)) {
        ic_rtErrorWithMessageID(hc_emlrtRTEI.fName, hc_emlrtRTEI.lineNo);
      }
    }
  }
  ncol_tmp = varargin_1.size(1);
  dv[0] = m;
  dv[1] = n;
  dv1[0] = 1.0;
  dv1[1] = (static_cast<double>(varargin_1.size(1)) - 1.0) + 1.0;
  internal::indexShapeCheck(dv, dv1);
  s.n = varargin_1.size(1);
  found = (varargin_1.size(1) + 1 < 0);
  if (found) {
    rtNonNegativeError(static_cast<double>(varargin_1.size(1) + 1), m_emlrtDCI);
  }
  s.d.set_size(0);
  s.rowidx.set_size(0);
  vk = varargin_1.size(1) + 1;
  s.colidx.set_size(varargin_1.size(1) + 1);
  for (i = 0; i < vk; i++) {
    s.colidx[i] = 0;
  }
  s.colidx[0] = 1;
  colNnz = 1;
  if (varargin_1.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int cidx{0}; cidx < ncol_tmp; cidx++) {
    b_d = varargin_1[cidx];
    if ((static_cast<int>(b_d) < 1) ||
        (static_cast<int>(b_d) >
         static_cast<int>(dv[0]) * static_cast<int>(dv[1]))) {
      gc_rtErrorWithMessageID(gc_emlrtRTEI.fName, gc_emlrtRTEI.lineNo);
    }
    i = static_cast<int>(dv[0]);
    vk = div_s32(static_cast<int>(b_d) - 1, i);
    vk = sparse_locBsearch(rowidx,
                           static_cast<double>(static_cast<int>(b_d) - vk * i),
                           colidx[vk], colidx[vk + 1], found);
    if (found) {
      i = s.d.size(0);
      overflow = s.d.size(0) + 1;
      s.d.set_size(s.d.size(0) + 1);
      s.d[i] = d[vk - 1];
      s.rowidx.set_size(overflow);
      s.rowidx[i] = 1;
      colNnz++;
    }
    s.colidx[cidx + 1] = colNnz;
  }
  if (s.d.size(0) == 0) {
    s.d.set_size(1);
    s.d[0] = false;
    s.rowidx.set_size(1);
    s.rowidx[0] = 0;
  }
}

//
// Arguments    : c_sparse &s
// Return Type  : void
//
void b_sparse::parenReference(c_sparse &s) const
{
  int idx;
  boolean_T found;
  if (n < 1) {
    rtErrorWithMessageID(static_cast<long>(1L), static_cast<int>(0),
                         bc_emlrtRTEI.fName, bc_emlrtRTEI.lineNo);
  }
  s.colidx.set_size(2);
  s.colidx[0] = 1;
  s.colidx[1] = 1;
  idx = sparse_locBsearch(rowidx, 1.0, colidx[0], colidx[1], found);
  if (found) {
    s.d.set_size(1);
    s.d[0] = d[idx - 1];
    s.rowidx.set_size(1);
    s.rowidx[0] = 1;
    s.colidx[1] = 2;
  } else {
    s.d.set_size(1);
    s.d[0] = 0.0;
    s.rowidx.set_size(1);
    s.rowidx[0] = 0;
  }
}

} // namespace coder

//
// File trailer for sparse1.cpp
//
// [EOF]
//
