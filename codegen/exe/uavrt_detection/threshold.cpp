//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: threshold.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "threshold.h"
#include "abs.h"
#include "anonymous_function.h"
#include "buildtimecorrelatormatrix.h"
#include "eml_int_forloop_overflow_check.h"
#include "eml_mtimes_helper.h"
#include "evfit.h"
#include "fileManager.h"
#include "find.h"
#include "fscanf.h"
#include "fzero.h"
#include "interp1.h"
#include "mtimes.h"
#include "nullAssignment.h"
#include "repetitionrejector.h"
#include "rt_nonfinite.h"
#include "sparse1.h"
#include "sprintf.h"
#include "stft.h"
#include "string1.h"
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
#include <cstdio>

// Function Definitions
//
// THRESHOLD Constructs an instance of this class
// INPUTS:
//    pf  probability of false alarm
//
//
// Arguments    : double b_pf
// Return Type  : void
//
void threshold::init(double b_pf)
{
  trials = 100U;
  pf = b_pf;
  evMuParam = 0.0;
  evSigmaParam = 0.0;
  thresh1W = 0.0;
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
// Arguments    : waveform &Wfm
// Return Type  : void
//
void threshold::makenewthreshold(waveform &Wfm)
{
  static rtBoundsCheckInfo ab_emlrtBCI{
      309,                                     // lineNo
      "values",                                // aName
      "threshold/loadThresholdValuesFromCache" // fName
  };
  static rtBoundsCheckInfo bb_emlrtBCI{
      310,                                     // lineNo
      "values",                                // aName
      "threshold/loadThresholdValuesFromCache" // fName
  };
  static rtBoundsCheckInfo cb_emlrtBCI{
      165,                         // lineNo
      "Ssynth",                    // aName
      "threshold/makenewthreshold" // fName
  };
  static rtBoundsCheckInfo db_emlrtBCI{
      165,                         // lineNo
      "scores",                    // aName
      "threshold/makenewthreshold" // fName
  };
  static rtDoubleCheckInfo q_emlrtDCI{
      148,                         // lineNo
      "threshold/makenewthreshold" // fName
  };
  std::FILE *f;
  coder::b_anonymous_function theFunc;
  coder::rtString filename;
  coder::sparse Wq;
  coder::sparse serialRejectionMatrix;
  coder::array<creal_T, 3U> Ssynth;
  coder::array<creal_T, 2U> b;
  coder::array<creal_T, 2U> xsynth;
  coder::array<creal_T, 2U> y;
  coder::array<double, 2U> a;
  coder::array<double, 2U> b_varargin_1;
  coder::array<double, 2U> r;
  coder::array<double, 1U> b_Wfm;
  coder::array<double, 1U> c_varargin_1;
  coder::array<double, 1U> scores;
  coder::array<double, 1U> tStft;
  coder::array<double, 1U> values;
  coder::array<int, 2U> b_nTimeWinds;
  coder::array<char, 2U> varargin_1;
  double PF;
  double nSamps;
  double previousToc;
  double threshMedPow;
  int i;
  int loop_ub;
  signed char fileid;
  boolean_T autoflush;
  PF = pf;
  previousToc = coder::toc();
  nSamps = 0.0;
  threshMedPow = 0.0;
  varargin_1.set_size(1, globalThresholdCachePath.size(1));
  loop_ub =
      globalThresholdCachePath.size(0) * globalThresholdCachePath.size(1) - 1;
  for (i = 0; i <= loop_ub; i++) {
    varargin_1[i] = globalThresholdCachePath[i];
  }
  coder::b_sprintf(varargin_1, Wfm.N, Wfm.M, Wfm.J, Wfm.K, trials, filename);
  fileid = coder::internal::cfopen(filename.Value, "rb");
  if (fileid != -1) {
    coder::b_fscanf(static_cast<double>(fileid), values);
    if (values.size(0) < 1) {
      rtDynamicBoundsError(1, 1, values.size(0), ab_emlrtBCI);
    }
    nSamps = values[0];
    if (values.size(0) < 2) {
      rtDynamicBoundsError(2, 1, values.size(0), bb_emlrtBCI);
    }
    threshMedPow = values[1];
    coder::internal::cfclose(static_cast<double>(fileid));
  } else {
    //  Cache miss
  }
  evMuParam = nSamps;
  evSigmaParam = threshMedPow;
  if ((nSamps == 0.0) && (threshMedPow == 0.0)) {
    double stftSz[2];
    int b_loop_ub;
    int nFreqBins;
    int nTimeWinds;
    unsigned int u;
    //  Mu and Sigma were not available from the cache. We have to generate them
    //  here.
    // This will be the reference power for the trials. Thresholds will be
    // interpolated for each bin from this value based on their bin power
    // median(freqBinPow);
    stftSz[0] = Wfm.stft->S.size(0);
    stftSz[1] = Wfm.stft->S.size(1);
    nTimeWinds = static_cast<int>(stftSz[1]);
    nFreqBins = static_cast<int>(stftSz[0]);
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
    if (nTimeWinds != Wq.m) {
      rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
    }
    // Here we approximated the number of samples of synthetic noise data needed
    // to get the correct number of time windows. We over estimate here and then
    // clip the number of correct windows after the stft operation.
    nSamps = (static_cast<double>(nTimeWinds) + 1.0) * Wfm.n_ws + Wfm.n_ol;
    // Based on the STFT help file for the number of windows as a function of
    // samples. We add an additional windows worth of samples to ensure we have
    // enough in our STFT output. We'll clip off any excess after the STFT
    u = trials;
    if (static_cast<double>(u) != static_cast<int>(u)) {
      rtIntegerError(static_cast<double>(u), q_emlrtDCI);
    }
    loop_ub = static_cast<int>(u);
    scores.set_size(static_cast<int>(u));
    if (static_cast<double>(u) != static_cast<int>(u)) {
      rtIntegerError(static_cast<double>(u), q_emlrtDCI);
    }
    for (i = 0; i < loop_ub; i++) {
      scores[i] = 0.0;
    }
    // Preallocate the scores matrix
    // Calculate the total power in the waveform for all frequency bins. Units
    // are W/bin * # bins = W
    coder::wgn(nSamps, trials, static_cast<double>(nFreqBins), xsynth);
    // Generate the synthetic data
    b_Wfm.set_size(Wfm.stft->wind.size(0));
    b_loop_ub = Wfm.stft->wind.size(0) - 1;
    for (i = 0; i <= b_loop_ub; i++) {
      b_Wfm[i] = Wfm.stft->wind[i];
    }
    coder::stft(xsynth, Wfm.Fs, b_Wfm, Wfm.n_ol, Wfm.n_w, Ssynth, values,
                tStft);
    b_loop_ub = Ssynth.size(1) - nTimeWinds;
    b_nTimeWinds.set_size(1, b_loop_ub);
    for (i = 0; i < b_loop_ub; i++) {
      b_nTimeWinds[i] = (nTimeWinds + i) + 1;
    }
    coder::internal::nullAssignment(Ssynth, b_nTimeWinds);
    // Trim excess so we have the correct number of windows.
    b_loop_ub = tStft.size(0);
    values.set_size(tStft.size(0));
    for (i = 0; i < b_loop_ub; i++) {
      values[i] = tStft[i];
    }
    b_loop_ub = tStft.size(0) - nTimeWinds;
    b_nTimeWinds.set_size(1, b_loop_ub);
    for (i = 0; i < b_loop_ub; i++) {
      b_nTimeWinds[i] = (nTimeWinds + i) + 1;
    }
    coder::internal::nullAssignment(values, b_nTimeWinds);
    nSamps = coder::toc() - previousToc;
    std::printf("complete. Elapsed time: %f seconds \n", nSamps);
    std::fflush(stdout);
    previousToc = coder::toc();
    std::printf("\t Running pulse summing process for all datasets ...");
    std::fflush(stdout);
    // Preform the incoherent summation using a matrix multiply.
    // Could use pagetimes.m for this, but it isn't supported for
    // code generation with sparse matrices as of R2023a
    // [serialRejectionMatrix] = repetitionrejector(tStft, [2 3 5 10]);
    repetitionrejector(values, serialRejectionMatrix);
    if (trials > 4294967294U) {
      coder::b_check_forloop_overflow_error();
    }
    i = static_cast<int>(trials);
    for (int b_i{0}; b_i < i; b_i++) {
      xsynth.set_size(Wfm.W.size(0), Wfm.W.size(1));
      b_loop_ub = Wfm.W.size(0) * Wfm.W.size(1);
      for (nTimeWinds = 0; nTimeWinds < b_loop_ub; nTimeWinds++) {
        xsynth[nTimeWinds] = Wfm.W[nTimeWinds];
      }
      if ((static_cast<int>(static_cast<unsigned int>(b_i) + 1U) < 1) ||
          (static_cast<int>(static_cast<unsigned int>(b_i) + 1U) >
           Ssynth.size(2))) {
        rtDynamicBoundsError(
            static_cast<int>(static_cast<unsigned int>(b_i) + 1U), 1,
            Ssynth.size(2), cb_emlrtBCI);
      }
      b_loop_ub = Ssynth.size(0);
      nFreqBins = Ssynth.size(1);
      b.set_size(Ssynth.size(0), Ssynth.size(1));
      for (nTimeWinds = 0; nTimeWinds < nFreqBins; nTimeWinds++) {
        for (int i1{0}; i1 < b_loop_ub; i1++) {
          b[i1 + b.size(0) * nTimeWinds] =
              Ssynth[(i1 + Ssynth.size(0) * nTimeWinds) +
                     Ssynth.size(0) * Ssynth.size(1) * b_i];
        }
      }
      coder::dynamic_size_checks(xsynth, b, xsynth.size(0), Ssynth.size(0));
      coder::internal::blas::mtimes(xsynth, b, y);
      coder::b_abs(y, a);
      r.set_size(a.size(0), a.size(1));
      nFreqBins = a.size(0) * a.size(1);
      for (nTimeWinds = 0; nTimeWinds < nFreqBins; nTimeWinds++) {
        nSamps = a[nTimeWinds];
        r[nTimeWinds] = nSamps * nSamps;
      }
      serialRejectionMatrix.mtimes(r, a);
      Wq.b_mtimes(a, b_varargin_1);
      nFreqBins = b_varargin_1.size(0) * b_varargin_1.size(1);
      if ((static_cast<int>(static_cast<unsigned int>(b_i) + 1U) < 1) ||
          (static_cast<int>(static_cast<unsigned int>(b_i) + 1U) > loop_ub)) {
        rtDynamicBoundsError(
            static_cast<int>(static_cast<unsigned int>(b_i) + 1U), 1, loop_ub,
            db_emlrtBCI);
      }
      c_varargin_1 = b_varargin_1.reshape(nFreqBins);
      scores[b_i] = coder::internal::unaryMinOrMax_anonFcn1(c_varargin_1);
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
    for (i = 0; i < loop_ub; i++) {
      scores[i] = -scores[i];
    }
    coder::evfit(scores, stftSz);
    evMuParam = stftSz[0];
    evSigmaParam = stftSz[1];
    varargin_1.set_size(1, globalThresholdCachePath.size(1));
    loop_ub =
        globalThresholdCachePath.size(0) * globalThresholdCachePath.size(1) - 1;
    for (i = 0; i <= loop_ub; i++) {
      varargin_1[i] = globalThresholdCachePath[i];
    }
    coder::b_sprintf(varargin_1, Wfm.N, Wfm.M, Wfm.J, Wfm.K, trials, filename);
    fileid = coder::internal::cfopen(filename.Value, "wb");
    if (fileid == -1) {
      varargin_1.set_size(1, filename.Value.size(1) + 1);
      nFreqBins = filename.Value.size(1);
      for (i = 0; i < nFreqBins; i++) {
        varargin_1[i] = filename.Value[i];
      }
      varargin_1[filename.Value.size(1)] = '\x00';
      std::printf("threshold::saveThresholdValuesToCache ERROR - Unable to "
                  "open file %s\n",
                  &varargin_1[0]);
      std::fflush(stdout);
    } else {
      if (fileid == 0) {
        e_rtErrorWithMessageID(jc_emlrtRTEI.fName, jc_emlrtRTEI.lineNo);
      }
      f = coder::internal::getfilestar(static_cast<double>(fileid), autoflush);
      if (f == nullptr) {
        c_rtErrorWithMessageID(kc_emlrtRTEI.fName, kc_emlrtRTEI.lineNo);
      } else {
        std::fprintf(f, "%f\n", stftSz[0]);
        if (autoflush) {
          std::fflush(f);
        }
      }
      if (fileid == 0) {
        e_rtErrorWithMessageID(jc_emlrtRTEI.fName, jc_emlrtRTEI.lineNo);
      }
      f = coder::internal::getfilestar(static_cast<double>(fileid), autoflush);
      if (f == nullptr) {
        c_rtErrorWithMessageID(kc_emlrtRTEI.fName, kc_emlrtRTEI.lineNo);
      } else {
        std::fprintf(f, "%f\n", stftSz[1]);
        if (autoflush) {
          std::fflush(f);
        }
      }
      coder::internal::cfclose(static_cast<double>(fileid));
    }
    // figure;plot(xi,F)
    // Uncomment to see how fitted distribution compares to histogram of max
    // scores
    //  p = evpdf(-xi,paramEstsMaxima(1),paramEstsMaxima(2));
    //  figure
    //  histogram(scores,'Normalization','pdf');
    //  hold on
    //  plot(xi,p,'DisplayName','EV Fit'); legend('Location','best')
    //  p = 1-evcdf(-xi,paramEstsMaxima(1),paramEstsMaxima(2));
    //  figure
    //  histogram(scores,'Normalization','cdf');
    //  hold on
    //  plot(xi,p,'DisplayName','EV Fit'); legend('Location','best')
  } else {
    std::printf("\t threshold values were pulled from cache\n");
    std::fflush(stdout);
  }
  // EVTHRESH computs a threshold value based on the parameters of an extreme
  // value distribution and a desired false alarm probability
  //
  // INPUTS:
  //    mu      scalar location parameter of the EV distribution
  //    sigma   scalar scale parameter of the EV distribution
  //    pf      scalar probability of false alarm desired
  // OUPUTS:
  //    thresh  scalar value of the threshold
  // --------------------------------------------------------------------------
  theFunc.workspace.mu = evMuParam;
  if (!(evSigmaParam > 0.0)) {
    h_rtErrorWithMessageID(j_emlrtRTEI.fName, j_emlrtRTEI.lineNo);
  }
  if (!(PF >= 0.0)) {
    m_rtErrorWithMessageID("0", n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
  }
  // Equivalent to 1-evcdf(x,mu,sigma)-pf
  theFunc.workspace.sigma = evSigmaParam;
  theFunc.workspace.pf = PF;
  // theFunc monitonically decrease, so starting at x = 0 should always converge
  threshMedPow = coder::fzero(theFunc);
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
  setthreshprops(threshMedPow, Wfm);
}

//
// Arguments    : double thresh
//                const waveform &Wfm
// Return Type  : void
//
void threshold::setthreshprops(double thresh, const waveform &Wfm)
{
  static rtBoundsCheckInfo ab_emlrtBCI{
      261,                       // lineNo
      "newThresh",               // aName
      "threshold/setthreshprops" // fName
  };
  static rtBoundsCheckInfo bb_emlrtBCI{
      247,                       // lineNo
      "Wfm.stft.f",              // aName
      "threshold/setthreshprops" // fName
  };
  static rtBoundsCheckInfo cb_emlrtBCI{
      247,                       // lineNo
      "Wfm.stft.f",              // aName
      "threshold/setthreshprops" // fName
  };
  static rtBoundsCheckInfo db_emlrtBCI{
      262,                       // lineNo
      "newThresh",               // aName
      "threshold/setthreshprops" // fName
  };
  static rtBoundsCheckInfo eb_emlrtBCI{
      263,                       // lineNo
      "firstTrueThreshInd",      // aName
      "threshold/setthreshprops" // fName
  };
  static rtBoundsCheckInfo fb_emlrtBCI{
      263,                       // lineNo
      "newThresh",               // aName
      "threshold/setthreshprops" // fName
  };
  static rtBoundsCheckInfo gb_emlrtBCI{
      263,                       // lineNo
      "newThresh",               // aName
      "threshold/setthreshprops" // fName
  };
  static rtBoundsCheckInfo hb_emlrtBCI{
      264,                       // lineNo
      "lastTrueThreshInd",       // aName
      "threshold/setthreshprops" // fName
  };
  static rtBoundsCheckInfo ib_emlrtBCI{
      264,                       // lineNo
      "newThresh",               // aName
      "threshold/setthreshprops" // fName
  };
  static rtBoundsCheckInfo jb_emlrtBCI{
      264,                       // lineNo
      "newThresh",               // aName
      "threshold/setthreshprops" // fName
  };
  static rtEqualityCheckInfo g_emlrtECI{
      -1,                        // nDims
      263,                       // lineNo
      "threshold/setthreshprops" // fName
  };
  static rtEqualityCheckInfo h_emlrtECI{
      -1,                        // nDims
      264,                       // lineNo
      "threshold/setthreshprops" // fName
  };
  coder::array<double, 2U> c_freqBinPSD;
  coder::array<double, 1U> b_freqBinPSD;
  coder::array<double, 1U> freqBinPSD;
  coder::array<boolean_T, 1U> x_tmp;
  double dv[2];
  double lastTrueThresh_data;
  int b_loop_ub;
  int firstTrueThreshInd_data;
  int i;
  int ii_data;
  int ii_size;
  int loop_ub;
  loop_ub = Wfm.stft->psd.size(0);
  freqBinPSD.set_size(loop_ub);
  b_loop_ub = Wfm.stft->psd.size(0);
  for (i = 0; i < b_loop_ub; i++) {
    freqBinPSD[i] = Wfm.stft->psd[i];
  }
  // Extract psd for current waveform. Units are W/Hz
  i = Wfm.stft->f.size(0);
  if (i < 2) {
    rtDynamicBoundsError(2, 1, i, cb_emlrtBCI);
  }
  i = Wfm.stft->f.size(0);
  if (i < 1) {
    rtDynamicBoundsError(1, 1, i, bb_emlrtBCI);
  }
  lastTrueThresh_data = Wfm.stft->f[1] - Wfm.stft->f[0];
  // PSD (W/Hz) times bin width (Hz/bin) gives bin total power in (W/bin)
  // 1W standard
  dv[0] = 0.0;
  dv[1] = thresh;
  b_freqBinPSD.set_size(loop_ub);
  for (i = 0; i < loop_ub; i++) {
    b_freqBinPSD[i] = freqBinPSD[i] * lastTrueThresh_data;
  }
  coder::interp1(dv, b_freqBinPSD, freqBinPSD);
  // Finally,extrapolating the thresholds that are a little beyond the original
  // frequeny range can result in negative thresholds. Here we copy the first
  // and last valid threshold out to the places where the extrapolations would
  // have occured
  loop_ub = freqBinPSD.size(0);
  x_tmp.set_size(freqBinPSD.size(0));
  for (i = 0; i < loop_ub; i++) {
    x_tmp[i] = !std::isnan(freqBinPSD[i]);
  }
  ii_size = coder::c_eml_find(x_tmp, (int *)&ii_data);
  b_loop_ub = ii_size;
  for (i = 0; i < ii_size; i++) {
    firstTrueThreshInd_data = ii_data;
  }
  ii_size = coder::d_eml_find(x_tmp, (int *)&ii_data);
  for (i = 0; i < b_loop_ub; i++) {
    if ((firstTrueThreshInd_data < 1) || (firstTrueThreshInd_data > loop_ub)) {
      rtDynamicBoundsError(firstTrueThreshInd_data, 1, loop_ub, ab_emlrtBCI);
    }
  }
  for (i = 0; i < ii_size; i++) {
    if ((ii_data < 1) || (ii_data > loop_ub)) {
      rtDynamicBoundsError(ii_data, 1, loop_ub, db_emlrtBCI);
    }
    lastTrueThresh_data = freqBinPSD[ii_data - 1];
  }
  if (b_loop_ub < 1) {
    rtDynamicBoundsError(1, 1, b_loop_ub, eb_emlrtBCI);
  }
  if (freqBinPSD.size(0) < 1) {
    rtDynamicBoundsError(1, 1, freqBinPSD.size(0), fb_emlrtBCI);
  }
  if ((firstTrueThreshInd_data < 1) ||
      (firstTrueThreshInd_data > freqBinPSD.size(0))) {
    rtDynamicBoundsError(firstTrueThreshInd_data, 1, freqBinPSD.size(0),
                         gb_emlrtBCI);
  }
  if (firstTrueThreshInd_data != b_loop_ub) {
    rtSizeEq1DError(firstTrueThreshInd_data, b_loop_ub, g_emlrtECI);
  }
  c_freqBinPSD.set_size(1, firstTrueThreshInd_data);
  for (i = 0; i < firstTrueThreshInd_data; i++) {
    c_freqBinPSD[i] = freqBinPSD[firstTrueThreshInd_data - 1];
  }
  loop_ub = c_freqBinPSD.size(1);
  for (i = 0; i < loop_ub; i++) {
    freqBinPSD[i] = c_freqBinPSD[i];
  }
  // The (1) call is needed by coder, as it doesn't know that the find call
  // above will only produced a scalar output.
  if (ii_size < 1) {
    rtDynamicBoundsError(1, 1, ii_size, hb_emlrtBCI);
  }
  if (ii_data > freqBinPSD.size(0)) {
    i = 0;
    b_loop_ub = 0;
  } else {
    if ((ii_data < 1) || (ii_data > freqBinPSD.size(0))) {
      rtDynamicBoundsError(ii_data, 1, freqBinPSD.size(0), ib_emlrtBCI);
    }
    i = ii_data - 1;
    if (freqBinPSD.size(0) < 1) {
      rtDynamicBoundsError(freqBinPSD.size(0), 1, freqBinPSD.size(0),
                           jb_emlrtBCI);
    }
    b_loop_ub = freqBinPSD.size(0);
  }
  loop_ub = b_loop_ub - i;
  if (loop_ub != ii_size) {
    rtSizeEq1DError(loop_ub, ii_size, h_emlrtECI);
  }
  for (b_loop_ub = 0; b_loop_ub < loop_ub; b_loop_ub++) {
    freqBinPSD[i + b_loop_ub] = lastTrueThresh_data;
  }
  // The (1) call is needed by coder, as it doesn't know that the find call
  // above will only produced a scalar output. toc
  thresh1W = thresh;
  coder::interp1(Wfm.stft->f, freqBinPSD, Wfm.Wf, threshVecFine);
}

//
// File trailer for threshold.cpp
//
// [EOF]
//
