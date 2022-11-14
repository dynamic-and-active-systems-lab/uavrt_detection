/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: wfmstft.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "wfmstft.h"
#include "mean.h"
#include "movSumProdOrMean.h"
#include "quickselect.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static void binary_expand_op(emxArray_boolean_T *in1,
                             const emxArray_real_T *in2,
                             const emxArray_real_T *in3);

/* Function Definitions */
/*
 * Arguments    : emxArray_boolean_T *in1
 *                const emxArray_real_T *in2
 *                const emxArray_real_T *in3
 * Return Type  : void
 */
static void binary_expand_op(emxArray_boolean_T *in1,
                             const emxArray_real_T *in2,
                             const emxArray_real_T *in3)
{
  const double *in2_data;
  const double *in3_data;
  int aux_0_1;
  int aux_1_1;
  int i;
  int i1;
  int loop_ub;
  int stride_0_0;
  int stride_0_1;
  int stride_1_0;
  int stride_1_1;
  bool *in1_data;
  in3_data = in3->data;
  in2_data = in2->data;
  i = in1->size[0] * in1->size[1];
  if (in3->size[0] == 1) {
    in1->size[0] = in2->size[0];
  } else {
    in1->size[0] = in3->size[0];
  }
  if (in3->size[1] == 1) {
    in1->size[1] = in2->size[1];
  } else {
    in1->size[1] = in3->size[1];
  }
  emxEnsureCapacity_boolean_T(in1, i);
  in1_data = in1->data;
  stride_0_0 = (in2->size[0] != 1);
  stride_0_1 = (in2->size[1] != 1);
  stride_1_0 = (in3->size[0] != 1);
  stride_1_1 = (in3->size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  if (in3->size[1] == 1) {
    loop_ub = in2->size[1];
  } else {
    loop_ub = in3->size[1];
  }
  for (i = 0; i < loop_ub; i++) {
    int b_loop_ub;
    i1 = in3->size[0];
    if (i1 == 1) {
      b_loop_ub = in2->size[0];
    } else {
      b_loop_ub = i1;
    }
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      in1_data[i1 + in1->size[0] * i] =
          (in2_data[i1 * stride_0_0 + in2->size[0] * aux_0_1] >
           10.0 * in3_data[i1 * stride_1_0 + in3->size[0] * aux_1_1]);
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
}

/*
 * obj.psd = obj.dt^2/obj.T*mean(abs(obj.S).^2,2);
 * obj.psd = obj.dt^2/obj.T*median(abs(obj.S).^2,2);%use median to exclude
 * outliers from short pulses runningPsd = obj.dt^2/obj.T*abs(obj.S).^2;
 *              psdStdDev  = stdev(runningPsd,[],2);
 *              psdStdDevMat = repmat(runningPsd,1,size(runningPsd,2));
 *
 * Arguments    : wfmstft *obj
 * Return Type  : void
 */
void wfmstft_updatepsd(wfmstft *obj)
{
  emxArray_boolean_T *magSqrdMask;
  emxArray_int32_T *r;
  emxArray_real_T *magSqrd;
  emxArray_real_T *movMeanMagSqrd;
  emxArray_real_T *xv;
  double b;
  double varargin_1;
  double *magSqrd_data;
  double *movMeanMagSqrd_data;
  double *xv_data;
  int ibtile;
  int ilast;
  int j;
  int len;
  int loop_ub;
  int midm1;
  int nx;
  int outsize_idx_0;
  int stride;
  int *r1;
  bool *magSqrdMask_data;
  /* This block calculates a three window moving mean of the power */
  /* spectral density of the waveform and then thresholds that */
  /* moving mean for values greater than 10x the median. This */
  /* thresholding step reduced the energy from very high power */
  /* pulses that might be in the signal from affecting the PSD */
  /* estimate. It is assumed here that low signal power pulses will */
  /* only marginally affect the psd estimate.  */
  /* coder.varsize('magSqrd','movMeanMagSqrd','medMovMeanMagSqrd','medMovMeanMagSqrdMat','magSqrdMask')
   */
  nx = obj->S->size[0] * obj->S->size[1];
  emxInit_real_T(&movMeanMagSqrd, 2);
  ilast = movMeanMagSqrd->size[0] * movMeanMagSqrd->size[1];
  movMeanMagSqrd->size[0] = obj->S->size[0];
  movMeanMagSqrd->size[1] = obj->S->size[1];
  emxEnsureCapacity_real_T(movMeanMagSqrd, ilast);
  movMeanMagSqrd_data = movMeanMagSqrd->data;
  for (midm1 = 0; midm1 < nx; midm1++) {
    movMeanMagSqrd_data[midm1] =
        rt_hypotd_snf(obj->S->data[midm1].re, obj->S->data[midm1].im);
  }
  emxInit_real_T(&magSqrd, 2);
  ilast = magSqrd->size[0] * magSqrd->size[1];
  magSqrd->size[0] = movMeanMagSqrd->size[0];
  magSqrd->size[1] = movMeanMagSqrd->size[1];
  emxEnsureCapacity_real_T(magSqrd, ilast);
  magSqrd_data = magSqrd->data;
  loop_ub = movMeanMagSqrd->size[0] * movMeanMagSqrd->size[1];
  for (ilast = 0; ilast < loop_ub; ilast++) {
    varargin_1 = movMeanMagSqrd_data[ilast];
    magSqrd_data[ilast] = varargin_1 * varargin_1;
  }
  ilast = movMeanMagSqrd->size[0] * movMeanMagSqrd->size[1];
  movMeanMagSqrd->size[0] = magSqrd->size[0];
  movMeanMagSqrd->size[1] = magSqrd->size[1];
  emxEnsureCapacity_real_T(movMeanMagSqrd, ilast);
  movMeanMagSqrd_data = movMeanMagSqrd->data;
  loop_ub = magSqrd->size[0] * magSqrd->size[1];
  for (ilast = 0; ilast < loop_ub; ilast++) {
    movMeanMagSqrd_data[ilast] = 0.0;
  }
  nx = magSqrd->size[1];
  stride = magSqrd->size[0];
  if (magSqrd->size[0] - 1 >= 0) {
    outsize_idx_0 = magSqrd->size[1];
    ibtile = magSqrd->size[1];
  }
  emxInit_real_T(&xv, 1);
  for (j = 0; j < stride; j++) {
    ilast = xv->size[0];
    xv->size[0] = outsize_idx_0;
    emxEnsureCapacity_real_T(xv, ilast);
    xv_data = xv->data;
    for (ilast = 0; ilast < ibtile; ilast++) {
      xv_data[ilast] = 0.0;
    }
    for (midm1 = 0; midm1 < nx; midm1++) {
      xv_data[midm1] = magSqrd_data[j + midm1 * stride];
    }
    vmovfun(xv, magSqrd->size[1], obj->psd);
    len = obj->psd->size[0];
    for (midm1 = 0; midm1 < len; midm1++) {
      movMeanMagSqrd_data[j + midm1 * stride] = obj->psd->data[midm1];
    }
  }
  ilast = obj->psd->size[0];
  obj->psd->size[0] = movMeanMagSqrd->size[0];
  emxEnsureCapacity_real_T(obj->psd, ilast);
  if ((movMeanMagSqrd->size[0] == 0) || (movMeanMagSqrd->size[1] == 0)) {
    len = obj->psd->size[0];
    ilast = obj->psd->size[0];
    obj->psd->size[0] = len;
    emxEnsureCapacity_real_T(obj->psd, ilast);
    for (ilast = 0; ilast < len; ilast++) {
      obj->psd->data[ilast] = rtNaN;
    }
  } else {
    int n;
    ilast = obj->psd->size[0];
    obj->psd->size[0] = movMeanMagSqrd->size[0];
    emxEnsureCapacity_real_T(obj->psd, ilast);
    loop_ub = movMeanMagSqrd->size[0];
    for (ilast = 0; ilast < loop_ub; ilast++) {
      obj->psd->data[ilast] = 0.0;
    }
    nx = movMeanMagSqrd->size[1];
    stride = movMeanMagSqrd->size[0];
    loop_ub = movMeanMagSqrd->size[1];
    n = movMeanMagSqrd->size[1];
    for (j = 0; j < stride; j++) {
      ilast = xv->size[0];
      xv->size[0] = nx;
      emxEnsureCapacity_real_T(xv, ilast);
      xv_data = xv->data;
      for (ilast = 0; ilast < loop_ub; ilast++) {
        xv_data[ilast] = 0.0;
      }
      for (midm1 = 0; midm1 < nx; midm1++) {
        xv_data[midm1] = movMeanMagSqrd_data[j + midm1 * stride];
      }
      midm1 = 0;
      int exitg1;
      do {
        exitg1 = 0;
        if (midm1 <= n - 1) {
          if (rtIsNaN(xv_data[midm1])) {
            obj->psd->data[j] = rtNaN;
            exitg1 = 1;
          } else {
            midm1++;
          }
        } else {
          if (n <= 4) {
            if (n == 1) {
              obj->psd->data[j] = xv_data[0];
            } else if (n == 2) {
              if (((xv_data[0] < 0.0) != (xv_data[1] < 0.0)) ||
                  rtIsInf(xv_data[0])) {
                obj->psd->data[j] = (xv_data[0] + xv_data[1]) / 2.0;
              } else {
                obj->psd->data[j] =
                    xv_data[0] + (xv_data[1] - xv_data[0]) / 2.0;
              }
            } else if (n == 3) {
              if (xv_data[0] < xv_data[1]) {
                if (xv_data[1] < xv_data[2]) {
                  ibtile = 1;
                } else if (xv_data[0] < xv_data[2]) {
                  ibtile = 2;
                } else {
                  ibtile = 0;
                }
              } else if (xv_data[0] < xv_data[2]) {
                ibtile = 0;
              } else if (xv_data[1] < xv_data[2]) {
                ibtile = 2;
              } else {
                ibtile = 1;
              }
              obj->psd->data[j] = xv_data[ibtile];
            } else {
              if (xv_data[0] < xv_data[1]) {
                if (xv_data[1] < xv_data[2]) {
                  outsize_idx_0 = 0;
                  ibtile = 1;
                  len = 2;
                } else if (xv_data[0] < xv_data[2]) {
                  outsize_idx_0 = 0;
                  ibtile = 2;
                  len = 1;
                } else {
                  outsize_idx_0 = 2;
                  ibtile = 0;
                  len = 1;
                }
              } else if (xv_data[0] < xv_data[2]) {
                outsize_idx_0 = 1;
                ibtile = 0;
                len = 2;
              } else if (xv_data[1] < xv_data[2]) {
                outsize_idx_0 = 1;
                ibtile = 2;
                len = 0;
              } else {
                outsize_idx_0 = 2;
                ibtile = 1;
                len = 0;
              }
              if (xv_data[outsize_idx_0] < xv_data[3]) {
                if (xv_data[3] < xv_data[len]) {
                  if (((xv_data[ibtile] < 0.0) != (xv_data[3] < 0.0)) ||
                      rtIsInf(xv_data[ibtile])) {
                    obj->psd->data[j] = (xv_data[ibtile] + xv_data[3]) / 2.0;
                  } else {
                    obj->psd->data[j] =
                        xv_data[ibtile] + (xv_data[3] - xv_data[ibtile]) / 2.0;
                  }
                } else if (((xv_data[ibtile] < 0.0) != (xv_data[len] < 0.0)) ||
                           rtIsInf(xv_data[ibtile])) {
                  obj->psd->data[j] = (xv_data[ibtile] + xv_data[len]) / 2.0;
                } else {
                  obj->psd->data[j] =
                      xv_data[ibtile] + (xv_data[len] - xv_data[ibtile]) / 2.0;
                }
              } else if (((xv_data[outsize_idx_0] < 0.0) !=
                          (xv_data[ibtile] < 0.0)) ||
                         rtIsInf(xv_data[outsize_idx_0])) {
                obj->psd->data[j] =
                    (xv_data[outsize_idx_0] + xv_data[ibtile]) / 2.0;
              } else {
                obj->psd->data[j] =
                    xv_data[outsize_idx_0] +
                    (xv_data[ibtile] - xv_data[outsize_idx_0]) / 2.0;
              }
            }
          } else {
            midm1 = n >> 1;
            if ((n & 1) == 0) {
              quickselect(xv, midm1 + 1, n, &varargin_1, &outsize_idx_0,
                          &ilast);
              obj->psd->data[j] = varargin_1;
              if (midm1 < outsize_idx_0) {
                quickselect(xv, midm1, ilast - 1, &b, &ibtile, &len);
                if (((varargin_1 < 0.0) != (b < 0.0)) || rtIsInf(varargin_1)) {
                  obj->psd->data[j] = (varargin_1 + b) / 2.0;
                } else {
                  obj->psd->data[j] = varargin_1 + (b - varargin_1) / 2.0;
                }
              }
            } else {
              quickselect(xv, midm1 + 1, n, &obj->psd->data[j], &outsize_idx_0,
                          &ibtile);
            }
          }
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
  }
  emxFree_real_T(&xv);
  /* transpose(median(transpose(movMeanMagSqrd)));%median(rand(80,32767),2); */
  ilast = movMeanMagSqrd->size[0] * movMeanMagSqrd->size[1];
  movMeanMagSqrd->size[0] = obj->psd->size[0];
  movMeanMagSqrd->size[1] = magSqrd->size[1];
  emxEnsureCapacity_real_T(movMeanMagSqrd, ilast);
  movMeanMagSqrd_data = movMeanMagSqrd->data;
  len = obj->psd->size[0];
  outsize_idx_0 = magSqrd->size[1];
  for (ilast = 0; ilast < outsize_idx_0; ilast++) {
    ibtile = ilast * len;
    for (midm1 = 0; midm1 < len; midm1++) {
      movMeanMagSqrd_data[ibtile + midm1] = obj->psd->data[midm1];
    }
  }
  emxInit_boolean_T(&magSqrdMask, 2);
  if ((magSqrd->size[0] == movMeanMagSqrd->size[0]) &&
      (magSqrd->size[1] == movMeanMagSqrd->size[1])) {
    ilast = magSqrdMask->size[0] * magSqrdMask->size[1];
    magSqrdMask->size[0] = magSqrd->size[0];
    magSqrdMask->size[1] = magSqrd->size[1];
    emxEnsureCapacity_boolean_T(magSqrdMask, ilast);
    magSqrdMask_data = magSqrdMask->data;
    loop_ub = magSqrd->size[0] * magSqrd->size[1];
    for (ilast = 0; ilast < loop_ub; ilast++) {
      magSqrdMask_data[ilast] =
          (magSqrd_data[ilast] > 10.0 * movMeanMagSqrd_data[ilast]);
    }
  } else {
    binary_expand_op(magSqrdMask, magSqrd, movMeanMagSqrd);
    magSqrdMask_data = magSqrdMask->data;
  }
  emxFree_real_T(&movMeanMagSqrd);
  outsize_idx_0 = magSqrdMask->size[0] * magSqrdMask->size[1] - 1;
  len = 0;
  for (ibtile = 0; ibtile <= outsize_idx_0; ibtile++) {
    if (magSqrdMask_data[ibtile]) {
      len++;
    }
  }
  emxInit_int32_T(&r, 1);
  ilast = r->size[0];
  r->size[0] = len;
  emxEnsureCapacity_int32_T(r, ilast);
  r1 = r->data;
  len = 0;
  for (ibtile = 0; ibtile <= outsize_idx_0; ibtile++) {
    if (magSqrdMask_data[ibtile]) {
      r1[len] = ibtile + 1;
      len++;
    }
  }
  emxFree_boolean_T(&magSqrdMask);
  loop_ub = r->size[0];
  for (ilast = 0; ilast < loop_ub; ilast++) {
    magSqrd_data[r1[ilast] - 1] = rtNaN;
  }
  emxFree_int32_T(&r);
  varargin_1 = obj->dt;
  varargin_1 = varargin_1 * varargin_1 / obj->T;
  mean(magSqrd, obj->psd);
  emxFree_real_T(&magSqrd);
  loop_ub = obj->psd->size[0];
  for (ilast = 0; ilast < loop_ub; ilast++) {
    obj->psd->data[ilast] *= varargin_1;
  }
  len = 1;
  if (obj->psd->size[0] != 1) {
    len = obj->psd->size[0];
  }
  if (obj->psd->size[0] == 1) {
    varargin_1 = obj->psd->data[0];
    ilast = obj->psd->size[0];
    obj->psd->size[0] = len;
    emxEnsureCapacity_real_T(obj->psd, ilast);
    for (ilast = 0; ilast < len; ilast++) {
      obj->psd->data[ilast] = varargin_1;
    }
  } else {
    ilast = obj->psd->size[0];
    obj->psd->size[0] = len;
    emxEnsureCapacity_real_T(obj->psd, ilast);
  }
  /* use median to exclude outliers from short pulses */
}

/*
 * File trailer for wfmstft.c
 *
 * [EOF]
 */
