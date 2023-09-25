//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: uavrt_detection_rtwutil.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 25-Sep-2023 11:48:59
//

#ifndef UAVRT_DETECTION_RTWUTIL_H
#define UAVRT_DETECTION_RTWUTIL_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>
#include <string>

// Type Declarations
struct rtDoubleCheckInfo;

struct rtEqualityCheckInfo;

struct rtBoundsCheckInfo;

// Function Declarations
extern void b_rtErrorWithMessageID(const int i, const char *aFcnName,
                                   int aLineNum);

extern void c_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void cb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void cc_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern int div_s32(int numerator, int denominator);

extern void e_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum);

extern void emlrtDimSizeImpxCheckR2021b(const int aDim1, const int aDim2,
                                        const rtEqualityCheckInfo &aInfo);

extern void fb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void g_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void g_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum);

extern void gb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void h_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum);

extern void i_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void i_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum);

extern void ib_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void j_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void j_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum);

extern void jb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void k_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void l_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void m_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void ob_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void oc_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void pc_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void q_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void rtDivisionByZeroErrorN();

extern void rtDynamicBoundsError(int aIndexValue, int aLoBound, int aHiBound,
                                 const rtBoundsCheckInfo &aInfo);

extern void rtErrorWithMessageID(const char *r, const char *aFcnName,
                                 int aLineNum);

extern void rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void rtErrorWithMessageID(const std::string r, const int i,
                                 const char *aFcnName, int aLineNum);

extern std::string rtGenSizeString(const int aNDims, const int *aDims);

extern void rtIntegerError(const double aInteger,
                           const rtDoubleCheckInfo &aInfo);

extern boolean_T rtIsNullOrEmptyString(const char *aString);

extern void rtNonNegativeError(const double aPositive,
                               const rtDoubleCheckInfo &aInfo);

extern void rtSizeEq1DError(const int aDim1, const int aDim2,
                            const rtEqualityCheckInfo &aInfo);

extern void rtSizeEqNDCheck(const int *aDims1, const int *aDims2,
                            const rtEqualityCheckInfo &aInfo);

extern void rtSubAssignSizeCheck(const int *aDims1, const int aNDims1,
                                 const int *aDims2, const int aNDims2,
                                 const rtEqualityCheckInfo &aInfo);

extern double rt_hypotd_snf(double u0, double u1);

extern double rt_powd_snf(double u0, double u1);

extern void s_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void u_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void v_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void xb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void y_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

#endif
//
// File trailer for uavrt_detection_rtwutil.h
//
// [EOF]
//
