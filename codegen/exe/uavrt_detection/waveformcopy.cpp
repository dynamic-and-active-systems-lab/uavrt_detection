//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: waveformcopy.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 14:31:55
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
  pulsestats *c_val;
  waveform *wfmOut;
  wfmstft *b_val;
  coder::array<c_struct_T, 2U> _in;
  coder::array<c_struct_T, 2U> b__in;
  coder::array<c_struct_T, 2U> r4;
  coder::array<c_struct_T, 2U> r5;
  coder::array<c_struct_T, 2U> r6;
  coder::array<c_struct_T, 2U> r7;
  coder::array<creal_T, 2U> b_val_data;
  coder::array<creal_T, 2U> e_val;
  coder::array<creal_T, 2U> f_val;
  coder::array<creal_T, 2U> r;
  coder::array<creal_T, 2U> r1;
  coder::array<creal_T, 2U> val_data;
  coder::array<double, 2U> b_wfmIn;
  coder::array<double, 2U> d__in;
  coder::array<double, 2U> f_tmp_data;
  coder::array<double, 2U> h_tmp_data;
  coder::array<double, 1U> b_tmp_data;
  coder::array<double, 1U> g_val;
  coder::array<double, 1U> val;
  coder::array<boolean_T, 2U> c__in;
  coder::array<boolean_T, 2U> d_tmp_data;
  coder::array<boolean_T, 2U> g_tmp_data;
  c_struct_T r2;
  emxArray_struct_T_1x1 r3;
  double tmp_data[400];
  double c_wfmIn[2];
  double e_tmp_data;
  double h_val;
  int loop_ub;
  int val_size_idx_1;
  boolean_T c_tmp_data;
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
  r.set(nullptr, 0, 0);
  coder::internal::validator_check_size(r, r1);
  iobj_2->W.set_size(0, 0);
  b_tmp_data.set(&tmp_data[0], 0);
  coder::internal::validator_check_size(b_tmp_data, val);
  iobj_2->Wf.set_size(val.size(0));
  loop_ub = val.size(0);
  for (val_size_idx_1 = 0; val_size_idx_1 < loop_ub; val_size_idx_1++) {
    iobj_2->Wf[val_size_idx_1] = val[val_size_idx_1];
  }
  iobj_2->thresh.init();
  // Set custom types for coder.
  b_val = iobj_0->init();
  iobj_2->stft = b_val;
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
  for (val_size_idx_1 = 0; val_size_idx_1 < loop_ub; val_size_idx_1++) {
    (&iobj_1[0])[0].pl[val_size_idx_1] = _in[val_size_idx_1];
  }
  makepulsestruc(&r2.A, &r2.P, &r2.SNR, &r2.yw, &r2.t_0, &r2.t_f, r2.t_next,
                 &r2.fp, &r2.fstart, &r2.fend, r2.mode, &r2.det_dec,
                 &r2.con_dec);
  r3.size[0] = 1;
  r3.size[1] = 1;
  r3.data[0] = r2;
  r5.set(&r3.data[0], r3.size[0], r3.size[1]);
  coder::internal::b_validator_check_size(r5, b__in);
  (&iobj_1[0])[0].clst.set_size(b__in.size(0), b__in.size(1));
  loop_ub = b__in.size(0) * b__in.size(1);
  for (val_size_idx_1 = 0; val_size_idx_1 < loop_ub; val_size_idx_1++) {
    (&iobj_1[0])[0].clst[val_size_idx_1] = b__in[val_size_idx_1];
  }
  d_tmp_data.set(&c_tmp_data, 0, 0);
  coder::internal::c_validator_check_size(d_tmp_data, c__in);
  (&iobj_1[0])[0].cmsk.set_size(c__in.size(0), c__in.size(1));
  loop_ub = c__in.size(0) * c__in.size(1);
  for (val_size_idx_1 = 0; val_size_idx_1 < loop_ub; val_size_idx_1++) {
    (&iobj_1[0])[0].cmsk[val_size_idx_1] = c__in[val_size_idx_1];
  }
  f_tmp_data.set(&e_tmp_data, 0, 0);
  coder::internal::b_validator_check_size(f_tmp_data, d__in);
  (&iobj_1[0])[0].cpki.set_size(d__in.size(0), d__in.size(1));
  loop_ub = d__in.size(0) * d__in.size(1);
  for (val_size_idx_1 = 0; val_size_idx_1 < loop_ub; val_size_idx_1++) {
    (&iobj_1[0])[0].cpki[val_size_idx_1] = d__in[val_size_idx_1];
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
  for (val_size_idx_1 = 0; val_size_idx_1 < loop_ub; val_size_idx_1++) {
    (&iobj_1[0])[1].pl[val_size_idx_1] = _in[val_size_idx_1];
  }
  makepulsestruc(&r2.A, &r2.P, &r2.SNR, &r2.yw, &r2.t_0, &r2.t_f, r2.t_next,
                 &r2.fp, &r2.fstart, &r2.fend, r2.mode, &r2.det_dec,
                 &r2.con_dec);
  r3.size[0] = 1;
  r3.size[1] = 1;
  r3.data[0] = r2;
  r7.set(&r3.data[0], r3.size[0], r3.size[1]);
  coder::internal::b_validator_check_size(r7, b__in);
  (&iobj_1[0])[1].clst.set_size(b__in.size(0), b__in.size(1));
  loop_ub = b__in.size(0) * b__in.size(1);
  for (val_size_idx_1 = 0; val_size_idx_1 < loop_ub; val_size_idx_1++) {
    (&iobj_1[0])[1].clst[val_size_idx_1] = b__in[val_size_idx_1];
  }
  g_tmp_data.set(&c_tmp_data, 0, 0);
  coder::internal::c_validator_check_size(g_tmp_data, c__in);
  (&iobj_1[0])[1].cmsk.set_size(c__in.size(0), c__in.size(1));
  loop_ub = c__in.size(0) * c__in.size(1);
  for (val_size_idx_1 = 0; val_size_idx_1 < loop_ub; val_size_idx_1++) {
    (&iobj_1[0])[1].cmsk[val_size_idx_1] = c__in[val_size_idx_1];
  }
  h_tmp_data.set(&e_tmp_data, 0, 0);
  coder::internal::b_validator_check_size(h_tmp_data, d__in);
  (&iobj_1[0])[1].cpki.set_size(d__in.size(0), d__in.size(1));
  loop_ub = d__in.size(0) * d__in.size(1);
  for (val_size_idx_1 = 0; val_size_idx_1 < loop_ub; val_size_idx_1++) {
    (&iobj_1[0])[1].cpki[val_size_idx_1] = d__in[val_size_idx_1];
  }
  iobj_2->ps_pos = &(&iobj_1[0])[1];
  _in.set_size(1, wfmIn->ps_pre->pl.size(1));
  loop_ub = wfmIn->ps_pre->pl.size(0) * wfmIn->ps_pre->pl.size(1) - 1;
  for (val_size_idx_1 = 0; val_size_idx_1 <= loop_ub; val_size_idx_1++) {
    _in[val_size_idx_1] = wfmIn->ps_pre->pl[val_size_idx_1];
  }
  b__in.set_size(wfmIn->ps_pre->clst.size(0), wfmIn->ps_pre->clst.size(1));
  loop_ub = wfmIn->ps_pre->clst.size(0) * wfmIn->ps_pre->clst.size(1) - 1;
  for (val_size_idx_1 = 0; val_size_idx_1 <= loop_ub; val_size_idx_1++) {
    b__in[val_size_idx_1] = wfmIn->ps_pre->clst[val_size_idx_1];
  }
  c__in.set_size(wfmIn->ps_pre->cmsk.size(0), wfmIn->ps_pre->cmsk.size(1));
  loop_ub = wfmIn->ps_pre->cmsk.size(0) * wfmIn->ps_pre->cmsk.size(1) - 1;
  for (val_size_idx_1 = 0; val_size_idx_1 <= loop_ub; val_size_idx_1++) {
    c__in[val_size_idx_1] = wfmIn->ps_pre->cmsk[val_size_idx_1];
  }
  b_wfmIn.set_size(wfmIn->ps_pre->cpki.size(0), wfmIn->ps_pre->cpki.size(1));
  loop_ub = wfmIn->ps_pre->cpki.size(0) * wfmIn->ps_pre->cpki.size(1) - 1;
  for (val_size_idx_1 = 0; val_size_idx_1 <= loop_ub; val_size_idx_1++) {
    b_wfmIn[val_size_idx_1] = wfmIn->ps_pre->cpki[val_size_idx_1];
  }
  c_wfmIn[0] = wfmIn->ps_pre->tmplt[0];
  c_wfmIn[1] = wfmIn->ps_pre->tmplt[1];
  c_val = iobj_1[2].b_init(wfmIn->ps_pre->t_p, wfmIn->ps_pre->t_ip,
                           wfmIn->ps_pre->t_ipu, wfmIn->ps_pre->t_ipj,
                           wfmIn->ps_pre->fp, wfmIn->ps_pre->fstart,
                           wfmIn->ps_pre->fend, c_wfmIn, wfmIn->ps_pre->mode,
                           _in, b__in, c__in, b_wfmIn);
  iobj_2->ps_pre = c_val;
  _in.set_size(1, wfmIn->ps_pos->pl.size(1));
  loop_ub = wfmIn->ps_pos->pl.size(0) * wfmIn->ps_pos->pl.size(1) - 1;
  for (val_size_idx_1 = 0; val_size_idx_1 <= loop_ub; val_size_idx_1++) {
    _in[val_size_idx_1] = wfmIn->ps_pos->pl[val_size_idx_1];
  }
  b__in.set_size(wfmIn->ps_pos->clst.size(0), wfmIn->ps_pos->clst.size(1));
  loop_ub = wfmIn->ps_pos->clst.size(0) * wfmIn->ps_pos->clst.size(1) - 1;
  for (val_size_idx_1 = 0; val_size_idx_1 <= loop_ub; val_size_idx_1++) {
    b__in[val_size_idx_1] = wfmIn->ps_pos->clst[val_size_idx_1];
  }
  c__in.set_size(wfmIn->ps_pos->cmsk.size(0), wfmIn->ps_pos->cmsk.size(1));
  loop_ub = wfmIn->ps_pos->cmsk.size(0) * wfmIn->ps_pos->cmsk.size(1) - 1;
  for (val_size_idx_1 = 0; val_size_idx_1 <= loop_ub; val_size_idx_1++) {
    c__in[val_size_idx_1] = wfmIn->ps_pos->cmsk[val_size_idx_1];
  }
  b_wfmIn.set_size(wfmIn->ps_pos->cpki.size(0), wfmIn->ps_pos->cpki.size(1));
  loop_ub = wfmIn->ps_pos->cpki.size(0) * wfmIn->ps_pos->cpki.size(1) - 1;
  for (val_size_idx_1 = 0; val_size_idx_1 <= loop_ub; val_size_idx_1++) {
    b_wfmIn[val_size_idx_1] = wfmIn->ps_pos->cpki[val_size_idx_1];
  }
  threshold d_val;
  c_wfmIn[0] = wfmIn->ps_pos->tmplt[0];
  c_wfmIn[1] = wfmIn->ps_pos->tmplt[1];
  c_val = iobj_1[3].b_init(wfmIn->ps_pos->t_p, wfmIn->ps_pos->t_ip,
                           wfmIn->ps_pos->t_ipu, wfmIn->ps_pos->t_ipj,
                           wfmIn->ps_pos->fp, wfmIn->ps_pos->fstart,
                           wfmIn->ps_pos->fend, c_wfmIn, wfmIn->ps_pos->mode,
                           _in, b__in, c__in, b_wfmIn);
  iobj_2->ps_pos = c_val;
  d_val = wfmIn->thresh;
  iobj_2->thresh = d_val;
  b_val = iobj_2->stft;
  e_val.set_size(wfmIn->stft->S.size(0), wfmIn->stft->S.size(1));
  loop_ub = wfmIn->stft->S.size(0) * wfmIn->stft->S.size(1);
  for (val_size_idx_1 = 0; val_size_idx_1 < loop_ub; val_size_idx_1++) {
    e_val[val_size_idx_1] = wfmIn->stft->S[val_size_idx_1];
  }
  f_val.set_size(e_val.size(0), e_val.size(1));
  loop_ub = e_val.size(0) * e_val.size(1) - 1;
  for (val_size_idx_1 = 0; val_size_idx_1 <= loop_ub; val_size_idx_1++) {
    f_val[val_size_idx_1] = e_val[val_size_idx_1];
  }
  coder::internal::validator_check_size(f_val, e_val);
  b_val->S.set_size(e_val.size(0), e_val.size(1));
  loop_ub = e_val.size(0) * e_val.size(1);
  for (val_size_idx_1 = 0; val_size_idx_1 < loop_ub; val_size_idx_1++) {
    b_val->S[val_size_idx_1] = e_val[val_size_idx_1];
  }
  b_val = iobj_2->stft;
  val.set_size(wfmIn->stft->f.size(0));
  loop_ub = wfmIn->stft->f.size(0);
  for (val_size_idx_1 = 0; val_size_idx_1 < loop_ub; val_size_idx_1++) {
    val[val_size_idx_1] = wfmIn->stft->f[val_size_idx_1];
  }
  g_val.set_size(val.size(0));
  loop_ub = val.size(0) - 1;
  for (val_size_idx_1 = 0; val_size_idx_1 <= loop_ub; val_size_idx_1++) {
    g_val[val_size_idx_1] = val[val_size_idx_1];
  }
  coder::internal::validator_check_size(g_val, val);
  b_val->f.set_size(val.size(0));
  loop_ub = val.size(0);
  for (val_size_idx_1 = 0; val_size_idx_1 < loop_ub; val_size_idx_1++) {
    b_val->f[val_size_idx_1] = val[val_size_idx_1];
  }
  b_val = iobj_2->stft;
  val.set_size(wfmIn->stft->t.size(0));
  loop_ub = wfmIn->stft->t.size(0);
  for (val_size_idx_1 = 0; val_size_idx_1 < loop_ub; val_size_idx_1++) {
    val[val_size_idx_1] = wfmIn->stft->t[val_size_idx_1];
  }
  g_val.set_size(val.size(0));
  loop_ub = val.size(0) - 1;
  for (val_size_idx_1 = 0; val_size_idx_1 <= loop_ub; val_size_idx_1++) {
    g_val[val_size_idx_1] = val[val_size_idx_1];
  }
  coder::internal::validator_check_size(g_val, val);
  b_val->t.set_size(val.size(0));
  loop_ub = val.size(0);
  for (val_size_idx_1 = 0; val_size_idx_1 < loop_ub; val_size_idx_1++) {
    b_val->t[val_size_idx_1] = val[val_size_idx_1];
  }
  b_val = iobj_2->stft;
  val.set_size(wfmIn->stft->psd.size(0));
  loop_ub = wfmIn->stft->psd.size(0);
  for (val_size_idx_1 = 0; val_size_idx_1 < loop_ub; val_size_idx_1++) {
    val[val_size_idx_1] = wfmIn->stft->psd[val_size_idx_1];
  }
  g_val.set_size(val.size(0));
  loop_ub = val.size(0) - 1;
  for (val_size_idx_1 = 0; val_size_idx_1 <= loop_ub; val_size_idx_1++) {
    g_val[val_size_idx_1] = val[val_size_idx_1];
  }
  coder::internal::validator_check_size(g_val, val);
  b_val->psd.set_size(val.size(0));
  loop_ub = val.size(0);
  for (val_size_idx_1 = 0; val_size_idx_1 < loop_ub; val_size_idx_1++) {
    b_val->psd[val_size_idx_1] = val[val_size_idx_1];
  }
  b_val = iobj_2->stft;
  h_val = wfmIn->stft->dt;
  b_val->dt = h_val;
  b_val = iobj_2->stft;
  h_val = wfmIn->stft->T;
  b_val->T = h_val;
  b_val = iobj_2->stft;
  val.set_size(wfmIn->stft->wind.size(0));
  loop_ub = wfmIn->stft->wind.size(0);
  for (val_size_idx_1 = 0; val_size_idx_1 < loop_ub; val_size_idx_1++) {
    val[val_size_idx_1] = wfmIn->stft->wind[val_size_idx_1];
  }
  g_val.set_size(val.size(0));
  loop_ub = val.size(0) - 1;
  for (val_size_idx_1 = 0; val_size_idx_1 <= loop_ub; val_size_idx_1++) {
    g_val[val_size_idx_1] = val[val_size_idx_1];
  }
  coder::internal::validator_check_size(g_val, val);
  b_val->wind.set_size(val.size(0));
  loop_ub = val.size(0);
  for (val_size_idx_1 = 0; val_size_idx_1 < loop_ub; val_size_idx_1++) {
    b_val->wind[val_size_idx_1] = val[val_size_idx_1];
  }
  double val_idx_1;
  iobj_2->K = rtNaN;
  iobj_2->x.set_size(1, 0);
  h_val = wfmIn->Fs;
  iobj_2->Fs = h_val;
  iobj_2->l = 1000.0;
  iobj_2->t_0 = 0.0;
  iobj_2->t_0 = 0.0;
  h_val = wfmIn->t_nextsegstart[0];
  val_idx_1 = wfmIn->t_nextsegstart[1];
  iobj_2->t_nextsegstart[0] = h_val;
  iobj_2->t_nextsegstart[1] = val_idx_1;
  h_val = wfmIn->OLF;
  iobj_2->OLF = h_val;
  loop_ub = wfmIn->W.size(0);
  val_size_idx_1 = wfmIn->W.size(1);
  val_data.set(nullptr, loop_ub, val_size_idx_1);
  coder::internal::validator_check_size(val_data, b_val_data);
  iobj_2->W.set_size(0, 0);
  val.set_size(wfmIn->Wf.size(0));
  loop_ub = wfmIn->Wf.size(0);
  for (val_size_idx_1 = 0; val_size_idx_1 < loop_ub; val_size_idx_1++) {
    val[val_size_idx_1] = wfmIn->Wf[val_size_idx_1];
  }
  g_val.set_size(val.size(0));
  loop_ub = val.size(0) - 1;
  for (val_size_idx_1 = 0; val_size_idx_1 <= loop_ub; val_size_idx_1++) {
    g_val[val_size_idx_1] = val[val_size_idx_1];
  }
  coder::internal::validator_check_size(g_val, val);
  iobj_2->Wf.set_size(val.size(0));
  loop_ub = val.size(0);
  for (val_size_idx_1 = 0; val_size_idx_1 < loop_ub; val_size_idx_1++) {
    iobj_2->Wf[val_size_idx_1] = val[val_size_idx_1];
  }
  h_val = wfmIn->n_p;
  iobj_2->n_p = h_val;
  h_val = wfmIn->n_w;
  iobj_2->n_w = h_val;
  h_val = wfmIn->n_ol;
  iobj_2->n_ol = h_val;
  h_val = wfmIn->n_ws;
  iobj_2->n_ws = h_val;
  h_val = wfmIn->t_ws;
  iobj_2->t_ws = h_val;
  h_val = wfmIn->n_ip;
  iobj_2->n_ip = h_val;
  h_val = wfmIn->N;
  iobj_2->N = h_val;
  h_val = wfmIn->M;
  iobj_2->M = h_val;
  h_val = wfmIn->J;
  iobj_2->J = h_val;
  return wfmOut;
}

//
// File trailer for waveformcopy.cpp
//
// [EOF]
//
