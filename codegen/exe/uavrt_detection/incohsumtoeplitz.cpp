//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: incohsumtoeplitz.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "incohsumtoeplitz.h"
#include "abs.h"
#include "any1.h"
#include "assertValidSizeArg.h"
#include "eml_mtimes_helper.h"
#include "find.h"
#include "indexShapeCheck.h"
#include "minOrMax.h"
#include "mtimes.h"
#include "repmat.h"
#include "rt_nonfinite.h"
#include "sparse.h"
#include "sparse1.h"
#include "speye.h"
#include "sub2ind.h"
#include "sum.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
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
//    IR      Repetition rejection comb filter matrix. Set to the identity to
//            if no comb filtering is needed.
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
// --------------------------------------------------------------------------
//
// Arguments    : const coder::array<boolean_T, 1U> &Fb
//                const coder::array<creal_T, 2U> &Wfherm
//                const coder::array<creal_T, 2U> &S
//                const coder::sparse &IR
//                const coder::array<double, 1U> &Tb
//                const coder::sparse &Wq
//                coder::array<double, 2U> &Sscores
//                coder::array<double, 2U> &Scols
// Return Type  : void
//
void incohsumtoeplitz(const coder::array<boolean_T, 1U> &Fb,
                      const coder::array<creal_T, 2U> &Wfherm,
                      const coder::array<creal_T, 2U> &S,
                      const coder::sparse &IR,
                      const coder::array<double, 1U> &Tb,
                      const coder::sparse &Wq,
                      coder::array<double, 2U> &Sscores,
                      coder::array<double, 2U> &Scols)
{
  static rtBoundsCheckInfo ab_emlrtBCI{
      193,               // lineNo
      "allScores",       // aName
      "incohsumtoeplitz" // fName
  };
  static rtBoundsCheckInfo bb_emlrtBCI{
      165,               // lineNo
      "Fb",              // aName
      "incohsumtoeplitz" // fName
  };
  static rtBoundsCheckInfo cb_emlrtBCI{
      178,               // lineNo
      "Tb",              // aName
      "incohsumtoeplitz" // fName
  };
  static rtBoundsCheckInfo db_emlrtBCI{
      199,               // lineNo
      "Scols",           // aName
      "incohsumtoeplitz" // fName
  };
  static rtBoundsCheckInfo eb_emlrtBCI{
      198,               // lineNo
      "Sscores",         // aName
      "incohsumtoeplitz" // fName
  };
  coder::b_sparse pulsesInEachColumn;
  coder::c_sparse firstPulseNum;
  coder::d_sparse r;
  coder::d_sparse sameAsFirst;
  coder::e_sparse r1;
  coder::f_sparse FbSparseMat;
  coder::f_sparse TbSparseMat;
  coder::g_sparse r3;
  coder::h_sparse Tbdiags;
  coder::sparse y;
  coder::array<creal_T, 2U> c_y;
  coder::array<double, 2U> FbmatDiagInds;
  coder::array<double, 2U> Sinds;
  coder::array<double, 2U> Srows;
  coder::array<double, 2U> allScores;
  coder::array<double, 2U> b_y;
  coder::array<double, 2U> selectedCombinedScores;
  coder::array<double, 1U> ex;
  coder::array<int, 2U> r2;
  coder::array<int, 2U> r4;
  coder::array<int, 1U> idx;
  coder::array<int, 1U> jj;
  coder::array<int, 1U> r5;
  coder::array<boolean_T, 2U> b_Fb;
  coder::array<boolean_T, 1U> Fbdiags;
  double Fbsz[2];
  double Ssz[2];
  double Fbnumrows_tmp;
  double K;
  double Tbnumrows_tmp;
  double minval_tmp;
  int iv[2];
  int K_tmp;
  int b_i;
  int i;
  int loop_ub;
  int n;
  int u0;
  Ssz[0] = Tb.size(0);
  Ssz[1] = 1.0;
  Fbsz[0] = Fb.size(0);
  Fbsz[1] = 1.0;
  minval_tmp = coder::internal::minimum(Ssz);
  K = coder::internal::minimum(Fbsz);
  if ((minval_tmp != 1.0) && (Tb.size(0) != 1)) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  if ((K != 1.0) && (Fb.size(0) != 1)) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  Tbnumrows_tmp = coder::internal::maximum(Ssz);
  Fbnumrows_tmp = coder::internal::maximum(Fbsz);
  if (Fbnumrows_tmp != Wfherm.size(0)) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  if (S.size(0) != Wfherm.size(1)) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  if (S.size(1) != Tbnumrows_tmp) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  i = static_cast<int>(Tbnumrows_tmp);
  if (i != Wq.m) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  // Make sure the number of pulses considered for all Wq columns is the same
  coder::sum(Wq, pulsesInEachColumn);
  pulsesInEachColumn.parenReference(firstPulseNum);
  pulsesInEachColumn.c_le(r);
  coder::any(r, r1);
  if (r1.full()) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  pulsesInEachColumn.eq(firstPulseNum, sameAsFirst);
  sameAsFirst.b_not(r);
  coder::any(r, r1);
  if (r1.full()) {
    // numel(unique(full(pulsesInEachColumn)))~=1 %Unique doesn't support sparse
    // for code-generation. %numel(unique(sum(Wq,1)))~=1
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  //  Generate Tb and Fb sparse matrices if entered as vectors
  // Frequency Blinder (Fb) matrix definitions:
  Ssz[0] = Fbnumrows_tmp;
  Ssz[1] = Fbnumrows_tmp;
  coder::speye(Ssz, y);
  y.logical(FbSparseMat);
  // Prototype Fb matrix with identity logical matrix
  if (Fbnumrows_tmp < 1.0) {
    FbmatDiagInds.set_size(1, 0);
    b_y.set_size(1, 0);
  } else {
    n = static_cast<int>(Fbnumrows_tmp - 1.0);
    b_i = n + 1;
    FbmatDiagInds.set_size(1, b_i);
    b_y.set_size(1, b_i);
    for (b_i = 0; b_i <= n; b_i++) {
      FbmatDiagInds[b_i] = static_cast<double>(b_i) + 1.0;
      b_y[b_i] = static_cast<double>(b_i) + 1.0;
    }
  }
  n = static_cast<int>(Fbnumrows_tmp);
  iv[0] = n;
  iv[1] = n;
  coder::internal::sub2ind(iv, FbmatDiagInds, b_y, r2);
  loop_ub = r2.size(1);
  FbmatDiagInds.set_size(1, r2.size(1));
  for (b_i = 0; b_i < loop_ub; b_i++) {
    FbmatDiagInds[b_i] = r2[b_i];
  }
  if (K == 1.0) {
    // Passed a vector, so make the matrix
    loop_ub = Fb.size(0);
    Fbdiags.set_size(Fb.size(0));
    for (b_i = 0; b_i < loop_ub; b_i++) {
      Fbdiags[b_i] = Fb[b_i];
    }
    // FbSparseMat = logical(speye(max(Fbsz)));
    FbSparseMat.parenAssign(Fb, FbmatDiagInds);
  } else {
    // Passed a matrix, so make sparse.
    // FbSparseMat = logical(sparse(Fb));
    b_Fb.set_size(1, r2.size(1));
    for (b_i = 0; b_i < loop_ub; b_i++) {
      n = static_cast<int>(FbmatDiagInds[b_i]);
      if ((n < 1) || (n > Fb.size(0))) {
        rtDynamicBoundsError(n, 1, Fb.size(0), bb_emlrtBCI);
      }
      b_Fb[b_i] = Fb[n - 1];
    }
    FbSparseMat.b_parenAssign(b_Fb, FbmatDiagInds);
    // Had do do it this way rather than with logical(sparse(Fb)) to get code to
    // work with Fb being either a vector or matrix.
    FbSparseMat.parenReference(FbmatDiagInds, r);
    r.full(b_Fb);
    loop_ub = b_Fb.size(1);
    Fbdiags.set_size(b_Fb.size(1));
    for (b_i = 0; b_i < loop_ub; b_i++) {
      Fbdiags[b_i] = b_Fb[b_i];
    }
    // Get the diag elements. Transpose needed for size considerations for code
    // generation.
  }
  // Time Blinder (Tb) matrix definitions:
  Ssz[0] = Tbnumrows_tmp;
  Ssz[1] = Tbnumrows_tmp;
  coder::speye(Ssz, y);
  y.logical(TbSparseMat);
  // Prototype Fb matrix with identity logical matrix
  if (Tbnumrows_tmp < 1.0) {
    FbmatDiagInds.set_size(1, 0);
    b_y.set_size(1, 0);
  } else {
    n = static_cast<int>(Tbnumrows_tmp - 1.0);
    b_i = n + 1;
    FbmatDiagInds.set_size(1, b_i);
    b_y.set_size(1, b_i);
    for (b_i = 0; b_i <= n; b_i++) {
      FbmatDiagInds[b_i] = static_cast<double>(b_i) + 1.0;
      b_y[b_i] = static_cast<double>(b_i) + 1.0;
    }
  }
  iv[0] = i;
  iv[1] = i;
  coder::internal::sub2ind(iv, FbmatDiagInds, b_y, r2);
  loop_ub = r2.size(1);
  FbmatDiagInds.set_size(1, r2.size(1));
  for (i = 0; i < loop_ub; i++) {
    FbmatDiagInds[i] = r2[i];
  }
  if (minval_tmp == 1.0) {
    coder::i_sparse(Tb, r3);
    r3.logical(Tbdiags);
    coder::internal::assertValidSizeArg(Tbnumrows_tmp);
    coder::sparse::eyeLike(static_cast<int>(Tbnumrows_tmp),
                           static_cast<int>(Tbnumrows_tmp),
                           static_cast<int>(Tbnumrows_tmp), y);
    y.logical(TbSparseMat);
    TbSparseMat.c_parenAssign(Tbdiags, FbmatDiagInds);
  } else {
    b_y.set_size(1, r2.size(1));
    for (i = 0; i < loop_ub; i++) {
      b_i = static_cast<int>(FbmatDiagInds[i]);
      if ((b_i < 1) || (b_i > Tb.size(0))) {
        rtDynamicBoundsError(b_i, 1, Tb.size(0), cb_emlrtBCI);
      }
      b_y[i] = Tb[b_i - 1];
    }
    TbSparseMat.c_parenAssign(b_y, FbmatDiagInds);
    // Had do do it this way rather than with logical(sparse(Tb)) to get code to
    // work with Tb being either a vector or matrix.
  }
  //  Perform the incoherent summation
  Wq.parenReference(r3);
  coder::sum(r3, firstPulseNum);
  K = firstPulseNum.full();
  coder::dynamic_size_checks(Wfherm, S, Wfherm.size(1), S.size(0));
  coder::internal::blas::b_mtimes(Wfherm, S, c_y);
  coder::b_abs(c_y, Srows);
  Sinds.set_size(Srows.size(0), Srows.size(1));
  n = Srows.size(0) * Srows.size(1);
  for (i = 0; i < n; i++) {
    minval_tmp = Srows[i];
    Sinds[i] = minval_tmp * minval_tmp;
  }
  IR.mtimes(Sinds, allScores);
  FbSparseMat.mtimes(allScores, Srows);
  TbSparseMat.b_mtimes(Srows, Sinds);
  Wq.b_mtimes(Sinds, selectedCombinedScores);
  coder::internal::maximum(selectedCombinedScores, ex, idx);
  // Check max on each row (frequency). This gives the columns of the resulting
  // matrix output with the max for each frequency bin This and the next line
  // gets the column numbers (time windows) of the S matrix where the highest
  // K-summed entries exist for each row (frequency bin)
  loop_ub = idx.size(0);
  ex.set_size(idx.size(0));
  for (i = 0; i < loop_ub; i++) {
    ex[i] = idx[i];
  }
  Wq.parenReference(ex, y);
  coder::e_eml_find(y, idx, jj);
  loop_ub = idx.size(0);
  ex.set_size(idx.size(0));
  for (i = 0; i < loop_ub; i++) {
    ex[i] = idx[i];
  }
  // Get the rows that had 1s in them that corresponded to the winning columns
  minval_tmp = static_cast<double>(ex.size(0)) / K;
  coder::internal::assertValidSizeArg(K);
  coder::internal::assertValidSizeArg(minval_tmp);
  n = idx.size(0);
  if (ex.size(0) < 1) {
    n = 1;
  }
  u0 = ex.size(0);
  if (u0 >= n) {
    n = u0;
  }
  if (static_cast<int>(K) > n) {
    k_rtErrorWithMessageID(k_emlrtRTEI.fName, k_emlrtRTEI.lineNo);
  }
  if (static_cast<int>(minval_tmp) > n) {
    k_rtErrorWithMessageID(k_emlrtRTEI.fName, k_emlrtRTEI.lineNo);
  }
  if (static_cast<int>(minval_tmp) < 0) {
    ib_rtErrorWithMessageID(tb_emlrtRTEI.fName, tb_emlrtRTEI.lineNo);
  }
  if (static_cast<int>(K) * static_cast<int>(minval_tmp) != ex.size(0)) {
    l_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
  }
  K_tmp = static_cast<int>(K);
  n = static_cast<int>(minval_tmp);
  Scols.set_size(static_cast<int>(minval_tmp), static_cast<int>(K));
  for (i = 0; i < K_tmp; i++) {
    for (b_i = 0; b_i < n; b_i++) {
      Scols[b_i + Scols.size(0) * i] = ex[i + static_cast<int>(K) * b_i];
    }
  }
  if (Wfherm.size(0) < 1) {
    FbmatDiagInds.set_size(1, 0);
  } else {
    FbmatDiagInds.set_size(1, Wfherm.size(0));
    loop_ub = Wfherm.size(0) - 1;
    for (i = 0; i <= loop_ub; i++) {
      FbmatDiagInds[i] = static_cast<double>(i) + 1.0;
    }
  }
  loop_ub = FbmatDiagInds.size(1);
  ex.set_size(FbmatDiagInds.size(1));
  for (i = 0; i < loop_ub; i++) {
    ex[i] = FbmatDiagInds[i];
  }
  coder::repmat(ex, K, Srows);
  iv[0] = (*(int(*)[2])allScores.size())[0];
  iv[1] = (*(int(*)[2])allScores.size())[1];
  coder::internal::b_sub2ind(iv, Srows, Scols, r4);
  loop_ub = r4.size(1);
  Sinds.set_size(r4.size(0), r4.size(1));
  n = r4.size(0) * r4.size(1);
  for (i = 0; i < n; i++) {
    Sinds[i] = r4[i];
  }
  int iv1[2];
  iv[0] = (*(int(*)[2])allScores.size())[0];
  iv[1] = (*(int(*)[2])allScores.size())[1];
  iv1[0] = (*(int(*)[2])Sinds.size())[0];
  iv1[1] = (*(int(*)[2])Sinds.size())[1];
  coder::internal::indexShapeCheck(iv, iv1);
  Sscores.set_size(r4.size(0), r4.size(1));
  u0 = allScores.size(0) * allScores.size(1);
  for (i = 0; i < n; i++) {
    b_i = static_cast<int>(Sinds[i]);
    if ((b_i < 1) || (b_i > u0)) {
      rtDynamicBoundsError(b_i, 1, u0, ab_emlrtBCI);
    }
    Sscores[i] = allScores[b_i - 1];
  }
  // Extract individual pulse scores
  // The max function will just return the first index if all elements are
  // equal. Here we zero out the scores and set the cols to NaN for frequencies
  // were ignored with the frequency blinder matrix.
  u0 = Fbdiags.size(0);
  n = 0;
  for (b_i = 0; b_i < u0; b_i++) {
    if (!Fbdiags[b_i]) {
      n++;
    }
  }
  r5.set_size(n);
  n = 0;
  for (b_i = 0; b_i < u0; b_i++) {
    if (!Fbdiags[b_i]) {
      r5[n] = b_i;
      n++;
    }
  }
  for (i = 0; i < loop_ub; i++) {
    n = r5.size(0);
    for (b_i = 0; b_i < n; b_i++) {
      if (r5[b_i] > Sinds.size(0) - 1) {
        rtDynamicBoundsError(r5[b_i], 0, Sinds.size(0) - 1, eb_emlrtBCI);
      }
      Sscores[r5[b_i] + Sscores.size(0) * i] = rtNaN;
    }
  }
  for (i = 0; i < K_tmp; i++) {
    loop_ub = r5.size(0);
    for (b_i = 0; b_i < loop_ub; b_i++) {
      if (r5[b_i] > Scols.size(0) - 1) {
        rtDynamicBoundsError(r5[b_i], 0, Scols.size(0) - 1, db_emlrtBCI);
      }
      Scols[r5[b_i] + Scols.size(0) * i] = rtNaN;
    }
  }
}

//
// File trailer for incohsumtoeplitz.cpp
//
// [EOF]
//
