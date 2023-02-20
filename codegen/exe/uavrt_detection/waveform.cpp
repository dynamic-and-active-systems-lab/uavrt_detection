//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: waveform.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 14:31:55
//

// Include Files
#include "waveform.h"
#include "find.h"
#include "pulsestats.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include "stft.h"
#include "threshold.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_internal_types.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "validator_check_size.h"
#include "wfmstft.h"
#include "coder_array.h"
#include "omp.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string.h>
#include <string>

// Variable Definitions
static rtRunTimeErrorInfo y_emlrtRTEI{
    18,           // lineNo
    "check_order" // fName
};

static rtRunTimeErrorInfo ab_emlrtRTEI{
    22,           // lineNo
    "check_order" // fName
};

// Function Declarations
static void binary_expand_op(double in1_data[], int *in1_size,
                             const double in2_data[], const int in2_size[2],
                             const double in3_data[], const int in3_size[2]);

static void cb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void f_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum);

static void l_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum);

static void r_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : double in1_data[]
//                int *in1_size
//                const double in2_data[]
//                const int in2_size[2]
//                const double in3_data[]
//                const int in3_size[2]
// Return Type  : void
//
static void binary_expand_op(double in1_data[], int *in1_size,
                             const double in2_data[], const int in2_size[2],
                             const double in3_data[], const int in3_size[2])
{
  int loop_ub;
  if (in3_size[1] == 1) {
    *in1_size = in2_size[1];
    loop_ub = in2_size[1];
  } else {
    *in1_size = in3_size[1];
    loop_ub = in3_size[1];
  }
  for (int i{0}; i < loop_ub; i++) {
    in1_data[0] = in2_data[0] + in3_data[0];
  }
}

//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void cb_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "The data abscissae must be distinct and strictly monotonic.";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// Arguments    : const char *r
//                const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void f_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((outStream << "Order, ") << r) << ", must be finite.";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// Arguments    : const char *r
//                const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void l_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((outStream << "For code generation, ") << r) << " must not be NaN.";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void r_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Order must be greater than or equal to zero.";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// WAVEFORM Constructs an instance of this class
// INPUTS:
//    x       1xn     Vector of samples
//    Fs      1x1     Sample frequency (Hz)
//    t_0     1x1     Time stamp of first element (s)
//  ps_pre  1x1     Pulse stats object from previous data (priori)
//    OLF     1x1     Overlap fraction as decimal (0.5 = 50%
//                    overlap)
// OUTPUTS:
//    obj             The waveform object
//             %%
//
// Arguments    : const creal32_T b_x[1000]
//                double b_Fs
//                pulsestats *b_ps_pre
//                const threshold *b_thresh
// Return Type  : waveform *
//
waveform *waveform::init(const creal32_T b_x[1000], double b_Fs,
                         pulsestats *b_ps_pre, const threshold *b_thresh)
{
  pulsestats *obj_out;
  waveform *b_obj;
  waveform *obj;
  wfmstft *val;
  coder::array<c_struct_T, 2U> c_ps_pre;
  coder::array<c_struct_T, 2U> d_ps_pre;
  coder::array<creal_T, 2U> r;
  coder::array<creal_T, 2U> r1;
  coder::array<double, 2U> f_ps_pre;
  coder::array<double, 1U> b_tmp_data;
  coder::array<double, 1U> r2;
  coder::array<boolean_T, 2U> e_ps_pre;
  double tmp_data[400];
  int loop_ub;
  obj = this;
  obj->x.set_size(1, 0);
  r.set(nullptr, 0, 0);
  coder::internal::validator_check_size(r, r1);
  obj->W.set_size(0, 0);
  b_tmp_data.set(&tmp_data[0], 0);
  coder::internal::validator_check_size(b_tmp_data, r2);
  obj->Wf.set_size(r2.size(0));
  loop_ub = r2.size(0);
  for (int i{0}; i < loop_ub; i++) {
    obj->Wf[i] = r2[i];
  }
  // Flatten input to row
  obj->x.set_size(1, 1000);
  for (int i{0}; i < 1000; i++) {
    obj->x[i] = b_x[i];
  }
  // Data vector
  obj->l = 1000.0;
  // Elements in the data
  obj->Fs = b_Fs;
  // Sample rate
  obj->t_0 = 0.0;
  // Time stamp of first element
  obj->t_f = 999.0 / b_Fs;
  // Time stamp of last element
  obj->t_nextsegstart[0] = 0.0;
  obj->t_nextsegstart[1] = 0.0;
  // This is the time when next
  // segment should start to
  // ensure sufficient overlap.
  // Will need to be updated
  // elsewhere.
  obj->ps_pre = b_ps_pre;
  obj->OLF = 0.5;
  // Overlap Fraction for STFT
  obj->K = rtNaN;
  // Unknown number of pulses.
  b_obj = obj;
  val = obj->_pobj1.init();
  b_obj->stft = val;
  // Unknown values but set types
  obj->W.set_size(0, 0);
  obj->Wf.set_size(0);
  // Copy over ps_
  // COPY Creates an exact copy of the pulse stats object as a separate object
  c_ps_pre.set_size(1, b_ps_pre->pl.size(1));
  loop_ub = b_ps_pre->pl.size(0) * b_ps_pre->pl.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    c_ps_pre[i] = b_ps_pre->pl[i];
  }
  d_ps_pre.set_size(b_ps_pre->clst.size(0), b_ps_pre->clst.size(1));
  loop_ub = b_ps_pre->clst.size(0) * b_ps_pre->clst.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    d_ps_pre[i] = b_ps_pre->clst[i];
  }
  e_ps_pre.set_size(b_ps_pre->cmsk.size(0), b_ps_pre->cmsk.size(1));
  loop_ub = b_ps_pre->cmsk.size(0) * b_ps_pre->cmsk.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    e_ps_pre[i] = b_ps_pre->cmsk[i];
  }
  f_ps_pre.set_size(b_ps_pre->cpki.size(0), b_ps_pre->cpki.size(1));
  loop_ub = b_ps_pre->cpki.size(0) * b_ps_pre->cpki.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    f_ps_pre[i] = b_ps_pre->cpki[i];
  }
  double g_ps_pre[2];
  g_ps_pre[0] = b_ps_pre->tmplt[0];
  g_ps_pre[1] = b_ps_pre->tmplt[1];
  obj_out = obj->_pobj0.b_init(b_ps_pre->t_p, b_ps_pre->t_ip, b_ps_pre->t_ipu,
                               b_ps_pre->t_ipj, b_ps_pre->fp, b_ps_pre->fstart,
                               b_ps_pre->fend, g_ps_pre, b_ps_pre->mode,
                               c_ps_pre, d_ps_pre, e_ps_pre, f_ps_pre);
  // ,...
  // obj.thresh);
  obj->ps_pos = obj_out;
  // Current stats are same as previous during construction
  // obj.ps_pos = pulsestats();%TESTING FOR CODER - NEEDS TO BE REVERTED BACK TO
  // LAST LINE obj.TimeCorr = TemporalCorrelator(10, 0, 0);%Generate a
  // temporalcorrelator object so coder knows the type of the object
  obj->setprioridependentprops(b_ps_pre);
  obj->thresh = *b_thresh;
  return obj;
}

//
// WAVEFORM Constructs an instance of this class
// INPUTS:
//    x       1xn     Vector of samples
//    Fs      1x1     Sample frequency (Hz)
//    t_0     1x1     Time stamp of first element (s)
//  ps_pre  1x1     Pulse stats object from previous data (priori)
//    OLF     1x1     Overlap fraction as decimal (0.5 = 50%
//                    overlap)
// OUTPUTS:
//    obj             The waveform object
//             %%
//
// Arguments    : const creal32_T b_x[1000]
//                double b_Fs
//                pulsestats *b_ps_pre
//                pulsestats *iobj_0
//                wfmstft *iobj_1
// Return Type  : b_waveform *
//
b_waveform *b_waveform::init(const creal32_T b_x[1000], double b_Fs,
                             pulsestats *b_ps_pre, pulsestats *iobj_0,
                             wfmstft *iobj_1)
{
  b_waveform *obj;
  pulsestats *obj_out;
  wfmstft *val;
  coder::array<c_struct_T, 2U> c_ps_pre;
  coder::array<c_struct_T, 2U> d_ps_pre;
  coder::array<creal_T, 2U> r;
  coder::array<creal_T, 2U> r1;
  coder::array<double, 2U> f_ps_pre;
  coder::array<double, 1U> b_tmp_data;
  coder::array<double, 1U> c_tmp_data;
  coder::array<boolean_T, 2U> e_ps_pre;
  double tmp_data[400];
  int loop_ub;
  obj = this;
  obj->x.set_size(1, 0);
  r.set(nullptr, 0, 0);
  coder::internal::validator_check_size(r, r1);
  b_tmp_data.set(&tmp_data[0], 0);
  coder::internal::validator_check_size(b_tmp_data, c_tmp_data);
  // Flatten input to row
  obj->x.set_size(1, 1000);
  for (int i{0}; i < 1000; i++) {
    obj->x[i] = b_x[i];
  }
  // Data vector
  // Elements in the data
  obj->Fs = b_Fs;
  // Sample rate
  obj->t_0 = 0.0;
  // Time stamp of first element
  // Time stamp of last element
  // This is the time when next
  // segment should start to
  // ensure sufficient overlap.
  // Will need to be updated
  // elsewhere.
  obj->ps_pre = b_ps_pre;
  obj->OLF = 0.5;
  // Overlap Fraction for STFT
  obj->K = rtNaN;
  // Unknown number of pulses.
  val = iobj_1->init();
  obj->stft = val;
  // Unknown values but set types
  // Copy over ps_
  // COPY Creates an exact copy of the pulse stats object as a separate object
  c_ps_pre.set_size(1, b_ps_pre->pl.size(1));
  loop_ub = b_ps_pre->pl.size(0) * b_ps_pre->pl.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    c_ps_pre[i] = b_ps_pre->pl[i];
  }
  d_ps_pre.set_size(b_ps_pre->clst.size(0), b_ps_pre->clst.size(1));
  loop_ub = b_ps_pre->clst.size(0) * b_ps_pre->clst.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    d_ps_pre[i] = b_ps_pre->clst[i];
  }
  e_ps_pre.set_size(b_ps_pre->cmsk.size(0), b_ps_pre->cmsk.size(1));
  loop_ub = b_ps_pre->cmsk.size(0) * b_ps_pre->cmsk.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    e_ps_pre[i] = b_ps_pre->cmsk[i];
  }
  f_ps_pre.set_size(b_ps_pre->cpki.size(0), b_ps_pre->cpki.size(1));
  loop_ub = b_ps_pre->cpki.size(0) * b_ps_pre->cpki.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    f_ps_pre[i] = b_ps_pre->cpki[i];
  }
  double g_ps_pre[2];
  double b_n_ol;
  double n_p;
  g_ps_pre[0] = b_ps_pre->tmplt[0];
  g_ps_pre[1] = b_ps_pre->tmplt[1];
  obj_out = iobj_0->b_init(b_ps_pre->t_p, b_ps_pre->t_ip, b_ps_pre->t_ipu,
                           b_ps_pre->t_ipj, b_ps_pre->fp, b_ps_pre->fstart,
                           b_ps_pre->fend, g_ps_pre, b_ps_pre->mode, c_ps_pre,
                           d_ps_pre, e_ps_pre, f_ps_pre);
  // ,...
  // obj.thresh);
  obj->ps_pos = obj_out;
  // Current stats are same as previous during construction
  // obj.ps_pos = pulsestats();%TESTING FOR CODER - NEEDS TO BE REVERTED BACK TO
  // LAST LINE obj.TimeCorr = TemporalCorrelator(10, 0, 0);%Generate a
  // temporalcorrelator object so coder knows the type of the object
  // SETPRIORIDEPENDENTVARS updates the properties in the
  // waveform that are dependent on properties in a pulsestats
  // object.
  //
  // INPUTS:
  //    obj     waveform object
  //    ps_obj  a pulse stats object
  // OUTPUTS:
  //    None (This method modifies the waveform object properties)
  //
  //             %%
  // GETPRIORIDEPENDENTVARS returns the properties in the
  // waveform that are dependent on prior pulse data estimates. It
  // depends on the waveform properties list Fs etc, as well as
  // pulse stats like t_ip, etc.
  // INPUTS:  ps_obj  1x1 pulse stats object
  // OUTPUTS:  pulse stats object
  // WHAT WAS DONE BY THIS METHOD IS NOW DONE BY A METHOD OF THE
  // PULSESTATS CLASS.
  //          function [] = update_posteriori(obj,pulselist)
  //              %UPDATE_POSTERIORI updates the posteriori pulse statistics of
  //              %this waveform object using the new pulse list (input) and the
  //              %apriori stats. The pulse contained in the waveform's ps_pos
  //              %property is not used directly so that the caller can decide
  //              %which pulses on which to focus the posteriori.
  //
  //              t_found    = [pulselist(:).t_0]';
  //              freq_found = mean([pulselist(:).fp],'omitnan');
  //
  //              %Create a vector of bandwidths from the pulselist
  //              bw_found =
  //              2*(mean([pulselist.fend],'omitnan')-mean([pulselist.fstart],'omitnan'));
  //              if isempty(bw_found)
  //                  bw_found = 100;
  //                  if coder.target('MATLAB')
  //                      warning(['UAV-R: No bandwidth could be calculated
  //                      ',...
  //                           'from the start and stop frequencies of the ',...
  //                           'identified pulses. A bandwidth of 100 Hz ',...
  //                           'will be used for continued informed search.'])
  //                  end
  //              end
  //
  //              %Here is where we update the stats. These methods of updates
  //              %could be improved in the future.
  //              %obj.ps_pre.t_p; %tp doesn't change. We assume it is
  //              stationary
  //
  //              if numel(pulselist)==1% Happens if K=1
  //                  %We only have one pulse to reference, so we need to check
  //                  %the prior pulse too.
  //                  if ~isempty(obj.ps_pre.pl) &&
  //                  ~isnan(obj.ps_pre.pl(end).t_0)
  //                      recent_tip = pulselist.t_0-obj.ps_pre.pl(end).t_0;
  //                      %There could be a case where the last segment and this
  //                      %segement identified the same pulse. In this case
  //                      %recent_tip will be very small. In this case, we just
  //                      %say we learned nothing about t_ip in this segment.
  //                      if recent_tip < obj.ps_pre.t_ipu + obj.ps_pre.t_ipJ
  //                          recent_tip = NaN;
  //                      end
  //                  else
  //                      %No new information because we don't know the last
  //                      %pulse time
  //                      recent_tip = NaN;
  //                  end
  //              else
  //                  recent_tip = diff(t_found);
  //              end
  //              %Do a check here to make sure the new tip isn't a huge change.
  //              %This could potentially happen if we are in the K = 1 case and
  //              %the block getting processed contained two pulses, with the
  //              %latter pulse getting identified/detected. The lines above
  //              %would look back to the last identified pulse and it might be
  //              %2*tip back in time, producing a very large recenttip values.
  //              %If something like this happens, we ignore it so it doesn't
  //              %affect our new tip estimates.
  //              if recent_tip > 1.5*obj.ps_pre.t_ip & recent_tip <
  //              0.5*obj.ps_pre.t_ip
  //                  recent_tip = NaN;
  //              end
  //
  //              %Only update time parameters if we are in tracking mode. If we
  //              %aren't, we may have identified somethign that isn't a pulse
  //              if strcmp(obj.ps_pos.mode,'T') || strcmp(obj.ps_pre.mode,'T')
  //                  obj.ps_pos.t_ip  =
  //                  mean([recent_tip;obj.ps_pre.t_ip],'omitnan');
  //                  obj.ps_pos.t_ipu = obj.ps_pre.t_ipu; %Don't update this
  //                  because it can get too
  //                  narrow.%mean([3*std(diff(t_found));obj.ps_pre.t_ipu]);
  //                  obj.ps_pos.t_ipj = obj.ps_pre.t_ipj;
  //              end
  //              fp_pos           =
  //              freq_found;%nanmean([freq_found;obj.ps_pre.fp]);%Previous fc
  //              may be nan if unknown obj.ps_pos.fp    = fp_pos;
  //              obj.ps_pos.fstart = fp_pos-bw_found/2;
  //              obj.ps_pos.fend   = fp_pos+bw_found/2;
  //
  //              obj.ps_pos.psdHist = obj.stft.psd
  //          end
  n_p = b_ps_pre->t_p * obj->Fs;
  n_p = std::ceil(n_p);
  // Samples per pulse
  // Number of elements in STFT window
  b_n_ol = obj->OLF * n_p;
  // Number of elements overlap in STFT window
  // Number of elements in each step of STFT
  // Time of each step of STFT
  // Samples per pulse
  obj->n_w = n_p;
  // Number of elements in STFT window
  obj->n_ol = std::floor(b_n_ol);
  // Number of elements overlap in STFT window
  // Number of elements in each step of STFT
  // Time of each step of STFT
  // Samples of interpulse duration
  // Baseline interpulse duration in units of STFT windows
  // Interpulse duration deviation from baselines in units of STFT windows
  // Amount of deviation from the PRI means to search
  //              if K ~= 1
  //                  samplesforKpulses = n_ws*(K*(N+M)-2*M)+n_ol;
  //              else
  //                  samplesforKpulses = n_ws*(N+M+J+1)+n_ol;
  //              end
  // See 2022-07-11 for updates to samples def
  // obj.t_nextsegstart  = obj.t_0+(samplesforKpulses)/obj.Fs; %Don't need the
  // overlap here since the next segment starts at samplesforKpulses+n_ol-n_ol
  // from current sample Don't need the overlap here since the next segment
  // starts at samplesforKpulses+n_ol-n_ol from current sample
  //              if isempty(obj.TimeCorr)
  //                  obj.TimeCorr = TemporalCorrelator(N, M, J);
  //              else
  //                  obj.TimeCorr.update(N, M, J);
  //              end
  return obj;
}

//
// WAVEFORM Constructs an instance of this class
// INPUTS:
//    x       1xn     Vector of samples
//    Fs      1x1     Sample frequency (Hz)
//    t_0     1x1     Time stamp of first element (s)
//  ps_pre  1x1     Pulse stats object from previous data (priori)
//    OLF     1x1     Overlap fraction as decimal (0.5 = 50%
//                    overlap)
// OUTPUTS:
//    obj             The waveform object
//             %%
//
// Arguments    : const creal32_T x_data[]
//                int x_size
//                double b_Fs
//                double b_t_0
//                pulsestats *b_ps_pre
//                const threshold *b_thresh
//                pulsestats *iobj_0
//                wfmstft *iobj_1
// Return Type  : waveform *
//
waveform *waveform::init(const creal32_T x_data[], int x_size, double b_Fs,
                         double b_t_0, pulsestats *b_ps_pre,
                         const threshold *b_thresh, pulsestats *iobj_0,
                         wfmstft *iobj_1)
{
  pulsestats *obj_out;
  waveform *obj;
  wfmstft *val;
  coder::array<c_struct_T, 2U> c_ps_pre;
  coder::array<c_struct_T, 2U> d_ps_pre;
  coder::array<creal_T, 2U> r;
  coder::array<creal_T, 2U> r1;
  coder::array<double, 2U> f_ps_pre;
  coder::array<double, 1U> b_tmp_data;
  coder::array<double, 1U> r2;
  coder::array<boolean_T, 2U> e_ps_pre;
  double tmp_data[400];
  int loop_ub;
  obj = this;
  obj->x.set_size(1, 0);
  r.set(nullptr, 0, 0);
  coder::internal::validator_check_size(r, r1);
  obj->W.set_size(0, 0);
  b_tmp_data.set(&tmp_data[0], 0);
  coder::internal::validator_check_size(b_tmp_data, r2);
  obj->Wf.set_size(r2.size(0));
  loop_ub = r2.size(0);
  for (int i{0}; i < loop_ub; i++) {
    obj->Wf[i] = r2[i];
  }
  if (x_size < 1) {
    l_rtErrorWithMessageID(m_emlrtRTEI.fName, m_emlrtRTEI.lineNo);
  }
  // Flatten input to row
  obj->x.set_size(1, 1);
  obj->x[0] = x_data[0];
  // Data vector
  obj->l = 1000.0;
  // Elements in the data
  obj->Fs = b_Fs;
  // Sample rate
  obj->t_0 = 0.0;
  // Time stamp of first element
  obj->t_f = b_t_0 + 0.0 / b_Fs;
  // Time stamp of last element
  obj->t_nextsegstart[0] = b_t_0;
  obj->t_nextsegstart[1] = b_t_0;
  // This is the time when next
  // segment should start to
  // ensure sufficient overlap.
  // Will need to be updated
  // elsewhere.
  obj->ps_pre = b_ps_pre;
  obj->OLF = 0.5;
  // Overlap Fraction for STFT
  obj->K = rtNaN;
  // Unknown number of pulses.
  val = iobj_1->init();
  obj->stft = val;
  // Unknown values but set types
  obj->W.set_size(0, 0);
  obj->Wf.set_size(0);
  // Copy over ps_
  // COPY Creates an exact copy of the pulse stats object as a separate object
  c_ps_pre.set_size(1, b_ps_pre->pl.size(1));
  loop_ub = b_ps_pre->pl.size(0) * b_ps_pre->pl.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    c_ps_pre[i] = b_ps_pre->pl[i];
  }
  d_ps_pre.set_size(b_ps_pre->clst.size(0), b_ps_pre->clst.size(1));
  loop_ub = b_ps_pre->clst.size(0) * b_ps_pre->clst.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    d_ps_pre[i] = b_ps_pre->clst[i];
  }
  e_ps_pre.set_size(b_ps_pre->cmsk.size(0), b_ps_pre->cmsk.size(1));
  loop_ub = b_ps_pre->cmsk.size(0) * b_ps_pre->cmsk.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    e_ps_pre[i] = b_ps_pre->cmsk[i];
  }
  f_ps_pre.set_size(b_ps_pre->cpki.size(0), b_ps_pre->cpki.size(1));
  loop_ub = b_ps_pre->cpki.size(0) * b_ps_pre->cpki.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    f_ps_pre[i] = b_ps_pre->cpki[i];
  }
  double g_ps_pre[2];
  g_ps_pre[0] = b_ps_pre->tmplt[0];
  g_ps_pre[1] = b_ps_pre->tmplt[1];
  obj_out = iobj_0->b_init(b_ps_pre->t_p, b_ps_pre->t_ip, b_ps_pre->t_ipu,
                           b_ps_pre->t_ipj, b_ps_pre->fp, b_ps_pre->fstart,
                           b_ps_pre->fend, g_ps_pre, b_ps_pre->mode, c_ps_pre,
                           d_ps_pre, e_ps_pre, f_ps_pre);
  // ,...
  // obj.thresh);
  obj->ps_pos = obj_out;
  // Current stats are same as previous during construction
  // obj.ps_pos = pulsestats();%TESTING FOR CODER - NEEDS TO BE REVERTED BACK TO
  // LAST LINE obj.TimeCorr = TemporalCorrelator(10, 0, 0);%Generate a
  // temporalcorrelator object so coder knows the type of the object
  obj->setprioridependentprops(b_ps_pre);
  obj->thresh = *b_thresh;
  return obj;
}

//
// SETPRIORIDEPENDENTVARS updates the properties in the
// waveform that are dependent on properties in a pulsestats
// object.
//
// INPUTS:
//    obj     waveform object
//    ps_obj  a pulse stats object
// OUTPUTS:
//    None (This method modifies the waveform object properties)
//
//             %%
//
// Arguments    : const pulsestats *ps_obj
// Return Type  : void
//
void waveform::setprioridependentprops(const pulsestats *ps_obj)
{
  double b_M;
  double b_N;
  double b_n_ip;
  double b_n_ol;
  double b_n_p;
  double b_n_ws;
  double n_ipj;
  double n_ipu;
  double val;
  // GETPRIORIDEPENDENTVARS returns the properties in the
  // waveform that are dependent on prior pulse data estimates. It
  // depends on the waveform properties list Fs etc, as well as
  // pulse stats like t_ip, etc.
  // INPUTS:  ps_obj  1x1 pulse stats object
  // OUTPUTS:  pulse stats object
  // WHAT WAS DONE BY THIS METHOD IS NOW DONE BY A METHOD OF THE
  // PULSESTATS CLASS.
  //          function [] = update_posteriori(obj,pulselist)
  //              %UPDATE_POSTERIORI updates the posteriori pulse statistics of
  //              %this waveform object using the new pulse list (input) and the
  //              %apriori stats. The pulse contained in the waveform's ps_pos
  //              %property is not used directly so that the caller can decide
  //              %which pulses on which to focus the posteriori.
  //
  //              t_found    = [pulselist(:).t_0]';
  //              freq_found = mean([pulselist(:).fp],'omitnan');
  //
  //              %Create a vector of bandwidths from the pulselist
  //              bw_found =
  //              2*(mean([pulselist.fend],'omitnan')-mean([pulselist.fstart],'omitnan'));
  //              if isempty(bw_found)
  //                  bw_found = 100;
  //                  if coder.target('MATLAB')
  //                      warning(['UAV-R: No bandwidth could be calculated
  //                      ',...
  //                           'from the start and stop frequencies of the ',...
  //                           'identified pulses. A bandwidth of 100 Hz ',...
  //                           'will be used for continued informed search.'])
  //                  end
  //              end
  //
  //              %Here is where we update the stats. These methods of updates
  //              %could be improved in the future.
  //              %obj.ps_pre.t_p; %tp doesn't change. We assume it is
  //              stationary
  //
  //              if numel(pulselist)==1% Happens if K=1
  //                  %We only have one pulse to reference, so we need to check
  //                  %the prior pulse too.
  //                  if ~isempty(obj.ps_pre.pl) &&
  //                  ~isnan(obj.ps_pre.pl(end).t_0)
  //                      recent_tip = pulselist.t_0-obj.ps_pre.pl(end).t_0;
  //                      %There could be a case where the last segment and this
  //                      %segement identified the same pulse. In this case
  //                      %recent_tip will be very small. In this case, we just
  //                      %say we learned nothing about t_ip in this segment.
  //                      if recent_tip < obj.ps_pre.t_ipu + obj.ps_pre.t_ipJ
  //                          recent_tip = NaN;
  //                      end
  //                  else
  //                      %No new information because we don't know the last
  //                      %pulse time
  //                      recent_tip = NaN;
  //                  end
  //              else
  //                  recent_tip = diff(t_found);
  //              end
  //              %Do a check here to make sure the new tip isn't a huge change.
  //              %This could potentially happen if we are in the K = 1 case and
  //              %the block getting processed contained two pulses, with the
  //              %latter pulse getting identified/detected. The lines above
  //              %would look back to the last identified pulse and it might be
  //              %2*tip back in time, producing a very large recenttip values.
  //              %If something like this happens, we ignore it so it doesn't
  //              %affect our new tip estimates.
  //              if recent_tip > 1.5*obj.ps_pre.t_ip & recent_tip <
  //              0.5*obj.ps_pre.t_ip
  //                  recent_tip = NaN;
  //              end
  //
  //              %Only update time parameters if we are in tracking mode. If we
  //              %aren't, we may have identified somethign that isn't a pulse
  //              if strcmp(obj.ps_pos.mode,'T') || strcmp(obj.ps_pre.mode,'T')
  //                  obj.ps_pos.t_ip  =
  //                  mean([recent_tip;obj.ps_pre.t_ip],'omitnan');
  //                  obj.ps_pos.t_ipu = obj.ps_pre.t_ipu; %Don't update this
  //                  because it can get too
  //                  narrow.%mean([3*std(diff(t_found));obj.ps_pre.t_ipu]);
  //                  obj.ps_pos.t_ipj = obj.ps_pre.t_ipj;
  //              end
  //              fp_pos           =
  //              freq_found;%nanmean([freq_found;obj.ps_pre.fp]);%Previous fc
  //              may be nan if unknown obj.ps_pos.fp    = fp_pos;
  //              obj.ps_pos.fstart = fp_pos-bw_found/2;
  //              obj.ps_pos.fend   = fp_pos+bw_found/2;
  //
  //              obj.ps_pos.psdHist = obj.stft.psd
  //          end
  b_n_p = ps_obj->t_p * Fs;
  b_n_p = std::ceil(b_n_p);
  // Samples per pulse
  // Number of elements in STFT window
  b_n_ol = OLF * b_n_p;
  b_n_ol = std::floor(b_n_ol);
  // Number of elements overlap in STFT window
  b_n_ws = b_n_p - b_n_ol;
  // Number of elements in each step of STFT
  val = b_n_ws / Fs;
  // Time of each step of STFT
  b_n_ip = ps_obj->t_ip * Fs;
  b_n_ip = std::ceil(b_n_ip);
  n_ipu = ps_obj->t_ipu * Fs;
  n_ipu = std::ceil(n_ipu);
  n_ipj = ps_obj->t_ipj * Fs;
  n_ipj = std::ceil(n_ipj);
  b_N = std::floor(b_n_ip / b_n_ws);
  b_M = std::ceil(n_ipu / b_n_ws);
  n_ipj = std::ceil(n_ipj / b_n_ws);
  n_p = b_n_p;
  // Samples per pulse
  n_w = b_n_p;
  // Number of elements in STFT window
  n_ol = b_n_ol;
  // Number of elements overlap in STFT window
  n_ws = b_n_ws;
  // Number of elements in each step of STFT
  t_ws = val;
  // Time of each step of STFT
  n_ip = b_n_ip;
  // Samples of interpulse duration
  N = b_N;
  // Baseline interpulse duration in units of STFT windows
  M = b_M;
  // Interpulse duration deviation from baselines in units of STFT windows
  J = n_ipj;
  // Amount of deviation from the PRI means to search
  n_ipu = K;
  //              if K ~= 1
  //                  samplesforKpulses = n_ws*(K*(N+M)-2*M)+n_ol;
  //              else
  //                  samplesforKpulses = n_ws*(N+M+J+1)+n_ol;
  //              end
  // See 2022-07-11 for updates to samples def
  // obj.t_nextsegstart  = obj.t_0+(samplesforKpulses)/obj.Fs; %Don't need the
  // overlap here since the next segment starts at samplesforKpulses+n_ol-n_ol
  // from current sample
  n_ipu = t_0 + ((b_n_ws * ((n_ipu * (b_N + b_M) + n_ipj) + 1.0) + b_n_ol) -
                 b_n_ws * (2.0 * (n_ipu * b_M + n_ipj))) /
                    Fs;
  t_nextsegstart[0] = n_ipu;
  t_nextsegstart[1] = n_ipu;
  // Don't need the overlap here since the next segment starts at
  // samplesforKpulses+n_ol-n_ol from current sample
  //              if isempty(obj.TimeCorr)
  //                  obj.TimeCorr = TemporalCorrelator(N, M, J);
  //              else
  //                  obj.TimeCorr.update(N, M, J);
  //              end
}

//
// SETWEIGHTINGMATRIX method sets the W and Wf properties of
// the waveform. These are the weighting matrix and the
// frequencys (Wf) at which they are computed.
// INPUTS:
//    none
// OUTPUTS:
//    none other than setting obj.Wf and obj.W
// ----------------------------------------------------------
//
// Here we build the spectral scaling vector. We make it the same
// size as the FFT length in the STFT operation, so it has the
// same frequency resolution.
// How many frequency bins are there?
//
// Arguments    : void
// Return Type  : void
//
void waveform::setweightingmatrix()
{
  static rtBoundsCheckInfo f_emlrtBCI{
      -1,                                              // iFirst
      -1,                                              // iLast
      202,                                             // lineNo
      9,                                               // colNo
      "W",                                             // aName
      "weightingmatrix",                               // fName
      "H:\\repos\\uavrt_detection\\weightingmatrix.m", // pName
      0                                                // checkKind
  };
  static rtBoundsCheckInfo g_emlrtBCI{
      -1,                                              // iFirst
      -1,                                              // iLast
      192,                                             // lineNo
      33,                                              // colNo
      "freqs",                                         // aName
      "weightingmatrix",                               // fName
      "H:\\repos\\uavrt_detection\\weightingmatrix.m", // pName
      0                                                // checkKind
  };
  static rtDoubleCheckInfo b_emlrtDCI{
      194,                                             // lineNo
      48,                                              // colNo
      "weightingmatrix",                               // fName
      "H:\\repos\\uavrt_detection\\weightingmatrix.m", // pName
      4                                                // checkKind
  };
  static rtDoubleCheckInfo c_emlrtDCI{
      194,                                             // lineNo
      55,                                              // colNo
      "weightingmatrix",                               // fName
      "H:\\repos\\uavrt_detection\\weightingmatrix.m", // pName
      4                                                // checkKind
  };
  static rtDoubleCheckInfo d_emlrtDCI{
      193,                                             // lineNo
      24,                                              // colNo
      "weightingmatrix",                               // fName
      "H:\\repos\\uavrt_detection\\weightingmatrix.m", // pName
      4                                                // checkKind
  };
  static rtDoubleCheckInfo e_emlrtDCI{
      43,                                          // lineNo
      28,                                          // colNo
      "gettemplate",                               // fName
      "H:\\repos\\uavrt_detection\\gettemplate.m", // pName
      4                                            // checkKind
  };
  static rtEqualityCheckInfo c_emlrtECI{
      -1,                                             // nDims
      191,                                            // lineNo
      1,                                              // colNo
      "weightingmatrix",                              // fName
      "H:\\repos\\uavrt_detection\\weightingmatrix.m" // pName
  };
  static rtEqualityCheckInfo d_emlrtECI{
      1,                                              // nDims
      195,                                            // lineNo
      6,                                              // colNo
      "weightingmatrix",                              // fName
      "H:\\repos\\uavrt_detection\\weightingmatrix.m" // pName
  };
  static rtRunTimeErrorInfo kb_emlrtRTEI{
      33,        // lineNo
      "linspace" // fName
  };
  static rtRunTimeErrorInfo lb_emlrtRTEI{
      206,           // lineNo
      "interp1_work" // fName
  };
  coder::array<creal_T, 2U> b_tmp_data;
  coder::array<creal_T, 2U> c_tmp_data;
  coder::array<double, 1U> b_Wf_data;
  coder::array<signed char, 2U> y;
  coder::array<boolean_T, 2U> c_w_time_domain_data;
  creal_T tmp_data;
  double Wf_data;
  double b_x;
  double tmplt_samps_idx_0;
  double tmplt_samps_idx_1;
  double w_time_domain_data;
  int ii_size[2];
  int output_samps_size[2];
  int w_time_domain_size[2];
  int i;
  int iidx_data;
  int iidx_size;
  int loop_ub;
  int nx;
  int varargin_2;
  signed char x_of_n_size_idx_0;
  boolean_T b_w_time_domain_data;
  if (stft->f.size(0) == 0) {
    b_rtErrorWithMessageID(b_emlrtRTEI.fName, b_emlrtRTEI.lineNo);
  }
  nx = stft->f.size(0);
  // Build a pulse time domain template with the same number
  // of samples as frequency bins:
  // GETTEMPLATE Generates a time domain template of the the signal template in
  // the priori pulsestats object in the waveform passed to the function. The
  // returned vector is the template at the waveform's sample rate. The
  // caller can request a total number of samples greater than the samples
  // required to describe the signal. This is useful if the call will be using
  // a DFT on the result and wants a specific number of samples to ensure a
  // particular frequency resolutions.
  //
  // INPUTS:
  //    X       A waveform object with a populated ps_pre property
  //    samples The number of sample desired in the output. Must be greater
  //            than or equal to ceil(X.ps_pre.t_p*X.Fs)
  //
  // OUTPUTS:
  //    sig_template    A vector of the signal amplitude over the samples
  //                    requested at the sample rate of the input waveform.
  //
  // Author: Michael W. Shafer
  // Date:   2021-05-21
  //
  // Sort out the samples input, if submitted by the caller
  b_x = ps_pre->t_p * Fs;
  b_x = std::ceil(b_x);
  if (nx < b_x) {
    b_rtErrorWithMessageID(b_emlrtRTEI.fName, b_emlrtRTEI.lineNo);
  }
  // Generates a the template in the time domain at the sample rate of the
  // waveform.
  b_x = Fs * ps_pre->t_p;
  tmplt_samps_idx_1 = std::ceil(b_x);
  tmplt_samps_idx_0 = 0.0;
  b_x = ps_pre->t_p * Fs;
  b_x = std::ceil(b_x);
  if (!(b_x >= 0.0)) {
    if (std::isnan(b_x)) {
      l_rtErrorWithMessageID("N", kb_emlrtRTEI.fName, kb_emlrtRTEI.lineNo);
    }
    output_samps_size[1] = 0;
  } else {
    output_samps_size[1] = static_cast<int>(b_x);
  }
  if (output_samps_size[1] != 0) {
    if (tmplt_samps_idx_1 < 0.0) {
      tmplt_samps_idx_0 = tmplt_samps_idx_1;
      tmplt_samps_idx_1 = 0.0;
    }
    if (tmplt_samps_idx_1 <= tmplt_samps_idx_0) {
      cb_rtErrorWithMessageID(lb_emlrtRTEI.fName, lb_emlrtRTEI.lineNo);
    }
  }
  // Generate the extra-zeros needed to pad to get to 'samples' samples
  i = nx - output_samps_size[1];
  if (i < 0) {
    rtNonNegativeError(-1.0, &e_emlrtDCI);
  }
  // Build a rectagular waveform in the time domain with the same number of
  // samples as frequency bins t = (0:numel(sig_template)-1)/X.Fs; A vector of
  // times associated with the output template. Useful for plotting in the time
  // domain. Build weighting matrix
  tmplt_samps_idx_0 = Fs;
  // WEIGHTINGMATRIX Builds the spectral weighting matrix for the incoherent
  // summationation algorithm. The matrix is based on the DFT coefficients
  // developed from the waveform passed to the function. The function first
  // developeds a weighting vectors based on an unaltered waveform, but then
  // shifts the waveforms spectral content base fractions of the DFT bin width,
  // as defined by the zetas input. These shifted waveforms then have their
  // DFT's computed. The original and shifted DFT coefficients are then aligned
  // in a matrix. In this way, this weighting matrix allows for the dominant
  // frequency in the vector it weights to be between bins. This submatrix is
  // then row shifted and concantinated a number of times so that the DFT
  // coefficients are shifted across all DFT frequency bins. The outputs are
  // the weighting matrix W and a frequency vector Wf that corresponds to the
  // rows of W. The frequencies, and therefore the rows of the W matrix, use a
  // centered frequency definitions defined by the STFT.m algorithm.
  //
  //    Example:   [W,Wf] = weightingmatrix(rand(1,10),1,[0 0.5])
  //
  //    INPUTS:
  //    x_of_n      nx1     Vector of discrete data sampled as Fs. Can be 1xn.
  //    Fs          1x1     Sampling rate in Hz of the dataset
  //    zetas       mx1     A vector of fractions of the DFT frequency bin
  //                        width for which to compute and include in the
  //                        spectral weighting matrix output. If no interbin
  //                        shifting is desired, enter 0. Range of inputs
  //                        [0,1).
  //    frequencyRangeType  String of either 'centered' or 'twosided'. See
  //                        stft.m documentation on details of these frequency
  //                        bounds. If 'centered' is selected, the zero
  //                        frequency point is near the center of the output
  //                        matrix. If 'twosided' is selected, the zero
  //                        frequency points is in the upper left corner of the
  //                        output W matrix.
  //
  //    OUTPUTS:
  //    W           nxnm    A matrix of spectral weighting vectors along each
  //                        column. The hermitian of this matrix is designed to
  //                        be multiplied by a vector of DFT coefficients. The
  //                        weights held in column p can be thought of as the
  //                        matched DFT coefficients if the signal were to have
  //                        been shifted by the template by Wf(p).
  //    Wf          nmx1    A matrix of the frequency shifts corresponding to
  //                        each column of W
  //
  //  The intended use of the W matrix is to multiply it's hermetian by a FFT
  //  vector, or STFT matrix with frequencies in the rows.
  //
  //
  //    [W^h]*S         or          [W^h]*FFT
  //
  //  The outputs of this multiplication will have n*m rows. The rows of the
  //  result there for are the "scores" of at frequency associated with that
  //  row. The row frequencies are dependent on the zetas. Consider an input
  //  series that had frequencies [-100 0 100 200]. If the zeta input was
  //  [0 0.5], weightings for full and half frequencies steps would be
  //  developed.
  //
  //        output freq     input freq
  //                            -100    0   100     200
  //                -150    [                           ]
  //                -100    [                           ]
  //                -50     [                           ]
  //                0       [            W^h            ]
  //                50      [                           ]
  //                100     [                           ]
  //                150     [                           ]
  //                200     [                           ]
  //
  //    The first row of the matrix above would contain the weightings for the
  //    -100 0 100 and 200 Hz frequencie bins if the FFT (or STFT time window)
  //    had a signal at -150 Hz. Similarly, the second row would contain the
  //    weightings for the -100 0 100 and 200 Hz frequencie bins if the FFT
  //    (or STFT time window) had a signal at -100 Hz.
  //
  // Author: Michael Shafer
  // Date:   2020-12-19
  //
  //  Change Log
  //  2022-01-12    Updated to include twosided frequency range for output and
  //                updated the code associated with generating the unsorted W
  //                matrix to increase speed. Added use of makestftFreqVector
  //                function.
  //
  // Check the inputs
  // Reshape to a column vector, as the algorithm expects
  x_of_n_size_idx_0 = static_cast<signed char>(
      static_cast<signed char>(output_samps_size[1]) + i == 1);
  // F_bin_width = Fs/nw;
  // Use complex so when implementing in simulink later, it knows this is a
  // complex vector.
  // Develop a vector of frequencies that would result from the centered method
  // of the STFT function if it were computed on the x input. This is useful
  // for debugging the frequency outputs.
  // These are designed to develop the same freqs as the STFT centered method
  // Check the "'FrequencyRange' — STFT frequency range" in the STFT help file
  // if mod(nw,2)==0
  //     freqs_orig = ((-nw/2+1):nw/2)*Fs/nw;
  // else
  //     freqs_orig = (ceil(-nw/2):floor(nw/2))*Fs/nw;
  // end
  // figure;
  // ylabel('|Xs|');xlabel('Frequency');legend('Location',"best");
  // title('DFT of primary frequency shifts of the template')
  // New W generation method. ~25% faster on average
  varargin_2 = x_of_n_size_idx_0 << 1;
  // Reshape in this way will interweave rows of each sub matrix of the stack
  nx = varargin_2 * x_of_n_size_idx_0;
  if (x_of_n_size_idx_0 > nx) {
    l_rtErrorWithMessageID(m_emlrtRTEI.fName, m_emlrtRTEI.lineNo);
  }
  if (varargin_2 > nx) {
    l_rtErrorWithMessageID(m_emlrtRTEI.fName, m_emlrtRTEI.lineNo);
  }
  if (x_of_n_size_idx_0 * varargin_2 != nx) {
    m_rtErrorWithMessageID(n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
  }
  // OLD W generation method. Easier to understand, but slower
  //  W     = 1i*zeros(nw,numZetas*nw);
  //  freqs = zeros(1,numZetas*nw);
  //  for i = 1:nw
  //      W(:,(i-1)*numZetas+(1:numZetas))=...
  //          circshift(Xs,i-1,1);
  //  end
  // Build a vector of the frequencies
  //   tick=1;
  //   for i = 1:numZetas:size(W,2)
  //       freqs(i:i+(numZetas-1)) = Fs/nw*((tick-1)+zetas);
  //       tick = tick+1;
  //   end
  nx = varargin_2 - 1;
  // MAKESTFTFREQVECTOR Generates the frequency vector based on the frequency
  // range specification for Matlab's stft.m 'FrequencyRange' input standard,
  //
  //    This function outputs a frequency vector based on the frequency
  //    range specification for Matlab's stft.m 'FrequencyRange' input
  //    standard. The options for the frequency ranges are 'centered'
  //    (default), 'twosided', and 'onesided'. The sftf.m documentation
  //    standard states:
  //        STFT frequency range, specified as 'centered', 'twosided', or
  //        'onesided'.
  //
  //        'centered' — Compute a two-sided, centered STFT. If 'FFTLength' is
  //        even, then s is computed over the interval (–π, π] rad/sample. If
  //        'FFTLength' is odd, then s is computed over the interval (–π, π)
  //        rad/sample. If you specify time information, then the intervals are
  //         (–fs, fs/2] cycles/unit time and (–fs, fs/2) cycles/unit time,
  //        respectively, where fs is the effective sample rate.
  //
  //        'twosided' — Compute a two-sided STFT over the interval [0, 2π)
  //        rad/sample. If you specify time information, then the interval is
  //        [0, fs) cycles/unit time.
  //
  //        'onesided' — Compute a one-sided STFT. If 'FFTLength' is even,
  //        then s is computed over the interval [0, π] rad/sample. If
  //        'FFTLength' is odd, then s is computed over the interval [0, π)
  //        rad/sample. If you specify time information, then the intervals are
  //         [0, fs/2] cycles/unit time and [0, fs/2) cycles/unit time,
  //        respectively, where fs is the effective sample rate. This option is
  //         valid only for real signals.
  //
  //    If Fs is not specificed, outputs will be in rad/sample with pi as
  //    specified in the stft.m frequency range standard.
  //
  // INPUTS:
  //    nfft                 Length of FFT performed on the STFT.
  //    frequencyRangeType   String containing 'centered', 'twosided',
  //    'onesided' Fs                   Sample rate of data
  //
  // OUTPUTS:
  //    freqs       Vector of frequencies at which the STFT is calculated
  //
  // Author:    Michael Shafer
  // Date:      2022-01-11
  //
  if (varargin_2 - 1 < 0) {
    y.set_size(1, 0);
  } else {
    y.set_size(1, varargin_2);
    for (i = 0; i <= nx; i++) {
      y[i] = static_cast<signed char>(i);
    }
  }
  w_time_domain_size[0] = 1;
  w_time_domain_size[1] = y.size(1);
  loop_ub = y.size(1);
  for (i = 0; i < loop_ub; i++) {
    w_time_domain_data = static_cast<double>(y[i]) * tmplt_samps_idx_0 /
                         static_cast<double>(varargin_2);
  }
  // Simulink (coder?) didn't like the new round inputs
  // freqs = round(freqs,3);
  // freqs = round(freqs*1000)/1000;
  // Shift everything so we use a negative frequencies
  // A little non-matlab notation to get this to run in simulink.
  // nyq_ind(1)  = find(freqs == floor(Fs/2),1,'first');
  b_x = tmplt_samps_idx_0 / 2.0;
  loop_ub = w_time_domain_size[1];
  for (i = 0; i < loop_ub; i++) {
    b_w_time_domain_data = (w_time_domain_data == b_x);
  }
  c_w_time_domain_data.set(&b_w_time_domain_data, 1, w_time_domain_size[1]);
  coder::eml_find(c_w_time_domain_data, (int *)&nx, ii_size);
  loop_ub = ii_size[1];
  for (i = 0; i < loop_ub; i++) {
    tmplt_samps_idx_1 = nx;
  }
  if (ii_size[1] != 1) {
    rtSizeEq1DError(1, 0, &c_emlrtECI);
  }
  nx = static_cast<int>(tmplt_samps_idx_1);
  if (w_time_domain_size[1] < 1) {
    rtDynamicBoundsError(w_time_domain_size[1], 1, w_time_domain_size[1],
                         &g_emlrtBCI);
  }
  b_x = -w_time_domain_data - (tmplt_samps_idx_0 - w_time_domain_data);
  if (nx < 0) {
    rtNonNegativeError(static_cast<double>(nx), &d_emlrtDCI);
  }
  y.set_size(1, y.size(1));
  loop_ub = w_time_domain_size[1] - nx;
  if (loop_ub < 0) {
    rtNonNegativeError(static_cast<double>(loop_ub), &c_emlrtDCI);
  }
  y.set_size(y.size(0), loop_ub);
  if (loop_ub < 0) {
    rtNonNegativeError(static_cast<double>(loop_ub), &b_emlrtDCI);
  }
  for (i = 0; i < loop_ub; i++) {
    y[i] = 1;
  }
  output_samps_size[0] = 1;
  output_samps_size[1] = nx + y.size(1);
  for (i = 0; i < nx; i++) {
    tmplt_samps_idx_1 = 0.0;
  }
  loop_ub = y.size(1);
  for (i = 0; i < loop_ub; i++) {
    tmplt_samps_idx_1 = b_x;
  }
  if ((output_samps_size[1] != w_time_domain_size[1]) &&
      ((output_samps_size[1] != 1) && (w_time_domain_size[1] != 1))) {
    emlrtDimSizeImpxCheckR2021b(output_samps_size[1], 0, &d_emlrtECI);
  }
  // Here we sort the output to set up to have an ascending order of frequency
  // to be similar to the centered frequency list used elsewhere in the
  // codebase for the STFT output.
  if (output_samps_size[1] == w_time_domain_size[1]) {
    nx = output_samps_size[1];
    loop_ub = output_samps_size[1];
    for (i = 0; i < loop_ub; i++) {
      Wf_data = tmplt_samps_idx_1 + w_time_domain_data;
    }
  } else {
    binary_expand_op((double *)&Wf_data, &nx,
                     (const double *)&tmplt_samps_idx_1, output_samps_size,
                     (const double *)&w_time_domain_data, w_time_domain_size);
  }
  iidx_size = coder::internal::sort(&nx);
  loop_ub = x_of_n_size_idx_0;
  for (i = 0; i < iidx_size; i++) {
    for (int i1{0}; i1 < loop_ub; i1++) {
      if ((iidx_data < 1) || (iidx_data > varargin_2)) {
        rtDynamicBoundsError(iidx_data, 1, varargin_2, &f_emlrtBCI);
      }
      tmp_data.re = 0.0;
      tmp_data.im = 0.0;
    }
  }
  b_tmp_data.set(&tmp_data, static_cast<int>(x_of_n_size_idx_0), iidx_size);
  coder::internal::validator_check_size(b_tmp_data, c_tmp_data);
  W.set_size(0, 0);
  b_Wf_data.set(&Wf_data, nx);
  coder::internal::validator_check_size(b_Wf_data, Wf);
}

//
// SPECTRO Executes an STFT of x and sets up the wfmstst object
// for the waveform
//
// INPUTS:
//    obj     The waveform object
// OUTPUTS:
//    none
//
//             %%
//
// Arguments    : wfmstft *iobj_0
// Return Type  : void
//
void b_waveform::spectro(wfmstft *iobj_0)
{
  coder::array<creal_T, 2U> b_S;
  coder::array<creal_T, 2U> r;
  coder::array<creal_T, 2U> val;
  coder::array<creal32_T, 2U> S;
  coder::array<creal32_T, 2U> obj;
  coder::array<double, 1U> _in;
  coder::array<double, 1U> b__in;
  coder::array<double, 1U> b_tmp_data;
  coder::array<double, 1U> d_tmp_data;
  coder::array<double, 1U> e_tmp_data;
  coder::array<double, 1U> f_tmp_data;
  coder::array<float, 1U> local_time;
  coder::array<float, 1U> r1;
  double tmp_data[2000];
  double c_tmp_data[200];
  double n_est;
  int loop_ub;
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
  r.set(nullptr, 0, 0);
  coder::internal::validator_check_size(r, val);
  iobj_0->S.set_size(val.size(0), val.size(1));
  loop_ub = val.size(0) * val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    iobj_0->S[i] = val[i];
  }
  b_tmp_data.set(&tmp_data[0], 0);
  coder::internal::validator_check_size(b_tmp_data, _in);
  iobj_0->t.set_size(_in.size(0));
  loop_ub = _in.size(0);
  for (int i{0}; i < loop_ub; i++) {
    iobj_0->t[i] = _in[i];
  }
  d_tmp_data.set(&c_tmp_data[0], 0);
  coder::internal::validator_check_size(d_tmp_data, _in);
  iobj_0->f.set_size(_in.size(0));
  loop_ub = _in.size(0);
  for (int i{0}; i < loop_ub; i++) {
    iobj_0->f[i] = _in[i];
  }
  e_tmp_data.set(&c_tmp_data[0], 0);
  coder::internal::validator_check_size(e_tmp_data, _in);
  iobj_0->psd.set_size(_in.size(0));
  loop_ub = _in.size(0);
  for (int i{0}; i < loop_ub; i++) {
    iobj_0->psd[i] = _in[i];
  }
  f_tmp_data.set(&c_tmp_data[0], 0);
  coder::internal::validator_check_size(f_tmp_data, _in);
  iobj_0->wind.set_size(_in.size(0));
  loop_ub = _in.size(0);
  for (int i{0}; i < loop_ub; i++) {
    iobj_0->wind[i] = _in[i];
  }
  iobj_0->dt = 0.0;
  iobj_0->T = 0.0;
  // wind = hann(waveform_obj.n_w,'periodic');
  // wind = tukeywin(waveform_obj.n_w,0.3);
  n_est = n_w;
  if (std::isinf(n_est) || std::isnan(n_est)) {
    f_rtErrorWithMessageID("N", y_emlrtRTEI.fName, y_emlrtRTEI.lineNo);
  }
  if (!(n_est >= 0.0)) {
    r_rtErrorWithMessageID(ab_emlrtRTEI.fName, ab_emlrtRTEI.lineNo);
  }
  if (n_est == std::floor(n_est)) {
    loop_ub = static_cast<int>(n_est);
  } else {
    loop_ub = static_cast<int>(std::round(n_est));
  }
  _in.set_size(loop_ub);
  for (int i{0}; i < loop_ub; i++) {
    _in[i] = 1.0;
  }
  b__in.set_size(_in.size(0));
  loop_ub = _in.size(0) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    b__in[i] = _in[i];
  }
  coder::internal::validator_check_size(b__in, _in);
  iobj_0->wind.set_size(_in.size(0));
  loop_ub = _in.size(0);
  for (int i{0}; i < loop_ub; i++) {
    iobj_0->wind[i] = _in[i];
  }
  obj.set_size(1, x.size(1));
  loop_ub = x.size(0) * x.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    obj[i] = x[i];
  }
  b__in.set_size(iobj_0->wind.size(0));
  loop_ub = iobj_0->wind.size(0) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    b__in[i] = iobj_0->wind[i];
  }
  ::coder::stft(obj, Fs, b__in, n_ol, n_w, S, r1, local_time);
  b__in.set_size(r1.size(0));
  loop_ub = r1.size(0);
  for (int i{0}; i < loop_ub; i++) {
    b__in[i] = r1[i];
  }
  coder::internal::validator_check_size(b__in, _in);
  iobj_0->f.set_size(_in.size(0));
  loop_ub = _in.size(0);
  for (int i{0}; i < loop_ub; i++) {
    iobj_0->f[i] = _in[i];
  }
  b_S.set_size(S.size(0), S.size(1));
  loop_ub = S.size(0) * S.size(1);
  for (int i{0}; i < loop_ub; i++) {
    b_S[i].re = S[i].re;
    b_S[i].im = S[i].im;
  }
  coder::internal::validator_check_size(b_S, val);
  iobj_0->S.set_size(val.size(0), val.size(1));
  loop_ub = val.size(0) * val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    iobj_0->S[i] = val[i];
  }
  //  Incoming x data in waveform is single precision, but sparse matrix
  //  multipliation later is only supported for double precision.
  _in.set_size(local_time.size(0));
  loop_ub = local_time.size(0);
  for (int i{0}; i < loop_ub; i++) {
    _in[i] = local_time[i] + t_0;
  }
  b__in.set_size(_in.size(0));
  loop_ub = _in.size(0) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    b__in[i] = _in[i];
  }
  coder::internal::validator_check_size(b__in, _in);
  iobj_0->t.set_size(_in.size(0));
  loop_ub = _in.size(0);
  for (int i{0}; i < loop_ub; i++) {
    iobj_0->t[i] = _in[i];
  }
  // Convert to global time of waveform. Double cast is needed because if x data
  // in stft is single precision then the output t will be single as well.
  n_est = 1.0 / Fs;
  iobj_0->dt = n_est;
  n_est = n_w / Fs;
  iobj_0->T = n_est;
  iobj_0->updatepsd();
  // obj.psd = obj.dt^2/obj.T*mean(abs(obj.S).^2,2);% Sxx = dt^2/T*|xhat(f)|^2
  // Vestigial properties no longer used. Kept in case we want
  // to resurect them.
  // obj.wind_per_pulse = floor(waveform_obj.n_w/waveform_obj.n_p); %How many
  // windows are needed to capture a pulse obj.stft_steps_per_pulse =
  // floor(waveform_obj.t_ws/waveform_obj.ps_pre.t_p);%How many stft steps are
  // needed to capture a pulse
  stft = iobj_0;
}

//
// SPECTRO Executes an STFT of x and sets up the wfmstst object
// for the waveform
//
// INPUTS:
//    obj     The waveform object
// OUTPUTS:
//    none
//
//             %%
//
// Arguments    : wfmstft *iobj_0
// Return Type  : void
//
void waveform::spectro(wfmstft *iobj_0)
{
  coder::array<creal_T, 2U> b_S;
  coder::array<creal_T, 2U> r;
  coder::array<creal_T, 2U> val;
  coder::array<creal32_T, 2U> S;
  coder::array<creal32_T, 2U> obj;
  coder::array<double, 1U> _in;
  coder::array<double, 1U> b__in;
  coder::array<double, 1U> b_tmp_data;
  coder::array<double, 1U> d_tmp_data;
  coder::array<double, 1U> e_tmp_data;
  coder::array<double, 1U> f_tmp_data;
  coder::array<float, 1U> local_time;
  coder::array<float, 1U> r1;
  double tmp_data[2000];
  double c_tmp_data[200];
  double n_est;
  int loop_ub;
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
  r.set(nullptr, 0, 0);
  coder::internal::validator_check_size(r, val);
  iobj_0->S.set_size(val.size(0), val.size(1));
  loop_ub = val.size(0) * val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    iobj_0->S[i] = val[i];
  }
  b_tmp_data.set(&tmp_data[0], 0);
  coder::internal::validator_check_size(b_tmp_data, _in);
  iobj_0->t.set_size(_in.size(0));
  loop_ub = _in.size(0);
  for (int i{0}; i < loop_ub; i++) {
    iobj_0->t[i] = _in[i];
  }
  d_tmp_data.set(&c_tmp_data[0], 0);
  coder::internal::validator_check_size(d_tmp_data, _in);
  iobj_0->f.set_size(_in.size(0));
  loop_ub = _in.size(0);
  for (int i{0}; i < loop_ub; i++) {
    iobj_0->f[i] = _in[i];
  }
  e_tmp_data.set(&c_tmp_data[0], 0);
  coder::internal::validator_check_size(e_tmp_data, _in);
  iobj_0->psd.set_size(_in.size(0));
  loop_ub = _in.size(0);
  for (int i{0}; i < loop_ub; i++) {
    iobj_0->psd[i] = _in[i];
  }
  f_tmp_data.set(&c_tmp_data[0], 0);
  coder::internal::validator_check_size(f_tmp_data, _in);
  iobj_0->wind.set_size(_in.size(0));
  loop_ub = _in.size(0);
  for (int i{0}; i < loop_ub; i++) {
    iobj_0->wind[i] = _in[i];
  }
  iobj_0->dt = 0.0;
  iobj_0->T = 0.0;
  // wind = hann(waveform_obj.n_w,'periodic');
  // wind = tukeywin(waveform_obj.n_w,0.3);
  n_est = n_w;
  if (std::isinf(n_est) || std::isnan(n_est)) {
    f_rtErrorWithMessageID("N", y_emlrtRTEI.fName, y_emlrtRTEI.lineNo);
  }
  if (!(n_est >= 0.0)) {
    r_rtErrorWithMessageID(ab_emlrtRTEI.fName, ab_emlrtRTEI.lineNo);
  }
  if (n_est == std::floor(n_est)) {
    loop_ub = static_cast<int>(n_est);
  } else {
    loop_ub = static_cast<int>(std::round(n_est));
  }
  _in.set_size(loop_ub);
  for (int i{0}; i < loop_ub; i++) {
    _in[i] = 1.0;
  }
  b__in.set_size(_in.size(0));
  loop_ub = _in.size(0) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    b__in[i] = _in[i];
  }
  coder::internal::validator_check_size(b__in, _in);
  iobj_0->wind.set_size(_in.size(0));
  loop_ub = _in.size(0);
  for (int i{0}; i < loop_ub; i++) {
    iobj_0->wind[i] = _in[i];
  }
  obj.set_size(1, x.size(1));
  loop_ub = x.size(0) * x.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    obj[i] = x[i];
  }
  b__in.set_size(iobj_0->wind.size(0));
  loop_ub = iobj_0->wind.size(0) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    b__in[i] = iobj_0->wind[i];
  }
  ::coder::stft(obj, Fs, b__in, n_ol, n_w, S, r1, local_time);
  b__in.set_size(r1.size(0));
  loop_ub = r1.size(0);
  for (int i{0}; i < loop_ub; i++) {
    b__in[i] = r1[i];
  }
  coder::internal::validator_check_size(b__in, _in);
  iobj_0->f.set_size(_in.size(0));
  loop_ub = _in.size(0);
  for (int i{0}; i < loop_ub; i++) {
    iobj_0->f[i] = _in[i];
  }
  b_S.set_size(S.size(0), S.size(1));
  loop_ub = S.size(0) * S.size(1);
  for (int i{0}; i < loop_ub; i++) {
    b_S[i].re = S[i].re;
    b_S[i].im = S[i].im;
  }
  coder::internal::validator_check_size(b_S, val);
  iobj_0->S.set_size(val.size(0), val.size(1));
  loop_ub = val.size(0) * val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    iobj_0->S[i] = val[i];
  }
  //  Incoming x data in waveform is single precision, but sparse matrix
  //  multipliation later is only supported for double precision.
  _in.set_size(local_time.size(0));
  loop_ub = local_time.size(0);
  for (int i{0}; i < loop_ub; i++) {
    _in[i] = local_time[i] + t_0;
  }
  b__in.set_size(_in.size(0));
  loop_ub = _in.size(0) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    b__in[i] = _in[i];
  }
  coder::internal::validator_check_size(b__in, _in);
  iobj_0->t.set_size(_in.size(0));
  loop_ub = _in.size(0);
  for (int i{0}; i < loop_ub; i++) {
    iobj_0->t[i] = _in[i];
  }
  // Convert to global time of waveform. Double cast is needed because if x data
  // in stft is single precision then the output t will be single as well.
  n_est = 1.0 / Fs;
  iobj_0->dt = n_est;
  n_est = n_w / Fs;
  iobj_0->T = n_est;
  iobj_0->updatepsd();
  // obj.psd = obj.dt^2/obj.T*mean(abs(obj.S).^2,2);% Sxx = dt^2/T*|xhat(f)|^2
  // Vestigial properties no longer used. Kept in case we want
  // to resurect them.
  // obj.wind_per_pulse = floor(waveform_obj.n_w/waveform_obj.n_p); %How many
  // windows are needed to capture a pulse obj.stft_steps_per_pulse =
  // floor(waveform_obj.t_ws/waveform_obj.ps_pre.t_p);%How many stft steps are
  // needed to capture a pulse
  stft = iobj_0;
}

//
// File trailer for waveform.cpp
//
// [EOF]
//
