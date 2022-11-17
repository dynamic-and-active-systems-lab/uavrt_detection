//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// pulsestats.cpp
//
// Code generation for function 'pulsestats'
//

// Include files
#include "pulsestats.h"
#include "blockedSummation.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_internal_types.h"
#include "validator_check_size.h"
#include "coder_array.h"
#include <cmath>
#include <string.h>

// Function Definitions
pulsestats *pulsestats::b_init(double tp, double tip, double tipu, double tipj,
                               double b_fp, double b_fstart, double b_fend,
                               const double b_tmplt[2], char b_mode,
                               const coder::array<c_struct_T, 2U> &b_pl,
                               const coder::array<c_struct_T, 2U> &b_clst,
                               const coder::array<boolean_T, 2U> &b_cmsk,
                               const coder::array<double, 2U> &b_cpki)
{
  pulsestats *obj;
  coder::array<c_struct_T, 2U> _in;
  coder::array<c_struct_T, 2U> val;
  coder::array<double, 2U> localCpki;
  coder::array<boolean_T, 2U> b_val;
  int loop_ub;
  obj = this;
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
  obj->t_p = tp;
  obj->t_ip = tip;
  obj->t_ipu = tipu;
  obj->t_ipj = tipj;
  obj->fp = b_fp;
  obj->fstart = b_fstart;
  obj->fend = b_fend;
  obj->tmplt[0] = b_tmplt[0];
  obj->tmplt[1] = b_tmplt[1];
  obj->mode = b_mode;
  // The following are variable sized properties. To tell coder
  // that they may vary setup as a local variable size variable
  // first, then set.
  // Instructions on
  // https://www.mathworks.com/help/simulink/ug/how-working-with-matlab-classes-is-different-for-code-generation.html
  // localMode = mode;
  // coder.varsize('localMode',[1 inf],[0 1]); %dims 0 if fixed, 1 if variable
  // Tell coder these are variable size.
  // Now actually assign them
  coder::internal::validator_check_size(b_pl, _in);
  obj->pl.set_size(1, _in.size(1));
  loop_ub = _in.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->pl[i] = _in[i];
  }
  coder::internal::c_validator_check_size(b_clst, val);
  obj->clst.set_size(val.size(0), val.size(1));
  loop_ub = val.size(0) * val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->clst[i] = val[i];
  }
  coder::internal::d_validator_check_size(b_cmsk, b_val);
  obj->cmsk.set_size(b_val.size(0), b_val.size(1));
  loop_ub = b_val.size(0) * b_val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->cmsk[i] = b_val[i];
  }
  coder::internal::c_validator_check_size(b_cpki, localCpki);
  obj->cpki.set_size(localCpki.size(0), localCpki.size(1));
  loop_ub = localCpki.size(0) * localCpki.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->cpki[i] = localCpki[i];
  }
  return obj;
}

pulsestats *pulsestats::c_init(double tp, double tip, double tipu, double tipj,
                               double b_fp, double b_fstart, double b_fend,
                               const double b_tmplt[2], const char mode_data[],
                               const coder::array<c_struct_T, 2U> &b_pl,
                               const coder::array<c_struct_T, 2U> &b_clst,
                               const coder::array<boolean_T, 2U> &b_cmsk,
                               const coder::array<double, 2U> &b_cpki)
{
  pulsestats *obj;
  coder::array<c_struct_T, 2U> _in;
  coder::array<c_struct_T, 2U> val;
  coder::array<double, 2U> localCpki;
  coder::array<boolean_T, 2U> b_val;
  int loop_ub;
  obj = this;
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
  obj->t_p = tp;
  obj->t_ip = tip;
  obj->t_ipu = tipu;
  obj->t_ipj = tipj;
  obj->fp = b_fp;
  obj->fstart = b_fstart;
  obj->fend = b_fend;
  obj->tmplt[0] = b_tmplt[0];
  obj->tmplt[1] = b_tmplt[1];
  obj->mode = mode_data[0];
  // The following are variable sized properties. To tell coder
  // that they may vary setup as a local variable size variable
  // first, then set.
  // Instructions on
  // https://www.mathworks.com/help/simulink/ug/how-working-with-matlab-classes-is-different-for-code-generation.html
  // localMode = mode;
  // coder.varsize('localMode',[1 inf],[0 1]); %dims 0 if fixed, 1 if variable
  // Tell coder these are variable size.
  // Now actually assign them
  coder::internal::validator_check_size(b_pl, _in);
  obj->pl.set_size(1, _in.size(1));
  loop_ub = _in.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->pl[i] = _in[i];
  }
  coder::internal::c_validator_check_size(b_clst, val);
  obj->clst.set_size(val.size(0), val.size(1));
  loop_ub = val.size(0) * val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->clst[i] = val[i];
  }
  coder::internal::d_validator_check_size(b_cmsk, b_val);
  obj->cmsk.set_size(b_val.size(0), b_val.size(1));
  loop_ub = b_val.size(0) * b_val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->cmsk[i] = b_val[i];
  }
  coder::internal::c_validator_check_size(b_cpki, localCpki);
  obj->cpki.set_size(localCpki.size(0), localCpki.size(1));
  loop_ub = localCpki.size(0) * localCpki.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->cpki[i] = localCpki[i];
  }
  return obj;
}

pulsestats *pulsestats::init(double tp, double tip, double tipu, double tipj,
                             const c_struct_T *b_pl, const c_struct_T *b_clst)
{
  pulsestats *obj;
  coder::array<c_struct_T, 2U> _in;
  coder::array<c_struct_T, 2U> d_pl;
  coder::array<c_struct_T, 2U> e_pl;
  coder::array<c_struct_T, 2U> val;
  coder::array<double, 2U> b_cmsk;
  coder::array<double, 2U> b_val;
  coder::array<boolean_T, 2U> b__in;
  coder::array<boolean_T, 2U> cmsk_data;
  emxArray_struct_T_1x1 c_pl;
  int loop_ub;
  obj = this;
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
  obj->t_p = tp;
  obj->t_ip = tip;
  obj->t_ipu = tipu;
  obj->t_ipj = tipj;
  obj->fp = 0.0;
  obj->fstart = 0.0;
  obj->fend = 0.0;
  obj->tmplt[0] = 1.0;
  obj->tmplt[1] = 1.0;
  obj->mode = 'D';
  // The following are variable sized properties. To tell coder
  // that they may vary setup as a local variable size variable
  // first, then set.
  // Instructions on
  // https://www.mathworks.com/help/simulink/ug/how-working-with-matlab-classes-is-different-for-code-generation.html
  // localMode = mode;
  // coder.varsize('localMode',[1 inf],[0 1]); %dims 0 if fixed, 1 if variable
  // Tell coder these are variable size.
  // Now actually assign them
  c_pl.size[0] = 1;
  c_pl.size[1] = 1;
  c_pl.data[0] = *b_pl;
  d_pl.set(&c_pl.data[0], c_pl.size[0], c_pl.size[1]);
  coder::internal::validator_check_size(d_pl, _in);
  obj->pl.set_size(1, _in.size(1));
  loop_ub = _in.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->pl[i] = _in[i];
  }
  c_pl.size[0] = 1;
  c_pl.size[1] = 1;
  c_pl.data[0] = *b_clst;
  e_pl.set(&c_pl.data[0], c_pl.size[0], c_pl.size[1]);
  coder::internal::c_validator_check_size(e_pl, val);
  obj->clst.set_size(val.size(0), val.size(1));
  loop_ub = val.size(0) * val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->clst[i] = val[i];
  }
  cmsk_data.set(nullptr, 0, 0);
  coder::internal::d_validator_check_size(cmsk_data, b__in);
  obj->cmsk.set_size(b__in.size(0), b__in.size(1));
  loop_ub = b__in.size(0) * b__in.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->cmsk[i] = b__in[i];
  }
  b_cmsk.set(nullptr, 0, 0);
  coder::internal::c_validator_check_size(b_cmsk, b_val);
  obj->cpki.set_size(b_val.size(0), b_val.size(1));
  loop_ub = b_val.size(0) * b_val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->cpki[i] = b_val[i];
  }
  return obj;
}

pulsestats *pulsestats::init(double tp, double tip, double tipu, double tipj,
                             double b_fp, const c_struct_T *b_pl,
                             const c_struct_T *b_clst)
{
  pulsestats *obj;
  coder::array<c_struct_T, 2U> _in;
  coder::array<c_struct_T, 2U> d_pl;
  coder::array<c_struct_T, 2U> e_pl;
  coder::array<c_struct_T, 2U> val;
  coder::array<double, 2U> c_val;
  coder::array<double, 2U> d_tmp_data;
  coder::array<boolean_T, 2U> b_tmp_data;
  coder::array<boolean_T, 2U> b_val;
  emxArray_struct_T_1x1 c_pl;
  double c_tmp_data;
  int loop_ub;
  boolean_T tmp_data;
  obj = this;
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
  obj->t_p = tp;
  obj->t_ip = tip;
  obj->t_ipu = tipu;
  obj->t_ipj = tipj;
  obj->fp = b_fp;
  obj->fstart = 0.0;
  obj->fend = 0.0;
  obj->tmplt[0] = 1.0;
  obj->tmplt[1] = 1.0;
  obj->mode = 'D';
  // The following are variable sized properties. To tell coder
  // that they may vary setup as a local variable size variable
  // first, then set.
  // Instructions on
  // https://www.mathworks.com/help/simulink/ug/how-working-with-matlab-classes-is-different-for-code-generation.html
  // localMode = mode;
  // coder.varsize('localMode',[1 inf],[0 1]); %dims 0 if fixed, 1 if variable
  // Tell coder these are variable size.
  // Now actually assign them
  c_pl.size[0] = 1;
  c_pl.size[1] = 1;
  c_pl.data[0] = *b_pl;
  d_pl.set(&c_pl.data[0], c_pl.size[0], c_pl.size[1]);
  coder::internal::validator_check_size(d_pl, _in);
  obj->pl.set_size(1, _in.size(1));
  loop_ub = _in.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->pl[i] = _in[i];
  }
  c_pl.size[0] = 1;
  c_pl.size[1] = 1;
  c_pl.data[0] = *b_clst;
  e_pl.set(&c_pl.data[0], c_pl.size[0], c_pl.size[1]);
  coder::internal::c_validator_check_size(e_pl, val);
  obj->clst.set_size(val.size(0), val.size(1));
  loop_ub = val.size(0) * val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->clst[i] = val[i];
  }
  tmp_data = false;
  b_tmp_data.set(&tmp_data, 1, 1);
  coder::internal::d_validator_check_size(b_tmp_data, b_val);
  obj->cmsk.set_size(b_val.size(0), b_val.size(1));
  loop_ub = b_val.size(0) * b_val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->cmsk[i] = b_val[i];
  }
  c_tmp_data = rtNaN;
  d_tmp_data.set(&c_tmp_data, 1, 1);
  coder::internal::c_validator_check_size(d_tmp_data, c_val);
  obj->cpki.set_size(c_val.size(0), c_val.size(1));
  loop_ub = c_val.size(0) * c_val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->cpki[i] = c_val[i];
  }
  return obj;
}

void pulsestats::updateposteriori(const coder::array<c_struct_T, 2U> &pulselist)
{
  coder::array<double, 2U> varargin_1;
  double freq_found;
  int n;
  //              %UPDATEPOSTERIORI updates the posteriori pulse statistics
  //              object using the new pulse list (input), prior pulse stats
  //              and the waveforms power spectral density vector. This
  //              methods is typically going to be called on a posteriori pulse
  //              stats object after a waveform has been processed and a set
  //              of candidate pulses found. This method uses those pulses and
  //              the prior information about the pulses to update the
  //              posteriori pulse stats.
  //
  //              The pulse contained in the waveform's ps_pos
  //              property is not used directly so that the caller can decide
  //              which pulses on which to focus the posteriori updates
  //
  //  updateType    What parts of the pulsestats to update. Valid
  //                options are 'time', 'freq', 'timeandfreq'. The
  //                'time' option will only update the interpulse
  //                time statistics. The 'freq' option will only
  //                update the frequency stats. The 'timeandfreq'
  //                option will update both.
  //
  if (pulselist.size(1) != 0) {
    //  pulselist(:).t_0]'
    n = pulselist.size(1);
    varargin_1.set_size(1, pulselist.size(1));
    for (int i{0}; i < n; i++) {
      varargin_1[i] = pulselist[i].fp;
    }
    coder::array<double, 1U> b_varargin_1;
    n = varargin_1.size(1);
    b_varargin_1 = varargin_1.reshape(n);
    coder::colMajorFlatIter(b_varargin_1, varargin_1.size(1), &freq_found, &n);
    freq_found /= static_cast<double>(n);
    // pulselist(:).fp
    // Create a vector of bandwidths from the pulselist
    // fEnds   = [pulselist.fend];
    // fStarts = [pulselist.fstart];
    // bw_found = 2*(mean(fEnds,'all','omitnan')-mean(fStarts,'all','omitnan'));
    // if isempty(bw_found)
    //     bw_found = 100;
    //     if coder.target('MATLAB')
    //        warning(['UAV-R: No bandwidth could be calculated ',...
    //             'from the start and stop frequencies of the ',...
    //             'identified pulses. A bandwidth of 100 Hz ',...
    //             'will be used for continued informed search.'])
    //     end
    // end
    // Fix the bandwidth in the priori to +/- 100 Hz.
    // Here is where we update the stats. These methods of updates
    // could be improved in the future.
    // wfm.ps_pre.t_p; %tp doesn't change. We assume it is stationary
    fp = freq_found;
    fstart = freq_found - 100.0;
    fend = freq_found + 100.0;
  }
}

void pulsestats::updateposteriori(const pulsestats *ps_pre,
                                  const coder::array<c_struct_T, 2U> &pulselist)
{
  coder::array<double, 2U> recent_tip;
  coder::array<double, 2U> varargin_1_tmp;
  coder::array<double, 2U> x;
  coder::array<double, 1U> result;
  coder::array<boolean_T, 2U> b_x;
  double work_data;
  int n;
  //              %UPDATEPOSTERIORI updates the posteriori pulse statistics
  //              object using the new pulse list (input), prior pulse stats
  //              and the waveforms power spectral density vector. This
  //              methods is typically going to be called on a posteriori pulse
  //              stats object after a waveform has been processed and a set
  //              of candidate pulses found. This method uses those pulses and
  //              the prior information about the pulses to update the
  //              posteriori pulse stats.
  //
  //              The pulse contained in the waveform's ps_pos
  //              property is not used directly so that the caller can decide
  //              which pulses on which to focus the posteriori updates
  //
  //  updateType    What parts of the pulsestats to update. Valid
  //                options are 'time', 'freq', 'timeandfreq'. The
  //                'time' option will only update the interpulse
  //                time statistics. The 'freq' option will only
  //                update the frequency stats. The 'timeandfreq'
  //                option will update both.
  //
  if (pulselist.size(1) != 0) {
    double d;
    int dimSize;
    boolean_T exitg1;
    boolean_T y;
    n = pulselist.size(1);
    varargin_1_tmp.set_size(1, pulselist.size(1));
    for (dimSize = 0; dimSize < n; dimSize++) {
      varargin_1_tmp[dimSize] = pulselist[dimSize].t_0;
    }
    //  pulselist(:).t_0]'
    // pulselist(:).fp
    // Create a vector of bandwidths from the pulselist
    // fEnds   = [pulselist.fend];
    // fStarts = [pulselist.fstart];
    // bw_found = 2*(mean(fEnds,'all','omitnan')-mean(fStarts,'all','omitnan'));
    // if isempty(bw_found)
    //     bw_found = 100;
    //     if coder.target('MATLAB')
    //        warning(['UAV-R: No bandwidth could be calculated ',...
    //             'from the start and stop frequencies of the ',...
    //             'identified pulses. A bandwidth of 100 Hz ',...
    //             'will be used for continued informed search.'])
    //     end
    // end
    // Fix the bandwidth in the priori to +/- 100 Hz.
    // Here is where we update the stats. These methods of updates
    // could be improved in the future.
    // wfm.ps_pre.t_p; %tp doesn't change. We assume it is stationary
    if (pulselist.size(1) == 1) {
      boolean_T guard1{false};
      //  Happens if K=1
      // We only have one pulse to reference, so we need to check
      // the prior pulse too.
      y = (ps_pre->pl.size(1) == 0);
      guard1 = false;
      if (!y) {
        work_data = ps_pre->pl[ps_pre->pl.size(1) - 1].t_0;
        if (!std::isnan(work_data)) {
          recent_tip.set_size(1, 1);
          recent_tip[0] =
              pulselist[0].t_0 - ps_pre->pl[ps_pre->pl.size(1) - 1].t_0;
          // recent_tip =
          // pulselist.t_0-ps_pre.pl(end).t_0;%Conflicts with
          // Coder. Needed the (1) callout
          // There could be a case where the last segment and this
          // segement identified the same pulse. In this case
          // recent_tip will be very small. In this case, we just
          // say we learned nothing about t_ip in this segment.
          b_x.set_size(1, 1);
          work_data = ps_pre->t_ipu + ps_pre->t_ipj;
          b_x[0] = (recent_tip[0] < work_data);
          if (b_x[0]) {
            recent_tip.set_size(1, 1);
            recent_tip[0] = rtNaN;
          }
        } else {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }
      if (guard1) {
        // No new information because we don't know the last
        // pulse time
        recent_tip.set_size(1, 1);
        recent_tip[0] = rtNaN;
      }
    } else {
      x.set_size(varargin_1_tmp.size(1), 1);
      n = varargin_1_tmp.size(1);
      for (dimSize = 0; dimSize < n; dimSize++) {
        x[dimSize] = varargin_1_tmp[dimSize];
      }
      dimSize = x.size(0);
      n = x.size(0) - 1;
      if (n > 1) {
        n = 1;
      }
      if (n < 1) {
        recent_tip.set_size(0, 1);
      } else {
        recent_tip.set_size(x.size(0) - 1, 1);
        if (recent_tip.size(0) != 0) {
          work_data = x[0];
          for (n = 2; n <= dimSize; n++) {
            double tmp1;
            tmp1 = x[n - 1];
            d = tmp1;
            tmp1 -= work_data;
            work_data = d;
            recent_tip[n - 2] = tmp1;
          }
        }
      }
    }
    // Do a check here to make sure the new tip isn't a huge change.
    // This could potentially happen if we are in the K = 1 case and
    // the block getting processed contained two pulses, with the
    // latter pulse getting identified/detected. The lines above
    // would look back to the last identified pulse and it might be
    // 2*tip back in time, producing a very large recenttip values.
    // If something like this happens, we ignore it so it doesn't
    // affect our new tip estimates.
    b_x.set_size(recent_tip.size(0), 1);
    d = 1.5 * ps_pre->t_ip;
    n = recent_tip.size(0);
    for (dimSize = 0; dimSize < n; dimSize++) {
      b_x[dimSize] = (recent_tip[dimSize] > d);
    }
    y = (b_x.size(0) != 0);
    if (y) {
      n = 0;
      exitg1 = false;
      while ((!exitg1) && (n <= b_x.size(0) - 1)) {
        if (!b_x[n]) {
          y = false;
          exitg1 = true;
        } else {
          n++;
        }
      }
    }
    if (y) {
      b_x.set_size(recent_tip.size(0), 1);
      d = 0.5 * ps_pre->t_ip;
      n = recent_tip.size(0);
      for (dimSize = 0; dimSize < n; dimSize++) {
        b_x[dimSize] = (recent_tip[dimSize] < d);
      }
      y = (b_x.size(0) != 0);
      if (y) {
        n = 0;
        exitg1 = false;
        while ((!exitg1) && (n <= b_x.size(0) - 1)) {
          if (!b_x[n]) {
            y = false;
            exitg1 = true;
          } else {
            n++;
          }
        }
      }
      if (y) {
        recent_tip.set_size(1, 1);
        recent_tip[0] = rtNaN;
      }
    }
    //                  %Only update time parameters if we are in tracking mode.
    //                  If we %aren't, we may have identified somethign that
    //                  isn't a pulse if strcmp(obj.mode,'T') ||
    //                  strcmp(ps_pre.mode,'T')
    //                      obj.t_ip  =
    //                      mean([recent_tip;ps_pre.t_ip],'omitnan'); obj.t_ipu
    //                      = ps_pre.t_ipu; %Don't update this because it can
    //                      get too
    //                      narrow.%mean([3*std(diff(t_found));wfm.ps_pre.t_ipu]);
    //                      obj.t_ipj = ps_pre.t_ipj;
    //                  end
    //                  fp_pos     =
    //                  freq_found;%nanmean([freq_found;wfm.ps_pre.fp]);%Previous
    //                  fc may be nan if unknown obj.fp     = fp_pos; obj.fstart
    //                  = fp_pos-bw_found/2; obj.fend   = fp_pos+bw_found/2;
    work_data = ps_pre->t_ip;
    if (recent_tip.size(0) != 0) {
      n = recent_tip.size(0);
    } else {
      n = 0;
    }
    result.set_size(n + 1);
    for (dimSize = 0; dimSize < n; dimSize++) {
      result[dimSize] = recent_tip[dimSize];
    }
    result[n] = work_data;
    coder::colMajorFlatIter(result, result.size(0), &work_data, &n);
    t_ip = work_data / static_cast<double>(n);
    work_data = ps_pre->t_ipu;
    t_ipu = work_data;
    // Don't update this because it can get too
    // narrow.%mean([3*std(diff(t_found));wfm.ps_pre.t_ipu]);
    work_data = ps_pre->t_ipj;
    t_ipj = work_data;
  }
}

// End of code generation (pulsestats.cpp)
