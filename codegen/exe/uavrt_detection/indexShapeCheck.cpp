//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: indexShapeCheck.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 17:16:38
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
#include <string.h>
#include <string>

// Variable Definitions
static rtRunTimeErrorInfo nb_emlrtRTEI{
    122,          // lineNo
    "errOrWarnIf" // fName
};

// Function Declarations
static void ec_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void fc_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void gc_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void x_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void ec_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream
      << "Code generation assumption about size violated. Run-time indexing is "
         "vector(vector) with different orientations, but compile-tim"
         "e assumption was matrix(matrix) indexing.";
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
static void fc_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream
      << "Code generation assumption about size violated. Run-time logical "
         "indexing into a row vector, but compile-time assumption was mat"
         "rix(matrix) logical indexing.";
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
static void gc_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream
      << "Code generation assumption about size violated. Run-time logical "
         "indexing with a row vector, but compile-time assumption was mat"
         "rix(matrix) logical indexing.";
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
static void x_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream
      << "Code generation assumption about size violated. Run-time indexing is "
         "scalar(vector), but compile-time assumption was vector(vect"
         "or) indexing.";
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
      fc_rtErrorWithMessageID(nb_emlrtRTEI.fName, nb_emlrtRTEI.lineNo);
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
        gc_rtErrorWithMessageID(nb_emlrtRTEI.fName, nb_emlrtRTEI.lineNo);
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
        ec_rtErrorWithMessageID(nb_emlrtRTEI.fName, nb_emlrtRTEI.lineNo);
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
  if (nonSingletonDimFound) {
    nonSingletonDimFound = (indexSize[0] != 1.0);
    if (indexSize[1] != 1.0) {
      if (nonSingletonDimFound) {
        nonSingletonDimFound = false;
      } else {
        nonSingletonDimFound = true;
      }
    }
    if (nonSingletonDimFound) {
      nonSingletonDimFound = !(matrixSize[0] == 1.0);
      if (nonSingletonDimFound ||
          ((matrixSize[1] == 1.0) != (indexSize[1] == 1.0))) {
        nonSingletonDimFound = true;
      }
      if (nonSingletonDimFound) {
        ec_rtErrorWithMessageID(nb_emlrtRTEI.fName, nb_emlrtRTEI.lineNo);
      }
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
    x_rtErrorWithMessageID(nb_emlrtRTEI.fName, nb_emlrtRTEI.lineNo);
  }
}

} // namespace internal
} // namespace coder

//
// File trailer for indexShapeCheck.cpp
//
// [EOF]
//
