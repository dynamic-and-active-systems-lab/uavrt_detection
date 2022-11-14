/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: fftshift.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "fftshift.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"

/* Function Definitions */
/*
 * Arguments    : emxArray_creal_T *x
 * Return Type  : void
 */
void fftshift(emxArray_creal_T *x)
{
  creal_T *x_data;
  int k;
  x_data = x->data;
  if (x->size[0] > 1) {
    int vlend2;
    vlend2 = (int)((unsigned int)x->size[0] >> 1) - 1;
    if ((vlend2 + 1) << 1 == x->size[0]) {
      for (k = 0; k <= vlend2; k++) {
        double xtmp_im;
        double xtmp_re;
        int i;
        xtmp_re = x_data[k].re;
        xtmp_im = x_data[k].im;
        i = (vlend2 + k) + 1;
        x_data[k] = x_data[i];
        x_data[i].re = xtmp_re;
        x_data[i].im = xtmp_im;
      }
    } else {
      double xtmp_im;
      double xtmp_re;
      xtmp_re = x_data[vlend2 + 1].re;
      xtmp_im = x_data[vlend2 + 1].im;
      for (k = 0; k <= vlend2; k++) {
        int i;
        i = (vlend2 + k) + 1;
        x_data[i] = x_data[k];
        x_data[k] = x_data[i + 1];
      }
      vlend2 = (vlend2 + vlend2) + 2;
      x_data[vlend2].re = xtmp_re;
      x_data[vlend2].im = xtmp_im;
    }
  }
}

/*
 * File trailer for fftshift.c
 *
 * [EOF]
 */
