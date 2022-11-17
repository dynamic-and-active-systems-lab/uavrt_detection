//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// waveform.cpp
//
// Code generation for function 'waveform'
//

// Include files
#include "waveform.h"
#include "FFTImplementationCallback.h"
#include "abs.h"
#include "all.h"
#include "buildtimecorrelatormatrix.h"
#include "circshift.h"
#include "div.h"
#include "fftshift.h"
#include "find.h"
#include "ifWhileCond.h"
#include "imresize.h"
#include "incohsumtoeplitz.h"
#include "interp1.h"
#include "linspace.h"
#include "makepulsestruc.h"
#include "mean.h"
#include "minOrMax.h"
#include "pulsestats.h"
#include "repmat.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include "sparse1.h"
#include "stft.h"
#include "strcmp.h"
#include "sum.h"
#include "threshold.h"
#include "uavrt_detection_internal_types.h"
#include "uavrt_detection_rtwutil.h"
#include "unaryMinOrMax.h"
#include "validator_check_size.h"
#include "weightingmatrix.h"
#include "wfmstft.h"
#include "coder_array.h"
#include <cmath>
#include <string.h>

// Function Declarations
static void b_and(coder::array<boolean_T, 1U> &in1, const coder::array<boolean_T,
                  1U> &in2, const coder::array<boolean_T, 1U> &in3);
static void b_binary_expand_op(coder::array<double, 2U> &in1, const waveform
  *in2, const coder::array<double, 2U> &in3);
static void b_binary_expand_op(coder::array<double, 1U> &in1, const waveform
  *in2);
static void b_binary_expand_op(coder::array<double, 2U> &in1, double in2, const
  coder::array<double, 2U> &in3);
static void b_binary_expand_op(coder::array<double, 1U> &in1, int in2, double
  in3, const coder::array<double, 2U> &in4, const coder::array<double, 2U> &in5);
static void b_binary_expand_op(coder::array<double, 2U> &in1, const coder::array<
  double, 2U> &in2, const coder::array<double, 2U> &in3, int in4, int in5);
static void b_binary_expand_op(coder::array<double, 2U> &in1, const coder::array<
  double, 2U> &in2, const coder::array<double, 2U> &in3, const coder::array<
  double, 2U> &in4, const coder::array<double, 2U> &in5);
static void b_binary_expand_op(coder::array<double, 2U> &in1, double in2, double
  in3, double in4, const coder::array<double, 2U> &in5);
static void b_binary_expand_op(coder::array<double, 2U> &in1, double in2, double
  in3, const coder::array<double, 2U> &in4, double in5);
static void c_and(coder::array<boolean_T, 1U> &in1, const coder::array<boolean_T,
                  1U> &in2);
static void c_binary_expand_op(coder::array<boolean_T, 2U> &in1, const coder::
  array<double, 2U> &in2, const int in3[2], const coder::array<double, 2U> &in4,
  const coder::array<double, 2U> &in5, const int in6[2], const coder::array<
  double, 2U> &in7, const coder::array<double, 2U> &in8, const int in9[2], const
  coder::array<double, 2U> &in10, const int in11[2], const coder::array<double,
  2U> &in12, const int in13[2], const coder::array<double, 2U> &in14, const int
  in15[2]);
static void d_binary_expand_op(coder::array<boolean_T, 2U> &in1, unsigned int
  in2, const coder::array<boolean_T, 1U> &in3, const coder::array<double, 1U>
  &in4, double in5, const coder::array<double, 1U> &in6, const coder::array<
  double, 1U> &in7, const coder::array<double, 2U> &in8, int in9, const coder::
  array<double, 1U> &in10, double in11, double in12);
static void e_binary_expand_op(coder::array<double, 1U> &in1, const coder::array<
  double, 1U> &in2, const coder::array<boolean_T, 2U> &in3, unsigned int in4,
  const coder::array<boolean_T, 1U> &in5);
static void f_binary_expand_op(coder::array<double, 1U> &in1, const coder::array<
  double, 1U> &in2, const coder::array<boolean_T, 1U> &in3);
static void g_binary_expand_op(coder::array<boolean_T, 1U> &in1, const coder::
  array<boolean_T, 1U> &in2, const coder::array<boolean_T, 1U> &in3, const coder::
  array<boolean_T, 1U> &in4, const coder::array<boolean_T, 1U> &in5, const coder::
  array<boolean_T, 1U> &in6, const coder::array<boolean_T, 1U> &in7, const coder::
  array<boolean_T, 1U> &in8, const coder::array<boolean_T, 1U> &in9);
static void h_binary_expand_op(coder::array<boolean_T, 1U> &in1, const coder::
  array<double, 1U> &in2, int in3, int in4);
static void i_binary_expand_op(coder::array<boolean_T, 1U> &in1, const coder::
  array<double, 1U> &in2, int in3, int in4, int in5);
static void j_binary_expand_op(coder::array<boolean_T, 1U> &in1, const coder::
  array<double, 2U> &in2, const coder::array<double, 2U> &in3, const coder::
  array<double, 2U> &in4, const coder::array<double, 2U> &in5);

// Function Definitions
void waveform::findpulse(const char time_searchtype_data[], const int
  time_searchtype_size[2], const char freq_searchtype_data[], const int
  freq_searchtype_size[2], const coder::array<double, 2U>
  &excluded_freq_bands_in, coder::array<c_struct_T, 2U> &pl_out, coder::array<
  boolean_T, 2U> &indiv_msk, coder::array<double, 1U> &peak_ind) const
{
  coder::sparse Wq;
  coder::array<creal_T, 2U> obj;
  coder::array<double, 2U> S_cols;
  coder::array<double, 2U> b_excluded_freq_bands;
  coder::array<double, 2U> b_refmat;
  coder::array<double, 2U> excluded_freq_bands;
  coder::array<double, 2U> r13;
  coder::array<double, 2U> r2;
  coder::array<double, 2U> r3;
  coder::array<double, 2U> refmat;
  coder::array<double, 2U> signalAmps;
  coder::array<double, 2U> timeSearchRange;
  coder::array<double, 2U> wind_start;
  coder::array<double, 2U> yw_max_all_freq;
  coder::array<double, 1U> b_freq_ind_rng_data;
  coder::array<double, 1U> b_x;
  coder::array<double, 1U> bandwidth_of_peak;
  coder::array<double, 1U> indsOfBinsValid;
  coder::array<double, 1U> peak;
  coder::array<double, 1U> scores;
  coder::array<double, 1U> timeBlinderVec;
  coder::array<int, 2U> r15;
  coder::array<int, 1U> r;
  coder::array<int, 1U> r1;
  coder::array<int, 1U> r12;
  coder::array<int, 1U> r14;
  coder::array<int, 1U> r4;
  coder::array<int, 1U> r5;
  coder::array<int, 1U> r6;
  coder::array<int, 1U> r7;
  coder::array<boolean_T, 2U> msk;
  coder::array<boolean_T, 1U> freq_mask;
  coder::array<boolean_T, 1U> greater_than_next;
  coder::array<boolean_T, 1U> greater_than_prev;
  coder::array<boolean_T, 1U> r10;
  coder::array<boolean_T, 1U> r11;
  coder::array<boolean_T, 1U> r8;
  coder::array<boolean_T, 1U> r9;
  coder::array<boolean_T, 1U> sideband_msk;
  coder::array<boolean_T, 1U> slope_peak;
  coder::array<boolean_T, 1U> slope_val;
  coder::array<boolean_T, 1U> y;
  c_struct_T expl_temp;
  double freq_ind_rng_data[2];
  double t_srch_rng[2];
  double a;
  double b_J;
  double b_M;
  double b_N;
  double d;
  double naive_wind_end;
  double naive_wind_end_tmp;
  double next_pulse_start;
  double stft_dt;
  double t_lastknown;
  double timetol;
  double tip_temp;
  double tp_temp;
  double wind_start_data;
  int S_cols_tmp;
  int b_loop_ub;
  int c_loop_ub;
  int d_loop_ub;
  int e_loop_ub;
  int f_loop_ub;
  int i;
  int i1;
  int i10;
  int i11;
  int i12;
  int i13;
  int i14;
  int i15;
  int i16;
  int i2;
  int i3;
  int i4;
  int i5;
  int i6;
  int i7;
  int i8;
  int i9;
  int inds_bkwd_2_next_valley_data;
  int inds_frwd_2_next_valley_data;
  int loop_ub;
  int maxStftTimeWind;
  int nRowsOfS;
  int n_freqs;
  int nx;
  unsigned int p;
  int wind_end_size;
  int wind_start_size;
  boolean_T exitg1;
  boolean_T t4_con_dec;
  boolean_T varargout_1;

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
  // 	pl_out      A matrix of all potential pulses. This will
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

    // INFORMED SEARCH BUT NOT PRIORI FOR START TIME
  } else {
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
    t_lastknown = ps_pre->pl[ps_pre->pl.size(1) - 1].t_0;
    tp_temp = ps_pre->t_p;

    // If the last pulse identified occured in this segement, use
    // it to downselect the first pulse search range.
    // Time steps in the STFT windows:
    stft_dt = stft->t[1] - stft->t[0];

    // IF LAST SEGMENT'S LAST PULSE ALSO LIVES IN THIS SEGMENT
    // BECAUSE OF OVERLAP:
    timetol = n_ws / Fs;
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
      b_x.set_size(stft->t.size(0));
      loop_ub = stft->t.size(0);
      for (i = 0; i < loop_ub; i++) {
        b_x[i] = (stft->t[i] - tip_temp) - t_lastknown;
      }

      nx = b_x.size(0);
      peak.set_size(b_x.size(0));
      for (int k{0}; k < nx; k++) {
        peak[k] = std::abs(b_x[k]);
      }

      y.set_size(peak.size(0));
      loop_ub = peak.size(0);
      for (i = 0; i < loop_ub; i++) {
        y[i] = (peak[i] <= timetol);
      }

      coder::c_eml_find(y, (int *)&inds_frwd_2_next_valley_data, &nx);
      wind_start_size = nx;
      for (i = 0; i < nx; i++) {
        wind_start_data = inds_frwd_2_next_valley_data;
      }

      stft_dt /= 2.0;
      t_lastknown += tp_temp;
      b_x.set_size(stft->t.size(0));
      loop_ub = stft->t.size(0);
      for (i = 0; i < loop_ub; i++) {
        b_x[i] = (stft->t[i] - stft_dt) - t_lastknown;
      }

      nx = b_x.size(0);
      peak.set_size(b_x.size(0));
      for (int k{0}; k < nx; k++) {
        peak[k] = std::abs(b_x[k]);
      }

      y.set_size(peak.size(0));
      loop_ub = peak.size(0);
      for (i = 0; i < loop_ub; i++) {
        y[i] = (peak[i] <= timetol);
      }

      coder::d_eml_find(y, (int *)&inds_frwd_2_next_valley_data, &nx);
      wind_end_size = nx;
      for (i = 0; i < nx; i++) {
        naive_wind_end = inds_frwd_2_next_valley_data;
      }

      // IF LAST SEGMENT'S LAST PULSE DOESN'T LIVE IN THIS SEGMENT:
    } else {
      // Project forward one pulse in time with
      // +/-2M uncertainty in search range.
      tip_temp = ps_pre->t_ip;
      a = ps_pre->t_ipu;
      next_pulse_start = t_lastknown + tip_temp;

      // +tp_temp/2;
      // These are the times of the START OF THE PULSE...not
      // the center. This is why we have stft_dt/2 terms in
      // subsequent equations.
      t_srch_rng[0] = -a + next_pulse_start;
      t_srch_rng[1] = a + next_pulse_start;
      if (t_srch_rng[0] < stft->t[0] - stft_dt / 2.0) {
        // If for some reason the last known pulse is more
        // that one pulse repetition interval away from the
        // current waveform start time, use the naive search
        // range.
        wind_start_size = 1;
        wind_start_data = 1.0;
        wind_end_size = 1;
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
        b_x.set_size(stft->t.size(0));
        loop_ub = stft->t.size(0);
        for (i = 0; i < loop_ub; i++) {
          b_x[i] = (stft->t[i] - tip_temp) - t_srch_rng[0];
        }

        nx = b_x.size(0);
        peak.set_size(b_x.size(0));
        for (int k{0}; k < nx; k++) {
          peak[k] = std::abs(b_x[k]);
        }

        y.set_size(peak.size(0));
        loop_ub = peak.size(0);
        for (i = 0; i < loop_ub; i++) {
          y[i] = (peak[i] <= timetol);
        }

        coder::c_eml_find(y, (int *)&inds_frwd_2_next_valley_data, &nx);
        wind_start_size = nx;
        for (i = 0; i < nx; i++) {
          wind_start_data = inds_frwd_2_next_valley_data;
        }

        stft_dt /= 2.0;
        b_x.set_size(stft->t.size(0));
        loop_ub = stft->t.size(0);
        for (i = 0; i < loop_ub; i++) {
          b_x[i] = (stft->t[i] - stft_dt) - t_srch_rng[1];
        }

        nx = b_x.size(0);
        peak.set_size(b_x.size(0));
        for (int k{0}; k < nx; k++) {
          peak[k] = std::abs(b_x[k]);
        }

        y.set_size(peak.size(0));
        loop_ub = peak.size(0);
        for (i = 0; i < loop_ub; i++) {
          y[i] = (peak[i] <= timetol);
        }

        coder::d_eml_find(y, (int *)&inds_frwd_2_next_valley_data, &nx);
        wind_end_size = nx;
        for (i = 0; i < nx; i++) {
          naive_wind_end = inds_frwd_2_next_valley_data;
        }
      }
    }
  }

  // time_search_range = [wind_start,wind_end];
  // Build a time search range matrix with one row for each pulse
  // The first column is the first window where that pulse might
  // live in the S matrix, and the second column is the last window
  // wher that pulse might live in the S matrix.
  i = static_cast<int>(K);
  timeSearchRange.set_size(i, 2);
  loop_ub = i << 1;
  for (i1 = 0; i1 < loop_ub; i1++) {
    timeSearchRange[i1] = 0.0;
  }

  wind_start.set_size(wind_start_size, 2);
  for (i1 = 0; i1 < wind_start_size; i1++) {
    wind_start[0] = wind_start_data;
  }

  for (i1 = 0; i1 < wind_end_size; i1++) {
    wind_start[wind_start.size(0)] = naive_wind_end;
  }

  timeSearchRange[0] = wind_start[0];
  timeSearchRange[timeSearchRange.size(0)] = wind_start[1];
  i1 = static_cast<int>(K + -1.0);
  for (int k{0}; k < i1; k++) {
    timeSearchRange[k + 1] = timeSearchRange[0] + (((static_cast<double>(k) +
      2.0) - 1.0) * (b_N - b_M) - b_J);
    timeSearchRange[(k + timeSearchRange.size(0)) + 1] =
      timeSearchRange[timeSearchRange.size(0)] + (((static_cast<double>(k) + 2.0)
      - 1.0) * naive_wind_end_tmp + b_J);
  }

  maxStftTimeWind = stft->S.size(1);

  // Limit the search to ranges of time that will be in the sftf
  // matrix
  inds_bkwd_2_next_valley_data = (timeSearchRange.size(0) << 1) - 1;
  wind_end_size = 0;
  for (int k{0}; k <= inds_bkwd_2_next_valley_data; k++) {
    if (timeSearchRange[k] > maxStftTimeWind) {
      wind_end_size++;
    }
  }

  r.set_size(wind_end_size);
  nx = 0;
  for (int k{0}; k <= inds_bkwd_2_next_valley_data; k++) {
    if (timeSearchRange[k] > maxStftTimeWind) {
      r[nx] = k + 1;
      nx++;
    }
  }

  loop_ub = r.size(0) - 1;
  for (i1 = 0; i1 <= loop_ub; i1++) {
    timeSearchRange[r[i1] - 1] = maxStftTimeWind;
  }

  inds_bkwd_2_next_valley_data = (timeSearchRange.size(0) << 1) - 1;
  wind_end_size = 0;
  for (int k{0}; k <= inds_bkwd_2_next_valley_data; k++) {
    if (timeSearchRange[k] < 1.0) {
      wind_end_size++;
    }
  }

  r1.set_size(wind_end_size);
  nx = 0;
  for (int k{0}; k <= inds_bkwd_2_next_valley_data; k++) {
    if (timeSearchRange[k] < 1.0) {
      r1[nx] = k + 1;
      nx++;
    }
  }

  loop_ub = r1.size(0) - 1;
  for (i1 = 0; i1 <= loop_ub; i1++) {
    timeSearchRange[r1[i1] - 1] = 1.0;
  }

  timeBlinderVec.set_size(maxStftTimeWind);
  for (i1 = 0; i1 < maxStftTimeWind; i1++) {
    timeBlinderVec[i1] = 0.0;
  }

  for (int k{0}; k < i; k++) {
    t_lastknown = timeSearchRange[k];
    next_pulse_start = timeSearchRange[k + timeSearchRange.size(0)];
    if (t_lastknown > next_pulse_start) {
      i1 = -1;
      wind_end_size = 0;
    } else {
      i1 = static_cast<int>(t_lastknown) - 2;
      wind_end_size = static_cast<int>(next_pulse_start);
    }

    loop_ub = (wind_end_size - i1) - 1;
    for (wind_end_size = 0; wind_end_size < loop_ub; wind_end_size++) {
      timeBlinderVec[(i1 + wind_end_size) + 1] = 1.0;
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
  wind_end_size = excluded_freq_bands.size(0);
  refmat.set_size(Wf.size(0), wind_end_size);
  nx = Wf.size(0);
  for (inds_bkwd_2_next_valley_data = 0; inds_bkwd_2_next_valley_data <
       wind_end_size; inds_bkwd_2_next_valley_data++) {
    maxStftTimeWind = inds_bkwd_2_next_valley_data * nx;
    for (int k{0}; k < nx; k++) {
      refmat[maxStftTimeWind + k] = Wf[k];
    }
  }

  // outmat = eval(['refmat',logical_op_string,'searchmat']);
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
  wind_end_size = excluded_freq_bands.size(0);
  b_refmat.set_size(Wf.size(0), wind_end_size);
  nx = Wf.size(0);
  for (inds_bkwd_2_next_valley_data = 0; inds_bkwd_2_next_valley_data <
       wind_end_size; inds_bkwd_2_next_valley_data++) {
    maxStftTimeWind = inds_bkwd_2_next_valley_data * nx;
    for (int k{0}; k < nx; k++) {
      b_refmat[maxStftTimeWind + k] = Wf[k];
    }
  }

  // outmat = eval(['refmat',logical_op_string,'searchmat']);
  // Build the priori frequency mask
  // Naive or informed frequency search
  if (coder::internal::f_strcmp(freq_searchtype_data, freq_searchtype_size)) {
    next_pulse_start = ps_pre->fstart;
    tip_temp = ps_pre->fend;

    // Check to makesure the informed search range is covered by
    // the frequencies available. If the prev bw is listed
    // as NaN, this will fail and will default to the naive
    // search. Freq_mask variable is a logicial vector of the
    // same size as Wf indicating which frequencies to look at.
    // IF FREQS ARE UNAVILABLE, USE NAIVE
    if ((next_pulse_start < coder::internal::unaryMinOrMax_anonFcn1(Wf)) ||
        (tip_temp > coder::internal::maximum(Wf))) {
      // isnan(obj.ps_pre.fc) %Naive
      wind_start_size = 1;
      wind_start_data = 1.0;
      wind_end_size = 1;
      naive_wind_end = Wf.size(0);

      // size(Sw,1);
      // IF FREQS ARE AVILABLE, USE INFORMED
    } else {
      sideband_msk.set_size(Wf.size(0));
      loop_ub = Wf.size(0);
      for (i = 0; i < loop_ub; i++) {
        sideband_msk[i] = (Wf[i] >= ps_pre->fstart);
      }

      coder::c_eml_find(sideband_msk, (int *)&inds_frwd_2_next_valley_data, &nx);
      wind_start_size = nx;
      for (i = 0; i < nx; i++) {
        wind_start_data = inds_frwd_2_next_valley_data;
      }

      sideband_msk.set_size(Wf.size(0));
      loop_ub = Wf.size(0);
      for (i = 0; i < loop_ub; i++) {
        sideband_msk[i] = (Wf[i] <= ps_pre->fend);
      }

      coder::d_eml_find(sideband_msk, (int *)&inds_frwd_2_next_valley_data, &nx);
      wind_end_size = nx;
      for (i = 0; i < nx; i++) {
        naive_wind_end = inds_frwd_2_next_valley_data;
      }
    }

    timeSearchRange.set_size(wind_start_size, 2);
    for (i = 0; i < wind_start_size; i++) {
      timeSearchRange[0] = wind_start_data;
    }

    for (i = 0; i < wind_end_size; i++) {
      timeSearchRange[timeSearchRange.size(0)] = naive_wind_end;
    }

    for (i = 0; i < wind_start_size; i++) {
      freq_ind_rng_data[0] = wind_start_data;
    }

    for (i = 0; i < wind_end_size; i++) {
      freq_ind_rng_data[wind_start_size] = naive_wind_end;
    }

    loop_ub = Wf.size(0);
    freq_mask.set_size(Wf.size(0));
    for (i = 0; i < loop_ub; i++) {
      freq_mask[i] = false;
    }

    if (static_cast<int>(timeSearchRange[0]) > static_cast<int>(timeSearchRange
         [1])) {
      i = -1;
      i1 = 0;
    } else {
      i = static_cast<int>(freq_ind_rng_data[0]) - 2;
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
  loop_ub = excluded_freq_bands.size(0);
  b_excluded_freq_bands.set_size(1, excluded_freq_bands.size(0));
  for (i = 0; i < loop_ub; i++) {
    b_excluded_freq_bands[i] = excluded_freq_bands[i];
  }

  wind_end_size = Wf.size(0);
  r2.set_size(wind_end_size, b_excluded_freq_bands.size(1));
  nx = b_excluded_freq_bands.size(1);
  for (inds_bkwd_2_next_valley_data = 0; inds_bkwd_2_next_valley_data < nx;
       inds_bkwd_2_next_valley_data++) {
    maxStftTimeWind = inds_bkwd_2_next_valley_data * wind_end_size;
    for (wind_start_size = 0; wind_start_size < wind_end_size; wind_start_size++)
    {
      r2[maxStftTimeWind + wind_start_size] =
        b_excluded_freq_bands[inds_bkwd_2_next_valley_data];
    }
  }

  loop_ub = excluded_freq_bands.size(0);
  b_excluded_freq_bands.set_size(1, excluded_freq_bands.size(0));
  for (i = 0; i < loop_ub; i++) {
    b_excluded_freq_bands[i] = excluded_freq_bands[i + excluded_freq_bands.size
      (0)];
  }

  wind_end_size = Wf.size(0);
  r3.set_size(wind_end_size, b_excluded_freq_bands.size(1));
  nx = b_excluded_freq_bands.size(1);
  for (inds_bkwd_2_next_valley_data = 0; inds_bkwd_2_next_valley_data < nx;
       inds_bkwd_2_next_valley_data++) {
    maxStftTimeWind = inds_bkwd_2_next_valley_data * wind_end_size;
    for (wind_start_size = 0; wind_start_size < wind_end_size; wind_start_size++)
    {
      r3[maxStftTimeWind + wind_start_size] =
        b_excluded_freq_bands[inds_bkwd_2_next_valley_data];
    }
  }

  if (refmat.size(0) == 1) {
    i = r2.size(0);
  } else {
    i = refmat.size(0);
  }

  if (b_refmat.size(0) == 1) {
    i1 = r3.size(0);
  } else {
    i1 = b_refmat.size(0);
  }

  if (refmat.size(1) == 1) {
    maxStftTimeWind = r2.size(1);
  } else {
    maxStftTimeWind = refmat.size(1);
  }

  if (b_refmat.size(1) == 1) {
    inds_bkwd_2_next_valley_data = r3.size(1);
  } else {
    inds_bkwd_2_next_valley_data = b_refmat.size(1);
  }

  if ((refmat.size(0) == r2.size(0)) && (refmat.size(1) == r2.size(1)) &&
      (b_refmat.size(0) == r3.size(0)) && (b_refmat.size(1) == r3.size(1)) && (i
       == i1) && (maxStftTimeWind == inds_bkwd_2_next_valley_data)) {
    msk.set_size(refmat.size(0), refmat.size(1));
    loop_ub = refmat.size(0) * refmat.size(1);
    for (i = 0; i < loop_ub; i++) {
      msk[i] = ((!(refmat[i] >= r2[i])) || (!(b_refmat[i] <= r3[i])));
    }

    coder::all(msk, sideband_msk);
  } else {
    j_binary_expand_op(sideband_msk, refmat, r2, b_refmat, r3);
  }

  if (freq_mask.size(0) == sideband_msk.size(0)) {
    loop_ub = freq_mask.size(0);
    for (i = 0; i < loop_ub; i++) {
      freq_mask[i] = (freq_mask[i] && sideband_msk[i]);
    }
  } else {
    c_and(freq_mask, sideband_msk);
  }

  // Check that we actually have something to search
  // Determine the number of blocks to cut the data into. Should
  // always be the number of pulses currently looking for.
  timetol = (static_cast<double>(stft->S.size(1)) - 1.0) / naive_wind_end_tmp;
  timetol = std::floor(timetol);
  buildtimecorrelatormatrix(b_N, b_M, b_J, K, &Wq);
  obj.set_size(W.size(1), W.size(0));
  loop_ub = W.size(0);
  for (i = 0; i < loop_ub; i++) {
    inds_bkwd_2_next_valley_data = W.size(1);
    for (i1 = 0; i1 < inds_bkwd_2_next_valley_data; i1++) {
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
  wind_start_size = stft->S.size(1);
  nRowsOfS = stft->S.size(0);

  // sIndsOfBins = sub2ind([nRowsOfS nColsOfS],repmat((1:nRowsOfS)',1,nColsOfS),S_cols);
  // sIndsOfBins = sub2ind([nZetas*nRowsOfS nColsOfS],transpose(1:numel(Wf)),S_cols);
  // The few lines below finds the noisePSD, but excludes regions
  // in time and frequency around possible detection. We do
  // detections as the zeta steps, but use the S matrix for PSD
  // estimates so there is a size mismatch that necessitates the
  // code below.
  wind_end_size = Wf.size(0);
  if (wind_end_size < 1) {
    b_excluded_freq_bands.set_size(1, 0);
  } else {
    b_excluded_freq_bands.set_size(1, wind_end_size);
    loop_ub = wind_end_size - 1;
    for (i = 0; i <= loop_ub; i++) {
      b_excluded_freq_bands[i] = static_cast<double>(i) + 1.0;
    }
  }

  peak.set_size(b_excluded_freq_bands.size(1));
  loop_ub = b_excluded_freq_bands.size(1);
  for (i = 0; i < loop_ub; i++) {
    peak[i] = b_excluded_freq_bands[i];
  }

  next_pulse_start = K;
  i = static_cast<int>(next_pulse_start);
  refmat.set_size(peak.size(0), static_cast<int>(next_pulse_start));
  nx = peak.size(0);
  for (inds_bkwd_2_next_valley_data = 0; inds_bkwd_2_next_valley_data < i;
       inds_bkwd_2_next_valley_data++) {
    maxStftTimeWind = inds_bkwd_2_next_valley_data * nx;
    for (int k{0}; k < nx; k++) {
      refmat[maxStftTimeWind + k] = peak[k];
    }
  }

  // sub2ind doesn't support NaN values, so we focus here on those
  // that don't have NaN
  msk.set_size(S_cols.size(0), S_cols.size(1));
  loop_ub = S_cols.size(0) * S_cols.size(1);
  for (i = 0; i < loop_ub; i++) {
    msk[i] = std::isnan(S_cols[i]);
  }

  loop_ub = msk.size(0) * msk.size(1);
  for (i = 0; i < loop_ub; i++) {
    msk[i] = !msk[i];
  }

  inds_bkwd_2_next_valley_data = msk.size(0) * msk.size(1) - 1;
  wind_end_size = 0;
  for (int k{0}; k <= inds_bkwd_2_next_valley_data; k++) {
    if (msk[k]) {
      wind_end_size++;
    }
  }

  r4.set_size(wind_end_size);
  nx = 0;
  for (int k{0}; k <= inds_bkwd_2_next_valley_data; k++) {
    if (msk[k]) {
      r4[nx] = k + 1;
      nx++;
    }
  }

  inds_bkwd_2_next_valley_data = msk.size(0) * msk.size(1) - 1;
  wind_end_size = 0;
  for (int k{0}; k <= inds_bkwd_2_next_valley_data; k++) {
    if (msk[k]) {
      wind_end_size++;
    }
  }

  r5.set_size(wind_end_size);
  nx = 0;
  for (int k{0}; k <= inds_bkwd_2_next_valley_data; k++) {
    if (msk[k]) {
      r5[nx] = k + 1;
      nx++;
    }
  }

  next_pulse_start = static_cast<double>(Wf.size(0)) / static_cast<double>
    (nRowsOfS) * static_cast<double>(nRowsOfS);
  timeBlinderVec.set_size(r4.size(0));
  loop_ub = r4.size(0);
  for (i = 0; i < loop_ub; i++) {
    timeBlinderVec[i] = static_cast<int>(refmat[r4[i] - 1]) + static_cast<int>
      (next_pulse_start) * (static_cast<int>(S_cols[r5[i] - 1]) - 1);
  }

  sideband_msk.set_size(timeBlinderVec.size(0));
  loop_ub = timeBlinderVec.size(0);
  for (i = 0; i < loop_ub; i++) {
    sideband_msk[i] = false;
  }

  inds_bkwd_2_next_valley_data = sideband_msk.size(0) - 1;
  wind_end_size = 0;
  for (int k{0}; k <= inds_bkwd_2_next_valley_data; k++) {
    wind_end_size++;
  }

  indsOfBinsValid.set_size(wind_end_size);
  for (int k{0}; k <= inds_bkwd_2_next_valley_data; k++) {
    indsOfBinsValid[k] = timeBlinderVec[k];
  }

  // binMaskMatrix will be a matrix of NaN at potential pulse
  // locations
  refmat.set_size(static_cast<int>(next_pulse_start), wind_start_size);
  loop_ub = static_cast<int>(next_pulse_start) * wind_start_size;
  for (i = 0; i < loop_ub; i++) {
    refmat[i] = 0.0;
  }

  r.set_size(indsOfBinsValid.size(0));
  loop_ub = indsOfBinsValid.size(0);
  for (i = 0; i < loop_ub; i++) {
    r[i] = static_cast<int>(indsOfBinsValid[i]);
  }

  loop_ub = r.size(0);
  for (i = 0; i < loop_ub; i++) {
    refmat[r[i] - 1] = rtNaN;
  }

  // 0;
  // Now add some buffer around the potential pulse locations
  r2.set_size(refmat.size(0), refmat.size(1));
  loop_ub = refmat.size(0) * refmat.size(1);
  for (i = 0; i < loop_ub; i++) {
    r2[i] = refmat[i];
  }

  coder::circshift(r2);
  r3.set_size(refmat.size(0), refmat.size(1));
  loop_ub = refmat.size(0) * refmat.size(1);
  for (i = 0; i < loop_ub; i++) {
    r3[i] = refmat[i];
  }

  coder::b_circshift(r3);
  b_refmat.set_size(refmat.size(0), refmat.size(1));
  loop_ub = refmat.size(0) * refmat.size(1);
  for (i = 0; i < loop_ub; i++) {
    b_refmat[i] = refmat[i];
  }

  coder::c_circshift(b_refmat);
  signalAmps.set_size(refmat.size(0), refmat.size(1));
  loop_ub = refmat.size(0) * refmat.size(1);
  for (i = 0; i < loop_ub; i++) {
    signalAmps[i] = refmat[i];
  }

  coder::d_circshift(signalAmps);
  if (refmat.size(0) == 1) {
    i = r2.size(0);
  } else {
    i = refmat.size(0);
  }

  if (refmat.size(1) == 1) {
    i1 = r2.size(1);
  } else {
    i1 = refmat.size(1);
  }

  if (refmat.size(0) == 1) {
    maxStftTimeWind = r2.size(0);
  } else {
    maxStftTimeWind = refmat.size(0);
  }

  if (maxStftTimeWind == 1) {
    maxStftTimeWind = r3.size(0);
  } else if (refmat.size(0) == 1) {
    maxStftTimeWind = r2.size(0);
  } else {
    maxStftTimeWind = refmat.size(0);
  }

  if (refmat.size(1) == 1) {
    inds_bkwd_2_next_valley_data = r2.size(1);
  } else {
    inds_bkwd_2_next_valley_data = refmat.size(1);
  }

  if (inds_bkwd_2_next_valley_data == 1) {
    inds_bkwd_2_next_valley_data = r3.size(1);
  } else if (refmat.size(1) == 1) {
    inds_bkwd_2_next_valley_data = r2.size(1);
  } else {
    inds_bkwd_2_next_valley_data = refmat.size(1);
  }

  if (refmat.size(0) == 1) {
    i2 = r2.size(0);
  } else {
    i2 = refmat.size(0);
  }

  if (i2 == 1) {
    i2 = r3.size(0);
  } else if (refmat.size(0) == 1) {
    i2 = r2.size(0);
  } else {
    i2 = refmat.size(0);
  }

  if (refmat.size(0) == 1) {
    i3 = r2.size(0);
  } else {
    i3 = refmat.size(0);
  }

  if (i2 == 1) {
    i2 = b_refmat.size(0);
  } else if (i3 == 1) {
    i2 = r3.size(0);
  } else if (refmat.size(0) == 1) {
    i2 = r2.size(0);
  } else {
    i2 = refmat.size(0);
  }

  if (refmat.size(1) == 1) {
    i3 = r2.size(1);
  } else {
    i3 = refmat.size(1);
  }

  if (i3 == 1) {
    i3 = r3.size(1);
  } else if (refmat.size(1) == 1) {
    i3 = r2.size(1);
  } else {
    i3 = refmat.size(1);
  }

  if (refmat.size(1) == 1) {
    wind_end_size = r2.size(1);
  } else {
    wind_end_size = refmat.size(1);
  }

  if (i3 == 1) {
    i3 = b_refmat.size(1);
  } else if (wind_end_size == 1) {
    i3 = r3.size(1);
  } else if (refmat.size(1) == 1) {
    i3 = r2.size(1);
  } else {
    i3 = refmat.size(1);
  }

  if ((refmat.size(0) == r2.size(0)) && (refmat.size(1) == r2.size(1)) && (i ==
       r3.size(0)) && (i1 == r3.size(1)) && (maxStftTimeWind == b_refmat.size(0))
      && (inds_bkwd_2_next_valley_data == b_refmat.size(1)) && (i2 ==
       signalAmps.size(0)) && (i3 == signalAmps.size(1))) {
    loop_ub = refmat.size(0) * refmat.size(1);
    for (i = 0; i < loop_ub; i++) {
      refmat[i] = (((refmat[i] + r2[i]) + r3[i]) + b_refmat[i]) + signalAmps[i];
    }
  } else {
    b_binary_expand_op(refmat, r2, r3, b_refmat, signalAmps);
  }

  // figure;spy(freqtimeShiftedBinMaskMatrix_scaled)
  next_pulse_start = 1.0 / Fs;

  // noisePSD = dt^2/T*abs(mean(obj.stft.S+freqtimeShiftedBinMaskMatrixScaled,2,'omitnan')).^2;%Add since it is 0 where we expect noise and NaN where there might be a pulse
  tip_temp = next_pulse_start * next_pulse_start / (n_w / Fs);
  r2.set_size(refmat.size(0), refmat.size(1));
  loop_ub = refmat.size(0) * refmat.size(1);
  for (i = 0; i < loop_ub; i++) {
    r2[i] = refmat[i];
  }

  coder::e_circshift(r2);
  r3.set_size(refmat.size(0), refmat.size(1));
  loop_ub = refmat.size(0) * refmat.size(1);
  for (i = 0; i < loop_ub; i++) {
    r3[i] = refmat[i];
  }

  coder::f_circshift(r3);
  if (refmat.size(0) == 1) {
    i = r2.size(0);
  } else {
    i = refmat.size(0);
  }

  if (refmat.size(1) == 1) {
    i1 = r2.size(1);
  } else {
    i1 = refmat.size(1);
  }

  if ((refmat.size(0) == r2.size(0)) && (refmat.size(1) == r2.size(1)) && (i ==
       r3.size(0)) && (i1 == r3.size(1))) {
    b_refmat.set_size(refmat.size(0), refmat.size(1));
    loop_ub = refmat.size(0) * refmat.size(1);
    for (i = 0; i < loop_ub; i++) {
      b_refmat[i] = (refmat[i] + r2[i]) + r3[i];
    }

    t_srch_rng[0] = nRowsOfS;
    t_srch_rng[1] = wind_start_size;
    coder::imresize(b_refmat, t_srch_rng, r2);
  } else {
    b_binary_expand_op(r2, refmat, r3, nRowsOfS, wind_start_size);
  }

  if ((stft->S.size(0) == r2.size(0)) && (stft->S.size(1) == r2.size(1))) {
    obj.set_size(stft->S.size(0), stft->S.size(1));
    loop_ub = stft->S.size(0) * stft->S.size(1);
    for (i = 0; i < loop_ub; i++) {
      obj[i].re = stft->S[i].re + r2[i];
      obj[i].im = stft->S[i].im;
    }

    nx = obj.size(0) * obj.size(1);
    refmat.set_size(obj.size(0), obj.size(1));
    for (int k{0}; k < nx; k++) {
      refmat[k] = rt_hypotd_snf(obj[k].re, obj[k].im);
    }
  } else {
    b_binary_expand_op(refmat, this, r2);
  }

  // Add since it is 0 where we expect noise and NaN where there might be a pulse
  r2.set_size(refmat.size(0), refmat.size(1));
  loop_ub = refmat.size(0) * refmat.size(1);
  for (i = 0; i < loop_ub; i++) {
    next_pulse_start = refmat[i];
    r2[i] = next_pulse_start * next_pulse_start;
  }

  coder::mean(r2, timeBlinderVec);
  peak.set_size(timeBlinderVec.size(0));
  loop_ub = timeBlinderVec.size(0);
  for (i = 0; i < loop_ub; i++) {
    peak[i] = tip_temp * timeBlinderVec[i];
  }

  coder::interp1(stft->f, peak, Wf, timeBlinderVec);
  inds_bkwd_2_next_valley_data = timeBlinderVec.size(0);
  for (int k{0}; k < inds_bkwd_2_next_valley_data; k++) {
    if (timeBlinderVec[k] < 0.0) {
      timeBlinderVec[k] = 0.0;
    }
  }

  next_pulse_start = stft->f[1] - stft->f[0];

  // Not the delta f of the Wf vector, because the frequency bins are the same width, just with half bin steps %
  // noisePowers = noisePSDAtZetas*fBinWidthZetas;
  // Calculate the power at each of the S locations that were
  // selected by the incohsum function. Scores are the mag squared
  // S values. Mult by dt^2/T to get psd, then mult by the width of
  // the frequency bin to get power. We have to do this because the
  // psd in the stft object uses dt^2/T factor for the psd calc.
  // scores;
  // signalPlusNoisePSDPulseGroup   = dt^2/T*scores;%scores;
  wind_end_size = yw_max_all_freq.size(1);
  b_refmat.set_size(timeBlinderVec.size(0), wind_end_size);
  nx = timeBlinderVec.size(0);
  for (inds_bkwd_2_next_valley_data = 0; inds_bkwd_2_next_valley_data <
       wind_end_size; inds_bkwd_2_next_valley_data++) {
    maxStftTimeWind = inds_bkwd_2_next_valley_data * nx;
    for (int k{0}; k < nx; k++) {
      b_refmat[maxStftTimeWind + k] = timeBlinderVec[k];
    }
  }

  if ((yw_max_all_freq.size(0) == b_refmat.size(0)) && (yw_max_all_freq.size(1) ==
       b_refmat.size(1))) {
    loop_ub = yw_max_all_freq.size(0) * yw_max_all_freq.size(1);
    b_refmat.set_size(yw_max_all_freq.size(0), yw_max_all_freq.size(1));
    for (i = 0; i < loop_ub; i++) {
      b_refmat[i] = tip_temp * yw_max_all_freq[i] - b_refmat[i];
    }
  } else {
    b_binary_expand_op(b_refmat, tip_temp, yw_max_all_freq);
  }

  // signalPSDPulseGroup   = signalPlusNoisePSDPulseGroup-noisePSDAtZetas;
  inds_bkwd_2_next_valley_data = b_refmat.size(0) * b_refmat.size(1) - 1;
  wind_end_size = 0;
  for (int k{0}; k <= inds_bkwd_2_next_valley_data; k++) {
    if (b_refmat[k] < 0.0) {
      wind_end_size++;
    }
  }

  r6.set_size(wind_end_size);
  nx = 0;
  for (int k{0}; k <= inds_bkwd_2_next_valley_data; k++) {
    if (b_refmat[k] < 0.0) {
      r6[nx] = k + 1;
      nx++;
    }
  }

  loop_ub = r6.size(0) - 1;
  for (i = 0; i <= loop_ub; i++) {
    b_refmat[r6[i] - 1] = 0.0;
  }

  // Can't have negative values
  // signalPSDPulseGroup(signalPSD<0)   = 0; %Can't have negative values
  signalAmps.set_size(b_refmat.size(0), b_refmat.size(1));
  loop_ub = b_refmat.size(0) * b_refmat.size(1);
  for (i = 0; i < loop_ub; i++) {
    signalAmps[i] = b_refmat[i] * next_pulse_start;
  }

  nx = signalAmps.size(0) * signalAmps.size(1);
  for (int k{0}; k < nx; k++) {
    signalAmps[k] = std::sqrt(signalAmps[k]);
  }

  // signalPlusNoisePowers = signalPlusNoisePSD*fBinWidthZetas;
  // signalPowers          = signalPlusNoisePowers-noisePowers;
  // SNRdB = 10*log10(powers./freqBinPowAtZetas);
  // Signal power ratio to  noise power in its frequency bin for all pulses in group
  // SNRdB = 10*log10(powers./sum(freqBinPowAtZetas));          %Signal power ratio to all noise power in bandwidth
  // SNRdB = 10*log10(powers./obj.K*1./sum(freqBinPowAtZetas)); %Average the power across all pulses
  // SNRdB = 10*log10(signalPowers./obj.K*1./noisePowers); %Average the power across all pulses
  wind_end_size = yw_max_all_freq.size(1);
  refmat.set_size(timeBlinderVec.size(0), wind_end_size);
  nx = timeBlinderVec.size(0);
  for (inds_bkwd_2_next_valley_data = 0; inds_bkwd_2_next_valley_data <
       wind_end_size; inds_bkwd_2_next_valley_data++) {
    maxStftTimeWind = inds_bkwd_2_next_valley_data * nx;
    for (int k{0}; k < nx; k++) {
      refmat[maxStftTimeWind + k] = timeBlinderVec[k];
    }
  }

  if ((b_refmat.size(0) == refmat.size(0)) && (b_refmat.size(1) == refmat.size(1)))
  {
    loop_ub = b_refmat.size(0) * b_refmat.size(1);
    for (i = 0; i < loop_ub; i++) {
      b_refmat[i] = b_refmat[i] / refmat[i];
    }
  } else {
    rdivide(b_refmat, refmat);
  }

  nx = b_refmat.size(0) * b_refmat.size(1);
  for (int k{0}; k < nx; k++) {
    b_refmat[k] = std::log10(b_refmat[k]);
  }

  loop_ub = b_refmat.size(0) * b_refmat.size(1);
  for (i = 0; i < loop_ub; i++) {
    b_refmat[i] = 10.0 * b_refmat[i];
  }

  // SNRdBPulseGroup = 10*log10(signalPSDPulseGroup./noisePSDAtZetas);
  inds_bkwd_2_next_valley_data = b_refmat.size(0) * b_refmat.size(1) - 1;
  wind_end_size = 0;
  for (int k{0}; k <= inds_bkwd_2_next_valley_data; k++) {
    if (b_refmat[k] == rtInf) {
      wind_end_size++;
    }
  }

  r7.set_size(wind_end_size);
  nx = 0;
  for (int k{0}; k <= inds_bkwd_2_next_valley_data; k++) {
    if (b_refmat[k] == rtInf) {
      r7[nx] = k + 1;
      nx++;
    }
  }

  loop_ub = r7.size(0) - 1;
  for (i = 0; i <= loop_ub; i++) {
    b_refmat[r7[i] - 1] = rtNaN;
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

  if (scores.size(0) < 2) {
    i = 0;
    i1 = 0;
  } else {
    i = 1;
    i1 = scores.size(0);
  }

  inds_bkwd_2_next_valley_data = i1 - i;
  if (loop_ub == inds_bkwd_2_next_valley_data + 1) {
    peak.set_size(inds_bkwd_2_next_valley_data + 1);
    for (i1 = 0; i1 < inds_bkwd_2_next_valley_data; i1++) {
      peak[i1] = scores[i + i1];
    }

    peak[inds_bkwd_2_next_valley_data] = 0.0;
    greater_than_next.set_size(loop_ub);
    for (i = 0; i < loop_ub; i++) {
      greater_than_next[i] = (scores[i] > peak[i]);
    }
  } else {
    i_binary_expand_op(greater_than_next, scores, loop_ub - 1, i, i1 - 1);
  }

  if (scores.size(0) < 1) {
    loop_ub = 0;
  } else {
    loop_ub = scores.size(0);
  }

  if (scores.size(0) - 1 < 1) {
    inds_bkwd_2_next_valley_data = 1;
  } else {
    inds_bkwd_2_next_valley_data = scores.size(0);
  }

  if (loop_ub == inds_bkwd_2_next_valley_data) {
    peak.set_size(inds_bkwd_2_next_valley_data);
    peak[0] = 0.0;
    for (i = 0; i <= inds_bkwd_2_next_valley_data - 2; i++) {
      peak[i + 1] = scores[i];
    }

    greater_than_prev.set_size(loop_ub);
    for (i = 0; i < loop_ub; i++) {
      greater_than_prev[i] = (scores[i] > peak[i]);
    }
  } else {
    h_binary_expand_op(greater_than_prev, scores, loop_ub - 1,
                       inds_bkwd_2_next_valley_data - 2);
  }

  // slope_pos = [false;~greater_than_next&greater_than_prev;false];
  // slope_neg = [false; greater_than_next&~greater_than_prev;false];
  // slope_val = [false;~greater_than_next&~greater_than_prev;false];
  // slope_peak = [false;greater_than_next&greater_than_prev;false];
  sideband_msk.set_size(greater_than_next.size(0));
  loop_ub = greater_than_next.size(0);
  for (i = 0; i < loop_ub; i++) {
    sideband_msk[i] = !greater_than_next[i];
  }

  y.set_size(greater_than_prev.size(0));
  loop_ub = greater_than_prev.size(0);
  for (i = 0; i < loop_ub; i++) {
    y[i] = !greater_than_prev[i];
  }

  if (sideband_msk.size(0) == y.size(0)) {
    slope_val.set_size(sideband_msk.size(0));
    loop_ub = sideband_msk.size(0);
    for (i = 0; i < loop_ub; i++) {
      slope_val[i] = (sideband_msk[i] && y[i]);
    }
  } else {
    b_and(slope_val, sideband_msk, y);
  }

  if (scores.size(0) < 2) {
    i = 0;
    i1 = 0;
  } else {
    i = 1;
    i1 = scores.size(0);
  }

  if (scores.size(0) - 1 < 1) {
    loop_ub = 0;
  } else {
    loop_ub = scores.size(0) - 1;
  }

  if (scores.size(0) - 1 < 1) {
    inds_bkwd_2_next_valley_data = 0;
  } else {
    inds_bkwd_2_next_valley_data = scores.size(0) - 1;
  }

  if (scores.size(0) < 2) {
    wind_end_size = 0;
    nx = 0;
  } else {
    wind_end_size = 1;
    nx = scores.size(0);
  }

  // [score_left_bndry&slope_neg,score_right_bndry&slope_pos,scores]
  // This deals with the frequency masking and some scores will be
  // NaN because they were excluded from consideration in the
  // incohsum processing. If the score is a left boundary
  // (frequencies lower were excluded) and the slope is negative,
  // this would be considered a peak. Visa-versa for right
  // boundaries.
  maxStftTimeWind = i1 - i;
  r8.set_size(maxStftTimeWind);
  for (i1 = 0; i1 < maxStftTimeWind; i1++) {
    r8[i1] = std::isnan(scores[i + i1]);
  }

  r9.set_size(loop_ub);
  for (i = 0; i < loop_ub; i++) {
    r9[i] = std::isnan(scores[i]);
  }

  r10.set_size(inds_bkwd_2_next_valley_data);
  for (i = 0; i < inds_bkwd_2_next_valley_data; i++) {
    r10[i] = std::isnan(scores[i]);
  }

  loop_ub = nx - wind_end_size;
  r11.set_size(loop_ub);
  for (i = 0; i < loop_ub; i++) {
    r11[i] = std::isnan(scores[wind_end_size + i]);
  }

  if (r8.size(0) == 1) {
    i = r9.size(0);
  } else {
    i = r8.size(0);
  }

  if (greater_than_next.size(0) == 1) {
    i1 = y.size(0);
  } else {
    i1 = greater_than_next.size(0);
  }

  if (greater_than_next.size(0) == 1) {
    maxStftTimeWind = greater_than_prev.size(0);
  } else {
    maxStftTimeWind = greater_than_next.size(0);
  }

  if (r8.size(0) == 1) {
    inds_bkwd_2_next_valley_data = r9.size(0);
  } else {
    inds_bkwd_2_next_valley_data = r8.size(0);
  }

  if (r8.size(0) == 1) {
    i2 = r9.size(0);
  } else {
    i2 = r8.size(0);
  }

  if (inds_bkwd_2_next_valley_data + 1 == 1) {
    if (greater_than_next.size(0) == 1) {
      inds_bkwd_2_next_valley_data = y.size(0);
    } else {
      inds_bkwd_2_next_valley_data = greater_than_next.size(0);
    }
  } else {
    inds_bkwd_2_next_valley_data = i2 + 1;
  }

  if (r10.size(0) == 1) {
    i2 = r11.size(0);
  } else {
    i2 = r10.size(0);
  }

  if (sideband_msk.size(0) == 1) {
    i3 = greater_than_prev.size(0);
  } else {
    i3 = sideband_msk.size(0);
  }

  if (greater_than_next.size(0) == 1) {
    wind_end_size = greater_than_prev.size(0);
  } else {
    wind_end_size = greater_than_next.size(0);
  }

  if (r8.size(0) == 1) {
    loop_ub = r9.size(0);
  } else {
    loop_ub = r8.size(0);
  }

  if (r8.size(0) == 1) {
    nx = r9.size(0);
  } else {
    nx = r8.size(0);
  }

  if (wind_end_size == 1) {
    if (loop_ub + 1 == 1) {
      if (greater_than_next.size(0) == 1) {
        wind_end_size = y.size(0);
      } else {
        wind_end_size = greater_than_next.size(0);
      }
    } else {
      wind_end_size = nx + 1;
    }
  } else if (greater_than_next.size(0) == 1) {
    wind_end_size = greater_than_prev.size(0);
  } else {
    wind_end_size = greater_than_next.size(0);
  }

  if (r10.size(0) == 1) {
    loop_ub = r11.size(0);
  } else {
    loop_ub = r10.size(0);
  }

  if (r10.size(0) == 1) {
    nx = r11.size(0);
  } else {
    nx = r10.size(0);
  }

  if (loop_ub + 1 == 1) {
    if (sideband_msk.size(0) == 1) {
      loop_ub = greater_than_prev.size(0);
    } else {
      loop_ub = sideband_msk.size(0);
    }
  } else {
    loop_ub = nx + 1;
  }

  if ((greater_than_next.size(0) == greater_than_prev.size(0)) && (r8.size(0) ==
       r9.size(0)) && (greater_than_next.size(0) == y.size(0)) && (i + 1 == i1) &&
      (maxStftTimeWind == inds_bkwd_2_next_valley_data) && (r10.size(0) ==
       r11.size(0)) && (sideband_msk.size(0) == greater_than_prev.size(0)) &&
      (i2 + 1 == i3) && (wind_end_size == loop_ub)) {
    slope_peak.set_size(r8.size(0) + 1);
    slope_peak[0] = true;
    loop_ub = r8.size(0);
    for (i = 0; i < loop_ub; i++) {
      slope_peak[i + 1] = ((!r8[i]) && r9[i]);
    }

    r8.set_size(r10.size(0) + 1);
    loop_ub = r10.size(0);
    for (i = 0; i < loop_ub; i++) {
      r8[i] = ((!r10[i]) && r11[i]);
    }

    r8[r10.size(0)] = true;
    slope_peak.set_size(greater_than_next.size(0));
    loop_ub = greater_than_next.size(0);
    for (i = 0; i < loop_ub; i++) {
      slope_peak[i] = ((greater_than_next[i] && greater_than_prev[i]) ||
                       (slope_peak[i] && (greater_than_next[i] && y[i])) ||
                       (r8[i] && (sideband_msk[i] && greater_than_prev[i])));
    }
  } else {
    g_binary_expand_op(slope_peak, greater_than_next, greater_than_prev, r8, r9,
                       y, r10, r11, sideband_msk);
  }

  // How many time windows difference do we considered the found
  // pulse to be the same as one found at a different frequency?
  // We'll say that if they are within two pulse time width of
  // each other they are the same pulse.
  stft_dt = 2.0 * n_p / n_ws;
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
  if (scores.size(0) == slope_peak.size(0)) {
    timeBlinderVec.set_size(scores.size(0));
    loop_ub = scores.size(0);
    for (i = 0; i < loop_ub; i++) {
      timeBlinderVec[i] = scores[i] * static_cast<double>(slope_peak[i]);
    }
  } else {
    f_binary_expand_op(timeBlinderVec, scores, slope_peak);
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
  if (timeBlinderVec.size(0) == 1) {
    i = thresh.threshVecFine.size(0);
  } else {
    i = timeBlinderVec.size(0);
  }

  if ((timeBlinderVec.size(0) == thresh.threshVecFine.size(0)) &&
      (timeBlinderVec.size(0) == i)) {
    loop_ub = timeBlinderVec.size(0);
    for (i = 0; i < loop_ub; i++) {
      timeBlinderVec[i] = timeBlinderVec[i] * static_cast<double>
        (timeBlinderVec[i] >= thresh.threshVecFine[i]);
    }
  } else {
    b_binary_expand_op(timeBlinderVec, this);
  }

  // ------------------------------------------------
  // thresh_hold = thresh;thresh = interp1(obj.stft.f,thresh,Wf);
  if (thresh.threshVecFine.size(0) == 1) {
    i = timeBlinderVec.size(0);
  } else {
    i = thresh.threshVecFine.size(0);
  }

  y.set_size(i);
  wind_end_size = (timeBlinderVec.size(0) != 1);
  nRowsOfS = (thresh.threshVecFine.size(0) != 1);
  if (thresh.threshVecFine.size(0) == 1) {
    loop_ub = timeBlinderVec.size(0);
  } else {
    loop_ub = thresh.threshVecFine.size(0);
  }

  for (i = 0; i < loop_ub; i++) {
    y[i] = (timeBlinderVec[i * wind_end_size] > thresh.threshVecFine[i *
            nRowsOfS]);
  }

  varargout_1 = false;
  wind_end_size = 1;
  exitg1 = false;
  while ((!exitg1) && (wind_end_size <= y.size(0))) {
    if (y[wind_end_size - 1]) {
      varargout_1 = true;
      exitg1 = true;
    } else {
      wind_end_size++;
    }
  }

  if (!varargout_1) {
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
  nRowsOfS = (thresh.threshVecFine.size(0) != 1);
  int exitg2;
  do {
    exitg2 = 0;
    if (thresh.threshVecFine.size(0) == 1) {
      i = timeBlinderVec.size(0);
    } else {
      i = thresh.threshVecFine.size(0);
    }

    y.set_size(i);
    wind_end_size = (timeBlinderVec.size(0) != 1);
    if (thresh.threshVecFine.size(0) == 1) {
      loop_ub = timeBlinderVec.size(0);
    } else {
      loop_ub = thresh.threshVecFine.size(0);
    }

    for (i = 0; i < loop_ub; i++) {
      y[i] = (timeBlinderVec[i * wind_end_size] > thresh.threshVecFine[i *
              nRowsOfS]);
    }

    varargout_1 = false;
    wind_end_size = 1;
    exitg1 = false;
    while ((!exitg1) && (wind_end_size <= y.size(0))) {
      if (y[wind_end_size - 1]) {
        varargout_1 = true;
        exitg1 = true;
      } else {
        wind_end_size++;
      }
    }

    if (varargout_1) {
      //    hold on; plot3([1:160],ones(160,1)*p,curr_scores)
      // Identify the highest scoring peak of the currently
      // identifed scores.
      coder::internal::maximum(timeBlinderVec, &peak[static_cast<int>(p) - 1],
        &wind_end_size);
      peak_ind[static_cast<int>(p) - 1] = wind_end_size;

      // Build a mask that highlights all the elements whose time
      // windows share (or are close) to any of the time windows
      // of the pulses associated with the current peak.
      i = static_cast<int>(timetol);
      if (i - 1 >= 0) {
        d = peak_ind[static_cast<int>(p) - 1];
        if (d - 1.0 < 1.0) {
          i4 = 0;
          i5 = 1;
          i6 = -1;
          i7 = 0;
          i8 = 1;
          i9 = -1;
        } else {
          i4 = static_cast<int>(d - 1.0) - 1;
          i5 = -1;
          i6 = 0;
          i7 = static_cast<int>(d - 1.0) - 1;
          i8 = -1;
          i9 = 0;
        }

        b_loop_ub = div_s32(i6 - i4, i5);
        if (d + 1.0 > scores.size(0)) {
          i10 = 0;
          i11 = 0;
        } else {
          i10 = static_cast<int>(peak_ind[static_cast<int>(p) - 1] + 1.0) - 1;
          i11 = scores.size(0);
        }

        if (peak_ind[static_cast<int>(p) - 1] + 1.0 > thresh.threshVecFine.size
            (0)) {
          i12 = 0;
          i13 = 0;
        } else {
          i12 = static_cast<int>(peak_ind[static_cast<int>(p) - 1] + 1.0) - 1;
          i13 = thresh.threshVecFine.size(0);
        }

        c_loop_ub = i11 - i10;
        if (d - 1.0 < 1.0) {
          i14 = 0;
          i15 = 1;
          i1 = -1;
        } else {
          i14 = static_cast<int>(peak_ind[static_cast<int>(p) - 1] - 1.0) - 1;
          i15 = -1;
          i1 = 0;
        }

        d_loop_ub = div_s32(i1 - i14, i15);
        if (peak_ind[static_cast<int>(p) - 1] + 1.0 > slope_val.size(0)) {
          i16 = 0;
          i1 = 0;
        } else {
          i16 = static_cast<int>(peak_ind[static_cast<int>(p) - 1] + 1.0) - 1;
          i1 = slope_val.size(0);
        }

        e_loop_ub = i1 - i16;
        S_cols_tmp = static_cast<int>(peak_ind[static_cast<int>(p) - 1]) - 1;
        f_loop_ub = S_cols.size(0);
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
        timeBlinderVec.set_size(n_freqs);
        indsOfBinsValid.set_size(n_freqs);
        for (i1 = 0; i1 < n_freqs; i1++) {
          timeBlinderVec[i1] = rtNaN;
          indsOfBinsValid[i1] = rtNaN;
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
        if (static_cast<double>(k) + 1.0 <= timetol - 1.0) {
          // Don't compute forward check when k=n_blks
          tp_temp = S_cols[(static_cast<int>(peak_ind[static_cast<int>(p) - 1])
                            + S_cols.size(0) * k) - 1];
          loop_ub = S_cols.size(0);
          b_x.set_size(S_cols.size(0));
          for (i1 = 0; i1 < loop_ub; i1++) {
            b_x[i1] = tp_temp - S_cols[i1 + S_cols.size(0) * (k + 1)];
          }

          nx = b_x.size(0);
          indsOfBinsValid.set_size(b_x.size(0));
          for (maxStftTimeWind = 0; maxStftTimeWind < nx; maxStftTimeWind++) {
            indsOfBinsValid[maxStftTimeWind] = std::abs(b_x[maxStftTimeWind]);
          }
        } else if (k + 1U >= 2U) {
          // Don't compute backward check when k=1
          tp_temp = S_cols[(static_cast<int>(peak_ind[static_cast<int>(p) - 1])
                            + S_cols.size(0) * k) - 1];
          loop_ub = S_cols.size(0);
          b_x.set_size(S_cols.size(0));
          for (i1 = 0; i1 < loop_ub; i1++) {
            b_x[i1] = tp_temp - S_cols[i1 + S_cols.size(0) * (k - 1)];
          }

          nx = b_x.size(0);
          timeBlinderVec.set_size(b_x.size(0));
          for (maxStftTimeWind = 0; maxStftTimeWind < nx; maxStftTimeWind++) {
            timeBlinderVec[maxStftTimeWind] = std::abs(b_x[maxStftTimeWind]);
          }
        }

        // There could be instances when a single block contains
        // two pulses, as mentioned above, but if the search is
        // only for one pulse (K = 1) then the if statments above
        // won't run. We need here to check if there are
        // identified scores within the current block that are
        // also one time repetition interval (tip+/tipu) away
        // from the current peak
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
        if (b_loop_ub + 1 == div_s32(i9 - i7, i8) + 1) {
          y.set_size(b_loop_ub + 1);
          for (i1 = 0; i1 <= b_loop_ub; i1++) {
            y[i1] = (scores[i4 + i5 * i1] < thresh.threshVecFine[i7 + i8 * i1]);
          }

          coder::c_eml_find(y, (int *)&inds_frwd_2_next_valley_data, &nx);
        } else {
          b_binary_expand_op((int *)&inds_frwd_2_next_valley_data, &nx, scores,
                             i4, i5, i6, this, i7, i8, i9);
        }

        wind_start_size = nx;
        for (i1 = 0; i1 < nx; i1++) {
          wind_start_data = static_cast<double>(inds_frwd_2_next_valley_data) -
            1.0;
        }

        if (c_loop_ub == i13 - i12) {
          y.set_size(c_loop_ub);
          for (i1 = 0; i1 < c_loop_ub; i1++) {
            y[i1] = (scores[i10 + i1] < thresh.threshVecFine[i12 + i1]);
          }

          coder::c_eml_find(y, (int *)&inds_frwd_2_next_valley_data, &nx);
        } else {
          b_binary_expand_op((int *)&inds_frwd_2_next_valley_data, &nx, scores,
                             i10, i11 - 1, this, i12, i13 - 1);
        }

        wind_end_size = nx;
        for (i1 = 0; i1 < nx; i1++) {
          naive_wind_end = static_cast<double>(inds_frwd_2_next_valley_data) -
            1.0;
        }

        // Here we look for the location where the slope changes.
        // We don't use the -1 like above because we want to be
        // sure to capture the entire saddle between peaks, so
        // we include the point after the transition of the slope
        // sign. If we didn't do this, then the lowest point
        // between the peaks that was still above the threshold
        // wouldn't be included in a sideband mask and might get
        // picked up later as an additional peak.
        y.set_size(d_loop_ub + 1);
        for (i1 = 0; i1 <= d_loop_ub; i1++) {
          y[i1] = slope_val[i14 + i15 * i1];
        }

        coder::c_eml_find(y, (int *)&inds_frwd_2_next_valley_data, &nx);
        maxStftTimeWind = nx;
        for (i1 = 0; i1 < nx; i1++) {
          inds_bkwd_2_next_valley_data = inds_frwd_2_next_valley_data;
        }

        y.set_size(e_loop_ub);
        for (i1 = 0; i1 < e_loop_ub; i1++) {
          y[i1] = slope_val[i16 + i1];
        }

        coder::c_eml_find(y, (int *)&inds_frwd_2_next_valley_data, &nx);

        // Wf_sub = Wf(freq_mask);
        if ((wind_end_size == 0) && (wind_start_size == 0)) {
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
          sideband_msk.set_size(n_freqs);
          for (i1 = 0; i1 < n_freqs; i1++) {
            sideband_msk[i1] = false;
          }

          if ((maxStftTimeWind == 0) && (nx == 0)) {
            sideband_msk.set_size(n_freqs);
            for (i1 = 0; i1 < n_freqs; i1++) {
              sideband_msk[i1] = true;
            }
          } else if ((maxStftTimeWind == 0) && (nx != 0)) {
            if (peak_ind[static_cast<int>(p) - 1] < 1.0) {
              loop_ub = 0;
            } else {
              loop_ub = static_cast<int>(peak_ind[static_cast<int>(p) - 1]);
            }

            for (i1 = 0; i1 < loop_ub; i1++) {
              sideband_msk[i1] = true;
            }
          } else if ((maxStftTimeWind != 0) && (nx == 0)) {
            if (d > n_freqs) {
              i1 = -1;
              wind_end_size = 0;
            } else {
              i1 = static_cast<int>(peak_ind[static_cast<int>(p) - 1]) - 2;
              wind_end_size = n_freqs;
            }

            loop_ub = (wind_end_size - i1) - 1;
            for (wind_end_size = 0; wind_end_size < loop_ub; wind_end_size++) {
              sideband_msk[(i1 + wind_end_size) + 1] = true;
            }
          } else if ((maxStftTimeWind != 0) && (nx != 0)) {
            if (inds_frwd_2_next_valley_data < -static_cast<double>
                (inds_bkwd_2_next_valley_data)) {
              b_excluded_freq_bands.set_size(1, 0);
            } else {
              loop_ub = inds_frwd_2_next_valley_data - static_cast<int>(-
                static_cast<double>(inds_bkwd_2_next_valley_data));
              b_excluded_freq_bands.set_size(1, loop_ub + 1);
              for (i1 = 0; i1 <= loop_ub; i1++) {
                b_excluded_freq_bands[i1] = -static_cast<double>
                  (inds_bkwd_2_next_valley_data) + static_cast<double>(i1);
              }
            }

            r15.set_size(1, b_excluded_freq_bands.size(1));
            loop_ub = b_excluded_freq_bands.size(1);
            for (i1 = 0; i1 < loop_ub; i1++) {
              r15[i1] = static_cast<int>(d + b_excluded_freq_bands[i1]);
            }

            loop_ub = r15.size(1);
            for (i1 = 0; i1 < loop_ub; i1++) {
              sideband_msk[r15[i1] - 1] = true;
            }
          }

          // If there was a threhold crossing before and/or after
          // the peak, sort out the sidebands here
        } else {
          sideband_msk.set_size(n_freqs);
          for (i1 = 0; i1 < n_freqs; i1++) {
            sideband_msk[i1] = false;
          }

          if ((wind_end_size == 0) && (wind_start_size != 0)) {
            // Threshold crossing back was found but not
            // forwards.
            // What is smaller, the distance from the peak to
            // the first entry backwards, or the distance
            // from the peak to the threshold crossing in
            // front of the peak? Use that distance as the
            // 1/2 width of the sideband.
            excluded_freq_bands.set_size(maxStftTimeWind, 2);
            for (i1 = 0; i1 < maxStftTimeWind; i1++) {
              excluded_freq_bands[0] = inds_bkwd_2_next_valley_data;
            }

            coder::array<double, 1U> b_wind_start;
            excluded_freq_bands[excluded_freq_bands.size(0)] = wind_start_data;
            b_wind_start = excluded_freq_bands.reshape(2);
            bandwidth_of_peak[static_cast<int>(p) - 1] = coder::internal::
              unaryMinOrMax_anonFcn1(b_wind_start);

            // Had to code this way so coder/simulink would know the size of the min operation
          } else if ((wind_end_size != 0) && (wind_start_size == 0)) {
            // Threshold crossing forward was found but not
            // backwards.
            // What is smaller, the distance from the peak to
            // the last entry forwards, or the distance
            // from the peak to the threshold crossing in
            // back of the peak? Use that distance as the
            // 1/2 width of the sideband.
            excluded_freq_bands.set_size(nx, 2);
            for (i1 = 0; i1 < nx; i1++) {
              excluded_freq_bands[0] = inds_frwd_2_next_valley_data;
            }

            coder::array<double, 1U> b_wind_start;
            excluded_freq_bands[excluded_freq_bands.size(0)] = naive_wind_end;
            b_wind_start = excluded_freq_bands.reshape(2);
            bandwidth_of_peak[static_cast<int>(p) - 1] = coder::internal::
              unaryMinOrMax_anonFcn1(b_wind_start);

            // Had to code this way so coder/simulink
            // would know the size of the min operation
          } else {
            coder::array<double, 1U> b_wind_start;

            // Threshold crossing forward and backward was
            // found.
            // What is smaller, the distance
            // from the peak to the threshold crossing in
            // or the distance from the peak to the nearby
            // valley? Use that distance as the 1/2 width of
            // the sideband. Do this both forwards and
            // backwards.
            if (maxStftTimeWind != 0) {
              wind_start.set_size(wind_start_size, 2);
              for (i1 = 0; i1 < wind_start_size; i1++) {
                wind_start[0] = wind_start_data;
              }

              wind_start[wind_start.size(0)] = inds_bkwd_2_next_valley_data;
              wind_start_size = 1;
              b_wind_start = wind_start.reshape(2);
              wind_start_data = coder::internal::unaryMinOrMax_anonFcn1
                (b_wind_start);
            }

            if (nx != 0) {
              excluded_freq_bands.set_size(1, 2);
              excluded_freq_bands[0] = inds_frwd_2_next_valley_data;
              for (i1 = 0; i1 < wind_end_size; i1++) {
                excluded_freq_bands[excluded_freq_bands.size(0)] =
                  naive_wind_end;
              }

              wind_end_size = 1;
              b_wind_start = excluded_freq_bands.reshape(2);
              naive_wind_end = coder::internal::unaryMinOrMax_anonFcn1
                (b_wind_start);
            }

            for (i1 = 0; i1 < wind_start_size; i1++) {
              freq_ind_rng_data[0] = wind_start_data;
            }

            for (i1 = 0; i1 < wind_end_size; i1++) {
              freq_ind_rng_data[wind_start_size] = naive_wind_end;
            }

            wind_end_size = wind_start_size << 1;
            b_freq_ind_rng_data.set(&freq_ind_rng_data[0], wind_end_size);
            bandwidth_of_peak[static_cast<int>(p) - 1] = coder::internal::
              maximum(b_freq_ind_rng_data);
          }

          // Make sure we aren't requesting masking of elements
          // that are outside the bounds of what we have
          // available in the vector
          t_srch_rng[0] = 1.0;
          next_pulse_start = bandwidth_of_peak[static_cast<int>(p) - 1];
          t_srch_rng[1] = d - next_pulse_start;
          tip_temp = coder::internal::maximum(t_srch_rng);
          t_srch_rng[0] = n_freqs;
          t_srch_rng[1] = d + next_pulse_start;
          next_pulse_start = coder::internal::minimum(t_srch_rng);
          if (tip_temp > next_pulse_start) {
            i1 = -1;
            wind_end_size = 0;
          } else {
            i1 = static_cast<int>(tip_temp) - 2;
            wind_end_size = static_cast<int>(next_pulse_start);
          }

          loop_ub = (wind_end_size - i1) - 1;
          for (wind_end_size = 0; wind_end_size < loop_ub; wind_end_size++) {
            sideband_msk[(i1 + wind_end_size) + 1] = true;
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
        tp_temp = S_cols[S_cols_tmp + S_cols.size(0) * k];
        b_x.set_size(S_cols.size(0));
        for (i1 = 0; i1 < f_loop_ub; i1++) {
          b_x[i1] = tp_temp - S_cols[i1 + S_cols.size(0) * k];
        }

        nx = b_x.size(0);
        peak.set_size(b_x.size(0));
        for (maxStftTimeWind = 0; maxStftTimeWind < nx; maxStftTimeWind++) {
          peak[maxStftTimeWind] = std::abs(b_x[maxStftTimeWind]);
        }

        if (peak.size(0) == 1) {
          i1 = timeBlinderVec.size(0);
        } else {
          i1 = peak.size(0);
        }

        if (peak.size(0) == 1) {
          maxStftTimeWind = timeBlinderVec.size(0);
        } else {
          maxStftTimeWind = peak.size(0);
        }

        if (maxStftTimeWind == 1) {
          maxStftTimeWind = indsOfBinsValid.size(0);
        } else if (peak.size(0) == 1) {
          maxStftTimeWind = timeBlinderVec.size(0);
        } else {
          maxStftTimeWind = peak.size(0);
        }

        if (peak.size(0) == 1) {
          inds_bkwd_2_next_valley_data = timeBlinderVec.size(0);
        } else {
          inds_bkwd_2_next_valley_data = peak.size(0);
        }

        if (sideband_msk.size(0) == 1) {
          if (inds_bkwd_2_next_valley_data == 1) {
            inds_bkwd_2_next_valley_data = indsOfBinsValid.size(0);
          } else if (peak.size(0) == 1) {
            inds_bkwd_2_next_valley_data = timeBlinderVec.size(0);
          } else {
            inds_bkwd_2_next_valley_data = peak.size(0);
          }
        } else {
          inds_bkwd_2_next_valley_data = sideband_msk.size(0);
        }

        if (peak.size(0) == 1) {
          i2 = timeBlinderVec.size(0);
        } else {
          i2 = peak.size(0);
        }

        if (sideband_msk.size(0) == 1) {
          if (i2 == 1) {
            i2 = indsOfBinsValid.size(0);
          } else if (peak.size(0) == 1) {
            i2 = timeBlinderVec.size(0);
          } else {
            i2 = peak.size(0);
          }
        } else {
          i2 = sideband_msk.size(0);
        }

        if (peak.size(0) == 1) {
          i3 = timeBlinderVec.size(0);
        } else {
          i3 = peak.size(0);
        }

        if (i2 == 1) {
          i2 = S_cols.size(0);
        } else if (sideband_msk.size(0) == 1) {
          if (i3 == 1) {
            i2 = indsOfBinsValid.size(0);
          } else if (peak.size(0) == 1) {
            i2 = timeBlinderVec.size(0);
          } else {
            i2 = peak.size(0);
          }
        } else {
          i2 = sideband_msk.size(0);
        }

        if ((peak.size(0) == timeBlinderVec.size(0)) && (i1 ==
             indsOfBinsValid.size(0)) && (sideband_msk.size(0) ==
             maxStftTimeWind) && (inds_bkwd_2_next_valley_data == S_cols.size(0))
            && (msk.size(0) == i2)) {
          nx = msk.size(0) - 1;
          next_pulse_start = S_cols[S_cols_tmp + S_cols.size(0) * k] + b_N;
          tp_temp = next_pulse_start + b_M;
          a = next_pulse_start - b_M;
          next_pulse_start = S_cols[S_cols_tmp + S_cols.size(0) * k] - b_N;
          wind_start_data = next_pulse_start - b_M;
          tip_temp = next_pulse_start + b_M;
          sideband_msk.set_size(msk.size(0));
          for (i1 = 0; i1 <= nx; i1++) {
            t_lastknown = S_cols[i1 + S_cols.size(0) * k];
            sideband_msk[i1] = (msk[i1 + msk.size(0) * (static_cast<int>(p) - 1)]
                                || msk[i1 + msk.size(0) * static_cast<int>(p)] ||
                                (sideband_msk[i1] || ((peak[i1] <= stft_dt) ||
              (timeBlinderVec[i1] <= stft_dt) || (indsOfBinsValid[i1] <= stft_dt))
                                 || (((t_lastknown < tp_temp) && (t_lastknown >
              a)) || ((t_lastknown > wind_start_data) && (t_lastknown < tip_temp)))));
          }

          loop_ub = sideband_msk.size(0);
          for (i1 = 0; i1 < loop_ub; i1++) {
            msk[i1 + msk.size(0) * static_cast<int>(p)] = sideband_msk[i1];
          }
        } else {
          d_binary_expand_op(msk, p, sideband_msk, peak, stft_dt, timeBlinderVec,
                             indsOfBinsValid, S_cols, k, peak_ind, b_N, b_M);
        }
      }

      // Extract the mask for this peak and no others
      loop_ub = msk.size(0);
      for (i = 0; i < loop_ub; i++) {
        indiv_msk[i + indiv_msk.size(0) * (static_cast<int>(p) - 1)] = (msk[i +
          msk.size(0) * static_cast<int>(p)] - msk[i + msk.size(0) * (
          static_cast<int>(p) - 1)] != 0);
      }

      // Update the current scores to exclude peaks and sidebands
      // we have identified so far.
      // Mask the recently found sidebands
      if (scores.size(0) == 1) {
        i = msk.size(0);
      } else {
        i = scores.size(0);
      }

      if ((scores.size(0) == msk.size(0)) && (i == slope_peak.size(0))) {
        timeBlinderVec.set_size(scores.size(0));
        loop_ub = scores.size(0);
        for (i = 0; i < loop_ub; i++) {
          timeBlinderVec[i] = scores[i] * static_cast<double>(!msk[i + msk.size
            (0) * static_cast<int>(p)]) * static_cast<double>(slope_peak[i]);
        }
      } else {
        e_binary_expand_op(timeBlinderVec, scores, msk, p, slope_peak);
      }

      // Mask to only look at peaks
      if (timeBlinderVec.size(0) == 1) {
        i = thresh.threshVecFine.size(0);
      } else {
        i = timeBlinderVec.size(0);
      }

      if ((timeBlinderVec.size(0) == thresh.threshVecFine.size(0)) &&
          (timeBlinderVec.size(0) == i)) {
        loop_ub = timeBlinderVec.size(0);
        for (i = 0; i < loop_ub; i++) {
          timeBlinderVec[i] = timeBlinderVec[i] * static_cast<double>
            (timeBlinderVec[i] >= thresh.threshVecFine[i]);
        }
      } else {
        b_binary_expand_op(timeBlinderVec, this);
      }

      // Eliminate non-threshold exceeding scores from consideration
      //                  hold on;plot(peak_masked_curr_scores)
      //                  pause(1)
      // peak_masked_curr_scores = curr_scores.*slope_peak.*independent_super_thresh_msk;
      p++;
    } else {
      exitg2 = 1;
    }
  } while (exitg2 == 0);

  // Clean up the msk and indiv_mask so their columns align with
  // n_pulsegroup_found.
  coder::g_circshift(msk);
  if (static_cast<int>(p - 1U) < 1) {
    loop_ub = 0;
  } else {
    loop_ub = static_cast<int>(p) - 1;
  }

  wind_end_size = indiv_msk.size(0) - 1;
  inds_bkwd_2_next_valley_data = indiv_msk.size(0);
  for (i = 0; i < loop_ub; i++) {
    for (i1 = 0; i1 < inds_bkwd_2_next_valley_data; i1++) {
      indiv_msk[i1 + (wind_end_size + 1) * i] = indiv_msk[i1 + indiv_msk.size(0)
        * i];
    }
  }

  indiv_msk.set_size(wind_end_size + 1, loop_ub);
  if (static_cast<int>(p - 1U) > 0) {
    // Only update from NaN if there were some found.
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
  makepulsestruc(&next_pulse_start, &tip_temp, &tp_temp, &a, &wind_start_data,
                 &t_lastknown, expl_temp.t_next, &stft_dt, &timetol,
                 &naive_wind_end, expl_temp.mode, &varargout_1, &t4_con_dec);
  expl_temp.con_dec = t4_con_dec;
  expl_temp.det_dec = varargout_1;
  expl_temp.fend = naive_wind_end;
  expl_temp.fstart = timetol;
  expl_temp.fp = stft_dt;
  expl_temp.t_f = t_lastknown;
  expl_temp.t_0 = wind_start_data;
  expl_temp.yw = a;
  expl_temp.SNR = tp_temp;
  expl_temp.P = tip_temp;
  expl_temp.A = next_pulse_start;
  coder::repmat(&expl_temp, static_cast<double>(yw_max_all_freq.size(0)),
                static_cast<double>(yw_max_all_freq.size(1)), pl_out);

  // Create a frequency array that accounts for the masking that
  // was done to reduce the frequency space.
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
  inds_bkwd_2_next_valley_data = freq_mask.size(0) - 1;
  wind_end_size = 0;
  for (int k{0}; k <= inds_bkwd_2_next_valley_data; k++) {
    if (freq_mask[k]) {
      wind_end_size++;
    }
  }

  r12.set_size(wind_end_size);
  nx = 0;
  for (int k{0}; k <= inds_bkwd_2_next_valley_data; k++) {
    if (freq_mask[k]) {
      r12[nx] = k + 1;
      nx++;
    }
  }

  loop_ub = S_cols.size(1);
  r13.set_size(r12.size(0), S_cols.size(1));
  for (i = 0; i < loop_ub; i++) {
    inds_bkwd_2_next_valley_data = r12.size(0);
    for (i1 = 0; i1 < inds_bkwd_2_next_valley_data; i1++) {
      r13[i1 + r13.size(0) * i] = stft->t[static_cast<int>(S_cols[(r12[i1] +
        S_cols.size(0) * i) - 1]) - 1];
    }
  }

  inds_bkwd_2_next_valley_data = freq_mask.size(0) - 1;
  wind_end_size = 0;
  for (int k{0}; k <= inds_bkwd_2_next_valley_data; k++) {
    if (freq_mask[k]) {
      wind_end_size++;
    }
  }

  r14.set_size(wind_end_size);
  nx = 0;
  for (int k{0}; k <= inds_bkwd_2_next_valley_data; k++) {
    if (freq_mask[k]) {
      r14[nx] = k + 1;
      nx++;
    }
  }

  next_pulse_start = stft->t[0];
  loop_ub = r13.size(1);
  for (i = 0; i < loop_ub; i++) {
    inds_bkwd_2_next_valley_data = r13.size(0);
    for (i1 = 0; i1 < inds_bkwd_2_next_valley_data; i1++) {
      refmat[(r14[i1] + refmat.size(0) * i) - 1] = (r13[i1 + r13.size(0) * i] -
        next_pulse_start) + t_0;
    }
  }

  // Don't forget the add the t_0 of this waveform
  // f_bands    = [Wf_sub-(Wf_sub(2)-Wf_sub(1))/2,...
  //               Wf_sub+(Wf_sub(2)-Wf_sub(1))/2];
  next_pulse_start = (Wf[1] - Wf[0]) / 2.0;
  timeSearchRange.set_size(Wf.size(0), 2);
  loop_ub = Wf.size(0);
  for (i = 0; i < loop_ub; i++) {
    timeSearchRange[i] = Wf[i] - next_pulse_start;
  }

  loop_ub = Wf.size(0);
  for (i = 0; i < loop_ub; i++) {
    timeSearchRange[i + timeSearchRange.size(0)] = Wf[i] + next_pulse_start;
  }

  // Build out the pulse object for each one found
  i = yw_max_all_freq.size(1);
  for (int k{0}; k < i; k++) {
    for (wind_end_size = 0; wind_end_size < n_freqs; wind_end_size++) {
      t_lastknown = refmat[wind_end_size + refmat.size(0) * k];
      t_srch_rng[0] = ((t_lastknown + ps_pos->t_ip) - ps_pos->t_ipu) -
        (-ps_pos->t_ipj);
      t_srch_rng[1] = ((t_lastknown + ps_pos->t_ip) + ps_pos->t_ipu) +
        ps_pos->t_ipj;
      b_makepulsestruc(signalAmps[wind_end_size + signalAmps.size(0) * k],
                       yw_max_all_freq[wind_end_size + yw_max_all_freq.size(0) *
                       k], b_refmat[wind_end_size + b_refmat.size(0) * k],
                       t_lastknown, t_lastknown + ps_pre->t_p, t_srch_rng,
                       Wf[wind_end_size], timeSearchRange[wind_end_size],
                       timeSearchRange[wind_end_size + timeSearchRange.size(0)],
                       &pl_out[wind_end_size + pl_out.size(0) * k]);

      // %NaN,...
      pl_out[wind_end_size + pl_out.size(0) * k].con_dec = false;

      // Confirmation status
      y.set_size(thresh.threshVecFine.size(0));
      loop_ub = thresh.threshVecFine.size(0);
      for (i1 = 0; i1 < loop_ub; i1++) {
        y[i1] = (scores[wind_end_size] >= thresh.threshVecFine[i1]);
      }

      if (coder::internal::ifWhileCond(y)) {
        // scores(j)>=thresh(j)
        pl_out[wind_end_size + pl_out.size(0) * k].det_dec = true;
      }
    }
  }
}

static void b_and(coder::array<boolean_T, 1U> &in1, const coder::array<boolean_T,
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

static void b_binary_expand_op(coder::array<double, 2U> &in1, double in2, double
  in3, const coder::array<double, 2U> &in4, double in5)
{
  coder::array<double, 2U> b_in2;
  int i;
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  if (in1.size(1) == 1) {
    i = in4.size(1);
  } else {
    i = in1.size(1);
  }

  b_in2.set_size(1, i);
  stride_0_1 = (in4.size(1) != 1);
  stride_1_1 = (in1.size(1) != 1);
  if (in1.size(1) == 1) {
    loop_ub = in4.size(1);
  } else {
    loop_ub = in1.size(1);
  }

  for (i = 0; i < loop_ub; i++) {
    b_in2[i] = (in2 + in3 * in4[i * stride_0_1]) - in5 * in1[i * stride_1_1];
  }

  in1.set_size(1, b_in2.size(1));
  loop_ub = b_in2.size(1);
  for (i = 0; i < loop_ub; i++) {
    in1[i] = b_in2[i];
  }
}

static void b_binary_expand_op(coder::array<double, 2U> &in1, double in2, const
  coder::array<double, 2U> &in3)
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
    i = in3.size(0);
  } else {
    i = in1.size(0);
  }

  if (in1.size(1) == 1) {
    i1 = in3.size(1);
  } else {
    i1 = in1.size(1);
  }

  b_in2.set_size(i, i1);
  stride_0_0 = (in3.size(0) != 1);
  stride_0_1 = (in3.size(1) != 1);
  stride_1_0 = (in1.size(0) != 1);
  stride_1_1 = (in1.size(1) != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  if (in1.size(1) == 1) {
    loop_ub = in3.size(1);
  } else {
    loop_ub = in1.size(1);
  }

  for (i = 0; i < loop_ub; i++) {
    if (in1.size(0) == 1) {
      b_loop_ub = in3.size(0);
    } else {
      b_loop_ub = in1.size(0);
    }

    for (i1 = 0; i1 < b_loop_ub; i1++) {
      b_in2[i1 + b_in2.size(0) * i] = in2 * in3[i1 * stride_0_0 + in3.size(0) *
        aux_0_1] - in1[i1 * stride_1_0 + in1.size(0) * aux_1_1];
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

static void b_binary_expand_op(coder::array<double, 2U> &in1, const waveform
  *in2, const coder::array<double, 2U> &in3)
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
  if (in3.size(0) == 1) {
    i = in2->stft->S.size(0);
  } else {
    i = in3.size(0);
  }

  if (in3.size(1) == 1) {
    i1 = in2->stft->S.size(1);
  } else {
    i1 = in3.size(1);
  }

  b_in2.set_size(i, i1);
  stride_0_0 = (in2->stft->S.size(0) != 1);
  stride_0_1 = (in2->stft->S.size(1) != 1);
  stride_1_0 = (in3.size(0) != 1);
  stride_1_1 = (in3.size(1) != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  if (in3.size(1) == 1) {
    loop_ub = in2->stft->S.size(1);
  } else {
    loop_ub = in3.size(1);
  }

  for (i = 0; i < loop_ub; i++) {
    int b_loop_ub;
    if (in3.size(0) == 1) {
      b_loop_ub = in2->stft->S.size(0);
    } else {
      b_loop_ub = in3.size(0);
    }

    for (i1 = 0; i1 < b_loop_ub; i1++) {
      b_in2[i1 + b_in2.size(0) * i].re = in2->stft->S[i1 * stride_0_0 +
        in2->stft->S.size(0) * aux_0_1].re + in3[i1 * stride_1_0 + in3.size(0) *
        aux_1_1];
      b_in2[i1 + b_in2.size(0) * i].im = in2->stft->S[i1 * stride_0_0 +
        in2->stft->S.size(0) * aux_0_1].im;
    }

    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }

  coder::b_abs(b_in2, in1);
}

static void b_binary_expand_op(coder::array<double, 2U> &in1, const coder::array<
  double, 2U> &in2, const coder::array<double, 2U> &in3, int in4, int in5)
{
  coder::array<double, 2U> b_in2;
  int aux_0_1;
  int aux_1_1;
  int aux_2_1;
  int i;
  int i1;
  int loop_ub;
  int stride_0_0;
  int stride_0_1;
  int stride_1_0;
  int stride_1_1;
  int stride_2_0;
  int stride_2_1;
  if (in3.size(0) == 1) {
    if (in1.size(0) == 1) {
      i = in2.size(0);
    } else {
      i = in1.size(0);
    }
  } else {
    i = in3.size(0);
  }

  if (in3.size(1) == 1) {
    if (in1.size(1) == 1) {
      i1 = in2.size(1);
    } else {
      i1 = in1.size(1);
    }
  } else {
    i1 = in3.size(1);
  }

  b_in2.set_size(i, i1);
  stride_0_0 = (in2.size(0) != 1);
  stride_0_1 = (in2.size(1) != 1);
  stride_1_0 = (in1.size(0) != 1);
  stride_1_1 = (in1.size(1) != 1);
  stride_2_0 = (in3.size(0) != 1);
  stride_2_1 = (in3.size(1) != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  aux_2_1 = 0;
  if (in3.size(1) == 1) {
    if (in1.size(1) == 1) {
      loop_ub = in2.size(1);
    } else {
      loop_ub = in1.size(1);
    }
  } else {
    loop_ub = in3.size(1);
  }

  for (i = 0; i < loop_ub; i++) {
    int b_loop_ub;
    if (in3.size(0) == 1) {
      if (in1.size(0) == 1) {
        b_loop_ub = in2.size(0);
      } else {
        b_loop_ub = in1.size(0);
      }
    } else {
      b_loop_ub = in3.size(0);
    }

    for (i1 = 0; i1 < b_loop_ub; i1++) {
      b_in2[i1 + b_in2.size(0) * i] = (in2[i1 * stride_0_0 + in2.size(0) *
        aux_0_1] + in1[i1 * stride_1_0 + in1.size(0) * aux_1_1]) + in3[i1 *
        stride_2_0 + in3.size(0) * aux_2_1];
    }

    aux_2_1 += stride_2_1;
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }

  double b_in4[2];
  b_in4[0] = static_cast<unsigned int>(in4);
  b_in4[1] = static_cast<unsigned int>(in5);
  coder::imresize(b_in2, b_in4, in1);
}

static void b_binary_expand_op(coder::array<double, 2U> &in1, const coder::array<
  double, 2U> &in2, const coder::array<double, 2U> &in3, const coder::array<
  double, 2U> &in4, const coder::array<double, 2U> &in5)
{
  coder::array<double, 2U> b_in1;
  int aux_0_1;
  int aux_1_1;
  int aux_2_1;
  int aux_3_1;
  int aux_4_1;
  int b_loop_ub;
  int i;
  int i1;
  int loop_ub;
  int stride_0_0;
  int stride_0_1;
  int stride_1_0;
  int stride_1_1;
  int stride_2_0;
  int stride_2_1;
  int stride_3_0;
  int stride_3_1;
  int stride_4_0;
  int stride_4_1;
  if (in5.size(0) == 1) {
    if (in4.size(0) == 1) {
      if (in3.size(0) == 1) {
        if (in2.size(0) == 1) {
          i = in1.size(0);
        } else {
          i = in2.size(0);
        }
      } else {
        i = in3.size(0);
      }
    } else {
      i = in4.size(0);
    }
  } else {
    i = in5.size(0);
  }

  if (in5.size(1) == 1) {
    if (in4.size(1) == 1) {
      if (in3.size(1) == 1) {
        if (in2.size(1) == 1) {
          i1 = in1.size(1);
        } else {
          i1 = in2.size(1);
        }
      } else {
        i1 = in3.size(1);
      }
    } else {
      i1 = in4.size(1);
    }
  } else {
    i1 = in5.size(1);
  }

  b_in1.set_size(i, i1);
  stride_0_0 = (in1.size(0) != 1);
  stride_0_1 = (in1.size(1) != 1);
  stride_1_0 = (in2.size(0) != 1);
  stride_1_1 = (in2.size(1) != 1);
  stride_2_0 = (in3.size(0) != 1);
  stride_2_1 = (in3.size(1) != 1);
  stride_3_0 = (in4.size(0) != 1);
  stride_3_1 = (in4.size(1) != 1);
  stride_4_0 = (in5.size(0) != 1);
  stride_4_1 = (in5.size(1) != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  aux_2_1 = 0;
  aux_3_1 = 0;
  aux_4_1 = 0;
  if (in5.size(1) == 1) {
    if (in4.size(1) == 1) {
      if (in3.size(1) == 1) {
        if (in2.size(1) == 1) {
          loop_ub = in1.size(1);
        } else {
          loop_ub = in2.size(1);
        }
      } else {
        loop_ub = in3.size(1);
      }
    } else {
      loop_ub = in4.size(1);
    }
  } else {
    loop_ub = in5.size(1);
  }

  for (i = 0; i < loop_ub; i++) {
    if (in5.size(0) == 1) {
      if (in4.size(0) == 1) {
        if (in3.size(0) == 1) {
          if (in2.size(0) == 1) {
            b_loop_ub = in1.size(0);
          } else {
            b_loop_ub = in2.size(0);
          }
        } else {
          b_loop_ub = in3.size(0);
        }
      } else {
        b_loop_ub = in4.size(0);
      }
    } else {
      b_loop_ub = in5.size(0);
    }

    for (i1 = 0; i1 < b_loop_ub; i1++) {
      b_in1[i1 + b_in1.size(0) * i] = (((in1[i1 * stride_0_0 + in1.size(0) *
        aux_0_1] + in2[i1 * stride_1_0 + in2.size(0) * aux_1_1]) + in3[i1 *
        stride_2_0 + in3.size(0) * aux_2_1]) + in4[i1 * stride_3_0 + in4.size(0)
        * aux_3_1]) + in5[i1 * stride_4_0 + in5.size(0) * aux_4_1];
    }

    aux_4_1 += stride_4_1;
    aux_3_1 += stride_3_1;
    aux_2_1 += stride_2_1;
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

static void b_binary_expand_op(coder::array<double, 2U> &in1, double in2, double
  in3, double in4, const coder::array<double, 2U> &in5)
{
  coder::array<double, 2U> b_in2;
  int i;
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  if (in5.size(1) == 1) {
    i = in1.size(1);
  } else {
    i = in5.size(1);
  }

  b_in2.set_size(1, i);
  stride_0_1 = (in1.size(1) != 1);
  stride_1_1 = (in5.size(1) != 1);
  if (in5.size(1) == 1) {
    loop_ub = in1.size(1);
  } else {
    loop_ub = in5.size(1);
  }

  for (i = 0; i < loop_ub; i++) {
    b_in2[i] = (in2 + in3 * in1[i * stride_0_1]) + in4 * in5[i * stride_1_1];
  }

  in1.set_size(1, b_in2.size(1));
  loop_ub = b_in2.size(1);
  for (i = 0; i < loop_ub; i++) {
    in1[i] = b_in2[i];
  }
}

static void b_binary_expand_op(coder::array<double, 1U> &in1, int in2, double
  in3, const coder::array<double, 2U> &in4, const coder::array<double, 2U> &in5)
{
  coder::array<double, 1U> r;
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  r.set_size(in2 + in4.size(1));
  for (i = 0; i < in2; i++) {
    r[i] = 0.0;
  }

  loop_ub = in4.size(1);
  for (i = 0; i < loop_ub; i++) {
    r[i + in2] = in3 * in4[i];
  }

  if (in5.size(1) == 1) {
    i = r.size(0);
  } else {
    i = in5.size(1);
  }

  in1.set_size(i);
  stride_0_0 = (r.size(0) != 1);
  stride_1_0 = (in5.size(1) != 1);
  if (in5.size(1) == 1) {
    loop_ub = r.size(0);
  } else {
    loop_ub = in5.size(1);
  }

  for (i = 0; i < loop_ub; i++) {
    in1[i] = r[i * stride_0_0] + in5[i * stride_1_0];
  }
}

static void b_binary_expand_op(coder::array<double, 1U> &in1, const waveform
  *in2)
{
  coder::array<double, 1U> b_in1;
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  int stride_2_0;
  if (in2->thresh.threshVecFine.size(0) == 1) {
    i = in1.size(0);
  } else {
    i = in2->thresh.threshVecFine.size(0);
  }

  if (i == 1) {
    i = in1.size(0);
  } else if (in2->thresh.threshVecFine.size(0) == 1) {
    i = in1.size(0);
  } else {
    i = in2->thresh.threshVecFine.size(0);
  }

  b_in1.set_size(i);
  stride_0_0 = (in1.size(0) != 1);
  stride_1_0 = (in1.size(0) != 1);
  stride_2_0 = (in2->thresh.threshVecFine.size(0) != 1);
  if (in2->thresh.threshVecFine.size(0) == 1) {
    i = in1.size(0);
  } else {
    i = in2->thresh.threshVecFine.size(0);
  }

  if (i == 1) {
    loop_ub = in1.size(0);
  } else if (in2->thresh.threshVecFine.size(0) == 1) {
    loop_ub = in1.size(0);
  } else {
    loop_ub = in2->thresh.threshVecFine.size(0);
  }

  for (i = 0; i < loop_ub; i++) {
    b_in1[i] = in1[i * stride_0_0] * static_cast<double>(in1[i * stride_1_0] >=
      in2->thresh.threshVecFine[i * stride_2_0]);
  }

  in1.set_size(b_in1.size(0));
  loop_ub = b_in1.size(0);
  for (i = 0; i < loop_ub; i++) {
    in1[i] = b_in1[i];
  }
}

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

static void c_binary_expand_op(coder::array<boolean_T, 2U> &in1, const coder::
  array<double, 2U> &in2, const int in3[2], const coder::array<double, 2U> &in4,
  const coder::array<double, 2U> &in5, const int in6[2], const coder::array<
  double, 2U> &in7, const coder::array<double, 2U> &in8, const int in9[2], const
  coder::array<double, 2U> &in10, const int in11[2], const coder::array<double,
  2U> &in12, const int in13[2], const coder::array<double, 2U> &in14, const int
  in15[2])
{
  int b_unnamed_idx_1;
  int c_unnamed_idx_1;
  int d_unnamed_idx_1;
  int e_unnamed_idx_1;
  int f_unnamed_idx_1;
  int g_unnamed_idx_1;
  int h_unnamed_idx_1;
  int i;
  int stride_1_1;
  int stride_2_1;
  int stride_3_1;
  int stride_4_1;
  int stride_5_1;
  int stride_6_1;
  int stride_7_1;
  int unnamed_idx_1;
  unnamed_idx_1 = in3[1];
  b_unnamed_idx_1 = in6[1];
  c_unnamed_idx_1 = in9[1];
  d_unnamed_idx_1 = in11[1];
  e_unnamed_idx_1 = in13[1];
  f_unnamed_idx_1 = in15[1];
  if (f_unnamed_idx_1 == 1) {
    g_unnamed_idx_1 = e_unnamed_idx_1;
  } else {
    g_unnamed_idx_1 = f_unnamed_idx_1;
  }

  if (g_unnamed_idx_1 == 1) {
    if (d_unnamed_idx_1 == 1) {
      g_unnamed_idx_1 = c_unnamed_idx_1;
    } else {
      g_unnamed_idx_1 = d_unnamed_idx_1;
    }
  } else if (f_unnamed_idx_1 == 1) {
    g_unnamed_idx_1 = e_unnamed_idx_1;
  } else {
    g_unnamed_idx_1 = f_unnamed_idx_1;
  }

  if (in7.size(1) == 1) {
    i = b_unnamed_idx_1;
  } else {
    i = in7.size(1);
  }

  if (f_unnamed_idx_1 == 1) {
    h_unnamed_idx_1 = e_unnamed_idx_1;
  } else {
    h_unnamed_idx_1 = f_unnamed_idx_1;
  }

  if (g_unnamed_idx_1 == 1) {
    if (i == 1) {
      if (in4.size(1) == 1) {
        g_unnamed_idx_1 = unnamed_idx_1;
      } else {
        g_unnamed_idx_1 = in4.size(1);
      }
    } else if (in7.size(1) == 1) {
      g_unnamed_idx_1 = b_unnamed_idx_1;
    } else {
      g_unnamed_idx_1 = in7.size(1);
    }
  } else if (h_unnamed_idx_1 == 1) {
    if (d_unnamed_idx_1 == 1) {
      g_unnamed_idx_1 = c_unnamed_idx_1;
    } else {
      g_unnamed_idx_1 = d_unnamed_idx_1;
    }
  } else if (f_unnamed_idx_1 == 1) {
    g_unnamed_idx_1 = e_unnamed_idx_1;
  } else {
    g_unnamed_idx_1 = f_unnamed_idx_1;
  }

  in1.set_size(1, g_unnamed_idx_1);
  h_unnamed_idx_1 = (unnamed_idx_1 != 1);
  stride_1_1 = (in4.size(1) != 1);
  stride_2_1 = (b_unnamed_idx_1 != 1);
  stride_3_1 = (in7.size(1) != 1);
  stride_4_1 = (c_unnamed_idx_1 != 1);
  stride_5_1 = (d_unnamed_idx_1 != 1);
  stride_6_1 = (e_unnamed_idx_1 != 1);
  stride_7_1 = (f_unnamed_idx_1 != 1);
  if (f_unnamed_idx_1 == 1) {
    g_unnamed_idx_1 = e_unnamed_idx_1;
  } else {
    g_unnamed_idx_1 = f_unnamed_idx_1;
  }

  if (g_unnamed_idx_1 == 1) {
    if (d_unnamed_idx_1 == 1) {
      g_unnamed_idx_1 = c_unnamed_idx_1;
    } else {
      g_unnamed_idx_1 = d_unnamed_idx_1;
    }
  } else if (f_unnamed_idx_1 == 1) {
    g_unnamed_idx_1 = e_unnamed_idx_1;
  } else {
    g_unnamed_idx_1 = f_unnamed_idx_1;
  }

  if (g_unnamed_idx_1 == 1) {
    if (in7.size(1) == 1) {
      i = b_unnamed_idx_1;
    } else {
      i = in7.size(1);
    }

    if (i == 1) {
      if (in4.size(1) != 1) {
        unnamed_idx_1 = in4.size(1);
      }
    } else if (in7.size(1) == 1) {
      unnamed_idx_1 = b_unnamed_idx_1;
    } else {
      unnamed_idx_1 = in7.size(1);
    }
  } else {
    if (f_unnamed_idx_1 == 1) {
      unnamed_idx_1 = e_unnamed_idx_1;
    } else {
      unnamed_idx_1 = f_unnamed_idx_1;
    }

    if (unnamed_idx_1 == 1) {
      if (d_unnamed_idx_1 == 1) {
        unnamed_idx_1 = c_unnamed_idx_1;
      } else {
        unnamed_idx_1 = d_unnamed_idx_1;
      }
    } else if (f_unnamed_idx_1 == 1) {
      unnamed_idx_1 = e_unnamed_idx_1;
    } else {
      unnamed_idx_1 = f_unnamed_idx_1;
    }
  }

  for (b_unnamed_idx_1 = 0; b_unnamed_idx_1 < unnamed_idx_1; b_unnamed_idx_1++)
  {
    in1[b_unnamed_idx_1] = ((in2[b_unnamed_idx_1 * h_unnamed_idx_1] <=
      in4[b_unnamed_idx_1 * stride_1_1]) && (in5[b_unnamed_idx_1 * stride_2_1] >=
      in7[b_unnamed_idx_1 * stride_3_1]) && ((in8[b_unnamed_idx_1 * stride_4_1] >=
      in10[b_unnamed_idx_1 * stride_5_1] - 100.0) && (in12[b_unnamed_idx_1 *
      stride_6_1] <= in14[b_unnamed_idx_1 * stride_7_1] + 100.0)));
  }
}

static void d_binary_expand_op(coder::array<boolean_T, 2U> &in1, unsigned int
  in2, const coder::array<boolean_T, 1U> &in3, const coder::array<double, 1U>
  &in4, double in5, const coder::array<double, 1U> &in6, const coder::array<
  double, 1U> &in7, const coder::array<double, 2U> &in8, int in9, const coder::
  array<double, 1U> &in10, double in11, double in12)
{
  coder::array<boolean_T, 1U> c_in1;
  double b_in8;
  double c_in8;
  double d_in8;
  double in8_tmp;
  double in8_tmp_tmp;
  int b_in1;
  int b_in1_tmp;
  int c_in1_tmp;
  int i;
  int i1;
  int in1_tmp;
  int stride_1_0;
  int stride_2_0;
  int stride_3_0;
  int stride_4_0;
  int stride_5_0;
  int stride_6_0;
  b_in1 = in1.size(0) - 1;
  in8_tmp_tmp = in8[(static_cast<int>(in10[static_cast<int>(in2) - 1]) +
                     in8.size(0) * in9) - 1];
  in8_tmp = in8_tmp_tmp + in11;
  b_in8 = in8_tmp + in12;
  c_in8 = in8_tmp - in12;
  in8_tmp = in8_tmp_tmp - in11;
  d_in8 = in8_tmp - in12;
  in8_tmp_tmp = in8_tmp + in12;
  i = in8.size(0);
  in1_tmp = in8.size(0);
  if (in1_tmp == 1) {
    b_in1_tmp = i;
  } else {
    b_in1_tmp = in1_tmp;
  }

  if (in7.size(0) == 1) {
    if (in6.size(0) == 1) {
      i1 = in4.size(0);
    } else {
      i1 = in6.size(0);
    }
  } else {
    i1 = in7.size(0);
  }

  if (b_in1_tmp == 1) {
    if (i1 == 1) {
      b_in1_tmp = in3.size(0);
    } else if (in7.size(0) == 1) {
      if (in6.size(0) == 1) {
        b_in1_tmp = in4.size(0);
      } else {
        b_in1_tmp = in6.size(0);
      }
    } else {
      b_in1_tmp = in7.size(0);
    }
  } else if (in1_tmp == 1) {
    b_in1_tmp = i;
  } else {
    b_in1_tmp = in1_tmp;
  }

  if (in1_tmp == 1) {
    c_in1_tmp = i;
  } else {
    c_in1_tmp = in1_tmp;
  }

  if (in7.size(0) == 1) {
    if (in6.size(0) == 1) {
      i1 = in4.size(0);
    } else {
      i1 = in6.size(0);
    }
  } else {
    i1 = in7.size(0);
  }

  if (b_in1_tmp == 1) {
    b_in1_tmp = b_in1 + 1;
  } else if (c_in1_tmp == 1) {
    if (i1 == 1) {
      b_in1_tmp = in3.size(0);
    } else if (in7.size(0) == 1) {
      if (in6.size(0) == 1) {
        b_in1_tmp = in4.size(0);
      } else {
        b_in1_tmp = in6.size(0);
      }
    } else {
      b_in1_tmp = in7.size(0);
    }
  } else if (in1_tmp == 1) {
    b_in1_tmp = i;
  } else {
    b_in1_tmp = in1_tmp;
  }

  c_in1.set_size(b_in1_tmp);
  c_in1_tmp = (b_in1 + 1 != 1);
  stride_1_0 = (in3.size(0) != 1);
  stride_2_0 = (in4.size(0) != 1);
  stride_3_0 = (in6.size(0) != 1);
  stride_4_0 = (in7.size(0) != 1);
  stride_5_0 = (i != 1);
  stride_6_0 = (in1_tmp != 1);
  if (in1_tmp == 1) {
    b_in1_tmp = i;
  } else {
    b_in1_tmp = in1_tmp;
  }

  if (in7.size(0) == 1) {
    if (in6.size(0) == 1) {
      i1 = in4.size(0);
    } else {
      i1 = in6.size(0);
    }
  } else {
    i1 = in7.size(0);
  }

  if (b_in1_tmp == 1) {
    if (i1 == 1) {
      b_in1_tmp = in3.size(0);
    } else if (in7.size(0) == 1) {
      if (in6.size(0) == 1) {
        b_in1_tmp = in4.size(0);
      } else {
        b_in1_tmp = in6.size(0);
      }
    } else {
      b_in1_tmp = in7.size(0);
    }
  } else if (in1_tmp == 1) {
    b_in1_tmp = i;
  } else {
    b_in1_tmp = in1_tmp;
  }

  if (b_in1_tmp == 1) {
    b_in1++;
  } else {
    if (in1_tmp == 1) {
      b_in1_tmp = i;
    } else {
      b_in1_tmp = in1_tmp;
    }

    if (b_in1_tmp == 1) {
      if (in7.size(0) == 1) {
        if (in6.size(0) == 1) {
          i = in4.size(0);
        } else {
          i = in6.size(0);
        }
      } else {
        i = in7.size(0);
      }

      if (i == 1) {
        b_in1 = in3.size(0);
      } else if (in7.size(0) == 1) {
        if (in6.size(0) == 1) {
          b_in1 = in4.size(0);
        } else {
          b_in1 = in6.size(0);
        }
      } else {
        b_in1 = in7.size(0);
      }
    } else if (in1_tmp == 1) {
      b_in1 = i;
    } else {
      b_in1 = in1_tmp;
    }
  }

  for (i = 0; i < b_in1; i++) {
    double d_in1_tmp;
    in1_tmp = i * c_in1_tmp;
    in8_tmp = in8[i * stride_5_0 + in8.size(0) * in9];
    d_in1_tmp = in8[i * stride_6_0 + in8.size(0) * in9];
    c_in1[i] = (in1[in1_tmp + in1.size(0) * (static_cast<int>(in2) - 1)] ||
                in1[in1_tmp + in1.size(0) * static_cast<int>(in2)] || (in3[i *
      stride_1_0] || ((in4[i * stride_2_0] <= in5) || (in6[i * stride_3_0] <=
      in5) || (in7[i * stride_4_0] <= in5)) || (((in8_tmp < b_in8) && (in8_tmp >
      c_in8)) || ((d_in1_tmp > d_in8) && (d_in1_tmp < in8_tmp_tmp)))));
  }

  b_in1 = c_in1.size(0);
  for (i = 0; i < b_in1; i++) {
    in1[i + in1.size(0) * static_cast<int>(in2)] = c_in1[i];
  }
}

static void e_binary_expand_op(coder::array<double, 1U> &in1, const coder::array<
  double, 1U> &in2, const coder::array<boolean_T, 2U> &in3, unsigned int in4,
  const coder::array<boolean_T, 1U> &in5)
{
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  int stride_2_0;
  i = in3.size(0);
  if (in5.size(0) == 1) {
    if (i == 1) {
      stride_0_0 = in2.size(0);
    } else {
      stride_0_0 = i;
    }
  } else {
    stride_0_0 = in5.size(0);
  }

  in1.set_size(stride_0_0);
  stride_0_0 = (in2.size(0) != 1);
  stride_1_0 = (i != 1);
  stride_2_0 = (in5.size(0) != 1);
  if (in5.size(0) == 1) {
    if (i == 1) {
      loop_ub = in2.size(0);
    } else {
      loop_ub = i;
    }
  } else {
    loop_ub = in5.size(0);
  }

  for (i = 0; i < loop_ub; i++) {
    in1[i] = in2[i * stride_0_0] * static_cast<double>(!in3[i * stride_1_0 +
      in3.size(0) * static_cast<int>(in4)]) * static_cast<double>(in5[i *
      stride_2_0]);
  }
}

static void f_binary_expand_op(coder::array<double, 1U> &in1, const coder::array<
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

static void g_binary_expand_op(coder::array<boolean_T, 1U> &in1, const coder::
  array<boolean_T, 1U> &in2, const coder::array<boolean_T, 1U> &in3, const coder::
  array<boolean_T, 1U> &in4, const coder::array<boolean_T, 1U> &in5, const coder::
  array<boolean_T, 1U> &in6, const coder::array<boolean_T, 1U> &in7, const coder::
  array<boolean_T, 1U> &in8, const coder::array<boolean_T, 1U> &in9)
{
  coder::array<boolean_T, 1U> b_in4;
  coder::array<boolean_T, 1U> b_in7;
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  int stride_2_0;
  int stride_3_0;
  int stride_4_0;
  int stride_5_0;
  int stride_6_0;
  int stride_7_0;
  if (in5.size(0) == 1) {
    i = in4.size(0);
  } else {
    i = in5.size(0);
  }

  b_in4.set_size(i);
  stride_0_0 = (in4.size(0) != 1);
  stride_1_0 = (in5.size(0) != 1);
  if (in5.size(0) == 1) {
    loop_ub = in4.size(0);
  } else {
    loop_ub = in5.size(0);
  }

  for (i = 0; i < loop_ub; i++) {
    b_in4[i] = ((!in4[i * stride_0_0]) && in5[i * stride_1_0]);
  }

  in1.set_size(b_in4.size(0) + 1);
  in1[0] = true;
  loop_ub = b_in4.size(0);
  for (i = 0; i < loop_ub; i++) {
    in1[i + 1] = b_in4[i];
  }

  if (in8.size(0) == 1) {
    i = in7.size(0);
  } else {
    i = in8.size(0);
  }

  b_in4.set_size(i);
  stride_0_0 = (in7.size(0) != 1);
  stride_1_0 = (in8.size(0) != 1);
  if (in8.size(0) == 1) {
    loop_ub = in7.size(0);
  } else {
    loop_ub = in8.size(0);
  }

  for (i = 0; i < loop_ub; i++) {
    b_in4[i] = ((!in7[i * stride_0_0]) && in8[i * stride_1_0]);
  }

  b_in7.set_size(b_in4.size(0) + 1);
  loop_ub = b_in4.size(0);
  for (i = 0; i < loop_ub; i++) {
    b_in7[i] = b_in4[i];
  }

  b_in7[b_in4.size(0)] = true;
  if (in3.size(0) == 1) {
    i = in9.size(0);
  } else {
    i = in3.size(0);
  }

  if (i == 1) {
    i = b_in7.size(0);
  } else if (in3.size(0) == 1) {
    i = in9.size(0);
  } else {
    i = in3.size(0);
  }

  if (in6.size(0) == 1) {
    stride_0_0 = in2.size(0);
  } else {
    stride_0_0 = in6.size(0);
  }

  if (stride_0_0 == 1) {
    stride_0_0 = in1.size(0);
  } else if (in6.size(0) == 1) {
    stride_0_0 = in2.size(0);
  } else {
    stride_0_0 = in6.size(0);
  }

  if (in6.size(0) == 1) {
    stride_1_0 = in2.size(0);
  } else {
    stride_1_0 = in6.size(0);
  }

  if (in3.size(0) == 1) {
    loop_ub = in9.size(0);
  } else {
    loop_ub = in3.size(0);
  }

  if (i == 1) {
    if (stride_0_0 == 1) {
      if (in3.size(0) == 1) {
        i = in2.size(0);
      } else {
        i = in3.size(0);
      }
    } else if (stride_1_0 == 1) {
      i = in1.size(0);
    } else if (in6.size(0) == 1) {
      i = in2.size(0);
    } else {
      i = in6.size(0);
    }
  } else if (loop_ub == 1) {
    i = b_in7.size(0);
  } else if (in3.size(0) == 1) {
    i = in9.size(0);
  } else {
    i = in3.size(0);
  }

  b_in4.set_size(i);
  stride_0_0 = (in2.size(0) != 1);
  stride_1_0 = (in3.size(0) != 1);
  stride_2_0 = (in1.size(0) != 1);
  stride_3_0 = (in2.size(0) != 1);
  stride_4_0 = (in6.size(0) != 1);
  stride_5_0 = (b_in7.size(0) != 1);
  stride_6_0 = (in9.size(0) != 1);
  stride_7_0 = (in3.size(0) != 1);
  if (in3.size(0) == 1) {
    i = in9.size(0);
  } else {
    i = in3.size(0);
  }

  if (i == 1) {
    i = b_in7.size(0);
  } else if (in3.size(0) == 1) {
    i = in9.size(0);
  } else {
    i = in3.size(0);
  }

  if (i == 1) {
    if (in6.size(0) == 1) {
      i = in2.size(0);
    } else {
      i = in6.size(0);
    }

    if (i == 1) {
      i = in1.size(0);
    } else if (in6.size(0) == 1) {
      i = in2.size(0);
    } else {
      i = in6.size(0);
    }

    if (i == 1) {
      if (in3.size(0) == 1) {
        loop_ub = in2.size(0);
      } else {
        loop_ub = in3.size(0);
      }
    } else {
      if (in6.size(0) == 1) {
        i = in2.size(0);
      } else {
        i = in6.size(0);
      }

      if (i == 1) {
        loop_ub = in1.size(0);
      } else if (in6.size(0) == 1) {
        loop_ub = in2.size(0);
      } else {
        loop_ub = in6.size(0);
      }
    }
  } else {
    if (in3.size(0) == 1) {
      i = in9.size(0);
    } else {
      i = in3.size(0);
    }

    if (i == 1) {
      loop_ub = b_in7.size(0);
    } else if (in3.size(0) == 1) {
      loop_ub = in9.size(0);
    } else {
      loop_ub = in3.size(0);
    }
  }

  for (i = 0; i < loop_ub; i++) {
    b_in4[i] = ((in2[i * stride_0_0] && in3[i * stride_1_0]) || (in1[i *
      stride_2_0] && (in2[i * stride_3_0] && in6[i * stride_4_0])) || (b_in7[i *
      stride_5_0] && (in9[i * stride_6_0] && in3[i * stride_7_0])));
  }

  in1.set_size(b_in4.size(0));
  loop_ub = b_in4.size(0);
  for (i = 0; i < loop_ub; i++) {
    in1[i] = b_in4[i];
  }
}

static void h_binary_expand_op(coder::array<boolean_T, 1U> &in1, const coder::
  array<double, 1U> &in2, int in3, int in4)
{
  coder::array<double, 1U> r;
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  r.set_size(in4 + 2);
  r[0] = 0.0;
  for (i = 0; i <= in4; i++) {
    r[i + 1] = in2[i];
  }

  if (r.size(0) == 1) {
    i = in3 + 1;
  } else {
    i = r.size(0);
  }

  in1.set_size(i);
  stride_0_0 = (in3 + 1 != 1);
  stride_1_0 = (r.size(0) != 1);
  if (r.size(0) == 1) {
    loop_ub = in3 + 1;
  } else {
    loop_ub = r.size(0);
  }

  for (i = 0; i < loop_ub; i++) {
    in1[i] = (in2[i * stride_0_0] > r[i * stride_1_0]);
  }
}

static void i_binary_expand_op(coder::array<boolean_T, 1U> &in1, const coder::
  array<double, 1U> &in2, int in3, int in4, int in5)
{
  coder::array<double, 1U> b_in2;
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  loop_ub = in5 - in4;
  b_in2.set_size(loop_ub + 2);
  for (i = 0; i <= loop_ub; i++) {
    b_in2[i] = in2[in4 + i];
  }

  b_in2[loop_ub + 1] = 0.0;
  if (b_in2.size(0) == 1) {
    i = in3 + 1;
  } else {
    i = b_in2.size(0);
  }

  in1.set_size(i);
  stride_0_0 = (in3 + 1 != 1);
  stride_1_0 = (b_in2.size(0) != 1);
  if (b_in2.size(0) == 1) {
    loop_ub = in3 + 1;
  } else {
    loop_ub = b_in2.size(0);
  }

  for (i = 0; i < loop_ub; i++) {
    in1[i] = (in2[i * stride_0_0] > b_in2[i * stride_1_0]);
  }
}

static void j_binary_expand_op(coder::array<boolean_T, 1U> &in1, const coder::
  array<double, 2U> &in2, const coder::array<double, 2U> &in3, const coder::
  array<double, 2U> &in4, const coder::array<double, 2U> &in5)
{
  coder::array<boolean_T, 2U> b_in2;
  int aux_0_1;
  int aux_1_1;
  int aux_2_1;
  int aux_3_1;
  int i;
  int i1;
  int loop_ub;
  int stride_0_0;
  int stride_0_1;
  int stride_1_0;
  int stride_1_1;
  int stride_2_0;
  int stride_2_1;
  int stride_3_0;
  int stride_3_1;
  if (in5.size(0) == 1) {
    i = in4.size(0);
  } else {
    i = in5.size(0);
  }

  if (i == 1) {
    if (in3.size(0) == 1) {
      i = in2.size(0);
    } else {
      i = in3.size(0);
    }
  } else if (in5.size(0) == 1) {
    i = in4.size(0);
  } else {
    i = in5.size(0);
  }

  if (in5.size(1) == 1) {
    i1 = in4.size(1);
  } else {
    i1 = in5.size(1);
  }

  if (i1 == 1) {
    if (in3.size(1) == 1) {
      i1 = in2.size(1);
    } else {
      i1 = in3.size(1);
    }
  } else if (in5.size(1) == 1) {
    i1 = in4.size(1);
  } else {
    i1 = in5.size(1);
  }

  b_in2.set_size(i, i1);
  stride_0_0 = (in2.size(0) != 1);
  stride_0_1 = (in2.size(1) != 1);
  stride_1_0 = (in3.size(0) != 1);
  stride_1_1 = (in3.size(1) != 1);
  stride_2_0 = (in4.size(0) != 1);
  stride_2_1 = (in4.size(1) != 1);
  stride_3_0 = (in5.size(0) != 1);
  stride_3_1 = (in5.size(1) != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  aux_2_1 = 0;
  aux_3_1 = 0;
  if (in5.size(1) == 1) {
    i = in4.size(1);
  } else {
    i = in5.size(1);
  }

  if (i == 1) {
    if (in3.size(1) == 1) {
      loop_ub = in2.size(1);
    } else {
      loop_ub = in3.size(1);
    }
  } else if (in5.size(1) == 1) {
    loop_ub = in4.size(1);
  } else {
    loop_ub = in5.size(1);
  }

  for (i = 0; i < loop_ub; i++) {
    int b_loop_ub;
    if (in5.size(0) == 1) {
      i1 = in4.size(0);
    } else {
      i1 = in5.size(0);
    }

    if (i1 == 1) {
      if (in3.size(0) == 1) {
        b_loop_ub = in2.size(0);
      } else {
        b_loop_ub = in3.size(0);
      }
    } else if (in5.size(0) == 1) {
      b_loop_ub = in4.size(0);
    } else {
      b_loop_ub = in5.size(0);
    }

    for (i1 = 0; i1 < b_loop_ub; i1++) {
      b_in2[i1 + b_in2.size(0) * i] = ((!(in2[i1 * stride_0_0 + in2.size(0) *
        aux_0_1] >= in3[i1 * stride_1_0 + in3.size(0) * aux_1_1])) || (!(in4[i1 *
        stride_2_0 + in4.size(0) * aux_2_1] <= in5[i1 * stride_3_0 + in5.size(0)
        * aux_3_1])));
    }

    aux_3_1 += stride_3_1;
    aux_2_1 += stride_2_1;
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }

  coder::all(b_in2, in1);
}

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

  // WAVEFORM Constructs an instance of this class
  // INPUTS:
  //    x       1xn     Vector of samples
  //    Fs      1x1     Sample frequency (Hz)
  //    t_0     1x1     Time stamp of first element (s)
  // 	ps_pre  1x1     Pulse stats object from previous data (priori)
  //    OLF     1x1     Overlap fraction as decimal (0.5 = 50%
  //                    overlap)
  // OUTPUTS:
  //    obj             The waveform object
  //             %%
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
  coder::array<creal32_T, 2U> r;
  coder::array<creal32_T, 2U> val;
  coder::array<double, 2U> f_ps_pre;
  coder::array<double, 1U> b_tmp_data;
  coder::array<double, 1U> c_val;
  coder::array<boolean_T, 2U> e_ps_pre;
  double tmp_data[400];
  int loop_ub;
  obj = this;

  // WAVEFORM Constructs an instance of this class
  // INPUTS:
  //    x       1xn     Vector of samples
  //    Fs      1x1     Sample frequency (Hz)
  //    t_0     1x1     Time stamp of first element (s)
  // 	ps_pre  1x1     Pulse stats object from previous data (priori)
  //    OLF     1x1     Overlap fraction as decimal (0.5 = 50%
  //                    overlap)
  // OUTPUTS:
  //    obj             The waveform object
  //             %%
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

  coder::array<creal32_T, 2U> c_x;

  // Flatten input to row
  loop_ub = b_x.size(0);
  c_x = b_x.reshape(1, loop_ub);
  coder::internal::validator_check_size(c_x, val);
  obj->x.set_size(1, val.size(1));
  loop_ub = val.size(1);
  for (int i{0}; i < loop_ub; i++) {
    obj->x[i] = val[i];
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

  // WAVEFORM Constructs an instance of this class
  // INPUTS:
  //    x       1xn     Vector of samples
  //    Fs      1x1     Sample frequency (Hz)
  //    t_0     1x1     Time stamp of first element (s)
  // 	ps_pre  1x1     Pulse stats object from previous data (priori)
  //    OLF     1x1     Overlap fraction as decimal (0.5 = 50%
  //                    overlap)
  // OUTPUTS:
  //    obj             The waveform object
  //             %%
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

void waveform::process(char mode, const coder::array<double, 2U>
  &excluded_freq_bands)
{
  static const char b_cv[8]{ 'i', 'n', 'f', 'o', 'r', 'm', 'e', 'd' };

  static const char cv3[7]{ 'c', 'o', 'n', 'f', 'i', 'r', 'm' };

  static const char b_cv2[6]{ 's', 'e', 'a', 'r', 'c', 'h' };

  static const char b_cv1[5]{ 'n', 'a', 'i', 'v', 'e' };

  static const char cv4[5]{ 't', 'r', 'a', 'c', 'k' };

  coder::array<c_struct_T, 2U> *structure;
  pulsestats *obj;
  coder::array<c_struct_T, 2U> b_candidatelist;
  coder::array<c_struct_T, 2U> b_val;
  coder::array<c_struct_T, 2U> c_candidatelist;
  coder::array<c_struct_T, 2U> candidatelist;
  coder::array<c_struct_T, 1U> b_obj;
  coder::array<double, 2U> _in;
  coder::array<double, 2U> b;
  coder::array<double, 2U> b_varargin_1;
  coder::array<double, 2U> c_varargin_1;
  coder::array<double, 2U> d_varargin_1;
  coder::array<double, 2U> e_varargin_1;
  coder::array<double, 2U> pulseendtimes_withuncert;
  coder::array<double, 2U> pulsestarttimes_withuncert;
  coder::array<double, 2U> varargin_1;
  coder::array<double, 1U> pk_ind;
  coder::array<boolean_T, 2U> b_conflog;
  coder::array<boolean_T, 2U> b_msk;
  coder::array<boolean_T, 2U> msk;
  coder::array<boolean_T, 1U> conflog;
  c_struct_T val;
  double b_x;
  double tip;
  double tipj;
  double tipu;
  double tref;
  int c_input_sizes[2];
  int d_input_sizes[2];
  int e_input_sizes[2];
  int f_input_sizes[2];
  int freq_search_type_size[2];
  int g_input_sizes[2];
  int h_input_sizes[2];
  int runmode_size[2];
  int time_search_type_size[2];
  int input_sizes;
  int n;
  char freq_search_type_data[8];
  char time_search_type_data[8];
  char runmode_data[7];
  boolean_T have_priori_freq_band;
  boolean_T have_priori_time;

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
  b_x = ps_pre->pl[ps_pre->pl.size(1) - 1].t_0;
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
    n = 0;
  } else if (mode == 'I') {
    n = 1;
  } else if (mode == 'C') {
    n = 2;
  } else if (mode == 'T') {
    n = 3;
  } else {
    n = -1;
  }

  switch (n) {
   case 0:
    {
      freq_search_type_size[0] = 1;
      freq_search_type_size[1] = 5;
      time_search_type_size[0] = 1;
      time_search_type_size[1] = 5;
      for (input_sizes = 0; input_sizes < 5; input_sizes++) {
        char c;
        c = b_cv1[input_sizes];
        freq_search_type_data[input_sizes] = c;
        time_search_type_data[input_sizes] = c;
      }

      runmode_size[0] = 1;
      runmode_size[1] = 6;
      for (input_sizes = 0; input_sizes < 6; input_sizes++) {
        runmode_data[input_sizes] = b_cv2[input_sizes];
      }
    }
    break;

   case 1:
    freq_search_type_size[0] = 1;
    freq_search_type_size[1] = 8;
    for (input_sizes = 0; input_sizes < 8; input_sizes++) {
      freq_search_type_data[input_sizes] = b_cv[input_sizes];
    }

    time_search_type_size[0] = 1;
    time_search_type_size[1] = 5;
    for (input_sizes = 0; input_sizes < 5; input_sizes++) {
      time_search_type_data[input_sizes] = b_cv1[input_sizes];
    }

    runmode_size[0] = 1;
    runmode_size[1] = 6;
    for (input_sizes = 0; input_sizes < 6; input_sizes++) {
      runmode_data[input_sizes] = b_cv2[input_sizes];
    }
    break;

   case 2:
    {
      freq_search_type_size[0] = 1;
      freq_search_type_size[1] = 5;
      time_search_type_size[0] = 1;
      time_search_type_size[1] = 5;
      for (input_sizes = 0; input_sizes < 5; input_sizes++) {
        char c;
        c = b_cv1[input_sizes];
        freq_search_type_data[input_sizes] = c;
        time_search_type_data[input_sizes] = c;
      }

      runmode_size[0] = 1;
      runmode_size[1] = 7;
      for (input_sizes = 0; input_sizes < 7; input_sizes++) {
        runmode_data[input_sizes] = cv3[input_sizes];
      }
    }
    break;

   case 3:
    {
      freq_search_type_size[0] = 1;
      freq_search_type_size[1] = 8;
      time_search_type_size[0] = 1;
      time_search_type_size[1] = 8;
      for (input_sizes = 0; input_sizes < 8; input_sizes++) {
        char c;
        c = b_cv[input_sizes];
        freq_search_type_data[input_sizes] = c;
        time_search_type_data[input_sizes] = c;
      }

      runmode_size[0] = 1;
      runmode_size[1] = 5;
      for (input_sizes = 0; input_sizes < 5; input_sizes++) {
        runmode_data[input_sizes] = cv4[input_sizes];
      }
    }
    break;

   default:
    {
      freq_search_type_size[0] = 1;
      freq_search_type_size[1] = 5;
      time_search_type_size[0] = 1;
      time_search_type_size[1] = 5;
      for (input_sizes = 0; input_sizes < 5; input_sizes++) {
        char c;
        c = b_cv1[input_sizes];
        freq_search_type_data[input_sizes] = c;
        time_search_type_data[input_sizes] = c;
      }

      runmode_size[0] = 1;
      runmode_size[1] = 6;
      for (input_sizes = 0; input_sizes < 6; input_sizes++) {
        runmode_data[input_sizes] = b_cv2[input_sizes];
      }
    }
    break;
  }

  if (coder::internal::b_strcmp(runmode_data, runmode_size)) {
    n = 0;
  } else if (coder::internal::c_strcmp(runmode_data, runmode_size)) {
    n = 1;
  } else if (coder::internal::d_strcmp(runmode_data, runmode_size)) {
    n = 2;
  } else {
    n = -1;
  }

  switch (n) {
   case 0:
    //             %% SEARCH RUN MODE
    // Find all the potential pulses in the dataset
    findpulse(time_search_type_data, time_search_type_size,
              freq_search_type_data, freq_search_type_size, excluded_freq_bands,
              candidatelist, msk, pk_ind);
    conflog.set_size(pk_ind.size(0));
    n = pk_ind.size(0);
    for (input_sizes = 0; input_sizes < n; input_sizes++) {
      conflog[input_sizes] = std::isnan(pk_ind[input_sizes]);
    }

    n = conflog.size(0);
    for (input_sizes = 0; input_sizes < n; input_sizes++) {
      conflog[input_sizes] = !conflog[input_sizes];
    }

    if (coder::internal::ifWhileCond(conflog)) {
      // Set the pulselist property in the ps_pos based on the
      // downselection of pulses
      obj = ps_pos;
      n = candidatelist.size(1);
      b_candidatelist.set_size(1, candidatelist.size(1));
      for (input_sizes = 0; input_sizes < n; input_sizes++) {
        b_candidatelist[input_sizes] = candidatelist[(static_cast<int>(pk_ind[0])
          + candidatelist.size(0) * input_sizes) - 1];
      }

      coder::internal::validator_check_size(b_candidatelist, b_val);
      obj->pl.set_size(1, b_val.size(1));
      n = b_val.size(1);
      for (input_sizes = 0; input_sizes < n; input_sizes++) {
        obj->pl[input_sizes] = b_val[input_sizes];
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
    c_candidatelist.set_size(candidatelist.size(0), candidatelist.size(1));
    n = candidatelist.size(0) * candidatelist.size(1) - 1;
    for (input_sizes = 0; input_sizes <= n; input_sizes++) {
      c_candidatelist[input_sizes] = candidatelist[input_sizes];
    }

    coder::internal::c_validator_check_size(c_candidatelist, candidatelist);
    obj->clst.set_size(candidatelist.size(0), candidatelist.size(1));
    n = candidatelist.size(0) * candidatelist.size(1);
    for (input_sizes = 0; input_sizes < n; input_sizes++) {
      obj->clst[input_sizes] = candidatelist[input_sizes];
    }

    obj = ps_pos;
    b_msk.set_size(msk.size(0), msk.size(1));
    n = msk.size(0) * msk.size(1) - 1;
    for (input_sizes = 0; input_sizes <= n; input_sizes++) {
      b_msk[input_sizes] = msk[input_sizes];
    }

    coder::internal::d_validator_check_size(b_msk, msk);
    obj->cmsk.set_size(msk.size(0), msk.size(1));
    n = msk.size(0) * msk.size(1);
    for (input_sizes = 0; input_sizes < n; input_sizes++) {
      obj->cmsk[input_sizes] = msk[input_sizes];
    }

    obj = ps_pos;
    coder::internal::validator_check_size(pk_ind, _in);
    obj->cpki.set_size(_in.size(0), _in.size(1));
    n = _in.size(0) * _in.size(1);
    for (input_sizes = 0; input_sizes < n; input_sizes++) {
      obj->cpki[input_sizes] = _in[input_sizes];
    }

    //  Detection?
    if (coder::internal::ifWhileCond(conflog)) {
      // Dection was made
      // True ->
      // Update confirmation property for each pulse. False
      // recorded for confirmation property since we are
      // currently in discovery mode and can't confirm anything
      // yet.
      input_sizes = ps_pos->pl.size(1) - 1;
      for (int ip{0}; ip <= input_sizes; ip++) {
        b_val.set_size(1, ps_pos->pl.size(1));
        n = ps_pos->pl.size(1);
        for (int b_input_sizes{0}; b_input_sizes < n; b_input_sizes++) {
          b_val[b_input_sizes] = ps_pos->pl[b_input_sizes];
        }

        b_val[ip].con_dec = false;
        obj = ps_pos;
        b_candidatelist.set_size(1, b_val.size(1));
        n = b_val.size(0) * b_val.size(1) - 1;
        for (int b_input_sizes{0}; b_input_sizes <= n; b_input_sizes++) {
          b_candidatelist[b_input_sizes] = b_val[b_input_sizes];
        }

        coder::internal::validator_check_size(b_candidatelist, b_val);
        obj->pl.set_size(1, b_val.size(1));
        n = b_val.size(1);
        for (int b_input_sizes{0}; b_input_sizes < n; b_input_sizes++) {
          obj->pl[b_input_sizes] = b_val[b_input_sizes];
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
    input_sizes = ps_pos->pl.size(1) - 1;
    for (int ip{0}; ip <= input_sizes; ip++) {
      b_val.set_size(1, ps_pos->pl.size(1));
      n = ps_pos->pl.size(1);
      for (int b_input_sizes{0}; b_input_sizes < n; b_input_sizes++) {
        b_val[b_input_sizes] = ps_pos->pl[b_input_sizes];
      }

      b_val[b_val.size(0) * ip].mode.set_size(1, 1);
      b_val[ip].mode[0] = mode;
      obj = ps_pos;
      b_candidatelist.set_size(1, b_val.size(1));
      n = b_val.size(0) * b_val.size(1) - 1;
      for (int b_input_sizes{0}; b_input_sizes <= n; b_input_sizes++) {
        b_candidatelist[b_input_sizes] = b_val[b_input_sizes];
      }

      coder::internal::validator_check_size(b_candidatelist, b_val);
      obj->pl.set_size(1, b_val.size(1));
      n = b_val.size(1);
      for (int b_input_sizes{0}; b_input_sizes < n; b_input_sizes++) {
        obj->pl[b_input_sizes] = b_val[b_input_sizes];
      }

      // 'D';
    }

    input_sizes = ps_pos->clst.size(0) * ps_pos->clst.size(1) - 1;
    for (int ip{0}; ip <= input_sizes; ip++) {
      candidatelist.set_size(ps_pos->clst.size(0), ps_pos->clst.size(1));
      n = ps_pos->clst.size(0) * ps_pos->clst.size(1);
      for (int b_input_sizes{0}; b_input_sizes < n; b_input_sizes++) {
        candidatelist[b_input_sizes] = ps_pos->clst[b_input_sizes];
      }

      candidatelist[ip].mode.set_size(1, 1);
      candidatelist[ip].mode[0] = mode;
      obj = ps_pos;
      c_candidatelist.set_size(candidatelist.size(0), candidatelist.size(1));
      n = candidatelist.size(0) * candidatelist.size(1) - 1;
      for (int b_input_sizes{0}; b_input_sizes <= n; b_input_sizes++) {
        c_candidatelist[b_input_sizes] = candidatelist[b_input_sizes];
      }

      coder::internal::c_validator_check_size(c_candidatelist, candidatelist);
      obj->clst.set_size(candidatelist.size(0), candidatelist.size(1));
      n = candidatelist.size(0) * candidatelist.size(1);
      for (int b_input_sizes{0}; b_input_sizes < n; b_input_sizes++) {
        obj->clst[b_input_sizes] = candidatelist[b_input_sizes];
      }

      //  'D';
    }

    //             %% CONFIRMATION MODE
    break;

   case 1:
    {
      int b_input_sizes;
      int ip;

      // Find all the potential pulses in the dataset
      findpulse(time_search_type_data, time_search_type_size,
                freq_search_type_data, freq_search_type_size,
                excluded_freq_bands, candidatelist, msk, pk_ind);
      conflog.set_size(pk_ind.size(0));
      n = pk_ind.size(0);
      for (input_sizes = 0; input_sizes < n; input_sizes++) {
        conflog[input_sizes] = std::isnan(pk_ind[input_sizes]);
      }

      n = conflog.size(0);
      for (input_sizes = 0; input_sizes < n; input_sizes++) {
        conflog[input_sizes] = !conflog[input_sizes];
      }

      if (coder::internal::ifWhileCond(conflog)) {
        // Record the detection pulses
        // We only use the highest power pulse group for now
        // because if we are in confirmation mode, we only allow
        // for the selection mode to be 'most'
        obj = ps_pos;
        n = candidatelist.size(1);
        b_candidatelist.set_size(1, candidatelist.size(1));
        for (input_sizes = 0; input_sizes < n; input_sizes++) {
          b_candidatelist[input_sizes] = candidatelist[(static_cast<int>(pk_ind
            [0]) + candidatelist.size(0) * input_sizes) - 1];
        }

        coder::internal::validator_check_size(b_candidatelist, b_val);
        obj->pl.set_size(1, b_val.size(1));
        n = b_val.size(1);
        for (input_sizes = 0; input_sizes < n; input_sizes++) {
          obj->pl[input_sizes] = b_val[input_sizes];
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
      c_candidatelist.set_size(candidatelist.size(0), candidatelist.size(1));
      n = candidatelist.size(0) * candidatelist.size(1) - 1;
      for (input_sizes = 0; input_sizes <= n; input_sizes++) {
        c_candidatelist[input_sizes] = candidatelist[input_sizes];
      }

      coder::internal::c_validator_check_size(c_candidatelist, candidatelist);
      obj->clst.set_size(candidatelist.size(0), candidatelist.size(1));
      n = candidatelist.size(0) * candidatelist.size(1);
      for (input_sizes = 0; input_sizes < n; input_sizes++) {
        obj->clst[input_sizes] = candidatelist[input_sizes];
      }

      obj = ps_pos;
      b_msk.set_size(msk.size(0), msk.size(1));
      n = msk.size(0) * msk.size(1) - 1;
      for (input_sizes = 0; input_sizes <= n; input_sizes++) {
        b_msk[input_sizes] = msk[input_sizes];
      }

      coder::internal::d_validator_check_size(b_msk, msk);
      obj->cmsk.set_size(msk.size(0), msk.size(1));
      n = msk.size(0) * msk.size(1);
      for (input_sizes = 0; input_sizes < n; input_sizes++) {
        obj->cmsk[input_sizes] = msk[input_sizes];
      }

      obj = ps_pos;
      coder::internal::validator_check_size(pk_ind, _in);
      obj->cpki.set_size(_in.size(0), _in.size(1));
      n = _in.size(0) * _in.size(1);
      for (input_sizes = 0; input_sizes < n; input_sizes++) {
        obj->cpki[input_sizes] = _in[input_sizes];
      }

      b_conflog.set_size(1, 1);
      b_conflog[0] = false;

      // Set to all false. Needed
      //  Detection?
      if (coder::internal::ifWhileCond(conflog)) {
        int i_input_sizes;
        int j_input_sizes;
        boolean_T exitg1;

        // ~isempty(pulselist)%obj.decide(pulselist,PF,decision_table) %Decision on IDed pulses
        // True ->
        tref = ps_pre->pl[ps_pre->pl.size(1) - 1].t_0;
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
            n = static_cast<int>(b_x);
            for (input_sizes = 0; input_sizes <= n; input_sizes++) {
              pulseendtimes_withuncert[input_sizes] = input_sizes;
            }
          }

          b_x = tip - tipu;
          pulsestarttimes_withuncert.set_size(1, static_cast<int>(K));
          n = static_cast<int>(K);
          for (input_sizes = 0; input_sizes < n; input_sizes++) {
            pulsestarttimes_withuncert[input_sizes] = 1.0;
          }

          if (pulseendtimes_withuncert.size(1) ==
              pulsestarttimes_withuncert.size(1)) {
            n = pulseendtimes_withuncert.size(1) - 1;
            pulsestarttimes_withuncert.set_size(1, pulseendtimes_withuncert.size
              (1));
            for (input_sizes = 0; input_sizes <= n; input_sizes++) {
              pulsestarttimes_withuncert[input_sizes] = (tref + b_x *
                pulseendtimes_withuncert[input_sizes]) - tipj *
                pulsestarttimes_withuncert[input_sizes];
            }
          } else {
            b_binary_expand_op(pulsestarttimes_withuncert, tref, b_x,
                               pulseendtimes_withuncert, tipj);
          }

          b_x = tip + tipu;
          b.set_size(1, static_cast<int>(K));
          n = static_cast<int>(K);
          for (input_sizes = 0; input_sizes < n; input_sizes++) {
            b[input_sizes] = 1.0;
          }

          if (pulseendtimes_withuncert.size(1) == b.size(1)) {
            n = pulseendtimes_withuncert.size(1) - 1;
            pulseendtimes_withuncert.set_size(1, pulseendtimes_withuncert.size(1));
            for (input_sizes = 0; input_sizes <= n; input_sizes++) {
              pulseendtimes_withuncert[input_sizes] = (tref + b_x *
                pulseendtimes_withuncert[input_sizes]) + tipj;
            }
          } else {
            b_binary_expand_op(pulseendtimes_withuncert, tref, b_x, tipj, b);
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
            n = static_cast<int>(b_x - 1.0);
            for (input_sizes = 0; input_sizes <= n; input_sizes++) {
              pulseendtimes_withuncert[input_sizes] = static_cast<double>
                (input_sizes) + 1.0;
            }
          }

          b_x = tip - tipu;
          pulsestarttimes_withuncert.set_size(1, static_cast<int>(K));
          n = static_cast<int>(K);
          for (input_sizes = 0; input_sizes < n; input_sizes++) {
            pulsestarttimes_withuncert[input_sizes] = 1.0;
          }

          if (pulseendtimes_withuncert.size(1) ==
              pulsestarttimes_withuncert.size(1)) {
            n = pulseendtimes_withuncert.size(1) - 1;
            pulsestarttimes_withuncert.set_size(1, pulseendtimes_withuncert.size
              (1));
            for (input_sizes = 0; input_sizes <= n; input_sizes++) {
              pulsestarttimes_withuncert[input_sizes] = (tref + b_x *
                pulseendtimes_withuncert[input_sizes]) - tipj *
                pulsestarttimes_withuncert[input_sizes];
            }
          } else {
            b_binary_expand_op(pulsestarttimes_withuncert, tref, b_x,
                               pulseendtimes_withuncert, tipj);
          }

          b_x = tip + tipu;
          b.set_size(1, static_cast<int>(K));
          n = static_cast<int>(K);
          for (input_sizes = 0; input_sizes < n; input_sizes++) {
            b[input_sizes] = 1.0;
          }

          if (pulseendtimes_withuncert.size(1) == b.size(1)) {
            n = pulseendtimes_withuncert.size(1) - 1;
            pulseendtimes_withuncert.set_size(1, pulseendtimes_withuncert.size(1));
            for (input_sizes = 0; input_sizes <= n; input_sizes++) {
              pulseendtimes_withuncert[input_sizes] = (tref + b_x *
                pulseendtimes_withuncert[input_sizes]) + tipj;
            }
          } else {
            b_binary_expand_op(pulseendtimes_withuncert, tref, b_x, tipj, b);
          }
        }

        // pulseendtimes_nom          = pulsestarttimes_nom+tp;
        // pulsestarttimes_withuncert = pulsestarttimes_nom-tipu-tipj;
        // pulseendtimes_withuncert   = pulsestarttimes_nom+tipu+tipj;
        // Check if pulses started after expected minimum start times
        n = ps_pos->pl.size(1);
        b_obj = ps_pos->pl.reshape(n);
        n = b_obj.size(0);
        if (b_obj.size(0) == 0) {
          input_sizes = 0;
        } else {
          input_sizes = b_obj.size(0);
        }

        b.set_size(1, input_sizes);
        for (ip = 0; ip < n; ip++) {
          b[ip] = b_obj[ip].t_0;
        }

        if (b.size(1) != 0) {
          c_input_sizes[1] = b.size(1);
        } else {
          c_input_sizes[1] = 0;
        }

        // Check if pulses started before expected maximum start times
        n = ps_pos->pl.size(1);
        b_obj = ps_pos->pl.reshape(n);
        n = b_obj.size(0);
        if (b_obj.size(0) == 0) {
          input_sizes = 0;
        } else {
          input_sizes = b_obj.size(0);
        }

        varargin_1.set_size(1, input_sizes);
        for (ip = 0; ip < n; ip++) {
          varargin_1[ip] = b_obj[ip].t_0;
        }

        if (varargin_1.size(1) != 0) {
          d_input_sizes[1] = varargin_1.size(1);
        } else {
          d_input_sizes[1] = 0;
        }

        // Frequency check. Within +/- 100 Hz of previously
        // detected pulses?
        structure = &ps_pos->pl;
        n = structure->size(1);
        if (structure->size(1) == 0) {
          input_sizes = 0;
        } else {
          input_sizes = structure->size(1);
        }

        b_varargin_1.set_size(1, input_sizes);
        for (ip = 0; ip < n; ip++) {
          b_varargin_1[ip] = (*structure)[ip].fp;
        }

        if (b_varargin_1.size(1) != 0) {
          e_input_sizes[1] = b_varargin_1.size(1);
        } else {
          e_input_sizes[1] = 0;
        }

        structure = &ps_pre->pl;
        n = structure->size(1);
        if (structure->size(1) == 0) {
          input_sizes = 0;
        } else {
          input_sizes = structure->size(1);
        }

        c_varargin_1.set_size(1, input_sizes);
        for (ip = 0; ip < n; ip++) {
          c_varargin_1[ip] = (*structure)[ip].fp;
        }

        if (c_varargin_1.size(1) != 0) {
          f_input_sizes[1] = c_varargin_1.size(1);
        } else {
          f_input_sizes[1] = 0;
        }

        structure = &ps_pos->pl;
        n = structure->size(1);
        if (structure->size(1) == 0) {
          input_sizes = 0;
        } else {
          input_sizes = structure->size(1);
        }

        d_varargin_1.set_size(1, input_sizes);
        for (ip = 0; ip < n; ip++) {
          d_varargin_1[ip] = (*structure)[ip].fp;
        }

        if (d_varargin_1.size(1) != 0) {
          g_input_sizes[1] = d_varargin_1.size(1);
        } else {
          g_input_sizes[1] = 0;
        }

        structure = &ps_pre->pl;
        n = structure->size(1);
        if (structure->size(1) == 0) {
          input_sizes = 0;
        } else {
          input_sizes = structure->size(1);
        }

        e_varargin_1.set_size(1, input_sizes);
        for (ip = 0; ip < n; ip++) {
          e_varargin_1[ip] = (*structure)[ip].fp;
        }

        if (e_varargin_1.size(1) != 0) {
          h_input_sizes[1] = e_varargin_1.size(1);
        } else {
          h_input_sizes[1] = 0;
        }

        if (d_input_sizes[1] == 1) {
          n = pulseendtimes_withuncert.size(1);
        } else {
          n = d_input_sizes[1];
        }

        if (c_input_sizes[1] == 1) {
          input_sizes = pulsestarttimes_withuncert.size(1);
        } else {
          input_sizes = c_input_sizes[1];
        }

        if (e_input_sizes[1] == 1) {
          ip = f_input_sizes[1];
        } else {
          ip = e_input_sizes[1];
        }

        if (g_input_sizes[1] == 1) {
          b_input_sizes = h_input_sizes[1];
        } else {
          b_input_sizes = g_input_sizes[1];
        }

        if (d_input_sizes[1] == 1) {
          i_input_sizes = pulseendtimes_withuncert.size(1);
        } else {
          i_input_sizes = d_input_sizes[1];
        }

        if (i_input_sizes == 1) {
          if (c_input_sizes[1] == 1) {
            i_input_sizes = pulsestarttimes_withuncert.size(1);
          } else {
            i_input_sizes = c_input_sizes[1];
          }
        } else if (d_input_sizes[1] == 1) {
          i_input_sizes = pulseendtimes_withuncert.size(1);
        } else {
          i_input_sizes = d_input_sizes[1];
        }

        if (e_input_sizes[1] == 1) {
          j_input_sizes = f_input_sizes[1];
        } else {
          j_input_sizes = e_input_sizes[1];
        }

        if (j_input_sizes == 1) {
          if (g_input_sizes[1] == 1) {
            j_input_sizes = h_input_sizes[1];
          } else {
            j_input_sizes = g_input_sizes[1];
          }
        } else if (e_input_sizes[1] == 1) {
          j_input_sizes = f_input_sizes[1];
        } else {
          j_input_sizes = e_input_sizes[1];
        }

        if ((d_input_sizes[1] == pulseendtimes_withuncert.size(1)) &&
            (c_input_sizes[1] == pulsestarttimes_withuncert.size(1)) && (n ==
             input_sizes) && (e_input_sizes[1] == f_input_sizes[1]) &&
            (g_input_sizes[1] == h_input_sizes[1]) && (ip == b_input_sizes) &&
            (i_input_sizes == j_input_sizes)) {
          b_conflog.set_size(1, d_input_sizes[1]);
          n = d_input_sizes[1];
          for (input_sizes = 0; input_sizes < n; input_sizes++) {
            b_conflog[input_sizes] = ((varargin_1[input_sizes] <=
              pulseendtimes_withuncert[input_sizes]) && (b[input_sizes] >=
              pulsestarttimes_withuncert[input_sizes]) &&
              ((b_varargin_1[input_sizes] >= c_varargin_1[input_sizes] - 100.0) &&
               (d_varargin_1[input_sizes] <= e_varargin_1[input_sizes] + 100.0)));
          }
        } else {
          c_binary_expand_op(b_conflog, varargin_1, d_input_sizes,
                             pulseendtimes_withuncert, b, c_input_sizes,
                             pulsestarttimes_withuncert, b_varargin_1,
                             e_input_sizes, c_varargin_1, f_input_sizes,
                             d_varargin_1, g_input_sizes, e_varargin_1,
                             h_input_sizes);
        }

        // [minstartlog', maxstartlog', freqInBand', conflog']
        n = b_conflog.size(1);
        conflog = b_conflog.reshape(n);
        have_priori_freq_band = false;
        n = 1;
        exitg1 = false;
        while ((!exitg1) && (n <= conflog.size(0))) {
          if (conflog[n - 1]) {
            have_priori_freq_band = true;
            exitg1 = true;
          } else {
            n++;
          }
        }

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
        input_sizes = ps_pos->pl.size(1) - 1;
        for (ip = 0; ip <= input_sizes; ip++) {
          // obj.ps_pos.pl(ip).con_dec = true;
          b_val.set_size(1, ps_pos->pl.size(1));
          n = ps_pos->pl.size(1);
          for (b_input_sizes = 0; b_input_sizes < n; b_input_sizes++) {
            b_val[b_input_sizes] = ps_pos->pl[b_input_sizes];
          }

          b_val[ip].con_dec = b_conflog[ip];
          obj = ps_pos;
          b_candidatelist.set_size(1, b_val.size(1));
          n = b_val.size(0) * b_val.size(1) - 1;
          for (b_input_sizes = 0; b_input_sizes <= n; b_input_sizes++) {
            b_candidatelist[b_input_sizes] = b_val[b_input_sizes];
          }

          coder::internal::validator_check_size(b_candidatelist, b_val);
          obj->pl.set_size(1, b_val.size(1));
          n = b_val.size(1);
          for (b_input_sizes = 0; b_input_sizes < n; b_input_sizes++) {
            obj->pl[b_input_sizes] = b_val[b_input_sizes];
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
      input_sizes = ps_pos->pl.size(1) - 1;
      for (ip = 0; ip <= input_sizes; ip++) {
        b_val.set_size(1, ps_pos->pl.size(1));
        n = ps_pos->pl.size(1);
        for (b_input_sizes = 0; b_input_sizes < n; b_input_sizes++) {
          b_val[b_input_sizes] = ps_pos->pl[b_input_sizes];
        }

        b_val[b_val.size(0) * ip].mode.set_size(1, 1);
        b_val[ip].mode[0] = mode;
        obj = ps_pos;
        b_candidatelist.set_size(1, b_val.size(1));
        n = b_val.size(0) * b_val.size(1) - 1;
        for (b_input_sizes = 0; b_input_sizes <= n; b_input_sizes++) {
          b_candidatelist[b_input_sizes] = b_val[b_input_sizes];
        }

        coder::internal::validator_check_size(b_candidatelist, b_val);
        obj->pl.set_size(1, b_val.size(1));
        n = b_val.size(1);
        for (b_input_sizes = 0; b_input_sizes < n; b_input_sizes++) {
          obj->pl[b_input_sizes] = b_val[b_input_sizes];
        }

        // 'C';
      }

      input_sizes = ps_pos->clst.size(0) * ps_pos->clst.size(1) - 1;
      for (ip = 0; ip <= input_sizes; ip++) {
        candidatelist.set_size(ps_pos->clst.size(0), ps_pos->clst.size(1));
        n = ps_pos->clst.size(0) * ps_pos->clst.size(1);
        for (b_input_sizes = 0; b_input_sizes < n; b_input_sizes++) {
          candidatelist[b_input_sizes] = ps_pos->clst[b_input_sizes];
        }

        candidatelist[ip].mode.set_size(1, 1);
        candidatelist[ip].mode[0] = mode;
        obj = ps_pos;
        c_candidatelist.set_size(candidatelist.size(0), candidatelist.size(1));
        n = candidatelist.size(0) * candidatelist.size(1) - 1;
        for (b_input_sizes = 0; b_input_sizes <= n; b_input_sizes++) {
          c_candidatelist[b_input_sizes] = candidatelist[b_input_sizes];
        }

        coder::internal::c_validator_check_size(c_candidatelist, candidatelist);
        obj->clst.set_size(candidatelist.size(0), candidatelist.size(1));
        n = candidatelist.size(0) * candidatelist.size(1);
        for (b_input_sizes = 0; b_input_sizes < n; b_input_sizes++) {
          obj->clst[b_input_sizes] = candidatelist[b_input_sizes];
        }

        // 'C';
      }
    }
    break;

   case 2:
    //                 %% TRACKING MODE
    // Find all the potential pulses in the dataset
    findpulse(time_search_type_data, time_search_type_size,
              freq_search_type_data, freq_search_type_size, excluded_freq_bands,
              candidatelist, msk, pk_ind);
    conflog.set_size(pk_ind.size(0));
    n = pk_ind.size(0);
    for (input_sizes = 0; input_sizes < n; input_sizes++) {
      conflog[input_sizes] = std::isnan(pk_ind[input_sizes]);
    }

    n = conflog.size(0);
    for (input_sizes = 0; input_sizes < n; input_sizes++) {
      conflog[input_sizes] = !conflog[input_sizes];
    }

    if (coder::internal::ifWhileCond(conflog)) {
      // Record the detection pulses
      // We only use the highest power pulse group for now
      // because if we are in confirmation mode, we only allow
      // for the selection mode to be 'most'
      obj = ps_pos;
      n = candidatelist.size(1);
      b_candidatelist.set_size(1, candidatelist.size(1));
      for (input_sizes = 0; input_sizes < n; input_sizes++) {
        b_candidatelist[input_sizes] = candidatelist[(static_cast<int>(pk_ind[0])
          + candidatelist.size(0) * input_sizes) - 1];
      }

      coder::internal::validator_check_size(b_candidatelist, b_val);
      obj->pl.set_size(1, b_val.size(1));
      n = b_val.size(1);
      for (input_sizes = 0; input_sizes < n; input_sizes++) {
        obj->pl[input_sizes] = b_val[input_sizes];
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
    c_candidatelist.set_size(candidatelist.size(0), candidatelist.size(1));
    n = candidatelist.size(0) * candidatelist.size(1) - 1;
    for (input_sizes = 0; input_sizes <= n; input_sizes++) {
      c_candidatelist[input_sizes] = candidatelist[input_sizes];
    }

    coder::internal::c_validator_check_size(c_candidatelist, candidatelist);
    obj->clst.set_size(candidatelist.size(0), candidatelist.size(1));
    n = candidatelist.size(0) * candidatelist.size(1);
    for (input_sizes = 0; input_sizes < n; input_sizes++) {
      obj->clst[input_sizes] = candidatelist[input_sizes];
    }

    obj = ps_pos;
    b_msk.set_size(msk.size(0), msk.size(1));
    n = msk.size(0) * msk.size(1) - 1;
    for (input_sizes = 0; input_sizes <= n; input_sizes++) {
      b_msk[input_sizes] = msk[input_sizes];
    }

    coder::internal::d_validator_check_size(b_msk, msk);
    obj->cmsk.set_size(msk.size(0), msk.size(1));
    n = msk.size(0) * msk.size(1);
    for (input_sizes = 0; input_sizes < n; input_sizes++) {
      obj->cmsk[input_sizes] = msk[input_sizes];
    }

    obj = ps_pos;
    coder::internal::validator_check_size(pk_ind, _in);
    obj->cpki.set_size(_in.size(0), _in.size(1));
    n = _in.size(0) * _in.size(1);
    for (input_sizes = 0; input_sizes < n; input_sizes++) {
      obj->cpki[input_sizes] = _in[input_sizes];
    }

    //  Detection?
    if (coder::internal::ifWhileCond(conflog)) {
      // ~isempty(pulselist)%obj.decide(pulselist,PF,decision_table) %Decision on IDed pulses
      // True ->
      // Update confirmation property for each pulse
      // If we are in tracking mode, we have narrowed the time and
      // frequeny bounds, so if there is a detection then we are
      // confirming the previous projections.
      input_sizes = ps_pos->pl.size(1) - 1;
      for (int ip{0}; ip <= input_sizes; ip++) {
        b_val.set_size(1, ps_pos->pl.size(1));
        n = ps_pos->pl.size(1);
        for (int b_input_sizes{0}; b_input_sizes < n; b_input_sizes++) {
          b_val[b_input_sizes] = ps_pos->pl[b_input_sizes];
        }

        b_val[ip].con_dec = true;
        obj = ps_pos;
        b_candidatelist.set_size(1, b_val.size(1));
        n = b_val.size(0) * b_val.size(1) - 1;
        for (int b_input_sizes{0}; b_input_sizes <= n; b_input_sizes++) {
          b_candidatelist[b_input_sizes] = b_val[b_input_sizes];
        }

        coder::internal::validator_check_size(b_candidatelist, b_val);
        obj->pl.set_size(1, b_val.size(1));
        n = b_val.size(1);
        for (int b_input_sizes{0}; b_input_sizes < n; b_input_sizes++) {
          obj->pl[b_input_sizes] = b_val[b_input_sizes];
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
    input_sizes = ps_pos->pl.size(1) - 1;
    for (int ip{0}; ip <= input_sizes; ip++) {
      b_val.set_size(1, ps_pos->pl.size(1));
      n = ps_pos->pl.size(1);
      for (int b_input_sizes{0}; b_input_sizes < n; b_input_sizes++) {
        b_val[b_input_sizes] = ps_pos->pl[b_input_sizes];
      }

      b_val[b_val.size(0) * ip].mode.set_size(1, 1);
      b_val[ip].mode[0] = mode;
      obj = ps_pos;
      b_candidatelist.set_size(1, b_val.size(1));
      n = b_val.size(0) * b_val.size(1) - 1;
      for (int b_input_sizes{0}; b_input_sizes <= n; b_input_sizes++) {
        b_candidatelist[b_input_sizes] = b_val[b_input_sizes];
      }

      coder::internal::validator_check_size(b_candidatelist, b_val);
      obj->pl.set_size(1, b_val.size(1));
      n = b_val.size(1);
      for (int b_input_sizes{0}; b_input_sizes < n; b_input_sizes++) {
        obj->pl[b_input_sizes] = b_val[b_input_sizes];
      }

      //  'T';
    }

    input_sizes = ps_pos->clst.size(0) * ps_pos->clst.size(1) - 1;
    for (int ip{0}; ip <= input_sizes; ip++) {
      candidatelist.set_size(ps_pos->clst.size(0), ps_pos->clst.size(1));
      n = ps_pos->clst.size(0) * ps_pos->clst.size(1);
      for (int b_input_sizes{0}; b_input_sizes < n; b_input_sizes++) {
        candidatelist[b_input_sizes] = ps_pos->clst[b_input_sizes];
      }

      candidatelist[ip].mode.set_size(1, 1);
      candidatelist[ip].mode[0] = mode;
      obj = ps_pos;
      c_candidatelist.set_size(candidatelist.size(0), candidatelist.size(1));
      n = candidatelist.size(0) * candidatelist.size(1) - 1;
      for (int b_input_sizes{0}; b_input_sizes <= n; b_input_sizes++) {
        c_candidatelist[b_input_sizes] = candidatelist[b_input_sizes];
      }

      coder::internal::c_validator_check_size(c_candidatelist, candidatelist);
      obj->clst.set_size(candidatelist.size(0), candidatelist.size(1));
      n = candidatelist.size(0) * candidatelist.size(1);
      for (int b_input_sizes{0}; b_input_sizes < n; b_input_sizes++) {
        obj->clst[b_input_sizes] = candidatelist[b_input_sizes];
      }

      //  'T';
    }
    break;

   default:
    //                 %% SOMETHING BROKE
    break;
  }
}

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

void waveform::setweightingmatrix()
{
  coder::array<creal_T, 2U> Xs;
  coder::array<creal_T, 2U> b_r;
  coder::array<creal_T, 2U> buffer;
  coder::array<creal_T, 2U> c_x;
  coder::array<creal_T, 2U> currDFT;
  coder::array<creal_T, 2U> s;
  coder::array<creal_T, 2U> stackedToeplitzMatrices;
  coder::array<creal_T, 1U> b_x;
  coder::array<creal_T, 1U> r;
  coder::array<double, 2U> output_samps;
  coder::array<double, 2U> sintab;
  coder::array<double, 2U> sintabinv;
  coder::array<double, 2U> w_time_domain;
  coder::array<double, 2U> x_of_n;
  coder::array<double, 1U> b_Wf;
  coder::array<double, 1U> r1;
  coder::array<int, 1U> iidx;
  coder::array<boolean_T, 2U> b_output_samps;
  double tmplt_samps[2];
  double y[2];
  double b_Fs;
  double xtmp_im;
  double xtmp_re;
  int b_loop_ub;
  int i;
  int i1;
  int k;
  int loop_ub;
  int loop_ub_tmp;
  int md2;
  unsigned int nfft;
  int nw;
  int nx;
  boolean_T useRadix2;

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
  nx = stft->f.size(0);

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
  y[0] = ps_pre->tmplt[0];
  y[1] = ps_pre->tmplt[1];
  w_time_domain.set_size(1, output_samps.size(1));
  loop_ub = output_samps.size(1);
  for (i = 0; i < loop_ub; i++) {
    w_time_domain[i] = rtNaN;
  }

  useRadix2 = (output_samps.size(1) == 0);
  if (!useRadix2) {
    k = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (k < 2) {
        if (std::isnan(tmplt_samps[k])) {
          exitg1 = 1;
        } else {
          k++;
        }
      } else {
        if (tmplt_samps[1] < 0.0) {
          tmplt_samps[0] = tmplt_samps[1];
          tmplt_samps[1] = 0.0;
          y[0] = ps_pre->tmplt[1];
          y[1] = ps_pre->tmplt[0];
        }

        coder::interp1Linear(y, output_samps, w_time_domain, tmplt_samps);
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  // Generate the extra-zeros needed to pad to get to 'samples' samples
  nx -= output_samps.size(1);
  output_samps.set_size(1, nx);
  for (i = 0; i < nx; i++) {
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
    double b_y;
    double t;
    xtmp_im = 0.5 * static_cast<double>(b_i) * 6.2831853071795862;
    b_x.set_size(output_samps.size(1));
    for (i = 0; i < loop_ub; i++) {
      t = xtmp_im * output_samps[i];
      if (t == 0.0) {
        b_x[i].re = 0.0 / static_cast<double>(nw);
        b_x[i].im = 0.0;
      } else {
        b_x[i].re = 0.0;
        b_x[i].im = t / static_cast<double>(nw);
      }
    }

    nx = b_x.size(0);
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

    b_loop_ub = b_x.size(0);
    for (i = 0; i < b_loop_ub; i++) {
      s[i + s.size(0) * b_i] = b_x[i];
    }

    if (s.size(0) == x_of_n.size(0)) {
      c_x.set_size(s.size(0), 1);
      b_loop_ub = s.size(0);
      for (i = 0; i < b_loop_ub; i++) {
        c_x[i].re = x_of_n[i] * s[i + s.size(0) * b_i].re;
        c_x[i].im = x_of_n[i] * s[i + s.size(0) * b_i].im;
      }
    } else {
      b_binary_expand_op(c_x, s, b_i, s.size(0), x_of_n);
    }

    if (c_x.size(0) == 0) {
      currDFT.set_size(0, 1);
    } else {
      useRadix2 = ((c_x.size(0) & (c_x.size(0) - 1)) == 0);
      coder::internal::FFTImplementationCallback::get_algo_sizes(c_x.size(0),
        useRadix2, &nx, &b_loop_ub);
      coder::internal::FFTImplementationCallback::generate_twiddle_tables
        (b_loop_ub, useRadix2, w_time_domain, sintab, sintabinv);
      if (useRadix2) {
        coder::internal::FFTImplementationCallback::r2br_r2dit_trig(c_x,
          c_x.size(0), w_time_domain, sintab, currDFT);
      } else {
        coder::internal::FFTImplementationCallback::dobluesteinfft(c_x, nx,
          c_x.size(0), w_time_domain, sintab, sintabinv, currDFT);
      }
    }

    if (currDFT.size(0) == 0) {
      b_y = 0.0;
    } else {
      b_y = 0.0;
      if (currDFT.size(0) == 1) {
        b_y = rt_hypotd_snf(currDFT[0].re, currDFT[0].im);
      } else {
        xtmp_re = 3.3121686421112381E-170;
        nx = currDFT.size(0);
        for (k = 0; k < nx; k++) {
          xtmp_im = std::abs(currDFT[k].re);
          if (xtmp_im > xtmp_re) {
            t = xtmp_re / xtmp_im;
            b_y = b_y * t * t + 1.0;
            xtmp_re = xtmp_im;
          } else {
            t = xtmp_im / xtmp_re;
            b_y += t * t;
          }

          xtmp_im = std::abs(currDFT[k].im);
          if (xtmp_im > xtmp_re) {
            t = xtmp_re / xtmp_im;
            b_y = b_y * t * t + 1.0;
            xtmp_re = xtmp_im;
          } else {
            t = xtmp_im / xtmp_re;
            b_y += t * t;
          }
        }

        b_y = xtmp_re * std::sqrt(b_y);
      }
    }

    currDFT.set_size(currDFT.size(0), 1);
    b_loop_ub = currDFT.size(0) - 1;
    for (i = 0; i <= b_loop_ub; i++) {
      xtmp_re = currDFT[i].re;
      t = currDFT[i].im;
      if (t == 0.0) {
        xtmp_im = xtmp_re / b_y;
        xtmp_re = 0.0;
      } else if (xtmp_re == 0.0) {
        xtmp_im = 0.0;
        xtmp_re = t / b_y;
      } else {
        xtmp_im = xtmp_re / b_y;
        xtmp_re = t / b_y;
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
      if ((currDFT.size(0) != 0) && (currDFT.size(0) != 1)) {
        b_loop_ub = static_cast<int>(std::floor(static_cast<double>(currDFT.size
          (0)) / 2.0));
        buffer.set_size(1, static_cast<int>(std::floor(static_cast<double>
          (currDFT.size(0)) / 2.0)));
        for (i = 0; i < b_loop_ub; i++) {
          buffer[i].re = 0.0;
          buffer[i].im = 0.0;
        }

        i = currDFT.size(0) - 2;
        buffer[0] = currDFT[0];
        for (k = 0; k <= i; k++) {
          currDFT[k] = currDFT[k + 1];
        }

        currDFT[i + 1] = buffer[0];
      }
    }

    b_loop_ub = Xs.size(0);
    for (i = 0; i < b_loop_ub; i++) {
      Xs[i + Xs.size(0) * b_i] = currDFT[i];
    }

    //    stem(freqs_orig,abs(Xs(:,i)),'DisplayName',['\zeta =',num2str(zetas(i))]);
    //    hold on
  }

  // ylabel('|Xs|');xlabel('Frequency');legend('Location',"best");
  // title('DFT of primary frequency shifts of the template')
  // New W generation method. ~25% faster on average
  stackedToeplitzMatrices.set_size(2 * x_of_n.size(0), x_of_n.size(0));
  loop_ub = 2 * x_of_n.size(0) * x_of_n.size(0);
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
    if (static_cast<unsigned int>(nw) < 1U) {
      i2 = 0;
    } else {
      i2 = b_i * nw;
    }

    b_x.set_size(loop_ub_tmp);
    for (i3 = 0; i3 < loop_ub_tmp; i3++) {
      b_x[i3] = Xs[((i + i3) + Xs.size(0) * b_i) + 1];
    }

    for (loop_ub = 0; loop_ub < md2; loop_ub++) {
      xtmp_re = b_x[loop_ub].re;
      xtmp_im = b_x[loop_ub].im;
      nx = (loop_ub_tmp - loop_ub) - 1;
      b_x[loop_ub] = b_x[nx];
      b_x[nx].re = xtmp_re;
      b_x[nx].im = xtmp_im;
    }

    r.set_size(b_x.size(0) + 1);
    r[0] = Xs[Xs.size(0) * b_i];
    loop_ub = b_x.size(0);
    for (i3 = 0; i3 < loop_ub; i3++) {
      r[i3 + 1] = b_x[i3];
    }

    b_r.set_size(Xs.size(0), r.size(0));
    nx = 0;
    i3 = r.size(0) - 1;
    for (b_loop_ub = 0; b_loop_ub <= i3; b_loop_ub++) {
      k = b_loop_ub;
      for (loop_ub = 0; loop_ub <= i1; loop_ub++) {
        if (loop_ub < b_loop_ub) {
          b_r[nx + loop_ub] = r[k];
          k--;
        } else {
          b_r[nx + loop_ub] = Xs[k + Xs.size(0) * b_i];
          k++;
        }
      }

      nx = (nx + i1) + 1;
    }

    loop_ub = b_r.size(1);
    for (i3 = 0; i3 < loop_ub; i3++) {
      b_loop_ub = b_r.size(0);
      for (nx = 0; nx < b_loop_ub; nx++) {
        stackedToeplitzMatrices[(i2 + nx) + stackedToeplitzMatrices.size(0) * i3]
          = b_r[nx + b_r.size(0) * i3];
      }
    }
  }

  // Reshape in this way will interweave rows of each sub matrix of the stack
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
  nfft = static_cast<unsigned int>(x_of_n.size(0)) << 1;

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
  if (static_cast<double>(nfft) - 1.0 < 0.0) {
    output_samps.set_size(output_samps.size(0), 0);
  } else {
    output_samps.set_size(1, static_cast<int>(static_cast<double>(nfft) - 1.0) +
                          1);
    loop_ub = static_cast<int>(static_cast<double>(nfft) - 1.0);
    for (i = 0; i <= loop_ub; i++) {
      output_samps[i] = i;
    }
  }

  // Simulink (coder?) didn't like the new round inputs
  // freqs = round(freqs,3);
  output_samps.set_size(1, output_samps.size(1));
  loop_ub = output_samps.size(1) - 1;
  for (i = 0; i <= loop_ub; i++) {
    output_samps[i] = output_samps[i] * b_Fs / static_cast<double>(nfft) *
      1000.0;
  }

  nx = output_samps.size(1);
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

  int tmp_size[2];
  coder::eml_find(b_output_samps, (int *)&nx, tmp_size);
  xtmp_re = -output_samps[output_samps.size(1) - 1] - (b_Fs -
    output_samps[output_samps.size(1) - 1]);
  w_time_domain.set_size(1, output_samps.size(1) - nx);
  loop_ub = output_samps.size(1) - nx;
  for (i = 0; i < loop_ub; i++) {
    w_time_domain[i] = 1.0;
  }

  // Here we sort the output to set up to have an ascending order of frequency
  // to be similar to the centered frequency list used elsewhere in the
  // codebase for the STFT output.
  if (nx + w_time_domain.size(1) == output_samps.size(1)) {
    r1.set_size(nx + w_time_domain.size(1));
    for (i = 0; i < nx; i++) {
      r1[i] = 0.0;
    }

    loop_ub = w_time_domain.size(1);
    for (i = 0; i < loop_ub; i++) {
      r1[i + nx] = xtmp_re;
    }

    b_Wf.set_size(r1.size(0));
    loop_ub = r1.size(0);
    for (i = 0; i < loop_ub; i++) {
      b_Wf[i] = r1[i] + output_samps[i];
    }
  } else {
    b_binary_expand_op(b_Wf, nx, xtmp_re, w_time_domain, output_samps);
  }

  coder::internal::sort(b_Wf, iidx);
  nx = x_of_n.size(0);
  loop_ub = x_of_n.size(0);
  b_r.set_size(x_of_n.size(0), iidx.size(0));
  b_loop_ub = iidx.size(0);
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      b_r[i1 + b_r.size(0) * i] = stackedToeplitzMatrices[i1 + nx * (iidx[i] - 1)];
    }
  }

  coder::internal::validator_check_size(b_r, W);
  coder::internal::validator_check_size(b_Wf, Wf);
}

void waveform::spectro(wfmstft *iobj_0)
{
  coder::array<creal_T, 2U> b_S;
  coder::array<creal_T, 2U> r;
  coder::array<creal_T, 2U> val;
  coder::array<creal32_T, 2U> S;
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

  // SPECTRO Executes an STFT of x and sets up the wfmstst object
  // for the waveform
  //
  // INPUTS:
  //    obj     The waveform object
  // OUTPUTS:
  //    none
  //
  //             %%
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
  if (n_est == std::floor(n_est)) {
    loop_ub = static_cast<int>(n_est);
  } else {
    loop_ub = static_cast<int>(std::round(n_est));
  }

  b__in.set_size(loop_ub);
  for (int i{0}; i < loop_ub; i++) {
    b__in[i] = 1.0;
  }

  coder::internal::validator_check_size(b__in, _in);
  iobj_0->wind.set_size(_in.size(0));
  loop_ub = _in.size(0);
  for (int i{0}; i < loop_ub; i++) {
    iobj_0->wind[i] = _in[i];
  }

  ::coder::stft(x, Fs, iobj_0->wind, n_ol, n_w, S, r1, local_time);
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

void b_waveform::spectro(wfmstft *iobj_0)
{
  coder::array<creal_T, 2U> b_S;
  coder::array<creal_T, 2U> r;
  coder::array<creal_T, 2U> val;
  coder::array<creal32_T, 2U> S;
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

  // SPECTRO Executes an STFT of x and sets up the wfmstst object
  // for the waveform
  //
  // INPUTS:
  //    obj     The waveform object
  // OUTPUTS:
  //    none
  //
  //             %%
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
  if (n_est == std::floor(n_est)) {
    loop_ub = static_cast<int>(n_est);
  } else {
    loop_ub = static_cast<int>(std::round(n_est));
  }

  b__in.set_size(loop_ub);
  for (int i{0}; i < loop_ub; i++) {
    b__in[i] = 1.0;
  }

  coder::internal::validator_check_size(b__in, _in);
  iobj_0->wind.set_size(_in.size(0));
  loop_ub = _in.size(0);
  for (int i{0}; i < loop_ub; i++) {
    iobj_0->wind[i] = _in[i];
  }

  ::coder::stft(x, Fs, iobj_0->wind, n_ol, n_w, S, r1, local_time);
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

// End of code generation (waveform.cpp)
