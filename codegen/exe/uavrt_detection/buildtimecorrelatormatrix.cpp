//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: buildtimecorrelatormatrix.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 11-Aug-2023 10:56:49
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
#include <string>

// Function Declarations
static void hb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void hb_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
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
//                coder::sparse &Wq
// Return Type  : void
//
void buildtimecorrelatormatrix(double pri, double priUncert, double priJtr,
                               double reps, coder::sparse &Wq)
{
  static rtBoundsCheckInfo ab_emlrtBCI{
      -1,                              // iFirst
      -1,                              // iLast
      36,                              // lineNo
      23,                              // colNo
      "pulse_position_value",          // aName
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      0         // checkKind
  };
  static rtBoundsCheckInfo bb_emlrtBCI{
      -1,                              // iFirst
      -1,                              // iLast
      42,                              // lineNo
      42,                              // colNo
      "PRI_mean_value",                // aName
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      0         // checkKind
  };
  static rtBoundsCheckInfo cb_emlrtBCI{
      -1,                              // iFirst
      -1,                              // iLast
      42,                              // lineNo
      69,                              // colNo
      "PRI_jitter_value",              // aName
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      0         // checkKind
  };
  static rtBoundsCheckInfo db_emlrtBCI{
      -1,                              // iFirst
      -1,                              // iLast
      41,                              // lineNo
      35,                              // colNo
      "pulse_position_value",          // aName
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      0         // checkKind
  };
  static rtBoundsCheckInfo eb_emlrtBCI{
      -1,                              // iFirst
      -1,                              // iLast
      41,                              // lineNo
      38,                              // colNo
      "pulse_position_value",          // aName
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      0         // checkKind
  };
  static rtBoundsCheckInfo fb_emlrtBCI{
      -1,                              // iFirst
      -1,                              // iLast
      41,                              // lineNo
      48,                              // colNo
      "pulse_position_value",          // aName
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      0         // checkKind
  };
  static rtBoundsCheckInfo gb_emlrtBCI{
      -1,                              // iFirst
      -1,                              // iLast
      71,                              // lineNo
      75,                              // colNo
      "pulse_position_value",          // aName
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      0         // checkKind
  };
  static rtBoundsCheckInfo hb_emlrtBCI{
      -1,                    // iFirst
      -1,                    // iLast
      31,                    // lineNo
      32,                    // colNo
      "C",                   // aName
      "cartesian_prod_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/cartesian_prod_func.m", // pName
      0                                                        // checkKind
  };
  static rtBoundsCheckInfo ib_emlrtBCI{
      -1,                    // iFirst
      -1,                    // iLast
      31,                    // lineNo
      9,                     // colNo
      "A",                   // aName
      "cartesian_prod_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/cartesian_prod_func.m", // pName
      0                                                        // checkKind
  };
  static rtBoundsCheckInfo jb_emlrtBCI{
      -1,                    // iFirst
      -1,                    // iLast
      31,                    // lineNo
      12,                    // colNo
      "C",                   // aName
      "cartesian_prod_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/cartesian_prod_func.m", // pName
      0                                                        // checkKind
  };
  static rtBoundsCheckInfo kb_emlrtBCI{
      -1,                    // iFirst
      -1,                    // iLast
      31,                    // lineNo
      17,                    // colNo
      "C",                   // aName
      "cartesian_prod_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/cartesian_prod_func.m", // pName
      0                                                        // checkKind
  };
  static rtBoundsCheckInfo lb_emlrtBCI{
      -1,                              // iFirst
      -1,                              // iLast
      72,                              // lineNo
      30,                              // colNo
      "pulse_position_matrix",         // aName
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      0         // checkKind
  };
  static rtBoundsCheckInfo mb_emlrtBCI{
      -1,                              // iFirst
      -1,                              // iLast
      72,                              // lineNo
      55,                              // colNo
      "pulse_position_matrix",         // aName
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      0         // checkKind
  };
  static rtBoundsCheckInfo y_emlrtBCI{
      -1,                              // iFirst
      -1,                              // iLast
      31,                              // lineNo
      27,                              // colNo
      "pulse_position_matrix",         // aName
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      0         // checkKind
  };
  static rtDoubleCheckInfo ab_emlrtDCI{
      31,                              // lineNo
      39,                              // colNo
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      1         // checkKind
  };
  static rtDoubleCheckInfo bb_emlrtDCI{
      35,                              // lineNo
      31,                              // colNo
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      1         // checkKind
  };
  static rtDoubleCheckInfo cb_emlrtDCI{
      35,                              // lineNo
      1,                               // colNo
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      1         // checkKind
  };
  static rtDoubleCheckInfo db_emlrtDCI{
      59,                              // lineNo
      32,                              // colNo
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      4         // checkKind
  };
  static rtDoubleCheckInfo eb_emlrtDCI{
      59,                              // lineNo
      32,                              // colNo
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      1         // checkKind
  };
  static rtDoubleCheckInfo fb_emlrtDCI{
      59,                              // lineNo
      55,                              // colNo
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      4         // checkKind
  };
  static rtDoubleCheckInfo gb_emlrtDCI{
      5,            // lineNo
      1,            // colNo
      "assembleWq", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/assembleWq.m", // pName
      1                                               // checkKind
  };
  static rtDoubleCheckInfo hb_emlrtDCI{
      13,                    // lineNo
      12,                    // colNo
      "cartesian_prod_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/cartesian_prod_func.m", // pName
      1                                                        // checkKind
  };
  static rtDoubleCheckInfo ib_emlrtDCI{
      71,                              // lineNo
      5,                               // colNo
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      1         // checkKind
  };
  static rtDoubleCheckInfo jb_emlrtDCI{
      31,                    // lineNo
      12,                    // colNo
      "cartesian_prod_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/cartesian_prod_func.m", // pName
      1                                                        // checkKind
  };
  static rtDoubleCheckInfo kb_emlrtDCI{
      31,                    // lineNo
      17,                    // colNo
      "cartesian_prod_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/cartesian_prod_func.m", // pName
      1                                                        // checkKind
  };
  static rtDoubleCheckInfo lb_emlrtDCI{
      72,                              // lineNo
      30,                              // colNo
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      1         // checkKind
  };
  static rtDoubleCheckInfo mb_emlrtDCI{
      72,                              // lineNo
      55,                              // colNo
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      1         // checkKind
  };
  static rtDoubleCheckInfo nb_emlrtDCI{
      75,                              // lineNo
      20,                              // colNo
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      1         // checkKind
  };
  static rtDoubleCheckInfo
      q_emlrtDCI{
          31,       // lineNo
          14,       // colNo
          "repmat", // fName
          "/Applications/MATLAB_R2023a.app/toolbox/eml/lib/matlab/elmat/"
          "repmat.m", // pName
          4           // checkKind
      };
  static rtDoubleCheckInfo r_emlrtDCI{
      15,                          // lineNo
      24,                          // colNo
      "buildtimecorrelatormatrix", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/buildtimecorrelatormatrix"
      ".m", // pName
      4     // checkKind
  };
  static rtDoubleCheckInfo s_emlrtDCI{
      15,                          // lineNo
      24,                          // colNo
      "buildtimecorrelatormatrix", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/buildtimecorrelatormatrix"
      ".m", // pName
      1     // checkKind
  };
  static rtDoubleCheckInfo t_emlrtDCI{
      16,                          // lineNo
      24,                          // colNo
      "buildtimecorrelatormatrix", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/buildtimecorrelatormatrix"
      ".m", // pName
      4     // checkKind
  };
  static rtDoubleCheckInfo u_emlrtDCI{
      16,                          // lineNo
      24,                          // colNo
      "buildtimecorrelatormatrix", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/buildtimecorrelatormatrix"
      ".m", // pName
      1     // checkKind
  };
  static rtDoubleCheckInfo v_emlrtDCI{
      29,                              // lineNo
      32,                              // colNo
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      4         // checkKind
  };
  static rtDoubleCheckInfo w_emlrtDCI{
      29,                              // lineNo
      32,                              // colNo
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      1         // checkKind
  };
  static rtDoubleCheckInfo x_emlrtDCI{
      29,                              // lineNo
      50,                              // colNo
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      4         // checkKind
  };
  static rtDoubleCheckInfo y_emlrtDCI{
      29,                              // lineNo
      50,                              // colNo
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m", // pName
      1         // checkKind
  };
  static rtEqualityCheckInfo g_emlrtECI{
      -1,                          // nDims
      24,                          // lineNo
      5,                           // colNo
      "buildtimecorrelatormatrix", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/buildtimecorrelatormatrix"
      ".m" // pName
  };
  static rtEqualityCheckInfo h_emlrtECI{
      -1,                          // nDims
      25,                          // lineNo
      5,                           // colNo
      "buildtimecorrelatormatrix", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/buildtimecorrelatormatrix"
      ".m" // pName
  };
  static rtEqualityCheckInfo i_emlrtECI{
      -1,                              // nDims
      31,                              // lineNo
      1,                               // colNo
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m" // pName
  };
  static rtEqualityCheckInfo j_emlrtECI{
      -1,                              // nDims
      72,                              // lineNo
      5,                               // colNo
      "generate_pulse_positions_func", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/generate_pulse_positions_"
      "func.m" // pName
  };
  static rtEqualityCheckInfo k_emlrtECI{
      1,            // nDims
      55,           // lineNo
      15,           // colNo
      "assembleWq", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/assembleWq.m" // pName
  };
  static rtEqualityCheckInfo l_emlrtECI{
      2,            // nDims
      55,           // lineNo
      15,           // colNo
      "assembleWq", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/assembleWq.m" // pName
  };
  static rtRunTimeErrorInfo qc_emlrtRTEI{
      82,         // lineNo
      5,          // colNo
      "fltpower", // fName
      "/Applications/MATLAB_R2023a.app/toolbox/eml/lib/matlab/ops/power.m" // pName
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
  double n_rows;
  double num_PRI_patterns;
  double num_position_patterns;
  double stride;
  int sizes[2];
  int i;
  int i1;
  int i2;
  int i3;
  int i4;
  int i5;
  int iacol;
  int ibcol;
  int ibmat;
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
    rtNonNegativeError(d, r_emlrtDCI);
  }
  if (d != static_cast<int>(std::floor(d))) {
    rtIntegerError(d, s_emlrtDCI);
  }
  num_PRI_patterns = 2.0 * priJtr + 1.0;
  if (!(num_PRI_patterns >= 0.0)) {
    rtNonNegativeError(num_PRI_patterns, t_emlrtDCI);
  }
  if (num_PRI_patterns != static_cast<int>(std::floor(num_PRI_patterns))) {
    rtIntegerError(num_PRI_patterns, u_emlrtDCI);
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
    ibcol = static_cast<int>(priUncert - (-priUncert));
    priJtrList.set_size(1, ibcol + 1);
    for (i = 0; i <= ibcol; i++) {
      priJtrList[i] = -priUncert + static_cast<double>(i);
    }
  } else {
    coder::eml_float_colon(-priUncert, priUncert, priJtrList);
  }
  if (static_cast<int>(d) != priJtrList.size(1)) {
    rtSizeEq1DError(static_cast<int>(d), priJtrList.size(1), g_emlrtECI);
  }
  priMeansList.set_size(1, priJtrList.size(1));
  ibcol = priJtrList.size(1);
  for (i = 0; i < ibcol; i++) {
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
    ibcol = static_cast<int>(priJtr - (-priJtr));
    priJtrList.set_size(1, ibcol + 1);
    for (i = 0; i <= ibcol; i++) {
      priJtrList[i] = -priJtr + static_cast<double>(i);
    }
  } else {
    coder::eml_float_colon(-priJtr, priJtr, priJtrList);
  }
  if (static_cast<int>(num_PRI_patterns) != priJtrList.size(1)) {
    rtSizeEq1DError(static_cast<int>(num_PRI_patterns), priJtrList.size(1),
                    h_emlrtECI);
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
  ntilerows = priJtrList.size(1);
  if ((ntilerows < 0) && (!std::isnan(reps - 1.0)) &&
      (std::floor(reps - 1.0) != reps - 1.0)) {
    hb_rtErrorWithMessageID(qc_emlrtRTEI.fName, qc_emlrtRTEI.lineNo);
  }
  num_PRI_patterns = static_cast<double>(priMeansList.size(1)) *
                     rt_powd_snf(static_cast<double>(ntilerows), reps - 1.0);
  if (!(num_PRI_patterns >= 0.0)) {
    rtNonNegativeError(num_PRI_patterns, v_emlrtDCI);
  }
  i = static_cast<int>(std::floor(num_PRI_patterns));
  if (num_PRI_patterns != i) {
    rtIntegerError(num_PRI_patterns, w_emlrtDCI);
  }
  if (!(reps >= 0.0)) {
    rtNonNegativeError(reps, x_emlrtDCI);
  }
  i1 = static_cast<int>(std::floor(reps));
  if (reps != i1) {
    rtIntegerError(reps, y_emlrtDCI);
  }
  //  place first pulse at pulse position q = 1
  if (reps < 1.0) {
    rtDynamicBoundsError(1, 1, static_cast<int>(reps), y_emlrtBCI);
  }
  nrows = static_cast<int>(num_PRI_patterns);
  if (nrows != i) {
    rtIntegerError(num_PRI_patterns, ab_emlrtDCI);
  }
  rtSubAssignSizeCheck(&nrows, 1, &nrows, 1, i_emlrtECI);
  //  based on the model, generate all the pulse position values in a 3D matrix
  //  pulse_position_value(k, i_position, i_mean )
  i = static_cast<int>(reps);
  if (i != i1) {
    rtIntegerError(reps, bb_emlrtDCI);
  }
  pulse_position_value.set_size(i, priJtrList.size(1), priMeansList.size(1));
  if (i != i1) {
    rtIntegerError(reps, cb_emlrtDCI);
  }
  ibcol = i * priJtrList.size(1) * priMeansList.size(1);
  for (i1 = 0; i1 < ibcol; i1++) {
    pulse_position_value[i1] = 0.0;
  }
  if (reps < 1.0) {
    rtDynamicBoundsError(1, 1, static_cast<int>(reps), ab_emlrtBCI);
  }
  ibcol = priMeansList.size(1);
  for (i1 = 0; i1 < ibcol; i1++) {
    nrows = priJtrList.size(1);
    for (jcol = 0; jcol < nrows; jcol++) {
      pulse_position_value[pulse_position_value.size(0) * jcol +
                           pulse_position_value.size(0) *
                               pulse_position_value.size(1) * i1] = 1.0;
    }
  }
  //  first pulse is always in position 1
  //  loop through the mean PRI values
  i1 = priMeansList.size(1);
  for (nrows = 0; nrows < i1; nrows++) {
    jcol = i - 1;
    for (int k{0}; k < jcol; k++) {
      i2 = priJtrList.size(1);
      for (ntilerows = 0; ntilerows < i2; ntilerows++) {
        if (nrows + 1 > priMeansList.size(1)) {
          rtDynamicBoundsError(nrows + 1, 1, priMeansList.size(1), bb_emlrtBCI);
        }
        if (ntilerows + 1 > priJtrList.size(1)) {
          rtDynamicBoundsError(ntilerows + 1, 1, priJtrList.size(1),
                               cb_emlrtBCI);
        }
        if (static_cast<int>(static_cast<unsigned int>(k) + 2U) >
            pulse_position_value.size(0)) {
          rtDynamicBoundsError(
              static_cast<int>(static_cast<unsigned int>(k) + 2U), 1,
              pulse_position_value.size(0), db_emlrtBCI);
        }
        if (ntilerows + 1 > pulse_position_value.size(1)) {
          rtDynamicBoundsError(ntilerows + 1, 1, pulse_position_value.size(1),
                               eb_emlrtBCI);
        }
        if (nrows + 1 > pulse_position_value.size(2)) {
          rtDynamicBoundsError(nrows + 1, 1, pulse_position_value.size(2),
                               fb_emlrtBCI);
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
  ntilerows = priJtrList.size(1);
  nrows = static_cast<int>(reps) - 1;
  num_position_patterns =
      static_cast<double>(priMeansList.size(1)) *
      rt_powd_snf(static_cast<double>(ntilerows), static_cast<double>(nrows));
  if (!(num_position_patterns >= 0.0)) {
    rtNonNegativeError(num_position_patterns, db_emlrtDCI);
  }
  i = static_cast<int>(std::floor(num_position_patterns));
  if (num_position_patterns != i) {
    rtIntegerError(num_position_patterns, eb_emlrtDCI);
  }
  ncols = static_cast<int>(num_position_patterns);
  pulsePositionMatrix.set_size(ncols, pulsePositionMatrix.size(1));
  if (!(reps - 1.0 >= 0.0)) {
    rtNonNegativeError(reps - 1.0, fb_emlrtDCI);
  }
  pulsePositionMatrix.set_size(pulsePositionMatrix.size(0), nrows);
  if (ncols != i) {
    rtIntegerError(num_position_patterns, gb_emlrtDCI);
  }
  ibcol = ncols * nrows;
  for (i1 = 0; i1 < ibcol; i1++) {
    pulsePositionMatrix[i1] = 0.0;
  }
  ntilerows = priJtrList.size(1);
  n_rows =
      rt_powd_snf(static_cast<double>(ntilerows), static_cast<double>(nrows));
  //  number of rows per PRI mean
  i1 = priMeansList.size(1);
  if (priMeansList.size(1) - 1 >= 0) {
    if (pulse_position_value.size(0) < 2) {
      i3 = 1;
      i4 = 0;
    } else {
      i3 = 2;
      i4 = pulse_position_value.size(0);
    }
    num_members_per_set = pulse_position_value.size(1);
    i5 = i4 - i3;
  }
  for (int i_set{0}; i_set < i1; i_set++) {
    //      % DEBUG
    //      a = [ 1 1 1 ]; b = [ 309 310 311 ]; c = [ 618 619 620 ];
    //      A = [ a; b; c ];
    //  since pattern is "fundamental" pattern starting with a pulse in the
    //  first STFT window, we only need to look at combinations
    //  rows 2:end, and then add the column of ones
    if (i_set + 1 > pulse_position_value.size(2)) {
      rtDynamicBoundsError(i_set + 1, 1, pulse_position_value.size(2),
                           gb_emlrtBCI);
    }
    //    returns the Cartesian product C of the (values in the) rows
    //    of the input matrix A.
    //    Each row of A is taken as a set to draw from
    //    Assumes all sets have the same number of members
    nrows = i4 - i3;
    ntilerows = pulse_position_value.size(1);
    if ((ntilerows < 0) && (static_cast<double>(nrows) + 1.0 !=
                            static_cast<double>(nrows) + 1.0)) {
      hb_rtErrorWithMessageID(qc_emlrtRTEI.fName, qc_emlrtRTEI.lineNo);
    }
    num_PRI_patterns = rt_powd_snf(static_cast<double>(ntilerows),
                                   static_cast<double>(nrows) + 1.0);
    jcol = static_cast<int>(std::floor(num_PRI_patterns));
    if (num_PRI_patterns != jcol) {
      rtIntegerError(num_PRI_patterns, hb_emlrtDCI);
    }
    i2 = static_cast<int>(num_PRI_patterns);
    pattern_matrix.set_size(i2, nrows + 1);
    if (i2 != jcol) {
      rtIntegerError(num_PRI_patterns, ib_emlrtDCI);
    }
    ibcol = i2 * (nrows + 1);
    for (jcol = 0; jcol < ibcol; jcol++) {
      pattern_matrix[jcol] = 0.0;
    }
    //  loop through columns of C
    for (ntilerows = 0; ntilerows <= i5; ntilerows++) {
      unsigned int i_col_A;
      //  fill the column (aka fill the elements in the column)
      //  stride is number of elements to repeat in a column
      //  num_strides is number of strides per column
      stride = rt_powd_snf(static_cast<double>(num_members_per_set),
                           static_cast<double>(nrows - ntilerows));
      i_col_A = 0U;
      //  the column in A that we use
      jcol = static_cast<int>(num_PRI_patterns / stride);
      for (iacol = 0; iacol < jcol; iacol++) {
        double star;
        i_col_A++;
        if (i_col_A > static_cast<unsigned int>(num_members_per_set)) {
          i_col_A = 1U;
        }
        star = ((static_cast<double>(iacol) + 1.0) - 1.0) * stride + 1.0;
        //  column of C gets elements from row of A
        d = (star + stride) - 1.0;
        if (star > d) {
          i2 = 0;
          ibmat = 0;
        } else {
          if (star != static_cast<int>(std::floor(star))) {
            rtIntegerError(star, jb_emlrtDCI);
          }
          if ((static_cast<int>(star) < 1) ||
              (static_cast<int>(star) > pattern_matrix.size(0))) {
            rtDynamicBoundsError(static_cast<int>(star), 1,
                                 pattern_matrix.size(0), jb_emlrtBCI);
          }
          i2 = static_cast<int>(star) - 1;
          if (d != static_cast<int>(std::floor(d))) {
            rtIntegerError(d, kb_emlrtDCI);
          }
          if ((static_cast<int>(d) < 1) ||
              (static_cast<int>(d) > pattern_matrix.size(0))) {
            rtDynamicBoundsError(static_cast<int>(d), 1, pattern_matrix.size(0),
                                 kb_emlrtBCI);
          }
          ibmat = static_cast<int>(d);
        }
        if (ntilerows + 1 > pattern_matrix.size(1)) {
          rtDynamicBoundsError(ntilerows + 1, 1, pattern_matrix.size(1),
                               hb_emlrtBCI);
        }
        ibcol = ibmat - i2;
        for (ibmat = 0; ibmat < ibcol; ibmat++) {
          if (ntilerows + 1 > nrows + 1) {
            rtDynamicBoundsError(ntilerows + 1, 1, nrows + 1, ib_emlrtBCI);
          }
          if ((static_cast<int>(i_col_A) < 1) ||
              (static_cast<int>(i_col_A) > pulse_position_value.size(1))) {
            rtDynamicBoundsError(static_cast<int>(i_col_A), 1,
                                 pulse_position_value.size(1), ib_emlrtBCI);
          }
          pattern_matrix[(i2 + ibmat) + pattern_matrix.size(0) * ntilerows] =
              pulse_position_value[(((i3 + ntilerows) +
                                     pulse_position_value.size(0) *
                                         (static_cast<int>(i_col_A) - 1)) +
                                    pulse_position_value.size(0) *
                                        pulse_position_value.size(1) * i_set) -
                                   1];
        }
      }
    }
    d = ((static_cast<double>(i_set) + 1.0) - 1.0) * n_rows + 1.0;
    num_PRI_patterns = (static_cast<double>(i_set) + 1.0) * n_rows;
    if (d > num_PRI_patterns) {
      jcol = 0;
      i2 = 0;
    } else {
      if (d != static_cast<int>(std::floor(d))) {
        rtIntegerError(d, lb_emlrtDCI);
      }
      if ((static_cast<int>(d) < 1) ||
          (static_cast<int>(d) > pulsePositionMatrix.size(0))) {
        rtDynamicBoundsError(static_cast<int>(d), 1,
                             pulsePositionMatrix.size(0), lb_emlrtBCI);
      }
      jcol = static_cast<int>(d) - 1;
      if (num_PRI_patterns != static_cast<int>(std::floor(num_PRI_patterns))) {
        rtIntegerError(num_PRI_patterns, mb_emlrtDCI);
      }
      if ((static_cast<int>(num_PRI_patterns) < 1) ||
          (static_cast<int>(num_PRI_patterns) > pulsePositionMatrix.size(0))) {
        rtDynamicBoundsError(static_cast<int>(num_PRI_patterns), 1,
                             pulsePositionMatrix.size(0), mb_emlrtBCI);
      }
      i2 = static_cast<int>(num_PRI_patterns);
    }
    sizes[0] = i2 - jcol;
    sizes[1] = pulsePositionMatrix.size(1);
    rtSubAssignSizeCheck(&sizes[0], 2, pattern_matrix.size(), 2, j_emlrtECI);
    ibcol = pattern_matrix.size(1);
    for (i2 = 0; i2 < ibcol; i2++) {
      nrows = pattern_matrix.size(0);
      for (ibmat = 0; ibmat < nrows; ibmat++) {
        pulsePositionMatrix[(jcol + ibmat) + pulsePositionMatrix.size(0) * i2] =
            pattern_matrix[ibmat + pattern_matrix.size(0) * i2];
      }
    }
  }
  if (ncols != i) {
    rtIntegerError(num_position_patterns, nb_emlrtDCI);
  }
  if (num_position_patterns != 0.0) {
    nrows = ncols;
  } else if ((pulsePositionMatrix.size(0) != 0) &&
             (pulsePositionMatrix.size(1) != 0)) {
    nrows = pulsePositionMatrix.size(0);
  } else {
    nrows = ncols;
    if (pulsePositionMatrix.size(0) > ncols) {
      nrows = pulsePositionMatrix.size(0);
    }
  }
  if ((ncols != nrows) && (!(num_position_patterns == 0.0))) {
    cb_rtErrorWithMessageID(ob_emlrtRTEI.fName, ob_emlrtRTEI.lineNo);
  }
  if ((pulsePositionMatrix.size(0) != nrows) &&
      ((pulsePositionMatrix.size(0) != 0) &&
       (pulsePositionMatrix.size(1) != 0))) {
    cb_rtErrorWithMessageID(ob_emlrtRTEI.fName, ob_emlrtRTEI.lineNo);
  }
  empty_non_axis_sizes = (nrows == 0);
  if (empty_non_axis_sizes || (num_position_patterns != 0.0)) {
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
  ibcol = input_sizes_idx_1;
  for (i = 0; i < ibcol; i++) {
    for (i1 = 0; i1 < nrows; i1++) {
      pattern_matrix[i1] = 1.0;
    }
  }
  ibcol = sizes[1];
  for (i = 0; i < ibcol; i++) {
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
    rtNonNegativeError(num_PRI_patterns + 1.0, q_emlrtDCI);
  }
  i = pulsePositionMatrix.size(0) * static_cast<int>(num_PRI_patterns + 1.0);
  pattern_matrix.set_size(i, pulsePositionMatrix.size(1));
  nrows = pulsePositionMatrix.size(0);
  ncols = pulsePositionMatrix.size(1);
  ntilerows = static_cast<int>(num_PRI_patterns + 1.0);
  if (pulsePositionMatrix.size(1) > 2147483646) {
    coder::check_forloop_overflow_error();
  }
  for (jcol = 0; jcol < ncols; jcol++) {
    iacol = jcol * nrows;
    ibmat = jcol * i - 1;
    if (static_cast<int>(num_PRI_patterns + 1.0) > 2147483646) {
      coder::check_forloop_overflow_error();
    }
    for (int i_set{0}; i_set < ntilerows; i_set++) {
      ibcol = ibmat + i_set * nrows;
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
    ibcol = static_cast<int>(num_PRI_patterns);
    for (i = 0; i <= ibcol; i++) {
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
                                k_emlrtECI);
  }
  if ((WqRowInds.size(1) != pattern_matrix.size(1)) &&
      ((WqRowInds.size(1) != 1) && (pattern_matrix.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(WqRowInds.size(1), pattern_matrix.size(1),
                                l_emlrtECI);
  }
  if ((WqRowInds.size(0) == pattern_matrix.size(0)) &&
      (WqRowInds.size(1) == pattern_matrix.size(1))) {
    ibcol = WqRowInds.size(0) * WqRowInds.size(1);
    for (i = 0; i < ibcol; i++) {
      WqRowInds[i] = WqRowInds[i] + pattern_matrix[i];
    }
  } else {
    plus(WqRowInds, pattern_matrix);
  }
  if (pattern_matrix.size(0) < 1) {
    priJtrList.set_size(1, 0);
  } else {
    priJtrList.set_size(1, pattern_matrix.size(0));
    ibcol = pattern_matrix.size(0) - 1;
    for (i = 0; i <= ibcol; i++) {
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
