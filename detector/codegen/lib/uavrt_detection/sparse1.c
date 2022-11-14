/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: sparse1.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "sparse1.h"
#include "fillIn.h"
#include "locBsearch.h"
#include "parenAssign2D.h"
#include "rt_nonfinite.h"
#include "sparse.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include <stddef.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : c_sparse *this
 *                const emxArray_real_T *rhs
 *                const emxArray_real_T *varargin_1
 * Return Type  : void
 */
void b_sparse_parenAssign(c_sparse *this, const emxArray_real_T *rhs,
                          const emxArray_real_T *varargin_1)
{
  const double *rhs_data;
  const double *varargin_1_data;
  int k;
  int nelem;
  int nidx;
  int vidx;
  bool thisv;
  varargin_1_data = varargin_1->data;
  rhs_data = rhs->data;
  nidx = varargin_1->size[1];
  for (k = 0; k < nidx; k++) {
    double d;
    int siz_idx_0;
    int vk;
    siz_idx_0 = this->m;
    d = varargin_1_data[k];
    vk = div_s32((int)d - 1, siz_idx_0);
    siz_idx_0 = (int)d - vk * siz_idx_0;
    b_sparse_locBsearch(this->rowidx, siz_idx_0, this->colidx->data[vk],
                        this->colidx->data[vk + 1], &vidx, &thisv);
    if (thisv) {
      thisv = this->d->data[vidx - 1];
    } else {
      thisv = false;
    }
    if (thisv || (!(rhs_data[k] == 0.0))) {
      if (thisv && (rhs_data[k] != 0.0)) {
        this->d->data[vidx - 1] = true;
      } else if (!thisv) {
        if (this->colidx->data[this->colidx->size[0] - 1] - 1 == this->maxnz) {
          b_realloc(this, this->colidx->data[this->colidx->size[0] - 1] + 9,
                    vidx, vidx + 1,
                    this->colidx->data[this->colidx->size[0] - 1] - 1);
          this->rowidx->data[vidx] = siz_idx_0;
          this->d->data[vidx] = (rhs_data[k] != 0.0);
        } else {
          nelem = (this->colidx->data[this->colidx->size[0] - 1] - vidx) - 1;
          if (nelem > 0) {
            memmove((void *)&this->rowidx->data[vidx + 1],
                    (void *)&this->rowidx->data[vidx],
                    (size_t)nelem * sizeof(int));
            memmove((void *)&this->d->data[vidx + 1],
                    (void *)&this->d->data[vidx], (size_t)nelem * sizeof(bool));
          }
          this->d->data[vidx] = (rhs_data[k] != 0.0);
          this->rowidx->data[vidx] = siz_idx_0;
        }
        siz_idx_0 = vk + 2;
        vidx = this->n + 1;
        for (nelem = siz_idx_0; nelem <= vidx; nelem++) {
          this->colidx->data[nelem - 1]++;
        }
      } else {
        nelem = (this->colidx->data[this->colidx->size[0] - 1] - vidx) - 1;
        if (nelem > 0) {
          memmove((void *)&this->rowidx->data[vidx - 1],
                  (void *)&this->rowidx->data[vidx],
                  (size_t)nelem * sizeof(int));
          memmove((void *)&this->d->data[vidx - 1],
                  (void *)&this->d->data[vidx], (size_t)nelem * sizeof(bool));
        }
        siz_idx_0 = vk + 2;
        vidx = this->n + 1;
        for (nelem = siz_idx_0; nelem <= vidx; nelem++) {
          this->colidx->data[nelem - 1]--;
        }
      }
    }
  }
}

/*
 * Arguments    : const emxArray_real_T *this_d
 *                const emxArray_int32_T *this_colidx
 *                const emxArray_int32_T *this_rowidx
 *                int this_m
 *                emxArray_real_T *s_d
 *                emxArray_int32_T *s_colidx
 *                emxArray_int32_T *s_rowidx
 *                int *s_m
 *                int *s_maxnz
 * Return Type  : void
 */
void b_sparse_parenReference(const emxArray_real_T *this_d,
                             const emxArray_int32_T *this_colidx,
                             const emxArray_int32_T *this_rowidx, int this_m,
                             emxArray_real_T *s_d, emxArray_int32_T *s_colidx,
                             emxArray_int32_T *s_rowidx, int *s_m, int *s_maxnz)
{
  const double *this_d_data;
  double *s_d_data;
  const int *this_colidx_data;
  const int *this_rowidx_data;
  int colstart;
  int k;
  int nd_tmp;
  int numalloc;
  int *s_colidx_data;
  int *s_rowidx_data;
  this_rowidx_data = this_rowidx->data;
  this_colidx_data = this_colidx->data;
  this_d_data = this_d->data;
  nd_tmp = this_colidx_data[1] - this_colidx_data[0];
  if (nd_tmp >= 1) {
    numalloc = nd_tmp;
  } else {
    numalloc = 1;
  }
  colstart = s_d->size[0];
  s_d->size[0] = numalloc;
  emxEnsureCapacity_real_T(s_d, colstart);
  s_d_data = s_d->data;
  for (colstart = 0; colstart < numalloc; colstart++) {
    s_d_data[colstart] = 0.0;
  }
  colstart = s_colidx->size[0];
  s_colidx->size[0] = 2;
  emxEnsureCapacity_int32_T(s_colidx, colstart);
  s_colidx_data = s_colidx->data;
  colstart = s_rowidx->size[0];
  s_rowidx->size[0] = numalloc;
  emxEnsureCapacity_int32_T(s_rowidx, colstart);
  s_rowidx_data = s_rowidx->data;
  for (colstart = 0; colstart < numalloc; colstart++) {
    s_rowidx_data[colstart] = 0;
  }
  s_colidx_data[0] = 1;
  s_colidx_data[1] = 1;
  if (nd_tmp != 0) {
    colstart = this_colidx_data[0] - 2;
    for (k = 0; k < nd_tmp; k++) {
      int s_d_tmp;
      s_d_tmp = (colstart + k) + 1;
      s_d_data[k] = this_d_data[s_d_tmp];
      s_rowidx_data[k] = this_rowidx_data[s_d_tmp];
    }
    s_colidx_data[1] = nd_tmp + 1;
  }
  *s_m = this_m;
  *s_maxnz = numalloc;
}

/*
 * Arguments    : const emxArray_real_T *this_d
 *                const emxArray_int32_T *this_colidx
 *                const emxArray_int32_T *this_rowidx
 *                int this_m
 *                const emxArray_real_T *varargin_2
 *                d_sparse *s
 * Return Type  : void
 */
void c_sparse_parenReference(const emxArray_real_T *this_d,
                             const emxArray_int32_T *this_colidx,
                             const emxArray_int32_T *this_rowidx, int this_m,
                             const emxArray_real_T *varargin_2, d_sparse *s)
{
  const double *this_d_data;
  const double *varargin_2_data;
  const int *this_colidx_data;
  const int *this_rowidx_data;
  int cidx;
  int i;
  int k;
  int nd;
  int numalloc;
  int sn;
  varargin_2_data = varargin_2->data;
  this_rowidx_data = this_rowidx->data;
  this_colidx_data = this_colidx->data;
  this_d_data = this_d->data;
  sn = varargin_2->size[0] - 1;
  nd = 0;
  for (cidx = 0; cidx <= sn; cidx++) {
    numalloc = (int)varargin_2_data[cidx];
    nd = (nd + this_colidx_data[numalloc]) - this_colidx_data[numalloc - 1];
  }
  s->m = this_m;
  s->n = varargin_2->size[0];
  if (nd >= 1) {
    numalloc = nd;
  } else {
    numalloc = 1;
  }
  i = s->d->size[0];
  s->d->size[0] = numalloc;
  emxEnsureCapacity_real_T(s->d, i);
  for (i = 0; i < numalloc; i++) {
    s->d->data[i] = 0.0;
  }
  i = s->colidx->size[0];
  s->colidx->size[0] = varargin_2->size[0] + 1;
  emxEnsureCapacity_int32_T(s->colidx, i);
  s->colidx->data[0] = 1;
  i = s->rowidx->size[0];
  s->rowidx->size[0] = numalloc;
  emxEnsureCapacity_int32_T(s->rowidx, i);
  for (i = 0; i < numalloc; i++) {
    s->rowidx->data[i] = 0;
  }
  i = varargin_2->size[0];
  for (numalloc = 0; numalloc < i; numalloc++) {
    s->colidx->data[numalloc + 1] = 1;
  }
  sparse_fillIn(s);
  if (nd != 0) {
    int outIdx;
    outIdx = 0;
    for (cidx = 0; cidx <= sn; cidx++) {
      int colstart_tmp;
      numalloc = (int)varargin_2_data[cidx];
      colstart_tmp = this_colidx_data[numalloc - 1];
      numalloc = this_colidx_data[numalloc] - colstart_tmp;
      for (k = 0; k < numalloc; k++) {
        i = (colstart_tmp + k) - 1;
        nd = outIdx + k;
        s->d->data[nd] = this_d_data[i];
        s->rowidx->data[nd] = this_rowidx_data[i];
      }
      outIdx += numalloc;
      s->colidx->data[cidx + 1] = s->colidx->data[cidx] + numalloc;
    }
  }
}

/*
 * Arguments    : const emxArray_real_T *a_d
 *                const emxArray_int32_T *a_colidx
 *                const emxArray_int32_T *a_rowidx
 *                int a_n
 *                const emxArray_real_T *b_d
 *                const emxArray_int32_T *b_colidx
 *                emxArray_boolean_T *s_d
 *                emxArray_int32_T *s_colidx
 *                emxArray_int32_T *s_rowidx
 *                int *s_n
 * Return Type  : void
 */
void sparse_eq(const emxArray_real_T *a_d, const emxArray_int32_T *a_colidx,
               const emxArray_int32_T *a_rowidx, int a_n,
               const emxArray_real_T *b_d, const emxArray_int32_T *b_colidx,
               emxArray_boolean_T *s_d, emxArray_int32_T *s_colidx,
               emxArray_int32_T *s_rowidx, int *s_n)
{
  emxArray_boolean_T *S;
  const double *a_d_data;
  const double *b_d_data;
  double uniOp_workspace_sb;
  const int *a_colidx_data;
  const int *a_rowidx_data;
  const int *b_colidx_data;
  int c;
  int currRowIdx;
  int i;
  int idx;
  int numalloc;
  int *s_colidx_data;
  int *s_rowidx_data;
  bool *S_data;
  bool *s_d_data;
  b_colidx_data = b_colidx->data;
  b_d_data = b_d->data;
  a_rowidx_data = a_rowidx->data;
  a_colidx_data = a_colidx->data;
  a_d_data = a_d->data;
  if (b_colidx_data[b_colidx->size[0] - 1] - 1 > 0) {
    uniOp_workspace_sb = b_d_data[0];
  } else {
    uniOp_workspace_sb = 0.0;
  }
  if (!(uniOp_workspace_sb == 0.0)) {
    currRowIdx = a_colidx_data[a_colidx->size[0] - 1];
    if (a_colidx_data[a_colidx->size[0] - 1] - 1 < 1) {
      numalloc = 0;
    } else {
      numalloc = a_colidx_data[a_colidx->size[0] - 1] - 1;
    }
    emxInit_boolean_T(&S, 1);
    i = S->size[0];
    S->size[0] = numalloc;
    emxEnsureCapacity_boolean_T(S, i);
    S_data = S->data;
    for (i = 0; i < numalloc; i++) {
      S_data[i] = (a_d_data[i] == uniOp_workspace_sb);
    }
    *s_n = a_n;
    if (a_colidx_data[a_colidx->size[0] - 1] - 1 >= 1) {
      numalloc = a_colidx_data[a_colidx->size[0] - 1] - 2;
    } else {
      numalloc = 0;
    }
    i = s_d->size[0];
    s_d->size[0] = numalloc + 1;
    emxEnsureCapacity_boolean_T(s_d, i);
    s_d_data = s_d->data;
    for (i = 0; i <= numalloc; i++) {
      s_d_data[i] = false;
    }
    i = s_rowidx->size[0];
    s_rowidx->size[0] = numalloc + 1;
    emxEnsureCapacity_int32_T(s_rowidx, i);
    s_rowidx_data = s_rowidx->data;
    for (i = 0; i <= numalloc; i++) {
      s_rowidx_data[i] = 0;
    }
    if (a_colidx_data[a_colidx->size[0] - 1] - 1 < 1) {
      numalloc = 1;
    } else {
      numalloc = a_colidx_data[a_colidx->size[0] - 1];
    }
    for (i = 0; i <= numalloc - 2; i++) {
      s_rowidx_data[i] = a_rowidx_data[i];
    }
    i = s_colidx->size[0];
    s_colidx->size[0] = a_colidx->size[0];
    emxEnsureCapacity_int32_T(s_colidx, i);
    s_colidx_data = s_colidx->data;
    numalloc = a_colidx->size[0];
    for (i = 0; i < numalloc; i++) {
      s_colidx_data[i] = a_colidx_data[i];
    }
    for (numalloc = 0; numalloc <= currRowIdx - 2; numalloc++) {
      s_d_data[numalloc] = S_data[numalloc];
    }
    emxFree_boolean_T(&S);
    idx = 1;
    i = a_colidx->size[0];
    for (c = 0; c <= i - 2; c++) {
      numalloc = s_colidx_data[c];
      s_colidx_data[c] = idx;
      while (numalloc < s_colidx_data[c + 1]) {
        bool val;
        currRowIdx = s_rowidx_data[numalloc - 1];
        val = s_d_data[numalloc - 1];
        numalloc++;
        if (val) {
          s_d_data[idx - 1] = true;
          s_rowidx_data[idx - 1] = currRowIdx;
          idx++;
        }
      }
    }
    s_colidx_data[s_colidx->size[0] - 1] = idx;
  } else {
    emxInit_boolean_T(&S, 2);
    i = S->size[0] * S->size[1];
    S->size[0] = 1;
    S->size[1] = a_n;
    emxEnsureCapacity_boolean_T(S, i);
    S_data = S->data;
    for (i = 0; i < a_n; i++) {
      S_data[i] = true;
    }
    for (currRowIdx = 0; currRowIdx < a_n; currRowIdx++) {
      i = a_colidx_data[currRowIdx];
      numalloc = a_colidx_data[currRowIdx + 1] - 1;
      for (idx = i; idx <= numalloc; idx++) {
        S_data[currRowIdx] = (a_d_data[idx - 1] == uniOp_workspace_sb);
      }
    }
    sparse(S, s_d, s_colidx, s_rowidx, s_n);
    emxFree_boolean_T(&S);
  }
}

/*
 * Arguments    : const emxArray_real_T *this_d
 *                const emxArray_int32_T *this_colidx
 *                const emxArray_int32_T *this_rowidx
 *                int this_m
 *                int this_n
 *                int this_maxnz
 *                emxArray_boolean_T *y_d
 *                emxArray_int32_T *y_colidx
 *                emxArray_int32_T *y_rowidx
 *                int *y_m
 *                int *y_n
 *                int *y_maxnz
 * Return Type  : void
 */
void sparse_logical(const emxArray_real_T *this_d,
                    const emxArray_int32_T *this_colidx,
                    const emxArray_int32_T *this_rowidx, int this_m, int this_n,
                    int this_maxnz, emxArray_boolean_T *y_d,
                    emxArray_int32_T *y_colidx, emxArray_int32_T *y_rowidx,
                    int *y_m, int *y_n, int *y_maxnz)
{
  const double *this_d_data;
  const int *this_colidx_data;
  const int *this_rowidx_data;
  int i;
  int loop_ub;
  int numalloc;
  int *y_rowidx_data;
  bool *y_d_data;
  this_rowidx_data = this_rowidx->data;
  this_colidx_data = this_colidx->data;
  this_d_data = this_d->data;
  if (this_maxnz >= 1) {
    numalloc = this_maxnz;
  } else {
    numalloc = 1;
  }
  i = y_d->size[0];
  y_d->size[0] = numalloc;
  emxEnsureCapacity_boolean_T(y_d, i);
  y_d_data = y_d->data;
  for (i = 0; i < numalloc; i++) {
    y_d_data[i] = false;
  }
  i = y_rowidx->size[0];
  y_rowidx->size[0] = this_rowidx->size[0];
  emxEnsureCapacity_int32_T(y_rowidx, i);
  y_rowidx_data = y_rowidx->data;
  loop_ub = this_rowidx->size[0];
  for (i = 0; i < loop_ub; i++) {
    y_rowidx_data[i] = this_rowidx_data[i];
  }
  i = y_colidx->size[0];
  y_colidx->size[0] = this_colidx->size[0];
  emxEnsureCapacity_int32_T(y_colidx, i);
  y_rowidx_data = y_colidx->data;
  loop_ub = this_colidx->size[0];
  for (i = 0; i < loop_ub; i++) {
    y_rowidx_data[i] = this_colidx_data[i];
  }
  loop_ub = this_colidx_data[this_colidx->size[0] - 1] - 1;
  if (loop_ub < 1) {
    loop_ub = 1;
  }
  for (i = 0; i < loop_ub; i++) {
    y_d_data[i] = (this_d_data[i] != 0.0);
  }
  *y_m = this_m;
  *y_n = this_n;
  *y_maxnz = numalloc;
}

/*
 * Arguments    : c_sparse *this
 *                const emxArray_boolean_T *rhs_d
 *                const emxArray_int32_T *rhs_colidx
 *                const emxArray_int32_T *rhs_rowidx
 *                int rhs_m
 *                const emxArray_real_T *varargin_1
 * Return Type  : void
 */
void sparse_parenAssign(c_sparse *this, const emxArray_boolean_T *rhs_d,
                        const emxArray_int32_T *rhs_colidx,
                        const emxArray_int32_T *rhs_rowidx, int rhs_m,
                        const emxArray_real_T *varargin_1)
{
  emxArray_boolean_T *s_d;
  emxArray_int8_T *s_colidx;
  const double *varargin_1_data;
  const int *rhs_colidx_data;
  int idx;
  int k;
  int nidx;
  signed char *s_colidx_data;
  const bool *rhs_d_data;
  bool rhsv;
  bool *s_d_data;
  varargin_1_data = varargin_1->data;
  rhs_colidx_data = rhs_colidx->data;
  rhs_d_data = rhs_d->data;
  nidx = varargin_1->size[1];
  emxInit_boolean_T(&s_d, 1);
  emxInit_int8_T(&s_colidx);
  for (k = 0; k < nidx; k++) {
    int b_vk;
    int cend;
    int siz_idx_0;
    int vk;
    siz_idx_0 = this->m;
    vk = div_s32((int)varargin_1_data[k] - 1, siz_idx_0);
    b_vk = s_colidx->size[0];
    s_colidx->size[0] = 2;
    emxEnsureCapacity_int8_T(s_colidx, b_vk);
    s_colidx_data = s_colidx->data;
    s_colidx_data[0] = 1;
    s_colidx_data[1] = 1;
    b_vk = div_s32(k, rhs_m);
    sparse_locBsearch(rhs_rowidx, (k - b_vk * rhs_m) + 1, rhs_colidx_data[b_vk],
                      rhs_colidx_data[b_vk + 1], &idx, &rhsv);
    if (rhsv) {
      b_vk = s_d->size[0];
      s_d->size[0] = 1;
      emxEnsureCapacity_boolean_T(s_d, b_vk);
      s_d_data = s_d->data;
      s_d_data[0] = rhs_d_data[idx - 1];
      s_colidx_data[1] = 2;
    } else {
      b_vk = s_d->size[0];
      s_d->size[0] = 1;
      emxEnsureCapacity_boolean_T(s_d, b_vk);
      s_d_data = s_d->data;
      s_d_data[0] = false;
    }
    rhsv = false;
    cend = s_colidx_data[1] - 1;
    b_vk = s_colidx_data[0];
    for (idx = b_vk; idx <= cend; idx++) {
      rhsv = s_d_data[0];
    }
    sparse_parenAssign2D(this, rhsv, (int)varargin_1_data[k] - vk * siz_idx_0,
                         vk + 1);
  }
  emxFree_int8_T(&s_colidx);
  emxFree_boolean_T(&s_d);
}

/*
 * Arguments    : const emxArray_boolean_T *this_d
 *                const emxArray_int32_T *this_colidx
 *                const emxArray_int32_T *this_rowidx
 *                int this_m
 *                const emxArray_real_T *varargin_1
 *                emxArray_boolean_T *s_d
 *                emxArray_int32_T *s_colidx
 *                emxArray_int32_T *s_rowidx
 *                int *s_n
 * Return Type  : void
 */
void sparse_parenReference(const emxArray_boolean_T *this_d,
                           const emxArray_int32_T *this_colidx,
                           const emxArray_int32_T *this_rowidx, int this_m,
                           const emxArray_real_T *varargin_1,
                           emxArray_boolean_T *s_d, emxArray_int32_T *s_colidx,
                           emxArray_int32_T *s_rowidx, int *s_n)
{
  const double *varargin_1_data;
  const int *this_colidx_data;
  int cidx;
  int colNnz;
  int idx;
  int loop_ub;
  int ncol;
  int vk;
  int *s_colidx_data;
  int *s_rowidx_data;
  const bool *this_d_data;
  bool found;
  bool *s_d_data;
  varargin_1_data = varargin_1->data;
  this_colidx_data = this_colidx->data;
  this_d_data = this_d->data;
  ncol = varargin_1->size[1];
  *s_n = varargin_1->size[1];
  s_d->size[0] = 0;
  s_rowidx->size[0] = 0;
  vk = s_colidx->size[0];
  s_colidx->size[0] = varargin_1->size[1] + 1;
  emxEnsureCapacity_int32_T(s_colidx, vk);
  s_colidx_data = s_colidx->data;
  loop_ub = varargin_1->size[1];
  for (vk = 0; vk <= loop_ub; vk++) {
    s_colidx_data[vk] = 0;
  }
  s_colidx_data[0] = 1;
  colNnz = 1;
  for (cidx = 0; cidx < ncol; cidx++) {
    loop_ub = (int)varargin_1_data[cidx];
    vk = div_s32(loop_ub - 1, this_m);
    sparse_locBsearch(this_rowidx, loop_ub - vk * this_m, this_colidx_data[vk],
                      this_colidx_data[vk + 1], &idx, &found);
    if (found) {
      vk = s_d->size[0];
      loop_ub = s_d->size[0];
      s_d->size[0]++;
      emxEnsureCapacity_boolean_T(s_d, loop_ub);
      s_d_data = s_d->data;
      s_d_data[vk] = this_d_data[idx - 1];
      vk = s_rowidx->size[0];
      loop_ub = s_rowidx->size[0];
      s_rowidx->size[0]++;
      emxEnsureCapacity_int32_T(s_rowidx, loop_ub);
      s_rowidx_data = s_rowidx->data;
      s_rowidx_data[vk] = 1;
      colNnz++;
    }
    s_colidx_data[cidx + 1] = colNnz;
  }
  if (s_d->size[0] == 0) {
    vk = s_d->size[0];
    s_d->size[0] = 1;
    emxEnsureCapacity_boolean_T(s_d, vk);
    s_d_data = s_d->data;
    s_d_data[0] = false;
    vk = s_rowidx->size[0];
    s_rowidx->size[0] = 1;
    emxEnsureCapacity_int32_T(s_rowidx, vk);
    s_rowidx_data = s_rowidx->data;
    s_rowidx_data[0] = 0;
  }
}

/*
 * File trailer for sparse1.c
 *
 * [EOF]
 */
