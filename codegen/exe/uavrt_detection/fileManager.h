//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: fileManager.h
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 22-Oct-2022 15:24:58
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

signed char cfopen(const char cfilename[34]);

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
