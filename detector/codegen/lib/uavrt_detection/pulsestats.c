/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: pulsestats.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "pulsestats.h"
#include "blockedSummation.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * PULSESTATS Constructs an instance of this class
 *
 * INPUTS:
 *    tp      1x1     Duration of pulse (second)
 *    tip     1x1     Inter-pulse time (seconds)
 *    tipu    1x1     Inter-pulse time uncertainty (seconds)
 *    tipj    1x1     Inter-pulse time jitter (deviations from means) (seconds)
 *    fp      1x1     Pulses' center frequency (Hz) (if known)
 *    fstart  1x1     Lower frequency bound pulses' center frequency (Hz) (if
 * known) fend    1x1     Upper frequency bound pulses' center frequency (Hz)
 * (if known) tmplt   1xn     Pulse template. See properies for definition.
 * Usually set to [1 1] for square pulse. pl      px1     Vector of pulse
 * objects in waveform (if known). If unknown enter a blank pulse made from the
 * contstructor "pulse"; Note: Unknown inputs should be set to NaN.
 *
 * OUTPUTS:
 *    pulsestats object
 *
 *             %%
 *
 * Arguments    : pulsestats *obj
 *                double tp
 *                double tip
 *                double tipu
 *                double tipj
 *                double fp
 *                double fstart
 *                double fend
 *                const double tmplt[2]
 *                char mode
 *                const emxArray_struct_T *pl
 *                const emxArray_struct_T *clst
 *                const emxArray_boolean_T *cmsk
 *                const emxArray_real_T *cpki
 * Return Type  : pulsestats *
 */
pulsestats *b_pulsestats_pulsestats(
    pulsestats *obj, double tp, double tip, double tipu, double tipj, double fp,
    double fstart, double fend, const double tmplt[2], char mode,
    const emxArray_struct_T *pl, const emxArray_struct_T *clst,
    const emxArray_boolean_T *cmsk, const emxArray_real_T *cpki)
{
  const b_struct_T *clst_data;
  const b_struct_T *pl_data;
  b_struct_T *out_data;
  emxArray_boolean_T *c_out;
  emxArray_real_T *in;
  emxArray_struct_T *b_out;
  emxArray_struct_T *out;
  pulsestats *b_obj;
  const double *cpki_data;
  double *in_data;
  int i;
  int inVectorLength;
  const bool *cmsk_data;
  bool *b_out_data;
  cpki_data = cpki->data;
  cmsk_data = cmsk->data;
  clst_data = clst->data;
  pl_data = pl->data;
  b_obj = obj;
  b_obj->t_p = tp;
  b_obj->t_ip = tip;
  b_obj->t_ipu = tipu;
  b_obj->t_ipj = tipj;
  b_obj->fp = fp;
  b_obj->fstart = fstart;
  b_obj->fend = fend;
  b_obj->tmplt[0] = tmplt[0];
  b_obj->tmplt[1] = tmplt[1];
  b_obj->mode = mode;
  /* The following are variable sized properties. To tell coder */
  /* that they may vary setup as a local variable size variable */
  /* first, then set. */
  /* Instructions on
   * https://www.mathworks.com/help/simulink/ug/how-working-with-matlab-classes-is-different-for-code-generation.html
   */
  /* localMode = mode; */
  /* coder.varsize('localMode',[1 inf],[0 1]); %dims 0 if fixed, 1 if variable
   */
  /* Tell coder these are variable size. */
  /* Now actually assign them  */
  emxInit_struct_T(&out);
  inVectorLength = 1;
  if (pl->size[1] != 1) {
    inVectorLength = pl->size[1];
  }
  if (pl->size[1] == 1) {
    i = out->size[0] * out->size[1];
    out->size[0] = 1;
    out->size[1] = inVectorLength;
    emxEnsureCapacity_struct_T(out, i);
    out_data = out->data;
    for (i = 0; i < inVectorLength; i++) {
      emxCopyStruct_struct_T(&out_data[i], &pl_data[0]);
    }
  } else if (pl->size[1] == 0) {
    i = out->size[0] * out->size[1];
    out->size[0] = 1;
    out->size[1] = inVectorLength;
    emxEnsureCapacity_struct_T(out, i);
    out_data = out->data;
    for (i = 0; i < inVectorLength; i++) {
      emxCopyStruct_struct_T(&out_data[i], &pl_data[i]);
    }
  } else {
    i = out->size[0] * out->size[1];
    out->size[0] = 1;
    out->size[1] = inVectorLength;
    emxEnsureCapacity_struct_T(out, i);
    out_data = out->data;
    for (i = 0; i < inVectorLength; i++) {
      emxCopyStruct_struct_T(&out_data[i], &pl_data[i]);
    }
  }
  i = b_obj->pl->size[0] * b_obj->pl->size[1];
  b_obj->pl->size[0] = 1;
  b_obj->pl->size[1] = out->size[1];
  emxEnsureCapacity_struct_T(b_obj->pl, i);
  inVectorLength = out->size[1];
  for (i = 0; i < inVectorLength; i++) {
    emxCopyStruct_struct_T(&b_obj->pl->data[i], &out_data[i]);
  }
  emxFree_struct_T(&out);
  emxInit_struct_T(&b_out);
  if ((clst->size[0] == 1) && (clst->size[1] == 1)) {
    i = b_out->size[0] * b_out->size[1];
    b_out->size[0] = 1;
    b_out->size[1] = 1;
    emxEnsureCapacity_struct_T(b_out, i);
    out_data = b_out->data;
    emxCopyStruct_struct_T(&out_data[0], &clst_data[0]);
  } else if ((clst->size[0] == 0) || (clst->size[1] == 0)) {
    i = b_out->size[0] * b_out->size[1];
    b_out->size[0] = clst->size[0];
    b_out->size[1] = clst->size[1];
    emxEnsureCapacity_struct_T(b_out, i);
    out_data = b_out->data;
    inVectorLength = clst->size[0] * clst->size[1];
    for (i = 0; i < inVectorLength; i++) {
      emxCopyStruct_struct_T(&out_data[i], &clst_data[i]);
    }
  } else {
    i = b_out->size[0] * b_out->size[1];
    b_out->size[0] = clst->size[0];
    b_out->size[1] = clst->size[1];
    emxEnsureCapacity_struct_T(b_out, i);
    out_data = b_out->data;
    inVectorLength = clst->size[0] * clst->size[1];
    for (i = 0; i < inVectorLength; i++) {
      emxCopyStruct_struct_T(&out_data[i], &clst_data[i]);
    }
  }
  i = b_obj->clst->size[0] * b_obj->clst->size[1];
  b_obj->clst->size[0] = b_out->size[0];
  b_obj->clst->size[1] = b_out->size[1];
  emxEnsureCapacity_struct_T(b_obj->clst, i);
  inVectorLength = b_out->size[0] * b_out->size[1];
  for (i = 0; i < inVectorLength; i++) {
    emxCopyStruct_struct_T(&b_obj->clst->data[i], &out_data[i]);
  }
  emxFree_struct_T(&b_out);
  emxInit_boolean_T(&c_out, 2);
  if ((cmsk->size[0] == 1) && (cmsk->size[1] == 1)) {
    i = c_out->size[0] * c_out->size[1];
    c_out->size[0] = 1;
    c_out->size[1] = 1;
    emxEnsureCapacity_boolean_T(c_out, i);
    b_out_data = c_out->data;
    b_out_data[0] = cmsk_data[0];
  } else if ((cmsk->size[0] == 0) || (cmsk->size[1] == 0)) {
    i = c_out->size[0] * c_out->size[1];
    c_out->size[0] = cmsk->size[0];
    c_out->size[1] = cmsk->size[1];
    emxEnsureCapacity_boolean_T(c_out, i);
    b_out_data = c_out->data;
    inVectorLength = cmsk->size[0] * cmsk->size[1];
    for (i = 0; i < inVectorLength; i++) {
      b_out_data[i] = cmsk_data[i];
    }
  } else {
    i = c_out->size[0] * c_out->size[1];
    c_out->size[0] = cmsk->size[0];
    c_out->size[1] = cmsk->size[1];
    emxEnsureCapacity_boolean_T(c_out, i);
    b_out_data = c_out->data;
    inVectorLength = cmsk->size[0] * cmsk->size[1];
    for (i = 0; i < inVectorLength; i++) {
      b_out_data[i] = cmsk_data[i];
    }
  }
  i = b_obj->cmsk->size[0] * b_obj->cmsk->size[1];
  b_obj->cmsk->size[0] = c_out->size[0];
  b_obj->cmsk->size[1] = c_out->size[1];
  emxEnsureCapacity_boolean_T(b_obj->cmsk, i);
  inVectorLength = c_out->size[0] * c_out->size[1];
  for (i = 0; i < inVectorLength; i++) {
    b_obj->cmsk->data[i] = b_out_data[i];
  }
  emxFree_boolean_T(&c_out);
  emxInit_real_T(&in, 2);
  i = in->size[0] * in->size[1];
  in->size[0] = cpki->size[0];
  in->size[1] = cpki->size[1];
  emxEnsureCapacity_real_T(in, i);
  in_data = in->data;
  inVectorLength = cpki->size[0] * cpki->size[1];
  for (i = 0; i < inVectorLength; i++) {
    in_data[i] = cpki_data[i];
  }
  if ((cpki->size[0] == 1) && (cpki->size[1] == 1)) {
    i = in->size[0] * in->size[1];
    in->size[0] = 1;
    in->size[1] = 1;
    emxEnsureCapacity_real_T(in, i);
    in_data = in->data;
    in_data[0] = cpki_data[0];
  }
  i = b_obj->cpki->size[0] * b_obj->cpki->size[1];
  b_obj->cpki->size[0] = in->size[0];
  b_obj->cpki->size[1] = in->size[1];
  emxEnsureCapacity_real_T(b_obj->cpki, i);
  inVectorLength = in->size[0] * in->size[1];
  for (i = 0; i < inVectorLength; i++) {
    b_obj->cpki->data[i] = in_data[i];
  }
  emxFree_real_T(&in);
  return b_obj;
}

/*
 * %UPDATEPOSTERIORI updates the posteriori pulse statistics
 *              object using the new pulse list (input), prior pulse stats
 *              and the waveforms power spectral density vector. This
 *              methods is typically going to be called on a posteriori pulse
 *              stats object after a waveform has been processed and a set
 *              of candidate pulses found. This method uses those pulses and
 *              the prior information about the pulses to update the
 *              posteriori pulse stats.
 *
 *              The pulse contained in the waveform's ps_pos
 *              property is not used directly so that the caller can decide
 *              which pulses on which to focus the posteriori updates
 *
 *  updateType    What parts of the pulsestats to update. Valid
 *                options are 'time', 'freq', 'timeandfreq'. The
 *                'time' option will only update the interpulse
 *                time statistics. The 'freq' option will only
 *                update the frequency stats. The 'timeandfreq'
 *                option will update both.
 *
 *
 * Arguments    : pulsestats *obj
 *                const pulsestats *ps_pre
 *                const emxArray_struct_T *pulselist
 * Return Type  : void
 */
void b_pulsestats_updateposteriori(pulsestats *obj, const pulsestats *ps_pre,
                                   const emxArray_struct_T *pulselist)
{
  const b_struct_T *pulselist_data;
  emxArray_boolean_T *x;
  emxArray_real_T *b_result;
  emxArray_real_T *b_x;
  emxArray_real_T *c_result;
  emxArray_real_T *recent_tip;
  emxArray_real_T *result;
  double work_data;
  double *b_result_data;
  double *recent_tip_data;
  double *result_data;
  int i;
  int n;
  bool *x_data;
  pulselist_data = pulselist->data;
  if (pulselist->size[1] != 0) {
    double d;
    bool exitg1;
    bool y;
    /*  pulselist(:).t_0]' */
    /* pulselist(:).fp */
    /* Create a vector of bandwidths from the pulselist */
    /* fEnds   = [pulselist.fend]; */
    /* fStarts = [pulselist.fstart]; */
    /* bw_found = 2*(mean(fEnds,'all','omitnan')-mean(fStarts,'all','omitnan'));
     */
    /* if isempty(bw_found) */
    /*     bw_found = 100; */
    /*     if coder.target('MATLAB') */
    /*        warning(['UAV-R: No bandwidth could be calculated ',... */
    /*             'from the start and stop frequencies of the ',... */
    /*             'identified pulses. A bandwidth of 100 Hz ',... */
    /*             'will be used for continued informed search.']) */
    /*     end */
    /* end */
    /* Fix the bandwidth in the priori to +/- 100 Hz. */
    /* Here is where we update the stats. These methods of updates */
    /* could be improved in the future. */
    /* wfm.ps_pre.t_p; %tp doesn't change. We assume it is stationary */
    emxInit_real_T(&recent_tip, 2);
    emxInit_boolean_T(&x, 2);
    if (pulselist->size[1] == 1) {
      /*  Happens if K=1 */
      /* We only have one pulse to reference, so we need to check */
      /* the prior pulse too. */
      if ((ps_pre->pl->size[1] != 0) &&
          (!rtIsNaN(ps_pre->pl->data[ps_pre->pl->size[1] - 1].t_0))) {
        i = recent_tip->size[0] * recent_tip->size[1];
        recent_tip->size[0] = 1;
        recent_tip->size[1] = 1;
        emxEnsureCapacity_real_T(recent_tip, i);
        recent_tip_data = recent_tip->data;
        recent_tip_data[0] = pulselist_data[0].t_0 -
                             ps_pre->pl->data[ps_pre->pl->size[1] - 1].t_0;
        /* recent_tip = */
        /* pulselist.t_0-ps_pre.pl(end).t_0;%Conflicts with */
        /* Coder. Needed the (1) callout */
        /* There could be a case where the last segment and this */
        /* segement identified the same pulse. In this case */
        /* recent_tip will be very small. In this case, we just */
        /* say we learned nothing about t_ip in this segment. */
        i = x->size[0] * x->size[1];
        x->size[0] = 1;
        x->size[1] = 1;
        emxEnsureCapacity_boolean_T(x, i);
        x_data = x->data;
        x_data[0] = (recent_tip_data[0] < ps_pre->t_ipu + ps_pre->t_ipj);
        if (x_data[0]) {
          i = recent_tip->size[0] * recent_tip->size[1];
          recent_tip->size[0] = 1;
          recent_tip->size[1] = 1;
          emxEnsureCapacity_real_T(recent_tip, i);
          recent_tip_data = recent_tip->data;
          recent_tip_data[0] = rtNaN;
        }
      } else {
        /* No new information because we don't know the last */
        /* pulse time */
        i = recent_tip->size[0] * recent_tip->size[1];
        recent_tip->size[0] = 1;
        recent_tip->size[1] = 1;
        emxEnsureCapacity_real_T(recent_tip, i);
        recent_tip_data = recent_tip->data;
        recent_tip_data[0] = rtNaN;
      }
    } else {
      emxInit_real_T(&result, 2);
      n = pulselist->size[1];
      i = result->size[0] * result->size[1];
      result->size[0] = 1;
      result->size[1] = pulselist->size[1];
      emxEnsureCapacity_real_T(result, i);
      result_data = result->data;
      for (i = 0; i < n; i++) {
        result_data[i] = pulselist_data[i].t_0;
      }
      emxInit_real_T(&b_result, 2);
      n = pulselist->size[1];
      i = b_result->size[0] * b_result->size[1];
      b_result->size[0] = 1;
      b_result->size[1] = pulselist->size[1];
      emxEnsureCapacity_real_T(b_result, i);
      b_result_data = b_result->data;
      for (i = 0; i < n; i++) {
        b_result_data[i] = pulselist_data[i].t_0;
      }
      emxInit_real_T(&b_x, 2);
      i = b_x->size[0] * b_x->size[1];
      b_x->size[0] = b_result->size[1];
      b_x->size[1] = 1;
      emxEnsureCapacity_real_T(b_x, i);
      b_result_data = b_x->data;
      n = b_result->size[1];
      emxFree_real_T(&b_result);
      for (i = 0; i < n; i++) {
        b_result_data[i] = result_data[i];
      }
      emxFree_real_T(&result);
      n = b_x->size[0];
      i = recent_tip->size[0] * recent_tip->size[1];
      recent_tip->size[0] = b_x->size[0] - 1;
      recent_tip->size[1] = 1;
      emxEnsureCapacity_real_T(recent_tip, i);
      recent_tip_data = recent_tip->data;
      work_data = b_result_data[0];
      for (i = 2; i <= n; i++) {
        double tmp1;
        tmp1 = b_result_data[i - 1];
        d = tmp1;
        tmp1 -= work_data;
        work_data = d;
        recent_tip_data[i - 2] = tmp1;
      }
      emxFree_real_T(&b_x);
    }
    /* Do a check here to make sure the new tip isn't a huge change. */
    /* This could potentially happen if we are in the K = 1 case and */
    /* the block getting processed contained two pulses, with the */
    /* latter pulse getting identified/detected. The lines above */
    /* would look back to the last identified pulse and it might be */
    /* 2*tip back in time, producing a very large recenttip values. */
    /* If something like this happens, we ignore it so it doesn't */
    /* affect our new tip estimates. */
    i = x->size[0] * x->size[1];
    x->size[0] = recent_tip->size[0];
    x->size[1] = 1;
    emxEnsureCapacity_boolean_T(x, i);
    x_data = x->data;
    d = 1.5 * ps_pre->t_ip;
    n = recent_tip->size[0];
    for (i = 0; i < n; i++) {
      x_data[i] = (recent_tip_data[i] > d);
    }
    y = true;
    n = 0;
    exitg1 = false;
    while ((!exitg1) && (n <= x->size[0] - 1)) {
      if (!x_data[n]) {
        y = false;
        exitg1 = true;
      } else {
        n++;
      }
    }
    if (y) {
      i = x->size[0] * x->size[1];
      x->size[0] = recent_tip->size[0];
      x->size[1] = 1;
      emxEnsureCapacity_boolean_T(x, i);
      x_data = x->data;
      d = 0.5 * ps_pre->t_ip;
      n = recent_tip->size[0];
      for (i = 0; i < n; i++) {
        x_data[i] = (recent_tip_data[i] < d);
      }
      y = true;
      n = 0;
      exitg1 = false;
      while ((!exitg1) && (n <= x->size[0] - 1)) {
        if (!x_data[n]) {
          y = false;
          exitg1 = true;
        } else {
          n++;
        }
      }
      if (y) {
        i = recent_tip->size[0] * recent_tip->size[1];
        recent_tip->size[0] = 1;
        recent_tip->size[1] = 1;
        emxEnsureCapacity_real_T(recent_tip, i);
        recent_tip_data = recent_tip->data;
        recent_tip_data[0] = rtNaN;
      }
    }
    emxFree_boolean_T(&x);
    /*                  %Only update time parameters if we are in tracking mode.
     * If we */
    /*                  %aren't, we may have identified somethign that isn't a
     * pulse */
    /*                  if strcmp(obj.mode,'T') || strcmp(ps_pre.mode,'T') */
    /*                      obj.t_ip  =
     * mean([recent_tip;ps_pre.t_ip],'omitnan'); */
    /*                      obj.t_ipu = ps_pre.t_ipu; %Don't update this because
     * it can get too narrow.%mean([3*std(diff(t_found));wfm.ps_pre.t_ipu]); */
    /*                      obj.t_ipj = ps_pre.t_ipj; */
    /*                  end */
    /*                  fp_pos     =
     * freq_found;%nanmean([freq_found;wfm.ps_pre.fp]);%Previous fc may be nan
     * if unknown */
    /*                  obj.fp     = fp_pos; */
    /*                  obj.fstart = fp_pos-bw_found/2; */
    /*                  obj.fend   = fp_pos+bw_found/2; */
    emxInit_real_T(&c_result, 1);
    n = recent_tip->size[0];
    i = c_result->size[0];
    c_result->size[0] = recent_tip->size[0] + 1;
    emxEnsureCapacity_real_T(c_result, i);
    result_data = c_result->data;
    for (i = 0; i < n; i++) {
      result_data[i] = recent_tip_data[i];
    }
    result_data[recent_tip->size[0]] = ps_pre->t_ip;
    emxFree_real_T(&recent_tip);
    colMajorFlatIter(c_result, c_result->size[0], &work_data, &n);
    emxFree_real_T(&c_result);
    obj->t_ip = work_data / (double)n;
    obj->t_ipu = ps_pre->t_ipu;
    /* Don't update this because it can get too
     * narrow.%mean([3*std(diff(t_found));wfm.ps_pre.t_ipu]); */
    obj->t_ipj = ps_pre->t_ipj;
  }
}

/*
 * PULSESTATS Constructs an instance of this class
 *
 * INPUTS:
 *    tp      1x1     Duration of pulse (second)
 *    tip     1x1     Inter-pulse time (seconds)
 *    tipu    1x1     Inter-pulse time uncertainty (seconds)
 *    tipj    1x1     Inter-pulse time jitter (deviations from means) (seconds)
 *    fp      1x1     Pulses' center frequency (Hz) (if known)
 *    fstart  1x1     Lower frequency bound pulses' center frequency (Hz) (if
 * known) fend    1x1     Upper frequency bound pulses' center frequency (Hz)
 * (if known) tmplt   1xn     Pulse template. See properies for definition.
 * Usually set to [1 1] for square pulse. pl      px1     Vector of pulse
 * objects in waveform (if known). If unknown enter a blank pulse made from the
 * contstructor "pulse"; Note: Unknown inputs should be set to NaN.
 *
 * OUTPUTS:
 *    pulsestats object
 *
 *             %%
 *
 * Arguments    : pulsestats *obj
 *                double tp
 *                double tip
 *                double tipu
 *                double tipj
 *                double fp
 *                const b_struct_T *pl
 *                const b_struct_T *clst
 * Return Type  : pulsestats *
 */
pulsestats *c_pulsestats_pulsestats(pulsestats *obj, double tp, double tip,
                                    double tipu, double tipj, double fp,
                                    const b_struct_T *pl,
                                    const b_struct_T *clst)
{
  b_struct_T *out_data;
  emxArray_struct_T *in;
  emxArray_struct_T *out;
  pulsestats *b_obj;
  int i;
  b_obj = obj;
  b_obj->t_p = tp;
  b_obj->t_ip = tip;
  b_obj->t_ipu = tipu;
  b_obj->t_ipj = tipj;
  b_obj->fp = fp;
  b_obj->fstart = 0.0;
  b_obj->fend = 0.0;
  b_obj->tmplt[0] = 1.0;
  b_obj->tmplt[1] = 1.0;
  b_obj->mode = 'D';
  /* The following are variable sized properties. To tell coder */
  /* that they may vary setup as a local variable size variable */
  /* first, then set. */
  /* Instructions on
   * https://www.mathworks.com/help/simulink/ug/how-working-with-matlab-classes-is-different-for-code-generation.html
   */
  /* localMode = mode; */
  /* coder.varsize('localMode',[1 inf],[0 1]); %dims 0 if fixed, 1 if variable
   */
  /* Tell coder these are variable size. */
  /* Now actually assign them  */
  emxInit_struct_T(&out);
  i = out->size[0] * out->size[1];
  out->size[0] = 1;
  out->size[1] = 1;
  emxEnsureCapacity_struct_T(out, i);
  out_data = out->data;
  emxCopyStruct_struct_T(&out_data[0], pl);
  i = b_obj->pl->size[0] * b_obj->pl->size[1];
  b_obj->pl->size[0] = 1;
  b_obj->pl->size[1] = 1;
  emxEnsureCapacity_struct_T(b_obj->pl, i);
  emxCopyStruct_struct_T(&b_obj->pl->data[0], &out_data[0]);
  emxFree_struct_T(&out);
  emxInit_struct_T(&in);
  i = in->size[0] * in->size[1];
  in->size[0] = 1;
  in->size[1] = 1;
  emxEnsureCapacity_struct_T(in, i);
  out_data = in->data;
  emxCopyStruct_struct_T(&out_data[0], clst);
  i = b_obj->clst->size[0] * b_obj->clst->size[1];
  b_obj->clst->size[0] = 1;
  b_obj->clst->size[1] = 1;
  emxEnsureCapacity_struct_T(b_obj->clst, i);
  emxCopyStruct_struct_T(&b_obj->clst->data[0], &out_data[0]);
  emxFree_struct_T(&in);
  i = b_obj->cmsk->size[0] * b_obj->cmsk->size[1];
  b_obj->cmsk->size[0] = 1;
  b_obj->cmsk->size[1] = 1;
  emxEnsureCapacity_boolean_T(b_obj->cmsk, i);
  b_obj->cmsk->data[0] = false;
  i = b_obj->cpki->size[0] * b_obj->cpki->size[1];
  b_obj->cpki->size[0] = 1;
  b_obj->cpki->size[1] = 1;
  emxEnsureCapacity_real_T(b_obj->cpki, i);
  b_obj->cpki->data[0] = rtNaN;
  return b_obj;
}

/*
 * PULSESTATS Constructs an instance of this class
 *
 * INPUTS:
 *    tp      1x1     Duration of pulse (second)
 *    tip     1x1     Inter-pulse time (seconds)
 *    tipu    1x1     Inter-pulse time uncertainty (seconds)
 *    tipj    1x1     Inter-pulse time jitter (deviations from means) (seconds)
 *    fp      1x1     Pulses' center frequency (Hz) (if known)
 *    fstart  1x1     Lower frequency bound pulses' center frequency (Hz) (if
 * known) fend    1x1     Upper frequency bound pulses' center frequency (Hz)
 * (if known) tmplt   1xn     Pulse template. See properies for definition.
 * Usually set to [1 1] for square pulse. pl      px1     Vector of pulse
 * objects in waveform (if known). If unknown enter a blank pulse made from the
 * contstructor "pulse"; Note: Unknown inputs should be set to NaN.
 *
 * OUTPUTS:
 *    pulsestats object
 *
 *             %%
 *
 * Arguments    : pulsestats *obj
 *                double tp
 *                double tip
 *                double tipu
 *                double tipj
 *                double fp
 *                double fstart
 *                double fend
 *                const double tmplt[2]
 *                const char mode_data[]
 *                const emxArray_struct_T *pl
 *                const emxArray_struct_T *clst
 *                const emxArray_boolean_T *cmsk
 *                const emxArray_real_T *cpki
 * Return Type  : pulsestats *
 */
pulsestats *d_pulsestats_pulsestats(
    pulsestats *obj, double tp, double tip, double tipu, double tipj, double fp,
    double fstart, double fend, const double tmplt[2], const char mode_data[],
    const emxArray_struct_T *pl, const emxArray_struct_T *clst,
    const emxArray_boolean_T *cmsk, const emxArray_real_T *cpki)
{
  const b_struct_T *clst_data;
  const b_struct_T *pl_data;
  b_struct_T *out_data;
  emxArray_boolean_T *c_out;
  emxArray_real_T *in;
  emxArray_struct_T *b_out;
  emxArray_struct_T *out;
  pulsestats *b_obj;
  const double *cpki_data;
  double *in_data;
  int i;
  int inVectorLength;
  const bool *cmsk_data;
  bool *b_out_data;
  cpki_data = cpki->data;
  cmsk_data = cmsk->data;
  clst_data = clst->data;
  pl_data = pl->data;
  b_obj = obj;
  b_obj->t_p = tp;
  b_obj->t_ip = tip;
  b_obj->t_ipu = tipu;
  b_obj->t_ipj = tipj;
  b_obj->fp = fp;
  b_obj->fstart = fstart;
  b_obj->fend = fend;
  b_obj->tmplt[0] = tmplt[0];
  b_obj->tmplt[1] = tmplt[1];
  b_obj->mode = mode_data[0];
  /* The following are variable sized properties. To tell coder */
  /* that they may vary setup as a local variable size variable */
  /* first, then set. */
  /* Instructions on
   * https://www.mathworks.com/help/simulink/ug/how-working-with-matlab-classes-is-different-for-code-generation.html
   */
  /* localMode = mode; */
  /* coder.varsize('localMode',[1 inf],[0 1]); %dims 0 if fixed, 1 if variable
   */
  /* Tell coder these are variable size. */
  /* Now actually assign them  */
  emxInit_struct_T(&out);
  inVectorLength = 1;
  if (pl->size[1] != 1) {
    inVectorLength = pl->size[1];
  }
  if (pl->size[1] == 1) {
    i = out->size[0] * out->size[1];
    out->size[0] = 1;
    out->size[1] = inVectorLength;
    emxEnsureCapacity_struct_T(out, i);
    out_data = out->data;
    for (i = 0; i < inVectorLength; i++) {
      emxCopyStruct_struct_T(&out_data[i], &pl_data[0]);
    }
  } else if (pl->size[1] == 0) {
    i = out->size[0] * out->size[1];
    out->size[0] = 1;
    out->size[1] = inVectorLength;
    emxEnsureCapacity_struct_T(out, i);
    out_data = out->data;
    for (i = 0; i < inVectorLength; i++) {
      emxCopyStruct_struct_T(&out_data[i], &pl_data[i]);
    }
  } else {
    i = out->size[0] * out->size[1];
    out->size[0] = 1;
    out->size[1] = inVectorLength;
    emxEnsureCapacity_struct_T(out, i);
    out_data = out->data;
    for (i = 0; i < inVectorLength; i++) {
      emxCopyStruct_struct_T(&out_data[i], &pl_data[i]);
    }
  }
  i = b_obj->pl->size[0] * b_obj->pl->size[1];
  b_obj->pl->size[0] = 1;
  b_obj->pl->size[1] = out->size[1];
  emxEnsureCapacity_struct_T(b_obj->pl, i);
  inVectorLength = out->size[1];
  for (i = 0; i < inVectorLength; i++) {
    emxCopyStruct_struct_T(&b_obj->pl->data[i], &out_data[i]);
  }
  emxFree_struct_T(&out);
  emxInit_struct_T(&b_out);
  if ((clst->size[0] == 1) && (clst->size[1] == 1)) {
    i = b_out->size[0] * b_out->size[1];
    b_out->size[0] = 1;
    b_out->size[1] = 1;
    emxEnsureCapacity_struct_T(b_out, i);
    out_data = b_out->data;
    emxCopyStruct_struct_T(&out_data[0], &clst_data[0]);
  } else if ((clst->size[0] == 0) || (clst->size[1] == 0)) {
    i = b_out->size[0] * b_out->size[1];
    b_out->size[0] = clst->size[0];
    b_out->size[1] = clst->size[1];
    emxEnsureCapacity_struct_T(b_out, i);
    out_data = b_out->data;
    inVectorLength = clst->size[0] * clst->size[1];
    for (i = 0; i < inVectorLength; i++) {
      emxCopyStruct_struct_T(&out_data[i], &clst_data[i]);
    }
  } else {
    i = b_out->size[0] * b_out->size[1];
    b_out->size[0] = clst->size[0];
    b_out->size[1] = clst->size[1];
    emxEnsureCapacity_struct_T(b_out, i);
    out_data = b_out->data;
    inVectorLength = clst->size[0] * clst->size[1];
    for (i = 0; i < inVectorLength; i++) {
      emxCopyStruct_struct_T(&out_data[i], &clst_data[i]);
    }
  }
  i = b_obj->clst->size[0] * b_obj->clst->size[1];
  b_obj->clst->size[0] = b_out->size[0];
  b_obj->clst->size[1] = b_out->size[1];
  emxEnsureCapacity_struct_T(b_obj->clst, i);
  inVectorLength = b_out->size[0] * b_out->size[1];
  for (i = 0; i < inVectorLength; i++) {
    emxCopyStruct_struct_T(&b_obj->clst->data[i], &out_data[i]);
  }
  emxFree_struct_T(&b_out);
  emxInit_boolean_T(&c_out, 2);
  if ((cmsk->size[0] == 1) && (cmsk->size[1] == 1)) {
    i = c_out->size[0] * c_out->size[1];
    c_out->size[0] = 1;
    c_out->size[1] = 1;
    emxEnsureCapacity_boolean_T(c_out, i);
    b_out_data = c_out->data;
    b_out_data[0] = cmsk_data[0];
  } else if ((cmsk->size[0] == 0) || (cmsk->size[1] == 0)) {
    i = c_out->size[0] * c_out->size[1];
    c_out->size[0] = cmsk->size[0];
    c_out->size[1] = cmsk->size[1];
    emxEnsureCapacity_boolean_T(c_out, i);
    b_out_data = c_out->data;
    inVectorLength = cmsk->size[0] * cmsk->size[1];
    for (i = 0; i < inVectorLength; i++) {
      b_out_data[i] = cmsk_data[i];
    }
  } else {
    i = c_out->size[0] * c_out->size[1];
    c_out->size[0] = cmsk->size[0];
    c_out->size[1] = cmsk->size[1];
    emxEnsureCapacity_boolean_T(c_out, i);
    b_out_data = c_out->data;
    inVectorLength = cmsk->size[0] * cmsk->size[1];
    for (i = 0; i < inVectorLength; i++) {
      b_out_data[i] = cmsk_data[i];
    }
  }
  i = b_obj->cmsk->size[0] * b_obj->cmsk->size[1];
  b_obj->cmsk->size[0] = c_out->size[0];
  b_obj->cmsk->size[1] = c_out->size[1];
  emxEnsureCapacity_boolean_T(b_obj->cmsk, i);
  inVectorLength = c_out->size[0] * c_out->size[1];
  for (i = 0; i < inVectorLength; i++) {
    b_obj->cmsk->data[i] = b_out_data[i];
  }
  emxFree_boolean_T(&c_out);
  emxInit_real_T(&in, 2);
  i = in->size[0] * in->size[1];
  in->size[0] = cpki->size[0];
  in->size[1] = cpki->size[1];
  emxEnsureCapacity_real_T(in, i);
  in_data = in->data;
  inVectorLength = cpki->size[0] * cpki->size[1];
  for (i = 0; i < inVectorLength; i++) {
    in_data[i] = cpki_data[i];
  }
  if ((cpki->size[0] == 1) && (cpki->size[1] == 1)) {
    i = in->size[0] * in->size[1];
    in->size[0] = 1;
    in->size[1] = 1;
    emxEnsureCapacity_real_T(in, i);
    in_data = in->data;
    in_data[0] = cpki_data[0];
  }
  i = b_obj->cpki->size[0] * b_obj->cpki->size[1];
  b_obj->cpki->size[0] = in->size[0];
  b_obj->cpki->size[1] = in->size[1];
  emxEnsureCapacity_real_T(b_obj->cpki, i);
  inVectorLength = in->size[0] * in->size[1];
  for (i = 0; i < inVectorLength; i++) {
    b_obj->cpki->data[i] = in_data[i];
  }
  emxFree_real_T(&in);
  return b_obj;
}

/*
 * PULSESTATS Constructs an instance of this class
 *
 * INPUTS:
 *    tp      1x1     Duration of pulse (second)
 *    tip     1x1     Inter-pulse time (seconds)
 *    tipu    1x1     Inter-pulse time uncertainty (seconds)
 *    tipj    1x1     Inter-pulse time jitter (deviations from means) (seconds)
 *    fp      1x1     Pulses' center frequency (Hz) (if known)
 *    fstart  1x1     Lower frequency bound pulses' center frequency (Hz) (if
 * known) fend    1x1     Upper frequency bound pulses' center frequency (Hz)
 * (if known) tmplt   1xn     Pulse template. See properies for definition.
 * Usually set to [1 1] for square pulse. pl      px1     Vector of pulse
 * objects in waveform (if known). If unknown enter a blank pulse made from the
 * contstructor "pulse"; Note: Unknown inputs should be set to NaN.
 *
 * OUTPUTS:
 *    pulsestats object
 *
 *             %%
 *
 * Arguments    : pulsestats *obj
 *                double tp
 *                double tip
 *                double tipu
 *                double tipj
 *                const b_struct_T *pl
 *                const b_struct_T *clst
 * Return Type  : pulsestats *
 */
pulsestats *pulsestats_pulsestats(pulsestats *obj, double tp, double tip,
                                  double tipu, double tipj,
                                  const b_struct_T *pl, const b_struct_T *clst)
{
  b_struct_T *out_data;
  emxArray_struct_T *in;
  emxArray_struct_T *out;
  pulsestats *b_obj;
  int i;
  b_obj = obj;
  b_obj->t_p = tp;
  b_obj->t_ip = tip;
  b_obj->t_ipu = tipu;
  b_obj->t_ipj = tipj;
  b_obj->fp = 0.0;
  b_obj->fstart = 0.0;
  b_obj->fend = 0.0;
  b_obj->tmplt[0] = 1.0;
  b_obj->tmplt[1] = 1.0;
  b_obj->mode = 'D';
  /* The following are variable sized properties. To tell coder */
  /* that they may vary setup as a local variable size variable */
  /* first, then set. */
  /* Instructions on
   * https://www.mathworks.com/help/simulink/ug/how-working-with-matlab-classes-is-different-for-code-generation.html
   */
  /* localMode = mode; */
  /* coder.varsize('localMode',[1 inf],[0 1]); %dims 0 if fixed, 1 if variable
   */
  /* Tell coder these are variable size. */
  /* Now actually assign them  */
  emxInit_struct_T(&out);
  i = out->size[0] * out->size[1];
  out->size[0] = 1;
  out->size[1] = 1;
  emxEnsureCapacity_struct_T(out, i);
  out_data = out->data;
  emxCopyStruct_struct_T(&out_data[0], pl);
  i = b_obj->pl->size[0] * b_obj->pl->size[1];
  b_obj->pl->size[0] = 1;
  b_obj->pl->size[1] = 1;
  emxEnsureCapacity_struct_T(b_obj->pl, i);
  emxCopyStruct_struct_T(&b_obj->pl->data[0], &out_data[0]);
  emxFree_struct_T(&out);
  emxInit_struct_T(&in);
  i = in->size[0] * in->size[1];
  in->size[0] = 1;
  in->size[1] = 1;
  emxEnsureCapacity_struct_T(in, i);
  out_data = in->data;
  emxCopyStruct_struct_T(&out_data[0], clst);
  i = b_obj->clst->size[0] * b_obj->clst->size[1];
  b_obj->clst->size[0] = 1;
  b_obj->clst->size[1] = 1;
  emxEnsureCapacity_struct_T(b_obj->clst, i);
  emxCopyStruct_struct_T(&b_obj->clst->data[0], &out_data[0]);
  emxFree_struct_T(&in);
  b_obj->cmsk->size[0] = 0;
  b_obj->cmsk->size[1] = 0;
  b_obj->cpki->size[0] = 0;
  b_obj->cpki->size[1] = 0;
  return b_obj;
}

/*
 * %UPDATEPOSTERIORI updates the posteriori pulse statistics
 *              object using the new pulse list (input), prior pulse stats
 *              and the waveforms power spectral density vector. This
 *              methods is typically going to be called on a posteriori pulse
 *              stats object after a waveform has been processed and a set
 *              of candidate pulses found. This method uses those pulses and
 *              the prior information about the pulses to update the
 *              posteriori pulse stats.
 *
 *              The pulse contained in the waveform's ps_pos
 *              property is not used directly so that the caller can decide
 *              which pulses on which to focus the posteriori updates
 *
 *  updateType    What parts of the pulsestats to update. Valid
 *                options are 'time', 'freq', 'timeandfreq'. The
 *                'time' option will only update the interpulse
 *                time statistics. The 'freq' option will only
 *                update the frequency stats. The 'timeandfreq'
 *                option will update both.
 *
 *
 * Arguments    : pulsestats *obj
 *                const emxArray_struct_T *pulselist
 * Return Type  : void
 */
void pulsestats_updateposteriori(pulsestats *obj,
                                 const emxArray_struct_T *pulselist)
{
  const b_struct_T *pulselist_data;
  emxArray_real_T b_varargin_1;
  emxArray_real_T *varargin_1;
  double freq_found;
  double *varargin_1_data;
  int b_pulselist;
  int c_pulselist;
  pulselist_data = pulselist->data;
  if (pulselist->size[1] != 0) {
    int n;
    /*  pulselist(:).t_0]' */
    n = pulselist->size[1];
    emxInit_real_T(&varargin_1, 2);
    b_pulselist = varargin_1->size[0] * varargin_1->size[1];
    varargin_1->size[0] = 1;
    varargin_1->size[1] = pulselist->size[1];
    emxEnsureCapacity_real_T(varargin_1, b_pulselist);
    varargin_1_data = varargin_1->data;
    for (b_pulselist = 0; b_pulselist < n; b_pulselist++) {
      varargin_1_data[b_pulselist] = pulselist_data[b_pulselist].fp;
    }
    b_pulselist = varargin_1->size[1];
    b_varargin_1 = *varargin_1;
    c_pulselist = b_pulselist;
    b_varargin_1.size = &c_pulselist;
    b_varargin_1.numDimensions = 1;
    colMajorFlatIter(&b_varargin_1, varargin_1->size[1], &freq_found,
                     &b_pulselist);
    emxFree_real_T(&varargin_1);
    freq_found /= (double)b_pulselist;
    /* pulselist(:).fp */
    /* Create a vector of bandwidths from the pulselist */
    /* fEnds   = [pulselist.fend]; */
    /* fStarts = [pulselist.fstart]; */
    /* bw_found = 2*(mean(fEnds,'all','omitnan')-mean(fStarts,'all','omitnan'));
     */
    /* if isempty(bw_found) */
    /*     bw_found = 100; */
    /*     if coder.target('MATLAB') */
    /*        warning(['UAV-R: No bandwidth could be calculated ',... */
    /*             'from the start and stop frequencies of the ',... */
    /*             'identified pulses. A bandwidth of 100 Hz ',... */
    /*             'will be used for continued informed search.']) */
    /*     end */
    /* end */
    /* Fix the bandwidth in the priori to +/- 100 Hz. */
    /* Here is where we update the stats. These methods of updates */
    /* could be improved in the future. */
    /* wfm.ps_pre.t_p; %tp doesn't change. We assume it is stationary */
    obj->fp = freq_found;
    obj->fstart = freq_found - 100.0;
    obj->fend = freq_found + 100.0;
  }
}

/*
 * File trailer for pulsestats.c
 *
 * [EOF]
 */
