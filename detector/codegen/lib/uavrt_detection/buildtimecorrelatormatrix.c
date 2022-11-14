/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: buildtimecorrelatormatrix.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "buildtimecorrelatormatrix.h"
#include "assembleWq.h"
#include "colon.h"
#include "fillIn.h"
#include "introsort.h"
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "unique.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
/*
 * UNTITLED Summary of this function goes here
 *    Detailed explanation goes here
 *
 * Arguments    : double pri
 *                double priUncert
 *                double priJtr
 *                double reps
 *                d_sparse *Wq
 * Return Type  : void
 */
void buildtimecorrelatormatrix(double pri, double priUncert, double priJtr,
                               double reps, d_sparse *Wq)
{
  emxArray_int32_T *cidxInt;
  emxArray_int32_T *ridxInt;
  emxArray_int32_T *sortedIndices;
  emxArray_int32_T *t;
  emxArray_real_T b_WqColInds;
  emxArray_real_T b_priMeansList;
  emxArray_real_T *WqColInds;
  emxArray_real_T *WqRowInds;
  emxArray_real_T *pattern_matrix;
  emxArray_real_T *priMeansList;
  emxArray_real_T *pulsePositionMatrix;
  emxArray_real_T *pulse_position_value;
  emxArray_real_T *shiftermat;
  double n_shifts;
  double num_position_patterns;
  double num_rows_C;
  double *WqColInds_data;
  double *pattern_matrix_data;
  double *priMeansList_data;
  double *pulse_position_value_data;
  int c_WqColInds;
  int c_priMeansList;
  int d_priMeansList;
  int i;
  int i1;
  int i2;
  int i3;
  int i_set;
  int i_stride;
  int iacol;
  int ibmat;
  int k;
  int loop_ub;
  int ncols;
  int nrows;
  int num_members_per_set;
  int sizes_idx_1;
  int *cidxInt_data;
  int *ridxInt_data;
  int *sortedIndices_data;
  int *t_data;
  signed char input_sizes_idx_1;
  bool empty_non_axis_sizes;
  /* First check to make sure all inputs contain the same number of */
  /* elements */
  /* Change names to align with other code. */
  emxInit_real_T(&priMeansList, 2);
  if (rtIsNaN(-priUncert) || rtIsNaN(priUncert)) {
    i = priMeansList->size[0] * priMeansList->size[1];
    priMeansList->size[0] = 1;
    priMeansList->size[1] = 1;
    emxEnsureCapacity_real_T(priMeansList, i);
    priMeansList_data = priMeansList->data;
    priMeansList_data[0] = rtNaN;
  } else if (priUncert < -priUncert) {
    priMeansList->size[1] = 0;
  } else if ((rtIsInf(-priUncert) || rtIsInf(priUncert)) &&
             (-priUncert == priUncert)) {
    i = priMeansList->size[0] * priMeansList->size[1];
    priMeansList->size[0] = 1;
    priMeansList->size[1] = 1;
    emxEnsureCapacity_real_T(priMeansList, i);
    priMeansList_data = priMeansList->data;
    priMeansList_data[0] = rtNaN;
  } else if (floor(-priUncert) == -priUncert) {
    i = priMeansList->size[0] * priMeansList->size[1];
    priMeansList->size[0] = 1;
    loop_ub = (int)(priUncert - (-priUncert));
    priMeansList->size[1] = loop_ub + 1;
    emxEnsureCapacity_real_T(priMeansList, i);
    priMeansList_data = priMeansList->data;
    for (i = 0; i <= loop_ub; i++) {
      priMeansList_data[i] = -priUncert + (double)i;
    }
  } else {
    eml_float_colon(-priUncert, priUncert, priMeansList);
  }
  i = priMeansList->size[0] * priMeansList->size[1];
  priMeansList->size[0] = 1;
  emxEnsureCapacity_real_T(priMeansList, i);
  priMeansList_data = priMeansList->data;
  loop_ub = priMeansList->size[1] - 1;
  for (i = 0; i <= loop_ub; i++) {
    priMeansList_data[i] += pri;
  }
  emxInit_real_T(&WqColInds, 2);
  WqColInds_data = WqColInds->data;
  if (rtIsNaN(-priJtr) || rtIsNaN(priJtr)) {
    i = WqColInds->size[0] * WqColInds->size[1];
    WqColInds->size[0] = 1;
    WqColInds->size[1] = 1;
    emxEnsureCapacity_real_T(WqColInds, i);
    WqColInds_data = WqColInds->data;
    WqColInds_data[0] = rtNaN;
  } else if (priJtr < -priJtr) {
    WqColInds->size[0] = 1;
    WqColInds->size[1] = 0;
  } else if ((rtIsInf(-priJtr) || rtIsInf(priJtr)) && (-priJtr == priJtr)) {
    i = WqColInds->size[0] * WqColInds->size[1];
    WqColInds->size[0] = 1;
    WqColInds->size[1] = 1;
    emxEnsureCapacity_real_T(WqColInds, i);
    WqColInds_data = WqColInds->data;
    WqColInds_data[0] = rtNaN;
  } else if (floor(-priJtr) == -priJtr) {
    i = WqColInds->size[0] * WqColInds->size[1];
    WqColInds->size[0] = 1;
    loop_ub = (int)(priJtr - (-priJtr));
    WqColInds->size[1] = loop_ub + 1;
    emxEnsureCapacity_real_T(WqColInds, i);
    WqColInds_data = WqColInds->data;
    for (i = 0; i <= loop_ub; i++) {
      WqColInds_data[i] = -priJtr + (double)i;
    }
  } else {
    eml_float_colon(-priJtr, priJtr, WqColInds);
    WqColInds_data = WqColInds->data;
  }
  /* PPM Contains the column positions (time windows) in the S matrix to search
   */
  /* for the K pulses assuming the first pulse arrives at window 1.  */
  /*  INPUTS: */
  /*    PRI_mean_value          row vector of PRI means (scale/index is STFT
   * step */
  /*                            size) */
  /*  */
  /*    PRI_jitter_value        row vector of jitter values (scale/index is STFT
   * step */
  /*                            size) */
  /*  */
  /*    K                       number of pulses forming the pattern */
  /*  */
  /*  OUTPUTS: */
  /*    pulse_position_matrix   row is a pattern; each pattern has K pulse */
  /*                            position values */
  /*  */
  /*  CALLS:  */
  /*                            cartesion_prod_func() */
  /*  */
  /*  generate_pulse_positions_func.m */
  /*  Author: Paul G. Flikkema */
  /*  Date:   1 Oct 2021 */
  n_shifts = rt_powd_snf(WqColInds->size[1], reps - 1.0);
  /*  place first pulse at pulse position q = 1 */
  /*  based on the model, generate all the pulse position values in a 3D matrix
   */
  /*  pulse_position_value(k, i_position, i_mean ) */
  emxInit_real_T(&pulse_position_value, 3);
  i = pulse_position_value->size[0] * pulse_position_value->size[1] *
      pulse_position_value->size[2];
  pulse_position_value->size[0] = (int)reps;
  pulse_position_value->size[1] = WqColInds->size[1];
  pulse_position_value->size[2] = priMeansList->size[1];
  emxEnsureCapacity_real_T(pulse_position_value, i);
  pulse_position_value_data = pulse_position_value->data;
  loop_ub = (int)reps * WqColInds->size[1] * priMeansList->size[1];
  for (i = 0; i < loop_ub; i++) {
    pulse_position_value_data[i] = 0.0;
  }
  loop_ub = priMeansList->size[1];
  for (i = 0; i < loop_ub; i++) {
    sizes_idx_1 = WqColInds->size[1];
    for (i1 = 0; i1 < sizes_idx_1; i1++) {
      pulse_position_value_data[pulse_position_value->size[0] * i1 +
                                pulse_position_value->size[0] *
                                    pulse_position_value->size[1] * i] = 1.0;
    }
  }
  /*  first pulse is always in position 1 */
  /*  loop through the mean PRI values */
  i = priMeansList->size[1];
  for (sizes_idx_1 = 0; sizes_idx_1 < i; sizes_idx_1++) {
    i1 = (int)(reps - 1.0);
    for (k = 0; k < i1; k++) {
      i2 = WqColInds->size[1];
      for (loop_ub = 0; loop_ub < i2; loop_ub++) {
        pulse_position_value_data[((k +
                                    pulse_position_value->size[0] * loop_ub) +
                                   pulse_position_value->size[0] *
                                       pulse_position_value->size[1] *
                                       sizes_idx_1) +
                                  1] =
            ((((double)k + 2.0) - 1.0) * priMeansList_data[sizes_idx_1] + 1.0) +
            WqColInds_data[loop_ub];
      }
    }
  }
  /*  generate the pulse_position_matrix by considering */
  /*  all possible combinations of the values; */
  /*  each row is for one pattern, there are K columns; */
  /*  pulse_position_matrix( i_pattern, k) */
  /*  */
  /*  The number of columns is the number of possible positions */
  /*  */
  /*  we generate a num_PRI_jitters^(K-1) x K matrix */
  /*  using the function cartesian_prod_func */
  /*  */
  /*  we stack matrices vertically into the pulse_position_matrix */
  num_position_patterns = (double)priMeansList->size[1] *
                          rt_powd_snf(WqColInds->size[1], reps - 1.0);
  emxInit_real_T(&pulsePositionMatrix, 2);
  i = pulsePositionMatrix->size[0] * pulsePositionMatrix->size[1];
  pulsePositionMatrix->size[0] = (int)num_position_patterns;
  pulsePositionMatrix->size[1] = (int)(reps - 1.0);
  emxEnsureCapacity_real_T(pulsePositionMatrix, i);
  WqColInds_data = pulsePositionMatrix->data;
  loop_ub = (int)num_position_patterns * (int)(reps - 1.0);
  for (i = 0; i < loop_ub; i++) {
    WqColInds_data[i] = 0.0;
  }
  /*  number of rows per PRI mean */
  i = priMeansList->size[1];
  if (priMeansList->size[1] - 1 >= 0) {
    if (pulse_position_value->size[0] < 2) {
      iacol = 1;
      ibmat = 0;
    } else {
      iacol = 2;
      ibmat = pulse_position_value->size[0];
    }
    num_members_per_set = pulse_position_value->size[1];
    nrows = ibmat - iacol;
    num_rows_C =
        rt_powd_snf(pulse_position_value->size[1], (double)nrows + 1.0);
    ncols = (int)num_rows_C * (nrows + 1);
  }
  emxInit_real_T(&pattern_matrix, 2);
  for (i_set = 0; i_set < i; i_set++) {
    double d;
    /*      % DEBUG */
    /*      a = [ 1 1 1 ]; b = [ 309 310 311 ]; c = [ 618 619 620 ]; */
    /*      A = [ a; b; c ]; */
    /*  since pattern is "fundamental" pattern starting with a pulse in the */
    /*  first STFT window, we only need to look at combinations */
    /*  rows 2:end, and then add the column of ones */
    /*    returns the Cartesian product C of the (values in the) rows  */
    /*    of the input matrix A. */
    /*    Each row of A is taken as a set to draw from */
    /*    Assumes all sets have the same number of members */
    i1 = pattern_matrix->size[0] * pattern_matrix->size[1];
    pattern_matrix->size[0] = (int)num_rows_C;
    i2 = ibmat - iacol;
    pattern_matrix->size[1] = i2 + 1;
    emxEnsureCapacity_real_T(pattern_matrix, i1);
    pattern_matrix_data = pattern_matrix->data;
    for (i1 = 0; i1 < ncols; i1++) {
      pattern_matrix_data[i1] = 0.0;
    }
    /*  loop through columns of C */
    for (sizes_idx_1 = 0; sizes_idx_1 <= nrows; sizes_idx_1++) {
      double stride;
      unsigned int i_col_A;
      /*  fill the column (aka fill the elements in the column) */
      /*  stride is number of elements to repeat in a column */
      /*  num_strides is number of strides per column */
      stride = rt_powd_snf(num_members_per_set, i2 - sizes_idx_1);
      i_col_A = 0U;
      /*  the column in A that we use */
      i1 = (int)(num_rows_C / stride);
      for (i_stride = 0; i_stride < i1; i_stride++) {
        double star;
        i_col_A++;
        if (i_col_A > (unsigned int)num_members_per_set) {
          i_col_A = 1U;
        }
        star = (((double)i_stride + 1.0) - 1.0) * stride + 1.0;
        /*  column of C gets elements from row of A */
        d = (star + stride) - 1.0;
        if (star > d) {
          i3 = 0;
          k = 0;
        } else {
          i3 = (int)star - 1;
          k = (int)d;
        }
        loop_ub = k - i3;
        for (k = 0; k < loop_ub; k++) {
          pattern_matrix_data[(i3 + k) +
                              pattern_matrix->size[0] * sizes_idx_1] =
              pulse_position_value_data
                  [(((iacol + sizes_idx_1) +
                     pulse_position_value->size[0] * ((int)i_col_A - 1)) +
                    pulse_position_value->size[0] *
                        pulse_position_value->size[1] * i_set) -
                   1];
        }
      }
    }
    d = (((double)i_set + 1.0) - 1.0) * n_shifts + 1.0;
    if (d > ((double)i_set + 1.0) * n_shifts) {
      i1 = 1;
    } else {
      i1 = (int)d;
    }
    loop_ub = pattern_matrix->size[1];
    for (i2 = 0; i2 < loop_ub; i2++) {
      sizes_idx_1 = pattern_matrix->size[0];
      for (i3 = 0; i3 < sizes_idx_1; i3++) {
        WqColInds_data[((i1 + i3) + pulsePositionMatrix->size[0] * i2) - 1] =
            pattern_matrix_data[i3 + pattern_matrix->size[0] * i2];
      }
    }
  }
  emxFree_real_T(&pulse_position_value);
  if ((int)num_position_patterns != 0) {
    iacol = (int)num_position_patterns;
  } else if ((pulsePositionMatrix->size[0] != 0) &&
             (pulsePositionMatrix->size[1] != 0)) {
    iacol = pulsePositionMatrix->size[0];
  } else {
    iacol = (int)num_position_patterns;
    if (iacol < 0) {
      iacol = 0;
    }
    if (pulsePositionMatrix->size[0] > iacol) {
      iacol = pulsePositionMatrix->size[0];
    }
  }
  empty_non_axis_sizes = (iacol == 0);
  if (empty_non_axis_sizes || ((int)num_position_patterns != 0)) {
    input_sizes_idx_1 = 1;
  } else {
    input_sizes_idx_1 = 0;
  }
  if (empty_non_axis_sizes || ((pulsePositionMatrix->size[0] != 0) &&
                               (pulsePositionMatrix->size[1] != 0))) {
    sizes_idx_1 = pulsePositionMatrix->size[1];
  } else {
    sizes_idx_1 = 0;
  }
  /*  remove duplicate patterns */
  i = pattern_matrix->size[0] * pattern_matrix->size[1];
  pattern_matrix->size[0] = iacol;
  pattern_matrix->size[1] = input_sizes_idx_1 + sizes_idx_1;
  emxEnsureCapacity_real_T(pattern_matrix, i);
  pattern_matrix_data = pattern_matrix->data;
  loop_ub = input_sizes_idx_1;
  if (loop_ub - 1 >= 0) {
    for (i = 0; i < iacol; i++) {
      pattern_matrix_data[i] = 1.0;
    }
  }
  for (i = 0; i < sizes_idx_1; i++) {
    for (i1 = 0; i1 < iacol; i1++) {
      pattern_matrix_data[i1 +
                          pattern_matrix->size[0] * (i + input_sizes_idx_1)] =
          WqColInds_data[i1 + iacol * i];
    }
  }
  unique_rows(pattern_matrix, pulsePositionMatrix);
  WqColInds_data = pulsePositionMatrix->data;
  /*  if K>1 */
  /*      %n_shifts = min(pulsePositionMatrix(:,2))-1;   %The number of shifts
   * necessary.  */
  /*   */
  /*  else */
  /*      n_shifts = max(PRI_means_q)+max(PRI_jitters_q); */
  /*  end */
  /* The max element of the ppm for K>1 is (K-1)*(N+M)+J+1 which is the latest
   */
  /* possible index of the Kth pulse if the first arrived at n = 1.  */
  /*  */
  /* The max element of the ppm for K=1 is 1 which is the first possible index
   */
  /* of the 1st pulse.  */
  /*  */
  /* The size of the STFT matrix is the latest possible location of the Kth */
  /* pulse which is equal to K*(N+M)+J+1 */
  /*  */
  /* We want to take the PPM matrix that contains the the time locations for */
  /* the search if the first pulse is at n=1 and shift them to do the search if
   */
  /* the first pulse arrives and n = 2,..., N+M+J+1 which is the latest */
  /* possible location of the pulse pulse. The difference is N+M+J+1-1 = N+M+J
   */
  /* This is the max number we need to add the the PPM matrix.  */
  /*  */
  /* For the K = 1 case, the PPM is simply 1 and we add N+M+J which generates a
   */
  /* Wq matrix with a dimension of 1+N+M+J. This is equivalent to the STFT */
  /* size definition for K = 1, which is K(N+M)+J+1 = N+M+J+1, so the sizes */
  /* will be compatible.  */
  /*  */
  /* For the K > 1 case however the maximum element of the PPM is */
  /* (K-1)(N+M)+J+1. Adding N+M+J to this will result in a Wq with a dimension
   */
  /* of (K-1)(N+M)+J+1+N+M+J = K(N+M)+2J+1. This will be J elements larger than
   */
  /* the STFT definitions of K(N+M)+J+1. This extra J comes from the fact that
   */
  /* the max element of the PPM include the jitter of the final pulse and we */
  /* also include the jitter in the shifting. Because jitter is stochastic and
   */
  /* zero mean, we don't sum jitter over multiple pulses. We need to remove the
   */
  /* extra jitter when shifting for K>1.  */
  /*  */
  if (reps > 1.0) {
    iacol = priMeansList->size[1];
    b_priMeansList = *priMeansList;
    c_priMeansList = iacol;
    b_priMeansList.size = &c_priMeansList;
    b_priMeansList.numDimensions = 1;
    n_shifts = maximum(&b_priMeansList);
    /* Equivalent to N+M+J-J */
  } else {
    iacol = priMeansList->size[1];
    sizes_idx_1 = WqColInds->size[1];
    b_priMeansList = *priMeansList;
    d_priMeansList = iacol;
    b_priMeansList.size = &d_priMeansList;
    b_priMeansList.numDimensions = 1;
    b_WqColInds = *WqColInds;
    c_WqColInds = sizes_idx_1;
    b_WqColInds.size = &c_WqColInds;
    b_WqColInds.numDimensions = 1;
    n_shifts = maximum(&b_priMeansList) + maximum(&b_WqColInds);
    /* Equivalent to N+M+J */
  }
  /* Number of rows in pulse_position_matrix */
  /* Number of cols in pulse_position_matrix --- should always be K */
  i = pattern_matrix->size[0] * pattern_matrix->size[1];
  pattern_matrix->size[0] =
      pulsePositionMatrix->size[0] * (int)(n_shifts + 1.0);
  pattern_matrix->size[1] = pulsePositionMatrix->size[1];
  emxEnsureCapacity_real_T(pattern_matrix, i);
  pattern_matrix_data = pattern_matrix->data;
  nrows = pulsePositionMatrix->size[0];
  ncols = pulsePositionMatrix->size[1];
  sizes_idx_1 = (int)(n_shifts + 1.0);
  for (i_stride = 0; i_stride < ncols; i_stride++) {
    iacol = i_stride * nrows;
    ibmat = i_stride * (nrows * (int)(n_shifts + 1.0)) - 1;
    for (loop_ub = 0; loop_ub < sizes_idx_1; loop_ub++) {
      num_members_per_set = ibmat + loop_ub * nrows;
      for (k = 0; k < nrows; k++) {
        pattern_matrix_data[(num_members_per_set + k) + 1] =
            WqColInds_data[iacol + k];
      }
    }
  }
  /* Create multiple copies of the PPM matrix. Each copy will eventually be
   * shifted. The second copy will get a 1 added to it, the third a 2 added, and
   * so on up to n_shifts. Use n_shifts+1 to account for the first one that
   * receives no shifting. */
  /* Get the number of rows in the big PPM matrix */
  if (rtIsNaN(n_shifts)) {
    i = priMeansList->size[0] * priMeansList->size[1];
    priMeansList->size[0] = 1;
    priMeansList->size[1] = 1;
    emxEnsureCapacity_real_T(priMeansList, i);
    priMeansList_data = priMeansList->data;
    priMeansList_data[0] = rtNaN;
  } else if (n_shifts < 0.0) {
    priMeansList->size[0] = 1;
    priMeansList->size[1] = 0;
  } else {
    i = priMeansList->size[0] * priMeansList->size[1];
    priMeansList->size[0] = 1;
    priMeansList->size[1] = (int)n_shifts + 1;
    emxEnsureCapacity_real_T(priMeansList, i);
    priMeansList_data = priMeansList->data;
    loop_ub = (int)n_shifts;
    for (i = 0; i <= loop_ub; i++) {
      priMeansList_data[i] = i;
    }
  }
  emxInit_real_T(&shiftermat, 2);
  i = shiftermat->size[0] * shiftermat->size[1];
  shiftermat->size[0] = pulsePositionMatrix->size[0];
  shiftermat->size[1] = priMeansList->size[1];
  emxEnsureCapacity_real_T(shiftermat, i);
  WqColInds_data = shiftermat->data;
  ncols = priMeansList->size[1];
  sizes_idx_1 = pulsePositionMatrix->size[0];
  for (i_stride = 0; i_stride < ncols; i_stride++) {
    ibmat = i_stride * sizes_idx_1;
    for (loop_ub = 0; loop_ub < sizes_idx_1; loop_ub++) {
      WqColInds_data[ibmat + loop_ub] = priMeansList_data[i_stride];
    }
  }
  /* Create a matrix of the shifts needed for each copy of the PPM matrix */
  emxInit_real_T(&WqRowInds, 2);
  i = WqRowInds->size[0] * WqRowInds->size[1];
  WqRowInds->size[0] = shiftermat->size[0] * shiftermat->size[1];
  WqRowInds->size[1] = pulsePositionMatrix->size[1];
  emxEnsureCapacity_real_T(WqRowInds, i);
  pulse_position_value_data = WqRowInds->data;
  nrows = shiftermat->size[0] * shiftermat->size[1];
  sizes_idx_1 = pulsePositionMatrix->size[1];
  for (ibmat = 0; ibmat < sizes_idx_1; ibmat++) {
    iacol = ibmat * nrows;
    for (k = 0; k < nrows; k++) {
      pulse_position_value_data[iacol + k] = WqColInds_data[k];
    }
  }
  emxFree_real_T(&shiftermat);
  if ((WqRowInds->size[0] == pattern_matrix->size[0]) &&
      (WqRowInds->size[1] == pattern_matrix->size[1])) {
    loop_ub = WqRowInds->size[0] * WqRowInds->size[1];
    for (i = 0; i < loop_ub; i++) {
      pulse_position_value_data[i] += pattern_matrix_data[i];
    }
  } else {
    plus(WqRowInds, pattern_matrix);
    pulse_position_value_data = WqRowInds->data;
  }
  if (pattern_matrix->size[0] < 1) {
    priMeansList->size[0] = 1;
    priMeansList->size[1] = 0;
  } else {
    i = priMeansList->size[0] * priMeansList->size[1];
    priMeansList->size[0] = 1;
    priMeansList->size[1] = pattern_matrix->size[0];
    emxEnsureCapacity_real_T(priMeansList, i);
    priMeansList_data = priMeansList->data;
    loop_ub = pattern_matrix->size[0] - 1;
    for (i = 0; i <= loop_ub; i++) {
      priMeansList_data[i] = (double)i + 1.0;
    }
  }
  emxFree_real_T(&pattern_matrix);
  i = WqColInds->size[0] * WqColInds->size[1];
  WqColInds->size[0] = 1;
  WqColInds->size[1] = priMeansList->size[1] * pulsePositionMatrix->size[1];
  emxEnsureCapacity_real_T(WqColInds, i);
  WqColInds_data = WqColInds->data;
  ncols = priMeansList->size[1];
  sizes_idx_1 = pulsePositionMatrix->size[1];
  emxFree_real_T(&pulsePositionMatrix);
  for (ibmat = 0; ibmat < sizes_idx_1; ibmat++) {
    iacol = ibmat * ncols;
    for (i_stride = 0; i_stride < ncols; i_stride++) {
      WqColInds_data[iacol + i_stride] = priMeansList_data[i_stride];
    }
  }
  emxFree_real_T(&priMeansList);
  ibmat = WqColInds->size[1];
  sizes_idx_1 = WqRowInds->size[0] * WqRowInds->size[1];
  emxInit_int32_T(&ridxInt, 1);
  i = ridxInt->size[0];
  ridxInt->size[0] = WqRowInds->size[0] * WqRowInds->size[1];
  emxEnsureCapacity_int32_T(ridxInt, i);
  ridxInt_data = ridxInt->data;
  for (k = 0; k < sizes_idx_1; k++) {
    ridxInt_data[k] = (int)pulse_position_value_data[k];
  }
  emxFree_real_T(&WqRowInds);
  sizes_idx_1 = WqColInds->size[1];
  emxInit_int32_T(&cidxInt, 1);
  i = cidxInt->size[0];
  cidxInt->size[0] = WqColInds->size[1];
  emxEnsureCapacity_int32_T(cidxInt, i);
  cidxInt_data = cidxInt->data;
  for (k = 0; k < sizes_idx_1; k++) {
    cidxInt_data[k] = (int)WqColInds_data[k];
  }
  emxInit_int32_T(&sortedIndices, 1);
  i = sortedIndices->size[0];
  sortedIndices->size[0] = WqColInds->size[1];
  emxEnsureCapacity_int32_T(sortedIndices, i);
  sortedIndices_data = sortedIndices->data;
  for (k = 0; k < ibmat; k++) {
    sortedIndices_data[k] = k + 1;
  }
  introsort(sortedIndices, cidxInt->size[0], cidxInt, ridxInt);
  sortedIndices_data = sortedIndices->data;
  iacol = cidxInt->size[0];
  emxInit_int32_T(&t, 1);
  i = t->size[0];
  t->size[0] = cidxInt->size[0];
  emxEnsureCapacity_int32_T(t, i);
  t_data = t->data;
  loop_ub = cidxInt->size[0];
  for (i = 0; i < loop_ub; i++) {
    t_data[i] = cidxInt_data[i];
  }
  for (k = 0; k < iacol; k++) {
    cidxInt_data[k] = t_data[sortedIndices_data[k] - 1];
  }
  iacol = ridxInt->size[0];
  i = t->size[0];
  t->size[0] = ridxInt->size[0];
  emxEnsureCapacity_int32_T(t, i);
  t_data = t->data;
  loop_ub = ridxInt->size[0];
  for (i = 0; i < loop_ub; i++) {
    t_data[i] = ridxInt_data[i];
  }
  for (k = 0; k < iacol; k++) {
    ridxInt_data[k] = t_data[sortedIndices_data[k] - 1];
  }
  emxFree_int32_T(&t);
  emxFree_int32_T(&sortedIndices);
  if ((ridxInt->size[0] == 0) || (cidxInt->size[0] == 0)) {
    iacol = 0;
    Wq->n = 0;
  } else {
    sizes_idx_1 = ridxInt->size[0];
    iacol = ridxInt_data[0];
    for (k = 2; k <= sizes_idx_1; k++) {
      i = ridxInt_data[k - 1];
      if (iacol < i) {
        iacol = i;
      }
    }
    Wq->n = cidxInt_data[cidxInt->size[0] - 1];
  }
  Wq->m = iacol;
  iacol = WqColInds->size[1];
  if (iacol < 1) {
    iacol = 1;
  }
  emxFree_real_T(&WqColInds);
  i = Wq->d->size[0];
  Wq->d->size[0] = iacol;
  emxEnsureCapacity_real_T(Wq->d, i);
  for (i = 0; i < iacol; i++) {
    Wq->d->data[i] = 0.0;
  }
  i = Wq->colidx->size[0];
  Wq->colidx->size[0] = Wq->n + 1;
  emxEnsureCapacity_int32_T(Wq->colidx, i);
  Wq->colidx->data[0] = 1;
  i = Wq->rowidx->size[0];
  Wq->rowidx->size[0] = iacol;
  emxEnsureCapacity_int32_T(Wq->rowidx, i);
  for (i = 0; i < iacol; i++) {
    Wq->rowidx->data[i] = 0;
  }
  iacol = 0;
  i = Wq->n;
  for (sizes_idx_1 = 0; sizes_idx_1 < i; sizes_idx_1++) {
    while ((iacol + 1 <= ibmat) && (cidxInt_data[iacol] == sizes_idx_1 + 1)) {
      Wq->rowidx->data[iacol] = ridxInt_data[iacol];
      iacol++;
    }
    Wq->colidx->data[sizes_idx_1 + 1] = iacol + 1;
  }
  emxFree_int32_T(&cidxInt);
  emxFree_int32_T(&ridxInt);
  for (k = 0; k < ibmat; k++) {
    Wq->d->data[k] = 1.0;
  }
  sparse_fillIn(Wq);
  /* , obj.reps(i)); */
}

/*
 * File trailer for buildtimecorrelatormatrix.c
 *
 * [EOF]
 */
