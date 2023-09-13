//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: wfmcsvwrite.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 13-Sep-2023 13:30:23
//

// Include Files
#include "wfmcsvwrite.h"
#include "fileManager.h"
#include "pulsestats.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_internal_types.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "waveform.h"
#include "wfmstft.h"
#include "coder_array.h"
#include <cstdio>

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
  static rtBoundsCheckInfo ab_emlrtBCI{
      -1,            // iFirst
      -1,            // iLast
      16,            // lineNo
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
      20,            // lineNo
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
      24,            // lineNo
      47,            // colNo
      "X.ps_pos.pl", // aName
      "wfmcsvwrite", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/wfmcsvwrite.m", // pName
      0                                                // checkKind
  };
  static rtBoundsCheckInfo db_emlrtBCI{
      -1,            // iFirst
      -1,            // iLast
      30,            // lineNo
      34,            // colNo
      "X.stft.f",    // aName
      "wfmcsvwrite", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/wfmcsvwrite.m", // pName
      0                                                // checkKind
  };
  static rtBoundsCheckInfo eb_emlrtBCI{
      -1,            // iFirst
      -1,            // iLast
      35,            // lineNo
      34,            // colNo
      "X.stft.t",    // aName
      "wfmcsvwrite", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/wfmcsvwrite.m", // pName
      0                                                // checkKind
  };
  static rtBoundsCheckInfo fb_emlrtBCI{
      -1,            // iFirst
      -1,            // iLast
      40,            // lineNo
      38,            // colNo
      "X.stft.S",    // aName
      "wfmcsvwrite", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/wfmcsvwrite.m", // pName
      0                                                // checkKind
  };
  static rtBoundsCheckInfo y_emlrtBCI{
      -1,            // iFirst
      -1,            // iLast
      12,            // lineNo
      41,            // colNo
      "X.ps_pos.pl", // aName
      "wfmcsvwrite", // fName
      "/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/"
      "CODE_PLAYGROUND/uavrt_detection/wfmcsvwrite.m", // pName
      0                                                // checkKind
  };
  std::FILE *f;
  double validatedHoleFilling_idx_0;
  int i;
  int i1;
  signed char fileid;
  boolean_T autoflush;
  fileid = coder::internal::cfopen(filePath, "wb");
  if (fileid == 0) {
    g_rtErrorWithMessageID(nc_emlrtRTEI.fName, nc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(static_cast<double>(fileid), autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "%s\n", "----------------------------------------");
    if (autoflush) {
      std::fflush(f);
    }
  }
  if (fileid == 0) {
    g_rtErrorWithMessageID(nc_emlrtRTEI.fName, nc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(static_cast<double>(fileid), autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "%s\n", "Record Start Time (s):");
    if (autoflush) {
      std::fflush(f);
    }
  }
  validatedHoleFilling_idx_0 = X.t_0;
  if (fileid == 0) {
    g_rtErrorWithMessageID(nc_emlrtRTEI.fName, nc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(static_cast<double>(fileid), autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "%f\n", validatedHoleFilling_idx_0);
    if (autoflush) {
      std::fflush(f);
    }
  }
  if (fileid == 0) {
    g_rtErrorWithMessageID(nc_emlrtRTEI.fName, nc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(static_cast<double>(fileid), autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "%s\n", "----------------------------------------");
    if (autoflush) {
      std::fflush(f);
    }
  }
  if (fileid == 0) {
    g_rtErrorWithMessageID(nc_emlrtRTEI.fName, nc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(static_cast<double>(fileid), autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "%s\n", "Pulse Listing:");
    if (autoflush) {
      std::fflush(f);
    }
  }
  i = X.ps_pos->pl.size(1) - 1;
  for (int b_i{0}; b_i <= i; b_i++) {
    i1 = X.ps_pos->pl.size(1);
    if (b_i + 1 > i1) {
      rtDynamicBoundsError(b_i + 1, 1, i1, y_emlrtBCI);
    }
    validatedHoleFilling_idx_0 = X.ps_pos->pl[b_i].t_0;
    if (fileid == 0) {
      g_rtErrorWithMessageID(nc_emlrtRTEI.fName, nc_emlrtRTEI.lineNo);
    }
    f = coder::internal::getfilestar(static_cast<double>(fileid), autoflush);
    if (f == nullptr) {
      c_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
    } else {
      std::fprintf(f, "%f,", validatedHoleFilling_idx_0);
      if (autoflush) {
        std::fflush(f);
      }
    }
  }
  if (fileid == 0) {
    g_rtErrorWithMessageID(nc_emlrtRTEI.fName, nc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(static_cast<double>(fileid), autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "\n");
    if (autoflush) {
      std::fflush(f);
    }
  }
  i = X.ps_pos->pl.size(1) - 1;
  for (int b_i{0}; b_i <= i; b_i++) {
    i1 = X.ps_pos->pl.size(1);
    if (b_i + 1 > i1) {
      rtDynamicBoundsError(b_i + 1, 1, i1, ab_emlrtBCI);
    }
    validatedHoleFilling_idx_0 = X.ps_pos->pl[b_i].fp / 1.0E+6 + radioFcMHz;
    if (fileid == 0) {
      g_rtErrorWithMessageID(nc_emlrtRTEI.fName, nc_emlrtRTEI.lineNo);
    }
    f = coder::internal::getfilestar(static_cast<double>(fileid), autoflush);
    if (f == nullptr) {
      c_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
    } else {
      std::fprintf(f, "%f,", validatedHoleFilling_idx_0);
      if (autoflush) {
        std::fflush(f);
      }
    }
  }
  if (fileid == 0) {
    g_rtErrorWithMessageID(nc_emlrtRTEI.fName, nc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(static_cast<double>(fileid), autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "\n");
    if (autoflush) {
      std::fflush(f);
    }
  }
  i = X.ps_pos->pl.size(1) - 1;
  for (int b_i{0}; b_i <= i; b_i++) {
    i1 = X.ps_pos->pl.size(1);
    if (b_i + 1 > i1) {
      rtDynamicBoundsError(b_i + 1, 1, i1, bb_emlrtBCI);
    }
    validatedHoleFilling_idx_0 = X.ps_pos->pl[b_i].SNR;
    if (fileid == 0) {
      g_rtErrorWithMessageID(nc_emlrtRTEI.fName, nc_emlrtRTEI.lineNo);
    }
    f = coder::internal::getfilestar(static_cast<double>(fileid), autoflush);
    if (f == nullptr) {
      c_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
    } else {
      std::fprintf(f, "%f,", validatedHoleFilling_idx_0);
      if (autoflush) {
        std::fflush(f);
      }
    }
  }
  if (fileid == 0) {
    g_rtErrorWithMessageID(nc_emlrtRTEI.fName, nc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(static_cast<double>(fileid), autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "\n");
    if (autoflush) {
      std::fflush(f);
    }
  }
  i = X.ps_pos->pl.size(1) - 1;
  for (int b_i{0}; b_i <= i; b_i++) {
    signed char b_validatedHoleFilling_idx_0;
    i1 = X.ps_pos->pl.size(1);
    if (b_i + 1 > i1) {
      rtDynamicBoundsError(b_i + 1, 1, i1, cb_emlrtBCI);
    }
    b_validatedHoleFilling_idx_0 =
        static_cast<signed char>(X.ps_pos->pl[b_i].con_dec);
    if (fileid == 0) {
      g_rtErrorWithMessageID(nc_emlrtRTEI.fName, nc_emlrtRTEI.lineNo);
    }
    f = coder::internal::getfilestar(static_cast<double>(fileid), autoflush);
    if (f == nullptr) {
      c_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
    } else {
      std::fprintf(f, "%u,",
                   static_cast<unsigned char>(b_validatedHoleFilling_idx_0));
      if (autoflush) {
        std::fflush(f);
      }
    }
  }
  if (fileid == 0) {
    g_rtErrorWithMessageID(nc_emlrtRTEI.fName, nc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(static_cast<double>(fileid), autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "\n%s\n", "----------------------------------------");
    if (autoflush) {
      std::fflush(f);
    }
  }
  if (fileid == 0) {
    g_rtErrorWithMessageID(nc_emlrtRTEI.fName, nc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(static_cast<double>(fileid), autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "%s\n", "Spectrogram Frequencies (MHz):");
    if (autoflush) {
      std::fflush(f);
    }
  }
  i = X.stft->f.size(0) - 1;
  for (int b_i{0}; b_i <= i; b_i++) {
    i1 = X.stft->f.size(0);
    if (b_i + 1 > i1) {
      rtDynamicBoundsError(b_i + 1, 1, i1, db_emlrtBCI);
    }
    validatedHoleFilling_idx_0 = X.stft->f[b_i] / 1.0E+6 + radioFcMHz;
    if (fileid == 0) {
      g_rtErrorWithMessageID(nc_emlrtRTEI.fName, nc_emlrtRTEI.lineNo);
    }
    f = coder::internal::getfilestar(static_cast<double>(fileid), autoflush);
    if (f == nullptr) {
      c_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
    } else {
      std::fprintf(f, "%f,", validatedHoleFilling_idx_0);
      if (autoflush) {
        std::fflush(f);
      }
    }
  }
  if (fileid == 0) {
    g_rtErrorWithMessageID(nc_emlrtRTEI.fName, nc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(static_cast<double>(fileid), autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "\n%s\n", "----------------------------------------");
    if (autoflush) {
      std::fflush(f);
    }
  }
  if (fileid == 0) {
    g_rtErrorWithMessageID(nc_emlrtRTEI.fName, nc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(static_cast<double>(fileid), autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "%s\n", "Spectrogram Times (s):");
    if (autoflush) {
      std::fflush(f);
    }
  }
  i = X.stft->t.size(0) - 1;
  for (int b_i{0}; b_i <= i; b_i++) {
    i1 = X.stft->t.size(0);
    if (b_i + 1 > i1) {
      rtDynamicBoundsError(b_i + 1, 1, i1, eb_emlrtBCI);
    }
    validatedHoleFilling_idx_0 = X.stft->t[b_i];
    if (fileid == 0) {
      g_rtErrorWithMessageID(nc_emlrtRTEI.fName, nc_emlrtRTEI.lineNo);
    }
    f = coder::internal::getfilestar(static_cast<double>(fileid), autoflush);
    if (f == nullptr) {
      c_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
    } else {
      std::fprintf(f, "%f,", validatedHoleFilling_idx_0);
      if (autoflush) {
        std::fflush(f);
      }
    }
  }
  if (fileid == 0) {
    g_rtErrorWithMessageID(nc_emlrtRTEI.fName, nc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(static_cast<double>(fileid), autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "\n%s\n", "----------------------------------------");
    if (autoflush) {
      std::fflush(f);
    }
  }
  if (fileid == 0) {
    g_rtErrorWithMessageID(nc_emlrtRTEI.fName, nc_emlrtRTEI.lineNo);
  }
  f = coder::internal::getfilestar(static_cast<double>(fileid), autoflush);
  if (f == nullptr) {
    c_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
  } else {
    std::fprintf(f, "%s\n", "Spectrogram Values (|STFT|):");
    if (autoflush) {
      std::fflush(f);
    }
  }
  i = X.stft->S.size(0) * X.stft->S.size(1) - 1;
  for (int b_i{0}; b_i <= i; b_i++) {
    double x_im;
    i1 = X.stft->S.size(0) * X.stft->S.size(1);
    if ((static_cast<int>(static_cast<unsigned int>(b_i) + 1U) < 1) ||
        (static_cast<int>(static_cast<unsigned int>(b_i) + 1U) > i1)) {
      rtDynamicBoundsError(
          static_cast<int>(static_cast<unsigned int>(b_i) + 1U), 1, i1,
          fb_emlrtBCI);
    }
    validatedHoleFilling_idx_0 = X.stft->S[b_i].re;
    i1 = X.stft->S.size(0) * X.stft->S.size(1);
    if ((static_cast<int>(static_cast<unsigned int>(b_i) + 1U) < 1) ||
        (static_cast<int>(static_cast<unsigned int>(b_i) + 1U) > i1)) {
      rtDynamicBoundsError(
          static_cast<int>(static_cast<unsigned int>(b_i) + 1U), 1, i1,
          fb_emlrtBCI);
    }
    x_im = X.stft->S[b_i].im;
    if (fileid == 0) {
      g_rtErrorWithMessageID(nc_emlrtRTEI.fName, nc_emlrtRTEI.lineNo);
    }
    f = coder::internal::getfilestar(static_cast<double>(fileid), autoflush);
    if (f == nullptr) {
      c_rtErrorWithMessageID(oc_emlrtRTEI.fName, oc_emlrtRTEI.lineNo);
    } else {
      std::fprintf(f, "%f,", rt_hypotd_snf(validatedHoleFilling_idx_0, x_im));
      if (autoflush) {
        std::fflush(f);
      }
    }
  }
  coder::internal::cfclose(static_cast<double>(fileid));
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
// File trailer for wfmcsvwrite.cpp
//
// [EOF]
//
