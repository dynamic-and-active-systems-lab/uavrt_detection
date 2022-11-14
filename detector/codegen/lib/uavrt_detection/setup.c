/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: setup.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "setup.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"

/* Function Definitions */
/*
 * Arguments    : dsp_UDPReceiver_1 *obj
 *                creal32_T Y0_data[]
 *                int Y0_size[2]
 * Return Type  : void
 */
void Outputs(dsp_UDPReceiver_1 *obj, creal32_T Y0_data[], int Y0_size[2])
{
  int i;
  int loop_ub;
  int samplesRead;
  char *sErr;
  /* System object Outputs function: dsp.UDPReceiver */
  sErr = GetErrorBuffer(&obj->W0_NetworkLib[0U]);
  obj->O0_Y0.size[0] = 1025;
  obj->O0_Y0.size[1] = 1;
  samplesRead = 1025;
  samplesRead <<= 1;
  LibOutputs_Network(&obj->W0_NetworkLib[0U], &obj->O0_Y0.data[0U],
                     &samplesRead);
  if (*sErr != 0) {
    PrintError(sErr);
  }
  obj->O0_Y0.size[0] = samplesRead >> 1;
  obj->O0_Y0.size[1] = 1;
  Y0_size[0] = obj->O0_Y0.size[0];
  Y0_size[1] = obj->O0_Y0.size[1];
  loop_ub = obj->O0_Y0.size[0] * obj->O0_Y0.size[1];
  for (i = 0; i < loop_ub; i++) {
    Y0_data[i] = obj->O0_Y0.data[i];
  }
}

/*
 * Arguments    : dsp_UDPReceiver_3 *obj
 *                signed char Y0_data[]
 *                int Y0_size[2]
 * Return Type  : void
 */
void b_Outputs(dsp_UDPReceiver_3 *obj, signed char Y0_data[], int Y0_size[2])
{
  int i;
  int loop_ub;
  int samplesRead;
  char *sErr;
  /* System object Outputs function: dsp.UDPReceiver */
  sErr = GetErrorBuffer(&obj->W0_NetworkLib[0U]);
  obj->O0_Y0.size[0] = 1024;
  obj->O0_Y0.size[1] = 1;
  samplesRead = 1024;
  LibOutputs_Network(&obj->W0_NetworkLib[0U], &obj->O0_Y0.data[0U],
                     &samplesRead);
  if (*sErr != 0) {
    PrintError(sErr);
  }
  obj->O0_Y0.size[0] = samplesRead;
  obj->O0_Y0.size[1] = 1;
  Y0_size[0] = obj->O0_Y0.size[0];
  Y0_size[1] = obj->O0_Y0.size[1];
  loop_ub = obj->O0_Y0.size[0] * obj->O0_Y0.size[1];
  for (i = 0; i < loop_ub; i++) {
    Y0_data[i] = obj->O0_Y0.data[i];
  }
}

/*
 * File trailer for setup.c
 *
 * [EOF]
 */
