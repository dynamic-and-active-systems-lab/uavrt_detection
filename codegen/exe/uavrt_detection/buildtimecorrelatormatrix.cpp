//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: buildtimecorrelatormatrix.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 20-Oct-2022 20:46:49
//

// Include Files
#include "buildtimecorrelatormatrix.h"
#include "anonymous_function.h"
#include "assembleWq.h"
#include "colon.h"
#include "introsort.h"
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "sparse1.h"
#include "uavrt_detection_internal_types.h"
#include "uavrt_detection_rtwutil.h"
#include "unique.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// UNTITLED Summary of this function goes here
//    Detailed explanation goes here
//
// Arguments    : double pri
//                double priUncert
//                double priJtr
//                double reps
//                coder::sparse *Wq
// Return Type  : void
//
void buildtimecorrelatormatrix(double pri, double priUncert, double priJtr,
                               double reps, coder::sparse *Wq)
{
  coder::anonymous_function b_this;
  coder::array<double, 3U> pulse_position_value;
  coder::array<double, 2U> WqColInds;
  coder::array<double, 2U> WqRowInds;
  coder::array<double, 2U> pattern_matrix;
  coder::array<double, 2U> priMeansList;
  coder::array<double, 2U> pulsePositionMatrix;
  coder::array<double, 2U> shiftermat;
  coder::array<double, 1U> b_WqColInds;
  coder::array<double, 1U> b_priMeansList;
  coder::array<int, 1U> sortedIndices;
  coder::array<int, 1U> t;
  double n_shifts;
  double num_position_patterns;
  double num_rows_C;
  int b_loop_ub;
  int i;
  int i1;
  int i2;
  int iacol;
  int ibcol;
  int ibmat;
  int itilerow;
  int loop_ub;
  int ncols;
  int nrows;
  int num_members_per_set;
  int num_rows_C_tmp;
  int sizes_idx_1;
  signed char input_sizes_idx_1;
  boolean_T empty_non_axis_sizes;
  // First check to make sure all inputs contain the same number of
  // elements
  // Change names to align with other code.
  if (std::isnan(-priUncert) || std::isnan(priUncert)) {
    priMeansList.set_size(1, 1);
    priMeansList[0] = rtNaN;
  } else if (priUncert < -priUncert) {
    priMeansList.set_size(priMeansList.size(0), 0);
  } else if ((std::isinf(-priUncert) || std::isinf(priUncert)) &&
             (-priUncert == priUncert)) {
    priMeansList.set_size(1, 1);
    priMeansList[0] = rtNaN;
  } else if (std::floor(-priUncert) == -priUncert) {
    loop_ub = static_cast<int>(priUncert - (-priUncert));
    priMeansList.set_size(1, loop_ub + 1);
    for (i = 0; i <= loop_ub; i++) {
      priMeansList[i] = -priUncert + static_cast<double>(i);
    }
  } else {
    coder::eml_float_colon(-priUncert, priUncert, priMeansList);
  }
  priMeansList.set_size(1, priMeansList.size(1));
  loop_ub = priMeansList.size(1) - 1;
  for (i = 0; i <= loop_ub; i++) {
    priMeansList[i] = pri + priMeansList[i];
  }
  if (std::isnan(-priJtr) || std::isnan(priJtr)) {
    WqColInds.set_size(1, 1);
    WqColInds[0] = rtNaN;
  } else if (priJtr < -priJtr) {
    WqColInds.set_size(1, 0);
  } else if ((std::isinf(-priJtr) || std::isinf(priJtr)) &&
             (-priJtr == priJtr)) {
    WqColInds.set_size(1, 1);
    WqColInds[0] = rtNaN;
  } else if (std::floor(-priJtr) == -priJtr) {
    loop_ub = static_cast<int>(priJtr - (-priJtr));
    WqColInds.set_size(1, loop_ub + 1);
    for (i = 0; i <= loop_ub; i++) {
      WqColInds[i] = -priJtr + static_cast<double>(i);
    }
  } else {
    coder::eml_float_colon(-priJtr, priJtr, WqColInds);
  }
  // PPM Contains the column positions (time windows) in the S matrix to search
  // for the K pulses assuming the first pulse arrives at window 1.
  //  INPUTS:
  //    PRI_mean_value          row vector of PRI means (scale/index is STFT
  //    step
  //                            size)
  //
  //    PRI_jitter_value        row vector of jitter values (scale/index is STFT
  //    step
  //                            size)
  //
  //    K                       number of pulses forming the pattern
  //
  //  OUTPUTS:
  //    pulse_position_matrix   row is a pattern; each pattern has K pulse
  //                            position values
  //
  //  CALLS:
  //                            cartesion_prod_func()
  //
  //  generate_pulse_positions_func.m
  //  Author: Paul G. Flikkema
  //  Date:   1 Oct 2021
  n_shifts = rt_powd_snf(static_cast<double>(WqColInds.size(1)), reps - 1.0);
  //  place first pulse at pulse position q = 1
  //  based on the model, generate all the pulse position values in a 3D matrix
  //  pulse_position_value(k, i_position, i_mean )
  pulse_position_value.set_size(static_cast<int>(reps), WqColInds.size(1),
                                priMeansList.size(1));
  loop_ub = static_cast<int>(reps) * WqColInds.size(1) * priMeansList.size(1);
  for (i = 0; i < loop_ub; i++) {
    pulse_position_value[i] = 0.0;
  }
  loop_ub = priMeansList.size(1);
  for (i = 0; i < loop_ub; i++) {
    sizes_idx_1 = WqColInds.size(1);
    for (i1 = 0; i1 < sizes_idx_1; i1++) {
      pulse_position_value[pulse_position_value.size(0) * i1 +
                           pulse_position_value.size(0) *
                               pulse_position_value.size(1) * i] = 1.0;
    }
  }
  //  first pulse is always in position 1
  //  loop through the mean PRI values
  i = priMeansList.size(1);
  for (sizes_idx_1 = 0; sizes_idx_1 < i; sizes_idx_1++) {
    i1 = static_cast<int>(reps - 1.0);
    for (loop_ub = 0; loop_ub < i1; loop_ub++) {
      i2 = WqColInds.size(1);
      for (iacol = 0; iacol < i2; iacol++) {
        pulse_position_value[((loop_ub + pulse_position_value.size(0) * iacol) +
                              pulse_position_value.size(0) *
                                  pulse_position_value.size(1) * sizes_idx_1) +
                             1] =
            (((static_cast<double>(loop_ub) + 2.0) - 1.0) *
                 priMeansList[sizes_idx_1] +
             1.0) +
            WqColInds[iacol];
      }
    }
  }
  //  generate the pulse_position_matrix by considering
  //  all possible combinations of the values;
  //  each row is for one pattern, there are K columns;
  //  pulse_position_matrix( i_pattern, k)
  //
  //  The number of columns is the number of possible positions
  //
  //  we generate a num_PRI_jitters^(K-1) x K matrix
  //  using the function cartesian_prod_func
  //
  //  we stack matrices vertically into the pulse_position_matrix
  num_position_patterns =
      static_cast<double>(priMeansList.size(1)) *
      rt_powd_snf(static_cast<double>(WqColInds.size(1)), reps - 1.0);
  pulsePositionMatrix.set_size(static_cast<int>(num_position_patterns),
                               static_cast<int>(reps - 1.0));
  loop_ub =
      static_cast<int>(num_position_patterns) * static_cast<int>(reps - 1.0);
  for (i = 0; i < loop_ub; i++) {
    pulsePositionMatrix[i] = 0.0;
  }
  //  number of rows per PRI mean
  i = priMeansList.size(1);
  if (priMeansList.size(1) - 1 >= 0) {
    if (pulse_position_value.size(0) < 2) {
      nrows = 1;
      ncols = 0;
    } else {
      nrows = 2;
      ncols = pulse_position_value.size(0);
    }
    num_members_per_set = pulse_position_value.size(1);
    num_rows_C_tmp = ncols - nrows;
    num_rows_C = rt_powd_snf(static_cast<double>(pulse_position_value.size(1)),
                             static_cast<double>(num_rows_C_tmp) + 1.0);
    b_loop_ub = static_cast<int>(num_rows_C) * (num_rows_C_tmp + 1);
  }
  for (ibcol = 0; ibcol < i; ibcol++) {
    double d;
    //      % DEBUG
    //      a = [ 1 1 1 ]; b = [ 309 310 311 ]; c = [ 618 619 620 ];
    //      A = [ a; b; c ];
    //  since pattern is "fundamental" pattern starting with a pulse in the
    //  first STFT window, we only need to look at combinations
    //  rows 2:end, and then add the column of ones
    //    returns the Cartesian product C of the (values in the) rows
    //    of the input matrix A.
    //    Each row of A is taken as a set to draw from
    //    Assumes all sets have the same number of members
    i1 = ncols - nrows;
    pattern_matrix.set_size(static_cast<int>(num_rows_C), i1 + 1);
    for (i2 = 0; i2 < b_loop_ub; i2++) {
      pattern_matrix[i2] = 0.0;
    }
    //  loop through columns of C
    for (sizes_idx_1 = 0; sizes_idx_1 <= num_rows_C_tmp; sizes_idx_1++) {
      double stride;
      unsigned int i_col_A;
      //  fill the column (aka fill the elements in the column)
      //  stride is number of elements to repeat in a column
      //  num_strides is number of strides per column
      stride = rt_powd_snf(static_cast<double>(num_members_per_set),
                           static_cast<double>(i1 - sizes_idx_1));
      i_col_A = 0U;
      //  the column in A that we use
      i2 = static_cast<int>(num_rows_C / stride);
      for (iacol = 0; iacol < i2; iacol++) {
        double star;
        i_col_A++;
        if (i_col_A > static_cast<unsigned int>(num_members_per_set)) {
          i_col_A = 1U;
        }
        star = ((static_cast<double>(iacol) + 1.0) - 1.0) * stride + 1.0;
        //  column of C gets elements from row of A
        d = (star + stride) - 1.0;
        if (star > d) {
          itilerow = 0;
          ibmat = 0;
        } else {
          itilerow = static_cast<int>(star) - 1;
          ibmat = static_cast<int>(d);
        }
        loop_ub = ibmat - itilerow;
        for (ibmat = 0; ibmat < loop_ub; ibmat++) {
          pattern_matrix[(itilerow + ibmat) +
                         pattern_matrix.size(0) * sizes_idx_1] =
              pulse_position_value[(((nrows + sizes_idx_1) +
                                     pulse_position_value.size(0) *
                                         (static_cast<int>(i_col_A) - 1)) +
                                    pulse_position_value.size(0) *
                                        pulse_position_value.size(1) * ibcol) -
                                   1];
        }
      }
    }
    d = ((static_cast<double>(ibcol) + 1.0) - 1.0) * n_shifts + 1.0;
    if (d > (static_cast<double>(ibcol) + 1.0) * n_shifts) {
      i1 = 1;
    } else {
      i1 = static_cast<int>(d);
    }
    loop_ub = pattern_matrix.size(1);
    for (i2 = 0; i2 < loop_ub; i2++) {
      sizes_idx_1 = pattern_matrix.size(0);
      for (itilerow = 0; itilerow < sizes_idx_1; itilerow++) {
        pulsePositionMatrix[((i1 + itilerow) +
                             pulsePositionMatrix.size(0) * i2) -
                            1] =
            pattern_matrix[itilerow + pattern_matrix.size(0) * i2];
      }
    }
  }
  if (static_cast<int>(num_position_patterns) != 0) {
    iacol = static_cast<int>(num_position_patterns);
  } else if ((pulsePositionMatrix.size(0) != 0) &&
             (pulsePositionMatrix.size(1) != 0)) {
    iacol = pulsePositionMatrix.size(0);
  } else {
    iacol = static_cast<int>(num_position_patterns);
    if (iacol < 0) {
      iacol = 0;
    }
    if (pulsePositionMatrix.size(0) > iacol) {
      iacol = pulsePositionMatrix.size(0);
    }
  }
  empty_non_axis_sizes = (iacol == 0);
  if (empty_non_axis_sizes || (static_cast<int>(num_position_patterns) != 0)) {
    input_sizes_idx_1 = 1;
  } else {
    input_sizes_idx_1 = 0;
  }
  if (empty_non_axis_sizes || ((pulsePositionMatrix.size(0) != 0) &&
                               (pulsePositionMatrix.size(1) != 0))) {
    sizes_idx_1 = pulsePositionMatrix.size(1);
  } else {
    sizes_idx_1 = 0;
  }
  //  remove duplicate patterns
  pattern_matrix.set_size(iacol, input_sizes_idx_1 + sizes_idx_1);
  loop_ub = input_sizes_idx_1;
  for (i = 0; i < loop_ub; i++) {
    for (i1 = 0; i1 < iacol; i1++) {
      pattern_matrix[i1] = 1.0;
    }
  }
  for (i = 0; i < sizes_idx_1; i++) {
    for (i1 = 0; i1 < iacol; i1++) {
      pattern_matrix[i1 + pattern_matrix.size(0) * (i + input_sizes_idx_1)] =
          pulsePositionMatrix[i1 + iacol * i];
    }
  }
  coder::unique_rows(pattern_matrix, pulsePositionMatrix);
  //  if K>1
  //      %n_shifts = min(pulsePositionMatrix(:,2))-1;   %The number of shifts
  //      necessary.
  //
  //  else
  //      n_shifts = max(PRI_means_q)+max(PRI_jitters_q);
  //  end
  // The max element of the ppm for K>1 is (K-1)*(N+M)+J+1 which is the latest
  // possible index of the Kth pulse if the first arrived at n = 1.
  //
  // The max element of the ppm for K=1 is 1 which is the first possible index
  // of the 1st pulse.
  //
  // The size of the STFT matrix is the latest possible location of the Kth
  // pulse which is equal to K*(N+M)+J+1
  //
  // We want to take the PPM matrix that contains the the time locations for
  // the search if the first pulse is at n=1 and shift them to do the search if
  // the first pulse arrives and n = 2,..., N+M+J+1 which is the latest
  // possible location of the pulse pulse. The difference is N+M+J+1-1 = N+M+J
  // This is the max number we need to add the the PPM matrix.
  //
  // For the K = 1 case, the PPM is simply 1 and we add N+M+J which generates a
  // Wq matrix with a dimension of 1+N+M+J. This is equivalent to the STFT
  // size definition for K = 1, which is K(N+M)+J+1 = N+M+J+1, so the sizes
  // will be compatible.
  //
  // For the K > 1 case however the maximum element of the PPM is
  // (K-1)(N+M)+J+1. Adding N+M+J to this will result in a Wq with a dimension
  // of (K-1)(N+M)+J+1+N+M+J = K(N+M)+2J+1. This will be J elements larger than
  // the STFT definitions of K(N+M)+J+1. This extra J comes from the fact that
  // the max element of the PPM include the jitter of the final pulse and we
  // also include the jitter in the shifting. Because jitter is stochastic and
  // zero mean, we don't sum jitter over multiple pulses. We need to remove the
  // extra jitter when shifting for K>1.
  //
  if (reps > 1.0) {
    iacol = priMeansList.size(1);
    b_priMeansList = priMeansList.reshape(iacol);
    n_shifts = coder::internal::maximum(b_priMeansList);
    // Equivalent to N+M+J-J
  } else {
    iacol = priMeansList.size(1);
    sizes_idx_1 = WqColInds.size(1);
    b_priMeansList = priMeansList.reshape(iacol);
    b_WqColInds = WqColInds.reshape(sizes_idx_1);
    n_shifts = coder::internal::maximum(b_priMeansList) +
               coder::internal::maximum(b_WqColInds);
    // Equivalent to N+M+J
  }
  // Number of rows in pulse_position_matrix
  // Number of cols in pulse_position_matrix --- should always be K
  pattern_matrix.set_size(pulsePositionMatrix.size(0) *
                              static_cast<int>(n_shifts + 1.0),
                          pulsePositionMatrix.size(1));
  nrows = pulsePositionMatrix.size(0);
  ncols = pulsePositionMatrix.size(1);
  sizes_idx_1 = static_cast<int>(n_shifts + 1.0);
  for (num_members_per_set = 0; num_members_per_set < ncols;
       num_members_per_set++) {
    iacol = num_members_per_set * nrows;
    ibmat =
        num_members_per_set * (nrows * static_cast<int>(n_shifts + 1.0)) - 1;
    for (itilerow = 0; itilerow < sizes_idx_1; itilerow++) {
      ibcol = ibmat + itilerow * nrows;
      for (loop_ub = 0; loop_ub < nrows; loop_ub++) {
        pattern_matrix[(ibcol + loop_ub) + 1] =
            pulsePositionMatrix[iacol + loop_ub];
      }
    }
  }
  // Create multiple copies of the PPM matrix. Each copy will eventually be
  // shifted. The second copy will get a 1 added to it, the third a 2 added, and
  // so on up to n_shifts. Use n_shifts+1 to account for the first one that
  // receives no shifting. Get the number of rows in the big PPM matrix
  if (std::isnan(n_shifts)) {
    priMeansList.set_size(1, 1);
    priMeansList[0] = rtNaN;
  } else if (n_shifts < 0.0) {
    priMeansList.set_size(1, 0);
  } else {
    priMeansList.set_size(1, static_cast<int>(n_shifts) + 1);
    loop_ub = static_cast<int>(n_shifts);
    for (i = 0; i <= loop_ub; i++) {
      priMeansList[i] = i;
    }
  }
  shiftermat.set_size(pulsePositionMatrix.size(0), priMeansList.size(1));
  ncols = priMeansList.size(1);
  sizes_idx_1 = pulsePositionMatrix.size(0);
  for (num_members_per_set = 0; num_members_per_set < ncols;
       num_members_per_set++) {
    ibmat = num_members_per_set * sizes_idx_1;
    for (itilerow = 0; itilerow < sizes_idx_1; itilerow++) {
      shiftermat[ibmat + itilerow] = priMeansList[num_members_per_set];
    }
  }
  // Create a matrix of the shifts needed for each copy of the PPM matrix
  WqRowInds.set_size(shiftermat.size(0) * shiftermat.size(1),
                     pulsePositionMatrix.size(1));
  nrows = shiftermat.size(0) * shiftermat.size(1);
  iacol = pulsePositionMatrix.size(1);
  for (ibmat = 0; ibmat < iacol; ibmat++) {
    sizes_idx_1 = ibmat * nrows;
    for (loop_ub = 0; loop_ub < nrows; loop_ub++) {
      WqRowInds[sizes_idx_1 + loop_ub] = shiftermat[loop_ub];
    }
  }
  if ((WqRowInds.size(0) == pattern_matrix.size(0)) &&
      (WqRowInds.size(1) == pattern_matrix.size(1))) {
    loop_ub = WqRowInds.size(0) * WqRowInds.size(1);
    for (i = 0; i < loop_ub; i++) {
      WqRowInds[i] = WqRowInds[i] + pattern_matrix[i];
    }
  } else {
    plus(WqRowInds, pattern_matrix);
  }
  if (pattern_matrix.size(0) < 1) {
    priMeansList.set_size(1, 0);
  } else {
    priMeansList.set_size(1, pattern_matrix.size(0));
    loop_ub = pattern_matrix.size(0) - 1;
    for (i = 0; i <= loop_ub; i++) {
      priMeansList[i] = static_cast<double>(i) + 1.0;
    }
  }
  WqColInds.set_size(1, priMeansList.size(1) * pulsePositionMatrix.size(1));
  ncols = priMeansList.size(1);
  iacol = pulsePositionMatrix.size(1);
  for (ibmat = 0; ibmat < iacol; ibmat++) {
    sizes_idx_1 = ibmat * ncols;
    for (num_members_per_set = 0; num_members_per_set < ncols;
         num_members_per_set++) {
      WqColInds[sizes_idx_1 + num_members_per_set] =
          priMeansList[num_members_per_set];
    }
  }
  ibmat = WqColInds.size(1);
  iacol = WqRowInds.size(0) * WqRowInds.size(1);
  b_this.workspace.b.set_size(WqRowInds.size(0) * WqRowInds.size(1));
  for (loop_ub = 0; loop_ub < iacol; loop_ub++) {
    b_this.workspace.b[loop_ub] = static_cast<int>(WqRowInds[loop_ub]);
  }
  iacol = WqColInds.size(1);
  b_this.workspace.a.set_size(WqColInds.size(1));
  for (loop_ub = 0; loop_ub < iacol; loop_ub++) {
    b_this.workspace.a[loop_ub] = static_cast<int>(WqColInds[loop_ub]);
  }
  sortedIndices.set_size(WqColInds.size(1));
  for (loop_ub = 0; loop_ub < ibmat; loop_ub++) {
    sortedIndices[loop_ub] = loop_ub + 1;
  }
  coder::internal::introsort(sortedIndices, b_this.workspace.a.size(0),
                             &b_this);
  iacol = b_this.workspace.a.size(0);
  t.set_size(b_this.workspace.a.size(0));
  loop_ub = b_this.workspace.a.size(0);
  for (i = 0; i < loop_ub; i++) {
    t[i] = b_this.workspace.a[i];
  }
  for (loop_ub = 0; loop_ub < iacol; loop_ub++) {
    b_this.workspace.a[loop_ub] = t[sortedIndices[loop_ub] - 1];
  }
  iacol = b_this.workspace.b.size(0);
  t.set_size(b_this.workspace.b.size(0));
  loop_ub = b_this.workspace.b.size(0);
  for (i = 0; i < loop_ub; i++) {
    t[i] = b_this.workspace.b[i];
  }
  for (loop_ub = 0; loop_ub < iacol; loop_ub++) {
    b_this.workspace.b[loop_ub] = t[sortedIndices[loop_ub] - 1];
  }
  if ((b_this.workspace.b.size(0) == 0) || (b_this.workspace.a.size(0) == 0)) {
    sizes_idx_1 = 0;
    Wq->n = 0;
  } else {
    iacol = b_this.workspace.b.size(0);
    sizes_idx_1 = b_this.workspace.b[0];
    for (loop_ub = 2; loop_ub <= iacol; loop_ub++) {
      i = b_this.workspace.b[loop_ub - 1];
      if (sizes_idx_1 < i) {
        sizes_idx_1 = i;
      }
    }
    Wq->n = b_this.workspace.a[b_this.workspace.a.size(0) - 1];
  }
  Wq->m = sizes_idx_1;
  sizes_idx_1 = WqColInds.size(1);
  if (sizes_idx_1 < 1) {
    sizes_idx_1 = 1;
  }
  Wq->d.set_size(sizes_idx_1);
  Wq->maxnz = sizes_idx_1;
  Wq->colidx.set_size(Wq->n + 1);
  Wq->colidx[0] = 1;
  Wq->rowidx.set_size(sizes_idx_1);
  for (i = 0; i < sizes_idx_1; i++) {
    Wq->d[i] = 0.0;
    Wq->rowidx[i] = 0;
  }
  iacol = 0;
  i = Wq->n;
  for (sizes_idx_1 = 0; sizes_idx_1 < i; sizes_idx_1++) {
    while ((iacol + 1 <= ibmat) &&
           (b_this.workspace.a[iacol] == sizes_idx_1 + 1)) {
      Wq->rowidx[iacol] = b_this.workspace.b[iacol];
      iacol++;
    }
    Wq->colidx[sizes_idx_1 + 1] = iacol + 1;
  }
  for (loop_ub = 0; loop_ub < ibmat; loop_ub++) {
    Wq->d[loop_ub] = 1.0;
  }
  Wq->fillIn();
  // , obj.reps(i));
}

//
// File trailer for buildtimecorrelatormatrix.cpp
//
// [EOF]
//
