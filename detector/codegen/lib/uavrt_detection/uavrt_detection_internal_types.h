/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: uavrt_detection_internal_types.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

#ifndef UAVRT_DETECTION_INTERNAL_TYPES_H
#define UAVRT_DETECTION_INTERNAL_TYPES_H

/* Include Files */
#include "rtwtypes.h"
#include "uavrt_detection_types.h"

/* Type Definitions */
#ifndef typedef_coder_internal_stickyStruct
#define typedef_coder_internal_stickyStruct
typedef struct {
  double value;
} coder_internal_stickyStruct;
#endif /* typedef_coder_internal_stickyStruct */

#ifndef typedef_b_coder_internal_stickyStruct
#define typedef_b_coder_internal_stickyStruct
typedef struct {
  coder_internal_stickyStruct next;
} b_coder_internal_stickyStruct;
#endif /* typedef_b_coder_internal_stickyStruct */

#ifndef typedef_c_coder_internal_stickyStruct
#define typedef_c_coder_internal_stickyStruct
typedef struct {
  b_coder_internal_stickyStruct next;
} c_coder_internal_stickyStruct;
#endif /* typedef_c_coder_internal_stickyStruct */

#ifndef typedef_d_coder_internal_stickyStruct
#define typedef_d_coder_internal_stickyStruct
typedef struct {
  c_coder_internal_stickyStruct next;
} d_coder_internal_stickyStruct;
#endif /* typedef_d_coder_internal_stickyStruct */

#ifndef typedef_e_coder_internal_stickyStruct
#define typedef_e_coder_internal_stickyStruct
typedef struct {
  d_coder_internal_stickyStruct next;
} e_coder_internal_stickyStruct;
#endif /* typedef_e_coder_internal_stickyStruct */

#ifndef typedef_f_coder_internal_stickyStruct
#define typedef_f_coder_internal_stickyStruct
typedef struct {
  e_coder_internal_stickyStruct next;
} f_coder_internal_stickyStruct;
#endif /* typedef_f_coder_internal_stickyStruct */

#ifndef typedef_g_coder_internal_stickyStruct
#define typedef_g_coder_internal_stickyStruct
typedef struct {
  f_coder_internal_stickyStruct next;
} g_coder_internal_stickyStruct;
#endif /* typedef_g_coder_internal_stickyStruct */

#ifndef typedef_h_coder_internal_stickyStruct
#define typedef_h_coder_internal_stickyStruct
typedef struct {
  double value;
  g_coder_internal_stickyStruct next;
} h_coder_internal_stickyStruct;
#endif /* typedef_h_coder_internal_stickyStruct */

#ifndef typedef_cell_wrap_2
#define typedef_cell_wrap_2
typedef struct {
  unsigned int f1[8];
} cell_wrap_2;
#endif /* typedef_cell_wrap_2 */

#ifndef typedef_c_dsp_internal_AsyncBuffercgHel
#define typedef_c_dsp_internal_AsyncBuffercgHel
typedef struct {
  bool matlabCodegenIsDeleted;
  int isInitialized;
  bool isSetupComplete;
  cell_wrap_2 inputVarSize[1];
  int NumChannels;
  creal32_T Cache[5800321];
  int CumulativeOverrun;
  int CumulativeUnderrun;
  int ReadPointer;
  int WritePointer;
  bool c_AsyncBuffercgHelper_isInitial;
} c_dsp_internal_AsyncBuffercgHel;
#endif /* typedef_c_dsp_internal_AsyncBuffercgHel */

#ifndef typedef_dsp_AsyncBuffer
#define typedef_dsp_AsyncBuffer
typedef struct {
  bool matlabCodegenIsDeleted;
  c_dsp_internal_AsyncBuffercgHel pBuffer;
} dsp_AsyncBuffer;
#endif /* typedef_dsp_AsyncBuffer */

#ifndef typedef_d_dsp_internal_AsyncBuffercgHel
#define typedef_d_dsp_internal_AsyncBuffercgHel
typedef struct {
  bool matlabCodegenIsDeleted;
  int isInitialized;
  bool isSetupComplete;
  cell_wrap_2 inputVarSize[1];
  int NumChannels;
  creal32_T Cache[600651];
  int CumulativeOverrun;
  int CumulativeUnderrun;
  int ReadPointer;
  int WritePointer;
  bool c_AsyncBuffercgHelper_isInitial;
} d_dsp_internal_AsyncBuffercgHel;
#endif /* typedef_d_dsp_internal_AsyncBuffercgHel */

#ifndef typedef_b_dsp_AsyncBuffer
#define typedef_b_dsp_AsyncBuffer
typedef struct {
  bool matlabCodegenIsDeleted;
  d_dsp_internal_AsyncBuffercgHel pBuffer;
} b_dsp_AsyncBuffer;
#endif /* typedef_b_dsp_AsyncBuffer */

#ifndef typedef_e_dsp_internal_AsyncBuffercgHel
#define typedef_e_dsp_internal_AsyncBuffercgHel
typedef struct {
  bool matlabCodegenIsDeleted;
  int isInitialized;
  bool isSetupComplete;
  cell_wrap_2 inputVarSize[1];
  int NumChannels;
  double Cache[5800321];
  int CumulativeOverrun;
  int CumulativeUnderrun;
  int ReadPointer;
  int WritePointer;
  bool c_AsyncBuffercgHelper_isInitial;
} e_dsp_internal_AsyncBuffercgHel;
#endif /* typedef_e_dsp_internal_AsyncBuffercgHel */

#ifndef typedef_c_dsp_AsyncBuffer
#define typedef_c_dsp_AsyncBuffer
typedef struct {
  bool matlabCodegenIsDeleted;
  e_dsp_internal_AsyncBuffercgHel pBuffer;
} c_dsp_AsyncBuffer;
#endif /* typedef_c_dsp_AsyncBuffer */

#endif
/*
 * File trailer for uavrt_detection_internal_types.h
 *
 * [EOF]
 */
