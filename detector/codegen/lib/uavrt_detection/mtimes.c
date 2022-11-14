/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: mtimes.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "mtimes.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"

/* Function Definitions */
/*
 * Arguments    : const emxArray_boolean_T *a_d
 *                const emxArray_int32_T *a_colidx
 *                const emxArray_int32_T *a_rowidx
 *                int a_m
 *                int a_n
 *                const emxArray_real_T *b
 *                emxArray_real_T *c
 * Return Type  : void
 */
void b_sparse_mtimes(const emxArray_boolean_T *a_d,
                     const emxArray_int32_T *a_colidx,
                     const emxArray_int32_T *a_rowidx, int a_m, int a_n,
                     const emxArray_real_T *b, emxArray_real_T *c)
{
  const double *b_data;
  double *c_data;
  const int *a_colidx_data;
  const int *a_rowidx_data;
  int acol;
  int ap;
  int apend;
  int i;
  int j;
  int n;
  const bool *a_d_data;
  b_data = b->data;
  a_rowidx_data = a_rowidx->data;
  a_colidx_data = a_colidx->data;
  a_d_data = a_d->data;
  n = b->size[1];
  i = c->size[0] * c->size[1];
  c->size[0] = a_m;
  c->size[1] = b->size[1];
  emxEnsureCapacity_real_T(c, i);
  c_data = c->data;
  apend = a_m * b->size[1];
  for (i = 0; i < apend; i++) {
    c_data[i] = 0.0;
  }
  if ((a_n != 0) && (a_m != 0) && (b->size[1] != 0) &&
      (a_colidx_data[a_colidx->size[0] - 1] - 1 != 0)) {
    if (b->size[1] == 1) {
      for (acol = 0; acol < a_n; acol++) {
        double bc;
        int nap;
        bc = b_data[acol];
        i = a_colidx_data[acol];
        apend = a_colidx_data[acol + 1];
        nap = apend - a_colidx_data[acol];
        if (nap >= 4) {
          int apend1;
          apend1 = (apend - nap) + ((nap / 4) << 2);
          for (ap = i; ap <= apend1 - 1; ap += 4) {
            nap = a_rowidx_data[ap - 1] - 1;
            c_data[nap] += (double)a_d_data[ap - 1] * bc;
            c_data[a_rowidx_data[ap] - 1] += (double)a_d_data[ap] * bc;
            nap = a_rowidx_data[ap + 1] - 1;
            c_data[nap] += (double)a_d_data[ap + 1] * bc;
            nap = a_rowidx_data[ap + 2] - 1;
            c_data[nap] += (double)a_d_data[ap + 2] * bc;
          }
          nap = a_colidx_data[acol + 1] - 1;
          for (ap = apend1; ap <= nap; ap++) {
            apend = a_rowidx_data[ap - 1] - 1;
            c_data[apend] += (double)a_d_data[ap - 1] * bc;
          }
        } else {
          apend--;
          for (ap = i; ap <= apend; ap++) {
            nap = a_rowidx_data[ap - 1] - 1;
            c_data[nap] += (double)a_d_data[ap - 1] * bc;
          }
        }
      }
    } else {
      for (j = 0; j < n; j++) {
        int coff;
        coff = j * c->size[0] - 1;
        for (acol = 0; acol < a_n; acol++) {
          double bc;
          int nap;
          bc = b_data[acol + b->size[0] * j];
          i = a_colidx_data[acol];
          apend = a_colidx_data[acol + 1];
          nap = apend - a_colidx_data[acol];
          if (nap >= 4) {
            int apend1;
            apend1 = (apend - nap) + ((nap / 4) << 2);
            for (ap = i; ap <= apend1 - 1; ap += 4) {
              nap = a_rowidx_data[ap - 1] + coff;
              c_data[nap] += (double)a_d_data[ap - 1] * bc;
              nap = a_rowidx_data[ap] + coff;
              c_data[nap] += (double)a_d_data[ap] * bc;
              nap = a_rowidx_data[ap + 1] + coff;
              c_data[nap] += (double)a_d_data[ap + 1] * bc;
              nap = a_rowidx_data[ap + 2] + coff;
              c_data[nap] += (double)a_d_data[ap + 2] * bc;
            }
            nap = a_colidx_data[acol + 1] - 1;
            for (ap = apend1; ap <= nap; ap++) {
              apend = a_rowidx_data[ap - 1] - 1;
              c_data[apend + c->size[0] * j] += (double)a_d_data[ap - 1] * bc;
            }
          } else {
            apend--;
            for (ap = i; ap <= apend; ap++) {
              nap = a_rowidx_data[ap - 1] + coff;
              c_data[nap] += (double)a_d_data[ap - 1] * bc;
            }
          }
        }
      }
    }
  }
}

/*
 * Arguments    : const emxArray_real_T *a
 *                const emxArray_boolean_T *b_d
 *                const emxArray_int32_T *b_colidx
 *                const emxArray_int32_T *b_rowidx
 *                int b_n
 *                emxArray_real_T *c
 * Return Type  : void
 */
void c_sparse_mtimes(const emxArray_real_T *a, const emxArray_boolean_T *b_d,
                     const emxArray_int32_T *b_colidx,
                     const emxArray_int32_T *b_rowidx, int b_n,
                     emxArray_real_T *c)
{
  const double *a_data;
  double *c_data;
  const int *b_colidx_data;
  const int *b_rowidx_data;
  int aoff;
  int bp;
  int ccol;
  int cidx;
  int crow;
  int i;
  int m;
  int mend;
  const bool *b_d_data;
  b_rowidx_data = b_rowidx->data;
  b_colidx_data = b_colidx->data;
  b_d_data = b_d->data;
  a_data = a->data;
  m = a->size[0];
  i = c->size[0] * c->size[1];
  c->size[0] = a->size[0];
  c->size[1] = b_n;
  emxEnsureCapacity_real_T(c, i);
  c_data = c->data;
  aoff = a->size[0] * b_n;
  for (i = 0; i < aoff; i++) {
    c_data[i] = 0.0;
  }
  if ((a->size[1] != 0) && (a->size[0] != 0) && (b_n != 0) &&
      (b_colidx_data[b_colidx->size[0] - 1] - 1 != 0)) {
    if (a->size[0] == 1) {
      for (mend = 0; mend < b_n; mend++) {
        double cd;
        cd = 0.0;
        aoff = b_colidx_data[mend + 1] - 1;
        i = b_colidx_data[mend];
        for (cidx = i; cidx <= aoff; cidx++) {
          cd +=
              (double)b_d_data[cidx - 1] * a_data[b_rowidx_data[cidx - 1] - 1];
        }
        c_data[mend] = cd;
      }
    } else if (a->size[0] >= 4) {
      for (ccol = 0; ccol < b_n; ccol++) {
        int bpend;
        int coff;
        coff = ccol * c->size[0];
        bpend = b_colidx_data[ccol + 1] - 1;
        i = b_colidx_data[ccol];
        for (bp = i; bp <= bpend; bp++) {
          int aoff_tmp;
          bool bd;
          aoff_tmp = b_rowidx_data[bp - 1] - 1;
          aoff = aoff_tmp * a->size[0];
          bd = b_d_data[bp - 1];
          mend = (m / 4) << 2;
          for (crow = 1; crow <= mend; crow += 4) {
            int aidx_tmp;
            cidx = crow + coff;
            aidx_tmp = crow + aoff;
            c_data[cidx - 1] += a_data[aidx_tmp - 1] * (double)bd;
            c_data[cidx] += a_data[aidx_tmp] * (double)bd;
            c_data[cidx + 1] += a_data[aidx_tmp + 1] * (double)bd;
            c_data[cidx + 2] += a_data[aidx_tmp + 2] * (double)bd;
          }
          aoff = mend + 1;
          for (crow = aoff; crow <= m; crow++) {
            mend = (crow + coff) - 1;
            c_data[mend] +=
                a_data[(crow + a->size[0] * aoff_tmp) - 1] * (double)bd;
          }
        }
      }
    } else {
      for (ccol = 0; ccol < b_n; ccol++) {
        int bpend;
        bpend = b_colidx_data[ccol + 1] - 1;
        i = b_colidx_data[ccol];
        for (bp = i; bp <= bpend; bp++) {
          for (crow = 0; crow < m; crow++) {
            c_data[crow + c->size[0] * ccol] +=
                a_data[crow + a->size[0] * (b_rowidx_data[bp - 1] - 1)] *
                (double)b_d_data[bp - 1];
          }
        }
      }
    }
  }
}

/*
 * Arguments    : const emxArray_real_T *a
 *                const emxArray_real_T *b_d
 *                const emxArray_int32_T *b_colidx
 *                const emxArray_int32_T *b_rowidx
 *                int b_n
 *                emxArray_real_T *c
 * Return Type  : void
 */
void sparse_mtimes(const emxArray_real_T *a, const emxArray_real_T *b_d,
                   const emxArray_int32_T *b_colidx,
                   const emxArray_int32_T *b_rowidx, int b_n,
                   emxArray_real_T *c)
{
  const double *a_data;
  const double *b_d_data;
  double *c_data;
  const int *b_colidx_data;
  const int *b_rowidx_data;
  int aoff;
  int bp;
  int ccol;
  int cidx;
  int crow;
  int i;
  int m;
  int mend;
  b_rowidx_data = b_rowidx->data;
  b_colidx_data = b_colidx->data;
  b_d_data = b_d->data;
  a_data = a->data;
  m = a->size[0];
  i = c->size[0] * c->size[1];
  c->size[0] = a->size[0];
  c->size[1] = b_n;
  emxEnsureCapacity_real_T(c, i);
  c_data = c->data;
  aoff = a->size[0] * b_n;
  for (i = 0; i < aoff; i++) {
    c_data[i] = 0.0;
  }
  if ((a->size[1] != 0) && (a->size[0] != 0) && (b_n != 0) &&
      (b_colidx_data[b_colidx->size[0] - 1] - 1 != 0)) {
    if (a->size[0] == 1) {
      for (mend = 0; mend < b_n; mend++) {
        double bd;
        bd = 0.0;
        aoff = b_colidx_data[mend + 1] - 1;
        i = b_colidx_data[mend];
        for (cidx = i; cidx <= aoff; cidx++) {
          bd += b_d_data[cidx - 1] * a_data[b_rowidx_data[cidx - 1] - 1];
        }
        c_data[mend] = bd;
      }
    } else if (a->size[0] >= 4) {
      for (ccol = 0; ccol < b_n; ccol++) {
        int bpend;
        int coff;
        coff = ccol * c->size[0];
        bpend = b_colidx_data[ccol + 1] - 1;
        i = b_colidx_data[ccol];
        for (bp = i; bp <= bpend; bp++) {
          double bd;
          int aoff_tmp;
          aoff_tmp = b_rowidx_data[bp - 1] - 1;
          aoff = aoff_tmp * a->size[0];
          bd = b_d_data[bp - 1];
          mend = (m / 4) << 2;
          for (crow = 1; crow <= mend; crow += 4) {
            int aidx_tmp;
            cidx = crow + coff;
            aidx_tmp = crow + aoff;
            c_data[cidx - 1] += a_data[aidx_tmp - 1] * bd;
            c_data[cidx] += a_data[aidx_tmp] * bd;
            c_data[cidx + 1] += a_data[aidx_tmp + 1] * bd;
            c_data[cidx + 2] += a_data[aidx_tmp + 2] * bd;
          }
          aoff = mend + 1;
          for (crow = aoff; crow <= m; crow++) {
            mend = (crow + coff) - 1;
            c_data[mend] += a_data[(crow + a->size[0] * aoff_tmp) - 1] * bd;
          }
        }
      }
    } else {
      for (ccol = 0; ccol < b_n; ccol++) {
        int bpend;
        bpend = b_colidx_data[ccol + 1] - 1;
        i = b_colidx_data[ccol];
        for (bp = i; bp <= bpend; bp++) {
          for (crow = 0; crow < m; crow++) {
            c_data[crow + c->size[0] * ccol] +=
                a_data[crow + a->size[0] * (b_rowidx_data[bp - 1] - 1)] *
                b_d_data[bp - 1];
          }
        }
      }
    }
  }
}

/*
 * File trailer for mtimes.c
 *
 * [EOF]
 */
