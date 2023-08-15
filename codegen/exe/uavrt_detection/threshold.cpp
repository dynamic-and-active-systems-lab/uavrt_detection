//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: threshold.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 15-Aug-2023 14:57:30
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
#include "waveform.h"
#include "wfmstft.h"
#include "wgn.h"
#include "coder_array.h"
#include <cmath>
#include <cstddef>
#include <cstdio>

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
// Arguments    : const waveform &Wfm
// Return Type  : void
//
void threshold::makenewthreshold(const waveform &Wfm)
{
  static rtBoundsCheckInfo ab_emlrtBCI{
      -1,                           // iFirst
      -1,                           // iLast
      163,                          // lineNo
      28,                           // colNo
      "scores",                     // aName
      "threshold/makenewthreshold", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/threshold.m", // pName
      0                                              // checkKind
  };
  static rtBoundsCheckInfo bb_emlrtBCI{
      -1,                                       // iFirst
      -1,                                       // iLast
      340,                                      // lineNo
      37,                                       // colNo
      "values",                                 // aName
      "threshold/loadThresholdValuesFromCache", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/threshold.m", // pName
      0                                              // checkKind
  };
  static rtBoundsCheckInfo cb_emlrtBCI{
      -1,                                       // iFirst
      -1,                                       // iLast
      339,                                      // lineNo
      37,                                       // colNo
      "values",                                 // aName
      "threshold/loadThresholdValuesFromCache", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/threshold.m", // pName
      0                                              // checkKind
  };
  static rtBoundsCheckInfo db_emlrtBCI{
      -1,                           // iFirst
      -1,                           // iLast
      163,                          // lineNo
      59,                           // colNo
      "Ssynth",                     // aName
      "threshold/makenewthreshold", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/threshold.m", // pName
      0                                              // checkKind
  };
  static rtBoundsCheckInfo eb_emlrtBCI{
      -1,                         // iFirst
      -1,                         // iLast
      282,                        // lineNo
      63,                         // colNo
      "Wfm.stft.f",               // aName
      "threshold/setthreshprops", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/threshold.m", // pName
      0                                              // checkKind
  };
  static rtBoundsCheckInfo fb_emlrtBCI{
      -1,                         // iFirst
      -1,                         // iLast
      296,                        // lineNo
      44,                         // colNo
      "newThresh",                // aName
      "threshold/setthreshprops", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/threshold.m", // pName
      0                                              // checkKind
  };
  static rtBoundsCheckInfo gb_emlrtBCI{
      -1,                         // iFirst
      -1,                         // iLast
      297,                        // lineNo
      44,                         // colNo
      "newThresh",                // aName
      "threshold/setthreshprops", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/threshold.m", // pName
      0                                              // checkKind
  };
  static rtBoundsCheckInfo hb_emlrtBCI{
      -1,                         // iFirst
      -1,                         // iLast
      298,                        // lineNo
      44,                         // colNo
      "firstTrueThreshInd",       // aName
      "threshold/setthreshprops", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/threshold.m", // pName
      0                                              // checkKind
  };
  static rtBoundsCheckInfo ib_emlrtBCI{
      -1,                         // iFirst
      -1,                         // iLast
      298,                        // lineNo
      23,                         // colNo
      "newThresh",                // aName
      "threshold/setthreshprops", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/threshold.m", // pName
      0                                              // checkKind
  };
  static rtBoundsCheckInfo jb_emlrtBCI{
      -1,                         // iFirst
      -1,                         // iLast
      298,                        // lineNo
      25,                         // colNo
      "newThresh",                // aName
      "threshold/setthreshprops", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/threshold.m", // pName
      0                                              // checkKind
  };
  static rtBoundsCheckInfo kb_emlrtBCI{
      -1,                         // iFirst
      -1,                         // iLast
      299,                        // lineNo
      41,                         // colNo
      "lastTrueThreshInd",        // aName
      "threshold/setthreshprops", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/threshold.m", // pName
      0                                              // checkKind
  };
  static rtBoundsCheckInfo lb_emlrtBCI{
      -1,                         // iFirst
      -1,                         // iLast
      299,                        // lineNo
      23,                         // colNo
      "newThresh",                // aName
      "threshold/setthreshprops", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/threshold.m", // pName
      0                                              // checkKind
  };
  static rtBoundsCheckInfo mb_emlrtBCI{
      -1,                         // iFirst
      -1,                         // iLast
      299,                        // lineNo
      44,                         // colNo
      "newThresh",                // aName
      "threshold/setthreshprops", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/threshold.m", // pName
      0                                              // checkKind
  };
  static rtBoundsCheckInfo y_emlrtBCI{
      -1,                         // iFirst
      -1,                         // iLast
      282,                        // lineNo
      49,                         // colNo
      "Wfm.stft.f",               // aName
      "threshold/setthreshprops", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/threshold.m", // pName
      0                                              // checkKind
  };
  static rtDoubleCheckInfo
      q_emlrtDCI{
          12,       // lineNo
          20,       // colNo
          "blanks", // fName
          "/Applications/MATLAB_R2023a.app/toolbox/eml/lib/matlab/strfun/"
          "blanks.m", // pName
          4           // checkKind
      };
  static rtDoubleCheckInfo r_emlrtDCI{
      148,                          // lineNo
      17,                           // colNo
      "threshold/makenewthreshold", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/threshold.m", // pName
      1                                              // checkKind
  };
  static rtEqualityCheckInfo g_emlrtECI{
      -1,                         // nDims
      298,                        // lineNo
      13,                         // colNo
      "threshold/setthreshprops", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/threshold.m" // pName
  };
  static rtEqualityCheckInfo h_emlrtECI{
      -1,                         // nDims
      299,                        // lineNo
      13,                         // colNo
      "threshold/setthreshprops", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/threshold.m" // pName
  };
  static rtRunTimeErrorInfo
      qc_emlrtRTEI{
          48,        // lineNo
          5,         // colNo
          "fprintf", // fName
          "/Applications/MATLAB_R2023a.app/toolbox/eml/lib/matlab/iofun/"
          "fprintf.m" // pName
      };
  static rtRunTimeErrorInfo
      rc_emlrtRTEI{
          125,        // lineNo
          17,         // colNo
          "cfprintf", // fName
          "/Applications/MATLAB_R2023a.app/toolbox/eml/lib/matlab/iofun/"
          "fprintf.m" // pName
      };
  std::FILE *f;
  coder::b_anonymous_function theFunc;
  coder::sparse Wq;
  coder::array<creal_T, 3U> Ssynth;
  coder::array<creal_T, 2U> b;
  coder::array<creal_T, 2U> xsynth;
  coder::array<creal_T, 2U> y;
  coder::array<double, 2U> b_newThresh;
  coder::array<double, 2U> b_y;
  coder::array<double, 2U> c_varargin_1;
  coder::array<double, 2U> r;
  coder::array<double, 1U> a__2;
  coder::array<double, 1U> b_Wfm;
  coder::array<double, 1U> newThresh;
  coder::array<double, 1U> values;
  coder::array<int, 2U> b_stftSz;
  coder::array<char, 2U> b_str;
  coder::array<char, 2U> b_varargin_1;
  coder::array<char, 2U> str;
  coder::array<char, 2U> varargin_1;
  coder::array<boolean_T, 1U> x_tmp;
  double stftSz[2];
  double nSamps;
  double previousToc;
  double s_im;
  double varargin_2;
  double varargin_3;
  double varargin_4;
  double varargin_5;
  int i;
  int ii_data;
  int inner;
  int k;
  int loop_ub;
  int n;
  int nbytes;
  int numRead;
  signed char fileid;
  boolean_T incompleteRead;
  boolean_T overflow;
  theFunc.workspace.pf = pf;
  previousToc = coder::toc();
  nSamps = 0.0;
  s_im = 0.0;
  varargin_2 = Wfm.N;
  varargin_3 = Wfm.M;
  varargin_4 = Wfm.J;
  varargin_5 = Wfm.K;
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
  nbytes = std::snprintf(nullptr, 0, "%s/N%f-M%f-J%f-K%f-Trials%u.threshold",
                         &b_varargin_1[0], varargin_2, varargin_3, varargin_4,
                         varargin_5, trials);
  if (nbytes + 1 < 0) {
    rtNonNegativeError(static_cast<double>(nbytes + 1), q_emlrtDCI);
  }
  str.set_size(1, nbytes + 1);
  std::snprintf(&str[0], (size_t)(nbytes + 1),
                "%s/N%f-M%f-J%f-K%f-Trials%u.threshold", &varargin_1[0],
                varargin_2, varargin_3, varargin_4, varargin_5, trials);
  if (nbytes < 1) {
    nbytes = 0;
  }
  str.set_size(str.size(0), nbytes);
  fileid = coder::internal::cfopen(str, "rb");
  if (fileid != -1) {
    boolean_T exitg1;
    nSamps = 0.0;
    // If formatSpec contains a combination of numeric and character specifiers,
    // then fscanf converts each character to its numeric equivalent. This
    // conversion occurs even when the format explicitly skips all numeric
    // values (for example, formatSpec is '%*d %s').
    values.set_size(0);
    numRead = 1;
    f = coder::internal::getfilestar(static_cast<double>(fileid),
                                     incompleteRead);
    exitg1 = false;
    while ((!exitg1) && (numRead > 0)) {
      nbytes = -1;
      numRead = std::fscanf(f, "%lf%n", &nSamps, &nbytes);
      if (nbytes != -1) {
        numRead++;
      }
      incompleteRead = (numRead == 0);
      if (numRead > 0) {
        i = values.size(0);
        values.set_size(values.size(0) + 1);
        values[i] = nSamps;
        incompleteRead = ((numRead < 2) || incompleteRead);
      }
      if (incompleteRead) {
        exitg1 = true;
      }
    }
    if (values.size(0) < 1) {
      rtDynamicBoundsError(1, 1, values.size(0), cb_emlrtBCI);
    }
    nSamps = values[0];
    if (values.size(0) < 2) {
      rtDynamicBoundsError(2, 1, values.size(0), bb_emlrtBCI);
    }
    s_im = values[1];
    coder::internal::cfclose(static_cast<double>(fileid));
  } else {
    //  Cache miss
  }
  evMuParam = nSamps;
  evSigmaParam = s_im;
  if ((nSamps == 0.0) && (s_im == 0.0)) {
    unsigned int u;
    //  Mu and Sigma were not available from the cache. We have to generate them
    //  here.
    // This will be the reference power for the trials. Thresholds will be
    // interpolated for each bin from this value based on their bin power
    // median(freqBinPow);
    stftSz[0] = Wfm.stft->S.size(0);
    stftSz[1] = Wfm.stft->S.size(1);
    std::printf("\n \t Building time correlation matrix ...");
    std::fflush(stdout);
    // Build the Wq time correlation matrix
    buildtimecorrelatormatrix(Wfm.N, Wfm.M, Wfm.J, Wfm.K, Wq);
    nSamps = coder::toc() - previousToc;
    std::printf("complete. Elapsed time: %f seconds \n", nSamps);
    std::fflush(stdout);
    previousToc = coder::toc();
    std::printf("\t Building synthetic data and taking STFTs ...");
    std::fflush(stdout);
    i = static_cast<int>(stftSz[1]);
    if (i != Wq.m) {
      rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
    }
    // Here we approximated the number of samples of synthetic noise data needed
    // to get the correct number of time windows. We over estimate here and then
    // clip the number of correct windows after the stft operation.
    nSamps = (stftSz[1] + 1.0) * Wfm.n_ws + Wfm.n_ol;
    // Based on the STFT help file for the number of windows as a function of
    // samples. We add an additional windows worth of samples to ensure we have
    // enough in our STFT output. We'll clip off any excess after the STFT
    u = trials;
    if (static_cast<double>(u) != static_cast<int>(u)) {
      rtIntegerError(static_cast<double>(u), r_emlrtDCI);
    }
    nbytes = static_cast<int>(u);
    values.set_size(nbytes);
    if (static_cast<double>(u) != static_cast<int>(u)) {
      rtIntegerError(static_cast<double>(u), r_emlrtDCI);
    }
    for (k = 0; k < nbytes; k++) {
      values[k] = 0.0;
    }
    // Preallocate the scores matrix
    // Calculate the total power in the waveform for all frequency bins. Units
    // are W/bin * # bins = W
    coder::wgn(nSamps, trials, stftSz[0], xsynth);
    // Generate the synthetic data
    b_Wfm.set_size(Wfm.stft->wind.size(0));
    nbytes = Wfm.stft->wind.size(0) - 1;
    for (k = 0; k <= nbytes; k++) {
      b_Wfm[k] = Wfm.stft->wind[k];
    }
    coder::stft(xsynth, Wfm.Fs, b_Wfm, Wfm.n_ol, Wfm.n_w, Ssynth, newThresh,
                a__2);
    nbytes = Ssynth.size(1) - i;
    b_stftSz.set_size(1, nbytes);
    for (k = 0; k < nbytes; k++) {
      b_stftSz[k] = (i + k) + 1;
    }
    coder::internal::nullAssignment(Ssynth, b_stftSz);
    // Trim excess so we have the correct number of windows.
    nSamps = coder::toc() - previousToc;
    std::printf("complete. Elapsed time: %f seconds \n", nSamps);
    std::fflush(stdout);
    previousToc = coder::toc();
    std::printf("\t Running pulse summing process for all datasets ...");
    std::fflush(stdout);
    // Preform the incoherent summation using a matrix multiply.
    // Could use pagetimes.m for this, but it isn't supported for
    // code generation with sparse matrices as of R2023a
    if (trials > 4294967294U) {
      coder::b_check_forloop_overflow_error();
    }
    i = static_cast<int>(trials);
    if (i - 1 >= 0) {
      loop_ub = Ssynth.size(1);
      n = Ssynth.size(1);
      overflow = (Ssynth.size(1) > 2147483646);
    }
    for (int b_i{0}; b_i < i; b_i++) {
      xsynth.set_size(Wfm.W.size(0), Wfm.W.size(1));
      nbytes = Wfm.W.size(0) * Wfm.W.size(1);
      for (k = 0; k < nbytes; k++) {
        xsynth[k] = Wfm.W[k];
      }
      if ((static_cast<int>(static_cast<unsigned int>(b_i) + 1U) < 1) ||
          (static_cast<int>(static_cast<unsigned int>(b_i) + 1U) >
           Ssynth.size(2))) {
        rtDynamicBoundsError(
            static_cast<int>(static_cast<unsigned int>(b_i) + 1U), 1,
            Ssynth.size(2), db_emlrtBCI);
      }
      b.set_size(Ssynth.size(0), Ssynth.size(1));
      for (k = 0; k < loop_ub; k++) {
        nbytes = Ssynth.size(0);
        for (numRead = 0; numRead < nbytes; numRead++) {
          b[numRead + b.size(0) * k] =
              Ssynth[(numRead + Ssynth.size(0) * k) +
                     Ssynth.size(0) * Ssynth.size(1) * b_i];
        }
      }
      if (xsynth.size(0) != Ssynth.size(0)) {
        if (((xsynth.size(0) == 1) && (xsynth.size(1) == 1)) ||
            ((Ssynth.size(0) == 1) && (Ssynth.size(1) == 1))) {
          xb_rtErrorWithMessageID(bc_emlrtRTEI.fName, bc_emlrtRTEI.lineNo);
        } else {
          ob_rtErrorWithMessageID(ac_emlrtRTEI.fName, ac_emlrtRTEI.lineNo);
        }
      }
      ii_data = xsynth.size(1);
      inner = xsynth.size(0);
      y.set_size(xsynth.size(1), Ssynth.size(1));
      if (overflow) {
        coder::check_forloop_overflow_error();
      }
      for (int j{0}; j < n; j++) {
        int boffset;
        int coffset;
        coffset = j * ii_data;
        boffset = j * Ssynth.size(0);
        if (ii_data > 2147483646) {
          coder::check_forloop_overflow_error();
        }
        for (int c_i{0}; c_i < ii_data; c_i++) {
          numRead = c_i * xsynth.size(0);
          nSamps = 0.0;
          s_im = 0.0;
          if (inner > 2147483646) {
            coder::check_forloop_overflow_error();
          }
          for (k = 0; k < inner; k++) {
            nbytes = numRead + k;
            varargin_2 = xsynth[nbytes].re;
            varargin_3 = -xsynth[nbytes].im;
            nbytes = boffset + k;
            varargin_4 = b[nbytes].im;
            varargin_5 = b[nbytes].re;
            nSamps += varargin_2 * varargin_5 - varargin_3 * varargin_4;
            s_im += varargin_2 * varargin_4 + varargin_3 * varargin_5;
          }
          k = coffset + c_i;
          y[k].re = nSamps;
          y[k].im = s_im;
        }
      }
      nbytes = y.size(0) * y.size(1);
      b_y.set_size(y.size(0), y.size(1));
      if (nbytes > 2147483646) {
        coder::check_forloop_overflow_error();
      }
      for (k = 0; k < nbytes; k++) {
        b_y[k] = rt_hypotd_snf(y[k].re, y[k].im);
      }
      r.set_size(b_y.size(0), b_y.size(1));
      nbytes = b_y.size(0) * b_y.size(1);
      for (k = 0; k < nbytes; k++) {
        nSamps = b_y[k];
        r[k] = nSamps * nSamps;
      }
      Wq.mtimes(r, c_varargin_1);
      nbytes = c_varargin_1.size(0) * c_varargin_1.size(1);
      if ((static_cast<int>(static_cast<unsigned int>(b_i) + 1U) < 1) ||
          (static_cast<int>(static_cast<unsigned int>(b_i) + 1U) >
           values.size(0))) {
        rtDynamicBoundsError(
            static_cast<int>(static_cast<unsigned int>(b_i) + 1U), 1,
            values.size(0), ab_emlrtBCI);
      }
      a__2 = c_varargin_1.reshape(nbytes);
      values[b_i] = coder::internal::unaryMinOrMax_anonFcn1(a__2);
      // 'all' call finds max across all temporal correlation sets and frequency
      // bins just like we do in the dectection code.
    }
    nSamps = coder::toc() - previousToc;
    std::printf("complete. Elapsed time: %f seconds \n", nSamps);
    std::fflush(stdout);
    previousToc = coder::toc();
    std::printf("\t Extracing extreme value fit parameters ...");
    std::fflush(stdout);
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
    varargin_2 = Wfm.N;
    varargin_3 = Wfm.M;
    varargin_4 = Wfm.J;
    varargin_5 = Wfm.K;
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
    nbytes = std::snprintf(nullptr, 0, "%s/N%f-M%f-J%f-K%f-Trials%u.threshold",
                           &b_varargin_1[0], varargin_2, varargin_3, varargin_4,
                           varargin_5, trials);
    if (nbytes + 1 < 0) {
      rtNonNegativeError(static_cast<double>(nbytes + 1), q_emlrtDCI);
    }
    b_str.set_size(1, nbytes + 1);
    std::snprintf(&b_str[0], (size_t)(nbytes + 1),
                  "%s/N%f-M%f-J%f-K%f-Trials%u.threshold", &varargin_1[0],
                  varargin_2, varargin_3, varargin_4, varargin_5, trials);
    if (nbytes < 1) {
      nbytes = 0;
    }
    b_str.set_size(b_str.size(0), nbytes);
    fileid = coder::internal::cfopen(b_str, "wb");
    if (fileid == -1) {
      varargin_1.set_size(1, b_str.size(1) + 1);
      nbytes = b_str.size(1);
      for (i = 0; i < nbytes; i++) {
        varargin_1[i] = b_str[i];
      }
      varargin_1[b_str.size(1)] = '\x00';
      std::printf("threshold::saveThresholdValuesToCache ERROR - Unable to "
                  "open file %s\n",
                  &varargin_1[0]);
      std::fflush(stdout);
    } else {
      if (fileid == 0) {
        g_rtErrorWithMessageID(qc_emlrtRTEI.fName, qc_emlrtRTEI.lineNo);
      }
      f = coder::internal::getfilestar(static_cast<double>(fileid),
                                       incompleteRead);
      if (f == nullptr) {
        c_rtErrorWithMessageID(rc_emlrtRTEI.fName, rc_emlrtRTEI.lineNo);
      } else {
        std::fprintf(f, "%f\n", stftSz[0]);
        if (incompleteRead) {
          std::fflush(f);
        }
      }
      if (fileid == 0) {
        g_rtErrorWithMessageID(qc_emlrtRTEI.fName, qc_emlrtRTEI.lineNo);
      }
      f = coder::internal::getfilestar(static_cast<double>(fileid),
                                       incompleteRead);
      if (f == nullptr) {
        c_rtErrorWithMessageID(rc_emlrtRTEI.fName, rc_emlrtRTEI.lineNo);
      } else {
        std::fprintf(f, "%f\n", stftSz[1]);
        if (incompleteRead) {
          std::fflush(f);
        }
      }
      coder::internal::cfclose(static_cast<double>(fileid));
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
    std::printf("Threshold values were pulled from cache\n");
    std::fflush(stdout);
  }
  theFunc.workspace.mu = evMuParam;
  theFunc.workspace.sigma = evSigmaParam;
  // theFunc = @(x) 1-exp(-exp((x-mu)/sigma));%Equivalent to evcdf(x,mu,sigma)
  // theFunc = @(x) exp(-exp((x-mu)/sigma));%Equivalent to 1-evcdf(x,mu,sigma)
  // Equivalent to 1-evcdf(x,mu,sigma)-pf
  s_im = coder::fzero(theFunc);
  // theFunc monitonically decrease, so starting at x = 0 should always converge
  nSamps = coder::toc() - previousToc;
  std::printf("complete. Elapsed time: %f seconds \n", nSamps);
  std::fflush(stdout);
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
  values.set_size(Wfm.stft->psd.size(0));
  nbytes = Wfm.stft->psd.size(0);
  for (i = 0; i < nbytes; i++) {
    values[i] = Wfm.stft->psd[i];
  }
  // Extract psd for current waveform. Units are W/Hz
  i = Wfm.stft->f.size(0);
  if (i < 2) {
    rtDynamicBoundsError(2, 1, i, y_emlrtBCI);
  }
  i = Wfm.stft->f.size(0);
  if (i < 1) {
    rtDynamicBoundsError(1, 1, i, eb_emlrtBCI);
  }
  nSamps = Wfm.stft->f[1] - Wfm.stft->f[0];
  // PSD (W/Hz) times bin width (Hz/bin) gives bin total power in (W/bin)
  // 1W standard
  nbytes = values.size(0);
  for (i = 0; i < nbytes; i++) {
    values[i] = values[i] * nSamps;
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
    x_tmp[i] = !std::isnan(newThresh[i]);
  }
  inner = coder::c_eml_find(x_tmp, (int *)&ii_data);
  numRead = inner;
  for (i = 0; i < inner; i++) {
    nbytes = ii_data;
  }
  inner = coder::d_eml_find(x_tmp, (int *)&ii_data);
  for (i = 0; i < numRead; i++) {
    if ((nbytes < 1) || (nbytes > newThresh.size(0))) {
      rtDynamicBoundsError(nbytes, 1, newThresh.size(0), fb_emlrtBCI);
    }
  }
  for (i = 0; i < inner; i++) {
    if ((ii_data < 1) || (ii_data > newThresh.size(0))) {
      rtDynamicBoundsError(ii_data, 1, newThresh.size(0), gb_emlrtBCI);
    }
    nSamps = newThresh[ii_data - 1];
  }
  if (numRead < 1) {
    rtDynamicBoundsError(1, 1, numRead, hb_emlrtBCI);
  }
  if (newThresh.size(0) < 1) {
    rtDynamicBoundsError(1, 1, newThresh.size(0), ib_emlrtBCI);
  }
  if ((nbytes < 1) || (nbytes > newThresh.size(0))) {
    rtDynamicBoundsError(nbytes, 1, newThresh.size(0), jb_emlrtBCI);
  }
  if (nbytes != numRead) {
    rtSizeEq1DError(nbytes, numRead, g_emlrtECI);
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
  if (inner < 1) {
    rtDynamicBoundsError(1, 1, inner, kb_emlrtBCI);
  }
  if (ii_data > newThresh.size(0)) {
    i = 0;
    k = 0;
  } else {
    if ((ii_data < 1) || (ii_data > newThresh.size(0))) {
      rtDynamicBoundsError(ii_data, 1, newThresh.size(0), lb_emlrtBCI);
    }
    i = ii_data - 1;
    if (newThresh.size(0) < 1) {
      rtDynamicBoundsError(newThresh.size(0), 1, newThresh.size(0),
                           mb_emlrtBCI);
    }
    k = newThresh.size(0);
  }
  nbytes = k - i;
  if (nbytes != inner) {
    rtSizeEq1DError(nbytes, inner, h_emlrtECI);
  }
  for (k = 0; k < nbytes; k++) {
    newThresh[i + k] = nSamps;
  }
  // The (1) call is needed by coder, as it doesn't know that the find call
  // above will only produced a scalar output. toc
  b_Wfm.set_size(Wfm.stft->f.size(0));
  nbytes = Wfm.stft->f.size(0) - 1;
  for (i = 0; i <= nbytes; i++) {
    b_Wfm[i] = Wfm.stft->f[i];
  }
  values.set_size(Wfm.Wf.size(0));
  nbytes = Wfm.Wf.size(0) - 1;
  for (i = 0; i <= nbytes; i++) {
    values[i] = Wfm.Wf[i];
  }
  coder::interp1(b_Wfm, newThresh, values, threshVecFine);
}

//
// File trailer for threshold.cpp
//
// [EOF]
//
