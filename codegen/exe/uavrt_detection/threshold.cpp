//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: threshold.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 14:31:55
//

// Include Files
#include "threshold.h"
#include "anonymous_function.h"
#include "assembleWq.h"
#include "colon.h"
#include "find.h"
#include "fzero.h"
#include "indexShapeCheck.h"
#include "repmat.h"
#include "rt_nonfinite.h"
#include "sparse.h"
#include "sparse1.h"
#include "stft.h"
#include "toc.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_internal_types.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "unique.h"
#include "waveform.h"
#include "wfmstft.h"
#include "wgn.h"
#include "coder_array.h"
#include "omp.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <stdio.h>
#include <string.h>
#include <string>

// Function Declarations
static void ib_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void ib_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "If the working dimension of MAX or MIN is variable in length, "
               "it must not have zero length at runtime.";
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
// Arguments    : void
// Return Type  : void
//
void threshold::init()
{
  pf = 0.01;
  evMuParam = 0.0;
  evSigmaParam = 0.0;
  threshVecFine.set_size(1);
  threshVecFine[0] = 0.0;
}

//
// BUILDTHRESHOLD generates a threshold vector for the waveform argument
// based on the false alarm probability input.
//
// This function creates a vector of thresholds for the incoherently summed
// results of the data in the input waveform. The probability of false alarm
// input is used for threshold generation. The output vector is a spectrally
// tuned threshold for each frequency in the STFT of the waveform. These
// thresholds are dependent on the power spectral density for each frequency
// bin, so areas of the spectrum with a high noise floor will have a higher
// output thresholde value
//
// INPUTS:
//    Wfm     A single waveform object
//    PF      A scalar probability of false alarm value (0 1];
// OUTPUTS:
//    newThresh   A vector of threshold with as many elements as rows in the
//                S matrix of the wfmstft object within the Wfm input.
//
// Author:    Michael W. Shafer
// Date:      2022-05-04
// --------------------------------------------------------------------------
//
// Arguments    : const waveform *Wfm
// Return Type  : void
//
void threshold::makenewthreshold(const waveform *Wfm) const
{
  static rtBoundsCheckInfo f_emlrtBCI{
      -1,                                                            // iFirst
      -1,                                                            // iLast
      31,                                                            // lineNo
      27,                                                            // colNo
      "pulse_position_matrix",                                       // aName
      "generate_pulse_positions_func",                               // fName
      "H:\\repos\\uavrt_detection\\generate_pulse_positions_func.m", // pName
      0 // checkKind
  };
  static rtBoundsCheckInfo g_emlrtBCI{
      -1,                                                            // iFirst
      -1,                                                            // iLast
      36,                                                            // lineNo
      23,                                                            // colNo
      "pulse_position_value",                                        // aName
      "generate_pulse_positions_func",                               // fName
      "H:\\repos\\uavrt_detection\\generate_pulse_positions_func.m", // pName
      0 // checkKind
  };
  static rtBoundsCheckInfo h_emlrtBCI{
      -1,                                        // iFirst
      -1,                                        // iLast
      276,                                       // lineNo
      49,                                        // colNo
      "Wfm.stft.f",                              // aName
      "threshold/setthreshprops",                // fName
      "H:\\repos\\uavrt_detection\\threshold.m", // pName
      0                                          // checkKind
  };
  static rtBoundsCheckInfo i_emlrtBCI{
      -1,                                        // iFirst
      -1,                                        // iLast
      276,                                       // lineNo
      63,                                        // colNo
      "Wfm.stft.f",                              // aName
      "threshold/setthreshprops",                // fName
      "H:\\repos\\uavrt_detection\\threshold.m", // pName
      0                                          // checkKind
  };
  static rtBoundsCheckInfo j_emlrtBCI{
      -1,                                        // iFirst
      -1,                                        // iLast
      291,                                       // lineNo
      44,                                        // colNo
      "newThresh",                               // aName
      "threshold/setthreshprops",                // fName
      "H:\\repos\\uavrt_detection\\threshold.m", // pName
      0                                          // checkKind
  };
  static rtBoundsCheckInfo k_emlrtBCI{
      -1,                                        // iFirst
      -1,                                        // iLast
      292,                                       // lineNo
      44,                                        // colNo
      "firstTrueThreshInd",                      // aName
      "threshold/setthreshprops",                // fName
      "H:\\repos\\uavrt_detection\\threshold.m", // pName
      0                                          // checkKind
  };
  static rtDoubleCheckInfo
      b_emlrtDCI{
          31,       // lineNo
          14,       // colNo
          "repmat", // fName
          "C:\\Program "
          "Files\\MATLAB\\toolbox\\eml\\lib\\matlab\\elmat\\repmat.m", // pName
          4 // checkKind
      };
  static rtDoubleCheckInfo c_emlrtDCI{
      16,                                                        // lineNo
      24,                                                        // colNo
      "buildtimecorrelatormatrix",                               // fName
      "H:\\repos\\uavrt_detection\\buildtimecorrelatormatrix.m", // pName
      1                                                          // checkKind
  };
  static rtDoubleCheckInfo d_emlrtDCI{
      15,                                                        // lineNo
      24,                                                        // colNo
      "buildtimecorrelatormatrix",                               // fName
      "H:\\repos\\uavrt_detection\\buildtimecorrelatormatrix.m", // pName
      1                                                          // checkKind
  };
  static rtDoubleCheckInfo e_emlrtDCI{
      15,                                                        // lineNo
      24,                                                        // colNo
      "buildtimecorrelatormatrix",                               // fName
      "H:\\repos\\uavrt_detection\\buildtimecorrelatormatrix.m", // pName
      4                                                          // checkKind
  };
  static rtDoubleCheckInfo f_emlrtDCI{
      16,                                                        // lineNo
      24,                                                        // colNo
      "buildtimecorrelatormatrix",                               // fName
      "H:\\repos\\uavrt_detection\\buildtimecorrelatormatrix.m", // pName
      4                                                          // checkKind
  };
  static rtDoubleCheckInfo g_emlrtDCI{
      29,                                                            // lineNo
      32,                                                            // colNo
      "generate_pulse_positions_func",                               // fName
      "H:\\repos\\uavrt_detection\\generate_pulse_positions_func.m", // pName
      4 // checkKind
  };
  static rtDoubleCheckInfo h_emlrtDCI{
      29,                                                            // lineNo
      32,                                                            // colNo
      "generate_pulse_positions_func",                               // fName
      "H:\\repos\\uavrt_detection\\generate_pulse_positions_func.m", // pName
      1 // checkKind
  };
  static rtDoubleCheckInfo i_emlrtDCI{
      29,                                                            // lineNo
      50,                                                            // colNo
      "generate_pulse_positions_func",                               // fName
      "H:\\repos\\uavrt_detection\\generate_pulse_positions_func.m", // pName
      4 // checkKind
  };
  static rtDoubleCheckInfo j_emlrtDCI{
      29,                                                            // lineNo
      50,                                                            // colNo
      "generate_pulse_positions_func",                               // fName
      "H:\\repos\\uavrt_detection\\generate_pulse_positions_func.m", // pName
      1 // checkKind
  };
  static rtDoubleCheckInfo k_emlrtDCI{
      31,                                                            // lineNo
      39,                                                            // colNo
      "generate_pulse_positions_func",                               // fName
      "H:\\repos\\uavrt_detection\\generate_pulse_positions_func.m", // pName
      1 // checkKind
  };
  static rtDoubleCheckInfo l_emlrtDCI{
      35,                                                            // lineNo
      31,                                                            // colNo
      "generate_pulse_positions_func",                               // fName
      "H:\\repos\\uavrt_detection\\generate_pulse_positions_func.m", // pName
      1 // checkKind
  };
  static rtDoubleCheckInfo m_emlrtDCI{
      59,                                                            // lineNo
      32,                                                            // colNo
      "generate_pulse_positions_func",                               // fName
      "H:\\repos\\uavrt_detection\\generate_pulse_positions_func.m", // pName
      4 // checkKind
  };
  static rtDoubleCheckInfo n_emlrtDCI{
      59,                                                            // lineNo
      32,                                                            // colNo
      "generate_pulse_positions_func",                               // fName
      "H:\\repos\\uavrt_detection\\generate_pulse_positions_func.m", // pName
      1 // checkKind
  };
  static rtDoubleCheckInfo o_emlrtDCI{
      59,                                                            // lineNo
      55,                                                            // colNo
      "generate_pulse_positions_func",                               // fName
      "H:\\repos\\uavrt_detection\\generate_pulse_positions_func.m", // pName
      4 // checkKind
  };
  static rtDoubleCheckInfo p_emlrtDCI{
      59,                                                            // lineNo
      55,                                                            // colNo
      "generate_pulse_positions_func",                               // fName
      "H:\\repos\\uavrt_detection\\generate_pulse_positions_func.m", // pName
      1 // checkKind
  };
  static rtDoubleCheckInfo q_emlrtDCI{
      75,                                                            // lineNo
      20,                                                            // colNo
      "generate_pulse_positions_func",                               // fName
      "H:\\repos\\uavrt_detection\\generate_pulse_positions_func.m", // pName
      1 // checkKind
  };
  static rtEqualityCheckInfo c_emlrtECI{
      -1,                                                       // nDims
      24,                                                       // lineNo
      5,                                                        // colNo
      "buildtimecorrelatormatrix",                              // fName
      "H:\\repos\\uavrt_detection\\buildtimecorrelatormatrix.m" // pName
  };
  static rtEqualityCheckInfo d_emlrtECI{
      -1,                                                       // nDims
      25,                                                       // lineNo
      5,                                                        // colNo
      "buildtimecorrelatormatrix",                              // fName
      "H:\\repos\\uavrt_detection\\buildtimecorrelatormatrix.m" // pName
  };
  static rtEqualityCheckInfo e_emlrtECI{
      -1,                                                           // nDims
      31,                                                           // lineNo
      1,                                                            // colNo
      "generate_pulse_positions_func",                              // fName
      "H:\\repos\\uavrt_detection\\generate_pulse_positions_func.m" // pName
  };
  static rtEqualityCheckInfo f_emlrtECI{
      1,                                         // nDims
      55,                                        // lineNo
      15,                                        // colNo
      "assembleWq",                              // fName
      "H:\\repos\\uavrt_detection\\assembleWq.m" // pName
  };
  static rtEqualityCheckInfo g_emlrtECI{
      2,                                         // nDims
      55,                                        // lineNo
      15,                                        // colNo
      "assembleWq",                              // fName
      "H:\\repos\\uavrt_detection\\assembleWq.m" // pName
  };
  static rtRunTimeErrorInfo kb_emlrtRTEI{
      135,            // lineNo
      "unaryMinOrMax" // fName
  };
  coder::b_anonymous_function theFunc;
  coder::sparse Wq;
  coder::array<double, 2U> r;
  coder::array<double, 1U> r1;
  creal_T xsynth_data[100];
  double WqColInds_data;
  double d;
  double ppmBig_data;
  double previousToc;
  double pri;
  double priJtr;
  double priMeansList_data;
  double reps;
  int WqColInds_size[2];
  int ppmBig_size[2];
  int sizes[2];
  int i;
  int i1;
  int ii_data;
  int k;
  int num_PRI_patterns_tmp;
  int priMeansList_size_idx_1;
  unsigned int stftSz_idx_0;
  unsigned int stftSz_idx_1;
  signed char input_sizes_idx_0;
  signed char input_sizes_idx_1;
  signed char outsize_idx_0_tmp;
  boolean_T empty_non_axis_sizes;
  theFunc.workspace.pf = pf;
  // This will be the reference power for the trials. Thresholds will be
  // interpolated for each bin from this value based on their bin power
  // median(freqBinPow);
  stftSz_idx_0 = static_cast<unsigned int>(Wfm->stft->S.size(0));
  stftSz_idx_1 = static_cast<unsigned int>(Wfm->stft->S.size(1));
  previousToc = coder::toc();
  printf("\n \t Building time correlation matrix ...");
  fflush(stdout);
  // Build the Wq time correlation matrix
  pri = Wfm->N;
  ppmBig_data = Wfm->M;
  priJtr = Wfm->J;
  reps = Wfm->K;
  // UNTITLED Summary of this function goes here
  //    Detailed explanation goes here
  // First check to make sure all inputs contain the same number of
  // elements
  priMeansList_data = 2.0 * ppmBig_data + 1.0;
  if (!(priMeansList_data >= 0.0)) {
    rtNonNegativeError(priMeansList_data, &e_emlrtDCI);
  }
  if (priMeansList_data != static_cast<int>(std::floor(priMeansList_data))) {
    rtIntegerError(priMeansList_data, &d_emlrtDCI);
  }
  d = 2.0 * priJtr + 1.0;
  if (!(d >= 0.0)) {
    rtNonNegativeError(d, &f_emlrtDCI);
  }
  if (d != static_cast<int>(std::floor(d))) {
    rtIntegerError(d, &c_emlrtDCI);
  }
  // Change names to align with other code.
  if (std::isnan(-ppmBig_data) || std::isnan(ppmBig_data)) {
    WqColInds_size[1] = 1;
    WqColInds_data = rtNaN;
  } else if (ppmBig_data < -ppmBig_data) {
    WqColInds_size[1] = 0;
  } else if ((std::isinf(-ppmBig_data) || std::isinf(ppmBig_data)) &&
             (-ppmBig_data == ppmBig_data)) {
    WqColInds_size[1] = 1;
    WqColInds_data = rtNaN;
  } else if (std::floor(-ppmBig_data) == -ppmBig_data) {
    k = static_cast<int>(ppmBig_data - (-ppmBig_data));
    WqColInds_size[1] = k + 1;
    for (i = 0; i <= k; i++) {
      WqColInds_data = -ppmBig_data + static_cast<double>(i);
    }
  } else {
    coder::eml_float_colon(-ppmBig_data, ppmBig_data, (double *)&WqColInds_data,
                           WqColInds_size);
  }
  if (static_cast<int>(priMeansList_data) != WqColInds_size[1]) {
    rtSizeEq1DError(static_cast<int>(priMeansList_data), WqColInds_size[1],
                    &c_emlrtECI);
  }
  priMeansList_size_idx_1 = WqColInds_size[1];
  k = WqColInds_size[1];
  for (i = 0; i < k; i++) {
    priMeansList_data = pri + WqColInds_data;
  }
  if (std::isnan(-priJtr) || std::isnan(priJtr)) {
    WqColInds_size[1] = 1;
    WqColInds_data = rtNaN;
  } else if (priJtr < -priJtr) {
    WqColInds_size[1] = 0;
  } else if ((std::isinf(-priJtr) || std::isinf(priJtr)) &&
             (-priJtr == priJtr)) {
    WqColInds_size[1] = 1;
    WqColInds_data = rtNaN;
  } else if (std::floor(-priJtr) == -priJtr) {
    k = static_cast<int>(priJtr - (-priJtr));
    WqColInds_size[1] = k + 1;
    for (i = 0; i <= k; i++) {
      WqColInds_data = -priJtr + static_cast<double>(i);
    }
  } else {
    coder::eml_float_colon(-priJtr, priJtr, (double *)&WqColInds_data,
                           WqColInds_size);
  }
  if (static_cast<int>(d) != WqColInds_size[1]) {
    rtSizeEq1DError(static_cast<int>(d), WqColInds_size[1], &d_emlrtECI);
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
  ppmBig_data = static_cast<double>(priMeansList_size_idx_1) *
                rt_powd_snf(static_cast<double>(WqColInds_size[1]), reps - 1.0);
  if (!(ppmBig_data >= 0.0)) {
    rtNonNegativeError(rtNaN, &g_emlrtDCI);
  }
  i = static_cast<int>(std::floor(ppmBig_data));
  if (ppmBig_data != i) {
    rtIntegerError(ppmBig_data, &h_emlrtDCI);
  }
  if (!(reps >= 0.0)) {
    rtNonNegativeError(reps, &i_emlrtDCI);
  }
  i1 = static_cast<int>(std::floor(reps));
  if (reps != i1) {
    rtIntegerError(reps, &j_emlrtDCI);
  }
  //  place first pulse at pulse position q = 1
  if (reps < 1.0) {
    rtDynamicBoundsError(1, 1, static_cast<int>(reps), &f_emlrtBCI);
  }
  num_PRI_patterns_tmp = static_cast<int>(ppmBig_data);
  if (num_PRI_patterns_tmp != i) {
    rtIntegerError(ppmBig_data, &k_emlrtDCI);
  }
  rtSubAssignSizeCheck(&num_PRI_patterns_tmp, 1, &num_PRI_patterns_tmp, 1,
                       &e_emlrtECI);
  //  based on the model, generate all the pulse position values in a 3D matrix
  //  pulse_position_value(k, i_position, i_mean )
  i = static_cast<int>(reps);
  if (i != i1) {
    rtIntegerError(reps, &l_emlrtDCI);
  }
  if (reps < 1.0) {
    rtDynamicBoundsError(1, 1, static_cast<int>(reps), &g_emlrtBCI);
  }
  //  first pulse is always in position 1
  //  loop through the mean PRI values
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
  if (!(ppmBig_data >= 0.0)) {
    rtNonNegativeError(rtNaN, &m_emlrtDCI);
  }
  i1 = static_cast<int>(std::floor(ppmBig_data));
  if (ppmBig_data != i1) {
    rtIntegerError(ppmBig_data, &n_emlrtDCI);
  }
  if (!(reps - 1.0 >= 0.0)) {
    rtNonNegativeError(reps - 1.0, &o_emlrtDCI);
  }
  if (reps - 1.0 != reps - 1.0) {
    rtIntegerError(reps - 1.0, &p_emlrtDCI);
  }
  //  number of rows per PRI mean
  k = static_cast<int>(ppmBig_data);
  if (k != i1) {
    rtIntegerError(ppmBig_data, &q_emlrtDCI);
  }
  if (ppmBig_data != 0.0) {
    num_PRI_patterns_tmp = k;
  } else if ((ppmBig_data != 0.0) && (reps - 1.0 != 0.0)) {
    num_PRI_patterns_tmp = k;
  } else {
    num_PRI_patterns_tmp = (ppmBig_data > 0.0);
    if (k > num_PRI_patterns_tmp) {
      num_PRI_patterns_tmp = 1;
    }
  }
  if ((k != num_PRI_patterns_tmp) && (!(ppmBig_data == 0.0))) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  if ((k != num_PRI_patterns_tmp) &&
      ((!(ppmBig_data == 0.0)) && (!(reps - 1.0 == 0.0)))) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  empty_non_axis_sizes = (num_PRI_patterns_tmp == 0);
  if (empty_non_axis_sizes || (ppmBig_data != 0.0)) {
    input_sizes_idx_1 = 1;
  } else {
    input_sizes_idx_1 = 0;
  }
  if (empty_non_axis_sizes || ((ppmBig_data != 0.0) && (reps - 1.0 != 0.0))) {
    sizes[1] = i - 1;
  } else {
    sizes[1] = 0;
  }
  //  remove duplicate patterns
  r.set_size(num_PRI_patterns_tmp, input_sizes_idx_1 + sizes[1]);
  k = input_sizes_idx_1;
  for (i = 0; i < k; i++) {
    for (i1 = 0; i1 < num_PRI_patterns_tmp; i1++) {
      r[i1] = 1.0;
    }
  }
  k = sizes[1];
  for (i = 0; i < k; i++) {
    for (i1 = 0; i1 < num_PRI_patterns_tmp; i1++) {
      r[i1 + r.size(0) * (i + input_sizes_idx_1)] = 0.0;
    }
  }
  r.reserve(1);
  coder::unique_rows(*(int(*)[2])r.size());
  input_sizes_idx_0 = static_cast<signed char>(r.size(0));
  input_sizes_idx_1 = static_cast<signed char>(r.size(1));
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
    if (priMeansList_size_idx_1 < 1) {
      ib_rtErrorWithMessageID(kb_emlrtRTEI.fName, kb_emlrtRTEI.lineNo);
    }
    // Equivalent to N+M+J-J
  } else {
    if (priMeansList_size_idx_1 < 1) {
      ib_rtErrorWithMessageID(kb_emlrtRTEI.fName, kb_emlrtRTEI.lineNo);
    }
    if (WqColInds_size[1] < 1) {
      ib_rtErrorWithMessageID(kb_emlrtRTEI.fName, kb_emlrtRTEI.lineNo);
    }
    priMeansList_data += WqColInds_data;
    // Equivalent to N+M+J
  }
  // Number of rows in pulse_position_matrix
  // Number of cols in pulse_position_matrix --- should always be K
  if ((priMeansList_data + 1.0 != priMeansList_data + 1.0) ||
      std::isinf(priMeansList_data + 1.0)) {
    c_rtErrorWithMessageID(MIN_int32_T, gb_emlrtRTEI.fName,
                           gb_emlrtRTEI.lineNo);
  }
  if (!(priMeansList_data + 1.0 >= 0.0)) {
    rtNonNegativeError(priMeansList_data + 1.0, &b_emlrtDCI);
  }
  outsize_idx_0_tmp =
      static_cast<signed char>(static_cast<signed char>(r.size(0)) *
                               static_cast<int>(priMeansList_data + 1.0));
  ppmBig_size[0] = outsize_idx_0_tmp;
  ppmBig_size[1] = static_cast<signed char>(r.size(1));
  // Create multiple copies of the PPM matrix. Each copy will eventually be
  // shifted. The second copy will get a 1 added to it, the third a 2 added, and
  // so on up to n_shifts. Use n_shifts+1 to account for the first one that
  // receives no shifting. Get the number of rows in the big PPM matrix
  if (std::isnan(priMeansList_data)) {
    sizes[1] = 1;
  } else if (priMeansList_data < 0.0) {
    sizes[1] = 0;
  } else {
    sizes[1] = static_cast<int>(priMeansList_data) + 1;
  }
  r.set_size(static_cast<int>(input_sizes_idx_0), sizes[1]);
  // Create a matrix of the shifts needed for each copy of the PPM matrix
  k = r.size(0) * r.size(1);
  r1.set_size(k);
  k--;
  for (i = 0; i <= k; i++) {
    r1[i] = r[i];
  }
  coder::repmat(r1, static_cast<double>(input_sizes_idx_1), r);
  if ((r.size(0) != outsize_idx_0_tmp) &&
      ((r.size(0) != 1) && (outsize_idx_0_tmp != 1))) {
    emlrtDimSizeImpxCheckR2021b(r.size(0), static_cast<int>(outsize_idx_0_tmp),
                                &f_emlrtECI);
  }
  if ((r.size(1) != input_sizes_idx_1) &&
      ((r.size(1) != 1) && (input_sizes_idx_1 != 1))) {
    emlrtDimSizeImpxCheckR2021b(r.size(1), static_cast<int>(input_sizes_idx_1),
                                &g_emlrtECI);
  }
  if ((r.size(0) == outsize_idx_0_tmp) && (r.size(1) == input_sizes_idx_1)) {
    k = r.size(0) * r.size(1);
    r.set_size(r.size(0), r.size(1));
    for (i = 0; i < k; i++) {
      r[i] = r[i] + ppmBig_data;
    }
  } else {
    binary_expand_op(r, (const double *)&ppmBig_data, ppmBig_size);
  }
  if (outsize_idx_0_tmp < 1) {
    sizes[1] = 0;
  } else {
    sizes[1] = 1;
  }
  k = r.size(0) * r.size(1);
  num_PRI_patterns_tmp =
      static_cast<signed char>(r.size(0)) * static_cast<signed char>(r.size(1));
  coder::b_sparse(k, sizes[1] * input_sizes_idx_1, num_PRI_patterns_tmp, &Wq);
  // , obj.reps(i));
  ppmBig_data = coder::toc() - previousToc;
  printf("complete. Elapsed time: %f seconds \n", ppmBig_data);
  fflush(stdout);
  previousToc = coder::toc();
  printf("\t Building synthetic data and taking STFTs ...");
  fflush(stdout);
  if (static_cast<int>(stftSz_idx_1) != Wq.m) {
    b_rtErrorWithMessageID(b_emlrtRTEI.fName, b_emlrtRTEI.lineNo);
  }
  // Here we approximated the number of samples of synthetic noise data needed
  // to get the correct number of time windows. We over estimate here and then
  // clip the number of correct windows after the stft operation.
  // Based on the STFT help file for the number of windows as a function of
  // samples. We add an additional windows worth of samples to ensure we have
  // enough in our STFT output. We'll clip off any excess after the STFT Number
  // of sets of synthetic noise to generate Preallocate the scores matrix
  // Calculate the total power in the waveform for all frequency bins. Units are
  // W/bin * # bins = W
  coder::wgn((static_cast<double>(stftSz_idx_1) + 1.0) * Wfm->n_ws + Wfm->n_ol,
             static_cast<double>(stftSz_idx_0), xsynth_data, WqColInds_size);
  // Generate the synthetic data
  coder::stft(WqColInds_size, (const double *)Wfm->stft->wind.data(),
              (*(int(*)[1])Wfm->stft->wind.size())[0], Wfm->n_ol, Wfm->n_w);
  // Trim excess so we have the correct number of windows.
  ppmBig_data = coder::toc() - previousToc;
  printf("complete. Elapsed time: %f seconds \n", ppmBig_data);
  fflush(stdout);
  previousToc = coder::toc();
  printf("\t Running pulse summing process for all datasets ...");
  fflush(stdout);
  // Preform the incoherent summation using a matrix multiply.
  // Could use pagetimes.m for this, but it isn't supported for
  // code generation with sparse matrices as of R2023a
  ppmBig_data = coder::toc() - previousToc;
  printf("complete. Elapsed time: %f seconds \n", ppmBig_data);
  fflush(stdout);
  previousToc = coder::toc();
  printf("\t Extracing extreme value fit parameters ...");
  fflush(stdout);
  // Build the distribution for all scores.
  // Old kernel density estimation method
  //  [f,xi]   =
  //  ksdensity(scores(:),'BoundaryCorrection','reflection','Support','positive');
  //  F        = cumtrapz(xi,f);
  // Updated extreme value estimation method
  // xi = linspace(1/2*min(scores),2*max(scores),1000);
  // paramEstsMaxima = evfit(-scores);
  // cdfVals = evcdf(-xi,paramEstsMaxima(1),paramEstsMaxima(2));
  // F = 1 - cdfVals;
  theFunc.workspace.mu = rtNaN;
  theFunc.workspace.sigma = rtNaN;
  // theFunc = @(x) 1-exp(-exp((x-mu)/sigma));%Equivalent to evcdf(x,mu,sigma)
  // theFunc = @(x) exp(-exp((x-mu)/sigma));%Equivalent to 1-evcdf(x,mu,sigma)
  // Equivalent to 1-evcdf(x,mu,sigma)-pf
  coder::fzero(theFunc);
  // theFunc monitonically decrease, so starting at x = 0 should always converge
  ppmBig_data = coder::toc() - previousToc;
  printf("complete. Elapsed time: %f seconds \n", ppmBig_data);
  fflush(stdout);
  coder::toc();
  // figure;plot(xi,F)
  // Uncomment to see how fitted distribution compares to histogram of max
  // scores
  //              p = evpdf(-xi,paramEstsMaxima(1),paramEstsMaxima(2));
  //              figure
  //              histogram(scores,'Normalization','pdf');
  //              hold on
  //              plot(xi,p,'DisplayName','EV Fit'); legend('Location','best')
  //              p = 1-evcdf(-xi,paramEstsMaxima(1),paramEstsMaxima(2));
  //              figure
  //              histogram(scores,'Normalization','cdf');
  //              hold on
  //              plot(xi,p,'DisplayName','EV Fit'); legend('Location','best')
  // Now we linearly interpolate the threshold values for different noise
  // powers. We showed elsewhere this linear relationship hold by calculating
  // thresholds for ranges of noise power.
  // Here we deal with points where there is no change in F. Interp needs
  // unique values and at the tails of the distibution, there may be repeated
  // values.
  // nochangelogic = [false,diff(F)==0];
  // threshMedPow =
  // interp1(F(~nochangelogic),xi(~nochangelogic),1-PF,'pchip','extrap');
  //              powGrid    = [0 medPowAllFreqBins];
  //              threshGrid = [0 threshMedPow];
  //              newThresh =
  //              interp1(powGrid,threshGrid,freqBinPow,'linear','extrap');
  //
  //              %Finally,extrapolating the thresholds that are a little beyond
  //              the original %frequeny range can result in negative
  //              thresholds. Here we copy the first %and last valid threshold
  //              out to the places where the extrapolations would %have occured
  //              isnanThreshLogic   = isnan(newThresh);
  //              firstTrueThreshInd = find(~isnanThreshLogic,1,'first');
  //              lastTrueThreshInd  = find(~isnanThreshLogic,1,'last');
  //              firstTrueThresh    = newThresh(firstTrueThreshInd);
  //              lastTrueThresh     = newThresh(lastTrueThreshInd);
  //              newThresh(1:firstTrueThreshInd(1))  = firstTrueThresh; %The
  //              (1) call is needed by coder, as it doesn't know that the find
  //              call above will only produced a scalar output.
  //              newThresh(lastTrueThreshInd(1):end) = lastTrueThresh; %The (1)
  //              call is needed by coder, as it doesn't know that the find call
  //              above will only produced a scalar output. %toc
  //
  //              obj.thresh1W        = threshMedPow;
  //              obj.threshVecCoarse = newThresh;
  //              obj.threshVecFine   =
  //              interp1(Wfm.stft.f,double(newThresh),Wfm.Wf,'linear','extrap');
  priMeansList_size_idx_1 = Wfm->stft->psd.size(0);
  // Extract psd for current waveform. Units are W/Hz
  i = Wfm->stft->f.size(0);
  if (i < 2) {
    rtDynamicBoundsError(2, 1, i, &h_emlrtBCI);
  }
  i = Wfm->stft->f.size(0);
  if (i < 1) {
    rtDynamicBoundsError(1, 1, i, &i_emlrtBCI);
  }
  // PSD (W/Hz) times bin width (Hz/bin) gives bin total power in (W/bin)
  // 1W standard
  // Finally,extrapolating the thresholds that are a little beyond the original
  // frequeny range can result in negative thresholds. Here we copy the first
  // and last valid threshold out to the places where the extrapolations would
  // have occured
  k = (priMeansList_size_idx_1 >= 1);
  if (k > priMeansList_size_idx_1) {
    j_rtErrorWithMessageID(h_emlrtRTEI.fName, h_emlrtRTEI.lineNo);
  }
  if (k != 1) {
    sizes[0] = 1;
    sizes[1] = 0;
    coder::internal::indexShapeCheck(0, sizes);
  }
  num_PRI_patterns_tmp = coder::c_eml_find(priMeansList_size_idx_1);
  for (i = 0; i < num_PRI_patterns_tmp; i++) {
    ppmBig_data = ii_data;
  }
  for (i = 0; i < num_PRI_patterns_tmp; i++) {
    if ((static_cast<int>(ppmBig_data) < 1) ||
        (static_cast<int>(ppmBig_data) > priMeansList_size_idx_1)) {
      rtDynamicBoundsError(static_cast<int>(ppmBig_data), 1,
                           priMeansList_size_idx_1, &j_emlrtBCI);
    }
  }
  rtDynamicBoundsError(1, 1, 0, &k_emlrtBCI);
}

//
// File trailer for threshold.cpp
//
// [EOF]
//
