//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: fgetl.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 23-Mar-2023 12:56:08
//

// Include Files
#include "fgetl.h"
#include "eml_int_forloop_overflow_check.h"
#include "fileManager.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include "omp.h"
#include "stdio.h"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <stdio.h>
#include <string.h>
#include <string>

// Function Declarations
static void f_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void rtErrorWithMessageID(const int i, const char *aFcnName,
                                 int aLineNum);

// Function Definitions
//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void f_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream
      << "File has nothing left to read. To avoid this error, call \'feof\' to "
         "check if you have reached the end of the file before using \'f"
         "gets\' or \'fgetl\'.";
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
// Arguments    : const int i
//                const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void rtErrorWithMessageID(const int i, const char *aFcnName,
                                 int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((outStream << "Read illegal non-ASCII character with integer value ") << i)
      << ". For code generation, all characters must have value less than 128.";
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
// Arguments    : double fileID
//                ::coder::array<char, 2U> &out
// Return Type  : void
//
namespace coder {
void fgetl(double fileID, ::coder::array<char, 2U> &out)
{
  static rtRunTimeErrorInfo ad_emlrtRTEI{
      122,     // lineNo
      "cFgets" // fName
  };
  static rtRunTimeErrorInfo bd_emlrtRTEI{
      143,     // lineNo
      "cFgets" // fName
  };
  static rtRunTimeErrorInfo wc_emlrtRTEI{
      104,     // lineNo
      "cFgets" // fName
  };
  static rtRunTimeErrorInfo xc_emlrtRTEI{
      249,          // lineNo
      "getFileStar" // fName
  };
  static rtRunTimeErrorInfo yc_emlrtRTEI{
      72,     // lineNo
      "fread" // fName
  };
  FILE *b_filestar;
  FILE *filestar;
  int b_i;
  int i;
  int i1;
  int i3;
  int reachedEndOfFile;
  boolean_T newLineAfterCarriageReturn;
  getfilestar(fileID, &filestar, &newLineAfterCarriageReturn);
  if (filestar == NULL) {
    c_rtErrorWithMessageID(xc_emlrtRTEI.fName, xc_emlrtRTEI.lineNo);
  }
  if ((!(fileID != 0.0)) || (!(fileID != 1.0)) || (!(fileID != 2.0))) {
    filestar = NULL;
  }
  out.set_size(1, 0);
  if (!(filestar == NULL)) {
    FILE *b_NULL;
    char *cOut;
    int exitg1;
    int st;
    int wherefrom;
    char ReadBuff[1024];
    boolean_T readNewline;
    do {
      exitg1 = 0;
      cOut = fgets(&ReadBuff[0], 1024, filestar);
      readNewline = false;
      b_NULL = NULL;
      getfilestar(fileID, &b_filestar, &newLineAfterCarriageReturn);
      if (b_filestar == b_NULL) {
        c_rtErrorWithMessageID(c_emlrtRTEI.fName, c_emlrtRTEI.lineNo);
      } else {
        st = feof(b_filestar);
        reachedEndOfFile = ((int)st != 0);
      }
      if ((cOut == NULL) && (out.size(1) == 0)) {
        f_rtErrorWithMessageID(wc_emlrtRTEI.fName, wc_emlrtRTEI.lineNo);
      }
      if (cOut == NULL) {
        exitg1 = 1;
      } else {
        int carriageReturnAt;
        int idx;
        boolean_T fileEndAfterCarriageReturn;
        idx = 0;
        carriageReturnAt = 0;
        if (reachedEndOfFile != 0) {
          boolean_T exitg2;
          i = 0;
          exitg2 = false;
          while ((!exitg2) && (i < 1024)) {
            if (ReadBuff[i] == '\x00') {
              idx = i;
              exitg2 = true;
            } else {
              if ((carriageReturnAt == 0) &&
                  (static_cast<unsigned char>(ReadBuff[i]) > 127)) {
                rtErrorWithMessageID(
                    static_cast<int>(static_cast<unsigned char>(ReadBuff[i])),
                    ad_emlrtRTEI.fName, ad_emlrtRTEI.lineNo);
              }
              if ((carriageReturnAt == 0) && (ReadBuff[i] == '\x0d')) {
                carriageReturnAt = i + 1;
              }
              i++;
            }
          }
          if (ReadBuff[idx] == '\x00') {
            idx--;
          }
        } else {
          boolean_T exitg2;
          i = 0;
          exitg2 = false;
          while ((!exitg2) && (i < 1025)) {
            if (i + 1 > 1024) {
              idx = 1022;
              exitg2 = true;
            } else if (ReadBuff[i] == '\x0a') {
              idx = i;
              exitg2 = true;
            } else {
              if ((carriageReturnAt == 0) &&
                  (static_cast<unsigned char>(ReadBuff[i]) > 127)) {
                rtErrorWithMessageID(
                    static_cast<int>(static_cast<unsigned char>(ReadBuff[i])),
                    bd_emlrtRTEI.fName, bd_emlrtRTEI.lineNo);
              }
              if ((carriageReturnAt == 0) && (ReadBuff[i] == '\x0d')) {
                carriageReturnAt = i + 1;
              }
              i++;
            }
          }
          readNewline = (ReadBuff[idx] == '\x0a');
        }
        if ((carriageReturnAt > 0) && (carriageReturnAt < 1024)) {
          newLineAfterCarriageReturn = (ReadBuff[carriageReturnAt] == '\x0a');
          if ((reachedEndOfFile != 0) &&
              (ReadBuff[carriageReturnAt] == '\x00')) {
            fileEndAfterCarriageReturn = true;
          } else {
            fileEndAfterCarriageReturn = false;
          }
        } else {
          newLineAfterCarriageReturn = false;
          fileEndAfterCarriageReturn = false;
        }
        if ((carriageReturnAt == 0) || newLineAfterCarriageReturn ||
            fileEndAfterCarriageReturn) {
          if (idx + 1 < 1) {
            i = 0;
          } else {
            i = idx + 1;
          }
          b_i = out.size(1);
          out.set_size(out.size(0), out.size(1) + i);
          for (int i2{0}; i2 < i; i2++) {
            out[b_i + i2] = ReadBuff[i2];
          }
        } else {
          b_i = out.size(1);
          out.set_size(out.size(0), out.size(1) + carriageReturnAt);
          for (int i2{0}; i2 < carriageReturnAt; i2++) {
            out[b_i + i2] = ReadBuff[i2];
          }
          wherefrom = SEEK_CUR;
          getfilestar(fileID, &b_filestar, &newLineAfterCarriageReturn);
          if (b_filestar == NULL) {
            c_rtErrorWithMessageID(d_emlrtRTEI.fName, d_emlrtRTEI.lineNo);
          }
          if ((!(fileID != 0.0)) || (!(fileID != 1.0)) || (!(fileID != 2.0))) {
            b_filestar = NULL;
          }
          if (!(b_filestar == NULL)) {
            fseek(b_filestar, (long int)((carriageReturnAt - idx) - 1),
                  wherefrom);
          }
        }
        if (readNewline || (reachedEndOfFile != 0) || (carriageReturnAt > 0)) {
          exitg1 = 1;
        }
      }
    } while (exitg1 == 0);
    b_NULL = NULL;
    getfilestar(fileID, &filestar, &newLineAfterCarriageReturn);
    if (filestar == b_NULL) {
      c_rtErrorWithMessageID(c_emlrtRTEI.fName, c_emlrtRTEI.lineNo);
    } else {
      st = feof(filestar);
      i1 = ((int)st != 0);
    }
    if (i1 == 0) {
      if ((!(fileID != 0.0)) || (!(fileID != 1.0)) || (!(fileID != 2.0))) {
        g_rtErrorWithMessageID(yc_emlrtRTEI.fName, yc_emlrtRTEI.lineNo);
      }
      getfilestar(fileID, &filestar, &newLineAfterCarriageReturn);
      if (filestar == NULL) {
        c_rtErrorWithMessageID(xc_emlrtRTEI.fName, xc_emlrtRTEI.lineNo);
      }
      if ((!(fileID != 0.0)) || (!(fileID != 1.0)) || (!(fileID != 2.0))) {
        filestar = NULL;
      }
      if (!(filestar == NULL)) {
        size_t numReadSizeT;
        unsigned char buf;
        numReadSizeT = fread(&buf, sizeof(unsigned char), (size_t)1, filestar);
        if ((int)numReadSizeT > 2147483646) {
          check_forloop_overflow_error();
        }
      }
      b_NULL = NULL;
      getfilestar(fileID, &filestar, &newLineAfterCarriageReturn);
      if (filestar == b_NULL) {
        c_rtErrorWithMessageID(c_emlrtRTEI.fName, c_emlrtRTEI.lineNo);
      } else {
        st = feof(filestar);
        i3 = ((int)st != 0);
      }
      if (i3 == 0) {
        wherefrom = SEEK_CUR;
        getfilestar(fileID, &filestar, &newLineAfterCarriageReturn);
        if (filestar == NULL) {
          c_rtErrorWithMessageID(d_emlrtRTEI.fName, d_emlrtRTEI.lineNo);
        }
        if ((!(fileID != 0.0)) || (!(fileID != 1.0)) || (!(fileID != 2.0))) {
          filestar = NULL;
        }
        if (!(filestar == NULL)) {
          fseek(filestar, (long int)-1.0, wherefrom);
        }
      }
    }
  }
  if (out.size(1) != 0) {
    if (out[out.size(1) - 1] == '\x0a') {
      if ((out.size(1) > 1) && (out[out.size(1) - 2] == '\x0d')) {
        if (out.size(1) - 2 < 1) {
          i = 0;
        } else {
          i = out.size(1) - 2;
        }
        for (b_i = 0; b_i < i; b_i++) {
          out[b_i] = out[b_i];
        }
        out.set_size(1, i);
      } else {
        if (out.size(1) - 1 < 1) {
          i = 0;
        } else {
          i = out.size(1) - 1;
        }
        for (b_i = 0; b_i < i; b_i++) {
          out[b_i] = out[b_i];
        }
        out.set_size(1, i);
      }
    } else if (out[out.size(1) - 1] == '\x0d') {
      if (out.size(1) - 1 < 1) {
        i = 0;
      } else {
        i = out.size(1) - 1;
      }
      for (b_i = 0; b_i < i; b_i++) {
        out[b_i] = out[b_i];
      }
      out.set_size(1, i);
    }
  }
}

} // namespace coder

//
// File trailer for fgetl.cpp
//
// [EOF]
//
