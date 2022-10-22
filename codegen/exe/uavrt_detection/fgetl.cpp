//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: fgetl.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 22-Oct-2022 12:48:10
//

// Include Files
#include "fgetl.h"
#include "fileManager.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cstddef>
#include <stdio.h>

// Function Definitions
//
// Arguments    : double fileID
//                ::coder::array<char, 2U> &out
// Return Type  : void
//
namespace coder {
void fgetl(double fileID, ::coder::array<char, 2U> &out)
{
  FILE *filestar;
  int b_i;
  int i;
  filestar = fileManager(fileID);
  if ((!(fileID != 0.0)) || (!(fileID != 1.0)) || (!(fileID != 2.0))) {
    filestar = NULL;
  }
  out.set_size(1, 0);
  if (!(filestar == NULL)) {
    FILE *b_NULL;
    FILE *b_filestar;
    char *cOut;
    int exitg1;
    int st;
    int wherefrom;
    char ReadBuff[1024];
    boolean_T readNewline;
    do {
      int reachedEndOfFile;
      exitg1 = 0;
      cOut = fgets(&ReadBuff[0], 1024, filestar);
      readNewline = false;
      b_NULL = NULL;
      b_filestar = fileManager(fileID);
      if (b_filestar == b_NULL) {
        reachedEndOfFile = 0;
      } else {
        st = feof(b_filestar);
        reachedEndOfFile = ((int)st != 0);
      }
      if (cOut == NULL) {
        exitg1 = 1;
      } else {
        int carriageReturnAt;
        int idx;
        boolean_T fileEndAfterCarriageReturn;
        boolean_T newLineAfterCarriageReturn;
        idx = 1;
        carriageReturnAt = 0;
        if (reachedEndOfFile != 0) {
          boolean_T exitg2;
          i = 0;
          exitg2 = false;
          while ((!exitg2) && (i < 1024)) {
            if (ReadBuff[i] == '\x00') {
              idx = i + 1;
              exitg2 = true;
            } else {
              if ((carriageReturnAt == 0) && (ReadBuff[i] == '\x0d')) {
                carriageReturnAt = i + 1;
              }
              i++;
            }
          }
          if (ReadBuff[idx - 1] == '\x00') {
            idx--;
          }
        } else {
          boolean_T exitg2;
          i = 0;
          exitg2 = false;
          while ((!exitg2) && (i < 1025)) {
            if (i + 1 > 1024) {
              idx = 1023;
              exitg2 = true;
            } else if (ReadBuff[i] == '\x0a') {
              idx = i + 1;
              exitg2 = true;
            } else {
              if ((carriageReturnAt == 0) && (ReadBuff[i] == '\x0d')) {
                carriageReturnAt = i + 1;
              }
              i++;
            }
          }
          readNewline = (ReadBuff[idx - 1] == '\x0a');
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
          if (idx < 1) {
            i = 0;
          } else {
            i = idx;
          }
          b_i = out.size(1);
          out.set_size(out.size(0), out.size(1) + i);
          for (int i1{0}; i1 < i; i1++) {
            out[b_i + i1] = ReadBuff[i1];
          }
        } else {
          b_i = out.size(1);
          out.set_size(out.size(0), out.size(1) + carriageReturnAt);
          for (int i1{0}; i1 < carriageReturnAt; i1++) {
            out[b_i + i1] = ReadBuff[i1];
          }
          wherefrom = SEEK_CUR;
          b_filestar = fileManager(fileID);
          if ((!(fileID != 0.0)) || (!(fileID != 1.0)) || (!(fileID != 2.0))) {
            b_filestar = NULL;
          }
          if (!(b_filestar == NULL)) {
            fseek(b_filestar, (long int)(carriageReturnAt - idx), wherefrom);
          }
        }
        if (readNewline || (reachedEndOfFile != 0) || (carriageReturnAt > 0)) {
          exitg1 = 1;
        }
      }
    } while (exitg1 == 0);
    b_NULL = NULL;
    filestar = fileManager(fileID);
    if (filestar == b_NULL) {
      b_i = 0;
    } else {
      st = feof(filestar);
      b_i = ((int)st != 0);
    }
    if (b_i == 0) {
      filestar = fileManager(fileID);
      if ((!(fileID != 0.0)) || (!(fileID != 1.0)) || (!(fileID != 2.0))) {
        filestar = NULL;
      }
      if (!(filestar == NULL)) {
        unsigned char buf;
        fread(&buf, sizeof(unsigned char), (size_t)1, filestar);
      }
      b_NULL = NULL;
      filestar = fileManager(fileID);
      if (filestar == b_NULL) {
        b_i = 0;
      } else {
        st = feof(filestar);
        b_i = ((int)st != 0);
      }
      if (b_i == 0) {
        wherefrom = SEEK_CUR;
        filestar = fileManager(fileID);
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
