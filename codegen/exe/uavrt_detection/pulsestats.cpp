//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: pulsestats.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 22-Oct-2022 15:24:58
//

// Include Files
#include "pulsestats.h"
#include "blockedSummation.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_internal_types.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// PULSESTATS Constructs an instance of this class
//
// INPUTS:
//    tp      1x1     Duration of pulse (second)
//    tip     1x1     Inter-pulse time (seconds)
//    tipu    1x1     Inter-pulse time uncertainty (seconds)
//    tipj    1x1     Inter-pulse time jitter (deviations from means) (seconds)
//    fp      1x1     Pulses' center frequency (Hz) (if known)
//    fstart  1x1     Lower frequency bound pulses' center frequency (Hz) (if
//    known) fend    1x1     Upper frequency bound pulses' center frequency (Hz)
//    (if known) tmplt   1xn     Pulse template. See properies for
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
//
// Arguments    : double tp
//                double tip
//                double tipu
//                double tipj
//                double b_fp
//                double b_fstart
//                double b_fend
//                const double b_tmplt[2]
//                char b_mode
//                const coder::array<c_struct_T, 2U> &b_pl
//                const coder::array<c_struct_T, 2U> &b_clst
//                const coder::array<boolean_T, 2U> &b_cmsk
//                const coder::array<double, 2U> &b_cpki
// Return Type  : pulsestats *
//
pulsestats *pulsestats::b_init(double tp, double tip, double tipu, double tipj,
                               double b_fp, double b_fstart, double b_fend,
                               const double b_tmplt[2], char b_mode,
                               const coder::array<c_struct_T, 2U> &b_pl,
                               const coder::array<c_struct_T, 2U> &b_clst,
                               const coder::array<boolean_T, 2U> &b_cmsk,
                               const coder::array<double, 2U> &b_cpki)
{
  pulsestats *obj;
  coder::array<c_struct_T, 2U> b_out;
  coder::array<c_struct_T, 2U> out;
  coder::array<double, 2U> in;
  coder::array<boolean_T, 2U> c_out;
  int inVectorLength;
  obj = this;
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
  inVectorLength = 1;
  if (b_pl.size(1) != 1) {
    inVectorLength = b_pl.size(1);
  }
  if (b_pl.size(1) == 1) {
    out.set_size(1, inVectorLength);
    for (int i{0}; i < inVectorLength; i++) {
      out[i] = b_pl[0];
    }
  } else if (b_pl.size(1) == 0) {
    out.set_size(1, inVectorLength);
    for (int i{0}; i < inVectorLength; i++) {
      out[i] = b_pl[i];
    }
  } else {
    out.set_size(1, inVectorLength);
    for (int i{0}; i < inVectorLength; i++) {
      out[i] = b_pl[i];
    }
  }
  obj->pl.set_size(1, out.size(1));
  inVectorLength = out.size(1);
  for (int i{0}; i < inVectorLength; i++) {
    obj->pl[i] = out[i];
  }
  if ((b_clst.size(0) == 1) && (b_clst.size(1) == 1)) {
    b_out.set_size(1, 1);
    b_out[0] = b_clst[0];
  } else if ((b_clst.size(0) == 0) || (b_clst.size(1) == 0)) {
    b_out.set_size(b_clst.size(0), b_clst.size(1));
    inVectorLength = b_clst.size(0) * b_clst.size(1);
    for (int i{0}; i < inVectorLength; i++) {
      b_out[i] = b_clst[i];
    }
  } else {
    b_out.set_size(b_clst.size(0), b_clst.size(1));
    inVectorLength = b_clst.size(0) * b_clst.size(1);
    for (int i{0}; i < inVectorLength; i++) {
      b_out[i] = b_clst[i];
    }
  }
  obj->clst.set_size(b_out.size(0), b_out.size(1));
  inVectorLength = b_out.size(0) * b_out.size(1);
  for (int i{0}; i < inVectorLength; i++) {
    obj->clst[i] = b_out[i];
  }
  if ((b_cmsk.size(0) == 1) && (b_cmsk.size(1) == 1)) {
    c_out.set_size(1, 1);
    c_out[0] = b_cmsk[0];
  } else if ((b_cmsk.size(0) == 0) || (b_cmsk.size(1) == 0)) {
    c_out.set_size(b_cmsk.size(0), b_cmsk.size(1));
    inVectorLength = b_cmsk.size(0) * b_cmsk.size(1);
    for (int i{0}; i < inVectorLength; i++) {
      c_out[i] = b_cmsk[i];
    }
  } else {
    c_out.set_size(b_cmsk.size(0), b_cmsk.size(1));
    inVectorLength = b_cmsk.size(0) * b_cmsk.size(1);
    for (int i{0}; i < inVectorLength; i++) {
      c_out[i] = b_cmsk[i];
    }
  }
  obj->cmsk.set_size(c_out.size(0), c_out.size(1));
  inVectorLength = c_out.size(0) * c_out.size(1);
  for (int i{0}; i < inVectorLength; i++) {
    obj->cmsk[i] = c_out[i];
  }
  in.set_size(b_cpki.size(0), b_cpki.size(1));
  inVectorLength = b_cpki.size(0) * b_cpki.size(1);
  for (int i{0}; i < inVectorLength; i++) {
    in[i] = b_cpki[i];
  }
  if ((b_cpki.size(0) == 1) && (b_cpki.size(1) == 1)) {
    in.set_size(1, 1);
    in[0] = b_cpki[0];
  }
  obj->cpki.set_size(in.size(0), in.size(1));
  inVectorLength = in.size(0) * in.size(1);
  for (int i{0}; i < inVectorLength; i++) {
    obj->cpki[i] = in[i];
  }
  return obj;
}

//
// PULSESTATS Constructs an instance of this class
//
// INPUTS:
//    tp      1x1     Duration of pulse (second)
//    tip     1x1     Inter-pulse time (seconds)
//    tipu    1x1     Inter-pulse time uncertainty (seconds)
//    tipj    1x1     Inter-pulse time jitter (deviations from means) (seconds)
//    fp      1x1     Pulses' center frequency (Hz) (if known)
//    fstart  1x1     Lower frequency bound pulses' center frequency (Hz) (if
//    known) fend    1x1     Upper frequency bound pulses' center frequency (Hz)
//    (if known) tmplt   1xn     Pulse template. See properies for
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
//
// Arguments    : double tp
//                double tip
//                double tipu
//                double tipj
//                double b_fp
//                double b_fstart
//                double b_fend
//                const double b_tmplt[2]
//                const char mode_data[]
//                const coder::array<c_struct_T, 2U> &b_pl
//                const coder::array<c_struct_T, 2U> &b_clst
//                const coder::array<boolean_T, 2U> &b_cmsk
//                const coder::array<double, 2U> &b_cpki
// Return Type  : pulsestats *
//
pulsestats *pulsestats::c_init(double tp, double tip, double tipu, double tipj,
                               double b_fp, double b_fstart, double b_fend,
                               const double b_tmplt[2], const char mode_data[],
                               const coder::array<c_struct_T, 2U> &b_pl,
                               const coder::array<c_struct_T, 2U> &b_clst,
                               const coder::array<boolean_T, 2U> &b_cmsk,
                               const coder::array<double, 2U> &b_cpki)
{
  pulsestats *obj;
  coder::array<c_struct_T, 2U> b_out;
  coder::array<c_struct_T, 2U> out;
  coder::array<double, 2U> in;
  coder::array<boolean_T, 2U> c_out;
  int inVectorLength;
  obj = this;
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
  inVectorLength = 1;
  if (b_pl.size(1) != 1) {
    inVectorLength = b_pl.size(1);
  }
  if (b_pl.size(1) == 1) {
    out.set_size(1, inVectorLength);
    for (int i{0}; i < inVectorLength; i++) {
      out[i] = b_pl[0];
    }
  } else if (b_pl.size(1) == 0) {
    out.set_size(1, inVectorLength);
    for (int i{0}; i < inVectorLength; i++) {
      out[i] = b_pl[i];
    }
  } else {
    out.set_size(1, inVectorLength);
    for (int i{0}; i < inVectorLength; i++) {
      out[i] = b_pl[i];
    }
  }
  obj->pl.set_size(1, out.size(1));
  inVectorLength = out.size(1);
  for (int i{0}; i < inVectorLength; i++) {
    obj->pl[i] = out[i];
  }
  if ((b_clst.size(0) == 1) && (b_clst.size(1) == 1)) {
    b_out.set_size(1, 1);
    b_out[0] = b_clst[0];
  } else if ((b_clst.size(0) == 0) || (b_clst.size(1) == 0)) {
    b_out.set_size(b_clst.size(0), b_clst.size(1));
    inVectorLength = b_clst.size(0) * b_clst.size(1);
    for (int i{0}; i < inVectorLength; i++) {
      b_out[i] = b_clst[i];
    }
  } else {
    b_out.set_size(b_clst.size(0), b_clst.size(1));
    inVectorLength = b_clst.size(0) * b_clst.size(1);
    for (int i{0}; i < inVectorLength; i++) {
      b_out[i] = b_clst[i];
    }
  }
  obj->clst.set_size(b_out.size(0), b_out.size(1));
  inVectorLength = b_out.size(0) * b_out.size(1);
  for (int i{0}; i < inVectorLength; i++) {
    obj->clst[i] = b_out[i];
  }
  if ((b_cmsk.size(0) == 1) && (b_cmsk.size(1) == 1)) {
    c_out.set_size(1, 1);
    c_out[0] = b_cmsk[0];
  } else if ((b_cmsk.size(0) == 0) || (b_cmsk.size(1) == 0)) {
    c_out.set_size(b_cmsk.size(0), b_cmsk.size(1));
    inVectorLength = b_cmsk.size(0) * b_cmsk.size(1);
    for (int i{0}; i < inVectorLength; i++) {
      c_out[i] = b_cmsk[i];
    }
  } else {
    c_out.set_size(b_cmsk.size(0), b_cmsk.size(1));
    inVectorLength = b_cmsk.size(0) * b_cmsk.size(1);
    for (int i{0}; i < inVectorLength; i++) {
      c_out[i] = b_cmsk[i];
    }
  }
  obj->cmsk.set_size(c_out.size(0), c_out.size(1));
  inVectorLength = c_out.size(0) * c_out.size(1);
  for (int i{0}; i < inVectorLength; i++) {
    obj->cmsk[i] = c_out[i];
  }
  in.set_size(b_cpki.size(0), b_cpki.size(1));
  inVectorLength = b_cpki.size(0) * b_cpki.size(1);
  for (int i{0}; i < inVectorLength; i++) {
    in[i] = b_cpki[i];
  }
  if ((b_cpki.size(0) == 1) && (b_cpki.size(1) == 1)) {
    in.set_size(1, 1);
    in[0] = b_cpki[0];
  }
  obj->cpki.set_size(in.size(0), in.size(1));
  inVectorLength = in.size(0) * in.size(1);
  for (int i{0}; i < inVectorLength; i++) {
    obj->cpki[i] = in[i];
  }
  return obj;
}

//
// PULSESTATS Constructs an instance of this class
//
// INPUTS:
//    tp      1x1     Duration of pulse (second)
//    tip     1x1     Inter-pulse time (seconds)
//    tipu    1x1     Inter-pulse time uncertainty (seconds)
//    tipj    1x1     Inter-pulse time jitter (deviations from means) (seconds)
//    fp      1x1     Pulses' center frequency (Hz) (if known)
//    fstart  1x1     Lower frequency bound pulses' center frequency (Hz) (if
//    known) fend    1x1     Upper frequency bound pulses' center frequency (Hz)
//    (if known) tmplt   1xn     Pulse template. See properies for
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
//
// Arguments    : double tp
//                double tip
//                double tipu
//                double tipj
//                const c_struct_T *b_pl
//                const c_struct_T *b_clst
// Return Type  : pulsestats *
//
pulsestats *pulsestats::init(double tp, double tip, double tipu, double tipj,
                             const c_struct_T *b_pl, const c_struct_T *b_clst)
{
  pulsestats *obj;
  coder::array<c_struct_T, 2U> in;
  coder::array<c_struct_T, 2U> out;
  obj = this;
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
  out.set_size(1, 1);
  out[0] = *b_pl;
  obj->pl.set_size(1, 1);
  obj->pl[0] = out[0];
  in.set_size(1, 1);
  in[0] = *b_clst;
  obj->clst.set_size(1, 1);
  obj->clst[0] = in[0];
  obj->cmsk.set_size(0, 0);
  obj->cpki.set_size(0, 0);
  return obj;
}

//
// PULSESTATS Constructs an instance of this class
//
// INPUTS:
//    tp      1x1     Duration of pulse (second)
//    tip     1x1     Inter-pulse time (seconds)
//    tipu    1x1     Inter-pulse time uncertainty (seconds)
//    tipj    1x1     Inter-pulse time jitter (deviations from means) (seconds)
//    fp      1x1     Pulses' center frequency (Hz) (if known)
//    fstart  1x1     Lower frequency bound pulses' center frequency (Hz) (if
//    known) fend    1x1     Upper frequency bound pulses' center frequency (Hz)
//    (if known) tmplt   1xn     Pulse template. See properies for
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
//
// Arguments    : double tp
//                double tip
//                double tipu
//                double tipj
//                double b_fp
//                const c_struct_T *b_pl
//                const c_struct_T *b_clst
// Return Type  : pulsestats *
//
pulsestats *pulsestats::init(double tp, double tip, double tipu, double tipj,
                             double b_fp, const c_struct_T *b_pl,
                             const c_struct_T *b_clst)
{
  pulsestats *obj;
  coder::array<c_struct_T, 2U> in;
  coder::array<c_struct_T, 2U> out;
  obj = this;
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
  out.set_size(1, 1);
  out[0] = *b_pl;
  obj->pl.set_size(1, 1);
  obj->pl[0] = out[0];
  in.set_size(1, 1);
  in[0] = *b_clst;
  obj->clst.set_size(1, 1);
  obj->clst[0] = in[0];
  obj->cmsk.set_size(1, 1);
  obj->cmsk[0] = false;
  obj->cpki.set_size(1, 1);
  obj->cpki[0] = rtNaN;
  return obj;
}

//
// %UPDATEPOSTERIORI updates the posteriori pulse statistics
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
//
// Arguments    : const coder::array<c_struct_T, 2U> &pulselist
// Return Type  : void
//
void pulsestats::updateposteriori(const coder::array<c_struct_T, 2U> &pulselist)
{
  coder::array<double, 2U> varargin_1;
  double freq_found;
  int n;
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

//
// %UPDATEPOSTERIORI updates the posteriori pulse statistics
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
//
// Arguments    : const pulsestats *ps_pre
//                const coder::array<c_struct_T, 2U> &pulselist
// Return Type  : void
//
void pulsestats::updateposteriori(const pulsestats *ps_pre,
                                  const coder::array<c_struct_T, 2U> &pulselist)
{
  coder::array<double, 2U> b_result;
  coder::array<double, 2U> recent_tip;
  coder::array<double, 2U> result;
  coder::array<double, 2U> x;
  coder::array<double, 1U> c_result;
  coder::array<boolean_T, 2U> b_x;
  double work_data;
  int n;
  if (pulselist.size(1) != 0) {
    double d;
    boolean_T exitg1;
    boolean_T y;
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
      //  Happens if K=1
      // We only have one pulse to reference, so we need to check
      // the prior pulse too.
      if ((ps_pre->pl.size(1) != 0) &&
          (!std::isnan(ps_pre->pl[ps_pre->pl.size(1) - 1].t_0))) {
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
        b_x[0] = (recent_tip[0] < ps_pre->t_ipu + ps_pre->t_ipj);
        if (b_x[0]) {
          recent_tip.set_size(1, 1);
          recent_tip[0] = rtNaN;
        }
      } else {
        // No new information because we don't know the last
        // pulse time
        recent_tip.set_size(1, 1);
        recent_tip[0] = rtNaN;
      }
    } else {
      n = pulselist.size(1);
      result.set_size(1, pulselist.size(1));
      for (int i{0}; i < n; i++) {
        result[i] = pulselist[i].t_0;
      }
      n = pulselist.size(1);
      b_result.set_size(1, pulselist.size(1));
      for (int i{0}; i < n; i++) {
        b_result[i] = pulselist[i].t_0;
      }
      x.set_size(b_result.size(1), 1);
      n = b_result.size(1);
      for (int i{0}; i < n; i++) {
        x[i] = result[i];
      }
      n = x.size(0);
      recent_tip.set_size(x.size(0) - 1, 1);
      work_data = x[0];
      for (int i{2}; i <= n; i++) {
        double tmp1;
        tmp1 = x[i - 1];
        d = tmp1;
        tmp1 -= work_data;
        work_data = d;
        recent_tip[i - 2] = tmp1;
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
    for (int i{0}; i < n; i++) {
      b_x[i] = (recent_tip[i] > d);
    }
    y = true;
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
    if (y) {
      b_x.set_size(recent_tip.size(0), 1);
      d = 0.5 * ps_pre->t_ip;
      n = recent_tip.size(0);
      for (int i{0}; i < n; i++) {
        b_x[i] = (recent_tip[i] < d);
      }
      y = true;
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
    n = recent_tip.size(0);
    c_result.set_size(recent_tip.size(0) + 1);
    for (int i{0}; i < n; i++) {
      c_result[i] = recent_tip[i];
    }
    c_result[recent_tip.size(0)] = ps_pre->t_ip;
    coder::colMajorFlatIter(c_result, c_result.size(0), &work_data, &n);
    t_ip = work_data / static_cast<double>(n);
    t_ipu = ps_pre->t_ipu;
    // Don't update this because it can get too
    // narrow.%mean([3*std(diff(t_found));wfm.ps_pre.t_ipu]);
    t_ipj = ps_pre->t_ipj;
  }
}

//
// File trailer for pulsestats.cpp
//
// [EOF]
//
