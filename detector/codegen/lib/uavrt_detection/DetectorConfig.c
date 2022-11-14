/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: DetectorConfig.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "DetectorConfig.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"

/* Function Definitions */
/*
 * DETECTORCONFIR Construct an instance of this class
 *
 * INPUTS:
 *    IDstr           A string identifier for the detector
 *    channelCenterFreqMHz    Center frequency of incoming data stream in MHz
 *    ipData          String ip from which to receive data. Enter
 *                    '0.0.0.0' to receive from any IP.
 *    portData        Port from which to receive data
 *    ipCntrl         String ip from which to receive control inputs.
 *                    Enter '0.0.0.0' to receive from any IP.
 *    portCntrl       Port from which to receive control inputs
 *    Fs              Sample rate of incoming data
 *    tagFreqMHz      Expected frequency of tag
 *    tp              Duration of pulse in seconds
 *    tip             Interpulse duration in seconds
 *    tipu            Interpulse duration uncertainty in seconds
 *    tipj            Interpulse jitter in seconds
 *    K               Number of pulses to integrate
 *    opMode          Operational mode for processing:
 *                        freqSearchHardLock
 *                        freqSearchSoftLock
 *                        freqKnownHardLock
 *                        freqAllNeverLock
 *    excldFreqs      [nx2] matrix of frequency bands to exclude
 *    falsAlarmProb   False alarm probability
 *    decisionEntryPath   Path to decision entry
 *    dataRecordPath      Path to location to which record the
 *                        data
 *    processedOuputPath  Path to location to save processed
 *                        results.
 *    ros2enable      Boolean (1/0 or True/False) to enable ros2 network
 *                    publishing
 *
 * Arguments    : double *obj_channelCenterFreqMHz
 *                double *obj_portData
 *                double *obj_portCntrl
 *                double *obj_Fs
 *                double *obj_tagFreqMHz
 *                double *obj_tp
 *                double *obj_tip
 *                double *obj_tipu
 *                double *obj_tipj
 *                double *obj_K
 *                emxArray_char_T *obj_opMode_Value
 *                emxArray_real_T *obj_excldFreqs
 *                double *obj_falseAlarmProb
 *                emxArray_char_T *obj_dataRecordPath_Value
 * Return Type  : void
 */
void DetectorConfig_DetectorConfig(
    double *obj_channelCenterFreqMHz, double *obj_portData,
    double *obj_portCntrl, double *obj_Fs, double *obj_tagFreqMHz,
    double *obj_tp, double *obj_tip, double *obj_tipu, double *obj_tipj,
    double *obj_K, emxArray_char_T *obj_opMode_Value,
    emxArray_real_T *obj_excldFreqs, double *obj_falseAlarmProb,
    emxArray_char_T *obj_dataRecordPath_Value)
{
  double *obj_excldFreqs_data;
  int i;
  char *obj_opMode_Value_data;
  i = obj_opMode_Value->size[0] * obj_opMode_Value->size[1];
  obj_opMode_Value->size[0] = 1;
  obj_opMode_Value->size[1] = 18;
  emxEnsureCapacity_char_T(obj_opMode_Value, i);
  obj_opMode_Value_data = obj_opMode_Value->data;
  for (i = 0; i < 18; i++) {
    obj_opMode_Value_data[i] = cv1[i];
  }
  i = obj_excldFreqs->size[0] * obj_excldFreqs->size[1];
  obj_excldFreqs->size[0] = 1;
  obj_excldFreqs->size[1] = 2;
  emxEnsureCapacity_real_T(obj_excldFreqs, i);
  obj_excldFreqs_data = obj_excldFreqs->data;
  obj_excldFreqs_data[0] = rtInf;
  obj_excldFreqs_data[1] = rtMinusInf;
  obj_dataRecordPath_Value->size[0] = 1;
  obj_dataRecordPath_Value->size[1] = 0;
  *obj_channelCenterFreqMHz = 150.0;
  *obj_portData = 1.0;
  *obj_portCntrl = 1.0;
  *obj_Fs = 192000.0;
  *obj_tagFreqMHz = 150.0;
  *obj_tp = 0.02;
  *obj_tip = 1.0;
  *obj_tipu = 0.0;
  *obj_tipj = 0.0;
  *obj_K = 1.0;
  *obj_falseAlarmProb = 0.01;
}

/*
 * File trailer for DetectorConfig.c
 *
 * [EOF]
 */
