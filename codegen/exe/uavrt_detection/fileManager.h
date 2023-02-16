//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: fileManager.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 16-Feb-2023 15:25:26
//

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>
#include <stdio.h>

// Function Declarations
namespace coder {
int cfclose(double fid);

signed char cfopen(const ::coder::array<char, 2U> &cfilename,
                   const char *cpermission);

FILE *fileManager(double varargin_1);

} // namespace coder
void filedata_init();

#endif
//
// File trailer for fileManager.h
//
// [EOF]
//
