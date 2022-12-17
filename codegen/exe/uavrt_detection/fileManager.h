//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: fileManager.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 17-Dec-2022 13:40:17
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

signed char cfopen(const char cfilename[65]);

signed char cfopen(const ::coder::array<char, 2U> &cfilename);

FILE *fileManager(double varargin_1);

} // namespace coder
void filedata_init();

#endif
//
// File trailer for fileManager.h
//
// [EOF]
//
