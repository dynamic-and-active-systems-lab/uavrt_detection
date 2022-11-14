/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: DetectorConfig.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

#ifndef DETECTORCONFIG_H
#define DETECTORCONFIG_H

/* Include Files */
#include "rtwtypes.h"
#include "uavrt_detection_types.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void DetectorConfig_DetectorConfig(
    double *obj_channelCenterFreqMHz, double *obj_portData,
    double *obj_portCntrl, double *obj_Fs, double *obj_tagFreqMHz,
    double *obj_tp, double *obj_tip, double *obj_tipu, double *obj_tipj,
    double *obj_K, emxArray_char_T *obj_opMode_Value,
    emxArray_real_T *obj_excldFreqs, double *obj_falseAlarmProb,
    emxArray_char_T *obj_dataRecordPath_Value);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for DetectorConfig.h
 *
 * [EOF]
 */
