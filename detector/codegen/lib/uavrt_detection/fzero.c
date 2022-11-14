/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: fzero.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "fzero.h"
#include "rt_nonfinite.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
/*
 * Arguments    : double FunFcn_workspace_mu
 *                double FunFcn_workspace_sigma
 *                double FunFcn_workspace_pf
 * Return Type  : double
 */
double fzero(double FunFcn_workspace_mu, double FunFcn_workspace_sigma,
             double FunFcn_workspace_pf)
{
  double b;
  double fx;
  fx =
      (1.0 - exp(-exp((-0.0 - FunFcn_workspace_mu) / FunFcn_workspace_sigma))) -
      FunFcn_workspace_pf;
  if (fx == 0.0) {
    b = 0.0;
  } else {
    double a;
    double dx;
    double fb;
    int exitg2;
    dx = 0.02;
    a = 0.0;
    b = 0.0;
    fb = fx;
    do {
      exitg2 = 0;
      if ((fx > 0.0) == (fb > 0.0)) {
        dx *= 1.4142135623730951;
        a = 0.0 - dx;
        fx = (1.0 - exp(-exp((-(0.0 - dx) - FunFcn_workspace_mu) /
                             FunFcn_workspace_sigma))) -
             FunFcn_workspace_pf;
        if (rtIsInf(fx) || rtIsNaN(fx)) {
          b = rtNaN;
          exitg2 = 1;
        } else if (rtIsInf(0.0 - dx)) {
          b = rtNaN;
          exitg2 = 1;
        } else if ((fx > 0.0) != (fb > 0.0)) {
          exitg2 = 2;
        } else {
          b = dx;
          fb = (1.0 - exp(-exp((-dx - FunFcn_workspace_mu) /
                               FunFcn_workspace_sigma))) -
               FunFcn_workspace_pf;
          if (rtIsInf(fb) || rtIsNaN(fb)) {
            b = rtNaN;
            exitg2 = 1;
          } else if (rtIsInf(dx)) {
            b = rtNaN;
            exitg2 = 1;
          }
        }
      } else {
        exitg2 = 2;
      }
    } while (exitg2 == 0);
    if (exitg2 != 1) {
      double c;
      double d;
      double e;
      double fc;
      bool exitg1;
      fc = fb;
      c = b;
      e = 0.0;
      d = 0.0;
      exitg1 = false;
      while ((!exitg1) && ((fb != 0.0) && (a != b))) {
        double m;
        double toler;
        if ((fb > 0.0) == (fc > 0.0)) {
          c = a;
          fc = fx;
          d = b - a;
          e = d;
        }
        if (fabs(fc) < fabs(fb)) {
          a = b;
          b = c;
          c = a;
          fx = fb;
          fb = fc;
          fc = fx;
        }
        m = 0.5 * (c - b);
        toler = 4.4408920985006262E-16 * fmax(fabs(b), 1.0);
        if ((fabs(m) <= toler) || (fb == 0.0)) {
          exitg1 = true;
        } else {
          if ((fabs(e) < toler) || (fabs(fx) <= fabs(fb))) {
            d = m;
            e = m;
          } else {
            double s;
            s = fb / fx;
            if (a == c) {
              dx = 2.0 * m * s;
              fx = 1.0 - s;
            } else {
              double r;
              fx /= fc;
              r = fb / fc;
              dx = s * (2.0 * m * fx * (fx - r) - (b - a) * (r - 1.0));
              fx = (fx - 1.0) * (r - 1.0) * (s - 1.0);
            }
            if (dx > 0.0) {
              fx = -fx;
            } else {
              dx = -dx;
            }
            if ((2.0 * dx < 3.0 * m * fx - fabs(toler * fx)) &&
                (dx < fabs(0.5 * e * fx))) {
              e = d;
              d = dx / fx;
            } else {
              d = m;
              e = m;
            }
          }
          a = b;
          fx = fb;
          if (fabs(d) > toler) {
            b += d;
          } else if (b > c) {
            b -= toler;
          } else {
            b += toler;
          }
          fb =
              (1.0 -
               exp(-exp((-b - FunFcn_workspace_mu) / FunFcn_workspace_sigma))) -
              FunFcn_workspace_pf;
        }
      }
    }
  }
  return b;
}

/*
 * File trailer for fzero.c
 *
 * [EOF]
 */
