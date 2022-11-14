/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: waveformcopy.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "waveformcopy.h"
#include "makepulsestruc.h"
#include "pulsestats.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_types.h"
#include "validator_check_size.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"

/* Function Definitions */
/*
 * WAVEFORMCOPY makes a copy of the input waveform. Waveforms are handle
 * objects, as are some of their properties. This function make new instances
 * of these objects.
 *
 * INPUTS:
 *    wfmIn   an individual waveform
 * OUTPUTS
 *    wfmOut  copy of input waveform
 *
 *
 * Arguments    : const waveform *wfmIn
 *                wfmstft *iobj_0
 *                pulsestats *iobj_1
 *                waveform *iobj_2
 * Return Type  : waveform *
 */
waveform *waveformcopy(const waveform *wfmIn, wfmstft *iobj_0,
                       pulsestats *iobj_1, waveform *iobj_2)
{
  b_struct_T r;
  b_struct_T *out_data;
  emxArray_boolean_T *b_wfmIn;
  emxArray_creal32_T *in;
  emxArray_creal_T *b_in;
  emxArray_real_T b_tmp_data;
  emxArray_real_T d_tmp_data;
  emxArray_real_T f_tmp_data;
  emxArray_real_T g_tmp_data;
  emxArray_real_T h_tmp_data;
  emxArray_real_T *c_val;
  emxArray_real_T *c_wfmIn;
  emxArray_real_T *d_val;
  emxArray_struct_T *c_in;
  emxArray_struct_T *out;
  pulsestats *b_val;
  threshold val;
  waveform *wfmOut;
  wfmstft *obj;
  creal_T *in_data;
  creal32_T *b_in_data;
  double c_tmp_data[2000];
  double tmp_data[400];
  double e_tmp_data[200];
  double d_wfmIn[2];
  double in_im;
  double in_re;
  double *b_wfmIn_data;
  double *val_data;
  int b_tmp_size;
  int c_tmp_size;
  int i;
  int inVectorLength;
  int tmp_size;
  bool *wfmIn_data;
  /* WAVEFORM Constructs an instance of this class */
  /* INPUTS: */
  /*    x       1xn     Vector of samples */
  /*    Fs      1x1     Sample frequency (Hz) */
  /*    t_0     1x1     Time stamp of first element (s) */
  /* 	ps_pre  1x1     Pulse stats object from previous data (priori) */
  /*    OLF     1x1     Overlap fraction as decimal (0.5 = 50% */
  /*                    overlap) */
  /* OUTPUTS: */
  /*    obj             The waveform object */
  /*             %% */
  wfmOut = iobj_2;
  emxInit_creal32_T(&in, 2);
  iobj_2->x->size[0] = 1;
  iobj_2->x->size[1] = 0;
  emxInit_creal_T(&b_in, 2);
  iobj_2->W->size[0] = 0;
  iobj_2->W->size[1] = 0;
  tmp_size = 0;
  b_tmp_data.data = &tmp_data[0];
  b_tmp_data.size = &tmp_size;
  b_tmp_data.allocatedSize = 400;
  b_tmp_data.numDimensions = 1;
  b_tmp_data.canFreeData = false;
  validator_check_size(&b_tmp_data, iobj_2->Wf);
  emxInitStruct_threshold(&val);
  val.pf = 0.01;
  val.evMuParam = 0.0;
  val.evSigmaParam = 0.0;
  i = val.threshVecFine->size[0];
  val.threshVecFine->size[0] = 1;
  emxEnsureCapacity_real_T(val.threshVecFine, i);
  val.threshVecFine->data[0] = 0.0;
  emxCopyStruct_threshold(&iobj_2->thresh, &val);
  /* Set custom types for coder.  */
  /* WFMSTFT Constructs and returns an instance of this class */
  /*  */
  /* An waveform object must be passed to this construction method */
  /* so that the constructor has access to the data vector, desired */
  /* overlap fraction, and priori pulse data, which is used to */
  /* develop the window sizes.  */
  /* INPUTS: */
  /*    waveform_obj   A single waveform object with prior */
  /*                   dependent properties set.  */
  /* OUTPUTS: */
  /*    obj             A wfmstft object */
  /*             %% */
  /*  */
  /* The following are variable sized properties. To tell coder */
  /* that they may vary setup as a local variable size variable */
  /* first, then set. */
  /* Instructions on
   * https://www.mathworks.com/help/simulink/ug/how-working-with-matlab-classes-is-different-for-code-generation.html
   */
  /* maxFs*maxpulsewidth */
  /* Now actually assign them */
  iobj_0->S->size[0] = 0;
  iobj_0->S->size[1] = 0;
  b_tmp_size = 0;
  d_tmp_data.data = &c_tmp_data[0];
  d_tmp_data.size = &b_tmp_size;
  d_tmp_data.allocatedSize = 2000;
  d_tmp_data.numDimensions = 1;
  d_tmp_data.canFreeData = false;
  validator_check_size(&d_tmp_data, iobj_0->t);
  c_tmp_size = 0;
  f_tmp_data.data = &e_tmp_data[0];
  f_tmp_data.size = &c_tmp_size;
  f_tmp_data.allocatedSize = 200;
  f_tmp_data.numDimensions = 1;
  f_tmp_data.canFreeData = false;
  validator_check_size(&f_tmp_data, iobj_0->f);
  c_tmp_size = 0;
  g_tmp_data.data = &e_tmp_data[0];
  g_tmp_data.size = &c_tmp_size;
  g_tmp_data.allocatedSize = 200;
  g_tmp_data.numDimensions = 1;
  g_tmp_data.canFreeData = false;
  validator_check_size(&g_tmp_data, iobj_0->psd);
  c_tmp_size = 0;
  h_tmp_data.data = &e_tmp_data[0];
  h_tmp_data.size = &c_tmp_size;
  h_tmp_data.allocatedSize = 200;
  h_tmp_data.numDimensions = 1;
  h_tmp_data.canFreeData = false;
  validator_check_size(&h_tmp_data, iobj_0->wind);
  iobj_0->dt = 0.0;
  iobj_0->T = 0.0;
  iobj_2->stft = iobj_0;
  /* PULSESTATS Constructs an instance of this class */
  /*  */
  /* INPUTS: */
  /*    tp      1x1     Duration of pulse (second) */
  /*    tip     1x1     Inter-pulse time (seconds) */
  /*    tipu    1x1     Inter-pulse time uncertainty (seconds) */
  /*    tipj    1x1     Inter-pulse time jitter (deviations from means)
   * (seconds) */
  /*    fp      1x1     Pulses' center frequency (Hz) (if known) */
  /*    fstart  1x1     Lower frequency bound pulses' center frequency (Hz) (if
   * known) */
  /*    fend    1x1     Upper frequency bound pulses' center frequency (Hz) (if
   * known) */
  /*    tmplt   1xn     Pulse template. See properies for */
  /*                    definition. Usually set to [1 1] for */
  /*                    square pulse. */
  /*    pl      px1     Vector of pulse objects in waveform (if */
  /*                    known). If unknown enter a blank pulse made */
  /*                    from the contstructor "pulse"; */
  /*  Note: Unknown inputs should be set to NaN. */
  /*  */
  /* OUTPUTS: */
  /*    pulsestats object */
  /*  */
  /*             %% */
  /* Tell coder these are variable size. */
  /* Now actually assign them  */
  emxInitStruct_struct_T(&r);
  makepulsestruc(&r.A, &r.P, &r.SNR, &r.yw, &r.t_0, &r.t_f, r.t_next, &r.fp,
                 &r.fstart, &r.fend, r.mode, &r.det_dec, &r.con_dec);
  emxInit_struct_T(&out);
  i = out->size[0] * out->size[1];
  out->size[0] = 1;
  out->size[1] = 1;
  emxEnsureCapacity_struct_T(out, i);
  out_data = out->data;
  emxCopyStruct_struct_T(&out_data[0], &r);
  i = (&iobj_1[0])[0].pl->size[0] * (&iobj_1[0])[0].pl->size[1];
  (&iobj_1[0])[0].pl->size[0] = 1;
  (&iobj_1[0])[0].pl->size[1] = 1;
  emxEnsureCapacity_struct_T((&iobj_1[0])[0].pl, i);
  emxCopyStruct_struct_T(&(&iobj_1[0])[0].pl->data[0], &out_data[0]);
  makepulsestruc(&r.A, &r.P, &r.SNR, &r.yw, &r.t_0, &r.t_f, r.t_next, &r.fp,
                 &r.fstart, &r.fend, r.mode, &r.det_dec, &r.con_dec);
  emxInit_struct_T(&c_in);
  i = c_in->size[0] * c_in->size[1];
  c_in->size[0] = 1;
  c_in->size[1] = 1;
  emxEnsureCapacity_struct_T(c_in, i);
  out_data = c_in->data;
  emxCopyStruct_struct_T(&out_data[0], &r);
  i = (&iobj_1[0])[0].clst->size[0] * (&iobj_1[0])[0].clst->size[1];
  (&iobj_1[0])[0].clst->size[0] = 1;
  (&iobj_1[0])[0].clst->size[1] = 1;
  emxEnsureCapacity_struct_T((&iobj_1[0])[0].clst, i);
  emxCopyStruct_struct_T(&(&iobj_1[0])[0].clst->data[0], &out_data[0]);
  (&iobj_1[0])[0].cmsk->size[0] = 0;
  (&iobj_1[0])[0].cmsk->size[1] = 0;
  (&iobj_1[0])[0].cpki->size[0] = 0;
  (&iobj_1[0])[0].cpki->size[1] = 0;
  iobj_2->ps_pre = &(&iobj_1[0])[0];
  /* PULSESTATS Constructs an instance of this class */
  /*  */
  /* INPUTS: */
  /*    tp      1x1     Duration of pulse (second) */
  /*    tip     1x1     Inter-pulse time (seconds) */
  /*    tipu    1x1     Inter-pulse time uncertainty (seconds) */
  /*    tipj    1x1     Inter-pulse time jitter (deviations from means)
   * (seconds) */
  /*    fp      1x1     Pulses' center frequency (Hz) (if known) */
  /*    fstart  1x1     Lower frequency bound pulses' center frequency (Hz) (if
   * known) */
  /*    fend    1x1     Upper frequency bound pulses' center frequency (Hz) (if
   * known) */
  /*    tmplt   1xn     Pulse template. See properies for */
  /*                    definition. Usually set to [1 1] for */
  /*                    square pulse. */
  /*    pl      px1     Vector of pulse objects in waveform (if */
  /*                    known). If unknown enter a blank pulse made */
  /*                    from the contstructor "pulse"; */
  /*  Note: Unknown inputs should be set to NaN. */
  /*  */
  /* OUTPUTS: */
  /*    pulsestats object */
  /*  */
  /*             %% */
  /* Tell coder these are variable size. */
  /* Now actually assign them  */
  makepulsestruc(&r.A, &r.P, &r.SNR, &r.yw, &r.t_0, &r.t_f, r.t_next, &r.fp,
                 &r.fstart, &r.fend, r.mode, &r.det_dec, &r.con_dec);
  i = out->size[0] * out->size[1];
  out->size[0] = 1;
  out->size[1] = 1;
  emxEnsureCapacity_struct_T(out, i);
  out_data = out->data;
  emxCopyStruct_struct_T(&out_data[0], &r);
  i = (&iobj_1[0])[1].pl->size[0] * (&iobj_1[0])[1].pl->size[1];
  (&iobj_1[0])[1].pl->size[0] = 1;
  (&iobj_1[0])[1].pl->size[1] = 1;
  emxEnsureCapacity_struct_T((&iobj_1[0])[1].pl, i);
  emxCopyStruct_struct_T(&(&iobj_1[0])[1].pl->data[0], &out_data[0]);
  makepulsestruc(&r.A, &r.P, &r.SNR, &r.yw, &r.t_0, &r.t_f, r.t_next, &r.fp,
                 &r.fstart, &r.fend, r.mode, &r.det_dec, &r.con_dec);
  i = c_in->size[0] * c_in->size[1];
  c_in->size[0] = 1;
  c_in->size[1] = 1;
  emxEnsureCapacity_struct_T(c_in, i);
  out_data = c_in->data;
  emxCopyStruct_struct_T(&out_data[0], &r);
  emxFreeStruct_struct_T(&r);
  i = (&iobj_1[0])[1].clst->size[0] * (&iobj_1[0])[1].clst->size[1];
  (&iobj_1[0])[1].clst->size[0] = 1;
  (&iobj_1[0])[1].clst->size[1] = 1;
  emxEnsureCapacity_struct_T((&iobj_1[0])[1].clst, i);
  emxCopyStruct_struct_T(&(&iobj_1[0])[1].clst->data[0], &out_data[0]);
  (&iobj_1[0])[1].cmsk->size[0] = 0;
  (&iobj_1[0])[1].cmsk->size[1] = 0;
  (&iobj_1[0])[1].cpki->size[0] = 0;
  (&iobj_1[0])[1].cpki->size[1] = 0;
  iobj_2->ps_pos = &(&iobj_1[0])[1];
  i = out->size[0] * out->size[1];
  out->size[0] = 1;
  out->size[1] = wfmIn->ps_pre->pl->size[1];
  emxEnsureCapacity_struct_T(out, i);
  out_data = out->data;
  inVectorLength = wfmIn->ps_pre->pl->size[0] * wfmIn->ps_pre->pl->size[1] - 1;
  for (i = 0; i <= inVectorLength; i++) {
    emxCopyStruct_struct_T(&out_data[i], &wfmIn->ps_pre->pl->data[i]);
  }
  i = c_in->size[0] * c_in->size[1];
  c_in->size[0] = wfmIn->ps_pre->clst->size[0];
  c_in->size[1] = wfmIn->ps_pre->clst->size[1];
  emxEnsureCapacity_struct_T(c_in, i);
  out_data = c_in->data;
  inVectorLength =
      wfmIn->ps_pre->clst->size[0] * wfmIn->ps_pre->clst->size[1] - 1;
  for (i = 0; i <= inVectorLength; i++) {
    emxCopyStruct_struct_T(&out_data[i], &wfmIn->ps_pre->clst->data[i]);
  }
  emxInit_boolean_T(&b_wfmIn, 2);
  i = b_wfmIn->size[0] * b_wfmIn->size[1];
  b_wfmIn->size[0] = wfmIn->ps_pre->cmsk->size[0];
  b_wfmIn->size[1] = wfmIn->ps_pre->cmsk->size[1];
  emxEnsureCapacity_boolean_T(b_wfmIn, i);
  wfmIn_data = b_wfmIn->data;
  inVectorLength =
      wfmIn->ps_pre->cmsk->size[0] * wfmIn->ps_pre->cmsk->size[1] - 1;
  for (i = 0; i <= inVectorLength; i++) {
    wfmIn_data[i] = wfmIn->ps_pre->cmsk->data[i];
  }
  emxInit_real_T(&c_wfmIn, 2);
  i = c_wfmIn->size[0] * c_wfmIn->size[1];
  c_wfmIn->size[0] = wfmIn->ps_pre->cpki->size[0];
  c_wfmIn->size[1] = wfmIn->ps_pre->cpki->size[1];
  emxEnsureCapacity_real_T(c_wfmIn, i);
  b_wfmIn_data = c_wfmIn->data;
  inVectorLength =
      wfmIn->ps_pre->cpki->size[0] * wfmIn->ps_pre->cpki->size[1] - 1;
  for (i = 0; i <= inVectorLength; i++) {
    b_wfmIn_data[i] = wfmIn->ps_pre->cpki->data[i];
  }
  d_wfmIn[0] = wfmIn->ps_pre->tmplt[0];
  d_wfmIn[1] = wfmIn->ps_pre->tmplt[1];
  b_val = b_pulsestats_pulsestats(
      &iobj_1[2], wfmIn->ps_pre->t_p, wfmIn->ps_pre->t_ip, wfmIn->ps_pre->t_ipu,
      wfmIn->ps_pre->t_ipj, wfmIn->ps_pre->fp, wfmIn->ps_pre->fstart,
      wfmIn->ps_pre->fend, d_wfmIn, wfmIn->ps_pre->mode, out, c_in, b_wfmIn,
      c_wfmIn);
  iobj_2->ps_pre = b_val;
  i = out->size[0] * out->size[1];
  out->size[0] = 1;
  out->size[1] = wfmIn->ps_pos->pl->size[1];
  emxEnsureCapacity_struct_T(out, i);
  out_data = out->data;
  inVectorLength = wfmIn->ps_pos->pl->size[0] * wfmIn->ps_pos->pl->size[1] - 1;
  for (i = 0; i <= inVectorLength; i++) {
    emxCopyStruct_struct_T(&out_data[i], &wfmIn->ps_pos->pl->data[i]);
  }
  i = c_in->size[0] * c_in->size[1];
  c_in->size[0] = wfmIn->ps_pos->clst->size[0];
  c_in->size[1] = wfmIn->ps_pos->clst->size[1];
  emxEnsureCapacity_struct_T(c_in, i);
  out_data = c_in->data;
  inVectorLength =
      wfmIn->ps_pos->clst->size[0] * wfmIn->ps_pos->clst->size[1] - 1;
  for (i = 0; i <= inVectorLength; i++) {
    emxCopyStruct_struct_T(&out_data[i], &wfmIn->ps_pos->clst->data[i]);
  }
  i = b_wfmIn->size[0] * b_wfmIn->size[1];
  b_wfmIn->size[0] = wfmIn->ps_pos->cmsk->size[0];
  b_wfmIn->size[1] = wfmIn->ps_pos->cmsk->size[1];
  emxEnsureCapacity_boolean_T(b_wfmIn, i);
  wfmIn_data = b_wfmIn->data;
  inVectorLength =
      wfmIn->ps_pos->cmsk->size[0] * wfmIn->ps_pos->cmsk->size[1] - 1;
  for (i = 0; i <= inVectorLength; i++) {
    wfmIn_data[i] = wfmIn->ps_pos->cmsk->data[i];
  }
  i = c_wfmIn->size[0] * c_wfmIn->size[1];
  c_wfmIn->size[0] = wfmIn->ps_pos->cpki->size[0];
  c_wfmIn->size[1] = wfmIn->ps_pos->cpki->size[1];
  emxEnsureCapacity_real_T(c_wfmIn, i);
  b_wfmIn_data = c_wfmIn->data;
  inVectorLength =
      wfmIn->ps_pos->cpki->size[0] * wfmIn->ps_pos->cpki->size[1] - 1;
  for (i = 0; i <= inVectorLength; i++) {
    b_wfmIn_data[i] = wfmIn->ps_pos->cpki->data[i];
  }
  d_wfmIn[0] = wfmIn->ps_pos->tmplt[0];
  d_wfmIn[1] = wfmIn->ps_pos->tmplt[1];
  b_val = b_pulsestats_pulsestats(
      &iobj_1[3], wfmIn->ps_pos->t_p, wfmIn->ps_pos->t_ip, wfmIn->ps_pos->t_ipu,
      wfmIn->ps_pos->t_ipj, wfmIn->ps_pos->fp, wfmIn->ps_pos->fstart,
      wfmIn->ps_pos->fend, d_wfmIn, wfmIn->ps_pos->mode, out, c_in, b_wfmIn,
      c_wfmIn);
  emxFree_real_T(&c_wfmIn);
  emxFree_boolean_T(&b_wfmIn);
  emxFree_struct_T(&c_in);
  emxFree_struct_T(&out);
  iobj_2->ps_pos = b_val;
  emxCopyStruct_threshold(&val, &wfmIn->thresh);
  emxCopyStruct_threshold(&iobj_2->thresh, &val);
  emxFreeStruct_threshold(&val);
  obj = iobj_2->stft;
  i = b_in->size[0] * b_in->size[1];
  b_in->size[0] = wfmIn->stft->S->size[0];
  b_in->size[1] = wfmIn->stft->S->size[1];
  emxEnsureCapacity_creal_T(b_in, i);
  in_data = b_in->data;
  inVectorLength = wfmIn->stft->S->size[0] * wfmIn->stft->S->size[1];
  for (i = 0; i < inVectorLength; i++) {
    in_data[i] = wfmIn->stft->S->data[i];
  }
  if ((b_in->size[0] == 1) && (b_in->size[1] == 1)) {
    in_re = in_data[0].re;
    in_im = in_data[0].im;
    i = b_in->size[0] * b_in->size[1];
    b_in->size[0] = 1;
    b_in->size[1] = 1;
    emxEnsureCapacity_creal_T(b_in, i);
    in_data = b_in->data;
    in_data[0].re = in_re;
    in_data[0].im = in_im;
  }
  i = obj->S->size[0] * obj->S->size[1];
  obj->S->size[0] = b_in->size[0];
  obj->S->size[1] = b_in->size[1];
  emxEnsureCapacity_creal_T(obj->S, i);
  inVectorLength = b_in->size[0] * b_in->size[1];
  for (i = 0; i < inVectorLength; i++) {
    obj->S->data[i] = in_data[i];
  }
  obj = iobj_2->stft;
  emxInit_real_T(&c_val, 1);
  i = c_val->size[0];
  c_val->size[0] = wfmIn->stft->f->size[0];
  emxEnsureCapacity_real_T(c_val, i);
  b_wfmIn_data = c_val->data;
  inVectorLength = wfmIn->stft->f->size[0];
  for (i = 0; i < inVectorLength; i++) {
    b_wfmIn_data[i] = wfmIn->stft->f->data[i];
  }
  emxInit_real_T(&d_val, 1);
  i = d_val->size[0];
  d_val->size[0] = c_val->size[0];
  emxEnsureCapacity_real_T(d_val, i);
  val_data = d_val->data;
  inVectorLength = c_val->size[0] - 1;
  for (i = 0; i <= inVectorLength; i++) {
    val_data[i] = b_wfmIn_data[i];
  }
  validator_check_size(d_val, c_val);
  b_wfmIn_data = c_val->data;
  i = obj->f->size[0];
  obj->f->size[0] = c_val->size[0];
  emxEnsureCapacity_real_T(obj->f, i);
  inVectorLength = c_val->size[0];
  for (i = 0; i < inVectorLength; i++) {
    obj->f->data[i] = b_wfmIn_data[i];
  }
  obj = iobj_2->stft;
  i = c_val->size[0];
  c_val->size[0] = wfmIn->stft->t->size[0];
  emxEnsureCapacity_real_T(c_val, i);
  b_wfmIn_data = c_val->data;
  inVectorLength = wfmIn->stft->t->size[0];
  for (i = 0; i < inVectorLength; i++) {
    b_wfmIn_data[i] = wfmIn->stft->t->data[i];
  }
  i = d_val->size[0];
  d_val->size[0] = c_val->size[0];
  emxEnsureCapacity_real_T(d_val, i);
  val_data = d_val->data;
  inVectorLength = c_val->size[0] - 1;
  for (i = 0; i <= inVectorLength; i++) {
    val_data[i] = b_wfmIn_data[i];
  }
  validator_check_size(d_val, c_val);
  b_wfmIn_data = c_val->data;
  i = obj->t->size[0];
  obj->t->size[0] = c_val->size[0];
  emxEnsureCapacity_real_T(obj->t, i);
  inVectorLength = c_val->size[0];
  for (i = 0; i < inVectorLength; i++) {
    obj->t->data[i] = b_wfmIn_data[i];
  }
  obj = iobj_2->stft;
  i = c_val->size[0];
  c_val->size[0] = wfmIn->stft->psd->size[0];
  emxEnsureCapacity_real_T(c_val, i);
  b_wfmIn_data = c_val->data;
  inVectorLength = wfmIn->stft->psd->size[0];
  for (i = 0; i < inVectorLength; i++) {
    b_wfmIn_data[i] = wfmIn->stft->psd->data[i];
  }
  i = d_val->size[0];
  d_val->size[0] = c_val->size[0];
  emxEnsureCapacity_real_T(d_val, i);
  val_data = d_val->data;
  inVectorLength = c_val->size[0] - 1;
  for (i = 0; i <= inVectorLength; i++) {
    val_data[i] = b_wfmIn_data[i];
  }
  validator_check_size(d_val, c_val);
  b_wfmIn_data = c_val->data;
  i = obj->psd->size[0];
  obj->psd->size[0] = c_val->size[0];
  emxEnsureCapacity_real_T(obj->psd, i);
  inVectorLength = c_val->size[0];
  for (i = 0; i < inVectorLength; i++) {
    obj->psd->data[i] = b_wfmIn_data[i];
  }
  obj = iobj_2->stft;
  in_re = wfmIn->stft->dt;
  obj->dt = in_re;
  obj = iobj_2->stft;
  in_re = wfmIn->stft->T;
  obj->T = in_re;
  obj = iobj_2->stft;
  i = c_val->size[0];
  c_val->size[0] = wfmIn->stft->wind->size[0];
  emxEnsureCapacity_real_T(c_val, i);
  b_wfmIn_data = c_val->data;
  inVectorLength = wfmIn->stft->wind->size[0];
  for (i = 0; i < inVectorLength; i++) {
    b_wfmIn_data[i] = wfmIn->stft->wind->data[i];
  }
  i = d_val->size[0];
  d_val->size[0] = c_val->size[0];
  emxEnsureCapacity_real_T(d_val, i);
  val_data = d_val->data;
  inVectorLength = c_val->size[0] - 1;
  for (i = 0; i <= inVectorLength; i++) {
    val_data[i] = b_wfmIn_data[i];
  }
  validator_check_size(d_val, c_val);
  b_wfmIn_data = c_val->data;
  i = obj->wind->size[0];
  obj->wind->size[0] = c_val->size[0];
  emxEnsureCapacity_real_T(obj->wind, i);
  inVectorLength = c_val->size[0];
  for (i = 0; i < inVectorLength; i++) {
    obj->wind->data[i] = b_wfmIn_data[i];
  }
  in_re = wfmIn->K;
  iobj_2->K = in_re;
  i = in->size[0] * in->size[1];
  in->size[0] = 1;
  in->size[1] = wfmIn->x->size[1];
  emxEnsureCapacity_creal32_T(in, i);
  b_in_data = in->data;
  inVectorLength = wfmIn->x->size[1];
  for (i = 0; i < inVectorLength; i++) {
    b_in_data[i] = wfmIn->x->data[i];
  }
  inVectorLength = 1;
  if (in->size[1] != 1) {
    inVectorLength = in->size[1];
  }
  if (in->size[1] == 1) {
    float b_in_im;
    float b_in_re;
    b_in_re = b_in_data[0].re;
    b_in_im = b_in_data[0].im;
    i = in->size[0] * in->size[1];
    in->size[0] = 1;
    in->size[1] = inVectorLength;
    emxEnsureCapacity_creal32_T(in, i);
    b_in_data = in->data;
    for (i = 0; i < inVectorLength; i++) {
      b_in_data[i].re = b_in_re;
      b_in_data[i].im = b_in_im;
    }
  } else {
    i = in->size[0] * in->size[1];
    in->size[0] = 1;
    in->size[1] = inVectorLength;
    emxEnsureCapacity_creal32_T(in, i);
    b_in_data = in->data;
  }
  i = iobj_2->x->size[0] * iobj_2->x->size[1];
  iobj_2->x->size[0] = 1;
  iobj_2->x->size[1] = in->size[1];
  emxEnsureCapacity_creal32_T(iobj_2->x, i);
  inVectorLength = in->size[1];
  for (i = 0; i < inVectorLength; i++) {
    iobj_2->x->data[i] = b_in_data[i];
  }
  emxFree_creal32_T(&in);
  in_re = wfmIn->Fs;
  iobj_2->Fs = in_re;
  in_re = wfmIn->l;
  iobj_2->l = in_re;
  in_re = wfmIn->t_0;
  iobj_2->t_0 = in_re;
  in_re = wfmIn->t_f;
  iobj_2->t_0 = in_re;
  in_re = wfmIn->t_nextsegstart[0];
  in_im = wfmIn->t_nextsegstart[1];
  iobj_2->t_nextsegstart[0] = in_re;
  iobj_2->t_nextsegstart[1] = in_im;
  in_re = wfmIn->OLF;
  iobj_2->OLF = in_re;
  i = b_in->size[0] * b_in->size[1];
  b_in->size[0] = wfmIn->W->size[0];
  b_in->size[1] = wfmIn->W->size[1];
  emxEnsureCapacity_creal_T(b_in, i);
  in_data = b_in->data;
  inVectorLength = wfmIn->W->size[0] * wfmIn->W->size[1];
  for (i = 0; i < inVectorLength; i++) {
    in_data[i] = wfmIn->W->data[i];
  }
  if ((b_in->size[0] == 1) && (b_in->size[1] == 1)) {
    in_re = in_data[0].re;
    in_im = in_data[0].im;
    i = b_in->size[0] * b_in->size[1];
    b_in->size[0] = 1;
    b_in->size[1] = 1;
    emxEnsureCapacity_creal_T(b_in, i);
    in_data = b_in->data;
    in_data[0].re = in_re;
    in_data[0].im = in_im;
  }
  i = iobj_2->W->size[0] * iobj_2->W->size[1];
  iobj_2->W->size[0] = b_in->size[0];
  iobj_2->W->size[1] = b_in->size[1];
  emxEnsureCapacity_creal_T(iobj_2->W, i);
  inVectorLength = b_in->size[0] * b_in->size[1];
  for (i = 0; i < inVectorLength; i++) {
    iobj_2->W->data[i] = in_data[i];
  }
  emxFree_creal_T(&b_in);
  i = c_val->size[0];
  c_val->size[0] = wfmIn->Wf->size[0];
  emxEnsureCapacity_real_T(c_val, i);
  b_wfmIn_data = c_val->data;
  inVectorLength = wfmIn->Wf->size[0];
  for (i = 0; i < inVectorLength; i++) {
    b_wfmIn_data[i] = wfmIn->Wf->data[i];
  }
  i = d_val->size[0];
  d_val->size[0] = c_val->size[0];
  emxEnsureCapacity_real_T(d_val, i);
  val_data = d_val->data;
  inVectorLength = c_val->size[0] - 1;
  for (i = 0; i <= inVectorLength; i++) {
    val_data[i] = b_wfmIn_data[i];
  }
  validator_check_size(d_val, c_val);
  b_wfmIn_data = c_val->data;
  emxFree_real_T(&d_val);
  i = iobj_2->Wf->size[0];
  iobj_2->Wf->size[0] = c_val->size[0];
  emxEnsureCapacity_real_T(iobj_2->Wf, i);
  inVectorLength = c_val->size[0];
  for (i = 0; i < inVectorLength; i++) {
    iobj_2->Wf->data[i] = b_wfmIn_data[i];
  }
  emxFree_real_T(&c_val);
  in_re = wfmIn->n_p;
  iobj_2->n_p = in_re;
  in_re = wfmIn->n_w;
  iobj_2->n_w = in_re;
  in_re = wfmIn->n_ol;
  iobj_2->n_ol = in_re;
  in_re = wfmIn->n_ws;
  iobj_2->n_ws = in_re;
  in_re = wfmIn->t_ws;
  iobj_2->t_ws = in_re;
  in_re = wfmIn->n_ip;
  iobj_2->n_ip = in_re;
  in_re = wfmIn->N;
  iobj_2->N = in_re;
  in_re = wfmIn->M;
  iobj_2->M = in_re;
  in_re = wfmIn->J;
  iobj_2->J = in_re;
  return wfmOut;
}

/*
 * File trailer for waveformcopy.c
 *
 * [EOF]
 */
