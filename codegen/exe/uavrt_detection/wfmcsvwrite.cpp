//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: wfmcsvwrite.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "wfmcsvwrite.h"
#include "abs.h"
#include "fileManager.h"
#include "pulsestats.h"
#include "rt_nonfinite.h"
#include "strcmp.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_internal_types.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "waveform.h"
#include "wfmstft.h"
#include "coder_array.h"
#include <cstdio>

// Variable Definitions
static boolean_T fid_not_empty;

static boolean_T filePathPersistent_not_empty;

// Function Definitions
//
// WFMCSVWRITE Saves the spectrogram, pulses, and the spectrogram frequencies
// and times to a file for record keeping and post-flight analysis.
//
// INPUTS:
//    X   waveform instance
//    radioFcMHz  radio channel center frequency in MHz
//    filePath    file path to write to
// OUTPUTS:
//    none other than the file
//
// Author:    Michael Shafer
// Date:      Fall 2023
//
// --------------------------------------------------------------------------
//
// Arguments    : waveform &X
//                double radioFcMHz
//                const coder::array<char, 2U> &filePath
// Return Type  : void
//
void wfmcsvwrite(waveform &X, double radioFcMHz,
                 const coder::array<char, 2U> &filePath)
{
  static coder::array<char, 2U> filePathPersistent;
  static rtBoundsCheckInfo ab_emlrtBCI{
      44,            // lineNo
      "X.ps_pos.pl", // aName
      "wfmcsvwrite"  // fName
  };
  static rtBoundsCheckInfo bb_emlrtBCI{
      48,            // lineNo
      "X.ps_pos.pl", // aName
      "wfmcsvwrite"  // fName
  };
  static rtBoundsCheckInfo cb_emlrtBCI{
      52,            // lineNo
      "X.ps_pos.pl", // aName
      "wfmcsvwrite"  // fName
  };
  static rtBoundsCheckInfo db_emlrtBCI{
      56,            // lineNo
      "X.ps_pos.pl", // aName
      "wfmcsvwrite"  // fName
  };
  static rtBoundsCheckInfo eb_emlrtBCI{
      62,           // lineNo
      "X.stft.f",   // aName
      "wfmcsvwrite" // fName
  };
  static rtBoundsCheckInfo fb_emlrtBCI{
      67,           // lineNo
      "X.stft.t",   // aName
      "wfmcsvwrite" // fName
  };
  static rtBoundsCheckInfo gb_emlrtBCI{
      72,           // lineNo
      "X.stft.S",   // aName
      "wfmcsvwrite" // fName
  };
  static double fid;
  std::FILE *f;
  double validatedHoleFilling_idx_0;
  int i;
  int loop_ub;
  signed char fileid;
  boolean_T autoflush;
  if (!fid_not_empty) {
    std::printf("\t Opening new spectro_segment record file.\n.");
    std::fflush(stdout);
    fileid = coder::internal::cfopen(filePath, "wb");
    fid = fileid;
    fid_not_empty = true;
    loop_ub = filePath.size(1);
    filePathPersistent.set_size(1, filePath.size(1));
    for (i = 0; i < loop_ub; i++) {
      filePathPersistent[i] = filePath[i];
    }
    filePathPersistent_not_empty = true;
  } else if (coder::internal::b_strcmp(filePathPersistent, filePath)) {
    std::printf(
        "\t Writing to an already open spectro_segment record file.\n.");
    std::fflush(stdout);
    // Do nothing, since we want to write to the same file
  } else if (fid_not_empty &&
             (!coder::internal::b_strcmp(filePathPersistent, filePath))) {
    // Close the previously opened file and open a new one with the updated file
    // name
    std::printf("\t Closing existing spectro_segment file and opening a new "
                "one with an updated file name.\n.");
    std::fflush(stdout);
    coder::internal::cfclose(fid);
    fileid = coder::internal::cfopen(filePath, "wb");
    fid = fileid;
    loop_ub = filePath.size(1);
    filePathPersistent.set_size(1, filePath.size(1));
    for (i = 0; i < loop_ub; i++) {
      filePathPersistent[i] = filePath[i];
    }
    filePathPersistent_not_empty = true;
  }
  if (fid == 0.0) {
    e_rtErrorWithMessageID(jc_emlrtRTEI.fName, jc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(fid, autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(kc_emlrtRTEI.fName, kc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "%s\n", "----------------------------------------");
    if (autoflush) {
      std::fflush(f);
    }
  }
  if (fid == 0.0) {
    e_rtErrorWithMessageID(jc_emlrtRTEI.fName, jc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(fid, autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(kc_emlrtRTEI.fName, kc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "%s\n", "Record Start Time (s):");
    if (autoflush) {
      std::fflush(f);
    }
  }
  validatedHoleFilling_idx_0 = X.t_0;
  if (fid == 0.0) {
    e_rtErrorWithMessageID(jc_emlrtRTEI.fName, jc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(fid, autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(kc_emlrtRTEI.fName, kc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "%f\n", validatedHoleFilling_idx_0);
    if (autoflush) {
      std::fflush(f);
    }
  }
  if (fid == 0.0) {
    e_rtErrorWithMessageID(jc_emlrtRTEI.fName, jc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(fid, autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(kc_emlrtRTEI.fName, kc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "%s\n", "----------------------------------------");
    if (autoflush) {
      std::fflush(f);
    }
  }
  if (fid == 0.0) {
    e_rtErrorWithMessageID(jc_emlrtRTEI.fName, jc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(fid, autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(kc_emlrtRTEI.fName, kc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "%s\n", "Pulse Listing:");
    if (autoflush) {
      std::fflush(f);
    }
  }
  i = X.ps_pos->pl.size(1);
  for (int b_i{0}; b_i < i; b_i++) {
    loop_ub = X.ps_pos->pl.size(1);
    if (b_i + 1 > loop_ub) {
      rtDynamicBoundsError(b_i + 1, 1, loop_ub, ab_emlrtBCI);
    }
    validatedHoleFilling_idx_0 = X.ps_pos->pl[b_i].t_0;
    if (fid == 0.0) {
      e_rtErrorWithMessageID(jc_emlrtRTEI.fName, jc_emlrtRTEI.lineNo);
    }
    f = coder::internal::getfilestar(fid, autoflush);
    if (f == nullptr) {
      c_rtErrorWithMessageID(kc_emlrtRTEI.fName, kc_emlrtRTEI.lineNo);
    } else {
      std::fprintf(f, "%f,", validatedHoleFilling_idx_0);
      if (autoflush) {
        std::fflush(f);
      }
    }
  }
  if (fid == 0.0) {
    e_rtErrorWithMessageID(jc_emlrtRTEI.fName, jc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(fid, autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(kc_emlrtRTEI.fName, kc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "\n");
    if (autoflush) {
      std::fflush(f);
    }
  }
  i = X.ps_pos->pl.size(1);
  for (int b_i{0}; b_i < i; b_i++) {
    loop_ub = X.ps_pos->pl.size(1);
    if (b_i + 1 > loop_ub) {
      rtDynamicBoundsError(b_i + 1, 1, loop_ub, bb_emlrtBCI);
    }
    validatedHoleFilling_idx_0 = X.ps_pos->pl[b_i].fp / 1.0E+6 + radioFcMHz;
    if (fid == 0.0) {
      e_rtErrorWithMessageID(jc_emlrtRTEI.fName, jc_emlrtRTEI.lineNo);
    }
    f = coder::internal::getfilestar(fid, autoflush);
    if (f == nullptr) {
      c_rtErrorWithMessageID(kc_emlrtRTEI.fName, kc_emlrtRTEI.lineNo);
    } else {
      std::fprintf(f, "%f,", validatedHoleFilling_idx_0);
      if (autoflush) {
        std::fflush(f);
      }
    }
  }
  if (fid == 0.0) {
    e_rtErrorWithMessageID(jc_emlrtRTEI.fName, jc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(fid, autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(kc_emlrtRTEI.fName, kc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "\n");
    if (autoflush) {
      std::fflush(f);
    }
  }
  i = X.ps_pos->pl.size(1);
  for (int b_i{0}; b_i < i; b_i++) {
    loop_ub = X.ps_pos->pl.size(1);
    if (b_i + 1 > loop_ub) {
      rtDynamicBoundsError(b_i + 1, 1, loop_ub, cb_emlrtBCI);
    }
    validatedHoleFilling_idx_0 = X.ps_pos->pl[b_i].SNR;
    if (fid == 0.0) {
      e_rtErrorWithMessageID(jc_emlrtRTEI.fName, jc_emlrtRTEI.lineNo);
    }
    f = coder::internal::getfilestar(fid, autoflush);
    if (f == nullptr) {
      c_rtErrorWithMessageID(kc_emlrtRTEI.fName, kc_emlrtRTEI.lineNo);
    } else {
      std::fprintf(f, "%f,", validatedHoleFilling_idx_0);
      if (autoflush) {
        std::fflush(f);
      }
    }
  }
  if (fid == 0.0) {
    e_rtErrorWithMessageID(jc_emlrtRTEI.fName, jc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(fid, autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(kc_emlrtRTEI.fName, kc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "\n");
    if (autoflush) {
      std::fflush(f);
    }
  }
  i = X.ps_pos->pl.size(1);
  for (int b_i{0}; b_i < i; b_i++) {
    loop_ub = X.ps_pos->pl.size(1);
    if (b_i + 1 > loop_ub) {
      rtDynamicBoundsError(b_i + 1, 1, loop_ub, db_emlrtBCI);
    }
    fileid = static_cast<signed char>(X.ps_pos->pl[b_i].con_dec);
    if (fid == 0.0) {
      e_rtErrorWithMessageID(jc_emlrtRTEI.fName, jc_emlrtRTEI.lineNo);
    }
    f = coder::internal::getfilestar(fid, autoflush);
    if (f == nullptr) {
      c_rtErrorWithMessageID(kc_emlrtRTEI.fName, kc_emlrtRTEI.lineNo);
    } else {
      std::fprintf(f, "%u,", static_cast<unsigned char>(fileid));
      if (autoflush) {
        std::fflush(f);
      }
    }
  }
  if (fid == 0.0) {
    e_rtErrorWithMessageID(jc_emlrtRTEI.fName, jc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(fid, autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(kc_emlrtRTEI.fName, kc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "\n%s\n", "----------------------------------------");
    if (autoflush) {
      std::fflush(f);
    }
  }
  if (fid == 0.0) {
    e_rtErrorWithMessageID(jc_emlrtRTEI.fName, jc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(fid, autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(kc_emlrtRTEI.fName, kc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "%s\n", "Spectrogram Frequencies (MHz):");
    if (autoflush) {
      std::fflush(f);
    }
  }
  i = X.stft->f.size(0);
  for (int b_i{0}; b_i < i; b_i++) {
    loop_ub = X.stft->f.size(0);
    if (b_i + 1 > loop_ub) {
      rtDynamicBoundsError(b_i + 1, 1, loop_ub, eb_emlrtBCI);
    }
    validatedHoleFilling_idx_0 = X.stft->f[b_i] / 1.0E+6 + radioFcMHz;
    if (fid == 0.0) {
      e_rtErrorWithMessageID(jc_emlrtRTEI.fName, jc_emlrtRTEI.lineNo);
    }
    f = coder::internal::getfilestar(fid, autoflush);
    if (f == nullptr) {
      c_rtErrorWithMessageID(kc_emlrtRTEI.fName, kc_emlrtRTEI.lineNo);
    } else {
      std::fprintf(f, "%f,", validatedHoleFilling_idx_0);
      if (autoflush) {
        std::fflush(f);
      }
    }
  }
  if (fid == 0.0) {
    e_rtErrorWithMessageID(jc_emlrtRTEI.fName, jc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(fid, autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(kc_emlrtRTEI.fName, kc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "\n%s\n", "----------------------------------------");
    if (autoflush) {
      std::fflush(f);
    }
  }
  if (fid == 0.0) {
    e_rtErrorWithMessageID(jc_emlrtRTEI.fName, jc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(fid, autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(kc_emlrtRTEI.fName, kc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "%s\n", "Spectrogram Times (s):");
    if (autoflush) {
      std::fflush(f);
    }
  }
  i = X.stft->t.size(0);
  for (int b_i{0}; b_i < i; b_i++) {
    loop_ub = X.stft->t.size(0);
    if (b_i + 1 > loop_ub) {
      rtDynamicBoundsError(b_i + 1, 1, loop_ub, fb_emlrtBCI);
    }
    validatedHoleFilling_idx_0 = X.stft->t[b_i];
    if (fid == 0.0) {
      e_rtErrorWithMessageID(jc_emlrtRTEI.fName, jc_emlrtRTEI.lineNo);
    }
    f = coder::internal::getfilestar(fid, autoflush);
    if (f == nullptr) {
      c_rtErrorWithMessageID(kc_emlrtRTEI.fName, kc_emlrtRTEI.lineNo);
    } else {
      std::fprintf(f, "%f,", validatedHoleFilling_idx_0);
      if (autoflush) {
        std::fflush(f);
      }
    }
  }
  if (fid == 0.0) {
    e_rtErrorWithMessageID(jc_emlrtRTEI.fName, jc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(fid, autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(kc_emlrtRTEI.fName, kc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "\n%s\n", "----------------------------------------");
    if (autoflush) {
      std::fflush(f);
    }
  }
  if (fid == 0.0) {
    e_rtErrorWithMessageID(jc_emlrtRTEI.fName, jc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(fid, autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(kc_emlrtRTEI.fName, kc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "%s\n", "Spectrogram Values (|STFT|):");
    if (autoflush) {
      std::fflush(f);
    }
  }
  i = X.stft->S.size(0) * X.stft->S.size(1);
  for (int b_i{0}; b_i < i; b_i++) {
    creal_T b_X;
    loop_ub = X.stft->S.size(0) * X.stft->S.size(1);
    if ((static_cast<int>(static_cast<unsigned int>(b_i) + 1U) < 1) ||
        (static_cast<int>(static_cast<unsigned int>(b_i) + 1U) > loop_ub)) {
      rtDynamicBoundsError(
          static_cast<int>(static_cast<unsigned int>(b_i) + 1U), 1, loop_ub,
          gb_emlrtBCI);
    }
    b_X.re = X.stft->S[b_i].re;
    loop_ub = X.stft->S.size(0) * X.stft->S.size(1);
    if ((static_cast<int>(static_cast<unsigned int>(b_i) + 1U) < 1) ||
        (static_cast<int>(static_cast<unsigned int>(b_i) + 1U) > loop_ub)) {
      rtDynamicBoundsError(
          static_cast<int>(static_cast<unsigned int>(b_i) + 1U), 1, loop_ub,
          gb_emlrtBCI);
    }
    b_X.im = X.stft->S[b_i].im;
    if (fid == 0.0) {
      e_rtErrorWithMessageID(jc_emlrtRTEI.fName, jc_emlrtRTEI.lineNo);
    }
    f = coder::internal::getfilestar(fid, autoflush);
    if (f == nullptr) {
      c_rtErrorWithMessageID(kc_emlrtRTEI.fName, kc_emlrtRTEI.lineNo);
    } else {
      std::fprintf(f, "%f,", coder::b_abs(b_X));
      if (autoflush) {
        std::fflush(f);
      }
    }
  }
  if (fid == 0.0) {
    e_rtErrorWithMessageID(jc_emlrtRTEI.fName, jc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(fid, autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(kc_emlrtRTEI.fName, kc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "\n");
    if (autoflush) {
      std::fflush(f);
    }
  }
}

//
// Arguments    : void
// Return Type  : void
//
void wfmcsvwrite_init()
{
  filePathPersistent_not_empty = false;
  fid_not_empty = false;
}

//
// File trailer for wfmcsvwrite.cpp
//
// [EOF]
//
