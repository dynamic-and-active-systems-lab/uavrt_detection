/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: channelreceiver.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

#ifndef CHANNELRECEIVER_H
#define CHANNELRECEIVER_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void channelreceiver(double localIPPort, creal32_T dataReceived_data[],
                     int dataReceived_size[2]);

void channelreceiver_free(void);

void channelreceiver_init(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for channelreceiver.h
 *
 * [EOF]
 */
