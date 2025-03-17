//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: fscanf.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "fscanf.h"
#include "fileManager.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cstdio>

// Function Definitions
//
// Arguments    : double fileID
//                array<double, 1U> &A
// Return Type  : void
//
namespace coder {
void b_fscanf(double fileID, array<double, 1U> &A)
{
  std::FILE *f;
  int numRead;
  boolean_T exitg1;
  boolean_T incompleteRead;
  A.set_size(0);
  numRead = 1;
  exitg1 = false;
  while ((!exitg1) && (numRead > 0)) {
    double tmpOut_f1;
    int tmpOut_f2;
    tmpOut_f1 = 0.0;
    tmpOut_f2 = -1;
    f = internal::getfilestar(fileID, incompleteRead);
    numRead = std::fscanf(f, "%lf%n", &tmpOut_f1, &tmpOut_f2);
    if (tmpOut_f2 != -1) {
      numRead++;
    }
    incompleteRead = (numRead == 0);
    if (numRead > 0) {
      tmpOut_f2 = A.size(0);
      A.set_size(A.size(0) + 1);
      A[tmpOut_f2] = tmpOut_f1;
      incompleteRead = ((numRead < 2) || incompleteRead);
    }
    if (incompleteRead) {
      exitg1 = true;
    }
  }
}

} // namespace coder

//
// File trailer for fscanf.cpp
//
// [EOF]
//
