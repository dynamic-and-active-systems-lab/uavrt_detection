//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: wfmcsvwrite.cpp
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 11-Nov-2023 11:31:43
//

// Include Files
#include "wfmcsvwrite.h"
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

// Function Definitions
//
// UNTITLED Summary of this function goes here
//    Detailed explanation goes here
//
// Arguments    : const waveform &X
//                double radioFcMHz
//                const coder::array<char, 2U> &filePath
// Return Type  : void
//
void wfmcsvwrite(const waveform &X, double radioFcMHz,
                 const coder::array<char, 2U> &filePath)
{
  static coder::array<char, 2U> filePathPersistent;
  static rtBoundsCheckInfo ab_emlrtBCI{
      -1,            // iFirst
      -1,            // iLast
      31,            // lineNo
      41,            // colNo
      "X.ps_pos.pl", // aName
      "wfmcsvwrite", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/wfmcsvwrite.m", // pName
      0                                                // checkKind
  };
  static rtBoundsCheckInfo bb_emlrtBCI{
      -1,            // iFirst
      -1,            // iLast
      35,            // lineNo
      41,            // colNo
      "X.ps_pos.pl", // aName
      "wfmcsvwrite", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/wfmcsvwrite.m", // pName
      0                                                // checkKind
  };
  static rtBoundsCheckInfo cb_emlrtBCI{
      -1,            // iFirst
      -1,            // iLast
      39,            // lineNo
      41,            // colNo
      "X.ps_pos.pl", // aName
      "wfmcsvwrite", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/wfmcsvwrite.m", // pName
      0                                                // checkKind
  };
  static rtBoundsCheckInfo db_emlrtBCI{
      -1,            // iFirst
      -1,            // iLast
      43,            // lineNo
      47,            // colNo
      "X.ps_pos.pl", // aName
      "wfmcsvwrite", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/wfmcsvwrite.m", // pName
      0                                                // checkKind
  };
  static rtBoundsCheckInfo eb_emlrtBCI{
      -1,            // iFirst
      -1,            // iLast
      49,            // lineNo
      34,            // colNo
      "X.stft.f",    // aName
      "wfmcsvwrite", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/wfmcsvwrite.m", // pName
      0                                                // checkKind
  };
  static rtBoundsCheckInfo fb_emlrtBCI{
      -1,            // iFirst
      -1,            // iLast
      54,            // lineNo
      34,            // colNo
      "X.stft.t",    // aName
      "wfmcsvwrite", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/wfmcsvwrite.m", // pName
      0                                                // checkKind
  };
  static rtBoundsCheckInfo gb_emlrtBCI{
      -1,            // iFirst
      -1,            // iLast
      59,            // lineNo
      38,            // colNo
      "X.stft.S",    // aName
      "wfmcsvwrite", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/wfmcsvwrite.m", // pName
      0                                                // checkKind
  };
  static double fid;
  std::FILE *f;
  coder::array<char, 2U> r;
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
    filePathPersistent.set_size(1, filePath.size(1));
    loop_ub = filePath.size(1);
    for (i = 0; i < loop_ub; i++) {
      filePathPersistent[i] = filePath[i];
    }
  } else {
    r.set_size(1, filePathPersistent.size(1));
    loop_ub = filePathPersistent.size(0) * filePathPersistent.size(1) - 1;
    for (i = 0; i <= loop_ub; i++) {
      r[i] = filePathPersistent[i];
    }
    if (coder::internal::b_strcmp(r, filePath)) {
      std::printf(
          "\t Writing to an already open spectro_segment record file.\n.");
      std::fflush(stdout);
      // Do nothing, since we want to write to the same file
    } else if (fid_not_empty) {
      r.set_size(1, filePathPersistent.size(1));
      loop_ub = filePathPersistent.size(0) * filePathPersistent.size(1) - 1;
      for (i = 0; i <= loop_ub; i++) {
        r[i] = filePathPersistent[i];
      }
      if (!coder::internal::b_strcmp(r, filePath)) {
        // Close the previously opened file and open a new one with the updated
        // file name
        std::printf("\t Closing existing spectro_segment file and opening a "
                    "new one with an updated file name.\n.");
        std::fflush(stdout);
        coder::internal::cfclose(fid);
        fileid = coder::internal::cfopen(filePath, "wb");
        fid = fileid;
        filePathPersistent.set_size(1, filePath.size(1));
        loop_ub = filePath.size(1);
        for (i = 0; i < loop_ub; i++) {
          filePathPersistent[i] = filePath[i];
        }
      }
    }
  }
  if (fid == 0.0) {
    g_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(fid, autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "%s\n", "----------------------------------------");
    if (autoflush) {
      std::fflush(f);
    }
  }
  if (fid == 0.0) {
    g_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(fid, autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "%s\n", "Record Start Time (s):");
    if (autoflush) {
      std::fflush(f);
    }
  }
  validatedHoleFilling_idx_0 = X.t_0;
  if (fid == 0.0) {
    g_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(fid, autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "%f\n", validatedHoleFilling_idx_0);
    if (autoflush) {
      std::fflush(f);
    }
  }
  if (fid == 0.0) {
    g_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(fid, autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "%s\n", "----------------------------------------");
    if (autoflush) {
      std::fflush(f);
    }
  }
  if (fid == 0.0) {
    g_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(fid, autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "%s\n", "Pulse Listing:");
    if (autoflush) {
      std::fflush(f);
    }
  }
  i = X.ps_pos->pl.size(1) - 1;
  for (int b_i{0}; b_i <= i; b_i++) {
    loop_ub = X.ps_pos->pl.size(1);
    if (b_i + 1 > loop_ub) {
      rtDynamicBoundsError(b_i + 1, 1, loop_ub, ab_emlrtBCI);
    }
    validatedHoleFilling_idx_0 = X.ps_pos->pl[b_i].t_0;
    if (fid == 0.0) {
      g_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
    }
    f = coder::internal::getfilestar(fid, autoflush);
    if (f == nullptr) {
      c_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
    } else {
      std::fprintf(f, "%f,", validatedHoleFilling_idx_0);
      if (autoflush) {
        std::fflush(f);
      }
    }
  }
  if (fid == 0.0) {
    g_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(fid, autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "\n");
    if (autoflush) {
      std::fflush(f);
    }
  }
  i = X.ps_pos->pl.size(1) - 1;
  for (int b_i{0}; b_i <= i; b_i++) {
    loop_ub = X.ps_pos->pl.size(1);
    if (b_i + 1 > loop_ub) {
      rtDynamicBoundsError(b_i + 1, 1, loop_ub, bb_emlrtBCI);
    }
    validatedHoleFilling_idx_0 = X.ps_pos->pl[b_i].fp / 1.0E+6 + radioFcMHz;
    if (fid == 0.0) {
      g_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
    }
    f = coder::internal::getfilestar(fid, autoflush);
    if (f == nullptr) {
      c_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
    } else {
      std::fprintf(f, "%f,", validatedHoleFilling_idx_0);
      if (autoflush) {
        std::fflush(f);
      }
    }
  }
  if (fid == 0.0) {
    g_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(fid, autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "\n");
    if (autoflush) {
      std::fflush(f);
    }
  }
  i = X.ps_pos->pl.size(1) - 1;
  for (int b_i{0}; b_i <= i; b_i++) {
    loop_ub = X.ps_pos->pl.size(1);
    if (b_i + 1 > loop_ub) {
      rtDynamicBoundsError(b_i + 1, 1, loop_ub, cb_emlrtBCI);
    }
    validatedHoleFilling_idx_0 = X.ps_pos->pl[b_i].SNR;
    if (fid == 0.0) {
      g_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
    }
    f = coder::internal::getfilestar(fid, autoflush);
    if (f == nullptr) {
      c_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
    } else {
      std::fprintf(f, "%f,", validatedHoleFilling_idx_0);
      if (autoflush) {
        std::fflush(f);
      }
    }
  }
  if (fid == 0.0) {
    g_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(fid, autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "\n");
    if (autoflush) {
      std::fflush(f);
    }
  }
  i = X.ps_pos->pl.size(1) - 1;
  for (int b_i{0}; b_i <= i; b_i++) {
    loop_ub = X.ps_pos->pl.size(1);
    if (b_i + 1 > loop_ub) {
      rtDynamicBoundsError(b_i + 1, 1, loop_ub, db_emlrtBCI);
    }
    fileid = static_cast<signed char>(X.ps_pos->pl[b_i].con_dec);
    if (fid == 0.0) {
      g_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
    }
    f = coder::internal::getfilestar(fid, autoflush);
    if (f == nullptr) {
      c_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
    } else {
      std::fprintf(f, "%u,", static_cast<unsigned char>(fileid));
      if (autoflush) {
        std::fflush(f);
      }
    }
  }
  if (fid == 0.0) {
    g_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(fid, autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "\n%s\n", "----------------------------------------");
    if (autoflush) {
      std::fflush(f);
    }
  }
  if (fid == 0.0) {
    g_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(fid, autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "%s\n", "Spectrogram Frequencies (MHz):");
    if (autoflush) {
      std::fflush(f);
    }
  }
  i = X.stft->f.size(0) - 1;
  for (int b_i{0}; b_i <= i; b_i++) {
    loop_ub = X.stft->f.size(0);
    if (b_i + 1 > loop_ub) {
      rtDynamicBoundsError(b_i + 1, 1, loop_ub, eb_emlrtBCI);
    }
    validatedHoleFilling_idx_0 = X.stft->f[b_i] / 1.0E+6 + radioFcMHz;
    if (fid == 0.0) {
      g_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
    }
    f = coder::internal::getfilestar(fid, autoflush);
    if (f == nullptr) {
      c_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
    } else {
      std::fprintf(f, "%f,", validatedHoleFilling_idx_0);
      if (autoflush) {
        std::fflush(f);
      }
    }
  }
  if (fid == 0.0) {
    g_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(fid, autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "\n%s\n", "----------------------------------------");
    if (autoflush) {
      std::fflush(f);
    }
  }
  if (fid == 0.0) {
    g_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(fid, autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "%s\n", "Spectrogram Times (s):");
    if (autoflush) {
      std::fflush(f);
    }
  }
  i = X.stft->t.size(0) - 1;
  for (int b_i{0}; b_i <= i; b_i++) {
    loop_ub = X.stft->t.size(0);
    if (b_i + 1 > loop_ub) {
      rtDynamicBoundsError(b_i + 1, 1, loop_ub, fb_emlrtBCI);
    }
    validatedHoleFilling_idx_0 = X.stft->t[b_i];
    if (fid == 0.0) {
      g_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
    }
    f = coder::internal::getfilestar(fid, autoflush);
    if (f == nullptr) {
      c_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
    } else {
      std::fprintf(f, "%f,", validatedHoleFilling_idx_0);
      if (autoflush) {
        std::fflush(f);
      }
    }
  }
  if (fid == 0.0) {
    g_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(fid, autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "\n%s\n", "----------------------------------------");
    if (autoflush) {
      std::fflush(f);
    }
  }
  if (fid == 0.0) {
    g_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(fid, autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "%s\n", "Spectrogram Values (|STFT|):");
    if (autoflush) {
      std::fflush(f);
    }
  }
  i = X.stft->S.size(0) * X.stft->S.size(1) - 1;
  for (int b_i{0}; b_i <= i; b_i++) {
    double x_im;
    loop_ub = X.stft->S.size(0) * X.stft->S.size(1);
    if ((static_cast<int>(static_cast<unsigned int>(b_i) + 1U) < 1) ||
        (static_cast<int>(static_cast<unsigned int>(b_i) + 1U) > loop_ub)) {
      rtDynamicBoundsError(
          static_cast<int>(static_cast<unsigned int>(b_i) + 1U), 1, loop_ub,
          gb_emlrtBCI);
    }
    validatedHoleFilling_idx_0 = X.stft->S[b_i].re;
    loop_ub = X.stft->S.size(0) * X.stft->S.size(1);
    if ((static_cast<int>(static_cast<unsigned int>(b_i) + 1U) < 1) ||
        (static_cast<int>(static_cast<unsigned int>(b_i) + 1U) > loop_ub)) {
      rtDynamicBoundsError(
          static_cast<int>(static_cast<unsigned int>(b_i) + 1U), 1, loop_ub,
          gb_emlrtBCI);
    }
    x_im = X.stft->S[b_i].im;
    if (fid == 0.0) {
      g_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
    }
    f = coder::internal::getfilestar(fid, autoflush);
    if (f == nullptr) {
      c_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
    } else {
      std::fprintf(f, "%f,", rt_hypotd_snf(validatedHoleFilling_idx_0, x_im));
      if (autoflush) {
        std::fflush(f);
      }
    }
  }
  if (fid == 0.0) {
    g_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(fid, autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "\n");
    if (autoflush) {
      std::fflush(f);
    }
  }
  // fclose(fid);
  //  for i = 1:numel(X.x)
  //      fprintf(fid,'%f,', real(X.x(i)));
  //  end
  //  fprintf(fid, '\n');
  //  for i = 1:numel(X.x)
  //      fprintf(fid, '%f,', imag(X.x(i)));
  //  end
  //  for i = 1:numel(X.stft.S)
  //      fprintf(fid, '%f,', real(X.stft.S(i)));
  //  end
  //  fprintf(fid, '\n');
  //  for i = 1:numel(X.stft.S)
  //      fprintf(fid, '%f,', imag(X.stft.S(i)));
  //  end
}

//
// UNTITLED Summary of this function goes here
//    Detailed explanation goes here
//
// Arguments    : void
// Return Type  : void
//
void wfmcsvwrite_init()
{
  fid_not_empty = false;
}

//
// File trailer for wfmcsvwrite.cpp
//
// [EOF]
//
