//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: threshold.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 16-Mar-2023 20:12:42
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
#include <cmath>
#include <stdio.h>
#include <string.h>

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
void threshold::init()
{
  pf = 0.01;
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
  static rtBoundsCheckInfo fb_emlrtBCI{
      -1,                                        // iFirst
      -1,                                        // iLast
      276,                                       // lineNo
      63,                                        // colNo
      "Wfm.stft.f",                              // aName
      "threshold/setthreshprops",                // fName
      "H:\\repos\\uavrt_detection\\threshold.m", // pName
      0                                          // checkKind
  };
  static rtBoundsCheckInfo gb_emlrtBCI{
      -1,                                        // iFirst
      -1,                                        // iLast
      276,                                       // lineNo
      49,                                        // colNo
      "Wfm.stft.f",                              // aName
      "threshold/setthreshprops",                // fName
      "H:\\repos\\uavrt_detection\\threshold.m", // pName
      0                                          // checkKind
  };
  static rtBoundsCheckInfo hb_emlrtBCI{
      -1,                                        // iFirst
      -1,                                        // iLast
      157,                                       // lineNo
      55,                                        // colNo
      "Ssynth",                                  // aName
      "threshold/makenewthreshold",              // fName
      "H:\\repos\\uavrt_detection\\threshold.m", // pName
      0                                          // checkKind
  };
  static rtBoundsCheckInfo ib_emlrtBCI{
      -1,                                        // iFirst
      -1,                                        // iLast
      291,                                       // lineNo
      44,                                        // colNo
      "newThresh",                               // aName
      "threshold/setthreshprops",                // fName
      "H:\\repos\\uavrt_detection\\threshold.m", // pName
      0                                          // checkKind
  };
  static rtBoundsCheckInfo jb_emlrtBCI{
      -1,                                        // iFirst
      -1,                                        // iLast
      290,                                       // lineNo
      44,                                        // colNo
      "newThresh",                               // aName
      "threshold/setthreshprops",                // fName
      "H:\\repos\\uavrt_detection\\threshold.m", // pName
      0                                          // checkKind
  };
  static rtBoundsCheckInfo kb_emlrtBCI{
      -1,                                        // iFirst
      -1,                                        // iLast
      292,                                       // lineNo
      44,                                        // colNo
      "firstTrueThreshInd",                      // aName
      "threshold/setthreshprops",                // fName
      "H:\\repos\\uavrt_detection\\threshold.m", // pName
      0                                          // checkKind
  };
  static rtBoundsCheckInfo lb_emlrtBCI{
      -1,                                        // iFirst
      -1,                                        // iLast
      292,                                       // lineNo
      23,                                        // colNo
      "newThresh",                               // aName
      "threshold/setthreshprops",                // fName
      "H:\\repos\\uavrt_detection\\threshold.m", // pName
      0                                          // checkKind
  };
  static rtBoundsCheckInfo mb_emlrtBCI{
      -1,                                        // iFirst
      -1,                                        // iLast
      292,                                       // lineNo
      25,                                        // colNo
      "newThresh",                               // aName
      "threshold/setthreshprops",                // fName
      "H:\\repos\\uavrt_detection\\threshold.m", // pName
      0                                          // checkKind
  };
  static rtBoundsCheckInfo nb_emlrtBCI{
      -1,                                        // iFirst
      -1,                                        // iLast
      293,                                       // lineNo
      41,                                        // colNo
      "lastTrueThreshInd",                       // aName
      "threshold/setthreshprops",                // fName
      "H:\\repos\\uavrt_detection\\threshold.m", // pName
      0                                          // checkKind
  };
  static rtBoundsCheckInfo ob_emlrtBCI{
      -1,                                        // iFirst
      -1,                                        // iLast
      293,                                       // lineNo
      23,                                        // colNo
      "newThresh",                               // aName
      "threshold/setthreshprops",                // fName
      "H:\\repos\\uavrt_detection\\threshold.m", // pName
      0                                          // checkKind
  };
  static rtBoundsCheckInfo pb_emlrtBCI{
      -1,                                        // iFirst
      -1,                                        // iLast
      293,                                       // lineNo
      44,                                        // colNo
      "newThresh",                               // aName
      "threshold/setthreshprops",                // fName
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
      -1,                                       // nDims
      292,                                      // lineNo
      13,                                       // colNo
      "threshold/setthreshprops",               // fName
      "H:\\repos\\uavrt_detection\\threshold.m" // pName
  };
  static rtEqualityCheckInfo h_emlrtECI{
      -1,                                       // nDims
      293,                                      // lineNo
      13,                                       // colNo
      "threshold/setthreshprops",               // fName
      "H:\\repos\\uavrt_detection\\threshold.m" // pName
  };
  static rtRunTimeErrorInfo uc_emlrtRTEI{
      449,                      // lineNo
      "general_null_assignment" // fName
  };
  static rtRunTimeErrorInfo vc_emlrtRTEI{
      81,               // lineNo
      "validate_inputs" // fName
  };
  coder::b_anonymous_function theFunc;
  coder::sparse Wq;
  coder::array<creal_T, 3U> Ssynth;
  coder::array<creal_T, 3U> b_Ssynth;
  coder::array<creal_T, 2U> b_b;
  coder::array<creal_T, 2U> xsynth;
  coder::array<creal_T, 2U> y;
  coder::array<double, 2U> b_newThresh;
  coder::array<double, 2U> b_y;
  coder::array<double, 2U> varargin_1;
  coder::array<double, 1U> a__2;
  coder::array<double, 1U> c_newThresh;
  coder::array<double, 1U> freqBinPSD;
  coder::array<double, 1U> newThresh;
  coder::array<int, 2U> idx;
  coder::array<boolean_T, 2U> b;
  coder::array<boolean_T, 1U> x_tmp;
  double scores[100];
  double stftSz[2];
  double previousToc;
  double s_im;
  double s_re;
  int i;
  int inner;
  int ix0;
  int iy0;
  int k;
  int loop_ub;
  int n;
  int npages;
  int nxout;
  int vlen;
  int vstride;
  int xpagesize;
  boolean_T exitg1;
  boolean_T overflow;
  theFunc.workspace.pf = pf;
  // This will be the reference power for the trials. Thresholds will be
  // interpolated for each bin from this value based on their bin power
  // median(freqBinPow);
  stftSz[0] = Wfm->stft->S.size(0);
  stftSz[1] = Wfm->stft->S.size(1);
  previousToc = coder::toc();
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
  // enough in our STFT output. We'll clip off any excess after the STFT Number
  // of sets of synthetic noise to generate Preallocate the scores matrix
  // Calculate the total power in the waveform for all frequency bins. Units are
  // W/bin * # bins = W
  coder::wgn((stftSz[1] + 1.0) * Wfm->n_ws + Wfm->n_ol, stftSz[0], xsynth);
  // Generate the synthetic data
  coder::stft(xsynth, Wfm->Fs, Wfm->stft->wind, Wfm->n_ol, Wfm->n_w, Ssynth,
              freqBinPSD, a__2);
  idx.set_size(1, Ssynth.size(1) - i);
  loop_ub = Ssynth.size(1) - i;
  for (nxout = 0; nxout < loop_ub; nxout++) {
    idx[nxout] = (i + nxout) + 1;
  }
  overflow = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= idx.size(1) - 1)) {
    if (idx[k] > Ssynth.size(1)) {
      overflow = false;
      exitg1 = true;
    } else {
      k++;
    }
  }
  if (!overflow) {
    jc_rtErrorWithMessageID(vc_emlrtRTEI.fName, vc_emlrtRTEI.lineNo);
  }
  vlen = Ssynth.size(1);
  b.set_size(1, Ssynth.size(1));
  loop_ub = Ssynth.size(1);
  for (nxout = 0; nxout < loop_ub; nxout++) {
    b[nxout] = false;
  }
  nxout = (Ssynth.size(1) - i) - 1;
  overflow = (Ssynth.size(1) - i > 2147483646);
  if (overflow) {
    coder::check_forloop_overflow_error();
  }
  for (k = 0; k <= nxout; k++) {
    b[idx[k] - 1] = true;
  }
  n = 0;
  nxout = b.size(1);
  if (b.size(1) > 2147483646) {
    coder::check_forloop_overflow_error();
  }
  for (k = 0; k < nxout; k++) {
    n += b[k];
  }
  nxout = Ssynth.size(1) - n;
  if (nxout > Ssynth.size(1)) {
    i_rtErrorWithMessageID(uc_emlrtRTEI.fName, uc_emlrtRTEI.lineNo);
  }
  if (nxout < 0) {
    rtNonNegativeError(static_cast<double>(nxout), &t_emlrtDCI);
  }
  b_Ssynth.set_size(Ssynth.size(0), nxout, Ssynth.size(2));
  vstride = Ssynth.size(0);
  xpagesize = Ssynth.size(0) * Ssynth.size(1);
  nxout *= Ssynth.size(0);
  npages = Ssynth.size(2);
  overflow = (Ssynth.size(1) > 2147483646);
  for (int b_i{0}; b_i < npages; b_i++) {
    ix0 = b_i * xpagesize;
    iy0 = b_i * nxout;
    if (overflow) {
      coder::check_forloop_overflow_error();
    }
    for (k = 0; k < vlen; k++) {
      if ((k + 1 > b.size(1)) || (!b[k])) {
        if (vstride > 2147483646) {
          coder::check_forloop_overflow_error();
        }
        for (int j{0}; j < vstride; j++) {
          b_Ssynth[iy0 + j] = Ssynth[ix0 + j];
        }
        iy0 += vstride;
      }
      ix0 += vstride;
    }
  }
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
  loop_ub = b_Ssynth.size(0);
  xpagesize = b_Ssynth.size(1);
  vlen = Wfm->W.size(1);
  inner = Wfm->W.size(0);
  n = b_Ssynth.size(1) - 1;
  overflow = (b_Ssynth.size(1) > 2147483646);
  for (int b_i{0}; b_i < 100; b_i++) {
    if (b_i + 1 > b_Ssynth.size(2)) {
      rtDynamicBoundsError(b_i + 1, 1, b_Ssynth.size(2), &hb_emlrtBCI);
    }
    b_b.set_size(loop_ub, xpagesize);
    for (i = 0; i < xpagesize; i++) {
      for (nxout = 0; nxout < loop_ub; nxout++) {
        b_b[nxout + b_b.size(0) * i] =
            b_Ssynth[(nxout + b_Ssynth.size(0) * i) +
                     b_Ssynth.size(0) * b_Ssynth.size(1) * b_i];
      }
    }
    if (Wfm->W.size(0) != b_Ssynth.size(0)) {
      if (((Wfm->W.size(0) == 1) && (Wfm->W.size(1) == 1)) ||
          ((b_Ssynth.size(0) == 1) && (b_Ssynth.size(1) == 1))) {
        xb_rtErrorWithMessageID(hc_emlrtRTEI.fName, hc_emlrtRTEI.lineNo);
      } else {
        ob_rtErrorWithMessageID(gc_emlrtRTEI.fName, gc_emlrtRTEI.lineNo);
      }
    }
    y.set_size(Wfm->W.size(1), b_Ssynth.size(1));
    if (overflow) {
      coder::check_forloop_overflow_error();
    }
    for (int j{0}; j <= n; j++) {
      ix0 = j * vlen;
      iy0 = j * b_Ssynth.size(0);
      if (vlen > 2147483646) {
        coder::check_forloop_overflow_error();
      }
      for (vstride = 0; vstride < vlen; vstride++) {
        nxout = vstride * Wfm->W.size(0);
        s_re = 0.0;
        s_im = 0.0;
        if (inner > 2147483646) {
          coder::check_forloop_overflow_error();
        }
        for (k = 0; k < inner; k++) {
          double Wfm_im;
          double Wfm_re;
          npages = nxout + k;
          Wfm_re = Wfm->W[npages].re;
          Wfm_im = -Wfm->W[npages].im;
          npages = iy0 + k;
          s_re += Wfm_re * b_b[npages].re - Wfm_im * b_b[npages].im;
          s_im += Wfm_re * b_b[npages].im + Wfm_im * b_b[npages].re;
        }
        i = ix0 + vstride;
        y[i].re = s_re;
        y[i].im = s_im;
      }
    }
    nxout = y.size(0) * y.size(1);
    b_y.set_size(y.size(0), y.size(1));
    if (nxout > 2147483646) {
      coder::check_forloop_overflow_error();
    }
    for (k = 0; k < nxout; k++) {
      b_y[k] = rt_hypotd_snf(y[k].re, y[k].im);
    }
    nxout = b_y.size(0) * b_y.size(1);
    for (i = 0; i < nxout; i++) {
      s_re = b_y[i];
      b_y[i] = s_re * s_re;
    }
    coder::array<double, 1U> b_varargin_1;
    Wq.mtimes(b_y, varargin_1);
    nxout = varargin_1.size(0) * varargin_1.size(1);
    b_varargin_1 = varargin_1.reshape(nxout);
    scores[b_i] = coder::internal::unaryMinOrMax_anonFcn1(b_varargin_1);
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
  for (i = 0; i < 100; i++) {
    scores[i] = -scores[i];
  }
  coder::evfit(scores, stftSz);
  theFunc.workspace.mu = stftSz[0];
  theFunc.workspace.sigma = stftSz[1];
  // theFunc = @(x) 1-exp(-exp((x-mu)/sigma));%Equivalent to evcdf(x,mu,sigma)
  // theFunc = @(x) exp(-exp((x-mu)/sigma));%Equivalent to 1-evcdf(x,mu,sigma)
  // Equivalent to 1-evcdf(x,mu,sigma)-pf
  s_im = coder::fzero(theFunc);
  // theFunc monitonically decrease, so starting at x = 0 should always converge
  s_re = coder::toc() - previousToc;
  printf("complete. Elapsed time: %f seconds \n", s_re);
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
  freqBinPSD.set_size(Wfm->stft->psd.size(0));
  loop_ub = Wfm->stft->psd.size(0);
  for (i = 0; i < loop_ub; i++) {
    freqBinPSD[i] = Wfm->stft->psd[i];
  }
  // Extract psd for current waveform. Units are W/Hz
  i = Wfm->stft->f.size(0);
  if (i < 2) {
    rtDynamicBoundsError(2, 1, i, &gb_emlrtBCI);
  }
  i = Wfm->stft->f.size(0);
  if (i < 1) {
    rtDynamicBoundsError(1, 1, i, &fb_emlrtBCI);
  }
  s_re = Wfm->stft->f[1] - Wfm->stft->f[0];
  loop_ub = freqBinPSD.size(0);
  for (i = 0; i < loop_ub; i++) {
    freqBinPSD[i] = freqBinPSD[i] * s_re;
  }
  // PSD (W/Hz) times bin width (Hz/bin) gives bin total power in (W/bin)
  // 1W standard
  newThresh.set_size(freqBinPSD.size(0));
  loop_ub = freqBinPSD.size(0);
  for (i = 0; i < loop_ub; i++) {
    newThresh[i] = 0.0;
  }
  if (freqBinPSD.size(0) != 0) {
    stftSz[0] = 0.0;
    stftSz[1] = s_im;
    coder::interp1Linear(stftSz, freqBinPSD, newThresh);
  }
  // Finally,extrapolating the thresholds that are a little beyond the original
  // frequeny range can result in negative thresholds. Here we copy the first
  // and last valid threshold out to the places where the extrapolations would
  // have occured
  x_tmp.set_size(newThresh.size(0));
  loop_ub = newThresh.size(0);
  for (i = 0; i < loop_ub; i++) {
    x_tmp[i] = std::isnan(newThresh[i]);
  }
  loop_ub = x_tmp.size(0);
  for (i = 0; i < loop_ub; i++) {
    x_tmp[i] = !x_tmp[i];
  }
  coder::c_eml_find(x_tmp, (int *)&ix0, &iy0);
  npages = iy0;
  for (i = 0; i < iy0; i++) {
    nxout = ix0;
  }
  coder::d_eml_find(x_tmp, (int *)&ix0, &iy0);
  for (i = 0; i < npages; i++) {
    if ((nxout < 1) || (nxout > newThresh.size(0))) {
      rtDynamicBoundsError(nxout, 1, newThresh.size(0), &jb_emlrtBCI);
    }
  }
  for (i = 0; i < iy0; i++) {
    if ((ix0 < 1) || (ix0 > newThresh.size(0))) {
      rtDynamicBoundsError(ix0, 1, newThresh.size(0), &ib_emlrtBCI);
    }
    s_re = newThresh[ix0 - 1];
  }
  if (npages < 1) {
    rtDynamicBoundsError(1, 1, npages, &kb_emlrtBCI);
  }
  if (newThresh.size(0) < 1) {
    rtDynamicBoundsError(1, 1, newThresh.size(0), &lb_emlrtBCI);
  }
  if ((nxout < 1) || (nxout > newThresh.size(0))) {
    rtDynamicBoundsError(nxout, 1, newThresh.size(0), &mb_emlrtBCI);
  }
  if (nxout != npages) {
    rtSizeEq1DError(nxout, npages, &g_emlrtECI);
  }
  b_newThresh.set_size(1, nxout);
  for (i = 0; i < nxout; i++) {
    b_newThresh[i] = newThresh[nxout - 1];
  }
  loop_ub = b_newThresh.size(1);
  for (i = 0; i < loop_ub; i++) {
    newThresh[i] = b_newThresh[i];
  }
  // The (1) call is needed by coder, as it doesn't know that the find call
  // above will only produced a scalar output.
  if (iy0 < 1) {
    rtDynamicBoundsError(1, 1, iy0, &nb_emlrtBCI);
  }
  if (ix0 > newThresh.size(0)) {
    i = -1;
    nxout = -1;
  } else {
    if ((ix0 < 1) || (ix0 > newThresh.size(0))) {
      rtDynamicBoundsError(ix0, 1, newThresh.size(0), &ob_emlrtBCI);
    }
    i = ix0 - 2;
    if (newThresh.size(0) < 1) {
      rtDynamicBoundsError(newThresh.size(0), 1, newThresh.size(0),
                           &pb_emlrtBCI);
    }
    nxout = newThresh.size(0) - 1;
  }
  loop_ub = nxout - i;
  if (loop_ub != iy0) {
    rtSizeEq1DError(loop_ub, iy0, &h_emlrtECI);
  }
  for (nxout = 0; nxout < loop_ub; nxout++) {
    newThresh[(i + nxout) + 1] = s_re;
  }
  // The (1) call is needed by coder, as it doesn't know that the find call
  // above will only produced a scalar output. toc
  coder::internal::validator_check_size(newThresh, c_newThresh);
  coder::interp1(Wfm->stft->f, newThresh, Wfm->Wf, a__2);
  coder::internal::validator_check_size(a__2, threshVecFine);
}

//
// File trailer for threshold.cpp
//
// [EOF]
//
