//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: waveform.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 16-Feb-2023 15:25:26
//

// Include Files
#include "waveform.h"
#include "FFTImplementationCallback.h"
#include "abs.h"
#include "all.h"
#include "allOrAny.h"
#include "assembleWq.h"
#include "assertCompatibleDims.h"
#include "assertValidSizeArg.h"
#include "buildtimecorrelatormatrix.h"
#include "circshift.h"
#include "eml_int_forloop_overflow_check.h"
#include "fftshift.h"
#include "find.h"
#include "function_handle.h"
#include "ifWhileCond.h"
#include "imresize.h"
#include "incohsumtoeplitz.h"
#include "indexShapeCheck.h"
#include "interp1.h"
#include "linspace.h"
#include "log10.h"
#include "makepulsestruc.h"
#include "mean.h"
#include "minOrMax.h"
#include "norm.h"
#include "pulsestats.h"
#include "repmat.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include "sparse1.h"
#include "sqrt.h"
#include "stft.h"
#include "strcmp.h"
#include "sub2ind.h"
#include "sum.h"
#include "threshold.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_internal_types.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "unaryMinOrMax.h"
#include "validator_check_size.h"
#include "vecfind.h"
#include "weightingmatrix.h"
#include "wfmstft.h"
#include "coder_array.h"
#include "omp.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string.h>
#include <string>

// Variable Definitions
static rtRunTimeErrorInfo r_emlrtRTEI{ 18,// lineNo
  "check_order"                        // fName
};

static rtRunTimeErrorInfo s_emlrtRTEI{ 22,// lineNo
  "check_order"                        // fName
};

// Function Declarations
static void b_and(coder::array<boolean_T, 2U> &in1, const coder::array<boolean_T,
                  2U> &in2);
static void b_binary_expand_op(coder::array<boolean_T, 2U> &in1, const coder::
  array<double, 2U> &in2, const int in3[2], const coder::array<double, 2U> &in4,
  const int in5[2]);
static void b_or(coder::array<boolean_T, 1U> &in1, const coder::array<boolean_T,
                 1U> &in2);
static void b_plus(coder::array<double, 2U> &in1, const coder::array<double, 2U>
                   &in2);
static void b_rtErrorWithMessageID(const char *r, const char *aFcnName, int
  aLineNum);
static void binary_expand_op(coder::array<double, 1U> &in1, const coder::array<
  double, 2U> &in2, const coder::array<double, 2U> &in3);
static void binary_expand_op(coder::array<double, 2U> &in1, double in2, const
  coder::array<double, 2U> &in3);
static void binary_expand_op(coder::array<double, 2U> &in1, const coder::array<
  double, 2U> &in2, const coder::array<double, 2U> &in3, int in4, int in5);
static void binary_expand_op(coder::array<double, 2U> &in1, const waveform *in2);
static void c_and(coder::array<boolean_T, 1U> &in1, const coder::array<boolean_T,
                  1U> &in2);
static void c_binary_expand_op(coder::array<boolean_T, 2U> &in1, const coder::
  array<double, 2U> &in2, const int in3[2], const coder::array<double, 2U> &in4,
  const int in5[2]);
static void d_and(coder::array<boolean_T, 1U> &in1, const coder::array<boolean_T,
                  1U> &in2, const coder::array<boolean_T, 1U> &in3);
static void d_binary_expand_op(coder::array<boolean_T, 2U> &in1, const coder::
  array<double, 2U> &in2, const int in3[2], const coder::array<double, 2U> &in4);
static void e_binary_expand_op(coder::array<boolean_T, 2U> &in1, const coder::
  array<double, 2U> &in2, const int in3[2], const coder::array<double, 2U> &in4);
static void f_binary_expand_op(coder::array<double, 2U> &in1, double in2, const
  coder::array<double, 2U> &in3);
static void g_binary_expand_op(coder::array<double, 1U> &in1, const coder::array<
  boolean_T, 1U> &in2);
static void h_binary_expand_op(coder::array<boolean_T, 1U> &in1, const coder::
  array<double, 1U> &in2, const waveform *in3);
static void i_binary_expand_op(coder::array<double, 1U> &in1, const coder::array<
  double, 1U> &in2, const coder::array<boolean_T, 1U> &in3);
static void j_binary_expand_op(coder::array<boolean_T, 1U> &in1, const coder::
  array<boolean_T, 1U> &in2, const coder::array<boolean_T, 1U> &in3);
static void k_binary_expand_op(coder::array<boolean_T, 1U> &in1, const coder::
  array<boolean_T, 1U> &in2, const coder::array<boolean_T, 1U> &in3);
static void l_binary_expand_op(coder::array<boolean_T, 1U> &in1, const coder::
  array<double, 1U> &in2, int in3, const coder::array<double, 1U> &in4);
static void minus(coder::array<double, 2U> &in1, const coder::array<double, 2U>
                  &in2);
static void n_binary_expand_op(coder::array<boolean_T, 1U> &in1, const coder::
  array<boolean_T, 2U> &in2, const coder::array<boolean_T, 2U> &in3);
static void o_rtErrorWithMessageID(const char *aFcnName, int aLineNum);
static void rdivide(coder::array<double, 2U> &in1, const coder::array<double, 2U>
                    &in2);

// Function Definitions
//
// FINDPULSE Looks for pulses in the waveform based on its pulse
// statistics object
//
// This method implemets the incoherent summation algorithm for
// the waveform. The number of pulses summed (blocks considere)
// is defined based on the length of obj.x and its priori
// pulsestats object. When the waveform object is created, the
// length of data (x property) included should be defined to be
// long enough so that it is assure to contain no fewer than K
// pulses. This method doesn't know K, but will create as many
// blocks as it can based on the priori information.
//
// Note: The algorithm used for pulse peak energy detection
// requires that the center frequency of the pulse not be at the
// edges of the frequency bins in Wf. There needs to be rolloff
// in signal power above and below the pulse center frequency.
// Pulses at or just above/below the upper/lower limits of Wf may
// exceeed the threshold for detection, but not get recorded in
// the pl_out because the peeling algorithm can't catch them. If
// this happens, the frequencies used in the priori to describe
// the bounds of the pulse frequencies should be adjusted or
// widened to ensure the pulse's spectral power has rolloff above
// and below the center frequency and that this rolloff is within
// the bounds of the Wf input.
//
//
// INPUTS:
//     obj            Waveform object
//     W              spectral weighting matrix
//     Wf             frequencies list from baseband of
//                    corresponding to each row of W
//     time_searchtype     'naive' or 'informed'
//     freq_searchtype     'naive' or 'informed'
//     excluded_freq_bands_in   nx2    matrix of bands of
//                                  frequencies to exclude in
//                                  the search. This is useful if
//                                  there has already been a tag
//                                  found and you want to exclude
//                                  that band when looking for
//                                  other frequencies. The lower
//                                  frequecies of the band should
//                                  be in the first column and
//                                  the upper should be in the
//                                  second. Leave empty [] if no
//                                  exclusion zones are
//                                  necessary. These frequencies
//                                  are used regardless of the
//                                  freq_searchtype setting.
// OUPUTS:
//  pl_out      A matrix of all potential pulses. This will
//                have as many rows as Wf elements and as many
//                rows as blocks that were possible given the
//                length of the data in obj. The number of pulses
//                to be searched for would be defined at the
//                time of the creation of obj and used to define
//                the length of its data.
//
//    indiv_msk   A logical matrix who's columns identify the
//                peaks and sideband locations in the spectrum of
//                each peak. The ith column of indiv_msk
//                identifies the spectral location of the ith
//                most powerful pulse group identified.
//    peak_ind    A vector of the frequency indicies (of Wf)
//                where the power of the pulses were found.
//                These are the row indicies of pl_out where the
//                peaks exist.
//                These are the center frequency of the pulse
//                where the most energy was detected. The
//                sidebands of the ith peak listed in peak_ind is
//                identified in the ith column of indiv_msk
//
//             %%
//
// Arguments    : const char time_searchtype_data[]
//                const int time_searchtype_size[2]
//                const char freq_searchtype_data[]
//                const int freq_searchtype_size[2]
//                const coder::array<double, 2U> &excluded_freq_bands_in
//                coder::array<c_struct_T, 2U> &pl_out
//                coder::array<boolean_T, 2U> &indiv_msk
//                coder::array<double, 1U> &peak_ind
// Return Type  : void
//
void waveform::findpulse(const char time_searchtype_data[], const int
  time_searchtype_size[2], const char freq_searchtype_data[], const int
  freq_searchtype_size[2], const coder::array<double, 2U>
  &excluded_freq_bands_in, coder::array<c_struct_T, 2U> &pl_out, coder::array<
  boolean_T, 2U> &indiv_msk, coder::array<double, 1U> &peak_ind) const
{
  static rtBoundsCheckInfo ac_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    977,                               // lineNo
    36,                                // colNo
    "peak_ind",                        // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ad_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1042,                              // lineNo
    68,                                // colNo
    "peak_ind",                        // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ae_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1143,                              // lineNo
    47,                                // colNo
    "bandwidth_of_peak",               // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo af_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1232,                              // lineNo
    82,                                // colNo
    "obj.stft.t",                      // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ag_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1254,                              // lineNo
    34,                                // colNo
    "cur_pl",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo bc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    991,                               // lineNo
    61,                                // colNo
    "peak_ind",                        // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo bd_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1042,                              // lineNo
    97,                                // colNo
    "peak_ind",                        // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo be_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1043,                              // lineNo
    87,                                // colNo
    "thresh",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo bf_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1235,                              // lineNo
    42,                                // colNo
    "obj.Wf",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo bg_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1191,                              // lineNo
    37,                                // colNo
    "indiv_msk",                       // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo cc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    991,                               // lineNo
    52,                                // colNo
    "S_cols",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo cd_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1043,                              // lineNo
    68,                                // colNo
    "peak_ind",                        // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ce_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1043,                              // lineNo
    101,                               // colNo
    "thresh",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo cf_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1235,                              // lineNo
    52,                                // colNo
    "obj.Wf",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo cg_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1191,                              // lineNo
    39,                                // colNo
    "indiv_msk",                       // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo dc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    991,                               // lineNo
    64,                                // colNo
    "S_cols",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo dd_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1043,                              // lineNo
    96,                                // colNo
    "peak_ind",                        // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo de_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1043,                              // lineNo
    59,                                // colNo
    "scores",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo df_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1236,                              // lineNo
    42,                                // colNo
    "obj.Wf",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo dg_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1054,                              // lineNo
    62,                                // colNo
    "slope_val",                       // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo eb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    662,                               // lineNo
    29,                                // colNo
    "timeSearchRange",                 // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ec_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    991,                               // lineNo
    76,                                // colNo
    "S_cols",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ed_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1053,                              // lineNo
    71,                                // colNo
    "peak_ind",                        // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ee_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1043,                              // lineNo
    73,                                // colNo
    "scores",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ef_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1236,                              // lineNo
    52,                                // colNo
    "obj.Wf",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo eg_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1054,                              // lineNo
    76,                                // colNo
    "slope_val",                       // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo fb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    664,                               // lineNo
    56,                                // colNo
    "timeSearchRange",                 // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo fc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1009,                              // lineNo
    67,                                // colNo
    "peak_ind",                        // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo fd_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1054,                              // lineNo
    71,                                // colNo
    "peak_ind",                        // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo fe_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1042,                              // lineNo
    88,                                // colNo
    "thresh",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ff_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1247,                              // lineNo
    26,                                // colNo
    "t_found",                         // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo fg_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1053,                              // lineNo
    62,                                // colNo
    "slope_val",                       // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo gb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    664,                               // lineNo
    33,                                // colNo
    "timeSearchRange",                 // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo gc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1009,                              // lineNo
    58,                                // colNo
    "S_cols",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo gd_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1164,                              // lineNo
    40,                                // colNo
    "msk",                             // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ge_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1042,                              // lineNo
    105,                               // colNo
    "thresh",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo gf_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1248,                              // lineNo
    25,                                // colNo
    "t_found",                         // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo gg_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1053,                              // lineNo
    79,                                // colNo
    "slope_val",                       // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo hb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    670,                               // lineNo
    13,                                // colNo
    "timeSearchRange",                 // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo hc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1009,                              // lineNo
    70,                                // colNo
    "S_cols",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo hd_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1165,                              // lineNo
    40,                                // colNo
    "msk",                             // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo he_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1042,                              // lineNo
    59,                                // colNo
    "scores",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo hf_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1242,                              // lineNo
    61,                                // colNo
    "signalAmps",                      // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo hg_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    906,                               // lineNo
    48,                                // colNo
    "scores",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ib_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    671,                               // lineNo
    13,                                // colNo
    "timeSearchRange",                 // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ic_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1009,                              // lineNo
    82,                                // colNo
    "S_cols",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo id_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1164,                              // lineNo
    27,                                // colNo
    "msk",                             // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ie_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1042,                              // lineNo
    76,                                // colNo
    "scores",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo if_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1242,                              // lineNo
    63,                                // colNo
    "signalAmps",                      // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ig_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    906,                               // lineNo
    50,                                // colNo
    "scores",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo jb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    674,                               // lineNo
    48,                                // colNo
    "timeSearchRange",                 // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo jc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1022,                              // lineNo
    58,                                // colNo
    "S_cols",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo jd_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1080,                              // lineNo
    53,                                // colNo
    "peak_ind",                        // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo je_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1011,                              // lineNo
    67,                                // colNo
    "peak_ind",                        // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo jf_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1243,                              // lineNo
    41,                                // colNo
    "yw_max_all_freq",                 // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo jg_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    905,                               // lineNo
    74,                                // colNo
    "scores",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo kb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    674,                               // lineNo
    69,                                // colNo
    "timeSearchRange",                 // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo kc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1022,                              // lineNo
    77,                                // colNo
    "peak_ind",                        // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo kd_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1080,                              // lineNo
    42,                                // colNo
    "sideband_msk",                    // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ke_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1011,                              // lineNo
    58,                                // colNo
    "S_cols",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo kf_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1243,                              // lineNo
    43,                                // colNo
    "yw_max_all_freq",                 // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo kg_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    905,                               // lineNo
    76,                                // colNo
    "scores",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo lb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    674,                               // lineNo
    32,                                // colNo
    "timeBlinderVec",                  // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo lc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1022,                              // lineNo
    68,                                // colNo
    "S_cols",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ld_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1080,                              // lineNo
    44,                                // colNo
    "sideband_msk",                    // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo le_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1011,                              // lineNo
    70,                                // colNo
    "S_cols",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo lf_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1244,                              // lineNo
    31,                                // colNo
    "SNRdB",                           // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo lg_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    894,                               // lineNo
    57,                                // colNo
    "scores",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo mb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    674,                               // lineNo
    53,                                // colNo
    "timeBlinderVec",                  // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo mc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1022,                              // lineNo
    80,                                // colNo
    "S_cols",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo md_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1082,                              // lineNo
    51,                                // colNo
    "peak_ind",                        // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo me_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1011,                              // lineNo
    82,                                // colNo
    "S_cols",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo mf_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1244,                              // lineNo
    33,                                // colNo
    "SNRdB",                           // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo mg_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    894,                               // lineNo
    59,                                // colNo
    "scores",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo nb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    720,                               // lineNo
    40,                                // colNo
    "freq_ind_rng",                    // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo nc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1023,                              // lineNo
    60,                                // colNo
    "S_cols",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo nd_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1082,                              // lineNo
    42,                                // colNo
    "sideband_msk",                    // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ne_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1174,                              // lineNo
    40,                                // colNo
    "msk",                             // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo nf_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1245,                              // lineNo
    33,                                // colNo
    "t_found",                         // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ng_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    720,                               // lineNo
    27,                                // colNo
    "freq_mask",                       // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ob_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    720,                               // lineNo
    56,                                // colNo
    "freq_ind_rng",                    // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo oc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1023,                              // lineNo
    79,                                // colNo
    "peak_ind",                        // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo od_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1082,                              // lineNo
    54,                                // colNo
    "sideband_msk",                    // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo oe_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1174,                              // lineNo
    51,                                // colNo
    "msk",                             // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo of_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1245,                              // lineNo
    35,                                // colNo
    "t_found",                         // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo og_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    720,                               // lineNo
    43,                                // colNo
    "freq_mask",                       // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo pb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    819,                               // lineNo
    40,                                // colNo
    "S_cols",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo pc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1023,                              // lineNo
    70,                                // colNo
    "S_cols",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo pd_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1084,                              // lineNo
    51,                                // colNo
    "peak_ind",                        // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo pe_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1174,                              // lineNo
    29,                                // colNo
    "indiv_msk",                       // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo pf_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1246,                              // lineNo
    33,                                // colNo
    "t_found",                         // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo pg_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    567,                               // lineNo
    80,                                // colNo
    "obj.ps_pre.pl",                   // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo qb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    820,                               // lineNo
    66,                                // colNo
    "weightedSRowSubsMat",             // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo qc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1023,                              // lineNo
    82,                                // colNo
    "S_cols",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo qd_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1084,                              // lineNo
    42,                                // colNo
    "sideband_msk",                    // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo qe_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1177,                              // lineNo
    46,                                // colNo
    "msk",                             // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo qf_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1246,                              // lineNo
    35,                                // colNo
    "t_found",                         // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo qg_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    591,                               // lineNo
    45,                                // colNo
    "obj.ps_pre.pl",                   // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo rb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    822,                               // lineNo
    42,                                // colNo
    "indsOfBins",                      // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo rc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1025,                              // lineNo
    58,                                // colNo
    "S_cols",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo rd_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1106,                              // lineNo
    47,                                // colNo
    "bandwidth_of_peak",               // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo re_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1190,                              // lineNo
    31,                                // colNo
    "msk",                             // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo rf_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1249,                              // lineNo
    36,                                // colNo
    "freq_found",                      // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo rg_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    596,                               // lineNo
    42,                                // colNo
    "obj.stft.t",                      // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo sb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    826,                               // lineNo
    27,                                // colNo
    "binMaskMatrix",                   // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo sc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1025,                              // lineNo
    77,                                // colNo
    "peak_ind",                        // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo sd_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1148,                              // lineNo
    62,                                // colNo
    "peak_ind",                        // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo se_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1190,                              // lineNo
    33,                                // colNo
    "msk",                             // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo sf_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1250,                              // lineNo
    33,                                // colNo
    "f_bands",                         // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo sg_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    596,                               // lineNo
    57,                                // colNo
    "obj.stft.t",                      // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo tb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    844,                               // lineNo
    29,                                // colNo
    "noisePSDAtZetas",                 // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo tc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1025,                              // lineNo
    68,                                // colNo
    "S_cols",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo td_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1148,                              // lineNo
    83,                                // colNo
    "bandwidth_of_peak",               // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo te_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1194,                              // lineNo
    38,                                // colNo
    "peak_ind",                        // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo tf_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1242,                              // lineNo
    28,                                // colNo
    "cur_pl",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo tg_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    601,                               // lineNo
    44,                                // colNo
    "obj.stft.t",                      // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ub_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    845,                               // lineNo
    41,                                // colNo
    "obj.stft.f",                      // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo uc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1025,                              // lineNo
    80,                                // colNo
    "S_cols",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ud_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1149,                              // lineNo
    68,                                // colNo
    "peak_ind",                        // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ue_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1194,                              // lineNo
    40,                                // colNo
    "peak_ind",                        // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo uf_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1242,                              // lineNo
    30,                                // colNo
    "cur_pl",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ug_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    628,                               // lineNo
    49,                                // colNo
    "obj.stft.t",                      // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo vb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    845,                               // lineNo
    55,                                // colNo
    "obj.stft.f",                      // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo vc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1026,                              // lineNo
    60,                                // colNo
    "S_cols",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo vd_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1149,                              // lineNo
    89,                                // colNo
    "bandwidth_of_peak",               // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ve_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1222,                              // lineNo
    29,                                // colNo
    "obj.Wf",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo vf_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1252,                              // lineNo
    28,                                // colNo
    "cur_pl",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo wb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    858,                               // lineNo
    13,                                // colNo
    "signalPSD",                       // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo wc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1026,                              // lineNo
    79,                                // colNo
    "peak_ind",                        // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo wd_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1150,                              // lineNo
    38,                                // colNo
    "sideband_msk",                    // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo we_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1232,                              // lineNo
    57,                                // colNo
    "S_cols",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo wf_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1252,                              // lineNo
    30,                                // colNo
    "cur_pl",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo xb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    875,                               // lineNo
    13,                                // colNo
    "SNRdB",                           // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo xc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1026,                              // lineNo
    70,                                // colNo
    "S_cols",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo xd_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1151,                              // lineNo
    38,                                // colNo
    "sideband_msk",                    // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo xe_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1232,                              // lineNo
    21,                                // colNo
    "t_found",                         // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo xf_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1253,                              // lineNo
    31,                                // colNo
    "scores",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo yb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    977,                               // lineNo
    23,                                // colNo
    "peak",                            // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo yc_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1026,                              // lineNo
    82,                                // colNo
    "S_cols",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo yd_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1118,                              // lineNo
    49,                                // colNo
    "bandwidth_of_peak",               // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ye_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1232,                              // lineNo
    50,                                // colNo
    "obj.stft.t",                      // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo yf_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1254,                              // lineNo
    32,                                // colNo
    "cur_pl",                          // aName
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtDoubleCheckInfo ab_emlrtDCI{ 825,// lineNo
    35,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    4                                  // checkKind
  };

  static rtDoubleCheckInfo bb_emlrtDCI{ 825,// lineNo
    35,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo cb_emlrtDCI{ 991,// lineNo
    52,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo db_emlrtDCI{ 1009,// lineNo
    58,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo eb_emlrtDCI{ 1022,// lineNo
    68,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo fb_emlrtDCI{ 1023,// lineNo
    70,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo gb_emlrtDCI{ 1025,// lineNo
    68,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo hb_emlrtDCI{ 1026,// lineNo
    70,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo ib_emlrtDCI{ 1080,// lineNo
    44,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo jb_emlrtDCI{ 1082,// lineNo
    42,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo kb_emlrtDCI{ 1084,// lineNo
    42,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo lb_emlrtDCI{ 1150,// lineNo
    38,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo mb_emlrtDCI{ 1151,// lineNo
    38,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo nb_emlrtDCI{ 1043,// lineNo
    87,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo ob_emlrtDCI{ 1043,// lineNo
    59,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo pb_emlrtDCI{ 1042,// lineNo
    88,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo qb_emlrtDCI{ 1042,// lineNo
    59,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo rb_emlrtDCI{ 1011,// lineNo
    58,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo sb_emlrtDCI{ 1232,// lineNo
    50,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo t_emlrtDCI{ 661,// lineNo
    37,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    4                                  // checkKind
  };

  static rtDoubleCheckInfo tb_emlrtDCI{ 1054,// lineNo
    62,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo u_emlrtDCI{ 661,// lineNo
    37,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo ub_emlrtDCI{ 1053,// lineNo
    62,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo v_emlrtDCI{ 661,// lineNo
    13,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    4                                  // checkKind
  };

  static rtDoubleCheckInfo w_emlrtDCI{ 661,// lineNo
    13,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo x_emlrtDCI{ 674,// lineNo
    32,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo y_emlrtDCI{ 674,// lineNo
    53,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    1                                  // checkKind
  };

  static rtEqualityCheckInfo ab_emlrtECI{ 1,// nDims
    900,                               // lineNo
    27,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo ac_emlrtECI{ 1,// nDims
    1178,                              // lineNo
    43,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo bb_emlrtECI{ 1,// nDims
    901,                               // lineNo
    28,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo bc_emlrtECI{ 1,// nDims
    1179,                              // lineNo
    69,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo cb_emlrtECI{ 1,// nDims
    902,                               // lineNo
    27,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo cc_emlrtECI{ 1,// nDims
    1179,                              // lineNo
    43,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo db_emlrtECI{ 1,// nDims
    903,                               // lineNo
    28,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo dc_emlrtECI{ -1,// nDims
    1232,                              // lineNo
    13,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo eb_emlrtECI{ 1,// nDims
    905,                               // lineNo
    39,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo fb_emlrtECI{ 1,// nDims
    906,                               // lineNo
    34,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo g_emlrtECI{ -1,// nDims
    662,                               // lineNo
    13,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo gb_emlrtECI{ 1,// nDims
    916,                               // lineNo
    27,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo h_emlrtECI{ 1,// nDims
    53,                                // lineNo
    14,                                // colNo
    "vecfind",                         // fName
    "H:\\repos\\uavrt_detection\\vecfind.m"// pName
  };

  static rtEqualityCheckInfo hb_emlrtECI{ 1,// nDims
    915,                               // lineNo
    26,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo i_emlrtECI{ 2,// nDims
    53,                                // lineNo
    14,                                // colNo
    "vecfind",                         // fName
    "H:\\repos\\uavrt_detection\\vecfind.m"// pName
  };

  static rtEqualityCheckInfo ib_emlrtECI{ 1,// nDims
    916,                               // lineNo
    56,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo j_emlrtECI{ 1,// nDims
    57,                                // lineNo
    14,                                // colNo
    "vecfind",                         // fName
    "H:\\repos\\uavrt_detection\\vecfind.m"// pName
  };

  static rtEqualityCheckInfo jb_emlrtECI{ 1,// nDims
    941,                               // lineNo
    39,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo k_emlrtECI{ 2,// nDims
    57,                                // lineNo
    14,                                // colNo
    "vecfind",                         // fName
    "H:\\repos\\uavrt_detection\\vecfind.m"// pName
  };

  static rtEqualityCheckInfo kb_emlrtECI{ 1,// nDims
    956,                               // lineNo
    65,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo l_emlrtECI{ 1,// nDims
    683,                               // lineNo
    32,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo lb_emlrtECI{ 1,// nDims
    956,                               // lineNo
    39,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo m_emlrtECI{ 2,// nDims
    683,                               // lineNo
    32,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo mb_emlrtECI{ 1,// nDims
    962,                               // lineNo
    21,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo n_emlrtECI{ 1,// nDims
    727,                               // lineNo
    57,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo nb_emlrtECI{ 1,// nDims
    973,                               // lineNo
    23,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo o_emlrtECI{ 1,// nDims
    734,                               // lineNo
    26,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo ob_emlrtECI{ -1,// nDims
    1022,                              // lineNo
    48,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo p_emlrtECI{ 1,// nDims
    828,                               // lineNo
    40,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo pb_emlrtECI{ -1,// nDims
    1025,                              // lineNo
    48,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo q_emlrtECI{ 2,// nDims
    828,                               // lineNo
    40,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo qb_emlrtECI{ 1,// nDims
    1027,                              // lineNo
    39,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo r_emlrtECI{ 1,// nDims
    833,                               // lineNo
    44,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo rb_emlrtECI{ 1,// nDims
    1042,                              // lineNo
    52,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo s_emlrtECI{ 2,// nDims
    833,                               // lineNo
    44,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo sb_emlrtECI{ 1,// nDims
    1043,                              // lineNo
    52,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo t_emlrtECI{ 1,// nDims
    842,                               // lineNo
    40,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo tb_emlrtECI{ 1,// nDims
    1167,                              // lineNo
    34,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo u_emlrtECI{ 2,// nDims
    842,                               // lineNo
    40,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo ub_emlrtECI{ 1,// nDims
    1166,                              // lineNo
    34,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo v_emlrtECI{ 1,// nDims
    855,                               // lineNo
    37,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo vb_emlrtECI{ 1,// nDims
    1164,                              // lineNo
    34,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo w_emlrtECI{ 2,// nDims
    855,                               // lineNo
    37,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo wb_emlrtECI{ -1,// nDims
    1164,                              // lineNo
    21,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo x_emlrtECI{ 1,// nDims
    893,                               // lineNo
    33,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo xb_emlrtECI{ -1,// nDims
    1174,                              // lineNo
    17,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo y_emlrtECI{ 1,// nDims
    894,                               // lineNo
    33,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo yb_emlrtECI{ 1,// nDims
    1177,                              // lineNo
    31,                                // colNo
    "waveform/findpulse",              // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  coder::sparse Wq;
  coder::array<creal_T, 2U> obj;
  coder::array<double, 2U> S_cols;
  coder::array<double, 2U> b_excluded_freq_bands;
  coder::array<double, 2U> excluded_freq_bands;
  coder::array<double, 2U> r13;
  coder::array<double, 2U> r6;
  coder::array<double, 2U> refmat;
  coder::array<double, 2U> result;
  coder::array<double, 2U> searchmat;
  coder::array<double, 2U> signalPlusNoisePSD;
  coder::array<double, 2U> timeSearchRange;
  coder::array<double, 2U> yw_max_all_freq;
  coder::array<double, 1U> b_S_cols;
  coder::array<double, 1U> b_freq_ind_rng_data;
  coder::array<double, 1U> bandwidth_of_peak;
  coder::array<double, 1U> indsOfBinsValid;
  coder::array<double, 1U> n_diff_check_for;
  coder::array<double, 1U> peak;
  coder::array<double, 1U> scores;
  coder::array<double, 1U> timeBlinderVec;
  coder::array<int, 2U> r15;
  coder::array<int, 1U> r;
  coder::array<int, 1U> r1;
  coder::array<int, 1U> r10;
  coder::array<int, 1U> r11;
  coder::array<int, 1U> r12;
  coder::array<int, 1U> r14;
  coder::array<int, 1U> r4;
  coder::array<int, 1U> r5;
  coder::array<int, 1U> r7;
  coder::array<int, 1U> r8;
  coder::array<boolean_T, 2U> msk;
  coder::array<boolean_T, 2U> r2;
  coder::array<boolean_T, 2U> r3;
  coder::array<boolean_T, 1U> b_freq_mask;
  coder::array<boolean_T, 1U> excld_msk_vec;
  coder::array<boolean_T, 1U> freq_mask;
  coder::array<boolean_T, 1U> greater_than_next;
  coder::array<boolean_T, 1U> r9;
  coder::array<boolean_T, 1U> score_right_bndry;
  coder::array<boolean_T, 1U> slope_neg;
  coder::array<boolean_T, 1U> slope_pos;
  coder::array<boolean_T, 1U> slope_val;
  c_struct_T expl_temp;
  double freq_ind_rng_data[2];
  double t_srch_rng[2];
  double b_J;
  double b_M;
  double b_N;
  double diff_thresh;
  double n_blks;
  double naive_wind_end;
  double stft_dt;
  double t_lastknown;
  double timetol;
  double tip_temp;
  double tp_temp;
  double wind_start_data;
  int iv[2];
  int trueCount[2];
  int b_loop_ub;
  int b_p;
  int c_loop_ub;
  int d_loop_ub;
  int e_loop_ub;
  int f_loop_ub;
  int g_loop_ub;
  int h_loop_ub;
  int i;
  int i1;
  int i10;
  int i11;
  int i12;
  int i2;
  int i3;
  int i4;
  int i5;
  int i6;
  int i7;
  int i8;
  int i9;
  int i_loop_ub;
  int ii_data;
  int ii_size;
  int inds_bkwd_2_next_valley_data;
  int loop_ub;
  int maxStftTimeWind;
  int nColsOfS;
  int n_freqs;
  int nx;
  unsigned int p;
  int wind_start_size;
  boolean_T t6_con_dec;
  boolean_T y;
  if (excluded_freq_bands_in.size(0) == 0) {
    excluded_freq_bands.set_size(1, 2);
    excluded_freq_bands[0] = rtInf;
    excluded_freq_bands[1] = rtMinusInf;
  } else {
    excluded_freq_bands.set_size(excluded_freq_bands_in.size(0), 2);
    loop_ub = excluded_freq_bands_in.size(0) * 2;
    for (i = 0; i < loop_ub; i++) {
      excluded_freq_bands[i] = excluded_freq_bands_in[i];
    }
  }

  // Get relavent variables and rename for readable code.
  b_N = N;
  b_M = M;
  b_J = J;

  // Define naive search window for pulse 1
  diff_thresh = b_N + b_M;
  naive_wind_end = diff_thresh + b_J;

  // The caller of this method should have already set the
  // threshold in the posteriori pulse stats. We just rename it
  // here to simplify code.
  // thresh = obj.ps_pos.thresh;
  // The caller of this method should have already set the
  // threshold. We just rename it
  // here to simplify code.
  // NAIVE SEARCH
  if (coder::internal::e_strcmp(time_searchtype_data, time_searchtype_size)) {
    wind_start_size = 1;
    wind_start_data = 1.0;
    maxStftTimeWind = 1;

    // INFORMED SEARCH BUT NOT PRIORI FOR START TIME
  } else {
    if (coder::internal::f_strcmp(time_searchtype_data, time_searchtype_size)) {
      i = ps_pre->pl.size(1);
      if (i < 1) {
        rtDynamicBoundsError(1, 1, i, &pg_emlrtBCI);
      }
    }

    // Due to segment lengths and overlapping, there can
    // sometimes be more than the desired number of pulses in a
    // segment. One more. If for example we were looking for 3
    // pulses, but the previous segment contained 4, the
    // algorithm may have localized the latter 3 rather than the
    // first 3. Here we set up the time window search range.
    // If the last known pulse is in the first part of the time
    // range of this segement currently getting processed, we
    // search around that very narrow region. If it
    // isn't (doesn't existing in this segement, only the
    // previous) we project the last known pulse forward one
    // interpulse time, and develop search region in accordance
    // with the uncertainty of the subsequent pulse.
    // Project out search range for first pulse in this segment
    // based on previous pulses.
    i = ps_pre->pl.size(1);
    i1 = ps_pre->pl.size(1);
    if ((i1 < 1) || (i1 > i)) {
      rtDynamicBoundsError(i1, 1, i, &qg_emlrtBCI);
    }

    t_lastknown = ps_pre->pl[i1 - 1].t_0;
    tp_temp = ps_pre->t_p;

    // If the last pulse identified occured in this segement, use
    // it to downselect the first pulse search range.
    // Time steps in the STFT windows:
    i = stft->t.size(0);
    if (i < 2) {
      rtDynamicBoundsError(2, 1, i, &rg_emlrtBCI);
    }

    i = stft->t.size(0);
    if (i < 1) {
      rtDynamicBoundsError(1, 1, i, &sg_emlrtBCI);
    }

    stft_dt = stft->t[1] - stft->t[0];

    // IF LAST SEGMENT'S LAST PULSE ALSO LIVES IN THIS SEGMENT
    // BECAUSE OF OVERLAP:
    timetol = n_ws / Fs;
    i = stft->t.size(0);
    if (i < 1) {
      rtDynamicBoundsError(1, 1, i, &tg_emlrtBCI);
    }

    if (t_lastknown >= stft->t[0] - stft_dt / 2.0) {
      // The stft_dt/2 is because the stft time stamps are for
      //  the middle of each time windpw
      // wind_start = find(obj.stft.t-stft_dt/2 >=t_lastknown,1,'first');
      // wind_end   = find(obj.stft.t-stft_dt/2 <=t_lastknown+tp_temp,1,'last');
      // The logic below executes the same logic as the two
      // lines above (left commented for reference) but avoids
      // issues associated when comparing floating point
      // numbers. There can be small errors that make two
      // numbers not equal each other and this addresses that
      // problem. See the Matlab help file on eq.m under the
      // section 'Compare Floating-Point Numbers'.
      tip_temp = stft_dt / 2.0;
      peak.set_size(stft->t.size(0));
      loop_ub = stft->t.size(0);
      for (i = 0; i < loop_ub; i++) {
        peak[i] = (stft->t[i] - tip_temp) - t_lastknown;
      }

      nx = peak.size(0);
      timeBlinderVec.set_size(peak.size(0));
      if (peak.size(0) > 2147483646) {
        coder::check_forloop_overflow_error();
      }

      for (int k{0}; k < nx; k++) {
        timeBlinderVec[k] = std::abs(peak[k]);
      }

      score_right_bndry.set_size(timeBlinderVec.size(0));
      loop_ub = timeBlinderVec.size(0);
      for (i = 0; i < loop_ub; i++) {
        score_right_bndry[i] = (timeBlinderVec[i] <= timetol);
      }

      coder::c_eml_find(score_right_bndry, (int *)&ii_data, &ii_size);
      wind_start_size = ii_size;
      for (i = 0; i < ii_size; i++) {
        wind_start_data = ii_data;
      }

      stft_dt /= 2.0;
      t_lastknown += tp_temp;
      peak.set_size(stft->t.size(0));
      loop_ub = stft->t.size(0);
      for (i = 0; i < loop_ub; i++) {
        peak[i] = (stft->t[i] - stft_dt) - t_lastknown;
      }

      nx = peak.size(0);
      timeBlinderVec.set_size(peak.size(0));
      if (peak.size(0) > 2147483646) {
        coder::check_forloop_overflow_error();
      }

      for (int k{0}; k < nx; k++) {
        timeBlinderVec[k] = std::abs(peak[k]);
      }

      score_right_bndry.set_size(timeBlinderVec.size(0));
      loop_ub = timeBlinderVec.size(0);
      for (i = 0; i < loop_ub; i++) {
        score_right_bndry[i] = (timeBlinderVec[i] <= timetol);
      }

      coder::d_eml_find(score_right_bndry, (int *)&ii_data, &ii_size);
      maxStftTimeWind = ii_size;
      for (i = 0; i < ii_size; i++) {
        naive_wind_end = ii_data;
      }

      // IF LAST SEGMENT'S LAST PULSE DOESN'T LIVE IN THIS SEGMENT:
    } else {
      // Project forward one pulse in time with
      // +/-2M uncertainty in search range.
      tip_temp = ps_pre->t_ip;
      n_blks = ps_pre->t_ipu;
      t_lastknown += tip_temp;

      // +tp_temp/2;
      // These are the times of the START OF THE PULSE...not
      // the center. This is why we have stft_dt/2 terms in
      // subsequent equations.
      t_srch_rng[0] = -n_blks + t_lastknown;
      t_srch_rng[1] = n_blks + t_lastknown;
      i = stft->t.size(0);
      if (i < 1) {
        rtDynamicBoundsError(1, 1, i, &ug_emlrtBCI);
      }

      if (t_srch_rng[0] < stft->t[0] - stft_dt / 2.0) {
        // If for some reason the last known pulse is more
        // that one pulse repetition interval away from the
        // current waveform start time, use the naive search
        // range.
        wind_start_size = 1;
        wind_start_data = 1.0;
        maxStftTimeWind = 1;
      } else {
        // wind_start = find(obj.stft.t-stft_dt/2>=t_srch_rng(1),1,'first');
        // wind_end   = find(obj.stft.t-stft_dt/2<=t_srch_rng(2),1,'last');
        // The logic below executes the same logic as the two
        // lines above (left commented for reference) but
        // avoids issues associated when comparing floating
        // point numbers. There can be small errors that
        // make two numbers not equal each other and this
        // addresses that problem. See the Matlab help file
        // on eq.m under the section 'Compare Floating-Point
        // Numbers'.
        tip_temp = stft_dt / 2.0;
        peak.set_size(stft->t.size(0));
        loop_ub = stft->t.size(0);
        for (i = 0; i < loop_ub; i++) {
          peak[i] = (stft->t[i] - tip_temp) - t_srch_rng[0];
        }

        nx = peak.size(0);
        timeBlinderVec.set_size(peak.size(0));
        if (peak.size(0) > 2147483646) {
          coder::check_forloop_overflow_error();
        }

        for (int k{0}; k < nx; k++) {
          timeBlinderVec[k] = std::abs(peak[k]);
        }

        score_right_bndry.set_size(timeBlinderVec.size(0));
        loop_ub = timeBlinderVec.size(0);
        for (i = 0; i < loop_ub; i++) {
          score_right_bndry[i] = (timeBlinderVec[i] <= timetol);
        }

        coder::c_eml_find(score_right_bndry, (int *)&ii_data, &ii_size);
        wind_start_size = ii_size;
        for (i = 0; i < ii_size; i++) {
          wind_start_data = ii_data;
        }

        stft_dt /= 2.0;
        peak.set_size(stft->t.size(0));
        loop_ub = stft->t.size(0);
        for (i = 0; i < loop_ub; i++) {
          peak[i] = (stft->t[i] - stft_dt) - t_srch_rng[1];
        }

        nx = peak.size(0);
        timeBlinderVec.set_size(peak.size(0));
        if (peak.size(0) > 2147483646) {
          coder::check_forloop_overflow_error();
        }

        for (int k{0}; k < nx; k++) {
          timeBlinderVec[k] = std::abs(peak[k]);
        }

        score_right_bndry.set_size(timeBlinderVec.size(0));
        loop_ub = timeBlinderVec.size(0);
        for (i = 0; i < loop_ub; i++) {
          score_right_bndry[i] = (timeBlinderVec[i] <= timetol);
        }

        coder::d_eml_find(score_right_bndry, (int *)&ii_data, &ii_size);
        maxStftTimeWind = ii_size;
        for (i = 0; i < ii_size; i++) {
          naive_wind_end = ii_data;
        }
      }
    }
  }

  // time_search_range = [wind_start,wind_end];
  // Build a time search range matrix with one row for each pulse
  // The first column is the first window where that pulse might
  // live in the S matrix, and the second column is the last window
  // wher that pulse might live in the S matrix.
  if (!(K >= 0.0)) {
    rtNonNegativeError(K, &t_emlrtDCI);
  }

  stft_dt = K;
  if (stft_dt != static_cast<int>(std::floor(stft_dt))) {
    rtIntegerError(stft_dt, &u_emlrtDCI);
  }

  timeSearchRange.set_size(static_cast<int>(stft_dt), 2);
  if (!(K >= 0.0)) {
    rtNonNegativeError(K, &v_emlrtDCI);
  }

  stft_dt = K;
  if (stft_dt != static_cast<int>(std::floor(stft_dt))) {
    rtIntegerError(stft_dt, &w_emlrtDCI);
  }

  loop_ub = static_cast<int>(stft_dt) << 1;
  for (i = 0; i < loop_ub; i++) {
    timeSearchRange[i] = 0.0;
  }

  if (static_cast<int>(K) < 1) {
    rtDynamicBoundsError(1, 1, static_cast<int>(K), &eb_emlrtBCI);
  }

  if (maxStftTimeWind != wind_start_size) {
    fb_rtErrorWithMessageID(vb_emlrtRTEI.fName, vb_emlrtRTEI.lineNo);
  }

  result.set_size(wind_start_size, 2);
  for (i = 0; i < wind_start_size; i++) {
    result[0] = wind_start_data;
  }

  for (i = 0; i < maxStftTimeWind; i++) {
    result[result.size(0)] = naive_wind_end;
  }

  trueCount[0] = 1;
  trueCount[1] = 2;
  rtSubAssignSizeCheck(&trueCount[0], 2, result.size(), 2, &g_emlrtECI);
  timeSearchRange[0] = result[0];
  timeSearchRange[timeSearchRange.size(0)] = result[1];
  i = static_cast<int>(K + -1.0);
  for (wind_start_size = 0; wind_start_size < i; wind_start_size++) {
    if (timeSearchRange.size(0) < 1) {
      rtDynamicBoundsError(1, 1, timeSearchRange.size(0), &fb_emlrtBCI);
    }

    if ((static_cast<int>(wind_start_size + 2U) < 1) || (static_cast<int>
         (wind_start_size + 2U) > timeSearchRange.size(0))) {
      rtDynamicBoundsError(static_cast<int>(wind_start_size + 2U), 1,
                           timeSearchRange.size(0), &gb_emlrtBCI);
    }

    timeSearchRange[wind_start_size + 1] = timeSearchRange[0] + (((static_cast<
      double>(wind_start_size) + 2.0) - 1.0) * (b_N - b_M) - b_J);
    timeSearchRange[(wind_start_size + timeSearchRange.size(0)) + 1] =
      timeSearchRange[timeSearchRange.size(0)] + (((static_cast<double>
      (wind_start_size) + 2.0) - 1.0) * diff_thresh + b_J);
  }

  maxStftTimeWind = stft->S.size(1);

  // Limit the search to ranges of time that will be in the sftf
  // matrix
  inds_bkwd_2_next_valley_data = (timeSearchRange.size(0) << 1) - 1;
  nx = 0;
  for (wind_start_size = 0; wind_start_size <= inds_bkwd_2_next_valley_data;
       wind_start_size++) {
    if (timeSearchRange[wind_start_size] > maxStftTimeWind) {
      nx++;
    }
  }

  r.set_size(nx);
  nx = 0;
  for (wind_start_size = 0; wind_start_size <= inds_bkwd_2_next_valley_data;
       wind_start_size++) {
    if (timeSearchRange[wind_start_size] > maxStftTimeWind) {
      r[nx] = wind_start_size + 1;
      nx++;
    }
  }

  loop_ub = r.size(0) - 1;
  nx = timeSearchRange.size(0) << 1;
  for (i = 0; i <= loop_ub; i++) {
    if ((r[i] < 1) || (r[i] > nx)) {
      rtDynamicBoundsError(r[i], 1, nx, &hb_emlrtBCI);
    }

    timeSearchRange[r[i] - 1] = maxStftTimeWind;
  }

  inds_bkwd_2_next_valley_data = (timeSearchRange.size(0) << 1) - 1;
  nx = 0;
  for (wind_start_size = 0; wind_start_size <= inds_bkwd_2_next_valley_data;
       wind_start_size++) {
    if (timeSearchRange[wind_start_size] < 1.0) {
      nx++;
    }
  }

  r1.set_size(nx);
  nx = 0;
  for (wind_start_size = 0; wind_start_size <= inds_bkwd_2_next_valley_data;
       wind_start_size++) {
    if (timeSearchRange[wind_start_size] < 1.0) {
      r1[nx] = wind_start_size + 1;
      nx++;
    }
  }

  loop_ub = r1.size(0) - 1;
  nx = timeSearchRange.size(0) << 1;
  for (i = 0; i <= loop_ub; i++) {
    if ((r1[i] < 1) || (r1[i] > nx)) {
      rtDynamicBoundsError(r1[i], 1, nx, &ib_emlrtBCI);
    }

    timeSearchRange[r1[i] - 1] = 1.0;
  }

  timeBlinderVec.set_size(maxStftTimeWind);
  for (i = 0; i < maxStftTimeWind; i++) {
    timeBlinderVec[i] = 0.0;
  }

  i = static_cast<int>(K);
  for (wind_start_size = 0; wind_start_size < i; wind_start_size++) {
    if ((static_cast<int>(wind_start_size + 1U) < 1) || (static_cast<int>
         (wind_start_size + 1U) > timeSearchRange.size(0))) {
      rtDynamicBoundsError(static_cast<int>(wind_start_size + 1U), 1,
                           timeSearchRange.size(0), &jb_emlrtBCI);
    }

    stft_dt = timeSearchRange[wind_start_size];
    if ((static_cast<int>(wind_start_size + 1U) < 1) || (static_cast<int>
         (wind_start_size + 1U) > timeSearchRange.size(0))) {
      rtDynamicBoundsError(static_cast<int>(wind_start_size + 1U), 1,
                           timeSearchRange.size(0), &kb_emlrtBCI);
    }

    tip_temp = timeSearchRange[wind_start_size + timeSearchRange.size(0)];
    if (stft_dt > tip_temp) {
      i1 = -1;
      i2 = 0;
    } else {
      if (stft_dt != static_cast<int>(std::floor(stft_dt))) {
        rtIntegerError(stft_dt, &x_emlrtDCI);
      }

      if ((static_cast<int>(stft_dt) < 1) || (static_cast<int>(stft_dt) >
           timeBlinderVec.size(0))) {
        rtDynamicBoundsError(static_cast<int>(stft_dt), 1, timeBlinderVec.size(0),
                             &lb_emlrtBCI);
      }

      i1 = static_cast<int>(stft_dt) - 2;
      if (tip_temp != static_cast<int>(std::floor(tip_temp))) {
        rtIntegerError(tip_temp, &y_emlrtDCI);
      }

      if ((static_cast<int>(tip_temp) < 1) || (static_cast<int>(tip_temp) >
           timeBlinderVec.size(0))) {
        rtDynamicBoundsError(static_cast<int>(tip_temp), 1, timeBlinderVec.size
                             (0), &mb_emlrtBCI);
      }

      i2 = static_cast<int>(tip_temp);
    }

    loop_ub = (i2 - i1) - 1;
    for (i2 = 0; i2 < loop_ub; i2++) {
      timeBlinderVec[(i1 + i2) + 1] = 1.0;
    }
  }

  // Build the excluded frequency mask
  // False where we want to exclude
  // VECFIND creates a logical matrix based on the input operator comparing a
  // reference vector and a vector to be compared.
  //    This function can be used to do comparison operations of vectors of
  //    difference sizes. Comparing a single to a vector work natively
  //    in Matlab and create a resulting logic vector, i.e. [1 3 5]>4 outputs
  //    [0 0 1]. Many cases though require comparison of on vector to all the
  //    elements of another. i.e. [1 3 5]>[2 4] would ask which elements of
  //    [1 3 5] are greater than 2 and which are greater than 4? This function
  //    produces an output matrix whose columns are the logicial comparion of
  //    the reference vector to each element of the search vector. Logicals fpr
  //    comparison are input to this function as strings.
  //
  //    Example:
  //              outmat = vecfind([1 3 5],'>',[2 4])
  //
  //              outmat =
  //
  //              3×2 logical array
  //
  //              0   0
  //              1   0
  //              1   1
  //
  // INPUTS:
  //    refvec              n-element vector of numerics to be compared.
  //    comparison_op_string   A string of the comparison operator to be used
  //                        Valid options are '<' '<=' '>' '>=' '==' '~='
  //    searchvec           m-element vector of numerics used for comparison
  // OUTPUTS:
  //    outmat              nxm logical matrix comparing the ref and search
  //                        vectors
  //
  // Author: Michael Shafer
  // Date:   2021-05-25
  //
  // 2022-01-24 - Updated to use limited comparison operators and removed use
  //              of the eval.m function.
  //
  // Ensure column vector
  coder::repmat(Wf, static_cast<double>(excluded_freq_bands.size(0)), refmat);
  loop_ub = excluded_freq_bands.size(0);
  b_excluded_freq_bands.set_size(1, excluded_freq_bands.size(0));
  for (i = 0; i < loop_ub; i++) {
    b_excluded_freq_bands[i] = excluded_freq_bands[i];
  }

  coder::repmat(b_excluded_freq_bands, static_cast<double>(Wf.size(0)),
                searchmat);

  // outmat = eval(['refmat',logical_op_string,'searchmat']);
  if ((refmat.size(0) != searchmat.size(0)) && ((refmat.size(0) != 1) &&
       (searchmat.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(refmat.size(0), searchmat.size(0), &h_emlrtECI);
  }

  if ((refmat.size(1) != searchmat.size(1)) && ((refmat.size(1) != 1) &&
       (searchmat.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(refmat.size(1), searchmat.size(1), &i_emlrtECI);
  }

  if ((refmat.size(0) == searchmat.size(0)) && (refmat.size(1) == searchmat.size
       (1))) {
    r2.set_size(refmat.size(0), refmat.size(1));
    loop_ub = refmat.size(0) * refmat.size(1);
    for (i = 0; i < loop_ub; i++) {
      r2[i] = (refmat[i] >= searchmat[i]);
    }
  } else {
    ge(r2, refmat, searchmat);
  }

  // VECFIND creates a logical matrix based on the input operator comparing a
  // reference vector and a vector to be compared.
  //    This function can be used to do comparison operations of vectors of
  //    difference sizes. Comparing a single to a vector work natively
  //    in Matlab and create a resulting logic vector, i.e. [1 3 5]>4 outputs
  //    [0 0 1]. Many cases though require comparison of on vector to all the
  //    elements of another. i.e. [1 3 5]>[2 4] would ask which elements of
  //    [1 3 5] are greater than 2 and which are greater than 4? This function
  //    produces an output matrix whose columns are the logicial comparion of
  //    the reference vector to each element of the search vector. Logicals fpr
  //    comparison are input to this function as strings.
  //
  //    Example:
  //              outmat = vecfind([1 3 5],'>',[2 4])
  //
  //              outmat =
  //
  //              3×2 logical array
  //
  //              0   0
  //              1   0
  //              1   1
  //
  // INPUTS:
  //    refvec              n-element vector of numerics to be compared.
  //    comparison_op_string   A string of the comparison operator to be used
  //                        Valid options are '<' '<=' '>' '>=' '==' '~='
  //    searchvec           m-element vector of numerics used for comparison
  // OUTPUTS:
  //    outmat              nxm logical matrix comparing the ref and search
  //                        vectors
  //
  // Author: Michael Shafer
  // Date:   2021-05-25
  //
  // 2022-01-24 - Updated to use limited comparison operators and removed use
  //              of the eval.m function.
  //
  // Ensure column vector
  coder::repmat(Wf, static_cast<double>(excluded_freq_bands.size(0)), refmat);
  loop_ub = excluded_freq_bands.size(0);
  b_excluded_freq_bands.set_size(1, excluded_freq_bands.size(0));
  for (i = 0; i < loop_ub; i++) {
    b_excluded_freq_bands[i] = excluded_freq_bands[i + excluded_freq_bands.size
      (0)];
  }

  coder::repmat(b_excluded_freq_bands, static_cast<double>(Wf.size(0)),
                searchmat);

  // outmat = eval(['refmat',logical_op_string,'searchmat']);
  if ((refmat.size(0) != searchmat.size(0)) && ((refmat.size(0) != 1) &&
       (searchmat.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(refmat.size(0), searchmat.size(0), &j_emlrtECI);
  }

  if ((refmat.size(1) != searchmat.size(1)) && ((refmat.size(1) != 1) &&
       (searchmat.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(refmat.size(1), searchmat.size(1), &k_emlrtECI);
  }

  if ((refmat.size(0) == searchmat.size(0)) && (refmat.size(1) == searchmat.size
       (1))) {
    msk.set_size(refmat.size(0), refmat.size(1));
    loop_ub = refmat.size(0) * refmat.size(1);
    for (i = 0; i < loop_ub; i++) {
      msk[i] = (refmat[i] <= searchmat[i]);
    }
  } else {
    le(msk, refmat, searchmat);
  }

  if ((r2.size(0) != msk.size(0)) && ((r2.size(0) != 1) && (msk.size(0) != 1)))
  {
    emlrtDimSizeImpxCheckR2021b(r2.size(0), msk.size(0), &l_emlrtECI);
  }

  if ((r2.size(1) != msk.size(1)) && ((r2.size(1) != 1) && (msk.size(1) != 1)))
  {
    emlrtDimSizeImpxCheckR2021b(r2.size(1), msk.size(1), &m_emlrtECI);
  }

  if ((r2.size(0) == msk.size(0)) && (r2.size(1) == msk.size(1))) {
    r3.set_size(r2.size(0), r2.size(1));
    loop_ub = r2.size(0) * r2.size(1);
    for (i = 0; i < loop_ub; i++) {
      r3[i] = ((!r2[i]) || (!msk[i]));
    }

    coder::all(r3, excld_msk_vec);
  } else {
    n_binary_expand_op(excld_msk_vec, r2, msk);
  }

  // Build the priori frequency mask
  // Naive or informed frequency search
  if (coder::internal::f_strcmp(freq_searchtype_data, freq_searchtype_size)) {
    boolean_T guard1{ false };

    t_lastknown = ps_pre->fstart;
    tip_temp = ps_pre->fend;

    // Check to makesure the informed search range is covered by
    // the frequencies available. If the prev bw is listed
    // as NaN, this will fail and will default to the naive
    // search. Freq_mask variable is a logicial vector of the
    // same size as Wf indicating which frequencies to look at.
    // IF FREQS ARE UNAVILABLE, USE NAIVE
    tp_temp = coder::internal::b_unaryMinOrMax_anonFcn1(Wf);
    guard1 = false;
    if (t_lastknown < tp_temp) {
      guard1 = true;
    } else {
      t_lastknown = coder::internal::unaryMinOrMax_anonFcn1(Wf);
      if (tip_temp > t_lastknown) {
        guard1 = true;
      } else {
        score_right_bndry.set_size(Wf.size(0));
        loop_ub = Wf.size(0);
        for (i = 0; i < loop_ub; i++) {
          score_right_bndry[i] = (Wf[i] >= ps_pre->fstart);
        }

        coder::c_eml_find(score_right_bndry, (int *)&ii_data, &ii_size);
        wind_start_size = ii_size;
        for (i = 0; i < ii_size; i++) {
          wind_start_data = ii_data;
        }

        score_right_bndry.set_size(Wf.size(0));
        loop_ub = Wf.size(0);
        for (i = 0; i < loop_ub; i++) {
          score_right_bndry[i] = (Wf[i] <= ps_pre->fend);
        }

        coder::d_eml_find(score_right_bndry, (int *)&ii_data, &ii_size);
        maxStftTimeWind = ii_size;
        for (i = 0; i < ii_size; i++) {
          naive_wind_end = ii_data;
        }
      }
    }

    if (guard1) {
      // isnan(obj.ps_pre.fc) %Naive
      wind_start_size = 1;
      wind_start_data = 1.0;
      maxStftTimeWind = 1;
      naive_wind_end = Wf.size(0);

      // size(Sw,1);
      // IF FREQS ARE AVILABLE, USE INFORMED
    }

    if (maxStftTimeWind != wind_start_size) {
      fb_rtErrorWithMessageID(vb_emlrtRTEI.fName, vb_emlrtRTEI.lineNo);
    }

    result.set_size(wind_start_size, 2);
    for (i = 0; i < wind_start_size; i++) {
      result[0] = wind_start_data;
    }

    for (i = 0; i < maxStftTimeWind; i++) {
      result[result.size(0)] = naive_wind_end;
    }

    for (i = 0; i < wind_start_size; i++) {
      freq_ind_rng_data[0] = wind_start_data;
    }

    for (i = 0; i < maxStftTimeWind; i++) {
      freq_ind_rng_data[wind_start_size] = naive_wind_end;
    }

    t_srch_rng[0] = Wf.size(0);
    nx = static_cast<int>(t_srch_rng[0]);
    freq_mask.set_size(nx);
    for (i = 0; i < nx; i++) {
      freq_mask[i] = false;
    }

    i = result.size(0) << 1;
    if (i < 1) {
      rtDynamicBoundsError(1, 1, i, &nb_emlrtBCI);
    }

    i = result.size(0) << 1;
    if (i < 2) {
      rtDynamicBoundsError(2, 1, i, &ob_emlrtBCI);
    }

    if (static_cast<int>(result[0]) > static_cast<int>(result[1])) {
      i = -1;
      i1 = 0;
    } else {
      if ((static_cast<int>(freq_ind_rng_data[0]) < 1) || (static_cast<int>
           (freq_ind_rng_data[0]) > nx)) {
        rtDynamicBoundsError(static_cast<int>(freq_ind_rng_data[0]), 1,
                             static_cast<int>(t_srch_rng[0]), &ng_emlrtBCI);
      }

      i = static_cast<int>(freq_ind_rng_data[0]) - 2;
      if ((static_cast<int>(freq_ind_rng_data[1]) < 1) || (static_cast<int>
           (freq_ind_rng_data[1]) > nx)) {
        rtDynamicBoundsError(static_cast<int>(freq_ind_rng_data[1]), 1,
                             static_cast<int>(t_srch_rng[0]), &og_emlrtBCI);
      }

      i1 = static_cast<int>(freq_ind_rng_data[1]);
    }

    loop_ub = (i1 - i) - 1;
    for (i1 = 0; i1 < loop_ub; i1++) {
      freq_mask[(i + i1) + 1] = true;
    }
  } else {
    // Naive frequency search
    loop_ub = Wf.size(0);
    freq_mask.set_size(Wf.size(0));
    for (i = 0; i < loop_ub; i++) {
      freq_mask[i] = true;
    }
  }

  // If using informed search and excluded frequencies overlap with
  // priori frequencies, warn the user.
  if (coder::internal::f_strcmp(freq_searchtype_data, freq_searchtype_size)) {
    b_freq_mask.set_size(excld_msk_vec.size(0));
    loop_ub = excld_msk_vec.size(0);
    for (i = 0; i < loop_ub; i++) {
      b_freq_mask[i] = !excld_msk_vec[i];
    }

    if ((freq_mask.size(0) != b_freq_mask.size(0)) && ((freq_mask.size(0) != 1) &&
         (b_freq_mask.size(0) != 1))) {
      emlrtDimSizeImpxCheckR2021b(freq_mask.size(0), b_freq_mask.size(0),
        &n_emlrtECI);
    }

    if (freq_mask.size(0) == b_freq_mask.size(0)) {
      b_freq_mask.set_size(freq_mask.size(0));
      loop_ub = freq_mask.size(0);
      for (i = 0; i < loop_ub; i++) {
        b_freq_mask[i] = (freq_mask[i] && b_freq_mask[i]);
      }

      coder::internal::allOrAny_anonFcn1(b_freq_mask);
    } else {
      m_binary_expand_op(freq_mask, b_freq_mask);
    }
  } else {
    // Combine the masks
  }

  if ((freq_mask.size(0) != excld_msk_vec.size(0)) && ((freq_mask.size(0) != 1) &&
       (excld_msk_vec.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(freq_mask.size(0), excld_msk_vec.size(0),
      &o_emlrtECI);
  }

  if (freq_mask.size(0) == excld_msk_vec.size(0)) {
    loop_ub = freq_mask.size(0);
    for (i = 0; i < loop_ub; i++) {
      freq_mask[i] = (freq_mask[i] && excld_msk_vec[i]);
    }
  } else {
    c_and(freq_mask, excld_msk_vec);
  }

  // Check that we actually have something to search
  y = coder::internal::allOrAny_anonFcn1(freq_mask);
  if (!y) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }

  // Determine the number of blocks to cut the data into. Should
  // always be the number of pulses currently looking for.
  n_blks = (static_cast<double>(stft->S.size(1)) - 1.0) / diff_thresh;
  n_blks = std::floor(n_blks);
  if (n_blks == 0.0) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }

  buildtimecorrelatormatrix(b_N, b_M, b_J, K, &Wq);
  obj.set_size(W.size(1), W.size(0));
  loop_ub = W.size(0);
  for (i = 0; i < loop_ub; i++) {
    maxStftTimeWind = W.size(1);
    for (i1 = 0; i1 < maxStftTimeWind; i1++) {
      obj[i1 + obj.size(0) * i].re = W[i + W.size(0) * i1].re;
      obj[i1 + obj.size(0) * i].im = -W[i + W.size(0) * i1].im;
    }
  }

  incohsumtoeplitz(freq_mask, obj, stft->S, timeBlinderVec, &Wq, yw_max_all_freq,
                   S_cols);

  // obj.TimeCorr.Wq(obj.K));
  // Only pass a freq_msk subset of the Sw matrix to the incohsum
  // function. Run the algorithm
  //              tic
  //              [yw_max_all_freq,S_cols,S_rows] = incohsumfast(Sw(freq_mask,:),...
  //                                                          N,M,...
  //                                                          time_search_range,...
  //                                                          n_blks);
  //              time(1) = toc;
  //              tic
  //              [yw_max_all_freq,S_cols,S_rows] = incohsum(Sw(freq_mask,:),...
  //                                                          N,M,...
  //                                                          time_search_range,...
  //                                                          n_blks);
  //              time(2) = toc;
  //              time
  //              yw_max_all_freq2 = NaN(numel(Wf),n_blks);
  //              yw_max_all_freq2(freq_mask,:) = yw_max_all_freq;
  //              yw_max_all_freq = yw_max_all_freq2;
  //              S_cols2 = NaN(numel(Wf),n_blks);
  //              S_cols2(freq_mask,:) = S_cols;
  //              S_cols = S_cols2;
  // PAPER EQUATION 14
  // y_vec_w = Sw(sub2ind(size(Sw),out(:,1),out(:,2)));
  //  %PAPER EQUATION pre-29
  // gamma   = abs(y_vec_w);
  // PAPER EQUATION 29
  // z       = sum(gamma.^2);
  //             %% PEELING ALGORITHM
  //  The following algorithm is used to help tease out the central
  //  peaks of the outputs of filter and sort out those entries
  //  that are sideband. It looks through all of the scores
  //  (yw_max_all_freqs), beginning with the highest score. It
  //  looks for other scores that are correlated in time and nearby
  //  frequency and identifies them as sidebands. Once the highest
  //  peak's sidebands are identified and excluded from further
  //  consideration as a separate pulse, the algorithm moves to the
  //  next highest score, repeating the sideband identification.
  //  This continues until no more scores that exceed the decision
  //  threshold remain.
  // Number of pulses identified for each frequency. This should be
  // equal to the K pulses of the search or n_blks.
  n_freqs = yw_max_all_freq.size(0);

  // Calculate the sum of the yw values - the score/test statistic
  coder::sum(yw_max_all_freq, scores);

  // Calculate an estimate of the noise only power in each bin
  // based on the PSD
  // psdAtZetas = interp1(obj.stft.f,obj.stft.psd,Wf,'linear','extrap');
  // freqBinPowAtZetas = psdAtZetas*(Wf(2)-Wf(1));
  nColsOfS = stft->S.size(1);
  ii_size = stft->S.size(0);

  // sIndsOfBins = sub2ind([nRowsOfS nColsOfS],repmat((1:nRowsOfS)',1,nColsOfS),S_cols);
  // sIndsOfBins = sub2ind([nZetas*nRowsOfS nColsOfS],transpose(1:numel(Wf)),S_cols);
  // The few lines below finds the noisePSD, but excludes regions
  // in time and frequency around possible detection. We do
  // detections as the zeta steps, but use the S matrix for PSD
  // estimates so there is a size mismatch that necessitates the
  // code below.
  nx = Wf.size(0);
  if (nx < 1) {
    b_excluded_freq_bands.set_size(1, 0);
  } else {
    b_excluded_freq_bands.set_size(1, nx);
    loop_ub = nx - 1;
    for (i = 0; i <= loop_ub; i++) {
      b_excluded_freq_bands[i] = static_cast<double>(i) + 1.0;
    }
  }

  peak.set_size(b_excluded_freq_bands.size(1));
  loop_ub = b_excluded_freq_bands.size(1);
  for (i = 0; i < loop_ub; i++) {
    peak[i] = b_excluded_freq_bands[i];
  }

  coder::repmat(peak, K, refmat);

  // sub2ind doesn't support NaN values, so we focus here on those
  // that don't have NaN
  r2.set_size(S_cols.size(0), S_cols.size(1));
  loop_ub = S_cols.size(0) * S_cols.size(1);
  for (i = 0; i < loop_ub; i++) {
    r2[i] = std::isnan(S_cols[i]);
  }

  loop_ub = r2.size(0) * r2.size(1);
  for (i = 0; i < loop_ub; i++) {
    r2[i] = !r2[i];
  }

  trueCount[0] = (*(int (*)[2])S_cols.size())[0];
  trueCount[1] = (*(int (*)[2])S_cols.size())[1];
  iv[0] = (*(int (*)[2])r2.size())[0];
  iv[1] = (*(int (*)[2])r2.size())[1];
  coder::internal::b_indexShapeCheck(trueCount, iv);
  inds_bkwd_2_next_valley_data = r2.size(0) * r2.size(1);
  for (wind_start_size = 0; wind_start_size < inds_bkwd_2_next_valley_data;
       wind_start_size++) {
    if (r2[wind_start_size]) {
      i = S_cols.size(0) * S_cols.size(1);
      if ((wind_start_size + 1 < 1) || (wind_start_size + 1 > i)) {
        rtDynamicBoundsError(wind_start_size + 1, 1, i, &pb_emlrtBCI);
      }
    }
  }

  trueCount[0] = (*(int (*)[2])refmat.size())[0];
  trueCount[1] = (*(int (*)[2])refmat.size())[1];
  iv[0] = (*(int (*)[2])r2.size())[0];
  iv[1] = (*(int (*)[2])r2.size())[1];
  coder::internal::b_indexShapeCheck(trueCount, iv);
  inds_bkwd_2_next_valley_data = r2.size(0) * r2.size(1);
  for (wind_start_size = 0; wind_start_size < inds_bkwd_2_next_valley_data;
       wind_start_size++) {
    if (r2[wind_start_size]) {
      i = refmat.size(0) * refmat.size(1);
      if ((wind_start_size + 1 < 1) || (wind_start_size + 1 > i)) {
        rtDynamicBoundsError(wind_start_size + 1, 1, i, &qb_emlrtBCI);
      }
    }
  }

  inds_bkwd_2_next_valley_data = r2.size(0) * r2.size(1) - 1;
  nx = 0;
  for (wind_start_size = 0; wind_start_size <= inds_bkwd_2_next_valley_data;
       wind_start_size++) {
    if (r2[wind_start_size]) {
      nx++;
    }
  }

  r4.set_size(nx);
  nx = 0;
  for (wind_start_size = 0; wind_start_size <= inds_bkwd_2_next_valley_data;
       wind_start_size++) {
    if (r2[wind_start_size]) {
      r4[nx] = wind_start_size + 1;
      nx++;
    }
  }

  inds_bkwd_2_next_valley_data = r2.size(0) * r2.size(1) - 1;
  nx = 0;
  for (wind_start_size = 0; wind_start_size <= inds_bkwd_2_next_valley_data;
       wind_start_size++) {
    if (r2[wind_start_size]) {
      nx++;
    }
  }

  r5.set_size(nx);
  nx = 0;
  for (wind_start_size = 0; wind_start_size <= inds_bkwd_2_next_valley_data;
       wind_start_size++) {
    if (r2[wind_start_size]) {
      r5[nx] = wind_start_size + 1;
      nx++;
    }
  }

  t_lastknown = static_cast<double>(Wf.size(0)) / static_cast<double>(ii_size) *
    static_cast<double>(ii_size);
  maxStftTimeWind = static_cast<int>(t_lastknown);
  trueCount[0] = static_cast<int>(t_lastknown);
  trueCount[1] = nColsOfS;
  peak.set_size(r4.size(0));
  loop_ub = r4.size(0);
  for (i = 0; i < loop_ub; i++) {
    peak[i] = refmat[r4[i] - 1];
  }

  b_S_cols.set_size(r5.size(0));
  loop_ub = r5.size(0);
  for (i = 0; i < loop_ub; i++) {
    b_S_cols[i] = S_cols[r5[i] - 1];
  }

  coder::eml_sub2ind(trueCount, peak, b_S_cols, r);
  timeBlinderVec.set_size(r.size(0));
  loop_ub = r.size(0);
  for (i = 0; i < loop_ub; i++) {
    timeBlinderVec[i] = r[i];
  }

  b_freq_mask.set_size(timeBlinderVec.size(0));
  loop_ub = timeBlinderVec.size(0);
  for (i = 0; i < loop_ub; i++) {
    b_freq_mask[i] = false;
  }

  inds_bkwd_2_next_valley_data = b_freq_mask.size(0) - 1;
  nx = 0;
  for (wind_start_size = 0; wind_start_size <= inds_bkwd_2_next_valley_data;
       wind_start_size++) {
    nx++;
  }

  indsOfBinsValid.set_size(nx);
  for (wind_start_size = 0; wind_start_size <= inds_bkwd_2_next_valley_data;
       wind_start_size++) {
    if (wind_start_size + 1 > timeBlinderVec.size(0)) {
      rtDynamicBoundsError(wind_start_size + 1, 1, timeBlinderVec.size(0),
                           &rb_emlrtBCI);
    }

    indsOfBinsValid[wind_start_size] = timeBlinderVec[wind_start_size];
  }

  // binMaskMatrix will be a matrix of NaN at potential pulse
  // locations
  if (!(t_lastknown >= 0.0)) {
    rtNonNegativeError(rtNaN, &ab_emlrtDCI);
  }

  if (t_lastknown != static_cast<int>(std::floor(t_lastknown))) {
    rtIntegerError(t_lastknown, &bb_emlrtDCI);
  }

  refmat.set_size(maxStftTimeWind, nColsOfS);
  nx = static_cast<int>(t_lastknown) * nColsOfS;
  for (i = 0; i < nx; i++) {
    refmat[i] = 0.0;
  }

  r.set_size(indsOfBinsValid.size(0));
  loop_ub = indsOfBinsValid.size(0);
  for (i = 0; i < loop_ub; i++) {
    i1 = static_cast<int>(indsOfBinsValid[i]);
    if ((i1 < 1) || (i1 > nx)) {
      rtDynamicBoundsError(static_cast<int>(indsOfBinsValid[i]), 1, nx,
                           &sb_emlrtBCI);
    }

    r[i] = i1;
  }

  loop_ub = r.size(0);
  for (i = 0; i < loop_ub; i++) {
    refmat[r[i] - 1] = rtNaN;
  }

  // 0;
  // Now add some buffer around the potential pulse locations
  searchmat.set_size(refmat.size(0), refmat.size(1));
  loop_ub = refmat.size(0) * refmat.size(1);
  for (i = 0; i < loop_ub; i++) {
    searchmat[i] = refmat[i];
  }

  coder::circshift(searchmat);
  if ((refmat.size(0) != searchmat.size(0)) && ((refmat.size(0) != 1) &&
       (searchmat.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(refmat.size(0), searchmat.size(0), &p_emlrtECI);
  }

  if ((refmat.size(1) != searchmat.size(1)) && ((refmat.size(1) != 1) &&
       (searchmat.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(refmat.size(1), searchmat.size(1), &q_emlrtECI);
  }

  if ((refmat.size(0) == searchmat.size(0)) && (refmat.size(1) == searchmat.size
       (1))) {
    loop_ub = refmat.size(0) * refmat.size(1);
    searchmat.set_size(refmat.size(0), refmat.size(1));
    for (i = 0; i < loop_ub; i++) {
      searchmat[i] = refmat[i] + searchmat[i];
    }
  } else {
    b_plus(searchmat, refmat);
  }

  r6.set_size(refmat.size(0), refmat.size(1));
  loop_ub = refmat.size(0) * refmat.size(1);
  for (i = 0; i < loop_ub; i++) {
    r6[i] = refmat[i];
  }

  coder::b_circshift(r6);
  if ((searchmat.size(0) != r6.size(0)) && ((searchmat.size(0) != 1) && (r6.size
        (0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(searchmat.size(0), r6.size(0), &p_emlrtECI);
  }

  if ((searchmat.size(1) != r6.size(1)) && ((searchmat.size(1) != 1) && (r6.size
        (1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(searchmat.size(1), r6.size(1), &q_emlrtECI);
  }

  if ((searchmat.size(0) == r6.size(0)) && (searchmat.size(1) == r6.size(1))) {
    loop_ub = searchmat.size(0) * searchmat.size(1);
    for (i = 0; i < loop_ub; i++) {
      searchmat[i] = searchmat[i] + r6[i];
    }
  } else {
    plus(searchmat, r6);
  }

  r6.set_size(refmat.size(0), refmat.size(1));
  loop_ub = refmat.size(0) * refmat.size(1);
  for (i = 0; i < loop_ub; i++) {
    r6[i] = refmat[i];
  }

  coder::c_circshift(r6);
  if ((searchmat.size(0) != r6.size(0)) && ((searchmat.size(0) != 1) && (r6.size
        (0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(searchmat.size(0), r6.size(0), &p_emlrtECI);
  }

  if ((searchmat.size(1) != r6.size(1)) && ((searchmat.size(1) != 1) && (r6.size
        (1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(searchmat.size(1), r6.size(1), &q_emlrtECI);
  }

  if ((searchmat.size(0) == r6.size(0)) && (searchmat.size(1) == r6.size(1))) {
    loop_ub = searchmat.size(0) * searchmat.size(1);
    for (i = 0; i < loop_ub; i++) {
      searchmat[i] = searchmat[i] + r6[i];
    }
  } else {
    plus(searchmat, r6);
  }

  coder::d_circshift(refmat);
  if ((searchmat.size(0) != refmat.size(0)) && ((searchmat.size(0) != 1) &&
       (refmat.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(searchmat.size(0), refmat.size(0), &p_emlrtECI);
  }

  if ((searchmat.size(1) != refmat.size(1)) && ((searchmat.size(1) != 1) &&
       (refmat.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(searchmat.size(1), refmat.size(1), &q_emlrtECI);
  }

  if ((searchmat.size(0) == refmat.size(0)) && (searchmat.size(1) == refmat.size
       (1))) {
    loop_ub = searchmat.size(0) * searchmat.size(1);
    for (i = 0; i < loop_ub; i++) {
      searchmat[i] = searchmat[i] + refmat[i];
    }
  } else {
    plus(searchmat, refmat);
  }

  r6.set_size(searchmat.size(0), searchmat.size(1));
  loop_ub = searchmat.size(0) * searchmat.size(1);
  for (i = 0; i < loop_ub; i++) {
    r6[i] = searchmat[i];
  }

  coder::e_circshift(r6);
  if ((searchmat.size(0) != r6.size(0)) && ((searchmat.size(0) != 1) && (r6.size
        (0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(searchmat.size(0), r6.size(0), &r_emlrtECI);
  }

  if ((searchmat.size(1) != r6.size(1)) && ((searchmat.size(1) != 1) && (r6.size
        (1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(searchmat.size(1), r6.size(1), &s_emlrtECI);
  }

  if ((searchmat.size(0) == r6.size(0)) && (searchmat.size(1) == r6.size(1))) {
    loop_ub = searchmat.size(0) * searchmat.size(1);
    r6.set_size(searchmat.size(0), searchmat.size(1));
    for (i = 0; i < loop_ub; i++) {
      r6[i] = searchmat[i] + r6[i];
    }
  } else {
    b_plus(r6, searchmat);
  }

  coder::f_circshift(searchmat);
  if ((r6.size(0) != searchmat.size(0)) && ((r6.size(0) != 1) && (searchmat.size
        (0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(r6.size(0), searchmat.size(0), &r_emlrtECI);
  }

  if ((r6.size(1) != searchmat.size(1)) && ((r6.size(1) != 1) && (searchmat.size
        (1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(r6.size(1), searchmat.size(1), &s_emlrtECI);
  }

  if ((r6.size(0) == searchmat.size(0)) && (r6.size(1) == searchmat.size(1))) {
    signalPlusNoisePSD.set_size(r6.size(0), r6.size(1));
    loop_ub = r6.size(0) * r6.size(1);
    for (i = 0; i < loop_ub; i++) {
      signalPlusNoisePSD[i] = r6[i] + searchmat[i];
    }

    t_srch_rng[0] = ii_size;
    t_srch_rng[1] = nColsOfS;
    coder::imresize(signalPlusNoisePSD, t_srch_rng, refmat);
  } else {
    binary_expand_op(refmat, r6, searchmat, ii_size, nColsOfS);
  }

  // figure;spy(freqtimeShiftedBinMaskMatrix_scaled)
  t_lastknown = 1.0 / Fs;

  // noisePSD = dt^2/T*abs(mean(obj.stft.S+freqtimeShiftedBinMaskMatrixScaled,2,'omitnan')).^2;%Add since it is 0 where we expect noise and NaN where there might be a pulse
  i = stft->S.size(0);
  if ((i != refmat.size(0)) && ((i != 1) && (refmat.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(i, refmat.size(0), &t_emlrtECI);
  }

  i = stft->S.size(1);
  if ((i != refmat.size(1)) && ((i != 1) && (refmat.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(i, refmat.size(1), &u_emlrtECI);
  }

  tp_temp = t_lastknown * t_lastknown / (n_w / Fs);
  if ((stft->S.size(0) == refmat.size(0)) && (stft->S.size(1) == refmat.size(1)))
  {
    obj.set_size(stft->S.size(0), stft->S.size(1));
    loop_ub = stft->S.size(0) * stft->S.size(1);
    for (i = 0; i < loop_ub; i++) {
      obj[i].re = stft->S[i].re + refmat[i];
      obj[i].im = stft->S[i].im;
    }

    nx = obj.size(0) * obj.size(1);
    refmat.set_size(obj.size(0), obj.size(1));
    if (nx > 2147483646) {
      coder::check_forloop_overflow_error();
    }

    for (int k{0}; k < nx; k++) {
      refmat[k] = rt_hypotd_snf(obj[k].re, obj[k].im);
    }
  } else {
    binary_expand_op(refmat, this);
  }

  r6.set_size(refmat.size(0), refmat.size(1));
  loop_ub = refmat.size(0) * refmat.size(1);
  for (i = 0; i < loop_ub; i++) {
    t_lastknown = refmat[i];
    r6[i] = t_lastknown * t_lastknown;
  }

  coder::mean(r6, timeBlinderVec);

  // Add since it is 0 where we expect noise and NaN where there might be a pulse
  peak.set_size(timeBlinderVec.size(0));
  loop_ub = timeBlinderVec.size(0);
  for (i = 0; i < loop_ub; i++) {
    peak[i] = tp_temp * timeBlinderVec[i];
  }

  coder::interp1(stft->f, peak, Wf, timeBlinderVec);
  inds_bkwd_2_next_valley_data = timeBlinderVec.size(0);
  for (wind_start_size = 0; wind_start_size < inds_bkwd_2_next_valley_data;
       wind_start_size++) {
    if (timeBlinderVec[wind_start_size] < 0.0) {
      if (wind_start_size + 1 > timeBlinderVec.size(0)) {
        rtDynamicBoundsError(wind_start_size + 1, 1, timeBlinderVec.size(0),
                             &tb_emlrtBCI);
      }

      timeBlinderVec[wind_start_size] = 0.0;
    }
  }

  i = stft->f.size(0);
  if (i < 2) {
    rtDynamicBoundsError(2, 1, i, &ub_emlrtBCI);
  }

  i = stft->f.size(0);
  if (i < 1) {
    rtDynamicBoundsError(1, 1, i, &vb_emlrtBCI);
  }

  t_lastknown = stft->f[1] - stft->f[0];

  // Not the delta f of the Wf vector, because the frequency bins are the same width, just with half bin steps %
  // noisePowers = noisePSDAtZetas*fBinWidthZetas;
  // Calculate the power at each of the S locations that were
  // selected by the incohsum function. Scores are the mag squared
  // S values. Mult by dt^2/T to get psd, then mult by the width of
  // the frequency bin to get power. We have to do this because the
  // psd in the stft object uses dt^2/T factor for the psd calc.
  signalPlusNoisePSD.set_size(yw_max_all_freq.size(0), yw_max_all_freq.size(1));
  loop_ub = yw_max_all_freq.size(0) * yw_max_all_freq.size(1);
  for (i = 0; i < loop_ub; i++) {
    signalPlusNoisePSD[i] = tp_temp * yw_max_all_freq[i];
  }

  // scores;
  // signalPlusNoisePSDPulseGroup   = dt^2/T*scores;%scores;
  coder::repmat(timeBlinderVec, static_cast<double>(yw_max_all_freq.size(1)), r6);
  if ((signalPlusNoisePSD.size(0) != r6.size(0)) && ((signalPlusNoisePSD.size(0)
        != 1) && (r6.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(signalPlusNoisePSD.size(0), r6.size(0),
      &v_emlrtECI);
  }

  if ((signalPlusNoisePSD.size(1) != r6.size(1)) && ((signalPlusNoisePSD.size(1)
        != 1) && (r6.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(signalPlusNoisePSD.size(1), r6.size(1),
      &w_emlrtECI);
  }

  if ((signalPlusNoisePSD.size(0) == r6.size(0)) && (signalPlusNoisePSD.size(1) ==
       r6.size(1))) {
    loop_ub = signalPlusNoisePSD.size(0) * signalPlusNoisePSD.size(1);
    for (i = 0; i < loop_ub; i++) {
      signalPlusNoisePSD[i] = signalPlusNoisePSD[i] - r6[i];
    }
  } else {
    minus(signalPlusNoisePSD, r6);
  }

  // signalPSDPulseGroup   = signalPlusNoisePSDPulseGroup-noisePSDAtZetas;
  inds_bkwd_2_next_valley_data = signalPlusNoisePSD.size(0) *
    signalPlusNoisePSD.size(1) - 1;
  nx = 0;
  for (wind_start_size = 0; wind_start_size <= inds_bkwd_2_next_valley_data;
       wind_start_size++) {
    if (signalPlusNoisePSD[wind_start_size] < 0.0) {
      nx++;
    }
  }

  r7.set_size(nx);
  nx = 0;
  for (wind_start_size = 0; wind_start_size <= inds_bkwd_2_next_valley_data;
       wind_start_size++) {
    if (signalPlusNoisePSD[wind_start_size] < 0.0) {
      r7[nx] = wind_start_size + 1;
      nx++;
    }
  }

  loop_ub = r7.size(0) - 1;
  nx = signalPlusNoisePSD.size(0) * signalPlusNoisePSD.size(1);
  for (i = 0; i <= loop_ub; i++) {
    if ((r7[i] < 1) || (r7[i] > nx)) {
      rtDynamicBoundsError(r7[i], 1, nx, &wb_emlrtBCI);
    }

    signalPlusNoisePSD[r7[i] - 1] = 0.0;
  }

  // Can't have negative values
  // signalPSDPulseGroup(signalPSD<0)   = 0; %Can't have negative values
  searchmat.set_size(signalPlusNoisePSD.size(0), signalPlusNoisePSD.size(1));
  loop_ub = signalPlusNoisePSD.size(0) * signalPlusNoisePSD.size(1);
  for (i = 0; i < loop_ub; i++) {
    searchmat[i] = signalPlusNoisePSD[i] * t_lastknown;
  }

  coder::b_sqrt(searchmat);

  // signalPlusNoisePowers = signalPlusNoisePSD*fBinWidthZetas;
  // signalPowers          = signalPlusNoisePowers-noisePowers;
  // SNRdB = 10*log10(powers./freqBinPowAtZetas);
  // Signal power ratio to  noise power in its frequency bin for all pulses in group
  // SNRdB = 10*log10(powers./sum(freqBinPowAtZetas));          %Signal power ratio to all noise power in bandwidth
  // SNRdB = 10*log10(powers./obj.K*1./sum(freqBinPowAtZetas)); %Average the power across all pulses
  // SNRdB = 10*log10(signalPowers./obj.K*1./noisePowers); %Average the power across all pulses
  coder::repmat(timeBlinderVec, static_cast<double>(yw_max_all_freq.size(1)),
                refmat);
  coder::internal::assertCompatibleDims(signalPlusNoisePSD, refmat);
  if ((signalPlusNoisePSD.size(0) == refmat.size(0)) && (signalPlusNoisePSD.size
       (1) == refmat.size(1))) {
    loop_ub = signalPlusNoisePSD.size(0) * signalPlusNoisePSD.size(1);
    for (i = 0; i < loop_ub; i++) {
      signalPlusNoisePSD[i] = signalPlusNoisePSD[i] / refmat[i];
    }
  } else {
    rdivide(signalPlusNoisePSD, refmat);
  }

  coder::b_log10(signalPlusNoisePSD);
  loop_ub = signalPlusNoisePSD.size(0) * signalPlusNoisePSD.size(1);
  for (i = 0; i < loop_ub; i++) {
    signalPlusNoisePSD[i] = 10.0 * signalPlusNoisePSD[i];
  }

  // SNRdBPulseGroup = 10*log10(signalPSDPulseGroup./noisePSDAtZetas);
  inds_bkwd_2_next_valley_data = signalPlusNoisePSD.size(0) *
    signalPlusNoisePSD.size(1) - 1;
  nx = 0;
  for (wind_start_size = 0; wind_start_size <= inds_bkwd_2_next_valley_data;
       wind_start_size++) {
    if (signalPlusNoisePSD[wind_start_size] == rtInf) {
      nx++;
    }
  }

  r8.set_size(nx);
  nx = 0;
  for (wind_start_size = 0; wind_start_size <= inds_bkwd_2_next_valley_data;
       wind_start_size++) {
    if (signalPlusNoisePSD[wind_start_size] == rtInf) {
      r8[nx] = wind_start_size + 1;
      nx++;
    }
  }

  loop_ub = r8.size(0) - 1;
  nx = signalPlusNoisePSD.size(0) * signalPlusNoisePSD.size(1);
  for (i = 0; i <= loop_ub; i++) {
    if ((r8[i] < 1) || (r8[i] > nx)) {
      rtDynamicBoundsError(r8[i], 1, nx, &xb_emlrtBCI);
    }

    signalPlusNoisePSD[r8[i] - 1] = rtNaN;
  }

  // SNRdBPulseGroup(SNRdBPulseGroup==Inf) = NaN;
  // Calculate the first and second frequency derivatives of the
  // scores. We'll use these for slope and curvature assessments.
  // These aren't truely the frequency derivatives because we don't
  // divide by deltaf. The are really dsdfrequency bin. We don't
  // really care about the magnitude though, just the sign. Each
  // dsdf value is the average of the slope ahead and behind the
  // point.
  // dsdf     = [0; mean([diff(scores(1:end-1)),diff(scores(2:end))],2);0];%See notebook entry 2021-02-10
  // d2sdf2   = [0; mean([diff(dsdf(1:end-1)),diff(dsdf(2:end))],2);0];%See notebook entry 2021-02-10
  // This block of code determines where there are peaks (negative
  // slopes to the left and right) and where there are valleys
  // (positive slopes to left and right)
  // greater_than_next = scores(2:end-1)>scores(3:end);
  // greater_than_prev = scores(2:end-1)>scores(1:end-2);
  if (scores.size(0) < 1) {
    loop_ub = 0;
  } else {
    loop_ub = scores.size(0);
  }

  trueCount[0] = 1;
  trueCount[1] = loop_ub;
  coder::internal::indexShapeCheck(scores.size(0), trueCount);
  if (scores.size(0) < 2) {
    i = 0;
    i1 = 0;
  } else {
    i = 1;
    i1 = scores.size(0);
  }

  trueCount[0] = 1;
  nx = i1 - i;
  trueCount[1] = nx;
  coder::internal::indexShapeCheck(scores.size(0), trueCount);
  timeBlinderVec.set_size(nx + 1);
  for (i1 = 0; i1 < nx; i1++) {
    timeBlinderVec[i1] = scores[i + i1];
  }

  timeBlinderVec[nx] = 0.0;
  if ((loop_ub != timeBlinderVec.size(0)) && ((loop_ub != 1) &&
       (timeBlinderVec.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(loop_ub, timeBlinderVec.size(0), &x_emlrtECI);
  }

  if (loop_ub == timeBlinderVec.size(0)) {
    greater_than_next.set_size(loop_ub);
    for (i = 0; i < loop_ub; i++) {
      greater_than_next[i] = (scores[i] > timeBlinderVec[i]);
    }
  } else {
    l_binary_expand_op(greater_than_next, scores, loop_ub - 1, timeBlinderVec);
  }

  if (scores.size(0) < 1) {
    loop_ub = 0;
  } else {
    loop_ub = scores.size(0);
  }

  trueCount[0] = 1;
  trueCount[1] = loop_ub;
  coder::internal::indexShapeCheck(scores.size(0), trueCount);
  if (scores.size(0) - 1 < 1) {
    maxStftTimeWind = 0;
  } else {
    if (scores.size(0) < 1) {
      rtDynamicBoundsError(1, 1, scores.size(0), &lg_emlrtBCI);
    }

    if ((scores.size(0) - 1 < 1) || (scores.size(0) - 1 > scores.size(0))) {
      rtDynamicBoundsError(scores.size(0) - 1, 1, scores.size(0), &mg_emlrtBCI);
    }

    maxStftTimeWind = scores.size(0) - 1;
  }

  trueCount[0] = 1;
  trueCount[1] = maxStftTimeWind;
  coder::internal::indexShapeCheck(scores.size(0), trueCount);
  timeBlinderVec.set_size(maxStftTimeWind + 1);
  timeBlinderVec[0] = 0.0;
  for (i = 0; i < maxStftTimeWind; i++) {
    timeBlinderVec[i + 1] = scores[i];
  }

  if ((loop_ub != timeBlinderVec.size(0)) && ((loop_ub != 1) &&
       (timeBlinderVec.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(loop_ub, timeBlinderVec.size(0), &y_emlrtECI);
  }

  if (loop_ub == timeBlinderVec.size(0)) {
    excld_msk_vec.set_size(loop_ub);
    for (i = 0; i < loop_ub; i++) {
      excld_msk_vec[i] = (scores[i] > timeBlinderVec[i]);
    }
  } else {
    l_binary_expand_op(excld_msk_vec, scores, loop_ub - 1, timeBlinderVec);
  }

  // slope_pos = [false;~greater_than_next&greater_than_prev;false];
  // slope_neg = [false; greater_than_next&~greater_than_prev;false];
  // slope_val = [false;~greater_than_next&~greater_than_prev;false];
  // slope_peak = [false;greater_than_next&greater_than_prev;false];
  slope_val.set_size(greater_than_next.size(0));
  loop_ub = greater_than_next.size(0);
  for (i = 0; i < loop_ub; i++) {
    slope_val[i] = !greater_than_next[i];
  }

  if ((slope_val.size(0) != excld_msk_vec.size(0)) && ((slope_val.size(0) != 1) &&
       (excld_msk_vec.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(slope_val.size(0), excld_msk_vec.size(0),
      &ab_emlrtECI);
  }

  if (slope_val.size(0) == excld_msk_vec.size(0)) {
    slope_pos.set_size(slope_val.size(0));
    loop_ub = slope_val.size(0);
    for (i = 0; i < loop_ub; i++) {
      slope_pos[i] = (slope_val[i] && excld_msk_vec[i]);
    }
  } else {
    d_and(slope_pos, slope_val, excld_msk_vec);
  }

  b_freq_mask.set_size(excld_msk_vec.size(0));
  loop_ub = excld_msk_vec.size(0);
  for (i = 0; i < loop_ub; i++) {
    b_freq_mask[i] = !excld_msk_vec[i];
  }

  if ((greater_than_next.size(0) != b_freq_mask.size(0)) &&
      ((greater_than_next.size(0) != 1) && (b_freq_mask.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(greater_than_next.size(0), b_freq_mask.size(0),
      &bb_emlrtECI);
  }

  if (greater_than_next.size(0) == b_freq_mask.size(0)) {
    slope_neg.set_size(greater_than_next.size(0));
    loop_ub = greater_than_next.size(0);
    for (i = 0; i < loop_ub; i++) {
      slope_neg[i] = (greater_than_next[i] && b_freq_mask[i]);
    }
  } else {
    d_and(slope_neg, greater_than_next, b_freq_mask);
  }

  if ((slope_val.size(0) != b_freq_mask.size(0)) && ((slope_val.size(0) != 1) &&
       (b_freq_mask.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(slope_val.size(0), b_freq_mask.size(0),
      &cb_emlrtECI);
  }

  if (slope_val.size(0) == b_freq_mask.size(0)) {
    loop_ub = slope_val.size(0);
    for (i = 0; i < loop_ub; i++) {
      slope_val[i] = (slope_val[i] && b_freq_mask[i]);
    }
  } else {
    c_and(slope_val, b_freq_mask);
  }

  if ((greater_than_next.size(0) != excld_msk_vec.size(0)) &&
      ((greater_than_next.size(0) != 1) && (excld_msk_vec.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(greater_than_next.size(0), excld_msk_vec.size(0),
      &db_emlrtECI);
  }

  if (greater_than_next.size(0) == excld_msk_vec.size(0)) {
    loop_ub = greater_than_next.size(0);
    for (i = 0; i < loop_ub; i++) {
      greater_than_next[i] = (greater_than_next[i] && excld_msk_vec[i]);
    }
  } else {
    c_and(greater_than_next, excld_msk_vec);
  }

  if (scores.size(0) < 2) {
    i = 0;
    i1 = 0;
  } else {
    i = 1;
    i1 = scores.size(0);
  }

  trueCount[0] = 1;
  nx = i1 - i;
  trueCount[1] = nx;
  coder::internal::indexShapeCheck(scores.size(0), trueCount);
  if (scores.size(0) - 1 < 1) {
    loop_ub = 0;
  } else {
    if (scores.size(0) < 1) {
      rtDynamicBoundsError(1, 1, scores.size(0), &jg_emlrtBCI);
    }

    if ((scores.size(0) - 1 < 1) || (scores.size(0) - 1 > scores.size(0))) {
      rtDynamicBoundsError(scores.size(0) - 1, 1, scores.size(0), &kg_emlrtBCI);
    }

    loop_ub = scores.size(0) - 1;
  }

  trueCount[0] = 1;
  trueCount[1] = loop_ub;
  coder::internal::indexShapeCheck(scores.size(0), trueCount);
  b_freq_mask.set_size(nx);
  for (i1 = 0; i1 < nx; i1++) {
    b_freq_mask[i1] = std::isnan(scores[i + i1]);
  }

  maxStftTimeWind = b_freq_mask.size(0);
  for (i = 0; i < maxStftTimeWind; i++) {
    b_freq_mask[i] = !b_freq_mask[i];
  }

  r9.set_size(loop_ub);
  for (i = 0; i < loop_ub; i++) {
    r9[i] = std::isnan(scores[i]);
  }

  if ((b_freq_mask.size(0) != r9.size(0)) && ((b_freq_mask.size(0) != 1) &&
       (r9.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(b_freq_mask.size(0), r9.size(0), &eb_emlrtECI);
  }

  if (b_freq_mask.size(0) == r9.size(0)) {
    excld_msk_vec.set_size(b_freq_mask.size(0) + 1);
    excld_msk_vec[0] = true;
    loop_ub = b_freq_mask.size(0);
    for (i = 0; i < loop_ub; i++) {
      excld_msk_vec[i + 1] = (b_freq_mask[i] && r9[i]);
    }
  } else {
    k_binary_expand_op(excld_msk_vec, b_freq_mask, r9);
  }

  if (scores.size(0) - 1 < 1) {
    loop_ub = 0;
  } else {
    if (scores.size(0) < 1) {
      rtDynamicBoundsError(1, 1, scores.size(0), &hg_emlrtBCI);
    }

    if ((scores.size(0) - 1 < 1) || (scores.size(0) - 1 > scores.size(0))) {
      rtDynamicBoundsError(scores.size(0) - 1, 1, scores.size(0), &ig_emlrtBCI);
    }

    loop_ub = scores.size(0) - 1;
  }

  trueCount[0] = 1;
  trueCount[1] = loop_ub;
  coder::internal::indexShapeCheck(scores.size(0), trueCount);
  if (scores.size(0) < 2) {
    i = 0;
    i1 = 0;
  } else {
    i = 1;
    i1 = scores.size(0);
  }

  trueCount[0] = 1;
  nx = i1 - i;
  trueCount[1] = nx;
  coder::internal::indexShapeCheck(scores.size(0), trueCount);
  b_freq_mask.set_size(loop_ub);
  for (i1 = 0; i1 < loop_ub; i1++) {
    b_freq_mask[i1] = std::isnan(scores[i1]);
  }

  loop_ub = b_freq_mask.size(0);
  for (i1 = 0; i1 < loop_ub; i1++) {
    b_freq_mask[i1] = !b_freq_mask[i1];
  }

  r9.set_size(nx);
  for (i1 = 0; i1 < nx; i1++) {
    r9[i1] = std::isnan(scores[i + i1]);
  }

  if ((b_freq_mask.size(0) != r9.size(0)) && ((b_freq_mask.size(0) != 1) &&
       (r9.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(b_freq_mask.size(0), r9.size(0), &fb_emlrtECI);
  }

  if (b_freq_mask.size(0) == r9.size(0)) {
    score_right_bndry.set_size(b_freq_mask.size(0) + 1);
    loop_ub = b_freq_mask.size(0);
    for (i = 0; i < loop_ub; i++) {
      score_right_bndry[i] = (b_freq_mask[i] && r9[i]);
    }

    score_right_bndry[b_freq_mask.size(0)] = true;
  } else {
    j_binary_expand_op(score_right_bndry, b_freq_mask, r9);
  }

  // [score_left_bndry&slope_neg,score_right_bndry&slope_pos,scores]
  // This deals with the frequency masking and some scores will be
  // NaN because they were excluded from consideration in the
  // incohsum processing. If the score is a left boundary
  // (frequencies lower were excluded) and the slope is negative,
  // this would be considered a peak. Visa-versa for right
  // boundaries.
  if ((excld_msk_vec.size(0) != slope_neg.size(0)) && ((excld_msk_vec.size(0) !=
        1) && (slope_neg.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(excld_msk_vec.size(0), slope_neg.size(0),
      &gb_emlrtECI);
  }

  if (excld_msk_vec.size(0) == slope_neg.size(0)) {
    loop_ub = excld_msk_vec.size(0);
    for (i = 0; i < loop_ub; i++) {
      excld_msk_vec[i] = (excld_msk_vec[i] && slope_neg[i]);
    }
  } else {
    c_and(excld_msk_vec, slope_neg);
  }

  if ((greater_than_next.size(0) != excld_msk_vec.size(0)) &&
      ((greater_than_next.size(0) != 1) && (excld_msk_vec.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(greater_than_next.size(0), excld_msk_vec.size(0),
      &hb_emlrtECI);
  }

  if ((score_right_bndry.size(0) != slope_pos.size(0)) &&
      ((score_right_bndry.size(0) != 1) && (slope_pos.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(score_right_bndry.size(0), slope_pos.size(0),
      &ib_emlrtECI);
  }

  if (greater_than_next.size(0) == excld_msk_vec.size(0)) {
    loop_ub = greater_than_next.size(0);
    for (i = 0; i < loop_ub; i++) {
      greater_than_next[i] = (greater_than_next[i] || excld_msk_vec[i]);
    }
  } else {
    b_or(greater_than_next, excld_msk_vec);
  }

  if (score_right_bndry.size(0) == slope_pos.size(0)) {
    loop_ub = score_right_bndry.size(0);
    for (i = 0; i < loop_ub; i++) {
      score_right_bndry[i] = (score_right_bndry[i] && slope_pos[i]);
    }
  } else {
    c_and(score_right_bndry, slope_pos);
  }

  if ((greater_than_next.size(0) != score_right_bndry.size(0)) &&
      ((greater_than_next.size(0) != 1) && (score_right_bndry.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(greater_than_next.size(0),
      score_right_bndry.size(0), &hb_emlrtECI);
  }

  if (greater_than_next.size(0) == score_right_bndry.size(0)) {
    loop_ub = greater_than_next.size(0);
    for (i = 0; i < loop_ub; i++) {
      greater_than_next[i] = (greater_than_next[i] || score_right_bndry[i]);
    }
  } else {
    b_or(greater_than_next, score_right_bndry);
  }

  // How many time windows difference do we considered the found
  // pulse to be the same as one found at a different frequency?
  // We'll say that if they are within two pulse time width of
  // each other they are the same pulse.
  diff_thresh = 2.0 * n_p / n_ws;
  p = 1U;

  // Initilize a peak counter variable
  // Initially these are the same.
  // The peak and peak_ind variables are a vector of scores and the
  // frequency index of the identified peaks of the pulses. There
  // could only ever be n_freqs peaks, so we preallocate the
  // vectors to be that long, although there will typically be far
  // fever of them - ideally the number of tags in the signal.
  peak.set_size(yw_max_all_freq.size(0));
  loop_ub = yw_max_all_freq.size(0);
  for (i = 0; i < loop_ub; i++) {
    peak[i] = 0.0;
  }

  peak_ind.set_size(yw_max_all_freq.size(0));
  loop_ub = yw_max_all_freq.size(0);
  for (i = 0; i < loop_ub; i++) {
    peak_ind[i] = 0.0;
  }

  bandwidth_of_peak.set_size(yw_max_all_freq.size(0));
  loop_ub = yw_max_all_freq.size(0);
  for (i = 0; i < loop_ub; i++) {
    bandwidth_of_peak[i] = 0.0;
  }

  msk.set_size(yw_max_all_freq.size(0), yw_max_all_freq.size(0));
  loop_ub = yw_max_all_freq.size(0) * yw_max_all_freq.size(0);
  for (i = 0; i < loop_ub; i++) {
    msk[i] = false;
  }

  indiv_msk.set_size(yw_max_all_freq.size(0), yw_max_all_freq.size(0));
  loop_ub = yw_max_all_freq.size(0) * yw_max_all_freq.size(0);
  for (i = 0; i < loop_ub; i++) {
    indiv_msk[i] = false;
  }

  // peak_masked_curr_scores is a vector of scores where only the
  // peaks have scores. All others (valleys, +slope, -slope) are
  // set to zero. As we identify peaks, they will also be set to
  // zero so that we can work our way through these peaks.
  if ((scores.size(0) != greater_than_next.size(0)) && ((scores.size(0) != 1) &&
       (greater_than_next.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(scores.size(0), greater_than_next.size(0),
      &jb_emlrtECI);
  }

  if (scores.size(0) == greater_than_next.size(0)) {
    timeBlinderVec.set_size(scores.size(0));
    loop_ub = scores.size(0);
    for (i = 0; i < loop_ub; i++) {
      timeBlinderVec[i] = scores[i] * static_cast<double>(greater_than_next[i]);
    }
  } else {
    i_binary_expand_op(timeBlinderVec, scores, greater_than_next);
  }

  // This checks to make sure that at least one frequency has a
  // threshold exceeding score. If there isn't one (all the scroes
  // are below the threshold), we set the output variables as NaN
  // so that the caller knows nothing was detected.
  // 2021-10-11
  // Update to to set all peak_masked_curr_scores less than the
  // threshold to zero. This wasn't needed when there was one
  // threshold, but with local frequency specific thresholds, we
  // only want threshold positive peaks listed in this vector so
  // the while loop below doesn't try to sort out sub-threshold
  // peaks. This can happen when there is a sub threhold peak that
  // has a higher score than a score at a different frequency that
  // was lower, but exceeded it's local threshold.
  i = thresh.threshVecFine.size(0);
  if ((timeBlinderVec.size(0) != i) && ((timeBlinderVec.size(0) != 1) && (i != 1)))
  {
    emlrtDimSizeImpxCheckR2021b(timeBlinderVec.size(0), i, &kb_emlrtECI);
  }

  if (timeBlinderVec.size(0) == thresh.threshVecFine.size(0)) {
    b_freq_mask.set_size(timeBlinderVec.size(0));
    loop_ub = timeBlinderVec.size(0);
    for (i = 0; i < loop_ub; i++) {
      b_freq_mask[i] = (timeBlinderVec[i] >= thresh.threshVecFine[i]);
    }
  } else {
    h_binary_expand_op(b_freq_mask, timeBlinderVec, this);
  }

  if ((timeBlinderVec.size(0) != b_freq_mask.size(0)) && ((timeBlinderVec.size(0)
        != 1) && (b_freq_mask.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(timeBlinderVec.size(0), b_freq_mask.size(0),
      &lb_emlrtECI);
  }

  if (timeBlinderVec.size(0) == b_freq_mask.size(0)) {
    loop_ub = timeBlinderVec.size(0);
    for (i = 0; i < loop_ub; i++) {
      timeBlinderVec[i] = timeBlinderVec[i] * static_cast<double>(b_freq_mask[i]);
    }
  } else {
    g_binary_expand_op(timeBlinderVec, b_freq_mask);
  }

  // ------------------------------------------------
  // thresh_hold = thresh;thresh = interp1(obj.stft.f,thresh,Wf);
  i = thresh.threshVecFine.size(0);
  if ((timeBlinderVec.size(0) != i) && ((timeBlinderVec.size(0) != 1) && (i != 1)))
  {
    emlrtDimSizeImpxCheckR2021b(timeBlinderVec.size(0), i, &mb_emlrtECI);
  }

  if (timeBlinderVec.size(0) == thresh.threshVecFine.size(0)) {
    score_right_bndry.set_size(timeBlinderVec.size(0));
    loop_ub = timeBlinderVec.size(0);
    for (i = 0; i < loop_ub; i++) {
      score_right_bndry[i] = (timeBlinderVec[i] > thresh.threshVecFine[i]);
    }

    y = coder::internal::allOrAny_anonFcn1(score_right_bndry);
  } else {
    y = binary_expand_op(timeBlinderVec, this);
  }

  if (!y) {
    // peak_ind = [];
    peak_ind.set_size(1);
    peak_ind[0] = rtNaN;
    peak.set_size(1);

    // [];
  }

  // Keep doing this loop below while there are scores that exceed
  // the threshold which aren't masked as a valley, +slope, -slope,
  // or previously identified peak/sideband.
  // figure; plot3([1:160],ones(160,1)*0,curr_scores)
  i = thresh.threshVecFine.size(0);
  int exitg1;
  do {
    exitg1 = 0;
    if ((timeBlinderVec.size(0) != i) && ((timeBlinderVec.size(0) != 1) && (i !=
          1))) {
      emlrtDimSizeImpxCheckR2021b(timeBlinderVec.size(0), i, &nb_emlrtECI);
    }

    if (timeBlinderVec.size(0) == thresh.threshVecFine.size(0)) {
      score_right_bndry.set_size(timeBlinderVec.size(0));
      loop_ub = timeBlinderVec.size(0);
      for (i1 = 0; i1 < loop_ub; i1++) {
        score_right_bndry[i1] = (timeBlinderVec[i1] > thresh.threshVecFine[i1]);
      }

      y = coder::internal::allOrAny_anonFcn1(score_right_bndry);
    } else {
      y = binary_expand_op(timeBlinderVec, this);
    }

    if (y) {
      //    hold on; plot3([1:160],ones(160,1)*p,curr_scores)
      // Identify the highest scoring peak of the currently
      // identifed scores.
      if ((static_cast<int>(p) < 1) || (static_cast<int>(p) > peak.size(0))) {
        rtDynamicBoundsError(static_cast<int>(p), 1, peak.size(0), &yb_emlrtBCI);
      }

      coder::internal::maximum(timeBlinderVec, &peak[static_cast<int>(p) - 1],
        &nx);
      if ((static_cast<int>(p) < 1) || (static_cast<int>(p) > peak_ind.size(0)))
      {
        rtDynamicBoundsError(static_cast<int>(p), 1, peak_ind.size(0),
                             &ac_emlrtBCI);
      }

      peak_ind[static_cast<int>(p) - 1] = nx;

      // Build a mask that highlights all the elements whose time
      // windows share (or are close) to any of the time windows
      // of the pulses associated with the current peak.
      i1 = static_cast<int>(n_blks);
      if (static_cast<int>(n_blks) - 1 >= 0) {
        i3 = S_cols.size(0);
        b_loop_ub = S_cols.size(0);
        c_loop_ub = n_freqs;
        i4 = S_cols.size(0);
        d_loop_ub = S_cols.size(0);
        i5 = S_cols.size(0);
        e_loop_ub = S_cols.size(0);
        i6 = S_cols.size(0);
        f_loop_ub = S_cols.size(0);
        i7 = S_cols.size(0);
        g_loop_ub = S_cols.size(0);
        stft_dt = peak_ind[static_cast<int>(p) - 1];
        if (stft_dt - 1.0 < 1.0) {
          i8 = 0;
          i9 = 1;
          i10 = -1;
        } else {
          if (stft_dt - 1.0 != static_cast<int>(stft_dt - 1.0)) {
            rtIntegerError(stft_dt - 1.0, &ub_emlrtDCI);
          }

          if ((static_cast<int>(stft_dt - 1.0) < 1) || (static_cast<int>(stft_dt
                - 1.0) > slope_val.size(0))) {
            rtDynamicBoundsError(static_cast<int>(stft_dt - 1.0), 1,
                                 slope_val.size(0), &fg_emlrtBCI);
          }

          i8 = static_cast<int>(stft_dt - 1.0) - 1;
          i9 = -1;
          if (slope_val.size(0) < 1) {
            rtDynamicBoundsError(1, 1, slope_val.size(0), &gg_emlrtBCI);
          }

          i10 = 0;
        }

        h_loop_ub = div_s32(i10 - i8, i9);
        if (stft_dt + 1.0 > slope_val.size(0)) {
          i11 = 0;
          i12 = 0;
        } else {
          stft_dt = peak_ind[static_cast<int>(p) - 1] + 1.0;
          if (stft_dt != static_cast<int>(stft_dt)) {
            rtIntegerError(stft_dt, &tb_emlrtDCI);
          }

          if ((static_cast<int>(stft_dt) < 1) || (static_cast<int>(stft_dt) >
               slope_val.size(0))) {
            rtDynamicBoundsError(static_cast<int>(stft_dt), 1, slope_val.size(0),
                                 &dg_emlrtBCI);
          }

          i11 = static_cast<int>(stft_dt) - 1;
          if (slope_val.size(0) < 1) {
            rtDynamicBoundsError(slope_val.size(0), 1, slope_val.size(0),
                                 &eg_emlrtBCI);
          }

          i12 = slope_val.size(0);
        }

        i_loop_ub = i12 - i11;
        b_p = static_cast<int>(p);
      }

      for (int k{0}; k < i1; k++) {
        int i13;
        int i14;

        // This block of code is used to find the number of time
        // windows between the current peak and the others in
        // the same block. It checks the blocks in front and
        // behind
        // n_diff_to_curr_pk is a vector of time window
        // differences between the currently identified peaks and
        // all the other identified time windows in the current
        // block
        if ((static_cast<int>(p) < 1) || (static_cast<int>(p) > peak_ind.size(0)))
        {
          rtDynamicBoundsError(static_cast<int>(p), 1, peak_ind.size(0),
                               &bc_emlrtBCI);
        }

        stft_dt = peak_ind[static_cast<int>(p) - 1];
        if (stft_dt != static_cast<int>(stft_dt)) {
          rtIntegerError(stft_dt, &cb_emlrtDCI);
        }

        if ((static_cast<int>(stft_dt) < 1) || (static_cast<int>(stft_dt) >
             S_cols.size(0))) {
          rtDynamicBoundsError(static_cast<int>(stft_dt), 1, S_cols.size(0),
                               &cc_emlrtBCI);
        }

        if ((static_cast<int>(k + 1U) < 1) || (static_cast<int>(k + 1U) >
             S_cols.size(1))) {
          rtDynamicBoundsError(static_cast<int>(k + 1U), 1, S_cols.size(1),
                               &dc_emlrtBCI);
        }

        t_lastknown = S_cols[(static_cast<int>(stft_dt) + S_cols.size(0) * k) -
          1];
        if ((static_cast<int>(k + 1U) < 1) || (static_cast<int>(k + 1U) >
             S_cols.size(1))) {
          rtDynamicBoundsError(static_cast<int>(k + 1U), 1, S_cols.size(1),
                               &ec_emlrtBCI);
        }

        b_S_cols.set_size(i3);
        for (i2 = 0; i2 < b_loop_ub; i2++) {
          b_S_cols[i2] = t_lastknown - S_cols[i2 + S_cols.size(0) * k];
        }

        nx = b_S_cols.size(0);
        timeBlinderVec.set_size(b_S_cols.size(0));
        if (b_S_cols.size(0) > 2147483646) {
          coder::check_forloop_overflow_error();
        }

        for (maxStftTimeWind = 0; maxStftTimeWind < nx; maxStftTimeWind++) {
          timeBlinderVec[maxStftTimeWind] = std::abs(b_S_cols[maxStftTimeWind]);
        }

        indsOfBinsValid.set_size(n_freqs);
        n_diff_check_for.set_size(n_freqs);
        for (i2 = 0; i2 < c_loop_ub; i2++) {
          indsOfBinsValid[i2] = rtNaN;
          n_diff_check_for[i2] = rtNaN;
        }

        // Remember that the segments are long enough to
        // guarentee K pulses, but can get K+1. If we identified
        // the first or last K peaks, but there is an extra, its
        // side bands might be in this list in nearby frequencies.
        // We need to exclude these like we do the sidebands that
        // are nearby in time. In this case, we want to see if
        // any of the identified peaks are +/-tp+/-tip from the
        // current peak. Here we look a block forward and/or
        // backward at the reported columns of the S matrix that
        // were identified as exceeding the decision threshold
        // and see if those columns are the same as the current
        // blocks identified column. We'll check later in the
        // code to see if these are less than a threshold.
        if (static_cast<double>(k) + 1.0 <= n_blks - 1.0) {
          // Don't compute forward check when k=n_blks
          if ((static_cast<int>(p) < 1) || (static_cast<int>(p) > peak_ind.size
               (0))) {
            rtDynamicBoundsError(static_cast<int>(p), 1, peak_ind.size(0),
                                 &fc_emlrtBCI);
          }

          if (stft_dt != static_cast<int>(stft_dt)) {
            rtIntegerError(stft_dt, &db_emlrtDCI);
          }

          if ((static_cast<int>(stft_dt) < 1) || (static_cast<int>(stft_dt) >
               S_cols.size(0))) {
            rtDynamicBoundsError(static_cast<int>(stft_dt), 1, S_cols.size(0),
                                 &gc_emlrtBCI);
          }

          if ((static_cast<int>(k + 1U) < 1) || (static_cast<int>(k + 1U) >
               S_cols.size(1))) {
            rtDynamicBoundsError(static_cast<int>(k + 1U), 1, S_cols.size(1),
                                 &hc_emlrtBCI);
          }

          t_lastknown = S_cols[(static_cast<int>(stft_dt) + S_cols.size(0) * k)
            - 1];
          if ((static_cast<int>(k + 2U) < 1) || (static_cast<int>(k + 2U) >
               S_cols.size(1))) {
            rtDynamicBoundsError(static_cast<int>(k + 2U), 1, S_cols.size(1),
                                 &ic_emlrtBCI);
          }

          loop_ub = S_cols.size(0);
          b_S_cols.set_size(S_cols.size(0));
          for (i2 = 0; i2 < loop_ub; i2++) {
            b_S_cols[i2] = t_lastknown - S_cols[i2 + S_cols.size(0) * (k + 1)];
          }

          nx = b_S_cols.size(0);
          n_diff_check_for.set_size(b_S_cols.size(0));
          if (b_S_cols.size(0) > 2147483646) {
            coder::check_forloop_overflow_error();
          }

          for (maxStftTimeWind = 0; maxStftTimeWind < nx; maxStftTimeWind++) {
            n_diff_check_for[maxStftTimeWind] = std::abs
              (b_S_cols[maxStftTimeWind]);
          }
        } else if (k + 1U >= 2U) {
          // Don't compute backward check when k=1
          if ((static_cast<int>(p) < 1) || (static_cast<int>(p) > peak_ind.size
               (0))) {
            rtDynamicBoundsError(static_cast<int>(p), 1, peak_ind.size(0),
                                 &je_emlrtBCI);
          }

          if (stft_dt != static_cast<int>(stft_dt)) {
            rtIntegerError(stft_dt, &rb_emlrtDCI);
          }

          if ((static_cast<int>(stft_dt) < 1) || (static_cast<int>(stft_dt) >
               S_cols.size(0))) {
            rtDynamicBoundsError(static_cast<int>(stft_dt), 1, S_cols.size(0),
                                 &ke_emlrtBCI);
          }

          if ((static_cast<int>(k + 1U) < 1) || (static_cast<int>(k + 1U) >
               S_cols.size(1))) {
            rtDynamicBoundsError(static_cast<int>(k + 1U), 1, S_cols.size(1),
                                 &le_emlrtBCI);
          }

          t_lastknown = S_cols[(static_cast<int>(stft_dt) + S_cols.size(0) * k)
            - 1];
          if ((k < 1) || (k > S_cols.size(1))) {
            rtDynamicBoundsError(k, 1, S_cols.size(1), &me_emlrtBCI);
          }

          loop_ub = S_cols.size(0);
          b_S_cols.set_size(S_cols.size(0));
          for (i2 = 0; i2 < loop_ub; i2++) {
            b_S_cols[i2] = t_lastknown - S_cols[i2 + S_cols.size(0) * (k - 1)];
          }

          nx = b_S_cols.size(0);
          indsOfBinsValid.set_size(b_S_cols.size(0));
          if (b_S_cols.size(0) > 2147483646) {
            coder::check_forloop_overflow_error();
          }

          for (maxStftTimeWind = 0; maxStftTimeWind < nx; maxStftTimeWind++) {
            indsOfBinsValid[maxStftTimeWind] = std::abs(b_S_cols[maxStftTimeWind]);
          }
        }

        // There could be instances when a single block contains
        // two pulses, as mentioned above, but if the search is
        // only for one pulse (K = 1) then the if statments above
        // won't run. We need here to check if there are
        // identified scores within the current block that are
        // also one time repetition interval (tip+/tipu) away
        // from the current peak
        if ((static_cast<int>(k + 1U) < 1) || (static_cast<int>(k + 1U) >
             S_cols.size(1))) {
          rtDynamicBoundsError(static_cast<int>(k + 1U), 1, S_cols.size(1),
                               &jc_emlrtBCI);
        }

        if ((static_cast<int>(p) < 1) || (static_cast<int>(p) > peak_ind.size(0)))
        {
          rtDynamicBoundsError(static_cast<int>(p), 1, peak_ind.size(0),
                               &kc_emlrtBCI);
        }

        if (stft_dt != static_cast<int>(stft_dt)) {
          rtIntegerError(stft_dt, &eb_emlrtDCI);
        }

        if ((static_cast<int>(stft_dt) < 1) || (static_cast<int>(stft_dt) >
             S_cols.size(0))) {
          rtDynamicBoundsError(static_cast<int>(stft_dt), 1, S_cols.size(0),
                               &lc_emlrtBCI);
        }

        if ((static_cast<int>(k + 1U) < 1) || (static_cast<int>(k + 1U) >
             S_cols.size(1))) {
          rtDynamicBoundsError(static_cast<int>(k + 1U), 1, S_cols.size(1),
                               &mc_emlrtBCI);
        }

        t_lastknown = (S_cols[(static_cast<int>(stft_dt) + S_cols.size(0) * k) -
                       1] + b_N) + b_M;
        slope_pos.set_size(i4);
        for (i2 = 0; i2 < d_loop_ub; i2++) {
          slope_pos[i2] = (S_cols[i2 + S_cols.size(0) * k] < t_lastknown);
        }

        if ((static_cast<int>(k + 1U) < 1) || (static_cast<int>(k + 1U) >
             S_cols.size(1))) {
          rtDynamicBoundsError(static_cast<int>(k + 1U), 1, S_cols.size(1),
                               &nc_emlrtBCI);
        }

        if ((static_cast<int>(p) < 1) || (static_cast<int>(p) > peak_ind.size(0)))
        {
          rtDynamicBoundsError(static_cast<int>(p), 1, peak_ind.size(0),
                               &oc_emlrtBCI);
        }

        if (stft_dt != static_cast<int>(stft_dt)) {
          rtIntegerError(stft_dt, &fb_emlrtDCI);
        }

        if ((static_cast<int>(stft_dt) < 1) || (static_cast<int>(stft_dt) >
             S_cols.size(0))) {
          rtDynamicBoundsError(static_cast<int>(stft_dt), 1, S_cols.size(0),
                               &pc_emlrtBCI);
        }

        if ((static_cast<int>(k + 1U) < 1) || (static_cast<int>(k + 1U) >
             S_cols.size(1))) {
          rtDynamicBoundsError(static_cast<int>(k + 1U), 1, S_cols.size(1),
                               &qc_emlrtBCI);
        }

        t_lastknown = (S_cols[(static_cast<int>(stft_dt) + S_cols.size(0) * k) -
                       1] + b_N) - b_M;
        b_freq_mask.set_size(i5);
        for (i2 = 0; i2 < e_loop_ub; i2++) {
          b_freq_mask[i2] = (S_cols[i2 + S_cols.size(0) * k] > t_lastknown);
        }

        if (slope_pos.size(0) != b_freq_mask.size(0)) {
          rtSizeEq1DError(slope_pos.size(0), b_freq_mask.size(0), &ob_emlrtECI);
        }

        loop_ub = slope_pos.size(0);
        for (i2 = 0; i2 < loop_ub; i2++) {
          slope_pos[i2] = (slope_pos[i2] && b_freq_mask[i2]);
        }

        if ((static_cast<int>(k + 1U) < 1) || (static_cast<int>(k + 1U) >
             S_cols.size(1))) {
          rtDynamicBoundsError(static_cast<int>(k + 1U), 1, S_cols.size(1),
                               &rc_emlrtBCI);
        }

        if ((static_cast<int>(p) < 1) || (static_cast<int>(p) > peak_ind.size(0)))
        {
          rtDynamicBoundsError(static_cast<int>(p), 1, peak_ind.size(0),
                               &sc_emlrtBCI);
        }

        if (stft_dt != static_cast<int>(stft_dt)) {
          rtIntegerError(stft_dt, &gb_emlrtDCI);
        }

        if ((static_cast<int>(stft_dt) < 1) || (static_cast<int>(stft_dt) >
             S_cols.size(0))) {
          rtDynamicBoundsError(static_cast<int>(stft_dt), 1, S_cols.size(0),
                               &tc_emlrtBCI);
        }

        if ((static_cast<int>(k + 1U) < 1) || (static_cast<int>(k + 1U) >
             S_cols.size(1))) {
          rtDynamicBoundsError(static_cast<int>(k + 1U), 1, S_cols.size(1),
                               &uc_emlrtBCI);
        }

        t_lastknown = (S_cols[(static_cast<int>(stft_dt) + S_cols.size(0) * k) -
                       1] - b_N) - b_M;
        score_right_bndry.set_size(i6);
        for (i2 = 0; i2 < f_loop_ub; i2++) {
          score_right_bndry[i2] = (S_cols[i2 + S_cols.size(0) * k] > t_lastknown);
        }

        if ((static_cast<int>(k + 1U) < 1) || (static_cast<int>(k + 1U) >
             S_cols.size(1))) {
          rtDynamicBoundsError(static_cast<int>(k + 1U), 1, S_cols.size(1),
                               &vc_emlrtBCI);
        }

        if ((static_cast<int>(p) < 1) || (static_cast<int>(p) > peak_ind.size(0)))
        {
          rtDynamicBoundsError(static_cast<int>(p), 1, peak_ind.size(0),
                               &wc_emlrtBCI);
        }

        if (stft_dt != static_cast<int>(stft_dt)) {
          rtIntegerError(stft_dt, &hb_emlrtDCI);
        }

        if ((static_cast<int>(stft_dt) < 1) || (static_cast<int>(stft_dt) >
             S_cols.size(0))) {
          rtDynamicBoundsError(static_cast<int>(stft_dt), 1, S_cols.size(0),
                               &xc_emlrtBCI);
        }

        if ((static_cast<int>(k + 1U) < 1) || (static_cast<int>(k + 1U) >
             S_cols.size(1))) {
          rtDynamicBoundsError(static_cast<int>(k + 1U), 1, S_cols.size(1),
                               &yc_emlrtBCI);
        }

        t_lastknown = (S_cols[(static_cast<int>(stft_dt) + S_cols.size(0) * k) -
                       1] - b_N) + b_M;
        b_freq_mask.set_size(i7);
        for (i2 = 0; i2 < g_loop_ub; i2++) {
          b_freq_mask[i2] = (S_cols[i2 + S_cols.size(0) * k] < t_lastknown);
        }

        if (score_right_bndry.size(0) != b_freq_mask.size(0)) {
          rtSizeEq1DError(score_right_bndry.size(0), b_freq_mask.size(0),
                          &pb_emlrtECI);
        }

        loop_ub = score_right_bndry.size(0);
        for (i2 = 0; i2 < loop_ub; i2++) {
          score_right_bndry[i2] = (score_right_bndry[i2] && b_freq_mask[i2]);
        }

        if ((slope_pos.size(0) != score_right_bndry.size(0)) && ((slope_pos.size
              (0) != 1) && (score_right_bndry.size(0) != 1))) {
          emlrtDimSizeImpxCheckR2021b(slope_pos.size(0), score_right_bndry.size
            (0), &qb_emlrtECI);
        }

        if (slope_pos.size(0) == score_right_bndry.size(0)) {
          loop_ub = slope_pos.size(0);
          for (i2 = 0; i2 < loop_ub; i2++) {
            slope_pos[i2] = (slope_pos[i2] || score_right_bndry[i2]);
          }
        } else {
          b_or(slope_pos, score_right_bndry);
        }

        // This code below builds a mask that highlights the
        // sidebands of the peak. It looks for the frequency bin
        // (higher and lower) where the score no longer meets
        // the threshold. If no threshold crossings are found,
        // it assumes the entire frequeny list is a sideband.
        // This happens often in an informed search method when
        // the frequency search has been narrowed to a small
        // band on either side of a known peak.
        // These are the number of frequency bins foward or
        // backward from the peak to the last score>threshold
        // inds_bkwd_2_thresh_xing = find(scores(peak_ind(p)-1:-1:1)<thresh,1,'first')-1;
        // inds_frwd_2_thresh_xing = find(scores(peak_ind(p)+1:end)<thresh,1,'first')-1;
        if ((static_cast<int>(p) < 1) || (static_cast<int>(p) > peak_ind.size(0)))
        {
          rtDynamicBoundsError(static_cast<int>(p), 1, peak_ind.size(0),
                               &ad_emlrtBCI);
        }

        if (peak_ind[static_cast<int>(p) - 1] - 1.0 < 1.0) {
          i2 = 0;
          i13 = 1;
          i14 = -1;
        } else {
          tip_temp = peak_ind[static_cast<int>(p) - 1] - 1.0;
          if (tip_temp != static_cast<int>(tip_temp)) {
            rtIntegerError(tip_temp, &qb_emlrtDCI);
          }

          if ((static_cast<int>(tip_temp) < 1) || (static_cast<int>(tip_temp) >
               scores.size(0))) {
            rtDynamicBoundsError(static_cast<int>(tip_temp), 1, scores.size(0),
                                 &he_emlrtBCI);
          }

          i2 = static_cast<int>(tip_temp) - 1;
          i13 = -1;
          if (scores.size(0) < 1) {
            rtDynamicBoundsError(1, 1, scores.size(0), &ie_emlrtBCI);
          }

          i14 = 0;
        }

        if ((static_cast<int>(p) < 1) || (static_cast<int>(p) > peak_ind.size(0)))
        {
          rtDynamicBoundsError(static_cast<int>(p), 1, peak_ind.size(0),
                               &bd_emlrtBCI);
        }

        if (peak_ind[static_cast<int>(p) - 1] - 1.0 < 1.0) {
          inds_bkwd_2_next_valley_data = 0;
          nColsOfS = 1;
          maxStftTimeWind = -1;
        } else {
          tip_temp = peak_ind[static_cast<int>(p) - 1] - 1.0;
          if (tip_temp != static_cast<int>(tip_temp)) {
            rtIntegerError(tip_temp, &pb_emlrtDCI);
          }

          inds_bkwd_2_next_valley_data = thresh.threshVecFine.size(0);
          if ((static_cast<int>(tip_temp) < 1) || (static_cast<int>(tip_temp) >
               inds_bkwd_2_next_valley_data)) {
            rtDynamicBoundsError(static_cast<int>(tip_temp), 1,
                                 inds_bkwd_2_next_valley_data, &fe_emlrtBCI);
          }

          inds_bkwd_2_next_valley_data = static_cast<int>(tip_temp) - 1;
          nColsOfS = -1;
          maxStftTimeWind = thresh.threshVecFine.size(0);
          if (maxStftTimeWind < 1) {
            rtDynamicBoundsError(1, 1, maxStftTimeWind, &ge_emlrtBCI);
          }

          maxStftTimeWind = 0;
        }

        loop_ub = div_s32(i14 - i2, i13);
        nx = div_s32(maxStftTimeWind - inds_bkwd_2_next_valley_data, nColsOfS) +
          1;
        if ((loop_ub + 1 != nx) && ((loop_ub + 1 != 1) && (nx != 1))) {
          emlrtDimSizeImpxCheckR2021b(loop_ub + 1, nx, &rb_emlrtECI);
        }

        if (loop_ub + 1 == nx) {
          score_right_bndry.set_size(loop_ub + 1);
          for (i14 = 0; i14 <= loop_ub; i14++) {
            score_right_bndry[i14] = (scores[i2 + i13 * i14] <
              thresh.threshVecFine[inds_bkwd_2_next_valley_data + nColsOfS * i14]);
          }

          coder::c_eml_find(score_right_bndry, (int *)&ii_data, &ii_size);
        } else {
          binary_expand_op((int *)&ii_data, &ii_size, scores, i2 + 1, i13, i14,
                           this, inds_bkwd_2_next_valley_data + 1, nColsOfS,
                           maxStftTimeWind);
        }

        wind_start_size = ii_size;
        for (i2 = 0; i2 < ii_size; i2++) {
          wind_start_data = static_cast<double>(ii_data) - 1.0;
        }

        if ((static_cast<int>(p) < 1) || (static_cast<int>(p) > peak_ind.size(0)))
        {
          rtDynamicBoundsError(static_cast<int>(p), 1, peak_ind.size(0),
                               &cd_emlrtBCI);
        }

        if (peak_ind[static_cast<int>(p) - 1] + 1.0 > scores.size(0)) {
          i2 = 0;
          i13 = 0;
        } else {
          tip_temp = peak_ind[static_cast<int>(p) - 1] + 1.0;
          if (tip_temp != static_cast<int>(tip_temp)) {
            rtIntegerError(tip_temp, &ob_emlrtDCI);
          }

          if ((static_cast<int>(tip_temp) < 1) || (static_cast<int>(tip_temp) >
               scores.size(0))) {
            rtDynamicBoundsError(static_cast<int>(tip_temp), 1, scores.size(0),
                                 &de_emlrtBCI);
          }

          i2 = static_cast<int>(tip_temp) - 1;
          if (scores.size(0) < 1) {
            rtDynamicBoundsError(scores.size(0), 1, scores.size(0), &ee_emlrtBCI);
          }

          i13 = scores.size(0);
        }

        if ((static_cast<int>(p) < 1) || (static_cast<int>(p) > peak_ind.size(0)))
        {
          rtDynamicBoundsError(static_cast<int>(p), 1, peak_ind.size(0),
                               &dd_emlrtBCI);
        }

        if (peak_ind[static_cast<int>(p) - 1] + 1.0 > thresh.threshVecFine.size
            (0)) {
          i14 = 0;
          nColsOfS = 0;
        } else {
          tip_temp = peak_ind[static_cast<int>(p) - 1] + 1.0;
          if (tip_temp != static_cast<int>(tip_temp)) {
            rtIntegerError(tip_temp, &nb_emlrtDCI);
          }

          i14 = thresh.threshVecFine.size(0);
          if ((static_cast<int>(tip_temp) < 1) || (static_cast<int>(tip_temp) >
               i14)) {
            rtDynamicBoundsError(static_cast<int>(tip_temp), 1, i14,
                                 &be_emlrtBCI);
          }

          i14 = static_cast<int>(tip_temp) - 1;
          inds_bkwd_2_next_valley_data = thresh.threshVecFine.size(0);
          nColsOfS = thresh.threshVecFine.size(0);
          if ((nColsOfS < 1) || (nColsOfS > inds_bkwd_2_next_valley_data)) {
            rtDynamicBoundsError(nColsOfS, 1, inds_bkwd_2_next_valley_data,
                                 &ce_emlrtBCI);
          }
        }

        loop_ub = i13 - i2;
        inds_bkwd_2_next_valley_data = nColsOfS - i14;
        if ((loop_ub != inds_bkwd_2_next_valley_data) && ((loop_ub != 1) &&
             (inds_bkwd_2_next_valley_data != 1))) {
          emlrtDimSizeImpxCheckR2021b(loop_ub, inds_bkwd_2_next_valley_data,
            &sb_emlrtECI);
        }

        if (loop_ub == inds_bkwd_2_next_valley_data) {
          score_right_bndry.set_size(loop_ub);
          for (i13 = 0; i13 < loop_ub; i13++) {
            score_right_bndry[i13] = (scores[i2 + i13] <
              thresh.threshVecFine[i14 + i13]);
          }

          coder::c_eml_find(score_right_bndry, (int *)&ii_data, &ii_size);
        } else {
          binary_expand_op((int *)&ii_data, &ii_size, scores, i2, i13, this, i14,
                           nColsOfS);
        }

        maxStftTimeWind = ii_size;
        for (i2 = 0; i2 < ii_size; i2++) {
          naive_wind_end = static_cast<double>(ii_data) - 1.0;
        }

        // Here we look for the location where the slope changes.
        // We don't use the -1 like above because we want to be
        // sure to capture the entire saddle between peaks, so
        // we include the point after the transition of the slope
        // sign. If we didn't do this, then the lowest point
        // between the peaks that was still above the threshold
        // wouldn't be included in a sideband mask and might get
        // picked up later as an additional peak.
        if ((static_cast<int>(p) < 1) || (static_cast<int>(p) > peak_ind.size(0)))
        {
          rtDynamicBoundsError(static_cast<int>(p), 1, peak_ind.size(0),
                               &ed_emlrtBCI);
        }

        score_right_bndry.set_size(div_s32(i10 - i8, i9) + 1);
        for (i2 = 0; i2 <= h_loop_ub; i2++) {
          score_right_bndry[i2] = slope_val[i8 + i9 * i2];
        }

        coder::c_eml_find(score_right_bndry, (int *)&ii_data, &ii_size);
        nx = ii_size;
        for (i2 = 0; i2 < ii_size; i2++) {
          inds_bkwd_2_next_valley_data = ii_data;
        }

        if ((static_cast<int>(p) < 1) || (static_cast<int>(p) > peak_ind.size(0)))
        {
          rtDynamicBoundsError(static_cast<int>(p), 1, peak_ind.size(0),
                               &fd_emlrtBCI);
        }

        score_right_bndry.set_size(i12 - i11);
        for (i2 = 0; i2 < i_loop_ub; i2++) {
          score_right_bndry[i2] = slope_val[i11 + i2];
        }

        coder::c_eml_find(score_right_bndry, (int *)&ii_data, &ii_size);

        // Wf_sub = Wf(freq_mask);
        if ((maxStftTimeWind == 0) && (wind_start_size == 0)) {
          // If it can't find a place backwards or forwards
          // that is less than the threshold, the whole thing
          // could be sideband. Often the case for informed
          // search.
          //                         sideband_msk = true(n_freqs,1);
          // Alternatively, the interactions of
          // adjacent sidebands might be so large, that there
          // are no adjacent scores that are below the
          // threshold. We need to deal with both of these
          // cases. In the latter, we need to find the
          // frequency bin ahead of and behind the peak where
          // the slope changes and define that as the
          // sidebands. If the slope doesn't change, then we
          // are likely the former case wherein the entire set
          // of scores are side band and we make the mask all
          // true.
          excld_msk_vec.set_size(n_freqs);
          for (i2 = 0; i2 < n_freqs; i2++) {
            excld_msk_vec[i2] = false;
          }

          if ((nx == 0) && (ii_size == 0)) {
            excld_msk_vec.set_size(n_freqs);
            for (i2 = 0; i2 < n_freqs; i2++) {
              excld_msk_vec[i2] = true;
            }
          } else if ((nx == 0) && (ii_size != 0)) {
            if ((static_cast<int>(p) < 1) || (static_cast<int>(p) >
                 peak_ind.size(0))) {
              rtDynamicBoundsError(static_cast<int>(p), 1, peak_ind.size(0),
                                   &jd_emlrtBCI);
            }

            if (stft_dt < 1.0) {
              loop_ub = 0;
            } else {
              if (n_freqs < 1) {
                rtDynamicBoundsError(1, 1, n_freqs, &kd_emlrtBCI);
              }

              if (stft_dt != static_cast<int>(peak_ind[static_cast<int>(p) - 1]))
              {
                rtIntegerError(peak_ind[static_cast<int>(p) - 1], &ib_emlrtDCI);
              }

              if ((static_cast<int>(peak_ind[static_cast<int>(p) - 1]) < 1) || (
                   static_cast<int>(peak_ind[static_cast<int>(p) - 1]) > n_freqs))
              {
                rtDynamicBoundsError(static_cast<int>(peak_ind[static_cast<int>
                  (p) - 1]), 1, n_freqs, &ld_emlrtBCI);
              }

              loop_ub = static_cast<int>(peak_ind[static_cast<int>(p) - 1]);
            }

            for (i2 = 0; i2 < loop_ub; i2++) {
              excld_msk_vec[i2] = true;
            }
          } else if ((nx != 0) && (ii_size == 0)) {
            if ((static_cast<int>(p) < 1) || (static_cast<int>(p) >
                 peak_ind.size(0))) {
              rtDynamicBoundsError(static_cast<int>(p), 1, peak_ind.size(0),
                                   &md_emlrtBCI);
            }

            if (stft_dt > n_freqs) {
              i2 = -1;
              i13 = 0;
            } else {
              if (stft_dt != static_cast<int>(peak_ind[static_cast<int>(p) - 1]))
              {
                rtIntegerError(peak_ind[static_cast<int>(p) - 1], &jb_emlrtDCI);
              }

              if ((static_cast<int>(peak_ind[static_cast<int>(p) - 1]) < 1) || (
                   static_cast<int>(peak_ind[static_cast<int>(p) - 1]) > n_freqs))
              {
                rtDynamicBoundsError(static_cast<int>(peak_ind[static_cast<int>
                  (p) - 1]), 1, n_freqs, &nd_emlrtBCI);
              }

              i2 = static_cast<int>(peak_ind[static_cast<int>(p) - 1]) - 2;
              if (n_freqs < 1) {
                rtDynamicBoundsError(n_freqs, 1, n_freqs, &od_emlrtBCI);
              }

              i13 = n_freqs;
            }

            loop_ub = (i13 - i2) - 1;
            for (i13 = 0; i13 < loop_ub; i13++) {
              excld_msk_vec[(i2 + i13) + 1] = true;
            }
          } else if ((nx != 0) && (ii_size != 0)) {
            if (ii_data < -static_cast<double>(inds_bkwd_2_next_valley_data)) {
              b_excluded_freq_bands.set_size(1, 0);
            } else {
              loop_ub = ii_data - static_cast<int>(-static_cast<double>
                (inds_bkwd_2_next_valley_data));
              b_excluded_freq_bands.set_size(1, loop_ub + 1);
              for (i2 = 0; i2 <= loop_ub; i2++) {
                b_excluded_freq_bands[i2] = -static_cast<double>
                  (inds_bkwd_2_next_valley_data) + static_cast<double>(i2);
              }
            }

            r15.set_size(1, b_excluded_freq_bands.size(1));
            if ((static_cast<int>(p) < 1) || (static_cast<int>(p) >
                 peak_ind.size(0))) {
              rtDynamicBoundsError(static_cast<int>(p), 1, peak_ind.size(0),
                                   &pd_emlrtBCI);
            }

            loop_ub = b_excluded_freq_bands.size(1);
            for (i2 = 0; i2 < loop_ub; i2++) {
              tip_temp = stft_dt + b_excluded_freq_bands[i2];
              if (tip_temp != static_cast<int>(tip_temp)) {
                rtIntegerError(tip_temp, &kb_emlrtDCI);
              }

              if ((static_cast<int>(tip_temp) < 1) || (static_cast<int>(tip_temp)
                   > n_freqs)) {
                rtDynamicBoundsError(static_cast<int>(tip_temp), 1, n_freqs,
                                     &qd_emlrtBCI);
              }

              r15[i2] = static_cast<int>(tip_temp);
            }

            loop_ub = r15.size(1);
            for (i2 = 0; i2 < loop_ub; i2++) {
              excld_msk_vec[r15[i2] - 1] = true;
            }
          }

          // If there was a threhold crossing before and/or after
          // the peak, sort out the sidebands here
        } else {
          excld_msk_vec.set_size(n_freqs);
          for (i2 = 0; i2 < n_freqs; i2++) {
            excld_msk_vec[i2] = false;
          }

          if ((maxStftTimeWind == 0) && (wind_start_size != 0)) {
            coder::array<double, 1U> c_excluded_freq_bands;

            // Threshold crossing back was found but not
            // forwards.
            // What is smaller, the distance from the peak to
            // the first entry backwards, or the distance
            // from the peak to the threshold crossing in
            // front of the peak? Use that distance as the
            // 1/2 width of the sideband.
            if (nx != 1) {
              fb_rtErrorWithMessageID(vb_emlrtRTEI.fName, vb_emlrtRTEI.lineNo);
            }

            excluded_freq_bands.set_size(nx, 2);
            for (i2 = 0; i2 < nx; i2++) {
              excluded_freq_bands[0] = inds_bkwd_2_next_valley_data;
            }

            excluded_freq_bands[excluded_freq_bands.size(0)] = wind_start_data;
            if ((static_cast<int>(p) < 1) || (static_cast<int>(p) >
                 bandwidth_of_peak.size(0))) {
              rtDynamicBoundsError(static_cast<int>(p), 1,
                                   bandwidth_of_peak.size(0), &rd_emlrtBCI);
            }

            c_excluded_freq_bands = excluded_freq_bands.reshape(2);
            bandwidth_of_peak[static_cast<int>(p) - 1] = coder::internal::
              b_unaryMinOrMax_anonFcn1(c_excluded_freq_bands);

            // Had to code this way so coder/simulink would know the size of the min operation
          } else if ((maxStftTimeWind != 0) && (wind_start_size == 0)) {
            coder::array<double, 1U> c_excluded_freq_bands;

            // Threshold crossing forward was found but not
            // backwards.
            // What is smaller, the distance from the peak to
            // the last entry forwards, or the distance
            // from the peak to the threshold crossing in
            // back of the peak? Use that distance as the
            // 1/2 width of the sideband.
            if (ii_size != 1) {
              fb_rtErrorWithMessageID(vb_emlrtRTEI.fName, vb_emlrtRTEI.lineNo);
            }

            excluded_freq_bands.set_size(ii_size, 2);
            for (i2 = 0; i2 < ii_size; i2++) {
              excluded_freq_bands[0] = ii_data;
            }

            excluded_freq_bands[excluded_freq_bands.size(0)] = naive_wind_end;
            if ((static_cast<int>(p) < 1) || (static_cast<int>(p) >
                 bandwidth_of_peak.size(0))) {
              rtDynamicBoundsError(static_cast<int>(p), 1,
                                   bandwidth_of_peak.size(0), &yd_emlrtBCI);
            }

            c_excluded_freq_bands = excluded_freq_bands.reshape(2);
            bandwidth_of_peak[static_cast<int>(p) - 1] = coder::internal::
              b_unaryMinOrMax_anonFcn1(c_excluded_freq_bands);

            // Had to code this way so coder/simulink
            // would know the size of the min operation
          } else {
            coder::array<double, 1U> c_excluded_freq_bands;

            // Threshold crossing forward and backward was
            // found.
            // What is smaller, the distance
            // from the peak to the threshold crossing in
            // or the distance from the peak to the nearby
            // valley? Use that distance as the 1/2 width of
            // the sideband. Do this both forwards and
            // backwards.
            if (nx != 0) {
              if (wind_start_size != 1) {
                fb_rtErrorWithMessageID(vb_emlrtRTEI.fName, vb_emlrtRTEI.lineNo);
              }

              excluded_freq_bands.set_size(wind_start_size, 2);
              for (i2 = 0; i2 < wind_start_size; i2++) {
                excluded_freq_bands[0] = wind_start_data;
              }

              excluded_freq_bands[excluded_freq_bands.size(0)] =
                inds_bkwd_2_next_valley_data;
              c_excluded_freq_bands = excluded_freq_bands.reshape(2);
              wind_start_data = coder::internal::b_unaryMinOrMax_anonFcn1
                (c_excluded_freq_bands);
              wind_start_size = 1;
            }

            if (ii_size != 0) {
              if (maxStftTimeWind != 1) {
                fb_rtErrorWithMessageID(vb_emlrtRTEI.fName, vb_emlrtRTEI.lineNo);
              }

              excluded_freq_bands.set_size(1, 2);
              excluded_freq_bands[0] = ii_data;
              for (i2 = 0; i2 < maxStftTimeWind; i2++) {
                excluded_freq_bands[excluded_freq_bands.size(0)] =
                  naive_wind_end;
              }

              c_excluded_freq_bands = excluded_freq_bands.reshape(2);
              naive_wind_end = coder::internal::b_unaryMinOrMax_anonFcn1
                (c_excluded_freq_bands);
              maxStftTimeWind = 1;
            }

            if (maxStftTimeWind != wind_start_size) {
              fb_rtErrorWithMessageID(vb_emlrtRTEI.fName, vb_emlrtRTEI.lineNo);
            }

            for (i2 = 0; i2 < wind_start_size; i2++) {
              freq_ind_rng_data[0] = wind_start_data;
            }

            for (i2 = 0; i2 < maxStftTimeWind; i2++) {
              freq_ind_rng_data[wind_start_size] = naive_wind_end;
            }

            nx = wind_start_size << 1;
            if ((static_cast<int>(p) < 1) || (static_cast<int>(p) >
                 bandwidth_of_peak.size(0))) {
              rtDynamicBoundsError(static_cast<int>(p), 1,
                                   bandwidth_of_peak.size(0), &ae_emlrtBCI);
            }

            b_freq_ind_rng_data.set(&freq_ind_rng_data[0], nx);
            bandwidth_of_peak[static_cast<int>(p) - 1] = coder::internal::
              unaryMinOrMax_anonFcn1(b_freq_ind_rng_data);
          }

          // Make sure we aren't requesting masking of elements
          // that are outside the bounds of what we have
          // available in the vector
          if ((static_cast<int>(p) < 1) || (static_cast<int>(p) > peak_ind.size
               (0))) {
            rtDynamicBoundsError(static_cast<int>(p), 1, peak_ind.size(0),
                                 &sd_emlrtBCI);
          }

          if ((static_cast<int>(p) < 1) || (static_cast<int>(p) >
               bandwidth_of_peak.size(0))) {
            rtDynamicBoundsError(static_cast<int>(p), 1, bandwidth_of_peak.size
                                 (0), &td_emlrtBCI);
          }

          t_srch_rng[0] = 1.0;
          t_lastknown = bandwidth_of_peak[static_cast<int>(p) - 1];
          t_srch_rng[1] = stft_dt - t_lastknown;
          tp_temp = coder::internal::maximum(t_srch_rng);
          if ((static_cast<int>(p) < 1) || (static_cast<int>(p) > peak_ind.size
               (0))) {
            rtDynamicBoundsError(static_cast<int>(p), 1, peak_ind.size(0),
                                 &ud_emlrtBCI);
          }

          if ((static_cast<int>(p) < 1) || (static_cast<int>(p) >
               bandwidth_of_peak.size(0))) {
            rtDynamicBoundsError(static_cast<int>(p), 1, bandwidth_of_peak.size
                                 (0), &vd_emlrtBCI);
          }

          t_srch_rng[0] = n_freqs;
          t_srch_rng[1] = stft_dt + t_lastknown;
          t_lastknown = coder::internal::minimum(t_srch_rng);
          if (tp_temp > t_lastknown) {
            i2 = -1;
            i13 = 0;
          } else {
            if (tp_temp != static_cast<int>(std::floor(tp_temp))) {
              rtIntegerError(tp_temp, &lb_emlrtDCI);
            }

            if ((static_cast<int>(tp_temp) < 1) || (static_cast<int>(tp_temp) >
                 n_freqs)) {
              rtDynamicBoundsError(static_cast<int>(tp_temp), 1, n_freqs,
                                   &wd_emlrtBCI);
            }

            i2 = static_cast<int>(tp_temp) - 2;
            if (t_lastknown != static_cast<int>(std::floor(t_lastknown))) {
              rtIntegerError(t_lastknown, &mb_emlrtDCI);
            }

            if ((static_cast<int>(t_lastknown) < 1) || (static_cast<int>
                 (t_lastknown) > n_freqs)) {
              rtDynamicBoundsError(static_cast<int>(t_lastknown), 1, n_freqs,
                                   &xd_emlrtBCI);
            }

            i13 = static_cast<int>(t_lastknown);
          }

          loop_ub = (i13 - i2) - 1;
          for (i13 = 0; i13 < loop_ub; i13++) {
            excld_msk_vec[(i2 + i13) + 1] = true;
          }
        }

        //                      timecheck(:,k) = (n_diff_to_curr_pk<=diff_thresh)|...
        //                                       (n_diff_check_back<=diff_thresh)|...
        //                                       (n_diff_check_for<=diff_thresh);
        // Here we build up a mask that incorporates all the
        // peaks and their sidebands that we have identified
        // so far. The msk(:,p+1) entry is here because we are
        // looping through n_blks and are updating the p+1 column
        // each time.
        if ((static_cast<int>(p) < 1) || (static_cast<int>(p) > msk.size(1))) {
          rtDynamicBoundsError(static_cast<int>(p), 1, msk.size(1), &gd_emlrtBCI);
        }

        if ((static_cast<int>(static_cast<double>(p) + 1.0) < 1) || (
             static_cast<int>(static_cast<double>(p) + 1.0) > msk.size(1))) {
          rtDynamicBoundsError(static_cast<int>(static_cast<double>(p) + 1.0), 1,
                               msk.size(1), &hd_emlrtBCI);
        }

        b_freq_mask.set_size(timeBlinderVec.size(0));
        loop_ub = timeBlinderVec.size(0);
        for (i2 = 0; i2 < loop_ub; i2++) {
          b_freq_mask[i2] = (timeBlinderVec[i2] <= diff_thresh);
        }

        r9.set_size(indsOfBinsValid.size(0));
        loop_ub = indsOfBinsValid.size(0);
        for (i2 = 0; i2 < loop_ub; i2++) {
          r9[i2] = (indsOfBinsValid[i2] <= diff_thresh);
        }

        if ((b_freq_mask.size(0) != r9.size(0)) && ((b_freq_mask.size(0) != 1) &&
             (r9.size(0) != 1))) {
          emlrtDimSizeImpxCheckR2021b(b_freq_mask.size(0), r9.size(0),
            &tb_emlrtECI);
        }

        if (b_freq_mask.size(0) == r9.size(0)) {
          loop_ub = b_freq_mask.size(0);
          for (i2 = 0; i2 < loop_ub; i2++) {
            b_freq_mask[i2] = (b_freq_mask[i2] || r9[i2]);
          }
        } else {
          b_or(b_freq_mask, r9);
        }

        r9.set_size(n_diff_check_for.size(0));
        loop_ub = n_diff_check_for.size(0);
        for (i2 = 0; i2 < loop_ub; i2++) {
          r9[i2] = (n_diff_check_for[i2] <= diff_thresh);
        }

        if ((b_freq_mask.size(0) != r9.size(0)) && ((b_freq_mask.size(0) != 1) &&
             (r9.size(0) != 1))) {
          emlrtDimSizeImpxCheckR2021b(b_freq_mask.size(0), r9.size(0),
            &tb_emlrtECI);
        }

        if (b_freq_mask.size(0) == r9.size(0)) {
          loop_ub = b_freq_mask.size(0);
          for (i2 = 0; i2 < loop_ub; i2++) {
            b_freq_mask[i2] = (b_freq_mask[i2] || r9[i2]);
          }
        } else {
          b_or(b_freq_mask, r9);
        }

        if ((excld_msk_vec.size(0) != b_freq_mask.size(0)) &&
            ((excld_msk_vec.size(0) != 1) && (b_freq_mask.size(0) != 1))) {
          emlrtDimSizeImpxCheckR2021b(excld_msk_vec.size(0), b_freq_mask.size(0),
            &ub_emlrtECI);
        }

        if (excld_msk_vec.size(0) == b_freq_mask.size(0)) {
          loop_ub = excld_msk_vec.size(0);
          for (i2 = 0; i2 < loop_ub; i2++) {
            excld_msk_vec[i2] = (excld_msk_vec[i2] || b_freq_mask[i2]);
          }
        } else {
          b_or(excld_msk_vec, b_freq_mask);
        }

        if ((excld_msk_vec.size(0) != slope_pos.size(0)) && ((excld_msk_vec.size
              (0) != 1) && (slope_pos.size(0) != 1))) {
          emlrtDimSizeImpxCheckR2021b(excld_msk_vec.size(0), slope_pos.size(0),
            &ub_emlrtECI);
        }

        loop_ub = msk.size(0);
        b_freq_mask.set_size(msk.size(0));
        for (i2 = 0; i2 < loop_ub; i2++) {
          b_freq_mask[i2] = (msk[i2 + msk.size(0) * (b_p - 1)] || msk[i2 +
                             msk.size(0) * static_cast<int>(p)]);
        }

        if (excld_msk_vec.size(0) == slope_pos.size(0)) {
          loop_ub = excld_msk_vec.size(0);
          for (i2 = 0; i2 < loop_ub; i2++) {
            excld_msk_vec[i2] = (excld_msk_vec[i2] || slope_pos[i2]);
          }
        } else {
          b_or(excld_msk_vec, slope_pos);
        }

        if ((b_freq_mask.size(0) != excld_msk_vec.size(0)) && ((b_freq_mask.size
              (0) != 1) && (excld_msk_vec.size(0) != 1))) {
          emlrtDimSizeImpxCheckR2021b(b_freq_mask.size(0), excld_msk_vec.size(0),
            &vb_emlrtECI);
        }

        if ((static_cast<int>(static_cast<double>(p) + 1.0) < 1) || (
             static_cast<int>(static_cast<double>(p) + 1.0) > msk.size(1))) {
          rtDynamicBoundsError(static_cast<int>(static_cast<double>(p) + 1.0), 1,
                               msk.size(1), &id_emlrtBCI);
        }

        if (b_freq_mask.size(0) == excld_msk_vec.size(0)) {
          loop_ub = b_freq_mask.size(0);
          for (i2 = 0; i2 < loop_ub; i2++) {
            b_freq_mask[i2] = (b_freq_mask[i2] || excld_msk_vec[i2]);
          }
        } else {
          b_or(b_freq_mask, excld_msk_vec);
        }

        rtSubAssignSizeCheck(msk.size(), 1, b_freq_mask.size(), 1, &wb_emlrtECI);
        loop_ub = b_freq_mask.size(0);
        for (i2 = 0; i2 < loop_ub; i2++) {
          msk[i2 + msk.size(0) * static_cast<int>(p)] = b_freq_mask[i2];
        }
      }

      // Extract the mask for this peak and no others
      if ((static_cast<int>(static_cast<double>(p) + 1.0) < 1) || (static_cast<
           int>(static_cast<double>(p) + 1.0) > msk.size(1))) {
        rtDynamicBoundsError(static_cast<int>(static_cast<double>(p) + 1.0), 1,
                             msk.size(1), &ne_emlrtBCI);
      }

      if ((static_cast<int>(p) < 1) || (static_cast<int>(p) > msk.size(1))) {
        rtDynamicBoundsError(static_cast<int>(p), 1, msk.size(1), &oe_emlrtBCI);
      }

      if ((static_cast<int>(p) < 1) || (static_cast<int>(p) > indiv_msk.size(1)))
      {
        rtDynamicBoundsError(static_cast<int>(p), 1, indiv_msk.size(1),
                             &pe_emlrtBCI);
      }

      loop_ub = msk.size(0);
      b_freq_mask.set_size(msk.size(0));
      for (i1 = 0; i1 < loop_ub; i1++) {
        b_freq_mask[i1] = (msk[i1 + msk.size(0) * static_cast<int>(p)] - msk[i1
                           + msk.size(0) * (static_cast<int>(p) - 1)] != 0);
      }

      rtSubAssignSizeCheck(indiv_msk.size(), 1, b_freq_mask.size(), 1,
                           &xb_emlrtECI);
      loop_ub = b_freq_mask.size(0);
      for (i1 = 0; i1 < loop_ub; i1++) {
        indiv_msk[i1 + indiv_msk.size(0) * (static_cast<int>(p) - 1)] =
          b_freq_mask[i1];
      }

      // Update the current scores to exclude peaks and sidebands
      // we have identified so far.
      if ((static_cast<int>(p + 1U) < 1) || (static_cast<int>(p + 1U) > msk.size
           (1))) {
        rtDynamicBoundsError(static_cast<int>(p + 1U), 1, msk.size(1),
                             &qe_emlrtBCI);
      }

      loop_ub = msk.size(0);
      b_freq_mask.set_size(msk.size(0));
      for (i1 = 0; i1 < loop_ub; i1++) {
        b_freq_mask[i1] = !msk[i1 + msk.size(0) * static_cast<int>(p)];
      }

      if ((scores.size(0) != b_freq_mask.size(0)) && ((scores.size(0) != 1) &&
           (b_freq_mask.size(0) != 1))) {
        emlrtDimSizeImpxCheckR2021b(scores.size(0), b_freq_mask.size(0),
          &yb_emlrtECI);
      }

      if (scores.size(0) == b_freq_mask.size(0)) {
        timeBlinderVec.set_size(scores.size(0));
        loop_ub = scores.size(0);
        for (i1 = 0; i1 < loop_ub; i1++) {
          timeBlinderVec[i1] = scores[i1] * static_cast<double>(b_freq_mask[i1]);
        }
      } else {
        i_binary_expand_op(timeBlinderVec, scores, b_freq_mask);
      }

      // Mask the recently found sidebands
      if ((timeBlinderVec.size(0) != greater_than_next.size(0)) &&
          ((timeBlinderVec.size(0) != 1) && (greater_than_next.size(0) != 1))) {
        emlrtDimSizeImpxCheckR2021b(timeBlinderVec.size(0),
          greater_than_next.size(0), &ac_emlrtECI);
      }

      if (timeBlinderVec.size(0) == greater_than_next.size(0)) {
        loop_ub = timeBlinderVec.size(0);
        for (i1 = 0; i1 < loop_ub; i1++) {
          timeBlinderVec[i1] = timeBlinderVec[i1] * static_cast<double>
            (greater_than_next[i1]);
        }
      } else {
        g_binary_expand_op(timeBlinderVec, greater_than_next);
      }

      // Mask to only look at peaks
      i1 = thresh.threshVecFine.size(0);
      if ((timeBlinderVec.size(0) != i1) && ((timeBlinderVec.size(0) != 1) &&
           (i1 != 1))) {
        emlrtDimSizeImpxCheckR2021b(timeBlinderVec.size(0), i1, &bc_emlrtECI);
      }

      if (timeBlinderVec.size(0) == thresh.threshVecFine.size(0)) {
        b_freq_mask.set_size(timeBlinderVec.size(0));
        loop_ub = timeBlinderVec.size(0);
        for (i1 = 0; i1 < loop_ub; i1++) {
          b_freq_mask[i1] = (timeBlinderVec[i1] >= thresh.threshVecFine[i1]);
        }
      } else {
        h_binary_expand_op(b_freq_mask, timeBlinderVec, this);
      }

      if ((timeBlinderVec.size(0) != b_freq_mask.size(0)) &&
          ((timeBlinderVec.size(0) != 1) && (b_freq_mask.size(0) != 1))) {
        emlrtDimSizeImpxCheckR2021b(timeBlinderVec.size(0), b_freq_mask.size(0),
          &cc_emlrtECI);
      }

      if (timeBlinderVec.size(0) == b_freq_mask.size(0)) {
        loop_ub = timeBlinderVec.size(0);
        for (i1 = 0; i1 < loop_ub; i1++) {
          timeBlinderVec[i1] = timeBlinderVec[i1] * static_cast<double>
            (b_freq_mask[i1]);
        }
      } else {
        g_binary_expand_op(timeBlinderVec, b_freq_mask);
      }

      // Eliminate non-threshold exceeding scores from consideration
      //                  hold on;plot(peak_masked_curr_scores)
      //                  pause(1)
      // peak_masked_curr_scores = curr_scores.*slope_peak.*independent_super_thresh_msk;
      p++;
    } else {
      exitg1 = 1;
    }
  } while (exitg1 == 0);

  // Clean up the msk and indiv_mask so their columns align with
  // n_pulsegroup_found.
  r2.set_size(msk.size(0), msk.size(1));
  loop_ub = msk.size(0) * msk.size(1);
  for (i = 0; i < loop_ub; i++) {
    r2[i] = msk[i];
  }

  coder::g_circshift(r2);
  if (static_cast<int>(p - 1U) >= 1) {
    if (r2.size(1) < 1) {
      rtDynamicBoundsError(1, 1, r2.size(1), &re_emlrtBCI);
    }

    if ((static_cast<int>(static_cast<double>(p) - 1.0) < 1) || (static_cast<int>
         (static_cast<double>(p) - 1.0) > r2.size(1))) {
      rtDynamicBoundsError(static_cast<int>(static_cast<double>(p) - 1.0), 1,
                           r2.size(1), &se_emlrtBCI);
    }
  }

  if (static_cast<int>(p - 1U) < 1) {
    loop_ub = 0;
  } else {
    if (indiv_msk.size(1) < 1) {
      rtDynamicBoundsError(1, 1, indiv_msk.size(1), &bg_emlrtBCI);
    }

    if ((static_cast<int>(p - 1U) < 1) || (static_cast<int>(p - 1U) >
         indiv_msk.size(1))) {
      rtDynamicBoundsError(static_cast<int>(p - 1U), 1, indiv_msk.size(1),
                           &cg_emlrtBCI);
    }

    loop_ub = static_cast<int>(p - 1U);
  }

  nx = indiv_msk.size(0) - 1;
  maxStftTimeWind = indiv_msk.size(0);
  for (i = 0; i < loop_ub; i++) {
    for (i1 = 0; i1 < maxStftTimeWind; i1++) {
      indiv_msk[i1 + (nx + 1) * i] = indiv_msk[i1 + indiv_msk.size(0) * i];
    }
  }

  indiv_msk.set_size(nx + 1, loop_ub);
  if (static_cast<int>(p - 1U) > 0) {
    // Only update from NaN if there were some found.
    if (peak_ind.size(0) < 1) {
      rtDynamicBoundsError(1, 1, peak_ind.size(0), &te_emlrtBCI);
    }

    if ((static_cast<int>(static_cast<double>(p) - 1.0) < 1) || (static_cast<int>
         (static_cast<double>(p) - 1.0) > peak_ind.size(0))) {
      rtDynamicBoundsError(static_cast<int>(static_cast<double>(p) - 1.0), 1,
                           peak_ind.size(0), &ue_emlrtBCI);
    }

    trueCount[0] = 1;
    trueCount[1] = static_cast<int>(p - 1U);
    coder::internal::indexShapeCheck(peak_ind.size(0), trueCount);
    peak_ind.set_size(static_cast<int>(p - 1U));
  }

  // Each row of msk is a mask that isolates the elements of the
  // yw_max_all_freq vector associated with that column's peak and all
  // higher power peaks. For exampl msk(:,2) provides a mask that
  // highlights which elements of yw_max_all_freq are associated in
  // time with the second highest peak and the first highest peak.
  // Plotting scores.*~msk(:,2) will plot all of the scores of
  // yw_max_all_freq that are not associated in time with the first
  // or second highest power peak.
  //             %% CODE FOR REPORTING A CANDIDATE PULSE AT ALL THE FREQUENCY
  // BINS WITHOUTH DOING THE THRESHOLDING.
  // Preallocate cur_pl matrix
  // This was the original code, but it doesn't work with Code
  // Generation
  // cur_pl(1:n_freqs,1:n_pls) = pulse;
  // cur_pl = pulse.empty(n_freqs,n_pls,0);  %Build empty array
  // cur_pl(n_freqs,n_pls,1) = pulse;        %This will cause all array elements to fill with the empty constructor
  // cur_pl = pulse;
  // cur_pl(n_freqs,n_pls) = pulse;
  makepulsestruc(&tip_temp, &tp_temp, &t_lastknown, &n_blks, &diff_thresh,
                 &stft_dt, expl_temp.t_next, &timetol, &wind_start_data,
                 &naive_wind_end, expl_temp.mode, &y, &t6_con_dec);
  expl_temp.con_dec = t6_con_dec;
  expl_temp.det_dec = y;
  expl_temp.fend = naive_wind_end;
  expl_temp.fstart = wind_start_data;
  expl_temp.fp = timetol;
  expl_temp.t_f = stft_dt;
  expl_temp.t_0 = diff_thresh;
  expl_temp.yw = n_blks;
  expl_temp.SNR = t_lastknown;
  expl_temp.P = tp_temp;
  expl_temp.A = tip_temp;
  coder::repmat(&expl_temp, static_cast<double>(yw_max_all_freq.size(0)),
                static_cast<double>(yw_max_all_freq.size(1)), pl_out);

  // Create a frequency array that accounts for the masking that
  // was done to reduce the frequency space.
  inds_bkwd_2_next_valley_data = freq_mask.size(0) - 1;
  nx = 0;
  for (wind_start_size = 0; wind_start_size <= inds_bkwd_2_next_valley_data;
       wind_start_size++) {
    if (freq_mask[wind_start_size]) {
      nx++;
    }
  }

  r10.set_size(nx);
  nx = 0;
  for (wind_start_size = 0; wind_start_size <= inds_bkwd_2_next_valley_data;
       wind_start_size++) {
    if (freq_mask[wind_start_size]) {
      r10[nx] = wind_start_size + 1;
      nx++;
    }
  }

  nx = Wf.size(0);
  loop_ub = r10.size(0);
  for (i = 0; i < loop_ub; i++) {
    if (r10[i] > nx) {
      rtDynamicBoundsError(r10[i], 1, nx, &ve_emlrtBCI);
    }
  }

  // freq_found = Wf_sub(S_rows);
  // t_found here is the start of the pulse - not the center like
  // in the time stamps in the stft, which are the centers of the
  // windows. The dt_stft/2 term offfset would affect both the first
  // and second terms of the equation below and therefore cancel.
  refmat.set_size(yw_max_all_freq.size(0), yw_max_all_freq.size(1));
  loop_ub = yw_max_all_freq.size(0) * yw_max_all_freq.size(1);
  for (i = 0; i < loop_ub; i++) {
    refmat[i] = rtNaN;
  }

  // t_found    = obj.stft.t(S_cols)-obj.stft.t(1)+obj.t_0;%Don't forget the add the t_0 of this waveform
  inds_bkwd_2_next_valley_data = freq_mask.size(0);
  for (wind_start_size = 0; wind_start_size < inds_bkwd_2_next_valley_data;
       wind_start_size++) {
    if (freq_mask[wind_start_size] && (wind_start_size + 1 > S_cols.size(0))) {
      rtDynamicBoundsError(wind_start_size + 1, 1, S_cols.size(0), &we_emlrtBCI);
    }
  }

  inds_bkwd_2_next_valley_data = freq_mask.size(0) - 1;
  nx = 0;
  for (wind_start_size = 0; wind_start_size <= inds_bkwd_2_next_valley_data;
       wind_start_size++) {
    if (freq_mask[wind_start_size]) {
      nx++;
    }
  }

  r11.set_size(nx);
  nx = 0;
  for (wind_start_size = 0; wind_start_size <= inds_bkwd_2_next_valley_data;
       wind_start_size++) {
    if (freq_mask[wind_start_size]) {
      r11[nx] = wind_start_size + 1;
      nx++;
    }
  }

  trueCount[0] = r11.size(0);
  trueCount[1] = S_cols.size(1);
  coder::internal::b_indexShapeCheck(stft->t.size(0), trueCount);
  inds_bkwd_2_next_valley_data = freq_mask.size(0);
  for (wind_start_size = 0; wind_start_size < inds_bkwd_2_next_valley_data;
       wind_start_size++) {
    if (freq_mask[wind_start_size] && (wind_start_size + 1 > n_freqs)) {
      rtDynamicBoundsError(wind_start_size + 1, 1, n_freqs, &xe_emlrtBCI);
    }
  }

  inds_bkwd_2_next_valley_data = freq_mask.size(0) - 1;
  nx = 0;
  for (wind_start_size = 0; wind_start_size <= inds_bkwd_2_next_valley_data;
       wind_start_size++) {
    if (freq_mask[wind_start_size]) {
      nx++;
    }
  }

  r12.set_size(nx);
  nx = 0;
  for (wind_start_size = 0; wind_start_size <= inds_bkwd_2_next_valley_data;
       wind_start_size++) {
    if (freq_mask[wind_start_size]) {
      r12[nx] = wind_start_size + 1;
      nx++;
    }
  }

  nx = stft->t.size(0);
  loop_ub = S_cols.size(1);
  r13.set_size(r12.size(0), S_cols.size(1));
  for (i = 0; i < loop_ub; i++) {
    maxStftTimeWind = r12.size(0);
    for (i1 = 0; i1 < maxStftTimeWind; i1++) {
      stft_dt = S_cols[(r12[i1] + S_cols.size(0) * i) - 1];
      if (stft_dt != static_cast<int>(std::floor(stft_dt))) {
        rtIntegerError(stft_dt, &sb_emlrtDCI);
      }

      if ((static_cast<int>(stft_dt) < 1) || (static_cast<int>(stft_dt) > nx)) {
        rtDynamicBoundsError(static_cast<int>(stft_dt), 1, nx, &ye_emlrtBCI);
      }

      r13[i1 + r13.size(0) * i] = stft->t[static_cast<int>(stft_dt) - 1];
    }
  }

  inds_bkwd_2_next_valley_data = freq_mask.size(0);
  nx = 0;
  for (wind_start_size = 0; wind_start_size < inds_bkwd_2_next_valley_data;
       wind_start_size++) {
    if (freq_mask[wind_start_size]) {
      nx++;
    }
  }

  trueCount[0] = nx;
  trueCount[1] = yw_max_all_freq.size(1);
  rtSubAssignSizeCheck(&trueCount[0], 2, r13.size(), 2, &dc_emlrtECI);
  i = stft->t.size(0);
  if (i < 1) {
    rtDynamicBoundsError(1, 1, i, &af_emlrtBCI);
  }

  inds_bkwd_2_next_valley_data = freq_mask.size(0) - 1;
  nx = 0;
  for (wind_start_size = 0; wind_start_size <= inds_bkwd_2_next_valley_data;
       wind_start_size++) {
    if (freq_mask[wind_start_size]) {
      nx++;
    }
  }

  r14.set_size(nx);
  nx = 0;
  for (wind_start_size = 0; wind_start_size <= inds_bkwd_2_next_valley_data;
       wind_start_size++) {
    if (freq_mask[wind_start_size]) {
      r14[nx] = wind_start_size + 1;
      nx++;
    }
  }

  t_lastknown = stft->t[0];
  loop_ub = r13.size(1);
  for (i = 0; i < loop_ub; i++) {
    maxStftTimeWind = r13.size(0);
    for (i1 = 0; i1 < maxStftTimeWind; i1++) {
      refmat[(r14[i1] + refmat.size(0) * i) - 1] = (r13[i1 + r13.size(0) * i] -
        t_lastknown) + t_0;
    }
  }

  // Don't forget the add the t_0 of this waveform
  // f_bands    = [Wf_sub-(Wf_sub(2)-Wf_sub(1))/2,...
  //               Wf_sub+(Wf_sub(2)-Wf_sub(1))/2];
  i = Wf.size(0);
  if (i < 2) {
    rtDynamicBoundsError(2, 1, i, &bf_emlrtBCI);
  }

  i = Wf.size(0);
  if (i < 1) {
    rtDynamicBoundsError(1, 1, i, &cf_emlrtBCI);
  }

  i = Wf.size(0);
  if (i < 2) {
    rtDynamicBoundsError(2, 1, i, &df_emlrtBCI);
  }

  i = Wf.size(0);
  if (i < 1) {
    rtDynamicBoundsError(1, 1, i, &ef_emlrtBCI);
  }

  t_lastknown = (Wf[1] - Wf[0]) / 2.0;
  timeBlinderVec.set_size(Wf.size(0));
  loop_ub = Wf.size(0);
  for (i = 0; i < loop_ub; i++) {
    timeBlinderVec[i] = Wf[i] - t_lastknown;
  }

  indsOfBinsValid.set_size(Wf.size(0));
  loop_ub = Wf.size(0);
  for (i = 0; i < loop_ub; i++) {
    indsOfBinsValid[i] = Wf[i] + t_lastknown;
  }

  if (indsOfBinsValid.size(0) != timeBlinderVec.size(0)) {
    fb_rtErrorWithMessageID(vb_emlrtRTEI.fName, vb_emlrtRTEI.lineNo);
  }

  excluded_freq_bands.set_size(timeBlinderVec.size(0), 2);
  loop_ub = timeBlinderVec.size(0);
  for (i = 0; i < loop_ub; i++) {
    excluded_freq_bands[i] = timeBlinderVec[i];
  }

  loop_ub = indsOfBinsValid.size(0);
  for (i = 0; i < loop_ub; i++) {
    excluded_freq_bands[i + excluded_freq_bands.size(0)] = indsOfBinsValid[i];
  }

  // Build out the pulse object for each one found
  i = yw_max_all_freq.size(1);
  for (wind_start_size = 0; wind_start_size < i; wind_start_size++) {
    for (nx = 0; nx < n_freqs; nx++) {
      if (nx + 1 > refmat.size(0)) {
        rtDynamicBoundsError(nx + 1, 1, refmat.size(0), &ff_emlrtBCI);
      }

      if (wind_start_size + 1 > refmat.size(1)) {
        rtDynamicBoundsError(wind_start_size + 1, 1, refmat.size(1),
                             &ff_emlrtBCI);
      }

      t_srch_rng[0] = ((refmat[nx + refmat.size(0) * wind_start_size] +
                        ps_pos->t_ip) - ps_pos->t_ipu) - (-ps_pos->t_ipj);
      if (nx + 1 > refmat.size(0)) {
        rtDynamicBoundsError(nx + 1, 1, refmat.size(0), &gf_emlrtBCI);
      }

      if (wind_start_size + 1 > refmat.size(1)) {
        rtDynamicBoundsError(wind_start_size + 1, 1, refmat.size(1),
                             &gf_emlrtBCI);
      }

      t_srch_rng[1] = ((refmat[nx + refmat.size(0) * wind_start_size] +
                        ps_pos->t_ip) + ps_pos->t_ipu) + ps_pos->t_ipj;
      if (nx + 1 > searchmat.size(0)) {
        rtDynamicBoundsError(nx + 1, 1, searchmat.size(0), &hf_emlrtBCI);
      }

      if (wind_start_size + 1 > searchmat.size(1)) {
        rtDynamicBoundsError(wind_start_size + 1, 1, searchmat.size(1),
                             &if_emlrtBCI);
      }

      if (nx + 1 > yw_max_all_freq.size(0)) {
        rtDynamicBoundsError(nx + 1, 1, yw_max_all_freq.size(0), &jf_emlrtBCI);
      }

      if (wind_start_size + 1 > yw_max_all_freq.size(1)) {
        rtDynamicBoundsError(wind_start_size + 1, 1, yw_max_all_freq.size(1),
                             &kf_emlrtBCI);
      }

      if (nx + 1 > signalPlusNoisePSD.size(0)) {
        rtDynamicBoundsError(nx + 1, 1, signalPlusNoisePSD.size(0), &lf_emlrtBCI);
      }

      if (wind_start_size + 1 > signalPlusNoisePSD.size(1)) {
        rtDynamicBoundsError(wind_start_size + 1, 1, signalPlusNoisePSD.size(1),
                             &mf_emlrtBCI);
      }

      if (nx + 1 > refmat.size(0)) {
        rtDynamicBoundsError(nx + 1, 1, refmat.size(0), &nf_emlrtBCI);
      }

      if (wind_start_size + 1 > refmat.size(1)) {
        rtDynamicBoundsError(wind_start_size + 1, 1, refmat.size(1),
                             &of_emlrtBCI);
      }

      if (nx + 1 > refmat.size(0)) {
        rtDynamicBoundsError(nx + 1, 1, refmat.size(0), &pf_emlrtBCI);
      }

      if (wind_start_size + 1 > refmat.size(1)) {
        rtDynamicBoundsError(wind_start_size + 1, 1, refmat.size(1),
                             &qf_emlrtBCI);
      }

      i1 = Wf.size(0);
      if (nx + 1 > i1) {
        rtDynamicBoundsError(nx + 1, 1, i1, &rf_emlrtBCI);
      }

      if (nx + 1 > excluded_freq_bands.size(0)) {
        rtDynamicBoundsError(nx + 1, 1, excluded_freq_bands.size(0),
                             &sf_emlrtBCI);
      }

      if (nx + 1 > pl_out.size(0)) {
        rtDynamicBoundsError(nx + 1, 1, pl_out.size(0), &tf_emlrtBCI);
      }

      if (wind_start_size + 1 > pl_out.size(1)) {
        rtDynamicBoundsError(wind_start_size + 1, 1, pl_out.size(1),
                             &uf_emlrtBCI);
      }

      b_makepulsestruc(searchmat[nx + searchmat.size(0) * wind_start_size],
                       yw_max_all_freq[nx + yw_max_all_freq.size(0) *
                       wind_start_size], signalPlusNoisePSD[nx +
                       signalPlusNoisePSD.size(0) * wind_start_size], refmat[nx
                       + refmat.size(0) * wind_start_size], refmat[nx +
                       refmat.size(0) * wind_start_size] + ps_pre->t_p,
                       t_srch_rng, Wf[nx], excluded_freq_bands[nx],
                       excluded_freq_bands[nx + excluded_freq_bands.size(0)],
                       &pl_out[nx + pl_out.size(0) * wind_start_size]);

      // %NaN,...
      if (nx + 1 > pl_out.size(0)) {
        rtDynamicBoundsError(nx + 1, 1, pl_out.size(0), &vf_emlrtBCI);
      }

      if (wind_start_size + 1 > pl_out.size(1)) {
        rtDynamicBoundsError(wind_start_size + 1, 1, pl_out.size(1),
                             &wf_emlrtBCI);
      }

      pl_out[nx + pl_out.size(0) * wind_start_size].con_dec = false;

      // Confirmation status
      if (nx + 1 > scores.size(0)) {
        rtDynamicBoundsError(nx + 1, 1, scores.size(0), &xf_emlrtBCI);
      }

      score_right_bndry.set_size(thresh.threshVecFine.size(0));
      loop_ub = thresh.threshVecFine.size(0);
      for (i1 = 0; i1 < loop_ub; i1++) {
        score_right_bndry[i1] = (scores[nx] >= thresh.threshVecFine[i1]);
      }

      if (coder::internal::ifWhileCond(score_right_bndry)) {
        // scores(j)>=thresh(j)
        if (nx + 1 > pl_out.size(0)) {
          rtDynamicBoundsError(nx + 1, 1, pl_out.size(0), &yf_emlrtBCI);
        }

        if (wind_start_size + 1 > pl_out.size(1)) {
          rtDynamicBoundsError(wind_start_size + 1, 1, pl_out.size(1),
                               &ag_emlrtBCI);
        }

        pl_out[nx + pl_out.size(0) * wind_start_size].det_dec = true;
      }
    }
  }
}

//
// Arguments    : coder::array<boolean_T, 2U> &in1
//                const coder::array<boolean_T, 2U> &in2
// Return Type  : void
//
static void b_and(coder::array<boolean_T, 2U> &in1, const coder::array<boolean_T,
                  2U> &in2)
{
  coder::array<boolean_T, 2U> b_in1;
  int i;
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  if (in2.size(1) == 1) {
    i = in1.size(1);
  } else {
    i = in2.size(1);
  }

  b_in1.set_size(1, i);
  stride_0_1 = (in1.size(1) != 1);
  stride_1_1 = (in2.size(1) != 1);
  if (in2.size(1) == 1) {
    loop_ub = in1.size(1);
  } else {
    loop_ub = in2.size(1);
  }

  for (i = 0; i < loop_ub; i++) {
    b_in1[i] = (in1[i * stride_0_1] && in2[i * stride_1_1]);
  }

  in1.set_size(1, b_in1.size(1));
  loop_ub = b_in1.size(1);
  for (i = 0; i < loop_ub; i++) {
    in1[i] = b_in1[i];
  }
}

//
// Arguments    : coder::array<boolean_T, 2U> &in1
//                const coder::array<double, 2U> &in2
//                const int in3[2]
//                const coder::array<double, 2U> &in4
//                const int in5[2]
// Return Type  : void
//
static void b_binary_expand_op(coder::array<boolean_T, 2U> &in1, const coder::
  array<double, 2U> &in2, const int in3[2], const coder::array<double, 2U> &in4,
  const int in5[2])
{
  int b_unnamed_idx_1;
  int c_unnamed_idx_1;
  int stride_1_1;
  int unnamed_idx_1;
  unnamed_idx_1 = in3[1];
  b_unnamed_idx_1 = in5[1];
  if (b_unnamed_idx_1 == 1) {
    c_unnamed_idx_1 = unnamed_idx_1;
  } else {
    c_unnamed_idx_1 = b_unnamed_idx_1;
  }

  in1.set_size(1, c_unnamed_idx_1);
  c_unnamed_idx_1 = (unnamed_idx_1 != 1);
  stride_1_1 = (b_unnamed_idx_1 != 1);
  if (b_unnamed_idx_1 != 1) {
    unnamed_idx_1 = b_unnamed_idx_1;
  }

  for (b_unnamed_idx_1 = 0; b_unnamed_idx_1 < unnamed_idx_1; b_unnamed_idx_1++)
  {
    in1[b_unnamed_idx_1] = (in2[b_unnamed_idx_1 * c_unnamed_idx_1] <=
      in4[b_unnamed_idx_1 * stride_1_1] + 100.0);
  }
}

//
// Arguments    : coder::array<boolean_T, 1U> &in1
//                const coder::array<boolean_T, 1U> &in2
// Return Type  : void
//
static void b_or(coder::array<boolean_T, 1U> &in1, const coder::array<boolean_T,
                 1U> &in2)
{
  coder::array<boolean_T, 1U> b_in1;
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in2.size(0) == 1) {
    i = in1.size(0);
  } else {
    i = in2.size(0);
  }

  b_in1.set_size(i);
  stride_0_0 = (in1.size(0) != 1);
  stride_1_0 = (in2.size(0) != 1);
  if (in2.size(0) == 1) {
    loop_ub = in1.size(0);
  } else {
    loop_ub = in2.size(0);
  }

  for (i = 0; i < loop_ub; i++) {
    b_in1[i] = (in1[i * stride_0_0] || in2[i * stride_1_0]);
  }

  in1.set_size(b_in1.size(0));
  loop_ub = b_in1.size(0);
  for (i = 0; i < loop_ub; i++) {
    in1[i] = b_in1[i];
  }
}

//
// Arguments    : coder::array<double, 2U> &in1
//                const coder::array<double, 2U> &in2
// Return Type  : void
//
static void b_plus(coder::array<double, 2U> &in1, const coder::array<double, 2U>
                   &in2)
{
  coder::array<double, 2U> b_in2;
  int aux_0_1;
  int aux_1_1;
  int b_loop_ub;
  int i;
  int i1;
  int loop_ub;
  int stride_0_0;
  int stride_0_1;
  int stride_1_0;
  int stride_1_1;
  if (in1.size(0) == 1) {
    i = in2.size(0);
  } else {
    i = in1.size(0);
  }

  if (in1.size(1) == 1) {
    i1 = in2.size(1);
  } else {
    i1 = in1.size(1);
  }

  b_in2.set_size(i, i1);
  stride_0_0 = (in2.size(0) != 1);
  stride_0_1 = (in2.size(1) != 1);
  stride_1_0 = (in1.size(0) != 1);
  stride_1_1 = (in1.size(1) != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  if (in1.size(1) == 1) {
    loop_ub = in2.size(1);
  } else {
    loop_ub = in1.size(1);
  }

  for (i = 0; i < loop_ub; i++) {
    if (in1.size(0) == 1) {
      b_loop_ub = in2.size(0);
    } else {
      b_loop_ub = in1.size(0);
    }

    for (i1 = 0; i1 < b_loop_ub; i1++) {
      b_in2[i1 + b_in2.size(0) * i] = in2[i1 * stride_0_0 + in2.size(0) *
        aux_0_1] + in1[i1 * stride_1_0 + in1.size(0) * aux_1_1];
    }

    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }

  in1.set_size(b_in2.size(0), b_in2.size(1));
  loop_ub = b_in2.size(1);
  for (i = 0; i < loop_ub; i++) {
    b_loop_ub = b_in2.size(0);
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      in1[i1 + in1.size(0) * i] = b_in2[i1 + b_in2.size(0) * i];
    }
  }
}

//
// Arguments    : const char *r
//                const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void b_rtErrorWithMessageID(const char *r, const char *aFcnName, int
  aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((outStream << "Order, ") << r) << ", must be finite.";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// Arguments    : coder::array<double, 2U> &in1
//                const waveform *in2
// Return Type  : void
//
static void binary_expand_op(coder::array<double, 2U> &in1, const waveform *in2)
{
  coder::array<creal_T, 2U> b_in2;
  int aux_0_1;
  int aux_1_1;
  int i;
  int i1;
  int loop_ub;
  int stride_0_0;
  int stride_0_1;
  int stride_1_0;
  int stride_1_1;
  if (in1.size(0) == 1) {
    i = in2->stft->S.size(0);
  } else {
    i = in1.size(0);
  }

  if (in1.size(1) == 1) {
    i1 = in2->stft->S.size(1);
  } else {
    i1 = in1.size(1);
  }

  b_in2.set_size(i, i1);
  stride_0_0 = (in2->stft->S.size(0) != 1);
  stride_0_1 = (in2->stft->S.size(1) != 1);
  stride_1_0 = (in1.size(0) != 1);
  stride_1_1 = (in1.size(1) != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  if (in1.size(1) == 1) {
    loop_ub = in2->stft->S.size(1);
  } else {
    loop_ub = in1.size(1);
  }

  for (i = 0; i < loop_ub; i++) {
    int b_loop_ub;
    if (in1.size(0) == 1) {
      b_loop_ub = in2->stft->S.size(0);
    } else {
      b_loop_ub = in1.size(0);
    }

    for (i1 = 0; i1 < b_loop_ub; i1++) {
      b_in2[i1 + b_in2.size(0) * i].re = in2->stft->S[i1 * stride_0_0 +
        in2->stft->S.size(0) * aux_0_1].re + in1[i1 * stride_1_0 + in1.size(0) *
        aux_1_1];
      b_in2[i1 + b_in2.size(0) * i].im = in2->stft->S[i1 * stride_0_0 +
        in2->stft->S.size(0) * aux_0_1].im;
    }

    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }

  coder::b_abs(b_in2, in1);
}

//
// Arguments    : coder::array<double, 2U> &in1
//                const coder::array<double, 2U> &in2
//                const coder::array<double, 2U> &in3
//                int in4
//                int in5
// Return Type  : void
//
static void binary_expand_op(coder::array<double, 2U> &in1, const coder::array<
  double, 2U> &in2, const coder::array<double, 2U> &in3, int in4, int in5)
{
  coder::array<double, 2U> b_in2;
  int aux_0_1;
  int aux_1_1;
  int i;
  int i1;
  int loop_ub;
  int stride_0_0;
  int stride_0_1;
  int stride_1_0;
  int stride_1_1;
  if (in3.size(0) == 1) {
    i = in2.size(0);
  } else {
    i = in3.size(0);
  }

  if (in3.size(1) == 1) {
    i1 = in2.size(1);
  } else {
    i1 = in3.size(1);
  }

  b_in2.set_size(i, i1);
  stride_0_0 = (in2.size(0) != 1);
  stride_0_1 = (in2.size(1) != 1);
  stride_1_0 = (in3.size(0) != 1);
  stride_1_1 = (in3.size(1) != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  if (in3.size(1) == 1) {
    loop_ub = in2.size(1);
  } else {
    loop_ub = in3.size(1);
  }

  for (i = 0; i < loop_ub; i++) {
    int b_loop_ub;
    if (in3.size(0) == 1) {
      b_loop_ub = in2.size(0);
    } else {
      b_loop_ub = in3.size(0);
    }

    for (i1 = 0; i1 < b_loop_ub; i1++) {
      b_in2[i1 + b_in2.size(0) * i] = in2[i1 * stride_0_0 + in2.size(0) *
        aux_0_1] + in3[i1 * stride_1_0 + in3.size(0) * aux_1_1];
    }

    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }

  double b_in4[2];
  b_in4[0] = static_cast<unsigned int>(in4);
  b_in4[1] = static_cast<unsigned int>(in5);
  coder::imresize(b_in2, b_in4, in1);
}

//
// Arguments    : coder::array<double, 1U> &in1
//                const coder::array<double, 2U> &in2
//                const coder::array<double, 2U> &in3
// Return Type  : void
//
static void binary_expand_op(coder::array<double, 1U> &in1, const coder::array<
  double, 2U> &in2, const coder::array<double, 2U> &in3)
{
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in3.size(1) == 1) {
    i = in2.size(1);
  } else {
    i = in3.size(1);
  }

  in1.set_size(i);
  stride_0_0 = (in2.size(1) != 1);
  stride_1_0 = (in3.size(1) != 1);
  if (in3.size(1) == 1) {
    loop_ub = in2.size(1);
  } else {
    loop_ub = in3.size(1);
  }

  for (i = 0; i < loop_ub; i++) {
    in1[i] = in2[i * stride_0_0] + in3[i * stride_1_0];
  }
}

//
// Arguments    : coder::array<double, 2U> &in1
//                double in2
//                const coder::array<double, 2U> &in3
// Return Type  : void
//
static void binary_expand_op(coder::array<double, 2U> &in1, double in2, const
  coder::array<double, 2U> &in3)
{
  coder::array<double, 2U> b_in2;
  int i;
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  if (in3.size(1) == 1) {
    i = in1.size(1);
  } else {
    i = in3.size(1);
  }

  b_in2.set_size(1, i);
  stride_0_1 = (in1.size(1) != 1);
  stride_1_1 = (in3.size(1) != 1);
  if (in3.size(1) == 1) {
    loop_ub = in1.size(1);
  } else {
    loop_ub = in3.size(1);
  }

  for (i = 0; i < loop_ub; i++) {
    b_in2[i] = (in2 + in1[i * stride_0_1]) + in3[i * stride_1_1];
  }

  in1.set_size(1, b_in2.size(1));
  loop_ub = b_in2.size(1);
  for (i = 0; i < loop_ub; i++) {
    in1[i] = b_in2[i];
  }
}

//
// Arguments    : coder::array<boolean_T, 1U> &in1
//                const coder::array<boolean_T, 1U> &in2
// Return Type  : void
//
static void c_and(coder::array<boolean_T, 1U> &in1, const coder::array<boolean_T,
                  1U> &in2)
{
  coder::array<boolean_T, 1U> b_in1;
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in2.size(0) == 1) {
    i = in1.size(0);
  } else {
    i = in2.size(0);
  }

  b_in1.set_size(i);
  stride_0_0 = (in1.size(0) != 1);
  stride_1_0 = (in2.size(0) != 1);
  if (in2.size(0) == 1) {
    loop_ub = in1.size(0);
  } else {
    loop_ub = in2.size(0);
  }

  for (i = 0; i < loop_ub; i++) {
    b_in1[i] = (in1[i * stride_0_0] && in2[i * stride_1_0]);
  }

  in1.set_size(b_in1.size(0));
  loop_ub = b_in1.size(0);
  for (i = 0; i < loop_ub; i++) {
    in1[i] = b_in1[i];
  }
}

//
// Arguments    : coder::array<boolean_T, 2U> &in1
//                const coder::array<double, 2U> &in2
//                const int in3[2]
//                const coder::array<double, 2U> &in4
//                const int in5[2]
// Return Type  : void
//
static void c_binary_expand_op(coder::array<boolean_T, 2U> &in1, const coder::
  array<double, 2U> &in2, const int in3[2], const coder::array<double, 2U> &in4,
  const int in5[2])
{
  int b_unnamed_idx_1;
  int c_unnamed_idx_1;
  int stride_1_1;
  int unnamed_idx_1;
  unnamed_idx_1 = in3[1];
  b_unnamed_idx_1 = in5[1];
  if (b_unnamed_idx_1 == 1) {
    c_unnamed_idx_1 = unnamed_idx_1;
  } else {
    c_unnamed_idx_1 = b_unnamed_idx_1;
  }

  in1.set_size(1, c_unnamed_idx_1);
  c_unnamed_idx_1 = (unnamed_idx_1 != 1);
  stride_1_1 = (b_unnamed_idx_1 != 1);
  if (b_unnamed_idx_1 != 1) {
    unnamed_idx_1 = b_unnamed_idx_1;
  }

  for (b_unnamed_idx_1 = 0; b_unnamed_idx_1 < unnamed_idx_1; b_unnamed_idx_1++)
  {
    in1[b_unnamed_idx_1] = (in2[b_unnamed_idx_1 * c_unnamed_idx_1] >=
      in4[b_unnamed_idx_1 * stride_1_1] - 100.0);
  }
}

//
// Arguments    : coder::array<boolean_T, 1U> &in1
//                const coder::array<boolean_T, 1U> &in2
//                const coder::array<boolean_T, 1U> &in3
// Return Type  : void
//
static void d_and(coder::array<boolean_T, 1U> &in1, const coder::array<boolean_T,
                  1U> &in2, const coder::array<boolean_T, 1U> &in3)
{
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in3.size(0) == 1) {
    i = in2.size(0);
  } else {
    i = in3.size(0);
  }

  in1.set_size(i);
  stride_0_0 = (in2.size(0) != 1);
  stride_1_0 = (in3.size(0) != 1);
  if (in3.size(0) == 1) {
    loop_ub = in2.size(0);
  } else {
    loop_ub = in3.size(0);
  }

  for (i = 0; i < loop_ub; i++) {
    in1[i] = (in2[i * stride_0_0] && in3[i * stride_1_0]);
  }
}

//
// Arguments    : coder::array<boolean_T, 2U> &in1
//                const coder::array<double, 2U> &in2
//                const int in3[2]
//                const coder::array<double, 2U> &in4
// Return Type  : void
//
static void d_binary_expand_op(coder::array<boolean_T, 2U> &in1, const coder::
  array<double, 2U> &in2, const int in3[2], const coder::array<double, 2U> &in4)
{
  int i;
  int stride_0_1;
  int stride_1_1;
  int unnamed_idx_1;
  unnamed_idx_1 = in3[1];
  if (in4.size(1) == 1) {
    i = unnamed_idx_1;
  } else {
    i = in4.size(1);
  }

  in1.set_size(1, i);
  stride_0_1 = (unnamed_idx_1 != 1);
  stride_1_1 = (in4.size(1) != 1);
  if (in4.size(1) != 1) {
    unnamed_idx_1 = in4.size(1);
  }

  for (i = 0; i < unnamed_idx_1; i++) {
    in1[i] = (in2[i * stride_0_1] <= in4[i * stride_1_1]);
  }
}

//
// Arguments    : coder::array<boolean_T, 2U> &in1
//                const coder::array<double, 2U> &in2
//                const int in3[2]
//                const coder::array<double, 2U> &in4
// Return Type  : void
//
static void e_binary_expand_op(coder::array<boolean_T, 2U> &in1, const coder::
  array<double, 2U> &in2, const int in3[2], const coder::array<double, 2U> &in4)
{
  int i;
  int stride_0_1;
  int stride_1_1;
  int unnamed_idx_1;
  unnamed_idx_1 = in3[1];
  if (in4.size(1) == 1) {
    i = unnamed_idx_1;
  } else {
    i = in4.size(1);
  }

  in1.set_size(1, i);
  stride_0_1 = (unnamed_idx_1 != 1);
  stride_1_1 = (in4.size(1) != 1);
  if (in4.size(1) != 1) {
    unnamed_idx_1 = in4.size(1);
  }

  for (i = 0; i < unnamed_idx_1; i++) {
    in1[i] = (in2[i * stride_0_1] >= in4[i * stride_1_1]);
  }
}

//
// Arguments    : coder::array<double, 2U> &in1
//                double in2
//                const coder::array<double, 2U> &in3
// Return Type  : void
//
static void f_binary_expand_op(coder::array<double, 2U> &in1, double in2, const
  coder::array<double, 2U> &in3)
{
  coder::array<double, 2U> b_in2;
  int i;
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  if (in3.size(1) == 1) {
    i = in1.size(1);
  } else {
    i = in3.size(1);
  }

  b_in2.set_size(1, i);
  stride_0_1 = (in1.size(1) != 1);
  stride_1_1 = (in3.size(1) != 1);
  if (in3.size(1) == 1) {
    loop_ub = in1.size(1);
  } else {
    loop_ub = in3.size(1);
  }

  for (i = 0; i < loop_ub; i++) {
    b_in2[i] = (in2 + in1[i * stride_0_1]) - in3[i * stride_1_1];
  }

  in1.set_size(1, b_in2.size(1));
  loop_ub = b_in2.size(1);
  for (i = 0; i < loop_ub; i++) {
    in1[i] = b_in2[i];
  }
}

//
// Arguments    : coder::array<double, 1U> &in1
//                const coder::array<boolean_T, 1U> &in2
// Return Type  : void
//
static void g_binary_expand_op(coder::array<double, 1U> &in1, const coder::array<
  boolean_T, 1U> &in2)
{
  coder::array<double, 1U> b_in1;
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in2.size(0) == 1) {
    i = in1.size(0);
  } else {
    i = in2.size(0);
  }

  b_in1.set_size(i);
  stride_0_0 = (in1.size(0) != 1);
  stride_1_0 = (in2.size(0) != 1);
  if (in2.size(0) == 1) {
    loop_ub = in1.size(0);
  } else {
    loop_ub = in2.size(0);
  }

  for (i = 0; i < loop_ub; i++) {
    b_in1[i] = in1[i * stride_0_0] * static_cast<double>(in2[i * stride_1_0]);
  }

  in1.set_size(b_in1.size(0));
  loop_ub = b_in1.size(0);
  for (i = 0; i < loop_ub; i++) {
    in1[i] = b_in1[i];
  }
}

//
// Arguments    : coder::array<boolean_T, 1U> &in1
//                const coder::array<double, 1U> &in2
//                const waveform *in3
// Return Type  : void
//
static void h_binary_expand_op(coder::array<boolean_T, 1U> &in1, const coder::
  array<double, 1U> &in2, const waveform *in3)
{
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in3->thresh.threshVecFine.size(0) == 1) {
    i = in2.size(0);
  } else {
    i = in3->thresh.threshVecFine.size(0);
  }

  in1.set_size(i);
  stride_0_0 = (in2.size(0) != 1);
  stride_1_0 = (in3->thresh.threshVecFine.size(0) != 1);
  if (in3->thresh.threshVecFine.size(0) == 1) {
    loop_ub = in2.size(0);
  } else {
    loop_ub = in3->thresh.threshVecFine.size(0);
  }

  for (i = 0; i < loop_ub; i++) {
    in1[i] = (in2[i * stride_0_0] >= in3->thresh.threshVecFine[i * stride_1_0]);
  }
}

//
// Arguments    : coder::array<double, 1U> &in1
//                const coder::array<double, 1U> &in2
//                const coder::array<boolean_T, 1U> &in3
// Return Type  : void
//
static void i_binary_expand_op(coder::array<double, 1U> &in1, const coder::array<
  double, 1U> &in2, const coder::array<boolean_T, 1U> &in3)
{
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in3.size(0) == 1) {
    i = in2.size(0);
  } else {
    i = in3.size(0);
  }

  in1.set_size(i);
  stride_0_0 = (in2.size(0) != 1);
  stride_1_0 = (in3.size(0) != 1);
  if (in3.size(0) == 1) {
    loop_ub = in2.size(0);
  } else {
    loop_ub = in3.size(0);
  }

  for (i = 0; i < loop_ub; i++) {
    in1[i] = in2[i * stride_0_0] * static_cast<double>(in3[i * stride_1_0]);
  }
}

//
// Arguments    : coder::array<boolean_T, 1U> &in1
//                const coder::array<boolean_T, 1U> &in2
//                const coder::array<boolean_T, 1U> &in3
// Return Type  : void
//
static void j_binary_expand_op(coder::array<boolean_T, 1U> &in1, const coder::
  array<boolean_T, 1U> &in2, const coder::array<boolean_T, 1U> &in3)
{
  coder::array<boolean_T, 1U> b_in2;
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in3.size(0) == 1) {
    i = in2.size(0);
  } else {
    i = in3.size(0);
  }

  b_in2.set_size(i);
  stride_0_0 = (in2.size(0) != 1);
  stride_1_0 = (in3.size(0) != 1);
  if (in3.size(0) == 1) {
    loop_ub = in2.size(0);
  } else {
    loop_ub = in3.size(0);
  }

  for (i = 0; i < loop_ub; i++) {
    b_in2[i] = (in2[i * stride_0_0] && in3[i * stride_1_0]);
  }

  in1.set_size(b_in2.size(0) + 1);
  loop_ub = b_in2.size(0);
  for (i = 0; i < loop_ub; i++) {
    in1[i] = b_in2[i];
  }

  in1[b_in2.size(0)] = true;
}

//
// Arguments    : coder::array<boolean_T, 1U> &in1
//                const coder::array<boolean_T, 1U> &in2
//                const coder::array<boolean_T, 1U> &in3
// Return Type  : void
//
static void k_binary_expand_op(coder::array<boolean_T, 1U> &in1, const coder::
  array<boolean_T, 1U> &in2, const coder::array<boolean_T, 1U> &in3)
{
  coder::array<boolean_T, 1U> b_in2;
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in3.size(0) == 1) {
    i = in2.size(0);
  } else {
    i = in3.size(0);
  }

  b_in2.set_size(i);
  stride_0_0 = (in2.size(0) != 1);
  stride_1_0 = (in3.size(0) != 1);
  if (in3.size(0) == 1) {
    loop_ub = in2.size(0);
  } else {
    loop_ub = in3.size(0);
  }

  for (i = 0; i < loop_ub; i++) {
    b_in2[i] = (in2[i * stride_0_0] && in3[i * stride_1_0]);
  }

  in1.set_size(b_in2.size(0) + 1);
  in1[0] = true;
  loop_ub = b_in2.size(0);
  for (i = 0; i < loop_ub; i++) {
    in1[i + 1] = b_in2[i];
  }
}

//
// Arguments    : coder::array<boolean_T, 1U> &in1
//                const coder::array<double, 1U> &in2
//                int in3
//                const coder::array<double, 1U> &in4
// Return Type  : void
//
static void l_binary_expand_op(coder::array<boolean_T, 1U> &in1, const coder::
  array<double, 1U> &in2, int in3, const coder::array<double, 1U> &in4)
{
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in4.size(0) == 1) {
    i = in3 + 1;
  } else {
    i = in4.size(0);
  }

  in1.set_size(i);
  stride_0_0 = (in3 + 1 != 1);
  stride_1_0 = (in4.size(0) != 1);
  if (in4.size(0) == 1) {
    loop_ub = in3 + 1;
  } else {
    loop_ub = in4.size(0);
  }

  for (i = 0; i < loop_ub; i++) {
    in1[i] = (in2[i * stride_0_0] > in4[i * stride_1_0]);
  }
}

//
// Arguments    : coder::array<double, 2U> &in1
//                const coder::array<double, 2U> &in2
// Return Type  : void
//
static void minus(coder::array<double, 2U> &in1, const coder::array<double, 2U>
                  &in2)
{
  coder::array<double, 2U> b_in1;
  int aux_0_1;
  int aux_1_1;
  int b_loop_ub;
  int i;
  int i1;
  int loop_ub;
  int stride_0_0;
  int stride_0_1;
  int stride_1_0;
  int stride_1_1;
  if (in2.size(0) == 1) {
    i = in1.size(0);
  } else {
    i = in2.size(0);
  }

  if (in2.size(1) == 1) {
    i1 = in1.size(1);
  } else {
    i1 = in2.size(1);
  }

  b_in1.set_size(i, i1);
  stride_0_0 = (in1.size(0) != 1);
  stride_0_1 = (in1.size(1) != 1);
  stride_1_0 = (in2.size(0) != 1);
  stride_1_1 = (in2.size(1) != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  if (in2.size(1) == 1) {
    loop_ub = in1.size(1);
  } else {
    loop_ub = in2.size(1);
  }

  for (i = 0; i < loop_ub; i++) {
    if (in2.size(0) == 1) {
      b_loop_ub = in1.size(0);
    } else {
      b_loop_ub = in2.size(0);
    }

    for (i1 = 0; i1 < b_loop_ub; i1++) {
      b_in1[i1 + b_in1.size(0) * i] = in1[i1 * stride_0_0 + in1.size(0) *
        aux_0_1] - in2[i1 * stride_1_0 + in2.size(0) * aux_1_1];
    }

    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }

  in1.set_size(b_in1.size(0), b_in1.size(1));
  loop_ub = b_in1.size(1);
  for (i = 0; i < loop_ub; i++) {
    b_loop_ub = b_in1.size(0);
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      in1[i1 + in1.size(0) * i] = b_in1[i1 + b_in1.size(0) * i];
    }
  }
}

//
// Arguments    : coder::array<boolean_T, 1U> &in1
//                const coder::array<boolean_T, 2U> &in2
//                const coder::array<boolean_T, 2U> &in3
// Return Type  : void
//
static void n_binary_expand_op(coder::array<boolean_T, 1U> &in1, const coder::
  array<boolean_T, 2U> &in2, const coder::array<boolean_T, 2U> &in3)
{
  coder::array<boolean_T, 2U> b_in2;
  int aux_0_1;
  int aux_1_1;
  int i;
  int i1;
  int loop_ub;
  int stride_0_0;
  int stride_0_1;
  int stride_1_0;
  int stride_1_1;
  if (in3.size(0) == 1) {
    i = in2.size(0);
  } else {
    i = in3.size(0);
  }

  if (in3.size(1) == 1) {
    i1 = in2.size(1);
  } else {
    i1 = in3.size(1);
  }

  b_in2.set_size(i, i1);
  stride_0_0 = (in2.size(0) != 1);
  stride_0_1 = (in2.size(1) != 1);
  stride_1_0 = (in3.size(0) != 1);
  stride_1_1 = (in3.size(1) != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  if (in3.size(1) == 1) {
    loop_ub = in2.size(1);
  } else {
    loop_ub = in3.size(1);
  }

  for (i = 0; i < loop_ub; i++) {
    int b_loop_ub;
    if (in3.size(0) == 1) {
      b_loop_ub = in2.size(0);
    } else {
      b_loop_ub = in3.size(0);
    }

    for (i1 = 0; i1 < b_loop_ub; i1++) {
      b_in2[i1 + b_in2.size(0) * i] = ((!in2[i1 * stride_0_0 + in2.size(0) *
        aux_0_1]) || (!in3[i1 * stride_1_0 + in3.size(0) * aux_1_1]));
    }

    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }

  coder::all(b_in2, in1);
}

//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void o_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Order must be greater than or equal to zero.";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// Arguments    : coder::array<double, 2U> &in1
//                const coder::array<double, 2U> &in2
// Return Type  : void
//
static void rdivide(coder::array<double, 2U> &in1, const coder::array<double, 2U>
                    &in2)
{
  coder::array<double, 2U> b_in1;
  int aux_0_1;
  int aux_1_1;
  int b_loop_ub;
  int i;
  int i1;
  int loop_ub;
  int stride_0_0;
  int stride_0_1;
  int stride_1_0;
  int stride_1_1;
  if (in2.size(0) == 1) {
    i = in1.size(0);
  } else {
    i = in2.size(0);
  }

  if (in2.size(1) == 1) {
    i1 = in1.size(1);
  } else {
    i1 = in2.size(1);
  }

  b_in1.set_size(i, i1);
  stride_0_0 = (in1.size(0) != 1);
  stride_0_1 = (in1.size(1) != 1);
  stride_1_0 = (in2.size(0) != 1);
  stride_1_1 = (in2.size(1) != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  if (in2.size(1) == 1) {
    loop_ub = in1.size(1);
  } else {
    loop_ub = in2.size(1);
  }

  for (i = 0; i < loop_ub; i++) {
    if (in2.size(0) == 1) {
      b_loop_ub = in1.size(0);
    } else {
      b_loop_ub = in2.size(0);
    }

    for (i1 = 0; i1 < b_loop_ub; i1++) {
      b_in1[i1 + b_in1.size(0) * i] = in1[i1 * stride_0_0 + in1.size(0) *
        aux_0_1] / in2[i1 * stride_1_0 + in2.size(0) * aux_1_1];
    }

    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }

  in1.set_size(b_in1.size(0), b_in1.size(1));
  loop_ub = b_in1.size(1);
  for (i = 0; i < loop_ub; i++) {
    b_loop_ub = b_in1.size(0);
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      in1[i1 + in1.size(0) * i] = b_in1[i1 + b_in1.size(0) * i];
    }
  }
}

//
// WAVEFORM Constructs an instance of this class
// INPUTS:
//    x       1xn     Vector of samples
//    Fs      1x1     Sample frequency (Hz)
//    t_0     1x1     Time stamp of first element (s)
//  ps_pre  1x1     Pulse stats object from previous data (priori)
//    OLF     1x1     Overlap fraction as decimal (0.5 = 50%
//                    overlap)
// OUTPUTS:
//    obj             The waveform object
//             %%
//
// Arguments    : const creal32_T b_x[1000]
//                double b_Fs
//                pulsestats *b_ps_pre
//                pulsestats *iobj_0
//                wfmstft *iobj_1
// Return Type  : b_waveform *
//
b_waveform *b_waveform::init(const creal32_T b_x[1000], double b_Fs, pulsestats *
  b_ps_pre, pulsestats *iobj_0, wfmstft *iobj_1)
{
  b_waveform *obj;
  pulsestats *obj_out;
  wfmstft *val;
  coder::array<c_struct_T, 2U> c_ps_pre;
  coder::array<c_struct_T, 2U> d_ps_pre;
  coder::array<creal_T, 2U> r1;
  coder::array<creal_T, 2U> r2;
  coder::array<creal32_T, 2U> _in;
  coder::array<creal32_T, 2U> r;
  coder::array<double, 2U> f_ps_pre;
  coder::array<double, 1U> b_tmp_data;
  coder::array<double, 1U> c_tmp_data;
  coder::array<boolean_T, 2U> e_ps_pre;
  double tmp_data[400];
  int loop_ub;
  obj = this;
  r.set(nullptr, 1, 0);
  coder::internal::validator_check_size(r, _in);
  obj->x.set_size(1, _in.size(1));
  loop_ub = _in.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->x[i] = _in[i];
  }

  r1.set(nullptr, 0, 0);
  coder::internal::validator_check_size(r1, r2);
  b_tmp_data.set(&tmp_data[0], 0);
  coder::internal::validator_check_size(b_tmp_data, c_tmp_data);

  // Flatten input to row
  obj->x.set_size(1, 1000);
  for (int i{0}; i < 1000; i++) {
    obj->x[i] = b_x[i];
  }

  // Data vector
  // Elements in the data
  obj->Fs = b_Fs;

  // Sample rate
  obj->t_0 = 0.0;

  // Time stamp of first element
  // Time stamp of last element
  // This is the time when next
  // segment should start to
  // ensure sufficient overlap.
  // Will need to be updated
  // elsewhere.
  obj->ps_pre = b_ps_pre;
  obj->OLF = 0.5;

  // Overlap Fraction for STFT
  obj->K = rtNaN;

  // Unknown number of pulses.
  val = iobj_1->init();
  obj->stft = val;

  // Unknown values but set types
  // Copy over ps_
  // COPY Creates an exact copy of the pulse stats object as a separate object
  c_ps_pre.set_size(1, b_ps_pre->pl.size(1));
  loop_ub = b_ps_pre->pl.size(0) * b_ps_pre->pl.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    c_ps_pre[i] = b_ps_pre->pl[i];
  }

  d_ps_pre.set_size(b_ps_pre->clst.size(0), b_ps_pre->clst.size(1));
  loop_ub = b_ps_pre->clst.size(0) * b_ps_pre->clst.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    d_ps_pre[i] = b_ps_pre->clst[i];
  }

  e_ps_pre.set_size(b_ps_pre->cmsk.size(0), b_ps_pre->cmsk.size(1));
  loop_ub = b_ps_pre->cmsk.size(0) * b_ps_pre->cmsk.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    e_ps_pre[i] = b_ps_pre->cmsk[i];
  }

  f_ps_pre.set_size(b_ps_pre->cpki.size(0), b_ps_pre->cpki.size(1));
  loop_ub = b_ps_pre->cpki.size(0) * b_ps_pre->cpki.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    f_ps_pre[i] = b_ps_pre->cpki[i];
  }

  double g_ps_pre[2];
  double b_n_ol;
  double n_p;
  g_ps_pre[0] = b_ps_pre->tmplt[0];
  g_ps_pre[1] = b_ps_pre->tmplt[1];
  obj_out = iobj_0->b_init(b_ps_pre->t_p, b_ps_pre->t_ip, b_ps_pre->t_ipu,
    b_ps_pre->t_ipj, b_ps_pre->fp, b_ps_pre->fstart, b_ps_pre->fend, g_ps_pre,
    b_ps_pre->mode, c_ps_pre, d_ps_pre, e_ps_pre, f_ps_pre);

  // ,...
  // obj.thresh);
  obj->ps_pos = obj_out;

  // Current stats are same as previous during construction
  // obj.ps_pos = pulsestats();%TESTING FOR CODER - NEEDS TO BE REVERTED BACK TO LAST LINE
  // obj.TimeCorr = TemporalCorrelator(10, 0, 0);%Generate a temporalcorrelator object so coder knows the type of the object
  // SETPRIORIDEPENDENTVARS updates the properties in the
  // waveform that are dependent on properties in a pulsestats
  // object.
  //
  // INPUTS:
  //    obj     waveform object
  //    ps_obj  a pulse stats object
  // OUTPUTS:
  //    None (This method modifies the waveform object properties)
  //
  //             %%
  // GETPRIORIDEPENDENTVARS returns the properties in the
  // waveform that are dependent on prior pulse data estimates. It
  // depends on the waveform properties list Fs etc, as well as
  // pulse stats like t_ip, etc.
  // INPUTS:  ps_obj  1x1 pulse stats object
  // OUTPUTS:  pulse stats object
  // WHAT WAS DONE BY THIS METHOD IS NOW DONE BY A METHOD OF THE
  // PULSESTATS CLASS.
  //          function [] = update_posteriori(obj,pulselist)
  //              %UPDATE_POSTERIORI updates the posteriori pulse statistics of
  //              %this waveform object using the new pulse list (input) and the
  //              %apriori stats. The pulse contained in the waveform's ps_pos
  //              %property is not used directly so that the caller can decide
  //              %which pulses on which to focus the posteriori.
  //
  //              t_found    = [pulselist(:).t_0]';
  //              freq_found = mean([pulselist(:).fp],'omitnan');
  //
  //              %Create a vector of bandwidths from the pulselist
  //              bw_found = 2*(mean([pulselist.fend],'omitnan')-mean([pulselist.fstart],'omitnan'));
  //              if isempty(bw_found)
  //                  bw_found = 100;
  //                  if coder.target('MATLAB')
  //                      warning(['UAV-R: No bandwidth could be calculated ',...
  //                           'from the start and stop frequencies of the ',...
  //                           'identified pulses. A bandwidth of 100 Hz ',...
  //                           'will be used for continued informed search.'])
  //                  end
  //              end
  //
  //              %Here is where we update the stats. These methods of updates
  //              %could be improved in the future.
  //              %obj.ps_pre.t_p; %tp doesn't change. We assume it is stationary
  //
  //              if numel(pulselist)==1% Happens if K=1
  //                  %We only have one pulse to reference, so we need to check
  //                  %the prior pulse too.
  //                  if ~isempty(obj.ps_pre.pl) && ~isnan(obj.ps_pre.pl(end).t_0)
  //                      recent_tip = pulselist.t_0-obj.ps_pre.pl(end).t_0;
  //                      %There could be a case where the last segment and this
  //                      %segement identified the same pulse. In this case
  //                      %recent_tip will be very small. In this case, we just
  //                      %say we learned nothing about t_ip in this segment.
  //                      if recent_tip < obj.ps_pre.t_ipu + obj.ps_pre.t_ipJ
  //                          recent_tip = NaN;
  //                      end
  //                  else
  //                      %No new information because we don't know the last
  //                      %pulse time
  //                      recent_tip = NaN;
  //                  end
  //              else
  //                  recent_tip = diff(t_found);
  //              end
  //              %Do a check here to make sure the new tip isn't a huge change.
  //              %This could potentially happen if we are in the K = 1 case and
  //              %the block getting processed contained two pulses, with the
  //              %latter pulse getting identified/detected. The lines above
  //              %would look back to the last identified pulse and it might be
  //              %2*tip back in time, producing a very large recenttip values.
  //              %If something like this happens, we ignore it so it doesn't
  //              %affect our new tip estimates.
  //              if recent_tip > 1.5*obj.ps_pre.t_ip & recent_tip < 0.5*obj.ps_pre.t_ip
  //                  recent_tip = NaN;
  //              end
  //
  //              %Only update time parameters if we are in tracking mode. If we
  //              %aren't, we may have identified somethign that isn't a pulse
  //              if strcmp(obj.ps_pos.mode,'T') || strcmp(obj.ps_pre.mode,'T')
  //                  obj.ps_pos.t_ip  = mean([recent_tip;obj.ps_pre.t_ip],'omitnan');
  //                  obj.ps_pos.t_ipu = obj.ps_pre.t_ipu; %Don't update this because it can get too narrow.%mean([3*std(diff(t_found));obj.ps_pre.t_ipu]);
  //                  obj.ps_pos.t_ipj = obj.ps_pre.t_ipj;
  //              end
  //              fp_pos           = freq_found;%nanmean([freq_found;obj.ps_pre.fp]);%Previous fc may be nan if unknown
  //              obj.ps_pos.fp    = fp_pos;
  //              obj.ps_pos.fstart = fp_pos-bw_found/2;
  //              obj.ps_pos.fend   = fp_pos+bw_found/2;
  //
  //              obj.ps_pos.psdHist = obj.stft.psd
  //          end
  n_p = b_ps_pre->t_p * obj->Fs;
  n_p = std::ceil(n_p);

  // Samples per pulse
  // Number of elements in STFT window
  b_n_ol = obj->OLF * n_p;

  // Number of elements overlap in STFT window
  // Number of elements in each step of STFT
  // Time of each step of STFT
  // Samples per pulse
  obj->n_w = n_p;

  // Number of elements in STFT window
  obj->n_ol = std::floor(b_n_ol);

  // Number of elements overlap in STFT window
  // Number of elements in each step of STFT
  // Time of each step of STFT
  // Samples of interpulse duration
  // Baseline interpulse duration in units of STFT windows
  // Interpulse duration deviation from baselines in units of STFT windows
  // Amount of deviation from the PRI means to search
  //              if K ~= 1
  //                  samplesforKpulses = n_ws*(K*(N+M)-2*M)+n_ol;
  //              else
  //                  samplesforKpulses = n_ws*(N+M+J+1)+n_ol;
  //              end
  // See 2022-07-11 for updates to samples def
  // obj.t_nextsegstart  = obj.t_0+(samplesforKpulses)/obj.Fs; %Don't need the overlap here since the next segment starts at samplesforKpulses+n_ol-n_ol from current sample
  // Don't need the overlap here since the next segment starts at samplesforKpulses+n_ol-n_ol from current sample
  //              if isempty(obj.TimeCorr)
  //                  obj.TimeCorr = TemporalCorrelator(N, M, J);
  //              else
  //                  obj.TimeCorr.update(N, M, J);
  //              end
  return obj;
}

//
// WAVEFORM Constructs an instance of this class
// INPUTS:
//    x       1xn     Vector of samples
//    Fs      1x1     Sample frequency (Hz)
//    t_0     1x1     Time stamp of first element (s)
//  ps_pre  1x1     Pulse stats object from previous data (priori)
//    OLF     1x1     Overlap fraction as decimal (0.5 = 50%
//                    overlap)
// OUTPUTS:
//    obj             The waveform object
//             %%
//
// Arguments    : const coder::array<creal32_T, 1U> &b_x
//                double b_Fs
//                double b_t_0
//                pulsestats *b_ps_pre
//                const threshold *b_thresh
//                pulsestats *iobj_0
//                wfmstft *iobj_1
// Return Type  : waveform *
//
waveform *waveform::init(const coder::array<creal32_T, 1U> &b_x, double b_Fs,
  double b_t_0, pulsestats *b_ps_pre, const threshold *b_thresh, pulsestats
  *iobj_0, wfmstft *iobj_1)
{
  pulsestats *obj_out;
  waveform *obj;
  wfmstft *d_val;
  coder::array<c_struct_T, 2U> c_ps_pre;
  coder::array<c_struct_T, 2U> d_ps_pre;
  coder::array<creal_T, 2U> b_val;
  coder::array<creal_T, 2U> r1;
  coder::array<creal32_T, 2U> c_x;
  coder::array<creal32_T, 2U> r;
  coder::array<creal32_T, 2U> val;
  coder::array<double, 2U> f_ps_pre;
  coder::array<double, 1U> b_tmp_data;
  coder::array<double, 1U> c_val;
  coder::array<boolean_T, 2U> e_ps_pre;
  double tmp_data[400];
  int loop_ub;
  int u0;
  obj = this;
  r.set(nullptr, 1, 0);
  coder::internal::validator_check_size(r, val);
  obj->x.set_size(1, val.size(1));
  loop_ub = val.size(1);
  for (u0 = 0; u0 < loop_ub; u0++) {
    obj->x[u0] = val[u0];
  }

  r1.set(nullptr, 0, 0);
  coder::internal::validator_check_size(r1, b_val);
  obj->W.set_size(b_val.size(0), b_val.size(1));
  loop_ub = b_val.size(0) * b_val.size(1);
  for (u0 = 0; u0 < loop_ub; u0++) {
    obj->W[u0] = b_val[u0];
  }

  b_tmp_data.set(&tmp_data[0], 0);
  coder::internal::validator_check_size(b_tmp_data, c_val);
  obj->Wf.set_size(c_val.size(0));
  loop_ub = c_val.size(0);
  for (u0 = 0; u0 < loop_ub; u0++) {
    obj->Wf[u0] = c_val[u0];
  }

  loop_ub = b_x.size(0);
  if (b_x.size(0) < 1) {
    loop_ub = 1;
  }

  u0 = b_x.size(0);
  if (u0 >= loop_ub) {
    loop_ub = u0;
  }

  if (b_x.size(0) > loop_ub) {
    l_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
  }

  // Flatten input to row
  loop_ub = b_x.size(0);
  c_x = b_x.reshape(1, loop_ub);
  coder::internal::validator_check_size(c_x, val);
  obj->x.set_size(1, val.size(1));
  loop_ub = val.size(1);
  for (u0 = 0; u0 < loop_ub; u0++) {
    obj->x[u0] = val[u0];
  }

  // Data vector
  obj->l = b_x.size(0);

  // Elements in the data
  obj->Fs = b_Fs;

  // Sample rate
  obj->t_0 = b_t_0;

  // Time stamp of first element
  obj->t_f = b_t_0 + (static_cast<double>(b_x.size(0)) - 1.0) / b_Fs;

  // Time stamp of last element
  obj->t_nextsegstart[0] = b_t_0;
  obj->t_nextsegstart[1] = b_t_0;

  // This is the time when next
  // segment should start to
  // ensure sufficient overlap.
  // Will need to be updated
  // elsewhere.
  obj->ps_pre = b_ps_pre;
  obj->OLF = 0.5;

  // Overlap Fraction for STFT
  obj->K = rtNaN;

  // Unknown number of pulses.
  d_val = iobj_1->init();
  obj->stft = d_val;

  // Unknown values but set types
  obj->W.set_size(0, 0);
  obj->Wf.set_size(0);

  // Copy over ps_
  // COPY Creates an exact copy of the pulse stats object as a separate object
  c_ps_pre.set_size(1, b_ps_pre->pl.size(1));
  loop_ub = b_ps_pre->pl.size(0) * b_ps_pre->pl.size(1) - 1;
  for (u0 = 0; u0 <= loop_ub; u0++) {
    c_ps_pre[u0] = b_ps_pre->pl[u0];
  }

  d_ps_pre.set_size(b_ps_pre->clst.size(0), b_ps_pre->clst.size(1));
  loop_ub = b_ps_pre->clst.size(0) * b_ps_pre->clst.size(1) - 1;
  for (u0 = 0; u0 <= loop_ub; u0++) {
    d_ps_pre[u0] = b_ps_pre->clst[u0];
  }

  e_ps_pre.set_size(b_ps_pre->cmsk.size(0), b_ps_pre->cmsk.size(1));
  loop_ub = b_ps_pre->cmsk.size(0) * b_ps_pre->cmsk.size(1) - 1;
  for (u0 = 0; u0 <= loop_ub; u0++) {
    e_ps_pre[u0] = b_ps_pre->cmsk[u0];
  }

  f_ps_pre.set_size(b_ps_pre->cpki.size(0), b_ps_pre->cpki.size(1));
  loop_ub = b_ps_pre->cpki.size(0) * b_ps_pre->cpki.size(1) - 1;
  for (u0 = 0; u0 <= loop_ub; u0++) {
    f_ps_pre[u0] = b_ps_pre->cpki[u0];
  }

  double g_ps_pre[2];
  g_ps_pre[0] = b_ps_pre->tmplt[0];
  g_ps_pre[1] = b_ps_pre->tmplt[1];
  obj_out = iobj_0->b_init(b_ps_pre->t_p, b_ps_pre->t_ip, b_ps_pre->t_ipu,
    b_ps_pre->t_ipj, b_ps_pre->fp, b_ps_pre->fstart, b_ps_pre->fend, g_ps_pre,
    b_ps_pre->mode, c_ps_pre, d_ps_pre, e_ps_pre, f_ps_pre);

  // ,...
  // obj.thresh);
  obj->ps_pos = obj_out;

  // Current stats are same as previous during construction
  // obj.ps_pos = pulsestats();%TESTING FOR CODER - NEEDS TO BE REVERTED BACK TO LAST LINE
  // obj.TimeCorr = TemporalCorrelator(10, 0, 0);%Generate a temporalcorrelator object so coder knows the type of the object
  obj->setprioridependentprops(b_ps_pre);
  obj->thresh = *b_thresh;
  return obj;
}

//
// WAVEFORM Constructs an instance of this class
// INPUTS:
//    x       1xn     Vector of samples
//    Fs      1x1     Sample frequency (Hz)
//    t_0     1x1     Time stamp of first element (s)
//  ps_pre  1x1     Pulse stats object from previous data (priori)
//    OLF     1x1     Overlap fraction as decimal (0.5 = 50%
//                    overlap)
// OUTPUTS:
//    obj             The waveform object
//             %%
//
// Arguments    : const creal32_T b_x[1000]
//                double b_Fs
//                pulsestats *b_ps_pre
//                const threshold *b_thresh
// Return Type  : waveform *
//
waveform *waveform::init(const creal32_T b_x[1000], double b_Fs, pulsestats
  *b_ps_pre, const threshold *b_thresh)
{
  pulsestats *obj_out;
  waveform *b_obj;
  waveform *obj;
  wfmstft *d_val;
  coder::array<c_struct_T, 2U> c_ps_pre;
  coder::array<c_struct_T, 2U> d_ps_pre;
  coder::array<creal_T, 2U> b_val;
  coder::array<creal_T, 2U> r1;
  coder::array<creal32_T, 2U> r;
  coder::array<creal32_T, 2U> val;
  coder::array<double, 2U> f_ps_pre;
  coder::array<double, 1U> b_tmp_data;
  coder::array<double, 1U> c_val;
  coder::array<boolean_T, 2U> e_ps_pre;
  double tmp_data[400];
  int loop_ub;
  obj = this;
  r.set(nullptr, 1, 0);
  coder::internal::validator_check_size(r, val);
  obj->x.set_size(1, val.size(1));
  loop_ub = val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->x[i] = val[i];
  }

  r1.set(nullptr, 0, 0);
  coder::internal::validator_check_size(r1, b_val);
  obj->W.set_size(b_val.size(0), b_val.size(1));
  loop_ub = b_val.size(0) * b_val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->W[i] = b_val[i];
  }

  b_tmp_data.set(&tmp_data[0], 0);
  coder::internal::validator_check_size(b_tmp_data, c_val);
  obj->Wf.set_size(c_val.size(0));
  loop_ub = c_val.size(0);
  for (int i{0}; i < loop_ub; i++) {
    obj->Wf[i] = c_val[i];
  }

  // Flatten input to row
  obj->x.set_size(1, 1000);
  for (int i{0}; i < 1000; i++) {
    obj->x[i] = b_x[i];
  }

  // Data vector
  obj->l = 1000.0;

  // Elements in the data
  obj->Fs = b_Fs;

  // Sample rate
  obj->t_0 = 0.0;

  // Time stamp of first element
  obj->t_f = 999.0 / b_Fs;

  // Time stamp of last element
  obj->t_nextsegstart[0] = 0.0;
  obj->t_nextsegstart[1] = 0.0;

  // This is the time when next
  // segment should start to
  // ensure sufficient overlap.
  // Will need to be updated
  // elsewhere.
  obj->ps_pre = b_ps_pre;
  obj->OLF = 0.5;

  // Overlap Fraction for STFT
  obj->K = rtNaN;

  // Unknown number of pulses.
  b_obj = obj;
  d_val = obj->_pobj1.init();
  b_obj->stft = d_val;

  // Unknown values but set types
  obj->W.set_size(0, 0);
  obj->Wf.set_size(0);

  // Copy over ps_
  // COPY Creates an exact copy of the pulse stats object as a separate object
  c_ps_pre.set_size(1, b_ps_pre->pl.size(1));
  loop_ub = b_ps_pre->pl.size(0) * b_ps_pre->pl.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    c_ps_pre[i] = b_ps_pre->pl[i];
  }

  d_ps_pre.set_size(b_ps_pre->clst.size(0), b_ps_pre->clst.size(1));
  loop_ub = b_ps_pre->clst.size(0) * b_ps_pre->clst.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    d_ps_pre[i] = b_ps_pre->clst[i];
  }

  e_ps_pre.set_size(b_ps_pre->cmsk.size(0), b_ps_pre->cmsk.size(1));
  loop_ub = b_ps_pre->cmsk.size(0) * b_ps_pre->cmsk.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    e_ps_pre[i] = b_ps_pre->cmsk[i];
  }

  f_ps_pre.set_size(b_ps_pre->cpki.size(0), b_ps_pre->cpki.size(1));
  loop_ub = b_ps_pre->cpki.size(0) * b_ps_pre->cpki.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    f_ps_pre[i] = b_ps_pre->cpki[i];
  }

  double g_ps_pre[2];
  g_ps_pre[0] = b_ps_pre->tmplt[0];
  g_ps_pre[1] = b_ps_pre->tmplt[1];
  obj_out = obj->_pobj0.b_init(b_ps_pre->t_p, b_ps_pre->t_ip, b_ps_pre->t_ipu,
    b_ps_pre->t_ipj, b_ps_pre->fp, b_ps_pre->fstart, b_ps_pre->fend, g_ps_pre,
    b_ps_pre->mode, c_ps_pre, d_ps_pre, e_ps_pre, f_ps_pre);

  // ,...
  // obj.thresh);
  obj->ps_pos = obj_out;

  // Current stats are same as previous during construction
  // obj.ps_pos = pulsestats();%TESTING FOR CODER - NEEDS TO BE REVERTED BACK TO LAST LINE
  // obj.TimeCorr = TemporalCorrelator(10, 0, 0);%Generate a temporalcorrelator object so coder knows the type of the object
  obj->setprioridependentprops(b_ps_pre);
  obj->thresh = *b_thresh;
  return obj;
}

//
// PROCESS is a method that runs the pulse detection algorithm on
// a waveform object.
//
// This method is is intended to be run on a waveform
// segment that is short enought to contain at most K+1 pulses,
// but at least K pulses, where K is the number of pulses to be
// summed. Input paramets allow for the selection of search mode,
// the focus mode, and the selection mode. The search mode
// ('mode') is eithr 'discovery', 'confirmation', or 'tracking'
// and selection of each of these affects how priori information
// is used to reduce the frequency or time scope of the pulse
// search. This also affects how the resulting ps_pos property of
// the waveform is set. The false alarm probabilty is used along
// with the decision table in order to determine the thresholds
// used for the decision making on pulse detection.
//
// Arguments    : char mode
//                const coder::array<double, 2U> &excluded_freq_bands
// Return Type  : void
//
void waveform::process(char mode, const coder::array<double, 2U>
  &excluded_freq_bands)
{
  static rtBoundsCheckInfo ac_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1714,                              // lineNo
    21,                                // colNo
    "obj.ps_pos.clst(tick)",           // aName
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo eb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1579,                              // lineNo
    56,                                // colNo
    "obj.ps_pre.pl",                   // aName
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo fb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1584,                              // lineNo
    56,                                // colNo
    "obj.ps_pre.pl",                   // aName
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo gb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1848,                              // lineNo
    58,                                // colNo
    "pk_ind",                          // aName
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo hb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1848,                              // lineNo
    51,                                // colNo
    "candidatelist",                   // aName
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ib_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1865,                              // lineNo
    39,                                // colNo
    "obj.ps_pos.pl(ip)",               // aName
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo jb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1895,                              // lineNo
    35,                                // colNo
    "obj.ps_pos.pl(tick)",             // aName
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo kb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1898,                              // lineNo
    37,                                // colNo
    "obj.ps_pos.clst(tick)",           // aName
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo lb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1898,                              // lineNo
    21,                                // colNo
    "obj.ps_pos.clst(tick)",           // aName
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo mb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1735,                              // lineNo
    58,                                // colNo
    "pk_ind",                          // aName
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo nb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1735,                              // lineNo
    51,                                // colNo
    "candidatelist",                   // aName
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ob_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1750,                              // lineNo
    42,                                // colNo
    "obj.ps_pre.pl",                   // aName
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo pb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1800,                              // lineNo
    61,                                // colNo
    "conflog",                         // aName
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo qb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1800,                              // lineNo
    39,                                // colNo
    "obj.ps_pos.pl(ip)",               // aName
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo rb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1825,                              // lineNo
    35,                                // colNo
    "obj.ps_pos.pl(tick)",             // aName
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo sb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1828,                              // lineNo
    37,                                // colNo
    "obj.ps_pos.clst(tick)",           // aName
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo tb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1828,                              // lineNo
    21,                                // colNo
    "obj.ps_pos.clst(tick)",           // aName
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ub_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1665,                              // lineNo
    58,                                // colNo
    "pk_ind",                          // aName
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo vb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1665,                              // lineNo
    51,                                // colNo
    "candidatelist",                   // aName
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo wb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1684,                              // lineNo
    39,                                // colNo
    "obj.ps_pos.pl(ip)",               // aName
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo xb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1711,                              // lineNo
    35,                                // colNo
    "obj.ps_pos.pl(tick)",             // aName
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo yb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    1714,                              // lineNo
    37,                                // colNo
    "obj.ps_pos.clst(tick)",           // aName
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    0                                  // checkKind
  };

  static rtDoubleCheckInfo ab_emlrtDCI{ 1758,// lineNo
    98,                                // colNo
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    4                                  // checkKind
  };

  static rtDoubleCheckInfo bb_emlrtDCI{ 1758,// lineNo
    98,                                // colNo
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo cb_emlrtDCI{ 1758,// lineNo
    91,                                // colNo
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    4                                  // checkKind
  };

  static rtDoubleCheckInfo db_emlrtDCI{ 1758,// lineNo
    91,                                // colNo
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo eb_emlrtDCI{ 1761,// lineNo
    96,                                // colNo
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    4                                  // checkKind
  };

  static rtDoubleCheckInfo fb_emlrtDCI{ 1761,// lineNo
    96,                                // colNo
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo gb_emlrtDCI{ 1761,// lineNo
    89,                                // colNo
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    4                                  // checkKind
  };

  static rtDoubleCheckInfo hb_emlrtDCI{ 1761,// lineNo
    89,                                // colNo
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo ib_emlrtDCI{ 1762,// lineNo
    96,                                // colNo
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    4                                  // checkKind
  };

  static rtDoubleCheckInfo jb_emlrtDCI{ 1762,// lineNo
    96,                                // colNo
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo kb_emlrtDCI{ 1762,// lineNo
    89,                                // colNo
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    4                                  // checkKind
  };

  static rtDoubleCheckInfo lb_emlrtDCI{ 1762,// lineNo
    89,                                // colNo
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo mb_emlrtDCI{ 1665,// lineNo
    51,                                // colNo
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo t_emlrtDCI{ 1848,// lineNo
    51,                                // colNo
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo u_emlrtDCI{ 1735,// lineNo
    51,                                // colNo
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo v_emlrtDCI{ 1757,// lineNo
    98,                                // colNo
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    4                                  // checkKind
  };

  static rtDoubleCheckInfo w_emlrtDCI{ 1757,// lineNo
    98,                                // colNo
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo x_emlrtDCI{ 1757,// lineNo
    91,                                // colNo
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    4                                  // checkKind
  };

  static rtDoubleCheckInfo y_emlrtDCI{ 1757,// lineNo
    91,                                // colNo
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m",// pName
    1                                  // checkKind
  };

  static rtEqualityCheckInfo g_emlrtECI{ 2,// nDims
    1757,                              // lineNo
    54,                                // colNo
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo h_emlrtECI{ 2,// nDims
    1758,                              // lineNo
    54,                                // colNo
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo i_emlrtECI{ 2,// nDims
    1769,                              // lineNo
    35,                                // colNo
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo j_emlrtECI{ 2,// nDims
    1771,                              // lineNo
    35,                                // colNo
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo k_emlrtECI{ 2,// nDims
    1775,                              // lineNo
    34,                                // colNo
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo l_emlrtECI{ 2,// nDims
    1776,                              // lineNo
    34,                                // colNo
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo m_emlrtECI{ 2,// nDims
    1779,                              // lineNo
    31,                                // colNo
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo n_emlrtECI{ 2,// nDims
    1761,                              // lineNo
    54,                                // colNo
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static rtEqualityCheckInfo o_emlrtECI{ 2,// nDims
    1762,                              // lineNo
    54,                                // colNo
    "waveform/process",                // fName
    "H:\\repos\\uavrt_detection\\waveform.m"// pName
  };

  static const char b_cv[8]{ 'i', 'n', 'f', 'o', 'r', 'm', 'e', 'd' };

  static const char b_cv3[7]{ 'c', 'o', 'n', 'f', 'i', 'r', 'm' };

  static const char b_cv2[6]{ 's', 'e', 'a', 'r', 'c', 'h' };

  static const char b_cv1[5]{ 'n', 'a', 'i', 'v', 'e' };

  static const char b_cv4[5]{ 't', 'r', 'a', 'c', 'k' };

  pulsestats *obj;
  coder::array<c_struct_T, 2U> b_candidatelist;
  coder::array<c_struct_T, 2U> b_val;
  coder::array<c_struct_T, 2U> c_candidatelist;
  coder::array<c_struct_T, 2U> candidatelist;
  coder::array<c_struct_T, 1U> b_obj;
  coder::array<double, 2U> _in;
  coder::array<double, 2U> b;
  coder::array<double, 2U> pulseendtimes_withuncert;
  coder::array<double, 2U> pulsestarttimes_withuncert;
  coder::array<double, 2U> varargin_1;
  coder::array<double, 1U> pk_ind;
  coder::array<boolean_T, 2U> b_msk;
  coder::array<boolean_T, 2U> freqInBand;
  coder::array<boolean_T, 2U> maxstartlog;
  coder::array<boolean_T, 2U> minstartlog;
  coder::array<boolean_T, 2U> msk;
  coder::array<boolean_T, 2U> r1;
  coder::array<boolean_T, 1U> r;
  c_struct_T val;
  double b_x;
  double tip;
  double tipj;
  double tipu;
  double tref;
  int b_input_sizes[2];
  int c_input_sizes[2];
  int d_input_sizes[2];
  int e_input_sizes[2];
  int f_input_sizes[2];
  int freq_search_type_size[2];
  int input_sizes[2];
  int runmode_size[2];
  int time_search_type_size[2];
  int b_n;
  int i;
  int n;
  char freq_search_type_data[8];
  char time_search_type_data[8];
  char runmode_data[7];
  boolean_T have_priori_freq_band;
  boolean_T have_priori_time;

  // Mode description:
  // Processing can be done in either discovery 'D', confirmation
  // 'C', or tracking 'T' modes. The selection of these modes
  // affects how time and frequency focusing is used to improve
  // processing time. In discovery mode is used for intial
  // detection when little is know about where pulses might exist
  // in time or frequeny. Confirmation is similar to discovery, but
  // is used after an initial detection to confirm that the
  // subsequent pulses exists where they should based on
  // forecasting from a previous detection. After pulses are
  // confirmed, the mode can be set to tracking which reduces the
  // frequency and time search space to improve processing speed.
  //
  //    Discovey mode:      'D'
  //        This mode uses no priori information and looks at the
  //        widest possible time bounds for pulses. If there is
  //        no priori frequency information in the ps_pre property
  //        or the focus mode is set to 'open', discovery mode
  //        will search across all frequencies. Otherwise it
  //        will search over all frequencies. If it detects pulses
  //        in the dataset that exceed the decision threshold, the
  //        posterior pulsestats object will be set to a mode of
  //        'C' so that the next segment processed will run in
  //        confirmation mode. If a detection or set of detections
  //        are made, the 'selection_mode' input will dictate how
  //        the posterior pulsestat property is set.
  //
  //    Confirmation mode:  'C'
  //        This mode is similar to discovery mode, but after a
  //        detection is made, it will compare the spectral and
  //        temporal location of the detected pulses to determine
  //        if the pulses align with what could be predicted from
  //        the pulses listed in the priori information of the
  //        waveform getting processed. If these pulses are
  //        confirmed, then the posteriori pulsestats mode property
  //        is set to 'T' so that subsequent segments can move to
  //        tracking mode. If pulses are detected but not where
  //        they should have been based on predictions from the
  //        priori, then the posteriori mode is set back to 'D'.
  //
  //    Tracking mode:      'T'
  //        Tracking mode uses priori pulsestats information in
  //        order to reduce the time and/or frequency space used
  //        for detection. The significantly speed processing
  //        speeds, but can miss detections if pulses move in time
  //        from where they should be based on a previous segment's
  //        detection. If using tracking mode and pulses aren't
  //        detected (scores don't meet the decision threhold), the
  //        posteriori pulsestats mode is set back to 'D'.
  //
  // INPUTS:
  //    mode    The search mode used. Must be string 'D' for
  //            discovery, 'C' for confirmation, or 'T' for
  //            tracking.
  //    focus_mode  How the algorithm decided whether or not to
  //            focus on a particular pulse. This mode can be set
  //            to 'open' wherein no focusing is done and the
  //            processing always proceeds along in discovery mode
  //            without narrowing the frequency or time span of the
  //            search. If this mode is set to 'focus', the method
  //            will allow for down selection of detected pulses
  //            for subsequent processing. The method of this
  //            downselection is determined by the 'selection_mode'
  //            input.
  //    selection_mode  How the algorithm narrows the scope for
  //            subsequent segment processing. This input is
  //            used when in 'discovery' mode. If pulses are
  //            detected, the focus mode will dictate which
  //            pulse is focused on for subsequent data
  //            segments. Focus mode can be set to 'most' to
  //            focus on the most powerful detecte pulse or
  //            'least' to focus on the least powerful detected
  //            pulse. See DETECT.M for more
  //            information on these focus modes.
  //    zetas   A vector of fractions of the DFT frequency bin
  //            width for which to compute and include in the
  //            spectral weighting matrix output. If no interbin
  //            shifting is desired, enter 0. Range of inputs
  //            [0,1). See WEIGHTINGMATRIX.m for more information
  //            on this vector.
  //    PF      A numeric probability of false alarm for decision
  //            threshold determination. Value range of PF must be
  //            within the pf property vector of the decision_table
  //            input.
  //    decision_table  A structure with two properties - 'pf' and
  //            'values'. The pf property is a vector of false alarm
  //            probabilities in decimal form (not percentage). The
  //            values property is vector of the same size as pf
  //            with the decision thresholds for the corresponding
  //            false alarm probability.
  //    excluded_freq_bands   nx2    matrix of bands of
  //                                 frequencies to exclude in
  //                                 the search. This is useful if
  //                                 there has already been a tag
  //                                 found and you want to exclude
  //                                 that band when looking for
  //                                 other frequencies. The lower
  //                                 frequecie of the band should
  //                                 be in the first column and
  //                                 the upper should be in the
  //                                 second. This is only used in
  //                                 the naive frequency search
  //                                 mode. Leave empty [] if no
  //                                 exclusion zones are
  //                                 necessary.
  //
  // OUTPUTS:
  //    None. This method updates the ps_pos property of the
  //    waveform object 'obj'.
  //
  //             %%
  //
  //         %% CHECK MODE ENTRANCE REQUIREMENTS
  // Determine if there is sufficient priori for the operation of each
  // mode. Check to see if they have entries and if they are finite (not Nan or Inf).
  // We just catch that and then set the have_priori flag to false.
  b_x = ps_pre->fstart;
  tref = ps_pre->fend;
  have_priori_freq_band = ((!std::isinf(b_x)) && (!std::isnan(b_x)) && ((!std::
    isinf(tref)) && (!std::isnan(tref))));
  n = ps_pre->pl.size(1);
  i = ps_pre->pl.size(1);
  if ((i < 1) || (i > n)) {
    rtDynamicBoundsError(i, 1, n, &eb_emlrtBCI);
  }

  n = ps_pre->pl.size(1);
  i = ps_pre->pl.size(1);
  if ((i < 1) || (i > n)) {
    rtDynamicBoundsError(i, 1, n, &fb_emlrtBCI);
  }

  b_x = ps_pre->pl[i - 1].t_0;
  tref = ps_pre->t_p;
  tip = ps_pre->t_ip;
  tipu = ps_pre->t_ipu;
  tipj = ps_pre->t_ipj;
  have_priori_time = ((!std::isinf(b_x)) && (!std::isnan(b_x)) && ((!std::isinf
    (tref)) && (!std::isnan(tref))) && ((!std::isinf(tip)) && (!std::isnan(tip)))
                      && ((!std::isinf(tipu)) && (!std::isnan(tipu))) && ((!std::
    isinf(tipj)) && (!std::isnan(tipj))));

  // Enforce entry requirements on the modes so we don't get errors in
  // the 'C' and 'T' modes, as they required priori freq and time info.
  if ((mode == 'T') && (!have_priori_time) && (!have_priori_freq_band)) {
    // if strcmp(mode,'C'); attemptedmodestring = 'confirmation';end
    mode = 'D';
  }

  if ((mode == 'C') && (!have_priori_time)) {
    mode = 'D';
  }

  if ((mode == 'I') && (!have_priori_freq_band)) {
    mode = 'D';
  }

  if (mode == 'D') {
    b_n = 0;
  } else if (mode == 'I') {
    b_n = 1;
  } else if (mode == 'C') {
    b_n = 2;
  } else if (mode == 'T') {
    b_n = 3;
  } else {
    b_n = -1;
  }

  switch (b_n) {
   case 0:
    {
      freq_search_type_size[0] = 1;
      freq_search_type_size[1] = 5;
      time_search_type_size[0] = 1;
      time_search_type_size[1] = 5;
      for (n = 0; n < 5; n++) {
        char c;
        c = b_cv1[n];
        freq_search_type_data[n] = c;
        time_search_type_data[n] = c;
      }

      runmode_size[0] = 1;
      runmode_size[1] = 6;
      for (n = 0; n < 6; n++) {
        runmode_data[n] = b_cv2[n];
      }
    }
    break;

   case 1:
    freq_search_type_size[0] = 1;
    freq_search_type_size[1] = 8;
    for (n = 0; n < 8; n++) {
      freq_search_type_data[n] = b_cv[n];
    }

    time_search_type_size[0] = 1;
    time_search_type_size[1] = 5;
    for (n = 0; n < 5; n++) {
      time_search_type_data[n] = b_cv1[n];
    }

    runmode_size[0] = 1;
    runmode_size[1] = 6;
    for (n = 0; n < 6; n++) {
      runmode_data[n] = b_cv2[n];
    }
    break;

   case 2:
    {
      freq_search_type_size[0] = 1;
      freq_search_type_size[1] = 5;
      time_search_type_size[0] = 1;
      time_search_type_size[1] = 5;
      for (n = 0; n < 5; n++) {
        char c;
        c = b_cv1[n];
        freq_search_type_data[n] = c;
        time_search_type_data[n] = c;
      }

      runmode_size[0] = 1;
      runmode_size[1] = 7;
      for (n = 0; n < 7; n++) {
        runmode_data[n] = b_cv3[n];
      }
    }
    break;

   case 3:
    {
      freq_search_type_size[0] = 1;
      freq_search_type_size[1] = 8;
      time_search_type_size[0] = 1;
      time_search_type_size[1] = 8;
      for (n = 0; n < 8; n++) {
        char c;
        c = b_cv[n];
        freq_search_type_data[n] = c;
        time_search_type_data[n] = c;
      }

      runmode_size[0] = 1;
      runmode_size[1] = 5;
      for (n = 0; n < 5; n++) {
        runmode_data[n] = b_cv4[n];
      }
    }
    break;

   default:
    {
      freq_search_type_size[0] = 1;
      freq_search_type_size[1] = 5;
      time_search_type_size[0] = 1;
      time_search_type_size[1] = 5;
      for (n = 0; n < 5; n++) {
        char c;
        c = b_cv1[n];
        freq_search_type_data[n] = c;
        time_search_type_data[n] = c;
      }

      runmode_size[0] = 1;
      runmode_size[1] = 6;
      for (n = 0; n < 6; n++) {
        runmode_data[n] = b_cv2[n];
      }
    }
    break;
  }

  if (coder::internal::b_strcmp(runmode_data, runmode_size)) {
    b_n = 0;
  } else if (coder::internal::c_strcmp(runmode_data, runmode_size)) {
    b_n = 1;
  } else if (coder::internal::d_strcmp(runmode_data, runmode_size)) {
    b_n = 2;
  } else {
    b_n = -1;
  }

  switch (b_n) {
   case 0:
    {
      coder::array<boolean_T, 1U> b_minstartlog;

      //             %% SEARCH RUN MODE
      // Find all the potential pulses in the dataset
      findpulse(time_search_type_data, time_search_type_size,
                freq_search_type_data, freq_search_type_size,
                excluded_freq_bands, candidatelist, msk, pk_ind);
      b_n = candidatelist.size(0) * candidatelist.size(1);
      if (b_n == 0) {
        n = 0;
      } else {
        n = b_n;
      }

      minstartlog.set_size(1, n);
      if (b_n > 2147483646) {
        coder::check_forloop_overflow_error();
      }

      for (int b_i{0}; b_i < b_n; b_i++) {
        minstartlog[b_i] = candidatelist[b_i].det_dec;
      }

      if (minstartlog.size(1) != 0) {
        b_n = minstartlog.size(1);
      } else {
        b_n = 0;
      }

      b_minstartlog = minstartlog.reshape(b_n);
      have_priori_freq_band = coder::internal::allOrAny_anonFcn1(b_minstartlog);
      if (have_priori_freq_band) {
        r.set_size(pk_ind.size(0));
        b_n = pk_ind.size(0);
        for (n = 0; n < b_n; n++) {
          r[n] = std::isnan(pk_ind[n]);
        }

        coder::internal::allOrAny_anonFcn1(r);
      } else {
        //  Determine which peak to focus depending on the selection mode
        //  Select a peak if we found had at least one detection
      }

      r.set_size(pk_ind.size(0));
      b_n = pk_ind.size(0);
      for (n = 0; n < b_n; n++) {
        r[n] = std::isnan(pk_ind[n]);
      }

      b_n = r.size(0);
      for (n = 0; n < b_n; n++) {
        r[n] = !r[n];
      }

      if (coder::internal::ifWhileCond(r)) {
        // Set the pulselist property in the ps_pos based on the
        // downselection of pulses
        if (pk_ind.size(0) < 1) {
          rtDynamicBoundsError(1, 1, pk_ind.size(0), &ub_emlrtBCI);
        }

        obj = ps_pos;
        if (pk_ind[0] != static_cast<int>(std::floor(pk_ind[0]))) {
          rtIntegerError(pk_ind[0], &mb_emlrtDCI);
        }

        n = static_cast<int>(pk_ind[0]);
        if ((static_cast<int>(pk_ind[0]) < 1) || (static_cast<int>(pk_ind[0]) >
             candidatelist.size(0))) {
          rtDynamicBoundsError(static_cast<int>(pk_ind[0]), 1,
                               candidatelist.size(0), &vb_emlrtBCI);
        }

        b_n = candidatelist.size(1);
        c_candidatelist.set_size(1, candidatelist.size(1));
        for (i = 0; i < b_n; i++) {
          c_candidatelist[i] = candidatelist[(n + candidatelist.size(0) * i) - 1];
        }

        coder::internal::validator_check_size(c_candidatelist, b_val);
        obj->pl.set_size(1, b_val.size(1));
        b_n = b_val.size(1);
        for (n = 0; n < b_n; n++) {
          obj->pl[n] = b_val[n];
        }
      } else {
        // If nothing above threshold was found, fill with empty
        // pulse object
        obj = ps_pos;
        makepulsestruc(&val.A, &val.P, &val.SNR, &val.yw, &val.t_0, &val.t_f,
                       val.t_next, &val.fp, &val.fstart, &val.fend, val.mode,
                       &val.det_dec, &val.con_dec);
        obj->pl.set_size(1, 1);
        obj->pl[0] = val;
      }

      // Record all candidates for posterity
      obj = ps_pos;
      b_candidatelist.set_size(candidatelist.size(0), candidatelist.size(1));
      b_n = candidatelist.size(0) * candidatelist.size(1) - 1;
      for (n = 0; n <= b_n; n++) {
        b_candidatelist[n] = candidatelist[n];
      }

      coder::internal::c_validator_check_size(b_candidatelist, candidatelist);
      obj->clst.set_size(candidatelist.size(0), candidatelist.size(1));
      b_n = candidatelist.size(0) * candidatelist.size(1);
      for (n = 0; n < b_n; n++) {
        obj->clst[n] = candidatelist[n];
      }

      obj = ps_pos;
      b_msk.set_size(msk.size(0), msk.size(1));
      b_n = msk.size(0) * msk.size(1) - 1;
      for (n = 0; n <= b_n; n++) {
        b_msk[n] = msk[n];
      }

      coder::internal::d_validator_check_size(b_msk, msk);
      obj->cmsk.set_size(msk.size(0), msk.size(1));
      b_n = msk.size(0) * msk.size(1);
      for (n = 0; n < b_n; n++) {
        obj->cmsk[n] = msk[n];
      }

      obj = ps_pos;
      coder::internal::validator_check_size(pk_ind, _in);
      obj->cpki.set_size(_in.size(0), _in.size(1));
      b_n = _in.size(0) * _in.size(1);
      for (n = 0; n < b_n; n++) {
        obj->cpki[n] = _in[n];
      }

      //  Detection?
      r.set_size(pk_ind.size(0));
      b_n = pk_ind.size(0);
      for (n = 0; n < b_n; n++) {
        r[n] = std::isnan(pk_ind[n]);
      }

      b_n = r.size(0);
      for (n = 0; n < b_n; n++) {
        r[n] = !r[n];
      }

      if (coder::internal::ifWhileCond(r)) {
        // Dection was made
        // True ->
        // Update confirmation property for each pulse. False
        // recorded for confirmation property since we are
        // currently in discovery mode and can't confirm anything
        // yet.
        n = ps_pos->pl.size(1) - 1;
        for (int b_i{0}; b_i <= n; b_i++) {
          b_val.set_size(1, ps_pos->pl.size(1));
          b_n = ps_pos->pl.size(1);
          for (i = 0; i < b_n; i++) {
            b_val[i] = ps_pos->pl[i];
          }

          if (b_i + 1 > b_val.size(1)) {
            rtDynamicBoundsError(b_i + 1, 1, b_val.size(1), &wb_emlrtBCI);
          }

          b_val[b_i].con_dec = false;
          obj = ps_pos;
          c_candidatelist.set_size(1, b_val.size(1));
          b_n = b_val.size(0) * b_val.size(1) - 1;
          for (i = 0; i <= b_n; i++) {
            c_candidatelist[i] = b_val[i];
          }

          coder::internal::validator_check_size(c_candidatelist, b_val);
          obj->pl.set_size(1, b_val.size(1));
          b_n = b_val.size(1);
          for (i = 0; i < b_n; i++) {
            obj->pl[i] = b_val[i];
          }
        }

        //                      %Only update posteriori if we are focusing. If in open
        //                      %mode, we don't evolve the understanding of pulse
        //                      %timing in the priori.
        //                      if strcmp(focus_mode,'focus')
        //                      %Calculate & set post. stats (reduced uncertainty)
        //                      %obj.update_posteriori(obj.ps_pos.pl)
        //                      obj.ps_pos.updateposteriori(obj.ps_pre,obj.ps_pos.pl)
        //                      end
        //    Update Mode Recommendation -> Confirmation
        obj = ps_pos;
        obj->mode = 'C';
      } else {
        // Dection was not made
        // False ->
        // Just update the mode recommendation to 'S' (search)
        // so we keep an open search
        obj = ps_pos;
        obj->mode = 'S';

        // 'D';
        // obj.ps_pos.updateposteriori(obj.ps_pre,[]);%No pulses to update the posteriori
      }

      // Set the mode in the pulse and candidate listing for
      // records. This records the mode that was used in the
      // detection of the record pulses. This is useful for
      // debugging.
      n = ps_pos->pl.size(1) - 1;
      for (int b_i{0}; b_i <= n; b_i++) {
        b_val.set_size(1, ps_pos->pl.size(1));
        b_n = ps_pos->pl.size(1);
        for (i = 0; i < b_n; i++) {
          b_val[i] = ps_pos->pl[i];
        }

        if (b_i + 1 > b_val.size(1)) {
          rtDynamicBoundsError(b_i + 1, 1, b_val.size(1), &xb_emlrtBCI);
        }

        b_val[b_val.size(0) * b_i].mode.set_size(1, b_val[b_val.size(0) * b_i].
          mode.size(1));
        if (b_i + 1 > b_val.size(1)) {
          rtDynamicBoundsError(b_i + 1, 1, b_val.size(1), &xb_emlrtBCI);
        }

        b_val[b_val.size(0) * b_i].mode.set_size(b_val[b_val.size(0) * b_i].
          mode.size(0), 1);
        if (b_i + 1 > b_val.size(1)) {
          rtDynamicBoundsError(b_i + 1, 1, b_val.size(1), &xb_emlrtBCI);
        }

        b_val[b_i].mode[0] = mode;
        obj = ps_pos;
        c_candidatelist.set_size(1, b_val.size(1));
        b_n = b_val.size(0) * b_val.size(1) - 1;
        for (i = 0; i <= b_n; i++) {
          c_candidatelist[i] = b_val[i];
        }

        coder::internal::validator_check_size(c_candidatelist, b_val);
        obj->pl.set_size(1, b_val.size(1));
        b_n = b_val.size(1);
        for (i = 0; i < b_n; i++) {
          obj->pl[i] = b_val[i];
        }

        // 'D';
      }

      n = ps_pos->clst.size(0) * ps_pos->clst.size(1) - 1;
      for (int b_i{0}; b_i <= n; b_i++) {
        candidatelist.set_size(ps_pos->clst.size(0), ps_pos->clst.size(1));
        b_n = ps_pos->clst.size(0) * ps_pos->clst.size(1);
        for (i = 0; i < b_n; i++) {
          candidatelist[i] = ps_pos->clst[i];
        }

        i = candidatelist.size(0) * candidatelist.size(1);
        if ((static_cast<int>(b_i + 1U) < 1) || (static_cast<int>(b_i + 1U) > i))
        {
          rtDynamicBoundsError(static_cast<int>(b_i + 1U), 1, i, &yb_emlrtBCI);
        }

        candidatelist[b_i].mode.set_size(1, candidatelist[b_i].mode.size(1));
        i = candidatelist.size(0) * candidatelist.size(1);
        if ((static_cast<int>(b_i + 1U) < 1) || (static_cast<int>(b_i + 1U) > i))
        {
          rtDynamicBoundsError(static_cast<int>(b_i + 1U), 1, i, &yb_emlrtBCI);
        }

        candidatelist[b_i].mode.set_size(candidatelist[b_i].mode.size(0), 1);
        i = candidatelist.size(0) * candidatelist.size(1);
        if ((static_cast<int>(b_i + 1U) < 1) || (static_cast<int>(b_i + 1U) > i))
        {
          rtDynamicBoundsError(static_cast<int>(b_i + 1U), 1, i, &yb_emlrtBCI);
        }

        i = candidatelist.size(0) * candidatelist.size(1);
        if ((static_cast<int>(b_i + 1U) < 1) || (static_cast<int>(b_i + 1U) > i))
        {
          rtDynamicBoundsError(static_cast<int>(b_i + 1U), 1, i, &yb_emlrtBCI);
        }

        i = candidatelist.size(0) * candidatelist.size(1);
        if ((static_cast<int>(b_i + 1U) < 1) || (static_cast<int>(b_i + 1U) > i))
        {
          rtDynamicBoundsError(static_cast<int>(b_i + 1U), 1, i, &ac_emlrtBCI);
        }

        candidatelist[b_i].mode[0] = mode;
        obj = ps_pos;
        b_candidatelist.set_size(candidatelist.size(0), candidatelist.size(1));
        b_n = candidatelist.size(0) * candidatelist.size(1) - 1;
        for (i = 0; i <= b_n; i++) {
          b_candidatelist[i] = candidatelist[i];
        }

        coder::internal::c_validator_check_size(b_candidatelist, candidatelist);
        obj->clst.set_size(candidatelist.size(0), candidatelist.size(1));
        b_n = candidatelist.size(0) * candidatelist.size(1);
        for (i = 0; i < b_n; i++) {
          obj->clst[i] = candidatelist[i];
        }

        //  'D';
      }

      //             %% CONFIRMATION MODE
    }
    break;

   case 1:
    {
      coder::array<boolean_T, 1U> b_minstartlog;

      // Find all the potential pulses in the dataset
      findpulse(time_search_type_data, time_search_type_size,
                freq_search_type_data, freq_search_type_size,
                excluded_freq_bands, candidatelist, msk, pk_ind);
      b_n = candidatelist.size(0) * candidatelist.size(1);
      if (b_n == 0) {
        n = 0;
      } else {
        n = b_n;
      }

      minstartlog.set_size(1, n);
      if (b_n > 2147483646) {
        coder::check_forloop_overflow_error();
      }

      for (int b_i{0}; b_i < b_n; b_i++) {
        minstartlog[b_i] = candidatelist[b_i].det_dec;
      }

      if (minstartlog.size(1) != 0) {
        b_n = minstartlog.size(1);
      } else {
        b_n = 0;
      }

      b_minstartlog = minstartlog.reshape(b_n);
      have_priori_freq_band = coder::internal::allOrAny_anonFcn1(b_minstartlog);
      if (have_priori_freq_band) {
        r.set_size(pk_ind.size(0));
        b_n = pk_ind.size(0);
        for (n = 0; n < b_n; n++) {
          r[n] = std::isnan(pk_ind[n]);
        }

        coder::internal::allOrAny_anonFcn1(r);
      } else {
        // At least one pulse group met the threshold
      }

      r.set_size(pk_ind.size(0));
      b_n = pk_ind.size(0);
      for (n = 0; n < b_n; n++) {
        r[n] = std::isnan(pk_ind[n]);
      }

      b_n = r.size(0);
      for (n = 0; n < b_n; n++) {
        r[n] = !r[n];
      }

      if (coder::internal::ifWhileCond(r)) {
        // Record the detection pulses
        // We only use the highest power pulse group for now
        // because if we are in confirmation mode, we only allow
        // for the selection mode to be 'most'
        if (pk_ind.size(0) < 1) {
          rtDynamicBoundsError(1, 1, pk_ind.size(0), &mb_emlrtBCI);
        }

        obj = ps_pos;
        if (pk_ind[0] != static_cast<int>(std::floor(pk_ind[0]))) {
          rtIntegerError(pk_ind[0], &u_emlrtDCI);
        }

        if ((static_cast<int>(pk_ind[0]) < 1) || (static_cast<int>(pk_ind[0]) >
             candidatelist.size(0))) {
          rtDynamicBoundsError(static_cast<int>(pk_ind[0]), 1,
                               candidatelist.size(0), &nb_emlrtBCI);
        }

        b_n = candidatelist.size(1);
        c_candidatelist.set_size(1, candidatelist.size(1));
        for (n = 0; n < b_n; n++) {
          c_candidatelist[n] = candidatelist[(static_cast<int>(pk_ind[0]) +
            candidatelist.size(0) * n) - 1];
        }

        coder::internal::validator_check_size(c_candidatelist, b_val);
        obj->pl.set_size(1, b_val.size(1));
        b_n = b_val.size(1);
        for (n = 0; n < b_n; n++) {
          obj->pl[n] = b_val[n];
        }
      } else {
        // If nothing above threshold was found, fill with empty
        // pulse object
        obj = ps_pos;
        makepulsestruc(&val.A, &val.P, &val.SNR, &val.yw, &val.t_0, &val.t_f,
                       val.t_next, &val.fp, &val.fstart, &val.fend, val.mode,
                       &val.det_dec, &val.con_dec);
        obj->pl.set_size(1, 1);
        obj->pl[0] = val;
      }

      // Record all candidates for posterity
      obj = ps_pos;
      b_candidatelist.set_size(candidatelist.size(0), candidatelist.size(1));
      b_n = candidatelist.size(0) * candidatelist.size(1) - 1;
      for (n = 0; n <= b_n; n++) {
        b_candidatelist[n] = candidatelist[n];
      }

      coder::internal::c_validator_check_size(b_candidatelist, candidatelist);
      obj->clst.set_size(candidatelist.size(0), candidatelist.size(1));
      b_n = candidatelist.size(0) * candidatelist.size(1);
      for (n = 0; n < b_n; n++) {
        obj->clst[n] = candidatelist[n];
      }

      obj = ps_pos;
      b_msk.set_size(msk.size(0), msk.size(1));
      b_n = msk.size(0) * msk.size(1) - 1;
      for (n = 0; n <= b_n; n++) {
        b_msk[n] = msk[n];
      }

      coder::internal::d_validator_check_size(b_msk, msk);
      obj->cmsk.set_size(msk.size(0), msk.size(1));
      b_n = msk.size(0) * msk.size(1);
      for (n = 0; n < b_n; n++) {
        obj->cmsk[n] = msk[n];
      }

      obj = ps_pos;
      coder::internal::validator_check_size(pk_ind, _in);
      obj->cpki.set_size(_in.size(0), _in.size(1));
      b_n = _in.size(0) * _in.size(1);
      for (n = 0; n < b_n; n++) {
        obj->cpki[n] = _in[n];
      }

      maxstartlog.set_size(1, 1);
      maxstartlog[0] = false;

      // Set to all false. Needed
      //  Detection?
      r.set_size(pk_ind.size(0));
      b_n = pk_ind.size(0);
      for (n = 0; n < b_n; n++) {
        r[n] = std::isnan(pk_ind[n]);
      }

      b_n = r.size(0);
      for (n = 0; n < b_n; n++) {
        r[n] = !r[n];
      }

      if (coder::internal::ifWhileCond(r)) {
        // ~isempty(pulselist)%obj.decide(pulselist,PF,decision_table) %Decision on IDed pulses
        // True ->
        n = ps_pre->pl.size(1);
        i = ps_pre->pl.size(1);
        if ((i < 1) || (i > n)) {
          rtDynamicBoundsError(i, 1, n, &ob_emlrtBCI);
        }

        tref = ps_pre->pl[i - 1].t_0;
        tip = ps_pre->t_ip;
        tipu = ps_pre->t_ipu;
        tipj = ps_pre->t_ipj;
        if (tref > t_0) {
          // First pulse in this segment exists in last segment as well because of overlap
          b_x = K - 1.0;
          if (std::isnan(b_x)) {
            pulseendtimes_withuncert.set_size(1, 1);
            pulseendtimes_withuncert[0] = rtNaN;
          } else if (b_x < 0.0) {
            pulseendtimes_withuncert.set_size(1, 0);
          } else {
            pulseendtimes_withuncert.set_size(1, static_cast<int>(b_x) + 1);
            b_n = static_cast<int>(b_x);
            for (n = 0; n <= b_n; n++) {
              pulseendtimes_withuncert[n] = n;
            }
          }

          b_x = tip - tipu;
          pulsestarttimes_withuncert.set_size(1, pulseendtimes_withuncert.size(1));
          b_n = pulseendtimes_withuncert.size(1);
          for (n = 0; n < b_n; n++) {
            pulsestarttimes_withuncert[n] = b_x * pulseendtimes_withuncert[n];
          }

          b.set_size(1, b.size(1));
          if (!(K >= 0.0)) {
            rtNonNegativeError(K, &v_emlrtDCI);
          }

          b_x = K;
          if (b_x != static_cast<int>(std::floor(b_x))) {
            rtIntegerError(b_x, &w_emlrtDCI);
          }

          b.set_size(b.size(0), static_cast<int>(b_x));
          if (!(K >= 0.0)) {
            rtNonNegativeError(K, &x_emlrtDCI);
          }

          b_x = K;
          if (b_x != static_cast<int>(std::floor(b_x))) {
            rtIntegerError(b_x, &y_emlrtDCI);
          }

          b_n = static_cast<int>(b_x);
          for (n = 0; n < b_n; n++) {
            b[n] = 1.0;
          }

          b.set_size(1, b.size(1));
          b_n = b.size(1) - 1;
          for (n = 0; n <= b_n; n++) {
            b[n] = tipj * b[n];
          }

          if ((pulsestarttimes_withuncert.size(1) != b.size(1)) &&
              ((pulsestarttimes_withuncert.size(1) != 1) && (b.size(1) != 1))) {
            emlrtDimSizeImpxCheckR2021b(pulsestarttimes_withuncert.size(1),
              b.size(1), &g_emlrtECI);
          }

          if (pulsestarttimes_withuncert.size(1) == b.size(1)) {
            b_n = pulsestarttimes_withuncert.size(1) - 1;
            pulsestarttimes_withuncert.set_size(1,
              pulsestarttimes_withuncert.size(1));
            for (n = 0; n <= b_n; n++) {
              pulsestarttimes_withuncert[n] = (tref +
                pulsestarttimes_withuncert[n]) - b[n];
            }
          } else {
            f_binary_expand_op(pulsestarttimes_withuncert, tref, b);
          }

          b_x = tip + tipu;
          pulseendtimes_withuncert.set_size(1, pulseendtimes_withuncert.size(1));
          b_n = pulseendtimes_withuncert.size(1) - 1;
          for (n = 0; n <= b_n; n++) {
            pulseendtimes_withuncert[n] = b_x * pulseendtimes_withuncert[n];
          }

          b.set_size(1, b.size(1));
          if (!(K >= 0.0)) {
            rtNonNegativeError(K, &ab_emlrtDCI);
          }

          b_x = K;
          if (b_x != static_cast<int>(std::floor(b_x))) {
            rtIntegerError(b_x, &bb_emlrtDCI);
          }

          b.set_size(b.size(0), static_cast<int>(b_x));
          if (!(K >= 0.0)) {
            rtNonNegativeError(K, &cb_emlrtDCI);
          }

          b_x = K;
          if (b_x != static_cast<int>(std::floor(b_x))) {
            rtIntegerError(b_x, &db_emlrtDCI);
          }

          b_n = static_cast<int>(b_x);
          for (n = 0; n < b_n; n++) {
            b[n] = 1.0;
          }

          b.set_size(1, b.size(1));
          b_n = b.size(1) - 1;
          for (n = 0; n <= b_n; n++) {
            b[n] = tipj * b[n];
          }

          if ((pulseendtimes_withuncert.size(1) != b.size(1)) &&
              ((pulseendtimes_withuncert.size(1) != 1) && (b.size(1) != 1))) {
            emlrtDimSizeImpxCheckR2021b(pulseendtimes_withuncert.size(1), b.size
              (1), &h_emlrtECI);
          }

          if (pulseendtimes_withuncert.size(1) == b.size(1)) {
            b_n = pulseendtimes_withuncert.size(1) - 1;
            pulseendtimes_withuncert.set_size(1, pulseendtimes_withuncert.size(1));
            for (n = 0; n <= b_n; n++) {
              pulseendtimes_withuncert[n] = (tref + pulseendtimes_withuncert[n])
                + b[n];
            }
          } else {
            binary_expand_op(pulseendtimes_withuncert, tref, b);
          }
        } else {
          // First pulse in this segment does not exists in last segment as well because of overlap
          b_x = K;
          if (std::isnan(b_x)) {
            pulseendtimes_withuncert.set_size(1, 1);
            pulseendtimes_withuncert[0] = rtNaN;
          } else if (b_x < 1.0) {
            pulseendtimes_withuncert.set_size(1, 0);
          } else {
            pulseendtimes_withuncert.set_size(1, static_cast<int>(b_x - 1.0) + 1);
            b_n = static_cast<int>(b_x - 1.0);
            for (n = 0; n <= b_n; n++) {
              pulseendtimes_withuncert[n] = static_cast<double>(n) + 1.0;
            }
          }

          b_x = tip - tipu;
          pulsestarttimes_withuncert.set_size(1, pulseendtimes_withuncert.size(1));
          b_n = pulseendtimes_withuncert.size(1);
          for (n = 0; n < b_n; n++) {
            pulsestarttimes_withuncert[n] = b_x * pulseendtimes_withuncert[n];
          }

          b.set_size(1, b.size(1));
          if (!(K >= 0.0)) {
            rtNonNegativeError(K, &eb_emlrtDCI);
          }

          b_x = K;
          if (b_x != static_cast<int>(std::floor(b_x))) {
            rtIntegerError(b_x, &fb_emlrtDCI);
          }

          b.set_size(b.size(0), static_cast<int>(b_x));
          if (!(K >= 0.0)) {
            rtNonNegativeError(K, &gb_emlrtDCI);
          }

          b_x = K;
          if (b_x != static_cast<int>(std::floor(b_x))) {
            rtIntegerError(b_x, &hb_emlrtDCI);
          }

          b_n = static_cast<int>(b_x);
          for (n = 0; n < b_n; n++) {
            b[n] = 1.0;
          }

          b.set_size(1, b.size(1));
          b_n = b.size(1) - 1;
          for (n = 0; n <= b_n; n++) {
            b[n] = tipj * b[n];
          }

          if ((pulsestarttimes_withuncert.size(1) != b.size(1)) &&
              ((pulsestarttimes_withuncert.size(1) != 1) && (b.size(1) != 1))) {
            emlrtDimSizeImpxCheckR2021b(pulsestarttimes_withuncert.size(1),
              b.size(1), &n_emlrtECI);
          }

          if (pulsestarttimes_withuncert.size(1) == b.size(1)) {
            b_n = pulsestarttimes_withuncert.size(1) - 1;
            pulsestarttimes_withuncert.set_size(1,
              pulsestarttimes_withuncert.size(1));
            for (n = 0; n <= b_n; n++) {
              pulsestarttimes_withuncert[n] = (tref +
                pulsestarttimes_withuncert[n]) - b[n];
            }
          } else {
            f_binary_expand_op(pulsestarttimes_withuncert, tref, b);
          }

          b_x = tip + tipu;
          pulseendtimes_withuncert.set_size(1, pulseendtimes_withuncert.size(1));
          b_n = pulseendtimes_withuncert.size(1) - 1;
          for (n = 0; n <= b_n; n++) {
            pulseendtimes_withuncert[n] = b_x * pulseendtimes_withuncert[n];
          }

          b.set_size(1, b.size(1));
          if (!(K >= 0.0)) {
            rtNonNegativeError(K, &ib_emlrtDCI);
          }

          b_x = K;
          if (b_x != static_cast<int>(std::floor(b_x))) {
            rtIntegerError(b_x, &jb_emlrtDCI);
          }

          b.set_size(b.size(0), static_cast<int>(b_x));
          if (!(K >= 0.0)) {
            rtNonNegativeError(K, &kb_emlrtDCI);
          }

          b_x = K;
          if (b_x != static_cast<int>(std::floor(b_x))) {
            rtIntegerError(b_x, &lb_emlrtDCI);
          }

          b_n = static_cast<int>(b_x);
          for (n = 0; n < b_n; n++) {
            b[n] = 1.0;
          }

          b.set_size(1, b.size(1));
          b_n = b.size(1) - 1;
          for (n = 0; n <= b_n; n++) {
            b[n] = tipj * b[n];
          }

          if ((pulseendtimes_withuncert.size(1) != b.size(1)) &&
              ((pulseendtimes_withuncert.size(1) != 1) && (b.size(1) != 1))) {
            emlrtDimSizeImpxCheckR2021b(pulseendtimes_withuncert.size(1), b.size
              (1), &o_emlrtECI);
          }

          if (pulseendtimes_withuncert.size(1) == b.size(1)) {
            b_n = pulseendtimes_withuncert.size(1) - 1;
            pulseendtimes_withuncert.set_size(1, pulseendtimes_withuncert.size(1));
            for (n = 0; n <= b_n; n++) {
              pulseendtimes_withuncert[n] = (tref + pulseendtimes_withuncert[n])
                + b[n];
            }
          } else {
            binary_expand_op(pulseendtimes_withuncert, tref, b);
          }
        }

        // pulseendtimes_nom          = pulsestarttimes_nom+tp;
        // pulsestarttimes_withuncert = pulsestarttimes_nom-tipu-tipj;
        // pulseendtimes_withuncert   = pulsestarttimes_nom+tipu+tipj;
        // Check if pulses started after expected minimum start times
        b_n = ps_pos->pl.size(1);
        b_obj.set_size(b_n);
        b_n--;
        for (n = 0; n <= b_n; n++) {
          b_obj[n] = ps_pos->pl[n];
        }

        b_n = b_obj.size(0);
        if (b_obj.size(0) == 0) {
          n = 0;
        } else {
          n = b_obj.size(0);
        }

        varargin_1.set_size(1, n);
        if (b_obj.size(0) > 2147483646) {
          coder::check_forloop_overflow_error();
        }

        for (int b_i{0}; b_i < b_n; b_i++) {
          varargin_1[b_i] = b_obj[b_i].t_0;
        }

        if (varargin_1.size(1) != 0) {
          input_sizes[1] = varargin_1.size(1);
        } else {
          input_sizes[1] = 0;
        }

        if ((input_sizes[1] != pulsestarttimes_withuncert.size(1)) &&
            ((input_sizes[1] != 1) && (pulsestarttimes_withuncert.size(1) != 1)))
        {
          emlrtDimSizeImpxCheckR2021b(input_sizes[1],
            pulsestarttimes_withuncert.size(1), &i_emlrtECI);
        }

        if (input_sizes[1] == pulsestarttimes_withuncert.size(1)) {
          minstartlog.set_size(1, input_sizes[1]);
          b_n = input_sizes[1];
          for (n = 0; n < b_n; n++) {
            minstartlog[n] = (varargin_1[n] >= pulsestarttimes_withuncert[n]);
          }
        } else {
          e_binary_expand_op(minstartlog, varargin_1, input_sizes,
                             pulsestarttimes_withuncert);
        }

        // Check if pulses started before expected maximum start times
        b_n = ps_pos->pl.size(1);
        b_obj.set_size(b_n);
        b_n--;
        for (n = 0; n <= b_n; n++) {
          b_obj[n] = ps_pos->pl[n];
        }

        b_n = b_obj.size(0);
        if (b_obj.size(0) == 0) {
          n = 0;
        } else {
          n = b_obj.size(0);
        }

        varargin_1.set_size(1, n);
        if (b_obj.size(0) > 2147483646) {
          coder::check_forloop_overflow_error();
        }

        for (int b_i{0}; b_i < b_n; b_i++) {
          varargin_1[b_i] = b_obj[b_i].t_0;
        }

        if (varargin_1.size(1) != 0) {
          b_input_sizes[1] = varargin_1.size(1);
        } else {
          b_input_sizes[1] = 0;
        }

        if ((b_input_sizes[1] != pulseendtimes_withuncert.size(1)) &&
            ((b_input_sizes[1] != 1) && (pulseendtimes_withuncert.size(1) != 1)))
        {
          emlrtDimSizeImpxCheckR2021b(b_input_sizes[1],
            pulseendtimes_withuncert.size(1), &j_emlrtECI);
        }

        if (b_input_sizes[1] == pulseendtimes_withuncert.size(1)) {
          maxstartlog.set_size(1, b_input_sizes[1]);
          b_n = b_input_sizes[1];
          for (n = 0; n < b_n; n++) {
            maxstartlog[n] = (varargin_1[n] <= pulseendtimes_withuncert[n]);
          }
        } else {
          d_binary_expand_op(maxstartlog, varargin_1, b_input_sizes,
                             pulseendtimes_withuncert);
        }

        // Frequency check. Within +/- 100 Hz of previously
        // detected pulses?
        c_candidatelist.set_size(1, ps_pos->pl.size(1));
        b_n = ps_pos->pl.size(0) * ps_pos->pl.size(1) - 1;
        for (n = 0; n <= b_n; n++) {
          c_candidatelist[n] = ps_pos->pl[n];
        }

        b_n = c_candidatelist.size(1);
        if (c_candidatelist.size(1) == 0) {
          n = 0;
        } else {
          n = c_candidatelist.size(1);
        }

        varargin_1.set_size(1, n);
        if (c_candidatelist.size(1) > 2147483646) {
          coder::check_forloop_overflow_error();
        }

        for (int b_i{0}; b_i < b_n; b_i++) {
          varargin_1[b_i] = c_candidatelist[b_i].fp;
        }

        if (varargin_1.size(1) != 0) {
          c_input_sizes[1] = varargin_1.size(1);
        } else {
          c_input_sizes[1] = 0;
        }

        c_candidatelist.set_size(1, ps_pre->pl.size(1));
        b_n = ps_pre->pl.size(0) * ps_pre->pl.size(1) - 1;
        for (n = 0; n <= b_n; n++) {
          c_candidatelist[n] = ps_pre->pl[n];
        }

        b_n = c_candidatelist.size(1);
        if (c_candidatelist.size(1) == 0) {
          n = 0;
        } else {
          n = c_candidatelist.size(1);
        }

        b.set_size(1, n);
        if (c_candidatelist.size(1) > 2147483646) {
          coder::check_forloop_overflow_error();
        }

        for (int b_i{0}; b_i < b_n; b_i++) {
          b[b_i] = c_candidatelist[b_i].fp;
        }

        if (b.size(1) != 0) {
          d_input_sizes[1] = b.size(1);
        } else {
          d_input_sizes[1] = 0;
        }

        if ((c_input_sizes[1] != d_input_sizes[1]) && ((c_input_sizes[1] != 1) &&
             (d_input_sizes[1] != 1))) {
          emlrtDimSizeImpxCheckR2021b(c_input_sizes[1], d_input_sizes[1],
            &k_emlrtECI);
        }

        c_candidatelist.set_size(1, ps_pos->pl.size(1));
        b_n = ps_pos->pl.size(0) * ps_pos->pl.size(1) - 1;
        for (n = 0; n <= b_n; n++) {
          c_candidatelist[n] = ps_pos->pl[n];
        }

        b_n = c_candidatelist.size(1);
        if (c_candidatelist.size(1) == 0) {
          n = 0;
        } else {
          n = c_candidatelist.size(1);
        }

        pulsestarttimes_withuncert.set_size(1, n);
        if (c_candidatelist.size(1) > 2147483646) {
          coder::check_forloop_overflow_error();
        }

        for (int b_i{0}; b_i < b_n; b_i++) {
          pulsestarttimes_withuncert[b_i] = c_candidatelist[b_i].fp;
        }

        if (pulsestarttimes_withuncert.size(1) != 0) {
          e_input_sizes[1] = pulsestarttimes_withuncert.size(1);
        } else {
          e_input_sizes[1] = 0;
        }

        c_candidatelist.set_size(1, ps_pre->pl.size(1));
        b_n = ps_pre->pl.size(0) * ps_pre->pl.size(1) - 1;
        for (n = 0; n <= b_n; n++) {
          c_candidatelist[n] = ps_pre->pl[n];
        }

        b_n = c_candidatelist.size(1);
        if (c_candidatelist.size(1) == 0) {
          n = 0;
        } else {
          n = c_candidatelist.size(1);
        }

        pulseendtimes_withuncert.set_size(1, n);
        if (c_candidatelist.size(1) > 2147483646) {
          coder::check_forloop_overflow_error();
        }

        for (int b_i{0}; b_i < b_n; b_i++) {
          pulseendtimes_withuncert[b_i] = c_candidatelist[b_i].fp;
        }

        if (pulseendtimes_withuncert.size(1) != 0) {
          f_input_sizes[1] = pulseendtimes_withuncert.size(1);
        } else {
          f_input_sizes[1] = 0;
        }

        if ((e_input_sizes[1] != f_input_sizes[1]) && ((e_input_sizes[1] != 1) &&
             (f_input_sizes[1] != 1))) {
          emlrtDimSizeImpxCheckR2021b(e_input_sizes[1], f_input_sizes[1],
            &l_emlrtECI);
        }

        if (c_input_sizes[1] == d_input_sizes[1]) {
          freqInBand.set_size(1, c_input_sizes[1]);
          b_n = c_input_sizes[1];
          for (n = 0; n < b_n; n++) {
            freqInBand[n] = (varargin_1[n] >= b[n] - 100.0);
          }
        } else {
          c_binary_expand_op(freqInBand, varargin_1, c_input_sizes, b,
                             d_input_sizes);
        }

        if (e_input_sizes[1] == f_input_sizes[1]) {
          r1.set_size(1, e_input_sizes[1]);
          b_n = e_input_sizes[1];
          for (n = 0; n < b_n; n++) {
            r1[n] = (pulsestarttimes_withuncert[n] <= pulseendtimes_withuncert[n]
                     + 100.0);
          }
        } else {
          b_binary_expand_op(r1, pulsestarttimes_withuncert, e_input_sizes,
                             pulseendtimes_withuncert, f_input_sizes);
        }

        if ((freqInBand.size(1) != r1.size(1)) && ((freqInBand.size(1) != 1) &&
             (r1.size(1) != 1))) {
          emlrtDimSizeImpxCheckR2021b(freqInBand.size(1), r1.size(1),
            &k_emlrtECI);
        }

        if (freqInBand.size(1) == r1.size(1)) {
          b_n = freqInBand.size(1) - 1;
          freqInBand.set_size(1, freqInBand.size(1));
          for (n = 0; n <= b_n; n++) {
            freqInBand[n] = (freqInBand[n] && r1[n]);
          }
        } else {
          b_and(freqInBand, r1);
        }

        if ((maxstartlog.size(1) != minstartlog.size(1)) && ((maxstartlog.size(1)
              != 1) && (minstartlog.size(1) != 1))) {
          emlrtDimSizeImpxCheckR2021b(maxstartlog.size(1), minstartlog.size(1),
            &m_emlrtECI);
        }

        if (maxstartlog.size(1) == minstartlog.size(1)) {
          b_n = maxstartlog.size(1) - 1;
          maxstartlog.set_size(1, maxstartlog.size(1));
          for (n = 0; n <= b_n; n++) {
            maxstartlog[n] = (maxstartlog[n] && minstartlog[n]);
          }
        } else {
          b_and(maxstartlog, minstartlog);
        }

        if ((maxstartlog.size(1) != freqInBand.size(1)) && ((maxstartlog.size(1)
              != 1) && (freqInBand.size(1) != 1))) {
          emlrtDimSizeImpxCheckR2021b(maxstartlog.size(1), freqInBand.size(1),
            &m_emlrtECI);
        }

        if (maxstartlog.size(1) == freqInBand.size(1)) {
          b_n = maxstartlog.size(1) - 1;
          maxstartlog.set_size(1, maxstartlog.size(1));
          for (n = 0; n <= b_n; n++) {
            maxstartlog[n] = (maxstartlog[n] && freqInBand[n]);
          }
        } else {
          b_and(maxstartlog, freqInBand);
        }

        // [minstartlog', maxstartlog', freqInBand', conflog']
        b_n = maxstartlog.size(1);
        b_minstartlog = maxstartlog.reshape(b_n);
        have_priori_freq_band = coder::internal::allOrAny_anonFcn1(b_minstartlog);
        if (have_priori_freq_band) {
          //  	Confirmed?
          //  		True -> Confirmation = True
          have_priori_freq_band = true;
        } else {
          //  		False -> Confirmation = False
          have_priori_freq_band = false;
        }
      } else {
        // False ->
        // Set confirmation = False
        have_priori_freq_band = false;
      }

      //  Confirmation?
      if (have_priori_freq_band) {
        // True ->
        // Update confirmation property for each pulse
        n = ps_pos->pl.size(1) - 1;
        for (int b_i{0}; b_i <= n; b_i++) {
          // obj.ps_pos.pl(ip).con_dec = true;
          b_val.set_size(1, ps_pos->pl.size(1));
          b_n = ps_pos->pl.size(1);
          for (i = 0; i < b_n; i++) {
            b_val[i] = ps_pos->pl[i];
          }

          if (b_i + 1 > maxstartlog.size(1)) {
            rtDynamicBoundsError(b_i + 1, 1, maxstartlog.size(1), &pb_emlrtBCI);
          }

          if (b_i + 1 > b_val.size(1)) {
            rtDynamicBoundsError(b_i + 1, 1, b_val.size(1), &qb_emlrtBCI);
          }

          b_val[b_i].con_dec = maxstartlog[b_i];
          obj = ps_pos;
          c_candidatelist.set_size(1, b_val.size(1));
          b_n = b_val.size(0) * b_val.size(1) - 1;
          for (i = 0; i <= b_n; i++) {
            c_candidatelist[i] = b_val[i];
          }

          coder::internal::validator_check_size(c_candidatelist, b_val);
          obj->pl.set_size(1, b_val.size(1));
          b_n = b_val.size(1);
          for (i = 0; i < b_n; i++) {
            obj->pl[i] = b_val[i];
          }
        }

        //                      %Open focus mode will never get to confirmation, so we
        //                      %don't need the 'if' statement here checking the focus
        //                      %most like in the discovery case above
        //                      %   Calculate & set post. stats (reduced uncertainty)
        //                      %obj.update_posteriori(obj.ps_pos.pl)%(Note this records pulse list)
        //                      obj.ps_pos.updateposteriori(obj.ps_pre,obj.ps_pos.pl)
        // Update mode suggestion for next segment processing
        //    Mode -> Tracking
        obj = ps_pos;
        obj->mode = 'T';
      } else {
        // False ->
        // Update mode suggestion for next segment processing
        // 	Mode -> Discovery
        obj = ps_pos;
        obj->mode = 'S';

        // obj.ps_pos.updateposteriori(obj.ps_pre,[]); %No pulses to update the posteriori
      }

      // Set the mode in the pulse and candidate listing for
      // records. This records the mode that was used in the
      // detection of the record pulses. This is useful for
      // debugging.
      n = ps_pos->pl.size(1) - 1;
      for (int b_i{0}; b_i <= n; b_i++) {
        b_val.set_size(1, ps_pos->pl.size(1));
        b_n = ps_pos->pl.size(1);
        for (i = 0; i < b_n; i++) {
          b_val[i] = ps_pos->pl[i];
        }

        if (b_i + 1 > b_val.size(1)) {
          rtDynamicBoundsError(b_i + 1, 1, b_val.size(1), &rb_emlrtBCI);
        }

        b_val[b_val.size(0) * b_i].mode.set_size(1, b_val[b_val.size(0) * b_i].
          mode.size(1));
        if (b_i + 1 > b_val.size(1)) {
          rtDynamicBoundsError(b_i + 1, 1, b_val.size(1), &rb_emlrtBCI);
        }

        b_val[b_val.size(0) * b_i].mode.set_size(b_val[b_val.size(0) * b_i].
          mode.size(0), 1);
        if (b_i + 1 > b_val.size(1)) {
          rtDynamicBoundsError(b_i + 1, 1, b_val.size(1), &rb_emlrtBCI);
        }

        b_val[b_i].mode[0] = mode;
        obj = ps_pos;
        c_candidatelist.set_size(1, b_val.size(1));
        b_n = b_val.size(0) * b_val.size(1) - 1;
        for (i = 0; i <= b_n; i++) {
          c_candidatelist[i] = b_val[i];
        }

        coder::internal::validator_check_size(c_candidatelist, b_val);
        obj->pl.set_size(1, b_val.size(1));
        b_n = b_val.size(1);
        for (i = 0; i < b_n; i++) {
          obj->pl[i] = b_val[i];
        }

        // 'C';
      }

      n = ps_pos->clst.size(0) * ps_pos->clst.size(1) - 1;
      for (int b_i{0}; b_i <= n; b_i++) {
        candidatelist.set_size(ps_pos->clst.size(0), ps_pos->clst.size(1));
        b_n = ps_pos->clst.size(0) * ps_pos->clst.size(1);
        for (i = 0; i < b_n; i++) {
          candidatelist[i] = ps_pos->clst[i];
        }

        i = candidatelist.size(0) * candidatelist.size(1);
        if ((static_cast<int>(b_i + 1U) < 1) || (static_cast<int>(b_i + 1U) > i))
        {
          rtDynamicBoundsError(static_cast<int>(b_i + 1U), 1, i, &sb_emlrtBCI);
        }

        candidatelist[b_i].mode.set_size(1, candidatelist[b_i].mode.size(1));
        i = candidatelist.size(0) * candidatelist.size(1);
        if ((static_cast<int>(b_i + 1U) < 1) || (static_cast<int>(b_i + 1U) > i))
        {
          rtDynamicBoundsError(static_cast<int>(b_i + 1U), 1, i, &sb_emlrtBCI);
        }

        candidatelist[b_i].mode.set_size(candidatelist[b_i].mode.size(0), 1);
        i = candidatelist.size(0) * candidatelist.size(1);
        if ((static_cast<int>(b_i + 1U) < 1) || (static_cast<int>(b_i + 1U) > i))
        {
          rtDynamicBoundsError(static_cast<int>(b_i + 1U), 1, i, &sb_emlrtBCI);
        }

        i = candidatelist.size(0) * candidatelist.size(1);
        if ((static_cast<int>(b_i + 1U) < 1) || (static_cast<int>(b_i + 1U) > i))
        {
          rtDynamicBoundsError(static_cast<int>(b_i + 1U), 1, i, &sb_emlrtBCI);
        }

        i = candidatelist.size(0) * candidatelist.size(1);
        if ((static_cast<int>(b_i + 1U) < 1) || (static_cast<int>(b_i + 1U) > i))
        {
          rtDynamicBoundsError(static_cast<int>(b_i + 1U), 1, i, &tb_emlrtBCI);
        }

        candidatelist[b_i].mode[0] = mode;
        obj = ps_pos;
        b_candidatelist.set_size(candidatelist.size(0), candidatelist.size(1));
        b_n = candidatelist.size(0) * candidatelist.size(1) - 1;
        for (i = 0; i <= b_n; i++) {
          b_candidatelist[i] = candidatelist[i];
        }

        coder::internal::c_validator_check_size(b_candidatelist, candidatelist);
        obj->clst.set_size(candidatelist.size(0), candidatelist.size(1));
        b_n = candidatelist.size(0) * candidatelist.size(1);
        for (i = 0; i < b_n; i++) {
          obj->clst[i] = candidatelist[i];
        }

        // 'C';
      }
    }
    break;

   case 2:
    {
      coder::array<boolean_T, 1U> b_minstartlog;

      //                 %% TRACKING MODE
      // Find all the potential pulses in the dataset
      findpulse(time_search_type_data, time_search_type_size,
                freq_search_type_data, freq_search_type_size,
                excluded_freq_bands, candidatelist, msk, pk_ind);
      b_n = candidatelist.size(0) * candidatelist.size(1);
      if (b_n == 0) {
        n = 0;
      } else {
        n = b_n;
      }

      minstartlog.set_size(1, n);
      if (b_n > 2147483646) {
        coder::check_forloop_overflow_error();
      }

      for (int b_i{0}; b_i < b_n; b_i++) {
        minstartlog[b_i] = candidatelist[b_i].det_dec;
      }

      if (minstartlog.size(1) != 0) {
        b_n = minstartlog.size(1);
      } else {
        b_n = 0;
      }

      b_minstartlog = minstartlog.reshape(b_n);
      have_priori_freq_band = coder::internal::allOrAny_anonFcn1(b_minstartlog);
      if (have_priori_freq_band) {
        r.set_size(pk_ind.size(0));
        b_n = pk_ind.size(0);
        for (n = 0; n < b_n; n++) {
          r[n] = std::isnan(pk_ind[n]);
        }

        coder::internal::allOrAny_anonFcn1(r);
      } else {
        // At least one pulse group met the threshold
      }

      r.set_size(pk_ind.size(0));
      b_n = pk_ind.size(0);
      for (n = 0; n < b_n; n++) {
        r[n] = std::isnan(pk_ind[n]);
      }

      b_n = r.size(0);
      for (n = 0; n < b_n; n++) {
        r[n] = !r[n];
      }

      if (coder::internal::ifWhileCond(r)) {
        // Record the detection pulses
        // We only use the highest power pulse group for now
        // because if we are in confirmation mode, we only allow
        // for the selection mode to be 'most'
        if (pk_ind.size(0) < 1) {
          rtDynamicBoundsError(1, 1, pk_ind.size(0), &gb_emlrtBCI);
        }

        obj = ps_pos;
        if (pk_ind[0] != static_cast<int>(std::floor(pk_ind[0]))) {
          rtIntegerError(pk_ind[0], &t_emlrtDCI);
        }

        if ((static_cast<int>(pk_ind[0]) < 1) || (static_cast<int>(pk_ind[0]) >
             candidatelist.size(0))) {
          rtDynamicBoundsError(static_cast<int>(pk_ind[0]), 1,
                               candidatelist.size(0), &hb_emlrtBCI);
        }

        b_n = candidatelist.size(1);
        c_candidatelist.set_size(1, candidatelist.size(1));
        for (n = 0; n < b_n; n++) {
          c_candidatelist[n] = candidatelist[(static_cast<int>(pk_ind[0]) +
            candidatelist.size(0) * n) - 1];
        }

        coder::internal::validator_check_size(c_candidatelist, b_val);
        obj->pl.set_size(1, b_val.size(1));
        b_n = b_val.size(1);
        for (n = 0; n < b_n; n++) {
          obj->pl[n] = b_val[n];
        }
      } else {
        // Nothing met the threshold for detection
        obj = ps_pos;
        makepulsestruc(&val.A, &val.P, &val.SNR, &val.yw, &val.t_0, &val.t_f,
                       val.t_next, &val.fp, &val.fstart, &val.fend, val.mode,
                       &val.det_dec, &val.con_dec);
        obj->pl.set_size(1, 1);
        obj->pl[0] = val;
      }

      obj = ps_pos;
      b_candidatelist.set_size(candidatelist.size(0), candidatelist.size(1));
      b_n = candidatelist.size(0) * candidatelist.size(1) - 1;
      for (n = 0; n <= b_n; n++) {
        b_candidatelist[n] = candidatelist[n];
      }

      coder::internal::c_validator_check_size(b_candidatelist, candidatelist);
      obj->clst.set_size(candidatelist.size(0), candidatelist.size(1));
      b_n = candidatelist.size(0) * candidatelist.size(1);
      for (n = 0; n < b_n; n++) {
        obj->clst[n] = candidatelist[n];
      }

      obj = ps_pos;
      b_msk.set_size(msk.size(0), msk.size(1));
      b_n = msk.size(0) * msk.size(1) - 1;
      for (n = 0; n <= b_n; n++) {
        b_msk[n] = msk[n];
      }

      coder::internal::d_validator_check_size(b_msk, msk);
      obj->cmsk.set_size(msk.size(0), msk.size(1));
      b_n = msk.size(0) * msk.size(1);
      for (n = 0; n < b_n; n++) {
        obj->cmsk[n] = msk[n];
      }

      obj = ps_pos;
      coder::internal::validator_check_size(pk_ind, _in);
      obj->cpki.set_size(_in.size(0), _in.size(1));
      b_n = _in.size(0) * _in.size(1);
      for (n = 0; n < b_n; n++) {
        obj->cpki[n] = _in[n];
      }

      //  Detection?
      r.set_size(pk_ind.size(0));
      b_n = pk_ind.size(0);
      for (n = 0; n < b_n; n++) {
        r[n] = std::isnan(pk_ind[n]);
      }

      b_n = r.size(0);
      for (n = 0; n < b_n; n++) {
        r[n] = !r[n];
      }

      if (coder::internal::ifWhileCond(r)) {
        // ~isempty(pulselist)%obj.decide(pulselist,PF,decision_table) %Decision on IDed pulses
        // True ->
        // Update confirmation property for each pulse
        // If we are in tracking mode, we have narrowed the time and
        // frequeny bounds, so if there is a detection then we are
        // confirming the previous projections.
        n = ps_pos->pl.size(1) - 1;
        for (int b_i{0}; b_i <= n; b_i++) {
          b_val.set_size(1, ps_pos->pl.size(1));
          b_n = ps_pos->pl.size(1);
          for (i = 0; i < b_n; i++) {
            b_val[i] = ps_pos->pl[i];
          }

          if (b_i + 1 > b_val.size(1)) {
            rtDynamicBoundsError(b_i + 1, 1, b_val.size(1), &ib_emlrtBCI);
          }

          b_val[b_i].con_dec = true;
          obj = ps_pos;
          c_candidatelist.set_size(1, b_val.size(1));
          b_n = b_val.size(0) * b_val.size(1) - 1;
          for (i = 0; i <= b_n; i++) {
            c_candidatelist[i] = b_val[i];
          }

          coder::internal::validator_check_size(c_candidatelist, b_val);
          obj->pl.set_size(1, b_val.size(1));
          b_n = b_val.size(1);
          for (i = 0; i < b_n; i++) {
            obj->pl[i] = b_val[i];
          }
        }

        //                      %Open focus mode will never get to tracking, so we
        //                      %don't need the 'if' statement here checking the focuse
        //                      %most like in the discovery case above
        //                      %   Calculate & set post. Stats (reduced uncertainty)
        //                      %obj.update_posteriori(obj.ps_pos.pl)
        //                      obj.ps_pos.updateposteriori(obj.ps_pre,obj.ps_pos.pl)
        //    Mode -> Tracking
        // Update mode suggestion for next segment processing
        obj = ps_pos;
        obj->mode = mode;

        // 'T';
      } else {
        // False ->
        // Update confirmation property for each pulse. Don't need to
        // do this since there are no pulses to record a confirmation
        // decision on.
        // Update mode suggestion for next segment processing
        //    Mode -> Discovery
        obj = ps_pos;
        obj->mode = 'S';

        // 'D';
        // obj.ps_pos.updateposteriori(obj.ps_pre,[]);%No pulses to update the posteriori
      }

      // Set the mode in the pulse and candidate listing for
      // records. This records the mode that was used in the
      // detection of the record pulses. This is useful for
      // debugging.
      n = ps_pos->pl.size(1) - 1;
      for (int b_i{0}; b_i <= n; b_i++) {
        b_val.set_size(1, ps_pos->pl.size(1));
        b_n = ps_pos->pl.size(1);
        for (i = 0; i < b_n; i++) {
          b_val[i] = ps_pos->pl[i];
        }

        if (b_i + 1 > b_val.size(1)) {
          rtDynamicBoundsError(b_i + 1, 1, b_val.size(1), &jb_emlrtBCI);
        }

        b_val[b_val.size(0) * b_i].mode.set_size(1, b_val[b_val.size(0) * b_i].
          mode.size(1));
        if (b_i + 1 > b_val.size(1)) {
          rtDynamicBoundsError(b_i + 1, 1, b_val.size(1), &jb_emlrtBCI);
        }

        b_val[b_val.size(0) * b_i].mode.set_size(b_val[b_val.size(0) * b_i].
          mode.size(0), 1);
        if (b_i + 1 > b_val.size(1)) {
          rtDynamicBoundsError(b_i + 1, 1, b_val.size(1), &jb_emlrtBCI);
        }

        b_val[b_i].mode[0] = mode;
        obj = ps_pos;
        c_candidatelist.set_size(1, b_val.size(1));
        b_n = b_val.size(0) * b_val.size(1) - 1;
        for (i = 0; i <= b_n; i++) {
          c_candidatelist[i] = b_val[i];
        }

        coder::internal::validator_check_size(c_candidatelist, b_val);
        obj->pl.set_size(1, b_val.size(1));
        b_n = b_val.size(1);
        for (i = 0; i < b_n; i++) {
          obj->pl[i] = b_val[i];
        }

        //  'T';
      }

      n = ps_pos->clst.size(0) * ps_pos->clst.size(1) - 1;
      for (int b_i{0}; b_i <= n; b_i++) {
        candidatelist.set_size(ps_pos->clst.size(0), ps_pos->clst.size(1));
        b_n = ps_pos->clst.size(0) * ps_pos->clst.size(1);
        for (i = 0; i < b_n; i++) {
          candidatelist[i] = ps_pos->clst[i];
        }

        i = candidatelist.size(0) * candidatelist.size(1);
        if ((static_cast<int>(b_i + 1U) < 1) || (static_cast<int>(b_i + 1U) > i))
        {
          rtDynamicBoundsError(static_cast<int>(b_i + 1U), 1, i, &kb_emlrtBCI);
        }

        candidatelist[b_i].mode.set_size(1, candidatelist[b_i].mode.size(1));
        i = candidatelist.size(0) * candidatelist.size(1);
        if ((static_cast<int>(b_i + 1U) < 1) || (static_cast<int>(b_i + 1U) > i))
        {
          rtDynamicBoundsError(static_cast<int>(b_i + 1U), 1, i, &kb_emlrtBCI);
        }

        candidatelist[b_i].mode.set_size(candidatelist[b_i].mode.size(0), 1);
        i = candidatelist.size(0) * candidatelist.size(1);
        if ((static_cast<int>(b_i + 1U) < 1) || (static_cast<int>(b_i + 1U) > i))
        {
          rtDynamicBoundsError(static_cast<int>(b_i + 1U), 1, i, &kb_emlrtBCI);
        }

        i = candidatelist.size(0) * candidatelist.size(1);
        if ((static_cast<int>(b_i + 1U) < 1) || (static_cast<int>(b_i + 1U) > i))
        {
          rtDynamicBoundsError(static_cast<int>(b_i + 1U), 1, i, &kb_emlrtBCI);
        }

        i = candidatelist.size(0) * candidatelist.size(1);
        if ((static_cast<int>(b_i + 1U) < 1) || (static_cast<int>(b_i + 1U) > i))
        {
          rtDynamicBoundsError(static_cast<int>(b_i + 1U), 1, i, &lb_emlrtBCI);
        }

        candidatelist[b_i].mode[0] = mode;
        obj = ps_pos;
        b_candidatelist.set_size(candidatelist.size(0), candidatelist.size(1));
        b_n = candidatelist.size(0) * candidatelist.size(1) - 1;
        for (i = 0; i <= b_n; i++) {
          b_candidatelist[i] = candidatelist[i];
        }

        coder::internal::c_validator_check_size(b_candidatelist, candidatelist);
        obj->clst.set_size(candidatelist.size(0), candidatelist.size(1));
        b_n = candidatelist.size(0) * candidatelist.size(1);
        for (i = 0; i < b_n; i++) {
          obj->clst[i] = candidatelist[i];
        }

        //  'T';
      }
    }
    break;

   default:
    //                 %% SOMETHING BROKE
    break;
  }
}

//
// SETPRIORIDEPENDENTVARS updates the properties in the
// waveform that are dependent on properties in a pulsestats
// object.
//
// INPUTS:
//    obj     waveform object
//    ps_obj  a pulse stats object
// OUTPUTS:
//    None (This method modifies the waveform object properties)
//
//             %%
//
// Arguments    : const pulsestats *ps_obj
// Return Type  : void
//
void waveform::setprioridependentprops(const pulsestats *ps_obj)
{
  double b_M;
  double b_N;
  double b_n_ip;
  double b_n_ol;
  double b_n_p;
  double b_n_ws;
  double n_ipj;
  double n_ipu;
  double val;

  // GETPRIORIDEPENDENTVARS returns the properties in the
  // waveform that are dependent on prior pulse data estimates. It
  // depends on the waveform properties list Fs etc, as well as
  // pulse stats like t_ip, etc.
  // INPUTS:  ps_obj  1x1 pulse stats object
  // OUTPUTS:  pulse stats object
  // WHAT WAS DONE BY THIS METHOD IS NOW DONE BY A METHOD OF THE
  // PULSESTATS CLASS.
  //          function [] = update_posteriori(obj,pulselist)
  //              %UPDATE_POSTERIORI updates the posteriori pulse statistics of
  //              %this waveform object using the new pulse list (input) and the
  //              %apriori stats. The pulse contained in the waveform's ps_pos
  //              %property is not used directly so that the caller can decide
  //              %which pulses on which to focus the posteriori.
  //
  //              t_found    = [pulselist(:).t_0]';
  //              freq_found = mean([pulselist(:).fp],'omitnan');
  //
  //              %Create a vector of bandwidths from the pulselist
  //              bw_found = 2*(mean([pulselist.fend],'omitnan')-mean([pulselist.fstart],'omitnan'));
  //              if isempty(bw_found)
  //                  bw_found = 100;
  //                  if coder.target('MATLAB')
  //                      warning(['UAV-R: No bandwidth could be calculated ',...
  //                           'from the start and stop frequencies of the ',...
  //                           'identified pulses. A bandwidth of 100 Hz ',...
  //                           'will be used for continued informed search.'])
  //                  end
  //              end
  //
  //              %Here is where we update the stats. These methods of updates
  //              %could be improved in the future.
  //              %obj.ps_pre.t_p; %tp doesn't change. We assume it is stationary
  //
  //              if numel(pulselist)==1% Happens if K=1
  //                  %We only have one pulse to reference, so we need to check
  //                  %the prior pulse too.
  //                  if ~isempty(obj.ps_pre.pl) && ~isnan(obj.ps_pre.pl(end).t_0)
  //                      recent_tip = pulselist.t_0-obj.ps_pre.pl(end).t_0;
  //                      %There could be a case where the last segment and this
  //                      %segement identified the same pulse. In this case
  //                      %recent_tip will be very small. In this case, we just
  //                      %say we learned nothing about t_ip in this segment.
  //                      if recent_tip < obj.ps_pre.t_ipu + obj.ps_pre.t_ipJ
  //                          recent_tip = NaN;
  //                      end
  //                  else
  //                      %No new information because we don't know the last
  //                      %pulse time
  //                      recent_tip = NaN;
  //                  end
  //              else
  //                  recent_tip = diff(t_found);
  //              end
  //              %Do a check here to make sure the new tip isn't a huge change.
  //              %This could potentially happen if we are in the K = 1 case and
  //              %the block getting processed contained two pulses, with the
  //              %latter pulse getting identified/detected. The lines above
  //              %would look back to the last identified pulse and it might be
  //              %2*tip back in time, producing a very large recenttip values.
  //              %If something like this happens, we ignore it so it doesn't
  //              %affect our new tip estimates.
  //              if recent_tip > 1.5*obj.ps_pre.t_ip & recent_tip < 0.5*obj.ps_pre.t_ip
  //                  recent_tip = NaN;
  //              end
  //
  //              %Only update time parameters if we are in tracking mode. If we
  //              %aren't, we may have identified somethign that isn't a pulse
  //              if strcmp(obj.ps_pos.mode,'T') || strcmp(obj.ps_pre.mode,'T')
  //                  obj.ps_pos.t_ip  = mean([recent_tip;obj.ps_pre.t_ip],'omitnan');
  //                  obj.ps_pos.t_ipu = obj.ps_pre.t_ipu; %Don't update this because it can get too narrow.%mean([3*std(diff(t_found));obj.ps_pre.t_ipu]);
  //                  obj.ps_pos.t_ipj = obj.ps_pre.t_ipj;
  //              end
  //              fp_pos           = freq_found;%nanmean([freq_found;obj.ps_pre.fp]);%Previous fc may be nan if unknown
  //              obj.ps_pos.fp    = fp_pos;
  //              obj.ps_pos.fstart = fp_pos-bw_found/2;
  //              obj.ps_pos.fend   = fp_pos+bw_found/2;
  //
  //              obj.ps_pos.psdHist = obj.stft.psd
  //          end
  b_n_p = ps_obj->t_p * Fs;
  b_n_p = std::ceil(b_n_p);

  // Samples per pulse
  // Number of elements in STFT window
  b_n_ol = OLF * b_n_p;
  b_n_ol = std::floor(b_n_ol);

  // Number of elements overlap in STFT window
  b_n_ws = b_n_p - b_n_ol;

  // Number of elements in each step of STFT
  val = b_n_ws / Fs;

  // Time of each step of STFT
  b_n_ip = ps_obj->t_ip * Fs;
  b_n_ip = std::ceil(b_n_ip);
  n_ipu = ps_obj->t_ipu * Fs;
  n_ipu = std::ceil(n_ipu);
  n_ipj = ps_obj->t_ipj * Fs;
  n_ipj = std::ceil(n_ipj);
  b_N = std::floor(b_n_ip / b_n_ws);
  b_M = std::ceil(n_ipu / b_n_ws);
  n_ipj = std::ceil(n_ipj / b_n_ws);
  n_p = b_n_p;

  // Samples per pulse
  n_w = b_n_p;

  // Number of elements in STFT window
  n_ol = b_n_ol;

  // Number of elements overlap in STFT window
  n_ws = b_n_ws;

  // Number of elements in each step of STFT
  t_ws = val;

  // Time of each step of STFT
  n_ip = b_n_ip;

  // Samples of interpulse duration
  N = b_N;

  // Baseline interpulse duration in units of STFT windows
  M = b_M;

  // Interpulse duration deviation from baselines in units of STFT windows
  J = n_ipj;

  // Amount of deviation from the PRI means to search
  n_ipu = K;

  //              if K ~= 1
  //                  samplesforKpulses = n_ws*(K*(N+M)-2*M)+n_ol;
  //              else
  //                  samplesforKpulses = n_ws*(N+M+J+1)+n_ol;
  //              end
  // See 2022-07-11 for updates to samples def
  // obj.t_nextsegstart  = obj.t_0+(samplesforKpulses)/obj.Fs; %Don't need the overlap here since the next segment starts at samplesforKpulses+n_ol-n_ol from current sample
  n_ipu = t_0 + ((b_n_ws * ((n_ipu * (b_N + b_M) + n_ipj) + 1.0) + b_n_ol) -
                 b_n_ws * (2.0 * (n_ipu * b_M + n_ipj))) / Fs;
  t_nextsegstart[0] = n_ipu;
  t_nextsegstart[1] = n_ipu;

  // Don't need the overlap here since the next segment starts at samplesforKpulses+n_ol-n_ol from current sample
  //              if isempty(obj.TimeCorr)
  //                  obj.TimeCorr = TemporalCorrelator(N, M, J);
  //              else
  //                  obj.TimeCorr.update(N, M, J);
  //              end
}

//
// SETWEIGHTINGMATRIX method sets the W and Wf properties of
// the waveform. These are the weighting matrix and the
// frequencys (Wf) at which they are computed.
// INPUTS:
//    none
// OUTPUTS:
//    none other than setting obj.Wf and obj.W
// ----------------------------------------------------------
//
// Here we build the spectral scaling vector. We make it the same
// size as the FFT length in the STFT operation, so it has the
// same frequency resolution.
// How many frequency bins are there?
//
// Arguments    : void
// Return Type  : void
//
void waveform::setweightingmatrix()
{
  static rtBoundsCheckInfo eb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    159,                               // lineNo
    38,                                // colNo
    "stackedToeplitzMatrices",         // aName
    "weightingmatrix",                 // fName
    "H:\\repos\\uavrt_detection\\weightingmatrix.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo fb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    159,                               // lineNo
    71,                                // colNo
    "Xs",                              // aName
    "weightingmatrix",                 // fName
    "H:\\repos\\uavrt_detection\\weightingmatrix.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo gb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    159,                               // lineNo
    29,                                // colNo
    "stackedToeplitzMatrices",         // aName
    "weightingmatrix",                 // fName
    "H:\\repos\\uavrt_detection\\weightingmatrix.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo hb_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    190,                               // lineNo
    33,                                // colNo
    "freqs",                           // aName
    "weightingmatrix",                 // fName
    "H:\\repos\\uavrt_detection\\weightingmatrix.m",// pName
    0                                  // checkKind
  };

  static rtBoundsCheckInfo ib_emlrtBCI{ -1,// iFirst
    -1,                                // iLast
    200,                               // lineNo
    9,                                 // colNo
    "W",                               // aName
    "weightingmatrix",                 // fName
    "H:\\repos\\uavrt_detection\\weightingmatrix.m",// pName
    0                                  // checkKind
  };

  static rtDoubleCheckInfo t_emlrtDCI{ 155,// lineNo
    1,                                 // colNo
    "weightingmatrix",                 // fName
    "H:\\repos\\uavrt_detection\\weightingmatrix.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo u_emlrtDCI{ 155,// lineNo
    41,                                // colNo
    "weightingmatrix",                 // fName
    "H:\\repos\\uavrt_detection\\weightingmatrix.m",// pName
    1                                  // checkKind
  };

  static rtDoubleCheckInfo v_emlrtDCI{ 43,// lineNo
    28,                                // colNo
    "gettemplate",                     // fName
    "H:\\repos\\uavrt_detection\\gettemplate.m",// pName
    4                                  // checkKind
  };

  static rtDoubleCheckInfo w_emlrtDCI{ 192,// lineNo
    55,                                // colNo
    "weightingmatrix",                 // fName
    "H:\\repos\\uavrt_detection\\weightingmatrix.m",// pName
    4                                  // checkKind
  };

  static rtDoubleCheckInfo x_emlrtDCI{ 192,// lineNo
    48,                                // colNo
    "weightingmatrix",                 // fName
    "H:\\repos\\uavrt_detection\\weightingmatrix.m",// pName
    4                                  // checkKind
  };

  static rtEqualityCheckInfo g_emlrtECI{ -1,// nDims
    189,                               // lineNo
    1,                                 // colNo
    "weightingmatrix",                 // fName
    "H:\\repos\\uavrt_detection\\weightingmatrix.m"// pName
  };

  static rtEqualityCheckInfo h_emlrtECI{ -1,// nDims
    147,                               // lineNo
    5,                                 // colNo
    "weightingmatrix",                 // fName
    "H:\\repos\\uavrt_detection\\weightingmatrix.m"// pName
  };

  static rtEqualityCheckInfo i_emlrtECI{ 1,// nDims
    146,                               // lineNo
    19,                                // colNo
    "weightingmatrix",                 // fName
    "H:\\repos\\uavrt_detection\\weightingmatrix.m"// pName
  };

  static rtEqualityCheckInfo j_emlrtECI{ -1,// nDims
    159,                               // lineNo
    5,                                 // colNo
    "weightingmatrix",                 // fName
    "H:\\repos\\uavrt_detection\\weightingmatrix.m"// pName
  };

  static rtEqualityCheckInfo k_emlrtECI{ -1,// nDims
    145,                               // lineNo
    5,                                 // colNo
    "weightingmatrix",                 // fName
    "H:\\repos\\uavrt_detection\\weightingmatrix.m"// pName
  };

  static rtEqualityCheckInfo l_emlrtECI{ 1,// nDims
    193,                               // lineNo
    6,                                 // colNo
    "weightingmatrix",                 // fName
    "H:\\repos\\uavrt_detection\\weightingmatrix.m"// pName
  };

  coder::array<creal_T, 2U> Xs;
  coder::array<creal_T, 2U> b_r;
  coder::array<creal_T, 2U> c_x;
  coder::array<creal_T, 2U> currDFT;
  coder::array<creal_T, 2U> s;
  coder::array<creal_T, 2U> stackedToeplitzMatrices;
  coder::array<creal_T, 1U> b_x;
  coder::array<creal_T, 1U> r;
  coder::array<double, 2U> output_samps;
  coder::array<double, 2U> sintabinv;
  coder::array<double, 2U> w_time_domain;
  coder::array<double, 2U> wrapper;
  coder::array<double, 2U> x_of_n;
  coder::array<double, 1U> b_Wf;
  coder::array<int, 1U> iidx;
  coder::array<boolean_T, 2U> b_output_samps;
  double tmplt_samps[2];
  double b_Fs;
  double xtmp_im;
  double xtmp_re;
  int b_w_time_domain[2];
  int i;
  int i1;
  int ij;
  int k;
  int loop_ub;
  int loop_ub_tmp;
  int md2;
  int nw;
  int nx;
  unsigned int rowEnd;
  unsigned int rowStart;
  if (stft->f.size(0) == 0) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }

  ij = stft->f.size(0);

  // Build a pulse time domain template with the same number
  // of samples as frequency bins:
  // GETTEMPLATE Generates a time domain template of the the signal template in
  // the priori pulsestats object in the waveform passed to the function. The
  // returned vector is the template at the waveform's sample rate. The
  // caller can request a total number of samples greater than the samples
  // required to describe the signal. This is useful if the call will be using
  // a DFT on the result and wants a specific number of samples to ensure a
  // particular frequency resolutions.
  //
  // INPUTS:
  //    X       A waveform object with a populated ps_pre property
  //    samples The number of sample desired in the output. Must be greater
  //            than or equal to ceil(X.ps_pre.t_p*X.Fs)
  //
  // OUTPUTS:
  //    sig_template    A vector of the signal amplitude over the samples
  //                    requested at the sample rate of the input waveform.
  //
  // Author: Michael W. Shafer
  // Date:   2021-05-21
  //
  // Sort out the samples input, if submitted by the caller
  xtmp_im = ps_pre->t_p * Fs;
  xtmp_im = std::ceil(xtmp_im);
  if (ij < xtmp_im) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }

  // Generates a the template in the time domain at the sample rate of the
  // waveform.
  xtmp_im = Fs * ps_pre->t_p;
  tmplt_samps[1] = std::ceil(xtmp_im);
  tmplt_samps[0] = 0.0;
  xtmp_im = Fs * ps_pre->t_p;
  xtmp_im = std::ceil(xtmp_im);
  xtmp_re = ps_pre->t_p * Fs;
  xtmp_re = std::ceil(xtmp_re);
  coder::linspace(xtmp_im, xtmp_re, output_samps);
  coder::interp1(tmplt_samps, ps_pre->tmplt, output_samps, w_time_domain);

  // Generate the extra-zeros needed to pad to get to 'samples' samples
  loop_ub = ij - output_samps.size(1);
  if (loop_ub < 0) {
    rtNonNegativeError(static_cast<double>(loop_ub), &v_emlrtDCI);
  }

  output_samps.set_size(1, loop_ub);
  for (i = 0; i < loop_ub; i++) {
    output_samps[i] = 0.0;
  }

  i = w_time_domain.size(1);
  loop_ub = output_samps.size(1);
  w_time_domain.set_size(w_time_domain.size(0), w_time_domain.size(1) +
    output_samps.size(1));
  for (i1 = 0; i1 < loop_ub; i1++) {
    w_time_domain[i + i1] = 0.0;
  }

  // Build a rectagular waveform in the time domain with the same number of samples as frequency bins
  // t = (0:numel(sig_template)-1)/X.Fs;
  // A vector of times associated with the output template.
  // Useful for plotting in the time domain.
  // Build weighting matrix
  b_Fs = Fs;

  // WEIGHTINGMATRIX Builds the spectral weighting matrix for the incoherent
  // summationation algorithm. The matrix is based on the DFT coefficients
  // developed from the waveform passed to the function. The function first
  // developeds a weighting vectors based on an unaltered waveform, but then
  // shifts the waveforms spectral content base fractions of the DFT bin width,
  // as defined by the zetas input. These shifted waveforms then have their
  // DFT's computed. The original and shifted DFT coefficients are then aligned
  // in a matrix. In this way, this weighting matrix allows for the dominant
  // frequency in the vector it weights to be between bins. This submatrix is
  // then row shifted and concantinated a number of times so that the DFT
  // coefficients are shifted across all DFT frequency bins. The outputs are
  // the weighting matrix W and a frequency vector Wf that corresponds to the
  // rows of W. The frequencies, and therefore the rows of the W matrix, use a
  // centered frequency definitions defined by the STFT.m algorithm.
  //
  //    Example:   [W,Wf] = weightingmatrix(rand(1,10),1,[0 0.5])
  //
  //    INPUTS:
  //    x_of_n      nx1     Vector of discrete data sampled as Fs. Can be 1xn.
  //    Fs          1x1     Sampling rate in Hz of the dataset
  //    zetas       mx1     A vector of fractions of the DFT frequency bin
  //                        width for which to compute and include in the
  //                        spectral weighting matrix output. If no interbin
  //                        shifting is desired, enter 0. Range of inputs
  //                        [0,1).
  //    frequencyRangeType  String of either 'centered' or 'twosided'. See
  //                        stft.m documentation on details of these frequency
  //                        bounds. If 'centered' is selected, the zero
  //                        frequency point is near the center of the output
  //                        matrix. If 'twosided' is selected, the zero
  //                        frequency points is in the upper left corner of the
  //                        output W matrix.
  //
  //    OUTPUTS:
  //    W           nxnm    A matrix of spectral weighting vectors along each
  //                        column. The hermitian of this matrix is designed to
  //                        be multiplied by a vector of DFT coefficients. The
  //                        weights held in column p can be thought of as the
  //                        matched DFT coefficients if the signal were to have
  //                        been shifted by the template by Wf(p).
  //    Wf          nmx1    A matrix of the frequency shifts corresponding to
  //                        each column of W
  //
  //  The intended use of the W matrix is to multiply it's hermetian by a FFT
  //  vector, or STFT matrix with frequencies in the rows.
  //
  //
  //    [W^h]*S         or          [W^h]*FFT
  //
  //  The outputs of this multiplication will have n*m rows. The rows of the
  //  result there for are the "scores" of at frequency associated with that
  //  row. The row frequencies are dependent on the zetas. Consider an input
  //  series that had frequencies [-100 0 100 200]. If the zeta input was
  //  [0 0.5], weightings for full and half frequencies steps would be
  //  developed.
  //
  //        output freq     input freq
  //                            -100    0   100     200
  //                -150    [                           ]
  //                -100    [                           ]
  //                -50     [                           ]
  //                0       [            W^h            ]
  //                50      [                           ]
  //                100     [                           ]
  //                150     [                           ]
  //                200     [                           ]
  //
  //    The first row of the matrix above would contain the weightings for the
  //    -100 0 100 and 200 Hz frequencie bins if the FFT (or STFT time window)
  //    had a signal at -150 Hz. Similarly, the second row would contain the
  //    weightings for the -100 0 100 and 200 Hz frequencie bins if the FFT
  //    (or STFT time window) had a signal at -100 Hz.
  //
  // Author: Michael Shafer
  // Date:   2020-12-19
  //
  //  Change Log
  //  2022-01-12    Updated to include twosided frequency range for output and
  //                updated the code associated with generating the unsorted W
  //                matrix to increase speed. Added use of makestftFreqVector
  //                function.
  //
  // Check the inputs
  // Reshape to a column vector, as the algorithm expects
  if (w_time_domain.size(1) != 1) {
    x_of_n.set_size(w_time_domain.size(1), 1);
    loop_ub = w_time_domain.size(1);
    for (i = 0; i < loop_ub; i++) {
      x_of_n[i] = w_time_domain[i];
    }
  } else {
    x_of_n.set_size(1, 1);
    x_of_n[0] = w_time_domain[0];
  }

  nw = x_of_n.size(0);

  // F_bin_width = Fs/nw;
  if (x_of_n.size(0) - 1 < 0) {
    output_samps.set_size(1, 0);
  } else {
    output_samps.set_size(1, x_of_n.size(0));
    loop_ub = x_of_n.size(0) - 1;
    for (i = 0; i <= loop_ub; i++) {
      output_samps[i] = i;
    }
  }

  // Use complex so when implementing in simulink later, it knows this is a
  // complex vector.
  s.set_size(x_of_n.size(0), 2);
  loop_ub = x_of_n.size(0) << 1;
  for (i = 0; i < loop_ub; i++) {
    s[i].re = 0.0;
    s[i].im = 0.0;
  }

  Xs.set_size(x_of_n.size(0), 2);
  loop_ub = x_of_n.size(0) << 1;
  for (i = 0; i < loop_ub; i++) {
    Xs[i].re = 0.0;
    Xs[i].im = 0.0;
  }

  // Develop a vector of frequencies that would result from the centered method
  // of the STFT function if it were computed on the x input. This is useful
  // for debugging the frequency outputs.
  // These are designed to develop the same freqs as the STFT centered method
  // Check the "'FrequencyRange' — STFT frequency range" in the STFT help file
  // if mod(nw,2)==0
  //     freqs_orig = ((-nw/2+1):nw/2)*Fs/nw;
  // else
  //     freqs_orig = (ceil(-nw/2):floor(nw/2))*Fs/nw;
  // end
  // figure;
  loop_ub = output_samps.size(1);
  for (int b_i{0}; b_i < 2; b_i++) {
    double ai;
    double y;
    xtmp_im = 0.5 * static_cast<double>(b_i) * 6.2831853071795862;
    b_x.set_size(output_samps.size(1));
    for (i = 0; i < loop_ub; i++) {
      ai = xtmp_im * output_samps[i];
      if (ai == 0.0) {
        b_x[i].re = 0.0 / static_cast<double>(nw);
        b_x[i].im = 0.0;
      } else {
        b_x[i].re = 0.0;
        b_x[i].im = ai / static_cast<double>(nw);
      }
    }

    nx = b_x.size(0);
    if (b_x.size(0) > 2147483646) {
      coder::check_forloop_overflow_error();
    }

    for (k = 0; k < nx; k++) {
      if (b_x[k].im == 0.0) {
        b_x[k].re = std::exp(b_x[k].re);
        b_x[k].im = 0.0;
      } else if (std::isinf(b_x[k].im) && std::isinf(b_x[k].re) && (b_x[k].re <
                  0.0)) {
        b_x[k].re = 0.0;
        b_x[k].im = 0.0;
      } else {
        xtmp_re = std::exp(b_x[k].re / 2.0);
        b_x[k].re = xtmp_re * (xtmp_re * std::cos(b_x[k].im));
        b_x[k].im = xtmp_re * (xtmp_re * std::sin(b_x[k].im));
      }
    }

    rtSubAssignSizeCheck(s.size(), 1, b_x.size(), 1, &k_emlrtECI);
    ij = b_x.size(0);
    for (i = 0; i < ij; i++) {
      s[i + s.size(0) * b_i] = b_x[i];
    }

    if ((s.size(0) != x_of_n.size(0)) && ((s.size(0) != 1) && (x_of_n.size(0) !=
          1))) {
      emlrtDimSizeImpxCheckR2021b(s.size(0), x_of_n.size(0), &i_emlrtECI);
    }

    if (s.size(0) == x_of_n.size(0)) {
      c_x.set_size(s.size(0), 1);
      ij = s.size(0);
      for (i = 0; i < ij; i++) {
        c_x[i].re = x_of_n[i] * s[i + s.size(0) * b_i].re;
        c_x[i].im = x_of_n[i] * s[i + s.size(0) * b_i].im;
      }
    } else {
      binary_expand_op(c_x, s, b_i, s.size(0), x_of_n);
    }

    if (c_x.size(0) == 1) {
      t_rtErrorWithMessageID(fb_emlrtRTEI.fName, fb_emlrtRTEI.lineNo);
    }

    if (c_x.size(0) == 0) {
      currDFT.set_size(0, 1);
    } else {
      boolean_T useRadix2;
      useRadix2 = ((c_x.size(0) & (c_x.size(0) - 1)) == 0);
      coder::internal::FFTImplementationCallback::get_algo_sizes(c_x.size(0),
        useRadix2, &ij, &nx);
      coder::internal::FFTImplementationCallback::generate_twiddle_tables(nx,
        useRadix2, w_time_domain, wrapper, sintabinv);
      if (useRadix2) {
        coder::internal::FFTImplementationCallback::r2br_r2dit_trig(c_x,
          c_x.size(0), w_time_domain, wrapper, currDFT);
      } else {
        coder::internal::FFTImplementationCallback::dobluesteinfft(c_x, ij,
          c_x.size(0), w_time_domain, wrapper, sintabinv, currDFT);
      }
    }

    y = coder::b_norm(currDFT);
    currDFT.set_size(currDFT.size(0), 1);
    ij = currDFT.size(0) - 1;
    for (i = 0; i <= ij; i++) {
      xtmp_re = currDFT[i].re;
      ai = currDFT[i].im;
      if (ai == 0.0) {
        xtmp_im = xtmp_re / y;
        xtmp_re = 0.0;
      } else if (xtmp_re == 0.0) {
        xtmp_im = 0.0;
        xtmp_re = ai / y;
      } else {
        xtmp_im = xtmp_re / y;
        xtmp_re = ai / y;
      }

      currDFT[i].re = xtmp_im;
      currDFT[i].im = xtmp_re;
    }

    // FFTSHIFTSTFT Performs a standard fftshift operation but accounts for the
    // different frequency range definition in Matlabs STFT function when
    // outputing a 'centered' frequency range
    //    When calling the STFT function, the default output for frequency is
    //    the 'centered' method where frequencies are reported on the range of
    //    (-n/2+1:n/2)*Fs/n if the vector is of even length and
    //    (ceil(-n/2):floor(n/2))*Fs/n if the vector is of odd length. It seems
    //    that Matlab's fftshift function is develped for frequencies in the
    //    range of (-n/2:n/2+1)*Fs/n if the vector is of even length. The odd
    //    length definition is unaffected. The result is an incorrect shifting of
    //    the frequency vector if fftshift is used on f defined by stft's
    //    centered method. This function uses the fftshift command for vectors
    //    of even length, but shifts the result by 1 to the left to correct for
    //    this problem.
    //
    //    If x is a matrix, it is assumed that the matrix is formatted similar to
    //    the output of a STFT call, wherein the rows represent the different
    //    frequencies and the rows are the time windows. As such, in this case
    //    the rows are operated on (shifted).
    //
    // INPUTS:
    //    x       nxm     A matrix of real or complex data. If passed a matrix,
    //                    the rows should represent frequency bins
    // OUTPUT:
    //    xout    nxm     A matrix of real or complex shifted data
    //
    //  Author: Michael Shafer
    //  Date:   2020-12-19
    //
    //  Change log:
    //  2022-01-10    Updated to deal with row or column vectors or stft matrices
    //
    //  if (numel(sz)~=2) && (min(sz)~=1)
    //      error('fftshiftstft only accepts vector inputs.')
    //  end
    // Passed a matrix or a column vector
    if (currDFT.size(0) == 0) {
      xtmp_im = 0.0;
    } else {
      xtmp_im = std::fmod(static_cast<double>(currDFT.size(0)), 2.0);
    }

    if (xtmp_im != 0.0) {
      coder::fftshift(currDFT);
    } else {
      coder::fftshift(currDFT);
      coder::circshift(currDFT);
    }

    rtSubAssignSizeCheck(Xs.size(), 1, currDFT.size(), 2, &h_emlrtECI);
    ij = Xs.size(0);
    for (i = 0; i < ij; i++) {
      Xs[i + Xs.size(0) * b_i] = currDFT[i];
    }

    //    stem(freqs_orig,abs(Xs(:,i)),'DisplayName',['\zeta =',num2str(zetas(i))]);
    //    hold on
  }

  // ylabel('|Xs|');xlabel('Frequency');legend('Location',"best");
  // title('DFT of primary frequency shifts of the template')
  // New W generation method. ~25% faster on average
  xtmp_im = 2.0 * static_cast<double>(x_of_n.size(0));
  if (xtmp_im != static_cast<int>(xtmp_im)) {
    rtIntegerError(xtmp_im, &u_emlrtDCI);
  }

  stackedToeplitzMatrices.set_size(static_cast<int>(xtmp_im), x_of_n.size(0));
  xtmp_im = 2.0 * static_cast<double>(x_of_n.size(0));
  if (xtmp_im != static_cast<int>(xtmp_im)) {
    rtIntegerError(xtmp_im, &t_emlrtDCI);
  }

  loop_ub = static_cast<int>(xtmp_im) * x_of_n.size(0);
  for (i = 0; i < loop_ub; i++) {
    stackedToeplitzMatrices[i].re = 0.0;
    stackedToeplitzMatrices[i].im = 0.0;
  }

  if (Xs.size(0) < 2) {
    i = -1;
    i1 = -1;
  } else {
    i = 0;
    i1 = Xs.size(0) - 1;
  }

  loop_ub_tmp = i1 - i;
  md2 = loop_ub_tmp >> 1;
  i1 = Xs.size(0) - 1;
  for (int b_i{0}; b_i < 2; b_i++) {
    int i2;
    int i3;
    int i4;
    rowStart = b_i * nw + 1U;
    rowEnd = (rowStart + nw) - 1U;
    if (rowStart > rowEnd) {
      i2 = 0;
      i3 = 0;
    } else {
      if ((static_cast<int>(rowStart) < 1) || (static_cast<int>(rowStart) >
           stackedToeplitzMatrices.size(0))) {
        rtDynamicBoundsError(static_cast<int>(rowStart), 1,
                             stackedToeplitzMatrices.size(0), &gb_emlrtBCI);
      }

      i2 = static_cast<int>(rowStart) - 1;
      if ((static_cast<int>(rowEnd) < 1) || (static_cast<int>(rowEnd) >
           stackedToeplitzMatrices.size(0))) {
        rtDynamicBoundsError(static_cast<int>(rowEnd), 1,
                             stackedToeplitzMatrices.size(0), &eb_emlrtBCI);
      }

      i3 = static_cast<int>(rowEnd);
    }

    if (Xs.size(0) < 1) {
      rtDynamicBoundsError(1, 1, Xs.size(0), &fb_emlrtBCI);
    }

    b_x.set_size(loop_ub_tmp);
    for (i4 = 0; i4 < loop_ub_tmp; i4++) {
      b_x[i4] = Xs[((i + i4) + Xs.size(0) * b_i) + 1];
    }

    for (loop_ub = 0; loop_ub < md2; loop_ub++) {
      xtmp_re = b_x[loop_ub].re;
      xtmp_im = b_x[loop_ub].im;
      ij = (loop_ub_tmp - loop_ub) - 1;
      b_x[loop_ub] = b_x[ij];
      b_x[ij].re = xtmp_re;
      b_x[ij].im = xtmp_im;
    }

    r.set_size(b_x.size(0) + 1);
    r[0] = Xs[Xs.size(0) * b_i];
    loop_ub = b_x.size(0);
    for (i4 = 0; i4 < loop_ub; i4++) {
      r[i4 + 1] = b_x[i4];
    }

    b_r.set_size(Xs.size(0), r.size(0));
    ij = 0;
    i4 = r.size(0) - 1;
    for (nx = 0; nx <= i4; nx++) {
      k = nx;
      for (loop_ub = 0; loop_ub <= i1; loop_ub++) {
        if (loop_ub < nx) {
          b_r[ij + loop_ub] = r[k];
          k--;
        } else {
          b_r[ij + loop_ub] = Xs[k + Xs.size(0) * b_i];
          k++;
        }
      }

      ij = (ij + i1) + 1;
    }

    b_w_time_domain[0] = i3 - i2;
    b_w_time_domain[1] = stackedToeplitzMatrices.size(1);
    rtSubAssignSizeCheck(&b_w_time_domain[0], 2, b_r.size(), 2, &j_emlrtECI);
    loop_ub = b_r.size(1);
    for (i3 = 0; i3 < loop_ub; i3++) {
      ij = b_r.size(0);
      for (i4 = 0; i4 < ij; i4++) {
        stackedToeplitzMatrices[(i2 + i4) + stackedToeplitzMatrices.size(0) * i3]
          = b_r[i4 + b_r.size(0) * i3];
      }
    }
  }

  // Reshape in this way will interweave rows of each sub matrix of the stack
  rowStart = static_cast<unsigned int>(x_of_n.size(0)) << 1;
  nx = stackedToeplitzMatrices.size(0) * stackedToeplitzMatrices.size(1);
  coder::internal::assertValidSizeArg(static_cast<double>(x_of_n.size(0)));
  coder::internal::assertValidSizeArg(static_cast<double>(rowStart));
  ij = stackedToeplitzMatrices.size(0);
  if (stackedToeplitzMatrices.size(1) > stackedToeplitzMatrices.size(0)) {
    ij = stackedToeplitzMatrices.size(1);
  }

  if (nx >= ij) {
    ij = nx;
  }

  if (x_of_n.size(0) > ij) {
    l_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
  }

  if (static_cast<int>(rowStart) > ij) {
    l_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
  }

  if (x_of_n.size(0) * static_cast<int>(rowStart) != nx) {
    m_rtErrorWithMessageID(m_emlrtRTEI.fName, m_emlrtRTEI.lineNo);
  }

  // OLD W generation method. Easier to understand, but slower
  //  W     = 1i*zeros(nw,numZetas*nw);
  //  freqs = zeros(1,numZetas*nw);
  //  for i = 1:nw
  //      W(:,(i-1)*numZetas+(1:numZetas))=...
  //          circshift(Xs,i-1,1);
  //  end
  // Build a vector of the frequencies
  //   tick=1;
  //   for i = 1:numZetas:size(W,2)
  //       freqs(i:i+(numZetas-1)) = Fs/nw*((tick-1)+zetas);
  //       tick = tick+1;
  //   end
  rowEnd = static_cast<unsigned int>(x_of_n.size(0)) << 1;

  // MAKESTFTFREQVECTOR Generates the frequency vector based on the frequency
  // range specification for Matlab's stft.m 'FrequencyRange' input standard,
  //
  //    This function outputs a frequency vector based on the frequency
  //    range specification for Matlab's stft.m 'FrequencyRange' input
  //    standard. The options for the frequency ranges are 'centered'
  //    (default), 'twosided', and 'onesided'. The sftf.m documentation
  //    standard states:
  //        STFT frequency range, specified as 'centered', 'twosided', or
  //        'onesided'.
  //
  //        'centered' — Compute a two-sided, centered STFT. If 'FFTLength' is
  //        even, then s is computed over the interval (–π, π] rad/sample. If
  //        'FFTLength' is odd, then s is computed over the interval (–π, π)
  //        rad/sample. If you specify time information, then the intervals are
  //         (–fs, fs/2] cycles/unit time and (–fs, fs/2) cycles/unit time,
  //        respectively, where fs is the effective sample rate.
  //
  //        'twosided' — Compute a two-sided STFT over the interval [0, 2π)
  //        rad/sample. If you specify time information, then the interval is
  //        [0, fs) cycles/unit time.
  //
  //        'onesided' — Compute a one-sided STFT. If 'FFTLength' is even,
  //        then s is computed over the interval [0, π] rad/sample. If
  //        'FFTLength' is odd, then s is computed over the interval [0, π)
  //        rad/sample. If you specify time information, then the intervals are
  //         [0, fs/2] cycles/unit time and [0, fs/2) cycles/unit time,
  //        respectively, where fs is the effective sample rate. This option is
  //         valid only for real signals.
  //
  //    If Fs is not specificed, outputs will be in rad/sample with pi as
  //    specified in the stft.m frequency range standard.
  //
  // INPUTS:
  //    nfft                 Length of FFT performed on the STFT.
  //    frequencyRangeType   String containing 'centered', 'twosided', 'onesided'
  //    Fs                   Sample rate of data
  //
  // OUTPUTS:
  //    freqs       Vector of frequencies at which the STFT is calculated
  //
  // Author:    Michael Shafer
  // Date:      2022-01-11
  //
  if (static_cast<double>(rowEnd) - 1.0 < 0.0) {
    output_samps.set_size(output_samps.size(0), 0);
  } else {
    output_samps.set_size(1, static_cast<int>(static_cast<double>(rowEnd) - 1.0)
                          + 1);
    loop_ub = static_cast<int>(static_cast<double>(rowEnd) - 1.0);
    for (i = 0; i <= loop_ub; i++) {
      output_samps[i] = i;
    }
  }

  // Simulink (coder?) didn't like the new round inputs
  // freqs = round(freqs,3);
  output_samps.set_size(1, output_samps.size(1));
  loop_ub = output_samps.size(1) - 1;
  for (i = 0; i <= loop_ub; i++) {
    output_samps[i] = output_samps[i] * b_Fs / static_cast<double>(rowEnd) *
      1000.0;
  }

  nx = output_samps.size(1);
  if (output_samps.size(1) > 2147483646) {
    coder::check_forloop_overflow_error();
  }

  for (k = 0; k < nx; k++) {
    output_samps[k] = std::round(output_samps[k]);
  }

  output_samps.set_size(1, output_samps.size(1));
  loop_ub = output_samps.size(1) - 1;
  for (i = 0; i <= loop_ub; i++) {
    output_samps[i] = output_samps[i] / 1000.0;
  }

  // Shift everything so we use a negative frequencies
  // A little non-matlab notation to get this to run in simulink.
  xtmp_im = std::floor(b_Fs / 2.0);
  b_output_samps.set_size(1, output_samps.size(1));
  loop_ub = output_samps.size(1);
  for (i = 0; i < loop_ub; i++) {
    b_output_samps[i] = (output_samps[i] == xtmp_im);
  }

  coder::eml_find(b_output_samps, (int *)&ij, b_w_time_domain);
  if (b_w_time_domain[1] != 1) {
    rtSizeEq1DError(1, 0, &g_emlrtECI);
  }

  if (output_samps.size(1) < 1) {
    rtDynamicBoundsError(output_samps.size(1), 1, output_samps.size(1),
                         &hb_emlrtBCI);
  }

  xtmp_re = -output_samps[output_samps.size(1) - 1] - (b_Fs -
    output_samps[output_samps.size(1) - 1]);
  w_time_domain.set_size(1, w_time_domain.size(1));
  xtmp_im = static_cast<double>(output_samps.size(1)) - static_cast<double>(ij);
  if (!(xtmp_im >= 0.0)) {
    rtNonNegativeError(xtmp_im, &w_emlrtDCI);
  }

  w_time_domain.set_size(w_time_domain.size(0), static_cast<int>(xtmp_im));
  xtmp_im = static_cast<double>(output_samps.size(1)) - static_cast<double>(ij);
  if (!(xtmp_im >= 0.0)) {
    rtNonNegativeError(xtmp_im, &x_emlrtDCI);
  }

  loop_ub = static_cast<int>(xtmp_im);
  for (i = 0; i < loop_ub; i++) {
    w_time_domain[i] = 1.0;
  }

  wrapper.set_size(1, ij + w_time_domain.size(1));
  for (i = 0; i < ij; i++) {
    wrapper[i] = 0.0;
  }

  loop_ub = w_time_domain.size(1);
  for (i = 0; i < loop_ub; i++) {
    wrapper[i + ij] = xtmp_re;
  }

  if ((wrapper.size(1) != output_samps.size(1)) && ((wrapper.size(1) != 1) &&
       (output_samps.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(wrapper.size(1), output_samps.size(1),
      &l_emlrtECI);
  }

  // Here we sort the output to set up to have an ascending order of frequency
  // to be similar to the centered frequency list used elsewhere in the
  // codebase for the STFT output.
  if (wrapper.size(1) == output_samps.size(1)) {
    b_Wf.set_size(wrapper.size(1));
    loop_ub = wrapper.size(1);
    for (i = 0; i < loop_ub; i++) {
      b_Wf[i] = wrapper[i] + output_samps[i];
    }
  } else {
    binary_expand_op(b_Wf, wrapper, output_samps);
  }

  coder::internal::sort(b_Wf, iidx);
  b_w_time_domain[0] = x_of_n.size(0);
  loop_ub = x_of_n.size(0);
  b_r.set_size(x_of_n.size(0), iidx.size(0));
  ij = iidx.size(0);
  for (i = 0; i < ij; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      if ((iidx[i] < 1) || (iidx[i] > static_cast<int>(rowStart))) {
        rtDynamicBoundsError(iidx[i], 1, static_cast<int>(rowStart),
                             &ib_emlrtBCI);
      }

      b_r[i1 + b_r.size(0) * i].re = stackedToeplitzMatrices[i1 +
        b_w_time_domain[0] * (iidx[i] - 1)].re;
      if ((iidx[i] < 1) || (iidx[i] > static_cast<int>(rowStart))) {
        rtDynamicBoundsError(iidx[i], 1, static_cast<int>(rowStart),
                             &ib_emlrtBCI);
      }

      b_r[i1 + b_r.size(0) * i].im = stackedToeplitzMatrices[i1 +
        b_w_time_domain[0] * (iidx[i] - 1)].im;
    }
  }

  coder::internal::validator_check_size(b_r, W);
  coder::internal::validator_check_size(b_Wf, Wf);
}

//
// SPECTRO Executes an STFT of x and sets up the wfmstst object
// for the waveform
//
// INPUTS:
//    obj     The waveform object
// OUTPUTS:
//    none
//
//             %%
//
// Arguments    : wfmstft *iobj_0
// Return Type  : void
//
void waveform::spectro(wfmstft *iobj_0)
{
  coder::array<creal_T, 2U> b_S;
  coder::array<creal_T, 2U> r;
  coder::array<creal_T, 2U> val;
  coder::array<creal32_T, 2U> S;
  coder::array<creal32_T, 2U> obj;
  coder::array<double, 1U> _in;
  coder::array<double, 1U> b__in;
  coder::array<double, 1U> b_tmp_data;
  coder::array<double, 1U> d_tmp_data;
  coder::array<double, 1U> e_tmp_data;
  coder::array<double, 1U> f_tmp_data;
  coder::array<float, 1U> local_time;
  coder::array<float, 1U> r1;
  double tmp_data[2000];
  double c_tmp_data[200];
  double n_est;
  int loop_ub;

  // WFMSTFT Constructs and returns an instance of this class
  //
  // An waveform object must be passed to this construction method
  // so that the constructor has access to the data vector, desired
  // overlap fraction, and priori pulse data, which is used to
  // develop the window sizes.
  // INPUTS:
  //    waveform_obj   A single waveform object with prior
  //                   dependent properties set.
  // OUTPUTS:
  //    obj             A wfmstft object
  //             %%
  //
  // The following are variable sized properties. To tell coder
  // that they may vary setup as a local variable size variable
  // first, then set.
  // Instructions on https://www.mathworks.com/help/simulink/ug/how-working-with-matlab-classes-is-different-for-code-generation.html
  // maxFs*maxpulsewidth
  // Now actually assign them
  r.set(nullptr, 0, 0);
  coder::internal::validator_check_size(r, val);
  iobj_0->S.set_size(val.size(0), val.size(1));
  loop_ub = val.size(0) * val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    iobj_0->S[i] = val[i];
  }

  b_tmp_data.set(&tmp_data[0], 0);
  coder::internal::validator_check_size(b_tmp_data, _in);
  iobj_0->t.set_size(_in.size(0));
  loop_ub = _in.size(0);
  for (int i{0}; i < loop_ub; i++) {
    iobj_0->t[i] = _in[i];
  }

  d_tmp_data.set(&c_tmp_data[0], 0);
  coder::internal::validator_check_size(d_tmp_data, _in);
  iobj_0->f.set_size(_in.size(0));
  loop_ub = _in.size(0);
  for (int i{0}; i < loop_ub; i++) {
    iobj_0->f[i] = _in[i];
  }

  e_tmp_data.set(&c_tmp_data[0], 0);
  coder::internal::validator_check_size(e_tmp_data, _in);
  iobj_0->psd.set_size(_in.size(0));
  loop_ub = _in.size(0);
  for (int i{0}; i < loop_ub; i++) {
    iobj_0->psd[i] = _in[i];
  }

  f_tmp_data.set(&c_tmp_data[0], 0);
  coder::internal::validator_check_size(f_tmp_data, _in);
  iobj_0->wind.set_size(_in.size(0));
  loop_ub = _in.size(0);
  for (int i{0}; i < loop_ub; i++) {
    iobj_0->wind[i] = _in[i];
  }

  iobj_0->dt = 0.0;
  iobj_0->T = 0.0;

  // wind = hann(waveform_obj.n_w,'periodic');
  // wind = tukeywin(waveform_obj.n_w,0.3);
  n_est = n_w;
  if (std::isinf(n_est) || std::isnan(n_est)) {
    b_rtErrorWithMessageID("N", r_emlrtRTEI.fName, r_emlrtRTEI.lineNo);
  }

  if (!(n_est >= 0.0)) {
    o_rtErrorWithMessageID(s_emlrtRTEI.fName, s_emlrtRTEI.lineNo);
  }

  if (n_est == std::floor(n_est)) {
    loop_ub = static_cast<int>(n_est);
  } else {
    loop_ub = static_cast<int>(std::round(n_est));
  }

  _in.set_size(loop_ub);
  for (int i{0}; i < loop_ub; i++) {
    _in[i] = 1.0;
  }

  b__in.set_size(_in.size(0));
  loop_ub = _in.size(0) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    b__in[i] = _in[i];
  }

  coder::internal::validator_check_size(b__in, _in);
  iobj_0->wind.set_size(_in.size(0));
  loop_ub = _in.size(0);
  for (int i{0}; i < loop_ub; i++) {
    iobj_0->wind[i] = _in[i];
  }

  obj.set_size(1, x.size(1));
  loop_ub = x.size(0) * x.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    obj[i] = x[i];
  }

  b__in.set_size(iobj_0->wind.size(0));
  loop_ub = iobj_0->wind.size(0) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    b__in[i] = iobj_0->wind[i];
  }

  ::coder::stft(obj, Fs, b__in, n_ol, n_w, S, r1, local_time);
  b__in.set_size(r1.size(0));
  loop_ub = r1.size(0);
  for (int i{0}; i < loop_ub; i++) {
    b__in[i] = r1[i];
  }

  coder::internal::validator_check_size(b__in, _in);
  iobj_0->f.set_size(_in.size(0));
  loop_ub = _in.size(0);
  for (int i{0}; i < loop_ub; i++) {
    iobj_0->f[i] = _in[i];
  }

  b_S.set_size(S.size(0), S.size(1));
  loop_ub = S.size(0) * S.size(1);
  for (int i{0}; i < loop_ub; i++) {
    b_S[i].re = S[i].re;
    b_S[i].im = S[i].im;
  }

  coder::internal::validator_check_size(b_S, val);
  iobj_0->S.set_size(val.size(0), val.size(1));
  loop_ub = val.size(0) * val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    iobj_0->S[i] = val[i];
  }

  //  Incoming x data in waveform is single precision, but sparse matrix multipliation later is only supported for double precision.
  _in.set_size(local_time.size(0));
  loop_ub = local_time.size(0);
  for (int i{0}; i < loop_ub; i++) {
    _in[i] = local_time[i] + t_0;
  }

  b__in.set_size(_in.size(0));
  loop_ub = _in.size(0) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    b__in[i] = _in[i];
  }

  coder::internal::validator_check_size(b__in, _in);
  iobj_0->t.set_size(_in.size(0));
  loop_ub = _in.size(0);
  for (int i{0}; i < loop_ub; i++) {
    iobj_0->t[i] = _in[i];
  }

  // Convert to global time of waveform. Double cast is needed because if x data in stft is single precision then the output t will be single as well.
  n_est = 1.0 / Fs;
  iobj_0->dt = n_est;
  n_est = n_w / Fs;
  iobj_0->T = n_est;
  iobj_0->updatepsd();

  // obj.psd = obj.dt^2/obj.T*mean(abs(obj.S).^2,2);% Sxx = dt^2/T*|xhat(f)|^2
  // Vestigial properties no longer used. Kept in case we want
  // to resurect them.
  // obj.wind_per_pulse = floor(waveform_obj.n_w/waveform_obj.n_p); %How many windows are needed to capture a pulse
  // obj.stft_steps_per_pulse = floor(waveform_obj.t_ws/waveform_obj.ps_pre.t_p);%How many stft steps are needed to capture a pulse
  stft = iobj_0;
}

//
// SPECTRO Executes an STFT of x and sets up the wfmstst object
// for the waveform
//
// INPUTS:
//    obj     The waveform object
// OUTPUTS:
//    none
//
//             %%
//
// Arguments    : wfmstft *iobj_0
// Return Type  : void
//
void b_waveform::spectro(wfmstft *iobj_0)
{
  coder::array<creal_T, 2U> b_S;
  coder::array<creal_T, 2U> r;
  coder::array<creal_T, 2U> val;
  coder::array<creal32_T, 2U> S;
  coder::array<creal32_T, 2U> obj;
  coder::array<double, 1U> _in;
  coder::array<double, 1U> b__in;
  coder::array<double, 1U> b_tmp_data;
  coder::array<double, 1U> d_tmp_data;
  coder::array<double, 1U> e_tmp_data;
  coder::array<double, 1U> f_tmp_data;
  coder::array<float, 1U> local_time;
  coder::array<float, 1U> r1;
  double tmp_data[2000];
  double c_tmp_data[200];
  double n_est;
  int loop_ub;

  // WFMSTFT Constructs and returns an instance of this class
  //
  // An waveform object must be passed to this construction method
  // so that the constructor has access to the data vector, desired
  // overlap fraction, and priori pulse data, which is used to
  // develop the window sizes.
  // INPUTS:
  //    waveform_obj   A single waveform object with prior
  //                   dependent properties set.
  // OUTPUTS:
  //    obj             A wfmstft object
  //             %%
  //
  // The following are variable sized properties. To tell coder
  // that they may vary setup as a local variable size variable
  // first, then set.
  // Instructions on https://www.mathworks.com/help/simulink/ug/how-working-with-matlab-classes-is-different-for-code-generation.html
  // maxFs*maxpulsewidth
  // Now actually assign them
  r.set(nullptr, 0, 0);
  coder::internal::validator_check_size(r, val);
  iobj_0->S.set_size(val.size(0), val.size(1));
  loop_ub = val.size(0) * val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    iobj_0->S[i] = val[i];
  }

  b_tmp_data.set(&tmp_data[0], 0);
  coder::internal::validator_check_size(b_tmp_data, _in);
  iobj_0->t.set_size(_in.size(0));
  loop_ub = _in.size(0);
  for (int i{0}; i < loop_ub; i++) {
    iobj_0->t[i] = _in[i];
  }

  d_tmp_data.set(&c_tmp_data[0], 0);
  coder::internal::validator_check_size(d_tmp_data, _in);
  iobj_0->f.set_size(_in.size(0));
  loop_ub = _in.size(0);
  for (int i{0}; i < loop_ub; i++) {
    iobj_0->f[i] = _in[i];
  }

  e_tmp_data.set(&c_tmp_data[0], 0);
  coder::internal::validator_check_size(e_tmp_data, _in);
  iobj_0->psd.set_size(_in.size(0));
  loop_ub = _in.size(0);
  for (int i{0}; i < loop_ub; i++) {
    iobj_0->psd[i] = _in[i];
  }

  f_tmp_data.set(&c_tmp_data[0], 0);
  coder::internal::validator_check_size(f_tmp_data, _in);
  iobj_0->wind.set_size(_in.size(0));
  loop_ub = _in.size(0);
  for (int i{0}; i < loop_ub; i++) {
    iobj_0->wind[i] = _in[i];
  }

  iobj_0->dt = 0.0;
  iobj_0->T = 0.0;

  // wind = hann(waveform_obj.n_w,'periodic');
  // wind = tukeywin(waveform_obj.n_w,0.3);
  n_est = n_w;
  if (std::isinf(n_est) || std::isnan(n_est)) {
    b_rtErrorWithMessageID("N", r_emlrtRTEI.fName, r_emlrtRTEI.lineNo);
  }

  if (!(n_est >= 0.0)) {
    o_rtErrorWithMessageID(s_emlrtRTEI.fName, s_emlrtRTEI.lineNo);
  }

  if (n_est == std::floor(n_est)) {
    loop_ub = static_cast<int>(n_est);
  } else {
    loop_ub = static_cast<int>(std::round(n_est));
  }

  _in.set_size(loop_ub);
  for (int i{0}; i < loop_ub; i++) {
    _in[i] = 1.0;
  }

  b__in.set_size(_in.size(0));
  loop_ub = _in.size(0) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    b__in[i] = _in[i];
  }

  coder::internal::validator_check_size(b__in, _in);
  iobj_0->wind.set_size(_in.size(0));
  loop_ub = _in.size(0);
  for (int i{0}; i < loop_ub; i++) {
    iobj_0->wind[i] = _in[i];
  }

  obj.set_size(1, x.size(1));
  loop_ub = x.size(0) * x.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    obj[i] = x[i];
  }

  b__in.set_size(iobj_0->wind.size(0));
  loop_ub = iobj_0->wind.size(0) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    b__in[i] = iobj_0->wind[i];
  }

  ::coder::stft(obj, Fs, b__in, n_ol, n_w, S, r1, local_time);
  b__in.set_size(r1.size(0));
  loop_ub = r1.size(0);
  for (int i{0}; i < loop_ub; i++) {
    b__in[i] = r1[i];
  }

  coder::internal::validator_check_size(b__in, _in);
  iobj_0->f.set_size(_in.size(0));
  loop_ub = _in.size(0);
  for (int i{0}; i < loop_ub; i++) {
    iobj_0->f[i] = _in[i];
  }

  b_S.set_size(S.size(0), S.size(1));
  loop_ub = S.size(0) * S.size(1);
  for (int i{0}; i < loop_ub; i++) {
    b_S[i].re = S[i].re;
    b_S[i].im = S[i].im;
  }

  coder::internal::validator_check_size(b_S, val);
  iobj_0->S.set_size(val.size(0), val.size(1));
  loop_ub = val.size(0) * val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    iobj_0->S[i] = val[i];
  }

  //  Incoming x data in waveform is single precision, but sparse matrix multipliation later is only supported for double precision.
  _in.set_size(local_time.size(0));
  loop_ub = local_time.size(0);
  for (int i{0}; i < loop_ub; i++) {
    _in[i] = local_time[i] + t_0;
  }

  b__in.set_size(_in.size(0));
  loop_ub = _in.size(0) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    b__in[i] = _in[i];
  }

  coder::internal::validator_check_size(b__in, _in);
  iobj_0->t.set_size(_in.size(0));
  loop_ub = _in.size(0);
  for (int i{0}; i < loop_ub; i++) {
    iobj_0->t[i] = _in[i];
  }

  // Convert to global time of waveform. Double cast is needed because if x data in stft is single precision then the output t will be single as well.
  n_est = 1.0 / Fs;
  iobj_0->dt = n_est;
  n_est = n_w / Fs;
  iobj_0->T = n_est;
  iobj_0->updatepsd();

  // obj.psd = obj.dt^2/obj.T*mean(abs(obj.S).^2,2);% Sxx = dt^2/T*|xhat(f)|^2
  // Vestigial properties no longer used. Kept in case we want
  // to resurect them.
  // obj.wind_per_pulse = floor(waveform_obj.n_w/waveform_obj.n_p); %How many windows are needed to capture a pulse
  // obj.stft_steps_per_pulse = floor(waveform_obj.t_ws/waveform_obj.ps_pre.t_p);%How many stft steps are needed to capture a pulse
  stft = iobj_0;
}

//
// File trailer for waveform.cpp
//
// [EOF]
//
