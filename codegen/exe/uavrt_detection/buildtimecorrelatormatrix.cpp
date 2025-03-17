//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: buildtimecorrelatormatrix.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "buildtimecorrelatormatrix.h"
#include "assembleWq.h"
#include "colon.h"
#include "minOrMax.h"
#include "mpower.h"
#include "repmat.h"
#include "rt_nonfinite.h"
#include "sparse.h"
#include "sparse1.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "unique.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// BUILDTIMECORRELATIONMATRIX Assembles the time correlation matrix that is
// used in the incoherent summation step.
// INPUTS:
//    pri         Pulse repetition interval in stft time windows (N)
//    priUncert   Pulse repetition interval uncertainty in stft time windows
//                (M)
//    priJtr      Pulse repetition interval jitter in stft time windows (J)
//    reps        Pulse repetitions to consider (K)
//
// Arguments    : double pri
//                double priUncert
//                double priJtr
//                double reps
//                coder::sparse &Wq
// Return Type  : void
//
void buildtimecorrelatormatrix(double pri, double priUncert, double priJtr,
                               double reps, coder::sparse &Wq)
{
  static rtBoundsCheckInfo ab_emlrtBCI{
      48,                             // lineNo
      "PRI_mean_value",               // aName
      "generate_pulse_positions_func" // fName
  };
  static rtBoundsCheckInfo bb_emlrtBCI{
      48,                             // lineNo
      "PRI_jitter_value",             // aName
      "generate_pulse_positions_func" // fName
  };
  static rtBoundsCheckInfo cb_emlrtBCI{
      47,                             // lineNo
      "pulse_position_value",         // aName
      "generate_pulse_positions_func" // fName
  };
  static rtBoundsCheckInfo db_emlrtBCI{
      47,                             // lineNo
      "pulse_position_value",         // aName
      "generate_pulse_positions_func" // fName
  };
  static rtBoundsCheckInfo eb_emlrtBCI{
      47,                             // lineNo
      "pulse_position_value",         // aName
      "generate_pulse_positions_func" // fName
  };
  static rtBoundsCheckInfo fb_emlrtBCI{
      79,                             // lineNo
      "pulse_position_value",         // aName
      "generate_pulse_positions_func" // fName
  };
  static rtBoundsCheckInfo gb_emlrtBCI{
      46,                   // lineNo
      "C",                  // aName
      "cartesian_prod_func" // fName
  };
  static rtBoundsCheckInfo hb_emlrtBCI{
      46,                   // lineNo
      "A",                  // aName
      "cartesian_prod_func" // fName
  };
  static rtBoundsCheckInfo ib_emlrtBCI{
      46,                   // lineNo
      "C",                  // aName
      "cartesian_prod_func" // fName
  };
  static rtBoundsCheckInfo jb_emlrtBCI{
      46,                   // lineNo
      "C",                  // aName
      "cartesian_prod_func" // fName
  };
  static rtBoundsCheckInfo kb_emlrtBCI{
      80,                             // lineNo
      "pulse_position_matrix",        // aName
      "generate_pulse_positions_func" // fName
  };
  static rtBoundsCheckInfo lb_emlrtBCI{
      80,                             // lineNo
      "pulse_position_matrix",        // aName
      "generate_pulse_positions_func" // fName
  };
  static rtDoubleCheckInfo ab_emlrtDCI{
      18,                   // lineNo
      "cartesian_prod_func" // fName
  };
  static rtDoubleCheckInfo bb_emlrtDCI{
      46,                   // lineNo
      "cartesian_prod_func" // fName
  };
  static rtDoubleCheckInfo cb_emlrtDCI{
      46,                   // lineNo
      "cartesian_prod_func" // fName
  };
  static rtDoubleCheckInfo db_emlrtDCI{
      80,                             // lineNo
      "generate_pulse_positions_func" // fName
  };
  static rtDoubleCheckInfo eb_emlrtDCI{
      80,                             // lineNo
      "generate_pulse_positions_func" // fName
  };
  static rtDoubleCheckInfo fb_emlrtDCI{
      84,                             // lineNo
      "generate_pulse_positions_func" // fName
  };
  static rtDoubleCheckInfo q_emlrtDCI{
      30,                         // lineNo
      "buildtimecorrelatormatrix" // fName
  };
  static rtDoubleCheckInfo r_emlrtDCI{
      32,                         // lineNo
      "buildtimecorrelatormatrix" // fName
  };
  static rtDoubleCheckInfo s_emlrtDCI{
      34,                             // lineNo
      "generate_pulse_positions_func" // fName
  };
  static rtDoubleCheckInfo t_emlrtDCI{
      34,                             // lineNo
      "generate_pulse_positions_func" // fName
  };
  static rtDoubleCheckInfo u_emlrtDCI{
      34,                             // lineNo
      "generate_pulse_positions_func" // fName
  };
  static rtDoubleCheckInfo v_emlrtDCI{
      36,                             // lineNo
      "generate_pulse_positions_func" // fName
  };
  static rtDoubleCheckInfo w_emlrtDCI{
      39,                             // lineNo
      "generate_pulse_positions_func" // fName
  };
  static rtDoubleCheckInfo x_emlrtDCI{
      66,                             // lineNo
      "generate_pulse_positions_func" // fName
  };
  static rtDoubleCheckInfo y_emlrtDCI{
      66,                             // lineNo
      "generate_pulse_positions_func" // fName
  };
  static rtEqualityCheckInfo g_emlrtECI{
      1,           // nDims
      70,          // lineNo
      "assembleWq" // fName
  };
  static rtEqualityCheckInfo h_emlrtECI{
      -1,                         // nDims
      40,                         // lineNo
      "buildtimecorrelatormatrix" // fName
  };
  static rtEqualityCheckInfo i_emlrtECI{
      -1,                         // nDims
      42,                         // lineNo
      "buildtimecorrelatormatrix" // fName
  };
  static rtEqualityCheckInfo j_emlrtECI{
      -1,                             // nDims
      36,                             // lineNo
      "generate_pulse_positions_func" // fName
  };
  static rtEqualityCheckInfo k_emlrtECI{
      -1,                             // nDims
      80,                             // lineNo
      "generate_pulse_positions_func" // fName
  };
  static rtEqualityCheckInfo l_emlrtECI{
      2,           // nDims
      70,          // lineNo
      "assembleWq" // fName
  };
  coder::array<double, 3U> pulse_position_value;
  coder::array<double, 2U> WqRowInds;
  coder::array<double, 2U> b_pulsePositionMatrix;
  coder::array<double, 2U> pattern_matrix;
  coder::array<double, 2U> priJtrList;
  coder::array<double, 2U> priMeansList;
  coder::array<double, 2U> shiftermat;
  coder::array<double, 1U> b_WqRowInds;
  coder::array<double, 1U> b_priMeansList;
  coder::array<double, 1U> r;
  double d;
  double n_rows;
  double num_PRI_patterns;
  double num_position_patterns;
  double stride;
  int sizes[2];
  int b_loop_ub;
  int b_num_PRI_patterns;
  int i;
  int i1;
  int i2;
  int i3;
  int i4;
  int i5;
  int i_jitter;
  int loop_ub;
  int loop_ub_tmp;
  int num_members_per_set;
  int num_rows_C_tmp{0};
  int pulsePositionMatrix;
  int result;
  signed char input_sizes_idx_1;
  boolean_T empty_non_axis_sizes;
  if (!(pri >= 0.0)) {
    m_rtErrorWithMessageID("0", n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
  }
  if (!(priUncert >= 0.0)) {
    m_rtErrorWithMessageID("0", n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
  }
  if (!(priJtr >= 0.0)) {
    m_rtErrorWithMessageID("0", n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
  }
  if (!(reps >= 1.0)) {
    m_rtErrorWithMessageID("1", n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
  }
  // First check to make sure all inputs contain the same number of
  // elements
  d = 2.0 * priUncert + 1.0;
  i = static_cast<int>(std::floor(d));
  if (d != i) {
    rtIntegerError(d, q_emlrtDCI);
  }
  i1 = static_cast<int>(d);
  if (i1 != i) {
    rtIntegerError(d, q_emlrtDCI);
  }
  num_PRI_patterns = 2.0 * priJtr + 1.0;
  i = static_cast<int>(std::floor(num_PRI_patterns));
  if (num_PRI_patterns != i) {
    rtIntegerError(num_PRI_patterns, r_emlrtDCI);
  }
  i2 = static_cast<int>(num_PRI_patterns);
  if (i2 != i) {
    rtIntegerError(num_PRI_patterns, r_emlrtDCI);
  }
  // Change names to align with other code.
  if ((std::isinf(-priUncert) || std::isinf(priUncert)) &&
      (-priUncert == priUncert)) {
    priJtrList.set_size(1, 1);
    priJtrList[0] = rtNaN;
  } else if (std::floor(-priUncert) == -priUncert) {
    loop_ub = static_cast<int>(priUncert - (-priUncert));
    priJtrList.set_size(1, loop_ub + 1);
    for (i = 0; i <= loop_ub; i++) {
      priJtrList[i] = -priUncert + static_cast<double>(i);
    }
  } else {
    coder::eml_float_colon(-priUncert, priUncert, priJtrList);
  }
  loop_ub = priJtrList.size(1);
  if (i1 != priJtrList.size(1)) {
    rtSizeEq1DError(static_cast<int>(d), priJtrList.size(1), h_emlrtECI);
  }
  priMeansList.set_size(1, priJtrList.size(1));
  for (i = 0; i < loop_ub; i++) {
    priMeansList[i] = pri + priJtrList[i];
  }
  if ((std::isinf(-priJtr) || std::isinf(priJtr)) && (-priJtr == priJtr)) {
    priJtrList.set_size(1, 1);
    priJtrList[0] = rtNaN;
  } else if (std::floor(-priJtr) == -priJtr) {
    b_loop_ub = static_cast<int>(priJtr - (-priJtr));
    priJtrList.set_size(1, b_loop_ub + 1);
    for (i = 0; i <= b_loop_ub; i++) {
      priJtrList[i] = -priJtr + static_cast<double>(i);
    }
  } else {
    coder::eml_float_colon(-priJtr, priJtr, priJtrList);
  }
  b_loop_ub = priJtrList.size(1);
  if (i2 != priJtrList.size(1)) {
    rtSizeEq1DError(static_cast<int>(num_PRI_patterns), priJtrList.size(1),
                    i_emlrtECI);
  }
  //  ASSEMBLEWQ Build the Wq matrix that is used in the incoherent summation
  //  based on a set of mean PRI values, jitter values, and the number of
  //  pulses to sum (K).
  // INPUTS:
  //    PRI_means   a vector of mean PRI values in units of STFT windows.
  //    PRI_jitters a vector of the jitter values in units of STFT windows.
  //    K           The number of pulses that will be summed
  // OUTPUTS:
  //    Wq          a sparse matrix to be used for the incoherent summation
  //
  // Example. Consider an interpulse nominal time of 10 stft windows and an
  // uncertainty of 2. The PRI_mean values would be the vector 10 + (-2:2) =
  //  [8     9    10    11    12]. Jitters input would be something like -1:1.
  //
  // --------------------------------------------------------------------------
  // PPM Contains the column positions (time windows) in the S matrix to search
  // for the K pulses assuming the first pulse arrives at window 1.
  //  GENERATE_PULSE_POSITIONS_FUNC generates the pulse position matrix from
  //  the number of pulses, mean pri values, and jitter values.
  //  PPM Contains the column positions (time windows) in the S matrix to
  //  search for the K pulses assuming the first pulse arrives at window 1.
  //
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
  //  Author: Paul G. Flikkema
  //  Date:   1 Oct 2021
  // --------------------------------------------------------------------------
  num_PRI_patterns =
      static_cast<double>(priMeansList.size(1)) *
      coder::mpower(static_cast<double>(priJtrList.size(1)), reps - 1.0);
  if (!(num_PRI_patterns >= 0.0)) {
    rtNonNegativeError(num_PRI_patterns, s_emlrtDCI);
  }
  i = static_cast<int>(std::floor(num_PRI_patterns));
  if (num_PRI_patterns != i) {
    rtIntegerError(num_PRI_patterns, t_emlrtDCI);
  }
  i1 = static_cast<int>(std::floor(reps));
  if (reps != i1) {
    rtIntegerError(reps, u_emlrtDCI);
  }
  if (static_cast<int>(num_PRI_patterns) != i) {
    rtIntegerError(num_PRI_patterns, t_emlrtDCI);
  }
  i2 = static_cast<int>(reps);
  if (i2 != i1) {
    rtIntegerError(reps, u_emlrtDCI);
  }
  //  place first pulse at pulse position q = 1
  if (static_cast<int>(num_PRI_patterns) != i) {
    rtIntegerError(num_PRI_patterns, v_emlrtDCI);
  }
  pulsePositionMatrix = static_cast<int>(num_PRI_patterns);
  rtSubAssignSizeCheck(&pulsePositionMatrix, 1, &pulsePositionMatrix, 1,
                       j_emlrtECI);
  //  based on the model, generate all the pulse position values in a 3D matrix
  if (i2 != i1) {
    rtIntegerError(reps, w_emlrtDCI);
  }
  pulse_position_value.set_size(i2, priJtrList.size(1), loop_ub);
  loop_ub_tmp = i2 * priJtrList.size(1) * priMeansList.size(1);
  for (i = 0; i < loop_ub_tmp; i++) {
    pulse_position_value[i] = 0.0;
  }
  for (i = 0; i < loop_ub; i++) {
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      pulse_position_value[pulse_position_value.size(0) * i1 +
                           pulse_position_value.size(0) *
                               pulse_position_value.size(1) * i] = 1.0;
    }
  }
  //  first pulse is always in position 1
  //  loop through the mean PRI values
  for (pulsePositionMatrix = 0; pulsePositionMatrix < loop_ub;
       pulsePositionMatrix++) {
    i = static_cast<int>(reps - 1.0);
    for (b_num_PRI_patterns = 0; b_num_PRI_patterns < i; b_num_PRI_patterns++) {
      for (i_jitter = 0; i_jitter < b_loop_ub; i_jitter++) {
        if (pulsePositionMatrix + 1 > loop_ub) {
          rtDynamicBoundsError(pulsePositionMatrix + 1, 1, loop_ub,
                               ab_emlrtBCI);
        }
        if (i_jitter + 1 > b_loop_ub) {
          rtDynamicBoundsError(i_jitter + 1, 1, b_loop_ub, bb_emlrtBCI);
        }
        if (static_cast<int>(static_cast<unsigned int>(b_num_PRI_patterns) +
                             2U) > i2) {
          rtDynamicBoundsError(
              static_cast<int>(static_cast<unsigned int>(b_num_PRI_patterns) +
                               2U),
              1, static_cast<int>(reps), cb_emlrtBCI);
        }
        if (i_jitter + 1 > b_loop_ub) {
          rtDynamicBoundsError(i_jitter + 1, 1, b_loop_ub, db_emlrtBCI);
        }
        if (pulsePositionMatrix + 1 > loop_ub) {
          rtDynamicBoundsError(pulsePositionMatrix + 1, 1, loop_ub,
                               eb_emlrtBCI);
        }
        pulse_position_value
            [((b_num_PRI_patterns + pulse_position_value.size(0) * i_jitter) +
              pulse_position_value.size(0) * pulse_position_value.size(1) *
                  pulsePositionMatrix) +
             1] = (((static_cast<double>(b_num_PRI_patterns) + 2.0) - 1.0) *
                       priMeansList[pulsePositionMatrix] +
                   1.0) +
                  priJtrList[i_jitter];
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
      coder::mpower(static_cast<double>(priJtrList.size(1)), reps - 1.0);
  if (!(num_position_patterns >= 0.0)) {
    rtNonNegativeError(num_position_patterns, x_emlrtDCI);
  }
  i = static_cast<int>(std::floor(num_position_patterns));
  if (num_position_patterns != i) {
    rtIntegerError(num_position_patterns, y_emlrtDCI);
  }
  loop_ub_tmp = static_cast<int>(reps - 1.0);
  result = static_cast<int>(num_position_patterns);
  b_pulsePositionMatrix.set_size(result, loop_ub_tmp);
  pulsePositionMatrix = result * loop_ub_tmp;
  for (i1 = 0; i1 < pulsePositionMatrix; i1++) {
    b_pulsePositionMatrix[i1] = 0.0;
  }
  n_rows = coder::mpower(static_cast<double>(priJtrList.size(1)), reps - 1.0);
  //  number of rows per PRI mean
  if (priMeansList.size(1) - 1 >= 0) {
    if (pulse_position_value.size(0) < 2) {
      i3 = 0;
      i4 = 0;
    } else {
      i3 = 1;
      i4 = i2;
    }
    num_members_per_set = priJtrList.size(1);
    i5 = i4 - i3;
  }
  if (loop_ub - 1 >= 0) {
    num_rows_C_tmp = i4 - i3;
  }
  for (int i_set{0}; i_set < loop_ub; i_set++) {
    //      % DEBUG
    //      a = [ 1 1 1 ]; b = [ 309 310 311 ]; c = [ 618 619 620 ];
    //      A = [ a; b; c ];
    //  since pattern is "fundamental" pattern starting with a pulse in the
    //  first STFT window, we only need to look at combinations
    //  rows 2:end, and then add the column of ones
    if (i_set + 1 > loop_ub) {
      rtDynamicBoundsError(i_set + 1, 1, loop_ub, fb_emlrtBCI);
    }
    // CARTESIAN_PROD_FUNC returns the Cartesian product C of the values in the
    //  rows of the input matrix A. Each row of A is taken as a set to draw from
    //  Assumes all sets have the same number of members
    // INPUTS:
    //    A   nxm matrix
    // OUTPUTS:
    //    C   a matrix of all the combinations of the sets in the columns of A
    num_PRI_patterns =
        coder::mpower(static_cast<double>(pulse_position_value.size(1)),
                      (static_cast<double>(num_rows_C_tmp) - 1.0) + 1.0);
    if (num_PRI_patterns != static_cast<int>(std::floor(num_PRI_patterns))) {
      rtIntegerError(num_PRI_patterns, ab_emlrtDCI);
    }
    pattern_matrix.set_size(static_cast<int>(num_PRI_patterns), num_rows_C_tmp);
    pulsePositionMatrix = static_cast<int>(num_PRI_patterns) * num_rows_C_tmp;
    for (i1 = 0; i1 < pulsePositionMatrix; i1++) {
      pattern_matrix[i1] = 0.0;
    }
    //  loop through columns of C
    for (b_num_PRI_patterns = 0; b_num_PRI_patterns < i5;
         b_num_PRI_patterns++) {
      unsigned int i_col_A;
      //  fill the column (aka fill the elements in the column)
      //  stride is number of elements to repeat in a column
      //  num_strides is number of strides per column
      stride = coder::mpower(
          static_cast<double>(num_members_per_set),
          static_cast<double>(num_rows_C_tmp - b_num_PRI_patterns) - 1.0);
      i_col_A = 0U;
      //  the column in A that we use
      i1 = static_cast<int>(num_PRI_patterns / stride);
      for (i_jitter = 0; i_jitter < i1; i_jitter++) {
        double star;
        i_col_A++;
        if (i_col_A > static_cast<unsigned int>(num_members_per_set)) {
          i_col_A = 1U;
        }
        star = ((static_cast<double>(i_jitter) + 1.0) - 1.0) * stride + 1.0;
        //  column of C gets elements from row of A
        d = (star + stride) - 1.0;
        if (star > d) {
          i2 = 0;
          i4 = 0;
        } else {
          if (star != static_cast<int>(std::floor(star))) {
            rtIntegerError(star, bb_emlrtDCI);
          }
          if ((static_cast<int>(star) < 1) ||
              (static_cast<int>(star) > static_cast<int>(num_PRI_patterns))) {
            rtDynamicBoundsError(static_cast<int>(star), 1,
                                 static_cast<int>(num_PRI_patterns),
                                 ib_emlrtBCI);
          }
          i2 = static_cast<int>(star) - 1;
          if (d != static_cast<int>(std::floor(d))) {
            rtIntegerError(d, cb_emlrtDCI);
          }
          if ((static_cast<int>(d) < 1) ||
              (static_cast<int>(d) > static_cast<int>(num_PRI_patterns))) {
            rtDynamicBoundsError(static_cast<int>(d), 1,
                                 static_cast<int>(num_PRI_patterns),
                                 jb_emlrtBCI);
          }
          i4 = static_cast<int>(d);
        }
        if (b_num_PRI_patterns + 1 > num_rows_C_tmp) {
          rtDynamicBoundsError(b_num_PRI_patterns + 1, 1, num_rows_C_tmp,
                               gb_emlrtBCI);
        }
        pulsePositionMatrix = i4 - i2;
        for (i4 = 0; i4 < pulsePositionMatrix; i4++) {
          if (b_num_PRI_patterns + 1 > num_rows_C_tmp) {
            rtDynamicBoundsError(b_num_PRI_patterns + 1, 1, num_rows_C_tmp,
                                 hb_emlrtBCI);
          }
          if ((static_cast<int>(i_col_A) < 1) ||
              (static_cast<int>(i_col_A) > b_loop_ub)) {
            rtDynamicBoundsError(static_cast<int>(i_col_A), 1, b_loop_ub,
                                 hb_emlrtBCI);
          }
          pattern_matrix[(i2 + i4) +
                         pattern_matrix.size(0) * b_num_PRI_patterns] =
              pulse_position_value[((i3 + b_num_PRI_patterns) +
                                    pulse_position_value.size(0) *
                                        (static_cast<int>(i_col_A) - 1)) +
                                   pulse_position_value.size(0) *
                                       pulse_position_value.size(1) * i_set];
        }
      }
    }
    d = ((static_cast<double>(i_set) + 1.0) - 1.0) * n_rows + 1.0;
    num_PRI_patterns = (static_cast<double>(i_set) + 1.0) * n_rows;
    if (d > num_PRI_patterns) {
      i1 = 0;
      i2 = 0;
    } else {
      if (d != static_cast<int>(std::floor(d))) {
        rtIntegerError(d, db_emlrtDCI);
      }
      if ((static_cast<int>(d) < 1) || (static_cast<int>(d) > result)) {
        rtDynamicBoundsError(static_cast<int>(d), 1,
                             static_cast<int>(num_position_patterns),
                             kb_emlrtBCI);
      }
      i1 = static_cast<int>(d) - 1;
      if (num_PRI_patterns != static_cast<int>(std::floor(num_PRI_patterns))) {
        rtIntegerError(num_PRI_patterns, eb_emlrtDCI);
      }
      if ((static_cast<int>(num_PRI_patterns) < 1) ||
          (static_cast<int>(num_PRI_patterns) > result)) {
        rtDynamicBoundsError(static_cast<int>(num_PRI_patterns), 1,
                             static_cast<int>(num_position_patterns),
                             lb_emlrtBCI);
      }
      i2 = static_cast<int>(num_PRI_patterns);
    }
    pulsePositionMatrix = i2 - i1;
    sizes[0] = pulsePositionMatrix;
    sizes[1] = loop_ub_tmp;
    rtSubAssignSizeCheck(&sizes[0], 2, pattern_matrix.size(), 2, k_emlrtECI);
    for (i2 = 0; i2 < loop_ub_tmp; i2++) {
      for (i4 = 0; i4 < pulsePositionMatrix; i4++) {
        b_pulsePositionMatrix[(i1 + i4) + b_pulsePositionMatrix.size(0) * i2] =
            pattern_matrix[i4 + pulsePositionMatrix * i2];
      }
    }
  }
  if (result != i) {
    rtIntegerError(num_position_patterns, fb_emlrtDCI);
  }
  if ((b_pulsePositionMatrix.size(0) != result) &&
      ((b_pulsePositionMatrix.size(0) != 0) &&
       (b_pulsePositionMatrix.size(1) != 0))) {
    fb_rtErrorWithMessageID(qb_emlrtRTEI.fName, qb_emlrtRTEI.lineNo);
  }
  empty_non_axis_sizes = (result == 0);
  if (empty_non_axis_sizes || (num_position_patterns != 0.0)) {
    input_sizes_idx_1 = 1;
  } else {
    input_sizes_idx_1 = 0;
  }
  if (empty_non_axis_sizes || ((b_pulsePositionMatrix.size(0) != 0) &&
                               (b_pulsePositionMatrix.size(1) != 0))) {
    sizes[1] = loop_ub_tmp;
  } else {
    sizes[1] = 0;
  }
  //  remove duplicate patterns
  pattern_matrix.set_size(result, input_sizes_idx_1 + sizes[1]);
  b_loop_ub = input_sizes_idx_1;
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < result; i1++) {
      pattern_matrix[i1] = 1.0;
    }
  }
  b_loop_ub = sizes[1];
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < result; i1++) {
      pattern_matrix[i1 + pattern_matrix.size(0) * (i + input_sizes_idx_1)] =
          b_pulsePositionMatrix[i1 + result * i];
    }
  }
  coder::unique_rows(pattern_matrix, b_pulsePositionMatrix);
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
    b_priMeansList = priMeansList.reshape(loop_ub);
    num_PRI_patterns = coder::internal::maximum(b_priMeansList);
    // Equivalent to N+M+J-J
  } else {
    b_priMeansList = priMeansList.reshape(loop_ub);
    num_PRI_patterns = coder::internal::maximum(b_priMeansList);
    pulsePositionMatrix = priJtrList.size(1);
    b_priMeansList = priJtrList.reshape(pulsePositionMatrix);
    stride = coder::internal::maximum(b_priMeansList);
    num_PRI_patterns += stride;
    // Equivalent to N+M+J
  }
  // Number of rows in pulse_position_matrix
  // Number of cols in pulse_position_matrix --- should always be K
  coder::repmat(b_pulsePositionMatrix, num_PRI_patterns + 1.0, pattern_matrix);
  // Create multiple copies of the PPM matrix. Each copy will eventually be
  // shifted. The second copy will get a 1 added to it, the third a 2 added, and
  // so on up to n_shifts. Use n_shifts+1 to account for the first one that
  // receives no shifting. Get the number of rows in the big PPM matrix
  if (std::isnan(num_PRI_patterns)) {
    priJtrList.set_size(1, 1);
    priJtrList[0] = rtNaN;
  } else if (num_PRI_patterns < 0.0) {
    priJtrList.set_size(1, 0);
  } else {
    priJtrList.set_size(1, static_cast<int>(num_PRI_patterns) + 1);
    loop_ub = static_cast<int>(num_PRI_patterns);
    for (i = 0; i <= loop_ub; i++) {
      priJtrList[i] = i;
    }
  }
  coder::b_repmat(priJtrList,
                  static_cast<double>(b_pulsePositionMatrix.size(0)),
                  shiftermat);
  // Create a matrix of the shifts needed for each copy of the PPM matrix
  pulsePositionMatrix = shiftermat.size(0) * shiftermat.size(1);
  b_priMeansList = shiftermat.reshape(pulsePositionMatrix);
  coder::repmat(b_priMeansList,
                static_cast<double>(b_pulsePositionMatrix.size(1)), WqRowInds);
  if ((WqRowInds.size(0) != pattern_matrix.size(0)) &&
      ((WqRowInds.size(0) != 1) && (pattern_matrix.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(WqRowInds.size(0), pattern_matrix.size(0),
                                g_emlrtECI);
  }
  if ((WqRowInds.size(1) != pattern_matrix.size(1)) &&
      ((WqRowInds.size(1) != 1) && (pattern_matrix.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(WqRowInds.size(1), pattern_matrix.size(1),
                                l_emlrtECI);
  }
  if ((WqRowInds.size(0) == pattern_matrix.size(0)) &&
      (WqRowInds.size(1) == pattern_matrix.size(1))) {
    loop_ub_tmp = WqRowInds.size(0) * WqRowInds.size(1);
    for (i = 0; i < loop_ub_tmp; i++) {
      WqRowInds[i] = WqRowInds[i] + pattern_matrix[i];
    }
  } else {
    plus(WqRowInds, pattern_matrix);
  }
  if (pattern_matrix.size(0) < 1) {
    priJtrList.set_size(1, 0);
  } else {
    priJtrList.set_size(1, pattern_matrix.size(0));
    loop_ub = pattern_matrix.size(0) - 1;
    for (i = 0; i <= loop_ub; i++) {
      priJtrList[i] = static_cast<double>(i) + 1.0;
    }
  }
  coder::c_repmat(priJtrList,
                  static_cast<double>(b_pulsePositionMatrix.size(1)),
                  priMeansList);
  i_jitter = WqRowInds.size(0) * WqRowInds.size(1);
  b_num_PRI_patterns = priMeansList.size(1);
  pulsePositionMatrix = WqRowInds.size(0) * WqRowInds.size(1);
  r.set_size(pulsePositionMatrix);
  for (i = 0; i < pulsePositionMatrix; i++) {
    r[i] = 1.0;
  }
  b_WqRowInds = WqRowInds.reshape(i_jitter);
  b_priMeansList = priMeansList.reshape(b_num_PRI_patterns);
  coder::i_sparse(b_WqRowInds, b_priMeansList, r, Wq);
}

//
// File trailer for buildtimecorrelatormatrix.cpp
//
// [EOF]
//
