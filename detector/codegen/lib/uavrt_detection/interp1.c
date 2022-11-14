/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: interp1.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "interp1.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include "omp.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static void c_interp1Linear(const emxArray_real_T *y, int nyrows,
                            const emxArray_real_T *xi, emxArray_real_T *yi,
                            const emxArray_real_T *varargin_1);

/* Function Definitions */
/*
 * Arguments    : const emxArray_real_T *y
 *                int nyrows
 *                const emxArray_real_T *xi
 *                emxArray_real_T *yi
 *                const emxArray_real_T *varargin_1
 * Return Type  : void
 */
static void c_interp1Linear(const emxArray_real_T *y, int nyrows,
                            const emxArray_real_T *xi, emxArray_real_T *yi,
                            const emxArray_real_T *varargin_1)
{
  const double *varargin_1_data;
  const double *xi_data;
  const double *y_data;
  double maxx;
  double minx;
  double penx;
  double r;
  double *yi_data;
  int high_i;
  int k;
  int low_i;
  int low_ip1;
  int mid_i;
  int ub_loop;
  varargin_1_data = varargin_1->data;
  yi_data = yi->data;
  xi_data = xi->data;
  y_data = y->data;
  minx = varargin_1_data[0];
  penx = varargin_1_data[varargin_1->size[0] - 2];
  maxx = varargin_1_data[varargin_1->size[0] - 1];
  ub_loop = xi->size[0] - 1;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    r, high_i, low_i, low_ip1, mid_i)

  for (k = 0; k <= ub_loop; k++) {
    if (rtIsNaN(xi_data[k])) {
      yi_data[k] = rtNaN;
    } else if (xi_data[k] > maxx) {
      if (nyrows > 1) {
        r = y_data[nyrows - 1];
        yi_data[k] =
            r + (xi_data[k] - maxx) / (maxx - penx) * (r - y_data[nyrows - 2]);
      }
    } else if (xi_data[k] < minx) {
      yi_data[k] = y_data[0] + (xi_data[k] - minx) /
                                   (varargin_1_data[1] - minx) *
                                   (y_data[1] - y_data[0]);
    } else {
      high_i = varargin_1->size[0];
      low_i = 1;
      low_ip1 = 2;
      while (high_i > low_ip1) {
        mid_i = (low_i >> 1) + (high_i >> 1);
        if (((low_i & 1) == 1) && ((high_i & 1) == 1)) {
          mid_i++;
        }
        if (xi_data[k] >= varargin_1_data[mid_i - 1]) {
          low_i = mid_i;
          low_ip1 = mid_i + 1;
        } else {
          high_i = mid_i;
        }
      }
      r = varargin_1_data[low_i - 1];
      r = (xi_data[k] - r) / (varargin_1_data[low_i] - r);
      if (r == 0.0) {
        yi_data[k] = y_data[low_i - 1];
      } else if (r == 1.0) {
        yi_data[k] = y_data[low_i];
      } else if (y_data[low_i - 1] == y_data[low_i]) {
        yi_data[k] = y_data[low_i - 1];
      } else {
        yi_data[k] = (1.0 - r) * y_data[low_i - 1] + r * y_data[low_i];
      }
    }
  }
}

/*
 * Arguments    : const double y[2]
 *                const emxArray_real_T *xi
 *                emxArray_real_T *yi
 * Return Type  : void
 */
void b_interp1Linear(const double y[2], const emxArray_real_T *xi,
                     emxArray_real_T *yi)
{
  const double *xi_data;
  double *yi_data;
  int k;
  int ub_loop;
  yi_data = yi->data;
  xi_data = xi->data;
  ub_loop = xi->size[0] - 1;
#pragma omp parallel for num_threads(omp_get_max_threads())

  for (k = 0; k <= ub_loop; k++) {
    if (rtIsNaN(xi_data[k])) {
      yi_data[k] = rtNaN;
    } else if (xi_data[k] > 1.0) {
      yi_data[k] = y[1] + (xi_data[k] - 1.0) * y[1];
    } else if (xi_data[k] < 0.0) {
      yi_data[k] = xi_data[k] * y[1];
    } else if (xi_data[k] == 0.0) {
      yi_data[k] = 0.0;
    } else if (xi_data[k] == 1.0) {
      yi_data[k] = y[1];
    } else if (y[1] == 0.0) {
      yi_data[k] = 0.0;
    } else {
      yi_data[k] = (1.0 - xi_data[k]) * 0.0 + xi_data[k] * y[1];
    }
  }
}

/*
 * Arguments    : const emxArray_real_T *varargin_1
 *                const emxArray_real_T *varargin_2
 *                const emxArray_real_T *varargin_3
 *                emxArray_real_T *Vq
 * Return Type  : void
 */
void interp1(const emxArray_real_T *varargin_1,
             const emxArray_real_T *varargin_2,
             const emxArray_real_T *varargin_3, emxArray_real_T *Vq)
{
  emxArray_real_T *x;
  emxArray_real_T *y;
  const double *varargin_1_data;
  const double *varargin_2_data;
  double *Vq_data;
  double *x_data;
  double *y_data;
  int b_j1;
  int k;
  int n;
  int nx;
  varargin_2_data = varargin_2->data;
  varargin_1_data = varargin_1->data;
  emxInit_real_T(&y, 1);
  k = y->size[0];
  y->size[0] = varargin_2->size[0];
  emxEnsureCapacity_real_T(y, k);
  y_data = y->data;
  n = varargin_2->size[0];
  for (k = 0; k < n; k++) {
    y_data[k] = varargin_2_data[k];
  }
  emxInit_real_T(&x, 1);
  k = x->size[0];
  x->size[0] = varargin_1->size[0];
  emxEnsureCapacity_real_T(x, k);
  x_data = x->data;
  n = varargin_1->size[0];
  for (k = 0; k < n; k++) {
    x_data[k] = varargin_1_data[k];
  }
  nx = varargin_1->size[0] - 1;
  k = Vq->size[0];
  Vq->size[0] = varargin_3->size[0];
  emxEnsureCapacity_real_T(Vq, k);
  Vq_data = Vq->data;
  n = varargin_3->size[0];
  for (k = 0; k < n; k++) {
    Vq_data[k] = 0.0;
  }
  if (varargin_3->size[0] != 0) {
    k = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (k <= nx) {
        if (rtIsNaN(varargin_1_data[k])) {
          exitg1 = 1;
        } else {
          k++;
        }
      } else {
        if (varargin_1_data[1] < varargin_1_data[0]) {
          double xtmp;
          k = (nx + 1) >> 1;
          for (b_j1 = 0; b_j1 < k; b_j1++) {
            xtmp = x_data[b_j1];
            n = nx - b_j1;
            x_data[b_j1] = x_data[n];
            x_data[n] = xtmp;
          }
          if (varargin_2->size[0] > 1) {
            n = varargin_2->size[0] - 1;
            nx = varargin_2->size[0] >> 1;
            for (k = 0; k < nx; k++) {
              xtmp = y_data[k];
              b_j1 = n - k;
              y_data[k] = y_data[b_j1];
              y_data[b_j1] = xtmp;
            }
          }
        }
        c_interp1Linear(y, varargin_2->size[0], varargin_3, Vq, x);
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  emxFree_real_T(&x);
  emxFree_real_T(&y);
}

/*
 * Arguments    : const double y[2]
 *                const emxArray_real_T *xi
 *                emxArray_real_T *yi
 *                const double varargin_1[2]
 * Return Type  : void
 */
void interp1Linear(const double y[2], const emxArray_real_T *xi,
                   emxArray_real_T *yi, const double varargin_1[2])
{
  const double *xi_data;
  double maxx;
  double minx;
  double r;
  double *yi_data;
  int k;
  int ub_loop;
  yi_data = yi->data;
  xi_data = xi->data;
  minx = varargin_1[0];
  maxx = varargin_1[1];
  ub_loop = xi->size[1] - 1;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(r)

  for (k = 0; k <= ub_loop; k++) {
    r = xi_data[k];
    if (rtIsNaN(r)) {
      yi_data[k] = rtNaN;
    } else if ((!(r > maxx)) && (!(r < minx))) {
      r = (r - varargin_1[0]) / (varargin_1[1] - varargin_1[0]);
      if (r == 0.0) {
        yi_data[k] = y[0];
      } else if (r == 1.0) {
        yi_data[k] = y[1];
      } else if (y[0] == y[1]) {
        yi_data[k] = y[0];
      } else {
        yi_data[k] = (1.0 - r) * y[0] + r * y[1];
      }
    }
  }
}

/*
 * File trailer for interp1.c
 *
 * [EOF]
 */
