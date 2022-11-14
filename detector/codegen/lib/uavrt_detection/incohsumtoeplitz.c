/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: incohsumtoeplitz.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "incohsumtoeplitz.h"
#include "any.h"
#include "eyeLike.h"
#include "find.h"
#include "locBsearch.h"
#include "minOrMax.h"
#include "mtimes.h"
#include "not.h"
#include "parenAssign2D.h"
#include "rt_nonfinite.h"
#include "sparse.h"
#include "sparse1.h"
#include "sum.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"

/* Function Definitions */
/*
 * INCOHSUMTOEPLITZ Performs the incoherent summation of time windows of an
 * input matrix S per the elements in the time selection matrix Wq.
 *    This function performs the incoherent summation of time elements within
 *    the short time Fourier transform matrix S per the selections within the
 *    Wq matrix. The rows of the S matrix represent frequency bins, whereas
 *    the columns represent the time windows. The Wq matrix is a Toeplitz
 *    based matrix with non-zero elements of each column used to select and
 *    then sum through matrix multiplication the time windows of S.
 *     abs(S).^2    *  Wq
 *    [1   2  3  4]  [1 0]
 *    [5   6  7  8]  [0 1]
 *    [9  10 11 12]  [1 0]
 *    [13 14 15 16]  [0 1]
 *
 *    The other matricies are used to select and weight the frequency and
 *    time elements of S through matrix multiplication. The Wfherm matrix
 *    applies weightings to the S matrix across frequency in order to capture
 *    energy spread across frequency bins. Fb is a matrix or a vector with 1s
 *    in elements associated with the frequency bins of Wh that are to be
 *    included for consideration. Similarly, the Tb matrix (vector) uses 1s
 *    to select time elements for consideration. Both Fb and Tb can use zeros
 *    to exclude particular frequencies or times from consideration in
 *    processing.
 *
 *    The code performs the matrix multiplication Fb*Wfherm*abs(S).^2*Tb*Wq.
 *    The sizes of these matricies must be set so that this matrix
 *    multiplication can be performed. The functions checks for correct
 *    dimensions and will generate an error of dimensional mismatch occurs.
 *    After performing the matrix multiplication of Fb*Wfherm*S*Tb*Wq, it
 *    determines which columns of the resulting matrix are maximum in each
 *    row (frequency bin). The function reports the a matrix that has the
 *    same number of rows as Fb and K columns that contains the scores for
 *    in each S time window that the maximum summed score based on the Wq
 *    matrix selections for each frequency bin. It also reports a similarly
 *    size matrix that contains the columns in S where these max scores were
 *    found
 *
 *    The number of pulses for summation (K) is extracted from Wq by querying
 *    the number of non-zero elements in the first column of the Wq matrix.
 *
 *
 * INPUTS:
 *    Fb      Frequency blinder matrix: A matrix (fz x fz) or vector (fz x 1)
 *            of elements with 1s for frequencies of the Wfherm matrix that
 *            should be considered when looking for maximum incoheren
 *            summation. If the rows of the Wfherm matrix represent
 *            frequencies of [100 50 0 -50 -100] and the search needs to
 *            focus only on the 0 and 50 Hz bins, Fb should be [0 1 1 0 0]
 *            or diag([0 1 1 0 0]). Inputs can be full or sparse.
 *    Wfherm  Hermitian of the spectral weighting matrix. This matrix should
 *            have the same number of columns as the number of rows in S. See
 *            weightingmatrix.m for information on this matrix. The function
 *            weightingmatrix.m generates Wf, so when passing Wf to this
 *            function, Wf' should be used.
 *    S       STFT output matrix
 *    Tb      Time blinder matrix: A matrix with only diagonal elements or a
 *            vector that contains 1s that corresponds to the columns (time
 *            windows) of the S matrix that should be considered for
 *            summation. If priori information informs the caller as to the
 *            potential location of the pulses in the block being processed,
 *            the Tb matrix can be used to exclude other times from
 *            consideration which can considerably decrease processing time
 *            for this function. If no-priori is available, this entry should
 *            be the identity matrix or vector of size equal to the number
 *            of columns of S.
 *    Wq      Time correlation matrix: A matrix containing 1s in entries in
 *            each column for S matrix time windows that should be summed.
 *            Wq must have the same number of rows as columns of S, but can
 *            have as many columns as summation cases that need to be
 *            considered.
 *
 * OUTPUTS:
 *    Sscores The results of the incoherent summation of S per the time
 *            selections of the inputs after looking for maximums for each
 *            frequency bin. This has the same number of rows as that of the
 *            input Fb and the same number of columns a the number of pulses
 *            used for summation. The matrix has K columns. The scores
 *            represent the square magnitudes of the selected elements of the
 *            S matrix.
 *
 *    Scols   A matrix of the columns of S (time windows of STFT)
 *            that correspond to the potential pulses identified
 *            in Sscors. The size of this matrix is the same as Sscores.
 *
 *
 * Author: Michael W. Shafer
 * Date:   2022-03-31
 *
 *
 * Arguments    : const emxArray_boolean_T *Fb
 *                const emxArray_creal_T *Wfherm
 *                const emxArray_creal_T *S
 *                const emxArray_real_T *Tb
 *                const emxArray_real_T *Wq_d
 *                const emxArray_int32_T *Wq_colidx
 *                const emxArray_int32_T *Wq_rowidx
 *                int Wq_m
 *                int Wq_n
 *                emxArray_real_T *Sscores
 *                emxArray_real_T *Scols
 * Return Type  : void
 */
void incohsumtoeplitz(const emxArray_boolean_T *Fb,
                      const emxArray_creal_T *Wfherm, const emxArray_creal_T *S,
                      const emxArray_real_T *Tb, const emxArray_real_T *Wq_d,
                      const emxArray_int32_T *Wq_colidx,
                      const emxArray_int32_T *Wq_rowidx, int Wq_m, int Wq_n,
                      emxArray_real_T *Sscores, emxArray_real_T *Scols)
{
  c_sparse FbSparseMat;
  c_sparse TbSparseMat;
  d_sparse c_expl_temp;
  emxArray_boolean_T *Fbdiags;
  emxArray_boolean_T *b_S;
  emxArray_boolean_T *b_y;
  emxArray_boolean_T *sameAsFirst_d;
  emxArray_creal_T *c_y;
  emxArray_int32_T *b_expl_temp;
  emxArray_int32_T *expl_temp;
  emxArray_int32_T *pulsesInEachColumn_colidx;
  emxArray_int32_T *pulsesInEachColumn_rowidx;
  emxArray_int32_T *r2;
  emxArray_int32_T *r3;
  emxArray_int32_T *sameAsFirst_colidx;
  emxArray_int32_T *sameAsFirst_rowidx;
  emxArray_real_T *FbmatDiagInds;
  emxArray_real_T *Srows;
  emxArray_real_T *allScores;
  emxArray_real_T *b_Tb;
  emxArray_real_T *pulsesInEachColumn_d;
  emxArray_real_T *r;
  emxArray_real_T *r1;
  emxArray_real_T *s_d;
  emxArray_uint32_T *y;
  const creal_T *S_data;
  const creal_T *Wfherm_data;
  creal_T *b_y_data;
  const double *Tb_data;
  double K;
  double s_re;
  double *FbmatDiagInds_data;
  double *Scols_data;
  double *Srows_data;
  double *allScores_data;
  double *pulsesInEachColumn_d_data;
  int i;
  int idx;
  int j;
  int k;
  int nidx;
  int numelFbDiagElements;
  int vk;
  int y_n;
  int *expl_temp_data;
  int *pulsesInEachColumn_colidx_data;
  unsigned int *y_data;
  const bool *Fb_data;
  bool found;
  bool *Fbdiags_data;
  bool *b_S_data;
  bool *sameAsFirst_d_data;
  Tb_data = Tb->data;
  S_data = S->data;
  Wfherm_data = Wfherm->data;
  Fb_data = Fb->data;
  /* Make sure the number of pulses considered for all Wq columns is the same */
  emxInit_real_T(&pulsesInEachColumn_d, 1);
  emxInit_int32_T(&pulsesInEachColumn_colidx, 1);
  emxInit_int32_T(&pulsesInEachColumn_rowidx, 1);
  b_sum(Wq_d, Wq_colidx, Wq_m, Wq_n, pulsesInEachColumn_d,
        pulsesInEachColumn_colidx, pulsesInEachColumn_rowidx, &nidx);
  pulsesInEachColumn_colidx_data = pulsesInEachColumn_colidx->data;
  pulsesInEachColumn_d_data = pulsesInEachColumn_d->data;
  emxInit_boolean_T(&b_S, 2);
  k = b_S->size[0] * b_S->size[1];
  b_S->size[0] = 1;
  b_S->size[1] = nidx;
  emxEnsureCapacity_boolean_T(b_S, k);
  b_S_data = b_S->data;
  for (k = 0; k < nidx; k++) {
    b_S_data[k] = true;
  }
  for (vk = 0; vk < nidx; vk++) {
    k = pulsesInEachColumn_colidx_data[vk];
    numelFbDiagElements = pulsesInEachColumn_colidx_data[vk + 1] - 1;
    for (idx = k; idx <= numelFbDiagElements; idx++) {
      b_S_data[vk] = (pulsesInEachColumn_d_data[idx - 1] <= 0.0);
    }
  }
  emxInit_boolean_T(&sameAsFirst_d, 1);
  emxInit_int32_T(&sameAsFirst_colidx, 1);
  emxInit_int32_T(&sameAsFirst_rowidx, 1);
  sparse(b_S, sameAsFirst_d, sameAsFirst_colidx, sameAsFirst_rowidx, &vk);
  emxInit_int32_T(&expl_temp, 1);
  emxInit_int32_T(&b_expl_temp, 1);
  any(sameAsFirst_colidx, sameAsFirst_rowidx, vk, sameAsFirst_d, expl_temp,
      b_expl_temp);
  emxInit_real_T(&s_d, 1);
  k = expl_temp->size[0];
  expl_temp->size[0] = 2;
  emxEnsureCapacity_int32_T(expl_temp, k);
  expl_temp_data = expl_temp->data;
  expl_temp_data[0] = 1;
  expl_temp_data[1] = 1;
  sparse_locBsearch(pulsesInEachColumn_rowidx, 1.0,
                    pulsesInEachColumn_colidx_data[0],
                    pulsesInEachColumn_colidx_data[1], &idx, &found);
  if (found) {
    k = s_d->size[0];
    s_d->size[0] = 1;
    emxEnsureCapacity_real_T(s_d, k);
    FbmatDiagInds_data = s_d->data;
    FbmatDiagInds_data[0] = pulsesInEachColumn_d_data[idx - 1];
    expl_temp_data[1] = 2;
  } else {
    k = s_d->size[0];
    s_d->size[0] = 1;
    emxEnsureCapacity_real_T(s_d, k);
    FbmatDiagInds_data = s_d->data;
    FbmatDiagInds_data[0] = 0.0;
  }
  sparse_eq(pulsesInEachColumn_d, pulsesInEachColumn_colidx,
            pulsesInEachColumn_rowidx, nidx, s_d, expl_temp, sameAsFirst_d,
            sameAsFirst_colidx, sameAsFirst_rowidx, &vk);
  sparse_not(sameAsFirst_colidx, sameAsFirst_rowidx, vk, sameAsFirst_d,
             pulsesInEachColumn_colidx, pulsesInEachColumn_rowidx, &nidx);
  any(pulsesInEachColumn_colidx, pulsesInEachColumn_rowidx, nidx, sameAsFirst_d,
      expl_temp, b_expl_temp);
  emxFree_int32_T(&b_expl_temp);
  if (Fb->size[0] < 1) {
    numelFbDiagElements = 1;
  } else {
    numelFbDiagElements = Fb->size[0];
  }
  emxInitStruct_sparse(&c_expl_temp);
  sparse_eyeLike(numelFbDiagElements, numelFbDiagElements, numelFbDiagElements,
                 pulsesInEachColumn_d, c_expl_temp.colidx, c_expl_temp.rowidx,
                 &vk, &y_n, &idx);
  emxInitStruct_sparse1(&FbSparseMat);
  sparse_logical(pulsesInEachColumn_d, c_expl_temp.colidx, c_expl_temp.rowidx,
                 vk, y_n, idx, FbSparseMat.d, FbSparseMat.colidx,
                 FbSparseMat.rowidx, &FbSparseMat.m, &FbSparseMat.n,
                 &FbSparseMat.maxnz);
  /* Prototype Fb matrix with identity logical matrix */
  emxInit_real_T(&FbmatDiagInds, 2);
  emxInit_uint32_T(&y);
  y_data = y->data;
  if (numelFbDiagElements < 1) {
    FbmatDiagInds->size[1] = 0;
    y->size[0] = 1;
    y->size[1] = 0;
  } else {
    k = FbmatDiagInds->size[0] * FbmatDiagInds->size[1];
    FbmatDiagInds->size[0] = 1;
    FbmatDiagInds->size[1] = numelFbDiagElements;
    emxEnsureCapacity_real_T(FbmatDiagInds, k);
    FbmatDiagInds_data = FbmatDiagInds->data;
    nidx = numelFbDiagElements - 1;
    for (k = 0; k <= nidx; k++) {
      FbmatDiagInds_data[k] = (double)k + 1.0;
    }
    k = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = numelFbDiagElements;
    emxEnsureCapacity_uint32_T(y, k);
    y_data = y->data;
    for (k = 0; k <= nidx; k++) {
      y_data[k] = (unsigned int)k + 1U;
    }
  }
  k = FbmatDiagInds->size[0] * FbmatDiagInds->size[1];
  FbmatDiagInds->size[0] = 1;
  emxEnsureCapacity_real_T(FbmatDiagInds, k);
  FbmatDiagInds_data = FbmatDiagInds->data;
  vk = FbmatDiagInds->size[1] - 1;
  for (k = 0; k <= vk; k++) {
    FbmatDiagInds_data[k] =
        (int)FbmatDiagInds_data[k] + numelFbDiagElements * ((int)y_data[k] - 1);
  }
  emxInit_boolean_T(&Fbdiags, 2);
  if (Fb->size[0] > 1) {
    nidx = 1;
  } else {
    nidx = Fb->size[0];
  }
  if (nidx == 1) {
    /* Passed a vector, so make the matrix */
    k = Fbdiags->size[0] * Fbdiags->size[1];
    Fbdiags->size[0] = Fb->size[0];
    Fbdiags->size[1] = 1;
    emxEnsureCapacity_boolean_T(Fbdiags, k);
    Fbdiags_data = Fbdiags->data;
    vk = Fb->size[0];
    for (k = 0; k < vk; k++) {
      Fbdiags_data[k] = Fb_data[k];
    }
    /* FbSparseMat = logical(speye(max(Fbsz))); */
    nidx = FbmatDiagInds->size[1];
    for (k = 0; k < nidx; k++) {
      s_re = FbmatDiagInds_data[k];
      vk = div_s32((int)s_re - 1, FbSparseMat.m);
      sparse_parenAssign2D(&FbSparseMat, Fb_data[k],
                           (int)s_re - vk * FbSparseMat.m, vk + 1);
    }
  } else {
    /* Passed a matrix, so make sparse.  */
    /* FbSparseMat = logical(sparse(Fb)); */
    k = b_S->size[0] * b_S->size[1];
    b_S->size[0] = 1;
    b_S->size[1] = FbmatDiagInds->size[1];
    emxEnsureCapacity_boolean_T(b_S, k);
    b_S_data = b_S->data;
    vk = FbmatDiagInds->size[1];
    for (k = 0; k < vk; k++) {
      b_S_data[k] = Fb_data[(int)FbmatDiagInds_data[k] - 1];
    }
    nidx = FbmatDiagInds->size[1];
    for (k = 0; k < nidx; k++) {
      s_re = FbmatDiagInds_data[k];
      vk = div_s32((int)(unsigned int)s_re - 1, FbSparseMat.m);
      sparse_parenAssign2D(&FbSparseMat, b_S_data[k],
                           (int)(unsigned int)s_re - vk * FbSparseMat.m,
                           vk + 1);
    }
    /* Had do do it this way rather than with logical(sparse(Fb)) to get code to
     * work with Fb being either a vector or matrix. */
    sparse_parenReference(FbSparseMat.d, FbSparseMat.colidx, FbSparseMat.rowidx,
                          FbSparseMat.m, FbmatDiagInds, sameAsFirst_d,
                          sameAsFirst_colidx, sameAsFirst_rowidx, &vk);
    pulsesInEachColumn_colidx_data = sameAsFirst_colidx->data;
    sameAsFirst_d_data = sameAsFirst_d->data;
    k = b_S->size[0] * b_S->size[1];
    b_S->size[0] = 1;
    b_S->size[1] = vk;
    emxEnsureCapacity_boolean_T(b_S, k);
    b_S_data = b_S->data;
    for (k = 0; k < vk; k++) {
      b_S_data[k] = false;
    }
    for (y_n = 0; y_n < vk; y_n++) {
      nidx = pulsesInEachColumn_colidx_data[y_n + 1] - 1;
      k = pulsesInEachColumn_colidx_data[y_n];
      for (idx = k; idx <= nidx; idx++) {
        b_S_data[y_n] = sameAsFirst_d_data[idx - 1];
      }
    }
    sparse_parenReference(FbSparseMat.d, FbSparseMat.colidx, FbSparseMat.rowidx,
                          FbSparseMat.m, FbmatDiagInds, sameAsFirst_d,
                          sameAsFirst_colidx, sameAsFirst_rowidx, &vk);
    pulsesInEachColumn_colidx_data = sameAsFirst_colidx->data;
    sameAsFirst_d_data = sameAsFirst_d->data;
    emxInit_boolean_T(&b_y, 2);
    k = b_y->size[0] * b_y->size[1];
    b_y->size[0] = 1;
    b_y->size[1] = vk;
    emxEnsureCapacity_boolean_T(b_y, k);
    b_S_data = b_y->data;
    for (k = 0; k < vk; k++) {
      b_S_data[k] = false;
    }
    for (y_n = 0; y_n < vk; y_n++) {
      nidx = pulsesInEachColumn_colidx_data[y_n + 1] - 1;
      k = pulsesInEachColumn_colidx_data[y_n];
      for (idx = k; idx <= nidx; idx++) {
        b_S_data[y_n] = sameAsFirst_d_data[idx - 1];
      }
    }
    k = Fbdiags->size[0] * Fbdiags->size[1];
    Fbdiags->size[0] = b_S->size[1];
    Fbdiags->size[1] = 1;
    emxEnsureCapacity_boolean_T(Fbdiags, k);
    Fbdiags_data = Fbdiags->data;
    vk = b_S->size[1];
    for (k = 0; k < vk; k++) {
      Fbdiags_data[k] = b_S_data[k];
    }
    emxFree_boolean_T(&b_y);
    /* Get the diag elements. Transpose needed for size considerations for code
     * generation. */
  }
  emxFree_boolean_T(&b_S);
  emxFree_int32_T(&sameAsFirst_rowidx);
  emxFree_int32_T(&sameAsFirst_colidx);
  /* Time Blinder (Tb) matrix definitions: */
  if (Tb->size[0] < 1) {
    numelFbDiagElements = 1;
  } else {
    numelFbDiagElements = Tb->size[0];
  }
  sparse_eyeLike(numelFbDiagElements, numelFbDiagElements, numelFbDiagElements,
                 pulsesInEachColumn_d, c_expl_temp.colidx, c_expl_temp.rowidx,
                 &vk, &y_n, &idx);
  emxInitStruct_sparse1(&TbSparseMat);
  sparse_logical(pulsesInEachColumn_d, c_expl_temp.colidx, c_expl_temp.rowidx,
                 vk, y_n, idx, TbSparseMat.d, TbSparseMat.colidx,
                 TbSparseMat.rowidx, &TbSparseMat.m, &TbSparseMat.n,
                 &TbSparseMat.maxnz);
  /* Prototype Fb matrix with identity logical matrix */
  if (numelFbDiagElements < 1) {
    FbmatDiagInds->size[1] = 0;
    y->size[0] = 1;
    y->size[1] = 0;
  } else {
    k = FbmatDiagInds->size[0] * FbmatDiagInds->size[1];
    FbmatDiagInds->size[0] = 1;
    FbmatDiagInds->size[1] = numelFbDiagElements;
    emxEnsureCapacity_real_T(FbmatDiagInds, k);
    FbmatDiagInds_data = FbmatDiagInds->data;
    nidx = numelFbDiagElements - 1;
    for (k = 0; k <= nidx; k++) {
      FbmatDiagInds_data[k] = (double)k + 1.0;
    }
    k = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = numelFbDiagElements;
    emxEnsureCapacity_uint32_T(y, k);
    y_data = y->data;
    for (k = 0; k <= nidx; k++) {
      y_data[k] = (unsigned int)k + 1U;
    }
  }
  k = FbmatDiagInds->size[0] * FbmatDiagInds->size[1];
  FbmatDiagInds->size[0] = 1;
  emxEnsureCapacity_real_T(FbmatDiagInds, k);
  FbmatDiagInds_data = FbmatDiagInds->data;
  vk = FbmatDiagInds->size[1] - 1;
  for (k = 0; k <= vk; k++) {
    FbmatDiagInds_data[k] =
        (int)FbmatDiagInds_data[k] + numelFbDiagElements * ((int)y_data[k] - 1);
  }
  if (Tb->size[0] > 1) {
    nidx = 1;
  } else {
    nidx = Tb->size[0];
  }
  if (nidx == 1) {
    if (Tb->size[0] < 1) {
      nidx = 1;
    } else {
      nidx = Tb->size[0];
    }
    sparse_eyeLike(nidx, nidx, nidx, pulsesInEachColumn_d, c_expl_temp.colidx,
                   c_expl_temp.rowidx, &vk, &y_n, &idx);
    sparse_logical(pulsesInEachColumn_d, c_expl_temp.colidx, c_expl_temp.rowidx,
                   vk, y_n, idx, TbSparseMat.d, TbSparseMat.colidx,
                   TbSparseMat.rowidx, &TbSparseMat.m, &TbSparseMat.n,
                   &TbSparseMat.maxnz);
    b_sparse(Tb, pulsesInEachColumn_d, pulsesInEachColumn_rowidx,
             pulsesInEachColumn_colidx, &vk, &nidx);
    pulsesInEachColumn_colidx_data = pulsesInEachColumn_rowidx->data;
    pulsesInEachColumn_d_data = pulsesInEachColumn_d->data;
    if (nidx < 1) {
      nidx = 1;
    }
    k = sameAsFirst_d->size[0];
    sameAsFirst_d->size[0] = nidx;
    emxEnsureCapacity_boolean_T(sameAsFirst_d, k);
    sameAsFirst_d_data = sameAsFirst_d->data;
    for (k = 0; k < nidx; k++) {
      sameAsFirst_d_data[k] = false;
    }
    nidx =
        pulsesInEachColumn_colidx_data[pulsesInEachColumn_rowidx->size[0] - 1] -
        1;
    if (nidx < 1) {
      nidx = 1;
    }
    for (k = 0; k < nidx; k++) {
      sameAsFirst_d_data[k] = (pulsesInEachColumn_d_data[k] != 0.0);
    }
    sparse_parenAssign(&TbSparseMat, sameAsFirst_d, pulsesInEachColumn_rowidx,
                       pulsesInEachColumn_colidx, vk, FbmatDiagInds);
  } else {
    emxInit_real_T(&b_Tb, 2);
    k = b_Tb->size[0] * b_Tb->size[1];
    b_Tb->size[0] = 1;
    b_Tb->size[1] = FbmatDiagInds->size[1];
    emxEnsureCapacity_real_T(b_Tb, k);
    Srows_data = b_Tb->data;
    vk = FbmatDiagInds->size[1];
    for (k = 0; k < vk; k++) {
      Srows_data[k] = Tb_data[(int)FbmatDiagInds_data[k] - 1];
    }
    b_sparse_parenAssign(&TbSparseMat, b_Tb, FbmatDiagInds);
    emxFree_real_T(&b_Tb);
    /* Had do do it this way rather than with logical(sparse(Tb)) to get code to
     * work with Tb being either a vector or matrix. */
  }
  emxFree_real_T(&FbmatDiagInds);
  emxFree_boolean_T(&sameAsFirst_d);
  /*  Perform the incoherent summation */
  /* S          = abs(S).^2; */
  b_sparse_parenReference(Wq_d, Wq_colidx, Wq_rowidx, Wq_m,
                          pulsesInEachColumn_d, pulsesInEachColumn_rowidx,
                          pulsesInEachColumn_colidx, &vk, &nidx);
  c_sum(pulsesInEachColumn_d, pulsesInEachColumn_rowidx, vk, s_d, expl_temp,
        pulsesInEachColumn_colidx);
  expl_temp_data = expl_temp->data;
  FbmatDiagInds_data = s_d->data;
  K = 0.0;
  nidx = expl_temp_data[1] - 1;
  k = expl_temp_data[0];
  emxFree_int32_T(&expl_temp);
  for (idx = k; idx <= nidx; idx++) {
    K = FbmatDiagInds_data[0];
  }
  emxFree_real_T(&s_d);
  vk = Wfherm->size[0];
  y_n = Wfherm->size[1];
  idx = S->size[1];
  emxInit_creal_T(&c_y, 2);
  k = c_y->size[0] * c_y->size[1];
  c_y->size[0] = Wfherm->size[0];
  c_y->size[1] = S->size[1];
  emxEnsureCapacity_creal_T(c_y, k);
  b_y_data = c_y->data;
  for (j = 0; j < idx; j++) {
    int boffset;
    numelFbDiagElements = j * vk;
    boffset = j * S->size[0];
    for (i = 0; i < vk; i++) {
      double s_im;
      s_re = 0.0;
      s_im = 0.0;
      for (k = 0; k < y_n; k++) {
        nidx = boffset + k;
        s_re += Wfherm_data[k * Wfherm->size[0] + i].re * S_data[nidx].re -
                Wfherm_data[k * Wfherm->size[0] + i].im * S_data[nidx].im;
        s_im += Wfherm_data[k * Wfherm->size[0] + i].re * S_data[nidx].im +
                Wfherm_data[k * Wfherm->size[0] + i].im * S_data[nidx].re;
      }
      k = numelFbDiagElements + i;
      b_y_data[k].re = s_re;
      b_y_data[k].im = s_im;
    }
  }
  nidx = c_y->size[0] * c_y->size[1];
  emxInit_real_T(&Srows, 2);
  k = Srows->size[0] * Srows->size[1];
  Srows->size[0] = c_y->size[0];
  Srows->size[1] = c_y->size[1];
  emxEnsureCapacity_real_T(Srows, k);
  Srows_data = Srows->data;
  for (k = 0; k < nidx; k++) {
    Srows_data[k] = rt_hypotd_snf(b_y_data[k].re, b_y_data[k].im);
  }
  emxFree_creal_T(&c_y);
  emxInit_real_T(&allScores, 2);
  k = allScores->size[0] * allScores->size[1];
  allScores->size[0] = Srows->size[0];
  allScores->size[1] = Srows->size[1];
  emxEnsureCapacity_real_T(allScores, k);
  allScores_data = allScores->data;
  vk = Srows->size[0] * Srows->size[1];
  for (k = 0; k < vk; k++) {
    s_re = Srows_data[k];
    allScores_data[k] = s_re * s_re;
  }
  b_sparse_mtimes(FbSparseMat.d, FbSparseMat.colidx, FbSparseMat.rowidx,
                  FbSparseMat.m, FbSparseMat.n, allScores, Srows);
  emxFreeStruct_sparse1(&FbSparseMat);
  emxInit_real_T(&r, 2);
  c_sparse_mtimes(Srows, TbSparseMat.d, TbSparseMat.colidx, TbSparseMat.rowidx,
                  TbSparseMat.n, r);
  emxFreeStruct_sparse1(&TbSparseMat);
  emxInit_real_T(&r1, 2);
  sparse_mtimes(r, Wq_d, Wq_colidx, Wq_rowidx, Wq_n, r1);
  emxFree_real_T(&r);
  b_maximum(r1, pulsesInEachColumn_d, pulsesInEachColumn_colidx);
  pulsesInEachColumn_colidx_data = pulsesInEachColumn_colidx->data;
  emxFree_real_T(&r1);
  /* Check max on each row (frequency). This gives the columns of the resulting
   * matrix output with the max for each frequency bin */
  /* This and the next line gets the column numbers (time windows) of the S
   * matrix where the highest K-summed entries exist for each row (frequency
   * bin) */
  k = pulsesInEachColumn_d->size[0];
  pulsesInEachColumn_d->size[0] = pulsesInEachColumn_colidx->size[0];
  emxEnsureCapacity_real_T(pulsesInEachColumn_d, k);
  pulsesInEachColumn_d_data = pulsesInEachColumn_d->data;
  vk = pulsesInEachColumn_colidx->size[0];
  for (k = 0; k < vk; k++) {
    pulsesInEachColumn_d_data[k] = pulsesInEachColumn_colidx_data[k];
  }
  c_sparse_parenReference(Wq_d, Wq_colidx, Wq_rowidx, Wq_m,
                          pulsesInEachColumn_d, &c_expl_temp);
  e_eml_find(c_expl_temp.colidx, c_expl_temp.rowidx, pulsesInEachColumn_colidx,
             pulsesInEachColumn_rowidx);
  pulsesInEachColumn_colidx_data = pulsesInEachColumn_colidx->data;
  emxFreeStruct_sparse(&c_expl_temp);
  emxFree_int32_T(&pulsesInEachColumn_rowidx);
  k = pulsesInEachColumn_d->size[0];
  pulsesInEachColumn_d->size[0] = pulsesInEachColumn_colidx->size[0];
  emxEnsureCapacity_real_T(pulsesInEachColumn_d, k);
  pulsesInEachColumn_d_data = pulsesInEachColumn_d->data;
  vk = pulsesInEachColumn_colidx->size[0];
  for (k = 0; k < vk; k++) {
    pulsesInEachColumn_d_data[k] = pulsesInEachColumn_colidx_data[k];
  }
  emxFree_int32_T(&pulsesInEachColumn_colidx);
  /* Get the rows that had 1s in them that corresponded to the winning columns
   */
  y_n = (int)K;
  nidx = (int)((double)pulsesInEachColumn_d->size[0] / K);
  k = Scols->size[0] * Scols->size[1];
  Scols->size[0] = nidx;
  Scols->size[1] = (int)K;
  emxEnsureCapacity_real_T(Scols, k);
  Scols_data = Scols->data;
  for (k = 0; k < y_n; k++) {
    for (numelFbDiagElements = 0; numelFbDiagElements < nidx;
         numelFbDiagElements++) {
      Scols_data[numelFbDiagElements + Scols->size[0] * k] =
          pulsesInEachColumn_d_data[k + (int)K * numelFbDiagElements];
    }
  }
  if (Wfherm->size[0] < 1) {
    y->size[0] = 1;
    y->size[1] = 0;
  } else {
    k = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = Wfherm->size[0];
    emxEnsureCapacity_uint32_T(y, k);
    y_data = y->data;
    vk = Wfherm->size[0] - 1;
    for (k = 0; k <= vk; k++) {
      y_data[k] = (unsigned int)k + 1U;
    }
  }
  k = pulsesInEachColumn_d->size[0];
  pulsesInEachColumn_d->size[0] = y->size[1];
  emxEnsureCapacity_real_T(pulsesInEachColumn_d, k);
  pulsesInEachColumn_d_data = pulsesInEachColumn_d->data;
  vk = y->size[1];
  for (k = 0; k < vk; k++) {
    pulsesInEachColumn_d_data[k] = y_data[k];
  }
  emxFree_uint32_T(&y);
  k = Srows->size[0] * Srows->size[1];
  Srows->size[0] = pulsesInEachColumn_d->size[0];
  Srows->size[1] = (int)K;
  emxEnsureCapacity_real_T(Srows, k);
  Srows_data = Srows->data;
  nidx = pulsesInEachColumn_d->size[0];
  for (idx = 0; idx < y_n; idx++) {
    vk = idx * nidx;
    for (k = 0; k < nidx; k++) {
      Srows_data[vk + k] = pulsesInEachColumn_d_data[k];
    }
  }
  emxFree_real_T(&pulsesInEachColumn_d);
  nidx = allScores->size[0];
  vk = Srows->size[0] * Srows->size[1];
  for (k = 0; k < vk; k++) {
    Srows_data[k] = (int)Srows_data[k] + nidx * ((int)Scols_data[k] - 1);
  }
  k = Sscores->size[0] * Sscores->size[1];
  Sscores->size[0] = Srows->size[0];
  Sscores->size[1] = Srows->size[1];
  emxEnsureCapacity_real_T(Sscores, k);
  FbmatDiagInds_data = Sscores->data;
  vk = Srows->size[0] * Srows->size[1];
  for (k = 0; k < vk; k++) {
    FbmatDiagInds_data[k] = allScores_data[(int)Srows_data[k] - 1];
  }
  emxFree_real_T(&allScores);
  /* Extract individual pulse scores */
  /* The max function will just return the first index if all elements are */
  /* equal. Here we zero out the scores and set the cols to NaN for frequencies
   */
  /* were ignored with the frequency blinder matrix. */
  vk = Fbdiags->size[0] - 1;
  nidx = 0;
  for (i = 0; i <= vk; i++) {
    if (!Fbdiags_data[i]) {
      nidx++;
    }
  }
  emxInit_int32_T(&r2, 1);
  k = r2->size[0];
  r2->size[0] = nidx;
  emxEnsureCapacity_int32_T(r2, k);
  pulsesInEachColumn_colidx_data = r2->data;
  nidx = 0;
  for (i = 0; i <= vk; i++) {
    if (!Fbdiags_data[i]) {
      pulsesInEachColumn_colidx_data[nidx] = i + 1;
      nidx++;
    }
  }
  vk = Srows->size[1];
  emxFree_real_T(&Srows);
  for (k = 0; k < vk; k++) {
    nidx = r2->size[0];
    for (numelFbDiagElements = 0; numelFbDiagElements < nidx;
         numelFbDiagElements++) {
      FbmatDiagInds_data[(pulsesInEachColumn_colidx_data[numelFbDiagElements] +
                          Sscores->size[0] * k) -
                         1] = rtNaN;
    }
  }
  emxFree_int32_T(&r2);
  vk = Fbdiags->size[0] - 1;
  nidx = 0;
  for (i = 0; i <= vk; i++) {
    if (!Fbdiags_data[i]) {
      nidx++;
    }
  }
  emxInit_int32_T(&r3, 1);
  k = r3->size[0];
  r3->size[0] = nidx;
  emxEnsureCapacity_int32_T(r3, k);
  pulsesInEachColumn_colidx_data = r3->data;
  nidx = 0;
  for (i = 0; i <= vk; i++) {
    if (!Fbdiags_data[i]) {
      pulsesInEachColumn_colidx_data[nidx] = i + 1;
      nidx++;
    }
  }
  emxFree_boolean_T(&Fbdiags);
  vk = Scols->size[1];
  for (k = 0; k < vk; k++) {
    nidx = r3->size[0];
    for (numelFbDiagElements = 0; numelFbDiagElements < nidx;
         numelFbDiagElements++) {
      Scols_data[(pulsesInEachColumn_colidx_data[numelFbDiagElements] +
                  Scols->size[0] * k) -
                 1] = rtNaN;
    }
  }
  emxFree_int32_T(&r3);
}

/*
 * File trailer for incohsumtoeplitz.c
 *
 * [EOF]
 */
