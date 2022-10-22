//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: threshold.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 21-Oct-2022 17:38:50
//

// Include Files
#include "threshold.h"
#include "anonymous_function.h"
#include "buildtimecorrelatormatrix.h"
#include "evfit.h"
#include "find.h"
#include "fzero.h"
#include "interp1.h"
#include "minOrMax.h"
#include "randn.h"
#include "rt_nonfinite.h"
#include "sparse1.h"
#include "stft.h"
#include "stickyStruct.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_internal_types.h"
#include "uavrt_detection_rtwutil.h"
#include "waveform.h"
#include "wfmstft.h"
#include "coder_array.h"
#include <cmath>
#include <stdio.h>

// Function Declarations
static void k_binary_expand_op(coder::array<boolean_T, 1U> &in1,
                               const waveform *in2, const waveform *in3);

static void l_binary_expand_op(coder::array<boolean_T, 2U> &in1,
                               const waveform *in2, const waveform *in3);

// Function Definitions
//
// Arguments    : double thresh
//                const waveform *Wfm
// Return Type  : void
//
void threshold::setthreshprops(double thresh, const waveform *Wfm)
{
  coder::array<double, 2U> b_newThresh;
  coder::array<double, 1U> newThresh;
  coder::array<boolean_T, 1U> x_tmp;
  double lastTrueThresh_data;
  int firstTrueThreshInd_data;
  int i;
  int inVectorLength;
  int lastTrueThreshInd_data;
  threshVecFine.set_size(Wfm->stft->psd.size(0));
  inVectorLength = Wfm->stft->psd.size(0);
  for (i = 0; i < inVectorLength; i++) {
    threshVecFine[i] = Wfm->stft->psd[i];
  }
  // Extract psd for current waveform. Units are W/Hz
  lastTrueThresh_data = Wfm->stft->f[1] - Wfm->stft->f[0];
  inVectorLength = threshVecFine.size(0);
  for (i = 0; i < inVectorLength; i++) {
    threshVecFine[i] = threshVecFine[i] * lastTrueThresh_data;
  }
  unsigned int outsize_idx_0;
  // PSD (W/Hz) times bin width (Hz/bin) gives bin total power in (W/bin)
  // 1W standard
  outsize_idx_0 = static_cast<unsigned int>(threshVecFine.size(0));
  newThresh.set_size(static_cast<int>(outsize_idx_0));
  inVectorLength = static_cast<int>(outsize_idx_0);
  for (i = 0; i < inVectorLength; i++) {
    newThresh[i] = 0.0;
  }
  if (threshVecFine.size(0) != 0) {
    double dv[2];
    dv[0] = 0.0;
    dv[1] = thresh;
    coder::interp1Linear(dv, threshVecFine, newThresh);
  }
  // Finally,extrapolating the thresholds that are a little beyond the original
  // frequeny range can result in negative thresholds. Here we copy the first
  // and last valid threshold out to the places where the extrapolations would
  // have occured
  x_tmp.set_size(newThresh.size(0));
  inVectorLength = newThresh.size(0);
  for (i = 0; i < inVectorLength; i++) {
    x_tmp[i] = std::isnan(newThresh[i]);
  }
  inVectorLength = x_tmp.size(0);
  for (i = 0; i < inVectorLength; i++) {
    x_tmp[i] = !x_tmp[i];
  }
  coder::c_eml_find(x_tmp, (int *)&lastTrueThreshInd_data, &inVectorLength);
  for (i = 0; i < inVectorLength; i++) {
    firstTrueThreshInd_data = lastTrueThreshInd_data;
  }
  coder::d_eml_find(x_tmp, (int *)&lastTrueThreshInd_data, &inVectorLength);
  for (i = 0; i < inVectorLength; i++) {
    lastTrueThresh_data = newThresh[lastTrueThreshInd_data - 1];
  }
  b_newThresh.set_size(1, firstTrueThreshInd_data);
  for (i = 0; i < firstTrueThreshInd_data; i++) {
    b_newThresh[i] = newThresh[firstTrueThreshInd_data - 1];
  }
  inVectorLength = b_newThresh.size(1);
  for (i = 0; i < inVectorLength; i++) {
    newThresh[i] = b_newThresh[i];
  }
  // The (1) call is needed by coder, as it doesn't know that the find call
  // above will only produced a scalar output.
  if (lastTrueThreshInd_data > newThresh.size(0)) {
    i = 0;
    firstTrueThreshInd_data = 0;
  } else {
    i = lastTrueThreshInd_data - 1;
    firstTrueThreshInd_data = newThresh.size(0);
  }
  inVectorLength = firstTrueThreshInd_data - i;
  for (firstTrueThreshInd_data = 0; firstTrueThreshInd_data < inVectorLength;
       firstTrueThreshInd_data++) {
    newThresh[i + firstTrueThreshInd_data] = lastTrueThresh_data;
  }
  // The (1) call is needed by coder, as it doesn't know that the find call
  // above will only produced a scalar output. toc
  coder::interp1(Wfm->stft->f, newThresh, Wfm->Wf, threshVecFine);
  inVectorLength = 1;
  if (threshVecFine.size(0) != 1) {
    inVectorLength = threshVecFine.size(0);
  }
  if (threshVecFine.size(0) == 1) {
    lastTrueThresh_data = threshVecFine[0];
    threshVecFine.set_size(inVectorLength);
    for (i = 0; i < inVectorLength; i++) {
      threshVecFine[i] = lastTrueThresh_data;
    }
  } else {
    threshVecFine.set_size(inVectorLength);
  }
}

//
// Arguments    : coder::array<boolean_T, 1U> &in1
//                const waveform *in2
//                const waveform *in3
// Return Type  : void
//
static void k_binary_expand_op(coder::array<boolean_T, 1U> &in1,
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
static void l_binary_expand_op(coder::array<boolean_T, 2U> &in1,
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
  static const char b_cv1[7]{'c', 'o', 'm', 'p', 'l', 'e', 'x'};
  static const char b[6]{'l', 'i', 'n', 'e', 'a', 'r'};
  static const char b_cv[6]{'l', 'i', 'n', 'e', 'a', 'r'};
  coder::b_anonymous_function theFunc;
  coder::internal::s_stickyStruct b_varargout_2;
  coder::internal::s_stickyStruct varargout_2;
  coder::sparse Wq;
  coder::array<creal_T, 3U> Ssynth;
  coder::array<creal_T, 3U> b_x;
  coder::array<creal_T, 2U> b_y;
  coder::array<creal_T, 2U> d_b;
  coder::array<creal_T, 2U> varargout_1;
  coder::array<double, 2U> b_b;
  coder::array<double, 2U> c_y;
  coder::array<double, 2U> tempT;
  coder::array<double, 2U> varargin_1;
  coder::array<int, 2U> idx;
  coder::array<char, 2U> x;
  coder::array<char, 2U> y;
  coder::array<boolean_T, 2U> c_b;
  double scores[100];
  double stftSz[2];
  double noisePower;
  double s_im;
  int i;
  int inner;
  int loop_ub;
  int n;
  int nxout;
  int sz_idx_0;
  int sz_idx_2;
  int vlen;
  int vstride;
  int xpagesize;
  char a_data[7];
  boolean_T b_bool;
  theFunc.workspace.pf = pf;
  // This will be the reference power for the trials. Thresholds will be
  // interpolated for each bin from this value based on their bin power
  // median(freqBinPow);
  stftSz[0] = Wfm->stft->S.size(0);
  stftSz[1] = Wfm->stft->S.size(1);
  // Build the Wq time correlation matrix
  buildtimecorrelatormatrix(Wfm->N, Wfm->M, Wfm->J, Wfm->K, &Wq);
  // Here we approximated the number of samples of synthetic noise data needed
  // to get the correct number of time windows. We over estimate here and then
  // clip the number of correct windows after the stft operation.
  s_im = (stftSz[1] + 1.0) * Wfm->n_ws + Wfm->n_ol;
  // Based on the STFT help file for the number of windows as a function of
  // samples. We add an additional windows worth of samples to ensure we have
  // enough in our STFT output. We'll clip off any excess after the STFT Number
  // of sets of synthetic noise to generate Preallocate the scores matrix
  // Calculate the total power in the waveform for all frequency bins. Units are
  // W/bin * # bins = W
  x.set_size(1, 6);
  for (i = 0; i < 6; i++) {
    x[i] = b[i];
  }
  y.set_size(1, 6);
  for (int k{0}; k < 6; k++) {
    y[k] = cv[static_cast<int>(x[k])];
  }
  b_bool = false;
  sz_idx_0 = 0;
  int exitg1;
  do {
    exitg1 = 0;
    if (sz_idx_0 < 6) {
      if (y[sz_idx_0] != b_cv[sz_idx_0]) {
        exitg1 = 1;
      } else {
        sz_idx_0++;
      }
    } else {
      b_bool = true;
      exitg1 = 1;
    }
  } while (exitg1 == 0);
  if (b_bool) {
    i = 0;
  } else {
    i = -1;
  }
  if (i == 0) {
    noisePower = stftSz[0];
  } else {
    noisePower = rt_powd_snf(10.0, (stftSz[0] - 30.0) / 10.0);
  }
  for (i = 0; i < 7; i++) {
    a_data[i] = b_cv1[i];
  }
  if (cv[static_cast<int>(a_data[0])] == 'r') {
    noisePower = std::sqrt(noisePower);
    coder::randn(s_im, b_b);
    varargout_1.set_size(b_b.size(0), 100);
    loop_ub = b_b.size(0) * 100;
    for (i = 0; i < loop_ub; i++) {
      varargout_1[i].re = noisePower * b_b[i];
      varargout_1[i].im = 0.0;
    }
  } else {
    noisePower = std::sqrt(noisePower);
    coder::complexLike(s_im, varargout_1);
    loop_ub = varargout_1.size(0) * 100;
    varargout_1.set_size(varargout_1.size(0), 100);
    for (i = 0; i < loop_ub; i++) {
      varargout_1[i].re = noisePower * varargout_1[i].re;
      varargout_1[i].im = noisePower * varargout_1[i].im;
    }
  }
  // Generate the synthetic data
  varargout_2.next.next.next.next.next.next.next.next.value.set_size(
      Wfm->stft->wind.size(0));
  loop_ub = Wfm->stft->wind.size(0);
  for (i = 0; i < loop_ub; i++) {
    varargout_2.next.next.next.next.next.next.next.next.value[i] =
        Wfm->stft->wind[i];
  }
  if (varargout_1.size(0) == 1) {
    varargout_1.set_size(100, 1);
  } else {
    loop_ub = varargout_1.size(0) * 100;
    for (i = 0; i < loop_ub; i++) {
      varargout_1[i] = varargout_1[i];
    }
  }
  varargout_2.next.next.next.next.next.next.next.next.next.next.next.next.next
      .next.next.next.next.value = varargout_1.size(0);
  varargout_2.next.next.next.next.next.next.next.next.next.next.value = Wfm->Fs;
  varargout_2.next.next.next.next.next.next.next.value =
      varargout_2.next.next.next.next.next.next.next.next.value.size(0);
  varargout_2.next.next.next.next.next.next.value = Wfm->n_ol;
  varargout_2.next.next.next.next.next.value = Wfm->n_w;
  b_varargout_2 = varargout_2;
  coder::computeSTFT(varargout_1, &b_varargout_2, Ssynth,
                     varargout_2.next.next.next.next.next.next.next.next.value,
                     tempT);
  i = static_cast<int>(stftSz[1]);
  idx.set_size(1, Ssynth.size(1) - i);
  loop_ub = Ssynth.size(1) - i;
  for (sz_idx_2 = 0; sz_idx_2 < loop_ub; sz_idx_2++) {
    idx[sz_idx_2] = (i + sz_idx_2) + 1;
  }
  b_x.set_size(Ssynth.size(0), Ssynth.size(1), Ssynth.size(2));
  loop_ub = Ssynth.size(0) * Ssynth.size(1) * Ssynth.size(2);
  for (sz_idx_2 = 0; sz_idx_2 < loop_ub; sz_idx_2++) {
    b_x[sz_idx_2] = Ssynth[sz_idx_2];
  }
  vlen = Ssynth.size(1);
  c_b.set_size(1, Ssynth.size(1));
  loop_ub = Ssynth.size(1);
  for (sz_idx_2 = 0; sz_idx_2 < loop_ub; sz_idx_2++) {
    c_b[sz_idx_2] = false;
  }
  i = (Ssynth.size(1) - i) - 1;
  for (int k{0}; k <= i; k++) {
    c_b[idx[k] - 1] = true;
  }
  n = 0;
  i = c_b.size(1);
  for (int k{0}; k < i; k++) {
    n += c_b[k];
  }
  nxout = Ssynth.size(1) - n;
  sz_idx_0 = Ssynth.size(0);
  sz_idx_2 = Ssynth.size(2);
  Ssynth.set_size(sz_idx_0, nxout, sz_idx_2);
  vstride = b_x.size(0);
  xpagesize = vlen * b_x.size(0);
  sz_idx_0 = nxout * b_x.size(0);
  i = b_x.size(2);
  for (int b_i{0}; b_i < i; b_i++) {
    sz_idx_2 = b_i * xpagesize;
    nxout = b_i * sz_idx_0;
    for (int k{0}; k < vlen; k++) {
      if ((k + 1 > c_b.size(1)) || (!c_b[k])) {
        for (int j{0}; j < vstride; j++) {
          Ssynth[nxout + j] = b_x[sz_idx_2 + j];
        }
        nxout += vstride;
      }
      sz_idx_2 += vstride;
    }
  }
  // Trim excess so we have the correct number of windows.
  // Preform the incoherent summation using a matrix multiply.
  // Could use pagetimes.m for this, but it isn't supported for code generation
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
  loop_ub = Ssynth.size(1);
  vlen = Wfm->W.size(1);
  inner = Wfm->W.size(0);
  n = Ssynth.size(1);
  for (int b_i{0}; b_i < 100; b_i++) {
    d_b.set_size(Ssynth.size(0), Ssynth.size(1));
    for (i = 0; i < loop_ub; i++) {
      sz_idx_0 = Ssynth.size(0);
      for (sz_idx_2 = 0; sz_idx_2 < sz_idx_0; sz_idx_2++) {
        d_b[sz_idx_2 + d_b.size(0) * i] =
            Ssynth[(sz_idx_2 + Ssynth.size(0) * i) +
                   Ssynth.size(0) * Ssynth.size(1) * b_i];
      }
    }
    b_y.set_size(Wfm->W.size(1), Ssynth.size(1));
    for (int j{0}; j < n; j++) {
      nxout = j * vlen;
      vstride = j * Ssynth.size(0);
      for (xpagesize = 0; xpagesize < vlen; xpagesize++) {
        sz_idx_0 = xpagesize * Wfm->W.size(0);
        noisePower = 0.0;
        s_im = 0.0;
        for (int k{0}; k < inner; k++) {
          double Wfm_im;
          double Wfm_re;
          sz_idx_2 = sz_idx_0 + k;
          Wfm_re = Wfm->W[sz_idx_2].re;
          Wfm_im = -Wfm->W[sz_idx_2].im;
          sz_idx_2 = vstride + k;
          noisePower += Wfm_re * d_b[sz_idx_2].re - Wfm_im * d_b[sz_idx_2].im;
          s_im += Wfm_re * d_b[sz_idx_2].im + Wfm_im * d_b[sz_idx_2].re;
        }
        i = nxout + xpagesize;
        b_y[i].re = noisePower;
        b_y[i].im = s_im;
      }
    }
    sz_idx_0 = b_y.size(0) * b_y.size(1);
    c_y.set_size(b_y.size(0), b_y.size(1));
    for (int k{0}; k < sz_idx_0; k++) {
      c_y[k] = rt_hypotd_snf(b_y[k].re, b_y[k].im);
    }
    sz_idx_0 = c_y.size(0) * c_y.size(1);
    for (i = 0; i < sz_idx_0; i++) {
      s_im = c_y[i];
      c_y[i] = s_im * s_im;
    }
    coder::array<double, 1U> b_varargin_1;
    Wq.mtimes(c_y, varargin_1);
    sz_idx_0 = varargin_1.size(0) * varargin_1.size(1);
    // 'all' call finds max across all temporal correlation sets and frequency
    // bins just like we do in the dectection code.
    b_varargin_1 = varargin_1.reshape(sz_idx_0);
    scores[b_i] = -coder::internal::maximum(b_varargin_1);
  }
  coder::evfit(scores, stftSz);
  theFunc.workspace.mu = stftSz[0];
  theFunc.workspace.sigma = stftSz[1];
  // theFunc = @(x) 1-exp(-exp((x-mu)/sigma));%Equivalent to evcdf(x,mu,sigma)
  // theFunc = @(x) exp(-exp((x-mu)/sigma));%Equivalent to 1-evcdf(x,mu,sigma)
  // Equivalent to 1-evcdf(x,mu,sigma)-pf
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
  setthreshprops(coder::fzero(theFunc), Wfm);
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
  coder::b_anonymous_function theFunc;
  coder::array<boolean_T, 2U> x;
  coder::array<boolean_T, 1U> b_x;
  int loop_ub;
  boolean_T b;
  boolean_T b1;
  boolean_T b2;
  boolean_T b_varargout_1;
  boolean_T exitg1;
  boolean_T needsUpdate;
  boolean_T varargout_1;
  needsUpdate = (WfmCurr->N != WfmPrev->N);
  b = (WfmCurr->M != WfmPrev->M);
  b1 = (WfmCurr->J != WfmPrev->J);
  b2 = (WfmCurr->K != WfmPrev->K);
  if ((WfmCurr->W.size(0) == WfmPrev->W.size(0)) &&
      (WfmCurr->W.size(1) == WfmPrev->W.size(1))) {
    x.set_size(WfmCurr->W.size(0), WfmCurr->W.size(1));
    loop_ub = WfmCurr->W.size(0) * WfmCurr->W.size(1);
    for (int i{0}; i < loop_ub; i++) {
      x[i] = ((WfmCurr->W[i].re != WfmPrev->W[i].re) ||
              (WfmCurr->W[i].im != WfmPrev->W[i].im));
    }
  } else {
    l_binary_expand_op(x, WfmCurr, WfmPrev);
  }
  if (WfmCurr->Wf.size(0) == WfmPrev->Wf.size(0)) {
    b_x.set_size(WfmCurr->Wf.size(0));
    loop_ub = WfmCurr->Wf.size(0);
    for (int i{0}; i < loop_ub; i++) {
      b_x[i] = (WfmCurr->Wf[i] != WfmPrev->Wf[i]);
    }
  } else {
    k_binary_expand_op(b_x, WfmCurr, WfmPrev);
  }
  varargout_1 = false;
  loop_ub = 1;
  exitg1 = false;
  while ((!exitg1) && (loop_ub <= x.size(0) * x.size(1))) {
    if (x[loop_ub - 1]) {
      varargout_1 = true;
      exitg1 = true;
    } else {
      loop_ub++;
    }
  }
  b_varargout_1 = false;
  loop_ub = 1;
  exitg1 = false;
  while ((!exitg1) && (loop_ub <= b_x.size(0))) {
    if (b_x[loop_ub - 1]) {
      b_varargout_1 = true;
      exitg1 = true;
    } else {
      loop_ub++;
    }
  }
  if (needsUpdate || b || b1 || b2 || varargout_1 || b_varargout_1) {
    makenewthreshold(WfmCurr);
  } else {
    double b_val;
    double val;
    val = WfmPrev->thresh.evMuParam;
    evMuParam = val;
    b_val = WfmPrev->thresh.evSigmaParam;
    evSigmaParam = b_val;
    printf("%f\n", val);
    fflush(stdout);
    printf("%f\n", val);
    fflush(stdout);
    printf("%f\n", pf);
    fflush(stdout);
    theFunc.workspace.mu = val;
    theFunc.workspace.sigma = b_val;
    theFunc.workspace.pf = pf;
    // theFunc = @(x) 1-exp(-exp((x-mu)/sigma));%Equivalent to evcdf(x,mu,sigma)
    // theFunc = @(x) exp(-exp((x-mu)/sigma));%Equivalent to 1-evcdf(x,mu,sigma)
    // Equivalent to 1-evcdf(x,mu,sigma)-pf
    // theFunc monitonically decrease, so starting at x = 0 should always
    // converge Build a single threshold value at 1 W bin power
    setthreshprops(coder::fzero(theFunc), WfmCurr);
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
