/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: controlreceiver.h
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

#ifndef CONTROLRECEIVER_H
#define CONTROLRECEIVER_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void controlreceiver(double localIPPort, signed char dataReceived_data[],
                     int dataReceived_size[2]);

void controlreceiver_free(void);

void controlreceiver_init(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for controlreceiver.h
 *
 * [EOF]
 */
