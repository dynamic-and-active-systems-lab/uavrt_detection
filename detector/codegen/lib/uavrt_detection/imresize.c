/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: imresize.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "imresize.h"
#include "rt_nonfinite.h"
#include "sum.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include "omp.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Declarations */
static void b_resizeAlongDim2D(const emxArray_real_T *in,
                               const emxArray_real_T *weights,
                               const emxArray_int32_T *indices,
                               double out_length, emxArray_real_T *out);

static void contributions(int in_length, double out_length, double scale,
                          double kernel_width, emxArray_real_T *weights,
                          emxArray_int32_T *indices);

static void resizeAlongDim2D(const emxArray_real_T *in,
                             const emxArray_real_T *weights,
                             const emxArray_int32_T *indices, double out_length,
                             emxArray_real_T *out);

/* Function Definitions */
/*
 * Arguments    : const emxArray_real_T *in
 *                const emxArray_real_T *weights
 *                const emxArray_int32_T *indices
 *                double out_length
 *                emxArray_real_T *out
 * Return Type  : void
 */
static void b_resizeAlongDim2D(const emxArray_real_T *in,
                               const emxArray_real_T *weights,
                               const emxArray_int32_T *indices,
                               double out_length, emxArray_real_T *out)
{
  const double *in_data;
  const double *weights_data;
  double sumVal1;
  double *out_data;
  const int *indices_data;
  int i;
  int i1;
  int inRInd;
  int k;
  int linearInds;
  int outCInd;
  int pixelIndex;
  int pixelIndex_tmp;
  int ub_loop;
  out_data = out->data;
  indices_data = indices->data;
  weights_data = weights->data;
  in_data = in->data;
  ub_loop = in->size[0] - 1;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    pixelIndex, linearInds, sumVal1, i, outCInd, i1, k, pixelIndex_tmp)

  for (inRInd = 0; inRInd <= ub_loop; inRInd++) {
    i = (int)out_length;
    for (outCInd = 0; outCInd < i; outCInd++) {
      sumVal1 = 0.0;
      /*  Core - second dimension */
      i1 = weights->size[0];
      linearInds = weights->size[0] * outCInd + 1;
      for (k = 0; k < i1; k++) {
        pixelIndex_tmp = (linearInds + k) - 1;
        pixelIndex =
            (inRInd + (indices_data[pixelIndex_tmp] - 1) * in->size[0]) + 1;
        sumVal1 += weights_data[pixelIndex_tmp] * in_data[pixelIndex - 1];
      }
      out_data[inRInd + out->size[0] * outCInd] = sumVal1;
    }
  }
}

/*
 * Arguments    : int in_length
 *                double out_length
 *                double scale
 *                double kernel_width
 *                emxArray_real_T *weights
 *                emxArray_int32_T *indices
 * Return Type  : void
 */
static void contributions(int in_length, double out_length, double scale,
                          double kernel_width, emxArray_real_T *weights,
                          emxArray_int32_T *indices)
{
  emxArray_boolean_T *copyCols;
  emxArray_int32_T *aux;
  emxArray_int32_T *b_indices;
  emxArray_int32_T *left;
  emxArray_int32_T *r;
  emxArray_int32_T *r1;
  emxArray_real_T *absx;
  emxArray_real_T *absx2;
  emxArray_real_T *b_x;
  emxArray_real_T *u;
  emxArray_real_T *x;
  emxArray_real_T *y;
  double k;
  double *absx2_data;
  double *absx_data;
  double *u_data;
  double *weights_data;
  int b_i;
  int b_k;
  int bcoef;
  int c_k;
  int i;
  int nx;
  int *aux_data;
  int *indices_data;
  int *left_data;
  bool *copyCols_data;
  /*  Contributions, using pixel indices */
  if (scale < 1.0) {
    kernel_width = 4.0 / scale;
  }
  emxInit_real_T(&y, 2);
  absx2_data = y->data;
  if (rtIsNaN(out_length)) {
    i = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = 1;
    emxEnsureCapacity_real_T(y, i);
    absx2_data = y->data;
    absx2_data[0] = rtNaN;
  } else if (out_length < 1.0) {
    y->size[0] = 1;
    y->size[1] = 0;
  } else {
    i = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = (int)(out_length - 1.0) + 1;
    emxEnsureCapacity_real_T(y, i);
    absx2_data = y->data;
    bcoef = (int)(out_length - 1.0);
    for (i = 0; i <= bcoef; i++) {
      absx2_data[i] = (double)i + 1.0;
    }
  }
  k = 0.5 * (1.0 - 1.0 / scale);
  emxInit_real_T(&u, 1);
  i = u->size[0];
  u->size[0] = y->size[1];
  emxEnsureCapacity_real_T(u, i);
  u_data = u->data;
  bcoef = y->size[1];
  for (i = 0; i < bcoef; i++) {
    u_data[i] = absx2_data[i] / scale + k;
  }
  emxFree_real_T(&y);
  k = kernel_width / 2.0;
  emxInit_real_T(&x, 1);
  i = x->size[0];
  x->size[0] = u->size[0];
  emxEnsureCapacity_real_T(x, i);
  absx2_data = x->data;
  bcoef = u->size[0];
  for (i = 0; i < bcoef; i++) {
    absx2_data[i] = u_data[i] - k;
  }
  nx = x->size[0];
  for (b_k = 0; b_k < nx; b_k++) {
    absx2_data[b_k] = floor(absx2_data[b_k]);
  }
  emxInit_int32_T(&left, 1);
  i = left->size[0];
  left->size[0] = x->size[0];
  emxEnsureCapacity_int32_T(left, i);
  left_data = left->data;
  bcoef = x->size[0];
  for (i = 0; i < bcoef; i++) {
    left_data[i] = (int)absx2_data[i];
  }
  emxFree_real_T(&x);
  bcoef = (int)(ceil(kernel_width) + 2.0);
  emxInit_int32_T(&aux, 2);
  i = aux->size[0] * aux->size[1];
  aux->size[0] = 1;
  aux->size[1] = bcoef;
  emxEnsureCapacity_int32_T(aux, i);
  aux_data = aux->data;
  aux_data[0] = 0;
  nx = 0;
  for (b_k = 2; b_k <= bcoef; b_k++) {
    nx++;
    aux_data[b_k - 1] = nx;
  }
  i = indices->size[0] * indices->size[1];
  indices->size[0] = left->size[0];
  indices->size[1] = aux->size[1];
  emxEnsureCapacity_int32_T(indices, i);
  indices_data = indices->data;
  if (left->size[0] != 0) {
    i = aux->size[1] - 1;
    nx = (left->size[0] != 1);
    b_i = indices->size[0] - 1;
    for (b_k = 0; b_k <= i; b_k++) {
      for (c_k = 0; c_k <= b_i; c_k++) {
        indices_data[c_k + indices->size[0] * b_k] =
            left_data[nx * c_k] + aux_data[b_k];
      }
    }
  }
  emxFree_int32_T(&left);
  emxInit_real_T(&absx, 2);
  i = absx->size[0] * absx->size[1];
  absx->size[0] = indices->size[0];
  absx->size[1] = indices->size[1];
  emxEnsureCapacity_real_T(absx, i);
  absx_data = absx->data;
  bcoef = indices->size[0] * indices->size[1];
  for (i = 0; i < bcoef; i++) {
    absx_data[i] = indices_data[i];
  }
  emxInit_real_T(&b_x, 2);
  i = b_x->size[0] * b_x->size[1];
  nx = absx->size[0];
  bcoef = u->size[0];
  if (nx <= bcoef) {
    bcoef = nx;
  }
  if (absx->size[0] == 1) {
    b_x->size[0] = u->size[0];
  } else if (u->size[0] == 1) {
    b_x->size[0] = absx->size[0];
  } else if (u->size[0] == absx->size[0]) {
    b_x->size[0] = u->size[0];
  } else {
    b_x->size[0] = bcoef;
  }
  b_x->size[1] = absx->size[1];
  emxEnsureCapacity_real_T(b_x, i);
  absx2_data = b_x->data;
  nx = absx->size[0];
  bcoef = u->size[0];
  if (nx <= bcoef) {
    bcoef = nx;
  }
  if (absx->size[0] == 1) {
    bcoef = u->size[0];
  } else if (u->size[0] == 1) {
    bcoef = absx->size[0];
  } else if (u->size[0] == absx->size[0]) {
    bcoef = u->size[0];
  }
  if (bcoef != 0) {
    i = absx->size[1] - 1;
    nx = (u->size[0] != 1);
    bcoef = (absx->size[0] != 1);
    b_i = b_x->size[0] - 1;
    for (b_k = 0; b_k <= i; b_k++) {
      for (c_k = 0; c_k <= b_i; c_k++) {
        absx2_data[c_k + b_x->size[0] * b_k] =
            u_data[nx * c_k] - absx_data[bcoef * c_k + absx->size[0] * b_k];
      }
    }
  }
  if (scale < 1.0) {
    bcoef = b_x->size[0] * b_x->size[1];
    for (i = 0; i < bcoef; i++) {
      absx2_data[i] *= scale;
    }
  }
  nx = b_x->size[0] * b_x->size[1];
  i = absx->size[0] * absx->size[1];
  absx->size[0] = b_x->size[0];
  absx->size[1] = b_x->size[1];
  emxEnsureCapacity_real_T(absx, i);
  absx_data = absx->data;
  for (b_k = 0; b_k < nx; b_k++) {
    absx_data[b_k] = fabs(absx2_data[b_k]);
  }
  emxFree_real_T(&b_x);
  emxInit_real_T(&absx2, 2);
  i = absx2->size[0] * absx2->size[1];
  absx2->size[0] = absx->size[0];
  absx2->size[1] = absx->size[1];
  emxEnsureCapacity_real_T(absx2, i);
  absx2_data = absx2->data;
  nx = absx->size[0] * absx->size[1];
  for (b_k = 0; b_k < nx; b_k++) {
    absx2_data[b_k] = absx_data[b_k] * absx_data[b_k];
  }
  i = weights->size[0] * weights->size[1];
  weights->size[0] = absx->size[0];
  weights->size[1] = absx->size[1];
  emxEnsureCapacity_real_T(weights, i);
  weights_data = weights->data;
  nx = absx->size[0] * absx->size[1];
  for (b_k = 0; b_k < nx; b_k++) {
    weights_data[b_k] = rt_powd_snf(absx_data[b_k], 3.0);
  }
  bcoef = absx2->size[0] * absx2->size[1];
  for (i = 0; i < bcoef; i++) {
    absx2_data[i] *= 2.5;
  }
  bcoef = weights->size[0] * weights->size[1];
  for (i = 0; i < bcoef; i++) {
    weights_data[i] =
        ((1.5 * weights_data[i] - absx2_data[i]) + 1.0) *
            (double)(absx_data[i] <= 1.0) +
        (((-0.5 * weights_data[i] + absx2_data[i]) - 4.0 * absx_data[i]) +
         2.0) *
            (double)((absx_data[i] > 1.0) && (absx_data[i] <= 2.0));
  }
  emxFree_real_T(&absx2);
  if (scale < 1.0) {
    bcoef = weights->size[0] * weights->size[1];
    for (i = 0; i < bcoef; i++) {
      weights_data[i] *= scale;
    }
  }
  i = absx->size[0] * absx->size[1];
  absx->size[0] = weights->size[0];
  absx->size[1] = weights->size[1];
  emxEnsureCapacity_real_T(absx, i);
  absx_data = absx->data;
  bcoef = weights->size[0] * weights->size[1];
  for (i = 0; i < bcoef; i++) {
    absx_data[i] = weights_data[i];
  }
  d_sum(weights, u);
  u_data = u->data;
  nx = u->size[0];
  bcoef = weights->size[0];
  if (nx <= bcoef) {
    bcoef = nx;
  }
  if (u->size[0] == 1) {
    nx = weights->size[0];
  } else if (weights->size[0] == 1) {
    nx = u->size[0];
  } else if (weights->size[0] == u->size[0]) {
    nx = weights->size[0];
  } else {
    nx = bcoef;
  }
  bcoef = weights->size[1];
  i = weights->size[0] * weights->size[1];
  weights->size[0] = nx;
  weights->size[1] = bcoef;
  emxEnsureCapacity_real_T(weights, i);
  weights_data = weights->data;
  if (nx != 0) {
    i = bcoef - 1;
    nx = (absx->size[0] != 1);
    bcoef = (u->size[0] != 1);
    b_i = weights->size[0] - 1;
    for (b_k = 0; b_k <= i; b_k++) {
      for (c_k = 0; c_k <= b_i; c_k++) {
        weights_data[c_k + weights->size[0] * b_k] =
            absx_data[nx * c_k + absx->size[0] * b_k] / u_data[bcoef * c_k];
      }
    }
  }
  emxFree_real_T(&u);
  /*  Create the auxiliary matrix: */
  bcoef = in_length << 1;
  i = aux->size[0] * aux->size[1];
  aux->size[0] = 1;
  aux->size[1] = bcoef;
  emxEnsureCapacity_int32_T(aux, i);
  aux_data = aux->data;
  aux_data[0] = 1;
  aux_data[in_length] = in_length;
  for (b_i = 2; b_i <= in_length; b_i++) {
    aux_data[b_i - 1] = aux_data[b_i - 2] + 1;
    nx = in_length + b_i;
    aux_data[nx - 1] = aux_data[nx - 2] - 1;
  }
  /*  Mirror the out-of-bounds indices using mod: */
  i = indices->size[0] * indices->size[1];
  for (b_i = 0; b_i < i; b_i++) {
    k = (double)indices_data[b_i] - 1.0;
    if (bcoef == 0) {
      if ((double)indices_data[b_i] - 1.0 == 0.0) {
        k = 0.0;
      }
    } else if ((double)indices_data[b_i] - 1.0 == 0.0) {
      k = 0.0;
    } else {
      k = fmod((double)indices_data[b_i] - 1.0, bcoef);
      if (k == 0.0) {
        k = 0.0;
      } else if ((double)indices_data[b_i] - 1.0 < 0.0) {
        k += (double)bcoef;
      }
    }
    indices_data[b_i] = aux_data[(int)k];
  }
  emxFree_int32_T(&aux);
  emxInit_boolean_T(&copyCols, 2);
  i = copyCols->size[0] * copyCols->size[1];
  copyCols->size[0] = 1;
  copyCols->size[1] = weights->size[1];
  emxEnsureCapacity_boolean_T(copyCols, i);
  copyCols_data = copyCols->data;
  bcoef = weights->size[1];
  for (i = 0; i < bcoef; i++) {
    copyCols_data[i] = false;
  }
  nx = weights->size[1];
  bcoef = 0;
  for (b_i = 0; b_i < nx; b_i++) {
    bool exitg1;
    c_k = bcoef + weights->size[0];
    b_k = bcoef;
    bcoef += weights->size[0];
    exitg1 = false;
    while ((!exitg1) && (b_k + 1 <= c_k)) {
      if ((weights_data[b_k] == 0.0) || rtIsNaN(weights_data[b_k])) {
        b_k++;
      } else {
        copyCols_data[b_i] = true;
        exitg1 = true;
      }
    }
  }
  bcoef = copyCols->size[1] - 1;
  nx = 0;
  for (b_i = 0; b_i <= bcoef; b_i++) {
    if (copyCols_data[b_i]) {
      nx++;
    }
  }
  emxInit_int32_T(&r, 2);
  i = r->size[0] * r->size[1];
  r->size[0] = 1;
  r->size[1] = nx;
  emxEnsureCapacity_int32_T(r, i);
  left_data = r->data;
  nx = 0;
  for (b_i = 0; b_i <= bcoef; b_i++) {
    if (copyCols_data[b_i]) {
      left_data[nx] = b_i + 1;
      nx++;
    }
  }
  nx = weights->size[0];
  i = absx->size[0] * absx->size[1];
  absx->size[0] = r->size[1];
  absx->size[1] = weights->size[0];
  emxEnsureCapacity_real_T(absx, i);
  absx_data = absx->data;
  for (i = 0; i < nx; i++) {
    bcoef = r->size[1];
    for (b_i = 0; b_i < bcoef; b_i++) {
      absx_data[b_i + absx->size[0] * i] =
          weights_data[i + weights->size[0] * (left_data[b_i] - 1)];
    }
  }
  emxFree_int32_T(&r);
  i = weights->size[0] * weights->size[1];
  weights->size[0] = absx->size[0];
  weights->size[1] = absx->size[1];
  emxEnsureCapacity_real_T(weights, i);
  weights_data = weights->data;
  bcoef = absx->size[0] * absx->size[1];
  for (i = 0; i < bcoef; i++) {
    weights_data[i] = absx_data[i];
  }
  emxFree_real_T(&absx);
  bcoef = copyCols->size[1] - 1;
  nx = 0;
  for (b_i = 0; b_i <= bcoef; b_i++) {
    if (copyCols_data[b_i]) {
      nx++;
    }
  }
  emxInit_int32_T(&r1, 2);
  i = r1->size[0] * r1->size[1];
  r1->size[0] = 1;
  r1->size[1] = nx;
  emxEnsureCapacity_int32_T(r1, i);
  left_data = r1->data;
  nx = 0;
  for (b_i = 0; b_i <= bcoef; b_i++) {
    if (copyCols_data[b_i]) {
      left_data[nx] = b_i + 1;
      nx++;
    }
  }
  emxFree_boolean_T(&copyCols);
  nx = indices->size[0];
  emxInit_int32_T(&b_indices, 2);
  i = b_indices->size[0] * b_indices->size[1];
  b_indices->size[0] = r1->size[1];
  b_indices->size[1] = indices->size[0];
  emxEnsureCapacity_int32_T(b_indices, i);
  aux_data = b_indices->data;
  for (i = 0; i < nx; i++) {
    bcoef = r1->size[1];
    for (b_i = 0; b_i < bcoef; b_i++) {
      aux_data[b_i + b_indices->size[0] * i] =
          indices_data[i + indices->size[0] * (left_data[b_i] - 1)];
    }
  }
  emxFree_int32_T(&r1);
  i = indices->size[0] * indices->size[1];
  indices->size[0] = b_indices->size[0];
  indices->size[1] = b_indices->size[1];
  emxEnsureCapacity_int32_T(indices, i);
  indices_data = indices->data;
  bcoef = b_indices->size[0] * b_indices->size[1];
  for (i = 0; i < bcoef; i++) {
    indices_data[i] = aux_data[i];
  }
  emxFree_int32_T(&b_indices);
}

/*
 * Arguments    : const emxArray_real_T *in
 *                const emxArray_real_T *weights
 *                const emxArray_int32_T *indices
 *                double out_length
 *                emxArray_real_T *out
 * Return Type  : void
 */
static void resizeAlongDim2D(const emxArray_real_T *in,
                             const emxArray_real_T *weights,
                             const emxArray_int32_T *indices, double out_length,
                             emxArray_real_T *out)
{
  const double *in_data;
  const double *weights_data;
  double sumVal1;
  double *out_data;
  const int *indices_data;
  int i;
  int i1;
  int inCInd;
  int k;
  int linearInds;
  int outRInd;
  int sumVal1_tmp;
  int ub_loop;
  out_data = out->data;
  indices_data = indices->data;
  weights_data = weights->data;
  in_data = in->data;
  ub_loop =
      (int)((double)(in->size[0] * in->size[1]) / (double)in->size[0]) - 1;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    linearInds, sumVal1, i, outRInd, i1, k, sumVal1_tmp)

  for (inCInd = 0; inCInd <= ub_loop; inCInd++) {
    i = (int)out_length;
    for (outRInd = 0; outRInd < i; outRInd++) {
      sumVal1 = 0.0;
      i1 = weights->size[0];
      linearInds = weights->size[0] * outRInd + 1;
      /*  Core - first dimension */
      for (k = 0; k < i1; k++) {
        sumVal1_tmp = (linearInds + k) - 1;
        sumVal1 +=
            weights_data[sumVal1_tmp] *
            in_data[(indices_data[sumVal1_tmp] + in->size[0] * inCInd) - 1];
      }
      out_data[outRInd + out->size[0] * inCInd] = sumVal1;
    }
  }
}

/*
 * Arguments    : const emxArray_real_T *Ain
 *                const double varargin_1[2]
 *                emxArray_real_T *Bout
 * Return Type  : void
 */
void imresize(const emxArray_real_T *Ain, const double varargin_1[2],
              emxArray_real_T *Bout)
{
  emxArray_int32_T *indices;
  emxArray_real_T *out;
  emxArray_real_T *weights;
  double outputSize_idx_0;
  double outputSize_idx_1;
  double scale_idx_0;
  double scale_idx_1;
  if (rtIsNaN(varargin_1[0])) {
    outputSize_idx_0 =
        ceil(varargin_1[1] * (double)Ain->size[0] / (double)Ain->size[1]);
    outputSize_idx_1 = ceil(varargin_1[1]);
    scale_idx_0 = outputSize_idx_1 / (double)Ain->size[1];
    scale_idx_1 = outputSize_idx_1 / (double)Ain->size[1];
  } else if (rtIsNaN(varargin_1[1])) {
    outputSize_idx_0 = ceil(varargin_1[0]);
    outputSize_idx_1 =
        ceil(varargin_1[0] * (double)Ain->size[1] / (double)Ain->size[0]);
    scale_idx_0 = outputSize_idx_0 / (double)Ain->size[0];
    scale_idx_1 = outputSize_idx_0 / (double)Ain->size[0];
  } else {
    outputSize_idx_0 = ceil(varargin_1[0]);
    outputSize_idx_1 = ceil(varargin_1[1]);
    scale_idx_0 = outputSize_idx_0 / (double)Ain->size[0];
    scale_idx_1 = outputSize_idx_1 / (double)Ain->size[1];
  }
  emxInit_real_T(&weights, 2);
  emxInit_int32_T(&indices, 2);
  emxInit_real_T(&out, 2);
  if (scale_idx_0 <= scale_idx_1) {
    int i;
    /*  Resize first dimension */
    contributions(Ain->size[0], outputSize_idx_0, scale_idx_0, 4.0, weights,
                  indices);
    i = out->size[0] * out->size[1];
    out->size[0] = weights->size[1];
    out->size[1] = Ain->size[1];
    emxEnsureCapacity_real_T(out, i);
    resizeAlongDim2D(Ain, weights, indices, weights->size[1], out);
    /*  Resize second dimension */
    contributions(Ain->size[1], outputSize_idx_1, scale_idx_1, 4.0, weights,
                  indices);
    i = Bout->size[0] * Bout->size[1];
    Bout->size[0] = out->size[0];
    Bout->size[1] = weights->size[1];
    emxEnsureCapacity_real_T(Bout, i);
    b_resizeAlongDim2D(out, weights, indices, weights->size[1], Bout);
  } else {
    int i;
    contributions(Ain->size[1], outputSize_idx_1, scale_idx_1, 4.0, weights,
                  indices);
    i = out->size[0] * out->size[1];
    out->size[0] = Ain->size[0];
    out->size[1] = weights->size[1];
    emxEnsureCapacity_real_T(out, i);
    b_resizeAlongDim2D(Ain, weights, indices, weights->size[1], out);
    /*  Resize second dimension */
    contributions(Ain->size[0], outputSize_idx_0, scale_idx_0, 4.0, weights,
                  indices);
    i = Bout->size[0] * Bout->size[1];
    Bout->size[0] = weights->size[1];
    Bout->size[1] = out->size[1];
    emxEnsureCapacity_real_T(Bout, i);
    resizeAlongDim2D(out, weights, indices, weights->size[1], Bout);
  }
  emxFree_real_T(&out);
  emxFree_int32_T(&indices);
  emxFree_real_T(&weights);
}

/*
 * File trailer for imresize.c
 *
 * [EOF]
 */
