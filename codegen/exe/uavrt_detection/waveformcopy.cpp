//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: waveformcopy.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 22-Oct-2022 12:48:10
//

// Include Files
#include "waveformcopy.h"
#include "makepulsestruc.h"
#include "pulsestats.h"
#include "rt_nonfinite.h"
#include "threshold.h"
#include "uavrt_detection_internal_types.h"
#include "validator_check_size.h"
#include "waveform.h"
#include "wfmstft.h"
#include "coder_array.h"

// Function Definitions
//
// WAVEFORMCOPY makes a copy of the input waveform. Waveforms are handle
// objects, as are some of their properties. This function make new instances
// of these objects.
//
// INPUTS:
//    wfmIn   an individual waveform
// OUTPUTS
//    wfmOut  copy of input waveform
//
//
// Arguments    : waveform *wfmIn
//                wfmstft *iobj_0
//                pulsestats *iobj_1
//                waveform *iobj_2
// Return Type  : waveform *
//
waveform *waveformcopy(waveform *wfmIn, wfmstft *iobj_0, pulsestats *iobj_1,
                       waveform *iobj_2)
{
  pulsestats *val;
  waveform *wfmOut;
  wfmstft *obj;
  coder::array<c_struct_T, 2U> in;
  coder::array<c_struct_T, 2U> out;
  coder::array<creal_T, 2U> b_in;
  coder::array<creal32_T, 2U> c_in;
  coder::array<double, 2U> c_wfmIn;
  coder::array<double, 1U> b_tmp_data;
  coder::array<double, 1U> c_val;
  coder::array<double, 1U> d_tmp_data;
  coder::array<double, 1U> d_val;
  coder::array<double, 1U> f_tmp_data;
  coder::array<double, 1U> g_tmp_data;
  coder::array<double, 1U> h_tmp_data;
  coder::array<boolean_T, 2U> b_wfmIn;
  c_struct_T r;
  double c_tmp_data[2000];
  double tmp_data[400];
  double e_tmp_data[200];
  double d_wfmIn[2];
  double in_im;
  double in_re;
  int inVectorLength;
  // WAVEFORM Constructs an instance of this class
  // INPUTS:
  //    x       1xn     Vector of samples
  //    Fs      1x1     Sample frequency (Hz)
  //    t_0     1x1     Time stamp of first element (s)
  // 	ps_pre  1x1     Pulse stats object from previous data (priori)
  //    OLF     1x1     Overlap fraction as decimal (0.5 = 50%
  //                    overlap)
  // OUTPUTS:
  //    obj             The waveform object
  //             %%
  wfmOut = iobj_2;
  iobj_2->x.set_size(1, 0);
  iobj_2->W.set_size(0, 0);
  b_tmp_data.set(&tmp_data[0], 0);
  coder::internal::validator_check_size(b_tmp_data, iobj_2->Wf);
  iobj_2->thresh.init();
  // Set custom types for coder.
  // WFMSTFT Constructs and returns an instance of this class
  //
  // An waveform object must be passed to this construction method
  // so that the constructor has access to the data vector, desired
  // overlap fraction, and priori pulse data, which is used to
  // develop the window sizes.
  // INPUTS:
  //    waveform_obj   A single waveform object with prior
  //                   dependent properties set.
  // OUTPUTS:
  //    obj             A wfmstft object
  //             %%
  //
  // The following are variable sized properties. To tell coder
  // that they may vary setup as a local variable size variable
  // first, then set.
  // Instructions on
  // https://www.mathworks.com/help/simulink/ug/how-working-with-matlab-classes-is-different-for-code-generation.html
  // maxFs*maxpulsewidth
  // Now actually assign them
  iobj_0->S.set_size(0, 0);
  d_tmp_data.set(&c_tmp_data[0], 0);
  coder::internal::validator_check_size(d_tmp_data, iobj_0->t);
  f_tmp_data.set(&e_tmp_data[0], 0);
  coder::internal::validator_check_size(f_tmp_data, iobj_0->f);
  g_tmp_data.set(&e_tmp_data[0], 0);
  coder::internal::validator_check_size(g_tmp_data, iobj_0->psd);
  h_tmp_data.set(&e_tmp_data[0], 0);
  coder::internal::validator_check_size(h_tmp_data, iobj_0->wind);
  iobj_0->dt = 0.0;
  iobj_0->T = 0.0;
  iobj_2->stft = iobj_0;
  // PULSESTATS Constructs an instance of this class
  //
  // INPUTS:
  //    tp      1x1     Duration of pulse (second)
  //    tip     1x1     Inter-pulse time (seconds)
  //    tipu    1x1     Inter-pulse time uncertainty (seconds)
  //    tipj    1x1     Inter-pulse time jitter (deviations from means)
  //    (seconds) fp      1x1     Pulses' center frequency (Hz) (if known)
  //    fstart  1x1     Lower frequency bound pulses' center frequency (Hz) (if
  //    known) fend    1x1     Upper frequency bound pulses' center frequency
  //    (Hz) (if known) tmplt   1xn     Pulse template. See properies for
  //                    definition. Usually set to [1 1] for
  //                    square pulse.
  //    pl      px1     Vector of pulse objects in waveform (if
  //                    known). If unknown enter a blank pulse made
  //                    from the contstructor "pulse";
  //  Note: Unknown inputs should be set to NaN.
  //
  // OUTPUTS:
  //    pulsestats object
  //
  //             %%
  // Tell coder these are variable size.
  // Now actually assign them
  makepulsestruc(&r.A, &r.P, &r.SNR, &r.yw, &r.t_0, &r.t_f, r.t_next, &r.fp,
                 &r.fstart, &r.fend, r.mode, &r.det_dec, &r.con_dec);
  out.set_size(1, 1);
  out[0] = r;
  (&iobj_1[0])[0].pl.set_size(1, 1);
  (&iobj_1[0])[0].pl[0] = out[0];
  makepulsestruc(&r.A, &r.P, &r.SNR, &r.yw, &r.t_0, &r.t_f, r.t_next, &r.fp,
                 &r.fstart, &r.fend, r.mode, &r.det_dec, &r.con_dec);
  in.set_size(1, 1);
  in[0] = r;
  (&iobj_1[0])[0].clst.set_size(1, 1);
  (&iobj_1[0])[0].clst[0] = in[0];
  (&iobj_1[0])[0].cmsk.set_size(0, 0);
  (&iobj_1[0])[0].cpki.set_size(0, 0);
  iobj_2->ps_pre = &(&iobj_1[0])[0];
  // PULSESTATS Constructs an instance of this class
  //
  // INPUTS:
  //    tp      1x1     Duration of pulse (second)
  //    tip     1x1     Inter-pulse time (seconds)
  //    tipu    1x1     Inter-pulse time uncertainty (seconds)
  //    tipj    1x1     Inter-pulse time jitter (deviations from means)
  //    (seconds) fp      1x1     Pulses' center frequency (Hz) (if known)
  //    fstart  1x1     Lower frequency bound pulses' center frequency (Hz) (if
  //    known) fend    1x1     Upper frequency bound pulses' center frequency
  //    (Hz) (if known) tmplt   1xn     Pulse template. See properies for
  //                    definition. Usually set to [1 1] for
  //                    square pulse.
  //    pl      px1     Vector of pulse objects in waveform (if
  //                    known). If unknown enter a blank pulse made
  //                    from the contstructor "pulse";
  //  Note: Unknown inputs should be set to NaN.
  //
  // OUTPUTS:
  //    pulsestats object
  //
  //             %%
  // Tell coder these are variable size.
  // Now actually assign them
  makepulsestruc(&r.A, &r.P, &r.SNR, &r.yw, &r.t_0, &r.t_f, r.t_next, &r.fp,
                 &r.fstart, &r.fend, r.mode, &r.det_dec, &r.con_dec);
  out.set_size(1, 1);
  out[0] = r;
  (&iobj_1[0])[1].pl.set_size(1, 1);
  (&iobj_1[0])[1].pl[0] = out[0];
  makepulsestruc(&r.A, &r.P, &r.SNR, &r.yw, &r.t_0, &r.t_f, r.t_next, &r.fp,
                 &r.fstart, &r.fend, r.mode, &r.det_dec, &r.con_dec);
  in.set_size(1, 1);
  in[0] = r;
  (&iobj_1[0])[1].clst.set_size(1, 1);
  (&iobj_1[0])[1].clst[0] = in[0];
  (&iobj_1[0])[1].cmsk.set_size(0, 0);
  (&iobj_1[0])[1].cpki.set_size(0, 0);
  iobj_2->ps_pos = &(&iobj_1[0])[1];
  out.set_size(1, wfmIn->ps_pre->pl.size(1));
  inVectorLength = wfmIn->ps_pre->pl.size(0) * wfmIn->ps_pre->pl.size(1) - 1;
  for (int i{0}; i <= inVectorLength; i++) {
    out[i] = wfmIn->ps_pre->pl[i];
  }
  in.set_size(wfmIn->ps_pre->clst.size(0), wfmIn->ps_pre->clst.size(1));
  inVectorLength =
      wfmIn->ps_pre->clst.size(0) * wfmIn->ps_pre->clst.size(1) - 1;
  for (int i{0}; i <= inVectorLength; i++) {
    in[i] = wfmIn->ps_pre->clst[i];
  }
  b_wfmIn.set_size(wfmIn->ps_pre->cmsk.size(0), wfmIn->ps_pre->cmsk.size(1));
  inVectorLength =
      wfmIn->ps_pre->cmsk.size(0) * wfmIn->ps_pre->cmsk.size(1) - 1;
  for (int i{0}; i <= inVectorLength; i++) {
    b_wfmIn[i] = wfmIn->ps_pre->cmsk[i];
  }
  c_wfmIn.set_size(wfmIn->ps_pre->cpki.size(0), wfmIn->ps_pre->cpki.size(1));
  inVectorLength =
      wfmIn->ps_pre->cpki.size(0) * wfmIn->ps_pre->cpki.size(1) - 1;
  for (int i{0}; i <= inVectorLength; i++) {
    c_wfmIn[i] = wfmIn->ps_pre->cpki[i];
  }
  d_wfmIn[0] = wfmIn->ps_pre->tmplt[0];
  d_wfmIn[1] = wfmIn->ps_pre->tmplt[1];
  val = iobj_1[2].b_init(wfmIn->ps_pre->t_p, wfmIn->ps_pre->t_ip,
                         wfmIn->ps_pre->t_ipu, wfmIn->ps_pre->t_ipj,
                         wfmIn->ps_pre->fp, wfmIn->ps_pre->fstart,
                         wfmIn->ps_pre->fend, d_wfmIn, wfmIn->ps_pre->mode, out,
                         in, b_wfmIn, c_wfmIn);
  iobj_2->ps_pre = val;
  out.set_size(1, wfmIn->ps_pos->pl.size(1));
  inVectorLength = wfmIn->ps_pos->pl.size(0) * wfmIn->ps_pos->pl.size(1) - 1;
  for (int i{0}; i <= inVectorLength; i++) {
    out[i] = wfmIn->ps_pos->pl[i];
  }
  in.set_size(wfmIn->ps_pos->clst.size(0), wfmIn->ps_pos->clst.size(1));
  inVectorLength =
      wfmIn->ps_pos->clst.size(0) * wfmIn->ps_pos->clst.size(1) - 1;
  for (int i{0}; i <= inVectorLength; i++) {
    in[i] = wfmIn->ps_pos->clst[i];
  }
  b_wfmIn.set_size(wfmIn->ps_pos->cmsk.size(0), wfmIn->ps_pos->cmsk.size(1));
  inVectorLength =
      wfmIn->ps_pos->cmsk.size(0) * wfmIn->ps_pos->cmsk.size(1) - 1;
  for (int i{0}; i <= inVectorLength; i++) {
    b_wfmIn[i] = wfmIn->ps_pos->cmsk[i];
  }
  c_wfmIn.set_size(wfmIn->ps_pos->cpki.size(0), wfmIn->ps_pos->cpki.size(1));
  inVectorLength =
      wfmIn->ps_pos->cpki.size(0) * wfmIn->ps_pos->cpki.size(1) - 1;
  for (int i{0}; i <= inVectorLength; i++) {
    c_wfmIn[i] = wfmIn->ps_pos->cpki[i];
  }
  threshold b_val;
  d_wfmIn[0] = wfmIn->ps_pos->tmplt[0];
  d_wfmIn[1] = wfmIn->ps_pos->tmplt[1];
  val = iobj_1[3].b_init(wfmIn->ps_pos->t_p, wfmIn->ps_pos->t_ip,
                         wfmIn->ps_pos->t_ipu, wfmIn->ps_pos->t_ipj,
                         wfmIn->ps_pos->fp, wfmIn->ps_pos->fstart,
                         wfmIn->ps_pos->fend, d_wfmIn, wfmIn->ps_pos->mode, out,
                         in, b_wfmIn, c_wfmIn);
  iobj_2->ps_pos = val;
  b_val = wfmIn->thresh;
  iobj_2->thresh = b_val;
  obj = iobj_2->stft;
  b_in.set_size(wfmIn->stft->S.size(0), wfmIn->stft->S.size(1));
  inVectorLength = wfmIn->stft->S.size(0) * wfmIn->stft->S.size(1);
  for (int i{0}; i < inVectorLength; i++) {
    b_in[i] = wfmIn->stft->S[i];
  }
  if ((b_in.size(0) == 1) && (b_in.size(1) == 1)) {
    in_re = b_in[0].re;
    in_im = b_in[0].im;
    b_in.set_size(1, 1);
    b_in[0].re = in_re;
    b_in[0].im = in_im;
  }
  obj->S.set_size(b_in.size(0), b_in.size(1));
  inVectorLength = b_in.size(0) * b_in.size(1);
  for (int i{0}; i < inVectorLength; i++) {
    obj->S[i] = b_in[i];
  }
  obj = iobj_2->stft;
  c_val.set_size(wfmIn->stft->f.size(0));
  inVectorLength = wfmIn->stft->f.size(0);
  for (int i{0}; i < inVectorLength; i++) {
    c_val[i] = wfmIn->stft->f[i];
  }
  d_val.set_size(c_val.size(0));
  inVectorLength = c_val.size(0) - 1;
  for (int i{0}; i <= inVectorLength; i++) {
    d_val[i] = c_val[i];
  }
  coder::internal::validator_check_size(d_val, c_val);
  obj->f.set_size(c_val.size(0));
  inVectorLength = c_val.size(0);
  for (int i{0}; i < inVectorLength; i++) {
    obj->f[i] = c_val[i];
  }
  obj = iobj_2->stft;
  c_val.set_size(wfmIn->stft->t.size(0));
  inVectorLength = wfmIn->stft->t.size(0);
  for (int i{0}; i < inVectorLength; i++) {
    c_val[i] = wfmIn->stft->t[i];
  }
  d_val.set_size(c_val.size(0));
  inVectorLength = c_val.size(0) - 1;
  for (int i{0}; i <= inVectorLength; i++) {
    d_val[i] = c_val[i];
  }
  coder::internal::validator_check_size(d_val, c_val);
  obj->t.set_size(c_val.size(0));
  inVectorLength = c_val.size(0);
  for (int i{0}; i < inVectorLength; i++) {
    obj->t[i] = c_val[i];
  }
  obj = iobj_2->stft;
  c_val.set_size(wfmIn->stft->psd.size(0));
  inVectorLength = wfmIn->stft->psd.size(0);
  for (int i{0}; i < inVectorLength; i++) {
    c_val[i] = wfmIn->stft->psd[i];
  }
  d_val.set_size(c_val.size(0));
  inVectorLength = c_val.size(0) - 1;
  for (int i{0}; i <= inVectorLength; i++) {
    d_val[i] = c_val[i];
  }
  coder::internal::validator_check_size(d_val, c_val);
  obj->psd.set_size(c_val.size(0));
  inVectorLength = c_val.size(0);
  for (int i{0}; i < inVectorLength; i++) {
    obj->psd[i] = c_val[i];
  }
  obj = iobj_2->stft;
  in_re = wfmIn->stft->dt;
  obj->dt = in_re;
  obj = iobj_2->stft;
  in_re = wfmIn->stft->T;
  obj->T = in_re;
  obj = iobj_2->stft;
  c_val.set_size(wfmIn->stft->wind.size(0));
  inVectorLength = wfmIn->stft->wind.size(0);
  for (int i{0}; i < inVectorLength; i++) {
    c_val[i] = wfmIn->stft->wind[i];
  }
  d_val.set_size(c_val.size(0));
  inVectorLength = c_val.size(0) - 1;
  for (int i{0}; i <= inVectorLength; i++) {
    d_val[i] = c_val[i];
  }
  coder::internal::validator_check_size(d_val, c_val);
  obj->wind.set_size(c_val.size(0));
  inVectorLength = c_val.size(0);
  for (int i{0}; i < inVectorLength; i++) {
    obj->wind[i] = c_val[i];
  }
  in_re = wfmIn->K;
  iobj_2->K = in_re;
  c_in.set_size(1, wfmIn->x.size(1));
  inVectorLength = wfmIn->x.size(1);
  for (int i{0}; i < inVectorLength; i++) {
    c_in[i] = wfmIn->x[i];
  }
  inVectorLength = 1;
  if (c_in.size(1) != 1) {
    inVectorLength = c_in.size(1);
  }
  if (c_in.size(1) == 1) {
    float b_in_im;
    float b_in_re;
    b_in_re = c_in[0].re;
    b_in_im = c_in[0].im;
    c_in.set_size(1, inVectorLength);
    for (int i{0}; i < inVectorLength; i++) {
      c_in[i].re = b_in_re;
      c_in[i].im = b_in_im;
    }
  } else {
    c_in.set_size(1, inVectorLength);
  }
  iobj_2->x.set_size(1, c_in.size(1));
  inVectorLength = c_in.size(1);
  for (int i{0}; i < inVectorLength; i++) {
    iobj_2->x[i] = c_in[i];
  }
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
  b_in.set_size(wfmIn->W.size(0), wfmIn->W.size(1));
  inVectorLength = wfmIn->W.size(0) * wfmIn->W.size(1);
  for (int i{0}; i < inVectorLength; i++) {
    b_in[i] = wfmIn->W[i];
  }
  if ((b_in.size(0) == 1) && (b_in.size(1) == 1)) {
    in_re = b_in[0].re;
    in_im = b_in[0].im;
    b_in.set_size(1, 1);
    b_in[0].re = in_re;
    b_in[0].im = in_im;
  }
  iobj_2->W.set_size(b_in.size(0), b_in.size(1));
  inVectorLength = b_in.size(0) * b_in.size(1);
  for (int i{0}; i < inVectorLength; i++) {
    iobj_2->W[i] = b_in[i];
  }
  c_val.set_size(wfmIn->Wf.size(0));
  inVectorLength = wfmIn->Wf.size(0);
  for (int i{0}; i < inVectorLength; i++) {
    c_val[i] = wfmIn->Wf[i];
  }
  d_val.set_size(c_val.size(0));
  inVectorLength = c_val.size(0) - 1;
  for (int i{0}; i <= inVectorLength; i++) {
    d_val[i] = c_val[i];
  }
  coder::internal::validator_check_size(d_val, c_val);
  iobj_2->Wf.set_size(c_val.size(0));
  inVectorLength = c_val.size(0);
  for (int i{0}; i < inVectorLength; i++) {
    iobj_2->Wf[i] = c_val[i];
  }
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

//
// File trailer for waveformcopy.cpp
//
// [EOF]
//
