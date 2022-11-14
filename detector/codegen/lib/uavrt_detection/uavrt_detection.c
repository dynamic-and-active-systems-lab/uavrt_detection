/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: uavrt_detection.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "uavrt_detection.h"
#include "AsyncBuffer.h"
#include "DetectorConfig.h"
#include "SystemCore.h"
#include "all.h"
#include "channelreceiver.h"
#include "controlreceiver.h"
#include "diff.h"
#include "fgetl.h"
#include "fileManager.h"
#include "find.h"
#include "fseek.h"
#include "ftell.h"
#include "fwrite.h"
#include "handle.h"
#include "horzcatStructList.h"
#include "ifWhileCond.h"
#include "makepulsestruc.h"
#include "pause.h"
#include "pulsestats.h"
#include "rt_nonfinite.h"
#include "str2double.h"
#include "str2matrix.h"
#include "strcmp.h"
#include "string1.h"
#include "sum.h"
#include "threshold.h"
#include "tic.h"
#include "toc.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_initialize.h"
#include "uavrt_detection_internal_types.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "validate_print_arguments.h"
#include "waveform.h"
#include "waveformcopy.h"
#include "wgn.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

/* Type Definitions */
#ifndef typedef_captured_var
#define typedef_captured_var
typedef struct {
  double contents;
} captured_var;
#endif /* typedef_captured_var */

#ifndef typedef_rtString
#define typedef_rtString
typedef struct {
  char Value[25];
} rtString;
#endif /* typedef_rtString */

#ifndef typedef_b_captured_var
#define typedef_b_captured_var
typedef struct {
  rtString contents;
} b_captured_var;
#endif /* typedef_b_captured_var */

/* Function Declarations */
static void checkcommand(const signed char cmdReceived_data[],
                         const int cmdReceived_size[2],
                         char currentState_data[], int currentState_size[2]);

static void updatebufferreadvariables(const c_captured_var *Config,
                                      const captured_var *stftOverlapFraction,
                                      captured_var *overlapSamples,
                                      captured_var *sampsForKPulses,
                                      const pulsestats *ps_input);

static void updateconfig(c_captured_var *Config,
                         const b_captured_var *configPath);

/* Function Definitions */
/*
 * This function is designed to check the incoming command and decide what to
 * do based on the received command and the current state
 *
 * Arguments    : const signed char cmdReceived_data[]
 *                const int cmdReceived_size[2]
 *                char currentState_data[]
 *                int currentState_size[2]
 * Return Type  : void
 */
static void checkcommand(const signed char cmdReceived_data[],
                         const int cmdReceived_size[2],
                         char currentState_data[], int currentState_size[2])
{
  emxArray_boolean_T *x;
  int i;
  bool *x_data;
  if ((cmdReceived_size[0] != 0) && (cmdReceived_size[1] != 0)) {
    int loop_ub;
    bool exitg1;
    bool y;
    emxInit_boolean_T(&x, 2);
    i = x->size[0] * x->size[1];
    x->size[0] = cmdReceived_size[0];
    x->size[1] = 1;
    emxEnsureCapacity_boolean_T(x, i);
    x_data = x->data;
    loop_ub = cmdReceived_size[0];
    for (i = 0; i < loop_ub; i++) {
      x_data[i] = (cmdReceived_data[i] == -1);
    }
    y = true;
    loop_ub = 0;
    exitg1 = false;
    while ((!exitg1) && (loop_ub <= x->size[0] - 1)) {
      if (!x_data[loop_ub]) {
        y = false;
        exitg1 = true;
      } else {
        loop_ub++;
      }
    }
    if (y) {
      printf("Received kill command. \n");
      fflush(stdout);
      currentState_size[0] = 1;
      currentState_size[1] = 4;
      currentState_data[0] = 'k';
      currentState_data[1] = 'i';
      currentState_data[2] = 'l';
      currentState_data[3] = 'l';
    } else {
      i = x->size[0] * x->size[1];
      x->size[0] = cmdReceived_size[0];
      x->size[1] = 1;
      emxEnsureCapacity_boolean_T(x, i);
      x_data = x->data;
      loop_ub = cmdReceived_size[0];
      for (i = 0; i < loop_ub; i++) {
        x_data[i] = (cmdReceived_data[i] == 0);
      }
      y = true;
      loop_ub = 0;
      exitg1 = false;
      while ((!exitg1) && (loop_ub <= x->size[0] - 1)) {
        if (!x_data[loop_ub]) {
          y = false;
          exitg1 = true;
        } else {
          loop_ub++;
        }
      }
      if (y) {
        printf("Received idle command. \n");
        fflush(stdout);
        currentState_size[0] = 1;
        currentState_size[1] = 4;
        currentState_data[0] = 'i';
        currentState_data[1] = 'd';
        currentState_data[2] = 'l';
        currentState_data[3] = 'e';
      } else {
        i = x->size[0] * x->size[1];
        x->size[0] = cmdReceived_size[0];
        x->size[1] = 1;
        emxEnsureCapacity_boolean_T(x, i);
        x_data = x->data;
        loop_ub = cmdReceived_size[0];
        for (i = 0; i < loop_ub; i++) {
          x_data[i] = (cmdReceived_data[i] == 1);
        }
        y = true;
        loop_ub = 0;
        exitg1 = false;
        while ((!exitg1) && (loop_ub <= x->size[0] - 1)) {
          if (!x_data[loop_ub]) {
            y = false;
            exitg1 = true;
          } else {
            loop_ub++;
          }
        }
        if (y) {
          printf("Received run command. \n");
          fflush(stdout);
          currentState_size[0] = 1;
          currentState_size[1] = 3;
          currentState_data[0] = 'r';
          currentState_data[1] = 'u';
          currentState_data[2] = 'n';
        } else {
          i = x->size[0] * x->size[1];
          x->size[0] = cmdReceived_size[0];
          x->size[1] = 1;
          emxEnsureCapacity_boolean_T(x, i);
          x_data = x->data;
          loop_ub = cmdReceived_size[0];
          for (i = 0; i < loop_ub; i++) {
            x_data[i] = (cmdReceived_data[i] == 2);
          }
          y = true;
          loop_ub = 0;
          exitg1 = false;
          while ((!exitg1) && (loop_ub <= x->size[0] - 1)) {
            if (!x_data[loop_ub]) {
              y = false;
              exitg1 = true;
            } else {
              loop_ub++;
            }
          }
          if (y) {
            printf("Received update config command. \n");
            fflush(stdout);
            currentState_size[0] = 1;
            currentState_size[1] = 12;
            for (i = 0; i < 12; i++) {
              currentState_data[i] = cv[i];
            }
          } else {
            i = x->size[0] * x->size[1];
            x->size[0] = cmdReceived_size[0];
            x->size[1] = 1;
            emxEnsureCapacity_boolean_T(x, i);
            x_data = x->data;
            loop_ub = cmdReceived_size[0];
            for (i = 0; i < loop_ub; i++) {
              x_data[i] = (cmdReceived_data[i] == 3);
            }
            y = true;
            loop_ub = 0;
            exitg1 = false;
            while ((!exitg1) && (loop_ub <= x->size[0] - 1)) {
              if (!x_data[loop_ub]) {
                y = false;
                exitg1 = true;
              } else {
                loop_ub++;
              }
            }
            if (y) {
              printf("Received test command. \n");
              fflush(stdout);
              currentState_size[0] = 1;
              currentState_size[1] = 4;
              currentState_data[0] = 't';
              currentState_data[1] = 'e';
              currentState_data[2] = 's';
              currentState_data[3] = 't';
            } else {
              /* Invalid command. Continue with current state. */
            }
          }
        }
      }
    }
    emxFree_boolean_T(&x);
  } else {
    /* Nothing received. Continue with current state. */
  }
}

/*
 * This function updates the buffer reading variables as needed by
 * the priori information about the pulse statistics. The segment
 * lengths depend on the interpulse duration and uncertainty
 * parameters.
 *
 * Arguments    : const c_captured_var *Config
 *                const captured_var *stftOverlapFraction
 *                captured_var *overlapSamples
 *                captured_var *sampsForKPulses
 *                const pulsestats *ps_input
 * Return Type  : void
 */
static void updatebufferreadvariables(const c_captured_var *Config,
                                      const captured_var *stftOverlapFraction,
                                      captured_var *overlapSamples,
                                      captured_var *sampsForKPulses,
                                      const pulsestats *ps_input)
{
  pulsestats lobj_2;
  double M;
  double N;
  double X0_Fs;
  double a__2;
  double n_ol;
  double n_ws;
  unsigned int u;
  unsigned int u1;
  unsigned int u2;
  emxInitStruct_pulsestats(&lobj_2);
  /* persistent X0 */
  /* if isempty(X0) */
  /* Build an empty waveform just so that we can calculate number */
  /* of overlapSamples. This is needed for buffer operations */
  /* X0 = waveform([], Config.Fs, 0, pulsestats, stftOverlapFraction); */
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
  /* Flatten input to row */
  /* Data vector */
  /* Elements in the data */
  X0_Fs = Config->contents.Fs;
  /* Sample rate */
  /* Time stamp of first element */
  /* Time stamp of last element */
  /* This is the time when next */
  /* segment should start to */
  /* ensure sufficient overlap. */
  /* Will need to be updated  */
  /* elsewhere.  */
  /* Overlap Fraction for STFT */
  /* Unknown number of pulses. */
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
  /* Unknown values but set types */
  /* Copy over ps_ */
  /* COPY Creates an exact copy of the pulse stats object as a separate object
   */
  b_pulsestats_pulsestats(&lobj_2, ps_input->t_p, ps_input->t_ip,
                          ps_input->t_ipu, ps_input->t_ipj, ps_input->fp,
                          ps_input->fstart, ps_input->fend, ps_input->tmplt,
                          ps_input->mode, ps_input->pl, ps_input->clst,
                          ps_input->cmsk, ps_input->cpki);
  /* ,... */
  /* obj.thresh); */
  /* Current stats are same as previous during construction */
  /* obj.ps_pos = pulsestats();%TESTING FOR CODER - NEEDS TO BE REVERTED BACK TO
   * LAST LINE */
  /* obj.TimeCorr = TemporalCorrelator(10, 0, 0);%Generate a temporalcorrelator
   * object so coder knows the type of the object */
  /* SETPRIORIDEPENDENTVARS updates the properties in the */
  /* waveform that are dependent on properties in a pulsestats */
  /* object.  */
  /*  */
  /* INPUTS:   */
  /*    obj     waveform object */
  /*    ps_obj  a pulse stats object */
  /* OUTPUTS:  */
  /*    None (This method modifies the waveform object properties)  */
  /*  */
  /*             %% */
  /* GETPRIORIDEPENDENTVARS returns the properties in the */
  /* waveform that are dependent on prior pulse data estimates. It */
  /* depends on the waveform properties list Fs etc, as well as */
  /* pulse stats like t_ip, etc. */
  /* INPUTS:  ps_obj  1x1 pulse stats object */
  /* OUTPUTS:  pulse stats object */
  /* WHAT WAS DONE BY THIS METHOD IS NOW DONE BY A METHOD OF THE */
  /* PULSESTATS CLASS.  */
  /*          function [] = update_posteriori(obj,pulselist) */
  /*              %UPDATE_POSTERIORI updates the posteriori pulse statistics of
   */
  /*              %this waveform object using the new pulse list (input) and the
   */
  /*              %apriori stats. The pulse contained in the waveform's ps_pos
   */
  /*              %property is not used directly so that the caller can decide
   */
  /*              %which pulses on which to focus the posteriori.  */
  /*               */
  /*              t_found    = [pulselist(:).t_0]'; */
  /*              freq_found = mean([pulselist(:).fp],'omitnan'); */
  /*               */
  /*              %Create a vector of bandwidths from the pulselist */
  /*              bw_found =
   * 2*(mean([pulselist.fend],'omitnan')-mean([pulselist.fstart],'omitnan')); */
  /*              if isempty(bw_found) */
  /*                  bw_found = 100; */
  /*                  if coder.target('MATLAB') */
  /*                      warning(['UAV-R: No bandwidth could be calculated
   * ',...  */
  /*                           'from the start and stop frequencies of the ',...
   */
  /*                           'identified pulses. A bandwidth of 100 Hz ',...
   */
  /*                           'will be used for continued informed search.'])
   */
  /*                  end */
  /*              end */
  /*               */
  /*              %Here is where we update the stats. These methods of updates
   */
  /*              %could be improved in the future.  */
  /*              %obj.ps_pre.t_p; %tp doesn't change. We assume it is
   * stationary */
  /*               */
  /*              if numel(pulselist)==1% Happens if K=1 */
  /*                  %We only have one pulse to reference, so we need to check
   */
  /*                  %the prior pulse too.  */
  /*                  if ~isempty(obj.ps_pre.pl) &&
   * ~isnan(obj.ps_pre.pl(end).t_0) */
  /*                      recent_tip = pulselist.t_0-obj.ps_pre.pl(end).t_0; */
  /*                      %There could be a case where the last segment and this
   */
  /*                      %segement identified the same pulse. In this case */
  /*                      %recent_tip will be very small. In this case, we just
   */
  /*                      %say we learned nothing about t_ip in this segment. */
  /*                      if recent_tip < obj.ps_pre.t_ipu + obj.ps_pre.t_ipJ */
  /*                          recent_tip = NaN; */
  /*                      end */
  /*                  else */
  /*                      %No new information because we don't know the last  */
  /*                      %pulse time */
  /*                      recent_tip = NaN; */
  /*                  end */
  /*              else */
  /*                  recent_tip = diff(t_found); */
  /*              end */
  /*              %Do a check here to make sure the new tip isn't a huge change.
   */
  /*              %This could potentially happen if we are in the K = 1 case and
   */
  /*              %the block getting processed contained two pulses, with the */
  /*              %latter pulse getting identified/detected. The lines above */
  /*              %would look back to the last identified pulse and it might be
   */
  /*              %2*tip back in time, producing a very large recenttip values.
   */
  /*              %If something like this happens, we ignore it so it doesn't */
  /*              %affect our new tip estimates.  */
  /*              if recent_tip > 1.5*obj.ps_pre.t_ip & recent_tip <
   * 0.5*obj.ps_pre.t_ip */
  /*                  recent_tip = NaN; */
  /*              end */
  /*               */
  /*              %Only update time parameters if we are in tracking mode. If we
   */
  /*              %aren't, we may have identified somethign that isn't a pulse
   */
  /*              if strcmp(obj.ps_pos.mode,'T') || strcmp(obj.ps_pre.mode,'T')
   */
  /*                  obj.ps_pos.t_ip  =
   * mean([recent_tip;obj.ps_pre.t_ip],'omitnan'); */
  /*                  obj.ps_pos.t_ipu = obj.ps_pre.t_ipu; %Don't update this
   * because it can get too
   * narrow.%mean([3*std(diff(t_found));obj.ps_pre.t_ipu]); */
  /*                  obj.ps_pos.t_ipj = obj.ps_pre.t_ipj; */
  /*              end */
  /*              fp_pos           =
   * freq_found;%nanmean([freq_found;obj.ps_pre.fp]);%Previous fc may be nan if
   * unknown */
  /*              obj.ps_pos.fp    = fp_pos; */
  /*              obj.ps_pos.fstart = fp_pos-bw_found/2; */
  /*              obj.ps_pos.fend   = fp_pos+bw_found/2; */
  /*               */
  /*              obj.ps_pos.psdHist = obj.stft.psd */
  /*          end */
  /* Samples per pulse */
  /* Number of elements in STFT window */
  /* Number of elements overlap in STFT window */
  /* Number of elements in each step of STFT */
  /* Time of each step of STFT */
  /* Samples per pulse */
  /* Number of elements in STFT window */
  /* Number of elements overlap in STFT window */
  /* Number of elements in each step of STFT */
  /* Time of each step of STFT */
  /* Samples of interpulse duration */
  /* Baseline interpulse duration in units of STFT windows */
  /* Interpulse duration deviation from baselines in units of STFT windows */
  /* Amount of deviation from the PRI means to search */
  /*              if K ~= 1 */
  /*                  samplesforKpulses = n_ws*(K*(N+M)-2*M)+n_ol; */
  /*              else */
  /*                  samplesforKpulses = n_ws*(N+M+J+1)+n_ol; */
  /*              end */
  /* See 2022-07-11 for updates to samples def */
  /* obj.t_nextsegstart  = obj.t_0+(samplesforKpulses)/obj.Fs; %Don't need the
   * overlap here since the next segment starts at samplesforKpulses+n_ol-n_ol
   * from current sample */
  /* Don't need the overlap here since the next segment starts at
   * samplesforKpulses+n_ol-n_ol from current sample */
  /*              if isempty(obj.TimeCorr) */
  /*                  obj.TimeCorr = TemporalCorrelator(N, M, J); */
  /*              else */
  /*                  obj.TimeCorr.update(N, M, J); */
  /*              end */
  /* end */
  /* X0.ps_pre = ps_pre; */
  /* SETPRIORIDEPENDENTVARS updates the properties in the */
  /* waveform that are dependent on properties in a pulsestats */
  /* object.  */
  /*  */
  /* INPUTS:   */
  /*    obj     waveform object */
  /*    ps_obj  a pulse stats object */
  /* OUTPUTS:  */
  /*    None (This method modifies the waveform object properties)  */
  /*  */
  /*             %% */
  /* GETPRIORIDEPENDENTVARS returns the properties in the */
  /* waveform that are dependent on prior pulse data estimates. It */
  /* depends on the waveform properties list Fs etc, as well as */
  /* pulse stats like t_ip, etc. */
  /* INPUTS:  ps_obj  1x1 pulse stats object */
  /* OUTPUTS:  pulse stats object */
  /* WHAT WAS DONE BY THIS METHOD IS NOW DONE BY A METHOD OF THE */
  /* PULSESTATS CLASS.  */
  /*          function [] = update_posteriori(obj,pulselist) */
  /*              %UPDATE_POSTERIORI updates the posteriori pulse statistics of
   */
  /*              %this waveform object using the new pulse list (input) and the
   */
  /*              %apriori stats. The pulse contained in the waveform's ps_pos
   */
  /*              %property is not used directly so that the caller can decide
   */
  /*              %which pulses on which to focus the posteriori.  */
  /*               */
  /*              t_found    = [pulselist(:).t_0]'; */
  /*              freq_found = mean([pulselist(:).fp],'omitnan'); */
  /*               */
  /*              %Create a vector of bandwidths from the pulselist */
  /*              bw_found =
   * 2*(mean([pulselist.fend],'omitnan')-mean([pulselist.fstart],'omitnan')); */
  /*              if isempty(bw_found) */
  /*                  bw_found = 100; */
  /*                  if coder.target('MATLAB') */
  /*                      warning(['UAV-R: No bandwidth could be calculated
   * ',...  */
  /*                           'from the start and stop frequencies of the ',...
   */
  /*                           'identified pulses. A bandwidth of 100 Hz ',...
   */
  /*                           'will be used for continued informed search.'])
   */
  /*                  end */
  /*              end */
  /*               */
  /*              %Here is where we update the stats. These methods of updates
   */
  /*              %could be improved in the future.  */
  /*              %obj.ps_pre.t_p; %tp doesn't change. We assume it is
   * stationary */
  /*               */
  /*              if numel(pulselist)==1% Happens if K=1 */
  /*                  %We only have one pulse to reference, so we need to check
   */
  /*                  %the prior pulse too.  */
  /*                  if ~isempty(obj.ps_pre.pl) &&
   * ~isnan(obj.ps_pre.pl(end).t_0) */
  /*                      recent_tip = pulselist.t_0-obj.ps_pre.pl(end).t_0; */
  /*                      %There could be a case where the last segment and this
   */
  /*                      %segement identified the same pulse. In this case */
  /*                      %recent_tip will be very small. In this case, we just
   */
  /*                      %say we learned nothing about t_ip in this segment. */
  /*                      if recent_tip < obj.ps_pre.t_ipu + obj.ps_pre.t_ipJ */
  /*                          recent_tip = NaN; */
  /*                      end */
  /*                  else */
  /*                      %No new information because we don't know the last  */
  /*                      %pulse time */
  /*                      recent_tip = NaN; */
  /*                  end */
  /*              else */
  /*                  recent_tip = diff(t_found); */
  /*              end */
  /*              %Do a check here to make sure the new tip isn't a huge change.
   */
  /*              %This could potentially happen if we are in the K = 1 case and
   */
  /*              %the block getting processed contained two pulses, with the */
  /*              %latter pulse getting identified/detected. The lines above */
  /*              %would look back to the last identified pulse and it might be
   */
  /*              %2*tip back in time, producing a very large recenttip values.
   */
  /*              %If something like this happens, we ignore it so it doesn't */
  /*              %affect our new tip estimates.  */
  /*              if recent_tip > 1.5*obj.ps_pre.t_ip & recent_tip <
   * 0.5*obj.ps_pre.t_ip */
  /*                  recent_tip = NaN; */
  /*              end */
  /*               */
  /*              %Only update time parameters if we are in tracking mode. If we
   */
  /*              %aren't, we may have identified somethign that isn't a pulse
   */
  /*              if strcmp(obj.ps_pos.mode,'T') || strcmp(obj.ps_pre.mode,'T')
   */
  /*                  obj.ps_pos.t_ip  =
   * mean([recent_tip;obj.ps_pre.t_ip],'omitnan'); */
  /*                  obj.ps_pos.t_ipu = obj.ps_pre.t_ipu; %Don't update this
   * because it can get too
   * narrow.%mean([3*std(diff(t_found));obj.ps_pre.t_ipu]); */
  /*                  obj.ps_pos.t_ipj = obj.ps_pre.t_ipj; */
  /*              end */
  /*              fp_pos           =
   * freq_found;%nanmean([freq_found;obj.ps_pre.fp]);%Previous fc may be nan if
   * unknown */
  /*              obj.ps_pos.fp    = fp_pos; */
  /*              obj.ps_pos.fstart = fp_pos-bw_found/2; */
  /*              obj.ps_pos.fend   = fp_pos+bw_found/2; */
  /*               */
  /*              obj.ps_pos.psdHist = obj.stft.psd */
  /*          end */
  /* Samples per pulse */
  /* Number of elements in STFT window */
  /* Number of elements overlap in STFT window */
  /* Number of elements in each step of STFT */
  /* Time of each step of STFT */
  /* Samples per pulse */
  /* Number of elements in STFT window */
  /* Number of elements overlap in STFT window */
  /* Number of elements in each step of STFT */
  /* Time of each step of STFT */
  /* Samples of interpulse duration */
  /* Baseline interpulse duration in units of STFT windows */
  /* Interpulse duration deviation from baselines in units of STFT windows */
  /* Amount of deviation from the PRI means to search */
  /*              if K ~= 1 */
  /*                  samplesforKpulses = n_ws*(K*(N+M)-2*M)+n_ol; */
  /*              else */
  /*                  samplesforKpulses = n_ws*(N+M+J+1)+n_ol; */
  /*              end */
  /* See 2022-07-11 for updates to samples def */
  /* obj.t_nextsegstart  = obj.t_0+(samplesforKpulses)/obj.Fs; %Don't need the
   * overlap here since the next segment starts at samplesforKpulses+n_ol-n_ol
   * from current sample */
  /* Don't need the overlap here since the next segment starts at
   * samplesforKpulses+n_ol-n_ol from current sample */
  /*              if isempty(obj.TimeCorr) */
  /*                  obj.TimeCorr = TemporalCorrelator(N, M, J); */
  /*              else */
  /*                  obj.TimeCorr.update(N, M, J); */
  /*              end */
  /* GETPRIORIDEPENDENTVARS returns the properties in the */
  /* waveform that are dependent on prior pulse data estimates. It */
  /* depends on the waveform properties list Fs etc, as well as */
  /* pulse stats like t_ip, etc. */
  /* INPUTS:  ps_obj  1x1 pulse stats object */
  /* OUTPUTS:  pulse stats object */
  /* WHAT WAS DONE BY THIS METHOD IS NOW DONE BY A METHOD OF THE */
  /* PULSESTATS CLASS.  */
  /*          function [] = update_posteriori(obj,pulselist) */
  /*              %UPDATE_POSTERIORI updates the posteriori pulse statistics of
   */
  /*              %this waveform object using the new pulse list (input) and the
   */
  /*              %apriori stats. The pulse contained in the waveform's ps_pos
   */
  /*              %property is not used directly so that the caller can decide
   */
  /*              %which pulses on which to focus the posteriori.  */
  /*               */
  /*              t_found    = [pulselist(:).t_0]'; */
  /*              freq_found = mean([pulselist(:).fp],'omitnan'); */
  /*               */
  /*              %Create a vector of bandwidths from the pulselist */
  /*              bw_found =
   * 2*(mean([pulselist.fend],'omitnan')-mean([pulselist.fstart],'omitnan')); */
  /*              if isempty(bw_found) */
  /*                  bw_found = 100; */
  /*                  if coder.target('MATLAB') */
  /*                      warning(['UAV-R: No bandwidth could be calculated
   * ',...  */
  /*                           'from the start and stop frequencies of the ',...
   */
  /*                           'identified pulses. A bandwidth of 100 Hz ',...
   */
  /*                           'will be used for continued informed search.'])
   */
  /*                  end */
  /*              end */
  /*               */
  /*              %Here is where we update the stats. These methods of updates
   */
  /*              %could be improved in the future.  */
  /*              %obj.ps_pre.t_p; %tp doesn't change. We assume it is
   * stationary */
  /*               */
  /*              if numel(pulselist)==1% Happens if K=1 */
  /*                  %We only have one pulse to reference, so we need to check
   */
  /*                  %the prior pulse too.  */
  /*                  if ~isempty(obj.ps_pre.pl) &&
   * ~isnan(obj.ps_pre.pl(end).t_0) */
  /*                      recent_tip = pulselist.t_0-obj.ps_pre.pl(end).t_0; */
  /*                      %There could be a case where the last segment and this
   */
  /*                      %segement identified the same pulse. In this case */
  /*                      %recent_tip will be very small. In this case, we just
   */
  /*                      %say we learned nothing about t_ip in this segment. */
  /*                      if recent_tip < obj.ps_pre.t_ipu + obj.ps_pre.t_ipJ */
  /*                          recent_tip = NaN; */
  /*                      end */
  /*                  else */
  /*                      %No new information because we don't know the last  */
  /*                      %pulse time */
  /*                      recent_tip = NaN; */
  /*                  end */
  /*              else */
  /*                  recent_tip = diff(t_found); */
  /*              end */
  /*              %Do a check here to make sure the new tip isn't a huge change.
   */
  /*              %This could potentially happen if we are in the K = 1 case and
   */
  /*              %the block getting processed contained two pulses, with the */
  /*              %latter pulse getting identified/detected. The lines above */
  /*              %would look back to the last identified pulse and it might be
   */
  /*              %2*tip back in time, producing a very large recenttip values.
   */
  /*              %If something like this happens, we ignore it so it doesn't */
  /*              %affect our new tip estimates.  */
  /*              if recent_tip > 1.5*obj.ps_pre.t_ip & recent_tip <
   * 0.5*obj.ps_pre.t_ip */
  /*                  recent_tip = NaN; */
  /*              end */
  /*               */
  /*              %Only update time parameters if we are in tracking mode. If we
   */
  /*              %aren't, we may have identified somethign that isn't a pulse
   */
  /*              if strcmp(obj.ps_pos.mode,'T') || strcmp(obj.ps_pre.mode,'T')
   */
  /*                  obj.ps_pos.t_ip  =
   * mean([recent_tip;obj.ps_pre.t_ip],'omitnan'); */
  /*                  obj.ps_pos.t_ipu = obj.ps_pre.t_ipu; %Don't update this
   * because it can get too
   * narrow.%mean([3*std(diff(t_found));obj.ps_pre.t_ipu]); */
  /*                  obj.ps_pos.t_ipj = obj.ps_pre.t_ipj; */
  /*              end */
  /*              fp_pos           =
   * freq_found;%nanmean([freq_found;obj.ps_pre.fp]);%Previous fc may be nan if
   * unknown */
  /*              obj.ps_pos.fp    = fp_pos; */
  /*              obj.ps_pos.fstart = fp_pos-bw_found/2; */
  /*              obj.ps_pos.fend   = fp_pos+bw_found/2; */
  /*               */
  /*              obj.ps_pos.psdHist = obj.stft.psd */
  /*          end */
  a__2 = ceil(ps_input->t_p * X0_Fs);
  /* Samples per pulse */
  /* Number of elements in STFT window */
  n_ol = floor(stftOverlapFraction->contents * a__2);
  /* Number of elements overlap in STFT window */
  n_ws = a__2 - n_ol;
  /* Number of elements in each step of STFT */
  /* Time of each step of STFT */
  N = floor(ceil(ps_input->t_ip * X0_Fs) / n_ws);
  M = ceil(ceil(ps_input->t_ipu * X0_Fs) / n_ws);
  a__2 = ceil(ceil(ps_input->t_ipj * X0_Fs) / n_ws);
  /*          overlapWindows  = 2*Config.K*M+1; */
  /*          overlapSamples	= n_ws*overlapWindows; */
  /*          %sampsForKPulses = Config.K*n_ws*(N+M+1+1); */
  /*          sampsForKPulses = n_ws*(Config.K*(N+M)+1+1); */
  overlapSamples->contents = n_ws * (2.0 * (Config->contents.K * M + a__2));
  /*          if Config.K~=1 */
  /*              sampsForKPulses = n_ws*(Config.K*(N+M)-2*M)+n_ol; */
  /*          else */
  /*              sampsForKPulses = n_ws*(N+M+J)+n_ol; */
  /*          end */
  /* See 2022-07-11 for updates to samples def */
  sampsForKPulses->contents =
      n_ws * ((Config->contents.K * (N + M) + a__2) + 1.0) + n_ol;
  if (N < 4.294967296E+9) {
    if (N >= 0.0) {
      u = (unsigned int)N;
    } else {
      u = 0U;
    }
  } else if (N >= 4.294967296E+9) {
    u = MAX_uint32_T;
  } else {
    u = 0U;
  }
  if (M < 4.294967296E+9) {
    if (M >= 0.0) {
      u1 = (unsigned int)M;
    } else {
      u1 = 0U;
    }
  } else if (M >= 4.294967296E+9) {
    u1 = MAX_uint32_T;
  } else {
    u1 = 0U;
  }
  if (a__2 < 4.294967296E+9) {
    if (a__2 >= 0.0) {
      u2 = (unsigned int)a__2;
    } else {
      u2 = 0U;
    }
  } else if (a__2 >= 4.294967296E+9) {
    u2 = MAX_uint32_T;
  } else {
    u2 = 0U;
  }
  printf("Updating buffer read vars|| N: %u, M: %u, J: %u,\n", u, u1, u2);
  fflush(stdout);
  a__2 = rt_roundd_snf(sampsForKPulses->contents);
  if (a__2 < 4.294967296E+9) {
    if (a__2 >= 0.0) {
      u = (unsigned int)a__2;
    } else {
      u = 0U;
    }
  } else if (a__2 >= 4.294967296E+9) {
    u = MAX_uint32_T;
  } else {
    u = 0U;
  }
  a__2 = rt_roundd_snf(overlapSamples->contents);
  if (a__2 < 4.294967296E+9) {
    if (a__2 >= 0.0) {
      u1 = (unsigned int)a__2;
    } else {
      u1 = 0U;
    }
  } else if (a__2 >= 4.294967296E+9) {
    u1 = MAX_uint32_T;
  } else {
    u1 = 0U;
  }
  printf(
      "Updating buffer read vars|| sampForKPulses: %u,  overlapSamples: %u,\n",
      u, u1);
  fflush(stdout);
  emxFreeStruct_pulsestats(&lobj_2);
}

/*
 * Add code here to update the variables within the function that are
 * part of the configuration file. Will first need to load the correct
 * file and
 *
 *
 * Arguments    : c_captured_var *Config
 *                const b_captured_var *configPath
 * Return Type  : void
 */
static void updateconfig(c_captured_var *Config,
                         const b_captured_var *configPath)
{
  static const char b_cv1[20] = {'c', 'h', 'a', 'n', 'n', 'e', 'l',
                                 'C', 'e', 'n', 't', 'e', 'r', 'F',
                                 'r', 'e', 'q', 'M', 'H', 'z'};
  static const char cv7[10] = {'t', 'a', 'g', 'F', 'r',
                               'e', 'q', 'M', 'H', 'z'};
  static const char cv5[9] = {'p', 'o', 'r', 't', 'C', 'n', 't', 'r', 'l'};
  static const char b_cv3[8] = {'p', 'o', 'r', 't', 'D', 'a', 't', 'a'};
  static const char cv4[7] = {'i', 'p', 'C', 'n', 't', 'r', 'l'};
  static const char b_cv2[6] = {'i', 'p', 'D', 'a', 't', 'a'};
  static const char b_cv[2] = {'I', 'D'};
  static const char cv6[2] = {'F', 's'};
  FILE *b_NULL;
  FILE *filestar;
  int st;
  emxArray_boolean_T *b_lineStr;
  emxArray_char_T *configType;
  emxArray_char_T *configValStr;
  emxArray_char_T *lineStr;
  emxArray_creal_T *r;
  emxArray_int32_T *match_out;
  emxArray_int32_T *matches;
  emxArray_real_T *sepByte;
  emxArray_real_T *val;
  emxArray_uint32_T *tabLocs;
  creal_T *r1;
  double configNum;
  double d;
  double *sepByte_data;
  double *val_data;
  int colonLocation_data;
  int i;
  int loop_ub;
  int text_len;
  int *match_out_data;
  int *matches_data;
  unsigned int *tabLocs_data;
  signed char fileid;
  char *configType_data;
  char *lineStr_data;
  bool a;
  bool done;
  bool *b_lineStr_data;
  DetectorConfig_DetectorConfig(
      &Config->contents.channelCenterFreqMHz, &Config->contents.portData,
      &Config->contents.portCntrl, &Config->contents.Fs,
      &Config->contents.tagFreqMHz, &Config->contents.tp, &Config->contents.tip,
      &Config->contents.tipu, &Config->contents.tipj, &Config->contents.K,
      Config->contents.opMode.Value, Config->contents.excldFreqs,
      &Config->contents.falseAlarmProb, Config->contents.dataRecordPath.Value);
  /* fillFromFile Replaces the properties of the instance passed to */
  /* it with the values specified in the configuration file passed */
  /* to the function. If multiple entries exist in the config file, */
  /* use the 'entry' argument to specify which entry to use (1-n). */
  /* If entry is not specified, the method will use the last entry */
  /* in the config file.  */
  /*  */
  /* INPUTS: */
  /*    filePath        String of full path to config file,  */
  /*                    including the file name and extension */
  /*                     */
  /*    entry           Scalar number (1-n) of which entry to use. */
  /*                    Method will use the last entry if entry is */
  /*                    not provided. Alternatively, enter -1 to  */
  /*                    use last entry. */
  /*  */
  /* OUTPUTS: */
  /*    none (method modifies the properties of the instance) */
  /*  */
  fileid = cfopen(configPath->contents.Value);
  configNum = 0.0;
  done = false;
  /* coder.varsize('sepLine') */
  emxInit_real_T(&sepByte, 2);
  i = sepByte->size[0] * sepByte->size[1];
  sepByte->size[0] = 1;
  sepByte->size[1] = 1;
  emxEnsureCapacity_real_T(sepByte, i);
  sepByte_data = sepByte->data;
  sepByte_data[0] = 0.0;
  /* First figure out where the separator lines are */
  emxInit_char_T(&lineStr);
  while (!done) {
    /* currByte = ftell(fid); */
    fgetl(fileid, lineStr);
    lineStr_data = lineStr->data;
    if (lineStr_data[0] == '#') {
      /* && lineNum~=1 */
      if (configNum == 0.0) {
        i = sepByte->size[0] * sepByte->size[1];
        sepByte->size[0] = 1;
        sepByte->size[1] = 1;
        emxEnsureCapacity_real_T(sepByte, i);
        sepByte_data = sepByte->data;
        d = b_ftell(fileid);
        sepByte_data[0] = d;
      } else {
        /* sepByte(configNum) = ftell(fid); */
        d = b_ftell(fileid);
        i = sepByte->size[1];
        colonLocation_data = sepByte->size[0] * sepByte->size[1];
        sepByte->size[0] = 1;
        sepByte->size[1]++;
        emxEnsureCapacity_real_T(sepByte, colonLocation_data);
        sepByte_data = sepByte->data;
        sepByte_data[i] = d;
        /* Modified for Coder compatibility */
      }
      configNum++;
    }
    b_NULL = NULL;
    getfilestar(fileid, &filestar, &a);
    if (filestar == b_NULL) {
      text_len = 0;
    } else {
      st = feof(filestar);
      text_len = ((int)st != 0);
    }
    done = (text_len == 1);
  }
  /* sepByte(configNum) = ftell(fid); */
  d = b_ftell(fileid);
  i = sepByte->size[1];
  colonLocation_data = sepByte->size[0] * sepByte->size[1];
  sepByte->size[0] = 1;
  sepByte->size[1]++;
  emxEnsureCapacity_real_T(sepByte, colonLocation_data);
  sepByte_data = sepByte->data;
  sepByte_data[i] = d;
  /* Modified for Coder compatibility */
  /* Jump to the line for the entry requested */
  b_fseek(fileid, sepByte_data[(int)configNum - 1]);
  done = false;
  emxInit_uint32_T(&tabLocs);
  tabLocs_data = tabLocs->data;
  emxInit_char_T(&configType);
  emxInit_char_T(&configValStr);
  emxInit_int32_T(&match_out, 2);
  emxInit_int32_T(&matches, 2);
  emxInit_real_T(&val, 2);
  emxInit_creal_T(&r, 2);
  emxInit_boolean_T(&b_lineStr, 2);
  while (!done) {
    fgetl(fileid, lineStr);
    lineStr_data = lineStr->data;
    if (lineStr_data[0] != '#') {
      int exitg1;
      int match_idx;
      i = b_lineStr->size[0] * b_lineStr->size[1];
      b_lineStr->size[0] = 1;
      b_lineStr->size[1] = lineStr->size[1];
      emxEnsureCapacity_boolean_T(b_lineStr, i);
      b_lineStr_data = b_lineStr->data;
      loop_ub = lineStr->size[1];
      for (i = 0; i < loop_ub; i++) {
        b_lineStr_data[i] = (lineStr_data[i] == ':');
      }
      int colonLocation_size[2];
      eml_find(b_lineStr, (int *)&colonLocation_data, colonLocation_size);
      /* note regexp is not supported for code generation */
      if (lineStr->size[1] == 0) {
        tabLocs->size[0] = 1;
        tabLocs->size[1] = 0;
      } else {
        text_len = lineStr->size[1];
        i = matches->size[0] * matches->size[1];
        matches->size[0] = 1;
        matches->size[1] = lineStr->size[1];
        emxEnsureCapacity_int32_T(matches, i);
        matches_data = matches->data;
        match_idx = 0;
        for (loop_ub = 0; loop_ub < text_len; loop_ub++) {
          if (lineStr_data[loop_ub] == '\x09') {
            matches_data[match_idx] = loop_ub + 1;
            match_idx++;
          }
        }
        i = match_out->size[0] * match_out->size[1];
        match_out->size[0] = 1;
        match_out->size[1] = match_idx;
        emxEnsureCapacity_int32_T(match_out, i);
        match_out_data = match_out->data;
        for (loop_ub = 0; loop_ub < match_idx; loop_ub++) {
          match_out_data[loop_ub] = matches_data[loop_ub];
        }
        i = tabLocs->size[0] * tabLocs->size[1];
        tabLocs->size[0] = 1;
        tabLocs->size[1] = match_out->size[1];
        emxEnsureCapacity_uint32_T(tabLocs, i);
        tabLocs_data = tabLocs->data;
        loop_ub = match_out->size[1];
        for (i = 0; i < loop_ub; i++) {
          tabLocs_data[i] = (unsigned int)match_out_data[i];
        }
      }
      /* Thanks to
       * https://www.mathworks.com/matlabcentral/answers/529668-how-do-i-detect-a-tab-character-in-a-line-of-text-read-by-fgetl
       */
      /* note regexp is not supported for code generation */
      if ((double)colonLocation_data - 1.0 < 1.0) {
        loop_ub = 0;
      } else {
        loop_ub = colonLocation_data - 1;
      }
      i = configType->size[0] * configType->size[1];
      configType->size[0] = 1;
      configType->size[1] = loop_ub;
      emxEnsureCapacity_char_T(configType, i);
      configType_data = configType->data;
      for (i = 0; i < loop_ub; i++) {
        configType_data[i] = lineStr_data[i];
      }
      if (tabLocs_data[0] + 1U > (unsigned int)lineStr->size[1]) {
        i = 0;
        colonLocation_data = 0;
      } else {
        i = (int)tabLocs_data[0];
        colonLocation_data = lineStr->size[1];
      }
      text_len = configValStr->size[0] * configValStr->size[1];
      configValStr->size[0] = 1;
      match_idx = colonLocation_data - i;
      configValStr->size[1] = match_idx;
      emxEnsureCapacity_char_T(configValStr, text_len);
      configType_data = configValStr->data;
      for (colonLocation_data = 0; colonLocation_data < match_idx;
           colonLocation_data++) {
        configType_data[colonLocation_data] =
            lineStr_data[i + colonLocation_data];
      }
      a = false;
      if (loop_ub == 2) {
        text_len = 0;
        do {
          exitg1 = 0;
          if (text_len < 2) {
            if (lineStr_data[text_len] != b_cv[text_len]) {
              exitg1 = 1;
            } else {
              text_len++;
            }
          } else {
            a = true;
            exitg1 = 1;
          }
        } while (exitg1 == 0);
      }
      if (!a) {
        a = false;
        if (loop_ub == 20) {
          text_len = 0;
          do {
            exitg1 = 0;
            if (text_len < 20) {
              if (lineStr_data[text_len] != b_cv1[text_len]) {
                exitg1 = 1;
              } else {
                text_len++;
              }
            } else {
              a = true;
              exitg1 = 1;
            }
          } while (exitg1 == 0);
        }
        if (a) {
          creal_T dc;
          dc = str2double(configValStr);
          Config->contents.channelCenterFreqMHz = dc.re;
        } else {
          a = false;
          if (loop_ub == 6) {
            text_len = 0;
            do {
              exitg1 = 0;
              if (text_len < 6) {
                if (lineStr_data[text_len] != b_cv2[text_len]) {
                  exitg1 = 1;
                } else {
                  text_len++;
                }
              } else {
                a = true;
                exitg1 = 1;
              }
            } while (exitg1 == 0);
          }
          if (!a) {
            a = false;
            if (loop_ub == 8) {
              text_len = 0;
              do {
                exitg1 = 0;
                if (text_len < 8) {
                  if (lineStr_data[text_len] != b_cv3[text_len]) {
                    exitg1 = 1;
                  } else {
                    text_len++;
                  }
                } else {
                  a = true;
                  exitg1 = 1;
                }
              } while (exitg1 == 0);
            }
            if (a) {
              creal_T dc;
              unsigned short in;
              dc = str2double(configValStr);
              d = rt_roundd_snf(dc.re);
              if (d < 65536.0) {
                if (d >= 0.0) {
                  in = (unsigned short)d;
                } else {
                  in = 0U;
                }
              } else if (d >= 65536.0) {
                in = MAX_uint16_T;
              } else {
                in = 0U;
              }
              Config->contents.portData = in;
            } else {
              a = false;
              if (loop_ub == 7) {
                text_len = 0;
                do {
                  exitg1 = 0;
                  if (text_len < 7) {
                    if (lineStr_data[text_len] != cv4[text_len]) {
                      exitg1 = 1;
                    } else {
                      text_len++;
                    }
                  } else {
                    a = true;
                    exitg1 = 1;
                  }
                } while (exitg1 == 0);
              }
              if (!a) {
                a = false;
                if (loop_ub == 9) {
                  text_len = 0;
                  do {
                    exitg1 = 0;
                    if (text_len < 9) {
                      if (lineStr_data[text_len] != cv5[text_len]) {
                        exitg1 = 1;
                      } else {
                        text_len++;
                      }
                    } else {
                      a = true;
                      exitg1 = 1;
                    }
                  } while (exitg1 == 0);
                }
                if (a) {
                  creal_T dc;
                  unsigned short in;
                  dc = str2double(configValStr);
                  d = rt_roundd_snf(dc.re);
                  if (d < 65536.0) {
                    if (d >= 0.0) {
                      in = (unsigned short)d;
                    } else {
                      in = 0U;
                    }
                  } else if (d >= 65536.0) {
                    in = MAX_uint16_T;
                  } else {
                    in = 0U;
                  }
                  Config->contents.portCntrl = in;
                } else {
                  a = false;
                  if (loop_ub == 2) {
                    text_len = 0;
                    do {
                      exitg1 = 0;
                      if (text_len < 2) {
                        if (lineStr_data[text_len] != cv6[text_len]) {
                          exitg1 = 1;
                        } else {
                          text_len++;
                        }
                      } else {
                        a = true;
                        exitg1 = 1;
                      }
                    } while (exitg1 == 0);
                  }
                  if (a) {
                    creal_T dc;
                    dc = str2double(configValStr);
                    Config->contents.Fs = dc.re;
                  } else {
                    a = false;
                    if (loop_ub == 10) {
                      text_len = 0;
                      do {
                        exitg1 = 0;
                        if (text_len < 10) {
                          if (lineStr_data[text_len] != cv7[text_len]) {
                            exitg1 = 1;
                          } else {
                            text_len++;
                          }
                        } else {
                          a = true;
                          exitg1 = 1;
                        }
                      } while (exitg1 == 0);
                    }
                    if (a) {
                      creal_T dc;
                      dc = str2double(configValStr);
                      Config->contents.tagFreqMHz = dc.re;
                    } else if (h_strcmp(configType)) {
                      creal_T dc;
                      dc = str2double(configValStr);
                      Config->contents.tp = dc.re;
                    } else if (i_strcmp(configType)) {
                      creal_T dc;
                      dc = str2double(configValStr);
                      Config->contents.tip = dc.re;
                    } else if (j_strcmp(configType)) {
                      creal_T dc;
                      dc = str2double(configValStr);
                      Config->contents.tipu = dc.re;
                    } else if (k_strcmp(configType)) {
                      creal_T dc;
                      dc = str2double(configValStr);
                      Config->contents.tipj = dc.re;
                    } else {
                      a = false;
                      if ((loop_ub == 1) && (lineStr_data[0] == 'K')) {
                        a = true;
                      }
                      if (a) {
                        creal_T dc;
                        unsigned char b_in;
                        dc = str2double(configValStr);
                        d = rt_roundd_snf(dc.re);
                        if (d < 256.0) {
                          if (d >= 0.0) {
                            b_in = (unsigned char)d;
                          } else {
                            b_in = 0U;
                          }
                        } else if (d >= 256.0) {
                          b_in = MAX_uint8_T;
                        } else {
                          b_in = 0U;
                        }
                        Config->contents.K = b_in;
                      } else if (l_strcmp(configType)) {
                        colonLocation_data =
                            configType->size[0] * configType->size[1];
                        configType->size[0] = 1;
                        configType->size[1] = match_idx;
                        emxEnsureCapacity_char_T(configType,
                                                 colonLocation_data);
                        configType_data = configType->data;
                        for (colonLocation_data = 0;
                             colonLocation_data < match_idx;
                             colonLocation_data++) {
                          configType_data[colonLocation_data] =
                              lineStr_data[i + colonLocation_data];
                        }
                        i = Config->contents.opMode.Value->size[0] *
                            Config->contents.opMode.Value->size[1];
                        Config->contents.opMode.Value->size[0] = 1;
                        Config->contents.opMode.Value->size[1] =
                            configType->size[1];
                        emxEnsureCapacity_char_T(Config->contents.opMode.Value,
                                                 i);
                        loop_ub = configType->size[1];
                        for (i = 0; i < loop_ub; i++) {
                          Config->contents.opMode.Value->data[i] =
                              configType_data[i];
                        }
                      } else if (m_strcmp(configType)) {
                        str2matrix(configValStr, r);
                        r1 = r->data;
                        i = val->size[0] * val->size[1];
                        val->size[0] = r->size[0];
                        val->size[1] = r->size[1];
                        emxEnsureCapacity_real_T(val, i);
                        val_data = val->data;
                        loop_ub = r->size[0] * r->size[1];
                        for (i = 0; i < loop_ub; i++) {
                          val_data[i] = r1[i].re;
                        }
                        if ((val->size[0] == 1) && (val->size[1] == 1)) {
                          i = Config->contents.excldFreqs->size[0] *
                              Config->contents.excldFreqs->size[1];
                          Config->contents.excldFreqs->size[0] = 1;
                          Config->contents.excldFreqs->size[1] = 2;
                          emxEnsureCapacity_real_T(Config->contents.excldFreqs,
                                                   i);
                          Config->contents.excldFreqs->data[0] = val_data[0];
                          Config->contents.excldFreqs->data[1] = val_data[0];
                        } else if (val->size[0] == 0) {
                          Config->contents.excldFreqs->size[0] = 0;
                          Config->contents.excldFreqs->size[1] = 2;
                        } else {
                          i = Config->contents.excldFreqs->size[0] *
                              Config->contents.excldFreqs->size[1];
                          Config->contents.excldFreqs->size[0] = val->size[0];
                          Config->contents.excldFreqs->size[1] = 2;
                          emxEnsureCapacity_real_T(Config->contents.excldFreqs,
                                                   i);
                          loop_ub = val->size[0] << 1;
                          for (i = 0; i < loop_ub; i++) {
                            Config->contents.excldFreqs->data[i] = val_data[i];
                          }
                        }
                      } else if (n_strcmp(configType)) {
                        creal_T dc;
                        dc = str2double(configValStr);
                        Config->contents.falseAlarmProb = dc.re;
                      } else if (o_strcmp(configType)) {
                        colonLocation_data =
                            configType->size[0] * configType->size[1];
                        configType->size[0] = 1;
                        configType->size[1] = match_idx;
                        emxEnsureCapacity_char_T(configType,
                                                 colonLocation_data);
                        configType_data = configType->data;
                        for (colonLocation_data = 0;
                             colonLocation_data < match_idx;
                             colonLocation_data++) {
                          configType_data[colonLocation_data] =
                              lineStr_data[i + colonLocation_data];
                        }
                        i = Config->contents.dataRecordPath.Value->size[0] *
                            Config->contents.dataRecordPath.Value->size[1];
                        Config->contents.dataRecordPath.Value->size[0] = 1;
                        Config->contents.dataRecordPath.Value->size[1] =
                            configType->size[1];
                        emxEnsureCapacity_char_T(
                            Config->contents.dataRecordPath.Value, i);
                        loop_ub = configType->size[1];
                        for (i = 0; i < loop_ub; i++) {
                          Config->contents.dataRecordPath.Value->data[i] =
                              configType_data[i];
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      /* Stop when we have finished reading this entry. */
      b_NULL = NULL;
      getfilestar(fileid, &filestar, &a);
      if (filestar == b_NULL) {
        text_len = 0;
      } else {
        st = feof(filestar);
        text_len = ((int)st != 0);
      }
      if ((text_len == 1) ||
          (b_ftell(fileid) == sepByte_data[(int)(unsigned int)configNum])) {
        done = true;
      }
    } else {
      b_NULL = NULL;
      getfilestar(fileid, &filestar, &a);
      if (filestar == b_NULL) {
        text_len = 0;
      } else {
        st = feof(filestar);
        text_len = ((int)st != 0);
      }
      if ((text_len == 1) ||
          (b_ftell(fileid) == sepByte_data[(int)(unsigned int)configNum])) {
        done = true;
      }
    }
  }
  emxFree_boolean_T(&b_lineStr);
  emxFree_creal_T(&r);
  emxFree_real_T(&val);
  emxFree_int32_T(&matches);
  emxFree_int32_T(&match_out);
  emxFree_char_T(&configValStr);
  emxFree_char_T(&configType);
  emxFree_uint32_T(&tabLocs);
  emxFree_char_T(&lineStr);
  emxFree_real_T(&sepByte);
  cfclose(fileid);
  /* Do we update the tip and tipu or use the ones that were adapted from */
  /* the previous detections? Probably just use the file. The supervisor */
  /* will have access to the detected pulses and can update these values if */
  /* it sees fit. */
}

/*
 * UNTITLED Summary of this function goes here
 *    Detailed explanation goes here
 *
 * Arguments    : void
 * Return Type  : void
 */
void uavrt_detection(void)
{
  static b_dsp_AsyncBuffer asyncWriteBuff;
  static c_dsp_AsyncBuffer asyncTimeBuff;
  static dsp_AsyncBuffer asyncDataBuff;
  static const char t7_Value[25] = {'c', 'o', 'n', 'f', 'i', 'g', '/', 'd', 'e',
                                    't', 'e', 'c', 't', 'o', 'r', 'C', 'o', 'n',
                                    'f', 'i', 'g', '.', 't', 'x', 't'};
  static const char b_cv[9] = {'u', 'n', 's', 'p', 'a', 'w', 'n', 'e', 'd'};
  b_captured_var configPath;
  b_struct_T expl_temp;
  b_struct_T r;
  b_struct_T *ps_pre_struc_clst_data;
  b_struct_T *ps_pre_struc_pl_data;
  b_waveform b_X;
  c_captured_var Config;
  captured_var overlapSamples;
  captured_var sampsForKPulses;
  captured_var stftOverlapFraction;
  emxArray_boolean_T b_tmp_data;
  emxArray_boolean_T *ps_pre_struc_cmsk;
  emxArray_boolean_T *r2;
  emxArray_boolean_T *r3;
  emxArray_boolean_T *r4;
  emxArray_boolean_T *varargin_1;
  emxArray_char_T *b_varargin_1;
  emxArray_creal32_T *dataWriterBuffData;
  emxArray_creal32_T *x;
  emxArray_int16_T *y;
  emxArray_real32_T b_dataMatrix;
  emxArray_real32_T *dataMatrix;
  emxArray_real_T *b_x;
  emxArray_real_T *ps_pre_struc_cpki;
  emxArray_real_T *r1;
  emxArray_real_T *t;
  emxArray_struct_T *ps_pre_struc_clst;
  emxArray_struct_T *ps_pre_struc_pl;
  pulsestats lobj_11[4];
  pulsestats lobj_21[2];
  pulsestats lobj_14;
  pulsestats lobj_16;
  pulsestats lobj_17;
  pulsestats lobj_18;
  pulsestats *pulseStatsPriori;
  threshold val;
  waveform X;
  waveform lobj_12;
  waveform lobj_20;
  waveform *Xhold;
  wfmstft lobj_19[3];
  wfmstft lobj_10;
  wfmstft lobj_13;
  wfmstft lobj_15;
  creal_T dcv[1000];
  creal32_T b_dataReceived_data[1025];
  creal32_T dataReceived_data[1025];
  creal32_T exampleData[1000];
  creal32_T *dataWriterBuffData_data;
  double ps_pre_struc_tmplt[2];
  double dataWriterSamples;
  double idleTic;
  double lastTimeStamp;
  double missingPackets;
  double missingTime;
  double ps_pre_struc_fend;
  double ps_pre_struc_fp;
  double ps_pre_struc_fstart;
  double ps_pre_struc_t_ip;
  double ps_pre_struc_t_ipj;
  double ps_pre_struc_t_ipu;
  double ps_pre_struc_t_p;
  double segmentsProcessed;
  double t8_fend;
  double t8_fp;
  double t8_fstart;
  double t8_t_0;
  double t8_t_f;
  double t8_yw;
  double timeStamp;
  double trackedCount;
  double *r5;
  double *t_data;
  float *dataMatrix_data;
  int state_size[2];
  int b_index;
  int i;
  int i1;
  int i2;
  int i3;
  int i4;
  int i5;
  int loop_ub;
  int previousState_size_idx_1;
  int tmp_size;
  short *y_data;
  signed char cmdReceived_data[1024];
  char previousState_data[64];
  char state_data[64];
  char state_tmp_data[64];
  signed char fileid;
  char mode;
  char suggestedMode;
  char *varargin_1_data;
  bool cleanBuffer;
  bool configUpdatedFlag;
  bool fLock;
  bool resetBuffersFlag;
  bool staleDataFlag;
  bool t8_con_dec;
  bool t8_det_dec;
  bool tmp_data;
  bool *ps_pre_struc_cmsk_data;
  bool *r6;
  if (!isInitialized_uavrt_detection) {
    uavrt_detection_initialize();
  }
  emxInitMatrix_pulsestats(lobj_21);
  emxInitStruct_waveform(&lobj_20);
  emxInitMatrix_wfmstft(lobj_19);
  emxInitStruct_pulsestats(&lobj_18);
  emxInitStruct_pulsestats(&lobj_17);
  emxInitStruct_pulsestats(&lobj_16);
  emxInitStruct_wfmstft(&lobj_15);
  emxInitStruct_pulsestats(&lobj_14);
  emxInitStruct_wfmstft(&lobj_13);
  emxInitStruct_waveform(&lobj_12);
  emxInitMatrix_pulsestats1(lobj_11);
  emxInitStruct_wfmstft(&lobj_10);
  emxInitStruct_waveform(&X);
  emxInitStruct_waveform1(&b_X);
  for (i = 0; i < 25; i++) {
    configPath.contents.Value[i] = t7_Value[i];
  }
  /* Must exist in the same directory as the execution of this executable */
  emxInitStruct_captured_var(&Config);
  DetectorConfig_DetectorConfig(
      &Config.contents.channelCenterFreqMHz, &Config.contents.portData,
      &Config.contents.portCntrl, &Config.contents.Fs,
      &Config.contents.tagFreqMHz, &Config.contents.tp, &Config.contents.tip,
      &Config.contents.tipu, &Config.contents.tipj, &Config.contents.K,
      Config.contents.opMode.Value, Config.contents.excldFreqs,
      &Config.contents.falseAlarmProb, Config.contents.dataRecordPath.Value);
  /* Build empty config object */
  updateconfig(&Config, &configPath);
  /* Update (fill) the configuration */
  configUpdatedFlag = true;
  emxInitStruct_struct_T(&r);
  makepulsestruc(&r.A, &r.P, &r.SNR, &r.yw, &r.t_0, &r.t_f, r.t_next, &r.fp,
                 &r.fstart, &r.fend, r.mode, &r.det_dec, &r.con_dec);
  emxInitStruct_struct_T(&expl_temp);
  makepulsestruc(&missingTime, &missingPackets, &timeStamp, &t8_yw, &t8_t_0,
                 &t8_t_f, expl_temp.t_next, &t8_fp, &t8_fstart, &t8_fend,
                 expl_temp.mode, &t8_det_dec, &t8_con_dec);
  expl_temp.con_dec = t8_con_dec;
  expl_temp.det_dec = t8_det_dec;
  expl_temp.fend = t8_fend;
  expl_temp.fstart = t8_fstart;
  expl_temp.fp = t8_fp;
  expl_temp.t_f = t8_t_f;
  expl_temp.t_0 = t8_t_0;
  expl_temp.yw = t8_yw;
  expl_temp.SNR = timeStamp;
  expl_temp.P = missingPackets;
  expl_temp.A = missingTime;
  pulseStatsPriori = pulsestats_pulsestats(
      &lobj_21[1], Config.contents.tp, Config.contents.tip,
      Config.contents.tipu, Config.contents.tipj, &r, &expl_temp);
  /*  % tp, tip, tipu */
  /*  % tipj, fp, fstart, fend, tmplt, mode */
  /*   % pl ,clst */
  /*  cmsk ,cpki) */
  stftOverlapFraction.contents = 0.5;
  /* Initialize and then set these variable needed for buffer reads */
  overlapSamples.contents = 0.0;
  sampsForKPulses.contents = 0.0;
  updatebufferreadvariables(&Config, &stftOverlapFraction, &overlapSamples,
                            &sampsForKPulses, pulseStatsPriori);
  /* 1024 plus a time stamp. */
  printf("Startup set 1 complete. \n");
  fflush(stdout);
  /*  Prepare data writing buffer */
  /*  Calculating the max size that would ever be needed for the buffer */
  /*  maxK    = 6; */
  /*  maxFs   = 912000/2; */
  /*  maxtp   = 0.04; */
  /*  maxtip  = 2; */
  /*  maxtipu = 0.1; */
  /*  maxpulseStatsPriori = pulsestats(maxtp,maxtip,maxtipu,[],[],[],[1
   * 1],pulse); */
  /*  Xmax = waveform([], maxFs, 0, maxpulseStatsPriori, stftOverlapFraction);
   */
  /*  [~,~,~,maxn_ws,~,~,maxN,maxM] = Xmax.getprioridependentprops(Xmax.ps_pre);
   */
  /*  sampsForMaxPulses = maxK*maxn_ws*(maxN+maxM+1+1); */
  asyncDataBuff.pBuffer.NumChannels = -1;
  asyncDataBuff.pBuffer.isInitialized = 0;
  asyncDataBuff.pBuffer.matlabCodegenIsDeleted = false;
  asyncDataBuff.matlabCodegenIsDeleted = false;
  asyncTimeBuff.pBuffer.NumChannels = -1;
  asyncTimeBuff.pBuffer.ReadPointer = 1;
  asyncTimeBuff.pBuffer.WritePointer = 2;
  asyncTimeBuff.pBuffer.isInitialized = 0;
  asyncTimeBuff.pBuffer.matlabCodegenIsDeleted = false;
  asyncTimeBuff.matlabCodegenIsDeleted = false;
  printf("Startup set 2 complete. \n");
  fflush(stdout);
  /* Write interval in seconds. 2.5*60*4000*32/8 should work out the 2.4Mb of
   * data at 4ksps. */
  dataWriterSamples = ceil(10.0 / (1024.0 / Config.contents.Fs)) * 1025.0;
  asyncWriteBuff.pBuffer.NumChannels = -1;
  asyncWriteBuff.pBuffer.isInitialized = 0;
  asyncWriteBuff.pBuffer.matlabCodegenIsDeleted = false;
  asyncWriteBuff.matlabCodegenIsDeleted = false;
  /* 600650 is the result of the nominal settings of ceil(150/(1024/4000)*1025.
   */
  AsyncBuffer_write(&asyncWriteBuff);
  /* Write to give Code the type. Read to remove data. */
  AsyncBuffer_read(&asyncWriteBuff);
  fileid = b_cfopen(Config.contents.dataRecordPath.Value);
  if (fileid == -1) {
    printf("UAV-RT: Error opening/creating data record file with error:\n");
    fflush(stdout);
  }
  printf("Startup set 3 complete. \n");
  fflush(stdout);
  /* Define a pulsestats structure that isn't an object. */
  /* This is needed for the loop, as Matlab coder has problems seeing */
  /* that the pulsestats handle object is set for all execution paths. */
  /* Holding all these properties in a structure rather than the */
  /* pulsestats object addressed this problem. */
  /* Needed to let coder know that some of these will be varying in size */
  /* https://www.mathworks.com/help/simulink/ug/how-working-with-matlab-classes-is-different-for-code-generation.html
   */
  mode = 'D';
  /* dims 0 if fixed, 1 if variable */
  printf("Startup set 4 complete. \n");
  fflush(stdout);
  ps_pre_struc_t_p = 0.0;
  ps_pre_struc_t_ip = 0.0;
  ps_pre_struc_t_ipu = 0.0;
  ps_pre_struc_t_ipj = 0.0;
  ps_pre_struc_fp = 0.0;
  ps_pre_struc_fstart = 0.0;
  ps_pre_struc_fend = 0.0;
  ps_pre_struc_tmplt[0] = 1.0;
  ps_pre_struc_tmplt[1] = 1.0;
  makepulsestruc(&r.A, &r.P, &r.SNR, &r.yw, &r.t_0, &r.t_f, r.t_next, &r.fp,
                 &r.fstart, &r.fend, r.mode, &r.det_dec, &r.con_dec);
  emxInit_struct_T(&ps_pre_struc_pl);
  i = ps_pre_struc_pl->size[0] * ps_pre_struc_pl->size[1];
  ps_pre_struc_pl->size[0] = 1;
  ps_pre_struc_pl->size[1] = 1;
  emxEnsureCapacity_struct_T(ps_pre_struc_pl, i);
  ps_pre_struc_pl_data = ps_pre_struc_pl->data;
  emxCopyStruct_struct_T(&ps_pre_struc_pl_data[0], &r);
  makepulsestruc(&r.A, &r.P, &r.SNR, &r.yw, &r.t_0, &r.t_f, r.t_next, &r.fp,
                 &r.fstart, &r.fend, r.mode, &r.det_dec, &r.con_dec);
  emxInit_struct_T(&ps_pre_struc_clst);
  i = ps_pre_struc_clst->size[0] * ps_pre_struc_clst->size[1];
  ps_pre_struc_clst->size[0] = 1;
  ps_pre_struc_clst->size[1] = 1;
  emxEnsureCapacity_struct_T(ps_pre_struc_clst, i);
  ps_pre_struc_clst_data = ps_pre_struc_clst->data;
  emxCopyStruct_struct_T(&ps_pre_struc_clst_data[0], &r);
  emxInit_boolean_T(&ps_pre_struc_cmsk, 2);
  i = ps_pre_struc_cmsk->size[0] * ps_pre_struc_cmsk->size[1];
  ps_pre_struc_cmsk->size[0] = 1;
  ps_pre_struc_cmsk->size[1] = 1;
  emxEnsureCapacity_boolean_T(ps_pre_struc_cmsk, i);
  ps_pre_struc_cmsk_data = ps_pre_struc_cmsk->data;
  ps_pre_struc_cmsk_data[0] = false;
  emxInit_real_T(&ps_pre_struc_cpki, 2);
  i = ps_pre_struc_cpki->size[0] * ps_pre_struc_cpki->size[1];
  ps_pre_struc_cpki->size[0] = 1;
  ps_pre_struc_cpki->size[1] = 1;
  emxEnsureCapacity_real_T(ps_pre_struc_cpki, i);
  t_data = ps_pre_struc_cpki->data;
  t_data[0] = rtNaN;
  printf("Startup set 5 complete. \n");
  fflush(stdout);
  /*  Preallocate X and Xhold so that coder knows the data types. */
  wgn(dcv);
  for (i = 0; i < 1000; i++) {
    exampleData[i].re = (float)dcv[i].re;
    exampleData[i].im = (float)dcv[i].im;
  }
  emxInitStruct_threshold(&val);
  threshold_threshold(Config.contents.falseAlarmProb, &val.pf, &val.evMuParam,
                      &val.evSigmaParam, val.threshVecFine);
  Xhold = waveform_waveform(&lobj_20, exampleData, Config.contents.Fs,
                            pulseStatsPriori, val);
  /* UNTITLED2 Construct an instance of this class */
  /*    Detailed explanation goes here */
  b_waveform_waveform(&b_X, exampleData, Config.contents.Fs, pulseStatsPriori,
                      &lobj_21[0], &lobj_19[0]);
  b_waveform_spectro(Xhold, &lobj_19[1]);
  waveform_spectro(&b_X, &lobj_19[2]);
  printf("Startup set 6 complete. \n");
  fflush(stdout);
  /* Initialize loop variables */
  resetBuffersFlag = true;
  segmentsProcessed = 0.0;
  state_tmp_data[0] = 'i';
  state_tmp_data[1] = 'd';
  state_tmp_data[2] = 'l';
  state_tmp_data[3] = 'e';
  state_size[0] = 1;
  state_size[1] = 4;
  for (i = 0; i < 4; i++) {
    state_data[i] = state_tmp_data[i];
  }
  previousState_size_idx_1 = 9;
  for (i = 0; i < 9; i++) {
    previousState_data[i] = b_cv[i];
  }
  suggestedMode = 'S';
  fLock = false;
  staleDataFlag = true;
  /* Force buffer  flush on start */
  idleTic = 1.0;
  lastTimeStamp = 0.0;
  cleanBuffer = true;
  trackedCount = 0.0;
  printf("Startup set 7 complete. Starting processing... \n");
  fflush(stdout);
  emxInit_creal32_T(&dataWriterBuffData, 1);
  emxInit_creal32_T(&x, 1);
  emxInit_real_T(&t, 1);
  emxInit_int16_T(&y);
  y_data = y->data;
  emxInit_boolean_T(&varargin_1, 2);
  emxInit_char_T(&b_varargin_1);
  emxInit_real_T(&b_x, 2);
  emxInit_real32_T(&dataMatrix, 2);
  emxInit_real_T(&r1, 1);
  emxInit_boolean_T(&r2, 1);
  emxInit_boolean_T(&r3, 2);
  emxInit_boolean_T(&r4, 2);
  int exitg1;
  do {
    exitg1 = 0;
    /* i <= maxInd */
    if (b_strcmp(state_data, state_size)) {
      b_index = 0;
    } else if (e_strcmp(state_data, state_size)) {
      b_index = 1;
    } else if (f_strcmp(state_data, state_size)) {
      b_index = 2;
    } else if (g_strcmp(state_data, state_size)) {
      b_index = 3;
    } else {
      b_index = -1;
    }
    switch (b_index) {
    case 0: {
      int dataReceived_size[2];
      int b_dataReceived_size;
      if (resetBuffersFlag) {
        if (asyncDataBuff.pBuffer.isInitialized == 1) {
          asyncDataBuff.pBuffer.ReadPointer = 1;
          asyncDataBuff.pBuffer.WritePointer = 2;
          asyncDataBuff.pBuffer.CumulativeOverrun = 0;
          asyncDataBuff.pBuffer.CumulativeUnderrun = 0;
          memset(&asyncDataBuff.pBuffer.Cache[0], 0,
                 5800321U * sizeof(creal32_T));
        }
        if (asyncTimeBuff.pBuffer.isInitialized == 1) {
          asyncTimeBuff.pBuffer.ReadPointer = 1;
          asyncTimeBuff.pBuffer.WritePointer = 2;
          asyncTimeBuff.pBuffer.CumulativeOverrun = 0;
          asyncTimeBuff.pBuffer.CumulativeUnderrun = 0;
          memset(&asyncTimeBuff.pBuffer.Cache[0], 0, 5800321U * sizeof(double));
        }
        resetBuffersFlag = false;
        cleanBuffer = true;
      }
      /*             %% Get data */
      channelreceiver(Config.contents.portData, dataReceived_data,
                      dataReceived_size);
      b_dataReceived_size = dataReceived_size[0];
      loop_ub = dataReceived_size[0];
      if (loop_ub - 1 >= 0) {
        memcpy(&b_dataReceived_data[0], &dataReceived_data[0],
               (unsigned int)loop_ub * sizeof(creal32_T));
      }
      /*             %% Flush UDP buffer if data in the buffer is stale. */
      if (staleDataFlag) {
        printf("********STALE DATA FLAG: %u *********\n", 1U);
        fflush(stdout);
        while (b_dataReceived_size != 0) {
          printf("********CLEARING UDP DATA BUFFER*********\n");
          fflush(stdout);
          channelreceiver(Config.contents.portData, dataReceived_data,
                          dataReceived_size);
          b_dataReceived_size = dataReceived_size[0];
          loop_ub = dataReceived_size[0];
          if (loop_ub - 1 >= 0) {
            memcpy(&b_dataReceived_data[0], &dataReceived_data[0],
                   (unsigned int)loop_ub * sizeof(creal32_T));
          }
        }
        staleDataFlag = false;
      }
      /*             %% Wait for new data if none ready, else put data in
       * buffers */
      if (b_dataReceived_size == 0) {
        pause(512.0 / Config.contents.Fs);
      } else {
        double timeStamp_data[1025];
        /* singlecomplex2int Converts a complex single precision positive */
        /* number with a portion of the integer digits in the real and imaginary
         */
        /* parts to integer value. The integer is split at the 7th digit. The
         * top */
        /* digits are then held in the real part of the input, while the lower 7
         */
        /* digits are held in the imaginary part of the input. These digits are
         */
        /* recombined to create a double precision output of the integer. */
        /*  */
        /* A single precision number has a maximum integer */
        /* values of flintmax('single') = 16777216. To avoid overrunning the */
        /* available digits, the output integer is split at digit 7. */
        /*  */
        /* The max value for each input part would be:   16777216 + 1i *
         * 16777216 */
        /* To avoid overflow, the complex part  */
        /* containing the lower digits only use          16777216 + 1i *
         * xxxxxxx */
        /* the first 7 digits available */
        /*  */
        /* Based on this standard, the maximum value that can be transmitted is
         */
        /*    167772169999999 = 1.6777e14; */
        /*  */
        /* INPUTS: */
        /*    singleComplex   Matrix of where each elements' imaginary part
         * contains */
        /*                    the bottom 7 digits of the output integer. The
         * inputs  */
        /*                    real part contain the upper digits of the output.
         */
        /*                    The maximum value of the input real part is
         * 16,777,216.  */
        /*                    The maximum value of the imaginary part if
         * 9,999,999.  */
        /*                    An error is generated if these values are
         * exceeded. */
        /*                    Imaginary parts (lower digits) must be positive.
         * Sign */
        /*                    can be contained in the upper digits (real part).
         * Real */
        /*                    and imaginary parts must only contain integers. */
        /* OUTPUTS: */
        /*    intOut           Matrix of integer values. */
        /*                    Maximum input value is 167772169999999. Inputs */
        /*                    exceedign this value will result in an error.  */
        /*  */
        /* -------------------------------------------------------------------------
         */
        /* Author:    Michael Shafer */
        /* Date:      2022-08-19 */
        /* -------------------------------------------------------------------------
         */
        timeStamp = 0.001 * (b_dataReceived_data[0].re * 1.0E+7 +
                             b_dataReceived_data[0].im);
        if (b_dataReceived_size < 2) {
          i = 1;
          i3 = 0;
          y->size[0] = 1;
          y->size[1] = 0;
        } else {
          i = 2;
          i3 = b_dataReceived_size;
          b_index = y->size[0] * y->size[1];
          y->size[0] = 1;
          y->size[1] = (short)(b_dataReceived_size - 2) + 1;
          emxEnsureCapacity_int16_T(y, b_index);
          y_data = y->data;
          loop_ub = (short)(b_dataReceived_size - 2);
          for (b_index = 0; b_index <= loop_ub; b_index++) {
            y_data[b_index] = (short)b_index;
          }
        }
        t8_yw = 1.0 / Config.contents.Fs;
        /* Check for missing packets based on packet timestamps. */
        if ((asyncTimeBuff.pBuffer.WritePointer >= 0) &&
            (asyncTimeBuff.pBuffer.ReadPointer <
             asyncTimeBuff.pBuffer.WritePointer - MAX_int32_T)) {
          b_index = MAX_int32_T;
        } else if ((asyncTimeBuff.pBuffer.WritePointer < 0) &&
                   (asyncTimeBuff.pBuffer.ReadPointer >
                    asyncTimeBuff.pBuffer.WritePointer - MIN_int32_T)) {
          b_index = MIN_int32_T;
        } else {
          b_index = asyncTimeBuff.pBuffer.WritePointer -
                    asyncTimeBuff.pBuffer.ReadPointer;
        }
        if (b_index < -2147483647) {
          b_index = MIN_int32_T;
        } else {
          b_index--;
        }
        if (asyncTimeBuff.pBuffer.ReadPointer < -2141683327) {
          previousState_size_idx_1 = MAX_int32_T;
        } else {
          previousState_size_idx_1 =
              5800320 - asyncTimeBuff.pBuffer.ReadPointer;
        }
        if ((previousState_size_idx_1 < 0) &&
            (asyncTimeBuff.pBuffer.WritePointer <
             MIN_int32_T - previousState_size_idx_1)) {
          previousState_size_idx_1 = MIN_int32_T;
        } else if ((previousState_size_idx_1 > 0) &&
                   (asyncTimeBuff.pBuffer.WritePointer >
                    MAX_int32_T - previousState_size_idx_1)) {
          previousState_size_idx_1 = MAX_int32_T;
        } else {
          previousState_size_idx_1 += asyncTimeBuff.pBuffer.WritePointer;
        }
        if (asyncTimeBuff.pBuffer.ReadPointer <
            asyncTimeBuff.pBuffer.WritePointer) {
          previousState_size_idx_1 = b_index;
        } else if (asyncTimeBuff.pBuffer.ReadPointer ==
                   asyncTimeBuff.pBuffer.WritePointer) {
          previousState_size_idx_1 = 5800320;
        }
        if (previousState_size_idx_1 != 0) {
          missingTime =
              (timeStamp - lastTimeStamp) - 1024.0 / Config.contents.Fs;
          missingPackets = missingTime * Config.contents.Fs / 1024.0;
          if (missingPackets > 1.0) {
            printf("Packet drop detected. Missed %f packets, or %f seconds of "
                   "data. \n",
                   missingPackets, missingTime);
            fflush(stdout);
          }
          lastTimeStamp = timeStamp;
        } else {
          lastTimeStamp = timeStamp;
        }
        /* Write out data and time. */
        loop_ub = i3 - i;
        for (i3 = 0; i3 <= loop_ub; i3++) {
          dataReceived_data[i3] = b_dataReceived_data[(i + i3) - 1];
        }
        b_AsyncBuffer_write(&asyncDataBuff, dataReceived_data, loop_ub + 1);
        b_index = y->size[1];
        loop_ub = y->size[1];
        for (i = 0; i < loop_ub; i++) {
          timeStamp_data[i] = timeStamp + t8_yw * (double)y_data[i];
        }
        c_AsyncBuffer_write(&asyncTimeBuff, timeStamp_data, b_index);
        d_AsyncBuffer_write(&asyncWriteBuff, b_dataReceived_data,
                            b_dataReceived_size);
        if ((asyncWriteBuff.pBuffer.WritePointer >= 0) &&
            (asyncWriteBuff.pBuffer.ReadPointer <
             asyncWriteBuff.pBuffer.WritePointer - MAX_int32_T)) {
          b_index = MAX_int32_T;
        } else if ((asyncWriteBuff.pBuffer.WritePointer < 0) &&
                   (asyncWriteBuff.pBuffer.ReadPointer >
                    asyncWriteBuff.pBuffer.WritePointer - MIN_int32_T)) {
          b_index = MIN_int32_T;
        } else {
          b_index = asyncWriteBuff.pBuffer.WritePointer -
                    asyncWriteBuff.pBuffer.ReadPointer;
        }
        if (b_index < -2147483647) {
          b_index = MIN_int32_T;
        } else {
          b_index--;
        }
        if (asyncWriteBuff.pBuffer.ReadPointer < -2146882997) {
          previousState_size_idx_1 = MAX_int32_T;
        } else {
          previousState_size_idx_1 =
              600650 - asyncWriteBuff.pBuffer.ReadPointer;
        }
        if ((previousState_size_idx_1 < 0) &&
            (asyncWriteBuff.pBuffer.WritePointer <
             MIN_int32_T - previousState_size_idx_1)) {
          previousState_size_idx_1 = MIN_int32_T;
        } else if ((previousState_size_idx_1 > 0) &&
                   (asyncWriteBuff.pBuffer.WritePointer >
                    MAX_int32_T - previousState_size_idx_1)) {
          previousState_size_idx_1 = MAX_int32_T;
        } else {
          previousState_size_idx_1 += asyncWriteBuff.pBuffer.WritePointer;
        }
        if (asyncWriteBuff.pBuffer.ReadPointer <
            asyncWriteBuff.pBuffer.WritePointer) {
          previousState_size_idx_1 = b_index;
        } else if (asyncWriteBuff.pBuffer.ReadPointer ==
                   asyncWriteBuff.pBuffer.WritePointer) {
          previousState_size_idx_1 = 600650;
        }
        if (previousState_size_idx_1 == dataWriterSamples) {
          b_AsyncBuffer_read(&asyncWriteBuff, dataWriterBuffData);
          dataWriterBuffData_data = dataWriterBuffData->data;
          /* dataWriterBuffDataComplexInterleave = [real(dataWriterBuffData),
           * imag(dataWriterBuffData)].'; */
          /* This function takes a vector of complex values, and interleaves */
          /* the real and complex parts to generate a output vector of 2x the */
          /* number of elements as the number of rows of the input. */
          /* Enforce column vector */
          i = dataMatrix->size[0] * dataMatrix->size[1];
          dataMatrix->size[0] = 2;
          dataMatrix->size[1] = dataWriterBuffData->size[0];
          emxEnsureCapacity_real32_T(dataMatrix, i);
          dataMatrix_data = dataMatrix->data;
          loop_ub = dataWriterBuffData->size[0];
          for (i = 0; i < loop_ub; i++) {
            dataMatrix_data[2 * i] = dataWriterBuffData_data[i].re;
            dataMatrix_data[2 * i + 1] = dataWriterBuffData_data[i].im;
          }
          /* Interleave */
          i = dataMatrix->size[1] << 1;
          b_dataMatrix = *dataMatrix;
          i5 = i;
          b_dataMatrix.size = &i5;
          b_dataMatrix.numDimensions = 1;
          b_fwrite(fileid, &b_dataMatrix);
        }
        /* end */
        /*                 %% Process data if there is enough in the buffers */
        if ((asyncDataBuff.pBuffer.WritePointer >= 0) &&
            (asyncDataBuff.pBuffer.ReadPointer <
             asyncDataBuff.pBuffer.WritePointer - MAX_int32_T)) {
          b_index = MAX_int32_T;
        } else if ((asyncDataBuff.pBuffer.WritePointer < 0) &&
                   (asyncDataBuff.pBuffer.ReadPointer >
                    asyncDataBuff.pBuffer.WritePointer - MIN_int32_T)) {
          b_index = MIN_int32_T;
        } else {
          b_index = asyncDataBuff.pBuffer.WritePointer -
                    asyncDataBuff.pBuffer.ReadPointer;
        }
        if (b_index < -2147483647) {
          b_index = MIN_int32_T;
        } else {
          b_index--;
        }
        if (asyncDataBuff.pBuffer.ReadPointer < -2141683327) {
          previousState_size_idx_1 = MAX_int32_T;
        } else {
          previousState_size_idx_1 =
              5800320 - asyncDataBuff.pBuffer.ReadPointer;
        }
        if ((previousState_size_idx_1 < 0) &&
            (asyncDataBuff.pBuffer.WritePointer <
             MIN_int32_T - previousState_size_idx_1)) {
          previousState_size_idx_1 = MIN_int32_T;
        } else if ((previousState_size_idx_1 > 0) &&
                   (asyncDataBuff.pBuffer.WritePointer >
                    MAX_int32_T - previousState_size_idx_1)) {
          previousState_size_idx_1 = MAX_int32_T;
        } else {
          previousState_size_idx_1 += asyncDataBuff.pBuffer.WritePointer;
        }
        if (asyncDataBuff.pBuffer.ReadPointer <
            asyncDataBuff.pBuffer.WritePointer) {
          previousState_size_idx_1 = b_index;
        } else if (asyncDataBuff.pBuffer.ReadPointer ==
                   asyncDataBuff.pBuffer.WritePointer) {
          previousState_size_idx_1 = 5800320;
        }
        if (previousState_size_idx_1 >=
            sampsForKPulses.contents + overlapSamples.contents) {
          unsigned int c_varargin_1;
          unsigned int varargin_2;
          bool guard1 = false;
          missingTime = rt_roundd_snf(sampsForKPulses.contents);
          if (missingTime < 4.294967296E+9) {
            if (missingTime >= 0.0) {
              c_varargin_1 = (unsigned int)missingTime;
            } else {
              c_varargin_1 = 0U;
            }
          } else if (missingTime >= 4.294967296E+9) {
            c_varargin_1 = MAX_uint32_T;
          } else {
            c_varargin_1 = 0U;
          }
          missingTime = rt_roundd_snf(overlapSamples.contents);
          if (missingTime < 4.294967296E+9) {
            if (missingTime >= 0.0) {
              varargin_2 = (unsigned int)missingTime;
            } else {
              varargin_2 = 0U;
            }
          } else if (missingTime >= 4.294967296E+9) {
            varargin_2 = MAX_uint32_T;
          } else {
            varargin_2 = 0U;
          }
          printf("Buffer Full|| sampsForKPulses: %u, overlapSamples: %u,\n",
                 c_varargin_1, varargin_2);
          fflush(stdout);
          if ((asyncDataBuff.pBuffer.WritePointer >= 0) &&
              (asyncDataBuff.pBuffer.ReadPointer <
               asyncDataBuff.pBuffer.WritePointer - MAX_int32_T)) {
            b_index = MAX_int32_T;
          } else if ((asyncDataBuff.pBuffer.WritePointer < 0) &&
                     (asyncDataBuff.pBuffer.ReadPointer >
                      asyncDataBuff.pBuffer.WritePointer - MIN_int32_T)) {
            b_index = MIN_int32_T;
          } else {
            b_index = asyncDataBuff.pBuffer.WritePointer -
                      asyncDataBuff.pBuffer.ReadPointer;
          }
          if (b_index < -2147483647) {
            b_index = MIN_int32_T;
          } else {
            b_index--;
          }
          if (asyncDataBuff.pBuffer.ReadPointer < -2141683327) {
            previousState_size_idx_1 = MAX_int32_T;
          } else {
            previousState_size_idx_1 =
                5800320 - asyncDataBuff.pBuffer.ReadPointer;
          }
          if ((previousState_size_idx_1 < 0) &&
              (asyncDataBuff.pBuffer.WritePointer <
               MIN_int32_T - previousState_size_idx_1)) {
            previousState_size_idx_1 = MIN_int32_T;
          } else if ((previousState_size_idx_1 > 0) &&
                     (asyncDataBuff.pBuffer.WritePointer >
                      MAX_int32_T - previousState_size_idx_1)) {
            previousState_size_idx_1 = MAX_int32_T;
          } else {
            previousState_size_idx_1 += asyncDataBuff.pBuffer.WritePointer;
          }
          if (asyncDataBuff.pBuffer.ReadPointer <
              asyncDataBuff.pBuffer.WritePointer) {
            previousState_size_idx_1 = b_index;
          } else if (asyncDataBuff.pBuffer.ReadPointer ==
                     asyncDataBuff.pBuffer.WritePointer) {
            previousState_size_idx_1 = 5800320;
          }
          printf("Running...Buffer full with %d samples. Processing. \n",
                 previousState_size_idx_1);
          fflush(stdout);
          tic();
          if (cleanBuffer) {
            /* Overlap reads back into the buffer, but there  */
            /* isn't anything back there on the first segment.  */
            /* Using an overlap will fill the output with  */
            /* overlapSamples of zeros at beginning  */
            /* of x if you specify overlap here. Don't want that */
            /* so specify zero overlap for first read after */
            /* cleaning buffer */
            c_AsyncBuffer_read(&asyncDataBuff, sampsForKPulses.contents, x);
            d_AsyncBuffer_read(&asyncTimeBuff, sampsForKPulses.contents, t);
            t_data = t->data;
            cleanBuffer = false;
          } else {
            e_AsyncBuffer_read(&asyncDataBuff, sampsForKPulses.contents,
                               overlapSamples.contents, x);
            f_AsyncBuffer_read(&asyncTimeBuff, sampsForKPulses.contents,
                               overlapSamples.contents, t);
            t_data = t->data;
          }
          /* Check the timestamps in the buffer for gaps larger */
          /* than the max interpulse uncertainty. If there are */
          /* enough dropped packets such that the time is shifted */
          /* by more than the interpulse uncertainty, then the */
          /* detection will likely fail or produces bad results. In */
          /* this case. Skip the processing and clear the buffer. */
          guard1 = false;
          if (Config.contents.K > 1.0) {
            diff(t, r1);
            r5 = r1->data;
            loop_ub = r1->size[0];
            for (i = 0; i < loop_ub; i++) {
              r5[i] -= t8_yw;
            }
            if (sum(r1) > Config.contents.tipu + Config.contents.tipj) {
              printf("Significant time differences found in timestamp record. "
                     "Skipping processing and clearing buffers.\n");
              fflush(stdout);
              resetBuffersFlag = true;
              staleDataFlag = true;
            } else {
              guard1 = true;
            }
          } else {
            guard1 = true;
          }
          if (guard1) {
            unsigned int validatedHoleFilling[3];
            unsigned int varargin_3;
            printf("Running...Building priori and waveform. \n");
            fflush(stdout);
            /* Set the priori info */
            if (configUpdatedFlag) {
              /* Initialize states for operational modes */
              if (string_eq(Config.contents.opMode.Value)) {
                b_index = 0;
              } else if (b_string_eq(Config.contents.opMode.Value)) {
                b_index = 1;
              } else if (c_string_eq(Config.contents.opMode.Value)) {
                b_index = 2;
              } else if (d_string_eq(Config.contents.opMode.Value)) {
                b_index = 3;
              } else {
                b_index = -1;
              }
              switch (b_index) {
              case 0:
                fLock = false;
                break;
              case 1:
                fLock = true;
                break;
              case 2:
                fLock = false;
                break;
              case 3:
                fLock = false;
                break;
              default:
                fLock = false;
                break;
              }
              makepulsestruc(&r.A, &r.P, &r.SNR, &r.yw, &r.t_0, &r.t_f,
                             r.t_next, &r.fp, &r.fstart, &r.fend, r.mode,
                             &r.det_dec, &r.con_dec);
              makepulsestruc(&missingTime, &missingPackets, &timeStamp, &t8_yw,
                             &t8_t_0, &t8_t_f, expl_temp.t_next, &t8_fp,
                             &t8_fstart, &t8_fend, expl_temp.mode, &t8_det_dec,
                             &t8_con_dec);
              expl_temp.con_dec = t8_con_dec;
              expl_temp.det_dec = t8_det_dec;
              expl_temp.fend = t8_fend;
              expl_temp.fstart = t8_fstart;
              expl_temp.fp = t8_fp;
              expl_temp.t_f = t8_t_f;
              expl_temp.t_0 = t8_t_0;
              expl_temp.yw = t8_yw;
              expl_temp.SNR = timeStamp;
              expl_temp.P = missingPackets;
              expl_temp.A = missingTime;
              pulseStatsPriori = c_pulsestats_pulsestats(
                  &lobj_14, Config.contents.tp, Config.contents.tip,
                  Config.contents.tipu, Config.contents.tipj,
                  1.0E-5 * fabs(Config.contents.tagFreqMHz -
                                Config.contents.channelCenterFreqMHz),
                  &r, &expl_temp);
              configUpdatedFlag = false;
            } else {
              pulseStatsPriori = d_pulsestats_pulsestats(
                  &lobj_17, ps_pre_struc_t_p, ps_pre_struc_t_ip,
                  ps_pre_struc_t_ipu, ps_pre_struc_t_ipj, ps_pre_struc_fp,
                  ps_pre_struc_fstart, ps_pre_struc_fend, ps_pre_struc_tmplt,
                  (char *)&mode, ps_pre_struc_pl, ps_pre_struc_clst,
                  ps_pre_struc_cmsk, ps_pre_struc_cpki);
            }
            /*                         %% PRIMARY PROCESSING BLOCK */
            /* Prep waveform for processing/detection */
            threshold_threshold(Config.contents.falseAlarmProb, &val.pf,
                                &val.evMuParam, &val.evSigmaParam,
                                val.threshVecFine);
            c_waveform_waveform(&X, x, Config.contents.Fs, t_data[0],
                                pulseStatsPriori, val, &lobj_16, &lobj_15);
            X.K = Config.contents.K;
            missingTime = rt_roundd_snf(X.N);
            if (missingTime < 4.294967296E+9) {
              if (missingTime >= 0.0) {
                c_varargin_1 = (unsigned int)missingTime;
              } else {
                c_varargin_1 = 0U;
              }
            } else if (missingTime >= 4.294967296E+9) {
              c_varargin_1 = MAX_uint32_T;
            } else {
              c_varargin_1 = 0U;
            }
            missingTime = rt_roundd_snf(X.M);
            if (missingTime < 4.294967296E+9) {
              if (missingTime >= 0.0) {
                varargin_2 = (unsigned int)missingTime;
              } else {
                varargin_2 = 0U;
              }
            } else if (missingTime >= 4.294967296E+9) {
              varargin_2 = MAX_uint32_T;
            } else {
              varargin_2 = 0U;
            }
            missingTime = rt_roundd_snf(X.J);
            if (missingTime < 4.294967296E+9) {
              if (missingTime >= 0.0) {
                varargin_3 = (unsigned int)missingTime;
              } else {
                varargin_3 = 0U;
              }
            } else if (missingTime >= 4.294967296E+9) {
              varargin_3 = MAX_uint32_T;
            } else {
              varargin_3 = 0U;
            }
            validate_print_arguments(c_varargin_1, varargin_2, varargin_3,
                                     validatedHoleFilling);
            printf("Current interpulse params || N: %u, M: %u, J: %u,\n",
                   validatedHoleFilling[0], validatedHoleFilling[1],
                   validatedHoleFilling[2]);
            fflush(stdout);
            c_waveform_setprioridependentpr(&X, X.ps_pre);
            c_varargin_1 = (unsigned int)X.x->size[1];
            printf("Samples in waveform: %u \n", c_varargin_1);
            fflush(stdout);
            tic();
            printf("Computing STFT...");
            fflush(stdout);
            b_waveform_spectro(&X, &lobj_13);
            missingPackets = toc();
            printf("complete. Elapsed time: %f seconds \n", missingPackets);
            fflush(stdout);
            printf("Building weighting matrix and generating thresholds...");
            fflush(stdout);
            tic();
            waveform_setweightingmatrix(&X);
            if (suggestedMode == 'S') {
              b_index = 0;
            } else if (suggestedMode == 'C') {
              b_index = 1;
            } else if (suggestedMode == 'T') {
              b_index = 2;
            } else {
              b_index = -1;
            }
            switch (b_index) {
            case 0:
              if (fLock) {
                mode = 'I';
              } else {
                mode = 'D';
              }
              break;
            case 1:
              mode = 'C';
              break;
            case 2:
              mode = 'T';
              trackedCount++;
              break;
            default:
              printf("UAV-RT: Unsupported mode requested. Defaulting to "
                     "Discovery (D) mode.");
              fflush(stdout);
              mode = 'D';
              break;
            }
            if (c_strcmp(Config.contents.opMode)) {
              mode = 'D';
            }
            if (segmentsProcessed == 0.0) {
              emxCopyStruct_threshold(&val, &X.thresh);
              threshold_makenewthreshold(&val, &X);
              emxCopyStruct_threshold(&X.thresh, &val);
            } else {
              emxCopyStruct_threshold(&val, &X.thresh);
              threshold_setthreshold(&val, &X, Xhold);
              emxCopyStruct_threshold(&X.thresh, &val);
            }
            missingPackets = toc();
            printf("complete. Elapsed time: %f seconds \n", missingPackets);
            fflush(stdout);
            c_varargin_1 = (unsigned int)X.stft->S->size[1];
            printf("Time windows in S: %u \n", c_varargin_1);
            fflush(stdout);
            printf("Finding pulses...");
            fflush(stdout);
            waveform_process(&X, mode, Config.contents.excldFreqs);
            missingTime = toc();
            missingPackets = toc();
            printf("complete. Elapsed time: %f seconds \n", missingPackets);
            fflush(stdout);
            /*                         %% PREP FOR NEXT LOOP */
            /* Latch/Release the frequency lock and setup the */
            /* suggested mode */
            suggestedMode = X.ps_pos->mode;
            c_horzcatStructList(X.ps_pos->pl, varargin_1);
            all(varargin_1, r2);
            ps_pre_struc_cmsk_data = r2->data;
            if (ifWhileCond(r2)) {
              /* Check if all were confirmed */
              fLock = true;
            }
            /* We only ever release if we are in softlock mode and */
            /* only do so in that case if we are no longer confirming */
            /* pulses. */
            if (d_strcmp(Config.contents.opMode)) {
              tmp_size = r2->size[0];
              loop_ub = r2->size[0];
              for (i = 0; i < loop_ub; i++) {
                tmp_data = !ps_pre_struc_cmsk_data[i];
              }
              b_tmp_data.data = &tmp_data;
              b_tmp_data.size = &tmp_size;
              b_tmp_data.allocatedSize = 1;
              b_tmp_data.numDimensions = 1;
              b_tmp_data.canFreeData = false;
              if (ifWhileCond(&b_tmp_data)) {
                fLock = false;
              }
            }
            /* Decide when/how the priori is updated for the next */
            /* segment's processing. */
            if (ifWhileCond(r2) && ((mode == 'C') || (mode == 'T'))) {
              i = ps_pre_struc_pl->size[0] * ps_pre_struc_pl->size[1];
              ps_pre_struc_pl->size[0] = 1;
              ps_pre_struc_pl->size[1] = X.ps_pos->pl->size[1];
              emxEnsureCapacity_struct_T(ps_pre_struc_pl, i);
              ps_pre_struc_pl_data = ps_pre_struc_pl->data;
              loop_ub = X.ps_pos->pl->size[0] * X.ps_pos->pl->size[1] - 1;
              for (i = 0; i <= loop_ub; i++) {
                emxCopyStruct_struct_T(&ps_pre_struc_pl_data[i],
                                       &X.ps_pos->pl->data[i]);
              }
              pulsestats_updateposteriori(X.ps_pos, ps_pre_struc_pl);
              if (trackedCount > 5.0) {
                trackedCount = 0.0;
                i = ps_pre_struc_pl->size[0] * ps_pre_struc_pl->size[1];
                ps_pre_struc_pl->size[0] = 1;
                ps_pre_struc_pl->size[1] = X.ps_pos->pl->size[1];
                emxEnsureCapacity_struct_T(ps_pre_struc_pl, i);
                ps_pre_struc_pl_data = ps_pre_struc_pl->data;
                loop_ub = X.ps_pos->pl->size[0] * X.ps_pos->pl->size[1] - 1;
                for (i = 0; i <= loop_ub; i++) {
                  emxCopyStruct_struct_T(&ps_pre_struc_pl_data[i],
                                         &X.ps_pos->pl->data[i]);
                }
                b_pulsestats_updateposteriori(X.ps_pos, X.ps_pre,
                                              ps_pre_struc_pl);
              }
            }
            /* Check lagging processing */
            if ((Config.contents.K > 1.0) &&
                (missingTime >
                 0.9 * sampsForKPulses.contents / Config.contents.Fs)) {
              missingTime = Config.contents.K - 1.0;
              Config.contents.K--;
              missingTime = rt_roundd_snf(missingTime);
              if (missingTime < 4.294967296E+9) {
                c_varargin_1 = (unsigned int)missingTime;
              } else {
                c_varargin_1 = MAX_uint32_T;
              }
              printf("WARNING!!! PROCESSING TIME TOOK LONGER THAN WAVEFORM "
                     "LENGTH. STREAMING NOT POSSIBLE. REDUCING NUMBER OF "
                     "PULSES CONSIDERED BY 1 T"
                     "O K = %u \n",
                     c_varargin_1);
              fflush(stdout);
              printf("Resetting all internal data buffers and udp buffers to "
                     "clear potential stale data. \n");
              fflush(stdout);
              resetBuffersFlag = true;
              staleDataFlag = true;
              suggestedMode = 'S';
            }
            segmentsProcessed++;
            tic();
            /* Prepare priori for next segment */
            printf("Updating priori...\n");
            fflush(stdout);
            ps_pre_struc_t_p = X.ps_pos->t_p;
            ps_pre_struc_t_ip = X.ps_pos->t_ip;
            ps_pre_struc_t_ipu = X.ps_pos->t_ipu;
            ps_pre_struc_t_ipj = X.ps_pos->t_ipj;
            ps_pre_struc_fp = X.ps_pos->fp;
            ps_pre_struc_fstart = X.ps_pos->fstart;
            ps_pre_struc_fend = X.ps_pos->fend;
            ps_pre_struc_tmplt[0] = X.ps_pos->tmplt[0];
            ps_pre_struc_tmplt[1] = X.ps_pos->tmplt[1];
            mode = X.ps_pos->mode;
            i = ps_pre_struc_pl->size[0] * ps_pre_struc_pl->size[1];
            ps_pre_struc_pl->size[0] = 1;
            ps_pre_struc_pl->size[1] = X.ps_pos->pl->size[1];
            emxEnsureCapacity_struct_T(ps_pre_struc_pl, i);
            ps_pre_struc_pl_data = ps_pre_struc_pl->data;
            loop_ub = X.ps_pos->pl->size[1];
            for (i = 0; i < loop_ub; i++) {
              emxCopyStruct_struct_T(&ps_pre_struc_pl_data[i],
                                     &X.ps_pos->pl->data[i]);
            }
            i = ps_pre_struc_clst->size[0] * ps_pre_struc_clst->size[1];
            ps_pre_struc_clst->size[0] = X.ps_pos->clst->size[0];
            ps_pre_struc_clst->size[1] = X.ps_pos->clst->size[1];
            emxEnsureCapacity_struct_T(ps_pre_struc_clst, i);
            ps_pre_struc_clst_data = ps_pre_struc_clst->data;
            loop_ub = X.ps_pos->clst->size[0] * X.ps_pos->clst->size[1];
            for (i = 0; i < loop_ub; i++) {
              emxCopyStruct_struct_T(&ps_pre_struc_clst_data[i],
                                     &X.ps_pos->clst->data[i]);
            }
            i = ps_pre_struc_cmsk->size[0] * ps_pre_struc_cmsk->size[1];
            ps_pre_struc_cmsk->size[0] = X.ps_pos->cmsk->size[0];
            ps_pre_struc_cmsk->size[1] = X.ps_pos->cmsk->size[1];
            emxEnsureCapacity_boolean_T(ps_pre_struc_cmsk, i);
            ps_pre_struc_cmsk_data = ps_pre_struc_cmsk->data;
            loop_ub = X.ps_pos->cmsk->size[0] * X.ps_pos->cmsk->size[1];
            for (i = 0; i < loop_ub; i++) {
              ps_pre_struc_cmsk_data[i] = X.ps_pos->cmsk->data[i];
            }
            i = ps_pre_struc_cpki->size[0] * ps_pre_struc_cpki->size[1];
            ps_pre_struc_cpki->size[0] = X.ps_pos->cpki->size[0];
            ps_pre_struc_cpki->size[1] = X.ps_pos->cpki->size[1];
            emxEnsureCapacity_real_T(ps_pre_struc_cpki, i);
            t_data = ps_pre_struc_cpki->data;
            loop_ub = X.ps_pos->cpki->size[0] * X.ps_pos->cpki->size[1];
            for (i = 0; i < loop_ub; i++) {
              t_data[i] = X.ps_pos->cpki->data[i];
            }
            updatebufferreadvariables(&Config, &stftOverlapFraction,
                                      &overlapSamples, &sampsForKPulses,
                                      X.ps_pos);
            missingPackets = toc();
            printf("complete. Elapsed time: %f seconds \n", missingPackets);
            fflush(stdout);
            /* Deal with detected pulses */
            /* Xhold{mod(segmentsProcessed,maxSegments)} = X;%Keep a maxSegments
             * running record of waveforms for debugging in Matlab */
            /* Xstruct = obj2structrecursive(X); */
            /* Xhold = X; */
            Xhold = waveformcopy(&X, &lobj_10, &lobj_11[0], &lobj_12);
            i = ps_pre_struc_pl->size[1];
            for (b_index = 0; b_index < i; b_index++) {
              printf("Pulse at %e Hz detected. Confirmation status: %u \n",
                     ps_pre_struc_pl_data[b_index].fp,
                     (unsigned int)ps_pre_struc_pl_data[b_index].con_dec);
              fflush(stdout);
            }
            missingTime = 0.0;
            i = b_x->size[0] * b_x->size[1];
            b_x->size[0] = X.ps_pos->cpki->size[0];
            b_x->size[1] = X.ps_pos->cpki->size[1];
            emxEnsureCapacity_real_T(b_x, i);
            t_data = b_x->data;
            loop_ub = X.ps_pos->cpki->size[0] * X.ps_pos->cpki->size[1];
            for (i = 0; i < loop_ub; i++) {
              t_data[i] = X.ps_pos->cpki->data[i];
            }
            i = r3->size[0] * r3->size[1];
            r3->size[0] = b_x->size[0];
            r3->size[1] = b_x->size[1];
            emxEnsureCapacity_boolean_T(r3, i);
            ps_pre_struc_cmsk_data = r3->data;
            loop_ub = b_x->size[0] * b_x->size[1];
            for (i = 0; i < loop_ub; i++) {
              ps_pre_struc_cmsk_data[i] = rtIsNaN(t_data[i]);
            }
            i = r4->size[0] * r4->size[1];
            r4->size[0] = r3->size[0];
            r4->size[1] = r3->size[1];
            emxEnsureCapacity_boolean_T(r4, i);
            r6 = r4->data;
            loop_ub = r3->size[0] * r3->size[1];
            for (i = 0; i < loop_ub; i++) {
              r6[i] = !ps_pre_struc_cmsk_data[i];
            }
            if (b_ifWhileCond(r4)) {
              printf("Transmitting ROS2 pulse messages");
              fflush(stdout);
              i = X.ps_pos->cpki->size[0] * X.ps_pos->cpki->size[1] - 1;
              for (b_index = 0; b_index <= i; b_index++) {
                i3 = X.ps_pos->clst->size[1] - 1;
                for (previousState_size_idx_1 = 0;
                     previousState_size_idx_1 <= i3;
                     previousState_size_idx_1++) {
                  /* Set pulseMsg parameters for sending */
                  missingTime++;
                  printf(".");
                  fflush(stdout);
                }
              }
              if (missingTime < 4.294967296E+9) {
                c_varargin_1 = (unsigned int)missingTime;
              } else {
                c_varargin_1 = MAX_uint32_T;
              }
              printf("complete. Transmitted %u pulse(s).\n", c_varargin_1);
              fflush(stdout);
            } else {
              printf("\n");
              fflush(stdout);
            }
            i = b_varargin_1->size[0] * b_varargin_1->size[1];
            b_varargin_1->size[0] = 1;
            b_varargin_1->size[1] = 2;
            emxEnsureCapacity_char_T(b_varargin_1, i);
            varargin_1_data = b_varargin_1->data;
            varargin_1_data[0] = mode;
            varargin_1_data[1] = '\x00';
            printf("Current Mode: %s\n", &varargin_1_data[0]);
            fflush(stdout);
            printf("====================================\n");
            fflush(stdout);
          }
        }
      }
      controlreceiver(Config.contents.portCntrl, cmdReceived_data,
                      dataReceived_size);
      previousState_size_idx_1 = state_size[1];
      loop_ub = state_size[1];
      if (loop_ub - 1 >= 0) {
        memcpy(&previousState_data[0], &state_data[0],
               (unsigned int)loop_ub * sizeof(char));
      }
      checkcommand(cmdReceived_data, dataReceived_size, state_data, state_size);
    } break;
    case 1: {
      int dataReceived_size[2];
      if (rtIsNaN(idleTic) || rtIsInf(idleTic)) {
        missingTime = rtNaN;
      } else {
        missingTime = fmod(idleTic, 8.0);
      }
      if (missingTime == 0.0) {
        printf("Waiting in idle state...\n");
        fflush(stdout);
        idleTic = 1.0;
      }
      idleTic++;
      b_AsyncBuffer_read(&asyncWriteBuff, dataWriterBuffData);
      dataWriterBuffData_data = dataWriterBuffData->data;
      /* This function takes a vector of complex values, and interleaves */
      /* the real and complex parts to generate a output vector of 2x the */
      /* number of elements as the number of rows of the input. */
      /* Enforce column vector */
      i = dataMatrix->size[0] * dataMatrix->size[1];
      dataMatrix->size[0] = 2;
      dataMatrix->size[1] = dataWriterBuffData->size[0];
      emxEnsureCapacity_real32_T(dataMatrix, i);
      dataMatrix_data = dataMatrix->data;
      loop_ub = dataWriterBuffData->size[0];
      for (i = 0; i < loop_ub; i++) {
        dataMatrix_data[2 * i] = dataWriterBuffData_data[i].re;
        dataMatrix_data[2 * i + 1] = dataWriterBuffData_data[i].im;
      }
      /* Interleave */
      i = dataMatrix->size[1] << 1;
      b_dataMatrix = *dataMatrix;
      i2 = i;
      b_dataMatrix.size = &i2;
      b_dataMatrix.numDimensions = 1;
      b_fwrite(fileid, &b_dataMatrix);
      if (asyncDataBuff.pBuffer.isInitialized == 1) {
        asyncDataBuff.pBuffer.ReadPointer = 1;
        asyncDataBuff.pBuffer.WritePointer = 2;
        asyncDataBuff.pBuffer.CumulativeOverrun = 0;
        asyncDataBuff.pBuffer.CumulativeUnderrun = 0;
        memset(&asyncDataBuff.pBuffer.Cache[0], 0,
               5800321U * sizeof(creal32_T));
      }
      if (asyncTimeBuff.pBuffer.isInitialized == 1) {
        asyncTimeBuff.pBuffer.ReadPointer = 1;
        asyncTimeBuff.pBuffer.WritePointer = 2;
        asyncTimeBuff.pBuffer.CumulativeOverrun = 0;
        asyncTimeBuff.pBuffer.CumulativeUnderrun = 0;
        memset(&asyncTimeBuff.pBuffer.Cache[0], 0, 5800321U * sizeof(double));
      }
      if (asyncWriteBuff.pBuffer.isInitialized == 1) {
        asyncWriteBuff.pBuffer.ReadPointer = 1;
        asyncWriteBuff.pBuffer.WritePointer = 2;
        asyncWriteBuff.pBuffer.CumulativeOverrun = 0;
        asyncWriteBuff.pBuffer.CumulativeUnderrun = 0;
        memset(&asyncWriteBuff.pBuffer.Cache[0], 0,
               600651U * sizeof(creal32_T));
      }
      pause(0.25);
      /* Wait a bit so to throttle idle execution */
      staleDataFlag = true;
      controlreceiver(Config.contents.portCntrl, cmdReceived_data,
                      dataReceived_size);
      previousState_size_idx_1 = state_size[1];
      loop_ub = state_size[1];
      if (loop_ub - 1 >= 0) {
        memcpy(&previousState_data[0], &state_data[0],
               (unsigned int)loop_ub * sizeof(char));
      }
      checkcommand(cmdReceived_data, dataReceived_size, state_data, state_size);
    } break;
    case 2: {
      int dataReceived_size[2];
      /* Write all remaining data in buffer before clearing */
      b_AsyncBuffer_read(&asyncWriteBuff, dataWriterBuffData);
      dataWriterBuffData_data = dataWriterBuffData->data;
      /* This function takes a vector of complex values, and interleaves */
      /* the real and complex parts to generate a output vector of 2x the */
      /* number of elements as the number of rows of the input. */
      /* Enforce column vector */
      i = dataMatrix->size[0] * dataMatrix->size[1];
      dataMatrix->size[0] = 2;
      dataMatrix->size[1] = dataWriterBuffData->size[0];
      emxEnsureCapacity_real32_T(dataMatrix, i);
      dataMatrix_data = dataMatrix->data;
      loop_ub = dataWriterBuffData->size[0];
      for (i = 0; i < loop_ub; i++) {
        dataMatrix_data[2 * i] = dataWriterBuffData_data[i].re;
        dataMatrix_data[2 * i + 1] = dataWriterBuffData_data[i].im;
      }
      /* Interleave */
      i = dataMatrix->size[1] << 1;
      b_dataMatrix = *dataMatrix;
      i1 = i;
      b_dataMatrix.size = &i1;
      b_dataMatrix.numDimensions = 1;
      b_fwrite(fileid, &b_dataMatrix);
      updateconfig(&Config, &configPath);
      configUpdatedFlag = true;
      /* Reset all the buffers and setup the buffer read variables */
      if (asyncDataBuff.pBuffer.isInitialized == 1) {
        asyncDataBuff.pBuffer.ReadPointer = 1;
        asyncDataBuff.pBuffer.WritePointer = 2;
        asyncDataBuff.pBuffer.CumulativeOverrun = 0;
        asyncDataBuff.pBuffer.CumulativeUnderrun = 0;
        memset(&asyncDataBuff.pBuffer.Cache[0], 0,
               5800321U * sizeof(creal32_T));
      }
      if (asyncTimeBuff.pBuffer.isInitialized == 1) {
        asyncTimeBuff.pBuffer.ReadPointer = 1;
        asyncTimeBuff.pBuffer.WritePointer = 2;
        asyncTimeBuff.pBuffer.CumulativeOverrun = 0;
        asyncTimeBuff.pBuffer.CumulativeUnderrun = 0;
        memset(&asyncTimeBuff.pBuffer.Cache[0], 0, 5800321U * sizeof(double));
      }
      if (asyncWriteBuff.pBuffer.isInitialized == 1) {
        asyncWriteBuff.pBuffer.ReadPointer = 1;
        asyncWriteBuff.pBuffer.WritePointer = 2;
        asyncWriteBuff.pBuffer.CumulativeOverrun = 0;
        asyncWriteBuff.pBuffer.CumulativeUnderrun = 0;
        memset(&asyncWriteBuff.pBuffer.Cache[0], 0,
               600651U * sizeof(creal32_T));
      }
      /* This sets up a standarized pulsestats object based on the config */
      /* passed to it. */
      makepulsestruc(&r.A, &r.P, &r.SNR, &r.yw, &r.t_0, &r.t_f, r.t_next, &r.fp,
                     &r.fstart, &r.fend, r.mode, &r.det_dec, &r.con_dec);
      makepulsestruc(&missingTime, &missingPackets, &timeStamp, &t8_yw, &t8_t_0,
                     &t8_t_f, expl_temp.t_next, &t8_fp, &t8_fstart, &t8_fend,
                     expl_temp.mode, &t8_det_dec, &t8_con_dec);
      expl_temp.con_dec = t8_con_dec;
      expl_temp.det_dec = t8_det_dec;
      expl_temp.fend = t8_fend;
      expl_temp.fstart = t8_fstart;
      expl_temp.fp = t8_fp;
      expl_temp.t_f = t8_t_f;
      expl_temp.t_0 = t8_t_0;
      expl_temp.yw = t8_yw;
      expl_temp.SNR = timeStamp;
      expl_temp.P = missingPackets;
      expl_temp.A = missingTime;
      pulseStatsPriori = c_pulsestats_pulsestats(
          &lobj_18, Config.contents.tp, Config.contents.tip,
          Config.contents.tipu, Config.contents.tipj,
          1.0E-5 * fabs(Config.contents.tagFreqMHz -
                        Config.contents.channelCenterFreqMHz),
          &r, &expl_temp);
      updatebufferreadvariables(&Config, &stftOverlapFraction, &overlapSamples,
                                &sampsForKPulses, pulseStatsPriori);
      /* Check control and update states */
      staleDataFlag = true;
      controlreceiver(Config.contents.portCntrl, cmdReceived_data,
                      dataReceived_size);
      if ((dataReceived_size[0] != 0) && (dataReceived_size[1] != 0)) {
        previousState_size_idx_1 = state_size[1];
        loop_ub = state_size[1];
        if (loop_ub - 1 >= 0) {
          memcpy(&previousState_data[0], &state_data[0],
                 (unsigned int)loop_ub * sizeof(char));
        }
        checkcommand(cmdReceived_data, dataReceived_size, state_data,
                     state_size);
      } else {
        /* On no command after config update, default to previous state */
        state_size[0] = 1;
        state_size[1] = previousState_size_idx_1;
        if (previousState_size_idx_1 - 1 >= 0) {
          memcpy(&state_data[0], &previousState_data[0],
                 (unsigned int)previousState_size_idx_1 * sizeof(char));
        }
        previousState_size_idx_1 = 12;
        for (i = 0; i < 12; i++) {
          previousState_data[i] = cv[i];
        }
      }
    } break;
    case 3:
      exitg1 = 1;
      break;
    default:
      /* Should never get to this case, but jump to idle if we get */
      /* here. */
      previousState_size_idx_1 = state_size[1];
      loop_ub = state_size[1];
      if (loop_ub - 1 >= 0) {
        memcpy(&previousState_data[0], &state_data[0],
               (unsigned int)loop_ub * sizeof(char));
      }
      state_size[0] = 1;
      state_size[1] = 4;
      for (i = 0; i < 4; i++) {
        state_data[i] = state_tmp_data[i];
      }
      break;
    }
  } while (exitg1 == 0);
  emxFree_boolean_T(&r4);
  emxFreeStruct_struct_T(&expl_temp);
  emxFree_boolean_T(&r3);
  emxFree_boolean_T(&r2);
  emxFree_real_T(&r1);
  emxFreeStruct_struct_T(&r);
  emxFree_real_T(&b_x);
  emxFreeStruct_threshold(&val);
  emxFree_char_T(&b_varargin_1);
  emxFree_boolean_T(&varargin_1);
  emxFree_int16_T(&y);
  emxFree_real_T(&t);
  emxFree_creal32_T(&x);
  emxFree_real_T(&ps_pre_struc_cpki);
  emxFree_boolean_T(&ps_pre_struc_cmsk);
  emxFree_struct_T(&ps_pre_struc_clst);
  emxFree_struct_T(&ps_pre_struc_pl);
  emxFreeStruct_captured_var(&Config);
  /* Send command to release the udp system objects */
  /* CONTROLRECEIVER receives control signal data from the  */
  /* via the specified local IP port from the specified remote IP. */
  /*  */
  /* This function is defined to receive integer control commands and pass */
  /* those receive integers as output. The remoteIP port is not tunable and is
   */
  /* only used on the first call to setup the dsp.UDPReceiver object. Changing
   */
  /* it on ubsequent calls will do nothing to change the receiver. The local  */
  /* IP port is tuneable however. This funtion uses persistant variables and  */
  /* must be cleared if subsequent calls are needed to change the remote IP.  */
  /* For example call  */
  /*  */
  /*    mycntrl = controlreceiver('127.0.0.1',12345); */
  /*    mynewercntrl = controlreceiver('127.0.0.1',12345); */
  /*    mynewercntrlfromdifferentport = controlreceiver('127.0.0.1',54321); */
  /*    clear channelreceiver */
  /*    cntrlfromnewip = controlreceiver('127.0.0.2',12345); */
  /*  */
  /* INPUTS: */
  /*    remoteIP    A string of the remote IP address from which to accept */
  /*                messages */
  /*                Example: '127.0.0.1' - local machine */
  /*                         '0.0.0.0'   - receive from any remote IP */
  /*                         '127.0.0.7' - receive from some other IP on the  */
  /*                                       network */
  /*    localIPPort     Scalar value of the port on which to receive the  */
  /*                    message. */
  /*    releaseSysObj   Logical to release the dsp.UDPReceiver system object  */
  /*  */
  /* OUTPUTS: */
  /*    dataReceived    The received real scalar command message passed. */
  /*                    Received messages are int8. */
  /*                    Maximum length is 1025 */
  /*  */
  /* Author:    Michael W. Shafer */
  /* Date:      2022-02-16 */
  /* --------------------------------------------------------------------------
   */
  /* Reset to clear the buffer of stale data. */
  if (!b_udpRx_not_empty) {
    b_udpRx.isInitialized = 0;
    /* System object Constructor function: dsp.UDPReceiver */
    b_udpRx.cSFunObject.P0_Port = 25000;
    b_udpRx.LocalIPPort = 25000.0;
    b_udpRx.matlabCodegenIsDeleted = false;
    b_udpRx_not_empty = true;
    /* %127.0.0.1',... %Accept all */
    /* %2^16 = 65536, 2^18 */
  }
  b_SystemCore_release(&b_udpRx);
  /* CHANNELRECEIVER receives channelized data from the channelizer function */
  /* via the specified local IP port from the specified remote IP. */
  /*  */
  /* This function is defined to interact with airspyhf_channelizer which */
  /* outputs 1024 samples of IQ with a timestamp for a total of 1025 complex */
  /* single precision values. The remoteIP port is not tunable and is only used
   */
  /* on the first call to setup the dsp.UDPReceiver object. Changing it on */
  /* subsequent calls will do nothing to change the receiver. The local IP port
   */
  /* is tunable however. This funtion uses persistant variables and must be */
  /* cleared if subsequent calls are needed to change the remote IP. For */
  /* example call  */
  /*  */
  /*    mydata = channelreceiver('127.0.0.1',12345); */
  /*    mynewerdata = channelreceiver('127.0.0.1',12345); */
  /*    mynewerdatafromdifferentport = channelreceiver('127.0.0.1',54321); */
  /*    clear channelreceiver */
  /*    datafromnewip = channelreceiver('127.0.0.2',12345); */
  /*  */
  /* INPUTS: */
  /*    remoteIP    A string of the remote IP address from which to accept data
   */
  /*                Example: '127.0.0.1' - local machine */
  /*                         '0.0.0.0'   - receive from any remote IP */
  /*                         '127.0.0.7' - receive from some other IP on the  */
  /*                                       network */
  /*    localIPPort     Scalar value of the port on which to receive the data.
   */
  /*    resetUDP        Logic to reset the persistant udp object */
  /*    releaseSysObj   Logical to release the dsp.UDPReceiver system object  */
  /*  */
  /* OUTPUTS: */
  /*    dataReceived    A vector of received  complex single precision values.
   */
  /*                    Maximum length is 1025 */
  /*  */
  /* Author:    Michael W. Shafer */
  /* Date:      2022-02-14 */
  /* --------------------------------------------------------------------------
   */
  /* Reset to clear the buffer of stale data. */
  if (!udpRx_not_empty) {
    udpRx.isInitialized = 0;
    /* System object Constructor function: dsp.UDPReceiver */
    udpRx.cSFunObject.P0_Port = 25000;
    udpRx.LocalIPPort = 25000.0;
    udpRx.matlabCodegenIsDeleted = false;
    udpRx_not_empty = true;
    /* %127.0.0.1',... %Accept all */
    /* %2^16 = 65536, 2^18 */
  }
  SystemCore_release(&udpRx);
  b_AsyncBuffer_read(&asyncWriteBuff, dataWriterBuffData);
  dataWriterBuffData_data = dataWriterBuffData->data;
  /* This function takes a vector of complex values, and interleaves */
  /* the real and complex parts to generate a output vector of 2x the */
  /* number of elements as the number of rows of the input. */
  /* Enforce column vector */
  i = dataMatrix->size[0] * dataMatrix->size[1];
  dataMatrix->size[0] = 2;
  dataMatrix->size[1] = dataWriterBuffData->size[0];
  emxEnsureCapacity_real32_T(dataMatrix, i);
  dataMatrix_data = dataMatrix->data;
  loop_ub = dataWriterBuffData->size[0];
  for (i = 0; i < loop_ub; i++) {
    dataMatrix_data[2 * i] = dataWriterBuffData_data[i].re;
  }
  loop_ub = dataWriterBuffData->size[0];
  for (i = 0; i < loop_ub; i++) {
    dataMatrix_data[2 * i + 1] = dataWriterBuffData_data[i].im;
  }
  emxFree_creal32_T(&dataWriterBuffData);
  /* Interleave */
  i = dataMatrix->size[1] << 1;
  b_dataMatrix = *dataMatrix;
  i4 = i;
  b_dataMatrix.size = &i4;
  b_dataMatrix.numDimensions = 1;
  b_fwrite(fileid, &b_dataMatrix);
  emxFree_real32_T(&dataMatrix);
  if (asyncDataBuff.pBuffer.isInitialized == 1) {
    asyncDataBuff.pBuffer.ReadPointer = 1;
    asyncDataBuff.pBuffer.WritePointer = 2;
    asyncDataBuff.pBuffer.CumulativeOverrun = 0;
    asyncDataBuff.pBuffer.CumulativeUnderrun = 0;
    memset(&asyncDataBuff.pBuffer.Cache[0], 0, 5800321U * sizeof(creal32_T));
  }
  if (asyncTimeBuff.pBuffer.isInitialized == 1) {
    asyncTimeBuff.pBuffer.ReadPointer = 1;
    asyncTimeBuff.pBuffer.WritePointer = 2;
    asyncTimeBuff.pBuffer.CumulativeOverrun = 0;
    asyncTimeBuff.pBuffer.CumulativeUnderrun = 0;
    memset(&asyncTimeBuff.pBuffer.Cache[0], 0, 5800321U * sizeof(double));
  }
  if (asyncWriteBuff.pBuffer.isInitialized == 1) {
    asyncWriteBuff.pBuffer.ReadPointer = 1;
    asyncWriteBuff.pBuffer.WritePointer = 2;
    asyncWriteBuff.pBuffer.CumulativeOverrun = 0;
    asyncWriteBuff.pBuffer.CumulativeUnderrun = 0;
    memset(&asyncWriteBuff.pBuffer.Cache[0], 0, 600651U * sizeof(creal32_T));
  }
  AsyncBuffer_release(&asyncDataBuff);
  b_AsyncBuffer_release(&asyncTimeBuff);
  c_AsyncBuffer_release(&asyncWriteBuff);
  cfclose(fileid);
  /* release(writer); */
  c_handle_matlabCodegenDestructo(&asyncWriteBuff.pBuffer);
  b_handle_matlabCodegenDestructo(&asyncTimeBuff.pBuffer);
  handle_matlabCodegenDestructor(&asyncDataBuff.pBuffer);
  emxFreeStruct_waveform1(&b_X);
  emxFreeStruct_waveform(&X);
  emxFreeStruct_wfmstft(&lobj_10);
  emxFreeMatrix_pulsestats1(lobj_11);
  emxFreeStruct_waveform(&lobj_12);
  emxFreeStruct_wfmstft(&lobj_13);
  emxFreeStruct_pulsestats(&lobj_14);
  emxFreeStruct_wfmstft(&lobj_15);
  emxFreeStruct_pulsestats(&lobj_16);
  emxFreeStruct_pulsestats(&lobj_17);
  emxFreeStruct_pulsestats(&lobj_18);
  emxFreeMatrix_wfmstft(lobj_19);
  emxFreeStruct_waveform(&lobj_20);
  emxFreeMatrix_pulsestats(lobj_21);
}

/*
 * File trailer for uavrt_detection.c
 *
 * [EOF]
 */
