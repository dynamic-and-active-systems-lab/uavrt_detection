//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: fileManager.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 17-Feb-2023 12:17:58
//

// Include Files
#include "fileManager.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include "omp.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <stdio.h>
#include <string.h>
#include <string>

// Variable Definitions
static FILE *eml_openfiles[20];

static rtRunTimeErrorInfo e_emlrtRTEI{
    292,                    // lineNo
    "cast_and_validate_fid" // fName
};

static rtRunTimeErrorInfo f_emlrtRTEI{
    144,          // lineNo
    "getfilestar" // fName
};

// Function Declarations
namespace coder {
static signed char filedata();

}
static void h_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void pc_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : void
// Return Type  : signed char
//
namespace coder {
static signed char filedata()
{
  int k;
  signed char f;
  boolean_T exitg1;
  f = 0;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 20)) {
    if (eml_openfiles[k] == NULL) {
      f = static_cast<signed char>(k + 1);
      exitg1 = true;
    } else {
      k++;
    }
  }
  return f;
}

//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
} // namespace coder
static void h_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Invalid file identifier.  Use fopen to generate a valid file "
               "identifier.";
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
static void pc_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((outStream << "For code generation, maximum number of open files is ") << 20)
      << ".";
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
// Arguments    : double fid
// Return Type  : int
//
namespace coder {
int cfclose(double fid)
{
  static rtRunTimeErrorInfo pc_emlrtRTEI{
      288,                    // lineNo
      "cast_and_validate_fid" // fName
  };
  static rtRunTimeErrorInfo qc_emlrtRTEI{
      165,                // lineNo
      "conditionalAssert" // fName
  };
  FILE *filestar;
  int cst;
  int st;
  signed char fileid;
  st = -1;
  fileid = static_cast<signed char>(std::round(fid));
  if (fid != fileid) {
    e_rtErrorWithMessageID(e_emlrtRTEI.fName, e_emlrtRTEI.lineNo);
  }
  if (static_cast<int>(fid) != fileid) {
    fileid = -1;
  }
  if (fileid < 0) {
    e_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
  }
  if (fileid >= 3) {
    filestar = eml_openfiles[fileid - 3];
    if (eml_openfiles[fileid - 3] == NULL) {
      h_rtErrorWithMessageID(f_emlrtRTEI.fName, f_emlrtRTEI.lineNo);
    }
  } else if (fileid == 0) {
    filestar = stdin;
  } else if (fileid == 1) {
    filestar = stdout;
  } else {
    filestar = stderr;
  }
  if ((!(filestar != NULL)) || (fileid < 3)) {
    e_rtErrorWithMessageID(qc_emlrtRTEI.fName, qc_emlrtRTEI.lineNo);
  }
  cst = fclose(filestar);
  if (cst == 0) {
    st = 0;
    eml_openfiles[fileid - 3] = NULL;
  }
  return st;
}

//
// Arguments    : const ::coder::array<char, 2U> &cfilename
//                const char *cpermission
// Return Type  : signed char
//
signed char cfopen(const ::coder::array<char, 2U> &cfilename,
                   const char *cpermission)
{
  static rtRunTimeErrorInfo pc_emlrtRTEI{
      111,     // lineNo
      "cfopen" // fName
  };
  array<char, 2U> ccfilename;
  signed char fileid;
  signed char j;
  fileid = -1;
  j = filedata();
  if (j < 1) {
    pc_rtErrorWithMessageID(pc_emlrtRTEI.fName, pc_emlrtRTEI.lineNo);
  } else {
    FILE *filestar;
    int i;
    int loop_ub;
    ccfilename.set_size(1, cfilename.size(1) + 1);
    loop_ub = cfilename.size(1);
    for (i = 0; i < loop_ub; i++) {
      ccfilename[i] = cfilename[i];
    }
    ccfilename[cfilename.size(1)] = '\x00';
    filestar = fopen(&ccfilename[0], cpermission);
    if (filestar != NULL) {
      eml_openfiles[j - 1] = filestar;
      i = j + 2;
      if (j + 2 > 127) {
        i = 127;
      }
      fileid = static_cast<signed char>(i);
    }
  }
  return fileid;
}

//
// Arguments    : double varargin_1
// Return Type  : FILE*
//
FILE *fileManager(double varargin_1)
{
  FILE *f;
  signed char fileid;
  fileid = static_cast<signed char>(std::round(varargin_1));
  if (varargin_1 != fileid) {
    e_rtErrorWithMessageID(e_emlrtRTEI.fName, e_emlrtRTEI.lineNo);
  }
  if (static_cast<int>(varargin_1) != fileid) {
    fileid = -1;
  }
  if (fileid >= 3) {
    f = eml_openfiles[fileid - 3];
    if (eml_openfiles[fileid - 3] == NULL) {
      h_rtErrorWithMessageID(f_emlrtRTEI.fName, f_emlrtRTEI.lineNo);
    }
  } else if (fileid == 0) {
    f = stdin;
  } else if (fileid == 1) {
    f = stdout;
  } else if (fileid == 2) {
    f = stderr;
  } else {
    f = NULL;
  }
  return f;
}

//
// Arguments    : void
// Return Type  : void
//
} // namespace coder
void filedata_init()
{
  FILE *a;
  a = NULL;
  for (int i{0}; i < 20; i++) {
    eml_openfiles[i] = a;
  }
}

//
// File trailer for fileManager.cpp
//
// [EOF]
//
