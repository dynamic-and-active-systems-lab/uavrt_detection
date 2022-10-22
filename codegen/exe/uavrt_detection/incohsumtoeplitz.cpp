//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: incohsumtoeplitz.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Oct-2022 17:38:50
//

// Include Files
#include "incohsumtoeplitz.h"
#include "any1.h"
#include "find.h"
#include "locBsearch.h"
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "sparse.h"
#include "sparse1.h"
#include "sum.h"
#include "uavrt_detection_rtwutil.h"
#include "coder_array.h"

// Function Definitions
//
// INCOHSUMTOEPLITZ Performs the incoherent summation of time windows of an
// input matrix S per the elements in the time selection matrix Wq.
//    This function performs the incoherent summation of time elements within
//    the short time Fourier transform matrix S per the selections within the
//    Wq matrix. The rows of the S matrix represent frequency bins, whereas
//    the columns represent the time windows. The Wq matrix is a Toeplitz
//    based matrix with non-zero elements of each column used to select and
//    then sum through matrix multiplication the time windows of S.
//     abs(S).^2    *  Wq
//    [1   2  3  4]  [1 0]
//    [5   6  7  8]  [0 1]
//    [9  10 11 12]  [1 0]
//    [13 14 15 16]  [0 1]
//
//    The other matricies are used to select and weight the frequency and
//    time elements of S through matrix multiplication. The Wfherm matrix
//    applies weightings to the S matrix across frequency in order to capture
//    energy spread across frequency bins. Fb is a matrix or a vector with 1s
//    in elements associated with the frequency bins of Wh that are to be
//    included for consideration. Similarly, the Tb matrix (vector) uses 1s
//    to select time elements for consideration. Both Fb and Tb can use zeros
//    to exclude particular frequencies or times from consideration in
//    processing.
//
//    The code performs the matrix multiplication Fb*Wfherm*abs(S).^2*Tb*Wq.
//    The sizes of these matricies must be set so that this matrix
//    multiplication can be performed. The functions checks for correct
//    dimensions and will generate an error of dimensional mismatch occurs.
//    After performing the matrix multiplication of Fb*Wfherm*S*Tb*Wq, it
//    determines which columns of the resulting matrix are maximum in each
//    row (frequency bin). The function reports the a matrix that has the
//    same number of rows as Fb and K columns that contains the scores for
//    in each S time window that the maximum summed score based on the Wq
//    matrix selections for each frequency bin. It also reports a similarly
//    size matrix that contains the columns in S where these max scores were
//    found
//
//    The number of pulses for summation (K) is extracted from Wq by querying
//    the number of non-zero elements in the first column of the Wq matrix.
//
//
// INPUTS:
//    Fb      Frequency blinder matrix: A matrix (fz x fz) or vector (fz x 1)
//            of elements with 1s for frequencies of the Wfherm matrix that
//            should be considered when looking for maximum incoheren
//            summation. If the rows of the Wfherm matrix represent
//            frequencies of [100 50 0 -50 -100] and the search needs to
//            focus only on the 0 and 50 Hz bins, Fb should be [0 1 1 0 0]
//            or diag([0 1 1 0 0]). Inputs can be full or sparse.
//    Wfherm  Hermitian of the spectral weighting matrix. This matrix should
//            have the same number of columns as the number of rows in S. See
//            weightingmatrix.m for information on this matrix. The function
//            weightingmatrix.m generates Wf, so when passing Wf to this
//            function, Wf' should be used.
//    S       STFT output matrix
//    Tb      Time blinder matrix: A matrix with only diagonal elements or a
//            vector that contains 1s that corresponds to the columns (time
//            windows) of the S matrix that should be considered for
//            summation. If priori information informs the caller as to the
//            potential location of the pulses in the block being processed,
//            the Tb matrix can be used to exclude other times from
//            consideration which can considerably decrease processing time
//            for this function. If no-priori is available, this entry should
//            be the identity matrix or vector of size equal to the number
//            of columns of S.
//    Wq      Time correlation matrix: A matrix containing 1s in entries in
//            each column for S matrix time windows that should be summed.
//            Wq must have the same number of rows as columns of S, but can
//            have as many columns as summation cases that need to be
//            considered.
//
// OUTPUTS:
//    Sscores The results of the incoherent summation of S per the time
//            selections of the inputs after looking for maximums for each
//            frequency bin. This has the same number of rows as that of the
//            input Fb and the same number of columns a the number of pulses
//            used for summation. The matrix has K columns. The scores
//            represent the square magnitudes of the selected elements of the
//            S matrix.
//
//    Scols   A matrix of the columns of S (time windows of STFT)
//            that correspond to the potential pulses identified
//            in Sscors. The size of this matrix is the same as Sscores.
//
//
// Author: Michael W. Shafer
// Date:   2022-03-31
//
//
// Arguments    : const coder::array<boolean_T, 1U> &Fb
//                const coder::array<creal_T, 2U> &Wfherm
//                const coder::array<creal_T, 2U> &S
//                const coder::array<double, 1U> &Tb
//                const coder::sparse *Wq
//                coder::array<double, 2U> &Sscores
//                coder::array<double, 2U> &Scols
// Return Type  : void
//
void incohsumtoeplitz(const coder::array<boolean_T, 1U> &Fb,
                      const coder::array<creal_T, 2U> &Wfherm,
                      const coder::array<creal_T, 2U> &S,
                      const coder::array<double, 1U> &Tb,
                      const coder::sparse *Wq,
                      coder::array<double, 2U> &Sscores,
                      coder::array<double, 2U> &Scols)
{
  coder::b_sparse pulsesInEachColumn;
  coder::c_sparse r;
  coder::c_sparse sameAsFirst_tmp;
  coder::d_sparse b_sameAsFirst_tmp;
  coder::d_sparse r1;
  coder::e_sparse s;
  coder::f_sparse FbSparseMat;
  coder::f_sparse TbSparseMat;
  coder::g_sparse b_this;
  coder::h_sparse d_y;
  coder::sparse y;
  coder::array<creal_T, 2U> e_y;
  coder::array<double, 2U> FbmatDiagInds;
  coder::array<double, 2U> Srows;
  coder::array<double, 2U> allScores;
  coder::array<double, 2U> b_Tb;
  coder::array<double, 2U> r2;
  coder::array<double, 2U> r3;
  coder::array<double, 1U> ex;
  coder::array<unsigned int, 2U> b_y;
  coder::array<int, 1U> idx;
  coder::array<int, 1U> jj;
  coder::array<int, 1U> r4;
  coder::array<int, 1U> r5;
  coder::array<boolean_T, 2U> Fbdiags;
  coder::array<boolean_T, 2U> b_S;
  coder::array<boolean_T, 2U> c_y;
  double K;
  double s_re;
  int boffset;
  int coffset;
  int k;
  int loop_ub;
  int n;
  int numelFbDiagElements;
  int vk;
  boolean_T found;
  // Make sure the number of pulses considered for all Wq columns is the same
  coder::sum(Wq, &pulsesInEachColumn);
  b_S.set_size(1, pulsesInEachColumn.n);
  loop_ub = pulsesInEachColumn.n;
  for (k = 0; k < loop_ub; k++) {
    b_S[k] = true;
  }
  n = pulsesInEachColumn.n;
  for (vk = 0; vk < n; vk++) {
    k = pulsesInEachColumn.colidx[vk];
    boffset = pulsesInEachColumn.colidx[vk + 1] - 1;
    for (loop_ub = k; loop_ub <= boffset; loop_ub++) {
      b_S[vk] = (pulsesInEachColumn.d[loop_ub - 1] <= 0.0);
    }
  }
  coder::i_sparse(b_S, &sameAsFirst_tmp);
  coder::any(&sameAsFirst_tmp, &b_sameAsFirst_tmp);
  s.colidx.set_size(2);
  s.colidx[0] = 1;
  s.colidx[1] = 1;
  coder::sparse_locBsearch(pulsesInEachColumn.rowidx, 1.0,
                           pulsesInEachColumn.colidx[0],
                           pulsesInEachColumn.colidx[1], &loop_ub, &found);
  if (found) {
    s.d.set_size(1);
    s.d[0] = pulsesInEachColumn.d[loop_ub - 1];
    s.rowidx.set_size(1);
    s.rowidx[0] = 1;
    s.colidx[1] = 2;
  } else {
    s.d.set_size(1);
    s.d[0] = 0.0;
    s.rowidx.set_size(1);
    s.rowidx[0] = 0;
  }
  pulsesInEachColumn.eq(&s, &sameAsFirst_tmp);
  sameAsFirst_tmp.b_not(&r);
  coder::any(&r, &r1);
  if (Fb.size(0) < 1) {
    numelFbDiagElements = 1;
  } else {
    numelFbDiagElements = Fb.size(0);
  }
  coder::sparse::eyeLike(numelFbDiagElements, numelFbDiagElements,
                         numelFbDiagElements, &y);
  y.logical(&FbSparseMat);
  // Prototype Fb matrix with identity logical matrix
  if (numelFbDiagElements < 1) {
    FbmatDiagInds.set_size(FbmatDiagInds.size(0), 0);
    b_y.set_size(1, 0);
  } else {
    FbmatDiagInds.set_size(1, numelFbDiagElements);
    vk = numelFbDiagElements - 1;
    b_y.set_size(1, numelFbDiagElements);
    for (k = 0; k <= vk; k++) {
      FbmatDiagInds[k] = static_cast<double>(k) + 1.0;
      b_y[k] = static_cast<unsigned int>(k) + 1U;
    }
  }
  FbmatDiagInds.set_size(1, FbmatDiagInds.size(1));
  loop_ub = FbmatDiagInds.size(1) - 1;
  for (k = 0; k <= loop_ub; k++) {
    FbmatDiagInds[k] = static_cast<int>(FbmatDiagInds[k]) +
                       numelFbDiagElements * (static_cast<int>(b_y[k]) - 1);
  }
  if (Fb.size(0) > 1) {
    n = 1;
  } else {
    n = Fb.size(0);
  }
  if (n == 1) {
    // Passed a vector, so make the matrix
    Fbdiags.set_size(Fb.size(0), 1);
    loop_ub = Fb.size(0);
    for (k = 0; k < loop_ub; k++) {
      Fbdiags[k] = Fb[k];
    }
    // FbSparseMat = logical(speye(max(Fbsz)));
    numelFbDiagElements = FbmatDiagInds.size(1);
    for (k = 0; k < numelFbDiagElements; k++) {
      s_re = FbmatDiagInds[k];
      vk = div_s32(static_cast<int>(s_re) - 1, FbSparseMat.m);
      FbSparseMat.parenAssign2D(
          Fb[k],
          static_cast<double>(static_cast<int>(s_re) - vk * FbSparseMat.m),
          static_cast<double>(vk + 1));
    }
  } else {
    // Passed a matrix, so make sparse.
    // FbSparseMat = logical(sparse(Fb));
    b_S.set_size(1, FbmatDiagInds.size(1));
    loop_ub = FbmatDiagInds.size(1);
    for (k = 0; k < loop_ub; k++) {
      b_S[k] = Fb[static_cast<int>(FbmatDiagInds[k]) - 1];
    }
    numelFbDiagElements = FbmatDiagInds.size(1);
    for (k = 0; k < numelFbDiagElements; k++) {
      s_re = FbmatDiagInds[k];
      vk = div_s32(static_cast<int>(static_cast<unsigned int>(s_re)) - 1,
                   FbSparseMat.m);
      FbSparseMat.parenAssign2D(
          b_S[k],
          static_cast<double>(
              static_cast<int>(static_cast<unsigned int>(s_re)) -
              vk * FbSparseMat.m),
          static_cast<double>(vk + 1));
    }
    // Had do do it this way rather than with logical(sparse(Fb)) to get code to
    // work with Fb being either a vector or matrix.
    FbSparseMat.parenReference(FbmatDiagInds, &sameAsFirst_tmp);
    b_S.set_size(1, sameAsFirst_tmp.n);
    loop_ub = sameAsFirst_tmp.n;
    for (k = 0; k < loop_ub; k++) {
      b_S[k] = false;
    }
    k = sameAsFirst_tmp.n;
    for (numelFbDiagElements = 0; numelFbDiagElements < k;
         numelFbDiagElements++) {
      vk = sameAsFirst_tmp.colidx[numelFbDiagElements + 1] - 1;
      boffset = sameAsFirst_tmp.colidx[numelFbDiagElements];
      for (loop_ub = boffset; loop_ub <= vk; loop_ub++) {
        b_S[numelFbDiagElements] = sameAsFirst_tmp.d[loop_ub - 1];
      }
    }
    c_y.set_size(1, sameAsFirst_tmp.n);
    loop_ub = sameAsFirst_tmp.n;
    for (k = 0; k < loop_ub; k++) {
      c_y[k] = false;
    }
    k = sameAsFirst_tmp.n;
    for (numelFbDiagElements = 0; numelFbDiagElements < k;
         numelFbDiagElements++) {
      vk = sameAsFirst_tmp.colidx[numelFbDiagElements + 1] - 1;
      boffset = sameAsFirst_tmp.colidx[numelFbDiagElements];
      for (loop_ub = boffset; loop_ub <= vk; loop_ub++) {
        c_y[numelFbDiagElements] = sameAsFirst_tmp.d[loop_ub - 1];
      }
    }
    Fbdiags.set_size(b_S.size(1), 1);
    loop_ub = b_S.size(1);
    for (k = 0; k < loop_ub; k++) {
      Fbdiags[k] = c_y[k];
    }
    // Get the diag elements. Transpose needed for size considerations for code
    // generation.
  }
  // Time Blinder (Tb) matrix definitions:
  if (Tb.size(0) < 1) {
    numelFbDiagElements = 1;
  } else {
    numelFbDiagElements = Tb.size(0);
  }
  coder::sparse::eyeLike(numelFbDiagElements, numelFbDiagElements,
                         numelFbDiagElements, &y);
  y.logical(&TbSparseMat);
  // Prototype Fb matrix with identity logical matrix
  if (numelFbDiagElements < 1) {
    FbmatDiagInds.set_size(FbmatDiagInds.size(0), 0);
    b_y.set_size(1, 0);
  } else {
    FbmatDiagInds.set_size(1, numelFbDiagElements);
    vk = numelFbDiagElements - 1;
    b_y.set_size(1, numelFbDiagElements);
    for (k = 0; k <= vk; k++) {
      FbmatDiagInds[k] = static_cast<double>(k) + 1.0;
      b_y[k] = static_cast<unsigned int>(k) + 1U;
    }
  }
  FbmatDiagInds.set_size(1, FbmatDiagInds.size(1));
  loop_ub = FbmatDiagInds.size(1) - 1;
  for (k = 0; k <= loop_ub; k++) {
    FbmatDiagInds[k] = static_cast<int>(FbmatDiagInds[k]) +
                       numelFbDiagElements * (static_cast<int>(b_y[k]) - 1);
  }
  if (Tb.size(0) > 1) {
    n = 1;
  } else {
    n = Tb.size(0);
  }
  if (n == 1) {
    if (Tb.size(0) < 1) {
      numelFbDiagElements = 1;
    } else {
      numelFbDiagElements = Tb.size(0);
    }
    coder::sparse::eyeLike(numelFbDiagElements, numelFbDiagElements,
                           numelFbDiagElements, &y);
    y.logical(&TbSparseMat);
    coder::j_sparse(Tb, &b_this);
    d_y.m = b_this.m;
    numelFbDiagElements = b_this.maxnz;
    if (numelFbDiagElements < 1) {
      numelFbDiagElements = 1;
    }
    d_y.d.set_size(numelFbDiagElements);
    for (k = 0; k < numelFbDiagElements; k++) {
      d_y.d[k] = false;
    }
    d_y.rowidx.set_size(b_this.rowidx.size(0));
    loop_ub = b_this.rowidx.size(0);
    for (k = 0; k < loop_ub; k++) {
      d_y.rowidx[k] = b_this.rowidx[k];
    }
    d_y.colidx.set_size(b_this.colidx.size(0));
    loop_ub = b_this.colidx.size(0);
    for (k = 0; k < loop_ub; k++) {
      d_y.colidx[k] = b_this.colidx[k];
    }
    numelFbDiagElements = b_this.colidx[b_this.colidx.size(0) - 1] - 1;
    if (numelFbDiagElements < 1) {
      numelFbDiagElements = 1;
    }
    for (k = 0; k < numelFbDiagElements; k++) {
      d_y.d[k] = (b_this.d[k] != 0.0);
    }
    TbSparseMat.parenAssign(&d_y, FbmatDiagInds);
  } else {
    b_Tb.set_size(1, FbmatDiagInds.size(1));
    loop_ub = FbmatDiagInds.size(1);
    for (k = 0; k < loop_ub; k++) {
      b_Tb[k] = Tb[static_cast<int>(FbmatDiagInds[k]) - 1];
    }
    TbSparseMat.parenAssign(b_Tb, FbmatDiagInds);
    // Had do do it this way rather than with logical(sparse(Tb)) to get code to
    // work with Tb being either a vector or matrix.
  }
  //  Perform the incoherent summation
  // S          = abs(S).^2;
  Wq->parenReference(&b_this);
  coder::sum(&b_this, &s);
  K = 0.0;
  vk = s.colidx[1] - 1;
  k = s.colidx[0];
  for (loop_ub = k; loop_ub <= vk; loop_ub++) {
    K = s.d[0];
  }
  numelFbDiagElements = Wfherm.size(0);
  loop_ub = Wfherm.size(1);
  n = S.size(1);
  e_y.set_size(Wfherm.size(0), S.size(1));
  for (int j{0}; j < n; j++) {
    coffset = j * numelFbDiagElements;
    boffset = j * S.size(0);
    for (int i{0}; i < numelFbDiagElements; i++) {
      double s_im;
      s_re = 0.0;
      s_im = 0.0;
      for (k = 0; k < loop_ub; k++) {
        vk = boffset + k;
        s_re += Wfherm[k * Wfherm.size(0) + i].re * S[vk].re -
                Wfherm[k * Wfherm.size(0) + i].im * S[vk].im;
        s_im += Wfherm[k * Wfherm.size(0) + i].re * S[vk].im +
                Wfherm[k * Wfherm.size(0) + i].im * S[vk].re;
      }
      k = coffset + i;
      e_y[k].re = s_re;
      e_y[k].im = s_im;
    }
  }
  numelFbDiagElements = e_y.size(0) * e_y.size(1);
  Srows.set_size(e_y.size(0), e_y.size(1));
  for (k = 0; k < numelFbDiagElements; k++) {
    Srows[k] = rt_hypotd_snf(e_y[k].re, e_y[k].im);
  }
  allScores.set_size(Srows.size(0), Srows.size(1));
  loop_ub = Srows.size(0) * Srows.size(1);
  for (k = 0; k < loop_ub; k++) {
    s_re = Srows[k];
    allScores[k] = s_re * s_re;
  }
  FbSparseMat.mtimes(allScores, Srows);
  TbSparseMat.b_mtimes(Srows, r2);
  Wq->mtimes(r2, r3);
  coder::internal::maximum(r3, ex, idx);
  // Check max on each row (frequency). This gives the columns of the resulting
  // matrix output with the max for each frequency bin This and the next line
  // gets the column numbers (time windows) of the S matrix where the highest
  // K-summed entries exist for each row (frequency bin)
  ex.set_size(idx.size(0));
  loop_ub = idx.size(0);
  for (k = 0; k < loop_ub; k++) {
    ex[k] = idx[k];
  }
  Wq->parenReference(ex, &y);
  coder::e_eml_find(&y, idx, jj);
  ex.set_size(idx.size(0));
  loop_ub = idx.size(0);
  for (k = 0; k < loop_ub; k++) {
    ex[k] = idx[k];
  }
  // Get the rows that had 1s in them that corresponded to the winning columns
  coffset = static_cast<int>(K);
  vk = static_cast<int>(static_cast<double>(ex.size(0)) / K);
  Scols.set_size(vk, coffset);
  for (k = 0; k < coffset; k++) {
    for (boffset = 0; boffset < vk; boffset++) {
      Scols[boffset + Scols.size(0) * k] =
          ex[k + static_cast<int>(K) * boffset];
    }
  }
  if (Wfherm.size(0) < 1) {
    b_y.set_size(1, 0);
  } else {
    b_y.set_size(1, Wfherm.size(0));
    loop_ub = Wfherm.size(0) - 1;
    for (k = 0; k <= loop_ub; k++) {
      b_y[k] = static_cast<unsigned int>(k) + 1U;
    }
  }
  ex.set_size(b_y.size(1));
  loop_ub = b_y.size(1);
  for (k = 0; k < loop_ub; k++) {
    ex[k] = b_y[k];
  }
  Srows.set_size(ex.size(0), coffset);
  vk = ex.size(0);
  for (loop_ub = 0; loop_ub < coffset; loop_ub++) {
    numelFbDiagElements = loop_ub * vk;
    for (k = 0; k < vk; k++) {
      Srows[numelFbDiagElements + k] = ex[k];
    }
  }
  numelFbDiagElements = allScores.size(0);
  loop_ub = Srows.size(0) * Srows.size(1);
  for (k = 0; k < loop_ub; k++) {
    Srows[k] = static_cast<int>(Srows[k]) +
               numelFbDiagElements * (static_cast<int>(Scols[k]) - 1);
  }
  Sscores.set_size(Srows.size(0), Srows.size(1));
  loop_ub = Srows.size(0) * Srows.size(1);
  for (k = 0; k < loop_ub; k++) {
    Sscores[k] = allScores[static_cast<int>(Srows[k]) - 1];
  }
  // Extract individual pulse scores
  // The max function will just return the first index if all elements are
  // equal. Here we zero out the scores and set the cols to NaN for frequencies
  // were ignored with the frequency blinder matrix.
  vk = Fbdiags.size(0) - 1;
  numelFbDiagElements = 0;
  for (int i{0}; i <= vk; i++) {
    if (!Fbdiags[i]) {
      numelFbDiagElements++;
    }
  }
  r4.set_size(numelFbDiagElements);
  numelFbDiagElements = 0;
  for (int i{0}; i <= vk; i++) {
    if (!Fbdiags[i]) {
      r4[numelFbDiagElements] = i + 1;
      numelFbDiagElements++;
    }
  }
  loop_ub = Srows.size(1);
  for (k = 0; k < loop_ub; k++) {
    vk = r4.size(0);
    for (boffset = 0; boffset < vk; boffset++) {
      Sscores[(r4[boffset] + Sscores.size(0) * k) - 1] = rtNaN;
    }
  }
  vk = Fbdiags.size(0) - 1;
  numelFbDiagElements = 0;
  for (int i{0}; i <= vk; i++) {
    if (!Fbdiags[i]) {
      numelFbDiagElements++;
    }
  }
  r5.set_size(numelFbDiagElements);
  numelFbDiagElements = 0;
  for (int i{0}; i <= vk; i++) {
    if (!Fbdiags[i]) {
      r5[numelFbDiagElements] = i + 1;
      numelFbDiagElements++;
    }
  }
  loop_ub = Scols.size(1);
  for (k = 0; k < loop_ub; k++) {
    vk = r5.size(0);
    for (boffset = 0; boffset < vk; boffset++) {
      Scols[(r5[boffset] + Scols.size(0) * k) - 1] = rtNaN;
    }
  }
}

//
// File trailer for incohsumtoeplitz.cpp
//
// [EOF]
//
