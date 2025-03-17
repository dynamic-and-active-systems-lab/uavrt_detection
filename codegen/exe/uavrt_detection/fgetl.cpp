//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: fgetl.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
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
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>

// Function Declarations
static void d_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void rtErrorWithMessageID(const int i, const char *aFcnName,
                                 int aLineNum);

// Function Definitions
//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void d_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream
      << "File has nothing left to read. To avoid this error, call \'feof\' to "
         "check if you have reached the end of the file before using "
         "\'fgets\' or \'fgetl\'.";
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
//                array<char, 2U> &out
// Return Type  : void
//
namespace coder {
void fgetl(double fileID, array<char, 2U> &out)
{
  static rtRunTimeErrorInfo rc_emlrtRTEI{
      253,          // lineNo
      "getFileStar" // fName
  };
  static rtRunTimeErrorInfo sc_emlrtRTEI{
      106,     // lineNo
      "cFgets" // fName
  };
  static rtRunTimeErrorInfo tc_emlrtRTEI{
      72,     // lineNo
      "fread" // fName
  };
  static rtRunTimeErrorInfo uc_emlrtRTEI{
      124,     // lineNo
      "cFgets" // fName
  };
  static rtRunTimeErrorInfo vc_emlrtRTEI{
      145,     // lineNo
      "cFgets" // fName
  };
  std::FILE *b_filestar;
  std::FILE *f;
  std::FILE *filestar;
  int b_i;
  int i;
  int i1;
  int i2;
  int loop_ub;
  int reachedEndOfFile;
  boolean_T newLineAfterCarriageReturn;
  f = internal::getfilestar(fileID, newLineAfterCarriageReturn);
  filestar = f;
  if (f == nullptr) {
    c_rtErrorWithMessageID(rc_emlrtRTEI.fName, rc_emlrtRTEI.lineNo);
  }
  if ((!(fileID != 0.0)) || (!(fileID != 1.0)) || (!(fileID != 2.0))) {
    filestar = nullptr;
  }
  out.set_size(1, 0);
  if (!(filestar == nullptr)) {
    char *cOut;
    int st;
    int exitg1;
    char ReadBuff[1024];
    unsigned char buf;
    boolean_T readNewline;
    do {
      exitg1 = 0;
      cOut = std::fgets(&ReadBuff[0], 1024, filestar);
      readNewline = false;
      f = internal::getfilestar(fileID, newLineAfterCarriageReturn);
      if (f == nullptr) {
        c_rtErrorWithMessageID(c_emlrtRTEI.fName, c_emlrtRTEI.lineNo);
      } else {
        st = std::feof(f);
        reachedEndOfFile = ((int)st != 0);
      }
      if ((cOut == nullptr) && (out.size(1) == 0)) {
        d_rtErrorWithMessageID(sc_emlrtRTEI.fName, sc_emlrtRTEI.lineNo);
      }
      if (cOut == nullptr) {
        exitg1 = 1;
      } else {
        int carriageReturnAt;
        int idx;
        boolean_T fileEndAfterCarriageReturn;
        idx = 0;
        carriageReturnAt = 0;
        if (reachedEndOfFile != 0) {
          boolean_T exitg2;
          b_i = 0;
          exitg2 = false;
          while ((!exitg2) && (b_i < 1024)) {
            if (ReadBuff[b_i] == '\x00') {
              idx = b_i;
              exitg2 = true;
            } else {
              if (carriageReturnAt == 0) {
                buf = static_cast<unsigned char>(ReadBuff[b_i]);
                if (buf > 127) {
                  rtErrorWithMessageID(static_cast<int>(buf),
                                       uc_emlrtRTEI.fName, uc_emlrtRTEI.lineNo);
                }
              }
              if ((carriageReturnAt == 0) && (ReadBuff[b_i] == '\r')) {
                carriageReturnAt = b_i + 1;
              }
              b_i++;
            }
          }
          if (ReadBuff[idx] == '\x00') {
            idx--;
          }
        } else {
          boolean_T exitg2;
          b_i = 0;
          exitg2 = false;
          while ((!exitg2) && (b_i < 1025)) {
            if (b_i + 1 > 1024) {
              idx = 1022;
              exitg2 = true;
            } else if (ReadBuff[b_i] == '\n') {
              idx = b_i;
              exitg2 = true;
            } else {
              if (carriageReturnAt == 0) {
                buf = static_cast<unsigned char>(ReadBuff[b_i]);
                if (buf > 127) {
                  rtErrorWithMessageID(static_cast<int>(buf),
                                       vc_emlrtRTEI.fName, vc_emlrtRTEI.lineNo);
                }
              }
              if ((carriageReturnAt == 0) && (ReadBuff[b_i] == '\r')) {
                carriageReturnAt = b_i + 1;
              }
              b_i++;
            }
          }
          readNewline = (ReadBuff[idx] == '\n');
        }
        if ((carriageReturnAt > 0) && (carriageReturnAt < 1024)) {
          newLineAfterCarriageReturn = (ReadBuff[carriageReturnAt] == '\n');
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
          loop_ub = idx + 1;
          i = out.size(1);
          out.set_size(out.size(0), (out.size(1) + idx) + 1);
          for (b_i = 0; b_i < loop_ub; b_i++) {
            out[i + b_i] = ReadBuff[b_i];
          }
        } else {
          i = out.size(1);
          out.set_size(out.size(0), out.size(1) + carriageReturnAt);
          for (b_i = 0; b_i < carriageReturnAt; b_i++) {
            out[i + b_i] = ReadBuff[b_i];
          }
          f = internal::getfilestar(fileID, newLineAfterCarriageReturn);
          b_filestar = f;
          if (f == nullptr) {
            c_rtErrorWithMessageID(b_emlrtRTEI.fName, b_emlrtRTEI.lineNo);
          }
          if ((!(fileID != 0.0)) || (!(fileID != 1.0)) || (!(fileID != 2.0))) {
            b_filestar = nullptr;
          }
          if (!(b_filestar == nullptr)) {
            std::fseek(b_filestar, (long int)((carriageReturnAt - idx) - 1),
                       SEEK_CUR);
          }
        }
        if (readNewline || (reachedEndOfFile != 0) || (carriageReturnAt > 0)) {
          exitg1 = 1;
        }
      }
    } while (exitg1 == 0);
    f = internal::getfilestar(fileID, newLineAfterCarriageReturn);
    if (f == nullptr) {
      c_rtErrorWithMessageID(c_emlrtRTEI.fName, c_emlrtRTEI.lineNo);
    } else {
      st = std::feof(f);
      i1 = ((int)st != 0);
    }
    if (i1 == 0) {
      if ((!(fileID != 0.0)) || (!(fileID != 1.0)) || (!(fileID != 2.0))) {
        e_rtErrorWithMessageID(tc_emlrtRTEI.fName, tc_emlrtRTEI.lineNo);
      }
      f = internal::getfilestar(fileID, newLineAfterCarriageReturn);
      filestar = f;
      if (f == nullptr) {
        c_rtErrorWithMessageID(rc_emlrtRTEI.fName, rc_emlrtRTEI.lineNo);
      }
      if ((!(fileID != 0.0)) || (!(fileID != 1.0)) || (!(fileID != 2.0))) {
        filestar = nullptr;
      }
      if (!(filestar == nullptr)) {
        size_t numReadSizeT;
        numReadSizeT =
            std::fread(&buf, sizeof(unsigned char), (size_t)1, filestar);
        if ((int)numReadSizeT > 2147483646) {
          check_forloop_overflow_error();
        }
      }
      f = internal::getfilestar(fileID, newLineAfterCarriageReturn);
      if (f == nullptr) {
        c_rtErrorWithMessageID(c_emlrtRTEI.fName, c_emlrtRTEI.lineNo);
      } else {
        st = std::feof(f);
        i2 = ((int)st != 0);
      }
      if (i2 == 0) {
        f = internal::getfilestar(fileID, newLineAfterCarriageReturn);
        filestar = f;
        if (f == nullptr) {
          c_rtErrorWithMessageID(b_emlrtRTEI.fName, b_emlrtRTEI.lineNo);
        }
        if ((!(fileID != 0.0)) || (!(fileID != 1.0)) || (!(fileID != 2.0))) {
          filestar = nullptr;
        }
        if (!(filestar == nullptr)) {
          std::fseek(filestar, (long int)-1.0, SEEK_CUR);
        }
      }
    }
  }
  if (out.size(1) != 0) {
    char c;
    loop_ub = out.size(1) - 1;
    c = out[out.size(1) - 1];
    if (c == '\n') {
      boolean_T guard1;
      guard1 = false;
      if (out.size(1) != 1) {
        b_i = out.size(1) - 2;
        if (out[out.size(1) - 2] == '\r') {
          for (i = 0; i < b_i; i++) {
            out[i] = out[i];
          }
          out.set_size(1, out.size(1) - 2);
        } else {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }
      if (guard1) {
        for (i = 0; i < loop_ub; i++) {
          out[i] = out[i];
        }
        out.set_size(1, out.size(1) - 1);
      }
    } else if (c == '\r') {
      for (i = 0; i < loop_ub; i++) {
        out[i] = out[i];
      }
      out.set_size(1, out.size(1) - 1);
    }
  }
}

} // namespace coder

//
// File trailer for fgetl.cpp
//
// [EOF]
//
