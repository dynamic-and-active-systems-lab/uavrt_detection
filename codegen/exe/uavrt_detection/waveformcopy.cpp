//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: waveformcopy.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 16-Feb-2023 15:25:26
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
#include <string.h>

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
  pulsestats *g_val;
  waveform *wfmOut;
  wfmstft *d_val;
  coder::array<c_struct_T, 2U> _in;
  coder::array<c_struct_T, 2U> e_val;
  coder::array<c_struct_T, 2U> r4;
  coder::array<c_struct_T, 2U> r5;
  coder::array<c_struct_T, 2U> r6;
  coder::array<c_struct_T, 2U> r7;
  coder::array<creal_T, 2U> b_val;
  coder::array<creal_T, 2U> i_val;
  coder::array<creal_T, 2U> r1;
  coder::array<creal32_T, 2U> l_val;
  coder::array<creal32_T, 2U> r;
  coder::array<creal32_T, 2U> val;
  coder::array<double, 2U> b__in;
  coder::array<double, 2U> b_wfmIn;
  coder::array<double, 2U> d_tmp_data;
  coder::array<double, 2U> f_tmp_data;
  coder::array<double, 1U> b_tmp_data;
  coder::array<double, 1U> c_val;
  coder::array<double, 1U> j_val;
  coder::array<boolean_T, 2U> c_tmp_data;
  coder::array<boolean_T, 2U> e_tmp_data;
  coder::array<boolean_T, 2U> f_val;
  c_struct_T r2;
  emxArray_struct_T_1x1 r3;
  double tmp_data[400];
  double c_wfmIn[2];
  double k_val;
  int loop_ub;
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
  r.set(nullptr, 1, 0);
  coder::internal::validator_check_size(r, val);
  iobj_2->x.set_size(1, val.size(1));
  loop_ub = val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    iobj_2->x[i] = val[i];
  }
  r1.set(nullptr, 0, 0);
  coder::internal::validator_check_size(r1, b_val);
  iobj_2->W.set_size(b_val.size(0), b_val.size(1));
  loop_ub = b_val.size(0) * b_val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    iobj_2->W[i] = b_val[i];
  }
  b_tmp_data.set(&tmp_data[0], 0);
  coder::internal::validator_check_size(b_tmp_data, c_val);
  iobj_2->Wf.set_size(c_val.size(0));
  loop_ub = c_val.size(0);
  for (int i{0}; i < loop_ub; i++) {
    iobj_2->Wf[i] = c_val[i];
  }
  iobj_2->thresh.init();
  // Set custom types for coder.
  d_val = iobj_0->init();
  iobj_2->stft = d_val;
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
  makepulsestruc(&r2.A, &r2.P, &r2.SNR, &r2.yw, &r2.t_0, &r2.t_f, r2.t_next,
                 &r2.fp, &r2.fstart, &r2.fend, r2.mode, &r2.det_dec,
                 &r2.con_dec);
  r3.size[0] = 1;
  r3.size[1] = 1;
  r3.data[0] = r2;
  r4.set(&r3.data[0], r3.size[0], r3.size[1]);
  coder::internal::validator_check_size(r4, _in);
  (&iobj_1[0])[0].pl.set_size(1, _in.size(1));
  loop_ub = _in.size(1);
  for (int i{0}; i < loop_ub; i++) {
    (&iobj_1[0])[0].pl[i] = _in[i];
  }
  makepulsestruc(&r2.A, &r2.P, &r2.SNR, &r2.yw, &r2.t_0, &r2.t_f, r2.t_next,
                 &r2.fp, &r2.fstart, &r2.fend, r2.mode, &r2.det_dec,
                 &r2.con_dec);
  r3.size[0] = 1;
  r3.size[1] = 1;
  r3.data[0] = r2;
  r5.set(&r3.data[0], r3.size[0], r3.size[1]);
  coder::internal::c_validator_check_size(r5, e_val);
  (&iobj_1[0])[0].clst.set_size(e_val.size(0), e_val.size(1));
  loop_ub = e_val.size(0) * e_val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    (&iobj_1[0])[0].clst[i] = e_val[i];
  }
  c_tmp_data.set(nullptr, 0, 0);
  coder::internal::d_validator_check_size(c_tmp_data, f_val);
  (&iobj_1[0])[0].cmsk.set_size(f_val.size(0), f_val.size(1));
  loop_ub = f_val.size(0) * f_val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    (&iobj_1[0])[0].cmsk[i] = f_val[i];
  }
  d_tmp_data.set(nullptr, 0, 0);
  coder::internal::c_validator_check_size(d_tmp_data, b__in);
  (&iobj_1[0])[0].cpki.set_size(b__in.size(0), b__in.size(1));
  loop_ub = b__in.size(0) * b__in.size(1);
  for (int i{0}; i < loop_ub; i++) {
    (&iobj_1[0])[0].cpki[i] = b__in[i];
  }
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
  makepulsestruc(&r2.A, &r2.P, &r2.SNR, &r2.yw, &r2.t_0, &r2.t_f, r2.t_next,
                 &r2.fp, &r2.fstart, &r2.fend, r2.mode, &r2.det_dec,
                 &r2.con_dec);
  r3.size[0] = 1;
  r3.size[1] = 1;
  r3.data[0] = r2;
  r6.set(&r3.data[0], r3.size[0], r3.size[1]);
  coder::internal::validator_check_size(r6, _in);
  (&iobj_1[0])[1].pl.set_size(1, _in.size(1));
  loop_ub = _in.size(1);
  for (int i{0}; i < loop_ub; i++) {
    (&iobj_1[0])[1].pl[i] = _in[i];
  }
  makepulsestruc(&r2.A, &r2.P, &r2.SNR, &r2.yw, &r2.t_0, &r2.t_f, r2.t_next,
                 &r2.fp, &r2.fstart, &r2.fend, r2.mode, &r2.det_dec,
                 &r2.con_dec);
  r3.size[0] = 1;
  r3.size[1] = 1;
  r3.data[0] = r2;
  r7.set(&r3.data[0], r3.size[0], r3.size[1]);
  coder::internal::c_validator_check_size(r7, e_val);
  (&iobj_1[0])[1].clst.set_size(e_val.size(0), e_val.size(1));
  loop_ub = e_val.size(0) * e_val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    (&iobj_1[0])[1].clst[i] = e_val[i];
  }
  e_tmp_data.set(nullptr, 0, 0);
  coder::internal::d_validator_check_size(e_tmp_data, f_val);
  (&iobj_1[0])[1].cmsk.set_size(f_val.size(0), f_val.size(1));
  loop_ub = f_val.size(0) * f_val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    (&iobj_1[0])[1].cmsk[i] = f_val[i];
  }
  f_tmp_data.set(nullptr, 0, 0);
  coder::internal::c_validator_check_size(f_tmp_data, b__in);
  (&iobj_1[0])[1].cpki.set_size(b__in.size(0), b__in.size(1));
  loop_ub = b__in.size(0) * b__in.size(1);
  for (int i{0}; i < loop_ub; i++) {
    (&iobj_1[0])[1].cpki[i] = b__in[i];
  }
  iobj_2->ps_pos = &(&iobj_1[0])[1];
  _in.set_size(1, wfmIn->ps_pre->pl.size(1));
  loop_ub = wfmIn->ps_pre->pl.size(0) * wfmIn->ps_pre->pl.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    _in[i] = wfmIn->ps_pre->pl[i];
  }
  e_val.set_size(wfmIn->ps_pre->clst.size(0), wfmIn->ps_pre->clst.size(1));
  loop_ub = wfmIn->ps_pre->clst.size(0) * wfmIn->ps_pre->clst.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    e_val[i] = wfmIn->ps_pre->clst[i];
  }
  f_val.set_size(wfmIn->ps_pre->cmsk.size(0), wfmIn->ps_pre->cmsk.size(1));
  loop_ub = wfmIn->ps_pre->cmsk.size(0) * wfmIn->ps_pre->cmsk.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    f_val[i] = wfmIn->ps_pre->cmsk[i];
  }
  b_wfmIn.set_size(wfmIn->ps_pre->cpki.size(0), wfmIn->ps_pre->cpki.size(1));
  loop_ub = wfmIn->ps_pre->cpki.size(0) * wfmIn->ps_pre->cpki.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    b_wfmIn[i] = wfmIn->ps_pre->cpki[i];
  }
  c_wfmIn[0] = wfmIn->ps_pre->tmplt[0];
  c_wfmIn[1] = wfmIn->ps_pre->tmplt[1];
  g_val = iobj_1[2].b_init(wfmIn->ps_pre->t_p, wfmIn->ps_pre->t_ip,
                           wfmIn->ps_pre->t_ipu, wfmIn->ps_pre->t_ipj,
                           wfmIn->ps_pre->fp, wfmIn->ps_pre->fstart,
                           wfmIn->ps_pre->fend, c_wfmIn, wfmIn->ps_pre->mode,
                           _in, e_val, f_val, b_wfmIn);
  iobj_2->ps_pre = g_val;
  _in.set_size(1, wfmIn->ps_pos->pl.size(1));
  loop_ub = wfmIn->ps_pos->pl.size(0) * wfmIn->ps_pos->pl.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    _in[i] = wfmIn->ps_pos->pl[i];
  }
  e_val.set_size(wfmIn->ps_pos->clst.size(0), wfmIn->ps_pos->clst.size(1));
  loop_ub = wfmIn->ps_pos->clst.size(0) * wfmIn->ps_pos->clst.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    e_val[i] = wfmIn->ps_pos->clst[i];
  }
  f_val.set_size(wfmIn->ps_pos->cmsk.size(0), wfmIn->ps_pos->cmsk.size(1));
  loop_ub = wfmIn->ps_pos->cmsk.size(0) * wfmIn->ps_pos->cmsk.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    f_val[i] = wfmIn->ps_pos->cmsk[i];
  }
  b_wfmIn.set_size(wfmIn->ps_pos->cpki.size(0), wfmIn->ps_pos->cpki.size(1));
  loop_ub = wfmIn->ps_pos->cpki.size(0) * wfmIn->ps_pos->cpki.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    b_wfmIn[i] = wfmIn->ps_pos->cpki[i];
  }
  threshold h_val;
  c_wfmIn[0] = wfmIn->ps_pos->tmplt[0];
  c_wfmIn[1] = wfmIn->ps_pos->tmplt[1];
  g_val = iobj_1[3].b_init(wfmIn->ps_pos->t_p, wfmIn->ps_pos->t_ip,
                           wfmIn->ps_pos->t_ipu, wfmIn->ps_pos->t_ipj,
                           wfmIn->ps_pos->fp, wfmIn->ps_pos->fstart,
                           wfmIn->ps_pos->fend, c_wfmIn, wfmIn->ps_pos->mode,
                           _in, e_val, f_val, b_wfmIn);
  iobj_2->ps_pos = g_val;
  h_val = wfmIn->thresh;
  iobj_2->thresh = h_val;
  d_val = iobj_2->stft;
  b_val.set_size(wfmIn->stft->S.size(0), wfmIn->stft->S.size(1));
  loop_ub = wfmIn->stft->S.size(0) * wfmIn->stft->S.size(1);
  for (int i{0}; i < loop_ub; i++) {
    b_val[i] = wfmIn->stft->S[i];
  }
  i_val.set_size(b_val.size(0), b_val.size(1));
  loop_ub = b_val.size(0) * b_val.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    i_val[i] = b_val[i];
  }
  coder::internal::validator_check_size(i_val, b_val);
  d_val->S.set_size(b_val.size(0), b_val.size(1));
  loop_ub = b_val.size(0) * b_val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    d_val->S[i] = b_val[i];
  }
  d_val = iobj_2->stft;
  c_val.set_size(wfmIn->stft->f.size(0));
  loop_ub = wfmIn->stft->f.size(0);
  for (int i{0}; i < loop_ub; i++) {
    c_val[i] = wfmIn->stft->f[i];
  }
  j_val.set_size(c_val.size(0));
  loop_ub = c_val.size(0) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    j_val[i] = c_val[i];
  }
  coder::internal::validator_check_size(j_val, c_val);
  d_val->f.set_size(c_val.size(0));
  loop_ub = c_val.size(0);
  for (int i{0}; i < loop_ub; i++) {
    d_val->f[i] = c_val[i];
  }
  d_val = iobj_2->stft;
  c_val.set_size(wfmIn->stft->t.size(0));
  loop_ub = wfmIn->stft->t.size(0);
  for (int i{0}; i < loop_ub; i++) {
    c_val[i] = wfmIn->stft->t[i];
  }
  j_val.set_size(c_val.size(0));
  loop_ub = c_val.size(0) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    j_val[i] = c_val[i];
  }
  coder::internal::validator_check_size(j_val, c_val);
  d_val->t.set_size(c_val.size(0));
  loop_ub = c_val.size(0);
  for (int i{0}; i < loop_ub; i++) {
    d_val->t[i] = c_val[i];
  }
  d_val = iobj_2->stft;
  c_val.set_size(wfmIn->stft->psd.size(0));
  loop_ub = wfmIn->stft->psd.size(0);
  for (int i{0}; i < loop_ub; i++) {
    c_val[i] = wfmIn->stft->psd[i];
  }
  j_val.set_size(c_val.size(0));
  loop_ub = c_val.size(0) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    j_val[i] = c_val[i];
  }
  coder::internal::validator_check_size(j_val, c_val);
  d_val->psd.set_size(c_val.size(0));
  loop_ub = c_val.size(0);
  for (int i{0}; i < loop_ub; i++) {
    d_val->psd[i] = c_val[i];
  }
  d_val = iobj_2->stft;
  k_val = wfmIn->stft->dt;
  d_val->dt = k_val;
  d_val = iobj_2->stft;
  k_val = wfmIn->stft->T;
  d_val->T = k_val;
  d_val = iobj_2->stft;
  c_val.set_size(wfmIn->stft->wind.size(0));
  loop_ub = wfmIn->stft->wind.size(0);
  for (int i{0}; i < loop_ub; i++) {
    c_val[i] = wfmIn->stft->wind[i];
  }
  j_val.set_size(c_val.size(0));
  loop_ub = c_val.size(0) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    j_val[i] = c_val[i];
  }
  coder::internal::validator_check_size(j_val, c_val);
  d_val->wind.set_size(c_val.size(0));
  loop_ub = c_val.size(0);
  for (int i{0}; i < loop_ub; i++) {
    d_val->wind[i] = c_val[i];
  }
  k_val = wfmIn->K;
  iobj_2->K = k_val;
  val.set_size(1, wfmIn->x.size(1));
  loop_ub = wfmIn->x.size(1);
  for (int i{0}; i < loop_ub; i++) {
    val[i] = wfmIn->x[i];
  }
  l_val.set_size(1, val.size(1));
  loop_ub = val.size(0) * val.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    l_val[i] = val[i];
  }
  coder::internal::validator_check_size(l_val, val);
  iobj_2->x.set_size(1, val.size(1));
  loop_ub = val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    iobj_2->x[i] = val[i];
  }
  double val_idx_1;
  k_val = wfmIn->Fs;
  iobj_2->Fs = k_val;
  k_val = wfmIn->l;
  iobj_2->l = k_val;
  k_val = wfmIn->t_0;
  iobj_2->t_0 = k_val;
  k_val = wfmIn->t_f;
  iobj_2->t_0 = k_val;
  k_val = wfmIn->t_nextsegstart[0];
  val_idx_1 = wfmIn->t_nextsegstart[1];
  iobj_2->t_nextsegstart[0] = k_val;
  iobj_2->t_nextsegstart[1] = val_idx_1;
  k_val = wfmIn->OLF;
  iobj_2->OLF = k_val;
  b_val.set_size(wfmIn->W.size(0), wfmIn->W.size(1));
  loop_ub = wfmIn->W.size(0) * wfmIn->W.size(1);
  for (int i{0}; i < loop_ub; i++) {
    b_val[i] = wfmIn->W[i];
  }
  i_val.set_size(b_val.size(0), b_val.size(1));
  loop_ub = b_val.size(0) * b_val.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    i_val[i] = b_val[i];
  }
  coder::internal::validator_check_size(i_val, b_val);
  iobj_2->W.set_size(b_val.size(0), b_val.size(1));
  loop_ub = b_val.size(0) * b_val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    iobj_2->W[i] = b_val[i];
  }
  c_val.set_size(wfmIn->Wf.size(0));
  loop_ub = wfmIn->Wf.size(0);
  for (int i{0}; i < loop_ub; i++) {
    c_val[i] = wfmIn->Wf[i];
  }
  j_val.set_size(c_val.size(0));
  loop_ub = c_val.size(0) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    j_val[i] = c_val[i];
  }
  coder::internal::validator_check_size(j_val, c_val);
  iobj_2->Wf.set_size(c_val.size(0));
  loop_ub = c_val.size(0);
  for (int i{0}; i < loop_ub; i++) {
    iobj_2->Wf[i] = c_val[i];
  }
  k_val = wfmIn->n_p;
  iobj_2->n_p = k_val;
  k_val = wfmIn->n_w;
  iobj_2->n_w = k_val;
  k_val = wfmIn->n_ol;
  iobj_2->n_ol = k_val;
  k_val = wfmIn->n_ws;
  iobj_2->n_ws = k_val;
  k_val = wfmIn->t_ws;
  iobj_2->t_ws = k_val;
  k_val = wfmIn->n_ip;
  iobj_2->n_ip = k_val;
  k_val = wfmIn->N;
  iobj_2->N = k_val;
  k_val = wfmIn->M;
  iobj_2->M = k_val;
  k_val = wfmIn->J;
  iobj_2->J = k_val;
  return wfmOut;
}

//
// File trailer for waveformcopy.cpp
//
// [EOF]
//
