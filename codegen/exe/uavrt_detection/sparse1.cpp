//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sparse1.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 22-Mar-2023 16:43:02
//

// Include Files
#include "sparse1.h"
#include "anonymous_function.h"
#include "bigProduct.h"
#include "eml_int_forloop_overflow_check.h"
#include "ind2sub.h"
#include "indexShapeCheck.h"
#include "locBsearch.h"
#include "rt_nonfinite.h"
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
#include <string.h>
#include <string>

// Variable Definitions
static rtRunTimeErrorInfo ec_emlrtRTEI{
    29,             // lineNo
    "sparse/mtimes" // fName
};

static rtRunTimeErrorInfo ic_emlrtRTEI{
    12,                                  // lineNo
    "sparse/sparse_validateNumericIndex" // fName
};

static rtRunTimeErrorInfo lc_emlrtRTEI{
    1629,             // lineNo
    "assertValidSize" // fName
};

static rtRunTimeErrorInfo pc_emlrtRTEI{
    11,                                  // lineNo
    "sparse/sparse_validateNumericIndex" // fName
};

static rtRunTimeErrorInfo qc_emlrtRTEI{
    92,                       // lineNo
    "parenReference2DColumns" // fName
};

static rtRunTimeErrorInfo tc_emlrtRTEI{
    11,                    // lineNo
    "sparse/parenAssign1D" // fName
};

// Function Declarations
static void ac_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void bc_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void ec_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void kb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void lb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void mb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void nc_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void oc_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void rtErrorWithMessageID(const int i, const int i1,
                                 const char *aFcnName, int aLineNum);

static void rtErrorWithMessageID(const long long i, const int i1,
                                 const char *aFcnName, int aLineNum);

static void yb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : f_sparse *b_this
//                int numAllocRequested
//                int ub1
//                int lb2
//                int ub2
// Return Type  : void
//
namespace coder {
void sparse::b_realloc(f_sparse *b_this, int numAllocRequested, int ub1,
                       int lb2, int ub2)
{
  static rtRunTimeErrorInfo uc_emlrtRTEI{
      237,           // lineNo
      "sparse/numel" // fName
  };
  array<int, 1U> rowidxt;
  array<boolean_T, 1U> dt;
  int numAlloc;
  int overflow;
  rowidxt.set_size(b_this->rowidx.size(0));
  numAlloc = b_this->rowidx.size(0);
  for (overflow = 0; overflow < numAlloc; overflow++) {
    rowidxt[overflow] = b_this->rowidx[overflow];
  }
  dt.set_size(b_this->d.size(0));
  numAlloc = b_this->d.size(0);
  for (overflow = 0; overflow < numAlloc; overflow++) {
    dt[overflow] = b_this->d[overflow];
  }
  internal::b_bigProduct(b_this->m, b_this->n, &numAlloc, &overflow);
  if (overflow == 0) {
    internal::b_bigProduct(b_this->m, b_this->n, &numAlloc, &overflow);
    if (overflow != 0) {
      oc_rtErrorWithMessageID(uc_emlrtRTEI.fName, uc_emlrtRTEI.lineNo);
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
    b_this->rowidx[numAlloc] = rowidxt[numAlloc - 1];
    b_this->d[numAlloc] = dt[numAlloc - 1];
  }
}

//
// Arguments    : boolean_T rhs
//                double r
//                double c
// Return Type  : void
//
void f_sparse::parenAssign2D(boolean_T rhs, double r, double c)
{
  int vidx;
  boolean_T thisv;
  if ((!(std::floor(r) == r)) || std::isinf(r) || (!(r > 0.0))) {
    ec_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
  }
  if (!(r <= m)) {
    rtErrorWithMessageID(static_cast<long long>(r), m, ic_emlrtRTEI.fName,
                         ic_emlrtRTEI.lineNo);
  }
  if ((!(std::floor(c) == c)) || std::isinf(c) || (!(c > 0.0))) {
    ec_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
  }
  if (!(c <= n)) {
    rtErrorWithMessageID(static_cast<long long>(c), n, ic_emlrtRTEI.fName,
                         ic_emlrtRTEI.lineNo);
  }
  b_sparse_locBsearch(rowidx, static_cast<int>(r),
                      colidx[static_cast<int>(c) - 1],
                      colidx[static_cast<int>(c)], &vidx, &thisv);
  if (thisv) {
    thisv = d[vidx - 1];
  } else {
    thisv = false;
  }
  if (thisv || rhs) {
    if (thisv && rhs) {
      d[vidx - 1] = true;
    } else if (!thisv) {
      int nelem;
      if (colidx[colidx.size(0) - 1] - 1 == maxnz) {
        sparse::b_realloc(this, colidx[colidx.size(0) - 1] + 9, vidx, vidx + 1,
                          colidx[colidx.size(0) - 1] - 1);
        rowidx[vidx] = static_cast<int>(r);
        d[vidx] = rhs;
      } else {
        nelem = (colidx[colidx.size(0) - 1] - vidx) - 1;
        if (nelem > 0) {
          std::memmove((void *)&rowidx[vidx + 1], (void *)&rowidx[vidx],
                       (unsigned int)((size_t)nelem * sizeof(int)));
          std::memmove((void *)&d[vidx + 1], (void *)&d[vidx],
                       (unsigned int)((size_t)nelem * sizeof(boolean_T)));
        }
        d[vidx] = rhs;
        rowidx[vidx] = static_cast<int>(r);
      }
      vidx = static_cast<int>(c) + 1;
      nelem = n + 1;
      if ((vidx <= nelem) && (nelem > 2147483646)) {
        check_forloop_overflow_error();
      }
      for (int k{vidx}; k <= nelem; k++) {
        colidx[k - 1] = colidx[k - 1] + 1;
      }
    } else {
      int nelem;
      nelem = (colidx[colidx.size(0) - 1] - vidx) - 1;
      if (nelem > 0) {
        std::memmove((void *)&rowidx[vidx - 1], (void *)&rowidx[vidx],
                     (unsigned int)((size_t)nelem * sizeof(int)));
        std::memmove((void *)&d[vidx - 1], (void *)&d[vidx],
                     (unsigned int)((size_t)nelem * sizeof(boolean_T)));
      }
      vidx = static_cast<int>(c) + 1;
      nelem = n + 1;
      if ((vidx <= nelem) && (nelem > 2147483646)) {
        check_forloop_overflow_error();
      }
      for (int k{vidx}; k <= nelem; k++) {
        colidx[k - 1] = colidx[k - 1] - 1;
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
static void ac_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
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
static void bc_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
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
static void ec_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
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
static void kb_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
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
static void lb_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
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
static void mb_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
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
static void nc_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
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
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void oc_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
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
  ((((((outStream
        << "Index expression out of bounds. Attempted to access element ")
       << i)
      << ". The valid range is ")
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
// Arguments    : const long long i
//                const int i1
//                const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void rtErrorWithMessageID(const long long i, const int i1,
                                 const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((((((outStream
        << "Index expression out of bounds. Attempted to access element ")
       << i)
      << ". The valid range is ")
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
static void yb_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
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
// Arguments    : const ::coder::array<double, 1U> &s
//                ::coder::array<int, 1U> &sint
// Return Type  : void
//
namespace coder {
void sparse::assertValidIndexArg(const ::coder::array<double, 1U> &s,
                                 ::coder::array<int, 1U> &sint)
{
  static rtRunTimeErrorInfo uc_emlrtRTEI{
      1660,                 // lineNo
      "assertValidIndexArg" // fName
  };
  static rtRunTimeErrorInfo vc_emlrtRTEI{
      1658,                 // lineNo
      "assertValidIndexArg" // fName
  };
  static rtRunTimeErrorInfo wc_emlrtRTEI{
      1662,                 // lineNo
      "assertValidIndexArg" // fName
  };
  int ns;
  ns = s.size(0);
  sint.set_size(s.size(0));
  if (s.size(0) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{0}; k < ns; k++) {
    if (!(std::floor(s[k]) == s[k])) {
      kb_rtErrorWithMessageID(vc_emlrtRTEI.fName, vc_emlrtRTEI.lineNo);
    }
    if (!(s[k] < 2.147483647E+9)) {
      lb_rtErrorWithMessageID(uc_emlrtRTEI.fName, uc_emlrtRTEI.lineNo);
    }
    if (!(s[k] > 0.0)) {
      mb_rtErrorWithMessageID(wc_emlrtRTEI.fName, wc_emlrtRTEI.lineNo);
    }
    sint[k] = static_cast<int>(s[k]);
  }
}

//
// Arguments    : d_sparse *s
// Return Type  : void
//
void b_sparse::b_le(d_sparse *s) const
{
  array<boolean_T, 2U> S;
  int a;
  int b_n;
  S.set_size(1, n);
  b_n = n;
  for (a = 0; a < b_n; a++) {
    S[a] = true;
  }
  b_n = n;
  if (n > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int col{0}; col < b_n; col++) {
    int b_tmp;
    a = colidx[col];
    b_tmp = colidx[col + 1] - 1;
    if ((colidx[col] <= b_tmp) && (b_tmp > 2147483646)) {
      check_forloop_overflow_error();
    }
    for (int idx{a}; idx <= b_tmp; idx++) {
      S[col] = (d[idx - 1] <= 0.0);
    }
  }
  j_sparse(S, s);
}

//
// Arguments    : const ::coder::array<double, 2U> &a
//                ::coder::array<double, 2U> &c
// Return Type  : void
//
void f_sparse::b_mtimes(const ::coder::array<double, 2U> &a,
                        ::coder::array<double, 2U> &c) const
{
  int aoff;
  int b_m;
  int b_n;
  int cidx;
  if (a.size(1) != m) {
    ob_rtErrorWithMessageID(ec_emlrtRTEI.fName, ec_emlrtRTEI.lineNo);
  }
  b_m = a.size(0);
  b_n = n - 1;
  c.set_size(a.size(0), n);
  aoff = a.size(0) * n;
  for (cidx = 0; cidx < aoff; cidx++) {
    c[cidx] = 0.0;
  }
  if ((a.size(1) != 0) && (a.size(0) != 0) && (n != 0) &&
      (colidx[colidx.size(0) - 1] - 1 != 0)) {
    if (a.size(0) == 1) {
      aoff = n;
      if (n > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int aidx_tmp{0}; aidx_tmp < aoff; aidx_tmp++) {
        double cd;
        int b_a;
        cd = 0.0;
        cidx = colidx[aidx_tmp + 1] - 1;
        b_a = colidx[aidx_tmp];
        if ((colidx[aidx_tmp] <= cidx) && (cidx > 2147483646)) {
          check_forloop_overflow_error();
        }
        for (int mend{b_a}; mend <= cidx; mend++) {
          cd += static_cast<double>(d[mend - 1]) * a[rowidx[mend - 1] - 1];
        }
        c[aidx_tmp] = cd;
      }
    } else if (a.size(0) >= 4) {
      if (n > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int ccol{0}; ccol <= b_n; ccol++) {
        int b_a;
        int bpend_tmp;
        int coff;
        coff = ccol * c.size(0);
        bpend_tmp = colidx[ccol + 1] - 1;
        b_a = colidx[ccol];
        if ((colidx[ccol] <= bpend_tmp) && (bpend_tmp > 2147483646)) {
          check_forloop_overflow_error();
        }
        for (int bp{b_a}; bp <= bpend_tmp; bp++) {
          int aoff_tmp;
          int mend;
          boolean_T bd;
          aoff_tmp = rowidx[bp - 1] - 1;
          aoff = aoff_tmp * a.size(0);
          bd = d[bp - 1];
          mend = (b_m / 4) << 2;
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
          aoff = mend + 1;
          if ((mend + 1 <= b_m) && (b_m > 2147483646)) {
            check_forloop_overflow_error();
          }
          for (int crow{aoff}; crow <= b_m; crow++) {
            cidx = (crow + coff) - 1;
            c[cidx] = c[cidx] + a[(crow + a.size(0) * aoff_tmp) - 1] *
                                    static_cast<double>(bd);
          }
        }
      }
    } else {
      if (n > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int ccol{0}; ccol <= b_n; ccol++) {
        int b_a;
        int bpend_tmp;
        bpend_tmp = colidx[ccol + 1] - 1;
        b_a = colidx[ccol];
        if ((colidx[ccol] <= bpend_tmp) && (bpend_tmp > 2147483646)) {
          check_forloop_overflow_error();
        }
        for (int bp{b_a}; bp <= bpend_tmp; bp++) {
          for (int crow{0}; crow < b_m; crow++) {
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
// Arguments    : d_sparse *out
// Return Type  : void
//
void d_sparse::b_not(d_sparse *out) const
{
  static rtRunTimeErrorInfo uc_emlrtRTEI{
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
      bc_rtErrorWithMessageID(uc_emlrtRTEI.fName, uc_emlrtRTEI.lineNo);
    }
  }
  nzmax = larger;
  out->n = n;
  if (larger < 1) {
    nzmax = 1;
  }
  out->d.set_size(nzmax);
  out->rowidx.set_size(nzmax);
  if (n + 1 < 0) {
    rtNonNegativeError(static_cast<double>(n + 1), &r_emlrtDCI);
  }
  out->colidx.set_size(n + 1);
  if (larger < 1) {
    larger = 0;
  }
  for (nzmax = 0; nzmax < larger; nzmax++) {
    out->d[nzmax] = true;
  }
  curPosition = 1;
  b = n;
  if (n > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int c{0}; c < b; c++) {
    out->colidx[c] = curPosition;
    nzmax = colidx[c + 1];
    if (colidx[c] == nzmax) {
      out->rowidx[curPosition - 1] = 1;
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
        out->rowidx[((curPosition + nzmax) - larger) - 1] = 1;
      }
      curPosition = (curPosition - larger) + 2;
    }
  }
  out->colidx[n] = curPosition;
}

//
// Arguments    : const ::coder::array<boolean_T, 2U> &rhs
//                const ::coder::array<double, 2U> &varargin_1
// Return Type  : void
//
void f_sparse::b_parenAssign(const ::coder::array<boolean_T, 2U> &rhs,
                             const ::coder::array<double, 2U> &varargin_1)
{
  int nidx;
  int overflow;
  int varargout_4;
  internal::bigProduct(m, n, &nidx, &overflow);
  if (rhs.size(1) != varargin_1.size(1)) {
    nc_rtErrorWithMessageID(tc_emlrtRTEI.fName, tc_emlrtRTEI.lineNo);
  }
  if (overflow == 0) {
    overflow = m * n;
    nidx = varargin_1.size(1);
    for (int k{0}; k < nidx; k++) {
      double b_d;
      b_d = varargin_1[k];
      if ((!(std::floor(b_d) == b_d)) || std::isinf(b_d)) {
        ec_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
      }
      if (!(b_d <= overflow)) {
        rtErrorWithMessageID(static_cast<long long>(b_d), overflow,
                             ic_emlrtRTEI.fName, ic_emlrtRTEI.lineNo);
      }
    }
  } else {
    nidx = varargin_1.size(1);
    for (int k{0}; k < nidx; k++) {
      double b_d;
      b_d = varargin_1[k];
      if ((!(std::floor(b_d) == b_d)) || std::isinf(b_d)) {
        ec_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
      }
      if (!(b_d <= 2.147483647E+9)) {
        rtErrorWithMessageID(static_cast<long long>(b_d), MAX_int32_T,
                             ic_emlrtRTEI.fName, ic_emlrtRTEI.lineNo);
      }
    }
  }
  nidx = varargin_1.size(1);
  if (varargin_1.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{0}; k < nidx; k++) {
    double b_this[2];
    b_this[0] = m;
    b_this[1] = n;
    ind2sub_indexClass(b_this, varargin_1[k], &overflow, &varargout_4);
    parenAssign2D(rhs[k], static_cast<double>(overflow),
                  static_cast<double>(varargout_4));
  }
}

//
// Arguments    : const ::coder::array<double, 2U> &rhs
//                const ::coder::array<double, 2U> &varargin_1
// Return Type  : void
//
void f_sparse::c_parenAssign(const ::coder::array<double, 2U> &rhs,
                             const ::coder::array<double, 2U> &varargin_1)
{
  int lowOrderSize;
  int nidx;
  int overflow;
  int varargout_4;
  boolean_T thisv;
  internal::bigProduct(m, n, &lowOrderSize, &overflow);
  if (rhs.size(1) != varargin_1.size(1)) {
    nc_rtErrorWithMessageID(tc_emlrtRTEI.fName, tc_emlrtRTEI.lineNo);
  }
  if (overflow == 0) {
    overflow = m * n;
    lowOrderSize = varargin_1.size(1);
    for (int k{0}; k < lowOrderSize; k++) {
      double b_d;
      b_d = varargin_1[k];
      if ((!(std::floor(b_d) == b_d)) || std::isinf(b_d)) {
        ec_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
      }
      if (!(b_d <= overflow)) {
        rtErrorWithMessageID(static_cast<long long>(b_d), overflow,
                             ic_emlrtRTEI.fName, ic_emlrtRTEI.lineNo);
      }
    }
  } else {
    lowOrderSize = varargin_1.size(1);
    for (int k{0}; k < lowOrderSize; k++) {
      double b_d;
      b_d = varargin_1[k];
      if ((!(std::floor(b_d) == b_d)) || std::isinf(b_d)) {
        ec_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
      }
      if (!(b_d <= 2.147483647E+9)) {
        rtErrorWithMessageID(static_cast<long long>(b_d), MAX_int32_T,
                             ic_emlrtRTEI.fName, ic_emlrtRTEI.lineNo);
      }
    }
  }
  nidx = varargin_1.size(1);
  if (varargin_1.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{0}; k < nidx; k++) {
    double b_this[2];
    b_this[0] = m;
    b_this[1] = n;
    ind2sub_indexClass(b_this, varargin_1[k], &lowOrderSize, &varargout_4);
    if (lowOrderSize <= 0) {
      ec_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
    }
    if (lowOrderSize > m) {
      rtErrorWithMessageID(static_cast<long long>(lowOrderSize), m,
                           ic_emlrtRTEI.fName, ic_emlrtRTEI.lineNo);
    }
    if (varargout_4 <= 0) {
      ec_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
    }
    if (varargout_4 > n) {
      rtErrorWithMessageID(static_cast<long long>(varargout_4), n,
                           ic_emlrtRTEI.fName, ic_emlrtRTEI.lineNo);
    }
    b_sparse_locBsearch(rowidx, lowOrderSize, colidx[varargout_4 - 1],
                        colidx[varargout_4], &overflow, &thisv);
    if (thisv) {
      thisv = d[overflow - 1];
    } else {
      thisv = false;
    }
    if (thisv || (!(rhs[k] == 0.0))) {
      if (thisv && (rhs[k] != 0.0)) {
        d[overflow - 1] = true;
      } else if (!thisv) {
        int nelem;
        if (colidx[colidx.size(0) - 1] - 1 == maxnz) {
          sparse::b_realloc(this, colidx[colidx.size(0) - 1] + 9, overflow,
                            overflow + 1, colidx[colidx.size(0) - 1] - 1);
          rowidx[overflow] = lowOrderSize;
          d[overflow] = (rhs[k] != 0.0);
        } else {
          nelem = (colidx[colidx.size(0) - 1] - overflow) - 1;
          if (nelem > 0) {
            std::memmove((void *)&rowidx[overflow + 1],
                         (void *)&rowidx[overflow],
                         (unsigned int)((size_t)nelem * sizeof(int)));
            std::memmove((void *)&d[overflow + 1], (void *)&d[overflow],
                         (unsigned int)((size_t)nelem * sizeof(boolean_T)));
          }
          d[overflow] = (rhs[k] != 0.0);
          rowidx[overflow] = lowOrderSize;
        }
        lowOrderSize = varargout_4 + 1;
        overflow = n + 1;
        if ((varargout_4 + 1 <= overflow) && (overflow > 2147483646)) {
          check_forloop_overflow_error();
        }
        for (nelem = lowOrderSize; nelem <= overflow; nelem++) {
          colidx[nelem - 1] = colidx[nelem - 1] + 1;
        }
      } else {
        int nelem;
        nelem = (colidx[colidx.size(0) - 1] - overflow) - 1;
        if (nelem > 0) {
          std::memmove((void *)&rowidx[overflow - 1], (void *)&rowidx[overflow],
                       (unsigned int)((size_t)nelem * sizeof(int)));
          std::memmove((void *)&d[overflow - 1], (void *)&d[overflow],
                       (unsigned int)((size_t)nelem * sizeof(boolean_T)));
        }
        lowOrderSize = varargout_4 + 1;
        overflow = n + 1;
        if ((varargout_4 + 1 <= overflow) && (overflow > 2147483646)) {
          check_forloop_overflow_error();
        }
        for (nelem = lowOrderSize; nelem <= overflow; nelem++) {
          colidx[nelem - 1] = colidx[nelem - 1] - 1;
        }
      }
    }
  }
}

//
// Arguments    : const h_sparse *rhs
//                const ::coder::array<double, 2U> &varargin_1
// Return Type  : void
//
void f_sparse::c_parenAssign(const h_sparse *rhs,
                             const ::coder::array<double, 2U> &varargin_1)
{
  e_sparse s;
  double varargout_1_tmp[2];
  int cend;
  int highOrderRHS;
  int idx;
  int nidx;
  int varargout_3;
  int varargout_4;
  boolean_T rhsv;
  internal::bigProduct(m, n, &cend, &nidx);
  varargout_1_tmp[0] = rhs->m;
  varargout_1_tmp[1] = 1.0;
  internal::bigProduct(rhs->m, 1, &cend, &highOrderRHS);
  if (((varargin_1.size(1) & 65535) + ((varargin_1.size(1) >> 16) << 16) !=
       cend) ||
      (highOrderRHS != 0)) {
    nc_rtErrorWithMessageID(tc_emlrtRTEI.fName, tc_emlrtRTEI.lineNo);
  }
  if (nidx == 0) {
    cend = m * n;
    highOrderRHS = varargin_1.size(1);
    for (int k{0}; k < highOrderRHS; k++) {
      double b_d;
      b_d = varargin_1[k];
      if ((!(std::floor(b_d) == b_d)) || std::isinf(b_d)) {
        ec_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
      }
      if (!(b_d <= cend)) {
        rtErrorWithMessageID(static_cast<long long>(b_d), cend,
                             ic_emlrtRTEI.fName, ic_emlrtRTEI.lineNo);
      }
    }
  } else {
    highOrderRHS = varargin_1.size(1);
    for (int k{0}; k < highOrderRHS; k++) {
      double b_d;
      b_d = varargin_1[k];
      if ((!(std::floor(b_d) == b_d)) || std::isinf(b_d)) {
        ec_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
      }
      if (!(b_d <= 2.147483647E+9)) {
        rtErrorWithMessageID(static_cast<long long>(b_d), MAX_int32_T,
                             ic_emlrtRTEI.fName, ic_emlrtRTEI.lineNo);
      }
    }
  }
  nidx = varargin_1.size(1);
  if (varargin_1.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{0}; k < nidx; k++) {
    double b_this[2];
    b_this[0] = m;
    b_this[1] = n;
    ind2sub_indexClass(b_this, varargin_1[k], &varargout_3, &varargout_4);
    if (((rhs->m & 65535) <= MAX_int32_T - ((rhs->m >> 16) << 16)) &&
        (k + 1 > rhs->m)) {
      rtErrorWithMessageID(k + 1, rhs->m, ic_emlrtRTEI.fName,
                           ic_emlrtRTEI.lineNo);
    }
    s.colidx.set_size(2);
    s.colidx[0] = 1;
    s.colidx[1] = 1;
    ind2sub_indexClass(varargout_1_tmp, k + 1, &cend, &highOrderRHS);
    sparse_locBsearch(rhs->rowidx, static_cast<double>(cend),
                      rhs->colidx[highOrderRHS - 1], rhs->colidx[highOrderRHS],
                      &idx, &rhsv);
    if (rhsv) {
      s.d.set_size(1);
      s.d[0] = rhs->d[idx - 1];
      s.colidx[1] = 2;
    } else {
      s.d.set_size(1);
      s.d[0] = false;
    }
    rhsv = false;
    cend = s.colidx[1] - 1;
    highOrderRHS = s.colidx[0];
    for (idx = highOrderRHS; idx <= cend; idx++) {
      rhsv = s.d[idx - 1];
    }
    parenAssign2D(rhsv, static_cast<double>(varargout_3),
                  static_cast<double>(varargout_4));
  }
}

//
// Arguments    : const c_sparse *b
//                d_sparse *s
// Return Type  : void
//
void b_sparse::eq(const c_sparse *b, d_sparse *s) const
{
  static rtRunTimeErrorInfo uc_emlrtRTEI{
      454,               // lineNo
      "sparse/spfunImpl" // fName
  };
  static rtRunTimeErrorInfo vc_emlrtRTEI{
      178,            // lineNo
      "sparse/sparse" // fName
  };
  d_anonymous_function uniOp;
  array<boolean_T, 2U> S;
  array<boolean_T, 1U> tmpd;
  if (b->colidx[b->colidx.size(0) - 1] - 1 > 0) {
    uniOp.workspace.sb = b->d[0];
  } else {
    uniOp.workspace.sb = 0.0;
  }
  if (!(uniOp.workspace.sb == 0.0)) {
    int b_n;
    int b_tmp;
    int i;
    int idx;
    b_tmp = colidx[colidx.size(0) - 1];
    if (colidx[colidx.size(0) - 1] - 1 < 1) {
      b_n = 0;
    } else {
      b_n = colidx[colidx.size(0) - 1] - 1;
    }
    tmpd.set_size(b_n);
    for (i = 0; i < b_n; i++) {
      tmpd[i] = (d[i] == uniOp.workspace.sb);
    }
    if (tmpd.size(0) != colidx[colidx.size(0) - 1] - 1) {
      jb_rtErrorWithMessageID(uc_emlrtRTEI.fName, uc_emlrtRTEI.lineNo);
    }
    if (n < 0) {
      ac_rtErrorWithMessageID(lc_emlrtRTEI.fName, lc_emlrtRTEI.lineNo);
    }
    if (n >= MAX_int32_T) {
      rc_rtErrorWithMessageID(jc_emlrtRTEI.fName, jc_emlrtRTEI.lineNo);
    }
    s->n = n;
    if (colidx[colidx.size(0) - 1] - 1 < 0) {
      ac_rtErrorWithMessageID(lc_emlrtRTEI.fName, lc_emlrtRTEI.lineNo);
    }
    if (colidx[colidx.size(0) - 1] - 1 >= MAX_int32_T) {
      rc_rtErrorWithMessageID(jc_emlrtRTEI.fName, jc_emlrtRTEI.lineNo);
    }
    if (colidx[colidx.size(0) - 1] - 1 < 0) {
      yb_rtErrorWithMessageID(vc_emlrtRTEI.fName, vc_emlrtRTEI.lineNo);
    }
    if (colidx[colidx.size(0) - 1] - 1 >= 1) {
      b_n = colidx[colidx.size(0) - 1] - 2;
    } else {
      b_n = 0;
    }
    s->d.set_size(b_n + 1);
    s->colidx.set_size(n + 1);
    s->rowidx.set_size(b_n + 1);
    for (i = 0; i <= b_n; i++) {
      s->d[i] = false;
      s->rowidx[i] = 0;
    }
    b_n = n;
    for (int col{0}; col < b_n; col++) {
      s->colidx[col + 1] = 1;
    }
    i = s->colidx.size(0);
    for (int col{0}; col <= i - 2; col++) {
      s->colidx[col] = 1;
    }
    if (colidx[colidx.size(0) - 1] - 1 < 1) {
      b_n = 1;
    } else {
      b_n = colidx[colidx.size(0) - 1];
    }
    for (i = 0; i <= b_n - 2; i++) {
      s->rowidx[i] = rowidx[i];
    }
    s->colidx.set_size(colidx.size(0));
    b_n = colidx.size(0);
    for (i = 0; i < b_n; i++) {
      s->colidx[i] = colidx[i];
    }
    if (colidx[colidx.size(0) - 1] - 1 > 2147483646) {
      check_forloop_overflow_error();
    }
    for (b_n = 0; b_n <= b_tmp - 2; b_n++) {
      s->d[b_n] = tmpd[b_n];
    }
    idx = 1;
    i = colidx.size(0);
    for (int col{0}; col <= i - 2; col++) {
      b_n = s->colidx[col];
      s->colidx[col] = idx;
      while (b_n < s->colidx[col + 1]) {
        int currRowIdx;
        boolean_T val;
        currRowIdx = s->rowidx[b_n - 1];
        val = s->d[b_n - 1];
        b_n++;
        if (val) {
          s->d[idx - 1] = true;
          s->rowidx[idx - 1] = currRowIdx;
          idx++;
        }
      }
    }
    s->colidx[s->colidx.size(0) - 1] = idx;
  } else {
    int b_n;
    S.set_size(1, n);
    b_n = n;
    for (int i{0}; i < b_n; i++) {
      S[i] = true;
    }
    b_n = n;
    if (n > 2147483646) {
      check_forloop_overflow_error();
    }
    for (int col{0}; col < b_n; col++) {
      int b_tmp;
      int currRowIdx;
      currRowIdx = colidx[col];
      b_tmp = colidx[col + 1] - 1;
      if ((colidx[col] <= b_tmp) && (b_tmp > 2147483646)) {
        check_forloop_overflow_error();
      }
      for (int idx{currRowIdx}; idx <= b_tmp; idx++) {
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
//                sparse *b_I
// Return Type  : void
//
void sparse::eyeLike(int ndiag, int b_m, int b_n, sparse *b_I)
{
  int b;
  int nzmax;
  b_I->m = b_m;
  nzmax = ndiag;
  b_I->n = b_n;
  if (ndiag < 1) {
    nzmax = 1;
  }
  b_I->maxnz = nzmax;
  b_I->d.set_size(nzmax);
  b_I->rowidx.set_size(nzmax);
  if (b_n + 1 < 0) {
    rtNonNegativeError(static_cast<double>(b_n + 1), &r_emlrtDCI);
  }
  b_I->colidx.set_size(b_n + 1);
  if (ndiag > 2147483646) {
    check_forloop_overflow_error();
  }
  for (nzmax = 0; nzmax < ndiag; nzmax++) {
    b_I->d[nzmax] = 1.0;
    b_I->rowidx[nzmax] = nzmax + 1;
  }
  b_I->colidx[0] = 1;
  for (int c{2}; c <= ndiag; c++) {
    b_I->colidx[c - 1] = c;
  }
  nzmax = ndiag + 1;
  b = b_n + 1;
  if ((ndiag + 1 <= b_n + 1) && (b_n + 1 > 2147483646)) {
    check_forloop_overflow_error();
  }
  for (int c{nzmax}; c <= b; c++) {
    b_I->colidx[c - 1] = ndiag + 1;
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
    int exitg1;
    int i1;
    do {
      exitg1 = 0;
      i1 = colidx[c + 1];
      if (ridx < i1) {
        double val;
        int currRowIdx;
        val = 0.0;
        currRowIdx = rowidx[ridx - 1];
        while ((ridx < i1) && (rowidx[ridx - 1] == currRowIdx)) {
          val += d[ridx - 1];
          ridx++;
        }
        if (val != 0.0) {
          d[idx - 1] = val;
          rowidx[idx - 1] = currRowIdx;
          idx++;
        }
      } else {
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  colidx[colidx.size(0) - 1] = idx;
}

//
// Arguments    : ::coder::array<boolean_T, 2U> &y
// Return Type  : void
//
void d_sparse::full(::coder::array<boolean_T, 2U> &y) const
{
  int cend_tmp;
  int loop_ub;
  y.set_size(1, n);
  loop_ub = n;
  for (cend_tmp = 0; cend_tmp < loop_ub; cend_tmp++) {
    y[cend_tmp] = false;
  }
  loop_ub = n;
  if (n > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int c{0}; c < loop_ub; c++) {
    int a;
    cend_tmp = colidx[c + 1] - 1;
    a = colidx[c];
    if ((colidx[c] <= cend_tmp) && (cend_tmp > 2147483646)) {
      check_forloop_overflow_error();
    }
    for (int idx{a}; idx <= cend_tmp; idx++) {
      y[c] = d[idx - 1];
    }
  }
}

//
// Arguments    : f_sparse *y
// Return Type  : void
//
void sparse::logical(f_sparse *y) const
{
  int i;
  int numalloc;
  if (m < 0) {
    ac_rtErrorWithMessageID(lc_emlrtRTEI.fName, lc_emlrtRTEI.lineNo);
  }
  if (m >= MAX_int32_T) {
    rc_rtErrorWithMessageID(jc_emlrtRTEI.fName, jc_emlrtRTEI.lineNo);
  }
  if (n < 0) {
    ac_rtErrorWithMessageID(lc_emlrtRTEI.fName, lc_emlrtRTEI.lineNo);
  }
  if (n >= MAX_int32_T) {
    rc_rtErrorWithMessageID(jc_emlrtRTEI.fName, jc_emlrtRTEI.lineNo);
  }
  y->m = m;
  y->n = n;
  if (maxnz < 0) {
    ac_rtErrorWithMessageID(lc_emlrtRTEI.fName, lc_emlrtRTEI.lineNo);
  }
  if (maxnz >= MAX_int32_T) {
    rc_rtErrorWithMessageID(jc_emlrtRTEI.fName, jc_emlrtRTEI.lineNo);
  }
  numalloc = maxnz;
  if (numalloc < 1) {
    numalloc = 1;
  }
  y->d.set_size(numalloc);
  for (i = 0; i < numalloc; i++) {
    y->d[i] = false;
  }
  y->maxnz = numalloc;
  y->colidx.set_size(n + 1);
  numalloc = n;
  for (int c{0}; c < numalloc; c++) {
    y->colidx[c + 1] = 1;
  }
  i = y->colidx.size(0);
  for (int c{0}; c <= i - 2; c++) {
    y->colidx[c] = 1;
  }
  y->rowidx.set_size(rowidx.size(0));
  numalloc = rowidx.size(0);
  for (i = 0; i < numalloc; i++) {
    y->rowidx[i] = rowidx[i];
  }
  y->colidx.set_size(colidx.size(0));
  numalloc = colidx.size(0);
  for (i = 0; i < numalloc; i++) {
    y->colidx[i] = colidx[i];
  }
  numalloc = colidx[colidx.size(0) - 1] - 1;
  if (numalloc < 1) {
    numalloc = 1;
  }
  i = numalloc - 1;
  for (int c{0}; c <= i; c++) {
    if (std::isnan(d[c])) {
      w_rtErrorWithMessageID(mb_emlrtRTEI.fName, mb_emlrtRTEI.lineNo);
    }
  }
  for (i = 0; i < numalloc; i++) {
    y->d[i] = (d[i] != 0.0);
  }
}

//
// Arguments    : h_sparse *y
// Return Type  : void
//
void g_sparse::logical(h_sparse *y) const
{
  int i;
  int numalloc;
  if (m < 0) {
    ac_rtErrorWithMessageID(lc_emlrtRTEI.fName, lc_emlrtRTEI.lineNo);
  }
  if (m >= MAX_int32_T) {
    rc_rtErrorWithMessageID(jc_emlrtRTEI.fName, jc_emlrtRTEI.lineNo);
  }
  y->m = m;
  if (maxnz < 0) {
    ac_rtErrorWithMessageID(lc_emlrtRTEI.fName, lc_emlrtRTEI.lineNo);
  }
  if (maxnz >= MAX_int32_T) {
    rc_rtErrorWithMessageID(jc_emlrtRTEI.fName, jc_emlrtRTEI.lineNo);
  }
  numalloc = maxnz;
  if (numalloc < 1) {
    numalloc = 1;
  }
  y->d.set_size(numalloc);
  for (i = 0; i < numalloc; i++) {
    y->d[i] = false;
  }
  y->rowidx.set_size(rowidx.size(0));
  numalloc = rowidx.size(0);
  for (i = 0; i < numalloc; i++) {
    y->rowidx[i] = rowidx[i];
  }
  y->colidx.set_size(colidx.size(0));
  numalloc = colidx.size(0);
  for (i = 0; i < numalloc; i++) {
    y->colidx[i] = colidx[i];
  }
  numalloc = colidx[colidx.size(0) - 1] - 1;
  if (numalloc < 1) {
    numalloc = 1;
  }
  i = numalloc - 1;
  for (int k{0}; k <= i; k++) {
    if (std::isnan(d[k])) {
      w_rtErrorWithMessageID(mb_emlrtRTEI.fName, mb_emlrtRTEI.lineNo);
    }
  }
  for (i = 0; i < numalloc; i++) {
    y->d[i] = (d[i] != 0.0);
  }
}

//
// Arguments    : const ::coder::array<double, 2U> &b
//                ::coder::array<double, 2U> &c
// Return Type  : void
//
void f_sparse::mtimes(const ::coder::array<double, 2U> &b,
                      ::coder::array<double, 2U> &c) const
{
  int b_n;
  int nap;
  int nap_tmp;
  if (n != b.size(0)) {
    ob_rtErrorWithMessageID(ec_emlrtRTEI.fName, ec_emlrtRTEI.lineNo);
  }
  b_n = b.size(1);
  c.set_size(m, b.size(1));
  nap = m * b.size(1);
  for (nap_tmp = 0; nap_tmp < nap; nap_tmp++) {
    c[nap_tmp] = 0.0;
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
        nap_tmp = colidx[acol + 1];
        nap = nap_tmp - colidx[acol];
        if (nap >= 4) {
          nap = ((nap_tmp - nap) + ((nap / 4) << 2)) - 1;
          if ((colidx[acol] <= nap) && (nap > 2147483643)) {
            check_forloop_overflow_error();
          }
          for (int ap{a}; ap <= nap; ap += 4) {
            nap_tmp = rowidx[ap - 1] - 1;
            c[nap_tmp] = c[nap_tmp] + static_cast<double>(d[ap - 1]) * bc;
            c[rowidx[ap] - 1] =
                c[rowidx[ap] - 1] + static_cast<double>(d[ap]) * bc;
            nap_tmp = rowidx[ap + 1] - 1;
            c[nap_tmp] = c[nap_tmp] + static_cast<double>(d[ap + 1]) * bc;
            nap_tmp = rowidx[ap + 2] - 1;
            c[nap_tmp] = c[nap_tmp] + static_cast<double>(d[ap + 2]) * bc;
          }
          nap_tmp = colidx[acol + 1] - 1;
          a = nap + 1;
          if ((nap + 1 <= nap_tmp) && (nap_tmp > 2147483646)) {
            check_forloop_overflow_error();
          }
          for (int ap{a}; ap <= nap_tmp; ap++) {
            nap = rowidx[ap - 1] - 1;
            c[nap] = c[nap] + static_cast<double>(d[ap - 1]) * bc;
          }
        } else {
          nap = nap_tmp - 1;
          if ((colidx[acol] <= nap_tmp - 1) && (nap_tmp - 1 > 2147483646)) {
            check_forloop_overflow_error();
          }
          for (int ap{a}; ap <= nap; ap++) {
            nap_tmp = rowidx[ap - 1] - 1;
            c[nap_tmp] = c[nap_tmp] + static_cast<double>(d[ap - 1]) * bc;
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
      for (int j{0}; j < b_n; j++) {
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
          nap_tmp = colidx[acol + 1];
          nap = nap_tmp - colidx[acol];
          if (nap >= 4) {
            nap = ((nap_tmp - nap) + ((nap / 4) << 2)) - 1;
            if ((colidx[acol] <= nap) && (nap > 2147483643)) {
              check_forloop_overflow_error();
            }
            for (int ap{a}; ap <= nap; ap += 4) {
              nap_tmp = rowidx[ap - 1] + coff;
              c[nap_tmp] = c[nap_tmp] + static_cast<double>(d[ap - 1]) * bc;
              nap_tmp = rowidx[ap] + coff;
              c[nap_tmp] = c[nap_tmp] + static_cast<double>(d[ap]) * bc;
              nap_tmp = rowidx[ap + 1] + coff;
              c[nap_tmp] = c[nap_tmp] + static_cast<double>(d[ap + 1]) * bc;
              nap_tmp = rowidx[ap + 2] + coff;
              c[nap_tmp] = c[nap_tmp] + static_cast<double>(d[ap + 2]) * bc;
            }
            nap_tmp = colidx[acol + 1] - 1;
            a = nap + 1;
            if ((nap + 1 <= nap_tmp) && (nap_tmp > 2147483646)) {
              check_forloop_overflow_error();
            }
            for (int ap{a}; ap <= nap_tmp; ap++) {
              nap = rowidx[ap - 1] - 1;
              c[nap + c.size(0) * j] =
                  c[nap + c.size(0) * j] + static_cast<double>(d[ap - 1]) * bc;
            }
          } else {
            nap = nap_tmp - 1;
            if ((colidx[acol] <= nap_tmp - 1) && (nap_tmp - 1 > 2147483646)) {
              check_forloop_overflow_error();
            }
            for (int ap{a}; ap <= nap; ap++) {
              nap_tmp = rowidx[ap - 1] + coff;
              c[nap_tmp] = c[nap_tmp] + static_cast<double>(d[ap - 1]) * bc;
            }
          }
        }
      }
    }
  }
}

//
// Arguments    : const ::coder::array<double, 2U> &a
//                ::coder::array<double, 2U> &c
// Return Type  : void
//
void sparse::mtimes(const ::coder::array<double, 2U> &a,
                    ::coder::array<double, 2U> &c) const
{
  int aoff;
  int b_m;
  int b_n;
  int cidx;
  if (a.size(1) != m) {
    ob_rtErrorWithMessageID(ec_emlrtRTEI.fName, ec_emlrtRTEI.lineNo);
  }
  b_m = a.size(0);
  b_n = n - 1;
  c.set_size(a.size(0), n);
  aoff = a.size(0) * n;
  for (cidx = 0; cidx < aoff; cidx++) {
    c[cidx] = 0.0;
  }
  if ((a.size(1) != 0) && (a.size(0) != 0) && (n != 0) &&
      (colidx[colidx.size(0) - 1] - 1 != 0)) {
    if (a.size(0) == 1) {
      aoff = n;
      if (n > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int aidx_tmp{0}; aidx_tmp < aoff; aidx_tmp++) {
        double bd;
        int b_a;
        bd = 0.0;
        cidx = colidx[aidx_tmp + 1] - 1;
        b_a = colidx[aidx_tmp];
        if ((colidx[aidx_tmp] <= cidx) && (cidx > 2147483646)) {
          check_forloop_overflow_error();
        }
        for (int mend{b_a}; mend <= cidx; mend++) {
          bd += d[mend - 1] * a[rowidx[mend - 1] - 1];
        }
        c[aidx_tmp] = bd;
      }
    } else if (a.size(0) >= 4) {
      if (n > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int ccol{0}; ccol <= b_n; ccol++) {
        int b_a;
        int bpend_tmp;
        int coff;
        coff = ccol * c.size(0);
        bpend_tmp = colidx[ccol + 1] - 1;
        b_a = colidx[ccol];
        if ((colidx[ccol] <= bpend_tmp) && (bpend_tmp > 2147483646)) {
          check_forloop_overflow_error();
        }
        for (int bp{b_a}; bp <= bpend_tmp; bp++) {
          double bd;
          int aoff_tmp;
          int mend;
          aoff_tmp = rowidx[bp - 1] - 1;
          aoff = aoff_tmp * a.size(0);
          bd = d[bp - 1];
          mend = (b_m / 4) << 2;
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
          aoff = mend + 1;
          if ((mend + 1 <= b_m) && (b_m > 2147483646)) {
            check_forloop_overflow_error();
          }
          for (int crow{aoff}; crow <= b_m; crow++) {
            cidx = (crow + coff) - 1;
            c[cidx] = c[cidx] + a[(crow + a.size(0) * aoff_tmp) - 1] * bd;
          }
        }
      }
    } else {
      if (n > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int ccol{0}; ccol <= b_n; ccol++) {
        int b_a;
        int bpend_tmp;
        bpend_tmp = colidx[ccol + 1] - 1;
        b_a = colidx[ccol];
        if ((colidx[ccol] <= bpend_tmp) && (bpend_tmp > 2147483646)) {
          check_forloop_overflow_error();
        }
        for (int bp{b_a}; bp <= bpend_tmp; bp++) {
          for (int crow{0}; crow < b_m; crow++) {
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
// Arguments    : const ::coder::array<boolean_T, 1U> &rhs
//                const ::coder::array<double, 2U> &varargin_1
// Return Type  : void
//
void f_sparse::parenAssign(const ::coder::array<boolean_T, 1U> &rhs,
                           const ::coder::array<double, 2U> &varargin_1)
{
  int nidx;
  int overflow;
  int varargout_4;
  internal::bigProduct(m, n, &nidx, &overflow);
  if (rhs.size(0) != varargin_1.size(1)) {
    nc_rtErrorWithMessageID(tc_emlrtRTEI.fName, tc_emlrtRTEI.lineNo);
  }
  if (overflow == 0) {
    overflow = m * n;
    nidx = varargin_1.size(1);
    for (int k{0}; k < nidx; k++) {
      double b_d;
      b_d = varargin_1[k];
      if ((!(std::floor(b_d) == b_d)) || std::isinf(b_d)) {
        ec_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
      }
      if (!(b_d <= overflow)) {
        rtErrorWithMessageID(static_cast<long long>(b_d), overflow,
                             ic_emlrtRTEI.fName, ic_emlrtRTEI.lineNo);
      }
    }
  } else {
    nidx = varargin_1.size(1);
    for (int k{0}; k < nidx; k++) {
      double b_d;
      b_d = varargin_1[k];
      if ((!(std::floor(b_d) == b_d)) || std::isinf(b_d)) {
        ec_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
      }
      if (!(b_d <= 2.147483647E+9)) {
        rtErrorWithMessageID(static_cast<long long>(b_d), MAX_int32_T,
                             ic_emlrtRTEI.fName, ic_emlrtRTEI.lineNo);
      }
    }
  }
  nidx = varargin_1.size(1);
  if (varargin_1.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int k{0}; k < nidx; k++) {
    double b_this[2];
    b_this[0] = m;
    b_this[1] = n;
    ind2sub_indexClass(b_this, varargin_1[k], &overflow, &varargout_4);
    parenAssign2D(rhs[k], static_cast<double>(overflow),
                  static_cast<double>(varargout_4));
  }
}

//
// Arguments    : const ::coder::array<double, 1U> &varargin_2
//                sparse *s
// Return Type  : void
//
void sparse::parenReference(const ::coder::array<double, 1U> &varargin_2,
                            sparse *s) const
{
  int i;
  int nd;
  int nd_tmp;
  int sn;
  int ub;
  ub = n;
  i = varargin_2.size(0);
  for (int k{0}; k < i; k++) {
    if ((!(std::floor(varargin_2[k]) == varargin_2[k])) ||
        std::isinf(varargin_2[k])) {
      ec_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
    }
    if (!(varargin_2[k] <= ub)) {
      rtErrorWithMessageID(static_cast<long long>(std::floor(varargin_2[k])),
                           ub, ic_emlrtRTEI.fName, ic_emlrtRTEI.lineNo);
    }
  }
  sn = varargin_2.size(0) - 1;
  ub = m * varargin_2.size(0);
  nd = 0;
  if (varargin_2.size(0) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int cidx{0}; cidx <= sn; cidx++) {
    nd_tmp = static_cast<int>(varargin_2[cidx]);
    nd = (nd + colidx[nd_tmp]) - colidx[nd_tmp - 1];
  }
  if ((nd > ub) && (ub != 0)) {
    i_rtErrorWithMessageID(qc_emlrtRTEI.fName, qc_emlrtRTEI.lineNo);
  }
  if (m < 0) {
    ac_rtErrorWithMessageID(lc_emlrtRTEI.fName, lc_emlrtRTEI.lineNo);
  }
  if (m >= MAX_int32_T) {
    rc_rtErrorWithMessageID(jc_emlrtRTEI.fName, jc_emlrtRTEI.lineNo);
  }
  s->m = m;
  s->n = varargin_2.size(0);
  if (nd < 0) {
    ac_rtErrorWithMessageID(lc_emlrtRTEI.fName, lc_emlrtRTEI.lineNo);
  }
  if (nd >= MAX_int32_T) {
    rc_rtErrorWithMessageID(jc_emlrtRTEI.fName, jc_emlrtRTEI.lineNo);
  }
  if (nd >= 1) {
    ub = nd;
  } else {
    ub = 1;
  }
  s->d.set_size(ub);
  s->maxnz = ub;
  s->colidx.set_size(varargin_2.size(0) + 1);
  s->colidx[0] = 1;
  s->rowidx.set_size(ub);
  for (i = 0; i < ub; i++) {
    s->d[i] = 0.0;
    s->rowidx[i] = 0;
  }
  ub = varargin_2.size(0);
  for (nd_tmp = 0; nd_tmp < ub; nd_tmp++) {
    s->colidx[nd_tmp + 1] = 1;
  }
  s->fillIn();
  if (nd != 0) {
    nd = 0;
    for (int cidx{0}; cidx <= sn; cidx++) {
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
        s->d[nd_tmp] = d[i];
        s->rowidx[nd_tmp] = rowidx[i];
      }
      nd += ub;
      s->colidx[cidx + 1] = s->colidx[cidx] + ub;
    }
  }
}

//
// Arguments    : const ::coder::array<double, 2U> &varargin_1
//                d_sparse *s
// Return Type  : void
//
void f_sparse::parenReference(const ::coder::array<double, 2U> &varargin_1,
                              d_sparse *s) const
{
  static rtDoubleCheckInfo t_emlrtDCI{
      248,                     // lineNo
      17,                      // colNo
      "sparse/parenReference", // fName
      "C:\\Program "
      "Files\\MATLAB\\toolbox\\shared\\coder\\coder\\+coder\\+internal\\@"
      "sparse\\sparse.m", // pName
      4                   // checkKind
  };
  array<double, 2U> b_varargin_1;
  double varargout_1_tmp[2];
  int a__1;
  int colNnz;
  int i;
  int idx;
  int overflow;
  boolean_T b_overflow;
  internal::b_bigProduct(m, n, &a__1, &overflow);
  if (overflow == 0) {
    a__1 = m * n;
    i = varargin_1.size(1) - 1;
    for (overflow = 0; overflow <= i; overflow++) {
      double b_d;
      b_d = varargin_1[overflow];
      if ((!(std::floor(b_d) == b_d)) || std::isinf(b_d)) {
        ec_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
      }
      if (!(b_d <= a__1)) {
        rtErrorWithMessageID(static_cast<long long>(b_d), a__1,
                             ic_emlrtRTEI.fName, ic_emlrtRTEI.lineNo);
      }
    }
  } else {
    i = varargin_1.size(1) - 1;
    for (overflow = 0; overflow <= i; overflow++) {
      double b_d;
      b_d = varargin_1[overflow];
      if ((!(std::floor(b_d) == b_d)) || std::isinf(b_d)) {
        ec_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
      }
      if (!(b_d <= 2.147483647E+9)) {
        rtErrorWithMessageID(static_cast<long long>(b_d), MAX_int32_T,
                             ic_emlrtRTEI.fName, ic_emlrtRTEI.lineNo);
      }
    }
  }
  i = varargin_1.size(1) - 1;
  varargout_1_tmp[0] = m;
  varargout_1_tmp[1] = n;
  a__1 = varargin_1.size(1);
  b_varargin_1.set_size(1, varargin_1.size(1));
  for (overflow = 0; overflow < a__1; overflow++) {
    b_varargin_1[overflow] = varargin_1[overflow];
  }
  double c_varargin_1[2];
  c_varargin_1[0] = 1.0;
  c_varargin_1[1] = b_varargin_1.size(1);
  internal::indexShapeCheck(varargout_1_tmp, c_varargin_1);
  s->n = varargin_1.size(1);
  if (varargin_1.size(1) + 1 < 0) {
    rtNonNegativeError(static_cast<double>(varargin_1.size(1) + 1),
                       &r_emlrtDCI);
  }
  s->d.set_size(0);
  s->rowidx.set_size(0);
  if (varargin_1.size(1) + 1 < 0) {
    rtNonNegativeError(static_cast<double>(varargin_1.size(1) + 1),
                       &t_emlrtDCI);
  }
  s->colidx.set_size(varargin_1.size(1) + 1);
  if (varargin_1.size(1) + 1 < 0) {
    rtNonNegativeError(static_cast<double>(varargin_1.size(1) + 1),
                       &t_emlrtDCI);
  }
  a__1 = varargin_1.size(1) + 1;
  for (overflow = 0; overflow < a__1; overflow++) {
    s->colidx[overflow] = 0;
  }
  s->colidx[0] = 1;
  colNnz = 1;
  b_overflow = (varargin_1.size(1) > 2147483646);
  if (b_overflow) {
    check_forloop_overflow_error();
  }
  for (int cidx{0}; cidx <= i; cidx++) {
    ind2sub_indexClass(varargout_1_tmp, static_cast<int>(varargin_1[cidx]),
                       &a__1, &overflow);
    sparse_locBsearch(rowidx, static_cast<double>(a__1), colidx[overflow - 1],
                      colidx[overflow], &idx, &b_overflow);
    if (b_overflow) {
      overflow = s->d.size(0);
      s->d.set_size(s->d.size(0) + 1);
      s->d[overflow] = d[idx - 1];
      overflow = s->rowidx.size(0);
      s->rowidx.set_size(s->rowidx.size(0) + 1);
      s->rowidx[overflow] = 1;
      colNnz++;
    }
    s->colidx[cidx + 1] = colNnz;
  }
  if (s->d.size(0) == 0) {
    s->d.set_size(1);
    s->d[0] = false;
    s->rowidx.set_size(1);
    s->rowidx[0] = 0;
  }
}

//
// Arguments    : c_sparse *s
// Return Type  : void
//
void b_sparse::parenReference(c_sparse *s) const
{
  int idx;
  boolean_T found;
  if (n < 1) {
    rtErrorWithMessageID(static_cast<long long>(1LL), static_cast<int>(0),
                         ic_emlrtRTEI.fName, ic_emlrtRTEI.lineNo);
  }
  s->colidx.set_size(2);
  s->colidx[0] = 1;
  s->colidx[1] = 1;
  sparse_locBsearch(rowidx, 1.0, colidx[0], colidx[1], &idx, &found);
  if (found) {
    s->d.set_size(1);
    s->d[0] = d[idx - 1];
    s->rowidx.set_size(1);
    s->rowidx[0] = 1;
    s->colidx[1] = 2;
  } else {
    s->d.set_size(1);
    s->d[0] = 0.0;
    s->rowidx.set_size(1);
    s->rowidx[0] = 0;
  }
}

//
// Arguments    : g_sparse *s
// Return Type  : void
//
void sparse::parenReference(g_sparse *s) const
{
  int i;
  int nd_tmp;
  int numalloc;
  if (n < 1) {
    rtErrorWithMessageID(static_cast<long long>(1LL), static_cast<int>(0),
                         ic_emlrtRTEI.fName, ic_emlrtRTEI.lineNo);
  }
  nd_tmp = colidx[1] - colidx[0];
  if ((nd_tmp > m) && (m != 0)) {
    i_rtErrorWithMessageID(qc_emlrtRTEI.fName, qc_emlrtRTEI.lineNo);
  }
  if (m < 0) {
    ac_rtErrorWithMessageID(lc_emlrtRTEI.fName, lc_emlrtRTEI.lineNo);
  }
  if (m >= MAX_int32_T) {
    rc_rtErrorWithMessageID(jc_emlrtRTEI.fName, jc_emlrtRTEI.lineNo);
  }
  s->m = m;
  if (nd_tmp < 0) {
    ac_rtErrorWithMessageID(lc_emlrtRTEI.fName, lc_emlrtRTEI.lineNo);
  }
  if (nd_tmp >= MAX_int32_T) {
    rc_rtErrorWithMessageID(jc_emlrtRTEI.fName, jc_emlrtRTEI.lineNo);
  }
  if (nd_tmp >= 1) {
    numalloc = nd_tmp;
  } else {
    numalloc = 1;
  }
  s->d.set_size(numalloc);
  s->maxnz = numalloc;
  s->colidx.set_size(2);
  s->rowidx.set_size(numalloc);
  for (i = 0; i < numalloc; i++) {
    s->d[i] = 0.0;
    s->rowidx[i] = 0;
  }
  s->colidx[0] = 1;
  s->colidx[1] = 1;
  if (nd_tmp != 0) {
    numalloc = colidx[0] - 2;
    for (int k{0}; k < nd_tmp; k++) {
      i = (numalloc + k) + 1;
      s->d[k] = d[i];
      s->rowidx[k] = rowidx[i];
    }
    s->colidx[1] = nd_tmp + 1;
  }
}

} // namespace coder

//
// File trailer for sparse1.cpp
//
// [EOF]
//
