//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: buildtimecorrelatormatrix.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 18-Feb-2023 14:54:54
//

// Include Files
#include "buildtimecorrelatormatrix.h"
#include "assembleWq.h"
#include "assertValidSizeArg.h"
#include "colon.h"
#include "eml_int_forloop_overflow_check.h"
#include "minOrMax.h"
#include "repmat.h"
#include "rt_nonfinite.h"
#include "sparse.h"
#include "sparse1.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "unique.h"
#include "coder_array.h"
#include "omp.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string.h>
#include <string>

// Function Declarations
static void gb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void gb_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Domain error. To compute complex results, make at least one "
               "input complex, e.g. \'power(complex(a),b)\'.";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

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
  static rtBoundsCheckInfo eb_emlrtBCI{
      -1,                                                            // iFirst
      -1,                                                            // iLast
      31,                                                            // lineNo
      27,                                                            // colNo
      "pulse_position_matrix",                                       // aName
      "generate_pulse_positions_func",                               // fName
      "H:\\repos\\uavrt_detection\\generate_pulse_positions_func.m", // pName
      0 // checkKind
  };
  static rtBoundsCheckInfo fb_emlrtBCI{
      -1,                                                            // iFirst
      -1,                                                            // iLast
      36,                                                            // lineNo
      23,                                                            // colNo
      "pulse_position_value",                                        // aName
      "generate_pulse_positions_func",                               // fName
      "H:\\repos\\uavrt_detection\\generate_pulse_positions_func.m", // pName
      0 // checkKind
  };
  static rtBoundsCheckInfo gb_emlrtBCI{
      -1,                                                            // iFirst
      -1,                                                            // iLast
      42,                                                            // lineNo
      42,                                                            // colNo
      "PRI_mean_value",                                              // aName
      "generate_pulse_positions_func",                               // fName
      "H:\\repos\\uavrt_detection\\generate_pulse_positions_func.m", // pName
      0 // checkKind
  };
  static rtBoundsCheckInfo hb_emlrtBCI{
      -1,                                                            // iFirst
      -1,                                                            // iLast
      42,                                                            // lineNo
      69,                                                            // colNo
      "PRI_jitter_value",                                            // aName
      "generate_pulse_positions_func",                               // fName
      "H:\\repos\\uavrt_detection\\generate_pulse_positions_func.m", // pName
      0 // checkKind
  };
  static rtBoundsCheckInfo ib_emlrtBCI{
      -1,                                                            // iFirst
      -1,                                                            // iLast
      41,                                                            // lineNo
      35,                                                            // colNo
      "pulse_position_value",                                        // aName
      "generate_pulse_positions_func",                               // fName
      "H:\\repos\\uavrt_detection\\generate_pulse_positions_func.m", // pName
      0 // checkKind
  };
  static rtBoundsCheckInfo jb_emlrtBCI{
      -1,                                                            // iFirst
      -1,                                                            // iLast
      41,                                                            // lineNo
      38,                                                            // colNo
      "pulse_position_value",                                        // aName
      "generate_pulse_positions_func",                               // fName
      "H:\\repos\\uavrt_detection\\generate_pulse_positions_func.m", // pName
      0 // checkKind
  };
  static rtBoundsCheckInfo kb_emlrtBCI{
      -1,                                                            // iFirst
      -1,                                                            // iLast
      41,                                                            // lineNo
      48,                                                            // colNo
      "pulse_position_value",                                        // aName
      "generate_pulse_positions_func",                               // fName
      "H:\\repos\\uavrt_detection\\generate_pulse_positions_func.m", // pName
      0 // checkKind
  };
  static rtBoundsCheckInfo lb_emlrtBCI{
      -1,                                                            // iFirst
      -1,                                                            // iLast
      71,                                                            // lineNo
      75,                                                            // colNo
      "pulse_position_value",                                        // aName
      "generate_pulse_positions_func",                               // fName
      "H:\\repos\\uavrt_detection\\generate_pulse_positions_func.m", // pName
      0 // checkKind
  };
  static rtBoundsCheckInfo mb_emlrtBCI{
      -1,                                                  // iFirst
      -1,                                                  // iLast
      31,                                                  // lineNo
      32,                                                  // colNo
      "C",                                                 // aName
      "cartesian_prod_func",                               // fName
      "H:\\repos\\uavrt_detection\\cartesian_prod_func.m", // pName
      0                                                    // checkKind
  };
  static rtBoundsCheckInfo nb_emlrtBCI{
      -1,                                                  // iFirst
      -1,                                                  // iLast
      31,                                                  // lineNo
      9,                                                   // colNo
      "A",                                                 // aName
      "cartesian_prod_func",                               // fName
      "H:\\repos\\uavrt_detection\\cartesian_prod_func.m", // pName
      0                                                    // checkKind
  };
  static rtBoundsCheckInfo ob_emlrtBCI{
      -1,                                                  // iFirst
      -1,                                                  // iLast
      31,                                                  // lineNo
      12,                                                  // colNo
      "C",                                                 // aName
      "cartesian_prod_func",                               // fName
      "H:\\repos\\uavrt_detection\\cartesian_prod_func.m", // pName
      0                                                    // checkKind
  };
  static rtBoundsCheckInfo pb_emlrtBCI{
      -1,                                                  // iFirst
      -1,                                                  // iLast
      31,                                                  // lineNo
      17,                                                  // colNo
      "C",                                                 // aName
      "cartesian_prod_func",                               // fName
      "H:\\repos\\uavrt_detection\\cartesian_prod_func.m", // pName
      0                                                    // checkKind
  };
  static rtBoundsCheckInfo qb_emlrtBCI{
      -1,                                                            // iFirst
      -1,                                                            // iLast
      72,                                                            // lineNo
      30,                                                            // colNo
      "pulse_position_matrix",                                       // aName
      "generate_pulse_positions_func",                               // fName
      "H:\\repos\\uavrt_detection\\generate_pulse_positions_func.m", // pName
      0 // checkKind
  };
  static rtBoundsCheckInfo rb_emlrtBCI{
      -1,                                                            // iFirst
      -1,                                                            // iLast
      72,                                                            // lineNo
      55,                                                            // colNo
      "pulse_position_matrix",                                       // aName
      "generate_pulse_positions_func",                               // fName
      "H:\\repos\\uavrt_detection\\generate_pulse_positions_func.m", // pName
      0 // checkKind
  };
  static rtDoubleCheckInfo ab_emlrtDCI{
      29,                                                            // lineNo
      50,                                                            // colNo
      "generate_pulse_positions_func",                               // fName
      "H:\\repos\\uavrt_detection\\generate_pulse_positions_func.m", // pName
      4 // checkKind
  };
  static rtDoubleCheckInfo bb_emlrtDCI{
      29,                                                            // lineNo
      50,                                                            // colNo
      "generate_pulse_positions_func",                               // fName
      "H:\\repos\\uavrt_detection\\generate_pulse_positions_func.m", // pName
      1 // checkKind
  };
  static rtDoubleCheckInfo cb_emlrtDCI{
      31,                                                            // lineNo
      39,                                                            // colNo
      "generate_pulse_positions_func",                               // fName
      "H:\\repos\\uavrt_detection\\generate_pulse_positions_func.m", // pName
      1 // checkKind
  };
  static rtDoubleCheckInfo db_emlrtDCI{
      35,                                                            // lineNo
      31,                                                            // colNo
      "generate_pulse_positions_func",                               // fName
      "H:\\repos\\uavrt_detection\\generate_pulse_positions_func.m", // pName
      1 // checkKind
  };
  static rtDoubleCheckInfo eb_emlrtDCI{
      35,                                                            // lineNo
      1,                                                             // colNo
      "generate_pulse_positions_func",                               // fName
      "H:\\repos\\uavrt_detection\\generate_pulse_positions_func.m", // pName
      1 // checkKind
  };
  static rtDoubleCheckInfo fb_emlrtDCI{
      59,                                                            // lineNo
      32,                                                            // colNo
      "generate_pulse_positions_func",                               // fName
      "H:\\repos\\uavrt_detection\\generate_pulse_positions_func.m", // pName
      4 // checkKind
  };
  static rtDoubleCheckInfo gb_emlrtDCI{
      59,                                                            // lineNo
      32,                                                            // colNo
      "generate_pulse_positions_func",                               // fName
      "H:\\repos\\uavrt_detection\\generate_pulse_positions_func.m", // pName
      1 // checkKind
  };
  static rtDoubleCheckInfo hb_emlrtDCI{
      5,                                          // lineNo
      1,                                          // colNo
      "assembleWq",                               // fName
      "H:\\repos\\uavrt_detection\\assembleWq.m", // pName
      1                                           // checkKind
  };
  static rtDoubleCheckInfo ib_emlrtDCI{
      13,                                                  // lineNo
      12,                                                  // colNo
      "cartesian_prod_func",                               // fName
      "H:\\repos\\uavrt_detection\\cartesian_prod_func.m", // pName
      1                                                    // checkKind
  };
  static rtDoubleCheckInfo jb_emlrtDCI{
      71,                                                            // lineNo
      5,                                                             // colNo
      "generate_pulse_positions_func",                               // fName
      "H:\\repos\\uavrt_detection\\generate_pulse_positions_func.m", // pName
      1 // checkKind
  };
  static rtDoubleCheckInfo kb_emlrtDCI{
      31,                                                  // lineNo
      12,                                                  // colNo
      "cartesian_prod_func",                               // fName
      "H:\\repos\\uavrt_detection\\cartesian_prod_func.m", // pName
      1                                                    // checkKind
  };
  static rtDoubleCheckInfo lb_emlrtDCI{
      31,                                                  // lineNo
      17,                                                  // colNo
      "cartesian_prod_func",                               // fName
      "H:\\repos\\uavrt_detection\\cartesian_prod_func.m", // pName
      1                                                    // checkKind
  };
  static rtDoubleCheckInfo mb_emlrtDCI{
      72,                                                            // lineNo
      30,                                                            // colNo
      "generate_pulse_positions_func",                               // fName
      "H:\\repos\\uavrt_detection\\generate_pulse_positions_func.m", // pName
      1 // checkKind
  };
  static rtDoubleCheckInfo nb_emlrtDCI{
      72,                                                            // lineNo
      55,                                                            // colNo
      "generate_pulse_positions_func",                               // fName
      "H:\\repos\\uavrt_detection\\generate_pulse_positions_func.m", // pName
      1 // checkKind
  };
  static rtDoubleCheckInfo ob_emlrtDCI{
      75,                                                            // lineNo
      20,                                                            // colNo
      "generate_pulse_positions_func",                               // fName
      "H:\\repos\\uavrt_detection\\generate_pulse_positions_func.m", // pName
      1 // checkKind
  };
  static rtDoubleCheckInfo t_emlrtDCI{
      15,                                                        // lineNo
      24,                                                        // colNo
      "buildtimecorrelatormatrix",                               // fName
      "H:\\repos\\uavrt_detection\\buildtimecorrelatormatrix.m", // pName
      4                                                          // checkKind
  };
  static rtDoubleCheckInfo u_emlrtDCI{
      15,                                                        // lineNo
      24,                                                        // colNo
      "buildtimecorrelatormatrix",                               // fName
      "H:\\repos\\uavrt_detection\\buildtimecorrelatormatrix.m", // pName
      1                                                          // checkKind
  };
  static rtDoubleCheckInfo v_emlrtDCI{
      16,                                                        // lineNo
      24,                                                        // colNo
      "buildtimecorrelatormatrix",                               // fName
      "H:\\repos\\uavrt_detection\\buildtimecorrelatormatrix.m", // pName
      4                                                          // checkKind
  };
  static rtDoubleCheckInfo w_emlrtDCI{
      16,                                                        // lineNo
      24,                                                        // colNo
      "buildtimecorrelatormatrix",                               // fName
      "H:\\repos\\uavrt_detection\\buildtimecorrelatormatrix.m", // pName
      1                                                          // checkKind
  };
  static rtDoubleCheckInfo x_emlrtDCI{
      29,                                                            // lineNo
      32,                                                            // colNo
      "generate_pulse_positions_func",                               // fName
      "H:\\repos\\uavrt_detection\\generate_pulse_positions_func.m", // pName
      4 // checkKind
  };
  static rtDoubleCheckInfo y_emlrtDCI{
      29,                                                            // lineNo
      32,                                                            // colNo
      "generate_pulse_positions_func",                               // fName
      "H:\\repos\\uavrt_detection\\generate_pulse_positions_func.m", // pName
      1 // checkKind
  };
  static rtEqualityCheckInfo g_emlrtECI{
      1,                                         // nDims
      55,                                        // lineNo
      15,                                        // colNo
      "assembleWq",                              // fName
      "H:\\repos\\uavrt_detection\\assembleWq.m" // pName
  };
  static rtEqualityCheckInfo h_emlrtECI{
      -1,                                                       // nDims
      24,                                                       // lineNo
      5,                                                        // colNo
      "buildtimecorrelatormatrix",                              // fName
      "H:\\repos\\uavrt_detection\\buildtimecorrelatormatrix.m" // pName
  };
  static rtEqualityCheckInfo i_emlrtECI{
      -1,                                                       // nDims
      25,                                                       // lineNo
      5,                                                        // colNo
      "buildtimecorrelatormatrix",                              // fName
      "H:\\repos\\uavrt_detection\\buildtimecorrelatormatrix.m" // pName
  };
  static rtEqualityCheckInfo j_emlrtECI{
      -1,                                                           // nDims
      31,                                                           // lineNo
      1,                                                            // colNo
      "generate_pulse_positions_func",                              // fName
      "H:\\repos\\uavrt_detection\\generate_pulse_positions_func.m" // pName
  };
  static rtEqualityCheckInfo k_emlrtECI{
      -1,                                                           // nDims
      72,                                                           // lineNo
      5,                                                            // colNo
      "generate_pulse_positions_func",                              // fName
      "H:\\repos\\uavrt_detection\\generate_pulse_positions_func.m" // pName
  };
  static rtEqualityCheckInfo l_emlrtECI{
      2,                                         // nDims
      55,                                        // lineNo
      15,                                        // colNo
      "assembleWq",                              // fName
      "H:\\repos\\uavrt_detection\\assembleWq.m" // pName
  };
  static rtRunTimeErrorInfo pc_emlrtRTEI{
      82,        // lineNo
      "fltpower" // fName
  };
  coder::array<double, 3U> pulse_position_value;
  coder::array<double, 2U> WqRowInds;
  coder::array<double, 2U> pattern_matrix;
  coder::array<double, 2U> priJtrList;
  coder::array<double, 2U> priMeansList;
  coder::array<double, 2U> pulsePositionMatrix;
  coder::array<double, 2U> shiftermat;
  coder::array<double, 1U> b_WqRowInds;
  coder::array<double, 1U> b_priMeansList;
  coder::array<double, 1U> r;
  double d;
  double d1;
  double n_rows;
  double num_PRI_patterns;
  double num_position_patterns;
  double stride;
  int sizes[2];
  int a;
  int i;
  int i1;
  int i2;
  int i3;
  int iacol;
  int ibcol;
  int ibmat;
  int itilerow;
  int jcol;
  int ncols;
  int nrows;
  int ntilerows;
  int num_members_per_set;
  signed char input_sizes_idx_1;
  boolean_T empty_non_axis_sizes;
  // First check to make sure all inputs contain the same number of
  // elements
  d = 2.0 * priUncert + 1.0;
  if (!(d >= 0.0)) {
    rtNonNegativeError(d, &t_emlrtDCI);
  }
  if (d != static_cast<int>(std::floor(d))) {
    rtIntegerError(d, &u_emlrtDCI);
  }
  d1 = 2.0 * priJtr + 1.0;
  if (!(d1 >= 0.0)) {
    rtNonNegativeError(d1, &v_emlrtDCI);
  }
  if (d1 != static_cast<int>(std::floor(d1))) {
    rtIntegerError(d1, &w_emlrtDCI);
  }
  // Change names to align with other code.
  if (std::isnan(-priUncert) || std::isnan(priUncert)) {
    priJtrList.set_size(1, 1);
    priJtrList[0] = rtNaN;
  } else if (priUncert < -priUncert) {
    priJtrList.set_size(1, 0);
  } else if ((std::isinf(-priUncert) || std::isinf(priUncert)) &&
             (-priUncert == priUncert)) {
    priJtrList.set_size(1, 1);
    priJtrList[0] = rtNaN;
  } else if (std::floor(-priUncert) == -priUncert) {
    ibmat = static_cast<int>(priUncert - (-priUncert));
    priJtrList.set_size(1, ibmat + 1);
    for (i = 0; i <= ibmat; i++) {
      priJtrList[i] = -priUncert + static_cast<double>(i);
    }
  } else {
    coder::eml_float_colon(-priUncert, priUncert, priJtrList);
  }
  if (static_cast<int>(d) != priJtrList.size(1)) {
    rtSizeEq1DError(static_cast<int>(d), priJtrList.size(1), &h_emlrtECI);
  }
  priMeansList.set_size(1, priJtrList.size(1));
  ibmat = priJtrList.size(1);
  for (i = 0; i < ibmat; i++) {
    priMeansList[i] = pri + priJtrList[i];
  }
  if (std::isnan(-priJtr) || std::isnan(priJtr)) {
    priJtrList.set_size(1, 1);
    priJtrList[0] = rtNaN;
  } else if (priJtr < -priJtr) {
    priJtrList.set_size(1, 0);
  } else if ((std::isinf(-priJtr) || std::isinf(priJtr)) &&
             (-priJtr == priJtr)) {
    priJtrList.set_size(1, 1);
    priJtrList[0] = rtNaN;
  } else if (std::floor(-priJtr) == -priJtr) {
    ibmat = static_cast<int>(priJtr - (-priJtr));
    priJtrList.set_size(1, ibmat + 1);
    for (i = 0; i <= ibmat; i++) {
      priJtrList[i] = -priJtr + static_cast<double>(i);
    }
  } else {
    coder::eml_float_colon(-priJtr, priJtr, priJtrList);
  }
  if (static_cast<int>(d1) != priJtrList.size(1)) {
    rtSizeEq1DError(static_cast<int>(d1), priJtrList.size(1), &i_emlrtECI);
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
  nrows = priJtrList.size(1);
  if ((nrows < 0) && (!std::isnan(reps - 1.0)) &&
      (std::floor(reps - 1.0) != reps - 1.0)) {
    gb_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
  }
  num_PRI_patterns = static_cast<double>(priMeansList.size(1)) *
                     rt_powd_snf(static_cast<double>(nrows), reps - 1.0);
  if (!(num_PRI_patterns >= 0.0)) {
    rtNonNegativeError(num_PRI_patterns, &x_emlrtDCI);
  }
  d = static_cast<int>(std::floor(num_PRI_patterns));
  if (num_PRI_patterns != d) {
    rtIntegerError(num_PRI_patterns, &y_emlrtDCI);
  }
  if (!(reps >= 0.0)) {
    rtNonNegativeError(reps, &ab_emlrtDCI);
  }
  i = static_cast<int>(std::floor(reps));
  if (reps != i) {
    rtIntegerError(reps, &bb_emlrtDCI);
  }
  //  place first pulse at pulse position q = 1
  if (static_cast<int>(reps) < 1) {
    rtDynamicBoundsError(1, 1, static_cast<int>(reps), &eb_emlrtBCI);
  }
  if (num_PRI_patterns != d) {
    rtIntegerError(num_PRI_patterns, &cb_emlrtDCI);
  }
  nrows = static_cast<int>(num_PRI_patterns);
  rtSubAssignSizeCheck(&nrows, 1, &nrows, 1, &j_emlrtECI);
  //  based on the model, generate all the pulse position values in a 3D matrix
  //  pulse_position_value(k, i_position, i_mean )
  if (reps != i) {
    rtIntegerError(reps, &db_emlrtDCI);
  }
  i1 = static_cast<int>(reps);
  pulse_position_value.set_size(i1, priJtrList.size(1), priMeansList.size(1));
  if (i1 != i) {
    rtIntegerError(reps, &eb_emlrtDCI);
  }
  ibmat = i1 * priJtrList.size(1) * priMeansList.size(1);
  for (i = 0; i < ibmat; i++) {
    pulse_position_value[i] = 0.0;
  }
  if (reps < 1.0) {
    rtDynamicBoundsError(1, 1, 0, &fb_emlrtBCI);
  }
  ibmat = priMeansList.size(1);
  for (i = 0; i < ibmat; i++) {
    nrows = priJtrList.size(1);
    for (itilerow = 0; itilerow < nrows; itilerow++) {
      pulse_position_value[pulse_position_value.size(0) * itilerow +
                           pulse_position_value.size(0) *
                               pulse_position_value.size(1) * i] = 1.0;
    }
  }
  //  first pulse is always in position 1
  //  loop through the mean PRI values
  i = priMeansList.size(1);
  for (nrows = 0; nrows < i; nrows++) {
    itilerow = i1 + -1;
    for (int k{0}; k < itilerow; k++) {
      ncols = priJtrList.size(1);
      for (ntilerows = 0; ntilerows < ncols; ntilerows++) {
        if (nrows + 1 > priMeansList.size(1)) {
          rtDynamicBoundsError(nrows + 1, 1, priMeansList.size(1),
                               &gb_emlrtBCI);
        }
        if (ntilerows + 1 > priJtrList.size(1)) {
          rtDynamicBoundsError(ntilerows + 1, 1, priJtrList.size(1),
                               &hb_emlrtBCI);
        }
        if (static_cast<int>(k + 2U) > pulse_position_value.size(0)) {
          rtDynamicBoundsError(static_cast<int>(k + 2U), 1,
                               pulse_position_value.size(0), &ib_emlrtBCI);
        }
        if (ntilerows + 1 > pulse_position_value.size(1)) {
          rtDynamicBoundsError(ntilerows + 1, 1, pulse_position_value.size(1),
                               &jb_emlrtBCI);
        }
        if (nrows + 1 > pulse_position_value.size(2)) {
          rtDynamicBoundsError(nrows + 1, 1, pulse_position_value.size(2),
                               &kb_emlrtBCI);
        }
        pulse_position_value[((k + pulse_position_value.size(0) * ntilerows) +
                              pulse_position_value.size(0) *
                                  pulse_position_value.size(1) * nrows) +
                             1] =
            (((static_cast<double>(k) + 2.0) - 1.0) * priMeansList[nrows] +
             1.0) +
            priJtrList[ntilerows];
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
  nrows = priJtrList.size(1);
  ntilerows = i1 - 1;
  num_position_patterns =
      static_cast<double>(priMeansList.size(1)) *
      rt_powd_snf(static_cast<double>(nrows), static_cast<double>(i1 - 1));
  if (!(num_position_patterns >= 0.0)) {
    rtNonNegativeError(num_position_patterns, &fb_emlrtDCI);
  }
  d = static_cast<int>(std::floor(num_position_patterns));
  if (num_position_patterns != d) {
    rtIntegerError(num_position_patterns, &gb_emlrtDCI);
  }
  pulsePositionMatrix.set_size(static_cast<int>(num_position_patterns),
                               pulsePositionMatrix.size(1));
  pulsePositionMatrix.set_size(pulsePositionMatrix.size(0), ntilerows);
  if (num_position_patterns != d) {
    rtIntegerError(num_position_patterns, &hb_emlrtDCI);
  }
  ibmat = static_cast<int>(num_position_patterns) * (i1 - 1);
  for (i = 0; i < ibmat; i++) {
    pulsePositionMatrix[i] = 0.0;
  }
  nrows = priJtrList.size(1);
  n_rows = rt_powd_snf(static_cast<double>(nrows), static_cast<double>(i1 - 1));
  //  number of rows per PRI mean
  i = priMeansList.size(1);
  if (priMeansList.size(1) - 1 >= 0) {
    if (pulse_position_value.size(0) < 2) {
      jcol = -1;
      i2 = -1;
    } else {
      jcol = 0;
      i2 = pulse_position_value.size(0) - 1;
    }
    num_members_per_set = pulse_position_value.size(1);
    a = pulse_position_value.size(1);
    i3 = (i2 - jcol) - 1;
  }
  for (ibcol = 0; ibcol < i; ibcol++) {
    //      % DEBUG
    //      a = [ 1 1 1 ]; b = [ 309 310 311 ]; c = [ 618 619 620 ];
    //      A = [ a; b; c ];
    //  since pattern is "fundamental" pattern starting with a pulse in the
    //  first STFT window, we only need to look at combinations
    //  rows 2:end, and then add the column of ones
    if (ibcol + 1 > pulse_position_value.size(2)) {
      rtDynamicBoundsError(ibcol + 1, 1, pulse_position_value.size(2),
                           &lb_emlrtBCI);
    }
    //    returns the Cartesian product C of the (values in the) rows
    //    of the input matrix A.
    //    Each row of A is taken as a set to draw from
    //    Assumes all sets have the same number of members
    num_PRI_patterns =
        rt_powd_snf(static_cast<double>(a), static_cast<double>(i2 - jcol));
    i1 = static_cast<int>(std::floor(num_PRI_patterns));
    if (num_PRI_patterns != i1) {
      rtIntegerError(num_PRI_patterns, &ib_emlrtDCI);
    }
    itilerow = i2 - jcol;
    ncols = static_cast<int>(num_PRI_patterns);
    pattern_matrix.set_size(ncols, itilerow);
    if (ncols != i1) {
      rtIntegerError(num_PRI_patterns, &jb_emlrtDCI);
    }
    ibmat = ncols * itilerow;
    for (i1 = 0; i1 < ibmat; i1++) {
      pattern_matrix[i1] = 0.0;
    }
    //  loop through columns of C
    for (nrows = 0; nrows <= i3; nrows++) {
      unsigned int i_col_A;
      //  fill the column (aka fill the elements in the column)
      //  stride is number of elements to repeat in a column
      //  num_strides is number of strides per column
      ntilerows = i2 - jcol;
      stride = rt_powd_snf(static_cast<double>(num_members_per_set),
                           static_cast<double>((ntilerows - nrows) - 1));
      i_col_A = 0U;
      //  the column in A that we use
      i1 = static_cast<int>(num_PRI_patterns / stride);
      for (iacol = 0; iacol < i1; iacol++) {
        double star;
        i_col_A++;
        if (i_col_A > static_cast<unsigned int>(num_members_per_set)) {
          i_col_A = 1U;
        }
        star = ((static_cast<double>(iacol) + 1.0) - 1.0) * stride + 1.0;
        //  column of C gets elements from row of A
        d1 = (star + stride) - 1.0;
        if (star > d1) {
          itilerow = 0;
          ncols = 0;
        } else {
          if (star != static_cast<int>(std::floor(star))) {
            rtIntegerError(star, &kb_emlrtDCI);
          }
          if ((static_cast<int>(star) < 1) ||
              (static_cast<int>(star) > pattern_matrix.size(0))) {
            rtDynamicBoundsError(static_cast<int>(star), 1,
                                 pattern_matrix.size(0), &ob_emlrtBCI);
          }
          itilerow = static_cast<int>(star) - 1;
          if (d1 != static_cast<int>(std::floor(d1))) {
            rtIntegerError(d1, &lb_emlrtDCI);
          }
          if ((static_cast<int>(d1) < 1) ||
              (static_cast<int>(d1) > pattern_matrix.size(0))) {
            rtDynamicBoundsError(static_cast<int>(d1), 1,
                                 pattern_matrix.size(0), &pb_emlrtBCI);
          }
          ncols = static_cast<int>(d1);
        }
        if (nrows + 1 > pattern_matrix.size(1)) {
          rtDynamicBoundsError(nrows + 1, 1, pattern_matrix.size(1),
                               &mb_emlrtBCI);
        }
        ibmat = ncols - itilerow;
        for (ncols = 0; ncols < ibmat; ncols++) {
          if (nrows + 1 > ntilerows) {
            rtDynamicBoundsError(nrows + 1, 1, ntilerows, &nb_emlrtBCI);
          }
          if ((static_cast<int>(i_col_A) < 1) ||
              (static_cast<int>(i_col_A) > pulse_position_value.size(1))) {
            rtDynamicBoundsError(static_cast<int>(i_col_A), 1,
                                 pulse_position_value.size(1), &nb_emlrtBCI);
          }
          pattern_matrix[(itilerow + ncols) + pattern_matrix.size(0) * nrows] =
              pulse_position_value[(((jcol + nrows) +
                                     pulse_position_value.size(0) *
                                         (static_cast<int>(i_col_A) - 1)) +
                                    pulse_position_value.size(0) *
                                        pulse_position_value.size(1) * ibcol) +
                                   1];
        }
      }
    }
    d1 = ((static_cast<double>(ibcol) + 1.0) - 1.0) * n_rows + 1.0;
    num_PRI_patterns = (static_cast<double>(ibcol) + 1.0) * n_rows;
    if (d1 > num_PRI_patterns) {
      i1 = 0;
      itilerow = 0;
    } else {
      if (d1 != static_cast<int>(std::floor(d1))) {
        rtIntegerError(d1, &mb_emlrtDCI);
      }
      if ((static_cast<int>(d1) < 1) ||
          (static_cast<int>(d1) > pulsePositionMatrix.size(0))) {
        rtDynamicBoundsError(static_cast<int>(d1), 1,
                             pulsePositionMatrix.size(0), &qb_emlrtBCI);
      }
      i1 = static_cast<int>(d1) - 1;
      if (num_PRI_patterns != static_cast<int>(std::floor(num_PRI_patterns))) {
        rtIntegerError(num_PRI_patterns, &nb_emlrtDCI);
      }
      if ((static_cast<int>(num_PRI_patterns) < 1) ||
          (static_cast<int>(num_PRI_patterns) > pulsePositionMatrix.size(0))) {
        rtDynamicBoundsError(static_cast<int>(num_PRI_patterns), 1,
                             pulsePositionMatrix.size(0), &rb_emlrtBCI);
      }
      itilerow = static_cast<int>(num_PRI_patterns);
    }
    sizes[0] = itilerow - i1;
    sizes[1] = pulsePositionMatrix.size(1);
    rtSubAssignSizeCheck(&sizes[0], 2, pattern_matrix.size(), 2, &k_emlrtECI);
    ibmat = pattern_matrix.size(1);
    for (itilerow = 0; itilerow < ibmat; itilerow++) {
      nrows = pattern_matrix.size(0);
      for (ncols = 0; ncols < nrows; ncols++) {
        pulsePositionMatrix[(i1 + ncols) +
                            pulsePositionMatrix.size(0) * itilerow] =
            pattern_matrix[ncols + pattern_matrix.size(0) * itilerow];
      }
    }
  }
  if (num_position_patterns != d) {
    rtIntegerError(num_position_patterns, &ob_emlrtDCI);
  }
  if (static_cast<int>(num_position_patterns) != 0) {
    nrows = static_cast<int>(num_position_patterns);
  } else if ((pulsePositionMatrix.size(0) != 0) &&
             (pulsePositionMatrix.size(1) != 0)) {
    nrows = pulsePositionMatrix.size(0);
  } else {
    nrows = static_cast<int>(num_position_patterns);
    if (pulsePositionMatrix.size(0) > nrows) {
      nrows = pulsePositionMatrix.size(0);
    }
  }
  if ((static_cast<int>(num_position_patterns) != nrows) &&
      (static_cast<int>(num_position_patterns) != 0)) {
    fb_rtErrorWithMessageID(vb_emlrtRTEI.fName, vb_emlrtRTEI.lineNo);
  }
  if ((pulsePositionMatrix.size(0) != nrows) &&
      ((pulsePositionMatrix.size(0) != 0) &&
       (pulsePositionMatrix.size(1) != 0))) {
    fb_rtErrorWithMessageID(vb_emlrtRTEI.fName, vb_emlrtRTEI.lineNo);
  }
  empty_non_axis_sizes = (nrows == 0);
  if (empty_non_axis_sizes || (static_cast<int>(num_position_patterns) != 0)) {
    input_sizes_idx_1 = 1;
  } else {
    input_sizes_idx_1 = 0;
  }
  if (empty_non_axis_sizes || ((pulsePositionMatrix.size(0) != 0) &&
                               (pulsePositionMatrix.size(1) != 0))) {
    sizes[1] = pulsePositionMatrix.size(1);
  } else {
    sizes[1] = 0;
  }
  //  remove duplicate patterns
  pattern_matrix.set_size(nrows, input_sizes_idx_1 + sizes[1]);
  ibmat = input_sizes_idx_1;
  for (i = 0; i < ibmat; i++) {
    for (i1 = 0; i1 < nrows; i1++) {
      pattern_matrix[i1] = 1.0;
    }
  }
  ibmat = sizes[1];
  for (i = 0; i < ibmat; i++) {
    for (i1 = 0; i1 < nrows; i1++) {
      pattern_matrix[i1 + pattern_matrix.size(0) * (i + input_sizes_idx_1)] =
          pulsePositionMatrix[i1 + nrows * i];
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
    ntilerows = priMeansList.size(1);
    b_priMeansList = priMeansList.reshape(ntilerows);
    num_PRI_patterns = coder::internal::maximum(b_priMeansList);
    // Equivalent to N+M+J-J
  } else {
    ntilerows = priMeansList.size(1);
    b_priMeansList = priMeansList.reshape(ntilerows);
    num_PRI_patterns = coder::internal::maximum(b_priMeansList);
    nrows = priJtrList.size(1);
    b_priMeansList = priJtrList.reshape(nrows);
    stride = coder::internal::maximum(b_priMeansList);
    num_PRI_patterns += stride;
    // Equivalent to N+M+J
  }
  // Number of rows in pulse_position_matrix
  // Number of cols in pulse_position_matrix --- should always be K
  coder::internal::assertValidSizeArg(num_PRI_patterns + 1.0);
  if (!(num_PRI_patterns + 1.0 >= 0.0)) {
    rtNonNegativeError(num_PRI_patterns + 1.0, &n_emlrtDCI);
  }
  pattern_matrix.set_size(pulsePositionMatrix.size(0) *
                              static_cast<int>(num_PRI_patterns + 1.0),
                          pulsePositionMatrix.size(1));
  nrows = pulsePositionMatrix.size(0);
  ncols = pulsePositionMatrix.size(1);
  ntilerows = static_cast<int>(num_PRI_patterns + 1.0);
  if (pulsePositionMatrix.size(1) > 2147483646) {
    coder::check_forloop_overflow_error();
  }
  for (jcol = 0; jcol < ncols; jcol++) {
    iacol = jcol * nrows;
    ibmat = jcol * (nrows * static_cast<int>(num_PRI_patterns + 1.0)) - 1;
    if (static_cast<int>(num_PRI_patterns + 1.0) > 2147483646) {
      coder::check_forloop_overflow_error();
    }
    for (itilerow = 0; itilerow < ntilerows; itilerow++) {
      ibcol = ibmat + itilerow * nrows;
      if (nrows > 2147483646) {
        coder::check_forloop_overflow_error();
      }
      for (int k{0}; k < nrows; k++) {
        pattern_matrix[(ibcol + k) + 1] = pulsePositionMatrix[iacol + k];
      }
    }
  }
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
    ibmat = static_cast<int>(num_PRI_patterns);
    for (i = 0; i <= ibmat; i++) {
      priJtrList[i] = i;
    }
  }
  coder::repmat(priJtrList, static_cast<double>(pulsePositionMatrix.size(0)),
                shiftermat);
  // Create a matrix of the shifts needed for each copy of the PPM matrix
  nrows = shiftermat.size(0) * shiftermat.size(1);
  b_priMeansList = shiftermat.reshape(nrows);
  coder::repmat(b_priMeansList,
                static_cast<double>(pulsePositionMatrix.size(1)), WqRowInds);
  if ((WqRowInds.size(0) != pattern_matrix.size(0)) &&
      ((WqRowInds.size(0) != 1) && (pattern_matrix.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(WqRowInds.size(0), pattern_matrix.size(0),
                                &g_emlrtECI);
  }
  if ((WqRowInds.size(1) != pattern_matrix.size(1)) &&
      ((WqRowInds.size(1) != 1) && (pattern_matrix.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(WqRowInds.size(1), pattern_matrix.size(1),
                                &l_emlrtECI);
  }
  if ((WqRowInds.size(0) == pattern_matrix.size(0)) &&
      (WqRowInds.size(1) == pattern_matrix.size(1))) {
    ibmat = WqRowInds.size(0) * WqRowInds.size(1);
    for (i = 0; i < ibmat; i++) {
      WqRowInds[i] = WqRowInds[i] + pattern_matrix[i];
    }
  } else {
    plus(WqRowInds, pattern_matrix);
  }
  if (pattern_matrix.size(0) < 1) {
    priJtrList.set_size(1, 0);
  } else {
    priJtrList.set_size(1, pattern_matrix.size(0));
    ibmat = pattern_matrix.size(0) - 1;
    for (i = 0; i <= ibmat; i++) {
      priJtrList[i] = static_cast<double>(i) + 1.0;
    }
  }
  coder::internal::assertValidSizeArg(
      static_cast<double>(pulsePositionMatrix.size(1)));
  priMeansList.set_size(1, priJtrList.size(1) * pulsePositionMatrix.size(1));
  ncols = priJtrList.size(1);
  nrows = pulsePositionMatrix.size(1);
  for (iacol = 0; iacol < nrows; iacol++) {
    ntilerows = iacol * ncols;
    if (ncols > 2147483646) {
      coder::check_forloop_overflow_error();
    }
    for (jcol = 0; jcol < ncols; jcol++) {
      priMeansList[ntilerows + jcol] = priJtrList[jcol];
    }
  }
  iacol = WqRowInds.size(0) * WqRowInds.size(1);
  ntilerows = priMeansList.size(1);
  nrows = WqRowInds.size(0) * WqRowInds.size(1);
  r.set_size(nrows);
  for (i = 0; i < nrows; i++) {
    r[i] = 1.0;
  }
  b_WqRowInds = WqRowInds.reshape(iacol);
  b_priMeansList = priMeansList.reshape(ntilerows);
  coder::i_sparse(b_WqRowInds, b_priMeansList, r, Wq);
  // , obj.reps(i));
}

//
// File trailer for buildtimecorrelatormatrix.cpp
//
// [EOF]
//
