/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: validate_print_arguments.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "validate_print_arguments.h"
#include "rt_nonfinite.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"

/* Function Definitions */
/*
 * Arguments    : unsigned int varargin_1
 *                unsigned int varargin_2
 *                unsigned int varargin_3
 *                unsigned int validatedArguments[3]
 * Return Type  : void
 */
void validate_print_arguments(unsigned int varargin_1, unsigned int varargin_2,
                              unsigned int varargin_3,
                              unsigned int validatedArguments[3])
{
  validatedArguments[0] = varargin_1;
  validatedArguments[1] = varargin_2;
  validatedArguments[2] = varargin_3;
}

/*
 * File trailer for validate_print_arguments.c
 *
 * [EOF]
 */
