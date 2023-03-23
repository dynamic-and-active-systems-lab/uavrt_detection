//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: threshold.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 23-Mar-2023 12:56:08
//

// Include Files
#include "threshold.h"
#include "anonymous_function.h"
#include "buildtimecorrelatormatrix.h"
#include "eml_int_forloop_overflow_check.h"
#include "evfit.h"
#include "fileManager.h"
#include "find.h"
#include "fzero.h"
#include "interp1.h"
#include "nullAssignment.h"
#include "rt_nonfinite.h"
#include "sparse1.h"
#include "stft.h"
#include "toc.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_internal_types.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "unaryMinOrMax.h"
#include "validator_check_size.h"
#include "waveform.h"
#include "wfmstft.h"
#include "wgn.h"
#include "coder_array.h"
#include "stdio.h"
#include <cmath>
#include <cstddef>
#include <stdio.h>
#include <string.h>

// Function Definitions
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
  static rtBoundsCheckInfo fb_emlrtBCI{
      -1,                                        // iFirst
      -1,                                        // iLast
      282,                                       // lineNo
      49,                                        // colNo
      "Wfm.stft.f",                              // aName
      "threshold/setthreshprops",                // fName
      "H:\\repos\\uavrt_detection\\threshold.m", // pName
      0                                          // checkKind
  };
  static rtBoundsCheckInfo gb_emlrtBCI{
      -1,                                        // iFirst
      -1,                                        // iLast
      163,                                       // lineNo
      28,                                        // colNo
      "scores",                                  // aName
      "threshold/makenewthreshold",              // fName
      "H:\\repos\\uavrt_detection\\threshold.m", // pName
      0                                          // checkKind
  };
  static rtBoundsCheckInfo hb_emlrtBCI{
      -1,                                        // iFirst
      -1,                                        // iLast
      340,                                       // lineNo
      37,                                        // colNo
      "values",                                  // aName
      "threshold/loadThresholdValuesFromCache",  // fName
      "H:\\repos\\uavrt_detection\\threshold.m", // pName
      0                                          // checkKind
  };
  static rtBoundsCheckInfo ib_emlrtBCI{
      -1,                                        // iFirst
      -1,                                        // iLast
      339,                                       // lineNo
      37,                                        // colNo
      "values",                                  // aName
      "threshold/loadThresholdValuesFromCache",  // fName
      "H:\\repos\\uavrt_detection\\threshold.m", // pName
      0                                          // checkKind
  };
  static rtBoundsCheckInfo jb_emlrtBCI{
      -1,                                        // iFirst
      -1,                                        // iLast
      282,                                       // lineNo
      63,                                        // colNo
      "Wfm.stft.f",                              // aName
      "threshold/setthreshprops",                // fName
      "H:\\repos\\uavrt_detection\\threshold.m", // pName
      0                                          // checkKind
  };
  static rtBoundsCheckInfo kb_emlrtBCI{
      -1,                                        // iFirst
      -1,                                        // iLast
      163,                                       // lineNo
      59,                                        // colNo
      "Ssynth",                                  // aName
      "threshold/makenewthreshold",              // fName
      "H:\\repos\\uavrt_detection\\threshold.m", // pName
      0                                          // checkKind
  };
  static rtBoundsCheckInfo lb_emlrtBCI{
      -1,                                        // iFirst
      -1,                                        // iLast
      296,                                       // lineNo
      44,                                        // colNo
      "newThresh",                               // aName
      "threshold/setthreshprops",                // fName
      "H:\\repos\\uavrt_detection\\threshold.m", // pName
      0                                          // checkKind
  };
  static rtBoundsCheckInfo mb_emlrtBCI{
      -1,                                        // iFirst
      -1,                                        // iLast
      297,                                       // lineNo
      44,                                        // colNo
      "newThresh",                               // aName
      "threshold/setthreshprops",                // fName
      "H:\\repos\\uavrt_detection\\threshold.m", // pName
      0                                          // checkKind
  };
  static rtBoundsCheckInfo nb_emlrtBCI{
      -1,                                        // iFirst
      -1,                                        // iLast
      298,                                       // lineNo
      44,                                        // colNo
      "firstTrueThreshInd",                      // aName
      "threshold/setthreshprops",                // fName
      "H:\\repos\\uavrt_detection\\threshold.m", // pName
      0                                          // checkKind
  };
  static rtBoundsCheckInfo ob_emlrtBCI{
      -1,                                        // iFirst
      -1,                                        // iLast
      298,                                       // lineNo
      23,                                        // colNo
      "newThresh",                               // aName
      "threshold/setthreshprops",                // fName
      "H:\\repos\\uavrt_detection\\threshold.m", // pName
      0                                          // checkKind
  };
  static rtBoundsCheckInfo pb_emlrtBCI{
      -1,                                        // iFirst
      -1,                                        // iLast
      298,                                       // lineNo
      25,                                        // colNo
      "newThresh",                               // aName
      "threshold/setthreshprops",                // fName
      "H:\\repos\\uavrt_detection\\threshold.m", // pName
      0                                          // checkKind
  };
  static rtBoundsCheckInfo qb_emlrtBCI{
      -1,                                        // iFirst
      -1,                                        // iLast
      299,                                       // lineNo
      41,                                        // colNo
      "lastTrueThreshInd",                       // aName
      "threshold/setthreshprops",                // fName
      "H:\\repos\\uavrt_detection\\threshold.m", // pName
      0                                          // checkKind
  };
  static rtBoundsCheckInfo rb_emlrtBCI{
      -1,                                        // iFirst
      -1,                                        // iLast
      299,                                       // lineNo
      23,                                        // colNo
      "newThresh",                               // aName
      "threshold/setthreshprops",                // fName
      "H:\\repos\\uavrt_detection\\threshold.m", // pName
      0                                          // checkKind
  };
  static rtBoundsCheckInfo sb_emlrtBCI{
      -1,                                        // iFirst
      -1,                                        // iLast
      299,                                       // lineNo
      44,                                        // colNo
      "newThresh",                               // aName
      "threshold/setthreshprops",                // fName
      "H:\\repos\\uavrt_detection\\threshold.m", // pName
      0                                          // checkKind
  };
  static rtDoubleCheckInfo t_emlrtDCI{
      148,                                       // lineNo
      17,                                        // colNo
      "threshold/makenewthreshold",              // fName
      "H:\\repos\\uavrt_detection\\threshold.m", // pName
      1                                          // checkKind
  };
  static rtDoubleCheckInfo
      u_emlrtDCI{
          12,       // lineNo
          20,       // colNo
          "blanks", // fName
          "C:\\Program "
          "Files\\MATLAB\\toolbox\\eml\\lib\\matlab\\strfun\\blanks.m", // pName
          4 // checkKind
      };
  static rtEqualityCheckInfo g_emlrtECI{
      -1,                                       // nDims
      298,                                      // lineNo
      13,                                       // colNo
      "threshold/setthreshprops",               // fName
      "H:\\repos\\uavrt_detection\\threshold.m" // pName
  };
  static rtEqualityCheckInfo h_emlrtECI{
      -1,                                       // nDims
      299,                                      // lineNo
      13,                                       // colNo
      "threshold/setthreshprops",               // fName
      "H:\\repos\\uavrt_detection\\threshold.m" // pName
  };
  static rtRunTimeErrorInfo wc_emlrtRTEI{
      48,       // lineNo
      "fprintf" // fName
  };
  static rtRunTimeErrorInfo xc_emlrtRTEI{
      118,       // lineNo
      "cfprintf" // fName
  };
  FILE *filestar;
  coder::b_anonymous_function theFunc;
  coder::sparse Wq;
  coder::array<creal_T, 3U> Ssynth;
  coder::array<creal_T, 2U> b;
  coder::array<creal_T, 2U> xsynth;
  coder::array<double, 2U> b_newThresh;
  coder::array<double, 2U> c_varargin_1;
  coder::array<double, 2U> y;
  coder::array<double, 1U> a__2;
  coder::array<double, 1U> c_newThresh;
  coder::array<double, 1U> newThresh;
  coder::array<double, 1U> values;
  coder::array<int, 2U> b_stftSz;
  coder::array<char, 2U> b_str;
  coder::array<char, 2U> b_varargin_1;
  coder::array<char, 2U> str;
  coder::array<char, 2U> varargin_1;
  coder::array<boolean_T, 1U> x_tmp;
  double stftSz[2];
  double previousToc;
  double s_im;
  double s_re;
  double varargin_2_tmp;
  double varargin_3_tmp;
  double varargin_4_tmp;
  double varargin_5_tmp;
  int b_loop_ub;
  int boffset;
  int i;
  int i1;
  int i2;
  int i3;
  int inner;
  int loop_ub;
  int m;
  int n;
  int nbytes;
  int numRead;
  int tmpOut_f2;
  signed char fileid;
  boolean_T incompleteRead;
  boolean_T overflow;
  theFunc.workspace.pf = pf;
  previousToc = coder::toc();
  s_re = 0.0;
  s_im = 0.0;
  varargin_2_tmp = Wfm->N;
  varargin_3_tmp = Wfm->M;
  varargin_4_tmp = Wfm->J;
  varargin_5_tmp = Wfm->K;
  varargin_1.set_size(1, globalThresholdCachePath.size(1) + 1);
  nbytes = globalThresholdCachePath.size(1);
  for (i = 0; i < nbytes; i++) {
    varargin_1[i] = globalThresholdCachePath[i];
  }
  varargin_1[globalThresholdCachePath.size(1)] = '\x00';
  b_varargin_1.set_size(1, globalThresholdCachePath.size(1) + 1);
  nbytes = globalThresholdCachePath.size(1);
  for (i = 0; i < nbytes; i++) {
    b_varargin_1[i] = globalThresholdCachePath[i];
  }
  b_varargin_1[globalThresholdCachePath.size(1)] = '\x00';
  nbytes = snprintf(nullptr, 0, "%s/N%f-M%f-J%f-K%f-Trials%u.threshold",
                    &b_varargin_1[0], varargin_2_tmp, varargin_3_tmp,
                    varargin_4_tmp, varargin_5_tmp, trials);
  if (nbytes + 1 < 0) {
    rtNonNegativeError(static_cast<double>(nbytes + 1), &u_emlrtDCI);
  }
  str.set_size(1, nbytes + 1);
  snprintf(&str[0], (size_t)(nbytes + 1),
           "%s/N%f-M%f-J%f-K%f-Trials%u.threshold", &varargin_1[0],
           varargin_2_tmp, varargin_3_tmp, varargin_4_tmp, varargin_5_tmp,
           trials);
  if (nbytes < 1) {
    nbytes = 0;
  }
  str.set_size(str.size(0), nbytes);
  fileid = coder::cfopen(str, "rb");
  if (fileid != -1) {
    boolean_T exitg1;
    s_re = 0.0;
    // If formatSpec contains a combination of numeric and character specifiers,
    // then fscanf converts each character to its numeric equivalent. This
    // conversion occurs even when the format explicitly skips all numeric
    // values (for example, formatSpec is '%*d %s').
    values.set_size(0);
    numRead = 1;
    coder::getfilestar(static_cast<double>(fileid), &filestar, &incompleteRead);
    exitg1 = false;
    while ((!exitg1) && (numRead > 0)) {
      tmpOut_f2 = -1;
      numRead = fscanf(filestar, "%lf%n", &s_re, &tmpOut_f2);
      if (tmpOut_f2 != -1) {
        numRead++;
      }
      incompleteRead = (numRead == 0);
      if (numRead > 0) {
        i = values.size(0);
        values.set_size(values.size(0) + 1);
        values[i] = s_re;
        incompleteRead = ((numRead < 2) || incompleteRead);
      }
      if (incompleteRead) {
        exitg1 = true;
      }
    }
    if (values.size(0) < 1) {
      rtDynamicBoundsError(1, 1, values.size(0), &ib_emlrtBCI);
    }
    s_re = values[0];
    if (values.size(0) < 2) {
      rtDynamicBoundsError(2, 1, values.size(0), &hb_emlrtBCI);
    }
    s_im = values[1];
    coder::cfclose(static_cast<double>(fileid));
  } else {
    //  Cache miss
  }
  evMuParam = s_re;
  evSigmaParam = s_im;
  if ((s_re == 0.0) && (s_im == 0.0)) {
    unsigned int u;
    //  Mu and Sigma were not available from the cache. We have to generate them
    //  here.
    // This will be the reference power for the trials. Thresholds will be
    // interpolated for each bin from this value based on their bin power
    // median(freqBinPow);
    stftSz[0] = Wfm->stft->S.size(0);
    stftSz[1] = Wfm->stft->S.size(1);
    printf("\n \t Building time correlation matrix ...");
    fflush(stdout);
    // Build the Wq time correlation matrix
    buildtimecorrelatormatrix(Wfm->N, Wfm->M, Wfm->J, Wfm->K, &Wq);
    s_re = coder::toc() - previousToc;
    printf("complete. Elapsed time: %f seconds \n", s_re);
    fflush(stdout);
    previousToc = coder::toc();
    printf("\t Building synthetic data and taking STFTs ...");
    fflush(stdout);
    i = static_cast<int>(stftSz[1]);
    if (i != Wq.m) {
      rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
    }
    // Here we approximated the number of samples of synthetic noise data needed
    // to get the correct number of time windows. We over estimate here and then
    // clip the number of correct windows after the stft operation.
    // Based on the STFT help file for the number of windows as a function of
    // samples. We add an additional windows worth of samples to ensure we have
    // enough in our STFT output. We'll clip off any excess after the STFT
    u = trials;
    if (static_cast<double>(u) != static_cast<int>(u)) {
      rtIntegerError(static_cast<double>(u), &t_emlrtDCI);
    }
    values.set_size(static_cast<int>(u));
    if (static_cast<double>(u) != static_cast<int>(u)) {
      rtIntegerError(static_cast<double>(u), &t_emlrtDCI);
    }
    nbytes = static_cast<int>(u);
    for (tmpOut_f2 = 0; tmpOut_f2 < nbytes; tmpOut_f2++) {
      values[tmpOut_f2] = 0.0;
    }
    // Preallocate the scores matrix
    // Calculate the total power in the waveform for all frequency bins. Units
    // are W/bin * # bins = W
    coder::wgn((stftSz[1] + 1.0) * Wfm->n_ws + Wfm->n_ol, trials, stftSz[0],
               xsynth);
    // Generate the synthetic data
    coder::stft(xsynth, Wfm->Fs, Wfm->stft->wind, Wfm->n_ol, Wfm->n_w, Ssynth,
                newThresh, a__2);
    b_stftSz.set_size(1, Ssynth.size(1) - i);
    nbytes = Ssynth.size(1) - i;
    for (tmpOut_f2 = 0; tmpOut_f2 < nbytes; tmpOut_f2++) {
      b_stftSz[tmpOut_f2] = (i + tmpOut_f2) + 1;
    }
    coder::internal::nullAssignment(Ssynth, b_stftSz);
    // Trim excess so we have the correct number of windows.
    s_re = coder::toc() - previousToc;
    printf("complete. Elapsed time: %f seconds \n", s_re);
    fflush(stdout);
    previousToc = coder::toc();
    printf("\t Running pulse summing process for all datasets ...");
    fflush(stdout);
    // Preform the incoherent summation using a matrix multiply.
    // Could use pagetimes.m for this, but it isn't supported for
    // code generation with sparse matrices as of R2023a
    if (trials > 4294967294U) {
      coder::b_check_forloop_overflow_error();
    }
    i = static_cast<int>(trials);
    if (i - 1 >= 0) {
      loop_ub = Ssynth.size(0);
      i1 = Ssynth.size(1);
      b_loop_ub = Ssynth.size(1);
      i2 = Ssynth.size(0);
      m = Wfm->W.size(1);
      inner = Wfm->W.size(0);
      n = Ssynth.size(1) - 1;
      i3 = Ssynth.size(1);
      overflow = (Ssynth.size(1) > 2147483646);
    }
    for (int b_i{0}; b_i < i; b_i++) {
      if ((static_cast<int>(b_i + 1U) < 1) ||
          (static_cast<int>(b_i + 1U) > Ssynth.size(2))) {
        rtDynamicBoundsError(static_cast<int>(b_i + 1U), 1, Ssynth.size(2),
                             &kb_emlrtBCI);
      }
      b.set_size(loop_ub, i1);
      for (tmpOut_f2 = 0; tmpOut_f2 < b_loop_ub; tmpOut_f2++) {
        for (nbytes = 0; nbytes < loop_ub; nbytes++) {
          b[nbytes + b.size(0) * tmpOut_f2] =
              Ssynth[(nbytes + Ssynth.size(0) * tmpOut_f2) +
                     Ssynth.size(0) * Ssynth.size(1) * b_i];
        }
      }
      if (Wfm->W.size(0) != i2) {
        if (((Wfm->W.size(0) == 1) && (Wfm->W.size(1) == 1)) ||
            ((Ssynth.size(0) == 1) && (Ssynth.size(1) == 1))) {
          xb_rtErrorWithMessageID(ic_emlrtRTEI.fName, ic_emlrtRTEI.lineNo);
        } else {
          ob_rtErrorWithMessageID(hc_emlrtRTEI.fName, hc_emlrtRTEI.lineNo);
        }
      }
      xsynth.set_size(Wfm->W.size(1), i3);
      if (overflow) {
        coder::check_forloop_overflow_error();
      }
      for (int j{0}; j <= n; j++) {
        numRead = j * m;
        boffset = j * Ssynth.size(0);
        if (m > 2147483646) {
          coder::check_forloop_overflow_error();
        }
        for (int c_i{0}; c_i < m; c_i++) {
          nbytes = c_i * Wfm->W.size(0);
          s_re = 0.0;
          s_im = 0.0;
          if (inner > 2147483646) {
            coder::check_forloop_overflow_error();
          }
          for (int k{0}; k < inner; k++) {
            double Wfm_im;
            double Wfm_re;
            tmpOut_f2 = nbytes + k;
            Wfm_re = Wfm->W[tmpOut_f2].re;
            Wfm_im = -Wfm->W[tmpOut_f2].im;
            tmpOut_f2 = boffset + k;
            s_re += Wfm_re * b[tmpOut_f2].re - Wfm_im * b[tmpOut_f2].im;
            s_im += Wfm_re * b[tmpOut_f2].im + Wfm_im * b[tmpOut_f2].re;
          }
          tmpOut_f2 = numRead + c_i;
          xsynth[tmpOut_f2].re = s_re;
          xsynth[tmpOut_f2].im = s_im;
        }
      }
      boffset = xsynth.size(0) * xsynth.size(1);
      y.set_size(xsynth.size(0), xsynth.size(1));
      if (boffset > 2147483646) {
        coder::check_forloop_overflow_error();
      }
      for (int k{0}; k < boffset; k++) {
        y[k] = rt_hypotd_snf(xsynth[k].re, xsynth[k].im);
      }
      nbytes = y.size(0) * y.size(1);
      for (tmpOut_f2 = 0; tmpOut_f2 < nbytes; tmpOut_f2++) {
        s_re = y[tmpOut_f2];
        y[tmpOut_f2] = s_re * s_re;
      }
      Wq.mtimes(y, c_varargin_1);
      numRead = c_varargin_1.size(0) * c_varargin_1.size(1);
      if ((static_cast<int>(b_i + 1U) < 1) ||
          (static_cast<int>(b_i + 1U) > values.size(0))) {
        rtDynamicBoundsError(static_cast<int>(b_i + 1U), 1, values.size(0),
                             &gb_emlrtBCI);
      }
      a__2 = c_varargin_1.reshape(numRead);
      values[b_i] = coder::internal::unaryMinOrMax_anonFcn1(a__2);
      // 'all' call finds max across all temporal correlation sets and frequency
      // bins just like we do in the dectection code.
    }
    s_re = coder::toc() - previousToc;
    printf("complete. Elapsed time: %f seconds \n", s_re);
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
    nbytes = values.size(0);
    for (i = 0; i < nbytes; i++) {
      values[i] = -values[i];
    }
    coder::evfit(values, stftSz);
    evMuParam = stftSz[0];
    evSigmaParam = stftSz[1];
    varargin_1.set_size(1, globalThresholdCachePath.size(1) + 1);
    nbytes = globalThresholdCachePath.size(1);
    for (i = 0; i < nbytes; i++) {
      varargin_1[i] = globalThresholdCachePath[i];
    }
    varargin_1[globalThresholdCachePath.size(1)] = '\x00';
    b_varargin_1.set_size(1, globalThresholdCachePath.size(1) + 1);
    nbytes = globalThresholdCachePath.size(1);
    for (i = 0; i < nbytes; i++) {
      b_varargin_1[i] = globalThresholdCachePath[i];
    }
    b_varargin_1[globalThresholdCachePath.size(1)] = '\x00';
    nbytes = snprintf(nullptr, 0, "%s/N%f-M%f-J%f-K%f-Trials%u.threshold",
                      &b_varargin_1[0], varargin_2_tmp, varargin_3_tmp,
                      varargin_4_tmp, varargin_5_tmp, trials);
    if (nbytes + 1 < 0) {
      rtNonNegativeError(static_cast<double>(nbytes + 1), &u_emlrtDCI);
    }
    b_str.set_size(1, nbytes + 1);
    snprintf(&b_str[0], (size_t)(nbytes + 1),
             "%s/N%f-M%f-J%f-K%f-Trials%u.threshold", &varargin_1[0],
             varargin_2_tmp, varargin_3_tmp, varargin_4_tmp, varargin_5_tmp,
             trials);
    if (nbytes < 1) {
      nbytes = 0;
    }
    b_str.set_size(b_str.size(0), nbytes);
    fileid = coder::cfopen(b_str, "wb");
    if (fileid == -1) {
      varargin_1.set_size(1, b_str.size(1) + 1);
      nbytes = b_str.size(1);
      for (i = 0; i < nbytes; i++) {
        varargin_1[i] = b_str[i];
      }
      varargin_1[b_str.size(1)] = '\x00';
      printf("threshold::saveThresholdValuesToCache ERROR - Unable to open "
             "file %s\n",
             &varargin_1[0]);
      fflush(stdout);
    } else {
      FILE *b_NULL;
      if (fileid == 0) {
        g_rtErrorWithMessageID(wc_emlrtRTEI.fName, wc_emlrtRTEI.lineNo);
      }
      b_NULL = NULL;
      coder::getfilestar(static_cast<double>(fileid), &filestar,
                         &incompleteRead);
      if (filestar == b_NULL) {
        c_rtErrorWithMessageID(xc_emlrtRTEI.fName, xc_emlrtRTEI.lineNo);
      } else {
        fprintf(filestar, "%f\n", stftSz[0]);
        if (incompleteRead) {
          fflush(filestar);
        }
      }
      if (fileid == 0) {
        g_rtErrorWithMessageID(wc_emlrtRTEI.fName, wc_emlrtRTEI.lineNo);
      }
      b_NULL = NULL;
      coder::getfilestar(static_cast<double>(fileid), &filestar,
                         &incompleteRead);
      if (filestar == b_NULL) {
        c_rtErrorWithMessageID(xc_emlrtRTEI.fName, xc_emlrtRTEI.lineNo);
      } else {
        fprintf(filestar, "%f\n", stftSz[1]);
        if (incompleteRead) {
          fflush(filestar);
        }
      }
      coder::cfclose(static_cast<double>(fileid));
    }
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
  } else {
    printf("Threshold values were pulled from cache\n");
    fflush(stdout);
  }
  theFunc.workspace.mu = evMuParam;
  theFunc.workspace.sigma = evSigmaParam;
  // theFunc = @(x) 1-exp(-exp((x-mu)/sigma));%Equivalent to evcdf(x,mu,sigma)
  // theFunc = @(x) exp(-exp((x-mu)/sigma));%Equivalent to 1-evcdf(x,mu,sigma)
  // Equivalent to 1-evcdf(x,mu,sigma)-pf
  s_im = coder::fzero(theFunc);
  // theFunc monitonically decrease, so starting at x = 0 should always converge
  s_re = coder::toc() - previousToc;
  printf("complete. Elapsed time: %f seconds \n", s_re);
  fflush(stdout);
  coder::toc();
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
  values.set_size(Wfm->stft->psd.size(0));
  nbytes = Wfm->stft->psd.size(0);
  for (i = 0; i < nbytes; i++) {
    values[i] = Wfm->stft->psd[i];
  }
  // Extract psd for current waveform. Units are W/Hz
  i = Wfm->stft->f.size(0);
  if (i < 2) {
    rtDynamicBoundsError(2, 1, i, &fb_emlrtBCI);
  }
  i = Wfm->stft->f.size(0);
  if (i < 1) {
    rtDynamicBoundsError(1, 1, i, &jb_emlrtBCI);
  }
  s_re = Wfm->stft->f[1] - Wfm->stft->f[0];
  // PSD (W/Hz) times bin width (Hz/bin) gives bin total power in (W/bin)
  // 1W standard
  nbytes = values.size(0);
  for (i = 0; i < nbytes; i++) {
    values[i] = values[i] * s_re;
  }
  newThresh.set_size(values.size(0));
  nbytes = values.size(0);
  for (i = 0; i < nbytes; i++) {
    newThresh[i] = 0.0;
  }
  if (values.size(0) != 0) {
    stftSz[0] = 0.0;
    stftSz[1] = s_im;
    coder::interp1Linear(stftSz, values, newThresh);
  }
  // Finally,extrapolating the thresholds that are a little beyond the original
  // frequeny range can result in negative thresholds. Here we copy the first
  // and last valid threshold out to the places where the extrapolations would
  // have occured
  x_tmp.set_size(newThresh.size(0));
  nbytes = newThresh.size(0);
  for (i = 0; i < nbytes; i++) {
    x_tmp[i] = std::isnan(newThresh[i]);
  }
  nbytes = x_tmp.size(0);
  for (i = 0; i < nbytes; i++) {
    x_tmp[i] = !x_tmp[i];
  }
  coder::c_eml_find(x_tmp, (int *)&numRead, &boffset);
  tmpOut_f2 = boffset;
  for (i = 0; i < boffset; i++) {
    nbytes = numRead;
  }
  coder::d_eml_find(x_tmp, (int *)&numRead, &boffset);
  for (i = 0; i < tmpOut_f2; i++) {
    if ((nbytes < 1) || (nbytes > newThresh.size(0))) {
      rtDynamicBoundsError(nbytes, 1, newThresh.size(0), &lb_emlrtBCI);
    }
  }
  for (i = 0; i < boffset; i++) {
    if ((numRead < 1) || (numRead > newThresh.size(0))) {
      rtDynamicBoundsError(numRead, 1, newThresh.size(0), &mb_emlrtBCI);
    }
    s_re = newThresh[numRead - 1];
  }
  if (tmpOut_f2 < 1) {
    rtDynamicBoundsError(1, 1, tmpOut_f2, &nb_emlrtBCI);
  }
  if (newThresh.size(0) < 1) {
    rtDynamicBoundsError(1, 1, newThresh.size(0), &ob_emlrtBCI);
  }
  if ((nbytes < 1) || (nbytes > newThresh.size(0))) {
    rtDynamicBoundsError(nbytes, 1, newThresh.size(0), &pb_emlrtBCI);
  }
  if (nbytes != tmpOut_f2) {
    rtSizeEq1DError(nbytes, tmpOut_f2, &g_emlrtECI);
  }
  b_newThresh.set_size(1, nbytes);
  for (i = 0; i < nbytes; i++) {
    b_newThresh[i] = newThresh[nbytes - 1];
  }
  nbytes = b_newThresh.size(1);
  for (i = 0; i < nbytes; i++) {
    newThresh[i] = b_newThresh[i];
  }
  // The (1) call is needed by coder, as it doesn't know that the find call
  // above will only produced a scalar output.
  if (boffset < 1) {
    rtDynamicBoundsError(1, 1, boffset, &qb_emlrtBCI);
  }
  if (numRead > newThresh.size(0)) {
    i = -1;
    tmpOut_f2 = -1;
  } else {
    if ((numRead < 1) || (numRead > newThresh.size(0))) {
      rtDynamicBoundsError(numRead, 1, newThresh.size(0), &rb_emlrtBCI);
    }
    i = numRead - 2;
    if (newThresh.size(0) < 1) {
      rtDynamicBoundsError(newThresh.size(0), 1, newThresh.size(0),
                           &sb_emlrtBCI);
    }
    tmpOut_f2 = newThresh.size(0) - 1;
  }
  nbytes = tmpOut_f2 - i;
  if (nbytes != boffset) {
    rtSizeEq1DError(nbytes, boffset, &h_emlrtECI);
  }
  for (tmpOut_f2 = 0; tmpOut_f2 < nbytes; tmpOut_f2++) {
    newThresh[(i + tmpOut_f2) + 1] = s_re;
  }
  // The (1) call is needed by coder, as it doesn't know that the find call
  // above will only produced a scalar output. toc
  coder::internal::validator_check_size(newThresh, c_newThresh);
  coder::interp1(Wfm->stft->f, newThresh, Wfm->Wf, values);
  coder::internal::validator_check_size(values, threshVecFine);
}

//
// File trailer for threshold.cpp
//
// [EOF]
//
