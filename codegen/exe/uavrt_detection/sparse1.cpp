//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: sparse1.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 22-Oct-2022 15:24:58
//

// Include Files
#include "sparse1.h"
#include "anonymous_function.h"
#include "locBsearch.h"
#include "rt_nonfinite.h"
#include "sparse.h"
#include "uavrt_detection_internal_types.h"
#include "uavrt_detection_rtwutil.h"
#include "coder_array.h"
#include <cstddef>
#include <cstring>

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
  array<int, 1U> rowidxt;
  array<boolean_T, 1U> dt;
  int highOrderA;
  int highOrderB;
  int lowOrderB;
  int overflow;
  int partialResults_idx_0_tmp;
  int partialResults_idx_1;
  int tmp;
  rowidxt.set_size(b_this->rowidx.size(0));
  partialResults_idx_1 = b_this->rowidx.size(0);
  for (highOrderA = 0; highOrderA < partialResults_idx_1; highOrderA++) {
    rowidxt[highOrderA] = b_this->rowidx[highOrderA];
  }
  dt.set_size(b_this->d.size(0));
  partialResults_idx_1 = b_this->d.size(0);
  for (highOrderA = 0; highOrderA < partialResults_idx_1; highOrderA++) {
    dt[highOrderA] = b_this->d[highOrderA];
  }
  highOrderA = b_this->m >> 16;
  partialResults_idx_1 = b_this->m & 65535;
  highOrderB = b_this->n >> 16;
  lowOrderB = b_this->n & 65535;
  partialResults_idx_0_tmp = partialResults_idx_1 * lowOrderB;
  tmp = partialResults_idx_1 * highOrderB;
  partialResults_idx_1 = tmp << 16;
  overflow = tmp >> 16;
  if (overflow <= 0) {
    tmp = highOrderA * lowOrderB;
    overflow = tmp >> 16;
    if (overflow <= 0) {
      overflow = highOrderA * highOrderB;
      if (overflow <= 0) {
        if (partialResults_idx_0_tmp > MAX_int32_T - partialResults_idx_1) {
          partialResults_idx_1 =
              (partialResults_idx_0_tmp + partialResults_idx_1) - MAX_int32_T;
          overflow = 1;
        } else {
          partialResults_idx_1 += partialResults_idx_0_tmp;
        }
        if (partialResults_idx_1 > MAX_int32_T - (tmp << 16)) {
          overflow++;
        }
      }
    }
  }
  if (overflow == 0) {
    partialResults_idx_1 = b_this->m * b_this->n;
    if (numAllocRequested <= partialResults_idx_1) {
      partialResults_idx_1 = numAllocRequested;
    }
    if (partialResults_idx_1 <= 1) {
      partialResults_idx_1 = 1;
    }
  } else if (numAllocRequested <= 1) {
    partialResults_idx_1 = 1;
  } else {
    partialResults_idx_1 = numAllocRequested;
  }
  b_this->rowidx.set_size(partialResults_idx_1);
  b_this->d.set_size(partialResults_idx_1);
  for (highOrderA = 0; highOrderA < partialResults_idx_1; highOrderA++) {
    b_this->rowidx[highOrderA] = 0;
    b_this->d[highOrderA] = false;
  }
  b_this->maxnz = partialResults_idx_1;
  for (partialResults_idx_1 = 0; partialResults_idx_1 < ub1;
       partialResults_idx_1++) {
    b_this->rowidx[partialResults_idx_1] = rowidxt[partialResults_idx_1];
    b_this->d[partialResults_idx_1] = dt[partialResults_idx_1];
  }
  for (partialResults_idx_1 = lb2; partialResults_idx_1 <= ub2;
       partialResults_idx_1++) {
    b_this->rowidx[partialResults_idx_1] = rowidxt[partialResults_idx_1 - 1];
    b_this->d[partialResults_idx_1] = dt[partialResults_idx_1 - 1];
  }
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
  int i;
  b_m = a.size(0);
  b_n = n - 1;
  c.set_size(a.size(0), n);
  aoff = a.size(0) * n;
  for (i = 0; i < aoff; i++) {
    c[i] = 0.0;
  }
  if ((a.size(1) != 0) && (a.size(0) != 0) && (n != 0) &&
      (colidx[colidx.size(0) - 1] - 1 != 0)) {
    if (a.size(0) == 1) {
      i = n;
      for (int mend{0}; mend < i; mend++) {
        double cd;
        int aidx_tmp;
        cd = 0.0;
        aoff = colidx[mend + 1] - 1;
        aidx_tmp = colidx[mend];
        for (int cidx{aidx_tmp}; cidx <= aoff; cidx++) {
          cd += static_cast<double>(d[cidx - 1]) * a[rowidx[cidx - 1] - 1];
        }
        c[mend] = cd;
      }
    } else if (a.size(0) >= 4) {
      for (int ccol{0}; ccol <= b_n; ccol++) {
        int bpend;
        int coff;
        coff = ccol * c.size(0);
        bpend = colidx[ccol + 1] - 1;
        i = colidx[ccol];
        for (int bp{i}; bp <= bpend; bp++) {
          int aidx_tmp;
          int aoff_tmp;
          int mend;
          boolean_T bd;
          aoff_tmp = rowidx[bp - 1] - 1;
          aoff = aoff_tmp * a.size(0);
          bd = d[bp - 1];
          mend = (b_m / 4) << 2;
          for (int crow{1}; crow <= mend; crow += 4) {
            int cidx;
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
          aidx_tmp = mend + 1;
          for (int crow{aidx_tmp}; crow <= b_m; crow++) {
            aoff = (crow + coff) - 1;
            c[aoff] = c[aoff] + a[(crow + a.size(0) * aoff_tmp) - 1] *
                                    static_cast<double>(bd);
          }
        }
      }
    } else {
      for (int ccol{0}; ccol <= b_n; ccol++) {
        int bpend;
        bpend = colidx[ccol + 1] - 1;
        i = colidx[ccol];
        for (int bp{i}; bp <= bpend; bp++) {
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
// Arguments    : c_sparse *out
// Return Type  : void
//
void c_sparse::b_not(c_sparse *out) const
{
  int curPosition;
  int i;
  int larger;
  int writeStart;
  if (n < 1) {
    larger = 0;
  } else {
    larger = (n - colidx[colidx.size(0) - 1]) + 1;
    if (larger == 0) {
      larger = 0;
    }
  }
  writeStart = larger;
  out->n = n;
  if (larger < 1) {
    writeStart = 1;
  }
  out->d.set_size(writeStart);
  out->rowidx.set_size(writeStart);
  out->colidx.set_size(n + 1);
  if (larger < 1) {
    larger = 0;
  }
  for (i = 0; i < larger; i++) {
    out->d[i] = true;
  }
  curPosition = 1;
  i = n;
  for (int c{0}; c < i; c++) {
    out->colidx[c] = curPosition;
    larger = colidx[c + 1];
    if (colidx[c] == larger) {
      out->rowidx[curPosition - 1] = 1;
      curPosition++;
    } else {
      larger = rowidx[larger - 2];
      writeStart = larger + 1;
      for (int writeRow{writeStart}; writeRow < 2; writeRow++) {
        out->rowidx[((curPosition + writeRow) - larger) - 2] = 1;
      }
      curPosition = (curPosition - larger) + 1;
    }
  }
  out->colidx[n] = curPosition;
}

//
// Arguments    : const e_sparse *b
//                c_sparse *s
// Return Type  : void
//
void b_sparse::eq(const e_sparse *b, c_sparse *s) const
{
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
    int currRowIdx;
    int i;
    int idx;
    currRowIdx = colidx[colidx.size(0) - 1];
    if (colidx[colidx.size(0) - 1] - 1 < 1) {
      b_n = 0;
    } else {
      b_n = colidx[colidx.size(0) - 1] - 1;
    }
    tmpd.set_size(b_n);
    for (i = 0; i < b_n; i++) {
      tmpd[i] = (d[i] == uniOp.workspace.sb);
    }
    s->n = n;
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
    i = n;
    for (int col{0}; col < i; col++) {
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
    for (b_n = 0; b_n <= currRowIdx - 2; b_n++) {
      s->d[b_n] = tmpd[b_n];
    }
    idx = 1;
    i = colidx.size(0);
    for (int col{0}; col <= i - 2; col++) {
      b_n = s->colidx[col];
      s->colidx[col] = idx;
      while (b_n < s->colidx[col + 1]) {
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
    int i;
    S.set_size(1, n);
    b_n = n;
    for (i = 0; i < b_n; i++) {
      S[i] = true;
    }
    b_n = n;
    for (int col{0}; col < b_n; col++) {
      int currRowIdx;
      i = colidx[col];
      currRowIdx = colidx[col + 1] - 1;
      for (int idx{i}; idx <= currRowIdx; idx++) {
        S[col] = (d[idx - 1] == uniOp.workspace.sb);
      }
    }
    i_sparse(S, s);
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
  int i;
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
  b_I->colidx.set_size(b_n + 1);
  for (nzmax = 0; nzmax < ndiag; nzmax++) {
    b_I->d[nzmax] = 1.0;
    b_I->rowidx[nzmax] = nzmax + 1;
  }
  b_I->colidx[0] = 1;
  for (int c{2}; c <= ndiag; c++) {
    b_I->colidx[c - 1] = c;
  }
  nzmax = ndiag + 1;
  i = b_n + 1;
  for (int c{nzmax}; c <= i; c++) {
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
// Arguments    : f_sparse *y
// Return Type  : void
//
void sparse::logical(f_sparse *y) const
{
  int i;
  int numalloc;
  y->m = m;
  y->n = n;
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
  i = n;
  for (numalloc = 0; numalloc < i; numalloc++) {
    y->colidx[numalloc + 1] = 1;
  }
  i = y->colidx.size(0);
  for (numalloc = 0; numalloc <= i - 2; numalloc++) {
    y->colidx[numalloc] = 1;
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
  int apend;
  int b_n;
  int i;
  b_n = b.size(1);
  c.set_size(m, b.size(1));
  apend = m * b.size(1);
  for (i = 0; i < apend; i++) {
    c[i] = 0.0;
  }
  if ((n != 0) && (m != 0) && (b.size(1) != 0) &&
      (colidx[colidx.size(0) - 1] - 1 != 0)) {
    if (b.size(1) == 1) {
      i = n;
      for (int acol{0}; acol < i; acol++) {
        double bc;
        int i1;
        int nap;
        bc = b[acol];
        i1 = colidx[acol];
        apend = colidx[acol + 1];
        nap = apend - colidx[acol];
        if (nap >= 4) {
          int apend1;
          apend1 = (apend - nap) + ((nap / 4) << 2);
          for (int ap{i1}; ap <= apend1 - 1; ap += 4) {
            nap = rowidx[ap - 1] - 1;
            c[nap] = c[nap] + static_cast<double>(d[ap - 1]) * bc;
            c[rowidx[ap] - 1] =
                c[rowidx[ap] - 1] + static_cast<double>(d[ap]) * bc;
            nap = rowidx[ap + 1] - 1;
            c[nap] = c[nap] + static_cast<double>(d[ap + 1]) * bc;
            nap = rowidx[ap + 2] - 1;
            c[nap] = c[nap] + static_cast<double>(d[ap + 2]) * bc;
          }
          nap = colidx[acol + 1] - 1;
          for (int ap{apend1}; ap <= nap; ap++) {
            apend = rowidx[ap - 1] - 1;
            c[apend] = c[apend] + static_cast<double>(d[ap - 1]) * bc;
          }
        } else {
          apend--;
          for (int ap{i1}; ap <= apend; ap++) {
            nap = rowidx[ap - 1] - 1;
            c[nap] = c[nap] + static_cast<double>(d[ap - 1]) * bc;
          }
        }
      }
    } else {
      i = n;
      for (int j{0}; j < b_n; j++) {
        int coff;
        coff = j * c.size(0) - 1;
        for (int acol{0}; acol < i; acol++) {
          double bc;
          int i1;
          int nap;
          bc = b[acol + b.size(0) * j];
          i1 = colidx[acol];
          apend = colidx[acol + 1];
          nap = apend - colidx[acol];
          if (nap >= 4) {
            int apend1;
            apend1 = (apend - nap) + ((nap / 4) << 2);
            for (int ap{i1}; ap <= apend1 - 1; ap += 4) {
              nap = rowidx[ap - 1] + coff;
              c[nap] = c[nap] + static_cast<double>(d[ap - 1]) * bc;
              nap = rowidx[ap] + coff;
              c[nap] = c[nap] + static_cast<double>(d[ap]) * bc;
              nap = rowidx[ap + 1] + coff;
              c[nap] = c[nap] + static_cast<double>(d[ap + 1]) * bc;
              nap = rowidx[ap + 2] + coff;
              c[nap] = c[nap] + static_cast<double>(d[ap + 2]) * bc;
            }
            nap = colidx[acol + 1] - 1;
            for (int ap{apend1}; ap <= nap; ap++) {
              apend = rowidx[ap - 1] - 1;
              c[apend + c.size(0) * j] = c[apend + c.size(0) * j] +
                                         static_cast<double>(d[ap - 1]) * bc;
            }
          } else {
            apend--;
            for (int ap{i1}; ap <= apend; ap++) {
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
  int i;
  b_m = a.size(0);
  b_n = n - 1;
  c.set_size(a.size(0), n);
  aoff = a.size(0) * n;
  for (i = 0; i < aoff; i++) {
    c[i] = 0.0;
  }
  if ((a.size(1) != 0) && (a.size(0) != 0) && (n != 0) &&
      (colidx[colidx.size(0) - 1] - 1 != 0)) {
    if (a.size(0) == 1) {
      i = n;
      for (int mend{0}; mend < i; mend++) {
        double bd;
        int aidx_tmp;
        bd = 0.0;
        aoff = colidx[mend + 1] - 1;
        aidx_tmp = colidx[mend];
        for (int cidx{aidx_tmp}; cidx <= aoff; cidx++) {
          bd += d[cidx - 1] * a[rowidx[cidx - 1] - 1];
        }
        c[mend] = bd;
      }
    } else if (a.size(0) >= 4) {
      for (int ccol{0}; ccol <= b_n; ccol++) {
        int bpend;
        int coff;
        coff = ccol * c.size(0);
        bpend = colidx[ccol + 1] - 1;
        i = colidx[ccol];
        for (int bp{i}; bp <= bpend; bp++) {
          double bd;
          int aidx_tmp;
          int aoff_tmp;
          int mend;
          aoff_tmp = rowidx[bp - 1] - 1;
          aoff = aoff_tmp * a.size(0);
          bd = d[bp - 1];
          mend = (b_m / 4) << 2;
          for (int crow{1}; crow <= mend; crow += 4) {
            int cidx;
            cidx = crow + coff;
            aidx_tmp = crow + aoff;
            c[cidx - 1] = c[cidx - 1] + a[aidx_tmp - 1] * bd;
            c[cidx] = c[cidx] + a[aidx_tmp] * bd;
            c[cidx + 1] = c[cidx + 1] + a[aidx_tmp + 1] * bd;
            c[cidx + 2] = c[cidx + 2] + a[aidx_tmp + 2] * bd;
          }
          aidx_tmp = mend + 1;
          for (int crow{aidx_tmp}; crow <= b_m; crow++) {
            aoff = (crow + coff) - 1;
            c[aoff] = c[aoff] + a[(crow + a.size(0) * aoff_tmp) - 1] * bd;
          }
        }
      }
    } else {
      for (int ccol{0}; ccol <= b_n; ccol++) {
        int bpend;
        bpend = colidx[ccol + 1] - 1;
        i = colidx[ccol];
        for (int bp{i}; bp <= bpend; bp++) {
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
// Arguments    : const h_sparse *rhs
//                const ::coder::array<double, 2U> &varargin_1
// Return Type  : void
//
void f_sparse::parenAssign(const h_sparse *rhs,
                           const ::coder::array<double, 2U> &varargin_1)
{
  d_sparse s;
  int idx;
  int nidx;
  int varargout_1_tmp_idx_0;
  boolean_T rhsv;
  varargout_1_tmp_idx_0 = rhs->m;
  nidx = varargin_1.size(1);
  for (int k{0}; k < nidx; k++) {
    int b_vk;
    int i;
    int siz_idx_0;
    int vk;
    siz_idx_0 = m;
    vk = div_s32(static_cast<int>(varargin_1[k]) - 1, siz_idx_0);
    s.colidx.set_size(2);
    s.colidx[0] = 1;
    s.colidx[1] = 1;
    b_vk = div_s32(k, varargout_1_tmp_idx_0);
    sparse_locBsearch(
        rhs->rowidx,
        static_cast<double>((k - b_vk * varargout_1_tmp_idx_0) + 1),
        rhs->colidx[b_vk], rhs->colidx[b_vk + 1], &idx, &rhsv);
    if (rhsv) {
      s.d.set_size(1);
      s.d[0] = rhs->d[idx - 1];
      s.colidx[1] = 2;
    } else {
      s.d.set_size(1);
      s.d[0] = false;
    }
    rhsv = false;
    b_vk = s.colidx[1] - 1;
    i = s.colidx[0];
    for (idx = i; idx <= b_vk; idx++) {
      rhsv = s.d[idx - 1];
    }
    parenAssign2D(
        rhsv,
        static_cast<double>(static_cast<int>(varargin_1[k]) - vk * siz_idx_0),
        static_cast<double>(vk + 1));
  }
}

//
// Arguments    : const ::coder::array<double, 2U> &rhs
//                const ::coder::array<double, 2U> &varargin_1
// Return Type  : void
//
void f_sparse::parenAssign(const ::coder::array<double, 2U> &rhs,
                           const ::coder::array<double, 2U> &varargin_1)
{
  int nidx;
  int vidx;
  boolean_T thisv;
  nidx = varargin_1.size(1);
  for (int k{0}; k < nidx; k++) {
    double b_d;
    int siz_idx_0;
    int vk;
    siz_idx_0 = m;
    b_d = varargin_1[k];
    vk = div_s32(static_cast<int>(b_d) - 1, siz_idx_0);
    siz_idx_0 = static_cast<int>(b_d) - vk * siz_idx_0;
    b_sparse_locBsearch(rowidx, siz_idx_0, colidx[vk], colidx[vk + 1], &vidx,
                        &thisv);
    if (thisv) {
      thisv = d[vidx - 1];
    } else {
      thisv = false;
    }
    if (thisv || (!(rhs[k] == 0.0))) {
      if (thisv && (rhs[k] != 0.0)) {
        d[vidx - 1] = true;
      } else if (!thisv) {
        int nelem;
        if (colidx[colidx.size(0) - 1] - 1 == maxnz) {
          sparse::b_realloc(this, colidx[colidx.size(0) - 1] + 9, vidx,
                            vidx + 1, colidx[colidx.size(0) - 1] - 1);
          rowidx[vidx] = siz_idx_0;
          d[vidx] = (rhs[k] != 0.0);
        } else {
          nelem = (colidx[colidx.size(0) - 1] - vidx) - 1;
          if (nelem > 0) {
            std::memmove((void *)&rowidx[vidx + 1], (void *)&rowidx[vidx],
                         (unsigned int)((size_t)nelem * sizeof(int)));
            std::memmove((void *)&d[vidx + 1], (void *)&d[vidx],
                         (unsigned int)((size_t)nelem * sizeof(boolean_T)));
          }
          d[vidx] = (rhs[k] != 0.0);
          rowidx[vidx] = siz_idx_0;
        }
        siz_idx_0 = vk + 2;
        vidx = n + 1;
        for (nelem = siz_idx_0; nelem <= vidx; nelem++) {
          colidx[nelem - 1] = colidx[nelem - 1] + 1;
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
        siz_idx_0 = vk + 2;
        vidx = n + 1;
        for (nelem = siz_idx_0; nelem <= vidx; nelem++) {
          colidx[nelem - 1] = colidx[nelem - 1] - 1;
        }
      }
    }
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
      for (int k{vidx}; k <= nelem; k++) {
        colidx[k - 1] = colidx[k - 1] - 1;
      }
    }
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
  nd_tmp = colidx[1] - colidx[0];
  s->m = m;
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
  int numalloc;
  int sn;
  sn = varargin_2.size(0) - 1;
  nd = 0;
  for (int cidx{0}; cidx <= sn; cidx++) {
    numalloc = static_cast<int>(varargin_2[cidx]);
    nd = (nd + colidx[numalloc]) - colidx[numalloc - 1];
  }
  s->m = m;
  s->n = varargin_2.size(0);
  if (nd >= 1) {
    numalloc = nd;
  } else {
    numalloc = 1;
  }
  s->d.set_size(numalloc);
  s->maxnz = numalloc;
  s->colidx.set_size(varargin_2.size(0) + 1);
  s->colidx[0] = 1;
  s->rowidx.set_size(numalloc);
  for (i = 0; i < numalloc; i++) {
    s->d[i] = 0.0;
    s->rowidx[i] = 0;
  }
  i = varargin_2.size(0);
  for (numalloc = 0; numalloc < i; numalloc++) {
    s->colidx[numalloc + 1] = 1;
  }
  s->fillIn();
  if (nd != 0) {
    int outIdx;
    outIdx = 0;
    for (int cidx{0}; cidx <= sn; cidx++) {
      int colstart_tmp;
      numalloc = static_cast<int>(varargin_2[cidx]);
      colstart_tmp = colidx[numalloc - 1];
      numalloc = colidx[numalloc] - colstart_tmp;
      for (int k{0}; k < numalloc; k++) {
        i = (colstart_tmp + k) - 1;
        nd = outIdx + k;
        s->d[nd] = d[i];
        s->rowidx[nd] = rowidx[i];
      }
      outIdx += numalloc;
      s->colidx[cidx + 1] = s->colidx[cidx] + numalloc;
    }
  }
}

//
// Arguments    : const ::coder::array<double, 2U> &varargin_1
//                c_sparse *s
// Return Type  : void
//
void f_sparse::parenReference(const ::coder::array<double, 2U> &varargin_1,
                              c_sparse *s) const
{
  int colNnz;
  int idx;
  int loop_ub;
  int ncol;
  int varargout_1_tmp_idx_0;
  int vk;
  boolean_T found;
  ncol = varargin_1.size(1);
  varargout_1_tmp_idx_0 = m;
  s->n = varargin_1.size(1);
  s->d.set_size(0);
  s->rowidx.set_size(0);
  s->colidx.set_size(varargin_1.size(1) + 1);
  loop_ub = varargin_1.size(1);
  for (vk = 0; vk <= loop_ub; vk++) {
    s->colidx[vk] = 0;
  }
  s->colidx[0] = 1;
  colNnz = 1;
  for (int cidx{0}; cidx < ncol; cidx++) {
    loop_ub = static_cast<int>(varargin_1[cidx]);
    vk = div_s32(loop_ub - 1, varargout_1_tmp_idx_0);
    sparse_locBsearch(rowidx,
                      static_cast<double>(loop_ub - vk * varargout_1_tmp_idx_0),
                      colidx[vk], colidx[vk + 1], &idx, &found);
    if (found) {
      vk = s->d.size(0);
      s->d.set_size(s->d.size(0) + 1);
      s->d[vk] = d[idx - 1];
      vk = s->rowidx.size(0);
      s->rowidx.set_size(s->rowidx.size(0) + 1);
      s->rowidx[vk] = 1;
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

} // namespace coder

//
// File trailer for sparse1.cpp
//
// [EOF]
//
