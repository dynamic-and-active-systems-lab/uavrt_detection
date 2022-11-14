/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: uavrt_detection_emxutil.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

#ifndef UAVRT_DETECTION_EMXUTIL_H
#define UAVRT_DETECTION_EMXUTIL_H

/* Include Files */
#include "rtwtypes.h"
#include "uavrt_detection_types.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void c_emxInitStruct_dspcodegen_UDPR(dspcodegen_UDPReceiver *pStruct);

extern void d_emxInitStruct_dspcodegen_UDPR(b_dspcodegen_UDPReceiver *pStruct);

extern void emxCopyMatrix_real_T(double dst[2], const double src[2]);

extern void emxCopyStruct_struct_T(b_struct_T *dst, const b_struct_T *src);

extern void emxCopyStruct_threshold(threshold *dst, const threshold *src);

extern void emxCopy_char_T(emxArray_char_T **dst, emxArray_char_T *const *src);

extern void emxCopy_real_T(emxArray_real_T **dst, emxArray_real_T *const *src);

extern void emxEnsureCapacity_boolean_T(emxArray_boolean_T *emxArray,
                                        int oldNumel);

extern void emxEnsureCapacity_char_T(emxArray_char_T *emxArray, int oldNumel);

extern void emxEnsureCapacity_creal32_T(emxArray_creal32_T *emxArray,
                                        int oldNumel);

extern void emxEnsureCapacity_creal_T(emxArray_creal_T *emxArray, int oldNumel);

extern void emxEnsureCapacity_int16_T(emxArray_int16_T *emxArray, int oldNumel);

extern void emxEnsureCapacity_int32_T(emxArray_int32_T *emxArray, int oldNumel);

extern void emxEnsureCapacity_int8_T(emxArray_int8_T *emxArray, int oldNumel);

extern void emxEnsureCapacity_real32_T(emxArray_real32_T *emxArray,
                                       int oldNumel);

extern void emxEnsureCapacity_real_T(emxArray_real_T *emxArray, int oldNumel);

extern void emxEnsureCapacity_struct_T(emxArray_struct_T *emxArray,
                                       int oldNumel);

extern void emxEnsureCapacity_uint32_T(emxArray_uint32_T *emxArray,
                                       int oldNumel);

extern void emxExpand_struct_T(emxArray_struct_T *emxArray, int fromIndex,
                               int toIndex);

extern void emxFreeMatrix_pulsestats(pulsestats pMatrix[2]);

extern void emxFreeMatrix_pulsestats1(pulsestats pMatrix[4]);

extern void emxFreeMatrix_wfmstft(wfmstft pMatrix[3]);

extern void emxFreeStruct_DetectorConfig(DetectorConfig *pStruct);

extern void emxFreeStruct_captured_var(c_captured_var *pStruct);

extern void emxFreeStruct_pulsestats(pulsestats *pStruct);

extern void emxFreeStruct_rtString(b_rtString *pStruct);

extern void emxFreeStruct_sparse(d_sparse *pStruct);

extern void emxFreeStruct_sparse1(c_sparse *pStruct);

extern void emxFreeStruct_struct_T(b_struct_T *pStruct);

extern void emxFreeStruct_threshold(threshold *pStruct);

extern void emxFreeStruct_waveform(waveform *pStruct);

extern void emxFreeStruct_waveform1(b_waveform *pStruct);

extern void emxFreeStruct_wfmstft(wfmstft *pStruct);

extern void emxFree_boolean_T(emxArray_boolean_T **pEmxArray);

extern void emxFree_char_T(emxArray_char_T **pEmxArray);

extern void emxFree_creal32_T(emxArray_creal32_T **pEmxArray);

extern void emxFree_creal_T(emxArray_creal_T **pEmxArray);

extern void emxFree_int16_T(emxArray_int16_T **pEmxArray);

extern void emxFree_int32_T(emxArray_int32_T **pEmxArray);

extern void emxFree_int8_T(emxArray_int8_T **pEmxArray);

extern void emxFree_real32_T(emxArray_real32_T **pEmxArray);

extern void emxFree_real_T(emxArray_real_T **pEmxArray);

extern void emxFree_struct_T(emxArray_struct_T **pEmxArray);

extern void emxFree_uint32_T(emxArray_uint32_T **pEmxArray);

extern void emxInitMatrix_pulsestats(pulsestats pMatrix[2]);

extern void emxInitMatrix_pulsestats1(pulsestats pMatrix[4]);

extern void emxInitMatrix_wfmstft(wfmstft pMatrix[3]);

extern void emxInitStruct_DetectorConfig(DetectorConfig *pStruct);

extern void emxInitStruct_captured_var(c_captured_var *pStruct);

extern void emxInitStruct_dsp_UDPReceiver_1(dsp_UDPReceiver_1 *pStruct);

extern void emxInitStruct_dsp_UDPReceiver_3(dsp_UDPReceiver_3 *pStruct);

extern void emxInitStruct_pulsestats(pulsestats *pStruct);

extern void emxInitStruct_rtString(b_rtString *pStruct);

extern void emxInitStruct_sparse(d_sparse *pStruct);

extern void emxInitStruct_sparse1(c_sparse *pStruct);

extern void emxInitStruct_struct_T(b_struct_T *pStruct);

extern void emxInitStruct_threshold(threshold *pStruct);

extern void emxInitStruct_waveform(waveform *pStruct);

extern void emxInitStruct_waveform1(b_waveform *pStruct);

extern void emxInitStruct_wfmstft(wfmstft *pStruct);

extern void emxInit_boolean_T(emxArray_boolean_T **pEmxArray,
                              int numDimensions);

extern void emxInit_char_T(emxArray_char_T **pEmxArray);

extern void emxInit_creal32_T(emxArray_creal32_T **pEmxArray,
                              int numDimensions);

extern void emxInit_creal_T(emxArray_creal_T **pEmxArray, int numDimensions);

extern void emxInit_int16_T(emxArray_int16_T **pEmxArray);

extern void emxInit_int32_T(emxArray_int32_T **pEmxArray, int numDimensions);

extern void emxInit_int8_T(emxArray_int8_T **pEmxArray);

extern void emxInit_real32_T(emxArray_real32_T **pEmxArray, int numDimensions);

extern void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);

extern void emxInit_struct_T(emxArray_struct_T **pEmxArray);

extern void emxInit_uint32_T(emxArray_uint32_T **pEmxArray);

extern void emxTrim_struct_T(emxArray_struct_T *emxArray, int fromIndex,
                             int toIndex);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for uavrt_detection_emxutil.h
 *
 * [EOF]
 */
