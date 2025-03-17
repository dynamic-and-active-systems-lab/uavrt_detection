//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: indexShapeCheck.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "indexShapeCheck.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_types.h"
#include "omp.h"
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>

// Variable Definitions
static rtRunTimeErrorInfo ib_emlrtRTEI{
    122,          // lineNo
    "errOrWarnIf" // fName
};

// Function Declarations
static void bb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void jc_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void kc_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void lc_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void bb_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream
      << "The sizes of the inputs supplied at run time are incompatible with "
         "the variable-size inputs that were specified at code generati"
         "on time. To perform this indexing operation, do not attempt to index "
         "a scalar by a vector at run-time. Alternatively, regenerate"
         " the code and specify variable-size input vectors that have the same "
         "orientation.";
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
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void jc_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream
      << "The orientations of the vectors supplied at run time are "
         "incompatible with the variable-size inputs that were specified at "
         "code "
         "generation time. To perform this indexing operation, either force "
         "the run-time input vectors to have the same orientation or reg"
         "enerate the code specifying fixed-sized inputs.";
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
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void kc_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream
      << "The orientations of the vectors supplied at run time are "
         "incompatible with the variable-size inputs that were specified at "
         "code "
         "generation time. To perform this indexing operation, either force "
         "the index vector to be a column vector at run time or regenera"
         "te the code specifying fixed-sized inputs.";
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
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void lc_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream
      << "The orientations of the vectors supplied at run time are "
         "incompatible with the variable-size inputs that were specified at "
         "code "
         "generation time. To perform this indexing operation, either force "
         "the data vector to be a column vector at run time or regenerat"
         "e the code specifying fixed-sized inputs.";
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
// Arguments    : const int matrixSize[2]
//                const int indexSize[2]
// Return Type  : void
//
namespace coder {
namespace internal {
void b_indexShapeCheck(const int matrixSize[2], const int indexSize[2])
{
  boolean_T nonSingletonDimFound;
  nonSingletonDimFound = (matrixSize[0] != 1);
  if (matrixSize[1] != 1) {
    if (nonSingletonDimFound) {
      nonSingletonDimFound = false;
    } else {
      nonSingletonDimFound = true;
    }
  }
  if (nonSingletonDimFound) {
    nonSingletonDimFound = (matrixSize[0] == 1);
    if (nonSingletonDimFound || (matrixSize[1] != 1)) {
      nonSingletonDimFound = true;
    }
    if (nonSingletonDimFound) {
      kc_rtErrorWithMessageID(ib_emlrtRTEI.fName, ib_emlrtRTEI.lineNo);
    }
  } else {
    nonSingletonDimFound = (indexSize[0] != 1);
    if (indexSize[1] != 1) {
      if (nonSingletonDimFound) {
        nonSingletonDimFound = false;
      } else {
        nonSingletonDimFound = true;
      }
    }
    if (nonSingletonDimFound) {
      nonSingletonDimFound = (indexSize[0] == 1);
      if (nonSingletonDimFound || (indexSize[1] != 1)) {
        nonSingletonDimFound = true;
      }
      if (nonSingletonDimFound) {
        lc_rtErrorWithMessageID(ib_emlrtRTEI.fName, ib_emlrtRTEI.lineNo);
      }
    }
  }
}

//
// Arguments    : const int matrixSize[2]
//                const int indexSize[2]
// Return Type  : void
//
void indexShapeCheck(const int matrixSize[2], const int indexSize[2])
{
  boolean_T nonSingletonDimFound;
  nonSingletonDimFound = (matrixSize[0] != 1);
  if (matrixSize[1] != 1) {
    if (nonSingletonDimFound) {
      nonSingletonDimFound = false;
    } else {
      nonSingletonDimFound = true;
    }
  }
  if (nonSingletonDimFound) {
    nonSingletonDimFound = (indexSize[0] != 1);
    if (indexSize[1] != 1) {
      if (nonSingletonDimFound) {
        nonSingletonDimFound = false;
      } else {
        nonSingletonDimFound = true;
      }
    }
    if (nonSingletonDimFound) {
      nonSingletonDimFound = ((matrixSize[0] == 1) != (indexSize[0] == 1));
      if (nonSingletonDimFound ||
          ((matrixSize[1] == 1) != (indexSize[1] == 1))) {
        nonSingletonDimFound = true;
      }
      if (nonSingletonDimFound) {
        jc_rtErrorWithMessageID(ib_emlrtRTEI.fName, ib_emlrtRTEI.lineNo);
      }
    }
  }
}

//
// Arguments    : const double matrixSize[2]
//                const double indexSize[2]
// Return Type  : void
//
void indexShapeCheck(const double matrixSize[2], const double indexSize[2])
{
  boolean_T nonSingletonDimFound;
  nonSingletonDimFound = (matrixSize[0] != 1.0);
  if (matrixSize[1] != 1.0) {
    if (nonSingletonDimFound) {
      nonSingletonDimFound = false;
    } else {
      nonSingletonDimFound = true;
    }
  }
  if (nonSingletonDimFound && (indexSize[1] != 1.0)) {
    nonSingletonDimFound = !(matrixSize[0] == 1.0);
    if (nonSingletonDimFound ||
        ((matrixSize[1] == 1.0) != (indexSize[1] == 1.0))) {
      nonSingletonDimFound = true;
    }
    if (nonSingletonDimFound) {
      jc_rtErrorWithMessageID(ib_emlrtRTEI.fName, ib_emlrtRTEI.lineNo);
    }
  }
}

//
// Arguments    : int matrixSize
//                const int indexSize[2]
// Return Type  : void
//
void indexShapeCheck(int matrixSize, const int indexSize[2])
{
  if ((matrixSize == 1) && (indexSize[1] != 1)) {
    bb_rtErrorWithMessageID(ib_emlrtRTEI.fName, ib_emlrtRTEI.lineNo);
  }
}

} // namespace internal
} // namespace coder

//
// File trailer for indexShapeCheck.cpp
//
// [EOF]
//
