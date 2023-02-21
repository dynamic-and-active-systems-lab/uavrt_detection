//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: str2matrix.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 16:51:51
//

// Include Files
#include "str2matrix.h"
#include "find.h"
#include "nullAssignment.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include "str2double.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include <string.h>

// Function Definitions
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
  static rtBoundsCheckInfo ac_emlrtBCI{
      -1,                                         // iFirst
      -1,                                         // iLast
      114,                                        // lineNo
      32,                                         // colNo
      "commaLocs",                                // aName
      "str2matrix",                               // fName
      "H:\\repos\\uavrt_detection\\str2matrix.m", // pName
      0                                           // checkKind
  };
  static rtBoundsCheckInfo bc_emlrtBCI{
      -1,                                         // iFirst
      -1,                                         // iLast
      127,                                        // lineNo
      54,                                         // colNo
      "colDividerLocs",                           // aName
      "str2matrix",                               // fName
      "H:\\repos\\uavrt_detection\\str2matrix.m", // pName
      0                                           // checkKind
  };
  static rtBoundsCheckInfo cc_emlrtBCI{
      -1,                                         // iFirst
      -1,                                         // iLast
      127,                                        // lineNo
      74,                                         // colNo
      "colDividerLocs",                           // aName
      "str2matrix",                               // fName
      "H:\\repos\\uavrt_detection\\str2matrix.m", // pName
      0                                           // checkKind
  };
  static rtBoundsCheckInfo dc_emlrtBCI{
      -1,                                         // iFirst
      -1,                                         // iLast
      128,                                        // lineNo
      17,                                         // colNo
      "tempRow",                                  // aName
      "str2matrix",                               // fName
      "H:\\repos\\uavrt_detection\\str2matrix.m", // pName
      0                                           // checkKind
  };
  static rtBoundsCheckInfo ec_emlrtBCI{
      -1,                                         // iFirst
      -1,                                         // iLast
      127,                                        // lineNo
      39,                                         // colNo
      "inputStr",                                 // aName
      "str2matrix",                               // fName
      "H:\\repos\\uavrt_detection\\str2matrix.m", // pName
      0                                           // checkKind
  };
  static rtBoundsCheckInfo fb_emlrtBCI{
      -1,                                         // iFirst
      -1,                                         // iLast
      103,                                        // lineNo
      28,                                         // colNo
      "rowDividerLocs",                           // aName
      "str2matrix",                               // fName
      "H:\\repos\\uavrt_detection\\str2matrix.m", // pName
      0                                           // checkKind
  };
  static rtBoundsCheckInfo fc_emlrtBCI{
      -1,                                         // iFirst
      -1,                                         // iLast
      127,                                        // lineNo
      59,                                         // colNo
      "inputStr",                                 // aName
      "str2matrix",                               // fName
      "H:\\repos\\uavrt_detection\\str2matrix.m", // pName
      0                                           // checkKind
  };
  static rtBoundsCheckInfo gb_emlrtBCI{
      -1,                                         // iFirst
      -1,                                         // iLast
      41,                                         // lineNo
      17,                                         // colNo
      "inputStr",                                 // aName
      "str2matrix",                               // fName
      "H:\\repos\\uavrt_detection\\str2matrix.m", // pName
      0                                           // checkKind
  };
  static rtBoundsCheckInfo gc_emlrtBCI{
      -1,                                         // iFirst
      -1,                                         // iLast
      130,                                        // lineNo
      12,                                         // colNo
      "outMat",                                   // aName
      "str2matrix",                               // fName
      "H:\\repos\\uavrt_detection\\str2matrix.m", // pName
      0                                           // checkKind
  };
  static rtBoundsCheckInfo hb_emlrtBCI{
      -1,                                         // iFirst
      -1,                                         // iLast
      26,                                         // lineNo
      49,                                         // colNo
      "inputStr",                                 // aName
      "str2matrix",                               // fName
      "H:\\repos\\uavrt_detection\\str2matrix.m", // pName
      0                                           // checkKind
  };
  static rtBoundsCheckInfo ib_emlrtBCI{
      -1,                                         // iFirst
      -1,                                         // iLast
      26,                                         // lineNo
      25,                                         // colNo
      "inputStr",                                 // aName
      "str2matrix",                               // fName
      "H:\\repos\\uavrt_detection\\str2matrix.m", // pName
      0                                           // checkKind
  };
  static rtBoundsCheckInfo jb_emlrtBCI{
      -1,                                         // iFirst
      -1,                                         // iLast
      41,                                         // lineNo
      45,                                         // colNo
      "inputStr",                                 // aName
      "str2matrix",                               // fName
      "H:\\repos\\uavrt_detection\\str2matrix.m", // pName
      0                                           // checkKind
  };
  static rtBoundsCheckInfo kb_emlrtBCI{
      -1,                                         // iFirst
      -1,                                         // iLast
      46,                                         // lineNo
      18,                                         // colNo
      "inputStr",                                 // aName
      "str2matrix",                               // fName
      "H:\\repos\\uavrt_detection\\str2matrix.m", // pName
      0                                           // checkKind
  };
  static rtBoundsCheckInfo lb_emlrtBCI{
      -1,                                         // iFirst
      -1,                                         // iLast
      46,                                         // lineNo
      46,                                         // colNo
      "inputStr",                                 // aName
      "str2matrix",                               // fName
      "H:\\repos\\uavrt_detection\\str2matrix.m", // pName
      0                                           // checkKind
  };
  static rtBoundsCheckInfo mb_emlrtBCI{
      -1,                                         // iFirst
      -1,                                         // iLast
      51,                                         // lineNo
      21,                                         // colNo
      "inputStr",                                 // aName
      "str2matrix",                               // fName
      "H:\\repos\\uavrt_detection\\str2matrix.m", // pName
      0                                           // checkKind
  };
  static rtBoundsCheckInfo nb_emlrtBCI{
      -1,                                         // iFirst
      -1,                                         // iLast
      51,                                         // lineNo
      49,                                         // colNo
      "inputStr",                                 // aName
      "str2matrix",                               // fName
      "H:\\repos\\uavrt_detection\\str2matrix.m", // pName
      0                                           // checkKind
  };
  static rtBoundsCheckInfo ob_emlrtBCI{
      -1,                                         // iFirst
      -1,                                         // iLast
      68,                                         // lineNo
      17,                                         // colNo
      "inputStr",                                 // aName
      "str2matrix",                               // fName
      "H:\\repos\\uavrt_detection\\str2matrix.m", // pName
      0                                           // checkKind
  };
  static rtBoundsCheckInfo pb_emlrtBCI{
      -1,                                         // iFirst
      -1,                                         // iLast
      68,                                         // lineNo
      45,                                         // colNo
      "inputStr",                                 // aName
      "str2matrix",                               // fName
      "H:\\repos\\uavrt_detection\\str2matrix.m", // pName
      0                                           // checkKind
  };
  static rtBoundsCheckInfo qb_emlrtBCI{
      -1,                                         // iFirst
      -1,                                         // iLast
      73,                                         // lineNo
      18,                                         // colNo
      "inputStr",                                 // aName
      "str2matrix",                               // fName
      "H:\\repos\\uavrt_detection\\str2matrix.m", // pName
      0                                           // checkKind
  };
  static rtBoundsCheckInfo rb_emlrtBCI{
      -1,                                         // iFirst
      -1,                                         // iLast
      73,                                         // lineNo
      46,                                         // colNo
      "inputStr",                                 // aName
      "str2matrix",                               // fName
      "H:\\repos\\uavrt_detection\\str2matrix.m", // pName
      0                                           // checkKind
  };
  static rtBoundsCheckInfo sb_emlrtBCI{
      -1,                                         // iFirst
      -1,                                         // iLast
      78,                                         // lineNo
      21,                                         // colNo
      "inputStr",                                 // aName
      "str2matrix",                               // fName
      "H:\\repos\\uavrt_detection\\str2matrix.m", // pName
      0                                           // checkKind
  };
  static rtBoundsCheckInfo tb_emlrtBCI{
      -1,                                         // iFirst
      -1,                                         // iLast
      78,                                         // lineNo
      49,                                         // colNo
      "inputStr",                                 // aName
      "str2matrix",                               // fName
      "H:\\repos\\uavrt_detection\\str2matrix.m", // pName
      0                                           // checkKind
  };
  static rtBoundsCheckInfo ub_emlrtBCI{
      -1,                                         // iFirst
      -1,                                         // iLast
      88,                                         // lineNo
      10,                                         // colNo
      "inputStr",                                 // aName
      "str2matrix",                               // fName
      "H:\\repos\\uavrt_detection\\str2matrix.m", // pName
      0                                           // checkKind
  };
  static rtBoundsCheckInfo vb_emlrtBCI{
      -1,                                         // iFirst
      -1,                                         // iLast
      104,                                        // lineNo
      28,                                         // colNo
      "rowDividerLocs",                           // aName
      "str2matrix",                               // fName
      "H:\\repos\\uavrt_detection\\str2matrix.m", // pName
      0                                           // checkKind
  };
  static rtBoundsCheckInfo wb_emlrtBCI{
      -1,                                         // iFirst
      -1,                                         // iLast
      105,                                        // lineNo
      28,                                         // colNo
      "commaLocs",                                // aName
      "str2matrix",                               // fName
      "H:\\repos\\uavrt_detection\\str2matrix.m", // pName
      0                                           // checkKind
  };
  static rtBoundsCheckInfo xb_emlrtBCI{
      -1,                                         // iFirst
      -1,                                         // iLast
      112,                                        // lineNo
      32,                                         // colNo
      "rowDividerLocs",                           // aName
      "str2matrix",                               // fName
      "H:\\repos\\uavrt_detection\\str2matrix.m", // pName
      0                                           // checkKind
  };
  static rtBoundsCheckInfo yb_emlrtBCI{
      -1,                                         // iFirst
      -1,                                         // iLast
      113,                                        // lineNo
      32,                                         // colNo
      "rowDividerLocs",                           // aName
      "str2matrix",                               // fName
      "H:\\repos\\uavrt_detection\\str2matrix.m", // pName
      0                                           // checkKind
  };
  static rtDoubleCheckInfo t_emlrtDCI{
      108,                                        // lineNo
      24,                                         // colNo
      "str2matrix",                               // fName
      "H:\\repos\\uavrt_detection\\str2matrix.m", // pName
      4                                           // checkKind
  };
  static rtDoubleCheckInfo u_emlrtDCI{
      108,                                        // lineNo
      34,                                         // colNo
      "str2matrix",                               // fName
      "H:\\repos\\uavrt_detection\\str2matrix.m", // pName
      1                                           // checkKind
  };
  static rtDoubleCheckInfo v_emlrtDCI{
      108,                                        // lineNo
      1,                                          // colNo
      "str2matrix",                               // fName
      "H:\\repos\\uavrt_detection\\str2matrix.m", // pName
      4                                           // checkKind
  };
  static rtDoubleCheckInfo w_emlrtDCI{
      108,                                        // lineNo
      1,                                          // colNo
      "str2matrix",                               // fName
      "H:\\repos\\uavrt_detection\\str2matrix.m", // pName
      1                                           // checkKind
  };
  static rtDoubleCheckInfo x_emlrtDCI{
      124,                                        // lineNo
      31,                                         // colNo
      "str2matrix",                               // fName
      "H:\\repos\\uavrt_detection\\str2matrix.m", // pName
      1                                           // checkKind
  };
  static rtDoubleCheckInfo y_emlrtDCI{
      124,                                        // lineNo
      5,                                          // colNo
      "str2matrix",                               // fName
      "H:\\repos\\uavrt_detection\\str2matrix.m", // pName
      1                                           // checkKind
  };
  static rtEqualityCheckInfo g_emlrtECI{
      2,                                         // nDims
      105,                                       // lineNo
      28,                                        // colNo
      "str2matrix",                              // fName
      "H:\\repos\\uavrt_detection\\str2matrix.m" // pName
  };
  static rtEqualityCheckInfo h_emlrtECI{
      2,                                         // nDims
      114,                                       // lineNo
      32,                                        // colNo
      "str2matrix",                              // fName
      "H:\\repos\\uavrt_detection\\str2matrix.m" // pName
  };
  static rtEqualityCheckInfo i_emlrtECI{
      -1,                                        // nDims
      130,                                       // lineNo
      5,                                         // colNo
      "str2matrix",                              // fName
      "H:\\repos\\uavrt_detection\\str2matrix.m" // pName
  };
  coder::array<creal_T, 2U> tempRow;
  coder::array<double, 2U> rightBracketLoc;
  coder::array<double, 2U> rowDividerLocs;
  coder::array<int, 2U> ii;
  coder::array<int, 2U> leftBracketLoc;
  coder::array<int, 2U> r1;
  coder::array<char, 2U> c_inputStr;
  coder::array<boolean_T, 2U> b_inputStr;
  coder::array<boolean_T, 2U> r;
  double b_rowDividerLocs;
  int iv[2];
  int iv1[2];
  int iv2[2];
  int b_i;
  int b_j1;
  unsigned int i;
  int j2;
  int loop_ub;
  int n;
  int nd2;
  int trueCount;
  char xtmp;
  boolean_T done;
  boolean_T guard1{false};
  boolean_T guard2{false};
  // Strip redundant white space
  done = false;
  i = 1U;
  while (!done) {
    done = (i + 1U == static_cast<unsigned int>(inputStr.size(1)));
    if ((static_cast<int>(i) < 1) || (static_cast<int>(i) > inputStr.size(1))) {
      rtDynamicBoundsError(static_cast<int>(i), 1, inputStr.size(1),
                           &ib_emlrtBCI);
    }
    b_i = static_cast<unsigned char>(inputStr[static_cast<int>(i) - 1]);
    if (b_i > 127) {
      qc_rtErrorWithMessageID(j_emlrtRTEI.fName, j_emlrtRTEI.lineNo);
    }
    if (bv[b_i]) {
      if ((static_cast<int>(static_cast<double>(i) + 1.0) < 1) ||
          (static_cast<int>(static_cast<double>(i) + 1.0) > inputStr.size(1))) {
        rtDynamicBoundsError(static_cast<int>(static_cast<double>(i) + 1.0), 1,
                             inputStr.size(1), &hb_emlrtBCI);
      }
      b_i = static_cast<unsigned char>(inputStr[static_cast<int>(i)]);
      if (b_i > 127) {
        qc_rtErrorWithMessageID(j_emlrtRTEI.fName, j_emlrtRTEI.lineNo);
      }
      if (bv[b_i]) {
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
    if ((static_cast<int>(i) < 1) || (static_cast<int>(i) > inputStr.size(1))) {
      rtDynamicBoundsError(static_cast<int>(i), 1, inputStr.size(1),
                           &gb_emlrtBCI);
    }
    xtmp = inputStr[static_cast<int>(i) - 1];
    guard1 = false;
    guard2 = false;
    if (xtmp == '[') {
      if ((static_cast<int>(static_cast<double>(i) + 1.0) < 1) ||
          (static_cast<int>(static_cast<double>(i) + 1.0) > inputStr.size(1))) {
        rtDynamicBoundsError(static_cast<int>(static_cast<double>(i) + 1.0), 1,
                             inputStr.size(1), &jb_emlrtBCI);
      }
      b_i = static_cast<unsigned char>(inputStr[static_cast<int>(i)]);
      if (b_i > 127) {
        qc_rtErrorWithMessageID(j_emlrtRTEI.fName, j_emlrtRTEI.lineNo);
      }
      if (bv[b_i]) {
        // inputStr(i+1) = '';
        // inputStr = inputStr(1:numel(inputStr) ~= i+1);
        coder::internal::nullAssignment(inputStr, static_cast<int>(i) + 1);
        i = static_cast<unsigned int>(static_cast<int>(i) - 1);
      } else {
        guard2 = true;
      }
    } else {
      guard2 = true;
    }
    if (guard2) {
      if ((static_cast<int>(i) < 1) ||
          (static_cast<int>(i) > inputStr.size(1))) {
        rtDynamicBoundsError(static_cast<int>(i), 1, inputStr.size(1),
                             &kb_emlrtBCI);
      }
      if (xtmp == ',') {
        if ((static_cast<int>(static_cast<double>(i) + 1.0) < 1) ||
            (static_cast<int>(static_cast<double>(i) + 1.0) >
             inputStr.size(1))) {
          rtDynamicBoundsError(static_cast<int>(static_cast<double>(i) + 1.0),
                               1, inputStr.size(1), &lb_emlrtBCI);
        }
        if (static_cast<unsigned char>(inputStr[static_cast<int>(i)]) > 127) {
          qc_rtErrorWithMessageID(j_emlrtRTEI.fName, j_emlrtRTEI.lineNo);
        }
        if (bv[static_cast<unsigned char>(inputStr[static_cast<int>(i)]) &
               127]) {
          // inputStr(i+1) = '';
          // inputStr = inputStr(1:numel(inputStr) ~= i+1);
          coder::internal::nullAssignment(inputStr, static_cast<int>(i) + 1);
          i = static_cast<unsigned int>(static_cast<int>(i) - 1);
        } else {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }
    }
    if (guard1) {
      if ((static_cast<int>(i) < 1) ||
          (static_cast<int>(i) > inputStr.size(1))) {
        rtDynamicBoundsError(static_cast<int>(i), 1, inputStr.size(1),
                             &mb_emlrtBCI);
      }
      if (xtmp == ';') {
        if ((static_cast<int>(static_cast<double>(i) + 1.0) < 1) ||
            (static_cast<int>(static_cast<double>(i) + 1.0) >
             inputStr.size(1))) {
          rtDynamicBoundsError(static_cast<int>(static_cast<double>(i) + 1.0),
                               1, inputStr.size(1), &nb_emlrtBCI);
        }
        if (static_cast<unsigned char>(inputStr[static_cast<int>(i)]) > 127) {
          qc_rtErrorWithMessageID(j_emlrtRTEI.fName, j_emlrtRTEI.lineNo);
        }
        if (bv[static_cast<unsigned char>(inputStr[static_cast<int>(i)]) &
               127]) {
          // inputStr(i+1) = '';
          // inputStr = inputStr(1:numel(inputStr) ~= i+1);
          coder::internal::nullAssignment(inputStr, static_cast<int>(i) + 1);
          i = static_cast<unsigned int>(static_cast<int>(i) - 1);
        }
      }
    }
    i++;
  }
  // Strip out white space before [ ; and , characters
  n = inputStr.size(1) - 1;
  nd2 = inputStr.size(1) >> 1;
  for (b_j1 = 0; b_j1 < nd2; b_j1++) {
    j2 = n - b_j1;
    xtmp = inputStr[b_j1];
    inputStr[b_j1] = inputStr[j2];
    inputStr[j2] = xtmp;
  }
  done = false;
  i = 1U;
  while (!done) {
    done = (i + 1U == static_cast<unsigned int>(inputStr.size(1)));
    if ((static_cast<int>(i) < 1) || (static_cast<int>(i) > inputStr.size(1))) {
      rtDynamicBoundsError(static_cast<int>(i), 1, inputStr.size(1),
                           &ob_emlrtBCI);
    }
    xtmp = inputStr[static_cast<int>(i) - 1];
    guard1 = false;
    guard2 = false;
    if (xtmp == '[') {
      if ((static_cast<int>(static_cast<double>(i) + 1.0) < 1) ||
          (static_cast<int>(static_cast<double>(i) + 1.0) > inputStr.size(1))) {
        rtDynamicBoundsError(static_cast<int>(static_cast<double>(i) + 1.0), 1,
                             inputStr.size(1), &pb_emlrtBCI);
      }
      b_i = static_cast<unsigned char>(inputStr[static_cast<int>(i)]);
      if (b_i > 127) {
        qc_rtErrorWithMessageID(j_emlrtRTEI.fName, j_emlrtRTEI.lineNo);
      }
      if (bv[b_i]) {
        // inputStr(i+1) = '';
        // inputStr = inputStr(1:numel(inputStr) ~= i+1);
        coder::internal::nullAssignment(inputStr, static_cast<int>(i) + 1);
        i = static_cast<unsigned int>(static_cast<int>(i) - 1);
      } else {
        guard2 = true;
      }
    } else {
      guard2 = true;
    }
    if (guard2) {
      if ((static_cast<int>(i) < 1) ||
          (static_cast<int>(i) > inputStr.size(1))) {
        rtDynamicBoundsError(static_cast<int>(i), 1, inputStr.size(1),
                             &qb_emlrtBCI);
      }
      if (xtmp == ',') {
        if ((static_cast<int>(static_cast<double>(i) + 1.0) < 1) ||
            (static_cast<int>(static_cast<double>(i) + 1.0) >
             inputStr.size(1))) {
          rtDynamicBoundsError(static_cast<int>(static_cast<double>(i) + 1.0),
                               1, inputStr.size(1), &rb_emlrtBCI);
        }
        if (static_cast<unsigned char>(inputStr[static_cast<int>(i)]) > 127) {
          qc_rtErrorWithMessageID(j_emlrtRTEI.fName, j_emlrtRTEI.lineNo);
        }
        if (bv[static_cast<unsigned char>(inputStr[static_cast<int>(i)]) &
               127]) {
          // inputStr(i+1) = '';
          // inputStr = inputStr(1:numel(inputStr) ~= i+1);
          coder::internal::nullAssignment(inputStr, static_cast<int>(i) + 1);
          i = static_cast<unsigned int>(static_cast<int>(i) - 1);
        } else {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }
    }
    if (guard1) {
      if ((static_cast<int>(i) < 1) ||
          (static_cast<int>(i) > inputStr.size(1))) {
        rtDynamicBoundsError(static_cast<int>(i), 1, inputStr.size(1),
                             &sb_emlrtBCI);
      }
      if (xtmp == ';') {
        if ((static_cast<int>(static_cast<double>(i) + 1.0) < 1) ||
            (static_cast<int>(static_cast<double>(i) + 1.0) >
             inputStr.size(1))) {
          rtDynamicBoundsError(static_cast<int>(static_cast<double>(i) + 1.0),
                               1, inputStr.size(1), &tb_emlrtBCI);
        }
        if (static_cast<unsigned char>(inputStr[static_cast<int>(i)]) > 127) {
          qc_rtErrorWithMessageID(j_emlrtRTEI.fName, j_emlrtRTEI.lineNo);
        }
        if (bv[static_cast<unsigned char>(inputStr[static_cast<int>(i)]) &
               127]) {
          // inputStr(i+1) = '';
          // inputStr = inputStr(1:numel(inputStr) ~= i+1);
          coder::internal::nullAssignment(inputStr, static_cast<int>(i) + 1);
          i = static_cast<unsigned int>(static_cast<int>(i) - 1);
        }
      }
    }
    i++;
  }
  n = inputStr.size(1) - 1;
  nd2 = inputStr.size(1) >> 1;
  for (b_j1 = 0; b_j1 < nd2; b_j1++) {
    j2 = n - b_j1;
    xtmp = inputStr[b_j1];
    inputStr[b_j1] = inputStr[j2];
    inputStr[j2] = xtmp;
  }
  // Replace space with commas for marking columns
  nd2 = inputStr.size(1);
  for (int c_i{0}; c_i < nd2; c_i++) {
    if (inputStr[c_i] == ' ') {
      if (c_i + 1 > inputStr.size(1)) {
        rtDynamicBoundsError(c_i + 1, 1, inputStr.size(1), &ub_emlrtBCI);
      }
      inputStr[c_i] = ',';
    }
  }
  b_inputStr.set_size(1, inputStr.size(1));
  n = inputStr.size(1);
  for (b_i = 0; b_i < n; b_i++) {
    b_inputStr[b_i] = (inputStr[b_i] == '[');
  }
  coder::b_eml_find(b_inputStr, ii);
  leftBracketLoc.set_size(1, ii.size(1));
  n = ii.size(1);
  for (b_i = 0; b_i < n; b_i++) {
    leftBracketLoc[b_i] = ii[b_i];
  }
  b_inputStr.set_size(1, inputStr.size(1));
  n = inputStr.size(1);
  for (b_i = 0; b_i < n; b_i++) {
    b_inputStr[b_i] = (inputStr[b_i] == ']');
  }
  coder::b_eml_find(b_inputStr, ii);
  rightBracketLoc.set_size(1, ii.size(1));
  n = ii.size(1);
  for (b_i = 0; b_i < n; b_i++) {
    rightBracketLoc[b_i] = ii[b_i];
  }
  if ((leftBracketLoc.size(1) != 1) || (rightBracketLoc.size(1) != 1)) {
    rtErrorWithMessageID(b_emlrtRTEI.fName, b_emlrtRTEI.lineNo);
  }
  b_inputStr.set_size(1, inputStr.size(1));
  n = inputStr.size(1);
  for (b_i = 0; b_i < n; b_i++) {
    b_inputStr[b_i] = (inputStr[b_i] == ';');
  }
  coder::b_eml_find(b_inputStr, ii);
  rowDividerLocs.set_size(1, ii.size(1) + 2);
  rowDividerLocs[0] = leftBracketLoc[0];
  n = ii.size(1);
  for (b_i = 0; b_i < n; b_i++) {
    rowDividerLocs[b_i + 1] = ii[b_i];
  }
  rowDividerLocs[ii.size(1) + 1] = rightBracketLoc[0];
  coder::internal::sort(rowDividerLocs);
  b_inputStr.set_size(1, inputStr.size(1));
  n = inputStr.size(1);
  for (b_i = 0; b_i < n; b_i++) {
    b_inputStr[b_i] = (inputStr[b_i] == ',');
  }
  coder::b_eml_find(b_inputStr, ii);
  leftBracketLoc.set_size(1, ii.size(1));
  n = ii.size(1);
  for (b_i = 0; b_i < n; b_i++) {
    leftBracketLoc[b_i] = ii[b_i];
  }
  // Check for the number of columns in the first row to preallocate outMat
  if (rowDividerLocs.size(1) < 1) {
    rtDynamicBoundsError(1, 1, rowDividerLocs.size(1), &fb_emlrtBCI);
  }
  if (rowDividerLocs.size(1) < 2) {
    rtDynamicBoundsError(2, 1, rowDividerLocs.size(1), &vb_emlrtBCI);
  }
  b_inputStr.set_size(1, leftBracketLoc.size(1));
  b_rowDividerLocs = rowDividerLocs[0];
  n = leftBracketLoc.size(1);
  for (b_i = 0; b_i < n; b_i++) {
    b_inputStr[b_i] = (leftBracketLoc[b_i] > b_rowDividerLocs);
  }
  r.set_size(1, leftBracketLoc.size(1));
  b_rowDividerLocs = rowDividerLocs[1];
  n = leftBracketLoc.size(1);
  for (b_i = 0; b_i < n; b_i++) {
    r[b_i] = (leftBracketLoc[b_i] < b_rowDividerLocs);
  }
  iv[0] = (*(int(*)[2])b_inputStr.size())[0];
  iv[1] = (*(int(*)[2])b_inputStr.size())[1];
  iv1[0] = (*(int(*)[2])r.size())[0];
  iv1[1] = (*(int(*)[2])r.size())[1];
  rtSizeEqNDCheck(&iv[0], &iv1[0], &g_emlrtECI);
  nd2 = b_inputStr.size(1);
  for (int c_i{0}; c_i < nd2; c_i++) {
    if (b_inputStr[c_i] && r[c_i] && (c_i + 1 > leftBracketLoc.size(1))) {
      rtDynamicBoundsError(c_i + 1, 1, leftBracketLoc.size(1), &wb_emlrtBCI);
    }
  }
  nd2 = b_inputStr.size(1);
  trueCount = 0;
  for (int c_i{0}; c_i < nd2; c_i++) {
    if (b_inputStr[c_i] && r[c_i]) {
      trueCount++;
    }
  }
  if (rowDividerLocs.size(1) - 1 < 0) {
    rtNonNegativeError(-1.0, &t_emlrtDCI);
  }
  outMat.set_size(rowDividerLocs.size(1) - 1, outMat.size(1));
  b_rowDividerLocs = trueCount + 1;
  if (static_cast<double>(trueCount) + 1.0 != b_rowDividerLocs) {
    rtIntegerError(static_cast<double>(trueCount) + 1.0, &u_emlrtDCI);
  }
  outMat.set_size(outMat.size(0), trueCount + 1);
  if (rowDividerLocs.size(1) - 1 < 0) {
    rtNonNegativeError(-1.0, &v_emlrtDCI);
  }
  if (static_cast<double>(trueCount) + 1.0 != b_rowDividerLocs) {
    rtIntegerError(static_cast<double>(trueCount) + 1.0, &w_emlrtDCI);
  }
  n = (rowDividerLocs.size(1) - 1) * (trueCount + 1);
  for (b_i = 0; b_i < n; b_i++) {
    outMat[b_i].re = 0.0;
    outMat[b_i].im = 0.0;
  }
  n = 0;
  b_i = rowDividerLocs.size(1);
  if (rowDividerLocs.size(1) - 2 >= 0) {
    loop_ub = leftBracketLoc.size(1);
    iv2[0] = 1;
  }
  for (int c_i{0}; c_i <= b_i - 2; c_i++) {
    double rowDividerLocs_tmp;
    int i1;
    if (c_i + 1 > rowDividerLocs.size(1)) {
      rtDynamicBoundsError(c_i + 1, 1, rowDividerLocs.size(1), &xb_emlrtBCI);
    }
    if (c_i + 2 > rowDividerLocs.size(1)) {
      rtDynamicBoundsError(c_i + 2, 1, rowDividerLocs.size(1), &yb_emlrtBCI);
    }
    b_inputStr.set_size(1, leftBracketLoc.size(1));
    b_rowDividerLocs = rowDividerLocs[c_i];
    r.set_size(1, leftBracketLoc.size(1));
    rowDividerLocs_tmp = rowDividerLocs[c_i + 1];
    for (i1 = 0; i1 < loop_ub; i1++) {
      nd2 = leftBracketLoc[i1];
      b_inputStr[i1] = (nd2 > b_rowDividerLocs);
      r[i1] = (nd2 < rowDividerLocs_tmp);
    }
    iv[0] = (*(int(*)[2])b_inputStr.size())[0];
    iv[1] = (*(int(*)[2])b_inputStr.size())[1];
    iv1[0] = (*(int(*)[2])r.size())[0];
    iv1[1] = (*(int(*)[2])r.size())[1];
    rtSizeEqNDCheck(&iv[0], &iv1[0], &h_emlrtECI);
    nd2 = b_inputStr.size(1);
    for (j2 = 0; j2 < nd2; j2++) {
      if (b_inputStr[j2] && r[j2] && (j2 + 1 > leftBracketLoc.size(1))) {
        rtDynamicBoundsError(j2 + 1, 1, leftBracketLoc.size(1), &ac_emlrtBCI);
      }
    }
    nd2 = b_inputStr.size(1);
    trueCount = 0;
    for (j2 = 0; j2 < nd2; j2++) {
      if (b_inputStr[j2] && r[j2]) {
        trueCount++;
      }
    }
    // numelCols = numelCommasCurr+1;
    if ((c_i + 1 > 1) && (trueCount != n)) {
      rtErrorWithMessageID(b_emlrtRTEI.fName, b_emlrtRTEI.lineNo);
    }
    nd2 = b_inputStr.size(1) - 1;
    n = 0;
    for (j2 = 0; j2 <= nd2; j2++) {
      if (b_inputStr[j2] && r[j2]) {
        n++;
      }
    }
    r1.set_size(1, n);
    n = 0;
    for (j2 = 0; j2 <= nd2; j2++) {
      if (b_inputStr[j2] && r[j2]) {
        r1[n] = j2 + 1;
        n++;
      }
    }
    n = r1.size(1);
    rightBracketLoc.set_size(1, r1.size(1) + 2);
    rightBracketLoc[0] = rowDividerLocs[c_i];
    for (i1 = 0; i1 < n; i1++) {
      rightBracketLoc[i1 + 1] = leftBracketLoc[r1[i1] - 1];
    }
    rightBracketLoc[r1.size(1) + 1] = rowDividerLocs_tmp;
    tempRow.set_size(1, tempRow.size(1));
    b_rowDividerLocs = trueCount + 1;
    if (static_cast<double>(trueCount) + 1.0 != b_rowDividerLocs) {
      rtIntegerError(static_cast<double>(trueCount) + 1.0, &x_emlrtDCI);
    }
    tempRow.set_size(tempRow.size(0), trueCount + 1);
    if (static_cast<double>(trueCount) + 1.0 != b_rowDividerLocs) {
      rtIntegerError(static_cast<double>(trueCount) + 1.0, &y_emlrtDCI);
    }
    n = trueCount + 1;
    for (i1 = 0; i1 < n; i1++) {
      tempRow[i1].re = 0.0;
      tempRow[i1].im = 0.0;
    }
    i1 = rightBracketLoc.size(1);
    for (j2 = 0; j2 <= i1 - 2; j2++) {
      if (j2 + 1 > rightBracketLoc.size(1)) {
        rtDynamicBoundsError(j2 + 1, 1, rightBracketLoc.size(1), &bc_emlrtBCI);
      }
      if (j2 + 2 > rightBracketLoc.size(1)) {
        rtDynamicBoundsError(j2 + 2, 1, rightBracketLoc.size(1), &cc_emlrtBCI);
      }
      b_rowDividerLocs = rightBracketLoc[j2 + 1] - 1.0;
      if (rightBracketLoc[j2] + 1.0 > b_rowDividerLocs) {
        nd2 = 0;
        b_j1 = 0;
      } else {
        nd2 = static_cast<int>(rightBracketLoc[j2] + 1.0);
        if ((nd2 < 1) || (nd2 > inputStr.size(1))) {
          rtDynamicBoundsError(nd2, 1, inputStr.size(1), &ec_emlrtBCI);
        }
        nd2--;
        if ((static_cast<int>(b_rowDividerLocs) < 1) ||
            (static_cast<int>(b_rowDividerLocs) > inputStr.size(1))) {
          rtDynamicBoundsError(static_cast<int>(b_rowDividerLocs), 1,
                               inputStr.size(1), &fc_emlrtBCI);
        }
        b_j1 = static_cast<int>(b_rowDividerLocs);
      }
      n = b_j1 - nd2;
      c_inputStr.set_size(1, n);
      for (b_j1 = 0; b_j1 < n; b_j1++) {
        c_inputStr[b_j1] = inputStr[nd2 + b_j1];
      }
      if (j2 + 1 > tempRow.size(1)) {
        rtDynamicBoundsError(j2 + 1, 1, tempRow.size(1), &dc_emlrtBCI);
      }
      tempRow[j2] = coder::str2double(c_inputStr);
    }
    if (c_i + 1 > outMat.size(0)) {
      rtDynamicBoundsError(c_i + 1, 1, outMat.size(0), &gc_emlrtBCI);
    }
    iv2[1] = outMat.size(1);
    rtSubAssignSizeCheck(&iv2[0], 2, tempRow.size(), 2, &i_emlrtECI);
    n = tempRow.size(1);
    for (i1 = 0; i1 < n; i1++) {
      outMat[c_i + outMat.size(0) * i1] = tempRow[i1];
    }
    n = trueCount;
  }
}

//
// File trailer for str2matrix.cpp
//
// [EOF]
//
