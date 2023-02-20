//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: pulsestats.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 14:31:55
//

#ifndef PULSESTATS_H
#define PULSESTATS_H

// Include Files
#include "rtwtypes.h"
#include "uavrt_detection_internal_types.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
class pulsestats {
public:
  pulsestats *init(double tp, double tip, double tipu, double tipj,
                   const c_struct_T *b_pl, const c_struct_T *b_clst);
  pulsestats *b_init(double tp, double tip, double tipu, double tipj,
                     double b_fp, double b_fstart, double b_fend,
                     const double b_tmplt[2], char b_mode,
                     const coder::array<c_struct_T, 2U> &b_pl,
                     const coder::array<c_struct_T, 2U> &b_clst,
                     const coder::array<boolean_T, 2U> &b_cmsk,
                     const coder::array<double, 2U> &b_cpki);
  pulsestats *init(double tp, double tip, double tipu, double tipj, double b_fp,
                   const c_struct_T *b_pl, const c_struct_T *b_clst);
  double t_p;
  double t_ip;
  double t_ipu;
  double t_ipj;
  double fp;
  double fstart;
  double fend;
  double tmplt[2];
  char mode;
  coder::array<c_struct_T, 2U> pl;
  coder::array<c_struct_T, 2U> clst;
  coder::array<boolean_T, 2U> cmsk;
  coder::array<double, 2U> cpki;
};

#endif
//
// File trailer for pulsestats.h
//
// [EOF]
//
