//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: uavrt_detection_rtwutil.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 30-Dec-2022 11:43:16
//

#ifndef UAVRT_DETECTION_RTWUTIL_H
#define UAVRT_DETECTION_RTWUTIL_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>
#include <string>

// Type Declarations
struct rtBoundsCheckInfo;

struct rtEqualityCheckInfo;

struct rtDoubleCheckInfo;

// Function Declarations
extern void c_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum);

extern void c_rtErrorWithMessageID(const int i, const char *aFcnName,
                                   int aLineNum);

extern void d_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void d_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum);

extern int div_s32(int numerator, int denominator);

extern void e_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum);

extern void eb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void emlrtDimSizeImpxCheckR2021b(const int aDim1, const int aDim2,
                                        const rtEqualityCheckInfo *aInfo);

extern void f_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum);

extern void g_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum);

extern void gb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void h_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void hb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void ic_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void k_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void l_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void l_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum);

extern void lb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void m_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void mc_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void pc_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void qc_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void r_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void rtDivisionByZeroErrorN();

extern void rtDynamicBoundsError(int aIndexValue, int aLoBound, int aHiBound,
                                 const rtBoundsCheckInfo *aInfo);

extern void rtErrorWithMessageID(const std::string r, const int i,
                                 const char *aFcnName, int aLineNum);

extern void rtErrorWithMessageID(const char *r, const char *r1,
                                 const char *aFcnName, int aLineNum);

extern void rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern std::string rtGenSizeString(const int aNDims, const int *aDims);

extern void rtIntegerError(const double aInteger,
                           const rtDoubleCheckInfo *aInfo);

extern boolean_T rtIsNullOrEmptyString(const char *aString);

extern void rtNonNegativeError(const double aPositive,
                               const rtDoubleCheckInfo *aInfo);

extern void rtSizeEq1DError(const int aDim1, const int aDim2,
                            const rtEqualityCheckInfo *aInfo);

extern void rtSizeEqNDCheck(const int *aDims1, const int *aDims2,
                            const rtEqualityCheckInfo *aInfo);

extern void rtSubAssignSizeCheck(const int *aDims1, const int aNDims1,
                                 const int *aDims2, const int aNDims2,
                                 const rtEqualityCheckInfo *aInfo);

extern double rt_hypotd_snf(double u0, double u1);

extern double rt_powd_snf(double u0, double u1);

extern void s_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void t_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void ub_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void v_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void yb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

#endif
//
// File trailer for uavrt_detection_rtwutil.h
//
// [EOF]
//
