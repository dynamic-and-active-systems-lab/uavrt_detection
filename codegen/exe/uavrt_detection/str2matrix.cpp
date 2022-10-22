//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: str2matrix.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 22-Oct-2022 15:24:58
//

// Include Files
#include "str2matrix.h"
#include "find.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include "str2double.h"
#include "uavrt_detection_data.h"
#include "coder_array.h"

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
  coder::array<creal_T, 2U> tempRow;
  coder::array<double, 2U> colDividerLocs;
  coder::array<double, 2U> rowDividerLocs;
  coder::array<int, 2U> commaLocs;
  coder::array<int, 2U> r;
  coder::array<int, 2U> r1;
  coder::array<int, 2U> r3;
  coder::array<char, 2U> c_inputStr;
  coder::array<boolean_T, 2U> b_inputStr;
  coder::array<boolean_T, 2U> r2;
  double b_rowDividerLocs;
  int b_i;
  int b_j1;
  unsigned int i;
  int j2;
  int nd2;
  char xtmp;
  boolean_T done;
  // Strip redundant white space
  done = false;
  i = 1U;
  while (!done) {
    done = (i + 1U == static_cast<unsigned int>(inputStr.size(1)));
    if (bv[static_cast<unsigned char>(inputStr[static_cast<int>(i) - 1]) &
           127] &&
        bv[static_cast<unsigned char>(inputStr[static_cast<int>(i)]) & 127]) {
      // inputStr(i+1) = '';
      // inputStr = inputStr(1:numel(inputStr) ~= i+1);
      nd2 = static_cast<int>(i) + 1;
      j2 = inputStr.size(1) - 1;
      for (b_j1 = nd2; b_j1 <= j2; b_j1++) {
        inputStr[b_j1 - 1] = inputStr[b_j1];
      }
      if (inputStr.size(1) - 1 < 1) {
        b_i = 0;
      } else {
        b_i = inputStr.size(1) - 1;
      }
      inputStr.set_size(inputStr.size(0), b_i);
      i = static_cast<unsigned int>(static_cast<int>(i) - 1);
    }
    i++;
  }
  // Strip out white space after [ ; and , characters
  done = false;
  i = 1U;
  while (!done) {
    done = (i + 1U == static_cast<unsigned int>(inputStr.size(1)));
    xtmp = inputStr[static_cast<int>(i) - 1];
    if ((xtmp == '[') &&
        bv[static_cast<unsigned char>(inputStr[static_cast<int>(i)]) & 127]) {
      // inputStr(i+1) = '';
      // inputStr = inputStr(1:numel(inputStr) ~= i+1);
      nd2 = static_cast<int>(i) + 1;
      j2 = inputStr.size(1) - 1;
      for (b_j1 = nd2; b_j1 <= j2; b_j1++) {
        inputStr[b_j1 - 1] = inputStr[b_j1];
      }
      if (inputStr.size(1) - 1 < 1) {
        b_i = 0;
      } else {
        b_i = inputStr.size(1) - 1;
      }
      inputStr.set_size(inputStr.size(0), b_i);
      i = static_cast<unsigned int>(static_cast<int>(i) - 1);
    } else if ((xtmp == ',') &&
               bv[static_cast<unsigned char>(inputStr[static_cast<int>(i)]) &
                  127]) {
      // inputStr(i+1) = '';
      // inputStr = inputStr(1:numel(inputStr) ~= i+1);
      nd2 = static_cast<int>(i) + 1;
      j2 = inputStr.size(1) - 1;
      for (b_j1 = nd2; b_j1 <= j2; b_j1++) {
        inputStr[b_j1 - 1] = inputStr[b_j1];
      }
      if (inputStr.size(1) - 1 < 1) {
        b_i = 0;
      } else {
        b_i = inputStr.size(1) - 1;
      }
      inputStr.set_size(inputStr.size(0), b_i);
      i = static_cast<unsigned int>(static_cast<int>(i) - 1);
    } else if ((xtmp == ';') &&
               bv[static_cast<unsigned char>(inputStr[static_cast<int>(i)]) &
                  127]) {
      // inputStr(i+1) = '';
      // inputStr = inputStr(1:numel(inputStr) ~= i+1);
      nd2 = static_cast<int>(i) + 1;
      j2 = inputStr.size(1) - 1;
      for (b_j1 = nd2; b_j1 <= j2; b_j1++) {
        inputStr[b_j1 - 1] = inputStr[b_j1];
      }
      if (inputStr.size(1) - 1 < 1) {
        b_i = 0;
      } else {
        b_i = inputStr.size(1) - 1;
      }
      inputStr.set_size(inputStr.size(0), b_i);
      i = static_cast<unsigned int>(static_cast<int>(i) - 1);
    }
    i++;
  }
  // Strip out white space before [ ; and , characters
  nd2 = inputStr.size(1) >> 1;
  for (b_j1 = 0; b_j1 < nd2; b_j1++) {
    j2 = (inputStr.size(1) - b_j1) - 1;
    xtmp = inputStr[b_j1];
    inputStr[b_j1] = inputStr[j2];
    inputStr[j2] = xtmp;
  }
  done = false;
  i = 1U;
  while (!done) {
    done = (i + 1U == static_cast<unsigned int>(inputStr.size(1)));
    xtmp = inputStr[static_cast<int>(i) - 1];
    if ((xtmp == '[') &&
        bv[static_cast<unsigned char>(inputStr[static_cast<int>(i)]) & 127]) {
      // inputStr(i+1) = '';
      // inputStr = inputStr(1:numel(inputStr) ~= i+1);
      nd2 = static_cast<int>(i) + 1;
      j2 = inputStr.size(1) - 1;
      for (b_j1 = nd2; b_j1 <= j2; b_j1++) {
        inputStr[b_j1 - 1] = inputStr[b_j1];
      }
      if (inputStr.size(1) - 1 < 1) {
        b_i = 0;
      } else {
        b_i = inputStr.size(1) - 1;
      }
      inputStr.set_size(inputStr.size(0), b_i);
      i = static_cast<unsigned int>(static_cast<int>(i) - 1);
    } else if ((xtmp == ',') &&
               bv[static_cast<unsigned char>(inputStr[static_cast<int>(i)]) &
                  127]) {
      // inputStr(i+1) = '';
      // inputStr = inputStr(1:numel(inputStr) ~= i+1);
      nd2 = static_cast<int>(i) + 1;
      j2 = inputStr.size(1) - 1;
      for (b_j1 = nd2; b_j1 <= j2; b_j1++) {
        inputStr[b_j1 - 1] = inputStr[b_j1];
      }
      if (inputStr.size(1) - 1 < 1) {
        b_i = 0;
      } else {
        b_i = inputStr.size(1) - 1;
      }
      inputStr.set_size(inputStr.size(0), b_i);
      i = static_cast<unsigned int>(static_cast<int>(i) - 1);
    } else if ((xtmp == ';') &&
               bv[static_cast<unsigned char>(inputStr[static_cast<int>(i)]) &
                  127]) {
      // inputStr(i+1) = '';
      // inputStr = inputStr(1:numel(inputStr) ~= i+1);
      nd2 = static_cast<int>(i) + 1;
      j2 = inputStr.size(1) - 1;
      for (b_j1 = nd2; b_j1 <= j2; b_j1++) {
        inputStr[b_j1 - 1] = inputStr[b_j1];
      }
      if (inputStr.size(1) - 1 < 1) {
        b_i = 0;
      } else {
        b_i = inputStr.size(1) - 1;
      }
      inputStr.set_size(inputStr.size(0), b_i);
      i = static_cast<unsigned int>(static_cast<int>(i) - 1);
    }
    i++;
  }
  nd2 = inputStr.size(1) >> 1;
  for (b_j1 = 0; b_j1 < nd2; b_j1++) {
    j2 = (inputStr.size(1) - b_j1) - 1;
    xtmp = inputStr[b_j1];
    inputStr[b_j1] = inputStr[j2];
    inputStr[j2] = xtmp;
  }
  // Replace space with commas for marking columns
  j2 = inputStr.size(1);
  for (int c_i{0}; c_i < j2; c_i++) {
    if (inputStr[c_i] == ' ') {
      inputStr[c_i] = ',';
    }
  }
  b_inputStr.set_size(1, inputStr.size(1));
  j2 = inputStr.size(1);
  for (b_i = 0; b_i < j2; b_i++) {
    b_inputStr[b_i] = (inputStr[b_i] == '[');
  }
  coder::b_eml_find(b_inputStr, commaLocs);
  b_inputStr.set_size(1, inputStr.size(1));
  j2 = inputStr.size(1);
  for (b_i = 0; b_i < j2; b_i++) {
    b_inputStr[b_i] = (inputStr[b_i] == ';');
  }
  coder::b_eml_find(b_inputStr, r);
  b_inputStr.set_size(1, inputStr.size(1));
  j2 = inputStr.size(1);
  for (b_i = 0; b_i < j2; b_i++) {
    b_inputStr[b_i] = (inputStr[b_i] == ']');
  }
  coder::b_eml_find(b_inputStr, r1);
  rowDividerLocs.set_size(1, (commaLocs.size(1) + r.size(1)) + r1.size(1));
  j2 = commaLocs.size(1);
  for (b_i = 0; b_i < j2; b_i++) {
    rowDividerLocs[b_i] = commaLocs[b_i];
  }
  j2 = r.size(1);
  for (b_i = 0; b_i < j2; b_i++) {
    rowDividerLocs[b_i + commaLocs.size(1)] = r[b_i];
  }
  j2 = r1.size(1);
  for (b_i = 0; b_i < j2; b_i++) {
    rowDividerLocs[(b_i + commaLocs.size(1)) + r.size(1)] = r1[b_i];
  }
  coder::internal::sort(rowDividerLocs);
  b_inputStr.set_size(1, inputStr.size(1));
  j2 = inputStr.size(1);
  for (b_i = 0; b_i < j2; b_i++) {
    b_inputStr[b_i] = (inputStr[b_i] == ',');
  }
  coder::b_eml_find(b_inputStr, commaLocs);
  // Check for the number of columns in the first row to preallocate outMat
  b_inputStr.set_size(1, commaLocs.size(1));
  b_rowDividerLocs = rowDividerLocs[0];
  j2 = commaLocs.size(1);
  for (b_i = 0; b_i < j2; b_i++) {
    b_inputStr[b_i] = (commaLocs[b_i] > b_rowDividerLocs);
  }
  r2.set_size(1, commaLocs.size(1));
  b_rowDividerLocs = rowDividerLocs[1];
  j2 = commaLocs.size(1);
  for (b_i = 0; b_i < j2; b_i++) {
    r2[b_i] = (commaLocs[b_i] < b_rowDividerLocs);
  }
  j2 = b_inputStr.size(1);
  b_j1 = 1;
  for (int c_i{0}; c_i < j2; c_i++) {
    if (b_inputStr[c_i] && r2[c_i]) {
      b_j1++;
    }
  }
  outMat.set_size(rowDividerLocs.size(1) - 1, b_j1);
  j2 = (rowDividerLocs.size(1) - 1) * b_j1;
  for (b_i = 0; b_i < j2; b_i++) {
    outMat[b_i].re = 0.0;
    outMat[b_i].im = 0.0;
  }
  b_i = rowDividerLocs.size(1);
  for (int c_i{0}; c_i <= b_i - 2; c_i++) {
    double rowDividerLocs_tmp;
    int d_i;
    int i1;
    b_inputStr.set_size(1, commaLocs.size(1));
    b_rowDividerLocs = rowDividerLocs[c_i];
    j2 = commaLocs.size(1);
    r2.set_size(1, commaLocs.size(1));
    rowDividerLocs_tmp = rowDividerLocs[c_i + 1];
    for (i1 = 0; i1 < j2; i1++) {
      nd2 = commaLocs[i1];
      b_inputStr[i1] = (nd2 > b_rowDividerLocs);
      r2[i1] = (nd2 < rowDividerLocs_tmp);
    }
    j2 = b_inputStr.size(1);
    b_j1 = 1;
    for (d_i = 0; d_i < j2; d_i++) {
      if (b_inputStr[d_i] && r2[d_i]) {
        b_j1++;
      }
    }
    // numelCols = numelCommasCurr+1;
    j2 = b_inputStr.size(1) - 1;
    nd2 = 0;
    for (d_i = 0; d_i <= j2; d_i++) {
      if (b_inputStr[d_i] && r2[d_i]) {
        nd2++;
      }
    }
    r3.set_size(1, nd2);
    nd2 = 0;
    for (d_i = 0; d_i <= j2; d_i++) {
      if (b_inputStr[d_i] && r2[d_i]) {
        r3[nd2] = d_i + 1;
        nd2++;
      }
    }
    j2 = r3.size(1);
    colDividerLocs.set_size(1, r3.size(1) + 2);
    colDividerLocs[0] = rowDividerLocs[c_i];
    for (i1 = 0; i1 < j2; i1++) {
      colDividerLocs[i1 + 1] = commaLocs[r3[i1] - 1];
    }
    colDividerLocs[r3.size(1) + 1] = rowDividerLocs_tmp;
    tempRow.set_size(1, b_j1);
    for (i1 = 0; i1 < b_j1; i1++) {
      tempRow[i1].re = 0.0;
      tempRow[i1].im = 0.0;
    }
    i1 = colDividerLocs.size(1);
    for (b_j1 = 0; b_j1 <= i1 - 2; b_j1++) {
      b_rowDividerLocs = colDividerLocs[b_j1];
      rowDividerLocs_tmp = colDividerLocs[b_j1 + 1];
      if (b_rowDividerLocs + 1.0 > rowDividerLocs_tmp - 1.0) {
        nd2 = 0;
        d_i = 0;
      } else {
        nd2 = static_cast<int>(b_rowDividerLocs + 1.0) - 1;
        d_i = static_cast<int>(rowDividerLocs_tmp - 1.0);
      }
      j2 = d_i - nd2;
      c_inputStr.set_size(1, j2);
      for (d_i = 0; d_i < j2; d_i++) {
        c_inputStr[d_i] = inputStr[nd2 + d_i];
      }
      tempRow[b_j1] = coder::str2double(c_inputStr);
    }
    j2 = tempRow.size(1);
    for (i1 = 0; i1 < j2; i1++) {
      outMat[c_i + outMat.size(0) * i1] = tempRow[i1];
    }
  }
}

//
// File trailer for str2matrix.cpp
//
// [EOF]
//
