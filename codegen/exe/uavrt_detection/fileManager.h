//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: fileManager.h
//
<<<<<<< HEAD
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 23-May-2023 12:05:02
=======
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Apr-2023 11:47:02
>>>>>>> 3930a1e557481905555f2756f2f70ac82e87beba
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
