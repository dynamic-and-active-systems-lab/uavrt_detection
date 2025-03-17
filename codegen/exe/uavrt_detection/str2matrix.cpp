//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: str2matrix.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "str2matrix.h"
#include "find.h"
#include "fliplr.h"
#include "isspace.h"
#include "nullAssignment.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include "str2double.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include "omp.h"
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>

// Function Declarations
static void rtSizeEqNDCheck(const int &aDims1, const int &aDims2,
                            const rtEqualityCheckInfo &aInfo);

// Function Definitions
//
// Arguments    : const int &aDims1
//                const int &aDims2
//                const rtEqualityCheckInfo &aInfo
// Return Type  : void
//
static void rtSizeEqNDCheck(const int &aDims1, const int &aDims2,
                            const rtEqualityCheckInfo &aInfo)
{
  std::string errMsg;
  std::stringstream outStream;
  for (int i{0}; i < aInfo.nDims; i++) {
    if ((&aDims1)[i] != (&aDims2)[i]) {
      std::string dims1Str;
      std::string dims2Str;
      dims1Str = rtGenSizeString(aInfo.nDims, &aDims1);
      dims2Str = rtGenSizeString(aInfo.nDims, &aDims2);
      ((((outStream << "Sizes mismatch: ") << dims1Str) << " ~= ") << dims2Str)
          << ".";
      outStream << "\n";
      ((((outStream << "Error in ") << aInfo.fName) << " (line ")
       << aInfo.lineNo)
          << ")";
      if (omp_in_parallel()) {
        errMsg = outStream.str();
        std::fprintf(stderr, "%s", errMsg.c_str());
        std::abort();
      } else {
        throw std::runtime_error(outStream.str());
      }
    }
  }
}

//
// STR2MATRIX Converts a string containing a matrix in Matlab notation to a
// numeric array. Arrays must be no greater than two dimensions. Hard
// brackets should enclose the array, with semicolons separating rows.
// Columns can be separated by white space or commas. All rows must have the
// same number of columns. Note that str2num would produce similar results to
// this function, but is not supported for code generation.
//
// INPUTS:
//    inputStr    A string containing a matrix. Ex: '[2 3; 5, 6 ;7 ,8 ]'
// OUTPUS:
//    outMat      A numeric array of the input matrix.
//
//
// Author:    Michael W. Shafer
// Date:      2022-02-15
// --------------------------------------------------------------------------
//
// Arguments    : coder::array<char, 2U> &inputStr
//                coder::array<creal_T, 2U> &outMat
// Return Type  : void
//
void str2matrix(coder::array<char, 2U> &inputStr,
                coder::array<creal_T, 2U> &outMat)
{
  static rtBoundsCheckInfo ab_emlrtBCI{
      91,               // lineNo
      "rowDividerLocs", // aName
      "str2matrix"      // fName
  };
  static rtBoundsCheckInfo bb_emlrtBCI{
      26,          // lineNo
      "inputStr",  // aName
      "str2matrix" // fName
  };
  static rtBoundsCheckInfo cb_emlrtBCI{
      26,          // lineNo
      "inputStr",  // aName
      "str2matrix" // fName
  };
  static rtBoundsCheckInfo db_emlrtBCI{
      41,          // lineNo
      "inputStr",  // aName
      "str2matrix" // fName
  };
  static rtBoundsCheckInfo eb_emlrtBCI{
      41,          // lineNo
      "inputStr",  // aName
      "str2matrix" // fName
  };
  static rtBoundsCheckInfo fb_emlrtBCI{
      44,          // lineNo
      "inputStr",  // aName
      "str2matrix" // fName
  };
  static rtBoundsCheckInfo gb_emlrtBCI{
      47,          // lineNo
      "inputStr",  // aName
      "str2matrix" // fName
  };
  static rtBoundsCheckInfo hb_emlrtBCI{
      62,          // lineNo
      "inputStr",  // aName
      "str2matrix" // fName
  };
  static rtBoundsCheckInfo ib_emlrtBCI{
      62,          // lineNo
      "inputStr",  // aName
      "str2matrix" // fName
  };
  static rtBoundsCheckInfo jb_emlrtBCI{
      65,          // lineNo
      "inputStr",  // aName
      "str2matrix" // fName
  };
  static rtBoundsCheckInfo kb_emlrtBCI{
      68,          // lineNo
      "inputStr",  // aName
      "str2matrix" // fName
  };
  static rtBoundsCheckInfo lb_emlrtBCI{
      76,          // lineNo
      "inputStr",  // aName
      "str2matrix" // fName
  };
  static rtBoundsCheckInfo mb_emlrtBCI{
      92,               // lineNo
      "rowDividerLocs", // aName
      "str2matrix"      // fName
  };
  static rtBoundsCheckInfo nb_emlrtBCI{
      93,          // lineNo
      "commaLocs", // aName
      "str2matrix" // fName
  };
  static rtBoundsCheckInfo ob_emlrtBCI{
      100,              // lineNo
      "rowDividerLocs", // aName
      "str2matrix"      // fName
  };
  static rtBoundsCheckInfo pb_emlrtBCI{
      101,              // lineNo
      "rowDividerLocs", // aName
      "str2matrix"      // fName
  };
  static rtBoundsCheckInfo qb_emlrtBCI{
      102,         // lineNo
      "commaLocs", // aName
      "str2matrix" // fName
  };
  static rtBoundsCheckInfo rb_emlrtBCI{
      114,              // lineNo
      "colDividerLocs", // aName
      "str2matrix"      // fName
  };
  static rtBoundsCheckInfo sb_emlrtBCI{
      114,              // lineNo
      "colDividerLocs", // aName
      "str2matrix"      // fName
  };
  static rtBoundsCheckInfo tb_emlrtBCI{
      115,         // lineNo
      "tempRow",   // aName
      "str2matrix" // fName
  };
  static rtBoundsCheckInfo ub_emlrtBCI{
      114,         // lineNo
      "inputStr",  // aName
      "str2matrix" // fName
  };
  static rtBoundsCheckInfo vb_emlrtBCI{
      114,         // lineNo
      "inputStr",  // aName
      "str2matrix" // fName
  };
  static rtBoundsCheckInfo wb_emlrtBCI{
      117,         // lineNo
      "outMat",    // aName
      "str2matrix" // fName
  };
  static rtDoubleCheckInfo q_emlrtDCI{
      96,          // lineNo
      "str2matrix" // fName
  };
  static rtDoubleCheckInfo r_emlrtDCI{
      96,          // lineNo
      "str2matrix" // fName
  };
  static rtDoubleCheckInfo s_emlrtDCI{
      111,         // lineNo
      "str2matrix" // fName
  };
  static rtEqualityCheckInfo g_emlrtECI{
      2,           // nDims
      102,         // lineNo
      "str2matrix" // fName
  };
  static rtEqualityCheckInfo h_emlrtECI{
      -1,          // nDims
      117,         // lineNo
      "str2matrix" // fName
  };
  coder::array<creal_T, 2U> tempRow;
  coder::array<double, 2U> rightBracketLoc;
  coder::array<double, 2U> rowDividerLocs;
  coder::array<int, 2U> ii;
  coder::array<int, 2U> leftBracketLoc;
  coder::array<int, 2U> r;
  coder::array<int, 2U> r1;
  coder::array<char, 2U> c_inputStr;
  coder::array<boolean_T, 2U> b_inputStr;
  int iv[2];
  int iv1[2];
  int b_leftBracketLoc;
  int b_loop_ub;
  int c_i;
  int end;
  int end_tmp;
  unsigned int i;
  int i1;
  int i2;
  int loop_ub;
  int numelCommasLast;
  int trueCount;
  char c;
  boolean_T b;
  boolean_T done;
  boolean_T guard1;
  boolean_T guard2;
  // Strip redundant white space
  done = false;
  i = 1U;
  while (!done) {
    done = (i + 1U == static_cast<unsigned int>(inputStr.size(1)));
    if ((static_cast<int>(i) < 1) || (static_cast<int>(i) > inputStr.size(1))) {
      rtDynamicBoundsError(static_cast<int>(i), 1, inputStr.size(1),
                           bb_emlrtBCI);
    }
    if (coder::b_isspace(inputStr[static_cast<int>(i) - 1])) {
      if ((static_cast<int>(i + 1U) < 1) ||
          (static_cast<int>(i + 1U) > inputStr.size(1))) {
        rtDynamicBoundsError(static_cast<int>(i + 1U), 1, inputStr.size(1),
                             cb_emlrtBCI);
      }
      if (coder::b_isspace(inputStr[static_cast<int>(i)])) {
        // inputStr(i+1) = '';
        // inputStr = inputStr(1:numel(inputStr) ~= i+1);
        coder::internal::nullAssignment(inputStr, static_cast<int>(i) + 1);
        i = static_cast<unsigned int>(static_cast<int>(i) - 1);
      }
    }
    i++;
  }
  // Strip out white space after [ ; and , characters
  done = false;
  i = 1U;
  while (!done) {
    done = (i + 1U == static_cast<unsigned int>(inputStr.size(1)));
    b = ((static_cast<int>(i) < 1) || (static_cast<int>(i) > inputStr.size(1)));
    if (b) {
      rtDynamicBoundsError(static_cast<int>(i), 1, inputStr.size(1),
                           db_emlrtBCI);
    }
    c = inputStr[static_cast<int>(i) - 1];
    guard1 = false;
    guard2 = false;
    if (c == '[') {
      if ((static_cast<int>(i + 1U) < 1) ||
          (static_cast<int>(i + 1U) > inputStr.size(1))) {
        rtDynamicBoundsError(static_cast<int>(i + 1U), 1, inputStr.size(1),
                             eb_emlrtBCI);
      }
      if (coder::b_isspace(inputStr[static_cast<int>(i)])) {
        coder::internal::nullAssignment(inputStr, static_cast<int>(i) + 1);
        i = static_cast<unsigned int>(static_cast<int>(i) - 1);
      } else {
        guard2 = true;
      }
    } else {
      guard2 = true;
    }
    if (guard2) {
      if (c == ',') {
        if ((static_cast<int>(i + 1U) < 1) ||
            (static_cast<int>(i + 1U) > inputStr.size(1))) {
          rtDynamicBoundsError(static_cast<int>(i + 1U), 1, inputStr.size(1),
                               fb_emlrtBCI);
        }
        if (coder::b_isspace(inputStr[static_cast<int>(i)])) {
          coder::internal::nullAssignment(inputStr, static_cast<int>(i) + 1);
          i = static_cast<unsigned int>(static_cast<int>(i) - 1);
        } else {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }
    }
    if (guard1 && (c == ';')) {
      if ((static_cast<int>(i + 1U) < 1) ||
          (static_cast<int>(i + 1U) > inputStr.size(1))) {
        rtDynamicBoundsError(static_cast<int>(i + 1U), 1, inputStr.size(1),
                             gb_emlrtBCI);
      }
      if (coder::b_isspace(inputStr[static_cast<int>(i)])) {
        coder::internal::nullAssignment(inputStr, static_cast<int>(i) + 1);
        i = static_cast<unsigned int>(static_cast<int>(i) - 1);
      }
    }
    i++;
  }
  // Strip out white space before [ ; and , characters
  coder::fliplr(inputStr);
  done = false;
  i = 1U;
  while (!done) {
    done = (i + 1U == static_cast<unsigned int>(inputStr.size(1)));
    b = ((static_cast<int>(i) < 1) || (static_cast<int>(i) > inputStr.size(1)));
    if (b) {
      rtDynamicBoundsError(static_cast<int>(i), 1, inputStr.size(1),
                           hb_emlrtBCI);
    }
    c = inputStr[static_cast<int>(i) - 1];
    guard1 = false;
    guard2 = false;
    if (c == '[') {
      if ((static_cast<int>(i + 1U) < 1) ||
          (static_cast<int>(i + 1U) > inputStr.size(1))) {
        rtDynamicBoundsError(static_cast<int>(i + 1U), 1, inputStr.size(1),
                             ib_emlrtBCI);
      }
      if (coder::b_isspace(inputStr[static_cast<int>(i)])) {
        coder::internal::nullAssignment(inputStr, static_cast<int>(i) + 1);
        i = static_cast<unsigned int>(static_cast<int>(i) - 1);
      } else {
        guard2 = true;
      }
    } else {
      guard2 = true;
    }
    if (guard2) {
      if (c == ',') {
        if ((static_cast<int>(i + 1U) < 1) ||
            (static_cast<int>(i + 1U) > inputStr.size(1))) {
          rtDynamicBoundsError(static_cast<int>(i + 1U), 1, inputStr.size(1),
                               jb_emlrtBCI);
        }
        if (coder::b_isspace(inputStr[static_cast<int>(i)])) {
          coder::internal::nullAssignment(inputStr, static_cast<int>(i) + 1);
          i = static_cast<unsigned int>(static_cast<int>(i) - 1);
        } else {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }
    }
    if (guard1 && (c == ';')) {
      if ((static_cast<int>(i + 1U) < 1) ||
          (static_cast<int>(i + 1U) > inputStr.size(1))) {
        rtDynamicBoundsError(static_cast<int>(i + 1U), 1, inputStr.size(1),
                             kb_emlrtBCI);
      }
      if (coder::b_isspace(inputStr[static_cast<int>(i)])) {
        coder::internal::nullAssignment(inputStr, static_cast<int>(i) + 1);
        i = static_cast<unsigned int>(static_cast<int>(i) - 1);
      }
    }
    i++;
  }
  coder::fliplr(inputStr);
  // Replace space with commas for marking columns
  end_tmp = inputStr.size(1);
  for (int b_i{0}; b_i < end_tmp; b_i++) {
    if (inputStr[b_i] == ' ') {
      if (b_i > inputStr.size(1) - 1) {
        rtDynamicBoundsError(b_i, 0, inputStr.size(1) - 1, lb_emlrtBCI);
      }
      inputStr[b_i] = ',';
    }
  }
  b_inputStr.set_size(1, inputStr.size(1));
  for (c_i = 0; c_i < end_tmp; c_i++) {
    b_inputStr[c_i] = (inputStr[c_i] == '[');
  }
  coder::b_eml_find(b_inputStr, ii);
  loop_ub = ii.size(1);
  leftBracketLoc.set_size(1, ii.size(1));
  for (c_i = 0; c_i < loop_ub; c_i++) {
    leftBracketLoc[c_i] = ii[c_i];
  }
  b_inputStr.set_size(1, inputStr.size(1));
  for (c_i = 0; c_i < end_tmp; c_i++) {
    b_inputStr[c_i] = (inputStr[c_i] == ']');
  }
  coder::b_eml_find(b_inputStr, ii);
  loop_ub = ii.size(1);
  rightBracketLoc.set_size(1, ii.size(1));
  for (c_i = 0; c_i < loop_ub; c_i++) {
    rightBracketLoc[c_i] = ii[c_i];
  }
  if ((leftBracketLoc.size(1) != 1) || (rightBracketLoc.size(1) != 1)) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  b_inputStr.set_size(1, inputStr.size(1));
  for (c_i = 0; c_i < end_tmp; c_i++) {
    b_inputStr[c_i] = (inputStr[c_i] == ';');
  }
  coder::b_eml_find(b_inputStr, ii);
  rowDividerLocs.set_size(1, ii.size(1) + 2);
  rowDividerLocs[0] = leftBracketLoc[0];
  loop_ub = ii.size(1);
  for (c_i = 0; c_i < loop_ub; c_i++) {
    rowDividerLocs[c_i + 1] = ii[c_i];
  }
  rowDividerLocs[ii.size(1) + 1] = rightBracketLoc[0];
  coder::internal::sort(rowDividerLocs);
  b_inputStr.set_size(1, inputStr.size(1));
  for (c_i = 0; c_i < end_tmp; c_i++) {
    b_inputStr[c_i] = (inputStr[c_i] == ',');
  }
  coder::b_eml_find(b_inputStr, ii);
  loop_ub = ii.size(1);
  leftBracketLoc.set_size(1, ii.size(1));
  for (c_i = 0; c_i < loop_ub; c_i++) {
    leftBracketLoc[c_i] = ii[c_i];
  }
  // Check for the number of columns in the first row to preallocate outMat
  c_i = rowDividerLocs.size(1);
  if (rowDividerLocs.size(1) < 1) {
    rtDynamicBoundsError(1, 1, rowDividerLocs.size(1), ab_emlrtBCI);
  }
  if (rowDividerLocs.size(1) < 2) {
    rtDynamicBoundsError(2, 1, rowDividerLocs.size(1), mb_emlrtBCI);
  }
  iv1[0] = 1;
  iv1[1] = ii.size(1);
  trueCount = 0;
  for (int b_i{0}; b_i < loop_ub; b_i++) {
    i1 = leftBracketLoc[b_i];
    if ((i1 > rowDividerLocs[0]) && (i1 < rowDividerLocs[1])) {
      trueCount++;
    }
  }
  r.set_size(1, trueCount);
  trueCount = 0;
  for (int b_i{0}; b_i < loop_ub; b_i++) {
    i1 = leftBracketLoc[b_i];
    if ((i1 > rowDividerLocs[0]) && (i1 < rowDividerLocs[1])) {
      r[trueCount] = b_i;
      trueCount++;
    }
  }
  b_loop_ub = r.size(1);
  for (i1 = 0; i1 < b_loop_ub; i1++) {
    if (r[i1] > leftBracketLoc.size(1) - 1) {
      rtDynamicBoundsError(r[i1], 0, leftBracketLoc.size(1) - 1, nb_emlrtBCI);
    }
  }
  if (rowDividerLocs.size(1) - 1 < 0) {
    rtNonNegativeError(-1.0, q_emlrtDCI);
  }
  if (static_cast<double>(r.size(1)) + 1.0 != r.size(1) + 1) {
    rtIntegerError(static_cast<double>(r.size(1)) + 1.0, r_emlrtDCI);
  }
  i1 = rowDividerLocs.size(1) - 1;
  b_loop_ub = r.size(1) + 1;
  outMat.set_size(rowDividerLocs.size(1) - 1, r.size(1) + 1);
  trueCount = (rowDividerLocs.size(1) - 1) * (r.size(1) + 1);
  for (i2 = 0; i2 < trueCount; i2++) {
    outMat[i2].re = 0.0;
    outMat[i2].im = 0.0;
  }
  numelCommasLast = 0;
  if (rowDividerLocs.size(1) - 2 >= 0) {
    iv1[0] = 1;
    iv1[1] = ii.size(1);
    end = ii.size(1);
    b_leftBracketLoc = ii.size(1);
  }
  for (int b_i{0}; b_i <= c_i - 2; b_i++) {
    int i3;
    if (b_i + 1 > c_i) {
      rtDynamicBoundsError(b_i + 1, 1, c_i, ob_emlrtBCI);
    }
    if (b_i + 2 > c_i) {
      rtDynamicBoundsError(b_i + 2, 1, c_i, pb_emlrtBCI);
    }
    iv[0] = 1;
    iv[1] = loop_ub;
    if (loop_ub != iv1[1]) {
      rtSizeEqNDCheck(iv[0], iv1[0], g_emlrtECI);
    }
    trueCount = 0;
    for (int d_i{0}; d_i < end; d_i++) {
      i2 = leftBracketLoc[d_i];
      if ((i2 > rowDividerLocs[b_i]) && (i2 < rowDividerLocs[b_i + 1])) {
        trueCount++;
      }
    }
    r1.set_size(1, trueCount);
    trueCount = 0;
    for (int d_i{0}; d_i < end; d_i++) {
      i2 = leftBracketLoc[d_i];
      if ((i2 > rowDividerLocs[b_i]) && (i2 < rowDividerLocs[b_i + 1])) {
        r1[trueCount] = d_i;
        trueCount++;
      }
    }
    trueCount = r1.size(1);
    for (i2 = 0; i2 < trueCount; i2++) {
      if ((r1[i2] < 0) || (r1[i2] > b_leftBracketLoc - 1)) {
        rtDynamicBoundsError(r1[i2], 0, b_leftBracketLoc - 1, qb_emlrtBCI);
      }
    }
    if ((b_i + 1 > 1) && (r1.size(1) != numelCommasLast)) {
      rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
    }
    i2 = r1.size(1) + 2;
    rightBracketLoc.set_size(1, r1.size(1) + 2);
    rightBracketLoc[0] = rowDividerLocs[b_i];
    for (i3 = 0; i3 < trueCount; i3++) {
      rightBracketLoc[i3 + 1] = leftBracketLoc[r1[i3]];
    }
    trueCount = r1.size(1) + 1;
    rightBracketLoc[r1.size(1) + 1] = rowDividerLocs[b_i + 1];
    if (static_cast<double>(r1.size(1)) + 1.0 != r1.size(1) + 1) {
      rtIntegerError(static_cast<double>(r1.size(1)) + 1.0, s_emlrtDCI);
    }
    tempRow.set_size(1, r1.size(1) + 1);
    for (i3 = 0; i3 < trueCount; i3++) {
      tempRow[i3].re = 0.0;
      tempRow[i3].im = 0.0;
    }
    for (int d_i{0}; d_i <= i2 - 2; d_i++) {
      double d;
      int i4;
      if (d_i + 1 > i2) {
        rtDynamicBoundsError(d_i + 1, 1, i2, rb_emlrtBCI);
      }
      if (d_i + 2 > i2) {
        rtDynamicBoundsError(d_i + 2, 1, i2, sb_emlrtBCI);
      }
      d = rightBracketLoc[d_i + 1] - 1.0;
      if (rightBracketLoc[d_i] + 1.0 > d) {
        i3 = 0;
        i4 = 0;
      } else {
        i3 = static_cast<int>(rightBracketLoc[d_i] + 1.0);
        if ((i3 < 1) || (i3 > end_tmp)) {
          rtDynamicBoundsError(i3, 1, end_tmp, ub_emlrtBCI);
        }
        i3--;
        if ((static_cast<int>(d) < 1) || (static_cast<int>(d) > end_tmp)) {
          rtDynamicBoundsError(static_cast<int>(d), 1, end_tmp, vb_emlrtBCI);
        }
        i4 = static_cast<int>(d);
      }
      numelCommasLast = i4 - i3;
      c_inputStr.set_size(1, numelCommasLast);
      for (i4 = 0; i4 < numelCommasLast; i4++) {
        c_inputStr[i4] = inputStr[i3 + i4];
      }
      if (d_i + 1 > trueCount) {
        rtDynamicBoundsError(d_i + 1, 1, trueCount, tb_emlrtBCI);
      }
      tempRow[d_i] = coder::internal::str2double(c_inputStr);
    }
    if (b_i + 1 > i1) {
      rtDynamicBoundsError(b_i + 1, 1, i1, wb_emlrtBCI);
    }
    iv[0] = 1;
    iv[1] = b_loop_ub;
    rtSubAssignSizeCheck(&iv[0], 2, tempRow.size(), 2, h_emlrtECI);
    for (i2 = 0; i2 < b_loop_ub; i2++) {
      outMat[b_i + outMat.size(0) * i2] = tempRow[i2];
    }
    numelCommasLast = r1.size(1);
  }
}

//
// File trailer for str2matrix.cpp
//
// [EOF]
//
