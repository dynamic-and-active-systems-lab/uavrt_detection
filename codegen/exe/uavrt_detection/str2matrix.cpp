//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// str2matrix.cpp
//
// Code generation for function 'str2matrix'
//

// Include files
#include "str2matrix.h"
#include "find.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include "str2double.h"
#include "uavrt_detection_data.h"
#include "coder_array.h"
#include <string.h>

// Function Definitions
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
  int b_j1;
  int c_i;
  unsigned int i;
  int j2;
  int n;
  int nd2;
  char xtmp;
  boolean_T done;
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
  // Author:    Michael W. Shafer
  // Date:      2022-02-15
  // --------------------------------------------------------------------------
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
      n = static_cast<int>(i) + 1;
      nd2 = inputStr.size(1);
      j2 = inputStr.size(1) - 1;
      for (b_j1 = n; b_j1 <= j2; b_j1++) {
        inputStr[b_j1 - 1] = inputStr[b_j1];
      }
      if (j2 < 1) {
        j2 = 0;
      } else {
        j2 = nd2 - 1;
      }
      inputStr.set_size(inputStr.size(0), j2);
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
      n = static_cast<int>(i) + 1;
      nd2 = inputStr.size(1);
      j2 = inputStr.size(1) - 1;
      for (b_j1 = n; b_j1 <= j2; b_j1++) {
        inputStr[b_j1 - 1] = inputStr[b_j1];
      }
      if (j2 < 1) {
        j2 = 0;
      } else {
        j2 = nd2 - 1;
      }
      inputStr.set_size(inputStr.size(0), j2);
      i = static_cast<unsigned int>(static_cast<int>(i) - 1);
    } else if ((xtmp == ',') &&
               bv[static_cast<unsigned char>(inputStr[static_cast<int>(i)]) &
                  127]) {
      // inputStr(i+1) = '';
      // inputStr = inputStr(1:numel(inputStr) ~= i+1);
      n = static_cast<int>(i) + 1;
      nd2 = inputStr.size(1);
      j2 = inputStr.size(1) - 1;
      for (b_j1 = n; b_j1 <= j2; b_j1++) {
        inputStr[b_j1 - 1] = inputStr[b_j1];
      }
      if (j2 < 1) {
        j2 = 0;
      } else {
        j2 = nd2 - 1;
      }
      inputStr.set_size(inputStr.size(0), j2);
      i = static_cast<unsigned int>(static_cast<int>(i) - 1);
    } else if ((xtmp == ';') &&
               bv[static_cast<unsigned char>(inputStr[static_cast<int>(i)]) &
                  127]) {
      // inputStr(i+1) = '';
      // inputStr = inputStr(1:numel(inputStr) ~= i+1);
      n = static_cast<int>(i) + 1;
      nd2 = inputStr.size(1);
      j2 = inputStr.size(1) - 1;
      for (b_j1 = n; b_j1 <= j2; b_j1++) {
        inputStr[b_j1 - 1] = inputStr[b_j1];
      }
      if (j2 < 1) {
        j2 = 0;
      } else {
        j2 = nd2 - 1;
      }
      inputStr.set_size(inputStr.size(0), j2);
      i = static_cast<unsigned int>(static_cast<int>(i) - 1);
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
    xtmp = inputStr[static_cast<int>(i) - 1];
    if ((xtmp == '[') &&
        bv[static_cast<unsigned char>(inputStr[static_cast<int>(i)]) & 127]) {
      // inputStr(i+1) = '';
      // inputStr = inputStr(1:numel(inputStr) ~= i+1);
      n = static_cast<int>(i) + 1;
      nd2 = inputStr.size(1);
      j2 = inputStr.size(1) - 1;
      for (b_j1 = n; b_j1 <= j2; b_j1++) {
        inputStr[b_j1 - 1] = inputStr[b_j1];
      }
      if (j2 < 1) {
        j2 = 0;
      } else {
        j2 = nd2 - 1;
      }
      inputStr.set_size(inputStr.size(0), j2);
      i = static_cast<unsigned int>(static_cast<int>(i) - 1);
    } else if ((xtmp == ',') &&
               bv[static_cast<unsigned char>(inputStr[static_cast<int>(i)]) &
                  127]) {
      // inputStr(i+1) = '';
      // inputStr = inputStr(1:numel(inputStr) ~= i+1);
      n = static_cast<int>(i) + 1;
      nd2 = inputStr.size(1);
      j2 = inputStr.size(1) - 1;
      for (b_j1 = n; b_j1 <= j2; b_j1++) {
        inputStr[b_j1 - 1] = inputStr[b_j1];
      }
      if (j2 < 1) {
        j2 = 0;
      } else {
        j2 = nd2 - 1;
      }
      inputStr.set_size(inputStr.size(0), j2);
      i = static_cast<unsigned int>(static_cast<int>(i) - 1);
    } else if ((xtmp == ';') &&
               bv[static_cast<unsigned char>(inputStr[static_cast<int>(i)]) &
                  127]) {
      // inputStr(i+1) = '';
      // inputStr = inputStr(1:numel(inputStr) ~= i+1);
      n = static_cast<int>(i) + 1;
      nd2 = inputStr.size(1);
      j2 = inputStr.size(1) - 1;
      for (b_j1 = n; b_j1 <= j2; b_j1++) {
        inputStr[b_j1 - 1] = inputStr[b_j1];
      }
      if (j2 < 1) {
        j2 = 0;
      } else {
        j2 = nd2 - 1;
      }
      inputStr.set_size(inputStr.size(0), j2);
      i = static_cast<unsigned int>(static_cast<int>(i) - 1);
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
  for (int b_i{0}; b_i < nd2; b_i++) {
    if (inputStr[b_i] == ' ') {
      inputStr[b_i] = ',';
    }
  }
  b_inputStr.set_size(1, inputStr.size(1));
  nd2 = inputStr.size(1);
  for (c_i = 0; c_i < nd2; c_i++) {
    b_inputStr[c_i] = (inputStr[c_i] == '[');
  }
  coder::b_eml_find(b_inputStr, commaLocs);
  b_inputStr.set_size(1, inputStr.size(1));
  nd2 = inputStr.size(1);
  for (c_i = 0; c_i < nd2; c_i++) {
    b_inputStr[c_i] = (inputStr[c_i] == ';');
  }
  coder::b_eml_find(b_inputStr, r);
  b_inputStr.set_size(1, inputStr.size(1));
  nd2 = inputStr.size(1);
  for (c_i = 0; c_i < nd2; c_i++) {
    b_inputStr[c_i] = (inputStr[c_i] == ']');
  }
  coder::b_eml_find(b_inputStr, r1);
  rowDividerLocs.set_size(1, (commaLocs.size(1) + r.size(1)) + r1.size(1));
  nd2 = commaLocs.size(1);
  for (c_i = 0; c_i < nd2; c_i++) {
    rowDividerLocs[c_i] = commaLocs[c_i];
  }
  nd2 = r.size(1);
  for (c_i = 0; c_i < nd2; c_i++) {
    rowDividerLocs[c_i + commaLocs.size(1)] = r[c_i];
  }
  nd2 = r1.size(1);
  for (c_i = 0; c_i < nd2; c_i++) {
    rowDividerLocs[(c_i + commaLocs.size(1)) + r.size(1)] = r1[c_i];
  }
  coder::internal::sort(rowDividerLocs);
  b_inputStr.set_size(1, inputStr.size(1));
  nd2 = inputStr.size(1);
  for (c_i = 0; c_i < nd2; c_i++) {
    b_inputStr[c_i] = (inputStr[c_i] == ',');
  }
  coder::b_eml_find(b_inputStr, commaLocs);
  // Check for the number of columns in the first row to preallocate outMat
  b_inputStr.set_size(1, commaLocs.size(1));
  b_rowDividerLocs = rowDividerLocs[0];
  nd2 = commaLocs.size(1);
  for (c_i = 0; c_i < nd2; c_i++) {
    b_inputStr[c_i] = (commaLocs[c_i] > b_rowDividerLocs);
  }
  r2.set_size(1, commaLocs.size(1));
  b_rowDividerLocs = rowDividerLocs[1];
  nd2 = commaLocs.size(1);
  for (c_i = 0; c_i < nd2; c_i++) {
    r2[c_i] = (commaLocs[c_i] < b_rowDividerLocs);
  }
  nd2 = b_inputStr.size(1);
  j2 = 1;
  for (int b_i{0}; b_i < nd2; b_i++) {
    if (b_inputStr[b_i] && r2[b_i]) {
      j2++;
    }
  }
  outMat.set_size(rowDividerLocs.size(1) - 1, j2);
  nd2 = (rowDividerLocs.size(1) - 1) * j2;
  for (c_i = 0; c_i < nd2; c_i++) {
    outMat[c_i].re = 0.0;
    outMat[c_i].im = 0.0;
  }
  c_i = rowDividerLocs.size(1);
  for (int b_i{0}; b_i <= c_i - 2; b_i++) {
    double rowDividerLocs_tmp;
    int i1;
    b_inputStr.set_size(1, commaLocs.size(1));
    b_rowDividerLocs = rowDividerLocs[b_i];
    nd2 = commaLocs.size(1);
    r2.set_size(1, commaLocs.size(1));
    rowDividerLocs_tmp = rowDividerLocs[b_i + 1];
    for (i1 = 0; i1 < nd2; i1++) {
      n = commaLocs[i1];
      b_inputStr[i1] = (n > b_rowDividerLocs);
      r2[i1] = (n < rowDividerLocs_tmp);
    }
    nd2 = b_inputStr.size(1);
    j2 = 1;
    for (b_j1 = 0; b_j1 < nd2; b_j1++) {
      if (b_inputStr[b_j1] && r2[b_j1]) {
        j2++;
      }
    }
    // numelCols = numelCommasCurr+1;
    nd2 = b_inputStr.size(1) - 1;
    n = 0;
    for (b_j1 = 0; b_j1 <= nd2; b_j1++) {
      if (b_inputStr[b_j1] && r2[b_j1]) {
        n++;
      }
    }
    r3.set_size(1, n);
    n = 0;
    for (b_j1 = 0; b_j1 <= nd2; b_j1++) {
      if (b_inputStr[b_j1] && r2[b_j1]) {
        r3[n] = b_j1 + 1;
        n++;
      }
    }
    nd2 = r3.size(1);
    colDividerLocs.set_size(1, r3.size(1) + 2);
    colDividerLocs[0] = rowDividerLocs[b_i];
    for (i1 = 0; i1 < nd2; i1++) {
      colDividerLocs[i1 + 1] = commaLocs[r3[i1] - 1];
    }
    colDividerLocs[r3.size(1) + 1] = rowDividerLocs_tmp;
    tempRow.set_size(1, j2);
    for (i1 = 0; i1 < j2; i1++) {
      tempRow[i1].re = 0.0;
      tempRow[i1].im = 0.0;
    }
    i1 = colDividerLocs.size(1);
    for (j2 = 0; j2 <= i1 - 2; j2++) {
      b_rowDividerLocs = colDividerLocs[j2];
      rowDividerLocs_tmp = colDividerLocs[j2 + 1];
      if (b_rowDividerLocs + 1.0 > rowDividerLocs_tmp - 1.0) {
        n = 0;
        b_j1 = 0;
      } else {
        n = static_cast<int>(b_rowDividerLocs + 1.0) - 1;
        b_j1 = static_cast<int>(rowDividerLocs_tmp - 1.0);
      }
      nd2 = b_j1 - n;
      c_inputStr.set_size(1, nd2);
      for (b_j1 = 0; b_j1 < nd2; b_j1++) {
        c_inputStr[b_j1] = inputStr[n + b_j1];
      }
      tempRow[j2] = coder::str2double(c_inputStr);
    }
    nd2 = tempRow.size(1);
    for (i1 = 0; i1 < nd2; i1++) {
      outMat[b_i + outMat.size(0) * i1] = tempRow[i1];
    }
  }
}

// End of code generation (str2matrix.cpp)
