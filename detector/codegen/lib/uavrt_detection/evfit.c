/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: evfit.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "evfit.h"
#include "rt_nonfinite.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
/*
 * Arguments    : const double x[100]
 *                double parmhat[2]
 * Return Type  : void
 */
void evfit(const double x[100], double parmhat[2])
{
  double m;
  double rangex;
  double tempMax;
  double tempMin;
  int i;
  tempMin = rtInf;
  tempMax = rtMinusInf;
  for (i = 0; i < 100; i++) {
    m = x[i];
    if (m > tempMax) {
      tempMax = m;
    }
    if (m < tempMin) {
      tempMin = m;
    }
  }
  rangex = tempMax - tempMin;
  if (rtIsInf(rangex) || rtIsNaN(rangex)) {
    parmhat[0] = rtNaN;
    parmhat[1] = rtNaN;
  } else if (rangex < 2.2250738585072014E-308) {
    parmhat[0] = x[0];
    parmhat[1] = 0.0;
  } else {
    double absdiff[100];
    double b_x[100];
    double x0[100];
    double fb;
    double scale;
    double sigmahat;
    double t;
    double upper;
    double wgtmeanUnc;
    for (i = 0; i < 100; i++) {
      x0[i] = (x[i] - tempMax) / rangex;
    }
    tempMin = x0[0];
    for (i = 0; i < 99; i++) {
      tempMin += x0[i + 1];
    }
    tempMin /= 100.0;
    fb = 0.0;
    scale = 3.3121686421112381E-170;
    for (i = 0; i < 100; i++) {
      m = fabs(x0[i] - tempMin);
      if (m > scale) {
        t = scale / m;
        fb = fb * t * t + 1.0;
        scale = m;
      } else {
        t = m / scale;
        fb += t * t;
      }
    }
    fb = scale * sqrt(fb);
    fb /= 9.9498743710662;
    sigmahat = 2.4494897427831779 * fb / 3.1415926535897931;
    fb = x0[0];
    for (i = 0; i < 99; i++) {
      fb += x0[i + 1];
    }
    wgtmeanUnc = fb / 100.0;
    for (i = 0; i < 100; i++) {
      m = x0[i];
      tempMin = exp(m / sigmahat);
      absdiff[i] = tempMin;
      b_x[i] = m * tempMin;
    }
    fb = b_x[0];
    tempMin = absdiff[0];
    for (i = 0; i < 99; i++) {
      fb += b_x[i + 1];
      tempMin += absdiff[i + 1];
    }
    if ((sigmahat + wgtmeanUnc) - fb / tempMin > 0.0) {
      upper = sigmahat;
      sigmahat *= 0.5;
      int exitg1;
      do {
        exitg1 = 0;
        for (i = 0; i < 100; i++) {
          m = x0[i];
          tempMin = exp(m / sigmahat);
          absdiff[i] = tempMin;
          b_x[i] = m * tempMin;
        }
        fb = b_x[0];
        tempMin = absdiff[0];
        for (i = 0; i < 99; i++) {
          fb += b_x[i + 1];
          tempMin += absdiff[i + 1];
        }
        if ((sigmahat + wgtmeanUnc) - fb / tempMin > 0.0) {
          upper = sigmahat;
          sigmahat *= 0.5;
        } else {
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    } else {
      upper = 2.0 * sigmahat;
      int exitg1;
      do {
        exitg1 = 0;
        for (i = 0; i < 100; i++) {
          m = x0[i];
          tempMin = exp(m / upper);
          absdiff[i] = tempMin;
          b_x[i] = m * tempMin;
        }
        fb = b_x[0];
        tempMin = absdiff[0];
        for (i = 0; i < 99; i++) {
          fb += b_x[i + 1];
          tempMin += absdiff[i + 1];
        }
        if ((upper + wgtmeanUnc) - fb / tempMin < 0.0) {
          sigmahat = upper;
          upper *= 2.0;
        } else {
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
    for (i = 0; i < 100; i++) {
      m = x0[i];
      tempMin = exp(m / sigmahat);
      absdiff[i] = tempMin;
      b_x[i] = m * tempMin;
    }
    fb = b_x[0];
    tempMin = absdiff[0];
    for (i = 0; i < 99; i++) {
      fb += b_x[i + 1];
      tempMin += absdiff[i + 1];
    }
    scale = (sigmahat + wgtmeanUnc) - fb / tempMin;
    for (i = 0; i < 100; i++) {
      m = x0[i];
      tempMin = exp(m / upper);
      absdiff[i] = tempMin;
      b_x[i] = m * tempMin;
    }
    fb = b_x[0];
    tempMin = absdiff[0];
    for (i = 0; i < 99; i++) {
      fb += b_x[i + 1];
      tempMin += absdiff[i + 1];
    }
    fb = (upper + wgtmeanUnc) - fb / tempMin;
    if (scale == 0.0) {
      upper = sigmahat;
    } else if (!(fb == 0.0)) {
      double c;
      double d;
      double e;
      double fc;
      bool exitg2;
      fc = fb;
      c = upper;
      e = 0.0;
      d = 0.0;
      exitg2 = false;
      while ((!exitg2) && ((fb != 0.0) && (sigmahat != upper))) {
        double toler;
        if ((fb > 0.0) == (fc > 0.0)) {
          c = sigmahat;
          fc = scale;
          d = upper - sigmahat;
          e = d;
        }
        if (fabs(fc) < fabs(fb)) {
          sigmahat = upper;
          upper = c;
          c = sigmahat;
          scale = fb;
          fb = fc;
          fc = scale;
        }
        m = 0.5 * (c - upper);
        toler = 2.0E-6 * fmax(fabs(upper), 1.0);
        if ((fabs(m) <= toler) || (fb == 0.0)) {
          exitg2 = true;
        } else {
          if ((fabs(e) < toler) || (fabs(scale) <= fabs(fb))) {
            d = m;
            e = m;
          } else {
            double s;
            s = fb / scale;
            if (sigmahat == c) {
              tempMin = 2.0 * m * s;
              scale = 1.0 - s;
            } else {
              scale /= fc;
              t = fb / fc;
              tempMin = s * (2.0 * m * scale * (scale - t) -
                             (upper - sigmahat) * (t - 1.0));
              scale = (scale - 1.0) * (t - 1.0) * (s - 1.0);
            }
            if (tempMin > 0.0) {
              scale = -scale;
            } else {
              tempMin = -tempMin;
            }
            if ((2.0 * tempMin < 3.0 * m * scale - fabs(toler * scale)) &&
                (tempMin < fabs(0.5 * e * scale))) {
              e = d;
              d = tempMin / scale;
            } else {
              d = m;
              e = m;
            }
          }
          sigmahat = upper;
          scale = fb;
          if (fabs(d) > toler) {
            upper += d;
          } else if (upper > c) {
            upper -= toler;
          } else {
            upper += toler;
          }
          for (i = 0; i < 100; i++) {
            m = x0[i];
            tempMin = exp(m / upper);
            absdiff[i] = tempMin;
            b_x[i] = m * tempMin;
          }
          fb = b_x[0];
          tempMin = absdiff[0];
          for (i = 0; i < 99; i++) {
            fb += b_x[i + 1];
            tempMin += absdiff[i + 1];
          }
          fb = (upper + wgtmeanUnc) - fb / tempMin;
        }
      }
    }
    for (i = 0; i < 100; i++) {
      x0[i] = exp(x0[i] / upper);
    }
    fb = x0[0];
    for (i = 0; i < 99; i++) {
      fb += x0[i + 1];
    }
    parmhat[0] = rangex * (upper * log(fb / 100.0)) + tempMax;
    parmhat[1] = rangex * upper;
  }
}

/*
 * File trailer for evfit.c
 *
 * [EOF]
 */
