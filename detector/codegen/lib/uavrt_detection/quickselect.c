/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: quickselect.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "quickselect.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"

/* Function Declarations */
static int thirdOfFive(const emxArray_real_T *v, int ia, int ib);

/* Function Definitions */
/*
 * Arguments    : const emxArray_real_T *v
 *                int ia
 *                int ib
 * Return Type  : int
 */
static int thirdOfFive(const emxArray_real_T *v, int ia, int ib)
{
  const double *v_data;
  int im;
  v_data = v->data;
  if ((ia == ib) || (ia + 1 == ib)) {
    im = ia;
  } else if ((ia + 2 == ib) || (ia + 3 == ib)) {
    double v4;
    v4 = v_data[ia - 1];
    if (v4 < v_data[ia]) {
      if (v_data[ia] < v_data[ia + 1]) {
        im = ia + 1;
      } else if (v_data[ia - 1] < v_data[ia + 1]) {
        im = ia + 2;
      } else {
        im = ia;
      }
    } else if (v4 < v_data[ia + 1]) {
      im = ia;
    } else if (v_data[ia] < v_data[ia + 1]) {
      im = ia + 2;
    } else {
      im = ia + 1;
    }
  } else {
    double v4;
    double v5;
    int j2;
    int j3;
    int j4;
    int j5;
    v4 = v_data[ia - 1];
    if (v4 < v_data[ia]) {
      v5 = v_data[ia + 1];
      if (v_data[ia] < v5) {
        im = ia;
        j2 = ia;
        j3 = ia + 2;
      } else if (v4 < v5) {
        im = ia;
        j2 = ia + 1;
        j3 = ia + 1;
      } else {
        im = ia + 2;
        j2 = ia - 1;
        j3 = ia + 1;
      }
    } else {
      v5 = v_data[ia + 1];
      if (v4 < v5) {
        im = ia + 1;
        j2 = ia - 1;
        j3 = ia + 2;
      } else if (v_data[ia] < v5) {
        im = ia + 1;
        j2 = ia + 1;
        j3 = ia;
      } else {
        im = ia + 2;
        j2 = ia;
        j3 = ia;
      }
    }
    j4 = ia;
    j5 = ia + 1;
    v4 = v_data[ia + 2];
    v5 = v_data[ia + 3];
    if (v5 < v4) {
      j4 = ia + 1;
      j5 = ia;
      v5 = v4;
      v4 = v_data[ia + 3];
    }
    if (!(v5 < v_data[im - 1])) {
      if (v5 < v_data[j2]) {
        im = j5 + 3;
      } else if (v4 < v_data[j2]) {
        im = j2 + 1;
      } else if (v4 < v_data[j3 - 1]) {
        im = j4 + 3;
      } else {
        im = j3;
      }
    }
  }
  return im;
}

/*
 * Arguments    : emxArray_real_T *v
 *                int n
 *                int vlen
 *                double *vn
 *                int *nfirst
 *                int *nlast
 * Return Type  : void
 */
void quickselect(emxArray_real_T *v, int n, int vlen, double *vn, int *nfirst,
                 int *nlast)
{
  double *v_data;
  int k;
  v_data = v->data;
  if (n > vlen) {
    *vn = rtNaN;
    *nfirst = 0;
    *nlast = 0;
  } else {
    int ia;
    int ib;
    int ilast;
    int ipiv;
    int oldnv;
    bool checkspeed;
    bool exitg1;
    bool isslow;
    ipiv = n;
    ia = 0;
    ib = vlen - 1;
    *nfirst = 1;
    ilast = vlen - 1;
    oldnv = vlen;
    checkspeed = false;
    isslow = false;
    exitg1 = false;
    while ((!exitg1) && (ia + 1 < ib + 1)) {
      double vref;
      bool guard1 = false;
      vref = v_data[ipiv - 1];
      v_data[ipiv - 1] = v_data[ib];
      v_data[ib] = vref;
      ilast = ia;
      ipiv = -1;
      for (k = ia + 1; k <= ib; k++) {
        double d;
        double vk;
        vk = v_data[k - 1];
        d = v_data[k - 1];
        if (d == vref) {
          v_data[k - 1] = v_data[ilast];
          v_data[ilast] = vk;
          ipiv++;
          ilast++;
        } else if (d < vref) {
          v_data[k - 1] = v_data[ilast];
          v_data[ilast] = vk;
          ilast++;
        }
      }
      v_data[ib] = v_data[ilast];
      v_data[ilast] = vref;
      guard1 = false;
      if (n <= ilast + 1) {
        *nfirst = ilast - ipiv;
        if (n >= *nfirst) {
          exitg1 = true;
        } else {
          ib = ilast - 1;
          guard1 = true;
        }
      } else {
        ia = ilast + 1;
        guard1 = true;
      }
      if (guard1) {
        int c;
        c = (ib - ia) + 1;
        if (checkspeed) {
          isslow = (c > oldnv / 2);
          oldnv = c;
        }
        checkspeed = !checkspeed;
        if (isslow) {
          while (c > 1) {
            int ngroupsof5;
            ngroupsof5 = c / 5;
            *nlast = c - ngroupsof5 * 5;
            c = ngroupsof5;
            for (k = 0; k < ngroupsof5; k++) {
              ipiv = (ia + k * 5) + 1;
              ipiv = thirdOfFive(v, ipiv, ipiv + 4) - 1;
              ilast = ia + k;
              vref = v_data[ilast];
              v_data[ilast] = v_data[ipiv];
              v_data[ipiv] = vref;
            }
            if (*nlast > 0) {
              ipiv = (ia + ngroupsof5 * 5) + 1;
              ipiv = thirdOfFive(v, ipiv, (ipiv + *nlast) - 1) - 1;
              ilast = ia + ngroupsof5;
              vref = v_data[ilast];
              v_data[ilast] = v_data[ipiv];
              v_data[ipiv] = vref;
              c = ngroupsof5 + 1;
            }
          }
        } else if (c >= 3) {
          ipiv = ia + (int)((unsigned int)(c - 1) >> 1);
          if (v_data[ia] < v_data[ipiv]) {
            if (!(v_data[ipiv] < v_data[ib])) {
              if (v_data[ia] < v_data[ib]) {
                ipiv = ib;
              } else {
                ipiv = ia;
              }
            }
          } else if (v_data[ia] < v_data[ib]) {
            ipiv = ia;
          } else if (v_data[ipiv] < v_data[ib]) {
            ipiv = ib;
          }
          if (ipiv + 1 > ia + 1) {
            vref = v_data[ia];
            v_data[ia] = v_data[ipiv];
            v_data[ipiv] = vref;
          }
        }
        ipiv = ia + 1;
        *nfirst = ia + 1;
        ilast = ib;
      }
    }
    *vn = v_data[ilast];
    *nlast = ilast + 1;
  }
}

/*
 * File trailer for quickselect.c
 *
 * [EOF]
 */
