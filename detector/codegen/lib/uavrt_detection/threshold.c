/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: threshold.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "threshold.h"
#include "buildtimecorrelatormatrix.h"
#include "evfit.h"
#include "find.h"
#include "fzero.h"
#include "interp1.h"
#include "minOrMax.h"
#include "mtimes.h"
#include "randn.h"
#include "rt_nonfinite.h"
#include "stft.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_internal_types.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <stdio.h>

/* Function Declarations */
static void threshold_setthreshprops(threshold *obj, double thresh,
                                     const waveform *Wfm);

static void v_binary_expand_op(emxArray_boolean_T *in1, const waveform *in2,
                               const waveform *in3);

static void w_binary_expand_op(emxArray_boolean_T *in1, const waveform *in2,
                               const waveform *in3);

/* Function Definitions */
/*
 * Arguments    : threshold *obj
 *                double thresh
 *                const waveform *Wfm
 * Return Type  : void
 */
static void threshold_setthreshprops(threshold *obj, double thresh,
                                     const waveform *Wfm)
{
  emxArray_boolean_T *x_tmp;
  emxArray_real_T *b_newThresh;
  emxArray_real_T *newThresh;
  double lastTrueThresh_data;
  double *b_newThresh_data;
  double *newThresh_data;
  int firstTrueThreshInd_data;
  int i;
  int inVectorLength;
  int lastTrueThreshInd_data;
  bool *x_tmp_data;
  i = obj->threshVecFine->size[0];
  obj->threshVecFine->size[0] = Wfm->stft->psd->size[0];
  emxEnsureCapacity_real_T(obj->threshVecFine, i);
  inVectorLength = Wfm->stft->psd->size[0];
  for (i = 0; i < inVectorLength; i++) {
    obj->threshVecFine->data[i] = Wfm->stft->psd->data[i];
  }
  /* Extract psd for current waveform. Units are W/Hz */
  lastTrueThresh_data = Wfm->stft->f->data[1] - Wfm->stft->f->data[0];
  inVectorLength = obj->threshVecFine->size[0];
  for (i = 0; i < inVectorLength; i++) {
    obj->threshVecFine->data[i] *= lastTrueThresh_data;
  }
  unsigned int outsize_idx_0;
  /* PSD (W/Hz) times bin width (Hz/bin) gives bin total power in (W/bin) */
  /* 1W standard */
  outsize_idx_0 = (unsigned int)obj->threshVecFine->size[0];
  emxInit_real_T(&newThresh, 1);
  i = newThresh->size[0];
  newThresh->size[0] = (int)outsize_idx_0;
  emxEnsureCapacity_real_T(newThresh, i);
  newThresh_data = newThresh->data;
  inVectorLength = (int)outsize_idx_0;
  for (i = 0; i < inVectorLength; i++) {
    newThresh_data[i] = 0.0;
  }
  if (obj->threshVecFine->size[0] != 0) {
    double dv[2];
    dv[0] = 0.0;
    dv[1] = thresh;
    b_interp1Linear(dv, obj->threshVecFine, newThresh);
    newThresh_data = newThresh->data;
  }
  /* Finally,extrapolating the thresholds that are a little beyond the original
   */
  /* frequeny range can result in negative thresholds. Here we copy the first */
  /* and last valid threshold out to the places where the extrapolations would
   */
  /* have occured */
  emxInit_boolean_T(&x_tmp, 1);
  i = x_tmp->size[0];
  x_tmp->size[0] = newThresh->size[0];
  emxEnsureCapacity_boolean_T(x_tmp, i);
  x_tmp_data = x_tmp->data;
  inVectorLength = newThresh->size[0];
  for (i = 0; i < inVectorLength; i++) {
    x_tmp_data[i] = rtIsNaN(newThresh_data[i]);
  }
  inVectorLength = x_tmp->size[0];
  for (i = 0; i < inVectorLength; i++) {
    x_tmp_data[i] = !x_tmp_data[i];
  }
  c_eml_find(x_tmp, (int *)&lastTrueThreshInd_data, &inVectorLength);
  for (i = 0; i < inVectorLength; i++) {
    firstTrueThreshInd_data = lastTrueThreshInd_data;
  }
  d_eml_find(x_tmp, (int *)&lastTrueThreshInd_data, &inVectorLength);
  emxFree_boolean_T(&x_tmp);
  for (i = 0; i < inVectorLength; i++) {
    lastTrueThresh_data = newThresh_data[lastTrueThreshInd_data - 1];
  }
  emxInit_real_T(&b_newThresh, 2);
  i = b_newThresh->size[0] * b_newThresh->size[1];
  b_newThresh->size[0] = 1;
  b_newThresh->size[1] = firstTrueThreshInd_data;
  emxEnsureCapacity_real_T(b_newThresh, i);
  b_newThresh_data = b_newThresh->data;
  for (i = 0; i < firstTrueThreshInd_data; i++) {
    b_newThresh_data[i] = newThresh_data[firstTrueThreshInd_data - 1];
  }
  inVectorLength = b_newThresh->size[1];
  for (i = 0; i < inVectorLength; i++) {
    newThresh_data[i] = b_newThresh_data[i];
  }
  emxFree_real_T(&b_newThresh);
  /* The (1) call is needed by coder, as it doesn't know that the find call
   * above will only produced a scalar output. */
  if (lastTrueThreshInd_data > newThresh->size[0]) {
    i = 0;
    firstTrueThreshInd_data = 0;
  } else {
    i = lastTrueThreshInd_data - 1;
    firstTrueThreshInd_data = newThresh->size[0];
  }
  inVectorLength = firstTrueThreshInd_data - i;
  for (firstTrueThreshInd_data = 0; firstTrueThreshInd_data < inVectorLength;
       firstTrueThreshInd_data++) {
    newThresh_data[i + firstTrueThreshInd_data] = lastTrueThresh_data;
  }
  /* The (1) call is needed by coder, as it doesn't know that the find call
   * above will only produced a scalar output. */
  /* toc */
  interp1(Wfm->stft->f, newThresh, Wfm->Wf, obj->threshVecFine);
  emxFree_real_T(&newThresh);
  inVectorLength = 1;
  if (obj->threshVecFine->size[0] != 1) {
    inVectorLength = obj->threshVecFine->size[0];
  }
  if (obj->threshVecFine->size[0] == 1) {
    lastTrueThresh_data = obj->threshVecFine->data[0];
    i = obj->threshVecFine->size[0];
    obj->threshVecFine->size[0] = inVectorLength;
    emxEnsureCapacity_real_T(obj->threshVecFine, i);
    for (i = 0; i < inVectorLength; i++) {
      obj->threshVecFine->data[i] = lastTrueThresh_data;
    }
  } else {
    i = obj->threshVecFine->size[0];
    obj->threshVecFine->size[0] = inVectorLength;
    emxEnsureCapacity_real_T(obj->threshVecFine, i);
  }
}

/*
 * Arguments    : emxArray_boolean_T *in1
 *                const waveform *in2
 *                const waveform *in3
 * Return Type  : void
 */
static void v_binary_expand_op(emxArray_boolean_T *in1, const waveform *in2,
                               const waveform *in3)
{
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  bool *in1_data;
  i = in1->size[0];
  if (in3->Wf->size[0] == 1) {
    in1->size[0] = in2->Wf->size[0];
  } else {
    in1->size[0] = in3->Wf->size[0];
  }
  emxEnsureCapacity_boolean_T(in1, i);
  in1_data = in1->data;
  stride_0_0 = (in2->Wf->size[0] != 1);
  stride_1_0 = (in3->Wf->size[0] != 1);
  if (in3->Wf->size[0] == 1) {
    loop_ub = in2->Wf->size[0];
  } else {
    loop_ub = in3->Wf->size[0];
  }
  for (i = 0; i < loop_ub; i++) {
    in1_data[i] =
        (in2->Wf->data[i * stride_0_0] != in3->Wf->data[i * stride_1_0]);
  }
}

/*
 * Arguments    : emxArray_boolean_T *in1
 *                const waveform *in2
 *                const waveform *in3
 * Return Type  : void
 */
static void w_binary_expand_op(emxArray_boolean_T *in1, const waveform *in2,
                               const waveform *in3)
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
  bool *in1_data;
  i = in1->size[0] * in1->size[1];
  if (in3->W->size[0] == 1) {
    in1->size[0] = in2->W->size[0];
  } else {
    in1->size[0] = in3->W->size[0];
  }
  if (in3->W->size[1] == 1) {
    in1->size[1] = in2->W->size[1];
  } else {
    in1->size[1] = in3->W->size[1];
  }
  emxEnsureCapacity_boolean_T(in1, i);
  in1_data = in1->data;
  stride_0_0 = (in2->W->size[0] != 1);
  stride_0_1 = (in2->W->size[1] != 1);
  stride_1_0 = (in3->W->size[0] != 1);
  stride_1_1 = (in3->W->size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  if (in3->W->size[1] == 1) {
    loop_ub = in2->W->size[1];
  } else {
    loop_ub = in3->W->size[1];
  }
  for (i = 0; i < loop_ub; i++) {
    int b_loop_ub;
    if (in3->W->size[0] == 1) {
      b_loop_ub = in2->W->size[0];
    } else {
      b_loop_ub = in3->W->size[0];
    }
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      int i2;
      i2 = i1 * stride_1_0;
      in1_data[i1 + in1->size[0] * i] =
          ((in2->W->data[i1 * stride_0_0 + in2->W->size[0] * aux_0_1].re !=
            in3->W->data[i2 + in3->W->size[0] * aux_1_1].re) ||
           (in2->W->data[i1 * stride_0_0 + in2->W->size[0] * aux_0_1].im !=
            in3->W->data[i2 + in3->W->size[0] * aux_1_1].im));
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
}

/*
 * BUILDTHRESHOLD generates a threshold vector for the waveform argument
 * based on the false alarm probability input.
 *
 * This function creates a vector of thresholds for the incoherently summed
 * results of the data in the input waveform. The probability of false alarm
 * input is used for threshold generation. The output vector is a spectrally
 * tuned threshold for each frequency in the STFT of the waveform. These
 * thresholds are dependent on the power spectral density for each frequency
 * bin, so areas of the spectrum with a high noise floor will have a higher
 * output thresholde value
 *
 * INPUTS:
 *    Wfm     A single waveform object
 *    PF      A scalar probability of false alarm value (0 1];
 * OUTPUTS:
 *    newThresh   A vector of threshold with as many elements as rows in the
 *                S matrix of the wfmstft object within the Wfm input.
 *
 * Author:    Michael W. Shafer
 * Date:      2022-05-04
 * --------------------------------------------------------------------------
 *
 * Arguments    : threshold *obj
 *                const waveform *Wfm
 * Return Type  : void
 */
void threshold_makenewthreshold(threshold *obj, const waveform *Wfm)
{
  static const char b_cv1[7] = {'c', 'o', 'm', 'p', 'l', 'e', 'x'};
  static const char b[6] = {'l', 'i', 'n', 'e', 'a', 'r'};
  static const char b_cv[6] = {'l', 'i', 'n', 'e', 'a', 'r'};
  d_sparse expl_temp;
  emxArray_boolean_T *c_b;
  emxArray_char_T *switch_expression;
  emxArray_char_T *x;
  emxArray_creal_T *Ssynth;
  emxArray_creal_T *b_x;
  emxArray_creal_T *d_b;
  emxArray_creal_T *varargout_1;
  emxArray_creal_T *y;
  emxArray_int32_T *idx;
  emxArray_real_T b_varargin_1;
  emxArray_real_T *b_b;
  emxArray_real_T *b_varargin_3;
  emxArray_real_T *b_y;
  emxArray_real_T *tempT;
  emxArray_real_T *varargin_1;
  emxArray_real_T *varargin_3;
  h_coder_internal_stickyStruct c_varargout_2_next_next_next_ne;
  creal_T *Ssynth_data;
  creal_T *varargout_1_data;
  creal_T *y_data;
  double scores[100];
  double stftSz[2];
  double noisePower;
  double s_im;
  double theFunc_workspace_pf;
  double *b_data;
  double *varargin_3_data;
  int b_i;
  int c_i;
  int c_varargin_1;
  int i;
  int j;
  int k;
  int loop_ub;
  int n;
  int nxout;
  int sz_idx_0;
  int sz_idx_2;
  int vlen;
  int vstride;
  int xpagesize;
  int *idx_data;
  char a_data[7];
  char *switch_expression_data;
  char *x_data;
  bool b_bool;
  bool *b_b_data;
  theFunc_workspace_pf = obj->pf;
  /* This will be the reference power for the trials. Thresholds will be */
  /* interpolated for each bin from this value based on their bin power */
  /* median(freqBinPow); */
  stftSz[0] = Wfm->stft->S->size[0];
  stftSz[1] = Wfm->stft->S->size[1];
  /* Build the Wq time correlation matrix */
  emxInitStruct_sparse(&expl_temp);
  buildtimecorrelatormatrix(Wfm->N, Wfm->M, Wfm->J, Wfm->K, &expl_temp);
  /* Here we approximated the number of samples of synthetic noise data needed
   */
  /* to get the correct number of time windows. We over estimate here and then
   */
  /* clip the number of correct windows after the stft operation. */
  s_im = (stftSz[1] + 1.0) * Wfm->n_ws + Wfm->n_ol;
  /* Based on the STFT help file for the number of windows as a function of
   * samples. We add an additional windows worth of samples to ensure we have
   * enough in our STFT output. We'll clip off any excess after the STFT */
  /* Number of sets of synthetic noise to generate */
  /* Preallocate the scores matrix */
  /* Calculate the total power in the waveform for all frequency bins. Units are
   * W/bin * # bins = W */
  emxInit_char_T(&x);
  i = x->size[0] * x->size[1];
  x->size[0] = 1;
  x->size[1] = 6;
  emxEnsureCapacity_char_T(x, i);
  x_data = x->data;
  for (i = 0; i < 6; i++) {
    x_data[i] = b[i];
  }
  emxInit_char_T(&switch_expression);
  i = switch_expression->size[0] * switch_expression->size[1];
  switch_expression->size[0] = 1;
  switch_expression->size[1] = 6;
  emxEnsureCapacity_char_T(switch_expression, i);
  switch_expression_data = switch_expression->data;
  for (k = 0; k < 6; k++) {
    switch_expression_data[k] = cv2[(int)x_data[k]];
  }
  emxFree_char_T(&x);
  b_bool = false;
  sz_idx_0 = 0;
  int exitg1;
  do {
    exitg1 = 0;
    if (sz_idx_0 < 6) {
      if (switch_expression_data[sz_idx_0] != b_cv[sz_idx_0]) {
        exitg1 = 1;
      } else {
        sz_idx_0++;
      }
    } else {
      b_bool = true;
      exitg1 = 1;
    }
  } while (exitg1 == 0);
  emxFree_char_T(&switch_expression);
  if (b_bool) {
    noisePower = stftSz[0];
  } else {
    noisePower = rt_powd_snf(10.0, (stftSz[0] - 30.0) / 10.0);
  }
  for (i = 0; i < 7; i++) {
    a_data[i] = b_cv1[i];
  }
  b_bool = (cv2[(int)a_data[0]] == 'r');
  emxInit_creal_T(&varargout_1, 2);
  if (b_bool) {
    noisePower = sqrt(noisePower);
    emxInit_real_T(&b_b, 2);
    b_randn(s_im, b_b);
    b_data = b_b->data;
    i = varargout_1->size[0] * varargout_1->size[1];
    varargout_1->size[0] = b_b->size[0];
    varargout_1->size[1] = 100;
    emxEnsureCapacity_creal_T(varargout_1, i);
    varargout_1_data = varargout_1->data;
    loop_ub = b_b->size[0] * 100;
    for (i = 0; i < loop_ub; i++) {
      varargout_1_data[i].re = noisePower * b_data[i];
      varargout_1_data[i].im = 0.0;
    }
    emxFree_real_T(&b_b);
  } else {
    noisePower = sqrt(noisePower);
    complexLike(s_im, varargout_1);
    loop_ub = varargout_1->size[0] * 100;
    i = varargout_1->size[0] * varargout_1->size[1];
    varargout_1->size[1] = 100;
    emxEnsureCapacity_creal_T(varargout_1, i);
    varargout_1_data = varargout_1->data;
    for (i = 0; i < loop_ub; i++) {
      varargout_1_data[i].re *= noisePower;
      varargout_1_data[i].im *= noisePower;
    }
  }
  /* Generate the synthetic data */
  emxInit_real_T(&varargin_3, 1);
  i = varargin_3->size[0];
  varargin_3->size[0] = Wfm->stft->wind->size[0];
  emxEnsureCapacity_real_T(varargin_3, i);
  b_data = varargin_3->data;
  loop_ub = Wfm->stft->wind->size[0];
  for (i = 0; i < loop_ub; i++) {
    b_data[i] = Wfm->stft->wind->data[i];
  }
  if (varargout_1->size[0] == 1) {
    i = varargout_1->size[0] * varargout_1->size[1];
    varargout_1->size[0] = 100;
    varargout_1->size[1] = 1;
    emxEnsureCapacity_creal_T(varargout_1, i);
  }
  c_varargout_2_next_next_next_ne.next.next.next.next.next.next.next.value =
      varargout_1->size[0];
  c_varargout_2_next_next_next_ne.value = Wfm->Fs;
  emxInit_real_T(&b_varargin_3, 1);
  i = b_varargin_3->size[0];
  b_varargin_3->size[0] = varargin_3->size[0];
  emxEnsureCapacity_real_T(b_varargin_3, i);
  varargin_3_data = b_varargin_3->data;
  loop_ub = varargin_3->size[0] - 1;
  for (i = 0; i <= loop_ub; i++) {
    varargin_3_data[i] = b_data[i];
  }
  emxInit_creal_T(&Ssynth, 3);
  emxInit_real_T(&tempT, 2);
  computeSTFT(varargout_1, Wfm->n_w, Wfm->n_ol, varargin_3->size[0],
              b_varargin_3, c_varargout_2_next_next_next_ne, Ssynth, varargin_3,
              tempT);
  Ssynth_data = Ssynth->data;
  emxFree_real_T(&b_varargin_3);
  emxFree_creal_T(&varargout_1);
  emxFree_real_T(&tempT);
  emxFree_real_T(&varargin_3);
  emxInit_int32_T(&idx, 2);
  i = idx->size[0] * idx->size[1];
  idx->size[0] = 1;
  sz_idx_2 = (int)stftSz[1];
  idx->size[1] = Ssynth->size[1] - sz_idx_2;
  emxEnsureCapacity_int32_T(idx, i);
  idx_data = idx->data;
  loop_ub = Ssynth->size[1] - sz_idx_2;
  for (i = 0; i < loop_ub; i++) {
    idx_data[i] = (sz_idx_2 + i) + 1;
  }
  emxInit_creal_T(&b_x, 3);
  i = b_x->size[0] * b_x->size[1] * b_x->size[2];
  b_x->size[0] = Ssynth->size[0];
  b_x->size[1] = Ssynth->size[1];
  b_x->size[2] = Ssynth->size[2];
  emxEnsureCapacity_creal_T(b_x, i);
  varargout_1_data = b_x->data;
  loop_ub = Ssynth->size[0] * Ssynth->size[1] * Ssynth->size[2];
  for (i = 0; i < loop_ub; i++) {
    varargout_1_data[i] = Ssynth_data[i];
  }
  vlen = Ssynth->size[1];
  emxInit_boolean_T(&c_b, 2);
  i = c_b->size[0] * c_b->size[1];
  c_b->size[0] = 1;
  c_b->size[1] = Ssynth->size[1];
  emxEnsureCapacity_boolean_T(c_b, i);
  b_b_data = c_b->data;
  loop_ub = Ssynth->size[1];
  for (i = 0; i < loop_ub; i++) {
    b_b_data[i] = false;
  }
  i = (Ssynth->size[1] - sz_idx_2) - 1;
  for (k = 0; k <= i; k++) {
    b_b_data[idx_data[k] - 1] = true;
  }
  emxFree_int32_T(&idx);
  n = 0;
  i = c_b->size[1];
  for (k = 0; k < i; k++) {
    n += b_b_data[k];
  }
  nxout = Ssynth->size[1] - n;
  sz_idx_0 = Ssynth->size[0];
  sz_idx_2 = Ssynth->size[2];
  i = Ssynth->size[0] * Ssynth->size[1] * Ssynth->size[2];
  Ssynth->size[0] = sz_idx_0;
  Ssynth->size[1] = nxout;
  Ssynth->size[2] = sz_idx_2;
  emxEnsureCapacity_creal_T(Ssynth, i);
  Ssynth_data = Ssynth->data;
  vstride = b_x->size[0];
  xpagesize = vlen * b_x->size[0];
  sz_idx_0 = nxout * b_x->size[0];
  i = b_x->size[2];
  for (b_i = 0; b_i < i; b_i++) {
    sz_idx_2 = b_i * xpagesize;
    nxout = b_i * sz_idx_0;
    for (k = 0; k < vlen; k++) {
      if ((k + 1 > c_b->size[1]) || (!b_b_data[k])) {
        for (j = 0; j < vstride; j++) {
          Ssynth_data[nxout + j] = varargout_1_data[sz_idx_2 + j];
        }
        nxout += vstride;
      }
      sz_idx_2 += vstride;
    }
  }
  emxFree_boolean_T(&c_b);
  emxFree_creal_T(&b_x);
  /* Trim excess so we have the correct number of windows. */
  /* Preform the incoherent summation using a matrix multiply. */
  /* Could use pagetimes.m for this, but it isn't supported for code generation
   */
  /* Build the distribution for all scores. */
  /* Old kernel density estimation method */
  /*  [f,xi]   =
   * ksdensity(scores(:),'BoundaryCorrection','reflection','Support','positive');
   */
  /*  F        = cumtrapz(xi,f); */
  /* Updated extreme value estimation method */
  /* xi = linspace(1/2*min(scores),2*max(scores),1000); */
  /* paramEstsMaxima = evfit(-scores); */
  /* cdfVals = evcdf(-xi,paramEstsMaxima(1),paramEstsMaxima(2)); */
  /* F = 1 - cdfVals; */
  loop_ub = Ssynth->size[1];
  xpagesize = Wfm->W->size[1];
  vlen = Wfm->W->size[0];
  n = Ssynth->size[1];
  emxInit_creal_T(&y, 2);
  emxInit_creal_T(&d_b, 2);
  emxInit_real_T(&varargin_1, 2);
  emxInit_real_T(&b_y, 2);
  for (b_i = 0; b_i < 100; b_i++) {
    i = d_b->size[0] * d_b->size[1];
    d_b->size[0] = Ssynth->size[0];
    d_b->size[1] = Ssynth->size[1];
    emxEnsureCapacity_creal_T(d_b, i);
    varargout_1_data = d_b->data;
    for (i = 0; i < loop_ub; i++) {
      sz_idx_0 = Ssynth->size[0];
      for (sz_idx_2 = 0; sz_idx_2 < sz_idx_0; sz_idx_2++) {
        varargout_1_data[sz_idx_2 + d_b->size[0] * i] =
            Ssynth_data[(sz_idx_2 + Ssynth->size[0] * i) +
                        Ssynth->size[0] * Ssynth->size[1] * b_i];
      }
    }
    i = y->size[0] * y->size[1];
    y->size[0] = Wfm->W->size[1];
    y->size[1] = Ssynth->size[1];
    emxEnsureCapacity_creal_T(y, i);
    y_data = y->data;
    for (j = 0; j < n; j++) {
      nxout = j * xpagesize;
      vstride = j * Ssynth->size[0];
      for (c_i = 0; c_i < xpagesize; c_i++) {
        sz_idx_0 = c_i * Wfm->W->size[0];
        noisePower = 0.0;
        s_im = 0.0;
        for (k = 0; k < vlen; k++) {
          double Wfm_im;
          double Wfm_re;
          sz_idx_2 = sz_idx_0 + k;
          Wfm_re = Wfm->W->data[sz_idx_2].re;
          Wfm_im = -Wfm->W->data[sz_idx_2].im;
          sz_idx_2 = vstride + k;
          noisePower += Wfm_re * varargout_1_data[sz_idx_2].re -
                        Wfm_im * varargout_1_data[sz_idx_2].im;
          s_im += Wfm_re * varargout_1_data[sz_idx_2].im +
                  Wfm_im * varargout_1_data[sz_idx_2].re;
        }
        i = nxout + c_i;
        y_data[i].re = noisePower;
        y_data[i].im = s_im;
      }
    }
    sz_idx_0 = y->size[0] * y->size[1];
    i = b_y->size[0] * b_y->size[1];
    b_y->size[0] = y->size[0];
    b_y->size[1] = y->size[1];
    emxEnsureCapacity_real_T(b_y, i);
    b_data = b_y->data;
    for (k = 0; k < sz_idx_0; k++) {
      b_data[k] = rt_hypotd_snf(y_data[k].re, y_data[k].im);
    }
    sz_idx_0 = b_y->size[0] * b_y->size[1];
    for (i = 0; i < sz_idx_0; i++) {
      s_im = b_data[i];
      b_data[i] = s_im * s_im;
    }
    sparse_mtimes(b_y, expl_temp.d, expl_temp.colidx, expl_temp.rowidx,
                  expl_temp.n, varargin_1);
    sz_idx_0 = varargin_1->size[0] * varargin_1->size[1];
    /* 'all' call finds max across all temporal correlation sets and frequency
     * bins just like we do in the dectection code. */
    b_varargin_1 = *varargin_1;
    c_varargin_1 = sz_idx_0;
    b_varargin_1.size = &c_varargin_1;
    b_varargin_1.numDimensions = 1;
    scores[b_i] = -maximum(&b_varargin_1);
  }
  emxFreeStruct_sparse(&expl_temp);
  emxFree_real_T(&b_y);
  emxFree_real_T(&varargin_1);
  emxFree_creal_T(&d_b);
  emxFree_creal_T(&y);
  emxFree_creal_T(&Ssynth);
  evfit(scores, stftSz);
  /* theFunc = @(x) 1-exp(-exp((x-mu)/sigma));%Equivalent to evcdf(x,mu,sigma)
   */
  /* theFunc = @(x) exp(-exp((x-mu)/sigma));%Equivalent to 1-evcdf(x,mu,sigma)
   */
  /* Equivalent to 1-evcdf(x,mu,sigma)-pf */
  /* theFunc monitonically decrease, so starting at x = 0 should always converge
   */
  /* figure;plot(xi,F) */
  /* Uncomment to see how fitted distribution compares to histogram of max */
  /* scores */
  /*              p = evpdf(-xi,paramEstsMaxima(1),paramEstsMaxima(2)); */
  /*              figure */
  /*              histogram(scores,'Normalization','pdf'); */
  /*              hold on */
  /*              plot(xi,p,'DisplayName','EV Fit'); legend('Location','best')
   */
  /*              p = 1-evcdf(-xi,paramEstsMaxima(1),paramEstsMaxima(2)); */
  /*              figure */
  /*              histogram(scores,'Normalization','cdf'); */
  /*              hold on */
  /*              plot(xi,p,'DisplayName','EV Fit'); legend('Location','best')
   */
  /* Now we linearly interpolate the threshold values for different noise */
  /* powers. We showed elsewhere this linear relationship hold by calculating */
  /* thresholds for ranges of noise power. */
  /* Here we deal with points where there is no change in F. Interp needs */
  /* unique values and at the tails of the distibution, there may be repeated */
  /* values. */
  /* nochangelogic = [false,diff(F)==0]; */
  /* threshMedPow =
   * interp1(F(~nochangelogic),xi(~nochangelogic),1-PF,'pchip','extrap'); */
  /*              powGrid    = [0 medPowAllFreqBins]; */
  /*              threshGrid = [0 threshMedPow]; */
  /*              newThresh =
   * interp1(powGrid,threshGrid,freqBinPow,'linear','extrap'); */
  /*   */
  /*              %Finally,extrapolating the thresholds that are a little beyond
   * the original */
  /*              %frequeny range can result in negative thresholds. Here we
   * copy the first */
  /*              %and last valid threshold out to the places where the
   * extrapolations would */
  /*              %have occured */
  /*              isnanThreshLogic   = isnan(newThresh); */
  /*              firstTrueThreshInd = find(~isnanThreshLogic,1,'first'); */
  /*              lastTrueThreshInd  = find(~isnanThreshLogic,1,'last'); */
  /*              firstTrueThresh    = newThresh(firstTrueThreshInd); */
  /*              lastTrueThresh     = newThresh(lastTrueThreshInd); */
  /*              newThresh(1:firstTrueThreshInd(1))  = firstTrueThresh; %The
   * (1) call is needed by coder, as it doesn't know that the find call above
   * will only produced a scalar output. */
  /*              newThresh(lastTrueThreshInd(1):end) = lastTrueThresh; %The (1)
   * call is needed by coder, as it doesn't know that the find call above will
   * only produced a scalar output. */
  /*              %toc */
  /*               */
  /*              obj.thresh1W        = threshMedPow; */
  /*              obj.threshVecCoarse = newThresh; */
  /*              obj.threshVecFine   =
   * interp1(Wfm.stft.f,double(newThresh),Wfm.Wf,'linear','extrap'); */
  obj->evMuParam = stftSz[0];
  obj->evSigmaParam = stftSz[1];
  threshold_setthreshprops(
      obj, fzero(stftSz[0], stftSz[1], theFunc_workspace_pf), Wfm);
}

/*
 * Wq depends on N M J K
 * if old and new N, M, J, K, W, Wf are the same
 *    copy over the fit parameters from prev to curr then
 *    use the updatepf method to set the others
 * else
 *    use the makenewthreshold method to build out
 *
 * Arguments    : threshold *obj
 *                const waveform *WfmCurr
 *                const waveform *WfmPrev
 * Return Type  : void
 */
void threshold_setthreshold(threshold *obj, const waveform *WfmCurr,
                            const waveform *WfmPrev)
{
  emxArray_boolean_T *b_x;
  emxArray_boolean_T *x;
  int i;
  int loop_ub;
  bool b;
  bool b1;
  bool b2;
  bool b_varargout_1;
  bool exitg1;
  bool needsUpdate;
  bool varargout_1;
  bool *b_x_data;
  bool *x_data;
  needsUpdate = (WfmCurr->N != WfmPrev->N);
  b = (WfmCurr->M != WfmPrev->M);
  b1 = (WfmCurr->J != WfmPrev->J);
  b2 = (WfmCurr->K != WfmPrev->K);
  emxInit_boolean_T(&x, 2);
  if ((WfmCurr->W->size[0] == WfmPrev->W->size[0]) &&
      (WfmCurr->W->size[1] == WfmPrev->W->size[1])) {
    i = x->size[0] * x->size[1];
    x->size[0] = WfmCurr->W->size[0];
    x->size[1] = WfmCurr->W->size[1];
    emxEnsureCapacity_boolean_T(x, i);
    x_data = x->data;
    loop_ub = WfmCurr->W->size[0] * WfmCurr->W->size[1];
    for (i = 0; i < loop_ub; i++) {
      x_data[i] = ((WfmCurr->W->data[i].re != WfmPrev->W->data[i].re) ||
                   (WfmCurr->W->data[i].im != WfmPrev->W->data[i].im));
    }
  } else {
    w_binary_expand_op(x, WfmCurr, WfmPrev);
    x_data = x->data;
  }
  emxInit_boolean_T(&b_x, 1);
  if (WfmCurr->Wf->size[0] == WfmPrev->Wf->size[0]) {
    i = b_x->size[0];
    b_x->size[0] = WfmCurr->Wf->size[0];
    emxEnsureCapacity_boolean_T(b_x, i);
    b_x_data = b_x->data;
    loop_ub = WfmCurr->Wf->size[0];
    for (i = 0; i < loop_ub; i++) {
      b_x_data[i] = (WfmCurr->Wf->data[i] != WfmPrev->Wf->data[i]);
    }
  } else {
    v_binary_expand_op(b_x, WfmCurr, WfmPrev);
    b_x_data = b_x->data;
  }
  varargout_1 = false;
  loop_ub = 1;
  exitg1 = false;
  while ((!exitg1) && (loop_ub <= x->size[0] * x->size[1])) {
    if (x_data[loop_ub - 1]) {
      varargout_1 = true;
      exitg1 = true;
    } else {
      loop_ub++;
    }
  }
  emxFree_boolean_T(&x);
  b_varargout_1 = false;
  loop_ub = 1;
  exitg1 = false;
  while ((!exitg1) && (loop_ub <= b_x->size[0])) {
    if (b_x_data[loop_ub - 1]) {
      b_varargout_1 = true;
      exitg1 = true;
    } else {
      loop_ub++;
    }
  }
  emxFree_boolean_T(&b_x);
  if (needsUpdate || b || b1 || b2 || varargout_1 || b_varargout_1) {
    threshold_makenewthreshold(obj, WfmCurr);
  } else {
    double b_val;
    double val;
    val = WfmPrev->thresh.evMuParam;
    obj->evMuParam = val;
    b_val = WfmPrev->thresh.evSigmaParam;
    obj->evSigmaParam = b_val;
    printf("%f\n", val);
    fflush(stdout);
    printf("%f\n", val);
    fflush(stdout);
    printf("%f\n", obj->pf);
    fflush(stdout);
    /* theFunc = @(x) 1-exp(-exp((x-mu)/sigma));%Equivalent to evcdf(x,mu,sigma)
     */
    /* theFunc = @(x) exp(-exp((x-mu)/sigma));%Equivalent to 1-evcdf(x,mu,sigma)
     */
    /* Equivalent to 1-evcdf(x,mu,sigma)-pf */
    /* theFunc monitonically decrease, so starting at x = 0 should always
     * converge */
    /* Build a single threshold value at 1 W bin power */
    threshold_setthreshprops(obj, fzero(val, b_val, obj->pf), WfmCurr);
    /* Set thresholds for each bin based on their bin powers */
    /* Not actually updating the pf, just using the method to set all the other
     * parameters */
  }
}

/*
 * UNTITLED2 Construct an instance of this class
 *    Detailed explanation goes here
 *
 * Arguments    : double pf
 *                double *obj_pf
 *                double *obj_evMuParam
 *                double *obj_evSigmaParam
 *                emxArray_real_T *obj_threshVecFine
 * Return Type  : void
 */
void threshold_threshold(double pf, double *obj_pf, double *obj_evMuParam,
                         double *obj_evSigmaParam,
                         emxArray_real_T *obj_threshVecFine)
{
  double *obj_threshVecFine_data;
  int i;
  i = obj_threshVecFine->size[0];
  obj_threshVecFine->size[0] = 1;
  emxEnsureCapacity_real_T(obj_threshVecFine, i);
  obj_threshVecFine_data = obj_threshVecFine->data;
  obj_threshVecFine_data[0] = 0.0;
  *obj_pf = pf;
  *obj_evMuParam = 0.0;
  *obj_evSigmaParam = 0.0;
}

/*
 * File trailer for threshold.c
 *
 * [EOF]
 */
