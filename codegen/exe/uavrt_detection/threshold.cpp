//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: threshold.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 30-Dec-2022 11:43:16
//

// Include Files
#include "threshold.h"
#include "anonymous_function.h"
#include "buildtimecorrelatormatrix.h"
#include "eml_int_forloop_overflow_check.h"
#include "evfit.h"
#include "find.h"
#include "fzero.h"
#include "interp1.h"
#include "randn.h"
#include "rt_nonfinite.h"
#include "sparse1.h"
#include "stft.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_internal_types.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "unaryMinOrMax.h"
#include "validator_check_size.h"
#include "waveform.h"
#include "wfmstft.h"
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
static void kc_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void o_binary_expand_op(coder::array<boolean_T, 1U> &in1,
                               const waveform *in2, const waveform *in3);

static void p_binary_expand_op(coder::array<boolean_T, 2U> &in1,
                               const waveform *in2, const waveform *in3);

// Function Definitions
//
// Arguments    : double thresh
//                const waveform *Wfm
// Return Type  : void
//
void threshold::setthreshprops(double thresh, const waveform *Wfm)
{
  static rtBoundsCheckInfo eb_emlrtBCI{
      -1,                                        // iFirst
      -1,                                        // iLast
      232,                                       // lineNo
      49,                                        // colNo
      "Wfm.stft.f",                              // aName
      "threshold/setthreshprops",                // fName
      "H:\\repos\\uavrt_detection\\threshold.m", // pName
      0                                          // checkKind
  };
  static rtBoundsCheckInfo fb_emlrtBCI{
      -1,                                        // iFirst
      -1,                                        // iLast
      232,                                       // lineNo
      63,                                        // colNo
      "Wfm.stft.f",                              // aName
      "threshold/setthreshprops",                // fName
      "H:\\repos\\uavrt_detection\\threshold.m", // pName
      0                                          // checkKind
  };
  static rtBoundsCheckInfo gb_emlrtBCI{
      -1,                                        // iFirst
      -1,                                        // iLast
      246,                                       // lineNo
      44,                                        // colNo
      "newThresh",                               // aName
      "threshold/setthreshprops",                // fName
      "H:\\repos\\uavrt_detection\\threshold.m", // pName
      0                                          // checkKind
  };
  static rtBoundsCheckInfo hb_emlrtBCI{
      -1,                                        // iFirst
      -1,                                        // iLast
      247,                                       // lineNo
      44,                                        // colNo
      "newThresh",                               // aName
      "threshold/setthreshprops",                // fName
      "H:\\repos\\uavrt_detection\\threshold.m", // pName
      0                                          // checkKind
  };
  static rtBoundsCheckInfo ib_emlrtBCI{
      -1,                                        // iFirst
      -1,                                        // iLast
      248,                                       // lineNo
      44,                                        // colNo
      "firstTrueThreshInd",                      // aName
      "threshold/setthreshprops",                // fName
      "H:\\repos\\uavrt_detection\\threshold.m", // pName
      0                                          // checkKind
  };
  static rtBoundsCheckInfo jb_emlrtBCI{
      -1,                                        // iFirst
      -1,                                        // iLast
      248,                                       // lineNo
      23,                                        // colNo
      "newThresh",                               // aName
      "threshold/setthreshprops",                // fName
      "H:\\repos\\uavrt_detection\\threshold.m", // pName
      0                                          // checkKind
  };
  static rtBoundsCheckInfo kb_emlrtBCI{
      -1,                                        // iFirst
      -1,                                        // iLast
      248,                                       // lineNo
      25,                                        // colNo
      "newThresh",                               // aName
      "threshold/setthreshprops",                // fName
      "H:\\repos\\uavrt_detection\\threshold.m", // pName
      0                                          // checkKind
  };
  static rtBoundsCheckInfo lb_emlrtBCI{
      -1,                                        // iFirst
      -1,                                        // iLast
      249,                                       // lineNo
      41,                                        // colNo
      "lastTrueThreshInd",                       // aName
      "threshold/setthreshprops",                // fName
      "H:\\repos\\uavrt_detection\\threshold.m", // pName
      0                                          // checkKind
  };
  static rtBoundsCheckInfo mb_emlrtBCI{
      -1,                                        // iFirst
      -1,                                        // iLast
      249,                                       // lineNo
      23,                                        // colNo
      "newThresh",                               // aName
      "threshold/setthreshprops",                // fName
      "H:\\repos\\uavrt_detection\\threshold.m", // pName
      0                                          // checkKind
  };
  static rtBoundsCheckInfo nb_emlrtBCI{
      -1,                                        // iFirst
      -1,                                        // iLast
      249,                                       // lineNo
      44,                                        // colNo
      "newThresh",                               // aName
      "threshold/setthreshprops",                // fName
      "H:\\repos\\uavrt_detection\\threshold.m", // pName
      0                                          // checkKind
  };
  static rtEqualityCheckInfo g_emlrtECI{
      -1,                                       // nDims
      248,                                      // lineNo
      13,                                       // colNo
      "threshold/setthreshprops",               // fName
      "H:\\repos\\uavrt_detection\\threshold.m" // pName
  };
  static rtEqualityCheckInfo h_emlrtECI{
      -1,                                       // nDims
      249,                                      // lineNo
      13,                                       // colNo
      "threshold/setthreshprops",               // fName
      "H:\\repos\\uavrt_detection\\threshold.m" // pName
  };
  coder::array<double, 2U> b_newThresh;
  coder::array<double, 1U> c_newThresh;
  coder::array<double, 1U> freqBinPSD;
  coder::array<double, 1U> newThresh;
  coder::array<boolean_T, 1U> x_tmp;
  double lastTrueThresh_data;
  int firstTrueThreshInd_data;
  int firstTrueThreshInd_size;
  int i;
  int ii_data;
  int ii_size;
  freqBinPSD.set_size(Wfm->stft->psd.size(0));
  firstTrueThreshInd_data = Wfm->stft->psd.size(0);
  for (i = 0; i < firstTrueThreshInd_data; i++) {
    freqBinPSD[i] = Wfm->stft->psd[i];
  }
  // Extract psd for current waveform. Units are W/Hz
  i = Wfm->stft->f.size(0);
  if (i < 2) {
    rtDynamicBoundsError(2, 1, i, &eb_emlrtBCI);
  }
  i = Wfm->stft->f.size(0);
  if (i < 1) {
    rtDynamicBoundsError(1, 1, i, &fb_emlrtBCI);
  }
  lastTrueThresh_data = Wfm->stft->f[1] - Wfm->stft->f[0];
  firstTrueThreshInd_data = freqBinPSD.size(0);
  for (i = 0; i < firstTrueThreshInd_data; i++) {
    freqBinPSD[i] = freqBinPSD[i] * lastTrueThresh_data;
  }
  // PSD (W/Hz) times bin width (Hz/bin) gives bin total power in (W/bin)
  // 1W standard
  newThresh.set_size(freqBinPSD.size(0));
  firstTrueThreshInd_data = freqBinPSD.size(0);
  for (i = 0; i < firstTrueThreshInd_data; i++) {
    newThresh[i] = 0.0;
  }
  if (freqBinPSD.size(0) != 0) {
    double dv[2];
    dv[0] = 0.0;
    dv[1] = thresh;
    coder::interp1Linear(dv, freqBinPSD, newThresh);
  }
  // Finally,extrapolating the thresholds that are a little beyond the original
  // frequeny range can result in negative thresholds. Here we copy the first
  // and last valid threshold out to the places where the extrapolations would
  // have occured
  x_tmp.set_size(newThresh.size(0));
  firstTrueThreshInd_data = newThresh.size(0);
  for (i = 0; i < firstTrueThreshInd_data; i++) {
    x_tmp[i] = std::isnan(newThresh[i]);
  }
  firstTrueThreshInd_data = x_tmp.size(0);
  for (i = 0; i < firstTrueThreshInd_data; i++) {
    x_tmp[i] = !x_tmp[i];
  }
  coder::c_eml_find(x_tmp, (int *)&ii_data, &ii_size);
  firstTrueThreshInd_size = ii_size;
  for (i = 0; i < ii_size; i++) {
    firstTrueThreshInd_data = ii_data;
  }
  coder::d_eml_find(x_tmp, (int *)&ii_data, &ii_size);
  for (i = 0; i < firstTrueThreshInd_size; i++) {
    if ((firstTrueThreshInd_data < 1) ||
        (firstTrueThreshInd_data > newThresh.size(0))) {
      rtDynamicBoundsError(firstTrueThreshInd_data, 1, newThresh.size(0),
                           &gb_emlrtBCI);
    }
  }
  for (i = 0; i < ii_size; i++) {
    if ((ii_data < 1) || (ii_data > newThresh.size(0))) {
      rtDynamicBoundsError(ii_data, 1, newThresh.size(0), &hb_emlrtBCI);
    }
    lastTrueThresh_data = newThresh[ii_data - 1];
  }
  if (firstTrueThreshInd_size < 1) {
    rtDynamicBoundsError(1, 1, firstTrueThreshInd_size, &ib_emlrtBCI);
  }
  if (newThresh.size(0) < 1) {
    rtDynamicBoundsError(1, 1, newThresh.size(0), &jb_emlrtBCI);
  }
  if ((firstTrueThreshInd_data < 1) ||
      (firstTrueThreshInd_data > newThresh.size(0))) {
    rtDynamicBoundsError(firstTrueThreshInd_data, 1, newThresh.size(0),
                         &kb_emlrtBCI);
  }
  if (firstTrueThreshInd_data != firstTrueThreshInd_size) {
    rtSizeEq1DError(firstTrueThreshInd_data, firstTrueThreshInd_size,
                    &g_emlrtECI);
  }
  b_newThresh.set_size(1, firstTrueThreshInd_data);
  for (i = 0; i < firstTrueThreshInd_data; i++) {
    b_newThresh[i] = newThresh[firstTrueThreshInd_data - 1];
  }
  firstTrueThreshInd_data = b_newThresh.size(1);
  for (i = 0; i < firstTrueThreshInd_data; i++) {
    newThresh[i] = b_newThresh[i];
  }
  // The (1) call is needed by coder, as it doesn't know that the find call
  // above will only produced a scalar output.
  if (ii_size < 1) {
    rtDynamicBoundsError(1, 1, ii_size, &lb_emlrtBCI);
  }
  if (ii_data > newThresh.size(0)) {
    i = -1;
    firstTrueThreshInd_size = -1;
  } else {
    if ((ii_data < 1) || (ii_data > newThresh.size(0))) {
      rtDynamicBoundsError(ii_data, 1, newThresh.size(0), &mb_emlrtBCI);
    }
    i = ii_data - 2;
    if (newThresh.size(0) < 1) {
      rtDynamicBoundsError(newThresh.size(0), 1, newThresh.size(0),
                           &nb_emlrtBCI);
    }
    firstTrueThreshInd_size = newThresh.size(0) - 1;
  }
  firstTrueThreshInd_data = firstTrueThreshInd_size - i;
  if (firstTrueThreshInd_data != ii_size) {
    rtSizeEq1DError(firstTrueThreshInd_data, ii_size, &h_emlrtECI);
  }
  for (firstTrueThreshInd_size = 0;
       firstTrueThreshInd_size < firstTrueThreshInd_data;
       firstTrueThreshInd_size++) {
    newThresh[(i + firstTrueThreshInd_size) + 1] = lastTrueThresh_data;
  }
  // The (1) call is needed by coder, as it doesn't know that the find call
  // above will only produced a scalar output. toc
  coder::internal::validator_check_size(newThresh, c_newThresh);
  coder::interp1(Wfm->stft->f, newThresh, Wfm->Wf, freqBinPSD);
  coder::internal::validator_check_size(freqBinPSD, threshVecFine);
}

//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void kc_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "The required dimensions must be real, integer scalars > 1.";
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
// Arguments    : coder::array<boolean_T, 1U> &in1
//                const waveform *in2
//                const waveform *in3
// Return Type  : void
//
static void o_binary_expand_op(coder::array<boolean_T, 1U> &in1,
                               const waveform *in2, const waveform *in3)
{
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in3->Wf.size(0) == 1) {
    i = in2->Wf.size(0);
  } else {
    i = in3->Wf.size(0);
  }
  in1.set_size(i);
  stride_0_0 = (in2->Wf.size(0) != 1);
  stride_1_0 = (in3->Wf.size(0) != 1);
  if (in3->Wf.size(0) == 1) {
    loop_ub = in2->Wf.size(0);
  } else {
    loop_ub = in3->Wf.size(0);
  }
  for (i = 0; i < loop_ub; i++) {
    in1[i] = (in2->Wf[i * stride_0_0] != in3->Wf[i * stride_1_0]);
  }
}

//
// Arguments    : coder::array<boolean_T, 2U> &in1
//                const waveform *in2
//                const waveform *in3
// Return Type  : void
//
static void p_binary_expand_op(coder::array<boolean_T, 2U> &in1,
                               const waveform *in2, const waveform *in3)
{
  int aux_0_1;
  int aux_1_1;
  int i;
  int i1;
  int loop_ub;
  int stride_0_0;
  int stride_0_1;
  int stride_1_0;
  int stride_1_1;
  if (in3->W.size(0) == 1) {
    i = in2->W.size(0);
  } else {
    i = in3->W.size(0);
  }
  if (in3->W.size(1) == 1) {
    i1 = in2->W.size(1);
  } else {
    i1 = in3->W.size(1);
  }
  in1.set_size(i, i1);
  stride_0_0 = (in2->W.size(0) != 1);
  stride_0_1 = (in2->W.size(1) != 1);
  stride_1_0 = (in3->W.size(0) != 1);
  stride_1_1 = (in3->W.size(1) != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  if (in3->W.size(1) == 1) {
    loop_ub = in2->W.size(1);
  } else {
    loop_ub = in3->W.size(1);
  }
  for (i = 0; i < loop_ub; i++) {
    int b_loop_ub;
    if (in3->W.size(0) == 1) {
      b_loop_ub = in2->W.size(0);
    } else {
      b_loop_ub = in3->W.size(0);
    }
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      int i2;
      i2 = i1 * stride_1_0;
      in1[i1 + in1.size(0) * i] =
          ((in2->W[i1 * stride_0_0 + in2->W.size(0) * aux_0_1].re !=
            in3->W[i2 + in3->W.size(0) * aux_1_1].re) ||
           (in2->W[i1 * stride_0_0 + in2->W.size(0) * aux_0_1].im !=
            in3->W[i2 + in3->W.size(0) * aux_1_1].im));
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
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
void threshold::makenewthreshold(const waveform *Wfm)
{
  static rtBoundsCheckInfo eb_emlrtBCI{
      -1,                                        // iFirst
      -1,                                        // iLast
      118,                                       // lineNo
      55,                                        // colNo
      "Ssynth",                                  // aName
      "threshold/makenewthreshold",              // fName
      "H:\\repos\\uavrt_detection\\threshold.m", // pName
      0                                          // checkKind
  };
  static rtDoubleCheckInfo
      t_emlrtDCI{
          452,                       // lineNo
          58,                        // colNo
          "general_null_assignment", // fName
          "C:\\Program "
          "Files\\MATLAB\\toolbox\\eml\\eml\\+coder\\+internal\\nullAssignment."
          "m", // pName
          4    // checkKind
      };
  static rtEqualityCheckInfo g_emlrtECI{
      2,                                                      // nDims
      223,                                                    // lineNo
      38,                                                     // colNo
      "wgn",                                                  // fName
      "C:\\Program Files\\MATLAB\\toolbox\\comm\\comm\\wgn.m" // pName
  };
  static rtRunTimeErrorInfo qc_emlrtRTEI{
      180,  // lineNo
      "wgn" // fName
  };
  static rtRunTimeErrorInfo rc_emlrtRTEI{
      81,               // lineNo
      "validate_inputs" // fName
  };
  static rtRunTimeErrorInfo sc_emlrtRTEI{
      449,                      // lineNo
      "general_null_assignment" // fName
  };
  static const char b[7]{'c', 'o', 'm', 'p', 'l', 'e', 'x'};
  static const char b_cv1[7]{'c', 'o', 'm', 'p', 'l', 'e', 'x'};
  static const char b_cv[6]{'l', 'i', 'n', 'e', 'a', 'r'};
  static const char c_b[6]{'l', 'i', 'n', 'e', 'a', 'r'};
  coder::b_anonymous_function theFunc;
  coder::sparse Wq;
  coder::array<creal_T, 3U> Ssynth;
  coder::array<creal_T, 3U> b_x;
  coder::array<creal_T, 2U> f_b;
  coder::array<creal_T, 2U> xsynth;
  coder::array<creal_T, 2U> y;
  coder::array<double, 2U> b_y;
  coder::array<double, 2U> d_b;
  coder::array<double, 2U> r1;
  coder::array<double, 2U> varargin_1;
  coder::array<double, 1U> a__1;
  coder::array<double, 1U> a__2;
  coder::array<int, 2U> idx;
  coder::array<char, 2U> b_b;
  coder::array<char, 2U> r;
  coder::array<boolean_T, 2U> e_b;
  double scores[100];
  double stftSz[2];
  double noisePower;
  double s_im;
  int iv[2];
  int iv1[2];
  int b_overflow;
  int exitg2;
  int inner;
  int iy0;
  int k;
  int n;
  int ns;
  int nxout;
  int sz_idx_2;
  int vlen;
  int vstride;
  int xpagesize;
  char cplxMode_data[7];
  boolean_T x[6];
  boolean_T exitg1;
  boolean_T overflow;
  theFunc.workspace.pf = pf;
  // This will be the reference power for the trials. Thresholds will be
  // interpolated for each bin from this value based on their bin power
  // median(freqBinPow);
  stftSz[0] = Wfm->stft->S.size(0);
  stftSz[1] = Wfm->stft->S.size(1);
  // Build the Wq time correlation matrix
  buildtimecorrelatormatrix(Wfm->N, Wfm->M, Wfm->J, Wfm->K, &Wq);
  sz_idx_2 = static_cast<int>(stftSz[1]);
  if (sz_idx_2 != Wq.m) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
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
  s_im = (stftSz[1] + 1.0) * Wfm->n_ws + Wfm->n_ol;
  for (ns = 0; ns < 7; ns++) {
    cplxMode_data[ns] = b[ns];
  }
  x[0] = (s_im <= 0.0);
  x[1] = false;
  x[2] = false;
  x[3] = false;
  x[4] = (s_im - std::floor(s_im) != 0.0);
  x[5] = false;
  overflow = false;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 6)) {
    if (x[k]) {
      overflow = true;
      exitg1 = true;
    } else {
      k++;
    }
  }
  if (overflow) {
    kc_rtErrorWithMessageID(qc_emlrtRTEI.fName, qc_emlrtRTEI.lineNo);
  }
  b_b.set((char *)&c_b[0], 1, 6);
  ns = b_b.size(1);
  overflow = true;
  if (b_b.size(1) > 2147483646) {
    coder::check_forloop_overflow_error();
  }
  for (k = 0; k < ns; k++) {
    overflow = (overflow && (static_cast<unsigned char>(b_b[k]) <= 127));
  }
  if (!overflow) {
    pc_rtErrorWithMessageID(i_emlrtRTEI.fName, i_emlrtRTEI.lineNo);
  }
  r.set_size(1, b_b.size(1));
  ns = b_b.size(1);
  for (k = 0; k < ns; k++) {
    r[k] = cv[static_cast<unsigned char>(b_b[k]) & 127];
  }
  overflow = false;
  ns = 0;
  do {
    exitg2 = 0;
    if (ns < 6) {
      if (r[ns] != b_cv[ns]) {
        exitg2 = 1;
      } else {
        ns++;
      }
    } else {
      overflow = true;
      exitg2 = 1;
    }
  } while (exitg2 == 0);
  if (overflow) {
    b_overflow = 0;
  } else {
    b_overflow = -1;
  }
  if (b_overflow == 0) {
    noisePower = stftSz[0];
  } else {
    noisePower = rt_powd_snf(10.0, (stftSz[0] - 30.0) / 10.0);
  }
  overflow = false;
  ns = 0;
  do {
    exitg2 = 0;
    if (ns < 7) {
      if (cplxMode_data[ns] != b_cv1[ns]) {
        exitg2 = 1;
      } else {
        ns++;
      }
    } else {
      overflow = true;
      exitg2 = 1;
    }
  } while (exitg2 == 0);
  if (overflow) {
    coder::randn(s_im, r1);
    coder::randn(s_im, d_b);
    xsynth.set_size(d_b.size(0), 100);
    b_overflow = d_b.size(0) * 100;
    for (ns = 0; ns < b_overflow; ns++) {
      xsynth[ns].re = d_b[ns] * 0.0;
      xsynth[ns].im = d_b[ns];
    }
    iv[0] = (*(int(*)[2])r1.size())[0];
    iv[1] = (*(int(*)[2])r1.size())[1];
    iv1[0] = (*(int(*)[2])xsynth.size())[0];
    iv1[1] = (*(int(*)[2])xsynth.size())[1];
    rtSizeEqNDCheck(&iv[0], &iv1[0], &g_emlrtECI);
    noisePower = std::sqrt(noisePower / 2.0);
    b_overflow = r1.size(0) * 100;
    xsynth.set_size(r1.size(0), 100);
    for (ns = 0; ns < b_overflow; ns++) {
      xsynth[ns].re = noisePower * (r1[ns] + xsynth[ns].re);
      xsynth[ns].im = noisePower * xsynth[ns].im;
    }
  } else {
    noisePower = std::sqrt(noisePower);
    coder::randn(s_im, d_b);
    xsynth.set_size(d_b.size(0), 100);
    b_overflow = d_b.size(0) * 100;
    for (ns = 0; ns < b_overflow; ns++) {
      xsynth[ns].re = noisePower * d_b[ns];
      xsynth[ns].im = 0.0;
    }
  }
  // Generate the synthetic data
  coder::stft(xsynth, Wfm->Fs, Wfm->stft->wind, Wfm->n_ol, Wfm->n_w, Ssynth,
              a__1, a__2);
  idx.set_size(1, Ssynth.size(1) - sz_idx_2);
  b_overflow = Ssynth.size(1) - sz_idx_2;
  for (ns = 0; ns < b_overflow; ns++) {
    idx[ns] = (sz_idx_2 + ns) + 1;
  }
  overflow = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= (Ssynth.size(1) - sz_idx_2) - 1)) {
    if (idx[k] > Ssynth.size(1)) {
      overflow = false;
      exitg1 = true;
    } else {
      k++;
    }
  }
  if (!overflow) {
    ic_rtErrorWithMessageID(rc_emlrtRTEI.fName, rc_emlrtRTEI.lineNo);
  }
  b_x.set_size(Ssynth.size(0), Ssynth.size(1), Ssynth.size(2));
  b_overflow = Ssynth.size(0) * Ssynth.size(1) * Ssynth.size(2);
  for (ns = 0; ns < b_overflow; ns++) {
    b_x[ns] = Ssynth[ns];
  }
  vlen = Ssynth.size(1);
  e_b.set_size(1, Ssynth.size(1));
  b_overflow = Ssynth.size(1);
  for (ns = 0; ns < b_overflow; ns++) {
    e_b[ns] = false;
  }
  ns = (Ssynth.size(1) - sz_idx_2) - 1;
  overflow = (Ssynth.size(1) - sz_idx_2 > 2147483646);
  if (overflow) {
    coder::check_forloop_overflow_error();
  }
  for (k = 0; k <= ns; k++) {
    e_b[idx[k] - 1] = true;
  }
  n = 0;
  ns = e_b.size(1);
  if (e_b.size(1) > 2147483646) {
    coder::check_forloop_overflow_error();
  }
  for (k = 0; k < ns; k++) {
    n += e_b[k];
  }
  nxout = Ssynth.size(1) - n;
  ns = Ssynth.size(0);
  sz_idx_2 = Ssynth.size(2);
  if (nxout > Ssynth.size(1)) {
    h_rtErrorWithMessageID(sc_emlrtRTEI.fName, sc_emlrtRTEI.lineNo);
  }
  if (nxout < 0) {
    rtNonNegativeError(static_cast<double>(nxout), &t_emlrtDCI);
  }
  Ssynth.set_size(ns, nxout, sz_idx_2);
  vstride = b_x.size(0);
  xpagesize = vlen * b_x.size(0);
  ns = nxout * b_x.size(0);
  sz_idx_2 = b_x.size(2);
  overflow = (vlen > 2147483646);
  for (int i{0}; i < sz_idx_2; i++) {
    nxout = i * xpagesize;
    iy0 = i * ns;
    if (overflow) {
      coder::check_forloop_overflow_error();
    }
    for (k = 0; k < vlen; k++) {
      if ((k + 1 > e_b.size(1)) || (!e_b[k])) {
        if (vstride > 2147483646) {
          coder::check_forloop_overflow_error();
        }
        for (int j{0}; j < vstride; j++) {
          Ssynth[iy0 + j] = b_x[nxout + j];
        }
        iy0 += vstride;
      }
      nxout += vstride;
    }
  }
  // Trim excess so we have the correct number of windows.
  // Preform the incoherent summation using a matrix multiply.
  // Could use pagetimes.m for this, but it isn't supported for code generation
  b_overflow = Ssynth.size(0);
  xpagesize = Ssynth.size(1);
  vlen = Wfm->W.size(1);
  inner = Wfm->W.size(0);
  n = Ssynth.size(1) - 1;
  overflow = (Ssynth.size(1) > 2147483646);
  for (int i{0}; i < 100; i++) {
    if (i + 1 > Ssynth.size(2)) {
      rtDynamicBoundsError(i + 1, 1, Ssynth.size(2), &eb_emlrtBCI);
    }
    f_b.set_size(b_overflow, xpagesize);
    for (sz_idx_2 = 0; sz_idx_2 < xpagesize; sz_idx_2++) {
      for (ns = 0; ns < b_overflow; ns++) {
        f_b[ns + f_b.size(0) * sz_idx_2] =
            Ssynth[(ns + Ssynth.size(0) * sz_idx_2) +
                   Ssynth.size(0) * Ssynth.size(1) * i];
      }
    }
    if (Wfm->W.size(0) != Ssynth.size(0)) {
      if (((Wfm->W.size(0) == 1) && (Wfm->W.size(1) == 1)) ||
          ((Ssynth.size(0) == 1) && (Ssynth.size(1) == 1))) {
        ub_rtErrorWithMessageID(cc_emlrtRTEI.fName, cc_emlrtRTEI.lineNo);
      } else {
        lb_rtErrorWithMessageID(bc_emlrtRTEI.fName, bc_emlrtRTEI.lineNo);
      }
    }
    y.set_size(Wfm->W.size(1), Ssynth.size(1));
    if (overflow) {
      coder::check_forloop_overflow_error();
    }
    for (int j{0}; j <= n; j++) {
      nxout = j * vlen;
      iy0 = j * Ssynth.size(0);
      if (vlen > 2147483646) {
        coder::check_forloop_overflow_error();
      }
      for (vstride = 0; vstride < vlen; vstride++) {
        ns = vstride * Wfm->W.size(0);
        noisePower = 0.0;
        s_im = 0.0;
        if (inner > 2147483646) {
          coder::check_forloop_overflow_error();
        }
        for (k = 0; k < inner; k++) {
          double Wfm_im;
          double Wfm_re;
          sz_idx_2 = ns + k;
          Wfm_re = Wfm->W[sz_idx_2].re;
          Wfm_im = -Wfm->W[sz_idx_2].im;
          sz_idx_2 = iy0 + k;
          noisePower += Wfm_re * f_b[sz_idx_2].re - Wfm_im * f_b[sz_idx_2].im;
          s_im += Wfm_re * f_b[sz_idx_2].im + Wfm_im * f_b[sz_idx_2].re;
        }
        sz_idx_2 = nxout + vstride;
        y[sz_idx_2].re = noisePower;
        y[sz_idx_2].im = s_im;
      }
    }
    ns = y.size(0) * y.size(1);
    b_y.set_size(y.size(0), y.size(1));
    if (ns > 2147483646) {
      coder::check_forloop_overflow_error();
    }
    for (k = 0; k < ns; k++) {
      b_y[k] = rt_hypotd_snf(y[k].re, y[k].im);
    }
    ns = b_y.size(0) * b_y.size(1);
    for (sz_idx_2 = 0; sz_idx_2 < ns; sz_idx_2++) {
      s_im = b_y[sz_idx_2];
      b_y[sz_idx_2] = s_im * s_im;
    }
    Wq.mtimes(b_y, varargin_1);
    ns = varargin_1.size(0) * varargin_1.size(1);
    a__1 = varargin_1.reshape(ns);
    scores[i] = coder::internal::unaryMinOrMax_anonFcn1(a__1);
    // 'all' call finds max across all temporal correlation sets and frequency
    // bins just like we do in the dectection code.
  }
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
  for (sz_idx_2 = 0; sz_idx_2 < 100; sz_idx_2++) {
    scores[sz_idx_2] = -scores[sz_idx_2];
  }
  coder::evfit(scores, stftSz);
  theFunc.workspace.mu = stftSz[0];
  theFunc.workspace.sigma = stftSz[1];
  // theFunc = @(x) 1-exp(-exp((x-mu)/sigma));%Equivalent to evcdf(x,mu,sigma)
  // theFunc = @(x) exp(-exp((x-mu)/sigma));%Equivalent to 1-evcdf(x,mu,sigma)
  // Equivalent to 1-evcdf(x,mu,sigma)-pf
  noisePower = coder::fzero(theFunc);
  // theFunc monitonically decrease, so starting at x = 0 should always converge
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
  evMuParam = stftSz[0];
  evSigmaParam = stftSz[1];
  setthreshprops(noisePower, Wfm);
}

//
// Wq depends on N M J K
// if old and new N, M, J, K, W, Wf are the same
//    copy over the fit parameters from prev to curr then
//    use the updatepf method to set the others
// else
//    use the makenewthreshold method to build out
//
// Arguments    : const waveform *WfmCurr
//                const waveform *WfmPrev
// Return Type  : void
//
void threshold::setthreshold(const waveform *WfmCurr, const waveform *WfmPrev)
{
  static rtEqualityCheckInfo g_emlrtECI{
      1,                                        // nDims
      43,                                       // lineNo
      45,                                       // colNo
      "threshold/setthreshold",                 // fName
      "H:\\repos\\uavrt_detection\\threshold.m" // pName
  };
  static rtEqualityCheckInfo h_emlrtECI{
      2,                                        // nDims
      43,                                       // lineNo
      45,                                       // colNo
      "threshold/setthreshold",                 // fName
      "H:\\repos\\uavrt_detection\\threshold.m" // pName
  };
  static rtEqualityCheckInfo i_emlrtECI{
      1,                                        // nDims
      44,                                       // lineNo
      45,                                       // colNo
      "threshold/setthreshold",                 // fName
      "H:\\repos\\uavrt_detection\\threshold.m" // pName
  };
  coder::b_anonymous_function theFunc;
  coder::array<boolean_T, 2U> x;
  coder::array<boolean_T, 1U> b_x;
  coder::array<boolean_T, 1U> c_x;
  int i;
  int loop_ub;
  boolean_T b;
  boolean_T b1;
  boolean_T b2;
  boolean_T b3;
  boolean_T b4;
  boolean_T exitg1;
  boolean_T needsUpdate;
  needsUpdate = (WfmCurr->N != WfmPrev->N);
  b = (WfmCurr->M != WfmPrev->M);
  b1 = (WfmCurr->J != WfmPrev->J);
  b2 = (WfmCurr->K != WfmPrev->K);
  i = WfmCurr->W.size(0);
  loop_ub = WfmPrev->W.size(0);
  if ((i != loop_ub) && ((i != 1) && (loop_ub != 1))) {
    emlrtDimSizeImpxCheckR2021b(i, loop_ub, &g_emlrtECI);
  }
  i = WfmCurr->W.size(1);
  loop_ub = WfmPrev->W.size(1);
  if ((i != loop_ub) && ((i != 1) && (loop_ub != 1))) {
    emlrtDimSizeImpxCheckR2021b(i, loop_ub, &h_emlrtECI);
  }
  if ((WfmCurr->W.size(0) == WfmPrev->W.size(0)) &&
      (WfmCurr->W.size(1) == WfmPrev->W.size(1))) {
    x.set_size(WfmCurr->W.size(0), WfmCurr->W.size(1));
    loop_ub = WfmCurr->W.size(0) * WfmCurr->W.size(1);
    for (i = 0; i < loop_ub; i++) {
      x[i] = ((WfmCurr->W[i].re != WfmPrev->W[i].re) ||
              (WfmCurr->W[i].im != WfmPrev->W[i].im));
    }
  } else {
    p_binary_expand_op(x, WfmCurr, WfmPrev);
  }
  loop_ub = x.size(0) * x.size(1);
  b_x = x.reshape(loop_ub);
  b3 = false;
  if (b_x.size(0) > 2147483646) {
    coder::check_forloop_overflow_error();
  }
  loop_ub = 1;
  exitg1 = false;
  while ((!exitg1) && (loop_ub <= b_x.size(0))) {
    if (b_x[loop_ub - 1]) {
      b3 = true;
      exitg1 = true;
    } else {
      loop_ub++;
    }
  }
  i = WfmCurr->Wf.size(0);
  loop_ub = WfmPrev->Wf.size(0);
  if ((i != loop_ub) && ((i != 1) && (loop_ub != 1))) {
    emlrtDimSizeImpxCheckR2021b(i, loop_ub, &i_emlrtECI);
  }
  if (WfmCurr->Wf.size(0) == WfmPrev->Wf.size(0)) {
    c_x.set_size(WfmCurr->Wf.size(0));
    loop_ub = WfmCurr->Wf.size(0);
    for (i = 0; i < loop_ub; i++) {
      c_x[i] = (WfmCurr->Wf[i] != WfmPrev->Wf[i]);
    }
  } else {
    o_binary_expand_op(c_x, WfmCurr, WfmPrev);
  }
  b4 = false;
  if (c_x.size(0) > 2147483646) {
    coder::check_forloop_overflow_error();
  }
  loop_ub = 1;
  exitg1 = false;
  while ((!exitg1) && (loop_ub <= c_x.size(0))) {
    if (c_x[loop_ub - 1]) {
      b4 = true;
      exitg1 = true;
    } else {
      loop_ub++;
    }
  }
  if (needsUpdate || b || b1 || b2 || b3 || b4) {
    makenewthreshold(WfmCurr);
  } else {
    double thresh;
    double val;
    thresh = WfmPrev->thresh.evMuParam;
    evMuParam = thresh;
    val = WfmPrev->thresh.evSigmaParam;
    evSigmaParam = val;
    printf("%f\n", thresh);
    fflush(stdout);
    printf("%f\n", thresh);
    fflush(stdout);
    printf("%f\n", pf);
    fflush(stdout);
    theFunc.workspace.mu = thresh;
    theFunc.workspace.sigma = val;
    theFunc.workspace.pf = pf;
    // theFunc = @(x) 1-exp(-exp((x-mu)/sigma));%Equivalent to evcdf(x,mu,sigma)
    // theFunc = @(x) exp(-exp((x-mu)/sigma));%Equivalent to 1-evcdf(x,mu,sigma)
    // Equivalent to 1-evcdf(x,mu,sigma)-pf
    thresh = coder::fzero(theFunc);
    // theFunc monitonically decrease, so starting at x = 0 should always
    // converge Build a single threshold value at 1 W bin power
    setthreshprops(thresh, WfmCurr);
    // Set thresholds for each bin based on their bin powers
    // Not actually updating the pf, just using the method to set all the other
    // parameters
  }
}

//
// File trailer for threshold.cpp
//
// [EOF]
//
