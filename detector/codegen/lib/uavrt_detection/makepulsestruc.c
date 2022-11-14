/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: makepulsestruc.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "makepulsestruc.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"

/* Function Definitions */
/*
 * PULSE is an thepulseect containing the details of an individual pulse
 *
 *
 * Author: Michael Shafer
 * Date:   Sometime in the summer of 2022.
 *
 *
 *      properties
 *          A           %Amplitude
 *          P           %Power
 *          SNR         %Signal to noise ratio in dB - This is often estimated
 * as signal+noise to noise. yw          %STFT value at location (time and freq)
 * of pulse. w here mean omega. This is equation 14 in the paper draft. t_0
 * %Start time of pulse t_f         %End time of pulse t_next      %Time range
 * [tstart tend] of expected location of next pulse fp          %Peak frequency
 * of pulse (Center frequency if symmetric in frequency domain fstart %Start of
 * the frequency bandwidth fend        %End of frequency bandwidth mode %State
 * machine mode under which pulse was discovered det_dec     %Detection decision
 * (true/false) con_dec     %Was the pulse confirmed (true/false). In tracking,
 * no confirmation step is executed so we record false.
 *
 *
 * Arguments    : double A
 *                double yw
 *                double SNR
 *                double t_0
 *                double t_f
 *                const double t_next[2]
 *                double fp
 *                double fstart
 *                double fend
 *                b_struct_T *thepulse
 * Return Type  : void
 */
void b_makepulsestruc(double A, double yw, double SNR, double t_0, double t_f,
                      const double t_next[2], double fp, double fstart,
                      double fend, b_struct_T *thepulse)
{
  int i;
  /* PULSE Constructs an instance of this class */
  /*  */
  /* Needed to let coder know the mode string will be of variable length */
  /* https://www.mathworks.com/help/simulink/ug/how-working-with-matlab-classes-is-different-for-code-generation.html
   */
  /* dims 0 if fixed, 1 if variable */
  /* Allows for array construction
   * https://www.mathworks.com/help/matlab/matlab_oop/initialize-thepulseect-arrays.html
   */
  thepulse->A = A;
  thepulse->P = A * A;
  thepulse->SNR = SNR;
  thepulse->yw = yw;
  thepulse->t_0 = t_0;
  thepulse->t_f = t_f;
  thepulse->t_next[0] = t_next[0];
  thepulse->t_next[1] = t_next[1];
  thepulse->fp = fp;
  thepulse->fstart = fstart;
  thepulse->fend = fend;
  i = thepulse->mode->size[0] * thepulse->mode->size[1];
  thepulse->mode->size[0] = 1;
  thepulse->mode->size[1] = 3;
  emxEnsureCapacity_char_T(thepulse->mode, i);
  thepulse->mode->data[0] = 'T';
  thepulse->mode->data[1] = 'B';
  thepulse->mode->data[2] = 'D';
  thepulse->det_dec = false;
  thepulse->con_dec = false;
}

/*
 * PULSE is an thepulseect containing the details of an individual pulse
 *
 *
 * Author: Michael Shafer
 * Date:   Sometime in the summer of 2022.
 *
 *
 *      properties
 *          A           %Amplitude
 *          P           %Power
 *          SNR         %Signal to noise ratio in dB - This is often estimated
 * as signal+noise to noise. yw          %STFT value at location (time and freq)
 * of pulse. w here mean omega. This is equation 14 in the paper draft. t_0
 * %Start time of pulse t_f         %End time of pulse t_next      %Time range
 * [tstart tend] of expected location of next pulse fp          %Peak frequency
 * of pulse (Center frequency if symmetric in frequency domain fstart %Start of
 * the frequency bandwidth fend        %End of frequency bandwidth mode %State
 * machine mode under which pulse was discovered det_dec     %Detection decision
 * (true/false) con_dec     %Was the pulse confirmed (true/false). In tracking,
 * no confirmation step is executed so we record false.
 *
 *
 * Arguments    : double *thepulse_A
 *                double *thepulse_P
 *                double *thepulse_SNR
 *                double *thepulse_yw
 *                double *thepulse_t_0
 *                double *thepulse_t_f
 *                double thepulse_t_next[2]
 *                double *thepulse_fp
 *                double *thepulse_fstart
 *                double *thepulse_fend
 *                emxArray_char_T *thepulse_mode
 *                bool *thepulse_det_dec
 *                bool *thepulse_con_dec
 * Return Type  : void
 */
void makepulsestruc(double *thepulse_A, double *thepulse_P,
                    double *thepulse_SNR, double *thepulse_yw,
                    double *thepulse_t_0, double *thepulse_t_f,
                    double thepulse_t_next[2], double *thepulse_fp,
                    double *thepulse_fstart, double *thepulse_fend,
                    emxArray_char_T *thepulse_mode, bool *thepulse_det_dec,
                    bool *thepulse_con_dec)
{
  int i;
  char *thepulse_mode_data;
  /* PULSE Constructs an instance of this class */
  /*  */
  /* Needed to let coder know the mode string will be of variable length */
  /* https://www.mathworks.com/help/simulink/ug/how-working-with-matlab-classes-is-different-for-code-generation.html
   */
  /* dims 0 if fixed, 1 if variable */
  thepulse_t_next[0] = rtNaN;
  thepulse_t_next[1] = rtNaN;
  i = thepulse_mode->size[0] * thepulse_mode->size[1];
  thepulse_mode->size[0] = 1;
  thepulse_mode->size[1] = 3;
  emxEnsureCapacity_char_T(thepulse_mode, i);
  thepulse_mode_data = thepulse_mode->data;
  thepulse_mode_data[0] = 'T';
  thepulse_mode_data[1] = 'B';
  thepulse_mode_data[2] = 'D';
  *thepulse_A = rtNaN;
  *thepulse_P = rtNaN;
  *thepulse_SNR = rtNaN;
  *thepulse_yw = rtNaN;
  *thepulse_t_0 = rtNaN;
  *thepulse_t_f = rtNaN;
  *thepulse_fp = rtNaN;
  *thepulse_fstart = rtNaN;
  *thepulse_fend = rtNaN;
  *thepulse_det_dec = false;
  *thepulse_con_dec = false;
}

/*
 * File trailer for makepulsestruc.c
 *
 * [EOF]
 */
