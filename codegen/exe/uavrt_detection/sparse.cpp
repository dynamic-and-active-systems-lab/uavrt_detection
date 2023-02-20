//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sparse.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 14:31:55
//

// Include Files
#include "sparse.h"
#include "anonymous_function.h"
#include "introsort.h"
#include "rt_nonfinite.h"
#include "sparse1.h"
#include "uavrt_detection_internal_types.h"
#include "uavrt_detection_types.h"
#include "omp.h"
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string.h>
#include <string>

// Function Declarations
static void db_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void db_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Vectors must be the same length.";
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
// Arguments    : int varargin_1_size
//                int varargin_2_size
//                int varargin_3_size
//                sparse *y
// Return Type  : void
//
namespace coder {
void b_sparse(int varargin_1_size, int varargin_2_size, int varargin_3_size,
              sparse *y)
{
  static rtRunTimeErrorInfo kb_emlrtRTEI{
      111,            // lineNo
      "sparse/sparse" // fName
  };
  static rtRunTimeErrorInfo lb_emlrtRTEI{
      116,            // lineNo
      "sparse/sparse" // fName
  };
  anonymous_function b_this;
  int sortedIndices_data;
  if ((varargin_1_size != varargin_2_size) ||
      (varargin_3_size != varargin_2_size)) {
    db_rtErrorWithMessageID(kb_emlrtRTEI.fName, kb_emlrtRTEI.lineNo);
  }
  if ((varargin_3_size != varargin_2_size) &&
      (varargin_3_size != varargin_1_size)) {
    db_rtErrorWithMessageID(lb_emlrtRTEI.fName, lb_emlrtRTEI.lineNo);
  }
  b_this.workspace.b.size[0] = varargin_1_size;
  b_this.workspace.a.size[0] = varargin_2_size;
  internal::introsort((int *)&sortedIndices_data, varargin_2_size, b_this);
  y->m = 0;
  y->n = 0;
  y->d.size[0] = 1;
  y->d.data[0] = 0.0;
  y->maxnz = 1;
  y->colidx.size[0] = 1;
  y->rowidx.size[0] = 1;
  y->rowidx.data[0] = 0;
  y->colidx.data[0] = 1;
}

} // namespace coder

//
// File trailer for sparse.cpp
//
// [EOF]
//
