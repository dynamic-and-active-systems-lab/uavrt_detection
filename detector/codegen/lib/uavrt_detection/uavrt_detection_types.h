/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: uavrt_detection_types.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

#ifndef UAVRT_DETECTION_TYPES_H
#define UAVRT_DETECTION_TYPES_H

/* Include Files */
#include "rtwtypes.h"

/* Type Definitions */
#ifndef typedef_emxArray_creal32_T_1025x1
#define typedef_emxArray_creal32_T_1025x1
typedef struct {
  creal32_T data[1025];
  int size[2];
} emxArray_creal32_T_1025x1;
#endif /* typedef_emxArray_creal32_T_1025x1 */

#ifndef typedef_dsp_UDPReceiver_1
#define typedef_dsp_UDPReceiver_1
typedef struct {
  int S0_isInitialized;
  double W0_NetworkLib[137];
  int P0_Port;
  emxArray_creal32_T_1025x1 O0_Y0;
} dsp_UDPReceiver_1;
#endif /* typedef_dsp_UDPReceiver_1 */

#ifndef typedef_dspcodegen_UDPReceiver
#define typedef_dspcodegen_UDPReceiver
typedef struct {
  bool matlabCodegenIsDeleted;
  int isInitialized;
  bool isSetupComplete;
  dsp_UDPReceiver_1 cSFunObject;
  double LocalIPPort;
} dspcodegen_UDPReceiver;
#endif /* typedef_dspcodegen_UDPReceiver */

#ifndef struct_emxArray_int8_T_1024x1
#define struct_emxArray_int8_T_1024x1
struct emxArray_int8_T_1024x1 {
  signed char data[1024];
  int size[2];
};
#endif /* struct_emxArray_int8_T_1024x1 */
#ifndef typedef_emxArray_int8_T_1024x1
#define typedef_emxArray_int8_T_1024x1
typedef struct emxArray_int8_T_1024x1 emxArray_int8_T_1024x1;
#endif /* typedef_emxArray_int8_T_1024x1 */

#ifndef typedef_dsp_UDPReceiver_3
#define typedef_dsp_UDPReceiver_3
typedef struct {
  int S0_isInitialized;
  double W0_NetworkLib[137];
  int P0_Port;
  emxArray_int8_T_1024x1 O0_Y0;
} dsp_UDPReceiver_3;
#endif /* typedef_dsp_UDPReceiver_3 */

#ifndef typedef_b_dspcodegen_UDPReceiver
#define typedef_b_dspcodegen_UDPReceiver
typedef struct {
  bool matlabCodegenIsDeleted;
  int isInitialized;
  bool isSetupComplete;
  dsp_UDPReceiver_3 cSFunObject;
  double LocalIPPort;
} b_dspcodegen_UDPReceiver;
#endif /* typedef_b_dspcodegen_UDPReceiver */

#ifndef struct_emxArray_char_T
#define struct_emxArray_char_T
struct emxArray_char_T {
  char *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  bool canFreeData;
};
#endif /* struct_emxArray_char_T */
#ifndef typedef_emxArray_char_T
#define typedef_emxArray_char_T
typedef struct emxArray_char_T emxArray_char_T;
#endif /* typedef_emxArray_char_T */

#ifndef typedef_b_struct_T
#define typedef_b_struct_T
typedef struct {
  double A;
  double P;
  double SNR;
  double yw;
  double t_0;
  double t_f;
  double t_next[2];
  double fp;
  double fstart;
  double fend;
  emxArray_char_T *mode;
  bool det_dec;
  bool con_dec;
} b_struct_T;
#endif /* typedef_b_struct_T */

#ifndef typedef_emxArray_struct_T
#define typedef_emxArray_struct_T
typedef struct {
  b_struct_T *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  bool canFreeData;
} emxArray_struct_T;
#endif /* typedef_emxArray_struct_T */

#ifndef struct_emxArray_boolean_T
#define struct_emxArray_boolean_T
struct emxArray_boolean_T {
  bool *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  bool canFreeData;
};
#endif /* struct_emxArray_boolean_T */
#ifndef typedef_emxArray_boolean_T
#define typedef_emxArray_boolean_T
typedef struct emxArray_boolean_T emxArray_boolean_T;
#endif /* typedef_emxArray_boolean_T */

#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T
struct emxArray_real_T {
  double *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  bool canFreeData;
};
#endif /* struct_emxArray_real_T */
#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T
typedef struct emxArray_real_T emxArray_real_T;
#endif /* typedef_emxArray_real_T */

#ifndef typedef_pulsestats
#define typedef_pulsestats
typedef struct {
  double t_p;
  double t_ip;
  double t_ipu;
  double t_ipj;
  double fp;
  double fstart;
  double fend;
  double tmplt[2];
  char mode;
  emxArray_struct_T *pl;
  emxArray_struct_T *clst;
  emxArray_boolean_T *cmsk;
  emxArray_real_T *cpki;
} pulsestats;
#endif /* typedef_pulsestats */

#ifndef typedef_emxArray_creal32_T
#define typedef_emxArray_creal32_T
typedef struct {
  creal32_T *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  bool canFreeData;
} emxArray_creal32_T;
#endif /* typedef_emxArray_creal32_T */

#ifndef typedef_emxArray_creal_T
#define typedef_emxArray_creal_T
typedef struct {
  creal_T *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  bool canFreeData;
} emxArray_creal_T;
#endif /* typedef_emxArray_creal_T */

#ifndef typedef_threshold
#define typedef_threshold
typedef struct {
  double pf;
  double evMuParam;
  double evSigmaParam;
  emxArray_real_T *threshVecFine;
} threshold;
#endif /* typedef_threshold */

#ifndef typedef_wfmstft
#define typedef_wfmstft
typedef struct {
  emxArray_creal_T *S;
  emxArray_real_T *f;
  emxArray_real_T *t;
  emxArray_real_T *psd;
  double dt;
  double T;
  emxArray_real_T *wind;
} wfmstft;
#endif /* typedef_wfmstft */

#ifndef typedef_waveform
#define typedef_waveform
typedef struct {
  pulsestats *ps_pre;
  pulsestats *ps_pos;
  double K;
  threshold thresh;
  emxArray_creal32_T *x;
  double Fs;
  double l;
  double t_0;
  double t_f;
  double t_nextsegstart[2];
  wfmstft *stft;
  double OLF;
  emxArray_creal_T *W;
  emxArray_real_T *Wf;
  double n_p;
  double n_w;
  double n_ol;
  double n_ws;
  double t_ws;
  double n_ip;
  double N;
  double M;
  double J;
  pulsestats _pobj0;
  wfmstft _pobj1;
} waveform;
#endif /* typedef_waveform */

#ifndef typedef_b_waveform
#define typedef_b_waveform
typedef struct {
  pulsestats *ps_pre;
  pulsestats *ps_pos;
  double K;
  emxArray_creal32_T *x;
  double Fs;
  double t_0;
  wfmstft *stft;
  double OLF;
  double n_w;
  double n_ol;
} b_waveform;
#endif /* typedef_b_waveform */

#ifndef typedef_b_rtString
#define typedef_b_rtString
typedef struct {
  emxArray_char_T *Value;
} b_rtString;
#endif /* typedef_b_rtString */

#ifndef typedef_DetectorConfig
#define typedef_DetectorConfig
typedef struct {
  double channelCenterFreqMHz;
  double portData;
  double portCntrl;
  double Fs;
  double tagFreqMHz;
  double tp;
  double tip;
  double tipu;
  double tipj;
  double K;
  b_rtString opMode;
  emxArray_real_T *excldFreqs;
  double falseAlarmProb;
  b_rtString dataRecordPath;
} DetectorConfig;
#endif /* typedef_DetectorConfig */

#ifndef typedef_c_captured_var
#define typedef_c_captured_var
typedef struct {
  DetectorConfig contents;
} c_captured_var;
#endif /* typedef_c_captured_var */

#ifndef struct_emxArray_int16_T
#define struct_emxArray_int16_T
struct emxArray_int16_T {
  short *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  bool canFreeData;
};
#endif /* struct_emxArray_int16_T */
#ifndef typedef_emxArray_int16_T
#define typedef_emxArray_int16_T
typedef struct emxArray_int16_T emxArray_int16_T;
#endif /* typedef_emxArray_int16_T */

#ifndef struct_emxArray_real32_T
#define struct_emxArray_real32_T
struct emxArray_real32_T {
  float *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  bool canFreeData;
};
#endif /* struct_emxArray_real32_T */
#ifndef typedef_emxArray_real32_T
#define typedef_emxArray_real32_T
typedef struct emxArray_real32_T emxArray_real32_T;
#endif /* typedef_emxArray_real32_T */

#ifndef struct_emxArray_uint32_T
#define struct_emxArray_uint32_T
struct emxArray_uint32_T {
  unsigned int *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  bool canFreeData;
};
#endif /* struct_emxArray_uint32_T */
#ifndef typedef_emxArray_uint32_T
#define typedef_emxArray_uint32_T
typedef struct emxArray_uint32_T emxArray_uint32_T;
#endif /* typedef_emxArray_uint32_T */

#ifndef struct_emxArray_int32_T
#define struct_emxArray_int32_T
struct emxArray_int32_T {
  int *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  bool canFreeData;
};
#endif /* struct_emxArray_int32_T */
#ifndef typedef_emxArray_int32_T
#define typedef_emxArray_int32_T
typedef struct emxArray_int32_T emxArray_int32_T;
#endif /* typedef_emxArray_int32_T */

#ifndef typedef_c_sparse
#define typedef_c_sparse
typedef struct {
  emxArray_boolean_T *d;
  emxArray_int32_T *colidx;
  emxArray_int32_T *rowidx;
  int m;
  int n;
  int maxnz;
} c_sparse;
#endif /* typedef_c_sparse */

#ifndef struct_emxArray_int8_T
#define struct_emxArray_int8_T
struct emxArray_int8_T {
  signed char *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  bool canFreeData;
};
#endif /* struct_emxArray_int8_T */
#ifndef typedef_emxArray_int8_T
#define typedef_emxArray_int8_T
typedef struct emxArray_int8_T emxArray_int8_T;
#endif /* typedef_emxArray_int8_T */

#ifndef typedef_d_sparse
#define typedef_d_sparse
typedef struct {
  emxArray_real_T *d;
  emxArray_int32_T *colidx;
  emxArray_int32_T *rowidx;
  int m;
  int n;
} d_sparse;
#endif /* typedef_d_sparse */

#endif
/*
 * File trailer for uavrt_detection_types.h
 *
 * [EOF]
 */
