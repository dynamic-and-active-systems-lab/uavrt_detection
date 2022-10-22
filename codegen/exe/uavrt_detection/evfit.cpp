//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: evfit.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 22-Oct-2022 15:24:58
//

// Include Files
#include "evfit.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const double x[100]
//                double parmhat[2]
// Return Type  : void
//
namespace coder {
void evfit(const double x[100], double parmhat[2])
{
  double m;
  double rangex;
  double tempMax;
  double tempMin;
  tempMin = rtInf;
  tempMax = rtMinusInf;
  for (int i{0}; i < 100; i++) {
    m = x[i];
    if (m > tempMax) {
      tempMax = m;
    }
    if (m < tempMin) {
      tempMin = m;
    }
  }
  rangex = tempMax - tempMin;
  if (std::isinf(rangex) || std::isnan(rangex)) {
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
    for (int i{0}; i < 100; i++) {
      x0[i] = (x[i] - tempMax) / rangex;
    }
    tempMin = x0[0];
    for (int i{0}; i < 99; i++) {
      tempMin += x0[i + 1];
    }
    tempMin /= 100.0;
    fb = 0.0;
    scale = 3.3121686421112381E-170;
    for (int i{0}; i < 100; i++) {
      m = std::abs(x0[i] - tempMin);
      if (m > scale) {
        t = scale / m;
        fb = fb * t * t + 1.0;
        scale = m;
      } else {
        t = m / scale;
        fb += t * t;
      }
    }
    fb = scale * std::sqrt(fb);
    fb /= 9.9498743710662;
    sigmahat = 2.4494897427831779 * fb / 3.1415926535897931;
    fb = x0[0];
    for (int i{0}; i < 99; i++) {
      fb += x0[i + 1];
    }
    wgtmeanUnc = fb / 100.0;
    for (int i{0}; i < 100; i++) {
      m = x0[i];
      tempMin = std::exp(m / sigmahat);
      absdiff[i] = tempMin;
      b_x[i] = m * tempMin;
    }
    fb = b_x[0];
    tempMin = absdiff[0];
    for (int i{0}; i < 99; i++) {
      fb += b_x[i + 1];
      tempMin += absdiff[i + 1];
    }
    if ((sigmahat + wgtmeanUnc) - fb / tempMin > 0.0) {
      upper = sigmahat;
      sigmahat *= 0.5;
      int exitg1;
      do {
        exitg1 = 0;
        for (int i{0}; i < 100; i++) {
          m = x0[i];
          tempMin = std::exp(m / sigmahat);
          absdiff[i] = tempMin;
          b_x[i] = m * tempMin;
        }
        fb = b_x[0];
        tempMin = absdiff[0];
        for (int i{0}; i < 99; i++) {
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
        for (int i{0}; i < 100; i++) {
          m = x0[i];
          tempMin = std::exp(m / upper);
          absdiff[i] = tempMin;
          b_x[i] = m * tempMin;
        }
        fb = b_x[0];
        tempMin = absdiff[0];
        for (int i{0}; i < 99; i++) {
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
    for (int i{0}; i < 100; i++) {
      m = x0[i];
      tempMin = std::exp(m / sigmahat);
      absdiff[i] = tempMin;
      b_x[i] = m * tempMin;
    }
    fb = b_x[0];
    tempMin = absdiff[0];
    for (int i{0}; i < 99; i++) {
      fb += b_x[i + 1];
      tempMin += absdiff[i + 1];
    }
    scale = (sigmahat + wgtmeanUnc) - fb / tempMin;
    for (int i{0}; i < 100; i++) {
      m = x0[i];
      tempMin = std::exp(m / upper);
      absdiff[i] = tempMin;
      b_x[i] = m * tempMin;
    }
    fb = b_x[0];
    tempMin = absdiff[0];
    for (int i{0}; i < 99; i++) {
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
      boolean_T exitg2;
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
        if (std::abs(fc) < std::abs(fb)) {
          sigmahat = upper;
          upper = c;
          c = sigmahat;
          scale = fb;
          fb = fc;
          fc = scale;
        }
        m = 0.5 * (c - upper);
        toler = 2.0E-6 * std::fmax(std::abs(upper), 1.0);
        if ((std::abs(m) <= toler) || (fb == 0.0)) {
          exitg2 = true;
        } else {
          if ((std::abs(e) < toler) || (std::abs(scale) <= std::abs(fb))) {
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
            if ((2.0 * tempMin < 3.0 * m * scale - std::abs(toler * scale)) &&
                (tempMin < std::abs(0.5 * e * scale))) {
              e = d;
              d = tempMin / scale;
            } else {
              d = m;
              e = m;
            }
          }
          sigmahat = upper;
          scale = fb;
          if (std::abs(d) > toler) {
            upper += d;
          } else if (upper > c) {
            upper -= toler;
          } else {
            upper += toler;
          }
          for (int i{0}; i < 100; i++) {
            m = x0[i];
            tempMin = std::exp(m / upper);
            absdiff[i] = tempMin;
            b_x[i] = m * tempMin;
          }
          fb = b_x[0];
          tempMin = absdiff[0];
          for (int i{0}; i < 99; i++) {
            fb += b_x[i + 1];
            tempMin += absdiff[i + 1];
          }
          fb = (upper + wgtmeanUnc) - fb / tempMin;
        }
      }
    }
    for (int i{0}; i < 100; i++) {
      x0[i] = std::exp(x0[i] / upper);
    }
    fb = x0[0];
    for (int i{0}; i < 99; i++) {
      fb += x0[i + 1];
    }
    parmhat[0] = rangex * (upper * std::log(fb / 100.0)) + tempMax;
    parmhat[1] = rangex * upper;
  }
}

} // namespace coder

//
// File trailer for evfit.cpp
//
// [EOF]
//
