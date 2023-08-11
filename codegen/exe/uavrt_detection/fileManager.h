//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: fileManager.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 11-Aug-2023 09:25:46
//

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdio>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
int cfclose(double fid);

signed char cfopen(const ::coder::array<char, 2U> &cfilename,
                   const char *cpermission);

std::FILE *getfilestar(double fid, boolean_T &autoflush);

} // namespace internal
} // namespace coder
void filedata_init();

#endif
//
// File trailer for fileManager.h
//
// [EOF]
//
