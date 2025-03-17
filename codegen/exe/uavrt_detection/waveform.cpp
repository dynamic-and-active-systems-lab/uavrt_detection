//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: waveform.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "waveform.h"
#include "abs.h"
#include "all.h"
#include "allOrAny.h"
#include "any1.h"
#include "assembleWq.h"
#include "assertCompatibleDims.h"
#include "assertValidSizeArg.h"
#include "blockedSummation.h"
#include "buildtimecorrelatormatrix.h"
#include "circshift.h"
#include "combineVectorElements.h"
#include "confirmpulses.h"
#include "exp.h"
#include "fft.h"
#include "fftshift.h"
#include "find.h"
#include "flipud.h"
#include "function_handle.h"
#include "horzcatStructList.h"
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
#include "mod.h"
#include "norm.h"
#include "pulsestats.h"
#include "rectwin.h"
#include "repetitionrejector.h"
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
#include "toc.h"
#include "toeplitz.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_internal_types.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "unaryMinOrMax.h"
#include "vecfind.h"
#include "weightingmatrix.h"
#include "wfmstft.h"
#include "coder_array.h"
#include <cmath>
#include <cstdio>

// Function Declarations
static void b_and(coder::array<boolean_T, 1U> &in1, const coder::array<boolean_T,
                  1U> &in2);
static void b_or(coder::array<boolean_T, 1U> &in1, const coder::array<boolean_T,
                 1U> &in2);
static void b_plus(coder::array<double, 2U> &in1, const coder::array<double, 2U>
                   &in2);
static void binary_expand_op_1(waveform *in1, const coder::array<double, 2U>
  &in2, const coder::array<double, 2U> &in3);
static void binary_expand_op_13(coder::array<boolean_T, 1U> &in1, const coder::
  array<boolean_T, 1U> &in2, const coder::array<boolean_T, 1U> &in3);
static void binary_expand_op_14(coder::array<boolean_T, 1U> &in1, const coder::
  array<boolean_T, 1U> &in2, const coder::array<boolean_T, 1U> &in3);
static void binary_expand_op_15(coder::array<boolean_T, 1U> &in1, const coder::
  array<double, 1U> &in2, int in3, const coder::array<double, 1U> &in4);
static void binary_expand_op_17(coder::array<double, 2U> &in1, const waveform
  *in2);
static void binary_expand_op_18(coder::array<double, 2U> &in1, const coder::
  array<double, 2U> &in2, const coder::array<double, 2U> &in3, int in4, int in5);
static void binary_expand_op_20(coder::array<boolean_T, 1U> &in1, const coder::
  array<boolean_T, 2U> &in2, const coder::array<boolean_T, 2U> &in3);
static void binary_expand_op_22(coder::array<double, 1U> &in1, const coder::
  array<boolean_T, 1U> &in2, const coder::array<boolean_T, 1U> &in3);
static void binary_expand_op_24(coder::array<boolean_T, 1U> &in1, const coder::
  array<double, 2U> &in2, const coder::array<double, 1U> &in3, const waveform
  *in4, const coder::array<double, 2U> &in5);
static void binary_expand_op_4(coder::array<double, 1U> &in1, const coder::array<
  boolean_T, 1U> &in2);
static void binary_expand_op_5(coder::array<boolean_T, 1U> &in1, const coder::
  array<double, 1U> &in2, const waveform *in3);
static void binary_expand_op_7(coder::array<double, 1U> &in1, const coder::array<
  double, 1U> &in2, const coder::array<boolean_T, 1U> &in3);
static void c_and(coder::array<boolean_T, 1U> &in1, const coder::array<boolean_T,
                  1U> &in2, const coder::array<boolean_T, 1U> &in3);
static void minus(coder::array<double, 2U> &in1, const coder::array<double, 2U>
                  &in2);
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
  static rtBoundsCheckInfo ab_emlrtBCI{ 660,// lineNo
    "timeSearchRange",                 // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo ac_emlrtBCI{ 993,// lineNo
    "S_cols",                          // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo ad_emlrtBCI{ 1194,// lineNo
    "msk",                             // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo ae_emlrtBCI{ 1252,// lineNo
    "t_found",                         // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo af_emlrtBCI{ 892,// lineNo
    "scores",                          // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo bb_emlrtBCI{ 662,// lineNo
    "timeSearchRange",                 // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo bc_emlrtBCI{ 993,// lineNo
    "S_cols",                          // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo bd_emlrtBCI{ 1194,// lineNo
    "msk",                             // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo be_emlrtBCI{ 1252,// lineNo
    "t_found",                         // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo bf_emlrtBCI{ 885,// lineNo
    "scores",                          // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo cb_emlrtBCI{ 662,// lineNo
    "timeSearchRange",                 // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo cc_emlrtBCI{ 1010,// lineNo
    "S_cols",                          // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo cd_emlrtBCI{ 1197,// lineNo
    "peak_ind",                        // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo ce_emlrtBCI{ 1255,// lineNo
    "freq_found",                      // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo cf_emlrtBCI{ 885,// lineNo
    "scores",                          // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo db_emlrtBCI{ 668,// lineNo
    "timeSearchRange",                 // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo dc_emlrtBCI{ 1160,// lineNo
    "msk",                             // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo dd_emlrtBCI{ 1199,// lineNo
    "peak_ind",                        // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo de_emlrtBCI{ 1256,// lineNo
    "f_bands",                         // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo df_emlrtBCI{ 732,// lineNo
    "freq_mask",                       // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo eb_emlrtBCI{ 669,// lineNo
    "timeSearchRange",                 // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo ec_emlrtBCI{ 1161,// lineNo
    "msk",                             // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo ed_emlrtBCI{ 1199,// lineNo
    "peak_ind",                        // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo ee_emlrtBCI{ 1248,// lineNo
    "cur_pl",                          // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo ef_emlrtBCI{ 732,// lineNo
    "freq_mask",                       // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo fb_emlrtBCI{ 672,// lineNo
    "timeSearchRange",                 // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo fc_emlrtBCI{ 1176,// lineNo
    "peak_masked_curr_scores",         // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo fd_emlrtBCI{ 1219,// lineNo
    "obj.Wf",                          // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo fe_emlrtBCI{ 1248,// lineNo
    "cur_pl",                          // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo ff_emlrtBCI{ 737,// lineNo
    "obj.Wf",                          // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo gb_emlrtBCI{ 672,// lineNo
    "timeBlinderVec",                  // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo gc_emlrtBCI{ 1073,// lineNo
    "sideband_msk",                    // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo gd_emlrtBCI{ 1237,// lineNo
    "S_cols",                          // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo ge_emlrtBCI{ 1258,// lineNo
    "cur_pl",                          // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo gf_emlrtBCI{ 737,// lineNo
    "obj.Wf",                          // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo hb_emlrtBCI{ 672,// lineNo
    "timeBlinderVec",                  // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo hc_emlrtBCI{ 1073,// lineNo
    "sideband_msk",                    // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo hd_emlrtBCI{ 1239,// lineNo
    "t_found_inds",                    // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo he_emlrtBCI{ 1258,// lineNo
    "cur_pl",                          // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo hf_emlrtBCI{ 558,// lineNo
    "obj.ps_pre.pl",                   // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo ib_emlrtBCI{ 728,// lineNo
    "obj.Wf",                          // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo ic_emlrtBCI{ 1075,// lineNo
    "sideband_msk",                    // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo id_emlrtBCI{ 1240,// lineNo
    "t_found",                         // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo ie_emlrtBCI{ 1259,// lineNo
    "scores",                          // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo if_emlrtBCI{ 582,// lineNo
    "obj.ps_pre.pl",                   // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo jb_emlrtBCI{ 728,// lineNo
    "obj.Wf",                          // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo jc_emlrtBCI{ 1075,// lineNo
    "sideband_msk",                    // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo jd_emlrtBCI{ 1240,// lineNo
    "obj.stft.t",                      // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo je_emlrtBCI{ 1259,// lineNo
    "thresh",                          // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo jf_emlrtBCI{ 587,// lineNo
    "obj.stft.t",                      // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo kb_emlrtBCI{ 821,// lineNo
    "S_cols",                          // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo kc_emlrtBCI{ 1077,// lineNo
    "sideband_msk",                    // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo kd_emlrtBCI{ 1240,// lineNo
    "obj.stft.t",                      // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo ke_emlrtBCI{ 1260,// lineNo
    "cur_pl",                          // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo kf_emlrtBCI{ 587,// lineNo
    "obj.stft.t",                      // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo lb_emlrtBCI{ 823,// lineNo
    "S_cols_for_mask",                 // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo lc_emlrtBCI{ 1098,// lineNo
    "bandwidth_of_peak",               // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo ld_emlrtBCI{ 1242,// lineNo
    "obj.Wf",                          // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo le_emlrtBCI{ 1260,// lineNo
    "cur_pl",                          // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo lf_emlrtBCI{ 592,// lineNo
    "obj.stft.t",                      // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo mb_emlrtBCI{ 830,// lineNo
    "S_cols_for_mask",                 // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo mc_emlrtBCI{ 1140,// lineNo
    "bandwidth_of_peak",               // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo md_emlrtBCI{ 1242,// lineNo
    "obj.Wf",                          // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo me_emlrtBCI{ 1195,// lineNo
    "indiv_msk",                       // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo mf_emlrtBCI{ 619,// lineNo
    "obj.stft.t",                      // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo nb_emlrtBCI{ 831,// lineNo
    "weightedSRowSubsMat",             // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo nc_emlrtBCI{ 1142,// lineNo
    "sideband_msk",                    // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo nd_emlrtBCI{ 1243,// lineNo
    "obj.Wf",                          // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo ne_emlrtBCI{ 1195,// lineNo
    "indiv_msk",                       // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo ob_emlrtBCI{ 833,// lineNo
    "indsOfBins",                      // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo oc_emlrtBCI{ 1143,// lineNo
    "sideband_msk",                    // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo od_emlrtBCI{ 1243,// lineNo
    "obj.Wf",                          // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo oe_emlrtBCI{ 1050,// lineNo
    "slope_val",                       // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo pb_emlrtBCI{ 837,// lineNo
    "binMaskMatrix",                   // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo pc_emlrtBCI{ 1110,// lineNo
    "bandwidth_of_peak",               // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo pd_emlrtBCI{ 1253,// lineNo
    "t_found",                         // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo pe_emlrtBCI{ 1050,// lineNo
    "slope_val",                       // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo qb_emlrtBCI{ 854,// lineNo
    "noisePSDAtZetas",                 // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo qc_emlrtBCI{ 1135,// lineNo
    "bandwidth_of_peak",               // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo qd_emlrtBCI{ 1254,// lineNo
    "t_found",                         // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo qe_emlrtBCI{ 1049,// lineNo
    "slope_val",                       // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo rb_emlrtBCI{ 855,// lineNo
    "obj.stft.f",                      // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo rc_emlrtBCI{ 1040,// lineNo
    "scores",                          // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo rd_emlrtBCI{ 1248,// lineNo
    "signalAmps",                      // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo re_emlrtBCI{ 1049,// lineNo
    "slope_val",                       // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo sb_emlrtBCI{ 855,// lineNo
    "obj.stft.f",                      // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo sc_emlrtBCI{ 1040,// lineNo
    "scores",                          // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo sd_emlrtBCI{ 1248,// lineNo
    "signalAmps",                      // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo se_emlrtBCI{ 1040,// lineNo
    "thresh",                          // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo tb_emlrtBCI{ 865,// lineNo
    "signalPSD",                       // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo tc_emlrtBCI{ 1039,// lineNo
    "scores",                          // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo td_emlrtBCI{ 1249,// lineNo
    "yw_max_all_freq",                 // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo te_emlrtBCI{ 1040,// lineNo
    "thresh",                          // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo ub_emlrtBCI{ 869,// lineNo
    "SNRdB",                           // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo uc_emlrtBCI{ 1039,// lineNo
    "scores",                          // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo ud_emlrtBCI{ 1249,// lineNo
    "yw_max_all_freq",                 // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo ue_emlrtBCI{ 1039,// lineNo
    "thresh",                          // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo vb_emlrtBCI{ 957,// lineNo
    "obj.Wf",                          // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo vc_emlrtBCI{ 1012,// lineNo
    "S_cols",                          // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo vd_emlrtBCI{ 1250,// lineNo
    "SNRdB",                           // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo ve_emlrtBCI{ 1039,// lineNo
    "thresh",                          // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo wb_emlrtBCI{ 962,// lineNo
    "thresh",                          // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo wc_emlrtBCI{ 1182,// lineNo
    "msk",                             // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo wd_emlrtBCI{ 1250,// lineNo
    "SNRdB",                           // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo we_emlrtBCI{ 893,// lineNo
    "scores",                          // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo xb_emlrtBCI{ 967,// lineNo
    "scores",                          // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo xc_emlrtBCI{ 1182,// lineNo
    "msk",                             // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo xd_emlrtBCI{ 1251,// lineNo
    "t_found",                         // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo xe_emlrtBCI{ 893,// lineNo
    "scores",                          // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo yb_emlrtBCI{ 978,// lineNo
    "peak",                            // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo yc_emlrtBCI{ 1185,// lineNo
    "msk",                             // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo yd_emlrtBCI{ 1251,// lineNo
    "t_found",                         // aName
    "waveform/findpulse"               // fName
  };

  static rtBoundsCheckInfo ye_emlrtBCI{ 892,// lineNo
    "scores",                          // aName
    "waveform/findpulse"               // fName
  };

  static rtDoubleCheckInfo ab_emlrtDCI{ 1023,// lineNo
    "waveform/findpulse"               // fName
  };

  static rtDoubleCheckInfo bb_emlrtDCI{ 1025,// lineNo
    "waveform/findpulse"               // fName
  };

  static rtDoubleCheckInfo cb_emlrtDCI{ 1026,// lineNo
    "waveform/findpulse"               // fName
  };

  static rtDoubleCheckInfo db_emlrtDCI{ 1073,// lineNo
    "waveform/findpulse"               // fName
  };

  static rtDoubleCheckInfo eb_emlrtDCI{ 1075,// lineNo
    "waveform/findpulse"               // fName
  };

  static rtDoubleCheckInfo fb_emlrtDCI{ 1077,// lineNo
    "waveform/findpulse"               // fName
  };

  static rtDoubleCheckInfo gb_emlrtDCI{ 1142,// lineNo
    "waveform/findpulse"               // fName
  };

  static rtDoubleCheckInfo hb_emlrtDCI{ 1143,// lineNo
    "waveform/findpulse"               // fName
  };

  static rtDoubleCheckInfo ib_emlrtDCI{ 1040,// lineNo
    "waveform/findpulse"               // fName
  };

  static rtDoubleCheckInfo jb_emlrtDCI{ 1039,// lineNo
    "waveform/findpulse"               // fName
  };

  static rtDoubleCheckInfo kb_emlrtDCI{ 1012,// lineNo
    "waveform/findpulse"               // fName
  };

  static rtDoubleCheckInfo lb_emlrtDCI{ 1240,// lineNo
    "waveform/findpulse"               // fName
  };

  static rtDoubleCheckInfo mb_emlrtDCI{ 1050,// lineNo
    "waveform/findpulse"               // fName
  };

  static rtDoubleCheckInfo nb_emlrtDCI{ 1049,// lineNo
    "waveform/findpulse"               // fName
  };

  static rtDoubleCheckInfo ob_emlrtDCI{ 1040,// lineNo
    "waveform/findpulse"               // fName
  };

  static rtDoubleCheckInfo pb_emlrtDCI{ 1039,// lineNo
    "waveform/findpulse"               // fName
  };

  static rtDoubleCheckInfo q_emlrtDCI{ 659,// lineNo
    "waveform/findpulse"               // fName
  };

  static rtDoubleCheckInfo r_emlrtDCI{ 659,// lineNo
    "waveform/findpulse"               // fName
  };

  static rtDoubleCheckInfo s_emlrtDCI{ 672,// lineNo
    "waveform/findpulse"               // fName
  };

  static rtDoubleCheckInfo t_emlrtDCI{ 672,// lineNo
    "waveform/findpulse"               // fName
  };

  static rtDoubleCheckInfo u_emlrtDCI{ 836,// lineNo
    "waveform/findpulse"               // fName
  };

  static rtDoubleCheckInfo v_emlrtDCI{ 836,// lineNo
    "waveform/findpulse"               // fName
  };

  static rtDoubleCheckInfo w_emlrtDCI{ 993,// lineNo
    "waveform/findpulse"               // fName
  };

  static rtDoubleCheckInfo x_emlrtDCI{ 1010,// lineNo
    "waveform/findpulse"               // fName
  };

  static rtDoubleCheckInfo y_emlrtDCI{ 1022,// lineNo
    "waveform/findpulse"               // fName
  };

  static rtEqualityCheckInfo ab_emlrtECI{ 1,// nDims
    887,                               // lineNo
    "waveform/findpulse"               // fName
  };

  static rtEqualityCheckInfo ac_emlrtECI{ -1,// nDims
    1240,                              // lineNo
    "waveform/findpulse"               // fName
  };

  static rtEqualityCheckInfo bb_emlrtECI{ 1,// nDims
    888,                               // lineNo
    "waveform/findpulse"               // fName
  };

  static rtEqualityCheckInfo cb_emlrtECI{ 1,// nDims
    889,                               // lineNo
    "waveform/findpulse"               // fName
  };

  static rtEqualityCheckInfo db_emlrtECI{ 1,// nDims
    890,                               // lineNo
    "waveform/findpulse"               // fName
  };

  static rtEqualityCheckInfo eb_emlrtECI{ 1,// nDims
    892,                               // lineNo
    "waveform/findpulse"               // fName
  };

  static rtEqualityCheckInfo fb_emlrtECI{ 1,// nDims
    893,                               // lineNo
    "waveform/findpulse"               // fName
  };

  static rtEqualityCheckInfo g_emlrtECI{ -1,// nDims
    660,                               // lineNo
    "waveform/findpulse"               // fName
  };

  static rtEqualityCheckInfo gb_emlrtECI{ 1,// nDims
    902,                               // lineNo
    "waveform/findpulse"               // fName
  };

  static rtEqualityCheckInfo h_emlrtECI{ 1,// nDims
    53,                                // lineNo
    "vecfind"                          // fName
  };

  static rtEqualityCheckInfo hb_emlrtECI{ 1,// nDims
    901,                               // lineNo
    "waveform/findpulse"               // fName
  };

  static rtEqualityCheckInfo i_emlrtECI{ 2,// nDims
    53,                                // lineNo
    "vecfind"                          // fName
  };

  static rtEqualityCheckInfo ib_emlrtECI{ 1,// nDims
    902,                               // lineNo
    "waveform/findpulse"               // fName
  };

  static rtEqualityCheckInfo j_emlrtECI{ 1,// nDims
    57,                                // lineNo
    "vecfind"                          // fName
  };

  static rtEqualityCheckInfo jb_emlrtECI{ 1,// nDims
    927,                               // lineNo
    "waveform/findpulse"               // fName
  };

  static rtEqualityCheckInfo k_emlrtECI{ 2,// nDims
    57,                                // lineNo
    "vecfind"                          // fName
  };

  static rtEqualityCheckInfo kb_emlrtECI{ 1,// nDims
    942,                               // lineNo
    "waveform/findpulse"               // fName
  };

  static rtEqualityCheckInfo l_emlrtECI{ 1,// nDims
    681,                               // lineNo
    "waveform/findpulse"               // fName
  };

  static rtEqualityCheckInfo lb_emlrtECI{ 1,// nDims
    942,                               // lineNo
    "waveform/findpulse"               // fName
  };

  static rtEqualityCheckInfo m_emlrtECI{ 2,// nDims
    681,                               // lineNo
    "waveform/findpulse"               // fName
  };

  static rtEqualityCheckInfo mb_emlrtECI{ 1,// nDims
    946,                               // lineNo
    "waveform/findpulse"               // fName
  };

  static rtEqualityCheckInfo n_emlrtECI{ 1,// nDims
    743,                               // lineNo
    "waveform/findpulse"               // fName
  };

  static rtEqualityCheckInfo nb_emlrtECI{ 1,// nDims
    974,                               // lineNo
    "waveform/findpulse"               // fName
  };

  static rtEqualityCheckInfo o_emlrtECI{ 1,// nDims
    752,                               // lineNo
    "waveform/findpulse"               // fName
  };

  static rtEqualityCheckInfo ob_emlrtECI{ 1,// nDims
    1039,                              // lineNo
    "waveform/findpulse"               // fName
  };

  static rtEqualityCheckInfo p_emlrtECI{ 1,// nDims
    839,                               // lineNo
    "waveform/findpulse"               // fName
  };

  static rtEqualityCheckInfo pb_emlrtECI{ 1,// nDims
    1040,                              // lineNo
    "waveform/findpulse"               // fName
  };

  static rtEqualityCheckInfo q_emlrtECI{ 2,// nDims
    839,                               // lineNo
    "waveform/findpulse"               // fName
  };

  static rtEqualityCheckInfo qb_emlrtECI{ 1,// nDims
    1163,                              // lineNo
    "waveform/findpulse"               // fName
  };

  static rtEqualityCheckInfo r_emlrtECI{ 1,// nDims
    844,                               // lineNo
    "waveform/findpulse"               // fName
  };

  static rtEqualityCheckInfo rb_emlrtECI{ 1,// nDims
    1162,                              // lineNo
    "waveform/findpulse"               // fName
  };

  static rtEqualityCheckInfo s_emlrtECI{ 2,// nDims
    844,                               // lineNo
    "waveform/findpulse"               // fName
  };

  static rtEqualityCheckInfo sb_emlrtECI{ 1,// nDims
    1160,                              // lineNo
    "waveform/findpulse"               // fName
  };

  static rtEqualityCheckInfo t_emlrtECI{ 1,// nDims
    852,                               // lineNo
    "waveform/findpulse"               // fName
  };

  static rtEqualityCheckInfo tb_emlrtECI{ -1,// nDims
    1160,                              // lineNo
    "waveform/findpulse"               // fName
  };

  static rtEqualityCheckInfo u_emlrtECI{ 2,// nDims
    852,                               // lineNo
    "waveform/findpulse"               // fName
  };

  static rtEqualityCheckInfo ub_emlrtECI{ -1,// nDims
    1182,                              // lineNo
    "waveform/findpulse"               // fName
  };

  static rtEqualityCheckInfo v_emlrtECI{ 1,// nDims
    864,                               // lineNo
    "waveform/findpulse"               // fName
  };

  static rtEqualityCheckInfo vb_emlrtECI{ 1,// nDims
    1185,                              // lineNo
    "waveform/findpulse"               // fName
  };

  static rtEqualityCheckInfo w_emlrtECI{ 2,// nDims
    864,                               // lineNo
    "waveform/findpulse"               // fName
  };

  static rtEqualityCheckInfo wb_emlrtECI{ 1,// nDims
    1186,                              // lineNo
    "waveform/findpulse"               // fName
  };

  static rtEqualityCheckInfo x_emlrtECI{ 1,// nDims
    884,                               // lineNo
    "waveform/findpulse"               // fName
  };

  static rtEqualityCheckInfo xb_emlrtECI{ 1,// nDims
    1187,                              // lineNo
    "waveform/findpulse"               // fName
  };

  static rtEqualityCheckInfo y_emlrtECI{ 1,// nDims
    885,                               // lineNo
    "waveform/findpulse"               // fName
  };

  static rtEqualityCheckInfo yb_emlrtECI{ 1,// nDims
    1187,                              // lineNo
    "waveform/findpulse"               // fName
  };

  coder::sparse Wq;
  coder::sparse serialRejectionMatrix;
  coder::array<creal_T, 2U> obj;
  coder::array<double, 2U> S_cols;
  coder::array<double, 2U> S_cols_for_mask;
  coder::array<double, 2U> b_S_cols;
  coder::array<double, 2U> b_excluded_freq_bands;
  coder::array<double, 2U> excluded_freq_bands;
  coder::array<double, 2U> r3;
  coder::array<double, 2U> refmat;
  coder::array<double, 2U> result;
  coder::array<double, 2U> searchmat;
  coder::array<double, 2U> signalPlusNoisePSD;
  coder::array<double, 2U> timeSearchRange;
  coder::array<double, 2U> yw_max_all_freq;
  coder::array<double, 1U> b_S_cols_for_mask;
  coder::array<double, 1U> b_varargin_1_data;
  coder::array<double, 1U> bandwidth_of_peak;
  coder::array<double, 1U> curr_scores;
  coder::array<double, 1U> n_diff_check_back;
  coder::array<double, 1U> n_diff_check_for;
  coder::array<double, 1U> n_diff_to_curr_pk;
  coder::array<double, 1U> scores;
  coder::array<double, 1U> timeBlinderVec;
  coder::array<int, 2U> r6;
  coder::array<int, 2U> r7;
  coder::array<int, 1U> r2;
  coder::array<int, 1U> r5;
  coder::array<boolean_T, 2U> msk;
  coder::array<boolean_T, 2U> r;
  coder::array<boolean_T, 2U> r1;
  coder::array<boolean_T, 1U> b_freq_mask;
  coder::array<boolean_T, 1U> excld_msk_vec;
  coder::array<boolean_T, 1U> freq_mask;
  coder::array<boolean_T, 1U> greater_than_next;
  coder::array<boolean_T, 1U> r4;
  coder::array<boolean_T, 1U> score_right_bndry;
  coder::array<boolean_T, 1U> slope_neg;
  coder::array<boolean_T, 1U> slope_pos;
  coder::array<boolean_T, 1U> slope_val;
  c_struct_T expl_temp;
  double t_srch_rng[2];
  double varargin_1_data[2];
  double a;
  double b_J;
  double b_M;
  double b_N;
  double naive_wind_end;
  double naive_wind_end_tmp;
  double previousToc;
  double stft_dt;
  double t_lastknown;
  double timetol;
  double tip_temp;
  double tp_temp;
  double wind_end_data;
  double wind_start_data;
  int iv[2];
  int sizes[2];
  int b_loop_ub;
  int b_loop_ub_tmp;
  int c_loop_ub;
  int d_loop_ub;
  int e_loop_ub;
  int f_loop_ub;
  int g_loop_ub;
  int i;
  int i1;
  int i10;
  int i11;
  int i2;
  int i3;
  int i4;
  int i5;
  int i6;
  int i7;
  int i8;
  int i9;
  int ii_data;
  int inds_bkwd_2_next_valley_data;
  int input_sizes_idx_1;
  int loop_ub;
  int loop_ub_tmp;
  int nRowsOfS;
  int n_freqs_tmp;
  unsigned int p;
  int wind_end_size;
  int wind_start_size;
  boolean_T freqModWarningFlag;
  boolean_T t9_con_dec;
  std::printf("FINDING PULSES...\n");
  std::fflush(stdout);
  previousToc = coder::toc();
  std::printf("\t Setting up parameter for finding pulses  ...\n");
  std::fflush(stdout);
  if (excluded_freq_bands_in.size(0) == 0) {
    excluded_freq_bands.set_size(1, 2);
    excluded_freq_bands[0] = rtInf;
    excluded_freq_bands[1] = rtMinusInf;
  } else {
    excluded_freq_bands.set_size(excluded_freq_bands_in.size(0), 2);
    loop_ub_tmp = excluded_freq_bands_in.size(0) << 1;
    for (i = 0; i < loop_ub_tmp; i++) {
      excluded_freq_bands[i] = excluded_freq_bands_in[i];
    }
  }

  // Get relavent variables and rename for readable code.
  b_N = N;
  b_M = M;
  b_J = J;

  // Define naive search window for pulse 1
  naive_wind_end_tmp = b_N + b_M;
  naive_wind_end = naive_wind_end_tmp + b_J;

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
    wind_end_size = 1;
    wind_end_data = naive_wind_end;

    // INFORMED SEARCH BUT NOT PRIORI FOR START TIME
  } else {
    if (coder::internal::f_strcmp(time_searchtype_data, time_searchtype_size)) {
      i = ps_pre->pl.size(1);
      if (i < 1) {
        rtDynamicBoundsError(1, 1, i, hf_emlrtBCI);
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
      rtDynamicBoundsError(i1, 1, i, if_emlrtBCI);
    }

    t_lastknown = ps_pre->pl[i1 - 1].t_0;
    tp_temp = ps_pre->t_p;

    // If the last pulse identified occured in this segement, use
    // it to downselect the first pulse search range.
    // Time steps in the STFT windows:
    i = stft->t.size(0);
    if (i < 2) {
      rtDynamicBoundsError(2, 1, i, jf_emlrtBCI);
    }

    i = stft->t.size(0);
    if (i < 1) {
      rtDynamicBoundsError(1, 1, i, kf_emlrtBCI);
    }

    stft_dt = stft->t[1] - stft->t[0];

    // IF LAST SEGMENT'S LAST PULSE ALSO LIVES IN THIS SEGMENT
    // BECAUSE OF OVERLAP:
    timetol = n_ws / Fs;
    i = stft->t.size(0);
    if (i < 1) {
      rtDynamicBoundsError(1, 1, i, lf_emlrtBCI);
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
      wind_end_data = stft_dt / 2.0;
      bandwidth_of_peak.set_size(stft->t.size(0));
      loop_ub = stft->t.size(0);
      for (i = 0; i < loop_ub; i++) {
        bandwidth_of_peak[i] = (stft->t[i] - wind_end_data) - t_lastknown;
      }

      coder::b_abs(bandwidth_of_peak, timeBlinderVec);
      loop_ub = timeBlinderVec.size(0);
      score_right_bndry.set_size(timeBlinderVec.size(0));
      for (i = 0; i < loop_ub; i++) {
        score_right_bndry[i] = (timeBlinderVec[i] <= timetol);
      }

      input_sizes_idx_1 = coder::c_eml_find(score_right_bndry, (int *)&ii_data);
      wind_start_size = input_sizes_idx_1;
      for (i = 0; i < input_sizes_idx_1; i++) {
        wind_start_data = ii_data;
      }

      t_lastknown += tp_temp;
      bandwidth_of_peak.set_size(stft->t.size(0));
      loop_ub = stft->t.size(0);
      for (i = 0; i < loop_ub; i++) {
        bandwidth_of_peak[i] = (stft->t[i] - wind_end_data) - t_lastknown;
      }

      coder::b_abs(bandwidth_of_peak, timeBlinderVec);
      loop_ub = timeBlinderVec.size(0);
      score_right_bndry.set_size(timeBlinderVec.size(0));
      for (i = 0; i < loop_ub; i++) {
        score_right_bndry[i] = (timeBlinderVec[i] <= timetol);
      }

      input_sizes_idx_1 = coder::d_eml_find(score_right_bndry, (int *)&ii_data);
      wind_end_size = input_sizes_idx_1;
      for (i = 0; i < input_sizes_idx_1; i++) {
        wind_end_data = ii_data;
      }

      // IF LAST SEGMENT'S LAST PULSE DOESN'T LIVE IN THIS SEGMENT:
    } else {
      // Project forward one pulse in time with
      // +/-2M uncertainty in search range.
      tip_temp = ps_pre->t_ip;
      a = ps_pre->t_ipu;
      tp_temp = t_lastknown + tip_temp;

      // +tp_temp/2;
      // These are the times of the START OF THE PULSE...not
      // the center. This is why we have stft_dt/2 terms in
      // subsequent equations.
      t_srch_rng[0] = -a + tp_temp;
      t_srch_rng[1] = a + tp_temp;
      i = stft->t.size(0);
      if (i < 1) {
        rtDynamicBoundsError(1, 1, i, mf_emlrtBCI);
      }

      if (t_srch_rng[0] < stft->t[0] - stft_dt / 2.0) {
        // If for some reason the last known pulse is more
        // that one pulse repetition interval away from the
        // current waveform start time, use the naive search
        // range.
        std::printf("UAV-RT: Requested informed search, but the last know pulse is more that one interpulse time away from the current segment start "
                    "time. This means the algorithm would have to project forward by more than one pulse repetition interval. This is not supported. "
                    "The naive search method will be used.");
        std::fflush(stdout);
        wind_start_size = 1;
        wind_start_data = 1.0;
        wind_end_size = 1;
        wind_end_data = naive_wind_end;
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
        wind_end_data = stft_dt / 2.0;
        bandwidth_of_peak.set_size(stft->t.size(0));
        loop_ub = stft->t.size(0);
        for (i = 0; i < loop_ub; i++) {
          bandwidth_of_peak[i] = (stft->t[i] - wind_end_data) - t_srch_rng[0];
        }

        coder::b_abs(bandwidth_of_peak, timeBlinderVec);
        loop_ub = timeBlinderVec.size(0);
        score_right_bndry.set_size(timeBlinderVec.size(0));
        for (i = 0; i < loop_ub; i++) {
          score_right_bndry[i] = (timeBlinderVec[i] <= timetol);
        }

        input_sizes_idx_1 = coder::c_eml_find(score_right_bndry, (int *)&ii_data);
        wind_start_size = input_sizes_idx_1;
        for (i = 0; i < input_sizes_idx_1; i++) {
          wind_start_data = ii_data;
        }

        bandwidth_of_peak.set_size(stft->t.size(0));
        loop_ub = stft->t.size(0);
        for (i = 0; i < loop_ub; i++) {
          bandwidth_of_peak[i] = (stft->t[i] - wind_end_data) - t_srch_rng[1];
        }

        coder::b_abs(bandwidth_of_peak, timeBlinderVec);
        loop_ub = timeBlinderVec.size(0);
        score_right_bndry.set_size(timeBlinderVec.size(0));
        for (i = 0; i < loop_ub; i++) {
          score_right_bndry[i] = (timeBlinderVec[i] <= timetol);
        }

        input_sizes_idx_1 = coder::d_eml_find(score_right_bndry, (int *)&ii_data);
        wind_end_size = input_sizes_idx_1;
        for (i = 0; i < input_sizes_idx_1; i++) {
          wind_end_data = ii_data;
        }
      }
    }
  }

  if (wind_start_size == 0) {
    std::printf("UAV-RT: An error occured when trying to determine a time window search range based on prior information. Defaulting to naive sea"
                "rch.\n");
    std::fflush(stdout);
    wind_start_data = 1.0;
    wind_end_size = 1;
    wind_end_data = naive_wind_end;
  }

  // Build a time search range matrix with one row for each pulse
  // The first column is the first window where that pulse might
  // live in the S matrix, and the second column is the last window
  // where that pulse might live in the S matrix.
  if (!(K >= 0.0)) {
    rtNonNegativeError(K, q_emlrtDCI);
  }

  if (K != static_cast<int>(std::floor(K))) {
    rtIntegerError(K, r_emlrtDCI);
  }

  a = K;
  timeSearchRange.set_size(static_cast<int>(a), 2);
  loop_ub_tmp = static_cast<int>(a) << 1;
  for (i = 0; i < loop_ub_tmp; i++) {
    timeSearchRange[i] = 0.0;
  }

  if (static_cast<int>(K) < 1) {
    rtDynamicBoundsError(1, 1, static_cast<int>(K), ab_emlrtBCI);
  }

  if (wind_end_size != 1) {
    fb_rtErrorWithMessageID(qb_emlrtRTEI.fName, qb_emlrtRTEI.lineNo);
  }

  result.set_size(1, 2);
  result[0] = wind_start_data;
  result[result.size(0)] = wind_end_data;
  sizes[0] = 1;
  sizes[1] = 2;
  rtSubAssignSizeCheck(&sizes[0], 2, result.size(), 2, g_emlrtECI);
  timeSearchRange[0] = result[0];
  timeSearchRange[timeSearchRange.size(0)] = result[1];
  i = static_cast<int>(K - 1.0);
  for (wind_start_size = 0; wind_start_size < i; wind_start_size++) {
    if (static_cast<int>(a) < 1) {
      rtDynamicBoundsError(1, 1, static_cast<int>(a), bb_emlrtBCI);
    }

    if ((static_cast<int>(static_cast<unsigned int>(wind_start_size) + 2U) < 1) ||
        (static_cast<int>(static_cast<unsigned int>(wind_start_size) + 2U) >
         static_cast<int>(a))) {
      rtDynamicBoundsError(static_cast<int>(static_cast<unsigned int>
        (wind_start_size) + 2U), 1, static_cast<int>(a), cb_emlrtBCI);
    }

    t_srch_rng[1] = timeSearchRange[timeSearchRange.size(0)] + (((static_cast<
      double>(wind_start_size) + 2.0) - 1.0) * naive_wind_end_tmp + b_J);
    timeSearchRange[wind_start_size + 1] = timeSearchRange[0] + (((static_cast<
      double>(wind_start_size) + 2.0) - 1.0) * (b_N - b_M) - b_J);
    timeSearchRange[(wind_start_size + timeSearchRange.size(0)) + 1] =
      t_srch_rng[1];
  }

  wind_end_size = stft->S.size(1);

  // Limit the search to ranges of time that will be in the sftf
  // matrix
  for (wind_start_size = 0; wind_start_size < loop_ub_tmp; wind_start_size++) {
    if (timeSearchRange[wind_start_size] > wind_end_size) {
      if (wind_start_size > loop_ub_tmp - 1) {
        rtDynamicBoundsError(wind_start_size, 0, loop_ub_tmp - 1, db_emlrtBCI);
      }

      timeSearchRange[wind_start_size] = wind_end_size;
    }
  }

  for (wind_start_size = 0; wind_start_size < loop_ub_tmp; wind_start_size++) {
    if (timeSearchRange[wind_start_size] < 1.0) {
      if (wind_start_size > loop_ub_tmp - 1) {
        rtDynamicBoundsError(wind_start_size, 0, loop_ub_tmp - 1, eb_emlrtBCI);
      }

      timeSearchRange[wind_start_size] = 1.0;
    }
  }

  timeBlinderVec.set_size(wind_end_size);
  for (i = 0; i < wind_end_size; i++) {
    timeBlinderVec[i] = 0.0;
  }

  i = static_cast<int>(K);
  for (wind_start_size = 0; wind_start_size < i; wind_start_size++) {
    if ((static_cast<int>(static_cast<unsigned int>(wind_start_size) + 1U) < 1) ||
        (static_cast<int>(static_cast<unsigned int>(wind_start_size) + 1U) >
         static_cast<int>(a))) {
      rtDynamicBoundsError(static_cast<int>(static_cast<unsigned int>
        (wind_start_size) + 1U), 1, static_cast<int>(a), fb_emlrtBCI);
    }

    tip_temp = timeSearchRange[wind_start_size];
    tp_temp = timeSearchRange[wind_start_size + timeSearchRange.size(0)];
    if (tip_temp > tp_temp) {
      i1 = 0;
      ii_data = 0;
    } else {
      if (tip_temp != static_cast<int>(std::floor(tip_temp))) {
        rtIntegerError(tip_temp, s_emlrtDCI);
      }

      if ((static_cast<int>(tip_temp) < 1) || (static_cast<int>(tip_temp) >
           wind_end_size)) {
        rtDynamicBoundsError(static_cast<int>(tip_temp), 1, wind_end_size,
                             gb_emlrtBCI);
      }

      i1 = static_cast<int>(tip_temp) - 1;
      if (tp_temp != static_cast<int>(std::floor(tp_temp))) {
        rtIntegerError(tp_temp, t_emlrtDCI);
      }

      if ((static_cast<int>(tp_temp) < 1) || (static_cast<int>(tp_temp) >
           wind_end_size)) {
        rtDynamicBoundsError(static_cast<int>(tp_temp), 1, wind_end_size,
                             hb_emlrtBCI);
      }

      ii_data = static_cast<int>(tp_temp);
    }

    loop_ub = ii_data - i1;
    for (ii_data = 0; ii_data < loop_ub; ii_data++) {
      timeBlinderVec[i1 + ii_data] = 1.0;
    }
  }

  // Build the excluded frequency mask
  // False where we want to exclude
  // VECFIND creates a logical matrix based on the input operator comparing a
  // reference vector and a vector to be compared.
  //    This function can be used to do comparison operations of vectors of
  //    difference sizes. Comparing a single to a vector work natively
  //    in Matlab and create a resulting logic vector, i.e. [1 3 5]>4 outputs
  //    [0 0 1]. Many cases though require comparison of a vector to all the
  //    elements of another. i.e. [1 3 5]>[2 4] would ask which elements of
  //    [1 3 5] are greater than 2 and which are greater than 4? This function
  //    produces an output matrix whose columns are the logicial comparion of
  //    the reference vector to each element of the search vector. Logicals for
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

  coder::b_repmat(b_excluded_freq_bands, static_cast<double>(Wf.size(0)),
                  searchmat);

  // outmat = eval(['refmat',logical_op_string,'searchmat']);
  if ((refmat.size(0) != searchmat.size(0)) && ((refmat.size(0) != 1) &&
       (searchmat.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(refmat.size(0), searchmat.size(0), h_emlrtECI);
  }

  if ((refmat.size(1) != searchmat.size(1)) && ((refmat.size(1) != 1) &&
       (searchmat.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(refmat.size(1), searchmat.size(1), i_emlrtECI);
  }

  if ((refmat.size(0) == searchmat.size(0)) && (refmat.size(1) == searchmat.size
       (1))) {
    r.set_size(refmat.size(0), refmat.size(1));
    loop_ub_tmp = refmat.size(0) * refmat.size(1);
    for (i = 0; i < loop_ub_tmp; i++) {
      r[i] = (refmat[i] >= searchmat[i]);
    }
  } else {
    ge(r, refmat, searchmat);
  }

  // VECFIND creates a logical matrix based on the input operator comparing a
  // reference vector and a vector to be compared.
  //    This function can be used to do comparison operations of vectors of
  //    difference sizes. Comparing a single to a vector work natively
  //    in Matlab and create a resulting logic vector, i.e. [1 3 5]>4 outputs
  //    [0 0 1]. Many cases though require comparison of a vector to all the
  //    elements of another. i.e. [1 3 5]>[2 4] would ask which elements of
  //    [1 3 5] are greater than 2 and which are greater than 4? This function
  //    produces an output matrix whose columns are the logicial comparion of
  //    the reference vector to each element of the search vector. Logicals for
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
  b_excluded_freq_bands.set_size(1, excluded_freq_bands.size(0));
  for (i = 0; i < loop_ub; i++) {
    b_excluded_freq_bands[i] = excluded_freq_bands[i + excluded_freq_bands.size
      (0)];
  }

  coder::b_repmat(b_excluded_freq_bands, static_cast<double>(Wf.size(0)),
                  searchmat);

  // outmat = eval(['refmat',logical_op_string,'searchmat']);
  if ((refmat.size(0) != searchmat.size(0)) && ((refmat.size(0) != 1) &&
       (searchmat.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(refmat.size(0), searchmat.size(0), j_emlrtECI);
  }

  if ((refmat.size(1) != searchmat.size(1)) && ((refmat.size(1) != 1) &&
       (searchmat.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(refmat.size(1), searchmat.size(1), k_emlrtECI);
  }

  if ((refmat.size(0) == searchmat.size(0)) && (refmat.size(1) == searchmat.size
       (1))) {
    msk.set_size(refmat.size(0), refmat.size(1));
    loop_ub_tmp = refmat.size(0) * refmat.size(1);
    for (i = 0; i < loop_ub_tmp; i++) {
      msk[i] = (refmat[i] <= searchmat[i]);
    }
  } else {
    le(msk, refmat, searchmat);
  }

  if ((r.size(0) != msk.size(0)) && ((r.size(0) != 1) && (msk.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(r.size(0), msk.size(0), l_emlrtECI);
  }

  if ((r.size(1) != msk.size(1)) && ((r.size(1) != 1) && (msk.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(r.size(1), msk.size(1), m_emlrtECI);
  }

  if ((r.size(0) == msk.size(0)) && (r.size(1) == msk.size(1))) {
    r1.set_size(r.size(0), r.size(1));
    loop_ub_tmp = r.size(0) * r.size(1);
    for (i = 0; i < loop_ub_tmp; i++) {
      r1[i] = ((!r[i]) || (!msk[i]));
    }

    coder::all(r1, excld_msk_vec);
  } else {
    binary_expand_op_20(excld_msk_vec, r, msk);
  }

  // Build the priori frequency mask
  // Naive or informed frequency search
  t9_con_dec = coder::internal::f_strcmp(freq_searchtype_data,
    freq_searchtype_size);
  if (t9_con_dec) {
    freqModWarningFlag = false;
    score_right_bndry.set_size(Wf.size(0));
    loop_ub = Wf.size(0);
    for (i = 0; i < loop_ub; i++) {
      score_right_bndry[i] = (Wf[i] >= ps_pre->fstart);
    }

    input_sizes_idx_1 = coder::c_eml_find(score_right_bndry, (int *)&ii_data);
    for (i = 0; i < input_sizes_idx_1; i++) {
      wind_start_data = ii_data;
    }

    if (input_sizes_idx_1 == 0) {
      wind_start_data = 1.0;
      freqModWarningFlag = true;
    }

    score_right_bndry.set_size(Wf.size(0));
    loop_ub = Wf.size(0);
    for (i = 0; i < loop_ub; i++) {
      score_right_bndry[i] = (Wf[i] <= ps_pre->fend);
    }

    input_sizes_idx_1 = coder::d_eml_find(score_right_bndry, (int *)&ii_data);
    for (i = 0; i < input_sizes_idx_1; i++) {
      wind_end_data = ii_data;
    }

    if (input_sizes_idx_1 == 0) {
      wind_end_data = Wf.size(0);
      freqModWarningFlag = true;
    }

    if (freqModWarningFlag) {
      std::printf("UAVRT: Requested informed search, but previous segment does not contain a start and/or stop frequency, or those values produces "
                  "a search range outside the range of frequencies available. The frequency search range has been modified.");
      std::fflush(stdout);
    }

    i = Wf.size(0);
    i1 = static_cast<int>(wind_start_data);
    if ((wind_start_data < 1.0) || (i1 > i)) {
      rtDynamicBoundsError(static_cast<int>(wind_start_data), 1, i, ib_emlrtBCI);
    }

    i = Wf.size(0);
    ii_data = static_cast<int>(wind_end_data);
    if ((wind_end_data < 1.0) || (ii_data > i)) {
      rtDynamicBoundsError(static_cast<int>(wind_end_data), 1, i, jb_emlrtBCI);
    }

    std::printf("\t Frequency Search Range will be \t %f \t to \t %f.\n", Wf[
                static_cast<int>(wind_start_data) - 1], Wf[static_cast<int>
                (wind_end_data) - 1]);
    std::fflush(stdout);

    // (1) is for coder so it knows it is a scalar
    result.set_size(1, 2);
    result[0] = wind_start_data;
    result[result.size(0)] = wind_end_data;
    t_srch_rng[0] = Wf.size(0);
    freq_mask.set_size(Wf.size(0));
    loop_ub = Wf.size(0);
    for (i = 0; i < loop_ub; i++) {
      freq_mask[i] = false;
    }

    if (static_cast<int>(result[0]) > static_cast<int>(result[1])) {
      i1 = 0;
      ii_data = 0;
    } else {
      i = static_cast<int>(t_srch_rng[0]);
      if ((i1 < 1) || (i1 > i)) {
        rtDynamicBoundsError(i1, 1, static_cast<int>(t_srch_rng[0]), df_emlrtBCI);
      }

      i1--;
      if ((ii_data < 1) || (ii_data > i)) {
        rtDynamicBoundsError(ii_data, 1, static_cast<int>(t_srch_rng[0]),
                             ef_emlrtBCI);
      }
    }

    loop_ub = ii_data - i1;
    for (i = 0; i < loop_ub; i++) {
      freq_mask[i1 + i] = true;
    }
  } else {
    // Naive frequency search
    freq_mask.set_size(Wf.size(0));
    loop_ub = Wf.size(0);
    for (i = 0; i < loop_ub; i++) {
      freq_mask[i] = true;
    }

    i = Wf.size(0);
    if (i < 1) {
      rtDynamicBoundsError(1, 1, i, ff_emlrtBCI);
    }

    i = Wf.size(0);
    i1 = Wf.size(0);
    if ((i1 < 1) || (i1 > i)) {
      rtDynamicBoundsError(i1, 1, i, gf_emlrtBCI);
    }

    std::printf("\t Frequency Search Range will be \t %f \t to \t %f.\n", Wf[0],
                Wf[i1 - 1]);
    std::fflush(stdout);
  }

  // If using informed search and excluded frequencies overlap with
  // priori frequencies, warn the user.
  if (t9_con_dec) {
    loop_ub = excld_msk_vec.size(0);
    b_freq_mask.set_size(excld_msk_vec.size(0));
    for (i = 0; i < loop_ub; i++) {
      b_freq_mask[i] = !excld_msk_vec[i];
    }

    loop_ub = freq_mask.size(0);
    if ((freq_mask.size(0) != excld_msk_vec.size(0)) && ((freq_mask.size(0) != 1)
         && (excld_msk_vec.size(0) != 1))) {
      emlrtDimSizeImpxCheckR2021b(freq_mask.size(0), excld_msk_vec.size(0),
        n_emlrtECI);
    }

    if (freq_mask.size(0) == b_freq_mask.size(0)) {
      b_freq_mask.set_size(freq_mask.size(0));
      for (i = 0; i < loop_ub; i++) {
        b_freq_mask[i] = (freq_mask[i] && b_freq_mask[i]);
      }

      freqModWarningFlag = coder::internal::allOrAny_anonFcn1(b_freq_mask);
    } else {
      freqModWarningFlag = binary_expand_op_19(freq_mask, b_freq_mask);
    }

    if (freqModWarningFlag) {
      std::printf("UAV-RT: Using informed frequency search method and excluded frequencies. Some or all of the priori frequency band used for the i"
                  "nformed search overlaps with frequencies specified for exclusion from the search and thus will not be included.");
      std::fflush(stdout);
    }
  }

  // Combine the masks
  loop_ub = freq_mask.size(0);
  if ((freq_mask.size(0) != excld_msk_vec.size(0)) && ((freq_mask.size(0) != 1) &&
       (excld_msk_vec.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(freq_mask.size(0), excld_msk_vec.size(0),
      o_emlrtECI);
  }

  if (freq_mask.size(0) == excld_msk_vec.size(0)) {
    for (i = 0; i < loop_ub; i++) {
      freq_mask[i] = (freq_mask[i] && excld_msk_vec[i]);
    }
  } else {
    b_and(freq_mask, excld_msk_vec);
  }

  // Check that we actually have something to search
  freqModWarningFlag = coder::internal::allOrAny_anonFcn1(freq_mask);
  if (!freqModWarningFlag) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }

  // Determine the number of blocks to cut the data into. Should
  // always be the number of pulses currently looking for.
  stft_dt = (static_cast<double>(stft->S.size(1)) - 1.0) / naive_wind_end_tmp;
  stft_dt = std::floor(stft_dt);
  if (stft_dt == 0.0) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }

  tp_temp = coder::toc() - previousToc;
  std::printf("complete. Elapsed time: %f seconds \n", tp_temp);
  std::fflush(stdout);
  previousToc = coder::toc();
  std::printf("\t Building Time Correlation Matrix  ...");
  std::fflush(stdout);
  buildtimecorrelatormatrix(b_N, b_M, b_J, K, Wq);
  tp_temp = coder::toc() - previousToc;
  std::printf("complete. Elapsed time: %f seconds \n", tp_temp);
  std::fflush(stdout);
  previousToc = coder::toc();
  std::printf("\t Conducting incoherent summation step  ...");
  std::fflush(stdout);

  // [serialRejectionMatrix] = repetitionrejector(obj.stft.t, [2 3 5 10]);
  repetitionrejector(stft->t, serialRejectionMatrix);

  // Outputs Identity for testing purposes
  obj.set_size(W.size(1), W.size(0));
  loop_ub = W.size(0);
  for (i = 0; i < loop_ub; i++) {
    b_loop_ub = W.size(1);
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      obj[i1 + obj.size(0) * i].re = W[i + W.size(0) * i1].re;
      obj[i1 + obj.size(0) * i].im = -W[i + W.size(0) * i1].im;
    }
  }

  incohsumtoeplitz(freq_mask, obj, stft->S, serialRejectionMatrix,
                   timeBlinderVec, Wq, yw_max_all_freq, S_cols);

  // obj.TimeCorr.Wq(obj.K));
  tp_temp = coder::toc() - previousToc;
  std::printf("complete. Elapsed time: %f seconds \n", tp_temp);
  std::fflush(stdout);
  previousToc = coder::toc();
  std::printf("\t Running Peeling Algorithm...\n");
  std::fflush(stdout);

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
  n_freqs_tmp = yw_max_all_freq.size(0);

  // Calculate the sum of the yw values - the score/test statistic
  coder::sum(yw_max_all_freq, scores);
  inds_bkwd_2_next_valley_data = stft->S.size(1);
  nRowsOfS = stft->S.size(0);

  // The few lines below finds the noisePSD, but excludes regions
  // in time and frequency around possible detection. We do
  // detections as the zeta steps, but use the S matrix for PSD
  // estimates so there is a size mismatch that necessitates the
  // code below.
  // In cases when there are K+1 pulses in a waveform, the
  // detection method will pull the first K, but an extra pulse
  // will be in the S matrix and needs to be excluded from the
  // noise power consideration. Here we add another column to the
  // S_cols matrix that projects the next Kth pulse out by 1
  // interpulse duration (N) so that that K+1th pulse will be
  // masked as well.
  loop_ub = S_cols.size(1);
  if (S_cols.size(1) < 1) {
    rtDynamicBoundsError(S_cols.size(1), 1, S_cols.size(1), kb_emlrtBCI);
  }

  b_loop_ub = S_cols.size(0);
  timeBlinderVec.set_size(S_cols.size(0));
  for (i = 0; i < b_loop_ub; i++) {
    timeBlinderVec[i] = S_cols[i + S_cols.size(0) * (S_cols.size(1) - 1)] + N;
  }

  t9_con_dec = ((S_cols.size(0) != 0) && (S_cols.size(1) != 0));
  if (t9_con_dec) {
    wind_end_size = S_cols.size(0);
  } else if (timeBlinderVec.size(0) != 0) {
    wind_end_size = S_cols.size(0);
  } else {
    wind_end_size = S_cols.size(0);
  }

  if ((S_cols.size(0) != wind_end_size) && ((S_cols.size(0) != 0) &&
       (S_cols.size(1) != 0))) {
    fb_rtErrorWithMessageID(qb_emlrtRTEI.fName, qb_emlrtRTEI.lineNo);
  }

  if ((timeBlinderVec.size(0) != wind_end_size) && (timeBlinderVec.size(0) != 0))
  {
    fb_rtErrorWithMessageID(qb_emlrtRTEI.fName, qb_emlrtRTEI.lineNo);
  }

  freqModWarningFlag = (wind_end_size == 0);
  if (freqModWarningFlag || t9_con_dec) {
    input_sizes_idx_1 = S_cols.size(1);
  } else {
    input_sizes_idx_1 = 0;
  }

  if (freqModWarningFlag || (timeBlinderVec.size(0) != 0)) {
    sizes[1] = 1;
  } else {
    sizes[1] = 0;
  }

  i = input_sizes_idx_1 + sizes[1];
  refmat.set_size(wind_end_size, i);
  for (i1 = 0; i1 < input_sizes_idx_1; i1++) {
    for (ii_data = 0; ii_data < wind_end_size; ii_data++) {
      refmat[ii_data + refmat.size(0) * i1] = S_cols[ii_data + wind_end_size *
        i1];
    }
  }

  c_loop_ub = sizes[1];
  for (i1 = 0; i1 < c_loop_ub; i1++) {
    for (ii_data = 0; ii_data < wind_end_size; ii_data++) {
      refmat[ii_data + refmat.size(0) * input_sizes_idx_1] =
        timeBlinderVec[ii_data];
    }
  }

  S_cols_for_mask.set_size(wind_end_size, i);
  for (i1 = 0; i1 < input_sizes_idx_1; i1++) {
    for (ii_data = 0; ii_data < wind_end_size; ii_data++) {
      S_cols_for_mask[ii_data + S_cols_for_mask.size(0) * i1] = S_cols[ii_data +
        wind_end_size * i1];
    }
  }

  for (i1 = 0; i1 < c_loop_ub; i1++) {
    for (ii_data = 0; ii_data < wind_end_size; ii_data++) {
      S_cols_for_mask[ii_data + S_cols_for_mask.size(0) * input_sizes_idx_1] =
        timeBlinderVec[ii_data];
    }
  }

  input_sizes_idx_1 = stft->S.size(1);
  wind_end_size = refmat.size(0) * refmat.size(1);
  for (wind_start_size = 0; wind_start_size < wind_end_size; wind_start_size++)
  {
    if (refmat[wind_start_size] > input_sizes_idx_1) {
      if (wind_start_size > wind_end_size - 1) {
        rtDynamicBoundsError(wind_start_size, 0, wind_end_size - 1, lb_emlrtBCI);
      }

      S_cols_for_mask[wind_start_size] = input_sizes_idx_1;
    }
  }

  input_sizes_idx_1 = Wf.size(0);
  if (input_sizes_idx_1 < 1) {
    b_excluded_freq_bands.set_size(1, 0);
  } else {
    b_excluded_freq_bands.set_size(1, input_sizes_idx_1);
    c_loop_ub = input_sizes_idx_1 - 1;
    for (i1 = 0; i1 <= c_loop_ub; i1++) {
      b_excluded_freq_bands[i1] = static_cast<double>(i1) + 1.0;
    }
  }

  c_loop_ub = b_excluded_freq_bands.size(1);
  bandwidth_of_peak.set_size(b_excluded_freq_bands.size(1));
  for (i1 = 0; i1 < c_loop_ub; i1++) {
    bandwidth_of_peak[i1] = b_excluded_freq_bands[i1];
  }

  coder::repmat(bandwidth_of_peak, static_cast<double>(S_cols_for_mask.size(1)),
                refmat);

  // sub2ind doesn't support NaN values, so we focus here on those
  // that don't have NaN
  sizes[0] = S_cols.size(0);
  sizes[1] = i;
  iv[0] = (*(int (*)[2])S_cols_for_mask.size())[0];
  iv[1] = (*(int (*)[2])S_cols_for_mask.size())[1];
  coder::internal::b_indexShapeCheck(iv, sizes);
  input_sizes_idx_1 = 0;
  for (wind_start_size = 0; wind_start_size < wind_end_size; wind_start_size++)
  {
    if (!std::isnan(S_cols_for_mask[wind_start_size])) {
      input_sizes_idx_1++;
    }
  }

  r2.set_size(input_sizes_idx_1);
  input_sizes_idx_1 = 0;
  for (wind_start_size = 0; wind_start_size < wind_end_size; wind_start_size++)
  {
    if (!std::isnan(S_cols_for_mask[wind_start_size])) {
      r2[input_sizes_idx_1] = wind_start_size;
      input_sizes_idx_1++;
    }
  }

  loop_ub_tmp = r2.size(0);
  for (i1 = 0; i1 < loop_ub_tmp; i1++) {
    if (r2[i1] > wind_end_size - 1) {
      rtDynamicBoundsError(r2[i1], 0, wind_end_size - 1, mb_emlrtBCI);
    }
  }

  sizes[0] = S_cols.size(0);
  sizes[1] = i;
  iv[0] = (*(int (*)[2])refmat.size())[0];
  iv[1] = (*(int (*)[2])refmat.size())[1];
  coder::internal::b_indexShapeCheck(iv, sizes);
  input_sizes_idx_1 = refmat.size(0) * refmat.size(1);
  for (i = 0; i < loop_ub_tmp; i++) {
    if (r2[i] > input_sizes_idx_1 - 1) {
      rtDynamicBoundsError(r2[i], 0, input_sizes_idx_1 - 1, nb_emlrtBCI);
    }
  }

  tip_temp = static_cast<double>(Wf.size(0)) / static_cast<double>(nRowsOfS) *
    static_cast<double>(nRowsOfS);
  wind_end_size = static_cast<int>(tip_temp);
  sizes[0] = static_cast<int>(tip_temp);
  sizes[1] = inds_bkwd_2_next_valley_data;
  bandwidth_of_peak.set_size(r2.size(0));
  b_S_cols_for_mask.set_size(r2.size(0));
  for (i = 0; i < loop_ub_tmp; i++) {
    bandwidth_of_peak[i] = refmat[r2[i]];
    b_S_cols_for_mask[i] = S_cols_for_mask[r2[i]];
  }

  coder::internal::sub2ind(sizes, bandwidth_of_peak, b_S_cols_for_mask, r2);
  c_loop_ub = r2.size(0);
  timeBlinderVec.set_size(r2.size(0));
  for (i = 0; i < c_loop_ub; i++) {
    timeBlinderVec[i] = r2[i];
  }

  for (wind_start_size = 0; wind_start_size < c_loop_ub; wind_start_size++) {
    if (wind_start_size > timeBlinderVec.size(0) - 1) {
      rtDynamicBoundsError(wind_start_size, 0, timeBlinderVec.size(0) - 1,
                           ob_emlrtBCI);
    }
  }

  // binMaskMatrix will be a matrix of NaN at potential pulse
  // locations
  if (!(tip_temp >= 0.0)) {
    rtNonNegativeError(rtNaN, u_emlrtDCI);
  }

  if (tip_temp != static_cast<int>(std::floor(tip_temp))) {
    rtIntegerError(tip_temp, v_emlrtDCI);
  }

  refmat.set_size(wind_end_size, inds_bkwd_2_next_valley_data);
  loop_ub_tmp = static_cast<int>(tip_temp) * inds_bkwd_2_next_valley_data;
  for (i = 0; i < loop_ub_tmp; i++) {
    refmat[i] = 0.0;
  }

  input_sizes_idx_1 = 0;
  for (wind_start_size = 0; wind_start_size < c_loop_ub; wind_start_size++) {
    input_sizes_idx_1++;
  }

  r2.set_size(input_sizes_idx_1);
  input_sizes_idx_1 = 0;
  for (wind_start_size = 0; wind_start_size < c_loop_ub; wind_start_size++) {
    i = static_cast<int>(timeBlinderVec[wind_start_size]);
    if ((i < 1) || (i > loop_ub_tmp)) {
      rtDynamicBoundsError(i, 1, loop_ub_tmp, pb_emlrtBCI);
    }

    r2[input_sizes_idx_1] = i;
    input_sizes_idx_1++;
  }

  c_loop_ub = r2.size(0);
  for (i = 0; i < c_loop_ub; i++) {
    refmat[r2[i] - 1] = rtNaN;
  }

  // 0;
  // Now add some buffer around the potential pulse locations
  searchmat.set_size(wind_end_size, inds_bkwd_2_next_valley_data);
  for (i = 0; i < loop_ub_tmp; i++) {
    searchmat[i] = refmat[i];
  }

  coder::circshift(searchmat);
  if ((static_cast<int>(tip_temp) != searchmat.size(0)) && ((static_cast<int>
        (tip_temp) != 1) && (searchmat.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(static_cast<int>(tip_temp), searchmat.size(0),
      p_emlrtECI);
  }

  if ((inds_bkwd_2_next_valley_data != searchmat.size(1)) &&
      ((inds_bkwd_2_next_valley_data != 1) && (searchmat.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(inds_bkwd_2_next_valley_data, searchmat.size(1),
      q_emlrtECI);
  }

  if ((refmat.size(0) == searchmat.size(0)) && (refmat.size(1) == searchmat.size
       (1))) {
    searchmat.set_size(wind_end_size, inds_bkwd_2_next_valley_data);
    for (i = 0; i < loop_ub_tmp; i++) {
      searchmat[i] = refmat[i] + searchmat[i];
    }
  } else {
    b_plus(searchmat, refmat);
  }

  r3.set_size(refmat.size(0), refmat.size(1));
  loop_ub_tmp = refmat.size(0) * refmat.size(1);
  for (i = 0; i < loop_ub_tmp; i++) {
    r3[i] = refmat[i];
  }

  coder::b_circshift(r3);
  if ((searchmat.size(0) != r3.size(0)) && ((searchmat.size(0) != 1) && (r3.size
        (0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(searchmat.size(0), r3.size(0), p_emlrtECI);
  }

  if ((searchmat.size(1) != r3.size(1)) && ((searchmat.size(1) != 1) && (r3.size
        (1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(searchmat.size(1), r3.size(1), q_emlrtECI);
  }

  if ((searchmat.size(0) == r3.size(0)) && (searchmat.size(1) == r3.size(1))) {
    b_loop_ub_tmp = searchmat.size(0) * searchmat.size(1);
    for (i = 0; i < b_loop_ub_tmp; i++) {
      searchmat[i] = searchmat[i] + r3[i];
    }
  } else {
    plus(searchmat, r3);
  }

  r3.set_size(refmat.size(0), refmat.size(1));
  for (i = 0; i < loop_ub_tmp; i++) {
    r3[i] = refmat[i];
  }

  coder::c_circshift(r3);
  if ((searchmat.size(0) != r3.size(0)) && ((searchmat.size(0) != 1) && (r3.size
        (0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(searchmat.size(0), r3.size(0), p_emlrtECI);
  }

  if ((searchmat.size(1) != r3.size(1)) && ((searchmat.size(1) != 1) && (r3.size
        (1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(searchmat.size(1), r3.size(1), q_emlrtECI);
  }

  if ((searchmat.size(0) == r3.size(0)) && (searchmat.size(1) == r3.size(1))) {
    loop_ub_tmp = searchmat.size(0) * searchmat.size(1);
    for (i = 0; i < loop_ub_tmp; i++) {
      searchmat[i] = searchmat[i] + r3[i];
    }
  } else {
    plus(searchmat, r3);
  }

  coder::d_circshift(refmat);
  if ((searchmat.size(0) != refmat.size(0)) && ((searchmat.size(0) != 1) &&
       (refmat.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(searchmat.size(0), refmat.size(0), p_emlrtECI);
  }

  if ((searchmat.size(1) != refmat.size(1)) && ((searchmat.size(1) != 1) &&
       (refmat.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(searchmat.size(1), refmat.size(1), q_emlrtECI);
  }

  if ((searchmat.size(0) == refmat.size(0)) && (searchmat.size(1) == refmat.size
       (1))) {
    loop_ub_tmp = searchmat.size(0) * searchmat.size(1);
    for (i = 0; i < loop_ub_tmp; i++) {
      searchmat[i] = searchmat[i] + refmat[i];
    }
  } else {
    plus(searchmat, refmat);
  }

  r3.set_size(searchmat.size(0), searchmat.size(1));
  loop_ub_tmp = searchmat.size(0) * searchmat.size(1);
  for (i = 0; i < loop_ub_tmp; i++) {
    r3[i] = searchmat[i];
  }

  coder::e_circshift(r3);
  if ((searchmat.size(0) != r3.size(0)) && ((searchmat.size(0) != 1) && (r3.size
        (0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(searchmat.size(0), r3.size(0), r_emlrtECI);
  }

  if ((searchmat.size(1) != r3.size(1)) && ((searchmat.size(1) != 1) && (r3.size
        (1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(searchmat.size(1), r3.size(1), s_emlrtECI);
  }

  if ((searchmat.size(0) == r3.size(0)) && (searchmat.size(1) == r3.size(1))) {
    r3.set_size(searchmat.size(0), searchmat.size(1));
    for (i = 0; i < loop_ub_tmp; i++) {
      r3[i] = searchmat[i] + r3[i];
    }
  } else {
    b_plus(r3, searchmat);
  }

  coder::f_circshift(searchmat);
  if ((r3.size(0) != searchmat.size(0)) && ((r3.size(0) != 1) && (searchmat.size
        (0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(r3.size(0), searchmat.size(0), r_emlrtECI);
  }

  if ((r3.size(1) != searchmat.size(1)) && ((r3.size(1) != 1) && (searchmat.size
        (1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(r3.size(1), searchmat.size(1), s_emlrtECI);
  }

  if ((r3.size(0) == searchmat.size(0)) && (r3.size(1) == searchmat.size(1))) {
    signalPlusNoisePSD.set_size(r3.size(0), r3.size(1));
    loop_ub_tmp = r3.size(0) * r3.size(1);
    for (i = 0; i < loop_ub_tmp; i++) {
      signalPlusNoisePSD[i] = r3[i] + searchmat[i];
    }

    t_srch_rng[0] = nRowsOfS;
    t_srch_rng[1] = inds_bkwd_2_next_valley_data;
    coder::imresize(signalPlusNoisePSD, t_srch_rng, refmat);
  } else {
    binary_expand_op_18(refmat, r3, searchmat, nRowsOfS,
                        inds_bkwd_2_next_valley_data);
  }

  tp_temp = 1.0 / Fs;
  i = stft->S.size(0);
  if ((i != refmat.size(0)) && ((i != 1) && (refmat.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(i, refmat.size(0), t_emlrtECI);
  }

  i = stft->S.size(1);
  if ((i != refmat.size(1)) && ((i != 1) && (refmat.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(i, refmat.size(1), u_emlrtECI);
  }

  tp_temp = tp_temp * tp_temp / (n_w / Fs);
  if ((stft->S.size(0) == refmat.size(0)) && (stft->S.size(1) == refmat.size(1)))
  {
    obj.set_size(stft->S.size(0), stft->S.size(1));
    c_loop_ub = stft->S.size(0) * stft->S.size(1);
    for (i = 0; i < c_loop_ub; i++) {
      obj[i].re = stft->S[i].re + refmat[i];
      obj[i].im = stft->S[i].im;
    }

    coder::b_abs(obj, refmat);
  } else {
    binary_expand_op_17(refmat, this);
  }

  r3.set_size(refmat.size(0), refmat.size(1));
  loop_ub_tmp = refmat.size(0) * refmat.size(1);
  for (i = 0; i < loop_ub_tmp; i++) {
    tip_temp = refmat[i];
    r3[i] = tip_temp * tip_temp;
  }

  coder::mean(r3, timeBlinderVec);

  // Add since it is 0 where we expect noise and NaN where there might be a pulse
  c_loop_ub = timeBlinderVec.size(0);
  bandwidth_of_peak.set_size(timeBlinderVec.size(0));
  for (i = 0; i < c_loop_ub; i++) {
    bandwidth_of_peak[i] = tp_temp * timeBlinderVec[i];
  }

  coder::interp1(stft->f, bandwidth_of_peak, Wf, timeBlinderVec);
  wind_end_size = timeBlinderVec.size(0);
  for (wind_start_size = 0; wind_start_size < wind_end_size; wind_start_size++)
  {
    if (timeBlinderVec[wind_start_size] < 0.0) {
      if (wind_start_size > timeBlinderVec.size(0) - 1) {
        rtDynamicBoundsError(wind_start_size, 0, timeBlinderVec.size(0) - 1,
                             qb_emlrtBCI);
      }

      timeBlinderVec[wind_start_size] = 0.0;
    }
  }

  i = stft->f.size(0);
  if (i < 2) {
    rtDynamicBoundsError(2, 1, i, rb_emlrtBCI);
  }

  i = stft->f.size(0);
  if (i < 1) {
    rtDynamicBoundsError(1, 1, i, sb_emlrtBCI);
  }

  tip_temp = stft->f[1] - stft->f[0];

  // Not the delta f of the Wf vector, because the frequency bins are the same width, just with half bin steps %
  // Calculate the power at each of the S locations that were
  // selected by the incohsum function. Scores are the mag squared
  // S values. Mult by dt^2/T to get psd, then mult by the width of
  // the frequency bin to get power. We have to do this because the
  // psd in the stft object uses dt^2/T factor for the psd calc.
  c_loop_ub = yw_max_all_freq.size(1);
  signalPlusNoisePSD.set_size(yw_max_all_freq.size(0), yw_max_all_freq.size(1));
  loop_ub_tmp = yw_max_all_freq.size(0) * yw_max_all_freq.size(1);
  for (i = 0; i < loop_ub_tmp; i++) {
    signalPlusNoisePSD[i] = tp_temp * yw_max_all_freq[i];
  }

  // scores;
  coder::repmat(timeBlinderVec, static_cast<double>(yw_max_all_freq.size(1)), r3);
  if ((yw_max_all_freq.size(0) != r3.size(0)) && ((yw_max_all_freq.size(0) != 1)
       && (r3.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(yw_max_all_freq.size(0), r3.size(0), v_emlrtECI);
  }

  if ((yw_max_all_freq.size(1) != r3.size(1)) && ((yw_max_all_freq.size(1) != 1)
       && (r3.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(yw_max_all_freq.size(1), r3.size(1), w_emlrtECI);
  }

  if ((signalPlusNoisePSD.size(0) == r3.size(0)) && (signalPlusNoisePSD.size(1) ==
       r3.size(1))) {
    for (i = 0; i < loop_ub_tmp; i++) {
      signalPlusNoisePSD[i] = signalPlusNoisePSD[i] - r3[i];
    }
  } else {
    minus(signalPlusNoisePSD, r3);
  }

  wind_end_size = signalPlusNoisePSD.size(0) * signalPlusNoisePSD.size(1);
  for (wind_start_size = 0; wind_start_size < wind_end_size; wind_start_size++)
  {
    if (signalPlusNoisePSD[wind_start_size] < 0.0) {
      if (wind_start_size > wind_end_size - 1) {
        rtDynamicBoundsError(wind_start_size, 0, wind_end_size - 1, tb_emlrtBCI);
      }

      signalPlusNoisePSD[wind_start_size] = 0.0;
    }
  }

  // Can't have negative values
  searchmat.set_size(signalPlusNoisePSD.size(0), signalPlusNoisePSD.size(1));
  for (i = 0; i < wind_end_size; i++) {
    searchmat[i] = signalPlusNoisePSD[i] * tip_temp;
  }

  coder::b_sqrt(searchmat);
  coder::repmat(timeBlinderVec, static_cast<double>(yw_max_all_freq.size(1)),
                refmat);
  coder::internal::assertCompatibleDims(signalPlusNoisePSD, refmat);
  if ((signalPlusNoisePSD.size(0) == refmat.size(0)) && (signalPlusNoisePSD.size
       (1) == refmat.size(1))) {
    for (i = 0; i < wind_end_size; i++) {
      signalPlusNoisePSD[i] = signalPlusNoisePSD[i] / refmat[i];
    }
  } else {
    rdivide(signalPlusNoisePSD, refmat);
  }

  coder::b_log10(signalPlusNoisePSD);
  b_loop_ub_tmp = signalPlusNoisePSD.size(0) * signalPlusNoisePSD.size(1);
  for (i = 0; i < b_loop_ub_tmp; i++) {
    signalPlusNoisePSD[i] = 10.0 * signalPlusNoisePSD[i];
  }

  for (wind_start_size = 0; wind_start_size < b_loop_ub_tmp; wind_start_size++)
  {
    if (signalPlusNoisePSD[wind_start_size] == rtInf) {
      if (wind_start_size > b_loop_ub_tmp - 1) {
        rtDynamicBoundsError(wind_start_size, 0, b_loop_ub_tmp - 1, ub_emlrtBCI);
      }

      signalPlusNoisePSD[wind_start_size] = rtNaN;
    }
  }

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
  if (scores.size(0) < 1) {
    wind_start_size = 0;
  } else {
    wind_start_size = scores.size(0);
  }

  sizes[0] = 1;
  sizes[1] = wind_start_size;
  coder::internal::indexShapeCheck(scores.size(0), sizes);
  if (scores.size(0) < 2) {
    i = 0;
    i1 = 0;
  } else {
    i = 1;
    i1 = scores.size(0);
  }

  sizes[0] = 1;
  wind_end_size = i1 - i;
  sizes[1] = wind_end_size;
  coder::internal::indexShapeCheck(scores.size(0), sizes);
  timeBlinderVec.set_size(wind_end_size + 1);
  for (i1 = 0; i1 < wind_end_size; i1++) {
    timeBlinderVec[i1] = scores[i + i1];
  }

  timeBlinderVec[wind_end_size] = 0.0;
  if ((wind_start_size != wind_end_size + 1) && ((wind_start_size != 1) &&
       (wind_end_size + 1 != 1))) {
    emlrtDimSizeImpxCheckR2021b(wind_start_size, wind_end_size + 1, x_emlrtECI);
  }

  if (wind_start_size == timeBlinderVec.size(0)) {
    greater_than_next.set_size(wind_start_size);
    for (i = 0; i < wind_start_size; i++) {
      greater_than_next[i] = (scores[i] > timeBlinderVec[i]);
    }
  } else {
    binary_expand_op_15(greater_than_next, scores, wind_start_size,
                        timeBlinderVec);
  }

  if (scores.size(0) < 1) {
    wind_start_size = 0;
  } else {
    wind_start_size = scores.size(0);
  }

  sizes[0] = 1;
  sizes[1] = wind_start_size;
  coder::internal::indexShapeCheck(scores.size(0), sizes);
  if (scores.size(0) - 1 < 1) {
    wind_end_size = 0;
  } else {
    if (scores.size(0) < 1) {
      rtDynamicBoundsError(1, 1, scores.size(0), bf_emlrtBCI);
    }

    if ((scores.size(0) - 1 < 1) || (scores.size(0) - 1 > scores.size(0))) {
      rtDynamicBoundsError(scores.size(0) - 1, 1, scores.size(0), cf_emlrtBCI);
    }

    wind_end_size = scores.size(0) - 1;
  }

  sizes[0] = 1;
  sizes[1] = wind_end_size;
  coder::internal::indexShapeCheck(scores.size(0), sizes);
  timeBlinderVec.set_size(wind_end_size + 1);
  timeBlinderVec[0] = 0.0;
  for (i = 0; i < wind_end_size; i++) {
    timeBlinderVec[i + 1] = scores[i];
  }

  if ((wind_start_size != timeBlinderVec.size(0)) && ((wind_start_size != 1) &&
       (timeBlinderVec.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(wind_start_size, timeBlinderVec.size(0),
      y_emlrtECI);
  }

  if (wind_start_size == timeBlinderVec.size(0)) {
    excld_msk_vec.set_size(wind_start_size);
    for (i = 0; i < wind_start_size; i++) {
      excld_msk_vec[i] = (scores[i] > timeBlinderVec[i]);
    }
  } else {
    binary_expand_op_15(excld_msk_vec, scores, wind_start_size, timeBlinderVec);
  }

  wind_start_size = greater_than_next.size(0);
  slope_val.set_size(greater_than_next.size(0));
  for (i = 0; i < wind_start_size; i++) {
    slope_val[i] = !greater_than_next[i];
  }

  if ((greater_than_next.size(0) != excld_msk_vec.size(0)) &&
      ((greater_than_next.size(0) != 1) && (excld_msk_vec.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(greater_than_next.size(0), excld_msk_vec.size(0),
      ab_emlrtECI);
  }

  if (slope_val.size(0) == excld_msk_vec.size(0)) {
    slope_pos.set_size(greater_than_next.size(0));
    for (i = 0; i < wind_start_size; i++) {
      slope_pos[i] = (slope_val[i] && excld_msk_vec[i]);
    }
  } else {
    c_and(slope_pos, slope_val, excld_msk_vec);
  }

  wind_end_size = excld_msk_vec.size(0);
  b_freq_mask.set_size(excld_msk_vec.size(0));
  for (i = 0; i < wind_end_size; i++) {
    b_freq_mask[i] = !excld_msk_vec[i];
  }

  if ((greater_than_next.size(0) != excld_msk_vec.size(0)) &&
      ((greater_than_next.size(0) != 1) && (excld_msk_vec.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(greater_than_next.size(0), excld_msk_vec.size(0),
      bb_emlrtECI);
  }

  if (greater_than_next.size(0) == b_freq_mask.size(0)) {
    slope_neg.set_size(greater_than_next.size(0));
    for (i = 0; i < wind_start_size; i++) {
      slope_neg[i] = (greater_than_next[i] && b_freq_mask[i]);
    }
  } else {
    c_and(slope_neg, greater_than_next, b_freq_mask);
  }

  wind_start_size = slope_val.size(0);
  if ((slope_val.size(0) != b_freq_mask.size(0)) && ((slope_val.size(0) != 1) &&
       (b_freq_mask.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(slope_val.size(0), b_freq_mask.size(0),
      cb_emlrtECI);
  }

  if (slope_val.size(0) == b_freq_mask.size(0)) {
    for (i = 0; i < wind_start_size; i++) {
      slope_val[i] = (slope_val[i] && b_freq_mask[i]);
    }
  } else {
    b_and(slope_val, b_freq_mask);
  }

  wind_start_size = greater_than_next.size(0);
  if ((greater_than_next.size(0) != excld_msk_vec.size(0)) &&
      ((greater_than_next.size(0) != 1) && (excld_msk_vec.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(greater_than_next.size(0), excld_msk_vec.size(0),
      db_emlrtECI);
  }

  if (greater_than_next.size(0) == excld_msk_vec.size(0)) {
    for (i = 0; i < wind_start_size; i++) {
      greater_than_next[i] = (greater_than_next[i] && excld_msk_vec[i]);
    }
  } else {
    b_and(greater_than_next, excld_msk_vec);
  }

  if (scores.size(0) < 2) {
    i = 0;
    i1 = 0;
  } else {
    i = 1;
    i1 = scores.size(0);
  }

  sizes[0] = 1;
  wind_end_size = i1 - i;
  sizes[1] = wind_end_size;
  coder::internal::indexShapeCheck(scores.size(0), sizes);
  if (scores.size(0) - 1 < 1) {
    wind_start_size = 0;
  } else {
    if (scores.size(0) < 1) {
      rtDynamicBoundsError(1, 1, scores.size(0), ye_emlrtBCI);
    }

    if ((scores.size(0) - 1 < 1) || (scores.size(0) - 1 > scores.size(0))) {
      rtDynamicBoundsError(scores.size(0) - 1, 1, scores.size(0), af_emlrtBCI);
    }

    wind_start_size = scores.size(0) - 1;
  }

  sizes[0] = 1;
  sizes[1] = wind_start_size;
  coder::internal::indexShapeCheck(scores.size(0), sizes);
  b_freq_mask.set_size(wind_end_size);
  for (i1 = 0; i1 < wind_end_size; i1++) {
    b_freq_mask[i1] = !std::isnan(scores[i + i1]);
  }

  r4.set_size(wind_start_size);
  for (i = 0; i < wind_start_size; i++) {
    r4[i] = std::isnan(scores[i]);
  }

  if ((wind_end_size != r4.size(0)) && ((wind_end_size != 1) && (r4.size(0) != 1)))
  {
    emlrtDimSizeImpxCheckR2021b(wind_end_size, r4.size(0), eb_emlrtECI);
  }

  if (b_freq_mask.size(0) == r4.size(0)) {
    excld_msk_vec.set_size(b_freq_mask.size(0) + 1);
    excld_msk_vec[0] = true;
    for (i = 0; i < wind_end_size; i++) {
      excld_msk_vec[i + 1] = (b_freq_mask[i] && r4[i]);
    }
  } else {
    binary_expand_op_14(excld_msk_vec, b_freq_mask, r4);
  }

  if (scores.size(0) - 1 < 1) {
    wind_start_size = 0;
  } else {
    if (scores.size(0) < 1) {
      rtDynamicBoundsError(1, 1, scores.size(0), we_emlrtBCI);
    }

    if ((scores.size(0) - 1 < 1) || (scores.size(0) - 1 > scores.size(0))) {
      rtDynamicBoundsError(scores.size(0) - 1, 1, scores.size(0), xe_emlrtBCI);
    }

    wind_start_size = scores.size(0) - 1;
  }

  sizes[0] = 1;
  sizes[1] = wind_start_size;
  coder::internal::indexShapeCheck(scores.size(0), sizes);
  if (scores.size(0) < 2) {
    i = 0;
    i1 = 0;
  } else {
    i = 1;
    i1 = scores.size(0);
  }

  sizes[0] = 1;
  wind_end_size = i1 - i;
  sizes[1] = wind_end_size;
  coder::internal::indexShapeCheck(scores.size(0), sizes);
  b_freq_mask.set_size(wind_start_size);
  for (i1 = 0; i1 < wind_start_size; i1++) {
    b_freq_mask[i1] = !std::isnan(scores[i1]);
  }

  r4.set_size(wind_end_size);
  for (i1 = 0; i1 < wind_end_size; i1++) {
    r4[i1] = std::isnan(scores[i + i1]);
  }

  wind_start_size = b_freq_mask.size(0);
  if ((b_freq_mask.size(0) != wind_end_size) && ((b_freq_mask.size(0) != 1) &&
       (wind_end_size != 1))) {
    emlrtDimSizeImpxCheckR2021b(b_freq_mask.size(0), wind_end_size, fb_emlrtECI);
  }

  if (b_freq_mask.size(0) == r4.size(0)) {
    score_right_bndry.set_size(b_freq_mask.size(0) + 1);
    for (i = 0; i < wind_start_size; i++) {
      score_right_bndry[i] = (b_freq_mask[i] && r4[i]);
    }

    score_right_bndry[b_freq_mask.size(0)] = true;
  } else {
    binary_expand_op_13(score_right_bndry, b_freq_mask, r4);
  }

  // This deals with the frequency masking and some scores will be
  // NaN because they were excluded from consideration in the
  // incohsum processing. If the score is a left boundary
  // (frequencies lower were excluded) and the slope is negative,
  // this would be considered a peak. Visa-versa for right
  // boundaries.
  wind_start_size = excld_msk_vec.size(0);
  if ((excld_msk_vec.size(0) != slope_neg.size(0)) && ((excld_msk_vec.size(0) !=
        1) && (slope_neg.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(excld_msk_vec.size(0), slope_neg.size(0),
      gb_emlrtECI);
  }

  if (excld_msk_vec.size(0) == slope_neg.size(0)) {
    for (i = 0; i < wind_start_size; i++) {
      excld_msk_vec[i] = (excld_msk_vec[i] && slope_neg[i]);
    }
  } else {
    b_and(excld_msk_vec, slope_neg);
  }

  wind_start_size = greater_than_next.size(0);
  if ((greater_than_next.size(0) != excld_msk_vec.size(0)) &&
      ((greater_than_next.size(0) != 1) && (excld_msk_vec.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(greater_than_next.size(0), excld_msk_vec.size(0),
      hb_emlrtECI);
  }

  wind_end_size = score_right_bndry.size(0);
  if ((score_right_bndry.size(0) != slope_pos.size(0)) &&
      ((score_right_bndry.size(0) != 1) && (slope_pos.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(score_right_bndry.size(0), slope_pos.size(0),
      ib_emlrtECI);
  }

  if (greater_than_next.size(0) == excld_msk_vec.size(0)) {
    for (i = 0; i < wind_start_size; i++) {
      greater_than_next[i] = (greater_than_next[i] || excld_msk_vec[i]);
    }
  } else {
    b_or(greater_than_next, excld_msk_vec);
  }

  if (score_right_bndry.size(0) == slope_pos.size(0)) {
    for (i = 0; i < wind_end_size; i++) {
      score_right_bndry[i] = (score_right_bndry[i] && slope_pos[i]);
    }
  } else {
    b_and(score_right_bndry, slope_pos);
  }

  wind_start_size = greater_than_next.size(0);
  if ((greater_than_next.size(0) != score_right_bndry.size(0)) &&
      ((greater_than_next.size(0) != 1) && (score_right_bndry.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(greater_than_next.size(0),
      score_right_bndry.size(0), hb_emlrtECI);
  }

  if (greater_than_next.size(0) == score_right_bndry.size(0)) {
    for (i = 0; i < wind_start_size; i++) {
      greater_than_next[i] = (greater_than_next[i] || score_right_bndry[i]);
    }
  } else {
    b_or(greater_than_next, score_right_bndry);
  }

  // How many time windows difference do we considered the found
  // pulse to be the same as one found at a different frequency?
  // We'll say that if they are within two pulse time width of
  // each other they are the same pulse.
  naive_wind_end = 2.0 * n_p / n_ws;
  p = 1U;

  // Initilize a peak counter variable
  // Initially these are the same.
  // The peak and peak_ind variables are a vector of scores and the
  // frequency index of the identified peaks of the pulses. There
  // could only ever be n_freqs peaks, so we preallocate the
  // vectors to be that long, although there will typically be far
  // fever of them - ideally the number of tags in the signal.
  timeBlinderVec.set_size(yw_max_all_freq.size(0));
  peak_ind.set_size(yw_max_all_freq.size(0));
  bandwidth_of_peak.set_size(yw_max_all_freq.size(0));
  for (i = 0; i < n_freqs_tmp; i++) {
    timeBlinderVec[i] = 0.0;
    peak_ind[i] = 0.0;
    bandwidth_of_peak[i] = 0.0;
  }

  msk.set_size(yw_max_all_freq.size(0), yw_max_all_freq.size(0));
  b_loop_ub_tmp = yw_max_all_freq.size(0) * yw_max_all_freq.size(0);
  indiv_msk.set_size(yw_max_all_freq.size(0), yw_max_all_freq.size(0));
  for (i = 0; i < b_loop_ub_tmp; i++) {
    msk[i] = false;
    indiv_msk[i] = false;
  }

  // peak_masked_curr_scores is a vector of scores where only the
  // peaks have scores. All others (valleys, +slope, -slope) are
  // set to zero. As we identify peaks, they will also be set to
  // zero so that we can work our way through these peaks.
  wind_start_size = scores.size(0);
  if ((scores.size(0) != greater_than_next.size(0)) && ((scores.size(0) != 1) &&
       (greater_than_next.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(scores.size(0), greater_than_next.size(0),
      jb_emlrtECI);
  }

  if (scores.size(0) == greater_than_next.size(0)) {
    curr_scores.set_size(scores.size(0));
    for (i = 0; i < wind_start_size; i++) {
      curr_scores[i] = scores[i] * static_cast<double>(greater_than_next[i]);
    }
  } else {
    binary_expand_op_7(curr_scores, scores, greater_than_next);
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
  wind_start_size = curr_scores.size(0);
  i = thresh.threshVecFine.size(0);
  if ((curr_scores.size(0) != i) && ((curr_scores.size(0) != 1) && (i != 1))) {
    emlrtDimSizeImpxCheckR2021b(curr_scores.size(0), i, kb_emlrtECI);
  }

  if (curr_scores.size(0) == thresh.threshVecFine.size(0)) {
    b_freq_mask.set_size(curr_scores.size(0));
    for (i = 0; i < wind_start_size; i++) {
      b_freq_mask[i] = (curr_scores[i] >= thresh.threshVecFine[i]);
    }
  } else {
    binary_expand_op_5(b_freq_mask, curr_scores, this);
  }

  wind_start_size = curr_scores.size(0);
  if ((curr_scores.size(0) != b_freq_mask.size(0)) && ((curr_scores.size(0) != 1)
       && (b_freq_mask.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(curr_scores.size(0), b_freq_mask.size(0),
      lb_emlrtECI);
  }

  if (curr_scores.size(0) == b_freq_mask.size(0)) {
    for (i = 0; i < wind_start_size; i++) {
      curr_scores[i] = curr_scores[i] * static_cast<double>(b_freq_mask[i]);
    }
  } else {
    binary_expand_op_4(curr_scores, b_freq_mask);
  }

  // ------------------------------------------------
  // thresh_hold = thresh;thresh = interp1(obj.stft.f,thresh,Wf);
  wind_start_size = curr_scores.size(0);
  i = thresh.threshVecFine.size(0);
  if ((curr_scores.size(0) != i) && ((curr_scores.size(0) != 1) && (i != 1))) {
    emlrtDimSizeImpxCheckR2021b(curr_scores.size(0), i, mb_emlrtECI);
  }

  if (curr_scores.size(0) == thresh.threshVecFine.size(0)) {
    score_right_bndry.set_size(curr_scores.size(0));
    for (i = 0; i < wind_start_size; i++) {
      score_right_bndry[i] = (curr_scores[i] >= thresh.threshVecFine[i]);
    }

    freqModWarningFlag = coder::internal::allOrAny_anonFcn1(score_right_bndry);
  } else {
    freqModWarningFlag = binary_expand_op_8(curr_scores, this);
  }

  if (!freqModWarningFlag) {
    // all(peak_masked_curr_scores < thresh, 'all')%
    // peak_ind = [];
    peak_ind.set_size(1);
    peak_ind[0] = rtNaN;
    timeBlinderVec.set_size(1);

    // [];
  }

  // PRINT OUT FREQUENCIES, THRESHOLDS, AND SCORES BEFORE WE ENTER
  // INTO THE LOOP IN CASE IT CRASHES WE CAN STILL SEE THESE IT THE
  // LOGS.
  std::printf("Frequencies are:\n");
  std::fflush(stdout);
  i = Wf.size(0);
  for (wind_start_size = 0; wind_start_size < i; wind_start_size++) {
    i1 = Wf.size(0);
    if (wind_start_size + 1 > i1) {
      rtDynamicBoundsError(wind_start_size + 1, 1, i1, vb_emlrtBCI);
    }

    std::printf("%.6f,", Wf[wind_start_size]);
    std::fflush(stdout);
  }

  std::printf("\n");
  std::fflush(stdout);
  std::printf("Threshold vector is equal to:\n");
  std::fflush(stdout);
  i = thresh.threshVecFine.size(0);
  for (wind_start_size = 0; wind_start_size < i; wind_start_size++) {
    i1 = thresh.threshVecFine.size(0);
    if (wind_start_size + 1 > i1) {
      rtDynamicBoundsError(wind_start_size + 1, 1, i1, wb_emlrtBCI);
    }

    std::printf("%f,", thresh.threshVecFine[wind_start_size]);
    std::fflush(stdout);
  }

  std::printf("\n");
  std::fflush(stdout);
  std::printf("Scores vector is equal to:\n");
  std::fflush(stdout);
  i = scores.size(0);
  for (wind_start_size = 0; wind_start_size < i; wind_start_size++) {
    if (wind_start_size + 1 > i) {
      rtDynamicBoundsError(wind_start_size + 1, 1, i, xb_emlrtBCI);
    }

    std::printf("%f,", scores[wind_start_size]);
    std::fflush(stdout);
  }

  std::printf("\n");
  std::fflush(stdout);

  // Keep doing this loop below while there are scores that exceed
  // the threshold which aren't masked as a valley, +slope, -slope,
  // or previously identified peak/sideband.
  int exitg1;
  do {
    exitg1 = 0;
    wind_start_size = curr_scores.size(0);
    i = thresh.threshVecFine.size(0);
    if ((curr_scores.size(0) != i) && ((curr_scores.size(0) != 1) && (i != 1)))
    {
      emlrtDimSizeImpxCheckR2021b(curr_scores.size(0), i, nb_emlrtECI);
    }

    if (curr_scores.size(0) == thresh.threshVecFine.size(0)) {
      score_right_bndry.set_size(curr_scores.size(0));
      for (i = 0; i < wind_start_size; i++) {
        score_right_bndry[i] = (curr_scores[i] >= thresh.threshVecFine[i]);
      }

      freqModWarningFlag = coder::internal::allOrAny_anonFcn1(score_right_bndry);
    } else {
      freqModWarningFlag = binary_expand_op_8(curr_scores, this);
    }

    if (freqModWarningFlag) {
      // Identify the highest scoring peak of the currently
      // identifed scores.
      t9_con_dec = ((static_cast<int>(p) < 1) || (static_cast<int>(p) >
        timeBlinderVec.size(0)));
      if (t9_con_dec) {
        rtDynamicBoundsError(static_cast<int>(p), 1, timeBlinderVec.size(0),
                             yb_emlrtBCI);
      }

      timeBlinderVec[static_cast<int>(p) - 1] = coder::internal::maximum
        (curr_scores, input_sizes_idx_1);
      peak_ind[static_cast<int>(p) - 1] = input_sizes_idx_1;

      // Build a mask that highlights all the elements whose time
      // windows share (or are close) to any of the time windows
      // of the pulses associated with the current peak.
      i = static_cast<int>(stft_dt);
      if (static_cast<int>(stft_dt) - 1 >= 0) {
        d_loop_ub = b_loop_ub;
        e_loop_ub = n_freqs_tmp;
        a = peak_ind[static_cast<int>(p) - 1];
        if (a - 1.0 < 1.0) {
          i2 = 0;
          i3 = 1;
          i4 = -1;
        } else {
          if (a - 1.0 != static_cast<int>(a - 1.0)) {
            rtIntegerError(a - 1.0, pb_emlrtDCI);
          }

          i1 = thresh.threshVecFine.size(0);
          if ((static_cast<int>(a - 1.0) < 1) || (static_cast<int>(a - 1.0) > i1))
          {
            rtDynamicBoundsError(static_cast<int>(a - 1.0), 1, i1, ue_emlrtBCI);
          }

          i2 = static_cast<int>(a - 1.0) - 1;
          i3 = -1;
          i1 = thresh.threshVecFine.size(0);
          if (i1 < 1) {
            rtDynamicBoundsError(1, 1, i1, ve_emlrtBCI);
          }

          i4 = 0;
        }

        if (a + 1.0 > thresh.threshVecFine.size(0)) {
          i5 = 0;
          i6 = 0;
        } else {
          if (a + 1.0 != static_cast<int>(a + 1.0)) {
            rtIntegerError(a + 1.0, ob_emlrtDCI);
          }

          i1 = thresh.threshVecFine.size(0);
          if ((static_cast<int>(a + 1.0) < 1) || (static_cast<int>(a + 1.0) > i1))
          {
            rtDynamicBoundsError(static_cast<int>(a + 1.0), 1, i1, se_emlrtBCI);
          }

          i5 = static_cast<int>(a + 1.0) - 1;
          i1 = thresh.threshVecFine.size(0);
          i6 = thresh.threshVecFine.size(0);
          if ((i6 < 1) || (i6 > i1)) {
            rtDynamicBoundsError(i6, 1, i1, te_emlrtBCI);
          }
        }

        if (a - 1.0 < 1.0) {
          i7 = 0;
          i8 = 1;
          i9 = -1;
        } else {
          if (a - 1.0 != static_cast<int>(a - 1.0)) {
            rtIntegerError(a - 1.0, nb_emlrtDCI);
          }

          if ((static_cast<int>(a - 1.0) < 1) || (static_cast<int>(a - 1.0) >
               slope_val.size(0))) {
            rtDynamicBoundsError(static_cast<int>(a - 1.0), 1, slope_val.size(0),
                                 qe_emlrtBCI);
          }

          i7 = static_cast<int>(a - 1.0) - 1;
          i8 = -1;
          if (slope_val.size(0) < 1) {
            rtDynamicBoundsError(1, 1, slope_val.size(0), re_emlrtBCI);
          }

          i9 = 0;
        }

        f_loop_ub = div_s32(i9 - i7, i8);
        if (a + 1.0 > slope_val.size(0)) {
          i10 = 0;
          i11 = 0;
        } else {
          if (a + 1.0 != static_cast<int>(a + 1.0)) {
            rtIntegerError(a + 1.0, mb_emlrtDCI);
          }

          if ((static_cast<int>(a + 1.0) < 1) || (static_cast<int>(a + 1.0) >
               slope_val.size(0))) {
            rtDynamicBoundsError(static_cast<int>(a + 1.0), 1, slope_val.size(0),
                                 oe_emlrtBCI);
          }

          i10 = static_cast<int>(a + 1.0) - 1;
          if (slope_val.size(0) < 1) {
            rtDynamicBoundsError(slope_val.size(0), 1, slope_val.size(0),
                                 pe_emlrtBCI);
          }

          i11 = slope_val.size(0);
        }

        g_loop_ub = i11 - i10;
      }

      for (int k{0}; k < i; k++) {
        // This block of code is used to find the number of time
        // windows between the current peak and the others in
        // the same block. It checks the blocks in front and
        // behind
        // n_diff_to_curr_pk is a vector of time window
        // differences between the currently identified peaks and
        // all the other identified time windows in the current
        // block
        a = peak_ind[static_cast<int>(p) - 1];
        if (a != static_cast<int>(a)) {
          rtIntegerError(a, w_emlrtDCI);
        }

        if ((static_cast<int>(a) < 1) || (static_cast<int>(a) > b_loop_ub)) {
          rtDynamicBoundsError(static_cast<int>(a), 1, b_loop_ub, ac_emlrtBCI);
        }

        if ((static_cast<int>(static_cast<unsigned int>(k) + 1U) < 1) || (
             static_cast<int>(static_cast<unsigned int>(k) + 1U) > loop_ub)) {
          rtDynamicBoundsError(static_cast<int>(static_cast<unsigned int>(k) +
            1U), 1, loop_ub, bc_emlrtBCI);
        }

        tp_temp = S_cols[(static_cast<int>(a) + S_cols.size(0) * k) - 1];
        b_S_cols_for_mask.set_size(b_loop_ub);
        for (i1 = 0; i1 < d_loop_ub; i1++) {
          b_S_cols_for_mask[i1] = tp_temp - S_cols[i1 + S_cols.size(0) * k];
        }

        coder::b_abs(b_S_cols_for_mask, n_diff_to_curr_pk);
        n_diff_check_back.set_size(n_freqs_tmp);
        n_diff_check_for.set_size(n_freqs_tmp);
        for (i1 = 0; i1 < e_loop_ub; i1++) {
          n_diff_check_back[i1] = rtNaN;
          n_diff_check_for[i1] = rtNaN;
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
        if (static_cast<double>(k) + 1.0 <= stft_dt - 1.0) {
          // Don't compute forward check when k=n_blks
          if (a != static_cast<int>(a)) {
            rtIntegerError(a, x_emlrtDCI);
          }

          if ((static_cast<int>(static_cast<unsigned int>(k) + 2U) < 1) || (
               static_cast<int>(static_cast<unsigned int>(k) + 2U) > loop_ub)) {
            rtDynamicBoundsError(static_cast<int>(static_cast<unsigned int>(k) +
              2U), 1, loop_ub, cc_emlrtBCI);
          }

          b_S_cols_for_mask.set_size(b_loop_ub);
          for (i1 = 0; i1 < b_loop_ub; i1++) {
            b_S_cols_for_mask[i1] = tp_temp - S_cols[i1 + S_cols.size(0) * (k +
              1)];
          }

          coder::b_abs(b_S_cols_for_mask, n_diff_check_for);
        } else if (static_cast<unsigned int>(k) + 1U >= 2U) {
          // Don't compute backward check when k=1
          if (a != static_cast<int>(a)) {
            rtIntegerError(a, kb_emlrtDCI);
          }

          if ((k < 1) || (k > loop_ub)) {
            rtDynamicBoundsError(k, 1, loop_ub, vc_emlrtBCI);
          }

          b_S_cols_for_mask.set_size(b_loop_ub);
          for (i1 = 0; i1 < b_loop_ub; i1++) {
            b_S_cols_for_mask[i1] = tp_temp - S_cols[i1 + S_cols.size(0) * (k -
              1)];
          }

          coder::b_abs(b_S_cols_for_mask, n_diff_check_back);
        }

        // There could be instances when a single block contains
        // two pulses, as mentioned above, but if the search is
        // only for one pulse (K = 1) then the if statments above
        // won't run. We need here to check if there are
        // identified scores within the current block that are
        // also one time repetition interval (tip+/tipu) away
        // from the current peak
        if (a != static_cast<int>(a)) {
          rtIntegerError(a, y_emlrtDCI);
        }

        tip_temp = tp_temp + b_N;
        wind_end_data = tip_temp + b_M;
        slope_pos.set_size(b_loop_ub);
        for (i1 = 0; i1 < d_loop_ub; i1++) {
          slope_pos[i1] = (S_cols[i1 + S_cols.size(0) * k] < wind_end_data);
        }

        if (a != static_cast<int>(a)) {
          rtIntegerError(a, ab_emlrtDCI);
        }

        wind_end_data = tip_temp - b_M;
        b_freq_mask.set_size(b_loop_ub);
        for (i1 = 0; i1 < d_loop_ub; i1++) {
          b_freq_mask[i1] = (S_cols[i1 + S_cols.size(0) * k] > wind_end_data);
        }

        for (i1 = 0; i1 < b_loop_ub; i1++) {
          slope_pos[i1] = (slope_pos[i1] && b_freq_mask[i1]);
        }

        if (a != static_cast<int>(a)) {
          rtIntegerError(a, bb_emlrtDCI);
        }

        tp_temp -= b_N;
        wind_end_data = tp_temp - b_M;
        score_right_bndry.set_size(b_loop_ub);
        for (i1 = 0; i1 < d_loop_ub; i1++) {
          score_right_bndry[i1] = (S_cols[i1 + S_cols.size(0) * k] >
            wind_end_data);
        }

        if (a != static_cast<int>(a)) {
          rtIntegerError(a, cb_emlrtDCI);
        }

        wind_end_data = tp_temp + b_M;
        b_freq_mask.set_size(b_loop_ub);
        for (i1 = 0; i1 < d_loop_ub; i1++) {
          b_freq_mask[i1] = (S_cols[i1 + S_cols.size(0) * k] < wind_end_data);
        }

        for (i1 = 0; i1 < b_loop_ub; i1++) {
          score_right_bndry[i1] = (score_right_bndry[i1] && b_freq_mask[i1]);
        }

        if (slope_pos.size(0) == score_right_bndry.size(0)) {
          for (i1 = 0; i1 < b_loop_ub; i1++) {
            slope_pos[i1] = (slope_pos[i1] || score_right_bndry[i1]);
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
        if (a - 1.0 < 1.0) {
          i1 = 0;
          ii_data = 1;
          input_sizes_idx_1 = -1;
        } else {
          if (a - 1.0 != static_cast<int>(a - 1.0)) {
            rtIntegerError(a - 1.0, jb_emlrtDCI);
          }

          if ((static_cast<int>(a - 1.0) < 1) || (static_cast<int>(a - 1.0) >
               scores.size(0))) {
            rtDynamicBoundsError(static_cast<int>(a - 1.0), 1, scores.size(0),
                                 tc_emlrtBCI);
          }

          i1 = static_cast<int>(a - 1.0) - 1;
          ii_data = -1;
          if (scores.size(0) < 1) {
            rtDynamicBoundsError(1, 1, scores.size(0), uc_emlrtBCI);
          }

          input_sizes_idx_1 = 0;
        }

        wind_start_size = div_s32(input_sizes_idx_1 - i1, ii_data);
        wind_end_size = div_s32(i4 - i2, i3) + 1;
        if ((wind_start_size + 1 != wind_end_size) && ((wind_start_size + 1 != 1)
             && (wind_end_size != 1))) {
          emlrtDimSizeImpxCheckR2021b(wind_start_size + 1, wind_end_size,
            ob_emlrtECI);
        }

        if (wind_start_size + 1 == wind_end_size) {
          score_right_bndry.set_size(wind_start_size + 1);
          for (input_sizes_idx_1 = 0; input_sizes_idx_1 <= wind_start_size;
               input_sizes_idx_1++) {
            score_right_bndry[input_sizes_idx_1] = (scores[i1 + ii_data *
              input_sizes_idx_1] < thresh.threshVecFine[i2 + i3 *
              input_sizes_idx_1]);
          }

          input_sizes_idx_1 = coder::c_eml_find(score_right_bndry, (int *)
            &ii_data);
        } else {
          input_sizes_idx_1 = binary_expand_op_3((int *)&ii_data, scores, i1 + 1,
            ii_data, input_sizes_idx_1, this, i2 + 1, i3, i4);
        }

        wind_start_size = input_sizes_idx_1;
        for (i1 = 0; i1 < input_sizes_idx_1; i1++) {
          wind_start_data = static_cast<double>(ii_data) - 1.0;
        }

        if (a + 1.0 > scores.size(0)) {
          i1 = 0;
          ii_data = 0;
        } else {
          if (a + 1.0 != static_cast<int>(a + 1.0)) {
            rtIntegerError(a + 1.0, ib_emlrtDCI);
          }

          if ((static_cast<int>(a + 1.0) < 1) || (static_cast<int>(a + 1.0) >
               scores.size(0))) {
            rtDynamicBoundsError(static_cast<int>(a + 1.0), 1, scores.size(0),
                                 rc_emlrtBCI);
          }

          i1 = static_cast<int>(a + 1.0) - 1;
          if (scores.size(0) < 1) {
            rtDynamicBoundsError(scores.size(0), 1, scores.size(0), sc_emlrtBCI);
          }

          ii_data = scores.size(0);
        }

        wind_end_size = ii_data - i1;
        input_sizes_idx_1 = i6 - i5;
        if ((wind_end_size != input_sizes_idx_1) && ((wind_end_size != 1) &&
             (input_sizes_idx_1 != 1))) {
          emlrtDimSizeImpxCheckR2021b(wind_end_size, input_sizes_idx_1,
            pb_emlrtECI);
        }

        if (wind_end_size == input_sizes_idx_1) {
          score_right_bndry.set_size(wind_end_size);
          for (ii_data = 0; ii_data < wind_end_size; ii_data++) {
            score_right_bndry[ii_data] = (scores[i1 + ii_data] <
              thresh.threshVecFine[i5 + ii_data]);
          }

          input_sizes_idx_1 = coder::c_eml_find(score_right_bndry, (int *)
            &ii_data);
        } else {
          input_sizes_idx_1 = binary_expand_op_2((int *)&ii_data, scores, i1,
            ii_data, this, i5, i6);
        }

        wind_end_size = input_sizes_idx_1;
        for (i1 = 0; i1 < input_sizes_idx_1; i1++) {
          wind_end_data = static_cast<double>(ii_data) - 1.0;
        }

        // Here we look for the location where the slope changes.
        // We don't use the -1 like above because we want to be
        // sure to capture the entire saddle between peaks, so
        // we include the point after the transition of the slope
        // sign. If we didn't do this, then the lowest point
        // between the peaks that was still above the threshold
        // wouldn't be included in a sideband mask and might get
        // picked up later as an additional peak.
        score_right_bndry.set_size(div_s32(i9 - i7, i8) + 1);
        for (i1 = 0; i1 <= f_loop_ub; i1++) {
          score_right_bndry[i1] = slope_val[i7 + i8 * i1];
        }

        input_sizes_idx_1 = coder::c_eml_find(score_right_bndry, (int *)&ii_data);
        nRowsOfS = input_sizes_idx_1;
        for (i1 = 0; i1 < input_sizes_idx_1; i1++) {
          inds_bkwd_2_next_valley_data = ii_data;
        }

        score_right_bndry.set_size(i11 - i10);
        for (i1 = 0; i1 < g_loop_ub; i1++) {
          score_right_bndry[i1] = slope_val[i10 + i1];
        }

        input_sizes_idx_1 = coder::c_eml_find(score_right_bndry, (int *)&ii_data);
        if ((wind_end_size == 0) && (wind_start_size == 0)) {
          // If it can't find a place backwards or forwards
          // that is less than the threshold, the whole thing
          // could be sideband. Often the case for informed
          // search.
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
          excld_msk_vec.set_size(n_freqs_tmp);
          for (i1 = 0; i1 < n_freqs_tmp; i1++) {
            excld_msk_vec[i1] = false;
          }

          if ((nRowsOfS == 0) && (input_sizes_idx_1 == 0)) {
            excld_msk_vec.set_size(n_freqs_tmp);
            for (i1 = 0; i1 < n_freqs_tmp; i1++) {
              excld_msk_vec[i1] = true;
            }
          } else if ((nRowsOfS == 0) && (input_sizes_idx_1 != 0)) {
            if (a < 1.0) {
              wind_start_size = 0;
            } else {
              if (n_freqs_tmp < 1) {
                rtDynamicBoundsError(1, 1, n_freqs_tmp, gc_emlrtBCI);
              }

              if (a != static_cast<int>(a)) {
                rtIntegerError(a, db_emlrtDCI);
              }

              if ((static_cast<int>(a) < 1) || (static_cast<int>(a) >
                   n_freqs_tmp)) {
                rtDynamicBoundsError(static_cast<int>(a), 1, n_freqs_tmp,
                                     hc_emlrtBCI);
              }

              wind_start_size = static_cast<int>(a);
            }

            for (i1 = 0; i1 < wind_start_size; i1++) {
              excld_msk_vec[i1] = true;
            }
          } else if ((nRowsOfS != 0) && (input_sizes_idx_1 == 0)) {
            if (a > n_freqs_tmp) {
              i1 = 0;
              ii_data = 0;
            } else {
              if (a != static_cast<int>(a)) {
                rtIntegerError(a, eb_emlrtDCI);
              }

              if ((static_cast<int>(a) < 1) || (static_cast<int>(a) >
                   n_freqs_tmp)) {
                rtDynamicBoundsError(static_cast<int>(a), 1, n_freqs_tmp,
                                     ic_emlrtBCI);
              }

              i1 = static_cast<int>(a) - 1;
              if (n_freqs_tmp < 1) {
                rtDynamicBoundsError(n_freqs_tmp, 1, n_freqs_tmp, jc_emlrtBCI);
              }

              ii_data = n_freqs_tmp;
            }

            wind_start_size = ii_data - i1;
            for (ii_data = 0; ii_data < wind_start_size; ii_data++) {
              excld_msk_vec[i1 + ii_data] = true;
            }
          } else if ((nRowsOfS != 0) && (input_sizes_idx_1 != 0)) {
            if (ii_data < -static_cast<double>(inds_bkwd_2_next_valley_data)) {
              b_excluded_freq_bands.set_size(1, 0);
            } else {
              wind_start_size = ii_data + inds_bkwd_2_next_valley_data;
              b_excluded_freq_bands.set_size(1, wind_start_size + 1);
              for (i1 = 0; i1 <= wind_start_size; i1++) {
                b_excluded_freq_bands[i1] = -static_cast<double>
                  (inds_bkwd_2_next_valley_data) + static_cast<double>(i1);
              }
            }

            wind_start_size = b_excluded_freq_bands.size(1);
            r7.set_size(1, b_excluded_freq_bands.size(1));
            for (i1 = 0; i1 < wind_start_size; i1++) {
              tip_temp = a + b_excluded_freq_bands[i1];
              if (tip_temp != static_cast<int>(tip_temp)) {
                rtIntegerError(tip_temp, fb_emlrtDCI);
              }

              if ((static_cast<int>(tip_temp) < 1) || (static_cast<int>(tip_temp)
                   > n_freqs_tmp)) {
                rtDynamicBoundsError(static_cast<int>(tip_temp), 1, n_freqs_tmp,
                                     kc_emlrtBCI);
              }

              r7[i1] = static_cast<int>(tip_temp);
            }

            for (i1 = 0; i1 < wind_start_size; i1++) {
              excld_msk_vec[r7[i1] - 1] = true;
            }
          }

          // If there was a threhold crossing before and/or after
          // the peak, sort out the sidebands here
        } else {
          excld_msk_vec.set_size(n_freqs_tmp);
          for (i1 = 0; i1 < n_freqs_tmp; i1++) {
            excld_msk_vec[i1] = false;
          }

          if ((wind_end_size == 0) && (wind_start_size != 0)) {
            // Threshold crossing back was found but not
            // forwards.
            // What is smaller, the distance from the peak to
            // the first entry backwards, or the distance
            // from the peak to the threshold crossing in
            // front of the peak? Use that distance as the
            // 1/2 width of the sideband.
            if (nRowsOfS != 1) {
              fb_rtErrorWithMessageID(qb_emlrtRTEI.fName, qb_emlrtRTEI.lineNo);
            }

            t_srch_rng[0] = inds_bkwd_2_next_valley_data;
            t_srch_rng[1] = wind_start_data;
            if ((static_cast<int>(p) < 1) || (static_cast<int>(p) > n_freqs_tmp))
            {
              rtDynamicBoundsError(static_cast<int>(p), 1, n_freqs_tmp,
                                   lc_emlrtBCI);
            }

            bandwidth_of_peak[static_cast<int>(p) - 1] = coder::internal::
              b_minimum(t_srch_rng);

            // Had to code this way so coder/simulink would know the size of the min operation
          } else if ((wind_end_size != 0) && (wind_start_size == 0)) {
            // Threshold crossing forward was found but not
            // backwards.
            // What is smaller, the distance from the peak to
            // the last entry forwards, or the distance
            // from the peak to the threshold crossing in
            // back of the peak? Use that distance as the
            // 1/2 width of the sideband.
            if (input_sizes_idx_1 != 1) {
              fb_rtErrorWithMessageID(qb_emlrtRTEI.fName, qb_emlrtRTEI.lineNo);
            }

            t_srch_rng[0] = ii_data;
            t_srch_rng[1] = wind_end_data;
            if ((static_cast<int>(p) < 1) || (static_cast<int>(p) > n_freqs_tmp))
            {
              rtDynamicBoundsError(static_cast<int>(p), 1, n_freqs_tmp,
                                   pc_emlrtBCI);
            }

            bandwidth_of_peak[static_cast<int>(p) - 1] = coder::internal::
              b_minimum(t_srch_rng);

            // Had to code this way so coder/simulink
            // would know the size of the min operation
          } else {
            // Threshold crossing forward and backward was
            // found.
            // What is smaller, the distance
            // from the peak to the threshold crossing in
            // or the distance from the peak to the nearby
            // valley? Use that distance as the 1/2 width of
            // the sideband. Do this both forwards and
            // backwards.
            if (nRowsOfS != 0) {
              if (wind_start_size != 1) {
                fb_rtErrorWithMessageID(qb_emlrtRTEI.fName, qb_emlrtRTEI.lineNo);
              }

              t_srch_rng[0] = wind_start_data;
              t_srch_rng[1] = inds_bkwd_2_next_valley_data;
              wind_start_size = 1;
              wind_start_data = coder::internal::b_minimum(t_srch_rng);
            }

            if (input_sizes_idx_1 != 0) {
              if (wind_end_size != 1) {
                fb_rtErrorWithMessageID(qb_emlrtRTEI.fName, qb_emlrtRTEI.lineNo);
              }

              t_srch_rng[0] = ii_data;
              t_srch_rng[1] = wind_end_data;
              wind_end_size = 1;
              wind_end_data = coder::internal::b_minimum(t_srch_rng);
            }

            if (wind_end_size != wind_start_size) {
              fb_rtErrorWithMessageID(qb_emlrtRTEI.fName, qb_emlrtRTEI.lineNo);
            }

            for (i1 = 0; i1 < wind_start_size; i1++) {
              varargin_1_data[0] = wind_start_data;
            }

            for (i1 = 0; i1 < wind_end_size; i1++) {
              varargin_1_data[wind_start_size] = wind_end_data;
            }

            wind_end_size = wind_start_size << 1;
            if ((static_cast<int>(p) < 1) || (static_cast<int>(p) > n_freqs_tmp))
            {
              rtDynamicBoundsError(static_cast<int>(p), 1, n_freqs_tmp,
                                   qc_emlrtBCI);
            }

            b_varargin_1_data.set(&varargin_1_data[0], wind_end_size);
            bandwidth_of_peak[static_cast<int>(p) - 1] = coder::internal::
              unaryMinOrMax_anonFcn1(b_varargin_1_data);
          }

          // Make sure we aren't requesting masking of elements
          // that are outside the bounds of what we have
          // available in the vector
          if ((static_cast<int>(p) < 1) || (static_cast<int>(p) > n_freqs_tmp))
          {
            rtDynamicBoundsError(static_cast<int>(p), 1, n_freqs_tmp,
                                 mc_emlrtBCI);
          }

          t_srch_rng[0] = 1.0;
          tp_temp = bandwidth_of_peak[static_cast<int>(p) - 1];
          t_srch_rng[1] = a - tp_temp;
          wind_end_data = coder::internal::maximum(t_srch_rng);
          t_srch_rng[0] = n_freqs_tmp;
          t_srch_rng[1] = a + tp_temp;
          tip_temp = coder::internal::minimum(t_srch_rng);
          if (wind_end_data > tip_temp) {
            i1 = 0;
            ii_data = 0;
          } else {
            if (wind_end_data != static_cast<int>(std::floor(wind_end_data))) {
              rtIntegerError(wind_end_data, gb_emlrtDCI);
            }

            if ((static_cast<int>(wind_end_data) < 1) || (static_cast<int>
                 (wind_end_data) > n_freqs_tmp)) {
              rtDynamicBoundsError(static_cast<int>(wind_end_data), 1,
                                   n_freqs_tmp, nc_emlrtBCI);
            }

            i1 = static_cast<int>(wind_end_data) - 1;
            if (tip_temp != static_cast<int>(std::floor(tip_temp))) {
              rtIntegerError(tip_temp, hb_emlrtDCI);
            }

            if ((static_cast<int>(tip_temp) < 1) || (static_cast<int>(tip_temp) >
                 n_freqs_tmp)) {
              rtDynamicBoundsError(static_cast<int>(tip_temp), 1, n_freqs_tmp,
                                   oc_emlrtBCI);
            }

            ii_data = static_cast<int>(tip_temp);
          }

          wind_start_size = ii_data - i1;
          for (ii_data = 0; ii_data < wind_start_size; ii_data++) {
            excld_msk_vec[i1 + ii_data] = true;
          }
        }

        // Here we build up a mask that incorporates all the
        // peaks and their sidebands that we have identified
        // so far. The msk(:,p+1) entry is here because we are
        // looping through n_blks and are updating the p+1 column
        // each time.
        if (static_cast<int>(p) < n_freqs_tmp) {
          // I got an error on this line in a flight with an
          // index bounds error on msk(:,p+1) saying that 151
          // exceeded the bounds, which had been 150. The stuff
          // in this part of the if statement was the original
          // code and I thought it was okay because there
          // shouldn't ever be more peaks than n_freqs, or
          // anywhere close.
          if ((static_cast<int>(p) < 1) || (static_cast<int>(p) > n_freqs_tmp))
          {
            rtDynamicBoundsError(static_cast<int>(p), 1, n_freqs_tmp,
                                 dc_emlrtBCI);
          }

          if ((static_cast<int>(static_cast<double>(p) + 1.0) < 1) || (
               static_cast<int>(static_cast<double>(p) + 1.0) > n_freqs_tmp)) {
            rtDynamicBoundsError(static_cast<int>(static_cast<double>(p) + 1.0),
                                 1, n_freqs_tmp, ec_emlrtBCI);
          }

          wind_start_size = n_diff_to_curr_pk.size(0);
          b_freq_mask.set_size(n_diff_to_curr_pk.size(0));
          for (i1 = 0; i1 < wind_start_size; i1++) {
            b_freq_mask[i1] = (n_diff_to_curr_pk[i1] <= naive_wind_end);
          }

          wind_end_size = n_diff_check_back.size(0);
          r4.set_size(n_diff_check_back.size(0));
          for (i1 = 0; i1 < wind_end_size; i1++) {
            r4[i1] = (n_diff_check_back[i1] <= naive_wind_end);
          }

          if ((n_diff_to_curr_pk.size(0) != n_diff_check_back.size(0)) &&
              ((n_diff_to_curr_pk.size(0) != 1) && (n_diff_check_back.size(0) !=
                1))) {
            emlrtDimSizeImpxCheckR2021b(n_diff_to_curr_pk.size(0),
              n_diff_check_back.size(0), qb_emlrtECI);
          }

          if (b_freq_mask.size(0) == r4.size(0)) {
            for (i1 = 0; i1 < wind_start_size; i1++) {
              b_freq_mask[i1] = (b_freq_mask[i1] || r4[i1]);
            }
          } else {
            b_or(b_freq_mask, r4);
          }

          wind_start_size = n_diff_check_for.size(0);
          r4.set_size(n_diff_check_for.size(0));
          for (i1 = 0; i1 < wind_start_size; i1++) {
            r4[i1] = (n_diff_check_for[i1] <= naive_wind_end);
          }

          wind_start_size = b_freq_mask.size(0);
          if ((b_freq_mask.size(0) != n_diff_check_for.size(0)) &&
              ((b_freq_mask.size(0) != 1) && (n_diff_check_for.size(0) != 1))) {
            emlrtDimSizeImpxCheckR2021b(b_freq_mask.size(0),
              n_diff_check_for.size(0), qb_emlrtECI);
          }

          if (b_freq_mask.size(0) == r4.size(0)) {
            for (i1 = 0; i1 < wind_start_size; i1++) {
              b_freq_mask[i1] = (b_freq_mask[i1] || r4[i1]);
            }
          } else {
            b_or(b_freq_mask, r4);
          }

          wind_start_size = excld_msk_vec.size(0);
          if ((excld_msk_vec.size(0) != b_freq_mask.size(0)) &&
              ((excld_msk_vec.size(0) != 1) && (b_freq_mask.size(0) != 1))) {
            emlrtDimSizeImpxCheckR2021b(excld_msk_vec.size(0), b_freq_mask.size
              (0), rb_emlrtECI);
          }

          if (excld_msk_vec.size(0) == b_freq_mask.size(0)) {
            for (i1 = 0; i1 < wind_start_size; i1++) {
              excld_msk_vec[i1] = (excld_msk_vec[i1] || b_freq_mask[i1]);
            }
          } else {
            b_or(excld_msk_vec, b_freq_mask);
          }

          wind_start_size = excld_msk_vec.size(0);
          if ((excld_msk_vec.size(0) != slope_pos.size(0)) &&
              ((excld_msk_vec.size(0) != 1) && (slope_pos.size(0) != 1))) {
            emlrtDimSizeImpxCheckR2021b(excld_msk_vec.size(0), slope_pos.size(0),
              rb_emlrtECI);
          }

          b_freq_mask.set_size(n_freqs_tmp);
          for (i1 = 0; i1 < n_freqs_tmp; i1++) {
            b_freq_mask[i1] = (msk[i1 + msk.size(0) * (static_cast<int>(p) - 1)]
                               || msk[i1 + msk.size(0) * static_cast<int>(p)]);
          }

          if (excld_msk_vec.size(0) == slope_pos.size(0)) {
            for (i1 = 0; i1 < wind_start_size; i1++) {
              excld_msk_vec[i1] = (excld_msk_vec[i1] || slope_pos[i1]);
            }
          } else {
            b_or(excld_msk_vec, slope_pos);
          }

          if ((n_freqs_tmp != excld_msk_vec.size(0)) && ((n_freqs_tmp != 1) &&
               (excld_msk_vec.size(0) != 1))) {
            emlrtDimSizeImpxCheckR2021b(n_freqs_tmp, excld_msk_vec.size(0),
              sb_emlrtECI);
          }

          if (b_freq_mask.size(0) == excld_msk_vec.size(0)) {
            for (i1 = 0; i1 < n_freqs_tmp; i1++) {
              b_freq_mask[i1] = (b_freq_mask[i1] || excld_msk_vec[i1]);
            }
          } else {
            b_or(b_freq_mask, excld_msk_vec);
          }

          rtSubAssignSizeCheck(&n_freqs_tmp, 1, b_freq_mask.size(), 1,
                               tb_emlrtECI);
          for (i1 = 0; i1 < n_freqs_tmp; i1++) {
            msk[i1 + msk.size(0) * static_cast<int>(p)] = b_freq_mask[i1];
          }

          std::printf("Everything normal, p = %f \n", static_cast<double>(p));
          std::fflush(stdout);
        } else {
          // This will let me know if there is a problem and
          // keep the code from crashing so that I can
          std::printf("!!!!!!!!!!!!!!!!!!!!!!!!\n");
          std::fflush(stdout);
          std::printf("SOMETHING WEIRD HAPPENED AND THE PEELING ALGORITHM GOT ALL THE WAY TO THE END OF THE MSK COLUMNS MEANING THERE WERE AT LEAST AS "
                      "MANY PEAKS AS THERE ARE FREQUENCIES.:\n");
          std::fflush(stdout);
          std::printf("p = %f \n", static_cast<double>(p));
          std::fflush(stdout);
          std::printf("peak_masked_curr_scores are:\n");
          std::fflush(stdout);
          i1 = curr_scores.size(0);
          for (input_sizes_idx_1 = 0; input_sizes_idx_1 < i1; input_sizes_idx_1
               ++) {
            if (input_sizes_idx_1 + 1 > i1) {
              rtDynamicBoundsError(input_sizes_idx_1 + 1, 1, i1, fc_emlrtBCI);
            }

            std::printf("%.6f,", curr_scores[input_sizes_idx_1]);
            std::fflush(stdout);
          }

          std::printf("!!!!!!!!!!!!!!!!!!!!!!!!\n");
          std::fflush(stdout);
        }
      }

      // Extract the mask for this peak and no others
      if ((static_cast<int>(static_cast<double>(p) + 1.0) < 1) || (static_cast<
           int>(static_cast<double>(p) + 1.0) > n_freqs_tmp)) {
        rtDynamicBoundsError(static_cast<int>(static_cast<double>(p) + 1.0), 1,
                             n_freqs_tmp, wc_emlrtBCI);
      }

      if ((static_cast<int>(p) < 1) || (static_cast<int>(p) > n_freqs_tmp)) {
        rtDynamicBoundsError(static_cast<int>(p), 1, n_freqs_tmp, xc_emlrtBCI);
      }

      b_freq_mask.set_size(n_freqs_tmp);
      for (i = 0; i < n_freqs_tmp; i++) {
        b_freq_mask[i] = (msk[i + msk.size(0) * static_cast<int>(p)] - msk[i +
                          msk.size(0) * (static_cast<int>(p) - 1)] != 0);
      }

      rtSubAssignSizeCheck(&n_freqs_tmp, 1, b_freq_mask.size(), 1, ub_emlrtECI);
      for (i = 0; i < n_freqs_tmp; i++) {
        indiv_msk[i + indiv_msk.size(0) * (static_cast<int>(p) - 1)] =
          b_freq_mask[i];
      }

      // Update the current scores to exclude peaks and sidebands
      // we have identified so far.
      if ((static_cast<int>(p + 1U) < 1) || (static_cast<int>(p + 1U) >
           n_freqs_tmp)) {
        rtDynamicBoundsError(static_cast<int>(p + 1U), 1, n_freqs_tmp,
                             yc_emlrtBCI);
      }

      b_freq_mask.set_size(n_freqs_tmp);
      for (i = 0; i < n_freqs_tmp; i++) {
        b_freq_mask[i] = !msk[i + msk.size(0) * static_cast<int>(p)];
      }

      wind_start_size = scores.size(0);
      if ((scores.size(0) != n_freqs_tmp) && ((scores.size(0) != 1) &&
           (n_freqs_tmp != 1))) {
        emlrtDimSizeImpxCheckR2021b(scores.size(0), n_freqs_tmp, vb_emlrtECI);
      }

      if (scores.size(0) == b_freq_mask.size(0)) {
        curr_scores.set_size(scores.size(0));
        for (i = 0; i < wind_start_size; i++) {
          curr_scores[i] = scores[i] * static_cast<double>(b_freq_mask[i]);
        }
      } else {
        binary_expand_op_7(curr_scores, scores, b_freq_mask);
      }

      // Mask the recently found sidebands
      wind_start_size = curr_scores.size(0);
      if ((curr_scores.size(0) != greater_than_next.size(0)) &&
          ((curr_scores.size(0) != 1) && (greater_than_next.size(0) != 1))) {
        emlrtDimSizeImpxCheckR2021b(curr_scores.size(0), greater_than_next.size
          (0), wb_emlrtECI);
      }

      if (curr_scores.size(0) == greater_than_next.size(0)) {
        for (i = 0; i < wind_start_size; i++) {
          curr_scores[i] = curr_scores[i] * static_cast<double>
            (greater_than_next[i]);
        }
      } else {
        binary_expand_op_4(curr_scores, greater_than_next);
      }

      // Mask to only look at peaks
      wind_start_size = curr_scores.size(0);
      i = thresh.threshVecFine.size(0);
      if ((curr_scores.size(0) != i) && ((curr_scores.size(0) != 1) && (i != 1)))
      {
        emlrtDimSizeImpxCheckR2021b(curr_scores.size(0), i, xb_emlrtECI);
      }

      if (curr_scores.size(0) == thresh.threshVecFine.size(0)) {
        b_freq_mask.set_size(curr_scores.size(0));
        for (i = 0; i < wind_start_size; i++) {
          b_freq_mask[i] = (curr_scores[i] >= thresh.threshVecFine[i]);
        }
      } else {
        binary_expand_op_5(b_freq_mask, curr_scores, this);
      }

      wind_start_size = curr_scores.size(0);
      if ((curr_scores.size(0) != b_freq_mask.size(0)) && ((curr_scores.size(0)
            != 1) && (b_freq_mask.size(0) != 1))) {
        emlrtDimSizeImpxCheckR2021b(curr_scores.size(0), b_freq_mask.size(0),
          yb_emlrtECI);
      }

      if (curr_scores.size(0) == b_freq_mask.size(0)) {
        for (i = 0; i < wind_start_size; i++) {
          curr_scores[i] = curr_scores[i] * static_cast<double>(b_freq_mask[i]);
        }
      } else {
        binary_expand_op_4(curr_scores, b_freq_mask);
      }

      // Eliminate non-threshold exceeding scores from consideration
      p++;
    } else {
      exitg1 = 1;
    }
  } while (exitg1 == 0);

  // Clean up the msk and indiv_mask so their columns align with
  // n_pulsegroup_found.
  r.set_size(yw_max_all_freq.size(0), yw_max_all_freq.size(0));
  for (i = 0; i < b_loop_ub_tmp; i++) {
    r[i] = msk[i];
  }

  coder::g_circshift(r);
  if (static_cast<int>(p - 1U) >= 1) {
    if (r.size(1) < 1) {
      rtDynamicBoundsError(1, 1, r.size(1), ad_emlrtBCI);
    }

    if ((static_cast<int>(static_cast<double>(p) - 1.0) < 1) || (static_cast<int>
         (static_cast<double>(p) - 1.0) > r.size(1))) {
      rtDynamicBoundsError(static_cast<int>(static_cast<double>(p) - 1.0), 1,
                           r.size(1), bd_emlrtBCI);
    }
  }

  if (static_cast<int>(p - 1U) < 1) {
    b_loop_ub = 0;
  } else {
    if (yw_max_all_freq.size(0) < 1) {
      rtDynamicBoundsError(1, 1, yw_max_all_freq.size(0), me_emlrtBCI);
    }

    if ((static_cast<int>(p - 1U) < 1) || (static_cast<int>(p - 1U) >
         yw_max_all_freq.size(0))) {
      rtDynamicBoundsError(static_cast<int>(p - 1U), 1, yw_max_all_freq.size(0),
                           ne_emlrtBCI);
    }

    b_loop_ub = static_cast<int>(p - 1U);
  }

  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < n_freqs_tmp; i1++) {
      indiv_msk[i1 + n_freqs_tmp * i] = indiv_msk[i1 + indiv_msk.size(0) * i];
    }
  }

  indiv_msk.set_size(indiv_msk.size(0), b_loop_ub);
  if (peak_ind.size(0) < 1) {
    rtDynamicBoundsError(1, 1, peak_ind.size(0), cd_emlrtBCI);
  }

  if ((!std::isnan(peak_ind[0])) && (static_cast<int>(p - 1U) > 0)) {
    // Only update from NaN if there were some found.
    if (peak_ind.size(0) < 1) {
      rtDynamicBoundsError(1, 1, peak_ind.size(0), dd_emlrtBCI);
    }

    if ((static_cast<int>(static_cast<double>(p) - 1.0) < 1) || (static_cast<int>
         (static_cast<double>(p) - 1.0) > peak_ind.size(0))) {
      rtDynamicBoundsError(static_cast<int>(static_cast<double>(p) - 1.0), 1,
                           peak_ind.size(0), ed_emlrtBCI);
    }

    sizes[0] = 1;
    sizes[1] = static_cast<int>(p - 1U);
    coder::internal::indexShapeCheck(peak_ind.size(0), sizes);
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
  tip_temp = makepulsestruc(expl_temp.t_next, expl_temp.mode, wind_end_data,
    tp_temp, a, stft_dt, t_lastknown, timetol, wind_start_data, naive_wind_end,
    freqModWarningFlag, t9_con_dec);
  expl_temp.con_dec = t9_con_dec;
  expl_temp.det_dec = freqModWarningFlag;
  expl_temp.fend = naive_wind_end;
  expl_temp.fstart = wind_start_data;
  expl_temp.fp = timetol;
  expl_temp.t_f = t_lastknown;
  expl_temp.t_0 = stft_dt;
  expl_temp.yw = a;
  expl_temp.SNR = tp_temp;
  expl_temp.P = wind_end_data;
  expl_temp.A = tip_temp;
  coder::repmat(expl_temp, static_cast<double>(yw_max_all_freq.size(0)),
                static_cast<double>(yw_max_all_freq.size(1)), pl_out);

  // Create a frequency array that accounts for the masking that
  // was done to reduce the frequency space.
  wind_end_size = freq_mask.size(0);
  input_sizes_idx_1 = 0;
  for (wind_start_size = 0; wind_start_size < wind_end_size; wind_start_size++)
  {
    if (freq_mask[wind_start_size]) {
      input_sizes_idx_1++;
    }
  }

  r5.set_size(input_sizes_idx_1);
  input_sizes_idx_1 = 0;
  for (wind_start_size = 0; wind_start_size < wind_end_size; wind_start_size++)
  {
    if (freq_mask[wind_start_size]) {
      r5[input_sizes_idx_1] = wind_start_size;
      input_sizes_idx_1++;
    }
  }

  input_sizes_idx_1 = Wf.size(0);
  b_loop_ub_tmp = r5.size(0);
  for (i = 0; i < b_loop_ub_tmp; i++) {
    if (r5[i] > input_sizes_idx_1 - 1) {
      rtDynamicBoundsError(r5[i], 0, input_sizes_idx_1 - 1, fd_emlrtBCI);
    }
  }

  // t_found here is the start of the pulse - not the center like
  // in the time stamps in the stft, which are the centers of the
  // windows. The dt_stft/2 term offfset would affect both the first
  // and second terms of the equation below and therefore cancel.
  refmat.set_size(yw_max_all_freq.size(0), yw_max_all_freq.size(1));
  for (i = 0; i < loop_ub_tmp; i++) {
    refmat[i] = rtNaN;
  }

  // The lines below effectively do the following operation:
  //     t_found(freq_mask,:)    = obj.stft.t(S_cols(freq_mask,:))-obj.stft.t(1)+obj.t_0;
  // but in a way that doesn't generate errors in the C++ generated
  // executable for cases when S_cols_freq_mask goes from an nxK
  // matrix to a 1xK matrix. This could sometimes happen when
  // switching between values of tip mid-processing through changes
  // to the interpulse spec. Coder had assumed at compile time that
  // the result of S_cols(freq_mask,:) was a matrix and then would
  // error our it it became a row vector at runtime. This method
  // does everythe as a vector input.
  for (i = 0; i < b_loop_ub_tmp; i++) {
    if (r5[i] > S_cols.size(0) - 1) {
      rtDynamicBoundsError(r5[i], 0, S_cols.size(0) - 1, gd_emlrtBCI);
    }
  }

  if (loop_ub_tmp < 1) {
    b_excluded_freq_bands.set_size(1, 0);
  } else {
    b_excluded_freq_bands.set_size(1, loop_ub_tmp);
    b_loop_ub = loop_ub_tmp - 1;
    for (i = 0; i <= b_loop_ub; i++) {
      b_excluded_freq_bands[i] = static_cast<double>(i) + 1.0;
    }
  }

  t_srch_rng[0] = yw_max_all_freq.size(0);
  t_srch_rng[1] = yw_max_all_freq.size(1);
  coder::internal::assertValidSizeArg(t_srch_rng);
  input_sizes_idx_1 = 1;
  if (b_excluded_freq_bands.size(1) > 1) {
    input_sizes_idx_1 = b_excluded_freq_bands.size(1);
  }

  wind_end_size = b_excluded_freq_bands.size(1);
  if (wind_end_size >= input_sizes_idx_1) {
    input_sizes_idx_1 = wind_end_size;
  }

  if (yw_max_all_freq.size(0) > input_sizes_idx_1) {
    k_rtErrorWithMessageID(k_emlrtRTEI.fName, k_emlrtRTEI.lineNo);
  }

  if (yw_max_all_freq.size(1) > input_sizes_idx_1) {
    k_rtErrorWithMessageID(k_emlrtRTEI.fName, k_emlrtRTEI.lineNo);
  }

  wind_end_size = yw_max_all_freq.size(1);
  if (wind_end_size < 0) {
    ib_rtErrorWithMessageID(tb_emlrtRTEI.fName, tb_emlrtRTEI.lineNo);
  }

  if (yw_max_all_freq.size(0) * yw_max_all_freq.size(1) !=
      b_excluded_freq_bands.size(1)) {
    l_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
  }

  for (i = 0; i < b_loop_ub_tmp; i++) {
    if (r5[i] > yw_max_all_freq.size(0) - 1) {
      rtDynamicBoundsError(r5[i], 0, yw_max_all_freq.size(0) - 1, hd_emlrtBCI);
    }
  }

  sizes[0] = yw_max_all_freq.size(0);
  r6.set_size(r5.size(0), yw_max_all_freq.size(1));
  for (i = 0; i < c_loop_ub; i++) {
    for (i1 = 0; i1 < b_loop_ub_tmp; i1++) {
      ii_data = static_cast<int>(b_excluded_freq_bands[r5[i1] + sizes[0] * i]);
      if (ii_data > loop_ub_tmp) {
        rtDynamicBoundsError(ii_data, 1, loop_ub_tmp, id_emlrtBCI);
      }

      r6[i1 + r6.size(0) * i] = ii_data;
    }
  }

  b_S_cols.set_size(r5.size(0), S_cols.size(1));
  for (i = 0; i < loop_ub; i++) {
    for (i1 = 0; i1 < b_loop_ub_tmp; i1++) {
      b_S_cols[i1 + b_S_cols.size(0) * i] = S_cols[r5[i1] + S_cols.size(0) * i];
    }
  }

  wind_end_size = r5.size(0) * S_cols.size(1);
  input_sizes_idx_1 = stft->t.size(0);
  timeBlinderVec.set_size(wind_end_size);
  for (i = 0; i < wind_end_size; i++) {
    a = b_S_cols[i];
    if (a != static_cast<int>(std::floor(a))) {
      rtIntegerError(a, lb_emlrtDCI);
    }

    if ((static_cast<int>(a) < 1) || (static_cast<int>(a) > input_sizes_idx_1))
    {
      rtDynamicBoundsError(static_cast<int>(a), 1, input_sizes_idx_1,
                           jd_emlrtBCI);
    }

    timeBlinderVec[i] = stft->t[static_cast<int>(a) - 1];
  }

  loop_ub = r6.size(0) * r6.size(1);
  if (loop_ub != wind_end_size) {
    rtSizeEq1DError(loop_ub, wind_end_size, ac_emlrtECI);
  }

  i = stft->t.size(0);
  if (i < 1) {
    rtDynamicBoundsError(1, 1, i, kd_emlrtBCI);
  }

  tp_temp = stft->t[0];
  for (i = 0; i < loop_ub; i++) {
    refmat[r6[i] - 1] = (timeBlinderVec[i] - tp_temp) + t_0;
  }

  i = Wf.size(0);
  if (i < 2) {
    rtDynamicBoundsError(2, 1, i, ld_emlrtBCI);
  }

  i = Wf.size(0);
  if (i < 1) {
    rtDynamicBoundsError(1, 1, i, md_emlrtBCI);
  }

  i = Wf.size(0);
  if (i < 2) {
    rtDynamicBoundsError(2, 1, i, nd_emlrtBCI);
  }

  i = Wf.size(0);
  if (i < 1) {
    rtDynamicBoundsError(1, 1, i, od_emlrtBCI);
  }

  tp_temp = (Wf[1] - Wf[0]) / 2.0;
  loop_ub = Wf.size(0);
  bandwidth_of_peak.set_size(loop_ub);
  b_loop_ub = Wf.size(0);
  tip_temp = (Wf[1] - Wf[0]) / 2.0;
  timeBlinderVec.set_size(Wf.size(0));
  for (i = 0; i < b_loop_ub; i++) {
    a = Wf[i];
    bandwidth_of_peak[i] = a - tp_temp;
    timeBlinderVec[i] = a + tip_temp;
  }

  if (timeBlinderVec.size(0) != bandwidth_of_peak.size(0)) {
    fb_rtErrorWithMessageID(qb_emlrtRTEI.fName, qb_emlrtRTEI.lineNo);
  }

  excluded_freq_bands.set_size(loop_ub, 2);
  for (i = 0; i < loop_ub; i++) {
    excluded_freq_bands[i] = bandwidth_of_peak[i];
    excluded_freq_bands[i + excluded_freq_bands.size(0)] = timeBlinderVec[i];
  }

  // Build out the pulse object for each one found
  for (wind_start_size = 0; wind_start_size < c_loop_ub; wind_start_size++) {
    for (wind_end_size = 0; wind_end_size < n_freqs_tmp; wind_end_size++) {
      if (wind_end_size + 1 > n_freqs_tmp) {
        rtDynamicBoundsError(wind_end_size + 1, 1, n_freqs_tmp, pd_emlrtBCI);
      }

      if (wind_start_size + 1 > c_loop_ub) {
        rtDynamicBoundsError(wind_start_size + 1, 1, c_loop_ub, pd_emlrtBCI);
      }

      tp_temp = refmat[wind_end_size + refmat.size(0) * wind_start_size];
      t_srch_rng[0] = ((tp_temp + ps_pos->t_ip) - ps_pos->t_ipu) - ps_pos->t_ipj;
      if (wind_end_size + 1 > n_freqs_tmp) {
        rtDynamicBoundsError(wind_end_size + 1, 1, n_freqs_tmp, qd_emlrtBCI);
      }

      if (wind_start_size + 1 > c_loop_ub) {
        rtDynamicBoundsError(wind_start_size + 1, 1, c_loop_ub, qd_emlrtBCI);
      }

      t_srch_rng[1] = ((tp_temp + ps_pos->t_ip) + ps_pos->t_ipu) + ps_pos->t_ipj;
      if (wind_end_size + 1 > searchmat.size(0)) {
        rtDynamicBoundsError(wind_end_size + 1, 1, searchmat.size(0),
                             rd_emlrtBCI);
      }

      if (wind_start_size + 1 > searchmat.size(1)) {
        rtDynamicBoundsError(wind_start_size + 1, 1, searchmat.size(1),
                             sd_emlrtBCI);
      }

      if (wind_end_size + 1 > n_freqs_tmp) {
        rtDynamicBoundsError(wind_end_size + 1, 1, n_freqs_tmp, td_emlrtBCI);
      }

      if (wind_start_size + 1 > c_loop_ub) {
        rtDynamicBoundsError(wind_start_size + 1, 1, c_loop_ub, ud_emlrtBCI);
      }

      if (wind_end_size + 1 > signalPlusNoisePSD.size(0)) {
        rtDynamicBoundsError(wind_end_size + 1, 1, signalPlusNoisePSD.size(0),
                             vd_emlrtBCI);
      }

      if (wind_start_size + 1 > signalPlusNoisePSD.size(1)) {
        rtDynamicBoundsError(wind_start_size + 1, 1, signalPlusNoisePSD.size(1),
                             wd_emlrtBCI);
      }

      if (wind_end_size + 1 > n_freqs_tmp) {
        rtDynamicBoundsError(wind_end_size + 1, 1, n_freqs_tmp, xd_emlrtBCI);
      }

      if (wind_start_size + 1 > c_loop_ub) {
        rtDynamicBoundsError(wind_start_size + 1, 1, c_loop_ub, yd_emlrtBCI);
      }

      if (wind_end_size + 1 > n_freqs_tmp) {
        rtDynamicBoundsError(wind_end_size + 1, 1, n_freqs_tmp, ae_emlrtBCI);
      }

      if (wind_start_size + 1 > c_loop_ub) {
        rtDynamicBoundsError(wind_start_size + 1, 1, c_loop_ub, be_emlrtBCI);
      }

      i = Wf.size(0);
      if (wind_end_size + 1 > i) {
        rtDynamicBoundsError(wind_end_size + 1, 1, i, ce_emlrtBCI);
      }

      if (wind_end_size + 1 > loop_ub) {
        rtDynamicBoundsError(wind_end_size + 1, 1, loop_ub, de_emlrtBCI);
      }

      if (wind_end_size + 1 > pl_out.size(0)) {
        rtDynamicBoundsError(wind_end_size + 1, 1, pl_out.size(0), ee_emlrtBCI);
      }

      if (wind_start_size + 1 > pl_out.size(1)) {
        rtDynamicBoundsError(wind_start_size + 1, 1, pl_out.size(1), fe_emlrtBCI);
      }

      b_makepulsestruc(searchmat[wind_end_size + searchmat.size(0) *
                       wind_start_size], yw_max_all_freq[wind_end_size +
                       yw_max_all_freq.size(0) * wind_start_size],
                       signalPlusNoisePSD[wind_end_size +
                       signalPlusNoisePSD.size(0) * wind_start_size], tp_temp,
                       tp_temp + ps_pre->t_p, t_srch_rng, Wf[wind_end_size],
                       excluded_freq_bands[wind_end_size],
                       excluded_freq_bands[wind_end_size +
                       excluded_freq_bands.size(0)], &pl_out[wind_end_size +
                       pl_out.size(0) * wind_start_size]);

      // %NaN,...
      if (wind_end_size + 1 > pl_out.size(0)) {
        rtDynamicBoundsError(wind_end_size + 1, 1, pl_out.size(0), ge_emlrtBCI);
      }

      if (wind_start_size + 1 > pl_out.size(1)) {
        rtDynamicBoundsError(wind_start_size + 1, 1, pl_out.size(1), he_emlrtBCI);
      }

      pl_out[wind_end_size + pl_out.size(0) * wind_start_size].con_dec = false;

      // Confirmation status
      if (wind_end_size + 1 > scores.size(0)) {
        rtDynamicBoundsError(wind_end_size + 1, 1, scores.size(0), ie_emlrtBCI);
      }

      i = thresh.threshVecFine.size(0);
      if (wind_end_size + 1 > i) {
        rtDynamicBoundsError(wind_end_size + 1, 1, i, je_emlrtBCI);
      }

      if (scores[wind_end_size] >= thresh.threshVecFine[wind_end_size]) {
        // scores(j)>=thresh
        if (wind_end_size + 1 > pl_out.size(0)) {
          rtDynamicBoundsError(wind_end_size + 1, 1, pl_out.size(0), ke_emlrtBCI);
        }

        if (wind_start_size + 1 > pl_out.size(1)) {
          rtDynamicBoundsError(wind_start_size + 1, 1, pl_out.size(1),
                               le_emlrtBCI);
        }

        pl_out[wind_end_size + pl_out.size(0) * wind_start_size].det_dec = true;
      }
    }
  }

  // FREQUENCY, THRESHOLD, AND SCORES PRINTING USED TO GO HERE.
  // MOVED TO ABOVE PEELING ALGORITHM SO THAT I CAN SEE THIS WHEN
  // IF THE ALGORITHM CRASHES
  tp_temp = coder::toc() - previousToc;
  std::printf("complete. Elapsed time: %f seconds \n", tp_temp);
  std::fflush(stdout);
  coder::toc();
}

//
// Arguments    : const coder::array<c_struct_T, 2U> &candidateList
//                const coder::array<double, 1U> &peakIndexList
// Return Type  : double
//
double waveform::selectpeakindex(const coder::array<c_struct_T, 2U>
  &candidateList, const coder::array<double, 1U> &peakIndexList) const
{
  static rtBoundsCheckInfo ab_emlrtBCI{ 1863,// lineNo
    "peakIndexList",                   // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtBoundsCheckInfo ac_emlrtBCI{ 1929,// lineNo
    "peakIndexList",                   // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtBoundsCheckInfo bb_emlrtBCI{ 1863,// lineNo
    "candidateList",                   // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtBoundsCheckInfo bc_emlrtBCI{ 1929,// lineNo
    "candidateList",                   // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtBoundsCheckInfo cb_emlrtBCI{ 1863,// lineNo
    "candidateList",                   // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtBoundsCheckInfo cc_emlrtBCI{ 1937,// lineNo
    "candidateList",                   // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtBoundsCheckInfo db_emlrtBCI{ 1863,// lineNo
    "peakIndexList",                   // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtBoundsCheckInfo dc_emlrtBCI{ 1937,// lineNo
    "peakIndexList",                   // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtBoundsCheckInfo eb_emlrtBCI{ 1863,// lineNo
    "obj.ps_pre.clst",                 // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtBoundsCheckInfo ec_emlrtBCI{ 1937,// lineNo
    "candidateList",                   // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtBoundsCheckInfo fb_emlrtBCI{ 1863,// lineNo
    "obj.ps_pre.clst",                 // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtBoundsCheckInfo fc_emlrtBCI{ 1945,// lineNo
    "candidateList",                   // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtBoundsCheckInfo gb_emlrtBCI{ 1864,// lineNo
    "interPulseAligned",               // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtBoundsCheckInfo gc_emlrtBCI{ 1945,// lineNo
    "peakIndexList",                   // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtBoundsCheckInfo hb_emlrtBCI{ 1878,// lineNo
    "candidateList",                   // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtBoundsCheckInfo hc_emlrtBCI{ 1945,// lineNo
    "candidateList",                   // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtBoundsCheckInfo ib_emlrtBCI{ 1878,// lineNo
    "peakIndexList",                   // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtBoundsCheckInfo ic_emlrtBCI{ 1955,// lineNo
    "selectedIndex",                   // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtBoundsCheckInfo jb_emlrtBCI{ 1878,// lineNo
    "candidateList",                   // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtBoundsCheckInfo jc_emlrtBCI{ 1956,// lineNo
    "candidateList",                   // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtBoundsCheckInfo kb_emlrtBCI{ 1878,// lineNo
    "peakIndexList",                   // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtBoundsCheckInfo kc_emlrtBCI{ 1956,// lineNo
    "peakIndexList",                   // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtBoundsCheckInfo lb_emlrtBCI{ 1878,// lineNo
    "obj.ps_pre.clst",                 // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtBoundsCheckInfo lc_emlrtBCI{ 1956,// lineNo
    "candidateList",                   // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtBoundsCheckInfo mb_emlrtBCI{ 1878,// lineNo
    "obj.ps_pre.clst",                 // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtBoundsCheckInfo mc_emlrtBCI{ 1964,// lineNo
    "candidateList",                   // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtBoundsCheckInfo nb_emlrtBCI{ 1881,// lineNo
    "peakIndexList",                   // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtBoundsCheckInfo nc_emlrtBCI{ 1964,// lineNo
    "peakIndexList",                   // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtBoundsCheckInfo ob_emlrtBCI{ 1881,// lineNo
    "obj.ps_pre.clst",                 // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtBoundsCheckInfo oc_emlrtBCI{ 1964,// lineNo
    "candidateList",                   // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtBoundsCheckInfo pb_emlrtBCI{ 1881,// lineNo
    "obj.ps_pre.clst",                 // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtBoundsCheckInfo pc_emlrtBCI{ 1972,// lineNo
    "candidateList",                   // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtBoundsCheckInfo qb_emlrtBCI{ 1881,// lineNo
    "interPulseAligned",               // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtBoundsCheckInfo qc_emlrtBCI{ 1972,// lineNo
    "peakIndexList",                   // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtBoundsCheckInfo rb_emlrtBCI{ 1883,// lineNo
    "interPulseAligned",               // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtBoundsCheckInfo rc_emlrtBCI{ 1972,// lineNo
    "candidateList",                   // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtBoundsCheckInfo sb_emlrtBCI{ 1891,// lineNo
    "candidateList",                   // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtBoundsCheckInfo tb_emlrtBCI{ 1920,// lineNo
    "selectedIndex",                   // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtBoundsCheckInfo ub_emlrtBCI{ 1921,// lineNo
    "candidateList",                   // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtBoundsCheckInfo vb_emlrtBCI{ 1921,// lineNo
    "peakIndexList",                   // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtBoundsCheckInfo wb_emlrtBCI{ 1921,// lineNo
    "candidateList",                   // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtBoundsCheckInfo xb_emlrtBCI{ 1928,// lineNo
    "selectedIndex",                   // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtBoundsCheckInfo yb_emlrtBCI{ 1929,// lineNo
    "candidateList",                   // aName
    "waveform/selectpeakindex"         // fName
  };

  static rtDoubleCheckInfo q_emlrtDCI{ 1863,// lineNo
    "waveform/selectpeakindex"         // fName
  };

  static rtDoubleCheckInfo r_emlrtDCI{ 1863,// lineNo
    "waveform/selectpeakindex"         // fName
  };

  static rtDoubleCheckInfo s_emlrtDCI{ 1878,// lineNo
    "waveform/selectpeakindex"         // fName
  };

  static rtDoubleCheckInfo t_emlrtDCI{ 1878,// lineNo
    "waveform/selectpeakindex"         // fName
  };

  static rtDoubleCheckInfo u_emlrtDCI{ 1881,// lineNo
    "waveform/selectpeakindex"         // fName
  };

  static rtDoubleCheckInfo v_emlrtDCI{ 1891,// lineNo
    "waveform/selectpeakindex"         // fName
  };

  static rtEqualityCheckInfo g_emlrtECI{ 1,// nDims
    1924,                              // lineNo
    "waveform/selectpeakindex"         // fName
  };

  static rtEqualityCheckInfo h_emlrtECI{ 1,// nDims
    1927,                              // lineNo
    "waveform/selectpeakindex"         // fName
  };

  static rtEqualityCheckInfo i_emlrtECI{ 1,// nDims
    1931,                              // lineNo
    "waveform/selectpeakindex"         // fName
  };

  static rtEqualityCheckInfo j_emlrtECI{ 1,// nDims
    1935,                              // lineNo
    "waveform/selectpeakindex"         // fName
  };

  static rtEqualityCheckInfo k_emlrtECI{ 1,// nDims
    1939,                              // lineNo
    "waveform/selectpeakindex"         // fName
  };

  static rtEqualityCheckInfo l_emlrtECI{ 1,// nDims
    1962,                              // lineNo
    "waveform/selectpeakindex"         // fName
  };

  coder::array<c_struct_T, 2U> b_candidateList;
  coder::array<double, 2U> r;
  coder::array<double, 2U> r1;
  coder::array<double, 2U> y;
  coder::array<double, 1U> r3;
  coder::array<double, 1U> sumScores;
  coder::array<boolean_T, 2U> r2;
  coder::array<boolean_T, 1U> interPulseAligned;
  coder::array<boolean_T, 1U> likelyCaughSingleBigPeak;
  c_struct_T c_candidateList[2];
  double d;
  double interpulseTimeRangeMax;
  double selectedIndex;
  int b_i;
  int i;
  int i1;
  int loop_ub;
  int maxdimlen;
  int nz;
  selectedIndex = (ps_pre->t_ip - ps_pre->t_ipu) - ps_pre->t_ipj;
  interpulseTimeRangeMax = (ps_pre->t_ip + ps_pre->t_ipu) + ps_pre->t_ipj;
  loop_ub = peakIndexList.size(0);
  interPulseAligned.set_size(peakIndexList.size(0));
  for (i = 0; i < loop_ub; i++) {
    interPulseAligned[i] = false;
  }

  if (ps_pre->clst.size(0) * ps_pre->clst.size(1) != 1) {
    // There is a previous candidate list
    for (b_i = 0; b_i < loop_ub; b_i++) {
      //  deltaTimeFromPrev = [candidateList(peakIndexList(i),1:(end-obj.K+2)).t_0]-[obj.ps_pre.clst(peakIndexList(i),end).t_0];
      if (K > 1.0) {
        double deltaTimeFromPrev[2];
        boolean_T c_deltaTimeFromPrev[2];

        // Need to consider first two candidate pulses in case the first was in the last segment due to overlap
        if (b_i + 1 > loop_ub) {
          rtDynamicBoundsError(b_i + 1, 1, loop_ub, ab_emlrtBCI);
        }

        d = peakIndexList[b_i];
        i = static_cast<int>(std::floor(d));
        if (d != i) {
          rtIntegerError(d, q_emlrtDCI);
        }

        if ((d < 1.0) || (static_cast<int>(d) > candidateList.size(0))) {
          rtDynamicBoundsError(static_cast<int>(d), 1, candidateList.size(0),
                               bb_emlrtBCI);
        }

        if (candidateList.size(1) < 1) {
          rtDynamicBoundsError(1, 1, candidateList.size(1), cb_emlrtBCI);
        }

        nz = static_cast<int>(peakIndexList[b_i]) - 1;
        c_candidateList[0] = candidateList[nz];
        if (candidateList.size(1) < 2) {
          rtDynamicBoundsError(2, 1, candidateList.size(1), cb_emlrtBCI);
        }

        c_candidateList[1] = candidateList[nz + candidateList.size(0)];
        coder::internal::b_horzcatStructList(c_candidateList, deltaTimeFromPrev);
        i1 = ps_pre->clst.size(0);
        if (b_i + 1 > loop_ub) {
          rtDynamicBoundsError(b_i + 1, 1, loop_ub, db_emlrtBCI);
        }

        if (static_cast<int>(d) != i) {
          rtIntegerError(d, r_emlrtDCI);
        }

        if (static_cast<int>(d) > i1) {
          rtDynamicBoundsError(static_cast<int>(d), 1, i1, eb_emlrtBCI);
        }

        i1 = ps_pre->clst.size(1);
        maxdimlen = ps_pre->clst.size(1);
        if ((maxdimlen < 1) || (maxdimlen > i1)) {
          rtDynamicBoundsError(maxdimlen, 1, i1, fb_emlrtBCI);
        }

        deltaTimeFromPrev[0] -= ps_pre->clst[(static_cast<int>(d) +
          ps_pre->clst.size(0) * (maxdimlen - 1)) - 1].t_0;
        i1 = ps_pre->clst.size(0);
        if (b_i + 1 > loop_ub) {
          rtDynamicBoundsError(b_i + 1, 1, loop_ub, db_emlrtBCI);
        }

        if (static_cast<int>(d) != i) {
          rtIntegerError(d, r_emlrtDCI);
        }

        if (static_cast<int>(d) > i1) {
          rtDynamicBoundsError(static_cast<int>(d), 1, i1, eb_emlrtBCI);
        }

        i = ps_pre->clst.size(1);
        i1 = ps_pre->clst.size(1);
        if ((i1 < 1) || (i1 > i)) {
          rtDynamicBoundsError(i1, 1, i, fb_emlrtBCI);
        }

        deltaTimeFromPrev[1] -= ps_pre->clst[(static_cast<int>(d) +
          ps_pre->clst.size(0) * (i1 - 1)) - 1].t_0;
        c_deltaTimeFromPrev[0] = ((deltaTimeFromPrev[0] < interpulseTimeRangeMax)
          && (deltaTimeFromPrev[0] > selectedIndex));
        c_deltaTimeFromPrev[1] = ((deltaTimeFromPrev[1] < interpulseTimeRangeMax)
          && (deltaTimeFromPrev[1] > selectedIndex));
        if (b_i + 1 > loop_ub) {
          rtDynamicBoundsError(b_i + 1, 1, loop_ub, gb_emlrtBCI);
        }

        interPulseAligned[b_i] = coder::b_any(c_deltaTimeFromPrev);
      } else {
        double b_deltaTimeFromPrev;

        // Due to overlap, there is a chance that the current
        // detetion is the same as the last detection. This
        // is why we check for time alignment of the first
        // twp pulses in the 'if' statement above. But for K
        // = 1, we only have one pulse to check in the
        // current candidate list. That pulse could be the
        // same as the one in the previous segement due to
        // the overlap. If we are detecting the same pulse as
        // was in the last segment, we can't look back beyond
        // the previous segment, but we can use that pulses
        // confirmation status, which would only have been
        // set if the interpulse duration was correct.
        if (candidateList.size(1) < 1) {
          rtDynamicBoundsError(1, 1, candidateList.size(1), hb_emlrtBCI);
        }

        if (b_i + 1 > loop_ub) {
          rtDynamicBoundsError(b_i + 1, 1, loop_ub, ib_emlrtBCI);
        }

        d = peakIndexList[b_i];
        i = static_cast<int>(std::floor(d));
        if (d != i) {
          rtIntegerError(d, s_emlrtDCI);
        }

        i1 = static_cast<int>(d);
        if ((d < 1.0) || (i1 > candidateList.size(0))) {
          rtDynamicBoundsError(static_cast<int>(d), 1, candidateList.size(0),
                               jb_emlrtBCI);
        }

        maxdimlen = ps_pre->clst.size(0);
        if (b_i + 1 > loop_ub) {
          rtDynamicBoundsError(b_i + 1, 1, loop_ub, kb_emlrtBCI);
        }

        if (i1 != i) {
          rtIntegerError(d, t_emlrtDCI);
        }

        if (i1 > maxdimlen) {
          rtDynamicBoundsError(static_cast<int>(d), 1, maxdimlen, lb_emlrtBCI);
        }

        maxdimlen = ps_pre->clst.size(1);
        nz = ps_pre->clst.size(1);
        if ((nz < 1) || (nz > maxdimlen)) {
          rtDynamicBoundsError(nz, 1, maxdimlen, mb_emlrtBCI);
        }

        b_deltaTimeFromPrev = candidateList[static_cast<int>(d) - 1].t_0 -
          ps_pre->clst[(static_cast<int>(d) + ps_pre->clst.size(0) * (nz - 1)) -
          1].t_0;
        if (b_deltaTimeFromPrev < 2.0 * ps_pre->t_p) {
          // detected same pulse as previous due to overlap
          maxdimlen = ps_pre->clst.size(0);
          if (b_i + 1 > loop_ub) {
            rtDynamicBoundsError(b_i + 1, 1, loop_ub, nb_emlrtBCI);
          }

          if (i1 != i) {
            rtIntegerError(d, u_emlrtDCI);
          }

          if (i1 > maxdimlen) {
            rtDynamicBoundsError(static_cast<int>(d), 1, maxdimlen, ob_emlrtBCI);
          }

          i = ps_pre->clst.size(1);
          i1 = ps_pre->clst.size(1);
          if ((i1 < 1) || (i1 > i)) {
            rtDynamicBoundsError(i1, 1, i, pb_emlrtBCI);
          }

          if (b_i + 1 > loop_ub) {
            rtDynamicBoundsError(b_i + 1, 1, loop_ub, qb_emlrtBCI);
          }

          interPulseAligned[b_i] = ps_pre->clst[(static_cast<int>(d) +
            ps_pre->clst.size(0) * (i1 - 1)) - 1].con_dec;
        } else {
          if (b_i + 1 > loop_ub) {
            rtDynamicBoundsError(b_i + 1, 1, loop_ub, rb_emlrtBCI);
          }

          interPulseAligned[b_i] = ((b_deltaTimeFromPrev <
            interpulseTimeRangeMax) && (b_deltaTimeFromPrev > selectedIndex));
        }
      }
    }
  }

  b_i = candidateList.size(1);
  b_candidateList.set_size(peakIndexList.size(0), candidateList.size(1));
  for (i = 0; i < b_i; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      if (peakIndexList[i1] != static_cast<int>(std::floor(peakIndexList[i1])))
      {
        rtIntegerError(peakIndexList[i1], v_emlrtDCI);
      }

      maxdimlen = static_cast<int>(peakIndexList[i1]);
      if ((maxdimlen < 1) || (maxdimlen > candidateList.size(0))) {
        rtDynamicBoundsError(maxdimlen, 1, candidateList.size(0), sb_emlrtBCI);
      }

      b_candidateList[i1 + b_candidateList.size(0) * i] = candidateList
        [(maxdimlen + candidateList.size(0) * i) - 1];
    }
  }

  coder::internal::b_horzcatStructList(b_candidateList, r);
  selectedIndex = K;
  coder::internal::assertValidSizeArg(static_cast<double>(peakIndexList.size(0)));
  coder::internal::assertValidSizeArg(selectedIndex);
  maxdimlen = 1;
  if (r.size(1) > 1) {
    maxdimlen = r.size(1);
  }

  nz = r.size(1);
  if (nz >= maxdimlen) {
    maxdimlen = nz;
  }

  if (peakIndexList.size(0) > maxdimlen) {
    k_rtErrorWithMessageID(k_emlrtRTEI.fName, k_emlrtRTEI.lineNo);
  }

  if (static_cast<int>(selectedIndex) > maxdimlen) {
    k_rtErrorWithMessageID(k_emlrtRTEI.fName, k_emlrtRTEI.lineNo);
  }

  if (static_cast<int>(selectedIndex) < 0) {
    ib_rtErrorWithMessageID(tb_emlrtRTEI.fName, tb_emlrtRTEI.lineNo);
  }

  b_i = peakIndexList.size(0) * static_cast<int>(selectedIndex);
  if (b_i != r.size(1)) {
    l_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
  }

  nz = peakIndexList.size(0);
  maxdimlen = static_cast<int>(K);
  r1 = r.reshape(nz, maxdimlen);
  coder::sum(r1, sumScores);
  if (K > 1.0) {
    coder::repmat(sumScores, K, y);
    nz = peakIndexList.size(0);
    r1 = r.reshape(nz, maxdimlen);
    coder::internal::assertCompatibleDims(r1, y);
    if ((peakIndexList.size(0) == y.size(0)) && (static_cast<int>(K) == y.size(1)))
    {
      r2.set_size(peakIndexList.size(0), maxdimlen);
      for (i = 0; i < b_i; i++) {
        r2[i] = (r[i] / y[i] > 0.8);
      }

      coder::c_any(r2, likelyCaughSingleBigPeak);
    } else {
      binary_expand_op_24(likelyCaughSingleBigPeak, r, peakIndexList, this, y);
    }

    b_i = likelyCaughSingleBigPeak.size(0);
    for (i = 0; i < b_i; i++) {
      likelyCaughSingleBigPeak[i] = !likelyCaughSingleBigPeak[i];
    }
  } else {
    b_i = sumScores.size(0);
    likelyCaughSingleBigPeak.set_size(sumScores.size(0));
    for (i = 0; i < b_i; i++) {
      likelyCaughSingleBigPeak[i] = true;
    }
  }

  // There are three things we need to consider. 1) Are the pulses
  // aligned in time (interPulseAligned). 2) Are the pulses
  // relatively consistent in their score - ie.
  // doesntContainSingleBigPeak. 3) Which peak had the largest
  // score. We'll selected pulses based on this order of
  // preference.
  //
  //  if sum(interPulseAligned) > 1 | sum(interPulseAligned) == 0
  //      selectedIndex = 1;
  //  else
  //      selectedIndex = find(interPulseAligned);
  //  end
  //
  selectedIndex = rtNaN;
  nz = coder::combineVectorElements(interPulseAligned);
  if (nz == 1) {
    // Only one option that has pulse times aligned with
    // previous segment, so select that even if there are
    // stronger (higher scoring) pulses available
    maxdimlen = coder::c_eml_find(interPulseAligned, (int *)&nz);

    // There will only be 1, but we use n = 1 so coder knows there selectedIndex will be a scalar
    if (maxdimlen < 1) {
      rtDynamicBoundsError(1, 1, maxdimlen, tb_emlrtBCI);
    }

    selectedIndex = nz;
    if (candidateList.size(1) < 1) {
      rtDynamicBoundsError(1, 1, candidateList.size(1), ub_emlrtBCI);
    }

    if ((nz < 1) || (nz > peakIndexList.size(0))) {
      rtDynamicBoundsError(nz, 1, peakIndexList.size(0), vb_emlrtBCI);
    }

    i = static_cast<int>(peakIndexList[nz - 1]);
    if ((i < 1) || (i > candidateList.size(0))) {
      rtDynamicBoundsError(i, 1, candidateList.size(0), wb_emlrtBCI);
    }

    std::printf("Selected peak at frequency %f Hz from center because it was the only one that was aligned in time with candidates from the previ"
                "ous segment.", candidateList[i - 1].fp);
    std::fflush(stdout);
  } else {
    nz = coder::combineVectorElements(interPulseAligned);
    if (nz > 1) {
      if ((peakIndexList.size(0) != likelyCaughSingleBigPeak.size(0)) &&
          ((peakIndexList.size(0) != 1) && (likelyCaughSingleBigPeak.size(0) !=
            1))) {
        emlrtDimSizeImpxCheckR2021b(peakIndexList.size(0),
          likelyCaughSingleBigPeak.size(0), g_emlrtECI);
      }

      if (interPulseAligned.size(0) == likelyCaughSingleBigPeak.size(0)) {
        r3.set_size(peakIndexList.size(0));
        for (i = 0; i < loop_ub; i++) {
          r3[i] = static_cast<double>(interPulseAligned[i]) * static_cast<double>
            (likelyCaughSingleBigPeak[i]);
        }
      } else {
        binary_expand_op_22(r3, interPulseAligned, likelyCaughSingleBigPeak);
      }

      d = coder::blockedSummation(r3, r3.size(0));
      if (d == 1.0) {
        // Single option that doesn't contain a single big
        // peak and pulses are aligned in time so pick that one
        if ((interPulseAligned.size(0) != likelyCaughSingleBigPeak.size(0)) &&
            ((interPulseAligned.size(0) != 1) && (likelyCaughSingleBigPeak.size
              (0) != 1))) {
          emlrtDimSizeImpxCheckR2021b(interPulseAligned.size(0),
            likelyCaughSingleBigPeak.size(0), h_emlrtECI);
        }

        maxdimlen = coder::e_eml_find(r3, (int *)&nz);

        // There will only be 1, but we use n = 1 so coder knows there selectedIndex will be a scalar
        if (maxdimlen < 1) {
          rtDynamicBoundsError(1, 1, maxdimlen, xb_emlrtBCI);
        }

        selectedIndex = nz;
        if (candidateList.size(1) < 1) {
          rtDynamicBoundsError(1, 1, candidateList.size(1), yb_emlrtBCI);
        }

        if ((nz < 1) || (nz > peakIndexList.size(0))) {
          rtDynamicBoundsError(nz, 1, peakIndexList.size(0), ac_emlrtBCI);
        }

        i = static_cast<int>(peakIndexList[nz - 1]);
        if ((i < 1) || (i > candidateList.size(0))) {
          rtDynamicBoundsError(i, 1, candidateList.size(0), bc_emlrtBCI);
        }

        std::printf("Selected peak at frequency %f Hz from center because of those that were aligned in time with candidates from the previous segmen"
                    "t, it was the only one without a single big peak.",
                    candidateList[i - 1].fp);
        std::fflush(stdout);
      } else {
        boolean_T b;
        b = ((interPulseAligned.size(0) != likelyCaughSingleBigPeak.size(0)) &&
             ((interPulseAligned.size(0) != 1) && (likelyCaughSingleBigPeak.size
               (0) != 1)));
        if (b) {
          emlrtDimSizeImpxCheckR2021b(interPulseAligned.size(0),
            likelyCaughSingleBigPeak.size(0), i_emlrtECI);
        }

        if (d > 1.0) {
          // Multiple options that don't contain a single big
          // peak and pulses are aligned in time. Pick the one
          // with the biggest score from that subset.
          if (b) {
            emlrtDimSizeImpxCheckR2021b(interPulseAligned.size(0),
              likelyCaughSingleBigPeak.size(0), j_emlrtECI);
          }

          loop_ub = r3.size(0);
          if ((r3.size(0) != sumScores.size(0)) && ((r3.size(0) != 1) &&
               (sumScores.size(0) != 1))) {
            emlrtDimSizeImpxCheckR2021b(r3.size(0), sumScores.size(0),
              j_emlrtECI);
          }

          if (r3.size(0) == sumScores.size(0)) {
            for (i = 0; i < loop_ub; i++) {
              r3[i] = r3[i] * sumScores[i];
            }

            coder::internal::b_maximum(r3, nz);
          } else {
            binary_expand_op_21(r3, sumScores, nz);
          }

          selectedIndex = nz;
          if (candidateList.size(1) < 1) {
            rtDynamicBoundsError(1, 1, candidateList.size(1), cc_emlrtBCI);
          }

          if ((nz < 1) || (nz > peakIndexList.size(0))) {
            rtDynamicBoundsError(nz, 1, peakIndexList.size(0), dc_emlrtBCI);
          }

          i = static_cast<int>(peakIndexList[nz - 1]);
          if ((i < 1) || (i > candidateList.size(0))) {
            rtDynamicBoundsError(i, 1, candidateList.size(0), ec_emlrtBCI);
          }

          std::printf("Selected peak at frequency %f Hz from center because of those that were aligned in time with candidates from the previous segmen"
                      "t and those without a single big peak, it had the strongst pulses",
                      candidateList[i - 1].fp);
          std::fflush(stdout);
        } else {
          if (b) {
            emlrtDimSizeImpxCheckR2021b(interPulseAligned.size(0),
              likelyCaughSingleBigPeak.size(0), k_emlrtECI);
          }

          if (d == 0.0) {
            // No options that don't contain a single big
            // peak and pulses are aligned in time. Pick the one
            // with the biggest score.
            coder::internal::b_maximum(sumScores, nz);
            selectedIndex = nz;
            if (candidateList.size(1) < 1) {
              rtDynamicBoundsError(1, 1, candidateList.size(1), fc_emlrtBCI);
            }

            if ((nz < 1) || (nz > peakIndexList.size(0))) {
              rtDynamicBoundsError(nz, 1, peakIndexList.size(0), gc_emlrtBCI);
            }

            i = static_cast<int>(peakIndexList[nz - 1]);
            if ((i < 1) || (i > candidateList.size(0))) {
              rtDynamicBoundsError(i, 1, candidateList.size(0), hc_emlrtBCI);
            }

            std::printf("Selected peak at frequency %f Hz from center because there were no pulses that aligned in time with the previous segment that al"
                        "so did not have a single bit peak, so the stronget pulse set was selected.",
                        candidateList[i - 1].fp);
            std::fflush(stdout);
          }
        }
      }
    } else {
      nz = coder::combineVectorElements(interPulseAligned);
      if (nz == 0) {
        // No pulses are aligned in time, so only use single big
        // peak and pulse stregth as decision criteria
        nz = coder::combineVectorElements(likelyCaughSingleBigPeak);
        if (nz == 1) {
          // Single option that doesn't contain a single big
          // peak and pulses are aligned in time so pick that one
          maxdimlen = coder::c_eml_find(likelyCaughSingleBigPeak, (int *)&nz);

          // There will only be 1, but we use n = 1 so coder knows there selectedIndex will be a scalar
          if (maxdimlen < 1) {
            rtDynamicBoundsError(1, 1, maxdimlen, ic_emlrtBCI);
          }

          selectedIndex = nz;
          if (candidateList.size(1) < 1) {
            rtDynamicBoundsError(1, 1, candidateList.size(1), jc_emlrtBCI);
          }

          if ((nz < 1) || (nz > peakIndexList.size(0))) {
            rtDynamicBoundsError(nz, 1, peakIndexList.size(0), kc_emlrtBCI);
          }

          i = static_cast<int>(peakIndexList[nz - 1]);
          if ((i < 1) || (i > candidateList.size(0))) {
            rtDynamicBoundsError(i, 1, candidateList.size(0), lc_emlrtBCI);
          }

          std::printf("Selected peak at frequency %f Hz from center because no pulses that aligned in time with the previous segment were found and thi"
                      "s was the only one that did not have a single big peak.",
                      candidateList[i - 1].fp);
          std::fflush(stdout);
        } else {
          nz = coder::combineVectorElements(likelyCaughSingleBigPeak);
          if (nz > 1) {
            // Multiple options that don't contain a single big
            // peak. Pick the one with the biggest score from that
            // subset.
            loop_ub = likelyCaughSingleBigPeak.size(0);
            if ((likelyCaughSingleBigPeak.size(0) != sumScores.size(0)) &&
                ((likelyCaughSingleBigPeak.size(0) != 1) && (sumScores.size(0)
                  != 1))) {
              emlrtDimSizeImpxCheckR2021b(likelyCaughSingleBigPeak.size(0),
                sumScores.size(0), l_emlrtECI);
            }

            if (likelyCaughSingleBigPeak.size(0) == sumScores.size(0)) {
              sumScores.set_size(likelyCaughSingleBigPeak.size(0));
              for (i = 0; i < loop_ub; i++) {
                sumScores[i] = static_cast<double>(likelyCaughSingleBigPeak[i]) *
                  sumScores[i];
              }

              coder::internal::b_maximum(sumScores, nz);
            } else {
              binary_expand_op_23(likelyCaughSingleBigPeak, sumScores, nz);
            }

            selectedIndex = nz;
            if (candidateList.size(1) < 1) {
              rtDynamicBoundsError(1, 1, candidateList.size(1), mc_emlrtBCI);
            }

            if ((nz < 1) || (nz > peakIndexList.size(0))) {
              rtDynamicBoundsError(nz, 1, peakIndexList.size(0), nc_emlrtBCI);
            }

            i = static_cast<int>(peakIndexList[nz - 1]);
            if ((i < 1) || (i > candidateList.size(0))) {
              rtDynamicBoundsError(i, 1, candidateList.size(0), oc_emlrtBCI);
            }

            std::printf("Selected peak at frequency %f Hz from center because no pulses that aligned in time with the previous segment were found and of "
                        "those that did not have a single big peak, this one had the strongest pulses.",
                        candidateList[i - 1].fp);
            std::fflush(stdout);
          } else {
            nz = coder::combineVectorElements(likelyCaughSingleBigPeak);
            if (nz == 0) {
              // No options that don't contain a single big
              // peak and pulses are aligned in time. Pick the one
              // with the biggest score.
              coder::internal::b_maximum(sumScores, nz);
              selectedIndex = nz;
              if (candidateList.size(1) < 1) {
                rtDynamicBoundsError(1, 1, candidateList.size(1), pc_emlrtBCI);
              }

              if ((nz < 1) || (nz > peakIndexList.size(0))) {
                rtDynamicBoundsError(nz, 1, peakIndexList.size(0), qc_emlrtBCI);
              }

              i = static_cast<int>(peakIndexList[nz - 1]);
              if ((i < 1) || (i > candidateList.size(0))) {
                rtDynamicBoundsError(i, 1, candidateList.size(0), rc_emlrtBCI);
              }

              std::printf("Selected peak at frequency %f Hz from center because no pulses that aligned in time with the previous segment were found and all"
                          " peaks considered had a single big peak. This one had the strongest pulses.",
                          candidateList[i - 1].fp);
              std::fflush(stdout);
            }
          }
        }
      }
    }
  }

  return selectedIndex;
}

//
// Arguments    : coder::array<boolean_T, 1U> &in1
//                const coder::array<boolean_T, 1U> &in2
// Return Type  : void
//
static void b_and(coder::array<boolean_T, 1U> &in1, const coder::array<boolean_T,
                  1U> &in2)
{
  coder::array<boolean_T, 1U> b_in1;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in2.size(0) == 1) {
    loop_ub = in1.size(0);
  } else {
    loop_ub = in2.size(0);
  }

  b_in1.set_size(loop_ub);
  stride_0_0 = (in1.size(0) != 1);
  stride_1_0 = (in2.size(0) != 1);
  for (int i{0}; i < loop_ub; i++) {
    b_in1[i] = (in1[i * stride_0_0] && in2[i * stride_1_0]);
  }

  in1.set_size(loop_ub);
  for (int i{0}; i < loop_ub; i++) {
    in1[i] = b_in1[i];
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
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in2.size(0) == 1) {
    loop_ub = in1.size(0);
  } else {
    loop_ub = in2.size(0);
  }

  b_in1.set_size(loop_ub);
  stride_0_0 = (in1.size(0) != 1);
  stride_1_0 = (in2.size(0) != 1);
  for (int i{0}; i < loop_ub; i++) {
    b_in1[i] = (in1[i * stride_0_0] || in2[i * stride_1_0]);
  }

  in1.set_size(loop_ub);
  for (int i{0}; i < loop_ub; i++) {
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
  int loop_ub;
  int stride_0_0;
  int stride_0_1;
  int stride_1_0;
  int stride_1_1;
  if (in1.size(0) == 1) {
    loop_ub = in2.size(0);
  } else {
    loop_ub = in1.size(0);
  }

  if (in1.size(1) == 1) {
    b_loop_ub = in2.size(1);
  } else {
    b_loop_ub = in1.size(1);
  }

  b_in2.set_size(loop_ub, b_loop_ub);
  stride_0_0 = (in2.size(0) != 1);
  stride_0_1 = (in2.size(1) != 1);
  stride_1_0 = (in1.size(0) != 1);
  stride_1_1 = (in1.size(1) != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (int i{0}; i < b_loop_ub; i++) {
    for (int i1{0}; i1 < loop_ub; i1++) {
      b_in2[i1 + b_in2.size(0) * i] = in2[i1 * stride_0_0 + in2.size(0) *
        aux_0_1] + in1[i1 * stride_1_0 + in1.size(0) * aux_1_1];
    }

    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }

  in1.set_size(loop_ub, b_loop_ub);
  for (int i{0}; i < b_loop_ub; i++) {
    for (int i1{0}; i1 < loop_ub; i1++) {
      in1[i1 + in1.size(0) * i] = b_in2[i1 + b_in2.size(0) * i];
    }
  }
}

//
// Arguments    : waveform *in1
//                const coder::array<double, 2U> &in2
//                const coder::array<double, 2U> &in3
// Return Type  : void
//
static void binary_expand_op_1(waveform *in1, const coder::array<double, 2U>
  &in2, const coder::array<double, 2U> &in3)
{
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in3.size(1) == 1) {
    loop_ub = in2.size(1);
  } else {
    loop_ub = in3.size(1);
  }

  in1->Wf.set_size(loop_ub);
  stride_0_0 = (in2.size(1) != 1);
  stride_1_0 = (in3.size(1) != 1);
  for (int i{0}; i < loop_ub; i++) {
    in1->Wf[i] = in2[i * stride_0_0] + in3[i * stride_1_0];
  }
}

//
// Arguments    : coder::array<boolean_T, 1U> &in1
//                const coder::array<boolean_T, 1U> &in2
//                const coder::array<boolean_T, 1U> &in3
// Return Type  : void
//
static void binary_expand_op_13(coder::array<boolean_T, 1U> &in1, const coder::
  array<boolean_T, 1U> &in2, const coder::array<boolean_T, 1U> &in3)
{
  coder::array<boolean_T, 1U> b_in2;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in3.size(0) == 1) {
    loop_ub = in2.size(0);
  } else {
    loop_ub = in3.size(0);
  }

  b_in2.set_size(loop_ub);
  stride_0_0 = (in2.size(0) != 1);
  stride_1_0 = (in3.size(0) != 1);
  for (int i{0}; i < loop_ub; i++) {
    b_in2[i] = (in2[i * stride_0_0] && in3[i * stride_1_0]);
  }

  in1.set_size(b_in2.size(0) + 1);
  for (int i{0}; i < loop_ub; i++) {
    in1[i] = b_in2[i];
  }

  in1[loop_ub] = true;
}

//
// Arguments    : coder::array<boolean_T, 1U> &in1
//                const coder::array<boolean_T, 1U> &in2
//                const coder::array<boolean_T, 1U> &in3
// Return Type  : void
//
static void binary_expand_op_14(coder::array<boolean_T, 1U> &in1, const coder::
  array<boolean_T, 1U> &in2, const coder::array<boolean_T, 1U> &in3)
{
  coder::array<boolean_T, 1U> b_in2;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in3.size(0) == 1) {
    loop_ub = in2.size(0);
  } else {
    loop_ub = in3.size(0);
  }

  b_in2.set_size(loop_ub);
  stride_0_0 = (in2.size(0) != 1);
  stride_1_0 = (in3.size(0) != 1);
  for (int i{0}; i < loop_ub; i++) {
    b_in2[i] = (in2[i * stride_0_0] && in3[i * stride_1_0]);
  }

  in1.set_size(b_in2.size(0) + 1);
  in1[0] = true;
  for (int i{0}; i < loop_ub; i++) {
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
static void binary_expand_op_15(coder::array<boolean_T, 1U> &in1, const coder::
  array<double, 1U> &in2, int in3, const coder::array<double, 1U> &in4)
{
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in4.size(0) == 1) {
    loop_ub = in3;
  } else {
    loop_ub = in4.size(0);
  }

  in1.set_size(loop_ub);
  stride_0_0 = (in3 != 1);
  stride_1_0 = (in4.size(0) != 1);
  for (int i{0}; i < loop_ub; i++) {
    in1[i] = (in2[i * stride_0_0] > in4[i * stride_1_0]);
  }
}

//
// Arguments    : coder::array<double, 2U> &in1
//                const waveform *in2
// Return Type  : void
//
static void binary_expand_op_17(coder::array<double, 2U> &in1, const waveform
  *in2)
{
  coder::array<creal_T, 2U> b_in2;
  int aux_0_1;
  int aux_1_1;
  int i;
  int i1;
  int loop_ub;
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
  i = (in2->stft->S.size(0) != 1);
  i1 = (in2->stft->S.size(1) != 1);
  stride_1_0 = (in1.size(0) != 1);
  stride_1_1 = (in1.size(1) != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  if (in1.size(1) == 1) {
    loop_ub = in2->stft->S.size(1);
  } else {
    loop_ub = in1.size(1);
  }

  for (int i2{0}; i2 < loop_ub; i2++) {
    int b_loop_ub;
    if (in1.size(0) == 1) {
      b_loop_ub = in2->stft->S.size(0);
    } else {
      b_loop_ub = in1.size(0);
    }

    for (int i3{0}; i3 < b_loop_ub; i3++) {
      int i4;
      i4 = i3 * i;
      b_in2[i3 + b_in2.size(0) * i2].re = in2->stft->S[i4 + in2->stft->S.size(0)
        * aux_0_1].re + in1[i3 * stride_1_0 + in1.size(0) * aux_1_1];
      b_in2[i3 + b_in2.size(0) * i2].im = in2->stft->S[i4 + in2->stft->S.size(0)
        * aux_0_1].im;
    }

    aux_1_1 += stride_1_1;
    aux_0_1 += i1;
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
static void binary_expand_op_18(coder::array<double, 2U> &in1, const coder::
  array<double, 2U> &in2, const coder::array<double, 2U> &in3, int in4, int in5)
{
  coder::array<double, 2U> b_in2;
  int aux_0_1;
  int aux_1_1;
  int b_loop_ub;
  int loop_ub;
  int stride_0_0;
  int stride_0_1;
  int stride_1_0;
  int stride_1_1;
  if (in3.size(0) == 1) {
    loop_ub = in2.size(0);
  } else {
    loop_ub = in3.size(0);
  }

  if (in3.size(1) == 1) {
    b_loop_ub = in2.size(1);
  } else {
    b_loop_ub = in3.size(1);
  }

  b_in2.set_size(loop_ub, b_loop_ub);
  stride_0_0 = (in2.size(0) != 1);
  stride_0_1 = (in2.size(1) != 1);
  stride_1_0 = (in3.size(0) != 1);
  stride_1_1 = (in3.size(1) != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (int i{0}; i < b_loop_ub; i++) {
    for (int i1{0}; i1 < loop_ub; i1++) {
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
// Arguments    : coder::array<boolean_T, 1U> &in1
//                const coder::array<boolean_T, 2U> &in2
//                const coder::array<boolean_T, 2U> &in3
// Return Type  : void
//
static void binary_expand_op_20(coder::array<boolean_T, 1U> &in1, const coder::
  array<boolean_T, 2U> &in2, const coder::array<boolean_T, 2U> &in3)
{
  coder::array<boolean_T, 2U> b_in2;
  int aux_0_1;
  int aux_1_1;
  int b_loop_ub;
  int loop_ub;
  int stride_0_0;
  int stride_0_1;
  int stride_1_0;
  int stride_1_1;
  if (in3.size(0) == 1) {
    loop_ub = in2.size(0);
  } else {
    loop_ub = in3.size(0);
  }

  if (in3.size(1) == 1) {
    b_loop_ub = in2.size(1);
  } else {
    b_loop_ub = in3.size(1);
  }

  b_in2.set_size(loop_ub, b_loop_ub);
  stride_0_0 = (in2.size(0) != 1);
  stride_0_1 = (in2.size(1) != 1);
  stride_1_0 = (in3.size(0) != 1);
  stride_1_1 = (in3.size(1) != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (int i{0}; i < b_loop_ub; i++) {
    for (int i1{0}; i1 < loop_ub; i1++) {
      b_in2[i1 + b_in2.size(0) * i] = ((!in2[i1 * stride_0_0 + in2.size(0) *
        aux_0_1]) || (!in3[i1 * stride_1_0 + in3.size(0) * aux_1_1]));
    }

    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }

  coder::all(b_in2, in1);
}

//
// Arguments    : coder::array<double, 1U> &in1
//                const coder::array<boolean_T, 1U> &in2
//                const coder::array<boolean_T, 1U> &in3
// Return Type  : void
//
static void binary_expand_op_22(coder::array<double, 1U> &in1, const coder::
  array<boolean_T, 1U> &in2, const coder::array<boolean_T, 1U> &in3)
{
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in3.size(0) == 1) {
    loop_ub = in2.size(0);
  } else {
    loop_ub = in3.size(0);
  }

  in1.set_size(loop_ub);
  stride_0_0 = (in2.size(0) != 1);
  stride_1_0 = (in3.size(0) != 1);
  for (int i{0}; i < loop_ub; i++) {
    in1[i] = static_cast<double>(in2[i * stride_0_0]) * static_cast<double>
      (in3[i * stride_1_0]);
  }
}

//
// Arguments    : coder::array<boolean_T, 1U> &in1
//                const coder::array<double, 2U> &in2
//                const coder::array<double, 1U> &in3
//                const waveform *in4
//                const coder::array<double, 2U> &in5
// Return Type  : void
//
static void binary_expand_op_24(coder::array<boolean_T, 1U> &in1, const coder::
  array<double, 2U> &in2, const coder::array<double, 1U> &in3, const waveform
  *in4, const coder::array<double, 2U> &in5)
{
  coder::array<boolean_T, 2U> b_in2;
  int aux_0_1;
  int aux_1_1;
  int b_loop_ub;
  int in3_idx_0;
  int in3_idx_1;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  int stride_1_1;
  in3_idx_0 = in3.size(0);
  in3_idx_1 = static_cast<int>(in4->K);
  if (in5.size(0) == 1) {
    loop_ub = in3_idx_0;
  } else {
    loop_ub = in5.size(0);
  }

  if (in5.size(1) == 1) {
    b_loop_ub = in3_idx_1;
  } else {
    b_loop_ub = in5.size(1);
  }

  b_in2.set_size(loop_ub, b_loop_ub);
  stride_0_0 = (in3_idx_0 != 1);
  in3_idx_1 = (in3_idx_1 != 1);
  stride_1_0 = (in5.size(0) != 1);
  stride_1_1 = (in5.size(1) != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (int i{0}; i < b_loop_ub; i++) {
    for (int i1{0}; i1 < loop_ub; i1++) {
      b_in2[i1 + b_in2.size(0) * i] = (in2[i1 * stride_0_0 + in3_idx_0 * aux_0_1]
        / in5[i1 * stride_1_0 + in5.size(0) * aux_1_1] > 0.8);
    }

    aux_1_1 += stride_1_1;
    aux_0_1 += in3_idx_1;
  }

  coder::c_any(b_in2, in1);
}

//
// Arguments    : coder::array<double, 1U> &in1
//                const coder::array<boolean_T, 1U> &in2
// Return Type  : void
//
static void binary_expand_op_4(coder::array<double, 1U> &in1, const coder::array<
  boolean_T, 1U> &in2)
{
  coder::array<double, 1U> b_in1;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in2.size(0) == 1) {
    loop_ub = in1.size(0);
  } else {
    loop_ub = in2.size(0);
  }

  b_in1.set_size(loop_ub);
  stride_0_0 = (in1.size(0) != 1);
  stride_1_0 = (in2.size(0) != 1);
  for (int i{0}; i < loop_ub; i++) {
    b_in1[i] = in1[i * stride_0_0] * static_cast<double>(in2[i * stride_1_0]);
  }

  in1.set_size(loop_ub);
  for (int i{0}; i < loop_ub; i++) {
    in1[i] = b_in1[i];
  }
}

//
// Arguments    : coder::array<boolean_T, 1U> &in1
//                const coder::array<double, 1U> &in2
//                const waveform *in3
// Return Type  : void
//
static void binary_expand_op_5(coder::array<boolean_T, 1U> &in1, const coder::
  array<double, 1U> &in2, const waveform *in3)
{
  int i;
  int loop_ub;
  int stride_1_0;
  if (in3->thresh.threshVecFine.size(0) == 1) {
    i = in2.size(0);
  } else {
    i = in3->thresh.threshVecFine.size(0);
  }

  in1.set_size(i);
  i = (in2.size(0) != 1);
  stride_1_0 = (in3->thresh.threshVecFine.size(0) != 1);
  if (in3->thresh.threshVecFine.size(0) == 1) {
    loop_ub = in2.size(0);
  } else {
    loop_ub = in3->thresh.threshVecFine.size(0);
  }

  for (int i1{0}; i1 < loop_ub; i1++) {
    in1[i1] = (in2[i1 * i] >= in3->thresh.threshVecFine[i1 * stride_1_0]);
  }
}

//
// Arguments    : coder::array<double, 1U> &in1
//                const coder::array<double, 1U> &in2
//                const coder::array<boolean_T, 1U> &in3
// Return Type  : void
//
static void binary_expand_op_7(coder::array<double, 1U> &in1, const coder::array<
  double, 1U> &in2, const coder::array<boolean_T, 1U> &in3)
{
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in3.size(0) == 1) {
    loop_ub = in2.size(0);
  } else {
    loop_ub = in3.size(0);
  }

  in1.set_size(loop_ub);
  stride_0_0 = (in2.size(0) != 1);
  stride_1_0 = (in3.size(0) != 1);
  for (int i{0}; i < loop_ub; i++) {
    in1[i] = in2[i * stride_0_0] * static_cast<double>(in3[i * stride_1_0]);
  }
}

//
// Arguments    : coder::array<boolean_T, 1U> &in1
//                const coder::array<boolean_T, 1U> &in2
//                const coder::array<boolean_T, 1U> &in3
// Return Type  : void
//
static void c_and(coder::array<boolean_T, 1U> &in1, const coder::array<boolean_T,
                  1U> &in2, const coder::array<boolean_T, 1U> &in3)
{
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in3.size(0) == 1) {
    loop_ub = in2.size(0);
  } else {
    loop_ub = in3.size(0);
  }

  in1.set_size(loop_ub);
  stride_0_0 = (in2.size(0) != 1);
  stride_1_0 = (in3.size(0) != 1);
  for (int i{0}; i < loop_ub; i++) {
    in1[i] = (in2[i * stride_0_0] && in3[i * stride_1_0]);
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
  int loop_ub;
  int stride_0_0;
  int stride_0_1;
  int stride_1_0;
  int stride_1_1;
  if (in2.size(0) == 1) {
    loop_ub = in1.size(0);
  } else {
    loop_ub = in2.size(0);
  }

  if (in2.size(1) == 1) {
    b_loop_ub = in1.size(1);
  } else {
    b_loop_ub = in2.size(1);
  }

  b_in1.set_size(loop_ub, b_loop_ub);
  stride_0_0 = (in1.size(0) != 1);
  stride_0_1 = (in1.size(1) != 1);
  stride_1_0 = (in2.size(0) != 1);
  stride_1_1 = (in2.size(1) != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (int i{0}; i < b_loop_ub; i++) {
    for (int i1{0}; i1 < loop_ub; i1++) {
      b_in1[i1 + b_in1.size(0) * i] = in1[i1 * stride_0_0 + in1.size(0) *
        aux_0_1] - in2[i1 * stride_1_0 + in2.size(0) * aux_1_1];
    }

    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }

  in1.set_size(loop_ub, b_loop_ub);
  for (int i{0}; i < b_loop_ub; i++) {
    for (int i1{0}; i1 < loop_ub; i1++) {
      in1[i1 + in1.size(0) * i] = b_in1[i1 + b_in1.size(0) * i];
    }
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
  int loop_ub;
  int stride_0_0;
  int stride_0_1;
  int stride_1_0;
  int stride_1_1;
  if (in2.size(0) == 1) {
    loop_ub = in1.size(0);
  } else {
    loop_ub = in2.size(0);
  }

  if (in2.size(1) == 1) {
    b_loop_ub = in1.size(1);
  } else {
    b_loop_ub = in2.size(1);
  }

  b_in1.set_size(loop_ub, b_loop_ub);
  stride_0_0 = (in1.size(0) != 1);
  stride_0_1 = (in1.size(1) != 1);
  stride_1_0 = (in2.size(0) != 1);
  stride_1_1 = (in2.size(1) != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (int i{0}; i < b_loop_ub; i++) {
    for (int i1{0}; i1 < loop_ub; i1++) {
      b_in1[i1 + b_in1.size(0) * i] = in1[i1 * stride_0_0 + in1.size(0) *
        aux_0_1] / in2[i1 * stride_1_0 + in2.size(0) * aux_1_1];
    }

    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }

  in1.set_size(loop_ub, b_loop_ub);
  for (int i{0}; i < b_loop_ub; i++) {
    for (int i1{0}; i1 < loop_ub; i1++) {
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
//                const threshold &b_thresh
// Return Type  : waveform *
//
waveform *waveform::init(const creal32_T b_x[1000], double b_Fs, pulsestats
  *b_ps_pre, const threshold &b_thresh)
{
  pulsestats *obj_out;
  waveform *obj;
  coder::array<c_struct_T, 2U> c_ps_pre;
  coder::array<c_struct_T, 2U> d_ps_pre;
  coder::array<double, 2U> f_ps_pre;
  coder::array<boolean_T, 2U> e_ps_pre;
  int loop_ub;
  obj = this;
  obj->x.set_size(1, 0);
  obj->W.set_size(0, 0);
  obj->Wf.set_size(0);

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
  obj->_pobj1.S.set_size(0, 0);
  obj->_pobj1.t.set_size(0);
  obj->_pobj1.f.set_size(0);
  obj->_pobj1.psd.set_size(0);
  obj->_pobj1.wind.set_size(0);
  obj->_pobj1.dt = 0.0;
  obj->_pobj1.T = 0.0;
  obj->stft = &obj->_pobj1;

  // Unknown values but set types
  obj->W.set_size(0, 0);
  obj->Wf.set_size(0);

  // Copy over ps_
  // COPY Creates an exact copy of the pulse stats object as a
  // separate object
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
  obj->setprioridependentprops(b_ps_pre);
  obj->thresh = b_thresh;
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
//                pulsestats &iobj_0
//                wfmstft &iobj_1
// Return Type  : b_waveform *
//
b_waveform *b_waveform::init(const creal32_T b_x[1000], double b_Fs, pulsestats *
  b_ps_pre, pulsestats &iobj_0, wfmstft &iobj_1)
{
  b_waveform *obj;
  pulsestats *obj_out;
  coder::array<c_struct_T, 2U> c_ps_pre;
  coder::array<c_struct_T, 2U> d_ps_pre;
  coder::array<double, 2U> f_ps_pre;
  coder::array<boolean_T, 2U> e_ps_pre;
  int loop_ub;
  obj = this;
  obj->x.set_size(1, 0);

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
  iobj_1.S.set_size(0, 0);
  iobj_1.t.set_size(0);
  iobj_1.f.set_size(0);
  iobj_1.psd.set_size(0);
  iobj_1.wind.set_size(0);
  iobj_1.dt = 0.0;
  iobj_1.T = 0.0;
  obj->stft = &iobj_1;

  // Unknown values but set types
  // Copy over ps_
  // COPY Creates an exact copy of the pulse stats object as a
  // separate object
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
  obj_out = iobj_0.b_init(b_ps_pre->t_p, b_ps_pre->t_ip, b_ps_pre->t_ipu,
    b_ps_pre->t_ipj, b_ps_pre->fp, b_ps_pre->fstart, b_ps_pre->fend, g_ps_pre,
    b_ps_pre->mode, c_ps_pre, d_ps_pre, e_ps_pre, f_ps_pre);

  // ,...
  // obj.thresh);
  obj->ps_pos = obj_out;

  // Current stats are same as previous during construction
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
  // See 2022-07-11 for updates to samples def
  // Don't need the overlap here since the next segment starts at samplesforKpulses+n_ol-n_ol from current sample
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
//                const threshold &b_thresh
//                pulsestats &iobj_0
//                wfmstft &iobj_1
// Return Type  : waveform *
//
waveform *waveform::init(const coder::array<creal32_T, 1U> &b_x, double b_Fs,
  double b_t_0, pulsestats *b_ps_pre, const threshold &b_thresh, pulsestats &
  iobj_0, wfmstft &iobj_1)
{
  pulsestats *obj_out;
  waveform *obj;
  coder::array<c_struct_T, 2U> c_ps_pre;
  coder::array<c_struct_T, 2U> d_ps_pre;
  coder::array<double, 2U> f_ps_pre;
  coder::array<boolean_T, 2U> e_ps_pre;
  int n;
  int n_tmp;
  int u0;
  obj = this;
  obj->x.set_size(1, 0);
  obj->W.set_size(0, 0);
  obj->Wf.set_size(0);
  coder::internal::assertValidSizeArg(static_cast<double>(b_x.size(0)));
  n_tmp = b_x.size(0);
  n = b_x.size(0);
  if (b_x.size(0) < 1) {
    n = 1;
  }

  u0 = b_x.size(0);
  if (u0 >= n) {
    n = u0;
  }

  if (b_x.size(0) > n) {
    k_rtErrorWithMessageID(k_emlrtRTEI.fName, k_emlrtRTEI.lineNo);
  }

  n = b_x.size(0);
  if (n < 0) {
    ib_rtErrorWithMessageID(tb_emlrtRTEI.fName, tb_emlrtRTEI.lineNo);
  }

  // Flatten input to row
  obj->x.set_size(1, b_x.size(0));
  for (u0 = 0; u0 < n_tmp; u0++) {
    obj->x[u0] = b_x[u0];
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
  iobj_1.S.set_size(0, 0);
  iobj_1.t.set_size(0);
  iobj_1.f.set_size(0);
  iobj_1.psd.set_size(0);
  iobj_1.wind.set_size(0);
  iobj_1.dt = 0.0;
  iobj_1.T = 0.0;
  obj->stft = &iobj_1;

  // Unknown values but set types
  obj->W.set_size(0, 0);
  obj->Wf.set_size(0);

  // Copy over ps_
  // COPY Creates an exact copy of the pulse stats object as a
  // separate object
  c_ps_pre.set_size(1, b_ps_pre->pl.size(1));
  n = b_ps_pre->pl.size(0) * b_ps_pre->pl.size(1) - 1;
  for (u0 = 0; u0 <= n; u0++) {
    c_ps_pre[u0] = b_ps_pre->pl[u0];
  }

  d_ps_pre.set_size(b_ps_pre->clst.size(0), b_ps_pre->clst.size(1));
  n = b_ps_pre->clst.size(0) * b_ps_pre->clst.size(1) - 1;
  for (u0 = 0; u0 <= n; u0++) {
    d_ps_pre[u0] = b_ps_pre->clst[u0];
  }

  e_ps_pre.set_size(b_ps_pre->cmsk.size(0), b_ps_pre->cmsk.size(1));
  n = b_ps_pre->cmsk.size(0) * b_ps_pre->cmsk.size(1) - 1;
  for (u0 = 0; u0 <= n; u0++) {
    e_ps_pre[u0] = b_ps_pre->cmsk[u0];
  }

  f_ps_pre.set_size(b_ps_pre->cpki.size(0), b_ps_pre->cpki.size(1));
  n = b_ps_pre->cpki.size(0) * b_ps_pre->cpki.size(1) - 1;
  for (u0 = 0; u0 <= n; u0++) {
    f_ps_pre[u0] = b_ps_pre->cpki[u0];
  }

  double g_ps_pre[2];
  g_ps_pre[0] = b_ps_pre->tmplt[0];
  g_ps_pre[1] = b_ps_pre->tmplt[1];
  obj_out = iobj_0.b_init(b_ps_pre->t_p, b_ps_pre->t_ip, b_ps_pre->t_ipu,
    b_ps_pre->t_ipj, b_ps_pre->fp, b_ps_pre->fstart, b_ps_pre->fend, g_ps_pre,
    b_ps_pre->mode, c_ps_pre, d_ps_pre, e_ps_pre, f_ps_pre);

  // ,...
  // obj.thresh);
  obj->ps_pos = obj_out;

  // Current stats are same as previous during construction
  obj->setprioridependentprops(b_ps_pre);
  obj->thresh = b_thresh;
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
  static rtBoundsCheckInfo ab_emlrtBCI{ 1514,// lineNo
    "obj.ps_pre.pl",                   // aName
    "waveform/process"                 // fName
  };

  static rtBoundsCheckInfo bb_emlrtBCI{ 1519,// lineNo
    "obj.ps_pre.pl",                   // aName
    "waveform/process"                 // fName
  };

  static rtBoundsCheckInfo cb_emlrtBCI{ 1777,// lineNo
    "pk_ind",                          // aName
    "waveform/process"                 // fName
  };

  static rtBoundsCheckInfo db_emlrtBCI{ 1777,// lineNo
    "candidatelist",                   // aName
    "waveform/process"                 // fName
  };

  static rtBoundsCheckInfo eb_emlrtBCI{ 1802,// lineNo
    "conflog",                         // aName
    "waveform/process"                 // fName
  };

  static rtBoundsCheckInfo fb_emlrtBCI{ 1802,// lineNo
    "obj.ps_pos.pl(ip)",               // aName
    "waveform/process"                 // fName
  };

  static rtBoundsCheckInfo gb_emlrtBCI{ 1836,// lineNo
    "obj.ps_pos.pl(tick)",             // aName
    "waveform/process"                 // fName
  };

  static rtBoundsCheckInfo hb_emlrtBCI{ 1839,// lineNo
    "obj.ps_pos.clst(tick)",           // aName
    "waveform/process"                 // fName
  };

  static rtBoundsCheckInfo ib_emlrtBCI{ 1701,// lineNo
    "pk_ind",                          // aName
    "waveform/process"                 // fName
  };

  static rtBoundsCheckInfo jb_emlrtBCI{ 1701,// lineNo
    "candidatelist",                   // aName
    "waveform/process"                 // fName
  };

  static rtBoundsCheckInfo kb_emlrtBCI{ 1732,// lineNo
    "conflog",                         // aName
    "waveform/process"                 // fName
  };

  static rtBoundsCheckInfo lb_emlrtBCI{ 1732,// lineNo
    "obj.ps_pos.pl(ip)",               // aName
    "waveform/process"                 // fName
  };

  static rtBoundsCheckInfo mb_emlrtBCI{ 1744,// lineNo
    "obj.ps_pos.pl(tick)",             // aName
    "waveform/process"                 // fName
  };

  static rtBoundsCheckInfo nb_emlrtBCI{ 1747,// lineNo
    "obj.ps_pos.clst(tick)",           // aName
    "waveform/process"                 // fName
  };

  static rtBoundsCheckInfo ob_emlrtBCI{ 1603,// lineNo
    "pk_ind",                          // aName
    "waveform/process"                 // fName
  };

  static rtBoundsCheckInfo pb_emlrtBCI{ 1603,// lineNo
    "candidatelist",                   // aName
    "waveform/process"                 // fName
  };

  static rtBoundsCheckInfo qb_emlrtBCI{ 1647,// lineNo
    "conflog",                         // aName
    "waveform/process"                 // fName
  };

  static rtBoundsCheckInfo rb_emlrtBCI{ 1647,// lineNo
    "obj.ps_pos.pl(ip)",               // aName
    "waveform/process"                 // fName
  };

  static rtBoundsCheckInfo sb_emlrtBCI{ 1664,// lineNo
    "obj.ps_pos.pl(tick)",             // aName
    "waveform/process"                 // fName
  };

  static rtBoundsCheckInfo tb_emlrtBCI{ 1667,// lineNo
    "obj.ps_pos.clst(tick)",           // aName
    "waveform/process"                 // fName
  };

  static rtDoubleCheckInfo q_emlrtDCI{ 1777,// lineNo
    "waveform/process"                 // fName
  };

  static rtDoubleCheckInfo r_emlrtDCI{ 1777,// lineNo
    "waveform/process"                 // fName
  };

  static rtDoubleCheckInfo s_emlrtDCI{ 1701,// lineNo
    "waveform/process"                 // fName
  };

  static rtDoubleCheckInfo t_emlrtDCI{ 1701,// lineNo
    "waveform/process"                 // fName
  };

  static rtDoubleCheckInfo u_emlrtDCI{ 1603,// lineNo
    "waveform/process"                 // fName
  };

  static rtDoubleCheckInfo v_emlrtDCI{ 1603,// lineNo
    "waveform/process"                 // fName
  };

  static const char b_cv[8]{ 'i', 'n', 'f', 'o', 'r', 'm', 'e', 'd' };

  static const char cv3[7]{ 'c', 'o', 'n', 'f', 'i', 'r', 'm' };

  static const char b_cv2[6]{ 's', 'e', 'a', 'r', 'c', 'h' };

  static const char b_cv1[5]{ 'n', 'a', 'i', 'v', 'e' };

  static const char cv4[5]{ 't', 'r', 'a', 'c', 'k' };

  pulsestats *obj;
  coder::array<c_struct_T, 2U> _in;
  coder::array<c_struct_T, 2U> candidatelist;
  coder::array<double, 1U> pk_ind;
  coder::array<char, 2U> varargin_1;
  coder::array<boolean_T, 2U> b_varargin_1;
  coder::array<boolean_T, 2U> conflog;
  coder::array<boolean_T, 2U> msk;
  coder::array<boolean_T, 1U> c_varargin_1;
  coder::array<boolean_T, 1U> r;
  c_struct_T r1;
  double b_x;
  double c_x;
  double d_x;
  double selected_ind;
  double validatedHoleFilling_idx_1;
  int freq_search_type_size[2];
  int runmode_size[2];
  int time_search_type_size[2];
  int b_index;
  int i;
  int i1;
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
  selected_ind = ps_pre->fstart;
  validatedHoleFilling_idx_1 = ps_pre->fend;
  std::printf("ps_pre.fstart and ps_pre.fend at beginning of PROCESS call: \t %f \t to \t %f.\n",
              selected_ind, validatedHoleFilling_idx_1);
  std::fflush(stdout);

  // (1) is for coder so it knows it is a scalar
  selected_ind = ps_pos->fstart;
  validatedHoleFilling_idx_1 = ps_pos->fend;
  std::printf("ps_pos.fstart and ps_pos.fend at beginning of PROCESS call: \t %f \t to \t %f.\n",
              selected_ind, validatedHoleFilling_idx_1);
  std::fflush(stdout);

  // (1) is for coder so it knows it is a scalar
  selected_ind = ps_pre->fstart;
  validatedHoleFilling_idx_1 = ps_pre->fend;
  have_priori_freq_band = ((!std::isinf(selected_ind)) && (!std::isnan
    (selected_ind)) && ((!std::isinf(validatedHoleFilling_idx_1)) && (!std::
    isnan(validatedHoleFilling_idx_1))));
  i = ps_pre->pl.size(1);
  i1 = ps_pre->pl.size(1);
  if ((i1 < 1) || (i1 > i)) {
    rtDynamicBoundsError(i1, 1, i, ab_emlrtBCI);
  }

  i = ps_pre->pl.size(1);
  i1 = ps_pre->pl.size(1);
  if ((i1 < 1) || (i1 > i)) {
    rtDynamicBoundsError(i1, 1, i, bb_emlrtBCI);
  }

  selected_ind = ps_pre->pl[i1 - 1].t_0;
  validatedHoleFilling_idx_1 = ps_pre->t_p;
  b_x = ps_pre->t_ip;
  c_x = ps_pre->t_ipu;
  d_x = ps_pre->t_ipj;
  have_priori_time = ((!std::isinf(selected_ind)) && (!std::isnan(selected_ind))
                      && ((!std::isinf(validatedHoleFilling_idx_1)) && (!std::
    isnan(validatedHoleFilling_idx_1))) && ((!std::isinf(b_x)) && (!std::isnan
    (b_x))) && ((!std::isinf(c_x)) && (!std::isnan(c_x))) && ((!std::isinf(d_x))
    && (!std::isnan(d_x))));

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
    b_index = 0;
  } else if (mode == 'I') {
    b_index = 1;
  } else if (mode == 'C') {
    b_index = 2;
  } else if (mode == 'T') {
    b_index = 3;
  } else {
    b_index = -1;
  }

  switch (b_index) {
   case 0:
    {
      freq_search_type_size[0] = 1;
      freq_search_type_size[1] = 5;
      time_search_type_size[0] = 1;
      time_search_type_size[1] = 5;
      for (i = 0; i < 5; i++) {
        char c;
        c = b_cv1[i];
        freq_search_type_data[i] = c;
        time_search_type_data[i] = c;
      }

      runmode_size[0] = 1;
      runmode_size[1] = 6;
      for (i = 0; i < 6; i++) {
        runmode_data[i] = b_cv2[i];
      }
    }
    break;

   case 1:
    freq_search_type_size[0] = 1;
    freq_search_type_size[1] = 8;
    for (i = 0; i < 8; i++) {
      freq_search_type_data[i] = b_cv[i];
    }

    time_search_type_size[0] = 1;
    time_search_type_size[1] = 5;
    for (i = 0; i < 5; i++) {
      time_search_type_data[i] = b_cv1[i];
    }

    runmode_size[0] = 1;
    runmode_size[1] = 6;
    for (i = 0; i < 6; i++) {
      runmode_data[i] = b_cv2[i];
    }
    break;

   case 2:
    {
      freq_search_type_size[0] = 1;
      freq_search_type_size[1] = 5;
      time_search_type_size[0] = 1;
      time_search_type_size[1] = 5;
      for (i = 0; i < 5; i++) {
        char c;
        c = b_cv1[i];
        freq_search_type_data[i] = c;
        time_search_type_data[i] = c;
      }

      runmode_size[0] = 1;
      runmode_size[1] = 7;
      for (i = 0; i < 7; i++) {
        runmode_data[i] = cv3[i];
      }
    }
    break;

   case 3:
    {
      freq_search_type_size[0] = 1;
      freq_search_type_size[1] = 8;
      time_search_type_size[0] = 1;
      time_search_type_size[1] = 8;
      for (i = 0; i < 8; i++) {
        char c;
        c = b_cv[i];
        freq_search_type_data[i] = c;
        time_search_type_data[i] = c;
      }

      runmode_size[0] = 1;
      runmode_size[1] = 5;
      for (i = 0; i < 5; i++) {
        runmode_data[i] = cv4[i];
      }
    }
    break;

   default:
    {
      freq_search_type_size[0] = 1;
      freq_search_type_size[1] = 5;
      time_search_type_size[0] = 1;
      time_search_type_size[1] = 5;
      for (i = 0; i < 5; i++) {
        char c;
        c = b_cv1[i];
        freq_search_type_data[i] = c;
        time_search_type_data[i] = c;
      }

      runmode_size[0] = 1;
      runmode_size[1] = 6;
      for (i = 0; i < 6; i++) {
        runmode_data[i] = b_cv2[i];
      }
    }
    break;
  }

  std::printf("================ RUNNING DETECTION ================\n");
  std::fflush(stdout);
  varargin_1.set_size(1, freq_search_type_size[1] + 1);
  b_index = freq_search_type_size[1];
  for (i = 0; i < b_index; i++) {
    varargin_1[i] = freq_search_type_data[i];
  }

  varargin_1[freq_search_type_size[1]] = '\x00';
  std::printf("FREQ SEARCH MODE: %s \n", &varargin_1[0]);
  std::fflush(stdout);
  varargin_1.set_size(1, time_search_type_size[1] + 1);
  b_index = time_search_type_size[1];
  for (i = 0; i < b_index; i++) {
    varargin_1[i] = time_search_type_data[i];
  }

  varargin_1[time_search_type_size[1]] = '\x00';
  std::printf("TIME SEARCH MODE: %s \n", &varargin_1[0]);
  std::fflush(stdout);
  if (coder::internal::b_strcmp(runmode_data, runmode_size)) {
    b_index = 0;
  } else if (coder::internal::c_strcmp(runmode_data, runmode_size)) {
    b_index = 1;
  } else if (coder::internal::d_strcmp(runmode_data, runmode_size)) {
    b_index = 2;
  } else {
    b_index = -1;
  }

  switch (b_index) {
   case 0:
    {
      int loop_ub;

      //             %% SEARCH RUN MODE
      std::printf("DETECTING IN SEARCH MODE.\n");
      std::fflush(stdout);

      // Find all the potential pulses in the dataset
      findpulse(time_search_type_data, time_search_type_size,
                freq_search_type_data, freq_search_type_size,
                excluded_freq_bands, candidatelist, msk, pk_ind);
      coder::internal::horzcatStructList(candidatelist, b_varargin_1);
      b_index = b_varargin_1.size(1);
      c_varargin_1 = b_varargin_1.reshape(b_index);
      have_priori_freq_band = coder::internal::allOrAny_anonFcn1(c_varargin_1);
      if (have_priori_freq_band) {
        loop_ub = pk_ind.size(0);
        r.set_size(pk_ind.size(0));
        for (i = 0; i < loop_ub; i++) {
          r[i] = std::isnan(pk_ind[i]);
        }

        coder::internal::allOrAny_anonFcn1(r);
      } else {
        //  Determine which peak to focus depending on the selection mode
        //  Select a peak if we found had at least one detection
      }

      loop_ub = pk_ind.size(0);
      r.set_size(pk_ind.size(0));
      for (i = 0; i < loop_ub; i++) {
        r[i] = !std::isnan(pk_ind[i]);
      }

      if (coder::internal::ifWhileCond(r)) {
        selected_ind = selectpeakindex(candidatelist, pk_ind);

        // Set the pulselist property in the ps_pos based on the
        // downselection of pulses
        obj = ps_pos;
        if (selected_ind != static_cast<int>(std::floor(selected_ind))) {
          rtIntegerError(selected_ind, u_emlrtDCI);
        }

        if ((static_cast<int>(selected_ind) < 1) || (static_cast<int>
             (selected_ind) > pk_ind.size(0))) {
          rtDynamicBoundsError(static_cast<int>(selected_ind), 1, pk_ind.size(0),
                               ob_emlrtBCI);
        }

        selected_ind = pk_ind[static_cast<int>(selected_ind) - 1];
        if (selected_ind != static_cast<int>(std::floor(selected_ind))) {
          rtIntegerError(selected_ind, v_emlrtDCI);
        }

        if ((static_cast<int>(selected_ind) < 1) || (static_cast<int>
             (selected_ind) > candidatelist.size(0))) {
          rtDynamicBoundsError(static_cast<int>(selected_ind), 1,
                               candidatelist.size(0), pb_emlrtBCI);
        }

        obj->pl.set_size(1, obj->pl.size(1));
        b_index = candidatelist.size(1);
        obj->pl.set_size(obj->pl.size(0), candidatelist.size(1));
        for (i = 0; i < b_index; i++) {
          obj->pl[i] = candidatelist[(static_cast<int>(selected_ind) +
            candidatelist.size(0) * i) - 1];
        }
      } else {
        // If nothing above threshold was found, fill with empty
        // pulse object
        obj = ps_pos;
        r1.A = makepulsestruc(r1.t_next, r1.mode, r1.P, r1.SNR, r1.yw, r1.t_0,
                              r1.t_f, r1.fp, r1.fstart, r1.fend, r1.det_dec,
                              r1.con_dec);
        obj->pl.set_size(1, 1);
        obj->pl[0] = r1;
      }

      // Record all candidates for posterity
      obj = ps_pos;
      obj->clst.set_size(candidatelist.size(0), candidatelist.size(1));
      b_index = candidatelist.size(0) * candidatelist.size(1);
      for (i = 0; i < b_index; i++) {
        obj->clst[i] = candidatelist[i];
      }

      obj = ps_pos;
      obj->cmsk.set_size(msk.size(0), msk.size(1));
      b_index = msk.size(0) * msk.size(1);
      for (i = 0; i < b_index; i++) {
        obj->cmsk[i] = msk[i];
      }

      obj = ps_pos;
      obj->cpki.set_size(pk_ind.size(0), 1);
      conflog.set_size(1, 1);
      conflog[0] = false;

      // Set to all false. Needed
      //  Detection?
      r.set_size(pk_ind.size(0));
      for (i = 0; i < loop_ub; i++) {
        obj->cpki[i] = pk_ind[i];
        r[i] = !std::isnan(pk_ind[i]);
      }

      if (coder::internal::ifWhileCond(r)) {
        // If move to confirm pulses that were real but the pulses before them were
        // noise, the real pulses will not be confirmed and the detector will move
        // back to search mode. Then when it gets to this point, it should try to
        // confirm against the previous detections.
        confirmpulses(this, conflog);
        b_index = conflog.size(0);
        c_varargin_1 = conflog.reshape(b_index);
        have_priori_freq_band = coder::internal::allOrAny_anonFcn1(c_varargin_1);

        //  %True ->
        //  %Update confirmation property for each pulse. False
        //  %recorded for confirmation property since we are
        //  %currently in discovery mode and can't confirm anything
        //  %yet.
        //  for ip = 1:length(obj.ps_pos.pl)
        //      obj.ps_pos.pl(ip).con_dec = false;
        //  end
        //
        //  %   Update Mode Recommendation -> Confirmation
        //  obj.ps_pos.mode = 'C';
      } else {
        // Dection was not made
        //  obj.ps_pos.mode = 'S';%'D';
        have_priori_freq_band = false;
      }

      //  Confirmation?
      if (have_priori_freq_band) {
        i = ps_pos->pl.size(1);
        for (int ip{0}; ip < i; ip++) {
          loop_ub = ps_pos->pl.size(1);
          _in.set_size(1, loop_ub);
          b_index = ps_pos->pl.size(1);
          for (i1 = 0; i1 < b_index; i1++) {
            _in[i1] = ps_pos->pl[i1];
          }

          if (ip + 1 > conflog.size(0)) {
            rtDynamicBoundsError(ip + 1, 1, conflog.size(0), qb_emlrtBCI);
          }

          if (ip + 1 > loop_ub) {
            rtDynamicBoundsError(ip + 1, 1, loop_ub, rb_emlrtBCI);
          }

          _in[ip].con_dec = conflog[ip];
          obj = ps_pos;
          obj->pl.set_size(1, loop_ub);
          for (i1 = 0; i1 < loop_ub; i1++) {
            obj->pl[i1] = _in[i1];
          }
        }

        obj = ps_pos;
        obj->mode = 'T';
      } else {
        r.set_size(pk_ind.size(0));
        for (i = 0; i < loop_ub; i++) {
          r[i] = !std::isnan(pk_ind[i]);
        }

        if (coder::internal::ifWhileCond(r)) {
          // Detection, no confirmation  -> Confirmation mode
          obj = ps_pos;
          obj->mode = 'C';
        } else {
          // No detection, no confirmation  -> Search mode
          obj = ps_pos;
          obj->mode = 'S';
        }
      }

      // Set the mode in the pulse and candidate listing for
      // records. This records the mode that was used in the
      // detection of the record pulses. This is useful for
      // debugging.
      i = ps_pos->pl.size(1);
      for (int ip{0}; ip < i; ip++) {
        loop_ub = ps_pos->pl.size(1);
        _in.set_size(1, loop_ub);
        b_index = ps_pos->pl.size(1);
        for (i1 = 0; i1 < b_index; i1++) {
          _in[i1] = ps_pos->pl[i1];
        }

        if (ip + 1 > loop_ub) {
          rtDynamicBoundsError(ip + 1, 1, loop_ub, sb_emlrtBCI);
        }

        _in[_in.size(0) * ip].mode.set_size(1, 1);
        _in[ip].mode[0] = mode;
        obj = ps_pos;
        obj->pl.set_size(1, loop_ub);
        for (i1 = 0; i1 < loop_ub; i1++) {
          obj->pl[i1] = _in[i1];
        }

        // 'D';
      }

      i = ps_pos->clst.size(0) * ps_pos->clst.size(1);
      for (int ip{0}; ip < i; ip++) {
        i1 = ps_pos->clst.size(0);
        b_index = ps_pos->clst.size(1);
        candidatelist.set_size(i1, b_index);
        loop_ub = ps_pos->clst.size(0) * ps_pos->clst.size(1);
        for (int freq_search_type_tmp{0}; freq_search_type_tmp < loop_ub;
             freq_search_type_tmp++) {
          candidatelist[freq_search_type_tmp] = ps_pos->
            clst[freq_search_type_tmp];
        }

        loop_ub = candidatelist.size(0) * candidatelist.size(1);
        if ((static_cast<int>(static_cast<unsigned int>(ip) + 1U) < 1) || (
             static_cast<int>(static_cast<unsigned int>(ip) + 1U) > loop_ub)) {
          rtDynamicBoundsError(static_cast<int>(static_cast<unsigned int>(ip) +
            1U), 1, loop_ub, tb_emlrtBCI);
        }

        candidatelist[ip].mode.set_size(1, 1);
        candidatelist[ip].mode[0] = mode;
        obj = ps_pos;
        obj->clst.set_size(i1, b_index);
        for (i1 = 0; i1 < loop_ub; i1++) {
          obj->clst[i1] = candidatelist[i1];
        }

        //  'D';
      }

      selected_ind = ps_pre->fstart;
      validatedHoleFilling_idx_1 = ps_pre->fend;
      std::printf("ps_pre.fstart and ps_pre.fend at the end Detection search : \t %f \t to \t %f.\n",
                  selected_ind, validatedHoleFilling_idx_1);
      std::fflush(stdout);

      // (1) is for coder so it knows it is a scalar
      selected_ind = ps_pos->fstart;
      validatedHoleFilling_idx_1 = ps_pos->fend;
      std::printf("ps_pos.fstart and ps_pos.fend at the end Detection search : \t %f \t to \t %f.\n",
                  selected_ind, validatedHoleFilling_idx_1);
      std::fflush(stdout);

      // (1) is for coder so it knows it is a scalar
      //             %% CONFIRMATION MODE
    }
    break;

   case 1:
    {
      int loop_ub;
      std::printf("DETECTING IN CONFIRMATION MODE.\n");
      std::fflush(stdout);

      // Find all the potential pulses in the dataset
      findpulse(time_search_type_data, time_search_type_size,
                freq_search_type_data, freq_search_type_size,
                excluded_freq_bands, candidatelist, msk, pk_ind);
      coder::internal::horzcatStructList(candidatelist, b_varargin_1);
      b_index = b_varargin_1.size(1);
      c_varargin_1 = b_varargin_1.reshape(b_index);
      have_priori_freq_band = coder::internal::allOrAny_anonFcn1(c_varargin_1);
      if (have_priori_freq_band) {
        loop_ub = pk_ind.size(0);
        r.set_size(pk_ind.size(0));
        for (i = 0; i < loop_ub; i++) {
          r[i] = std::isnan(pk_ind[i]);
        }

        coder::internal::allOrAny_anonFcn1(r);
      } else {
        // At least one pulse group met the threshold
      }

      loop_ub = pk_ind.size(0);
      r.set_size(pk_ind.size(0));
      for (i = 0; i < loop_ub; i++) {
        r[i] = !std::isnan(pk_ind[i]);
      }

      if (coder::internal::ifWhileCond(r)) {
        selected_ind = selectpeakindex(candidatelist, pk_ind);

        // Record the detection pulses
        // We only use the highest power pulse group for now
        // because if we are in confirmation mode, we only allow
        // for the selection mode to be 'most'
        obj = ps_pos;
        if (selected_ind != static_cast<int>(std::floor(selected_ind))) {
          rtIntegerError(selected_ind, s_emlrtDCI);
        }

        if ((static_cast<int>(selected_ind) < 1) || (static_cast<int>
             (selected_ind) > pk_ind.size(0))) {
          rtDynamicBoundsError(static_cast<int>(selected_ind), 1, pk_ind.size(0),
                               ib_emlrtBCI);
        }

        selected_ind = pk_ind[static_cast<int>(selected_ind) - 1];
        if (selected_ind != static_cast<int>(std::floor(selected_ind))) {
          rtIntegerError(selected_ind, t_emlrtDCI);
        }

        if ((static_cast<int>(selected_ind) < 1) || (static_cast<int>
             (selected_ind) > candidatelist.size(0))) {
          rtDynamicBoundsError(static_cast<int>(selected_ind), 1,
                               candidatelist.size(0), jb_emlrtBCI);
        }

        obj->pl.set_size(1, obj->pl.size(1));
        b_index = candidatelist.size(1);
        obj->pl.set_size(obj->pl.size(0), candidatelist.size(1));
        for (i = 0; i < b_index; i++) {
          obj->pl[i] = candidatelist[(static_cast<int>(selected_ind) +
            candidatelist.size(0) * i) - 1];
        }
      } else {
        // If nothing above threshold was found, fill with empty
        // pulse object
        obj = ps_pos;
        r1.A = makepulsestruc(r1.t_next, r1.mode, r1.P, r1.SNR, r1.yw, r1.t_0,
                              r1.t_f, r1.fp, r1.fstart, r1.fend, r1.det_dec,
                              r1.con_dec);
        obj->pl.set_size(1, 1);
        obj->pl[0] = r1;
      }

      // Record all candidates for posterity
      obj = ps_pos;
      obj->clst.set_size(candidatelist.size(0), candidatelist.size(1));
      b_index = candidatelist.size(0) * candidatelist.size(1);
      for (i = 0; i < b_index; i++) {
        obj->clst[i] = candidatelist[i];
      }

      obj = ps_pos;
      obj->cmsk.set_size(msk.size(0), msk.size(1));
      b_index = msk.size(0) * msk.size(1);
      for (i = 0; i < b_index; i++) {
        obj->cmsk[i] = msk[i];
      }

      obj = ps_pos;
      obj->cpki.set_size(pk_ind.size(0), 1);
      conflog.set_size(1, 1);
      conflog[0] = false;

      // Set to all false. Needed
      //  Detection?
      r.set_size(pk_ind.size(0));
      for (i = 0; i < loop_ub; i++) {
        obj->cpki[i] = pk_ind[i];
        r[i] = !std::isnan(pk_ind[i]);
      }

      if (coder::internal::ifWhileCond(r)) {
        confirmpulses(this, conflog);

        // Confirmation?
        b_index = conflog.size(0);
        c_varargin_1 = conflog.reshape(b_index);
        have_priori_freq_band = coder::internal::allOrAny_anonFcn1(c_varargin_1);
      } else {
        // False ->
        // Set confirmation = False
        have_priori_freq_band = false;
      }

      if (have_priori_freq_band) {
        i = ps_pos->pl.size(1);
        for (int ip{0}; ip < i; ip++) {
          loop_ub = ps_pos->pl.size(1);
          _in.set_size(1, loop_ub);
          b_index = ps_pos->pl.size(1);
          for (i1 = 0; i1 < b_index; i1++) {
            _in[i1] = ps_pos->pl[i1];
          }

          if (ip + 1 > conflog.size(0)) {
            rtDynamicBoundsError(ip + 1, 1, conflog.size(0), kb_emlrtBCI);
          }

          if (ip + 1 > loop_ub) {
            rtDynamicBoundsError(ip + 1, 1, loop_ub, lb_emlrtBCI);
          }

          _in[ip].con_dec = conflog[ip];
          obj = ps_pos;
          obj->pl.set_size(1, loop_ub);
          for (i1 = 0; i1 < loop_ub; i1++) {
            obj->pl[i1] = _in[i1];
          }
        }

        obj = ps_pos;
        obj->mode = 'T';
      } else {
        obj = ps_pos;
        obj->mode = 'S';
      }

      // Set the mode in the pulse and candidate listing for
      // records. This records the mode that was used in the
      // detection of the record pulses. This is useful for
      // debugging.
      i = ps_pos->pl.size(1);
      for (int ip{0}; ip < i; ip++) {
        loop_ub = ps_pos->pl.size(1);
        _in.set_size(1, loop_ub);
        b_index = ps_pos->pl.size(1);
        for (i1 = 0; i1 < b_index; i1++) {
          _in[i1] = ps_pos->pl[i1];
        }

        if (ip + 1 > loop_ub) {
          rtDynamicBoundsError(ip + 1, 1, loop_ub, mb_emlrtBCI);
        }

        _in[_in.size(0) * ip].mode.set_size(1, 1);
        _in[ip].mode[0] = mode;
        obj = ps_pos;
        obj->pl.set_size(1, loop_ub);
        for (i1 = 0; i1 < loop_ub; i1++) {
          obj->pl[i1] = _in[i1];
        }

        // 'C';
      }

      i = ps_pos->clst.size(0) * ps_pos->clst.size(1);
      for (int ip{0}; ip < i; ip++) {
        i1 = ps_pos->clst.size(0);
        b_index = ps_pos->clst.size(1);
        candidatelist.set_size(i1, b_index);
        loop_ub = ps_pos->clst.size(0) * ps_pos->clst.size(1);
        for (int freq_search_type_tmp{0}; freq_search_type_tmp < loop_ub;
             freq_search_type_tmp++) {
          candidatelist[freq_search_type_tmp] = ps_pos->
            clst[freq_search_type_tmp];
        }

        loop_ub = candidatelist.size(0) * candidatelist.size(1);
        if ((static_cast<int>(static_cast<unsigned int>(ip) + 1U) < 1) || (
             static_cast<int>(static_cast<unsigned int>(ip) + 1U) > loop_ub)) {
          rtDynamicBoundsError(static_cast<int>(static_cast<unsigned int>(ip) +
            1U), 1, loop_ub, nb_emlrtBCI);
        }

        candidatelist[ip].mode.set_size(1, 1);
        candidatelist[ip].mode[0] = mode;
        obj = ps_pos;
        obj->clst.set_size(i1, b_index);
        for (i1 = 0; i1 < loop_ub; i1++) {
          obj->clst[i1] = candidatelist[i1];
        }

        // 'C';
      }

      selected_ind = ps_pre->fstart;
      validatedHoleFilling_idx_1 = ps_pre->fend;
      std::printf("ps_pre.fstart and ps_pre.fend at the end Confirmation search : \t %f \t to \t %f.\n",
                  selected_ind, validatedHoleFilling_idx_1);
      std::fflush(stdout);

      // (1) is for coder so it knows it is a scalar
      selected_ind = ps_pos->fstart;
      validatedHoleFilling_idx_1 = ps_pos->fend;
      std::printf("ps_pos.fstart and ps_pos.fend at the end Confirmation search : \t %f \t to \t %f.\n",
                  selected_ind, validatedHoleFilling_idx_1);
      std::fflush(stdout);

      // (1) is for coder so it knows it is a scalar
    }
    break;

   case 2:
    {
      int freq_search_type_tmp;
      int loop_ub;

      //                 %% TRACKING MODE
      std::printf("DETECTING IN TRACKING MODE.\n");
      std::fflush(stdout);

      // Find all the potential pulses in the dataset
      findpulse(time_search_type_data, time_search_type_size,
                freq_search_type_data, freq_search_type_size,
                excluded_freq_bands, candidatelist, msk, pk_ind);
      coder::internal::horzcatStructList(candidatelist, b_varargin_1);
      b_index = b_varargin_1.size(1);
      c_varargin_1 = b_varargin_1.reshape(b_index);
      have_priori_freq_band = coder::internal::allOrAny_anonFcn1(c_varargin_1);
      if (have_priori_freq_band) {
        loop_ub = pk_ind.size(0);
        r.set_size(pk_ind.size(0));
        for (i = 0; i < loop_ub; i++) {
          r[i] = std::isnan(pk_ind[i]);
        }

        coder::internal::allOrAny_anonFcn1(r);
      } else {
        // At least one pulse group met the threshold
      }

      loop_ub = pk_ind.size(0);
      r.set_size(pk_ind.size(0));
      for (i = 0; i < loop_ub; i++) {
        r[i] = !std::isnan(pk_ind[i]);
      }

      if (coder::internal::ifWhileCond(r)) {
        selected_ind = selectpeakindex(candidatelist, pk_ind);

        // Record the detection pulses
        // We only use the highest power pulse group for now
        // because if we are in confirmation mode, we only allow
        // for the selection mode to be 'most'
        obj = ps_pos;
        if (selected_ind != static_cast<int>(std::floor(selected_ind))) {
          rtIntegerError(selected_ind, q_emlrtDCI);
        }

        if ((static_cast<int>(selected_ind) < 1) || (static_cast<int>
             (selected_ind) > pk_ind.size(0))) {
          rtDynamicBoundsError(static_cast<int>(selected_ind), 1, pk_ind.size(0),
                               cb_emlrtBCI);
        }

        selected_ind = pk_ind[static_cast<int>(selected_ind) - 1];
        if (selected_ind != static_cast<int>(std::floor(selected_ind))) {
          rtIntegerError(selected_ind, r_emlrtDCI);
        }

        if ((static_cast<int>(selected_ind) < 1) || (static_cast<int>
             (selected_ind) > candidatelist.size(0))) {
          rtDynamicBoundsError(static_cast<int>(selected_ind), 1,
                               candidatelist.size(0), db_emlrtBCI);
        }

        obj->pl.set_size(1, obj->pl.size(1));
        b_index = candidatelist.size(1);
        obj->pl.set_size(obj->pl.size(0), candidatelist.size(1));
        for (i = 0; i < b_index; i++) {
          obj->pl[i] = candidatelist[(static_cast<int>(selected_ind) +
            candidatelist.size(0) * i) - 1];
        }
      } else {
        // Nothing met the threshold for detection
        obj = ps_pos;
        r1.A = makepulsestruc(r1.t_next, r1.mode, r1.P, r1.SNR, r1.yw, r1.t_0,
                              r1.t_f, r1.fp, r1.fstart, r1.fend, r1.det_dec,
                              r1.con_dec);
        obj->pl.set_size(1, 1);
        obj->pl[0] = r1;
      }

      obj = ps_pos;
      obj->clst.set_size(candidatelist.size(0), candidatelist.size(1));
      b_index = candidatelist.size(0) * candidatelist.size(1);
      for (i = 0; i < b_index; i++) {
        obj->clst[i] = candidatelist[i];
      }

      obj = ps_pos;
      obj->cmsk.set_size(msk.size(0), msk.size(1));
      b_index = msk.size(0) * msk.size(1);
      for (i = 0; i < b_index; i++) {
        obj->cmsk[i] = msk[i];
      }

      obj = ps_pos;
      obj->cpki.set_size(pk_ind.size(0), 1);

      //  Detection?
      r.set_size(pk_ind.size(0));
      for (i = 0; i < loop_ub; i++) {
        obj->cpki[i] = pk_ind[i];
        r[i] = !std::isnan(pk_ind[i]);
      }

      if (coder::internal::ifWhileCond(r)) {
        // ~isempty(pulselist)%obj.decide(pulselist,PF,decision_table) %Decision on IDed pulses
        // True ->
        confirmpulses(this, conflog);

        // [minstartlog', maxstartlog', freqInBand', conflog']
        freq_search_type_tmp = conflog.size(0);
        b_index = conflog.size(0);
        c_varargin_1 = conflog.reshape(b_index);
        have_priori_freq_band = coder::internal::allOrAny_anonFcn1(c_varargin_1);
        if (have_priori_freq_band) {
          //  	Confirmed?
          //  		True -> Confirmation = True
          have_priori_freq_band = true;

          // Update confirmation property for each pulse
          i = ps_pos->pl.size(1);
          for (int ip{0}; ip < i; ip++) {
            // obj.ps_pos.pl(ip).con_dec = true;
            loop_ub = ps_pos->pl.size(1);
            _in.set_size(1, loop_ub);
            b_index = ps_pos->pl.size(1);
            for (i1 = 0; i1 < b_index; i1++) {
              _in[i1] = ps_pos->pl[i1];
            }

            if (ip + 1 > freq_search_type_tmp) {
              rtDynamicBoundsError(ip + 1, 1, freq_search_type_tmp, eb_emlrtBCI);
            }

            if (ip + 1 > loop_ub) {
              rtDynamicBoundsError(ip + 1, 1, loop_ub, fb_emlrtBCI);
            }

            _in[ip].con_dec = conflog[ip];
            obj = ps_pos;
            obj->pl.set_size(1, loop_ub);
            for (i1 = 0; i1 < loop_ub; i1++) {
              obj->pl[i1] = _in[i1];
            }
          }

          // Update mode suggestion for next segment processing
          //    Mode -> Tracking
          obj = ps_pos;
          obj->mode = mode;

          // 'T';
        } else {
          //  		False -> Confirmation = False
          have_priori_freq_band = false;
        }
      } else {
        // False ->
        // Set confirmation = False
        have_priori_freq_band = false;
      }

      //  Handle not confirmed
      if (!have_priori_freq_band) {
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
      i = ps_pos->pl.size(1);
      for (int ip{0}; ip < i; ip++) {
        loop_ub = ps_pos->pl.size(1);
        _in.set_size(1, loop_ub);
        b_index = ps_pos->pl.size(1);
        for (i1 = 0; i1 < b_index; i1++) {
          _in[i1] = ps_pos->pl[i1];
        }

        if (ip + 1 > loop_ub) {
          rtDynamicBoundsError(ip + 1, 1, loop_ub, gb_emlrtBCI);
        }

        _in[_in.size(0) * ip].mode.set_size(1, 1);
        _in[ip].mode[0] = mode;
        obj = ps_pos;
        obj->pl.set_size(1, loop_ub);
        for (i1 = 0; i1 < loop_ub; i1++) {
          obj->pl[i1] = _in[i1];
        }

        //  'T';
      }

      i = ps_pos->clst.size(0) * ps_pos->clst.size(1);
      for (int ip{0}; ip < i; ip++) {
        i1 = ps_pos->clst.size(0);
        b_index = ps_pos->clst.size(1);
        candidatelist.set_size(i1, b_index);
        loop_ub = ps_pos->clst.size(0) * ps_pos->clst.size(1);
        for (freq_search_type_tmp = 0; freq_search_type_tmp < loop_ub;
             freq_search_type_tmp++) {
          candidatelist[freq_search_type_tmp] = ps_pos->
            clst[freq_search_type_tmp];
        }

        loop_ub = candidatelist.size(0) * candidatelist.size(1);
        if ((static_cast<int>(static_cast<unsigned int>(ip) + 1U) < 1) || (
             static_cast<int>(static_cast<unsigned int>(ip) + 1U) > loop_ub)) {
          rtDynamicBoundsError(static_cast<int>(static_cast<unsigned int>(ip) +
            1U), 1, loop_ub, hb_emlrtBCI);
        }

        candidatelist[ip].mode.set_size(1, 1);
        candidatelist[ip].mode[0] = mode;
        obj = ps_pos;
        obj->clst.set_size(i1, b_index);
        for (i1 = 0; i1 < loop_ub; i1++) {
          obj->clst[i1] = candidatelist[i1];
        }

        //  'T';
      }

      selected_ind = ps_pre->fstart;
      validatedHoleFilling_idx_1 = ps_pre->fend;
      std::printf("ps_pre.fstart and ps_pre.fend at the end Tracking search : \t %f \t to \t %f.\n",
                  selected_ind, validatedHoleFilling_idx_1);
      std::fflush(stdout);

      // (1) is for coder so it knows it is a scalar
      selected_ind = ps_pos->fstart;
      validatedHoleFilling_idx_1 = ps_pos->fend;
      std::printf("ps_pos.fstart and ps_pre.fend at the end Tracking search : \t %f \t to \t %f.\n",
                  selected_ind, validatedHoleFilling_idx_1);
      std::fflush(stdout);

      // (1) is for coder so it knows it is a scalar
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

  // See 2022-07-11 for updates to samples def
  n_ipu = t_0 + ((b_n_ws * ((n_ipu * (b_N + b_M) + n_ipj) + 1.0) + b_n_ol) -
                 b_n_ws * (2.0 * (n_ipu * b_M + n_ipj))) / Fs;
  t_nextsegstart[0] = n_ipu;
  t_nextsegstart[1] = n_ipu;

  // Don't need the overlap here since the next segment starts at samplesforKpulses+n_ol-n_ol from current sample
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
  static rtBoundsCheckInfo ab_emlrtBCI{ 159,// lineNo
    "stackedToeplitzMatrices",         // aName
    "weightingmatrix"                  // fName
  };

  static rtBoundsCheckInfo bb_emlrtBCI{ 159,// lineNo
    "stackedToeplitzMatrices",         // aName
    "weightingmatrix"                  // fName
  };

  static rtBoundsCheckInfo cb_emlrtBCI{ 159,// lineNo
    "Xs",                              // aName
    "weightingmatrix"                  // fName
  };

  static rtBoundsCheckInfo db_emlrtBCI{ 191,// lineNo
    "W",                               // aName
    "weightingmatrix"                  // fName
  };

  static rtBoundsCheckInfo eb_emlrtBCI{ 181,// lineNo
    "freqs",                           // aName
    "weightingmatrix"                  // fName
  };

  static rtDoubleCheckInfo q_emlrtDCI{ 53,// lineNo
    "gettemplate"                      // fName
  };

  static rtDoubleCheckInfo r_emlrtDCI{ 183,// lineNo
    "weightingmatrix"                  // fName
  };

  static rtDoubleCheckInfo s_emlrtDCI{ 155,// lineNo
    "weightingmatrix"                  // fName
  };

  static rtEqualityCheckInfo g_emlrtECI{ -1,// nDims
    180,                               // lineNo
    "weightingmatrix"                  // fName
  };

  static rtEqualityCheckInfo h_emlrtECI{ -1,// nDims
    147,                               // lineNo
    "weightingmatrix"                  // fName
  };

  static rtEqualityCheckInfo i_emlrtECI{ -1,// nDims
    145,                               // lineNo
    "weightingmatrix"                  // fName
  };

  static rtEqualityCheckInfo j_emlrtECI{ 1,// nDims
    146,                               // lineNo
    "weightingmatrix"                  // fName
  };

  static rtEqualityCheckInfo k_emlrtECI{ -1,// nDims
    159,                               // lineNo
    "weightingmatrix"                  // fName
  };

  static rtEqualityCheckInfo l_emlrtECI{ 1,// nDims
    184,                               // lineNo
    "weightingmatrix"                  // fName
  };

  coder::array<creal_T, 2U> Xs;
  coder::array<creal_T, 2U> _in;
  coder::array<creal_T, 2U> b_s;
  coder::array<creal_T, 2U> currDFT;
  coder::array<creal_T, 2U> s;
  coder::array<creal_T, 2U> stackedToeplitzMatrices;
  coder::array<creal_T, 1U> b_Xs;
  coder::array<creal_T, 1U> c_Xs;
  coder::array<creal_T, 1U> r;
  coder::array<double, 2U> output_samps;
  coder::array<double, 2U> w_time_domain;
  coder::array<double, 2U> wrapper;
  coder::array<double, 2U> x_of_n;
  coder::array<int, 1U> iidx;
  coder::array<boolean_T, 2U> b_output_samps;
  double tmplt_samps[2];
  double ai;
  double b_Fs;
  double y_im;
  int b_w_time_domain[2];
  int b_loop_ub;
  int b_loop_ub_tmp;
  int i;
  int i1;
  int loop_ub;
  int loop_ub_tmp;
  int n;
  int nw_tmp;
  unsigned int rowStart;
  boolean_T b;
  if (stft->f.size(0) == 0) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }

  n = stft->f.size(0);

  // Build a pulse time domain template with the same number
  // of samples as frequency bins:
  // GETTEMPLATE Generates a time domain template of the the signal template
  //  (tmplt)in the priori pulsestats object in the waveform passed to the
  //  function. The returned vector is the template at the waveform's sample
  //  rate. The caller can request a total number of samples greater than the
  //  samples required to describe the signal. This is useful if the call will
  //  be using a DFT on the result and wants a specific number of samples to
  //  ensure a particular frequency resolution.
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
  // --------------------------------------------------------------------------
  // Sort out the samples input, if submitted by the caller
  ai = ps_pre->t_p * Fs;
  ai = std::ceil(ai);
  if (n < ai) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }

  // Generates a the template in the time domain at the sample rate of the
  // waveform.
  tmplt_samps[1] = ai;
  tmplt_samps[0] = 0.0;
  coder::linspace(ai, ai, output_samps);
  coder::interp1(tmplt_samps, ps_pre->tmplt, output_samps, w_time_domain);

  // Generate the extra-zeros needed to pad to get to 'samples' samples
  loop_ub = n - output_samps.size(1);
  if (loop_ub < 0) {
    rtNonNegativeError(static_cast<double>(loop_ub), q_emlrtDCI);
  }

  output_samps.set_size(1, loop_ub);
  for (i = 0; i < loop_ub; i++) {
    output_samps[i] = 0.0;
  }

  i = w_time_domain.size(1);
  b_loop_ub = w_time_domain.size(1) + output_samps.size(1);
  w_time_domain.set_size(w_time_domain.size(0), b_loop_ub);
  for (i1 = 0; i1 < loop_ub; i1++) {
    w_time_domain[i + i1] = 0.0;
  }

  // Build a rectagular waveform in the time domain with the same number of samples as frequency bins
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
    x_of_n.set_size(b_loop_ub, 1);
    for (i = 0; i < b_loop_ub; i++) {
      x_of_n[i] = w_time_domain[i];
    }
  } else {
    x_of_n.set_size(1, 1);
    x_of_n[0] = w_time_domain[0];
  }

  nw_tmp = x_of_n.size(0);

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
  loop_ub_tmp = x_of_n.size(0) << 1;
  for (i = 0; i < loop_ub_tmp; i++) {
    s[i].re = 0.0;
    s[i].im = 0.0;
  }

  Xs.set_size(x_of_n.size(0), 2);
  for (i = 0; i < loop_ub_tmp; i++) {
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
  loop_ub_tmp = output_samps.size(1);
  for (int b_i{0}; b_i < 2; b_i++) {
    double y;
    y_im = 0.5 * static_cast<double>(b_i) * 6.2831853071795862;
    r.set_size(loop_ub_tmp);
    for (i = 0; i < loop_ub_tmp; i++) {
      ai = y_im * output_samps[i];
      if (ai == 0.0) {
        r[i].re = 0.0 / static_cast<double>(nw_tmp);
        r[i].im = 0.0;
      } else {
        r[i].re = 0.0;
        r[i].im = ai / static_cast<double>(nw_tmp);
      }
    }

    coder::b_exp(r);
    n = s.size(0);
    rtSubAssignSizeCheck(s.size(), 1, r.size(), 1, i_emlrtECI);
    for (i = 0; i < n; i++) {
      s[i + s.size(0) * b_i] = r[i];
    }

    if ((s.size(0) != x_of_n.size(0)) && ((s.size(0) != 1) && (x_of_n.size(0) !=
          1))) {
      emlrtDimSizeImpxCheckR2021b(s.size(0), x_of_n.size(0), j_emlrtECI);
    }

    if (s.size(0) == x_of_n.size(0)) {
      b_s.set_size(s.size(0), 1);
      for (i = 0; i < n; i++) {
        b_s[i].re = x_of_n[i] * s[i + s.size(0) * b_i].re;
        b_s[i].im = x_of_n[i] * s[i + s.size(0) * b_i].im;
      }

      coder::fft(b_s, currDFT);
    } else {
      binary_expand_op(currDFT, s, b_i, x_of_n);
    }

    y = coder::b_norm(currDFT);
    currDFT.set_size(currDFT.size(0), 1);
    loop_ub = currDFT.size(0) - 1;
    for (i = 0; i <= loop_ub; i++) {
      y_im = currDFT[i].re;
      ai = currDFT[i].im;
      if (ai == 0.0) {
        y_im /= y;
        ai = 0.0;
      } else if (y_im == 0.0) {
        y_im = 0.0;
        ai /= y;
      } else {
        y_im /= y;
        ai /= y;
      }

      currDFT[i].re = y_im;
      currDFT[i].im = ai;
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
    // --------------------------------------------------------------------------
    // Passed a matrix or a column vector
    y_im = coder::b_mod(static_cast<double>(currDFT.size(0)));
    if (std::isnan(y_im)) {
      y_rtErrorWithMessageID(hb_emlrtRTEI.fName, hb_emlrtRTEI.lineNo);
    }

    if (y_im != 0.0) {
      coder::fftshift(currDFT);
    } else {
      coder::fftshift(currDFT);
      coder::circshift(currDFT);
    }

    rtSubAssignSizeCheck(&nw_tmp, 1, currDFT.size(), 2, h_emlrtECI);
    for (i = 0; i < nw_tmp; i++) {
      Xs[i + Xs.size(0) * b_i] = currDFT[i];
    }

    //    stem(freqs_orig,abs(Xs(:,i)),'DisplayName',['\zeta =',num2str(zetas(i))]);
    //    hold on
  }

  // ylabel('|Xs|');xlabel('Frequency');legend('Location',"best");
  // title('DFT of primary frequency shifts of the template')
  // New W generation method. ~25% faster on average
  ai = 2.0 * static_cast<double>(x_of_n.size(0));
  if (ai != static_cast<int>(ai)) {
    rtIntegerError(ai, s_emlrtDCI);
  }

  loop_ub = x_of_n.size(0);
  stackedToeplitzMatrices.set_size(static_cast<int>(ai), x_of_n.size(0));
  loop_ub_tmp = static_cast<int>(ai) * x_of_n.size(0);
  for (i = 0; i < loop_ub_tmp; i++) {
    stackedToeplitzMatrices[i].re = 0.0;
    stackedToeplitzMatrices[i].im = 0.0;
  }

  if (Xs.size(0) < 2) {
    i = 0;
    i1 = 0;
  } else {
    i = 1;
    i1 = x_of_n.size(0);
  }

  b_loop_ub_tmp = i1 - i;
  for (int b_i{0}; b_i < 2; b_i++) {
    int i2;
    unsigned int rowEnd;
    rowStart = static_cast<unsigned int>(b_i * nw_tmp) + 1U;
    rowEnd = (rowStart + static_cast<unsigned int>(nw_tmp)) - 1U;
    if (rowStart > rowEnd) {
      i1 = 0;
      i2 = 0;
    } else {
      if ((static_cast<int>(rowStart) < 1) || (static_cast<int>(rowStart) >
           static_cast<int>(ai))) {
        rtDynamicBoundsError(static_cast<int>(rowStart), 1, static_cast<int>(ai),
                             bb_emlrtBCI);
      }

      i1 = static_cast<int>(rowStart) - 1;
      if ((static_cast<int>(rowEnd) < 1) || (static_cast<int>(rowEnd) >
           static_cast<int>(ai))) {
        rtDynamicBoundsError(static_cast<int>(rowEnd), 1, static_cast<int>(ai),
                             ab_emlrtBCI);
      }

      i2 = static_cast<int>(rowEnd);
    }

    if (nw_tmp < 1) {
      rtDynamicBoundsError(1, 1, nw_tmp, cb_emlrtBCI);
    }

    r.set_size(b_loop_ub_tmp);
    for (int i3{0}; i3 < b_loop_ub_tmp; i3++) {
      r[i3] = Xs[(i + i3) + Xs.size(0) * b_i];
    }

    coder::flipud(r);
    b_Xs.set_size(nw_tmp);
    for (int i3{0}; i3 < nw_tmp; i3++) {
      b_Xs[i3] = Xs[i3 + Xs.size(0) * b_i];
    }

    c_Xs.set_size(r.size(0) + 1);
    c_Xs[0] = Xs[Xs.size(0) * b_i];
    b_loop_ub = r.size(0);
    for (int i3{0}; i3 < b_loop_ub; i3++) {
      c_Xs[i3 + 1] = r[i3];
    }

    coder::toeplitz(b_Xs, c_Xs, _in);
    n = i2 - i1;
    b_w_time_domain[0] = n;
    b_w_time_domain[1] = loop_ub;
    rtSubAssignSizeCheck(&b_w_time_domain[0], 2, _in.size(), 2, k_emlrtECI);
    for (i2 = 0; i2 < loop_ub; i2++) {
      for (int i3{0}; i3 < n; i3++) {
        stackedToeplitzMatrices[(i1 + i3) + stackedToeplitzMatrices.size(0) * i2]
          = _in[i3 + n * i2];
      }
    }
  }

  // Reshape in this way will interweave rows of each sub matrix of the stack
  rowStart = static_cast<unsigned int>(x_of_n.size(0)) << 1;
  coder::internal::assertValidSizeArg(static_cast<double>(x_of_n.size(0)));
  coder::internal::assertValidSizeArg(static_cast<double>(rowStart));
  n = static_cast<int>(ai);
  if (stackedToeplitzMatrices.size(1) > stackedToeplitzMatrices.size(0)) {
    n = x_of_n.size(0);
  }

  if (loop_ub_tmp >= n) {
    n = loop_ub_tmp;
  }

  if (x_of_n.size(0) > n) {
    k_rtErrorWithMessageID(k_emlrtRTEI.fName, k_emlrtRTEI.lineNo);
  }

  if (static_cast<int>(rowStart) > n) {
    k_rtErrorWithMessageID(k_emlrtRTEI.fName, k_emlrtRTEI.lineNo);
  }

  if (static_cast<int>(rowStart) < 0) {
    ib_rtErrorWithMessageID(tb_emlrtRTEI.fName, tb_emlrtRTEI.lineNo);
  }

  if (x_of_n.size(0) * static_cast<int>(rowStart) != loop_ub_tmp) {
    l_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
  }

  // OLD W generation method. Easier to understand, but slower
  //  W     = 1i*zeros(nw,numZetas*nw);
  //  freqs = zeros(1,numZetas*nw);
  //  for i = 1:nw
  //      W(:,(i-1)*numZetas+(1:numZetas))=...
  //          circshift(Xs,i-1,1);
  //  end
  // Build a vector of the frequencies
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
  if (static_cast<double>(rowStart) - 1.0 < 0.0) {
    output_samps.set_size(output_samps.size(0), 0);
  } else {
    output_samps.set_size(1, static_cast<int>(static_cast<double>(rowStart) -
      1.0) + 1);
    b_loop_ub = static_cast<int>(static_cast<double>(rowStart) - 1.0);
    for (i = 0; i <= b_loop_ub; i++) {
      output_samps[i] = i;
    }
  }

  output_samps.set_size(1, output_samps.size(1));
  b_loop_ub = output_samps.size(1) - 1;
  for (i = 0; i <= b_loop_ub; i++) {
    output_samps[i] = output_samps[i] * b_Fs / static_cast<double>(rowStart);
  }

  // Shift everything so we use a negative frequencies
  // A little non-matlab notation to get this to run in simulink.
  y_im = b_Fs / 2.0;
  b_loop_ub = output_samps.size(1);
  b_output_samps.set_size(1, output_samps.size(1));
  for (i = 0; i < b_loop_ub; i++) {
    b_output_samps[i] = (output_samps[i] == y_im);
  }

  coder::eml_find(b_output_samps, (int *)&n, b_w_time_domain);
  if (b_w_time_domain[1] != 1) {
    rtSizeEq1DError(1, 0, g_emlrtECI);
  }

  b = (output_samps.size(1) < 1);
  if (b) {
    rtDynamicBoundsError(output_samps.size(1), 1, output_samps.size(1),
                         eb_emlrtBCI);
  }

  y_im = output_samps[output_samps.size(1) - 1];
  y_im = -y_im - (b_Fs - y_im);
  ai = static_cast<double>(output_samps.size(1)) - static_cast<double>(n);
  if (!(ai >= 0.0)) {
    rtNonNegativeError(ai, r_emlrtDCI);
  }

  loop_ub_tmp = static_cast<int>(ai);
  w_time_domain.set_size(1, loop_ub_tmp);
  for (i = 0; i < loop_ub_tmp; i++) {
    w_time_domain[i] = 1.0;
  }

  b_loop_ub = n + w_time_domain.size(1);
  wrapper.set_size(1, b_loop_ub);
  for (i = 0; i < n; i++) {
    wrapper[i] = 0.0;
  }

  for (i = 0; i < loop_ub_tmp; i++) {
    wrapper[i + n] = y_im;
  }

  if ((b_loop_ub != output_samps.size(1)) && ((b_loop_ub != 1) &&
       (output_samps.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(b_loop_ub, output_samps.size(1), l_emlrtECI);
  }

  // Here we sort the output to set up to have an ascending order of frequency
  // to be similar to the centered frequency list used elsewhere in the
  // codebase for the STFT output.
  if (wrapper.size(1) == output_samps.size(1)) {
    Wf.set_size(b_loop_ub);
    for (i = 0; i < b_loop_ub; i++) {
      Wf[i] = wrapper[i] + output_samps[i];
    }
  } else {
    binary_expand_op_1(this, wrapper, output_samps);
  }

  coder::internal::sort(Wf, iidx);
  b_w_time_domain[0] = x_of_n.size(0);
  W.set_size(x_of_n.size(0), W.size(1));
  b_loop_ub = iidx.size(0);
  W.set_size(W.size(0), iidx.size(0));
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      b = ((iidx[i] < 1) || (iidx[i] > static_cast<int>(rowStart)));
      if (b) {
        rtDynamicBoundsError(iidx[i], 1, static_cast<int>(rowStart), db_emlrtBCI);
      }

      W[i1 + W.size(0) * i].re = stackedToeplitzMatrices[i1 + b_w_time_domain[0]
        * (iidx[i] - 1)].re;
      W[i1 + W.size(0) * i].im = stackedToeplitzMatrices[i1 + b_w_time_domain[0]
        * (iidx[i] - 1)].im;
    }
  }
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
//
//
// Arguments    : wfmstft &iobj_0
// Return Type  : void
//
void b_waveform::spectro(wfmstft &iobj_0)
{
  coder::array<creal32_T, 2U> S;
  coder::array<creal32_T, 2U> obj;
  coder::array<double, 1U> _in;
  coder::array<float, 1U> local_time;
  coder::array<float, 1U> r;
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
  iobj_0.S.set_size(0, 0);
  iobj_0.t.set_size(0);
  iobj_0.f.set_size(0);
  iobj_0.psd.set_size(0);
  iobj_0.wind.set_size(0);
  iobj_0.dt = 0.0;
  iobj_0.T = 0.0;

  // wind = hann(waveform_obj.n_w,'periodic');
  // wind = tukeywin(waveform_obj.n_w,0.3);
  coder::rectwin(n_w, _in);
  loop_ub = _in.size(0);
  iobj_0.wind.set_size(_in.size(0));
  for (int i{0}; i < loop_ub; i++) {
    iobj_0.wind[i] = _in[i];
  }

  obj.set_size(1, x.size(1));
  loop_ub = x.size(0) * x.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    obj[i] = x[i];
  }

  _in.set_size(iobj_0.wind.size(0));
  loop_ub = iobj_0.wind.size(0) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    _in[i] = iobj_0.wind[i];
  }

  ::coder::stft(obj, Fs, _in, n_ol, n_w, S, r, local_time);
  loop_ub = r.size(0);
  iobj_0.f.set_size(r.size(0));
  for (int i{0}; i < loop_ub; i++) {
    iobj_0.f[i] = r[i];
  }

  iobj_0.S.set_size(S.size(0), S.size(1));
  loop_ub = S.size(0) * S.size(1);
  for (int i{0}; i < loop_ub; i++) {
    iobj_0.S[i].re = S[i].re;
    iobj_0.S[i].im = S[i].im;
  }

  //  Incoming x data in waveform is single precision, but sparse matrix multipliation later is only supported for double precision.
  loop_ub = local_time.size(0);
  _in.set_size(local_time.size(0));
  for (int i{0}; i < loop_ub; i++) {
    _in[i] = local_time[i] + t_0;
  }

  iobj_0.t.set_size(local_time.size(0));
  for (int i{0}; i < loop_ub; i++) {
    iobj_0.t[i] = _in[i];
  }

  double val;

  // Convert to global time of waveform. Double cast is needed because if x data in stft is single precision then the output t will be single as well.
  val = 1.0 / Fs;
  iobj_0.dt = val;
  val = n_w / Fs;
  iobj_0.T = val;
  iobj_0.updatepsd();

  // obj.psd = obj.dt^2/obj.T*mean(abs(obj.S).^2,2);% Sxx = dt^2/T*|xhat(f)|^2
  // Vestigial properties no longer used. Kept in case we want
  // to resurect them.
  // obj.wind_per_pulse = floor(waveform_obj.n_w/waveform_obj.n_p); %How many windows are needed to capture a pulse
  // obj.stft_steps_per_pulse = floor(waveform_obj.t_ws/waveform_obj.ps_pre.t_p);%How many stft steps are needed to capture a pulse
  stft = &iobj_0;
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
//
//
// Arguments    : wfmstft &iobj_0
// Return Type  : void
//
void waveform::spectro(wfmstft &iobj_0)
{
  coder::array<creal32_T, 2U> S;
  coder::array<creal32_T, 2U> obj;
  coder::array<double, 1U> _in;
  coder::array<float, 1U> local_time;
  coder::array<float, 1U> r;
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
  iobj_0.S.set_size(0, 0);
  iobj_0.t.set_size(0);
  iobj_0.f.set_size(0);
  iobj_0.psd.set_size(0);
  iobj_0.wind.set_size(0);
  iobj_0.dt = 0.0;
  iobj_0.T = 0.0;

  // wind = hann(waveform_obj.n_w,'periodic');
  // wind = tukeywin(waveform_obj.n_w,0.3);
  coder::rectwin(n_w, _in);
  loop_ub = _in.size(0);
  iobj_0.wind.set_size(_in.size(0));
  for (int i{0}; i < loop_ub; i++) {
    iobj_0.wind[i] = _in[i];
  }

  obj.set_size(1, x.size(1));
  loop_ub = x.size(0) * x.size(1) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    obj[i] = x[i];
  }

  _in.set_size(iobj_0.wind.size(0));
  loop_ub = iobj_0.wind.size(0) - 1;
  for (int i{0}; i <= loop_ub; i++) {
    _in[i] = iobj_0.wind[i];
  }

  ::coder::stft(obj, Fs, _in, n_ol, n_w, S, r, local_time);
  loop_ub = r.size(0);
  iobj_0.f.set_size(r.size(0));
  for (int i{0}; i < loop_ub; i++) {
    iobj_0.f[i] = r[i];
  }

  iobj_0.S.set_size(S.size(0), S.size(1));
  loop_ub = S.size(0) * S.size(1);
  for (int i{0}; i < loop_ub; i++) {
    iobj_0.S[i].re = S[i].re;
    iobj_0.S[i].im = S[i].im;
  }

  //  Incoming x data in waveform is single precision, but sparse matrix multipliation later is only supported for double precision.
  loop_ub = local_time.size(0);
  _in.set_size(local_time.size(0));
  for (int i{0}; i < loop_ub; i++) {
    _in[i] = local_time[i] + t_0;
  }

  iobj_0.t.set_size(local_time.size(0));
  for (int i{0}; i < loop_ub; i++) {
    iobj_0.t[i] = _in[i];
  }

  double val;

  // Convert to global time of waveform. Double cast is needed because if x data in stft is single precision then the output t will be single as well.
  val = 1.0 / Fs;
  iobj_0.dt = val;
  val = n_w / Fs;
  iobj_0.T = val;
  iobj_0.updatepsd();

  // obj.psd = obj.dt^2/obj.T*mean(abs(obj.S).^2,2);% Sxx = dt^2/T*|xhat(f)|^2
  // Vestigial properties no longer used. Kept in case we want
  // to resurect them.
  // obj.wind_per_pulse = floor(waveform_obj.n_w/waveform_obj.n_p); %How many windows are needed to capture a pulse
  // obj.stft_steps_per_pulse = floor(waveform_obj.t_ws/waveform_obj.ps_pre.t_p);%How many stft steps are needed to capture a pulse
  stft = &iobj_0;
}

//
// File trailer for waveform.cpp
//
// [EOF]
//
